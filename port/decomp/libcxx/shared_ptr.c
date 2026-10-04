// port/decomp/libcxx/shared_ptr.c: Ghidra decompiles for the libcxx subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-04 05:14 UTC: tools/decomp.sh '--into' 'libcxx/shared_ptr' '__shared_count::__(add|release)_shared' '__shared_weak_count::__(add|release)_(shared|weak)' '__shared_weak_count::lock'

// ==== std::__ndk1::__shared_count::__add_shared()
// vaddr 0x269537c | ghidra 0x279537c | size 24 | symbol _ZNSt6__ndk114__shared_count12__add_sharedEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZNSt6__ndk114__shared_count12__add_sharedEv(long param_1)

{
  long *plVar1;
  char cVar2;
  bool bVar3;
  
  plVar1 = (long *)(param_1 + 8);
  do {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(plVar1,0x10);
    if (bVar3) {
      *plVar1 = *plVar1 + 1;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
  return;
}

// ==== std::__ndk1::__shared_count::__release_shared()
// vaddr 0x2695394 | ghidra 0x2795394 | size 64 | symbol _ZNSt6__ndk114__shared_count16__release_sharedEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNSt6__ndk114__shared_count16__release_sharedEv(long *param_1)

{
  long *plVar1;
  char cVar2;
  bool bVar3;
  long lVar4;
  
  plVar1 = param_1 + 1;
  do {
    lVar4 = *plVar1;
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(plVar1,0x10);
    if (bVar3) {
      *plVar1 = lVar4 + -1;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
  if (lVar4 != 0) {
    return 0;
  }
  (**(code **)(*param_1 + 0x10))();
  return 1;
}

// ==== std::__ndk1::__shared_weak_count::__add_shared()
// vaddr 0x26953d8 | ghidra 0x27953d8 | size 24 | symbol _ZNSt6__ndk119__shared_weak_count12__add_sharedEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZNSt6__ndk119__shared_weak_count12__add_sharedEv(long param_1)

{
  long *plVar1;
  char cVar2;
  bool bVar3;
  
  plVar1 = (long *)(param_1 + 8);
  do {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(plVar1,0x10);
    if (bVar3) {
      *plVar1 = *plVar1 + 1;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
  return;
}

// ==== std::__ndk1::__shared_weak_count::__add_weak()
// vaddr 0x26953f0 | ghidra 0x27953f0 | size 24 | symbol _ZNSt6__ndk119__shared_weak_count10__add_weakEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZNSt6__ndk119__shared_weak_count10__add_weakEv(long param_1)

{
  long *plVar1;
  char cVar2;
  bool bVar3;
  
  plVar1 = (long *)(param_1 + 0x10);
  do {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(plVar1,0x10);
    if (bVar3) {
      *plVar1 = *plVar1 + 1;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
  return;
}

// ==== std::__ndk1::__shared_weak_count::__release_shared()
// vaddr 0x2695408 | ghidra 0x2795408 | size 116 | symbol _ZNSt6__ndk119__shared_weak_count16__release_sharedEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZNSt6__ndk119__shared_weak_count16__release_sharedEv(long *param_1)

{
  char cVar1;
  bool bVar2;
  long lVar3;
  long *plVar4;
  
  plVar4 = param_1 + 1;
  do {
    lVar3 = *plVar4;
    cVar1 = '\x01';
    bVar2 = (bool)ExclusiveMonitorPass(plVar4,0x10);
    if (bVar2) {
      *plVar4 = lVar3 + -1;
      cVar1 = ExclusiveMonitorsStatus();
    }
  } while (cVar1 != '\0');
  if (lVar3 == 0) {
    plVar4 = param_1 + 2;
    (**(code **)(*param_1 + 0x10))(param_1);
    do {
      lVar3 = *plVar4;
      cVar1 = '\x01';
      bVar2 = (bool)ExclusiveMonitorPass(plVar4,0x10);
      if (bVar2) {
        *plVar4 = lVar3 + -1;
        cVar1 = ExclusiveMonitorsStatus();
      }
    } while (cVar1 != '\0');
    if (lVar3 == 0) {
                    /* WARNING: Could not recover jumptable at 0x02795478. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (**(code **)(*param_1 + 0x20))(param_1);
      return;
    }
  }
  return;
}

// ==== std::__ndk1::__shared_weak_count::__release_weak()
// vaddr 0x269547c | ghidra 0x279547c | size 40 | symbol _ZNSt6__ndk119__shared_weak_count14__release_weakEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZNSt6__ndk119__shared_weak_count14__release_weakEv(long *param_1)

{
  long *plVar1;
  char cVar2;
  bool bVar3;
  long lVar4;
  
  plVar1 = param_1 + 2;
  do {
    lVar4 = *plVar1;
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(plVar1,0x10);
    if (bVar3) {
      *plVar1 = lVar4 + -1;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
  if (lVar4 != 0) {
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x027954a0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*param_1 + 0x20))();
  return;
}

// ==== std::__ndk1::__shared_weak_count::lock()
// vaddr 0x26954a4 | ghidra 0x27954a4 | size 68 | symbol _ZNSt6__ndk119__shared_weak_count4lockEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZNSt6__ndk119__shared_weak_count4lockEv(long param_1)

{
  long *plVar1;
  char cVar2;
  bool bVar3;
  long lVar4;
  long lVar5;
  
  plVar1 = (long *)(param_1 + 8);
  lVar4 = *plVar1;
  do {
    while( true ) {
      if (lVar4 == -1) {
        return 0;
      }
      lVar5 = *plVar1;
      if (lVar5 == lVar4) break;
      ClearExclusiveLocal();
      lVar4 = lVar5;
    }
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(plVar1,0x10);
    if (bVar3) {
      *plVar1 = lVar4 + 1;
      cVar2 = ExclusiveMonitorsStatus();
    }
    lVar4 = lVar5;
  } while (cVar2 != '\0');
  return param_1;
}
