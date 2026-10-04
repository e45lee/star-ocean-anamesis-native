// port/decomp/kernel/global.c: Ghidra decompiles for the kernel subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-04 06:18 UTC: tools/decomp.sh '--into' 'kernel/global' 'Aska::Global::Get' 'Aska::Global::InitAll' 'Aska::Global::RegisterPeripheral'

// ==== Aska::Global::GetAvailableMemoryManager()
// vaddr 0x1f49d14 | ghidra 0x2049d14 | size 32 | symbol _ZN4Aska6Global25GetAvailableMemoryManagerEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska6Global25GetAvailableMemoryManagerEv(void)

{
  long lVar1;
  
  lVar1 = *(long *)PTR__ZN4Aska6Global16m_pMemoryManagerE_02cbd3f0;
  if (*(long *)PTR__ZN4Aska6Global16m_pMemoryManagerE_02cbd3f0 == 0) {
    lVar1 = lRam0000000002dcc6a0;
  }
  return lVar1;
}

// ==== Aska::Global::GetPadCapture(int*)
// vaddr 0x1f5720c | ghidra 0x205720c | size 8 | symbol _ZN4Aska6Global13GetPadCaptureEPi | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska6Global13GetPadCaptureEPi(void)

{
  return 0;
}

// ==== Aska::Global::GetActivePad()
// vaddr 0x1f572a4 | ghidra 0x20572a4 | size 32 | symbol _ZN4Aska6Global12GetActivePadEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska6Global12GetActivePadEv(void)

{
  if (*(long *)PTR__ZN4Aska6Global20m_pPeripheralManagerE_02cc47d0 != 0) {
    return *(undefined8 *)(*(long *)PTR__ZN4Aska6Global20m_pPeripheralManagerE_02cc47d0 + 0x20);
  }
  return 0;
}

// ==== Aska::Global::RegisterPeripheral(int, Aska::BasePeripheral*)
// vaddr 0x1f572c4 | ghidra 0x20572c4 | size 76 | symbol _ZN4Aska6Global18RegisterPeripheralEiPNS_14BasePeripheralE | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska6Global18RegisterPeripheralEiPNS_14BasePeripheralE(int param_1,long *param_2)

{
  undefined8 uVar1;
  
  uVar1 = 0;
  if ((param_1 == 0) && (*(long *)PTR__ZN4Aska6Global20m_pPeripheralManagerE_02cc47d0 != 0)) {
    *(long **)(*(long *)PTR__ZN4Aska6Global20m_pPeripheralManagerE_02cc47d0 + 0x20) = param_2;
    (**(code **)(*param_2 + 0x38))(param_2,0);
    uVar1 = 1;
    *(undefined1 *)(param_2 + 0x13) = 0;
  }
  return uVar1;
}

// ==== Aska::Global::GetPeripheral(int)
// vaddr 0x1f57338 | ghidra 0x2057338 | size 36 | symbol _ZN4Aska6Global13GetPeripheralEi | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska6Global13GetPeripheralEi(int param_1)

{
  undefined8 uVar1;
  
  uVar1 = 0;
  if ((param_1 == 0) && (*(long *)PTR__ZN4Aska6Global20m_pPeripheralManagerE_02cc47d0 != 0)) {
    uVar1 = *(undefined8 *)(*(long *)PTR__ZN4Aska6Global20m_pPeripheralManagerE_02cc47d0 + 0x20);
  }
  return uVar1;
}

// ==== Aska::Global::GetExPeripheral(int)
// vaddr 0x1f573d0 | ghidra 0x20573d0 | size 32 | symbol _ZN4Aska6Global15GetExPeripheralEi | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska6Global15GetExPeripheralEi(int param_1)

{
  if (param_1 != 0) {
    return 0;
  }
  return *(undefined8 *)(*(long *)PTR__ZN4Aska6Global20m_pPeripheralManagerE_02cc47d0 + 0x28);
}

// ==== Aska::Global::GetText()
// vaddr 0x1f83d00 | ghidra 0x2083d00 | size 8 | symbol _ZN4Aska6Global7GetTextEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska6Global7GetTextEv(void)

{
  return 0;
}

// ==== Aska::Global::InitAll()
// vaddr 0x220fa98 | ghidra 0x230fa98 | size 908 | symbol _ZN4Aska6Global7InitAllEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska6Global7InitAllEv(void)

{
  undefined8 uVar1;
  undefined *puVar2;
  ulong uVar3;
  long lVar4;
  long *plVar5;
  ushort auStack_40 [2];
  undefined4 uStack_3c;
  undefined2 uStack_36;
  uint uStack_34;
  uint auStack_30 [3];
  undefined4 uStack_24;
  
  puVar2 = PTR__ZN4Aska6Global6m_pAppE_02cc2078;
  plVar5 = *(long **)PTR__ZN4Aska6Global6m_pAppE_02cc2078;
  (**(code **)(*plVar5 + 0x10))(plVar5);
  *(undefined1 *)(plVar5 + 0x28) = 1;
  uVar3 = Aska::Global::InitializeMemoryManager(unsigned long)(0);
  if ((uVar3 & 1) != 0) {
    Aska::detail::SmallHeapProxy::Initialize()();
    Aska::App::LocalInit()(plVar5);
    (**(code **)(*plVar5 + 0x18))(plVar5);
    uVar3 = Aska::Global::InstantiateSystemCallbackManager()();
    if (((uVar3 & 1) != 0) && (lVar4 = *(long *)puVar2, lVar4 != 0)) {
      *(undefined8 *)PTR__ZN4Aska6Global20m_pszStorageRootPathE_02cbf040 =
           *(undefined8 *)(lVar4 + 8);
      *(undefined8 *)PTR__ZN4Aska6Global29m_pszUserGeneratedContentPathE_02cbda18 =
           *(undefined8 *)(lVar4 + 0x10);
      uVar1 = *(undefined8 *)(lVar4 + 0x20);
      *(undefined8 *)PTR__ZN4Aska6Global17m_pszTempFilePathE_02cc4170 =
           *(undefined8 *)(lVar4 + 0x18);
      *(undefined8 *)PTR__ZN4Aska6Global24m_pszDownloadContentPathE_02cbe1a8 = uVar1;
      uVar3 = Aska::Global::InstantiateLogger()();
      if ((uVar3 & 1) != 0) {
        Aska::GetLocalTime(Aska::ASKATIME*)(auStack_40);
        auStack_30[0] = (uint)auStack_40[0] | uStack_34 / 1000 << 0x10;
        uStack_24 = uStack_3c;
        *(int *)PTR__ZN4Aska26g_uiLowPrecisionRandomSeedE_02cbb068 =
             CONCAT22((undefined2)uStack_3c,uStack_36) * 0x9534c85 + 0x9535932;
        Aska::InitRandom(unsigned int)();
        Aska::InitHighPrecisionRandom(unsigned int*, int)(auStack_30,4);
        uVar3 = Aska::Global::InitializeThreadManager()();
        if (((uVar3 & 1) != 0) && (uVar3 = Aska::Global::InstantiateVideoManager()(), (uVar3 & 1) != 0)) {
          Aska::RenderDeviceGL::GetImageFlags() const(*(undefined8 *)
                           (*(long *)PTR__ZN4Aska6Global15m_pVideoManagerE_02cbe250 + 8));
          Aska::MappedResourceFilter::SetImageFlags(unsigned short)();
          uVar3 = Aska::Global::InitializeDeleteManager()();
          if ((uVar3 & 1) != 0) {
            uVar3 = Aska::Global::InstantiateMappedMemoryManager()();
            puVar2 = PTR__ZN4Aska6Global20m_pSystemTaskManagerE_02cbf620;
            if ((uVar3 & 1) == 0) {
              return 0;
            }
            if (*(long *)PTR__ZN4Aska6Global20m_pSystemTaskManagerE_02cbf620 != 0) {
              return 0;
            }
            lVar4 = operator new(unsigned long, std::nothrow_t const&)(0xff0,PTR__ZSt7nothrow_02cb9a80);
            if (lVar4 == 0) {
              *(undefined8 *)puVar2 = 0;
              return 0;
            }
            Aska::TaskManager::TaskManager()(lVar4);
            *(long *)puVar2 = lVar4;
            uVar3 = Aska::TaskManager::CreateEndNotifyList(int)(lVar4,8);
            if ((((((uVar3 & 1) != 0) && (uVar3 = Aska::Global::InstantiateHostMachineList()(), (uVar3 & 1) != 0)) &&
                 (uVar3 = Aska::Global::InstantiateGeneralMessageHandler()(), (uVar3 & 1) != 0)) &&
                ((uVar3 = Aska::Global::InitializeSystemCallbackManagerTask()(), (uVar3 & 1) != 0 &&
                 (uVar3 = Aska::Global::InstantiateDecodeTextureManager()(), (uVar3 & 1) != 0)))) &&
               ((uVar3 = Aska::Global::InstantiateDecodeTextureQueue()(), (uVar3 & 1) != 0 &&
                ((uVar3 = Aska::Global::InstantiateTextureManager()(), (uVar3 & 1) != 0 &&
                 (uVar3 = Aska::TaskManager::AddEndNotify(Aska::INotify*, unsigned long)(*(undefined8 *)puVar2,
                                          PTR__ZN4Aska6Global17m_deleteEndNotifyE_02cc1960,0),
                 (uVar3 & 1) != 0)))))) {
              Aska::VideoManager::CallVSyncCallback()();
              uVar3 = Aska::Global::InstantiateRenderStatePool()();
              if (((((((uVar3 & 1) != 0) &&
                     (((uVar3 = Aska::Global::InstantiateRenderStateManager()(), (uVar3 & 1) != 0 &&
                       (uVar3 = Aska::Global::InstantiateFileReadManager()(), (uVar3 & 1) != 0)) &&
                      (uVar3 = Aska::Global::InstantiatePeripheralManager()(), (uVar3 & 1) != 0)))) &&
                    ((((uVar3 = Aska::Global::InstantiateRenderTargetManager()(), (uVar3 & 1) != 0 &&
                       (uVar3 = Aska::Global::InstantiateFrameBuffer()(), (uVar3 & 1) != 0)) &&
                      ((uVar3 = Aska::Global::InstantiateDynamicsManager()(), (uVar3 & 1) != 0 &&
                       ((uVar3 = Aska::Global::InstantiateRigidBodyManager()(), (uVar3 & 1) != 0 &&
                        (uVar3 = Aska::Global::InstantiateCameraManager()(), (uVar3 & 1) != 0)))))) &&
                     (uVar3 = Aska::Global::InstantiateLightManager()(), (uVar3 & 1) != 0)))) &&
                   (((((uVar3 = Aska::Global::InstantiateModifierManager()(), (uVar3 & 1) != 0 &&
                       (uVar3 = Aska::Global::InstantiateMeshGeneratorManager()(), (uVar3 & 1) != 0)) &&
                      (uVar3 = Aska::Global::InstantiateMappingQueue()(), (uVar3 & 1) != 0)) &&
                     ((uVar3 = Aska::Global::InstantiateResourceReadyQueue()(), (uVar3 & 1) != 0 &&
                      (uVar3 = Aska::Global::InstantiateRenderLayerChooser()(), (uVar3 & 1) != 0)))) &&
                    (((uVar3 = Aska::Global::InstantiateVSync()(), (uVar3 & 1) != 0 &&
                      ((uVar3 = Aska::Global::InstantiatePerformanceCounter()(), (uVar3 & 1) != 0 &&
                       (uVar3 = Aska::Global::InstantiateMeshGeometryManager()(), (uVar3 & 1) != 0)))) &&
                     (uVar3 = Aska::Global::InstantiateShaderConstantBufferPool()(), (uVar3 & 1) != 0)))))) &&
                  ((((((uVar3 = Aska::Global::InstantiateSoundManager()(), (uVar3 & 1) != 0 &&
                       (uVar3 = Aska::Global::InstantiateDecompressQueue()(), (uVar3 & 1) != 0)) &&
                      (uVar3 = Aska::Global::InstantiateOpticalPhenomenon()(), (uVar3 & 1) != 0)) &&
                     ((uVar3 = Aska::Global::InstantiateMessageDispatcher()(), (uVar3 & 1) != 0 &&
                      (uVar3 = Aska::FontManagerProxy::Initialize()(), (uVar3 & 1) != 0)))) &&
                    (uVar3 = Aska::Global::InstantiateLIBLManager()(), (uVar3 & 1) != 0)) &&
                   (((uVar3 = Aska::Global::InstantiateObjectManager()(), (uVar3 & 1) != 0 &&
                     (uVar3 = Aska::Global::InstantiateParticleManager()(), (uVar3 & 1) != 0)) &&
                    ((uVar3 = Aska::Global::InstantiateShaderLinkManager()(), (uVar3 & 1) != 0 &&
                     (((uVar3 = Aska::Global::InstantiateProjectorManager()(), (uVar3 & 1) != 0 &&
                       (uVar3 = Aska::Global::InstantiateDynamicsPrimitiveListPool()(), (uVar3 & 1) != 0)) &&
                      (uVar3 = Aska::Global::InstantiateObjectManagerJobDispatcher()(), (uVar3 & 1) != 0)))))))))) &&
                 (((uVar3 = Aska::Global::InstantiateNetworkAllocator()(), (uVar3 & 1) != 0 &&
                   (uVar3 = Aska::Global::InstantiateNetworkManager()(), (uVar3 & 1) != 0)) &&
                  ((uVar3 = Aska::Yayoi::NetworkManager::InitializeThreads()(*(undefined8 *)
                                             PTR__ZN4Aska6Global17m_pNetworkManagerE_02cb9e90),
                   (uVar3 & 1) != 0 &&
                   (((uVar3 = Aska::Global::InstantiateEventPool(int)(0x10), (uVar3 & 1) != 0 &&
                     (uVar3 = Aska::Global::InstantiateLocalKVS()(), (uVar3 & 1) != 0)) &&
                    (uVar3 = Aska::ShaderLinkManager::Init()(*(undefined8 *)
                                              PTR__ZN4Aska6Global20m_pShaderLinkManagerE_02cb93f8),
                    (uVar3 & 1) != 0)))))))) {
                if ((*(long *)PTR__ZN4Aska6Global17m_pTextureManagerE_02cc19f0 != 0) &&
                   (uVar3 = Aska::TextureManager::InitStorage(bool)(0), (uVar3 & 1) == 0)) {
                  return 0;
                }
                return 1;
              }
            }
          }
        }
      }
    }
  }
  return 0;
}

// ==== Aska::Global::InitAll_RootPaths()
// vaddr 0x220fe24 | ghidra 0x230fe24 | size 92 | symbol _ZN4Aska6Global17InitAll_RootPathsEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska6Global17InitAll_RootPathsEv(void)

{
  undefined8 uVar1;
  long lVar2;
  
  lVar2 = *(long *)PTR__ZN4Aska6Global6m_pAppE_02cc2078;
  if (lVar2 != 0) {
    *(undefined8 *)PTR__ZN4Aska6Global20m_pszStorageRootPathE_02cbf040 = *(undefined8 *)(lVar2 + 8);
    *(undefined8 *)PTR__ZN4Aska6Global29m_pszUserGeneratedContentPathE_02cbda18 =
         *(undefined8 *)(lVar2 + 0x10);
    uVar1 = *(undefined8 *)(lVar2 + 0x20);
    *(undefined8 *)PTR__ZN4Aska6Global17m_pszTempFilePathE_02cc4170 = *(undefined8 *)(lVar2 + 0x18);
    *(undefined8 *)PTR__ZN4Aska6Global24m_pszDownloadContentPathE_02cbe1a8 = uVar1;
    return 1;
  }
  return 0;
}

// ==== Aska::Global::InitAll_SeedRandom()
// vaddr 0x220fe80 | ghidra 0x230fe80 | size 152 | symbol _ZN4Aska6Global18InitAll_SeedRandomEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6Global18InitAll_SeedRandomEv(void)

{
  ushort auStack_30 [2];
  undefined4 uStack_2c;
  undefined2 uStack_26;
  uint uStack_24;
  uint auStack_20 [3];
  undefined4 uStack_14;
  
  Aska::GetLocalTime(Aska::ASKATIME*)(auStack_30);
  auStack_20[0] = (uint)auStack_30[0] | uStack_24 / 1000 << 0x10;
  uStack_14 = uStack_2c;
  *(int *)PTR__ZN4Aska26g_uiLowPrecisionRandomSeedE_02cbb068 =
       CONCAT22((undefined2)uStack_2c,uStack_26) * 0x9534c85 + 0x9535932;
  Aska::InitRandom(unsigned int)();
  Aska::InitHighPrecisionRandom(unsigned int*, int)(auStack_20,4);
  return;
}

// ==== Aska::Global::InitAll_SectionAddress()
// vaddr 0x22100e0 | ghidra 0x23100e0 | size 4 | symbol _ZN4Aska6Global22InitAll_SectionAddressEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6Global22InitAll_SectionAddressEv(void)

{
  return;
}

// ==== Aska::Global::GetRemoteHostMachine(char*, unsigned int, unsigned int*, int)
// vaddr 0x22103e8 | ghidra 0x23103e8 | size 180 | symbol _ZN4Aska6Global20GetRemoteHostMachineEPcjPji | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Possible PIC construction at 0x02310444: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0x02310448) */

undefined8
_ZN4Aska6Global20GetRemoteHostMachineEPcjPji
          (undefined8 param_1,undefined4 param_2,undefined8 param_3,undefined4 param_4)

{
  undefined *puVar1;
  undefined8 uVar2;
  long lVar3;
  
  puVar1 = PTR__ZN4Aska6Global18m_pHostMachineListE_02cba4c8;
  lVar3 = *(long *)PTR__ZN4Aska6Global18m_pHostMachineListE_02cba4c8;
  if (lVar3 == 0) {
    return 0xffffffff;
  }
  if (*(long *)PTR__ZN4Aska6Global35m_pCriticalSectionOfHostMachineListE_02cbdc48 != 0) {
    Aska::CriticalSection::Enter() const(*(long *)PTR__ZN4Aska6Global35m_pCriticalSectionOfHostMachineListE_02cbdc48);
    lVar3 = *(long *)puVar1;
  }
  uVar2 = (*(code *)PTR__ZNK4Aska15HostMachineList14GetHostMachineEPcjPji_02c910f8)
                    (lVar3,param_1,param_2,param_3,param_4);
  return uVar2;
}

// ==== Aska::Global::GetNumberOfProcessors()
// vaddr 0x2210dac | ghidra 0x2310dac | size 4 | symbol _ZN4Aska6Global21GetNumberOfProcessorsEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6Global21GetNumberOfProcessorsEv(void)

{
  (*(code *)PTR__ZN4Aska14RenderDeviceGL21GetNumberOfProcessorsEv_02ca34a0)();
  return;
}

// ==== Aska::Global::GetNumberOfHighProcessors()
// vaddr 0x2210db0 | ghidra 0x2310db0 | size 4 | symbol _ZN4Aska6Global25GetNumberOfHighProcessorsEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6Global25GetNumberOfHighProcessorsEv(void)

{
  (*(code *)PTR__ZN4Aska14RenderDeviceGL25GetNumberOfHighProcessorsEv_02cad7e8)();
  return;
}

// ==== Aska::Global::GetNumberOfLowProcessors()
// vaddr 0x2210db4 | ghidra 0x2310db4 | size 4 | symbol _ZN4Aska6Global24GetNumberOfLowProcessorsEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6Global24GetNumberOfLowProcessorsEv(void)

{
  (*(code *)PTR__ZN4Aska14RenderDeviceGL24GetNumberOfLowProcessorsEv_02c953e8)();
  return;
}

// ==== Aska::Global::GetCurrentThreadCpuId()
// vaddr 0x2210db8 | ghidra 0x2310db8 | size 44 | symbol _ZN4Aska6Global21GetCurrentThreadCpuIdEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZN4Aska6Global21GetCurrentThreadCpuIdEv(void)

{
  long lVar1;
  undefined4 uStack_4;
  
  lVar1 = syscall(0xa8,&uStack_4,0,0);
  if (lVar1 < 0) {
    uStack_4 = 0xffffffff;
  }
  return uStack_4;
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

// ==== Aska::Global::GetMainThreadID()
// vaddr 0x2210f74 | ghidra 0x2310f74 | size 32 | symbol _ZN4Aska6Global15GetMainThreadIDEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska6Global15GetMainThreadIDEv(void)

{
  if (*(long *)PTR__ZN4Aska6Global6m_pAppE_02cc2078 != 0) {
    return *(undefined8 *)(*(long *)PTR__ZN4Aska6Global6m_pAppE_02cc2078 + 0x108);
  }
  return 0;
}
