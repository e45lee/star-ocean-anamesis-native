// port/decomp/audio/framework.c: Ghidra decompiles for the audio subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-08 13:04 UTC: tools/decomp.sh '--into' 'audio/framework' 'Framework::CSound[A-Za-z0-9]*::'

// ==== Framework::CSound::Volume3D()
// vaddr 0x1e97918 | ghidra 0x1f97918 | size 60 | symbol _ZN9Framework6CSound8Volume3DEv | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined1  [16] _ZN9Framework6CSound8Volume3DEv(void)

{
  undefined4 extraout_s0;
  undefined4 extraout_var;
  undefined8 extraout_var_00;
  undefined1 auVar1 [16];
  
  if (_UNK_02965bf8 < *(float *)(*(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50 + 0x610)) {
    (*(code *)PTR_powf_02c96d40)
              (0x41200000,
               *(float *)(*(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50 + 0x610) *
               _UNK_027edb4c);
    auVar1._4_4_ = extraout_var;
    auVar1._0_4_ = extraout_s0;
    auVar1._8_8_ = extraout_var_00;
    return auVar1;
  }
  return ZEXT816(0);
}

// ==== Framework::CSound::Volume3D(float)
// vaddr 0x1e97954 | ghidra 0x1f97954 | size 72 | symbol _ZN9Framework6CSound8Volume3DEf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN9Framework6CSound8Volume3DEf(float param_1)

{
  long lVar1;
  float fVar2;
  
  lVar1 = *(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50;
  fVar2 = _UNK_02965bf8;
  if (_UNK_027fac84 <= ABS(param_1)) {
    fVar2 = (float)log10f();
    fVar2 = fVar2 * 20.0;
  }
  *(float *)(lVar1 + 0x610) = fVar2;
  return;
}

// ==== Framework::CSound::EmitterMinDistance()
// vaddr 0x1e9799c | ghidra 0x1f9799c | size 20 | symbol _ZN9Framework6CSound18EmitterMinDistanceEv | lib libSOA-3.7.0.so | 2026-10-08
undefined4 _ZN9Framework6CSound18EmitterMinDistanceEv(void)

{
  return *(undefined4 *)(*(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50 + 0x614);
}

// ==== Framework::CSound::EmitterMinDistance(float)
// vaddr 0x1e979b0 | ghidra 0x1f979b0 | size 20 | symbol _ZN9Framework6CSound18EmitterMinDistanceEf | lib libSOA-3.7.0.so | 2026-10-08
void _ZN9Framework6CSound18EmitterMinDistanceEf(undefined4 param_1)

{
  *(undefined4 *)(*(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50 + 0x614) = param_1;
  return;
}

// ==== Framework::CSound::EmitterMaxDistance()
// vaddr 0x1e979c4 | ghidra 0x1f979c4 | size 20 | symbol _ZN9Framework6CSound18EmitterMaxDistanceEv | lib libSOA-3.7.0.so | 2026-10-08
undefined4 _ZN9Framework6CSound18EmitterMaxDistanceEv(void)

{
  return *(undefined4 *)(*(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50 + 0x618);
}

// ==== Framework::CSound::EmitterMaxDistance(float)
// vaddr 0x1e979d8 | ghidra 0x1f979d8 | size 20 | symbol _ZN9Framework6CSound18EmitterMaxDistanceEf | lib libSOA-3.7.0.so | 2026-10-08
void _ZN9Framework6CSound18EmitterMaxDistanceEf(undefined4 param_1)

{
  *(undefined4 *)(*(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50 + 0x618) = param_1;
  return;
}

// ==== Framework::CSound::RolloffFactor()
// vaddr 0x1e979ec | ghidra 0x1f979ec | size 8 | symbol _ZN9Framework6CSound13RolloffFactorEv | lib libSOA-3.7.0.so | 2026-10-08
undefined1  [16] _ZN9Framework6CSound13RolloffFactorEv(void)

{
  return ZEXT816(0);
}

// ==== Framework::CSound::RolloffFactor(float)
// vaddr 0x1e979f4 | ghidra 0x1f979f4 | size 4 | symbol _ZN9Framework6CSound13RolloffFactorEf | lib libSOA-3.7.0.so | 2026-10-08
void _ZN9Framework6CSound13RolloffFactorEf(void)

{
  return;
}

// ==== Framework::CSound::ListenerMinDistance()
// vaddr 0x1e979f8 | ghidra 0x1f979f8 | size 20 | symbol _ZN9Framework6CSound19ListenerMinDistanceEv | lib libSOA-3.7.0.so | 2026-10-08
undefined4 _ZN9Framework6CSound19ListenerMinDistanceEv(void)

{
  return *(undefined4 *)(*(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50 + 0x6a0);
}

// ==== Framework::CSound::ListenerMinDistance(float)
// vaddr 0x1e97a0c | ghidra 0x1f97a0c | size 20 | symbol _ZN9Framework6CSound19ListenerMinDistanceEf | lib libSOA-3.7.0.so | 2026-10-08
void _ZN9Framework6CSound19ListenerMinDistanceEf(undefined4 param_1)

{
  *(undefined4 *)(*(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50 + 0x6a0) = param_1;
  return;
}

// ==== Framework::CSound::ListenerMaxDistance()
// vaddr 0x1e97a20 | ghidra 0x1f97a20 | size 20 | symbol _ZN9Framework6CSound19ListenerMaxDistanceEv | lib libSOA-3.7.0.so | 2026-10-08
undefined4 _ZN9Framework6CSound19ListenerMaxDistanceEv(void)

{
  return *(undefined4 *)(*(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50 + 0x6a4);
}

// ==== Framework::CSound::ListenerMaxDistance(float)
// vaddr 0x1e97a34 | ghidra 0x1f97a34 | size 100 | symbol _ZN9Framework6CSound19ListenerMaxDistanceEf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Possible PIC construction at 0x01f97a54: Changing call to branch */
/* WARNING: Possible PIC construction at 0x01f97a6c: Changing call to branch */
/* WARNING: Possible PIC construction at 0x01f97a84: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0x01f97a70) */
/* WARNING: Removing unreachable block (ram,0x01f97a58) */
/* WARNING: Removing unreachable block (ram,0x01f97a88) */

void _ZN9Framework6CSound19ListenerMaxDistanceEf(undefined4 param_1)

{
  long lVar1;
  
  lVar1 = *(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50;
  *(undefined4 *)(lVar1 + 0x6a4) = param_1;
  (*(code *)PTR__ZN4Aska13Audio3DEngine21UpdateSpeakerPositionEi_02cad848)(lVar1 + 0x390,0);
  return;
}

// ==== Framework::CSound::ListenerOffsetZ()
// vaddr 0x1e97a98 | ghidra 0x1f97a98 | size 20 | symbol _ZN9Framework6CSound15ListenerOffsetZEv | lib libSOA-3.7.0.so | 2026-10-08
undefined4 _ZN9Framework6CSound15ListenerOffsetZEv(void)

{
  return *(undefined4 *)(*(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50 + 0x490);
}

// ==== Framework::CSound::ListenerOffsetZ(float)
// vaddr 0x1e97aac | ghidra 0x1f97aac | size 20 | symbol _ZN9Framework6CSound15ListenerOffsetZEf | lib libSOA-3.7.0.so | 2026-10-08
void _ZN9Framework6CSound15ListenerOffsetZEf(undefined4 param_1)

{
  *(undefined4 *)(*(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50 + 0x490) = param_1;
  return;
}

// ==== Framework::CSound::MaxGain()
// vaddr 0x1e97ac0 | ghidra 0x1f97ac0 | size 20 | symbol _ZN9Framework6CSound7MaxGainEv | lib libSOA-3.7.0.so | 2026-10-08
undefined4 _ZN9Framework6CSound7MaxGainEv(void)

{
  return *(undefined4 *)(*(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50 + 0x6a8);
}

// ==== Framework::CSound::MaxGain(float)
// vaddr 0x1e97ad4 | ghidra 0x1f97ad4 | size 20 | symbol _ZN9Framework6CSound7MaxGainEf | lib libSOA-3.7.0.so | 2026-10-08
void _ZN9Framework6CSound7MaxGainEf(undefined4 param_1)

{
  *(undefined4 *)(*(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50 + 0x6a8) = param_1;
  return;
}

// ==== Framework::CSound::SpeakerPositionRadian(unsigned int, float)
// vaddr 0x1e97ae8 | ghidra 0x1f97ae8 | size 96 | symbol _ZN9Framework6CSound21SpeakerPositionRadianEjf | lib libSOA-3.7.0.so | 2026-10-08
void _ZN9Framework6CSound21SpeakerPositionRadianEjf(undefined4 param_1,uint param_2)

{
  long lVar1;
  
  if (5 < param_2) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965bfc/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Sound.cpp"*/,0xb3,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,param_2,6);
  }
  lVar1 = *(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50;
  *(undefined4 *)(lVar1 + 0x390 + (long)(int)param_2 * 4 + 0x28c) = param_1;
  (*(code *)PTR__ZN4Aska13Audio3DEngine21UpdateSpeakerPositionEi_02cad848)(lVar1 + 0x390,param_2);
  return;
}

// ==== Framework::CSound::SpeakerPositionRadian(unsigned int)
// vaddr 0x1e97b48 | ghidra 0x1f97b48 | size 76 | symbol _ZN9Framework6CSound21SpeakerPositionRadianEj | lib libSOA-3.7.0.so | 2026-10-08
undefined4 _ZN9Framework6CSound21SpeakerPositionRadianEj(uint param_1)

{
  if (5 < param_1) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965bfc/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Sound.cpp"*/,0xbc,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,param_1,6);
  }
  return *(undefined4 *)
          (*(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50 + (long)(int)param_1 * 4 + 0x61c)
  ;
}

// ==== Framework::CSound::SetAudioListener(Aska::HierarchicalObject*, float)
// vaddr 0x1e97b94 | ghidra 0x1f97b94 | size 32 | symbol _ZN9Framework6CSound16SetAudioListenerEPN4Aska18HierarchicalObjectEf | lib libSOA-3.7.0.so | 2026-10-08
void _ZN9Framework6CSound16SetAudioListenerEPN4Aska18HierarchicalObjectEf(undefined8 param_1)

{
  (*(code *)PTR__ZN4Aska13Audio3DEngine16SetAudioListenerEPNS_18HierarchicalObjectEf_02c8efd8)
            (*(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50 + 0x390,param_1);
  return;
}

// ==== Framework::CSound::DeleteAudioListener()
// vaddr 0x1e97bb4 | ghidra 0x1f97bb4 | size 20 | symbol _ZN9Framework6CSound19DeleteAudioListenerEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN9Framework6CSound19DeleteAudioListenerEv(void)

{
  (*(code *)PTR__ZN4Aska13Audio3DEngine19DeleteAudioListenerEv_02c973b8)
            (*(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50 + 0x390);
  return;
}

// ==== Framework::CSound::tArguments::tArguments()
// vaddr 0x1e97bc8 | ghidra 0x1f97bc8 | size 80 | symbol _ZN9Framework6CSound10tArgumentsC1Ev | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN9Framework6CSound10tArgumentsC2Ev(long param_1)

{
  undefined4 uVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined *puVar4;
  long lVar5;
  
  *(undefined4 *)(param_1 + 0x34) = 0;
  uVar3 = _UNK_027dbb38;
  uVar2 = _UNK_027dbb30;
  *(undefined1 *)(param_1 + 0x38) = 0;
  *(undefined1 *)(param_1 + 0x40) = 0;
  puVar4 = PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50;
  *(undefined8 *)(param_1 + 0x58) = uVar3;
  *(undefined8 *)(param_1 + 0x50) = uVar2;
  lVar5 = *(long *)puVar4;
  *(undefined4 *)(param_1 + 0x60) = *(undefined4 *)(lVar5 + 0x614);
  uVar1 = *(undefined4 *)(lVar5 + 0x618);
  *(undefined8 *)(param_1 + 0x58) = uVar3;
  *(undefined8 *)(param_1 + 0x50) = uVar2;
  *(undefined4 *)(param_1 + 100) = uVar1;
  Aska::SoundManager::SetDefaultDirectPlaybackSettings(Aska::DirectPlaybackSettings*)();
  *(undefined1 *)(param_1 + 0x1f) = 0;
  return;
}

// ==== Framework::CSound::tArguments::Set3D(Framework::CVector const&)
// vaddr 0x1e97c18 | ghidra 0x1f97c18 | size 44 | symbol _ZN9Framework6CSound10tArguments5Set3DERKNS_7CVectorE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN9Framework6CSound10tArguments5Set3DERKNS_7CVectorE(long param_1,undefined4 *param_2)

{
  *(undefined1 *)(param_1 + 0x40) = 1;
  *(undefined4 *)(param_1 + 0x50) = *param_2;
  *(undefined4 *)(param_1 + 0x54) = param_2[1];
  *(undefined4 *)(param_1 + 0x58) = param_2[2];
  *(undefined4 *)(param_1 + 0x5c) = param_2[3];
  return;
}

// ==== Framework::CSound::CElement::CElement()
// vaddr 0x1e97c44 | ghidra 0x1f97c44 | size 28 | symbol _ZN9Framework6CSound8CElementC1Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN9Framework6CSound8CElementC2Ev(long *param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZTVN9Framework6CSound8CElementE_02cc3c98;
  param_1[2] = 0;
  param_1[4] = 0;
  *param_1 = (long)(puVar1 + 0x10);
  return;
}

// ==== Framework::CSound::CElement::~CElement()
// vaddr 0x1e97c60 | ghidra 0x1f97c60 | size 84 | symbol _ZN9Framework6CSound8CElementD2Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN9Framework6CSound8CElementD1Ev(long *param_1)

{
  long *plVar1;
  
  *param_1 = (long)(PTR__ZTVN9Framework6CSound8CElementE_02cc3c98 + 0x10);
  if ((long *)param_1[2] != (long *)0x0) {
    (**(code **)(*(long *)param_1[2] + 0x38))();
    param_1[2] = 0;
  }
  plVar1 = (long *)param_1[4];
  if (plVar1 != (long *)0x0) {
    (**(code **)(*plVar1 + 0x38))(plVar1,0);
    param_1[4] = 0;
  }
  return;
}

// ==== Framework::CSound::CElement::Release()
// vaddr 0x1e97cb4 | ghidra 0x1f97cb4 | size 68 | symbol _ZN9Framework6CSound8CElement7ReleaseEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN9Framework6CSound8CElement7ReleaseEv(long param_1)

{
  long *plVar1;
  
  if (*(long **)(param_1 + 0x10) != (long *)0x0) {
    (**(code **)(**(long **)(param_1 + 0x10) + 0x38))();
    *(undefined8 *)(param_1 + 0x10) = 0;
  }
  plVar1 = *(long **)(param_1 + 0x20);
  if (plVar1 != (long *)0x0) {
    (**(code **)(*plVar1 + 0x38))(plVar1,0);
    *(undefined8 *)(param_1 + 0x20) = 0;
  }
  return;
}

// ==== Framework::CSound::CElement::~CElement()
// vaddr 0x1e97cf8 | ghidra 0x1f97cf8 | size 84 | symbol _ZN9Framework6CSound8CElementD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN9Framework6CSound8CElementD0Ev(long *param_1)

{
  long *plVar1;
  
  *param_1 = (long)(PTR__ZTVN9Framework6CSound8CElementE_02cc3c98 + 0x10);
  if ((long *)param_1[2] != (long *)0x0) {
    (**(code **)(*(long *)param_1[2] + 0x38))();
    param_1[2] = 0;
  }
  plVar1 = (long *)param_1[4];
  if (plVar1 != (long *)0x0) {
    (**(code **)(*plVar1 + 0x38))(plVar1,0);
  }
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Framework::CSound::CElement::Initialize()
// vaddr 0x1e97d4c | ghidra 0x1f97d4c | size 412 | symbol _ZN9Framework6CSound8CElement10InitializeEv | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN9Framework6CSound8CElement10InitializeEv(long param_1)

{
  undefined *puVar1;
  byte bVar2;
  byte bVar3;
  long lVar4;
  long lVar5;
  undefined4 uVar6;
  long *plVar7;
  code *pcVar8;
  long *plVar9;
  long *plVar10;
  long *plVar11;
  
  if (*(long *)(param_1 + 0x10) != 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965bfc/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Sound.cpp"*/,0x105,&UNK_02965c4d/*"m_pAskaSoundObject isn't null.(%08x)"*/);
  }
  *(undefined8 *)(param_1 + 8) = *(undefined8 *)PTR__ZN9Framework6CSound14iInvalidHandleE_02cc4340;
  if (*(long *)(param_1 + 0x20) != 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965bfc/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Sound.cpp"*/,0x107,&UNK_02965c72/*"m_pHierarchicalObject isn't null.(%08x)"*/);
  }
  plVar7 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x1a0,PTR__ZSt7nothrow_02cb9a80);
  puVar1 = PTR__ZTVN4Aska4TaskE_02cbe020;
  if (plVar7 != (long *)0x0) {
    plVar7[2] = 0;
    plVar7[3] = 0;
    *(undefined2 *)((long)plVar7 + 0x24) = 0;
    pcVar8 = *(code **)(puVar1 + 0x68);
    *plVar7 = (long)(puVar1 + 0x10);
    plVar7[1] = 0;
    *(undefined1 *)((long)plVar7 + 0x26) = 0;
    uVar6 = (*pcVar8)(plVar7);
    *(undefined4 *)(plVar7 + 4) = uVar6;
    puVar1 = PTR__ZTVN4Aska27HierarchicalObjectContainerE_02cb81a8 + 0x10;
    *plVar7 = (long)(PTR__ZTVN4Aska18HierarchicalObjectE_02cb6bb0 + 0x10);
    plVar9 = plVar7 + 6;
    *plVar9 = (long)puVar1;
    plVar7[0x14] = 0x3f8000003f800000;
    plVar7[0x15] = 0x3f8000003f800000;
    lVar5 = _UNK_027dbb38;
    lVar4 = _UNK_027dbb30;
    bVar2 = *(byte *)(plVar7 + 0x25);
    bVar3 = *(byte *)((long)plVar7 + 0x129);
    *(byte *)((long)plVar7 + 0x129) = bVar3 & 0xfc;
    plVar7[0x11] = lVar5;
    plVar7[0x10] = lVar4;
    plVar7[0x13] = lVar5;
    plVar7[0x12] = lVar4;
    *(byte *)(plVar7 + 0x25) = bVar2 & 0xde | 1;
    plVar10 = plVar7 + 0x18;
    do {
      plVar11 = (long *)((long)plVar10 + 0x7fU & 0xffffffffffffff81);
      Hint_Prefetch(plVar10,0,2,0);
      plVar10 = plVar11;
    } while (plVar11 < plVar7 + 0x1a);
    plVar7[0x20] = (long)plVar9;
    plVar7[0x21] = (long)plVar9;
    *(byte *)((long)plVar7 + 0x129) = bVar3 & 0xf8;
    plVar7[0x18] = 0;
    plVar7[0x19] = 0x3f80000000000000;
    plVar7[0x1b] = lVar5;
    plVar7[0x1a] = lVar4;
    plVar7[0x1d] = lVar5;
    plVar7[0x1c] = lVar4;
    plVar7[0x17] = lVar5;
    plVar7[0x16] = lVar4;
    plVar7[0x22] = 0;
    plVar7[0x23] = 0;
    plVar7[0x1e] = 0;
    plVar7[0x1f] = 0;
    plVar7[5] = 0;
    plVar7[0x23] = (long)plVar7;
    plVar7[0x24] = (long)(plVar7 + 8);
    plVar7[0x30] = 0;
    plVar7[0x31] = 0;
    *(undefined4 *)(plVar7 + 0x32) = 0;
    *(undefined1 *)((long)plVar7 + 0x195) = 0;
    *(undefined1 *)((long)plVar7 + 0x194) = 1;
    *(byte *)(plVar7 + 0x25) = bVar2 & 200 | 1;
    *(undefined1 *)((long)plVar7 + 0x197) = 0;
  }
  *(long **)(param_1 + 0x20) = plVar7;
  (**(code **)(*plVar7 + 200))(0,0,0,plVar7);
  *(undefined1 *)(param_1 + 0x28) = 0;
  return;
}

// ==== Framework::CSound::CElement::rHierarchicalObject()
// vaddr 0x1e97ee8 | ghidra 0x1f97ee8 | size 60 | symbol _ZN9Framework6CSound8CElement19rHierarchicalObjectEv | lib libSOA-3.7.0.so | 2026-10-08
long _ZN9Framework6CSound8CElement19rHierarchicalObjectEv(long param_1)

{
  if (*(long *)(param_1 + 0x20) != 0) {
    return *(long *)(param_1 + 0x20);
  }
  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965bfc/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Sound.cpp"*/,0x11d,&UNK_02965c9a/*"m_pHierarchicalObject is null."*/);
  return *(long *)(param_1 + 0x20);
}

// ==== Framework::CSound::CElement::Activate(unsigned long, Aska::SoundObject&, Framework::CSound::tArguments const&, char const*)
// vaddr 0x1e97f24 | ghidra 0x1f97f24 | size 152 | symbol _ZN9Framework6CSound8CElement8ActivateEmRN4Aska11SoundObjectERKNS0_10tArgumentsEPKc | lib libSOA-3.7.0.so | 2026-10-08
void _ZN9Framework6CSound8CElement8ActivateEmRN4Aska11SoundObjectERKNS0_10tArgumentsEPKc
               (long param_1,undefined8 param_2,undefined8 param_3,long param_4)

{
  undefined1 uVar1;
  
  if (*(long *)(param_1 + 8) != *(long *)PTR__ZN9Framework6CSound14iInvalidHandleE_02cc4340) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965bfc/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Sound.cpp"*/,0x123,&UNK_02965cb9/*"m_Handle == iInvalidHandle is null."*/);
  }
  *(undefined8 *)(param_1 + 8) = param_2;
  if (*(long *)(param_1 + 0x10) != 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965bfc/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Sound.cpp"*/,0x125,&UNK_02965c4d/*"m_pAskaSoundObject isn't null.(%08x)"*/);
  }
  *(undefined8 *)(param_1 + 0x10) = param_3;
  *(undefined1 *)(param_1 + 0x18) = *(undefined1 *)(param_4 + 0x38);
  uVar1 = *(undefined1 *)(param_4 + 0x40);
  *(undefined1 *)(param_1 + 0x29) = 0;
  *(undefined1 *)(param_1 + 0x28) = uVar1;
  return;
}

// ==== Framework::CSound::CElement::IsActive() const
// vaddr 0x1e97fbc | ghidra 0x1f97fbc | size 28 | symbol _ZNK9Framework6CSound8CElement8IsActiveEv | lib libSOA-3.7.0.so | 2026-10-08
bool _ZNK9Framework6CSound8CElement8IsActiveEv(long param_1)

{
  return *(long *)(param_1 + 8) != *(long *)PTR__ZN9Framework6CSound14iInvalidHandleE_02cc4340;
}

// ==== Framework::CSound::CElement::Handle() const
// vaddr 0x1e97fd8 | ghidra 0x1f97fd8 | size 8 | symbol _ZNK9Framework6CSound8CElement6HandleEv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK9Framework6CSound8CElement6HandleEv(long param_1)

{
  return *(undefined8 *)(param_1 + 8);
}

// ==== Framework::CSound::CElement::pName() const
// vaddr 0x1e97fe0 | ghidra 0x1f97fe0 | size 8 | symbol _ZNK9Framework6CSound8CElement5pNameEv | lib libSOA-3.7.0.so | 2026-10-08
long _ZNK9Framework6CSound8CElement5pNameEv(long param_1)

{
  return param_1 + 0x29;
}

// ==== Framework::CSound::CElement::Position() const
// vaddr 0x1e97fe8 | ghidra 0x1f97fe8 | size 56 | symbol _ZNK9Framework6CSound8CElement8PositionEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZNK9Framework6CSound8CElement8PositionEv(undefined4 *param_1,long param_2)

{
  long lVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  
  if (*(char *)(param_2 + 0x28) == '\0') {
    uVar2 = 0;
    uVar3 = 0;
    uVar4 = 0;
  }
  else {
    lVar1 = *(long *)(param_2 + 0x20);
    uVar2 = *(undefined4 *)(lVar1 + 0x80);
    uVar3 = *(undefined4 *)(lVar1 + 0x84);
    uVar4 = *(undefined4 *)(lVar1 + 0x88);
  }
  *param_1 = uVar2;
  param_1[1] = uVar3;
  param_1[2] = uVar4;
  param_1[3] = 0x3f800000;
  return;
}

// ==== Framework::CSound::CElement::Position(Framework::CVector const&)
// vaddr 0x1e98020 | ghidra 0x1f98020 | size 68 | symbol _ZN9Framework6CSound8CElement8PositionERKNS_7CVectorE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN9Framework6CSound8CElement8PositionERKNS_7CVectorE(long param_1,undefined4 *param_2)

{
  if (*(char *)(param_1 + 0x28) != '\0') {
    (**(code **)(**(long **)(param_1 + 0x20) + 200))(*param_2,param_2[1],param_2[2]);
                    /* WARNING: Could not recover jumptable at 0x01f98058. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(**(long **)(param_1 + 0x20) + 0xa8))();
    return;
  }
  return;
}

// ==== Framework::CSound::CElement::Is3D() const
// vaddr 0x1e98064 | ghidra 0x1f98064 | size 8 | symbol _ZNK9Framework6CSound8CElement4Is3DEv | lib libSOA-3.7.0.so | 2026-10-08
undefined1 _ZNK9Framework6CSound8CElement4Is3DEv(long param_1)

{
  return *(undefined1 *)(param_1 + 0x28);
}

// ==== Framework::CSound::CElement::Volume(float, float)
// vaddr 0x1e9806c | ghidra 0x1f9806c | size 116 | symbol _ZN9Framework6CSound8CElement6VolumeEff | lib libSOA-3.7.0.so | 2026-10-08
void _ZN9Framework6CSound8CElement6VolumeEff(undefined4 param_1,float param_2,long param_3)

{
  long lVar1;
  undefined4 uStack_24;
  
  lVar1 = *(long *)(param_3 + 0x10);
  if (lVar1 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965bfc/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Sound.cpp"*/,0x16e,&UNK_02965cdd/*"m_pAskaSoundObject is null."*/);
    lVar1 = *(long *)(param_3 + 0x10);
  }
  Aska::Sequencer2::AddMessageNote(unsigned int, float, void const*, void const*)(*(float *)(lVar1 + 0x108) + 0.0,lVar1 + 0x18,5,CONCAT44(uStack_24,param_1),
                  (long)(int)param_2);
  return;
}

// ==== Framework::CSound::CElement::Volume() const
// vaddr 0x1e980e0 | ghidra 0x1f980e0 | size 92 | symbol _ZNK9Framework6CSound8CElement6VolumeEv | lib libSOA-3.7.0.so | 2026-10-08
undefined1  [16] _ZNK9Framework6CSound8CElement6VolumeEv(long param_1)

{
  long *plVar1;
  undefined4 extraout_s0;
  undefined4 extraout_var;
  undefined8 extraout_var_00;
  undefined1 auVar2 [16];
  
  if (*(long *)(param_1 + 0x10) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965bfc/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Sound.cpp"*/,0x174,&UNK_02965cdd/*"m_pAskaSoundObject is null."*/);
    plVar1 = *(long **)(*(long *)(param_1 + 0x10) + 0x128);
  }
  else {
    plVar1 = *(long **)(*(long *)(param_1 + 0x10) + 0x128);
  }
  if (plVar1 != (long *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x01f98108. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*plVar1 + 0x88))(plVar1,0);
    auVar2._4_4_ = extraout_var;
    auVar2._0_4_ = extraout_s0;
    auVar2._8_8_ = extraout_var_00;
    return auVar2;
  }
  return ZEXT816(0);
}

// ==== Framework::CSound::CElement::Pitch(float, float)
// vaddr 0x1e9813c | ghidra 0x1f9813c | size 116 | symbol _ZN9Framework6CSound8CElement5PitchEff | lib libSOA-3.7.0.so | 2026-10-08
void _ZN9Framework6CSound8CElement5PitchEff(undefined4 param_1,float param_2,long param_3)

{
  long lVar1;
  undefined4 uStack_24;
  
  lVar1 = *(long *)(param_3 + 0x10);
  if (lVar1 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965bfc/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Sound.cpp"*/,0x17a,&UNK_02965cdd/*"m_pAskaSoundObject is null."*/);
    lVar1 = *(long *)(param_3 + 0x10);
  }
  Aska::Sequencer2::AddMessageNote(unsigned int, float, void const*, void const*)(*(float *)(lVar1 + 0x108) + 0.0,lVar1 + 0x18,6,CONCAT44(uStack_24,param_1),
                  (long)(int)param_2);
  return;
}

// ==== Framework::CSound::CElement::Pitch() const
// vaddr 0x1e981b0 | ghidra 0x1f981b0 | size 92 | symbol _ZNK9Framework6CSound8CElement5PitchEv | lib libSOA-3.7.0.so | 2026-10-08
undefined1  [16] _ZNK9Framework6CSound8CElement5PitchEv(long param_1)

{
  long *plVar1;
  undefined4 extraout_s0;
  undefined4 extraout_var;
  undefined8 extraout_var_00;
  undefined1 auVar2 [16];
  
  if (*(long *)(param_1 + 0x10) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965bfc/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Sound.cpp"*/,0x180,&UNK_02965cdd/*"m_pAskaSoundObject is null."*/);
    plVar1 = *(long **)(*(long *)(param_1 + 0x10) + 0x128);
  }
  else {
    plVar1 = *(long **)(*(long *)(param_1 + 0x10) + 0x128);
  }
  if (plVar1 != (long *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x01f981d8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*plVar1 + 0x88))(plVar1,1);
    auVar2._4_4_ = extraout_var;
    auVar2._0_4_ = extraout_s0;
    auVar2._8_8_ = extraout_var_00;
    return auVar2;
  }
  return ZEXT816(0);
}

// ==== Framework::CSound::CElement::Pan(float, float)
// vaddr 0x1e9820c | ghidra 0x1f9820c | size 100 | symbol _ZN9Framework6CSound8CElement3PanEff | lib libSOA-3.7.0.so | 2026-10-08
void _ZN9Framework6CSound8CElement3PanEff(undefined4 param_1,float param_2,long param_3)

{
  long lVar1;
  
  lVar1 = *(long *)(param_3 + 0x10);
  if (lVar1 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965bfc/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Sound.cpp"*/,0x186,&UNK_02965cdd/*"m_pAskaSoundObject is null."*/);
    lVar1 = *(long *)(param_3 + 0x10);
  }
  (*(code *)PTR__ZN4Aska10Sequencer214AddMessageNoteEjfPKvS2__02c9f638)
            (*(float *)(lVar1 + 0x108) + 0.0,lVar1 + 0x18,7,param_1,(long)(int)param_2);
  return;
}

// ==== Framework::CSound::CElement::Pan() const
// vaddr 0x1e98270 | ghidra 0x1f98270 | size 92 | symbol _ZNK9Framework6CSound8CElement3PanEv | lib libSOA-3.7.0.so | 2026-10-08
undefined1  [16] _ZNK9Framework6CSound8CElement3PanEv(long param_1)

{
  long *plVar1;
  undefined4 extraout_s0;
  undefined4 extraout_var;
  undefined8 extraout_var_00;
  undefined1 auVar2 [16];
  
  if (*(long *)(param_1 + 0x10) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965bfc/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Sound.cpp"*/,0x18e,&UNK_02965cdd/*"m_pAskaSoundObject is null."*/);
    plVar1 = *(long **)(*(long *)(param_1 + 0x10) + 0x128);
  }
  else {
    plVar1 = *(long **)(*(long *)(param_1 + 0x10) + 0x128);
  }
  if (plVar1 != (long *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x01f98298. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*plVar1 + 0x88))(plVar1,2);
    auVar2._4_4_ = extraout_var;
    auVar2._0_4_ = extraout_s0;
    auVar2._8_8_ = extraout_var_00;
    return auVar2;
  }
  return ZEXT816(0);
}

// ==== Framework::CSound::CElement::pSoundObject() const
// vaddr 0x1e982cc | ghidra 0x1f982cc | size 8 | symbol _ZNK9Framework6CSound8CElement12pSoundObjectEv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK9Framework6CSound8CElement12pSoundObjectEv(long param_1)

{
  return *(undefined8 *)(param_1 + 0x10);
}

// ==== Framework::CSound::CElement::SendStopRequest(float)
// vaddr 0x1e982d4 | ghidra 0x1f982d4 | size 164 | symbol _ZN9Framework6CSound8CElement15SendStopRequestEf | lib libSOA-3.7.0.so | 2026-10-08
void _ZN9Framework6CSound8CElement15SendStopRequestEf(float param_1,long param_2)

{
  long lVar1;
  
  if (param_1 < 0.0) {
    Framework::gDoAssert(char const*, int, char const*, ...)((double)param_1,&UNK_02965bfc/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Sound.cpp"*/,0x19d,&UNK_02965cf9/*"The arguments 'aFadeTime' less than 0.(%f)"*/);
  }
  if (*(long *)(param_2 + 8) != *(long *)PTR__ZN9Framework6CSound14iInvalidHandleE_02cc4340) {
    lVar1 = *(long *)(param_2 + 0x10);
    if ((*(byte *)(lVar1 + 0x1f2) & 1) == 0) {
      if (((*(uint *)(lVar1 + 0x1e8) & 1) == 0) && ((*(uint *)(lVar1 + 0x1e8) >> 1 & 1) == 0)) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965bfc/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Sound.cpp"*/,0x1b1,&UNK_02965d24/*"Illegal sound type.(%08x)"*/);
      }
      else {
        Aska::SoundManager::StopSound(Aska::SoundObject*, unsigned int)(*(undefined8 *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50,lVar1,
                        (int)param_1);
      }
    }
    *(undefined1 *)(param_2 + 0x18) = 0;
  }
  return;
}

// ==== Framework::CSound::CElement::SendPauseRequest(float, bool)
// vaddr 0x1e98378 | ghidra 0x1f98378 | size 184 | symbol _ZN9Framework6CSound8CElement16SendPauseRequestEfb | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Possible PIC construction at 0x01f983a8: Changing call to branch */

void _ZN9Framework6CSound8CElement16SendPauseRequestEfb(double param_1,long param_2,ulong param_3)

{
  undefined8 uVar1;
  undefined *puVar2;
  
  if (0.0 <= SUB84(param_1,0)) {
    if ((*(long *)(param_2 + 8) == *(long *)PTR__ZN9Framework6CSound14iInvalidHandleE_02cc4340) ||
       ((*(byte *)(*(long *)(param_2 + 0x10) + 0x1f2) & 1) != 0)) {
      return;
    }
    if ((*(uint *)(*(long *)(param_2 + 0x10) + 0x1e8) & 3) != 0) {
      if ((param_3 & 1) != 0) {
        (*(code *)PTR__ZN4Aska12SoundManager10PauseSoundEPNS_11SoundObjectE_02cb6788)();
        return;
      }
      (*(code *)PTR__ZN4Aska12SoundManager11ResumeSoundEPNS_11SoundObjectE_02ca2518)
                (*(undefined8 *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50);
      return;
    }
    puVar2 = &UNK_02965d24/*"Illegal sound type.(%08x)"*/;
    uVar1 = 0x1cf;
  }
  else {
    param_1 = (double)SUB84(param_1,0);
    puVar2 = &UNK_02965cf9/*"The arguments 'aFadeTime' less than 0.(%f)"*/;
    uVar1 = 0x1ba;
  }
  (*(code *)PTR__ZN9Framework9gDoAssertEPKciS1_z_02ca3240)(param_1,&UNK_02965bfc/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Sound.cpp"*/,uVar1,puVar2);
  return;
}

// ==== Framework::CSound::CElement::IsKeepPlayByWatchdog(bool)
// vaddr 0x1e98430 | ghidra 0x1f98430 | size 12 | symbol _ZN9Framework6CSound8CElement20IsKeepPlayByWatchdogEb | lib libSOA-3.7.0.so | 2026-10-08
void _ZN9Framework6CSound8CElement20IsKeepPlayByWatchdogEb(long param_1,byte param_2)

{
  *(byte *)(param_1 + 0x18) = param_2 & 1;
  return;
}

// ==== Framework::CSound::CElement::Watchdog()
// vaddr 0x1e9843c | ghidra 0x1f9843c | size 12 | symbol _ZN9Framework6CSound8CElement8WatchdogEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN9Framework6CSound8CElement8WatchdogEv(long param_1)

{
  *(undefined1 *)(param_1 + 0x19) = 1;
  return;
}

// ==== Framework::CSound::CElement::PreProgress(float)
// vaddr 0x1e98448 | ghidra 0x1f98448 | size 8 | symbol _ZN9Framework6CSound8CElement11PreProgressEf | lib libSOA-3.7.0.so | 2026-10-08
void _ZN9Framework6CSound8CElement11PreProgressEf(long param_1)

{
  *(undefined1 *)(param_1 + 0x19) = 0;
  return;
}

// ==== Framework::CSound::CElement::PostProgress(float)
// vaddr 0x1e98450 | ghidra 0x1f98450 | size 224 | symbol _ZN9Framework6CSound8CElement12PostProgressEf | lib libSOA-3.7.0.so | 2026-10-08
void _ZN9Framework6CSound8CElement12PostProgressEf(long param_1)

{
  undefined *puVar1;
  long lVar2;
  
  puVar1 = PTR__ZN9Framework6CSound14iInvalidHandleE_02cc4340;
  if (*(long *)(param_1 + 8) != *(long *)PTR__ZN9Framework6CSound14iInvalidHandleE_02cc4340) {
    if (*(long *)(param_1 + 0x10) == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965bfc/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Sound.cpp"*/,0x1eb,&UNK_02965cdd/*"m_pAskaSoundObject is null."*/);
    }
    if (((*(char *)(param_1 + 0x18) != '\0') && (*(char *)(param_1 + 0x19) == '\0')) &&
       (*(long *)(param_1 + 8) != *(long *)puVar1)) {
      lVar2 = *(long *)(param_1 + 0x10);
      if ((*(byte *)(lVar2 + 0x1f2) & 1) == 0) {
        if (((*(uint *)(lVar2 + 0x1e8) & 1) == 0) && ((*(uint *)(lVar2 + 0x1e8) >> 1 & 1) == 0)) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965bfc/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Sound.cpp"*/,0x1b1,&UNK_02965d24/*"Illegal sound type.(%08x)"*/);
        }
        else {
          Aska::SoundManager::StopSound(Aska::SoundObject*, unsigned int)(*(undefined8 *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50,lVar2,10);
        }
      }
      *(undefined1 *)(param_1 + 0x18) = 0;
    }
    if ((*(byte *)((long)*(long **)(param_1 + 0x10) + 0x1f2) & 1) != 0) {
      (**(code **)(**(long **)(param_1 + 0x10) + 0x38))();
      *(undefined8 *)(param_1 + 0x10) = 0;
      *(undefined8 *)(param_1 + 8) = *(undefined8 *)puVar1;
    }
  }
  return;
}

// ==== Framework::CSoundManager::CSoundManager()
// vaddr 0x1e98530 | ghidra 0x1f98530 | size 80 | symbol _ZN9Framework13CSoundManagerC2Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN9Framework13CSoundManagerC1Ev(long *param_1)

{
  int iVar1;
  undefined *puVar2;
  int iVar3;
  
  Framework::CTimeElement::CTimeElement()();
  puVar2 = PTR__ZN9Framework13CSoundManager21gInstanceUniqueNumberE_02cb8dd8;
  *param_1 = (long)(PTR__ZTVN9Framework13CSoundManagerE_02cbd508 + 0x10);
  iVar1 = *(int *)puVar2;
  *(undefined1 *)((long)param_1 + 0x7c) = 0;
  param_1[0xb] = 0;
  param_1[10] = 0;
  param_1[0xd] = 0;
  param_1[0xc] = 0;
  *(int *)(param_1 + 9) = iVar1;
  iVar3 = 1;
  if (iVar1 != -1) {
    iVar3 = iVar1 + 1;
  }
  *(int *)puVar2 = iVar3;
  return;
}

// ==== Framework::CSoundManager::~CSoundManager()
// vaddr 0x1e98580 | ghidra 0x1f98580 | size 40 | symbol _ZN9Framework13CSoundManagerD1Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN9Framework13CSoundManagerD2Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN9Framework13CSoundManagerE_02cbd508 + 0x10);
  Framework::CSoundManager::Release()();
  (*(code *)PTR__ZN9Framework12CTimeElementD2Ev_02c99a20)(param_1);
  return;
}

// ==== Framework::CSoundManager::Release()
// vaddr 0x1e985a8 | ghidra 0x1f985a8 | size 316 | symbol _ZN9Framework13CSoundManager7ReleaseEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN9Framework13CSoundManager7ReleaseEv(long *param_1)

{
  bool bVar1;
  long *plVar2;
  long lVar3;
  ulong uVar4;
  ulong uVar5;
  
  plVar2 = (long *)param_1[0xc];
  if (plVar2 != (long *)0x0) {
    if ((int)param_1[0xe] != 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965bfc/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Sound.cpp"*/,0x27b,&UNK_02965d8d/*"Some sound sources not stoped yet.(%d)"*/);
      plVar2 = (long *)param_1[0xc];
    }
    lVar3 = (**(code **)(*plVar2 + 0x20))();
    plVar2 = (long *)param_1[0xc];
    if (lVar3 != 0) {
      uVar4 = 0;
      uVar5 = 1;
      do {
        lVar3 = (**(code **)(*plVar2 + 0x28))(plVar2,uVar4);
        if (*(long **)(lVar3 + 0x10) != (long *)0x0) {
          (**(code **)(**(long **)(lVar3 + 0x10) + 0x38))();
          *(undefined8 *)(lVar3 + 0x10) = 0;
        }
        plVar2 = *(long **)(lVar3 + 0x20);
        if (plVar2 != (long *)0x0) {
          (**(code **)(*plVar2 + 0x38))(plVar2,0);
          *(undefined8 *)(lVar3 + 0x20) = 0;
        }
        uVar4 = (**(code **)(*(long *)param_1[0xc] + 0x20))();
        plVar2 = (long *)param_1[0xc];
        bVar1 = uVar5 < uVar4;
        uVar4 = uVar5;
        uVar5 = (ulong)((int)uVar5 + 1);
      } while (bVar1);
    }
    if (plVar2 != (long *)0x0) {
      (**(code **)(*plVar2 + 8))(plVar2);
      param_1[0xc] = 0;
    }
  }
  if ((long *)param_1[10] != (long *)0x0) {
    (**(code **)(*(long *)param_1[10] + 8))();
    param_1[10] = 0;
  }
  if ((long *)param_1[0xb] != (long *)0x0) {
    (**(code **)(*(long *)param_1[0xb] + 8))();
    param_1[0xb] = 0;
  }
  if ((long *)param_1[0xd] != (long *)0x0) {
    (**(code **)(*(long *)param_1[0xd] + 8))();
    param_1[0xd] = 0;
  }
                    /* WARNING: Could not recover jumptable at 0x01f986e0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*param_1 + 0x18))(param_1);
  return;
}

// ==== Framework::CSoundManager::~CSoundManager()
// vaddr 0x1e986e4 | ghidra 0x1f986e4 | size 48 | symbol _ZN9Framework13CSoundManagerD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN9Framework13CSoundManagerD0Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN9Framework13CSoundManagerE_02cbd508 + 0x10);
  Framework::CSoundManager::Release()();
  Framework::CTimeElement::~CTimeElement()(param_1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Framework::CSoundManager::Initialize(unsigned int)
// vaddr 0x1e98714 | ghidra 0x1f98714 | size 628 | symbol _ZN9Framework13CSoundManager10InitializeEj | lib libSOA-3.7.0.so | 2026-10-08
void _ZN9Framework13CSoundManager10InitializeEj(long param_1,undefined4 param_2)

{
  bool bVar1;
  int iVar2;
  undefined *puVar3;
  long lVar4;
  long *plVar5;
  ulong uVar6;
  ulong uVar7;
  
  if (*(long *)(param_1 + 0x68) != 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965bfc/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Sound.cpp"*/,0x256,&UNK_02963d3d/*"m_pMutex isn't null.(%08x)"*/);
  }
  lVar4 = operator new(unsigned long, std::nothrow_t const&)(0xb0,PTR__ZSt7nothrow_02cb9a80);
  if (lVar4 != 0) {
    Framework::CMutex::CMutex()(lVar4);
  }
  *(long *)(param_1 + 0x68) = lVar4;
  Framework::CMutex::Initialize()(lVar4);
  if (*(long *)(param_1 + 0x50) != 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965bfc/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Sound.cpp"*/,0x25d,&UNK_02965d3e/*"m_pFiber_PreProgress isn't null.(%08x)"*/);
  }
  if (*(long *)(param_1 + 0x58) != 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965bfc/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Sound.cpp"*/,0x25e,&UNK_02965d65/*"m_pFiber_PostProgress isn't null.(%08x)"*/);
  }
  plVar5 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x48,PTR__ZSt7nothrow_02cb9a80);
  if (plVar5 != (long *)0x0) {
    Framework::CFiberUnit::CFiberUnit(unsigned int)(plVar5,0x200);
    puVar3 = PTR__ZTVN9Framework13CSoundManager12CManageFiberE_02cbe7f8;
    plVar5[7] = param_1;
    *(undefined4 *)(plVar5 + 8) = 0;
    *plVar5 = (long)(puVar3 + 0x10);
  }
  *(long **)(param_1 + 0x50) = plVar5;
  plVar5 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x48,PTR__ZSt7nothrow_02cb9a80);
  if (plVar5 != (long *)0x0) {
    Framework::CFiberUnit::CFiberUnit(unsigned int)(plVar5,0xa00);
    puVar3 = PTR__ZTVN9Framework13CSoundManager12CManageFiberE_02cbe7f8;
    plVar5[7] = param_1;
    *(undefined4 *)(plVar5 + 8) = 1;
    *plVar5 = (long)(puVar3 + 0x10);
  }
  *(long **)(param_1 + 0x58) = plVar5;
  puVar3 = PTR__ZN9Framework10TSingletonINS_12CApplication9CMainTaskEE11m_pInstanceE_02cc41c8;
  lVar4 = *(long *)
           PTR__ZN9Framework10TSingletonINS_12CApplication9CMainTaskEE11m_pInstanceE_02cc41c8;
  if (lVar4 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029612b1/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar4 = *(long *)puVar3;
  }
  plVar5 = (long *)Framework::CApplication::CMainTask::rRootFiberKernel()(lVar4);
  (**(code **)(*plVar5 + 0x48))(plVar5,*(undefined8 *)(param_1 + 0x50));
  lVar4 = *(long *)puVar3;
  if (lVar4 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029612b1/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar4 = *(long *)puVar3;
  }
  plVar5 = (long *)Framework::CApplication::CMainTask::rRootFiberKernel()(lVar4);
  (**(code **)(*plVar5 + 0x48))(plVar5,*(undefined8 *)(param_1 + 0x58));
  if (*(long *)(param_1 + 0x60) != 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965bfc/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Sound.cpp"*/,0x266,&UNK_027ee2b4/*"m_pElements isn't null.(%08x)"*/);
  }
  plVar5 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x18,PTR__ZSt7nothrow_02cb9a80);
  puVar3 = PTR__ZTVN9Framework16TObjectContainerINS_6CSound8CElementEEE_02cc3758;
  if (plVar5 != (long *)0x0) {
    plVar5[2] = 0;
    *plVar5 = (long)(puVar3 + 0x10);
  }
  *(long **)(param_1 + 0x60) = plVar5;
  (**(code **)(*plVar5 + 0x10))(plVar5,param_2);
  lVar4 = (**(code **)(**(long **)(param_1 + 0x60) + 0x20))();
  if (lVar4 != 0) {
    uVar6 = 0;
    uVar7 = 1;
    do {
      (**(code **)(**(long **)(param_1 + 0x60) + 0x28))(*(long **)(param_1 + 0x60),uVar6);
      Framework::CSound::CElement::Initialize()();
      uVar6 = (**(code **)(**(long **)(param_1 + 0x60) + 0x20))();
      bVar1 = uVar7 < uVar6;
      uVar6 = uVar7;
      uVar7 = (ulong)((int)uVar7 + 1);
    } while (bVar1);
  }
  iVar2 = *(int *)PTR__ZN9Framework19CHandleManager_Base19iInvalidHandleValueE_02cba248;
  *(undefined4 *)(param_1 + 0x70) = 0;
  *(undefined1 *)(param_1 + 0x74) = 0;
  *(undefined4 *)(param_1 + 0x80) = 0;
  *(int *)(param_1 + 0x78) = iVar2 + 1;
  return;
}

// ==== Framework::CSoundManager::NumPlaying() const
// vaddr 0x1e98988 | ghidra 0x1f98988 | size 8 | symbol _ZNK9Framework13CSoundManager10NumPlayingEv | lib libSOA-3.7.0.so | 2026-10-08
undefined4 _ZNK9Framework13CSoundManager10NumPlayingEv(long param_1)

{
  return *(undefined4 *)(param_1 + 0x70);
}

// ==== Framework::CSoundManager::SearchBlank() const
// vaddr 0x1e98990 | ghidra 0x1f98990 | size 160 | symbol _ZNK9Framework13CSoundManager11SearchBlankEv | lib libSOA-3.7.0.so | 2026-10-08
ulong _ZNK9Framework13CSoundManager11SearchBlankEv(long param_1)

{
  undefined *puVar1;
  long *plVar2;
  long lVar3;
  ulong uVar4;
  ulong uVar5;
  
  plVar2 = *(long **)(param_1 + 0x60);
  if (plVar2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965bfc/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Sound.cpp"*/,0x28a,&UNK_027ee29f/*"m_pElements is null."*/);
    plVar2 = *(long **)(param_1 + 0x60);
  }
  lVar3 = (**(code **)(*plVar2 + 0x20))();
  puVar1 = PTR__ZN9Framework6CSound14iInvalidHandleE_02cc4340;
  if (lVar3 != 0) {
    uVar5 = 0;
    do {
      lVar3 = (**(code **)(**(long **)(param_1 + 0x60) + 0x28))(*(long **)(param_1 + 0x60),uVar5);
      if (*(long *)(lVar3 + 8) == *(long *)puVar1) {
        return uVar5;
      }
      uVar5 = (ulong)((int)uVar5 + 1);
      uVar4 = (**(code **)(**(long **)(param_1 + 0x60) + 0x20))();
    } while (uVar5 < uVar4);
  }
  return 0xffffffff;
}

// ==== Framework::CSoundManager::Search(unsigned long) const
// vaddr 0x1e98a30 | ghidra 0x1f98a30 | size 152 | symbol _ZNK9Framework13CSoundManager6SearchEm | lib libSOA-3.7.0.so | 2026-10-08
ulong _ZNK9Framework13CSoundManager6SearchEm(long param_1,long param_2)

{
  long *plVar1;
  long lVar2;
  ulong uVar3;
  ulong uVar4;
  
  plVar1 = *(long **)(param_1 + 0x60);
  if (plVar1 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965bfc/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Sound.cpp"*/,0x297,&UNK_027ee29f/*"m_pElements is null."*/);
    plVar1 = *(long **)(param_1 + 0x60);
  }
  lVar2 = (**(code **)(*plVar1 + 0x20))();
  if (lVar2 != 0) {
    uVar4 = 0;
    do {
      lVar2 = (**(code **)(**(long **)(param_1 + 0x60) + 0x28))(*(long **)(param_1 + 0x60),uVar4);
      if (*(long *)(lVar2 + 8) == param_2) {
        return uVar4;
      }
      uVar4 = (ulong)((int)uVar4 + 1);
      uVar3 = (**(code **)(**(long **)(param_1 + 0x60) + 0x20))();
    } while (uVar4 < uVar3);
  }
  return 0xffffffff;
}

// ==== Framework::CSoundManager::NewHandle()
// vaddr 0x1e98ac8 | ghidra 0x1f98ac8 | size 20 | symbol _ZN9Framework13CSoundManager9NewHandleEv | lib libSOA-3.7.0.so | 2026-10-08
int _ZN9Framework13CSoundManager9NewHandleEv(long param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x78);
  *(int *)(param_1 + 0x78) = iVar1 + 1;
  return iVar1;
}

// ==== Framework::CSoundManager::StopAll()
// vaddr 0x1e98adc | ghidra 0x1f98adc | size 376 | symbol _ZN9Framework13CSoundManager7StopAllEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN9Framework13CSoundManager7StopAllEv(long param_1)

{
  bool bVar1;
  undefined *puVar2;
  undefined *puVar3;
  ulong uVar4;
  long *plVar5;
  long lVar6;
  long lVar7;
  long lVar8;
  ulong uVar9;
  
  lVar8 = *(long *)(param_1 + 0x68);
  if (lVar8 != 0) {
    uVar4 = Framework::CMutex::IsInitialized() const(lVar8);
    if ((uVar4 & 1) == 0) {
      Framework::CMutex::Initialize()(lVar8);
    }
    Framework::CMutex::Lock()(lVar8);
  }
  plVar5 = *(long **)(param_1 + 0x60);
  if (plVar5 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965bfc/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Sound.cpp"*/,0x2b3,&UNK_027ee29f/*"m_pElements is null."*/);
    plVar5 = *(long **)(param_1 + 0x60);
  }
  lVar6 = (**(code **)(*plVar5 + 0x20))();
  puVar3 = PTR__ZN9Framework6CSound14iInvalidHandleE_02cc4340;
  puVar2 = PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50;
  if (lVar6 != 0) {
    uVar4 = 0;
    uVar9 = 1;
    do {
      lVar6 = (**(code **)(**(long **)(param_1 + 0x60) + 0x28))(*(long **)(param_1 + 0x60),uVar4);
      if ((*(long *)(lVar6 + 8) != *(long *)puVar3) &&
         (lVar6 = (**(code **)(**(long **)(param_1 + 0x60) + 0x28))
                            (*(long **)(param_1 + 0x60),uVar4),
         *(long *)(lVar6 + 8) != *(long *)puVar3)) {
        lVar7 = *(long *)(lVar6 + 0x10);
        if ((*(byte *)(lVar7 + 0x1f2) & 1) == 0) {
          if (((*(uint *)(lVar7 + 0x1e8) & 1) == 0) && ((*(uint *)(lVar7 + 0x1e8) >> 1 & 1) == 0)) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965bfc/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Sound.cpp"*/,0x1b1,&UNK_02965d24/*"Illegal sound type.(%08x)"*/);
          }
          else {
            Aska::SoundManager::StopSound(Aska::SoundObject*, unsigned int)(*(undefined8 *)puVar2,lVar7,10);
          }
        }
        *(undefined1 *)(lVar6 + 0x18) = 0;
      }
      uVar4 = (**(code **)(**(long **)(param_1 + 0x60) + 0x20))();
      bVar1 = uVar9 < uVar4;
      uVar4 = uVar9;
      uVar9 = (ulong)((int)uVar9 + 1);
    } while (bVar1);
  }
  if (lVar8 != 0) {
    (*(code *)PTR__ZN9Framework6CMutex6UnlockEv_02cb3f98)(lVar8);
    return;
  }
  return;
}

// ==== Framework::CSoundManager::StopSE(float)
// vaddr 0x1e98c54 | ghidra 0x1f98c54 | size 304 | symbol _ZN9Framework13CSoundManager6StopSEEf | lib libSOA-3.7.0.so | 2026-10-08
void _ZN9Framework13CSoundManager6StopSEEf(undefined8 param_1,long param_2)

{
  bool bVar1;
  undefined *puVar2;
  ulong uVar3;
  long *plVar4;
  long lVar5;
  long lVar6;
  ulong uVar7;
  
  lVar6 = *(long *)(param_2 + 0x68);
  if (lVar6 != 0) {
    uVar3 = Framework::CMutex::IsInitialized() const(lVar6);
    if ((uVar3 & 1) == 0) {
      Framework::CMutex::Initialize()(lVar6);
    }
    Framework::CMutex::Lock()(lVar6);
  }
  plVar4 = *(long **)(param_2 + 0x60);
  if (plVar4 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965bfc/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Sound.cpp"*/,0x2c1,&UNK_027ee29f/*"m_pElements is null."*/);
    plVar4 = *(long **)(param_2 + 0x60);
  }
  lVar5 = (**(code **)(*plVar4 + 0x20))();
  puVar2 = PTR__ZN9Framework6CSound14iInvalidHandleE_02cc4340;
  if (lVar5 != 0) {
    uVar3 = 0;
    uVar7 = 1;
    do {
      lVar5 = (**(code **)(**(long **)(param_2 + 0x60) + 0x28))(*(long **)(param_2 + 0x60),uVar3);
      if ((*(long *)(lVar5 + 8) != *(long *)puVar2) &&
         (lVar5 = (**(code **)(**(long **)(param_2 + 0x60) + 0x28))
                            (*(long **)(param_2 + 0x60),uVar3),
         (*(byte *)(*(long *)(lVar5 + 0x10) + 0x1e8) & 1) != 0)) {
        (**(code **)(**(long **)(param_2 + 0x60) + 0x28))(*(long **)(param_2 + 0x60),uVar3);
        Framework::CSound::CElement::SendStopRequest(float)(param_1);
      }
      uVar3 = (**(code **)(**(long **)(param_2 + 0x60) + 0x20))();
      bVar1 = uVar7 < uVar3;
      uVar3 = uVar7;
      uVar7 = (ulong)((int)uVar7 + 1);
    } while (bVar1);
  }
  if (lVar6 != 0) {
    (*(code *)PTR__ZN9Framework6CMutex6UnlockEv_02cb3f98)(lVar6);
    return;
  }
  return;
}

// ==== Framework::CSoundManager::PauseAll(float)
// vaddr 0x1e98d84 | ghidra 0x1f98d84 | size 624 | symbol _ZN9Framework13CSoundManager8PauseAllEf | lib libSOA-3.7.0.so | 2026-10-08
void _ZN9Framework13CSoundManager8PauseAllEf(float param_1,long param_2)

{
  bool bVar1;
  undefined *puVar2;
  undefined *puVar3;
  ulong uVar4;
  long *plVar5;
  long lVar6;
  long lVar7;
  ulong uVar8;
  
  lVar7 = *(long *)(param_2 + 0x68);
  if (lVar7 != 0) {
    uVar4 = Framework::CMutex::IsInitialized() const(lVar7);
    if ((uVar4 & 1) == 0) {
      Framework::CMutex::Initialize()(lVar7);
    }
    Framework::CMutex::Lock()(lVar7);
  }
  plVar5 = *(long **)(param_2 + 0x60);
  if (plVar5 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965bfc/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Sound.cpp"*/,0x2d4,&UNK_027ee29f/*"m_pElements is null."*/);
    plVar5 = *(long **)(param_2 + 0x60);
  }
  lVar6 = (**(code **)(*plVar5 + 0x20))();
  puVar3 = PTR__ZN9Framework6CSound14iInvalidHandleE_02cc4340;
  puVar2 = PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50;
  if (lVar6 != 0) {
    if (0.0 <= param_1) {
      uVar4 = 0;
      uVar8 = 1;
      do {
        lVar6 = (**(code **)(**(long **)(param_2 + 0x60) + 0x28))(*(long **)(param_2 + 0x60),uVar4);
        if (((*(long *)(lVar6 + 8) != *(long *)puVar3) &&
            (lVar6 = (**(code **)(**(long **)(param_2 + 0x60) + 0x28))
                               (*(long **)(param_2 + 0x60),uVar4),
            *(long *)(lVar6 + 8) != *(long *)puVar3)) &&
           ((*(byte *)(*(long *)(lVar6 + 0x10) + 0x1f2) & 1) == 0)) {
          if ((*(uint *)(*(long *)(lVar6 + 0x10) + 0x1e8) & 3) == 0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965bfc/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Sound.cpp"*/,0x1cf,&UNK_02965d24/*"Illegal sound type.(%08x)"*/);
          }
          else {
            Aska::SoundManager::PauseSound(Aska::SoundObject*)(*(undefined8 *)puVar2);
          }
        }
        uVar4 = (**(code **)(**(long **)(param_2 + 0x60) + 0x20))();
        bVar1 = uVar8 < uVar4;
        uVar4 = uVar8;
        uVar8 = (ulong)((int)uVar8 + 1);
      } while (bVar1);
    }
    else {
      uVar4 = 0;
      uVar8 = 1;
      do {
        lVar6 = (**(code **)(**(long **)(param_2 + 0x60) + 0x28))(*(long **)(param_2 + 0x60),uVar4);
        if (*(long *)(lVar6 + 8) != *(long *)puVar3) {
          lVar6 = (**(code **)(**(long **)(param_2 + 0x60) + 0x28))
                            (*(long **)(param_2 + 0x60),uVar4);
          Framework::gDoAssert(char const*, int, char const*, ...)((double)param_1,&UNK_02965bfc/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Sound.cpp"*/,0x1ba,&UNK_02965cf9/*"The arguments 'aFadeTime' less than 0.(%f)"*/);
          if ((*(long *)(lVar6 + 8) != *(long *)puVar3) &&
             ((*(byte *)(*(long *)(lVar6 + 0x10) + 0x1f2) & 1) == 0)) {
            if ((*(uint *)(*(long *)(lVar6 + 0x10) + 0x1e8) & 3) == 0) {
              Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965bfc/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Sound.cpp"*/,0x1cf,&UNK_02965d24/*"Illegal sound type.(%08x)"*/);
            }
            else {
              Aska::SoundManager::PauseSound(Aska::SoundObject*)(*(undefined8 *)puVar2);
            }
          }
        }
        uVar4 = (**(code **)(**(long **)(param_2 + 0x60) + 0x20))();
        bVar1 = uVar8 < uVar4;
        uVar4 = uVar8;
        uVar8 = (ulong)((int)uVar8 + 1);
      } while (bVar1);
    }
  }
  if (lVar7 != 0) {
    (*(code *)PTR__ZN9Framework6CMutex6UnlockEv_02cb3f98)(lVar7);
    return;
  }
  return;
}

// ==== Framework::CSoundManager::ResumeAll(float)
// vaddr 0x1e98ff4 | ghidra 0x1f98ff4 | size 624 | symbol _ZN9Framework13CSoundManager9ResumeAllEf | lib libSOA-3.7.0.so | 2026-10-08
void _ZN9Framework13CSoundManager9ResumeAllEf(float param_1,long param_2)

{
  bool bVar1;
  undefined *puVar2;
  undefined *puVar3;
  ulong uVar4;
  long *plVar5;
  long lVar6;
  long lVar7;
  ulong uVar8;
  
  lVar7 = *(long *)(param_2 + 0x68);
  if (lVar7 != 0) {
    uVar4 = Framework::CMutex::IsInitialized() const(lVar7);
    if ((uVar4 & 1) == 0) {
      Framework::CMutex::Initialize()(lVar7);
    }
    Framework::CMutex::Lock()(lVar7);
  }
  plVar5 = *(long **)(param_2 + 0x60);
  if (plVar5 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965bfc/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Sound.cpp"*/,0x2e3,&UNK_027ee29f/*"m_pElements is null."*/);
    plVar5 = *(long **)(param_2 + 0x60);
  }
  lVar6 = (**(code **)(*plVar5 + 0x20))();
  puVar3 = PTR__ZN9Framework6CSound14iInvalidHandleE_02cc4340;
  puVar2 = PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50;
  if (lVar6 != 0) {
    if (0.0 <= param_1) {
      uVar4 = 0;
      uVar8 = 1;
      do {
        lVar6 = (**(code **)(**(long **)(param_2 + 0x60) + 0x28))(*(long **)(param_2 + 0x60),uVar4);
        if (((*(long *)(lVar6 + 8) != *(long *)puVar3) &&
            (lVar6 = (**(code **)(**(long **)(param_2 + 0x60) + 0x28))
                               (*(long **)(param_2 + 0x60),uVar4),
            *(long *)(lVar6 + 8) != *(long *)puVar3)) &&
           ((*(byte *)(*(long *)(lVar6 + 0x10) + 0x1f2) & 1) == 0)) {
          if ((*(uint *)(*(long *)(lVar6 + 0x10) + 0x1e8) & 3) == 0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965bfc/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Sound.cpp"*/,0x1cf,&UNK_02965d24/*"Illegal sound type.(%08x)"*/);
          }
          else {
            Aska::SoundManager::ResumeSound(Aska::SoundObject*)(*(undefined8 *)puVar2);
          }
        }
        uVar4 = (**(code **)(**(long **)(param_2 + 0x60) + 0x20))();
        bVar1 = uVar8 < uVar4;
        uVar4 = uVar8;
        uVar8 = (ulong)((int)uVar8 + 1);
      } while (bVar1);
    }
    else {
      uVar4 = 0;
      uVar8 = 1;
      do {
        lVar6 = (**(code **)(**(long **)(param_2 + 0x60) + 0x28))(*(long **)(param_2 + 0x60),uVar4);
        if (*(long *)(lVar6 + 8) != *(long *)puVar3) {
          lVar6 = (**(code **)(**(long **)(param_2 + 0x60) + 0x28))
                            (*(long **)(param_2 + 0x60),uVar4);
          Framework::gDoAssert(char const*, int, char const*, ...)((double)param_1,&UNK_02965bfc/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Sound.cpp"*/,0x1ba,&UNK_02965cf9/*"The arguments 'aFadeTime' less than 0.(%f)"*/);
          if ((*(long *)(lVar6 + 8) != *(long *)puVar3) &&
             ((*(byte *)(*(long *)(lVar6 + 0x10) + 0x1f2) & 1) == 0)) {
            if ((*(uint *)(*(long *)(lVar6 + 0x10) + 0x1e8) & 3) == 0) {
              Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965bfc/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Sound.cpp"*/,0x1cf,&UNK_02965d24/*"Illegal sound type.(%08x)"*/);
            }
            else {
              Aska::SoundManager::ResumeSound(Aska::SoundObject*)(*(undefined8 *)puVar2);
            }
          }
        }
        uVar4 = (**(code **)(**(long **)(param_2 + 0x60) + 0x20))();
        bVar1 = uVar8 < uVar4;
        uVar4 = uVar8;
        uVar8 = (ulong)((int)uVar8 + 1);
      } while (bVar1);
    }
  }
  if (lVar7 != 0) {
    (*(code *)PTR__ZN9Framework6CMutex6UnlockEv_02cb3f98)(lVar7);
    return;
  }
  return;
}

// ==== Framework::CSoundManager::PreProgress()
// vaddr 0x1e99264 | ghidra 0x1f99264 | size 284 | symbol _ZN9Framework13CSoundManager11PreProgressEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN9Framework13CSoundManager11PreProgressEv(long param_1)

{
  bool bVar1;
  undefined *puVar2;
  ulong uVar3;
  long lVar4;
  long lVar5;
  ulong uVar6;
  
  lVar5 = *(long *)(param_1 + 0x68);
  if (lVar5 != 0) {
    uVar3 = Framework::CMutex::IsInitialized() const(lVar5);
    if ((uVar3 & 1) == 0) {
      Framework::CMutex::Initialize()(lVar5);
    }
    Framework::CMutex::Lock()(lVar5);
  }
  if (*(long *)(param_1 + 0x60) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965bfc/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Sound.cpp"*/,0x2f6,&UNK_027ee29f/*"m_pElements is null."*/);
    lVar4 = *(long *)(param_1 + 8);
  }
  else {
    lVar4 = *(long *)(param_1 + 8);
  }
  if (lVar4 == 0) {
    Framework::CTimeElementContainer::FrameworkDT()();
  }
  else {
    Framework::CTimeElement::DT() const(param_1);
  }
  lVar4 = (**(code **)(**(long **)(param_1 + 0x60) + 0x20))();
  puVar2 = PTR__ZN9Framework6CSound14iInvalidHandleE_02cc4340;
  if (lVar4 != 0) {
    uVar3 = 0;
    uVar6 = 1;
    do {
      lVar4 = (**(code **)(**(long **)(param_1 + 0x60) + 0x28))(*(long **)(param_1 + 0x60),uVar3);
      if (*(long *)(lVar4 + 8) != *(long *)puVar2) {
        lVar4 = (**(code **)(**(long **)(param_1 + 0x60) + 0x28))(*(long **)(param_1 + 0x60),uVar3);
        *(undefined1 *)(lVar4 + 0x19) = 0;
      }
      uVar3 = (**(code **)(**(long **)(param_1 + 0x60) + 0x20))();
      bVar1 = uVar6 < uVar3;
      uVar3 = uVar6;
      uVar6 = (ulong)((int)uVar6 + 1);
    } while (bVar1);
  }
  if (lVar5 == 0) {
    return;
  }
  (*(code *)PTR__ZN9Framework6CMutex6UnlockEv_02cb3f98)(lVar5);
  return;
}

// ==== Framework::CSoundManager::PostProgress()
// vaddr 0x1e99380 | ghidra 0x1f99380 | size 324 | symbol _ZN9Framework13CSoundManager12PostProgressEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN9Framework13CSoundManager12PostProgressEv(long param_1)

{
  bool bVar1;
  undefined *puVar2;
  ulong uVar3;
  long lVar4;
  long lVar5;
  ulong uVar6;
  undefined *puStack_38;
  
  lVar5 = *(long *)(param_1 + 0x68);
  if (lVar5 != 0) {
    uVar3 = Framework::CMutex::IsInitialized() const(lVar5);
    if ((uVar3 & 1) == 0) {
      Framework::CMutex::Initialize()(lVar5);
    }
    Framework::CMutex::Lock()(lVar5);
  }
  if (*(long *)(param_1 + 0x60) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965bfc/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Sound.cpp"*/,0x305,&UNK_027ee29f/*"m_pElements is null."*/);
  }
  *(undefined4 *)(param_1 + 0x70) = 0;
  if (*(long *)(param_1 + 8) == 0) {
    Framework::CTimeElementContainer::FrameworkDT()();
  }
  else {
    Framework::CTimeElement::DT() const(param_1);
  }
  lVar4 = (**(code **)(**(long **)(param_1 + 0x60) + 0x20))();
  puVar2 = PTR__ZN9Framework6CSound14iInvalidHandleE_02cc4340;
  if (lVar4 != 0) {
    uVar3 = 0;
    uVar6 = 1;
    do {
      lVar4 = (**(code **)(**(long **)(param_1 + 0x60) + 0x28))(*(long **)(param_1 + 0x60),uVar3);
      if (*(long *)(lVar4 + 8) != *(long *)puVar2) {
        (**(code **)(**(long **)(param_1 + 0x60) + 0x28))(*(long **)(param_1 + 0x60),uVar3);
        Framework::CSound::CElement::PostProgress(float)();
        *(int *)(param_1 + 0x70) = *(int *)(param_1 + 0x70) + 1;
      }
      uVar3 = (**(code **)(**(long **)(param_1 + 0x60) + 0x20))();
      bVar1 = uVar6 < uVar3;
      uVar3 = uVar6;
      uVar6 = (ulong)((int)uVar6 + 1);
    } while (bVar1);
  }
  if (lVar5 != 0) {
    Framework::CMutex::Unlock()(lVar5);
  }
  puStack_38 = &UNK_02bab058;
  if (*(char *)(param_1 + 0x7c) != '\0') {
    Framework::CSoundManager::FunctorAllPlayingElements(Framework::ICallback&)(param_1,&puStack_38);
  }
  return;
}

// ==== Framework::CSoundManager::FunctorAllPlayingElements(Framework::ICallback&)
// vaddr 0x1e994c4 | ghidra 0x1f994c4 | size 288 | symbol _ZN9Framework13CSoundManager25FunctorAllPlayingElementsERNS_9ICallbackE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN9Framework13CSoundManager25FunctorAllPlayingElementsERNS_9ICallbackE
               (long param_1,undefined8 *param_2)

{
  bool bVar1;
  undefined *puVar2;
  ulong uVar3;
  long *plVar4;
  long lVar5;
  undefined8 uVar6;
  long lVar7;
  ulong uVar8;
  
  lVar7 = *(long *)(param_1 + 0x68);
  if (lVar7 != 0) {
    uVar3 = Framework::CMutex::IsInitialized() const(lVar7);
    if ((uVar3 & 1) == 0) {
      Framework::CMutex::Initialize()(lVar7);
    }
    Framework::CMutex::Lock()(lVar7);
  }
  plVar4 = *(long **)(param_1 + 0x60);
  if (plVar4 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965bfc/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Sound.cpp"*/,0x496,&UNK_027ee29f/*"m_pElements is null."*/);
    plVar4 = *(long **)(param_1 + 0x60);
  }
  lVar5 = (**(code **)(*plVar4 + 0x20))();
  puVar2 = PTR__ZN9Framework6CSound14iInvalidHandleE_02cc4340;
  if (lVar5 != 0) {
    uVar3 = 0;
    uVar8 = 1;
    do {
      lVar5 = (**(code **)(**(long **)(param_1 + 0x60) + 0x28))(*(long **)(param_1 + 0x60),uVar3);
      if (*(long *)(lVar5 + 8) != *(long *)puVar2) {
        uVar6 = (**(code **)(**(long **)(param_1 + 0x60) + 0x28))(*(long **)(param_1 + 0x60),uVar3);
        (**(code **)*param_2)(param_2,0,uVar6);
      }
      uVar3 = (**(code **)(**(long **)(param_1 + 0x60) + 0x20))();
      bVar1 = uVar8 < uVar3;
      uVar3 = uVar8;
      uVar8 = (ulong)((int)uVar8 + 1);
    } while (bVar1);
  }
  if (lVar7 != 0) {
    (*(code *)PTR__ZN9Framework6CMutex6UnlockEv_02cb3f98)(lVar7);
    return;
  }
  return;
}

// ==== Framework::CSoundManager::EnableIgnorePlayRequest(bool)
// vaddr 0x1e995e4 | ghidra 0x1f995e4 | size 12 | symbol _ZN9Framework13CSoundManager23EnableIgnorePlayRequestEb | lib libSOA-3.7.0.so | 2026-10-08
void _ZN9Framework13CSoundManager23EnableIgnorePlayRequestEb(long param_1,byte param_2)

{
  *(byte *)(param_1 + 0x74) = param_2 & 1;
  return;
}

// ==== Framework::CSoundManager::PlayMemorySE(void const*, unsigned long, Framework::CSound::tArguments const&, char const*)
// vaddr 0x1e995f0 | ghidra 0x1f995f0 | size 856 | symbol _ZN9Framework13CSoundManager12PlayMemorySEEPKvmRKNS_6CSound10tArgumentsEPKc | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN9Framework13CSoundManager12PlayMemorySEEPKvmRKNS_6CSound10tArgumentsEPKc
          (long param_1,undefined8 param_2,undefined8 param_3,long *param_4,undefined8 param_5)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  char cVar4;
  undefined *puVar5;
  ulong uVar6;
  long *plVar7;
  long lVar8;
  ulong uVar9;
  long lVar10;
  long lVar11;
  undefined8 uVar12;
  int iVar13;
  undefined8 uVar14;
  long *plStack_f0;
  long lStack_e8;
  long lStack_e0;
  long lStack_d8;
  long lStack_d0;
  long lStack_c8;
  undefined4 uStack_c0;
  undefined4 uStack_bc;
  undefined1 uStack_b8;
  char cStack_b0;
  undefined4 uStack_a0;
  undefined4 uStack_9c;
  undefined4 uStack_98;
  undefined4 uStack_94;
  undefined8 uStack_90;
  undefined4 uStack_74;
  
  lVar11 = *(long *)(param_1 + 0x68);
  if (lVar11 != 0) {
    uVar6 = Framework::CMutex::IsInitialized() const(lVar11);
    if ((uVar6 & 1) == 0) {
      Framework::CMutex::Initialize()(lVar11);
    }
    Framework::CMutex::Lock()(lVar11);
  }
  if (*(long *)(param_1 + 0x60) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965bfc/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Sound.cpp"*/,0x352,&UNK_027ee29f/*"m_pElements is null."*/);
  }
  puVar5 = PTR__ZN9Framework6CSound14iInvalidHandleE_02cc4340;
  uVar12 = *(undefined8 *)PTR__ZN9Framework6CSound14iInvalidHandleE_02cc4340;
  if (*(char *)(param_1 + 0x74) == '\0') {
    plVar7 = *(long **)(param_1 + 0x60);
    if (plVar7 == (long *)0x0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965bfc/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Sound.cpp"*/,0x28a,&UNK_027ee29f/*"m_pElements is null."*/);
      plVar7 = *(long **)(param_1 + 0x60);
    }
    lVar8 = (**(code **)(*plVar7 + 0x20))();
    if (lVar8 != 0) {
      uVar6 = 0;
      do {
        lVar8 = (**(code **)(**(long **)(param_1 + 0x60) + 0x28))(*(long **)(param_1 + 0x60),uVar6);
        iVar13 = (int)uVar6;
        if (*(long *)(lVar8 + 8) == *(long *)puVar5) {
          if (-1 < iVar13) {
            lStack_c8 = param_4[5];
            lStack_d0 = param_4[4];
            lStack_d8 = param_4[3];
            lStack_e0 = param_4[2];
            lStack_e8 = param_4[1];
            plStack_f0 = (long *)*param_4;
            uStack_b8 = (undefined1)param_4[7];
            _uStack_c0 = CONCAT44(*(undefined4 *)((long)param_4 + 0x34),(int)param_4[6]);
            cVar4 = (char)param_4[8];
            uVar1 = (undefined4)param_4[10];
            uVar3 = *(undefined4 *)((long)param_4 + 0x54);
            uVar2 = (undefined4)param_4[0xb];
            uStack_94 = *(undefined4 *)((long)param_4 + 0x5c);
            uStack_90 = param_4[0xc];
            uVar14 = *(undefined8 *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50;
            cStack_b0 = cVar4;
            uStack_a0 = uVar1;
            uStack_9c = uVar3;
            uStack_98 = uVar2;
            if (plStack_f0 != (long *)0x0) {
              Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965bfc/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Sound.cpp"*/,0x36c,&UNK_02965db4/*"arguments.pEmitter isn't null"*/);
            }
            plStack_f0 = (long *)0x0;
            if (cVar4 != '\0') {
              lVar8 = (**(code **)(**(long **)(param_1 + 0x60) + 0x28))
                                (*(long **)(param_1 + 0x60),(long)iVar13);
              plVar7 = *(long **)(lVar8 + 0x20);
              if (plVar7 == (long *)0x0) {
                Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965bfc/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Sound.cpp"*/,0x11d,&UNK_02965c9a/*"m_pHierarchicalObject is null."*/);
                plVar7 = *(long **)(lVar8 + 0x20);
              }
              (**(code **)(*plVar7 + 200))(uVar1,uVar3,uVar2,plVar7);
              (**(code **)(*plVar7 + 0xa8))(plVar7);
              plStack_f0 = plVar7;
            }
            lVar8 = Aska::SoundManager::PlaySound(unsigned long, bool, unsigned int, unsigned int, Aska::DirectPlaybackSettings const*)(uVar14,param_2,0,uStack_bc,5,&plStack_f0);
            if (lVar8 != 0) {
              *(int *)(param_1 + 0x78) = *(int *)(param_1 + 0x78) + 1;
              uVar12 = Framework::CHandleManager_Base::MountAdditionalInformation(unsigned int, unsigned int)(*(undefined4 *)(param_1 + 0x48));
              lVar10 = (**(code **)(**(long **)(param_1 + 0x60) + 0x28))
                                 (*(long **)(param_1 + 0x60),(long)iVar13);
              if (*(long *)(lVar10 + 8) != *(long *)puVar5) {
                Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965bfc/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Sound.cpp"*/,0x123,&UNK_02965cb9/*"m_Handle == iInvalidHandle is null."*/);
              }
              *(undefined8 *)(lVar10 + 8) = uVar12;
              if (*(long *)(lVar10 + 0x10) != 0) {
                Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965bfc/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Sound.cpp"*/,0x125,&UNK_02965c4d/*"m_pAskaSoundObject isn't null.(%08x)"*/);
              }
              *(long *)(lVar10 + 0x10) = lVar8;
              *(undefined1 *)(lVar10 + 0x18) = uStack_b8;
              *(undefined1 *)(lVar10 + 0x29) = 0;
              *(char *)(lVar10 + 0x28) = cStack_b0;
              if (cStack_b0 != '\0') {
                Aska::SoundObject::RequestSet(unsigned int, void const*)(lVar8,1,CONCAT44(uStack_74,(undefined4)uStack_90));
                Aska::SoundObject::RequestSet(unsigned int, void const*)(lVar8,2,CONCAT44(uStack_74,uStack_90._4_4_));
              }
              if (*(long *)
                   PTR__ZN9Framework10TSingletonINS_27CDebugWindow_SoundPreviewerEE11m_pInstanceE_02cb8f60
                  != 0) {
                Framework::CDebugWindow_SoundPreviewer::AddSELog(char const*)(*(long *)
                                 PTR__ZN9Framework10TSingletonINS_27CDebugWindow_SoundPreviewerEE11m_pInstanceE_02cb8f60
                                ,param_5);
                if (lVar11 == 0) {
                  return uVar12;
                }
                goto code_r0x01f99680;
              }
            }
          }
          break;
        }
        uVar6 = (ulong)(iVar13 + 1);
        uVar9 = (**(code **)(**(long **)(param_1 + 0x60) + 0x20))();
      } while (uVar6 < uVar9);
    }
  }
  if (lVar11 != 0) {
code_r0x01f99680:
    Framework::CMutex::Unlock()(lVar11);
  }
  return uVar12;
}

// ==== Framework::CSoundManager::PlayFileStreamImageSE(void const*, unsigned int, Framework::CSound::tArguments const&)
// vaddr 0x1e99948 | ghidra 0x1f99948 | size 172 | symbol _ZN9Framework13CSoundManager21PlayFileStreamImageSEEPKvjRKNS_6CSound10tArgumentsE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN9Framework13CSoundManager21PlayFileStreamImageSEEPKvjRKNS_6CSound10tArgumentsE
               (undefined8 param_1,int *param_2,uint param_3)

{
  if ((*param_2 != 0x46534900) || (0x20130304 < (uint)param_2[1])) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965bfc/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Sound.cpp"*/,0x3ac,&UNK_02965dd2/*"pImage->IsValid() is null."*/);
  }
  if ((uint)param_2[2] <= param_3) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02960f2f/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Tools\MakeFileStream/FileStream_Image.h"*/,0xf1,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,param_3);
  }
  (*(code *)PTR__ZN9Framework13CSoundManager12PlayMemorySEEPKvmRKNS_6CSound10tArgumentsEPKc_02ca15c8
  )(param_1,(ulong)(uint)param_2[(ulong)param_3 * 4 + 5] + (long)param_2);
  return;
}

// ==== Framework::CSoundManager::PlayFileStreamImageSEByName(void const*, char const*, Framework::CSound::tArguments const&)
// vaddr 0x1e999f4 | ghidra 0x1f999f4 | size 248 | symbol _ZN9Framework13CSoundManager27PlayFileStreamImageSEByNameEPKvPKcRKNS_6CSound10tArgumentsE | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN9Framework13CSoundManager27PlayFileStreamImageSEByNameEPKvPKcRKNS_6CSound10tArgumentsE
          (undefined8 param_1,int *param_2,undefined8 param_3)

{
  uint uVar1;
  undefined8 uVar2;
  
  if ((*param_2 != 0x46534900) || (0x20130304 < (uint)param_2[1])) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965bfc/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Sound.cpp"*/,0x3b5,&UNK_02965dd2/*"pImage->IsValid() is null."*/);
  }
  uVar1 = Framework::FileStream::tImage::Find(char const*) const(param_2,param_3);
  if (-1 < (int)uVar1) {
    if ((uint)param_2[2] <= uVar1) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02960f2f/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Tools\MakeFileStream/FileStream_Image.h"*/,0xf1,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,uVar1);
    }
    uVar2 = (*(code *)
              PTR__ZN9Framework13CSoundManager12PlayMemorySEEPKvmRKNS_6CSound10tArgumentsEPKc_02ca15c8
            )(param_1,(ulong)(uint)param_2[(ulong)uVar1 * 4 + 5] + (long)param_2);
    return uVar2;
  }
  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965bfc/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Sound.cpp"*/,0x3b7,&UNK_02965ded,param_3);
  return *(undefined8 *)PTR__ZN9Framework6CSound14iInvalidHandleE_02cc4340;
}

// ==== Framework::CSoundManager::PlayBGM(unsigned int, Framework::CSound::tArguments const&)
// vaddr 0x1e99bfc | ghidra 0x1f99bfc | size 584 | symbol _ZN9Framework13CSoundManager7PlayBGMEjRKNS_6CSound10tArgumentsE | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN9Framework13CSoundManager7PlayBGMEjRKNS_6CSound10tArgumentsE
          (long param_1,undefined4 param_2,long *param_3)

{
  undefined *puVar1;
  ulong uVar2;
  long *plVar3;
  long lVar4;
  ulong uVar5;
  long lVar6;
  undefined8 uVar7;
  long lVar8;
  undefined8 uVar9;
  int iVar10;
  
  lVar8 = *(long *)(param_1 + 0x68);
  if (lVar8 != 0) {
    uVar2 = Framework::CMutex::IsInitialized() const(lVar8);
    if ((uVar2 & 1) == 0) {
      Framework::CMutex::Initialize()(lVar8);
    }
    Framework::CMutex::Lock()(lVar8);
  }
  if (*(long *)(param_1 + 0x60) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965bfc/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Sound.cpp"*/,0x3c5,&UNK_027ee29f/*"m_pElements is null."*/);
  }
  puVar1 = PTR__ZN9Framework6CSound14iInvalidHandleE_02cc4340;
  uVar9 = *(undefined8 *)PTR__ZN9Framework6CSound14iInvalidHandleE_02cc4340;
  if (*(char *)(param_1 + 0x74) == '\0') {
    plVar3 = *(long **)(param_1 + 0x60);
    if (plVar3 == (long *)0x0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965bfc/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Sound.cpp"*/,0x28a,&UNK_027ee29f/*"m_pElements is null."*/);
      plVar3 = *(long **)(param_1 + 0x60);
    }
    lVar4 = (**(code **)(*plVar3 + 0x20))();
    if (lVar4 != 0) {
      uVar2 = 0;
      do {
        lVar4 = (**(code **)(**(long **)(param_1 + 0x60) + 0x28))(*(long **)(param_1 + 0x60),uVar2);
        iVar10 = (int)uVar2;
        if (*(long *)(lVar4 + 8) == *(long *)puVar1) {
          if (-1 < iVar10) {
            uVar7 = *(undefined8 *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50;
            if (*param_3 != 0) {
              Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965bfc/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Sound.cpp"*/,0x3d8,&UNK_02965db4/*"arguments.pEmitter isn't null"*/);
            }
            if ((char)param_3[8] != '\0') {
              Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965bfc/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Sound.cpp"*/,0x3d9,&UNK_02965e07/*"arguments.m_3D is enabled."*/);
            }
            lVar4 = Aska::SoundManager::PlaySound(unsigned long, bool, unsigned int, unsigned int, Aska::DirectPlaybackSettings const*)(uVar7,param_2,0,*(undefined4 *)((long)param_3 + 0x34),2,param_3)
            ;
            if (lVar4 != 0) {
              *(int *)(param_1 + 0x78) = *(int *)(param_1 + 0x78) + 1;
              uVar9 = Framework::CHandleManager_Base::MountAdditionalInformation(unsigned int, unsigned int)(*(undefined4 *)(param_1 + 0x48));
              lVar6 = (**(code **)(**(long **)(param_1 + 0x60) + 0x28))
                                (*(long **)(param_1 + 0x60),(long)iVar10);
              if (*(long *)(lVar6 + 8) != *(long *)puVar1) {
                Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965bfc/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Sound.cpp"*/,0x123,&UNK_02965cb9/*"m_Handle == iInvalidHandle is null."*/);
              }
              *(undefined8 *)(lVar6 + 8) = uVar9;
              if (*(long *)(lVar6 + 0x10) != 0) {
                Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965bfc/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Sound.cpp"*/,0x125,&UNK_02965c4d/*"m_pAskaSoundObject isn't null.(%08x)"*/);
              }
              *(long *)(lVar6 + 0x10) = lVar4;
              *(char *)(lVar6 + 0x18) = (char)param_3[7];
              lVar4 = param_3[8];
              *(undefined1 *)(lVar6 + 0x29) = 0;
              *(char *)(lVar6 + 0x28) = (char)lVar4;
            }
          }
          break;
        }
        uVar2 = (ulong)(iVar10 + 1);
        uVar5 = (**(code **)(**(long **)(param_1 + 0x60) + 0x20))();
      } while (uVar2 < uVar5);
    }
    lVar4 = *(long *)
             PTR__ZN9Framework10TSingletonINS_27CDebugWindow_SoundPreviewerEE11m_pInstanceE_02cb8f60
    ;
    if (lVar4 != 0) {
      uVar7 = Framework::FileID::gpFileName(unsigned int)(param_2);
      Framework::CDebugWindow_SoundPreviewer::AddBGMLog(char const*)(lVar4,uVar7);
    }
  }
  if (lVar8 != 0) {
    Framework::CMutex::Unlock()(lVar8);
  }
  return uVar9;
}

// ==== Framework::CSoundManager::PlayBGM(char const*, Framework::CSound::tArguments const&)
// vaddr 0x1e99e44 | ghidra 0x1f99e44 | size 656 | symbol _ZN9Framework13CSoundManager7PlayBGMEPKcRKNS_6CSound10tArgumentsE | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN9Framework13CSoundManager7PlayBGMEPKcRKNS_6CSound10tArgumentsE
          (long param_1,long param_2,long *param_3)

{
  undefined4 uVar1;
  undefined *puVar2;
  ulong uVar3;
  long *plVar4;
  long lVar5;
  ulong uVar6;
  long lVar7;
  long lVar8;
  long lVar9;
  undefined8 uVar10;
  int iVar11;
  
  if (param_2 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965bfc/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Sound.cpp"*/,0x3ff,&UNK_029655cd/*"apFileName is null."*/);
  }
  lVar9 = *(long *)(param_1 + 0x68);
  if (lVar9 != 0) {
    uVar3 = Framework::CMutex::IsInitialized() const(lVar9);
    if ((uVar3 & 1) == 0) {
      Framework::CMutex::Initialize()(lVar9);
    }
    Framework::CMutex::Lock()(lVar9);
  }
  if (*(long *)(param_1 + 0x60) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965bfc/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Sound.cpp"*/,0x403,&UNK_027ee29f/*"m_pElements is null."*/);
  }
  puVar2 = PTR__ZN9Framework6CSound14iInvalidHandleE_02cc4340;
  uVar10 = *(undefined8 *)PTR__ZN9Framework6CSound14iInvalidHandleE_02cc4340;
  if (*(char *)(param_1 + 0x74) == '\0') {
    plVar4 = *(long **)(param_1 + 0x60);
    if (plVar4 == (long *)0x0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965bfc/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Sound.cpp"*/,0x28a,&UNK_027ee29f/*"m_pElements is null."*/);
      plVar4 = *(long **)(param_1 + 0x60);
    }
    lVar5 = (**(code **)(*plVar4 + 0x20))();
    if (lVar5 != 0) {
      uVar3 = 0;
      do {
        lVar5 = (**(code **)(**(long **)(param_1 + 0x60) + 0x28))(*(long **)(param_1 + 0x60),uVar3);
        iVar11 = (int)uVar3;
        if (*(long *)(lVar5 + 8) == *(long *)puVar2) {
          if (-1 < iVar11) {
            lVar5 = *(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50;
            if (*param_3 != 0) {
              Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965bfc/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Sound.cpp"*/,0x416,&UNK_02965db4/*"arguments.pEmitter isn't null"*/);
            }
            if ((char)param_3[8] != '\0') {
              Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965bfc/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Sound.cpp"*/,0x417,&UNK_02965e07/*"arguments.m_3D is enabled."*/);
            }
            uVar1 = *(undefined4 *)((long)param_3 + 0x34);
            lVar7 = Aska::SoundServer::AcquireFilePathBuffer()(*(undefined8 *)(lVar5 + 0xe8));
            if (lVar7 != 0) {
              strcpy(lVar7,param_2);
              lVar8 = Aska::SoundManager::PlaySound(unsigned long, bool, unsigned int, unsigned int, Aska::DirectPlaybackSettings const*)(lVar5,lVar7,1,uVar1,2,param_3);
              if (lVar8 == 0) {
                Aska::SoundServer::ReleaseFilePathBuffer(char*)(*(undefined8 *)(lVar5 + 0xe8),lVar7);
              }
              else {
                *(int *)(param_1 + 0x78) = *(int *)(param_1 + 0x78) + 1;
                uVar10 = Framework::CHandleManager_Base::MountAdditionalInformation(unsigned int, unsigned int)(*(undefined4 *)(param_1 + 0x48));
                lVar5 = (**(code **)(**(long **)(param_1 + 0x60) + 0x28))
                                  (*(long **)(param_1 + 0x60),(long)iVar11);
                if (*(long *)(lVar5 + 8) != *(long *)puVar2) {
                  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965bfc/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Sound.cpp"*/,0x123,&UNK_02965cb9/*"m_Handle == iInvalidHandle is null."*/);
                }
                *(undefined8 *)(lVar5 + 8) = uVar10;
                if (*(long *)(lVar5 + 0x10) != 0) {
                  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965bfc/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Sound.cpp"*/,0x125,&UNK_02965c4d/*"m_pAskaSoundObject isn't null.(%08x)"*/);
                }
                *(long *)(lVar5 + 0x10) = lVar8;
                *(char *)(lVar5 + 0x18) = (char)param_3[7];
                lVar7 = param_3[8];
                *(undefined1 *)(lVar5 + 0x29) = 0;
                *(char *)(lVar5 + 0x28) = (char)lVar7;
              }
            }
          }
          break;
        }
        uVar3 = (ulong)(iVar11 + 1);
        uVar6 = (**(code **)(**(long **)(param_1 + 0x60) + 0x20))();
      } while (uVar3 < uVar6);
    }
    if (*(long *)
         PTR__ZN9Framework10TSingletonINS_27CDebugWindow_SoundPreviewerEE11m_pInstanceE_02cb8f60 !=
        0) {
      Framework::CDebugWindow_SoundPreviewer::AddBGMLog(char const*)(*(long *)
                       PTR__ZN9Framework10TSingletonINS_27CDebugWindow_SoundPreviewerEE11m_pInstanceE_02cb8f60
                      ,param_2);
    }
  }
  if (lVar9 != 0) {
    Framework::CMutex::Unlock()(lVar9);
  }
  return uVar10;
}

// ==== Framework::CSoundManager::IsPlaying(unsigned long) const
// vaddr 0x1e9a0d4 | ghidra 0x1f9a0d4 | size 244 | symbol _ZNK9Framework13CSoundManager9IsPlayingEm | lib libSOA-3.7.0.so | 2026-10-08
uint _ZNK9Framework13CSoundManager9IsPlayingEm(long param_1,long param_2)

{
  ulong uVar1;
  long *plVar2;
  long lVar3;
  ulong uVar4;
  long lVar5;
  uint uVar6;
  
  if (*(long *)PTR__ZN9Framework6CSound14iInvalidHandleE_02cc4340 == param_2) {
    uVar6 = 0;
  }
  else {
    lVar5 = *(long *)(param_1 + 0x68);
    if (lVar5 != 0) {
      uVar1 = Framework::CMutex::IsInitialized() const(lVar5);
      if ((uVar1 & 1) == 0) {
        Framework::CMutex::Initialize()(lVar5);
      }
      Framework::CMutex::Lock()(lVar5);
    }
    plVar2 = *(long **)(param_1 + 0x60);
    if (plVar2 == (long *)0x0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965bfc/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Sound.cpp"*/,0x297,&UNK_027ee29f/*"m_pElements is null."*/);
      plVar2 = *(long **)(param_1 + 0x60);
    }
    lVar3 = (**(code **)(*plVar2 + 0x20))();
    if (lVar3 != 0) {
      uVar1 = 0;
      do {
        lVar3 = (**(code **)(**(long **)(param_1 + 0x60) + 0x28))(*(long **)(param_1 + 0x60),uVar1);
        if (*(long *)(lVar3 + 8) == param_2) goto code_r0x01f9a1a0;
        uVar1 = (ulong)((int)uVar1 + 1);
        uVar4 = (**(code **)(**(long **)(param_1 + 0x60) + 0x20))();
      } while (uVar1 < uVar4);
    }
    uVar1 = 0xffffffff;
code_r0x01f9a1a0:
    uVar6 = (uint)(uVar1 >> 0x1f) ^ 1;
    if (lVar5 != 0) {
      Framework::CMutex::Unlock()(lVar5);
    }
  }
  return uVar6;
}

// ==== Framework::CSoundManager::Stop(unsigned long, float)
// vaddr 0x1e9a1c8 | ghidra 0x1f9a1c8 | size 264 | symbol _ZN9Framework13CSoundManager4StopEmf | lib libSOA-3.7.0.so | 2026-10-08
void _ZN9Framework13CSoundManager4StopEmf(undefined8 param_1,long param_2,long param_3)

{
  ulong uVar1;
  long *plVar2;
  long lVar3;
  ulong uVar4;
  long lVar5;
  int iVar6;
  
  lVar5 = *(long *)(param_2 + 0x68);
  if (lVar5 != 0) {
    uVar1 = Framework::CMutex::IsInitialized() const(lVar5);
    if ((uVar1 & 1) == 0) {
      Framework::CMutex::Initialize()(lVar5);
    }
    Framework::CMutex::Lock()(lVar5);
  }
  plVar2 = *(long **)(param_2 + 0x60);
  if (plVar2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965bfc/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Sound.cpp"*/,0x297,&UNK_027ee29f/*"m_pElements is null."*/);
    plVar2 = *(long **)(param_2 + 0x60);
  }
  lVar3 = (**(code **)(*plVar2 + 0x20))();
  if (lVar3 != 0) {
    uVar1 = 0;
    do {
      lVar3 = (**(code **)(**(long **)(param_2 + 0x60) + 0x28))(*(long **)(param_2 + 0x60),uVar1);
      iVar6 = (int)uVar1;
      if (*(long *)(lVar3 + 8) == param_3) {
        if (-1 < iVar6) {
          (**(code **)(**(long **)(param_2 + 0x60) + 0x28))(*(long **)(param_2 + 0x60),(long)iVar6);
          Framework::CSound::CElement::SendStopRequest(float)(param_1);
        }
        break;
      }
      uVar1 = (ulong)(iVar6 + 1);
      uVar4 = (**(code **)(**(long **)(param_2 + 0x60) + 0x20))();
    } while (uVar1 < uVar4);
  }
  if (lVar5 == 0) {
    return;
  }
  (*(code *)PTR__ZN9Framework6CMutex6UnlockEv_02cb3f98)(lVar5);
  return;
}

// ==== Framework::CSoundManager::Pause(unsigned long, float)
// vaddr 0x1e9a2d0 | ghidra 0x1f9a2d0 | size 388 | symbol _ZN9Framework13CSoundManager5PauseEmf | lib libSOA-3.7.0.so | 2026-10-08
void _ZN9Framework13CSoundManager5PauseEmf(float param_1,long param_2,long param_3)

{
  ulong uVar1;
  long *plVar2;
  long lVar3;
  ulong uVar4;
  long lVar5;
  int iVar6;
  
  lVar5 = *(long *)(param_2 + 0x68);
  if (lVar5 != 0) {
    uVar1 = Framework::CMutex::IsInitialized() const(lVar5);
    if ((uVar1 & 1) == 0) {
      Framework::CMutex::Initialize()(lVar5);
    }
    Framework::CMutex::Lock()(lVar5);
  }
  plVar2 = *(long **)(param_2 + 0x60);
  if (plVar2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965bfc/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Sound.cpp"*/,0x297,&UNK_027ee29f/*"m_pElements is null."*/);
    plVar2 = *(long **)(param_2 + 0x60);
  }
  lVar3 = (**(code **)(*plVar2 + 0x20))();
  if (lVar3 != 0) {
    uVar1 = 0;
    do {
      lVar3 = (**(code **)(**(long **)(param_2 + 0x60) + 0x28))(*(long **)(param_2 + 0x60),uVar1);
      iVar6 = (int)uVar1;
      if (*(long *)(lVar3 + 8) == param_3) {
        if (-1 < iVar6) {
          lVar3 = (**(code **)(**(long **)(param_2 + 0x60) + 0x28))
                            (*(long **)(param_2 + 0x60),(long)iVar6);
          if (param_1 < 0.0) {
            Framework::gDoAssert(char const*, int, char const*, ...)((double)param_1,&UNK_02965bfc/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Sound.cpp"*/,0x1ba,&UNK_02965cf9/*"The arguments 'aFadeTime' less than 0.(%f)"*/);
          }
          if ((*(long *)(lVar3 + 8) != *(long *)PTR__ZN9Framework6CSound14iInvalidHandleE_02cc4340)
             && ((*(byte *)(*(long *)(lVar3 + 0x10) + 0x1f2) & 1) == 0)) {
            if ((*(uint *)(*(long *)(lVar3 + 0x10) + 0x1e8) & 3) == 0) {
              Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965bfc/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Sound.cpp"*/,0x1cf,&UNK_02965d24/*"Illegal sound type.(%08x)"*/);
            }
            else {
              Aska::SoundManager::PauseSound(Aska::SoundObject*)(*(undefined8 *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50);
            }
          }
        }
        break;
      }
      uVar1 = (ulong)(iVar6 + 1);
      uVar4 = (**(code **)(**(long **)(param_2 + 0x60) + 0x20))();
    } while (uVar1 < uVar4);
  }
  if (lVar5 != 0) {
    (*(code *)PTR__ZN9Framework6CMutex6UnlockEv_02cb3f98)(lVar5);
    return;
  }
  return;
}

// ==== Framework::CSoundManager::Resume(unsigned long, float)
// vaddr 0x1e9a454 | ghidra 0x1f9a454 | size 388 | symbol _ZN9Framework13CSoundManager6ResumeEmf | lib libSOA-3.7.0.so | 2026-10-08
void _ZN9Framework13CSoundManager6ResumeEmf(float param_1,long param_2,long param_3)

{
  ulong uVar1;
  long *plVar2;
  long lVar3;
  ulong uVar4;
  long lVar5;
  int iVar6;
  
  lVar5 = *(long *)(param_2 + 0x68);
  if (lVar5 != 0) {
    uVar1 = Framework::CMutex::IsInitialized() const(lVar5);
    if ((uVar1 & 1) == 0) {
      Framework::CMutex::Initialize()(lVar5);
    }
    Framework::CMutex::Lock()(lVar5);
  }
  plVar2 = *(long **)(param_2 + 0x60);
  if (plVar2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965bfc/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Sound.cpp"*/,0x297,&UNK_027ee29f/*"m_pElements is null."*/);
    plVar2 = *(long **)(param_2 + 0x60);
  }
  lVar3 = (**(code **)(*plVar2 + 0x20))();
  if (lVar3 != 0) {
    uVar1 = 0;
    do {
      lVar3 = (**(code **)(**(long **)(param_2 + 0x60) + 0x28))(*(long **)(param_2 + 0x60),uVar1);
      iVar6 = (int)uVar1;
      if (*(long *)(lVar3 + 8) == param_3) {
        if (-1 < iVar6) {
          lVar3 = (**(code **)(**(long **)(param_2 + 0x60) + 0x28))
                            (*(long **)(param_2 + 0x60),(long)iVar6);
          if (param_1 < 0.0) {
            Framework::gDoAssert(char const*, int, char const*, ...)((double)param_1,&UNK_02965bfc/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Sound.cpp"*/,0x1ba,&UNK_02965cf9/*"The arguments 'aFadeTime' less than 0.(%f)"*/);
          }
          if ((*(long *)(lVar3 + 8) != *(long *)PTR__ZN9Framework6CSound14iInvalidHandleE_02cc4340)
             && ((*(byte *)(*(long *)(lVar3 + 0x10) + 0x1f2) & 1) == 0)) {
            if ((*(uint *)(*(long *)(lVar3 + 0x10) + 0x1e8) & 3) == 0) {
              Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965bfc/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Sound.cpp"*/,0x1cf,&UNK_02965d24/*"Illegal sound type.(%08x)"*/);
            }
            else {
              Aska::SoundManager::ResumeSound(Aska::SoundObject*)(*(undefined8 *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50);
            }
          }
        }
        break;
      }
      uVar1 = (ulong)(iVar6 + 1);
      uVar4 = (**(code **)(**(long **)(param_2 + 0x60) + 0x20))();
    } while (uVar1 < uVar4);
  }
  if (lVar5 != 0) {
    (*(code *)PTR__ZN9Framework6CMutex6UnlockEv_02cb3f98)(lVar5);
    return;
  }
  return;
}

// ==== Framework::CSoundManager::Watchdog(unsigned long)
// vaddr 0x1e9a5d8 | ghidra 0x1f9a5d8 | size 268 | symbol _ZN9Framework13CSoundManager8WatchdogEm | lib libSOA-3.7.0.so | 2026-10-08
void _ZN9Framework13CSoundManager8WatchdogEm(long param_1,long param_2)

{
  ulong uVar1;
  long *plVar2;
  long lVar3;
  ulong uVar4;
  long lVar5;
  int iVar6;
  
  if (*(long *)PTR__ZN9Framework6CSound14iInvalidHandleE_02cc4340 != param_2) {
    lVar5 = *(long *)(param_1 + 0x68);
    if (lVar5 != 0) {
      uVar1 = Framework::CMutex::IsInitialized() const(lVar5);
      if ((uVar1 & 1) == 0) {
        Framework::CMutex::Initialize()(lVar5);
      }
      Framework::CMutex::Lock()(lVar5);
    }
    plVar2 = *(long **)(param_1 + 0x60);
    if (plVar2 == (long *)0x0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965bfc/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Sound.cpp"*/,0x297,&UNK_027ee29f/*"m_pElements is null."*/);
      plVar2 = *(long **)(param_1 + 0x60);
    }
    lVar3 = (**(code **)(*plVar2 + 0x20))();
    if (lVar3 != 0) {
      uVar1 = 0;
      do {
        lVar3 = (**(code **)(**(long **)(param_1 + 0x60) + 0x28))(*(long **)(param_1 + 0x60),uVar1);
        iVar6 = (int)uVar1;
        if (*(long *)(lVar3 + 8) == param_2) {
          if (-1 < iVar6) {
            lVar3 = (**(code **)(**(long **)(param_1 + 0x60) + 0x28))
                              (*(long **)(param_1 + 0x60),(long)iVar6);
            *(undefined1 *)(lVar3 + 0x19) = 1;
          }
          break;
        }
        uVar1 = (ulong)(iVar6 + 1);
        uVar4 = (**(code **)(**(long **)(param_1 + 0x60) + 0x20))();
      } while (uVar1 < uVar4);
    }
    if (lVar5 != 0) {
      (*(code *)PTR__ZN9Framework6CMutex6UnlockEv_02cb3f98)(lVar5);
      return;
    }
  }
  return;
}

// ==== Framework::CSoundManager::Element(unsigned long, std::__ndk1::function<void (Framework::CSound::CElement&)>)
// vaddr 0x1e9a6e4 | ghidra 0x1f9a6e4 | size 288 | symbol _ZN9Framework13CSoundManager7ElementEmNSt6__ndk18functionIFvRNS_6CSound8CElementEEEE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN9Framework13CSoundManager7ElementEmNSt6__ndk18functionIFvRNS_6CSound8CElementEEEE
               (long param_1,long param_2,long param_3)

{
  ulong uVar1;
  long *plVar2;
  long lVar3;
  ulong uVar4;
  undefined8 uVar5;
  long lVar6;
  int iVar7;
  
  if (*(long *)PTR__ZN9Framework6CSound14iInvalidHandleE_02cc4340 != param_2) {
    lVar6 = *(long *)(param_1 + 0x68);
    if (lVar6 != 0) {
      uVar1 = Framework::CMutex::IsInitialized() const(lVar6);
      if ((uVar1 & 1) == 0) {
        Framework::CMutex::Initialize()(lVar6);
      }
      Framework::CMutex::Lock()(lVar6);
    }
    plVar2 = *(long **)(param_1 + 0x60);
    if (plVar2 == (long *)0x0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965bfc/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Sound.cpp"*/,0x297,&UNK_027ee29f/*"m_pElements is null."*/);
      plVar2 = *(long **)(param_1 + 0x60);
    }
    lVar3 = (**(code **)(*plVar2 + 0x20))();
    if (lVar3 != 0) {
      uVar1 = 0;
      do {
        lVar3 = (**(code **)(**(long **)(param_1 + 0x60) + 0x28))(*(long **)(param_1 + 0x60),uVar1);
        iVar7 = (int)uVar1;
        if (*(long *)(lVar3 + 8) == param_2) {
          if (-1 < iVar7) {
            uVar5 = (**(code **)(**(long **)(param_1 + 0x60) + 0x28))
                              (*(long **)(param_1 + 0x60),(long)iVar7);
            (**(code **)(**(long **)(param_3 + 0x20) + 0x30))(*(long **)(param_3 + 0x20),uVar5);
          }
          break;
        }
        uVar1 = (ulong)(iVar7 + 1);
        uVar4 = (**(code **)(**(long **)(param_1 + 0x60) + 0x20))();
      } while (uVar1 < uVar4);
    }
    if (lVar6 != 0) {
      (*(code *)PTR__ZN9Framework6CMutex6UnlockEv_02cb3f98)(lVar6);
      return;
    }
  }
  return;
}

// ==== Framework::CSoundManager::rElementContainer() const
// vaddr 0x1e9a804 | ghidra 0x1f9a804 | size 60 | symbol _ZNK9Framework13CSoundManager17rElementContainerEv | lib libSOA-3.7.0.so | 2026-10-08
long _ZNK9Framework13CSoundManager17rElementContainerEv(long param_1)

{
  if (*(long *)(param_1 + 0x60) != 0) {
    return *(long *)(param_1 + 0x60);
  }
  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965bfc/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Sound.cpp"*/,0x489,&UNK_027ee29f/*"m_pElements is null."*/);
  return *(long *)(param_1 + 0x60);
}

// ==== Framework::CSoundManager::CManageFiber::~CManageFiber()
// vaddr 0x1e9a840 | ghidra 0x1f9a840 | size 44 | symbol _ZN9Framework13CSoundManager12CManageFiberD2Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN9Framework13CSoundManager12CManageFiberD2Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN9Framework13CSoundManager12CManageFiberE_02cbe7f8 + 0x10);
  Framework::CFiberUnit::Destroy(bool)(param_1,0);
  (*(code *)PTR__ZN9Framework10CFiberUnitD1Ev_02c90ac0)(param_1);
  return;
}

// ==== Framework::CSoundManager::CManageFiber::~CManageFiber()
// vaddr 0x1e9a86c | ghidra 0x1f9a86c | size 52 | symbol _ZN9Framework13CSoundManager12CManageFiberD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN9Framework13CSoundManager12CManageFiberD0Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN9Framework13CSoundManager12CManageFiberE_02cbe7f8 + 0x10);
  Framework::CFiberUnit::Destroy(bool)(param_1,0);
  Framework::CFiberUnit::~CFiberUnit()(param_1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Framework::CSoundManager::CManageFiber::Progress()
// vaddr 0x1e9a8a0 | ghidra 0x1f9a8a0 | size 72 | symbol _ZN9Framework13CSoundManager12CManageFiber8ProgressEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN9Framework13CSoundManager12CManageFiber8ProgressEv(long param_1)

{
  if (*(int *)(param_1 + 0x40) != 0) {
    if (*(int *)(param_1 + 0x40) == 1) {
      (*(code *)PTR__ZN9Framework13CSoundManager12PostProgressEv_02c99db8)
                (*(undefined8 *)(param_1 + 0x38));
      return;
    }
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965bfc/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Sound.cpp"*/,0x22e,&UNK_027ec344/*"Illegal type.(%d)"*/);
  }
  (*(code *)PTR__ZN9Framework13CSoundManager11PreProgressEv_02cb2b60)
            (*(undefined8 *)(param_1 + 0x38));
  return;
}

// ==== Framework::TObjectContainer<Framework::CSound::CElement>::~TObjectContainer()
// vaddr 0x1e9aacc | ghidra 0x1f9aacc | size 176 | symbol _ZN9Framework16TObjectContainerINS_6CSound8CElementEED2Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN9Framework16TObjectContainerINS_6CSound8CElementEED2Ev(long *param_1)

{
  undefined *puVar1;
  long lVar2;
  long *plVar3;
  long lVar4;
  long lVar5;
  
  lVar5 = param_1[2];
  *param_1 = (long)(PTR__ZTVN9Framework16TObjectContainerINS_6CSound8CElementEEE_02cc3758 + 0x10);
  if (lVar5 != 0) {
    lVar4 = *(long *)(lVar5 + -8);
    if (lVar4 != 0) {
      lVar4 = lVar4 * 0x70;
      puVar1 = PTR__ZTVN9Framework6CSound8CElementE_02cc3c98 + 0x10;
      do {
        lVar2 = lVar5 + lVar4;
        *(undefined **)(lVar2 + -0x70) = puVar1;
        if (*(long **)(lVar2 + -0x60) != (long *)0x0) {
          (**(code **)(**(long **)(lVar2 + -0x60) + 0x38))();
          *(undefined8 *)(lVar2 + -0x60) = 0;
        }
        plVar3 = *(long **)(lVar2 + -0x50);
        if (plVar3 != (long *)0x0) {
          (**(code **)(*plVar3 + 0x38))(plVar3,0);
          *(undefined8 *)(lVar2 + -0x50) = 0;
        }
        lVar4 = lVar4 + -0x70;
      } while (lVar4 != 0);
    }
    operator delete[](void*)((long *)(lVar5 + -8));
    param_1[2] = 0;
  }
  return;
}

// ==== Framework::TObjectContainer<Framework::CSound::CElement>::~TObjectContainer()
// vaddr 0x1e9ab7c | ghidra 0x1f9ab7c | size 176 | symbol _ZN9Framework16TObjectContainerINS_6CSound8CElementEED0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN9Framework16TObjectContainerINS_6CSound8CElementEED0Ev(long *param_1)

{
  undefined *puVar1;
  long lVar2;
  long *plVar3;
  long lVar4;
  long lVar5;
  
  lVar5 = param_1[2];
  *param_1 = (long)(PTR__ZTVN9Framework16TObjectContainerINS_6CSound8CElementEEE_02cc3758 + 0x10);
  if (lVar5 != 0) {
    lVar4 = *(long *)(lVar5 + -8);
    if (lVar4 != 0) {
      lVar4 = lVar4 * 0x70;
      puVar1 = PTR__ZTVN9Framework6CSound8CElementE_02cc3c98 + 0x10;
      do {
        lVar2 = lVar5 + lVar4;
        *(undefined **)(lVar2 + -0x70) = puVar1;
        if (*(long **)(lVar2 + -0x60) != (long *)0x0) {
          (**(code **)(**(long **)(lVar2 + -0x60) + 0x38))();
          *(undefined8 *)(lVar2 + -0x60) = 0;
        }
        plVar3 = *(long **)(lVar2 + -0x50);
        if (plVar3 != (long *)0x0) {
          (**(code **)(*plVar3 + 0x38))(plVar3,0);
          *(undefined8 *)(lVar2 + -0x50) = 0;
        }
        lVar4 = lVar4 + -0x70;
      } while (lVar4 != 0);
    }
    operator delete[](void*)((long *)(lVar5 + -8));
  }
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Framework::TObjectContainer<Framework::CSound::CElement>::Initialize(unsigned long)
// vaddr 0x1e9ac2c | ghidra 0x1f9ac2c | size 180 | symbol _ZN9Framework16TObjectContainerINS_6CSound8CElementEE10InitializeEm | lib libSOA-3.7.0.so | 2026-10-08
void _ZN9Framework16TObjectContainerINS_6CSound8CElementEE10InitializeEm(long param_1,ulong param_2)

{
  long lVar1;
  undefined *puVar2;
  undefined1 auVar3 [16];
  ulong *puVar4;
  ulong *puVar5;
  
  if (*(long *)(param_1 + 0x10) != 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965e66/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TObjectContainer.h"*/,0x25,&UNK_027ee2b4/*"m_pElements isn't null.(%08x)"*/);
  }
  auVar3._8_8_ = 0;
  auVar3._0_8_ = param_2;
  *(ulong *)(param_1 + 8) = param_2;
  lVar1 = param_2 * 0x70 + 8;
  if (SUB168(auVar3 * ZEXT816(0x70),8) != 0 || 0xfffffffffffffff7 < param_2 * 0x70) {
    lVar1 = -1;
  }
  puVar4 = (ulong *)operator new[](unsigned long, std::nothrow_t const&)(lVar1,PTR__ZSt7nothrow_02cb9a80);
  puVar5 = puVar4;
  if (puVar4 != (ulong *)0x0) {
    puVar5 = puVar4 + 1;
    *puVar4 = param_2;
    if (param_2 != 0) {
      puVar2 = PTR__ZTVN9Framework6CSound8CElementE_02cc3c98 + 0x10;
      puVar4 = puVar5;
      do {
        *puVar4 = (ulong)puVar2;
        puVar4[2] = 0;
        puVar4[4] = 0;
        puVar4 = puVar4 + 0xe;
      } while (puVar4 != puVar5 + param_2 * 0xe);
    }
  }
  *(ulong **)(param_1 + 0x10) = puVar5;
  return;
}

// ==== Framework::TObjectContainer<Framework::CSound::CElement>::Reset()
// vaddr 0x1e9ace0 | ghidra 0x1f9ace0 | size 4 | symbol _ZN9Framework16TObjectContainerINS_6CSound8CElementEE5ResetEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN9Framework16TObjectContainerINS_6CSound8CElementEE5ResetEv(void)

{
  return;
}

// ==== Framework::TObjectContainer<Framework::CSound::CElement>::NumElements() const
// vaddr 0x1e9ace4 | ghidra 0x1f9ace4 | size 52 | symbol _ZNK9Framework16TObjectContainerINS_6CSound8CElementEE11NumElementsEv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK9Framework16TObjectContainerINS_6CSound8CElementEE11NumElementsEv(long param_1)

{
  if (*(long *)(param_1 + 0x10) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965e66/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TObjectContainer.h"*/,0x3e,&UNK_027ee29f/*"m_pElements is null."*/);
  }
  return *(undefined8 *)(param_1 + 8);
}

// ==== Framework::TObjectContainer<Framework::CSound::CElement>::rElement(unsigned long)
// vaddr 0x1e9ad18 | ghidra 0x1f9ad18 | size 144 | symbol _ZN9Framework16TObjectContainerINS_6CSound8CElementEE8rElementEm | lib libSOA-3.7.0.so | 2026-10-08
long _ZN9Framework16TObjectContainerINS_6CSound8CElementEE8rElementEm(long *param_1,ulong param_2)

{
  ulong uVar1;
  undefined8 uVar2;
  
  if (param_1[2] == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965e66/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TObjectContainer.h"*/,0x44,&UNK_027ee29f/*"m_pElements is null."*/);
  }
  uVar1 = (**(code **)(*param_1 + 0x20))(param_1);
  if (uVar1 <= param_2) {
    uVar2 = (**(code **)(*param_1 + 0x20))(param_1);
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965e66/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TObjectContainer.h"*/,0x45,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,param_2,uVar2);
  }
  return param_1[2] + param_2 * 0x70;
}

// ==== Framework::TObjectContainer<Framework::CSound::CElement>::crElement(unsigned long) const
// vaddr 0x1e9ada8 | ghidra 0x1f9ada8 | size 144 | symbol _ZNK9Framework16TObjectContainerINS_6CSound8CElementEE9crElementEm | lib libSOA-3.7.0.so | 2026-10-08
long _ZNK9Framework16TObjectContainerINS_6CSound8CElementEE9crElementEm(long *param_1,ulong param_2)

{
  ulong uVar1;
  undefined8 uVar2;
  
  if (param_1[2] == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965e66/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TObjectContainer.h"*/,0x4b,&UNK_027ee29f/*"m_pElements is null."*/);
  }
  uVar1 = (**(code **)(*param_1 + 0x20))(param_1);
  if (uVar1 <= param_2) {
    uVar2 = (**(code **)(*param_1 + 0x20))(param_1);
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965e66/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TObjectContainer.h"*/,0x4c,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,param_2,uVar2);
  }
  return param_1[2] + param_2 * 0x70;
}


// FAILED to create function at 027e7850 typeinfo name for std::__ndk1::__function::__base<void (Framework::CSound::CElement&)>
// FAILED to create function at 02965ec0 typeinfo name for Framework::CSound::CElement
// FAILED to create function at 02965ee0 typeinfo name for Framework::TNonCopyable<Framework::CSound::CElement>
// FAILED to create function at 02965f70 typeinfo name for Framework::CSoundManager::CManageFiber
// FAILED to create function at 02965ff0 typeinfo name for Framework::TObjectContainer<Framework::CSound::CElement>
// FAILED to create function at 02aa1e60 std::__ndk1::__function::__base<void(Framework::CSound::CElement&)>::typeinfo
// FAILED to create function at 02baaee0 Framework::CSound::CElement::vtable
// FAILED to create function at 02baaf00 Framework::CSoundManager::vtable
// FAILED to create function at 02baaf38 Framework::TNonCopyable<Framework::CSound::CElement>::typeinfo
// FAILED to create function at 02baaf50 Framework::CSound::CElement::typeinfo
// FAILED to create function at 02baaf90 Framework::CSoundManager::typeinfo
// FAILED to create function at 02baafc8 Framework::CSoundManager::CManageFiber::vtable
// FAILED to create function at 02bab030 Framework::CSoundManager::CManageFiber::typeinfo
// FAILED to create function at 02bab088 Framework::TObjectContainer<Framework::CSound::CElement>::vtable
// FAILED to create function at 02bab0d0 Framework::TObjectContainer<Framework::CSound::CElement>::typeinfo
// FAILED to create function at 02cc70ac Framework::CSoundManager::gInstanceUniqueNumber
// FAILED to create function at 02d00518 Framework::CSound::iInvalidHandle
