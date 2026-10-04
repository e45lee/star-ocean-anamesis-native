// port/decomp/scene/object_manager.c: Ghidra decompiles for the scene subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-04 06:27 UTC: tools/decomp.sh '--into' 'scene/object_manager' 'Aska::ObjectManager::' 'Aska::ObjectManagerJobDispatcher::' 'Aska::ObjectManagerWorkerThread::'

// ==== Aska::ObjectManager::ObjectManager()
// vaddr 0x215c918 | ghidra 0x225c918 | size 3052 | symbol _ZN4Aska13ObjectManagerC1Ev | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska13ObjectManagerC2Ev(long *param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  undefined *puVar3;
  ushort *puVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  undefined4 uVar7;
  long *plVar8;
  long lVar9;
  long *plVar10;
  code *pcVar11;
  int iVar12;
  long lVar13;
  
  Aska::TaskManager::TaskManager()();
  puVar1 = PTR__ZTVN4Aska13ObjectManagerE_02cc45c0 + 0xb0;
  *param_1 = (long)(PTR__ZTVN4Aska13ObjectManagerE_02cc45c0 + 0x10);
  param_1[5] = (long)puVar1;
  Aska::FastCriticalSection::FastCriticalSection()(param_1 + 0x362);
  lVar13 = *(long *)PTR__ZN4Aska6Global6m_pAppE_02cc2078;
  *PTR__ZN4Aska13ObjectManager19m_cShaderGradeLevelE_02cb9f98 = 1;
  *(undefined1 *)(param_1 + 0x7e1) = 3;
  plVar10 = param_1 + 0x8b3;
  *(int *)plVar10 = 0;
  *(undefined1 *)((long)param_1 + 0x3f09) = 0;
  param_1[0x360] = 0;
  param_1[0x892] = 0;
  param_1[0x891] = 0;
  plVar8 = (long *)operator new(unsigned long, std::nothrow_t const&)(0xd8,PTR__ZSt7nothrow_02cb9a80);
  if (plVar8 != (long *)0x0) {
    Aska::NotifierThread::NotifierThread(int)(plVar8,8);
    *plVar8 = (long)(PTR__ZTVN4Aska14BackBufferSyncE_02cc0048 + 0x10);
    Aska::Semaphore::Semaphore()(plVar8 + 0x18);
    *(undefined1 *)(plVar8 + 0x17) = 0;
    Aska::Semaphore::Create(int, int)(plVar8 + 0x18,1,1);
  }
  *(long **)PTR__ZN4Aska13ObjectManager17m_pBackBufferSyncE_02cb8770 = plVar8;
  Aska::NotifierThread::Init()(plVar8);
  plVar8 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x28,PTR__ZSt7nothrow_02cb9a80);
  if (plVar8 != (long *)0x0) {
    plVar8[4] = 0;
    puVar1 = PTR__ZTVN4Aska4TaskE_02cbe020;
    plVar8[1] = 0;
    *plVar8 = 0;
    plVar8[3] = 0;
    plVar8[2] = 0;
    pcVar11 = *(code **)(puVar1 + 0x68);
    *plVar8 = (long)(puVar1 + 0x10);
    *(undefined2 *)((long)plVar8 + 0x24) = 0;
    *(undefined1 *)((long)plVar8 + 0x26) = 0;
    uVar7 = (*pcVar11)(plVar8);
    *(undefined4 *)(plVar8 + 4) = uVar7;
    *plVar8 = (long)(PTR__ZTVN4Aska19FreezeRenderingTaskE_02cc4b18 + 0x10);
  }
  param_1[0x88c] = (long)plVar8;
  puVar1 = PTR__ZN4Aska6Global20m_pSystemTaskManagerE_02cbf620;
  Aska::TaskManager::AddTop(Aska::Task*)(*(undefined8 *)PTR__ZN4Aska6Global20m_pSystemTaskManagerE_02cbf620,plVar8);
  lVar9 = operator new(unsigned long, std::nothrow_t const&)(0x58,PTR__ZSt7nothrow_02cb9a80);
  if (lVar9 != 0) {
    Aska::RenderContextServer::RenderContextServer(int, int, int, int)(lVar9,*(undefined4 *)(lVar13 + 0x90),*(undefined4 *)(lVar13 + 0x94),
                    *(undefined4 *)(lVar13 + 0x98),*(undefined4 *)(lVar13 + 0x9c));
  }
  param_1[0x200] = lVar9;
  lVar9 = operator new(unsigned long, std::nothrow_t const&)(0x110,PTR__ZSt7nothrow_02cb9a80);
  if (lVar9 != 0) {
    Aska::RenderLayer::RenderLayer()(lVar9);
  }
  param_1[0x88f] = lVar9;
  Aska::RenderLayer::Init()(lVar9);
  lVar9 = operator new(unsigned long, std::nothrow_t const&)(0x50298,PTR__ZSt7nothrow_02cb9a80);
  if (lVar9 != 0) {
    Aska::RenderThread::RenderThread()(lVar9);
  }
  param_1[0x890] = lVar9;
  Aska::RenderThread::WaitForInit()(lVar9);
  Aska::TPoolFast<unsigned char [90], true>::SecurePool(unsigned int, unsigned char (*) [90])(PTR__ZN4Aska17ShaderNodeHandler15m_ShaderKeyPoolE_02cbf0f0,
                  (ulong)(*(uint *)(lVar13 + 0xa4) >> 1) / 0x2d,0);
  lVar13 = operator new(unsigned long, std::nothrow_t const&)(0x2480,PTR__ZSt7nothrow_02cb9a80);
  if (lVar13 != 0) {
    Aska::FilterTextureObject::FilterTextureObject()(lVar13);
  }
  param_1[0x8b6] = lVar13;
  *(byte *)(lVar13 + 0x21fa) = *(byte *)(lVar13 + 0x21fa) | 1;
  Aska::FilterTextureObject::SetTextureID(unsigned long, unsigned int)(lVar13,0x7274406300000000,0x66744061);
  (**(code **)(*(long *)param_1[0x8b6] + 0x160))((long *)param_1[0x8b6],0x11);
  param_1[(long)(int)*plVar10 + 0x893] = param_1[0x8b6];
  iVar12 = (int)*plVar10 + 1;
  *(int *)plVar10 = iVar12;
  lVar13 = operator new(unsigned long, std::nothrow_t const&)(0x2220,PTR__ZSt7nothrow_02cb9a80);
  if (lVar13 != 0) {
    Aska::DepthTextureObject::DepthTextureObject()(lVar13);
    iVar12 = (int)*plVar10;
  }
  param_1[0x8b7] = lVar13;
  param_1[(long)iVar12 + 0x893] = lVar13;
  *(int *)plVar10 = (int)*plVar10 + 1;
  plVar8 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x310,PTR__ZSt7nothrow_02cb9a80);
  if (plVar8 != (long *)0x0) {
    Aska::RenderableObject::RenderableObject()(plVar8);
    *plVar8 = (long)(PTR__ZTVN4Aska17MSAAChangerObjectE_02cbfcb8 + 0x10);
    *(undefined2 *)(plVar8 + 0x61) = 0x100;
    Aska::RenderableObject::SetRenderLayerID(unsigned char)(plVar8,0xe);
    *(uint *)(plVar8 + 0x33) = *(uint *)(plVar8 + 0x33) | 2;
  }
  param_1[0x8b8] = (long)plVar8;
  *(undefined2 *)(plVar8 + 0x61) = 0x101;
  plVar8 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x310,PTR__ZSt7nothrow_02cb9a80);
  if (plVar8 != (long *)0x0) {
    Aska::RenderableObject::RenderableObject()(plVar8);
    *plVar8 = (long)(PTR__ZTVN4Aska17MSAAChangerObjectE_02cbfcb8 + 0x10);
    *(undefined2 *)(plVar8 + 0x61) = 0x100;
    Aska::RenderableObject::SetRenderLayerID(unsigned char)(plVar8,0xe);
    *(uint *)(plVar8 + 0x33) = *(uint *)(plVar8 + 0x33) | 2;
  }
  param_1[0x8b9] = (long)plVar8;
  *(undefined2 *)(plVar8 + 0x61) = 1;
  *(undefined4 *)(param_1 + 0x7e3) = 0x3f800000;
  Aska::CameraFilterManager::InitAskasRGBTableTable()();
  memset(param_1 + 0x167e,0,0x240);
  plVar8 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x1920,PTR__ZSt7nothrow_02cb9a80);
  if (plVar8 != (long *)0x0) {
    Aska::RenderableObject::RenderableObject()(plVar8);
    *plVar8 = (long)(PTR__ZTVN4Aska24ProceduralTextureManagerE_02cba158 + 0x10);
    *(undefined8 *)((long)plVar8 + 0x30c) = 0;
    *(undefined1 *)(plVar8 + 0x61) = 0;
    memset(plVar8 + 99,0,0x1600);
  }
  param_1[0x8bc] = (long)plVar8;
  Aska::CDRFTextureHandler::InitPrim()();
  plVar8 = (long *)operator new(unsigned long, unsigned long, bool)(0x7a0,0x10,1);
  if (plVar8 != (long *)0x0) {
    *(undefined4 *)(plVar8 + 0x22) = 0;
    plVar8[0x21] = 0x3f800000;
    memset(plVar8 + 1,0,0x100);
    *(undefined1 *)((long)plVar8 + 0x294) = 1;
    lVar13 = _UNK_029c7240;
    puVar2 = PTR__ZTVN4Aska19TFilmQuadraticCurveILi32EEE_02cc2d80 + 0x10;
    plVar8[0x54] = _UNK_029c7248;
    plVar8[0x53] = lVar13;
    *plVar8 = (long)puVar2;
    *(undefined4 *)(plVar8 + 0x78) = 0;
    plVar8[0x77] = 0x3f800000;
    memset(plVar8 + 0x57,0,0x100);
    *(undefined1 *)((long)plVar8 + 0x544) = 1;
    plVar8[0xa9] = 0x3f800000;
    plVar8[0xaa] = 0x3f800000;
    plVar8[0x56] = (long)puVar2;
    *(undefined1 *)(plVar8 + 0xaf) = 0;
    *(undefined1 *)(plVar8 + 0xb3) = 0;
    *(undefined1 *)(plVar8 + 0xb7) = 0;
    *(undefined1 *)(plVar8 + 0xbb) = 0;
    *(undefined1 *)(plVar8 + 0xbf) = 0;
    *(undefined1 *)(plVar8 + 0xc3) = 0;
    *(undefined1 *)(plVar8 + 199) = 0;
    *(undefined1 *)(plVar8 + 0xcb) = 0;
    *(undefined1 *)(plVar8 + 0xcf) = 0;
    *(undefined1 *)(plVar8 + 0xd3) = 0;
    *(undefined1 *)(plVar8 + 0xd7) = 0;
    *(undefined1 *)(plVar8 + 0xdb) = 0;
    *(undefined1 *)(plVar8 + 0xdf) = 0;
    *(undefined1 *)(plVar8 + 0xe3) = 0;
    *(undefined1 *)(plVar8 + 0xe7) = 0;
    *(undefined1 *)(plVar8 + 0xeb) = 0;
    *(undefined1 *)(plVar8 + 0xef) = 0;
    plVar8[0xad] = 0;
    plVar8[0xac] = 0;
    *(undefined4 *)(plVar8 + 0xae) = 0x800001;
    plVar8[0xb1] = 0;
    plVar8[0xb0] = 0;
    *(undefined4 *)(plVar8 + 0xb2) = 0x800001;
    plVar8[0xb5] = 0;
    plVar8[0xb4] = 0;
    *(undefined4 *)(plVar8 + 0xb6) = 0x800001;
    plVar8[0xb9] = 0;
    plVar8[0xb8] = 0;
    *(undefined4 *)(plVar8 + 0xba) = 0x800001;
    plVar8[0xbd] = 0;
    plVar8[0xbc] = 0;
    *(undefined4 *)(plVar8 + 0xbe) = 0x800001;
    plVar8[0xc1] = 0;
    plVar8[0xc0] = 0;
    *(undefined4 *)(plVar8 + 0xc2) = 0x800001;
    plVar8[0xc5] = 0;
    plVar8[0xc4] = 0;
    *(undefined4 *)(plVar8 + 0xc6) = 0x800001;
    plVar8[0xc9] = 0;
    plVar8[200] = 0;
    *(undefined4 *)(plVar8 + 0xca) = 0x800001;
    plVar8[0xcd] = 0;
    plVar8[0xcc] = 0;
    *(undefined4 *)(plVar8 + 0xce) = 0x800001;
    plVar8[0xd1] = 0;
    plVar8[0xd0] = 0;
    *(undefined4 *)(plVar8 + 0xd2) = 0x800001;
    plVar8[0xd5] = 0;
    plVar8[0xd4] = 0;
    *(undefined4 *)(plVar8 + 0xd6) = 0x800001;
    plVar8[0xd9] = 0;
    plVar8[0xd8] = 0;
    *(undefined4 *)(plVar8 + 0xda) = 0x800001;
    plVar8[0xdd] = 0;
    plVar8[0xdc] = 0;
    *(undefined4 *)(plVar8 + 0xde) = 0x800001;
    plVar8[0xe1] = 0;
    plVar8[0xe0] = 0;
    *(undefined4 *)(plVar8 + 0xe2) = 0x800001;
    plVar8[0xe5] = 0;
    plVar8[0xe4] = 0;
    *(undefined4 *)(plVar8 + 0xe6) = 0x800001;
    plVar8[0xe9] = 0;
    plVar8[0xe8] = 0;
    *(undefined4 *)(plVar8 + 0xea) = 0x800001;
    plVar8[0xed] = 0;
    plVar8[0xec] = 0;
    *(undefined4 *)(plVar8 + 0xee) = 0x800001;
    plVar8[0xf1] = 0;
    plVar8[0xf0] = 0;
    *(undefined4 *)(plVar8 + 0xf2) = 0x800001;
    *(undefined1 *)(plVar8 + 0xf3) = 0;
  }
  param_1[0x8bb] = (long)plVar8;
  Aska::PostProcessMaster::CreateTableTextures()(plVar8);
  plVar8 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x4a0,PTR__ZSt7nothrow_02cb9a80);
  if (plVar8 != (long *)0x0) {
    Aska::RenderableObject::RenderableObject()(plVar8);
    *(undefined4 *)(plVar8 + 0x61) = 0;
    puVar2 = PTR__ZTVN4Aska24PostProcessBufferManagerE_02cc48d0;
    *(undefined2 *)((long)plVar8 + 0x43c) = 0;
    *(undefined2 *)(plVar8 + 0x88) = 0;
    *plVar8 = (long)(puVar2 + 0x10);
    plVar8[0x84] = 0;
    plVar8[0x83] = 0;
    *(undefined4 *)((long)plVar8 + 0x444) = 0x3f800000;
    *(undefined1 *)((long)plVar8 + 0x1b7) = 0x15;
    plVar8[0x6f] = 0;
    plVar8[0x6e] = 0;
    plVar8[0x71] = 0;
    plVar8[0x70] = 0;
    *(undefined4 *)(plVar8 + 0x89) = 0;
    plVar8[0x75] = 0;
    plVar8[0x74] = 0;
    plVar8[0x77] = 0;
    plVar8[0x76] = 0;
    plVar8[0x7f] = 0;
    plVar8[0x7e] = 0;
    plVar8[0x81] = 0;
    plVar8[0x80] = 0;
    *(ushort *)((long)plVar8 + 0x24) = *(ushort *)((long)plVar8 + 0x24) | 2;
    plVar8[0x82] = 0;
  }
  param_1[(long)(int)*plVar10 + 0x893] = (long)plVar8;
  *(int *)plVar10 = (int)*plVar10 + 1;
  param_1[0x1684] = (long)plVar8;
  plVar10 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x1ee0,PTR__ZSt7nothrow_02cb9a80);
  if (plVar10 != (long *)0x0) {
    Aska::RenderableObject::RenderableObject()(plVar10);
    *(undefined4 *)(plVar10 + 0x61) = 0;
    *plVar10 = (long)(PTR__ZTVN4Aska22PostProcessCombinerTBRE_02cbc048 + 0x10);
    plVar10[0x67] = 0;
    *(undefined1 *)((long)plVar10 + 0x344) = 0;
    *(undefined4 *)(plVar10 + 0x68) = 0xffffffff;
    *(byte *)((long)plVar10 + 0x345) = *(byte *)((long)plVar10 + 0x345) & 0xfc | 1;
    plVar10[0x66] = 0x408000003f400000;
    Aska::ToneMapTable::CalcLogEncodeCoef()(plVar10 + 0x62);
    plVar10[0x6a] = 0;
    *(undefined1 *)((long)plVar10 + 0x1ed5) = 0;
    *(byte *)((long)plVar10 + 0x1ed7) = *(byte *)((long)plVar10 + 0x1ed7) | 1;
    *(undefined1 *)((long)plVar10 + 0x1b7) = 0x18;
    *(uint *)(plVar10 + 0x33) = *(uint *)(plVar10 + 0x33) | 2;
    *(ushort *)((long)plVar10 + 0x24) = *(ushort *)((long)plVar10 + 0x24) | 2;
    Aska::ToneMapTable::CreateToneCurveTextures()(plVar10 + 0x62);
    *(undefined4 *)((long)plVar10 + 0x464) = 0x3f800000;
    uVar6 = _UNK_029cc808;
    uVar5 = _UNK_029cc800;
    *(undefined4 *)(plVar10 + 0x91) = 0x41700000;
    *(undefined1 *)((long)plVar10 + 0x1ed4) = 0;
    *(undefined8 *)((long)plVar10 + 0x494) = uVar6;
    *(undefined8 *)((long)plVar10 + 0x48c) = uVar5;
    plVar10[0x8e] = 0;
    plVar10[0x90] = 0;
    plVar10[0xb6] = 0;
    plVar10[0xb5] = 0;
    plVar10[0xb4] = 0;
    plVar10[0xb3] = 0;
    plVar10[0xb2] = 0;
    plVar10[0xb1] = 0;
    plVar10[0xb0] = 0;
    plVar10[0xaf] = 0;
    *(undefined2 *)(plVar10 + 0xb8) = 0;
    *(byte *)((long)plVar10 + 0x5fa) = *(byte *)((long)plVar10 + 0x5fa) & 0xfd;
    memset(plVar10 + 0xde,0,0x600);
    plVar10[0x1a5] = 0;
    plVar10[0x1a4] = 0;
    plVar10[0x1a9] = 0;
    plVar10[0x1a8] = 0;
    plVar10[0x1a7] = 0;
    plVar10[0x1a6] = 0;
    *(byte *)((long)plVar10 + 0x1ed7) = *(byte *)((long)plVar10 + 0x1ed7) & 0xfb;
    memset(plVar10 + 0x9e,0,0x78);
  }
  Aska::PostProcessCombinerTBR::Init(Aska::PostProcessBufferManager*)(plVar10,plVar8);
  plVar10[0x8a] = param_1[0x8bb];
  Aska::PostProcessBloomTBR::CreateAverageLuminanceSurvey()(plVar10[0x8e]);
  param_1[0x1683] = (long)plVar10;
  *(undefined4 *)(param_1 + 0x8bd) = 0x3dcccccd;
  memset(param_1 + 0x20a4,0,0x1d8);
  param_1[0x209f] = param_1[0x8b7];
  param_1[0x20a1] = param_1[0x8b9];
  param_1[0x20a0] = param_1[0x8b8];
  param_1[0x20a2] = param_1[0x8b6];
  *(undefined4 *)(param_1 + 0x20df) = 5;
  param_1[0x20a3] = (long)plVar8;
  Aska::PostProcessCombinerTBR::AddSystemObjects(Aska::ObjectManager*)(plVar10,param_1);
  Aska::ObjectManager::MakeDefaultRenderLayers()(param_1);
  *(undefined2 *)((long)param_1 + 0x3efa) = 0;
  param_1[0x202] = 0;
  param_1[0x201] = 0;
  memset(param_1 + 0x204,0,0x80);
  *(undefined4 *)((long)param_1 + 0x1bc4) = 0;
  param_1[0x3d4] = 0;
  param_1[0x3d3] = 0;
  param_1[0x3d2] = 0;
  param_1[0x3d1] = 0;
  *(undefined1 *)((long)param_1 + 0x3f1d) = 1;
  memset(param_1 + 0x8be,0,0x2400);
  param_1[0x37a] = 0;
  param_1[0x379] = 0;
  param_1[0x37c] = 0;
  param_1[0x37b] = 0;
  memset(param_1 + 0x3d5,0,0x200);
  memset(param_1 + 0x381,0,0x200);
  memset(param_1 + 0x214,0,0x800);
  lVar13 = -0x1200;
  do {
    lVar9 = lVar13 + 0x48;
    *(ushort *)((long)param_1 + lVar13 + 0xa032) =
         *(ushort *)((long)param_1 + lVar13 + 0xa032) & 0xfff3;
    lVar13 = lVar9;
  } while (lVar9 != 0);
  memset(param_1 + 0x163e,0,0x200);
  memset(param_1 + 0x3c1,0,0x80);
  puVar2 = PTR__ZSt7nothrow_02cb9a80;
  lVar13 = operator new[](unsigned long, std::nothrow_t const&)(0x8000,PTR__ZSt7nothrow_02cb9a80);
  param_1[0x203] = lVar13;
  lVar13 = operator new[](unsigned long, std::nothrow_t const&)(0x8000,puVar2);
  param_1[0x204] = lVar13;
  lVar13 = operator new[](unsigned long, std::nothrow_t const&)(0x8000,puVar2);
  param_1[0x205] = lVar13;
  lVar13 = operator new[](unsigned long, std::nothrow_t const&)(0x8000,puVar2);
  param_1[0x201] = lVar13;
  lVar13 = operator new[](unsigned long, std::nothrow_t const&)(0x8000,puVar2);
  param_1[0x202] = lVar13;
  lVar13 = operator new[](unsigned long, std::nothrow_t const&)(0x8000,puVar2);
  param_1[0x314] = lVar13;
  Aska::LIBLManager::CreateNotify(int)(*(undefined8 *)PTR__ZN4Aska6Global14m_pLIBLManagerE_02cc46a8,0x1000);
  lVar13 = operator new[](unsigned long, std::nothrow_t const&)(0x100,puVar2);
  param_1[0x35c] = lVar13;
  *(undefined4 *)(param_1 + 0x361) = 0;
  memset(param_1 + 0x7e9,0,0x50a);
  lVar13 = operator new[](unsigned long, std::nothrow_t const&)(0x8000,puVar2);
  if (lVar13 != 0) {
    param_1[0x7e9] = lVar13;
    *(undefined2 *)(param_1 + 0x86a) = 0x1000;
  }
  puVar2 = PTR__ZSt7nothrow_02cb9a80;
  lVar13 = operator new[](unsigned long, std::nothrow_t const&)(0x200,PTR__ZSt7nothrow_02cb9a80);
  param_1[0x35d] = lVar13;
  *(undefined2 *)((long)param_1 + 0x3f04) = 0;
  lVar13 = operator new[](unsigned long, std::nothrow_t const&)(0x8000,puVar2);
  param_1[0x35e] = lVar13;
  *(undefined2 *)(param_1 + 0x7e0) = 0;
  lVar13 = operator new[](unsigned long, std::nothrow_t const&)(0x8000,puVar2);
  param_1[0x359] = lVar13;
  lVar13 = operator new[](unsigned long, std::nothrow_t const&)(0x8000,puVar2);
  param_1[0x356] = lVar13;
  lVar13 = operator new[](unsigned long, std::nothrow_t const&)(0x8000,puVar2);
  param_1[0x357] = lVar13;
  lVar13 = operator new[](unsigned long, std::nothrow_t const&)(0x4000,puVar2);
  param_1[0x358] = lVar13;
  lVar13 = operator new[](unsigned long, std::nothrow_t const&)(0x8000,puVar2);
  param_1[0x35a] = lVar13;
  lVar13 = operator new[](unsigned long, std::nothrow_t const&)(0x8000,puVar2);
  param_1[0x35b] = lVar13;
  *(undefined1 *)((long)param_1 + 0x3f0b) = 0;
  *(undefined1 *)((long)param_1 + 0x3f12) = 1;
  *(undefined4 *)((long)param_1 + 0x3ef4) = 0;
  *(undefined2 *)(param_1 + 0x7df) = 0;
  *(undefined2 *)((long)param_1 + 0x3efc) = 0;
  *(undefined4 *)((long)param_1 + 0x3f24) = 0x3e800000;
  *(undefined1 *)((long)param_1 + 0x3f11) = 0;
  *(undefined4 *)(param_1 + 0x7e5) = 0;
  *(undefined4 *)(param_1 + 0x7e4) = 0;
  param_1[0x88b] = 0;
  *(undefined4 *)((long)param_1 + 0x1bc4) = 0;
  puVar4 = (ushort *)((long)param_1 + 0xb432);
  param_1[0x1680] = 7;
  param_1[0x1681] = 0x3f800000;
  *puVar4 = *puVar4 & 0xfef3 | 0x104;
  plVar10 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x13f0,puVar2);
  if (plVar10 != (long *)0x0) {
    Aska::TaskManager::TaskManager()(plVar10);
    puVar2 = PTR__ZTVN4Aska21ShadowManagerRegistryE_02cb7e60 + 0x10;
    puVar3 = PTR__ZTVN4Aska21ShadowManagerRegistryE_02cb7e60 + 0xb0;
    *(undefined1 *)((long)plVar10 + 0xffb) = 0;
    *plVar10 = (long)puVar2;
    plVar10[5] = (long)puVar3;
    *(undefined2 *)(plVar10 + 0x1ff) = 0;
    memset(plVar10 + 0x200,0,0x1f0);
    *(undefined1 *)((long)plVar10 + 0xffa) = 0x10;
    memset(plVar10 + 0x24e,0,0x80);
  }
  param_1[0x209e] = (long)plVar10;
  plVar8 = (long *)0x0;
  if (plVar10 != (long *)0x0) {
    plVar8 = plVar10 + 5;
  }
  Aska::TaskManager::Add(Aska::Task*)(*(undefined8 *)puVar1,plVar8);
  *puVar4 = *puVar4 & 0xedff | 0x1000;
  param_1[0x374] = 0;
  *(undefined4 *)(param_1 + 0x375) = 0;
  *(undefined1 *)((long)param_1 + 0x3f13) = 0;
  *(undefined1 *)((long)param_1 + 0x3f0c) = 1;
  *(undefined1 *)((long)param_1 + 0x3f0d) = 0;
  *(undefined1 *)((long)param_1 + 0x3f0e) = 0;
  *(undefined1 *)((long)param_1 + 0x3f0f) = 0;
  *(undefined1 *)(param_1 + 0x7e2) = 0;
  *(undefined1 *)(param_1 + 0x1ff) = 1;
  *(undefined4 *)(param_1 + 0x8ba) = 0;
  *(undefined1 *)((long)param_1 + 0x3f14) = 0;
  return;
}

// ==== Aska::ObjectManager::MakeDefaultRenderLayers()
// vaddr 0x215d504 | ghidra 0x225d504 | size 480 | symbol _ZN4Aska13ObjectManager23MakeDefaultRenderLayersEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13ObjectManager23MakeDefaultRenderLayersEv(long param_1)

{
  Aska::RenderLayer::AddLayer(unsigned char, unsigned char)(*(undefined8 *)(param_1 + 0x4478),0,2);
  Aska::RenderLayer::AddLayer(unsigned char, unsigned char)(*(undefined8 *)(param_1 + 0x4478),1,0);
  Aska::RenderLayer::AddLayer(unsigned char, unsigned char)(*(undefined8 *)(param_1 + 0x4478),2,0);
  Aska::RenderLayer::AddLayer(unsigned char, unsigned char)(*(undefined8 *)(param_1 + 0x4478),3,2);
  Aska::RenderLayer::AddLayer(unsigned char, unsigned char)(*(undefined8 *)(param_1 + 0x4478),4,0);
  Aska::RenderLayer::AddLayer(unsigned char, unsigned char)(*(undefined8 *)(param_1 + 0x4478),5,0);
  Aska::RenderLayer::AddLayer(unsigned char, unsigned char)(*(undefined8 *)(param_1 + 0x4478),6,1);
  Aska::RenderLayer::AddLayer(unsigned char, unsigned char)(*(undefined8 *)(param_1 + 0x4478),7,1);
  Aska::RenderLayer::AddLayer(unsigned char, unsigned char)(*(undefined8 *)(param_1 + 0x4478),8,0x11);
  Aska::RenderLayer::AddLayer(unsigned char, unsigned char)(*(undefined8 *)(param_1 + 0x4478),9,1);
  Aska::RenderLayer::AddLayer(unsigned char, unsigned char)(*(undefined8 *)(param_1 + 0x4478),10,1);
  Aska::RenderLayer::AddLayer(unsigned char, unsigned char)(*(undefined8 *)(param_1 + 0x4478),0xb,1);
  Aska::RenderLayer::AddLayer(unsigned char, unsigned char)(*(undefined8 *)(param_1 + 0x4478),0xc,1);
  Aska::RenderLayer::AddLayer(unsigned char, unsigned char)(*(undefined8 *)(param_1 + 0x4478),0xd,1);
  Aska::RenderLayer::AddLayer(unsigned char, unsigned char)(*(undefined8 *)(param_1 + 0x4478),0xf,1);
  Aska::RenderLayer::AddLayer(unsigned char, unsigned char)(*(undefined8 *)(param_1 + 0x4478),0x10,0);
  Aska::RenderLayer::AddLayer(unsigned char, unsigned char)(*(undefined8 *)(param_1 + 0x4478),0xe,1);
  Aska::RenderLayer::AddLayer(unsigned char, unsigned char)(*(undefined8 *)(param_1 + 0x4478),0x11,0);
  Aska::RenderLayer::AddLayer(unsigned char, unsigned char)(*(undefined8 *)(param_1 + 0x4478),0x1b,0x10);
  Aska::RenderLayer::AddLayer(unsigned char, unsigned char)(*(undefined8 *)(param_1 + 0x4478),0x12,1);
  Aska::RenderLayer::AddLayer(unsigned char, unsigned char)(*(undefined8 *)(param_1 + 0x4478),0x13,0);
  Aska::RenderLayer::AddLayer(unsigned char, unsigned char)(*(undefined8 *)(param_1 + 0x4478),0x14,0);
  Aska::RenderLayer::AddLayer(unsigned char, unsigned char)(*(undefined8 *)(param_1 + 0x4478),0x15,0);
  Aska::RenderLayer::AddLayer(unsigned char, unsigned char)(*(undefined8 *)(param_1 + 0x4478),0x16,1);
  Aska::RenderLayer::AddLayer(unsigned char, unsigned char)(*(undefined8 *)(param_1 + 0x4478),0x17,0);
  Aska::RenderLayer::AddLayer(unsigned char, unsigned char)(*(undefined8 *)(param_1 + 0x4478),0x18,0);
  Aska::RenderLayer::AddLayer(unsigned char, unsigned char)(*(undefined8 *)(param_1 + 0x4478),0x19,0);
  Aska::RenderLayer::AddLayer(unsigned char, unsigned char)(*(undefined8 *)(param_1 + 0x4478),0x1a,0);
  *(undefined4 *)(param_1 + 0xff0) = 0x15;
  return;
}

// ==== Aska::ObjectManager::SetTileEnvironment(int, int, unsigned int, float, int)
// vaddr 0x215d6e4 | ghidra 0x225d6e4 | size 72 | symbol _ZN4Aska13ObjectManager18SetTileEnvironmentEiijfi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13ObjectManager18SetTileEnvironmentEiijfi
               (undefined4 param_1,long param_2,int param_3,undefined4 param_4,undefined4 param_5,
               undefined4 param_6)

{
  param_2 = param_2 + (long)param_3 * 0x48;
  *(undefined4 *)(param_2 + 0xb400) = param_4;
  *(undefined4 *)(param_2 + 0xb404) = param_5;
  *(undefined4 *)(param_2 + 0xb408) = param_1;
  *(undefined4 *)(param_2 + 0xb40c) = param_6;
  *(ushort *)(param_2 + 0xb432) = *(ushort *)(param_2 + 0xb432) & 0xfef3 | 0x104;
  return;
}

// ==== Aska::ObjectManager::~ObjectManager()
// vaddr 0x215d72c | ghidra 0x225d72c | size 1020 | symbol _ZN4Aska13ObjectManagerD1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13ObjectManagerD2Ev(long *param_1)

{
  undefined *puVar1;
  long *plVar2;
  long lVar3;
  
  puVar1 = PTR__ZTVN4Aska13ObjectManagerE_02cc45c0 + 0xb0;
  *param_1 = (long)(PTR__ZTVN4Aska13ObjectManagerE_02cc45c0 + 0x10);
  param_1[5] = (long)puVar1;
  plVar2 = param_1 + 0x209e;
  if (*plVar2 != 0) {
    Aska::Task::Remove()(*plVar2 + 0x28);
    (**(code **)(*(long *)(*plVar2 + 0x28) + 0x38))((long *)(*plVar2 + 0x28),0);
    *plVar2 = 0;
  }
  puVar1 = PTR__ZN4Aska13ObjectManager17m_pBackBufferSyncE_02cb8770;
  if (*(long **)PTR__ZN4Aska13ObjectManager17m_pBackBufferSyncE_02cb8770 != (long *)0x0) {
    (**(code **)(**(long **)PTR__ZN4Aska13ObjectManager17m_pBackBufferSyncE_02cb8770 + 8))();
    *(undefined8 *)puVar1 = 0;
  }
  plVar2 = (long *)param_1[0x88c];
  if (plVar2 != (long *)0x0) {
    (**(code **)(*plVar2 + 0x38))(plVar2,0);
    param_1[0x88c] = 0;
  }
  if ((long *)param_1[0x200] != (long *)0x0) {
    (**(code **)(*(long *)param_1[0x200] + 8))();
    param_1[0x200] = 0;
  }
  lVar3 = param_1[0x88f];
  if (lVar3 != 0) {
    Aska::RenderLayer::~RenderLayer()(lVar3);
    operator delete(void*)(lVar3);
    param_1[0x88f] = 0;
  }
  if ((long *)param_1[0x890] != (long *)0x0) {
    (**(code **)(*(long *)param_1[0x890] + 8))();
    param_1[0x890] = 0;
  }
  if (param_1[0x356] != 0) {
    operator delete(void*)();
    param_1[0x356] = 0;
  }
  if (param_1[0x357] != 0) {
    operator delete(void*)();
    param_1[0x357] = 0;
  }
  if (param_1[0x358] != 0) {
    operator delete(void*)();
    param_1[0x358] = 0;
  }
  puVar1 = PTR__ZN4Aska17ShaderNodeHandler15m_ShaderKeyPoolE_02cbf0f0;
  if (PTR__ZN4Aska17ShaderNodeHandler15m_ShaderKeyPoolE_02cbf0f0[0xd0] == '\0') {
    *(undefined8 *)(PTR__ZN4Aska17ShaderNodeHandler15m_ShaderKeyPoolE_02cbf0f0 + 0x30) = 0;
    lVar3 = *(long *)(puVar1 + 0x18);
  }
  else {
    if (*(long *)(PTR__ZN4Aska17ShaderNodeHandler15m_ShaderKeyPoolE_02cbf0f0 + 0x30) != 0) {
      operator delete[](void*)();
      *(undefined8 *)(puVar1 + 0x30) = 0;
    }
    puVar1[0xd0] = 0;
    lVar3 = *(long *)(puVar1 + 0x18);
  }
  if ((lVar3 != 0) && (puVar1[0x28] != '\0')) {
    operator delete[](void*)();
    puVar1[0x28] = 0;
  }
  *(undefined8 *)(puVar1 + 0x18) = 0;
  *(undefined8 *)(puVar1 + 0x20) = 0;
  plVar2 = (long *)param_1[0x8bc];
  if (plVar2 != (long *)0x0) {
    (**(code **)(*plVar2 + 0x38))(plVar2,0);
    param_1[0x8bc] = 0;
  }
  lVar3 = param_1[0x8bb];
  if (lVar3 != 0) {
    Aska::PostProcessMaster::~PostProcessMaster()(lVar3);
    operator delete(void*)(lVar3);
    param_1[0x8bb] = 0;
  }
  plVar2 = (long *)param_1[0x1684];
  if (plVar2 != (long *)0x0) {
    (**(code **)(*plVar2 + 0x38))(plVar2,0);
    param_1[0x1684] = 0;
  }
  plVar2 = (long *)param_1[0x1683];
  if (plVar2 != (long *)0x0) {
    (**(code **)(*plVar2 + 0x38))(plVar2,0);
    param_1[0x1683] = 0;
  }
  if (param_1[0x314] != 0) {
    operator delete[](void*)();
    param_1[0x314] = 0;
  }
  if (param_1[0x204] != 0) {
    operator delete[](void*)();
    param_1[0x204] = 0;
  }
  if (param_1[0x205] != 0) {
    operator delete[](void*)();
    param_1[0x205] = 0;
  }
  if (param_1[0x206] != 0) {
    operator delete[](void*)();
    param_1[0x206] = 0;
  }
  if (param_1[0x207] != 0) {
    operator delete[](void*)();
    param_1[0x207] = 0;
  }
  if (param_1[0x208] != 0) {
    operator delete[](void*)();
    param_1[0x208] = 0;
  }
  if (param_1[0x209] != 0) {
    operator delete[](void*)();
    param_1[0x209] = 0;
  }
  if (param_1[0x20a] != 0) {
    operator delete[](void*)();
    param_1[0x20a] = 0;
  }
  if (param_1[0x20b] != 0) {
    operator delete[](void*)();
    param_1[0x20b] = 0;
  }
  if (param_1[0x20c] != 0) {
    operator delete[](void*)();
    param_1[0x20c] = 0;
  }
  if (param_1[0x20d] != 0) {
    operator delete[](void*)();
    param_1[0x20d] = 0;
  }
  if (param_1[0x20e] != 0) {
    operator delete[](void*)();
    param_1[0x20e] = 0;
  }
  if (param_1[0x20f] != 0) {
    operator delete[](void*)();
    param_1[0x20f] = 0;
  }
  if (param_1[0x210] != 0) {
    operator delete[](void*)();
    param_1[0x210] = 0;
  }
  if (param_1[0x211] != 0) {
    operator delete[](void*)();
    param_1[0x211] = 0;
  }
  if (param_1[0x212] != 0) {
    operator delete[](void*)();
    param_1[0x212] = 0;
  }
  if (param_1[0x213] != 0) {
    operator delete[](void*)();
    param_1[0x213] = 0;
  }
  if (param_1[0x201] != 0) {
    operator delete[](void*)();
    param_1[0x201] = 0;
  }
  if (param_1[0x202] != 0) {
    operator delete[](void*)();
    param_1[0x202] = 0;
  }
  if (param_1[0x203] != 0) {
    operator delete[](void*)();
    param_1[0x203] = 0;
  }
  if (param_1[0x35c] != 0) {
    operator delete[](void*)();
    param_1[0x35c] = 0;
  }
  if (param_1[0x35d] != 0) {
    operator delete[](void*)();
    param_1[0x35d] = 0;
  }
  if (param_1[0x35e] != 0) {
    operator delete[](void*)();
    param_1[0x35e] = 0;
  }
  lVar3 = -0x800;
  do {
    if (*(long *)((long)param_1 + lVar3 + 0x18a0) != 0) {
      operator delete(void*)();
      *(undefined8 *)((long)param_1 + lVar3 + 0x18a0) = 0;
    }
    if (*(long *)((long)param_1 + lVar3 + 0x18a8) != 0) {
      operator delete(void*)();
      *(undefined8 *)((long)param_1 + lVar3 + 0x18a8) = 0;
    }
    lVar3 = lVar3 + 0x10;
  } while (lVar3 != 0);
  lVar3 = 0;
  do {
    if (*(long *)((long)param_1 + lVar3 + 0x3f48) != 0) {
      operator delete(void*)();
      *(undefined8 *)((long)param_1 + lVar3 + 0x3f48) = 0;
    }
    lVar3 = lVar3 + 8;
  } while (lVar3 != 0x408);
  if (param_1[0x359] != 0) {
    operator delete(void*)();
    param_1[0x359] = 0;
  }
  if (param_1[0x35b] != 0) {
    operator delete(void*)();
    param_1[0x35b] = 0;
  }
  if (param_1[0x35a] != 0) {
    operator delete(void*)();
    param_1[0x35a] = 0;
  }
  if (param_1[0x374] != 0) {
    operator delete[](void*)();
  }
  Aska::FastCriticalSection::~FastCriticalSection()(param_1 + 0x362);
  (*(code *)PTR__ZN4Aska11TaskManagerD2Ev_02ca45c0)(param_1);
  return;
}

// ==== non-virtual thunk to Aska::ObjectManager::~ObjectManager()
// vaddr 0x215db28 | ghidra 0x225db28 | size 8 | symbol _ZThn40_N4Aska13ObjectManagerD1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZThn40_N4Aska13ObjectManagerD1Ev(long param_1)

{
  (*(code *)PTR__ZN4Aska13ObjectManagerD2Ev_02caad98)(param_1 + -0x28);
  return;
}

// ==== Aska::ObjectManager::~ObjectManager()
// vaddr 0x215db30 | ghidra 0x225db30 | size 24 | symbol _ZN4Aska13ObjectManagerD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13ObjectManagerD0Ev(undefined8 param_1)

{
  Aska::ObjectManager::~ObjectManager()();
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== non-virtual thunk to Aska::ObjectManager::~ObjectManager()
// vaddr 0x215db48 | ghidra 0x225db48 | size 28 | symbol _ZThn40_N4Aska13ObjectManagerD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZThn40_N4Aska13ObjectManagerD0Ev(long param_1)

{
  Aska::ObjectManager::~ObjectManager()(param_1 + -0x28);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1 + -0x28);
  return;
}

// ==== Aska::ObjectManager::SetTilebasedRendering(int)
// vaddr 0x215db64 | ghidra 0x225db64 | size 368 | symbol _ZN4Aska13ObjectManager21SetTilebasedRenderingEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13ObjectManager21SetTilebasedRenderingEi(long param_1,int param_2)

{
  long lVar1;
  undefined *puVar2;
  undefined8 uVar3;
  long lVar4;
  undefined8 *puVar5;
  
  if (*(long *)(param_1 + 0x1030) != 0) {
    operator delete[](void*)();
    *(undefined8 *)(param_1 + 0x1030) = 0;
  }
  if (*(long *)(param_1 + 0x1038) != 0) {
    operator delete[](void*)();
    *(undefined8 *)(param_1 + 0x1038) = 0;
  }
  if (*(long *)(param_1 + 0x1040) != 0) {
    operator delete[](void*)();
    *(undefined8 *)(param_1 + 0x1040) = 0;
  }
  if (*(long *)(param_1 + 0x1048) != 0) {
    operator delete[](void*)();
    *(undefined8 *)(param_1 + 0x1048) = 0;
  }
  if (*(long *)(param_1 + 0x1050) != 0) {
    operator delete[](void*)();
    *(undefined8 *)(param_1 + 0x1050) = 0;
  }
  if (*(long *)(param_1 + 0x1058) != 0) {
    operator delete[](void*)();
    *(undefined8 *)(param_1 + 0x1058) = 0;
  }
  if (*(long *)(param_1 + 0x1060) != 0) {
    operator delete[](void*)();
    *(undefined8 *)(param_1 + 0x1060) = 0;
  }
  if (*(long *)(param_1 + 0x1068) != 0) {
    operator delete[](void*)();
    *(undefined8 *)(param_1 + 0x1068) = 0;
  }
  if (*(long *)(param_1 + 0x1070) != 0) {
    operator delete[](void*)();
    *(undefined8 *)(param_1 + 0x1070) = 0;
  }
  if (*(long *)(param_1 + 0x1078) != 0) {
    operator delete[](void*)();
    *(undefined8 *)(param_1 + 0x1078) = 0;
  }
  if (*(long *)(param_1 + 0x1080) != 0) {
    operator delete[](void*)();
    *(undefined8 *)(param_1 + 0x1080) = 0;
  }
  if (*(long *)(param_1 + 0x1088) != 0) {
    operator delete[](void*)();
    *(undefined8 *)(param_1 + 0x1088) = 0;
  }
  if (*(long *)(param_1 + 0x1090) != 0) {
    operator delete[](void*)();
    *(undefined8 *)(param_1 + 0x1090) = 0;
  }
  if (*(long *)(param_1 + 0x1098) != 0) {
    operator delete[](void*)();
    *(undefined8 *)(param_1 + 0x1098) = 0;
  }
  if (7 < param_2) {
    param_2 = 8;
  }
  *(int *)(param_1 + 0x3f20) = param_2;
  puVar2 = PTR__ZSt7nothrow_02cb9a80;
  if (1 < param_2) {
    lVar4 = 0;
    puVar5 = (undefined8 *)(param_1 + 0x1038);
    do {
      *(undefined4 *)(param_1 + 0x3f2c + lVar4 * 4) = 0;
      uVar3 = operator new[](unsigned long, std::nothrow_t const&)(0x8000,puVar2);
      puVar5[-1] = uVar3;
      uVar3 = operator new[](unsigned long, std::nothrow_t const&)(0x8000,puVar2);
      lVar1 = lVar4 + 2;
      *puVar5 = uVar3;
      lVar4 = lVar4 + 1;
      puVar5 = puVar5 + 2;
    } while (lVar1 < param_2);
  }
  return;
}

// ==== Aska::ObjectManager::FlushSystemTextures()
// vaddr 0x215dcd4 | ghidra 0x225dcd4 | size 100 | symbol _ZN4Aska13ObjectManager19FlushSystemTexturesEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13ObjectManager19FlushSystemTexturesEv(long param_1)

{
  long lVar1;
  undefined4 *puVar2;
  
  if (*(char *)(param_1 + 0x3f09) == '\x02') {
    lVar1 = 0x40;
    puVar2 = (undefined4 *)(param_1 + 0x8e2c);
    do {
      if ((*(byte *)((long)puVar2 + 6) >> 2 & 1) != 0) {
        *puVar2 = 60000;
      }
      lVar1 = lVar1 + -1;
      puVar2 = puVar2 + 0x12;
    } while (lVar1 != 0);
  }
  *(undefined2 *)(*(long *)(param_1 + 0x45b0) + 0x21f8) = 0xfffe;
  Aska::DepthTextureObject::FlushTexture()(*(undefined8 *)(param_1 + 0x45b8));
  (*(code *)PTR__ZN4Aska24ProceduralTextureManager13FlushTexturesEv_02ca7e60)
            (*(undefined8 *)(param_1 + 0x45e0));
  return;
}

// ==== Aska::ObjectManager::OnPrePaint()
// vaddr 0x215dd38 | ghidra 0x225dd38 | size 2344 | symbol _ZN4Aska13ObjectManager10OnPrePaintEv | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Possible PIC construction at 0x0225e64c: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0x0225e650) */

void _ZN4Aska13ObjectManager10OnPrePaintEv(long param_1)

{
  ulong *puVar1;
  undefined *puVar2;
  ushort *puVar3;
  int *piVar4;
  uint uVar5;
  byte bVar6;
  ushort uVar7;
  char cVar8;
  bool bVar9;
  undefined1 auVar10 [16];
  undefined8 uVar11;
  long lVar12;
  undefined8 uVar13;
  ulong uVar14;
  ulong uVar15;
  uint *puVar16;
  byte *pbVar17;
  long lVar18;
  ulong *puVar19;
  long lVar20;
  undefined *puVar21;
  long *plVar22;
  ulong uVar23;
  char *pcVar24;
  int iVar25;
  int iVar26;
  int iVar27;
  int iVar28;
  int iVar29;
  int iVar30;
  int iVar31;
  int iVar32;
  ulong uVar33;
  ulong uVar34;
  
  if ((*(char *)(param_1 + 0x3f0c) == '\0') || (*(char *)(param_1 + 0x3f0e) != '\0')) {
    return;
  }
  if ((*(char *)(param_1 + 0x3f14) == '\0') &&
     (*(char *)(*(long *)(param_1 + 0x4480) + 0x501d1) != '\0')) {
    *(char *)(param_1 + 0x3f14) = '\x01';
    return;
  }
  if (*(long *)(*(long *)PTR__ZN4Aska6Global16m_pCameraManagerE_02cb7d08 + 0xff0) == 0) {
    return;
  }
  if (*(int *)(param_1 + 0x3ef4) == 0) {
    return;
  }
  lVar20 = *(long *)PTR__ZN4Aska6Global29m_pObjectManagerJobDispatcherE_02cb8e98;
  if (lVar20 == 0) {
    return;
  }
  Aska::SimpleMessageDispatcher::SuspendWorkerThread()(*(undefined8 *)PTR__ZN4Aska6Global20m_pMessageDispatcherE_02cb77c8);
  Aska::ObjectManagerJobDispatcher::ChangeMode(int)(lVar20,1);
  puVar2 = PTR__ZN4Aska20FrameTextureEntities13m_coordinatorE_02cc44e0 + 8;
  for (puVar21 = *(undefined **)(PTR__ZN4Aska20FrameTextureEntities13m_coordinatorE_02cc44e0 + 0x18)
      ; puVar21 != puVar2; puVar21 = *(undefined **)(puVar21 + 0x10)) {
    memset(puVar21 + 0x18,0,0x440);
    *(undefined4 *)(puVar21 + 0x1e14) = *(undefined4 *)(puVar21 + 0x1e10);
    puVar21[0x1e44] = puVar21[0x1e43];
    puVar21[0x1e43] = 0;
  }
  iVar25 = *(int *)(param_1 + 0x3ef4);
  plVar22 = *(long **)(param_1 + 0x45b0);
  *(int *)(param_1 + 0x3ef4) = iVar25 + 1;
  *(long **)(*(long *)(param_1 + 0x1ac8) + (long)iVar25 * 8) = plVar22;
  puVar3 = (ushort *)((long)plVar22 + 0x1b5);
  *(uint *)(plVar22 + 0x33) = *(uint *)(plVar22 + 0x33) & 0xdfffffbf;
  *puVar3 = *puVar3 & 0xfefe;
  *(undefined4 *)((long)plVar22 + 0x1ac) = 0;
  plVar22[0x3a] = 0;
  *(undefined4 *)((long)plVar22 + 0x1cc) = 0;
  (**(code **)(*plVar22 + 0x198))(plVar22);
  plVar22[0x47] = 0;
  plVar22[0x46] = 0;
  plVar22[0x40] = 0;
  plVar22[0x3f] = 0;
  plVar22[0x3e] = 0;
  plVar22[0x3d] = 0;
  *puVar3 = *puVar3 & 0xfff1 | 8;
  *(uint *)(plVar22 + 0x33) = *(uint *)(plVar22 + 0x33) & 0xfffffedb | 0x24;
  iVar25 = *(int *)(param_1 + 0x3ef4);
  plVar22 = *(long **)(param_1 + 0x45b8);
  *(int *)(param_1 + 0x3ef4) = iVar25 + 1;
  *(long **)(*(long *)(param_1 + 0x1ac8) + (long)iVar25 * 8) = plVar22;
  puVar3 = (ushort *)((long)plVar22 + 0x1b5);
  *(uint *)(plVar22 + 0x33) = *(uint *)(plVar22 + 0x33) & 0xdfffffbf;
  *puVar3 = *puVar3 & 0xfefe;
  *(undefined4 *)((long)plVar22 + 0x1ac) = 0;
  plVar22[0x3a] = 0;
  *(undefined4 *)((long)plVar22 + 0x1cc) = 0;
  (**(code **)(*plVar22 + 0x198))(plVar22);
  plVar22[0x47] = 0;
  plVar22[0x46] = 0;
  plVar22[0x40] = 0;
  plVar22[0x3f] = 0;
  plVar22[0x3e] = 0;
  plVar22[0x3d] = 0;
  *puVar3 = *puVar3 & 0xfff1 | 8;
  *(uint *)(plVar22 + 0x33) = *(uint *)(plVar22 + 0x33) & 0xfffffedb | 0x24;
  iVar25 = *(int *)(param_1 + 0x3ef4);
  plVar22 = *(long **)(param_1 + 0x45c0);
  *(int *)(param_1 + 0x3ef4) = iVar25 + 1;
  *(long **)(*(long *)(param_1 + 0x1ac8) + (long)iVar25 * 8) = plVar22;
  puVar3 = (ushort *)((long)plVar22 + 0x1b5);
  *(uint *)(plVar22 + 0x33) = *(uint *)(plVar22 + 0x33) & 0xdfffffbf;
  *puVar3 = *puVar3 & 0xfefe;
  *(undefined4 *)((long)plVar22 + 0x1ac) = 0;
  plVar22[0x3a] = 0;
  *(undefined4 *)((long)plVar22 + 0x1cc) = 0;
  (**(code **)(*plVar22 + 0x198))(plVar22);
  plVar22[0x47] = 0;
  plVar22[0x46] = 0;
  plVar22[0x40] = 0;
  plVar22[0x3f] = 0;
  plVar22[0x3e] = 0;
  plVar22[0x3d] = 0;
  *puVar3 = *puVar3 & 0xfff1 | 8;
  *(uint *)(plVar22 + 0x33) = *(uint *)(plVar22 + 0x33) & 0xfffffedb | 0x24;
  iVar25 = *(int *)(param_1 + 0x3ef4);
  plVar22 = *(long **)(param_1 + 0x45c8);
  *(int *)(param_1 + 0x3ef4) = iVar25 + 1;
  *(long **)(*(long *)(param_1 + 0x1ac8) + (long)iVar25 * 8) = plVar22;
  puVar3 = (ushort *)((long)plVar22 + 0x1b5);
  *(uint *)(plVar22 + 0x33) = *(uint *)(plVar22 + 0x33) & 0xdfffffbf;
  *puVar3 = *puVar3 & 0xfefe;
  *(undefined4 *)((long)plVar22 + 0x1ac) = 0;
  plVar22[0x3a] = 0;
  *(undefined4 *)((long)plVar22 + 0x1cc) = 0;
  (**(code **)(*plVar22 + 0x198))(plVar22);
  plVar22[0x47] = 0;
  plVar22[0x46] = 0;
  plVar22[0x40] = 0;
  plVar22[0x3f] = 0;
  plVar22[0x3e] = 0;
  plVar22[0x3d] = 0;
  *puVar3 = *puVar3 & 0xfff1 | 8;
  *(uint *)(plVar22 + 0x33) = *(uint *)(plVar22 + 0x33) & 0xfffffedb | 0x24;
  puVar16 = *(uint **)(param_1 + 0x4478);
  bVar6 = *(byte *)((long)puVar16 + 0x21);
  *(byte *)(param_1 + 0x3f1c) = bVar6;
  if ((*(char *)(param_1 + 0x3f1d) != '\0') && (*(byte *)((long)puVar16 + 0x1e) < bVar6)) {
    *(byte *)(param_1 + 0x3f1c) = *(byte *)((long)puVar16 + 0x1e);
  }
  uVar5 = *puVar16;
  if ((int)uVar5 < 1) {
    iVar25 = 0;
  }
  else {
    if (uVar5 < 8) {
      lVar18 = 0;
code_r0x0225e158:
      iVar25 = 0;
    }
    else {
      uVar23 = 8;
      if ((uVar5 & 7) != 0) {
        uVar23 = (ulong)(uVar5 & 7);
      }
      lVar18 = uVar5 - uVar23;
      if (lVar18 == 0) goto code_r0x0225e158;
      puVar19 = (ulong *)(*(long *)(puVar16 + 2) + 9);
      iVar25 = 0;
      iVar26 = 0;
      iVar27 = 0;
      iVar28 = 0;
      iVar29 = 0;
      iVar30 = 0;
      iVar31 = 0;
      iVar32 = 0;
      lVar12 = lVar18;
      do {
        puVar1 = puVar19 + -1;
        uVar33 = *puVar19;
        lVar12 = lVar12 + -8;
        puVar19 = puVar19 + 2;
        uVar14 = *puVar1 & 0xffffffffffff00ff;
        uVar15 = CONCAT44((int)(uVar14 >> 0x20),CONCAT22((short)(*puVar1 >> 0x10),(short)uVar14)) &
                 0xffffffff00ffffff;
        uVar14 = CONCAT26((short)(uVar15 >> 0x30),CONCAT24((short)(uVar14 >> 0x20),(int)uVar15)) &
                 0xff00ffffffffff;
        uVar34 = uVar33 & 0xffffffffffff00ff;
        uVar15 = CONCAT44((int)(uVar34 >> 0x20),CONCAT22((short)(uVar33 >> 0x10),(short)uVar34)) &
                 0xffffffff00ffffff;
        uVar15 = CONCAT26((short)(uVar15 >> 0x30),CONCAT24((short)(uVar34 >> 0x20),(int)uVar15)) &
                 0xff00ffffffffff;
        uVar14 = CONCAT26((ushort)(uVar14 >> 0x33),
                          CONCAT24((ushort)(uVar14 >> 0x20) >> 3,
                                   CONCAT22((ushort)(uVar14 >> 0x10) >> 3,(ushort)uVar14 >> 3))) &
                 0x1000100010001;
        uVar15 = CONCAT26((ushort)(uVar15 >> 0x33),
                          CONCAT24((ushort)(uVar15 >> 0x20) >> 3,
                                   CONCAT22((ushort)(uVar15 >> 0x10) >> 3,(ushort)uVar15 >> 3))) &
                 0x1000100010001;
        iVar25 = iVar25 + (uint)(ushort)uVar14;
        iVar26 = iVar26 + (uint)(ushort)(uVar14 >> 0x10);
        iVar27 = iVar27 + (uint)(ushort)(uVar14 >> 0x20);
        iVar28 = iVar28 + (uint)(ushort)(uVar14 >> 0x30);
        iVar29 = iVar29 + (uint)(ushort)uVar15;
        iVar30 = iVar30 + (uint)(ushort)(uVar15 >> 0x10);
        iVar31 = iVar31 + (uint)(ushort)(uVar15 >> 0x20);
        iVar32 = iVar32 + (uint)(ushort)(uVar15 >> 0x30);
      } while (lVar12 != 0);
      iVar25 = iVar29 + iVar25 + iVar30 + iVar26 + iVar31 + iVar27 + iVar32 + iVar28;
      if (uVar23 == 0) goto code_r0x0225e17c;
    }
    lVar12 = (ulong)uVar5 - lVar18;
    pbVar17 = (byte *)(*(long *)(puVar16 + 2) + lVar18 * 2 + 1);
    do {
      lVar12 = lVar12 + -1;
      iVar25 = iVar25 + (*pbVar17 >> 3 & 1);
      pbVar17 = pbVar17 + 2;
    } while (lVar12 != 0);
  }
code_r0x0225e17c:
  *(int *)(param_1 + 0x45d0) = iVar25;
  iVar25 = *(int *)(param_1 + 0x3ef4);
  plVar22 = *(long **)(param_1 + 0xb420);
  *(int *)(param_1 + 0x3ef4) = iVar25 + 1;
  *(long **)(*(long *)(param_1 + 0x1ac8) + (long)iVar25 * 8) = plVar22;
  puVar3 = (ushort *)((long)plVar22 + 0x1b5);
  *(uint *)(plVar22 + 0x33) = *(uint *)(plVar22 + 0x33) & 0xdfffffbf;
  *puVar3 = *puVar3 & 0xfefe;
  *(undefined4 *)((long)plVar22 + 0x1ac) = 0;
  plVar22[0x3a] = 0;
  *(undefined4 *)((long)plVar22 + 0x1cc) = 0;
  (**(code **)(*plVar22 + 0x198))(plVar22);
  plVar22[0x47] = 0;
  plVar22[0x46] = 0;
  plVar22[0x40] = 0;
  plVar22[0x3f] = 0;
  plVar22[0x3e] = 0;
  plVar22[0x3d] = 0;
  *puVar3 = *puVar3 & 0xfff1 | 8;
  *(uint *)(plVar22 + 0x33) = *(uint *)(plVar22 + 0x33) & 0xfffffedb | 0x24;
  uVar23 = 0;
  uVar13 = *(undefined8 *)PTR__ZN4Aska6Global15m_pLightManagerE_02cc1770;
  do {
    if (*(short *)(param_1 + 0x1e08 + uVar23 * 2) != 0) {
      Aska::ObjectManagerJobDispatcher::Dispatch_MakePaintingList(int, int)(lVar20,2,uVar23 & 0xffffffff);
    }
    uVar23 = uVar23 + 1;
  } while (uVar23 != 0x40);
  uVar23 = 0;
  pcVar24 = (char *)(param_1 + 0x4632);
  do {
    if (*(int *)(param_1 + 0x1c08 + uVar23 * 4) != 0) {
      if (*pcVar24 < '\0') {
        iVar25 = *(int *)(param_1 + 0x3ef4);
        plVar22 = *(long **)(pcVar24 + -0x12);
        *(int *)(param_1 + 0x3ef4) = iVar25 + 1;
        *(long **)(*(long *)(param_1 + 0x1ac8) + (long)iVar25 * 8) = plVar22;
        puVar3 = (ushort *)((long)plVar22 + 0x1b5);
        *(uint *)(plVar22 + 0x33) = *(uint *)(plVar22 + 0x33) & 0xdfffffbf;
        *puVar3 = *puVar3 & 0xfefe;
        *(undefined4 *)((long)plVar22 + 0x1ac) = 0;
        plVar22[0x3a] = 0;
        *(undefined4 *)((long)plVar22 + 0x1cc) = 0;
        (**(code **)(*plVar22 + 0x198))(plVar22);
        plVar22[0x47] = 0;
        plVar22[0x46] = 0;
        plVar22[0x40] = 0;
        plVar22[0x3f] = 0;
        plVar22[0x3e] = 0;
        plVar22[0x3d] = 0;
        *puVar3 = *puVar3 & 0xfff1 | 8;
        *(uint *)(plVar22 + 0x33) = *(uint *)(plVar22 + 0x33) & 0xfffffedb | 0x24;
      }
      Aska::ObjectManagerJobDispatcher::Dispatch_MakePaintingList(int, int)(lVar20,1,uVar23 & 0xffffffff);
    }
    uVar23 = uVar23 + 1;
    pcVar24 = pcVar24 + 0x48;
  } while (uVar23 != 0x80);
  iVar25 = *(int *)(param_1 + 0x3f20);
  if (iVar25 < 2) {
    iVar25 = 1;
  }
  if (0 < iVar25) {
    iVar26 = 0;
    do {
      Aska::ObjectManagerJobDispatcher::Dispatch_MakePaintingList(int, int)(lVar20,0,iVar26);
      iVar26 = iVar26 + 1;
    } while (iVar26 < iVar25);
  }
  if (*(int *)(param_1 + 0x1bc4) != 0) {
    Aska::ObjectManagerJobDispatcher::Dispatch_MakePaintingList(int, int)(lVar20,3,0);
  }
  Aska::RenderContextServer::ResetServer()(*(undefined8 *)(param_1 + 0x1000));
  iVar25 = *(int *)(param_1 + 0x3f20);
  if (iVar25 < 2) {
    iVar25 = 1;
  }
  if (0 < *(int *)(param_1 + 0x106f8)) {
    uVar7 = *(ushort *)(param_1 + 0x3ef0);
    lVar18 = 0;
    do {
      lVar12 = *(long *)(param_1 + 0x104f8 + lVar18 * 8);
      uVar11 = Aska::RenderContextServer::GetRenderContext(int)(*(undefined8 *)(param_1 + 0x1000),iVar25 + (uint)uVar7);
      *(undefined8 *)(lVar12 + 0x1d0) = uVar11;
      *(undefined4 *)(lVar12 + 0x1cc) = 0;
      lVar18 = lVar18 + 1;
    } while (lVar18 < *(int *)(param_1 + 0x106f8));
  }
  uVar5 = *(uint *)(param_1 + 0x1b08);
  if (0 < (int)uVar5) {
    uVar23 = 0;
    do {
      piVar4 = (int *)(*(long *)(*(long *)(param_1 + 0x1ae0) + uVar23 * 8) + 0x1ac);
      do {
        cVar8 = '\x01';
        bVar9 = (bool)ExclusiveMonitorPass(piVar4,0x10);
        if (bVar9) {
          *piVar4 = *piVar4 + 1;
          cVar8 = ExclusiveMonitorsStatus();
        }
      } while (cVar8 != '\0');
      uVar23 = uVar23 + 1;
    } while (uVar23 != uVar5);
  }
  iVar25 = *(int *)(param_1 + 0x3ef4);
  Aska::ObjectManagerJobDispatcher::ChangeMode(int)(lVar20,2);
  if (*(int *)(param_1 + 0x1ba8) < iVar25) {
    *(int *)(param_1 + 0x1ba8) = iVar25;
    if (*(long *)(param_1 + 0x1ba0) != 0) {
      operator delete[](void*)();
    }
    uVar5 = iVar25 + 0x3e;
    if (-1 < (int)(iVar25 + 0x1fU)) {
      uVar5 = iVar25 + 0x1fU;
    }
    uVar23 = (long)((ulong)uVar5 << 0x20) >> 0x25;
    uVar14 = -(ulong)((uint)((int)uVar5 >> 5) >> 0x1f) & 0xfffffff800000000 |
             (ulong)(uint)((int)uVar5 >> 5) << 3;
    auVar10._8_8_ = 0;
    auVar10._0_8_ = uVar23;
    if (SUB168(auVar10 * ZEXT816(8),8) != 0) {
      uVar14 = 0xffffffffffffffff;
    }
    lVar18 = operator new[](unsigned long, std::nothrow_t const&)(uVar14,PTR__ZSt7nothrow_02cb9a80);
    *(long *)(param_1 + 0x1ba0) = lVar18;
    if (lVar18 == 0) {
      Aska::ObjectManagerJobDispatcher::Sleep()(lVar20);
      uVar13 = *(undefined8 *)PTR__ZN4Aska6Global20m_pMessageDispatcherE_02cb77c8;
      goto code_r0x011d6110;
    }
  }
  else {
    lVar18 = *(long *)(param_1 + 0x1ba0);
    uVar5 = iVar25 + 0x3e;
    if (-1 < (int)(iVar25 + 0x1fU)) {
      uVar5 = iVar25 + 0x1fU;
    }
    uVar23 = (long)((ulong)uVar5 << 0x20) >> 0x25;
  }
  memset(lVar18,0,uVar23 << 3);
  Aska::ObjectManagerJobDispatcher::SetPreliminarilyPrepareBasicParameter(Aska::LightManager*, unsigned long*)(lVar20,uVar13,*(long *)(param_1 + 0x1ba0));
  if (0 < iVar25) {
    uVar23 = 0;
    iVar26 = 0;
    do {
      iVar27 = iVar26;
      if (iVar26 < iVar25) {
        iVar27 = iVar26 + 0x40;
        if (iVar25 <= iVar26 + 0x40) {
          iVar27 = iVar25;
        }
        uVar14 = Aska::ObjectManagerJobDispatcher::Dispatch_PreliminarilyPrepare(Aska::RenderableObject**, int, int)(lVar20,*(long *)(param_1 + 0x1ac8) + (long)iVar26 * 8,iVar26,
                                 iVar27 + -1);
        if ((uVar14 & 1) == 0) {
          iVar27 = iVar26;
        }
      }
      iVar26 = iVar27;
      if ((int)uVar23 < iVar26) {
        uVar14 = (uVar23 & 0xffffffff) << 1;
        uVar23 = (ulong)(int)uVar23;
        iVar27 = 0;
        do {
          uVar15 = *(ulong *)(*(long *)(param_1 + 0x1ba0) + (long)((int)uVar23 >> 5) * 8) >>
                   (uVar14 & 0x3e);
          if ((uVar15 & 3) == 0) break;
          uVar5 = (uint)uVar15 & 3;
          plVar22 = *(long **)(*(long *)(param_1 + 0x1ac8) + uVar23 * 8);
          if (uVar5 == 3) {
code_r0x0225e5f4:
            if ((*(uint *)(plVar22 + 0x33) & 0x200008) == 0x200000) {
              (**(code **)(*plVar22 + 0x298))(plVar22);
            }
          }
          else if (uVar5 == 2) {
            lVar18 = plVar22[0x3a];
            if ((lVar18 == 0) &&
               (lVar18 = Aska::RenderContextServer::GetRenderContext(int)(*(undefined8 *)(param_1 + 0x1000),(int)plVar22[0x38]),
               lVar18 == 0)) goto code_r0x0225e5f4;
            plVar22[0x3a] = lVar18;
            *(undefined4 *)((long)plVar22 + 0x1cc) = 0;
            *(ushort *)((long)plVar22 + 0x1b5) = *(ushort *)((long)plVar22 + 0x1b5) | 1;
          }
          uVar23 = uVar23 + 1;
          if ((long)iVar26 <= (long)uVar23) break;
          uVar14 = uVar14 + 2;
          bVar9 = iVar27 < 1;
          iVar27 = iVar27 + 1;
        } while (bVar9);
      }
    } while ((int)uVar23 < iVar25);
  }
  Aska::ObjectManagerJobDispatcher::Sleep()(lVar20);
  uVar13 = *(undefined8 *)PTR__ZN4Aska6Global20m_pMessageDispatcherE_02cb77c8;
code_r0x011d6110:
  (*(code *)PTR__ZN4Aska23SimpleMessageDispatcher18ResumeWorkerThreadEv_02ca3078)(uVar13);
  return;
}

// ==== Aska::ObjectManager::UpdateRenderLayerCondition()
// vaddr 0x215e660 | ghidra 0x225e660 | size 52 | symbol _ZN4Aska13ObjectManager26UpdateRenderLayerConditionEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13ObjectManager26UpdateRenderLayerConditionEv(long param_1)

{
  byte bVar1;
  byte bVar2;
  
  bVar1 = *(byte *)(*(long *)(param_1 + 0x4478) + 0x21);
  *(byte *)(param_1 + 0x3f1c) = bVar1;
  if ((*(char *)(param_1 + 0x3f1d) != '\0') &&
     (bVar2 = *(byte *)(*(long *)(param_1 + 0x4478) + 0x1e), bVar2 < bVar1)) {
    *(byte *)(param_1 + 0x3f1c) = bVar2;
  }
  return;
}

// ==== Aska::ObjectManager::UpdateMultiDraw()
// vaddr 0x215e694 | ghidra 0x225e694 | size 204 | symbol _ZN4Aska13ObjectManager15UpdateMultiDrawEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13ObjectManager15UpdateMultiDrawEv(long param_1)

{
  ulong *puVar1;
  ulong uVar2;
  uint uVar3;
  long lVar4;
  long lVar5;
  byte *pbVar6;
  long lVar7;
  ulong *puVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  ulong uVar17;
  ulong uVar18;
  ulong uVar19;
  
  uVar3 = **(uint **)(param_1 + 0x4478);
  if ((int)uVar3 < 1) {
    iVar9 = 0;
    goto code_r0x0225e754;
  }
  lVar5 = *(long *)(*(uint **)(param_1 + 0x4478) + 2);
  if (uVar3 < 8) {
    lVar7 = 0;
code_r0x0225e730:
    iVar9 = 0;
  }
  else {
    uVar2 = 8;
    if ((uVar3 & 7) != 0) {
      uVar2 = (ulong)(uVar3 & 7);
    }
    lVar7 = uVar3 - uVar2;
    if (lVar7 == 0) goto code_r0x0225e730;
    puVar8 = (ulong *)(lVar5 + 9);
    iVar9 = 0;
    iVar10 = 0;
    iVar11 = 0;
    iVar12 = 0;
    iVar13 = 0;
    iVar14 = 0;
    iVar15 = 0;
    iVar16 = 0;
    lVar4 = lVar7;
    do {
      puVar1 = puVar8 + -1;
      uVar18 = *puVar8;
      lVar4 = lVar4 + -8;
      puVar8 = puVar8 + 2;
      uVar17 = *puVar1 & 0xffffffffffff00ff;
      uVar19 = CONCAT44((int)(uVar17 >> 0x20),CONCAT22((short)(*puVar1 >> 0x10),(short)uVar17)) &
               0xffffffff00ffffff;
      uVar17 = CONCAT26((short)(uVar19 >> 0x30),CONCAT24((short)(uVar17 >> 0x20),(int)uVar19)) &
               0xff00ffffffffff;
      uVar19 = uVar18 & 0xffffffffffff00ff;
      uVar18 = CONCAT44((int)(uVar19 >> 0x20),CONCAT22((short)(uVar18 >> 0x10),(short)uVar19)) &
               0xffffffff00ffffff;
      uVar19 = CONCAT26((short)(uVar18 >> 0x30),CONCAT24((short)(uVar19 >> 0x20),(int)uVar18)) &
               0xff00ffffffffff;
      uVar17 = CONCAT26((ushort)(uVar17 >> 0x33),
                        CONCAT24((ushort)(uVar17 >> 0x20) >> 3,
                                 CONCAT22((ushort)(uVar17 >> 0x10) >> 3,(ushort)uVar17 >> 3))) &
               0x1000100010001;
      uVar19 = CONCAT26((ushort)(uVar19 >> 0x33),
                        CONCAT24((ushort)(uVar19 >> 0x20) >> 3,
                                 CONCAT22((ushort)(uVar19 >> 0x10) >> 3,(ushort)uVar19 >> 3))) &
               0x1000100010001;
      iVar9 = iVar9 + (uint)(ushort)uVar17;
      iVar10 = iVar10 + (uint)(ushort)(uVar17 >> 0x10);
      iVar11 = iVar11 + (uint)(ushort)(uVar17 >> 0x20);
      iVar12 = iVar12 + (uint)(ushort)(uVar17 >> 0x30);
      iVar13 = iVar13 + (uint)(ushort)uVar19;
      iVar14 = iVar14 + (uint)(ushort)(uVar19 >> 0x10);
      iVar15 = iVar15 + (uint)(ushort)(uVar19 >> 0x20);
      iVar16 = iVar16 + (uint)(ushort)(uVar19 >> 0x30);
    } while (lVar4 != 0);
    iVar9 = iVar13 + iVar9 + iVar14 + iVar10 + iVar15 + iVar11 + iVar16 + iVar12;
    if (uVar2 == 0) goto code_r0x0225e754;
  }
  lVar4 = (ulong)uVar3 - lVar7;
  pbVar6 = (byte *)(lVar5 + lVar7 * 2 + 1);
  do {
    lVar4 = lVar4 + -1;
    iVar9 = iVar9 + (*pbVar6 >> 3 & 1);
    pbVar6 = pbVar6 + 2;
  } while (lVar4 != 0);
code_r0x0225e754:
  *(int *)(param_1 + 0x45d0) = iVar9;
  return;
}

// ==== Aska::ObjectManager::OnPostPaint()
// vaddr 0x215e760 | ghidra 0x225e760 | size 3624 | symbol _ZN4Aska13ObjectManager11OnPostPaintEv | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Possible PIC construction at 0x0225f558: Changing call to branch */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska13ObjectManager11OnPostPaintEv(long param_1)

{
  ushort *puVar1;
  undefined1 *puVar2;
  int iVar3;
  ushort uVar4;
  ushort uVar5;
  ushort uVar6;
  bool bVar7;
  float fVar8;
  undefined *puVar9;
  undefined *puVar10;
  undefined *puVar11;
  ulong uVar12;
  undefined8 uVar13;
  byte bVar14;
  byte bVar15;
  int iVar16;
  ulong uVar17;
  undefined8 *puVar18;
  long *plVar19;
  undefined8 uVar20;
  long lVar21;
  long lVar22;
  ulong uVar23;
  ulong uVar24;
  long lVar25;
  long *plVar26;
  byte *pbVar27;
  long lVar28;
  long lVar29;
  undefined8 uVar30;
  long lVar31;
  uint uVar32;
  long lVar33;
  short sVar34;
  long lVar35;
  float fVar36;
  float fVar37;
  float fVar38;
  undefined8 uStack_b0;
  undefined8 uStack_a8;
  long lStack_a0;
  undefined8 uStack_98;
  
  if (*(char *)(param_1 + 0x3f13) != '\0') {
    *(char *)(param_1 + 0x3f13) = '\0';
    lVar22 = *(long *)PTR__ZN4Aska6Global14m_pLIBLManagerE_02cc46a8;
    if (*(int *)(lVar22 + 0x88) != 0) {
      Aska::ObjectManagerJobDispatcher::WaitIdle()(*(undefined8 *)PTR__ZN4Aska6Global29m_pObjectManagerJobDispatcherE_02cb8e98);
      Aska::LIBLManager::SetResult(Aska::RenderableObject**, int)(lVar22,*(undefined8 *)(param_1 + 0x18a0),*(undefined4 *)(param_1 + 0x18a8));
      Aska::LIBLManager::MakeEffectiveLIBLList()(lVar22);
    }
    *(undefined1 *)(param_1 + 0x3f09) = 1;
    *(undefined1 *)(param_1 + 0x3f11) = 1;
    uVar32 = *(uint *)(param_1 + 0x4598);
    uVar23 = (ulong)uVar32;
    if (0 < (int)uVar32) {
      puVar18 = (undefined8 *)(param_1 + 0x4498);
      do {
        (**(code **)(*(long *)*puVar18 + 0x2b8))();
        uVar23 = uVar23 - 1;
        puVar18 = puVar18 + 1;
      } while (uVar23 != 0);
    }
    Aska::ShadowManagerRegistry::DeleteShadowTextures()(*(undefined8 *)(param_1 + 0x104f0));
    uVar4 = *(ushort *)(param_1 + 0x3efc);
    uVar23 = (ulong)uVar4;
    uVar20 = *(undefined8 *)PTR__ZN4Aska6Global22m_pRenderTargetManagerE_02cbfa00;
    if (uVar23 != 0) {
      uVar24 = 0;
      pbVar27 = (byte *)(param_1 + 0x8e32);
      do {
        if ((*pbVar27 >> 3 & 1) == 0) {
          Aska::RenderTargetManagerGL::ReleaseID(unsigned int)(uVar20,(int)uVar24 + 0x81);
        }
        uVar24 = uVar24 + 1;
        pbVar27 = pbVar27 + 0x48;
      } while (uVar23 != uVar24);
    }
    Aska::RenderTargetManagerGL::AcceptRenderTargetWaiting()(uVar20);
    uVar30 = *(undefined8 *)PTR__ZN4Aska6Global15m_pLightManagerE_02cc1770;
    Aska::LightManager::PrepareForTexture()(uVar30);
    if (0 < (int)uVar32) {
      lVar22 = (long)(int)uVar32 + 0x892;
      do {
        (**(code **)(**(long **)(param_1 + lVar22 * 8) + 0x2c0))();
        lVar21 = lVar22 + -0x892;
        lVar22 = lVar22 + -1;
      } while (1 < lVar21);
    }
    if (uVar4 != 0) {
      lVar25 = 0;
      lVar21 = 0;
      uVar24 = 0;
      lVar33 = param_1 + 0x8e32;
      lVar35 = param_1 + 0x9ff0;
      lVar22 = 0x8df0;
      do {
        if ((*(byte *)(lVar33 + lVar21) >> 3 & 1) == 0) {
          lVar28 = lVar35 + lVar21;
          memcpy(lVar28,param_1 + lVar22,0x48);
          uVar17 = Aska::ShadowMapResolver::CreateBuffers(unsigned int, int, int, int, int, Aska::APXFORMAT)(*(undefined8 *)(lVar35 + lVar25 + 0x1200),(int)uVar24 + 0x81,
                                   *(undefined4 *)(lVar28 + 0x38),*(undefined2 *)(lVar28 + 4),
                                   *(undefined2 *)(lVar35 + lVar21),*(undefined2 *)(lVar28 + 2),
                                   *(undefined4 *)(lVar28 + 0xc));
          if ((uVar17 & 1) != 0) {
            *(ushort *)(lVar33 + lVar21) = *(ushort *)(lVar33 + lVar21) | 8;
          }
        }
        uVar24 = uVar24 + 1;
        lVar22 = lVar22 + 0x48;
        lVar21 = lVar21 + 0x48;
        lVar25 = lVar25 + 8;
      } while (uVar23 != uVar24);
    }
    uVar32 = *(uint *)(param_1 + 0x3ef4);
    if (0 < (int)uVar32) {
      uVar24 = 0;
      do {
        lVar22 = uVar24 * 8;
        uVar24 = uVar24 + 1;
        *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x1ac8) + lVar22) + 0x1a8) = 0;
      } while (uVar32 != uVar24);
    }
    puVar9 = PTR__ZN4Aska6Global20m_pMessageDispatcherE_02cb77c8;
    lVar22 = *(long *)PTR__ZN4Aska6Global29m_pObjectManagerJobDispatcherE_02cb8e98;
    if (lVar22 == 0) {
      uVar20 = *(undefined8 *)PTR__ZN4Aska6Global21m_pPerformanceCounterE_02cc3ad8;
    }
    else {
      Aska::SimpleMessageDispatcher::SuspendWorkerThread()(*(undefined8 *)PTR__ZN4Aska6Global20m_pMessageDispatcherE_02cb77c8);
      Aska::ObjectManagerJobDispatcher::ChangeMode(int)(lVar22,3);
      puVar11 = PTR__ZN4Aska6Global21m_pPerformanceCounterE_02cc3ad8;
      Aska::PerformanceCounter::Mark(int)(*(undefined8 *)PTR__ZN4Aska6Global21m_pPerformanceCounterE_02cc3ad8,3);
      Aska::PerformanceCounter::Mark(int)(*(undefined8 *)puVar11,4);
      puVar10 = PTR__ZN4Aska13ObjectManager17m_pBackBufferSyncE_02cb8770;
      lVar21 = *(long *)(*(long *)PTR__ZN4Aska6Global16m_pCameraManagerE_02cb7d08 + 0xff0);
      if ((lVar21 == 0) || (*(int *)(param_1 + 0x3ef4) == 0)) {
        Aska::ObjectManagerJobDispatcher::Sleep()(lVar22);
        Aska::SimpleMessageDispatcher::ResumeWorkerThread()(*(undefined8 *)puVar9);
        puVar18 = *(undefined8 **)(param_1 + 0x4458);
        if (puVar18 != (undefined8 *)0x0) {
          (**(code **)*puVar18)(puVar18,0);
        }
        uVar20 = *(undefined8 *)puVar11;
      }
      else {
        *(undefined1 *)(param_1 + 0x3f10) = 1;
        *(undefined1 *)(*(long *)puVar10 + 0xb8) = 1;
        uStack_a8 = 0;
        lStack_a0 = 0;
        uStack_b0 = 0;
        uStack_98 = uVar30;
        Aska::RenderThread::WaitDeviceReset()(*(undefined8 *)(param_1 + 0x4480));
        Aska::RenderThread::AddBeginRender()(*(undefined8 *)(param_1 + 0x4480));
        if (*(int *)(param_1 + 0x1b08) != 0) {
          uStack_b0._0_4_ = CONCAT13(3,(undefined3)uStack_b0);
          Aska::ObjectManager::TraversePaintingListNoResolve(Aska::RENDERINFO*, int, Aska::RenderableObject**, int, int, Aska::Camera*, bool)(param_1,&uStack_b0,1,*(undefined8 *)(param_1 + 0x1ae0),
                          *(int *)(param_1 + 0x1b08),5,lVar21,0);
        }
        if (uVar4 != 0) {
          uVar24 = 0;
          bVar7 = false;
          lVar25 = 0x8e32;
          lVar33 = 0x9ff0;
          lVar35 = 0xa031;
          lVar28 = 0xa010;
          uStack_b0 = uStack_b0 & 0xfffffffff8ffffff | 0x2000000;
          do {
            if (((*(byte *)(param_1 + lVar25) >> 3 & 1) != 0) &&
               (lVar31 = param_1 + 0x18b0 + uVar24 * 2, *(short *)(lVar31 + 0x558) != 0)) {
              if ((*(byte *)(param_1 + lVar35) >> 1 & 1) == 0) {
                if (bVar7) {
                  bVar7 = true;
                }
                else {
                  bVar7 = true;
                  Aska::RenderThread::AddEnableFastZ(bool)(*(undefined8 *)(param_1 + 0x4480),1);
                }
              }
              else {
                if (bVar7) {
                  Aska::RenderThread::AddEnableFastZ(bool)(*(undefined8 *)(param_1 + 0x4480),0);
                }
                bVar7 = false;
              }
              uVar17 = uVar24 + 0x81;
              Aska::RenderThread::AddChangeRenderTarget(unsigned int, Aska::MULTIPASS_ENVIRONMENT*)(*(undefined8 *)(param_1 + 0x4480),uVar17 & 0xffffffff,param_1 + lVar33
                             );
              bVar14 = Aska::RenderTargetManagerGL::IsCommandBufferAvailable(unsigned int) const(uVar20,uVar17 & 0xffffffff);
              uVar12 = uStack_b0;
              bVar15 = uStack_b0._3_1_;
              uStack_b0 = CONCAT62(uStack_b0._2_6_,(short)uVar17);
              uStack_b0._0_4_ =
                   CONCAT13(bVar15 & 0xc0 | bVar15 & 0x1f | (bVar14 & 1) << 5,(undefined3)uStack_b0)
              ;
              lStack_a0 = *(undefined8 *)(param_1 + lVar28);
              uStack_b0._5_3_ = SUB83(uVar12,5);
              uStack_b0._0_5_ =
                   CONCAT14((byte)((ushort)*(undefined2 *)(param_1 + lVar25 + 0x1200) >> 0xb) & 1 |
                            *(byte *)(param_1 + lVar35),(undefined4)uStack_b0);
              Aska::ObjectManager::TraversePaintingListNoResolve(Aska::RENDERINFO*, int, Aska::RenderableObject**, int, int, Aska::Camera*, bool)(param_1,&uStack_b0,0,*(undefined8 *)(param_1 + 0x18b0 + uVar24 * 8),
                              *(undefined2 *)(lVar31 + 0x558),4,lVar21,0);
              Aska::RenderThread::AddFinishRenderTarget(unsigned int, int, int)(*(undefined8 *)(param_1 + 0x4480),uVar17 & 0xffffffff,2,0);
            }
            uVar24 = uVar24 + 1;
            lVar25 = lVar25 + 0x48;
            lVar33 = lVar33 + 0x48;
            lVar35 = lVar35 + 0x48;
            lVar28 = lVar28 + 0x48;
          } while (uVar23 != uVar24);
          if (!bVar7) {
            Aska::RenderThread::AddEnableFastZ(bool)(*(undefined8 *)(param_1 + 0x4480),1);
          }
        }
        lStack_a0 = 0;
        fVar36 = (float)exp2f(-*(float *)(*(long *)(lVar21 + 0xe10) + 0x44));
        fVar8 = _UNK_027e51a0;
        fVar36 = fVar36 * _UNK_027e51a0;
        iVar16 = Aska::CameraFilterManager::GetISO()(*(undefined8 *)(lVar21 + 0xe30));
        fVar38 = _UNK_027e5198;
        *(float *)(param_1 + 0x3f18) = fVar36 * ((float)iVar16 / _UNK_027e5198) * 4.0;
        fVar36 = (float)exp2f(-*(float *)(*(long *)(lVar21 + 0xe10) + 0x44));
        iVar16 = Aska::CameraFilterManager::GetISO()(*(undefined8 *)(lVar21 + 0xe30));
        lVar25 = 0;
        sVar34 = 0;
        fVar36 = _UNK_029cc840 / (fVar36 * fVar8 * ((float)iVar16 / fVar38));
        do {
          lVar33 = param_1 + lVar25 * 4;
          if (*(int *)(lVar33 + 0x1c08) == 0) {
            puVar1 = (ushort *)(param_1 + lVar25 * 0x48 + 0x4632);
            if ((*(byte *)puVar1 >> 6 & 1) != 0) {
              Aska::RenderTargetManagerGL::ReleaseID(unsigned int)(*(undefined8 *)PTR__ZN4Aska6Global22m_pRenderTargetManagerE_02cbfa00,
                              lVar25 + 1U & 0xffffffff);
              *puVar1 = *puVar1 & 0xffb7;
            }
          }
          else {
            lVar28 = param_1 + lVar25 * 0x48;
            lStack_a0 = *(long *)(lVar28 + 0x4610);
            uVar23 = lVar25 + 1;
            puVar1 = (ushort *)(lVar28 + 0x4632);
            uVar4 = *puVar1;
            uVar32 = (uint)uVar4;
            lVar35 = param_1 + lVar25 * 0x48;
            if ((uVar4 >> 3 & 1) == 0) {
              lVar29 = param_1 + lVar25 * 0x48;
              lVar35 = lVar35 + 0x45f0;
              lVar31 = lVar29 + 0x69f0;
              uVar32 = uVar4 | 8;
              *puVar1 = (ushort)uVar32;
              memcpy(lVar31,lVar35,0x48);
              memcpy(lVar29 + 0xbcf0,lVar35,0x48);
              *(undefined4 *)(lVar29 + 0xbd04) = 0;
              memcpy(lVar29 + 0xe0f0,lVar35,0x48);
              *(uint *)(lVar29 + 0xe100) = *(uint *)(lVar29 + 0xe100) & 0xfffffff9;
            }
            else {
              lVar31 = lVar35 + 0x69f0;
            }
            Aska::RenderThread::AddChangeRenderTarget(unsigned int, Aska::MULTIPASS_ENVIRONMENT*)(*(undefined8 *)(param_1 + 0x4480),(uint)uVar23 | (uVar32 & 0x80) << 0x11
                            ,lVar31);
            Aska::RenderThread::AddEnableFastZ(bool)(*(undefined8 *)(param_1 + 0x4480),1);
            lVar35 = lStack_a0;
            fVar37 = 1.0;
            if (*(char *)puVar1 < '\0') {
              fVar37 = (float)exp2f(-*(float *)(*(long *)(lStack_a0 + 0xe10) + 0x44));
              iVar16 = Aska::CameraFilterManager::GetISO()(*(undefined8 *)(lVar35 + 0xe30));
              fVar37 = fVar37 * fVar8 * ((float)iVar16 / fVar38) * 4.0;
            }
            Aska::RenderThread::AddExposureScale(float, float)(fVar37,fVar36,*(undefined8 *)(param_1 + 0x4480));
            bVar14 = Aska::RenderTargetManagerGL::IsCommandBufferAvailable(unsigned int) const(uVar20,uVar23 & 0xffffffff);
            uVar24 = uStack_b0;
            bVar15 = uStack_b0._3_1_;
            uStack_b0 = CONCAT62(uStack_b0._2_6_,sVar34 + 1);
            uVar30 = uStack_b0;
            iVar16 = *(int *)(param_1 + lVar25 * 4 + 0x1ea8);
            iVar3 = *(int *)(lVar33 + 0x1c08);
            uStack_b0._4_4_ = SUB84(uVar24,4);
            uStack_b0._0_3_ = (undefined3)uVar30;
            uStack_b0 = CONCAT44(uStack_b0._4_4_,
                                 CONCAT13(bVar15 & 0xc0 | bVar15 & 0x18 | (bVar14 & 1) << 5,
                                          (undefined3)uStack_b0)) | 0x1000000;
            lVar33 = param_1 + lVar25 * 0x10;
            plVar19 = (long *)(lVar33 + 0x10a0);
            Aska::ObjectManager::TraversePaintingListNoResolve(Aska::RENDERINFO*, int, Aska::RenderableObject**, int, int, Aska::Camera*, bool)(param_1,&uStack_b0,0,*(undefined8 *)(lVar33 + 0x10a0),iVar16,1,lVar21,0)
            ;
            Aska::RenderThread::AddEnableFastZ(bool)(*(undefined8 *)(param_1 + 0x4480),0);
            bVar15 = uStack_b0._3_1_ & 0xf8;
            uStack_b0 = uStack_b0 & 0xfffffffff8ffffff;
            uVar24 = (ulong)*(byte *)(param_1 + lVar25 + 0x3e70);
            if (uVar24 == 0) {
              Aska::ObjectManager::TraversePaintingList(Aska::RENDERINFO*, int, Aska::RenderableObject**, int, int, int, Aska::Camera*, bool)(param_1,&uStack_b0,0,*plVar19 + (long)iVar16 * 8,uVar23 & 0xffffffff,
                              iVar3 - iVar16,0,0);
            }
            else {
              lVar33 = lVar25 * 0x38 + 0x226e;
              lVar35 = lVar25 * 0x38 + 0x2268;
              do {
                uVar17 = uStack_b0;
                puVar2 = (undefined1 *)(param_1 + lVar33);
                bVar14 = 5;
                if (puVar2[-1] != '\x01') {
                  bVar14 = 0;
                }
                uStack_b0._0_4_ =
                     CONCAT13(bVar14 | bVar15 & 0xe0 | (puVar2[-2] & 3) << 3,(undefined3)uStack_b0);
                uVar30 = uStack_b0;
                uStack_b0._6_2_ = SUB82(uVar17,6);
                uStack_b0._0_5_ = (undefined5)uVar30;
                uStack_b0._0_6_ = CONCAT15(*puVar2,(undefined5)uStack_b0);
                uVar4 = *(ushort *)(param_1 + lVar35);
                Aska::ObjectManager::TraversePaintingList(Aska::RENDERINFO*, int, Aska::RenderableObject**, int, int, int, Aska::Camera*, bool)(param_1,&uStack_b0,0,*plVar19 + (ulong)uVar4 * 8,uVar23 & 0xffffffff
                                ,(uint)((ushort *)(param_1 + lVar35))[1] - (uint)uVar4,0,0);
                uVar24 = uVar24 - 1;
                lVar33 = lVar33 + 8;
                lVar35 = lVar35 + 8;
                bVar15 = uStack_b0._3_1_;
              } while (uVar24 != 0);
              uStack_b0 = uStack_b0 & 0xffffffffe7ffffff;
            }
            if ((*(byte *)(lVar28 + 0x4633) >> 2 & 1) == 0) {
              Aska::RenderThread::AddFinishRenderTarget(unsigned int, int, int)(*(undefined8 *)(param_1 + 0x4480),uVar23 & 0xffffffff,1,
                              -(uint)*(byte *)(param_1 + lVar25 * 0x48 + 0x4630));
            }
          }
          lVar25 = lVar25 + 1;
          sVar34 = sVar34 + 1;
        } while (lVar25 != 0x80);
        uVar32 = *(uint *)(param_1 + 0x3f20);
        if ((int)uVar32 < 2) {
          uVar32 = 1;
        }
        if (0 < (int)uVar32) {
          uVar23 = 0;
          lVar21 = 0x20ae;
          lVar25 = 0x20a8;
          uVar30 = *(undefined8 *)(*(long *)PTR__ZN4Aska6Global16m_pCameraManagerE_02cb7d08 + 0xff0)
          ;
          do {
            uStack_b0 = (ulong)CONCAT51(uStack_b0._3_5_,(char)uVar23) << 0x10;
            *PTR__ZN4Aska6Camera15m_cActiveTileNoE_02cbb2c8 = (char)uVar23;
            puVar1 = (ushort *)(param_1 + uVar23 * 0x48 + 0xb432);
            uVar4 = *puVar1;
            if ((uVar4 >> 3 & 1) == 0) {
              lVar35 = param_1 + uVar23 * 0x48;
              *puVar1 = uVar4 | 8;
              lVar33 = lVar35 + 0xb630;
              memcpy(lVar33,lVar35 + 0xb3f0,0x48);
              memcpy(lVar35 + 0xb870,lVar35 + 0xb3f0,0x48);
              *(undefined4 *)(lVar35 + 0xb884) = 0;
              memcpy(lVar35 + 0xbab0,lVar33,0x48);
              *(uint *)(lVar35 + 0xbac0) = *(uint *)(lVar35 + 0xbac0) & 0xfffffff9;
            }
            else {
              lVar33 = param_1 + uVar23 * 0x48 + 0xb630;
            }
            lVar35 = param_1 + uVar23 * 4;
            Aska::RenderThread::AddChangeRenderTarget(unsigned int, Aska::MULTIPASS_ENVIRONMENT*)(*(undefined8 *)(param_1 + 0x4480),
                            *(uint *)(lVar35 + 0x3f28) | (int)uVar23 << 0x10,lVar33);
            Aska::RenderThread::AddEnableFastZ(bool)(*(undefined8 *)(param_1 + 0x4480),1);
            Aska::RenderThread::AddExposureScale(float, float)(*(float *)(param_1 + 0x3f18) /
                            (*(float *)PTR__ZN4Aska13ObjectManager17m_fGlobalHDRRangeE_02cbb9f0 *
                            8.0),fVar36,*(undefined8 *)(param_1 + 0x4480));
            bVar15 = Aska::RenderTargetManagerGL::IsCommandBufferAvailable(unsigned int) const(uVar20,*(undefined4 *)(lVar35 + 0x3f28));
            iVar16 = *(int *)(lVar35 + 0x1bc8);
            iVar3 = *(int *)(lVar35 + 0x1e88);
            uStack_b0 = CONCAT44(uStack_b0._4_4_,
                                 CONCAT13(uStack_b0._3_1_ & 0xc0 |
                                          uStack_b0._3_1_ & 0x18 | (bVar15 & 1) << 5,
                                          (undefined3)uStack_b0)) | 0x1000000;
            lVar33 = param_1 + uVar23 * 0x10;
            plVar19 = (long *)(lVar33 + 0x1020);
            Aska::ObjectManager::TraversePaintingListNoResolve(Aska::RENDERINFO*, int, Aska::RenderableObject**, int, int, Aska::Camera*, bool)(param_1,&uStack_b0,1,*(undefined8 *)(lVar33 + 0x1020),iVar3,1,uVar30,0);
            Aska::RenderThread::AddEnableFastZ(bool)(*(undefined8 *)(param_1 + 0x4480),0);
            bVar15 = uStack_b0._3_1_ & 0xf8;
            uStack_b0 = uStack_b0 & 0xfffffffff8ffffff;
            uVar24 = (ulong)*(byte *)(param_1 + uVar23 + 0x3e68);
            lVar33 = lVar21;
            lVar35 = lVar25;
            if (uVar24 == 0) {
              Aska::ObjectManager::TraversePaintingList(Aska::RENDERINFO*, int, Aska::RenderableObject**, int, int, int, Aska::Camera*, bool)(param_1,&uStack_b0,1,*plVar19 + (long)iVar3 * 8,uVar23 & 0xffffffff,
                              iVar16 - iVar3,0,uVar30);
            }
            else {
              do {
                uVar17 = uStack_b0;
                puVar2 = (undefined1 *)(param_1 + lVar33);
                bVar14 = 5;
                if (puVar2[-1] != '\x01') {
                  bVar14 = 0;
                }
                uStack_b0._0_4_ =
                     CONCAT13(bVar14 | bVar15 & 0xe0 | (puVar2[-2] & 3) << 3,(undefined3)uStack_b0);
                uVar13 = uStack_b0;
                uStack_b0._6_2_ = SUB82(uVar17,6);
                uStack_b0._0_5_ = (undefined5)uVar13;
                uStack_b0._0_6_ = CONCAT15(*puVar2,(undefined5)uStack_b0);
                uVar4 = *(ushort *)(param_1 + lVar35);
                Aska::ObjectManager::TraversePaintingList(Aska::RENDERINFO*, int, Aska::RenderableObject**, int, int, int, Aska::Camera*, bool)(param_1,&uStack_b0,1,*plVar19 + (ulong)uVar4 * 8,uVar23 & 0xffffffff
                                ,(uint)((ushort *)(param_1 + lVar35))[1] - (uint)uVar4,0,uVar30);
                uVar24 = uVar24 - 1;
                lVar33 = lVar33 + 8;
                lVar35 = lVar35 + 8;
                bVar15 = uStack_b0._3_1_;
              } while (uVar24 != 0);
              uStack_b0 = uStack_b0 & 0xffffffffe7ffffff;
            }
            uVar23 = uVar23 + 1;
            lVar21 = lVar21 + 0x38;
            lVar25 = lVar25 + 0x38;
          } while ((long)uVar23 < (long)(ulong)uVar32);
        }
        puVar9 = PTR__ZN4Aska6Global16m_pCameraManagerE_02cb7d08;
        if (*(int *)(param_1 + 0x1bc4) != 0) {
          lVar21 = *(long *)PTR__ZN4Aska6Global16m_pCameraManagerE_02cb7d08;
          *PTR__ZN4Aska6Camera15m_cActiveTileNoE_02cbb2c8 = 0xfe;
          uVar30 = *(undefined8 *)(lVar21 + 0xff0);
          uStack_b0 = CONCAT44((int)(uStack_b0 >> 0x20),CONCAT13(uStack_b0._3_1_,0xff0000)) &
                      0xfffffffff8ffffff;
          Aska::RenderThread::AddExposureScale(float, float)(0x3f800000,0x3f800000,*(undefined8 *)(param_1 + 0x4480));
          bVar15 = Aska::RenderTargetManagerGL::IsCommandBufferAvailable(unsigned int) const(uVar20,0xc1);
          uStack_b0._0_4_ =
               CONCAT13(uStack_b0._3_1_ & 0xc0 | uStack_b0._3_1_ & 0x1f | (bVar15 & 1) << 5,
                        (undefined3)uStack_b0);
          sVar34 = *(short *)(param_1 + 0x3f04);
          iVar16 = *(int *)(param_1 + 0x1bc4);
          if (sVar34 == 0) {
            lVar21 = *(long *)(param_1 + 0x1008);
          }
          else {
            uVar4 = *(ushort *)(param_1 + 0x3f02);
            uVar5 = *(ushort *)(param_1 + 0x3efe);
            uVar6 = *(ushort *)(param_1 + 0x3f06);
            Aska::ObjectManager::TraversePaintingList(Aska::RENDERINFO*, int, Aska::RenderableObject**, int, int, int, Aska::Camera*, bool)(param_1,&uStack_b0,1,*(undefined8 *)(param_1 + 0x1008),0,(ulong)uVar4,0,
                            uVar30);
            uStack_b0 = uStack_b0 & 0xfffffffff8ffffff | 0x4000000;
            Aska::ObjectManager::TraversePaintingList(Aska::RENDERINFO*, int, Aska::RenderableObject**, int, int, int, Aska::Camera*, bool)(param_1,&uStack_b0,1,*(long *)(param_1 + 0x1008) + (ulong)uVar4 * 8,0,
                            sVar34,0,uVar30);
            iVar16 = (iVar16 - (uint)uVar5) + (uint)uVar6;
            uStack_b0 = uStack_b0 & 0xfffffffff8ffffff;
            lVar21 = *(long *)(param_1 + 0x1008) + (long)(int)((uint)uVar5 - (uint)uVar6) * 8;
          }
          Aska::ObjectManager::TraversePaintingList(Aska::RENDERINFO*, int, Aska::RenderableObject**, int, int, int, Aska::Camera*, bool)(param_1,&uStack_b0,1,lVar21,0,iVar16,0,uVar30);
        }
        if ((*(byte *)(*(long *)(param_1 + 0xb418) + 0x1ed7) >> 2 & 1) != 0) {
          Aska::RenderThread::AddFinishRenderTarget(unsigned int, int, int)(*(undefined8 *)(param_1 + 0x4480),0xc1,1,0);
        }
        Aska::RenderThread::AddEndRender(Aska::INotify*)(*(undefined8 *)(param_1 + 0x4480),*(undefined8 *)(param_1 + 0x4458));
        Aska::RenderFinishCallbackThread::ReorderCallbacks()(*(undefined8 *)(*(long *)(param_1 + 0x4480) + 0x501d8));
        *(undefined1 *)(param_1 + 0x3f11) = 0;
        lVar21 = *(long *)(*(long *)(param_1 + 0x4480) + 0x501d8);
        *(undefined1 *)(lVar21 + 0x3c) = 1;
        DataMemoryBarrier(2,3);
        Aska::Semaphore::Signal() const(lVar21 + 0x18);
        Aska::CameraManager::UpdatePrevView()(*(undefined8 *)puVar9);
        fVar38 = (float)(**(code **)**(undefined8 **)PTR__ZN4Aska6Global8m_pVSyncE_02cbd460)
                                  (*(undefined8 **)PTR__ZN4Aska6Global8m_pVSyncE_02cbd460,0);
        if ((_UNK_027e519c < fVar38) && (uVar4 = *(ushort *)(param_1 + 0x3f00), (ulong)uVar4 != 0))
        {
          uVar23 = 0;
          do {
            plVar26 = *(long **)(*(long *)(param_1 + 0x1af0) + uVar23 * 8);
            plVar19 = (long *)(**(code **)(*plVar26 + 0x98))(plVar26);
            lVar21 = *plVar19;
            uVar23 = uVar23 + 1;
            plVar26[0xad] = plVar19[1];
            plVar26[0xac] = lVar21;
            lVar21 = plVar19[2];
            plVar26[0xaf] = plVar19[3];
            plVar26[0xae] = lVar21;
            lVar21 = plVar19[4];
            plVar26[0xb1] = plVar19[5];
            plVar26[0xb0] = lVar21;
            lVar21 = plVar19[6];
            plVar26[0xb3] = plVar19[7];
            plVar26[0xb2] = lVar21;
          } while (uVar4 != uVar23);
        }
        uVar32 = *(uint *)(param_1 + 0x3ef4);
        if (0 < (int)uVar32) {
          uVar23 = 0;
          do {
            lVar21 = uVar23 * 8;
            uVar23 = uVar23 + 1;
            puVar1 = (ushort *)(*(long *)(*(long *)(param_1 + 0x1ac8) + lVar21) + 0x1b5);
            *puVar1 = *puVar1 & 0xfff7;
          } while (uVar32 != uVar23);
        }
        Aska::ObjectManagerJobDispatcher::Sleep()(lVar22);
        Aska::SimpleMessageDispatcher::ResumeWorkerThread()(*(undefined8 *)PTR__ZN4Aska6Global20m_pMessageDispatcherE_02cb77c8);
        *(undefined1 *)(param_1 + 0x3f09) = 2;
        uVar20 = *(undefined8 *)PTR__ZN4Aska6Global21m_pPerformanceCounterE_02cc3ad8;
      }
    }
    (*(code *)PTR__ZN4Aska18PerformanceCounter3SetEi_02ca4c38)(uVar20,3);
    return;
  }
  puVar18 = *(undefined8 **)(param_1 + 0x4458);
  if (puVar18 != (undefined8 *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x0225f364. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)*puVar18)(puVar18,0);
    return;
  }
  return;
}

// ==== Aska::ObjectManager::TraversePaintingListNoResolve(Aska::RENDERINFO*, int, Aska::RenderableObject**, int, int, Aska::Camera*, bool)
// vaddr 0x215f588 | ghidra 0x225f588 | size 500 | symbol _ZN4Aska13ObjectManager29TraversePaintingListNoResolveEPNS_10RENDERINFOEiPPNS_16RenderableObjectEiiPNS_6CameraEb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13ObjectManager29TraversePaintingListNoResolveEPNS_10RENDERINFOEiPPNS_16RenderableObjectEiiPNS_6CameraEb
               (long param_1,undefined8 param_2,undefined4 param_3,long param_4,int param_5,
               undefined8 param_6,undefined8 param_7)

{
  uint uVar1;
  int iVar2;
  undefined1 auVar3 [16];
  long lVar4;
  undefined8 uVar5;
  ulong uVar6;
  ulong uVar7;
  int iVar8;
  int iVar9;
  ulong uVar10;
  
  if (param_5 != 0) {
    if (*(int *)(param_1 + 0x1ba8) < param_5) {
      *(int *)(param_1 + 0x1ba8) = param_5;
      if (*(long *)(param_1 + 0x1ba0) != 0) {
        operator delete[](void*)();
      }
      uVar1 = param_5 + 0x3e;
      if (-1 < (int)(param_5 + 0x1fU)) {
        uVar1 = param_5 + 0x1fU;
      }
      uVar10 = (long)((ulong)uVar1 << 0x20) >> 0x25;
      uVar6 = -(ulong)((uint)((int)uVar1 >> 5) >> 0x1f) & 0xfffffff800000000 |
              (ulong)(uint)((int)uVar1 >> 5) << 3;
      auVar3._8_8_ = 0;
      auVar3._0_8_ = uVar10;
      if (SUB168(auVar3 * ZEXT816(8),8) != 0) {
        uVar6 = 0xffffffffffffffff;
      }
      lVar4 = operator new[](unsigned long, std::nothrow_t const&)(uVar6,PTR__ZSt7nothrow_02cb9a80);
      *(long *)(param_1 + 0x1ba0) = lVar4;
      if (lVar4 == 0) {
        return;
      }
    }
    else {
      lVar4 = *(long *)(param_1 + 0x1ba0);
      uVar1 = param_5 + 0x3e;
      if (-1 < (int)(param_5 + 0x1fU)) {
        uVar1 = param_5 + 0x1fU;
      }
      uVar10 = (long)((ulong)uVar1 << 0x20) >> 0x25;
    }
    memset(lVar4,0,uVar10 << 3);
    uVar5 = *(undefined8 *)PTR__ZN4Aska6Global29m_pObjectManagerJobDispatcherE_02cb8e98;
    Aska::ObjectManagerJobDispatcher::SetPrepareForRenderingBasicParameter(Aska::RENDERINFO*, unsigned long*, Aska::Camera*)(uVar5,param_2,*(long *)(param_1 + 0x1ba0),param_7);
    if (0 < param_5) {
      uVar10 = 0;
      iVar9 = 0;
      do {
        iVar8 = iVar9;
        if (iVar9 < param_5) {
          iVar8 = param_5;
          if (iVar9 + 8 < param_5) {
            iVar8 = iVar9 + 8;
          }
          uVar6 = Aska::ObjectManagerJobDispatcher::Dispatch_PrepareForRendering(int, Aska::RenderableObject**, unsigned long)(uVar5,param_3,param_4 + (long)iVar9 * 8,
                                  (long)iVar9 | (ulong)(iVar8 - 1) << 0x20);
          if ((uVar6 & 1) == 0) {
            iVar8 = iVar9;
          }
        }
        iVar9 = iVar8;
        if ((int)uVar10 < iVar9) {
          iVar8 = 0;
          uVar6 = (uVar10 & 0xffffffff) << 1;
          uVar10 = (ulong)(int)uVar10;
          do {
            uVar7 = *(ulong *)(*(long *)(param_1 + 0x1ba0) + (long)((int)uVar10 >> 5) * 8) >>
                    (uVar6 & 0x3e);
            if ((uVar7 & 3) == 0) break;
            if (((uint)uVar7 & 3) == 2) {
              lVar4 = *(long *)(param_4 + uVar10 * 8);
              DataMemoryBarrier(2,3);
              iVar2 = 0;
              if (*(int *)(lVar4 + 0x1ac) != 0) {
                iVar2 = *(int *)(lVar4 + 0x1c0) / *(int *)(lVar4 + 0x1ac);
              }
              Aska::RenderThread::AddRenderQueue(Aska::RenderableObject*, Aska::RenderContext*, int)(*(undefined8 *)(param_1 + 0x4480),lVar4,
                              *(long *)(lVar4 + 0x1d0) + (long)*(int *)(lVar4 + 0x1cc) * 0x230,iVar2
                             );
              *(int *)(lVar4 + 0x1cc) = *(int *)(lVar4 + 0x1cc) + iVar2;
            }
            uVar10 = uVar10 + 1;
            if (0 < iVar8) break;
            iVar8 = iVar8 + 1;
            uVar6 = uVar6 + 2;
          } while ((long)uVar10 < (long)iVar9);
        }
      } while ((int)uVar10 < param_5);
    }
  }
  return;
}

// ==== Aska::ObjectManager::TraversePaintingList(Aska::RENDERINFO*, int, Aska::RenderableObject**, int, int, int, Aska::Camera*, bool)
// vaddr 0x215f77c | ghidra 0x225f77c | size 528 | symbol _ZN4Aska13ObjectManager20TraversePaintingListEPNS_10RENDERINFOEiPPNS_16RenderableObjectEiiiPNS_6CameraEb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13ObjectManager20TraversePaintingListEPNS_10RENDERINFOEiPPNS_16RenderableObjectEiiiPNS_6CameraEb
               (long param_1,undefined8 param_2,undefined4 param_3,long param_4,undefined4 param_5,
               int param_6,undefined8 param_7,undefined8 param_8)

{
  uint uVar1;
  int iVar2;
  undefined1 auVar3 [16];
  long lVar4;
  undefined8 uVar5;
  ulong uVar6;
  ulong uVar7;
  ulong uVar8;
  int iVar9;
  int iVar10;
  
  if (param_6 != 0) {
    if (*(int *)(param_1 + 0x1ba8) < param_6) {
      *(int *)(param_1 + 0x1ba8) = param_6;
      if (*(long *)(param_1 + 0x1ba0) != 0) {
        operator delete[](void*)();
      }
      uVar1 = param_6 + 0x3e;
      if (-1 < (int)(param_6 + 0x1fU)) {
        uVar1 = param_6 + 0x1fU;
      }
      uVar8 = (long)((ulong)uVar1 << 0x20) >> 0x25;
      uVar6 = -(ulong)((uint)((int)uVar1 >> 5) >> 0x1f) & 0xfffffff800000000 |
              (ulong)(uint)((int)uVar1 >> 5) << 3;
      auVar3._8_8_ = 0;
      auVar3._0_8_ = uVar8;
      if (SUB168(auVar3 * ZEXT816(8),8) != 0) {
        uVar6 = 0xffffffffffffffff;
      }
      lVar4 = operator new[](unsigned long, std::nothrow_t const&)(uVar6,PTR__ZSt7nothrow_02cb9a80);
      *(long *)(param_1 + 0x1ba0) = lVar4;
      if (lVar4 == 0) {
        return;
      }
    }
    else {
      lVar4 = *(long *)(param_1 + 0x1ba0);
      uVar1 = param_6 + 0x3e;
      if (-1 < (int)(param_6 + 0x1fU)) {
        uVar1 = param_6 + 0x1fU;
      }
      uVar8 = (long)((ulong)uVar1 << 0x20) >> 0x25;
    }
    memset(lVar4,0,uVar8 << 3);
    uVar5 = *(undefined8 *)PTR__ZN4Aska6Global29m_pObjectManagerJobDispatcherE_02cb8e98;
    Aska::ObjectManagerJobDispatcher::SetPrepareForRenderingBasicParameter(Aska::RENDERINFO*, unsigned long*, Aska::Camera*)(uVar5,param_2,*(long *)(param_1 + 0x1ba0),param_8);
    if (0 < param_6) {
      uVar8 = 0;
      iVar10 = 0;
      do {
        iVar9 = iVar10;
        if (iVar10 < param_6) {
          iVar9 = param_6;
          if (iVar10 + 8 < param_6) {
            iVar9 = iVar10 + 8;
          }
          uVar6 = Aska::ObjectManagerJobDispatcher::Dispatch_PrepareForRendering(int, Aska::RenderableObject**, unsigned long)(uVar5,param_3,param_4 + (long)iVar10 * 8,
                                  (long)iVar10 | (ulong)(iVar9 - 1) << 0x20);
          if ((uVar6 & 1) == 0) {
            iVar9 = iVar10;
          }
        }
        iVar10 = iVar9;
        if ((int)uVar8 < iVar10) {
          iVar9 = 0;
          uVar6 = (uVar8 & 0xffffffff) << 1;
          uVar8 = (ulong)(int)uVar8;
          do {
            uVar7 = *(ulong *)(*(long *)(param_1 + 0x1ba0) + (long)((int)uVar8 >> 5) * 8) >>
                    (uVar6 & 0x3e);
            if ((uVar7 & 3) == 0) break;
            if (((uint)uVar7 & 3) == 2) {
              lVar4 = *(long *)(param_4 + uVar8 * 8);
              if ((*(byte *)(lVar4 + 0x19a) >> 2 & 1) != 0) {
                Aska::RenderThread::AddTemporaryResolve(Aska::RenderableObject*, int, int)(*(undefined8 *)(param_1 + 0x4480),lVar4,param_5,0);
              }
              DataMemoryBarrier(2,3);
              iVar2 = 0;
              if (*(int *)(lVar4 + 0x1ac) != 0) {
                iVar2 = *(int *)(lVar4 + 0x1c0) / *(int *)(lVar4 + 0x1ac);
              }
              Aska::RenderThread::AddRenderQueue(Aska::RenderableObject*, Aska::RenderContext*, int)(*(undefined8 *)(param_1 + 0x4480),lVar4,
                              *(long *)(lVar4 + 0x1d0) + (long)*(int *)(lVar4 + 0x1cc) * 0x230,iVar2
                             );
              *(int *)(lVar4 + 0x1cc) = *(int *)(lVar4 + 0x1cc) + iVar2;
            }
            uVar8 = uVar8 + 1;
            if (0 < iVar9) break;
            iVar9 = iVar9 + 1;
            uVar6 = uVar6 + 2;
          } while ((long)uVar8 < (long)iVar10);
        }
      } while ((int)uVar8 < param_6);
    }
  }
  return;
}

// ==== Aska::ObjectManager::OnPaint()
// vaddr 0x215f98c | ghidra 0x225f98c | size 184 | symbol _ZN4Aska13ObjectManager7OnPaintEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13ObjectManager7OnPaintEv(long param_1)

{
  undefined *puVar1;
  undefined8 *puVar2;
  
  if (*(char *)(param_1 + 0x3f0e) == '\0') {
    if (*(char *)(param_1 + 0x3f14) != '\0') {
      Aska::RenderThread::WaitDeviceReset()(*(undefined8 *)(param_1 + 0x4480));
      Aska::ObjectManager::OnPrePaint()(param_1);
      *(char *)(param_1 + 0x3f14) = '\0';
    }
    if (*(char *)(param_1 + 0x3f0c) != '\0') {
      *(char *)(param_1 + 0x3f0c) = '\0';
      Aska::ObjectManager::OnPostPaint()(param_1);
    }
  }
  else {
    *(undefined1 *)(param_1 + 0x3f09) = 2;
    puVar1 = PTR__ZN4Aska6Global21m_pPerformanceCounterE_02cc3ad8;
    Aska::PerformanceCounter::Set(int)(*(undefined8 *)PTR__ZN4Aska6Global21m_pPerformanceCounterE_02cc3ad8,1);
    Aska::PerformanceCounter::Mark(int)(*(undefined8 *)puVar1,4);
    puVar2 = *(undefined8 **)(param_1 + 0x4458);
    if (puVar2 != (undefined8 *)0x0) {
      (**(code **)*puVar2)(puVar2,0);
    }
  }
  *(undefined1 *)(param_1 + 0x3f0f) = 1;
  return;
}

// ==== Aska::ObjectManager::MakeRenderInfoConditionList(Aska::ObjectManager::RenderInfoCond*, unsigned short*, int*, bool*, unsigned int)
// vaddr 0x215fa44 | ghidra 0x225fa44 | size 264 | symbol _ZN4Aska13ObjectManager27MakeRenderInfoConditionListEPNS0_14RenderInfoCondEPtPiPbj | lib libSOA-3.7.0.so | 2026-10-04
int _ZN4Aska13ObjectManager27MakeRenderInfoConditionListEPNS0_14RenderInfoCondEPtPiPbj
              (long param_1,long param_2,long param_3,int *param_4,undefined8 param_5,
              undefined2 param_6)

{
  undefined2 *puVar1;
  long lVar2;
  int iVar3;
  char cVar4;
  char cVar5;
  undefined2 uVar6;
  byte bVar7;
  bool bVar8;
  int iVar9;
  long lVar10;
  long lVar11;
  long lVar12;
  byte bVar13;
  
  if ((int)**(uint **)(param_1 + 0x4478) < 2) {
    iVar9 = 0;
  }
  else {
    lVar11 = 0;
    lVar10 = 0;
    lVar12 = (ulong)**(uint **)(param_1 + 0x4478) - 1;
    bVar13 = 1;
    do {
      param_4 = param_4 + 1;
      if (*param_4 != 0) {
        lVar2 = *(long *)(*(long *)(param_1 + 0x4478) + 8) + lVar11;
        cVar4 = *(char *)(lVar2 + 2);
        bVar7 = *(byte *)(lVar2 + 3) >> 3 & 1;
        bVar8 = cVar4 == '\x02';
        iVar9 = (int)lVar10;
        if ((bVar13 & 1) == 0) {
          cVar5 = *(char *)(param_2 + (long)iVar9 * 8 + 4);
        }
        else {
          uVar6 = *(undefined2 *)(param_3 + lVar11);
          puVar1 = (undefined2 *)(param_2 + (long)iVar9 * 8);
          *(byte *)((long)puVar1 + 5) = bVar7;
          *puVar1 = uVar6;
          *(bool *)(puVar1 + 2) = bVar8;
          *(char *)(puVar1 + 3) = cVar4;
          cVar5 = bVar8;
        }
        if (((bVar7 != 0) || ((bool)cVar5 != (cVar4 == '\x02'))) ||
           (bVar13 = *(byte *)(param_2 + (long)iVar9 * 8 + 5), bVar13 != 0)) {
          lVar2 = param_3 + lVar11;
          lVar10 = (long)iVar9 + 1;
          *(undefined2 *)(param_2 + (long)iVar9 * 8 + 2) = *(undefined2 *)(lVar2 + 2);
          puVar1 = (undefined2 *)(param_2 + lVar10 * 8);
          bVar13 = 0;
          *puVar1 = *(undefined2 *)(lVar2 + 2);
          uVar6 = *(undefined2 *)(lVar2 + 2);
          *(byte *)((long)puVar1 + 5) = bVar7;
          *(bool *)(puVar1 + 2) = bVar8;
          *(char *)(puVar1 + 3) = cVar4;
          puVar1[1] = uVar6;
        }
      }
      iVar9 = (int)lVar10;
      lVar12 = lVar12 + -1;
      lVar11 = lVar11 + 2;
    } while (lVar12 != 0);
  }
  iVar3 = 0;
  if (iVar9 != 0) {
    iVar3 = iVar9 + 1;
  }
  *(undefined2 *)(param_2 + (long)iVar9 * 8 + 2) = param_6;
  return iVar3;
}

// ==== Aska::ObjectManager::MakePaintingList(int)
// vaddr 0x215fb4c | ghidra 0x225fb4c | size 2376 | symbol _ZN4Aska13ObjectManager16MakePaintingListEi | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Type propagation algorithm not settling */

uint _ZN4Aska13ObjectManager16MakePaintingListEi(long param_1,int param_2)

{
  int *piVar1;
  long lVar2;
  int *piVar3;
  uint uVar4;
  byte bVar5;
  ushort uVar6;
  uint uVar7;
  char cVar8;
  bool bVar9;
  undefined1 uVar10;
  long *plVar11;
  long *plVar12;
  ulong uVar13;
  long *plVar14;
  char *pcVar15;
  ulong uVar16;
  long lVar17;
  short *psVar18;
  int iVar19;
  ushort *puVar20;
  ushort *puVar21;
  byte *pbVar22;
  long lVar23;
  undefined8 uVar24;
  uint uVar25;
  ulong uVar26;
  ulong uVar27;
  uint *puVar28;
  long lVar29;
  ulong uVar30;
  uint uVar31;
  ushort auStack_860 [128];
  short asStack_760 [127];
  ushort auStack_662 [3];
  ushort auStack_65c [126];
  char acStack_560 [128];
  byte abStack_4e0 [128];
  int aiStack_460 [128];
  uint auStack_260 [128];
  
  lVar17 = param_1 + (long)param_2 * 0x10;
  if (*(long *)(lVar17 + 0x1020) != 0) {
    lVar29 = (long)param_2;
    lVar2 = param_1 + lVar29 * 0x10;
    if (*(long *)(lVar2 + 0x1028) != 0) {
      puVar28 = *(uint **)(param_1 + 0x4478);
      plVar12 = (long *)(lVar2 + 0x1028);
      uVar7 = *puVar28;
      uVar30 = (ulong)uVar7;
      if ((int)uVar7 < 1) {
        uVar31 = 0;
      }
      else {
        memset(auStack_260,0,(ulong)(uVar7 - 1) * 4 + 4);
        uVar13 = 0;
        uVar31 = 0;
        pbVar22 = (byte *)(*(long *)(puVar28 + 2) + 1);
        do {
          if ((*pbVar22 >> 3 & 1) != 0) {
            aiStack_460[uVar31] = (int)uVar13;
            uVar31 = uVar31 + 1;
          }
          uVar13 = uVar13 + 1;
          pbVar22 = pbVar22 + 2;
        } while (uVar30 != uVar13);
      }
      lVar2 = param_1 + lVar29 * 4;
      *(undefined4 *)(lVar2 + 0x1be8) = 0;
      uVar4 = *(uint *)(lVar2 + 0x1bc8);
      uVar13 = (ulong)uVar4;
      if (*(char *)(param_1 + 0x3f0b) == '\0') {
        if (0 < (int)uVar4) {
          if (uVar31 == 0) {
            lVar23 = *(long *)(param_1 + 0x4478);
            plVar14 = (long *)*plVar12;
            uVar16 = uVar13;
            do {
              uVar16 = uVar16 - 1;
              bVar5 = *(byte *)(lVar23 + (ulong)*(byte *)(*plVar14 + 0x1b7) + 0x10);
              auStack_260[bVar5] = auStack_260[bVar5] + 1;
              plVar14 = plVar14 + 1;
            } while (uVar16 != 0);
          }
          else {
            uVar16 = 0;
            do {
              lVar23 = *(long *)(*plVar12 + uVar16 * 8);
              bVar5 = *(byte *)(*(long *)(param_1 + 0x4478) + (ulong)*(byte *)(lVar23 + 0x1b7) +
                               0x10);
              auStack_260[bVar5] = auStack_260[bVar5] + 1;
              if (*(int *)(lVar23 + 0x198) < 0) {
                uVar26 = 0;
                piVar3 = (int *)(lVar23 + 0x1ac);
                do {
                  if (uVar26 < *(uint *)(lVar23 + 0x22c)) {
                    do {
                      cVar8 = '\x01';
                      bVar9 = (bool)ExclusiveMonitorPass(piVar3,0x10);
                      if (bVar9) {
                        *piVar3 = *piVar3 + 1;
                        cVar8 = ExclusiveMonitorsStatus();
                      }
                    } while (cVar8 != '\0');
                    auStack_260[aiStack_460[uVar26]] = auStack_260[aiStack_460[uVar26]] + 1;
                  }
                  uVar26 = uVar26 + 1;
                } while (uVar26 != uVar31);
              }
              uVar16 = uVar16 + 1;
            } while (uVar16 != uVar13);
          }
        }
      }
      else if (0 < (int)uVar4) {
        piVar3 = (int *)(lVar2 + 0x1be8);
        uVar16 = 0;
        if (uVar31 == 0) {
          do {
            lVar23 = *(long *)(*plVar12 + uVar16 * 8);
            bVar5 = *(byte *)(*(long *)(param_1 + 0x4478) + (ulong)*(byte *)(lVar23 + 0x1b7) + 0x10)
            ;
            auStack_260[bVar5] = auStack_260[bVar5] + 1;
            if ((*(uint *)(lVar23 + 0x198) & 0x20400010) == 0x10) {
              piVar1 = (int *)(lVar23 + 0x1ac);
              do {
                cVar8 = '\x01';
                bVar9 = (bool)ExclusiveMonitorPass(piVar1,0x10);
                if (bVar9) {
                  *piVar1 = *piVar1 + 1;
                  cVar8 = ExclusiveMonitorsStatus();
                }
              } while (cVar8 != '\0');
              auStack_260[0] = auStack_260[0] + 1;
              *piVar3 = *piVar3 + 1;
            }
            uVar16 = uVar16 + 1;
          } while (uVar16 != uVar13);
        }
        else {
          do {
            lVar23 = *(long *)(*plVar12 + uVar16 * 8);
            bVar5 = *(byte *)(*(long *)(param_1 + 0x4478) + (ulong)*(byte *)(lVar23 + 0x1b7) + 0x10)
            ;
            auStack_260[bVar5] = auStack_260[bVar5] + 1;
            uVar25 = *(uint *)(lVar23 + 0x198);
            if ((uVar25 & 0x20400010) == 0x10) {
              piVar1 = (int *)(lVar23 + 0x1ac);
              do {
                cVar8 = '\x01';
                bVar9 = (bool)ExclusiveMonitorPass(piVar1,0x10);
                if (bVar9) {
                  *piVar1 = *piVar1 + 1;
                  cVar8 = ExclusiveMonitorsStatus();
                }
              } while (cVar8 != '\0');
              auStack_260[0] = auStack_260[0] + 1;
              *piVar3 = *piVar3 + 1;
              uVar25 = *(uint *)(lVar23 + 0x198);
            }
            if ((int)uVar25 < 0) {
              uVar26 = 0;
              piVar1 = (int *)(lVar23 + 0x1ac);
              do {
                if (uVar26 < *(uint *)(lVar23 + 0x22c)) {
                  do {
                    cVar8 = '\x01';
                    bVar9 = (bool)ExclusiveMonitorPass(piVar1,0x10);
                    if (bVar9) {
                      *piVar1 = *piVar1 + 1;
                      cVar8 = ExclusiveMonitorsStatus();
                    }
                  } while (cVar8 != '\0');
                  auStack_260[aiStack_460[uVar26]] = auStack_260[aiStack_460[uVar26]] + 1;
                }
                uVar26 = uVar26 + 1;
              } while (uVar26 != uVar31);
            }
            uVar16 = uVar16 + 1;
          } while (uVar16 != uVar13);
        }
      }
      piVar3 = (int *)(param_1 + 0x106f8);
      if (0 < *piVar3) {
        lVar23 = 0;
        do {
          plVar14 = (long *)(param_1 + lVar23 * 8 + 0x104f8);
          plVar11 = (long *)*plVar14;
          uVar16 = (**(code **)(*plVar11 + 0x1f8))
                             (plVar11,abStack_4e0 + lVar23 * 2,param_2,0,auStack_260);
          if ((uVar16 & 1) == 0) {
            abStack_4e0[lVar23 * 2] = 0;
          }
          else {
            piVar1 = (int *)(*plVar14 + 0x1ac);
            do {
              cVar8 = '\x01';
              bVar9 = (bool)ExclusiveMonitorPass(piVar1,0x10);
              if (bVar9) {
                *piVar1 = *piVar1 + 1;
                cVar8 = ExclusiveMonitorsStatus();
              }
            } while (cVar8 != '\0');
            auStack_260[abStack_4e0[lVar23 * 2 + 1]] = auStack_260[abStack_4e0[lVar23 * 2 + 1]] + 1;
          }
          lVar23 = lVar23 + 1;
        } while (lVar23 < *piVar3);
      }
      if (0 < (int)uVar7) {
        uVar16 = 0;
        bVar9 = false;
        do {
          uVar25 = auStack_260[uVar16];
          acStack_560[uVar16] = '\0';
          if ((uVar25 != 0) &&
             ((bVar5 = *(byte *)(*(long *)(*(long *)(param_1 + 0x4478) + 8) + uVar16 * 2 + 1),
              (bVar5 >> 5 & 1) != 0 || (!bVar9 && (bVar5 & 0x10) != 0)))) {
            acStack_560[uVar16] = '\x01';
            void Aska::FrameTextureEntities::AddEntry<true>(int, int)(*(long *)(param_1 + 0x45b8) + 0x308,0,param_2);
            piVar1 = (int *)(*(long *)(param_1 + 0x45b8) + 0x1ac);
            do {
              cVar8 = '\x01';
              bVar9 = (bool)ExclusiveMonitorPass(piVar1,0x10);
              if (bVar9) {
                *piVar1 = *piVar1 + 1;
                cVar8 = ExclusiveMonitorsStatus();
              }
            } while (cVar8 != '\0');
            auStack_260[uVar16] = auStack_260[uVar16] + 1;
            bVar9 = true;
          }
          uVar16 = uVar16 + 1;
        } while (uVar16 != uVar30);
      }
      plVar14 = (long *)(lVar17 + 0x1020);
      *(uint *)(param_1 + lVar29 * 4 + 0x1e88) = auStack_260[0];
      asStack_760[0] = 0;
      auStack_662[1] = 0;
      if (1 < (int)uVar7) {
        auStack_662[2] = (short)auStack_260[0];
        asStack_760[1] = (short)auStack_260[0];
        if (uVar7 != 2) {
          puVar28 = auStack_260;
          lVar17 = uVar30 - 2;
          puVar20 = (ushort *)(asStack_760 + 2);
          puVar21 = auStack_662 + 3;
          uVar25 = auStack_260[0];
          do {
            puVar28 = puVar28 + 1;
            lVar17 = lVar17 + -1;
            uVar25 = *puVar28 + (uVar25 & 0xffff);
            *puVar21 = (ushort)uVar25;
            *puVar20 = (ushort)uVar25;
            puVar20 = puVar20 + 1;
            puVar21 = puVar21 + 1;
          } while (lVar17 != 0);
        }
      }
      if (0 < (int)uVar7) {
        pcVar15 = acStack_560;
        puVar20 = auStack_662;
        psVar18 = asStack_760;
        uVar16 = uVar30;
        do {
          puVar20 = (ushort *)((long)puVar20 + 2);
          if (*pcVar15 != '\0') {
            uVar6 = *puVar20;
            uVar24 = *(undefined8 *)(param_1 + 0x45b8);
            lVar17 = *plVar14;
            *puVar20 = uVar6 + 1;
            *(undefined8 *)(lVar17 + (ulong)uVar6 * 8) = uVar24;
            *psVar18 = *psVar18 + 1;
          }
          pcVar15 = pcVar15 + 1;
          uVar16 = uVar16 - 1;
          psVar18 = psVar18 + 1;
        } while (uVar16 != 0);
      }
      iVar19 = *piVar3;
      if (0 < iVar19) {
        lVar17 = 0;
        pbVar22 = (byte *)((ulong)abStack_4e0 | 1);
        do {
          if (pbVar22[-1] == 1) {
            uVar16 = (ulong)*pbVar22;
            uVar24 = *(undefined8 *)(param_1 + 0x104f8 + lVar17 * 8);
            lVar23 = *plVar14;
            uVar6 = auStack_662[uVar16 + 1];
            auStack_662[uVar16 + 1] = uVar6 + 1;
            *(undefined8 *)(lVar23 + (ulong)uVar6 * 8) = uVar24;
            asStack_760[uVar16] = asStack_760[uVar16] + 1;
            iVar19 = *piVar3;
          }
          lVar17 = lVar17 + 1;
          pbVar22 = pbVar22 + 2;
        } while (lVar17 < iVar19);
      }
      if (*(char *)(param_1 + 0x3f0b) == '\0') {
        if (0 < (int)uVar4) {
          if (uVar31 == 0) {
            uVar16 = 0;
            do {
              lVar23 = *plVar14;
              lVar17 = *(long *)(*plVar12 + uVar16 * 8);
              uVar16 = uVar16 + 1;
              uVar26 = (ulong)*(byte *)(*(long *)(param_1 + 0x4478) +
                                        (ulong)*(byte *)(lVar17 + 0x1b7) + 0x10);
              uVar6 = auStack_662[uVar26 + 1];
              auStack_662[uVar26 + 1] = uVar6 + 1;
              *(long *)(lVar23 + (ulong)uVar6 * 8) = lVar17;
            } while (uVar13 != uVar16);
          }
          else {
            uVar16 = 0;
            do {
              lVar23 = *plVar14;
              lVar17 = *(long *)(*plVar12 + uVar16 * 8);
              uVar26 = (ulong)*(byte *)(*(long *)(param_1 + 0x4478) +
                                        (ulong)*(byte *)(lVar17 + 0x1b7) + 0x10);
              uVar6 = auStack_662[uVar26 + 1];
              auStack_662[uVar26 + 1] = uVar6 + 1;
              *(long *)(lVar23 + (ulong)uVar6 * 8) = lVar17;
              if (*(int *)(lVar17 + 0x198) < 0) {
                uVar26 = 0;
                do {
                  if (uVar26 < *(uint *)(lVar17 + 0x22c)) {
                    lVar23 = *plVar14;
                    uVar6 = auStack_662[(long)aiStack_460[uVar26] + 1];
                    auStack_662[(long)aiStack_460[uVar26] + 1] = uVar6 + 1;
                    *(long *)(lVar23 + (ulong)uVar6 * 8) = lVar17;
                  }
                  uVar26 = uVar26 + 1;
                } while (uVar31 != uVar26);
              }
              uVar16 = uVar16 + 1;
            } while (uVar16 != uVar13);
          }
        }
      }
      else if (0 < (int)uVar4) {
        if (uVar31 == 0) {
          uVar16 = 0;
          do {
            lVar17 = *(long *)(*plVar12 + uVar16 * 8);
            uVar26 = (ulong)*(byte *)(*(long *)(param_1 + 0x4478) + (ulong)*(byte *)(lVar17 + 0x1b7)
                                     + 0x10);
            if ((*(uint *)(lVar17 + 0x198) & 0x20400010) == 0x10) {
              uVar27 = (ulong)auStack_662[1];
              auStack_662[1] = auStack_662[1] + 1;
              *(long *)(*plVar14 + uVar27 * 8) = lVar17;
            }
            uVar6 = auStack_662[uVar26 + 1];
            lVar23 = *plVar14;
            uVar16 = uVar16 + 1;
            auStack_662[uVar26 + 1] = uVar6 + 1;
            *(long *)(lVar23 + (ulong)uVar6 * 8) = lVar17;
          } while (uVar13 != uVar16);
        }
        else {
          uVar16 = 0;
          do {
            lVar17 = *(long *)(*plVar12 + uVar16 * 8);
            uVar26 = (ulong)*(byte *)(*(long *)(param_1 + 0x4478) + (ulong)*(byte *)(lVar17 + 0x1b7)
                                     + 0x10);
            if ((*(uint *)(lVar17 + 0x198) & 0x20400010) == 0x10) {
              uVar27 = (ulong)auStack_662[1];
              auStack_662[1] = auStack_662[1] + 1;
              *(long *)(*plVar14 + uVar27 * 8) = lVar17;
            }
            uVar6 = auStack_662[uVar26 + 1];
            lVar23 = *plVar14;
            auStack_662[uVar26 + 1] = uVar6 + 1;
            *(long *)(lVar23 + (ulong)uVar6 * 8) = lVar17;
            if (*(int *)(lVar17 + 0x198) < 0) {
              uVar26 = 0;
              do {
                if (uVar26 < *(uint *)(lVar17 + 0x22c)) {
                  lVar23 = *plVar14;
                  uVar6 = auStack_662[(long)aiStack_460[uVar26] + 1];
                  auStack_662[(long)aiStack_460[uVar26] + 1] = uVar6 + 1;
                  *(long *)(lVar23 + (ulong)uVar6 * 8) = lVar17;
                }
                uVar26 = uVar26 + 1;
              } while (uVar31 != uVar26);
            }
            uVar16 = uVar16 + 1;
          } while (uVar16 != uVar13);
        }
      }
      memcpy(auStack_860,auStack_662 + 1,(long)(int)uVar7 << 1);
      iVar19 = *piVar3;
      if (0 < iVar19) {
        lVar17 = 0;
        pbVar22 = (byte *)((ulong)abStack_4e0 | 1);
        do {
          if (pbVar22[-1] == 2) {
            uVar24 = *(undefined8 *)(param_1 + 0x104f8 + lVar17 * 8);
            lVar23 = *plVar14;
            uVar6 = auStack_860[*pbVar22];
            auStack_860[*pbVar22] = uVar6 + 1;
            *(undefined8 *)(lVar23 + (ulong)uVar6 * 8) = uVar24;
            iVar19 = *piVar3;
          }
          lVar17 = lVar17 + 1;
          pbVar22 = pbVar22 + 2;
        } while (lVar17 < iVar19);
      }
      if (0 < (int)uVar7) {
        lVar17 = 0;
        do {
          lVar23 = *(long *)(*(long *)(param_1 + 0x4478) + 8);
          bVar5 = *(byte *)(lVar23 + lVar17 + 1);
          if ((bVar5 & 1) == 0) {
            if ((bVar5 >> 1 & 1) == 0) {
              if (((bVar5 >> 2 & 1) != 0) &&
                 (plVar12 = *(long **)(param_1 + 0x1b00), plVar12 != (long *)0x0)) {
                (**(code **)(*plVar12 + 0x10))
                          (plVar12,*(undefined1 *)(lVar23 + lVar17),*plVar14,
                           *(undefined2 *)((long)asStack_760 + lVar17),
                           *(undefined2 *)((long)auStack_662 + lVar17 + 2U));
              }
            }
            else {
              TOMQuickSort<Aska::RenderableObject, float, 64, 10>::Ascend(Aska::RenderableObject**, int, int, Aska::ObjectManager::RenderableObjectContext*)(*plVar14,*(undefined2 *)((long)asStack_760 + lVar17),
                              *(undefined2 *)((long)auStack_662 + lVar17 + 2U),
                              *(undefined8 *)(param_1 + 0x3f48));
            }
          }
          else {
            TOMQuickSort<Aska::RenderableObject, float, 64, 10>::Descend(Aska::RenderableObject**, int, int, Aska::ObjectManager::RenderableObjectContext*)(*plVar14,*(undefined2 *)((long)asStack_760 + lVar17),
                            *(undefined2 *)((long)auStack_662 + lVar17 + 2U),
                            *(undefined8 *)(param_1 + 0x3f48));
          }
          uVar30 = uVar30 - 1;
          lVar17 = lVar17 + 2;
        } while (uVar30 != 0);
      }
      uVar6 = auStack_662[(int)uVar7];
      *(uint *)(lVar2 + 0x1bc8) = (uint)uVar6;
      uVar10 = Aska::ObjectManager::MakeRenderInfoConditionList(Aska::ObjectManager::RenderInfoCond*, unsigned short*, int*, bool*, unsigned int)(param_1,param_1 + lVar29 * 0x38 + 0x20a8,asStack_760,auStack_260);
      *(undefined1 *)(param_1 + lVar29 + 0x3e68) = uVar10;
      return (uint)uVar6;
    }
  }
  return 0;
}

// ==== TOMQuickSort<Aska::RenderableObject, float, 64, 10>::Descend(Aska::RenderableObject**, int, int, Aska::ObjectManager::RenderableObjectContext*)
// vaddr 0x2160494 | ghidra 0x2260494 | size 524 | symbol _ZN12TOMQuickSortIN4Aska16RenderableObjectEfLi64ELi10EE7DescendEPPS1_iiPNS0_13ObjectManager23RenderableObjectContextE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN12TOMQuickSortIN4Aska16RenderableObjectEfLi64ELi10EE7DescendEPPS1_iiPNS0_13ObjectManager23RenderableObjectContextE
               (long param_1,uint param_2,uint param_3,long param_4)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  long lVar4;
  ulong uVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  long lVar9;
  long lVar10;
  int iVar11;
  long lVar12;
  int iVar13;
  long lVar14;
  ulong uVar15;
  int iVar16;
  float fVar17;
  int aiStack_210 [64];
  uint auStack_110 [64];
  
  if (param_2 == param_3) {
    return;
  }
  uVar5 = 0;
  iVar6 = param_3 - 1;
  uVar7 = param_2;
  do {
    if ((int)(iVar6 - uVar7) < 10) {
      if ((int)uVar5 == 0) {
        if ((int)param_3 <= (int)(param_2 + 1)) {
          return;
        }
        lVar9 = (long)(int)(param_2 + 1);
        uVar7 = param_2;
        do {
          lVar10 = *(long *)(param_1 + lVar9 * 8);
          uVar5 = (ulong)uVar7;
          if ((int)param_2 <= (int)uVar7) {
            fVar17 = *(float *)(param_4 + (ulong)*(ushort *)(lVar10 + 0x1b8) * 8 + 4);
            uVar15 = (long)(int)uVar7;
            do {
              lVar14 = *(long *)(param_1 + uVar15 * 8);
              if (fVar17 <= *(float *)(param_4 + (ulong)*(ushort *)(lVar14 + 0x1b8) * 8 + 4)) {
                uVar5 = uVar15 & 0xffffffff;
                break;
              }
              uVar5 = uVar15 - 1;
              *(long *)(param_1 + uVar15 * 8 + 8) = lVar14;
              bVar1 = (long)(int)param_2 < (long)uVar15;
              uVar15 = uVar5;
            } while (bVar1);
          }
          lVar9 = lVar9 + 1;
          uVar7 = uVar7 + 1;
          *(long *)(param_1 + (long)((int)uVar5 + 1) * 8) = lVar10;
          if ((uint)lVar9 == param_3) {
            return;
          }
        } while( true );
      }
      uVar5 = (long)(int)uVar5 - 1;
      uVar7 = auStack_110[uVar5];
      iVar6 = aiStack_210[uVar5];
    }
    iVar2 = uVar7 + iVar6;
    if (iVar2 < 0) {
      iVar2 = iVar2 + 1;
    }
    fVar17 = *(float *)(param_4 + (ulong)*(ushort *)
                                          (*(long *)(param_1 + (long)(iVar2 >> 1) * 8) + 0x1b8) * 8
                       + 4);
    iVar2 = iVar6;
    uVar3 = uVar7;
    while( true ) {
      lVar9 = 0;
      lVar10 = (long)(int)uVar3;
      do {
        lVar14 = *(long *)(param_1 + (long)(int)uVar3 * 8 + lVar9 * 8);
        lVar9 = lVar9 + 1;
      } while (fVar17 < *(float *)(param_4 + (ulong)*(ushort *)(lVar14 + 0x1b8) * 8 + 4));
      lVar12 = 0;
      do {
        lVar4 = *(long *)(param_1 + (long)iVar2 * 8 + lVar12 * 8);
        lVar12 = lVar12 + -1;
      } while (*(float *)(param_4 + (ulong)*(ushort *)(lVar4 + 0x1b8) * 8 + 4) < fVar17);
      iVar8 = (int)lVar9;
      iVar11 = (int)lVar12;
      if (iVar2 + iVar11 + 1 <= (int)(uVar3 + iVar8 + -1)) break;
      uVar3 = uVar3 + iVar8;
      *(long *)(param_1 + lVar10 * 8 + lVar9 * 8 + -8) = lVar4;
      *(long *)(param_1 + (long)iVar2 * 8 + lVar12 * 8 + 8) = lVar14;
      iVar2 = iVar2 + iVar11;
    }
    iVar13 = ~uVar7 + uVar3 + iVar8;
    iVar16 = ((iVar6 + -1) - iVar2) - iVar11;
    if (iVar16 < iVar13) {
      if (10 < iVar13) {
        uVar15 = -(uVar5 >> 0x1f & 1) & 0xfffffffc00000000 | (uVar5 & 0xffffffff) << 2;
        *(uint *)((long)auStack_110 + uVar15) = uVar7;
        uVar5 = (ulong)((int)uVar5 + 1);
        *(uint *)((long)aiStack_210 + uVar15) = uVar3 + iVar8 + -2;
      }
      uVar7 = iVar2 + iVar11 + 2;
    }
    else {
      if (10 < iVar16) {
        uVar15 = -(uVar5 >> 0x1f & 1) & 0xfffffffc00000000 | (uVar5 & 0xffffffff) << 2;
        uVar5 = (ulong)((int)uVar5 + 1);
        *(int *)((long)aiStack_210 + uVar15) = iVar6;
        *(int *)((long)auStack_110 + uVar15) = iVar2 + iVar11 + 2;
      }
      iVar6 = uVar3 + iVar8 + -2;
    }
  } while( true );
}

// ==== TOMQuickSort<Aska::RenderableObject, float, 64, 10>::Ascend(Aska::RenderableObject**, int, int, Aska::ObjectManager::RenderableObjectContext*)
// vaddr 0x21606a0 | ghidra 0x22606a0 | size 524 | symbol _ZN12TOMQuickSortIN4Aska16RenderableObjectEfLi64ELi10EE6AscendEPPS1_iiPNS0_13ObjectManager23RenderableObjectContextE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN12TOMQuickSortIN4Aska16RenderableObjectEfLi64ELi10EE6AscendEPPS1_iiPNS0_13ObjectManager23RenderableObjectContextE
               (long param_1,uint param_2,uint param_3,long param_4)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  long lVar4;
  ulong uVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  long lVar9;
  long lVar10;
  int iVar11;
  long lVar12;
  int iVar13;
  long lVar14;
  ulong uVar15;
  int iVar16;
  float fVar17;
  int aiStack_210 [64];
  uint auStack_110 [64];
  
  if (param_2 == param_3) {
    return;
  }
  uVar5 = 0;
  iVar6 = param_3 - 1;
  uVar7 = param_2;
  do {
    if ((int)(iVar6 - uVar7) < 10) {
      if ((int)uVar5 == 0) {
        if ((int)param_3 <= (int)(param_2 + 1)) {
          return;
        }
        lVar9 = (long)(int)(param_2 + 1);
        uVar7 = param_2;
        do {
          lVar10 = *(long *)(param_1 + lVar9 * 8);
          uVar5 = (ulong)uVar7;
          if ((int)param_2 <= (int)uVar7) {
            fVar17 = *(float *)(param_4 + (ulong)*(ushort *)(lVar10 + 0x1b8) * 8 + 4);
            uVar15 = (long)(int)uVar7;
            do {
              lVar14 = *(long *)(param_1 + uVar15 * 8);
              if (*(float *)(param_4 + (ulong)*(ushort *)(lVar14 + 0x1b8) * 8 + 4) <= fVar17) {
                uVar5 = uVar15 & 0xffffffff;
                break;
              }
              uVar5 = uVar15 - 1;
              *(long *)(param_1 + uVar15 * 8 + 8) = lVar14;
              bVar1 = (long)(int)param_2 < (long)uVar15;
              uVar15 = uVar5;
            } while (bVar1);
          }
          lVar9 = lVar9 + 1;
          uVar7 = uVar7 + 1;
          *(long *)(param_1 + (long)((int)uVar5 + 1) * 8) = lVar10;
          if ((uint)lVar9 == param_3) {
            return;
          }
        } while( true );
      }
      uVar5 = (long)(int)uVar5 - 1;
      uVar7 = auStack_110[uVar5];
      iVar6 = aiStack_210[uVar5];
    }
    iVar2 = uVar7 + iVar6;
    if (iVar2 < 0) {
      iVar2 = iVar2 + 1;
    }
    fVar17 = *(float *)(param_4 + (ulong)*(ushort *)
                                          (*(long *)(param_1 + (long)(iVar2 >> 1) * 8) + 0x1b8) * 8
                       + 4);
    iVar2 = iVar6;
    uVar3 = uVar7;
    while( true ) {
      lVar9 = 0;
      lVar10 = (long)(int)uVar3;
      do {
        lVar14 = *(long *)(param_1 + (long)(int)uVar3 * 8 + lVar9 * 8);
        lVar9 = lVar9 + 1;
      } while (*(float *)(param_4 + (ulong)*(ushort *)(lVar14 + 0x1b8) * 8 + 4) < fVar17);
      lVar12 = 0;
      do {
        lVar4 = *(long *)(param_1 + (long)iVar2 * 8 + lVar12 * 8);
        lVar12 = lVar12 + -1;
      } while (fVar17 < *(float *)(param_4 + (ulong)*(ushort *)(lVar4 + 0x1b8) * 8 + 4));
      iVar8 = (int)lVar9;
      iVar11 = (int)lVar12;
      if (iVar2 + iVar11 + 1 <= (int)(uVar3 + iVar8 + -1)) break;
      uVar3 = uVar3 + iVar8;
      *(long *)(param_1 + lVar10 * 8 + lVar9 * 8 + -8) = lVar4;
      *(long *)(param_1 + (long)iVar2 * 8 + lVar12 * 8 + 8) = lVar14;
      iVar2 = iVar2 + iVar11;
    }
    iVar13 = ~uVar7 + uVar3 + iVar8;
    iVar16 = ((iVar6 + -1) - iVar2) - iVar11;
    if (iVar16 < iVar13) {
      if (10 < iVar13) {
        uVar15 = -(uVar5 >> 0x1f & 1) & 0xfffffffc00000000 | (uVar5 & 0xffffffff) << 2;
        *(uint *)((long)auStack_110 + uVar15) = uVar7;
        uVar5 = (ulong)((int)uVar5 + 1);
        *(uint *)((long)aiStack_210 + uVar15) = uVar3 + iVar8 + -2;
      }
      uVar7 = iVar2 + iVar11 + 2;
    }
    else {
      if (10 < iVar16) {
        uVar15 = -(uVar5 >> 0x1f & 1) & 0xfffffffc00000000 | (uVar5 & 0xffffffff) << 2;
        uVar5 = (ulong)((int)uVar5 + 1);
        *(int *)((long)aiStack_210 + uVar15) = iVar6;
        *(int *)((long)auStack_110 + uVar15) = iVar2 + iVar11 + 2;
      }
      iVar6 = uVar3 + iVar8 + -2;
    }
  } while( true );
}

// ==== Aska::ObjectManager::MakePaintingListPost()
// vaddr 0x21608ac | ghidra 0x22608ac | size 696 | symbol _ZN4Aska13ObjectManager20MakePaintingListPostEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13ObjectManager20MakePaintingListPostEv(long param_1)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  byte bVar6;
  char cVar7;
  bool bVar8;
  uint uVar9;
  long *plVar10;
  long lVar11;
  int iVar12;
  ulong uVar13;
  ulong uVar14;
  long lVar15;
  ulong uVar16;
  ulong uVar17;
  int *piVar18;
  long lVar19;
  uint *puVar20;
  int *piVar21;
  int *piVar22;
  int aiStack_660 [127];
  int aiStack_464 [129];
  int aiStack_260 [128];
  
  piVar21 = aiStack_660;
  puVar20 = *(uint **)(param_1 + 0x4478);
  uVar1 = *puVar20;
  memset(aiStack_260,0,0x200);
  uVar2 = *(uint *)(param_1 + 0x1bc4);
  if (0 < (int)uVar2) {
    plVar10 = *(long **)(param_1 + 0x1010);
    uVar13 = (ulong)uVar2;
    do {
      uVar13 = uVar13 - 1;
      bVar6 = *(byte *)((long)puVar20 + (ulong)*(byte *)(*plVar10 + 0x1b7) + 0x10);
      aiStack_260[bVar6] = aiStack_260[bVar6] + 1;
      plVar10 = plVar10 + 1;
    } while (uVar13 != 0);
  }
  uVar3 = *(uint *)(param_1 + 0x1af8);
  uVar13 = (ulong)*(byte *)((long)puVar20 + 0x26);
  if (0 < (int)uVar3) {
    uVar14 = 0;
    do {
      piVar22 = (int *)(*(long *)(*(long *)(param_1 + 0x1ae8) + uVar14 * 8) + 0x1ac);
      do {
        cVar7 = '\x01';
        bVar8 = (bool)ExclusiveMonitorPass(piVar22,0x10);
        if (bVar8) {
          *piVar22 = *piVar22 + 1;
          cVar7 = ExclusiveMonitorsStatus();
        }
      } while (cVar7 != '\0');
      uVar14 = uVar14 + 1;
      aiStack_260[uVar13] = aiStack_260[uVar13] + 1;
    } while (uVar14 != uVar3);
    puVar20 = *(uint **)(param_1 + 0x4478);
  }
  bVar6 = *(byte *)((long)puVar20 + 0x25);
  uVar14 = (ulong)bVar6;
  uVar9 = puVar20[10];
  aiStack_660[0] = 0;
  aiStack_464[1] = 0;
  if (1 < (int)uVar1) {
    piVar22 = aiStack_464 + 1;
    iVar12 = 0;
    lVar15 = (ulong)uVar1 - 1;
    piVar18 = aiStack_260;
    do {
      piVar21 = piVar21 + 1;
      piVar22 = piVar22 + 1;
      lVar15 = lVar15 + -1;
      iVar12 = *piVar18 + iVar12;
      *piVar22 = iVar12;
      *piVar21 = iVar12;
      piVar18 = piVar18 + 1;
    } while (lVar15 != 0);
  }
  if (0 < (int)uVar3) {
    iVar12 = aiStack_464[uVar13 + 1];
    uVar16 = 0;
    do {
      lVar15 = uVar16 * 8;
      uVar16 = uVar16 + 1;
      *(undefined8 *)(*(long *)(param_1 + 0x1008) + (long)iVar12 * 8 + lVar15) =
           *(undefined8 *)(*(long *)(param_1 + 0x1ae8) + lVar15);
    } while (uVar3 != uVar16);
    aiStack_464[uVar13 + 1] = iVar12 + uVar3;
  }
  if (0 < (int)uVar2) {
    uVar16 = 0;
    do {
      lVar19 = *(long *)(param_1 + 0x1008);
      lVar15 = *(long *)(*(long *)(param_1 + 0x1010) + uVar16 * 8);
      uVar16 = uVar16 + 1;
      uVar17 = (ulong)*(byte *)(*(long *)(param_1 + 0x4478) + (ulong)*(byte *)(lVar15 + 0x1b7) +
                               0x10);
      iVar12 = aiStack_464[uVar17 + 1];
      aiStack_464[uVar17 + 1] = iVar12 + 1;
      *(long *)(lVar19 + (long)iVar12 * 8) = lVar15;
    } while (uVar2 != uVar16);
  }
  if ((int)(uint)bVar6 < (int)uVar1) {
    lVar15 = uVar14 << 1;
    piVar21 = aiStack_464 + uVar14 + 1;
    piVar22 = aiStack_660 + uVar14;
    lVar19 = uVar1 - uVar14;
    do {
      lVar11 = *(long *)(*(long *)(param_1 + 0x4478) + 8);
      bVar6 = *(byte *)(lVar11 + lVar15 + 1);
      if ((bVar6 & 1) == 0) {
        if ((bVar6 >> 1 & 1) == 0) {
          if (((bVar6 >> 2 & 1) != 0) &&
             (plVar10 = *(long **)(param_1 + 0x1b00), plVar10 != (long *)0x0)) {
            (**(code **)(*plVar10 + 0x10))
                      (plVar10,*(undefined1 *)(lVar11 + lVar15),*(undefined8 *)(param_1 + 0x1008),
                       *piVar22,*piVar21);
          }
        }
        else {
          TOMQuickSort<Aska::RenderableObject, float, 64, 10>::Ascend(Aska::RenderableObject**, int, int, Aska::ObjectManager::RenderableObjectContext*)(*(undefined8 *)(param_1 + 0x1008),*piVar22,*piVar21,
                          *(undefined8 *)(param_1 + 0x3f48));
        }
      }
      else {
        TOMQuickSort<Aska::RenderableObject, float, 64, 10>::Descend(Aska::RenderableObject**, int, int, Aska::ObjectManager::RenderableObjectContext*)(*(undefined8 *)(param_1 + 0x1008),*piVar22,*piVar21,
                        *(undefined8 *)(param_1 + 0x3f48));
      }
      piVar21 = piVar21 + 1;
      piVar22 = piVar22 + 1;
      lVar19 = lVar19 + -1;
      lVar15 = lVar15 + 2;
    } while (lVar19 != 0);
  }
  *(int *)(param_1 + 0x1bc4) = aiStack_464[(int)uVar1];
  iVar12 = aiStack_464[(ulong)(byte)uVar9 + 1];
  *(short *)(param_1 + 0x3efe) = (short)iVar12;
  iVar4 = aiStack_464[uVar14 + 1];
  *(short *)(param_1 + 0x3f02) = (short)iVar4;
  iVar5 = aiStack_464[uVar13 + 1];
  *(short *)(param_1 + 0x3f04) = (short)iVar5 - (short)iVar4;
  *(short *)(param_1 + 0x3f06) = (short)iVar12 - (short)iVar5;
  return;
}

// ==== Aska::ObjectManager::MakePaintingListShadow(int)
// vaddr 0x2160b64 | ghidra 0x2260b64 | size 12 | symbol _ZN4Aska13ObjectManager22MakePaintingListShadowEi | lib libSOA-3.7.0.so | 2026-10-04
undefined2 _ZN4Aska13ObjectManager22MakePaintingListShadowEi(long param_1,int param_2)

{
  return *(undefined2 *)(param_1 + (long)param_2 * 2 + 0x1e08);
}

// ==== Aska::ObjectManager::MakePaintingListMultipass(int)
// vaddr 0x2160b70 | ghidra 0x2260b70 | size 1744 | symbol _ZN4Aska13ObjectManager25MakePaintingListMultipassEi | lib libSOA-3.7.0.so | 2026-10-04
uint _ZN4Aska13ObjectManager25MakePaintingListMultipassEi(long param_1,int param_2)

{
  long lVar1;
  int *piVar2;
  int *piVar3;
  undefined8 *puVar4;
  undefined8 *puVar5;
  uint uVar6;
  uint uVar7;
  byte bVar8;
  byte bVar9;
  ushort uVar10;
  ushort uVar11;
  ushort uVar12;
  char cVar13;
  bool bVar14;
  undefined1 uVar15;
  long *plVar16;
  long *plVar17;
  uint uVar18;
  ulong uVar19;
  int iVar20;
  char *pcVar21;
  ushort *puVar22;
  long lVar23;
  ushort *puVar24;
  byte *pbVar25;
  short *psVar26;
  long lVar27;
  ulong uVar28;
  undefined8 uVar29;
  long lVar30;
  long lVar31;
  uint *puVar32;
  ulong uVar33;
  ulong uVar34;
  ushort auStack_660 [128];
  short asStack_560 [128];
  ushort auStack_460 [128];
  char acStack_360 [128];
  byte abStack_2e0 [128];
  uint auStack_260 [128];
  
  puVar32 = *(uint **)(param_1 + 0x4478);
  uVar6 = *puVar32;
  uVar33 = (ulong)uVar6;
  if (0 < (int)uVar6) {
    memset(auStack_260,0,(ulong)(uVar6 - 1) * 4 + 4);
  }
  lVar1 = param_1 + (long)param_2 * 4;
  puVar22 = (ushort *)(param_1 + (long)param_2 * 0x48 + 0x4632);
  uVar7 = *(uint *)(lVar1 + 0x1c08);
  uVar34 = (ulong)uVar7;
  uVar10 = *puVar22;
  lVar27 = (long)param_2;
  if ((*(char *)(param_1 + 0x3f0b) == '\0') || ((uVar10 >> 1 & 1) == 0)) {
    if (0 < (int)uVar7) {
      plVar17 = *(long **)(param_1 + lVar27 * 0x10 + 0x10a8);
      uVar19 = uVar34;
      do {
        uVar19 = uVar19 - 1;
        bVar8 = *(byte *)((long)puVar32 + (ulong)*(byte *)(*plVar17 + 0x1b7) + 0x10);
        auStack_260[bVar8] = auStack_260[bVar8] + 1;
        plVar17 = plVar17 + 1;
      } while (uVar19 != 0);
    }
  }
  else if (0 < (int)uVar7) {
    uVar19 = 0;
    while( true ) {
      lVar23 = *(long *)(*(long *)(param_1 + lVar27 * 0x10 + 0x10a8) + uVar19 * 8);
      bVar8 = *(byte *)((long)puVar32 + (ulong)*(byte *)(lVar23 + 0x1b7) + 0x10);
      auStack_260[bVar8] = auStack_260[bVar8] + 1;
      if ((*(uint *)(lVar23 + 0x198) & 0x20400010) == 0x10) {
        piVar2 = (int *)(lVar23 + 0x1ac);
        do {
          cVar13 = '\x01';
          bVar14 = (bool)ExclusiveMonitorPass(piVar2,0x10);
          if (bVar14) {
            *piVar2 = *piVar2 + 1;
            cVar13 = ExclusiveMonitorsStatus();
          }
        } while (cVar13 != '\0');
        auStack_260[0] = auStack_260[0] + 1;
      }
      uVar19 = uVar19 + 1;
      if (uVar19 == uVar34) break;
      puVar32 = *(uint **)(param_1 + 0x4478);
    }
  }
  piVar2 = (int *)(param_1 + 0x106f8);
  if (0 < *piVar2) {
    lVar23 = 0;
    do {
      plVar17 = (long *)(param_1 + lVar23 * 8 + 0x104f8);
      plVar16 = (long *)*plVar17;
      uVar19 = (**(code **)(*plVar16 + 0x1f8))
                         (plVar16,abStack_2e0 + lVar23 * 2,0,param_2 + 1,auStack_260);
      if ((uVar19 & 1) == 0) {
        abStack_2e0[lVar23 * 2] = 0;
      }
      else {
        piVar3 = (int *)(*plVar17 + 0x1ac);
        do {
          cVar13 = '\x01';
          bVar14 = (bool)ExclusiveMonitorPass(piVar3,0x10);
          if (bVar14) {
            *piVar3 = *piVar3 + 1;
            cVar13 = ExclusiveMonitorsStatus();
          }
        } while (cVar13 != '\0');
        auStack_260[abStack_2e0[lVar23 * 2 + 1]] = auStack_260[abStack_2e0[lVar23 * 2 + 1]] + 1;
      }
      lVar23 = lVar23 + 1;
    } while (lVar23 < *piVar2);
  }
  if (0 < (int)uVar6) {
    uVar19 = 0;
    bVar14 = false;
    do {
      uVar18 = auStack_260[uVar19];
      acStack_360[uVar19] = '\0';
      if ((uVar18 != 0) &&
         ((bVar8 = *(byte *)(*(long *)(*(long *)(param_1 + 0x4478) + 8) + uVar19 * 2 + 1),
          (bVar8 >> 5 & 1) != 0 || (!bVar14 && (bVar8 & 0x10) != 0)))) {
        acStack_360[uVar19] = '\x01';
        void Aska::FrameTextureEntities::AddEntry<true>(int, int)(*(long *)(param_1 + 0x45b8) + 0x308,param_2 + 1,0);
        piVar3 = (int *)(*(long *)(param_1 + 0x45b8) + 0x1ac);
        do {
          cVar13 = '\x01';
          bVar14 = (bool)ExclusiveMonitorPass(piVar3,0x10);
          if (bVar14) {
            *piVar3 = *piVar3 + 1;
            cVar13 = ExclusiveMonitorsStatus();
          }
        } while (cVar13 != '\0');
        auStack_260[uVar19] = auStack_260[uVar19] + 1;
        bVar14 = true;
      }
      uVar19 = uVar19 + 1;
    } while (uVar19 != uVar33);
  }
  uVar11 = *puVar22;
  bVar8 = *(byte *)(*(long *)(param_1 + 0x4478) + 0x25);
  *(uint *)(param_1 + lVar27 * 4 + 0x1ea8) = auStack_260[0];
  asStack_560[0] = 0;
  auStack_460[0] = 0;
  if (1 < (int)uVar6) {
    auStack_460[1] = (short)auStack_260[0];
    asStack_560[1] = (short)auStack_260[0];
    if (uVar6 != 2) {
      puVar32 = auStack_260;
      lVar23 = uVar33 - 2;
      puVar22 = (ushort *)(asStack_560 + 2);
      puVar24 = auStack_460 + 2;
      uVar18 = auStack_260[0];
      do {
        puVar32 = puVar32 + 1;
        lVar23 = lVar23 + -1;
        uVar18 = *puVar32 + (uVar18 & 0xffff);
        *puVar24 = (ushort)uVar18;
        *puVar22 = (ushort)uVar18;
        puVar22 = puVar22 + 1;
        puVar24 = puVar24 + 1;
      } while (lVar23 != 0);
    }
  }
  iVar20 = *piVar2;
  if (0 < iVar20) {
    lVar23 = 0;
    pbVar25 = (byte *)((ulong)abStack_2e0 | 1);
    do {
      if (pbVar25[-1] == 1) {
        bVar9 = *pbVar25;
        uVar29 = *(undefined8 *)(param_1 + 0x104f8 + lVar23 * 8);
        lVar31 = *(long *)(param_1 + lVar27 * 0x10 + 0x10a0);
        uVar12 = auStack_460[bVar9];
        auStack_460[bVar9] = uVar12 + 1;
        *(undefined8 *)(lVar31 + (ulong)uVar12 * 8) = uVar29;
        asStack_560[bVar9] = asStack_560[bVar9] + 1;
        iVar20 = *piVar2;
      }
      lVar23 = lVar23 + 1;
      pbVar25 = pbVar25 + 2;
    } while (lVar23 < iVar20);
  }
  if (0 < (int)uVar6) {
    pcVar21 = acStack_360;
    puVar22 = auStack_460;
    psVar26 = asStack_560;
    uVar19 = uVar33;
    do {
      if (*pcVar21 != '\0') {
        uVar12 = *puVar22;
        uVar29 = *(undefined8 *)(param_1 + 0x45b8);
        lVar23 = *(long *)(param_1 + lVar27 * 0x10 + 0x10a0);
        *puVar22 = uVar12 + 1;
        *(undefined8 *)(lVar23 + (ulong)uVar12 * 8) = uVar29;
        *psVar26 = *psVar26 + 1;
      }
      pcVar21 = pcVar21 + 1;
      puVar22 = puVar22 + 1;
      uVar19 = uVar19 - 1;
      psVar26 = psVar26 + 1;
    } while (uVar19 != 0);
  }
  if (((uVar10 >> 1 & 1) == 0) || (*(char *)(param_1 + 0x3f0b) == '\0')) {
    if (0 < (int)uVar7) {
      lVar23 = param_1 + lVar27 * 0x10;
      uVar19 = 0;
      do {
        lVar30 = *(long *)(lVar23 + 0x10a0);
        lVar31 = *(long *)(*(long *)(lVar23 + 0x10a8) + uVar19 * 8);
        uVar19 = uVar19 + 1;
        bVar9 = *(byte *)(*(long *)(param_1 + 0x4478) + (ulong)*(byte *)(lVar31 + 0x1b7) + 0x10);
        uVar10 = auStack_460[bVar9];
        auStack_460[bVar9] = uVar10 + 1;
        *(long *)(lVar30 + (ulong)uVar10 * 8) = lVar31;
      } while (uVar34 != uVar19);
    }
  }
  else if (0 < (int)uVar7) {
    lVar23 = param_1 + lVar27 * 0x10;
    uVar19 = 0;
    plVar17 = (long *)(lVar23 + 0x10a0);
    do {
      lVar31 = *(long *)(*(long *)(lVar23 + 0x10a8) + uVar19 * 8);
      bVar9 = *(byte *)(*(long *)(param_1 + 0x4478) + (ulong)*(byte *)(lVar31 + 0x1b7) + 0x10);
      if ((*(uint *)(lVar31 + 0x198) & 0x20400010) == 0x10) {
        uVar28 = (ulong)auStack_460[0];
        auStack_460[0] = auStack_460[0] + 1;
        *(long *)(*plVar17 + uVar28 * 8) = lVar31;
      }
      uVar10 = auStack_460[bVar9];
      lVar30 = *plVar17;
      uVar19 = uVar19 + 1;
      auStack_460[bVar9] = uVar10 + 1;
      *(long *)(lVar30 + (ulong)uVar10 * 8) = lVar31;
    } while (uVar34 != uVar19);
  }
  memcpy(auStack_660,auStack_460,(long)(int)uVar6 << 1);
  iVar20 = *piVar2;
  if (0 < iVar20) {
    lVar23 = 0;
    pbVar25 = (byte *)((ulong)abStack_2e0 | 1);
    do {
      if (pbVar25[-1] == 2) {
        uVar29 = *(undefined8 *)(param_1 + 0x104f8 + lVar23 * 8);
        lVar31 = *(long *)(param_1 + lVar27 * 0x10 + 0x10a0);
        uVar10 = auStack_660[*pbVar25];
        auStack_660[*pbVar25] = uVar10 + 1;
        *(undefined8 *)(lVar31 + (ulong)uVar10 * 8) = uVar29;
        iVar20 = *piVar2;
      }
      lVar23 = lVar23 + 1;
      pbVar25 = pbVar25 + 2;
    } while (lVar23 < iVar20);
  }
  if (0 < (int)uVar6) {
    lVar23 = 0;
    puVar4 = (undefined8 *)(param_1 + lVar27 * 0x10 + 0x10a0);
    puVar5 = (undefined8 *)(param_1 + lVar27 * 8 + 0x3f50);
    do {
      lVar31 = *(long *)(*(long *)(param_1 + 0x4478) + 8);
      bVar9 = *(byte *)(lVar31 + lVar23 + 1);
      if ((bVar9 & 1) == 0) {
        if ((bVar9 >> 1 & 1) == 0) {
          if (((bVar9 >> 2 & 1) != 0) &&
             (plVar17 = *(long **)(param_1 + 0x1b00), plVar17 != (long *)0x0)) {
            (**(code **)(*plVar17 + 0x10))
                      (plVar17,*(undefined1 *)(lVar31 + lVar23),*puVar4,
                       *(undefined2 *)((long)asStack_560 + lVar23),
                       *(undefined2 *)((long)auStack_460 + lVar23));
          }
        }
        else {
          TOMQuickSort<Aska::RenderableObject, float, 64, 10>::Ascend(Aska::RenderableObject**, int, int, Aska::ObjectManager::RenderableObjectContext*)(*puVar4,*(undefined2 *)((long)asStack_560 + lVar23),
                          *(undefined2 *)((long)auStack_460 + lVar23),*puVar5);
        }
      }
      else {
        TOMQuickSort<Aska::RenderableObject, float, 64, 10>::Descend(Aska::RenderableObject**, int, int, Aska::ObjectManager::RenderableObjectContext*)(*puVar4,*(undefined2 *)((long)asStack_560 + lVar23),
                        *(undefined2 *)((long)auStack_460 + lVar23),*puVar5);
      }
      uVar33 = uVar33 - 1;
      lVar23 = lVar23 + 2;
    } while (uVar33 != 0);
  }
  uVar33 = (ulong)(bVar8 - 1);
  if ((uVar11 & 0x80) != 0) {
    uVar33 = (long)(int)uVar6 - 1;
  }
  uVar10 = auStack_460[uVar33];
  *(uint *)(lVar1 + 0x1c08) = (uint)uVar10;
  uVar15 = Aska::ObjectManager::MakeRenderInfoConditionList(Aska::ObjectManager::RenderInfoCond*, unsigned short*, int*, bool*, unsigned int)(param_1,param_1 + lVar27 * 0x38 + 0x2268,asStack_560,auStack_260);
  *(undefined1 *)(param_1 + lVar27 + 0x3e70) = uVar15;
  return (uint)uVar10;
}

// ==== Aska::ObjectManager::Prerender()
// vaddr 0x2161240 | ghidra 0x2261240 | size 2248 | symbol _ZN4Aska13ObjectManager9PrerenderEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13ObjectManager9PrerenderEv(long param_1)

{
  long *plVar1;
  int *piVar2;
  int *piVar3;
  uint uVar4;
  undefined1 *puVar5;
  undefined8 *puVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  byte bVar10;
  char cVar11;
  bool bVar12;
  undefined *puVar13;
  undefined4 uVar14;
  undefined4 uVar15;
  uint uVar16;
  long lVar17;
  int iVar18;
  undefined8 *puVar19;
  uint uVar20;
  long lVar21;
  long lVar22;
  ulong uVar23;
  ulong uVar24;
  long lVar25;
  long lVar26;
  long *plVar27;
  undefined8 *puVar28;
  int iVar29;
  long *plVar30;
  undefined8 uVar31;
  uint uVar32;
  undefined8 *puVar33;
  ulong uStack_70;
  ulong uStack_68;
  
  puVar5 = (undefined1 *)(param_1 + 0x3f09);
  if (*(char *)(param_1 + 0x3f0e) != '\0') {
    *puVar5 = 5;
    return;
  }
  *puVar5 = 3;
  *(undefined8 *)(param_1 + 0x45a8) = 0;
  *(undefined8 *)(param_1 + 0x45a0) = 0;
  *(undefined8 *)(param_1 + 0x4470) = 0;
  *(undefined8 *)(param_1 + 0x4468) = 0;
  if ((*(byte *)(param_1 + 0xb433) >> 1 & 1) != 0) {
    *(undefined8 *)(param_1 + 0x4468) = 1;
  }
  lVar26 = *(long *)(*(long *)PTR__ZN4Aska6Global16m_pCameraManagerE_02cb7d08 + 0xff0);
  if (lVar26 == 0) {
    *(undefined1 *)(param_1 + 0x3f0c) = 1;
    return;
  }
  Aska::Camera::MakeCameraMatrix()(lVar26);
  if (*(char *)(lVar26 + 0x940) == '\0') {
    Aska::Camera::MakeViewFrustumPlane(int)(lVar26,0xffffffff);
  }
  uStack_68 = *(ulong *)(param_1 + 0x4490);
  uStack_70 = *(ulong *)(param_1 + 0x4488);
  uVar9 = *(uint *)(param_1 + 0x3f20);
  uVar32 = uVar9;
  if ((int)uVar9 < 2) {
    uVar32 = 1;
  }
  if (0x20 < *(int *)(param_1 + 0x20)) {
    puVar19 = (undefined8 *)(*(long *)(param_1 + 0x1018) + 0x7fU & 0xffffffffffffff80);
    uVar16 = (*(int *)(param_1 + 0x20) * 4 + -0x80) -
             ((int)puVar19 - (int)*(long *)(param_1 + 0x1018)) & 0xffffff80;
    if (0 < (int)uVar16) {
      uVar16 = uVar16 >> 5;
      Hint_Prefetch(puVar19,2,2,0);
      if (uVar16 != 0) {
        iVar18 = -uVar16;
        do {
          Hint_Prefetch(puVar19 + 4,2,2,0);
          iVar18 = iVar18 + 1;
          puVar19[1] = 0;
          *puVar19 = 0;
          puVar19[3] = 0;
          puVar19[2] = 0;
          puVar19 = puVar19 + 4;
        } while (iVar18 != 0);
      }
    }
  }
  if (*(int *)(*(long *)PTR__ZN4Aska6Global14m_pLIBLManagerE_02cc46a8 + 0x88) != 0) {
    Aska::LIBLManager::Update()();
  }
  piVar2 = (int *)(param_1 + 0xf98);
  iVar18 = 0;
code_r0x02261394:
  do {
    if (*piVar2 != -1) {
      ClearExclusiveLocal();
      bVar12 = iVar18 < 0x1ff;
      iVar18 = iVar18 + 1;
      if (bVar12) goto code_r0x02261394;
      piVar3 = (int *)(param_1 + 0xf9c);
      do {
        cVar11 = '\x01';
        bVar12 = (bool)ExclusiveMonitorPass(piVar3,0x10);
        if (bVar12) {
          *piVar3 = *piVar3 + 1;
          cVar11 = ExclusiveMonitorsStatus();
        }
      } while (cVar11 != '\0');
      do {
        if (*piVar2 != -1) {
          ClearExclusiveLocal();
          do {
            uVar23 = Aska::Semaphore::IsReady() const(param_1 + 0xfd8);
            if ((uVar23 & 1) == 0) {
              do {
                cVar11 = '\x01';
                bVar12 = (bool)ExclusiveMonitorPass(piVar3,0x10);
                if (bVar12) {
                  *piVar3 = *piVar3 + -1;
                  cVar11 = ExclusiveMonitorsStatus();
                }
              } while (cVar11 != '\0');
              Aska::Thread::Sleep(unsigned int)(1);
            }
            else {
              Aska::Semaphore::Wait() const(param_1 + 0xfd8);
            }
            do {
              cVar11 = '\x01';
              bVar12 = (bool)ExclusiveMonitorPass(piVar3,0x10);
              if (bVar12) {
                *piVar3 = *piVar3 + 1;
                cVar11 = ExclusiveMonitorsStatus();
              }
            } while (cVar11 != '\0');
            while (*piVar2 == -1) {
              cVar11 = '\x01';
              bVar12 = (bool)ExclusiveMonitorPass(piVar2,0x10);
              if (bVar12) {
                *piVar2 = 0;
                cVar11 = ExclusiveMonitorsStatus();
              }
              if (cVar11 == '\0') goto code_r0x0226145c;
            }
            ClearExclusiveLocal();
          } while( true );
        }
        cVar11 = '\x01';
        bVar12 = (bool)ExclusiveMonitorPass(piVar2,0x10);
        if (bVar12) {
          *piVar2 = 0;
          cVar11 = ExclusiveMonitorsStatus();
        }
      } while (cVar11 != '\0');
code_r0x0226145c:
      do {
        cVar11 = '\x01';
        bVar12 = (bool)ExclusiveMonitorPass(piVar3,0x10);
        if (bVar12) {
          *piVar3 = *piVar3 + -1;
          cVar11 = ExclusiveMonitorsStatus();
        }
      } while (cVar11 != '\0');
code_r0x0226146c:
      DataMemoryBarrier(2,3);
      if (0 < (int)uVar32) {
        lVar17 = 0;
        do {
          lVar22 = lVar26 + lVar17;
          lVar17 = lVar17 + 1;
          if (*(char *)(lVar22 + 0x941) == '\0') {
            Aska::Camera::MakeViewFrustumPlane(int)(lVar26);
          }
        } while (lVar17 < (long)(ulong)uVar32);
      }
      uVar14 = Aska::ObjectManager::PrepareMatrices(int, Aska::RenderableObject**)(param_1,uVar32,*(undefined8 *)(param_1 + 0x1018));
      puVar13 = PTR__ZN4Aska6Global23m_pMeshGeneratorManagerE_02cc2bc0;
      Aska::MeshGeneratorManager::PrepareMatrices(Aska::Camera*)(*(undefined8 *)PTR__ZN4Aska6Global23m_pMeshGeneratorManagerE_02cc2bc0,lVar26);
      Aska::Event::Wait(unsigned int) const(*(long *)puVar13 + 0x50,0);
      Aska::OccluderManager::ResetOccluderFlag()(*(undefined8 *)PTR__ZN4Aska6Global18m_pOccluderManagerE_02cbbc98);
      *(undefined4 *)(param_1 + 0x3ef4) = 0;
      lVar17 = *(long *)PTR__ZN4Aska6Global29m_pObjectManagerJobDispatcherE_02cb8e98;
      if (lVar17 == 0) {
        *(undefined1 *)(param_1 + 0x3f0c) = 1;
        DataMemoryBarrier(2,3);
        *(undefined4 *)(param_1 + 0xf98) = 0xffffffff;
        DataMemoryBarrier(2,3);
        if (*(int *)(param_1 + 0xf9c) < 0x15) {
          return;
        }
        piVar2 = (int *)(param_1 + 0xf9c);
        do {
          cVar11 = '\x01';
          bVar12 = (bool)ExclusiveMonitorPass(piVar2,0x10);
          if (bVar12) {
            *piVar2 = *piVar2 + -1;
            cVar11 = ExclusiveMonitorsStatus();
          }
        } while (cVar11 != '\0');
        goto code_r0x02261aec;
      }
      Aska::SimpleMessageDispatcher::SuspendWorkerThread()(*(undefined8 *)PTR__ZN4Aska6Global20m_pMessageDispatcherE_02cb77c8);
      Aska::ObjectManagerJobDispatcher::ChangeMode(int)(lVar17,4);
      uVar31 = *(undefined8 *)(param_1 + 0x1020 + (ulong)(1 < (int)uVar9) * 8);
      plVar30 = *(long **)(param_1 + 0x1020 + (ulong)((int)uVar9 < 2) * 8);
      uVar15 = Aska::ObjectManager::MultithreadViewFrustumCulling(Aska::Camera*, int, int, Aska::RenderableObject**, Aska::RenderableObject**, int)(param_1,lVar26,0,0xffffffff,*(undefined8 *)(param_1 + 0x1018),uVar31,
                               uVar14);
      uVar16 = Aska::ObjectManager::MultithreadOcclusionCulling(Aska::Camera*, int, int, bool, Aska::RenderableObject**, Aska::RenderableObject**, int)(param_1,lVar26,0,0xffffffff,(ulong)((int)uVar9 < 2),uVar31,plVar30,
                               uVar15);
      Aska::MeshGeneratorManager::InstanceCulling(Aska::Camera*)(*(undefined8 *)puVar13,lVar26);
      if (0 < (int)uVar16) {
        if (uVar16 == 1) {
          lVar22 = 0;
        }
        else {
          lVar22 = (ulong)uVar16 - (ulong)(uVar16 & 1);
          if (lVar22 != 0) {
            uVar23 = 0;
            uVar24 = 0;
            plVar27 = plVar30 + 1;
            lVar21 = lVar22;
            do {
              plVar1 = plVar27 + -1;
              lVar25 = *plVar27;
              lVar21 = lVar21 + -2;
              plVar27 = plVar27 + 2;
              uStack_70 = uStack_70 | *(ulong *)(*plVar1 + 0x218);
              uVar24 = uVar24 | *(ulong *)(lVar25 + 0x218);
              uStack_68 = uStack_68 | *(ulong *)(*plVar1 + 0x220);
              uVar23 = uVar23 | *(ulong *)(lVar25 + 0x220);
            } while (lVar21 != 0);
            uStack_70 = uVar24 | uStack_70;
            uStack_68 = uVar23 | uStack_68;
            if ((uVar16 & 1) == 0) goto code_r0x02261690;
          }
        }
        lVar21 = (ulong)uVar16 - lVar22;
        plVar27 = plVar30 + lVar22;
        do {
          lVar21 = lVar21 + -1;
          uStack_70 = uStack_70 | *(ulong *)(*plVar27 + 0x218);
          uStack_68 = uStack_68 | *(ulong *)(*plVar27 + 0x220);
          plVar27 = plVar27 + 1;
        } while (lVar21 != 0);
      }
code_r0x02261690:
      uStack_70 = uStack_70 |
                  *(ulong *)(*(long *)PTR__ZN4Aska6Global19m_pProjectorManagerE_02cb70f8 + 0xff0);
      uStack_68 = uStack_68 |
                  *(ulong *)(*(long *)PTR__ZN4Aska6Global19m_pProjectorManagerE_02cb70f8 + 0xff8);
      *puVar5 = 4;
      lVar21 = *(long *)(param_1 + 0x4478);
      lVar22 = *(long *)(param_1 + 0x1010);
      bVar10 = *(byte *)(lVar21 + 0x25);
      if ((int)uVar9 < 2) {
        if (0 < (int)uVar16) {
          uVar23 = (ulong)uVar16;
          iVar18 = 0;
          iVar29 = 0;
          plVar27 = plVar30;
          while( true ) {
            uVar23 = uVar23 - 1;
            lVar25 = *plVar27;
            if (*(byte *)(lVar21 + (ulong)*(byte *)(lVar25 + 0x1b7) + 0x10) < bVar10) {
              plVar30[iVar18] = lVar25;
              iVar18 = iVar18 + 1;
            }
            else {
              *(ushort *)(lVar25 + 0x1b5) = *(ushort *)(lVar25 + 0x1b5) | 0x100;
              *(long *)(lVar22 + (long)iVar29 * 8) = lVar25;
              iVar29 = iVar29 + 1;
            }
            if (uVar23 == 0) break;
            lVar21 = *(long *)(param_1 + 0x4478);
            plVar27 = plVar27 + 1;
          }
          goto code_r0x022617e8;
        }
        *(undefined4 *)(param_1 + 0x1bc4) = 0;
        Aska::ObjectManager::Prerender_VersatileAndMotionBlur(Aska::RenderableObject**, int, Aska::Camera*)(param_1,plVar30,0,lVar26);
        iVar18 = 0;
code_r0x02261854:
        *(int *)(param_1 + 0x1bc8) = iVar18;
      }
      else {
        if ((int)uVar16 < 1) {
          iVar29 = 0;
          iVar18 = 0;
        }
        else {
          uVar23 = 0;
          iVar18 = 0;
          iVar29 = 0;
          while( true ) {
            lVar25 = plVar30[uVar23];
            if (*(byte *)(lVar21 + (ulong)*(byte *)(lVar25 + 0x1b7) + 0x10) < bVar10) {
              plVar30[iVar18] = lVar25;
              iVar18 = iVar18 + 1;
            }
            else {
              piVar2 = (int *)(lVar25 + 0x1ac);
              do {
                cVar11 = '\x01';
                bVar12 = (bool)ExclusiveMonitorPass(piVar2,0x10);
                if (bVar12) {
                  *piVar2 = *piVar2 + 1;
                  cVar11 = ExclusiveMonitorsStatus();
                }
              } while (cVar11 != '\0');
              *(ushort *)(lVar25 + 0x1b5) = *(ushort *)(lVar25 + 0x1b5) | 0x100;
              *(long *)(lVar22 + (long)iVar29 * 8) = lVar25;
              iVar29 = iVar29 + 1;
            }
            uVar23 = uVar23 + 1;
            if (uVar23 == uVar16) break;
            lVar21 = *(long *)(param_1 + 0x4478);
          }
        }
code_r0x022617e8:
        *(int *)(param_1 + 0x1bc4) = iVar29;
        Aska::ObjectManager::Prerender_VersatileAndMotionBlur(Aska::RenderableObject**, int, Aska::Camera*)(param_1,plVar30,iVar18,lVar26);
        if ((int)uVar9 < 2) goto code_r0x02261854;
        lVar22 = 0x6f2;
        lVar21 = 0x1028;
        do {
          uVar15 = Aska::ObjectManager::MultithreadSubViewFrustumCulling(Aska::Camera*, int, int, Aska::RenderableObject**, Aska::RenderableObject**, int)(param_1,lVar26,0,(int)lVar22 + -0x6f2,plVar30,
                                   *(undefined8 *)(param_1 + lVar21),iVar18);
          *(undefined4 *)(param_1 + lVar22 * 4) = uVar15;
          lVar22 = lVar22 + 1;
          lVar21 = lVar21 + 0x10;
        } while (lVar22 - (ulong)uVar32 != 0x6f2);
      }
      plVar30 = (long *)(param_1 + 0xb418);
      *(long *)(*plVar30 + 0x478) = lVar26;
      Aska::PostProcessCombinerTBR::AddPostFiltersToPaintingListCandidates(Aska::ObjectManager*)(*plVar30,param_1);
      Aska::ObjectManager::Prerender_MultiPass(Aska::TLongInt<unsigned long, 2>*, int, Aska::ObjectManagerJobDispatcher*)(param_1,&uStack_70,uVar14);
      puVar19 = (undefined8 *)PTR__ZN4Aska6Global15m_pLightManagerE_02cc1770;
      lVar26 = *(long *)PTR__ZN4Aska6Global15m_pLightManagerE_02cc1770;
      *(undefined2 *)(lVar26 + 0x2ffa) = 0;
      if (*(int *)(*(long *)PTR__ZN4Aska6Global14m_pLIBLManagerE_02cc46a8 + 0x88) != 0) {
        puVar28 = *(undefined8 **)(param_1 + 0x18a0);
        puVar19 = puVar28;
        if (0 < *(int *)(param_1 + 0x3ef4)) {
          puVar33 = *(undefined8 **)(param_1 + 0x1ac8);
          puVar6 = puVar33 + *(int *)(param_1 + 0x3ef4);
          do {
            plVar27 = (long *)*puVar33;
            if (((char)plVar27[0x49] == '\0') || (plVar27[0x4c] == 0)) {
code_r0x0226192c:
              plVar27[0x47] = 0;
              plVar27[0x46] = 0;
            }
            else {
              uVar32 = *(uint *)(plVar27 + 0x36);
              uVar23 = (**(code **)(*plVar27 + 0x268))(plVar27);
              if ((((uVar32 & 7) == 0) && ((uVar23 & 1) == 0)) &&
                 (((uVar32 & 0x600) == 0 || ((*(byte *)(plVar27 + 0x32) & 0x1c) == 0))))
              goto code_r0x0226192c;
              *puVar19 = plVar27;
              puVar19 = puVar19 + 1;
            }
            puVar33 = puVar33 + 1;
          } while (puVar33 < puVar6);
        }
        iVar18 = (int)((ulong)((long)puVar19 - (long)puVar28) >> 3);
        *(int *)(param_1 + 0x18a8) = iVar18;
        puVar19 = (undefined8 *)PTR__ZN4Aska6Global15m_pLightManagerE_02cc1770;
        if (0 < iVar18) {
          *(undefined2 *)(lVar26 + 0x2ffa) = 1;
          Aska::ObjectManagerJobDispatcher::ChangeMode(int)(lVar17,5);
          uVar9 = *(uint *)(param_1 + 0x18a8);
          uVar31 = *(undefined8 *)(param_1 + 0x18a0);
          lVar26 = *(long *)PTR__ZN4Aska6Global29m_pObjectManagerJobDispatcherE_02cb8e98;
          iVar18 = *(int *)(lVar26 + 0xac) + 1;
          uVar32 = 0;
          if (iVar18 != 0) {
            uVar32 = (int)uVar9 / iVar18;
          }
          if ((int)uVar32 < 9) {
            uVar32 = 8;
          }
          uVar16 = uVar32;
          if (0xff < (int)uVar32) {
            uVar16 = 0x100;
          }
          Aska::ObjectManagerJobDispatcher::SetDetectLIBLBasicParameter(Aska::RenderableObject**)(lVar26);
          puVar19 = (undefined8 *)PTR__ZN4Aska6Global15m_pLightManagerE_02cc1770;
          if (0 < (int)uVar9) {
            uVar20 = 0xfffffeff;
            if (-0x101 < (int)~uVar32) {
              uVar20 = ~uVar32;
            }
            iVar18 = uVar20 + 1;
            iVar29 = -1;
            uVar32 = 0;
            do {
              uVar4 = uVar32 + uVar16;
              uVar7 = uVar20;
              if ((int)uVar20 <= (int)~uVar9) {
                uVar7 = ~uVar9;
              }
              uVar8 = uVar4;
              if ((int)uVar9 <= (int)uVar4) {
                uVar8 = uVar9;
              }
              uVar23 = Aska::ObjectManagerJobDispatcher::Dispatch_DetectLIBL(int, int)(lVar26,uVar32,uVar8 - 1);
              if ((uVar23 & 1) == 0) {
                Aska::LIBLManager::Intersect(Aska::RenderableObject**, int, int)(*(undefined8 *)PTR__ZN4Aska6Global14m_pLIBLManagerE_02cc46a8,uVar31,
                                uVar32,iVar29 - uVar7);
              }
              iVar29 = iVar29 + iVar18;
              uVar20 = uVar20 + iVar18;
              puVar19 = (undefined8 *)PTR__ZN4Aska6Global15m_pLightManagerE_02cc1770;
              uVar32 = uVar4;
            } while ((int)uVar4 < (int)uVar9);
          }
        }
      }
      puVar13 = PTR__ZN4Aska6Global20m_pMessageDispatcherE_02cb77c8;
      Aska::LightManager::PrepareLightsForRendering(Aska::RenderableObject**, int)(*puVar19,*(undefined8 *)(param_1 + 0x1ac8),*(undefined4 *)(param_1 + 0x3ef4));
      Aska::ObjectManagerJobDispatcher::Sleep()(lVar17);
      Aska::SimpleMessageDispatcher::ResumeWorkerThread()(*(undefined8 *)puVar13);
      Aska::ToneMapTable::UpdateToneCurveTextures(Aska::Camera*)(*plVar30 + 0x310,*(undefined8 *)(*plVar30 + 0x478));
      *puVar5 = 5;
      *(undefined1 *)(param_1 + 0x3f0c) = 1;
      DataMemoryBarrier(2,3);
      *(undefined4 *)(param_1 + 0xf98) = 0xffffffff;
      DataMemoryBarrier(2,3);
      if (*(int *)(param_1 + 0xf9c) < 0x15) {
        return;
      }
      piVar2 = (int *)(param_1 + 0xf9c);
      do {
        cVar11 = '\x01';
        bVar12 = (bool)ExclusiveMonitorPass(piVar2,0x10);
        if (bVar12) {
          *piVar2 = *piVar2 + -1;
          cVar11 = ExclusiveMonitorsStatus();
        }
      } while (cVar11 != '\0');
code_r0x02261aec:
      uVar23 = Aska::Semaphore::IsReady() const(param_1 + 0xfd8);
      if ((uVar23 & 1) != 0) {
        Aska::Semaphore::Signal() const(param_1 + 0xfd8);
      }
      return;
    }
    cVar11 = '\x01';
    bVar12 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar12) {
      *piVar2 = 0;
      cVar11 = ExclusiveMonitorsStatus();
    }
    if (cVar11 == '\0') goto code_r0x0226146c;
  } while( true );
}

// ==== Aska::ObjectManager::PrepareMatrices(int, Aska::RenderableObject**)
// vaddr 0x2161b08 | ghidra 0x2261b08 | size 912 | symbol _ZN4Aska13ObjectManager15PrepareMatricesEiPPNS_16RenderableObjectE | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZN4Aska13ObjectManager15PrepareMatricesEiPPNS_16RenderableObjectE
                (long param_1,uint param_2,long param_3)

{
  long *plVar1;
  ushort *puVar2;
  ushort *puVar3;
  long lVar4;
  uint uVar5;
  ushort uVar6;
  ulong uVar7;
  ulong uVar8;
  int iVar9;
  undefined8 uVar10;
  long *plVar11;
  long *plVar12;
  long lVar13;
  long *plVar14;
  long *plVar15;
  
  plVar14 = *(long **)(param_1 + 0x18);
  puVar3 = (ushort *)(param_1 + 0x3f00);
  plVar1 = (long *)(param_1 + 8);
  *puVar3 = 0;
  Aska::HierarchicalObjectContainer::OpenIterator()();
  uVar10 = *(undefined8 *)PTR__ZN4Aska6Global29m_pObjectManagerJobDispatcherE_02cb8e98;
  Aska::SimpleMessageDispatcher::SuspendWorkerThread()(*(undefined8 *)PTR__ZN4Aska6Global20m_pMessageDispatcherE_02cb77c8);
  Aska::ObjectManagerJobDispatcher::ChangeMode(int)(uVar10,6);
  if (plVar1 != plVar14) {
    iVar9 = 0;
    plVar12 = (long *)0x0;
    do {
      while( true ) {
        plVar15 = (long *)plVar14[2];
        plVar11 = plVar14;
        if (plVar12 != (long *)0x0) {
          plVar11 = plVar12;
        }
        if ((0x4e < iVar9) || (plVar1 == plVar15)) break;
        iVar9 = iVar9 + 1;
        plVar12 = plVar11;
        plVar14 = plVar15;
        if (plVar1 == plVar15) goto code_r0x02261c98;
      }
      uVar7 = Aska::ObjectManagerJobDispatcher::Dispatch_ResetSystemFlags(Aska::RenderableObject*, Aska::RenderableObject*)(uVar10,plVar11,plVar14);
      if ((uVar7 & 1) == 0) {
        do {
          puVar2 = (ushort *)((long)plVar11 + 0x1b5);
          *(uint *)(plVar11 + 0x33) = *(uint *)(plVar11 + 0x33) & 0xdfffffbf;
          *puVar2 = *puVar2 & 0xfefe;
          *(undefined4 *)((long)plVar11 + 0x1ac) = 0;
          plVar11[0x3a] = 0;
          *(undefined4 *)((long)plVar11 + 0x1cc) = 0;
          (**(code **)(*plVar11 + 0x198))(plVar11);
          plVar11[0x47] = 0;
          plVar11[0x46] = 0;
          plVar11[0x40] = 0;
          plVar11[0x3f] = 0;
          plVar11[0x3e] = 0;
          plVar11[0x3d] = 0;
          *puVar2 = *puVar2 & 0xfff9;
          uVar5 = *(uint *)(plVar11 + 0x33);
          *(uint *)(plVar11 + 0x33) = uVar5 | 0x124;
          if ((uVar5 & 0x6081) != 0) {
            if ((uVar5 >> 0x19 & 1) != 0) {
              (**(code **)(*plVar11 + 0x1f0))(plVar11);
            }
            if ((uVar5 >> 0x15 & 1) != 0) {
              (**(code **)(*plVar11 + 0x298))(plVar11);
            }
          }
        } while ((plVar11 != plVar14) && (plVar11 = (long *)plVar11[2], plVar1 != plVar11));
      }
      plVar12 = (long *)0x0;
      iVar9 = 0;
      plVar14 = plVar15;
    } while (plVar1 != plVar15);
  }
code_r0x02261c98:
  plVar14 = *(long **)(param_1 + 0x18);
  Aska::SimpleMessageDispatcher::ResumeWorkerThread()(*(undefined8 *)PTR__ZN4Aska6Global20m_pMessageDispatcherE_02cb77c8);
  if ((int)param_2 < 0) {
    uVar7 = 0;
    while (plVar12 = plVar14, plVar1 != plVar12) {
      uVar5 = *(uint *)(plVar12 + 0x33);
      plVar14 = (long *)plVar12[2];
      if (((uVar5 >> 0x1a & 1) != 0) && (uVar8 = Aska::IAnimatable::IsThisIt(unsigned short) const(plVar12,0xf113), (uVar8 & 1) != 0))
      {
        uVar6 = *puVar3;
        *puVar3 = uVar6 + 1;
        *(long **)(*(long *)(param_1 + 0x1af0) + (ulong)uVar6 * 8) = plVar12;
      }
      if ((uVar5 & 0x6081) == 0) {
        if ((uVar5 >> 0x17 & 1) != 0) {
          Aska::Camera::MakeCameraMatrix()(plVar12[0x34]);
        }
        if ((*(byte *)(plVar12 + 0x25) & 1) != 0) {
          if (*(char *)((long)plVar12 + 0x197) == '\0') {
            uVar8 = Aska::HierarchicalObjectContainer::AddToIterator()(plVar12 + 6);
            if ((uVar8 & 1) != 0) goto code_r0x02261dbc;
          }
          else {
            (**(code **)(*plVar12 + 0xa8))(plVar12);
          }
          lVar13 = (**(code **)(*plVar12 + 0x98))(plVar12);
          plVar12[0x24] = lVar13;
        }
code_r0x02261dbc:
        *(short *)(plVar12 + 0x37) = (short)uVar7;
        *(long **)(param_3 + uVar7 * 8) = plVar12;
        uVar7 = uVar7 + 1;
      }
    }
  }
  else {
    uVar7 = 0;
    while (plVar12 = plVar14, plVar1 != plVar12) {
      uVar5 = *(uint *)(plVar12 + 0x33);
      plVar14 = (long *)plVar12[2];
      if (((uVar5 >> 0x1a & 1) != 0) && (uVar8 = Aska::IAnimatable::IsThisIt(unsigned short) const(plVar12,0xf113), (uVar8 & 1) != 0))
      {
        uVar6 = *puVar3;
        *puVar3 = uVar6 + 1;
        *(long **)(*(long *)(param_1 + 0x1af0) + (ulong)uVar6 * 8) = plVar12;
      }
      if ((uVar5 & 0x6081) == 0) {
        if ((uVar5 >> 0x17 & 1) != 0) {
          lVar13 = plVar12[0x34];
          Aska::Camera::MakeCameraMatrix()(lVar13);
          uVar8 = 0xffffffffffffffff;
          do {
            lVar4 = lVar13 + uVar8;
            uVar8 = uVar8 + 1;
            if (*(char *)(lVar4 + 0x941) == '\0') {
              Aska::Camera::MakeViewFrustumPlane(int)(lVar13);
            }
          } while (param_2 != uVar8);
        }
        if ((*(byte *)(plVar12 + 0x25) & 1) != 0) {
          if (*(char *)((long)plVar12 + 0x197) == '\0') {
            uVar8 = Aska::HierarchicalObjectContainer::AddToIterator()(plVar12 + 6);
            if ((uVar8 & 1) != 0) goto code_r0x02261d10;
          }
          else {
            (**(code **)(*plVar12 + 0xa8))(plVar12);
          }
          lVar13 = (**(code **)(*plVar12 + 0x98))(plVar12);
          plVar12[0x24] = lVar13;
        }
code_r0x02261d10:
        *(short *)(plVar12 + 0x37) = (short)uVar7;
        *(long **)(param_3 + uVar7 * 8) = plVar12;
        uVar7 = uVar7 + 1;
      }
    }
  }
  *(short *)(param_1 + 0x4452) = (short)uVar7;
  Aska::HierarchicalObjectContainer::IterateMakeMatrix()();
  return uVar7 & 0xffffffff;
}

// ==== Aska::ObjectManager::MultithreadViewFrustumCulling(Aska::Camera*, int, int, Aska::RenderableObject**, Aska::RenderableObject**, int)
// vaddr 0x2161e98 | ghidra 0x2261e98 | size 916 | symbol _ZN4Aska13ObjectManager29MultithreadViewFrustumCullingEPNS_6CameraEiiPPNS_16RenderableObjectES5_i | lib libSOA-3.7.0.so | 2026-10-04
int _ZN4Aska13ObjectManager29MultithreadViewFrustumCullingEPNS_6CameraEiiPPNS_16RenderableObjectES5_i
              (long param_1,undefined8 param_2,int param_3,undefined4 param_4,long param_5,
              long *param_6,int param_7)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  undefined1 auVar4 [16];
  long lVar5;
  ulong uVar6;
  long *plVar7;
  int iVar8;
  ulong uVar9;
  int iVar10;
  long *plVar11;
  int iVar12;
  long lVar13;
  int iVar14;
  long *plVar15;
  long *plStack_68;
  
  if (*(int *)(param_1 + 0x1ba8) < param_7) {
    *(int *)(param_1 + 0x1ba8) = param_7;
    if (*(long *)(param_1 + 0x1ba0) != 0) {
      operator delete[](void*)();
    }
    uVar1 = param_7 + 0x3e;
    if (-1 < (int)(param_7 + 0x1fU)) {
      uVar1 = param_7 + 0x1fU;
    }
    uVar6 = (long)((ulong)uVar1 << 0x20) >> 0x25;
    uVar9 = -(ulong)((uint)((int)uVar1 >> 5) >> 0x1f) & 0xfffffff800000000 |
            (ulong)(uint)((int)uVar1 >> 5) << 3;
    auVar4._8_8_ = 0;
    auVar4._0_8_ = uVar6;
    if (SUB168(auVar4 * ZEXT816(8),8) != 0) {
      uVar9 = 0xffffffffffffffff;
    }
    lVar5 = operator new[](unsigned long, std::nothrow_t const&)(uVar9,PTR__ZSt7nothrow_02cb9a80);
    *(long *)(param_1 + 0x1ba0) = lVar5;
    if (lVar5 == 0) {
      return 0;
    }
  }
  else {
    lVar5 = *(long *)(param_1 + 0x1ba0);
    uVar1 = param_7 + 0x3e;
    if (-1 < (int)(param_7 + 0x1fU)) {
      uVar1 = param_7 + 0x1fU;
    }
    uVar6 = (long)((ulong)uVar1 << 0x20) >> 0x25;
  }
  plVar11 = (long *)(param_1 + 0x1ba0);
  memset(lVar5,0,uVar6 << 3);
  lVar5 = *(long *)PTR__ZN4Aska6Global29m_pObjectManagerJobDispatcherE_02cb8e98;
  Aska::ObjectManagerJobDispatcher::SetViewFrustumCullingBasicParameter(Aska::Camera*, int, int, Aska::RenderableObject**, unsigned long*)(lVar5,param_2,param_3,param_4,param_5,*plVar11);
  *(undefined8 *)(param_5 + (long)param_7 * 8) = *(undefined8 *)(param_5 + ((long)param_7 + -1) * 8)
  ;
  iVar2 = *(int *)(lVar5 + 0xac);
  iVar3 = 0;
  if (iVar2 != 0) {
    iVar3 = param_7 / iVar2;
  }
  if (iVar3 < 9) {
    iVar3 = 8;
  }
  if (0xff < iVar3) {
    iVar3 = 0x100;
  }
  if (iVar2 < 5) {
    iVar12 = 10;
  }
  else {
    iVar12 = (iVar2 + -4) * 2 + 10;
    iVar3 = iVar3 + (iVar2 + -4) * 0x40;
  }
  if (param_7 < 1) {
    return 0;
  }
  lVar13 = 0;
  iVar10 = 0;
  iVar14 = 0;
  plStack_68 = param_6;
  do {
    while( true ) {
      iVar8 = iVar10;
      if (iVar10 < param_7) {
        iVar8 = iVar10 + iVar3;
        if (param_7 <= iVar10 + iVar3) {
          iVar8 = param_7;
        }
        uVar6 = Aska::ObjectManagerJobDispatcher::Dispatch_ViewFrustumCulling(int, int, int)(lVar5,0,iVar10,iVar8 + -1);
        if ((uVar6 & 1) == 0) {
          iVar8 = iVar10;
        }
        if ((iVar2 < 3) && ((uVar6 & 1) == 0)) {
          iVar8 = (int)((long)param_7 + -1);
          if (iVar10 + 2 < param_7) {
            iVar8 = iVar10 + 1;
          }
          Aska::ObjectManager::ViewFrustumCulling(Aska::Camera*, int, int, Aska::RenderableObject**, int, int, unsigned long*)(param_1,param_2,param_3,param_4,param_5,iVar10,iVar8,
                          *(undefined8 *)(param_1 + 0x1ba0));
          iVar8 = iVar8 + 1;
        }
      }
      iVar10 = iVar8;
      if ((0 < iVar12) && ((int)lVar13 < iVar10)) break;
code_r0x0226214c:
      if (param_7 <= (int)lVar13) {
        return iVar14;
      }
    }
    lVar13 = (long)(int)lVar13;
    if (param_3 != 0) {
      uVar6 = lVar13 << 1;
      iVar8 = 1;
      plVar15 = plStack_68;
      do {
        uVar9 = *(ulong *)(*plVar11 + (long)((int)lVar13 >> 5) * 8) >> (uVar6 & 0x3e);
        plStack_68 = plVar15;
        if ((uVar9 & 3) == 0) break;
        plVar7 = *(long **)(param_5 + lVar13 * 8);
        uVar1 = (uint)uVar9 & 3;
        if (uVar1 == 1) {
          iVar14 = iVar14 + 1;
          plStack_68 = plVar15 + 1;
          *plVar15 = (long)plVar7;
        }
        else if ((uVar1 == 2) && ((*(byte *)((long)plVar7 + 0x19b) >> 1 & 1) != 0)) {
          (**(code **)(*plVar7 + 0x1f0))();
        }
        lVar13 = lVar13 + 1;
        if (iVar12 <= iVar8) break;
        uVar6 = uVar6 + 2;
        iVar8 = iVar8 + 1;
        plVar15 = plStack_68;
      } while (lVar13 < iVar10);
      goto code_r0x0226214c;
    }
    uVar6 = lVar13 << 1;
    iVar8 = 1;
    do {
      uVar9 = *(ulong *)(*plVar11 + (long)((int)lVar13 >> 5) * 8) >> (uVar6 & 0x3e);
      if ((uVar9 & 3) == 0) break;
      plVar15 = *(long **)(param_5 + lVar13 * 8);
      uVar1 = (uint)uVar9 & 3;
      if (uVar1 == 2) {
        uVar1 = *(uint *)(plVar15 + 0x33);
        if ((uVar1 >> 0x19 & 1) != 0) {
          (**(code **)(*plVar15 + 0x1f0))(plVar15);
        }
        if ((uVar1 >> 0x15 & 1) != 0) {
          (**(code **)(*plVar15 + 0x298))(plVar15);
        }
      }
      else if (uVar1 == 1) {
        iVar14 = iVar14 + 1;
        *plStack_68 = (long)plVar15;
        plStack_68 = plStack_68 + 1;
      }
      lVar13 = lVar13 + 1;
      if (iVar12 <= iVar8) break;
      uVar6 = uVar6 + 2;
      iVar8 = iVar8 + 1;
    } while (lVar13 < iVar10);
    if (param_7 <= (int)lVar13) {
      return iVar14;
    }
  } while( true );
}

// ==== Aska::ObjectManager::MultithreadOcclusionCulling(Aska::Camera*, int, int, bool, Aska::RenderableObject**, Aska::RenderableObject**, int)
// vaddr 0x216222c | ghidra 0x226222c | size 1660 | symbol _ZN4Aska13ObjectManager27MultithreadOcclusionCullingEPNS_6CameraEiibPPNS_16RenderableObjectES5_i | lib libSOA-3.7.0.so | 2026-10-04
int _ZN4Aska13ObjectManager27MultithreadOcclusionCullingEPNS_6CameraEiibPPNS_16RenderableObjectES5_i
              (long param_1,undefined8 param_2,int param_3,undefined4 param_4,uint param_5,
              undefined8 *param_6,undefined8 *param_7,int param_8)

{
  bool bVar1;
  int *piVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  long lVar6;
  char cVar7;
  undefined1 auVar8 [16];
  long lVar9;
  ulong uVar10;
  undefined8 *puVar11;
  int iVar12;
  ulong uVar13;
  int iVar14;
  int iVar15;
  long *plVar16;
  int iStack_80;
  
  if (*(int *)(param_1 + 0x1ba8) < param_8) {
    *(int *)(param_1 + 0x1ba8) = param_8;
    if (*(long *)(param_1 + 0x1ba0) != 0) {
      operator delete[](void*)();
    }
    uVar3 = param_8 + 0x3e;
    if (-1 < (int)(param_8 + 0x1fU)) {
      uVar3 = param_8 + 0x1fU;
    }
    uVar13 = (long)((ulong)uVar3 << 0x20) >> 0x25;
    uVar10 = -(ulong)((uint)((int)uVar3 >> 5) >> 0x1f) & 0xfffffff800000000 |
             (ulong)(uint)((int)uVar3 >> 5) << 3;
    auVar8._8_8_ = 0;
    auVar8._0_8_ = uVar13;
    if (SUB168(auVar8 * ZEXT816(8),8) != 0) {
      uVar10 = 0xffffffffffffffff;
    }
    lVar9 = operator new[](unsigned long, std::nothrow_t const&)(uVar10,PTR__ZSt7nothrow_02cb9a80);
    *(long *)(param_1 + 0x1ba0) = lVar9;
    if (lVar9 == 0) {
      return 0;
    }
  }
  else {
    lVar9 = *(long *)(param_1 + 0x1ba0);
    uVar3 = param_8 + 0x3e;
    if (-1 < (int)(param_8 + 0x1fU)) {
      uVar3 = param_8 + 0x1fU;
    }
    uVar13 = (long)((ulong)uVar3 << 0x20) >> 0x25;
  }
  memset(lVar9,0,uVar13 << 3);
  lVar9 = *(long *)PTR__ZN4Aska6Global18m_pOccluderManagerE_02cbbc98;
  if ((param_8 != 0) && (*(char *)(param_1 + 0x3f12) != '\0')) {
    Aska::OccluderManager::MakeOccluderList(Aska::Camera*, int, int)(lVar9,param_2,param_4,param_3);
  }
  if ((*(int *)(lVar9 + 0x5c0) == 0) || (*(char *)(param_1 + 0x3f12) == '\0')) {
    if ((param_5 & 1) == 0) {
      if (param_8 < 1) {
        return param_8;
      }
      if (param_3 == 0) {
        lVar9 = 0;
        do {
          plVar16 = (long *)param_6[lVar9];
          *(uint *)(plVar16 + 0x33) = *(uint *)(plVar16 + 0x33) | 0x40;
          if ((*(byte *)((long)plVar16 + 0x1b5) >> 3 & 1) == 0) {
            iVar12 = *(int *)(param_1 + 0x3ef4);
            *(int *)(param_1 + 0x3ef4) = iVar12 + 1;
            *(long **)(*(long *)(param_1 + 0x1ac8) + (long)iVar12 * 8) = plVar16;
            *(ushort *)((long)plVar16 + 0x1b5) = *(ushort *)((long)plVar16 + 0x1b5) | 8;
            uVar3 = *(uint *)(plVar16 + 0x33);
            *(uint *)(plVar16 + 0x33) = uVar3 & 0xfffffeff;
            if ((uVar3 >> 9 & 1) != 0) {
              (**(code **)(*plVar16 + 0x270))(plVar16);
            }
          }
          param_7[lVar9] = plVar16;
          lVar9 = lVar9 + 1;
        } while (param_8 != (int)lVar9);
        return param_8;
      }
      lVar9 = (long)((ulong)(param_3 - 1U) << 0x20) >> 0x26;
      iVar12 = param_8;
      do {
        plVar16 = (long *)*param_6;
        plVar16[lVar9 + 0x3f] = plVar16[lVar9 + 0x3f] | 1L << ((long)(int)(param_3 - 1U) & 0x3fU);
        if ((*(byte *)((long)plVar16 + 0x1b5) >> 3 & 1) == 0) {
          iVar15 = *(int *)(param_1 + 0x3ef4);
          *(int *)(param_1 + 0x3ef4) = iVar15 + 1;
          *(long **)(*(long *)(param_1 + 0x1ac8) + (long)iVar15 * 8) = plVar16;
          *(ushort *)((long)plVar16 + 0x1b5) = *(ushort *)((long)plVar16 + 0x1b5) | 8;
          uVar3 = *(uint *)(plVar16 + 0x33);
          *(uint *)(plVar16 + 0x33) = uVar3 & 0xfffffeff;
          if ((uVar3 >> 9 & 1) != 0) {
            (**(code **)(*plVar16 + 0x270))(plVar16);
          }
        }
        iVar12 = iVar12 + -1;
        *param_7 = plVar16;
        param_7 = param_7 + 1;
        param_6 = param_6 + 1;
      } while (iVar12 != 0);
      return param_8;
    }
    if (param_8 < 1) {
      return param_8;
    }
    iVar12 = 0;
    if (param_3 == 0) {
      do {
        plVar16 = (long *)*param_6;
        *(uint *)(plVar16 + 0x33) = *(uint *)(plVar16 + 0x33) | 0x40;
        if ((*(byte *)((long)plVar16 + 0x1b5) >> 3 & 1) == 0) {
          iVar15 = *(int *)(param_1 + 0x3ef4);
          *(int *)(param_1 + 0x3ef4) = iVar15 + 1;
          *(long **)(*(long *)(param_1 + 0x1ac8) + (long)iVar15 * 8) = plVar16;
          *(ushort *)((long)plVar16 + 0x1b5) = *(ushort *)((long)plVar16 + 0x1b5) | 8;
          uVar3 = *(uint *)(plVar16 + 0x33);
          *(uint *)(plVar16 + 0x33) = uVar3 & 0xfffffeff;
          if ((uVar3 >> 9 & 1) != 0) {
            (**(code **)(*plVar16 + 0x270))(plVar16);
          }
        }
        piVar2 = (int *)((long)plVar16 + 0x1ac);
        do {
          cVar7 = '\x01';
          bVar1 = (bool)ExclusiveMonitorPass(piVar2,0x10);
          if (bVar1) {
            *piVar2 = *piVar2 + 1;
            cVar7 = ExclusiveMonitorsStatus();
          }
        } while (cVar7 != '\0');
        iVar12 = iVar12 + 1;
        *param_7 = plVar16;
        param_7 = param_7 + 1;
        param_6 = param_6 + 1;
      } while (iVar12 != param_8);
      return param_8;
    }
    lVar9 = (long)((ulong)(param_3 - 1U) << 0x20) >> 0x26;
    do {
      plVar16 = (long *)*param_6;
      plVar16[lVar9 + 0x3f] = plVar16[lVar9 + 0x3f] | 1L << ((long)(int)(param_3 - 1U) & 0x3fU);
      if ((*(byte *)((long)plVar16 + 0x1b5) >> 3 & 1) == 0) {
        iVar15 = *(int *)(param_1 + 0x3ef4);
        *(int *)(param_1 + 0x3ef4) = iVar15 + 1;
        *(long **)(*(long *)(param_1 + 0x1ac8) + (long)iVar15 * 8) = plVar16;
        *(ushort *)((long)plVar16 + 0x1b5) = *(ushort *)((long)plVar16 + 0x1b5) | 8;
        uVar3 = *(uint *)(plVar16 + 0x33);
        *(uint *)(plVar16 + 0x33) = uVar3 & 0xfffffeff;
        if ((uVar3 >> 9 & 1) != 0) {
          (**(code **)(*plVar16 + 0x270))(plVar16);
        }
      }
      piVar2 = (int *)((long)plVar16 + 0x1ac);
      do {
        cVar7 = '\x01';
        bVar1 = (bool)ExclusiveMonitorPass(piVar2,0x10);
        if (bVar1) {
          *piVar2 = *piVar2 + 1;
          cVar7 = ExclusiveMonitorsStatus();
        }
      } while (cVar7 != '\0');
      iVar12 = iVar12 + 1;
      *param_7 = plVar16;
      param_7 = param_7 + 1;
      param_6 = param_6 + 1;
    } while (iVar12 != param_8);
    return param_8;
  }
  lVar9 = *(long *)PTR__ZN4Aska6Global29m_pObjectManagerJobDispatcherE_02cb8e98;
  Aska::ObjectManagerJobDispatcher::SetViewFrustumCullingBasicParameter(Aska::Camera*, int, int, Aska::RenderableObject**, unsigned long*)(lVar9,param_2,param_3,param_4,param_6,*(undefined8 *)(param_1 + 0x1ba0));
  param_6[param_8] = (param_6 + param_8)[-1];
  iVar12 = *(int *)(lVar9 + 0xac);
  iStack_80 = 0;
  if (iVar12 != 0) {
    iStack_80 = param_8 / iVar12;
  }
  if (iStack_80 < 9) {
    iStack_80 = 8;
  }
  if (0xff < iStack_80) {
    iStack_80 = 0x100;
  }
  if (4 < iVar12) {
    iStack_80 = iStack_80 + iVar12 * 0x40 + -0x100;
  }
  if (param_8 < 1) {
    return 0;
  }
  lVar6 = (long)((ulong)(param_3 - 1U) << 0x20) >> 0x26;
  uVar13 = 0;
  iVar15 = 0;
  iVar12 = 0;
  do {
    iVar14 = iVar15;
    if (iVar15 < param_8) {
      iVar14 = iStack_80 + iVar15;
      if (param_8 <= iStack_80 + iVar15) {
        iVar14 = param_8;
      }
      uVar10 = Aska::ObjectManagerJobDispatcher::Dispatch_ViewFrustumCulling(int, int, int)(lVar9,2,iVar15,iVar14 + -1);
      if ((uVar10 & 1) == 0) {
        iVar14 = iVar15;
      }
    }
    iVar15 = iVar14;
    if ((int)uVar13 < iVar15) {
      uVar13 = (ulong)(int)uVar13;
      if (param_3 == 0) {
        iVar14 = 0;
        while (uVar10 = *(ulong *)(*(long *)(param_1 + 0x1ba0) + (long)((int)uVar13 >> 5) * 8) >>
                        ((uVar13 & 0x1f) << 1), (uVar10 & 3) != 0) {
          plVar16 = (long *)param_6[uVar13];
          uVar3 = (uint)uVar10 & 3;
          uVar4 = *(uint *)(plVar16 + 0x33);
          if (uVar3 == 2) {
            if ((uVar4 >> 0x19 & 1) != 0) {
              (**(code **)(*plVar16 + 0x1f0))(plVar16);
            }
            if ((uVar4 >> 0x15 & 1) != 0) {
              (**(code **)(*plVar16 + 0x298))(plVar16);
            }
          }
          else if (uVar3 == 1) {
            *(uint *)(plVar16 + 0x33) = uVar4 | 0x40;
            if ((*(byte *)((long)plVar16 + 0x1b5) >> 3 & 1) == 0) {
              iVar5 = *(int *)(param_1 + 0x3ef4);
              *(int *)(param_1 + 0x3ef4) = iVar5 + 1;
              *(long **)(*(long *)(param_1 + 0x1ac8) + (long)iVar5 * 8) = plVar16;
              *(ushort *)((long)plVar16 + 0x1b5) = *(ushort *)((long)plVar16 + 0x1b5) | 8;
              *(uint *)(plVar16 + 0x33) = *(uint *)(plVar16 + 0x33) & 0xfffffeff;
              if ((uVar4 >> 9 & 1) != 0) {
                (**(code **)(*plVar16 + 0x270))(plVar16);
              }
            }
            if ((param_5 & 1) != 0) {
              piVar2 = (int *)((long)plVar16 + 0x1ac);
              do {
                cVar7 = '\x01';
                bVar1 = (bool)ExclusiveMonitorPass(piVar2,0x10);
                if (bVar1) {
                  *piVar2 = *piVar2 + 1;
                  cVar7 = ExclusiveMonitorsStatus();
                }
              } while (cVar7 != '\0');
            }
            *param_7 = plVar16;
            iVar12 = iVar12 + 1;
            param_7 = param_7 + 1;
          }
          uVar13 = uVar13 + 1;
          if (((long)iVar15 <= (long)uVar13) || (bVar1 = 8 < iVar14, iVar14 = iVar14 + 1, bVar1))
          break;
        }
      }
      else {
        puVar11 = param_7;
        iVar14 = 0;
        while (uVar10 = *(ulong *)(*(long *)(param_1 + 0x1ba0) + (long)((int)uVar13 >> 5) * 8) >>
                        ((uVar13 & 0x1f) << 1), param_7 = puVar11, (uVar10 & 3) != 0) {
          plVar16 = (long *)param_6[uVar13];
          uVar3 = (uint)uVar10 & 3;
          uVar4 = *(uint *)(plVar16 + 0x33);
          if (uVar3 == 1) {
            plVar16[lVar6 + 0x3f] =
                 plVar16[lVar6 + 0x3f] | 1L << ((long)(int)(param_3 - 1U) & 0x3fU);
            if ((*(byte *)((long)plVar16 + 0x1b5) >> 3 & 1) == 0) {
              iVar5 = *(int *)(param_1 + 0x3ef4);
              *(int *)(param_1 + 0x3ef4) = iVar5 + 1;
              *(long **)(*(long *)(param_1 + 0x1ac8) + (long)iVar5 * 8) = plVar16;
              *(ushort *)((long)plVar16 + 0x1b5) = *(ushort *)((long)plVar16 + 0x1b5) | 8;
              *(uint *)(plVar16 + 0x33) = *(uint *)(plVar16 + 0x33) & 0xfffffeff;
              if ((uVar4 >> 9 & 1) != 0) {
                (**(code **)(*plVar16 + 0x270))(plVar16);
              }
            }
            if ((param_5 & 1) != 0) {
              piVar2 = (int *)((long)plVar16 + 0x1ac);
              do {
                cVar7 = '\x01';
                bVar1 = (bool)ExclusiveMonitorPass(piVar2,0x10);
                if (bVar1) {
                  *piVar2 = *piVar2 + 1;
                  cVar7 = ExclusiveMonitorsStatus();
                }
              } while (cVar7 != '\0');
            }
            param_7 = puVar11 + 1;
            *puVar11 = plVar16;
            iVar12 = iVar12 + 1;
          }
          else if ((uVar3 == 2) && ((uVar4 >> 0x19 & 1) != 0)) {
            (**(code **)(*plVar16 + 0x1f0))(plVar16);
          }
          uVar13 = uVar13 + 1;
          if (((long)iVar15 <= (long)uVar13) ||
             (bVar1 = 8 < iVar14, puVar11 = param_7, iVar14 = iVar14 + 1, bVar1)) break;
        }
      }
    }
    if (param_8 <= (int)uVar13) {
      return iVar12;
    }
  } while( true );
}

// ==== Aska::ObjectManager::Prerender_SortForPostProcessing(int, Aska::RenderableObject**, int, Aska::RenderableObject**, int*, Aska::RenderableObject**, int*)
// vaddr 0x21628a8 | ghidra 0x22628a8 | size 272 | symbol _ZN4Aska13ObjectManager31Prerender_SortForPostProcessingEiPPNS_16RenderableObjectEiS3_PiS3_S4_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13ObjectManager31Prerender_SortForPostProcessingEiPPNS_16RenderableObjectEiS3_PiS3_S4_
               (long param_1,int param_2,long *param_3,uint param_4,long param_5,int *param_6,
               long param_7,int *param_8)

{
  int *piVar1;
  byte bVar2;
  char cVar3;
  bool bVar4;
  int iVar5;
  int iVar6;
  long lVar7;
  ulong uVar8;
  long lVar9;
  
  lVar7 = *(long *)(param_1 + 0x4478);
  bVar2 = *(byte *)(lVar7 + 0x25);
  if (param_2 == 1) {
    if (0 < (int)param_4) {
      iVar6 = 0;
      iVar5 = 0;
      uVar8 = (ulong)param_4;
      while( true ) {
        lVar9 = *param_3;
        uVar8 = uVar8 - 1;
        if (*(byte *)(lVar7 + (ulong)*(byte *)(lVar9 + 0x1b7) + 0x10) < bVar2) {
          *(long *)(param_5 + (long)iVar6 * 8) = lVar9;
          iVar6 = iVar6 + 1;
        }
        else {
          *(ushort *)(lVar9 + 0x1b5) = *(ushort *)(lVar9 + 0x1b5) | 0x100;
          *(long *)(param_7 + (long)iVar5 * 8) = lVar9;
          iVar5 = iVar5 + 1;
        }
        if (uVar8 == 0) break;
        lVar7 = *(long *)(param_1 + 0x4478);
        param_3 = param_3 + 1;
      }
      goto code_r0x022629ac;
    }
  }
  else if (0 < (int)param_4) {
    uVar8 = 0;
    iVar6 = 0;
    iVar5 = 0;
    while( true ) {
      lVar9 = param_3[uVar8];
      if (*(byte *)(lVar7 + (ulong)*(byte *)(lVar9 + 0x1b7) + 0x10) < bVar2) {
        *(long *)(param_5 + (long)iVar6 * 8) = lVar9;
        iVar6 = iVar6 + 1;
      }
      else {
        piVar1 = (int *)(lVar9 + 0x1ac);
        do {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar4) {
            *piVar1 = *piVar1 + 1;
            cVar3 = ExclusiveMonitorsStatus();
          }
        } while (cVar3 != '\0');
        *(ushort *)(lVar9 + 0x1b5) = *(ushort *)(lVar9 + 0x1b5) | 0x100;
        *(long *)(param_7 + (long)iVar5 * 8) = lVar9;
        iVar5 = iVar5 + 1;
      }
      uVar8 = uVar8 + 1;
      if (uVar8 == param_4) break;
      lVar7 = *(long *)(param_1 + 0x4478);
    }
    goto code_r0x022629ac;
  }
  iVar5 = 0;
  iVar6 = 0;
code_r0x022629ac:
  *param_6 = iVar6;
  *param_8 = iVar5;
  return;
}

// ==== Aska::ObjectManager::Prerender_VersatileAndMotionBlur(Aska::RenderableObject**, int, Aska::Camera*)
// vaddr 0x21629b8 | ghidra 0x22629b8 | size 380 | symbol _ZN4Aska13ObjectManager32Prerender_VersatileAndMotionBlurEPPNS_16RenderableObjectEiPNS_6CameraE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13ObjectManager32Prerender_VersatileAndMotionBlurEPPNS_16RenderableObjectEiPNS_6CameraE
               (long param_1,long *param_2,uint param_3,long param_4)

{
  ushort *puVar1;
  uint uVar2;
  int iVar3;
  ulong uVar4;
  long *plVar5;
  
  iVar3 = *(int *)(param_1 + 0x3ef4);
  plVar5 = *(long **)(param_1 + 0x45e0);
  *(undefined4 *)(param_1 + 0x1b08) = 0;
  *(undefined4 *)(param_1 + 0x1af8) = 0;
  *(int *)(param_1 + 0x3ef4) = iVar3 + 1;
  *(long **)(*(long *)(param_1 + 0x1ac8) + (long)iVar3 * 8) = plVar5;
  puVar1 = (ushort *)((long)plVar5 + 0x1b5);
  *(uint *)(plVar5 + 0x33) = *(uint *)(plVar5 + 0x33) & 0xdfffffbf;
  *puVar1 = *puVar1 & 0xfefe;
  *(undefined4 *)((long)plVar5 + 0x1ac) = 0;
  plVar5[0x3a] = 0;
  *(undefined4 *)((long)plVar5 + 0x1cc) = 0;
  (**(code **)(*plVar5 + 0x198))(plVar5);
  plVar5[0x47] = 0;
  plVar5[0x46] = 0;
  plVar5[0x40] = 0;
  plVar5[0x3f] = 0;
  plVar5[0x3e] = 0;
  plVar5[0x3d] = 0;
  *puVar1 = *puVar1 & 0xfff1 | 8;
  *(uint *)(plVar5 + 0x33) = *(uint *)(plVar5 + 0x33) & 0xfffffedb | 0x24;
  iVar3 = *(int *)(param_1 + 0x1b08);
  *(int *)(param_1 + 0x1b08) = iVar3 + 1;
  *(undefined8 *)(*(long *)(param_1 + 0x1ae0) + (long)iVar3 * 8) = *(undefined8 *)(param_1 + 0x45e0)
  ;
  if (0 < (int)param_3) {
    uVar4 = (ulong)param_3;
    do {
      plVar5 = (long *)*param_2;
      uVar2 = *(uint *)(plVar5 + 0x33);
      if ((uVar2 >> 0x1b & 1) != 0) {
        iVar3 = *(int *)(param_1 + 0x1b08);
        if (iVar3 < 0x20) {
          *(int *)(param_1 + 0x1b08) = iVar3 + 1;
          *(long **)(*(long *)(param_1 + 0x1ae0) + (long)iVar3 * 8) = plVar5;
        }
      }
      if ((uVar2 >> 0x1a & 1) != 0) {
        iVar3 = *(int *)(param_1 + 0x1af8);
        if (iVar3 < 0x40) {
          *(int *)(param_1 + 0x1af8) = iVar3 + 1;
          *(long **)(*(long *)(param_1 + 0x1ae8) + (long)iVar3 * 8) = plVar5;
        }
      }
      if ((int)uVar2 < 0) {
        (**(code **)(*plVar5 + 0x168))();
      }
      uVar4 = uVar4 - 1;
      param_2 = param_2 + 1;
    } while (uVar4 != 0);
  }
  if (((*(byte *)(param_4 + 0xeb4) >> 4 & 1) == 0) ||
     ((*(byte *)(*(long *)(param_4 + 0xe18) + 0x2c0) >> 2 & 1) == 0)) {
    *(undefined4 *)(param_1 + 0x1af8) = 0;
  }
  return;
}

// ==== Aska::ObjectManager::Prerender_TileCandidates(Aska::RenderableObject**, int, Aska::Camera*, int, Aska::ObjectManagerJobDispatcher*)
// vaddr 0x2162b34 | ghidra 0x2262b34 | size 152 | symbol _ZN4Aska13ObjectManager24Prerender_TileCandidatesEPPNS_16RenderableObjectEiPNS_6CameraEiPNS_26ObjectManagerJobDispatcherE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13ObjectManager24Prerender_TileCandidatesEPPNS_16RenderableObjectEiPNS_6CameraEiPNS_26ObjectManagerJobDispatcherE
               (long param_1,undefined8 param_2,undefined4 param_3,undefined8 param_4,uint param_5)

{
  undefined4 uVar1;
  long lVar2;
  long lVar3;
  
  if ((int)param_5 < 2) {
    *(undefined4 *)(param_1 + 0x1bc8) = param_3;
  }
  else {
    lVar2 = 0x6f2;
    lVar3 = 0x1028;
    do {
      uVar1 = Aska::ObjectManager::MultithreadSubViewFrustumCulling(Aska::Camera*, int, int, Aska::RenderableObject**, Aska::RenderableObject**, int)(param_1,param_4,0,(int)lVar2 + -0x6f2,param_2,
                              *(undefined8 *)(param_1 + lVar3),param_3);
      *(undefined4 *)(param_1 + lVar2 * 4) = uVar1;
      lVar2 = lVar2 + 1;
      lVar3 = lVar3 + 0x10;
    } while (lVar2 - (ulong)param_5 != 0x6f2);
  }
  *(undefined8 *)(*(long *)(param_1 + 0xb418) + 0x478) = param_4;
  return;
}

// ==== Aska::ObjectManager::Prerender_MultiPass(Aska::TLongInt<unsigned long, 2>*, int, Aska::ObjectManagerJobDispatcher*)
// vaddr 0x2162bcc | ghidra 0x2262bcc | size 3756 | symbol _ZN4Aska13ObjectManager19Prerender_MultiPassEPNS_8TLongIntImLi2EEEiPNS_26ObjectManagerJobDispatcherE | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska13ObjectManager19Prerender_MultiPassEPNS_8TLongIntImLi2EEEiPNS_26ObjectManagerJobDispatcherE
               (long param_1,long param_2,undefined4 param_3)

{
  undefined *puVar1;
  undefined *puVar2;
  int *piVar3;
  int *piVar4;
  long lVar5;
  long lVar6;
  long lVar7;
  long lVar8;
  short *psVar9;
  long lVar10;
  ushort *puVar11;
  long *plVar12;
  ushort *puVar13;
  undefined4 uVar14;
  int iVar15;
  undefined8 uVar16;
  undefined8 uVar17;
  int iVar18;
  int iVar19;
  undefined4 uVar20;
  long *plVar21;
  long lVar22;
  ulong uVar23;
  long *plVar24;
  ulong uVar25;
  ushort uVar26;
  uint uVar27;
  long lVar28;
  long lVar29;
  undefined8 *puVar30;
  long lVar31;
  long lVar32;
  undefined8 uVar33;
  ushort uVar34;
  ulong uVar35;
  undefined8 uVar36;
  ulong uVar37;
  
  uVar17 = _UNK_029cc808;
  uVar16 = _UNK_029cc800;
  piVar3 = (int *)(param_1 + 0x106f8);
  piVar4 = (int *)(param_1 + 0x4598);
  lVar5 = param_1 + 0x10500;
  lVar6 = param_1 + 0x4490;
  lVar7 = param_1 + 0x44a8;
  lVar8 = param_1 + 0x4498;
  puVar1 = PTR__ZTVN4Aska24PostProcessBufferManagerE_02cc48d0 + 0x10;
  uVar35 = 0;
  psVar9 = (short *)(param_1 + 0x3ef0);
  puVar2 = PTR__ZTVN4Aska22PostProcessCombinerTBRE_02cbc048 + 0x10;
  lVar10 = param_1 + 0x104f8;
  *psVar9 = 0;
  do {
    lVar29 = param_1 + uVar35 * 4;
    lVar31 = param_1 + uVar35 * 0x48;
    *(undefined4 *)(lVar29 + 0x1c08) = 0;
    puVar11 = (ushort *)(lVar31 + 0x4632);
    uVar26 = *puVar11;
    uVar27 = (uint)uVar26;
    if ((uVar26 >> 2 & 1) == 0) goto code_r0x02263a4c;
    if ((uVar26 & 1) == 0) {
      if ((*(ulong *)(param_2 + ((long)uVar35 >> 6) * 8) & 1L << (uVar35 & 0x3f)) == 0) {
        if (((uVar26 >> 4 & 1) == 0) ||
           (lVar29 = param_1 + uVar35 * 0x48, iVar19 = *(int *)(lVar29 + 0x462c),
           *(int *)(lVar29 + 0x462c) = iVar19 + 1, iVar19 < 299)) goto code_r0x02263a4c;
        lVar29 = param_1 + uVar35 * 0x10;
        if (*(long *)(lVar29 + 0x10a0) != 0) {
          operator delete[](void*)();
          *(undefined8 *)(lVar29 + 0x10a0) = 0;
        }
        if (*(long *)(lVar29 + 0x10a8) != 0) {
          operator delete[](void*)();
          *(undefined8 *)(lVar29 + 0x10a8) = 0;
        }
        *puVar11 = *puVar11 & 0xffaf | 0x40;
        lVar29 = param_1 + uVar35 * 0x48;
        lVar31 = *(long *)(lVar29 + 0x4620);
        plVar12 = (long *)(lVar29 + 0x4620);
        if (lVar31 == 0) {
          plVar24 = (long *)(param_1 + uVar35 * 0x48 + 0x4618);
          plVar21 = (long *)*plVar24;
        }
        else {
          iVar19 = *piVar3;
          if (0 < iVar19) {
            lVar28 = 0;
            lVar29 = 0;
code_r0x02263894:
            if (*(long *)(lVar10 + lVar29 * 8) != lVar31) goto code_r0x022638a0;
            if ((int)lVar29 + 1 < iVar19) {
              do {
                lVar31 = lVar28 >> 0x1d;
                lVar28 = lVar28 + 0x100000000;
                *(undefined8 *)(param_1 + lVar31 + 0x104f8) = *(undefined8 *)(lVar5 + lVar29 * 8);
                iVar19 = *piVar3;
                lVar31 = lVar29 + 2;
                lVar29 = lVar29 + 1;
              } while (lVar31 < iVar19);
            }
            *piVar3 = iVar19 + -1;
            *(undefined8 *)(param_1 + (long)iVar19 * 8 + 0x104f8) = 0;
          }
code_r0x02262f58:
          lVar29 = param_1 + uVar35 * 0x48;
          plVar24 = (long *)(lVar29 + 0x4618);
          Aska::PostProcessCombinerTBR::DeleteSystemObjects(Aska::ObjectManager*)(*(undefined8 *)(lVar29 + 0x4618),param_1);
          if (*plVar12 == 0) {
code_r0x02263050:
            plVar21 = (long *)*plVar24;
          }
          else {
            lVar28 = 0;
            iVar19 = *piVar4;
            lVar31 = (long)iVar19;
            lVar29 = (lVar31 << 0x20) + 0x100000000;
            iVar18 = iVar19;
            do {
              iVar15 = iVar18;
              if (lVar31 + lVar28 < 1) goto code_r0x02263050;
              lVar22 = lVar28 * 8;
              lVar29 = lVar29 + -0x100000000;
              lVar28 = lVar28 + -1;
              iVar18 = iVar15 + -1;
            } while (*(long *)(lVar6 + (long)iVar19 * 8 + lVar22) != *plVar12);
            if (iVar19 + (int)lVar28 + 1 < iVar19) {
              lVar29 = lVar29 >> 0x20;
              uVar23 = lVar31 - lVar29;
              if ((uVar23 < 4) || (uVar25 = uVar23 & 0xfffffffffffffffc, uVar25 == 0)) {
code_r0x02263024:
                lVar31 = lVar31 - lVar29;
                puVar30 = (undefined8 *)(lVar8 + lVar29 * 8);
                do {
                  lVar31 = lVar31 + -1;
                  puVar30[-1] = *puVar30;
                  puVar30 = puVar30 + 1;
                } while (lVar31 != 0);
              }
              else {
                lVar29 = lVar29 + uVar25;
                uVar37 = lVar31 - iVar15 & 0xfffffffffffffffc;
                puVar30 = (undefined8 *)(lVar7 + (long)iVar15 * 8);
                do {
                  uVar33 = puVar30[-2];
                  uVar36 = *puVar30;
                  uVar37 = uVar37 - 4;
                  puVar30[-2] = puVar30[-1];
                  puVar30[-3] = uVar33;
                  *puVar30 = puVar30[1];
                  puVar30[-1] = uVar36;
                  puVar30 = puVar30 + 4;
                } while (uVar37 != 0);
                if (uVar23 != uVar25) goto code_r0x02263024;
              }
              iVar19 = *piVar4;
            }
            *piVar4 = iVar19 + -1;
            plVar21 = (long *)*plVar24;
          }
        }
        if (plVar21 != (long *)0x0) {
          (**(code **)(*plVar21 + 0x38))(plVar21,0);
          *plVar24 = 0;
        }
        plVar24 = (long *)*plVar12;
        if (plVar24 != (long *)0x0) {
          (**(code **)(*plVar24 + 0x38))(plVar24,0);
          *plVar12 = 0;
        }
        uVar26 = *puVar11;
        goto code_r0x02263a44;
      }
      *(undefined4 *)(param_1 + uVar35 * 0x48 + 0x462c) = 0;
      if ((uVar26 >> 3 & 1) == 0) {
        uVar27 = uVar26 & 0xffcf;
        *puVar11 = (ushort)uVar27;
      }
      if ((uVar27 >> 4 & 1) == 0) {
        lVar28 = param_1 + uVar35 * 0x10;
        if (*(long *)(lVar28 + 0x10a0) == 0) {
          lVar22 = operator new[](unsigned long, std::nothrow_t const&)(0x8000,PTR__ZSt7nothrow_02cb9a80);
          *(long *)(lVar28 + 0x10a0) = lVar22;
          if (lVar22 == 0) goto code_r0x02263a4c;
        }
        if (*(long *)(lVar28 + 0x10a8) == 0) {
          lVar22 = operator new[](unsigned long, std::nothrow_t const&)(0x8000,PTR__ZSt7nothrow_02cb9a80);
          *(long *)(lVar28 + 0x10a8) = lVar22;
          if (lVar22 == 0) goto code_r0x02263a4c;
        }
        iVar19 = (int)uVar35 + 1;
        uVar33 = *(undefined8 *)PTR__ZN4Aska6Global22m_pRenderTargetManagerE_02cbfa00;
        lVar28 = param_1 + uVar35 * 0x48;
        uVar23 = Aska::RenderTargetManagerGL::Create(unsigned int, int, int, unsigned int, Aska::APXFORMAT, Aska::APXFORMAT, unsigned long, unsigned long)(uVar33,iVar19,*(undefined2 *)(lVar31 + 0x45f0),
                                 *(undefined2 *)(lVar28 + 0x45f2),*(undefined2 *)(lVar28 + 0x45f6),
                                 *(undefined4 *)(lVar28 + 0x45f8),*(undefined4 *)(lVar28 + 0x45fc),0
                                 ,0);
        if ((uVar23 & 1) != 0) {
          if ((*(byte *)(lVar31 + 0x4633) >> 2 & 1) == 0) {
            uVar23 = Aska::RenderTargetManagerGL::CreateResolveTarget(unsigned int, int, int)(uVar33,iVar19,*(undefined4 *)(param_1 + uVar35 * 0x48 + 0x4628)
                                     ,1);
            if ((uVar23 & 1) == 0) goto code_r0x02263a4c;
            iVar19 = Aska::IPixelFormatGL::GetAppropriateResolveTextureFormat(Aska::APXFORMAT)(*(undefined4 *)(lVar28 + 0x45f8));
            if (iVar19 == 0xb80017) {
              *(undefined1 *)(param_1 + uVar35 * 0x48 + 0x4630) = 5;
            }
          }
          uVar27 = *puVar11 | 0x10;
          *puVar11 = (ushort)uVar27;
          goto code_r0x02263384;
        }
        goto code_r0x02263a4c;
      }
code_r0x02263384:
      lVar28 = *(long *)(param_1 + uVar35 * 0x48 + 0x4610);
      if ((uVar27 & 0xa0) == 0x80) {
        lVar22 = param_1 + uVar35 * 0x48;
        plVar12 = (long *)(lVar22 + 0x4620);
        if (*(long *)(lVar22 + 0x4620) == 0) {
          plVar24 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x4a0,PTR__ZSt7nothrow_02cb9a80);
          if (plVar24 == (long *)0x0) {
            *plVar12 = 0;
            goto code_r0x02263a4c;
          }
          Aska::RenderableObject::RenderableObject()(plVar24);
          *(undefined4 *)(plVar24 + 0x61) = 0;
          *(undefined1 *)((long)plVar24 + 0x43d) = 0;
          *(undefined2 *)(plVar24 + 0x88) = 0;
          *plVar24 = (long)puVar1;
          plVar24[0x84] = 0;
          plVar24[0x83] = 0;
          *(undefined8 *)((long)plVar24 + 0x444) = 0x3f800000;
          *(undefined1 *)((long)plVar24 + 0x1b7) = 0x15;
          plVar24[0x6f] = 0;
          plVar24[0x6e] = 0;
          plVar24[0x71] = 0;
          plVar24[0x70] = 0;
          plVar24[0x75] = 0;
          plVar24[0x74] = 0;
          plVar24[0x77] = 0;
          plVar24[0x76] = 0;
          plVar24[0x82] = 0;
          plVar24[0x7f] = 0;
          plVar24[0x7e] = 0;
          plVar24[0x81] = 0;
          plVar24[0x80] = 0;
          *(ushort *)((long)plVar24 + 0x24) = *(ushort *)((long)plVar24 + 0x24) | 2;
          *plVar12 = (long)plVar24;
          *(char *)((long)plVar24 + 0x43c) = (char)uVar35 + '\x01';
          iVar19 = *piVar3;
          if (iVar19 < 0x40) {
            *piVar3 = iVar19 + 1;
            *(long **)(param_1 + (long)iVar19 * 8 + 0x104f8) = plVar24;
            plVar24 = (long *)*plVar12;
          }
          *(long **)(param_1 + (long)*piVar4 * 8 + 0x4498) = plVar24;
          *piVar4 = *piVar4 + 1;
        }
        lVar32 = param_1 + uVar35 * 0x48;
        lVar22 = *(long *)(lVar32 + 0x4618);
        uVar23 = uVar35 + 1;
        plVar24 = (long *)(lVar32 + 0x4618);
        if (lVar22 == 0) {
          plVar21 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x1ee0,PTR__ZSt7nothrow_02cb9a80);
          if (plVar21 == (long *)0x0) {
            *plVar24 = 0;
          }
          else {
            Aska::RenderableObject::RenderableObject()(plVar21);
            *(undefined4 *)(plVar21 + 0x61) = 0;
            *plVar21 = (long)puVar2;
            plVar21[0x67] = 0;
            *(undefined4 *)(plVar21 + 0x68) = 0xffffffff;
            *(undefined1 *)((long)plVar21 + 0x344) = 0;
            *(byte *)((long)plVar21 + 0x345) = *(byte *)((long)plVar21 + 0x345) & 0xfc | 1;
            plVar21[0x66] = 0x408000003f400000;
            Aska::ToneMapTable::CalcLogEncodeCoef()(plVar21 + 0x62);
            plVar21[0x6a] = 0;
            *(undefined1 *)((long)plVar21 + 0x1ed5) = 0;
            *(byte *)((long)plVar21 + 0x1ed7) = *(byte *)((long)plVar21 + 0x1ed7) | 1;
            *(undefined1 *)((long)plVar21 + 0x1b7) = 0x18;
            *(uint *)(plVar21 + 0x33) = *(uint *)(plVar21 + 0x33) | 2;
            *(ushort *)((long)plVar21 + 0x24) = *(ushort *)((long)plVar21 + 0x24) | 2;
            Aska::ToneMapTable::CreateToneCurveTextures()(plVar21 + 0x62);
            *(undefined4 *)(plVar21 + 0x91) = 0x41700000;
            *(undefined4 *)((long)plVar21 + 0x464) = 0x3f800000;
            *(undefined1 *)((long)plVar21 + 0x1ed4) = 0;
            *(undefined8 *)((long)plVar21 + 0x494) = uVar17;
            *(undefined8 *)((long)plVar21 + 0x48c) = uVar16;
            plVar21[0x8e] = 0;
            plVar21[0x90] = 0;
            plVar21[0xb6] = 0;
            plVar21[0xb5] = 0;
            plVar21[0xb4] = 0;
            plVar21[0xb3] = 0;
            plVar21[0xb2] = 0;
            plVar21[0xb1] = 0;
            plVar21[0xb0] = 0;
            plVar21[0xaf] = 0;
            *(undefined2 *)(plVar21 + 0xb8) = 0;
            *(byte *)((long)plVar21 + 0x5fa) = *(byte *)((long)plVar21 + 0x5fa) & 0xfd;
            memset(plVar21 + 0xde,0,0x600);
            plVar21[0x1a5] = 0;
            plVar21[0x1a4] = 0;
            plVar21[0x1a9] = 0;
            plVar21[0x1a8] = 0;
            plVar21[0x1a7] = 0;
            plVar21[0x1a6] = 0;
            *(byte *)((long)plVar21 + 0x1ed7) = *(byte *)((long)plVar21 + 0x1ed7) & 0xfb;
            memset(plVar21 + 0x9e,0,0x78);
            *plVar24 = (long)plVar21;
            uVar25 = Aska::PostProcessCombinerTBR::Init(Aska::PostProcessBufferManager*)(plVar21,*plVar12);
            plVar21 = (long *)*plVar24;
            if ((uVar25 & 1) != 0) {
              plVar21[0x8a] = *(long *)(param_1 + 0x45d8);
              Aska::PostProcessCombinerTBR::SetMultipassNo(int)(*plVar24,uVar23 & 0xffffffff);
              lVar22 = *plVar24;
              if ((*(byte *)(lVar22 + 0x345) & 1) != 0) {
                *(byte *)(lVar22 + 0x345) = *(byte *)(lVar22 + 0x345) & 0xfc;
                lVar22 = *plVar24;
              }
              Aska::PostProcessCombinerTBR::AddSystemObjects(Aska::ObjectManager*)(lVar22,param_1);
              lVar22 = *plVar24;
              goto code_r0x022634a0;
            }
            if (plVar21 != (long *)0x0) {
              (**(code **)(*plVar21 + 0x38))(plVar21,0);
              *plVar24 = 0;
            }
          }
        }
        else {
code_r0x022634a0:
          *(long *)(lVar22 + 0x478) = lVar28;
          Aska::ToneMapTable::UpdateToneCurveTextures(Aska::Camera*)(*plVar24 + 0x310,*(undefined8 *)(*plVar24 + 0x478));
          uVar33 = *(undefined8 *)PTR__ZN4Aska6Global22m_pRenderTargetManagerE_02cbfa00;
          iVar19 = Aska::RenderDeviceGL::GetGLVersion() const(*(undefined8 *)PTR__ZN4Aska12g_pRenderDevE_02cbb1a0);
          lVar22 = param_1 + uVar35 * 0x48;
          uVar20 = 0x980093;
          if (iVar19 != 0) {
            uVar20 = 0xb88097;
          }
          uVar37 = 0;
          uVar25 = Aska::RenderTargetManagerGL::Create(unsigned int, int, int, unsigned int, Aska::APXFORMAT, Aska::APXFORMAT, unsigned long, unsigned long)(uVar33,(uint)uVar23 | 0x1000000,*(undefined2 *)(lVar31 + 0x45f0),
                                   *(undefined2 *)(lVar22 + 0x45f2),*(undefined2 *)(lVar22 + 0x45f6)
                                   ,uVar20,*(undefined4 *)(lVar22 + 0x45fc),0,0);
          if ((uVar25 & 1) != 0) {
            lVar32 = *plVar12;
            uVar14 = *(undefined4 *)(lVar22 + 0x45fc);
            lVar31 = Aska::RenderTargetManagerGL::GetRenderTarget(unsigned int)(uVar33,uVar23);
            uVar23 = Aska::PostProcessBufferManager::CreateBuffer(Aska::APXFORMAT, Aska::APXFORMAT, Aska::TilingInfo*, void*, unsigned int, unsigned int, void*, unsigned int, unsigned int)(lVar32,uVar20,uVar14,*(undefined8 *)(lVar31 + 8),0,0,0,0,
                                     uVar37 & 0xffffffff00000000,0);
            if ((uVar23 & 1) != 0) {
              uVar27 = *puVar11 | 0x20;
              *puVar11 = (ushort)uVar27;
              goto code_r0x02263594;
            }
            plVar24 = (long *)*plVar12;
            iVar19 = *piVar3;
            if (0 < iVar19) {
              lVar31 = 0;
              lVar29 = 0;
code_r0x02262eb0:
              if (*(long **)(lVar10 + lVar29 * 8) != plVar24) goto code_r0x02262ebc;
              if ((int)lVar29 + 1 < iVar19) {
                do {
                  lVar28 = lVar31 >> 0x1d;
                  lVar31 = lVar31 + 0x100000000;
                  *(undefined8 *)(param_1 + lVar28 + 0x104f8) = *(undefined8 *)(lVar5 + lVar29 * 8);
                  iVar19 = *piVar3;
                  lVar28 = lVar29 + 2;
                  lVar29 = lVar29 + 1;
                } while (lVar28 < iVar19);
              }
              *piVar3 = iVar19 + -1;
              *(undefined8 *)(param_1 + (long)iVar19 * 8 + 0x104f8) = 0;
              plVar24 = (long *)*plVar12;
            }
code_r0x022630ec:
            iVar19 = *piVar4;
            lVar28 = 0;
            lVar31 = (long)iVar19;
            lVar29 = (lVar31 << 0x20) + 0x100000000;
            iVar18 = iVar19;
            do {
              iVar15 = iVar18;
              if (lVar31 + lVar28 < 1) goto code_r0x022631bc;
              lVar22 = lVar28 * 8;
              lVar29 = lVar29 + -0x100000000;
              lVar28 = lVar28 + -1;
              iVar18 = iVar15 + -1;
            } while (*(long **)(lVar6 + (long)iVar19 * 8 + lVar22) != plVar24);
            if (iVar19 + (int)lVar28 + 1 < iVar19) {
              lVar29 = lVar29 >> 0x20;
              uVar23 = lVar31 - lVar29;
              if ((uVar23 < 4) || (uVar25 = uVar23 & 0xfffffffffffffffc, uVar25 == 0)) {
code_r0x0226318c:
                lVar31 = lVar31 - lVar29;
                puVar30 = (undefined8 *)(lVar8 + lVar29 * 8);
                do {
                  lVar31 = lVar31 + -1;
                  puVar30[-1] = *puVar30;
                  puVar30 = puVar30 + 1;
                } while (lVar31 != 0);
              }
              else {
                lVar29 = lVar29 + uVar25;
                uVar37 = lVar31 - iVar15 & 0xfffffffffffffffc;
                puVar30 = (undefined8 *)(lVar7 + (long)iVar15 * 8);
                do {
                  uVar33 = puVar30[-2];
                  uVar36 = *puVar30;
                  uVar37 = uVar37 - 4;
                  puVar30[-2] = puVar30[-1];
                  puVar30[-3] = uVar33;
                  *puVar30 = puVar30[1];
                  puVar30[-1] = uVar36;
                  puVar30 = puVar30 + 4;
                } while (uVar37 != 0);
                if (uVar23 != uVar25) goto code_r0x0226318c;
              }
              iVar19 = *piVar4;
            }
            *piVar4 = iVar19 + -1;
            plVar24 = (long *)*plVar12;
code_r0x022631bc:
            if (plVar24 != (long *)0x0) {
              (**(code **)(*plVar24 + 0x38))(plVar24,0);
              *plVar12 = 0;
            }
          }
        }
      }
      else {
code_r0x02263594:
        if ((uVar27 & 0xa0) != 0x80) {
          uVar23 = uVar35 + 1;
          uVar26 = *(ushort *)(param_1 + 0x4452);
          puVar13 = (ushort *)(param_1 + uVar23 * 2 + 0x4350);
          uVar34 = *puVar13;
          if ((uVar34 < uVar26) &&
             (lVar31 = operator new[](unsigned long, std::nothrow_t const&)((ulong)uVar26 << 3,PTR__ZSt7nothrow_02cb9a80), lVar31 != 0))
          {
            lVar22 = param_1 + uVar23 * 8;
            plVar12 = (long *)(lVar22 + 0x3f48);
            if (*(long *)(lVar22 + 0x3f48) != 0) {
              operator delete[](void*)();
              *plVar12 = 0;
            }
            *plVar12 = lVar31;
            *puVar13 = uVar26;
            uVar34 = uVar26;
          }
          if (((lVar28 != 0) && ((*(byte *)puVar11 >> 4 & 1) != 0)) &&
             (*(ushort *)(param_1 + 0x4452) <= uVar34)) {
            Aska::Camera::MakeCameraMatrix()(lVar28);
            if (*(char *)(lVar28 + 0x941) == '\0') {
              Aska::Camera::MakeViewFrustumPlane(int)(lVar28,0);
            }
            lVar31 = param_1 + uVar35 * 0x10;
            uVar20 = Aska::ObjectManager::MultithreadViewFrustumCulling(Aska::Camera*, int, int, Aska::RenderableObject**, Aska::RenderableObject**, int)(param_1,lVar28,uVar23 & 0xffffffff,0,
                                     *(undefined8 *)(param_1 + 0x1018),
                                     *(undefined8 *)(lVar31 + 0x10a0),param_3);
            uVar20 = Aska::ObjectManager::MultithreadOcclusionCulling(Aska::Camera*, int, int, bool, Aska::RenderableObject**, Aska::RenderableObject**, int)(param_1,lVar28,uVar23 & 0xffffffff,0,1,
                                     *(undefined8 *)(lVar31 + 0x10a0),
                                     *(undefined8 *)(lVar31 + 0x10a8),uVar20);
            *(undefined4 *)(lVar29 + 0x1c08) = uVar20;
            uVar26 = *puVar11;
            if ((uVar26 >> 7 & 1) != 0) {
              lVar31 = param_1 + uVar35 * 0x48;
              lVar29 = *(long *)(lVar31 + 0x4618);
              Aska::ToneMapTable::UpdateToneCurveTextures(Aska::Camera*)(lVar29 + 0x310,*(undefined8 *)(lVar29 + 0x478));
              Aska::PostProcessCombinerTBR::AddPostFiltersToPaintingListCandidates(Aska::ObjectManager*)(*(undefined8 *)(lVar31 + 0x4618),param_1);
              uVar26 = *puVar11;
            }
            if ((uVar26 >> 9 & 1) != 0) {
              lVar29 = param_1 + ((long)uVar23 >> 6) * 8;
              *(ulong *)(lVar29 + 0x4468) = *(ulong *)(lVar29 + 0x4468) | 1L << (uVar23 & 0x3f);
            }
            *psVar9 = *psVar9 + 1;
          }
        }
      }
    }
    else {
      *puVar11 = uVar26 & 0xffba | 0x40;
      lVar29 = param_1 + uVar35 * 0x10;
      if (*(long *)(lVar29 + 0x10a0) != 0) {
        operator delete[](void*)();
        *(undefined8 *)(lVar29 + 0x10a0) = 0;
      }
      if (*(long *)(lVar29 + 0x10a8) != 0) {
        operator delete[](void*)();
        *(undefined8 *)(lVar29 + 0x10a8) = 0;
      }
      *puVar11 = *puVar11 & 0xffef;
      lVar29 = param_1 + uVar35 * 0x48;
      lVar31 = *(long *)(lVar29 + 0x4620);
      plVar12 = (long *)(lVar29 + 0x4620);
      if (lVar31 != 0) {
        iVar19 = *piVar3;
        if (0 < iVar19) {
          lVar28 = 0;
          lVar29 = 0;
code_r0x022637c8:
          if (*(long *)(lVar10 + lVar29 * 8) != lVar31) break;
          if ((int)lVar29 + 1 < iVar19) {
            do {
              lVar31 = lVar28 >> 0x1d;
              lVar28 = lVar28 + 0x100000000;
              *(undefined8 *)(param_1 + lVar31 + 0x104f8) = *(undefined8 *)(lVar5 + lVar29 * 8);
              iVar19 = *piVar3;
              lVar31 = lVar29 + 2;
              lVar29 = lVar29 + 1;
            } while (lVar31 < iVar19);
          }
          *piVar3 = iVar19 + -1;
          *(undefined8 *)(param_1 + (long)iVar19 * 8 + 0x104f8) = 0;
          lVar31 = *plVar12;
        }
code_r0x022638fc:
        lVar22 = 0;
        iVar19 = *piVar4;
        lVar28 = (long)iVar19;
        lVar29 = (lVar28 << 0x20) + 0x100000000;
        iVar18 = iVar19;
        do {
          iVar15 = iVar18;
          if (lVar28 + lVar22 < 1) goto code_r0x022639e4;
          lVar32 = lVar22 * 8;
          lVar29 = lVar29 + -0x100000000;
          lVar22 = lVar22 + -1;
          iVar18 = iVar15 + -1;
        } while (*(long *)(lVar6 + (long)iVar19 * 8 + lVar32) != lVar31);
        if (iVar19 + (int)lVar22 + 1 < iVar19) {
          lVar29 = lVar29 >> 0x20;
          uVar23 = lVar28 - lVar29;
          if ((uVar23 < 4) || (uVar25 = uVar23 & 0xfffffffffffffffc, uVar25 == 0)) {
code_r0x022639b4:
            lVar28 = lVar28 - lVar29;
            puVar30 = (undefined8 *)(lVar8 + lVar29 * 8);
            do {
              lVar28 = lVar28 + -1;
              puVar30[-1] = *puVar30;
              puVar30 = puVar30 + 1;
            } while (lVar28 != 0);
          }
          else {
            lVar29 = lVar29 + uVar25;
            uVar37 = lVar28 - iVar15 & 0xfffffffffffffffc;
            puVar30 = (undefined8 *)(lVar7 + (long)iVar15 * 8);
            do {
              uVar33 = puVar30[-2];
              uVar36 = *puVar30;
              uVar37 = uVar37 - 4;
              puVar30[-2] = puVar30[-1];
              puVar30[-3] = uVar33;
              *puVar30 = puVar30[1];
              puVar30[-1] = uVar36;
              puVar30 = puVar30 + 4;
            } while (uVar37 != 0);
            if (uVar23 != uVar25) goto code_r0x022639b4;
          }
          iVar19 = *piVar4;
        }
        *piVar4 = iVar19 + -1;
      }
code_r0x022639e4:
      lVar31 = param_1 + uVar35 * 0x48;
      lVar29 = *(long *)(lVar31 + 0x4618);
      if (lVar29 != 0) {
        plVar24 = (long *)(lVar31 + 0x4618);
        Aska::PostProcessCombinerTBR::DeleteSystemObjects(Aska::ObjectManager*)(lVar29,param_1);
        plVar21 = (long *)*plVar24;
        if (plVar21 != (long *)0x0) {
          (**(code **)(*plVar21 + 0x38))(plVar21,0);
          *plVar24 = 0;
        }
      }
      plVar24 = (long *)*plVar12;
      if (plVar24 != (long *)0x0) {
        (**(code **)(*plVar24 + 0x38))(plVar24,0);
        *plVar12 = 0;
      }
      uVar26 = *puVar11;
code_r0x02263a44:
      *puVar11 = uVar26 & 0xffdf;
    }
code_r0x02263a4c:
    uVar35 = uVar35 + 1;
    if (uVar35 == 0x80) {
      return;
    }
  } while( true );
  lVar29 = lVar29 + 1;
  lVar28 = lVar28 + 0x100000000;
  if (iVar19 <= lVar29) goto code_r0x022638fc;
  goto code_r0x022637c8;
code_r0x022638a0:
  lVar29 = lVar29 + 1;
  lVar28 = lVar28 + 0x100000000;
  if (iVar19 <= lVar29) goto code_r0x02262f58;
  goto code_r0x02263894;
code_r0x02262ebc:
  lVar29 = lVar29 + 1;
  lVar31 = lVar31 + 0x100000000;
  if (iVar19 <= lVar29) goto code_r0x022630ec;
  goto code_r0x02262eb0;
}

// ==== Aska::ObjectManager::MakeDetectLIBLList(Aska::RenderableObject**, Aska::RenderableObject**, int)
// vaddr 0x2163a78 | ghidra 0x2263a78 | size 172 | symbol _ZN4Aska13ObjectManager18MakeDetectLIBLListEPPNS_16RenderableObjectES3_i | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZN4Aska13ObjectManager18MakeDetectLIBLListEPPNS_16RenderableObjectES3_i
                (undefined8 param_1,undefined8 *param_2,undefined8 *param_3,int param_4)

{
  undefined8 *puVar1;
  uint uVar2;
  ulong uVar3;
  long *plVar4;
  undefined8 *puVar5;
  
  puVar5 = param_2;
  if (0 < param_4) {
    puVar1 = param_3 + param_4;
    do {
      plVar4 = (long *)*param_3;
      if (((char)plVar4[0x49] == '\0') || (plVar4[0x4c] == 0)) {
code_r0x02263af4:
        plVar4[0x47] = 0;
        plVar4[0x46] = 0;
      }
      else {
        uVar2 = *(uint *)(plVar4 + 0x36);
        uVar3 = (**(code **)(*plVar4 + 0x268))(plVar4);
        if ((((uVar2 & 7) == 0) && ((uVar3 & 1) == 0)) &&
           (((uVar2 & 0x600) == 0 || ((*(byte *)(plVar4 + 0x32) & 0x1c) == 0))))
        goto code_r0x02263af4;
        *puVar5 = plVar4;
        puVar5 = puVar5 + 1;
      }
      param_3 = param_3 + 1;
    } while (param_3 < puVar1);
  }
  return (ulong)((long)puVar5 - (long)param_2) >> 3;
}

// ==== Aska::ObjectManager::MultithreadDetectLIBL(Aska::RenderableObject**, int)
// vaddr 0x2163b24 | ghidra 0x2263b24 | size 244 | symbol _ZN4Aska13ObjectManager21MultithreadDetectLIBLEPPNS_16RenderableObjectEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13ObjectManager21MultithreadDetectLIBLEPPNS_16RenderableObjectEi
               (undefined8 param_1,undefined8 param_2,uint param_3)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  ulong uVar6;
  uint uVar7;
  long lVar8;
  uint uVar9;
  int iVar10;
  
  lVar8 = *(long *)PTR__ZN4Aska6Global29m_pObjectManagerJobDispatcherE_02cb8e98;
  iVar1 = *(int *)(lVar8 + 0xac) + 1;
  uVar9 = 0;
  if (iVar1 != 0) {
    uVar9 = (int)param_3 / iVar1;
  }
  if ((int)uVar9 < 9) {
    uVar9 = 8;
  }
  uVar3 = uVar9;
  if (0xff < (int)uVar9) {
    uVar3 = 0x100;
  }
  Aska::ObjectManagerJobDispatcher::SetDetectLIBLBasicParameter(Aska::RenderableObject**)(lVar8);
  if (0 < (int)param_3) {
    uVar7 = 0xfffffeff;
    if (-0x101 < (int)~uVar9) {
      uVar7 = ~uVar9;
    }
    iVar10 = -1;
    iVar1 = uVar7 + 1;
    uVar9 = 0;
    do {
      uVar2 = uVar9 + uVar3;
      uVar4 = uVar7;
      if ((int)uVar7 <= (int)~param_3) {
        uVar4 = ~param_3;
      }
      uVar5 = uVar2;
      if ((int)param_3 <= (int)uVar2) {
        uVar5 = param_3;
      }
      uVar6 = Aska::ObjectManagerJobDispatcher::Dispatch_DetectLIBL(int, int)(lVar8,uVar9,uVar5 - 1);
      if ((uVar6 & 1) == 0) {
        Aska::LIBLManager::Intersect(Aska::RenderableObject**, int, int)(*(undefined8 *)PTR__ZN4Aska6Global14m_pLIBLManagerE_02cc46a8,param_2,uVar9,
                        iVar10 - uVar4);
      }
      iVar10 = iVar10 + iVar1;
      uVar7 = uVar7 + iVar1;
      uVar9 = uVar2;
    } while ((int)uVar2 < (int)param_3);
  }
  return;
}

// ==== Aska::ObjectManager::MultithreadSubViewFrustumCulling(Aska::Camera*, int, int, Aska::RenderableObject**, Aska::RenderableObject**, int)
// vaddr 0x2163c18 | ghidra 0x2263c18 | size 476 | symbol _ZN4Aska13ObjectManager32MultithreadSubViewFrustumCullingEPNS_6CameraEiiPPNS_16RenderableObjectES5_i | lib libSOA-3.7.0.so | 2026-10-04
int _ZN4Aska13ObjectManager32MultithreadSubViewFrustumCullingEPNS_6CameraEiiPPNS_16RenderableObjectES5_i
              (long param_1,undefined8 param_2,undefined4 param_3,undefined4 param_4,long param_5,
              undefined8 *param_6,int param_7)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  undefined1 auVar4 [16];
  long lVar5;
  int iVar6;
  ulong uVar7;
  ulong uVar8;
  undefined8 *puVar9;
  undefined8 uVar10;
  int iVar11;
  int iVar12;
  ulong uVar13;
  
  if (*(int *)(param_1 + 0x1ba8) < param_7) {
    *(int *)(param_1 + 0x1ba8) = param_7;
    if (*(long *)(param_1 + 0x1ba0) != 0) {
      operator delete[](void*)();
    }
    uVar3 = param_7 + 0x3e;
    if (-1 < (int)(param_7 + 0x1fU)) {
      uVar3 = param_7 + 0x1fU;
    }
    uVar13 = (long)((ulong)uVar3 << 0x20) >> 0x25;
    uVar7 = -(ulong)((uint)((int)uVar3 >> 5) >> 0x1f) & 0xfffffff800000000 |
            (ulong)(uint)((int)uVar3 >> 5) << 3;
    auVar4._8_8_ = 0;
    auVar4._0_8_ = uVar13;
    if (SUB168(auVar4 * ZEXT816(8),8) != 0) {
      uVar7 = 0xffffffffffffffff;
    }
    lVar5 = operator new[](unsigned long, std::nothrow_t const&)(uVar7,PTR__ZSt7nothrow_02cb9a80);
    *(long *)(param_1 + 0x1ba0) = lVar5;
    if (lVar5 == 0) {
      return 0;
    }
  }
  else {
    lVar5 = *(long *)(param_1 + 0x1ba0);
    uVar3 = param_7 + 0x3e;
    if (-1 < (int)(param_7 + 0x1fU)) {
      uVar3 = param_7 + 0x1fU;
    }
    uVar13 = (long)((ulong)uVar3 << 0x20) >> 0x25;
  }
  memset(lVar5,0,uVar13 << 3);
  uVar10 = *(undefined8 *)PTR__ZN4Aska6Global29m_pObjectManagerJobDispatcherE_02cb8e98;
  Aska::ObjectManagerJobDispatcher::SetViewFrustumCullingBasicParameter(Aska::Camera*, int, int, Aska::RenderableObject**, unsigned long*)(uVar10,param_2,param_3,param_4,param_5,*(long *)(param_1 + 0x1ba0));
  puVar9 = (undefined8 *)(param_5 + (long)param_7 * 8);
  *puVar9 = puVar9[-1];
  if (param_7 < 1) {
    return 0;
  }
  uVar13 = 0;
  iVar11 = 0;
  iVar12 = 0;
  do {
    iVar6 = iVar11;
    if (iVar11 < param_7) {
      iVar6 = iVar11 + 0x100;
      if (param_7 <= iVar11 + 0x100) {
        iVar6 = param_7;
      }
      uVar7 = Aska::ObjectManagerJobDispatcher::Dispatch_ViewFrustumCulling(int, int, int)(uVar10,1,iVar11,iVar6 + -1);
      if ((uVar7 & 1) == 0) {
        iVar6 = iVar11;
      }
    }
    iVar11 = iVar6;
    if ((int)uVar13 < iVar11) {
      iVar6 = 0;
      uVar7 = (uVar13 & 0xffffffff) << 1;
      uVar13 = (ulong)(int)uVar13;
      do {
        uVar8 = *(ulong *)(*(long *)(param_1 + 0x1ba0) + (long)((int)uVar13 >> 5) * 8) >>
                (uVar7 & 0x3e);
        if (((uint)uVar8 & 3) == 1) {
          iVar2 = iVar12 + 1;
          puVar9 = param_6 + 1;
          *param_6 = *(undefined8 *)(param_5 + uVar13 * 8);
          bVar1 = 0xffe < iVar12;
          param_6 = puVar9;
          iVar12 = iVar2;
          if (bVar1) break;
        }
        else {
          puVar9 = param_6;
          if ((uVar8 & 3) == 0) break;
        }
        uVar13 = uVar13 + 1;
        param_6 = puVar9;
        if (8 < iVar6) break;
        iVar6 = iVar6 + 1;
        uVar7 = uVar7 + 2;
      } while ((long)uVar13 < (long)iVar11);
    }
    if (param_7 <= (int)uVar13) {
      return iVar12;
    }
  } while( true );
}

// ==== Aska::ObjectManager::ViewFrustumCulling(Aska::Camera*, int, int, Aska::RenderableObject**, int, int, unsigned long*)
// vaddr 0x2163df4 | ghidra 0x2263df4 | size 7320 | symbol _ZN4Aska13ObjectManager18ViewFrustumCullingEPNS_6CameraEiiPPNS_16RenderableObjectEiiPm | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Removing unreachable block (ram,0x022647d0) */
/* WARNING: Removing unreachable block (ram,0x022646b4) */
/* WARNING: Type propagation algorithm not settling */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska13ObjectManager18ViewFrustumCullingEPNS_6CameraEiiPPNS_16RenderableObjectEiiPm
               (long param_1,long param_2,int param_3,int param_4,long param_5,ulong param_6,
               int param_7,long param_8)

{
  ulong *puVar1;
  long *plVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  ushort uVar6;
  char cVar7;
  float fVar8;
  undefined1 auVar9 [16];
  undefined1 auVar10 [16];
  undefined1 auVar11 [16];
  undefined1 auVar12 [16];
  undefined1 auVar13 [16];
  undefined1 auVar14 [16];
  undefined1 auVar15 [16];
  undefined1 auVar16 [16];
  undefined1 auVar17 [16];
  undefined1 auVar18 [16];
  undefined1 auVar19 [16];
  undefined1 auVar20 [16];
  undefined1 auVar21 [16];
  undefined1 auVar22 [16];
  undefined1 auVar23 [16];
  bool bVar24;
  float fVar25;
  float fVar26;
  float fVar27;
  float fVar28;
  float fVar29;
  float fVar30;
  float fVar31;
  float fVar32;
  float fVar33;
  float fVar34;
  float fVar35;
  float fVar36;
  float fVar37;
  undefined1 auVar38 [16];
  undefined1 auVar39 [12];
  undefined1 auVar40 [12];
  undefined1 auVar41 [16];
  undefined1 auVar42 [16];
  bool bVar43;
  float *pfVar44;
  long *plVar45;
  bool bVar46;
  long lVar47;
  undefined1 (*pauVar48) [16];
  long *plVar49;
  float *pfVar50;
  ulong uVar51;
  long lVar52;
  long lVar53;
  int iVar54;
  uint *puVar55;
  int iVar56;
  int iVar57;
  ulong uVar58;
  long *plVar59;
  long *plVar60;
  float fVar61;
  float fVar62;
  float fVar63;
  float fVar64;
  float fVar65;
  float fVar66;
  float fVar67;
  float fVar68;
  float extraout_s0;
  float fVar69;
  float fVar70;
  float fVar71;
  float fVar72;
  float fVar73;
  float fVar74;
  undefined1 auVar75 [16];
  undefined1 auVar76 [16];
  undefined1 auVar77 [16];
  undefined1 auVar78 [16];
  undefined1 auVar79 [16];
  undefined1 auVar80 [16];
  undefined1 auVar81 [16];
  undefined1 auVar82 [16];
  undefined1 auVar83 [16];
  undefined1 auVar84 [16];
  undefined1 auVar85 [16];
  undefined1 auVar86 [16];
  undefined1 auVar87 [16];
  undefined1 auVar88 [16];
  undefined1 auVar89 [16];
  undefined1 auVar90 [16];
  undefined1 auVar91 [16];
  undefined1 auVar92 [16];
  undefined1 auVar93 [16];
  undefined1 auVar94 [16];
  undefined1 auVar95 [16];
  undefined1 auVar96 [16];
  undefined1 auVar97 [16];
  undefined1 auVar98 [16];
  undefined1 auVar99 [16];
  undefined1 auVar100 [16];
  undefined1 auVar101 [16];
  undefined1 auVar102 [16];
  undefined1 auVar103 [16];
  undefined1 auVar104 [16];
  undefined1 auVar105 [16];
  undefined1 auVar106 [16];
  undefined1 auVar107 [16];
  undefined1 auVar108 [16];
  undefined1 auVar109 [16];
  undefined1 auVar110 [16];
  undefined8 uVar111;
  undefined1 auVar112 [16];
  undefined1 auVar113 [16];
  undefined1 auVar114 [16];
  undefined1 auVar115 [16];
  undefined8 uVar116;
  undefined1 auVar117 [16];
  undefined1 auVar118 [16];
  undefined1 auVar119 [16];
  undefined1 auVar120 [16];
  undefined1 auVar121 [16];
  undefined8 uVar122;
  undefined1 auVar123 [16];
  undefined1 auVar124 [16];
  undefined1 auVar125 [16];
  undefined1 auVar126 [16];
  undefined1 auVar127 [16];
  undefined1 auVar128 [16];
  undefined1 auVar129 [16];
  float fVar130;
  float fVar131;
  float fVar132;
  float fVar133;
  undefined1 auVar135 [16];
  undefined1 auVar136 [16];
  undefined1 auVar137 [16];
  undefined1 auVar138 [16];
  undefined1 auVar139 [16];
  undefined1 auVar140 [16];
  undefined1 auVar141 [16];
  float fVar142;
  undefined8 uVar143;
  undefined1 auVar144 [16];
  undefined1 auVar145 [16];
  undefined1 auVar146 [16];
  undefined1 auVar147 [16];
  undefined1 auVar148 [16];
  undefined1 auVar149 [16];
  undefined8 uVar150;
  undefined1 auVar152 [16];
  undefined1 auVar153 [16];
  undefined1 auVar154 [16];
  undefined1 auVar155 [16];
  undefined1 auVar156 [16];
  undefined1 auVar157 [16];
  undefined8 uVar151;
  undefined1 auVar158 [16];
  undefined1 auVar159 [16];
  undefined8 uVar160;
  undefined1 auVar161 [16];
  undefined1 auVar162 [16];
  undefined1 auVar163 [16];
  undefined1 auVar164 [16];
  undefined1 auVar165 [16];
  undefined8 uVar166;
  undefined1 auVar168 [16];
  undefined1 auVar169 [16];
  undefined1 auVar170 [16];
  undefined8 uVar167;
  undefined1 auVar171 [16];
  float fVar172;
  undefined8 uVar173;
  undefined1 auVar174 [16];
  undefined1 auVar175 [16];
  undefined1 auVar176 [16];
  undefined1 auVar177 [16];
  undefined1 auVar178 [16];
  undefined1 auVar179 [16];
  undefined8 uVar180;
  undefined8 uVar182;
  undefined8 uVar183;
  undefined8 uVar184;
  undefined8 uVar185;
  undefined8 uVar186;
  undefined1 auVar187 [16];
  undefined8 uVar181;
  undefined1 auVar188 [16];
  undefined1 auVar189 [16];
  undefined1 auVar190 [16];
  undefined8 uVar191;
  undefined1 auVar192 [16];
  undefined1 auVar193 [16];
  undefined1 auVar194 [16];
  float fVar195;
  undefined8 uVar196;
  float fVar205;
  undefined1 auVar199 [16];
  undefined1 auVar200 [16];
  undefined1 auVar201 [16];
  undefined1 auVar202 [16];
  undefined8 uVar197;
  undefined8 uVar198;
  float fVar204;
  undefined1 auVar203 [16];
  undefined8 uVar206;
  undefined1 auVar207 [16];
  undefined1 auVar208 [16];
  float fVar209;
  float fVar210;
  float fVar211;
  float fVar212;
  float fVar213;
  float fVar214;
  float fVar215;
  float fVar216;
  float fVar217;
  float fVar218;
  float fVar219;
  float fVar220;
  undefined1 auVar221 [16];
  undefined8 uStack_220;
  undefined8 uStack_218;
  undefined8 uStack_210;
  undefined8 uStack_208;
  undefined8 uStack_200;
  undefined8 uStack_1f8;
  undefined8 uStack_1f0;
  undefined8 uStack_1e8;
  float fStack_1c0;
  float fStack_1bc;
  float fStack_1b8;
  undefined8 uStack_1b0;
  undefined8 uStack_1a8;
  undefined8 uStack_1a0;
  undefined8 uStack_198;
  undefined8 uStack_190;
  undefined8 uStack_188;
  undefined8 uStack_180;
  undefined8 uStack_178;
  undefined8 uStack_170;
  undefined8 uStack_168;
  undefined8 uStack_160;
  undefined8 uStack_158;
  undefined8 uStack_150;
  undefined8 uStack_148;
  long lStack_128;
  undefined8 auStack_d0 [4];
  undefined1 auStack_b0 [16];
  undefined1 auVar134 [12];
  
  uVar58 = param_6 & 0xffffffff;
  if ((int)param_6 <= param_7) {
    fVar132 = *(float *)(param_1 + 0x3f24);
    fVar215 = (float)*(undefined8 *)(param_2 + 0x148);
    fVar216 = (float)((ulong)*(undefined8 *)(param_2 + 0x148) >> 0x20);
    fVar213 = (float)*(undefined8 *)(param_2 + 0x140);
    fVar214 = (float)((ulong)*(undefined8 *)(param_2 + 0x140) >> 0x20);
    fVar219 = (float)*(undefined8 *)(param_2 + 0x158);
    fVar220 = (float)((ulong)*(undefined8 *)(param_2 + 0x158) >> 0x20);
    fVar217 = (float)*(undefined8 *)(param_2 + 0x150);
    fVar218 = (float)((ulong)*(undefined8 *)(param_2 + 0x150) >> 0x20);
    fVar211 = (float)*(undefined8 *)(param_2 + 0x138);
    fVar212 = (float)((ulong)*(undefined8 *)(param_2 + 0x138) >> 0x20);
    fVar209 = (float)*(undefined8 *)(param_2 + 0x130);
    fVar210 = (float)((ulong)*(undefined8 *)(param_2 + 0x130) >> 0x20);
    lVar47 = param_2 + ((long)param_4 + 1) * 0x60;
    plVar2 = (long *)(param_1 + (long)param_3 * 8 + 0x3f48);
    uStack_218 = *(undefined8 *)(lVar47 + 0x5b8);
    uStack_220 = *(undefined8 *)(lVar47 + 0x5b0);
    uStack_208 = *(undefined8 *)(lVar47 + 0x5a8);
    uStack_210 = *(undefined8 *)(lVar47 + 0x5a0);
    uVar180 = *(undefined8 *)(lVar47 + 0x590);
    fStack_1b8 = (float)*(undefined8 *)(lVar47 + 0x598);
    fStack_1c0 = (float)uVar180;
    fStack_1bc = (float)((ulong)uVar180 >> 0x20);
    uStack_1a8 = *(undefined8 *)(lVar47 + 0x588);
    uStack_1b0 = *(undefined8 *)(lVar47 + 0x580);
    uStack_198 = *(undefined8 *)(lVar47 + 0x578);
    uStack_1a0 = *(undefined8 *)(lVar47 + 0x570);
    uStack_188 = *(undefined8 *)(lVar47 + 0x568);
    uStack_190 = *(undefined8 *)(lVar47 + 0x560);
    uStack_1f8 = *(undefined8 *)(lVar47 + 600);
    uStack_200 = *(undefined8 *)(lVar47 + 0x250);
    uStack_1e8 = *(undefined8 *)(lVar47 + 0x248);
    uStack_1f0 = *(undefined8 *)(lVar47 + 0x240);
    uStack_178 = *(undefined8 *)(lVar47 + 0x238);
    uStack_180 = *(undefined8 *)(lVar47 + 0x230);
    uStack_168 = *(undefined8 *)(lVar47 + 0x228);
    uStack_170 = *(undefined8 *)(lVar47 + 0x220);
    uStack_158 = *(undefined8 *)(lVar47 + 0x218);
    uStack_160 = *(undefined8 *)(lVar47 + 0x210);
    uStack_148 = *(undefined8 *)(lVar47 + 0x208);
    uStack_150 = *(undefined8 *)(lVar47 + 0x200);
    fVar8 = *(float *)(*(long *)PTR__ZN4Aska6Global16m_pObjectManagerE_02cc4688 + 0x45e8);
    fVar67 = 1.0;
    plVar59 = *(long **)(param_5 + (long)(int)param_6 * 8);
    lStack_128 = param_2;
    do {
      while( true ) {
        uVar51 = (ulong)(int)uVar58;
        if (param_3 == 0) {
          while( true ) {
            uVar58 = uVar51 + 1;
            plVar60 = *(long **)(param_5 + uVar58 * 8);
            iVar56 = (int)(uint)uVar51 >> 5;
            iVar57 = ((uint)uVar51 & 0x1f) << 1;
            Hint_Prefetch(plVar60,0,2,0);
            uVar4 = *(uint *)(plVar59 + 0x33);
            if ((uVar4 >> 3 & 1) == 0) break;
            puVar1 = (ulong *)(param_8 + (long)iVar56 * 8);
            do {
              cVar7 = '\x01';
              bVar43 = (bool)ExclusiveMonitorPass(puVar1,0x10);
              if (bVar43) {
                *puVar1 = *puVar1 | 3L << iVar57;
                cVar7 = ExclusiveMonitorsStatus();
              }
            } while (cVar7 != '\0');
            bVar43 = (long)param_7 <= (long)uVar51;
            uVar51 = uVar58;
            plVar59 = plVar60;
            if (bVar43) {
              return;
            }
          }
        }
        else {
          while( true ) {
            uVar58 = uVar51 + 1;
            plVar60 = *(long **)(param_5 + uVar58 * 8);
            iVar56 = (int)(uint)uVar51 >> 5;
            iVar57 = ((uint)uVar51 & 0x1f) << 1;
            Hint_Prefetch(plVar60,0,2,0);
            if ((plVar59[((long)((ulong)(param_3 - 1U) << 0x20) >> 0x26) + 0x41] &
                1L << ((long)(int)(param_3 - 1U) & 0x3fU)) != 0) break;
            puVar1 = (ulong *)(param_8 + (long)iVar56 * 8);
            do {
              cVar7 = '\x01';
              bVar43 = (bool)ExclusiveMonitorPass(puVar1,0x10);
              if (bVar43) {
                *puVar1 = *puVar1 | 3L << iVar57;
                cVar7 = ExclusiveMonitorsStatus();
              }
            } while (cVar7 != '\0');
            bVar43 = (long)param_7 <= (long)uVar51;
            uVar51 = uVar58;
            plVar59 = plVar60;
            if (bVar43) {
              return;
            }
          }
          uVar4 = *(uint *)(plVar59 + 0x33);
        }
        puVar55 = (uint *)(plVar59 + 0x33);
        uVar5 = *(uint *)(plVar59 + 0x36);
        if ((*(byte *)(plVar59 + 0x25) >> 4 & 1) == 0) {
          fVar67 = (float)(**(code **)(*plVar59 + 600))(fVar67,plVar59,0);
        }
        fVar70 = 1.0;
        if ((uVar4 >> 1 & 1) != 0) break;
        if (param_3 == 0) {
          if ((uVar4 >> 0x17 & 1) == 0) {
            bVar43 = lStack_128 != param_2;
            lStack_128 = param_2;
            if (bVar43) {
              uStack_148 = *(undefined8 *)(lVar47 + 0x208);
              uStack_150 = *(undefined8 *)(lVar47 + 0x200);
              uStack_158 = *(undefined8 *)(lVar47 + 0x218);
              uStack_160 = *(undefined8 *)(lVar47 + 0x210);
              uStack_168 = *(undefined8 *)(lVar47 + 0x228);
              uStack_170 = *(undefined8 *)(lVar47 + 0x220);
              uStack_178 = *(undefined8 *)(lVar47 + 0x238);
              uStack_180 = *(undefined8 *)(lVar47 + 0x230);
              uStack_1e8 = *(undefined8 *)(lVar47 + 0x248);
              uStack_1f0 = *(undefined8 *)(lVar47 + 0x240);
              uStack_1f8 = *(undefined8 *)(lVar47 + 600);
              uStack_200 = *(undefined8 *)(lVar47 + 0x250);
              uStack_188 = *(undefined8 *)(lVar47 + 0x568);
              uStack_190 = *(undefined8 *)(lVar47 + 0x560);
              uStack_198 = *(undefined8 *)(lVar47 + 0x578);
              uStack_1a0 = *(undefined8 *)(lVar47 + 0x570);
              uStack_1a8 = *(undefined8 *)(lVar47 + 0x588);
              uStack_1b0 = *(undefined8 *)(lVar47 + 0x580);
              uVar180 = *(undefined8 *)(lVar47 + 0x590);
              fStack_1b8 = (float)*(undefined8 *)(lVar47 + 0x598);
              fStack_1c0 = (float)uVar180;
              fStack_1bc = (float)((ulong)uVar180 >> 0x20);
              uStack_208 = *(undefined8 *)(lVar47 + 0x5a8);
              uStack_210 = *(undefined8 *)(lVar47 + 0x5a0);
              uStack_218 = *(undefined8 *)(lVar47 + 0x5b8);
              uStack_220 = *(undefined8 *)(lVar47 + 0x5b0);
              fVar67 = (float)uStack_220;
              fVar211 = (float)*(undefined8 *)(param_2 + 0x138);
              fVar212 = (float)((ulong)*(undefined8 *)(param_2 + 0x138) >> 0x20);
              fVar209 = (float)*(undefined8 *)(param_2 + 0x130);
              fVar210 = (float)((ulong)*(undefined8 *)(param_2 + 0x130) >> 0x20);
              fVar215 = (float)*(undefined8 *)(param_2 + 0x148);
              fVar216 = (float)((ulong)*(undefined8 *)(param_2 + 0x148) >> 0x20);
              fVar213 = (float)*(undefined8 *)(param_2 + 0x140);
              fVar214 = (float)((ulong)*(undefined8 *)(param_2 + 0x140) >> 0x20);
              fVar219 = (float)*(undefined8 *)(param_2 + 0x158);
              fVar220 = (float)((ulong)*(undefined8 *)(param_2 + 0x158) >> 0x20);
              fVar217 = (float)*(undefined8 *)(param_2 + 0x150);
              fVar218 = (float)((ulong)*(undefined8 *)(param_2 + 0x150) >> 0x20);
              lStack_128 = param_2;
            }
          }
          else {
            lVar53 = plVar59[0x34];
            if ((lVar53 != 0) && (lVar53 != lStack_128)) {
              fVar211 = (float)*(undefined8 *)(lVar53 + 0x138);
              fVar212 = (float)((ulong)*(undefined8 *)(lVar53 + 0x138) >> 0x20);
              fVar209 = (float)*(undefined8 *)(lVar53 + 0x130);
              fVar210 = (float)((ulong)*(undefined8 *)(lVar53 + 0x130) >> 0x20);
              fVar215 = (float)*(undefined8 *)(lVar53 + 0x148);
              fVar216 = (float)((ulong)*(undefined8 *)(lVar53 + 0x148) >> 0x20);
              fVar213 = (float)*(undefined8 *)(lVar53 + 0x140);
              fVar214 = (float)((ulong)*(undefined8 *)(lVar53 + 0x140) >> 0x20);
              lVar52 = lVar53 + ((long)param_4 + 1) * 0x60;
              uStack_148 = *(undefined8 *)(lVar52 + 0x208);
              uStack_150 = *(undefined8 *)(lVar52 + 0x200);
              uStack_158 = *(undefined8 *)(lVar52 + 0x218);
              uStack_160 = *(undefined8 *)(lVar52 + 0x210);
              uStack_168 = *(undefined8 *)(lVar52 + 0x228);
              uStack_170 = *(undefined8 *)(lVar52 + 0x220);
              uStack_178 = *(undefined8 *)(lVar52 + 0x238);
              uStack_180 = *(undefined8 *)(lVar52 + 0x230);
              uStack_1e8 = *(undefined8 *)(lVar52 + 0x248);
              uStack_1f0 = *(undefined8 *)(lVar52 + 0x240);
              uStack_1f8 = *(undefined8 *)(lVar52 + 600);
              uStack_200 = *(undefined8 *)(lVar52 + 0x250);
              uStack_188 = *(undefined8 *)(lVar52 + 0x568);
              uStack_190 = *(undefined8 *)(lVar52 + 0x560);
              uStack_198 = *(undefined8 *)(lVar52 + 0x578);
              uStack_1a0 = *(undefined8 *)(lVar52 + 0x570);
              uStack_1a8 = *(undefined8 *)(lVar52 + 0x588);
              uStack_1b0 = *(undefined8 *)(lVar52 + 0x580);
              fStack_1b8 = (float)*(undefined8 *)(lVar52 + 0x598);
              fStack_1c0 = (float)*(undefined8 *)(lVar52 + 0x590);
              fStack_1bc = (float)((ulong)*(undefined8 *)(lVar52 + 0x590) >> 0x20);
              uStack_208 = *(undefined8 *)(lVar52 + 0x5a8);
              uStack_210 = *(undefined8 *)(lVar52 + 0x5a0);
              uStack_218 = *(undefined8 *)(lVar52 + 0x5b8);
              uStack_220 = *(undefined8 *)(lVar52 + 0x5b0);
              fVar67 = (float)uStack_220;
              fVar219 = (float)*(undefined8 *)(lVar53 + 0x158);
              fVar220 = (float)((ulong)*(undefined8 *)(lVar53 + 0x158) >> 0x20);
              fVar217 = (float)*(undefined8 *)(lVar53 + 0x150);
              fVar218 = (float)((ulong)*(undefined8 *)(lVar53 + 0x150) >> 0x20);
              lStack_128 = lVar53;
            }
          }
        }
        bVar43 = false;
        auStack_b0._12_4_ = 0;
        auVar108 = auStack_b0;
        if ((uVar4 >> 10 & 1) == 0) {
          auStack_b0 = auVar108;
          bVar46 = bVar43;
          if (param_3 == 0) {
code_r0x02264028:
            bVar46 = bVar43;
            if ((uVar5 >> 0xe & 1) != 0) {
              fVar74 = *(float *)((long)plVar59 + 0x4c);
              fVar73 = *(float *)((long)plVar59 + 0x5c);
              pauVar48 = (undefined1 (*) [16])plVar59[0x24];
              uVar3 = *(uint *)((long)plVar59 + 0x2f4);
              fVar71 = *(float *)((long)plVar59 + 0x6c);
              bVar46 = (uVar3 & 1) != 0;
              uVar180 = _UNK_029cc810;
              uVar111 = _UNK_029cc818;
              if (!bVar46) {
                uVar180 = auStack_d0[0];
                uVar111 = auStack_d0[1];
              }
              auStack_d0[1] = uVar111;
              auStack_d0[0] = uVar180;
              uVar51 = (ulong)bVar46;
              if ((uVar3 >> 1 & 1) != 0) {
                auStack_d0[uVar51 * 2 + 1] = _UNK_029cc828;
                auStack_d0[uVar51 * 2] = _UNK_029cc820;
                uVar51 = (ulong)(bVar46 + 1);
              }
              if ((uVar3 >> 2 & 1) != 0) {
                iVar54 = (int)uVar51;
                auStack_d0[(long)iVar54 * 2 + 1] = _UNK_027f7c08;
                auStack_d0[(long)iVar54 * 2] = _UNK_027f7c00;
                uVar51 = (ulong)(iVar54 + 1);
              }
              fVar130 = *(float *)((long)plVar59 + 0x2fc);
              fVar131 = *(float *)(plVar59 + 0x5f) * 0.5;
              fVar68 = (float)cosf(fVar131);
              fVar67 = (float)cosf(fVar131 + fVar130);
              auVar18._8_4_ = fVar215;
              auVar18._0_8_ = CONCAT44(fVar214,fVar213);
              auVar17._8_4_ = fVar215;
              auVar17._0_8_ = CONCAT44(fVar214,fVar213);
              auVar16._8_4_ = fVar211;
              auVar16._0_8_ = CONCAT44(fVar210,fVar209);
              auVar15._8_4_ = fVar211;
              auVar15._0_8_ = CONCAT44(fVar210,fVar209);
              auVar21._8_4_ = fVar219;
              auVar21._0_8_ = CONCAT44(fVar218,fVar217);
              auVar20._8_4_ = fVar219;
              auVar20._0_8_ = CONCAT44(fVar218,fVar217);
              auVar75._0_4_ = fVar209 * fVar74;
              auVar75._4_4_ = fVar210 * fVar73;
              auVar75._8_4_ = fVar211 * fVar71;
              auVar75._12_4_ = fVar212 * 1.0;
              auVar86._0_4_ = fVar213 * fVar74;
              auVar86._4_4_ = fVar214 * fVar73;
              auVar86._8_4_ = fVar215 * fVar71;
              auVar86._12_4_ = fVar216 * 1.0;
              auVar109 = NEON_ext(auVar75,auVar75,8,1);
              auVar96._0_4_ = fVar217 * fVar74;
              auVar96._4_4_ = fVar218 * fVar73;
              auVar96._8_4_ = fVar219 * fVar71;
              auVar96._12_4_ = fVar220 * 1.0;
              auVar110 = NEON_ext(auVar86,auVar86,8,1);
              auVar108 = NEON_ext(auVar96,auVar96,8,1);
              fVar73 = auVar109._0_4_ + auVar75._0_4_ + auVar109._4_4_ + auVar75._4_4_;
              fVar64 = auVar110._0_4_ + auVar86._0_4_ + auVar110._4_4_ + auVar86._4_4_;
              auVar221._4_4_ = fVar64;
              auVar221._0_4_ = fVar73;
              fVar71 = auVar108._0_4_ + auVar96._0_4_ + auVar108._4_4_ + auVar96._4_4_;
              auVar221._12_4_ =
                   SUB164(ZEXT816(0x3f0000003f000000),0) + SUB164(ZEXT816(0x3f0000003f000000),4);
              auVar221._8_4_ = fVar71;
              fVar74 = 0.0;
              if ((int)uVar51 == 0) {
                if (fVar68 < 0.0) goto code_r0x02264794;
              }
              else {
                fVar74 = fVar71 * fVar71 + fVar73 * fVar73 + fVar64 * fVar64 + 0.0;
                auVar76._4_4_ = fVar74;
                auVar76._0_4_ = fVar74;
                auVar76._8_4_ = fVar74;
                auVar76._12_4_ = fVar74;
                auVar108 = *pauVar48;
                auVar109 = pauVar48[1];
                auVar110 = pauVar48[2];
                auVar161 = NEON_frsqrte(auVar76,4);
                fVar74 = auVar161._0_4_;
                auVar152._0_4_ = fVar74 * fVar74;
                fVar61 = auVar161._4_4_;
                auVar152._4_4_ = fVar61 * fVar61;
                fVar62 = auVar161._8_4_;
                auVar152._8_4_ = fVar62 * fVar62;
                auVar152._12_4_ = auVar161._12_4_ * auVar161._12_4_;
                auVar161 = NEON_frsqrts(auVar152,auVar76,4);
                auVar15._12_4_ = fVar212;
                auVar16._12_4_ = fVar212;
                auVar117 = NEON_ext(auVar15,auVar16,8,1);
                auVar17._12_4_ = fVar216;
                auVar18._12_4_ = fVar216;
                auVar123 = NEON_ext(auVar17,auVar18,8,1);
                auVar20._12_4_ = fVar220;
                auVar21._12_4_ = fVar220;
                auVar135 = NEON_ext(auVar20,auVar21,8,1);
                auVar144 = NEON_ext(auVar108,auVar108,8,1);
                auVar153 = NEON_ext(auVar109,auVar109,8,1);
                auVar162 = NEON_ext(auVar110,auVar110,8,1);
                fVar73 = fVar73 * fVar74 * auVar161._0_4_;
                fVar64 = fVar64 * fVar61 * auVar161._4_4_;
                fVar71 = fVar71 * fVar62 * auVar161._8_4_;
                if ((uVar5 >> 0xf & 1) == 0) {
                  fVar74 = 0.0;
                  pauVar48 = (undefined1 (*) [16])auStack_d0;
                  do {
                    auVar161 = *pauVar48;
                    uVar51 = uVar51 - 1;
                    auVar187 = NEON_ext(auVar161,auVar161,8,1);
                    fVar66 = auVar187._0_4_;
                    fVar62 = auVar161._0_4_;
                    fVar63 = auVar161._4_4_;
                    fVar61 = auVar108._0_4_ * fVar62 + auVar144._0_4_ * fVar66 +
                             auVar108._4_4_ * fVar63 + 0.0;
                    fVar65 = auVar109._0_4_ * fVar62 + auVar153._0_4_ * fVar66 +
                             auVar109._4_4_ * fVar63 + 0.0;
                    fVar62 = auVar110._0_4_ * fVar62 + auVar162._0_4_ * fVar66 +
                             auVar110._4_4_ * fVar63 + 0.0;
                    fVar63 = auVar117._0_4_ * fVar62 + fVar209 * fVar61 + fVar210 * fVar65 + 0.0;
                    fVar66 = auVar123._0_4_ * fVar62 + fVar213 * fVar61 + fVar214 * fVar65 + 0.0;
                    fVar61 = auVar135._0_4_ * fVar62 + fVar217 * fVar61 + fVar218 * fVar65 + 0.0;
                    fVar62 = fVar61 * fVar61 + fVar63 * fVar63 + fVar66 * fVar66 + 0.0;
                    auVar174._4_4_ = fVar62;
                    auVar174._0_4_ = fVar62;
                    auVar174._8_4_ = fVar62;
                    auVar174._12_4_ = fVar62;
                    auVar161 = NEON_frsqrte(auVar174,4);
                    fVar62 = auVar161._0_4_;
                    auVar199._0_4_ = fVar62 * fVar62;
                    fVar65 = auVar161._4_4_;
                    auVar199._4_4_ = fVar65 * fVar65;
                    fVar133 = auVar161._8_4_;
                    auVar199._8_4_ = fVar133 * fVar133;
                    auVar199._12_4_ = auVar161._12_4_ * auVar161._12_4_;
                    auVar161 = NEON_frsqrts(auVar199,auVar174,4);
                    auVar175._0_4_ = fVar73 * fVar63 * fVar62 * auVar161._0_4_;
                    auVar175._4_4_ = fVar64 * fVar66 * fVar65 * auVar161._4_4_;
                    auVar175._8_4_ = fVar71 * fVar61 * fVar133 * auVar161._8_4_;
                    auVar175._12_4_ = 0;
                    auVar161 = NEON_ext(auVar175,auVar175,8,1);
                    uVar180 = NEON_rev64(CONCAT44(auVar161._0_4_ + auVar161._4_4_,
                                                  auVar175._0_4_ + auVar175._4_4_),4);
                    fVar61 = auVar175._0_4_ + auVar175._4_4_ + (float)uVar180;
                    if (fVar74 <= fVar61) {
                      fVar74 = fVar61;
                    }
                    pauVar48 = pauVar48 + 1;
                  } while (uVar51 != 0);
                }
                else {
                  fVar74 = 0.0;
                  pauVar48 = (undefined1 (*) [16])auStack_d0;
                  do {
                    auVar161 = *pauVar48;
                    uVar51 = uVar51 - 1;
                    auVar187 = NEON_ext(auVar161,auVar161,8,1);
                    fVar66 = auVar187._0_4_;
                    fVar62 = auVar161._0_4_;
                    fVar63 = auVar161._4_4_;
                    fVar61 = auVar108._0_4_ * fVar62 + auVar144._0_4_ * fVar66 +
                             auVar108._4_4_ * fVar63 + 0.0;
                    fVar65 = auVar109._0_4_ * fVar62 + auVar153._0_4_ * fVar66 +
                             auVar109._4_4_ * fVar63 + 0.0;
                    fVar62 = auVar110._0_4_ * fVar62 + auVar162._0_4_ * fVar66 +
                             auVar110._4_4_ * fVar63 + 0.0;
                    fVar63 = auVar117._0_4_ * fVar62 + fVar209 * fVar61 + fVar210 * fVar65 + 0.0;
                    fVar66 = auVar123._0_4_ * fVar62 + fVar213 * fVar61 + fVar214 * fVar65 + 0.0;
                    fVar61 = auVar135._0_4_ * fVar62 + fVar217 * fVar61 + fVar218 * fVar65 + 0.0;
                    fVar62 = fVar61 * fVar61 + fVar63 * fVar63 + fVar66 * fVar66 + 0.0;
                    auVar176._4_4_ = fVar62;
                    auVar176._0_4_ = fVar62;
                    auVar176._8_4_ = fVar62;
                    auVar176._12_4_ = fVar62;
                    auVar161 = NEON_frsqrte(auVar176,4);
                    fVar62 = auVar161._0_4_;
                    auVar200._0_4_ = fVar62 * fVar62;
                    fVar65 = auVar161._4_4_;
                    auVar200._4_4_ = fVar65 * fVar65;
                    fVar133 = auVar161._8_4_;
                    auVar200._8_4_ = fVar133 * fVar133;
                    auVar200._12_4_ = auVar161._12_4_ * auVar161._12_4_;
                    auVar161 = NEON_frsqrts(auVar200,auVar176,4);
                    auVar177._0_4_ = fVar73 * fVar63 * fVar62 * auVar161._0_4_;
                    auVar177._4_4_ = fVar64 * fVar66 * fVar65 * auVar161._4_4_;
                    auVar177._8_4_ = fVar71 * fVar61 * fVar133 * auVar161._8_4_;
                    auVar177._12_4_ = 0;
                    auVar161 = NEON_ext(auVar177,auVar177,8,1);
                    uVar180 = NEON_rev64(CONCAT44(auVar161._0_4_ + auVar161._4_4_,
                                                  auVar177._0_4_ + auVar177._4_4_),4);
                    fVar61 = ABS(auVar177._0_4_ + auVar177._4_4_ + (float)uVar180);
                    if (fVar74 <= fVar61) {
                      fVar74 = fVar61;
                    }
                    pauVar48 = pauVar48 + 1;
                  } while (uVar51 != 0);
                }
                if (fVar68 < fVar74) {
code_r0x02264794:
                  puVar1 = (ulong *)(param_8 + (long)iVar56 * 8);
                  do {
                    cVar7 = '\x01';
                    bVar43 = (bool)ExclusiveMonitorPass(puVar1,0x10);
                    if (bVar43) {
                      *puVar1 = *puVar1 | 2L << iVar57;
                      cVar7 = ExclusiveMonitorsStatus();
                    }
                  } while (cVar7 != '\0');
                  goto joined_r0x02265a58;
                }
              }
              bVar46 = true;
              if ((fVar67 <= fVar74) && (fVar74 <= fVar68)) {
                fVar67 = (float)acosf(fVar74);
                fVar73 = (float)sinf(fVar67 - fVar131);
                fVar67 = (float)sinf(fVar130);
                fVar73 = fVar73 / fVar67;
                fVar67 = fVar70 * fVar73;
                fVar74 = fVar67;
                if (fVar73 <= 0.0) {
                  fVar74 = fVar70;
                }
                fVar70 = fVar74;
                bVar46 = (bool)(bVar43 | 0.0 < fVar73);
              }
              if ((uVar5 >> 0x12 & 1) != 0) {
                auStack_b0 = auVar221;
              }
            }
          }
        }
        else {
          plVar45 = plVar59;
          if ((((uVar4 >> 0xb & 1) != 0) && (plVar59[0x1e] != 0)) &&
             (plVar49 = *(long **)(plVar59[0x1e] + 0xe8), plVar49 != (long *)0x0)) {
            plVar45 = plVar49;
          }
          pauVar48 = (undefined1 (*) [16])plVar45[0x24];
          fVar71 = *(float *)((long)plVar45 + 0x4c);
          auVar109 = *pauVar48;
          auVar110 = pauVar48[1];
          auVar161 = pauVar48[2];
          fVar68 = *(float *)((long)plVar45 + 0x5c);
          auVar135 = NEON_ext(auVar109,auVar109,8,1);
          auVar144 = NEON_ext(auVar110,auVar110,8,1);
          auVar117 = NEON_ext(auVar161,auVar161,8,1);
          fVar67 = *(float *)((long)plVar45 + 0x6c);
          fVar73 = (float)_UNK_029cc848;
          fVar130 = (float)((ulong)_UNK_029cc848 >> 0x20);
          auVar162._4_4_ = fVar210;
          auVar162._0_4_ = fVar209;
          auVar162._8_4_ = fVar211;
          auVar162._12_4_ = fVar212;
          auVar187._4_4_ = fVar210;
          auVar187._0_4_ = fVar209;
          auVar187._8_4_ = fVar211;
          auVar187._12_4_ = fVar212;
          auVar123 = NEON_ext(auVar162,auVar187,8,1);
          auVar208._4_4_ = fVar214;
          auVar208._0_4_ = fVar213;
          auVar208._8_4_ = fVar215;
          auVar208._12_4_ = fVar216;
          auVar19._4_4_ = fVar214;
          auVar19._0_4_ = fVar213;
          auVar19._8_4_ = fVar215;
          auVar19._12_4_ = fVar216;
          auVar162 = NEON_ext(auVar208,auVar19,8,1);
          auVar22._4_4_ = fVar218;
          auVar22._0_4_ = fVar217;
          auVar22._8_4_ = fVar219;
          auVar22._12_4_ = fVar220;
          auVar23._4_4_ = fVar218;
          auVar23._0_4_ = fVar217;
          auVar23._8_4_ = fVar219;
          auVar23._12_4_ = fVar220;
          auVar187 = NEON_ext(auVar22,auVar23,8,1);
          fVar74 = auVar109._0_4_ * _UNK_027e51b0 + auVar135._0_4_ * fVar73 +
                   auVar109._4_4_ * _UNK_027e51b4 + fVar130 * 0.0;
          fVar64 = auVar110._0_4_ * _UNK_027e51b0 + auVar144._0_4_ * fVar73 +
                   auVar110._4_4_ * _UNK_027e51b4 + fVar130 * 0.0;
          fVar73 = auVar161._0_4_ * _UNK_027e51b0 + auVar117._0_4_ * fVar73 +
                   auVar161._4_4_ * _UNK_027e51b4 + fVar130 * 0.0;
          auVar103._0_4_ = fVar209 * fVar71;
          auVar103._4_4_ = fVar210 * fVar68;
          auVar103._8_4_ = fVar211 * fVar67;
          auVar103._12_4_ = fVar212 * 1.0;
          auVar112._0_4_ = fVar213 * fVar71;
          auVar112._4_4_ = fVar214 * fVar68;
          auVar112._8_4_ = fVar215 * fVar67;
          auVar112._12_4_ = fVar216 * 1.0;
          auVar109 = NEON_ext(auVar103,auVar103,8,1);
          fVar71 = fVar217 * fVar71;
          fVar68 = fVar218 * fVar68;
          auVar110 = NEON_ext(auVar112,auVar112,8,1);
          auVar144._4_4_ = fVar68;
          auVar144._0_4_ = fVar71;
          auVar144._8_4_ = fVar219 * fVar67;
          auVar144._12_4_ = fVar220 * 1.0;
          auVar153._4_4_ = fVar68;
          auVar153._0_4_ = fVar71;
          auVar153._8_4_ = fVar219 * fVar67;
          auVar153._12_4_ = fVar220 * 1.0;
          auVar161 = NEON_ext(auVar144,auVar153,8,1);
          fVar67 = auVar109._0_4_ + auVar103._0_4_ + auVar109._4_4_ + auVar103._4_4_;
          auStack_b0._4_4_ = auVar110._0_4_ + auVar112._0_4_ + auVar110._4_4_ + auVar112._4_4_;
          auStack_b0._8_4_ = auVar161._0_4_ + fVar71 + auVar161._4_4_ + fVar68;
          auStack_b0._12_4_ = 0x3f800000;
          fVar71 = auVar123._0_4_ * fVar73 + fVar209 * fVar74 + fVar210 * fVar64 + 0.0;
          fVar68 = auVar162._0_4_ * fVar73 + fVar213 * fVar74 + fVar214 * fVar64 + 0.0;
          fVar74 = auVar187._0_4_ * fVar73 + fVar217 * fVar74 + fVar218 * fVar64 + 0.0;
          fVar73 = (float)auStack_b0._8_4_ * (float)auStack_b0._8_4_ + fVar67 * fVar67 +
                   (float)auStack_b0._4_4_ * (float)auStack_b0._4_4_ + 0.0;
          fVar64 = fVar74 * fVar74 + fVar71 * fVar71 + fVar68 * fVar68 + 0.0;
          auVar87._4_4_ = fVar73;
          auVar87._0_4_ = fVar73;
          auVar87._8_4_ = fVar73;
          auVar87._12_4_ = fVar73;
          auVar77._4_4_ = fVar64;
          auVar77._0_4_ = fVar64;
          auVar77._8_4_ = fVar64;
          auVar77._12_4_ = fVar64;
          auVar109 = NEON_frsqrte(auVar87,4);
          auVar110 = NEON_frsqrte(auVar77,4);
          fVar73 = auVar109._0_4_;
          auVar118._0_4_ = fVar73 * fVar73;
          fVar64 = auVar109._4_4_;
          auVar118._4_4_ = fVar64 * fVar64;
          fVar130 = auVar109._8_4_;
          auVar118._8_4_ = fVar130 * fVar130;
          auVar118._12_4_ = auVar109._12_4_ * auVar109._12_4_;
          fVar131 = auVar110._0_4_;
          auVar124._0_4_ = fVar131 * fVar131;
          fVar61 = auVar110._4_4_;
          auVar124._4_4_ = fVar61 * fVar61;
          fVar62 = auVar110._8_4_;
          auVar124._8_4_ = fVar62 * fVar62;
          auVar124._12_4_ = auVar110._12_4_ * auVar110._12_4_;
          auVar110 = NEON_frsqrts(auVar118,auVar87,4);
          auVar109 = NEON_frsqrts(auVar124,auVar77,4);
          auVar78._0_4_ = fVar67 * fVar73 * auVar110._0_4_ * fVar71 * fVar131 * auVar109._0_4_;
          auVar78._4_4_ =
               (float)auStack_b0._4_4_ * fVar64 * auVar110._4_4_ * fVar68 * fVar61 * auVar109._4_4_;
          auVar78._8_4_ =
               (float)auStack_b0._8_4_ * fVar130 * auVar110._8_4_ * fVar74 * fVar62 * auVar109._8_4_
          ;
          auVar78._12_4_ = 0;
          auVar109 = NEON_ext(auVar78,auVar78,8,1);
          uVar180 = NEON_rev64(CONCAT44(auVar109._0_4_ + auVar109._4_4_,
                                        auVar78._0_4_ + auVar78._4_4_),4);
          fVar74 = auVar78._0_4_ + auVar78._4_4_ + (float)uVar180;
          if (0.0 < fVar74) {
            puVar1 = (ulong *)(param_8 + (long)iVar56 * 8);
            do {
              cVar7 = '\x01';
              bVar43 = (bool)ExclusiveMonitorPass(puVar1,0x10);
              if (bVar43) {
                *puVar1 = *puVar1 | 2L << iVar57;
                cVar7 = ExclusiveMonitorsStatus();
              }
              auStack_b0 = auVar108;
            } while (cVar7 != '\0');
            goto joined_r0x02265a58;
          }
          if (param_3 == 0) {
            if (((uVar5 >> 0x12 & 1) != 0) && (plVar45 == plVar59)) {
              auStack_b0._0_4_ = fVar67;
              auVar108 = auStack_b0;
            }
            auStack_b0 = auVar108;
            if ((uVar4 >> 0xc & 1) == 0) {
              bVar43 = false;
            }
            else {
              fVar67 = -fVar74;
              if (fVar132 <= fVar67) {
                bVar43 = true;
                fVar70 = 1.0;
              }
              else {
                fVar67 = (1.0 / fVar132) * fVar67;
                fVar74 = fVar67;
                if (1.0 < fVar67) {
                  fVar74 = fVar70;
                }
                fVar70 = fVar74;
                bVar43 = true;
              }
            }
            goto code_r0x02264028;
          }
          auStack_b0 = auVar108;
          bVar46 = false;
        }
        if ((uVar4 >> 0xf & 1) != 0) {
          plVar45 = plVar59;
          if (((uVar4 >> 0xb & 1) != 0) &&
             (((plVar59[0x1e] == 0 ||
               (plVar45 = *(long **)(plVar59[0x1e] + 0xe8), plVar45 == (long *)0x0)) ||
              (uVar51 = Aska::IAnimatable::IsThisIt(unsigned short) const(plVar45,0xf112), (uVar51 & 1) == 0)))) {
            plVar45 = plVar59;
          }
          fVar67 = *(float *)(plVar45 + 0x5c);
          auVar79._0_4_ = fVar217 * *(float *)((long)plVar45 + 0x4c);
          auVar79._4_4_ = fVar218 * *(float *)((long)plVar45 + 0x5c);
          auVar79._8_4_ = fVar219 * *(float *)((long)plVar45 + 0x6c);
          auVar79._12_4_ = fVar220 * 1.0;
          auVar108 = NEON_ext(auVar79,auVar79,8,1);
          uVar180 = NEON_rev64(CONCAT44(auVar108._0_4_ + auVar108._4_4_,
                                        auVar79._0_4_ + auVar79._4_4_),4);
          fVar74 = auVar79._0_4_ + auVar79._4_4_ + (float)uVar180;
          if (fVar67 < fVar74) {
            puVar1 = (ulong *)(param_8 + (long)iVar56 * 8);
            do {
              cVar7 = '\x01';
              bVar43 = (bool)ExclusiveMonitorPass(puVar1,0x10);
              if (bVar43) {
                *puVar1 = *puVar1 | 2L << iVar57;
                cVar7 = ExclusiveMonitorsStatus();
              }
            } while (cVar7 != '\0');
            goto joined_r0x02265a58;
          }
          if ((param_3 == 0) && ((uVar4 >> 0x10 & 1) != 0)) {
            fVar73 = *(float *)((long)plVar45 + 0x2e4);
            if (fVar73 < fVar74) {
              fVar67 = 1.0 - (fVar74 - fVar73) / (fVar67 - fVar73);
              fVar70 = fVar70 * fVar67;
            }
            bVar46 = true;
          }
        }
        if ((uVar5 >> 0x13 & 1) == 0) {
code_r0x02264920:
          if (((uVar5 & 0x40000) != 0 && param_3 == 0) &&
             (plVar45 = (long *)plVar59[0x60], plVar45 != (long *)0x0)) {
            if ((float)auStack_b0._12_4_ == 0.0) {
              fVar67 = *(float *)((long)plVar59 + 0x4c);
              fVar74 = *(float *)((long)plVar59 + 0x5c);
              fVar73 = *(float *)((long)plVar59 + 0x6c);
              auVar80._0_4_ = fVar209 * fVar67;
              auVar80._4_4_ = fVar210 * fVar74;
              auVar80._8_4_ = fVar211 * fVar73;
              auVar80._12_4_ = fVar212 * 1.0;
              auVar88._0_4_ = fVar213 * fVar67;
              auVar88._4_4_ = fVar214 * fVar74;
              auVar88._8_4_ = fVar215 * fVar73;
              auVar88._12_4_ = fVar216 * 1.0;
              auVar108 = NEON_ext(auVar80,auVar80,8,1);
              fVar67 = fVar217 * fVar67;
              fVar74 = fVar218 * fVar74;
              auVar109 = NEON_ext(auVar88,auVar88,8,1);
              auVar9._4_4_ = fVar74;
              auVar9._0_4_ = fVar67;
              auVar9._8_4_ = fVar219 * fVar73;
              auVar9._12_4_ = fVar220 * 1.0;
              auVar10._4_4_ = fVar74;
              auVar10._0_4_ = fVar67;
              auVar10._8_4_ = fVar219 * fVar73;
              auVar10._12_4_ = fVar220 * 1.0;
              auVar110 = NEON_ext(auVar9,auVar10,8,1);
              auStack_b0._4_4_ = auVar109._0_4_ + auVar88._0_4_ + auVar109._4_4_ + auVar88._4_4_;
              auStack_b0._0_4_ = auVar108._0_4_ + auVar80._0_4_ + auVar108._4_4_ + auVar80._4_4_;
              auStack_b0._12_4_ =
                   SUB164(ZEXT816(0x3f0000003f000000),0) + SUB164(ZEXT816(0x3f0000003f000000),4);
              auStack_b0._8_4_ = auVar110._0_4_ + fVar67 + auVar110._4_4_ + fVar74;
            }
            fVar67 = (float)(**(code **)(*plVar45 + 8))(fVar70,plVar45,auStack_b0,plVar59,0,0);
            fVar70 = fVar67;
            goto joined_r0x02264b58;
          }
          if (bVar46) goto joined_r0x02264b58;
        }
        else {
          plVar45 = plVar59;
          if (((uVar4 >> 0xb & 1) != 0) &&
             (((plVar59[0x1e] == 0 ||
               (plVar45 = *(long **)(plVar59[0x1e] + 0xe8), plVar45 == (long *)0x0)) ||
              (uVar51 = Aska::IAnimatable::IsThisIt(unsigned short) const(plVar45,0xf112), (uVar51 & 1) == 0)))) {
            plVar45 = plVar59;
          }
          fVar67 = *(float *)(plVar45 + 0x5d);
          auVar81._0_4_ = fVar217 * *(float *)((long)plVar45 + 0x4c);
          auVar81._4_4_ = fVar218 * *(float *)((long)plVar45 + 0x5c);
          auVar81._8_4_ = fVar219 * *(float *)((long)plVar45 + 0x6c);
          auVar81._12_4_ = fVar220 * 1.0;
          auVar108 = NEON_ext(auVar81,auVar81,8,1);
          uVar180 = NEON_rev64(CONCAT44(auVar108._0_4_ + auVar108._4_4_,
                                        auVar81._0_4_ + auVar81._4_4_),4);
          fVar74 = auVar81._0_4_ + auVar81._4_4_ + (float)uVar180;
          if (fVar74 < fVar67) {
            puVar1 = (ulong *)(param_8 + (long)iVar56 * 8);
            do {
              cVar7 = '\x01';
              bVar43 = (bool)ExclusiveMonitorPass(puVar1,0x10);
              if (bVar43) {
                *puVar1 = *puVar1 | 2L << iVar57;
                cVar7 = ExclusiveMonitorsStatus();
              }
            } while (cVar7 != '\0');
            goto joined_r0x02265a58;
          }
          if (param_3 == 0) {
            fVar73 = *(float *)((long)plVar45 + 0x2ec);
            if (fVar74 < fVar73) {
              fVar67 = 1.0 - (fVar73 - fVar74) / (fVar73 - fVar67);
              fVar70 = fVar70 * fVar67;
            }
            bVar46 = true;
            goto code_r0x02264920;
          }
          if (!bVar46) goto code_r0x02264bf0;
joined_r0x02264b58:
          if (fVar70 <= 0.0) {
            puVar1 = (ulong *)(param_8 + (long)iVar56 * 8);
            do {
              cVar7 = '\x01';
              bVar43 = (bool)ExclusiveMonitorPass(puVar1,0x10);
              if (bVar43) {
                *puVar1 = *puVar1 | 2L << iVar57;
                cVar7 = ExclusiveMonitorsStatus();
              }
            } while (cVar7 != '\0');
            goto joined_r0x02265a58;
          }
          (**(code **)(*plVar59 + 0x240))(fVar70,plVar59);
        }
code_r0x02264bf0:
        fVar71 = (float)plVar59[0x5b];
        fVar64 = (float)((ulong)plVar59[0x5b] >> 0x20);
        fVar67 = (float)plVar59[0x5a];
        fVar73 = (float)((ulong)plVar59[0x5a] >> 0x20);
        Hint_Prefetch(plVar60 + 0x33,0,2,0);
        auVar154._4_4_ = fVar64;
        auVar154._0_4_ = fVar64;
        auVar154._8_4_ = fVar64;
        auVar154._12_4_ = fVar64;
        auVar82._0_4_ = fVar209 * fVar67;
        auVar82._4_4_ = fVar210 * fVar73;
        auVar82._8_4_ = fVar211 * fVar71;
        auVar82._12_4_ = fVar212 * 1.0;
        auVar89._0_4_ = fVar213 * fVar67;
        auVar89._4_4_ = fVar214 * fVar73;
        auVar89._8_4_ = fVar215 * fVar71;
        auVar89._12_4_ = fVar216 * 1.0;
        auVar108 = NEON_ext(auVar82,auVar82,8,1);
        auVar97._0_4_ = fVar217 * fVar67;
        auVar97._4_4_ = fVar218 * fVar73;
        auVar97._8_4_ = fVar219 * fVar71;
        auVar97._12_4_ = fVar220 * 1.0;
        auVar109 = NEON_ext(auVar89,auVar89,8,1);
        auVar110 = NEON_ext(auVar97,auVar97,8,1);
        fVar74 = auVar109._0_4_ + auVar89._0_4_ + auVar109._4_4_ + auVar89._4_4_;
        uVar180 = CONCAT44(fVar74,auVar108._0_4_ + auVar82._0_4_ + auVar108._4_4_ + auVar82._4_4_);
        fVar70 = auVar110._0_4_ + auVar97._0_4_ + auVar110._4_4_ + auVar97._4_4_;
        auVar136._8_8_ = CONCAT44(0x3f800000,fVar70);
        auVar136._0_8_ = uVar180;
        auVar134 = auVar136._0_12_;
        auVar108 = NEON_frecpe(auVar136,4);
        auVar109 = NEON_frecps(auVar108,auVar136,4);
        fVar68 = auVar108._4_4_ * auVar109._4_4_;
        fVar130 = auVar108._8_4_ * auVar109._8_4_;
        auVar39._4_4_ = fVar130;
        auVar39._0_4_ = fVar68;
        auVar39._8_4_ = auVar108._12_4_ * auVar109._12_4_;
        auVar145._12_4_ = 0;
        auVar145._0_12_ = auVar39;
        auVar145 = auVar145 << 0x20;
        fVar74 = fVar74 - fVar64;
        auVar40._4_4_ = fVar70 - fVar64;
        auVar40._0_4_ = fVar74;
        auVar40._8_4_ = 1.0 - fVar64;
        auVar163._12_4_ = 0;
        auVar163._0_12_ = auVar40;
        auVar163 = auVar163 << 0x20;
        if (((param_3 == 0) && (0.0 < fVar70 - fVar64)) &&
           (fVar64 * fVar130 <= fVar8 &&
            (fVar64 * fVar130 <= fVar8 && (fVar64 * fVar130 <= fVar8 && fVar64 * fVar130 <= fVar8)))
           ) {
          *puVar55 = *puVar55 | 0x20000000;
        }
        auVar83._0_4_ = (float)uStack_190 * (fVar67 - (float)uStack_150);
        auVar83._4_4_ = uStack_190._4_4_ * (fVar73 - uStack_150._4_4_);
        auVar83._8_4_ = (float)uStack_188 * (fVar71 - (float)uStack_148);
        auVar90._0_4_ = (float)uStack_1a0 * (fVar67 - (float)uStack_160);
        auVar90._4_4_ = uStack_1a0._4_4_ * (fVar73 - uStack_160._4_4_);
        auVar90._8_4_ = (float)uStack_198 * (fVar71 - (float)uStack_158);
        auVar98._0_4_ = (float)uStack_1b0 * (fVar67 - (float)uStack_170);
        auVar98._4_4_ = uStack_1b0._4_4_ * (fVar73 - uStack_170._4_4_);
        auVar98._8_4_ = (float)uStack_1a8 * (fVar71 - (float)uStack_168);
        auVar83._12_4_ = 0;
        auVar90._12_4_ = 0;
        auVar98._12_4_ = 0;
        auVar104._0_4_ = fStack_1c0 * (fVar67 - (float)uStack_180);
        auVar104._4_4_ = fStack_1bc * (fVar73 - uStack_180._4_4_);
        auVar104._8_4_ = fStack_1b8 * (fVar71 - (float)uStack_178);
        auVar108 = NEON_ext(auVar83,auVar83,8,1);
        auVar109 = NEON_ext(auVar90,auVar90,8,1);
        auVar104._12_4_ = 0;
        auVar110 = NEON_ext(auVar98,auVar98,8,1);
        auVar161 = NEON_ext(auVar104,auVar104,8,1);
        uVar111 = NEON_rev64(CONCAT44(auVar108._0_4_ + auVar108._4_4_,auVar83._0_4_ + auVar83._4_4_)
                             ,4);
        fVar130 = auVar83._0_4_ + auVar83._4_4_ + (float)uVar111;
        uVar111 = NEON_rev64(CONCAT44(auVar109._0_4_ + auVar109._4_4_,auVar90._0_4_ + auVar90._4_4_)
                             ,4);
        fVar131 = auVar90._0_4_ + auVar90._4_4_ + (float)uVar111;
        uVar111 = NEON_rev64(CONCAT44(auVar110._0_4_ + auVar110._4_4_,auVar98._0_4_ + auVar98._4_4_)
                             ,4);
        fVar61 = auVar98._0_4_ + auVar98._4_4_ + (float)uVar111;
        uVar111 = NEON_rev64(CONCAT44(auVar161._0_4_ + auVar161._4_4_,
                                      auVar104._0_4_ + auVar104._4_4_),4);
        fVar62 = auVar104._0_4_ + auVar104._4_4_ + (float)uVar111;
        if (((fVar64 + fVar130 < 0.0 || fVar64 + fVar131 < 0.0) || fVar64 + fVar61 < 0.0) ||
            fVar64 + fVar62 < 0.0) {
code_r0x02264dac:
          bVar46 = false;
          bVar43 = true;
joined_r0x02264db4:
          bVar24 = bVar43;
          if ((uVar4 >> 0x1e & 1) == 0) goto code_r0x02264db8;
code_r0x022656cc:
          *(undefined4 *)(*plVar2 + (ulong)*(ushort *)(plVar59 + 0x37) * 8 + 4) =
               *(undefined4 *)((long)plVar59 + 0x1bc);
          bVar24 = bVar43;
        }
        else {
          auVar113._0_4_ = (float)uStack_210 * (fVar67 - (float)uStack_1f0);
          auVar113._4_4_ = uStack_210._4_4_ * (fVar73 - uStack_1f0._4_4_);
          auVar113._8_4_ = (float)uStack_208 * (fVar71 - (float)uStack_1e8);
          auVar113._12_4_ = 0;
          fVar67 = (float)uStack_220 * (fVar67 - (float)uStack_200);
          fVar73 = uStack_220._4_4_ * (fVar73 - uStack_200._4_4_);
          fVar71 = (float)uStack_218 * (fVar71 - (float)uStack_1f8);
          auVar108 = NEON_ext(auVar113,auVar113,8,1);
          auVar11._4_4_ = fVar73;
          auVar11._0_4_ = fVar67;
          auVar11._8_4_ = fVar71;
          auVar11._12_4_ = 0;
          auVar12._4_4_ = fVar73;
          auVar12._0_4_ = fVar67;
          auVar12._8_4_ = fVar71;
          auVar12._12_4_ = 0;
          auVar109 = NEON_ext(auVar11,auVar12,8,1);
          uVar111 = NEON_rev64(CONCAT44(auVar108._0_4_ + auVar108._4_4_,
                                        auVar113._0_4_ + auVar113._4_4_),4);
          fVar71 = auVar113._0_4_ + auVar113._4_4_ + (float)uVar111;
          uVar111 = NEON_rev64(CONCAT44(auVar109._0_4_ + auVar109._4_4_,fVar67 + fVar73),4);
          fVar67 = fVar67 + fVar73 + (float)uVar111;
          if (((fVar64 + fVar71 < 0.0 || fVar64 + fVar67 < 0.0) || fVar64 + fVar67 < 0.0) ||
              fVar64 + fVar67 < 0.0) goto code_r0x02264dac;
          if ((((fVar130 - fVar64 < 0.0 || fVar130 - fVar64 < 0.0) || fVar130 - fVar64 < 0.0) ||
               fVar131 - fVar64 < 0.0) ||
             (fVar73 = fVar67 - fVar64, bVar43 = fVar61 - fVar64 < 0.0,
             fVar67 = (float)-(uint)bVar43,
             fVar73 < 0.0 || (fVar71 - fVar64 < 0.0 || (fVar62 - fVar64 < 0.0 || bVar43)))) {
            uVar111 = auVar154._8_8_;
            pfVar44 = (float *)(**(code **)(*plVar59 + 0x150))(plVar59,0);
            if (pfVar44 == (float *)0x0) {
              bVar43 = false;
              fVar67 = extraout_s0;
            }
            else {
              pfVar50 = (float *)plVar59[0x24];
              auVar105._0_4_ = (float)uStack_190 * (float)uStack_150;
              auVar105._4_4_ = uStack_190._4_4_ * uStack_150._4_4_;
              auVar105._8_4_ = (float)uStack_188 * (float)uStack_148;
              auVar114._0_4_ = (float)uStack_1a0 * (float)uStack_160;
              auVar114._4_4_ = uStack_1a0._4_4_ * uStack_160._4_4_;
              auVar114._8_4_ = (float)uStack_198 * (float)uStack_158;
              auVar119._0_4_ = (float)uStack_1b0 * (float)uStack_170;
              auVar119._4_4_ = uStack_1b0._4_4_ * uStack_170._4_4_;
              auVar119._8_4_ = (float)uStack_1a8 * (float)uStack_168;
              auVar125._0_4_ = fStack_1c0 * (float)uStack_180;
              auVar125._4_4_ = fStack_1bc * uStack_180._4_4_;
              auVar125._8_4_ = fStack_1b8 * (float)uStack_178;
              auVar105._12_4_ = 0;
              auVar114._12_4_ = 0;
              auVar119._12_4_ = 0;
              auVar125._12_4_ = 0;
              auVar108 = NEON_ext(auVar105,auVar105,8,1);
              auVar109 = NEON_ext(auVar114,auVar114,8,1);
              auVar110 = NEON_ext(auVar119,auVar119,8,1);
              auVar161 = NEON_ext(auVar125,auVar125,8,1);
              fVar73 = *pfVar44;
              fVar71 = pfVar44[1];
              fVar130 = pfVar44[2];
              fVar131 = pfVar44[3];
              fVar72 = (float)*(undefined8 *)(pfVar44 + 6);
              fVar67 = (float)*(undefined8 *)(pfVar44 + 4);
              fVar69 = (float)((ulong)*(undefined8 *)(pfVar44 + 4) >> 0x20);
              fVar61 = *pfVar50;
              fVar62 = pfVar50[1];
              fVar63 = pfVar50[2];
              fVar65 = pfVar50[3];
              fVar66 = pfVar50[4];
              fVar133 = pfVar50[5];
              fVar142 = pfVar50[6];
              fVar172 = pfVar50[7];
              fVar26 = pfVar44[8];
              fVar27 = pfVar44[9];
              fVar28 = pfVar44[10];
              fVar29 = pfVar44[0xb];
              fVar195 = pfVar44[0xc];
              fVar204 = pfVar44[0xd];
              fVar205 = pfVar44[0xe];
              fVar25 = pfVar44[0xf];
              fVar30 = pfVar50[8];
              fVar31 = pfVar50[9];
              fVar32 = pfVar50[10];
              fVar33 = pfVar50[0xb];
              fVar34 = pfVar50[0xc];
              fVar35 = pfVar50[0xd];
              fVar36 = pfVar50[0xe];
              fVar37 = pfVar50[0xf];
              uVar116 = NEON_rev64(CONCAT44(auVar108._0_4_ + auVar108._4_4_,
                                            auVar105._0_4_ + auVar105._4_4_),4);
              uVar181 = NEON_rev64(CONCAT44(auVar109._0_4_ + auVar109._4_4_,
                                            auVar114._0_4_ + auVar114._4_4_),4);
              uVar191 = NEON_rev64(CONCAT44(auVar110._0_4_ + auVar110._4_4_,
                                            auVar119._0_4_ + auVar119._4_4_),4);
              uVar196 = NEON_rev64(CONCAT44(auVar161._0_4_ + auVar161._4_4_,
                                            auVar125._0_4_ + auVar125._4_4_),4);
              auVar137._0_4_ = fVar61 * fVar73;
              auVar137._4_4_ = fVar62 * fVar71;
              auVar137._8_4_ = fVar63 * fVar130;
              auVar137._12_4_ = fVar65 * fVar131;
              auVar146._0_4_ = fVar66 * fVar73;
              auVar146._4_4_ = fVar133 * fVar71;
              auVar146._8_4_ = fVar142 * fVar130;
              auVar146._12_4_ = fVar172 * fVar131;
              auVar188._0_4_ = fVar30 * fVar73;
              auVar188._4_4_ = fVar31 * fVar71;
              auVar188._8_4_ = fVar32 * fVar130;
              auVar188._12_4_ = fVar33 * fVar131;
              auVar99._0_4_ = fVar34 * fVar73;
              auVar99._4_4_ = fVar35 * fVar71;
              auVar99._8_4_ = fVar36 * fVar130;
              auVar99._12_4_ = fVar37 * fVar131;
              auVar192._0_4_ = fVar61 * fVar26;
              auVar192._4_4_ = fVar62 * fVar27;
              auVar192._8_4_ = fVar63 * fVar28;
              auVar192._12_4_ = fVar65 * fVar29;
              auVar201._0_4_ = fVar66 * fVar26;
              auVar201._4_4_ = fVar133 * fVar27;
              auVar201._8_4_ = fVar142 * fVar28;
              auVar201._12_4_ = fVar172 * fVar29;
              auVar207._0_4_ = fVar30 * fVar26;
              auVar207._4_4_ = fVar31 * fVar27;
              auVar207._8_4_ = fVar32 * fVar28;
              auVar207._12_4_ = fVar33 * fVar29;
              auVar91._0_4_ = fVar34 * fVar26;
              auVar91._4_4_ = fVar35 * fVar27;
              auVar91._8_4_ = fVar36 * fVar28;
              auVar91._12_4_ = fVar37 * fVar29;
              auVar155._0_4_ = fVar61 * fVar195;
              auVar155._4_4_ = fVar62 * fVar204;
              auVar155._8_4_ = fVar63 * fVar205;
              auVar155._12_4_ = fVar65 * fVar25;
              auVar164._0_4_ = fVar66 * fVar195;
              auVar164._4_4_ = fVar133 * fVar204;
              auVar164._8_4_ = fVar142 * fVar205;
              auVar164._12_4_ = fVar172 * fVar25;
              auVar168._0_4_ = fVar30 * fVar195;
              auVar168._4_4_ = fVar31 * fVar204;
              auVar168._8_4_ = fVar32 * fVar205;
              auVar168._12_4_ = fVar33 * fVar25;
              auVar84._0_4_ = fVar34 * fVar195;
              auVar84._4_4_ = fVar35 * fVar204;
              auVar84._8_4_ = fVar36 * fVar205;
              auVar84._12_4_ = fVar37 * fVar25;
              auVar108 = NEON_ext(auVar137,auVar137,8,1);
              auVar109 = NEON_ext(auVar146,auVar146,8,1);
              auVar110 = NEON_ext(auVar188,auVar188,8,1);
              auVar161 = NEON_ext(auVar99,auVar99,8,1);
              auVar117 = NEON_ext(auVar192,auVar192,8,1);
              auVar123 = NEON_ext(auVar201,auVar201,8,1);
              auVar135 = NEON_ext(auVar207,auVar207,8,1);
              auVar144 = NEON_ext(auVar91,auVar91,8,1);
              auVar153 = NEON_ext(auVar155,auVar155,8,1);
              auVar162 = NEON_ext(auVar164,auVar164,8,1);
              auVar187 = NEON_ext(auVar168,auVar168,8,1);
              auVar208 = NEON_ext(auVar84,auVar84,8,1);
              uVar206 = NEON_rev64(CONCAT44(auVar108._0_4_ + auVar108._4_4_,
                                            auVar137._0_4_ + auVar137._4_4_),4);
              fVar133 = auVar137._0_4_ + auVar137._4_4_ + (float)uVar206;
              uVar206 = NEON_rev64(CONCAT44(auVar109._0_4_ + auVar109._4_4_,
                                            auVar146._0_4_ + auVar146._4_4_),4);
              fVar142 = auVar146._0_4_ + auVar146._4_4_ + (float)uVar206;
              uVar206 = NEON_rev64(CONCAT44(auVar110._0_4_ + auVar110._4_4_,
                                            auVar188._0_4_ + auVar188._4_4_),4);
              fVar172 = auVar188._0_4_ + auVar188._4_4_ + (float)uVar206;
              NEON_rev64(CONCAT44(auVar161._0_4_ + auVar161._4_4_,auVar99._0_4_ + auVar99._4_4_),4);
              uVar206 = NEON_rev64(CONCAT44(auVar117._0_4_ + auVar117._4_4_,
                                            auVar192._0_4_ + auVar192._4_4_),4);
              fVar62 = auVar192._0_4_ + auVar192._4_4_ + (float)uVar206;
              uVar206 = NEON_rev64(CONCAT44(auVar123._0_4_ + auVar123._4_4_,
                                            auVar201._0_4_ + auVar201._4_4_),4);
              fVar63 = auVar201._0_4_ + auVar201._4_4_ + (float)uVar206;
              uVar206 = NEON_rev64(CONCAT44(auVar135._0_4_ + auVar135._4_4_,
                                            auVar207._0_4_ + auVar207._4_4_),4);
              fVar65 = auVar207._0_4_ + auVar207._4_4_ + (float)uVar206;
              uVar206 = NEON_rev64(CONCAT44(auVar144._0_4_ + auVar144._4_4_,
                                            auVar91._0_4_ + auVar91._4_4_),4);
              fVar73 = auVar91._0_4_ + auVar91._4_4_ + (float)uVar206;
              uVar206 = NEON_rev64(CONCAT44(auVar153._0_4_ + auVar153._4_4_,
                                            auVar155._0_4_ + auVar155._4_4_),4);
              fVar130 = auVar155._0_4_ + auVar155._4_4_ + (float)uVar206;
              uVar206 = NEON_rev64(CONCAT44(auVar162._0_4_ + auVar162._4_4_,
                                            auVar164._0_4_ + auVar164._4_4_),4);
              fVar131 = auVar164._0_4_ + auVar164._4_4_ + (float)uVar206;
              uVar206 = NEON_rev64(CONCAT44(auVar187._0_4_ + auVar187._4_4_,
                                            auVar168._0_4_ + auVar168._4_4_),4);
              fVar61 = auVar168._0_4_ + auVar168._4_4_ + (float)uVar206;
              uVar206 = NEON_rev64(CONCAT44(auVar208._0_4_ + auVar208._4_4_,
                                            auVar84._0_4_ + auVar84._4_4_),4);
              fVar71 = auVar84._0_4_ + auVar84._4_4_ + (float)uVar206;
              auVar92._0_4_ = fVar62 * fVar62;
              auVar92._4_4_ = fVar63 * fVar63;
              auVar92._8_4_ = fVar65 * fVar65;
              auVar92._12_4_ = fVar73 * fVar73;
              auVar169._0_4_ = (float)uStack_190 * fVar133;
              auVar169._4_4_ = uStack_190._4_4_ * fVar142;
              auVar169._8_4_ = (float)uStack_188 * fVar172;
              auVar100._0_4_ = fVar130 * fVar130;
              auVar100._4_4_ = fVar131 * fVar131;
              auVar100._8_4_ = fVar61 * fVar61;
              auVar100._12_4_ = fVar71 * fVar71;
              auVar193._0_4_ = (float)uStack_1a0 * fVar133;
              auVar193._4_4_ = uStack_1a0._4_4_ * fVar142;
              auVar193._8_4_ = (float)uStack_198 * fVar172;
              auVar117 = NEON_ext(auVar92,auVar92,8,1);
              auVar169._12_4_ = 0;
              auVar189._0_4_ = (float)uStack_1b0 * fVar133;
              auVar189._4_4_ = uStack_1b0._4_4_ * fVar142;
              auVar189._8_4_ = (float)uStack_1a8 * fVar172;
              auVar123 = NEON_ext(auVar100,auVar100,8,1);
              auVar193._12_4_ = 0;
              auVar108 = NEON_ext(auVar169,auVar169,8,1);
              auVar202._0_4_ = fStack_1c0 * fVar133;
              auVar202._4_4_ = fStack_1bc * fVar142;
              auVar202._8_4_ = fStack_1b8 * fVar172;
              auVar189._12_4_ = 0;
              auVar109 = NEON_ext(auVar193,auVar193,8,1);
              auVar202._12_4_ = 0;
              auVar110 = NEON_ext(auVar189,auVar189,8,1);
              auVar161 = NEON_ext(auVar202,auVar202,8,1);
              fVar73 = auVar117._0_4_ + auVar92._0_4_ + auVar117._4_4_ + auVar92._4_4_;
              auVar138._0_4_ = (fVar63 * fVar61 - fVar65 * fVar131) * _UNK_029c49f0;
              auVar138._4_4_ = (fVar62 * fVar61 - fVar65 * fVar130) * _UNK_029c49f4;
              auVar138._8_4_ = (fVar62 * fVar131 - fVar63 * fVar130) * _UNK_029c49f8;
              uVar150 = NEON_rev64(CONCAT44(auVar108._0_4_ + auVar108._4_4_,
                                            auVar169._0_4_ + auVar169._4_4_),4);
              fVar71 = auVar123._0_4_ + auVar100._0_4_ + auVar123._4_4_ + auVar100._4_4_;
              auVar93._4_4_ = fVar73;
              auVar93._0_4_ = fVar73;
              auVar93._8_4_ = fVar73;
              auVar93._12_4_ = fVar73;
              uVar197 = NEON_rev64(CONCAT44(auVar109._0_4_ + auVar109._4_4_,
                                            auVar193._0_4_ + auVar193._4_4_),4);
              uVar166 = NEON_rev64(CONCAT44(auVar110._0_4_ + auVar110._4_4_,
                                            auVar189._0_4_ + auVar189._4_4_),4);
              auVar101._4_4_ = fVar71;
              auVar101._0_4_ = fVar71;
              auVar101._8_4_ = fVar71;
              auVar101._12_4_ = fVar71;
              uVar198 = NEON_rev64(CONCAT44(auVar161._0_4_ + auVar161._4_4_,
                                            auVar202._0_4_ + auVar202._4_4_),4);
              auVar108 = NEON_frsqrte(auVar93,4);
              auVar109 = NEON_frsqrte(auVar101,4);
              fVar73 = auVar108._0_4_;
              auVar156._0_4_ = fVar73 * fVar73;
              fVar71 = auVar108._4_4_;
              auVar156._4_4_ = fVar71 * fVar71;
              fVar66 = auVar108._8_4_;
              auVar156._8_4_ = fVar66 * fVar66;
              auVar156._12_4_ = auVar108._12_4_ * auVar108._12_4_;
              fVar195 = auVar109._0_4_;
              auVar178._0_4_ = fVar195 * fVar195;
              fVar204 = auVar109._4_4_;
              auVar178._4_4_ = fVar204 * fVar204;
              fVar205 = auVar109._8_4_;
              auVar178._8_4_ = fVar205 * fVar205;
              auVar178._12_4_ = auVar109._12_4_ * auVar109._12_4_;
              auVar108 = NEON_frsqrts(auVar156,auVar93,4);
              auVar138._12_4_ = 0x3f800000;
              auVar109 = NEON_frsqrts(auVar178,auVar101,4);
              auVar135 = NEON_ext(auVar138,auVar138,8,1);
              fVar62 = fVar62 * fVar73 * auVar108._0_4_;
              fVar63 = fVar63 * fVar71 * auVar108._4_4_;
              fVar65 = fVar65 * fVar66 * auVar108._8_4_;
              fVar130 = fVar130 * fVar195 * auVar109._0_4_;
              fVar131 = fVar131 * fVar204 * auVar109._4_4_;
              fVar61 = fVar61 * fVar205 * auVar109._8_4_;
              auVar126._0_4_ = (float)uStack_190 * fVar62;
              auVar126._4_4_ = uStack_190._4_4_ * fVar63;
              auVar126._8_4_ = (float)uStack_188 * fVar65;
              auVar147._0_4_ = (float)uStack_190 * fVar130;
              auVar147._4_4_ = uStack_190._4_4_ * fVar131;
              auVar147._8_4_ = (float)uStack_188 * fVar61;
              auVar126._12_4_ = 0;
              auVar157._0_4_ = (float)uStack_1a0 * fVar62;
              auVar157._4_4_ = uStack_1a0._4_4_ * fVar63;
              auVar157._8_4_ = (float)uStack_198 * fVar65;
              auVar147._12_4_ = 0;
              auVar109 = NEON_ext(auVar126,auVar126,8,1);
              auVar165._0_4_ = (float)uStack_1a0 * fVar130;
              auVar165._4_4_ = uStack_1a0._4_4_ * fVar131;
              auVar165._8_4_ = (float)uStack_198 * fVar61;
              auVar157._12_4_ = 0;
              auVar110 = NEON_ext(auVar147,auVar147,8,1);
              auVar170._0_4_ = (float)uStack_1b0 * fVar62;
              auVar170._4_4_ = uStack_1b0._4_4_ * fVar63;
              auVar170._8_4_ = (float)uStack_1a8 * fVar65;
              auVar165._12_4_ = 0;
              auVar161 = NEON_ext(auVar157,auVar157,8,1);
              auVar179._0_4_ = (float)uStack_1b0 * fVar130;
              auVar179._4_4_ = uStack_1b0._4_4_ * fVar131;
              auVar179._8_4_ = (float)uStack_1a8 * fVar61;
              auVar170._12_4_ = 0;
              auVar117 = NEON_ext(auVar165,auVar165,8,1);
              auVar190._0_4_ = fStack_1c0 * fVar62;
              auVar190._4_4_ = fStack_1bc * fVar63;
              auVar190._8_4_ = fStack_1b8 * fVar65;
              auVar179._12_4_ = 0;
              auVar123 = NEON_ext(auVar170,auVar170,8,1);
              fVar73 = auVar138._0_4_ * auVar138._0_4_ + auVar135._0_4_ * auVar135._0_4_ +
                       auVar138._4_4_ * auVar138._4_4_ + 0.0;
              auVar194._0_4_ = fStack_1c0 * fVar130;
              auVar194._4_4_ = fStack_1bc * fVar131;
              auVar194._8_4_ = fStack_1b8 * fVar61;
              auVar190._12_4_ = 0;
              auVar135 = NEON_ext(auVar179,auVar179,8,1);
              auVar106._4_4_ = fVar73;
              auVar106._0_4_ = fVar73;
              auVar106._8_4_ = fVar73;
              auVar106._12_4_ = fVar73;
              auVar194._12_4_ = 0;
              auVar144 = NEON_ext(auVar190,auVar190,8,1);
              auVar108 = NEON_frsqrte(auVar106,4);
              auVar153 = NEON_ext(auVar194,auVar194,8,1);
              fVar73 = auVar108._0_4_;
              auVar203._0_4_ = fVar73 * fVar73;
              fVar71 = auVar108._4_4_;
              auVar203._4_4_ = fVar71 * fVar71;
              fVar66 = auVar108._8_4_;
              auVar203._8_4_ = fVar66 * fVar66;
              auVar203._12_4_ = auVar108._12_4_ * auVar108._12_4_;
              auVar108 = NEON_frsqrts(auVar203,auVar106,4);
              uVar206 = NEON_rev64(CONCAT44(auVar109._0_4_ + auVar109._4_4_,
                                            auVar126._0_4_ + auVar126._4_4_),4);
              uVar122 = NEON_rev64(CONCAT44(auVar110._0_4_ + auVar110._4_4_,
                                            auVar147._0_4_ + auVar147._4_4_),4);
              uVar143 = NEON_rev64(CONCAT44(auVar161._0_4_ + auVar161._4_4_,
                                            auVar157._0_4_ + auVar157._4_4_),4);
              uVar151 = NEON_rev64(CONCAT44(auVar117._0_4_ + auVar117._4_4_,
                                            auVar165._0_4_ + auVar165._4_4_),4);
              uVar160 = NEON_rev64(CONCAT44(auVar123._0_4_ + auVar123._4_4_,
                                            auVar170._0_4_ + auVar170._4_4_),4);
              uVar167 = NEON_rev64(CONCAT44(auVar135._0_4_ + auVar135._4_4_,
                                            auVar179._0_4_ + auVar179._4_4_),4);
              fVar73 = auVar138._0_4_ * fVar73 * auVar108._0_4_;
              fVar71 = auVar138._4_4_ * fVar71 * auVar108._4_4_;
              fVar66 = auVar138._8_4_ * fVar66 * auVar108._8_4_;
              uVar173 = NEON_rev64(CONCAT44(auVar144._0_4_ + auVar144._4_4_,
                                            auVar190._0_4_ + auVar190._4_4_),4);
              uVar182 = NEON_rev64(CONCAT44(auVar153._0_4_ + auVar153._4_4_,
                                            auVar194._0_4_ + auVar194._4_4_),4);
              auVar127._0_4_ = (float)uStack_190 * fVar73;
              auVar127._4_4_ = uStack_190._4_4_ * fVar71;
              auVar127._8_4_ = (float)uStack_188 * fVar66;
              auVar139._0_4_ = (float)uStack_1a0 * fVar73;
              auVar139._4_4_ = uStack_1a0._4_4_ * fVar71;
              auVar139._8_4_ = (float)uStack_198 * fVar66;
              auVar127._12_4_ = 0;
              auVar158._0_4_ = (float)uStack_1b0 * fVar73;
              auVar158._4_4_ = uStack_1b0._4_4_ * fVar71;
              auVar158._8_4_ = (float)uStack_1a8 * fVar66;
              auVar139._12_4_ = 0;
              auVar108 = NEON_ext(auVar127,auVar127,8,1);
              auVar171._0_4_ = fStack_1c0 * fVar73;
              auVar171._4_4_ = fStack_1bc * fVar71;
              auVar171._8_4_ = fStack_1b8 * fVar66;
              auVar158._12_4_ = 0;
              auVar109 = NEON_ext(auVar139,auVar139,8,1);
              auVar171._12_4_ = 0;
              auVar110 = NEON_ext(auVar158,auVar158,8,1);
              auVar161 = NEON_ext(auVar171,auVar171,8,1);
              uVar183 = NEON_rev64(CONCAT44(auVar108._0_4_ + auVar108._4_4_,
                                            auVar127._0_4_ + auVar127._4_4_),4);
              uVar184 = NEON_rev64(CONCAT44(auVar109._0_4_ + auVar109._4_4_,
                                            auVar139._0_4_ + auVar139._4_4_),4);
              uVar185 = NEON_rev64(CONCAT44(auVar110._0_4_ + auVar110._4_4_,
                                            auVar158._0_4_ + auVar158._4_4_),4);
              uVar186 = NEON_rev64(CONCAT44(auVar161._0_4_ + auVar161._4_4_,
                                            auVar171._0_4_ + auVar171._4_4_),4);
              auVar128._0_4_ = fVar67 * ABS(auVar157._0_4_ + auVar157._4_4_ + (float)uVar143);
              auVar128._4_4_ = fVar69 * ABS(auVar165._0_4_ + auVar165._4_4_ + (float)uVar151);
              auVar128._8_4_ = fVar72 * ABS(auVar139._0_4_ + auVar139._4_4_ + (float)uVar184);
              auVar120._0_4_ = fVar67 * ABS(auVar126._0_4_ + auVar126._4_4_ + (float)uVar206);
              auVar120._4_4_ = fVar69 * ABS(auVar147._0_4_ + auVar147._4_4_ + (float)uVar122);
              auVar120._8_4_ = fVar72 * ABS(auVar127._0_4_ + auVar127._4_4_ + (float)uVar183);
              auVar128._12_4_ = 0;
              auVar140._0_4_ = fVar67 * ABS(auVar170._0_4_ + auVar170._4_4_ + (float)uVar160);
              auVar140._4_4_ = fVar69 * ABS(auVar179._0_4_ + auVar179._4_4_ + (float)uVar167);
              auVar140._8_4_ = fVar72 * ABS(auVar158._0_4_ + auVar158._4_4_ + (float)uVar185);
              auVar148._0_4_ = fVar67 * ABS(auVar190._0_4_ + auVar190._4_4_ + (float)uVar173);
              auVar148._4_4_ = fVar69 * ABS(auVar194._0_4_ + auVar194._4_4_ + (float)uVar182);
              auVar148._8_4_ = fVar72 * ABS(auVar171._0_4_ + auVar171._4_4_ + (float)uVar186);
              auVar120._12_4_ = 0;
              auVar109 = NEON_ext(auVar128,auVar128,8,1);
              auVar140._12_4_ = 0;
              auVar148._12_4_ = 0;
              auVar108 = NEON_ext(auVar120,auVar120,8,1);
              auVar110 = NEON_ext(auVar140,auVar140,8,1);
              auVar161 = NEON_ext(auVar148,auVar148,8,1);
              uVar122 = NEON_rev64(CONCAT44(auVar109._0_4_ + auVar109._4_4_,
                                            auVar128._0_4_ + auVar128._4_4_),4);
              uVar206 = NEON_rev64(CONCAT44(auVar108._0_4_ + auVar108._4_4_,
                                            auVar120._0_4_ + auVar120._4_4_),4);
              uVar143 = NEON_rev64(CONCAT44(auVar110._0_4_ + auVar110._4_4_,
                                            auVar140._0_4_ + auVar140._4_4_),4);
              uVar151 = NEON_rev64(CONCAT44(auVar161._0_4_ + auVar161._4_4_,
                                            auVar148._0_4_ + auVar148._4_4_),4);
              if (((0.0 <= auVar120._0_4_ + auVar120._4_4_ + (float)uVar206 +
                           ((auVar169._0_4_ + auVar169._4_4_ + (float)uVar150) -
                           (auVar105._0_4_ + auVar105._4_4_ + (float)uVar116)) &&
                   0.0 <= auVar128._0_4_ + auVar128._4_4_ + (float)uVar122 +
                          ((auVar193._0_4_ + auVar193._4_4_ + (float)uVar197) -
                          (auVar114._0_4_ + auVar114._4_4_ + (float)uVar181))) &&
                  0.0 <= auVar140._0_4_ + auVar140._4_4_ + (float)uVar143 +
                         ((auVar189._0_4_ + auVar189._4_4_ + (float)uVar166) -
                         (auVar119._0_4_ + auVar119._4_4_ + (float)uVar191))) &&
                  0.0 <= auVar148._0_4_ + auVar148._4_4_ + (float)uVar151 +
                         ((auVar202._0_4_ + auVar202._4_4_ + (float)uVar198) -
                         (auVar125._0_4_ + auVar125._4_4_ + (float)uVar196))) {
                auVar115._0_4_ = (float)uStack_210 * fVar62;
                auVar115._4_4_ = uStack_210._4_4_ * fVar63;
                auVar115._8_4_ = (float)uStack_208 * fVar65;
                auVar121._0_4_ = (float)uStack_210 * fVar130;
                auVar121._4_4_ = uStack_210._4_4_ * fVar131;
                auVar121._8_4_ = (float)uStack_208 * fVar61;
                auVar115._12_4_ = 0;
                auVar129._0_4_ = (float)uStack_210 * fVar73;
                auVar129._4_4_ = uStack_210._4_4_ * fVar71;
                auVar129._8_4_ = (float)uStack_208 * fVar66;
                auVar141._0_4_ = (float)uStack_210 * (float)uStack_1f0;
                auVar141._4_4_ = uStack_210._4_4_ * uStack_1f0._4_4_;
                auVar141._8_4_ = (float)uStack_208 * (float)uStack_1e8;
                auVar149._0_4_ = (float)uStack_210 * fVar133;
                auVar149._4_4_ = uStack_210._4_4_ * fVar142;
                auVar149._8_4_ = (float)uStack_208 * fVar172;
                auVar102._0_4_ = (float)uStack_220 * fVar62;
                auVar102._4_4_ = uStack_220._4_4_ * fVar63;
                auVar102._8_4_ = (float)uStack_218 * fVar65;
                auVar94._0_4_ = (float)uStack_220 * fVar130;
                auVar94._4_4_ = uStack_220._4_4_ * fVar131;
                auVar94._8_4_ = (float)uStack_218 * fVar61;
                auVar107._0_4_ = (float)uStack_220 * fVar73;
                auVar107._4_4_ = uStack_220._4_4_ * fVar71;
                auVar107._8_4_ = (float)uStack_218 * fVar66;
                auVar159._0_4_ = (float)uStack_220 * (float)uStack_200;
                auVar159._4_4_ = uStack_220._4_4_ * uStack_200._4_4_;
                auVar159._8_4_ = (float)uStack_218 * (float)uStack_1f8;
                auVar85._0_4_ = (float)uStack_220 * fVar133;
                auVar85._4_4_ = uStack_220._4_4_ * fVar142;
                auVar85._8_4_ = (float)uStack_218 * fVar172;
                auVar121._12_4_ = 0;
                auVar108 = NEON_ext(auVar115,auVar115,8,1);
                auVar129._12_4_ = 0;
                auVar109 = NEON_ext(auVar121,auVar121,8,1);
                auVar141._12_4_ = 0;
                auVar110 = NEON_ext(auVar129,auVar129,8,1);
                auVar149._12_4_ = 0;
                auVar161 = NEON_ext(auVar141,auVar141,8,1);
                auVar102._12_4_ = 0;
                auVar117 = NEON_ext(auVar149,auVar149,8,1);
                auVar94._12_4_ = 0;
                auVar123 = NEON_ext(auVar102,auVar102,8,1);
                auVar107._12_4_ = 0;
                auVar135 = NEON_ext(auVar94,auVar94,8,1);
                auVar159._12_4_ = 0;
                auVar144 = NEON_ext(auVar107,auVar107,8,1);
                auVar85._12_4_ = 0;
                auVar153 = NEON_ext(auVar159,auVar159,8,1);
                auVar162 = NEON_ext(auVar85,auVar85,8,1);
                uVar116 = NEON_rev64(CONCAT44(auVar108._0_4_ + auVar108._4_4_,
                                              auVar115._0_4_ + auVar115._4_4_),4);
                uVar206 = NEON_rev64(CONCAT44(auVar109._0_4_ + auVar109._4_4_,
                                              auVar121._0_4_ + auVar121._4_4_),4);
                uVar122 = NEON_rev64(CONCAT44(auVar110._0_4_ + auVar110._4_4_,
                                              auVar129._0_4_ + auVar129._4_4_),4);
                uVar143 = NEON_rev64(CONCAT44(auVar123._0_4_ + auVar123._4_4_,
                                              auVar102._0_4_ + auVar102._4_4_),4);
                uVar150 = NEON_rev64(CONCAT44(auVar135._0_4_ + auVar135._4_4_,
                                              auVar94._0_4_ + auVar94._4_4_),4);
                uVar151 = NEON_rev64(CONCAT44(auVar144._0_4_ + auVar144._4_4_,
                                              auVar107._0_4_ + auVar107._4_4_),4);
                auVar95._0_4_ = fVar67 * ABS(auVar115._0_4_ + auVar115._4_4_ + (float)uVar116);
                auVar95._4_4_ = fVar69 * ABS(auVar121._0_4_ + auVar121._4_4_ + (float)uVar206);
                auVar95._8_4_ = fVar72 * ABS(auVar129._0_4_ + auVar129._4_4_ + (float)uVar122);
                fVar67 = fVar67 * ABS(auVar102._0_4_ + auVar102._4_4_ + (float)uVar143);
                fVar69 = fVar69 * ABS(auVar94._0_4_ + auVar94._4_4_ + (float)uVar150);
                fVar72 = fVar72 * ABS(auVar107._0_4_ + auVar107._4_4_ + (float)uVar151);
                uVar206 = NEON_rev64(CONCAT44(auVar153._0_4_ + auVar153._4_4_,
                                              auVar159._0_4_ + auVar159._4_4_),4);
                uVar122 = NEON_rev64(CONCAT44(auVar162._0_4_ + auVar162._4_4_,
                                              auVar85._0_4_ + auVar85._4_4_),4);
                auVar95._12_4_ = 0;
                auVar13._4_4_ = fVar69;
                auVar13._0_4_ = fVar67;
                auVar13._8_4_ = fVar72;
                auVar13._12_4_ = 0;
                auVar14._4_4_ = fVar69;
                auVar14._0_4_ = fVar67;
                auVar14._8_4_ = fVar72;
                auVar14._12_4_ = 0;
                auVar109 = NEON_ext(auVar13,auVar14,8,1);
                uVar143 = NEON_rev64(CONCAT44(auVar117._0_4_ + auVar117._4_4_,
                                              auVar149._0_4_ + auVar149._4_4_),4);
                auVar108 = NEON_ext(auVar95,auVar95,8,1);
                uVar150 = NEON_rev64(CONCAT44(auVar161._0_4_ + auVar161._4_4_,
                                              auVar141._0_4_ + auVar141._4_4_),4);
                uVar116 = NEON_rev64(CONCAT44(auVar109._0_4_ + auVar109._4_4_,fVar67 + fVar69),4);
                fVar71 = (auVar85._0_4_ + auVar85._4_4_ + (float)uVar122) -
                         (auVar159._0_4_ + auVar159._4_4_ + (float)uVar206);
                uVar206 = NEON_rev64(CONCAT44(auVar108._0_4_ + auVar108._4_4_,
                                              auVar95._0_4_ + auVar95._4_4_),4);
                fVar73 = fVar67 + fVar69 + (float)uVar116;
                bVar43 = auVar95._0_4_ + auVar95._4_4_ + (float)uVar206 +
                         ((auVar149._0_4_ + auVar149._4_4_ + (float)uVar143) -
                         (auVar141._0_4_ + auVar141._4_4_ + (float)uVar150)) < 0.0;
                fVar67 = (float)-(uint)bVar43;
                if (0.0 <= fVar73 + fVar71 &&
                    (0.0 <= fVar73 + fVar71 && (0.0 <= fVar73 + fVar71 && !bVar43))) {
                  bVar43 = false;
                  goto code_r0x022656bc;
                }
              }
              bVar43 = true;
            }
code_r0x022656bc:
            bVar46 = true;
            auVar38._8_8_ = CONCAT44(0x3f800000,fVar70);
            auVar38._0_8_ = uVar180;
            auVar134 = auVar38._0_12_;
            auVar41._4_8_ = auVar39._4_8_;
            auVar41._0_4_ = fVar68;
            auVar41._12_4_ = 0;
            auVar145 = auVar41 << 0x20;
            auVar42._4_8_ = auVar40._4_8_;
            auVar42._0_4_ = fVar74;
            auVar42._12_4_ = 0;
            auVar163 = auVar42 << 0x20;
            auVar154._8_8_ = uVar111;
            goto joined_r0x02264db4;
          }
          bVar43 = false;
          bVar24 = false;
          bVar46 = false;
          if ((uVar4 >> 0x1e & 1) != 0) {
            bVar46 = false;
            goto code_r0x022656cc;
          }
code_r0x02264db8:
          uVar180 = auVar134._0_8_;
          fVar67 = 0.0;
          if ((uVar5 >> 0x10 & 1) != 0) {
            fVar67 = *(float *)((long)plVar59 + 0x1c4);
          }
          *(float *)(*plVar2 + (ulong)*(ushort *)(plVar59 + 0x37) * 8 + 4) = auVar163._8_4_ - fVar67
          ;
          fVar67 = (auVar154._8_4_ + auVar134._8_4_) - fVar67;
          *(float *)(*plVar2 + (ulong)*(ushort *)(plVar59 + 0x37) * 8) = fVar67;
        }
        if (param_3 == 0) {
          fVar67 = (float)((ulong)uVar180 >> 0x20) * auVar145._8_4_;
          *(float *)(plVar59 + 0x4a) = (float)uVar180 * auVar145._8_4_;
          *(ulong *)((long)plVar59 + 0x254) = CONCAT44(fVar70,fVar67);
          *(undefined4 *)((long)plVar59 + 0x25c) = 0;
        }
        puVar1 = (ulong *)(param_8 + (long)iVar56 * 8);
        if (bVar24) {
          do {
            cVar7 = '\x01';
            bVar43 = (bool)ExclusiveMonitorPass(puVar1,0x10);
            if (bVar43) {
              *puVar1 = *puVar1 | 2L << iVar57;
              cVar7 = ExclusiveMonitorsStatus();
            }
          } while (cVar7 != '\0');
        }
        else {
          do {
            cVar7 = '\x01';
            bVar43 = (bool)ExclusiveMonitorPass(puVar1,0x10);
            if (bVar43) {
              *puVar1 = *puVar1 | 1L << iVar57;
              cVar7 = ExclusiveMonitorsStatus();
            }
          } while (cVar7 != '\0');
          if (param_3 == 0) {
            uVar4 = *puVar55;
            *puVar55 = uVar4 & 0xfffffffb;
            if (!bVar46) {
              *puVar55 = uVar4 & 0xffffffdb;
            }
          }
        }
joined_r0x02265a58:
        plVar59 = plVar60;
        if (param_7 < (int)uVar58) {
          return;
        }
      }
      auVar108 = *(undefined1 (*) [16])(plVar59 + 0x10);
      plVar59[0x4b] = auVar108._8_8_;
      plVar59[0x4a] = auVar108._0_8_;
      if ((uVar4 >> 0x1e & 1) == 0) {
        fVar67 = 0.0;
        if ((uVar5 >> 0x10 & 1) != 0) {
          fVar67 = *(float *)((long)plVar59 + 0x1c4);
        }
        if ((uVar5 >> 0x11 & 1) == 0) {
          fVar67 = auVar108._8_4_ - fVar67;
          *(float *)(*plVar2 + (ulong)*(ushort *)(plVar59 + 0x37) * 8 + 4) = fVar67;
          uVar6 = *(ushort *)(plVar59 + 0x37);
          lVar53 = *plVar2;
        }
        else {
          fVar70 = *(float *)(plVar59 + 0x5a);
          fVar74 = *(float *)((long)plVar59 + 0x2d4);
          fVar73 = *(float *)(plVar59 + 0x5b);
          fVar71 = *(float *)((long)plVar59 + 0x2dc);
          fVar211 = (float)*(undefined8 *)(param_2 + 0x138);
          fVar212 = (float)((ulong)*(undefined8 *)(param_2 + 0x138) >> 0x20);
          fVar209 = (float)*(undefined8 *)(param_2 + 0x130);
          fVar210 = (float)((ulong)*(undefined8 *)(param_2 + 0x130) >> 0x20);
          fVar215 = (float)*(undefined8 *)(param_2 + 0x148);
          fVar216 = (float)((ulong)*(undefined8 *)(param_2 + 0x148) >> 0x20);
          fVar213 = (float)*(undefined8 *)(param_2 + 0x140);
          fVar214 = (float)((ulong)*(undefined8 *)(param_2 + 0x140) >> 0x20);
          fVar219 = (float)*(undefined8 *)(param_2 + 0x158);
          fVar220 = (float)((ulong)*(undefined8 *)(param_2 + 0x158) >> 0x20);
          fVar217 = (float)*(undefined8 *)(param_2 + 0x150);
          fVar218 = (float)((ulong)*(undefined8 *)(param_2 + 0x150) >> 0x20);
          auVar109._0_4_ = fVar209 * fVar70;
          auVar109._4_4_ = fVar210 * fVar74;
          auVar109._8_4_ = fVar211 * fVar73;
          auVar109._12_4_ = fVar212 * 1.0;
          auVar110._0_4_ = fVar213 * fVar70;
          auVar110._4_4_ = fVar214 * fVar74;
          auVar110._8_4_ = fVar215 * fVar73;
          auVar110._12_4_ = fVar216 * 1.0;
          NEON_ext(auVar109,auVar109,8,1);
          auVar108._0_4_ = fVar217 * fVar70;
          auVar108._4_4_ = fVar218 * fVar74;
          auVar108._8_4_ = fVar219 * fVar73;
          auVar108._12_4_ = fVar220 * 1.0;
          NEON_ext(auVar110,auVar110,8,1);
          auVar109 = NEON_ext(auVar108,auVar108,8,1);
          fVar70 = auVar109._0_4_ + auVar108._0_4_ + auVar109._4_4_ + auVar108._4_4_;
          *(float *)(*plVar2 + (ulong)*(ushort *)(plVar59 + 0x37) * 8 + 4) =
               (fVar70 - fVar71) - fVar67;
          uVar6 = *(ushort *)(plVar59 + 0x37);
          lVar53 = *plVar2;
          fVar67 = (fVar71 + fVar70) - fVar67;
        }
        *(float *)(lVar53 + (ulong)uVar6 * 8) = fVar67;
      }
      else {
        *(undefined4 *)(*plVar2 + (ulong)*(ushort *)(plVar59 + 0x37) * 8 + 4) =
             *(undefined4 *)((long)plVar59 + 0x1bc);
      }
      if (((param_3 != 0) || (*puVar55 = *puVar55 & 0xffffffdb, (uVar5 >> 0x12 & 1) == 0)) ||
         (plVar45 = (long *)plVar59[0x60], plVar45 == (long *)0x0)) {
code_r0x02265a38:
        puVar1 = (ulong *)(param_8 + (long)iVar56 * 8);
        do {
          cVar7 = '\x01';
          bVar43 = (bool)ExclusiveMonitorPass(puVar1,0x10);
          if (bVar43) {
            *puVar1 = *puVar1 | 1L << iVar57;
            cVar7 = ExclusiveMonitorsStatus();
          }
        } while (cVar7 != '\0');
        goto joined_r0x02265a58;
      }
      lVar53 = param_2;
      if (((uVar4 >> 0x17 & 1) != 0) && (plVar59[0x34] != 0)) {
        lVar53 = plVar59[0x34];
      }
      fVar74 = *(float *)((long)plVar59 + 0x6c);
      fVar67 = *(float *)((long)plVar59 + 0x4c);
      fVar70 = *(float *)((long)plVar59 + 0x5c);
      auVar123._0_4_ = *(float *)(lVar53 + 0x130) * fVar67;
      auVar123._4_4_ = *(float *)(lVar53 + 0x134) * fVar70;
      auVar123._8_4_ = *(float *)(lVar53 + 0x138) * fVar74;
      auVar123._12_4_ = *(float *)(lVar53 + 0x13c) * 1.0;
      auVar135._0_4_ = *(float *)(lVar53 + 0x140) * fVar67;
      auVar135._4_4_ = *(float *)(lVar53 + 0x144) * fVar70;
      auVar135._8_4_ = *(float *)(lVar53 + 0x148) * fVar74;
      auVar135._12_4_ = *(float *)(lVar53 + 0x14c) * 1.0;
      fVar67 = *(float *)(lVar53 + 0x150) * fVar67;
      fVar70 = *(float *)(lVar53 + 0x154) * fVar70;
      fVar74 = *(float *)(lVar53 + 0x158) * fVar74;
      fVar73 = *(float *)(lVar53 + 0x15c) * 1.0;
      auVar108 = NEON_ext(auVar123,auVar123,8,1);
      auVar109 = NEON_ext(auVar135,auVar135,8,1);
      auVar161._4_4_ = fVar70;
      auVar161._0_4_ = fVar67;
      auVar161._8_4_ = fVar74;
      auVar161._12_4_ = fVar73;
      auVar117._4_4_ = fVar70;
      auVar117._0_4_ = fVar67;
      auVar117._8_4_ = fVar74;
      auVar117._12_4_ = fVar73;
      auVar110 = NEON_ext(auVar161,auVar117,8,1);
      auStack_d0[0]._0_4_ = auVar108._0_4_ + auVar123._0_4_ + auVar108._4_4_ + auVar123._4_4_;
      auStack_d0[0]._4_4_ = auVar109._0_4_ + auVar135._0_4_ + auVar109._4_4_ + auVar135._4_4_;
      auStack_d0[1]._4_4_ =
           SUB164(ZEXT816(0x3f0000003f000000),0) + SUB164(ZEXT816(0x3f0000003f000000),4);
      auStack_d0[1]._0_4_ = auVar110._0_4_ + fVar67 + auVar110._4_4_ + fVar70;
      fVar67 = (float)(**(code **)(*plVar45 + 8))(0x3f800000,plVar45,auStack_d0,plVar59,0,0);
      if (0.0 < fVar67) {
        fVar67 = (float)(**(code **)(*plVar59 + 0x240))(plVar59);
        goto code_r0x02265a38;
      }
      puVar1 = (ulong *)(param_8 + (long)iVar56 * 8);
      do {
        cVar7 = '\x01';
        bVar43 = (bool)ExclusiveMonitorPass(puVar1,0x10);
        if (bVar43) {
          *puVar1 = *puVar1 | 2L << iVar57;
          cVar7 = ExclusiveMonitorsStatus();
        }
      } while (cVar7 != '\0');
      plVar59 = plVar60;
    } while ((int)uVar58 <= param_7);
  }
  return;
}

// ==== Aska::ObjectManager::DetectLIBL(Aska::RenderableObject**, int, int)
// vaddr 0x2165a8c | ghidra 0x2265a8c | size 28 | symbol _ZN4Aska13ObjectManager10DetectLIBLEPPNS_16RenderableObjectEii | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13ObjectManager10DetectLIBLEPPNS_16RenderableObjectEii
               (undefined8 param_1,undefined8 param_2,int param_3,int param_4)

{
  (*(code *)PTR__ZN4Aska11LIBLManager9IntersectEPPNS_16RenderableObjectEii_02c94cb8)
            (*(undefined8 *)PTR__ZN4Aska6Global14m_pLIBLManagerE_02cc46a8,param_2,param_3,
             (1 - param_3) + param_4);
  return;
}

// ==== Aska::ObjectManager::SubViewFrustumCulling(Aska::Camera*, int, int, Aska::RenderableObject**, int, int, unsigned long*)
// vaddr 0x2165aa8 | ghidra 0x2265aa8 | size 3196 | symbol _ZN4Aska13ObjectManager21SubViewFrustumCullingEPNS_6CameraEiiPPNS_16RenderableObjectEiiPm | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska13ObjectManager21SubViewFrustumCullingEPNS_6CameraEiiPPNS_16RenderableObjectEiiPm
               (undefined8 param_1,long param_2,int param_3,undefined8 param_4,long param_5,
               uint param_6,int param_7,long param_8)

{
  ulong *puVar1;
  long lVar2;
  int *piVar3;
  int iVar4;
  char cVar5;
  undefined1 auVar6 [16];
  undefined1 auVar7 [16];
  undefined1 auVar8 [16];
  undefined1 auVar9 [16];
  undefined1 auVar10 [16];
  undefined1 auVar11 [16];
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  bool bVar19;
  int iVar20;
  float *pfVar21;
  long lVar22;
  float *pfVar23;
  long lVar24;
  long lVar25;
  ulong uVar26;
  uint uVar27;
  ulong uVar28;
  long *plVar29;
  long *plVar30;
  float fVar31;
  float fVar32;
  undefined4 uVar33;
  float fVar34;
  undefined4 uVar35;
  float fVar36;
  uint uVar37;
  float fVar38;
  float fVar39;
  float fVar40;
  float fVar41;
  float fVar42;
  float fVar43;
  float fVar44;
  float fVar45;
  float fVar46;
  undefined1 auVar47 [16];
  undefined1 auVar48 [16];
  undefined1 auVar49 [16];
  undefined1 auVar50 [16];
  float fVar51;
  undefined1 auVar52 [16];
  undefined1 auVar53 [16];
  undefined1 auVar54 [16];
  undefined1 auVar55 [16];
  float fVar59;
  undefined1 auVar56 [16];
  undefined1 auVar57 [16];
  undefined1 auVar58 [16];
  float fVar60;
  float fVar61;
  float fVar62;
  float fVar63;
  float fVar64;
  float fVar65;
  float fVar66;
  float fVar67;
  undefined8 uVar68;
  undefined1 auVar69 [16];
  undefined1 auVar70 [16];
  undefined1 auVar71 [16];
  undefined1 auVar72 [16];
  undefined8 uVar73;
  undefined1 auVar74 [16];
  undefined1 auVar75 [16];
  undefined1 auVar76 [16];
  undefined1 auVar77 [16];
  undefined1 auVar78 [16];
  undefined1 auVar79 [16];
  undefined8 uVar80;
  undefined1 auVar81 [16];
  undefined1 auVar82 [16];
  undefined1 auVar83 [16];
  undefined1 auVar84 [16];
  undefined1 auVar85 [16];
  undefined1 auVar86 [16];
  undefined1 auVar87 [16];
  undefined8 uVar88;
  undefined1 auVar89 [16];
  undefined1 auVar90 [16];
  undefined1 auVar91 [16];
  undefined1 auVar92 [16];
  undefined1 auVar93 [16];
  undefined8 uVar94;
  undefined1 auVar96 [16];
  undefined1 auVar97 [16];
  undefined1 auVar98 [16];
  undefined1 auVar99 [16];
  undefined8 uVar95;
  undefined1 auVar100 [16];
  undefined1 auVar101 [16];
  undefined8 uVar102;
  undefined1 auVar103 [16];
  undefined1 auVar104 [16];
  undefined1 auVar105 [16];
  undefined1 auVar106 [16];
  undefined8 uVar107;
  undefined1 auVar109 [16];
  undefined1 auVar110 [16];
  undefined1 auVar111 [16];
  undefined8 uVar108;
  undefined1 auVar112 [16];
  float fVar113;
  undefined8 uVar114;
  undefined1 auVar115 [16];
  undefined1 auVar116 [16];
  float fVar117;
  undefined8 uVar118;
  undefined8 uVar119;
  undefined8 uVar120;
  undefined8 uVar121;
  undefined8 uVar122;
  undefined8 uVar123;
  undefined1 auVar124 [16];
  undefined1 auVar125 [16];
  undefined1 auVar126 [16];
  undefined1 auVar127 [16];
  undefined8 uVar128;
  undefined1 auVar129 [16];
  undefined1 auVar130 [16];
  undefined1 auVar131 [16];
  undefined8 uVar132;
  float fVar138;
  undefined1 auVar135 [16];
  undefined1 auVar136 [16];
  undefined8 uVar133;
  undefined8 uVar134;
  undefined1 auVar137 [16];
  undefined1 auVar139 [16];
  undefined1 auVar140 [16];
  undefined1 auVar141 [16];
  undefined1 auVar142 [16];
  undefined1 auVar143 [16];
  undefined8 uStack_150;
  ulong uStack_148;
  undefined8 uStack_140;
  undefined8 uStack_138;
  undefined8 uStack_130;
  undefined8 uStack_128;
  undefined8 uStack_120;
  undefined8 uStack_118;
  long lStack_108;
  undefined8 uStack_100;
  undefined8 uStack_f8;
  undefined8 uStack_f0;
  undefined8 uStack_e8;
  undefined8 uStack_e0;
  undefined8 uStack_d8;
  undefined8 uStack_d0;
  undefined8 uStack_c8;
  undefined8 uStack_c0;
  undefined8 uStack_b8;
  undefined8 uStack_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined8 uStack_98;
  undefined8 uStack_90;
  undefined8 uStack_88;
  
  uVar26 = (ulong)param_6;
  if (((bRam0000000002dd06b0 & 1) == 0) && (iVar20 = __cxa_guard_acquire(0x2dd06b0), iVar20 != 0)) {
    uRam0000000002dd06a8 = _UNK_027e51b8;
    uRam0000000002dd06a0 = _UNK_027e51b0;
    __cxa_guard_release(0x2dd06b0);
  }
  if ((int)param_6 <= param_7) {
    plVar30 = *(long **)(param_5 + (long)(int)param_6 * 8);
    lVar2 = (long)(int)param_4 + 1;
    lVar22 = param_2 + lVar2 * 0x60;
    uStack_148 = *(ulong *)(lVar22 + 0x5b8);
    uStack_150 = *(undefined8 *)(lVar22 + 0x5b0);
    uStack_138 = *(undefined8 *)(lVar22 + 0x5a8);
    uStack_140 = *(undefined8 *)(lVar22 + 0x5a0);
    uStack_f8 = *(undefined8 *)(lVar22 + 0x598);
    uStack_100 = *(undefined8 *)(lVar22 + 0x590);
    uStack_e8 = *(undefined8 *)(lVar22 + 0x588);
    uStack_f0 = *(undefined8 *)(lVar22 + 0x580);
    uStack_d8 = *(undefined8 *)(lVar22 + 0x578);
    uStack_e0 = *(undefined8 *)(lVar22 + 0x570);
    uStack_c8 = *(undefined8 *)(lVar22 + 0x568);
    uStack_d0 = *(undefined8 *)(lVar22 + 0x560);
    uStack_128 = *(undefined8 *)(lVar22 + 600);
    uStack_130 = *(undefined8 *)(lVar22 + 0x250);
    uStack_118 = *(undefined8 *)(lVar22 + 0x248);
    uStack_120 = *(undefined8 *)(lVar22 + 0x240);
    uStack_b8 = *(undefined8 *)(lVar22 + 0x238);
    uStack_c0 = *(undefined8 *)(lVar22 + 0x230);
    uStack_a8 = *(undefined8 *)(lVar22 + 0x228);
    uStack_b0 = *(undefined8 *)(lVar22 + 0x220);
    uStack_98 = *(undefined8 *)(lVar22 + 0x218);
    uStack_a0 = *(undefined8 *)(lVar22 + 0x210);
    uStack_88 = *(undefined8 *)(lVar22 + 0x208);
    uStack_90 = *(undefined8 *)(lVar22 + 0x200);
    lStack_108 = param_2;
    do {
      uVar28 = (long)(int)uVar26;
      plVar29 = plVar30;
      while( true ) {
        uVar26 = uVar28 + 1;
        plVar30 = *(long **)(param_5 + uVar26 * 8);
        uVar37 = *(uint *)(plVar29 + 0x33);
        uVar27 = (uint)uVar28;
        iVar20 = (uVar27 & 0x1f) << 1;
        if ((*(byte *)(plVar29 + 0x25) >> 4 & 1) == 0) {
          (**(code **)(*plVar29 + 600))(plVar29,0);
        }
        iVar4 = (int)uVar27 >> 5;
        if ((uVar37 >> 1 & 1) == 0) break;
        piVar3 = (int *)((long)plVar29 + 0x1ac);
        do {
          cVar5 = '\x01';
          bVar19 = (bool)ExclusiveMonitorPass(piVar3,0x10);
          if (bVar19) {
            *piVar3 = *piVar3 + 1;
            cVar5 = ExclusiveMonitorsStatus();
          }
        } while (cVar5 != '\0');
        puVar1 = (ulong *)(param_8 + (long)iVar4 * 8);
        do {
          cVar5 = '\x01';
          bVar19 = (bool)ExclusiveMonitorPass(puVar1,0x10);
          if (bVar19) {
            *puVar1 = *puVar1 | 1L << iVar20;
            cVar5 = ExclusiveMonitorsStatus();
          }
        } while (cVar5 != '\0');
        bVar19 = (long)param_7 <= (long)uVar28;
        uVar28 = uVar26;
        plVar29 = plVar30;
        if (bVar19) {
          return;
        }
      }
      if (param_3 == 0) {
        if ((uVar37 >> 0x17 & 1) == 0) {
          bVar19 = lStack_108 != param_2;
          lStack_108 = param_2;
          if (bVar19) {
            if (*(char *)(param_2 + lVar2 + 0x940) == '\0') {
              Aska::Camera::MakeViewFrustumPlane(int)(param_2,param_4);
            }
            uStack_88 = *(undefined8 *)(lVar22 + 0x208);
            uStack_90 = *(undefined8 *)(lVar22 + 0x200);
            uStack_98 = *(undefined8 *)(lVar22 + 0x218);
            uStack_a0 = *(undefined8 *)(lVar22 + 0x210);
            uStack_a8 = *(undefined8 *)(lVar22 + 0x228);
            uStack_b0 = *(undefined8 *)(lVar22 + 0x220);
            uStack_b8 = *(undefined8 *)(lVar22 + 0x238);
            uStack_c0 = *(undefined8 *)(lVar22 + 0x230);
            uStack_118 = *(undefined8 *)(lVar22 + 0x248);
            uStack_120 = *(undefined8 *)(lVar22 + 0x240);
            uStack_128 = *(undefined8 *)(lVar22 + 600);
            uStack_130 = *(undefined8 *)(lVar22 + 0x250);
            uStack_c8 = *(undefined8 *)(lVar22 + 0x568);
            uStack_d0 = *(undefined8 *)(lVar22 + 0x560);
            uStack_d8 = *(undefined8 *)(lVar22 + 0x578);
            uStack_e0 = *(undefined8 *)(lVar22 + 0x570);
            uStack_e8 = *(undefined8 *)(lVar22 + 0x588);
            uStack_f0 = *(undefined8 *)(lVar22 + 0x580);
            uStack_f8 = *(undefined8 *)(lVar22 + 0x598);
            uStack_100 = *(undefined8 *)(lVar22 + 0x590);
            uStack_138 = *(undefined8 *)(lVar22 + 0x5a8);
            uStack_140 = *(undefined8 *)(lVar22 + 0x5a0);
            uVar37 = (uint)*(undefined8 *)(lVar22 + 0x5b8);
            uVar68 = *(undefined8 *)(lVar22 + 0x5b0);
            uVar33 = (undefined4)uVar68;
            uVar35 = (undefined4)((ulong)uVar68 >> 0x20);
            lVar24 = param_2;
code_r0x02266544:
            uStack_148 = (ulong)uVar37;
            uStack_150 = CONCAT44(uVar35,uVar33);
            lStack_108 = lVar24;
          }
        }
        else {
          lVar24 = plVar29[0x34];
          if ((lVar24 != 0) && (lVar24 != lStack_108)) {
            lVar25 = lVar24 + lVar2 * 0x60;
            uStack_88 = *(undefined8 *)(lVar25 + 0x208);
            uStack_90 = *(undefined8 *)(lVar25 + 0x200);
            uStack_98 = *(undefined8 *)(lVar25 + 0x218);
            uStack_a0 = *(undefined8 *)(lVar25 + 0x210);
            uStack_a8 = *(undefined8 *)(lVar25 + 0x228);
            uStack_b0 = *(undefined8 *)(lVar25 + 0x220);
            uStack_b8 = *(undefined8 *)(lVar25 + 0x238);
            uStack_c0 = *(undefined8 *)(lVar25 + 0x230);
            uStack_118 = *(undefined8 *)(lVar25 + 0x248);
            uStack_120 = *(undefined8 *)(lVar25 + 0x240);
            uStack_128 = *(undefined8 *)(lVar25 + 600);
            uStack_130 = *(undefined8 *)(lVar25 + 0x250);
            uStack_c8 = *(undefined8 *)(lVar25 + 0x568);
            uStack_d0 = *(undefined8 *)(lVar25 + 0x560);
            uStack_d8 = *(undefined8 *)(lVar25 + 0x578);
            uStack_e0 = *(undefined8 *)(lVar25 + 0x570);
            uStack_e8 = *(undefined8 *)(lVar25 + 0x588);
            uStack_f0 = *(undefined8 *)(lVar25 + 0x580);
            uStack_f8 = *(undefined8 *)(lVar25 + 0x598);
            uStack_100 = *(undefined8 *)(lVar25 + 0x590);
            uStack_138 = *(undefined8 *)(lVar25 + 0x5a8);
            uStack_140 = *(undefined8 *)(lVar25 + 0x5a0);
            uVar37 = (uint)*(undefined8 *)(lVar25 + 0x5b8);
            uVar33 = (undefined4)*(undefined8 *)(lVar25 + 0x5b0);
            uVar35 = (undefined4)((ulong)*(undefined8 *)(lVar25 + 0x5b0) >> 0x20);
            goto code_r0x02266544;
          }
        }
      }
      fVar45 = (float)plVar29[0x5b];
      fVar31 = (float)((ulong)plVar29[0x5b] >> 0x20);
      fVar40 = (float)plVar29[0x5a];
      fVar43 = (float)((ulong)plVar29[0x5a] >> 0x20);
      fVar117 = (float)((ulong)uStack_c0 >> 0x20);
      auVar96._0_4_ = (float)uStack_d0 * (fVar40 - (float)uStack_90);
      auVar96._4_4_ = uStack_d0._4_4_ * (fVar43 - uStack_90._4_4_);
      auVar96._8_4_ = (float)uStack_c8 * (fVar45 - (float)uStack_88);
      auVar103._0_4_ = (float)uStack_e0 * (fVar40 - (float)uStack_a0);
      auVar103._4_4_ = uStack_e0._4_4_ * (fVar43 - uStack_a0._4_4_);
      auVar103._8_4_ = (float)uStack_d8 * (fVar45 - (float)uStack_98);
      auVar125._0_4_ = (float)uStack_f0 * (fVar40 - (float)uStack_b0);
      auVar125._4_4_ = uStack_f0._4_4_ * (fVar43 - uStack_b0._4_4_);
      auVar125._8_4_ = (float)uStack_e8 * (fVar45 - (float)uStack_a8);
      Hint_Prefetch(plVar30 + 0x33,0,2,0);
      fVar62 = (float)uStack_100 * (fVar40 - (float)uStack_c0);
      fVar65 = uStack_100._4_4_ * (fVar43 - fVar117);
      fVar66 = (float)uStack_f8 * (fVar45 - (float)uStack_b8);
      auVar96._12_4_ = 0;
      auVar103._12_4_ = 0;
      auVar125._12_4_ = 0;
      auVar72 = NEON_ext(auVar96,auVar96,8,1);
      auVar79 = NEON_ext(auVar103,auVar103,8,1);
      auVar86 = NEON_ext(auVar125,auVar125,8,1);
      auVar93._4_4_ = fVar65;
      auVar93._0_4_ = fVar62;
      auVar93._8_4_ = fVar66;
      auVar93._12_4_ = 0;
      auVar87._4_4_ = fVar65;
      auVar87._0_4_ = fVar62;
      auVar87._8_4_ = fVar66;
      auVar87._12_4_ = 0;
      auVar93 = NEON_ext(auVar93,auVar87,8,1);
      uVar68 = NEON_rev64(CONCAT44(auVar72._0_4_ + auVar72._4_4_,auVar96._0_4_ + auVar96._4_4_),4);
      uVar73 = NEON_rev64(CONCAT44(auVar79._0_4_ + auVar79._4_4_,auVar103._0_4_ + auVar103._4_4_),4)
      ;
      uVar80 = NEON_rev64(CONCAT44(auVar86._0_4_ + auVar86._4_4_,auVar125._0_4_ + auVar125._4_4_),4)
      ;
      uVar88 = NEON_rev64(CONCAT44(auVar93._0_4_ + auVar93._4_4_,fVar62 + fVar65),4);
      fVar66 = auVar96._0_4_ + auVar96._4_4_ + (float)uVar68;
      fVar51 = auVar103._0_4_ + auVar103._4_4_ + (float)uVar73;
      fVar67 = auVar125._0_4_ + auVar125._4_4_ + (float)uVar80;
      fVar62 = fVar62 + fVar65 + (float)uVar88;
      if (((fVar31 + fVar66 < 0.0 || fVar31 + fVar51 < 0.0) || fVar31 + fVar67 < 0.0) ||
          fVar31 + fVar62 < 0.0) {
code_r0x022666dc:
        puVar1 = (ulong *)(param_8 + (long)iVar4 * 8);
        do {
          cVar5 = '\x01';
          bVar19 = (bool)ExclusiveMonitorPass(puVar1,0x10);
          if (bVar19) {
            *puVar1 = *puVar1 | 3L << iVar20;
            cVar5 = ExclusiveMonitorsStatus();
          }
        } while (cVar5 != '\0');
      }
      else {
        auVar86._0_4_ = (float)uStack_140 * (fVar40 - (float)uStack_120);
        auVar86._4_4_ = uStack_140._4_4_ * (fVar43 - uStack_120._4_4_);
        auVar86._8_4_ = (float)uStack_138 * (fVar45 - (float)uStack_118);
        fVar40 = (float)uStack_150 * (fVar40 - (float)uStack_130);
        fVar43 = uStack_150._4_4_ * (fVar43 - uStack_130._4_4_);
        fVar45 = (float)uStack_148 * (fVar45 - (float)uStack_128);
        auVar86._12_4_ = 0;
        auVar93 = NEON_ext(auVar86,auVar86,8,1);
        auVar72._4_4_ = fVar43;
        auVar72._0_4_ = fVar40;
        auVar72._8_4_ = fVar45;
        auVar72._12_4_ = 0;
        auVar79._4_4_ = fVar43;
        auVar79._0_4_ = fVar40;
        auVar79._8_4_ = fVar45;
        auVar79._12_4_ = 0;
        auVar87 = NEON_ext(auVar72,auVar79,8,1);
        uVar68 = NEON_rev64(CONCAT44(auVar93._0_4_ + auVar93._4_4_,auVar86._0_4_ + auVar86._4_4_),4)
        ;
        uVar73 = NEON_rev64(CONCAT44(auVar87._0_4_ + auVar87._4_4_,fVar40 + fVar43),4);
        fVar45 = auVar86._0_4_ + auVar86._4_4_ + (float)uVar68;
        fVar40 = fVar40 + fVar43 + (float)uVar73;
        if (((fVar31 + fVar45 < 0.0 || fVar31 + fVar40 < 0.0) || fVar31 + fVar40 < 0.0) ||
            fVar31 + fVar40 < 0.0) goto code_r0x022666dc;
        if (((((fVar66 - fVar31 < 0.0 || fVar66 - fVar31 < 0.0) || fVar66 - fVar31 < 0.0) ||
              fVar51 - fVar31 < 0.0) ||
            (fVar62 = fVar62 - fVar31, fVar45 = fVar45 - fVar31, fVar43 = fVar40 - fVar31,
            bVar19 = fVar67 - fVar31 < 0.0, fVar31 = (float)-(uint)bVar19,
            fVar43 < 0.0 || (fVar45 < 0.0 || (fVar62 < 0.0 || bVar19)))) &&
           (pfVar21 = (float *)(**(code **)(*plVar29 + 0x150))(fVar31,fVar40,plVar29,0),
           pfVar21 != (float *)0x0)) {
          pfVar23 = (float *)plVar29[0x24];
          auVar56._0_4_ = (float)uStack_d0 * (float)uStack_90;
          auVar56._4_4_ = uStack_d0._4_4_ * uStack_90._4_4_;
          auVar56._8_4_ = (float)uStack_c8 * (float)uStack_88;
          fVar60 = (float)uStack_e0 * (float)uStack_a0;
          fVar63 = uStack_e0._4_4_ * uStack_a0._4_4_;
          auVar69._0_4_ = (float)uStack_f0 * (float)uStack_b0;
          auVar69._4_4_ = uStack_f0._4_4_ * uStack_b0._4_4_;
          auVar69._8_4_ = (float)uStack_e8 * (float)uStack_a8;
          auVar74._0_4_ = (float)uStack_100 * (float)uStack_c0;
          auVar74._4_4_ = uStack_100._4_4_ * fVar117;
          auVar74._8_4_ = (float)uStack_f8 * (float)uStack_b8;
          auVar56._12_4_ = 0;
          auVar69._12_4_ = 0;
          auVar74._12_4_ = 0;
          auVar93 = NEON_ext(auVar56,auVar56,8,1);
          auVar140._4_4_ = fVar63;
          auVar140._0_4_ = fVar60;
          auVar140._8_4_ = (float)uStack_d8 * (float)uStack_98;
          auVar140._12_4_ = 0;
          auVar141._4_4_ = fVar63;
          auVar141._0_4_ = fVar60;
          auVar141._8_4_ = (float)uStack_d8 * (float)uStack_98;
          auVar141._12_4_ = 0;
          auVar87 = NEON_ext(auVar140,auVar141,8,1);
          auVar96 = NEON_ext(auVar69,auVar69,8,1);
          auVar103 = NEON_ext(auVar74,auVar74,8,1);
          fVar31 = *pfVar21;
          fVar40 = pfVar21[1];
          fVar43 = pfVar21[2];
          fVar45 = pfVar21[3];
          fVar36 = (float)*(undefined8 *)(pfVar21 + 6);
          fVar32 = (float)*(undefined8 *)(pfVar21 + 4);
          fVar34 = (float)((ulong)*(undefined8 *)(pfVar21 + 4) >> 0x20);
          fVar66 = *pfVar23;
          fVar51 = pfVar23[1];
          fVar62 = pfVar23[2];
          fVar117 = pfVar23[3];
          fVar65 = pfVar23[4];
          fVar67 = pfVar23[5];
          fVar59 = pfVar23[6];
          fVar113 = pfVar23[7];
          fVar61 = pfVar21[8];
          fVar64 = pfVar21[9];
          fVar138 = pfVar21[10];
          fVar12 = pfVar21[0xb];
          fVar44 = (float)*(undefined8 *)(pfVar21 + 0xe);
          fVar46 = (float)((ulong)*(undefined8 *)(pfVar21 + 0xe) >> 0x20);
          fVar38 = (float)*(undefined8 *)(pfVar21 + 0xc);
          fVar41 = (float)((ulong)*(undefined8 *)(pfVar21 + 0xc) >> 0x20);
          fVar13 = pfVar23[8];
          fVar14 = pfVar23[9];
          fVar15 = pfVar23[10];
          fVar16 = pfVar23[0xb];
          fVar39 = pfVar23[0xc];
          fVar42 = pfVar23[0xd];
          fVar17 = pfVar23[0xe];
          fVar18 = pfVar23[0xf];
          uVar68 = NEON_rev64(CONCAT44(auVar93._0_4_ + auVar93._4_4_,auVar56._0_4_ + auVar56._4_4_),
                              4);
          uVar118 = NEON_rev64(CONCAT44(auVar87._0_4_ + auVar87._4_4_,fVar60 + fVar63),4);
          uVar128 = NEON_rev64(CONCAT44(auVar96._0_4_ + auVar96._4_4_,auVar69._0_4_ + auVar69._4_4_)
                               ,4);
          uVar132 = NEON_rev64(CONCAT44(auVar103._0_4_ + auVar103._4_4_,
                                        auVar74._0_4_ + auVar74._4_4_),4);
          auVar81._0_4_ = fVar66 * fVar31;
          auVar81._4_4_ = fVar51 * fVar40;
          auVar81._8_4_ = fVar62 * fVar43;
          auVar81._12_4_ = fVar117 * fVar45;
          auVar89._0_4_ = fVar65 * fVar31;
          auVar89._4_4_ = fVar67 * fVar40;
          auVar89._8_4_ = fVar59 * fVar43;
          auVar89._12_4_ = fVar113 * fVar45;
          auVar124._0_4_ = fVar13 * fVar31;
          auVar124._4_4_ = fVar14 * fVar40;
          auVar124._8_4_ = fVar15 * fVar43;
          auVar124._12_4_ = fVar16 * fVar45;
          auVar52._0_4_ = fVar39 * fVar31;
          auVar52._4_4_ = fVar42 * fVar40;
          auVar52._8_4_ = fVar17 * fVar43;
          auVar52._12_4_ = fVar18 * fVar45;
          auVar129._0_4_ = fVar66 * fVar61;
          auVar129._4_4_ = fVar51 * fVar64;
          auVar129._8_4_ = fVar62 * fVar138;
          auVar129._12_4_ = fVar117 * fVar12;
          auVar135._0_4_ = fVar65 * fVar61;
          auVar135._4_4_ = fVar67 * fVar64;
          auVar135._8_4_ = fVar59 * fVar138;
          auVar135._12_4_ = fVar113 * fVar12;
          auVar139._0_4_ = fVar13 * fVar61;
          auVar139._4_4_ = fVar14 * fVar64;
          auVar139._8_4_ = fVar15 * fVar138;
          auVar139._12_4_ = fVar16 * fVar12;
          auVar47._0_4_ = fVar39 * fVar61;
          auVar47._4_4_ = fVar42 * fVar64;
          auVar47._8_4_ = fVar17 * fVar138;
          auVar47._12_4_ = fVar18 * fVar12;
          auVar97._0_4_ = fVar66 * fVar38;
          auVar97._4_4_ = fVar51 * fVar41;
          auVar97._8_4_ = fVar62 * fVar44;
          auVar97._12_4_ = fVar117 * fVar46;
          auVar104._0_4_ = fVar65 * fVar38;
          auVar104._4_4_ = fVar67 * fVar41;
          auVar104._8_4_ = fVar59 * fVar44;
          auVar104._12_4_ = fVar113 * fVar46;
          auVar109._0_4_ = fVar13 * fVar38;
          auVar109._4_4_ = fVar14 * fVar41;
          auVar109._8_4_ = fVar15 * fVar44;
          auVar109._12_4_ = fVar16 * fVar46;
          fVar39 = fVar39 * fVar38;
          fVar42 = fVar42 * fVar41;
          auVar93 = NEON_ext(auVar81,auVar81,8,1);
          auVar87 = NEON_ext(auVar89,auVar89,8,1);
          auVar96 = NEON_ext(auVar124,auVar124,8,1);
          auVar103 = NEON_ext(auVar52,auVar52,8,1);
          auVar125 = NEON_ext(auVar129,auVar129,8,1);
          auVar72 = NEON_ext(auVar135,auVar135,8,1);
          auVar79 = NEON_ext(auVar139,auVar139,8,1);
          auVar86 = NEON_ext(auVar47,auVar47,8,1);
          auVar140 = NEON_ext(auVar97,auVar97,8,1);
          auVar141 = NEON_ext(auVar104,auVar104,8,1);
          auVar142 = NEON_ext(auVar109,auVar109,8,1);
          auVar143._4_4_ = fVar42;
          auVar143._0_4_ = fVar39;
          auVar143._8_4_ = fVar17 * fVar44;
          auVar143._12_4_ = fVar18 * fVar46;
          auVar106._4_4_ = fVar42;
          auVar106._0_4_ = fVar39;
          auVar106._8_4_ = fVar17 * fVar44;
          auVar106._12_4_ = fVar18 * fVar46;
          auVar143 = NEON_ext(auVar143,auVar106,8,1);
          uVar73 = NEON_rev64(CONCAT44(auVar93._0_4_ + auVar93._4_4_,auVar81._0_4_ + auVar81._4_4_),
                              4);
          fVar43 = auVar81._0_4_ + auVar81._4_4_ + (float)uVar73;
          uVar73 = NEON_rev64(CONCAT44(auVar87._0_4_ + auVar87._4_4_,auVar89._0_4_ + auVar89._4_4_),
                              4);
          fVar45 = auVar89._0_4_ + auVar89._4_4_ + (float)uVar73;
          uVar73 = NEON_rev64(CONCAT44(auVar96._0_4_ + auVar96._4_4_,auVar124._0_4_ + auVar124._4_4_
                                      ),4);
          fVar113 = auVar124._0_4_ + auVar124._4_4_ + (float)uVar73;
          NEON_rev64(CONCAT44(auVar103._0_4_ + auVar103._4_4_,auVar52._0_4_ + auVar52._4_4_),4);
          uVar73 = NEON_rev64(CONCAT44(auVar125._0_4_ + auVar125._4_4_,
                                       auVar129._0_4_ + auVar129._4_4_),4);
          fVar117 = auVar129._0_4_ + auVar129._4_4_ + (float)uVar73;
          uVar73 = NEON_rev64(CONCAT44(auVar72._0_4_ + auVar72._4_4_,auVar135._0_4_ + auVar135._4_4_
                                      ),4);
          fVar65 = auVar135._0_4_ + auVar135._4_4_ + (float)uVar73;
          uVar73 = NEON_rev64(CONCAT44(auVar79._0_4_ + auVar79._4_4_,auVar139._0_4_ + auVar139._4_4_
                                      ),4);
          fVar67 = auVar139._0_4_ + auVar139._4_4_ + (float)uVar73;
          uVar73 = NEON_rev64(CONCAT44(auVar86._0_4_ + auVar86._4_4_,auVar47._0_4_ + auVar47._4_4_),
                              4);
          fVar31 = auVar47._0_4_ + auVar47._4_4_ + (float)uVar73;
          uVar73 = NEON_rev64(CONCAT44(auVar140._0_4_ + auVar140._4_4_,auVar97._0_4_ + auVar97._4_4_
                                      ),4);
          fVar66 = auVar97._0_4_ + auVar97._4_4_ + (float)uVar73;
          uVar73 = NEON_rev64(CONCAT44(auVar141._0_4_ + auVar141._4_4_,
                                       auVar104._0_4_ + auVar104._4_4_),4);
          fVar51 = auVar104._0_4_ + auVar104._4_4_ + (float)uVar73;
          uVar73 = NEON_rev64(CONCAT44(auVar142._0_4_ + auVar142._4_4_,
                                       auVar109._0_4_ + auVar109._4_4_),4);
          fVar62 = auVar109._0_4_ + auVar109._4_4_ + (float)uVar73;
          uVar73 = NEON_rev64(CONCAT44(auVar143._0_4_ + auVar143._4_4_,fVar39 + fVar42),4);
          fVar40 = fVar39 + fVar42 + (float)uVar73;
          auVar142._0_4_ = fVar117 * fVar117;
          auVar142._4_4_ = fVar65 * fVar65;
          auVar142._8_4_ = fVar67 * fVar67;
          auVar142._12_4_ = fVar31 * fVar31;
          auVar110._0_4_ = (float)uStack_d0 * fVar43;
          auVar110._4_4_ = uStack_d0._4_4_ * fVar45;
          auVar110._8_4_ = (float)uStack_c8 * fVar113;
          auVar53._0_4_ = fVar66 * fVar66;
          auVar53._4_4_ = fVar51 * fVar51;
          auVar53._8_4_ = fVar62 * fVar62;
          auVar53._12_4_ = fVar40 * fVar40;
          auVar130._0_4_ = (float)uStack_e0 * fVar43;
          auVar130._4_4_ = uStack_e0._4_4_ * fVar45;
          auVar130._8_4_ = (float)uStack_d8 * fVar113;
          auVar125 = NEON_ext(auVar142,auVar142,8,1);
          auVar110._12_4_ = 0;
          auVar126._0_4_ = (float)uStack_f0 * fVar43;
          auVar126._4_4_ = uStack_f0._4_4_ * fVar45;
          auVar126._8_4_ = (float)uStack_e8 * fVar113;
          auVar72 = NEON_ext(auVar53,auVar53,8,1);
          auVar130._12_4_ = 0;
          auVar93 = NEON_ext(auVar110,auVar110,8,1);
          auVar136._0_4_ = (float)uStack_100 * fVar43;
          auVar136._4_4_ = uStack_100._4_4_ * fVar45;
          auVar136._8_4_ = (float)uStack_f8 * fVar113;
          auVar126._12_4_ = 0;
          auVar87 = NEON_ext(auVar130,auVar130,8,1);
          auVar136._12_4_ = 0;
          auVar96 = NEON_ext(auVar126,auVar126,8,1);
          auVar103 = NEON_ext(auVar136,auVar136,8,1);
          fVar31 = auVar125._0_4_ + auVar142._0_4_ + auVar125._4_4_ + auVar142._4_4_;
          auVar82._0_4_ = (fVar65 * fVar62 - fVar67 * fVar51) * _UNK_029c49f0;
          auVar82._4_4_ = (fVar117 * fVar62 - fVar67 * fVar66) * _UNK_029c49f4;
          auVar82._8_4_ = (fVar117 * fVar51 - fVar65 * fVar66) * _UNK_029c49f8;
          uVar94 = NEON_rev64(CONCAT44(auVar93._0_4_ + auVar93._4_4_,auVar110._0_4_ + auVar110._4_4_
                                      ),4);
          fVar40 = auVar72._0_4_ + auVar53._0_4_ + auVar72._4_4_ + auVar53._4_4_;
          auVar48._4_4_ = fVar31;
          auVar48._0_4_ = fVar31;
          auVar48._8_4_ = fVar31;
          auVar48._12_4_ = fVar31;
          uVar133 = NEON_rev64(CONCAT44(auVar87._0_4_ + auVar87._4_4_,
                                        auVar130._0_4_ + auVar130._4_4_),4);
          uVar107 = NEON_rev64(CONCAT44(auVar96._0_4_ + auVar96._4_4_,
                                        auVar126._0_4_ + auVar126._4_4_),4);
          auVar54._4_4_ = fVar40;
          auVar54._0_4_ = fVar40;
          auVar54._8_4_ = fVar40;
          auVar54._12_4_ = fVar40;
          uVar134 = NEON_rev64(CONCAT44(auVar103._0_4_ + auVar103._4_4_,
                                        auVar136._0_4_ + auVar136._4_4_),4);
          auVar93 = NEON_frsqrte(auVar48,4);
          auVar87 = NEON_frsqrte(auVar54,4);
          fVar31 = auVar93._0_4_;
          auVar98._0_4_ = fVar31 * fVar31;
          fVar40 = auVar93._4_4_;
          auVar98._4_4_ = fVar40 * fVar40;
          fVar59 = auVar93._8_4_;
          auVar98._8_4_ = fVar59 * fVar59;
          auVar98._12_4_ = auVar93._12_4_ * auVar93._12_4_;
          fVar61 = auVar87._0_4_;
          auVar115._0_4_ = fVar61 * fVar61;
          fVar64 = auVar87._4_4_;
          auVar115._4_4_ = fVar64 * fVar64;
          fVar138 = auVar87._8_4_;
          auVar115._8_4_ = fVar138 * fVar138;
          auVar115._12_4_ = auVar87._12_4_ * auVar87._12_4_;
          auVar93 = NEON_frsqrts(auVar98,auVar48,4);
          auVar82._12_4_ = 0x3f800000;
          auVar87 = NEON_frsqrts(auVar115,auVar54,4);
          auVar79 = NEON_ext(auVar82,auVar82,8,1);
          fVar117 = fVar117 * fVar31 * auVar93._0_4_;
          fVar65 = fVar65 * fVar40 * auVar93._4_4_;
          fVar67 = fVar67 * fVar59 * auVar93._8_4_;
          fVar66 = fVar66 * fVar61 * auVar87._0_4_;
          fVar51 = fVar51 * fVar64 * auVar87._4_4_;
          fVar62 = fVar62 * fVar138 * auVar87._8_4_;
          auVar75._0_4_ = (float)uStack_d0 * fVar117;
          auVar75._4_4_ = uStack_d0._4_4_ * fVar65;
          auVar75._8_4_ = (float)uStack_c8 * fVar67;
          auVar90._0_4_ = (float)uStack_d0 * fVar66;
          auVar90._4_4_ = uStack_d0._4_4_ * fVar51;
          auVar90._8_4_ = (float)uStack_c8 * fVar62;
          auVar75._12_4_ = 0;
          auVar99._0_4_ = (float)uStack_e0 * fVar117;
          auVar99._4_4_ = uStack_e0._4_4_ * fVar65;
          auVar99._8_4_ = (float)uStack_d8 * fVar67;
          auVar90._12_4_ = 0;
          auVar87 = NEON_ext(auVar75,auVar75,8,1);
          auVar105._0_4_ = (float)uStack_e0 * fVar66;
          auVar105._4_4_ = uStack_e0._4_4_ * fVar51;
          auVar105._8_4_ = (float)uStack_d8 * fVar62;
          auVar99._12_4_ = 0;
          auVar96 = NEON_ext(auVar90,auVar90,8,1);
          auVar111._0_4_ = (float)uStack_f0 * fVar117;
          auVar111._4_4_ = uStack_f0._4_4_ * fVar65;
          auVar111._8_4_ = (float)uStack_e8 * fVar67;
          auVar105._12_4_ = 0;
          auVar103 = NEON_ext(auVar99,auVar99,8,1);
          auVar116._0_4_ = (float)uStack_f0 * fVar66;
          auVar116._4_4_ = uStack_f0._4_4_ * fVar51;
          auVar116._8_4_ = (float)uStack_e8 * fVar62;
          auVar111._12_4_ = 0;
          auVar125 = NEON_ext(auVar105,auVar105,8,1);
          auVar127._0_4_ = (float)uStack_100 * fVar117;
          auVar127._4_4_ = uStack_100._4_4_ * fVar65;
          auVar127._8_4_ = (float)uStack_f8 * fVar67;
          auVar116._12_4_ = 0;
          auVar72 = NEON_ext(auVar111,auVar111,8,1);
          fVar31 = auVar82._0_4_ * auVar82._0_4_ + auVar79._0_4_ * auVar79._0_4_ +
                   auVar82._4_4_ * auVar82._4_4_ + 0.0;
          auVar131._0_4_ = (float)uStack_100 * fVar66;
          auVar131._4_4_ = uStack_100._4_4_ * fVar51;
          auVar131._8_4_ = (float)uStack_f8 * fVar62;
          auVar127._12_4_ = 0;
          auVar79 = NEON_ext(auVar116,auVar116,8,1);
          auVar57._4_4_ = fVar31;
          auVar57._0_4_ = fVar31;
          auVar57._8_4_ = fVar31;
          auVar57._12_4_ = fVar31;
          auVar131._12_4_ = 0;
          auVar86 = NEON_ext(auVar127,auVar127,8,1);
          auVar93 = NEON_frsqrte(auVar57,4);
          auVar143 = NEON_ext(auVar131,auVar131,8,1);
          fVar31 = auVar93._0_4_;
          auVar137._0_4_ = fVar31 * fVar31;
          fVar40 = auVar93._4_4_;
          auVar137._4_4_ = fVar40 * fVar40;
          fVar59 = auVar93._8_4_;
          auVar137._8_4_ = fVar59 * fVar59;
          auVar137._12_4_ = auVar93._12_4_ * auVar93._12_4_;
          auVar93 = NEON_frsqrts(auVar137,auVar57,4);
          uVar73 = NEON_rev64(CONCAT44(auVar87._0_4_ + auVar87._4_4_,auVar75._0_4_ + auVar75._4_4_),
                              4);
          uVar80 = NEON_rev64(CONCAT44(auVar96._0_4_ + auVar96._4_4_,auVar90._0_4_ + auVar90._4_4_),
                              4);
          uVar88 = NEON_rev64(CONCAT44(auVar103._0_4_ + auVar103._4_4_,auVar99._0_4_ + auVar99._4_4_
                                      ),4);
          uVar95 = NEON_rev64(CONCAT44(auVar125._0_4_ + auVar125._4_4_,
                                       auVar105._0_4_ + auVar105._4_4_),4);
          uVar102 = NEON_rev64(CONCAT44(auVar72._0_4_ + auVar72._4_4_,
                                        auVar111._0_4_ + auVar111._4_4_),4);
          uVar108 = NEON_rev64(CONCAT44(auVar79._0_4_ + auVar79._4_4_,
                                        auVar116._0_4_ + auVar116._4_4_),4);
          fVar31 = auVar82._0_4_ * fVar31 * auVar93._0_4_;
          fVar40 = auVar82._4_4_ * fVar40 * auVar93._4_4_;
          fVar59 = auVar82._8_4_ * fVar59 * auVar93._8_4_;
          uVar114 = NEON_rev64(CONCAT44(auVar86._0_4_ + auVar86._4_4_,
                                        auVar127._0_4_ + auVar127._4_4_),4);
          uVar119 = NEON_rev64(CONCAT44(auVar143._0_4_ + auVar143._4_4_,
                                        auVar131._0_4_ + auVar131._4_4_),4);
          auVar76._0_4_ = (float)uStack_d0 * fVar31;
          auVar76._4_4_ = uStack_d0._4_4_ * fVar40;
          auVar76._8_4_ = (float)uStack_c8 * fVar59;
          auVar83._0_4_ = (float)uStack_e0 * fVar31;
          auVar83._4_4_ = uStack_e0._4_4_ * fVar40;
          auVar83._8_4_ = (float)uStack_d8 * fVar59;
          auVar76._12_4_ = 0;
          auVar100._0_4_ = (float)uStack_f0 * fVar31;
          auVar100._4_4_ = uStack_f0._4_4_ * fVar40;
          auVar100._8_4_ = (float)uStack_e8 * fVar59;
          auVar83._12_4_ = 0;
          auVar93 = NEON_ext(auVar76,auVar76,8,1);
          auVar112._0_4_ = (float)uStack_100 * fVar31;
          auVar112._4_4_ = uStack_100._4_4_ * fVar40;
          auVar112._8_4_ = (float)uStack_f8 * fVar59;
          auVar100._12_4_ = 0;
          auVar87 = NEON_ext(auVar83,auVar83,8,1);
          auVar112._12_4_ = 0;
          auVar96 = NEON_ext(auVar100,auVar100,8,1);
          auVar103 = NEON_ext(auVar112,auVar112,8,1);
          uVar120 = NEON_rev64(CONCAT44(auVar93._0_4_ + auVar93._4_4_,auVar76._0_4_ + auVar76._4_4_)
                               ,4);
          uVar121 = NEON_rev64(CONCAT44(auVar87._0_4_ + auVar87._4_4_,auVar83._0_4_ + auVar83._4_4_)
                               ,4);
          uVar122 = NEON_rev64(CONCAT44(auVar96._0_4_ + auVar96._4_4_,
                                        auVar100._0_4_ + auVar100._4_4_),4);
          uVar123 = NEON_rev64(CONCAT44(auVar103._0_4_ + auVar103._4_4_,
                                        auVar112._0_4_ + auVar112._4_4_),4);
          auVar77._0_4_ = fVar32 * ABS(auVar99._0_4_ + auVar99._4_4_ + (float)uVar88);
          auVar77._4_4_ = fVar34 * ABS(auVar105._0_4_ + auVar105._4_4_ + (float)uVar95);
          auVar77._8_4_ = fVar36 * ABS(auVar83._0_4_ + auVar83._4_4_ + (float)uVar121);
          auVar70._0_4_ = fVar32 * ABS(auVar75._0_4_ + auVar75._4_4_ + (float)uVar73);
          auVar70._4_4_ = fVar34 * ABS(auVar90._0_4_ + auVar90._4_4_ + (float)uVar80);
          auVar70._8_4_ = fVar36 * ABS(auVar76._0_4_ + auVar76._4_4_ + (float)uVar120);
          auVar77._12_4_ = 0;
          auVar84._0_4_ = fVar32 * ABS(auVar111._0_4_ + auVar111._4_4_ + (float)uVar102);
          auVar84._4_4_ = fVar34 * ABS(auVar116._0_4_ + auVar116._4_4_ + (float)uVar108);
          auVar84._8_4_ = fVar36 * ABS(auVar100._0_4_ + auVar100._4_4_ + (float)uVar122);
          auVar91._0_4_ = fVar32 * ABS(auVar127._0_4_ + auVar127._4_4_ + (float)uVar114);
          auVar91._4_4_ = fVar34 * ABS(auVar131._0_4_ + auVar131._4_4_ + (float)uVar119);
          auVar91._8_4_ = fVar36 * ABS(auVar112._0_4_ + auVar112._4_4_ + (float)uVar123);
          auVar70._12_4_ = 0;
          auVar87 = NEON_ext(auVar77,auVar77,8,1);
          auVar84._12_4_ = 0;
          auVar91._12_4_ = 0;
          auVar93 = NEON_ext(auVar70,auVar70,8,1);
          auVar96 = NEON_ext(auVar84,auVar84,8,1);
          auVar103 = NEON_ext(auVar91,auVar91,8,1);
          uVar80 = NEON_rev64(CONCAT44(auVar87._0_4_ + auVar87._4_4_,auVar77._0_4_ + auVar77._4_4_),
                              4);
          uVar73 = NEON_rev64(CONCAT44(auVar93._0_4_ + auVar93._4_4_,auVar70._0_4_ + auVar70._4_4_),
                              4);
          uVar88 = NEON_rev64(CONCAT44(auVar96._0_4_ + auVar96._4_4_,auVar84._0_4_ + auVar84._4_4_),
                              4);
          uVar95 = NEON_rev64(CONCAT44(auVar103._0_4_ + auVar103._4_4_,auVar91._0_4_ + auVar91._4_4_
                                      ),4);
          if (0.0 <= auVar91._0_4_ + auVar91._4_4_ + (float)uVar95 +
                     ((auVar136._0_4_ + auVar136._4_4_ + (float)uVar134) -
                     (auVar74._0_4_ + auVar74._4_4_ + (float)uVar132)) &&
              (0.0 <= auVar84._0_4_ + auVar84._4_4_ + (float)uVar88 +
                      ((auVar126._0_4_ + auVar126._4_4_ + (float)uVar107) -
                      (auVar69._0_4_ + auVar69._4_4_ + (float)uVar128)) &&
              (0.0 <= auVar70._0_4_ + auVar70._4_4_ + (float)uVar73 +
                      ((auVar110._0_4_ + auVar110._4_4_ + (float)uVar94) -
                      (auVar56._0_4_ + auVar56._4_4_ + (float)uVar68)) &&
              0.0 <= auVar77._0_4_ + auVar77._4_4_ + (float)uVar80 +
                     ((auVar130._0_4_ + auVar130._4_4_ + (float)uVar133) -
                     (fVar60 + fVar63 + (float)uVar118))))) {
            fVar61 = (float)uStack_140 * fVar117;
            fVar64 = uStack_140._4_4_ * fVar65;
            auVar71._0_4_ = (float)uStack_140 * fVar66;
            auVar71._4_4_ = uStack_140._4_4_ * fVar51;
            auVar71._8_4_ = (float)uStack_138 * fVar62;
            auVar78._0_4_ = (float)uStack_140 * fVar31;
            auVar78._4_4_ = uStack_140._4_4_ * fVar40;
            auVar78._8_4_ = (float)uStack_138 * fVar59;
            auVar85._0_4_ = (float)uStack_140 * (float)uStack_120;
            auVar85._4_4_ = uStack_140._4_4_ * uStack_120._4_4_;
            auVar85._8_4_ = (float)uStack_138 * (float)uStack_118;
            auVar92._0_4_ = (float)uStack_140 * fVar43;
            auVar92._4_4_ = uStack_140._4_4_ * fVar45;
            auVar92._8_4_ = (float)uStack_138 * fVar113;
            auVar55._0_4_ = (float)uStack_150 * fVar117;
            auVar55._4_4_ = uStack_150._4_4_ * fVar65;
            auVar55._8_4_ = (float)uStack_148 * fVar67;
            auVar49._0_4_ = (float)uStack_150 * fVar66;
            auVar49._4_4_ = uStack_150._4_4_ * fVar51;
            auVar49._8_4_ = (float)uStack_148 * fVar62;
            auVar58._0_4_ = (float)uStack_150 * fVar31;
            auVar58._4_4_ = uStack_150._4_4_ * fVar40;
            auVar58._8_4_ = (float)uStack_148 * fVar59;
            auVar101._0_4_ = (float)uStack_150 * (float)uStack_130;
            auVar101._4_4_ = uStack_150._4_4_ * uStack_130._4_4_;
            auVar101._8_4_ = (float)uStack_148 * (float)uStack_128;
            fVar43 = (float)uStack_150 * fVar43;
            fVar45 = uStack_150._4_4_ * fVar45;
            auVar71._12_4_ = 0;
            auVar10._4_4_ = fVar64;
            auVar10._0_4_ = fVar61;
            auVar10._8_4_ = (float)uStack_138 * fVar67;
            auVar10._12_4_ = 0;
            auVar11._4_4_ = fVar64;
            auVar11._0_4_ = fVar61;
            auVar11._8_4_ = (float)uStack_138 * fVar67;
            auVar11._12_4_ = 0;
            auVar93 = NEON_ext(auVar10,auVar11,8,1);
            auVar78._12_4_ = 0;
            auVar87 = NEON_ext(auVar71,auVar71,8,1);
            auVar85._12_4_ = 0;
            auVar96 = NEON_ext(auVar78,auVar78,8,1);
            auVar92._12_4_ = 0;
            auVar103 = NEON_ext(auVar85,auVar85,8,1);
            auVar55._12_4_ = 0;
            auVar125 = NEON_ext(auVar92,auVar92,8,1);
            auVar49._12_4_ = 0;
            auVar72 = NEON_ext(auVar55,auVar55,8,1);
            auVar58._12_4_ = 0;
            auVar79 = NEON_ext(auVar49,auVar49,8,1);
            auVar101._12_4_ = 0;
            auVar86 = NEON_ext(auVar58,auVar58,8,1);
            auVar143 = NEON_ext(auVar101,auVar101,8,1);
            auVar8._4_4_ = fVar45;
            auVar8._0_4_ = fVar43;
            auVar8._8_4_ = (float)uStack_148 * fVar113;
            auVar8._12_4_ = 0;
            auVar9._4_4_ = fVar45;
            auVar9._0_4_ = fVar43;
            auVar9._8_4_ = (float)uStack_148 * fVar113;
            auVar9._12_4_ = 0;
            auVar106 = NEON_ext(auVar8,auVar9,8,1);
            uVar68 = NEON_rev64(CONCAT44(auVar93._0_4_ + auVar93._4_4_,fVar61 + fVar64),4);
            uVar73 = NEON_rev64(CONCAT44(auVar87._0_4_ + auVar87._4_4_,auVar71._0_4_ + auVar71._4_4_
                                        ),4);
            uVar80 = NEON_rev64(CONCAT44(auVar96._0_4_ + auVar96._4_4_,auVar78._0_4_ + auVar78._4_4_
                                        ),4);
            uVar88 = NEON_rev64(CONCAT44(auVar72._0_4_ + auVar72._4_4_,auVar55._0_4_ + auVar55._4_4_
                                        ),4);
            uVar94 = NEON_rev64(CONCAT44(auVar79._0_4_ + auVar79._4_4_,auVar49._0_4_ + auVar49._4_4_
                                        ),4);
            uVar95 = NEON_rev64(CONCAT44(auVar86._0_4_ + auVar86._4_4_,auVar58._0_4_ + auVar58._4_4_
                                        ),4);
            auVar50._0_4_ = fVar32 * ABS(fVar61 + fVar64 + (float)uVar68);
            auVar50._4_4_ = fVar34 * ABS(auVar71._0_4_ + auVar71._4_4_ + (float)uVar73);
            auVar50._8_4_ = fVar36 * ABS(auVar78._0_4_ + auVar78._4_4_ + (float)uVar80);
            fVar32 = fVar32 * ABS(auVar55._0_4_ + auVar55._4_4_ + (float)uVar88);
            fVar34 = fVar34 * ABS(auVar49._0_4_ + auVar49._4_4_ + (float)uVar94);
            fVar36 = fVar36 * ABS(auVar58._0_4_ + auVar58._4_4_ + (float)uVar95);
            uVar73 = NEON_rev64(CONCAT44(auVar143._0_4_ + auVar143._4_4_,
                                         auVar101._0_4_ + auVar101._4_4_),4);
            uVar80 = NEON_rev64(CONCAT44(auVar106._0_4_ + auVar106._4_4_,fVar43 + fVar45),4);
            auVar50._12_4_ = 0;
            auVar6._4_4_ = fVar34;
            auVar6._0_4_ = fVar32;
            auVar6._8_4_ = fVar36;
            auVar6._12_4_ = 0;
            auVar7._4_4_ = fVar34;
            auVar7._0_4_ = fVar32;
            auVar7._8_4_ = fVar36;
            auVar7._12_4_ = 0;
            auVar87 = NEON_ext(auVar6,auVar7,8,1);
            uVar88 = NEON_rev64(CONCAT44(auVar125._0_4_ + auVar125._4_4_,
                                         auVar92._0_4_ + auVar92._4_4_),4);
            auVar93 = NEON_ext(auVar50,auVar50,8,1);
            uVar94 = NEON_rev64(CONCAT44(auVar103._0_4_ + auVar103._4_4_,
                                         auVar85._0_4_ + auVar85._4_4_),4);
            uVar68 = NEON_rev64(CONCAT44(auVar87._0_4_ + auVar87._4_4_,fVar32 + fVar34),4);
            fVar40 = (fVar43 + fVar45 + (float)uVar80) -
                     (auVar101._0_4_ + auVar101._4_4_ + (float)uVar73);
            uVar73 = NEON_rev64(CONCAT44(auVar93._0_4_ + auVar93._4_4_,auVar50._0_4_ + auVar50._4_4_
                                        ),4);
            fVar31 = fVar32 + fVar34 + (float)uVar68;
            if (0.0 <= fVar31 + fVar40 &&
                (0.0 <= fVar31 + fVar40 &&
                (0.0 <= fVar31 + fVar40 &&
                0.0 <= auVar50._0_4_ + auVar50._4_4_ + (float)uVar73 +
                       ((auVar92._0_4_ + auVar92._4_4_ + (float)uVar88) -
                       (auVar85._0_4_ + auVar85._4_4_ + (float)uVar94))))) goto code_r0x02266354;
          }
          goto code_r0x022666dc;
        }
code_r0x02266354:
        piVar3 = (int *)((long)plVar29 + 0x1ac);
        do {
          cVar5 = '\x01';
          bVar19 = (bool)ExclusiveMonitorPass(piVar3,0x10);
          if (bVar19) {
            *piVar3 = *piVar3 + 1;
            cVar5 = ExclusiveMonitorsStatus();
          }
        } while (cVar5 != '\0');
        puVar1 = (ulong *)(param_8 + (long)iVar4 * 8);
        do {
          cVar5 = '\x01';
          bVar19 = (bool)ExclusiveMonitorPass(puVar1,0x10);
          if (bVar19) {
            *puVar1 = *puVar1 | 1L << iVar20;
            cVar5 = ExclusiveMonitorsStatus();
          }
        } while (cVar5 != '\0');
      }
    } while ((int)uVar27 < param_7);
  }
  return;
}

// ==== Aska::ObjectManager::OcclusionCulling(Aska::Camera*, int, int, bool, Aska::RenderableObject**, int, int, unsigned long*)
// vaddr 0x2166724 | ghidra 0x2266724 | size 3016 | symbol _ZN4Aska13ObjectManager16OcclusionCullingEPNS_6CameraEiibPPNS_16RenderableObjectEiiPm | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska13ObjectManager16OcclusionCullingEPNS_6CameraEiibPPNS_16RenderableObjectEiiPm
               (long param_1,long param_2,int param_3,undefined8 param_4,undefined8 param_5,
               long param_6,int param_7,int param_8,long param_9)

{
  long lVar1;
  ulong *puVar2;
  uint uVar3;
  uint uVar4;
  char cVar5;
  bool bVar6;
  int iVar7;
  undefined1 auVar8 [16];
  undefined1 auVar9 [16];
  undefined1 auVar10 [16];
  undefined1 auVar11 [16];
  undefined1 auVar12 [16];
  undefined1 auVar13 [16];
  undefined1 auVar14 [16];
  undefined1 auVar15 [16];
  undefined1 auVar16 [16];
  undefined1 auVar17 [16];
  undefined1 auVar18 [16];
  undefined1 auVar19 [16];
  undefined1 auVar20 [16];
  undefined1 auVar21 [16];
  undefined1 auVar22 [16];
  undefined1 auVar23 [16];
  undefined1 auVar24 [16];
  undefined1 auVar25 [16];
  undefined1 auVar26 [16];
  undefined1 auVar27 [16];
  undefined1 auVar28 [16];
  undefined1 auVar29 [16];
  undefined1 auVar30 [16];
  long lVar31;
  float fVar32;
  float fVar33;
  float fVar34;
  float fVar35;
  float fVar36;
  float fVar37;
  float fVar38;
  float fVar39;
  float fVar40;
  float fVar41;
  float fVar42;
  float fVar43;
  float fVar44;
  float fVar45;
  float fVar46;
  undefined8 uVar47;
  undefined8 uVar48;
  undefined8 uVar49;
  undefined8 uVar50;
  undefined8 uVar51;
  undefined8 uVar52;
  long *plVar53;
  int iVar54;
  int iVar55;
  int iVar56;
  long lVar57;
  long lVar58;
  float *pfVar59;
  long lVar60;
  long lVar61;
  undefined8 *puVar62;
  long lVar63;
  long lVar64;
  long lVar65;
  long lVar66;
  undefined8 *puVar67;
  long lVar68;
  long lVar69;
  undefined8 *puVar70;
  uint uVar71;
  long *plVar72;
  ulong uVar73;
  ulong uVar74;
  ulong uVar75;
  long lVar76;
  long lVar77;
  long lVar84;
  undefined1 auVar78 [16];
  undefined1 auVar79 [16];
  undefined1 auVar80 [16];
  undefined1 auVar81 [16];
  undefined1 auVar82 [16];
  undefined1 auVar83 [16];
  long lVar85;
  float fVar86;
  float fVar87;
  float fVar88;
  float fVar89;
  float fVar90;
  float fVar91;
  float fVar92;
  float fVar93;
  float fVar94;
  float fVar95;
  float fVar96;
  undefined1 auVar97 [16];
  undefined1 auVar98 [16];
  undefined1 auVar99 [16];
  undefined1 auVar100 [16];
  undefined1 auVar101 [16];
  float fVar102;
  undefined1 auVar103 [16];
  undefined1 auVar104 [16];
  undefined1 auVar105 [16];
  undefined1 auVar106 [16];
  undefined1 auVar107 [16];
  undefined8 uVar108;
  undefined1 auVar109 [16];
  undefined1 auVar110 [16];
  undefined8 uVar111;
  undefined1 auVar112 [16];
  undefined1 auVar113 [16];
  undefined1 auVar114 [16];
  undefined1 auVar115 [16];
  float fVar116;
  float fVar117;
  undefined8 uVar118;
  float fVar122;
  float fVar123;
  undefined1 auVar120 [16];
  undefined8 uVar119;
  undefined1 auVar121 [16];
  float fVar124;
  float fVar125;
  float fVar126;
  float fVar127;
  float fVar128;
  float fVar129;
  float fVar130;
  float fVar131;
  float fVar132;
  float fVar133;
  float fVar134;
  float fVar135;
  float fVar136;
  float fVar137;
  float fVar138;
  float fVar139;
  float fVar140;
  float fVar141;
  float fVar142;
  float fVar143;
  float fVar144;
  float fVar145;
  float fVar146;
  float fVar147;
  float fVar148;
  undefined8 uVar149;
  undefined1 auVar151 [16];
  undefined1 auVar152 [16];
  undefined1 auVar153 [16];
  undefined1 auVar154 [16];
  undefined8 uVar150;
  undefined1 auVar155 [16];
  float fVar156;
  undefined8 uVar157;
  undefined8 uVar158;
  undefined8 uVar159;
  undefined8 uVar160;
  undefined1 auVar161 [16];
  undefined8 uVar162;
  undefined1 auVar164 [16];
  undefined1 auVar165 [16];
  undefined8 uVar163;
  undefined1 auVar166 [16];
  float fVar167;
  undefined8 uVar168;
  undefined1 auVar169 [16];
  undefined1 auVar170 [16];
  undefined1 auVar171 [16];
  undefined1 auVar172 [16];
  float fVar173;
  undefined8 uVar174;
  undefined8 uVar175;
  undefined8 uVar176;
  undefined8 uVar177;
  undefined8 uVar178;
  undefined1 auVar179 [16];
  undefined1 auVar180 [16];
  undefined1 auVar181 [16];
  undefined1 auVar182 [16];
  undefined1 auVar183 [16];
  float fVar184;
  undefined1 auVar185 [16];
  undefined1 auVar186 [16];
  undefined1 auVar187 [16];
  undefined1 auVar188 [16];
  float fVar189;
  undefined8 uVar190;
  undefined1 auVar192 [16];
  undefined1 auVar193 [16];
  undefined1 auVar194 [16];
  undefined8 uVar191;
  undefined1 auVar195 [16];
  undefined1 auVar196 [16];
  undefined1 auVar197 [16];
  undefined1 auVar198 [16];
  undefined1 auVar199 [16];
  undefined1 auVar200 [16];
  undefined1 auVar201 [16];
  float fStack_220;
  float fStack_21c;
  float fStack_210;
  float fStack_20c;
  float fStack_b0;
  float fStack_ac;
  float fStack_a8;
  float fStack_a4;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  float fStack_94;
  float fStack_90;
  float fStack_8c;
  float fStack_88;
  float fStack_84;
  
  lVar58 = _UNK_029cc838;
  lVar57 = _UNK_029cc830;
  lVar60 = *(long *)PTR__ZN4Aska6Global18m_pOccluderManagerE_02cbbc98;
  uVar3 = *(uint *)(lVar60 + 0x5c0);
  if (0 < (int)uVar3) {
    lVar68 = *(long *)(param_1 + 0x1ac0);
    lVar69 = (long)param_7;
    uVar74 = 0;
    uVar71 = (1 - param_7) + param_8;
    lVar1 = lVar68 + (long)param_7 * 4;
    lVar84 = UNK_02866310._8_8_;
    lVar76 = (long)UNK_02866310;
    do {
      lVar61 = *(long *)(lVar60 + uVar74 * 8 + 0x1c0);
      if (uVar74 == 0) {
        lVar63 = *(long *)(param_1 + 0x1ab0);
        if (0 < (int)uVar71) {
          if (uVar71 < 8) {
            lVar65 = 0;
          }
          else {
            lVar65 = (ulong)uVar71 - (ulong)(uVar71 & 7);
            lVar66 = lVar65;
            puVar67 = (undefined8 *)(lVar68 + lVar69 * 4 + 0x10);
            lVar64 = lVar57;
            lVar31 = lVar58;
            lVar77 = lVar76;
            lVar85 = lVar84;
            if (lVar65 != 0) {
              do {
                iVar7 = (int)lVar77 + param_7;
                iVar54 = (int)lVar85 + param_7;
                iVar55 = (int)lVar64 + param_7;
                iVar56 = (int)lVar31 + param_7;
                auVar78._0_8_ = CONCAT44(iVar54,iVar7);
                auVar78._8_4_ = iVar55;
                auVar78._12_4_ = iVar56;
                auVar79._0_8_ = CONCAT44(iVar54 + 4,iVar7 + 4);
                auVar79._8_4_ = iVar55 + 4;
                auVar79._12_4_ = iVar56 + 4;
                lVar66 = lVar66 + -8;
                puVar67[-1] = auVar78._8_8_;
                puVar67[-2] = auVar78._0_8_;
                puVar67[1] = auVar79._8_8_;
                *puVar67 = auVar79._0_8_;
                puVar67 = puVar67 + 4;
                lVar64 = lVar64 + 8;
                lVar31 = lVar31 + 8;
                lVar77 = lVar77 + 8;
                lVar85 = lVar85 + 8;
              } while (lVar66 != 0);
              if ((uVar71 & 7) == 0) goto code_r0x022672a0;
            }
          }
          lVar64 = (ulong)uVar71 - lVar65;
          lVar65 = lVar69 + lVar65;
          do {
            *(int *)(lVar68 + lVar65 * 4) = (int)lVar65;
            lVar64 = lVar64 + -1;
            lVar65 = lVar65 + 1;
          } while (lVar64 != 0);
        }
code_r0x022672a0:
        lVar65 = param_6;
        if (0 < (int)uVar71) goto code_r0x02266854;
code_r0x022672ac:
        uVar71 = 0;
      }
      else {
        plVar72 = (long *)(param_1 + 0x1ab8);
        plVar53 = (long *)(param_1 + 0x1ab0);
        if ((uVar74 & 1) != 0) {
          plVar72 = (long *)(param_1 + 0x1ab0);
          plVar53 = (long *)(param_1 + 0x1ab8);
        }
        lVar63 = *plVar53;
        lVar65 = *plVar72;
        if ((int)uVar71 < 1) goto code_r0x022672ac;
code_r0x02266854:
        fVar32 = *(float *)(lVar61 + 0x200);
        fVar33 = *(float *)(lVar61 + 0x204);
        fVar34 = *(float *)(lVar61 + 0x208);
        fVar93 = (float)*(undefined8 *)(lVar61 + 0x218);
        fVar86 = (float)*(undefined8 *)(lVar61 + 0x210);
        fVar89 = (float)((ulong)*(undefined8 *)(lVar61 + 0x210) >> 0x20);
        fVar35 = *(float *)(lVar61 + 0x220);
        fVar36 = *(float *)(lVar61 + 0x224);
        fVar37 = *(float *)(lVar61 + 0x228);
        fVar38 = *(float *)(lVar61 + 0x230);
        fVar39 = *(float *)(lVar61 + 0x234);
        fVar40 = *(float *)(lVar61 + 0x238);
        fVar41 = *(float *)(lVar61 + 0x240);
        fVar42 = *(float *)(lVar61 + 0x244);
        fVar43 = *(float *)(lVar61 + 0x248);
        fVar44 = *(float *)(lVar61 + 0x250);
        fVar45 = *(float *)(lVar61 + 0x254);
        fVar46 = *(float *)(lVar61 + 600);
        uVar47 = *(undefined8 *)(param_2 + 0x130);
        uVar48 = *(undefined8 *)(param_2 + 0x138);
        auVar78 = *(undefined1 (*) [16])(lVar61 + 0x260);
        fVar132 = (float)*(undefined8 *)(lVar61 + 0x278);
        fVar124 = (float)*(undefined8 *)(lVar61 + 0x270);
        fVar128 = (float)((ulong)*(undefined8 *)(lVar61 + 0x270) >> 0x20);
        fVar138 = (float)*(undefined8 *)(lVar61 + 0x288);
        fVar133 = (float)*(undefined8 *)(lVar61 + 0x280);
        fVar136 = (float)((ulong)*(undefined8 *)(lVar61 + 0x280) >> 0x20);
        fVar145 = (float)*(undefined8 *)(lVar61 + 0x298);
        fVar139 = (float)*(undefined8 *)(lVar61 + 0x290);
        fVar142 = (float)((ulong)*(undefined8 *)(lVar61 + 0x290) >> 0x20);
        uVar75 = 0;
        uVar49 = *(undefined8 *)(param_2 + 0x140);
        uVar50 = *(undefined8 *)(param_2 + 0x148);
        uVar73 = (ulong)uVar71;
        uVar71 = 0;
        uVar51 = *(undefined8 *)(param_2 + 0x150);
        uVar52 = *(undefined8 *)(param_2 + 0x158);
        fVar147 = *(float *)(lVar61 + 0x1a4);
        fVar116 = auVar78._0_4_;
        fVar87 = fVar86 * fVar116;
        fVar122 = auVar78._4_4_;
        fVar90 = fVar89 * fVar122;
        fVar123 = auVar78._8_4_;
        fVar94 = fVar93 * fVar123;
        auVar112._0_4_ = fVar32 * fVar44;
        auVar112._4_4_ = fVar33 * fVar45;
        auVar112._8_4_ = fVar34 * fVar46;
        auVar97._0_4_ = fVar35 * fVar124;
        auVar97._4_4_ = fVar36 * fVar128;
        auVar97._8_4_ = fVar37 * fVar132;
        auVar103._0_4_ = fVar38 * fVar133;
        auVar103._4_4_ = fVar39 * fVar136;
        auVar103._8_4_ = fVar40 * fVar138;
        auVar109._0_4_ = fVar41 * fVar139;
        auVar109._4_4_ = fVar42 * fVar142;
        auVar109._8_4_ = fVar43 * fVar145;
        auVar112._12_4_ = 0;
        auVar97._12_4_ = 0;
        auVar103._12_4_ = 0;
        auVar109._12_4_ = 0;
        auVar78 = NEON_ext(auVar112,auVar112,8,1);
        auVar80._4_4_ = fVar90;
        auVar80._0_4_ = fVar87;
        auVar80._8_4_ = fVar94;
        auVar80._12_4_ = 0;
        auVar81._4_4_ = fVar90;
        auVar81._0_4_ = fVar87;
        auVar81._8_4_ = fVar94;
        auVar81._12_4_ = 0;
        auVar79 = NEON_ext(auVar80,auVar81,8,1);
        auVar80 = NEON_ext(auVar97,auVar97,8,1);
        auVar81 = NEON_ext(auVar103,auVar103,8,1);
        puVar67 = (undefined8 *)(lVar63 + lVar69 * 8);
        auVar82 = NEON_ext(auVar109,auVar109,8,1);
        puVar70 = (undefined8 *)(lVar65 + lVar69 * 8);
        do {
          uVar4 = *(uint *)(lVar1 + uVar75 * 4);
          plVar72 = (long *)*puVar70;
          iVar7 = (uVar4 & 0x1f) << 1;
          if (((plVar72[0x34] != 0) || ((*(uint *)(plVar72 + 0x33) & 0x100002) != 0)) ||
             ((param_3 < 1 &&
              (*(float *)(*(long *)(param_1 + (long)param_3 * 8 + 0x3f48) +
                         (ulong)*(ushort *)(plVar72 + 0x37) * 8) <= fVar147)))) {
code_r0x022671c8:
            if (uVar74 == uVar3 - 1) {
              puVar2 = (ulong *)(param_9 + (long)((int)uVar4 >> 5) * 8);
              do {
                cVar5 = '\x01';
                bVar6 = (bool)ExclusiveMonitorPass(puVar2,0x10);
                if (bVar6) {
                  *puVar2 = *puVar2 | 1L << iVar7;
                  cVar5 = ExclusiveMonitorsStatus();
                }
              } while (cVar5 != '\0');
            }
            else {
              *(uint *)(lVar1 + (long)(int)uVar71 * 4) = uVar4;
              *puVar67 = plVar72;
              uVar71 = uVar71 + 1;
              puVar67 = puVar67 + 1;
            }
          }
          else {
            if ((*(byte *)(plVar72 + 0x25) >> 4 & 1) == 0) {
              (**(code **)(*plVar72 + 600))(plVar72,0);
            }
            fVar95 = (float)plVar72[0x5b];
            fVar156 = (float)((ulong)plVar72[0x5b] >> 0x20);
            fVar94 = (float)plVar72[0x5a];
            fVar91 = (float)((ulong)plVar72[0x5a] >> 0x20);
            fStack_a0 = (float)uVar49;
            fStack_9c = (float)((ulong)uVar49 >> 0x20);
            fStack_98 = (float)uVar50;
            fStack_94 = (float)((ulong)uVar50 >> 0x20);
            fStack_90 = (float)uVar47;
            fStack_8c = (float)((ulong)uVar47 >> 0x20);
            fStack_88 = (float)uVar48;
            fStack_84 = (float)((ulong)uVar48 >> 0x20);
            fStack_b0 = (float)uVar51;
            fStack_ac = (float)((ulong)uVar51 >> 0x20);
            fStack_a8 = (float)uVar52;
            fStack_a4 = (float)((ulong)uVar52 >> 0x20);
            auVar113._0_4_ = fStack_90 * fVar94;
            auVar113._4_4_ = fStack_8c * fVar91;
            auVar113._8_4_ = fStack_88 * fVar95;
            auVar113._12_4_ = fStack_84 * 1.0;
            auVar114._0_4_ = fStack_a0 * fVar94;
            auVar114._4_4_ = fStack_9c * fVar91;
            auVar114._8_4_ = fStack_98 * fVar95;
            auVar114._12_4_ = fStack_94 * 1.0;
            NEON_ext(auVar113,auVar113,8,1);
            auVar120._0_4_ = fStack_b0 * fVar94;
            auVar120._4_4_ = fStack_ac * fVar91;
            auVar120._8_4_ = fStack_a8 * fVar95;
            auVar120._12_4_ = fStack_a4 * 1.0;
            NEON_ext(auVar114,auVar114,8,1);
            auVar113 = NEON_ext(auVar120,auVar120,8,1);
            if (fVar156 + auVar113._0_4_ + auVar120._0_4_ + auVar113._4_4_ + auVar120._4_4_ <=
                fVar147) goto code_r0x022671c8;
            auVar181._0_4_ = fVar44 * (fVar94 - fVar32);
            auVar181._4_4_ = fVar45 * (fVar91 - fVar33);
            auVar181._8_4_ = fVar46 * (fVar95 - fVar34);
            auVar181._12_4_ = 0;
            auVar186._0_4_ = fVar116 * (fVar94 - fVar86);
            auVar186._4_4_ = fVar122 * (fVar91 - fVar89);
            auVar186._8_4_ = fVar123 * (fVar95 - fVar93);
            auVar186._12_4_ = 0;
            auVar113 = NEON_ext(auVar181,auVar181,8,1);
            auVar114 = NEON_ext(auVar186,auVar186,8,1);
            uVar108 = NEON_rev64(CONCAT44(auVar113._0_4_ + auVar113._4_4_,
                                          auVar181._0_4_ + auVar181._4_4_),4);
            uVar111 = NEON_rev64(CONCAT44(auVar114._0_4_ + auVar114._4_4_,
                                          auVar186._0_4_ + auVar186._4_4_),4);
            fVar96 = auVar181._0_4_ + auVar181._4_4_ + (float)uVar108;
            fVar102 = auVar186._0_4_ + auVar186._4_4_ + (float)uVar111;
            auVar193._0_4_ = fVar124 * (fVar94 - fVar35);
            auVar193._4_4_ = fVar128 * (fVar91 - fVar36);
            auVar193._8_4_ = fVar132 * (fVar95 - fVar37);
            auVar193._12_4_ = 0;
            auVar197._0_4_ = fVar133 * (fVar94 - fVar38);
            auVar197._4_4_ = fVar136 * (fVar91 - fVar39);
            auVar197._8_4_ = fVar138 * (fVar95 - fVar40);
            auVar197._12_4_ = 0;
            fVar94 = fVar139 * (fVar94 - fVar41);
            fVar91 = fVar142 * (fVar91 - fVar42);
            fVar95 = fVar145 * (fVar95 - fVar43);
            auVar113 = NEON_ext(auVar193,auVar193,8,1);
            auVar114 = NEON_ext(auVar197,auVar197,8,1);
            auVar170._4_4_ = fVar91;
            auVar170._0_4_ = fVar94;
            auVar170._8_4_ = fVar95;
            auVar170._12_4_ = 0;
            auVar180._4_4_ = fVar91;
            auVar180._0_4_ = fVar94;
            auVar180._8_4_ = fVar95;
            auVar180._12_4_ = 0;
            auVar120 = NEON_ext(auVar170,auVar180,8,1);
            uVar108 = NEON_rev64(CONCAT44(auVar113._0_4_ + auVar113._4_4_,
                                          auVar193._0_4_ + auVar193._4_4_),4);
            fVar95 = auVar193._0_4_ + auVar193._4_4_ + (float)uVar108;
            uVar111 = NEON_rev64(CONCAT44(auVar114._0_4_ + auVar114._4_4_,
                                          auVar197._0_4_ + auVar197._4_4_),4);
            uVar108 = NEON_rev64(CONCAT44(auVar120._0_4_ + auVar120._4_4_,fVar94 + fVar91),4);
            fVar117 = auVar197._0_4_ + auVar197._4_4_ + (float)uVar111;
            fVar94 = fVar94 + fVar91 + (float)uVar108;
            auVar198._4_4_ = fVar95;
            auVar198._0_4_ = fVar95;
            auVar198._8_4_ = fVar95;
            auVar198._12_4_ = fVar95;
            if (fVar102 - fVar156 < 0.0 ||
                (fVar96 - fVar156 < 0.0 || (fVar96 - fVar156 < 0.0 || fVar96 - fVar156 < 0.0))) {
code_r0x02266b7c:
              if (((0.0 <= fVar156 + fVar117 &&
                    (0.0 <= fVar156 + fVar95 &&
                    (0.0 <= fVar156 + fVar96 && 0.0 <= fVar156 + fVar102))) &&
                  (0.0 <= fVar156 + fVar94 &&
                   (0.0 <= fVar156 + fVar94 && (0.0 <= fVar156 + fVar94 && 0.0 <= fVar156 + fVar94))
                  )) && (pfVar59 = (float *)(**(code **)(*plVar72 + 0x150))(plVar72,0),
                        pfVar59 != (float *)0x0)) {
                fStack_220 = auVar79._0_4_;
                fStack_21c = auVar79._4_4_;
                fStack_210 = auVar78._0_4_;
                fStack_20c = auVar78._4_4_;
                puVar62 = (undefined8 *)plVar72[0x24];
                fVar94 = *pfVar59;
                fVar91 = pfVar59[1];
                fVar95 = pfVar59[2];
                fVar156 = pfVar59[3];
                auVar113 = *(undefined1 (*) [16])(pfVar59 + 4);
                fVar96 = pfVar59[8];
                fVar102 = pfVar59[9];
                fVar117 = pfVar59[10];
                fVar148 = pfVar59[0xb];
                fVar130 = (float)*(undefined8 *)(pfVar59 + 0xe);
                fVar131 = (float)((ulong)*(undefined8 *)(pfVar59 + 0xe) >> 0x20);
                fVar127 = (float)*(undefined8 *)(pfVar59 + 0xc);
                fVar129 = (float)((ulong)*(undefined8 *)(pfVar59 + 0xc) >> 0x20);
                uVar149 = NEON_rev64(CONCAT44(fStack_220 + fStack_21c,fVar87 + fVar90),4);
                uVar157 = NEON_rev64(CONCAT44(auVar80._0_4_ + auVar80._4_4_,
                                              auVar97._0_4_ + auVar97._4_4_),4);
                uVar118 = NEON_rev64(CONCAT44(fStack_210 + fStack_20c,
                                              auVar112._0_4_ + auVar112._4_4_),4);
                uVar162 = NEON_rev64(CONCAT44(auVar81._0_4_ + auVar81._4_4_,
                                              auVar103._0_4_ + auVar103._4_4_),4);
                fVar141 = (float)puVar62[1];
                fVar144 = (float)((ulong)puVar62[1] >> 0x20);
                fVar134 = (float)*puVar62;
                fVar137 = (float)((ulong)*puVar62 >> 0x20);
                fVar167 = (float)puVar62[3];
                fVar146 = (float)((ulong)puVar62[3] >> 0x20);
                fVar140 = (float)puVar62[2];
                fVar143 = (float)((ulong)puVar62[2] >> 0x20);
                fVar173 = *(float *)(puVar62 + 4);
                fVar184 = *(float *)((long)puVar62 + 0x24);
                fVar189 = *(float *)(puVar62 + 5);
                fVar135 = *(float *)((long)puVar62 + 0x2c);
                fVar88 = *(float *)(puVar62 + 6);
                fVar92 = *(float *)((long)puVar62 + 0x34);
                fVar125 = *(float *)(puVar62 + 7);
                fVar126 = *(float *)((long)puVar62 + 0x3c);
                auVar164._0_4_ = fVar134 * fVar94;
                auVar164._4_4_ = fVar137 * fVar91;
                auVar164._8_4_ = fVar141 * fVar95;
                auVar164._12_4_ = fVar144 * fVar156;
                auVar169._0_4_ = fVar140 * fVar94;
                auVar169._4_4_ = fVar143 * fVar91;
                auVar169._8_4_ = fVar167 * fVar95;
                auVar169._12_4_ = fVar146 * fVar156;
                auVar179._0_4_ = fVar173 * fVar94;
                auVar179._4_4_ = fVar184 * fVar91;
                auVar179._8_4_ = fVar189 * fVar95;
                auVar179._12_4_ = fVar135 * fVar156;
                auVar104._0_4_ = fVar88 * fVar94;
                auVar104._4_4_ = fVar92 * fVar91;
                auVar104._8_4_ = fVar125 * fVar95;
                auVar104._12_4_ = fVar126 * fVar156;
                auVar185._0_4_ = fVar134 * fVar96;
                auVar185._4_4_ = fVar137 * fVar102;
                auVar185._8_4_ = fVar141 * fVar117;
                auVar185._12_4_ = fVar144 * fVar148;
                auVar192._0_4_ = fVar140 * fVar96;
                auVar192._4_4_ = fVar143 * fVar102;
                auVar192._8_4_ = fVar167 * fVar117;
                auVar192._12_4_ = fVar146 * fVar148;
                auVar196._0_4_ = fVar173 * fVar96;
                auVar196._4_4_ = fVar184 * fVar102;
                auVar196._8_4_ = fVar189 * fVar117;
                auVar196._12_4_ = fVar135 * fVar148;
                auVar98._0_4_ = fVar88 * fVar96;
                auVar98._4_4_ = fVar92 * fVar102;
                auVar98._8_4_ = fVar125 * fVar117;
                auVar98._12_4_ = fVar126 * fVar148;
                fVar134 = fVar134 * fVar127;
                fVar137 = fVar137 * fVar129;
                fVar140 = fVar140 * fVar127;
                fVar143 = fVar143 * fVar129;
                auVar151._0_4_ = fVar173 * fVar127;
                auVar151._4_4_ = fVar184 * fVar129;
                auVar151._8_4_ = fVar189 * fVar130;
                auVar151._12_4_ = fVar135 * fVar131;
                fVar88 = fVar88 * fVar127;
                fVar92 = fVar92 * fVar129;
                auVar114 = NEON_ext(auVar164,auVar164,8,1);
                auVar120 = NEON_ext(auVar169,auVar169,8,1);
                auVar170 = NEON_ext(auVar179,auVar179,8,1);
                auVar180 = NEON_ext(auVar104,auVar104,8,1);
                auVar181 = NEON_ext(auVar185,auVar185,8,1);
                auVar186 = NEON_ext(auVar192,auVar192,8,1);
                auVar193 = NEON_ext(auVar196,auVar196,8,1);
                auVar197 = NEON_ext(auVar98,auVar98,8,1);
                auVar17._4_4_ = fVar137;
                auVar17._0_4_ = fVar134;
                auVar17._8_4_ = fVar141 * fVar130;
                auVar17._12_4_ = fVar144 * fVar131;
                auVar18._4_4_ = fVar137;
                auVar18._0_4_ = fVar134;
                auVar18._8_4_ = fVar141 * fVar130;
                auVar18._12_4_ = fVar144 * fVar131;
                auVar198 = NEON_ext(auVar17,auVar18,8,1);
                auVar25._4_4_ = fVar143;
                auVar25._0_4_ = fVar140;
                auVar25._8_4_ = fVar167 * fVar130;
                auVar25._12_4_ = fVar146 * fVar131;
                auVar26._4_4_ = fVar143;
                auVar26._0_4_ = fVar140;
                auVar26._8_4_ = fVar167 * fVar130;
                auVar26._12_4_ = fVar146 * fVar131;
                auVar199 = NEON_ext(auVar25,auVar26,8,1);
                auVar200 = NEON_ext(auVar151,auVar151,8,1);
                auVar201._4_4_ = fVar92;
                auVar201._0_4_ = fVar88;
                auVar201._8_4_ = fVar125 * fVar130;
                auVar201._12_4_ = fVar126 * fVar131;
                auVar8._4_4_ = fVar92;
                auVar8._0_4_ = fVar88;
                auVar8._8_4_ = fVar125 * fVar130;
                auVar8._12_4_ = fVar126 * fVar131;
                auVar201 = NEON_ext(auVar201,auVar8,8,1);
                uVar108 = NEON_rev64(CONCAT44(auVar114._0_4_ + auVar114._4_4_,
                                              auVar164._0_4_ + auVar164._4_4_),4);
                fVar156 = auVar164._0_4_ + auVar164._4_4_ + (float)uVar108;
                uVar108 = NEON_rev64(CONCAT44(auVar120._0_4_ + auVar120._4_4_,
                                              auVar169._0_4_ + auVar169._4_4_),4);
                fVar96 = auVar169._0_4_ + auVar169._4_4_ + (float)uVar108;
                uVar108 = NEON_rev64(CONCAT44(auVar170._0_4_ + auVar170._4_4_,
                                              auVar179._0_4_ + auVar179._4_4_),4);
                fVar167 = auVar179._0_4_ + auVar179._4_4_ + (float)uVar108;
                NEON_rev64(CONCAT44(auVar180._0_4_ + auVar180._4_4_,auVar104._0_4_ + auVar104._4_4_)
                           ,4);
                uVar108 = NEON_rev64(CONCAT44(auVar181._0_4_ + auVar181._4_4_,
                                              auVar185._0_4_ + auVar185._4_4_),4);
                fVar173 = auVar185._0_4_ + auVar185._4_4_ + (float)uVar108;
                uVar108 = NEON_rev64(CONCAT44(auVar186._0_4_ + auVar186._4_4_,
                                              auVar192._0_4_ + auVar192._4_4_),4);
                fVar184 = auVar192._0_4_ + auVar192._4_4_ + (float)uVar108;
                uVar108 = NEON_rev64(CONCAT44(auVar193._0_4_ + auVar193._4_4_,
                                              auVar196._0_4_ + auVar196._4_4_),4);
                fVar189 = auVar196._0_4_ + auVar196._4_4_ + (float)uVar108;
                uVar108 = NEON_rev64(CONCAT44(auVar197._0_4_ + auVar197._4_4_,
                                              auVar98._0_4_ + auVar98._4_4_),4);
                fVar94 = auVar98._0_4_ + auVar98._4_4_ + (float)uVar108;
                uVar108 = NEON_rev64(CONCAT44(auVar198._0_4_ + auVar198._4_4_,fVar134 + fVar137),4);
                fVar102 = fVar134 + fVar137 + (float)uVar108;
                uVar108 = NEON_rev64(CONCAT44(auVar199._0_4_ + auVar199._4_4_,fVar140 + fVar143),4);
                fVar117 = fVar140 + fVar143 + (float)uVar108;
                uVar108 = NEON_rev64(CONCAT44(auVar200._0_4_ + auVar200._4_4_,
                                              auVar151._0_4_ + auVar151._4_4_),4);
                fVar148 = auVar151._0_4_ + auVar151._4_4_ + (float)uVar108;
                uVar108 = NEON_rev64(CONCAT44(auVar201._0_4_ + auVar201._4_4_,fVar88 + fVar92),4);
                fVar91 = fVar88 + fVar92 + (float)uVar108;
                auVar99._0_4_ = fVar173 * fVar173;
                auVar99._4_4_ = fVar184 * fVar184;
                auVar99._8_4_ = fVar189 * fVar189;
                auVar99._12_4_ = fVar94 * fVar94;
                auVar152._0_4_ = fVar44 * fVar156;
                auVar152._4_4_ = fVar45 * fVar96;
                auVar152._8_4_ = fVar46 * fVar167;
                auVar105._0_4_ = fVar102 * fVar102;
                auVar105._4_4_ = fVar117 * fVar117;
                auVar105._8_4_ = fVar148 * fVar148;
                auVar105._12_4_ = fVar91 * fVar91;
                auVar187._0_4_ = fVar116 * fVar156;
                auVar187._4_4_ = fVar122 * fVar96;
                auVar187._8_4_ = fVar123 * fVar167;
                auVar181 = NEON_ext(auVar99,auVar99,8,1);
                auVar152._12_4_ = 0;
                auVar182._0_4_ = fVar124 * fVar156;
                auVar182._4_4_ = fVar128 * fVar96;
                auVar182._8_4_ = fVar132 * fVar167;
                auVar186 = NEON_ext(auVar105,auVar105,8,1);
                auVar187._12_4_ = 0;
                auVar114 = NEON_ext(auVar152,auVar152,8,1);
                auVar194._0_4_ = fVar133 * fVar156;
                auVar194._4_4_ = fVar136 * fVar96;
                auVar194._8_4_ = fVar138 * fVar167;
                auVar182._12_4_ = 0;
                auVar120 = NEON_ext(auVar187,auVar187,8,1);
                auVar194._12_4_ = 0;
                auVar170 = NEON_ext(auVar182,auVar182,8,1);
                auVar180 = NEON_ext(auVar194,auVar194,8,1);
                fVar94 = auVar181._0_4_ + auVar99._0_4_ + auVar181._4_4_ + auVar99._4_4_;
                fVar135 = (fVar184 * fVar148 - fVar189 * fVar117) * _UNK_029c49f0;
                fVar88 = (fVar173 * fVar148 - fVar189 * fVar102) * _UNK_029c49f4;
                fVar92 = (fVar173 * fVar117 - fVar184 * fVar102) * _UNK_029c49f8;
                uVar158 = NEON_rev64(CONCAT44(auVar114._0_4_ + auVar114._4_4_,
                                              auVar152._0_4_ + auVar152._4_4_),4);
                fVar91 = auVar186._0_4_ + auVar105._0_4_ + auVar186._4_4_ + auVar105._4_4_;
                auVar100._4_4_ = fVar94;
                auVar100._0_4_ = fVar94;
                auVar100._8_4_ = fVar94;
                auVar100._12_4_ = fVar94;
                uVar190 = NEON_rev64(CONCAT44(auVar120._0_4_ + auVar120._4_4_,
                                              auVar187._0_4_ + auVar187._4_4_),4);
                uVar159 = NEON_rev64(CONCAT44(auVar170._0_4_ + auVar170._4_4_,
                                              auVar182._0_4_ + auVar182._4_4_),4);
                auVar106._4_4_ = fVar91;
                auVar106._0_4_ = fVar91;
                auVar106._8_4_ = fVar91;
                auVar106._12_4_ = fVar91;
                uVar191 = NEON_rev64(CONCAT44(auVar180._0_4_ + auVar180._4_4_,
                                              auVar194._0_4_ + auVar194._4_4_),4);
                auVar114 = NEON_frsqrte(auVar100,4);
                auVar120 = NEON_frsqrte(auVar106,4);
                fVar94 = auVar114._0_4_;
                auVar153._0_4_ = fVar94 * fVar94;
                fVar91 = auVar114._4_4_;
                auVar153._4_4_ = fVar91 * fVar91;
                fVar95 = auVar114._8_4_;
                auVar153._8_4_ = fVar95 * fVar95;
                auVar153._12_4_ = auVar114._12_4_ * auVar114._12_4_;
                auVar19._4_4_ = fVar88;
                auVar19._0_4_ = fVar135;
                auVar19._8_4_ = fVar92;
                auVar19._12_4_ = 0x3f800000;
                auVar20._4_4_ = fVar88;
                auVar20._0_4_ = fVar135;
                auVar20._8_4_ = fVar92;
                auVar20._12_4_ = 0x3f800000;
                auVar170 = NEON_ext(auVar19,auVar20,8,1);
                fVar125 = auVar120._0_4_;
                auVar171._0_4_ = fVar125 * fVar125;
                fVar126 = auVar120._4_4_;
                auVar171._4_4_ = fVar126 * fVar126;
                fVar127 = auVar120._8_4_;
                auVar171._8_4_ = fVar127 * fVar127;
                auVar171._12_4_ = auVar120._12_4_ * auVar120._12_4_;
                auVar114 = NEON_frsqrts(auVar153,auVar100,4);
                auVar120 = NEON_frsqrts(auVar171,auVar106,4);
                fVar173 = fVar173 * fVar94 * auVar114._0_4_;
                fVar184 = fVar184 * fVar91 * auVar114._4_4_;
                fVar189 = fVar189 * fVar95 * auVar114._8_4_;
                fVar102 = fVar102 * fVar125 * auVar120._0_4_;
                fVar117 = fVar117 * fVar126 * auVar120._4_4_;
                fVar148 = fVar148 * fVar127 * auVar120._8_4_;
                fVar94 = fVar135 * fVar135 + auVar170._0_4_ * auVar170._0_4_ + fVar88 * fVar88 + 0.0
                ;
                fVar125 = fVar44 * fVar173;
                fVar129 = fVar45 * fVar184;
                fVar141 = fVar44 * fVar102;
                fVar144 = fVar45 * fVar117;
                auVar154._0_4_ = fVar116 * fVar173;
                auVar154._4_4_ = fVar122 * fVar184;
                auVar154._8_4_ = fVar123 * fVar189;
                auVar11._4_4_ = fVar129;
                auVar11._0_4_ = fVar125;
                auVar11._8_4_ = fVar46 * fVar189;
                auVar11._12_4_ = 0;
                auVar12._4_4_ = fVar129;
                auVar12._0_4_ = fVar125;
                auVar12._8_4_ = fVar46 * fVar189;
                auVar12._12_4_ = 0;
                auVar120 = NEON_ext(auVar11,auVar12,8,1);
                auVar161._0_4_ = fVar116 * fVar102;
                auVar161._4_4_ = fVar122 * fVar117;
                auVar161._8_4_ = fVar123 * fVar148;
                auVar154._12_4_ = 0;
                auVar27._4_4_ = fVar144;
                auVar27._0_4_ = fVar141;
                auVar27._8_4_ = fVar46 * fVar148;
                auVar27._12_4_ = 0;
                auVar28._4_4_ = fVar144;
                auVar28._0_4_ = fVar141;
                auVar28._8_4_ = fVar46 * fVar148;
                auVar28._12_4_ = 0;
                auVar170 = NEON_ext(auVar27,auVar28,8,1);
                auVar165._0_4_ = fVar124 * fVar173;
                auVar165._4_4_ = fVar128 * fVar184;
                auVar165._8_4_ = fVar132 * fVar189;
                auVar161._12_4_ = 0;
                auVar180 = NEON_ext(auVar154,auVar154,8,1);
                auVar172._0_4_ = fVar124 * fVar102;
                auVar172._4_4_ = fVar128 * fVar117;
                auVar172._8_4_ = fVar132 * fVar148;
                auVar165._12_4_ = 0;
                auVar181 = NEON_ext(auVar161,auVar161,8,1);
                auVar183._0_4_ = fVar133 * fVar173;
                auVar183._4_4_ = fVar136 * fVar184;
                auVar183._8_4_ = fVar138 * fVar189;
                auVar172._12_4_ = 0;
                auVar186 = NEON_ext(auVar165,auVar165,8,1);
                auVar188._0_4_ = fVar133 * fVar102;
                auVar188._4_4_ = fVar136 * fVar117;
                auVar188._8_4_ = fVar138 * fVar148;
                auVar183._12_4_ = 0;
                auVar193 = NEON_ext(auVar172,auVar172,8,1);
                auVar115._4_4_ = fVar94;
                auVar115._0_4_ = fVar94;
                auVar115._8_4_ = fVar94;
                auVar115._12_4_ = fVar94;
                auVar188._12_4_ = 0;
                auVar197 = NEON_ext(auVar183,auVar183,8,1);
                auVar114 = NEON_frsqrte(auVar115,4);
                auVar198 = NEON_ext(auVar188,auVar188,8,1);
                fVar94 = auVar114._0_4_;
                auVar195._0_4_ = fVar94 * fVar94;
                fVar91 = auVar114._4_4_;
                auVar195._4_4_ = fVar91 * fVar91;
                fVar95 = auVar114._8_4_;
                auVar195._8_4_ = fVar95 * fVar95;
                auVar195._12_4_ = auVar114._12_4_ * auVar114._12_4_;
                auVar114 = NEON_frsqrts(auVar195,auVar115,4);
                uVar119 = NEON_rev64(CONCAT44(auVar120._0_4_ + auVar120._4_4_,fVar125 + fVar129),4);
                uVar108 = NEON_rev64(CONCAT44(auVar170._0_4_ + auVar170._4_4_,fVar141 + fVar144),4);
                uVar111 = NEON_rev64(CONCAT44(auVar180._0_4_ + auVar180._4_4_,
                                              auVar154._0_4_ + auVar154._4_4_),4);
                uVar150 = NEON_rev64(CONCAT44(auVar181._0_4_ + auVar181._4_4_,
                                              auVar161._0_4_ + auVar161._4_4_),4);
                uVar160 = NEON_rev64(CONCAT44(auVar186._0_4_ + auVar186._4_4_,
                                              auVar165._0_4_ + auVar165._4_4_),4);
                uVar163 = NEON_rev64(CONCAT44(auVar193._0_4_ + auVar193._4_4_,
                                              auVar172._0_4_ + auVar172._4_4_),4);
                fVar135 = fVar135 * fVar94 * auVar114._0_4_;
                fVar88 = fVar88 * fVar91 * auVar114._4_4_;
                fVar92 = fVar92 * fVar95 * auVar114._8_4_;
                uVar168 = NEON_rev64(CONCAT44(auVar197._0_4_ + auVar197._4_4_,
                                              auVar183._0_4_ + auVar183._4_4_),4);
                uVar174 = NEON_rev64(CONCAT44(auVar198._0_4_ + auVar198._4_4_,
                                              auVar188._0_4_ + auVar188._4_4_),4);
                fVar126 = fVar44 * fVar135;
                fVar130 = fVar45 * fVar88;
                fVar134 = fVar116 * fVar135;
                fVar137 = fVar122 * fVar88;
                auVar155._0_4_ = fVar124 * fVar135;
                auVar155._4_4_ = fVar128 * fVar88;
                auVar155._8_4_ = fVar132 * fVar92;
                auVar13._4_4_ = fVar130;
                auVar13._0_4_ = fVar126;
                auVar13._8_4_ = fVar46 * fVar92;
                auVar13._12_4_ = 0;
                auVar14._4_4_ = fVar130;
                auVar14._0_4_ = fVar126;
                auVar14._8_4_ = fVar46 * fVar92;
                auVar14._12_4_ = 0;
                auVar114 = NEON_ext(auVar13,auVar14,8,1);
                auVar166._0_4_ = fVar133 * fVar135;
                auVar166._4_4_ = fVar136 * fVar88;
                auVar166._8_4_ = fVar138 * fVar92;
                auVar155._12_4_ = 0;
                auVar21._4_4_ = fVar137;
                auVar21._0_4_ = fVar134;
                auVar21._8_4_ = fVar123 * fVar92;
                auVar21._12_4_ = 0;
                auVar22._4_4_ = fVar137;
                auVar22._0_4_ = fVar134;
                auVar22._8_4_ = fVar123 * fVar92;
                auVar22._12_4_ = 0;
                auVar120 = NEON_ext(auVar21,auVar22,8,1);
                auVar166._12_4_ = 0;
                auVar170 = NEON_ext(auVar155,auVar155,8,1);
                auVar180 = NEON_ext(auVar166,auVar166,8,1);
                uVar175 = NEON_rev64(CONCAT44(auVar114._0_4_ + auVar114._4_4_,fVar126 + fVar130),4);
                uVar176 = NEON_rev64(CONCAT44(auVar120._0_4_ + auVar120._4_4_,fVar134 + fVar137),4);
                uVar177 = NEON_rev64(CONCAT44(auVar170._0_4_ + auVar170._4_4_,
                                              auVar155._0_4_ + auVar155._4_4_),4);
                uVar178 = NEON_rev64(CONCAT44(auVar180._0_4_ + auVar180._4_4_,
                                              auVar166._0_4_ + auVar166._4_4_),4);
                fVar94 = auVar113._0_4_;
                fVar127 = fVar94 * ABS(auVar154._0_4_ + auVar154._4_4_ + (float)uVar111);
                fVar91 = auVar113._4_4_;
                fVar131 = fVar91 * ABS(auVar161._0_4_ + auVar161._4_4_ + (float)uVar150);
                fVar95 = auVar113._8_4_;
                fVar134 = fVar95 * ABS(fVar134 + fVar137 + (float)uVar176);
                auVar121._0_4_ = fVar94 * ABS(fVar125 + fVar129 + (float)uVar119);
                auVar121._4_4_ = fVar91 * ABS(fVar141 + fVar144 + (float)uVar108);
                auVar121._8_4_ = fVar95 * ABS(fVar126 + fVar130 + (float)uVar175);
                fVar125 = fVar94 * ABS(auVar165._0_4_ + auVar165._4_4_ + (float)uVar160);
                fVar126 = fVar91 * ABS(auVar172._0_4_ + auVar172._4_4_ + (float)uVar163);
                fVar129 = fVar95 * ABS(auVar155._0_4_ + auVar155._4_4_ + (float)uVar177);
                fVar130 = fVar94 * ABS(auVar183._0_4_ + auVar183._4_4_ + (float)uVar168);
                fVar137 = fVar91 * ABS(auVar188._0_4_ + auVar188._4_4_ + (float)uVar174);
                fVar141 = fVar95 * ABS(auVar166._0_4_ + auVar166._4_4_ + (float)uVar178);
                auVar121._12_4_ = 0;
                auVar15._4_4_ = fVar131;
                auVar15._0_4_ = fVar127;
                auVar15._8_4_ = fVar134;
                auVar15._12_4_ = 0;
                auVar16._4_4_ = fVar131;
                auVar16._0_4_ = fVar127;
                auVar16._8_4_ = fVar134;
                auVar16._12_4_ = 0;
                auVar114 = NEON_ext(auVar15,auVar16,8,1);
                auVar113 = NEON_ext(auVar121,auVar121,8,1);
                auVar23._4_4_ = fVar126;
                auVar23._0_4_ = fVar125;
                auVar23._8_4_ = fVar129;
                auVar23._12_4_ = 0;
                auVar24._4_4_ = fVar126;
                auVar24._0_4_ = fVar125;
                auVar24._8_4_ = fVar129;
                auVar24._12_4_ = 0;
                auVar120 = NEON_ext(auVar23,auVar24,8,1);
                auVar29._4_4_ = fVar137;
                auVar29._0_4_ = fVar130;
                auVar29._8_4_ = fVar141;
                auVar29._12_4_ = 0;
                auVar30._4_4_ = fVar137;
                auVar30._0_4_ = fVar130;
                auVar30._8_4_ = fVar141;
                auVar30._12_4_ = 0;
                auVar170 = NEON_ext(auVar29,auVar30,8,1);
                uVar111 = NEON_rev64(CONCAT44(auVar114._0_4_ + auVar114._4_4_,fVar127 + fVar131),4);
                uVar108 = NEON_rev64(CONCAT44(auVar113._0_4_ + auVar113._4_4_,
                                              auVar121._0_4_ + auVar121._4_4_),4);
                uVar119 = NEON_rev64(CONCAT44(auVar120._0_4_ + auVar120._4_4_,fVar125 + fVar126),4);
                uVar150 = NEON_rev64(CONCAT44(auVar170._0_4_ + auVar170._4_4_,fVar130 + fVar137),4);
                if (0.0 <= ((auVar194._0_4_ + auVar194._4_4_ + (float)uVar191) -
                           (auVar103._0_4_ + auVar103._4_4_ + (float)uVar162)) -
                           (fVar130 + fVar137 + (float)uVar150) &&
                    (0.0 <= ((auVar182._0_4_ + auVar182._4_4_ + (float)uVar159) -
                            (auVar97._0_4_ + auVar97._4_4_ + (float)uVar157)) -
                            (fVar125 + fVar126 + (float)uVar119) &&
                    (0.0 <= ((auVar152._0_4_ + auVar152._4_4_ + (float)uVar158) -
                            (auVar112._0_4_ + auVar112._4_4_ + (float)uVar118)) -
                            (auVar121._0_4_ + auVar121._4_4_ + (float)uVar108) &&
                    0.0 <= ((auVar187._0_4_ + auVar187._4_4_ + (float)uVar190) -
                           (fVar87 + fVar90 + (float)uVar149)) -
                           (fVar127 + fVar131 + (float)uVar111)))) {
                  auVar110._0_4_ = fVar139 * fVar135;
                  auVar110._4_4_ = fVar142 * fVar88;
                  auVar110._8_4_ = fVar145 * fVar92;
                  auVar107._0_4_ = fVar139 * fVar173;
                  auVar107._4_4_ = fVar142 * fVar184;
                  auVar107._8_4_ = fVar145 * fVar189;
                  auVar101._0_4_ = fVar139 * fVar102;
                  auVar101._4_4_ = fVar142 * fVar117;
                  auVar101._8_4_ = fVar145 * fVar148;
                  fVar156 = fVar139 * fVar156;
                  fVar96 = fVar142 * fVar96;
                  auVar107._12_4_ = 0;
                  uVar111 = NEON_rev64(CONCAT44(auVar82._0_4_ + auVar82._4_4_,
                                                auVar109._0_4_ + auVar109._4_4_),4);
                  auVar101._12_4_ = 0;
                  auVar113 = NEON_ext(auVar107,auVar107,8,1);
                  auVar110._12_4_ = 0;
                  auVar114 = NEON_ext(auVar101,auVar101,8,1);
                  auVar120 = NEON_ext(auVar110,auVar110,8,1);
                  auVar9._4_4_ = fVar96;
                  auVar9._0_4_ = fVar156;
                  auVar9._8_4_ = fVar145 * fVar167;
                  auVar9._12_4_ = 0;
                  auVar10._4_4_ = fVar96;
                  auVar10._0_4_ = fVar156;
                  auVar10._8_4_ = fVar145 * fVar167;
                  auVar10._12_4_ = 0;
                  auVar170 = NEON_ext(auVar9,auVar10,8,1);
                  uVar108 = NEON_rev64(CONCAT44(auVar113._0_4_ + auVar113._4_4_,
                                                auVar107._0_4_ + auVar107._4_4_),4);
                  uVar118 = NEON_rev64(CONCAT44(auVar114._0_4_ + auVar114._4_4_,
                                                auVar101._0_4_ + auVar101._4_4_),4);
                  uVar119 = NEON_rev64(CONCAT44(auVar120._0_4_ + auVar120._4_4_,
                                                auVar110._0_4_ + auVar110._4_4_),4);
                  auVar83._0_4_ = fVar94 * ABS(auVar107._0_4_ + auVar107._4_4_ + (float)uVar108);
                  auVar83._4_4_ = fVar91 * ABS(auVar101._0_4_ + auVar101._4_4_ + (float)uVar118);
                  auVar83._8_4_ = fVar95 * ABS(auVar110._0_4_ + auVar110._4_4_ + (float)uVar119);
                  auVar83._12_4_ = 0;
                  auVar113 = NEON_ext(auVar83,auVar83,8,1);
                  uVar118 = NEON_rev64(CONCAT44(auVar170._0_4_ + auVar170._4_4_,fVar156 + fVar96),4)
                  ;
                  uVar108 = NEON_rev64(CONCAT44(auVar113._0_4_ + auVar113._4_4_,
                                                auVar83._0_4_ + auVar83._4_4_),4);
                  if (0.0 <= ((fVar156 + fVar96 + (float)uVar118) -
                             (auVar109._0_4_ + auVar109._4_4_ + (float)uVar111)) -
                             (auVar83._0_4_ + auVar83._4_4_ + (float)uVar108))
                  goto code_r0x02266b5c;
                }
              }
              goto code_r0x022671c8;
            }
            auVar200._4_4_ = fVar117;
            auVar200._0_4_ = fVar95;
            auVar200._8_8_ = auVar198._8_8_;
            auVar199._4_4_ = fVar94;
            auVar199._0_4_ = fVar94;
            auVar199._8_4_ = fVar94;
            auVar199._12_4_ = fVar94;
            auVar113 = NEON_ext(auVar199,auVar200,8,1);
            auVar113 = NEON_ext(auVar113,auVar113,8,1);
            if (auVar113._12_4_ - fVar156 < 0.0 ||
                (auVar113._8_4_ - fVar156 < 0.0 ||
                (auVar113._0_4_ - fVar156 < 0.0 || auVar113._4_4_ - fVar156 < 0.0)))
            goto code_r0x02266b7c;
code_r0x02266b5c:
            puVar2 = (ulong *)(param_9 + (long)((int)uVar4 >> 5) * 8);
            do {
              cVar5 = '\x01';
              bVar6 = (bool)ExclusiveMonitorPass(puVar2,0x10);
              if (bVar6) {
                *puVar2 = *puVar2 | 2L << iVar7;
                cVar5 = ExclusiveMonitorsStatus();
              }
            } while (cVar5 != '\0');
          }
          uVar75 = uVar75 + 1;
          puVar70 = puVar70 + 1;
        } while (uVar75 != uVar73);
      }
      uVar74 = uVar74 + 1;
    } while (uVar74 != uVar3);
  }
  return;
}

// ==== Aska::ObjectManager::AddPaintingListCandidates(Aska::RenderableObject*)
// vaddr 0x21672ec | ghidra 0x22672ec | size 228 | symbol _ZN4Aska13ObjectManager25AddPaintingListCandidatesEPNS_16RenderableObjectE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13ObjectManager25AddPaintingListCandidatesEPNS_16RenderableObjectE
               (long param_1,long param_2)

{
  int *piVar1;
  long lVar2;
  uint uVar3;
  int iVar4;
  char cVar5;
  bool bVar6;
  long lVar7;
  
  if ((*(byte *)(param_2 + 0x1b5) >> 3 & 1) == 0) {
    iVar4 = *(int *)(param_1 + 0x3ef4);
    *(int *)(param_1 + 0x3ef4) = iVar4 + 1;
    *(long *)(*(long *)(param_1 + 0x1ac8) + (long)iVar4 * 8) = param_2;
    *(ushort *)(param_2 + 0x1b5) = *(ushort *)(param_2 + 0x1b5) | 8;
    *(uint *)(param_2 + 0x198) = *(uint *)(param_2 + 0x198) & 0xfffffeff;
  }
  if (*(byte *)(*(long *)(param_1 + 0x4478) + (ulong)*(byte *)(param_2 + 0x1b7) + 0x10) <
      *(byte *)(*(long *)(param_1 + 0x4478) + 0x25)) {
    uVar3 = *(uint *)(param_1 + 0x3f20);
    if ((int)uVar3 < 2) {
      uVar3 = 1;
    }
    if (0 < (int)uVar3) {
      lVar7 = 0;
      piVar1 = (int *)(param_2 + 0x1ac);
      do {
        lVar2 = param_1 + lVar7 * 4;
        *(long *)(*(long *)(param_1 + lVar7 * 0x10 + 0x1028) + (long)*(int *)(lVar2 + 0x1bc8) * 8) =
             param_2;
        *(int *)(lVar2 + 0x1bc8) = *(int *)(lVar2 + 0x1bc8) + 1;
        do {
          cVar5 = '\x01';
          bVar6 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar6) {
            *piVar1 = *piVar1 + 1;
            cVar5 = ExclusiveMonitorsStatus();
          }
        } while (cVar5 != '\0');
        lVar7 = lVar7 + 1;
      } while (lVar7 < (long)(ulong)uVar3);
    }
  }
  else {
    *(long *)(*(long *)(param_1 + 0x1010) + (long)*(int *)(param_1 + 0x1bc4) * 8) = param_2;
    *(int *)(param_1 + 0x1bc4) = *(int *)(param_1 + 0x1bc4) + 1;
    piVar1 = (int *)(param_2 + 0x1ac);
    do {
      cVar5 = '\x01';
      bVar6 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar6) {
        *piVar1 = *piVar1 + 1;
        cVar5 = ExclusiveMonitorsStatus();
      }
    } while (cVar5 != '\0');
  }
  return;
}

// ==== Aska::ObjectManager::AddMultipassPaintingListCandidates(Aska::RenderableObject*, int)
// vaddr 0x21673d0 | ghidra 0x22673d0 | size 112 | symbol _ZN4Aska13ObjectManager34AddMultipassPaintingListCandidatesEPNS_16RenderableObjectEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13ObjectManager34AddMultipassPaintingListCandidatesEPNS_16RenderableObjectEi
               (long param_1,long param_2,int param_3)

{
  long lVar1;
  int *piVar2;
  int iVar3;
  char cVar4;
  bool bVar5;
  
  if ((*(byte *)(param_2 + 0x1b5) >> 3 & 1) == 0) {
    iVar3 = *(int *)(param_1 + 0x3ef4);
    *(int *)(param_1 + 0x3ef4) = iVar3 + 1;
    *(long *)(*(long *)(param_1 + 0x1ac8) + (long)iVar3 * 8) = param_2;
    *(ushort *)(param_2 + 0x1b5) = *(ushort *)(param_2 + 0x1b5) | 8;
    *(uint *)(param_2 + 0x198) = *(uint *)(param_2 + 0x198) & 0xfffffeff;
  }
  lVar1 = param_1 + (long)param_3 * 4;
  *(long *)(*(long *)(param_1 + (long)param_3 * 0x10 + 0x10a8) + (long)*(int *)(lVar1 + 0x1c08) * 8)
       = param_2;
  *(int *)(lVar1 + 0x1c08) = *(int *)(lVar1 + 0x1c08) + 1;
  piVar2 = (int *)(param_2 + 0x1ac);
  do {
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar5) {
      *piVar2 = *piVar2 + 1;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
  return;
}

// ==== Aska::ObjectManager::IsReducedBufferLayer(int)
// vaddr 0x2167440 | ghidra 0x2267440 | size 8 | symbol _ZN4Aska13ObjectManager20IsReducedBufferLayerEi | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska13ObjectManager20IsReducedBufferLayerEi(void)

{
  return 0;
}

// ==== Aska::ObjectManager::IsNeedZLayer(int)
// vaddr 0x2167448 | ghidra 0x2267448 | size 36 | symbol _ZN4Aska13ObjectManager12IsNeedZLayerEi | lib libSOA-3.7.0.so | 2026-10-04
byte _ZN4Aska13ObjectManager12IsNeedZLayerEi(long param_1,uint param_2)

{
  return *(byte *)(*(long *)(*(long *)(param_1 + 0x4478) + 8) +
                   (ulong)*(byte *)(*(long *)(param_1 + 0x4478) + (ulong)(param_2 & 0xff) + 0x10) *
                   2 + 1) >> 4 & 1;
}

// ==== Aska::ObjectManager::ClearMultipassEnvironment(int)
// vaddr 0x216746c | ghidra 0x226746c | size 28 | symbol _ZN4Aska13ObjectManager25ClearMultipassEnvironmentEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13ObjectManager25ClearMultipassEnvironmentEi(long param_1,int param_2)

{
  param_1 = param_1 + (long)param_2 * 0x48;
  *(ushort *)(param_1 + 0x45ea) = *(ushort *)(param_1 + 0x45ea) | 1;
  return;
}

// ==== Aska::ObjectManager::SetMultipassEnvironment(int, bool, int, int, int, int, int, int, unsigned int, float, int, Aska::Camera*, bool, bool, bool, bool)
// vaddr 0x2167488 | ghidra 0x2267488 | size 560 | symbol _ZN4Aska13ObjectManager23SetMultipassEnvironmentEibiiiiiijfiPNS_6CameraEbbbb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13ObjectManager23SetMultipassEnvironmentEibiiiiiijfiPNS_6CameraEbbbb
               (float param_1,long param_2,int param_3,ushort param_4,uint param_5,uint param_6,
               uint param_7,int param_8,int param_9,int param_10,int param_11,int param_12,
               long param_13,byte param_14,byte param_15,byte param_16,byte param_17)

{
  ushort *puVar1;
  ushort *puVar2;
  long lVar3;
  ushort uVar4;
  long lVar5;
  
  lVar5 = (long)param_3 + -1;
  lVar3 = param_2 + lVar5 * 0x48;
  puVar1 = (ushort *)(lVar3 + 0x4632);
  uVar4 = *puVar1;
  puVar2 = (ushort *)(lVar3 + 0x45f0);
  if (((uVar4 >> 2 & 1) != 0) &&
     ((((((uVar4 >> 1 & 1) != (param_4 & 1) || (*puVar2 != param_5)) ||
        (*(ushort *)(param_2 + lVar5 * 0x48 + 0x45f2) != param_6)) ||
       (((*(ushort *)(param_2 + lVar5 * 0x48 + 0x45f6) != param_7 ||
         (*(int *)(param_2 + lVar5 * 0x48 + 0x45f8) != param_8)) ||
        ((*(int *)(param_2 + lVar5 * 0x48 + 0x45fc) != param_9 ||
         ((*(int *)(param_2 + lVar5 * 0x48 + 0x4600) != param_10 ||
          (*(int *)(param_2 + lVar5 * 0x48 + 0x4604) != param_11)))))))) ||
      ((*(float *)(param_2 + lVar5 * 0x48 + 0x4608) != param_1 ||
       (((((*(int *)(param_2 + lVar5 * 0x48 + 0x460c) != param_12 ||
           (*(long *)(param_2 + lVar5 * 0x48 + 0x4610) != param_13)) ||
          ((uVar4 >> 7 & 1) != (param_14 & 1))) ||
         (((uVar4 >> 9 & 1) != (param_15 & 1) || ((uVar4 >> 0xc & 1) != (param_16 & 1))))) ||
        ((uVar4 >> 10 & 1) != (param_17 & 1))))))))) {
    uVar4 = uVar4 & 0xfff7;
    *puVar1 = uVar4;
  }
  *puVar2 = (ushort)param_5;
  param_2 = param_2 + lVar5 * 0x48;
  *(short *)(param_2 + 0x45f2) = (short)param_6;
  *(short *)(param_2 + 0x45f6) = (short)param_7;
  *(int *)(param_2 + 0x45f8) = param_8;
  *(int *)(param_2 + 0x45fc) = param_9;
  *(int *)(param_2 + 0x4600) = param_10;
  *(int *)(param_2 + 0x4604) = param_11;
  *(float *)(param_2 + 0x4608) = param_1;
  *(int *)(param_2 + 0x460c) = param_12;
  *(long *)(param_2 + 0x4610) = param_13;
  *(undefined4 *)(param_2 + 0x4628) = 0x1000;
  *puVar1 = (param_16 & 1) << 0xc | (param_17 & 1) << 10 | uVar4 & 0xe878 | (param_4 & 1) << 1 | 4;
  *(undefined1 *)(param_2 + 0x4630) = 0;
  return;
}

// ==== Aska::ObjectManager::SetShadowEnvironment(int, bool, int, int, int, int, int, int, unsigned int, float, int, Aska::Camera*, int, int, bool, unsigned char)
// vaddr 0x21676b8 | ghidra 0x22676b8 | size 580 | symbol _ZN4Aska13ObjectManager20SetShadowEnvironmentEibiiiiiijfiPNS_6CameraEiibh | lib libSOA-3.7.0.so | 2026-10-04
bool _ZN4Aska13ObjectManager20SetShadowEnvironmentEibiiiiiijfiPNS_6CameraEiibh
               (float param_1,long param_2,int param_3,ushort param_4,uint param_5,uint param_6,
               uint param_7,int param_8,int param_9,int param_10,int param_11,int param_12,
               long param_13,int param_14,uint param_15,byte param_16,byte param_17)

{
  ushort *puVar1;
  ushort uVar2;
  long lVar3;
  ushort uVar4;
  long lVar5;
  
  lVar3 = param_2 + (long)param_3 * 0x48;
  *(undefined4 *)(lVar3 + 0x8e2c) = 0;
  puVar1 = (ushort *)(lVar3 + 0x8e32);
  uVar4 = *puVar1;
  uVar2 = param_16 & 1;
  lVar5 = (long)param_3;
  if (((uVar4 >> 2 & 1) != 0) &&
     ((((((uVar4 >> 1 & 1) != (param_4 & 1) || (*(ushort *)(lVar3 + 0x8df0) != param_5)) ||
        (*(ushort *)(param_2 + lVar5 * 0x48 + 0x8df2) != param_6)) ||
       (((*(ushort *)(param_2 + lVar5 * 0x48 + 0x8df6) != param_7 ||
         (*(int *)(param_2 + lVar5 * 0x48 + 0x8df8) != param_8)) ||
        ((*(int *)(param_2 + lVar5 * 0x48 + 0x8dfc) != param_9 ||
         ((*(int *)(param_2 + lVar5 * 0x48 + 0x8e00) != param_10 ||
          (*(int *)(param_2 + lVar5 * 0x48 + 0x8e04) != param_11)))))))) ||
      ((*(float *)(param_2 + lVar5 * 0x48 + 0x8e08) != param_1 ||
       (((((*(int *)(param_2 + lVar5 * 0x48 + 0x8e0c) != param_12 ||
           (*(long *)(param_2 + lVar5 * 0x48 + 0x8e10) != param_13)) ||
          (*(int *)(param_2 + lVar5 * 0x48 + 0x8e28) != param_14)) ||
         ((*(ushort *)(param_2 + lVar5 * 0x48 + 0x8df4) != param_15 || ((uVar4 >> 0xb & 1) != uVar2)
          ))) || ((ushort)(param_17 | uVar2) != (ushort)*(byte *)(param_2 + lVar5 * 0x48 + 0x8e31)))
       )))))) {
    uVar4 = uVar4 & 0xfff7;
    *puVar1 = uVar4;
  }
  *(ushort *)(lVar3 + 0x8df0) = (ushort)param_5;
  param_2 = param_2 + lVar5 * 0x48;
  *(short *)(param_2 + 0x8df2) = (short)param_6;
  *(short *)(param_2 + 0x8df6) = (short)param_7;
  *(int *)(param_2 + 0x8df8) = param_8;
  *(int *)(param_2 + 0x8dfc) = param_9;
  *(int *)(param_2 + 0x8e00) = param_10;
  *(int *)(param_2 + 0x8e04) = param_11;
  *(float *)(param_2 + 0x8e08) = param_1;
  *(int *)(param_2 + 0x8e0c) = param_12;
  *(long *)(param_2 + 0x8e10) = param_13;
  *(int *)(param_2 + 0x8e28) = param_14;
  *(short *)(param_2 + 0x8df4) = (short)param_15;
  *puVar1 = uVar4 & 0xf000 | uVar4 & 0x7f8 | (param_4 & 1) << 1 | uVar2 << 0xb | 4;
  *(char *)(param_2 + 0x8e31) = (char)(param_17 | uVar2);
  return (uVar4 & 8) == 0;
}

// ==== Aska::ObjectManager::SetShadowMapResolver(int, Aska::ShadowManager*)
// vaddr 0x21678fc | ghidra 0x22678fc | size 304 | symbol _ZN4Aska13ObjectManager20SetShadowMapResolverEiPNS_13ShadowManagerE | lib libSOA-3.7.0.so | 2026-10-04
long * _ZN4Aska13ObjectManager20SetShadowMapResolverEiPNS_13ShadowManagerE
                 (long param_1,int param_2,long param_3)

{
  ushort *puVar1;
  int *piVar2;
  long *plVar3;
  int iVar4;
  char cVar5;
  bool bVar6;
  long *plVar7;
  
  plVar3 = (long *)(param_1 + (long)param_2 * 8 + 0xb1f0);
  plVar7 = (long *)*plVar3;
  if (plVar7 == (long *)0x0) {
    plVar7 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x440,PTR__ZSt7nothrow_02cb9a80);
    if (plVar7 == (long *)0x0) {
      *plVar3 = 0;
      return (long *)0x0;
    }
    Aska::ShadowMapResolver::ShadowMapResolver()(plVar7);
    *plVar3 = (long)plVar7;
  }
  plVar7[0x80] = param_3;
  *(char *)(plVar7 + 0x86) = (char)param_2;
  *(uint *)(plVar7 + 0x33) = *(uint *)(plVar7 + 0x33) & 0xdfffffbf;
  puVar1 = (ushort *)((long)plVar7 + 0x1b5);
  piVar2 = (int *)((long)plVar7 + 0x1ac);
  *puVar1 = *puVar1 & 0xfefe;
  *(undefined4 *)((long)plVar7 + 0x1ac) = 0;
  plVar7[0x3a] = 0;
  *(undefined4 *)((long)plVar7 + 0x1cc) = 0;
  (**(code **)(*plVar7 + 0x198))(plVar7);
  plVar7[0x47] = 0;
  plVar7[0x46] = 0;
  plVar7[0x40] = 0;
  plVar7[0x3f] = 0;
  plVar7[0x3e] = 0;
  plVar7[0x3d] = 0;
  *puVar1 = *puVar1 & 0xfff9;
  *(uint *)(plVar7 + 0x33) = *(uint *)(plVar7 + 0x33) | 0x124;
  iVar4 = *(int *)(param_1 + 0x3ef4);
  *(int *)(param_1 + 0x3ef4) = iVar4 + 1;
  *(long **)(*(long *)(param_1 + 0x1ac8) + (long)iVar4 * 8) = plVar7;
  *puVar1 = *puVar1 | 8;
  *(uint *)(plVar7 + 0x33) = *(uint *)(plVar7 + 0x33) & 0xfffffeff;
  do {
    cVar5 = '\x01';
    bVar6 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar6) {
      *piVar2 = *piVar2 + 1;
      cVar5 = ExclusiveMonitorsStatus();
    }
  } while (cVar5 != '\0');
  return plVar7;
}

// ==== Aska::ObjectManager::WaitForInitialize()
// vaddr 0x2167a2c | ghidra 0x2267a2c | size 28 | symbol _ZN4Aska13ObjectManager17WaitForInitializeEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13ObjectManager17WaitForInitializeEv(long param_1)

{
  Aska::RenderThread::ReqSwap()(*(undefined8 *)(param_1 + 0x4480));
  (*(code *)PTR__ZN4Aska12RenderThread15WaitDeviceResetEv_02cb3888)
            (*(undefined8 *)(param_1 + 0x4480));
  return;
}

// ==== Aska::ObjectManager::OrMultipassRenderingIDtoAllObjects(Aska::TLongInt<unsigned long, 2> const*, bool)
// vaddr 0x2167a48 | ghidra 0x2267a48 | size 120 | symbol _ZN4Aska13ObjectManager34OrMultipassRenderingIDtoAllObjectsEPKNS_8TLongIntImLi2EEEb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13ObjectManager34OrMultipassRenderingIDtoAllObjectsEPKNS_8TLongIntImLi2EEEb
               (long param_1,ulong *param_2,uint param_3)

{
  ulong uVar1;
  bool bVar2;
  long lVar3;
  
  lVar3 = *(long *)(param_1 + 0x18);
  param_1 = param_1 + 8;
  bVar2 = param_1 != lVar3;
  if ((param_3 & 1) == 0) {
    while (bVar2) {
      uVar1 = param_2[1];
      *(ulong *)(lVar3 + 0x208) = *param_2 | *(ulong *)(lVar3 + 0x208);
      *(ulong *)(lVar3 + 0x210) = uVar1 | *(ulong *)(lVar3 + 0x210);
      lVar3 = *(long *)(lVar3 + 0x10);
      bVar2 = param_1 != lVar3;
    }
  }
  else {
    while (bVar2) {
      if ((*(byte *)(lVar3 + 0x198) >> 3 & 1) == 0) {
        uVar1 = param_2[1];
        *(ulong *)(lVar3 + 0x208) = *param_2 | *(ulong *)(lVar3 + 0x208);
        *(ulong *)(lVar3 + 0x210) = uVar1 | *(ulong *)(lVar3 + 0x210);
      }
      lVar3 = *(long *)(lVar3 + 0x10);
      bVar2 = param_1 != lVar3;
    }
  }
  return;
}

// ==== Aska::ObjectManager::AndMultipassRenderingIDtoAllObjects(Aska::TLongInt<unsigned long, 2> const*, bool)
// vaddr 0x2167ac0 | ghidra 0x2267ac0 | size 120 | symbol _ZN4Aska13ObjectManager35AndMultipassRenderingIDtoAllObjectsEPKNS_8TLongIntImLi2EEEb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13ObjectManager35AndMultipassRenderingIDtoAllObjectsEPKNS_8TLongIntImLi2EEEb
               (long param_1,ulong *param_2,uint param_3)

{
  ulong uVar1;
  bool bVar2;
  long lVar3;
  
  lVar3 = *(long *)(param_1 + 0x18);
  param_1 = param_1 + 8;
  bVar2 = param_1 != lVar3;
  if ((param_3 & 1) == 0) {
    while (bVar2) {
      uVar1 = param_2[1];
      *(ulong *)(lVar3 + 0x208) = *param_2 & *(ulong *)(lVar3 + 0x208);
      *(ulong *)(lVar3 + 0x210) = uVar1 & *(ulong *)(lVar3 + 0x210);
      lVar3 = *(long *)(lVar3 + 0x10);
      bVar2 = param_1 != lVar3;
    }
  }
  else {
    while (bVar2) {
      if ((*(byte *)(lVar3 + 0x198) >> 3 & 1) == 0) {
        uVar1 = param_2[1];
        *(ulong *)(lVar3 + 0x208) = *param_2 & *(ulong *)(lVar3 + 0x208);
        *(ulong *)(lVar3 + 0x210) = uVar1 & *(ulong *)(lVar3 + 0x210);
      }
      lVar3 = *(long *)(lVar3 + 0x10);
      bVar2 = param_1 != lVar3;
    }
  }
  return;
}

// ==== Aska::ObjectManager::DeleteResources()
// vaddr 0x2167b38 | ghidra 0x2267b38 | size 200 | symbol _ZN4Aska13ObjectManager15DeleteResourcesEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13ObjectManager15DeleteResourcesEv(long param_1)

{
  long *plVar1;
  long *plVar2;
  
  if (*(long *)(param_1 + 0x45d8) != 0) {
    Aska::PostProcessMaster::DeleteResources()();
  }
  plVar1 = *(long **)(param_1 + 0x45b0);
  if (plVar1 != (long *)0x0) {
    (**(code **)(*plVar1 + 0x38))(plVar1,0);
    *(undefined8 *)(param_1 + 0x45b0) = 0;
  }
  plVar1 = *(long **)(param_1 + 0x45b8);
  if (plVar1 != (long *)0x0) {
    (**(code **)(*plVar1 + 0x38))(plVar1,0);
    *(undefined8 *)(param_1 + 0x45b8) = 0;
  }
  plVar1 = *(long **)(param_1 + 0x45c0);
  if (plVar1 != (long *)0x0) {
    (**(code **)(*plVar1 + 0x38))(plVar1,0);
    *(undefined8 *)(param_1 + 0x45c0) = 0;
  }
  plVar1 = *(long **)(param_1 + 0x45c8);
  if (plVar1 != (long *)0x0) {
    (**(code **)(*plVar1 + 0x38))(plVar1,0);
    *(undefined8 *)(param_1 + 0x45c8) = 0;
  }
  plVar1 = (long *)(param_1 + 0xb1f0);
  do {
    plVar2 = (long *)*plVar1;
    if (plVar2 != (long *)0x0) {
      (**(code **)(*plVar2 + 0x38))(plVar2,0);
    }
    plVar1 = plVar1 + 1;
  } while (plVar1 < (long *)(param_1 + 0xb3f0U));
  (*(code *)PTR__ZN4Aska21ShadowManagerRegistry27DeleteDummyRenderableObjectEv_02ca8798)();
  return;
}

// ==== Aska::ObjectManager::SetSceneEV(int, float, float, float)
// vaddr 0x2167c00 | ghidra 0x2267c00 | size 124 | symbol _ZN4Aska13ObjectManager10SetSceneEVEifff | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska13ObjectManager10SetSceneEVEifff
          (undefined4 param_1,undefined4 param_2,undefined4 param_3,long param_4,int param_5)

{
  long lVar1;
  
  if (param_5 == 0) {
    *(undefined4 *)(*(long *)(param_4 + 0xb418) + 0x488) = param_1;
    lVar1 = *(long *)(param_4 + 0xb418);
  }
  else {
    if ((*(byte *)(param_4 + ((long)param_5 + -1) * 0x48 + 0x4632) >> 5 & 1) == 0) {
      return 0;
    }
    param_4 = param_4 + ((long)param_5 + -1) * 0x48;
    *(undefined4 *)(*(long *)(param_4 + 0x4618) + 0x488) = param_1;
    lVar1 = *(long *)(param_4 + 0x4618);
  }
  *(undefined4 *)(lVar1 + 0x490) = param_2;
  *(undefined4 *)(lVar1 + 0x494) = param_3;
  Aska::CameraManager::AdjustAllCameraEV(int)(*(undefined8 *)PTR__ZN4Aska6Global16m_pCameraManagerE_02cb7d08);
  return 1;
}

// ==== Aska::ObjectManager::GetSceneEV(int) const
// vaddr 0x2167c7c | ghidra 0x2267c7c | size 76 | symbol _ZNK4Aska13ObjectManager10GetSceneEVEi | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK4Aska13ObjectManager10GetSceneEVEi(long param_1,int param_2)

{
  long *plVar1;
  
  if (param_2 == 0) {
    plVar1 = (long *)(param_1 + 0xb418);
  }
  else {
    if ((*(byte *)(param_1 + ((long)param_2 + -1) * 0x48 + 0x4632) >> 5 & 1) == 0) {
      return 0;
    }
    plVar1 = (long *)(param_1 + ((long)param_2 + -1) * 0x48 + 0x4618);
  }
  return *(undefined4 *)(*plVar1 + 0x488);
}

// ==== Aska::ObjectManager::SetMeteringScale(int, float)
// vaddr 0x2167cc8 | ghidra 0x2267cc8 | size 104 | symbol _ZN4Aska13ObjectManager16SetMeteringScaleEif | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska13ObjectManager16SetMeteringScaleEif(undefined4 param_1,long param_2,int param_3)

{
  long lVar1;
  
  if (param_3 == 0) {
    lVar1 = *(long *)(param_2 + 0xb418);
  }
  else {
    if ((*(byte *)(param_2 + ((long)param_3 + -1) * 0x48 + 0x4632) >> 5 & 1) == 0) {
      return 0;
    }
    lVar1 = *(long *)(param_2 + ((long)param_3 + -1) * 0x48 + 0x4618);
  }
  *(undefined4 *)(lVar1 + 0x48c) = param_1;
  Aska::CameraManager::AdjustAllCameraEV(int)(*(undefined8 *)PTR__ZN4Aska6Global16m_pCameraManagerE_02cb7d08);
  return 1;
}

// ==== Aska::ObjectManager::SetPostProcessDitherRate(float)
// vaddr 0x2167d30 | ghidra 0x2267d30 | size 32 | symbol _ZN4Aska13ObjectManager24SetPostProcessDitherRateEf | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska13ObjectManager24SetPostProcessDitherRateEf(float param_1,long param_2)

{
  float fVar1;
  long lVar2;
  
  fVar1 = _UNK_029cc844;
  lVar2 = *(long *)(param_2 + 0xb418);
  *(float *)(lVar2 + 0x464) = param_1;
  *(float *)(lVar2 + 0x3f4) = param_1 * fVar1;
  return;
}

// ==== Aska::ObjectManager::GetPostProcessDitherRate() const
// vaddr 0x2167d50 | ghidra 0x2267d50 | size 16 | symbol _ZNK4Aska13ObjectManager24GetPostProcessDitherRateEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK4Aska13ObjectManager24GetPostProcessDitherRateEv(long param_1)

{
  return *(undefined4 *)(*(long *)(param_1 + 0xb418) + 0x464);
}

// ==== Aska::ObjectManager::GetPostProcessBloom()
// vaddr 0x2167d60 | ghidra 0x2267d60 | size 16 | symbol _ZN4Aska13ObjectManager19GetPostProcessBloomEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska13ObjectManager19GetPostProcessBloomEv(long param_1)

{
  return *(undefined8 *)(*(long *)(param_1 + 0xb418) + 0x470);
}

// ==== Aska::ObjectManager::SetVertexShaderGprAllocation(int)
// vaddr 0x2167d70 | ghidra 0x2267d70 | size 4 | symbol _ZN4Aska13ObjectManager28SetVertexShaderGprAllocationEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13ObjectManager28SetVertexShaderGprAllocationEi(void)

{
  return;
}

// ==== Aska::ObjectManager::GetVertexShaderGprAllocation() const
// vaddr 0x2167d74 | ghidra 0x2267d74 | size 8 | symbol _ZNK4Aska13ObjectManager28GetVertexShaderGprAllocationEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska13ObjectManager28GetVertexShaderGprAllocationEv(void)

{
  return 0x40;
}

// ==== Aska::ObjectManager::WaitBackBufferSync()
// vaddr 0x2167d7c | ghidra 0x2267d7c | size 4 | symbol _ZN4Aska13ObjectManager18WaitBackBufferSyncEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13ObjectManager18WaitBackBufferSyncEv(void)

{
  return;
}

// ==== Aska::ObjectManager::SwapFrame()
// vaddr 0x2167d80 | ghidra 0x2267d80 | size 8 | symbol _ZN4Aska13ObjectManager9SwapFrameEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13ObjectManager9SwapFrameEv(long param_1)

{
  (*(code *)PTR__ZN4Aska12RenderThread7ReqSwapEv_02c92488)(*(undefined8 *)(param_1 + 0x4480));
  return;
}

// ==== Aska::ObjectManager::WaitGPUSync()
// vaddr 0x2167d88 | ghidra 0x2267d88 | size 44 | symbol _ZN4Aska13ObjectManager11WaitGPUSyncEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13ObjectManager11WaitGPUSyncEv(long param_1)

{
  Aska::GPUSync::WaitGPUSync()(*(undefined8 *)PTR__ZN4Aska12RenderThread10m_pGPUSyncE_02cbe328);
  *(undefined1 *)(param_1 + 0x3f10) = 0;
  return;
}

// ==== Aska::ObjectManager::AddGPUSyncNotify(Aska::INotify*)
// vaddr 0x2167db4 | ghidra 0x2267db4 | size 20 | symbol _ZN4Aska13ObjectManager16AddGPUSyncNotifyEPNS_7INotifyE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13ObjectManager16AddGPUSyncNotifyEPNS_7INotifyE(undefined8 param_1,undefined8 param_2)

{
  (*(code *)PTR__ZN4Aska14NotifierThread9AddNotifyEPNS_7INotifyEj_02ca6378)
            (*(undefined8 *)PTR__ZN4Aska12RenderThread10m_pGPUSyncE_02cbe328,param_2,0);
  return;
}

// ==== Aska::ObjectManager::RemoveGPUSyncNotify(Aska::INotify*)
// vaddr 0x2167dc8 | ghidra 0x2267dc8 | size 16 | symbol _ZN4Aska13ObjectManager19RemoveGPUSyncNotifyEPNS_7INotifyE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13ObjectManager19RemoveGPUSyncNotifyEPNS_7INotifyE(void)

{
  (*(code *)PTR__ZN4Aska14NotifierThread12RemoveNotifyEPNS_7INotifyE_02cb3518)
            (*(undefined8 *)PTR__ZN4Aska12RenderThread10m_pGPUSyncE_02cbe328);
  return;
}

// ==== Aska::ObjectManager::QueryGPUSyncNotify(Aska::INotify*)
// vaddr 0x2167dd8 | ghidra 0x2267dd8 | size 16 | symbol _ZN4Aska13ObjectManager18QueryGPUSyncNotifyEPNS_7INotifyE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13ObjectManager18QueryGPUSyncNotifyEPNS_7INotifyE(void)

{
  (*(code *)PTR__ZN4Aska14NotifierThread11QueryNotifyEPNS_7INotifyE_02c99b60)
            (*(undefined8 *)PTR__ZN4Aska12RenderThread10m_pGPUSyncE_02cbe328);
  return;
}

// ==== Aska::ObjectManager::IsGPUBusy()
// vaddr 0x2167de8 | ghidra 0x2267de8 | size 20 | symbol _ZN4Aska13ObjectManager9IsGPUBusyEv | lib libSOA-3.7.0.so | 2026-10-04
undefined1 _ZN4Aska13ObjectManager9IsGPUBusyEv(void)

{
  return *(undefined1 *)(*(long *)PTR__ZN4Aska12RenderThread10m_pGPUSyncE_02cbe328 + 0xb8);
}

// ==== Aska::ObjectManager::GetNoTexture() const
// vaddr 0x2167dfc | ghidra 0x2267dfc | size 20 | symbol _ZNK4Aska13ObjectManager12GetNoTextureEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska13ObjectManager12GetNoTextureEv(long param_1)

{
  return *(undefined8 *)(*(long *)(param_1 + 0x4480) + 0x501e8);
}

// ==== Aska::ObjectManager::Get(unsigned long, void*) const
// vaddr 0x2167e10 | ghidra 0x2267e10 | size 188 | symbol _ZNK4Aska13ObjectManager3GetEmPv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska13ObjectManager3GetEmPv(long param_1,undefined8 param_2,uint *param_3)

{
  undefined8 uVar1;
  byte bVar2;
  uint uVar3;
  long lVar5;
  byte *pbVar4;
  
  if ((short)((ulong)param_2 >> 0x20) != 0) {
    return 0;
  }
  uVar1 = 0;
  switch((uint)param_2 & 0xffff) {
  case 0x15:
    lVar5 = 0x3f0b;
    goto code_r0x02267ebc;
  case 0x16:
    uVar3 = *(uint *)(param_1 + 0x3f24);
    break;
  default:
    goto code_r0x02267ec8;
  case 0x1f:
  case 0x20:
    uVar3 = 0x40;
    break;
  case 0x32:
    uVar3 = *(uint *)(param_1 + 0x45e8);
    break;
  case 0x3a:
    uVar3 = *(uint *)(param_1 + 0x3f18);
    break;
  case 0x3b:
    pbVar4 = PTR__ZN4Aska13ObjectManager20m_LightConfigurationE_02cbf638;
    goto code_r0x02267e9c;
  case 0x3c:
    uVar3 = *(uint *)PTR__ZN4Aska13ObjectManager17m_fGlobalHDRRangeE_02cbb9f0;
    break;
  case 0x3d:
    pbVar4 = PTR__ZN4Aska13ObjectManager19m_ucGammaCorrectionE_02cc1f30;
code_r0x02267e9c:
    uVar3 = (uint)*pbVar4;
    break;
  case 0x42:
    bVar2 = *(byte *)(*(long *)(param_1 + 0x45c8) + 0x308) ^ 1;
    goto code_r0x02267ec0;
  case 0x43:
    lVar5 = 0x3f1d;
code_r0x02267ebc:
    bVar2 = *(byte *)(param_1 + lVar5);
code_r0x02267ec0:
    *(byte *)param_3 = bVar2;
    goto code_r0x02267ec4;
  }
  *param_3 = uVar3;
code_r0x02267ec4:
  uVar1 = 1;
code_r0x02267ec8:
  return uVar1;
}

// ==== non-virtual thunk to Aska::ObjectManager::Get(unsigned long, void*) const
// vaddr 0x2167ecc | ghidra 0x2267ecc | size 192 | symbol _ZThn40_NK4Aska13ObjectManager3GetEmPv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZThn40_NK4Aska13ObjectManager3GetEmPv(long param_1,undefined8 param_2,uint *param_3)

{
  undefined8 uVar1;
  byte bVar2;
  uint uVar3;
  long lVar5;
  byte *pbVar4;
  
  if ((short)((ulong)param_2 >> 0x20) != 0) {
    return 0;
  }
  uVar3 = (uint)param_2 & 0xffff;
  uVar1 = 0;
  if (0x2e < uVar3 - 0x15) {
    return 0;
  }
  switch(uVar3) {
  case 0x15:
    lVar5 = 0x3f0b;
    goto code_r0x02267f7c;
  case 0x16:
    uVar3 = *(uint *)(param_1 + 0x3efc);
    break;
  default:
    goto code_r0x02267f88;
  case 0x1f:
  case 0x20:
    uVar3 = 0x40;
    break;
  case 0x32:
    uVar3 = *(uint *)(param_1 + 0x45c0);
    break;
  case 0x3a:
    uVar3 = *(uint *)(param_1 + 0x3ef0);
    break;
  case 0x3b:
    pbVar4 = PTR__ZN4Aska13ObjectManager20m_LightConfigurationE_02cbf638;
    goto code_r0x02267f5c;
  case 0x3c:
    uVar3 = *(uint *)PTR__ZN4Aska13ObjectManager17m_fGlobalHDRRangeE_02cbb9f0;
    break;
  case 0x3d:
    pbVar4 = PTR__ZN4Aska13ObjectManager19m_ucGammaCorrectionE_02cc1f30;
code_r0x02267f5c:
    uVar3 = (uint)*pbVar4;
    break;
  case 0x42:
    bVar2 = *(byte *)(*(long *)(param_1 + 0x45a0) + 0x308) ^ 1;
    goto code_r0x02267f80;
  case 0x43:
    lVar5 = 0x3f1d;
code_r0x02267f7c:
    bVar2 = *(byte *)(param_1 + -0x28 + lVar5);
code_r0x02267f80:
    *(byte *)param_3 = bVar2;
    goto code_r0x02267f84;
  }
  *param_3 = uVar3;
code_r0x02267f84:
  uVar1 = 1;
code_r0x02267f88:
  return uVar1;
}

// ==== Aska::ObjectManager::Set(unsigned long, void const*)
// vaddr 0x2167f8c | ghidra 0x2267f8c | size 212 | symbol _ZN4Aska13ObjectManager3SetEmPKv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska13ObjectManager3SetEmPKv(long param_1,undefined8 param_2,byte *param_3)

{
  undefined8 uVar1;
  byte bVar2;
  long lVar3;
  
  if ((short)((ulong)param_2 >> 0x20) != 0) {
    return 0;
  }
  uVar1 = 0;
  switch((uint)param_2 & 0xffff) {
  case 0x15:
    bVar2 = *param_3;
    lVar3 = 0x3f0b;
    goto code_r0x02268054;
  case 0x16:
    *(undefined4 *)(param_1 + 0x3f24) = *(undefined4 *)param_3;
    break;
  default:
    goto code_r0x0226805c;
  case 0x1f:
    break;
  case 0x32:
    *(undefined4 *)(param_1 + 0x45e8) = *(undefined4 *)param_3;
    break;
  case 0x3a:
    *(undefined4 *)(param_1 + 0x3f18) = *(undefined4 *)param_3;
    break;
  case 0x3b:
    *PTR__ZN4Aska13ObjectManager20m_LightConfigurationE_02cbf638 = (char)*(undefined4 *)param_3;
    break;
  case 0x3c:
    *(undefined4 *)PTR__ZN4Aska13ObjectManager17m_fGlobalHDRRangeE_02cbb9f0 = *(undefined4 *)param_3
    ;
    break;
  case 0x3d:
    *PTR__ZN4Aska13ObjectManager19m_ucGammaCorrectionE_02cc1f30 = (char)*(undefined4 *)param_3;
    break;
  case 0x42:
    *(byte *)(*(long *)(param_1 + 0x45c8) + 0x308) = *param_3 ^ 1;
    break;
  case 0x43:
    bVar2 = *param_3;
    lVar3 = 0x3f1d;
code_r0x02268054:
    *(byte *)(param_1 + lVar3) = bVar2;
  }
  uVar1 = 1;
code_r0x0226805c:
  return uVar1;
}

// ==== non-virtual thunk to Aska::ObjectManager::Set(unsigned long, void const*)
// vaddr 0x2169060 | ghidra 0x2269060 | size 216 | symbol _ZThn40_N4Aska13ObjectManager3SetEmPKv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZThn40_N4Aska13ObjectManager3SetEmPKv(long param_1,undefined8 param_2,byte *param_3)

{
  uint uVar1;
  undefined8 uVar2;
  byte bVar3;
  long lVar4;
  
  if ((short)((ulong)param_2 >> 0x20) != 0) {
    return 0;
  }
  uVar1 = (uint)param_2 & 0xffff;
  uVar2 = 0;
  if (0x2e < uVar1 - 0x15) {
    return 0;
  }
  switch(uVar1) {
  case 0x15:
    bVar3 = *param_3;
    lVar4 = 0x3f0b;
    goto code_r0x0226912c;
  case 0x16:
    *(undefined4 *)(param_1 + 0x3efc) = *(undefined4 *)param_3;
    break;
  default:
    goto code_r0x02269134;
  case 0x1f:
    break;
  case 0x32:
    *(undefined4 *)(param_1 + 0x45c0) = *(undefined4 *)param_3;
    break;
  case 0x3a:
    *(undefined4 *)(param_1 + 0x3ef0) = *(undefined4 *)param_3;
    break;
  case 0x3b:
    *PTR__ZN4Aska13ObjectManager20m_LightConfigurationE_02cbf638 = (char)*(undefined4 *)param_3;
    break;
  case 0x3c:
    *(undefined4 *)PTR__ZN4Aska13ObjectManager17m_fGlobalHDRRangeE_02cbb9f0 = *(undefined4 *)param_3
    ;
    break;
  case 0x3d:
    *PTR__ZN4Aska13ObjectManager19m_ucGammaCorrectionE_02cc1f30 = (char)*(undefined4 *)param_3;
    break;
  case 0x42:
    *(byte *)(*(long *)(param_1 + 0x45a0) + 0x308) = *param_3 ^ 1;
    break;
  case 0x43:
    bVar3 = *param_3;
    lVar4 = 0x3f1d;
code_r0x0226912c:
    *(byte *)(param_1 + -0x28 + lVar4) = bVar3;
  }
  uVar2 = 1;
code_r0x02269134:
  return uVar2;
}

// ==== Aska::ObjectManager::BackBufferSyncCallback(unsigned long, unsigned long)
// vaddr 0x216924c | ghidra 0x226924c | size 20 | symbol _ZN4Aska13ObjectManager22BackBufferSyncCallbackEmm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13ObjectManager22BackBufferSyncCallbackEmm(void)

{
  (*(code *)PTR__ZNK4Aska9Semaphore6SignalEv_02c96cd0)
            (*(long *)PTR__ZN4Aska13ObjectManager17m_pBackBufferSyncE_02cb8770 + 0x58);
  return;
}

// ==== Aska::ObjectManager::ProfileCallBack(unsigned long, unsigned long)
// vaddr 0x2169260 | ghidra 0x2269260 | size 156 | symbol _ZN4Aska13ObjectManager15ProfileCallBackEmm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13ObjectManager15ProfileCallBackEmm(undefined8 param_1)

{
  undefined8 uVar1;
  undefined8 uVar2;
  
  switch(param_1) {
  case 1:
    uVar2 = 8;
    uVar1 = *(undefined8 *)PTR__ZN4Aska6Global21m_pPerformanceCounterE_02cc3ad8;
    break;
  case 2:
    uVar2 = 8;
    uVar1 = *(undefined8 *)PTR__ZN4Aska6Global21m_pPerformanceCounterE_02cc3ad8;
    goto code_r0x011d9890;
  case 3:
    uVar2 = 9;
    uVar1 = *(undefined8 *)PTR__ZN4Aska6Global21m_pPerformanceCounterE_02cc3ad8;
    break;
  case 4:
    uVar2 = 9;
    uVar1 = *(undefined8 *)PTR__ZN4Aska6Global21m_pPerformanceCounterE_02cc3ad8;
    goto code_r0x011d9890;
  case 5:
    uVar2 = 10;
    uVar1 = *(undefined8 *)PTR__ZN4Aska6Global21m_pPerformanceCounterE_02cc3ad8;
    break;
  case 6:
    uVar2 = 10;
    uVar1 = *(undefined8 *)PTR__ZN4Aska6Global21m_pPerformanceCounterE_02cc3ad8;
code_r0x011d9890:
    (*(code *)PTR__ZN4Aska18PerformanceCounter3SetEi_02ca4c38)(uVar1,uVar2);
    return;
  default:
    return;
  }
  (*(code *)PTR__ZN4Aska18PerformanceCounter4MarkEi_02c9c9c0)(uVar1,uVar2);
  return;
}

// ==== Aska::ObjectManager::GetPassFormat(int) const
// vaddr 0x21692fc | ghidra 0x22692fc | size 120 | symbol _ZNK4Aska13ObjectManager13GetPassFormatEi | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK4Aska13ObjectManager13GetPassFormatEi(long param_1,uint param_2)

{
  long lVar1;
  undefined4 *puVar2;
  
  if (param_2 == 0) {
    puVar2 = (undefined4 *)(param_1 + 0xb3f8);
  }
  else if ((*(char *)(param_1 + ((long)(int)param_2 + -1) * 0x48 + 0x4632) < '\0') &&
          (lVar1 = Aska::RenderTargetManagerGL::GetRenderTarget(unsigned int)(*(undefined8 *)
                                    PTR__ZN4Aska6Global22m_pRenderTargetManagerE_02cbfa00,
                                   param_2 | 0x1000000), lVar1 != 0)) {
    puVar2 = (undefined4 *)(lVar1 + 0x54);
  }
  else {
    puVar2 = (undefined4 *)(param_1 + ((long)(int)param_2 + -1) * 0x48 + 0x45f8);
  }
  return *puVar2;
}

// ==== Aska::ObjectManager::GetClassID(int) const
// vaddr 0x21693fc | ghidra 0x22693fc | size 88 | symbol _ZNK4Aska13ObjectManager10GetClassIDEi | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska13ObjectManager10GetClassIDEi(undefined8 param_1,int param_2)

{
  undefined8 uVar1;
  undefined8 uVar2;
  
  if (param_2 == 0) {
    return 0xf002f003f00a;
  }
  if (param_2 == 1) {
    return 0xf002f003;
  }
  uVar2 = 0xf000f001;
  if (param_2 != 3) {
    uVar2 = 0xf000;
  }
  uVar1 = 0xf000f001f002;
  if (param_2 != 2) {
    uVar1 = uVar2;
  }
  return uVar1;
}

// ==== non-virtual thunk to Aska::ObjectManager::GetClassID(int) const
// vaddr 0x2169454 | ghidra 0x2269454 | size 88 | symbol _ZThn40_NK4Aska13ObjectManager10GetClassIDEi | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZThn40_NK4Aska13ObjectManager10GetClassIDEi(undefined8 param_1,int param_2)

{
  undefined8 uVar1;
  undefined8 uVar2;
  
  if (param_2 == 0) {
    return 0xf002f003f00a;
  }
  if (param_2 == 1) {
    return 0xf002f003;
  }
  uVar2 = 0xf000f001;
  if (param_2 != 3) {
    uVar2 = 0xf000;
  }
  uVar1 = 0xf000f001f002;
  if (param_2 != 2) {
    uVar1 = uVar2;
  }
  return uVar1;
}

// ==== Aska::ObjectManagerWorkerThread::ObjectManagerWorkerThread()
// vaddr 0x216a048 | ghidra 0x226a048 | size 108 | symbol _ZN4Aska25ObjectManagerWorkerThreadC2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska25ObjectManagerWorkerThreadC1Ev(long *param_1)

{
  Aska::Thread::Thread()();
  *param_1 = (long)(PTR__ZTVN4Aska25ObjectManagerWorkerThreadE_02cbf0f8 + 0x10);
  Aska::Event::Event()(param_1 + 3);
  Aska::FastCriticalSection::FastCriticalSection()(param_1 + 0x10);
  *(undefined4 *)(param_1 + 0x22) = 7;
  *(undefined1 *)((long)param_1 + 0x119) = 0;
  param_1[0x25] = 0;
  param_1[0x26] = 0;
  *(undefined1 *)(param_1 + 0x23) = 0;
  *(undefined1 *)((long)param_1 + 0x11a) = 1;
  *(undefined1 *)((long)param_1 + 0x11b) = 0;
  *(undefined4 *)((long)param_1 + 0x11c) = 0;
  *(int *)((long)param_1 + 0x114) = (int)param_1[0x22];
  param_1[0x2b] = 0;
  *(undefined4 *)((long)param_1 + 0x15c) = 0xffffffff;
  return;
}

// ==== Aska::ObjectManagerWorkerThread::~ObjectManagerWorkerThread()
// vaddr 0x216a0b4 | ghidra 0x226a0b4 | size 80 | symbol _ZN4Aska25ObjectManagerWorkerThreadD1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska25ObjectManagerWorkerThreadD2Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska25ObjectManagerWorkerThreadE_02cbf0f8 + 0x10);
  *(undefined1 *)((long)param_1 + 0x11b) = 1;
  Aska::Event::Set() const(param_1 + 3);
  Aska::FastCriticalSection::~FastCriticalSection()(param_1 + 0x10);
  Aska::Event::Exit()(param_1 + 3);
  (*(code *)PTR__ZN4Aska6ThreadD1Ev_02c9be08)(param_1);
  return;
}

// ==== Aska::ObjectManagerWorkerThread::~ObjectManagerWorkerThread()
// vaddr 0x216a104 | ghidra 0x226a104 | size 88 | symbol _ZN4Aska25ObjectManagerWorkerThreadD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska25ObjectManagerWorkerThreadD0Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska25ObjectManagerWorkerThreadE_02cbf0f8 + 0x10);
  *(undefined1 *)((long)param_1 + 0x11b) = 1;
  Aska::Event::Set() const(param_1 + 3);
  Aska::FastCriticalSection::~FastCriticalSection()(param_1 + 0x10);
  Aska::Event::Exit()(param_1 + 3);
  Aska::Thread::~Thread()(param_1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::ObjectManagerWorkerThread::Initialize(int)
// vaddr 0x216a15c | ghidra 0x226a15c | size 68 | symbol _ZN4Aska25ObjectManagerWorkerThread10InitializeEi | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska25ObjectManagerWorkerThread10InitializeEi(long param_1)

{
  undefined8 uVar1;
  ulong uVar2;
  
  uVar2 = Aska::Event::Create(bool, bool)(param_1 + 0x18,0,0);
  if ((uVar2 & 1) != 0) {
    uVar1 = (*(code *)PTR__ZN4Aska6Thread6CreateEbiib_02c95600)(param_1,0,0xa0,0x20000,1);
    return uVar1;
  }
  return 0;
}

// ==== Aska::ObjectManagerWorkerThread::Handler()
// vaddr 0x216a1a0 | ghidra 0x226a1a0 | size 796 | symbol _ZN4Aska25ObjectManagerWorkerThread7HandlerEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska25ObjectManagerWorkerThread7HandlerEv(long param_1)

{
  ulong *puVar1;
  long lVar2;
  int *piVar3;
  int *piVar4;
  long lVar5;
  int iVar6;
  long lVar7;
  int iVar8;
  char cVar9;
  bool bVar10;
  int iVar11;
  ulong uVar12;
  long *plVar13;
  int iVar14;
  long lVar15;
  long lVar16;
  
  lVar2 = param_1 + 0x18;
  Aska::Event::Reset() const(lVar2);
  piVar3 = (int *)(param_1 + 0xb8);
  piVar4 = (int *)(param_1 + 0xbc);
  lVar5 = param_1 + 0xf8;
code_r0x0226a1e0:
  iVar14 = 0;
code_r0x0226a29c:
  do {
    if (*piVar3 != -1) goto code_r0x0226a28c;
    cVar9 = '\x01';
    bVar10 = (bool)ExclusiveMonitorPass(piVar3,0x10);
    if (bVar10) {
      *piVar3 = 0;
      cVar9 = ExclusiveMonitorsStatus();
    }
  } while (cVar9 != '\0');
  goto code_r0x0226a2b0;
code_r0x0226a28c:
  ClearExclusiveLocal();
  bVar10 = iVar14 < 0x1ff;
  iVar14 = iVar14 + 1;
  if (bVar10) goto code_r0x0226a29c;
  do {
    cVar9 = '\x01';
    bVar10 = (bool)ExclusiveMonitorPass(piVar4,0x10);
    if (bVar10) {
      *piVar4 = *piVar4 + 1;
      cVar9 = ExclusiveMonitorsStatus();
    }
  } while (cVar9 != '\0');
  do {
    if (*piVar3 != -1) {
      do {
        ClearExclusiveLocal();
        uVar12 = Aska::Semaphore::IsReady() const(lVar5);
        if ((uVar12 & 1) == 0) {
          do {
            cVar9 = '\x01';
            bVar10 = (bool)ExclusiveMonitorPass(piVar4,0x10);
            if (bVar10) {
              *piVar4 = *piVar4 + -1;
              cVar9 = ExclusiveMonitorsStatus();
            }
          } while (cVar9 != '\0');
          Aska::Thread::Sleep(unsigned int)(1);
        }
        else {
          Aska::Semaphore::Wait() const(lVar5);
        }
        do {
          cVar9 = '\x01';
          bVar10 = (bool)ExclusiveMonitorPass(piVar4,0x10);
          if (bVar10) {
            *piVar4 = *piVar4 + 1;
            cVar9 = ExclusiveMonitorsStatus();
          }
        } while (cVar9 != '\0');
        while (*piVar3 == -1) {
          cVar9 = '\x01';
          bVar10 = (bool)ExclusiveMonitorPass(piVar3,0x10);
          if (bVar10) {
            *piVar3 = 0;
            cVar9 = ExclusiveMonitorsStatus();
          }
          if (cVar9 == '\0') goto code_r0x0226a278;
        }
      } while( true );
    }
    cVar9 = '\x01';
    bVar10 = (bool)ExclusiveMonitorPass(piVar3,0x10);
    if (bVar10) {
      *piVar3 = 0;
      cVar9 = ExclusiveMonitorsStatus();
    }
  } while (cVar9 != '\0');
code_r0x0226a278:
  do {
    cVar9 = '\x01';
    bVar10 = (bool)ExclusiveMonitorPass(piVar4,0x10);
    if (bVar10) {
      *piVar4 = *piVar4 + -1;
      cVar9 = ExclusiveMonitorsStatus();
    }
  } while (cVar9 != '\0');
code_r0x0226a2b0:
  DataMemoryBarrier(2,3);
  if (*(char *)(param_1 + 0x119) != '\0') {
    *(undefined1 *)(param_1 + 0x118) = 0;
    if (0 < *(int *)(param_1 + 0x11c)) {
      Aska::Event::Set() const(lVar2);
    }
    *(undefined4 *)(param_1 + 0x110) = *(undefined4 *)(param_1 + 0x114);
    *(undefined4 *)(param_1 + 0x114) = 0xffffffff;
    *(undefined1 *)(param_1 + 0x119) = 0;
  }
  DataMemoryBarrier(2,3);
  *piVar3 = -1;
  DataMemoryBarrier(2,3);
  if (0x14 < *piVar4) {
    do {
      cVar9 = '\x01';
      bVar10 = (bool)ExclusiveMonitorPass(piVar4,0x10);
      if (bVar10) {
        *piVar4 = *piVar4 + -1;
        cVar9 = ExclusiveMonitorsStatus();
      }
    } while (cVar9 != '\0');
    uVar12 = Aska::Semaphore::IsReady() const(lVar5);
    if ((uVar12 & 1) != 0) {
      Aska::Semaphore::Signal() const(lVar5);
    }
  }
  switch(*(undefined4 *)(param_1 + 0x110)) {
  case 1:
    Aska::ObjectManagerWorkerThread::Handler_MakePaintingList()(param_1);
    iVar14 = 0;
    goto code_r0x0226a29c;
  case 2:
    do {
      *(undefined1 *)(param_1 + 0x118) = 1;
      Aska::Event::Wait(unsigned int) const(lVar2,0);
      DataMemoryBarrier(2,3);
      if (*(int *)(param_1 + 0x11c) == 2) {
        iVar14 = *(int *)(param_1 + 0x168);
        iVar8 = *(int *)(param_1 + 0x16c);
        lVar16 = *(long *)(param_1 + 0x160);
        lVar15 = (long)iVar14;
        if (iVar14 <= iVar8) {
          do {
            plVar13 = *(long **)(lVar16 + (lVar15 - iVar14) * 8);
            iVar6 = (int)(uint)lVar15 >> 5;
            iVar11 = ((uint)lVar15 & 0x1f) << 1;
            if ((*(byte *)((long)plVar13 + 0x1b5) & 1) == 0) {
              uVar12 = (**(code **)(*plVar13 + 0x278))(plVar13,*(undefined8 *)(param_1 + 0x138));
              lVar7 = 2;
              if ((uVar12 & 1) == 0) {
                lVar7 = 3;
              }
              puVar1 = (ulong *)(*(long *)(param_1 + 0x140) + (long)iVar6 * 8);
              do {
                cVar9 = '\x01';
                bVar10 = (bool)ExclusiveMonitorPass(puVar1,0x10);
                if (bVar10) {
                  *puVar1 = *puVar1 | lVar7 << iVar11;
                  cVar9 = ExclusiveMonitorsStatus();
                }
              } while (cVar9 != '\0');
            }
            else {
              puVar1 = (ulong *)(*(long *)(param_1 + 0x140) + (long)iVar6 * 8);
              do {
                cVar9 = '\x01';
                bVar10 = (bool)ExclusiveMonitorPass(puVar1,0x10);
                if (bVar10) {
                  *puVar1 = *puVar1 | 1L << iVar11;
                  cVar9 = ExclusiveMonitorsStatus();
                }
              } while (cVar9 != '\0');
            }
            bVar10 = lVar15 < iVar8;
            lVar15 = lVar15 + 1;
          } while (bVar10);
        }
        *(undefined4 *)(param_1 + 0x11c) = 0;
      }
    } while (*(char *)(param_1 + 0x119) == '\0');
    break;
  case 3:
    Aska::ObjectManagerWorkerThread::Handler_PrepareForRendering()(param_1);
    iVar14 = 0;
    goto code_r0x0226a29c;
  case 4:
    Aska::ObjectManagerWorkerThread::Handler_ViewFrustumCulling()(param_1);
    iVar14 = 0;
    goto code_r0x0226a29c;
  case 5:
    goto code_r0x0226a440;
  case 6:
    Aska::ObjectManagerWorkerThread::Handler_ResetSystemFlags()(param_1);
    iVar14 = 0;
    goto code_r0x0226a29c;
  case 7:
    *(undefined1 *)(param_1 + 0x118) = 1;
    Aska::Event::Wait(unsigned int) const(lVar2,0);
    if (*(char *)(param_1 + 0x11b) != '\0') {
      return;
    }
  default:
    break;
  }
  goto code_r0x0226a1e0;
code_r0x0226a440:
  do {
    *(undefined1 *)(param_1 + 0x118) = 1;
    Aska::Event::Wait(unsigned int) const(lVar2,0);
    DataMemoryBarrier(2,3);
    if (*(int *)(param_1 + 0x11c) == 5) {
      Aska::ObjectManager::DetectLIBL(Aska::RenderableObject**, int, int)(*(undefined8 *)(param_1 + 0x130),*(undefined8 *)(param_1 + 0x200),
                      *(undefined4 *)(param_1 + 0x208),*(undefined4 *)(param_1 + 0x20c));
      *(undefined4 *)(param_1 + 0x11c) = 0;
    }
  } while (*(char *)(param_1 + 0x119) == '\0');
  goto code_r0x0226a1e0;
}

// ==== Aska::ObjectManagerWorkerThread::Handler_MakePaintingList()
// vaddr 0x216a4bc | ghidra 0x226a4bc | size 164 | symbol _ZN4Aska25ObjectManagerWorkerThread24Handler_MakePaintingListEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska25ObjectManagerWorkerThread24Handler_MakePaintingListEv(long param_1)

{
  do {
    *(undefined1 *)(param_1 + 0x118) = 1;
    Aska::Event::Wait(unsigned int) const(param_1 + 0x18,0);
    DataMemoryBarrier(2,3);
    if (*(int *)(param_1 + 0x11c) == 1) {
      switch(*(undefined4 *)(param_1 + 0x158)) {
      case 0:
        Aska::ObjectManager::MakePaintingList(int)(*(undefined8 *)(param_1 + 0x130));
        break;
      case 1:
        Aska::ObjectManager::MakePaintingListMultipass(int)(*(undefined8 *)(param_1 + 0x130));
        break;
      case 2:
        Aska::ObjectManager::MakePaintingListShadow(int)(*(undefined8 *)(param_1 + 0x130));
        break;
      case 3:
        Aska::ObjectManager::MakePaintingListPost()(*(undefined8 *)(param_1 + 0x130),*(undefined4 *)(param_1 + 0x15c));
      }
      *(undefined4 *)(param_1 + 0x11c) = 0;
    }
  } while (*(char *)(param_1 + 0x119) == '\0');
  return;
}

// ==== Aska::ObjectManagerWorkerThread::Handler_PreliminarilyPrepare()
// vaddr 0x216a560 | ghidra 0x226a560 | size 256 | symbol _ZN4Aska25ObjectManagerWorkerThread28Handler_PreliminarilyPrepareEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska25ObjectManagerWorkerThread28Handler_PreliminarilyPrepareEv(long param_1)

{
  ulong *puVar1;
  int iVar2;
  long lVar3;
  int iVar4;
  int iVar5;
  char cVar6;
  bool bVar7;
  int iVar8;
  long *plVar9;
  ulong uVar10;
  long lVar11;
  long lVar12;
  
  do {
    *(undefined1 *)(param_1 + 0x118) = 1;
    Aska::Event::Wait(unsigned int) const(param_1 + 0x18,0);
    DataMemoryBarrier(2,3);
    if (*(int *)(param_1 + 0x11c) == 2) {
      iVar4 = *(int *)(param_1 + 0x168);
      iVar5 = *(int *)(param_1 + 0x16c);
      lVar11 = *(long *)(param_1 + 0x160);
      lVar12 = (long)iVar4;
      if (iVar4 <= iVar5) {
        do {
          plVar9 = *(long **)(lVar11 + (lVar12 - iVar4) * 8);
          iVar2 = (int)(uint)lVar12 >> 5;
          iVar8 = ((uint)lVar12 & 0x1f) << 1;
          if ((*(byte *)((long)plVar9 + 0x1b5) & 1) == 0) {
            uVar10 = (**(code **)(*plVar9 + 0x278))(plVar9,*(undefined8 *)(param_1 + 0x138));
            lVar3 = 2;
            if ((uVar10 & 1) == 0) {
              lVar3 = 3;
            }
            puVar1 = (ulong *)(*(long *)(param_1 + 0x140) + (long)iVar2 * 8);
            do {
              cVar6 = '\x01';
              bVar7 = (bool)ExclusiveMonitorPass(puVar1,0x10);
              if (bVar7) {
                *puVar1 = *puVar1 | lVar3 << iVar8;
                cVar6 = ExclusiveMonitorsStatus();
              }
            } while (cVar6 != '\0');
          }
          else {
            puVar1 = (ulong *)(*(long *)(param_1 + 0x140) + (long)iVar2 * 8);
            do {
              cVar6 = '\x01';
              bVar7 = (bool)ExclusiveMonitorPass(puVar1,0x10);
              if (bVar7) {
                *puVar1 = *puVar1 | 1L << iVar8;
                cVar6 = ExclusiveMonitorsStatus();
              }
            } while (cVar6 != '\0');
          }
          bVar7 = lVar12 < iVar5;
          lVar12 = lVar12 + 1;
        } while (bVar7);
      }
      *(undefined4 *)(param_1 + 0x11c) = 0;
    }
  } while (*(char *)(param_1 + 0x119) == '\0');
  return;
}

// ==== Aska::ObjectManagerWorkerThread::Handler_PrepareForRendering()
// vaddr 0x216a660 | ghidra 0x226a660 | size 528 | symbol _ZN4Aska25ObjectManagerWorkerThread27Handler_PrepareForRenderingEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska25ObjectManagerWorkerThread27Handler_PrepareForRenderingEv(long param_1)

{
  ulong *puVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined2 uVar5;
  char cVar6;
  bool bVar7;
  int iVar8;
  long *plVar9;
  ulong uVar10;
  long lVar11;
  long lVar12;
  long lVar13;
  long lVar14;
  
  do {
    *(undefined1 *)(param_1 + 0x118) = 1;
    Aska::Event::Wait(unsigned int) const(param_1 + 0x18,0);
    DataMemoryBarrier(2,3);
    if (*(int *)(param_1 + 0x11c) == 3) {
      iVar2 = *(int *)(param_1 + 0x1a8);
      lVar12 = (long)iVar2;
      iVar3 = *(int *)(param_1 + 0x1ac);
      lVar13 = *(long *)(param_1 + 0x1a0);
      if (*(int *)(param_1 + 0x198) == 0) {
        lVar14 = lVar12;
        if (iVar2 <= iVar3) {
          do {
            plVar9 = *(long **)(lVar13 + (lVar14 - lVar12) * 8);
            iVar2 = (int)(uint)lVar14 >> 5;
            iVar8 = ((uint)lVar14 & 0x1f) << 1;
            if ((*(byte *)((long)plVar9 + 0x1b5) & 1) == 0) {
              puVar1 = (ulong *)(*(long *)(param_1 + 0x140) + (long)iVar2 * 8);
              do {
                cVar6 = '\x01';
                bVar7 = (bool)ExclusiveMonitorPass(puVar1,0x10);
                if (bVar7) {
                  *puVar1 = *puVar1 | 1L << iVar8;
                  cVar6 = ExclusiveMonitorsStatus();
                }
              } while (cVar6 != '\0');
            }
            else {
              DataMemoryBarrier(2,3);
              lVar11 = plVar9[0x3a];
              iVar4 = *(int *)((long)plVar9 + 0x1cc);
              uVar5 = 0;
              if (*(int *)((long)plVar9 + 0x1ac) != 0) {
                uVar5 = (undefined2)((int)plVar9[0x38] / *(int *)((long)plVar9 + 0x1ac));
              }
              *(undefined2 *)(param_1 + 0x176) = uVar5;
              *(long *)(param_1 + 0x178) = lVar11 + (long)iVar4 * 0x230;
              uVar10 = (**(code **)(*plVar9 + 0x280))(plVar9,param_1 + 0x170);
              lVar11 = 2;
              if ((uVar10 & 1) == 0) {
                lVar11 = 3;
              }
              puVar1 = (ulong *)(*(long *)(param_1 + 0x140) + (long)iVar2 * 8);
              do {
                cVar6 = '\x01';
                bVar7 = (bool)ExclusiveMonitorPass(puVar1,0x10);
                if (bVar7) {
                  *puVar1 = *puVar1 | lVar11 << iVar8;
                  cVar6 = ExclusiveMonitorsStatus();
                }
              } while (cVar6 != '\0');
            }
            bVar7 = lVar14 < iVar3;
            lVar14 = lVar14 + 1;
          } while (bVar7);
        }
      }
      else if ((*(int *)(param_1 + 0x198) == 1) && (lVar14 = lVar12, iVar2 <= iVar3)) {
        do {
          plVar9 = *(long **)(lVar13 + (lVar14 - lVar12) * 8);
          iVar2 = (int)(uint)lVar14 >> 5;
          iVar8 = ((uint)lVar14 & 0x1f) << 1;
          if ((*(byte *)((long)plVar9 + 0x1b5) & 1) == 0) {
            puVar1 = (ulong *)(*(long *)(param_1 + 0x140) + (long)iVar2 * 8);
            do {
              cVar6 = '\x01';
              bVar7 = (bool)ExclusiveMonitorPass(puVar1,0x10);
              if (bVar7) {
                *puVar1 = *puVar1 | 1L << iVar8;
                cVar6 = ExclusiveMonitorsStatus();
              }
            } while (cVar6 != '\0');
          }
          else {
            lVar11 = plVar9[0x34];
            if (lVar11 == 0) {
              lVar11 = *(long *)(param_1 + 400);
            }
            *(long *)(param_1 + 0x180) = lVar11;
            DataMemoryBarrier(2,3);
            lVar11 = plVar9[0x3a];
            iVar4 = *(int *)((long)plVar9 + 0x1cc);
            uVar5 = 0;
            if (*(int *)((long)plVar9 + 0x1ac) != 0) {
              uVar5 = (undefined2)((int)plVar9[0x38] / *(int *)((long)plVar9 + 0x1ac));
            }
            *(undefined2 *)(param_1 + 0x176) = uVar5;
            *(long *)(param_1 + 0x178) = lVar11 + (long)iVar4 * 0x230;
            uVar10 = (**(code **)(*plVar9 + 0x280))(plVar9,param_1 + 0x170);
            lVar11 = 2;
            if ((uVar10 & 1) == 0) {
              lVar11 = 3;
            }
            puVar1 = (ulong *)(*(long *)(param_1 + 0x140) + (long)iVar2 * 8);
            do {
              cVar6 = '\x01';
              bVar7 = (bool)ExclusiveMonitorPass(puVar1,0x10);
              if (bVar7) {
                *puVar1 = *puVar1 | lVar11 << iVar8;
                cVar6 = ExclusiveMonitorsStatus();
              }
            } while (cVar6 != '\0');
          }
          bVar7 = lVar14 < iVar3;
          lVar14 = lVar14 + 1;
        } while (bVar7);
      }
      *(undefined4 *)(param_1 + 0x11c) = 0;
    }
  } while (*(char *)(param_1 + 0x119) == '\0');
  return;
}

// ==== Aska::ObjectManagerWorkerThread::Handler_ViewFrustumCulling()
// vaddr 0x216a870 | ghidra 0x226a870 | size 232 | symbol _ZN4Aska25ObjectManagerWorkerThread26Handler_ViewFrustumCullingEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska25ObjectManagerWorkerThread26Handler_ViewFrustumCullingEv(long param_1)

{
  int iVar1;
  
  do {
    *(undefined1 *)(param_1 + 0x118) = 1;
    Aska::Event::Wait(unsigned int) const(param_1 + 0x18,0);
    DataMemoryBarrier(2,3);
    if (*(int *)(param_1 + 0x11c) == 4) {
      iVar1 = *(int *)(param_1 + 0x1c8);
      if (iVar1 == 2) {
        Aska::ObjectManager::OcclusionCulling(Aska::Camera*, int, int, bool, Aska::RenderableObject**, int, int, unsigned long*)(*(undefined8 *)(param_1 + 0x130),*(undefined8 *)(param_1 + 0x1b0),
                        *(undefined4 *)(param_1 + 0x1b8),*(undefined4 *)(param_1 + 0x1bc),0,
                        *(undefined8 *)(param_1 + 0x1c0),*(undefined4 *)(param_1 + 0x1cc),
                        *(undefined4 *)(param_1 + 0x1d0),*(undefined8 *)(param_1 + 0x140));
      }
      else if (iVar1 == 1) {
        Aska::ObjectManager::SubViewFrustumCulling(Aska::Camera*, int, int, Aska::RenderableObject**, int, int, unsigned long*)(*(undefined8 *)(param_1 + 0x130),*(undefined8 *)(param_1 + 0x1b0),
                        *(undefined4 *)(param_1 + 0x1b8),*(undefined4 *)(param_1 + 0x1bc),
                        *(undefined8 *)(param_1 + 0x1c0),*(undefined4 *)(param_1 + 0x1cc),
                        *(undefined4 *)(param_1 + 0x1d0),*(undefined8 *)(param_1 + 0x140));
      }
      else if (iVar1 == 0) {
        Aska::ObjectManager::ViewFrustumCulling(Aska::Camera*, int, int, Aska::RenderableObject**, int, int, unsigned long*)(*(undefined8 *)(param_1 + 0x130),*(undefined8 *)(param_1 + 0x1b0),
                        *(undefined4 *)(param_1 + 0x1b8),*(undefined4 *)(param_1 + 0x1bc),
                        *(undefined8 *)(param_1 + 0x1c0),*(undefined4 *)(param_1 + 0x1cc),
                        *(undefined4 *)(param_1 + 0x1d0),*(undefined8 *)(param_1 + 0x140));
      }
      *(undefined4 *)(param_1 + 0x11c) = 0;
    }
  } while (*(char *)(param_1 + 0x119) == '\0');
  return;
}

// ==== Aska::ObjectManagerWorkerThread::Handler_DetectLIBL()
// vaddr 0x216a958 | ghidra 0x226a958 | size 96 | symbol _ZN4Aska25ObjectManagerWorkerThread18Handler_DetectLIBLEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska25ObjectManagerWorkerThread18Handler_DetectLIBLEv(long param_1)

{
  do {
    *(undefined1 *)(param_1 + 0x118) = 1;
    Aska::Event::Wait(unsigned int) const(param_1 + 0x18,0);
    DataMemoryBarrier(2,3);
    if (*(int *)(param_1 + 0x11c) == 5) {
      Aska::ObjectManager::DetectLIBL(Aska::RenderableObject**, int, int)(*(undefined8 *)(param_1 + 0x130),*(undefined8 *)(param_1 + 0x200),
                      *(undefined4 *)(param_1 + 0x208),*(undefined4 *)(param_1 + 0x20c));
      *(undefined4 *)(param_1 + 0x11c) = 0;
    }
  } while (*(char *)(param_1 + 0x119) == '\0');
  return;
}

// ==== Aska::ObjectManagerWorkerThread::Handler_ResetSystemFlags()
// vaddr 0x216a9b8 | ghidra 0x226a9b8 | size 332 | symbol _ZN4Aska25ObjectManagerWorkerThread24Handler_ResetSystemFlagsEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska25ObjectManagerWorkerThread24Handler_ResetSystemFlagsEv(long param_1)

{
  ushort *puVar1;
  uint uVar2;
  long lVar3;
  long *plVar4;
  long *plVar5;
  
  do {
    *(undefined1 *)(param_1 + 0x118) = 1;
    Aska::Event::Wait(unsigned int) const(param_1 + 0x18,0);
    DataMemoryBarrier(2,3);
    if (*(int *)(param_1 + 0x11c) == 6) {
      lVar3 = *(long *)PTR__ZN4Aska6Global16m_pObjectManagerE_02cc4688;
      plVar4 = *(long **)(param_1 + 0x148);
      plVar5 = *(long **)(param_1 + 0x150);
      do {
        puVar1 = (ushort *)((long)plVar4 + 0x1b5);
        *(uint *)(plVar4 + 0x33) = *(uint *)(plVar4 + 0x33) & 0xdfffffbf;
        *puVar1 = *puVar1 & 0xfefe;
        *(undefined4 *)((long)plVar4 + 0x1ac) = 0;
        plVar4[0x3a] = 0;
        *(undefined4 *)((long)plVar4 + 0x1cc) = 0;
        (**(code **)(*plVar4 + 0x198))(plVar4);
        plVar4[0x47] = 0;
        plVar4[0x46] = 0;
        plVar4[0x40] = 0;
        plVar4[0x3f] = 0;
        plVar4[0x3e] = 0;
        plVar4[0x3d] = 0;
        *puVar1 = *puVar1 & 0xfff9;
        uVar2 = *(uint *)(plVar4 + 0x33);
        *(uint *)(plVar4 + 0x33) = uVar2 | 0x124;
        if ((uVar2 & 0x6081) != 0) {
          if ((uVar2 >> 0x19 & 1) != 0) {
            (**(code **)(*plVar4 + 0x1f0))(plVar4);
          }
          if ((uVar2 >> 0x15 & 1) != 0) {
            (**(code **)(*plVar4 + 0x298))(plVar4);
          }
        }
      } while ((plVar4 != plVar5) && (plVar4 = (long *)plVar4[2], (long *)(lVar3 + 8) != plVar4));
      *(undefined4 *)(param_1 + 0x11c) = 0;
    }
  } while (*(char *)(param_1 + 0x119) == '\0');
  return;
}

// ==== Aska::ObjectManagerJobDispatcher::ObjectManagerJobDispatcher(Aska::ObjectManager*, int, int*)
// vaddr 0x216ab04 | ghidra 0x226ab04 | size 436 | symbol _ZN4Aska26ObjectManagerJobDispatcherC1EPNS_13ObjectManagerEiPi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska26ObjectManagerJobDispatcherC2EPNS_13ObjectManagerEiPi
               (long *param_1,long param_2,int param_3)

{
  undefined *puVar1;
  undefined1 auVar2 [16];
  ulong *puVar3;
  ulong *puVar4;
  long lVar5;
  long lVar6;
  ulong uVar7;
  
  *param_1 = (long)(PTR__ZTVN4Aska26ObjectManagerJobDispatcherE_02cb73b8 + 0x10);
  Aska::FastCriticalSection::FastCriticalSection()(param_1 + 1);
  uVar7 = (ulong)param_3;
  *(undefined4 *)((long)param_1 + 0xb4) = 0xffffffff;
  auVar2._8_8_ = 0;
  auVar2._0_8_ = uVar7;
  *(int *)((long)param_1 + 0xac) = param_3;
  *(undefined1 *)(param_1 + 0x17) = 0;
  param_1[0x14] = param_2;
  lVar5 = uVar7 * 0x210 + 8;
  if (SUB168(auVar2 * ZEXT816(0x210),8) != 0 || 0xfffffffffffffff7 < uVar7 * 0x210) {
    lVar5 = -1;
  }
  puVar3 = (ulong *)operator new[](unsigned long, std::nothrow_t const&)(lVar5,PTR__ZSt7nothrow_02cb9a80);
  puVar4 = puVar3;
  if (puVar3 != (ulong *)0x0) {
    puVar4 = puVar3 + 1;
    *puVar3 = uVar7;
    if (param_3 == 0) {
      param_1[0x13] = (long)puVar4;
      goto code_r0x0226ac98;
    }
    puVar1 = PTR__ZTVN4Aska25ObjectManagerWorkerThreadE_02cbf0f8 + 0x10;
    puVar3 = puVar4;
    do {
      Aska::Thread::Thread()(puVar3);
      *puVar3 = (ulong)puVar1;
      Aska::Event::Event()(puVar3 + 3);
      Aska::FastCriticalSection::FastCriticalSection()(puVar3 + 0x10);
      *(undefined4 *)(puVar3 + 0x22) = 7;
      *(undefined1 *)((long)puVar3 + 0x119) = 0;
      puVar3[0x25] = 0;
      puVar3[0x26] = 0;
      *(undefined1 *)(puVar3 + 0x23) = 0;
      *(undefined1 *)((long)puVar3 + 0x11a) = 1;
      *(undefined1 *)((long)puVar3 + 0x11b) = 0;
      *(undefined4 *)((long)puVar3 + 0x11c) = 0;
      *(int *)((long)puVar3 + 0x114) = (int)puVar3[0x22];
      puVar3[0x2b] = 0;
      *(undefined4 *)((long)puVar3 + 0x15c) = 0xffffffff;
      puVar3 = puVar3 + 0x42;
    } while (puVar3 != puVar4 + uVar7 * 0x42);
    param_3 = *(int *)((long)param_1 + 0xac);
  }
  param_1[0x13] = (long)puVar4;
  if (0 < param_3) {
    lVar5 = 0;
    lVar6 = 1;
    while( true ) {
      uVar7 = Aska::Event::Create(bool, bool)((long)puVar4 + lVar5 + 0x18,0,0);
      if ((uVar7 & 1) != 0) {
        Aska::Thread::Create(bool, int, int, bool)((long)puVar4 + lVar5,0,0xa0,0x20000,1);
      }
      *(long **)(param_1[0x13] + lVar5 + 0x128) = param_1;
      *(long *)(param_1[0x13] + lVar5 + 0x130) = param_2;
      if (*(int *)((long)param_1 + 0xac) <= lVar6) break;
      puVar4 = (ulong *)param_1[0x13];
      lVar5 = lVar5 + 0x210;
      lVar6 = lVar6 + 1;
    }
  }
code_r0x0226ac98:
  *(undefined4 *)(param_1 + 0x16) = 0x80;
  return;
}

// ==== Aska::ObjectManagerJobDispatcher::~ObjectManagerJobDispatcher()
// vaddr 0x216acb8 | ghidra 0x226acb8 | size 204 | symbol _ZN4Aska26ObjectManagerJobDispatcherD1Ev | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Possible PIC construction at 0x0226ad38: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0x0226ad3c) */

void _ZN4Aska26ObjectManagerJobDispatcherD2Ev(long *param_1)

{
  long lVar1;
  long lVar2;
  
  lVar1 = param_1[0x13];
  *param_1 = (long)(PTR__ZTVN4Aska26ObjectManagerJobDispatcherE_02cb73b8 + 0x10);
  if (lVar1 != 0) {
    lVar2 = *(long *)(lVar1 + -8);
    if (lVar2 != 0) {
      lVar1 = lVar1 + lVar2 * 0x210;
      *(undefined **)(lVar1 + -0x210) = PTR__ZTVN4Aska25ObjectManagerWorkerThreadE_02cbf0f8 + 0x10;
      *(undefined1 *)(lVar1 + -0xf5) = 1;
      Aska::Event::Set() const(lVar1 + -0x1f8);
      param_1 = (long *)(lVar1 + -400);
      goto code_r0x011d43e0;
    }
    operator delete[](void*)((long *)(lVar1 + -8));
    param_1[0x13] = 0;
  }
  param_1 = param_1 + 1;
code_r0x011d43e0:
  (*(code *)PTR__ZN4Aska19FastCriticalSectionD2Ev_02ca21e0)(param_1);
  return;
}

// ==== Aska::ObjectManagerJobDispatcher::~ObjectManagerJobDispatcher()
// vaddr 0x216ad84 | ghidra 0x226ad84 | size 212 | symbol _ZN4Aska26ObjectManagerJobDispatcherD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska26ObjectManagerJobDispatcherD0Ev(long *param_1)

{
  undefined *puVar1;
  long lVar2;
  long lVar3;
  long lVar4;
  long lVar5;
  
  lVar3 = param_1[0x13];
  *param_1 = (long)(PTR__ZTVN4Aska26ObjectManagerJobDispatcherE_02cb73b8 + 0x10);
  if (lVar3 != 0) {
    lVar4 = *(long *)(lVar3 + -8);
    if (lVar4 != 0) {
      lVar4 = lVar4 * 0x210;
      lVar5 = 0;
      puVar1 = PTR__ZTVN4Aska25ObjectManagerWorkerThreadE_02cbf0f8 + 0x10;
      do {
        lVar2 = lVar3 + lVar4 + lVar5;
        *(long *)(lVar2 + -0x210) = (long)puVar1;
        *(undefined1 *)(lVar2 + -0xf5) = 1;
        Aska::Event::Set() const(lVar2 + -0x1f8);
        Aska::FastCriticalSection::~FastCriticalSection()(lVar2 + -400);
        Aska::Event::Exit()(lVar2 + -0x1f8);
        Aska::Thread::~Thread()((long *)(lVar2 + -0x210));
        lVar5 = lVar5 + -0x210;
      } while (lVar4 + lVar5 != 0);
    }
    operator delete[](void*)((long *)(lVar3 + -8));
    param_1[0x13] = 0;
  }
  Aska::FastCriticalSection::~FastCriticalSection()(param_1 + 1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::ObjectManagerJobDispatcher::WaitIdle()
// vaddr 0x216ae58 | ghidra 0x226ae58 | size 272 | symbol _ZN4Aska26ObjectManagerJobDispatcher8WaitIdleEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska26ObjectManagerJobDispatcher8WaitIdleEv(long param_1)

{
  int iVar1;
  ulong uVar2;
  long lVar3;
  long lVar4;
  
  if (*(char *)(param_1 + 0xb8) != '\0') {
    do {
      iVar1 = *(int *)(param_1 + 0xac);
      if (iVar1 < 1) {
        if (iVar1 == 0) {
          return;
        }
      }
      else {
        uVar2 = 0;
        lVar3 = 0x11a;
        do {
          if ((uVar2 != *(uint *)(param_1 + 0xb4)) &&
             (*(char *)(*(long *)(param_1 + 0x98) + lVar3) != '\0')) {
            DataMemoryBarrier(2,3);
            if (*(char *)(*(long *)(param_1 + 0x98) + lVar3 + -2) == '\0') {
              if ((int)uVar2 == *(int *)(param_1 + 0xac)) {
                return;
              }
              goto code_r0x0226ae94;
            }
            iVar1 = *(int *)(param_1 + 0xac);
          }
          uVar2 = uVar2 + 1;
          lVar3 = lVar3 + 0x210;
        } while ((long)uVar2 < (long)iVar1);
        if ((int)uVar2 == iVar1) {
          return;
        }
      }
code_r0x0226ae94:
      Aska::Thread::Switch()();
    } while( true );
  }
  do {
    iVar1 = *(int *)(param_1 + 0xac);
    if (iVar1 < 1) {
      if (iVar1 == 0) {
        return;
      }
    }
    else {
      lVar3 = 0;
      lVar4 = 0x11a;
      do {
        if (*(char *)(*(long *)(param_1 + 0x98) + lVar4) != '\0') {
          DataMemoryBarrier(2,3);
          if (*(char *)(*(long *)(param_1 + 0x98) + lVar4 + -2) == '\0') {
            if ((int)lVar3 == *(int *)(param_1 + 0xac)) {
              return;
            }
            goto code_r0x0226af14;
          }
          iVar1 = *(int *)(param_1 + 0xac);
        }
        lVar3 = lVar3 + 1;
        lVar4 = lVar4 + 0x210;
      } while (lVar3 < iVar1);
      if ((int)lVar3 == iVar1) {
        return;
      }
    }
code_r0x0226af14:
    Aska::Thread::Switch()();
  } while( true );
}

// ==== Aska::ObjectManagerJobDispatcher::WaitAllIssued()
// vaddr 0x216af68 | ghidra 0x226af68 | size 200 | symbol _ZN4Aska26ObjectManagerJobDispatcher13WaitAllIssuedEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska26ObjectManagerJobDispatcher13WaitAllIssuedEv(long param_1)

{
  int iVar1;
  ulong uVar2;
  long lVar3;
  int *piVar4;
  
  if (*(char *)(param_1 + 0xb8) != '\0') {
    do {
      iVar1 = *(int *)(param_1 + 0xac);
      if (iVar1 < 1) {
        if (iVar1 == 0) {
          return;
        }
      }
      else {
        uVar2 = 0;
        lVar3 = 0x11c;
        do {
          if ((*(uint *)(param_1 + 0xb4) != uVar2) &&
             (*(int *)(*(long *)(param_1 + 0x98) + lVar3) != 0)) break;
          uVar2 = uVar2 + 1;
          lVar3 = lVar3 + 0x210;
        } while ((long)uVar2 < (long)iVar1);
        if ((int)uVar2 == iVar1) {
          return;
        }
      }
      Aska::Thread::Switch()();
    } while( true );
  }
  do {
    iVar1 = *(int *)(param_1 + 0xac);
    if (iVar1 < 1) {
      if (iVar1 == 0) {
        return;
      }
    }
    else {
      lVar3 = 0;
      piVar4 = (int *)(*(long *)(param_1 + 0x98) + 0x11c);
      do {
        if (*piVar4 != 0) break;
        lVar3 = lVar3 + 1;
        piVar4 = piVar4 + 0x84;
      } while (lVar3 < iVar1);
      if ((int)lVar3 == iVar1) {
        return;
      }
    }
    Aska::Thread::Switch()();
  } while( true );
}

// ==== Aska::ObjectManagerJobDispatcher::ChangeMode(int)
// vaddr 0x216b030 | ghidra 0x226b030 | size 560 | symbol _ZN4Aska26ObjectManagerJobDispatcher10ChangeModeEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska26ObjectManagerJobDispatcher10ChangeModeEi(long param_1,int param_2)

{
  uint uVar1;
  ulong uVar2;
  int iVar3;
  ulong uVar4;
  int *piVar5;
  long lVar6;
  int iVar7;
  long lVar8;
  
  if (*(char *)(param_1 + 0xb8) == '\0') {
    do {
      uVar1 = *(uint *)(param_1 + 0xac);
      uVar2 = (ulong)uVar1;
      if ((int)uVar1 < 1) {
        if (uVar1 == 0) goto code_r0x0226b110;
      }
      else {
        lVar6 = 0;
        piVar5 = (int *)(*(long *)(param_1 + 0x98) + 0x11c);
        do {
          if (*piVar5 != 0) break;
          lVar6 = lVar6 + 1;
          piVar5 = piVar5 + 0x84;
        } while (lVar6 < (int)uVar1);
        if ((uint)lVar6 == uVar1) goto code_r0x0226b110;
      }
      Aska::Thread::Switch()();
    } while( true );
  }
  do {
    uVar1 = *(uint *)(param_1 + 0xac);
    uVar2 = (ulong)uVar1;
    if ((int)uVar1 < 1) {
      if (uVar1 == 0) break;
    }
    else {
      uVar4 = 0;
      lVar6 = 0x11c;
      do {
        if ((*(uint *)(param_1 + 0xb4) != uVar4) &&
           (*(int *)(*(long *)(param_1 + 0x98) + lVar6) != 0)) break;
        uVar4 = uVar4 + 1;
        lVar6 = lVar6 + 0x210;
      } while ((long)uVar4 < (long)(int)uVar1);
      if ((uint)uVar4 == uVar1) break;
    }
    Aska::Thread::Switch()();
  } while( true );
code_r0x0226b110:
  *(int *)(param_1 + 0xa8) = (int)uVar2;
  if (param_2 == 3) {
code_r0x0226b124:
    do {
      uVar1 = *(uint *)(param_1 + 0xb4);
      if ((int)uVar1 < 0) {
        if (*(char *)(param_1 + 0xb8) != '\0') {
          *(undefined1 *)(param_1 + 0xb8) = 0;
        }
        if (*(int *)(param_1 + 0xac) < 1) goto code_r0x0226b124;
        lVar8 = 0;
        lVar6 = 0;
        iVar7 = 0;
        do {
          uVar1 = Aska::ObjectManagerWorkerThread::ChangeMode(int)(*(long *)(param_1 + 0x98) + lVar8,3);
          lVar6 = lVar6 + 1;
          iVar7 = iVar7 + (uVar1 & 1);
          lVar8 = lVar8 + 0x210;
        } while (lVar6 < *(int *)(param_1 + 0xac));
      }
      else {
        iVar3 = *(int *)(param_1 + 0xac);
        if (iVar3 < 1) {
          iVar7 = 0;
        }
        else {
          lVar6 = 0;
          uVar2 = 0;
          iVar7 = 0;
          do {
            if (uVar2 != uVar1) {
              uVar1 = Aska::ObjectManagerWorkerThread::ChangeMode(int)(*(long *)(param_1 + 0x98) + lVar6,3);
              iVar3 = *(int *)(param_1 + 0xac);
              iVar7 = iVar7 + (uVar1 & 1);
            }
            uVar1 = *(uint *)(param_1 + 0xb4);
            uVar2 = uVar2 + 1;
            lVar6 = lVar6 + 0x210;
          } while ((long)uVar2 < (long)iVar3);
        }
        Aska::ObjectManagerWorkerThread::ChangeMode(int)(*(long *)(param_1 + 0x98) + (long)(int)uVar1 * 0x210,7);
        *(undefined1 *)(param_1 + 0xb8) = 1;
      }
    } while (iVar7 < 1);
  }
  else {
    do {
      do {
        if (*(char *)(param_1 + 0xb8) != '\0') {
          *(undefined1 *)(param_1 + 0xb8) = 0;
        }
      } while ((int)uVar2 < 1);
      lVar8 = 0;
      lVar6 = 0;
      iVar7 = 0;
      do {
        uVar1 = Aska::ObjectManagerWorkerThread::ChangeMode(int)(*(long *)(param_1 + 0x98) + lVar8,param_2);
        uVar2 = (ulong)*(int *)(param_1 + 0xac);
        lVar6 = lVar6 + 1;
        iVar7 = iVar7 + (uVar1 & 1);
        lVar8 = lVar8 + 0x210;
      } while (lVar6 < (long)uVar2);
    } while (iVar7 < 1);
  }
  return;
}

// ==== Aska::ObjectManagerWorkerThread::ChangeMode(int)
// vaddr 0x216b260 | ghidra 0x226b260 | size 444 | symbol _ZN4Aska25ObjectManagerWorkerThread10ChangeModeEi | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZN4Aska25ObjectManagerWorkerThread10ChangeModeEi(long param_1,undefined4 param_2)

{
  int *piVar1;
  char cVar2;
  bool bVar3;
  ulong uVar4;
  int iVar5;
  int *piVar6;
  undefined4 uVar7;
  
  piVar6 = (int *)(param_1 + 0xb8);
  iVar5 = 0;
  do {
    while (*piVar6 == -1) {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar6,0x10);
      if (bVar3) {
        *piVar6 = 0;
        cVar2 = ExclusiveMonitorsStatus();
      }
      if (cVar2 == '\0') goto code_r0x0226b344;
    }
    ClearExclusiveLocal();
    bVar3 = iVar5 < 0x1ff;
    iVar5 = iVar5 + 1;
  } while (bVar3);
  piVar1 = (int *)(param_1 + 0xbc);
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
        uVar4 = Aska::Semaphore::IsReady() const(param_1 + 0xf8);
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
          Aska::Semaphore::Wait() const(param_1 + 0xf8);
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
          if (cVar2 == '\0') goto code_r0x0226b334;
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
code_r0x0226b334:
  do {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar3) {
      *piVar1 = *piVar1 + -1;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
code_r0x0226b344:
  DataMemoryBarrier(2,3);
  if (*(char *)(param_1 + 0x119) == '\0') {
    uVar7 = 1;
    *(undefined1 *)(param_1 + 0x119) = 1;
    *(undefined4 *)(param_1 + 0x114) = param_2;
    *(undefined1 *)(param_1 + 0x118) = 0;
    DataMemoryBarrier(2,3);
    Aska::Event::Set() const(param_1 + 0x18);
    DataMemoryBarrier(2,3);
    *(undefined4 *)(param_1 + 0xb8) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar6 = (int *)(param_1 + 0xbc);
    if (0x14 < *piVar6) {
      do {
        cVar2 = '\x01';
        bVar3 = (bool)ExclusiveMonitorPass(piVar6,0x10);
        if (bVar3) {
          *piVar6 = *piVar6 + -1;
          cVar2 = ExclusiveMonitorsStatus();
        }
      } while (cVar2 != '\0');
      uVar4 = Aska::Semaphore::IsReady() const(param_1 + 0xf8);
      if ((uVar4 & 1) != 0) {
        Aska::Semaphore::Signal() const(param_1 + 0xf8);
      }
      uVar7 = 1;
    }
  }
  else {
    DataMemoryBarrier(2,3);
    *(undefined4 *)(param_1 + 0xb8) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar6 = (int *)(param_1 + 0xbc);
    if (0x14 < *piVar6) {
      do {
        cVar2 = '\x01';
        bVar3 = (bool)ExclusiveMonitorPass(piVar6,0x10);
        if (bVar3) {
          *piVar6 = *piVar6 + -1;
          cVar2 = ExclusiveMonitorsStatus();
        }
      } while (cVar2 != '\0');
      uVar4 = Aska::Semaphore::IsReady() const(param_1 + 0xf8);
      if ((uVar4 & 1) != 0) {
        Aska::Semaphore::Signal() const(param_1 + 0xf8);
      }
    }
    uVar7 = 0;
  }
  return uVar7;
}

// ==== Aska::ObjectManagerJobDispatcher::RetryChangeMode(int)
// vaddr 0x216b41c | ghidra 0x226b41c | size 148 | symbol _ZN4Aska26ObjectManagerJobDispatcher15RetryChangeModeEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska26ObjectManagerJobDispatcher15RetryChangeModeEi(long param_1,int param_2)

{
  long lVar1;
  ulong uVar2;
  long lVar3;
  
  uVar2 = (ulong)*(uint *)(param_1 + 0xac);
  if (0 < (int)*(uint *)(param_1 + 0xac)) {
    lVar3 = 0x11c;
    do {
      lVar1 = *(long *)(param_1 + 0x98);
      DataMemoryBarrier(2,3);
      if ((((*(char *)(lVar1 + lVar3 + -2) != '\0') && (*(char *)(lVar1 + lVar3 + -4) != '\0')) &&
          (*(char *)(lVar1 + lVar3 + -3) == '\0')) &&
         (((*(int *)(lVar1 + lVar3) == 0 && (*(int *)(lVar1 + lVar3 + -8) < 0)) &&
          (*(int *)(lVar1 + lVar3 + -0xc) != param_2)))) {
        Aska::ObjectManagerJobDispatcher::ChangeMode(int)(param_1,param_2);
      }
      uVar2 = uVar2 - 1;
      lVar3 = lVar3 + 0x210;
    } while (uVar2 != 0);
  }
  return;
}

// ==== Aska::ObjectManagerJobDispatcher::RetryChangeModeExceptRenderThread(int)
// vaddr 0x216b4b0 | ghidra 0x226b4b0 | size 300 | symbol _ZN4Aska26ObjectManagerJobDispatcher33RetryChangeModeExceptRenderThreadEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska26ObjectManagerJobDispatcher33RetryChangeModeExceptRenderThreadEi
               (long param_1,int param_2)

{
  uint uVar1;
  long lVar2;
  ulong uVar3;
  ulong uVar4;
  long lVar5;
  
  uVar1 = *(uint *)(param_1 + 0xac);
  uVar3 = (ulong)uVar1;
  if (*(int *)(param_1 + 0xb4) < 0) {
    if (0 < (int)uVar1) {
      lVar5 = 0x110;
      do {
        lVar2 = *(long *)(param_1 + 0x98);
        DataMemoryBarrier(2,3);
        if ((((*(char *)(lVar2 + lVar5 + 10) != '\0') && (*(char *)(lVar2 + lVar5 + 8) != '\0')) &&
            (*(char *)(lVar2 + lVar5 + 9) == '\0')) &&
           (((*(int *)(lVar2 + lVar5 + 0xc) == 0 && (*(int *)(lVar2 + lVar5 + 4) < 0)) &&
            (*(int *)(lVar2 + lVar5) != param_2)))) {
          Aska::ObjectManagerJobDispatcher::ChangeMode(int)(param_1,param_2);
        }
        uVar3 = uVar3 - 1;
        lVar5 = lVar5 + 0x210;
      } while (uVar3 != 0);
    }
  }
  else if (0 < (int)uVar1) {
    uVar4 = 0;
    lVar5 = 0x11c;
    if (*(int *)(param_1 + 0xb4) == 0) goto code_r0x0226b558;
    do {
      lVar2 = *(long *)(param_1 + 0x98);
      DataMemoryBarrier(2,3);
      if (((*(char *)(lVar2 + lVar5 + -2) != '\0') && (*(char *)(lVar2 + lVar5 + -4) != '\0')) &&
         ((*(char *)(lVar2 + lVar5 + -3) == '\0' &&
          (((*(int *)(lVar2 + lVar5) == 0 && (*(int *)(lVar2 + lVar5 + -8) < 0)) &&
           (*(int *)(lVar2 + lVar5 + -0xc) != param_2)))))) {
        Aska::ObjectManagerJobDispatcher::ChangeMode(int)(param_1,param_2);
      }
code_r0x0226b558:
      do {
        if (uVar3 - 1 == uVar4) {
          return;
        }
        uVar4 = uVar4 + 1;
        lVar5 = lVar5 + 0x210;
      } while (uVar4 == *(uint *)(param_1 + 0xb4));
    } while( true );
  }
  return;
}

// ==== Aska::ObjectManagerJobDispatcher::Dispatch_ResetSystemFlags(Aska::RenderableObject*, Aska::RenderableObject*)
// vaddr 0x216b5dc | ghidra 0x226b5dc | size 280 | symbol _ZN4Aska26ObjectManagerJobDispatcher25Dispatch_ResetSystemFlagsEPNS_16RenderableObjectES2_ | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska26ObjectManagerJobDispatcher25Dispatch_ResetSystemFlagsEPNS_16RenderableObjectES2_
          (long param_1,undefined8 param_2,undefined8 param_3)

{
  undefined8 *puVar1;
  long lVar2;
  long lVar3;
  long lVar4;
  ulong uVar5;
  
  if (0 < *(int *)(param_1 + 0xac)) {
    lVar2 = 0;
    lVar3 = 0x150;
    do {
      lVar4 = *(long *)(param_1 + 0x98);
      DataMemoryBarrier(2,3);
      if ((((*(char *)(lVar4 + lVar3 + -0x36) != '\0') && (*(char *)(lVar4 + lVar3 + -0x38) != '\0')
           ) && (*(char *)(lVar4 + lVar3 + -0x37) == '\0')) &&
         ((*(int *)(lVar4 + lVar3 + -0x34) == 0 &&
          (puVar1 = (undefined8 *)(lVar4 + lVar3), *(int *)(puVar1 + -8) == 6)))) {
        *(undefined1 *)(puVar1 + -7) = 0;
        puVar1[-1] = param_2;
        *puVar1 = param_3;
        *(undefined4 *)((long)puVar1 + -0x34) = 6;
        DataMemoryBarrier(2,3);
        Aska::Event::Set() const(puVar1 + -0x27);
        return 1;
      }
      lVar2 = lVar2 + 1;
      lVar3 = lVar3 + 0x210;
    } while (lVar2 < *(int *)(param_1 + 0xac));
    uVar5 = (ulong)*(uint *)(param_1 + 0xac);
    if (0 < (int)*(uint *)(param_1 + 0xac)) {
      lVar2 = 0x110;
      do {
        lVar3 = *(long *)(param_1 + 0x98);
        DataMemoryBarrier(2,3);
        if (((*(char *)(lVar3 + lVar2 + 10) != '\0') && (*(char *)(lVar3 + lVar2 + 8) != '\0')) &&
           ((*(char *)(lVar3 + lVar2 + 9) == '\0' &&
            (((*(int *)(lVar3 + lVar2 + 0xc) == 0 && (*(int *)(lVar3 + lVar2 + 4) < 0)) &&
             (*(int *)(lVar3 + lVar2) != 6)))))) {
          Aska::ObjectManagerJobDispatcher::ChangeMode(int)(param_1,6);
        }
        uVar5 = uVar5 - 1;
        lVar2 = lVar2 + 0x210;
      } while (uVar5 != 0);
    }
  }
  return 0;
}

// ==== Aska::ObjectManagerJobDispatcher::Dispatch_MakePaintingList(int, int)
// vaddr 0x216b6f4 | ghidra 0x226b6f4 | size 428 | symbol _ZN4Aska26ObjectManagerJobDispatcher25Dispatch_MakePaintingListEii | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska26ObjectManagerJobDispatcher25Dispatch_MakePaintingListEii
               (long param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 *puVar1;
  uint uVar2;
  long lVar3;
  long lVar4;
  long lVar5;
  ulong uVar6;
  
  uVar2 = *(uint *)(param_1 + 0xac);
  if ((int)uVar2 < 1) {
    do {
      if (0 < (int)uVar2) {
        uVar6 = (ulong)uVar2;
        lVar3 = 0x110;
        do {
          lVar4 = *(long *)(param_1 + 0x98);
          DataMemoryBarrier(2,3);
          if ((((*(char *)(lVar4 + lVar3 + 10) != '\0') && (*(char *)(lVar4 + lVar3 + 8) != '\0'))
              && (*(char *)(lVar4 + lVar3 + 9) == '\0')) &&
             (((*(int *)(lVar4 + lVar3 + 0xc) == 0 && (*(int *)(lVar4 + lVar3 + 4) < 0)) &&
              (*(int *)(lVar4 + lVar3) != 1)))) {
            Aska::ObjectManagerJobDispatcher::ChangeMode(int)(param_1,1);
          }
          uVar6 = uVar6 - 1;
          lVar3 = lVar3 + 0x210;
        } while (uVar6 != 0);
      }
      Aska::Thread::Switch()();
      uVar2 = *(uint *)(param_1 + 0xac);
    } while( true );
  }
  do {
    lVar3 = 0;
    lVar4 = 0x15c;
    do {
      lVar5 = *(long *)(param_1 + 0x98);
      DataMemoryBarrier(2,3);
      if (((*(char *)(lVar5 + lVar4 + -0x42) != '\0') && (*(char *)(lVar5 + lVar4 + -0x44) != '\0'))
         && ((*(char *)(lVar5 + lVar4 + -0x43) == '\0' &&
             ((*(int *)(lVar5 + lVar4 + -0x40) == 0 &&
              (puVar1 = (undefined4 *)(lVar5 + lVar4), puVar1[-0x13] == 1)))))) {
        *(undefined1 *)(puVar1 + -0x11) = 0;
        puVar1[-1] = param_2;
        *puVar1 = param_3;
        puVar1[-0x10] = 1;
        DataMemoryBarrier(2,3);
        (*(code *)PTR__ZNK4Aska5Event3SetEv_02c9dcf0)(puVar1 + -0x51);
        return;
      }
      lVar3 = lVar3 + 1;
      lVar4 = lVar4 + 0x210;
    } while (lVar3 < (int)uVar2);
    uVar6 = (ulong)*(uint *)(param_1 + 0xac);
    if (0 < (int)*(uint *)(param_1 + 0xac)) {
      lVar3 = 0x110;
      do {
        lVar4 = *(long *)(param_1 + 0x98);
        DataMemoryBarrier(2,3);
        if (((((*(char *)(lVar4 + lVar3 + 10) != '\0') && (*(char *)(lVar4 + lVar3 + 8) != '\0')) &&
             (*(char *)(lVar4 + lVar3 + 9) == '\0')) &&
            ((*(int *)(lVar4 + lVar3 + 0xc) == 0 && (*(int *)(lVar4 + lVar3 + 4) < 0)))) &&
           (*(int *)(lVar4 + lVar3) != 1)) {
          Aska::ObjectManagerJobDispatcher::ChangeMode(int)(param_1,1);
        }
        uVar6 = uVar6 - 1;
        lVar3 = lVar3 + 0x210;
      } while (uVar6 != 0);
    }
    Aska::Thread::Switch()();
  } while( true );
}

// ==== Aska::ObjectManagerJobDispatcher::Dispatch_PreliminarilyPrepare(Aska::RenderableObject**, int, int)
// vaddr 0x216b8a0 | ghidra 0x226b8a0 | size 284 | symbol _ZN4Aska26ObjectManagerJobDispatcher29Dispatch_PreliminarilyPrepareEPPNS_16RenderableObjectEii | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska26ObjectManagerJobDispatcher29Dispatch_PreliminarilyPrepareEPPNS_16RenderableObjectEii
          (long param_1,undefined8 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 *puVar1;
  long lVar2;
  long lVar3;
  long lVar4;
  ulong uVar5;
  
  if (0 < *(int *)(param_1 + 0xac)) {
    lVar2 = 0;
    lVar3 = 0x16c;
    do {
      lVar4 = *(long *)(param_1 + 0x98);
      DataMemoryBarrier(2,3);
      if ((((*(char *)(lVar4 + lVar3 + -0x52) != '\0') && (*(char *)(lVar4 + lVar3 + -0x54) != '\0')
           ) && (*(char *)(lVar4 + lVar3 + -0x53) == '\0')) &&
         ((*(int *)(lVar4 + lVar3 + -0x50) == 0 &&
          (puVar1 = (undefined4 *)(lVar4 + lVar3), puVar1[-0x17] == 2)))) {
        *(undefined1 *)(puVar1 + -0x15) = 0;
        *(undefined8 *)(puVar1 + -3) = param_2;
        puVar1[-1] = param_3;
        *puVar1 = param_4;
        puVar1[-0x14] = 2;
        DataMemoryBarrier(2,3);
        Aska::Event::Set() const(puVar1 + -0x55);
        return 1;
      }
      lVar2 = lVar2 + 1;
      lVar3 = lVar3 + 0x210;
    } while (lVar2 < *(int *)(param_1 + 0xac));
    uVar5 = (ulong)*(uint *)(param_1 + 0xac);
    if (0 < (int)*(uint *)(param_1 + 0xac)) {
      lVar2 = 0x110;
      do {
        lVar3 = *(long *)(param_1 + 0x98);
        DataMemoryBarrier(2,3);
        if (((*(char *)(lVar3 + lVar2 + 10) != '\0') && (*(char *)(lVar3 + lVar2 + 8) != '\0')) &&
           ((*(char *)(lVar3 + lVar2 + 9) == '\0' &&
            (((*(int *)(lVar3 + lVar2 + 0xc) == 0 && (*(int *)(lVar3 + lVar2 + 4) < 0)) &&
             (*(int *)(lVar3 + lVar2) != 2)))))) {
          Aska::ObjectManagerJobDispatcher::ChangeMode(int)(param_1,2);
        }
        uVar5 = uVar5 - 1;
        lVar2 = lVar2 + 0x210;
      } while (uVar5 != 0);
    }
  }
  return 0;
}

// ==== Aska::ObjectManagerJobDispatcher::Dispatch_PrepareForRendering(int, Aska::RenderableObject**, unsigned long)
// vaddr 0x216b9bc | ghidra 0x226b9bc | size 432 | symbol _ZN4Aska26ObjectManagerJobDispatcher28Dispatch_PrepareForRenderingEiPPNS_16RenderableObjectEm | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska26ObjectManagerJobDispatcher28Dispatch_PrepareForRenderingEiPPNS_16RenderableObjectEm
          (long param_1,undefined4 param_2,undefined8 param_3,undefined8 param_4)

{
  int iVar1;
  ulong uVar2;
  long lVar3;
  long lVar4;
  long lVar5;
  undefined4 *puVar6;
  
  iVar1 = *(int *)(param_1 + 0xac);
  if (*(int *)(param_1 + 0xb4) < 0) {
    if (0 < iVar1) {
      lVar3 = 0;
      lVar4 = 0x1ac;
      do {
        lVar5 = *(long *)(param_1 + 0x98);
        DataMemoryBarrier(2,3);
        if ((((*(char *)(lVar5 + lVar4 + -0x92) != '\0') &&
             (*(char *)(lVar5 + lVar4 + -0x94) != '\0')) &&
            (*(char *)(lVar5 + lVar4 + -0x93) == '\0')) &&
           ((*(int *)(lVar5 + lVar4 + -0x90) == 0 &&
            (puVar6 = (undefined4 *)(lVar5 + lVar4), puVar6[-0x27] == 3)))) goto code_r0x0226bb3c;
        lVar3 = lVar3 + 1;
        lVar4 = lVar4 + 0x210;
      } while (lVar3 < iVar1);
      uVar2 = (ulong)*(uint *)(param_1 + 0xac);
      if (0 < (int)*(uint *)(param_1 + 0xac)) {
        lVar3 = 0x110;
        do {
          lVar4 = *(long *)(param_1 + 0x98);
          DataMemoryBarrier(2,3);
          if (((*(char *)(lVar4 + lVar3 + 10) != '\0') && (*(char *)(lVar4 + lVar3 + 8) != '\0')) &&
             ((*(char *)(lVar4 + lVar3 + 9) == '\0' &&
              (((*(int *)(lVar4 + lVar3 + 0xc) == 0 && (*(int *)(lVar4 + lVar3 + 4) < 0)) &&
               (*(int *)(lVar4 + lVar3) != 3)))))) {
            Aska::ObjectManagerJobDispatcher::ChangeMode(int)(param_1,3);
          }
          uVar2 = uVar2 - 1;
          lVar3 = lVar3 + 0x210;
        } while (uVar2 != 0);
      }
    }
  }
  else {
    if (0 < iVar1) {
      uVar2 = 0;
      lVar3 = 0x1ac;
      if (*(int *)(param_1 + 0xb4) == 0) goto code_r0x0226ba44;
      while( true ) {
        lVar4 = *(long *)(param_1 + 0x98);
        DataMemoryBarrier(2,3);
        if (((*(char *)(lVar4 + lVar3 + -0x92) != '\0') &&
            (*(char *)(lVar4 + lVar3 + -0x94) != '\0')) &&
           ((*(char *)(lVar4 + lVar3 + -0x93) == '\0' &&
            ((*(int *)(lVar4 + lVar3 + -0x90) == 0 &&
             (puVar6 = (undefined4 *)(lVar4 + lVar3), puVar6[-0x27] == 3)))))) break;
code_r0x0226ba44:
        do {
          uVar2 = uVar2 + 1;
          if ((long)iVar1 <= (long)uVar2) goto code_r0x0226ba50;
          lVar3 = lVar3 + 0x210;
        } while (uVar2 == *(uint *)(param_1 + 0xb4));
      }
code_r0x0226bb3c:
      *(undefined1 *)(puVar6 + -0x25) = 0;
      puVar6[-5] = param_2;
      *(undefined8 *)(puVar6 + -3) = param_3;
      puVar6[-1] = (int)param_4;
      *puVar6 = (int)((ulong)param_4 >> 0x20);
      puVar6[-0x24] = 3;
      DataMemoryBarrier(2,3);
      Aska::Event::Set() const(puVar6 + -0x65);
      return 1;
    }
code_r0x0226ba50:
    Aska::ObjectManagerJobDispatcher::RetryChangeModeExceptRenderThread(int)(param_1,3);
  }
  return 0;
}

// ==== Aska::ObjectManagerJobDispatcher::Dispatch_ViewFrustumCulling(int, int, int)
// vaddr 0x216bb6c | ghidra 0x226bb6c | size 284 | symbol _ZN4Aska26ObjectManagerJobDispatcher27Dispatch_ViewFrustumCullingEiii | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska26ObjectManagerJobDispatcher27Dispatch_ViewFrustumCullingEiii
          (long param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 *puVar1;
  long lVar2;
  long lVar3;
  long lVar4;
  ulong uVar5;
  
  if (0 < *(int *)(param_1 + 0xac)) {
    lVar2 = 0;
    lVar3 = 0x1d0;
    do {
      lVar4 = *(long *)(param_1 + 0x98);
      DataMemoryBarrier(2,3);
      if ((((*(char *)(lVar4 + lVar3 + -0xb6) != '\0') && (*(char *)(lVar4 + lVar3 + -0xb8) != '\0')
           ) && (*(char *)(lVar4 + lVar3 + -0xb7) == '\0')) &&
         ((*(int *)(lVar4 + lVar3 + -0xb4) == 0 &&
          (puVar1 = (undefined4 *)(lVar4 + lVar3), puVar1[-0x30] == 4)))) {
        *(undefined1 *)(puVar1 + -0x2e) = 0;
        puVar1[-2] = param_2;
        puVar1[-1] = param_3;
        *puVar1 = param_4;
        puVar1[-0x2d] = 4;
        DataMemoryBarrier(2,3);
        Aska::Event::Set() const(puVar1 + -0x6e);
        return 1;
      }
      lVar2 = lVar2 + 1;
      lVar3 = lVar3 + 0x210;
    } while (lVar2 < *(int *)(param_1 + 0xac));
    uVar5 = (ulong)*(uint *)(param_1 + 0xac);
    if (0 < (int)*(uint *)(param_1 + 0xac)) {
      lVar2 = 0x110;
      do {
        lVar3 = *(long *)(param_1 + 0x98);
        DataMemoryBarrier(2,3);
        if (((*(char *)(lVar3 + lVar2 + 10) != '\0') && (*(char *)(lVar3 + lVar2 + 8) != '\0')) &&
           ((*(char *)(lVar3 + lVar2 + 9) == '\0' &&
            (((*(int *)(lVar3 + lVar2 + 0xc) == 0 && (*(int *)(lVar3 + lVar2 + 4) < 0)) &&
             (*(int *)(lVar3 + lVar2) != 4)))))) {
          Aska::ObjectManagerJobDispatcher::ChangeMode(int)(param_1,4);
        }
        uVar5 = uVar5 - 1;
        lVar2 = lVar2 + 0x210;
      } while (uVar5 != 0);
    }
  }
  return 0;
}

// ==== Aska::ObjectManagerJobDispatcher::Dispatch_RenderingDecided(Aska::RenderableObject***, unsigned short*, int, unsigned short*, int*)
// vaddr 0x216bc88 | ghidra 0x226bc88 | size 164 | symbol _ZN4Aska26ObjectManagerJobDispatcher25Dispatch_RenderingDecidedEPPPNS_16RenderableObjectEPtiS5_Pi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska26ObjectManagerJobDispatcher25Dispatch_RenderingDecidedEPPPNS_16RenderableObjectEPtiS5_Pi
               (long param_1,undefined8 param_2,undefined8 param_3,undefined4 param_4,
               undefined8 param_5,undefined8 param_6)

{
  undefined1 *puVar1;
  ulong uVar2;
  long lVar3;
  
  uVar2 = (ulong)*(uint *)(param_1 + 0xac);
  if (0 < (int)*(uint *)(param_1 + 0xac)) {
    lVar3 = 0x118;
    do {
      puVar1 = (undefined1 *)(*(long *)(param_1 + 0x98) + lVar3);
      *puVar1 = 0;
      *(undefined4 *)(puVar1 + 0xb0) = 3;
      *(undefined8 *)(puVar1 + 0xc0) = param_2;
      *(undefined8 *)(puVar1 + 200) = param_3;
      *(undefined8 *)(puVar1 + 0xd0) = param_5;
      *(undefined4 *)(puVar1 + 0xd8) = param_4;
      *(undefined8 *)(puVar1 + 0xe0) = param_6;
      *(undefined4 *)(puVar1 + 4) = 4;
      DataMemoryBarrier(2,3);
      Aska::Event::Set() const(puVar1 + -0x100);
      uVar2 = uVar2 - 1;
      lVar3 = lVar3 + 0x210;
    } while (uVar2 != 0);
  }
  return;
}

// ==== Aska::ObjectManagerJobDispatcher::Dispatch_DetectLIBL(int, int)
// vaddr 0x216bd2c | ghidra 0x226bd2c | size 280 | symbol _ZN4Aska26ObjectManagerJobDispatcher19Dispatch_DetectLIBLEii | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska26ObjectManagerJobDispatcher19Dispatch_DetectLIBLEii
          (long param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 *puVar1;
  long lVar2;
  long lVar3;
  long lVar4;
  ulong uVar5;
  
  if (0 < *(int *)(param_1 + 0xac)) {
    lVar2 = 0;
    lVar3 = 0x20c;
    do {
      lVar4 = *(long *)(param_1 + 0x98);
      DataMemoryBarrier(2,3);
      if ((((*(char *)(lVar4 + lVar3 + -0xf2) != '\0') && (*(char *)(lVar4 + lVar3 + -0xf4) != '\0')
           ) && (*(char *)(lVar4 + lVar3 + -0xf3) == '\0')) &&
         ((*(int *)(lVar4 + lVar3 + -0xf0) == 0 &&
          (puVar1 = (undefined4 *)(lVar4 + lVar3), puVar1[-0x3f] == 5)))) {
        *(undefined1 *)(puVar1 + -0x3d) = 0;
        puVar1[-1] = param_2;
        *puVar1 = param_3;
        puVar1[-0x3c] = 5;
        DataMemoryBarrier(2,3);
        Aska::Event::Set() const(puVar1 + -0x7d);
        return 1;
      }
      lVar2 = lVar2 + 1;
      lVar3 = lVar3 + 0x210;
    } while (lVar2 < *(int *)(param_1 + 0xac));
    uVar5 = (ulong)*(uint *)(param_1 + 0xac);
    if (0 < (int)*(uint *)(param_1 + 0xac)) {
      lVar2 = 0x110;
      do {
        lVar3 = *(long *)(param_1 + 0x98);
        DataMemoryBarrier(2,3);
        if (((*(char *)(lVar3 + lVar2 + 10) != '\0') && (*(char *)(lVar3 + lVar2 + 8) != '\0')) &&
           ((*(char *)(lVar3 + lVar2 + 9) == '\0' &&
            (((*(int *)(lVar3 + lVar2 + 0xc) == 0 && (*(int *)(lVar3 + lVar2 + 4) < 0)) &&
             (*(int *)(lVar3 + lVar2) != 5)))))) {
          Aska::ObjectManagerJobDispatcher::ChangeMode(int)(param_1,5);
        }
        uVar5 = uVar5 - 1;
        lVar2 = lVar2 + 0x210;
      } while (uVar5 != 0);
    }
  }
  return 0;
}

// ==== Aska::ObjectManagerJobDispatcher::SetPreliminarilyPrepareBasicParameter(Aska::LightManager*, unsigned long*)
// vaddr 0x216be44 | ghidra 0x226be44 | size 44 | symbol _ZN4Aska26ObjectManagerJobDispatcher37SetPreliminarilyPrepareBasicParameterEPNS_12LightManagerEPm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska26ObjectManagerJobDispatcher37SetPreliminarilyPrepareBasicParameterEPNS_12LightManagerEPm
               (long param_1,undefined8 param_2,undefined8 param_3)

{
  undefined8 *puVar1;
  ulong uVar2;
  long lVar3;
  
  uVar2 = (ulong)*(uint *)(param_1 + 0xac);
  if (0 < (int)*(uint *)(param_1 + 0xac)) {
    lVar3 = 0x138;
    do {
      uVar2 = uVar2 - 1;
      puVar1 = (undefined8 *)(*(long *)(param_1 + 0x98) + lVar3);
      lVar3 = lVar3 + 0x210;
      *puVar1 = param_2;
      puVar1[1] = param_3;
    } while (uVar2 != 0);
  }
  return;
}

// ==== Aska::ObjectManagerJobDispatcher::SetPrepareForRenderingBasicParameter(Aska::RENDERINFO*, unsigned long*, Aska::Camera*)
// vaddr 0x216be70 | ghidra 0x226be70 | size 64 | symbol _ZN4Aska26ObjectManagerJobDispatcher36SetPrepareForRenderingBasicParameterEPNS_10RENDERINFOEPmPNS_6CameraE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska26ObjectManagerJobDispatcher36SetPrepareForRenderingBasicParameterEPNS_10RENDERINFOEPmPNS_6CameraE
               (long param_1,undefined8 *param_2,undefined8 param_3,undefined8 param_4)

{
  undefined8 *puVar1;
  ulong uVar2;
  long lVar3;
  undefined8 uVar4;
  
  uVar2 = (ulong)*(uint *)(param_1 + 0xac);
  if (0 < (int)*(uint *)(param_1 + 0xac)) {
    lVar3 = 400;
    do {
      uVar4 = param_2[2];
      uVar2 = uVar2 - 1;
      puVar1 = (undefined8 *)(*(long *)(param_1 + 0x98) + lVar3);
      puVar1[-1] = param_2[3];
      puVar1[-2] = uVar4;
      uVar4 = *param_2;
      lVar3 = lVar3 + 0x210;
      puVar1[-3] = param_2[1];
      puVar1[-4] = uVar4;
      *puVar1 = param_4;
      puVar1[-10] = param_3;
    } while (uVar2 != 0);
  }
  return;
}

// ==== Aska::ObjectManagerJobDispatcher::SetViewFrustumCullingBasicParameter(Aska::Camera*, int, int, Aska::RenderableObject**, unsigned long*)
// vaddr 0x216beb0 | ghidra 0x226beb0 | size 60 | symbol _ZN4Aska26ObjectManagerJobDispatcher35SetViewFrustumCullingBasicParameterEPNS_6CameraEiiPPNS_16RenderableObjectEPm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska26ObjectManagerJobDispatcher35SetViewFrustumCullingBasicParameterEPNS_6CameraEiiPPNS_16RenderableObjectEPm
               (long param_1,undefined8 param_2,undefined4 param_3,undefined4 param_4,
               undefined8 param_5,undefined8 param_6)

{
  undefined8 *puVar1;
  ulong uVar2;
  long lVar3;
  
  uVar2 = (ulong)*(uint *)(param_1 + 0xac);
  if (0 < (int)*(uint *)(param_1 + 0xac)) {
    lVar3 = 0x1c0;
    do {
      uVar2 = uVar2 - 1;
      puVar1 = (undefined8 *)(*(long *)(param_1 + 0x98) + lVar3);
      lVar3 = lVar3 + 0x210;
      puVar1[-2] = param_2;
      *(undefined4 *)(puVar1 + -1) = param_3;
      *(undefined4 *)((long)puVar1 + -4) = param_4;
      *puVar1 = param_5;
      puVar1[-0x10] = param_6;
    } while (uVar2 != 0);
  }
  return;
}

// ==== Aska::ObjectManagerJobDispatcher::SetDetectLIBLBasicParameter(Aska::RenderableObject**)
// vaddr 0x216beec | ghidra 0x226beec | size 40 | symbol _ZN4Aska26ObjectManagerJobDispatcher27SetDetectLIBLBasicParameterEPPNS_16RenderableObjectE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska26ObjectManagerJobDispatcher27SetDetectLIBLBasicParameterEPPNS_16RenderableObjectE
               (long param_1,undefined8 param_2)

{
  ulong uVar1;
  long lVar2;
  
  uVar1 = (ulong)*(uint *)(param_1 + 0xac);
  if (0 < (int)*(uint *)(param_1 + 0xac)) {
    lVar2 = 0x200;
    do {
      uVar1 = uVar1 - 1;
      *(undefined8 *)(*(long *)(param_1 + 0x98) + lVar2) = param_2;
      lVar2 = lVar2 + 0x210;
    } while (uVar1 != 0);
  }
  return;
}

// ==== Aska::ObjectManagerJobDispatcher::Sleep()
// vaddr 0x216bf14 | ghidra 0x226bf14 | size 84 | symbol _ZN4Aska26ObjectManagerJobDispatcher5SleepEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska26ObjectManagerJobDispatcher5SleepEv(long param_1)

{
  long lVar1;
  long lVar2;
  
  Aska::ObjectManagerJobDispatcher::WaitIdle()();
  if (0 < *(int *)(param_1 + 0xac)) {
    lVar1 = 0;
    lVar2 = 0;
    do {
      Aska::ObjectManagerWorkerThread::ChangeMode(int)(*(long *)(param_1 + 0x98) + lVar1,7);
      lVar2 = lVar2 + 1;
      lVar1 = lVar1 + 0x210;
    } while (lVar2 < *(int *)(param_1 + 0xac));
  }
  return;
}


// FAILED to create function at 02c4f508 Aska::ObjectManager::vtable
// FAILED to create function at 02c4f6b0 Aska::ObjectManager::typeinfo
// FAILED to create function at 02c4fdc8 Aska::ObjectManagerWorkerThread::vtable
// FAILED to create function at 02c4fdf0 Aska::ObjectManagerJobDispatcher::vtable
// FAILED to create function at 02c4fe10 Aska::ObjectManagerWorkerThread::typeinfo
// FAILED to create function at 02c4fe28 Aska::ObjectManagerJobDispatcher::typeinfo
// FAILED to create function at 02ccb350 Aska::ObjectManager::m_bSRGBTexDecode
// FAILED to create function at 02ccb354 Aska::ObjectManager::m_fGlobalHDRRange
// FAILED to create function at 02ccb358 Aska::ObjectManager::m_ucGammaCorrection
// FAILED to create function at 02dd0660 Aska::ObjectManager::m_lastRenderStartPoint
// FAILED to create function at 02dd0668 Aska::ObjectManager::m_pBackBufferSync
// FAILED to create function at 02dd0670 Aska::ObjectManager::m_LightConfiguration
// FAILED to create function at 02dd068a Aska::ObjectManager::m_cShaderGradeLevel
