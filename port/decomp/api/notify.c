// port/decomp/api/notify.c: Ghidra decompiles for the api subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-09 01:44 UTC: tools/decomp.sh '--into' 'api/notify' 'CApiNotify::CApiNotify' 'CApiNotify::OnProtocolError'

// ==== CApiNotify::CApiNotify(IApiCaller*)
// vaddr 0x13baafc | ghidra 0x14baafc | size 560 | symbol _ZN10CApiNotifyC2EP10IApiCaller | lib libSOA-3.7.0.so | 2026-10-09
void _ZN10CApiNotifyC1EP10IApiCaller(long *param_1,long param_2)

{
  undefined *puVar1;
  undefined *puVar2;
  long *plVar3;
  code *pcVar4;
  
  puVar2 = PTR__ZTV10CApiNotify_02cc4f40;
  param_1[6] = 0;
  puVar1 = PTR__ZTVN4Aska5Yayoi11THttpClientINS0_3TCPELi5EEE_02cc2e80 + 0x10;
  *param_1 = (long)(puVar2 + 0x10);
  param_1[8] = (long)puVar1;
  Aska::Yayoi::HttpProtocol::HttpProtocol()(param_1 + 9);
  *(undefined1 *)(param_1 + 0x12) = 0;
  param_1[0x13] =
       (long)(PTR__ZTVN4Aska6TQueueINS_5Yayoi11SSLProtocol11RecordLayerELi10EEE_02cbc400 + 0x10);
  *(undefined4 *)(param_1 + 0x14) = 1;
  *(undefined4 *)((long)param_1 + 0xa4) = 0;
  param_1[0x18] = 0;
  *(undefined1 *)(param_1 + 0x19) = 0;
  param_1[0x16] = 0;
  param_1[0x15] = 0;
  *(undefined1 *)(param_1 + 0x17) = 0;
  param_1[0x1d] = 0;
  *(undefined1 *)(param_1 + 0x1e) = 0;
  param_1[0x1b] = 0;
  param_1[0x1a] = 0;
  *(undefined1 *)(param_1 + 0x1c) = 0;
  param_1[0x22] = 0;
  *(undefined1 *)(param_1 + 0x23) = 0;
  *(undefined1 *)(param_1 + 0x21) = 0;
  param_1[0x1f] = 0;
  param_1[0x20] = 0;
  param_1[0x27] = 0;
  *(undefined1 *)(param_1 + 0x28) = 0;
  *(undefined1 *)(param_1 + 0x26) = 0;
  param_1[0x24] = 0;
  param_1[0x25] = 0;
  param_1[0x2c] = 0;
  *(undefined1 *)(param_1 + 0x2d) = 0;
  *(undefined1 *)(param_1 + 0x2b) = 0;
  param_1[0x29] = 0;
  param_1[0x2a] = 0;
  param_1[0x31] = 0;
  *(undefined1 *)(param_1 + 0x32) = 0;
  *(undefined1 *)(param_1 + 0x30) = 0;
  param_1[0x2e] = 0;
  param_1[0x2f] = 0;
  param_1[0x36] = 0;
  *(undefined1 *)(param_1 + 0x37) = 0;
  *(undefined1 *)(param_1 + 0x35) = 0;
  param_1[0x33] = 0;
  param_1[0x34] = 0;
  param_1[0x3b] = 0;
  *(undefined1 *)(param_1 + 0x3c) = 0;
  *(undefined1 *)(param_1 + 0x3a) = 0;
  param_1[0x38] = 0;
  param_1[0x39] = 0;
  param_1[0x40] = 0;
  *(undefined1 *)(param_1 + 0x41) = 0;
  *(undefined1 *)(param_1 + 0x3f) = 0;
  param_1[0x3d] = 0;
  param_1[0x3e] = 0;
  param_1[0x45] = 0;
  *(undefined1 *)(param_1 + 0x46) = 0;
  *(undefined1 *)(param_1 + 0x44) = 0;
  param_1[0x43] = 0;
  param_1[0x42] = 0;
  param_1[0x4a] = 0;
  *(undefined1 *)(param_1 + 0x4b) = 0;
  param_1[0x47] = 0;
  *(undefined1 *)(param_1 + 0x49) = 0;
  param_1[0x48] = 0;
  param_1[0x4d] = 0;
  param_1[0x4c] = 0;
  param_1[0x50] = 0;
  param_1[0x4f] = 0;
  param_1[0x5a] = 0;
  param_1[0x59] = 0;
  param_1[0x65] = 0;
  param_1[100] = 0;
  param_1[99] = 0;
  param_1[0x62] = 0;
  param_1[0x61] = 0;
  param_1[0x68] = 0;
  param_1[0x67] = 0;
  *(undefined2 *)(param_1 + 0x6c) = 0x301;
  *(undefined2 *)(param_1 + 0x69) = 0;
  param_1[0x6b] = 0;
  param_1[0x6a] = 0;
  param_1[0x6e] = 0;
  param_1[0x6d] = 0;
  *(undefined1 *)(param_1 + 0x6f) = 1;
  *(undefined1 *)(param_1 + 0x70) = 1;
  *(undefined8 *)((long)param_1 + 0x3b4) = 0;
  *(undefined8 *)((long)param_1 + 0x3ac) = 0;
  *(undefined4 *)((long)param_1 + 0x3bc) = 0;
  param_1[0x72] = 0;
  param_1[0x71] = 0;
  param_1[0x74] = 0;
  param_1[0x73] = 0;
  *(undefined1 *)(param_1 + 0x75) = 0;
  param_1[0x79] = 0;
  param_1[0x78] = 0;
  param_1[0x7b] = 0;
  param_1[0x7a] = 0;
  param_1[0x7d] = 0;
  param_1[0x7c] = 0;
  param_1[0x7f] = 0;
  param_1[0x7e] = 0;
  Aska::Yayoi::IPAddress::IPAddress()(param_1 + 0x81);
  *(undefined1 *)(param_1 + 0x92) = 0;
  param_1[0x94] = 0;
  param_1[0x93] = 0;
  puVar1 = PTR__ZTV12BridgeNotify_02cbc800;
  param_1[0x95] = 0;
  *(undefined4 *)(param_1 + 0x96) = 0;
  plVar3 = (long *)param_1[6];
  param_1[0x97] = (long)(puVar1 + 0x10);
  param_1[0x98] = param_2;
  param_1[0x99] = -0x3a5;
  *(undefined1 *)(param_1 + 0x9a) = 0;
  param_1[0xa2] = 0x7b1a9377;
  *(undefined1 *)(param_1 + 0xa3) = 0;
  if (param_1 + 2 == plVar3) {
    pcVar4 = *(code **)(*plVar3 + 0x20);
  }
  else {
    if (plVar3 == (long *)0x0) goto code_r0x014bad08;
    pcVar4 = *(code **)(*plVar3 + 0x28);
  }
  (*pcVar4)();
code_r0x014bad08:
  param_1[6] = 0;
  *(undefined1 *)((long)param_1 + 0x4d1) = 0;
  *(undefined1 *)(param_1 + 0xa1) = 0;
  param_1[0xa0] = 0;
  param_1[0x9f] = 0;
  return;
}

// ==== CApiNotify::OnProtocolError(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, Aska::Status)
// vaddr 0x13bafe8 | ghidra 0x14bafe8 | size 396 | symbol _ZN10CApiNotify15OnProtocolErrorEN4Aska5Yayoi7GameRPC12GameProtocol10FunctionIDENS0_6StatusE | lib libSOA-3.7.0.so | 2026-10-09
void _ZN10CApiNotify15OnProtocolErrorEN4Aska5Yayoi7GameRPC12GameProtocol10FunctionIDENS0_6StatusE
               (long param_1,undefined4 param_2,long *param_3)

{
  ulong uVar1;
  undefined *puVar2;
  int iVar3;
  long lVar4;
  undefined1 auStack_48 [8];
  long lStack_40;
  long lStack_38;
  
  lStack_38 = *param_3;
  iVar3 = CNetworkUtility::AskaStatus2ApiErrorCode(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, Aska::Status)(param_2,&lStack_38);
  if (*param_3 == -0x3b4) {
    return;
  }
  if (*(char *)(param_1 + 0x518) == '\0') {
    return;
  }
  uVar1 = *param_3 + 0x3f6;
  if ((uVar1 < 0x1f) && ((1L << (uVar1 & 0x3f) & 0x40002001U) != 0)) {
    return;
  }
  *(undefined1 *)(param_1 + 0x518) = 0;
  puVar2 = PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
  lVar4 = *(long *)PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
  if (lVar4 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar4 = *(long *)puVar2;
  }
  lVar4 = CParameterManager::pParameterPlayer() const(lVar4);
  if (*(char *)(lVar4 + 0x178) != '\0') {
    lVar4 = *(long *)puVar2;
    if (lVar4 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
      lVar4 = *(long *)puVar2;
    }
    CParameterManager::pParameterPlayer() const(lVar4);
    lVar4 = CParameterPlayer::pParameter() const();
    if (((*(int *)(lVar4 + 0x38) != 0) && (iVar3 != 0x3ed)) && (*param_3 != -0x393))
    goto code_r0x014bb0f8;
  }
  (**(code **)(**(long **)PTR__ZN9Framework10TSingletonI10CApiCallerE11m_pInstanceE_02cb8278 + 0x470
              ))(*(long **)PTR__ZN9Framework10TSingletonI10CApiCallerE11m_pInstanceE_02cb8278,0);
  *(undefined1 *)(param_1 + 0x4d0) = 0;
code_r0x014bb0f8:
  puVar2 = PTR__ZN9Framework10TSingletonI12ErrorHandlerE11m_pInstanceE_02cc0dc0;
  lVar4 = *(long *)PTR__ZN9Framework10TSingletonI12ErrorHandlerE11m_pInstanceE_02cc0dc0;
  if (lVar4 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar4 = *(long *)puVar2;
  }
  lStack_40 = *param_3;
  ErrorHandler::Handle(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, Aska::Status)(lVar4,param_2,&lStack_40);
  *(int *)(param_1 + 0x514) = iVar3;
  (**(code **)(**(long **)PTR__ZN9Framework10TSingletonI10CApiCallerE11m_pInstanceE_02cb8278 + 0x478
              ))(auStack_48,
                 *(long **)PTR__ZN9Framework10TSingletonI10CApiCallerE11m_pInstanceE_02cb8278,1,1);
  return;
}
