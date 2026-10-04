// port/decomp/input/base_input.c: Ghidra decompiles for the input subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-04 06:16 UTC: tools/decomp.sh '--into' 'input/base_input' 'Aska::BaseInputPeripheral::'

// ==== Aska::BaseInputPeripheral::BaseInputPeripheral()
// vaddr 0x2221864 | ghidra 0x2321864 | size 88 | symbol _ZN4Aska19BaseInputPeripheralC2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska19BaseInputPeripheralC1Ev(long *param_1)

{
  undefined *puVar1;
  
  *param_1 = (long)(PTR__ZTVN4Aska14BasePeripheralE_02cbc550 + 0x10);
  Aska::FastCriticalSection::FastCriticalSection()(param_1 + 1);
  puVar1 = PTR__ZTVN4Aska19BaseInputPeripheralE_02cba178;
  param_1[0x13] = 0xffff0000ffff;
  *(undefined2 *)(param_1 + 0x14) = 0xff;
  *param_1 = (long)(puVar1 + 0x10);
  memset((long)param_1 + 0xa4,0,0x208);
  return;
}

// ==== Aska::BaseInputPeripheral::~BaseInputPeripheral()
// vaddr 0x22218bc | ghidra 0x23218bc | size 40 | symbol _ZN4Aska19BaseInputPeripheralD1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska19BaseInputPeripheralD2Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska14BasePeripheralE_02cbc550 + 0x10);
  Aska::FastCriticalSection::~FastCriticalSection()(param_1 + 1);
  (*(code *)PTR__ZN4Aska11IAnimatableD2Ev_02cb13b8)(param_1);
  return;
}

// ==== Aska::BaseInputPeripheral::~BaseInputPeripheral()
// vaddr 0x22218e4 | ghidra 0x23218e4 | size 48 | symbol _ZN4Aska19BaseInputPeripheralD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska19BaseInputPeripheralD0Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska14BasePeripheralE_02cbc550 + 0x10);
  Aska::FastCriticalSection::~FastCriticalSection()(param_1 + 1);
  Aska::IAnimatable::~IAnimatable()(param_1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::BaseInputPeripheral::Initialize(unsigned char)
// vaddr 0x2221914 | ghidra 0x2321914 | size 4 | symbol _ZN4Aska19BaseInputPeripheral10InitializeEh | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska19BaseInputPeripheral10InitializeEh(void)

{
  return;
}

// ==== Aska::BaseInputPeripheral::Release()
// vaddr 0x2221918 | ghidra 0x2321918 | size 4 | symbol _ZN4Aska19BaseInputPeripheral7ReleaseEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska19BaseInputPeripheral7ReleaseEv(void)

{
  (*(code *)PTR__ZN4Aska14BasePeripheral7ReleaseEv_02cb1f90)();
  return;
}

// ==== Aska::BaseInputPeripheral::GetStatus()
// vaddr 0x222191c | ghidra 0x232191c | size 8 | symbol _ZN4Aska19BaseInputPeripheral9GetStatusEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska19BaseInputPeripheral9GetStatusEv(void)

{
  return 0;
}

// ==== Aska::BaseInputPeripheral::ResetStatus()
// vaddr 0x2221924 | ghidra 0x2321924 | size 4 | symbol _ZN4Aska19BaseInputPeripheral11ResetStatusEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska19BaseInputPeripheral11ResetStatusEv(void)

{
  return;
}

// ==== Aska::BaseInputPeripheral::CopyMessages(Aska::BaseInputPeripheral::Message*) const
// vaddr 0x2221928 | ghidra 0x2321928 | size 144 | symbol _ZNK4Aska19BaseInputPeripheral12CopyMessagesEPNS0_7MessageE | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK4Aska19BaseInputPeripheral12CopyMessagesEPNS0_7MessageE(long param_1,undefined8 *param_2)

{
  uint uVar1;
  uint uVar2;
  ulong uVar3;
  
  uVar2 = *(int *)(param_1 + 0x2a8) - *(int *)(param_1 + 0x2a4);
  if (0 < (int)uVar2) {
    uVar1 = 0x40;
    if (*(int *)(param_1 + 0x2a8) < 0x41) {
      uVar1 = uVar2;
    }
    if ((0 < (int)uVar1) &&
       (*param_2 = *(undefined8 *)(param_1 + (long)(*(int *)(param_1 + 0x2a4) % 0x40) * 8 + 0xa4),
       uVar1 != 1)) {
      uVar3 = 1;
      do {
        param_2[uVar3] =
             *(undefined8 *)
              (param_1 + (long)(((int)uVar3 + *(int *)(param_1 + 0x2a4)) % 0x40) * 8 + 0xa4);
        uVar3 = uVar3 + 1;
      } while (uVar1 != uVar3);
    }
  }
  return;
}

// ==== Aska::BaseInputPeripheral::ClearMessages()
// vaddr 0x22219b8 | ghidra 0x23219b8 | size 12 | symbol _ZN4Aska19BaseInputPeripheral13ClearMessagesEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska19BaseInputPeripheral13ClearMessagesEv(long param_1)

{
  *(undefined8 *)(param_1 + 0x2a4) = 0;
  return;
}

// ==== Aska::BaseInputPeripheral::AddMessage(Aska::BaseInputPeripheral::Message const*)
// vaddr 0x22219c4 | ghidra 0x23219c4 | size 60 | symbol _ZN4Aska19BaseInputPeripheral10AddMessageEPKNS0_7MessageE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska19BaseInputPeripheral10AddMessageEPKNS0_7MessageE(long param_1,undefined8 *param_2)

{
  if (*(int *)(param_1 + 0x2a8) < 0x40) {
    *(undefined8 *)(param_1 + (long)(*(int *)(param_1 + 0x2a8) % 0x40) * 8 + 0xa4) = *param_2;
    *(int *)(param_1 + 0x2a8) = *(int *)(param_1 + 0x2a8) + 1;
  }
  return;
}

// ==== Aska::BaseInputPeripheral::GetDeviceDataNoPort()
// vaddr 0x2221a00 | ghidra 0x2321a00 | size 4 | symbol _ZN4Aska19BaseInputPeripheral19GetDeviceDataNoPortEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska19BaseInputPeripheral19GetDeviceDataNoPortEv(void)

{
  return;
}

// ==== Aska::BaseInputPeripheral::GetDeviceData()
// vaddr 0x2221a04 | ghidra 0x2321a04 | size 8 | symbol _ZN4Aska19BaseInputPeripheral13GetDeviceDataEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska19BaseInputPeripheral13GetDeviceDataEv(void)

{
  return 0;
}


// FAILED to create function at 02c5dc68 Aska::BaseInputPeripheral::vtable
// FAILED to create function at 02c5dce0 Aska::BaseInputPeripheral::typeinfo
