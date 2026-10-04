// port/decomp/resource/ahsl.c: Ghidra decompiles for the resource subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-04 06:15 UTC: tools/decomp.sh '--into' 'resource/ahsl' 'Aska::AHSLCacheManagerV2::' 'Aska::AHSLBase::' 'AHSLDatabase<'

// ==== Aska::AHSLCacheManagerV2::AHSLCacheManagerV2()
// vaddr 0x20ab260 | ghidra 0x21ab260 | size 920 | symbol _ZN4Aska18AHSLCacheManagerV2C2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18AHSLCacheManagerV2C1Ev(long *param_1)

{
  undefined *puVar1;
  undefined1 *puVar2;
  long lVar3;
  long *plVar4;
  char acStack_40 [2];
  undefined1 uStack_3e;
  undefined1 uStack_3c;
  undefined1 uStack_3a;
  
  param_1[3] = 0;
  *(undefined4 *)(param_1 + 4) = 0xffffffff;
  param_1[5] = 0;
  Aska::Thread::Thread()();
  *param_1 = (long)(PTR__ZTVN4Aska18AHSLCacheManagerV2E_02cbadd8 + 0x10);
  Aska::FastCriticalSection::FastCriticalSection()(param_1 + 6);
  plVar4 = param_1 + 0x18;
  do {
    *plVar4 = 0;
    *(undefined4 *)(plVar4 + 1) = 8;
    plVar4[2] = 0;
    plVar4 = plVar4 + 4;
  } while (plVar4 != param_1 + 0x818);
  plVar4 = param_1 + 0x818;
  do {
    *plVar4 = 0;
    *(undefined4 *)(plVar4 + 1) = 8;
    plVar4[2] = 0;
    plVar4 = plVar4 + 0x13;
  } while (plVar4 != param_1 + 0x2e18);
  *(undefined4 *)(param_1 + 0x2e18) = 0;
  Aska::MemoryManager::MemoryManager()(param_1 + 0x2e19);
  Aska::FastCriticalSection::FastCriticalSection()(param_1 + 0x2e39);
  Aska::FastCriticalSection::FastCriticalSection()(param_1 + 0x3317);
  plVar4 = param_1 + 0x3329;
  do {
    *plVar4 = 0;
    *(undefined4 *)(plVar4 + 1) = 8;
    plVar4[2] = 0;
    plVar4 = plVar4 + 4;
  } while (plVar4 != param_1 + 0x3b29);
  plVar4 = param_1 + 0x3b29;
  do {
    *plVar4 = 0;
    *(undefined4 *)(plVar4 + 1) = 8;
    plVar4[2] = 0;
    plVar4 = plVar4 + 0x13;
  } while (plVar4 != param_1 + 0x6129);
  *(undefined4 *)(param_1 + 0x6129) = 0;
  Aska::FastCriticalSection::FastCriticalSection()(param_1 + 0x612e);
  Aska::Event::Event()(param_1 + 0x6144);
  Aska::Event::Event()(param_1 + 0x6151);
  Aska::Event::Event()(param_1 + 0x615f);
  *(undefined1 *)((long)param_1 + 0x1725c) = 0;
  param_1[0x2e4c] = 1;
  *(undefined1 *)(param_1 + 0x6140) = 0;
  *(undefined1 *)((long)param_1 + 0x30a01) = 0;
  *(undefined1 *)((long)param_1 + 0x1748c) = 0;
  *(undefined1 *)(param_1 + 0x3296) = 0;
  memset(param_1 + 0x3297,0,0x400);
  puVar1 = PTR__ZSt7nothrow_02cb9a80;
  puVar2 = (undefined1 *)operator new[](unsigned long, std::nothrow_t const&)(0xb000,PTR__ZSt7nothrow_02cb9a80);
  param_1[0x612c] = (long)puVar2;
  *puVar2 = 0;
  puVar2 = (undefined1 *)operator new[](unsigned long, std::nothrow_t const&)(0xb000,puVar1);
  param_1[0x612d] = (long)puVar2;
  *puVar2 = 0;
  lVar3 = operator new[](unsigned long, unsigned long, bool)(0x304020,0x10,1);
  param_1[0x2e4d] = lVar3;
  Aska::MemoryManager::InitHeap(unsigned char*, unsigned long)(param_1 + 0x2e19,lVar3,0x300000);
  puVar1 = PTR_szNonDebugTargetName_02cb93e0;
  param_1[0x2e37] = 0;
  *(undefined2 *)(param_1 + 0x2e38) = 0;
  param_1[0x2e4e] = *(long *)puVar1;
  param_1[0x2e50] = 0;
  param_1[0x2e4f] = 0;
  Aska::GetLocalTime(Aska::ASKATIME*)(acStack_40);
  *(char *)(param_1 + 0x2e91) = acStack_40[0] + '0';
  *(undefined1 *)((long)param_1 + 0x17489) = uStack_3e;
  *(undefined1 *)((long)param_1 + 0x1748a) = uStack_3c;
  *(undefined1 *)((long)param_1 + 0x1748b) = uStack_3a;
  *(undefined1 *)(param_1 + 0x2e51) = 0;
  *(undefined1 *)(param_1 + 0x2e71) = 0;
  *(undefined4 *)((long)param_1 + 0x171c4) = 2;
  *(undefined4 *)((long)param_1 + 0x30a04) = 0xffffffff;
  param_1[0x6142] = 0;
  param_1[0x6141] = 0;
  *(undefined1 *)(param_1 + 0x6143) = 0;
  *(undefined1 *)((long)param_1 + 0x30a19) = 0;
  Aska::Event::Create(bool, bool)(param_1 + 0x6144,0,0);
  Aska::Event::Create(bool, bool)(param_1 + 0x6151,0,0);
  *(undefined1 *)(param_1 + 0x615e) = 0;
  return;
}

// ==== Aska::AHSLCacheManagerV2::UpdateTimestamp()
// vaddr 0x20ab5f8 | ghidra 0x21ab5f8 | size 100 | symbol _ZN4Aska18AHSLCacheManagerV215UpdateTimestampEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18AHSLCacheManagerV215UpdateTimestampEv(long param_1)

{
  char acStack_20 [2];
  undefined1 uStack_1e;
  undefined1 uStack_1c;
  undefined1 uStack_1a;
  
  Aska::GetLocalTime(Aska::ASKATIME*)(acStack_20);
  *(char *)(param_1 + 0x17488) = acStack_20[0] + '0';
  *(undefined1 *)(param_1 + 0x17489) = uStack_1e;
  *(undefined1 *)(param_1 + 0x1748a) = uStack_1c;
  *(undefined1 *)(param_1 + 0x1748b) = uStack_1a;
  return;
}

// ==== Aska::AHSLCacheManagerV2::~AHSLCacheManagerV2()
// vaddr 0x20ab65c | ghidra 0x21ab65c | size 892 | symbol _ZN4Aska18AHSLCacheManagerV2D2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18AHSLCacheManagerV2D1Ev(long *param_1)

{
  long *plVar1;
  undefined *puVar2;
  long *plVar3;
  long lVar4;
  long *plVar5;
  ulong uVar6;
  long lVar7;
  
  *param_1 = (long)(PTR__ZTVN4Aska18AHSLCacheManagerV2E_02cbadd8 + 0x10);
  plVar3 = param_1 + 0x615f;
  *(undefined1 *)(param_1 + 0x615e) = 1;
  do {
    if ((char)param_1[0x6143] != '\0') {
      Aska::Event::Set() const(param_1 + 0x6144);
      Aska::Event::Wait(unsigned int) const(param_1 + 0x6151,0);
      *(undefined1 *)(param_1 + 0x6143) = 0;
    }
    Aska::Event::Set() const(plVar3);
    Aska::Thread::Sleep(unsigned int)(1);
  } while ((char)param_1[0x615e] != '\0');
  Aska::Thread::WaitEnd()(param_1);
  lVar4 = 0;
  plVar5 = param_1 + 0x81b;
  do {
    uVar6 = (ulong)*(ushort *)((long)param_1 + lVar4 * 0x98 + 0x40ca);
    if (uVar6 != 0) {
      lVar7 = 0;
      do {
        plVar1 = plVar5;
        if ((long *)param_1[lVar4 * 0x13 + 0x818] != (long *)0x0) {
          plVar1 = (long *)param_1[lVar4 * 0x13 + 0x818];
        }
        Aska::ShaderCache::ReleaseShader()(*(undefined8 *)((long)plVar1 + lVar7 + 8));
        uVar6 = uVar6 - 1;
        lVar7 = lVar7 + 0x10;
      } while (uVar6 != 0);
    }
    lVar4 = lVar4 + 1;
    plVar5 = plVar5 + 0x13;
  } while (lVar4 != 0x200);
  plVar5 = param_1 + 0x3297;
  lVar4 = 0x20;
  do {
    if (((*(char *)((long)plVar5 + 3) == '\x02') || (*(char *)((long)plVar5 + 4) == '\x02')) &&
       ((long *)plVar5[3] != (long *)0x0)) {
      (**(code **)(*(long *)plVar5[3] + 0x10))();
      plVar5[3] = 0;
    }
    Aska::AHSLCacheManagerV2::CleanCacheSlotL3(Aska::AHSLCacheManagerV2::CacheSlot*)(param_1,plVar5);
    puVar2 = PTR__ZN4Aska12g_pRenderDevE_02cbb1a0;
    lVar4 = lVar4 + -1;
    plVar5 = plVar5 + 4;
  } while (lVar4 != 0);
  Aska::RenderDeviceGL::SetCurrentContext_AskaMain()(*(undefined8 *)PTR__ZN4Aska12g_pRenderDevE_02cbb1a0);
  Aska::RenderDeviceGL::SetCurrentContext_None()(*(undefined8 *)puVar2);
  plVar5 = param_1 + 0x2e19;
  Aska::MemoryManager::ClearHeap()(plVar5);
  if (param_1[0x2e4d] != 0) {
    operator delete[](void*)();
    param_1[0x2e4d] = 0;
  }
  if (param_1[0x612c] != 0) {
    operator delete[](void*)();
    param_1[0x612c] = 0;
  }
  if (param_1[0x612d] != 0) {
    operator delete[](void*)();
    param_1[0x612d] = 0;
  }
  lVar7 = 0x13000;
  Aska::MemoryManager::DeleteHeap()(plVar5);
  Aska::Event::Exit()(plVar3);
  Aska::Event::Exit()(plVar3);
  Aska::Event::Exit()(param_1 + 0x6151);
  Aska::Event::Exit()(param_1 + 0x6144);
  Aska::FastCriticalSection::~FastCriticalSection()(param_1 + 0x612e);
  plVar3 = param_1 + 0x6118;
  lVar4 = -0x13000;
  do {
    if (plVar3[-2] != 0) {
      if (*plVar3 == 0) {
        operator delete[](void*)(plVar3[-2]);
      }
      else {
        Aska::MemoryManager::LocalFree(void*)();
      }
    }
    lVar4 = lVar4 + 0x98;
    plVar3 = plVar3 + -0x13;
  } while (lVar4 != 0);
  plVar3 = param_1 + 0x3b27;
  lVar4 = -0x4000;
  do {
    if (plVar3[-2] != 0) {
      if (*plVar3 == 0) {
        operator delete[](void*)(plVar3[-2]);
      }
      else {
        Aska::MemoryManager::LocalFree(void*)();
      }
    }
    lVar4 = lVar4 + 0x20;
    plVar3 = plVar3 + -4;
  } while (lVar4 != 0);
  Aska::FastCriticalSection::~FastCriticalSection()(param_1 + 0x3317);
  Aska::FastCriticalSection::~FastCriticalSection()(param_1 + 0x2e39);
  Aska::MemoryManager::~MemoryManager()(plVar5);
  do {
    while( true ) {
      lVar4 = *(long *)((long)param_1 + lVar7 + 0x4028);
      if (lVar4 != 0) break;
code_r0x021ab958:
      lVar7 = lVar7 + -0x98;
      if (lVar7 == 0) goto code_r0x021ab974;
    }
    if (*(long *)((long)param_1 + lVar7 + 0x4038) != 0) {
      Aska::MemoryManager::LocalFree(void*)();
      goto code_r0x021ab958;
    }
    operator delete[](void*)(lVar4);
    lVar7 = lVar7 + -0x98;
  } while (lVar7 != 0);
code_r0x021ab974:
  lVar4 = 0x4000;
  do {
    while( true ) {
      lVar7 = *(long *)((long)param_1 + lVar4 + 0xa0);
      if (lVar7 != 0) break;
code_r0x021ab990:
      lVar4 = lVar4 + -0x20;
      if (lVar4 == 0) goto code_r0x011c7c30;
    }
    if (*(long *)((long)param_1 + lVar4 + 0xb0) != 0) {
      Aska::MemoryManager::LocalFree(void*)();
      goto code_r0x021ab990;
    }
    operator delete[](void*)(lVar7);
    lVar4 = lVar4 + -0x20;
  } while (lVar4 != 0);
code_r0x011c7c30:
  Aska::FastCriticalSection::~FastCriticalSection()(param_1 + 6);
  (*(code *)PTR__ZN4Aska6ThreadD1Ev_02c9be08)(param_1);
  return;
}

// ==== Aska::AHSLCacheManagerV2::CleanCacheSlotL3(Aska::AHSLCacheManagerV2::CacheSlot*)
// vaddr 0x20ab9d8 | ghidra 0x21ab9d8 | size 376 | symbol _ZN4Aska18AHSLCacheManagerV216CleanCacheSlotL3EPNS0_9CacheSlotE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18AHSLCacheManagerV216CleanCacheSlotL3EPNS0_9CacheSlotE(long param_1,long param_2)

{
  ushort *puVar1;
  long lVar2;
  long lVar3;
  int *piVar4;
  ushort uVar5;
  int *piVar6;
  uint uVar7;
  undefined1 auStack_b040 [45056];
  
  piVar4 = *(int **)(param_2 + 8);
  if ((piVar4 != (int *)0x0) && (*(char *)(param_2 + 3) != '\x01')) {
    if ((*piVar4 == 0x5348504b) && (puVar1 = (ushort *)(piVar4 + 3), *puVar1 != 0)) {
      uVar5 = 0;
      piVar6 = piVar4 + 0x808;
      do {
        piVar4 = piVar6 + 2;
        if (*piVar4 == *(int *)PTR__ZN4Aska18AHSLDISKCACHEMAGICE_02cbad60) break;
        uVar5 = uVar5 + 1;
        piVar6 = (int *)((ulong)(piVar6[1] + 3U & 0xfffffffc) + (long)piVar6);
      } while (uVar5 < *puVar1);
    }
    if ((((*piVar4 == *(int *)PTR__ZN4Aska18AHSLDISKCACHEMAGICE_02cbad60) &&
         ((short)piVar4[2] == *(short *)(param_1 + 0x17258))) &&
        (*(short *)((long)piVar4 + 10) == *(short *)(param_1 + 0x1725a))) &&
       (uVar7 = (uint)*(ushort *)(piVar4 + 3), *(ushort *)(piVar4 + 3) != 0)) {
      piVar4 = piVar4 + 0x808;
      do {
        lVar3 = Aska::AHSLBase::UncompressShaderCache(Aska::ShaderDiskCache*, Aska::ShaderDiskCache const*, unsigned char*)(param_1 + 0x18,auStack_b040,piVar4,param_1 + 0x174b0);
        lVar2 = (ulong)*(ushort *)(lVar3 + 6) + lVar3;
        if (*(long **)(lVar2 + 0x20) != (long *)0x0) {
          (**(code **)(**(long **)(lVar2 + 0x20) + 8))();
          *(undefined8 *)(lVar2 + 0x20) = 0;
        }
        if (*(long *)(lVar2 + 0x28) != 0) {
          operator delete[](void*)();
          *(undefined8 *)(lVar2 + 0x28) = 0;
        }
        if ((*(byte *)((long)piVar4 + 10) & 3) != 0) {
          Aska::AHSLBase::CreateCompressedShaderCache(Aska::ShaderDiskCache*, void*, unsigned char*)(param_1 + 0x18,lVar3,piVar4,param_1 + 0x174b0);
        }
        uVar7 = uVar7 - 1;
        piVar4 = (int *)((long)piVar4 + (ulong)*(ushort *)((long)piVar4 + 2));
      } while (uVar7 != 0);
    }
  }
  return;
}

// ==== Aska::AHSLCacheManagerV2::CleanAllLinkedDiskCacheL2()
// vaddr 0x20abb50 | ghidra 0x21abb50 | size 4 | symbol _ZN4Aska18AHSLCacheManagerV225CleanAllLinkedDiskCacheL2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18AHSLCacheManagerV225CleanAllLinkedDiskCacheL2Ev(void)

{
  return;
}

// ==== Aska::AHSLCacheManagerV2::~AHSLCacheManagerV2()
// vaddr 0x20abb54 | ghidra 0x21abb54 | size 24 | symbol _ZN4Aska18AHSLCacheManagerV2D0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18AHSLCacheManagerV2D0Ev(undefined8 param_1)

{
  Aska::AHSLCacheManagerV2::~AHSLCacheManagerV2()();
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::AHSLCacheManagerV2::L1::ReleaseShaders()
// vaddr 0x20abb6c | ghidra 0x21abb6c | size 152 | symbol _ZN4Aska18AHSLCacheManagerV22L114ReleaseShadersEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18AHSLCacheManagerV22L114ReleaseShadersEv(long param_1)

{
  long lVar1;
  long lVar2;
  long lVar3;
  long lVar4;
  ulong uVar5;
  long lVar6;
  
  lVar3 = 0;
  lVar4 = param_1 + 0x40a8;
  do {
    uVar5 = (ulong)*(ushort *)(param_1 + lVar3 * 0x98 + 0x409a);
    if (uVar5 != 0) {
      lVar6 = 0;
      do {
        lVar2 = *(long *)(param_1 + lVar3 * 0x98 + 0x4090);
        lVar1 = lVar4;
        if (lVar2 != 0) {
          lVar1 = lVar2;
        }
        Aska::ShaderCache::ReleaseShader()(*(undefined8 *)(lVar1 + lVar6 + 8));
        uVar5 = uVar5 - 1;
        lVar6 = lVar6 + 0x10;
      } while (uVar5 != 0);
    }
    lVar3 = lVar3 + 1;
    lVar4 = lVar4 + 0x98;
  } while (lVar3 != 0x200);
  return;
}

// ==== Aska::AHSLCacheManagerV2::Init()
// vaddr 0x20abc04 | ghidra 0x21abc04 | size 408 | symbol _ZN4Aska18AHSLCacheManagerV24InitEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska18AHSLCacheManagerV24InitEv(long param_1)

{
  undefined *puVar1;
  undefined2 uVar2;
  ulong uVar3;
  
  *(undefined4 *)(param_1 + 0x20) = *(undefined4 *)PTR__ZN4Aska5s_eTCE_02cbe390;
  Aska::InitShaderKeyModifyUtil()();
  *(undefined8 *)(param_1 + 0x174a8) = 0;
  *(undefined8 *)(param_1 + 0x174a0) = 0;
  puVar1 = PTR__ZN4Aska18AHSLDISKCACHEMAGICE_02cbad60;
  *(undefined8 *)(param_1 + 0x17498) = 0;
  *(undefined8 *)(param_1 + 0x17490) = 0;
  *(undefined4 *)(param_1 + 0x17490) = *(undefined4 *)puVar1;
  *(undefined4 *)(param_1 + 0x17498) = *(undefined4 *)(param_1 + 0x17258);
  *(undefined2 *)(param_1 + 0x1749c) = 0;
  *(undefined4 *)(param_1 + 0x17494) = 0;
  memset(param_1 + 0x174b0,0,0x2000);
  uVar2 = Aska::ShaderKeyUtil::CalcCRC16(int, unsigned char const*)(0x2000,param_1 + 0x174b0);
  *(undefined2 *)(param_1 + 0x1748e) = uVar2;
  uVar3 = Aska::Event::Create(bool, bool)(param_1 + 0x30af8,0,0);
  if (((uVar3 & 1) != 0) && (uVar3 = Aska::Thread::Create(bool, int, int, bool)(param_1,0,0x50,0x64000,1), (uVar3 & 1) != 0)) {
    Aska::AHSLCacheManagerV2::AttachDiskCache(int, int)(param_1,0,1);
    puVar1 = PTR__ZN4Aska6Global24m_pSystemCallbackManagerE_02cb82c0;
    do {
      if (*(char *)(param_1 + 0x194b0) == '\0') {
        return 1;
      }
      if (*(char *)(param_1 + 0x30a18) != '\0') {
        Aska::Event::Set() const(param_1 + 0x30a20);
        Aska::Event::Wait(unsigned int) const(param_1 + 0x30a88,0);
        *(char *)(param_1 + 0x30a18) = '\0';
      }
    } while (*(char *)(*(long *)puVar1 + 8) == '\0');
  }
  return 0;
}

// ==== Aska::AHSLCacheManagerV2::InitFileCacheHeaderWork()
// vaddr 0x20abd9c | ghidra 0x21abd9c | size 168 | symbol _ZN4Aska18AHSLCacheManagerV223InitFileCacheHeaderWorkEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18AHSLCacheManagerV223InitFileCacheHeaderWorkEv(long param_1)

{
  undefined *puVar1;
  undefined2 uVar2;
  
  *(undefined8 *)(param_1 + 0x174a8) = 0;
  *(undefined8 *)(param_1 + 0x174a0) = 0;
  puVar1 = PTR__ZN4Aska18AHSLDISKCACHEMAGICE_02cbad60;
  *(undefined8 *)(param_1 + 0x17498) = 0;
  *(undefined8 *)(param_1 + 0x17490) = 0;
  *(undefined4 *)(param_1 + 0x17490) = *(undefined4 *)puVar1;
  *(undefined4 *)(param_1 + 0x17498) = *(undefined4 *)(param_1 + 0x17258);
  *(undefined2 *)(param_1 + 0x1749c) = 0;
  *(undefined4 *)(param_1 + 0x17494) = 0;
  memset(param_1 + 0x174b0,0,0x2000);
  uVar2 = Aska::ShaderKeyUtil::CalcCRC16(int, unsigned char const*)(0x2000,param_1 + 0x174b0);
  *(undefined2 *)(param_1 + 0x1748e) = uVar2;
  return;
}

// ==== Aska::AHSLCacheManagerV2::SetShaderCacheInfoNo(int)
// vaddr 0x20abe44 | ghidra 0x21abe44 | size 4 | symbol _ZN4Aska18AHSLCacheManagerV220SetShaderCacheInfoNoEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18AHSLCacheManagerV220SetShaderCacheInfoNoEi(void)

{
  return;
}

// ==== Aska::AHSLCacheManagerV2::LoadBootDiskCache()
// vaddr 0x20abe48 | ghidra 0x21abe48 | size 164 | symbol _ZN4Aska18AHSLCacheManagerV217LoadBootDiskCacheEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska18AHSLCacheManagerV217LoadBootDiskCacheEv(long param_1)

{
  undefined *puVar1;
  
  Aska::AHSLCacheManagerV2::AttachDiskCache(int, int)(param_1,0,1);
  puVar1 = PTR__ZN4Aska6Global24m_pSystemCallbackManagerE_02cb82c0;
  do {
    if (*(char *)(param_1 + 0x194b0) == '\0') {
      return 1;
    }
    if (*(char *)(param_1 + 0x30a18) != '\0') {
      Aska::Event::Set() const(param_1 + 0x30a20);
      Aska::Event::Wait(unsigned int) const(param_1 + 0x30a88,0);
      *(char *)(param_1 + 0x30a18) = '\0';
    }
  } while (*(char *)(*(long *)puVar1 + 8) == '\0');
  return 0;
}

// ==== Aska::AHSLCacheManagerV2::GetShaderCacheMajorShadersText(char*, int*, int*)
// vaddr 0x20abeec | ghidra 0x21abeec | size 8 | symbol _ZN4Aska18AHSLCacheManagerV230GetShaderCacheMajorShadersTextEPcPiS2_ | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska18AHSLCacheManagerV230GetShaderCacheMajorShadersTextEPcPiS2_(void)

{
  return 0;
}

// ==== Aska::AHSLCacheManagerV2::InformationDispMain(int)
// vaddr 0x20abef4 | ghidra 0x21abef4 | size 4 | symbol _ZN4Aska18AHSLCacheManagerV219InformationDispMainEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18AHSLCacheManagerV219InformationDispMainEi(void)

{
  return;
}

// ==== Aska::AHSLCacheManagerV2::L1::MallocEx(unsigned long)
// vaddr 0x20abef8 | ghidra 0x21abef8 | size 72 | symbol _ZN4Aska18AHSLCacheManagerV22L18MallocExEm | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska18AHSLCacheManagerV22L18MallocExEm(long param_1,undefined8 param_2)

{
  long lVar1;
  ulong uVar2;
  
  do {
    lVar1 = Aska::MemoryManager::Malloc(unsigned long)(param_1 + 0x17098,param_2);
    if (lVar1 != 0) {
      return lVar1;
    }
    uVar2 = Aska::AHSLCacheManagerV2::L1::DeleteColdCache()(param_1);
  } while ((uVar2 & 1) != 0);
  return 0;
}

// ==== Aska::AHSLCacheManagerV2::L1::DeleteColdCache()
// vaddr 0x20abf40 | ghidra 0x21abf40 | size 444 | symbol _ZN4Aska18AHSLCacheManagerV22L115DeleteColdCacheEv | lib libSOA-3.7.0.so | 2026-10-04
bool _ZN4Aska18AHSLCacheManagerV22L115DeleteColdCacheEv(long param_1)

{
  int *piVar1;
  int *piVar2;
  char cVar3;
  bool bVar4;
  long lVar5;
  ulong uVar6;
  int iVar7;
  
  piVar1 = (int *)(param_1 + 0x171d0);
  iVar7 = 0;
  do {
    while (*piVar1 == -1) {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = 0;
        cVar3 = ExclusiveMonitorsStatus();
      }
      if (cVar3 == '\0') goto code_r0x021ac038;
    }
    ClearExclusiveLocal();
    bVar4 = iVar7 < 0x1ff;
    iVar7 = iVar7 + 1;
  } while (bVar4);
  piVar2 = (int *)(param_1 + 0x171d4);
  do {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar4) {
      *piVar2 = *piVar2 + 1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
  do {
    if (*piVar1 != -1) {
      ClearExclusiveLocal();
      do {
        uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x17210);
        if ((uVar6 & 1) == 0) {
          do {
            cVar3 = '\x01';
            bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
            if (bVar4) {
              *piVar2 = *piVar2 + -1;
              cVar3 = ExclusiveMonitorsStatus();
            }
          } while (cVar3 != '\0');
          Aska::Thread::Sleep(unsigned int)(1);
        }
        else {
          Aska::Semaphore::Wait() const(param_1 + 0x17210);
        }
        do {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
          if (bVar4) {
            *piVar2 = *piVar2 + 1;
            cVar3 = ExclusiveMonitorsStatus();
          }
        } while (cVar3 != '\0');
        while (*piVar1 == -1) {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar4) {
            *piVar1 = 0;
            cVar3 = ExclusiveMonitorsStatus();
          }
          if (cVar3 == '\0') goto code_r0x021ac028;
        }
        ClearExclusiveLocal();
      } while( true );
    }
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar4) {
      *piVar1 = 0;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
code_r0x021ac028:
  do {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar4) {
      *piVar2 = *piVar2 + -1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
code_r0x021ac038:
  DataMemoryBarrier(2,3);
  lVar5 = Aska::AHSLCacheManagerV2::L1::SearchColdCache()(param_1);
  if (lVar5 != 0) {
    Aska::AHSLDatabase<Aska::ShaderCache, (unsigned char)9>::DeleteData(unsigned char*, Aska::ShaderCache*)(param_1,*(undefined8 *)(lVar5 + 0x18),lVar5);
    Aska::ShaderCache::FreeCache()(lVar5);
    Aska::MemoryManager::LocalFree(void*)(param_1 + 0x17098,lVar5);
    *(int *)(param_1 + 0x1718c) = *(int *)(param_1 + 0x1718c) + 1;
  }
  DataMemoryBarrier(2,3);
  *piVar1 = -1;
  DataMemoryBarrier(2,3);
  piVar1 = (int *)(param_1 + 0x171d4);
  if (0x14 < *piVar1) {
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
    uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x17210);
    if ((uVar6 & 1) != 0) {
      Aska::Semaphore::Signal() const(param_1 + 0x17210);
    }
  }
  return lVar5 != 0;
}

// ==== Aska::AHSLCacheManagerV2::L1::AlignedMallocEx(unsigned long, int)
// vaddr 0x20ac0fc | ghidra 0x21ac0fc | size 88 | symbol _ZN4Aska18AHSLCacheManagerV22L115AlignedMallocExEmi | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska18AHSLCacheManagerV22L115AlignedMallocExEmi
               (long param_1,undefined8 param_2,int param_3)

{
  long lVar1;
  ulong uVar2;
  
  do {
    lVar1 = Aska::MemoryManager::AlignedMalloc(unsigned long, long)(param_1 + 0x17098,param_2,(long)param_3);
    if (lVar1 != 0) {
      return lVar1;
    }
    uVar2 = Aska::AHSLCacheManagerV2::L1::DeleteColdCache()(param_1);
  } while ((uVar2 & 1) != 0);
  return 0;
}

// ==== Aska::AHSLCacheManagerV2::SearchBindedVS(Aska::ShaderCache*, unsigned long, int)
// vaddr 0x20ac154 | ghidra 0x21ac154 | size 1108 | symbol _ZN4Aska18AHSLCacheManagerV214SearchBindedVSEPNS_11ShaderCacheEmi | lib libSOA-3.7.0.so | 2026-10-04
undefined4 *
_ZN4Aska18AHSLCacheManagerV214SearchBindedVSEPNS_11ShaderCacheEmi
          (long param_1,long param_2,long param_3,undefined4 param_4)

{
  int *piVar1;
  int *piVar2;
  ushort uVar3;
  char cVar4;
  bool bVar5;
  int iVar6;
  ulong uVar7;
  ulong uVar8;
  long lVar9;
  undefined4 *puVar10;
  int *piVar11;
  long lVar12;
  
  piVar1 = (int *)(param_1 + 0x309a8);
  iVar6 = 0;
code_r0x021ac18c:
  if (*piVar1 == -1) {
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar5) {
      *piVar1 = 0;
      cVar4 = ExclusiveMonitorsStatus();
    }
    if (cVar4 == '\0') goto code_r0x021ac264;
    goto code_r0x021ac18c;
  }
  ClearExclusiveLocal();
  bVar5 = iVar6 < 0x1ff;
  iVar6 = iVar6 + 1;
  if (bVar5) goto code_r0x021ac18c;
  piVar2 = (int *)(param_1 + 0x309ac);
  do {
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar5) {
      *piVar2 = *piVar2 + 1;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
  do {
    if (*piVar1 != -1) {
      ClearExclusiveLocal();
      do {
        uVar7 = Aska::Semaphore::IsReady() const(param_1 + 0x309e8);
        if ((uVar7 & 1) == 0) {
          do {
            cVar4 = '\x01';
            bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
            if (bVar5) {
              *piVar2 = *piVar2 + -1;
              cVar4 = ExclusiveMonitorsStatus();
            }
          } while (cVar4 != '\0');
          Aska::Thread::Sleep(unsigned int)(1);
        }
        else {
          Aska::Semaphore::Wait() const(param_1 + 0x309e8);
        }
        do {
          cVar4 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
          if (bVar5) {
            *piVar2 = *piVar2 + 1;
            cVar4 = ExclusiveMonitorsStatus();
          }
        } while (cVar4 != '\0');
        while (*piVar1 == -1) {
          cVar4 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar5) {
            *piVar1 = 0;
            cVar4 = ExclusiveMonitorsStatus();
          }
          if (cVar4 == '\0') goto code_r0x021ac254;
        }
        ClearExclusiveLocal();
      } while( true );
    }
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar5) {
      *piVar1 = 0;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
code_r0x021ac254:
  do {
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar5) {
      *piVar2 = *piVar2 + -1;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
code_r0x021ac264:
  DataMemoryBarrier(2,3);
  piVar2 = (int *)(param_1 + 0x17200);
  iVar6 = 0;
code_r0x021ac27c:
  do {
    if (*piVar2 == -1) goto code_r0x021ac288;
    ClearExclusiveLocal();
    bVar5 = iVar6 < 0x1ff;
    iVar6 = iVar6 + 1;
  } while (bVar5);
  piVar11 = (int *)(param_1 + 0x17204);
  do {
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar11,0x10);
    if (bVar5) {
      *piVar11 = *piVar11 + 1;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
  do {
    if (*piVar2 != -1) {
      ClearExclusiveLocal();
      do {
        uVar7 = Aska::Semaphore::IsReady() const(param_1 + 0x17240);
        if ((uVar7 & 1) == 0) {
          do {
            cVar4 = '\x01';
            bVar5 = (bool)ExclusiveMonitorPass(piVar11,0x10);
            if (bVar5) {
              *piVar11 = *piVar11 + -1;
              cVar4 = ExclusiveMonitorsStatus();
            }
          } while (cVar4 != '\0');
          Aska::Thread::Sleep(unsigned int)(1);
        }
        else {
          Aska::Semaphore::Wait() const(param_1 + 0x17240);
        }
        do {
          cVar4 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(piVar11,0x10);
          if (bVar5) {
            *piVar11 = *piVar11 + 1;
            cVar4 = ExclusiveMonitorsStatus();
          }
        } while (cVar4 != '\0');
        while (*piVar2 == -1) {
          cVar4 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
          if (bVar5) {
            *piVar2 = 0;
            cVar4 = ExclusiveMonitorsStatus();
          }
          if (cVar4 == '\0') goto code_r0x021ac590;
        }
        ClearExclusiveLocal();
      } while( true );
    }
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar5) {
      *piVar2 = 0;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
code_r0x021ac590:
  do {
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar11,0x10);
    if (bVar5) {
      *piVar11 = *piVar11 + -1;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
  DataMemoryBarrier(2,3);
  goto code_r0x021ac2e8;
code_r0x021ac288:
  cVar4 = '\x01';
  bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
  if (bVar5) {
    *piVar2 = 0;
    cVar4 = ExclusiveMonitorsStatus();
  }
  if (cVar4 == '\0') goto code_r0x021ac2d8;
  goto code_r0x021ac27c;
code_r0x021ac2d8:
  DataMemoryBarrier(2,3);
code_r0x021ac2e8:
  piVar11 = (int *)(param_1 + 0x17204);
  *(undefined4 *)(param_2 + 0x48) = *(undefined4 *)(param_1 + 0x171c4);
  DataMemoryBarrier(2,3);
  *piVar2 = -1;
  DataMemoryBarrier(2,3);
  if (0x14 < *piVar11) {
    do {
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar11,0x10);
      if (bVar5) {
        *piVar11 = *piVar11 + -1;
        cVar4 = ExclusiveMonitorsStatus();
      }
    } while (cVar4 != '\0');
    uVar7 = Aska::Semaphore::IsReady() const(param_1 + 0x17240);
    if ((uVar7 & 1) != 0) {
      Aska::Semaphore::Signal() const(param_1 + 0x17240);
    }
  }
  uVar7 = (ulong)*(ushort *)(param_2 + 0x56);
  if (uVar7 != 0) {
    lVar9 = 0;
    do {
      if (*(long *)(*(long *)(param_2 + 0x40) + lVar9 * 8) == param_3) {
        puVar10 = *(undefined4 **)
                   (*(long *)(param_2 + 0x40) + (ulong)*(ushort *)(param_2 + 0x58) * 8 + lVar9 * 8);
        goto code_r0x021ac4ac;
      }
      lVar9 = lVar9 + 1;
    } while (lVar9 < (long)uVar7);
  }
  uVar3 = *(ushort *)(param_2 + 0x58);
  if (uVar3 == *(ushort *)(param_2 + 0x56)) {
    do {
      lVar9 = Aska::MemoryManager::Malloc(unsigned long)(param_1 + 0x170c8,(ulong)uVar3 << 5);
      if (lVar9 != 0) {
        lVar12 = uVar7 * 8;
        memcpy(lVar9,*(undefined8 *)(param_2 + 0x40),lVar12);
        memcpy(lVar9 + uVar7 * 0x10,*(long *)(param_2 + 0x40) + lVar12,lVar12);
        if (*(long *)(param_2 + 0x40) != 0) {
          Aska::MemoryManager::LocalFree(void*)(param_1 + 0x170c8);
        }
        *(long *)(param_2 + 0x40) = lVar9;
        *(ushort *)(param_2 + 0x58) = uVar3 << 1;
        goto code_r0x021ac410;
      }
      uVar8 = Aska::AHSLCacheManagerV2::L1::DeleteColdCache()(param_1 + 0x30);
    } while ((uVar8 & 1) != 0);
  }
  else {
code_r0x021ac410:
    do {
      puVar10 = (undefined4 *)Aska::MemoryManager::AlignedMalloc(unsigned long, long)(param_1 + 0x170c8,0x28,0x10);
      if (puVar10 != (undefined4 *)0x0) {
        *(long *)(puVar10 + 4) = param_2;
        *(long *)(puVar10 + 6) = param_3;
        iVar6 = Aska::RenderDeviceGL::CreateVertexDeclaration(unsigned long)(*(undefined8 *)PTR__ZN4Aska12g_pRenderDevE_02cbb1a0,param_3);
        if ((iVar6 != -1) && (*(long *)(param_2 + 0x28) != 0)) {
          *(long *)(puVar10 + 2) = *(long *)(param_2 + 0x28);
          puVar10[8] = iVar6;
          *puVar10 = param_4;
          uVar3 = *(ushort *)(param_2 + 0x58);
          lVar9 = (ulong)*(ushort *)(param_2 + 0x56) * 8;
          *(long *)(lVar9 + *(long *)(param_2 + 0x40)) = param_3;
          *(undefined4 **)(lVar9 + (ulong)uVar3 * 8 + *(long *)(param_2 + 0x40)) = puVar10;
          *(short *)(param_2 + 0x56) = *(short *)(param_2 + 0x56) + 1;
          goto code_r0x021ac4ac;
        }
        Aska::MemoryManager::LocalFree(void*)(param_1 + 0x170c8,puVar10);
        break;
      }
      uVar7 = Aska::AHSLCacheManagerV2::L1::DeleteColdCache()(param_1 + 0x30);
    } while ((uVar7 & 1) != 0);
  }
  puVar10 = (undefined4 *)0x0;
code_r0x021ac4ac:
  DataMemoryBarrier(2,3);
  *piVar1 = -1;
  DataMemoryBarrier(2,3);
  piVar1 = (int *)(param_1 + 0x309ac);
  if (0x14 < *piVar1) {
    do {
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar5) {
        *piVar1 = *piVar1 + -1;
        cVar4 = ExclusiveMonitorsStatus();
      }
    } while (cVar4 != '\0');
    uVar7 = Aska::Semaphore::IsReady() const(param_1 + 0x309e8);
    if ((uVar7 & 1) != 0) {
      Aska::Semaphore::Signal() const(param_1 + 0x309e8);
    }
  }
  return puVar10;
}

// ==== Aska::AHSLCacheManagerV2::UpdateLastCreation(Aska::ShaderCache*)
// vaddr 0x20ac5a8 | ghidra 0x21ac5a8 | size 4 | symbol _ZN4Aska18AHSLCacheManagerV218UpdateLastCreationEPNS_11ShaderCacheE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18AHSLCacheManagerV218UpdateLastCreationEPNS_11ShaderCacheE(void)

{
  return;
}

// ==== Aska::AHSLCacheManagerV2::SearchOrCompile(unsigned char const*, int*)
// vaddr 0x20ac5ac | ghidra 0x21ac5ac | size 652 | symbol _ZN4Aska18AHSLCacheManagerV215SearchOrCompileEPKhPi | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska18AHSLCacheManagerV215SearchOrCompileEPKhPi(long param_1,long param_2)

{
  int *piVar1;
  int *piVar2;
  char cVar3;
  bool bVar4;
  long lVar5;
  ulong uVar6;
  long lVar7;
  int iVar8;
  
  if ((*(char *)(param_2 + 2) == '\0') && (*(char *)(param_2 + 3) == '\0')) {
    return 0;
  }
  piVar1 = (int *)(param_1 + 0x17200);
  iVar8 = 0;
  do {
    while (*piVar1 == -1) {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = 0;
        cVar3 = ExclusiveMonitorsStatus();
      }
      if (cVar3 == '\0') goto code_r0x021ac6b8;
    }
    ClearExclusiveLocal();
    bVar4 = iVar8 < 0x1ff;
    iVar8 = iVar8 + 1;
  } while (bVar4);
  piVar2 = (int *)(param_1 + 0x17204);
  do {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar4) {
      *piVar2 = *piVar2 + 1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
  do {
    if (*piVar1 != -1) {
      ClearExclusiveLocal();
      do {
        uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x17240);
        if ((uVar6 & 1) == 0) {
          do {
            cVar3 = '\x01';
            bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
            if (bVar4) {
              *piVar2 = *piVar2 + -1;
              cVar3 = ExclusiveMonitorsStatus();
            }
          } while (cVar3 != '\0');
          Aska::Thread::Sleep(unsigned int)(1);
        }
        else {
          Aska::Semaphore::Wait() const(param_1 + 0x17240);
        }
        do {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
          if (bVar4) {
            *piVar2 = *piVar2 + 1;
            cVar3 = ExclusiveMonitorsStatus();
          }
        } while (cVar3 != '\0');
        while (*piVar1 == -1) {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar4) {
            *piVar1 = 0;
            cVar3 = ExclusiveMonitorsStatus();
          }
          if (cVar3 == '\0') goto code_r0x021ac6a8;
        }
        ClearExclusiveLocal();
      } while( true );
    }
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar4) {
      *piVar1 = 0;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
code_r0x021ac6a8:
  do {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar4) {
      *piVar2 = *piVar2 + -1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
code_r0x021ac6b8:
  DataMemoryBarrier(2,3);
  lVar5 = Aska::AHSLDatabase<Aska::ShaderCache, (unsigned char)9>::GetData(unsigned char const*)(param_1 + 0x30,param_2);
  if (lVar5 == 0) {
    DataMemoryBarrier(2,3);
    *piVar1 = -1;
    DataMemoryBarrier(2,3);
    piVar1 = (int *)(param_1 + 0x17204);
    if (0x14 < *piVar1) {
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
        if (bVar4) {
          *piVar1 = *piVar1 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x17240);
      if ((uVar6 & 1) != 0) {
        Aska::Semaphore::Signal() const(param_1 + 0x17240);
      }
    }
    lVar5 = Aska::AHSLDatabase<Aska::ShaderDiskCache, (unsigned char)9>::GetData(unsigned char const*)(param_1 + 0x198b8,param_2);
    if (lVar5 != 0) {
      if ((*(byte *)(lVar5 + 10) >> 5 & 1) == 0) {
        lVar7 = 0;
      }
      else {
        lVar7 = Aska::AHSLDatabase<Aska::ShaderDiskCache, (unsigned char)9>::GetData(unsigned char const*)(param_1 + 0x198b8,
                                *(undefined8 *)((ulong)*(ushort *)(lVar5 + 6) + lVar5 + 4));
        if (lVar7 == 0) {
          return 0;
        }
      }
      lVar5 = (*(code *)
                PTR__ZN4Aska18AHSLCacheManagerV212AddToL1CacheEPKNS_15ShaderDiskCacheES3__02c987e8)
                        (param_1,lVar5,lVar7);
      return lVar5;
    }
    *(int *)(param_1 + 0x171b8) = *(int *)(param_1 + 0x171b8) + 1;
    return 0;
  }
  *(undefined4 *)(lVar5 + 0x48) = *(undefined4 *)(param_1 + 0x171c4);
  DataMemoryBarrier(2,3);
  *piVar1 = -1;
  DataMemoryBarrier(2,3);
  piVar1 = (int *)(param_1 + 0x17204);
  if (*piVar1 < 0x15) {
    return lVar5;
  }
  do {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar4) {
      *piVar1 = *piVar1 + -1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
  uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x17240);
  if ((uVar6 & 1) != 0) {
    Aska::Semaphore::Signal() const(param_1 + 0x17240);
    return lVar5;
  }
  return lVar5;
}

// ==== Aska::AHSLDatabase<Aska::ShaderCache, (unsigned char)9>::GetData(unsigned char const*)
// vaddr 0x20ac838 | ghidra 0x21ac838 | size 656 | symbol _ZN4Aska12AHSLDatabaseINS_11ShaderCacheELh9EE7GetDataEPKh | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska12AHSLDatabaseINS_11ShaderCacheELh9EE7GetDataEPKh(long param_1,byte *param_2)

{
  int *piVar1;
  long *plVar2;
  uint uVar3;
  byte bVar4;
  byte bVar5;
  char cVar6;
  bool bVar7;
  long lVar8;
  int iVar9;
  int iVar10;
  ulong uVar11;
  long lVar12;
  long lVar13;
  int *piVar14;
  byte *pbVar15;
  ulong uVar16;
  long lVar17;
  long lVar18;
  long *plVar19;
  
  bVar5 = param_2[1];
  pbVar15 = param_2 + 2;
  bVar4 = *pbVar15;
  uVar11 = (ulong)(((uint)bVar5 << 0x10 | (uint)*param_2 << 0x18) >> 0x17);
  iVar9 = Aska::ShaderKeyUtil::GetShaderKeySize(unsigned char const*)(param_2);
  if (param_1 != 0) {
    piVar14 = (int *)(param_1 + 0x38);
    iVar10 = 0;
code_r0x021ac88c:
    do {
      if (*piVar14 == -1) goto code_r0x021ac898;
      ClearExclusiveLocal();
      bVar7 = iVar10 < 0x1ff;
      iVar10 = iVar10 + 1;
    } while (bVar7);
    piVar1 = (int *)(param_1 + 0x3c);
    do {
      cVar6 = '\x01';
      bVar7 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar7) {
        *piVar1 = *piVar1 + 1;
        cVar6 = ExclusiveMonitorsStatus();
      }
    } while (cVar6 != '\0');
    do {
      if (*piVar14 != -1) {
        ClearExclusiveLocal();
        do {
          uVar16 = Aska::Semaphore::IsReady() const(param_1 + 0x78);
          if ((uVar16 & 1) == 0) {
            do {
              cVar6 = '\x01';
              bVar7 = (bool)ExclusiveMonitorPass(piVar1,0x10);
              if (bVar7) {
                *piVar1 = *piVar1 + -1;
                cVar6 = ExclusiveMonitorsStatus();
              }
            } while (cVar6 != '\0');
            Aska::Thread::Sleep(unsigned int)(1);
          }
          else {
            Aska::Semaphore::Wait() const(param_1 + 0x78);
          }
          do {
            cVar6 = '\x01';
            bVar7 = (bool)ExclusiveMonitorPass(piVar1,0x10);
            if (bVar7) {
              *piVar1 = *piVar1 + 1;
              cVar6 = ExclusiveMonitorsStatus();
            }
          } while (cVar6 != '\0');
          while (*piVar14 == -1) {
            cVar6 = '\x01';
            bVar7 = (bool)ExclusiveMonitorPass(piVar14,0x10);
            if (bVar7) {
              *piVar14 = 0;
              cVar6 = ExclusiveMonitorsStatus();
            }
            if (cVar6 == '\0') goto code_r0x021ac944;
          }
          ClearExclusiveLocal();
        } while( true );
      }
      cVar6 = '\x01';
      bVar7 = (bool)ExclusiveMonitorPass(piVar14,0x10);
      if (bVar7) {
        *piVar14 = 0;
        cVar6 = ExclusiveMonitorsStatus();
      }
    } while (cVar6 != '\0');
code_r0x021ac944:
    do {
      cVar6 = '\x01';
      bVar7 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar7) {
        *piVar1 = *piVar1 + -1;
        cVar6 = ExclusiveMonitorsStatus();
      }
    } while (cVar6 != '\0');
code_r0x021ac954:
    DataMemoryBarrier(2,3);
  }
  lVar12 = param_1 + uVar11 * 0x98;
  uVar16 = (ulong)*(ushort *)(lVar12 + 0x409a);
  if (uVar16 != 0) {
    lVar18 = param_1 + uVar11 * 0x20;
    lVar17 = *(long *)(lVar18 + 0x90);
    uVar3 = (uint)bVar5 << 0x10 | (uint)bVar4 << 8;
    plVar2 = (long *)(lVar12 + 0x4090);
    lVar12 = 0;
    if (lVar17 == 0) {
      lVar17 = 0;
      do {
        if ((uint)*(byte *)(lVar18 + 0xa8 + lVar12) == (uVar3 >> 0xf & 0xff)) {
          lVar13 = *plVar2;
          lVar8 = param_1 + uVar11 * 0x98 + 0x40a8;
          if (lVar13 != 0) {
            lVar8 = lVar13;
          }
          plVar19 = (long *)(lVar8 + lVar17);
          iVar10 = memcmp(pbVar15,*plVar19 + 2,(long)(iVar9 + -2));
          if (iVar10 == 0) goto code_r0x021aca5c;
        }
        lVar12 = lVar12 + 1;
        lVar17 = lVar17 + 0x10;
      } while (lVar12 < (long)uVar16);
    }
    else {
      lVar18 = 0;
      do {
        if ((uint)*(byte *)(lVar17 + lVar18) == (uVar3 >> 0xf & 0xff)) {
          lVar13 = *plVar2;
          lVar8 = param_1 + uVar11 * 0x98 + 0x40a8;
          if (lVar13 != 0) {
            lVar8 = lVar13;
          }
          plVar19 = (long *)(lVar8 + lVar12);
          iVar10 = memcmp(pbVar15,*plVar19 + 2,(long)(iVar9 + -2));
          if (iVar10 == 0) goto code_r0x021aca5c;
        }
        lVar18 = lVar18 + 1;
        lVar12 = lVar12 + 0x10;
      } while (lVar18 < (long)uVar16);
    }
  }
  lVar12 = 0;
code_r0x021aca60:
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_1 + 0x38) = 0xffffffff;
  DataMemoryBarrier(2,3);
  piVar14 = (int *)(param_1 + 0x3c);
  if (0x14 < *piVar14) {
    do {
      cVar6 = '\x01';
      bVar7 = (bool)ExclusiveMonitorPass(piVar14,0x10);
      if (bVar7) {
        *piVar14 = *piVar14 + -1;
        cVar6 = ExclusiveMonitorsStatus();
      }
    } while (cVar6 != '\0');
    uVar11 = Aska::Semaphore::IsReady() const(param_1 + 0x78);
    if ((uVar11 & 1) != 0) {
      Aska::Semaphore::Signal() const(param_1 + 0x78);
    }
  }
  return lVar12;
code_r0x021ac898:
  cVar6 = '\x01';
  bVar7 = (bool)ExclusiveMonitorPass(piVar14,0x10);
  if (bVar7) {
    *piVar14 = 0;
    cVar6 = ExclusiveMonitorsStatus();
  }
  if (cVar6 == '\0') goto code_r0x021ac954;
  goto code_r0x021ac88c;
code_r0x021aca5c:
  lVar12 = plVar19[1];
  goto code_r0x021aca60;
}

// ==== Aska::AHSLDatabase<Aska::ShaderDiskCache, (unsigned char)9>::GetData(unsigned char const*)
// vaddr 0x20acac8 | ghidra 0x21acac8 | size 656 | symbol _ZN4Aska12AHSLDatabaseINS_15ShaderDiskCacheELh9EE7GetDataEPKh | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska12AHSLDatabaseINS_15ShaderDiskCacheELh9EE7GetDataEPKh(long param_1,byte *param_2)

{
  int *piVar1;
  long *plVar2;
  uint uVar3;
  byte bVar4;
  byte bVar5;
  char cVar6;
  bool bVar7;
  long lVar8;
  int iVar9;
  int iVar10;
  ulong uVar11;
  long lVar12;
  long lVar13;
  int *piVar14;
  byte *pbVar15;
  ulong uVar16;
  long lVar17;
  long lVar18;
  long *plVar19;
  
  bVar5 = param_2[1];
  pbVar15 = param_2 + 2;
  bVar4 = *pbVar15;
  uVar11 = (ulong)(((uint)bVar5 << 0x10 | (uint)*param_2 << 0x18) >> 0x17);
  iVar9 = Aska::ShaderKeyUtil::GetShaderKeySize(unsigned char const*)(param_2);
  if (param_1 != 0) {
    piVar14 = (int *)(param_1 + 0x38);
    iVar10 = 0;
code_r0x021acb1c:
    do {
      if (*piVar14 == -1) goto code_r0x021acb28;
      ClearExclusiveLocal();
      bVar7 = iVar10 < 0x1ff;
      iVar10 = iVar10 + 1;
    } while (bVar7);
    piVar1 = (int *)(param_1 + 0x3c);
    do {
      cVar6 = '\x01';
      bVar7 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar7) {
        *piVar1 = *piVar1 + 1;
        cVar6 = ExclusiveMonitorsStatus();
      }
    } while (cVar6 != '\0');
    do {
      if (*piVar14 != -1) {
        ClearExclusiveLocal();
        do {
          uVar16 = Aska::Semaphore::IsReady() const(param_1 + 0x78);
          if ((uVar16 & 1) == 0) {
            do {
              cVar6 = '\x01';
              bVar7 = (bool)ExclusiveMonitorPass(piVar1,0x10);
              if (bVar7) {
                *piVar1 = *piVar1 + -1;
                cVar6 = ExclusiveMonitorsStatus();
              }
            } while (cVar6 != '\0');
            Aska::Thread::Sleep(unsigned int)(1);
          }
          else {
            Aska::Semaphore::Wait() const(param_1 + 0x78);
          }
          do {
            cVar6 = '\x01';
            bVar7 = (bool)ExclusiveMonitorPass(piVar1,0x10);
            if (bVar7) {
              *piVar1 = *piVar1 + 1;
              cVar6 = ExclusiveMonitorsStatus();
            }
          } while (cVar6 != '\0');
          while (*piVar14 == -1) {
            cVar6 = '\x01';
            bVar7 = (bool)ExclusiveMonitorPass(piVar14,0x10);
            if (bVar7) {
              *piVar14 = 0;
              cVar6 = ExclusiveMonitorsStatus();
            }
            if (cVar6 == '\0') goto code_r0x021acbd4;
          }
          ClearExclusiveLocal();
        } while( true );
      }
      cVar6 = '\x01';
      bVar7 = (bool)ExclusiveMonitorPass(piVar14,0x10);
      if (bVar7) {
        *piVar14 = 0;
        cVar6 = ExclusiveMonitorsStatus();
      }
    } while (cVar6 != '\0');
code_r0x021acbd4:
    do {
      cVar6 = '\x01';
      bVar7 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar7) {
        *piVar1 = *piVar1 + -1;
        cVar6 = ExclusiveMonitorsStatus();
      }
    } while (cVar6 != '\0');
code_r0x021acbe4:
    DataMemoryBarrier(2,3);
  }
  lVar12 = param_1 + uVar11 * 0x98;
  uVar16 = (ulong)*(ushort *)(lVar12 + 0x409a);
  if (uVar16 != 0) {
    lVar18 = param_1 + uVar11 * 0x20;
    lVar17 = *(long *)(lVar18 + 0x90);
    uVar3 = (uint)bVar5 << 0x10 | (uint)bVar4 << 8;
    plVar2 = (long *)(lVar12 + 0x4090);
    lVar12 = 0;
    if (lVar17 == 0) {
      lVar17 = 0;
      do {
        if ((uint)*(byte *)(lVar18 + 0xa8 + lVar12) == (uVar3 >> 0xf & 0xff)) {
          lVar13 = *plVar2;
          lVar8 = param_1 + uVar11 * 0x98 + 0x40a8;
          if (lVar13 != 0) {
            lVar8 = lVar13;
          }
          plVar19 = (long *)(lVar8 + lVar17);
          iVar10 = memcmp(pbVar15,*plVar19 + 2,(long)(iVar9 + -2));
          if (iVar10 == 0) goto code_r0x021accec;
        }
        lVar12 = lVar12 + 1;
        lVar17 = lVar17 + 0x10;
      } while (lVar12 < (long)uVar16);
    }
    else {
      lVar18 = 0;
      do {
        if ((uint)*(byte *)(lVar17 + lVar18) == (uVar3 >> 0xf & 0xff)) {
          lVar13 = *plVar2;
          lVar8 = param_1 + uVar11 * 0x98 + 0x40a8;
          if (lVar13 != 0) {
            lVar8 = lVar13;
          }
          plVar19 = (long *)(lVar8 + lVar12);
          iVar10 = memcmp(pbVar15,*plVar19 + 2,(long)(iVar9 + -2));
          if (iVar10 == 0) goto code_r0x021accec;
        }
        lVar18 = lVar18 + 1;
        lVar12 = lVar12 + 0x10;
      } while (lVar18 < (long)uVar16);
    }
  }
  lVar12 = 0;
code_r0x021accf0:
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_1 + 0x38) = 0xffffffff;
  DataMemoryBarrier(2,3);
  piVar14 = (int *)(param_1 + 0x3c);
  if (0x14 < *piVar14) {
    do {
      cVar6 = '\x01';
      bVar7 = (bool)ExclusiveMonitorPass(piVar14,0x10);
      if (bVar7) {
        *piVar14 = *piVar14 + -1;
        cVar6 = ExclusiveMonitorsStatus();
      }
    } while (cVar6 != '\0');
    uVar11 = Aska::Semaphore::IsReady() const(param_1 + 0x78);
    if ((uVar11 & 1) != 0) {
      Aska::Semaphore::Signal() const(param_1 + 0x78);
    }
  }
  return lVar12;
code_r0x021acb28:
  cVar6 = '\x01';
  bVar7 = (bool)ExclusiveMonitorPass(piVar14,0x10);
  if (bVar7) {
    *piVar14 = 0;
    cVar6 = ExclusiveMonitorsStatus();
  }
  if (cVar6 == '\0') goto code_r0x021acbe4;
  goto code_r0x021acb1c;
code_r0x021accec:
  lVar12 = plVar19[1];
  goto code_r0x021accf0;
}

// ==== Aska::AHSLCacheManagerV2::AddToL1Cache(Aska::ShaderDiskCache const*, Aska::ShaderDiskCache const*)
// vaddr 0x20acd58 | ghidra 0x21acd58 | size 852 | symbol _ZN4Aska18AHSLCacheManagerV212AddToL1CacheEPKNS_15ShaderDiskCacheES3_ | lib libSOA-3.7.0.so | 2026-10-04
undefined8 *
_ZN4Aska18AHSLCacheManagerV212AddToL1CacheEPKNS_15ShaderDiskCacheES3_
          (long param_1,long param_2,long param_3)

{
  long lVar1;
  long lVar2;
  undefined8 *puVar3;
  long lVar4;
  int *piVar5;
  int *piVar6;
  uint uVar7;
  undefined4 uVar8;
  undefined2 uVar9;
  char cVar10;
  bool bVar11;
  int iVar12;
  int iVar13;
  long lVar14;
  undefined8 *puVar15;
  ulong uVar16;
  long lVar17;
  undefined8 *puVar18;
  int iVar19;
  undefined8 uVar20;
  undefined1 auStack_b060 [45056];
  
  if (10 < *(ushort *)(param_2 + 4) >> 0xc) {
    return (undefined8 *)0x0;
  }
  lVar1 = param_2 + 0xc;
  if (param_3 != 0) {
    param_2 = param_3;
  }
  lVar14 = Aska::AHSLBase::UncompressShaderCache(Aska::ShaderDiskCache*, Aska::ShaderDiskCache const*, unsigned char*)(param_1 + 0x18,auStack_b060,param_2,param_1 + 0x174b0);
  puVar18 = (undefined8 *)((ulong)*(ushort *)(lVar14 + 6) + lVar14);
  iVar12 = Aska::ShaderKeyUtil::GetTarget(unsigned char const*)(lVar1);
  iVar13 = Aska::ShaderKeyUtil::GetShaderKeySize(unsigned char const*)(lVar1);
  uVar7 = iVar13 + 3U & 0xfffffffc;
  iVar19 = uVar7 + (uint)*(ushort *)((long)puVar18 + 0x1e) * 4 + 0x60;
  lVar2 = param_1 + 0x30;
  lVar4 = param_1 + 0x170c8;
  while (puVar15 = (undefined8 *)Aska::MemoryManager::AlignedMalloc(unsigned long, long)(lVar4,(long)iVar19,0x10),
        puVar15 == (undefined8 *)0x0) {
    uVar16 = Aska::AHSLCacheManagerV2::L1::DeleteColdCache()(lVar2);
    if ((uVar16 & 1) == 0) {
      return (undefined8 *)0x0;
    }
  }
  memset(puVar15,0,0x60);
  if (iVar12 == 0) {
    while (lVar17 = Aska::MemoryManager::Malloc(unsigned long)(lVar4,0x80), lVar17 == 0) {
      uVar16 = Aska::AHSLCacheManagerV2::L1::DeleteColdCache()(lVar2);
      if ((uVar16 & 1) == 0) {
        puVar15[8] = 0;
        Aska::MemoryManager::LocalFree(void*)(lVar4,puVar15);
        return (undefined8 *)0x0;
      }
    }
    puVar15[8] = lVar17;
    *(undefined2 *)(puVar15 + 0xb) = 8;
  }
  puVar3 = puVar15 + 0xc;
  *puVar15 = *puVar18;
  puVar15[1] = puVar18[1];
  puVar15[2] = puVar18[2];
  *(undefined2 *)(puVar15 + 10) = *(undefined2 *)((long)puVar18 + 0x1e);
  uVar20 = puVar18[4];
  puVar15[3] = puVar3;
  puVar15[5] = uVar20;
  memcpy(puVar3,lVar1,(long)iVar13);
  lVar1 = (long)puVar3 + (long)(int)uVar7;
  puVar15[4] = lVar1;
  if ((ulong)*(ushort *)((long)puVar18 + 0x1e) != 0) {
    memcpy(lVar1,puVar18[5],(ulong)*(ushort *)((long)puVar18 + 0x1e) << 2);
  }
  uVar9 = *(undefined2 *)(lVar14 + 4);
  *(short *)((long)puVar15 + 0x52) = (short)iVar19;
  *(undefined2 *)((long)puVar15 + 0x54) = uVar9;
  uVar8 = *(undefined4 *)(param_1 + 0x171c4);
  piVar5 = (int *)(param_1 + 0x17200);
  *(undefined2 *)((long)puVar15 + 0x56) = 0;
  *(undefined4 *)(puVar15 + 9) = uVar8;
  *(undefined4 *)((long)puVar15 + 0x4c) = 0;
  puVar15[6] = 0;
  puVar15[7] = 0;
  iVar19 = 0;
  do {
    while (*piVar5 == -1) {
      cVar10 = '\x01';
      bVar11 = (bool)ExclusiveMonitorPass(piVar5,0x10);
      if (bVar11) {
        *piVar5 = 0;
        cVar10 = ExclusiveMonitorsStatus();
      }
      if (cVar10 == '\0') goto code_r0x021ad00c;
    }
    ClearExclusiveLocal();
    bVar11 = iVar19 < 0x1ff;
    iVar19 = iVar19 + 1;
  } while (bVar11);
  piVar6 = (int *)(param_1 + 0x17204);
  do {
    cVar10 = '\x01';
    bVar11 = (bool)ExclusiveMonitorPass(piVar6,0x10);
    if (bVar11) {
      *piVar6 = *piVar6 + 1;
      cVar10 = ExclusiveMonitorsStatus();
    }
  } while (cVar10 != '\0');
  do {
    if (*piVar5 != -1) {
      ClearExclusiveLocal();
      do {
        uVar16 = Aska::Semaphore::IsReady() const(param_1 + 0x17240);
        if ((uVar16 & 1) == 0) {
          do {
            cVar10 = '\x01';
            bVar11 = (bool)ExclusiveMonitorPass(piVar6,0x10);
            if (bVar11) {
              *piVar6 = *piVar6 + -1;
              cVar10 = ExclusiveMonitorsStatus();
            }
          } while (cVar10 != '\0');
          Aska::Thread::Sleep(unsigned int)(1);
        }
        else {
          Aska::Semaphore::Wait() const(param_1 + 0x17240);
        }
        do {
          cVar10 = '\x01';
          bVar11 = (bool)ExclusiveMonitorPass(piVar6,0x10);
          if (bVar11) {
            *piVar6 = *piVar6 + 1;
            cVar10 = ExclusiveMonitorsStatus();
          }
        } while (cVar10 != '\0');
        while (*piVar5 == -1) {
          cVar10 = '\x01';
          bVar11 = (bool)ExclusiveMonitorPass(piVar5,0x10);
          if (bVar11) {
            *piVar5 = 0;
            cVar10 = ExclusiveMonitorsStatus();
          }
          if (cVar10 == '\0') goto code_r0x021acffc;
        }
        ClearExclusiveLocal();
      } while( true );
    }
    cVar10 = '\x01';
    bVar11 = (bool)ExclusiveMonitorPass(piVar5,0x10);
    if (bVar11) {
      *piVar5 = 0;
      cVar10 = ExclusiveMonitorsStatus();
    }
  } while (cVar10 != '\0');
code_r0x021acffc:
  do {
    cVar10 = '\x01';
    bVar11 = (bool)ExclusiveMonitorPass(piVar6,0x10);
    if (bVar11) {
      *piVar6 = *piVar6 + -1;
      cVar10 = ExclusiveMonitorsStatus();
    }
  } while (cVar10 != '\0');
code_r0x021ad00c:
  DataMemoryBarrier(2,3);
  puVar18 = (undefined8 *)Aska::AHSLDatabase<Aska::ShaderCache, (unsigned char)9>::GetData(unsigned char const*)(lVar2,puVar15[3]);
  if (puVar18 == (undefined8 *)0x0) {
    Aska::AHSLDatabase<Aska::ShaderCache, (unsigned char)9>::SetData(unsigned char*, Aska::ShaderCache*)(lVar2,puVar15[3],puVar15);
  }
  else {
    Aska::ShaderCache::FreeCache()(puVar15);
    Aska::MemoryManager::LocalFree(void*)(lVar4,puVar15);
    puVar15 = puVar18;
  }
  DataMemoryBarrier(2,3);
  *piVar5 = -1;
  DataMemoryBarrier(2,3);
  piVar5 = (int *)(param_1 + 0x17204);
  if (*piVar5 < 0x15) {
    return puVar15;
  }
  do {
    cVar10 = '\x01';
    bVar11 = (bool)ExclusiveMonitorPass(piVar5,0x10);
    if (bVar11) {
      *piVar5 = *piVar5 + -1;
      cVar10 = ExclusiveMonitorsStatus();
    }
  } while (cVar10 != '\0');
  uVar16 = Aska::Semaphore::IsReady() const(param_1 + 0x17240);
  if ((uVar16 & 1) != 0) {
    Aska::Semaphore::Signal() const(param_1 + 0x17240);
    return puVar15;
  }
  return puVar15;
}

// ==== Aska::AHSLCacheManagerV2::Tick()
// vaddr 0x20ad0ac | ghidra 0x21ad0ac | size 104 | symbol _ZN4Aska18AHSLCacheManagerV24TickEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18AHSLCacheManagerV24TickEv(long param_1)

{
  if (*(char *)(param_1 + 0x30a18) != '\0') {
    Aska::Event::Set() const(param_1 + 0x30a20);
    Aska::Event::Wait(unsigned int) const(param_1 + 0x30a88,0);
    *(char *)(param_1 + 0x30a18) = '\0';
  }
  *(int *)(param_1 + 0x171c4) = *(int *)(param_1 + 0x171c4) + 1;
  return;
}

// ==== Aska::AHSLCacheManagerV2::Tick_RebuildCache()
// vaddr 0x20ad114 | ghidra 0x21ad114 | size 4 | symbol _ZN4Aska18AHSLCacheManagerV217Tick_RebuildCacheEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18AHSLCacheManagerV217Tick_RebuildCacheEv(void)

{
  return;
}

// ==== Aska::AHSLCacheManagerV2::ResetErrorShader()
// vaddr 0x20ad118 | ghidra 0x21ad118 | size 4 | symbol _ZN4Aska18AHSLCacheManagerV216ResetErrorShaderEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18AHSLCacheManagerV216ResetErrorShaderEv(void)

{
  return;
}

// ==== Aska::AHSLCacheManagerV2::L1::ReleaseAndDeleteShaderCache(Aska::ShaderCache*)
// vaddr 0x20ad11c | ghidra 0x21ad11c | size 124 | symbol _ZN4Aska18AHSLCacheManagerV22L127ReleaseAndDeleteShaderCacheEPNS_11ShaderCacheE | lib libSOA-3.7.0.so | 2026-10-04
undefined4
_ZN4Aska18AHSLCacheManagerV22L127ReleaseAndDeleteShaderCacheEPNS_11ShaderCacheE
          (long param_1,long param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = *(int *)(param_2 + 0x4c) + -1;
  *(int *)(param_2 + 0x4c) = iVar1;
  if (iVar1 == 0) {
    Aska::AHSLDatabase<Aska::ShaderCache, (unsigned char)9>::DeleteData(unsigned char*, Aska::ShaderCache*)(param_1,*(undefined8 *)(param_2 + 0x18),param_2);
    uVar2 = Aska::ShaderCache::FreeCache()(param_2);
    Aska::MemoryManager::LocalFree(void*)(param_1 + 0x17098,param_2);
    *(int *)(param_1 + 0x1718c) = *(int *)(param_1 + 0x1718c) + 1;
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

// ==== Aska::AHSLCacheManagerV2::L1::DeleteFromL1Cache(Aska::ShaderCache*)
// vaddr 0x20ad198 | ghidra 0x21ad198 | size 100 | symbol _ZN4Aska18AHSLCacheManagerV22L117DeleteFromL1CacheEPNS_11ShaderCacheE | lib libSOA-3.7.0.so | 2026-10-04
undefined4
_ZN4Aska18AHSLCacheManagerV22L117DeleteFromL1CacheEPNS_11ShaderCacheE(long param_1,long param_2)

{
  undefined4 uVar1;
  
  Aska::AHSLDatabase<Aska::ShaderCache, (unsigned char)9>::DeleteData(unsigned char*, Aska::ShaderCache*)(param_1,*(undefined8 *)(param_2 + 0x18),param_2);
  uVar1 = Aska::ShaderCache::FreeCache()(param_2);
  if (param_2 != 0) {
    Aska::MemoryManager::LocalFree(void*)(param_1 + 0x17098,param_2);
  }
  *(int *)(param_1 + 0x1718c) = *(int *)(param_1 + 0x1718c) + 1;
  return uVar1;
}

// ==== Aska::AHSLCacheManagerV2::GetBackendCompilingShaderCaches() const
// vaddr 0x20ad1fc | ghidra 0x21ad1fc | size 16 | symbol _ZNK4Aska18AHSLCacheManagerV231GetBackendCompilingShaderCachesEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK4Aska18AHSLCacheManagerV231GetBackendCompilingShaderCachesEv(void)

{
  (*(code *)PTR__ZNK4Aska14RenderDeviceGL31GetBackendCompilingShaderCachesEv_02ca67b8)
            (*(undefined8 *)PTR__ZN4Aska12g_pRenderDevE_02cbb1a0);
  return;
}

// ==== Aska::AHSLCacheManagerV2::EnableBackendCompilingShaderCaches(bool)
// vaddr 0x20ad20c | ghidra 0x21ad20c | size 20 | symbol _ZN4Aska18AHSLCacheManagerV234EnableBackendCompilingShaderCachesEb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18AHSLCacheManagerV234EnableBackendCompilingShaderCachesEb
               (undefined8 param_1,uint param_2)

{
  (*(code *)PTR__ZN4Aska14RenderDeviceGL34EnableBackendCompilingShaderCachesEb_02ca72f8)
            (*(undefined8 *)PTR__ZN4Aska12g_pRenderDevE_02cbb1a0,param_2 & 1);
  return;
}

// ==== Aska::AHSLCacheManagerV2::IsBackendCompilingShaderCachesEnabled() const
// vaddr 0x20ad220 | ghidra 0x21ad220 | size 16 | symbol _ZNK4Aska18AHSLCacheManagerV237IsBackendCompilingShaderCachesEnabledEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK4Aska18AHSLCacheManagerV237IsBackendCompilingShaderCachesEnabledEv(void)

{
  (*(code *)PTR__ZNK4Aska14RenderDeviceGL37IsBackendCompilingShaderCachesEnabledEv_02c9b058)
            (*(undefined8 *)PTR__ZN4Aska12g_pRenderDevE_02cbb1a0);
  return;
}

// ==== Aska::AHSLCacheManagerV2::SetBackendCompilingShaderCachesPerFrame(unsigned int)
// vaddr 0x20ad230 | ghidra 0x21ad230 | size 16 | symbol _ZN4Aska18AHSLCacheManagerV239SetBackendCompilingShaderCachesPerFrameEj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18AHSLCacheManagerV239SetBackendCompilingShaderCachesPerFrameEj(void)

{
  (*(code *)PTR__ZN4Aska14RenderDeviceGL39SetBackendCompilingShaderCachesPerFrameEj_02c91d10)
            (*(undefined8 *)PTR__ZN4Aska12g_pRenderDevE_02cbb1a0);
  return;
}

// ==== Aska::AHSLCacheManagerV2::GetBackendCompilingShaderCachesPerFrame() const
// vaddr 0x20ad240 | ghidra 0x21ad240 | size 16 | symbol _ZNK4Aska18AHSLCacheManagerV239GetBackendCompilingShaderCachesPerFrameEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK4Aska18AHSLCacheManagerV239GetBackendCompilingShaderCachesPerFrameEv(void)

{
  (*(code *)PTR__ZNK4Aska14RenderDeviceGL39GetBackendCompilingShaderCachesPerFrameEv_02cb2938)
            (*(undefined8 *)PTR__ZN4Aska12g_pRenderDevE_02cbb1a0);
  return;
}

// ==== Aska::AHSLCacheManagerV2::EnableDeleteShaderCaches(bool)
// vaddr 0x20ad250 | ghidra 0x21ad250 | size 20 | symbol _ZN4Aska18AHSLCacheManagerV224EnableDeleteShaderCachesEb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18AHSLCacheManagerV224EnableDeleteShaderCachesEb(undefined8 param_1,uint param_2)

{
  (*(code *)PTR__ZN4Aska14RenderDeviceGL24EnableDeleteShaderCachesEb_02cb48e0)
            (*(undefined8 *)PTR__ZN4Aska12g_pRenderDevE_02cbb1a0,param_2 & 1);
  return;
}

// ==== Aska::AHSLCacheManagerV2::AddToL2Cache(Aska::ShaderDiskCache const*)
// vaddr 0x20ad264 | ghidra 0x21ad264 | size 68 | symbol _ZN4Aska18AHSLCacheManagerV212AddToL2CacheEPKNS_15ShaderDiskCacheE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18AHSLCacheManagerV212AddToL2CacheEPKNS_15ShaderDiskCacheE(long param_1,long param_2)

{
  ulong uVar1;
  
  uVar1 = Aska::AHSLCacheManagerV2::BuildLinkedDiskCacheL2(Aska::ShaderDiskCache const*)();
  if ((uVar1 & 1) != 0) {
    (*(code *)PTR__ZN4Aska12AHSLDatabaseINS_15ShaderDiskCacheELh9EE7SetDataEPhPS1__02caa3e0)
              (param_1 + 0x198b8,param_2 + 0xc,param_2);
    return;
  }
  return;
}

// ==== Aska::AHSLCacheManagerV2::BuildLinkedDiskCacheL2(Aska::ShaderDiskCache const*)
// vaddr 0x20ad2a8 | ghidra 0x21ad2a8 | size 616 | symbol _ZN4Aska18AHSLCacheManagerV222BuildLinkedDiskCacheL2EPKNS_15ShaderDiskCacheE | lib libSOA-3.7.0.so | 2026-10-04
int _ZN4Aska18AHSLCacheManagerV222BuildLinkedDiskCacheL2EPKNS_15ShaderDiskCacheE
              (long param_1,long param_2)

{
  long lVar1;
  long lVar2;
  undefined *puVar3;
  int iVar4;
  int iVar5;
  long lVar6;
  long *plVar7;
  ulong uVar8;
  long lVar9;
  undefined8 uVar10;
  int iVar11;
  byte abStack_160d0 [8];
  undefined8 uStack_160c8;
  long lStack_160c0;
  undefined1 auStack_16060 [45056];
  undefined1 auStack_b060 [45056];
  
  if ((*(byte *)(param_2 + 10) >> 5 & 1) != 0) {
    return 1;
  }
  lVar1 = param_2 + 0xc;
  abStack_160d0[0] = 0;
  uStack_160c8 = 0;
  lStack_160c0 = 0;
  Aska::ShaderKeyUtil::Attach(unsigned char const*)(abStack_160d0,lVar1);
  iVar4 = Aska::ShaderKeyUtil::GetKind()(abStack_160d0);
  iVar5 = Aska::ShaderKeyUtil::GetTarget()(abStack_160d0);
  lVar2 = param_1 + 0x18;
  uVar10 = *(undefined8 *)PTR__ZN4Aska12g_pRenderDevE_02cbb1a0;
  param_1 = param_1 + 0x174b0;
  lVar6 = Aska::AHSLBase::UncompressShaderCache(Aska::ShaderDiskCache*, Aska::ShaderDiskCache const*, unsigned char*)(lVar2,auStack_16060,param_2,param_1);
  lVar9 = (ulong)*(ushort *)(lVar6 + 6) + lVar6;
  if (iVar5 == 1) {
    plVar7 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x48,PTR__ZSt7nothrow_02cb9a80);
    if (plVar7 != (long *)0x0) {
      Aska::Shader::Shader()(plVar7);
      *plVar7 = (long)(PTR__ZTVN4Aska11PixelShaderE_02cba750 + 0x10);
    }
    *(long **)(lVar9 + 0x20) = plVar7;
    uVar8 = Aska::RenderDeviceGL::CreateShaderFromMemory(char const*, Aska::PixelShader*, Aska::AHSLShaderConstListKind::E, unsigned char const*, int, Aska::ConstAssign**, unsigned short*, unsigned short*)(uVar10,(ulong)*(ushort *)(lVar9 + 0x1a) + lVar6,plVar7,iVar4 == 2,lVar1,
                            0xffffffff,lVar9 + 0x28,lVar9 + 0x1e,lVar9 + 0x10);
  }
  else {
    iVar11 = 0;
    if (iVar5 != 0) goto code_r0x021ad440;
    plVar7 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x178,PTR__ZSt7nothrow_02cb9a80);
    if (plVar7 != (long *)0x0) {
      Aska::Shader::Shader()(plVar7);
      puVar3 = PTR__ZTVN4Aska12VertexShaderE_02cbfe20;
      plVar7[0x2e] = 0;
      *plVar7 = (long)(puVar3 + 0x10);
    }
    *(long **)(lVar9 + 0x20) = plVar7;
    uVar8 = Aska::RenderDeviceGL::CreateShaderFromMemory(char const*, Aska::VertexShader*, Aska::AHSLShaderConstListKind::E, unsigned char const*, int, Aska::ConstAssign**, unsigned short*, unsigned short*)(uVar10,(ulong)*(ushort *)(lVar9 + 0x1a) + lVar6,plVar7,iVar4 == 2,lVar1,
                            0xffffffff,lVar9 + 0x28,lVar9 + 0x1e,lVar9 + 0x10);
  }
  if ((uVar8 & 1) == 0) {
    iVar11 = 0;
  }
  else {
    iVar11 = 1;
  }
code_r0x021ad440:
  if ((*(byte *)(param_2 + 10) & 3) != 0) {
    Aska::AHSLBase::CreateCompressedShaderCache(Aska::ShaderDiskCache*, void*, unsigned char*)(lVar2,lVar6,param_2,param_1);
  }
  if (iVar11 == 0) {
    lVar9 = Aska::AHSLBase::UncompressShaderCache(Aska::ShaderDiskCache*, Aska::ShaderDiskCache const*, unsigned char*)(lVar2,auStack_b060,param_2,param_1);
    lVar1 = (ulong)*(ushort *)(lVar9 + 6) + lVar9;
    if (*(long **)(lVar1 + 0x20) != (long *)0x0) {
      (**(code **)(**(long **)(lVar1 + 0x20) + 8))();
      *(undefined8 *)(lVar1 + 0x20) = 0;
    }
    if (*(long *)(lVar1 + 0x28) != 0) {
      operator delete[](void*)();
      *(undefined8 *)(lVar1 + 0x28) = 0;
    }
    if ((*(byte *)(param_2 + 10) & 3) != 0) {
      Aska::AHSLBase::CreateCompressedShaderCache(Aska::ShaderDiskCache*, void*, unsigned char*)(lVar2,lVar9,param_2,param_1);
    }
  }
  if (((abStack_160d0[0] & 1) != 0) && (lStack_160c0 != 0)) {
    operator delete[](void*)();
  }
  return iVar11;
}

// ==== Aska::AHSLDatabase<Aska::ShaderDiskCache, (unsigned char)9>::SetData(unsigned char*, Aska::ShaderDiskCache*)
// vaddr 0x20ad510 | ghidra 0x21ad510 | size 996 | symbol _ZN4Aska12AHSLDatabaseINS_15ShaderDiskCacheELh9EE7SetDataEPhPS1_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska12AHSLDatabaseINS_15ShaderDiskCacheELh9EE7SetDataEPhPS1_
               (long param_1,byte *param_2,undefined8 param_3)

{
  int *piVar1;
  long lVar2;
  undefined1 *puVar3;
  undefined8 *puVar4;
  byte bVar5;
  byte bVar6;
  char cVar7;
  bool bVar8;
  long lVar9;
  int iVar10;
  long lVar11;
  int *piVar12;
  long lVar13;
  long lVar14;
  ulong uVar15;
  long *plVar16;
  ulong uVar17;
  ushort *puVar18;
  
  bVar5 = param_2[1];
  bVar6 = param_2[2];
  uVar15 = (ulong)(((uint)bVar5 << 0x10 | (uint)*param_2 << 0x18) >> 0x17);
  if (param_1 != 0) {
    piVar12 = (int *)(param_1 + 0x38);
    iVar10 = 0;
code_r0x021ad560:
    do {
      if (*piVar12 == -1) goto code_r0x021ad56c;
      ClearExclusiveLocal();
      bVar8 = iVar10 < 0x1ff;
      iVar10 = iVar10 + 1;
    } while (bVar8);
    piVar1 = (int *)(param_1 + 0x3c);
    do {
      cVar7 = '\x01';
      bVar8 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar8) {
        *piVar1 = *piVar1 + 1;
        cVar7 = ExclusiveMonitorsStatus();
      }
    } while (cVar7 != '\0');
    do {
      if (*piVar12 != -1) {
        ClearExclusiveLocal();
        do {
          uVar17 = Aska::Semaphore::IsReady() const(param_1 + 0x78);
          if ((uVar17 & 1) == 0) {
            do {
              cVar7 = '\x01';
              bVar8 = (bool)ExclusiveMonitorPass(piVar1,0x10);
              if (bVar8) {
                *piVar1 = *piVar1 + -1;
                cVar7 = ExclusiveMonitorsStatus();
              }
            } while (cVar7 != '\0');
            Aska::Thread::Sleep(unsigned int)(1);
          }
          else {
            Aska::Semaphore::Wait() const(param_1 + 0x78);
          }
          do {
            cVar7 = '\x01';
            bVar8 = (bool)ExclusiveMonitorPass(piVar1,0x10);
            if (bVar8) {
              *piVar1 = *piVar1 + 1;
              cVar7 = ExclusiveMonitorsStatus();
            }
          } while (cVar7 != '\0');
          while (*piVar12 == -1) {
            cVar7 = '\x01';
            bVar8 = (bool)ExclusiveMonitorPass(piVar12,0x10);
            if (bVar8) {
              *piVar12 = 0;
              cVar7 = ExclusiveMonitorsStatus();
            }
            if (cVar7 == '\0') goto code_r0x021ad8d8;
          }
          ClearExclusiveLocal();
        } while( true );
      }
      cVar7 = '\x01';
      bVar8 = (bool)ExclusiveMonitorPass(piVar12,0x10);
      if (bVar8) {
        *piVar12 = 0;
        cVar7 = ExclusiveMonitorsStatus();
      }
    } while (cVar7 != '\0');
code_r0x021ad8d8:
    do {
      cVar7 = '\x01';
      bVar8 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar8) {
        *piVar1 = *piVar1 + -1;
        cVar7 = ExclusiveMonitorsStatus();
      }
    } while (cVar7 != '\0');
    DataMemoryBarrier(2,3);
  }
code_r0x021ad5bc:
  lVar2 = param_1 + uVar15 * 0x20;
  puVar18 = (ushort *)(lVar2 + 0x9a);
  uVar17 = (ulong)*puVar18;
  plVar16 = (long *)(lVar2 + 0x90);
  if (*puVar18 < *(ushort *)(lVar2 + 0x98)) {
    lVar14 = *plVar16;
code_r0x021ad688:
    puVar3 = (undefined1 *)(param_1 + uVar15 * 0x20 + uVar17 + 0xa8);
    if (lVar14 != 0) {
      puVar3 = (undefined1 *)(lVar14 + uVar17);
    }
    *puVar18 = (ushort)(uVar17 + 1);
    *puVar3 = (char)(((uint)bVar5 << 0x10 | (uint)bVar6 << 8) >> 0xf);
  }
  else {
    lVar13 = *plVar16;
    lVar14 = *(long *)(lVar2 + 0xa0);
    lVar9 = (uVar17 + 1) * 2;
    if (lVar13 == 0) {
      if (lVar14 == 0) {
        lVar14 = operator new[](unsigned long, std::nothrow_t const&)(lVar9,PTR__ZSt7nothrow_02cb9a80);
      }
      else {
        lVar14 = Aska::MemoryManager::Malloc(unsigned long)(lVar14,lVar9);
      }
      if (lVar14 != 0) {
        memcpy(lVar14,param_1 + uVar15 * 0x20 + 0xa8,*puVar18);
        goto code_r0x021ad67c;
      }
    }
    else {
      if (lVar14 == 0) {
        lVar14 = operator new[](unsigned long, void*, unsigned long)(lVar9,lVar13,4);
      }
      else {
        lVar14 = Aska::MemoryManager::Realloc(unsigned long, void*, long)(lVar14,lVar9,lVar13,4);
      }
      if (lVar14 != 0) {
code_r0x021ad67c:
        *plVar16 = lVar14;
        *(ushort *)(lVar2 + 0x98) = (ushort)lVar9;
        goto code_r0x021ad688;
      }
    }
  }
  lVar14 = param_1 + uVar15 * 0x98;
  puVar18 = (ushort *)(lVar14 + 0x409a);
  uVar17 = (ulong)*puVar18;
  plVar16 = (long *)(lVar14 + 0x4090);
  lVar2 = uVar17 + 1;
  if (*puVar18 < *(ushort *)(lVar14 + 0x4098)) {
    lVar13 = *plVar16;
  }
  else {
    lVar11 = *plVar16;
    lVar13 = *(long *)(param_1 + uVar15 * 0x98 + 0x40a0);
    lVar9 = lVar2 * 0x20;
    if (lVar11 == 0) {
      if (lVar13 == 0) {
        lVar13 = operator new[](unsigned long, std::nothrow_t const&)(lVar9,PTR__ZSt7nothrow_02cb9a80);
      }
      else {
        lVar13 = Aska::MemoryManager::Malloc(unsigned long)();
      }
      if (lVar13 != 0) {
        memcpy(lVar13,param_1 + uVar15 * 0x98 + 0x40a8,(ulong)*puVar18 << 4);
      }
    }
    else if (lVar13 == 0) {
      lVar13 = operator new[](unsigned long, void*, unsigned long)(lVar9,lVar11,4);
    }
    else {
      lVar13 = Aska::MemoryManager::Realloc(unsigned long, void*, long)(lVar13,lVar9,lVar11,4);
    }
    if (lVar13 == 0) {
      lVar13 = *plVar16;
      uVar17 = (ulong)*puVar18 - 1;
      goto code_r0x021ad7a0;
    }
    *plVar16 = lVar13;
    *(ushort *)(lVar14 + 0x4098) = (ushort)((int)lVar2 << 1);
  }
  *puVar18 = (ushort)lVar2;
code_r0x021ad7a0:
  puVar4 = (undefined8 *)(param_1 + uVar15 * 0x98 + uVar17 * 0x10 + 0x40a8);
  if (lVar13 != 0) {
    puVar4 = (undefined8 *)(lVar13 + uVar17 * 0x10);
  }
  *puVar4 = param_2;
  puVar4[1] = param_3;
  *(int *)(param_1 + 0x17090) = *(int *)(param_1 + 0x17090) + 1;
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_1 + 0x38) = 0xffffffff;
  DataMemoryBarrier(2,3);
  piVar12 = (int *)(param_1 + 0x3c);
  if (0x14 < *piVar12) {
    do {
      cVar7 = '\x01';
      bVar8 = (bool)ExclusiveMonitorPass(piVar12,0x10);
      if (bVar8) {
        *piVar12 = *piVar12 + -1;
        cVar7 = ExclusiveMonitorsStatus();
      }
    } while (cVar7 != '\0');
    uVar15 = Aska::Semaphore::IsReady() const(param_1 + 0x78);
    if ((uVar15 & 1) != 0) {
      (*(code *)PTR__ZNK4Aska9Semaphore6SignalEv_02c96cd0)(param_1 + 0x78);
      return;
    }
  }
  return;
code_r0x021ad56c:
  cVar7 = '\x01';
  bVar8 = (bool)ExclusiveMonitorPass(piVar12,0x10);
  if (bVar8) {
    *piVar12 = 0;
    cVar7 = ExclusiveMonitorsStatus();
  }
  if (cVar7 == '\0') goto code_r0x021ad5b8;
  goto code_r0x021ad560;
code_r0x021ad5b8:
  DataMemoryBarrier(2,3);
  goto code_r0x021ad5bc;
}

// ==== Aska::AHSLCacheManagerV2::CleanLinkedDiskCacheL2(Aska::ShaderDiskCache const*)
// vaddr 0x20ad8f4 | ghidra 0x21ad8f4 | size 172 | symbol _ZN4Aska18AHSLCacheManagerV222CleanLinkedDiskCacheL2EPKNS_15ShaderDiskCacheE | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska18AHSLCacheManagerV222CleanLinkedDiskCacheL2EPKNS_15ShaderDiskCacheE
          (long param_1,long param_2)

{
  long lVar1;
  long lVar2;
  undefined1 auStack_b040 [45056];
  
  lVar2 = Aska::AHSLBase::UncompressShaderCache(Aska::ShaderDiskCache*, Aska::ShaderDiskCache const*, unsigned char*)(param_1 + 0x18,auStack_b040,param_2,param_1 + 0x174b0);
  lVar1 = (ulong)*(ushort *)(lVar2 + 6) + lVar2;
  if (*(long **)(lVar1 + 0x20) != (long *)0x0) {
    (**(code **)(**(long **)(lVar1 + 0x20) + 8))();
    *(undefined8 *)(lVar1 + 0x20) = 0;
  }
  if (*(long *)(lVar1 + 0x28) != 0) {
    operator delete[](void*)();
    *(undefined8 *)(lVar1 + 0x28) = 0;
  }
  if ((*(byte *)(param_2 + 10) & 3) != 0) {
    Aska::AHSLBase::CreateCompressedShaderCache(Aska::ShaderDiskCache*, void*, unsigned char*)(param_1 + 0x18,lVar2,param_2,param_1 + 0x174b0);
  }
  return 1;
}

// ==== Aska::AHSLCacheManagerV2::IsValidFileCacheHeader(Aska::AHSLFileCacheHeader const*, bool)
// vaddr 0x20ad9ac | ghidra 0x21ad9ac | size 88 | symbol _ZN4Aska18AHSLCacheManagerV222IsValidFileCacheHeaderEPKNS_19AHSLFileCacheHeaderEb | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska18AHSLCacheManagerV222IsValidFileCacheHeaderEPKNS_19AHSLFileCacheHeaderEb
          (long param_1,int *param_2)

{
  if (((*param_2 == *(int *)PTR__ZN4Aska18AHSLDISKCACHEMAGICE_02cbad60) &&
      ((short)param_2[2] == *(short *)(param_1 + 0x17258))) &&
     (*(short *)((long)param_2 + 10) == *(short *)(param_1 + 0x1725a))) {
    return 1;
  }
  return 0;
}

// ==== Aska::AHSLCacheManagerV2::L1::PurgeNonDrewL1Cache(int)
// vaddr 0x20ada04 | ghidra 0x21ada04 | size 852 | symbol _ZN4Aska18AHSLCacheManagerV22L119PurgeNonDrewL1CacheEi | lib libSOA-3.7.0.so | 2026-10-04
int _ZN4Aska18AHSLCacheManagerV22L119PurgeNonDrewL1CacheEi(long param_1,int param_2)

{
  bool bVar1;
  int *piVar2;
  int *piVar3;
  ushort *puVar4;
  ushort uVar5;
  char cVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  long lVar12;
  ulong uVar13;
  long *plVar14;
  long lVar15;
  uint uVar16;
  
  lVar15 = param_1 + 0x17098;
  iVar7 = Aska::MemoryManager::CalcFreeSize(bool)(lVar15,0);
  if (param_2 <= iVar7) {
    return iVar7;
  }
  puVar4 = (ushort *)(param_1 + 0x17190);
  uVar5 = *puVar4;
  if (uVar5 < 0x200) {
    uVar16 = (uint)uVar5;
    do {
      iVar8 = Aska::AHSLDatabase<Aska::ShaderCache, (unsigned char)9>::GetNodeCount(int) const(param_1,uVar16);
      if (0 < iVar8) {
        iVar10 = 0;
        do {
          lVar12 = Aska::AHSLDatabase<Aska::ShaderCache, (unsigned char)9>::GetNodeDirect(int, int)(param_1,uVar16,iVar10);
          if (*(int *)(lVar12 + 0x4c) == 0) {
            *puVar4 = (ushort)uVar16;
            Aska::AHSLDatabase<Aska::ShaderCache, (unsigned char)9>::DeleteData(unsigned char*, Aska::ShaderCache*)(param_1,*(undefined8 *)(lVar12 + 0x18),lVar12);
            iVar9 = Aska::ShaderCache::FreeCache()(lVar12);
            if (lVar12 != 0) {
              Aska::MemoryManager::LocalFree(void*)(lVar15,lVar12);
            }
            iVar7 = iVar9 + iVar7;
            *(int *)(param_1 + 0x1718c) = *(int *)(param_1 + 0x1718c) + 1;
            if (param_2 <= iVar7) {
              return iVar7;
            }
          }
          iVar10 = iVar10 + 1;
        } while (iVar10 < iVar8);
      }
      bVar1 = (int)uVar16 < 0x1ff;
      uVar16 = uVar16 + 1;
    } while (bVar1);
    if (uVar5 == 0) goto code_r0x021adbc0;
  }
  iVar8 = 0;
  do {
    iVar10 = Aska::AHSLDatabase<Aska::ShaderCache, (unsigned char)9>::GetNodeCount(int) const(param_1,iVar8);
    if (0 < iVar10) {
      iVar9 = 0;
      do {
        lVar12 = Aska::AHSLDatabase<Aska::ShaderCache, (unsigned char)9>::GetNodeDirect(int, int)(param_1,iVar8,iVar9);
        if (*(int *)(lVar12 + 0x4c) == 0) {
          *puVar4 = (ushort)iVar8;
          Aska::AHSLDatabase<Aska::ShaderCache, (unsigned char)9>::DeleteData(unsigned char*, Aska::ShaderCache*)(param_1,*(undefined8 *)(lVar12 + 0x18),lVar12);
          iVar11 = Aska::ShaderCache::FreeCache()(lVar12);
          if (lVar12 != 0) {
            Aska::MemoryManager::LocalFree(void*)(lVar15,lVar12);
          }
          iVar7 = iVar11 + iVar7;
          *(int *)(param_1 + 0x1718c) = *(int *)(param_1 + 0x1718c) + 1;
          if (param_2 <= iVar7) {
            return iVar7;
          }
        }
        iVar9 = iVar9 + 1;
      } while (iVar9 < iVar10);
    }
    iVar8 = iVar8 + 1;
  } while (iVar8 < (int)(uint)uVar5);
code_r0x021adbc0:
  lVar15 = *(long *)PTR__ZN4Aska6Global16m_pObjectManagerE_02cc4688;
  piVar2 = (int *)(lVar15 + 0xf98);
  iVar8 = 0;
code_r0x021adbd4:
  do {
    if (*piVar2 != -1) {
      ClearExclusiveLocal();
      bVar1 = iVar8 < 0x1ff;
      iVar8 = iVar8 + 1;
      if (bVar1) goto code_r0x021adbd4;
      piVar3 = (int *)(lVar15 + 0xf9c);
      do {
        cVar6 = '\x01';
        bVar1 = (bool)ExclusiveMonitorPass(piVar3,0x10);
        if (bVar1) {
          *piVar3 = *piVar3 + 1;
          cVar6 = ExclusiveMonitorsStatus();
        }
      } while (cVar6 != '\0');
      do {
        if (*piVar2 != -1) {
          ClearExclusiveLocal();
          do {
            uVar13 = Aska::Semaphore::IsReady() const(lVar15 + 0xfd8);
            if ((uVar13 & 1) == 0) {
              do {
                cVar6 = '\x01';
                bVar1 = (bool)ExclusiveMonitorPass(piVar3,0x10);
                if (bVar1) {
                  *piVar3 = *piVar3 + -1;
                  cVar6 = ExclusiveMonitorsStatus();
                }
              } while (cVar6 != '\0');
              Aska::Thread::Sleep(unsigned int)(1);
            }
            else {
              Aska::Semaphore::Wait() const(lVar15 + 0xfd8);
            }
            do {
              cVar6 = '\x01';
              bVar1 = (bool)ExclusiveMonitorPass(piVar3,0x10);
              if (bVar1) {
                *piVar3 = *piVar3 + 1;
                cVar6 = ExclusiveMonitorsStatus();
              }
            } while (cVar6 != '\0');
            while (*piVar2 == -1) {
              cVar6 = '\x01';
              bVar1 = (bool)ExclusiveMonitorPass(piVar2,0x10);
              if (bVar1) {
                *piVar2 = 0;
                cVar6 = ExclusiveMonitorsStatus();
              }
              if (cVar6 == '\0') goto code_r0x021adc8c;
            }
            ClearExclusiveLocal();
          } while( true );
        }
        cVar6 = '\x01';
        bVar1 = (bool)ExclusiveMonitorPass(piVar2,0x10);
        if (bVar1) {
          *piVar2 = 0;
          cVar6 = ExclusiveMonitorsStatus();
        }
      } while (cVar6 != '\0');
code_r0x021adc8c:
      do {
        cVar6 = '\x01';
        bVar1 = (bool)ExclusiveMonitorPass(piVar3,0x10);
        if (bVar1) {
          *piVar3 = *piVar3 + -1;
          cVar6 = ExclusiveMonitorsStatus();
        }
      } while (cVar6 != '\0');
code_r0x021adc9c:
      DataMemoryBarrier(2,3);
      plVar14 = *(long **)(lVar15 + 0x18);
      DataMemoryBarrier(2,3);
      do {
        if ((long *)(lVar15 + 8) == plVar14) {
          *(undefined4 *)(lVar15 + 0xf98) = 0xffffffff;
          DataMemoryBarrier(2,3);
          if (0x14 < *(int *)(lVar15 + 0xf9c)) {
            piVar2 = (int *)(lVar15 + 0xf9c);
            do {
              cVar6 = '\x01';
              bVar1 = (bool)ExclusiveMonitorPass(piVar2,0x10);
              if (bVar1) {
                *piVar2 = *piVar2 + -1;
                cVar6 = ExclusiveMonitorsStatus();
              }
            } while (cVar6 != '\0');
            uVar13 = Aska::Semaphore::IsReady() const(lVar15 + 0xfd8);
            if ((uVar13 & 1) != 0) {
              Aska::Semaphore::Signal() const(lVar15 + 0xfd8);
            }
          }
          return iVar7;
        }
        if (*(int *)((long)plVar14 + 0x1ac) == 0) {
          iVar8 = (**(code **)(*plVar14 + 0x2a8))(plVar14);
          iVar7 = iVar8 + iVar7;
          if (param_2 <= iVar7) {
            return iVar7;
          }
        }
        plVar14 = (long *)plVar14[2];
        DataMemoryBarrier(2,3);
      } while( true );
    }
    cVar6 = '\x01';
    bVar1 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar1) {
      *piVar2 = 0;
      cVar6 = ExclusiveMonitorsStatus();
    }
    if (cVar6 == '\0') goto code_r0x021adc9c;
  } while( true );
}

// ==== Aska::AHSLDatabase<Aska::ShaderCache, (unsigned char)9>::GetNodeCount(int) const
// vaddr 0x20add58 | ghidra 0x21add58 | size 348 | symbol _ZNK4Aska12AHSLDatabaseINS_11ShaderCacheELh9EE12GetNodeCountEi | lib libSOA-3.7.0.so | 2026-10-04
undefined2 _ZNK4Aska12AHSLDatabaseINS_11ShaderCacheELh9EE12GetNodeCountEi(long param_1,int param_2)

{
  int *piVar1;
  undefined2 uVar2;
  char cVar3;
  bool bVar4;
  code *pcVar5;
  ulong uVar6;
  int iVar7;
  int *piVar8;
  
  if (param_1 == 0) {
                    /* WARNING: Does not return */
    pcVar5 = (code *)SoftwareBreakpoint(1,0x21adeb4);
    (*pcVar5)();
  }
  piVar8 = (int *)(param_1 + 0x38);
  iVar7 = 0;
  do {
    while (*piVar8 == -1) {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
      if (bVar4) {
        *piVar8 = 0;
        cVar3 = ExclusiveMonitorsStatus();
      }
      if (cVar3 == '\0') goto code_r0x021ade40;
    }
    ClearExclusiveLocal();
    bVar4 = iVar7 < 0x1ff;
    iVar7 = iVar7 + 1;
  } while (bVar4);
  piVar1 = (int *)(param_1 + 0x3c);
  do {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar4) {
      *piVar1 = *piVar1 + 1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
  do {
    if (*piVar8 != -1) {
      ClearExclusiveLocal();
      do {
        uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x78);
        if ((uVar6 & 1) == 0) {
          do {
            cVar3 = '\x01';
            bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
            if (bVar4) {
              *piVar1 = *piVar1 + -1;
              cVar3 = ExclusiveMonitorsStatus();
            }
          } while (cVar3 != '\0');
          Aska::Thread::Sleep(unsigned int)(1);
        }
        else {
          Aska::Semaphore::Wait() const(param_1 + 0x78);
        }
        do {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar4) {
            *piVar1 = *piVar1 + 1;
            cVar3 = ExclusiveMonitorsStatus();
          }
        } while (cVar3 != '\0');
        while (*piVar8 == -1) {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
          if (bVar4) {
            *piVar8 = 0;
            cVar3 = ExclusiveMonitorsStatus();
          }
          if (cVar3 == '\0') goto code_r0x021ade30;
        }
        ClearExclusiveLocal();
      } while( true );
    }
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
    if (bVar4) {
      *piVar8 = 0;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
code_r0x021ade30:
  do {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar4) {
      *piVar1 = *piVar1 + -1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
code_r0x021ade40:
  DataMemoryBarrier(2,3);
  uVar2 = *(undefined2 *)(param_1 + (long)param_2 * 0x98 + 0x409a);
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_1 + 0x38) = 0xffffffff;
  DataMemoryBarrier(2,3);
  piVar8 = (int *)(param_1 + 0x3c);
  if (0x14 < *piVar8) {
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
      if (bVar4) {
        *piVar8 = *piVar8 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
    uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x78);
    if ((uVar6 & 1) != 0) {
      Aska::Semaphore::Signal() const(param_1 + 0x78);
    }
  }
  return uVar2;
}

// ==== Aska::AHSLDatabase<Aska::ShaderCache, (unsigned char)9>::GetNodeDirect(int, int)
// vaddr 0x20adeb4 | ghidra 0x21adeb4 | size 392 | symbol _ZN4Aska12AHSLDatabaseINS_11ShaderCacheELh9EE13GetNodeDirectEii | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska12AHSLDatabaseINS_11ShaderCacheELh9EE13GetNodeDirectEii
          (long param_1,int param_2,uint param_3)

{
  int *piVar1;
  char cVar2;
  bool bVar3;
  int iVar4;
  long lVar5;
  int *piVar6;
  ulong uVar7;
  long lVar8;
  undefined8 uVar9;
  
  if (param_1 == 0) {
code_r0x021adfa8:
    lVar5 = param_1 + (long)param_2 * 0x98;
    lVar8 = *(long *)(lVar5 + 0x4090);
    uVar7 = -(ulong)(param_3 >> 0x1f) & 0xfffffff000000000 | (ulong)param_3 << 4;
    lVar5 = lVar5 + uVar7 + 0x40a8;
    if (lVar8 != 0) {
      lVar5 = lVar8 + uVar7;
    }
    uVar9 = *(undefined8 *)(lVar5 + 8);
    if (param_1 != 0) {
      DataMemoryBarrier(2,3);
      *(undefined4 *)(param_1 + 0x38) = 0xffffffff;
      DataMemoryBarrier(2,3);
      piVar6 = (int *)(param_1 + 0x3c);
      if (0x14 < *piVar6) {
        do {
          cVar2 = '\x01';
          bVar3 = (bool)ExclusiveMonitorPass(piVar6,0x10);
          if (bVar3) {
            *piVar6 = *piVar6 + -1;
            cVar2 = ExclusiveMonitorsStatus();
          }
        } while (cVar2 != '\0');
        uVar7 = Aska::Semaphore::IsReady() const(param_1 + 0x78);
        if ((uVar7 & 1) != 0) {
          Aska::Semaphore::Signal() const(param_1 + 0x78);
        }
      }
    }
    return uVar9;
  }
  piVar6 = (int *)(param_1 + 0x38);
  iVar4 = 0;
code_r0x021adedc:
  do {
    if (*piVar6 != -1) {
      ClearExclusiveLocal();
      bVar3 = iVar4 < 0x1ff;
      iVar4 = iVar4 + 1;
      if (bVar3) goto code_r0x021adedc;
      piVar1 = (int *)(param_1 + 0x3c);
      do {
        cVar2 = '\x01';
        bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
        if (bVar3) {
          *piVar1 = *piVar1 + 1;
          cVar2 = ExclusiveMonitorsStatus();
        }
      } while (cVar2 != '\0');
      do {
        if (*piVar6 != -1) {
          ClearExclusiveLocal();
          do {
            uVar7 = Aska::Semaphore::IsReady() const(param_1 + 0x78);
            if ((uVar7 & 1) == 0) {
              do {
                cVar2 = '\x01';
                bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
                if (bVar3) {
                  *piVar1 = *piVar1 + -1;
                  cVar2 = ExclusiveMonitorsStatus();
                }
              } while (cVar2 != '\0');
              Aska::Thread::Sleep(unsigned int)(1);
            }
            else {
              Aska::Semaphore::Wait() const(param_1 + 0x78);
            }
            do {
              cVar2 = '\x01';
              bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
              if (bVar3) {
                *piVar1 = *piVar1 + 1;
                cVar2 = ExclusiveMonitorsStatus();
              }
            } while (cVar2 != '\0');
            while (*piVar6 == -1) {
              cVar2 = '\x01';
              bVar3 = (bool)ExclusiveMonitorPass(piVar6,0x10);
              if (bVar3) {
                *piVar6 = 0;
                cVar2 = ExclusiveMonitorsStatus();
              }
              if (cVar2 == '\0') goto code_r0x021adf94;
            }
            ClearExclusiveLocal();
          } while( true );
        }
        cVar2 = '\x01';
        bVar3 = (bool)ExclusiveMonitorPass(piVar6,0x10);
        if (bVar3) {
          *piVar6 = 0;
          cVar2 = ExclusiveMonitorsStatus();
        }
      } while (cVar2 != '\0');
code_r0x021adf94:
      do {
        cVar2 = '\x01';
        bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
        if (bVar3) {
          *piVar1 = *piVar1 + -1;
          cVar2 = ExclusiveMonitorsStatus();
        }
      } while (cVar2 != '\0');
code_r0x021adfa4:
      DataMemoryBarrier(2,3);
      goto code_r0x021adfa8;
    }
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar6,0x10);
    if (bVar3) {
      *piVar6 = 0;
      cVar2 = ExclusiveMonitorsStatus();
    }
    if (cVar2 == '\0') goto code_r0x021adfa4;
  } while( true );
}

// ==== Aska::AHSLCacheManagerV2::L1::SearchColdCache()
// vaddr 0x20ae03c | ghidra 0x21ae03c | size 280 | symbol _ZN4Aska18AHSLCacheManagerV22L115SearchColdCacheEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska18AHSLCacheManagerV22L115SearchColdCacheEv(long param_1)

{
  bool bVar1;
  ushort uVar2;
  uint uVar3;
  int iVar4;
  long lVar5;
  int iVar6;
  uint uVar7;
  
  uVar2 = *(ushort *)(param_1 + 0x17190);
  uVar7 = (uint)uVar2;
  uVar3 = *(int *)(param_1 + 0x17194) - 2;
  if (uVar2 < 0x200) {
    do {
      iVar4 = Aska::AHSLDatabase<Aska::ShaderCache, (unsigned char)9>::GetNodeCount(int) const(param_1,uVar7);
      if (0 < iVar4) {
        iVar6 = 0;
        do {
          lVar5 = Aska::AHSLDatabase<Aska::ShaderCache, (unsigned char)9>::GetNodeDirect(int, int)(param_1,uVar7,iVar6);
          if ((*(int *)(lVar5 + 0x4c) == 0) && (*(uint *)(lVar5 + 0x48) <= uVar3))
          goto code_r0x021ae13c;
          iVar6 = iVar6 + 1;
        } while (iVar6 < iVar4);
      }
      bVar1 = (int)uVar7 < 0x1ff;
      uVar7 = uVar7 + 1;
    } while (bVar1);
    if (uVar2 == 0) {
      return 0;
    }
  }
  uVar7 = 0;
  do {
    iVar4 = Aska::AHSLDatabase<Aska::ShaderCache, (unsigned char)9>::GetNodeCount(int) const(param_1,uVar7);
    if (0 < iVar4) {
      iVar6 = 0;
      do {
        lVar5 = Aska::AHSLDatabase<Aska::ShaderCache, (unsigned char)9>::GetNodeDirect(int, int)(param_1,uVar7,iVar6);
        if ((*(int *)(lVar5 + 0x4c) == 0) && (*(uint *)(lVar5 + 0x48) <= uVar3)) {
code_r0x021ae13c:
          *(ushort *)(param_1 + 0x17190) = (ushort)uVar7;
          return lVar5;
        }
        iVar6 = iVar6 + 1;
      } while (iVar6 < iVar4);
    }
    uVar7 = uVar7 + 1;
    if ((int)(uint)uVar2 <= (int)uVar7) {
      return 0;
    }
  } while( true );
}

// ==== Aska::AHSLCacheManagerV2::L1::FreeCache(Aska::ShaderCache*)
// vaddr 0x20ae154 | ghidra 0x21ae154 | size 68 | symbol _ZN4Aska18AHSLCacheManagerV22L19FreeCacheEPNS_11ShaderCacheE | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZN4Aska18AHSLCacheManagerV22L19FreeCacheEPNS_11ShaderCacheE(long param_1,long param_2)

{
  undefined4 uVar1;
  
  uVar1 = Aska::ShaderCache::FreeCache()(param_2);
  if (param_2 != 0) {
    Aska::MemoryManager::LocalFree(void*)(param_1 + 0x17098,param_2);
  }
  return uVar1;
}

// ==== Aska::AHSLDatabase<Aska::ShaderCache, (unsigned char)9>::DeleteData(unsigned char*, Aska::ShaderCache*)
// vaddr 0x20ae198 | ghidra 0x21ae198 | size 1212 | symbol _ZN4Aska12AHSLDatabaseINS_11ShaderCacheELh9EE10DeleteDataEPhPS1_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska12AHSLDatabaseINS_11ShaderCacheELh9EE10DeleteDataEPhPS1_
               (long param_1,byte *param_2,long param_3)

{
  int *piVar1;
  ushort *puVar2;
  long *plVar3;
  ushort *puVar4;
  undefined1 *puVar5;
  undefined8 *puVar6;
  undefined8 *puVar7;
  byte bVar8;
  byte bVar9;
  ushort uVar10;
  char cVar11;
  bool bVar12;
  int iVar13;
  long lVar14;
  int *piVar15;
  long lVar16;
  ulong uVar17;
  undefined1 *puVar18;
  long lVar19;
  long lVar20;
  ulong uVar21;
  long *plVar22;
  uint uVar23;
  long lVar24;
  undefined8 uVar25;
  
  bVar8 = param_2[1];
  bVar9 = param_2[2];
  uVar21 = (ulong)(((uint)bVar8 << 0x10 | (uint)*param_2 << 0x18) >> 0x17);
  if (param_1 != 0) {
    piVar15 = (int *)(param_1 + 0x38);
    iVar13 = 0;
code_r0x021ae1e0:
    do {
      if (*piVar15 == -1) goto code_r0x021ae1ec;
      ClearExclusiveLocal();
      bVar12 = iVar13 < 0x1ff;
      iVar13 = iVar13 + 1;
    } while (bVar12);
    piVar1 = (int *)(param_1 + 0x3c);
    do {
      cVar11 = '\x01';
      bVar12 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar12) {
        *piVar1 = *piVar1 + 1;
        cVar11 = ExclusiveMonitorsStatus();
      }
    } while (cVar11 != '\0');
    do {
      if (*piVar15 != -1) {
        ClearExclusiveLocal();
        do {
          uVar17 = Aska::Semaphore::IsReady() const(param_1 + 0x78);
          if ((uVar17 & 1) == 0) {
            do {
              cVar11 = '\x01';
              bVar12 = (bool)ExclusiveMonitorPass(piVar1,0x10);
              if (bVar12) {
                *piVar1 = *piVar1 + -1;
                cVar11 = ExclusiveMonitorsStatus();
              }
            } while (cVar11 != '\0');
            Aska::Thread::Sleep(unsigned int)(1);
          }
          else {
            Aska::Semaphore::Wait() const(param_1 + 0x78);
          }
          do {
            cVar11 = '\x01';
            bVar12 = (bool)ExclusiveMonitorPass(piVar1,0x10);
            if (bVar12) {
              *piVar1 = *piVar1 + 1;
              cVar11 = ExclusiveMonitorsStatus();
            }
          } while (cVar11 != '\0');
          while (*piVar15 == -1) {
            cVar11 = '\x01';
            bVar12 = (bool)ExclusiveMonitorPass(piVar15,0x10);
            if (bVar12) {
              *piVar15 = 0;
              cVar11 = ExclusiveMonitorsStatus();
            }
            if (cVar11 == '\0') goto code_r0x021ae298;
          }
          ClearExclusiveLocal();
        } while( true );
      }
      cVar11 = '\x01';
      bVar12 = (bool)ExclusiveMonitorPass(piVar15,0x10);
      if (bVar12) {
        *piVar15 = 0;
        cVar11 = ExclusiveMonitorsStatus();
      }
    } while (cVar11 != '\0');
code_r0x021ae298:
    do {
      cVar11 = '\x01';
      bVar12 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar12) {
        *piVar1 = *piVar1 + -1;
        cVar11 = ExclusiveMonitorsStatus();
      }
    } while (cVar11 != '\0');
code_r0x021ae2a8:
    DataMemoryBarrier(2,3);
  }
  puVar2 = (ushort *)(param_1 + uVar21 * 0x98 + 0x409a);
  uVar10 = *puVar2;
  uVar17 = (ulong)uVar10;
  if (uVar10 != 0) {
    lVar24 = param_1 + uVar21 * 0x20;
    plVar22 = (long *)(lVar24 + 0x90);
    lVar16 = *plVar22;
    uVar23 = (uint)bVar8 << 0x10 | (uint)bVar9 << 8;
    plVar3 = (long *)(param_1 + uVar21 * 0x98 + 0x4090);
    lVar19 = 0;
    lVar14 = 0;
    if (lVar16 == 0) {
code_r0x021ae35c:
      if ((uint)*(byte *)(lVar24 + 0xa8 + lVar14) != (uVar23 >> 0xf & 0xff)) goto code_r0x021ae388;
      lVar20 = param_1 + uVar21 * 0x98 + 0x40a8;
      if (*plVar3 != 0) {
        lVar20 = *plVar3;
      }
      if (*(long *)(lVar20 + lVar19 + 8) != param_3) goto code_r0x021ae388;
      puVar18 = (undefined1 *)(param_1 + uVar21 * 0x20 + lVar14 + 0xa8);
      lVar19 = param_1 + uVar21 * 0x98 + lVar19;
code_r0x021ae428:
      lVar24 = uVar17 - 1;
      uVar23 = (uint)lVar24;
      if ((1 < uVar10) && (uVar23 != (uint)lVar14)) {
        puVar5 = (undefined1 *)(param_1 + uVar21 * 0x20 + lVar24 + 0xa8);
        if (lVar16 != 0) {
          puVar5 = (undefined1 *)(lVar16 + lVar24);
        }
        *puVar18 = *puVar5;
        lVar16 = *plVar3;
        puVar6 = (undefined8 *)(param_1 + uVar21 * 0x98 + lVar24 * 0x10 + 0x40a8);
        if (lVar16 != 0) {
          puVar6 = (undefined8 *)(lVar16 + lVar24 * 0x10);
        }
        uVar25 = *puVar6;
        puVar7 = (undefined8 *)(lVar19 + 0x40a8);
        if (lVar16 != 0) {
          puVar7 = (undefined8 *)(lVar16 + lVar14 * 0x10);
        }
        puVar7[1] = puVar6[1];
        *puVar7 = uVar25;
      }
      lVar14 = param_1 + uVar21 * 0x20;
      if ((int)(uint)*(ushort *)(lVar14 + 0x98) < (int)uVar23) {
        lVar16 = *plVar22;
        lVar19 = *(long *)(lVar14 + 0xa0);
        lVar20 = (long)(int)(uVar23 << 1);
        if (lVar16 == 0) {
          if (lVar19 == 0) {
            lVar19 = operator new[](unsigned long, std::nothrow_t const&)(lVar20,PTR__ZSt7nothrow_02cb9a80);
          }
          else {
            lVar19 = Aska::MemoryManager::Malloc(unsigned long)(lVar19,lVar20);
          }
          if (lVar19 != 0) {
            lVar16 = param_1 + uVar21 * 0x20;
            memcpy(lVar19,lVar16 + 0xa8,*(undefined2 *)(lVar16 + 0x9a));
            goto code_r0x021ae544;
          }
        }
        else {
          if (lVar19 == 0) {
            lVar19 = operator new[](unsigned long, void*, unsigned long)(lVar20,lVar16,4);
          }
          else {
            lVar19 = Aska::MemoryManager::Realloc(unsigned long, void*, long)(lVar19,lVar20,lVar16,4);
          }
          if (lVar19 != 0) {
code_r0x021ae544:
            *plVar22 = lVar19;
            *(ushort *)(lVar14 + 0x98) = (ushort)(uVar23 << 1);
            goto code_r0x021ae54c;
          }
        }
      }
      else {
code_r0x021ae54c:
        *(ushort *)(lVar14 + 0x9a) = (ushort)lVar24;
      }
      puVar4 = (ushort *)(param_1 + uVar21 * 0x98 + 0x4098);
      if ((int)(uint)*puVar4 < (int)uVar23) {
        lVar19 = *plVar3;
        lVar14 = *(long *)(param_1 + uVar21 * 0x98 + 0x40a0);
        uVar17 = -(ulong)((uVar23 & 0x7fffffff) >> 0x1e) & 0xfffffff000000000 |
                 (ulong)(uVar23 << 1) << 4;
        if (lVar19 == 0) {
          if (lVar14 == 0) {
            lVar14 = operator new[](unsigned long, std::nothrow_t const&)(uVar17,PTR__ZSt7nothrow_02cb9a80);
          }
          else {
            lVar14 = Aska::MemoryManager::Malloc(unsigned long)();
          }
          if (lVar14 != 0) {
            memcpy(lVar14,param_1 + uVar21 * 0x98 + 0x40a8,(ulong)*puVar2 << 4);
          }
        }
        else if (lVar14 == 0) {
          lVar14 = operator new[](unsigned long, void*, unsigned long)(uVar17,lVar19,4);
        }
        else {
          lVar14 = Aska::MemoryManager::Realloc(unsigned long, void*, long)(lVar14,uVar17,lVar19,4);
        }
        if (lVar14 != 0) {
          *plVar3 = lVar14;
          *puVar4 = (ushort)(uVar23 << 1);
          goto code_r0x021ae61c;
        }
      }
      else {
code_r0x021ae61c:
        *puVar2 = (ushort)lVar24;
      }
      *(int *)(param_1 + 0x17090) = *(int *)(param_1 + 0x17090) + -1;
      if (param_1 == 0) {
        return;
      }
      goto code_r0x021ae39c;
    }
    do {
      if ((uint)*(byte *)(lVar16 + lVar14) == (uVar23 >> 0xf & 0xff)) {
        lVar24 = param_1 + uVar21 * 0x98 + 0x40a8;
        if (*plVar3 != 0) {
          lVar24 = *plVar3;
        }
        if (*(long *)(lVar24 + lVar19 + 8) == param_3) {
          puVar18 = (undefined1 *)(lVar16 + lVar14);
          lVar19 = param_1 + uVar21 * 0x98 + lVar19;
          goto code_r0x021ae428;
        }
      }
      lVar14 = lVar14 + 1;
      lVar19 = lVar19 + 0x10;
    } while (lVar14 < (long)uVar17);
  }
code_r0x021ae398:
  if (param_1 != 0) {
code_r0x021ae39c:
    DataMemoryBarrier(2,3);
    *(undefined4 *)(param_1 + 0x38) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar15 = (int *)(param_1 + 0x3c);
    if (0x14 < *piVar15) {
      do {
        cVar11 = '\x01';
        bVar12 = (bool)ExclusiveMonitorPass(piVar15,0x10);
        if (bVar12) {
          *piVar15 = *piVar15 + -1;
          cVar11 = ExclusiveMonitorsStatus();
        }
      } while (cVar11 != '\0');
      uVar21 = Aska::Semaphore::IsReady() const(param_1 + 0x78);
      if ((uVar21 & 1) != 0) {
        (*(code *)PTR__ZNK4Aska9Semaphore6SignalEv_02c96cd0)(param_1 + 0x78);
        return;
      }
    }
  }
  return;
code_r0x021ae1ec:
  cVar11 = '\x01';
  bVar12 = (bool)ExclusiveMonitorPass(piVar15,0x10);
  if (bVar12) {
    *piVar15 = 0;
    cVar11 = ExclusiveMonitorsStatus();
  }
  if (cVar11 == '\0') goto code_r0x021ae2a8;
  goto code_r0x021ae1e0;
code_r0x021ae388:
  lVar14 = lVar14 + 1;
  lVar19 = lVar19 + 0x10;
  if ((long)uVar17 <= lVar14) goto code_r0x021ae398;
  goto code_r0x021ae35c;
}

// ==== Aska::AHSLDatabase<Aska::ShaderCache, (unsigned char)9>::SetData(unsigned char*, Aska::ShaderCache*)
// vaddr 0x20ae654 | ghidra 0x21ae654 | size 996 | symbol _ZN4Aska12AHSLDatabaseINS_11ShaderCacheELh9EE7SetDataEPhPS1_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska12AHSLDatabaseINS_11ShaderCacheELh9EE7SetDataEPhPS1_
               (long param_1,byte *param_2,undefined8 param_3)

{
  int *piVar1;
  long lVar2;
  undefined1 *puVar3;
  undefined8 *puVar4;
  byte bVar5;
  byte bVar6;
  char cVar7;
  bool bVar8;
  long lVar9;
  int iVar10;
  long lVar11;
  int *piVar12;
  long lVar13;
  long lVar14;
  ulong uVar15;
  long *plVar16;
  ulong uVar17;
  ushort *puVar18;
  
  bVar5 = param_2[1];
  bVar6 = param_2[2];
  uVar15 = (ulong)(((uint)bVar5 << 0x10 | (uint)*param_2 << 0x18) >> 0x17);
  if (param_1 != 0) {
    piVar12 = (int *)(param_1 + 0x38);
    iVar10 = 0;
code_r0x021ae6a4:
    do {
      if (*piVar12 == -1) goto code_r0x021ae6b0;
      ClearExclusiveLocal();
      bVar8 = iVar10 < 0x1ff;
      iVar10 = iVar10 + 1;
    } while (bVar8);
    piVar1 = (int *)(param_1 + 0x3c);
    do {
      cVar7 = '\x01';
      bVar8 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar8) {
        *piVar1 = *piVar1 + 1;
        cVar7 = ExclusiveMonitorsStatus();
      }
    } while (cVar7 != '\0');
    do {
      if (*piVar12 != -1) {
        ClearExclusiveLocal();
        do {
          uVar17 = Aska::Semaphore::IsReady() const(param_1 + 0x78);
          if ((uVar17 & 1) == 0) {
            do {
              cVar7 = '\x01';
              bVar8 = (bool)ExclusiveMonitorPass(piVar1,0x10);
              if (bVar8) {
                *piVar1 = *piVar1 + -1;
                cVar7 = ExclusiveMonitorsStatus();
              }
            } while (cVar7 != '\0');
            Aska::Thread::Sleep(unsigned int)(1);
          }
          else {
            Aska::Semaphore::Wait() const(param_1 + 0x78);
          }
          do {
            cVar7 = '\x01';
            bVar8 = (bool)ExclusiveMonitorPass(piVar1,0x10);
            if (bVar8) {
              *piVar1 = *piVar1 + 1;
              cVar7 = ExclusiveMonitorsStatus();
            }
          } while (cVar7 != '\0');
          while (*piVar12 == -1) {
            cVar7 = '\x01';
            bVar8 = (bool)ExclusiveMonitorPass(piVar12,0x10);
            if (bVar8) {
              *piVar12 = 0;
              cVar7 = ExclusiveMonitorsStatus();
            }
            if (cVar7 == '\0') goto code_r0x021aea1c;
          }
          ClearExclusiveLocal();
        } while( true );
      }
      cVar7 = '\x01';
      bVar8 = (bool)ExclusiveMonitorPass(piVar12,0x10);
      if (bVar8) {
        *piVar12 = 0;
        cVar7 = ExclusiveMonitorsStatus();
      }
    } while (cVar7 != '\0');
code_r0x021aea1c:
    do {
      cVar7 = '\x01';
      bVar8 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar8) {
        *piVar1 = *piVar1 + -1;
        cVar7 = ExclusiveMonitorsStatus();
      }
    } while (cVar7 != '\0');
    DataMemoryBarrier(2,3);
  }
code_r0x021ae700:
  lVar2 = param_1 + uVar15 * 0x20;
  puVar18 = (ushort *)(lVar2 + 0x9a);
  uVar17 = (ulong)*puVar18;
  plVar16 = (long *)(lVar2 + 0x90);
  if (*puVar18 < *(ushort *)(lVar2 + 0x98)) {
    lVar14 = *plVar16;
code_r0x021ae7cc:
    puVar3 = (undefined1 *)(param_1 + uVar15 * 0x20 + uVar17 + 0xa8);
    if (lVar14 != 0) {
      puVar3 = (undefined1 *)(lVar14 + uVar17);
    }
    *puVar18 = (ushort)(uVar17 + 1);
    *puVar3 = (char)(((uint)bVar5 << 0x10 | (uint)bVar6 << 8) >> 0xf);
  }
  else {
    lVar13 = *plVar16;
    lVar14 = *(long *)(lVar2 + 0xa0);
    lVar9 = (uVar17 + 1) * 2;
    if (lVar13 == 0) {
      if (lVar14 == 0) {
        lVar14 = operator new[](unsigned long, std::nothrow_t const&)(lVar9,PTR__ZSt7nothrow_02cb9a80);
      }
      else {
        lVar14 = Aska::MemoryManager::Malloc(unsigned long)(lVar14,lVar9);
      }
      if (lVar14 != 0) {
        memcpy(lVar14,param_1 + uVar15 * 0x20 + 0xa8,*puVar18);
        goto code_r0x021ae7c0;
      }
    }
    else {
      if (lVar14 == 0) {
        lVar14 = operator new[](unsigned long, void*, unsigned long)(lVar9,lVar13,4);
      }
      else {
        lVar14 = Aska::MemoryManager::Realloc(unsigned long, void*, long)(lVar14,lVar9,lVar13,4);
      }
      if (lVar14 != 0) {
code_r0x021ae7c0:
        *plVar16 = lVar14;
        *(ushort *)(lVar2 + 0x98) = (ushort)lVar9;
        goto code_r0x021ae7cc;
      }
    }
  }
  lVar14 = param_1 + uVar15 * 0x98;
  puVar18 = (ushort *)(lVar14 + 0x409a);
  uVar17 = (ulong)*puVar18;
  plVar16 = (long *)(lVar14 + 0x4090);
  lVar2 = uVar17 + 1;
  if (*puVar18 < *(ushort *)(lVar14 + 0x4098)) {
    lVar13 = *plVar16;
  }
  else {
    lVar11 = *plVar16;
    lVar13 = *(long *)(param_1 + uVar15 * 0x98 + 0x40a0);
    lVar9 = lVar2 * 0x20;
    if (lVar11 == 0) {
      if (lVar13 == 0) {
        lVar13 = operator new[](unsigned long, std::nothrow_t const&)(lVar9,PTR__ZSt7nothrow_02cb9a80);
      }
      else {
        lVar13 = Aska::MemoryManager::Malloc(unsigned long)();
      }
      if (lVar13 != 0) {
        memcpy(lVar13,param_1 + uVar15 * 0x98 + 0x40a8,(ulong)*puVar18 << 4);
      }
    }
    else if (lVar13 == 0) {
      lVar13 = operator new[](unsigned long, void*, unsigned long)(lVar9,lVar11,4);
    }
    else {
      lVar13 = Aska::MemoryManager::Realloc(unsigned long, void*, long)(lVar13,lVar9,lVar11,4);
    }
    if (lVar13 == 0) {
      lVar13 = *plVar16;
      uVar17 = (ulong)*puVar18 - 1;
      goto code_r0x021ae8e4;
    }
    *plVar16 = lVar13;
    *(ushort *)(lVar14 + 0x4098) = (ushort)((int)lVar2 << 1);
  }
  *puVar18 = (ushort)lVar2;
code_r0x021ae8e4:
  puVar4 = (undefined8 *)(param_1 + uVar15 * 0x98 + uVar17 * 0x10 + 0x40a8);
  if (lVar13 != 0) {
    puVar4 = (undefined8 *)(lVar13 + uVar17 * 0x10);
  }
  *puVar4 = param_2;
  puVar4[1] = param_3;
  *(int *)(param_1 + 0x17090) = *(int *)(param_1 + 0x17090) + 1;
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_1 + 0x38) = 0xffffffff;
  DataMemoryBarrier(2,3);
  piVar12 = (int *)(param_1 + 0x3c);
  if (0x14 < *piVar12) {
    do {
      cVar7 = '\x01';
      bVar8 = (bool)ExclusiveMonitorPass(piVar12,0x10);
      if (bVar8) {
        *piVar12 = *piVar12 + -1;
        cVar7 = ExclusiveMonitorsStatus();
      }
    } while (cVar7 != '\0');
    uVar15 = Aska::Semaphore::IsReady() const(param_1 + 0x78);
    if ((uVar15 & 1) != 0) {
      (*(code *)PTR__ZNK4Aska9Semaphore6SignalEv_02c96cd0)(param_1 + 0x78);
      return;
    }
  }
  return;
code_r0x021ae6b0:
  cVar7 = '\x01';
  bVar8 = (bool)ExclusiveMonitorPass(piVar12,0x10);
  if (bVar8) {
    *piVar12 = 0;
    cVar7 = ExclusiveMonitorsStatus();
  }
  if (cVar7 == '\0') goto code_r0x021ae6fc;
  goto code_r0x021ae6a4;
code_r0x021ae6fc:
  DataMemoryBarrier(2,3);
  goto code_r0x021ae700;
}

// ==== Aska::AHSLCacheManagerV2::Logging_WriteShaderKey(Aska::File&, unsigned char*, bool)
// vaddr 0x20aea38 | ghidra 0x21aea38 | size 432 | symbol _ZN4Aska18AHSLCacheManagerV222Logging_WriteShaderKeyERNS_4FileEPhb | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska18AHSLCacheManagerV222Logging_WriteShaderKeyERNS_4FileEPhb
               (undefined8 param_1,byte *param_2,ulong param_3)

{
  byte bVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined8 uVar6;
  ulong uVar7;
  byte *pbVar8;
  undefined8 uStack_80;
  undefined8 uStack_78;
  undefined2 uStack_70;
  undefined3 uStack_6e;
  undefined3 uStack_6b;
  undefined5 uStack_68;
  undefined1 auStack_44 [4];
  
  if ((param_3 & 1) == 0) {
    uStack_68 = _UNK_029c51dd;
    uStack_70 = (undefined2)_UNK_029c51d5;
    uStack_6e = (undefined3)((uint5)_UNK_029c51d5 >> 0x10);
    uStack_6b = _UNK_029c51da;
    uVar6 = strlen(&uStack_70);
    Aska::File::Write(void const*, unsigned long)(param_1,&uStack_70,uVar6);
  }
  uVar2 = Aska::ShaderKeyUtil::GetShaderKeySize(unsigned char const*)(param_2);
  if (0 < (int)uVar2) {
    uVar7 = (ulong)uVar2;
    pbVar8 = param_2;
    do {
      bVar1 = *pbVar8;
      sprintf(auStack_44,&UNK_029c51e2/*"%hhx"*/,bVar1);
      if (bVar1 < 0x10) {
        Aska::File::Write(void const*, unsigned long)(param_1,&UNK_0295c676/*"0"*/,1);
        uVar6 = 1;
      }
      else {
        uVar6 = 2;
      }
      Aska::File::Write(void const*, unsigned long)(param_1,auStack_44,uVar6);
      uVar7 = uVar7 - 1;
      pbVar8 = pbVar8 + 1;
    } while (uVar7 != 0);
  }
  if ((param_3 & 1) == 0) {
    uStack_70 = 10;
    uVar6 = strlen(&uStack_70);
    Aska::File::Write(void const*, unsigned long)(param_1,&uStack_70,uVar6);
    uVar7 = Aska::ShaderKeyUtil::GetIsKeyLinked(unsigned char const*)(param_2);
    if ((uVar7 & 1) == 0) {
      uVar3 = Aska::ShaderKeyUtil::GetShaderCRC(unsigned char const*)(param_2);
      sprintf(&uStack_70,&UNK_029c5207,uVar3);
    }
    else {
      uStack_80 = 0;
      uStack_78 = 0;
      Aska::ShaderKeyUtil::UnlinkKeys(unsigned char const*, unsigned char**, unsigned char**)(param_2,&uStack_78,&uStack_80);
      uVar3 = Aska::ShaderKeyUtil::GetShaderCRC(unsigned char const*)(param_2);
      uVar4 = Aska::ShaderKeyUtil::GetShaderCRC(unsigned char const*)(uStack_78);
      uVar5 = Aska::ShaderKeyUtil::GetShaderCRC(unsigned char const*)(uStack_80);
      sprintf(&uStack_70,&UNK_029c51e7,uVar3,uVar4,uVar5);
    }
    uVar6 = strlen(&uStack_70);
    Aska::File::Write(void const*, unsigned long)(param_1,&uStack_70,uVar6);
  }
  return;
}

// ==== Aska::AHSLCacheManagerV2::DoesPrebuiltFinished() const
// vaddr 0x20aebe8 | ghidra 0x21aebe8 | size 8 | symbol _ZNK4Aska18AHSLCacheManagerV220DoesPrebuiltFinishedEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska18AHSLCacheManagerV220DoesPrebuiltFinishedEv(void)

{
  return 0;
}

// ==== Aska::AHSLCacheManagerV2::SetPrebuiltBinary(void const*, unsigned long)
// vaddr 0x20aebf0 | ghidra 0x21aebf0 | size 8 | symbol _ZN4Aska18AHSLCacheManagerV217SetPrebuiltBinaryEPKvm | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska18AHSLCacheManagerV217SetPrebuiltBinaryEPKvm(void)

{
  return 0;
}

// ==== Aska::AHSLCacheManagerV2::AttachDiskCache(int, void*)
// vaddr 0x20aebf8 | ghidra 0x21aebf8 | size 144 | symbol _ZN4Aska18AHSLCacheManagerV215AttachDiskCacheEiPv | lib libSOA-3.7.0.so | 2026-10-04
bool _ZN4Aska18AHSLCacheManagerV215AttachDiskCacheEiPv(long param_1,int param_2,undefined8 param_3)

{
  long lVar1;
  bool bVar2;
  
  lVar1 = param_1 + (long)param_2 * 0x20;
  if (*(char *)(lVar1 + 0x194bb) != '\0') {
    *(byte *)(lVar1 + 0x194ba) = *(byte *)(lVar1 + 0x194ba) | 1;
  }
  bVar2 = *(char *)(lVar1 + 0x194bc) == '\0';
  if (bVar2) {
    *(undefined8 *)(param_1 + (long)param_2 * 0x20 + 0x194d0) = param_3;
    DataMemoryBarrier(2,3);
    *(char *)(lVar1 + 0x194bc) = '\x01';
    *(undefined1 *)(param_1 + 0x194b0) = 1;
    Aska::Event::Set() const(param_1 + 0x30af8);
  }
  return bVar2;
}

// ==== Aska::AHSLCacheManagerV2::AttachDiskCache(int, int)
// vaddr 0x20aec88 | ghidra 0x21aec88 | size 460 | symbol _ZN4Aska18AHSLCacheManagerV215AttachDiskCacheEii | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska18AHSLCacheManagerV215AttachDiskCacheEii(long param_1,int param_2,undefined4 param_3)

{
  long lVar1;
  char *pcVar2;
  undefined *puVar3;
  undefined *puVar4;
  long *plVar5;
  ulong uVar6;
  long *plVar7;
  long lVar8;
  
  lVar8 = (long)param_2;
  lVar1 = param_1 + lVar8 * 0x20;
  if (*(char *)(lVar1 + 0x194bb) != '\0') {
    *(byte *)(lVar1 + 0x194ba) = *(byte *)(lVar1 + 0x194ba) | 1;
  }
  pcVar2 = (char *)(lVar1 + 0x194bc);
  if (*pcVar2 == '\0') {
    plVar5 = (long *)operator new(unsigned long, std::nothrow_t const&)(0xf8,PTR__ZSt7nothrow_02cb9a80);
    puVar3 = PTR__ZTVN4Aska15ResourceManagerE_02cb9e28;
    if (plVar5 == (long *)0x0) {
      return 0;
    }
    *(undefined4 *)(plVar5 + 3) = 0xa20;
    plVar5[4] = 0xffffffff;
    puVar4 = PTR__ZTVN4Aska15ResourceManager12WakeupNotifyE_02cbbae0;
    plVar5[2] = 0;
    *(undefined4 *)(plVar5 + 5) = 0;
    plVar5[1] = (long)(puVar4 + 0x10);
    *plVar5 = (long)(puVar3 + 0x10);
    *(undefined1 *)((long)plVar5 + 0x2c) = 0;
    *(undefined2 *)((long)plVar5 + 0x2e) = 1;
    plVar5[7] = 0;
    Aska::FastCriticalSection::FastCriticalSection()(plVar5 + 8);
    plVar5[0x1b] = 0;
    plVar5[0x1a] = 0;
    plVar5[0x1d] = 0;
    plVar5[0x1c] = 0;
    Aska::ResourceManager::Init()(plVar5);
    uVar6 = Aska::ResourceManager::SetFileID(unsigned int, int, unsigned short, bool, void*, Aska::INotify*, bool, void*, Aska::DecompressInfo*, Aska::INotify*, unsigned char)(plVar5,param_3,4,0,1,0,0,0,0,0,0,0);
    if ((uVar6 & 1) != 0) {
      if ((*(char *)(lVar1 + 0x194bb) == '\x02') || (*pcVar2 == '\x02')) {
        plVar7 = (long *)(param_1 + lVar8 * 0x20 + 0x194d0);
        if ((long *)*plVar7 != (long *)0x0) {
          (**(code **)(*(long *)*plVar7 + 0x10))();
          *plVar7 = 0;
        }
      }
      else {
        plVar7 = (long *)(param_1 + lVar8 * 0x20 + 0x194d0);
      }
      *plVar7 = (long)plVar5;
      DataMemoryBarrier(2,3);
      *pcVar2 = '\x02';
      *(undefined1 *)(param_1 + 0x194b0) = 1;
      Aska::Event::Set() const(param_1 + 0x30af8);
      return 1;
    }
    (**(code **)(*plVar5 + 0x10))(plVar5);
  }
  return 0;
}

// ==== Aska::AHSLCacheManagerV2::IsAttachmentCompleted()
// vaddr 0x20aee54 | ghidra 0x21aee54 | size 24 | symbol _ZN4Aska18AHSLCacheManagerV221IsAttachmentCompletedEv | lib libSOA-3.7.0.so | 2026-10-04
bool _ZN4Aska18AHSLCacheManagerV221IsAttachmentCompletedEv(long param_1)

{
  return *(char *)(param_1 + 0x194b0) == '\0';
}

// ==== Aska::AHSLCacheManagerV2::RemoveDiskCache(int)
// vaddr 0x20aee6c | ghidra 0x21aee6c | size 88 | symbol _ZN4Aska18AHSLCacheManagerV215RemoveDiskCacheEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18AHSLCacheManagerV215RemoveDiskCacheEi(long param_1,int param_2)

{
  long lVar1;
  
  lVar1 = param_1 + (long)param_2 * 0x20;
  if (*(char *)(lVar1 + 0x194bb) != '\0') {
    *(byte *)(lVar1 + 0x194ba) = *(byte *)(lVar1 + 0x194ba) | 1;
    DataMemoryBarrier(2,3);
    *(undefined1 *)(param_1 + 0x194b0) = 1;
    (*(code *)PTR__ZNK4Aska5Event3SetEv_02c9dcf0)(param_1 + 0x30af8);
    return;
  }
  return;
}

// ==== Aska::AHSLCacheManagerV2::WriteHDDDiskCache(int, unsigned char*)
// vaddr 0x20aeec4 | ghidra 0x21aeec4 | size 8 | symbol _ZN4Aska18AHSLCacheManagerV217WriteHDDDiskCacheEiPh | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska18AHSLCacheManagerV217WriteHDDDiskCacheEiPh(void)

{
  return 0;
}

// ==== Aska::AHSLCacheManagerV2::Compile_CreateLogName(char*, unsigned int)
// vaddr 0x20aeecc | ghidra 0x21aeecc | size 192 | symbol _ZN4Aska18AHSLCacheManagerV221Compile_CreateLogNameEPcj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18AHSLCacheManagerV221Compile_CreateLogNameEPcj
               (long param_1,undefined8 param_2,undefined4 param_3)

{
  ushort uStack_30;
  undefined2 uStack_2e;
  undefined2 uStack_2c;
  undefined2 uStack_2a;
  undefined2 uStack_28;
  undefined2 uStack_26;
  uint uStack_24;
  
  Aska::Global::MakeShaderWritePath(char*, unsigned int, char const*)(param_2,param_3,&UNK_029c521d/*"AHSLerr"*/);
  sprintf(param_2,&UNK_0285ec00/*"%s_%s"*/,param_2,*(undefined8 *)(param_1 + 0x17270));
  Aska::GetLocalTime(Aska::ASKATIME*)(&uStack_30);
  __aska_snprintf_s(char*, unsigned long, unsigned long, char const*, ...)(param_2,param_3,0xffffffffffffffff,&UNK_029c5225/*"%s_%02d%02d%02d_%02d%02d%02d%03d.ahsl"*/,param_2,uStack_30 - 2000,
                  uStack_2e,uStack_2c,uStack_2a,uStack_28,uStack_26,uStack_24 / 1000);
  return;
}

// ==== Aska::AHSLCacheManagerV2::MakeCachePath(char*, int)
// vaddr 0x20aef8c | ghidra 0x21aef8c | size 232 | symbol _ZN4Aska18AHSLCacheManagerV213MakeCachePathEPci | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska18AHSLCacheManagerV213MakeCachePathEPci(long param_1,undefined1 *param_2,int param_3)

{
  undefined8 uVar1;
  long lVar2;
  undefined2 uVar3;
  undefined4 uVar4;
  
  param_1 = param_1 + 0x17288;
  if (param_3 < 0x20) {
    if (param_3 != 0) {
      (*(code *)PTR_sprintf_02cacc88)(param_2,&UNK_027f7e11/*"%s_%02d"*/,param_1,param_3);
      return;
    }
    *param_2 = 0;
    strcat(param_2,param_1);
    lVar2 = strlen(param_2);
    uVar3 = 0x54;
    uVar4 = 0x4f4f425f;
  }
  else {
    *param_2 = 0;
    strcat(param_2,param_1);
    if (param_3 == 0x33) {
      lVar2 = strlen(param_2);
      uVar1 = _UNK_029c5257;
      *(undefined2 *)((long)(param_2 + lVar2) + 8) = 0x74;
      *(undefined8 *)(param_2 + lVar2) = uVar1;
      return;
    }
    if (param_3 != 0x32) {
      return;
    }
    lVar2 = strlen(param_2);
    uVar3 = 0x62;
    uVar4 = 0x6368615f;
  }
  *(undefined2 *)((long)(param_2 + lVar2) + 4) = uVar3;
  *(undefined4 *)(param_2 + lVar2) = uVar4;
  return;
}

// ==== Aska::AHSLCacheManagerV2::MakeCachePathPrivate(char*, int, char const*)
// vaddr 0x20af074 | ghidra 0x21af074 | size 220 | symbol _ZN4Aska18AHSLCacheManagerV220MakeCachePathPrivateEPciPKc | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska18AHSLCacheManagerV220MakeCachePathPrivateEPciPKc
               (undefined8 param_1,undefined1 *param_2,int param_3,undefined8 param_4)

{
  undefined8 uVar1;
  long lVar2;
  undefined2 uVar3;
  undefined4 uVar4;
  
  if (param_3 < 0x20) {
    if (param_3 != 0) {
      (*(code *)PTR_sprintf_02cacc88)(param_2,&UNK_027f7e11/*"%s_%02d"*/,param_4,param_3);
      return;
    }
    *param_2 = 0;
    strcat(param_2,param_4);
    lVar2 = strlen(param_2);
    uVar3 = 0x54;
    uVar4 = 0x4f4f425f;
  }
  else {
    *param_2 = 0;
    strcat(param_2,param_4);
    if (param_3 == 0x33) {
      lVar2 = strlen(param_2);
      uVar1 = _UNK_029c5257;
      *(undefined2 *)((long)(param_2 + lVar2) + 8) = 0x74;
      *(undefined8 *)(param_2 + lVar2) = uVar1;
      return;
    }
    if (param_3 != 0x32) {
      return;
    }
    lVar2 = strlen(param_2);
    uVar3 = 0x62;
    uVar4 = 0x6368615f;
  }
  *(undefined2 *)((long)(param_2 + lVar2) + 4) = uVar3;
  *(undefined4 *)(param_2 + lVar2) = uVar4;
  return;
}

// ==== Aska::AHSLCacheManagerV2::Handler()
// vaddr 0x20af150 | ghidra 0x21af150 | size 132 | symbol _ZN4Aska18AHSLCacheManagerV27HandlerEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18AHSLCacheManagerV27HandlerEv(long param_1)

{
  char *pcVar1;
  undefined *puVar2;
  ulong uVar3;
  
  puVar2 = PTR__ZN4Aska12g_pRenderDevE_02cbb1a0;
  Aska::RenderDeviceGL::SetCurrentContext(Aska::RENDER_CONTEXT_TYPE::E)(*(undefined8 *)PTR__ZN4Aska12g_pRenderDevE_02cbb1a0,1);
  pcVar1 = (char *)(param_1 + 0x30af0);
  if (*pcVar1 == '\0') {
    do {
      uVar3 = Aska::AHSLCacheManagerV2::ProcDiskCacheEntry()(param_1);
      if ((uVar3 & 1) != 0) {
        Aska::Event::Wait(unsigned int) const(param_1 + 0x30af8,0);
      }
    } while (*pcVar1 == '\0');
  }
  *pcVar1 = '\0';
  (*(code *)PTR__ZN4Aska14RenderDeviceGL14ReleaseContextENS_19RENDER_CONTEXT_TYPE1EE_02ca7bc0)
            (*(undefined8 *)puVar2,1);
  return;
}

// ==== Aska::AHSLCacheManagerV2::Tick_BG_AHSL_Compile()
// vaddr 0x20af1d4 | ghidra 0x21af1d4 | size 48 | symbol _ZN4Aska18AHSLCacheManagerV220Tick_BG_AHSL_CompileEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18AHSLCacheManagerV220Tick_BG_AHSL_CompileEv(long param_1)

{
  ulong uVar1;
  
  uVar1 = Aska::AHSLCacheManagerV2::ProcDiskCacheEntry()();
  if ((uVar1 & 1) != 0) {
    (*(code *)PTR__ZNK4Aska5Event4WaitEj_02c992c0)(param_1 + 0x30af8,0);
    return;
  }
  return;
}

// ==== Aska::AHSLCacheManagerV2::FlushProfile()
// vaddr 0x20af204 | ghidra 0x21af204 | size 4 | symbol _ZN4Aska18AHSLCacheManagerV212FlushProfileEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18AHSLCacheManagerV212FlushProfileEv(void)

{
  return;
}

// ==== Aska::AHSLCacheManagerV2::ProcDiskCacheEntry()
// vaddr 0x20af208 | ghidra 0x21af208 | size 244 | symbol _ZN4Aska18AHSLCacheManagerV218ProcDiskCacheEntryEv | lib libSOA-3.7.0.so | 2026-10-04
bool _ZN4Aska18AHSLCacheManagerV218ProcDiskCacheEntryEv(long param_1)

{
  char *pcVar1;
  char *pcVar2;
  char cVar3;
  ulong uVar4;
  char acStack_28 [4];
  char acStack_24 [4];
  
  acStack_24[0] = '\0';
  acStack_28[0] = '\0';
  pcVar1 = (char *)(param_1 + 0x194b0);
  if (*pcVar1 == '\0') {
    uVar4 = 0;
  }
  else {
    uVar4 = Aska::AHSLCacheManagerV2::ProcDiskCacheEntry_Helper(bool&, bool&)(param_1,acStack_24,acStack_28);
    uVar4 = uVar4 & 0xffffffff;
    if (acStack_28[0] != '\0' || acStack_24[0] != '\0') {
      pcVar2 = (char *)(param_1 + 0x30a18);
      if (acStack_24[0] == '\0') {
        *pcVar2 = '\x01';
        Aska::Event::Wait(unsigned int) const(param_1 + 0x30a20,0);
      }
      Aska::AHSLDatabase<Aska::ShaderDiskCache, (unsigned char)9>::DeleteAll()(param_1 + 0x198b8);
      Aska::AHSLCacheManagerV2::RebuildL2Database()(param_1);
      Aska::Event::Set() const(param_1 + 0x30a88);
      cVar3 = *pcVar2;
      while (cVar3 != '\0') {
        Aska::Thread::SleepU(unsigned int)(100);
        cVar3 = *pcVar2;
      }
    }
  }
  if ((uVar4 & 1) != 0) {
    *pcVar1 = '\0';
  }
  return *pcVar1 == '\0';
}

// ==== Aska::AHSLCacheManagerV2::ProcDiskCacheEntry_Helper(bool&, bool&)
// vaddr 0x20af2fc | ghidra 0x21af2fc | size 488 | symbol _ZN4Aska18AHSLCacheManagerV225ProcDiskCacheEntry_HelperERbS1_ | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska18AHSLCacheManagerV225ProcDiskCacheEntry_HelperERbS1_
          (long param_1,char *param_2,undefined1 *param_3)

{
  long lVar1;
  long lVar2;
  byte bVar3;
  char cVar4;
  long lVar5;
  ulong uVar6;
  long lVar7;
  long lVar8;
  int iVar9;
  undefined1 auStack_260 [512];
  
  lVar8 = 0;
  iVar9 = -1;
  lVar1 = param_1 + 0x194c8;
  do {
    lVar2 = lVar1 + lVar8;
    bVar3 = *(byte *)(lVar2 + -0xe);
    if ((bVar3 & 1) != 0) {
      if (*(char *)(lVar2 + -0xd) != '\0') {
        if (*param_2 == '\0') {
          *(undefined1 *)(param_1 + 0x30a18) = 1;
          Aska::Event::Wait(unsigned int) const(param_1 + 0x30a20,0);
          *param_2 = '\x01';
        }
        Aska::AHSLCacheManagerV2::CleanCacheSlotL3(Aska::AHSLCacheManagerV2::CacheSlot*)(param_1,lVar2 + -0x10);
        if (*(char *)(lVar2 + -0xd) == '\x03') {
          if (*(long *)(lVar1 + lVar8 + -8) != 0) {
            operator delete(void*)();
          }
        }
        else if (*(char *)(lVar2 + -0xd) == '\x02') {
          if (*(long **)(lVar1 + lVar8) != (long *)0x0) {
            (**(code **)(**(long **)(lVar1 + lVar8) + 0x10))();
          }
          *(undefined8 *)(lVar1 + lVar8) = 0;
        }
        *(undefined1 *)(lVar2 + -0xd) = 0;
        *(undefined8 *)(lVar1 + lVar8 + -8) = 0;
        bVar3 = *(byte *)(lVar2 + -0xe);
      }
      *(byte *)(lVar2 + -0xe) = bVar3 & 0xfe;
    }
    if (*(char *)(lVar2 + -0xc) != '\0') {
      cVar4 = *(char *)(lVar2 + -0xc);
      if (cVar4 == '\x03') {
        if (*param_2 != '\0') {
          return 0;
        }
        Aska::AHSLCacheManagerV2::MakeCachePath(char*, int)(param_1,auStack_260,*(undefined1 *)(lVar1 + lVar8 + -0xb));
        lVar5 = Aska::AHSLBase::LoadFile(void*, char const*, unsigned int*)(param_1 + 0x18,0,auStack_260,0);
        *(long *)(lVar1 + lVar8 + -8) = lVar5;
        if (lVar5 == 0) {
          return 0;
        }
      }
      else if (cVar4 == '\x02') {
        lVar5 = lVar1 + lVar8;
        uVar6 = Aska::ResourceManager::IsPrepared()(*(undefined8 *)(lVar5 + 8));
        if ((uVar6 & 1) == 0) {
          return 0;
        }
        lVar7 = Aska::ResourceManager::Lock()(*(undefined8 *)(lVar5 + 8));
        *(long *)(lVar5 + -8) = lVar7;
        if (lVar7 == 0) {
          return 0;
        }
        *(undefined8 *)(lVar1 + lVar8) = *(undefined8 *)(lVar1 + lVar8 + 8);
      }
      else {
        if (cVar4 != '\x01') goto code_r0x021af4a8;
        *(undefined8 *)(lVar1 + lVar8 + -8) = *(undefined8 *)(lVar1 + lVar8 + 8);
      }
      *(undefined1 *)(lVar1 + lVar8 + -0xd) = *(undefined1 *)(lVar2 + -0xc);
      *(undefined1 *)(lVar2 + -0xc) = 0;
      *param_3 = 1;
    }
code_r0x021af4a8:
    iVar9 = iVar9 + 1;
    lVar8 = lVar8 + 0x20;
    if (0x1e < iVar9) {
      return 1;
    }
  } while( true );
}

// ==== Aska::AHSLDatabase<Aska::ShaderDiskCache, (unsigned char)9>::DeleteAll()
// vaddr 0x20af4e4 | ghidra 0x21af4e4 | size 380 | symbol _ZN4Aska12AHSLDatabaseINS_15ShaderDiskCacheELh9EE9DeleteAllEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska12AHSLDatabaseINS_15ShaderDiskCacheELh9EE9DeleteAllEv(long param_1)

{
  int *piVar1;
  char cVar2;
  bool bVar3;
  ulong uVar4;
  int iVar5;
  long lVar6;
  int *piVar7;
  long lVar8;
  
  if (param_1 == 0) {
code_r0x021af5cc:
    lVar6 = 0;
    lVar8 = -0x4000;
    do {
      *(undefined2 *)(param_1 + 0x409a + lVar8) = 0;
      *(undefined2 *)(param_1 + 0x409a + lVar6) = 0;
      lVar8 = lVar8 + 0x20;
      lVar6 = lVar6 + 0x98;
    } while (lVar8 != 0);
    *(undefined4 *)(param_1 + 0x17090) = 0;
    DataMemoryBarrier(2,3);
    *(undefined4 *)(param_1 + 0x38) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar7 = (int *)(param_1 + 0x3c);
    if (0x14 < *piVar7) {
      do {
        cVar2 = '\x01';
        bVar3 = (bool)ExclusiveMonitorPass(piVar7,0x10);
        if (bVar3) {
          *piVar7 = *piVar7 + -1;
          cVar2 = ExclusiveMonitorsStatus();
        }
      } while (cVar2 != '\0');
      uVar4 = Aska::Semaphore::IsReady() const(param_1 + 0x78);
      if ((uVar4 & 1) != 0) {
        (*(code *)PTR__ZNK4Aska9Semaphore6SignalEv_02c96cd0)(param_1 + 0x78);
        return;
      }
    }
    return;
  }
  piVar7 = (int *)(param_1 + 0x38);
  iVar5 = 0;
code_r0x021af500:
  do {
    if (*piVar7 != -1) {
      ClearExclusiveLocal();
      bVar3 = iVar5 < 0x1ff;
      iVar5 = iVar5 + 1;
      if (bVar3) goto code_r0x021af500;
      piVar1 = (int *)(param_1 + 0x3c);
      do {
        cVar2 = '\x01';
        bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
        if (bVar3) {
          *piVar1 = *piVar1 + 1;
          cVar2 = ExclusiveMonitorsStatus();
        }
      } while (cVar2 != '\0');
      do {
        if (*piVar7 != -1) {
          ClearExclusiveLocal();
          do {
            uVar4 = Aska::Semaphore::IsReady() const(param_1 + 0x78);
            if ((uVar4 & 1) == 0) {
              do {
                cVar2 = '\x01';
                bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
                if (bVar3) {
                  *piVar1 = *piVar1 + -1;
                  cVar2 = ExclusiveMonitorsStatus();
                }
              } while (cVar2 != '\0');
              Aska::Thread::Sleep(unsigned int)(1);
            }
            else {
              Aska::Semaphore::Wait() const(param_1 + 0x78);
            }
            do {
              cVar2 = '\x01';
              bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
              if (bVar3) {
                *piVar1 = *piVar1 + 1;
                cVar2 = ExclusiveMonitorsStatus();
              }
            } while (cVar2 != '\0');
            while (*piVar7 == -1) {
              cVar2 = '\x01';
              bVar3 = (bool)ExclusiveMonitorPass(piVar7,0x10);
              if (bVar3) {
                *piVar7 = 0;
                cVar2 = ExclusiveMonitorsStatus();
              }
              if (cVar2 == '\0') goto code_r0x021af5b8;
            }
            ClearExclusiveLocal();
          } while( true );
        }
        cVar2 = '\x01';
        bVar3 = (bool)ExclusiveMonitorPass(piVar7,0x10);
        if (bVar3) {
          *piVar7 = 0;
          cVar2 = ExclusiveMonitorsStatus();
        }
      } while (cVar2 != '\0');
code_r0x021af5b8:
      do {
        cVar2 = '\x01';
        bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
        if (bVar3) {
          *piVar1 = *piVar1 + -1;
          cVar2 = ExclusiveMonitorsStatus();
        }
      } while (cVar2 != '\0');
code_r0x021af5c8:
      DataMemoryBarrier(2,3);
      goto code_r0x021af5cc;
    }
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar7,0x10);
    if (bVar3) {
      *piVar7 = 0;
      cVar2 = ExclusiveMonitorsStatus();
    }
    if (cVar2 == '\0') goto code_r0x021af5c8;
  } while( true );
}

// ==== Aska::AHSLCacheManagerV2::RebuildL2Database()
// vaddr 0x20af660 | ghidra 0x21af660 | size 748 | symbol _ZN4Aska18AHSLCacheManagerV217RebuildL2DatabaseEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18AHSLCacheManagerV217RebuildL2DatabaseEv(long param_1)

{
  ushort *puVar1;
  uint *puVar2;
  ushort uVar3;
  uint uVar4;
  long lVar5;
  ulong uVar6;
  int *piVar7;
  short *psVar8;
  int *piVar9;
  int *piVar10;
  int iVar11;
  
  psVar8 = (short *)(param_1 + 0x194b8);
  iVar11 = 0;
  piVar10 = (int *)PTR__ZN4Aska18AHSLDISKCACHEMAGICE_02cbad60;
  do {
    piVar9 = *(int **)(psVar8 + 4);
    if (piVar9 != (int *)0x0) {
      if ((*piVar9 == 0x5348504b) && (puVar1 = (ushort *)(piVar9 + 3), *puVar1 != 0)) {
        uVar3 = 0;
        piVar7 = piVar9 + 0x808;
        do {
          piVar9 = piVar7 + 2;
          if (*piVar9 == *piVar10) break;
          uVar3 = uVar3 + 1;
          piVar7 = (int *)((ulong)(piVar7[1] + 3U & 0xfffffffc) + (long)piVar7);
        } while (uVar3 < *puVar1);
      }
      if (((*piVar9 == *piVar10) && ((short)piVar9[2] == *(short *)(param_1 + 0x17258))) &&
         (*(short *)((long)piVar9 + 10) == *(short *)(param_1 + 0x1725a))) {
        if (*(char *)(param_1 + 0x1748c) == '\0') {
          memcpy(param_1 + 0x17490,piVar9,0x2020);
          uVar3 = Aska::ShaderKeyUtil::CalcCRC16(int, unsigned char const*)(0x2000,param_1 + 0x174b0);
          *(ushort *)(param_1 + 0x1748e) = uVar3;
          *(char *)(param_1 + 0x1748c) = '\x01';
        }
        else {
          uVar3 = *(ushort *)(param_1 + 0x1748e);
        }
        uVar4 = Aska::ShaderKeyUtil::CalcCRC16(int, unsigned char const*)(0x2000,piVar9 + 8);
        if (uVar4 == uVar3) {
          *psVar8 = 0;
          uVar4 = (uint)*(ushort *)(piVar9 + 3);
          if (*(ushort *)(piVar9 + 3) != 0) {
            piVar10 = piVar9 + 0x808;
            do {
              uVar3 = *(ushort *)((long)piVar10 + 2);
              if (uVar3 != *(ushort *)((long)piVar10 + 6)) {
                lVar5 = Aska::AHSLDatabase<Aska::ShaderDiskCache, (unsigned char)9>::GetData(unsigned char const*)(param_1 + 0x198b8,piVar10 + 3);
                if (lVar5 == 0) {
                  if ((*(byte *)((long)piVar10 + 10) >> 5 & 1) != 0) {
                    puVar2 = (uint *)((long)piVar10 + (ulong)*(ushort *)((long)piVar10 + 6));
                    *(ulong *)(puVar2 + 1) = (ulong)*puVar2 + (long)piVar9;
                  }
                  uVar6 = Aska::AHSLCacheManagerV2::BuildLinkedDiskCacheL2(Aska::ShaderDiskCache const*)(param_1,piVar10);
                  if ((uVar6 & 1) != 0) {
                    Aska::AHSLDatabase<Aska::ShaderDiskCache, (unsigned char)9>::SetData(unsigned char*, Aska::ShaderDiskCache*)(param_1 + 0x198b8,piVar10 + 3,piVar10);
                  }
                  *psVar8 = *psVar8 + 1;
                }
              }
              uVar4 = uVar4 - 1;
              piVar10 = (int *)((long)piVar10 + (ulong)uVar3);
            } while (uVar4 != 0);
          }
          piVar10 = (int *)PTR__ZN4Aska18AHSLDISKCACHEMAGICE_02cbad60;
          piVar9 = *(int **)(psVar8 + 4);
          if ((*piVar9 == 0x5348504b) && (puVar1 = (ushort *)(piVar9 + 3), *puVar1 != 0)) {
            uVar3 = 0;
            piVar7 = piVar9 + 0x808;
            do {
              piVar9 = piVar7 + 2;
              if (*piVar9 == *(int *)PTR__ZN4Aska24AHSLLINKEDDISKCACHEMAGICE_02cc3678) break;
              uVar3 = uVar3 + 1;
              piVar7 = (int *)((ulong)(piVar7[1] + 3U & 0xfffffffc) + (long)piVar7);
            } while (uVar3 < *puVar1);
          }
          if (*piVar9 == *(int *)PTR__ZN4Aska24AHSLLINKEDDISKCACHEMAGICE_02cc3678) {
            Aska::RenderDeviceGL::ReadShaderProgramCacheFromMemory(unsigned char const*)(*(undefined8 *)PTR__ZN4Aska12g_pRenderDevE_02cbb1a0);
          }
        }
      }
    }
    iVar11 = iVar11 + 1;
    psVar8 = psVar8 + 0x10;
    if (iVar11 == 0x20) {
      return;
    }
  } while( true );
}

// ==== Aska::AHSLCacheManagerV2::RecompileDiskCache()
// vaddr 0x20af94c | ghidra 0x21af94c | size 4 | symbol _ZN4Aska18AHSLCacheManagerV218RecompileDiskCacheEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18AHSLCacheManagerV218RecompileDiskCacheEv(void)

{
  return;
}

// ==== Aska::AHSLCacheManagerV2::DynamicDiskCacheReplace()
// vaddr 0x20af950 | ghidra 0x21af950 | size 4 | symbol _ZN4Aska18AHSLCacheManagerV223DynamicDiskCacheReplaceEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18AHSLCacheManagerV223DynamicDiskCacheReplaceEv(void)

{
  return;
}

// ==== Aska::AHSLCacheManagerV2::InvalidateObjectShaderCache()
// vaddr 0x20af954 | ghidra 0x21af954 | size 424 | symbol _ZN4Aska18AHSLCacheManagerV227InvalidateObjectShaderCacheEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18AHSLCacheManagerV227InvalidateObjectShaderCacheEv(void)

{
  int *piVar1;
  int *piVar2;
  char cVar3;
  bool bVar4;
  ulong uVar5;
  int iVar6;
  long *plVar7;
  long lVar8;
  undefined8 *puVar9;
  
  lVar8 = *(long *)PTR__ZN4Aska6Global16m_pObjectManagerE_02cc4688;
  piVar1 = (int *)(lVar8 + 0xf98);
  iVar6 = 0;
  do {
    while (*piVar1 == -1) {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = 0;
        cVar3 = ExclusiveMonitorsStatus();
      }
      if (cVar3 == '\0') goto code_r0x021afa3c;
    }
    ClearExclusiveLocal();
    bVar4 = iVar6 < 0x1ff;
    iVar6 = iVar6 + 1;
  } while (bVar4);
  piVar2 = (int *)(lVar8 + 0xf9c);
  do {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar4) {
      *piVar2 = *piVar2 + 1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
  do {
    if (*piVar1 != -1) {
      ClearExclusiveLocal();
      do {
        uVar5 = Aska::Semaphore::IsReady() const(lVar8 + 0xfd8);
        if ((uVar5 & 1) == 0) {
          do {
            cVar3 = '\x01';
            bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
            if (bVar4) {
              *piVar2 = *piVar2 + -1;
              cVar3 = ExclusiveMonitorsStatus();
            }
          } while (cVar3 != '\0');
          Aska::Thread::Sleep(unsigned int)(1);
        }
        else {
          Aska::Semaphore::Wait() const(lVar8 + 0xfd8);
        }
        do {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
          if (bVar4) {
            *piVar2 = *piVar2 + 1;
            cVar3 = ExclusiveMonitorsStatus();
          }
        } while (cVar3 != '\0');
        while (*piVar1 == -1) {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar4) {
            *piVar1 = 0;
            cVar3 = ExclusiveMonitorsStatus();
          }
          if (cVar3 == '\0') goto code_r0x021afa2c;
        }
        ClearExclusiveLocal();
      } while( true );
    }
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar4) {
      *piVar1 = 0;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
code_r0x021afa2c:
  do {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar4) {
      *piVar2 = *piVar2 + -1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
code_r0x021afa3c:
  DataMemoryBarrier(2,3);
  for (plVar7 = *(long **)(lVar8 + 0x18); (long *)(lVar8 + 8) != plVar7; plVar7 = (long *)plVar7[2])
  {
    (**(code **)(*plVar7 + 0x2a8))(plVar7);
  }
  DataMemoryBarrier(2,3);
  *(undefined4 *)(lVar8 + 0xf98) = 0xffffffff;
  DataMemoryBarrier(2,3);
  if (0x14 < *(int *)(lVar8 + 0xf9c)) {
    piVar1 = (int *)(lVar8 + 0xf9c);
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
    uVar5 = Aska::Semaphore::IsReady() const(lVar8 + 0xfd8);
    if ((uVar5 & 1) != 0) {
      Aska::Semaphore::Signal() const(lVar8 + 0xfd8);
    }
  }
  uVar5 = (ulong)*(uint *)(lVar8 + 0x106f8);
  if (0 < (int)*(uint *)(lVar8 + 0x106f8)) {
    puVar9 = (undefined8 *)(lVar8 + 0x104f8);
    do {
      (**(code **)(*(long *)*puVar9 + 0x2a8))();
      uVar5 = uVar5 - 1;
      puVar9 = puVar9 + 1;
    } while (uVar5 != 0);
  }
  return;
}

// ==== Aska::AHSLCacheManagerV2::ExportBackendCompilationDiskCache()
// vaddr 0x20afafc | ghidra 0x21afafc | size 4 | symbol _ZN4Aska18AHSLCacheManagerV233ExportBackendCompilationDiskCacheEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18AHSLCacheManagerV233ExportBackendCompilationDiskCacheEv(void)

{
  return;
}

// ==== Aska::AHSLCacheManagerV2::CreateEmptyShader(unsigned char const*, unsigned char*, bool)
// vaddr 0x20afb00 | ghidra 0x21afb00 | size 180 | symbol _ZN4Aska18AHSLCacheManagerV217CreateEmptyShaderEPKhPhb | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska18AHSLCacheManagerV217CreateEmptyShaderEPKhPhb
               (long param_1,undefined8 param_2,undefined2 *param_3,uint param_4)

{
  uint uVar1;
  undefined2 uVar2;
  undefined2 uVar3;
  int iVar4;
  
  iVar4 = Aska::ShaderKeyUtil::GetShaderKeySize(unsigned char const*)(param_2);
  uVar1 = iVar4 + 0xfU & 0xfffffffc;
  uVar3 = *(undefined2 *)(param_1 + 0x1748e);
  *param_3 = 0;
  param_3[5] = 0;
  uVar2 = (undefined2)uVar1;
  param_3[1] = uVar2;
  param_3[2] = uVar2;
  param_3[3] = uVar2;
  param_3[4] = uVar3;
  memcpy(param_3 + 6,param_2,(long)iVar4);
  memset((long)(param_3 + 6) + (long)iVar4,0,(long)(int)((-0xc - iVar4) + uVar1));
  if ((param_4 & 1) != 0) {
    uVar3 = Aska::ShaderDiskCache::CalcDiskCacheCRC()(param_3);
    *param_3 = uVar3;
  }
  return (long)param_3 + (long)(int)uVar1;
}

// ==== Aska::AHSLCacheManagerV2::Handler_ProcBGQueue(bool)
// vaddr 0x20afbb4 | ghidra 0x21afbb4 | size 8 | symbol _ZN4Aska18AHSLCacheManagerV219Handler_ProcBGQueueEb | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska18AHSLCacheManagerV219Handler_ProcBGQueueEb(void)

{
  return 1;
}

// ==== Aska::AHSLCacheManagerV2::CheckOnHandler(unsigned char*)
// vaddr 0x20afbbc | ghidra 0x21afbbc | size 76 | symbol _ZN4Aska18AHSLCacheManagerV214CheckOnHandlerEPh | lib libSOA-3.7.0.so | 2026-10-04
bool _ZN4Aska18AHSLCacheManagerV214CheckOnHandlerEPh(long param_1,undefined8 param_2)

{
  bool bVar1;
  long lVar2;
  
  lVar2 = Aska::AHSLDatabase<Aska::ShaderCache, (unsigned char)9>::GetData(unsigned char const*)(param_1 + 0x30);
  if (lVar2 == 0) {
    lVar2 = Aska::AHSLDatabase<Aska::ShaderDiskCache, (unsigned char)9>::GetData(unsigned char const*)(param_1 + 0x198b8,param_2);
    bVar1 = lVar2 != 0;
  }
  else {
    bVar1 = true;
  }
  return bVar1;
}

// ==== Aska::AHSLBase::LoadFile(void*, char const*, unsigned int*)
// vaddr 0x20afce4 | ghidra 0x21afce4 | size 236 | symbol _ZN4Aska8AHSLBase8LoadFileEPvPKcPj | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska8AHSLBase8LoadFileEPvPKcPj
               (undefined8 param_1,long param_2,undefined8 param_3,undefined4 *param_4)

{
  undefined *puVar1;
  ulong uVar2;
  long lVar3;
  undefined *puStack_48;
  undefined1 uStack_40;
  long lStack_38;
  
  puVar1 = PTR__ZTVN4Aska4FileE_02cb6e28;
  puStack_48 = PTR__ZTVN4Aska4FileE_02cb6e28 + 0x10;
  lStack_38 = 0;
  uStack_40 = 1;
  uVar2 = Aska::File::Open(char const*, bool, bool, bool)(&puStack_48,param_3,1,0,0);
  if ((uVar2 & 1) == 0) {
    if (param_4 == (undefined4 *)0x0) {
      param_2 = 0;
    }
    else {
      param_2 = 0;
      *param_4 = 0;
    }
  }
  else {
    lVar3 = Aska::File::GetFileSize() const(&puStack_48);
    if (param_4 != (undefined4 *)0x0) {
      *param_4 = (int)lVar3;
    }
    if ((param_2 != 0) ||
       (param_2 = operator new[](unsigned long, std::nothrow_t const&)(lVar3 + 1,PTR__ZSt7nothrow_02cb9a80), param_2 != 0)) {
      Aska::File::Read(void*, unsigned long, unsigned int*)(&puStack_48,param_2,lVar3,0);
      *(undefined1 *)(param_2 + lVar3) = 0;
    }
    Aska::File::Close()(&puStack_48);
  }
  puStack_48 = puVar1 + 0x10;
  if (lStack_38 != 0) {
    Aska::File::Close()(&puStack_48);
  }
  return param_2;
}

// ==== Aska::AHSLBase::CopyString(char*, char const*, int)
// vaddr 0x20afdd0 | ghidra 0x21afdd0 | size 44 | symbol _ZN4Aska8AHSLBase10CopyStringEPcPKci | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZN4Aska8AHSLBase10CopyStringEPcPKci
                (undefined8 param_1,long param_2,long param_3,uint param_4)

{
  ulong uVar1;
  
  uVar1 = 0;
  do {
    if (*(char *)(param_3 + uVar1) == '\0') {
      return uVar1 & 0xffffffff;
    }
    *(char *)(param_2 + uVar1) = *(char *)(param_3 + uVar1);
    uVar1 = uVar1 + 1;
  } while (param_4 != (uint)uVar1);
  return (ulong)param_4;
}

// ==== Aska::AHSLBase::CopyIntString(char*, int, int)
// vaddr 0x20afdfc | ghidra 0x21afdfc | size 100 | symbol _ZN4Aska8AHSLBase13CopyIntStringEPcii | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZN4Aska8AHSLBase13CopyIntStringEPcii
                (undefined8 param_1,long param_2,undefined4 param_3,uint param_4)

{
  ulong uVar1;
  char acStack_30 [16];
  
  Aska::detail::Itoa(int, char*, int)(param_3,acStack_30,10);
  uVar1 = 0;
  do {
    if (acStack_30[uVar1] == '\0') {
      return uVar1 & 0xffffffff;
    }
    *(char *)(param_2 + uVar1) = acStack_30[uVar1];
    uVar1 = uVar1 + 1;
  } while (param_4 != (uint)uVar1);
  return (ulong)param_4;
}

// ==== Aska::AHSLBase::ChopTailNumber(char*, char const*)
// vaddr 0x20afe60 | ghidra 0x21afe60 | size 100 | symbol _ZN4Aska8AHSLBase14ChopTailNumberEPcPKc | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska8AHSLBase14ChopTailNumberEPcPKc(undefined8 param_1,char *param_2,char *param_3)

{
  char cVar1;
  long lVar2;
  undefined8 uVar3;
  long lVar4;
  
  cVar1 = *param_3;
  while (cVar1 != '\0') {
    param_3 = param_3 + 1;
    *param_2 = cVar1;
    param_2 = param_2 + 1;
    cVar1 = *param_3;
  }
  *param_2 = '\0';
  lVar2 = 0;
  do {
    lVar4 = lVar2;
    lVar2 = lVar4 + -1;
  } while ((byte)param_2[lVar4 + -1] - 0x30 < 10);
  if (lVar4 + -1 != -1) {
    uVar3 = atoi(param_2 + lVar4);
    param_2[lVar4] = '\0';
    return uVar3;
  }
  return 0;
}

// ==== Aska::AHSLBase::Static::IsValidTargetConsole(Aska::AHSLBase::TargetConsole)
// vaddr 0x20afec4 | ghidra 0x21afec4 | size 12 | symbol _ZN4Aska8AHSLBase6Static20IsValidTargetConsoleENS0_13TargetConsoleE | lib libSOA-3.7.0.so | 2026-10-04
bool _ZN4Aska8AHSLBase6Static20IsValidTargetConsoleENS0_13TargetConsoleE(uint param_1)

{
  return param_1 < 0xc;
}

// ==== Aska::AHSLCompiler::GeneratePipeCode(char**, Aska::TLongInt<unsigned long, 1>, Aska::AHSLBase::TargetConsole)
// vaddr 0x20b184c | ghidra 0x21b184c | size 2648 | symbol _ZN4Aska12AHSLCompiler16GeneratePipeCodeEPPcNS_8TLongIntImLi1EEENS_8AHSLBase13TargetConsoleE | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska12AHSLCompiler16GeneratePipeCodeEPPcNS_8TLongIntImLi1EEENS_8AHSLBase13TargetConsoleE
               (undefined8 param_1,undefined8 *param_2,ulong param_3,uint param_4)

{
  int iVar1;
  bool bVar2;
  uint uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  ulong uVar9;
  int iVar10;
  undefined *puVar11;
  undefined1 uVar12;
  undefined8 *puVar13;
  uint uVar14;
  int iVar15;
  ulong uVar16;
  long lVar17;
  int *piVar18;
  uint *puVar19;
  byte *pbVar20;
  byte bVar21;
  undefined1 uVar22;
  undefined4 *puVar23;
  undefined4 *puVar24;
  uint uVar25;
  uint uVar26;
  undefined8 *puVar27;
  long *plVar28;
  int iVar29;
  ulong uVar30;
  ulong uVar31;
  ulong uVar32;
  undefined1 auStack_718 [128];
  undefined1 auStack_698 [64];
  undefined1 auStack_658 [64];
  undefined1 auStack_618 [64];
  undefined1 auStack_5d8 [40];
  undefined8 uStack_5b0;
  long lStack_5a8;
  long alStack_5a0 [89];
  long lStack_2d8;
  long lStack_2d0;
  int iStack_2c8;
  uint uStack_2c4;
  undefined *puStack_2c0;
  byte abStack_2b8 [128];
  byte abStack_238 [32];
  byte abStack_218 [32];
  byte abStack_1f8 [128];
  undefined1 auStack_178 [128];
  byte abStack_f8 [128];
  undefined8 uStack_78;
  uint uStack_70;
  undefined4 uStack_6c;
  int iStack_68;
  
  memset(abStack_2b8,0,0xc0);
  uStack_78 = 0;
  iStack_68 = 0;
  uVar25 = (uint)param_3;
  bVar2 = (uVar25 >> 3 & 1) != 0;
  if (bVar2) {
    abStack_1f8[0] = 0xb;
    auStack_178[0] = param_4 == 2;
    iStack_68 = *(int *)(PTR_aPieceInfo_02cba770 + 0x16c);
    abStack_f8[0] = auStack_178[0];
  }
  uStack_6c = 0;
  uStack_70 = (uint)bVar2;
  if ((10 < param_4) || (uVar12 = 1, (1 << (ulong)(param_4 & 0x1f) & 0x644U) == 0)) {
    uVar12 = 0;
  }
  if ((param_4 - 5 < 5) && ((0x1bU >> (ulong)(param_4 - 5 & 0x1f) & 1) != 0)) {
    uVar26 = 1;
    uVar16 = (ulong)(uVar25 >> 0xc & 0xf);
    if ((uVar25 >> 0x14 & 1) == 0) goto code_r0x021b1918;
code_r0x021b1988:
    if ((int)uVar16 != 0) {
      lVar17 = 0;
      piVar18 = (int *)(PTR_aPieceInfo_02cba770 + 0x18c);
      do {
        abStack_1f8[(int)uStack_70] = (char)lVar17 + 0xc;
        lVar17 = lVar17 + 1;
        auStack_178[(int)uStack_70] = uVar12;
        abStack_f8[(int)uStack_70] = 0;
        uStack_70 = uStack_70 + 1;
        iStack_68 = iStack_68 + *piVar18;
        piVar18 = piVar18 + 8;
      } while (lVar17 < (long)uVar16);
    }
  }
  else {
    uVar26 = (uint)(param_4 == 0xb);
    uVar16 = (ulong)(uVar25 >> 0xc & 0xf);
    if ((uVar25 >> 0x14 & 1) != 0) goto code_r0x021b1988;
code_r0x021b1918:
    if ((int)uVar16 != 0) {
      lVar17 = 0;
      piVar18 = (int *)(PTR_aPieceInfo_02cba770 + 0x2c);
      do {
        lVar17 = lVar17 + 1;
        abStack_1f8[(int)uStack_70] = (byte)lVar17;
        auStack_178[(int)uStack_70] = uVar12;
        abStack_f8[(int)uStack_70] = 0;
        uStack_70 = uStack_70 + 1;
        iStack_68 = iStack_68 + *piVar18;
        piVar18 = piVar18 + 8;
      } while (lVar17 < (long)uVar16);
    }
  }
  if ((uVar25 >> 0x19 & 1) == 0) {
    if ((uVar25 >> 0x1a & 1) != 0) goto code_r0x021b1ad8;
code_r0x021b19f4:
    if ((uVar25 >> 0x1b & 1) != 0) goto code_r0x021b1b28;
code_r0x021b19f8:
    if (param_4 == 2) goto code_r0x021b1b7c;
code_r0x021b1a00:
    lVar17 = 0;
    puVar19 = (uint *)(PTR_aPieceInfo_02cba770 + 0x338);
    uVar14 = uStack_70;
    do {
      if ((1L << ((ulong)*puVar19 & 0x3f) & param_3) != 0) {
        abStack_1f8[(int)uVar14] = (char)lVar17 + 0x19;
        uVar22 = uVar12;
        if (3 < (int)lVar17 - 0xcU) {
          uVar22 = 0;
        }
        auStack_178[(int)uStack_70] = uVar22;
        uVar3 = puVar19[-3];
        abStack_f8[(int)uStack_70] = 0;
        uVar14 = uStack_70 + 1;
        iStack_68 = iStack_68 + uVar3;
        uStack_70 = uVar14;
      }
      lVar17 = lVar17 + 1;
      puVar19 = puVar19 + 8;
    } while (lVar17 != 0x13);
  }
  else {
    abStack_1f8[(int)uStack_70] = 0x16;
    auStack_178[(int)uStack_70] = uVar12;
    abStack_f8[(int)uStack_70] = 0;
    uStack_70 = uStack_70 + 1;
    iStack_68 = iStack_68 + *(int *)(PTR_aPieceInfo_02cba770 + 0x2cc);
    if ((uVar25 >> 0x1a & 1) == 0) goto code_r0x021b19f4;
code_r0x021b1ad8:
    abStack_1f8[(int)uStack_70] = 0x17;
    auStack_178[(int)uStack_70] = uVar12;
    abStack_f8[(int)uStack_70] = 0;
    uStack_70 = uStack_70 + 1;
    iStack_68 = iStack_68 + *(int *)(PTR_aPieceInfo_02cba770 + 0x2ec);
    if ((uVar25 >> 0x1b & 1) == 0) goto code_r0x021b19f8;
code_r0x021b1b28:
    abStack_1f8[(int)uStack_70] = 0x18;
    auStack_178[(int)uStack_70] = uVar12;
    abStack_f8[(int)uStack_70] = 0;
    uStack_70 = uStack_70 + 1;
    iStack_68 = iStack_68 + *(int *)(PTR_aPieceInfo_02cba770 + 0x30c);
    if (param_4 != 2) goto code_r0x021b1a00;
code_r0x021b1b7c:
    lVar17 = 0;
    pbVar20 = PTR_aPieceInfo_02cba770 + 0x33c;
    uVar14 = uStack_70;
    do {
      if ((1L << ((ulong)*(uint *)(pbVar20 + -4) & 0x3f) & param_3) != 0) {
        if ((int)lVar17 - 0xcU < 4) {
          bVar21 = 0;
          uVar22 = uVar12;
        }
        else {
          bVar21 = *pbVar20;
          uVar22 = 0;
        }
        abStack_1f8[(int)uVar14] = (char)lVar17 + 0x19;
        auStack_178[(int)uStack_70] = uVar22;
        abStack_f8[(int)uStack_70] = bVar21;
        uVar14 = uStack_70 + 1;
        iStack_68 = iStack_68 + *(int *)(pbVar20 + -0x10);
        uStack_70 = uVar14;
      }
      lVar17 = lVar17 + 1;
      pbVar20 = pbVar20 + 0x20;
    } while (lVar17 != 0x13);
  }
  puVar13 = (undefined8 *)*param_2;
  iStack_2c8 = 0;
  lStack_2d8 = operator new[](unsigned long, std::nothrow_t const&)(0x1000,PTR__ZSt7nothrow_02cb9a80);
  puStack_2c0 = &UNK_029c5ced/*"Pipe."*/;
  if (param_4 == 4) {
    puVar11 = &UNK_029c5bd7/*"SV_Position"*/;
  }
  else if (param_4 == 7) {
    puVar11 = &UNK_029c5be3/*"S_POSITION"*/;
  }
  else {
    puVar11 = &UNK_029c5be5/*"POSITION"*/;
  }
  lStack_2d0 = lStack_2d8;
  uStack_2c4 = uVar26;
  PipeFormatter::Set(char const*, char const*, char const*, char const*, char const*, char const*)(auStack_5d8,0,&UNK_029c5c2e/*"float4"*/,&UNK_029c5bcf/*"vOutPos"*/,puVar11,&UNK_029c5bcf/*"vOutPos"*/,0);
  bVar2 = (uVar25 >> 1 & 1) != 0;
  if (bVar2) {
    PipeFormatter::Set(char const*, char const*, char const*, char const*, char const*, char const*)(auStack_5d8,&UNK_029c5bcb/*"HIP"*/,&UNK_029c5c2e/*"float4"*/,&UNK_029c5bee/*"vPosThru"*/,&UNK_029c5bf7/*"CENTROID(TEXCOORD0)"*/,
                    &UNK_029c5c0b/*"float4(vPos.xyz,vsin.vPos.w)"*/,&UNK_029c5c28/*"vPos"*/);
  }
  uVar26 = (uint)bVar2;
  if ((uVar25 >> 9 & 1) != 0) {
    puVar11 = &UNK_029c5c2e/*"float4"*/;
    if (param_4 == 2) {
      puVar11 = &UNK_029c5c2d/*"sfloat4"*/;
    }
    PipeFormatter::Set(char const*, char const*, char const*, char const*, char const*, char const*)(auStack_5d8,&UNK_029c5bcb/*"HIP"*/,puVar11,&UNK_029cd7a7/*"vColor"*/,&UNK_029c5c35/*"CENTROID_COLOR(COLOR0)"*/,&UNK_029c5c4c/*"vOutputColor"*/,
                    &UNK_029c5c59/*"vVertexColor"*/);
  }
  if ((uVar25 >> 10 & 1) != 0) {
    puVar11 = &UNK_029c5c2e/*"float4"*/;
    if (param_4 == 2) {
      puVar11 = &UNK_029c5c2d/*"sfloat4"*/;
    }
    PipeFormatter::Set(char const*, char const*, char const*, char const*, char const*, char const*)(auStack_5d8,&UNK_029c5bcb/*"HIP"*/,puVar11,&UNK_029c5c66/*"vColor2"*/,&UNK_029c5c6e/*"CENTROID_COLOR(COLOR1)"*/,&UNK_029c5c85/*"vVertexColor2"*/,
                    &UNK_029c5c85/*"vVertexColor2"*/);
  }
  puVar11 = PTR_aPieceInfo_02cba770;
  if (param_4 == 2) {
    PipeLayout::Assign(int, bool, bool, bool)(abStack_2b8,10 - uVar26,1,0,1);
  }
  else {
    uVar16 = (ulong)uStack_70;
    uVar25 = iStack_68 + 3 >> 2;
    uStack_78 = CONCAT44(uStack_78._4_4_,uVar25);
    if ((int)uStack_70 < 1) goto code_r0x021b1e08;
    uVar30 = 0;
    do {
      PipeLayout::AssignPiece(int, int, bool)(abStack_2b8,(ulong)abStack_1f8[uVar30],
                      *(undefined4 *)(puVar11 + (ulong)abStack_1f8[uVar30] * 0x20 + 0xc),
                      auStack_178[uVar30]);
      uVar30 = uVar30 + 1;
    } while (uVar16 != uVar30);
  }
  uVar25 = (uint)uStack_78;
code_r0x021b1e08:
  if (0 < (int)uVar25) {
    iVar10 = 0;
    uVar16 = 0;
    do {
      sprintf(auStack_618,&UNK_029dc524/*"%s%s"*/,
                      *(undefined8 *)
                       (PTR_aPiecePrecisionName_02cb9b88 + (ulong)abStack_218[uVar16] * 8),
                      *(undefined8 *)(&UNK_02c485f8 + (ulong)abStack_238[uVar16] * 8));
      sprintf(auStack_658,&UNK_029c5c93/*"vPacked%d"*/,uVar16 & 0xffffffff);
      sprintf(auStack_698,&UNK_029c5c9d/*"CENTROID(TEXCOORD%d)"*/,uVar26 + (int)uVar16);
      SprintStorePipeAssign(char*, int, unsigned char*, unsigned char)(auStack_718,abStack_238[uVar16],abStack_2b8 + iVar10,abStack_218[uVar16]);
      PipeFormatter::Set(char const*, char const*, char const*, char const*, char const*, char const*)(auStack_5d8,&UNK_029c5bcb/*"HIP"*/,auStack_618,auStack_658,auStack_698,auStack_718,0);
      uVar16 = uVar16 + 1;
      iVar10 = iVar10 + 4;
    } while (uVar25 != uVar16);
  }
  uVar4 = CONCAT26(_UNK_029c5cb8,_UNK_029c5cb2);
  *(ulong *)((long)puVar13 + 6) = CONCAT62(_UNK_029c5cba,_UNK_029c5cb8);
  *puVar13 = uVar4;
  puVar23 = (undefined4 *)((long)puVar13 + 0xd);
  if (0 < iStack_2c8) {
    lVar17 = 0;
    plVar28 = alStack_5a0;
    do {
      iVar10 = sprintf(puVar23,&UNK_029c5d28,plVar28[-6],plVar28[-5],plVar28[-4]);
      puVar23 = (undefined4 *)((long)puVar23 + (long)iVar10);
      if (*plVar28 != 0) {
        iVar10 = sprintf(puVar23,&UNK_029c5d37/*"/* %s */"*/);
        puVar23 = (undefined4 *)((long)puVar23 + (long)iVar10);
      }
      lVar17 = lVar17 + 1;
      plVar28 = plVar28 + 8;
    } while (lVar17 < iStack_2c8);
  }
  *(undefined2 *)(puVar23 + 1) = 10;
  uVar7 = _UNK_029c5cce;
  uVar4 = _UNK_029c5cc6;
  *puVar23 = 0xa3b7d0a;
  *(undefined4 *)((long)puVar23 + 0x15) = 0x204550;
  *(undefined8 *)((long)puVar23 + 0xd) = uVar7;
  *(undefined8 *)((long)puVar23 + 5) = uVar4;
  uVar8 = _UNK_029c5d50;
  uVar7 = _UNK_029c5d48;
  uVar4 = _UNK_029c5d40;
  puVar13 = (undefined8 *)(puVar23 + 6);
  if (uStack_2c4 == 1) {
    uVar6 = CONCAT62(_UNK_029c5d60,_UNK_029c5d5e);
    uVar5 = CONCAT26(_UNK_029c5d5e,_UNK_029c5d58);
    *(undefined8 *)((long)puVar23 + 0x3e) = _UNK_029c5d66;
    *(undefined8 *)((long)puVar23 + 0x36) = uVar6;
    *(undefined8 *)(puVar23 + 8) = uVar7;
    *puVar13 = uVar4;
    *(undefined8 *)(puVar23 + 0xc) = uVar5;
    *(undefined8 *)(puVar23 + 10) = uVar8;
    puVar13 = (undefined8 *)((long)puVar23 + 0x45);
    if (0 < iStack_2c8) {
      lVar17 = 0;
      puVar27 = &uStack_5b0;
      do {
        iVar10 = sprintf(puVar13,&UNK_029c5d6e,puStack_2c0,puVar27[-3],*puVar27);
        lVar17 = lVar17 + 1;
        puVar13 = (undefined8 *)((long)puVar13 + (long)iVar10);
        puVar27 = puVar27 + 8;
      } while (lVar17 < iStack_2c8);
    }
  }
  else if (0 < iStack_2c8) {
    lVar17 = 0;
    puVar27 = &uStack_5b0;
    do {
      iVar10 = sprintf(puVar13,&UNK_029c5d6e,puStack_2c0,puVar27[-3],*puVar27);
      lVar17 = lVar17 + 1;
      puVar13 = (undefined8 *)((long)puVar13 + (long)iVar10);
      puVar27 = puVar27 + 8;
    } while (lVar17 < iStack_2c8);
  }
  *(undefined1 *)((long)puVar13 + 2) = 0;
  uVar7 = _UNK_029c5ce2;
  uVar4 = _UNK_029c5cda;
  *(undefined2 *)puVar13 = 0xa0a;
  *(undefined2 *)((long)puVar13 + 0x12) = 0x2045;
  *(undefined8 *)((long)puVar13 + 10) = uVar7;
  *(undefined8 *)((long)puVar13 + 2) = uVar4;
  puVar23 = (undefined4 *)((long)puVar13 + 0x14);
  *(undefined1 *)puVar23 = 0;
  if (0 < iStack_2c8) {
    lVar17 = 0;
    plVar28 = &lStack_5a8;
    iVar10 = iStack_2c8;
    do {
      if (*plVar28 != 0) {
        iVar10 = sprintf(puVar23,&UNK_029c5d7c,*plVar28,puStack_2c0,plVar28[-4]);
        puVar23 = (undefined4 *)((long)puVar23 + (long)iVar10);
        iVar10 = iStack_2c8;
      }
      lVar17 = lVar17 + 1;
      plVar28 = plVar28 + 8;
    } while (lVar17 < iVar10);
  }
  uVar16 = (ulong)uStack_70;
  if (0 < (int)uStack_70) {
    uVar30 = 0;
    do {
      puVar11 = PTR_aPieceInfo_02cba770;
      bVar21 = abStack_1f8[uVar30];
      iVar10 = sprintf(puVar23,&UNK_029c5cfc,
                               *(undefined8 *)
                                (PTR_aPieceInfo_02cba770 + (ulong)bVar21 * 0x20 + 0x10),
                               *(undefined8 *)
                                (&UNK_02c485d0 +
                                (long)*(int *)(PTR_aPieceInfo_02cba770 + (ulong)bVar21 * 0x20 + 0xc)
                                * 8),*(undefined8 *)
                                      (PTR_aPiecePrecisionName_02cb9b88 +
                                      (ulong)abStack_f8[uVar30] * 8),
                               *(undefined8 *)
                                (&UNK_02c485f8 +
                                (long)*(int *)(PTR_aPieceInfo_02cba770 + (ulong)bVar21 * 0x20 + 0xc)
                                * 8));
      uVar25 = *(uint *)(puVar11 + (ulong)bVar21 * 0x20 + 8);
      uVar9 = 0;
      do {
        uVar31 = uVar9;
        uVar9 = uVar31 + 1;
      } while (abStack_2b8[uVar31] >> 2 != uVar25);
      iVar29 = *(int *)(puVar11 + (long)(int)uVar25 * 0x20 + 0xc);
      puVar24 = (undefined4 *)((long)puVar23 + (long)iVar10);
      if (iVar29 != 0) {
        iVar10 = -1;
        do {
          uVar9 = (long)(int)uVar31;
          iVar1 = (int)uVar31 + -1;
          do {
            iVar15 = iVar1;
            uVar32 = uVar9;
            uVar31 = uVar32 + 1;
            iVar1 = iVar15 + 1;
            uVar9 = uVar31;
          } while (abStack_2b8[uVar32] >> 2 != uVar25);
          iVar15 = iVar15 + 4;
          if (-1 < iVar1) {
            iVar15 = iVar1;
          }
          iVar15 = iVar15 >> 2;
          bVar21 = abStack_238[iVar15];
          if (iVar15 != iVar10) {
            puVar11 = &UNK_029c5d8b/*" %s%s%d."*/;
            if (iVar10 != -1) {
              puVar11 = &UNK_029c5d8a/*", %s%s%d."*/;
            }
            iVar10 = sprintf(puVar24,puVar11,&UNK_029c5ced/*"Pipe."*/,&UNK_029c5d0c/*"vPacked"*/,iVar15);
            puVar24 = (undefined4 *)((long)puVar24 + (long)iVar10);
            iVar10 = iVar15;
          }
          if (bVar21 == 1) {
            lVar17 = -1;
          }
          else {
            uVar12 = PTR__ZZN10PipeLayout19PrintLoadPipeAssignEPPciPKcS3_E11szComponent_02cbf698
                     [uVar32 & 3];
            *(undefined1 *)((long)puVar24 + 1) = 0;
            *(undefined1 *)puVar24 = uVar12;
            lVar17 = 1;
          }
          iVar29 = iVar29 + -1;
          puVar24 = (undefined4 *)((long)puVar24 + lVar17);
        } while (iVar29 != 0);
      }
      uVar30 = uVar30 + 1;
      puVar23 = (undefined4 *)((long)puVar24 + 3);
      *puVar24 = 0x3b2920;
    } while (uVar30 != uVar16);
  }
  *(undefined2 *)puVar23 = 0xa0a;
  *(undefined1 *)((long)puVar23 + 2) = 0;
  *param_2 = (undefined2 *)((long)puVar23 + 2);
  if (lStack_2d8 != 0) {
    operator delete[](void*)();
  }
  return;
}

// ==== Aska::AHSLBase::CreateCompressedShaderCache(Aska::ShaderDiskCache*, void*, unsigned char*)
// vaddr 0x20b2eec | ghidra 0x21b2eec | size 148 | symbol _ZN4Aska8AHSLBase27CreateCompressedShaderCacheEPNS_15ShaderDiskCacheEPvPh | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska8AHSLBase27CreateCompressedShaderCacheEPNS_15ShaderDiskCacheEPvPh
          (long param_1,long param_2,long param_3,undefined8 param_4)

{
  long lVar1;
  short sVar2;
  undefined8 uVar3;
  uint uVar4;
  
  uVar4 = *(int *)(param_1 + 8) - 5;
  if (uVar4 < 7) {
    uVar4 = *(uint *)(&UNK_029c5da0/*"0"*/ + (long)(int)uVar4 * 4);
  }
  else {
    uVar4 = 0;
  }
  lVar1 = (ulong)*(ushort *)(param_2 + 6) + (ulong)uVar4;
  memcpy(param_3,param_2,lVar1);
  uVar3 = Aska::ShaderCompression::CompressLZwordDic(void*, int, void*, unsigned char*)(lVar1 + param_2,(uint)*(ushort *)(param_2 + 4) - (int)lVar1,
                          lVar1 + param_3,param_4);
  if ((int)uVar3 != 0) {
    sVar2 = (short)uVar3;
    uVar3 = 1;
    *(short *)(param_3 + 2) = sVar2 + (short)lVar1;
    *(undefined1 *)(param_3 + 10) = 3;
  }
  return uVar3;
}

// ==== Aska::AHSLBase::GetSizeOfShaderCacheBodyForCompression() const
// vaddr 0x20b2f80 | ghidra 0x21b2f80 | size 40 | symbol _ZNK4Aska8AHSLBase38GetSizeOfShaderCacheBodyForCompressionEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK4Aska8AHSLBase38GetSizeOfShaderCacheBodyForCompressionEv(long param_1)

{
  uint uVar1;
  
  uVar1 = *(int *)(param_1 + 8) - 5;
  if (uVar1 < 7) {
    return *(undefined4 *)(&UNK_029c5da0/*"0"*/ + (long)(int)uVar1 * 4);
  }
  return 0;
}

// ==== Aska::AHSLBase::UncompressShaderCache(Aska::ShaderDiskCache*, Aska::ShaderDiskCache const*, unsigned char*)
// vaddr 0x20b2fa8 | ghidra 0x21b2fa8 | size 196 | symbol _ZN4Aska8AHSLBase21UncompressShaderCacheEPNS_15ShaderDiskCacheEPKS1_Ph | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska8AHSLBase21UncompressShaderCacheEPNS_15ShaderDiskCacheEPKS1_Ph
               (long param_1,long param_2,long param_3,undefined8 param_4)

{
  byte bVar1;
  undefined2 uVar2;
  uint uVar3;
  long lVar4;
  
  bVar1 = *(byte *)(param_3 + 10);
  if ((bVar1 & 3) != 0) {
    uVar3 = *(int *)(param_1 + 8) - 5;
    if (uVar3 < 7) {
      lVar4 = *(long *)(&UNK_029c5dc0/*"0"*/ + (long)(int)uVar3 * 8);
    }
    else {
      lVar4 = 0;
    }
    lVar4 = lVar4 + (ulong)*(ushort *)(param_3 + 6);
    memcpy(param_2,param_3,lVar4);
    bVar1 = bVar1 & 3;
    if (bVar1 == 3) {
      Aska::ShaderCompression::DecompressLZwordDic(unsigned short*, unsigned short*, unsigned char*)(lVar4 + param_3,lVar4 + param_2,param_4);
    }
    else if (bVar1 == 2) {
      Aska::ShaderCompression::DecompressLZword(unsigned short*, unsigned short*)();
    }
    else if (bVar1 == 1) {
      Aska::ShaderCompression::DecompressLZ(unsigned char*, unsigned char*)();
    }
    uVar2 = *(undefined2 *)(param_3 + 4);
    *(undefined1 *)(param_2 + 10) = 0;
    *(undefined2 *)(param_2 + 2) = uVar2;
    param_3 = param_2;
  }
  return param_3;
}


// FAILED to create function at 02c484b8 Aska::AHSLCacheManagerV2::vtable
// FAILED to create function at 02c484e8 Aska::AHSLBase::typeinfo
// FAILED to create function at 02c48520 Aska::AHSLCacheManagerV2::typeinfo
