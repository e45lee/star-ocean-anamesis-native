// port/decomp/yayoi/network.c: Ghidra decompiles for the yayoi subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-04 06:29 UTC: tools/decomp.sh '--into' 'yayoi/network' '[ :]Aska::Yayoi::(URI|IPAddress|NetworkManager|NetworkManagerThread|NativeHttpClient|NativeHttpRequestProcessor|NetworkAllocator)::'

// ==== Aska::Yayoi::IPAddress::SetPort(unsigned short)
// vaddr 0x21f587c | ghidra 0x22f587c | size 52 | symbol _ZN4Aska5Yayoi9IPAddress7SetPortEt | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi9IPAddress7SetPortEt(undefined8 *param_1,long param_2,uint param_3)

{
  if ((*(ushort *)(param_2 + 8) | 8) == 10) {
    *(ushort *)(param_2 + 10) = (ushort)(param_3 >> 8) & 0xff | (ushort)((param_3 & 0xff00ff) << 8);
    *param_1 = 0;
    return;
  }
  *param_1 = 0xfffffffffffffc4d;
  return;
}

// ==== Aska::Yayoi::IPAddress::IPAddress()
// vaddr 0x21f58b0 | ghidra 0x22f58b0 | size 8 | symbol _ZN4Aska5Yayoi9IPAddressC2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi9IPAddressC1Ev(undefined4 *param_1)

{
  *param_1 = 0;
  return;
}

// ==== Aska::Yayoi::IPAddress::GetHost(signed char*, unsigned int, int) const
// vaddr 0x21f58b8 | ghidra 0x22f58b8 | size 72 | symbol _ZNK4Aska5Yayoi9IPAddress7GetHostEPaji | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK4Aska5Yayoi9IPAddress7GetHostEPaji
               (undefined8 *param_1,undefined4 *param_2,undefined8 param_3,undefined4 param_4,
               undefined4 param_5)

{
  int iVar1;
  
  iVar1 = getnameinfo(param_2 + 2,*param_2,param_3,param_4,0,0,param_5);
  if (iVar1 != 0) {
    (*(code *)PTR__ZN4Aska6Status17ErrnoToAskaStatusEi_02c91238)(param_1);
    return;
  }
  *param_1 = 0;
  return;
}

// ==== Aska::Yayoi::IPAddress::GetPort() const
// vaddr 0x21f5900 | ghidra 0x22f5900 | size 40 | symbol _ZNK4Aska5Yayoi9IPAddress7GetPortEv | lib libSOA-3.7.0.so | 2026-10-04
ushort _ZNK4Aska5Yayoi9IPAddress7GetPortEv(long param_1)

{
  if ((*(ushort *)(param_1 + 8) | 8) == 10) {
    return *(ushort *)(param_1 + 10) >> 8 | *(ushort *)(param_1 + 10) << 8;
  }
  return 0xfc4d;
}

// ==== Aska::Yayoi::IPAddress::IsTheSame(Aska::Yayoi::IPAddress const&) const
// vaddr 0x21f5928 | ghidra 0x22f5928 | size 32 | symbol _ZNK4Aska5Yayoi9IPAddress9IsTheSameERKS1_ | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK4Aska5Yayoi9IPAddress9IsTheSameERKS1_(undefined4 *param_1,long param_2)

{
  int iVar1;
  
  iVar1 = memcmp(param_1 + 2,param_2 + 8,*param_1);
  return iVar1 == 0;
}

// ==== Aska::Yayoi::IPAddress::GetAddress(sockaddr const**, unsigned int*) const
// vaddr 0x21f5948 | ghidra 0x22f5948 | size 24 | symbol _ZNK4Aska5Yayoi9IPAddress10GetAddressEPPK8sockaddrPj | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK4Aska5Yayoi9IPAddress10GetAddressEPPK8sockaddrPj
               (undefined8 *param_1,undefined4 *param_2,long *param_3,undefined4 *param_4)

{
  *param_3 = (long)(param_2 + 2);
  *param_4 = *param_2;
  *param_1 = 0;
  return;
}

// ==== Aska::Yayoi::IPAddress::InitAsServer(unsigned short, Aska::Yayoi::AddressFamily)
// vaddr 0x21f5960 | ghidra 0x22f5960 | size 196 | symbol _ZN4Aska5Yayoi9IPAddress12InitAsServerEtNS0_13AddressFamilyE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi9IPAddress12InitAsServerEtNS0_13AddressFamilyE
               (undefined8 *param_1,undefined4 *param_2,undefined2 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  long lVar2;
  int iVar3;
  undefined4 uStack_68;
  undefined2 uStack_64;
  undefined4 uStack_60;
  undefined4 uStack_5c;
  undefined8 uStack_58;
  undefined8 uStack_50;
  undefined8 uStack_48;
  undefined8 uStack_40;
  undefined8 uStack_38;
  long lStack_28;
  
  lStack_28 = 0;
  uStack_60 = 9;
  uStack_38 = 0;
  uStack_64 = 0;
  uStack_68 = 0;
  uStack_40 = 0;
  uStack_48 = 0;
  uStack_50 = 0;
  uStack_58 = 0;
  uStack_5c = param_4;
  iVar3 = __aska_snprintf_s(char*, unsigned long, unsigned long, char const*, ...)(&uStack_68,6,0xffffffffffffffff,&UNK_02a3d191/*"%d"*/,param_3);
  if (iVar3 < 0) {
    Aska::Status::ErrnoToAskaStatus(int)(param_1);
  }
  else {
    iVar3 = getaddrinfo(0,&uStack_68,&uStack_60,&lStack_28);
    lVar2 = lStack_28;
    if (iVar3 == 0) {
      uVar1 = *(undefined4 *)(lStack_28 + 0x10);
      memcpy(param_2 + 2,*(undefined8 *)(lStack_28 + 0x20),uVar1);
      *param_2 = uVar1;
      freeaddrinfo(lVar2);
      *param_1 = 0;
    }
    else {
      *param_1 = 0xffffffffffffffff;
    }
  }
  return;
}

// ==== Aska::Yayoi::IPAddress::Set(sockaddr const&, unsigned int)
// vaddr 0x21f5a24 | ghidra 0x22f5a24 | size 44 | symbol _ZN4Aska5Yayoi9IPAddress3SetERK8sockaddrj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi9IPAddress3SetERK8sockaddrj
               (undefined4 *param_1,undefined8 param_2,undefined4 param_3)

{
  memcpy(param_1 + 2,param_2,param_3);
  *param_1 = param_3;
  return;
}

// ==== Aska::Yayoi::IPAddress::Copy(Aska::Yayoi::IPAddress const&)
// vaddr 0x21f5a50 | ghidra 0x22f5a50 | size 8 | symbol _ZN4Aska5Yayoi9IPAddress4CopyERKS1_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi9IPAddress4CopyERKS1_(undefined8 param_1,undefined8 param_2)

{
  (*(code *)PTR_memcpy_02cae5d8)(param_1,param_2,0x88);
  return;
}

// ==== Aska::Yayoi::IPAddress::Create(char const*, Aska::Yayoi::SocketType, unsigned short, Aska::Yayoi::AddressFamily, Aska::Yayoi::IPAddress*)
// vaddr 0x21f5a58 | ghidra 0x22f5a58 | size 112 | symbol _ZN4Aska5Yayoi9IPAddress6CreateEPKcNS0_10SocketTypeEtNS0_13AddressFamilyEPS1_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi9IPAddress6CreateEPKcNS0_10SocketTypeEtNS0_13AddressFamilyEPS1_
               (long *param_1,undefined8 param_2,undefined4 param_3,uint param_4,undefined8 param_5,
               long param_6)

{
  long lStack_28;
  
  Aska::Yayoi::Socket::ConvertIPAddrNtoB(char const*, unsigned short, Aska::Yayoi::SocketType, Aska::Yayoi::AddressFamily, Aska::Yayoi::IPAddress*)(&lStack_28,param_2,param_4,param_3);
  if (-1 < lStack_28) {
    if ((*(ushort *)(param_6 + 8) | 8) == 10) {
      lStack_28 = 0;
      *(ushort *)(param_6 + 10) =
           (ushort)(param_4 >> 8) & 0xff | (ushort)((param_4 & 0xff00ff) << 8);
    }
    else {
      lStack_28 = -0x3b3;
    }
  }
  *param_1 = lStack_28;
  return;
}

// ==== Aska::Yayoi::IPAddress::Set(__kernel_sockaddr_storage const&, unsigned int)
// vaddr 0x21f5ac8 | ghidra 0x22f5ac8 | size 44 | symbol _ZN4Aska5Yayoi9IPAddress3SetERK25__kernel_sockaddr_storagej | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi9IPAddress3SetERK25__kernel_sockaddr_storagej
               (undefined4 *param_1,undefined8 param_2,undefined4 param_3)

{
  memcpy(param_1 + 2,param_2,0x80);
  *param_1 = param_3;
  return;
}

// ==== Aska::Yayoi::IPAddress::Clear()
// vaddr 0x21f5af4 | ghidra 0x22f5af4 | size 12 | symbol _ZN4Aska5Yayoi9IPAddress5ClearEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi9IPAddress5ClearEv(undefined8 param_1)

{
  (*(code *)PTR_memset_02c9b870)(param_1,0,0x88);
  return;
}

// ==== Aska::Yayoi::NetworkAllocator::Delete()
// vaddr 0x21fd350 | ghidra 0x22fd350 | size 52 | symbol _ZN4Aska5Yayoi16NetworkAllocator6DeleteEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi16NetworkAllocator6DeleteEv(long *param_1)

{
  if ((char)param_1[1] != '\0') {
    if ((long *)*param_1 != (long *)0x0) {
      (**(code **)(*(long *)*param_1 + 0xd0))();
      *param_1 = 0;
    }
    *(undefined1 *)(param_1 + 1) = 0;
  }
  return;
}

// ==== Aska::Yayoi::NetworkAllocator::Set(Aska::MemoryManager*, bool)
// vaddr 0x21fd384 | ghidra 0x22fd384 | size 16 | symbol _ZN4Aska5Yayoi16NetworkAllocator3SetEPNS_13MemoryManagerEb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi16NetworkAllocator3SetEPNS_13MemoryManagerEb
               (undefined8 *param_1,undefined8 param_2,byte param_3)

{
  *param_1 = param_2;
  *(byte *)(param_1 + 1) = param_3 & 1;
  return;
}

// ==== Aska::Yayoi::NetworkManagerThread::NetworkManagerThread()
// vaddr 0x2203aa0 | ghidra 0x2303aa0 | size 60 | symbol _ZN4Aska5Yayoi20NetworkManagerThreadC2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi20NetworkManagerThreadC1Ev(long *param_1)

{
  undefined *puVar1;
  
  Aska::Thread::Thread()();
  puVar1 = PTR__ZTVN4Aska5Yayoi20NetworkManagerThreadE_02cc0b38;
  param_1[4] = 0;
  param_1[5] = 0;
  *param_1 = (long)(puVar1 + 0x10);
  param_1[3] = (long)(puVar1 + 0x48);
  Aska::Semaphore::Semaphore()(param_1 + 7);
  *(undefined1 *)(param_1 + 10) = 0;
  return;
}

// ==== Aska::Yayoi::NetworkManagerThread::~NetworkManagerThread()
// vaddr 0x2203adc | ghidra 0x2303adc | size 168 | symbol _ZN4Aska5Yayoi20NetworkManagerThreadD1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi20NetworkManagerThreadD2Ev(long *param_1)

{
  undefined *puVar1;
  long *plVar2;
  long lVar3;
  
  puVar1 = PTR__ZTVN4Aska5Yayoi20NetworkManagerThreadE_02cc0b38 + 0x48;
  *param_1 = (long)(PTR__ZTVN4Aska5Yayoi20NetworkManagerThreadE_02cc0b38 + 0x10);
  param_1[3] = (long)puVar1;
  Aska::Semaphore::Exit()(param_1 + 7);
  if (param_1[5] != 0) {
    Aska::Yayoi::NetworkEvent::Clear()();
    lVar3 = param_1[5];
    if (lVar3 != 0) {
      Aska::Yayoi::NetworkEvent::~NetworkEvent()(lVar3);
      operator delete(void*)(lVar3);
      param_1[5] = 0;
    }
  }
  if (param_1[4] != 0) {
    plVar2 = (long *)(param_1[4] + 0x28);
    (**(code **)(*plVar2 + 0x38))(plVar2,0);
    param_1[4] = 0;
  }
  lVar3 = param_1[6];
  if (lVar3 != 0) {
    Aska::Yayoi::NativeHttpRequestProcessor::~NativeHttpRequestProcessor()(lVar3);
    operator delete(void*)(lVar3);
    param_1[6] = 0;
  }
  Aska::Semaphore::~Semaphore()(param_1 + 7);
  (*(code *)PTR__ZN4Aska6ThreadD1Ev_02c9be08)(param_1);
  return;
}

// ==== non-virtual thunk to Aska::Yayoi::NetworkManagerThread::~NetworkManagerThread()
// vaddr 0x2203b84 | ghidra 0x2303b84 | size 8 | symbol _ZThn24_N4Aska5Yayoi20NetworkManagerThreadD1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZThn24_N4Aska5Yayoi20NetworkManagerThreadD1Ev(long param_1)

{
  (*(code *)PTR__ZN4Aska5Yayoi20NetworkManagerThreadD2Ev_02cb06f8)(param_1 + -0x18);
  return;
}

// ==== Aska::Yayoi::NetworkManagerThread::~NetworkManagerThread()
// vaddr 0x2203b8c | ghidra 0x2303b8c | size 24 | symbol _ZN4Aska5Yayoi20NetworkManagerThreadD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi20NetworkManagerThreadD0Ev(undefined8 param_1)

{
  Aska::Yayoi::NetworkManagerThread::~NetworkManagerThread()();
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== non-virtual thunk to Aska::Yayoi::NetworkManagerThread::~NetworkManagerThread()
// vaddr 0x2203ba4 | ghidra 0x2303ba4 | size 28 | symbol _ZThn24_N4Aska5Yayoi20NetworkManagerThreadD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZThn24_N4Aska5Yayoi20NetworkManagerThreadD0Ev(long param_1)

{
  Aska::Yayoi::NetworkManagerThread::~NetworkManagerThread()(param_1 + -0x18);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1 + -0x18);
  return;
}

// ==== Aska::Yayoi::NetworkManagerThread::Kill()
// vaddr 0x2203bc0 | ghidra 0x2303bc0 | size 64 | symbol _ZN4Aska5Yayoi20NetworkManagerThread4KillEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi20NetworkManagerThread4KillEv(long param_1)

{
  *(undefined1 *)(param_1 + 0x50) = 1;
  if (*(long *)(param_1 + 0x28) != 0) {
    Aska::Yayoi::NetworkEvent::Terminate()();
  }
  if (*(long *)(param_1 + 0x30) != 0) {
    *(undefined1 *)(*(long *)(param_1 + 0x30) + 0x8c8) = 1;
  }
  Aska::Semaphore::Signal() const(param_1 + 0x38);
  (*(code *)PTR__ZN4Aska6Thread7WaitEndEv_02c98108)(param_1);
  return;
}

// ==== Aska::Yayoi::NetworkManagerThread::Handler()
// vaddr 0x2203c00 | ghidra 0x2303c00 | size 152 | symbol _ZN4Aska5Yayoi20NetworkManagerThread7HandlerEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi20NetworkManagerThread7HandlerEv(long param_1)

{
  undefined1 auStack_38 [12];
  char acStack_2c [4];
  undefined1 auStack_28 [8];
  undefined1 auStack_18 [8];
  
  while (Aska::Semaphore::Wait() const(param_1 + 0x38), *(char *)(param_1 + 0x50) == '\0') {
    if (*(long *)(param_1 + 0x20) != 0) {
      (**(code **)(**(long **)(*(long *)(param_1 + 0x20) + 0x108) + 0x70))();
    }
    Aska::Yayoi::NetworkEvent::Run()(auStack_28,*(undefined8 *)(param_1 + 0x28));
    acStack_2c[0] = '\0';
    Aska::Yayoi::NativeHttpRequestProcessor::FlushRequests(bool*)(auStack_38,*(undefined8 *)(param_1 + 0x30),acStack_2c);
    if (acStack_2c[0] != '\0') {
      Aska::Semaphore::Signal() const(param_1 + 0x38);
    }
  }
  Aska::Yayoi::NetworkEvent::Run()(auStack_18,*(undefined8 *)(param_1 + 0x28));
  Aska::Thread::Delete()(param_1);
  return;
}

// ==== Aska::Yayoi::NetworkManagerThread::Init()
// vaddr 0x2203c98 | ghidra 0x2303c98 | size 556 | symbol _ZN4Aska5Yayoi20NetworkManagerThread4InitEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska5Yayoi20NetworkManagerThread4InitEv(long param_1)

{
  undefined *puVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  ulong uVar8;
  long lVar9;
  undefined8 uVar10;
  long lStack_58;
  undefined1 auStack_48 [8];
  
  uVar8 = Aska::Semaphore::Create(int, int)(param_1 + 0x38,0,0x1000);
  if ((uVar8 & 1) == 0) {
    return 0;
  }
  lVar9 = operator new(unsigned long, std::nothrow_t const&)(0xff0,PTR__ZSt7nothrow_02cb9a80);
  if (lVar9 == 0) {
    *(undefined8 *)(param_1 + 0x20) = 0;
    return 0;
  }
  Aska::TaskManager::TaskManager()(lVar9);
  *(long *)(param_1 + 0x20) = lVar9;
  Aska::AppNetworkCommonSettingProxy::AppNetworkCommonSettingProxy()(auStack_48);
  uVar2 = Aska::AppNetworkCommonSettingProxy::GetAcceptJobQueueSize() const(auStack_48);
  uVar3 = Aska::AppNetworkCommonSettingProxy::GetRecvJobQueueSize() const(auStack_48);
  uVar4 = Aska::AppNetworkCommonSettingProxy::GetRecvfromJobQueueSize() const(auStack_48);
  uVar5 = Aska::AppNetworkCommonSettingProxy::GetSendJobQueueSize() const(auStack_48);
  uVar6 = Aska::AppNetworkCommonSettingProxy::GetConnectJobQueueSize() const(auStack_48);
  uVar7 = Aska::AppNetworkCommonSettingProxy::GetPollJobQueueSize() const(auStack_48);
  uVar8 = Aska::Thread::Create(bool, int, int, bool)(param_1,0,0x80,0x80000,0);
  uVar10 = 0;
  if ((uVar8 & 1) == 0) goto code_r0x02303e70;
  lVar9 = operator new(unsigned long, std::nothrow_t const&)(0x670,PTR__ZSt7nothrow_02cb9a80);
  if (lVar9 == 0) {
    *(undefined8 *)(param_1 + 0x28) = 0;
    uVar10 = 0;
    goto code_r0x02303e70;
  }
  Aska::Yayoi::NetworkEvent::NetworkEvent()(lVar9);
  *(long *)(param_1 + 0x28) = lVar9;
  Aska::Yayoi::NetworkEvent::Initialize(unsigned short, unsigned short, unsigned short, unsigned short, unsigned short, unsigned short)(&lStack_58,lVar9,uVar2,uVar3,uVar4,uVar5,uVar6,uVar7);
  puVar1 = PTR__ZN4Aska6Global17m_pNetworkManagerE_02cb9e90;
  if (-1 < lStack_58) {
    *(long *)(*(long *)(param_1 + 0x28) + 0x540) = param_1 + 0x18;
    uVar8 = Aska::Yayoi::NetworkManager::RegisterNetworkEvent(long, Aska::Yayoi::NetworkEvent*)(*(undefined8 *)puVar1,*(undefined8 *)(param_1 + 8),
                            *(undefined8 *)(param_1 + 0x28));
    if ((uVar8 & 1) == 0) {
      lVar9 = *(long *)(param_1 + 0x28);
      if (lVar9 != 0) {
        Aska::Yayoi::NetworkEvent::~NetworkEvent()(lVar9);
code_r0x02303e68:
        operator delete(void*)(lVar9);
      }
    }
    else {
      lVar9 = operator new(unsigned long, std::nothrow_t const&)(0x8d0,PTR__ZSt7nothrow_02cb9a80);
      if (lVar9 == 0) {
        lVar9 = *(long *)(param_1 + 0x28);
        *(undefined8 *)(param_1 + 0x30) = 0;
        if (lVar9 != 0) {
          Aska::Yayoi::NetworkEvent::~NetworkEvent()(lVar9);
          goto code_r0x02303e68;
        }
      }
      else {
        Aska::Yayoi::NativeHttpRequestProcessor::NativeHttpRequestProcessor()(lVar9);
        *(long *)(param_1 + 0x30) = lVar9;
        Aska::Yayoi::NativeHttpRequestProcessor::Initialize()(&lStack_58,lVar9);
        if (-1 < lStack_58) {
          uVar10 = 1;
          *(undefined8 *)(*(long *)puVar1 + 0xd8) = *(undefined8 *)(param_1 + 0x30);
          goto code_r0x02303e70;
        }
        lVar9 = *(long *)(param_1 + 0x28);
        if (lVar9 != 0) {
          Aska::Yayoi::NetworkEvent::~NetworkEvent()(lVar9);
          operator delete(void*)(lVar9);
        }
        lVar9 = *(long *)(param_1 + 0x30);
        if (lVar9 != 0) {
          Aska::Yayoi::NativeHttpRequestProcessor::~NativeHttpRequestProcessor()(lVar9);
          goto code_r0x02303e68;
        }
      }
    }
  }
  uVar10 = 0;
code_r0x02303e70:
  Aska::AppNetworkCommonSettingProxy::~AppNetworkCommonSettingProxy()(auStack_48);
  return uVar10;
}

// ==== Aska::Yayoi::NetworkManager::RegisterNetworkEvent(long, Aska::Yayoi::NetworkEvent*)
// vaddr 0x2203ec4 | ghidra 0x2303ec4 | size 648 | symbol _ZN4Aska5Yayoi14NetworkManager20RegisterNetworkEventElPNS0_12NetworkEventE | lib libSOA-3.7.0.so | 2026-10-04
bool _ZN4Aska5Yayoi14NetworkManager20RegisterNetworkEventElPNS0_12NetworkEventE
               (long param_1,ulong param_2,undefined8 param_3)

{
  int *piVar1;
  int *piVar2;
  ulong uVar3;
  char cVar4;
  bool bVar5;
  ulong uVar6;
  undefined8 *puVar7;
  int iVar8;
  ulong uVar9;
  char *pcVar10;
  ulong uVar11;
  ulong uVar12;
  long lVar13;
  char *pcVar14;
  long lVar15;
  ulong uStack_38;
  
  uVar9 = *(ulong *)(param_1 + 0x28);
  if (uVar9 != 0) {
    uVar11 = ~param_2 + param_2 * 0x200000;
    uVar11 = (uVar11 ^ uVar11 >> 0x18) * 0x109;
    uVar12 = (uVar11 ^ uVar11 >> 0xe) * 0x15;
    uVar11 = 0;
    do {
      uVar3 = (uVar12 ^ uVar12 >> 0x1c) * 0x80000001 + uVar11;
      uVar6 = 0;
      if (uVar9 != 0) {
        uVar6 = uVar3 / uVar9;
      }
      lVar13 = uVar3 - uVar6 * uVar9;
      cVar4 = *(char *)(*(long *)(param_1 + 0x20) + lVar13 * 0x18);
      if (cVar4 == '\x01') {
        if (*(ulong *)(*(long *)(param_1 + 0x20) + lVar13 * 0x18 + 8) == param_2) {
          return false;
        }
      }
      else if (cVar4 == '\0') break;
      uVar11 = uVar11 + 1;
    } while (uVar11 < uVar9);
  }
  piVar1 = (int *)(param_1 + 0x68);
  iVar8 = 0;
code_r0x02303f68:
  do {
    uStack_38 = param_2;
    if (*piVar1 == -1) goto code_r0x02303f74;
    ClearExclusiveLocal();
    bVar5 = iVar8 < 0x1ff;
    iVar8 = iVar8 + 1;
  } while (bVar5);
  piVar2 = (int *)(param_1 + 0x6c);
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
        uVar9 = Aska::Semaphore::IsReady() const(param_1 + 0xa8);
        if ((uVar9 & 1) == 0) {
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
          Aska::Semaphore::Wait() const(param_1 + 0xa8);
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
          if (cVar4 == '\0') goto code_r0x02304134;
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
code_r0x02304134:
  do {
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar5) {
      *piVar2 = *piVar2 + -1;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
  DataMemoryBarrier(2,3);
  goto code_r0x02303fc4;
code_r0x02303f74:
  cVar4 = '\x01';
  bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
  if (bVar5) {
    *piVar1 = 0;
    cVar4 = ExclusiveMonitorsStatus();
  }
  if (cVar4 == '\0') goto code_r0x02303fbc;
  goto code_r0x02303f68;
code_r0x02303fbc:
  DataMemoryBarrier(2,3);
code_r0x02303fc4:
  puVar7 = (undefined8 *)Aska::THashMap<long, Aska::Yayoi::NetworkEvent*, Aska::THasher<long>, Aska::TEqualTo<long>, Aska::TAllocator<Aska::TPair<long const, Aska::Yayoi::NetworkEvent*> > >::operator[](long const&)(param_1,&uStack_38);
  *puVar7 = param_3;
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_1 + 0x68) = 0xffffffff;
  DataMemoryBarrier(2,3);
  piVar1 = (int *)(param_1 + 0x6c);
  if (0x14 < *piVar1) {
    do {
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar5) {
        *piVar1 = *piVar1 + -1;
        cVar4 = ExclusiveMonitorsStatus();
      }
    } while (cVar4 != '\0');
    uVar9 = Aska::Semaphore::IsReady() const(param_1 + 0xa8);
    if ((uVar9 & 1) != 0) {
      Aska::Semaphore::Signal() const(param_1 + 0xa8);
    }
  }
  lVar13 = *(long *)(param_1 + 0x20);
  uVar9 = *(ulong *)(param_1 + 0x28);
  if (uVar9 != 0) {
    uVar11 = 0;
    uVar12 = ~uStack_38 + uStack_38 * 0x200000;
    uVar12 = (uVar12 ^ uVar12 >> 0x18) * 0x109;
    uVar12 = (uVar12 ^ uVar12 >> 0xe) * 0x15;
    do {
      uVar3 = (uVar12 ^ uVar12 >> 0x1c) * 0x80000001 + uVar11;
      uVar6 = 0;
      if (uVar9 != 0) {
        uVar6 = uVar3 / uVar9;
      }
      lVar15 = uVar3 - uVar6 * uVar9;
      pcVar14 = (char *)(lVar13 + lVar15 * 0x18);
      if (*pcVar14 == '\x01') {
        if (*(ulong *)(lVar13 + lVar15 * 0x18 + 8) == uStack_38) {
          pcVar10 = (char *)(lVar13 + uVar9 * 0x18);
          goto code_r0x023040a0;
        }
      }
      else if (*pcVar14 == '\0') break;
      uVar11 = uVar11 + 1;
    } while (uVar11 < uVar9);
  }
  pcVar10 = (char *)(lVar13 + uVar9 * 0x18);
  pcVar14 = pcVar10;
code_r0x023040a0:
  return pcVar14 != pcVar10;
}

// ==== Aska::Yayoi::NetworkManager::RegisterHttpRequestProcessor(Aska::Yayoi::NativeHttpRequestProcessor*)
// vaddr 0x220414c | ghidra 0x230414c | size 16 | symbol _ZN4Aska5Yayoi14NetworkManager28RegisterHttpRequestProcessorEPNS0_26NativeHttpRequestProcessorE | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska5Yayoi14NetworkManager28RegisterHttpRequestProcessorEPNS0_26NativeHttpRequestProcessorE
          (long param_1,undefined8 param_2)

{
  *(undefined8 *)(param_1 + 0xd8) = param_2;
  return 1;
}

// ==== Aska::Yayoi::NetworkManager::NetworkManager()
// vaddr 0x220415c | ghidra 0x230415c | size 228 | symbol _ZN4Aska5Yayoi14NetworkManagerC1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi14NetworkManagerC2Ev(long *param_1)

{
  undefined *puVar1;
  ulong uVar2;
  long lVar3;
  undefined1 *puVar4;
  undefined1 *puVar5;
  ulong uVar7;
  ulong uVar8;
  undefined1 *puVar6;
  
  puVar1 = PTR__ZTVN4Aska8THashMapIlPNS_5Yayoi12NetworkEventENS_7THasherIlEENS_8TEqualToIlEENS_10TAllocatorINS_5TPairIKlS3_EEEEEE_02cbacb8
           + 0x10;
  *(undefined8 *)((long)param_1 + 0xc) = 0x3f400000;
  *param_1 = (long)puVar1;
  *(undefined4 *)((long)param_1 + 0x14) = 0;
  puVar4 = (undefined1 *)Aska::MemoryManagerAdapter::AlignedMalloc(unsigned long, unsigned long)(0x198,8);
  lVar3 = 0x11;
  if (puVar4 == (undefined1 *)0x0) {
    lVar3 = 0;
  }
  param_1[4] = (long)puVar4;
  param_1[5] = lVar3;
  if (puVar4 != (undefined1 *)0x0) {
    uVar2 = (lVar3 * 0x18 - 0x18U) / 0x18 + 1;
    puVar6 = puVar4;
    if ((1 < uVar2) && (uVar7 = uVar2 & 0x1ffffffffffffffe, uVar7 != 0)) {
      uVar8 = uVar7;
      do {
        *puVar6 = 0;
        puVar6[0x18] = 0;
        uVar8 = uVar8 - 2;
        puVar6 = puVar6 + 0x30;
      } while (uVar8 != 0);
      puVar6 = puVar4 + uVar7 * 0x18;
      if (uVar2 == uVar7) goto code_r0x0230421c;
    }
    do {
      puVar5 = puVar6 + 0x18;
      *puVar6 = 0;
      puVar6 = puVar5;
    } while (puVar4 + lVar3 * 0x18 != puVar5);
  }
code_r0x0230421c:
  Aska::FastCriticalSection::FastCriticalSection()(param_1 + 6);
  param_1[0x18] = 0;
  param_1[0x1a] = 0;
  Aska::Yayoi::DNSCache::DNSCache()(param_1 + 0x1c);
  param_1[0x34] = 0;
  param_1[0x35] = 0;
  return;
}

// ==== Aska::Yayoi::NetworkManager::~NetworkManager()
// vaddr 0x2204240 | ghidra 0x2304240 | size 240 | symbol _ZN4Aska5Yayoi14NetworkManagerD2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi14NetworkManagerD1Ev(long *param_1)

{
  long lVar1;
  
  lVar1 = param_1[0x34];
  if (lVar1 != 0) {
    Aska::Yayoi::CookieManager::~CookieManager()(lVar1);
    operator delete(void*)(lVar1);
    param_1[0x34] = 0;
  }
  if ((long *)param_1[0x1a] != (long *)0x0) {
    (**(code **)(*(long *)param_1[0x1a] + 8))();
    param_1[0x1a] = 0;
  }
  if ((long *)param_1[0x35] != (long *)0x0) {
    (**(code **)(*(long *)param_1[0x35] + 8))();
    param_1[0x35] = 0;
  }
  lVar1 = param_1[0x18];
  if (lVar1 != 0) {
    *(undefined1 *)(lVar1 + 0x50) = 1;
    if (*(long *)(lVar1 + 0x28) != 0) {
      Aska::Yayoi::NetworkEvent::Terminate()();
    }
    if (*(long *)(lVar1 + 0x30) != 0) {
      *(undefined1 *)(*(long *)(lVar1 + 0x30) + 0x8c8) = 1;
    }
    Aska::Semaphore::Signal() const(lVar1 + 0x38);
    Aska::Thread::WaitEnd()(lVar1);
    if ((long *)param_1[0x18] != (long *)0x0) {
      (**(code **)(*(long *)param_1[0x18] + 8))();
      param_1[0x18] = 0;
    }
  }
  Aska::Yayoi::DNSCache::~DNSCache()(param_1 + 0x1c);
  Aska::FastCriticalSection::~FastCriticalSection()(param_1 + 6);
  *param_1 = (long)(
                   PTR__ZTVN4Aska8THashMapIlPNS_5Yayoi12NetworkEventENS_7THasherIlEENS_8TEqualToIlEENS_10TAllocatorINS_5TPairIKlS3_EEEEEE_02cbacb8
                   + 0x10);
  if (param_1[4] != 0) {
    Aska::MemoryManagerAdapter::AlignedFree(void*)();
    param_1[4] = 0;
    param_1[5] = 0;
  }
  param_1[2] = 0;
  return;
}

// ==== Aska::Yayoi::NetworkManager::Kill()
// vaddr 0x2204330 | ghidra 0x2304330 | size 76 | symbol _ZN4Aska5Yayoi14NetworkManager4KillEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi14NetworkManager4KillEv(long param_1)

{
  long lVar1;
  
  lVar1 = *(long *)(param_1 + 0xc0);
  if (lVar1 != 0) {
    *(undefined1 *)(lVar1 + 0x50) = 1;
    if (*(long *)(lVar1 + 0x28) != 0) {
      Aska::Yayoi::NetworkEvent::Terminate()();
    }
    if (*(long *)(lVar1 + 0x30) != 0) {
      *(undefined1 *)(*(long *)(lVar1 + 0x30) + 0x8c8) = 1;
    }
    Aska::Semaphore::Signal() const(lVar1 + 0x38);
    (*(code *)PTR__ZN4Aska6Thread7WaitEndEv_02c98108)(lVar1);
    return;
  }
  return;
}

// ==== Aska::Yayoi::NetworkManager::InitializeThreads()
// vaddr 0x22043bc | ghidra 0x23043bc | size 296 | symbol _ZN4Aska5Yayoi14NetworkManager17InitializeThreadsEv | lib libSOA-3.7.0.so | 2026-10-04
bool _ZN4Aska5Yayoi14NetworkManager17InitializeThreadsEv(long param_1)

{
  undefined *puVar1;
  undefined2 uVar2;
  undefined2 uVar3;
  long *plVar4;
  ulong uVar5;
  long lVar6;
  long lStack_28;
  undefined1 auStack_18 [8];
  
  plVar4 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x58,PTR__ZSt7nothrow_02cb9a80);
  if (plVar4 == (long *)0x0) {
    *(undefined8 *)(param_1 + 0xc0) = 0;
  }
  else {
    Aska::Thread::Thread()(plVar4);
    puVar1 = PTR__ZTVN4Aska5Yayoi20NetworkManagerThreadE_02cc0b38;
    plVar4[4] = 0;
    plVar4[5] = 0;
    *plVar4 = (long)(puVar1 + 0x10);
    plVar4[3] = (long)(puVar1 + 0x48);
    Aska::Semaphore::Semaphore()(plVar4 + 7);
    *(undefined1 *)(plVar4 + 10) = 0;
    *(long **)(param_1 + 0xc0) = plVar4;
    uVar5 = Aska::Yayoi::NetworkManagerThread::Init()(plVar4);
    if ((uVar5 & 1) != 0) {
      *(undefined8 *)(param_1 + 200) = *(undefined8 *)(*(long *)(param_1 + 0xc0) + 8);
      lVar6 = operator new(unsigned long, std::nothrow_t const&)(0x680,PTR__ZSt7nothrow_02cb9a80);
      if (lVar6 != 0) {
        Aska::Yayoi::Downloader::Downloader()(lVar6);
        *(long *)(param_1 + 0x1a8) = lVar6;
        Aska::AppNetworkCommonSettingProxy::AppNetworkCommonSettingProxy()(auStack_18);
        uVar2 = Aska::AppNetworkCommonSettingProxy::GetParallelDownloadNum() const(auStack_18);
        uVar3 = Aska::AppNetworkCommonSettingProxy::GetDownloadQueueSize() const(auStack_18);
        Aska::Yayoi::Downloader::Init(int, int)(&lStack_28,*(undefined8 *)(param_1 + 0x1a8),uVar2,uVar3);
        if (-1 < lStack_28) {
          Aska::Yayoi::Downloader::SetPath(char const*)(*(undefined8 *)(param_1 + 0x1a8),
                          *(undefined8 *)PTR__ZN4Aska6Global24m_pszDownloadContentPathE_02cbe1a8);
        }
        Aska::AppNetworkCommonSettingProxy::~AppNetworkCommonSettingProxy()(auStack_18);
        return -1 < lStack_28;
      }
      *(undefined8 *)(param_1 + 0x1a8) = 0;
    }
  }
  return false;
}

// ==== Aska::Yayoi::NetworkManager::Initialize()
// vaddr 0x22044e4 | ghidra 0x23044e4 | size 112 | symbol _ZN4Aska5Yayoi14NetworkManager10InitializeEv | lib libSOA-3.7.0.so | 2026-10-04
bool _ZN4Aska5Yayoi14NetworkManager10InitializeEv(long param_1)

{
  bool bVar1;
  long lVar2;
  
  lVar2 = operator new(unsigned long, std::nothrow_t const&)(0x6e0,PTR__ZSt7nothrow_02cb9a80);
  if (lVar2 == 0) {
    *(undefined8 *)(param_1 + 0x1a0) = 0;
    bVar1 = false;
  }
  else {
    Aska::Yayoi::CookieManager::CookieManager()(lVar2);
    *(long *)(param_1 + 0x1a0) = lVar2;
    lVar2 = operator new(unsigned long, std::nothrow_t const&)(0x30,PTR__ZSt7nothrow_02cb9a80);
    if (lVar2 != 0) {
      Aska::Yayoi::PaymentClient::PaymentClient()(lVar2);
    }
    bVar1 = lVar2 != 0;
    *(long *)(param_1 + 0xd0) = lVar2;
  }
  return bVar1;
}

// ==== Aska::Yayoi::NetworkManager::GetNetworkEvent(long)
// vaddr 0x2204694 | ghidra 0x2304694 | size 40 | symbol _ZN4Aska5Yayoi14NetworkManager15GetNetworkEventEl | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska5Yayoi14NetworkManager15GetNetworkEventEl(long param_1,long param_2)

{
  undefined8 *puVar1;
  long lStack_8;
  
  lStack_8 = param_2;
  if (param_2 == 0) {
    lStack_8 = *(long *)(param_1 + 200);
  }
  puVar1 = (undefined8 *)Aska::THashMap<long, Aska::Yayoi::NetworkEvent*, Aska::THasher<long>, Aska::TEqualTo<long>, Aska::TAllocator<Aska::TPair<long const, Aska::Yayoi::NetworkEvent*> > >::operator[](long const&)(param_1,&lStack_8);
  return *puVar1;
}

// ==== Aska::Yayoi::NetworkManager::BeginPoll(Aska::Yayoi::TransportProtocolBase*, Aska::Yayoi::ISocketNotify*, Aska::Yayoi::SelectMode, unsigned short, long, long)
// vaddr 0x22046bc | ghidra 0x23046bc | size 132 | symbol _ZN4Aska5Yayoi14NetworkManager9BeginPollEPNS0_21TransportProtocolBaseEPNS0_13ISocketNotifyENS0_10SelectModeEtll | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi14NetworkManager9BeginPollEPNS0_21TransportProtocolBaseEPNS0_13ISocketNotifyENS0_10SelectModeEtll
               (undefined8 *param_1,long param_2,undefined8 param_3,undefined8 param_4,
               undefined4 param_5,undefined4 param_6,undefined8 param_7,long param_8)

{
  long *plVar1;
  long lStack_38;
  
  lStack_38 = param_8;
  if (param_8 == 0) {
    lStack_38 = *(long *)(param_2 + 200);
  }
  plVar1 = (long *)Aska::THashMap<long, Aska::Yayoi::NetworkEvent*, Aska::THasher<long>, Aska::TEqualTo<long>, Aska::TAllocator<Aska::TPair<long const, Aska::Yayoi::NetworkEvent*> > >::operator[](long const&)(param_2,&lStack_38);
  if (*plVar1 == 0) {
    *param_1 = 0xfffffffffffffc38;
  }
  else {
    Aska::Yayoi::NetworkEvent::RequestPoll(Aska::Yayoi::TransportProtocolBase*, Aska::Yayoi::ISocketNotify*, Aska::Yayoi::SelectMode, unsigned short, long)(param_1,*plVar1,param_3,param_4,param_5,param_6,param_7);
  }
  return;
}

// ==== Aska::Yayoi::NetworkManager::BeginConnect(Aska::Yayoi::TransportProtocolBase*, Aska::Yayoi::ISocketNotify*, Aska::Yayoi::IPAddress const&, long)
// vaddr 0x2204740 | ghidra 0x2304740 | size 108 | symbol _ZN4Aska5Yayoi14NetworkManager12BeginConnectEPNS0_21TransportProtocolBaseEPNS0_13ISocketNotifyERKNS0_9IPAddressEl | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi14NetworkManager12BeginConnectEPNS0_21TransportProtocolBaseEPNS0_13ISocketNotifyERKNS0_9IPAddressEl
               (undefined8 *param_1,long param_2,undefined8 param_3,undefined8 param_4,
               undefined8 param_5,long param_6)

{
  long *plVar1;
  long lStack_28;
  
  lStack_28 = param_6;
  if (param_6 == 0) {
    lStack_28 = *(long *)(param_2 + 200);
  }
  plVar1 = (long *)Aska::THashMap<long, Aska::Yayoi::NetworkEvent*, Aska::THasher<long>, Aska::TEqualTo<long>, Aska::TAllocator<Aska::TPair<long const, Aska::Yayoi::NetworkEvent*> > >::operator[](long const&)(param_2,&lStack_28);
  if (*plVar1 == 0) {
    *param_1 = 0xfffffffffffffc38;
  }
  else {
    Aska::Yayoi::NetworkEvent::RequestConnect(Aska::Yayoi::TransportProtocolBase*, Aska::Yayoi::ISocketNotify*, Aska::Yayoi::IPAddress const&)(param_1,*plVar1,param_3,param_4,param_5);
  }
  return;
}

// ==== Aska::Yayoi::NetworkManager::AddErrorCallback(Aska::Yayoi::ISocketNotify*, Aska::Status, char const*, bool, long)
// vaddr 0x22047ac | ghidra 0x23047ac | size 132 | symbol _ZN4Aska5Yayoi14NetworkManager16AddErrorCallbackEPNS0_13ISocketNotifyENS_6StatusEPKcbl | lib libSOA-3.7.0.so | 2026-10-04
uint _ZN4Aska5Yayoi14NetworkManager16AddErrorCallbackEPNS0_13ISocketNotifyENS_6StatusEPKcbl
               (long param_1,undefined8 param_2,undefined8 *param_3,undefined8 param_4,uint param_5,
               undefined8 param_6)

{
  uint uVar1;
  long *plVar2;
  long lVar3;
  undefined8 uStack_38;
  undefined8 uStack_28;
  
  uStack_28 = param_6;
  if ((param_5 & 1) != 0) {
    uStack_28 = *(undefined8 *)(param_1 + 200);
  }
  plVar2 = (long *)Aska::THashMap<long, Aska::Yayoi::NetworkEvent*, Aska::THasher<long>, Aska::TEqualTo<long>, Aska::TAllocator<Aska::TPair<long const, Aska::Yayoi::NetworkEvent*> > >::operator[](long const&)(param_1,&uStack_28);
  lVar3 = *plVar2;
  if (lVar3 == 0) {
    plVar2 = (long *)Aska::THashMap<long, Aska::Yayoi::NetworkEvent*, Aska::THasher<long>, Aska::TEqualTo<long>, Aska::TAllocator<Aska::TPair<long const, Aska::Yayoi::NetworkEvent*> > >::operator[](long const&)(param_1,param_1 + 200);
    lVar3 = *plVar2;
    uVar1 = 0;
    if (lVar3 == 0) goto code_r0x02304818;
  }
  uStack_38 = *param_3;
  uVar1 = Aska::Yayoi::NetworkEvent::AddErrorCallback(Aska::Yayoi::ISocketNotify*, Aska::Status, char const*)(lVar3,param_2,&uStack_38,param_4);
code_r0x02304818:
  return uVar1 & 1;
}

// ==== Aska::Yayoi::NetworkManager::AddHttpRequest(Aska::Yayoi::TPeerNotify<Aska::Yayoi::TProtocolSuite<Aska::Yayoi::HttpProtocol, Aska::Yayoi::SSLProtocol, Aska::Yayoi::NoProtocol<2> > >*, Aska::TSharedPointer<Aska::Yayoi::URI>, Aska::TSharedPointer<Aska::Yayoi::TDataSuite<Aska::Yayoi::TProtocolSuite<Aska::Yayoi::HttpProtocol, Aska::Yayoi::SSLProtocol, Aska::Yayoi::NoProtocol<2> > > >, Aska::Yayoi::TProtocolSuite<Aska::Yayoi::HttpProtocol, Aska::Yayoi::SSLProtocol, Aska::Yayoi::NoProtocol<2> >*, Aska::Yayoi::HttpProtocol*)
// vaddr 0x2204830 | ghidra 0x2304830 | size 292 | symbol _ZN4Aska5Yayoi14NetworkManager14AddHttpRequestEPNS0_11TPeerNotifyINS0_14TProtocolSuiteINS0_12HttpProtocolENS0_11SSLProtocolENS0_10NoProtocolILi2EEEEEEENS_14TSharedPointerINS0_3URIEEENSB_INS0_10TDataSuiteIS8_EEEEPS8_PS4_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi14NetworkManager14AddHttpRequestEPNS0_11TPeerNotifyINS0_14TProtocolSuiteINS0_12HttpProtocolENS0_11SSLProtocolENS0_10NoProtocolILi2EEEEEEENS_14TSharedPointerINS0_3URIEEENSB_INS0_10TDataSuiteIS8_EEEEPS8_PS4_
               (long *param_1,long param_2,undefined8 param_3,long *param_4,long *param_5)

{
  int iVar1;
  char cVar2;
  bool bVar3;
  long lVar4;
  undefined8 uVar5;
  long lStack_40;
  int *piStack_38;
  long lStack_30;
  int *piStack_28;
  
  lStack_30 = *param_4;
  uVar5 = *(undefined8 *)(param_2 + 0xd8);
  piStack_28 = (int *)param_4[1];
  if (piStack_28 != (int *)0x0) {
    do {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piStack_28,0x10);
      if (bVar3) {
        *piStack_28 = *piStack_28 + 1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
  }
  lStack_40 = *param_5;
  piStack_38 = (int *)param_5[1];
  if (piStack_38 != (int *)0x0) {
    do {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piStack_38,0x10);
      if (bVar3) {
        *piStack_38 = *piStack_38 + 1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
  }
  Aska::Yayoi::NativeHttpRequestProcessor::AddRequest(Aska::Yayoi::TPeerNotify<Aska::Yayoi::TProtocolSuite<Aska::Yayoi::HttpProtocol, Aska::Yayoi::SSLProtocol, Aska::Yayoi::NoProtocol<2> > >*, Aska::TSharedPointer<Aska::Yayoi::URI>, Aska::TSharedPointer<Aska::Yayoi::TDataSuite<Aska::Yayoi::TProtocolSuite<Aska::Yayoi::HttpProtocol, Aska::Yayoi::SSLProtocol, Aska::Yayoi::NoProtocol<2> > > >, Aska::Yayoi::TProtocolSuite<Aska::Yayoi::HttpProtocol, Aska::Yayoi::SSLProtocol, Aska::Yayoi::NoProtocol<2> >*, Aska::Yayoi::HttpProtocol*)(param_1,uVar5,param_3,&lStack_30,&lStack_40);
  lVar4 = lStack_40;
  if (piStack_38 == (int *)0x0) {
code_r0x023048bc:
    if (lStack_40 != 0) {
      Aska::Yayoi::SSLProtocoledData::FreeInnerData()(lStack_40 + 0x198);
      Aska::Yayoi::HttpProtocoledData::~HttpProtocoledData()(lVar4);
      operator delete(void*)(lVar4);
    }
    if (piStack_38 != (int *)0x0) {
      Aska::TSharedPointerCode::DeleteCounter(int*)();
    }
  }
  else {
    do {
      iVar1 = *piStack_38;
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piStack_38,0x10);
      if (bVar3) {
        *piStack_38 = iVar1 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    if (iVar1 + -1 == 0) goto code_r0x023048bc;
  }
  lVar4 = lStack_30;
  lStack_40 = 0;
  piStack_38 = (int *)0x0;
  if (piStack_28 != (int *)0x0) {
    do {
      iVar1 = *piStack_28;
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piStack_28,0x10);
      if (bVar3) {
        *piStack_28 = iVar1 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    if (iVar1 + -1 != 0) goto code_r0x0230492c;
  }
  if (lStack_30 != 0) {
    Aska::Yayoi::URI::DeleteBuffer()(lStack_30);
    operator delete(void*)(lVar4);
  }
  if (piStack_28 != (int *)0x0) {
    Aska::TSharedPointerCode::DeleteCounter(int*)();
  }
code_r0x0230492c:
  lStack_30 = 0;
  piStack_28 = (int *)0x0;
  if (-1 < *param_1) {
    Aska::Semaphore::Signal() const(*(long *)(param_2 + 0xc0) + 0x38);
  }
  return;
}

// ==== Aska::Yayoi::NetworkManager::RegisterVersatileTask(Aska::Task*)
// vaddr 0x2204954 | ghidra 0x2304954 | size 12 | symbol _ZN4Aska5Yayoi14NetworkManager21RegisterVersatileTaskEPNS_4TaskE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi14NetworkManager21RegisterVersatileTaskEPNS_4TaskE(long param_1)

{
  (*(code *)PTR__ZN4Aska11TaskManager3AddEPNS_4TaskE_02c95ab0)
            (*(undefined8 *)(*(long *)(param_1 + 0xc0) + 0x20));
  return;
}

// ==== Aska::Yayoi::NetworkManagerThread::DoWakeup()
// vaddr 0x2204b58 | ghidra 0x2304b58 | size 8 | symbol _ZN4Aska5Yayoi20NetworkManagerThread8DoWakeupEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi20NetworkManagerThread8DoWakeupEv(long param_1)

{
  (*(code *)PTR__ZNK4Aska9Semaphore6SignalEv_02c96cd0)(param_1 + 0x38);
  return;
}

// ==== Aska::Yayoi::NetworkManagerThread::GetThreadID()
// vaddr 0x2204b60 | ghidra 0x2304b60 | size 8 | symbol _ZN4Aska5Yayoi20NetworkManagerThread11GetThreadIDEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska5Yayoi20NetworkManagerThread11GetThreadIDEv(long param_1)

{
  return *(undefined8 *)(param_1 + 8);
}

// ==== non-virtual thunk to Aska::Yayoi::NetworkManagerThread::DoWakeup()
// vaddr 0x2204b68 | ghidra 0x2304b68 | size 8 | symbol _ZThn24_N4Aska5Yayoi20NetworkManagerThread8DoWakeupEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZThn24_N4Aska5Yayoi20NetworkManagerThread8DoWakeupEv(long param_1)

{
  (*(code *)PTR__ZNK4Aska9Semaphore6SignalEv_02c96cd0)(param_1 + 0x20);
  return;
}

// ==== non-virtual thunk to Aska::Yayoi::NetworkManagerThread::GetThreadID()
// vaddr 0x2204b70 | ghidra 0x2304b70 | size 8 | symbol _ZThn24_N4Aska5Yayoi20NetworkManagerThread11GetThreadIDEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZThn24_N4Aska5Yayoi20NetworkManagerThread11GetThreadIDEv(long param_1)

{
  return *(undefined8 *)(param_1 + -0x10);
}

// ==== Aska::Yayoi::URI::CalcBufferSize(char const*)
// vaddr 0x220f234 | ghidra 0x230f234 | size 24 | symbol _ZN4Aska5Yayoi3URI14CalcBufferSizeEPKc | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska5Yayoi3URI14CalcBufferSizeEPKc(void)

{
  long lVar1;
  
  lVar1 = strlen();
  return lVar1 * 2 + 0xc;
}

// ==== Aska::Yayoi::URI::GetBufferSize(unsigned long)
// vaddr 0x220f24c | ghidra 0x230f24c | size 12 | symbol _ZN4Aska5Yayoi3URI13GetBufferSizeEm | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska5Yayoi3URI13GetBufferSizeEm(long param_1)

{
  return param_1 * 2 + 10;
}

// ==== Aska::Yayoi::URI::DeleteBuffer()
// vaddr 0x220f258 | ghidra 0x230f258 | size 56 | symbol _ZN4Aska5Yayoi3URI12DeleteBufferEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi3URI12DeleteBufferEv(long param_1)

{
  if (*(char *)(param_1 + 0x68) != '\0') {
    if (*(long *)(param_1 + 0x50) != 0) {
      operator delete[](void*)();
      *(undefined8 *)(param_1 + 0x50) = 0;
    }
    *(undefined1 *)(param_1 + 0x68) = 0;
    return;
  }
  *(undefined8 *)(param_1 + 0x50) = 0;
  return;
}

// ==== Aska::Yayoi::URI::Deserialize(char const*, unsigned short, Aska::Yayoi::AddressFamily, signed char*, unsigned long)
// vaddr 0x220f290 | ghidra 0x230f290 | size 1820 | symbol _ZN4Aska5Yayoi3URI11DeserializeEPKctNS0_13AddressFamilyEPam | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi3URI11DeserializeEPKctNS0_13AddressFamilyEPam
               (long *param_1,undefined4 *param_2,undefined8 param_3,uint param_4,undefined4 param_5
               ,long param_6,ulong param_7)

{
  ulong uVar1;
  ulong uVar2;
  undefined4 *puVar3;
  undefined1 *puVar4;
  char cVar5;
  bool bVar6;
  int iVar7;
  long lVar8;
  undefined8 uVar9;
  long lVar10;
  undefined4 uVar11;
  long lVar12;
  ulong uVar13;
  ulong uVar14;
  long *plVar15;
  ulong uVar16;
  bool bVar17;
  undefined1 auStack_78 [8];
  undefined4 uStack_70;
  undefined2 uStack_6c;
  long lStack_68;
  
  *(undefined1 *)(param_2 + 0x3e) = 0;
  *param_2 = 5;
  memset(param_2 + 2,0,0x48);
  if (param_6 == 0) {
    plVar15 = (long *)(param_2 + 0x14);
    if (*(char *)(param_2 + 0x1a) == '\0') {
      *plVar15 = 0;
    }
    else {
      if (*plVar15 != 0) {
        operator delete[](void*)();
        *plVar15 = 0;
      }
      *(undefined1 *)(param_2 + 0x1a) = 0;
    }
    lVar8 = strlen(param_3);
    uVar13 = lVar8 + 1;
    param_7 = uVar13 * 2 + 10;
    if (param_7 == 0) {
code_r0x0230f3b4:
      *param_1 = -0x3bf;
      return;
    }
    lVar8 = **(long **)PTR__ZN4Aska6Global19m_pNetworkAllocatorE_02cbc200;
    if (lVar8 == 0) {
      lVar8 = Aska::Global::GetAvailableMemoryManager()();
    }
    param_6 = Aska::MemoryManager::Malloc(unsigned long)(lVar8,param_7);
    if (param_6 == 0) goto code_r0x0230f3b4;
    *(undefined1 *)(param_2 + 0x1a) = 1;
  }
  else {
    lVar8 = strlen(param_3);
    uVar13 = lVar8 + 1;
    if (param_7 < uVar13 * 2 + 10) {
      *param_1 = -0x3eb;
      return;
    }
  }
  plVar15 = (long *)(param_2 + 0x14);
  if (*plVar15 != param_6) {
    if (*plVar15 != 0) {
      if (*(char *)(param_2 + 0x1a) == '\0') {
        *plVar15 = 0;
      }
      else {
        operator delete[](void*)();
        *(undefined8 *)(param_2 + 0x14) = 0;
        *(undefined1 *)(param_2 + 0x1a) = 0;
      }
    }
    *(long *)(param_2 + 0x14) = param_6;
    *(ulong *)(param_2 + 0x16) = param_6 + (param_7 >> 1);
    *(ulong *)(param_2 + 0x18) = param_7 >> 1;
  }
  memcpy(param_6,param_3,uVar13 + 1);
  *(ulong *)(param_2 + 2) = uVar13;
  uStack_6c = 0;
  uStack_70 = 0;
  if (uVar13 == 0) {
    lVar8 = 0;
    lVar10 = *(long *)(param_2 + 8);
    if (lVar10 != 0) goto code_r0x0230f42c;
code_r0x0230f85c:
    if ((*(long *)(param_2 + 0xc) == 0) || (*(long *)(param_2 + 0xe) != 0)) {
      if ((*(long *)(param_2 + 0x10) == 0) || (*(long *)(param_2 + 0x12) != 0)) {
        lVar8 = *(long *)(param_2 + 4);
        goto joined_r0x0230f884;
      }
      *(ulong *)(param_2 + 0x12) =
           (*(long *)(param_2 + 0x14) + uVar13 + -1) - *(long *)(param_2 + 0x10);
      memcpy(*(long *)(param_2 + 0x16) + lVar8);
      lVar10 = *(long *)(param_2 + 0x16);
      lVar12 = *(long *)(param_2 + 0x12);
    }
    else {
      *(ulong *)(param_2 + 0xe) =
           (*(long *)(param_2 + 0x14) + uVar13 + -1) - *(long *)(param_2 + 0xc);
      memcpy(*(long *)(param_2 + 0x16) + lVar8);
      lVar10 = *(long *)(param_2 + 0x16);
      lVar12 = *(long *)(param_2 + 0xe);
    }
    *(long *)(param_2 + 0xc) = lVar10 + lVar8;
    *(undefined1 *)(lVar10 + lVar12 + lVar8) = 0;
    lVar8 = *(long *)(param_2 + 4);
  }
  else {
    uVar16 = 0;
    lVar8 = 0;
    bVar17 = true;
    bVar6 = false;
    do {
      puVar4 = (undefined1 *)(*plVar15 + uVar16);
      switch(*puVar4) {
      case 0x23:
        if (*(long *)(param_2 + 0x10) == 0) {
          puVar4 = puVar4 + 1;
          *(undefined1 **)(param_2 + 0x10) = puVar4;
          if (*(long *)(param_2 + 0xc) == 0) {
            if (*(long *)(param_2 + 8) == 0) goto code_r0x0230f9a4;
            *(undefined1 **)(param_2 + 10) = puVar4 + (-1 - *(long *)(param_2 + 8));
            memcpy(*(long *)(param_2 + 0x16) + lVar8);
            lVar12 = *(long *)(param_2 + 0x16);
            lVar10 = *(long *)(param_2 + 10);
            *(long *)(param_2 + 8) = lVar12 + lVar8;
          }
          else {
            *(undefined1 **)(param_2 + 0xe) = puVar4 + (-1 - *(long *)(param_2 + 0xc));
            memcpy(*(long *)(param_2 + 0x16) + lVar8);
            lVar12 = *(long *)(param_2 + 0x16);
            lVar10 = *(long *)(param_2 + 0xe);
            *(long *)(param_2 + 0xc) = lVar12 + lVar8;
          }
          lVar10 = lVar10 + lVar8;
          lVar8 = lVar10 + 1;
          *(undefined1 *)(lVar12 + lVar10) = 0;
        }
        break;
      case 0x2f:
        if (*(char *)(*plVar15 + uVar16 + 1) == '/') {
          *(undefined1 **)(param_2 + 4) = puVar4 + 2;
          uVar16 = uVar16 + 1;
        }
        else if (*(long *)(param_2 + 8) == 0) {
          *(undefined1 **)(param_2 + 8) = puVar4;
          if (!bVar6) {
            if (*(long *)(param_2 + 4) == 0) {
              bVar6 = false;
              break;
            }
            *(long *)(param_2 + 6) = (long)puVar4 - *(long *)(param_2 + 4);
            memcpy(*(long *)(param_2 + 0x16) + lVar8);
            lVar10 = *(long *)(param_2 + 6) + lVar8;
            *(long *)(param_2 + 4) = *(long *)(param_2 + 0x16) + lVar8;
            lVar8 = lVar10 + 1;
            *(undefined1 *)(*(long *)(param_2 + 0x16) + lVar10) = 0;
          }
          bVar6 = true;
        }
        break;
      case 0x3a:
        if (bVar17) {
          *puVar4 = 0;
          lVar10 = *plVar15;
          iVar7 = strcasecmp(lVar10,&UNK_02871fee/*"http"*/);
          if (iVar7 == 0) {
            uVar11 = 0;
          }
          else {
            iVar7 = strcasecmp(lVar10,&UNK_029d4c6c/*"https"*/);
            if (iVar7 == 0) {
              uVar11 = 1;
            }
            else {
              iVar7 = strcasecmp(lVar10,&UNK_029d4c72/*"ftp"*/);
              if (iVar7 == 0) {
                uVar11 = 2;
              }
              else {
                iVar7 = strcasecmp(lVar10,&UNK_029de20d/*"ws"*/);
                if (iVar7 == 0) {
                  uVar11 = 3;
                }
                else {
                  iVar7 = strcasecmp(lVar10,&UNK_029d4c76/*"arpc"*/);
                  uVar11 = 4;
                  if (iVar7 != 0) {
                    uVar11 = 5;
                  }
                }
              }
            }
          }
          *param_2 = uVar11;
          *(undefined1 *)(lVar10 + uVar16) = 0x3a;
          memcpy(*(long *)(param_2 + 0x16) + lVar8,*(undefined8 *)(param_2 + 0x14),uVar16);
          lVar10 = uVar16 + lVar8;
          bVar17 = false;
          lVar8 = lVar10 + 1;
          *(undefined1 *)(*(long *)(param_2 + 0x16) + lVar10) = 0;
          if (*(char *)(*(long *)(param_2 + 0x14) + uVar16 + 1) != '/') {
            bVar17 = false;
            *(ulong *)(param_2 + 8) = *(long *)(param_2 + 0x14) + uVar16 + 1;
          }
        }
        else if ((param_4 & 0xffff) == 0) {
          if (bVar6) {
code_r0x0230f6f4:
            bVar6 = true;
          }
          else {
            if (*(long *)(param_2 + 4) != 0) {
              *(long *)(param_2 + 6) = (long)puVar4 - *(long *)(param_2 + 4);
              memcpy(*(long *)(param_2 + 0x16) + lVar8);
              lVar10 = *(long *)(param_2 + 6) + lVar8;
              lVar12 = *(long *)(param_2 + 0x16) + lVar8;
              lVar8 = lVar10 + 1;
              *(long *)(param_2 + 4) = lVar12;
              *(undefined1 *)(*(long *)(param_2 + 0x16) + lVar10) = 0;
              goto code_r0x0230f6f4;
            }
            bVar6 = false;
          }
          uVar11 = uStack_70;
          uVar1 = uVar16 + 1;
          uVar14 = uVar1;
          if (uVar1 < uVar13) {
            lVar10 = *plVar15;
            cVar5 = *(char *)(lVar10 + uVar1);
            uVar14 = uVar16;
            if (cVar5 != '/') {
              uVar2 = uVar16 + 2;
              uStack_70 = CONCAT31(uStack_70._1_3_,cVar5);
              uVar14 = uVar2;
              if ((uVar2 < uVar13) && (uVar14 = uVar1, *(char *)(lVar10 + uVar2) != '/')) {
                uVar1 = uVar16 + 3;
                uStack_70._2_2_ = SUB42(uVar11,2);
                uStack_70._0_2_ = CONCAT11(*(char *)(lVar10 + uVar2),cVar5);
                uVar14 = uVar1;
                if ((uVar1 < uVar13) && (uVar14 = uVar2, *(char *)(lVar10 + uVar1) != '/')) {
                  uVar2 = uVar16 + 4;
                  uStack_70._3_1_ = SUB41(uVar11,3);
                  uStack_70._0_3_ = CONCAT12(*(char *)(lVar10 + uVar1),(undefined2)uStack_70);
                  uVar14 = uVar2;
                  if ((uVar2 < uVar13) && (uVar14 = uVar1, *(char *)(lVar10 + uVar2) != '/')) {
                    uVar1 = uVar16 + 5;
                    uStack_70 = CONCAT13(*(char *)(lVar10 + uVar2),(undefined3)uStack_70);
                    uVar14 = uVar1;
                    if ((uVar1 < uVar13) &&
                       (cVar5 = *(char *)(lVar10 + uVar1), uVar14 = uVar2, cVar5 != '/')) {
                      uVar16 = uVar16 + 6;
                      uStack_6c = CONCAT11(uStack_6c._1_1_,cVar5);
                      uVar14 = uVar16;
                      if ((uVar16 < uVar13) && (uVar14 = uVar1, *(char *)(lVar10 + uVar16) != '/'))
                      {
                        uStack_6c = CONCAT11(*(char *)(lVar10 + uVar16),cVar5);
                        uVar14 = uVar16;
                      }
                    }
                  }
                }
              }
            }
          }
          param_4 = strtol(&uStack_70,&lStack_68,10);
          bVar17 = false;
          uVar16 = uVar14;
        }
        else {
          bVar17 = false;
        }
        break;
      case 0x3f:
        if (*(long *)(param_2 + 0xc) == 0) {
          if (*(long *)(param_2 + 8) == 0) {
code_r0x0230f9a4:
            lStack_68 = -0x3ee;
            goto code_r0x0230f940;
          }
          *(undefined1 **)(param_2 + 10) = puVar4 + 1 + (-1 - *(long *)(param_2 + 8));
          *(undefined1 **)(param_2 + 0xc) = puVar4 + 1;
          memcpy(*(long *)(param_2 + 0x16) + lVar8);
          lVar10 = *(long *)(param_2 + 10) + lVar8;
          *(long *)(param_2 + 8) = *(long *)(param_2 + 0x16) + lVar8;
          lVar8 = lVar10 + 1;
          *(undefined1 *)(*(long *)(param_2 + 0x16) + lVar10) = 0;
        }
      }
      uVar16 = uVar16 + 1;
    } while (uVar16 < uVar13);
    lVar10 = *(long *)(param_2 + 8);
    if (lVar10 == 0) goto code_r0x0230f85c;
code_r0x0230f42c:
    if (*(long *)(param_2 + 10) != 0) goto code_r0x0230f85c;
    *(ulong *)(param_2 + 10) = (*(long *)(param_2 + 0x14) + uVar13 + -1) - lVar10;
    memcpy(*(long *)(param_2 + 0x16) + lVar8);
    *(long *)(param_2 + 8) = *(long *)(param_2 + 0x16) + lVar8;
    *(undefined1 *)(*(long *)(param_2 + 0x16) + *(long *)(param_2 + 10) + lVar8) = 0;
    lVar8 = *(long *)(param_2 + 4);
  }
joined_r0x0230f884:
  if (lVar8 == 0) {
    lVar8 = *(long *)(param_2 + 0x14);
    *(long *)(param_2 + 4) = lVar8;
    uVar9 = strlen(lVar8);
    *(undefined8 *)(param_2 + 6) = uVar9;
  }
  puVar3 = param_2 + 0x1c;
  Aska::Yayoi::Socket::ConvertIPAddrNtoB(char const*, unsigned short, Aska::Yayoi::SocketType, Aska::Yayoi::AddressFamily, Aska::Yayoi::IPAddress*)(&lStack_68,lVar8,param_4,1,param_5,puVar3);
  if (lStack_68 < 0) {
    if (*(char *)(param_2 + 0x1a) == '\0') {
      *plVar15 = 0;
    }
    else {
      if (*plVar15 != 0) {
        operator delete[](void*)();
        *plVar15 = 0;
      }
      *(undefined1 *)(param_2 + 0x1a) = 0;
    }
    Aska::Yayoi::IPAddress::Clear()(puVar3);
    if (lStack_68 < 0) goto code_r0x0230f940;
  }
  else {
    lStack_68 = 0;
  }
  Aska::Yayoi::IPAddress::SetPort(unsigned short)(auStack_78,puVar3,param_4);
  *(undefined1 *)(param_2 + 0x3e) = 1;
code_r0x0230f940:
  *param_1 = lStack_68;
  return;
}

// ==== Aska::Yayoi::URI::ResolveThis(Aska::Yayoi::AddressFamily, unsigned short)
// vaddr 0x220f9ac | ghidra 0x230f9ac | size 144 | symbol _ZN4Aska5Yayoi3URI11ResolveThisENS0_13AddressFamilyEt | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi3URI11ResolveThisENS0_13AddressFamilyEt
               (long *param_1,long param_2,undefined4 param_3,undefined4 param_4)

{
  long lStack_28;
  
  Aska::Yayoi::Socket::ConvertIPAddrNtoB(char const*, unsigned short, Aska::Yayoi::SocketType, Aska::Yayoi::AddressFamily, Aska::Yayoi::IPAddress*)(&lStack_28,*(undefined8 *)(param_2 + 0x10),param_4,1,param_3,param_2 + 0x70);
  if (lStack_28 < 0) {
    if (*(char *)(param_2 + 0x68) == '\0') {
      *(undefined8 *)(param_2 + 0x50) = 0;
    }
    else {
      if (*(long *)(param_2 + 0x50) != 0) {
        operator delete[](void*)();
        *(undefined8 *)(param_2 + 0x50) = 0;
      }
      *(undefined1 *)(param_2 + 0x68) = 0;
    }
    Aska::Yayoi::IPAddress::Clear()(param_2 + 0x70);
    *param_1 = lStack_28;
  }
  else {
    *param_1 = 0;
  }
  return;
}

// ==== Aska::Yayoi::URI::Clear()
// vaddr 0x220fa3c | ghidra 0x230fa3c | size 56 | symbol _ZN4Aska5Yayoi3URI5ClearEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi3URI5ClearEv(long param_1)

{
  if (*(char *)(param_1 + 0x68) == '\0') {
    *(undefined8 *)(param_1 + 0x50) = 0;
  }
  else {
    if (*(long *)(param_1 + 0x50) != 0) {
      operator delete[](void*)();
      *(undefined8 *)(param_1 + 0x50) = 0;
    }
    *(undefined1 *)(param_1 + 0x68) = 0;
  }
  (*(code *)PTR__ZN4Aska5Yayoi9IPAddress5ClearEv_02ca3018)(param_1 + 0x70);
  return;
}

// ==== Aska::Yayoi::URI::SetPort(unsigned short)
// vaddr 0x220fa74 | ghidra 0x230fa74 | size 28 | symbol _ZN4Aska5Yayoi3URI7SetPortEt | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi3URI7SetPortEt(undefined8 *param_1,long param_2)

{
  if (*(int *)(param_2 + 0x70) != 0) {
    (*(code *)PTR__ZN4Aska5Yayoi9IPAddress7SetPortEt_02ca65e0)(param_2 + 0x70);
    return;
  }
  *param_1 = 0xfffffffffffffc4d;
  return;
}

// ==== Aska::Yayoi::URI::Serialize(signed char*, unsigned long) const
// vaddr 0x220fa90 | ghidra 0x230fa90 | size 8 | symbol _ZNK4Aska5Yayoi3URI9SerializeEPam | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska5Yayoi3URI9SerializeEPam(void)

{
  return 0;
}

// ==== Aska::Yayoi::NativeHttpRequestProcessor::NativeHttpRequestProcessor()
// vaddr 0x259e3ec | ghidra 0x269e3ec | size 64 | symbol _ZN4Aska5Yayoi26NativeHttpRequestProcessorC1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi26NativeHttpRequestProcessorC2Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska6TQueueIPNS_5Yayoi16NativeHttpClientELi32EEE_02cc23e8 + 0x10);
  *(undefined4 *)(param_1 + 1) = 1;
  *(undefined4 *)((long)param_1 + 0xc) = 0;
  Aska::TPoolAtomic<Aska::Yayoi::NativeHttpClient, 32>::TPoolAtomic()(param_1 + 0x23);
  Aska::FastCriticalSection::FastCriticalSection()(param_1 + 0x107);
  *(undefined1 *)(param_1 + 0x119) = 0;
  return;
}

// ==== Aska::Yayoi::NativeHttpRequestProcessor::~NativeHttpRequestProcessor()
// vaddr 0x259e578 | ghidra 0x269e578 | size 28 | symbol _ZN4Aska5Yayoi26NativeHttpRequestProcessorD1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi26NativeHttpRequestProcessorD2Ev(long param_1)

{
  Aska::FastCriticalSection::~FastCriticalSection()(param_1 + 0x838);
  (*(code *)PTR__ZN4Aska11TPoolAtomicINS_5Yayoi16NativeHttpClientELi32EED2Ev_02ca4320)
            (param_1 + 0x118);
  return;
}

// ==== Aska::Yayoi::NativeHttpRequestProcessor::AddRequest(Aska::Yayoi::TPeerNotify<Aska::Yayoi::TProtocolSuite<Aska::Yayoi::HttpProtocol, Aska::Yayoi::SSLProtocol, Aska::Yayoi::NoProtocol<2> > >*, Aska::TSharedPointer<Aska::Yayoi::URI>, Aska::TSharedPointer<Aska::Yayoi::TDataSuite<Aska::Yayoi::TProtocolSuite<Aska::Yayoi::HttpProtocol, Aska::Yayoi::SSLProtocol, Aska::Yayoi::NoProtocol<2> > > >, Aska::Yayoi::TProtocolSuite<Aska::Yayoi::HttpProtocol, Aska::Yayoi::SSLProtocol, Aska::Yayoi::NoProtocol<2> >*, Aska::Yayoi::HttpProtocol*)
// vaddr 0x259e6c8 | ghidra 0x269e6c8 | size 1244 | symbol _ZN4Aska5Yayoi26NativeHttpRequestProcessor10AddRequestEPNS0_11TPeerNotifyINS0_14TProtocolSuiteINS0_12HttpProtocolENS0_11SSLProtocolENS0_10NoProtocolILi2EEEEEEENS_14TSharedPointerINS0_3URIEEENSB_INS0_10TDataSuiteIS8_EEEEPS8_PS4_ | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Possible PIC construction at 0x0269eb98: Changing call to branch */

void _ZN4Aska5Yayoi26NativeHttpRequestProcessor10AddRequestEPNS0_11TPeerNotifyINS0_14TProtocolSuiteINS0_12HttpProtocolENS0_11SSLProtocolENS0_10NoProtocolILi2EEEEEEENS_14TSharedPointerINS0_3URIEEENSB_INS0_10TDataSuiteIS8_EEEEPS8_PS4_
               (undefined8 *param_1,long param_2,undefined8 param_3,long *param_4,long *param_5,
               undefined8 param_6,long param_7)

{
  int *piVar1;
  long *plVar2;
  long *plVar3;
  long *plVar4;
  int *piVar5;
  uint uVar6;
  char cVar7;
  bool bVar8;
  ulong uVar9;
  int iVar10;
  long lVar11;
  int *piVar12;
  uint uVar13;
  long lVar14;
  uint *puVar15;
  uint uVar16;
  uint uVar17;
  uint uVar18;
  long lVar19;
  long lVar20;
  
  DataMemoryBarrier(2,3);
  if (0x1f < *(int *)(param_2 + 0x82c)) {
code_r0x0269e9b0:
    *param_1 = 0xfffffffffffffc41;
    return;
  }
  uVar13 = *(uint *)(param_2 + 0x828);
  piVar1 = (int *)(param_2 + 0x82c);
  uVar16 = uVar13 + 0x1f;
  if (-1 < (int)uVar13) {
    uVar16 = uVar13;
  }
  puVar15 = (uint *)(param_2 + (long)((int)uVar16 >> 5) * 4 + 0x120);
  uVar16 = *puVar15;
  uVar18 = 1 << (ulong)(uVar13 & 0x1f);
  uVar17 = uVar18 | uVar16;
  do {
    uVar6 = 0;
    if ((int)uVar13 < 0x20) {
      uVar6 = uVar13;
    }
    if ((uVar18 & uVar16) == 0) {
      do {
        uVar13 = *puVar15;
        if (uVar13 != uVar16) {
          ClearExclusiveLocal();
          break;
        }
        cVar7 = '\x01';
        bVar8 = (bool)ExclusiveMonitorPass(puVar15,0x10);
        if (bVar8) {
          *puVar15 = uVar17;
          cVar7 = ExclusiveMonitorsStatus();
        }
      } while (cVar7 != '\0');
      if ((uVar16 == uVar13) && (uVar16 != *puVar15)) break;
    }
    DataMemoryBarrier(2,3);
    if (0x1f < *piVar1) goto code_r0x0269e9b0;
    uVar13 = 0;
    if ((int)uVar6 < 0x1f) {
      uVar13 = uVar6 + 1;
    }
    uVar16 = uVar13 + 0x1f;
    if (-1 < (int)uVar13) {
      uVar16 = uVar13;
    }
    lVar11 = param_2 + (long)((int)uVar16 >> 5) * 4;
    uVar16 = *(uint *)(lVar11 + 0x120);
    uVar18 = 1 << (ulong)(uVar13 & 0x1f);
    puVar15 = (uint *)(lVar11 + 0x120);
    uVar17 = uVar16 | uVar18;
  } while( true );
  do {
    cVar7 = '\x01';
    bVar8 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar8) {
      *piVar1 = *piVar1 + 1;
      cVar7 = ExclusiveMonitorsStatus();
    }
  } while (cVar7 != '\0');
  DataMemoryBarrier(2,3);
  iVar10 = 0;
  if ((int)uVar6 < 0x1f) {
    iVar10 = uVar6 + 1;
  }
  do {
    cVar7 = '\x01';
    bVar8 = (bool)ExclusiveMonitorPass((int *)(param_2 + 0x828),0x10);
    if (bVar8) {
      *(int *)(param_2 + 0x828) = iVar10;
      cVar7 = ExclusiveMonitorsStatus();
    }
  } while (cVar7 != '\0');
  lVar11 = param_2 + (long)(int)uVar6 * 0x38;
  *(undefined8 *)(lVar11 + 0x138) = param_3;
  lVar19 = *(long *)(lVar11 + 0x150);
  lVar20 = (long)(int)uVar6;
  plVar2 = (long *)(lVar11 + 0x128);
  if (*param_4 != lVar19) {
    lVar14 = param_2 + lVar20 * 0x38;
    piVar12 = *(int **)(lVar14 + 0x158);
    plVar3 = (long *)(lVar11 + 0x150);
    plVar4 = (long *)(lVar14 + 0x158);
    if (piVar12 == (int *)0x0) {
code_r0x0269e858:
      if (lVar19 != 0) {
        Aska::Yayoi::URI::DeleteBuffer()(lVar19);
        operator delete(void*)(lVar19);
      }
      if (*plVar4 != 0) {
        Aska::TSharedPointerCode::DeleteCounter(int*)();
      }
    }
    else {
      do {
        iVar10 = *piVar12;
        cVar7 = '\x01';
        bVar8 = (bool)ExclusiveMonitorPass(piVar12,0x10);
        if (bVar8) {
          *piVar12 = iVar10 + -1;
          cVar7 = ExclusiveMonitorsStatus();
        }
      } while (cVar7 != '\0');
      if (iVar10 + -1 == 0) {
        lVar19 = *plVar3;
        goto code_r0x0269e858;
      }
    }
    *plVar3 = 0;
    *(undefined8 *)(lVar11 + 0x158) = 0;
    piVar12 = (int *)param_4[1];
    *plVar4 = (long)piVar12;
    *plVar3 = *param_4;
    if (piVar12 != (int *)0x0) {
      do {
        cVar7 = '\x01';
        bVar8 = (bool)ExclusiveMonitorPass(piVar12,0x10);
        if (bVar8) {
          *piVar12 = *piVar12 + 1;
          cVar7 = ExclusiveMonitorsStatus();
        }
      } while (cVar7 != '\0');
    }
  }
  lVar11 = param_2 + lVar20 * 0x38;
  lVar19 = *(long *)(lVar11 + 0x140);
  if (*param_5 != lVar19) {
    lVar14 = param_2 + lVar20 * 0x38;
    piVar12 = *(int **)(lVar14 + 0x148);
    plVar3 = (long *)(lVar11 + 0x140);
    plVar4 = (long *)(lVar14 + 0x148);
    if (piVar12 == (int *)0x0) {
code_r0x0269e8ec:
      if (lVar19 != 0) {
        Aska::Yayoi::SSLProtocoledData::FreeInnerData()(lVar19 + 0x198);
        Aska::Yayoi::HttpProtocoledData::~HttpProtocoledData()(lVar19);
        operator delete(void*)(lVar19);
      }
      if (*plVar4 != 0) {
        Aska::TSharedPointerCode::DeleteCounter(int*)();
      }
    }
    else {
      do {
        iVar10 = *piVar12;
        cVar7 = '\x01';
        bVar8 = (bool)ExclusiveMonitorPass(piVar12,0x10);
        if (bVar8) {
          *piVar12 = iVar10 + -1;
          cVar7 = ExclusiveMonitorsStatus();
        }
      } while (cVar7 != '\0');
      if (iVar10 + -1 == 0) {
        lVar19 = *plVar3;
        goto code_r0x0269e8ec;
      }
    }
    *plVar3 = 0;
    *(undefined8 *)(lVar11 + 0x148) = 0;
    piVar12 = (int *)param_5[1];
    *plVar4 = (long)piVar12;
    *plVar3 = *param_5;
    if (piVar12 != (int *)0x0) {
      do {
        cVar7 = '\x01';
        bVar8 = (bool)ExclusiveMonitorPass(piVar12,0x10);
        if (bVar8) {
          *piVar12 = *piVar12 + 1;
          cVar7 = ExclusiveMonitorsStatus();
        }
      } while (cVar7 != '\0');
    }
  }
  *(undefined8 *)(param_2 + lVar20 * 0x38 + 0x130) = param_6;
  *plVar2 = param_7;
  *(undefined4 *)(param_7 + 0x18) = 1;
  piVar12 = (int *)(param_2 + 0x870);
  iVar10 = 0;
  do {
    while (*piVar12 == -1) {
      cVar7 = '\x01';
      bVar8 = (bool)ExclusiveMonitorPass(piVar12,0x10);
      if (bVar8) {
        *piVar12 = 0;
        cVar7 = ExclusiveMonitorsStatus();
      }
      if (cVar7 == '\0') goto code_r0x0269ea4c;
    }
    ClearExclusiveLocal();
    bVar8 = iVar10 < 0x1ff;
    iVar10 = iVar10 + 1;
  } while (bVar8);
  piVar5 = (int *)(param_2 + 0x874);
  do {
    cVar7 = '\x01';
    bVar8 = (bool)ExclusiveMonitorPass(piVar5,0x10);
    if (bVar8) {
      *piVar5 = *piVar5 + 1;
      cVar7 = ExclusiveMonitorsStatus();
    }
  } while (cVar7 != '\0');
  do {
    if (*piVar12 != -1) {
      ClearExclusiveLocal();
      do {
        uVar9 = Aska::Semaphore::IsReady() const(param_2 + 0x8b0);
        if ((uVar9 & 1) == 0) {
          do {
            cVar7 = '\x01';
            bVar8 = (bool)ExclusiveMonitorPass(piVar5,0x10);
            if (bVar8) {
              *piVar5 = *piVar5 + -1;
              cVar7 = ExclusiveMonitorsStatus();
            }
          } while (cVar7 != '\0');
          Aska::Thread::Sleep(unsigned int)(1);
        }
        else {
          Aska::Semaphore::Wait() const(param_2 + 0x8b0);
        }
        do {
          cVar7 = '\x01';
          bVar8 = (bool)ExclusiveMonitorPass(piVar5,0x10);
          if (bVar8) {
            *piVar5 = *piVar5 + 1;
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
          if (cVar7 == '\0') goto code_r0x0269ea3c;
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
code_r0x0269ea3c:
  do {
    cVar7 = '\x01';
    bVar8 = (bool)ExclusiveMonitorPass(piVar5,0x10);
    if (bVar8) {
      *piVar5 = *piVar5 + -1;
      cVar7 = ExclusiveMonitorsStatus();
    }
  } while (cVar7 != '\0');
code_r0x0269ea4c:
  DataMemoryBarrier(2,3);
  uVar16 = *(uint *)(param_2 + 8);
  if (*(uint *)(param_2 + 0xc) == uVar16) {
    Aska::Yayoi::NativeHttpClient::~NativeHttpClient()(plVar2);
    uVar13 = (int)((ulong)((long)plVar2 - (param_2 + 0x128)) >> 3) * -0x49249249;
    uVar16 = uVar13 + 0x1f;
    if (-1 < (int)uVar13) {
      uVar16 = uVar13;
    }
    puVar15 = (uint *)(param_2 + (long)((int)uVar16 >> 5) * 4 + 0x120);
    do {
      cVar7 = '\x01';
      bVar8 = (bool)ExclusiveMonitorPass(puVar15,0x10);
      if (bVar8) {
        *puVar15 = *puVar15 & ~(1 << (ulong)(uVar13 & 0x1f));
        cVar7 = ExclusiveMonitorsStatus();
      }
    } while (cVar7 != '\0');
    do {
      cVar7 = '\x01';
      bVar8 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar8) {
        *piVar1 = *piVar1 + -1;
        cVar7 = ExclusiveMonitorsStatus();
      }
    } while (cVar7 != '\0');
    DataMemoryBarrier(2,3);
    *param_1 = 0xfffffffffffffc41;
    DataMemoryBarrier(2,3);
    *(undefined4 *)(param_2 + 0x870) = 0xffffffff;
    DataMemoryBarrier(2,3);
    if (*(int *)(param_2 + 0x874) < 0x15) {
      return;
    }
    piVar1 = (int *)(param_2 + 0x874);
    do {
      cVar7 = '\x01';
      bVar8 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar8) {
        *piVar1 = *piVar1 + -1;
        cVar7 = ExclusiveMonitorsStatus();
      }
    } while (cVar7 != '\0');
    uVar9 = Aska::Semaphore::IsReady() const(param_2 + 0x8b0);
    if ((uVar9 & 1) == 0) {
      return;
    }
code_r0x011bd9c0:
    (*(code *)PTR__ZNK4Aska9Semaphore6SignalEv_02c96cd0)(param_2 + 0x8b0);
    return;
  }
  iVar10 = 0;
  if (uVar16 + 1 < 0x21) {
    iVar10 = uVar16 + 1;
  }
  *(long **)(param_2 + (ulong)uVar16 * 8 + 0x10) = plVar2;
  *(int *)(param_2 + 8) = iVar10;
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_2 + 0x870) = 0xffffffff;
  DataMemoryBarrier(2,3);
  if (0x14 < *(int *)(param_2 + 0x874)) {
    piVar1 = (int *)(param_2 + 0x874);
    do {
      cVar7 = '\x01';
      bVar8 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar8) {
        *piVar1 = *piVar1 + -1;
        cVar7 = ExclusiveMonitorsStatus();
      }
    } while (cVar7 != '\0');
    uVar9 = Aska::Semaphore::IsReady() const(param_2 + 0x8b0);
    if ((uVar9 & 1) != 0) goto code_r0x011bd9c0;
  }
  *param_1 = 0;
  return;
}

// ==== Aska::Yayoi::NativeHttpRequestProcessor::FlushRequests(bool*)
// vaddr 0x259eba4 | ghidra 0x269eba4 | size 1244 | symbol _ZN4Aska5Yayoi26NativeHttpRequestProcessor13FlushRequestsEPb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi26NativeHttpRequestProcessor13FlushRequestsEPb
               (undefined8 *param_1,long param_2,undefined8 param_3)

{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  long lVar4;
  uint *puVar5;
  uint uVar6;
  uint uVar7;
  char cVar8;
  bool bVar9;
  bool bVar10;
  ulong uVar11;
  undefined8 uVar12;
  int iVar13;
  long lVar14;
  long lVar15;
  
  piVar1 = (int *)(param_2 + 0x870);
  iVar13 = 0;
code_r0x0269ebd4:
  do {
    if (*piVar1 == -1) goto code_r0x0269ebe0;
    ClearExclusiveLocal();
    bVar10 = iVar13 < 0x1ff;
    iVar13 = iVar13 + 1;
  } while (bVar10);
  piVar2 = (int *)(param_2 + 0x874);
  do {
    cVar8 = '\x01';
    bVar10 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar10) {
      *piVar2 = *piVar2 + 1;
      cVar8 = ExclusiveMonitorsStatus();
    }
  } while (cVar8 != '\0');
  do {
    if (*piVar1 != -1) {
      ClearExclusiveLocal();
      do {
        uVar11 = Aska::Semaphore::IsReady() const(param_2 + 0x8b0);
        if ((uVar11 & 1) == 0) {
          do {
            cVar8 = '\x01';
            bVar10 = (bool)ExclusiveMonitorPass(piVar2,0x10);
            if (bVar10) {
              *piVar2 = *piVar2 + -1;
              cVar8 = ExclusiveMonitorsStatus();
            }
          } while (cVar8 != '\0');
          Aska::Thread::Sleep(unsigned int)(1);
        }
        else {
          Aska::Semaphore::Wait() const(param_2 + 0x8b0);
        }
        do {
          cVar8 = '\x01';
          bVar10 = (bool)ExclusiveMonitorPass(piVar2,0x10);
          if (bVar10) {
            *piVar2 = *piVar2 + 1;
            cVar8 = ExclusiveMonitorsStatus();
          }
        } while (cVar8 != '\0');
        while (*piVar1 == -1) {
          cVar8 = '\x01';
          bVar10 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar10) {
            *piVar1 = 0;
            cVar8 = ExclusiveMonitorsStatus();
          }
          if (cVar8 == '\0') goto code_r0x0269ec8c;
        }
        ClearExclusiveLocal();
      } while( true );
    }
    cVar8 = '\x01';
    bVar10 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar10) {
      *piVar1 = 0;
      cVar8 = ExclusiveMonitorsStatus();
    }
  } while (cVar8 != '\0');
code_r0x0269ec8c:
  do {
    cVar8 = '\x01';
    bVar10 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar10) {
      *piVar2 = *piVar2 + -1;
      cVar8 = ExclusiveMonitorsStatus();
    }
  } while (cVar8 != '\0');
code_r0x0269ec9c:
  DataMemoryBarrier(2,3);
  uVar6 = 0;
  if (*(int *)(param_2 + 0xc) + 1U < 0x21) {
    uVar6 = *(int *)(param_2 + 0xc) + 1;
  }
  bVar10 = uVar6 != *(uint *)(param_2 + 8);
  if (bVar10) {
    *(uint *)(param_2 + 0xc) = uVar6;
  }
  lVar15 = *(long *)(param_2 + (ulong)uVar6 * 8 + 0x10);
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_2 + 0x870) = 0xffffffff;
  DataMemoryBarrier(2,3);
  piVar2 = (int *)(param_2 + 0x874);
  if (0x14 < *(int *)(param_2 + 0x874)) {
    do {
      cVar8 = '\x01';
      bVar9 = (bool)ExclusiveMonitorPass(piVar2,0x10);
      if (bVar9) {
        *piVar2 = *piVar2 + -1;
        cVar8 = ExclusiveMonitorsStatus();
      }
    } while (cVar8 != '\0');
    uVar11 = Aska::Semaphore::IsReady() const(param_2 + 0x8b0);
    if ((uVar11 & 1) != 0) {
      Aska::Semaphore::Signal() const(param_2 + 0x8b0);
    }
  }
  if (!bVar10) goto code_r0x0269f018;
  piVar3 = (int *)(param_2 + 0x82c);
  lVar4 = param_2 + 0x8b0;
  lVar14 = lVar15;
code_r0x0269ed38:
  if (*(char *)(param_2 + 0x8c8) != '\0') {
    uVar12 = 0xfffffffffffffc0f;
    goto code_r0x0269f058;
  }
  uVar11 = Aska::Yayoi::NativeHttpClient::_doRequest()(lVar14);
  if ((uVar11 & 1) != 0) {
    iVar13 = 0;
    do {
      while (*piVar1 != -1) {
        ClearExclusiveLocal();
        bVar10 = 0x1fe < iVar13;
        iVar13 = iVar13 + 1;
        if (bVar10) goto code_r0x0269ed78;
      }
      cVar8 = '\x01';
      bVar10 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar10) {
        *piVar1 = 0;
        cVar8 = ExclusiveMonitorsStatus();
      }
    } while (cVar8 != '\0');
    goto code_r0x0269ee70;
  }
  Aska::Yayoi::NativeHttpClient::~NativeHttpClient()(lVar14);
  uVar7 = (int)((ulong)(lVar14 - (param_2 + 0x128)) >> 3) * -0x49249249;
  uVar6 = uVar7 + 0x1f;
  if (-1 < (int)uVar7) {
    uVar6 = uVar7;
  }
  puVar5 = (uint *)(param_2 + (long)((int)uVar6 >> 5) * 4 + 0x120);
  do {
    cVar8 = '\x01';
    bVar10 = (bool)ExclusiveMonitorPass(puVar5,0x10);
    if (bVar10) {
      *puVar5 = *puVar5 & ~(1 << (ulong)(uVar7 & 0x1f));
      cVar8 = ExclusiveMonitorsStatus();
    }
  } while (cVar8 != '\0');
  do {
    cVar8 = '\x01';
    bVar10 = (bool)ExclusiveMonitorPass(piVar3,0x10);
    if (bVar10) {
      *piVar3 = *piVar3 + -1;
      cVar8 = ExclusiveMonitorsStatus();
    }
  } while (cVar8 != '\0');
  DataMemoryBarrier(2,3);
  goto code_r0x0269eee0;
code_r0x0269ebe0:
  cVar8 = '\x01';
  bVar10 = (bool)ExclusiveMonitorPass(piVar1,0x10);
  if (bVar10) {
    *piVar1 = 0;
    cVar8 = ExclusiveMonitorsStatus();
  }
  if (cVar8 == '\0') goto code_r0x0269ec9c;
  goto code_r0x0269ebd4;
code_r0x0269ed78:
  do {
    cVar8 = '\x01';
    bVar10 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar10) {
      *piVar2 = *piVar2 + 1;
      cVar8 = ExclusiveMonitorsStatus();
    }
  } while (cVar8 != '\0');
  do {
    if (*piVar1 != -1) {
      do {
        ClearExclusiveLocal();
        uVar11 = Aska::Semaphore::IsReady() const(lVar4);
        if ((uVar11 & 1) == 0) {
          do {
            cVar8 = '\x01';
            bVar10 = (bool)ExclusiveMonitorPass(piVar2,0x10);
            if (bVar10) {
              *piVar2 = *piVar2 + -1;
              cVar8 = ExclusiveMonitorsStatus();
            }
          } while (cVar8 != '\0');
          Aska::Thread::Sleep(unsigned int)(1);
        }
        else {
          Aska::Semaphore::Wait() const(lVar4);
        }
        do {
          cVar8 = '\x01';
          bVar10 = (bool)ExclusiveMonitorPass(piVar2,0x10);
          if (bVar10) {
            *piVar2 = *piVar2 + 1;
            cVar8 = ExclusiveMonitorsStatus();
          }
        } while (cVar8 != '\0');
        while (*piVar1 == -1) {
          cVar8 = '\x01';
          bVar10 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar10) {
            *piVar1 = 0;
            cVar8 = ExclusiveMonitorsStatus();
          }
          if (cVar8 == '\0') goto code_r0x0269ee60;
        }
      } while( true );
    }
    cVar8 = '\x01';
    bVar10 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar10) {
      *piVar1 = 0;
      cVar8 = ExclusiveMonitorsStatus();
    }
  } while (cVar8 != '\0');
code_r0x0269ee60:
  do {
    cVar8 = '\x01';
    bVar10 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar10) {
      *piVar2 = *piVar2 + -1;
      cVar8 = ExclusiveMonitorsStatus();
    }
  } while (cVar8 != '\0');
code_r0x0269ee70:
  DataMemoryBarrier(2,3);
  uVar6 = *(uint *)(param_2 + 8);
  if (*(uint *)(param_2 + 0xc) != uVar6) {
    iVar13 = 0;
    if (uVar6 + 1 < 0x21) {
      iVar13 = uVar6 + 1;
    }
    *(long *)(param_2 + (ulong)uVar6 * 8 + 0x10) = lVar14;
    *(int *)(param_2 + 8) = iVar13;
  }
  DataMemoryBarrier(2,3);
  *piVar1 = -1;
  DataMemoryBarrier(2,3);
  if (*piVar2 < 0x15) {
code_r0x0269eee0:
    iVar13 = 0;
  }
  else {
    do {
      cVar8 = '\x01';
      bVar10 = (bool)ExclusiveMonitorPass(piVar2,0x10);
      if (bVar10) {
        *piVar2 = *piVar2 + -1;
        cVar8 = ExclusiveMonitorsStatus();
      }
    } while (cVar8 != '\0');
    uVar11 = Aska::Semaphore::IsReady() const(lVar4);
    if ((uVar11 & 1) == 0) goto code_r0x0269eee0;
    Aska::Semaphore::Signal() const(lVar4);
    iVar13 = 0;
  }
  do {
    while (*piVar1 != -1) {
      ClearExclusiveLocal();
      bVar10 = 0x1fe < iVar13;
      iVar13 = iVar13 + 1;
      if (bVar10) goto code_r0x0269ef0c;
    }
    cVar8 = '\x01';
    bVar10 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar10) {
      *piVar1 = 0;
      cVar8 = ExclusiveMonitorsStatus();
    }
  } while (cVar8 != '\0');
code_r0x0269ef9c:
  DataMemoryBarrier(2,3);
  uVar6 = 0;
  if (*(int *)(param_2 + 0xc) + 1U < 0x21) {
    uVar6 = *(int *)(param_2 + 0xc) + 1;
  }
  bVar10 = uVar6 != *(uint *)(param_2 + 8);
  if (bVar10) {
    *(uint *)(param_2 + 0xc) = uVar6;
  }
  lVar14 = *(long *)(param_2 + (ulong)uVar6 * 8 + 0x10);
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_2 + 0x870) = 0xffffffff;
  DataMemoryBarrier(2,3);
  if (0x14 < *(int *)(param_2 + 0x874)) {
    do {
      cVar8 = '\x01';
      bVar9 = (bool)ExclusiveMonitorPass(piVar2,0x10);
      if (bVar9) {
        *piVar2 = *piVar2 + -1;
        cVar8 = ExclusiveMonitorsStatus();
      }
    } while (cVar8 != '\0');
    uVar11 = Aska::Semaphore::IsReady() const(lVar4);
    if ((uVar11 & 1) != 0) {
      Aska::Semaphore::Signal() const(lVar4);
    }
  }
  if ((!bVar10) || (lVar14 == lVar15)) {
code_r0x0269f018:
    uVar12 = 0;
    iVar13 = 0x20;
    if (*(uint *)(param_2 + 0xc) < *(uint *)(param_2 + 8)) {
      iVar13 = -1;
    }
    *(bool *)param_3 = 0 < (*(int *)(param_2 + 8) + iVar13) - *(int *)(param_2 + 0xc);
code_r0x0269f058:
    *param_1 = uVar12;
    return;
  }
  goto code_r0x0269ed38;
code_r0x0269ef0c:
  do {
    cVar8 = '\x01';
    bVar10 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar10) {
      *piVar2 = *piVar2 + 1;
      cVar8 = ExclusiveMonitorsStatus();
    }
  } while (cVar8 != '\0');
  do {
    if (*piVar1 != -1) {
      do {
        ClearExclusiveLocal();
        uVar11 = Aska::Semaphore::IsReady() const(lVar4);
        if ((uVar11 & 1) == 0) {
          do {
            cVar8 = '\x01';
            bVar10 = (bool)ExclusiveMonitorPass(piVar2,0x10);
            if (bVar10) {
              *piVar2 = *piVar2 + -1;
              cVar8 = ExclusiveMonitorsStatus();
            }
          } while (cVar8 != '\0');
          Aska::Thread::Sleep(unsigned int)(1);
        }
        else {
          Aska::Semaphore::Wait() const(lVar4);
        }
        do {
          cVar8 = '\x01';
          bVar10 = (bool)ExclusiveMonitorPass(piVar2,0x10);
          if (bVar10) {
            *piVar2 = *piVar2 + 1;
            cVar8 = ExclusiveMonitorsStatus();
          }
        } while (cVar8 != '\0');
        while (*piVar1 == -1) {
          cVar8 = '\x01';
          bVar10 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar10) {
            *piVar1 = 0;
            cVar8 = ExclusiveMonitorsStatus();
          }
          if (cVar8 == '\0') goto code_r0x0269ef8c;
        }
      } while( true );
    }
    cVar8 = '\x01';
    bVar10 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar10) {
      *piVar1 = 0;
      cVar8 = ExclusiveMonitorsStatus();
    }
  } while (cVar8 != '\0');
code_r0x0269ef8c:
  do {
    cVar8 = '\x01';
    bVar10 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar10) {
      *piVar2 = *piVar2 + -1;
      cVar8 = ExclusiveMonitorsStatus();
    }
  } while (cVar8 != '\0');
  goto code_r0x0269ef9c;
}

// ==== Aska::Yayoi::NativeHttpRequestProcessor::Initialize()
// vaddr 0x259f080 | ghidra 0x269f080 | size 8 | symbol _ZN4Aska5Yayoi26NativeHttpRequestProcessor10InitializeEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi26NativeHttpRequestProcessor10InitializeEv(undefined8 *param_1)

{
  *param_1 = 0;
  return;
}

// ==== Aska::Yayoi::NativeHttpClient::NativeHttpClient()
// vaddr 0x25a4e84 | ghidra 0x26a4e84 | size 20 | symbol _ZN4Aska5Yayoi16NativeHttpClientC1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi16NativeHttpClientC2Ev(undefined8 *param_1)

{
  param_1[5] = 0;
  param_1[6] = 0;
  param_1[1] = 0;
  *param_1 = 0;
  param_1[3] = 0;
  param_1[2] = 0;
  param_1[4] = 0;
  return;
}

// ==== Aska::Yayoi::NativeHttpClient::~NativeHttpClient()
// vaddr 0x25a4e98 | ghidra 0x26a4e98 | size 168 | symbol _ZN4Aska5Yayoi16NativeHttpClientD2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi16NativeHttpClientD1Ev(long param_1)

{
  int iVar1;
  char cVar2;
  bool bVar3;
  int *piVar4;
  long lVar5;
  
  piVar4 = *(int **)(param_1 + 0x30);
  if (piVar4 == (int *)0x0) {
code_r0x026a4ec0:
    lVar5 = *(long *)(param_1 + 0x28);
    if (lVar5 != 0) {
      Aska::Yayoi::URI::DeleteBuffer()(lVar5);
      operator delete(void*)(lVar5);
    }
    if (*(long *)(param_1 + 0x30) != 0) {
      Aska::TSharedPointerCode::DeleteCounter(int*)();
    }
  }
  else {
    do {
      iVar1 = *piVar4;
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar4,0x10);
      if (bVar3) {
        *piVar4 = iVar1 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    if (iVar1 + -1 == 0) goto code_r0x026a4ec0;
  }
  piVar4 = *(int **)(param_1 + 0x20);
  *(undefined8 *)(param_1 + 0x28) = 0;
  *(undefined8 *)(param_1 + 0x30) = 0;
  if (piVar4 != (int *)0x0) {
    do {
      iVar1 = *piVar4;
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar4,0x10);
      if (bVar3) {
        *piVar4 = iVar1 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    if (iVar1 + -1 != 0) goto code_r0x026a4f30;
  }
  lVar5 = *(long *)(param_1 + 0x18);
  if (lVar5 != 0) {
    Aska::Yayoi::SSLProtocoledData::FreeInnerData()(lVar5 + 0x198);
    Aska::Yayoi::HttpProtocoledData::~HttpProtocoledData()(lVar5);
    operator delete(void*)(lVar5);
  }
  if (*(long *)(param_1 + 0x20) != 0) {
    Aska::TSharedPointerCode::DeleteCounter(int*)();
  }
code_r0x026a4f30:
  *(undefined8 *)(param_1 + 0x18) = 0;
  *(undefined8 *)(param_1 + 0x20) = 0;
  return;
}

// ==== Aska::Yayoi::NativeHttpClient::_doRequest()
// vaddr 0x25a4f40 | ghidra 0x26a4f40 | size 2968 | symbol _ZN4Aska5Yayoi16NativeHttpClient10_doRequestEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska5Yayoi16NativeHttpClient10_doRequestEv(long *param_1)

{
  int iVar1;
  char cVar2;
  bool bVar3;
  byte bVar4;
  undefined *puVar5;
  undefined2 uVar6;
  long lVar7;
  long lVar8;
  undefined8 uVar9;
  long *plVar10;
  long *plVar11;
  ulong uVar12;
  code *pcVar13;
  long lVar14;
  int *piVar15;
  int **ppiVar16;
  long lVar17;
  undefined8 uVar18;
  long lVar19;
  undefined8 uVar20;
  long lStack_168;
  int *piStack_160;
  undefined1 auStack_158 [8];
  long lStack_150;
  int *piStack_148;
  undefined8 uStack_140;
  long lStack_138;
  int *piStack_130;
  undefined8 uStack_128;
  long lStack_120;
  int *piStack_118;
  undefined8 uStack_110;
  undefined1 auStack_108 [8];
  long lStack_100;
  int *piStack_f8;
  long lStack_f0;
  int *piStack_e8;
  undefined8 uStack_e0;
  long lStack_d8;
  int *piStack_d0;
  undefined8 uStack_c8;
  long lStack_c0;
  int *piStack_b8;
  long lStack_b0;
  long lStack_a8;
  int *piStack_a0;
  undefined8 uStack_98;
  long lStack_90;
  int *piStack_88;
  undefined8 uStack_80;
  undefined1 auStack_78 [8];
  long *plStack_70;
  int iStack_68;
  undefined4 uStack_64;
  
  Aska::AndroidUtil::ScopeJniCall::ScopeJniCall(_JNIEnv*&)(auStack_78,&plStack_70);
  lVar17 = param_1[3];
  lVar14 = *(long *)(param_1[5] + 0x50);
  if (*(int *)(lVar17 + 0x7c) == 3) {
    lVar7 = Aska::Yayoi::HttpProtocoledData::MakeParamString(char*, unsigned long)(lVar17,0,0);
    if (lVar7 == 0) {
      lVar19 = 0;
      uVar18 = 0;
    }
    else {
      lVar19 = operator new[](unsigned long, std::nothrow_t const&)(lVar7,PTR__ZSt7nothrow_02cb9a80);
      Aska::Yayoi::HttpProtocoledData::MakeParamString(char*, unsigned long)(lVar17,lVar19,lVar7);
      uVar18 = (**(code **)(*plStack_70 + 0x538))(plStack_70,lVar19);
    }
    bVar4 = 0;
    uVar20 = 1;
  }
  else if (*(int *)(lVar17 + 0x7c) == 1) {
    lVar7 = Aska::Yayoi::HttpProtocoledData::MakeParamString(char*, unsigned long)(lVar17,0,0);
    if (lVar7 == 0) {
      bVar4 = 0;
      uVar20 = 0;
      uVar18 = 0;
      lVar19 = 0;
    }
    else {
      lVar19 = *(long *)(param_1[5] + 8);
      lVar8 = operator new[](unsigned long, std::nothrow_t const&)(lVar19 + lVar7,PTR__ZSt7nothrow_02cb9a80);
      memcpy(lVar8,lVar14,lVar19);
      *(undefined1 *)(lVar8 + lVar19 + -1) = 0x3f;
      Aska::Yayoi::HttpProtocoledData::MakeParamString(char*, unsigned long)(lVar17,lVar8 + lVar19,lVar7);
      uVar20 = 0;
      lVar19 = 0;
      uVar18 = 0;
      bVar4 = 1;
      lVar14 = lVar8;
    }
  }
  else {
    bVar4 = 0;
    uVar20 = 0;
    lVar19 = 0;
    uVar18 = 0;
  }
  if (*(long *)(*param_1 + 8) != 0) {
    uVar9 = (**(code **)(*plStack_70 + 0x538))();
    Aska::AndroidUtil::CallMethod(_JNIEnv*, jvalue*, _jobject*, char const*, char const*, ...)(&lStack_c0,plStack_70,&iStack_68,
                    *(undefined8 *)
                     (*(long *)(*(long *)PTR__ZN4Aska6Global13m_pAndroidAppE_02cc2688 + 0x18) + 0x18
                     ),&UNK_02a31b80/*"SetHttpUserAgent"*/,&UNK_029702cf/*"(Ljava/lang/String;)Ljava/lang/Boolean;"*/,uVar9);
    (**(code **)(*plStack_70 + 0xb8))(plStack_70,uVar9);
  }
  uVar9 = (**(code **)(*plStack_70 + 0x538))(plStack_70,lVar14);
  if (*(int *)(param_1[5] + 0x70) == 0) {
    uVar6 = 0;
  }
  else {
    uVar6 = Aska::Yayoi::IPAddress::GetPort() const((int *)(param_1[5] + 0x70));
  }
  puVar5 = PTR__ZN4Aska6Global13m_pAndroidAppE_02cc2688;
  Aska::AndroidUtil::CallMethod(_JNIEnv*, jvalue*, _jobject*, char const*, char const*, ...)(&lStack_c0,plStack_70,&iStack_68,
                  *(undefined8 *)
                   (*(long *)(*(long *)PTR__ZN4Aska6Global13m_pAndroidAppE_02cc2688 + 0x18) + 0x18),
                  &UNK_02a31bf7/*"HttpRequest"*/,&UNK_02a31b91/*"(Ljava/lang/String;ILjava/lang/String;Z)I"*/,uVar9,uVar6,uVar18,uVar20);
  if ((lVar14 != 0) && ((bool)(bVar4 & lVar14 != 0))) {
    operator delete[](void*)(lVar14);
  }
  if (lVar19 != 0) {
    operator delete[](void*)(lVar19);
    (**(code **)(*plStack_70 + 0xb8))(plStack_70,uVar18);
  }
  (**(code **)(*plStack_70 + 0xb8))(plStack_70,uVar9);
  if (iStack_68 < 1) {
    piStack_88 = (int *)0x0;
    uStack_80 = 0xffffffffffffffff;
    lStack_90 = 0;
    (**(code **)(*(long *)param_1[2] + 0x50))
              ((long *)param_1[2],&uStack_80,&UNK_02a5041c/*"unexpected error"*/,&lStack_90);
    lVar14 = lStack_90;
    if (piStack_88 == (int *)0x0) {
code_r0x026a5254:
      if (lStack_90 != 0) {
        Aska::Yayoi::SSLProtocoledData::FreeInnerData()(lStack_90 + 0x198);
        Aska::Yayoi::HttpProtocoledData::~HttpProtocoledData()(lVar14);
        operator delete(void*)(lVar14);
      }
      if (piStack_88 != (int *)0x0) {
        Aska::TSharedPointerCode::DeleteCounter(int*)();
      }
    }
    else {
      do {
        iVar1 = *piStack_88;
        cVar2 = '\x01';
        bVar3 = (bool)ExclusiveMonitorPass(piStack_88,0x10);
        if (bVar3) {
          *piStack_88 = iVar1 + -1;
          cVar2 = ExclusiveMonitorsStatus();
        }
      } while (cVar2 != '\0');
      if (iVar1 + -1 == 0) goto code_r0x026a5254;
    }
    lStack_90 = 0;
    piStack_88 = (int *)0x0;
    piStack_a0 = (int *)0x0;
    uStack_98 = 0xffffffffffffffff;
    lStack_a8 = 0;
    (**(code **)(*(long *)param_1[2] + 0x48))
              ((long *)param_1[2],&uStack_98,&lStack_a8,&UNK_02a5041c/*"unexpected error"*/);
    lVar14 = lStack_a8;
    if (piStack_a0 == (int *)0x0) {
code_r0x026a52cc:
      if (lStack_a8 != 0) {
        Aska::Yayoi::SSLProtocoledData::FreeInnerData()(lStack_a8 + 0x198);
        Aska::Yayoi::HttpProtocoledData::~HttpProtocoledData()(lVar14);
        operator delete(void*)(lVar14);
      }
      if (piStack_a0 != (int *)0x0) {
        Aska::TSharedPointerCode::DeleteCounter(int*)();
      }
    }
    else {
      do {
        iVar1 = *piStack_a0;
        cVar2 = '\x01';
        bVar3 = (bool)ExclusiveMonitorPass(piStack_a0,0x10);
        if (bVar3) {
          *piStack_a0 = iVar1 + -1;
          cVar2 = ExclusiveMonitorsStatus();
        }
      } while (cVar2 != '\0');
      if (iVar1 + -1 == 0) goto code_r0x026a52cc;
    }
    lStack_a8 = 0;
    piStack_a0 = (int *)0x0;
    goto code_r0x026a5798;
  }
  lStack_b0 = 0;
  Aska::Yayoi::TProtocolSuite<Aska::Yayoi::HttpProtocol, Aska::Yayoi::SSLProtocol, Aska::Yayoi::NoProtocol<2> >::AllocateDataSuite()(&lStack_c0,param_1[1]);
  lVar14 = lStack_c0;
  if (lStack_c0 == 0) {
    piVar15 = (int *)0x0;
code_r0x026a5304:
    if (piStack_b8 == (int *)0x0) goto code_r0x026a532c;
    do {
      iVar1 = *piStack_b8;
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piStack_b8,0x10);
      if (bVar3) {
        *piStack_b8 = iVar1 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    if (iVar1 + -1 == 0) goto code_r0x026a532c;
  }
  else {
    lStack_b0 = lStack_c0;
    piVar15 = piStack_b8;
    if (piStack_b8 != (int *)0x0) {
      do {
        cVar2 = '\x01';
        bVar3 = (bool)ExclusiveMonitorPass(piStack_b8,0x10);
        if (bVar3) {
          *piStack_b8 = *piStack_b8 + 1;
          cVar2 = ExclusiveMonitorsStatus();
        }
      } while (cVar2 != '\0');
      goto code_r0x026a5304;
    }
code_r0x026a532c:
    if (lStack_c0 != 0) {
      Aska::Yayoi::SSLProtocoledData::FreeInnerData()(lStack_c0 + 0x198);
      Aska::Yayoi::HttpProtocoledData::~HttpProtocoledData()(lVar14);
      operator delete(void*)(lVar14);
    }
    if (piStack_b8 != (int *)0x0) {
      Aska::TSharedPointerCode::DeleteCounter(int*)();
    }
  }
  lVar14 = lStack_b0;
  piStack_b8 = (int *)0x0;
  Aska::AndroidUtil::CallMethod(_JNIEnv*, jvalue*, _jobject*, char const*, char const*, ...)(&lStack_c0,plStack_70,&iStack_68,
                  *(undefined8 *)(*(long *)(*(long *)puVar5 + 0x18) + 0x18),&UNK_02a31bbb/*"GetHttpHeader"*/,
                  &UNK_0295bd8b/*"()Ljava/lang/String;"*/);
  uVar18 = CONCAT44(uStack_64,iStack_68);
  lVar17 = Aska::AndroidUtil::jstring2string(_JNIEnv*, _jstring*, char*, unsigned long)(plStack_70,uVar18,0,0);
  if (lVar17 < 0) {
    piStack_d0 = (int *)0x0;
    uStack_c8 = 0xffffffffffffffff;
    lStack_d8 = 0;
    (**(code **)(*(long *)param_1[2] + 0x50))
              ((long *)param_1[2],&uStack_c8,&UNK_02a31bc9/*"response header is nothing"*/,&lStack_d8);
    lVar14 = lStack_d8;
    if (piStack_d0 == (int *)0x0) {
code_r0x026a5420:
      if (lStack_d8 != 0) {
        Aska::Yayoi::SSLProtocoledData::FreeInnerData()(lStack_d8 + 0x198);
        Aska::Yayoi::HttpProtocoledData::~HttpProtocoledData()(lVar14);
        operator delete(void*)(lVar14);
      }
      if (piStack_d0 != (int *)0x0) {
        Aska::TSharedPointerCode::DeleteCounter(int*)();
      }
    }
    else {
      do {
        iVar1 = *piStack_d0;
        cVar2 = '\x01';
        bVar3 = (bool)ExclusiveMonitorPass(piStack_d0,0x10);
        if (bVar3) {
          *piStack_d0 = iVar1 + -1;
          cVar2 = ExclusiveMonitorsStatus();
        }
      } while (cVar2 != '\0');
      if (iVar1 + -1 == 0) goto code_r0x026a5420;
    }
    lStack_d8 = 0;
    piStack_d0 = (int *)0x0;
    piStack_e8 = (int *)0x0;
    uStack_e0 = 0xffffffffffffffff;
    lStack_f0 = 0;
    (**(code **)(*(long *)param_1[2] + 0x48))
              ((long *)param_1[2],&uStack_e0,&lStack_f0,&UNK_02a31bc9/*"response header is nothing"*/);
    lVar14 = lStack_f0;
    if (piStack_e8 == (int *)0x0) {
code_r0x026a5498:
      if (lStack_f0 != 0) {
        Aska::Yayoi::SSLProtocoledData::FreeInnerData()(lStack_f0 + 0x198);
        Aska::Yayoi::HttpProtocoledData::~HttpProtocoledData()(lVar14);
        operator delete(void*)(lVar14);
      }
      if (piStack_e8 != (int *)0x0) {
        Aska::TSharedPointerCode::DeleteCounter(int*)();
      }
    }
    else {
      do {
        iVar1 = *piStack_e8;
        cVar2 = '\x01';
        bVar3 = (bool)ExclusiveMonitorPass(piStack_e8,0x10);
        if (bVar3) {
          *piStack_e8 = iVar1 + -1;
          cVar2 = ExclusiveMonitorsStatus();
        }
      } while (cVar2 != '\0');
      if (iVar1 + -1 == 0) goto code_r0x026a5498;
    }
    lStack_f0 = 0;
    piStack_e8 = (int *)0x0;
    lVar17 = lStack_b0;
  }
  else {
    lVar7 = lVar17 + 1;
    if (lVar7 == 0) {
      lVar19 = 0;
    }
    else {
      lVar19 = **(long **)PTR__ZN4Aska6Global19m_pNetworkAllocatorE_02cbc200;
      if (lVar19 == 0) {
        lVar19 = Aska::Global::GetAvailableMemoryManager()();
      }
      lVar19 = Aska::MemoryManager::Malloc(unsigned long)(lVar19,lVar7);
    }
    Aska::AndroidUtil::jstring2string(_JNIEnv*, _jstring*, char*, unsigned long)(plStack_70,uVar18,lVar19,lVar7);
    lStack_100 = param_1[5];
    lVar7 = *param_1;
    piStack_f8 = (int *)param_1[6];
    if (piStack_f8 != (int *)0x0) {
      do {
        cVar2 = '\x01';
        bVar3 = (bool)ExclusiveMonitorPass(piStack_f8,0x10);
        if (bVar3) {
          *piStack_f8 = *piStack_f8 + 1;
          cVar2 = ExclusiveMonitorsStatus();
        }
      } while (cVar2 != '\0');
    }
    Aska::Yayoi::HttpProtocol::ParseHeader(signed char const*, unsigned long, Aska::Yayoi::HttpProtocoledData*, Aska::TSharedPointer<Aska::Yayoi::URI>)(lVar7,lVar19,lVar17,lVar14,&lStack_100);
    lVar17 = lStack_100;
    if (piStack_f8 == (int *)0x0) {
code_r0x026a5540:
      if (lStack_100 != 0) {
        Aska::Yayoi::URI::DeleteBuffer()(lStack_100);
        operator delete(void*)(lVar17);
      }
      if (piStack_f8 != (int *)0x0) {
        Aska::TSharedPointerCode::DeleteCounter(int*)();
      }
    }
    else {
      do {
        iVar1 = *piStack_f8;
        cVar2 = '\x01';
        bVar3 = (bool)ExclusiveMonitorPass(piStack_f8,0x10);
        if (bVar3) {
          *piStack_f8 = iVar1 + -1;
          cVar2 = ExclusiveMonitorsStatus();
        }
      } while (cVar2 != '\0');
      if (iVar1 + -1 == 0) goto code_r0x026a5540;
    }
    lStack_100 = 0;
    piStack_f8 = (int *)0x0;
    if (lVar19 != 0) {
      operator delete[](void*)(lVar19);
    }
    Aska::AndroidUtil::CallMethod(_JNIEnv*, jvalue*, _jobject*, char const*, char const*, ...)(&lStack_c0,plStack_70,&iStack_68,
                    *(undefined8 *)(*(long *)(*(long *)puVar5 + 0x18) + 0x18),&UNK_02a31be4/*"GetStatusCode"*/,
                    &UNK_0295bd40/*"()I"*/);
    lVar17 = lStack_b0;
    if (-1 < lStack_c0) {
      *(int *)(lVar14 + 0x8c) = iStack_68;
      if (*(char *)(lVar14 + 0x133) != '\0') {
        *(undefined1 *)(lVar14 + 0x133) = 0;
      }
      Aska::AppNetworkCommonSettingProxy::AppNetworkCommonSettingProxy()(&lStack_c0);
      uVar18 = Aska::AppNetworkCommonSettingProxy::GetTcpReceiveSize() const(&lStack_c0);
      uVar18 = (**(code **)(*plStack_70 + 0x580))(plStack_70,uVar18);
      if (*(char *)(*param_1 + 0x41) == '\0') {
        plVar10 = param_1 + 2;
        if (piVar15 == (int *)0x0) {
          do {
            Aska::AndroidUtil::CallMethod(_JNIEnv*, jvalue*, _jobject*, char const*, char const*, ...)(auStack_108,plStack_70,&iStack_68,
                            *(undefined8 *)(*(long *)(*(long *)puVar5 + 0x18) + 0x18),&UNK_02a31c19/*"ReadHttpResponse"*/,
                            &UNK_02a31c2a/*"([B)I"*/,uVar18);
            lVar17 = (long)iStack_68;
            if (iStack_68 < 0) goto code_r0x026a5a14;
            auStack_108[0] = 0;
            lVar7 = (**(code **)(*plStack_70 + 0x6f0))(plStack_70,uVar18,auStack_108);
            if (lVar7 == 0) goto code_r0x026a5aa4;
            lVar17 = Aska::Yayoi::HttpProtocol::ParseMessageBody(signed char const*, unsigned long, Aska::Yayoi::HttpProtocoledData*)(*param_1,lVar7,lVar17,lVar14);
            if (lVar17 == 0) goto code_r0x026a5aac;
            piStack_118 = (int *)0x0;
            uStack_110 = 0;
            lStack_120 = lStack_b0;
            uVar12 = (**(code **)(*(long *)*plVar10 + 0x30))
                               ((long *)*plVar10,&uStack_110,&lStack_120,0);
            lVar17 = lStack_120;
            if (piStack_118 == (int *)0x0) {
code_r0x026a59b4:
              if (lStack_120 != 0) {
                Aska::Yayoi::SSLProtocoledData::FreeInnerData()(lStack_120 + 0x198);
                Aska::Yayoi::HttpProtocoledData::~HttpProtocoledData()(lVar17);
                operator delete(void*)(lVar17);
              }
              if (piStack_118 != (int *)0x0) {
                Aska::TSharedPointerCode::DeleteCounter(int*)();
              }
            }
            else {
              do {
                iVar1 = *piStack_118;
                cVar2 = '\x01';
                bVar3 = (bool)ExclusiveMonitorPass(piStack_118,0x10);
                if (bVar3) {
                  *piStack_118 = iVar1 + -1;
                  cVar2 = ExclusiveMonitorsStatus();
                }
              } while (cVar2 != '\0');
              if (iVar1 + -1 == 0) goto code_r0x026a59b4;
            }
            lStack_120 = 0;
            piStack_118 = (int *)0x0;
            (**(code **)(*plStack_70 + 0x6f8))(plStack_70,uVar18,lVar7,auStack_108[0]);
            if ((uVar12 & 1) == 0) goto code_r0x026a5624;
          } while (*(char *)(*param_1 + 0x41) == '\0');
        }
        else {
          do {
            Aska::AndroidUtil::CallMethod(_JNIEnv*, jvalue*, _jobject*, char const*, char const*, ...)(auStack_108,plStack_70,&iStack_68,
                            *(undefined8 *)(*(long *)(*(long *)puVar5 + 0x18) + 0x18),&UNK_02a31c19/*"ReadHttpResponse"*/,
                            &UNK_02a31c2a/*"([B)I"*/,uVar18);
            lVar17 = (long)iStack_68;
            if (iStack_68 < 0) goto code_r0x026a5a14;
            auStack_108[0] = 0;
            lVar7 = (**(code **)(*plStack_70 + 0x6f0))(plStack_70,uVar18,auStack_108);
            if (lVar7 == 0) goto code_r0x026a5aa4;
            lVar17 = Aska::Yayoi::HttpProtocol::ParseMessageBody(signed char const*, unsigned long, Aska::Yayoi::HttpProtocoledData*)(*param_1,lVar7,lVar17,lVar14);
            if (lVar17 == 0) goto code_r0x026a5aac;
            plVar11 = (long *)*plVar10;
            pcVar13 = *(code **)(*plVar11 + 0x30);
            uStack_110 = 0;
            lStack_120 = lStack_b0;
            do {
              cVar2 = '\x01';
              bVar3 = (bool)ExclusiveMonitorPass(piVar15,0x10);
              if (bVar3) {
                *piVar15 = *piVar15 + 1;
                cVar2 = ExclusiveMonitorsStatus();
              }
            } while (cVar2 != '\0');
            piStack_118 = piVar15;
            uVar12 = (*pcVar13)(plVar11,&uStack_110,&lStack_120,0);
            lVar17 = lStack_120;
            if (piStack_118 == (int *)0x0) {
code_r0x026a58a0:
              if (lStack_120 != 0) {
                Aska::Yayoi::SSLProtocoledData::FreeInnerData()(lStack_120 + 0x198);
                Aska::Yayoi::HttpProtocoledData::~HttpProtocoledData()(lVar17);
                operator delete(void*)(lVar17);
              }
              if (piStack_118 != (int *)0x0) {
                Aska::TSharedPointerCode::DeleteCounter(int*)();
              }
            }
            else {
              do {
                iVar1 = *piStack_118;
                cVar2 = '\x01';
                bVar3 = (bool)ExclusiveMonitorPass(piStack_118,0x10);
                if (bVar3) {
                  *piStack_118 = iVar1 + -1;
                  cVar2 = ExclusiveMonitorsStatus();
                }
              } while (cVar2 != '\0');
              if (iVar1 + -1 == 0) goto code_r0x026a58a0;
            }
            lStack_120 = 0;
            piStack_118 = (int *)0x0;
            (**(code **)(*plStack_70 + 0x6f8))(plStack_70,uVar18,lVar7,auStack_108[0]);
            if ((uVar12 & 1) == 0) goto code_r0x026a5624;
          } while (*(char *)(*param_1 + 0x41) == '\0');
        }
      }
      Aska::AndroidUtil::CallMethod(_JNIEnv*, jvalue*, _jobject*, char const*, char const*, ...)(auStack_108,plStack_70,&iStack_68,
                      *(undefined8 *)(*(long *)(*(long *)puVar5 + 0x18) + 0x18),&UNK_02a31bf2/*"AbortHttpRequest"*/,
                      &UNK_02a31c03/*"()Ljava/lang/Boolean;"*/);
code_r0x026a5624:
      uStack_140 = 0xfffffffffffffc4c;
      goto code_r0x026a5628;
    }
  }
  goto joined_r0x026a5754;
code_r0x026a5a14:
  plVar10 = (long *)*plVar10;
  pcVar13 = *(code **)(*plVar10 + 0x28);
  lStack_138 = lStack_b0;
  ppiVar16 = &piStack_130;
  uStack_128 = 0;
  if (piVar15 != (int *)0x0) {
    do {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar15,0x10);
      if (bVar3) {
        *piVar15 = *piVar15 + 1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
  }
  piStack_130 = piVar15;
  (*pcVar13)(plVar10,&uStack_128,&lStack_138,0);
  lVar14 = lStack_138;
  if (piStack_130 == (int *)0x0) {
code_r0x026a5a74:
    if (lStack_138 != 0) {
      Aska::Yayoi::SSLProtocoledData::FreeInnerData()(lStack_138 + 0x198);
      Aska::Yayoi::HttpProtocoledData::~HttpProtocoledData()(lVar14);
      operator delete(void*)(lVar14);
    }
    if (piStack_130 == (int *)0x0) goto code_r0x026a5ad0;
    plVar10 = &lStack_138;
    goto code_r0x026a56b4;
  }
  do {
    iVar1 = *piStack_130;
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piStack_130,0x10);
    if (bVar3) {
      *piStack_130 = iVar1 + -1;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
  if (iVar1 + -1 == 0) goto code_r0x026a5a74;
code_r0x026a5ad0:
  plVar10 = &lStack_138;
  goto code_r0x026a56c0;
code_r0x026a5aa4:
  uStack_140 = 0xfffffffffffffc41;
  goto code_r0x026a5628;
code_r0x026a5aac:
  (**(code **)(*plStack_70 + 0x6f8))(plStack_70,uVar18,lVar7,auStack_108[0]);
  uStack_140 = 0xfffffffffffffc4d;
code_r0x026a5628:
  plVar10 = (long *)param_1[2];
  pcVar13 = *(code **)(*plVar10 + 0x50);
  ppiVar16 = &piStack_148;
  lStack_150 = lStack_b0;
  if (piVar15 != (int *)0x0) {
    do {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar15,0x10);
      if (bVar3) {
        *piVar15 = *piVar15 + 1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
  }
  piStack_148 = piVar15;
  (*pcVar13)(plVar10,&uStack_140,0,&lStack_150);
  lVar14 = lStack_150;
  if (piStack_148 == (int *)0x0) {
code_r0x026a5688:
    if (lStack_150 != 0) {
      Aska::Yayoi::SSLProtocoledData::FreeInnerData()(lStack_150 + 0x198);
      Aska::Yayoi::HttpProtocoledData::~HttpProtocoledData()(lVar14);
      operator delete(void*)(lVar14);
    }
    if (piStack_148 == (int *)0x0) goto code_r0x026a56bc;
    plVar10 = &lStack_150;
code_r0x026a56b4:
    Aska::TSharedPointerCode::DeleteCounter(int*)();
  }
  else {
    do {
      iVar1 = *piStack_148;
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piStack_148,0x10);
      if (bVar3) {
        *piStack_148 = iVar1 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    if (iVar1 + -1 == 0) goto code_r0x026a5688;
code_r0x026a56bc:
    plVar10 = &lStack_150;
  }
code_r0x026a56c0:
  *ppiVar16 = (int *)0x0;
  *plVar10 = 0;
  plVar10 = (long *)param_1[2];
  pcVar13 = *(code **)(*plVar10 + 0x48);
  lStack_168 = lStack_b0;
  if (piVar15 != (int *)0x0) {
    do {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar15,0x10);
      if (bVar3) {
        *piVar15 = *piVar15 + 1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
  }
  piStack_160 = piVar15;
  (*pcVar13)(plVar10,auStack_158,&lStack_168,0);
  lVar14 = lStack_168;
  if (piStack_160 == (int *)0x0) {
code_r0x026a571c:
    if (lStack_168 != 0) {
      Aska::Yayoi::SSLProtocoledData::FreeInnerData()(lStack_168 + 0x198);
      Aska::Yayoi::HttpProtocoledData::~HttpProtocoledData()(lVar14);
      operator delete(void*)(lVar14);
    }
    if (piStack_160 != (int *)0x0) {
      Aska::TSharedPointerCode::DeleteCounter(int*)();
    }
  }
  else {
    do {
      iVar1 = *piStack_160;
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piStack_160,0x10);
      if (bVar3) {
        *piStack_160 = iVar1 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    if (iVar1 + -1 == 0) goto code_r0x026a571c;
  }
  lStack_168 = 0;
  piStack_160 = (int *)0x0;
  Aska::AppNetworkCommonSettingProxy::~AppNetworkCommonSettingProxy()(&lStack_c0);
  lVar17 = lStack_b0;
joined_r0x026a5754:
  lStack_b0 = lVar17;
  if (piVar15 != (int *)0x0) {
    do {
      iVar1 = *piVar15;
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar15,0x10);
      if (bVar3) {
        *piVar15 = iVar1 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    if (iVar1 + -1 != 0) goto code_r0x026a5798;
  }
  if (lVar17 != 0) {
    Aska::Yayoi::SSLProtocoledData::FreeInnerData()(lVar17 + 0x198);
    Aska::Yayoi::HttpProtocoledData::~HttpProtocoledData()(lVar17);
    operator delete(void*)(lVar17);
  }
  if (piVar15 != (int *)0x0) {
    Aska::TSharedPointerCode::DeleteCounter(int*)(piVar15);
  }
code_r0x026a5798:
  Aska::AndroidUtil::ScopeJniCall::~ScopeJniCall()(auStack_78);
  return 0;
}
