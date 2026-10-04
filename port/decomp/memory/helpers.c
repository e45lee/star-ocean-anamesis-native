// port/decomp/memory/helpers.c: Ghidra decompiles for the memory subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-04 05:08 UTC: tools/decomp.sh '--into' 'memory/helpers' 'Aska::MemoryManagerHelper::' 'Framework::CApplicationMemory::' 'Aska::FastCriticalSection::FastCriticalSection' 'Aska::Global::'

// ==== Framework::CApplicationMemory::CApplicationMemory()
// vaddr 0x1e63c88 | ghidra 0x1f63c88 | size 80 | symbol _ZN9Framework18CApplicationMemoryC1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework18CApplicationMemoryC2Ev(undefined8 *param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZN9Framework10TSingletonINS_18CApplicationMemoryEE11m_pInstanceE_02cb8148;
  if (*(long *)PTR__ZN9Framework10TSingletonINS_18CApplicationMemoryEE11m_pInstanceE_02cb8148 != 0)
  {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029612b1/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TSingleton.h"*/,0x15,&UNK_027daee5/*"m_pInstance isn't null.(%08x)"*/);
  }
  *(undefined8 **)puVar1 = param_1;
  param_1[4] = 0;
  param_1[1] = 0;
  *param_1 = 0;
  param_1[3] = 0;
  param_1[2] = 0;
  return;
}

// ==== Framework::CApplicationMemory::SetPrimaryMemoryManager()
// vaddr 0x1e63cd8 | ghidra 0x1f63cd8 | size 100 | symbol _ZN9Framework18CApplicationMemory23SetPrimaryMemoryManagerEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework18CApplicationMemory23SetPrimaryMemoryManagerEv(long *param_1)

{
  long lVar1;
  
  if (*param_1 != 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02961439/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ApplicationMemory.cpp"*/,0x27,&UNK_02961496/*"m_pPrimaryMemoryManager isn't null.(%08x)"*/);
  }
  lVar1 = Aska::Global::GetAvailableMemoryManager()();
  *param_1 = lVar1;
  if (lVar1 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02961439/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ApplicationMemory.cpp"*/,0x29,&UNK_0296154f/*"pPrimaryMemoryManager is null."*/);
    lVar1 = *param_1;
  }
  Aska::MemoryManager::CalcFreeSize(bool)(lVar1,0);
  (*(code *)PTR__ZN9Framework37CAssignedMemoryManagerForSTLAllocator15CreateAndAttachEm_02caf2e8)
            (0x1c00000);
  return;
}

// ==== Framework::CApplicationMemory::SetParticleMemoryManager()
// vaddr 0x1e63d3c | ghidra 0x1f63d3c | size 220 | symbol _ZN9Framework18CApplicationMemory24SetParticleMemoryManagerEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework18CApplicationMemory24SetParticleMemoryManagerEv(long param_1)

{
  undefined *puVar1;
  int iVar2;
  long lVar3;
  ulong uVar4;
  undefined8 uVar5;
  
  if (*(long *)(param_1 + 0x10) != 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02961439/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ApplicationMemory.cpp"*/,0x66,&UNK_029614c0/*"m_pParticleMemoryManager isn't null.(%08x)"*/);
  }
  lVar3 = operator new(unsigned long, std::nothrow_t const&)(0xf0,PTR__ZSt7nothrow_02cb9a80);
  if (lVar3 != 0) {
    Aska::MemoryManager::MemoryManager()(lVar3);
  }
  *(long *)(param_1 + 0x10) = lVar3;
  uVar4 = Aska::MemoryManager::InitHeap(unsigned long)(lVar3,0xf00000);
  if ((uVar4 & 1) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02961439/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ApplicationMemory.cpp"*/,0x69,&UNK_029614eb/*"result is null."*/);
  }
  lVar3 = *(long *)(param_1 + 0x10);
  if (((bRam0000000002d00278 & 1) == 0) && (iVar2 = __cxa_guard_acquire(0x2d00278), iVar2 != 0)) {
    __cxa_guard_release(0x2d00278);
  }
  puVar1 = PTR__ZN4Aska6Global18m_pParticleManagerE_02cbd300;
  *(pointer_____offset_0x10___ **)(lVar3 + 0x30) =
       &PTR__ZTVN9Framework23CBadAllocateNotifyRetryE_16__02cc7088;
  uVar5 = *(undefined8 *)puVar1;
  *(undefined8 *)PTR__ZN4Aska15ParticleManager9gpMemHeapE_02cba838 = *(undefined8 *)(param_1 + 0x10)
  ;
  (*(code *)PTR__ZN4Aska15ParticleManager18PreAllocateBuffersEv_02c9c840)(uVar5);
  return;
}

// ==== Framework::CApplicationMemory::rDefaultBadAllocateNotifyRetry()
// vaddr 0x1e63e18 | ghidra 0x1f63e18 | size 64 | symbol _ZN9Framework18CApplicationMemory30rDefaultBadAllocateNotifyRetryEv | lib libSOA-3.7.0.so | 2026-10-04
pointer_____offset_0x10___ *
_ZN9Framework18CApplicationMemory30rDefaultBadAllocateNotifyRetryEv(void)

{
  int iVar1;
  
  if (((bRam0000000002d00278 & 1) == 0) && (iVar1 = __cxa_guard_acquire(0x2d00278), iVar1 != 0)) {
    __cxa_guard_release(0x2d00278);
  }
  return &PTR__ZTVN9Framework23CBadAllocateNotifyRetryE_16__02cc7088;
}

// ==== Framework::CApplicationMemory::SetSoundMemoryManager()
// vaddr 0x1e63e58 | ghidra 0x1f63e58 | size 208 | symbol _ZN9Framework18CApplicationMemory21SetSoundMemoryManagerEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework18CApplicationMemory21SetSoundMemoryManagerEv(long param_1)

{
  int iVar1;
  long lVar2;
  ulong uVar3;
  
  if (*(long *)(param_1 + 0x18) != 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02961439/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ApplicationMemory.cpp"*/,0x7b,&UNK_029614fb/*"m_pSoundMemoryManager isn't null.(%08x)"*/);
  }
  lVar2 = operator new(unsigned long, std::nothrow_t const&)(0xf0,PTR__ZSt7nothrow_02cb9a80);
  if (lVar2 != 0) {
    Aska::MemoryManager::MemoryManager()(lVar2);
  }
  *(long *)(param_1 + 0x18) = lVar2;
  uVar3 = Aska::MemoryManager::InitHeap(unsigned long)(lVar2,0x200000);
  if ((uVar3 & 1) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02961439/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ApplicationMemory.cpp"*/,0x7e,&UNK_029614eb/*"result is null."*/);
  }
  lVar2 = *(long *)(param_1 + 0x18);
  if (((bRam0000000002d00278 & 1) == 0) && (iVar1 = __cxa_guard_acquire(0x2d00278), iVar1 != 0)) {
    __cxa_guard_release(0x2d00278);
  }
  *(pointer_____offset_0x10___ **)(lVar2 + 0x30) =
       &PTR__ZTVN9Framework23CBadAllocateNotifyRetryE_16__02cc7088;
  *(undefined8 *)PTR__ZN4Aska11SoundMemory10m_pMemHeapE_02cbbc38 = *(undefined8 *)(param_1 + 0x18);
  (*(code *)PTR__ZN4Aska11SoundMemory20SetResourceMemoryMgrEPNS_13MemoryManagerE_02c99980)();
  return;
}

// ==== Framework::CApplicationMemory::SetNetworkMemoryManager()
// vaddr 0x1e63f28 | ghidra 0x1f63f28 | size 212 | symbol _ZN9Framework18CApplicationMemory23SetNetworkMemoryManagerEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework18CApplicationMemory23SetNetworkMemoryManagerEv(long param_1)

{
  undefined *puVar1;
  int iVar2;
  long lVar3;
  ulong uVar4;
  
  if (*(long *)(param_1 + 0x20) != 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02961439/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ApplicationMemory.cpp"*/,0x8e,&UNK_02961523/*"m_pNetworkMemoryManager isn't null.(%08x)"*/);
  }
  lVar3 = operator new(unsigned long, std::nothrow_t const&)(0xf0,PTR__ZSt7nothrow_02cb9a80);
  if (lVar3 != 0) {
    Aska::MemoryManager::MemoryManager()(lVar3);
  }
  *(long *)(param_1 + 0x20) = lVar3;
  uVar4 = Aska::MemoryManager::InitHeap(unsigned long)(lVar3,0x200000);
  if ((uVar4 & 1) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02961439/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ApplicationMemory.cpp"*/,0x91,&UNK_029614eb/*"result is null."*/);
  }
  lVar3 = *(long *)(param_1 + 0x20);
  if (((bRam0000000002d00278 & 1) == 0) && (iVar2 = __cxa_guard_acquire(0x2d00278), iVar2 != 0)) {
    __cxa_guard_release(0x2d00278);
  }
  puVar1 = PTR__ZN4Aska6Global19m_pNetworkAllocatorE_02cbc200;
  *(pointer_____offset_0x10___ **)(lVar3 + 0x30) =
       &PTR__ZTVN9Framework23CBadAllocateNotifyRetryE_16__02cc7088;
  (*(code *)PTR__ZN4Aska5Yayoi16NetworkAllocator3SetEPNS_13MemoryManagerEb_02ca8c20)
            (*(undefined8 *)puVar1,*(undefined8 *)(param_1 + 0x20),0);
  return;
}

// ==== Framework::CApplicationMemory::gReportMemory()
// vaddr 0x1e63ffc | ghidra 0x1f63ffc | size 60 | symbol _ZN9Framework18CApplicationMemory13gReportMemoryEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework18CApplicationMemory13gReportMemoryEv(long *param_1)

{
  long lVar1;
  
  lVar1 = *param_1;
  if (lVar1 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02961439/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ApplicationMemory.cpp"*/,0xc1,&UNK_0296154d/*"m_pPrimaryMemoryManager is null."*/);
    lVar1 = *param_1;
  }
  (*(code *)PTR__ZN9Framework21gReportMemoryManagerCERN4Aska13MemoryManagerEPKc_02cb3d38)
            (lVar1,&UNK_0296156e/*"CApplicationMemory::gReportMemory"*/);
  return;
}

// ==== Framework::CApplicationMemory::rPrimaryMemoryManager()
// vaddr 0x1e64038 | ghidra 0x1f64038 | size 60 | symbol _ZN9Framework18CApplicationMemory21rPrimaryMemoryManagerEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZN9Framework18CApplicationMemory21rPrimaryMemoryManagerEv(long *param_1)

{
  if (*param_1 != 0) {
    return *param_1;
  }
  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02961439/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ApplicationMemory.cpp"*/,200,&UNK_0296154d/*"m_pPrimaryMemoryManager is null."*/);
  return *param_1;
}

// ==== Framework::CApplicationMemory::rSecondaryMemoryManager()
// vaddr 0x1e64074 | ghidra 0x1f64074 | size 60 | symbol _ZN9Framework18CApplicationMemory23rSecondaryMemoryManagerEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZN9Framework18CApplicationMemory23rSecondaryMemoryManagerEv(long param_1)

{
  if (*(long *)(param_1 + 8) != 0) {
    return *(long *)(param_1 + 8);
  }
  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02961439/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ApplicationMemory.cpp"*/,0xce,&UNK_02961590/*"m_pSecondaryMemoryManager is null."*/);
  return *(long *)(param_1 + 8);
}

// ==== Framework::CApplicationMemory::rDefaultBadAllocateNotify()
// vaddr 0x1e640b0 | ghidra 0x1f640b0 | size 64 | symbol _ZN9Framework18CApplicationMemory25rDefaultBadAllocateNotifyEv | lib libSOA-3.7.0.so | 2026-10-04
pointer_____offset_0x10___ * _ZN9Framework18CApplicationMemory25rDefaultBadAllocateNotifyEv(void)

{
  int iVar1;
  
  if (((bRam0000000002d00270 & 1) == 0) && (iVar1 = __cxa_guard_acquire(0x2d00270), iVar1 != 0)) {
    __cxa_guard_release(0x2d00270);
  }
  return &PTR__ZTVN9Framework18CBadAllocateNotifyE_16__02cc7080;
}

// ==== Framework::CApplicationMemory::rParticleMemoryManager()
// vaddr 0x1e640f0 | ghidra 0x1f640f0 | size 60 | symbol _ZN9Framework18CApplicationMemory22rParticleMemoryManagerEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZN9Framework18CApplicationMemory22rParticleMemoryManagerEv(long param_1)

{
  if (*(long *)(param_1 + 0x10) != 0) {
    return *(long *)(param_1 + 0x10);
  }
  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02961439/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ApplicationMemory.cpp"*/,0xe4,&UNK_029615b3/*"m_pParticleMemoryManager is null."*/);
  return *(long *)(param_1 + 0x10);
}

// ==== Framework::CApplicationMemory::rSoundMemoryManager()
// vaddr 0x1e6412c | ghidra 0x1f6412c | size 60 | symbol _ZN9Framework18CApplicationMemory19rSoundMemoryManagerEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZN9Framework18CApplicationMemory19rSoundMemoryManagerEv(long param_1)

{
  if (*(long *)(param_1 + 0x18) != 0) {
    return *(long *)(param_1 + 0x18);
  }
  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02961439/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ApplicationMemory.cpp"*/,0xeb,&UNK_029615d5/*"m_pSoundMemoryManager is null."*/);
  return *(long *)(param_1 + 0x18);
}

// ==== Framework::CApplicationMemory::rNetworkMemoryManager()
// vaddr 0x1e64168 | ghidra 0x1f64168 | size 60 | symbol _ZN9Framework18CApplicationMemory21rNetworkMemoryManagerEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZN9Framework18CApplicationMemory21rNetworkMemoryManagerEv(long param_1)

{
  if (*(long *)(param_1 + 0x20) != 0) {
    return *(long *)(param_1 + 0x20);
  }
  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02961439/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ApplicationMemory.cpp"*/,0xf2,&UNK_029615f4/*"m_pNetworkMemoryManager is null."*/);
  return *(long *)(param_1 + 0x20);
}

// ==== Aska::MemoryManagerHelper::MemoryManagerHelper()
// vaddr 0x1f0aaac | ghidra 0x200aaac | size 32 | symbol _ZN4Aska19MemoryManagerHelperC1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska19MemoryManagerHelperC2Ev(long *param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZTVN4Aska19MemoryManagerHelperE_02cbae08;
  param_1[4] = 0;
  param_1[3] = 0;
  param_1[2] = 0;
  param_1[1] = 0;
  *param_1 = (long)(puVar1 + 0x10);
  return;
}

// ==== Aska::MemoryManagerHelper::~MemoryManagerHelper()
// vaddr 0x1f0aacc | ghidra 0x200aacc | size 72 | symbol _ZN4Aska19MemoryManagerHelperD2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska19MemoryManagerHelperD1Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska19MemoryManagerHelperE_02cbae08 + 0x10);
  if ((long *)param_1[1] != (long *)0x0) {
    (**(code **)(*(long *)param_1[1] + 0xd0))();
    param_1[1] = 0;
  }
  *(long *)PTR__ZN4Aska6Global16m_pMemoryManagerE_02cbd3f0 = param_1[2];
  return;
}

// ==== Aska::MemoryManagerHelper::Init(unsigned long, unsigned int)
// vaddr 0x1f0ab14 | ghidra 0x200ab14 | size 108 | symbol _ZN4Aska19MemoryManagerHelper4InitEmj | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska19MemoryManagerHelper4InitEmj(long param_1,undefined8 param_2)

{
  undefined *puVar1;
  undefined8 uVar2;
  
  puVar1 = PTR__ZN4Aska6Global16m_pMemoryManagerE_02cbd3f0;
  *(undefined8 *)(param_1 + 0x10) = *(undefined8 *)PTR__ZN4Aska6Global16m_pMemoryManagerE_02cbd3f0;
  uVar2 = operator new(unsigned long)(0xf0);
  Aska::MemoryManager::MemoryManager()();
  *(undefined8 *)(param_1 + 8) = uVar2;
  Aska::MemoryManager::InitHeap(unsigned long)(uVar2,param_2);
  Aska::MemoryManager::CalcFreeSize(bool)(*(undefined8 *)(param_1 + 8),0);
  *(undefined8 *)puVar1 = *(undefined8 *)(param_1 + 8);
  return 1;
}

// ==== Aska::MemoryManagerHelper::InitMemoryManager(unsigned long)
// vaddr 0x1f0ab80 | ghidra 0x200ab80 | size 76 | symbol _ZN4Aska19MemoryManagerHelper17InitMemoryManagerEm | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska19MemoryManagerHelper17InitMemoryManagerEm(long param_1,undefined8 param_2)

{
  undefined8 uVar1;
  
  uVar1 = operator new(unsigned long)(0xf0);
  Aska::MemoryManager::MemoryManager()();
  *(undefined8 *)(param_1 + 8) = uVar1;
  Aska::MemoryManager::InitHeap(unsigned long)(uVar1,param_2);
  Aska::MemoryManager::CalcFreeSize(bool)(*(undefined8 *)(param_1 + 8),0);
  return 1;
}

// ==== Aska::MemoryManagerHelper::Cleanup()
// vaddr 0x1f0abcc | ghidra 0x200abcc | size 56 | symbol _ZN4Aska19MemoryManagerHelper7CleanupEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska19MemoryManagerHelper7CleanupEv(long param_1)

{
  if (*(long **)(param_1 + 8) != (long *)0x0) {
    (**(code **)(**(long **)(param_1 + 8) + 0xd0))();
    *(undefined8 *)(param_1 + 8) = 0;
  }
  *(undefined8 *)PTR__ZN4Aska6Global16m_pMemoryManagerE_02cbd3f0 = *(undefined8 *)(param_1 + 0x10);
  return;
}

// ==== Aska::MemoryManagerHelper::CleanupMemoryManaer()
// vaddr 0x1f0ac04 | ghidra 0x200ac04 | size 40 | symbol _ZN4Aska19MemoryManagerHelper19CleanupMemoryManaerEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska19MemoryManagerHelper19CleanupMemoryManaerEv(long param_1)

{
  if (*(long **)(param_1 + 8) != (long *)0x0) {
    (**(code **)(**(long **)(param_1 + 8) + 0xd0))();
    *(undefined8 *)(param_1 + 8) = 0;
  }
  return;
}

// ==== Aska::MemoryManagerHelper::InitMemoryHandleManager(unsigned long, unsigned int)
// vaddr 0x1f0ac2c | ghidra 0x200ac2c | size 172 | symbol _ZN4Aska19MemoryManagerHelper23InitMemoryHandleManagerEmj | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska19MemoryManagerHelper23InitMemoryHandleManagerEmj
          (long param_1,long param_2,undefined4 param_3)

{
  long lVar1;
  long lVar2;
  ulong uVar3;
  long lVar4;
  
  if (*(long *)(param_1 + 8) != 0) {
    lVar1 = Aska::MemoryHandleManager::CalcSrbkAndBlocksSize(unsigned long, int)(param_2,param_3);
    lVar2 = operator new[](unsigned long, std::nothrow_t const&)(lVar1,PTR__ZSt7nothrow_02cb9a80);
    *(long *)(param_1 + 0x20) = lVar2;
    if (lVar2 == 0) {
      return 0;
    }
    lVar4 = *(long *)(param_1 + 0x18);
    if (lVar4 == 0) {
      lVar4 = operator new[](unsigned long, std::nothrow_t const&)(param_2 - lVar1,PTR__ZSt7nothrow_02cb9a80);
      *(long *)(param_1 + 0x18) = lVar4;
      if (lVar4 == 0) {
        return 0;
      }
    }
    uVar3 = Aska::MemoryManager::InitHeap(unsigned char*, unsigned long, unsigned char*, unsigned long)(*(undefined8 *)(param_1 + 8),lVar4,param_2 - lVar1,lVar2,lVar1);
    if ((uVar3 & 1) != 0) {
      Aska::MemoryManager::CalcFreeSize(bool)(*(undefined8 *)(param_1 + 8),0);
      return 1;
    }
  }
  return 0;
}

// ==== Aska::MemoryManagerHelper::CleanupMemoryHandleManager()
// vaddr 0x1f0acd8 | ghidra 0x200acd8 | size 72 | symbol _ZN4Aska19MemoryManagerHelper26CleanupMemoryHandleManagerEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska19MemoryManagerHelper26CleanupMemoryHandleManagerEv(long param_1)

{
  if (*(long **)(param_1 + 8) != (long *)0x0) {
    (**(code **)(**(long **)(param_1 + 8) + 0xd0))();
    *(undefined8 *)(param_1 + 8) = 0;
  }
  if (*(long *)(param_1 + 0x18) != 0) {
    operator delete[](void*)();
    *(undefined8 *)(param_1 + 0x18) = 0;
  }
  if (*(long *)(param_1 + 0x20) != 0) {
    operator delete[](void*)();
    *(undefined8 *)(param_1 + 0x20) = 0;
  }
  return;
}

