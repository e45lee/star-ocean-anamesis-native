// port/decomp/input/framework.c: Ghidra decompiles for the input subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-04 06:12 UTC: tools/decomp.sh '--into' 'input/framework' 'Framework::(CPad|CPadReader|CTouchPanel|CMouse|CKeyboard)::'

// ==== Framework::CKeyboard::Initialize()
// vaddr 0x1e88d64 | ghidra 0x1f88d64 | size 60 | symbol _ZN9Framework9CKeyboard10InitializeEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework9CKeyboard10InitializeEv(long param_1)

{
  long lVar1;
  long lVar2;
  
  lVar2 = 0;
  do {
    lVar1 = param_1 + lVar2;
    lVar2 = lVar2 + 8;
    *(undefined4 *)(lVar1 + 0x104) = 0;
    *(byte *)(lVar1 + 0x100) = *(byte *)(lVar1 + 0x100) & 0xfc;
  } while (lVar2 != 0x800);
  memset(param_1,0,0x100);
  return;
}

// ==== Framework::CKeyboard::Release()
// vaddr 0x1e88da0 | ghidra 0x1f88da0 | size 4 | symbol _ZN9Framework9CKeyboard7ReleaseEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework9CKeyboard7ReleaseEv(void)

{
  return;
}

// ==== Framework::CKeyboard::Progress(float)
// vaddr 0x1e88da4 | ghidra 0x1f88da4 | size 312 | symbol _ZN9Framework9CKeyboard8ProgressEf | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework9CKeyboard8ProgressEf(float param_1,long param_2)

{
  uint uVar1;
  byte bVar2;
  long lVar3;
  ulong uVar4;
  float *pfVar5;
  ulong uVar6;
  float fVar7;
  
  uVar4 = 0;
  do {
    uVar6 = uVar4 >> 3;
    uVar1 = (int)uVar4 + 2;
    uVar4 = (ulong)uVar1;
    *(undefined1 *)(param_2 + uVar6) = 0;
  } while (uVar1 != 0x100);
  lVar3 = Aska::Keyboard::GetInstance()();
  if (lVar3 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964858/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Keyboard.cpp"*/,100,&UNK_027e7588/*"pSubstance is null."*/);
  }
  uVar4 = 0;
  do {
    if (0 < *(int *)(lVar3 + 0x2ac + uVar4 * 4)) {
      uVar6 = uVar4 >> 3 & 0x1fffffff;
      *(byte *)(param_2 + uVar6) =
           (byte)(1 << (ulong)((uint)uVar4 & 7)) | *(byte *)(param_2 + uVar6);
    }
    uVar4 = uVar4 + 1;
  } while (uVar4 != 0x100);
  uVar4 = 0;
  pfVar5 = (float *)(param_2 + 0x104);
  do {
    if ((1 << (ulong)((uint)uVar4 & 7) & (uint)*(byte *)(param_2 + (uVar4 >> 3 & 0x1fffffff))) == 0)
    {
      *pfVar5 = 0.0;
      *(byte *)(pfVar5 + -1) = *(byte *)(pfVar5 + -1) & 0xfc;
    }
    else {
      bVar2 = *(byte *)(pfVar5 + -1);
      fVar7 = *pfVar5 - param_1;
      *pfVar5 = fVar7;
      if (fVar7 <= 0.0) {
        *(byte *)(pfVar5 + -1) = bVar2 | 1;
        if ((bVar2 >> 1 & 1) == 0) {
          *pfVar5 = fVar7 + 12.0;
          *(byte *)(pfVar5 + -1) = bVar2 | 3;
        }
        else {
          *pfVar5 = fVar7 + 6.0;
        }
      }
      else {
        *(byte *)(pfVar5 + -1) = bVar2 & 0xfe;
      }
    }
    uVar4 = uVar4 + 1;
    pfVar5 = pfVar5 + 2;
  } while (uVar4 != 0x100);
  return;
}

// ==== Framework::CKeyboard::Now(int) const
// vaddr 0x1e88edc | ghidra 0x1f88edc | size 148 | symbol _ZNK9Framework9CKeyboard3NowEi | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK9Framework9CKeyboard3NowEi(long param_1,uint param_2)

{
  uint uVar1;
  
  if (0xff < (int)param_2) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964858/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Keyboard.cpp"*/,0x8c,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,param_2,0x100);
  }
  uVar1 = param_2 + 7;
  if (-1 < (int)param_2) {
    uVar1 = param_2;
  }
  uVar1 = (int)uVar1 >> 3;
  if (0xff < uVar1) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964858/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Keyboard.cpp"*/,0x8f,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,uVar1,0x100);
  }
  return (1 << (ulong)(param_2 & 7) & (uint)*(byte *)(param_1 + (ulong)uVar1)) != 0;
}

// ==== Framework::CKeyboard::Repeat(int) const
// vaddr 0x1e88f70 | ghidra 0x1f88f70 | size 80 | symbol _ZNK9Framework9CKeyboard6RepeatEi | lib libSOA-3.7.0.so | 2026-10-04
byte _ZNK9Framework9CKeyboard6RepeatEi(long param_1,int param_2)

{
  if (0xff < param_2) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964858/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Keyboard.cpp"*/,0x95,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,param_2,0x100);
  }
  return *(byte *)(param_1 + (long)param_2 * 8 + 0x100) & 1;
}

// ==== Framework::CKeyboard::Press() const
// vaddr 0x1e88fc0 | ghidra 0x1f88fc0 | size 40 | symbol _ZNK9Framework9CKeyboard5PressEv | lib libSOA-3.7.0.so | 2026-10-04
uint _ZNK9Framework9CKeyboard5PressEv(long param_1)

{
  uint uVar1;
  
  uVar1 = 0;
  do {
    if ((*(byte *)(param_1 + (long)(int)uVar1 * 8 + 0x100) & 1) != 0) {
      return uVar1;
    }
    uVar1 = uVar1 + 1;
  } while (uVar1 < 0x100);
  return 0;
}

// ==== Framework::CKeyboard::IsDrawableCharacter(unsigned int)
// vaddr 0x1e88fe8 | ghidra 0x1f88fe8 | size 56 | symbol _ZN9Framework9CKeyboard19IsDrawableCharacterEj | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN9Framework9CKeyboard19IsDrawableCharacterEj(undefined8 param_1)

{
  long lVar1;
  
  if ((int)param_1 != 0) {
    lVar1 = 0;
    while ((int)(char)(&UNK_029648ac)[lVar1] != (int)param_1) {
      lVar1 = lVar1 + 1;
      if (99 < (uint)lVar1) {
        return 0;
      }
    }
    param_1 = 1;
  }
  return param_1;
}

// ==== Framework::CMouse::Initialize()
// vaddr 0x1e8b7f4 | ghidra 0x1f8b7f4 | size 68 | symbol _ZN9Framework6CMouse10InitializeEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework6CMouse10InitializeEv(undefined8 *param_1)

{
  *param_1 = 0;
  *(byte *)(param_1 + 1) = *(byte *)(param_1 + 1) & 0xf0;
  *(byte *)((long)param_1 + 0xc) = *(byte *)((long)param_1 + 0xc) & 0xf0;
  *(byte *)(param_1 + 2) = *(byte *)(param_1 + 2) & 0xf0;
  *(byte *)((long)param_1 + 0x14) = *(byte *)((long)param_1 + 0x14) & 0xf0;
  *(byte *)(param_1 + 3) = *(byte *)(param_1 + 3) & 0xf0;
  return;
}

// ==== Framework::CMouse::Reset()
// vaddr 0x1e8b838 | ghidra 0x1f8b838 | size 68 | symbol _ZN9Framework6CMouse5ResetEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework6CMouse5ResetEv(undefined8 *param_1)

{
  *param_1 = 0;
  *(byte *)(param_1 + 1) = *(byte *)(param_1 + 1) & 0xf0;
  *(byte *)((long)param_1 + 0xc) = *(byte *)((long)param_1 + 0xc) & 0xf0;
  *(byte *)(param_1 + 2) = *(byte *)(param_1 + 2) & 0xf0;
  *(byte *)((long)param_1 + 0x14) = *(byte *)((long)param_1 + 0x14) & 0xf0;
  *(byte *)(param_1 + 3) = *(byte *)(param_1 + 3) & 0xf0;
  return;
}

// ==== Framework::CMouse::Progress(float)
// vaddr 0x1e8b87c | ghidra 0x1f8b87c | size 372 | symbol _ZN9Framework6CMouse8ProgressEf | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework6CMouse8ProgressEf(undefined8 *param_1)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  byte bVar6;
  byte bVar7;
  byte bVar8;
  byte bVar9;
  byte bVar10;
  long lVar11;
  
  *param_1 = 0;
  *(byte *)(param_1 + 1) = *(byte *)(param_1 + 1) & 0xfe;
  *(byte *)((long)param_1 + 0xc) = *(byte *)((long)param_1 + 0xc) & 0xfe;
  *(byte *)(param_1 + 2) = *(byte *)(param_1 + 2) & 0xfe;
  lVar11 = Aska::Mouse::GetInstance()();
  if ((lVar11 != 0) && (*(char *)(lVar11 + 0x9a) != '\0')) {
    *(undefined4 *)param_1 = *(undefined4 *)(lVar11 + 0x2fc);
    *(undefined4 *)((long)param_1 + 4) = *(undefined4 *)(lVar11 + 0x300);
    *(byte *)(param_1 + 1) = *(byte *)(param_1 + 1) & 0xfe | *(byte *)(lVar11 + 0x2c0) & 1;
    *(byte *)((long)param_1 + 0xc) =
         *(byte *)((long)param_1 + 0xc) & 0xfe | *(byte *)(lVar11 + 0x2c4) & 1;
    bVar1 = *(byte *)(lVar11 + 0x2c8);
    *(byte *)(param_1 + 3) = *(byte *)(param_1 + 3) & 0xfe;
    *(byte *)(param_1 + 2) = *(byte *)(param_1 + 2) & 0xfe | bVar1 & 1;
    *(byte *)((long)param_1 + 0x14) = *(byte *)((long)param_1 + 0x14) & 0xfe;
  }
  Framework::CMouse::InputFromPanel()(param_1);
  bVar1 = *(byte *)(param_1 + 1);
  bVar2 = *(byte *)((long)param_1 + 0xc);
  bVar3 = *(byte *)(param_1 + 2);
  bVar4 = *(byte *)((long)param_1 + 0x14);
  bVar5 = *(byte *)(param_1 + 3);
  bVar6 = bVar1 ^ bVar1 >> 1;
  bVar7 = bVar2 ^ bVar2 >> 1;
  bVar8 = bVar3 ^ bVar3 >> 1;
  bVar9 = bVar4 ^ bVar4 >> 1;
  bVar10 = bVar5 ^ bVar5 >> 1;
  *(byte *)(param_1 + 1) =
       bVar1 & 0xf0 |
       bVar1 & 1 | (bVar1 & 1) << 1 | (bVar1 & bVar6 & 1) << 2 | (bVar6 & (bVar1 ^ 0xff) & 1) << 3;
  *(byte *)((long)param_1 + 0xc) =
       bVar2 & 0xf0 |
       bVar2 & 1 | (bVar2 & 1) << 1 | (bVar2 & bVar7 & 1) << 2 | (bVar7 & (bVar2 ^ 0xff) & 1) << 3;
  *(byte *)(param_1 + 2) =
       bVar3 & 0xf0 |
       bVar3 & 1 | (bVar3 & 1) << 1 | (bVar3 & bVar8 & 1) << 2 | (bVar8 & (bVar3 ^ 0xff) & 1) << 3;
  *(byte *)((long)param_1 + 0x14) =
       bVar4 & 0xf0 |
       bVar4 & 1 | (bVar4 & 1) << 1 | (bVar4 & bVar9 & 1) << 2 | (bVar9 & (bVar4 ^ 0xff) & 1) << 3;
  *(byte *)(param_1 + 3) =
       bVar5 & 0xf0 |
       bVar5 & 1 | (bVar5 & 1) << 1 | (bVar5 & bVar10 & 1) << 2 | (bVar10 & (bVar5 ^ 0xff) & 1) << 3
  ;
  return;
}

// ==== Framework::CMouse::InputFromPanel()
// vaddr 0x1e8b9f0 | ghidra 0x1f8b9f0 | size 196 | symbol _ZN9Framework6CMouse14InputFromPanelEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework6CMouse14InputFromPanelEv(undefined4 *param_1)

{
  undefined *puVar1;
  ulong uVar2;
  long lVar3;
  
  puVar1 = PTR__ZN9Framework10TSingletonINS_11CTouchPanelEE11m_pInstanceE_02cbd318;
  if ((*(long *)PTR__ZN9Framework10TSingletonINS_11CTouchPanelEE11m_pInstanceE_02cbd318 != 0) &&
     (uVar2 = Framework::CTouchPanel::IsConnected() const(*(long *)
                               PTR__ZN9Framework10TSingletonINS_11CTouchPanelEE11m_pInstanceE_02cbd318
                             ), (uVar2 & 1) != 0)) {
    lVar3 = *(long *)puVar1;
    if (lVar3 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029612b1/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
      lVar3 = *(long *)puVar1;
    }
    *param_1 = *(undefined4 *)(lVar3 + 0x10);
    lVar3 = *(long *)puVar1;
    if (lVar3 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029612b1/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
      lVar3 = *(long *)puVar1;
    }
    param_1[1] = *(undefined4 *)(lVar3 + 0x14);
    lVar3 = *(long *)puVar1;
    if (lVar3 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029612b1/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
      lVar3 = *(long *)puVar1;
    }
    if (*(char *)(lVar3 + 0x38) != '\0') {
      *(byte *)(param_1 + 2) = *(byte *)(param_1 + 2) | 1;
    }
  }
  return;
}

// ==== Framework::CPad::CPad()
// vaddr 0x1e8bfbc | ghidra 0x1f8bfbc | size 96 | symbol _ZN9Framework4CPadC1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework4CPadC2Ev(long *param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZN9Framework10TSingletonINS_4CPadEE11m_pInstanceE_02cbef78;
  if (*(long *)PTR__ZN9Framework10TSingletonINS_4CPadEE11m_pInstanceE_02cbef78 != 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029612b1/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TSingleton.h"*/,0x15,&UNK_027daee5/*"m_pInstance isn't null.(%08x)"*/);
  }
  *(long **)puVar1 = param_1;
  *param_1 = (long)(PTR__ZTVN9Framework4CPadE_02cbf140 + 0x10);
  Framework::CMutex::CMutex()(param_1 + 2);
  param_1[0x19] = 0;
  return;
}

// ==== Framework::CPad::~CPad()
// vaddr 0x1e8c01c | ghidra 0x1f8c01c | size 244 | symbol _ZN9Framework4CPadD2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework4CPadD1Ev(long *param_1)

{
  undefined *puVar1;
  long lVar2;
  long *plVar3;
  long lVar4;
  long lVar5;
  
  *param_1 = (long)(PTR__ZTVN9Framework4CPadE_02cbf140 + 0x10);
  Framework::CMutex::Release()(param_1 + 2);
  lVar5 = param_1[0x19];
  if (lVar5 != 0) {
    lVar4 = *(long *)(lVar5 + -8);
    if (lVar4 != 0) {
      lVar4 = lVar4 * 0x68;
      puVar1 = PTR__ZTVN9Framework4CPad5CUnitE_02cbaa18 + 0x10;
      do {
        lVar2 = lVar5 + lVar4;
        *(undefined **)(lVar2 + -0x68) = puVar1;
        if (*(int *)(lVar2 + -0x60) != -1) {
          plVar3 = (long *)Aska::Global::GetPeripheral(int)();
          if (plVar3 != (long *)0x0) {
            (**(code **)(*plVar3 + 8))();
            Aska::Global::ReleasePeripheral(int)(*(undefined4 *)(lVar2 + -0x60));
          }
          *(undefined4 *)(lVar2 + -0x60) = 0xffffffff;
        }
        lVar4 = lVar4 + -0x68;
      } while (lVar4 != 0);
    }
    operator delete[](void*)((long *)(lVar5 + -8));
    param_1[0x19] = 0;
  }
  Framework::CMutex::~CMutex()(param_1 + 2);
  puVar1 = PTR__ZN9Framework10TSingletonINS_4CPadEE11m_pInstanceE_02cbef78;
  if (*(long *)PTR__ZN9Framework10TSingletonINS_4CPadEE11m_pInstanceE_02cbef78 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029612b1/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TSingleton.h"*/,0x1d,&UNK_027daf21/*"m_pInstance is null."*/);
  }
  *(undefined8 *)puVar1 = 0;
  return;
}

// ==== Framework::CPad::Release()
// vaddr 0x1e8c110 | ghidra 0x1f8c110 | size 164 | symbol _ZN9Framework4CPad7ReleaseEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework4CPad7ReleaseEv(long param_1)

{
  undefined *puVar1;
  long lVar2;
  long *plVar3;
  long lVar4;
  long lVar5;
  
  Framework::CMutex::Release()(param_1 + 0x10);
  lVar5 = *(long *)(param_1 + 200);
  if (lVar5 != 0) {
    lVar4 = *(long *)(lVar5 + -8);
    if (lVar4 != 0) {
      lVar4 = lVar4 * 0x68;
      puVar1 = PTR__ZTVN9Framework4CPad5CUnitE_02cbaa18 + 0x10;
      do {
        lVar2 = lVar5 + lVar4;
        *(undefined **)(lVar2 + -0x68) = puVar1;
        if (*(int *)(lVar2 + -0x60) != -1) {
          plVar3 = (long *)Aska::Global::GetPeripheral(int)();
          if (plVar3 != (long *)0x0) {
            (**(code **)(*plVar3 + 8))();
            Aska::Global::ReleasePeripheral(int)(*(undefined4 *)(lVar2 + -0x60));
          }
          *(undefined4 *)(lVar2 + -0x60) = 0xffffffff;
        }
        lVar4 = lVar4 + -0x68;
      } while (lVar4 != 0);
    }
    operator delete[](void*)((long *)(lVar5 + -8));
    *(undefined8 *)(param_1 + 200) = 0;
  }
  return;
}

// ==== Framework::CPad::~CPad()
// vaddr 0x1e8c1b4 | ghidra 0x1f8c1b4 | size 24 | symbol _ZN9Framework4CPadD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework4CPadD0Ev(undefined8 param_1)

{
  Framework::CPad::~CPad()();
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Framework::CPad::Initialize()
// vaddr 0x1e8c1cc | ghidra 0x1f8c1cc | size 612 | symbol _ZN9Framework4CPad10InitializeEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework4CPad10InitializeEv(long param_1)

{
  undefined *puVar1;
  undefined4 uVar2;
  undefined8 *puVar3;
  long *plVar4;
  uint uVar5;
  long lVar6;
  code *pcVar7;
  uint uVar8;
  
  if (*(long *)(param_1 + 200) != 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964cc8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Pad.cpp"*/,0x70,&UNK_02964d17/*"m_pUnits isn't null.(%08x)"*/);
  }
  Framework::CMutex::Initialize()(param_1 + 0x10);
  *(undefined4 *)(param_1 + 0xc0) = 1;
  puVar3 = (undefined8 *)operator new[](unsigned long, std::nothrow_t const&)(0x70,PTR__ZSt7nothrow_02cb9a80);
  puVar1 = PTR__ZTVN9Framework4CPad5CUnitE_02cbaa18;
  if (puVar3 == (undefined8 *)0x0) {
    plVar4 = (long *)0x0;
  }
  else {
    *puVar3 = 1;
    plVar4 = puVar3 + 1;
    *plVar4 = (long)(puVar1 + 0x10);
    *(undefined4 *)(puVar3 + 2) = 0xffffffff;
  }
  uVar8 = 0;
  uVar5 = 1;
  *(long **)(param_1 + 200) = plVar4;
  *(undefined4 *)(param_1 + 0xd0) = 0;
  if (plVar4 != (long *)0x0) goto code_r0x01f8c28c;
  do {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964cc8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Pad.cpp"*/,0x98,&UNK_02964d32/*"m_pUnits is null."*/);
    if (*(uint *)(param_1 + 0xc0) <= uVar8) goto code_r0x01f8c294;
    while( true ) {
      Framework::CPad::CUnit::Initialize(unsigned int)(*(long *)(param_1 + 200) + (ulong)uVar8 * 0x68,uVar8);
      uVar5 = *(uint *)(param_1 + 0xc0);
      uVar8 = uVar8 + 1;
      if (uVar5 <= uVar8) {
        if (uVar5 != 0) {
          uVar8 = 0;
          do {
            if (*(long *)(param_1 + 200) == 0) {
              Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964cc8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Pad.cpp"*/,0x98,&UNK_02964d32/*"m_pUnits is null."*/);
              uVar5 = *(uint *)(param_1 + 0xc0);
            }
            if (uVar5 <= uVar8) {
              Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964cc8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Pad.cpp"*/,0x99,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,uVar8);
            }
            lVar6 = *(long *)(param_1 + 200) + (ulong)uVar8 * 0x68;
            *(undefined8 *)(lVar6 + 0x2c) = 0;
            *(undefined8 *)(lVar6 + 0x24) = 0;
            *(undefined8 *)(lVar6 + 0x1c) = 0;
            *(undefined8 *)(lVar6 + 0x14) = 0;
            *(undefined8 *)(lVar6 + 0xc) = 0;
            uVar5 = *(uint *)(param_1 + 0xc0);
            uVar8 = uVar8 + 1;
          } while (uVar8 < uVar5);
        }
        *(undefined8 *)(param_1 + 0xda) = 0;
        *(undefined8 *)(param_1 + 0xd4) = 0;
        *(undefined8 *)(param_1 + 0xfc) = 0;
        *(undefined8 *)(param_1 + 0xf4) = 0;
        *(undefined8 *)(param_1 + 0xec) = 0;
        *(undefined8 *)(param_1 + 0xe4) = 0;
        *(undefined8 *)(param_1 + 0x104) = 0;
        plVar4 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x28,PTR__ZSt7nothrow_02cb9a80);
        puVar1 = PTR__ZTVN4Aska4TaskE_02cbe020;
        if (plVar4 != (long *)0x0) {
          plVar4[2] = 0;
          plVar4[3] = 0;
          *(undefined2 *)((long)plVar4 + 0x24) = 0;
          pcVar7 = *(code **)(puVar1 + 0x68);
          *plVar4 = (long)(puVar1 + 0x10);
          plVar4[1] = 0;
          *(undefined1 *)((long)plVar4 + 0x26) = 0;
          uVar2 = (*pcVar7)(plVar4);
          puVar1 = PTR__ZN9Framework10TSingletonINS_10CPadReaderEE11m_pInstanceE_02cc3868;
          *(undefined4 *)(plVar4 + 4) = uVar2;
          if (*(long *)puVar1 != 0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029612b1/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TSingleton.h"*/,0x15,&UNK_027daee5/*"m_pInstance isn't null.(%08x)"*/);
          }
          *(long **)puVar1 = plVar4;
          *plVar4 = (long)(PTR__ZTVN9Framework10CPadReaderE_02cbbab8 + 0x10);
        }
        return;
      }
      if (*(long *)(param_1 + 200) == 0) break;
code_r0x01f8c28c:
      if (uVar5 <= uVar8) {
code_r0x01f8c294:
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964cc8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Pad.cpp"*/,0x99,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,uVar8);
      }
    }
  } while( true );
}

// ==== Framework::CPad::Mode(unsigned int)
// vaddr 0x1e8c430 | ghidra 0x1f8c430 | size 68 | symbol _ZN9Framework4CPad4ModeEj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework4CPad4ModeEj(long param_1,int param_2)

{
  if (param_2 != 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964cc8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Pad.cpp"*/,0x110,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,param_2,1);
  }
  *(int *)(param_1 + 0xd0) = param_2;
  return;
}

// ==== Framework::CPad::rUnit(unsigned int)
// vaddr 0x1e8c474 | ghidra 0x1f8c474 | size 112 | symbol _ZN9Framework4CPad5rUnitEj | lib libSOA-3.7.0.so | 2026-10-04
long _ZN9Framework4CPad5rUnitEj(long param_1,uint param_2)

{
  if (*(long *)(param_1 + 200) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964cc8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Pad.cpp"*/,0x98,&UNK_02964d32/*"m_pUnits is null."*/);
  }
  if (*(uint *)(param_1 + 0xc0) <= param_2) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964cc8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Pad.cpp"*/,0x99,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,param_2);
  }
  return *(long *)(param_1 + 200) + (ulong)param_2 * 0x68;
}

// ==== Framework::CPad::CUnit::Initialize(unsigned int)
// vaddr 0x1e8c4e4 | ghidra 0x1f8c4e4 | size 364 | symbol _ZN9Framework4CPad5CUnit10InitializeEj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework4CPad5CUnit10InitializeEj(long param_1,int param_2)

{
  undefined4 uVar1;
  long *plVar2;
  undefined8 uVar3;
  long lVar4;
  
  if (*(int *)(param_1 + 8) != -1) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964cc8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Pad.cpp"*/,0x183,&UNK_027f6dcb/*"Already initialized.(%d)"*/);
  }
  if (param_2 == 0) {
    *(undefined4 *)(param_1 + 8) = 0;
  }
  else {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964cc8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Pad.cpp"*/,0x184,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,param_2,1);
    *(int *)(param_1 + 8) = param_2;
    if (param_2 == -1) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964cc8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Pad.cpp"*/,0x186,&UNK_02964d44/*"Illegal port number.(%d)"*/,0xffffffff);
      param_2 = *(int *)(param_1 + 8);
    }
  }
  plVar2 = (long *)Aska::Global::GetPeripheral(int)(param_2);
  if (plVar2 == (long *)0x0) {
    uVar1 = *(undefined4 *)(param_1 + 8);
    uVar3 = Aska::Pad::InstantiateAppropriatePad()();
    Aska::Global::RegisterPeripheral(int, Aska::BasePeripheral*)(uVar1,uVar3);
    plVar2 = (long *)Aska::Global::GetPeripheral(int)(*(undefined4 *)(param_1 + 8));
    if (plVar2 == (long *)0x0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964cc8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Pad.cpp"*/,399,&UNK_02964d5d/*"pAskaPad is null."*/);
    }
  }
  (**(code **)(*plVar2 + 0x38))(plVar2,*(undefined4 *)(param_1 + 8));
  Aska::Pad::SetAnalogAsDigital(bool)(plVar2,1);
  Aska::Pad::EnableRumble(bool)(plVar2,0);
  Aska::Pad::SetRepeatThreshold(unsigned char)(plVar2,0xc);
  Aska::Pad::SetRepeatInterval(unsigned char)(plVar2,6);
  lVar4 = Aska::Global::GetPeripheral(int)(*(undefined4 *)(param_1 + 8));
  if (lVar4 != 0) {
    Aska::Pad::SetAnalogAsDigital(bool)(lVar4,0);
    Aska::Pad::SetRepeatThreshold(unsigned char)(lVar4,0xc);
    Aska::Pad::SetRepeatInterval(unsigned char)(lVar4,6);
  }
  *(undefined8 *)(param_1 + 0x54) = 0;
  *(undefined8 *)(param_1 + 0x4c) = 0;
  *(undefined8 *)(param_1 + 0x44) = 0;
  *(undefined8 *)(param_1 + 0x3c) = 0;
  *(undefined8 *)(param_1 + 0x34) = 0;
  return;
}

// ==== Framework::CPad::Clear()
// vaddr 0x1e8c650 | ghidra 0x1f8c650 | size 192 | symbol _ZN9Framework4CPad5ClearEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework4CPad5ClearEv(long param_1)

{
  uint uVar1;
  long lVar2;
  uint uVar3;
  
  uVar1 = *(uint *)(param_1 + 0xc0);
  if (uVar1 != 0) {
    uVar3 = 0;
    do {
      if (*(long *)(param_1 + 200) == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964cc8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Pad.cpp"*/,0x98,&UNK_02964d32/*"m_pUnits is null."*/);
        uVar1 = *(uint *)(param_1 + 0xc0);
      }
      if (uVar1 <= uVar3) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964cc8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Pad.cpp"*/,0x99,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,uVar3);
      }
      lVar2 = *(long *)(param_1 + 200) + (ulong)uVar3 * 0x68;
      *(undefined8 *)(lVar2 + 0x2c) = 0;
      *(undefined8 *)(lVar2 + 0x24) = 0;
      *(undefined8 *)(lVar2 + 0x1c) = 0;
      *(undefined8 *)(lVar2 + 0x14) = 0;
      *(undefined8 *)(lVar2 + 0xc) = 0;
      uVar1 = *(uint *)(param_1 + 0xc0);
      uVar3 = uVar3 + 1;
    } while (uVar3 < uVar1);
  }
  return;
}

// ==== Framework::CPad::tMerged::Reset()
// vaddr 0x1e8c710 | ghidra 0x1f8c710 | size 24 | symbol _ZN9Framework4CPad7tMerged5ResetEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework4CPad7tMerged5ResetEv(undefined8 *param_1)

{
  *(undefined8 *)((long)param_1 + 6) = 0;
  *param_1 = 0;
  param_1[6] = 0;
  param_1[3] = 0;
  param_1[2] = 0;
  param_1[5] = 0;
  param_1[4] = 0;
  return;
}

// ==== Framework::CPad::NumUnits() const
// vaddr 0x1e8c728 | ghidra 0x1f8c728 | size 8 | symbol _ZNK9Framework4CPad8NumUnitsEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK9Framework4CPad8NumUnitsEv(long param_1)

{
  return *(undefined4 *)(param_1 + 0xc0);
}

// ==== Framework::CPad::Unit(unsigned int) const
// vaddr 0x1e8c730 | ghidra 0x1f8c730 | size 112 | symbol _ZNK9Framework4CPad4UnitEj | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK9Framework4CPad4UnitEj(long param_1,uint param_2)

{
  if (*(long *)(param_1 + 200) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964cc8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Pad.cpp"*/,0x9f,&UNK_02964d32/*"m_pUnits is null."*/);
  }
  if (*(uint *)(param_1 + 0xc0) <= param_2) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964cc8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Pad.cpp"*/,0xa0,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,param_2);
  }
  return *(long *)(param_1 + 200) + (ulong)param_2 * 0x68;
}

// ==== Framework::CPad::Progress(float)
// vaddr 0x1e8c7a0 | ghidra 0x1f8c7a0 | size 484 | symbol _ZN9Framework4CPad8ProgressEf | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework4CPad8ProgressEf(undefined8 param_1,long param_2)

{
  undefined *puVar1;
  long *plVar2;
  long lVar3;
  uint uVar4;
  uint uVar5;
  
  if (*(long *)(param_2 + 200) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964cc8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Pad.cpp"*/,0xbc,&UNK_02964d32/*"m_pUnits is null."*/);
  }
  puVar1 = PTR__ZN9Framework10TSingletonINS_10CPadReaderEE11m_pInstanceE_02cc3868;
  plVar2 = *(long **)PTR__ZN9Framework10TSingletonINS_10CPadReaderEE11m_pInstanceE_02cc3868;
  if (plVar2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029612b1/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    plVar2 = *(long **)puVar1;
  }
  (**(code **)(*plVar2 + 0x68))(plVar2,0);
  if (*(int *)(param_2 + 0xd0) != 0) {
    return;
  }
  lVar3 = Aska::Global::GetActivePad()();
  if (lVar3 != 0) {
    Aska::Pad::Flip()();
  }
  uVar4 = *(uint *)(param_2 + 0xc0);
  if (uVar4 != 0) {
    uVar5 = 0;
    do {
      if (*(long *)(param_2 + 200) == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964cc8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Pad.cpp"*/,0x98,&UNK_02964d32/*"m_pUnits is null."*/);
        uVar4 = *(uint *)(param_2 + 0xc0);
      }
      if (uVar4 <= uVar5) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964cc8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Pad.cpp"*/,0x99,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,uVar5);
      }
      lVar3 = *(long *)(param_2 + 200) + (ulong)uVar5 * 0x68;
      *(undefined1 *)(lVar3 + 0x60) = 0;
      *(undefined4 *)(lVar3 + 0x5c) = 0;
      if (*(long *)(param_2 + 200) == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964cc8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Pad.cpp"*/,0x98,&UNK_02964d32/*"m_pUnits is null."*/);
      }
      if (*(uint *)(param_2 + 0xc0) <= uVar5) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964cc8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Pad.cpp"*/,0x99,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,uVar5);
      }
      Framework::CPad::CUnit::Progress(float)(param_1,*(long *)(param_2 + 200) + (ulong)uVar5 * 0x68);
      if (*(long *)(param_2 + 200) == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964cc8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Pad.cpp"*/,0x98,&UNK_02964d32/*"m_pUnits is null."*/);
      }
      if (*(uint *)(param_2 + 0xc0) <= uVar5) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964cc8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Pad.cpp"*/,0x99,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,uVar5);
      }
      Framework::CPad::CUnit::Copy()(*(long *)(param_2 + 200) + (ulong)uVar5 * 0x68);
      uVar4 = *(uint *)(param_2 + 0xc0);
      uVar5 = uVar5 + 1;
    } while (uVar5 < uVar4);
  }
  (*(code *)PTR__ZN9Framework4CPad5MergeEv_02c99f20)(param_2);
  return;
}

// ==== Framework::CPad::CUnit::UnlockAll()
// vaddr 0x1e8c984 | ghidra 0x1f8c984 | size 12 | symbol _ZN9Framework4CPad5CUnit9UnlockAllEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework4CPad5CUnit9UnlockAllEv(long param_1)

{
  *(undefined1 *)(param_1 + 0x60) = 0;
  *(undefined4 *)(param_1 + 0x5c) = 0;
  return;
}

// ==== Framework::CPad::CUnit::Progress(float)
// vaddr 0x1e8c990 | ghidra 0x1f8c990 | size 188 | symbol _ZN9Framework4CPad5CUnit8ProgressEf | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework4CPad5CUnit8ProgressEf(float param_1,long param_2)

{
  long lVar1;
  int iVar2;
  int iVar3;
  float fVar4;
  
  lVar1 = Aska::Global::GetPeripheral(int)(*(undefined4 *)(param_2 + 8));
  if (lVar1 != 0) {
    Aska::Pad::SetAnalogAsDigital(bool)(lVar1,0);
    if (param_1 <= 3.0) {
      fVar4 = 2.0;
      if (param_1 != 0.0) {
        fVar4 = param_1;
      }
      iVar2 = (int)(12.0 / fVar4);
      iVar3 = (int)(6.0 / fVar4);
      if (iVar2 < 4) {
        iVar2 = 3;
      }
      if (iVar3 < 3) {
        iVar3 = 2;
      }
      Aska::Pad::SetRepeatThreshold(unsigned char)(2,lVar1,iVar2);
    }
    else {
      Aska::Pad::SetRepeatThreshold(unsigned char)(lVar1,0xc);
      iVar3 = 0xc;
    }
    (*(code *)PTR__ZN4Aska3Pad17SetRepeatIntervalEh_02cad8b0)(lVar1,iVar3);
    return;
  }
  return;
}

// ==== Framework::CPad::CUnit::Copy()
// vaddr 0x1e8ca4c | ghidra 0x1f8ca4c | size 192 | symbol _ZN9Framework4CPad5CUnit4CopyEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework4CPad5CUnit4CopyEv(long param_1)

{
  long *plVar1;
  long lVar2;
  ulong uVar3;
  
  if (*(int *)(param_1 + 8) == -1) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964cc8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Pad.cpp"*/,0x1c4,&UNK_02964d6f/*"Uninitialized instance."*/);
    lVar2 = Aska::Global::GetPeripheral(int)(*(undefined4 *)(param_1 + 8));
    plVar1 = (long *)PTR__ZN9Framework10TSingletonINS_4CPadEE11m_pInstanceE_02cbef78;
  }
  else {
    lVar2 = Aska::Global::GetPeripheral(int)();
    plVar1 = (long *)PTR__ZN9Framework10TSingletonINS_4CPadEE11m_pInstanceE_02cbef78;
  }
  PTR__ZN9Framework10TSingletonINS_4CPadEE11m_pInstanceE_02cbef78 = (undefined *)plVar1;
  if (lVar2 != 0) {
    lVar2 = *plVar1;
    if (lVar2 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029612b1/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
      lVar2 = *plVar1;
    }
    lVar2 = lVar2 + 0x10;
    uVar3 = Framework::CMutex::IsInitialized() const(lVar2);
    if ((uVar3 & 1) == 0) {
      Framework::CMutex::Initialize()(lVar2);
    }
    Framework::CMutex::Lock()(lVar2);
    Framework::CMutex::Unlock()(lVar2);
    *(undefined8 *)(param_1 + 0x2c) = *(undefined8 *)(param_1 + 0x54);
    *(undefined8 *)(param_1 + 0x24) = *(undefined8 *)(param_1 + 0x4c);
    *(undefined8 *)(param_1 + 0x1c) = *(undefined8 *)(param_1 + 0x44);
    *(undefined8 *)(param_1 + 0x14) = *(undefined8 *)(param_1 + 0x3c);
    *(undefined8 *)(param_1 + 0xc) = *(undefined8 *)(param_1 + 0x34);
  }
  return;
}

// ==== Framework::CPad::Merge()
// vaddr 0x1e8cb0c | ghidra 0x1f8cb0c | size 1388 | symbol _ZN9Framework4CPad5MergeEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework4CPad5MergeEv(long param_1)

{
  int iVar1;
  int iVar2;
  byte bVar3;
  short sVar4;
  undefined *puVar5;
  long lVar6;
  long lVar7;
  ulong uVar8;
  long lVar9;
  uint uVar10;
  uint *puVar11;
  float fVar12;
  
  puVar11 = (uint *)(param_1 + 0xe4);
  *(undefined8 *)(param_1 + 0xec) = 0;
  puVar11[0] = 0;
  puVar11[1] = 0;
  *(undefined8 *)(param_1 + 0xda) = 0;
  *(undefined8 *)(param_1 + 0xd4) = 0;
  *(undefined8 *)(param_1 + 0x104) = 0;
  *(undefined8 *)(param_1 + 0xfc) = 0;
  *(undefined8 *)(param_1 + 0xf4) = 0;
  puVar5 = PTR__ZN9Framework10TSingletonINS_9CKeyboardEE11m_pInstanceE_02cbebc8;
  lVar6 = *(long *)PTR__ZN9Framework10TSingletonINS_9CKeyboardEE11m_pInstanceE_02cbebc8;
  if (lVar6 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029612b1/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar6 = *(long *)puVar5;
  }
  Framework::CKeyboard::Now(int) const(lVar6,0x85);
  puVar5 = PTR__ZN9Framework10TSingletonINS_4CPadEE11m_pInstanceE_02cbef78;
  uVar10 = 0;
  lVar6 = *(long *)PTR__ZN9Framework10TSingletonINS_4CPadEE11m_pInstanceE_02cbef78;
  while( true ) {
    if (lVar6 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029612b1/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
      lVar6 = *(long *)puVar5;
    }
    if (*(uint *)(lVar6 + 0xc0) <= uVar10) break;
    if (lVar6 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029612b1/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
      lVar6 = *(long *)puVar5;
      lVar7 = *(long *)(lVar6 + 200);
    }
    else {
      lVar7 = *(long *)(lVar6 + 200);
    }
    if (lVar7 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964cc8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Pad.cpp"*/,0x9f,&UNK_02964d32/*"m_pUnits is null."*/);
    }
    if (*(uint *)(lVar6 + 0xc0) <= uVar10) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964cc8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Pad.cpp"*/,0xa0,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,uVar10);
    }
    lVar6 = *(long *)(lVar6 + 200);
    lVar7 = lVar6 + (ulong)uVar10 * 0x68;
    *(ushort *)(param_1 + 0xd4) = *(ushort *)(param_1 + 0xd4) | *(ushort *)(lVar7 + 0xc);
    *(ushort *)(param_1 + 0xd6) = *(ushort *)(param_1 + 0xd6) | *(ushort *)(lVar7 + 0xe);
    *(ushort *)(param_1 + 0xd8) = *(ushort *)(param_1 + 0xd8) | *(ushort *)(lVar7 + 0x10);
    *(ushort *)(param_1 + 0xda) = *(ushort *)(param_1 + 0xda) | *(ushort *)(lVar7 + 0x12);
    *(ushort *)(param_1 + 0xdc) = *(ushort *)(param_1 + 0xdc) | *(ushort *)(lVar7 + 0x14);
    *(ushort *)(param_1 + 0xde) = *(ushort *)(param_1 + 0xde) | *(ushort *)(lVar7 + 0x16);
    iVar2 = *(int *)(param_1 + 0xec);
    *(ushort *)(param_1 + 0xe0) = *(ushort *)(param_1 + 0xe0) | *(ushort *)(lVar7 + 0x18);
    sVar4 = *(short *)(lVar7 + 0x1a);
    iVar1 = -iVar2;
    if (-1 < iVar2) {
      iVar1 = iVar2;
    }
    iVar2 = -(int)sVar4;
    if (-1 < sVar4) {
      iVar2 = (int)sVar4;
    }
    uVar8 = (ulong)uVar10;
    if (iVar1 < iVar2) {
      *(int *)(param_1 + 0xec) = (int)sVar4;
    }
    iVar2 = *(int *)(param_1 + 0xf0);
    sVar4 = *(short *)(lVar6 + uVar8 * 0x68 + 0x1c);
    iVar1 = -iVar2;
    if (-1 < iVar2) {
      iVar1 = iVar2;
    }
    iVar2 = -(int)sVar4;
    if (-1 < sVar4) {
      iVar2 = (int)sVar4;
    }
    if (iVar1 < iVar2) {
      *(int *)(param_1 + 0xf0) = (int)sVar4;
    }
    iVar2 = *(int *)(param_1 + 0xf4);
    sVar4 = *(short *)(lVar6 + uVar8 * 0x68 + 0x1e);
    iVar1 = -iVar2;
    if (-1 < iVar2) {
      iVar1 = iVar2;
    }
    iVar2 = -(int)sVar4;
    if (-1 < sVar4) {
      iVar2 = (int)sVar4;
    }
    if (iVar1 < iVar2) {
      *(int *)(param_1 + 0xf4) = (int)sVar4;
    }
    iVar2 = *(int *)(param_1 + 0xf8);
    sVar4 = *(short *)(lVar6 + uVar8 * 0x68 + 0x20);
    iVar1 = -iVar2;
    if (-1 < iVar2) {
      iVar1 = iVar2;
    }
    iVar2 = -(int)sVar4;
    if (-1 < sVar4) {
      iVar2 = (int)sVar4;
    }
    if (iVar1 < iVar2) {
      *(int *)(param_1 + 0xf8) = (int)sVar4;
    }
    fVar12 = *(float *)(lVar6 + uVar8 * 0x68 + 0x24);
    if (ABS(*(float *)(param_1 + 0xfc)) < ABS(fVar12)) {
      *(float *)(param_1 + 0xfc) = fVar12;
    }
    fVar12 = *(float *)(lVar6 + uVar8 * 0x68 + 0x28);
    if (ABS(*(float *)(param_1 + 0x100)) < ABS(fVar12)) {
      *(float *)(param_1 + 0x100) = fVar12;
    }
    fVar12 = *(float *)(lVar6 + uVar8 * 0x68 + 0x2c);
    if (ABS(*(float *)(param_1 + 0x104)) < ABS(fVar12)) {
      *(float *)(param_1 + 0x104) = fVar12;
    }
    fVar12 = *(float *)(lVar6 + uVar8 * 0x68 + 0x30);
    if (ABS(*(float *)(param_1 + 0x108)) < ABS(fVar12)) {
      *(float *)(param_1 + 0x108) = fVar12;
    }
    bVar3 = *(byte *)(lVar6 + uVar8 * 0x68 + 0x22);
    fVar12 = (float)NEON_ucvtf(*puVar11);
    if (fVar12 < (float)bVar3) {
      *puVar11 = (uint)bVar3;
    }
    bVar3 = *(byte *)(lVar6 + uVar8 * 0x68 + 0x23);
    fVar12 = (float)NEON_ucvtf(*(undefined4 *)(param_1 + 0xe8));
    if (fVar12 < (float)bVar3) {
      *(uint *)(param_1 + 0xe8) = (uint)bVar3;
    }
    uVar10 = uVar10 + 1;
    lVar6 = *(long *)puVar5;
  }
  lVar6 = Aska::Global::GetActivePad()();
  if (lVar6 != 0) {
    lVar7 = (long)*(int *)(lVar6 + 0x108);
    lVar9 = lVar6 + lVar7 * 0x28;
    *(ushort *)(param_1 + 0xd4) = *(ushort *)(param_1 + 0xd4) | *(ushort *)(lVar9 + 0xb8);
    *(ushort *)(param_1 + 0xd6) = *(ushort *)(param_1 + 0xd6) | *(ushort *)(lVar9 + 0xba);
    *(ushort *)(param_1 + 0xd8) = *(ushort *)(param_1 + 0xd8) | *(ushort *)(lVar9 + 0xbc);
    *(ushort *)(param_1 + 0xda) = *(ushort *)(param_1 + 0xda) | *(ushort *)(lVar9 + 0xbe);
    *(ushort *)(param_1 + 0xdc) = *(ushort *)(param_1 + 0xdc) | *(ushort *)(lVar9 + 0xc0);
    *(ushort *)(param_1 + 0xde) = *(ushort *)(param_1 + 0xde) | *(ushort *)(lVar9 + 0xc2);
    iVar2 = *(int *)(param_1 + 0xec);
    *(ushort *)(param_1 + 0xe0) = *(ushort *)(param_1 + 0xe0) | *(ushort *)(lVar9 + 0xc4);
    sVar4 = *(short *)(lVar9 + 0xc6);
    iVar1 = -iVar2;
    if (-1 < iVar2) {
      iVar1 = iVar2;
    }
    iVar2 = -(int)sVar4;
    if (-1 < sVar4) {
      iVar2 = (int)sVar4;
    }
    if (iVar1 < iVar2) {
      *(int *)(param_1 + 0xec) = (int)sVar4;
    }
    iVar2 = *(int *)(param_1 + 0xf0);
    sVar4 = *(short *)(lVar6 + lVar7 * 0x28 + 200);
    iVar1 = -iVar2;
    if (-1 < iVar2) {
      iVar1 = iVar2;
    }
    iVar2 = -(int)sVar4;
    if (-1 < sVar4) {
      iVar2 = (int)sVar4;
    }
    if (iVar1 < iVar2) {
      *(int *)(param_1 + 0xf0) = (int)sVar4;
    }
    iVar2 = *(int *)(param_1 + 0xf4);
    sVar4 = *(short *)(lVar6 + lVar7 * 0x28 + 0xca);
    iVar1 = -iVar2;
    if (-1 < iVar2) {
      iVar1 = iVar2;
    }
    iVar2 = -(int)sVar4;
    if (-1 < sVar4) {
      iVar2 = (int)sVar4;
    }
    if (iVar1 < iVar2) {
      *(int *)(param_1 + 0xf4) = (int)sVar4;
    }
    iVar2 = *(int *)(param_1 + 0xf8);
    sVar4 = *(short *)(lVar6 + lVar7 * 0x28 + 0xcc);
    iVar1 = -iVar2;
    if (-1 < iVar2) {
      iVar1 = iVar2;
    }
    iVar2 = -(int)sVar4;
    if (-1 < sVar4) {
      iVar2 = (int)sVar4;
    }
    if (iVar1 < iVar2) {
      *(int *)(param_1 + 0xf8) = (int)sVar4;
    }
    fVar12 = *(float *)(lVar6 + lVar7 * 0x28 + 0xd0);
    if (ABS(*(float *)(param_1 + 0xfc)) < ABS(fVar12)) {
      *(float *)(param_1 + 0xfc) = fVar12;
    }
    fVar12 = *(float *)(lVar6 + lVar7 * 0x28 + 0xd4);
    if (ABS(*(float *)(param_1 + 0x100)) < ABS(fVar12)) {
      *(float *)(param_1 + 0x100) = fVar12;
    }
    fVar12 = *(float *)(lVar6 + lVar7 * 0x28 + 0xd8);
    if (ABS(*(float *)(param_1 + 0x104)) < ABS(fVar12)) {
      *(float *)(param_1 + 0x104) = fVar12;
    }
    fVar12 = *(float *)(lVar6 + lVar7 * 0x28 + 0xdc);
    if (ABS(*(float *)(param_1 + 0x108)) < ABS(fVar12)) {
      *(float *)(param_1 + 0x108) = fVar12;
    }
    bVar3 = *(byte *)(lVar6 + lVar7 * 0x28 + 0xce);
    fVar12 = (float)NEON_ucvtf(*puVar11);
    if (fVar12 < (float)bVar3) {
      *puVar11 = (uint)bVar3;
    }
    bVar3 = *(byte *)(lVar6 + lVar7 * 0x28 + 0xcf);
    fVar12 = (float)NEON_ucvtf(*(undefined4 *)(param_1 + 0xe8));
    if (fVar12 < (float)bVar3) {
      *(uint *)(param_1 + 0xe8) = (uint)bVar3;
    }
  }
  return;
}

// ==== Framework::CPad::PrintS(int)
// vaddr 0x1e8d078 | ghidra 0x1f8d078 | size 4 | symbol _ZN9Framework4CPad6PrintSEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework4CPad6PrintSEi(void)

{
  return;
}

// ==== Framework::CPad::Mode() const
// vaddr 0x1e8d07c | ghidra 0x1f8d07c | size 8 | symbol _ZNK9Framework4CPad4ModeEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK9Framework4CPad4ModeEv(long param_1)

{
  return *(undefined4 *)(param_1 + 0xd0);
}

// ==== Framework::CPad::NowWithEveryMode() const
// vaddr 0x1e8d084 | ghidra 0x1f8d084 | size 76 | symbol _ZNK9Framework4CPad16NowWithEveryModeEv | lib libSOA-3.7.0.so | 2026-10-04
undefined2 _ZNK9Framework4CPad16NowWithEveryModeEv(long param_1)

{
  undefined *puVar1;
  long lVar2;
  
  puVar1 = PTR__ZN9Framework10TSingletonINS_4CPadEE11m_pInstanceE_02cbef78;
  if (*(int *)(param_1 + 0xd0) != 0) {
    return 0;
  }
  lVar2 = *(long *)PTR__ZN9Framework10TSingletonINS_4CPadEE11m_pInstanceE_02cbef78;
  if (lVar2 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029612b1/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar2 = *(long *)puVar1;
  }
  return *(undefined2 *)(lVar2 + 0xd4);
}

// ==== Framework::CPad::GetNow(int)
// vaddr 0x1e8d0d0 | ghidra 0x1f8d0d0 | size 184 | symbol _ZN9Framework4CPad6GetNowEi | lib libSOA-3.7.0.so | 2026-10-04
undefined2 _ZN9Framework4CPad6GetNowEi(uint param_1)

{
  undefined *puVar1;
  undefined2 *puVar2;
  long lVar3;
  
  puVar1 = PTR__ZN9Framework10TSingletonINS_4CPadEE11m_pInstanceE_02cbef78;
  lVar3 = *(long *)PTR__ZN9Framework10TSingletonINS_4CPadEE11m_pInstanceE_02cbef78;
  if (lVar3 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029612b1/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar3 = *(long *)puVar1;
  }
  if (param_1 == 0xffffffff) {
    puVar2 = (undefined2 *)(lVar3 + 0xd4);
  }
  else {
    if (*(long *)(lVar3 + 200) == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964cc8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Pad.cpp"*/,0x9f,&UNK_02964d32/*"m_pUnits is null."*/);
    }
    if (*(uint *)(lVar3 + 0xc0) <= param_1) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964cc8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Pad.cpp"*/,0xa0,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,param_1);
    }
    puVar2 = (undefined2 *)(*(long *)(lVar3 + 200) + (ulong)param_1 * 0x68 + 0xc);
  }
  return *puVar2;
}

// ==== Framework::CPad::SingleWithEveryMode() const
// vaddr 0x1e8d188 | ghidra 0x1f8d188 | size 76 | symbol _ZNK9Framework4CPad19SingleWithEveryModeEv | lib libSOA-3.7.0.so | 2026-10-04
undefined2 _ZNK9Framework4CPad19SingleWithEveryModeEv(long param_1)

{
  undefined *puVar1;
  long lVar2;
  
  puVar1 = PTR__ZN9Framework10TSingletonINS_4CPadEE11m_pInstanceE_02cbef78;
  if (*(int *)(param_1 + 0xd0) != 0) {
    return 0;
  }
  lVar2 = *(long *)PTR__ZN9Framework10TSingletonINS_4CPadEE11m_pInstanceE_02cbef78;
  if (lVar2 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029612b1/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar2 = *(long *)puVar1;
  }
  return *(undefined2 *)(lVar2 + 0xda);
}

// ==== Framework::CPad::GetSingle(int)
// vaddr 0x1e8d1d4 | ghidra 0x1f8d1d4 | size 184 | symbol _ZN9Framework4CPad9GetSingleEi | lib libSOA-3.7.0.so | 2026-10-04
undefined2 _ZN9Framework4CPad9GetSingleEi(uint param_1)

{
  undefined *puVar1;
  undefined2 *puVar2;
  long lVar3;
  
  puVar1 = PTR__ZN9Framework10TSingletonINS_4CPadEE11m_pInstanceE_02cbef78;
  lVar3 = *(long *)PTR__ZN9Framework10TSingletonINS_4CPadEE11m_pInstanceE_02cbef78;
  if (lVar3 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029612b1/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar3 = *(long *)puVar1;
  }
  if (param_1 == 0xffffffff) {
    puVar2 = (undefined2 *)(lVar3 + 0xda);
  }
  else {
    if (*(long *)(lVar3 + 200) == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964cc8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Pad.cpp"*/,0x9f,&UNK_02964d32/*"m_pUnits is null."*/);
    }
    if (*(uint *)(lVar3 + 0xc0) <= param_1) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964cc8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Pad.cpp"*/,0xa0,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,param_1);
    }
    puVar2 = (undefined2 *)(*(long *)(lVar3 + 200) + (ulong)param_1 * 0x68 + 0x12);
  }
  return *puVar2;
}

// ==== Framework::CPad::RepeatWithEveryMode() const
// vaddr 0x1e8d28c | ghidra 0x1f8d28c | size 76 | symbol _ZNK9Framework4CPad19RepeatWithEveryModeEv | lib libSOA-3.7.0.so | 2026-10-04
undefined2 _ZNK9Framework4CPad19RepeatWithEveryModeEv(long param_1)

{
  undefined *puVar1;
  long lVar2;
  
  puVar1 = PTR__ZN9Framework10TSingletonINS_4CPadEE11m_pInstanceE_02cbef78;
  if (*(int *)(param_1 + 0xd0) != 0) {
    return 0;
  }
  lVar2 = *(long *)PTR__ZN9Framework10TSingletonINS_4CPadEE11m_pInstanceE_02cbef78;
  if (lVar2 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029612b1/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar2 = *(long *)puVar1;
  }
  return *(undefined2 *)(lVar2 + 0xde);
}

// ==== Framework::CPad::GetRepeat(int)
// vaddr 0x1e8d2d8 | ghidra 0x1f8d2d8 | size 184 | symbol _ZN9Framework4CPad9GetRepeatEi | lib libSOA-3.7.0.so | 2026-10-04
undefined2 _ZN9Framework4CPad9GetRepeatEi(uint param_1)

{
  undefined *puVar1;
  undefined2 *puVar2;
  long lVar3;
  
  puVar1 = PTR__ZN9Framework10TSingletonINS_4CPadEE11m_pInstanceE_02cbef78;
  lVar3 = *(long *)PTR__ZN9Framework10TSingletonINS_4CPadEE11m_pInstanceE_02cbef78;
  if (lVar3 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029612b1/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar3 = *(long *)puVar1;
  }
  if (param_1 == 0xffffffff) {
    puVar2 = (undefined2 *)(lVar3 + 0xde);
  }
  else {
    if (*(long *)(lVar3 + 200) == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964cc8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Pad.cpp"*/,0x9f,&UNK_02964d32/*"m_pUnits is null."*/);
    }
    if (*(uint *)(lVar3 + 0xc0) <= param_1) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964cc8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Pad.cpp"*/,0xa0,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,param_1);
    }
    puVar2 = (undefined2 *)(*(long *)(lVar3 + 200) + (ulong)param_1 * 0x68 + 0x16);
  }
  return *puVar2;
}

// ==== Framework::CPad::CUnit::Clear()
// vaddr 0x1e8d390 | ghidra 0x1f8d390 | size 20 | symbol _ZN9Framework4CPad5CUnit5ClearEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework4CPad5CUnit5ClearEv(long param_1)

{
  *(undefined8 *)(param_1 + 0x2c) = 0;
  *(undefined8 *)(param_1 + 0x24) = 0;
  *(undefined8 *)(param_1 + 0x1c) = 0;
  *(undefined8 *)(param_1 + 0x14) = 0;
  *(undefined8 *)(param_1 + 0xc) = 0;
  return;
}

// ==== Framework::CPad::CUnit::CUnit()
// vaddr 0x1e8d3a4 | ghidra 0x1f8d3a4 | size 28 | symbol _ZN9Framework4CPad5CUnitC2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework4CPad5CUnitC1Ev(long *param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZTVN9Framework4CPad5CUnitE_02cbaa18;
  *(undefined4 *)(param_1 + 1) = 0xffffffff;
  *param_1 = (long)(puVar1 + 0x10);
  return;
}

// ==== Framework::CPad::CUnit::~CUnit()
// vaddr 0x1e8d3c0 | ghidra 0x1f8d3c0 | size 80 | symbol _ZN9Framework4CPad5CUnitD2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework4CPad5CUnitD1Ev(long *param_1)

{
  long *plVar1;
  
  *param_1 = (long)(PTR__ZTVN9Framework4CPad5CUnitE_02cbaa18 + 0x10);
  if ((int)param_1[1] != -1) {
    plVar1 = (long *)Aska::Global::GetPeripheral(int)();
    if (plVar1 != (long *)0x0) {
      (**(code **)(*plVar1 + 8))();
      Aska::Global::ReleasePeripheral(int)((int)param_1[1]);
    }
    *(undefined4 *)(param_1 + 1) = 0xffffffff;
  }
  return;
}

// ==== Framework::CPad::CUnit::Release()
// vaddr 0x1e8d410 | ghidra 0x1f8d410 | size 64 | symbol _ZN9Framework4CPad5CUnit7ReleaseEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework4CPad5CUnit7ReleaseEv(long param_1)

{
  long *plVar1;
  
  if (*(int *)(param_1 + 8) != -1) {
    plVar1 = (long *)Aska::Global::GetPeripheral(int)();
    if (plVar1 != (long *)0x0) {
      (**(code **)(*plVar1 + 8))();
      Aska::Global::ReleasePeripheral(int)(*(undefined4 *)(param_1 + 8));
    }
    *(undefined4 *)(param_1 + 8) = 0xffffffff;
  }
  return;
}

// ==== Framework::CPad::CUnit::rKeys()
// vaddr 0x1e8d858 | ghidra 0x1f8d858 | size 8 | symbol _ZN9Framework4CPad5CUnit5rKeysEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZN9Framework4CPad5CUnit5rKeysEv(long param_1)

{
  return param_1 + 0xc;
}

// ==== Framework::CPad::CUnit::Keys() const
// vaddr 0x1e8d860 | ghidra 0x1f8d860 | size 8 | symbol _ZNK9Framework4CPad5CUnit4KeysEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK9Framework4CPad5CUnit4KeysEv(long param_1)

{
  return param_1 + 0xc;
}

// ==== Framework::CPad::CUnit::LockAll()
// vaddr 0x1e8d868 | ghidra 0x1f8d868 | size 20 | symbol _ZN9Framework4CPad5CUnit7LockAllEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework4CPad5CUnit7LockAllEv(long param_1)

{
  *(undefined1 *)(param_1 + 0x60) = 1;
  *(undefined4 *)(param_1 + 0x5c) = 0x1010101;
  return;
}

// ==== Framework::CPad::CUnit::LockButtons()
// vaddr 0x1e8d87c | ghidra 0x1f8d87c | size 12 | symbol _ZN9Framework4CPad5CUnit11LockButtonsEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework4CPad5CUnit11LockButtonsEv(long param_1)

{
  *(undefined1 *)(param_1 + 0x5c) = 1;
  return;
}

// ==== Framework::CPad::CUnit::LockAnalogLeverL()
// vaddr 0x1e8d888 | ghidra 0x1f8d888 | size 12 | symbol _ZN9Framework4CPad5CUnit16LockAnalogLeverLEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework4CPad5CUnit16LockAnalogLeverLEv(long param_1)

{
  *(undefined1 *)(param_1 + 0x5d) = 1;
  return;
}

// ==== Framework::CPad::CUnit::LockAnalogLeverR()
// vaddr 0x1e8d894 | ghidra 0x1f8d894 | size 12 | symbol _ZN9Framework4CPad5CUnit16LockAnalogLeverREv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework4CPad5CUnit16LockAnalogLeverREv(long param_1)

{
  *(undefined1 *)(param_1 + 0x5e) = 1;
  return;
}

// ==== Framework::CPad::CUnit::LockAnalogTriggerL()
// vaddr 0x1e8d8a0 | ghidra 0x1f8d8a0 | size 12 | symbol _ZN9Framework4CPad5CUnit18LockAnalogTriggerLEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework4CPad5CUnit18LockAnalogTriggerLEv(long param_1)

{
  *(undefined1 *)(param_1 + 0x5f) = 1;
  return;
}

// ==== Framework::CPad::CUnit::LockAnalogTriggerR()
// vaddr 0x1e8d8ac | ghidra 0x1f8d8ac | size 12 | symbol _ZN9Framework4CPad5CUnit18LockAnalogTriggerREv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework4CPad5CUnit18LockAnalogTriggerREv(long param_1)

{
  *(undefined1 *)(param_1 + 0x60) = 1;
  return;
}

// ==== Framework::CPad::GetBefore(int)
// vaddr 0x1e8d8b8 | ghidra 0x1f8d8b8 | size 184 | symbol _ZN9Framework4CPad9GetBeforeEi | lib libSOA-3.7.0.so | 2026-10-04
undefined2 _ZN9Framework4CPad9GetBeforeEi(uint param_1)

{
  undefined *puVar1;
  undefined2 *puVar2;
  long lVar3;
  
  puVar1 = PTR__ZN9Framework10TSingletonINS_4CPadEE11m_pInstanceE_02cbef78;
  lVar3 = *(long *)PTR__ZN9Framework10TSingletonINS_4CPadEE11m_pInstanceE_02cbef78;
  if (lVar3 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029612b1/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar3 = *(long *)puVar1;
  }
  if (param_1 == 0xffffffff) {
    puVar2 = (undefined2 *)(lVar3 + 0xd6);
  }
  else {
    if (*(long *)(lVar3 + 200) == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964cc8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Pad.cpp"*/,0x9f,&UNK_02964d32/*"m_pUnits is null."*/);
    }
    if (*(uint *)(lVar3 + 0xc0) <= param_1) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964cc8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Pad.cpp"*/,0xa0,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,param_1);
    }
    puVar2 = (undefined2 *)(*(long *)(lVar3 + 200) + (ulong)param_1 * 0x68 + 0xe);
  }
  return *puVar2;
}

// ==== Framework::CPad::GetStock(int)
// vaddr 0x1e8d970 | ghidra 0x1f8d970 | size 184 | symbol _ZN9Framework4CPad8GetStockEi | lib libSOA-3.7.0.so | 2026-10-04
undefined2 _ZN9Framework4CPad8GetStockEi(uint param_1)

{
  undefined *puVar1;
  undefined2 *puVar2;
  long lVar3;
  
  puVar1 = PTR__ZN9Framework10TSingletonINS_4CPadEE11m_pInstanceE_02cbef78;
  lVar3 = *(long *)PTR__ZN9Framework10TSingletonINS_4CPadEE11m_pInstanceE_02cbef78;
  if (lVar3 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029612b1/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar3 = *(long *)puVar1;
  }
  if (param_1 == 0xffffffff) {
    puVar2 = (undefined2 *)(lVar3 + 0xd8);
  }
  else {
    if (*(long *)(lVar3 + 200) == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964cc8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Pad.cpp"*/,0x9f,&UNK_02964d32/*"m_pUnits is null."*/);
    }
    if (*(uint *)(lVar3 + 0xc0) <= param_1) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964cc8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Pad.cpp"*/,0xa0,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,param_1);
    }
    puVar2 = (undefined2 *)(*(long *)(lVar3 + 200) + (ulong)param_1 * 0x68 + 0x10);
  }
  return *puVar2;
}

// ==== Framework::CPad::GetRelease(int)
// vaddr 0x1e8da28 | ghidra 0x1f8da28 | size 184 | symbol _ZN9Framework4CPad10GetReleaseEi | lib libSOA-3.7.0.so | 2026-10-04
undefined2 _ZN9Framework4CPad10GetReleaseEi(uint param_1)

{
  undefined *puVar1;
  undefined2 *puVar2;
  long lVar3;
  
  puVar1 = PTR__ZN9Framework10TSingletonINS_4CPadEE11m_pInstanceE_02cbef78;
  lVar3 = *(long *)PTR__ZN9Framework10TSingletonINS_4CPadEE11m_pInstanceE_02cbef78;
  if (lVar3 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029612b1/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar3 = *(long *)puVar1;
  }
  if (param_1 == 0xffffffff) {
    puVar2 = (undefined2 *)(lVar3 + 0xdc);
  }
  else {
    if (*(long *)(lVar3 + 200) == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964cc8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Pad.cpp"*/,0x9f,&UNK_02964d32/*"m_pUnits is null."*/);
    }
    if (*(uint *)(lVar3 + 0xc0) <= param_1) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964cc8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Pad.cpp"*/,0xa0,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,param_1);
    }
    puVar2 = (undefined2 *)(*(long *)(lVar3 + 200) + (ulong)param_1 * 0x68 + 0x14);
  }
  return *puVar2;
}

// ==== Framework::CPad::GetRepeatEach(int)
// vaddr 0x1e8dae0 | ghidra 0x1f8dae0 | size 184 | symbol _ZN9Framework4CPad13GetRepeatEachEi | lib libSOA-3.7.0.so | 2026-10-04
undefined2 _ZN9Framework4CPad13GetRepeatEachEi(uint param_1)

{
  undefined *puVar1;
  undefined2 *puVar2;
  long lVar3;
  
  puVar1 = PTR__ZN9Framework10TSingletonINS_4CPadEE11m_pInstanceE_02cbef78;
  lVar3 = *(long *)PTR__ZN9Framework10TSingletonINS_4CPadEE11m_pInstanceE_02cbef78;
  if (lVar3 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029612b1/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar3 = *(long *)puVar1;
  }
  if (param_1 == 0xffffffff) {
    puVar2 = (undefined2 *)(lVar3 + 0xe0);
  }
  else {
    if (*(long *)(lVar3 + 200) == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964cc8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Pad.cpp"*/,0x9f,&UNK_02964d32/*"m_pUnits is null."*/);
    }
    if (*(uint *)(lVar3 + 0xc0) <= param_1) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964cc8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Pad.cpp"*/,0xa0,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,param_1);
    }
    puVar2 = (undefined2 *)(*(long *)(lVar3 + 200) + (ulong)param_1 * 0x68 + 0x18);
  }
  return *puVar2;
}

// ==== Framework::CPad::GetAnalogLT(int)
// vaddr 0x1e8db98 | ghidra 0x1f8db98 | size 180 | symbol _ZN9Framework4CPad11GetAnalogLTEi | lib libSOA-3.7.0.so | 2026-10-04
uint _ZN9Framework4CPad11GetAnalogLTEi(uint param_1)

{
  undefined *puVar1;
  uint uVar2;
  long lVar3;
  
  puVar1 = PTR__ZN9Framework10TSingletonINS_4CPadEE11m_pInstanceE_02cbef78;
  lVar3 = *(long *)PTR__ZN9Framework10TSingletonINS_4CPadEE11m_pInstanceE_02cbef78;
  if (lVar3 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029612b1/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar3 = *(long *)puVar1;
  }
  if (param_1 == 0xffffffff) {
    uVar2 = *(uint *)(lVar3 + 0xe4);
  }
  else {
    if (*(long *)(lVar3 + 200) == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964cc8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Pad.cpp"*/,0x9f,&UNK_02964d32/*"m_pUnits is null."*/);
    }
    if (*(uint *)(lVar3 + 0xc0) <= param_1) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964cc8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Pad.cpp"*/,0xa0,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,param_1);
    }
    uVar2 = (uint)*(byte *)(*(long *)(lVar3 + 200) + (ulong)param_1 * 0x68 + 0x22);
  }
  return uVar2;
}

// ==== Framework::CPad::GetAnalogRT(int)
// vaddr 0x1e8dc4c | ghidra 0x1f8dc4c | size 180 | symbol _ZN9Framework4CPad11GetAnalogRTEi | lib libSOA-3.7.0.so | 2026-10-04
uint _ZN9Framework4CPad11GetAnalogRTEi(uint param_1)

{
  undefined *puVar1;
  uint uVar2;
  long lVar3;
  
  puVar1 = PTR__ZN9Framework10TSingletonINS_4CPadEE11m_pInstanceE_02cbef78;
  lVar3 = *(long *)PTR__ZN9Framework10TSingletonINS_4CPadEE11m_pInstanceE_02cbef78;
  if (lVar3 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029612b1/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar3 = *(long *)puVar1;
  }
  if (param_1 == 0xffffffff) {
    uVar2 = *(uint *)(lVar3 + 0xe8);
  }
  else {
    if (*(long *)(lVar3 + 200) == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964cc8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Pad.cpp"*/,0x9f,&UNK_02964d32/*"m_pUnits is null."*/);
    }
    if (*(uint *)(lVar3 + 0xc0) <= param_1) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964cc8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Pad.cpp"*/,0xa0,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,param_1);
    }
    uVar2 = (uint)*(byte *)(*(long *)(lVar3 + 200) + (ulong)param_1 * 0x68 + 0x23);
  }
  return uVar2;
}

// ==== Framework::CPad::GetAnalogLTF(int)
// vaddr 0x1e8dd00 | ghidra 0x1f8dd00 | size 196 | symbol _ZN9Framework4CPad12GetAnalogLTFEi | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float _ZN9Framework4CPad12GetAnalogLTFEi(uint param_1)

{
  undefined *puVar1;
  uint uVar2;
  long lVar3;
  
  puVar1 = PTR__ZN9Framework10TSingletonINS_4CPadEE11m_pInstanceE_02cbef78;
  lVar3 = *(long *)PTR__ZN9Framework10TSingletonINS_4CPadEE11m_pInstanceE_02cbef78;
  if (lVar3 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029612b1/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar3 = *(long *)puVar1;
  }
  if (param_1 == 0xffffffff) {
    uVar2 = *(uint *)(lVar3 + 0xe4);
  }
  else {
    if (*(long *)(lVar3 + 200) == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964cc8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Pad.cpp"*/,0x9f,&UNK_02964d32/*"m_pUnits is null."*/);
    }
    if (*(uint *)(lVar3 + 0xc0) <= param_1) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964cc8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Pad.cpp"*/,0xa0,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,param_1);
    }
    uVar2 = (uint)*(byte *)(*(long *)(lVar3 + 200) + (ulong)param_1 * 0x68 + 0x22);
  }
  return (float)uVar2 / _UNK_028014f8;
}

// ==== Framework::CPad::GetAnalogRTF(int)
// vaddr 0x1e8ddc4 | ghidra 0x1f8ddc4 | size 196 | symbol _ZN9Framework4CPad12GetAnalogRTFEi | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float _ZN9Framework4CPad12GetAnalogRTFEi(uint param_1)

{
  undefined *puVar1;
  uint uVar2;
  long lVar3;
  
  puVar1 = PTR__ZN9Framework10TSingletonINS_4CPadEE11m_pInstanceE_02cbef78;
  lVar3 = *(long *)PTR__ZN9Framework10TSingletonINS_4CPadEE11m_pInstanceE_02cbef78;
  if (lVar3 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029612b1/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar3 = *(long *)puVar1;
  }
  if (param_1 == 0xffffffff) {
    uVar2 = *(uint *)(lVar3 + 0xe8);
  }
  else {
    if (*(long *)(lVar3 + 200) == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964cc8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Pad.cpp"*/,0x9f,&UNK_02964d32/*"m_pUnits is null."*/);
    }
    if (*(uint *)(lVar3 + 0xc0) <= param_1) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964cc8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Pad.cpp"*/,0xa0,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,param_1);
    }
    uVar2 = (uint)*(byte *)(*(long *)(lVar3 + 200) + (ulong)param_1 * 0x68 + 0x23);
  }
  return (float)uVar2 / _UNK_028014f8;
}

// ==== Framework::CPad::GetAnalogLX(int)
// vaddr 0x1e8de88 | ghidra 0x1f8de88 | size 180 | symbol _ZN9Framework4CPad11GetAnalogLXEi | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZN9Framework4CPad11GetAnalogLXEi(uint param_1)

{
  undefined *puVar1;
  ulong uVar2;
  long lVar3;
  
  puVar1 = PTR__ZN9Framework10TSingletonINS_4CPadEE11m_pInstanceE_02cbef78;
  lVar3 = *(long *)PTR__ZN9Framework10TSingletonINS_4CPadEE11m_pInstanceE_02cbef78;
  if (lVar3 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029612b1/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar3 = *(long *)puVar1;
  }
  if (param_1 == 0xffffffff) {
    uVar2 = (ulong)*(uint *)(lVar3 + 0xec);
  }
  else {
    if (*(long *)(lVar3 + 200) == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964cc8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Pad.cpp"*/,0x9f,&UNK_02964d32/*"m_pUnits is null."*/);
    }
    if (*(uint *)(lVar3 + 0xc0) <= param_1) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964cc8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Pad.cpp"*/,0xa0,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,param_1);
    }
    uVar2 = (ulong)*(short *)(*(long *)(lVar3 + 200) + (ulong)param_1 * 0x68 + 0x1a);
  }
  return uVar2;
}

// ==== Framework::CPad::GetAnalogLY(int)
// vaddr 0x1e8df3c | ghidra 0x1f8df3c | size 180 | symbol _ZN9Framework4CPad11GetAnalogLYEi | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZN9Framework4CPad11GetAnalogLYEi(uint param_1)

{
  undefined *puVar1;
  ulong uVar2;
  long lVar3;
  
  puVar1 = PTR__ZN9Framework10TSingletonINS_4CPadEE11m_pInstanceE_02cbef78;
  lVar3 = *(long *)PTR__ZN9Framework10TSingletonINS_4CPadEE11m_pInstanceE_02cbef78;
  if (lVar3 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029612b1/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar3 = *(long *)puVar1;
  }
  if (param_1 == 0xffffffff) {
    uVar2 = (ulong)*(uint *)(lVar3 + 0xf0);
  }
  else {
    if (*(long *)(lVar3 + 200) == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964cc8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Pad.cpp"*/,0x9f,&UNK_02964d32/*"m_pUnits is null."*/);
    }
    if (*(uint *)(lVar3 + 0xc0) <= param_1) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964cc8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Pad.cpp"*/,0xa0,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,param_1);
    }
    uVar2 = (ulong)*(short *)(*(long *)(lVar3 + 200) + (ulong)param_1 * 0x68 + 0x1c);
  }
  return uVar2;
}

// ==== Framework::CPad::GetAnalogRX(int)
// vaddr 0x1e8dff0 | ghidra 0x1f8dff0 | size 180 | symbol _ZN9Framework4CPad11GetAnalogRXEi | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZN9Framework4CPad11GetAnalogRXEi(uint param_1)

{
  undefined *puVar1;
  ulong uVar2;
  long lVar3;
  
  puVar1 = PTR__ZN9Framework10TSingletonINS_4CPadEE11m_pInstanceE_02cbef78;
  lVar3 = *(long *)PTR__ZN9Framework10TSingletonINS_4CPadEE11m_pInstanceE_02cbef78;
  if (lVar3 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029612b1/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar3 = *(long *)puVar1;
  }
  if (param_1 == 0xffffffff) {
    uVar2 = (ulong)*(uint *)(lVar3 + 0xf4);
  }
  else {
    if (*(long *)(lVar3 + 200) == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964cc8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Pad.cpp"*/,0x9f,&UNK_02964d32/*"m_pUnits is null."*/);
    }
    if (*(uint *)(lVar3 + 0xc0) <= param_1) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964cc8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Pad.cpp"*/,0xa0,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,param_1);
    }
    uVar2 = (ulong)*(short *)(*(long *)(lVar3 + 200) + (ulong)param_1 * 0x68 + 0x1e);
  }
  return uVar2;
}

// ==== Framework::CPad::GetAnalogRY(int)
// vaddr 0x1e8f0a4 | ghidra 0x1f8f0a4 | size 180 | symbol _ZN9Framework4CPad11GetAnalogRYEi | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZN9Framework4CPad11GetAnalogRYEi(uint param_1)

{
  undefined *puVar1;
  ulong uVar2;
  long lVar3;
  
  puVar1 = PTR__ZN9Framework10TSingletonINS_4CPadEE11m_pInstanceE_02cbef78;
  lVar3 = *(long *)PTR__ZN9Framework10TSingletonINS_4CPadEE11m_pInstanceE_02cbef78;
  if (lVar3 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029612b1/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar3 = *(long *)puVar1;
  }
  if (param_1 == 0xffffffff) {
    uVar2 = (ulong)*(uint *)(lVar3 + 0xf8);
  }
  else {
    if (*(long *)(lVar3 + 200) == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964cc8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Pad.cpp"*/,0x9f,&UNK_02964d32/*"m_pUnits is null."*/);
    }
    if (*(uint *)(lVar3 + 0xc0) <= param_1) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964cc8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Pad.cpp"*/,0xa0,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,param_1);
    }
    uVar2 = (ulong)*(short *)(*(long *)(lVar3 + 200) + (ulong)param_1 * 0x68 + 0x20);
  }
  return uVar2;
}

// ==== Framework::CPad::GetAnalogLXF(int)
// vaddr 0x1e8f158 | ghidra 0x1f8f158 | size 184 | symbol _ZN9Framework4CPad12GetAnalogLXFEi | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZN9Framework4CPad12GetAnalogLXFEi(uint param_1)

{
  undefined *puVar1;
  undefined4 *puVar2;
  long lVar3;
  
  puVar1 = PTR__ZN9Framework10TSingletonINS_4CPadEE11m_pInstanceE_02cbef78;
  lVar3 = *(long *)PTR__ZN9Framework10TSingletonINS_4CPadEE11m_pInstanceE_02cbef78;
  if (lVar3 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029612b1/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar3 = *(long *)puVar1;
  }
  if (param_1 == 0xffffffff) {
    puVar2 = (undefined4 *)(lVar3 + 0xfc);
  }
  else {
    if (*(long *)(lVar3 + 200) == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964cc8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Pad.cpp"*/,0x9f,&UNK_02964d32/*"m_pUnits is null."*/);
    }
    if (*(uint *)(lVar3 + 0xc0) <= param_1) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964cc8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Pad.cpp"*/,0xa0,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,param_1);
    }
    puVar2 = (undefined4 *)(*(long *)(lVar3 + 200) + (ulong)param_1 * 0x68 + 0x24);
  }
  return *puVar2;
}

// ==== Framework::CPad::GetAnalogLYF(int)
// vaddr 0x1e8f210 | ghidra 0x1f8f210 | size 184 | symbol _ZN9Framework4CPad12GetAnalogLYFEi | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZN9Framework4CPad12GetAnalogLYFEi(uint param_1)

{
  undefined *puVar1;
  undefined4 *puVar2;
  long lVar3;
  
  puVar1 = PTR__ZN9Framework10TSingletonINS_4CPadEE11m_pInstanceE_02cbef78;
  lVar3 = *(long *)PTR__ZN9Framework10TSingletonINS_4CPadEE11m_pInstanceE_02cbef78;
  if (lVar3 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029612b1/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar3 = *(long *)puVar1;
  }
  if (param_1 == 0xffffffff) {
    puVar2 = (undefined4 *)(lVar3 + 0x100);
  }
  else {
    if (*(long *)(lVar3 + 200) == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964cc8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Pad.cpp"*/,0x9f,&UNK_02964d32/*"m_pUnits is null."*/);
    }
    if (*(uint *)(lVar3 + 0xc0) <= param_1) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964cc8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Pad.cpp"*/,0xa0,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,param_1);
    }
    puVar2 = (undefined4 *)(*(long *)(lVar3 + 200) + (ulong)param_1 * 0x68 + 0x28);
  }
  return *puVar2;
}

// ==== Framework::CPad::GetAnalogRXF(int)
// vaddr 0x1e8f2c8 | ghidra 0x1f8f2c8 | size 184 | symbol _ZN9Framework4CPad12GetAnalogRXFEi | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZN9Framework4CPad12GetAnalogRXFEi(uint param_1)

{
  undefined *puVar1;
  undefined4 *puVar2;
  long lVar3;
  
  puVar1 = PTR__ZN9Framework10TSingletonINS_4CPadEE11m_pInstanceE_02cbef78;
  lVar3 = *(long *)PTR__ZN9Framework10TSingletonINS_4CPadEE11m_pInstanceE_02cbef78;
  if (lVar3 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029612b1/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar3 = *(long *)puVar1;
  }
  if (param_1 == 0xffffffff) {
    puVar2 = (undefined4 *)(lVar3 + 0x104);
  }
  else {
    if (*(long *)(lVar3 + 200) == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964cc8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Pad.cpp"*/,0x9f,&UNK_02964d32/*"m_pUnits is null."*/);
    }
    if (*(uint *)(lVar3 + 0xc0) <= param_1) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964cc8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Pad.cpp"*/,0xa0,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,param_1);
    }
    puVar2 = (undefined4 *)(*(long *)(lVar3 + 200) + (ulong)param_1 * 0x68 + 0x2c);
  }
  return *puVar2;
}

// ==== Framework::CPad::GetAnalogRYF(int)
// vaddr 0x1e8f380 | ghidra 0x1f8f380 | size 184 | symbol _ZN9Framework4CPad12GetAnalogRYFEi | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZN9Framework4CPad12GetAnalogRYFEi(uint param_1)

{
  undefined *puVar1;
  undefined4 *puVar2;
  long lVar3;
  
  puVar1 = PTR__ZN9Framework10TSingletonINS_4CPadEE11m_pInstanceE_02cbef78;
  lVar3 = *(long *)PTR__ZN9Framework10TSingletonINS_4CPadEE11m_pInstanceE_02cbef78;
  if (lVar3 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029612b1/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar3 = *(long *)puVar1;
  }
  if (param_1 == 0xffffffff) {
    puVar2 = (undefined4 *)(lVar3 + 0x108);
  }
  else {
    if (*(long *)(lVar3 + 200) == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964cc8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Pad.cpp"*/,0x9f,&UNK_02964d32/*"m_pUnits is null."*/);
    }
    if (*(uint *)(lVar3 + 0xc0) <= param_1) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964cc8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Pad.cpp"*/,0xa0,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,param_1);
    }
    puVar2 = (undefined4 *)(*(long *)(lVar3 + 200) + (ulong)param_1 * 0x68 + 0x30);
  }
  return *puVar2;
}

// ==== Framework::CPad::CUnit::GetNow() const
// vaddr 0x1e8f438 | ghidra 0x1f8f438 | size 24 | symbol _ZNK9Framework4CPad5CUnit6GetNowEv | lib libSOA-3.7.0.so | 2026-10-04
undefined2 _ZNK9Framework4CPad5CUnit6GetNowEv(long param_1)

{
  if (*(char *)(param_1 + 0x5c) != '\0') {
    return 0;
  }
  return *(undefined2 *)(param_1 + 0xc);
}

// ==== Framework::CPad::CUnit::GetBefore() const
// vaddr 0x1e8f450 | ghidra 0x1f8f450 | size 24 | symbol _ZNK9Framework4CPad5CUnit9GetBeforeEv | lib libSOA-3.7.0.so | 2026-10-04
undefined2 _ZNK9Framework4CPad5CUnit9GetBeforeEv(long param_1)

{
  if (*(char *)(param_1 + 0x5c) != '\0') {
    return 0;
  }
  return *(undefined2 *)(param_1 + 0xe);
}

// ==== Framework::CPad::CUnit::GetStock() const
// vaddr 0x1e8f468 | ghidra 0x1f8f468 | size 24 | symbol _ZNK9Framework4CPad5CUnit8GetStockEv | lib libSOA-3.7.0.so | 2026-10-04
undefined2 _ZNK9Framework4CPad5CUnit8GetStockEv(long param_1)

{
  if (*(char *)(param_1 + 0x5c) != '\0') {
    return 0;
  }
  return *(undefined2 *)(param_1 + 0x10);
}

// ==== Framework::CPad::CUnit::GetSingle() const
// vaddr 0x1e8f480 | ghidra 0x1f8f480 | size 24 | symbol _ZNK9Framework4CPad5CUnit9GetSingleEv | lib libSOA-3.7.0.so | 2026-10-04
undefined2 _ZNK9Framework4CPad5CUnit9GetSingleEv(long param_1)

{
  if (*(char *)(param_1 + 0x5c) != '\0') {
    return 0;
  }
  return *(undefined2 *)(param_1 + 0x12);
}

// ==== Framework::CPad::CUnit::GetRelease() const
// vaddr 0x1e8f498 | ghidra 0x1f8f498 | size 24 | symbol _ZNK9Framework4CPad5CUnit10GetReleaseEv | lib libSOA-3.7.0.so | 2026-10-04
undefined2 _ZNK9Framework4CPad5CUnit10GetReleaseEv(long param_1)

{
  if (*(char *)(param_1 + 0x5c) != '\0') {
    return 0;
  }
  return *(undefined2 *)(param_1 + 0x14);
}

// ==== Framework::CPad::CUnit::GetRepeat() const
// vaddr 0x1e8f4b0 | ghidra 0x1f8f4b0 | size 24 | symbol _ZNK9Framework4CPad5CUnit9GetRepeatEv | lib libSOA-3.7.0.so | 2026-10-04
undefined2 _ZNK9Framework4CPad5CUnit9GetRepeatEv(long param_1)

{
  if (*(char *)(param_1 + 0x5c) != '\0') {
    return 0;
  }
  return *(undefined2 *)(param_1 + 0x16);
}

// ==== Framework::CPad::CUnit::GetRepeatEach() const
// vaddr 0x1e8f4c8 | ghidra 0x1f8f4c8 | size 24 | symbol _ZNK9Framework4CPad5CUnit13GetRepeatEachEv | lib libSOA-3.7.0.so | 2026-10-04
undefined2 _ZNK9Framework4CPad5CUnit13GetRepeatEachEv(long param_1)

{
  if (*(char *)(param_1 + 0x5c) != '\0') {
    return 0;
  }
  return *(undefined2 *)(param_1 + 0x18);
}

// ==== Framework::CPad::CUnit::GetAnalogLX() const
// vaddr 0x1e8f4e0 | ghidra 0x1f8f4e0 | size 24 | symbol _ZNK9Framework4CPad5CUnit11GetAnalogLXEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK9Framework4CPad5CUnit11GetAnalogLXEv(long param_1)

{
  if (*(char *)(param_1 + 0x5d) != '\0') {
    return 0;
  }
  return (long)*(short *)(param_1 + 0x1a);
}

// ==== Framework::CPad::CUnit::GetAnalogLY() const
// vaddr 0x1e8f4f8 | ghidra 0x1f8f4f8 | size 24 | symbol _ZNK9Framework4CPad5CUnit11GetAnalogLYEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK9Framework4CPad5CUnit11GetAnalogLYEv(long param_1)

{
  if (*(char *)(param_1 + 0x5d) != '\0') {
    return 0;
  }
  return (long)*(short *)(param_1 + 0x1c);
}

// ==== Framework::CPad::CUnit::GetAnalogRX() const
// vaddr 0x1e8f510 | ghidra 0x1f8f510 | size 24 | symbol _ZNK9Framework4CPad5CUnit11GetAnalogRXEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK9Framework4CPad5CUnit11GetAnalogRXEv(long param_1)

{
  if (*(char *)(param_1 + 0x5e) != '\0') {
    return 0;
  }
  return (long)*(short *)(param_1 + 0x1e);
}

// ==== Framework::CPad::CUnit::GetAnalogRY() const
// vaddr 0x1e8f528 | ghidra 0x1f8f528 | size 24 | symbol _ZNK9Framework4CPad5CUnit11GetAnalogRYEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK9Framework4CPad5CUnit11GetAnalogRYEv(long param_1)

{
  if (*(char *)(param_1 + 0x5e) != '\0') {
    return 0;
  }
  return (long)*(short *)(param_1 + 0x20);
}

// ==== Framework::CPad::CUnit::GetAnalogLT() const
// vaddr 0x1e8f540 | ghidra 0x1f8f540 | size 24 | symbol _ZNK9Framework4CPad5CUnit11GetAnalogLTEv | lib libSOA-3.7.0.so | 2026-10-04
undefined1 _ZNK9Framework4CPad5CUnit11GetAnalogLTEv(long param_1)

{
  if (*(char *)(param_1 + 0x5f) != '\0') {
    return 0;
  }
  return *(undefined1 *)(param_1 + 0x22);
}

// ==== Framework::CPad::CUnit::GetAnalogRT() const
// vaddr 0x1e8f558 | ghidra 0x1f8f558 | size 24 | symbol _ZNK9Framework4CPad5CUnit11GetAnalogRTEv | lib libSOA-3.7.0.so | 2026-10-04
undefined1 _ZNK9Framework4CPad5CUnit11GetAnalogRTEv(long param_1)

{
  if (*(char *)(param_1 + 0x60) != '\0') {
    return 0;
  }
  return *(undefined1 *)(param_1 + 0x23);
}

// ==== Framework::CPad::CUnit::GetAnalogLTF() const
// vaddr 0x1e8f570 | ghidra 0x1f8f570 | size 40 | symbol _ZNK9Framework4CPad5CUnit12GetAnalogLTFEv | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float _ZNK9Framework4CPad5CUnit12GetAnalogLTFEv(long param_1)

{
  float fVar1;
  
  if (*(char *)(param_1 + 0x5f) != '\0') {
    return 0.0;
  }
  fVar1 = (float)NEON_ucvtf((uint)*(byte *)(param_1 + 0x22));
  return fVar1 / _UNK_028014f8;
}

// ==== Framework::CPad::CUnit::GetAnalogRTF() const
// vaddr 0x1e8f598 | ghidra 0x1f8f598 | size 40 | symbol _ZNK9Framework4CPad5CUnit12GetAnalogRTFEv | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float _ZNK9Framework4CPad5CUnit12GetAnalogRTFEv(long param_1)

{
  float fVar1;
  
  if (*(char *)(param_1 + 0x60) != '\0') {
    return 0.0;
  }
  fVar1 = (float)NEON_ucvtf((uint)*(byte *)(param_1 + 0x23));
  return fVar1 / _UNK_028014f8;
}

// ==== Framework::CPad::CUnit::GetAnalogLXF() const
// vaddr 0x1e8f5c0 | ghidra 0x1f8f5c0 | size 24 | symbol _ZNK9Framework4CPad5CUnit12GetAnalogLXFEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK9Framework4CPad5CUnit12GetAnalogLXFEv(long param_1)

{
  if (*(char *)(param_1 + 0x5d) != '\0') {
    return 0;
  }
  return *(undefined4 *)(param_1 + 0x24);
}

// ==== Framework::CPad::CUnit::GetAnalogLYF() const
// vaddr 0x1e8f5d8 | ghidra 0x1f8f5d8 | size 24 | symbol _ZNK9Framework4CPad5CUnit12GetAnalogLYFEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK9Framework4CPad5CUnit12GetAnalogLYFEv(long param_1)

{
  if (*(char *)(param_1 + 0x5d) != '\0') {
    return 0;
  }
  return *(undefined4 *)(param_1 + 0x28);
}

// ==== Framework::CPad::CUnit::GetAnalogRXF() const
// vaddr 0x1e8f5f0 | ghidra 0x1f8f5f0 | size 24 | symbol _ZNK9Framework4CPad5CUnit12GetAnalogRXFEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK9Framework4CPad5CUnit12GetAnalogRXFEv(long param_1)

{
  if (*(char *)(param_1 + 0x5e) != '\0') {
    return 0;
  }
  return *(undefined4 *)(param_1 + 0x2c);
}

// ==== Framework::CPad::CUnit::GetAnalogRYF() const
// vaddr 0x1e8f608 | ghidra 0x1f8f608 | size 24 | symbol _ZNK9Framework4CPad5CUnit12GetAnalogRYFEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK9Framework4CPad5CUnit12GetAnalogRYFEv(long param_1)

{
  if (*(char *)(param_1 + 0x5e) != '\0') {
    return 0;
  }
  return *(undefined4 *)(param_1 + 0x30);
}

// ==== Framework::CPad::CUnit::IsNow(unsigned short) const
// vaddr 0x1e8f620 | ghidra 0x1f8f620 | size 36 | symbol _ZNK9Framework4CPad5CUnit5IsNowEt | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK9Framework4CPad5CUnit5IsNowEt(long param_1,ushort param_2)

{
  if (*(char *)(param_1 + 0x5c) != '\0') {
    return false;
  }
  return (*(ushort *)(param_1 + 0xc) & param_2) != 0;
}

// ==== Framework::CPad::CUnit::IsBefore(unsigned short) const
// vaddr 0x1e8f644 | ghidra 0x1f8f644 | size 36 | symbol _ZNK9Framework4CPad5CUnit8IsBeforeEt | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK9Framework4CPad5CUnit8IsBeforeEt(long param_1,ushort param_2)

{
  if (*(char *)(param_1 + 0x5c) != '\0') {
    return false;
  }
  return (*(ushort *)(param_1 + 0xe) & param_2) != 0;
}

// ==== Framework::CPad::CUnit::IsSingle(unsigned short) const
// vaddr 0x1e8f668 | ghidra 0x1f8f668 | size 36 | symbol _ZNK9Framework4CPad5CUnit8IsSingleEt | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK9Framework4CPad5CUnit8IsSingleEt(long param_1,ushort param_2)

{
  if (*(char *)(param_1 + 0x5c) != '\0') {
    return false;
  }
  return (*(ushort *)(param_1 + 0x12) & param_2) != 0;
}

// ==== Framework::CPad::CUnit::IsRelease(unsigned short) const
// vaddr 0x1e8f68c | ghidra 0x1f8f68c | size 36 | symbol _ZNK9Framework4CPad5CUnit9IsReleaseEt | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK9Framework4CPad5CUnit9IsReleaseEt(long param_1,ushort param_2)

{
  if (*(char *)(param_1 + 0x5c) != '\0') {
    return false;
  }
  return (*(ushort *)(param_1 + 0x14) & param_2) != 0;
}

// ==== Framework::CPad::CUnit::IsRepeat(unsigned short) const
// vaddr 0x1e8f6b0 | ghidra 0x1f8f6b0 | size 36 | symbol _ZNK9Framework4CPad5CUnit8IsRepeatEt | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK9Framework4CPad5CUnit8IsRepeatEt(long param_1,ushort param_2)

{
  if (*(char *)(param_1 + 0x5c) != '\0') {
    return false;
  }
  return (*(ushort *)(param_1 + 0x16) & param_2) != 0;
}

// ==== Framework::CPad::CUnit::IsRepeatEach(unsigned short) const
// vaddr 0x1e8f6d4 | ghidra 0x1f8f6d4 | size 36 | symbol _ZNK9Framework4CPad5CUnit12IsRepeatEachEt | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK9Framework4CPad5CUnit12IsRepeatEachEt(long param_1,ushort param_2)

{
  if (*(char *)(param_1 + 0x5c) != '\0') {
    return false;
  }
  return (*(ushort *)(param_1 + 0x18) & param_2) != 0;
}

// ==== Framework::CPadReader::~CPadReader()
// vaddr 0x1e8f6f8 | ghidra 0x1f8f6f8 | size 72 | symbol _ZN9Framework10CPadReaderD2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework10CPadReaderD2Ev(undefined8 param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZN9Framework10TSingletonINS_10CPadReaderEE11m_pInstanceE_02cc3868;
  if (*(long *)PTR__ZN9Framework10TSingletonINS_10CPadReaderEE11m_pInstanceE_02cc3868 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029612b1/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TSingleton.h"*/,0x1d,&UNK_027daf21/*"m_pInstance is null."*/);
  }
  *(undefined8 *)puVar1 = 0;
  (*(code *)PTR__ZN4Aska4TaskD1Ev_02c92d10)(param_1);
  return;
}

// ==== Framework::CPadReader::~CPadReader()
// vaddr 0x1e8f740 | ghidra 0x1f8f740 | size 80 | symbol _ZN9Framework10CPadReaderD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework10CPadReaderD0Ev(undefined8 param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZN9Framework10TSingletonINS_10CPadReaderEE11m_pInstanceE_02cc3868;
  if (*(long *)PTR__ZN9Framework10TSingletonINS_10CPadReaderEE11m_pInstanceE_02cc3868 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029612b1/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TSingleton.h"*/,0x1d,&UNK_027daf21/*"m_pInstance is null."*/);
  }
  *(undefined8 *)puVar1 = 0;
  Aska::Task::~Task()(param_1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Framework::CPadReader::GetClassID(int) const
// vaddr 0x1e8f790 | ghidra 0x1f8f790 | size 32 | symbol _ZNK9Framework10CPadReader10GetClassIDEi | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK9Framework10CPadReader10GetClassIDEi(undefined8 param_1,int param_2)

{
  undefined8 uVar1;
  
  uVar1 = 0xf002000c;
  if (param_2 != 0) {
    uVar1 = 0xf000f001f002;
  }
  return uVar1;
}

// ==== Framework::CPadReader::GetDefaultLevel() const
// vaddr 0x1e8f7b0 | ghidra 0x1f8f7b0 | size 8 | symbol _ZNK9Framework10CPadReader15GetDefaultLevelEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK9Framework10CPadReader15GetDefaultLevelEv(void)

{
  return 4;
}

// ==== Framework::CPadReader::Run(int)
// vaddr 0x1e8f7b8 | ghidra 0x1f8f7b8 | size 388 | symbol _ZN9Framework10CPadReader3RunEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework10CPadReader3RunEi(void)

{
  undefined *puVar1;
  ulong uVar2;
  long lVar3;
  long lVar4;
  uint uVar5;
  long lVar6;
  undefined8 uVar7;
  
  puVar1 = PTR__ZN9Framework10TSingletonINS_4CPadEE11m_pInstanceE_02cbef78;
  if (*(long *)PTR__ZN9Framework10TSingletonINS_4CPadEE11m_pInstanceE_02cbef78 != 0) {
    lVar3 = *(long *)PTR__ZN9Framework10TSingletonINS_4CPadEE11m_pInstanceE_02cbef78 + 0x10;
    uVar2 = Framework::CMutex::IsInitialized() const(lVar3);
    if ((uVar2 & 1) == 0) {
      Framework::CMutex::Initialize()(lVar3);
    }
    Framework::CMutex::Lock()(lVar3);
    Framework::CMutex::Unlock()(lVar3);
    uVar5 = 0;
    lVar3 = *(long *)puVar1;
    while( true ) {
      if (lVar3 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029612b1/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
        lVar3 = *(long *)puVar1;
      }
      if (*(uint *)(lVar3 + 0xc0) <= uVar5) break;
      lVar3 = Aska::Global::GetPeripheral(int)(uVar5);
      if (lVar3 != 0) {
        Aska::Pad::Flip()(lVar3);
        lVar6 = *(long *)puVar1;
        if (lVar6 == 0) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029612b1/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
          lVar6 = *(long *)puVar1;
          lVar4 = *(long *)(lVar6 + 200);
        }
        else {
          lVar4 = *(long *)(lVar6 + 200);
        }
        if (lVar4 == 0) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964cc8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Pad.cpp"*/,0x98,&UNK_02964d32/*"m_pUnits is null."*/);
        }
        if (*(uint *)(lVar6 + 0xc0) <= uVar5) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964cc8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Pad.cpp"*/,0x99,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,uVar5);
        }
        lVar3 = lVar3 + (long)*(int *)(lVar3 + 0x108) * 0x28;
        lVar6 = *(long *)(lVar6 + 200) + (ulong)uVar5 * 0x68;
        *(undefined8 *)(lVar6 + 0x54) = *(undefined8 *)(lVar3 + 0xd8);
        uVar7 = *(undefined8 *)(lVar3 + 200);
        *(undefined8 *)(lVar6 + 0x4c) = *(undefined8 *)(lVar3 + 0xd0);
        *(undefined8 *)(lVar6 + 0x44) = uVar7;
        uVar7 = *(undefined8 *)(lVar3 + 0xb8);
        *(undefined8 *)(lVar6 + 0x3c) = *(undefined8 *)(lVar3 + 0xc0);
        *(undefined8 *)(lVar6 + 0x34) = uVar7;
      }
      uVar5 = uVar5 + 1;
      lVar3 = *(long *)puVar1;
    }
  }
  return;
}

// ==== Framework::CTouchPanel::CTouchPanel()
// vaddr 0x1e9f178 | ghidra 0x1f9f178 | size 220 | symbol _ZN9Framework11CTouchPanelC1Ev | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN9Framework11CTouchPanelC2Ev(long *param_1)

{
  long lVar1;
  undefined *puVar2;
  long lVar3;
  
  puVar2 = PTR__ZN9Framework10TSingletonINS_11CTouchPanelEE11m_pInstanceE_02cbd318;
  if (*(long *)PTR__ZN9Framework10TSingletonINS_11CTouchPanelEE11m_pInstanceE_02cbd318 != 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029612b1/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TSingleton.h"*/,0x15,&UNK_027daee5/*"m_pInstance isn't null.(%08x)"*/);
  }
  *(long **)puVar2 = param_1;
  lVar1 = _UNK_02966798;
  lVar3 = _UNK_02966790;
  *param_1 = (long)(PTR__ZTVN9Framework11CTouchPanelE_02cbf6f0 + 0x10);
  *(undefined1 *)(param_1 + 4) = 0;
  param_1[3] = 0;
  param_1[6] = lVar1;
  param_1[5] = lVar3;
  lVar3 = 0;
  do {
    lVar1 = lVar3 + 0x98;
    *(undefined4 *)((long)param_1 + lVar3 + 0x60) = 0;
    *(undefined1 *)((long)param_1 + lVar3 + 100) = 0;
    *(undefined2 *)((long)param_1 + lVar3 + 0xde) = 0;
    *(undefined8 *)((long)param_1 + lVar3 + 0xd6) = 0;
    *(undefined8 *)((long)param_1 + lVar3 + 0x66) = 0;
    *(undefined8 *)((long)param_1 + lVar3 + 0x6d) = 0;
    *(undefined8 *)((long)param_1 + lVar3 + 0x76) = 0;
    *(undefined8 *)((long)param_1 + lVar3 + 0x7d) = 0;
    *(undefined8 *)((long)param_1 + lVar3 + 0x8d) = 0;
    *(undefined8 *)((long)param_1 + lVar3 + 0x86) = 0;
    *(undefined8 *)((long)param_1 + lVar3 + 0x9d) = 0;
    *(undefined8 *)((long)param_1 + lVar3 + 0x96) = 0;
    *(undefined8 *)((long)param_1 + lVar3 + 0xad) = 0;
    *(undefined8 *)((long)param_1 + lVar3 + 0xa6) = 0;
    *(undefined8 *)((long)param_1 + lVar3 + 0xbd) = 0;
    *(undefined8 *)((long)param_1 + lVar3 + 0xb6) = 0;
    *(undefined8 *)((long)param_1 + lVar3 + 0xcd) = 0;
    *(undefined8 *)((long)param_1 + lVar3 + 0xc6) = 0;
    lVar3 = lVar1;
  } while (lVar1 != 0x2600);
  *(undefined4 *)(param_1 + 0x4d5) = 0;
  param_1[1] = 0;
  *(undefined1 *)(param_1 + 7) = 0;
  *(undefined2 *)((long)param_1 + 0x44) = 0;
  *(undefined8 *)((long)param_1 + 0x3c) = 0;
  return;
}

// ==== Framework::CTouchPanel::Initialize()
// vaddr 0x1e9f254 | ghidra 0x1f9f254 | size 356 | symbol _ZN9Framework11CTouchPanel10InitializeEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework11CTouchPanel10InitializeEv(long param_1)

{
  long lVar1;
  undefined *puVar2;
  long *plVar3;
  long lVar4;
  
  plVar3 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x29d8,PTR__ZSt7nothrow_02cb9a80);
  if (plVar3 != (long *)0x0) {
    *plVar3 = (long)(PTR__ZTVN4Aska14BasePeripheralE_02cbc550 + 0x10);
    Aska::FastCriticalSection::FastCriticalSection()(plVar3 + 1);
    puVar2 = PTR__ZTVN4Aska10TouchPanelE_02cc3980;
    plVar3[0x13] = 0xffff0000ffff;
    *plVar3 = (long)(puVar2 + 0x10);
    *(undefined2 *)(plVar3 + 0x14) = 0xff;
    lVar4 = 0;
    do {
      *(undefined4 *)((long)plVar3 + lVar4 + 0xc0) = 0;
      *(undefined1 *)((long)plVar3 + lVar4 + 0xc4) = 0;
      *(undefined2 *)((long)plVar3 + lVar4 + 0x13e) = 0;
      *(undefined8 *)((long)plVar3 + lVar4 + 0x136) = 0;
      lVar1 = lVar4 + 0x98;
      *(undefined8 *)((long)plVar3 + lVar4 + 0xc6) = 0;
      *(undefined8 *)((long)plVar3 + lVar4 + 0xcd) = 0;
      *(undefined8 *)((long)plVar3 + lVar4 + 0xd6) = 0;
      *(undefined8 *)((long)plVar3 + lVar4 + 0xdd) = 0;
      *(undefined8 *)((long)plVar3 + lVar4 + 0xed) = 0;
      *(undefined8 *)((long)plVar3 + lVar4 + 0xe6) = 0;
      *(undefined8 *)((long)plVar3 + lVar4 + 0xfd) = 0;
      *(undefined8 *)((long)plVar3 + lVar4 + 0xf6) = 0;
      *(undefined8 *)((long)plVar3 + lVar4 + 0x10d) = 0;
      *(undefined8 *)((long)plVar3 + lVar4 + 0x106) = 0;
      *(undefined8 *)((long)plVar3 + lVar4 + 0x11d) = 0;
      *(undefined8 *)((long)plVar3 + lVar4 + 0x116) = 0;
      *(undefined8 *)((long)plVar3 + lVar4 + 0x12d) = 0;
      *(undefined8 *)((long)plVar3 + lVar4 + 0x126) = 0;
      lVar4 = lVar1;
    } while (lVar1 != 0x2600);
    *(undefined4 *)(plVar3 + 0x4d5) = 0;
    *(undefined1 *)((long)plVar3 + 0x99) = 0xff;
    plVar3[0x4d6] = 0;
    memset(plVar3 + 0x15,0,0x2600);
    *(undefined2 *)((long)plVar3 + 0x26c4) = 0;
    *(undefined4 *)(plVar3 + 0x4d8) = 0;
    (**(code **)(*plVar3 + 0x50))(plVar3);
  }
  *(long **)(param_1 + 8) = plVar3;
  Aska::Global::RegisterExPeripheral(int, Aska::BasePeripheral*)(0,plVar3);
  *(undefined8 *)(param_1 + 0x30) = 0;
  *(undefined4 *)(param_1 + 0x2648) = 0;
  *(undefined1 *)(param_1 + 0x2654) = 0;
  *(undefined1 *)(param_1 + 0x265a) = 0;
  *(undefined1 *)(param_1 + 0x2674) = 0;
  *(undefined1 *)(param_1 + 0x26a4) = 0;
  *(undefined1 *)(param_1 + 0x2680) = 0;
  *(undefined1 *)(param_1 + 0x46) = 0;
  return;
}

// ==== Framework::CTouchPanel::Release()
// vaddr 0x1e9f3b8 | ghidra 0x1f9f3b8 | size 48 | symbol _ZN9Framework11CTouchPanel7ReleaseEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework11CTouchPanel7ReleaseEv(long param_1)

{
  Aska::Global::ReleaseExPeripheral(int)(0);
  if (*(long **)(param_1 + 8) != (long *)0x0) {
    (**(code **)(**(long **)(param_1 + 8) + 8))();
    *(undefined8 *)(param_1 + 8) = 0;
  }
  return;
}

// ==== Framework::CTouchPanel::Reset()
// vaddr 0x1e9f3e8 | ghidra 0x1f9f3e8 | size 24 | symbol _ZN9Framework11CTouchPanel5ResetEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework11CTouchPanel5ResetEv(long param_1)

{
  if (*(long **)(param_1 + 8) != (long *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x01f9f3f8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(**(long **)(param_1 + 8) + 0x50))();
    return;
  }
  return;
}

// ==== Framework::CTouchPanel::Progress(float)
// vaddr 0x1e9f400 | ghidra 0x1f9f400 | size 1320 | symbol _ZN9Framework11CTouchPanel8ProgressEf | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN9Framework11CTouchPanel8ProgressEf(float param_1,long param_2)

{
  undefined2 uVar1;
  ushort uVar2;
  undefined6 uVar3;
  byte bVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  long *plVar8;
  undefined8 *puVar9;
  float fVar10;
  int iVar11;
  float fVar12;
  undefined8 uVar13;
  float fVar14;
  float fVar15;
  
  plVar8 = (long *)Aska::Global::GetExPeripheral(int)(0);
  if ((plVar8 == (long *)0x0) || (*(char *)((long)plVar8 + 0x26c4) == '\0')) goto code_r0x01f9f77c;
  Aska::TouchPanel::ResetGestureParam()(plVar8);
  uVar5 = Aska::TouchPanel::CopyMessages(Aska::TouchData*)(plVar8,param_2 + 0x48);
  *(undefined4 *)(param_2 + 0x2648) = uVar5;
  Aska::TouchPanel::UpdateGesture(Aska::TouchData*, int)(plVar8,param_2 + 0x48,uVar5);
  puVar9 = (undefined8 *)(param_2 + 0x3c);
  *puVar9 = 0;
  *(undefined1 *)(param_2 + 0x38) = 0;
  *(undefined2 *)(param_2 + 0x44) = 0;
  uVar1 = *(undefined2 *)((long)plVar8 + 0x26c2);
  uVar2 = *(ushort *)(plVar8 + 0x4d8);
  iVar6 = Aska::TouchPanel::GetTap(Aska::TouchPanel::Vector2*, int)(plVar8,param_2 + 0x264c,2);
  *(bool *)(param_2 + 0x2654) = 0 < iVar6;
  if (iVar6 < 1) {
    uVar3 = CONCAT24(uVar1,(uint)uVar2);
  }
  else {
    *(undefined1 *)(param_2 + 0x38) = 1;
    uVar3 = CONCAT24(*(undefined2 *)(param_2 + 0x264e),(uint)*(ushort *)(param_2 + 0x264c));
    *(int *)(param_2 + 0x3c) = iVar6;
    *(undefined1 *)(param_2 + 0x20) = 0;
  }
  iVar6 = Aska::TouchPanel::GetDoubleTap(Aska::TouchPanel::Vector2*, int)(plVar8,param_2 + 0x2656,1);
  *(bool *)(param_2 + 0x265a) = 0 < iVar6;
  if (0 < iVar6) {
    *(int *)(param_2 + 0x40) = iVar6;
  }
  iVar6 = (int)(short)uVar3;
  iVar11 = (int)(short)((uint6)uVar3 >> 0x20);
  bVar4 = Aska::TouchPanel::GetDrag(Aska::TouchPanel::DragParam*)(plVar8,(int *)(param_2 + 0x265c));
  *(byte *)(param_2 + 0x2674) = bVar4 & 1;
  if ((bVar4 & 1) == 0) {
    if ((*(char *)(param_2 + 0x20) != '\0') &&
       (iVar7 = (**(code **)(**(long **)PTR__ZN4Aska6Global8m_pVSyncE_02cbd460 + 8))(),
       param_1 * 3.0 < (float)(uint)(iVar7 - *(int *)(param_2 + 0x24)))) {
      uVar13 = NEON_scvtf(CONCAT44(iVar11,iVar6),4);
      fVar14 = (float)uVar13 - (float)*(undefined8 *)(param_2 + 0x18);
      fVar15 = (float)((ulong)uVar13 >> 0x20) -
               (float)((ulong)*(undefined8 *)(param_2 + 0x18) >> 0x20);
      fVar15 = fVar14 * fVar14 + fVar15 * fVar15;
      fVar14 = SQRT(fVar15);
      if (NAN(fVar14)) {
        fVar14 = (float)sqrtf(fVar15);
      }
      if ((fVar14 < _UNK_027e5198) &&
         (*(undefined1 *)(param_2 + 0x38) = 1, *(int *)(param_2 + 0x3c) == 0)) {
        *(undefined4 *)puVar9 = 1;
      }
      goto code_r0x01f9f6dc;
    }
  }
  else {
    iVar7 = *(int *)(param_2 + 0x265c);
    if (iVar7 == 2) {
      if (*(char *)(param_2 + 0x20) != '\0') {
        uVar13 = NEON_scvtf(CONCAT44((int)*(short *)(param_2 + 0x266a),
                                     (int)*(short *)(param_2 + 0x2668)),4);
        fVar14 = (float)uVar13 - (float)*(undefined8 *)(param_2 + 0x18);
        fVar15 = (float)((ulong)uVar13 >> 0x20) -
                 (float)((ulong)*(undefined8 *)(param_2 + 0x18) >> 0x20);
        fVar15 = fVar14 * fVar14 + fVar15 * fVar15;
        fVar14 = SQRT(fVar15);
        if (NAN(fVar14)) {
          fVar14 = (float)sqrtf(fVar15);
        }
        if (fVar14 < _UNK_027e5198) {
          *(undefined1 *)(param_2 + 0x38) = 1;
          if (*(int *)(param_2 + 0x3c) == 0) {
            *(undefined4 *)puVar9 = 1;
          }
          iVar6 = (int)*(short *)(param_2 + 0x2668);
          iVar11 = (int)*(short *)(param_2 + 0x266a);
        }
      }
      *(undefined8 *)(param_2 + 0x30) = 0;
code_r0x01f9f6dc:
      *(undefined1 *)(param_2 + 0x20) = 0;
    }
    else if (iVar7 == 1) {
      if (*(char *)(param_2 + 0x20) == '\0') {
        *(undefined4 *)(param_2 + 0x265c) = 0;
        *(undefined1 *)(param_2 + 0x20) = 1;
        *(float *)(param_2 + 0x18) = (float)(int)*(short *)(param_2 + 0x2668);
        *(float *)(param_2 + 0x1c) = (float)(int)*(short *)(param_2 + 0x266a);
        uVar5 = (**(code **)(**(long **)PTR__ZN4Aska6Global8m_pVSyncE_02cbd460 + 8))();
        *(undefined4 *)(param_2 + 0x24) = uVar5;
      }
      fVar14 = (float)(int)*(short *)(param_2 + 0x2668) - *(float *)(param_2 + 0x18);
      fVar15 = (float)(int)*(short *)(param_2 + 0x266a) - *(float *)(param_2 + 0x1c);
      if (*(float *)(param_2 + 0x2c) * *(float *)(param_2 + 0x2c) <=
          fVar14 * fVar14 + fVar15 * fVar15) {
        fVar15 = *(float *)(param_2 + 0x18) - (float)(int)*(short *)(param_2 + 0x2668);
        fVar14 = *(float *)(param_2 + 0x1c) - (float)(int)*(short *)(param_2 + 0x266a);
        fVar12 = fVar15 * fVar15 + fVar14 * fVar14;
        fVar10 = SQRT(fVar12);
        *(float *)(param_2 + 0x30) = fVar15;
        *(float *)(param_2 + 0x34) = fVar14;
        if (NAN(fVar10)) {
          fVar10 = (float)sqrtf(fVar12);
        }
        fVar10 = fVar10 / *(float *)(param_2 + 0x28);
        fVar15 = *(float *)(param_2 + 0x30) * *(float *)(param_2 + 0x30) +
                 *(float *)(param_2 + 0x34) * *(float *)(param_2 + 0x34);
        fVar14 = SQRT(fVar15);
        if (NAN(fVar14)) {
          fVar14 = (float)sqrtf(fVar15);
        }
        if (1.0 < fVar10) {
          fVar10 = 1.0;
        }
        if (fVar14 == 0.0) {
          fVar15 = 0.0;
          fVar14 = 0.0;
        }
        else {
          fVar15 = *(float *)(param_2 + 0x30) / fVar14;
          fVar14 = *(float *)(param_2 + 0x34) / fVar14;
        }
        *(float *)(param_2 + 0x30) = fVar10 * fVar15;
        *(float *)(param_2 + 0x34) = fVar10 * fVar14;
      }
      else {
        *(undefined8 *)(param_2 + 0x30) = 0;
      }
    }
    else if (iVar7 == 0) {
      *(undefined1 *)(param_2 + 0x20) = 1;
      *(float *)(param_2 + 0x18) = (float)(int)*(short *)(param_2 + 0x2668);
      *(float *)(param_2 + 0x1c) = (float)(int)*(short *)(param_2 + 0x266a);
      uVar5 = (**(code **)(**(long **)PTR__ZN4Aska6Global8m_pVSyncE_02cbd460 + 8))();
      *(undefined4 *)(param_2 + 0x24) = uVar5;
      *(undefined8 *)(param_2 + 0x30) = 0;
    }
  }
  bVar4 = Aska::TouchPanel::GetTouchAndHold(Aska::TouchPanel::TouchAndHoldParam*)(plVar8,param_2 + 0x2678);
  *(byte *)(param_2 + 0x2680) = bVar4 & 1;
  if ((bVar4 & 1) != 0) {
    *(undefined1 *)(param_2 + 0x44) = 1;
  }
  fVar15 = *(float *)(param_2 + 0x2688);
  bVar4 = Aska::TouchPanel::GetPinchOutIn(Aska::TouchPanel::PinchOutInParam*)(plVar8,param_2 + 0x2684);
  *(byte *)(param_2 + 0x26a4) = bVar4 & 1;
  fVar14 = _UNK_027e6a14;
  if ((bVar4 & 1) == 0) {
code_r0x01f9f75c:
    *(undefined4 *)(param_2 + 0x26a8) = 0;
  }
  else {
    fVar15 = *(float *)(param_2 + 0x2688) - fVar15;
    fVar10 = -fVar15;
    if (0.0 <= fVar15) {
      fVar10 = fVar15;
    }
    *(undefined1 *)(param_2 + 0x45) = 1;
    *(float *)(param_2 + 0x26a8) = fVar15;
    if (fVar14 < fVar10) goto code_r0x01f9f75c;
  }
  *(int *)(param_2 + 0x10) = iVar6;
  *(int *)(param_2 + 0x14) = iVar11;
  (**(code **)(*plVar8 + 0x50))(plVar8);
code_r0x01f9f77c:
  *(undefined1 *)(param_2 + 0x46) = 0;
  Aska::Global::GetPeripheral(int)(0);
  if (((bRam0000000002d006a8 & 1) == 0) && (*PTR__ZN4Aska8PadDroid7m_bBackE_02cb9e10 != '\0')) {
    bRam0000000002d006a8 = 1;
    *(undefined1 *)(param_2 + 0x46) = 1;
  }
  else if ((*PTR__ZN4Aska8PadDroid7m_bBackE_02cb9e10 == '\0') &&
          (((bRam0000000002d006a8 ^ 1) & 1) == 0)) {
    bRam0000000002d006a8 = 0;
  }
  return;
}

// ==== Framework::CTouchPanel::InputFromMouse()
// vaddr 0x1e9f928 | ghidra 0x1f9f928 | size 4 | symbol _ZN9Framework11CTouchPanel14InputFromMouseEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework11CTouchPanel14InputFromMouseEv(void)

{
  return;
}

// ==== Framework::CTouchPanel::IsConnected() const
// vaddr 0x1e9fbcc | ghidra 0x1f9fbcc | size 52 | symbol _ZNK9Framework11CTouchPanel11IsConnectedEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK9Framework11CTouchPanel11IsConnectedEv(void)

{
  long lVar1;
  
  lVar1 = Aska::Global::GetExPeripheral(int)(0);
  if ((lVar1 != 0) && (*(char *)(lVar1 + 0x26c4) != '\0')) {
    return 1;
  }
  return 0;
}

// ==== Framework::CTouchPanel::rAnalogVirtual() const
// vaddr 0x1e9fc00 | ghidra 0x1f9fc00 | size 8 | symbol _ZNK9Framework11CTouchPanel14rAnalogVirtualEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK9Framework11CTouchPanel14rAnalogVirtualEv(long param_1)

{
  return param_1 + 0x30;
}

// ==== Framework::CTouchPanel::rTouchDataBuffer() const
// vaddr 0x1e9fc08 | ghidra 0x1f9fc08 | size 8 | symbol _ZNK9Framework11CTouchPanel16rTouchDataBufferEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK9Framework11CTouchPanel16rTouchDataBufferEv(long param_1)

{
  return param_1 + 0x48;
}

// ==== Framework::CTouchPanel::NumTouchData() const
// vaddr 0x1e9fc10 | ghidra 0x1f9fc10 | size 8 | symbol _ZNK9Framework11CTouchPanel12NumTouchDataEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK9Framework11CTouchPanel12NumTouchDataEv(long param_1)

{
  return *(undefined4 *)(param_1 + 0x2648);
}

// ==== Framework::CTouchPanel::rTapParam(unsigned int) const
// vaddr 0x1e9fc18 | ghidra 0x1f9fc18 | size 84 | symbol _ZNK9Framework11CTouchPanel9rTapParamEj | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK9Framework11CTouchPanel9rTapParamEj(long param_1,uint param_2)

{
  if (1 < param_2) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029667a0/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\TouchPanel.cpp"*/,0x1b5,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,param_2,2);
  }
  return param_1 + (ulong)param_2 * 4 + 0x264c;
}

// ==== Framework::CTouchPanel::IsTapParam() const
// vaddr 0x1e9fc6c | ghidra 0x1f9fc6c | size 12 | symbol _ZNK9Framework11CTouchPanel10IsTapParamEv | lib libSOA-3.7.0.so | 2026-10-04
undefined1 _ZNK9Framework11CTouchPanel10IsTapParamEv(long param_1)

{
  return *(undefined1 *)(param_1 + 0x2654);
}

// ==== Framework::CTouchPanel::rDoubleTapParam() const
// vaddr 0x1e9fc78 | ghidra 0x1f9fc78 | size 12 | symbol _ZNK9Framework11CTouchPanel15rDoubleTapParamEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK9Framework11CTouchPanel15rDoubleTapParamEv(long param_1)

{
  return param_1 + 0x2656;
}

// ==== Framework::CTouchPanel::IsDoubleTapParam() const
// vaddr 0x1e9fc84 | ghidra 0x1f9fc84 | size 12 | symbol _ZNK9Framework11CTouchPanel16IsDoubleTapParamEv | lib libSOA-3.7.0.so | 2026-10-04
undefined1 _ZNK9Framework11CTouchPanel16IsDoubleTapParamEv(long param_1)

{
  return *(undefined1 *)(param_1 + 0x265a);
}

// ==== Framework::CTouchPanel::rDragParam() const
// vaddr 0x1e9fc90 | ghidra 0x1f9fc90 | size 12 | symbol _ZNK9Framework11CTouchPanel10rDragParamEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK9Framework11CTouchPanel10rDragParamEv(long param_1)

{
  return param_1 + 0x265c;
}

// ==== Framework::CTouchPanel::IsDragParam() const
// vaddr 0x1e9fc9c | ghidra 0x1f9fc9c | size 12 | symbol _ZNK9Framework11CTouchPanel11IsDragParamEv | lib libSOA-3.7.0.so | 2026-10-04
undefined1 _ZNK9Framework11CTouchPanel11IsDragParamEv(long param_1)

{
  return *(undefined1 *)(param_1 + 0x2674);
}

// ==== Framework::CTouchPanel::rTouchAndHoldParam() const
// vaddr 0x1e9fca8 | ghidra 0x1f9fca8 | size 12 | symbol _ZNK9Framework11CTouchPanel18rTouchAndHoldParamEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK9Framework11CTouchPanel18rTouchAndHoldParamEv(long param_1)

{
  return param_1 + 0x2678;
}

// ==== Framework::CTouchPanel::IsTouchAndHoldParam() const
// vaddr 0x1e9fcb4 | ghidra 0x1f9fcb4 | size 12 | symbol _ZNK9Framework11CTouchPanel19IsTouchAndHoldParamEv | lib libSOA-3.7.0.so | 2026-10-04
undefined1 _ZNK9Framework11CTouchPanel19IsTouchAndHoldParamEv(long param_1)

{
  return *(undefined1 *)(param_1 + 0x2680);
}

// ==== Framework::CTouchPanel::rPinchOutInParam() const
// vaddr 0x1e9fcc0 | ghidra 0x1f9fcc0 | size 12 | symbol _ZNK9Framework11CTouchPanel16rPinchOutInParamEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK9Framework11CTouchPanel16rPinchOutInParamEv(long param_1)

{
  return param_1 + 0x2684;
}

// ==== Framework::CTouchPanel::IsPinchOutInParam() const
// vaddr 0x1e9fccc | ghidra 0x1f9fccc | size 12 | symbol _ZNK9Framework11CTouchPanel17IsPinchOutInParamEv | lib libSOA-3.7.0.so | 2026-10-04
undefined1 _ZNK9Framework11CTouchPanel17IsPinchOutInParamEv(long param_1)

{
  return *(undefined1 *)(param_1 + 0x26a4);
}

// ==== Framework::CTouchPanel::PinchOutInDeltaScale() const
// vaddr 0x1e9fcd8 | ghidra 0x1f9fcd8 | size 8 | symbol _ZNK9Framework11CTouchPanel20PinchOutInDeltaScaleEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK9Framework11CTouchPanel20PinchOutInDeltaScaleEv(long param_1)

{
  return *(undefined4 *)(param_1 + 0x26a8);
}

// ==== Framework::CTouchPanel::AnalogVirtualMaxDistance() const
// vaddr 0x1e9fce0 | ghidra 0x1f9fce0 | size 8 | symbol _ZNK9Framework11CTouchPanel24AnalogVirtualMaxDistanceEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK9Framework11CTouchPanel24AnalogVirtualMaxDistanceEv(long param_1)

{
  return *(undefined4 *)(param_1 + 0x28);
}

// ==== Framework::CTouchPanel::AnalogVirtualMaxDistance(float)
// vaddr 0x1e9fce8 | ghidra 0x1f9fce8 | size 8 | symbol _ZN9Framework11CTouchPanel24AnalogVirtualMaxDistanceEf | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework11CTouchPanel24AnalogVirtualMaxDistanceEf(undefined4 param_1,long param_2)

{
  *(undefined4 *)(param_2 + 0x28) = param_1;
  return;
}

// ==== Framework::CTouchPanel::AnalogVirtualThreshold() const
// vaddr 0x1e9fcf0 | ghidra 0x1f9fcf0 | size 8 | symbol _ZNK9Framework11CTouchPanel22AnalogVirtualThresholdEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK9Framework11CTouchPanel22AnalogVirtualThresholdEv(long param_1)

{
  return *(undefined4 *)(param_1 + 0x2c);
}

// ==== Framework::CTouchPanel::AnalogVirtualThreshold(float)
// vaddr 0x1e9fcf8 | ghidra 0x1f9fcf8 | size 8 | symbol _ZN9Framework11CTouchPanel22AnalogVirtualThresholdEf | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework11CTouchPanel22AnalogVirtualThresholdEf(undefined4 param_1,long param_2)

{
  *(undefined4 *)(param_2 + 0x2c) = param_1;
  return;
}

// ==== Framework::CTouchPanel::~CTouchPanel()
// vaddr 0x1e9fd00 | ghidra 0x1f9fd00 | size 108 | symbol _ZN9Framework11CTouchPanelD2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework11CTouchPanelD2Ev(long *param_1)

{
  undefined *puVar1;
  
  *param_1 = (long)(PTR__ZTVN9Framework11CTouchPanelE_02cbf6f0 + 0x10);
  Aska::Global::ReleaseExPeripheral(int)(0);
  if ((long *)param_1[1] != (long *)0x0) {
    (**(code **)(*(long *)param_1[1] + 8))();
    param_1[1] = 0;
  }
  puVar1 = PTR__ZN9Framework10TSingletonINS_11CTouchPanelEE11m_pInstanceE_02cbd318;
  if (*(long *)PTR__ZN9Framework10TSingletonINS_11CTouchPanelEE11m_pInstanceE_02cbd318 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029612b1/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TSingleton.h"*/,0x1d,&UNK_027daf21/*"m_pInstance is null."*/);
  }
  *(undefined8 *)puVar1 = 0;
  return;
}

// ==== Framework::CTouchPanel::~CTouchPanel()
// vaddr 0x1e9fd6c | ghidra 0x1f9fd6c | size 120 | symbol _ZN9Framework11CTouchPanelD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework11CTouchPanelD0Ev(long *param_1)

{
  undefined *puVar1;
  
  *param_1 = (long)(PTR__ZTVN9Framework11CTouchPanelE_02cbf6f0 + 0x10);
  Aska::Global::ReleaseExPeripheral(int)(0);
  if ((long *)param_1[1] != (long *)0x0) {
    (**(code **)(*(long *)param_1[1] + 8))();
    param_1[1] = 0;
  }
  puVar1 = PTR__ZN9Framework10TSingletonINS_11CTouchPanelEE11m_pInstanceE_02cbd318;
  if (*(long *)PTR__ZN9Framework10TSingletonINS_11CTouchPanelEE11m_pInstanceE_02cbd318 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029612b1/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TSingleton.h"*/,0x1d,&UNK_027daf21/*"m_pInstance is null."*/);
  }
  *(undefined8 *)puVar1 = 0;
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}


// FAILED to create function at 02964de0 typeinfo name for Framework::CPad::CUnit
// FAILED to create function at 02ba9238 Framework::CPad::vtable
// FAILED to create function at 02ba9258 Framework::CPad::CUnit::vtable
// FAILED to create function at 02ba9340 Framework::CPad::typeinfo
// FAILED to create function at 02ba9370 Framework::CPad::CUnit::typeinfo
// FAILED to create function at 02ba9388 Framework::CPadReader::vtable
// FAILED to create function at 02ba9440 Framework::CPadReader::typeinfo
// FAILED to create function at 02bab4f8 Framework::CTouchPanel::vtable
// FAILED to create function at 02bab530 Framework::CTouchPanel::typeinfo
