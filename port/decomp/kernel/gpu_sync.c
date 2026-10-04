// port/decomp/kernel/gpu_sync.c: Ghidra decompiles for the kernel subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-04 08:18 UTC: tools/decomp.sh '--into' 'kernel/gpu_sync' 'Aska::GPUSync::'

// ==== Aska::GPUSync::WaitGPUSync()
// vaddr 0x21c4e30 | ghidra 0x22c4e30 | size 220 | symbol _ZN4Aska7GPUSync11WaitGPUSyncEv | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Possible PIC construction at 0x022c4e98: Changing call to branch */
/* WARNING: Possible PIC construction at 0x022c4ed8: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0x022c4e9c) */
/* WARNING: Removing unreachable block (ram,0x022c4edc) */
/* WARNING: Removing unreachable block (ram,0x022c4ee4) */
/* WARNING: Removing unreachable block (ram,0x022c4ef4) */

void _ZN4Aska7GPUSync11WaitGPUSyncEv(long param_1)

{
  ulong uVar1;
  undefined *puStack_98;
  undefined1 *puStack_90;
  undefined1 auStack_88 [104];
  
  Aska::Semaphore::Wait() const(param_1 + 0xc0);
  if (*(char *)(param_1 + 0xb8) != '\0') {
    Aska::Event::Event()(auStack_88);
    uVar1 = Aska::Event::Create(bool, bool)(auStack_88,1,0);
    if ((uVar1 & 1) != 0) {
      puStack_98 = PTR__ZTVN4Aska11EventNotifyE_02cb7e68 + 0x10;
      puStack_90 = auStack_88;
      Aska::NotifierThread::AddNotify(Aska::INotify*, unsigned int)(param_1,&puStack_98,0);
    }
  }
  (*(code *)PTR__ZNK4Aska9Semaphore6SignalEv_02c96cd0)(param_1 + 0xc0);
  return;
}

// ==== Aska::GPUSync::Notify()
// vaddr 0x21c4f0c | ghidra 0x22c4f0c | size 72 | symbol _ZN4Aska7GPUSync6NotifyEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska7GPUSync6NotifyEv(long param_1)

{
  Aska::Semaphore::Wait() const(param_1 + 0xc0);
  *(undefined1 *)(param_1 + 0xb8) = 0;
  Aska::PerformanceCounter::Set(int)(*(undefined8 *)PTR__ZN4Aska6Global21m_pPerformanceCounterE_02cc3ad8,2);
  Aska::NotifierThread::Notify()(param_1);
  (*(code *)PTR__ZNK4Aska9Semaphore6SignalEv_02c96cd0)(param_1 + 0xc0);
  return;
}

// ==== Aska::GPUSync::~GPUSync()
// vaddr 0x21c53e0 | ghidra 0x22c53e0 | size 64 | symbol _ZN4Aska7GPUSyncD2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska7GPUSyncD2Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska7GPUSyncE_02cc05c8 + 0x10);
  Aska::Semaphore::Exit()(param_1 + 0x18);
  Aska::Semaphore::~Semaphore()(param_1 + 0x18);
  (*(code *)PTR__ZN4Aska14NotifierThreadD2Ev_02ca2268)(param_1);
  return;
}

// ==== Aska::GPUSync::~GPUSync()
// vaddr 0x21c5420 | ghidra 0x22c5420 | size 72 | symbol _ZN4Aska7GPUSyncD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska7GPUSyncD0Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska7GPUSyncE_02cc05c8 + 0x10);
  Aska::Semaphore::Exit()(param_1 + 0x18);
  Aska::Semaphore::~Semaphore()(param_1 + 0x18);
  Aska::NotifierThread::~NotifierThread()(param_1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}


// FAILED to create function at 02c54420 Aska::GPUSync::vtable
// FAILED to create function at 02c54460 Aska::GPUSync::typeinfo
