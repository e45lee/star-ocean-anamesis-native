// port/decomp/input/pad_droid.c: Ghidra decompiles for the input subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-04 06:25 UTC: tools/decomp.sh '--into' 'input/pad_droid' 'Aska::PadDroid::'

// ==== Aska::PadDroid::PadDroid()
// vaddr 0x1f06128 | ghidra 0x2006128 | size 40 | symbol _ZN4Aska8PadDroidC1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska8PadDroidC2Ev(long *param_1)

{
  Aska::Pad::Pad(short)(param_1,0);
  *param_1 = (long)(PTR__ZTVN4Aska8PadDroidE_02cbb7c0 + 0x10);
  return;
}

// ==== Aska::PadDroid::~PadDroid()
// vaddr 0x1f06178 | ghidra 0x2006178 | size 48 | symbol _ZN4Aska8PadDroidD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska8PadDroidD0Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska14BasePeripheralE_02cbc550 + 0x10);
  Aska::FastCriticalSection::~FastCriticalSection()(param_1 + 1);
  Aska::IAnimatable::~IAnimatable()(param_1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::PadDroid::GetClassID(int) const
// vaddr 0x1f061a8 | ghidra 0x20061a8 | size 100 | symbol _ZNK4Aska8PadDroid10GetClassIDEi | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska8PadDroid10GetClassIDEi(undefined8 param_1,int param_2)

{
  undefined8 uVar1;
  undefined8 uVar2;
  
  if (param_2 == 0) {
    return 0xf035f036f037f039;
  }
  if (param_2 == 1) {
    return 0xf000f035f036f037;
  }
  uVar2 = 0xf000f035;
  if (param_2 != 3) {
    uVar2 = 0xf000;
  }
  uVar1 = 0xf000f035f036;
  if (param_2 != 2) {
    uVar1 = uVar2;
  }
  return uVar1;
}

// ==== Aska::PadDroid::Get(unsigned long, void*) const
// vaddr 0x1f0620c | ghidra 0x200620c | size 8 | symbol _ZNK4Aska8PadDroid3GetEmPv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska8PadDroid3GetEmPv(void)

{
  return 0;
}

// ==== Aska::PadDroid::Set(unsigned long, void const*)
// vaddr 0x1f06214 | ghidra 0x2006214 | size 8 | symbol _ZN4Aska8PadDroid3SetEmPKv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska8PadDroid3SetEmPKv(void)

{
  return 0;
}

// ==== Aska::PadDroid::Initialize(unsigned char)
// vaddr 0x1f0621c | ghidra 0x200621c | size 4 | symbol _ZN4Aska8PadDroid10InitializeEh | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska8PadDroid10InitializeEh(void)

{
  return;
}

// ==== Aska::PadDroid::Release()
// vaddr 0x1f06220 | ghidra 0x2006220 | size 4 | symbol _ZN4Aska8PadDroid7ReleaseEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska8PadDroid7ReleaseEv(void)

{
  return;
}

// ==== Aska::PadDroid::ResetStatus()
// vaddr 0x1f06224 | ghidra 0x2006224 | size 4 | symbol _ZN4Aska8PadDroid11ResetStatusEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska8PadDroid11ResetStatusEv(void)

{
  return;
}

// ==== Aska::PadDroid::GetDeviceDataNoPort()
// vaddr 0x1f06228 | ghidra 0x2006228 | size 4 | symbol _ZN4Aska8PadDroid19GetDeviceDataNoPortEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska8PadDroid19GetDeviceDataNoPortEv(void)

{
  return;
}

// ==== Aska::PadDroid::GetDeviceData()
// vaddr 0x1f0622c | ghidra 0x200622c | size 8 | symbol _ZN4Aska8PadDroid13GetDeviceDataEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska8PadDroid13GetDeviceDataEv(void)

{
  return 1;
}

// ==== Aska::PadDroid::GetRawInputData() const
// vaddr 0x1f06234 | ghidra 0x2006234 | size 8 | symbol _ZNK4Aska8PadDroid15GetRawInputDataEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska8PadDroid15GetRawInputDataEv(void)

{
  return 0;
}

// ==== Aska::PadDroid::GetRawInputDataSize() const
// vaddr 0x1f0623c | ghidra 0x200623c | size 8 | symbol _ZNK4Aska8PadDroid19GetRawInputDataSizeEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska8PadDroid19GetRawInputDataSizeEv(void)

{
  return 0;
}

// ==== Aska::PadDroid::SetRawOutputData(void const*)
// vaddr 0x1f06244 | ghidra 0x2006244 | size 4 | symbol _ZN4Aska8PadDroid16SetRawOutputDataEPKv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska8PadDroid16SetRawOutputDataEPKv(void)

{
  return;
}

// ==== Aska::PadDroid::GetRawOutputDataSize() const
// vaddr 0x1f06248 | ghidra 0x2006248 | size 8 | symbol _ZNK4Aska8PadDroid20GetRawOutputDataSizeEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska8PadDroid20GetRawOutputDataSizeEv(void)

{
  return 0;
}

// ==== Aska::PadDroid::SetTriggerThreshold(Aska::Pad::TriggerThreshold, int)
// vaddr 0x1f06250 | ghidra 0x2006250 | size 4 | symbol _ZN4Aska8PadDroid19SetTriggerThresholdENS_3Pad16TriggerThresholdEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska8PadDroid19SetTriggerThresholdENS_3Pad16TriggerThresholdEi(void)

{
  return;
}

// ==== Aska::PadDroid::GetTriggerThreshold(Aska::Pad::TriggerThreshold) const
// vaddr 0x1f06254 | ghidra 0x2006254 | size 8 | symbol _ZNK4Aska8PadDroid19GetTriggerThresholdENS_3Pad16TriggerThresholdE | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska8PadDroid19GetTriggerThresholdENS_3Pad16TriggerThresholdE(void)

{
  return 0x7f;
}


// FAILED to create function at 02baf158 Aska::PadDroid::vtable
// FAILED to create function at 02baf200 Aska::PadDroid::typeinfo
// FAILED to create function at 02d00a59 Aska::PadDroid::m_bMenu
// FAILED to create function at 02d00a5a Aska::PadDroid::m_bBack
