// port/decomp/resource/resource_manager.c: Ghidra decompiles for the resource subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-04 06:12 UTC: tools/decomp.sh '--into' 'resource/resource_manager' 'Framework::CResourceManager::' 'Framework::CResourceElement::'

// ==== Framework::CResourceElement::gpInstantiate(unsigned int)
// vaddr 0x1e904c0 | ghidra 0x1f904c0 | size 2696 | symbol _ZN9Framework16CResourceElement13gpInstantiateEj | lib libSOA-3.7.0.so | 2026-10-04
long * _ZN9Framework16CResourceElement13gpInstantiateEj(undefined4 param_1)

{
  undefined4 uVar1;
  long *plVar2;
  code *pcVar3;
  long lVar4;
  undefined *puVar5;
  undefined *puVar6;
  long *plVar7;
  
  switch(param_1) {
  case 2:
    plVar2 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x158,PTR__ZSt7nothrow_02cb9a80);
    if (plVar2 == (long *)0x0) {
      return (long *)0x0;
    }
    Framework::CFileLoader::CFileLoader()(plVar2);
    plVar2[0x19] = 0;
    plVar2[0x1a] = 0;
    pcVar3 = *(code **)(PTR__ZTVN4Aska4TaskE_02cbe020 + 0x68);
    plVar7 = plVar2 + 0x18;
    *plVar7 = (long)(PTR__ZTVN4Aska4TaskE_02cbe020 + 0x10);
    plVar2[0x1b] = 0;
    *(undefined2 *)((long)plVar2 + 0xe4) = 0;
    *(undefined1 *)((long)plVar2 + 0xe6) = 0;
    uVar1 = (*pcVar3)(plVar7);
    *(undefined4 *)(plVar2 + 0x1c) = uVar1;
    plVar2[0x21] = 0;
    plVar2[0x22] = 0;
    plVar2[0x20] = 0;
    puVar5 = PTR__ZTVN9Framework16CResourceElement13CFinishNotifyE_02cbe2d0;
    *(undefined1 *)(plVar2 + 0x25) = 0;
    *(undefined1 *)((long)plVar2 + 0x14a) = 0;
    *(undefined2 *)(plVar2 + 0x29) = 0;
    plVar2[0x27] = 0;
    plVar2[0x28] = 0;
    plVar2[0x26] = (long)plVar2;
    puVar6 = PTR__ZTVN9Framework20CResourceElement_AifE_02cc4760;
    plVar2[0x1d] = 2;
    plVar2[0x1e] = 0;
    plVar2[0x24] = (long)(puVar5 + 0x10);
    *plVar2 = (long)(puVar6 + 0x10);
    *plVar7 = (long)(puVar6 + 0xb0);
    plVar2[0x2a] = 0;
    return plVar2;
  case 3:
    plVar2 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x158,PTR__ZSt7nothrow_02cb9a80);
    if (plVar2 == (long *)0x0) {
      return (long *)0x0;
    }
    Framework::CFileLoader::CFileLoader()(plVar2);
    plVar2[0x19] = 0;
    plVar2[0x1a] = 0;
    pcVar3 = *(code **)(PTR__ZTVN4Aska4TaskE_02cbe020 + 0x68);
    plVar7 = plVar2 + 0x18;
    *plVar7 = (long)(PTR__ZTVN4Aska4TaskE_02cbe020 + 0x10);
    plVar2[0x1b] = 0;
    *(undefined2 *)((long)plVar2 + 0xe4) = 0;
    *(undefined1 *)((long)plVar2 + 0xe6) = 0;
    uVar1 = (*pcVar3)(plVar7);
    *(undefined4 *)(plVar2 + 0x1c) = uVar1;
    plVar2[0x1e] = 0;
    plVar2[0x21] = 0;
    plVar2[0x22] = 0;
    plVar2[0x20] = 0;
    puVar5 = PTR__ZTVN9Framework16CResourceElement13CFinishNotifyE_02cbe2d0;
    *(undefined1 *)(plVar2 + 0x25) = 0;
    *(undefined1 *)((long)plVar2 + 0x14a) = 0;
    *(undefined2 *)(plVar2 + 0x29) = 0;
    plVar2[0x27] = 0;
    plVar2[0x28] = 0;
    plVar2[0x26] = (long)plVar2;
    puVar6 = PTR__ZTVN9Framework20CResourceElement_AifE_02cc4760;
    plVar2[0x24] = (long)(puVar5 + 0x10);
    *plVar2 = (long)(puVar6 + 0x10);
    lVar4 = 3;
    *plVar7 = (long)(puVar6 + 0xb0);
    plVar2[0x2a] = 0;
    goto code_r0x01f90f34;
  case 4:
    plVar2 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x150,PTR__ZSt7nothrow_02cb9a80);
    if (plVar2 == (long *)0x0) {
      return (long *)0x0;
    }
    Framework::CFileLoader::CFileLoader()(plVar2);
    plVar2[0x19] = 0;
    plVar2[0x1a] = 0;
    pcVar3 = *(code **)(PTR__ZTVN4Aska4TaskE_02cbe020 + 0x68);
    plVar7 = plVar2 + 0x18;
    *plVar7 = (long)(PTR__ZTVN4Aska4TaskE_02cbe020 + 0x10);
    plVar2[0x1b] = 0;
    *(undefined2 *)((long)plVar2 + 0xe4) = 0;
    *(undefined1 *)((long)plVar2 + 0xe6) = 0;
    uVar1 = (*pcVar3)(plVar7);
    *(undefined4 *)(plVar2 + 0x1c) = uVar1;
    plVar2[0x21] = 0;
    plVar2[0x22] = 0;
    plVar2[0x20] = 0;
    puVar5 = PTR__ZTVN9Framework16CResourceElement13CFinishNotifyE_02cbe2d0;
    *(undefined1 *)(plVar2 + 0x25) = 0;
    *(undefined1 *)((long)plVar2 + 0x14a) = 0;
    *(undefined2 *)(plVar2 + 0x29) = 0;
    plVar2[0x27] = 0;
    plVar2[0x28] = 0;
    plVar2[0x26] = (long)plVar2;
    lVar4 = 4;
    puVar6 = PTR__ZTVN9Framework20CResourceElement_AsfE_02cbd578;
    break;
  case 5:
    plVar2 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x150,PTR__ZSt7nothrow_02cb9a80);
    if (plVar2 == (long *)0x0) {
      return (long *)0x0;
    }
    Framework::CFileLoader::CFileLoader()(plVar2);
    plVar2[0x19] = 0;
    plVar2[0x1a] = 0;
    pcVar3 = *(code **)(PTR__ZTVN4Aska4TaskE_02cbe020 + 0x68);
    plVar7 = plVar2 + 0x18;
    *plVar7 = (long)(PTR__ZTVN4Aska4TaskE_02cbe020 + 0x10);
    plVar2[0x1b] = 0;
    *(undefined2 *)((long)plVar2 + 0xe4) = 0;
    *(undefined1 *)((long)plVar2 + 0xe6) = 0;
    uVar1 = (*pcVar3)(plVar7);
    *(undefined4 *)(plVar2 + 0x1c) = uVar1;
    plVar2[0x21] = 0;
    plVar2[0x22] = 0;
    plVar2[0x20] = 0;
    puVar5 = PTR__ZTVN9Framework16CResourceElement13CFinishNotifyE_02cbe2d0;
    *(undefined1 *)(plVar2 + 0x25) = 0;
    *(undefined1 *)((long)plVar2 + 0x14a) = 0;
    *(undefined2 *)(plVar2 + 0x29) = 0;
    plVar2[0x27] = 0;
    plVar2[0x28] = 0;
    plVar2[0x26] = (long)plVar2;
    lVar4 = 5;
    puVar6 = PTR__ZTVN9Framework20CResourceElement_AafE_02cba1a0;
    break;
  case 6:
    plVar2 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x150,PTR__ZSt7nothrow_02cb9a80);
    if (plVar2 == (long *)0x0) {
      return (long *)0x0;
    }
    Framework::CFileLoader::CFileLoader()(plVar2);
    plVar2[0x19] = 0;
    plVar2[0x1a] = 0;
    pcVar3 = *(code **)(PTR__ZTVN4Aska4TaskE_02cbe020 + 0x68);
    plVar7 = plVar2 + 0x18;
    *plVar7 = (long)(PTR__ZTVN4Aska4TaskE_02cbe020 + 0x10);
    plVar2[0x1b] = 0;
    *(undefined2 *)((long)plVar2 + 0xe4) = 0;
    *(undefined1 *)((long)plVar2 + 0xe6) = 0;
    uVar1 = (*pcVar3)(plVar7);
    *(undefined4 *)(plVar2 + 0x1c) = uVar1;
    plVar2[0x21] = 0;
    plVar2[0x22] = 0;
    plVar2[0x20] = 0;
    puVar5 = PTR__ZTVN9Framework16CResourceElement13CFinishNotifyE_02cbe2d0;
    *(undefined1 *)(plVar2 + 0x25) = 0;
    *(undefined1 *)((long)plVar2 + 0x14a) = 0;
    *(undefined2 *)(plVar2 + 0x29) = 0;
    plVar2[0x27] = 0;
    plVar2[0x28] = 0;
    plVar2[0x26] = (long)plVar2;
    lVar4 = 6;
    puVar6 = PTR__ZTVN9Framework20CResourceElement_AcfE_02cc0398;
    break;
  case 7:
    plVar2 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x150,PTR__ZSt7nothrow_02cb9a80);
    if (plVar2 == (long *)0x0) {
      return (long *)0x0;
    }
    Framework::CFileLoader::CFileLoader()(plVar2);
    plVar2[0x19] = 0;
    plVar2[0x1a] = 0;
    pcVar3 = *(code **)(PTR__ZTVN4Aska4TaskE_02cbe020 + 0x68);
    plVar7 = plVar2 + 0x18;
    *plVar7 = (long)(PTR__ZTVN4Aska4TaskE_02cbe020 + 0x10);
    plVar2[0x1b] = 0;
    *(undefined2 *)((long)plVar2 + 0xe4) = 0;
    *(undefined1 *)((long)plVar2 + 0xe6) = 0;
    uVar1 = (*pcVar3)(plVar7);
    *(undefined4 *)(plVar2 + 0x1c) = uVar1;
    plVar2[0x21] = 0;
    plVar2[0x22] = 0;
    plVar2[0x20] = 0;
    puVar5 = PTR__ZTVN9Framework16CResourceElement13CFinishNotifyE_02cbe2d0;
    *(undefined1 *)(plVar2 + 0x25) = 0;
    *(undefined1 *)((long)plVar2 + 0x14a) = 0;
    *(undefined2 *)(plVar2 + 0x29) = 0;
    plVar2[0x27] = 0;
    plVar2[0x28] = 0;
    plVar2[0x26] = (long)plVar2;
    lVar4 = 7;
    puVar6 = PTR__ZTVN9Framework20CResourceElement_BsbE_02cbdf90;
    break;
  case 8:
    plVar2 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x158,PTR__ZSt7nothrow_02cb9a80);
    if (plVar2 == (long *)0x0) {
      return (long *)0x0;
    }
    Framework::CFileLoader::CFileLoader()(plVar2);
    plVar2[0x19] = 0;
    plVar2[0x1a] = 0;
    pcVar3 = *(code **)(PTR__ZTVN4Aska4TaskE_02cbe020 + 0x68);
    plVar7 = plVar2 + 0x18;
    *plVar7 = (long)(PTR__ZTVN4Aska4TaskE_02cbe020 + 0x10);
    plVar2[0x1b] = 0;
    *(undefined2 *)((long)plVar2 + 0xe4) = 0;
    *(undefined1 *)((long)plVar2 + 0xe6) = 0;
    uVar1 = (*pcVar3)(plVar7);
    *(undefined4 *)(plVar2 + 0x1c) = uVar1;
    plVar2[0x21] = 0;
    plVar2[0x22] = 0;
    plVar2[0x20] = 0;
    puVar5 = PTR__ZTVN9Framework16CResourceElement13CFinishNotifyE_02cbe2d0;
    *(undefined1 *)(plVar2 + 0x25) = 0;
    *(undefined1 *)((long)plVar2 + 0x14a) = 0;
    *(undefined2 *)(plVar2 + 0x29) = 0;
    plVar2[0x27] = 0;
    plVar2[0x28] = 0;
    plVar2[0x26] = (long)plVar2;
    puVar6 = PTR__ZTVN9Framework20CResourceElement_LuaE_02cc0cf0;
    plVar2[0x1d] = 8;
    plVar2[0x1e] = 0;
    plVar2[0x24] = (long)(puVar5 + 0x10);
    *plVar2 = (long)(puVar6 + 0x10);
    *plVar7 = (long)(puVar6 + 0xb8);
    plVar2[0x2a] = 0;
    goto code_r0x01f90ca8;
  case 9:
    plVar2 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x150,PTR__ZSt7nothrow_02cb9a80);
    if (plVar2 == (long *)0x0) {
      return (long *)0x0;
    }
    Framework::CFileLoader::CFileLoader()(plVar2);
    plVar2[0x19] = 0;
    plVar2[0x1a] = 0;
    pcVar3 = *(code **)(PTR__ZTVN4Aska4TaskE_02cbe020 + 0x68);
    plVar7 = plVar2 + 0x18;
    *plVar7 = (long)(PTR__ZTVN4Aska4TaskE_02cbe020 + 0x10);
    plVar2[0x1b] = 0;
    *(undefined2 *)((long)plVar2 + 0xe4) = 0;
    *(undefined1 *)((long)plVar2 + 0xe6) = 0;
    uVar1 = (*pcVar3)(plVar7);
    *(undefined4 *)(plVar2 + 0x1c) = uVar1;
    plVar2[0x21] = 0;
    plVar2[0x22] = 0;
    plVar2[0x20] = 0;
    puVar5 = PTR__ZTVN9Framework16CResourceElement13CFinishNotifyE_02cbe2d0;
    *(undefined1 *)(plVar2 + 0x25) = 0;
    *(undefined1 *)((long)plVar2 + 0x14a) = 0;
    *(undefined2 *)(plVar2 + 0x29) = 0;
    plVar2[0x27] = 0;
    plVar2[0x28] = 0;
    plVar2[0x26] = (long)plVar2;
    lVar4 = 9;
    puVar6 = PTR__ZTVN9Framework20CResourceElement_AetE_02cc17c8;
    break;
  default:
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029651b8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Resource.cpp"*/,0x1c,&UNK_027ec344/*"Illegal type.(%d)"*/,param_1);
  case 1:
    plVar2 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x150,PTR__ZSt7nothrow_02cb9a80);
    if (plVar2 == (long *)0x0) {
      return (long *)0x0;
    }
    Framework::CFileLoader::CFileLoader()(plVar2);
    plVar2[0x19] = 0;
    plVar2[0x1a] = 0;
    pcVar3 = *(code **)(PTR__ZTVN4Aska4TaskE_02cbe020 + 0x68);
    plVar7 = plVar2 + 0x18;
    *plVar7 = (long)(PTR__ZTVN4Aska4TaskE_02cbe020 + 0x10);
    plVar2[0x1b] = 0;
    *(undefined2 *)((long)plVar2 + 0xe4) = 0;
    *(undefined1 *)((long)plVar2 + 0xe6) = 0;
    uVar1 = (*pcVar3)(plVar7);
    *(undefined4 *)(plVar2 + 0x1c) = uVar1;
    plVar2[0x21] = 0;
    plVar2[0x22] = 0;
    plVar2[0x20] = 0;
    puVar5 = PTR__ZTVN9Framework16CResourceElement13CFinishNotifyE_02cbe2d0;
    *(undefined1 *)(plVar2 + 0x25) = 0;
    *(undefined1 *)((long)plVar2 + 0x14a) = 0;
    *(undefined2 *)(plVar2 + 0x29) = 0;
    plVar2[0x27] = 0;
    plVar2[0x28] = 0;
    plVar2[0x26] = (long)plVar2;
    lVar4 = 1;
    puVar6 = PTR__ZTVN9Framework20CResourceElement_BinE_02cb9288;
    break;
  case 0xb:
    plVar2 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x150,PTR__ZSt7nothrow_02cb9a80);
    if (plVar2 == (long *)0x0) {
      return (long *)0x0;
    }
    Framework::CFileLoader::CFileLoader()(plVar2);
    plVar2[0x19] = 0;
    plVar2[0x1a] = 0;
    pcVar3 = *(code **)(PTR__ZTVN4Aska4TaskE_02cbe020 + 0x68);
    plVar7 = plVar2 + 0x18;
    *plVar7 = (long)(PTR__ZTVN4Aska4TaskE_02cbe020 + 0x10);
    plVar2[0x1b] = 0;
    *(undefined2 *)((long)plVar2 + 0xe4) = 0;
    *(undefined1 *)((long)plVar2 + 0xe6) = 0;
    uVar1 = (*pcVar3)(plVar7);
    *(undefined4 *)(plVar2 + 0x1c) = uVar1;
    plVar2[0x1e] = 0;
    plVar2[0x21] = 0;
    plVar2[0x22] = 0;
    plVar2[0x20] = 0;
    puVar6 = PTR__ZTVN9Framework16CResourceElement13CFinishNotifyE_02cbe2d0;
    *(undefined1 *)(plVar2 + 0x25) = 0;
    *(undefined1 *)((long)plVar2 + 0x14a) = 0;
    *(undefined2 *)(plVar2 + 0x29) = 0;
    plVar2[0x27] = 0;
    plVar2[0x28] = 0;
    plVar2[0x26] = (long)plVar2;
    puVar5 = PTR__ZTVN9Framework20CResourceElement_ApkE_02cc3838;
    plVar2[0x24] = (long)(puVar6 + 0x10);
    *plVar2 = (long)(puVar5 + 0x10);
    lVar4 = 0xb;
    goto code_r0x01f90f2c;
  case 0xc:
    plVar2 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x150,PTR__ZSt7nothrow_02cb9a80);
    if (plVar2 == (long *)0x0) {
      return (long *)0x0;
    }
    Framework::CFileLoader::CFileLoader()(plVar2);
    plVar2[0x19] = 0;
    plVar2[0x1a] = 0;
    pcVar3 = *(code **)(PTR__ZTVN4Aska4TaskE_02cbe020 + 0x68);
    plVar7 = plVar2 + 0x18;
    *plVar7 = (long)(PTR__ZTVN4Aska4TaskE_02cbe020 + 0x10);
    plVar2[0x1b] = 0;
    *(undefined2 *)((long)plVar2 + 0xe4) = 0;
    *(undefined1 *)((long)plVar2 + 0xe6) = 0;
    uVar1 = (*pcVar3)(plVar7);
    *(undefined4 *)(plVar2 + 0x1c) = uVar1;
    plVar2[0x1e] = 0;
    plVar2[0x21] = 0;
    plVar2[0x22] = 0;
    plVar2[0x20] = 0;
    puVar6 = PTR__ZTVN9Framework16CResourceElement13CFinishNotifyE_02cbe2d0;
    *(undefined1 *)(plVar2 + 0x25) = 0;
    *(undefined1 *)((long)plVar2 + 0x14a) = 0;
    *(undefined2 *)(plVar2 + 0x29) = 0;
    plVar2[0x27] = 0;
    plVar2[0x28] = 0;
    plVar2[0x26] = (long)plVar2;
    puVar5 = PTR__ZTVN9Framework20CResourceElement_SpkE_02cc3d38;
    plVar2[0x24] = (long)(puVar6 + 0x10);
    *plVar2 = (long)(puVar5 + 0x10);
    lVar4 = 0xc;
    goto code_r0x01f90f2c;
  case 0xd:
    plVar2 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x150,PTR__ZSt7nothrow_02cb9a80);
    if (plVar2 == (long *)0x0) {
      return (long *)0x0;
    }
    Framework::CFileLoader::CFileLoader()(plVar2);
    plVar2[0x19] = 0;
    plVar2[0x1a] = 0;
    pcVar3 = *(code **)(PTR__ZTVN4Aska4TaskE_02cbe020 + 0x68);
    plVar7 = plVar2 + 0x18;
    *plVar7 = (long)(PTR__ZTVN4Aska4TaskE_02cbe020 + 0x10);
    plVar2[0x1b] = 0;
    *(undefined2 *)((long)plVar2 + 0xe4) = 0;
    *(undefined1 *)((long)plVar2 + 0xe6) = 0;
    uVar1 = (*pcVar3)(plVar7);
    *(undefined4 *)(plVar2 + 0x1c) = uVar1;
    plVar2[0x1e] = 0;
    plVar2[0x21] = 0;
    plVar2[0x22] = 0;
    plVar2[0x20] = 0;
    puVar6 = PTR__ZTVN9Framework16CResourceElement13CFinishNotifyE_02cbe2d0;
    *(undefined1 *)(plVar2 + 0x25) = 0;
    *(undefined1 *)((long)plVar2 + 0x14a) = 0;
    *(undefined2 *)(plVar2 + 0x29) = 0;
    plVar2[0x27] = 0;
    plVar2[0x28] = 0;
    plVar2[0x26] = (long)plVar2;
    puVar5 = PTR__ZTVN9Framework20CResourceElement_TpkE_02cc05e0;
    plVar2[0x24] = (long)(puVar6 + 0x10);
    *plVar2 = (long)(puVar5 + 0x10);
    lVar4 = 0xd;
    goto code_r0x01f90f2c;
  case 0xe:
    plVar2 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x150,PTR__ZSt7nothrow_02cb9a80);
    if (plVar2 == (long *)0x0) {
      return (long *)0x0;
    }
    Framework::CFileLoader::CFileLoader()(plVar2);
    plVar2[0x19] = 0;
    plVar2[0x1a] = 0;
    pcVar3 = *(code **)(PTR__ZTVN4Aska4TaskE_02cbe020 + 0x68);
    plVar7 = plVar2 + 0x18;
    *plVar7 = (long)(PTR__ZTVN4Aska4TaskE_02cbe020 + 0x10);
    plVar2[0x1b] = 0;
    *(undefined2 *)((long)plVar2 + 0xe4) = 0;
    *(undefined1 *)((long)plVar2 + 0xe6) = 0;
    uVar1 = (*pcVar3)(plVar7);
    *(undefined4 *)(plVar2 + 0x1c) = uVar1;
    plVar2[0x1e] = 0;
    plVar2[0x21] = 0;
    plVar2[0x22] = 0;
    plVar2[0x20] = 0;
    puVar6 = PTR__ZTVN9Framework16CResourceElement13CFinishNotifyE_02cbe2d0;
    *(undefined1 *)(plVar2 + 0x25) = 0;
    *(undefined1 *)((long)plVar2 + 0x14a) = 0;
    *(undefined2 *)(plVar2 + 0x29) = 0;
    plVar2[0x27] = 0;
    plVar2[0x28] = 0;
    plVar2[0x26] = (long)plVar2;
    puVar5 = PTR__ZTVN9Framework20CResourceElement_CsvE_02cba710;
    plVar2[0x24] = (long)(puVar6 + 0x10);
    *plVar2 = (long)(puVar5 + 0x10);
    *plVar7 = (long)(puVar5 + 0xb0);
    plVar2[0x1d] = 0xe;
code_r0x01f90ca8:
    Framework::CFileLoader::DummySize(unsigned long)(plVar2,1);
    return plVar2;
  case 0xf:
    plVar2 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x150,PTR__ZSt7nothrow_02cb9a80);
    if (plVar2 == (long *)0x0) {
      return (long *)0x0;
    }
    Framework::CFileLoader::CFileLoader()(plVar2);
    plVar2[0x19] = 0;
    plVar2[0x1a] = 0;
    pcVar3 = *(code **)(PTR__ZTVN4Aska4TaskE_02cbe020 + 0x68);
    plVar7 = plVar2 + 0x18;
    *plVar7 = (long)(PTR__ZTVN4Aska4TaskE_02cbe020 + 0x10);
    plVar2[0x1b] = 0;
    *(undefined2 *)((long)plVar2 + 0xe4) = 0;
    *(undefined1 *)((long)plVar2 + 0xe6) = 0;
    uVar1 = (*pcVar3)(plVar7);
    *(undefined4 *)(plVar2 + 0x1c) = uVar1;
    plVar2[0x1e] = 0;
    plVar2[0x21] = 0;
    plVar2[0x22] = 0;
    plVar2[0x20] = 0;
    puVar6 = PTR__ZTVN9Framework16CResourceElement13CFinishNotifyE_02cbe2d0;
    *(undefined1 *)(plVar2 + 0x25) = 0;
    *(undefined1 *)((long)plVar2 + 0x14a) = 0;
    *(undefined2 *)(plVar2 + 0x29) = 0;
    plVar2[0x27] = 0;
    plVar2[0x28] = 0;
    plVar2[0x26] = (long)plVar2;
    puVar5 = PTR__ZTVN9Framework20CResourceElement_GuiE_02cbd030;
    plVar2[0x24] = (long)(puVar6 + 0x10);
    *plVar2 = (long)(puVar5 + 0x10);
    lVar4 = 0xf;
    goto code_r0x01f90f2c;
  case 0x10:
    plVar2 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x150,PTR__ZSt7nothrow_02cb9a80);
    if (plVar2 == (long *)0x0) {
      return (long *)0x0;
    }
    Framework::CFileLoader::CFileLoader()(plVar2);
    plVar2[0x19] = 0;
    plVar2[0x1a] = 0;
    pcVar3 = *(code **)(PTR__ZTVN4Aska4TaskE_02cbe020 + 0x68);
    plVar7 = plVar2 + 0x18;
    *plVar7 = (long)(PTR__ZTVN4Aska4TaskE_02cbe020 + 0x10);
    plVar2[0x1b] = 0;
    *(undefined2 *)((long)plVar2 + 0xe4) = 0;
    *(undefined1 *)((long)plVar2 + 0xe6) = 0;
    uVar1 = (*pcVar3)(plVar7);
    *(undefined4 *)(plVar2 + 0x1c) = uVar1;
    plVar2[0x21] = 0;
    plVar2[0x22] = 0;
    plVar2[0x20] = 0;
    puVar5 = PTR__ZTVN9Framework16CResourceElement13CFinishNotifyE_02cbe2d0;
    *(undefined1 *)(plVar2 + 0x25) = 0;
    *(undefined1 *)((long)plVar2 + 0x14a) = 0;
    *(undefined2 *)(plVar2 + 0x29) = 0;
    plVar2[0x27] = 0;
    plVar2[0x28] = 0;
    plVar2[0x26] = (long)plVar2;
    lVar4 = 0x10;
    puVar6 = PTR__ZTVN9Framework20CResourceElement_NvdE_02cc1258;
    break;
  case 0x11:
    plVar2 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x150,PTR__ZSt7nothrow_02cb9a80);
    if (plVar2 == (long *)0x0) {
      return (long *)0x0;
    }
    Framework::CFileLoader::CFileLoader()(plVar2);
    plVar2[0x19] = 0;
    plVar2[0x1a] = 0;
    pcVar3 = *(code **)(PTR__ZTVN4Aska4TaskE_02cbe020 + 0x68);
    plVar7 = plVar2 + 0x18;
    *plVar7 = (long)(PTR__ZTVN4Aska4TaskE_02cbe020 + 0x10);
    plVar2[0x1b] = 0;
    *(undefined2 *)((long)plVar2 + 0xe4) = 0;
    *(undefined1 *)((long)plVar2 + 0xe6) = 0;
    uVar1 = (*pcVar3)(plVar7);
    *(undefined4 *)(plVar2 + 0x1c) = uVar1;
    plVar2[0x1e] = 0;
    plVar2[0x21] = 0;
    plVar2[0x22] = 0;
    plVar2[0x20] = 0;
    puVar6 = PTR__ZTVN9Framework16CResourceElement13CFinishNotifyE_02cbe2d0;
    *(undefined1 *)(plVar2 + 0x25) = 0;
    *(undefined1 *)((long)plVar2 + 0x14a) = 0;
    *(undefined2 *)(plVar2 + 0x29) = 0;
    plVar2[0x27] = 0;
    plVar2[0x28] = 0;
    plVar2[0x26] = (long)plVar2;
    puVar5 = PTR__ZTVN9Framework20CResourceElement_CsfE_02cbe288;
    plVar2[0x24] = (long)(puVar6 + 0x10);
    *plVar2 = (long)(puVar5 + 0x10);
    lVar4 = 0x11;
    goto code_r0x01f90f2c;
  case 0x12:
    plVar2 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x150,PTR__ZSt7nothrow_02cb9a80);
    if (plVar2 == (long *)0x0) {
      return (long *)0x0;
    }
    Framework::CFileLoader::CFileLoader()(plVar2);
    plVar2[0x19] = 0;
    plVar2[0x1a] = 0;
    pcVar3 = *(code **)(PTR__ZTVN4Aska4TaskE_02cbe020 + 0x68);
    plVar7 = plVar2 + 0x18;
    *plVar7 = (long)(PTR__ZTVN4Aska4TaskE_02cbe020 + 0x10);
    plVar2[0x1b] = 0;
    *(undefined2 *)((long)plVar2 + 0xe4) = 0;
    *(undefined1 *)((long)plVar2 + 0xe6) = 0;
    uVar1 = (*pcVar3)(plVar7);
    *(undefined4 *)(plVar2 + 0x1c) = uVar1;
    plVar2[0x1e] = 0;
    plVar2[0x21] = 0;
    plVar2[0x22] = 0;
    plVar2[0x20] = 0;
    puVar6 = PTR__ZTVN9Framework16CResourceElement13CFinishNotifyE_02cbe2d0;
    *(undefined1 *)(plVar2 + 0x25) = 0;
    *(undefined1 *)((long)plVar2 + 0x14a) = 0;
    *(undefined2 *)(plVar2 + 0x29) = 0;
    plVar2[0x27] = 0;
    plVar2[0x28] = 0;
    plVar2[0x26] = (long)plVar2;
    puVar5 = PTR__ZTVN9Framework20CResourceElement_FpkE_02cbbfe8;
    plVar2[0x24] = (long)(puVar6 + 0x10);
    *plVar2 = (long)(puVar5 + 0x10);
    lVar4 = 0x12;
code_r0x01f90f2c:
    *plVar7 = (long)(puVar5 + 0xb0);
code_r0x01f90f34:
    plVar2[0x1d] = lVar4;
    return plVar2;
  }
  plVar2[0x1d] = lVar4;
  plVar2[0x1e] = 0;
  plVar2[0x24] = (long)(puVar5 + 0x10);
  *plVar2 = (long)(puVar6 + 0x10);
  *plVar7 = (long)(puVar6 + 0xb0);
  return plVar2;
}

// ==== Framework::CResourceElement::tMappingImage::tMappingImage()
// vaddr 0x1e90f48 | ghidra 0x1f90f48 | size 20 | symbol _ZN9Framework16CResourceElement13tMappingImageC2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework16CResourceElement13tMappingImageC1Ev(undefined8 *param_1)

{
  *(undefined4 *)(param_1 + 5) = 0;
  param_1[4] = 0;
  param_1[1] = 0;
  *param_1 = 0;
  param_1[3] = 0;
  param_1[2] = 0;
  return;
}

// ==== Framework::CResourceElement::tMappingImage::~tMappingImage()
// vaddr 0x1e90f5c | ghidra 0x1f90f5c | size 20 | symbol _ZN9Framework16CResourceElement13tMappingImageD2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework16CResourceElement13tMappingImageD1Ev(long param_1)

{
  if ((*(byte *)(param_1 + 0x10) & 1) == 0) {
    return;
  }
  (*(code *)PTR__ZN9Framework37CAssignedMemoryManagerForSTLAllocator4FreeEPv_02ca11c0)
            (*(undefined8 *)(param_1 + 0x20));
  return;
}

// ==== Framework::CResourceElement::tMemoryDescription::tMemoryDescription()
// vaddr 0x1e90f70 | ghidra 0x1f90f70 | size 12 | symbol _ZN9Framework16CResourceElement18tMemoryDescriptionC2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework16CResourceElement18tMemoryDescriptionC1Ev(undefined2 *param_1)

{
  *param_1 = 0;
  *(undefined1 *)(param_1 + 1) = 0;
  return;
}

// ==== Framework::CResourceElement::tMemoryDescription::IsHigh() const
// vaddr 0x1e90f7c | ghidra 0x1f90f7c | size 48 | symbol _ZNK9Framework16CResourceElement18tMemoryDescription6IsHighEv | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK9Framework16CResourceElement18tMemoryDescription6IsHighEv(char *param_1)

{
  if (*param_1 != '\0') {
    return true;
  }
  if (param_1[1] != '\0') {
    return true;
  }
  return param_1[2] != '\0';
}

// ==== Framework::CResourceElement::tMemoryDescription::Create(bool, bool, bool)
// vaddr 0x1e90fac | ghidra 0x1f90fac | size 100 | symbol _ZN9Framework16CResourceElement18tMemoryDescription6CreateEbbb | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZN9Framework16CResourceElement18tMemoryDescription6CreateEbbb
                (ulong param_1,uint param_2,uint param_3)

{
  byte *pbVar1;
  byte *pbVar2;
  ulong uVar3;
  ulong uVar4;
  ulong uVar5;
  byte abStack_c [12];
  
  uVar4 = 0;
  uVar5 = 0;
  uVar3 = 0;
  abStack_c[8] = 0;
  abStack_c[4] = 0;
  abStack_c[0] = 0;
  if ((param_1 & 1) != 0) {
    pbVar1 = abStack_c + 4;
    if ((param_2 & 1) == 0) {
      pbVar1 = abStack_c + 8;
    }
    pbVar2 = abStack_c;
    if ((param_3 & 1) == 0) {
      pbVar2 = pbVar1;
    }
    *pbVar2 = 1;
    uVar3 = (ulong)abStack_c[8];
    uVar5 = (ulong)abStack_c[4];
    uVar4 = (ulong)abStack_c[0];
  }
  return uVar3 | uVar5 << 8 | uVar4 << 0x10;
}

// ==== Framework::CResourceElement::CResourceElement(unsigned int)
// vaddr 0x1e91010 | ghidra 0x1f91010 | size 160 | symbol _ZN9Framework16CResourceElementC1Ej | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework16CResourceElementC2Ej(long *param_1,undefined4 param_2)

{
  undefined *puVar1;
  undefined *puVar2;
  undefined4 uVar3;
  code *pcVar4;
  long *plVar5;
  
  Framework::CFileLoader::CFileLoader()();
  param_1[0x19] = 0;
  param_1[0x1a] = 0;
  pcVar4 = *(code **)(PTR__ZTVN4Aska4TaskE_02cbe020 + 0x68);
  plVar5 = param_1 + 0x18;
  *plVar5 = (long)(PTR__ZTVN4Aska4TaskE_02cbe020 + 0x10);
  param_1[0x1b] = 0;
  *(undefined2 *)((long)param_1 + 0xe4) = 0;
  *(undefined1 *)((long)param_1 + 0xe6) = 0;
  uVar3 = (*pcVar4)(plVar5);
  *(undefined4 *)(param_1 + 0x1c) = uVar3;
  puVar1 = PTR__ZTVN9Framework16CResourceElementE_02cb8700;
  *param_1 = (long)(PTR__ZTVN9Framework16CResourceElementE_02cb8700 + 0x10);
  puVar2 = PTR__ZTVN9Framework16CResourceElement13CFinishNotifyE_02cbe2d0;
  *plVar5 = (long)(puVar1 + 0xb0);
  *(undefined4 *)(param_1 + 0x1d) = param_2;
  *(undefined4 *)((long)param_1 + 0xec) = 0;
  param_1[0x1e] = 0;
  param_1[0x21] = 0;
  param_1[0x22] = 0;
  param_1[0x20] = 0;
  param_1[0x24] = (long)(puVar2 + 0x10);
  *(undefined1 *)(param_1 + 0x25) = 0;
  *(undefined2 *)(param_1 + 0x29) = 0;
  *(undefined1 *)((long)param_1 + 0x14a) = 0;
  param_1[0x27] = 0;
  param_1[0x28] = 0;
  param_1[0x26] = (long)param_1;
  return;
}

// ==== Framework::CResourceElement::_Initialize(unsigned int, unsigned long, Framework::CResourceElement::tMemoryDescription const&)
// vaddr 0x1e910b0 | ghidra 0x1f910b0 | size 136 | symbol _ZN9Framework16CResourceElement11_InitializeEjmRKNS0_18tMemoryDescriptionE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework16CResourceElement11_InitializeEjmRKNS0_18tMemoryDescriptionE
               (long param_1,undefined4 param_2,undefined8 param_3,undefined2 *param_4)

{
  undefined1 uVar1;
  
  if (*(int *)(param_1 + 0xec) != 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029651b8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Resource.cpp"*/,0x8c,&UNK_0296520c);
  }
  *(undefined2 *)(param_1 + 0x148) = *param_4;
  uVar1 = *(undefined1 *)(param_4 + 1);
  *(undefined4 *)(param_1 + 0xec) = 1;
  *(undefined1 *)(param_1 + 0x14a) = uVar1;
  Framework::CFileLoader::Initialize(unsigned int, unsigned long, bool)(param_1,param_2,param_3,*(undefined1 *)(param_1 + 0x148));
  (*(code *)PTR__ZN4Aska11TaskManager3AddEPNS_4TaskE_02c95ab0)
            (*(undefined8 *)PTR__ZN4Aska6Global20m_pSystemTaskManagerE_02cbf620,param_1 + 0xc0);
  return;
}

// ==== Framework::CResourceElement::_InitializeByMemory(void*, Framework::CResourceElement::tMemoryDescription const&)
// vaddr 0x1e91138 | ghidra 0x1f91138 | size 168 | symbol _ZN9Framework16CResourceElement19_InitializeByMemoryEPvRKNS0_18tMemoryDescriptionE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework16CResourceElement19_InitializeByMemoryEPvRKNS0_18tMemoryDescriptionE
               (long param_1,long param_2,undefined2 *param_3)

{
  undefined2 uVar1;
  
  if (*(int *)(param_1 + 0xec) != 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029651b8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Resource.cpp"*/,0xa3,&UNK_0296520c);
  }
  if (*(long *)(param_1 + 0xf0) != 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029651b8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Resource.cpp"*/,0xa4,&UNK_02965222/*"m_pInitializedByDirectMemory isn't null.(%08x)"*/);
  }
  if (param_2 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029651b8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Resource.cpp"*/,0xa5,&UNK_02965251/*"apDirectMemory is null."*/);
  }
  *(undefined1 *)(param_1 + 0x14a) = *(undefined1 *)(param_3 + 1);
  uVar1 = *param_3;
  *(long *)(param_1 + 0xf0) = param_2;
  *(undefined4 *)(param_1 + 0xec) = 1;
  *(undefined2 *)(param_1 + 0x148) = uVar1;
  (*(code *)PTR__ZN4Aska11TaskManager3AddEPNS_4TaskE_02c95ab0)
            (*(undefined8 *)PTR__ZN4Aska6Global20m_pSystemTaskManagerE_02cbf620,param_1 + 0xc0);
  return;
}

// ==== Framework::CResourceElement::_InitializeByDirectFile(char const*, unsigned long, Framework::CResourceElement::tMemoryDescription const&, char const*)
// vaddr 0x1e911e0 | ghidra 0x1f911e0 | size 156 | symbol _ZN9Framework16CResourceElement23_InitializeByDirectFileEPKcmRKNS0_18tMemoryDescriptionES2_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework16CResourceElement23_InitializeByDirectFileEPKcmRKNS0_18tMemoryDescriptionES2_
               (long param_1,undefined8 param_2,undefined8 param_3,undefined2 *param_4,long param_5)

{
  if (*(int *)(param_1 + 0xec) != 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029651b8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Resource.cpp"*/,0xc6,&UNK_0296520c);
  }
  *(undefined1 *)(param_1 + 0x14a) = *(undefined1 *)(param_4 + 1);
  *(undefined2 *)(param_1 + 0x148) = *param_4;
  if (param_5 != 0) {
    Framework::CFileLoader::EnableDirectLoad(char const*)(param_1,param_5);
  }
  *(undefined4 *)(param_1 + 0xec) = 1;
  Framework::CFileLoader::InitializeByDirectFile(char const*, unsigned long, bool)(param_1,param_2,param_3,*(undefined1 *)(param_1 + 0x148));
  (*(code *)PTR__ZN4Aska11TaskManager3AddEPNS_4TaskE_02c95ab0)
            (*(undefined8 *)PTR__ZN4Aska6Global20m_pSystemTaskManagerE_02cbf620,param_1 + 0xc0);
  return;
}

// ==== Framework::CResourceElement::Release()
// vaddr 0x1e9127c | ghidra 0x1f9127c | size 240 | symbol _ZN9Framework16CResourceElement7ReleaseEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework16CResourceElement7ReleaseEv(long param_1)

{
  long lVar1;
  undefined8 *puVar2;
  long lVar3;
  undefined *puVar4;
  long lVar5;
  undefined8 *puVar6;
  undefined8 *puVar7;
  
  if ((*(int *)(param_1 + 0xec) != 0) && (*(int *)(param_1 + 0xec) != 9)) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029651b8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Resource.cpp"*/,0xd4,&UNK_02965269/*"Bad access timing.(%d)"*/);
  }
  Framework::CFileLoader::Release()(param_1);
  puVar6 = *(undefined8 **)(param_1 + 0x100);
  puVar2 = *(undefined8 **)(param_1 + 0x108);
  *(undefined8 *)(param_1 + 0xf0) = 0;
  puVar4 = PTR__ZN4Aska6Global21m_systemDeleteManagerE_02cb77c0;
  if (puVar6 != puVar2) {
    do {
      puVar7 = puVar6 + 6;
      Aska::DeleteManager::AddMain(void*, unsigned char, unsigned char, Aska::IDeleteHandler*)(puVar4,*puVar6,0,1,0);
      puVar6 = puVar7;
    } while (puVar2 != puVar7);
    lVar1 = *(long *)(param_1 + 0x100);
    lVar5 = *(long *)(param_1 + 0x108);
    while (lVar3 = lVar5, lVar3 != lVar1) {
      *(long *)(param_1 + 0x108) = lVar3 + -0x30;
      lVar5 = lVar3 + -0x30;
      if ((*(byte *)(lVar3 + -0x20) & 1) != 0) {
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(*(undefined8 *)(lVar3 + -0x10));
        lVar5 = *(long *)(param_1 + 0x108);
      }
    }
  }
  if ((*(long *)(param_1 + 0x140) != 0) &&
     (Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029651b8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Resource.cpp"*/,0xdd,&UNK_02965280/*"m_pDecompressInfo isn't null.(%08x)"*/), *(long *)(param_1 + 0x140) != 0)) {
    operator delete(void*)();
    *(undefined8 *)(param_1 + 0x140) = 0;
  }
  *(undefined4 *)(param_1 + 0xec) = 0;
  return;
}

// ==== Framework::CResourceElement::Run(int)
// vaddr 0x1e9136c | ghidra 0x1f9136c | size 4248 | symbol _ZN9Framework16CResourceElement3RunEi | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Possible PIC construction at 0x01f91720: Changing call to branch */
/* WARNING: Possible PIC construction at 0x01f91ecc: Changing call to branch */
/* WARNING: Possible PIC construction at 0x01f91f18: Changing call to branch */
/* WARNING: Possible PIC construction at 0x01f91f84: Changing call to branch */
/* WARNING: Possible PIC construction at 0x01f920b8: Changing call to branch */
/* WARNING: Possible PIC construction at 0x01f921b8: Changing call to branch */
/* WARNING: Possible PIC construction at 0x01f92288: Changing call to branch */
/* WARNING: Possible PIC construction at 0x01f92010: Changing call to branch */
/* WARNING: Possible PIC construction at 0x01f92044: Changing call to branch */
/* WARNING: Possible PIC construction at 0x01f91b08: Changing call to branch */
/* WARNING: Possible PIC construction at 0x01f91b94: Changing call to branch */
/* WARNING: Possible PIC construction at 0x01f91ccc: Changing call to branch */
/* WARNING: Possible PIC construction at 0x01f91dd0: Changing call to branch */
/* WARNING: Possible PIC construction at 0x01f92350: Changing call to branch */
/* WARNING: Possible PIC construction at 0x01f923d8: Changing call to branch */
/* WARNING: Possible PIC construction at 0x01f91c20: Changing call to branch */
/* WARNING: Possible PIC construction at 0x01f91c54: Changing call to branch */
/* WARNING: Possible PIC construction at 0x01f9146c: Changing call to branch */
/* WARNING: Possible PIC construction at 0x01f917b0: Changing call to branch */
/* WARNING: Possible PIC construction at 0x01f9183c: Changing call to branch */
/* WARNING: Possible PIC construction at 0x01f9196c: Changing call to branch */
/* WARNING: Possible PIC construction at 0x01f919d8: Changing call to branch */
/* WARNING: Possible PIC construction at 0x01f918c8: Changing call to branch */
/* WARNING: Possible PIC construction at 0x01f918fc: Changing call to branch */
/* WARNING: Possible PIC construction at 0x01f91774: Changing call to branch */
/* WARNING: Possible PIC construction at 0x01f91644: Changing call to branch */
/* WARNING: Possible PIC construction at 0x01f916a4: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0x01f91778) */
/* WARNING: Removing unreachable block (ram,0x01f92354) */
/* WARNING: Removing unreachable block (ram,0x01f91f1c) */
/* WARNING: Removing unreachable block (ram,0x01f91724) */
/* WARNING: Removing unreachable block (ram,0x01f91648) */
/* WARNING: Removing unreachable block (ram,0x01f91fd4) */
/* WARNING: Removing unreachable block (ram,0x01f91fe0) */
/* WARNING: Removing unreachable block (ram,0x01f91fec) */
/* WARNING: Removing unreachable block (ram,0x01f91be4) */
/* WARNING: Removing unreachable block (ram,0x01f91bf0) */
/* WARNING: Removing unreachable block (ram,0x01f91bfc) */
/* WARNING: Removing unreachable block (ram,0x01f91c00) */
/* WARNING: Removing unreachable block (ram,0x01f91c24) */
/* WARNING: Removing unreachable block (ram,0x01f91c40) */
/* WARNING: Removing unreachable block (ram,0x01f91c58) */
/* WARNING: Removing unreachable block (ram,0x01f91c6c) */
/* WARNING: Removing unreachable block (ram,0x01f91c7c) */
/* WARNING: Removing unreachable block (ram,0x01f91c0c) */
/* WARNING: Removing unreachable block (ram,0x01f918b4) */
/* WARNING: Removing unreachable block (ram,0x01f9188c) */
/* WARNING: Removing unreachable block (ram,0x01f91898) */
/* WARNING: Removing unreachable block (ram,0x01f918a4) */
/* WARNING: Removing unreachable block (ram,0x01f918a8) */
/* WARNING: Removing unreachable block (ram,0x01f918cc) */
/* WARNING: Removing unreachable block (ram,0x01f918e8) */
/* WARNING: Removing unreachable block (ram,0x01f91900) */
/* WARNING: Removing unreachable block (ram,0x01f9190c) */
/* WARNING: Removing unreachable block (ram,0x01f9191c) */
/* WARNING: Removing unreachable block (ram,0x01f91ff0) */
/* WARNING: Removing unreachable block (ram,0x01f92014) */
/* WARNING: Removing unreachable block (ram,0x01f92030) */
/* WARNING: Removing unreachable block (ram,0x01f92048) */
/* WARNING: Removing unreachable block (ram,0x01f9205c) */
/* WARNING: Removing unreachable block (ram,0x01f9206c) */
/* WARNING: Removing unreachable block (ram,0x01f91ffc) */
/* WARNING: Restarted to delay deadcode elimination for space: stack */

void _ZN9Framework16CResourceElement3RunEi(long *param_1)

{
  long *plVar1;
  long *plVar2;
  uint uVar3;
  uint uVar4;
  bool bVar5;
  bool bVar6;
  ulong uVar7;
  char *pcVar8;
  int *piVar9;
  undefined *puVar10;
  undefined8 uVar11;
  ulong uVar12;
  ulong uVar13;
  undefined *puVar14;
  undefined4 uVar15;
  ulong uVar16;
  int iVar17;
  long lVar18;
  undefined8 *puVar19;
  undefined8 *puVar20;
  uint uVar21;
  long lVar22;
  ulong *puVar23;
  long lVar24;
  undefined8 uStack_90;
  undefined8 uStack_88;
  ulong uStack_80;
  undefined8 uStack_78;
  undefined8 uStack_70;
  undefined4 uStack_68;
  
  switch(*(undefined4 *)((long)param_1 + 0xec)) {
  case 2:
    (*(code *)PTR__ZN9Framework16CResourceElement18PhaseLoadingFinishEv_02c9d720)(param_1);
    return;
  case 3:
    if ((char)param_1[0x25] == '\0') {
      return;
    }
    iVar17 = (int)param_1[0x1d];
    *(undefined4 *)((long)param_1 + 0xec) = 4;
    if (iVar17 == 4) goto code_r0x011f6ac0;
    if (iVar17 != 3) {
      if (iVar17 != 2) {
        return;
      }
      goto code_r0x011f6ac0;
    }
code_r0x01f91510:
    (**(code **)(*param_1 + 0x88))(param_1);
    uVar15 = 8;
    goto code_r0x01f923e0;
  case 4:
    break;
  case 5:
    if (param_1[0x20] != param_1[0x21]) {
      bVar5 = false;
      lVar24 = param_1[0x20];
      do {
        lVar18 = lVar24 + 0x30;
        bVar6 = *(int *)(lVar24 + 0x28) != 200;
        bVar5 = (bool)(bVar5 | bVar6);
        if (bVar6) break;
        lVar24 = lVar18;
      } while (param_1[0x21] != lVar18);
      if (bVar5) {
        return;
      }
    }
    goto code_r0x011f6ac0;
  case 6:
    if ((int)param_1[0x1f] != 400) {
      if ((int)param_1[0x1f] != 200) {
        return;
      }
      switch((int)param_1[0x1d]) {
      case 2:
      case 4:
      case 0x11:
        goto code_r0x011f6ac0;
      case 3:
        goto code_r0x01f91510;
      default:
        puVar10 = &UNK_029651b8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Resource.cpp"*/;
        puVar14 = &UNK_029654b8/*"Internal error.(%d)"*/;
        uVar11 = 0x27c;
        goto code_r0x011d64a0;
      }
    }
    puVar10 = &UNK_029651b8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Resource.cpp"*/;
    puVar14 = &UNK_029654cc/*"Mapping failed."*/;
    uVar11 = 0x290;
    goto code_r0x011d64a0;
  case 7:
    lVar24 = param_1[0x20];
    if (lVar24 != param_1[0x21]) {
      iVar17 = 0;
      do {
        if ((iVar17 != 0) && (*(int *)(lVar24 + 0x28) != 200)) {
          return;
        }
        lVar24 = lVar24 + 0x30;
        iVar17 = iVar17 + -1;
      } while (param_1[0x21] != lVar24);
    }
    goto code_r0x011f6ac0;
  case 8:
    uVar7 = (**(code **)(*param_1 + 0x80))(param_1);
    if ((uVar7 & 1) != 0) goto code_r0x011f6ac0;
  default:
    goto code_r0x01f923e4;
  }
  switch((int)param_1[0x1d]) {
  default:
    goto code_r0x011f6ac0;
  case 2:
  case 3:
  case 4:
    pcVar8 = (char *)(**(code **)(*param_1 + 0x78))(param_1);
    if (((*(uint *)(param_1 + 0x1d) & 0xfffffffe) == 2) &&
       (((*pcVar8 != ' ' || (pcVar8[1] != 'F')) || ((pcVar8[2] != 'I' || (pcVar8[3] != 'A')))))) {
      Framework::CFileLoader::pFileName() const(param_1);
      puVar10 = &UNK_029651b8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Resource.cpp"*/;
      puVar14 = &UNK_029652a4/*"Illegal AIF format.[%s]"*/;
      uVar11 = 300;
      goto code_r0x011d64a0;
    }
    if ((*(uint *)(param_1 + 0x1d) == 4) &&
       ((((*pcVar8 != ' ' || (pcVar8[1] != 'F')) || (pcVar8[2] != 'S')) || (pcVar8[3] != 'A')))) {
      Framework::CFileLoader::pFileName() const(param_1);
      puVar10 = &UNK_029651b8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Resource.cpp"*/;
      puVar14 = &UNK_029652bc/*"Illegal ASF format.[%s]"*/;
      uVar11 = 0x134;
      goto code_r0x011d64a0;
    }
    *(undefined4 *)(param_1 + 0x1f) = 0;
    lVar24 = param_1[0x1e];
    uVar11 = *(undefined8 *)PTR__ZN4Aska6Global15m_pMappingQueueE_02cbda98;
    if (lVar24 == 0) {
      lVar24 = (**(code **)(*param_1 + 0x78))(param_1);
    }
    lVar24 = Aska::MappingQueue::Add(void*, Aska::AFF::AskaFile*, unsigned int*, Aska::INotify*, int)(uVar11,lVar24,lVar24,param_1 + 0x1f,0,0xffffffff);
    if (lVar24 == 0) {
      uVar11 = 0x145;
code_r0x01f923d8:
      puVar14 = &UNK_029614eb/*"result is null."*/;
      puVar10 = &UNK_029651b8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Resource.cpp"*/;
code_r0x011d64a0:
      (*(code *)PTR__ZN9Framework9gDoAssertEPKciS1_z_02ca3240)(puVar10,uVar11,puVar14);
      return;
    }
    goto code_r0x01f923dc;
  case 9:
    piVar9 = (int *)(**(code **)(*param_1 + 0x78))(param_1);
    if ((piVar9[1] != 0x12060400) || (*piVar9 != 0x41455400)) {
      puVar10 = &UNK_029651b8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Resource.cpp"*/;
      puVar14 = &UNK_02960a3c/*"Illegal Aet image."*/;
      uVar11 = 0x160;
      goto code_r0x011d64a0;
    }
    goto code_r0x011f6ac0;
  case 10:
  case 0xb:
  case 0xc:
  case 0xf:
    piVar9 = (int *)(**(code **)(*param_1 + 0x78))(param_1);
    if (*piVar9 != 0x46534900) {
      puVar10 = &UNK_029651b8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Resource.cpp"*/;
      puVar14 = &UNK_029652d4/*"FileStream: Illegal FileStream image. (Unknown magic code)"*/;
      uVar11 = 0x173;
      goto code_r0x011d64a0;
    }
    if (0x20130304 < (uint)piVar9[1]) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029651b8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Resource.cpp"*/,0x174,&UNK_0296530f/*"FileStream: Illegal FileStream image version. (%08x/%08x)"*/,piVar9[1],0x20130304);
    }
code_r0x011f6ac0:
    *(undefined4 *)((long)param_1 + 0xec) = 9;
    (*(code *)PTR__ZN4Aska4Task6RemoveEv_02cb3550)(param_1 + 0x18);
    return;
  case 0xd:
    piVar9 = (int *)(**(code **)(*param_1 + 0x78))(param_1);
    if (*piVar9 != 0x46534900) {
      puVar10 = &UNK_029651b8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Resource.cpp"*/;
      puVar14 = &UNK_02965349/*"Tpk: Illegal FileStream image. (Unknown magic code)"*/;
      uVar11 = 0x17d;
      goto code_r0x011d64a0;
    }
    if (0x20130304 < (uint)piVar9[1]) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029651b8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Resource.cpp"*/,0x17e,&UNK_0296537d/*"Tpk: Illegal FileStream image version. (%08x/%08x)"*/,piVar9[1],0x20130304);
    }
    plVar1 = param_1 + 0x20;
    std::__ndk1::vector<Framework::CResourceElement::tMappingImage, Framework::CSTLAllocator<Framework::CResourceElement::tMappingImage, Framework::CSTLVectorAllocatorInf> >::reserve(unsigned long)(plVar1,piVar9[2]);
    if (piVar9[2] != 0) {
      uVar21 = 0;
      plVar2 = param_1 + 0x21;
      do {
        uStack_68 = 0;
        uStack_70 = 0;
        uStack_88 = 0;
        uStack_90 = 0;
        uStack_78 = 0;
        uStack_80 = 0;
        puVar19 = (undefined8 *)param_1[0x21];
        if (puVar19 < (undefined8 *)param_1[0x22]) {
          if (puVar19 == (undefined8 *)0x0) {
            uVar11 = 0xcc;
            puVar10 = &UNK_0296188c/*"C:\BAS_Submission\Client\Library\Framework\Source\Framework/STL_Allocator.h"*/;
            puVar14 = &UNK_027dc43e/*"apAssignedMemory is null."*/;
            goto code_r0x011d64a0;
          }
          puVar19[1] = 0;
          *puVar19 = 0;
          puVar19[2] = 0;
          puVar19[3] = 0;
          puVar19[4] = 0;
          puVar19[4] = 0;
          puVar19[3] = 0;
          puVar19[2] = 0;
          uStack_68 = 0;
          uStack_70 = 0;
          uStack_78 = 0;
          uStack_80 = 0;
          uStack_88 = 0;
          uStack_90 = 0;
          *(undefined4 *)(puVar19 + 5) = 0;
          *plVar2 = *plVar2 + 0x30;
        }
        else {
          void std::__ndk1::vector<Framework::CResourceElement::tMappingImage, Framework::CSTLAllocator<Framework::CResourceElement::tMappingImage, Framework::CSTLVectorAllocatorInf> >::__push_back_slow_path<Framework::CResourceElement::tMappingImage>(Framework::CResourceElement::tMappingImage&&)(plVar1,&uStack_90);
          if ((uStack_80 & 1) != 0) {
            Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_70);
          }
        }
        lVar24 = *plVar2;
        if ((uint)piVar9[2] <= uVar21) {
          uVar11 = 0xf1;
          puVar10 = &UNK_02960f2f/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Tools\MakeFileStream/FileStream_Image.h"*/;
          puVar14 = &UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/;
          goto code_r0x011d64a0;
        }
        uVar7 = (ulong)(uint)piVar9[(ulong)uVar21 * 4 + 6];
        pcVar8 = (char *)((ulong)(uint)piVar9[(ulong)uVar21 * 4 + 5] + (long)piVar9);
        lVar18 = (ulong)(uint)piVar9[(ulong)uVar21 * 4 + 4] + (long)piVar9;
        if ((((*pcVar8 != ' ') || (pcVar8[1] != 'F')) || (pcVar8[2] != 'I')) || (pcVar8[3] != 'A'))
        {
          Framework::CFileLoader::pFileName() const(param_1);
          uVar11 = 0x189;
          puVar10 = &UNK_029651b8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Resource.cpp"*/;
          puVar14 = &UNK_029653b0/*"Illegal AIF format.[%s] Index[%d]"*/;
          goto code_r0x011d64a0;
        }
        uVar16 = strlen(lVar18);
        puVar23 = (ulong *)(lVar24 + -0x20);
        uVar13 = (ulong)*(byte *)puVar23;
        if ((*(byte *)puVar23 & 1) == 0) {
          uVar12 = 0x16;
          lVar22 = uVar16 - 0x16;
          if (0x15 < uVar16 && lVar22 != 0) goto code_r0x01f91a48;
code_r0x01f91a00:
          if ((uVar13 & 1) == 0) {
            lVar22 = lVar24 + -0x1f;
          }
          else {
            lVar22 = *(long *)(lVar24 + -0x10);
          }
          if (uVar16 != 0) {
            memmove(lVar22,lVar18,uVar16);
          }
          *(undefined1 *)(lVar22 + uVar16) = 0;
          if ((*(byte *)puVar23 & 1) == 0) {
            *(byte *)puVar23 = (byte)(uVar16 << 1);
          }
          else {
            *(ulong *)(lVar24 + -0x18) = uVar16;
          }
        }
        else {
          uVar13 = *puVar23;
          uVar12 = (uVar13 & 0xfffffffffffffffe) - 1;
          lVar22 = uVar16 - uVar12;
          if (uVar16 < uVar12 || lVar22 == 0) goto code_r0x01f91a00;
code_r0x01f91a48:
          if ((uVar13 & 1) == 0) {
            uVar13 = (ulong)(((uint)uVar13 & 0xfe) >> 1);
          }
          else {
            uVar13 = *(ulong *)(lVar24 + -0x18);
          }
          string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(puVar23,uVar12,lVar22,uVar13,0,uVar13,uVar16,lVar18);
        }
        *(ulong *)(lVar24 + -0x28) = uVar7;
        if (*(char *)((long)param_1 + 0x14a) == '\0') {
          uVar11 = Framework::gMAlloc(unsigned long, unsigned long)(uVar7,0x1000);
        }
        else {
          uVar11 = Framework::gMAllocHigh(unsigned long, unsigned long)(uVar7,0x1000);
        }
        *(undefined8 *)(lVar24 + -0x30) = uVar11;
        memcpy(uVar11,pcVar8,*(undefined8 *)(lVar24 + -0x28));
        uVar21 = uVar21 + 1;
      } while (uVar21 < (uint)piVar9[2]);
    }
    Framework::CFileLoader::DirectReleaseBuffer(bool)(param_1,0);
    puVar10 = PTR__ZN4Aska6Global15m_pMappingQueueE_02cbda98;
    puVar20 = (undefined8 *)param_1[0x21];
    for (puVar19 = (undefined8 *)*plVar1; puVar19 != puVar20; puVar19 = puVar19 + 6) {
      Aska::MappingQueue::Add(void*, Aska::AFF::AskaFile*, unsigned int*, Aska::INotify*, int)(*(undefined8 *)puVar10,*puVar19,*puVar19,puVar19 + 5,0,0xffffffff);
    }
    uVar15 = 5;
    break;
  case 0x11:
    piVar9 = (int *)(**(code **)(*param_1 + 0x78))(param_1);
    if (*piVar9 != 0x46534900) {
      puVar10 = &UNK_029651b8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Resource.cpp"*/;
      puVar14 = &UNK_029653d2/*"Csf: Illegal FileStream image. (Unknown magic code)"*/;
      uVar11 = 0x1d7;
      goto code_r0x011d64a0;
    }
    if (0x20130304 < (uint)piVar9[1]) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029651b8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Resource.cpp"*/,0x1d8,&UNK_02965406/*"Csf: Illegal FileStream image version. (%08x/%08x)"*/,piVar9[1],0x20130304);
    }
    plVar1 = param_1 + 0x20;
    std::__ndk1::vector<Framework::CResourceElement::tMappingImage, Framework::CSTLAllocator<Framework::CResourceElement::tMappingImage, Framework::CSTLVectorAllocatorInf> >::reserve(unsigned long)(plVar1,piVar9[2]);
    if (piVar9[2] != 0) {
      uVar21 = 0;
      plVar2 = param_1 + 0x21;
      do {
        uStack_68 = 0;
        uStack_70 = 0;
        uStack_88 = 0;
        uStack_90 = 0;
        uStack_78 = 0;
        uStack_80 = 0;
        puVar19 = (undefined8 *)param_1[0x21];
        if (puVar19 < (undefined8 *)param_1[0x22]) {
          if (puVar19 == (undefined8 *)0x0) {
            uVar11 = 0xcc;
            puVar10 = &UNK_0296188c/*"C:\BAS_Submission\Client\Library\Framework\Source\Framework/STL_Allocator.h"*/;
            puVar14 = &UNK_027dc43e/*"apAssignedMemory is null."*/;
            goto code_r0x011d64a0;
          }
          puVar19[1] = 0;
          *puVar19 = 0;
          puVar19[2] = 0;
          puVar19[3] = 0;
          puVar19[4] = 0;
          puVar19[4] = 0;
          puVar19[3] = 0;
          puVar19[2] = 0;
          uStack_68 = 0;
          uStack_70 = 0;
          uStack_78 = 0;
          uStack_80 = 0;
          uStack_88 = 0;
          uStack_90 = 0;
          *(undefined4 *)(puVar19 + 5) = 0;
          *plVar2 = *plVar2 + 0x30;
        }
        else {
          void std::__ndk1::vector<Framework::CResourceElement::tMappingImage, Framework::CSTLAllocator<Framework::CResourceElement::tMappingImage, Framework::CSTLVectorAllocatorInf> >::__push_back_slow_path<Framework::CResourceElement::tMappingImage>(Framework::CResourceElement::tMappingImage&&)(plVar1,&uStack_90);
          if ((uStack_80 & 1) != 0) {
            Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_70);
          }
        }
        lVar24 = *plVar2;
        if ((uint)piVar9[2] <= uVar21) {
          uVar11 = 0xf1;
          puVar10 = &UNK_02960f2f/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Tools\MakeFileStream/FileStream_Image.h"*/;
          puVar14 = &UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/;
          goto code_r0x011d64a0;
        }
        uVar3 = piVar9[(ulong)uVar21 * 4 + 5];
        uVar4 = piVar9[(ulong)uVar21 * 4 + 6];
        lVar18 = (ulong)(uint)piVar9[(ulong)uVar21 * 4 + 4] + (long)piVar9;
        uVar7 = strlen(lVar18);
        puVar23 = (ulong *)(lVar24 + -0x20);
        uVar16 = (ulong)*(byte *)puVar23;
        if ((*(byte *)puVar23 & 1) == 0) {
          uVar13 = 0x16;
          lVar22 = uVar7 - 0x16;
          if (0x15 < uVar7 && lVar22 != 0) goto code_r0x01f91d50;
code_r0x01f91d04:
          if ((uVar16 & 1) == 0) {
            lVar22 = lVar24 + -0x1f;
          }
          else {
            lVar22 = *(long *)(lVar24 + -0x10);
          }
          if (uVar7 != 0) {
            memmove(lVar22,lVar18,uVar7);
          }
          *(undefined1 *)(lVar22 + uVar7) = 0;
          if ((*(byte *)puVar23 & 1) == 0) {
            *(byte *)puVar23 = (byte)(uVar7 << 1);
          }
          else {
            *(ulong *)(lVar24 + -0x18) = uVar7;
          }
        }
        else {
          uVar16 = *puVar23;
          uVar13 = (uVar16 & 0xfffffffffffffffe) - 1;
          lVar22 = uVar7 - uVar13;
          if (uVar7 < uVar13 || lVar22 == 0) goto code_r0x01f91d04;
code_r0x01f91d50:
          if ((uVar16 & 1) == 0) {
            uVar16 = (ulong)(((uint)uVar16 & 0xfe) >> 1);
          }
          else {
            uVar16 = *(ulong *)(lVar24 + -0x18);
          }
          string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(puVar23,uVar13,lVar22,uVar16,0,uVar16,uVar7,lVar18);
        }
        *(ulong *)(lVar24 + -0x28) = (ulong)uVar4;
        if ((*piVar9 != 0x46534900) || (0x20130304 < (uint)piVar9[1])) {
          uVar11 = 0xea;
          puVar10 = &UNK_02960f2f/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Tools\MakeFileStream/FileStream_Image.h"*/;
          puVar14 = &UNK_02866eaf/*"Illegal instance."*/;
          goto code_r0x011d64a0;
        }
        if ((uint)piVar9[2] <= uVar21) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02960f2f/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Tools\MakeFileStream/FileStream_Image.h"*/,0xeb,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,uVar21);
        }
        if (uVar21 == 1) {
          lVar18 = *(long *)(lVar24 + -0x28);
          uVar11 = 0x1000;
          if (*(char *)((long)param_1 + 0x14a) == '\0') {
code_r0x01f91e70:
            uVar11 = Framework::gMAlloc(unsigned long, unsigned long)(lVar18,uVar11);
          }
          else {
            uVar11 = Framework::gMAllocHigh(unsigned long, unsigned long)();
          }
code_r0x01f91e74:
          *(undefined8 *)(lVar24 + -0x30) = uVar11;
        }
        else {
          lVar18 = *(long *)(lVar24 + -0x28);
          if (uVar21 != 2) {
            if (*(char *)((long)param_1 + 0x14a) == '\0') {
              uVar11 = 0x10;
              goto code_r0x01f91e70;
            }
            uVar11 = Framework::gMAllocHigh(unsigned long, unsigned long)(lVar18,0x10);
            goto code_r0x01f91e74;
          }
          if (*(char *)((long)param_1 + 0x14a) == '\0') {
            lVar18 = Framework::gMAlloc(unsigned long, unsigned long)(lVar18 + 1,0x10);
          }
          else {
            lVar18 = Framework::gMAllocHigh(unsigned long, unsigned long)();
          }
          *(long *)(lVar24 + -0x30) = lVar18;
          *(undefined1 *)(lVar18 + *(long *)(lVar24 + -0x28)) = 0;
          uVar11 = *(undefined8 *)(lVar24 + -0x30);
        }
        memcpy(uVar11,(ulong)uVar3 + (long)piVar9,*(undefined8 *)(lVar24 + -0x28));
        uVar21 = uVar21 + 1;
      } while (uVar21 < (uint)piVar9[2]);
    }
    Framework::CFileLoader::DirectReleaseBuffer(bool)(param_1,0);
    *(undefined4 *)(param_1 + 0x1f) = 0;
    lVar24 = param_1[0x20];
    if ((ulong)((param_1[0x21] - lVar24 >> 4) * -0x5555555555555555) < 2) {
      puVar10 = &UNK_029651b8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Resource.cpp"*/;
      puVar14 = &UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/;
      uVar11 = 0x20b;
      goto code_r0x011d64a0;
    }
    uVar11 = *(undefined8 *)PTR__ZN4Aska6Global15m_pMappingQueueE_02cbda98;
    if ((ulong)((param_1[0x21] - lVar24 >> 4) * -0x5555555555555555) < 2) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02962054/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/STL_Vector.h"*/,0x58,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,1);
      lVar24 = *plVar1;
    }
    lVar24 = Aska::MappingQueue::Add(void*, Aska::AFF::AskaFile*, unsigned int*, Aska::INotify*, int)(uVar11,*(undefined8 *)(lVar24 + 0x30),*(undefined8 *)(lVar24 + 0x30),
                             param_1 + 0x1f,0,0xffffffff);
    if (lVar24 == 0) {
      uVar11 = 0x213;
      goto code_r0x01f923d8;
    }
code_r0x01f923dc:
    uVar15 = 6;
    break;
  case 0x12:
    piVar9 = (int *)(**(code **)(*param_1 + 0x78))(param_1);
    if (*piVar9 != 0x46534900) {
      puVar10 = &UNK_029651b8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Resource.cpp"*/;
      puVar14 = &UNK_02965439/*"Fpk: Illegal FileStream image. (Unknown magic code)"*/;
      uVar11 = 0x21b;
      goto code_r0x011d64a0;
    }
    if (0x20130304 < (uint)piVar9[1]) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029651b8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Resource.cpp"*/,0x21c,&UNK_0296546d/*"Fpk: Illegal FileStream image version. (%08x/%08x)"*/,piVar9[1],0x20130304);
    }
    if (3 < (uint)piVar9[2]) {
      puVar10 = &UNK_029651b8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Resource.cpp"*/;
      puVar14 = &UNK_029654a0/*"Fpk: Illegal csf file. "*/;
      uVar11 = 0x21f;
      goto code_r0x011d64a0;
    }
    std::__ndk1::vector<Framework::CResourceElement::tMappingImage, Framework::CSTLAllocator<Framework::CResourceElement::tMappingImage, Framework::CSTLVectorAllocatorInf> >::reserve(unsigned long)(param_1 + 0x20,piVar9[2]);
    if (piVar9[2] != 0) {
      uVar21 = 0;
      do {
        uStack_68 = 0;
        uStack_70 = 0;
        uStack_88 = 0;
        uStack_90 = 0;
        uStack_78 = 0;
        uStack_80 = 0;
        puVar19 = (undefined8 *)param_1[0x21];
        if (puVar19 < (undefined8 *)param_1[0x22]) {
          if (puVar19 == (undefined8 *)0x0) {
            uVar11 = 0xcc;
            puVar10 = &UNK_0296188c/*"C:\BAS_Submission\Client\Library\Framework\Source\Framework/STL_Allocator.h"*/;
            puVar14 = &UNK_027dc43e/*"apAssignedMemory is null."*/;
            goto code_r0x011d64a0;
          }
          puVar19[1] = 0;
          *puVar19 = 0;
          puVar19[2] = 0;
          puVar19[3] = 0;
          puVar19[4] = 0;
          puVar19[4] = 0;
          puVar19[3] = 0;
          puVar19[2] = 0;
          uStack_68 = 0;
          uStack_70 = 0;
          uStack_78 = 0;
          uStack_80 = 0;
          uStack_88 = 0;
          uStack_90 = 0;
          *(undefined4 *)(puVar19 + 5) = 0;
          param_1[0x21] = param_1[0x21] + 0x30;
        }
        else {
          void std::__ndk1::vector<Framework::CResourceElement::tMappingImage, Framework::CSTLAllocator<Framework::CResourceElement::tMappingImage, Framework::CSTLVectorAllocatorInf> >::__push_back_slow_path<Framework::CResourceElement::tMappingImage>(Framework::CResourceElement::tMappingImage&&)(param_1 + 0x20,&uStack_90);
          if ((uStack_80 & 1) != 0) {
            Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_70);
          }
        }
        lVar24 = param_1[0x21];
        if ((uint)piVar9[2] <= uVar21) {
          uVar11 = 0xf1;
          puVar10 = &UNK_02960f2f/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Tools\MakeFileStream/FileStream_Image.h"*/;
          puVar14 = &UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/;
          goto code_r0x011d64a0;
        }
        uVar3 = piVar9[(ulong)uVar21 * 4 + 5];
        uVar4 = piVar9[(ulong)uVar21 * 4 + 6];
        lVar18 = (ulong)(uint)piVar9[(ulong)uVar21 * 4 + 4] + (long)piVar9;
        uVar7 = strlen(lVar18);
        puVar23 = (ulong *)(lVar24 + -0x20);
        uVar16 = (ulong)*(byte *)puVar23;
        if ((*(byte *)puVar23 & 1) == 0) {
          uVar13 = 0x16;
          lVar22 = uVar7 - 0x16;
          if (0x15 < uVar7 && lVar22 != 0) goto code_r0x01f9213c;
code_r0x01f920f0:
          if ((uVar16 & 1) == 0) {
            lVar22 = lVar24 + -0x1f;
          }
          else {
            lVar22 = *(long *)(lVar24 + -0x10);
          }
          if (uVar7 != 0) {
            memmove(lVar22,lVar18,uVar7);
          }
          *(undefined1 *)(lVar22 + uVar7) = 0;
          if ((*(byte *)puVar23 & 1) == 0) {
            *(byte *)puVar23 = (byte)(uVar7 << 1);
          }
          else {
            *(ulong *)(lVar24 + -0x18) = uVar7;
          }
        }
        else {
          uVar16 = *puVar23;
          uVar13 = (uVar16 & 0xfffffffffffffffe) - 1;
          lVar22 = uVar7 - uVar13;
          if (uVar7 < uVar13 || lVar22 == 0) goto code_r0x01f920f0;
code_r0x01f9213c:
          if ((uVar16 & 1) == 0) {
            uVar16 = (ulong)(((uint)uVar16 & 0xfe) >> 1);
          }
          else {
            uVar16 = *(ulong *)(lVar24 + -0x18);
          }
          string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(puVar23,uVar13,lVar22,uVar16,0,uVar16,uVar7,lVar18);
        }
        *(ulong *)(lVar24 + -0x28) = (ulong)uVar4;
        if ((*piVar9 != 0x46534900) || (0x20130304 < (uint)piVar9[1])) {
          uVar11 = 0xea;
          puVar10 = &UNK_02960f2f/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Tools\MakeFileStream/FileStream_Image.h"*/;
          puVar14 = &UNK_02866eaf/*"Illegal instance."*/;
          goto code_r0x011d64a0;
        }
        if ((uint)piVar9[2] <= uVar21) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02960f2f/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Tools\MakeFileStream/FileStream_Image.h"*/,0xeb,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,uVar21);
        }
        if (*(char *)((long)param_1 + 0x14a) == '\0') {
          uVar11 = Framework::gMAlloc(unsigned long, unsigned long)(*(undefined8 *)(lVar24 + -0x28),0x1000);
        }
        else {
          uVar11 = Framework::gMAllocHigh(unsigned long, unsigned long)(*(undefined8 *)(lVar24 + -0x28),0x1000);
        }
        *(undefined8 *)(lVar24 + -0x30) = uVar11;
        memcpy(uVar11,(ulong)uVar3 + (long)piVar9,*(undefined8 *)(lVar24 + -0x28));
        uVar21 = uVar21 + 1;
      } while (uVar21 < (uint)piVar9[2]);
    }
    Framework::CFileLoader::DirectReleaseBuffer(bool)(param_1,0);
    puVar10 = PTR__ZN4Aska6Global15m_pMappingQueueE_02cbda98;
    puVar19 = (undefined8 *)param_1[0x20];
    puVar20 = (undefined8 *)param_1[0x21];
    if (puVar19 != puVar20) {
      iVar17 = 0;
      do {
        if ((iVar17 != 0) &&
           (lVar24 = Aska::MappingQueue::Add(void*, Aska::AFF::AskaFile*, unsigned int*, Aska::INotify*, int)(*(undefined8 *)puVar10,*puVar19,*puVar19,puVar19 + 5,0,
                                     0xffffffff), lVar24 == 0)) {
          uVar11 = 0x24e;
          puVar10 = &UNK_029651b8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Resource.cpp"*/;
          puVar14 = &UNK_029614eb/*"result is null."*/;
          goto code_r0x011d64a0;
        }
        puVar19 = puVar19 + 6;
        iVar17 = iVar17 + -1;
      } while (puVar20 != puVar19);
    }
    uVar15 = 7;
  }
code_r0x01f923e0:
  *(undefined4 *)((long)param_1 + 0xec) = uVar15;
code_r0x01f923e4:
  return;
}

// ==== Framework::CResourceElement::PhaseLoadingFinish()
// vaddr 0x1e92404 | ghidra 0x1f92404 | size 380 | symbol _ZN9Framework16CResourceElement18PhaseLoadingFinishEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework16CResourceElement18PhaseLoadingFinishEv(long *param_1)

{
  undefined *puVar1;
  uint uVar2;
  undefined4 uVar3;
  ulong uVar4;
  long lVar5;
  undefined4 *puVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  
  if ((param_1[0x1e] == 0) && (uVar4 = Framework::CFileLoader::IsLoading() const(param_1), (uVar4 & 1) != 0)) {
    return;
  }
  (**(code **)(*param_1 + 0x78))(param_1);
  uVar4 = Aska::DecompressBase::IsCompressed(void const*)();
  puVar1 = PTR__ZN4Aska6Global18m_pDecompressQueueE_02cc0f20;
  if ((uVar4 & 1) == 0) {
    uVar3 = 4;
  }
  else {
    uVar2 = Aska::DecompressQueue::GetSize() const(*(undefined8 *)PTR__ZN4Aska6Global18m_pDecompressQueueE_02cc0f20);
    if (0xf < uVar2) {
      return;
    }
    lVar5 = (**(code **)(*param_1 + 0x78))(param_1);
    param_1[0x27] = (long)*(int *)(lVar5 + 0xc);
    if (param_1[0x28] != 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029651b8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Resource.cpp"*/,0x339,&UNK_02965280/*"m_pDecompressInfo isn't null.(%08x)"*/);
    }
    puVar6 = (undefined4 *)operator new(unsigned long, std::nothrow_t const&)(0x28,PTR__ZSt7nothrow_02cb9a80);
    if (puVar6 == (undefined4 *)0x0) {
      param_1[0x28] = 0;
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029651b8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Resource.cpp"*/,0x33b,&UNK_029654dc/*"m_pDecompressInfo is null."*/);
    }
    else {
      *puVar6 = 4;
      *(undefined8 *)(puVar6 + 2) = 0;
      *(undefined8 *)(puVar6 + 4) = 0;
      *(undefined8 *)(puVar6 + 6) = 0x10;
      param_1[0x28] = (long)puVar6;
    }
    uVar3 = (**(code **)(*param_1 + 0x30))(param_1);
    *(undefined4 *)(param_1[0x28] + 0x18) = uVar3;
    if (*(char *)((long)param_1 + 0x149) != '\0') {
      *(uint *)(param_1[0x28] + 0x1c) = *(uint *)(param_1[0x28] + 0x1c) | 2;
    }
    uVar8 = *(undefined8 *)puVar1;
    uVar7 = (**(code **)(*param_1 + 0x78))(param_1);
    uVar4 = Aska::DecompressQueue::Add(void const*, Aska::DecompressInfo*, int, Aska::INotify*, Aska::IMemoryManager*, Aska::IMemoryManager*, Aska::IMemoryManager*, Aska::IMemoryManager*)(uVar8,uVar7,param_1[0x28],0,param_1 + 0x24,0,0,0,0);
    if ((uVar4 & 1) == 0) {
      if (param_1[0x28] == 0) {
        return;
      }
      operator delete(void*)();
      param_1[0x28] = 0;
      return;
    }
    uVar3 = 3;
  }
  *(undefined4 *)((long)param_1 + 0xec) = uVar3;
  return;
}

// ==== Framework::CResourceElement::Type() const
// vaddr 0x1e92580 | ghidra 0x1f92580 | size 8 | symbol _ZNK9Framework16CResourceElement4TypeEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK9Framework16CResourceElement4TypeEv(long param_1)

{
  return *(undefined4 *)(param_1 + 0xe8);
}

// ==== Framework::CResourceElement::Done()
// vaddr 0x1e92588 | ghidra 0x1f92588 | size 20 | symbol _ZN9Framework16CResourceElement4DoneEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework16CResourceElement4DoneEv(long param_1)

{
  *(undefined4 *)(param_1 + 0xec) = 9;
  (*(code *)PTR__ZN4Aska4Task6RemoveEv_02cb3550)(param_1 + 0xc0);
  return;
}

// ==== std::__ndk1::vector<Framework::CResourceElement::tMappingImage, Framework::CSTLAllocator<Framework::CResourceElement::tMappingImage, Framework::CSTLVectorAllocatorInf> >::reserve(unsigned long)
// vaddr 0x1e9259c | ghidra 0x1f9259c | size 256 | symbol _ZNSt6__ndk16vectorIN9Framework16CResourceElement13tMappingImageENS1_13CSTLAllocatorIS3_NS1_22CSTLVectorAllocatorInfEEEE7reserveEm | lib libSOA-3.7.0.so | 2026-10-04
void _ZNSt6__ndk16vectorIN9Framework16CResourceElement13tMappingImageENS1_13CSTLAllocatorIS3_NS1_22CSTLVectorAllocatorInfEEEE7reserveEm
               (long *param_1,ulong param_2)

{
  long lVar1;
  long lVar2;
  long lStack_58;
  long lStack_50;
  long lStack_48;
  long lStack_40;
  long *plStack_38;
  
  lVar1 = *param_1;
  if ((ulong)((param_1[2] - lVar1 >> 4) * -0x5555555555555555) < param_2) {
    lVar2 = param_1[1];
    plStack_38 = param_1 + 2;
    lStack_40 = 0;
    lStack_58 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(param_2 * 0x30,&UNK_02962054/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/STL_Vector.h"*/,0x20);
    if (lStack_58 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296188c/*"C:\BAS_Submission\Client\Library\Framework\Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
    lStack_50 = lStack_58 + (lVar2 - lVar1 >> 4) * 0x10;
    lStack_40 = lStack_58 + param_2 * 0x30;
    lStack_48 = lStack_50;
    std::__ndk1::vector<Framework::CResourceElement::tMappingImage, Framework::CSTLAllocator<Framework::CResourceElement::tMappingImage, Framework::CSTLVectorAllocatorInf> >::__swap_out_circular_buffer(std::__ndk1::__split_buffer<Framework::CResourceElement::tMappingImage, Framework::CSTLAllocator<Framework::CResourceElement::tMappingImage, Framework::CSTLVectorAllocatorInf>&>&)(param_1,&lStack_58);
    lVar1 = lStack_50;
    while (lVar2 = lStack_48, lVar2 != lVar1) {
      lStack_48 = lVar2 + -0x30;
      if ((*(byte *)(lVar2 + -0x20) & 1) != 0) {
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(*(undefined8 *)(lVar2 + -0x10));
      }
    }
    if (lStack_58 != 0) {
      lStack_48 = lVar2;
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)();
    }
  }
  return;
}

// ==== non-virtual thunk to Framework::CResourceElement::Run(int)
// vaddr 0x1e9269c | ghidra 0x1f9269c | size 8 | symbol _ZThn192_N9Framework16CResourceElement3RunEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZThn192_N9Framework16CResourceElement3RunEi(long param_1)

{
  (*(code *)PTR__ZN9Framework16CResourceElement3RunEi_02c92a50)(param_1 + -0xc0);
  return;
}

// ==== Framework::CResourceElement::IsRquestMappingMemoryType(unsigned int)
// vaddr 0x1e926a4 | ghidra 0x1f926a4 | size 40 | symbol _ZN9Framework16CResourceElement25IsRquestMappingMemoryTypeEj | lib libSOA-3.7.0.so | 2026-10-04
uint _ZN9Framework16CResourceElement25IsRquestMappingMemoryTypeEj(int param_1)

{
  if (param_1 - 0xdU < 6) {
    return 0x31U >> (ulong)(param_1 - 0xdU & 0x1f) & 1;
  }
  return 0;
}

// ==== Framework::CResourceElement::SwapDecompressBuffer()
// vaddr 0x1e926cc | ghidra 0x1f926cc | size 132 | symbol _ZN9Framework16CResourceElement20SwapDecompressBufferEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework16CResourceElement20SwapDecompressBufferEv(long param_1)

{
  char cVar1;
  long lVar2;
  
  lVar2 = *(long *)(param_1 + 0x140);
  if (lVar2 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029651b8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Resource.cpp"*/,0x2d3,&UNK_029654dc/*"m_pDecompressInfo is null."*/);
    lVar2 = *(long *)(param_1 + 0x140);
    cVar1 = *(char *)(lVar2 + 0x20);
  }
  else {
    cVar1 = *(char *)(lVar2 + 0x20);
  }
  if (cVar1 == '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029651b8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Resource.cpp"*/,0x2d4,&UNK_029654f7);
    lVar2 = *(long *)(param_1 + 0x140);
  }
  Framework::CFileLoader::SwapBufferPointer(void*, unsigned long)(param_1,*(undefined8 *)(lVar2 + 0x10),*(undefined8 *)(param_1 + 0x138));
  if (*(long *)(param_1 + 0x140) != 0) {
    operator delete(void*)();
    *(undefined8 *)(param_1 + 0x140) = 0;
  }
  return;
}

// ==== Framework::CResourceElement::Phase() const
// vaddr 0x1e92750 | ghidra 0x1f92750 | size 8 | symbol _ZNK9Framework16CResourceElement5PhaseEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK9Framework16CResourceElement5PhaseEv(long param_1)

{
  return *(undefined4 *)(param_1 + 0xec);
}

// ==== Framework::CResourceElement::IsInitialized() const
// vaddr 0x1e92758 | ghidra 0x1f92758 | size 16 | symbol _ZNK9Framework16CResourceElement13IsInitializedEv | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK9Framework16CResourceElement13IsInitializedEv(long param_1)

{
  return *(int *)(param_1 + 0xec) != 0;
}

// ==== Framework::CResourceElement::IsDone() const
// vaddr 0x1e92768 | ghidra 0x1f92768 | size 16 | symbol _ZNK9Framework16CResourceElement6IsDoneEv | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK9Framework16CResourceElement6IsDoneEv(long param_1)

{
  return *(int *)(param_1 + 0xec) == 9;
}

// ==== Framework::CResourceElement::pImage() const
// vaddr 0x1e92778 | ghidra 0x1f92778 | size 80 | symbol _ZNK9Framework16CResourceElement6pImageEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK9Framework16CResourceElement6pImageEv(long *param_1)

{
  undefined8 uVar1;
  
  if (*(int *)((long)param_1 + 0xec) != 9) {
    uVar1 = Framework::CFileLoader::pFileName() const(param_1);
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029651b8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Resource.cpp"*/,0x2f0,&UNK_02965511/*"[%s] Not ready yet.(Phase=%d)"*/,uVar1,*(undefined4 *)((long)param_1 + 0xec));
  }
                    /* WARNING: Could not recover jumptable at 0x01f927c4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*param_1 + 0x78))(param_1);
  return;
}

// ==== Framework::CResourceElement::pFindMappingImage(char const*) const
// vaddr 0x1e927c8 | ghidra 0x1f927c8 | size 236 | symbol _ZNK9Framework16CResourceElement17pFindMappingImageEPKc | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK9Framework16CResourceElement17pFindMappingImageEPKc(long param_1,undefined8 param_2)

{
  ulong uVar1;
  long lVar2;
  long lVar3;
  byte bVar4;
  int iVar5;
  undefined8 uVar6;
  ulong uVar7;
  long lVar8;
  
  if (*(int *)(param_1 + 0xec) != 9) {
    uVar6 = Framework::CFileLoader::pFileName() const(param_1);
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029651b8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Resource.cpp"*/,0x2f9,&UNK_02965511/*"[%s] Not ready yet.(Phase=%d)"*/,uVar6,*(undefined4 *)(param_1 + 0xec));
  }
  lVar8 = *(long *)(param_1 + 0x100);
  lVar3 = *(long *)(param_1 + 0x108);
  if (lVar8 != lVar3) {
    uVar7 = strlen(param_2);
    if (uVar7 == 0) {
      do {
        uVar7 = (ulong)(*(byte *)(lVar8 + 0x10) >> 1);
        if ((*(byte *)(lVar8 + 0x10) & 1) != 0) {
          uVar7 = *(ulong *)(lVar8 + 0x18);
        }
        if (uVar7 == 0) {
          return lVar8;
        }
        lVar8 = lVar8 + 0x30;
      } while (lVar3 != lVar8);
    }
    else {
      do {
        bVar4 = *(byte *)(lVar8 + 0x10);
        uVar1 = (ulong)(bVar4 >> 1);
        if ((bVar4 & 1) != 0) {
          uVar1 = *(ulong *)(lVar8 + 0x18);
        }
        if (uVar7 == uVar1) {
          lVar2 = lVar8 + 0x11;
          if ((bVar4 & 1) != 0) {
            lVar2 = *(long *)(lVar8 + 0x20);
          }
          iVar5 = memcmp(lVar2,param_2,uVar7);
          if (iVar5 == 0) {
            return lVar8;
          }
        }
        lVar8 = lVar8 + 0x30;
      } while (lVar3 != lVar8);
    }
  }
  return 0;
}

// ==== Framework::CResourceElement::IsArchiveType(unsigned int)
// vaddr 0x1e928b4 | ghidra 0x1f928b4 | size 68 | symbol _ZN9Framework16CResourceElement13IsArchiveTypeEj | lib libSOA-3.7.0.so | 2026-10-04
undefined1 _ZN9Framework16CResourceElement13IsArchiveTypeEj(uint param_1)

{
  if (0x12 < param_1) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02962e40/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/STL_Array.h"*/,0x25,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,(ulong)param_1,0x13);
  }
  return PTR__ZN9Framework16CResourceElement14m_ArchiveTypesE_02cc2408[param_1];
}

// ==== Framework::CResourceElement::IsArchiveType(unsigned int, bool)
// vaddr 0x1e928f8 | ghidra 0x1f928f8 | size 80 | symbol _ZN9Framework16CResourceElement13IsArchiveTypeEjb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework16CResourceElement13IsArchiveTypeEjb(uint param_1,byte param_2)

{
  if (0x12 < param_1) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02962e40/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/STL_Array.h"*/,0x25,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,(ulong)param_1,0x13);
  }
  PTR__ZN9Framework16CResourceElement14m_ArchiveTypesE_02cc2408[param_1] = param_2 & 1;
  return;
}

// ==== Framework::CResourceElement::Handler(unsigned long)
// vaddr 0x1e92948 | ghidra 0x1f92948 | size 48 | symbol _ZN9Framework16CResourceElement7HandlerEm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework16CResourceElement7HandlerEm(long param_1)

{
  Framework::CFileLoader::Handler(unsigned long)();
  Framework::CResourceElement::PhaseLoadingFinish()(param_1);
  if (*(int *)(param_1 + 0xec) == 1) {
    *(undefined4 *)(param_1 + 0xec) = 2;
  }
  return;
}

// ==== Framework::CResourceElement::IsExpansionFinished() const
// vaddr 0x1e92978 | ghidra 0x1f92978 | size 8 | symbol _ZNK9Framework16CResourceElement19IsExpansionFinishedEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK9Framework16CResourceElement19IsExpansionFinishedEv(void)

{
  return 1;
}

// ==== Framework::CResourceElement::CFinishNotify::Handler(unsigned long)
// vaddr 0x1e92980 | ghidra 0x1f92980 | size 236 | symbol _ZN9Framework16CResourceElement13CFinishNotify7HandlerEm | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Possible PIC construction at 0x01f929dc: Changing call to branch */

void _ZN9Framework16CResourceElement13CFinishNotify7HandlerEm
               (long param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  undefined8 uVar1;
  undefined *puVar2;
  long lVar3;
  long lVar4;
  
  switch(param_2) {
  case 0:
    lVar4 = *(long *)(param_1 + 0x10);
    lVar3 = *(long *)(lVar4 + 0x140);
    if ((lVar3 != 0) && (*(char *)(lVar3 + 0x20) != '\0')) {
      if (*(char *)(lVar3 + 0x20) == '\0') {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029651b8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Resource.cpp"*/,0x2d4,&UNK_029654f7);
        lVar3 = *(long *)(lVar4 + 0x140);
      }
      Framework::CFileLoader::SwapBufferPointer(void*, unsigned long)(lVar4,*(undefined8 *)(lVar3 + 0x10),*(undefined8 *)(lVar4 + 0x138));
      if (*(long *)(lVar4 + 0x140) != 0) {
        operator delete(void*)();
        *(undefined8 *)(lVar4 + 0x140) = 0;
      }
    }
    *(undefined1 *)(param_1 + 8) = 1;
    return;
  case 1:
    puVar2 = &UNK_0296552f;
    uVar1 = 0x365;
    break;
  case 2:
    puVar2 = &UNK_0296555c;
    uVar1 = 0x368;
    break;
  case 3:
  case 4:
    return;
  default:
    puVar2 = &UNK_0296557b;
    uVar1 = 0x372;
    param_4 = param_2;
  }
  (*(code *)PTR__ZN9Framework9gDoAssertEPKciS1_z_02ca3240)(&UNK_029651b8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Resource.cpp"*/,uVar1,puVar2,param_4);
  return;
}

// ==== Framework::CResourceElement::~CResourceElement()
// vaddr 0x1e936a4 | ghidra 0x1f936a4 | size 148 | symbol _ZN9Framework16CResourceElementD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework16CResourceElementD0Ev(long *param_1)

{
  undefined *puVar1;
  long lVar2;
  long lVar3;
  long lVar4;
  
  puVar1 = PTR__ZTVN9Framework16CResourceElementE_02cb8700 + 0xb0;
  *param_1 = (long)(PTR__ZTVN9Framework16CResourceElementE_02cb8700 + 0x10);
  param_1[0x18] = (long)puVar1;
  Framework::CResourceElement::Release()();
  lVar4 = param_1[0x20];
  if (lVar4 != 0) {
    lVar3 = param_1[0x21];
    if (lVar3 != lVar4) {
      do {
        param_1[0x21] = lVar3 + -0x30;
        lVar2 = lVar3 + -0x30;
        if ((*(byte *)(lVar3 + -0x20) & 1) != 0) {
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(*(undefined8 *)(lVar3 + -0x10));
          lVar2 = param_1[0x21];
        }
        lVar3 = lVar2;
      } while (lVar3 != lVar4);
      lVar4 = param_1[0x20];
    }
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(lVar4);
  }
  Aska::Task::~Task()(param_1 + 0x18);
  Framework::CFileLoader::~CFileLoader()(param_1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Framework::CResourceElement::pBuffer() const
// vaddr 0x1e93738 | ghidra 0x1f93738 | size 40 | symbol _ZNK9Framework16CResourceElement7pBufferEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK9Framework16CResourceElement7pBufferEv(void)

{
  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029655e1/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/Resource.h"*/,0xa0,&UNK_02965633/*"Forbidden call."*/);
  return 0;
}

// ==== Framework::CResourceElement::Align() const
// vaddr 0x1e93760 | ghidra 0x1f93760 | size 8 | symbol _ZNK9Framework16CResourceElement5AlignEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK9Framework16CResourceElement5AlignEv(void)

{
  return 0x20;
}

// ==== Framework::CResourceElement::Initialize(unsigned int, Framework::CResourceElement::tMemoryDescription const&)
// vaddr 0x1e93768 | ghidra 0x1f93768 | size 84 | symbol _ZN9Framework16CResourceElement10InitializeEjRKNS0_18tMemoryDescriptionE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework16CResourceElement10InitializeEjRKNS0_18tMemoryDescriptionE
               (long *param_1,undefined4 param_2,undefined8 param_3)

{
  code *UNRECOVERED_JUMPTABLE;
  undefined8 uVar1;
  
  UNRECOVERED_JUMPTABLE = *(code **)(*param_1 + 0x60);
  uVar1 = (**(code **)(*param_1 + 0x30))(param_1);
                    /* WARNING: Could not recover jumptable at 0x01f937b8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*UNRECOVERED_JUMPTABLE)(param_1,param_2,uVar1,param_3);
  return;
}

// ==== Framework::CResourceElement::InitializeByDirectFile(char const*, Framework::CResourceElement::tMemoryDescription const&, char const*)
// vaddr 0x1e937bc | ghidra 0x1f937bc | size 92 | symbol _ZN9Framework16CResourceElement22InitializeByDirectFileEPKcRKNS0_18tMemoryDescriptionES2_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework16CResourceElement22InitializeByDirectFileEPKcRKNS0_18tMemoryDescriptionES2_
               (long *param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  code *UNRECOVERED_JUMPTABLE;
  undefined8 uVar1;
  
  UNRECOVERED_JUMPTABLE = *(code **)(*param_1 + 0x68);
  uVar1 = (**(code **)(*param_1 + 0x30))(param_1);
                    /* WARNING: Could not recover jumptable at 0x01f93814. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*UNRECOVERED_JUMPTABLE)(param_1,param_2,uVar1,param_3,param_4);
  return;
}

// ==== Framework::CResourceElement::pResourceElement_Bsb()
// vaddr 0x1e93818 | ghidra 0x1f93818 | size 8 | symbol _ZN9Framework16CResourceElement20pResourceElement_BsbEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN9Framework16CResourceElement20pResourceElement_BsbEv(void)

{
  return 0;
}

// ==== Framework::CResourceElement::pBufferDirect() const
// vaddr 0x1e93820 | ghidra 0x1f93820 | size 4 | symbol _ZNK9Framework16CResourceElement13pBufferDirectEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK9Framework16CResourceElement13pBufferDirectEv(void)

{
  (*(code *)PTR__ZNK9Framework11CFileLoader7pBufferEv_02cb1a28)();
  return;
}

// ==== Framework::CResourceElement::StartExpansion()
// vaddr 0x1e93824 | ghidra 0x1f93824 | size 4 | symbol _ZN9Framework16CResourceElement14StartExpansionEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework16CResourceElement14StartExpansionEv(void)

{
  return;
}

// ==== non-virtual thunk to Framework::CResourceElement::~CResourceElement()
// vaddr 0x1e93828 | ghidra 0x1f93828 | size 144 | symbol _ZThn192_N9Framework16CResourceElementD1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZThn192_N9Framework16CResourceElementD1Ev(long *param_1)

{
  undefined *puVar1;
  long lVar2;
  long lVar3;
  long *plVar4;
  long lVar5;
  
  puVar1 = PTR__ZTVN9Framework16CResourceElementE_02cb8700;
  plVar4 = param_1 + -0x18;
  *plVar4 = (long)(PTR__ZTVN9Framework16CResourceElementE_02cb8700 + 0x10);
  *param_1 = (long)(puVar1 + 0xb0);
  Framework::CResourceElement::Release()(plVar4);
  lVar5 = param_1[8];
  if (lVar5 != 0) {
    lVar3 = param_1[9];
    if (lVar3 != lVar5) {
      do {
        param_1[9] = lVar3 + -0x30;
        lVar2 = lVar3 + -0x30;
        if ((*(byte *)(lVar3 + -0x20) & 1) != 0) {
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(*(undefined8 *)(lVar3 + -0x10));
          lVar2 = param_1[9];
        }
        lVar3 = lVar2;
      } while (lVar3 != lVar5);
      lVar5 = param_1[8];
    }
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(lVar5);
  }
  Aska::Task::~Task()(param_1);
  (*(code *)PTR__ZN9Framework11CFileLoaderD2Ev_02cb0d60)(plVar4);
  return;
}

// ==== non-virtual thunk to Framework::CResourceElement::~CResourceElement()
// vaddr 0x1e938b8 | ghidra 0x1f938b8 | size 8 | symbol _ZThn192_N9Framework16CResourceElementD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZThn192_N9Framework16CResourceElementD0Ev(long param_1)

{
  (*(code *)PTR__ZN9Framework16CResourceElementD0Ev_02cb34c8)(param_1 + -0xc0);
  return;
}

// ==== Framework::CResourceElement::CFinishNotify::~CFinishNotify()
// vaddr 0x1e938c0 | ghidra 0x1f938c0 | size 4 | symbol _ZN9Framework16CResourceElement13CFinishNotifyD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework16CResourceElement13CFinishNotifyD0Ev(void)

{
  (*(code *)PTR__ZdlPv_02ca4758)();
  return;
}

// ==== Framework::CResourceElement::~CResourceElement()
// vaddr 0x1e945c0 | ghidra 0x1f945c0 | size 140 | symbol _ZN9Framework16CResourceElementD2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework16CResourceElementD2Ev(long *param_1)

{
  undefined *puVar1;
  long lVar2;
  long lVar3;
  long lVar4;
  
  puVar1 = PTR__ZTVN9Framework16CResourceElementE_02cb8700 + 0xb0;
  *param_1 = (long)(PTR__ZTVN9Framework16CResourceElementE_02cb8700 + 0x10);
  param_1[0x18] = (long)puVar1;
  Framework::CResourceElement::Release()();
  lVar4 = param_1[0x20];
  if (lVar4 != 0) {
    lVar3 = param_1[0x21];
    if (lVar3 != lVar4) {
      do {
        param_1[0x21] = lVar3 + -0x30;
        lVar2 = lVar3 + -0x30;
        if ((*(byte *)(lVar3 + -0x20) & 1) != 0) {
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(*(undefined8 *)(lVar3 + -0x10));
          lVar2 = param_1[0x21];
        }
        lVar3 = lVar2;
      } while (lVar3 != lVar4);
      lVar4 = param_1[0x20];
    }
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(lVar4);
  }
  Aska::Task::~Task()(param_1 + 0x18);
  (*(code *)PTR__ZN9Framework11CFileLoaderD2Ev_02cb0d60)(param_1);
  return;
}

// ==== std::__ndk1::vector<Framework::CResourceElement::tMappingImage, Framework::CSTLAllocator<Framework::CResourceElement::tMappingImage, Framework::CSTLVectorAllocatorInf> >::__swap_out_circular_buffer(std::__ndk1::__split_buffer<Framework::CResourceElement::tMappingImage, Framework::CSTLAllocator<Framework::CResourceElement::tMappingImage, Framework::CSTLVectorAllocatorInf>&>&)
// vaddr 0x1e94afc | ghidra 0x1f94afc | size 384 | symbol _ZNSt6__ndk16vectorIN9Framework16CResourceElement13tMappingImageENS1_13CSTLAllocatorIS3_NS1_22CSTLVectorAllocatorInfEEEE26__swap_out_circular_bufferERNS_14__split_bufferIS3_RS6_EE | lib libSOA-3.7.0.so | 2026-10-04
void _ZNSt6__ndk16vectorIN9Framework16CResourceElement13tMappingImageENS1_13CSTLAllocatorIS3_NS1_22CSTLVectorAllocatorInfEEEE26__swap_out_circular_bufferERNS_14__split_bufferIS3_RS6_EE
               (long *param_1,undefined8 *param_2)

{
  long lVar1;
  ulong *puVar2;
  ulong *puVar3;
  long lVar4;
  ulong uVar5;
  long lVar6;
  ulong uVar7;
  ulong uVar8;
  
  lVar1 = *param_1;
  if (param_1[1] == lVar1) {
    lVar6 = param_2[1];
  }
  else {
    lVar6 = param_2[1];
    puVar2 = (ulong *)(param_1[1] + -0x18);
    do {
      uVar8 = puVar2[-2];
      uVar7 = puVar2[-3];
      puVar3 = (ulong *)(lVar6 + -0x20);
      *puVar3 = 0;
      *(undefined8 *)(lVar6 + -0x18) = 0;
      *(undefined8 *)(lVar6 + -0x10) = 0;
      *(ulong *)(lVar6 + -0x28) = uVar8;
      *(ulong *)(lVar6 + -0x30) = uVar7;
      if ((puVar2[-1] & 1) == 0) {
        *(ulong *)(lVar6 + -0x10) = puVar2[1];
        uVar7 = puVar2[-1];
        *(ulong *)(lVar6 + -0x18) = *puVar2;
        *puVar3 = uVar7;
      }
      else {
        uVar7 = *puVar2;
        uVar8 = puVar2[1];
        if (uVar7 < 0x17) {
          lVar4 = lVar6 + -0x1f;
          *(char *)puVar3 = (char)(uVar7 << 1);
          if (uVar7 != 0) goto code_r0x01f94bec;
        }
        else {
          uVar5 = uVar7 + 0x10 & 0xfffffffffffffff0;
          if (uVar5 == 0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296188c/*"C:\BAS_Submission\Client\Library\Framework\Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
          }
          lVar4 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar5,&UNK_029618d8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/STL_String.h"*/,0x1c);
          if (lVar4 == 0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296188c/*"C:\BAS_Submission\Client\Library\Framework\Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
          }
          *(ulong *)(lVar6 + -0x18) = uVar7;
          *(long *)(lVar6 + -0x10) = lVar4;
          *(ulong *)(lVar6 + -0x20) = uVar5 | 1;
code_r0x01f94bec:
          memcpy(lVar4,uVar8,uVar7);
        }
        *(undefined1 *)(lVar4 + uVar7) = 0;
      }
      puVar3 = puVar2 + 2;
      puVar2 = puVar2 + -6;
      *(int *)(lVar6 + -8) = (int)*puVar3;
      lVar6 = param_2[1] + -0x30;
      param_2[1] = lVar6;
    } while ((long)puVar2 - lVar1 != -0x18);
    lVar1 = *param_1;
  }
  *param_1 = lVar6;
  param_2[1] = lVar1;
  lVar1 = param_1[1];
  param_1[1] = param_2[2];
  param_2[2] = lVar1;
  lVar1 = param_1[2];
  param_1[2] = param_2[3];
  param_2[3] = lVar1;
  *param_2 = param_2[1];
  return;
}

// ==== void std::__ndk1::vector<Framework::CResourceElement::tMappingImage, Framework::CSTLAllocator<Framework::CResourceElement::tMappingImage, Framework::CSTLVectorAllocatorInf> >::__push_back_slow_path<Framework::CResourceElement::tMappingImage>(Framework::CResourceElement::tMappingImage&&)
// vaddr 0x1e94c7c | ghidra 0x1f94c7c | size 592 | symbol _ZNSt6__ndk16vectorIN9Framework16CResourceElement13tMappingImageENS1_13CSTLAllocatorIS3_NS1_22CSTLVectorAllocatorInfEEEE21__push_back_slow_pathIS3_EEvOT_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZNSt6__ndk16vectorIN9Framework16CResourceElement13tMappingImageENS1_13CSTLAllocatorIS3_NS1_22CSTLVectorAllocatorInfEEEE21__push_back_slow_pathIS3_EEvOT_
               (long *param_1,undefined8 *param_2)

{
  undefined8 *puVar1;
  long lVar2;
  long lVar3;
  ulong uVar4;
  long lVar5;
  ulong uVar6;
  undefined8 *puVar7;
  long lVar8;
  ulong *puVar9;
  undefined8 uVar10;
  long lStack_78;
  undefined8 *puStack_70;
  undefined8 *puStack_68;
  long lStack_60;
  long *plStack_58;
  
  plStack_58 = param_1 + 2;
  lVar5 = param_1[1] - *param_1 >> 4;
  lVar3 = *plStack_58 - *param_1 >> 4;
  if ((ulong)(lVar3 * -0x5555555555555555) < 0x2aaaaaaaaaaaaaa) {
    uVar6 = lVar5 * -0x5555555555555555 + 1;
    uVar4 = lVar3 * 0x5555555555555556;
    if (uVar6 <= uVar4) {
      uVar6 = uVar4;
    }
    if (uVar6 != 0) goto code_r0x01f94d04;
    lVar3 = 0;
  }
  else {
    uVar6 = 0x555555555555555;
code_r0x01f94d04:
    lStack_60 = 0;
    lVar3 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar6 * 0x30,&UNK_02962054/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/STL_Vector.h"*/,0x20);
    if (lVar3 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296188c/*"C:\BAS_Submission\Client\Library\Framework\Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
  }
  puVar7 = (undefined8 *)(lVar3 + lVar5 * 0x10);
  lStack_60 = lVar3 + uVar6 * 0x30;
  lStack_78 = lVar3;
  puStack_70 = puVar7;
  puStack_68 = puVar7;
  if (puVar7 == (undefined8 *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296188c/*"C:\BAS_Submission\Client\Library\Framework\Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
  }
  uVar10 = *param_2;
  lVar8 = lVar3 + lVar5 * 0x10;
  puVar7[1] = param_2[1];
  *puVar7 = uVar10;
  puVar9 = (ulong *)(lVar8 + 0x10);
  *puVar9 = 0;
  *(undefined8 *)(lVar8 + 0x18) = 0;
  *(undefined8 *)(lVar8 + 0x20) = 0;
  if ((param_2[2] & 1) == 0) {
    *(undefined8 *)(lVar8 + 0x20) = param_2[4];
    uVar6 = param_2[2];
    *(undefined8 *)(lVar8 + 0x18) = param_2[3];
    *puVar9 = uVar6;
    puStack_68 = puVar7;
    goto code_r0x01f94e4c;
  }
  uVar6 = param_2[3];
  uVar10 = param_2[4];
  if (uVar6 < 0x17) {
    lVar8 = lVar8 + 0x11;
    *(char *)puVar9 = (char)(uVar6 << 1);
    if (uVar6 != 0) goto code_r0x01f94e34;
  }
  else {
    uVar4 = uVar6 + 0x10 & 0xfffffffffffffff0;
    if (uVar4 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296188c/*"C:\BAS_Submission\Client\Library\Framework\Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
    }
    lVar8 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar4,&UNK_029618d8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/STL_String.h"*/,0x1c);
    if (lVar8 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296188c/*"C:\BAS_Submission\Client\Library\Framework\Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
    lVar2 = lVar3 + lVar5 * 0x10;
    *(ulong *)(lVar2 + 0x18) = uVar6;
    *(long *)(lVar2 + 0x20) = lVar8;
    *puVar9 = uVar4 | 1;
code_r0x01f94e34:
    memcpy(lVar8,uVar10,uVar6);
  }
  *(undefined1 *)(lVar8 + uVar6) = 0;
code_r0x01f94e4c:
  puStack_68 = puStack_68 + 6;
  *(undefined4 *)(lVar3 + lVar5 * 0x10 + 0x28) = *(undefined4 *)(param_2 + 5);
  std::__ndk1::vector<Framework::CResourceElement::tMappingImage, Framework::CSTLAllocator<Framework::CResourceElement::tMappingImage, Framework::CSTLVectorAllocatorInf> >::__swap_out_circular_buffer(std::__ndk1::__split_buffer<Framework::CResourceElement::tMappingImage, Framework::CSTLAllocator<Framework::CResourceElement::tMappingImage, Framework::CSTLVectorAllocatorInf>&>&)(param_1,&lStack_78);
  puVar7 = puStack_70;
  while (puVar1 = puStack_68, puVar1 != puVar7) {
    puStack_68 = puVar1 + -6;
    if ((*(byte *)(puVar1 + -4) & 1) != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puVar1[-2]);
    }
  }
  if (lStack_78 != 0) {
    puStack_68 = puVar1;
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)();
  }
  return;
}

// ==== Framework::CResourceManager::tElement::tElement()
// vaddr 0x1e94ecc | ghidra 0x1f94ecc | size 8 | symbol _ZN9Framework16CResourceManager8tElementC2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework16CResourceManager8tElementC1Ev(undefined8 *param_1)

{
  *param_1 = 0;
  param_1[1] = 0;
  return;
}

// ==== Framework::CResourceManager::tElement::~tElement()
// vaddr 0x1e94ed4 | ghidra 0x1f94ed4 | size 4 | symbol _ZN9Framework16CResourceManager8tElementD2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework16CResourceManager8tElementD1Ev(void)

{
  return;
}

// ==== Framework::CResourceManager::tElement::Initialize(unsigned int, unsigned int, unsigned int, bool)
// vaddr 0x1e94ed8 | ghidra 0x1f94ed8 | size 232 | symbol _ZN9Framework16CResourceManager8tElement10InitializeEjjjb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework16CResourceManager8tElement10InitializeEjjjb
               (int *param_1,undefined4 param_2,undefined4 param_3,int param_4,uint param_5)

{
  uint uVar1;
  uint uVar2;
  long *plVar3;
  undefined8 uVar4;
  code *pcVar5;
  undefined2 uStack_48;
  undefined1 uStack_46;
  
  if (*(long *)(param_1 + 2) != 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029659c3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResourceManager.cpp"*/,0x26,&UNK_02965a1e/*"m_pResourceElement isn't null.(%08x)"*/);
  }
  if (*param_1 != 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029659c3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResourceManager.cpp"*/,0x27,&UNK_02965a43/*"m_ReferenceCounter == 0 is null."*/);
  }
  plVar3 = (long *)Framework::CResourceElement::gpInstantiate(unsigned int)(param_2);
  *(long **)(param_1 + 2) = plVar3;
  pcVar5 = *(code **)(*plVar3 + 0x38);
  uVar1 = Framework::CResourceElement::IsArchiveType(unsigned int)(param_2);
  uVar2 = Framework::CResourceElement::IsRquestMappingMemoryType(unsigned int)(param_2);
  uVar4 = Framework::CResourceElement::tMemoryDescription::Create(bool, bool, bool)(param_5 & 1,uVar1 & 1,uVar2 & 1);
  uStack_48 = (undefined2)uVar4;
  uStack_46 = (undefined1)((ulong)uVar4 >> 0x10);
  (*pcVar5)(plVar3,param_3,&uStack_48);
  *param_1 = *param_1 + 1;
  param_1[1] = param_4;
  return;
}

// ==== Framework::CResourceManager::tElement::IncrementReferenceCounter()
// vaddr 0x1e94fc0 | ghidra 0x1f94fc0 | size 16 | symbol _ZN9Framework16CResourceManager8tElement25IncrementReferenceCounterEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework16CResourceManager8tElement25IncrementReferenceCounterEv(int *param_1)

{
  *param_1 = *param_1 + 1;
  return;
}

// ==== Framework::CResourceManager::tElement::InitializeByDirectFile(unsigned int, char const*, unsigned int, bool)
// vaddr 0x1e94fd0 | ghidra 0x1f94fd0 | size 236 | symbol _ZN9Framework16CResourceManager8tElement22InitializeByDirectFileEjPKcjb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework16CResourceManager8tElement22InitializeByDirectFileEjPKcjb
               (int *param_1,undefined4 param_2,undefined8 param_3,int param_4,uint param_5)

{
  uint uVar1;
  uint uVar2;
  long *plVar3;
  undefined8 uVar4;
  code *pcVar5;
  undefined2 uStack_48;
  undefined1 uStack_46;
  
  if (*(long *)(param_1 + 2) != 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029659c3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResourceManager.cpp"*/,0x40,&UNK_02965a1e/*"m_pResourceElement isn't null.(%08x)"*/);
  }
  if (*param_1 != 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029659c3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResourceManager.cpp"*/,0x41,&UNK_02965a43/*"m_ReferenceCounter == 0 is null."*/);
  }
  plVar3 = (long *)Framework::CResourceElement::gpInstantiate(unsigned int)(param_2);
  *(long **)(param_1 + 2) = plVar3;
  pcVar5 = *(code **)(*plVar3 + 0x40);
  uVar1 = Framework::CResourceElement::IsArchiveType(unsigned int)(param_2);
  uVar2 = Framework::CResourceElement::IsRquestMappingMemoryType(unsigned int)(param_2);
  uVar4 = Framework::CResourceElement::tMemoryDescription::Create(bool, bool, bool)(param_5 & 1,uVar1 & 1,uVar2 & 1);
  uStack_48 = (undefined2)uVar4;
  uStack_46 = (undefined1)((ulong)uVar4 >> 0x10);
  (*pcVar5)(plVar3,param_3,&uStack_48,0);
  *param_1 = *param_1 + 1;
  param_1[1] = param_4;
  return;
}

// ==== Framework::CResourceManager::tElement::InitializeByDirectFileWithFolder(unsigned int, char const*, char const*, unsigned int, bool)
// vaddr 0x1e950bc | ghidra 0x1f950bc | size 248 | symbol _ZN9Framework16CResourceManager8tElement32InitializeByDirectFileWithFolderEjPKcS3_jb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework16CResourceManager8tElement32InitializeByDirectFileWithFolderEjPKcS3_jb
               (int *param_1,undefined4 param_2,undefined8 param_3,undefined8 param_4,int param_5,
               uint param_6)

{
  uint uVar1;
  uint uVar2;
  long *plVar3;
  undefined8 uVar4;
  code *pcVar5;
  undefined2 uStack_58;
  undefined1 uStack_56;
  
  if (*(long *)(param_1 + 2) != 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029659c3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResourceManager.cpp"*/,0x4a,&UNK_02965a1e/*"m_pResourceElement isn't null.(%08x)"*/);
  }
  if (*param_1 != 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029659c3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResourceManager.cpp"*/,0x4b,&UNK_02965a43/*"m_ReferenceCounter == 0 is null."*/);
  }
  plVar3 = (long *)Framework::CResourceElement::gpInstantiate(unsigned int)(param_2);
  *(long **)(param_1 + 2) = plVar3;
  pcVar5 = *(code **)(*plVar3 + 0x40);
  uVar1 = Framework::CResourceElement::IsArchiveType(unsigned int)(param_2);
  uVar2 = Framework::CResourceElement::IsRquestMappingMemoryType(unsigned int)(param_2);
  uVar4 = Framework::CResourceElement::tMemoryDescription::Create(bool, bool, bool)(param_6 & 1,uVar1 & 1,uVar2 & 1);
  uStack_58 = (undefined2)uVar4;
  uStack_56 = (undefined1)((ulong)uVar4 >> 0x10);
  (*pcVar5)(plVar3,param_4,&uStack_58,param_3);
  *param_1 = *param_1 + 1;
  param_1[1] = param_5;
  return;
}

// ==== Framework::CResourceManager::tElement::Release()
// vaddr 0x1e951b4 | ghidra 0x1f951b4 | size 36 | symbol _ZN9Framework16CResourceManager8tElement7ReleaseEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework16CResourceManager8tElement7ReleaseEv(undefined4 *param_1)

{
  Framework::CDelayDelete::AddTask(Aska::Task&)(*(long *)(param_1 + 2) + 0xc0);
  *(undefined8 *)(param_1 + 2) = 0;
  *param_1 = 0;
  return;
}

// ==== Framework::CResourceManager::tElement::DecrementReferenceCounter()
// vaddr 0x1e951d8 | ghidra 0x1f951d8 | size 64 | symbol _ZN9Framework16CResourceManager8tElement25DecrementReferenceCounterEv | lib libSOA-3.7.0.so | 2026-10-04
bool _ZN9Framework16CResourceManager8tElement25DecrementReferenceCounterEv(int *param_1)

{
  int iVar1;
  
  iVar1 = *param_1;
  if (iVar1 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029659c3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResourceManager.cpp"*/,0x65,&UNK_02965a64/*"Internal error. Reference counter already zero."*/);
    iVar1 = *param_1;
  }
  *param_1 = iVar1 + -1;
  return iVar1 + -1 == 0;
}

// ==== Framework::CResourceManager::tElement::ReferenceCounter() const
// vaddr 0x1e95218 | ghidra 0x1f95218 | size 8 | symbol _ZNK9Framework16CResourceManager8tElement16ReferenceCounterEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK9Framework16CResourceManager8tElement16ReferenceCounterEv(undefined4 *param_1)

{
  return *param_1;
}

// ==== Framework::CResourceManager::tElement::ForceRelease()
// vaddr 0x1e95220 | ghidra 0x1f95220 | size 36 | symbol _ZN9Framework16CResourceManager8tElement12ForceReleaseEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework16CResourceManager8tElement12ForceReleaseEv(undefined4 *param_1)

{
  Framework::CDelayDelete::AddTask(Aska::Task&)(*(long *)(param_1 + 2) + 0xc0);
  *(undefined8 *)(param_1 + 2) = 0;
  *param_1 = 0;
  return;
}

// ==== Framework::CResourceManager::tElement::rResourceElement()
// vaddr 0x1e95244 | ghidra 0x1f95244 | size 60 | symbol _ZN9Framework16CResourceManager8tElement16rResourceElementEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZN9Framework16CResourceManager8tElement16rResourceElementEv(long param_1)

{
  if (*(long *)(param_1 + 8) != 0) {
    return *(long *)(param_1 + 8);
  }
  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029659c3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResourceManager.cpp"*/,0x7e,&UNK_02965a94/*"m_pResourceElement is null."*/);
  return *(long *)(param_1 + 8);
}

// ==== Framework::CResourceManager::tElement::crResourceElement() const
// vaddr 0x1e95280 | ghidra 0x1f95280 | size 60 | symbol _ZNK9Framework16CResourceManager8tElement17crResourceElementEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK9Framework16CResourceManager8tElement17crResourceElementEv(long param_1)

{
  if (*(long *)(param_1 + 8) != 0) {
    return *(long *)(param_1 + 8);
  }
  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029659c3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResourceManager.cpp"*/,0x84,&UNK_02965a94/*"m_pResourceElement is null."*/);
  return *(long *)(param_1 + 8);
}

// ==== Framework::CResourceManager::tElement::UniqueBitFlag() const
// vaddr 0x1e952bc | ghidra 0x1f952bc | size 8 | symbol _ZNK9Framework16CResourceManager8tElement13UniqueBitFlagEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK9Framework16CResourceManager8tElement13UniqueBitFlagEv(long param_1)

{
  return *(undefined4 *)(param_1 + 4);
}

// ==== Framework::CResourceManager::tElement::OrUniqueBitFlag(unsigned int)
// vaddr 0x1e952c4 | ghidra 0x1f952c4 | size 16 | symbol _ZN9Framework16CResourceManager8tElement15OrUniqueBitFlagEj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework16CResourceManager8tElement15OrUniqueBitFlagEj(long param_1,uint param_2)

{
  *(uint *)(param_1 + 4) = *(uint *)(param_1 + 4) | param_2;
  return;
}

// ==== Framework::CResourceManager::tElement::AndUniqueBitFlag(unsigned int)
// vaddr 0x1e952d4 | ghidra 0x1f952d4 | size 16 | symbol _ZN9Framework16CResourceManager8tElement16AndUniqueBitFlagEj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework16CResourceManager8tElement16AndUniqueBitFlagEj(long param_1,uint param_2)

{
  *(uint *)(param_1 + 4) = *(uint *)(param_1 + 4) & param_2;
  return;
}

// ==== Framework::CResourceManager::CResourceManager(char const*)
// vaddr 0x1e952e4 | ghidra 0x1f952e4 | size 92 | symbol _ZN9Framework16CResourceManagerC1EPKc | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework16CResourceManagerC2EPKc(long *param_1)

{
  undefined *puVar1;
  undefined4 uVar2;
  code *pcVar3;
  
  pcVar3 = *(code **)(PTR__ZTVN4Aska4TaskE_02cbe020 + 0x68);
  *param_1 = (long)(PTR__ZTVN4Aska4TaskE_02cbe020 + 0x10);
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  *(undefined2 *)((long)param_1 + 0x24) = 0;
  *(undefined1 *)((long)param_1 + 0x26) = 0;
  uVar2 = (*pcVar3)();
  *(undefined4 *)(param_1 + 4) = uVar2;
  puVar1 = PTR__ZTVN9Framework16CResourceManagerE_02cc46d8;
  *(undefined1 *)((long)param_1 + 0x27) = 0;
  param_1[5] = (long)(param_1 + 5);
  param_1[6] = (long)(param_1 + 5);
  *param_1 = (long)(puVar1 + 0x10);
  param_1[7] = 0;
  (*(code *)PTR__ZN9Framework6CMutexC2Ev_02c96d98)(param_1 + 8);
  return;
}

// ==== Framework::CResourceManager::~CResourceManager()
// vaddr 0x1e95340 | ghidra 0x1f95340 | size 124 | symbol _ZN9Framework16CResourceManagerD1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework16CResourceManagerD2Ev(long *param_1)

{
  long lVar1;
  long *plVar2;
  
  *param_1 = (long)(PTR__ZTVN9Framework16CResourceManagerE_02cc46d8 + 0x10);
  Framework::CMutex::~CMutex()(param_1 + 8);
  if (param_1[7] != 0) {
    lVar1 = param_1[5];
    plVar2 = (long *)param_1[6];
    *(undefined8 *)(*plVar2 + 8) = *(undefined8 *)(lVar1 + 8);
    **(long **)(lVar1 + 8) = *plVar2;
    param_1[7] = 0;
    while (plVar2 != param_1 + 5) {
      plVar2 = (long *)plVar2[1];
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)();
    }
  }
  (*(code *)PTR__ZN4Aska4TaskD1Ev_02c92d10)(param_1);
  return;
}

// ==== Framework::CResourceManager::Release()
// vaddr 0x1e953bc | ghidra 0x1f953bc | size 4 | symbol _ZN9Framework16CResourceManager7ReleaseEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework16CResourceManager7ReleaseEv(void)

{
  return;
}

// ==== Framework::CResourceManager::~CResourceManager()
// vaddr 0x1e953c0 | ghidra 0x1f953c0 | size 132 | symbol _ZN9Framework16CResourceManagerD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework16CResourceManagerD0Ev(long *param_1)

{
  long lVar1;
  long *plVar2;
  
  *param_1 = (long)(PTR__ZTVN9Framework16CResourceManagerE_02cc46d8 + 0x10);
  Framework::CMutex::~CMutex()(param_1 + 8);
  if (param_1[7] != 0) {
    lVar1 = param_1[5];
    plVar2 = (long *)param_1[6];
    *(undefined8 *)(*plVar2 + 8) = *(undefined8 *)(lVar1 + 8);
    **(long **)(lVar1 + 8) = *plVar2;
    param_1[7] = 0;
    while (plVar2 != param_1 + 5) {
      plVar2 = (long *)plVar2[1];
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)();
    }
  }
  Aska::Task::~Task()(param_1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Framework::CResourceManager::Initialize()
// vaddr 0x1e95444 | ghidra 0x1f95444 | size 164 | symbol _ZN9Framework16CResourceManager10InitializeEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework16CResourceManager10InitializeEv(long param_1)

{
  long lVar1;
  long *plVar2;
  
  if (*(char *)(param_1 + 0x27) != '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029659c3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResourceManager.cpp"*/,0xba,&UNK_02964a0a/*"m_IsInitialized isn't null.(%08x)"*/);
  }
  Aska::TaskManager::Add(Aska::Task*)(*(undefined8 *)PTR__ZN4Aska6Global20m_pSystemTaskManagerE_02cbf620,param_1);
  if (*(long *)(param_1 + 0x38) != 0) {
    lVar1 = *(long *)(param_1 + 0x28);
    plVar2 = *(long **)(param_1 + 0x30);
    *(undefined8 *)(*plVar2 + 8) = *(undefined8 *)(lVar1 + 8);
    **(long **)(lVar1 + 8) = *plVar2;
    *(undefined8 *)(param_1 + 0x38) = 0;
    while (plVar2 != (long *)(param_1 + 0x28)) {
      plVar2 = (long *)plVar2[1];
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)();
    }
  }
  Framework::CMutex::Initialize()(param_1 + 0x40);
  *(undefined1 *)(param_1 + 0x27) = 1;
  return;
}

// ==== Framework::CResourceManager::Run(int)
// vaddr 0x1e954e8 | ghidra 0x1f954e8 | size 276 | symbol _ZN9Framework16CResourceManager3RunEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework16CResourceManager3RunEi(long param_1)

{
  long lVar1;
  long *plVar2;
  ulong uVar3;
  long *plVar4;
  
  if (*(char *)(param_1 + 0x27) == '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029659c3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResourceManager.cpp"*/,0xd5,&UNK_02964a2c/*"m_IsInitialized is null."*/);
  }
  lVar1 = param_1 + 0x40;
  uVar3 = Framework::CMutex::IsInitialized() const(lVar1);
  if ((uVar3 & 1) == 0) {
    Framework::CMutex::Initialize()(lVar1);
  }
  Framework::CMutex::Lock()(lVar1);
  plVar4 = *(long **)(param_1 + 0x30);
  while ((long *)(param_1 + 0x28) != plVar4) {
    while( true ) {
      if (plVar4[3] == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029659c3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResourceManager.cpp"*/,0x7e,&UNK_02965a94/*"m_pResourceElement is null."*/);
        uVar3 = Framework::CResourceElement::IsDone() const(plVar4[3]);
      }
      else {
        uVar3 = Framework::CResourceElement::IsDone() const();
      }
      if (((uVar3 & 1) != 0) && ((int)plVar4[2] == 0)) break;
      plVar4 = (long *)plVar4[1];
      if ((long *)(param_1 + 0x28) == plVar4) goto code_r0x011f7f50;
    }
    Framework::CDelayDelete::AddTask(Aska::Task&)(plVar4[3] + 0xc0);
    plVar2 = (long *)plVar4[1];
    plVar4[3] = 0;
    *(undefined4 *)(plVar4 + 2) = 0;
    *(long **)(*plVar4 + 8) = plVar2;
    *(long *)plVar4[1] = *plVar4;
    *(long *)(param_1 + 0x38) = *(long *)(param_1 + 0x38) + -1;
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar4);
    plVar4 = plVar2;
  }
code_r0x011f7f50:
  (*(code *)PTR__ZN9Framework6CMutex6UnlockEv_02cb3f98)(lVar1);
  return;
}

// ==== Framework::CResourceManager::pSearch(unsigned int) const
// vaddr 0x1e955fc | ghidra 0x1f955fc | size 164 | symbol _ZNK9Framework16CResourceManager7pSearchEj | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK9Framework16CResourceManager7pSearchEj(long param_1,int param_2)

{
  int iVar1;
  long lVar2;
  long lVar3;
  
  if (*(char *)(param_1 + 0x27) == '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029659c3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResourceManager.cpp"*/,0xfc,&UNK_02964a2c/*"m_IsInitialized is null."*/);
  }
  lVar3 = *(long *)(param_1 + 0x30);
  while( true ) {
    if (param_1 + 0x28 == lVar3) {
      return 0;
    }
    lVar2 = *(long *)(lVar3 + 0x18);
    if (lVar2 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029659c3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResourceManager.cpp"*/,0x84,&UNK_02965a94/*"m_pResourceElement is null."*/);
      lVar2 = *(long *)(lVar3 + 0x18);
    }
    iVar1 = Framework::CFileLoader::FileNumber() const(lVar2);
    if (iVar1 == param_2) break;
    lVar3 = *(long *)(lVar3 + 8);
  }
  return lVar3 + 0x10;
}

// ==== Framework::CResourceManager::pSearch(unsigned int)
// vaddr 0x1e956a0 | ghidra 0x1f956a0 | size 164 | symbol _ZN9Framework16CResourceManager7pSearchEj | lib libSOA-3.7.0.so | 2026-10-04
long _ZN9Framework16CResourceManager7pSearchEj(long param_1,int param_2)

{
  int iVar1;
  long lVar2;
  long lVar3;
  
  if (*(char *)(param_1 + 0x27) == '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029659c3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResourceManager.cpp"*/,0x10a,&UNK_02964a2c/*"m_IsInitialized is null."*/);
  }
  lVar3 = *(long *)(param_1 + 0x30);
  while( true ) {
    if (param_1 + 0x28 == lVar3) {
      return 0;
    }
    lVar2 = *(long *)(lVar3 + 0x18);
    if (lVar2 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029659c3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResourceManager.cpp"*/,0x7e,&UNK_02965a94/*"m_pResourceElement is null."*/);
      lVar2 = *(long *)(lVar3 + 0x18);
    }
    iVar1 = Framework::CFileLoader::FileNumber() const(lVar2);
    if (iVar1 == param_2) break;
    lVar3 = *(long *)(lVar3 + 8);
  }
  return lVar3 + 0x10;
}

// ==== Framework::CResourceManager::pSearchByDirectPath(char const*) const
// vaddr 0x1e95744 | ghidra 0x1f95744 | size 168 | symbol _ZNK9Framework16CResourceManager19pSearchByDirectPathEPKc | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK9Framework16CResourceManager19pSearchByDirectPathEPKc(long param_1,undefined8 param_2)

{
  int iVar1;
  long lVar2;
  undefined8 uVar3;
  long lVar4;
  
  if (*(char *)(param_1 + 0x27) == '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029659c3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResourceManager.cpp"*/,0x11c,&UNK_02964a2c/*"m_IsInitialized is null."*/);
  }
  lVar4 = *(long *)(param_1 + 0x30);
  while( true ) {
    if (param_1 + 0x28 == lVar4) {
      return 0;
    }
    lVar2 = *(long *)(lVar4 + 0x18);
    if (lVar2 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029659c3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResourceManager.cpp"*/,0x84,&UNK_02965a94/*"m_pResourceElement is null."*/);
      lVar2 = *(long *)(lVar4 + 0x18);
    }
    uVar3 = Framework::CFileLoader::pFileName() const(lVar2);
    iVar1 = strcmp(uVar3,param_2);
    if (iVar1 == 0) break;
    lVar4 = *(long *)(lVar4 + 8);
  }
  return lVar4 + 0x10;
}

// ==== Framework::CResourceManager::pSearchByDirectPath(char const*)
// vaddr 0x1e957ec | ghidra 0x1f957ec | size 168 | symbol _ZN9Framework16CResourceManager19pSearchByDirectPathEPKc | lib libSOA-3.7.0.so | 2026-10-04
long _ZN9Framework16CResourceManager19pSearchByDirectPathEPKc(long param_1,undefined8 param_2)

{
  int iVar1;
  long lVar2;
  undefined8 uVar3;
  long lVar4;
  
  if (*(char *)(param_1 + 0x27) == '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029659c3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResourceManager.cpp"*/,300,&UNK_02964a2c/*"m_IsInitialized is null."*/);
  }
  lVar4 = *(long *)(param_1 + 0x30);
  while( true ) {
    if (param_1 + 0x28 == lVar4) {
      return 0;
    }
    lVar2 = *(long *)(lVar4 + 0x18);
    if (lVar2 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029659c3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResourceManager.cpp"*/,0x7e,&UNK_02965a94/*"m_pResourceElement is null."*/);
      lVar2 = *(long *)(lVar4 + 0x18);
    }
    uVar3 = Framework::CFileLoader::pFileName() const(lVar2);
    iVar1 = strcmp(uVar3,param_2);
    if (iVar1 == 0) break;
    lVar4 = *(long *)(lVar4 + 8);
  }
  return lVar4 + 0x10;
}

// ==== Framework::CResourceManager::Add(unsigned int, unsigned int, unsigned int, bool)
// vaddr 0x1e95894 | ghidra 0x1f95894 | size 404 | symbol _ZN9Framework16CResourceManager3AddEjjjb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework16CResourceManager3AddEjjjb
               (long param_1,undefined4 param_2,int param_3,uint param_4,uint param_5)

{
  long lVar1;
  int iVar2;
  ulong uVar3;
  long lVar4;
  long *plVar5;
  long lVar6;
  long lStack_70;
  long lStack_68;
  
  if (*(char *)(param_1 + 0x27) == '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029659c3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResourceManager.cpp"*/,0x143,&UNK_02964a2c/*"m_IsInitialized is null."*/);
  }
  lVar1 = param_1 + 0x40;
  uVar3 = Framework::CMutex::IsInitialized() const(lVar1);
  if ((uVar3 & 1) == 0) {
    Framework::CMutex::Initialize()(lVar1);
  }
  Framework::CMutex::Lock()(lVar1);
  if (*(char *)(param_1 + 0x27) == '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029659c3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResourceManager.cpp"*/,0x10a,&UNK_02964a2c/*"m_IsInitialized is null."*/);
  }
  lVar6 = *(long *)(param_1 + 0x30);
  do {
    if (param_1 + 0x28 == lVar6) {
      lStack_70 = 0;
      lStack_68 = 0;
      Framework::CResourceManager::tElement::Initialize(unsigned int, unsigned int, unsigned int, bool)(&lStack_70,param_2,param_3,param_4,param_5 & 1);
      plVar5 = (long *)Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(0x20,&UNK_0296283b/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/STL_List.h"*/,0x20);
      if (plVar5 == (long *)0x0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296188c/*"C:\BAS_Submission\Client\Library\Framework\Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
      }
      plVar5[1] = param_1 + 0x28;
      plVar5[3] = lStack_68;
      plVar5[2] = lStack_70;
      lVar6 = *(long *)(param_1 + 0x28);
      *plVar5 = lVar6;
      *(long **)(lVar6 + 8) = plVar5;
      *(long **)(param_1 + 0x28) = plVar5;
      *(long *)(param_1 + 0x38) = *(long *)(param_1 + 0x38) + 1;
code_r0x011f7f50:
      (*(code *)PTR__ZN9Framework6CMutex6UnlockEv_02cb3f98)(lVar1);
      return;
    }
    lVar4 = *(long *)(lVar6 + 0x18);
    if (lVar4 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029659c3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResourceManager.cpp"*/,0x7e,&UNK_02965a94/*"m_pResourceElement is null."*/);
      lVar4 = *(long *)(lVar6 + 0x18);
    }
    iVar2 = Framework::CFileLoader::FileNumber() const(lVar4);
    if (iVar2 == param_3) {
      *(int *)(lVar6 + 0x10) = *(int *)(lVar6 + 0x10) + 1;
      *(uint *)(lVar6 + 0x14) = *(uint *)(lVar6 + 0x14) | param_4;
      goto code_r0x011f7f50;
    }
    lVar6 = *(long *)(lVar6 + 8);
  } while( true );
}

// ==== Framework::CResourceManager::AddByName(unsigned int, char const*, unsigned int, bool)
// vaddr 0x1e95a28 | ghidra 0x1f95a28 | size 100 | symbol _ZN9Framework16CResourceManager9AddByNameEjPKcjb | lib libSOA-3.7.0.so | 2026-10-04
bool _ZN9Framework16CResourceManager9AddByNameEjPKcjb
               (undefined8 param_1,undefined4 param_2,undefined8 param_3,undefined4 param_4,
               uint param_5)

{
  int iVar1;
  
  iVar1 = Framework::FileID::Get(char const*)(param_3);
  if (iVar1 != -1) {
    Framework::CResourceManager::Add(unsigned int, unsigned int, unsigned int, bool)(param_1,param_2,iVar1,param_4,param_5 & 1);
  }
  return iVar1 != -1;
}

// ==== Framework::CResourceManager::AddImmediateFile(unsigned int, unsigned int, char const*, unsigned int, bool)
// vaddr 0x1e95a8c | ghidra 0x1f95a8c | size 4 | symbol _ZN9Framework16CResourceManager16AddImmediateFileEjjPKcjb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework16CResourceManager16AddImmediateFileEjjPKcjb(void)

{
  return;
}

// ==== Framework::CResourceManager::AddDirectFile(unsigned int, char const*, unsigned int, bool)
// vaddr 0x1e95a90 | ghidra 0x1f95a90 | size 408 | symbol _ZN9Framework16CResourceManager13AddDirectFileEjPKcjb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework16CResourceManager13AddDirectFileEjPKcjb
               (long param_1,undefined4 param_2,undefined8 param_3,uint param_4,uint param_5)

{
  long lVar1;
  int iVar2;
  ulong uVar3;
  long lVar4;
  undefined8 uVar5;
  long *plVar6;
  long lVar7;
  long lStack_70;
  long lStack_68;
  
  if (*(char *)(param_1 + 0x27) == '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029659c3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResourceManager.cpp"*/,0x17a,&UNK_02964a2c/*"m_IsInitialized is null."*/);
  }
  lVar1 = param_1 + 0x40;
  uVar3 = Framework::CMutex::IsInitialized() const(lVar1);
  if ((uVar3 & 1) == 0) {
    Framework::CMutex::Initialize()(lVar1);
  }
  Framework::CMutex::Lock()(lVar1);
  if (*(char *)(param_1 + 0x27) == '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029659c3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResourceManager.cpp"*/,300,&UNK_02964a2c/*"m_IsInitialized is null."*/);
  }
  lVar7 = *(long *)(param_1 + 0x30);
  do {
    if (param_1 + 0x28 == lVar7) {
      lStack_70 = 0;
      lStack_68 = 0;
      Framework::CResourceManager::tElement::InitializeByDirectFile(unsigned int, char const*, unsigned int, bool)(&lStack_70,param_2,param_3,param_4,param_5 & 1);
      plVar6 = (long *)Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(0x20,&UNK_0296283b/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/STL_List.h"*/,0x20);
      if (plVar6 == (long *)0x0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296188c/*"C:\BAS_Submission\Client\Library\Framework\Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
      }
      plVar6[1] = param_1 + 0x28;
      plVar6[3] = lStack_68;
      plVar6[2] = lStack_70;
      lVar7 = *(long *)(param_1 + 0x28);
      *plVar6 = lVar7;
      *(long **)(lVar7 + 8) = plVar6;
      *(long **)(param_1 + 0x28) = plVar6;
      *(long *)(param_1 + 0x38) = *(long *)(param_1 + 0x38) + 1;
code_r0x011f7f50:
      (*(code *)PTR__ZN9Framework6CMutex6UnlockEv_02cb3f98)(lVar1);
      return;
    }
    lVar4 = *(long *)(lVar7 + 0x18);
    if (lVar4 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029659c3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResourceManager.cpp"*/,0x7e,&UNK_02965a94/*"m_pResourceElement is null."*/);
      lVar4 = *(long *)(lVar7 + 0x18);
    }
    uVar5 = Framework::CFileLoader::pFileName() const(lVar4);
    iVar2 = strcmp(uVar5,param_3);
    if (iVar2 == 0) {
      *(int *)(lVar7 + 0x10) = *(int *)(lVar7 + 0x10) + 1;
      *(uint *)(lVar7 + 0x14) = *(uint *)(lVar7 + 0x14) | param_4;
      goto code_r0x011f7f50;
    }
    lVar7 = *(long *)(lVar7 + 8);
  } while( true );
}

// ==== Framework::CResourceManager::AddDirectFileWithFolder(unsigned int, char const*, char const*, unsigned int, bool)
// vaddr 0x1e95c28 | ghidra 0x1f95c28 | size 416 | symbol _ZN9Framework16CResourceManager23AddDirectFileWithFolderEjPKcS2_jb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework16CResourceManager23AddDirectFileWithFolderEjPKcS2_jb
               (long param_1,undefined4 param_2,undefined8 param_3,undefined8 param_4,uint param_5,
               uint param_6)

{
  long lVar1;
  int iVar2;
  ulong uVar3;
  long lVar4;
  undefined8 uVar5;
  long *plVar6;
  long lVar7;
  long lStack_70;
  long lStack_68;
  
  if (*(char *)(param_1 + 0x27) == '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029659c3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResourceManager.cpp"*/,0x191,&UNK_02964a2c/*"m_IsInitialized is null."*/);
  }
  lVar1 = param_1 + 0x40;
  uVar3 = Framework::CMutex::IsInitialized() const(lVar1);
  if ((uVar3 & 1) == 0) {
    Framework::CMutex::Initialize()(lVar1);
  }
  Framework::CMutex::Lock()(lVar1);
  if (*(char *)(param_1 + 0x27) == '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029659c3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResourceManager.cpp"*/,300,&UNK_02964a2c/*"m_IsInitialized is null."*/);
  }
  lVar7 = *(long *)(param_1 + 0x30);
  do {
    if (param_1 + 0x28 == lVar7) {
      lStack_70 = 0;
      lStack_68 = 0;
      Framework::CResourceManager::tElement::InitializeByDirectFileWithFolder(unsigned int, char const*, char const*, unsigned int, bool)(&lStack_70,param_2,param_3,param_4,param_5,param_6 & 1);
      plVar6 = (long *)Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(0x20,&UNK_0296283b/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/STL_List.h"*/,0x20);
      if (plVar6 == (long *)0x0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296188c/*"C:\BAS_Submission\Client\Library\Framework\Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
      }
      plVar6[1] = param_1 + 0x28;
      plVar6[3] = lStack_68;
      plVar6[2] = lStack_70;
      lVar7 = *(long *)(param_1 + 0x28);
      *plVar6 = lVar7;
      *(long **)(lVar7 + 8) = plVar6;
      *(long **)(param_1 + 0x28) = plVar6;
      *(long *)(param_1 + 0x38) = *(long *)(param_1 + 0x38) + 1;
code_r0x011f7f50:
      (*(code *)PTR__ZN9Framework6CMutex6UnlockEv_02cb3f98)(lVar1);
      return;
    }
    lVar4 = *(long *)(lVar7 + 0x18);
    if (lVar4 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029659c3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResourceManager.cpp"*/,0x7e,&UNK_02965a94/*"m_pResourceElement is null."*/);
      lVar4 = *(long *)(lVar7 + 0x18);
    }
    uVar5 = Framework::CFileLoader::pFileName() const(lVar4);
    iVar2 = strcmp(uVar5,param_4);
    if (iVar2 == 0) {
      *(int *)(lVar7 + 0x10) = *(int *)(lVar7 + 0x10) + 1;
      *(uint *)(lVar7 + 0x14) = *(uint *)(lVar7 + 0x14) | param_5;
      goto code_r0x011f7f50;
    }
    lVar7 = *(long *)(lVar7 + 8);
  } while( true );
}

// ==== Framework::CResourceManager::Remove(unsigned int)
// vaddr 0x1e95dc8 | ghidra 0x1f95dc8 | size 268 | symbol _ZN9Framework16CResourceManager6RemoveEj | lib libSOA-3.7.0.so | 2026-10-04
uint _ZN9Framework16CResourceManager6RemoveEj(long param_1,int param_2)

{
  long lVar1;
  int iVar2;
  ulong uVar3;
  long lVar4;
  uint uVar5;
  uint extraout_w9;
  uint extraout_w9_00;
  uint uVar6;
  long lVar7;
  
  if (*(char *)(param_1 + 0x27) == '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029659c3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResourceManager.cpp"*/,0x1ac,&UNK_02964a2c/*"m_IsInitialized is null."*/);
  }
  lVar1 = param_1 + 0x40;
  uVar3 = Framework::CMutex::IsInitialized() const(lVar1);
  if ((uVar3 & 1) == 0) {
    Framework::CMutex::Initialize()(lVar1);
  }
  Framework::CMutex::Lock()(lVar1);
  lVar7 = *(long *)(param_1 + 0x30);
  uVar6 = extraout_w9;
  do {
    if (param_1 + 0x28 == lVar7) {
      uVar5 = 0;
code_r0x01f95eb0:
      Framework::CMutex::Unlock()(lVar1);
      return uVar5 & uVar6;
    }
    lVar4 = *(long *)(lVar7 + 0x18);
    if (lVar4 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029659c3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResourceManager.cpp"*/,0x7e,&UNK_02965a94/*"m_pResourceElement is null."*/);
      lVar4 = *(long *)(lVar7 + 0x18);
    }
    iVar2 = Framework::CFileLoader::FileNumber() const(lVar4);
    if (iVar2 == param_2) {
      iVar2 = *(int *)(lVar7 + 0x10);
      if (iVar2 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029659c3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResourceManager.cpp"*/,0x65,&UNK_02965a64/*"Internal error. Reference counter already zero."*/);
        iVar2 = *(int *)(lVar7 + 0x10);
      }
      *(int *)(lVar7 + 0x10) = iVar2 + -1;
      uVar6 = (uint)(iVar2 + -1 == 0);
      uVar5 = 1;
      goto code_r0x01f95eb0;
    }
    lVar7 = *(long *)(lVar7 + 8);
    uVar6 = extraout_w9_00;
  } while( true );
}

// ==== Framework::CResourceManager::RemoveByName(char const*)
// vaddr 0x1e95ed4 | ghidra 0x1f95ed4 | size 56 | symbol _ZN9Framework16CResourceManager12RemoveByNameEPKc | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN9Framework16CResourceManager12RemoveByNameEPKc(undefined8 param_1,undefined8 param_2)

{
  int iVar1;
  undefined8 uVar2;
  
  iVar1 = Framework::FileID::Get(char const*)(param_2);
  if (iVar1 != -1) {
    uVar2 = (*(code *)PTR__ZN9Framework16CResourceManager6RemoveEj_02ca2630)(param_1,iVar1);
    return uVar2;
  }
  return 0;
}

// ==== Framework::CResourceManager::RemoveDirectFile(char const*)
// vaddr 0x1e95f0c | ghidra 0x1f95f0c | size 280 | symbol _ZN9Framework16CResourceManager16RemoveDirectFileEPKc | lib libSOA-3.7.0.so | 2026-10-04
uint _ZN9Framework16CResourceManager16RemoveDirectFileEPKc(long param_1)

{
  long lVar1;
  ulong uVar2;
  long lVar3;
  uint uVar4;
  int iVar5;
  uint extraout_w9;
  uint extraout_w9_00;
  uint uVar6;
  long lVar7;
  undefined1 auStack_60 [16];
  undefined1 auStack_50 [16];
  
  Framework::CHash32::CHash32(char const*)(auStack_50);
  lVar1 = param_1 + 0x40;
  uVar2 = Framework::CMutex::IsInitialized() const(lVar1);
  if ((uVar2 & 1) == 0) {
    Framework::CMutex::Initialize()(lVar1);
  }
  Framework::CMutex::Lock()(lVar1);
  lVar7 = *(long *)(param_1 + 0x30);
  uVar6 = extraout_w9;
  do {
    if (param_1 + 0x28 == lVar7) {
      uVar4 = 0;
code_r0x01f95ff4:
      Framework::CMutex::Unlock()(lVar1);
      Framework::CHash32::~CHash32()(auStack_50);
      return uVar4 & uVar6;
    }
    lVar3 = *(long *)(lVar7 + 0x18);
    if (lVar3 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029659c3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResourceManager.cpp"*/,0x7e,&UNK_02965a94/*"m_pResourceElement is null."*/);
      lVar3 = *(long *)(lVar7 + 0x18);
    }
    Framework::CFileLoader::FileNameHash() const(auStack_60,lVar3);
    uVar2 = Framework::CHash32::operator==(Framework::CHash32 const&) const(auStack_60,auStack_50);
    Framework::CHash32::~CHash32()(auStack_60);
    if ((uVar2 & 1) != 0) {
      iVar5 = *(int *)(lVar7 + 0x10);
      if (iVar5 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029659c3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResourceManager.cpp"*/,0x65,&UNK_02965a64/*"Internal error. Reference counter already zero."*/);
        iVar5 = *(int *)(lVar7 + 0x10);
      }
      *(int *)(lVar7 + 0x10) = iVar5 + -1;
      uVar6 = (uint)(iVar5 + -1 == 0);
      uVar4 = 1;
      goto code_r0x01f95ff4;
    }
    lVar7 = *(long *)(lVar7 + 8);
    uVar6 = extraout_w9_00;
  } while( true );
}

// ==== Framework::CResourceManager::RemoveForce(unsigned int)
// vaddr 0x1e96024 | ghidra 0x1f96024 | size 228 | symbol _ZN9Framework16CResourceManager11RemoveForceEj | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZN9Framework16CResourceManager11RemoveForceEj(long param_1,int param_2)

{
  long lVar1;
  int iVar2;
  ulong uVar3;
  long lVar4;
  undefined4 uVar5;
  long lVar6;
  
  if (*(char *)(param_1 + 0x27) == '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029659c3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResourceManager.cpp"*/,0x1ea,&UNK_02964a2c/*"m_IsInitialized is null."*/);
  }
  lVar1 = param_1 + 0x40;
  uVar3 = Framework::CMutex::IsInitialized() const(lVar1);
  if ((uVar3 & 1) == 0) {
    Framework::CMutex::Initialize()(lVar1);
  }
  Framework::CMutex::Lock()(lVar1);
  lVar6 = *(long *)(param_1 + 0x30);
  do {
    if (param_1 + 0x28 == lVar6) {
      uVar5 = 0;
code_r0x01f960e8:
      Framework::CMutex::Unlock()(lVar1);
      return uVar5;
    }
    lVar4 = *(long *)(lVar6 + 0x18);
    if (lVar4 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029659c3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResourceManager.cpp"*/,0x7e,&UNK_02965a94/*"m_pResourceElement is null."*/);
      lVar4 = *(long *)(lVar6 + 0x18);
    }
    iVar2 = Framework::CFileLoader::FileNumber() const(lVar4);
    if (iVar2 == param_2) {
      if (*(int *)(lVar6 + 0x10) != 0) {
        *(undefined4 *)(lVar6 + 0x10) = 0;
      }
      uVar5 = 1;
      goto code_r0x01f960e8;
    }
    lVar6 = *(long *)(lVar6 + 8);
  } while( true );
}

// ==== Framework::CResourceManager::RemoveForceByName(char const*)
// vaddr 0x1e96108 | ghidra 0x1f96108 | size 64 | symbol _ZN9Framework16CResourceManager17RemoveForceByNameEPKc | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN9Framework16CResourceManager17RemoveForceByNameEPKc(undefined8 param_1,undefined8 param_2)

{
  int iVar1;
  
  iVar1 = Framework::FileID::Get(char const*)(param_2);
  if (iVar1 != -1) {
    Framework::CResourceManager::RemoveForce(unsigned int)(param_1,iVar1);
    return 1;
  }
  return 0;
}

// ==== Framework::CResourceManager::RemoveForceDirectFile(char const*)
// vaddr 0x1e96148 | ghidra 0x1f96148 | size 284 | symbol _ZN9Framework16CResourceManager21RemoveForceDirectFileEPKc | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZN9Framework16CResourceManager21RemoveForceDirectFileEPKc(long param_1)

{
  long lVar1;
  ulong uVar2;
  long lVar3;
  undefined4 uVar4;
  long *plVar5;
  undefined1 auStack_60 [16];
  undefined1 auStack_50 [16];
  
  Framework::CHash32::CHash32(char const*)(auStack_50);
  lVar1 = param_1 + 0x40;
  uVar2 = Framework::CMutex::IsInitialized() const(lVar1);
  if ((uVar2 & 1) == 0) {
    Framework::CMutex::Initialize()(lVar1);
  }
  Framework::CMutex::Lock()(lVar1);
  plVar5 = *(long **)(param_1 + 0x30);
  do {
    if ((long *)(param_1 + 0x28) == plVar5) {
      uVar4 = 0;
code_r0x01f96238:
      Framework::CMutex::Unlock()(lVar1);
      Framework::CHash32::~CHash32()(auStack_50);
      return uVar4;
    }
    lVar3 = plVar5[3];
    if (lVar3 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029659c3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResourceManager.cpp"*/,0x7e,&UNK_02965a94/*"m_pResourceElement is null."*/);
      lVar3 = plVar5[3];
    }
    Framework::CFileLoader::FileNameHash() const(auStack_60,lVar3);
    uVar2 = Framework::CHash32::operator==(Framework::CHash32 const&) const(auStack_60,auStack_50);
    Framework::CHash32::~CHash32()(auStack_60);
    if ((uVar2 & 1) != 0) {
      Framework::CDelayDelete::AddTask(Aska::Task&)(plVar5[3] + 0xc0);
      plVar5[3] = 0;
      *(undefined4 *)(plVar5 + 2) = 0;
      *(long *)(*plVar5 + 8) = plVar5[1];
      *(long *)plVar5[1] = *plVar5;
      *(long *)(param_1 + 0x38) = *(long *)(param_1 + 0x38) + -1;
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar5);
      uVar4 = 1;
      goto code_r0x01f96238;
    }
    plVar5 = (long *)plVar5[1];
  } while( true );
}

// ==== Framework::CResourceManager::RemoveByUniqueBitFlag(unsigned int)
// vaddr 0x1e96264 | ghidra 0x1f96264 | size 224 | symbol _ZN9Framework16CResourceManager21RemoveByUniqueBitFlagEj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework16CResourceManager21RemoveByUniqueBitFlagEj(long param_1,uint param_2)

{
  long lVar1;
  ulong uVar2;
  int iVar3;
  long lVar4;
  
  if (*(char *)(param_1 + 0x27) == '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029659c3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResourceManager.cpp"*/,0x22c,&UNK_02964a2c/*"m_IsInitialized is null."*/);
  }
  lVar1 = param_1 + 0x40;
  uVar2 = Framework::CMutex::IsInitialized() const(lVar1);
  if ((uVar2 & 1) == 0) {
    Framework::CMutex::Initialize()(lVar1);
  }
  Framework::CMutex::Lock()(lVar1);
  lVar4 = *(long *)(param_1 + 0x30);
  if (param_1 + 0x28 != lVar4) {
code_r0x01f962e0:
    do {
      if ((*(uint *)(lVar4 + 0x14) & param_2) != 0) {
        iVar3 = *(int *)(lVar4 + 0x10);
        if (iVar3 == 0) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029659c3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResourceManager.cpp"*/,0x65,&UNK_02965a64/*"Internal error. Reference counter already zero."*/);
          iVar3 = *(int *)(lVar4 + 0x10);
        }
        *(int *)(lVar4 + 0x10) = iVar3 + -1;
        if (iVar3 + -1 == 0) goto code_r0x01f962e0;
        *(uint *)(lVar4 + 0x14) = *(uint *)(lVar4 + 0x14) & ~param_2;
      }
      lVar4 = *(long *)(lVar4 + 8);
    } while (param_1 + 0x28 != lVar4);
  }
  (*(code *)PTR__ZN9Framework6CMutex6UnlockEv_02cb3f98)(lVar1);
  return;
}

// ==== Framework::CResourceManager::IsReady(unsigned int, bool*) const
// vaddr 0x1e96344 | ghidra 0x1f96344 | size 328 | symbol _ZNK9Framework16CResourceManager7IsReadyEjPb | lib libSOA-3.7.0.so | 2026-10-04
uint _ZNK9Framework16CResourceManager7IsReadyEjPb(long param_1,int param_2,long param_3)

{
  long lVar1;
  int iVar2;
  uint uVar3;
  ulong uVar4;
  long lVar5;
  long lVar6;
  
  if (*(char *)(param_1 + 0x27) == '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029659c3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResourceManager.cpp"*/,0x251,&UNK_02964a2c/*"m_IsInitialized is null."*/);
  }
  lVar1 = param_1 + 0x40;
  uVar4 = Framework::CMutex::IsInitialized() const(lVar1);
  if ((uVar4 & 1) == 0) {
    Framework::CMutex::Initialize()(lVar1);
  }
  Framework::CMutex::Lock()(lVar1);
  if (*(char *)(param_1 + 0x27) == '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029659c3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResourceManager.cpp"*/,0xfc,&UNK_02964a2c/*"m_IsInitialized is null."*/);
  }
  lVar6 = *(long *)(param_1 + 0x30);
  do {
    if (param_1 + 0x28 == lVar6) {
      lVar6 = 0;
joined_r0x01f96484:
      if (param_3 != 0) {
        *(bool *)param_3 = lVar6 != 0;
      }
      if (lVar6 == 0) {
        uVar3 = 0;
      }
      else {
        lVar5 = *(long *)(lVar6 + 8);
        if (lVar5 == 0) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029659c3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResourceManager.cpp"*/,0x84,&UNK_02965a94/*"m_pResourceElement is null."*/);
          lVar5 = *(long *)(lVar6 + 8);
        }
        uVar3 = Framework::CResourceElement::IsDone() const(lVar5);
      }
      Framework::CMutex::Unlock()(lVar1);
      return uVar3 & 1;
    }
    lVar5 = *(long *)(lVar6 + 0x18);
    if (lVar5 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029659c3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResourceManager.cpp"*/,0x84,&UNK_02965a94/*"m_pResourceElement is null."*/);
      lVar5 = *(long *)(lVar6 + 0x18);
    }
    iVar2 = Framework::CFileLoader::FileNumber() const(lVar5);
    if (iVar2 == param_2) {
      lVar6 = lVar6 + 0x10;
      goto joined_r0x01f96484;
    }
    lVar6 = *(long *)(lVar6 + 8);
  } while( true );
}

// ==== Framework::CResourceManager::IsReadyByName(char const*, bool*) const
// vaddr 0x1e9648c | ghidra 0x1f9648c | size 48 | symbol _ZNK9Framework16CResourceManager13IsReadyByNameEPKcPb | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK9Framework16CResourceManager13IsReadyByNameEPKcPb
               (undefined8 param_1,undefined8 param_2,undefined8 param_3)

{
  undefined4 uVar1;
  
  uVar1 = Framework::FileID::Get(char const*)(param_2);
  (*(code *)PTR__ZNK9Framework16CResourceManager7IsReadyEjPb_02ca3c38)(param_1,uVar1,param_3);
  return;
}

// ==== Framework::CResourceManager::IsReadyDirectFile(char const*, bool*) const
// vaddr 0x1e964bc | ghidra 0x1f964bc | size 332 | symbol _ZNK9Framework16CResourceManager17IsReadyDirectFileEPKcPb | lib libSOA-3.7.0.so | 2026-10-04
uint _ZNK9Framework16CResourceManager17IsReadyDirectFileEPKcPb
               (long param_1,undefined8 param_2,long param_3)

{
  long lVar1;
  int iVar2;
  uint uVar3;
  ulong uVar4;
  long lVar5;
  undefined8 uVar6;
  long lVar7;
  
  if (*(char *)(param_1 + 0x27) == '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029659c3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResourceManager.cpp"*/,0x263,&UNK_02964a2c/*"m_IsInitialized is null."*/);
  }
  lVar1 = param_1 + 0x40;
  uVar4 = Framework::CMutex::IsInitialized() const(lVar1);
  if ((uVar4 & 1) == 0) {
    Framework::CMutex::Initialize()(lVar1);
  }
  Framework::CMutex::Lock()(lVar1);
  if (*(char *)(param_1 + 0x27) == '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029659c3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResourceManager.cpp"*/,0x11c,&UNK_02964a2c/*"m_IsInitialized is null."*/);
  }
  lVar7 = *(long *)(param_1 + 0x30);
  do {
    if (param_1 + 0x28 == lVar7) {
      lVar7 = 0;
joined_r0x01f96600:
      if (param_3 != 0) {
        *(bool *)param_3 = lVar7 != 0;
      }
      if (lVar7 == 0) {
        uVar3 = 0;
      }
      else {
        lVar5 = *(long *)(lVar7 + 8);
        if (lVar5 == 0) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029659c3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResourceManager.cpp"*/,0x84,&UNK_02965a94/*"m_pResourceElement is null."*/);
          lVar5 = *(long *)(lVar7 + 8);
        }
        uVar3 = Framework::CResourceElement::IsDone() const(lVar5);
      }
      Framework::CMutex::Unlock()(lVar1);
      return uVar3 & 1;
    }
    lVar5 = *(long *)(lVar7 + 0x18);
    if (lVar5 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029659c3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResourceManager.cpp"*/,0x84,&UNK_02965a94/*"m_pResourceElement is null."*/);
      lVar5 = *(long *)(lVar7 + 0x18);
    }
    uVar6 = Framework::CFileLoader::pFileName() const(lVar5);
    iVar2 = strcmp(uVar6,param_2);
    if (iVar2 == 0) {
      lVar7 = lVar7 + 0x10;
      goto joined_r0x01f96600;
    }
    lVar7 = *(long *)(lVar7 + 8);
  } while( true );
}

// ==== Framework::CResourceManager::Lock()
// vaddr 0x1e96608 | ghidra 0x1f96608 | size 52 | symbol _ZN9Framework16CResourceManager4LockEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework16CResourceManager4LockEv(long param_1)

{
  if (*(char *)(param_1 + 0x27) == '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029659c3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResourceManager.cpp"*/,0x271,&UNK_02964a2c/*"m_IsInitialized is null."*/);
  }
  (*(code *)PTR__ZN9Framework6CMutex4LockEv_02c9c1d0)(param_1 + 0x40);
  return;
}

// ==== Framework::CResourceManager::Unlock()
// vaddr 0x1e9663c | ghidra 0x1f9663c | size 52 | symbol _ZN9Framework16CResourceManager6UnlockEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework16CResourceManager6UnlockEv(long param_1)

{
  if (*(char *)(param_1 + 0x27) == '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029659c3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResourceManager.cpp"*/,0x278,&UNK_02964a2c/*"m_IsInitialized is null."*/);
  }
  (*(code *)PTR__ZN9Framework6CMutex6UnlockEv_02cb3f98)(param_1 + 0x40);
  return;
}

// ==== Framework::CResourceManager::IsLocked() const
// vaddr 0x1e96670 | ghidra 0x1f96670 | size 52 | symbol _ZNK9Framework16CResourceManager8IsLockedEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK9Framework16CResourceManager8IsLockedEv(long param_1)

{
  if (*(char *)(param_1 + 0x27) == '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029659c3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResourceManager.cpp"*/,0x27f,&UNK_02964a2c/*"m_IsInitialized is null."*/);
  }
  (*(code *)PTR__ZNK9Framework6CMutex8IsLockedEv_02c96d08)(param_1 + 0x40);
  return;
}

// ==== Framework::CResourceManager::LockCounter() const
// vaddr 0x1e966a4 | ghidra 0x1f966a4 | size 52 | symbol _ZNK9Framework16CResourceManager11LockCounterEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK9Framework16CResourceManager11LockCounterEv(long param_1)

{
  if (*(char *)(param_1 + 0x27) == '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029659c3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResourceManager.cpp"*/,0x285,&UNK_02964a2c/*"m_IsInitialized is null."*/);
  }
  (*(code *)PTR__ZNK9Framework6CMutex11LockCounterEv_02ca4118)(param_1 + 0x40);
  return;
}

// ==== Framework::CResourceManager::rResourceElement(unsigned int)
// vaddr 0x1e966d8 | ghidra 0x1f966d8 | size 312 | symbol _ZN9Framework16CResourceManager16rResourceElementEj | lib libSOA-3.7.0.so | 2026-10-04
long _ZN9Framework16CResourceManager16rResourceElementEj(long param_1,int param_2)

{
  int iVar1;
  ulong uVar2;
  long lVar3;
  undefined8 uVar4;
  long lVar5;
  
  if (*(char *)(param_1 + 0x27) == '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029659c3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResourceManager.cpp"*/,0x28f,&UNK_02964a2c/*"m_IsInitialized is null."*/);
  }
  uVar2 = Framework::CMutex::IsLocked() const(param_1 + 0x40);
  if ((uVar2 & 1) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029659c3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResourceManager.cpp"*/,0x290,&UNK_02965ab0/*"Mutex was not locked."*/);
  }
  if (*(char *)(param_1 + 0x27) == '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029659c3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResourceManager.cpp"*/,0x10a,&UNK_02964a2c/*"m_IsInitialized is null."*/);
  }
  lVar5 = *(long *)(param_1 + 0x30);
  do {
    if (param_1 + 0x28 == lVar5) {
      uVar4 = Framework::FileID::gpFileName(unsigned int)(param_2);
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029659c3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResourceManager.cpp"*/,0x292,&UNK_02965ac6/*"The resource [%s] doesn't found"*/,uVar4);
      lVar3 = 0;
      lVar5 = lRam0000000000000008;
      if (lRam0000000000000008 == 0) {
code_r0x01f967d4:
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029659c3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResourceManager.cpp"*/,0x7e,&UNK_02965a94/*"m_pResourceElement is null."*/);
        lVar5 = *(long *)(lVar3 + 8);
      }
      return lVar5;
    }
    lVar3 = *(long *)(lVar5 + 0x18);
    if (lVar3 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029659c3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResourceManager.cpp"*/,0x7e,&UNK_02965a94/*"m_pResourceElement is null."*/);
      lVar3 = *(long *)(lVar5 + 0x18);
    }
    iVar1 = Framework::CFileLoader::FileNumber() const(lVar3);
    if (iVar1 == param_2) {
      lVar3 = lVar5 + 0x10;
      if (*(long *)(lVar5 + 0x18) != 0) {
        return *(long *)(lVar5 + 0x18);
      }
      goto code_r0x01f967d4;
    }
    lVar5 = *(long *)(lVar5 + 8);
  } while( true );
}

// ==== Framework::CResourceManager::crResourceElement(unsigned int) const
// vaddr 0x1e96810 | ghidra 0x1f96810 | size 312 | symbol _ZNK9Framework16CResourceManager17crResourceElementEj | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK9Framework16CResourceManager17crResourceElementEj(long param_1,int param_2)

{
  int iVar1;
  ulong uVar2;
  long lVar3;
  undefined8 uVar4;
  long lVar5;
  
  if (*(char *)(param_1 + 0x27) == '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029659c3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResourceManager.cpp"*/,0x298,&UNK_02964a2c/*"m_IsInitialized is null."*/);
  }
  uVar2 = Framework::CMutex::IsLocked() const(param_1 + 0x40);
  if ((uVar2 & 1) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029659c3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResourceManager.cpp"*/,0x299,&UNK_02965ab0/*"Mutex was not locked."*/);
  }
  if (*(char *)(param_1 + 0x27) == '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029659c3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResourceManager.cpp"*/,0xfc,&UNK_02964a2c/*"m_IsInitialized is null."*/);
  }
  lVar5 = *(long *)(param_1 + 0x30);
  do {
    if (param_1 + 0x28 == lVar5) {
      uVar4 = Framework::FileID::gpFileName(unsigned int)(param_2);
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029659c3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResourceManager.cpp"*/,0x29b,&UNK_02965ac6/*"The resource [%s] doesn't found"*/,uVar4);
      lVar3 = 0;
      lVar5 = lRam0000000000000008;
      if (lRam0000000000000008 == 0) {
code_r0x01f9690c:
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029659c3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResourceManager.cpp"*/,0x84,&UNK_02965a94/*"m_pResourceElement is null."*/);
        lVar5 = *(long *)(lVar3 + 8);
      }
      return lVar5;
    }
    lVar3 = *(long *)(lVar5 + 0x18);
    if (lVar3 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029659c3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResourceManager.cpp"*/,0x84,&UNK_02965a94/*"m_pResourceElement is null."*/);
      lVar3 = *(long *)(lVar5 + 0x18);
    }
    iVar1 = Framework::CFileLoader::FileNumber() const(lVar3);
    if (iVar1 == param_2) {
      lVar3 = lVar5 + 0x10;
      if (*(long *)(lVar5 + 0x18) != 0) {
        return *(long *)(lVar5 + 0x18);
      }
      goto code_r0x01f9690c;
    }
    lVar5 = *(long *)(lVar5 + 8);
  } while( true );
}

// ==== Framework::CResourceManager::rResourceElementByName(char const*)
// vaddr 0x1e96948 | ghidra 0x1f96948 | size 36 | symbol _ZN9Framework16CResourceManager22rResourceElementByNameEPKc | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework16CResourceManager22rResourceElementByNameEPKc
               (undefined8 param_1,undefined8 param_2)

{
  undefined4 uVar1;
  
  uVar1 = Framework::FileID::Get(char const*)(param_2);
  Framework::CResourceManager::rResourceElement(unsigned int)(param_1,uVar1);
  return;
}

// ==== Framework::CResourceManager::crResourceElementByName(char const*) const
// vaddr 0x1e9696c | ghidra 0x1f9696c | size 36 | symbol _ZNK9Framework16CResourceManager23crResourceElementByNameEPKc | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK9Framework16CResourceManager23crResourceElementByNameEPKc
               (undefined8 param_1,undefined8 param_2)

{
  undefined4 uVar1;
  
  uVar1 = Framework::FileID::Get(char const*)(param_2);
  Framework::CResourceManager::crResourceElement(unsigned int) const(param_1,uVar1);
  return;
}

// ==== Framework::CResourceManager::rResourceElementDirectFile(char const*)
// vaddr 0x1e96990 | ghidra 0x1f96990 | size 308 | symbol _ZN9Framework16CResourceManager26rResourceElementDirectFileEPKc | lib libSOA-3.7.0.so | 2026-10-04
long _ZN9Framework16CResourceManager26rResourceElementDirectFileEPKc
               (long param_1,undefined8 param_2)

{
  int iVar1;
  ulong uVar2;
  long lVar3;
  undefined8 uVar4;
  long lVar5;
  
  if (*(char *)(param_1 + 0x27) == '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029659c3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResourceManager.cpp"*/,0x2ac,&UNK_02964a2c/*"m_IsInitialized is null."*/);
  }
  uVar2 = Framework::CMutex::IsLocked() const(param_1 + 0x40);
  if ((uVar2 & 1) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029659c3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResourceManager.cpp"*/,0x2ad,&UNK_02965ab0/*"Mutex was not locked."*/);
  }
  if (*(char *)(param_1 + 0x27) == '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029659c3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResourceManager.cpp"*/,300,&UNK_02964a2c/*"m_IsInitialized is null."*/);
  }
  lVar5 = *(long *)(param_1 + 0x30);
  do {
    if (param_1 + 0x28 == lVar5) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029659c3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResourceManager.cpp"*/,0x2af,&UNK_02965ac6/*"The resource [%s] doesn't found"*/,param_2);
      lVar3 = 0;
      lVar5 = lRam0000000000000008;
      if (lRam0000000000000008 == 0) {
code_r0x01f96a88:
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029659c3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResourceManager.cpp"*/,0x7e,&UNK_02965a94/*"m_pResourceElement is null."*/);
        lVar5 = *(long *)(lVar3 + 8);
      }
      return lVar5;
    }
    lVar3 = *(long *)(lVar5 + 0x18);
    if (lVar3 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029659c3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResourceManager.cpp"*/,0x7e,&UNK_02965a94/*"m_pResourceElement is null."*/);
      lVar3 = *(long *)(lVar5 + 0x18);
    }
    uVar4 = Framework::CFileLoader::pFileName() const(lVar3);
    iVar1 = strcmp(uVar4,param_2);
    if (iVar1 == 0) {
      lVar3 = lVar5 + 0x10;
      if (*(long *)(lVar5 + 0x18) != 0) {
        return *(long *)(lVar5 + 0x18);
      }
      goto code_r0x01f96a88;
    }
    lVar5 = *(long *)(lVar5 + 8);
  } while( true );
}

// ==== Framework::CResourceManager::crResourceElementDirectFile(char const*) const
// vaddr 0x1e96ac4 | ghidra 0x1f96ac4 | size 308 | symbol _ZNK9Framework16CResourceManager27crResourceElementDirectFileEPKc | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK9Framework16CResourceManager27crResourceElementDirectFileEPKc
               (long param_1,undefined8 param_2)

{
  int iVar1;
  ulong uVar2;
  long lVar3;
  undefined8 uVar4;
  long lVar5;
  
  if (*(char *)(param_1 + 0x27) == '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029659c3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResourceManager.cpp"*/,0x2b5,&UNK_02964a2c/*"m_IsInitialized is null."*/);
  }
  uVar2 = Framework::CMutex::IsLocked() const(param_1 + 0x40);
  if ((uVar2 & 1) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029659c3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResourceManager.cpp"*/,0x2b6,&UNK_02965ab0/*"Mutex was not locked."*/);
  }
  if (*(char *)(param_1 + 0x27) == '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029659c3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResourceManager.cpp"*/,0x11c,&UNK_02964a2c/*"m_IsInitialized is null."*/);
  }
  lVar5 = *(long *)(param_1 + 0x30);
  do {
    if (param_1 + 0x28 == lVar5) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029659c3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResourceManager.cpp"*/,0x2b8,&UNK_02965ac6/*"The resource [%s] doesn't found"*/,param_2);
      lVar3 = 0;
      lVar5 = lRam0000000000000008;
      if (lRam0000000000000008 == 0) {
code_r0x01f96bbc:
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029659c3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResourceManager.cpp"*/,0x84,&UNK_02965a94/*"m_pResourceElement is null."*/);
        lVar5 = *(long *)(lVar3 + 8);
      }
      return lVar5;
    }
    lVar3 = *(long *)(lVar5 + 0x18);
    if (lVar3 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029659c3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResourceManager.cpp"*/,0x84,&UNK_02965a94/*"m_pResourceElement is null."*/);
      lVar3 = *(long *)(lVar5 + 0x18);
    }
    uVar4 = Framework::CFileLoader::pFileName() const(lVar3);
    iVar1 = strcmp(uVar4,param_2);
    if (iVar1 == 0) {
      lVar3 = lVar5 + 0x10;
      if (*(long *)(lVar5 + 0x18) != 0) {
        return *(long *)(lVar5 + 0x18);
      }
      goto code_r0x01f96bbc;
    }
    lVar5 = *(long *)(lVar5 + 8);
  } while( true );
}

// ==== Framework::CResourceManager::crResourceElementByIndex(unsigned int) const
// vaddr 0x1e96bf8 | ghidra 0x1f96bf8 | size 164 | symbol _ZNK9Framework16CResourceManager24crResourceElementByIndexEj | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK9Framework16CResourceManager24crResourceElementByIndexEj(long param_1,uint param_2)

{
  ulong uVar1;
  long lVar2;
  long lVar3;
  
  if (*(char *)(param_1 + 0x27) == '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029659c3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResourceManager.cpp"*/,0x2be,&UNK_02964a2c/*"m_IsInitialized is null."*/);
  }
  uVar1 = Framework::CMutex::IsLocked() const(param_1 + 0x40);
  if ((uVar1 & 1) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029659c3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResourceManager.cpp"*/,0x2bf,&UNK_02965ab0/*"Mutex was not locked."*/);
  }
  lVar3 = *(long *)(param_1 + 0x30);
  if (param_2 != 0) {
    lVar2 = (ulong)param_2 + 1;
    do {
      lVar3 = *(long *)(lVar3 + 8);
      lVar2 = lVar2 + -1;
    } while (1 < lVar2);
  }
  lVar2 = *(long *)(lVar3 + 0x18);
  if (lVar2 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029659c3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResourceManager.cpp"*/,0x84,&UNK_02965a94/*"m_pResourceElement is null."*/);
    lVar2 = *(long *)(lVar3 + 0x18);
  }
  return lVar2;
}

// ==== Framework::CResourceManager::NumLoading() const
// vaddr 0x1e96c9c | ghidra 0x1f96c9c | size 220 | symbol _ZNK9Framework16CResourceManager10NumLoadingEv | lib libSOA-3.7.0.so | 2026-10-04
int _ZNK9Framework16CResourceManager10NumLoadingEv(long param_1)

{
  long lVar1;
  uint uVar2;
  ulong uVar3;
  long lVar4;
  int iVar5;
  long lVar6;
  
  if (*(char *)(param_1 + 0x27) == '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029659c3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResourceManager.cpp"*/,0x2cd,&UNK_02964a2c/*"m_IsInitialized is null."*/);
  }
  lVar1 = param_1 + 0x40;
  uVar3 = Framework::CMutex::IsLocked() const(lVar1);
  if ((uVar3 & 1) == 0) {
    Framework::CMutex::Lock()(lVar1);
  }
  lVar6 = *(long *)(param_1 + 0x30);
  if (param_1 + 0x28 == lVar6) {
    iVar5 = 0;
  }
  else {
    iVar5 = 0;
    do {
      lVar4 = *(long *)(lVar6 + 0x18);
      if (lVar4 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029659c3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResourceManager.cpp"*/,0x84,&UNK_02965a94/*"m_pResourceElement is null."*/);
        lVar4 = *(long *)(lVar6 + 0x18);
      }
      uVar2 = Framework::CResourceElement::IsDone() const(lVar4);
      lVar6 = *(long *)(lVar6 + 8);
      iVar5 = iVar5 + (~uVar2 & 1);
    } while (param_1 + 0x28 != lVar6);
  }
  if ((uVar3 & 1) == 0) {
    Framework::CMutex::Unlock()(lVar1);
  }
  return iVar5;
}

// ==== Framework::CResourceManager::IsLoading() const
// vaddr 0x1e96d78 | ghidra 0x1f96d78 | size 284 | symbol _ZNK9Framework16CResourceManager9IsLoadingEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK9Framework16CResourceManager9IsLoadingEv(long param_1)

{
  long lVar1;
  ulong uVar2;
  long lVar3;
  ulong uVar4;
  long lVar5;
  
  if (*(char *)(param_1 + 0x27) == '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029659c3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResourceManager.cpp"*/,0x2e6,&UNK_02964a2c/*"m_IsInitialized is null."*/);
  }
  lVar1 = param_1 + 0x40;
  uVar2 = Framework::CMutex::IsLocked() const(lVar1);
  if ((uVar2 & 1) == 0) {
    Framework::CMutex::Lock()(lVar1);
  }
  lVar5 = *(long *)(param_1 + 0x30);
  param_1 = param_1 + 0x28;
  if (param_1 != lVar5) {
    if ((uVar2 & 1) == 0) {
      do {
        lVar3 = *(long *)(lVar5 + 0x18);
        if (lVar3 == 0) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029659c3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResourceManager.cpp"*/,0x84,&UNK_02965a94/*"m_pResourceElement is null."*/);
          lVar3 = *(long *)(lVar5 + 0x18);
        }
        uVar4 = Framework::CResourceElement::IsDone() const(lVar3);
        if ((uVar4 & 1) == 0) {
          Framework::CMutex::Unlock()(lVar1);
          return 1;
        }
        lVar5 = *(long *)(lVar5 + 8);
      } while (param_1 != lVar5);
    }
    else {
      do {
        lVar3 = *(long *)(lVar5 + 0x18);
        if (lVar3 == 0) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029659c3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResourceManager.cpp"*/,0x84,&UNK_02965a94/*"m_pResourceElement is null."*/);
          lVar3 = *(long *)(lVar5 + 0x18);
        }
        uVar4 = Framework::CResourceElement::IsDone() const(lVar3);
        if ((uVar4 & 1) == 0) {
          return 1;
        }
        lVar5 = *(long *)(lVar5 + 8);
      } while (param_1 != lVar5);
    }
  }
  if ((uVar2 & 1) == 0) {
    Framework::CMutex::Unlock()(lVar1);
  }
  return 0;
}

// ==== Framework::CResourceManager::Num() const
// vaddr 0x1e96e94 | ghidra 0x1f96e94 | size 104 | symbol _ZNK9Framework16CResourceManager3NumEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK9Framework16CResourceManager3NumEv(long param_1)

{
  long lVar1;
  undefined4 uVar2;
  ulong uVar3;
  
  if (*(char *)(param_1 + 0x27) == '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029659c3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResourceManager.cpp"*/,0x306,&UNK_02964a2c/*"m_IsInitialized is null."*/);
  }
  lVar1 = param_1 + 0x40;
  uVar3 = Framework::CMutex::IsInitialized() const(lVar1);
  if ((uVar3 & 1) == 0) {
    Framework::CMutex::Initialize()(lVar1);
  }
  Framework::CMutex::Lock()(lVar1);
  uVar2 = *(undefined4 *)(param_1 + 0x38);
  Framework::CMutex::Unlock()(lVar1);
  return uVar2;
}

// ==== Framework::CResourceManager::NumByUniqueBitFlag(unsigned int) const
// vaddr 0x1e96efc | ghidra 0x1f96efc | size 156 | symbol _ZNK9Framework16CResourceManager18NumByUniqueBitFlagEj | lib libSOA-3.7.0.so | 2026-10-04
int _ZNK9Framework16CResourceManager18NumByUniqueBitFlagEj(long param_1,uint param_2)

{
  uint *puVar1;
  long lVar2;
  ulong uVar3;
  long lVar4;
  int iVar5;
  
  if (*(char *)(param_1 + 0x27) == '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029659c3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResourceManager.cpp"*/,0x312,&UNK_02964a2c/*"m_IsInitialized is null."*/);
  }
  lVar2 = param_1 + 0x40;
  uVar3 = Framework::CMutex::IsInitialized() const(lVar2);
  if ((uVar3 & 1) == 0) {
    Framework::CMutex::Initialize()(lVar2);
  }
  Framework::CMutex::Lock()(lVar2);
  lVar4 = *(long *)(param_1 + 0x30);
  if (param_1 + 0x28 == lVar4) {
    iVar5 = 0;
  }
  else {
    iVar5 = 0;
    do {
      puVar1 = (uint *)(lVar4 + 0x14);
      lVar4 = *(long *)(lVar4 + 8);
      if ((*puVar1 & param_2) != 0) {
        iVar5 = iVar5 + 1;
      }
    } while (param_1 + 0x28 != lVar4);
  }
  Framework::CMutex::Unlock()(lVar2);
  return iVar5;
}

// ==== Framework::CResourceManager::tElement::PrintS(unsigned int) const
// vaddr 0x1e96f98 | ghidra 0x1f96f98 | size 4 | symbol _ZNK9Framework16CResourceManager8tElement6PrintSEj | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK9Framework16CResourceManager8tElement6PrintSEj(void)

{
  return;
}

// ==== Framework::CResourceManager::PrintS(char const*)
// vaddr 0x1e96f9c | ghidra 0x1f96f9c | size 116 | symbol _ZN9Framework16CResourceManager6PrintSEPKc | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework16CResourceManager6PrintSEPKc(long param_1)

{
  long lVar1;
  ulong uVar2;
  long lVar3;
  long *plVar4;
  
  if (*(char *)(param_1 + 0x27) == '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029659c3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResourceManager.cpp"*/,0x331,&UNK_02964a2c/*"m_IsInitialized is null."*/);
  }
  lVar1 = param_1 + 0x40;
  uVar2 = Framework::CMutex::IsInitialized() const(lVar1);
  if ((uVar2 & 1) == 0) {
    Framework::CMutex::Initialize()(lVar1);
  }
  Framework::CMutex::Lock()(lVar1);
  plVar4 = (long *)(param_1 + 0x30);
  do {
    lVar3 = *plVar4;
    plVar4 = (long *)(lVar3 + 8);
  } while (lVar3 != param_1 + 0x28);
  (*(code *)PTR__ZN9Framework6CMutex6UnlockEv_02cb3f98)(lVar1);
  return;
}

// ==== Framework::CResourceManager::GetClassID(int) const
// vaddr 0x1e97010 | ghidra 0x1f97010 | size 64 | symbol _ZNK9Framework16CResourceManager10GetClassIDEi | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK9Framework16CResourceManager10GetClassIDEi(undefined8 param_1,int param_2)

{
  undefined8 uVar1;
  undefined8 uVar2;
  
  if (param_2 != 0) {
    uVar2 = 0xf000f001;
    if (param_2 != 2) {
      uVar2 = 0xf000;
    }
    uVar1 = 0xf000f001f002;
    if (param_2 != 1) {
      uVar1 = uVar2;
    }
    return uVar1;
  }
  return 0xf0021005;
}

// ==== Framework::CResourceManager::GetDefaultLevel() const
// vaddr 0x1e97050 | ghidra 0x1f97050 | size 8 | symbol _ZNK9Framework16CResourceManager15GetDefaultLevelEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK9Framework16CResourceManager15GetDefaultLevelEv(void)

{
  return 0x40;
}


// FAILED to create function at 02965670 typeinfo name for Framework::CResourceElement::CFinishNotify
// FAILED to create function at 02ba9590 Framework::CResourceElement::vtable
// FAILED to create function at 02ba9820 Framework::CResourceElement::typeinfo
// FAILED to create function at 02ba9858 Framework::CResourceElement::CFinishNotify::vtable
// FAILED to create function at 02ba9880 Framework::CResourceElement::CFinishNotify::typeinfo
// FAILED to create function at 02baad88 Framework::CResourceManager::vtable
// FAILED to create function at 02baae30 Framework::CResourceManager::typeinfo
// FAILED to create function at 02d00500 Framework::CResourceElement::m_ArchiveTypes
