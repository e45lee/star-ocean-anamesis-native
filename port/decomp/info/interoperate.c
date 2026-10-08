// port/decomp/info/interoperate.c: Ghidra decompiles for the info subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-08 15:06 UTC: tools/decomp.sh '--into' 'info/interoperate' 'Framework::CInteroperateParameter::'

// ==== Framework::CInteroperateParameter::InitializeDefaultKey(char const*, unsigned long)
// vaddr 0x1e86104 | ghidra 0x1f86104 | size 276 | symbol _ZN9Framework22CInteroperateParameter20InitializeDefaultKeyEPKcm | lib libSOA-3.7.0.so | 2026-10-08
void _ZN9Framework22CInteroperateParameter20InitializeDefaultKeyEPKcm(long param_1,ulong param_2)

{
  undefined *puVar1;
  long lVar2;
  bool bVar3;
  undefined8 *puVar4;
  ulong uVar5;
  long lVar6;
  long *plVar7;
  ulong uVar8;
  long lVar9;
  
  if (param_1 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964324/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\InteroperateParameter.cpp"*/,0x1e,&UNK_02964385/*"apDefaultKeyWord is null."*/);
  }
  if (param_2 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964324/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\InteroperateParameter.cpp"*/,0x1f,&UNK_0296439f/*"aNumInitialDefaultKey is null."*/);
  }
  puVar1 = PTR__ZN9Framework22CInteroperateParameter13m_pDefaultKeyE_02cb6e20;
  plVar7 = *(long **)PTR__ZN9Framework22CInteroperateParameter13m_pDefaultKeyE_02cb6e20;
  *(long *)PTR__ZN9Framework22CInteroperateParameter17m_pDefaultKeyWordE_02cbab98 = param_1;
  if (plVar7 != (long *)0x0) {
    lVar9 = *plVar7;
    if (lVar9 != 0) {
      lVar6 = plVar7[1];
      if (lVar6 != lVar9) {
        do {
          plVar7[1] = lVar6 + -0x18;
          lVar2 = lVar6 + -0x18;
          if ((*(byte *)(lVar6 + -0x18) & 1) != 0) {
            Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(*(undefined8 *)(lVar6 + -8));
            lVar2 = plVar7[1];
          }
          lVar6 = lVar2;
        } while (lVar6 != lVar9);
        lVar9 = *plVar7;
      }
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(lVar9);
    }
    operator delete(void*)(plVar7);
    *(undefined8 *)puVar1 = 0;
  }
  puVar4 = (undefined8 *)operator new(unsigned long, std::nothrow_t const&)(0x18,PTR__ZSt7nothrow_02cb9a80);
  if (puVar4 != (undefined8 *)0x0) {
    puVar4[1] = 0;
    puVar4[2] = 0;
    *puVar4 = 0;
  }
  *(undefined8 **)puVar1 = puVar4;
  if (param_2 != 0) {
    uVar5 = 0;
    uVar8 = 1;
    do {
      Framework::CInteroperateParameter::DefaultKey(unsigned long)(uVar5);
      bVar3 = uVar8 < param_2;
      uVar5 = uVar8;
      uVar8 = (ulong)((int)uVar8 + 1);
    } while (bVar3);
  }
  return;
}

// ==== Framework::CInteroperateParameter::ReleaseDefaultKey()
// vaddr 0x1e86218 | ghidra 0x1f86218 | size 120 | symbol _ZN9Framework22CInteroperateParameter17ReleaseDefaultKeyEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN9Framework22CInteroperateParameter17ReleaseDefaultKeyEv(void)

{
  undefined *puVar1;
  long lVar2;
  long lVar3;
  long *plVar4;
  long lVar5;
  
  puVar1 = PTR__ZN9Framework22CInteroperateParameter13m_pDefaultKeyE_02cb6e20;
  plVar4 = *(long **)PTR__ZN9Framework22CInteroperateParameter13m_pDefaultKeyE_02cb6e20;
  if (plVar4 != (long *)0x0) {
    lVar5 = *plVar4;
    if (lVar5 != 0) {
      lVar3 = plVar4[1];
      if (lVar3 != lVar5) {
        do {
          plVar4[1] = lVar3 + -0x18;
          lVar2 = lVar3 + -0x18;
          if ((*(byte *)(lVar3 + -0x18) & 1) != 0) {
            Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(*(undefined8 *)(lVar3 + -8));
            lVar2 = plVar4[1];
          }
          lVar3 = lVar2;
        } while (lVar3 != lVar5);
        lVar5 = *plVar4;
      }
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(lVar5);
    }
    operator delete(void*)(plVar4);
    *(undefined8 *)puVar1 = 0;
  }
  return;
}

// ==== Framework::CInteroperateParameter::DefaultKey(unsigned long)
// vaddr 0x1e86290 | ghidra 0x1f86290 | size 332 | symbol _ZN9Framework22CInteroperateParameter10DefaultKeyEm | lib libSOA-3.7.0.so | 2026-10-08
long _ZN9Framework22CInteroperateParameter10DefaultKeyEm(ulong param_1)

{
  ulong uVar1;
  long lVar2;
  undefined *puVar3;
  long lVar4;
  long extraout_x1;
  long lVar5;
  long lVar6;
  ulong uVar7;
  long *plVar8;
  byte *pbVar9;
  undefined8 uStack_48;
  undefined8 uStack_40;
  undefined8 uStack_38;
  
  if (*(long *)PTR__ZN9Framework22CInteroperateParameter17m_pDefaultKeyWordE_02cbab98 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964324/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\InteroperateParameter.cpp"*/,0x30,&UNK_029643be/*"m_pDefaultKeyWord is null."*/);
  }
  puVar3 = PTR__ZN9Framework22CInteroperateParameter13m_pDefaultKeyE_02cb6e20;
  plVar8 = *(long **)PTR__ZN9Framework22CInteroperateParameter13m_pDefaultKeyE_02cb6e20;
  lVar5 = *plVar8;
  lVar6 = plVar8[1] - lVar5 >> 3;
  uVar7 = lVar6 * -0x5555555555555555;
  if (param_1 <= uVar7) {
    uVar1 = param_1 + 1;
    lVar6 = uVar1 + lVar6 * 0x5555555555555555;
    if (uVar1 < uVar7 || lVar6 == 0) {
      if (uVar1 < uVar7) {
        lVar4 = plVar8[1];
        while (lVar2 = lVar4, lVar5 + uVar1 * 0x18 != lVar2) {
          plVar8[1] = lVar2 + -0x18;
          lVar4 = lVar2 + -0x18;
          if ((*(byte *)(lVar2 + -0x18) & 1) != 0) {
            Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(*(undefined8 *)(lVar2 + -8),lVar6);
            lVar4 = plVar8[1];
            lVar6 = extraout_x1;
          }
        }
      }
    }
    else {
      std::__ndk1::vector<string, Framework::CSTLAllocator<string, Framework::CSTLVectorAllocatorInf> >::__append(unsigned long)(plVar8);
    }
    Framework::CSTLStringUtility_Base<string >::Format(char const*, ...)(&uStack_48,&UNK_029643d9/*"rw%d"*/,param_1);
    lVar5 = **(long **)puVar3;
    pbVar9 = (byte *)(lVar5 + param_1 * 0x18);
    if ((*pbVar9 & 1) == 0) {
      pbVar9[0] = 0;
      pbVar9[1] = 0;
    }
    else {
      lVar5 = lVar5 + param_1 * 0x18;
      **(undefined1 **)(lVar5 + 0x10) = 0;
      *(undefined8 *)(lVar5 + 8) = 0;
    }
    string::reserve(unsigned long)(pbVar9,0);
    *(undefined8 *)(pbVar9 + 0x10) = uStack_38;
    *(undefined8 *)(pbVar9 + 8) = uStack_40;
    *(undefined8 *)pbVar9 = uStack_48;
    plVar8 = *(long **)puVar3;
  }
  return *plVar8 + param_1 * 0x18;
}

// ==== Framework::CInteroperateParameter::CInteroperateParameter()
// vaddr 0x1e863dc | ghidra 0x1f863dc | size 28 | symbol _ZN9Framework22CInteroperateParameterC2Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN9Framework22CInteroperateParameterC1Ev(long *param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZTVN9Framework22CInteroperateParameterE_02cc0e38;
  *(undefined4 *)((long)param_1 + 0x24) = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  *param_1 = (long)(puVar1 + 0x10);
  param_1[1] = 0;
  return;
}

// ==== Framework::CInteroperateParameter::~CInteroperateParameter()
// vaddr 0x1e863f8 | ghidra 0x1f863f8 | size 128 | symbol _ZN9Framework22CInteroperateParameterD1Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN9Framework22CInteroperateParameterD2Ev(long *param_1)

{
  long lVar1;
  
  *param_1 = (long)(PTR__ZTVN9Framework22CInteroperateParameterE_02cc0e38 + 0x10);
  if ((long *)param_1[1] != (long *)0x0) {
    (**(code **)(*(long *)param_1[1] + 8))();
    param_1[1] = 0;
  }
  lVar1 = param_1[2];
  if (lVar1 != 0) {
    std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, unsigned long>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, unsigned long>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, unsigned long>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, unsigned long>, void*>*)(lVar1,*(undefined8 *)(lVar1 + 8));
    operator delete(void*)(lVar1);
    param_1[2] = 0;
  }
  lVar1 = param_1[3];
  if (lVar1 != 0) {
    std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, unsigned long>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, unsigned long>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, unsigned long>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, unsigned long>, void*>*)(lVar1,*(undefined8 *)(lVar1 + 8));
    operator delete(void*)(lVar1);
    param_1[3] = 0;
  }
  return;
}

// ==== Framework::CInteroperateParameter::Release()
// vaddr 0x1e86478 | ghidra 0x1f86478 | size 112 | symbol _ZN9Framework22CInteroperateParameter7ReleaseEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN9Framework22CInteroperateParameter7ReleaseEv(long param_1)

{
  long lVar1;
  
  if (*(long **)(param_1 + 8) != (long *)0x0) {
    (**(code **)(**(long **)(param_1 + 8) + 8))();
    *(undefined8 *)(param_1 + 8) = 0;
  }
  lVar1 = *(long *)(param_1 + 0x10);
  if (lVar1 != 0) {
    std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, unsigned long>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, unsigned long>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, unsigned long>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, unsigned long>, void*>*)(lVar1,*(undefined8 *)(lVar1 + 8));
    operator delete(void*)(lVar1);
    *(undefined8 *)(param_1 + 0x10) = 0;
  }
  lVar1 = *(long *)(param_1 + 0x18);
  if (lVar1 != 0) {
    std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, unsigned long>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, unsigned long>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, unsigned long>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, unsigned long>, void*>*)(lVar1,*(undefined8 *)(lVar1 + 8));
    operator delete(void*)(lVar1);
    *(undefined8 *)(param_1 + 0x18) = 0;
  }
  return;
}

// ==== Framework::CInteroperateParameter::~CInteroperateParameter()
// vaddr 0x1e864e8 | ghidra 0x1f864e8 | size 128 | symbol _ZN9Framework22CInteroperateParameterD0Ev | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Possible PIC construction at 0x01f86534: Changing call to branch */
/* WARNING: Possible PIC construction at 0x01f86554: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0x01f86538) */

void _ZN9Framework22CInteroperateParameterD0Ev(long *param_1)

{
  long *plVar1;
  
  *param_1 = (long)(PTR__ZTVN9Framework22CInteroperateParameterE_02cc0e38 + 0x10);
  if ((long *)param_1[1] != (long *)0x0) {
    (**(code **)(*(long *)param_1[1] + 8))();
    param_1[1] = 0;
  }
  plVar1 = (long *)param_1[2];
  if (plVar1 == (long *)0x0) {
    plVar1 = (long *)param_1[3];
    if (plVar1 != (long *)0x0) {
      std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, unsigned long>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, unsigned long>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, unsigned long>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, unsigned long>, void*>*)(plVar1,plVar1[1]);
      param_1 = plVar1;
    }
  }
  else {
    std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, unsigned long>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, unsigned long>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, unsigned long>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, unsigned long>, void*>*)(plVar1,plVar1[1]);
    param_1 = plVar1;
  }
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Framework::CInteroperateParameter::Initialize(char const*, unsigned int, Framework::CInteroperateParameter::ICSVAccessor*)
// vaddr 0x1e86568 | ghidra 0x1f86568 | size 212 | symbol _ZN9Framework22CInteroperateParameter10InitializeEPKcjPNS0_12ICSVAccessorE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN9Framework22CInteroperateParameter10InitializeEPKcjPNS0_12ICSVAccessorE
               (long param_1,undefined8 param_2,undefined4 param_3,long *param_4)

{
  if (*(long *)(param_1 + 8) != 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964324/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\InteroperateParameter.cpp"*/,0x53,&UNK_02868190/*"m_pCSV isn't null.(%08x)"*/);
  }
  if (*(long *)(param_1 + 0x10) != 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964324/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\InteroperateParameter.cpp"*/,0x54,&UNK_029643de/*"m_pRowHash isn't null.(%08x)"*/);
  }
  *(undefined4 *)(param_1 + 0x24) = param_3;
  *(long **)(param_1 + 8) = param_4;
  if (param_4 == (long *)0x0) {
    param_4 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x108,PTR__ZSt7nothrow_02cb9a80);
    if (param_4 != (long *)0x0) {
      *param_4 = (long)(
                       PTR__ZTVN9Framework22CInteroperateParameter12TCSVAccessorINS_5CACSVEEE_02cb8080
                       + 0x10);
      Framework::CACSV::CACSV()(param_4 + 1);
    }
    *(long **)(param_1 + 8) = param_4;
  }
  (**(code **)(*param_4 + 0x10))(param_4);
  (**(code **)(**(long **)(param_1 + 8) + 0x18))(*(long **)(param_1 + 8),param_2);
  (*(code *)PTR__ZN9Framework22CInteroperateParameter16InitializeCommonEv_02ca50c0)(param_1);
  return;
}

// ==== Framework::CInteroperateParameter::InitializeCommon()
// vaddr 0x1e8663c | ghidra 0x1f8663c | size 976 | symbol _ZN9Framework22CInteroperateParameter16InitializeCommonEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN9Framework22CInteroperateParameter16InitializeCommonEv(long param_1)

{
  bool bVar1;
  ulong uVar2;
  byte bVar3;
  undefined *puVar4;
  int iVar5;
  undefined4 uVar6;
  ulong uVar7;
  undefined8 uVar8;
  undefined8 *puVar9;
  ulong uVar10;
  ulong uVar11;
  byte *pbVar12;
  ulong extraout_x1;
  ulong extraout_x1_00;
  ulong uVar13;
  ulong uVar14;
  undefined4 auStack_88 [2];
  ulong uStack_80;
  byte abStack_78 [8];
  ulong uStack_70;
  ulong uStack_68;
  
  uVar7 = (**(code **)(**(long **)(param_1 + 8) + 0x28))();
  if (0xfffffffe < uVar7) {
    uVar8 = (**(code **)(**(long **)(param_1 + 8) + 0x28))();
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964324/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\InteroperateParameter.cpp"*/,0x7d,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,uVar8,0xffffffff);
  }
  uVar7 = (**(code **)(**(long **)(param_1 + 8) + 0x38))();
  if (0xfffffffe < uVar7) {
    uVar8 = (**(code **)(**(long **)(param_1 + 8) + 0x38))();
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964324/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\InteroperateParameter.cpp"*/,0x7e,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,uVar8,0xffffffff);
  }
  uVar7 = (**(code **)(**(long **)(param_1 + 8) + 0x28))();
  puVar9 = (undefined8 *)operator new(unsigned long, std::nothrow_t const&)(0x18,PTR__ZSt7nothrow_02cb9a80);
  if (puVar9 != (undefined8 *)0x0) {
    puVar9[2] = 0;
    puVar9[1] = 0;
    *puVar9 = puVar9 + 1;
  }
  *(undefined8 **)(param_1 + 0x10) = puVar9;
  puVar4 = PTR__ZN9Framework22CInteroperateParameter17m_pDefaultKeyWordE_02cbab98;
  if (uVar7 != 0) {
    uVar13 = 0;
    uVar14 = 1;
    do {
      uVar10 = (**(code **)(**(long **)(param_1 + 8) + 0x50))(*(long **)(param_1 + 8),uVar13,0);
      if ((uVar10 & 1) == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964324/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\InteroperateParameter.cpp"*/,0x102,&UNK_029643fb/*"Top of CSV element in a rom isn't string."*/);
      }
      (**(code **)(**(long **)(param_1 + 8) + 0x68))(abStack_78,*(long **)(param_1 + 8),uVar13,0);
      uVar8 = *(undefined8 *)puVar4;
      uVar11 = strlen(uVar8);
      bVar3 = abStack_78[0];
      uVar10 = (ulong)(abStack_78[0] >> 1);
      if ((abStack_78[0] & 1) != 0) {
        uVar10 = uStack_70;
      }
      uVar2 = uVar11;
      if (uVar10 <= uVar11) {
        uVar2 = uVar10;
      }
      if (uVar2 == 0) {
        if (uVar10 == uVar11) goto code_r0x01f86818;
        pbVar12 = abStack_78;
        if ((abStack_78[0] & 1) != 0) goto code_r0x01f8683c;
code_r0x01f86808:
        pbVar12 = pbVar12 + 1;
      }
      else {
        uVar2 = (ulong)abStack_78 | 1;
        if ((abStack_78[0] & 1) != 0) {
          uVar2 = uStack_68;
        }
        iVar5 = memcmp(uVar2,uVar8);
        pbVar12 = abStack_78;
        if ((uVar10 == uVar11) && (iVar5 == 0)) {
code_r0x01f86818:
          pbVar12 = (byte *)(**(long **)
                               PTR__ZN9Framework22CInteroperateParameter13m_pDefaultKeyE_02cb6e20 +
                            uVar13 * 0x18);
          bVar3 = *pbVar12;
        }
        if ((bVar3 & 1) == 0) goto code_r0x01f86808;
code_r0x01f8683c:
        pbVar12 = *(byte **)(pbVar12 + 0x10);
      }
      Framework::CHash32::CHash32(char const*)(auStack_88,pbVar12);
      uVar6 = Framework::CHash32::Get() const(auStack_88);
      Framework::CHash32::~CHash32()(auStack_88);
      auStack_88[0] = uVar6;
      uStack_80 = uVar13;
      std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, unsigned long>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, unsigned long>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, unsigned long>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, unsigned long>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, unsigned long>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, std::__ndk1::pair<unsigned int const, unsigned long> >(unsigned int const&, std::__ndk1::pair<unsigned int const, unsigned long>&&)(*(undefined8 *)(param_1 + 0x10),auStack_88,auStack_88);
      if ((extraout_x1 & 1) == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964324/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\InteroperateParameter.cpp"*/,0x114,&UNK_02964425/*"Registering RowHash table failed"*/);
      }
      if ((abStack_78[0] & 1) != 0) {
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_68);
      }
      bVar1 = uVar14 < uVar7;
      uVar13 = uVar14;
      uVar14 = (ulong)((int)uVar14 + 1);
    } while (bVar1);
  }
  if ((*(byte *)(param_1 + 0x24) & 1) != 0) {
    uVar7 = (**(code **)(**(long **)(param_1 + 8) + 0x38))();
    if (*(long *)(param_1 + 0x18) != 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964324/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\InteroperateParameter.cpp"*/,0x119,&UNK_02964446/*"m_pColumnHash isn't null.(%08x)"*/);
    }
    puVar9 = (undefined8 *)operator new(unsigned long, std::nothrow_t const&)(0x18,PTR__ZSt7nothrow_02cb9a80);
    if (puVar9 != (undefined8 *)0x0) {
      puVar9[2] = 0;
      puVar9[1] = 0;
      *puVar9 = puVar9 + 1;
    }
    *(undefined8 **)(param_1 + 0x18) = puVar9;
    if (1 < uVar7) {
      uVar13 = 1;
      uVar14 = 2;
      do {
        uVar10 = (**(code **)(**(long **)(param_1 + 8) + 0x50))(*(long **)(param_1 + 8),0,uVar13);
        if ((uVar10 & 1) != 0) {
          (**(code **)(**(long **)(param_1 + 8) + 0x68))
                    (abStack_78,*(long **)(param_1 + 8),0,uVar13);
          uVar13 = (ulong)abStack_78 | 1;
          if ((abStack_78[0] & 1) != 0) {
            uVar13 = uStack_68;
          }
          Framework::CHash32::CHash32(char const*)(auStack_88,uVar13);
          uVar6 = Framework::CHash32::Get() const(auStack_88);
          Framework::CHash32::~CHash32()(auStack_88);
          uStack_80 = (ulong)((int)uVar14 - 2);
          auStack_88[0] = uVar6;
          std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, unsigned long>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, unsigned long>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, unsigned long>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, unsigned long>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, unsigned long>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, std::__ndk1::pair<unsigned int const, unsigned long> >(unsigned int const&, std::__ndk1::pair<unsigned int const, unsigned long>&&)(*(undefined8 *)(param_1 + 0x18),auStack_88,auStack_88);
          if ((extraout_x1_00 & 1) == 0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964324/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\InteroperateParameter.cpp"*/,0x122,&UNK_02964466/*"Registering ColumnHash table failed"*/);
          }
          if ((abStack_78[0] & 1) != 0) {
            Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_68);
          }
        }
        bVar1 = uVar14 < uVar7;
        uVar13 = uVar14;
        uVar14 = (ulong)((int)uVar14 + 1);
      } while (bVar1);
    }
  }
  return;
}

// ==== Framework::CInteroperateParameter::InitializeBinary(void const*, unsigned long, unsigned int, Framework::CInteroperateParameter::ICSVAccessor*)
// vaddr 0x1e86a0c | ghidra 0x1f86a0c | size 220 | symbol _ZN9Framework22CInteroperateParameter16InitializeBinaryEPKvmjPNS0_12ICSVAccessorE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN9Framework22CInteroperateParameter16InitializeBinaryEPKvmjPNS0_12ICSVAccessorE
               (long param_1,undefined8 param_2,undefined8 param_3,undefined4 param_4,long *param_5)

{
  if (*(long *)(param_1 + 8) != 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964324/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\InteroperateParameter.cpp"*/,0x68,&UNK_02868190/*"m_pCSV isn't null.(%08x)"*/);
  }
  if (*(long *)(param_1 + 0x10) != 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964324/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\InteroperateParameter.cpp"*/,0x69,&UNK_029643de/*"m_pRowHash isn't null.(%08x)"*/);
  }
  *(undefined4 *)(param_1 + 0x24) = param_4;
  *(long **)(param_1 + 8) = param_5;
  if (param_5 == (long *)0x0) {
    param_5 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x108,PTR__ZSt7nothrow_02cb9a80);
    if (param_5 != (long *)0x0) {
      *param_5 = (long)(
                       PTR__ZTVN9Framework22CInteroperateParameter12TCSVAccessorINS_5CACSVEEE_02cb8080
                       + 0x10);
      Framework::CACSV::CACSV()(param_5 + 1);
    }
    *(long **)(param_1 + 8) = param_5;
  }
  (**(code **)(*param_5 + 0x10))(param_5);
  (**(code **)(**(long **)(param_1 + 8) + 0x20))(*(long **)(param_1 + 8),param_2,param_3);
  (*(code *)PTR__ZN9Framework22CInteroperateParameter16InitializeCommonEv_02ca50c0)(param_1);
  return;
}

// ==== Framework::CInteroperateParameter::IsInitialized() const
// vaddr 0x1e86ae8 | ghidra 0x1f86ae8 | size 16 | symbol _ZNK9Framework22CInteroperateParameter13IsInitializedEv | lib libSOA-3.7.0.so | 2026-10-08
bool _ZNK9Framework22CInteroperateParameter13IsInitializedEv(long param_1)

{
  return *(long *)(param_1 + 8) != 0;
}

// ==== Framework::CInteroperateParameter::NumRows() const
// vaddr 0x1e86af8 | ghidra 0x1f86af8 | size 60 | symbol _ZNK9Framework22CInteroperateParameter7NumRowsEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZNK9Framework22CInteroperateParameter7NumRowsEv(long param_1)

{
  long *plVar1;
  
  plVar1 = *(long **)(param_1 + 8);
  if (plVar1 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964324/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\InteroperateParameter.cpp"*/,0x13f,&UNK_0296448a/*"m_pCSV is null."*/);
    plVar1 = *(long **)(param_1 + 8);
  }
                    /* WARNING: Could not recover jumptable at 0x01f86b30. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*plVar1 + 0x28))();
  return;
}

// ==== Framework::CInteroperateParameter::NumColumns() const
// vaddr 0x1e86b34 | ghidra 0x1f86b34 | size 76 | symbol _ZNK9Framework22CInteroperateParameter10NumColumnsEv | lib libSOA-3.7.0.so | 2026-10-08
long _ZNK9Framework22CInteroperateParameter10NumColumnsEv(long param_1)

{
  long *plVar1;
  long lVar2;
  long lVar3;
  
  plVar1 = *(long **)(param_1 + 8);
  if (plVar1 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964324/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\InteroperateParameter.cpp"*/,0x146,&UNK_0296448a/*"m_pCSV is null."*/);
    plVar1 = *(long **)(param_1 + 8);
  }
  lVar2 = (**(code **)(*plVar1 + 0x38))();
  lVar3 = lVar2 + -1;
  if (lVar2 == 0) {
    lVar3 = 0;
  }
  return lVar3;
}

// ==== Framework::CInteroperateParameter::IsExist(char const*) const
// vaddr 0x1e86b80 | ghidra 0x1f86b80 | size 240 | symbol _ZNK9Framework22CInteroperateParameter7IsExistEPKc | lib libSOA-3.7.0.so | 2026-10-08
bool _ZNK9Framework22CInteroperateParameter7IsExistEPKc(long param_1,undefined8 param_2)

{
  long *plVar1;
  long *plVar2;
  uint uVar3;
  long *plVar4;
  long *plVar5;
  long lVar6;
  long *plVar7;
  undefined1 auStack_30 [16];
  
  if (*(long *)(param_1 + 8) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964324/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\InteroperateParameter.cpp"*/,0x14f,&UNK_0296448a/*"m_pCSV is null."*/);
    lVar6 = *(long *)(param_1 + 0x10);
  }
  else {
    lVar6 = *(long *)(param_1 + 0x10);
  }
  if (lVar6 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964324/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\InteroperateParameter.cpp"*/,0x150,&UNK_0296449a/*"m_pRowHash is null."*/);
    lVar6 = *(long *)(param_1 + 0x10);
  }
  Framework::CHash32::CHash32(char const*)(auStack_30,param_2);
  uVar3 = Framework::CHash32::Get() const(auStack_30);
  plVar7 = (long *)(lVar6 + 8);
  plVar2 = (long *)*plVar7;
  plVar4 = plVar7;
  if ((long *)*plVar7 != (long *)0x0) {
    do {
      while (plVar5 = plVar2, uVar3 <= *(uint *)(plVar5 + 4)) {
        plVar2 = (long *)*plVar5;
        plVar4 = plVar5;
        if ((long *)*plVar5 == (long *)0x0) goto code_r0x01f86bf4;
      }
      plVar1 = plVar5 + 1;
      plVar5 = plVar4;
      plVar2 = (long *)*plVar1;
    } while ((long *)*plVar1 != (long *)0x0);
code_r0x01f86bf4:
    if ((plVar5 != plVar7) && (*(uint *)(plVar5 + 4) <= uVar3)) goto code_r0x01f86c0c;
  }
  plVar5 = plVar7;
code_r0x01f86c0c:
  Framework::CHash32::~CHash32()(auStack_30);
  return plVar5 != plVar7;
}

// ==== Framework::CInteroperateParameter::IsExist(char const*, unsigned long) const
// vaddr 0x1e86c70 | ghidra 0x1f86c70 | size 332 | symbol _ZNK9Framework22CInteroperateParameter7IsExistEPKcm | lib libSOA-3.7.0.so | 2026-10-08
bool _ZNK9Framework22CInteroperateParameter7IsExistEPKcm
               (long param_1,undefined8 param_2,ulong param_3)

{
  long *plVar1;
  long *plVar2;
  bool bVar3;
  uint uVar4;
  long *plVar5;
  ulong uVar6;
  long *plVar7;
  long *plVar8;
  long lVar9;
  long *plVar10;
  undefined1 auStack_40 [16];
  
  if (*(long *)(param_1 + 8) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964324/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\InteroperateParameter.cpp"*/,0x158,&UNK_0296448a/*"m_pCSV is null."*/);
  }
  plVar8 = (long *)(param_1 + 0x10);
  lVar9 = *plVar8;
  if (lVar9 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964324/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\InteroperateParameter.cpp"*/,0x159,&UNK_0296449a/*"m_pRowHash is null."*/);
    lVar9 = *plVar8;
  }
  Framework::CHash32::CHash32(char const*)(auStack_40,param_2);
  uVar4 = Framework::CHash32::Get() const(auStack_40);
  plVar10 = (long *)(lVar9 + 8);
  plVar2 = (long *)*plVar10;
  plVar5 = plVar10;
  if ((long *)*plVar10 != (long *)0x0) {
    do {
      while (plVar7 = plVar2, uVar4 <= *(uint *)(plVar7 + 4)) {
        plVar2 = (long *)*plVar7;
        plVar5 = plVar7;
        if ((long *)*plVar7 == (long *)0x0) goto code_r0x01f86d24;
      }
      plVar1 = plVar7 + 1;
      plVar7 = plVar5;
      plVar2 = (long *)*plVar1;
    } while ((long *)*plVar1 != (long *)0x0);
code_r0x01f86d24:
    if ((plVar7 != plVar10) && (*(uint *)(plVar7 + 4) <= uVar4)) goto code_r0x01f86d3c;
  }
  plVar7 = plVar10;
code_r0x01f86d3c:
  Framework::CHash32::~CHash32()(auStack_40);
  if (plVar7 == (long *)(*plVar8 + 8)) {
    bVar3 = false;
  }
  else {
    plVar8 = *(long **)(param_1 + 8);
    lVar9 = plVar7[5];
    if (plVar8 == (long *)0x0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964324/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\InteroperateParameter.cpp"*/,0x16f,&UNK_0296448a/*"m_pCSV is null."*/);
      plVar8 = *(long **)(param_1 + 8);
    }
    lVar9 = (**(code **)(*plVar8 + 0x30))(plVar8,lVar9);
    uVar6 = lVar9 - 1;
    if (lVar9 == 0) {
      uVar6 = 0;
    }
    bVar3 = param_3 < uVar6;
  }
  return bVar3;
}

// ==== Framework::CInteroperateParameter::NumElements(unsigned long) const
// vaddr 0x1e86dbc | ghidra 0x1f86dbc | size 92 | symbol _ZNK9Framework22CInteroperateParameter11NumElementsEm | lib libSOA-3.7.0.so | 2026-10-08
long _ZNK9Framework22CInteroperateParameter11NumElementsEm(long param_1,undefined8 param_2)

{
  long *plVar1;
  long lVar2;
  long lVar3;
  
  plVar1 = *(long **)(param_1 + 8);
  if (plVar1 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964324/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\InteroperateParameter.cpp"*/,0x16f,&UNK_0296448a/*"m_pCSV is null."*/);
    plVar1 = *(long **)(param_1 + 8);
  }
  lVar2 = (**(code **)(*plVar1 + 0x30))(plVar1,param_2);
  lVar3 = lVar2 + -1;
  if (lVar2 == 0) {
    lVar3 = 0;
  }
  return lVar3;
}

// ==== Framework::CInteroperateParameter::NumElements(char const*) const
// vaddr 0x1e86e18 | ghidra 0x1f86e18 | size 320 | symbol _ZNK9Framework22CInteroperateParameter11NumElementsEPKc | lib libSOA-3.7.0.so | 2026-10-08
long _ZNK9Framework22CInteroperateParameter11NumElementsEPKc(long param_1,undefined8 param_2)

{
  long *plVar1;
  long *plVar2;
  uint uVar3;
  long lVar4;
  long *plVar5;
  long *plVar6;
  long *plVar7;
  long lVar8;
  long *plVar9;
  undefined1 auStack_40 [16];
  
  if (*(long *)(param_1 + 8) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964324/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\InteroperateParameter.cpp"*/,0x165,&UNK_0296448a/*"m_pCSV is null."*/);
  }
  plVar7 = (long *)(param_1 + 0x10);
  lVar8 = *plVar7;
  if (lVar8 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964324/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\InteroperateParameter.cpp"*/,0x166,&UNK_0296449a/*"m_pRowHash is null."*/);
    lVar8 = *plVar7;
  }
  Framework::CHash32::CHash32(char const*)(auStack_40,param_2);
  uVar3 = Framework::CHash32::Get() const(auStack_40);
  plVar9 = (long *)(lVar8 + 8);
  plVar2 = (long *)*plVar9;
  plVar5 = plVar9;
  if ((long *)*plVar9 != (long *)0x0) {
    do {
      while (plVar6 = plVar2, uVar3 <= *(uint *)(plVar6 + 4)) {
        plVar2 = (long *)*plVar6;
        plVar5 = plVar6;
        if ((long *)*plVar6 == (long *)0x0) goto code_r0x01f86ec8;
      }
      plVar1 = plVar6 + 1;
      plVar6 = plVar5;
      plVar2 = (long *)*plVar1;
    } while ((long *)*plVar1 != (long *)0x0);
code_r0x01f86ec8:
    if ((plVar6 != plVar9) && (*(uint *)(plVar6 + 4) <= uVar3)) goto code_r0x01f86ee0;
  }
  plVar6 = plVar9;
code_r0x01f86ee0:
  Framework::CHash32::~CHash32()(auStack_40);
  if (plVar6 == (long *)(*plVar7 + 8)) {
    lVar8 = 0;
  }
  else {
    plVar7 = *(long **)(param_1 + 8);
    lVar8 = plVar6[5];
    if (plVar7 == (long *)0x0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964324/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\InteroperateParameter.cpp"*/,0x16f,&UNK_0296448a/*"m_pCSV is null."*/);
      plVar7 = *(long **)(param_1 + 8);
    }
    lVar4 = (**(code **)(*plVar7 + 0x30))(plVar7,lVar8);
    lVar8 = lVar4 + -1;
    if (lVar4 == 0) {
      lVar8 = 0;
    }
  }
  return lVar8;
}

// ==== Framework::CInteroperateParameter::ToCsvRow(unsigned long) const
// vaddr 0x1e86f58 | ghidra 0x1f86f58 | size 8 | symbol _ZNK9Framework22CInteroperateParameter8ToCsvRowEm | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK9Framework22CInteroperateParameter8ToCsvRowEm(undefined8 param_1,undefined8 param_2)

{
  return param_2;
}

// ==== Framework::CInteroperateParameter::IsBlank(char const*, unsigned long) const
// vaddr 0x1e86f60 | ghidra 0x1f86f60 | size 44 | symbol _ZNK9Framework22CInteroperateParameter7IsBlankEPKcm | lib libSOA-3.7.0.so | 2026-10-08
void _ZNK9Framework22CInteroperateParameter7IsBlankEPKcm
               (undefined8 param_1,undefined8 param_2,undefined8 param_3)

{
  int iVar1;
  
  iVar1 = Framework::CInteroperateParameter::ConvertToRow(char const*) const();
  (*(code *)PTR__ZNK9Framework22CInteroperateParameter7IsBlankEmm_02c9f478)
            (param_1,(long)iVar1,param_3);
  return;
}

// ==== Framework::CInteroperateParameter::IsBlank(unsigned long, unsigned long) const
// vaddr 0x1e86f8c | ghidra 0x1f86f8c | size 260 | symbol _ZNK9Framework22CInteroperateParameter7IsBlankEmm | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZNK9Framework22CInteroperateParameter7IsBlankEmm(long param_1,ulong param_2,ulong param_3)

{
  long *plVar1;
  ulong uVar2;
  long lVar3;
  undefined8 uVar4;
  
  plVar1 = *(long **)(param_1 + 8);
  if (plVar1 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964324/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\InteroperateParameter.cpp"*/,0x1e3,&UNK_0296448a/*"m_pCSV is null."*/);
    plVar1 = *(long **)(param_1 + 8);
    if (plVar1 == (long *)0x0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964324/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\InteroperateParameter.cpp"*/,0x1dc,&UNK_0296448a/*"m_pCSV is null."*/);
      plVar1 = *(long **)(param_1 + 8);
      if (plVar1 == (long *)0x0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964324/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\InteroperateParameter.cpp"*/,0x13f,&UNK_0296448a/*"m_pCSV is null."*/);
        plVar1 = *(long **)(param_1 + 8);
      }
    }
  }
  uVar2 = (**(code **)(*plVar1 + 0x28))();
  if (param_2 < uVar2) {
    plVar1 = *(long **)(param_1 + 8);
    if (plVar1 == (long *)0x0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964324/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\InteroperateParameter.cpp"*/,0x16f,&UNK_0296448a/*"m_pCSV is null."*/);
      plVar1 = *(long **)(param_1 + 8);
    }
    lVar3 = (**(code **)(*plVar1 + 0x30))(plVar1,param_2);
    uVar2 = lVar3 - 1;
    if (lVar3 == 0) {
      uVar2 = 0;
    }
    if (param_3 < uVar2) {
                    /* WARNING: Could not recover jumptable at 0x01f8707c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      uVar4 = (**(code **)(**(long **)(param_1 + 8) + 0x40))
                        (*(long **)(param_1 + 8),param_2,param_3 + 1);
      return uVar4;
    }
  }
  return 1;
}

// ==== Framework::CInteroperateParameter::ConvertToRow(char const*) const
// vaddr 0x1e87090 | ghidra 0x1f87090 | size 256 | symbol _ZNK9Framework22CInteroperateParameter12ConvertToRowEPKc | lib libSOA-3.7.0.so | 2026-10-08
undefined4 _ZNK9Framework22CInteroperateParameter12ConvertToRowEPKc(long param_1,undefined8 param_2)

{
  long *plVar1;
  long *plVar2;
  uint uVar3;
  undefined4 uVar4;
  long *plVar5;
  long *plVar6;
  long lVar7;
  long *plVar8;
  undefined1 auStack_30 [16];
  
  if (*(long *)(param_1 + 8) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964324/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\InteroperateParameter.cpp"*/,0x214,&UNK_0296448a/*"m_pCSV is null."*/);
    lVar7 = *(long *)(param_1 + 0x10);
  }
  else {
    lVar7 = *(long *)(param_1 + 0x10);
  }
  if (lVar7 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964324/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\InteroperateParameter.cpp"*/,0x215,&UNK_0296449a/*"m_pRowHash is null."*/);
    lVar7 = *(long *)(param_1 + 0x10);
  }
  Framework::CHash32::CHash32(char const*)(auStack_30,param_2);
  uVar3 = Framework::CHash32::Get() const(auStack_30);
  plVar8 = (long *)(lVar7 + 8);
  plVar2 = (long *)*plVar8;
  plVar5 = plVar8;
  if ((long *)*plVar8 != (long *)0x0) {
    do {
      while (plVar6 = plVar2, uVar3 <= *(uint *)(plVar6 + 4)) {
        plVar2 = (long *)*plVar6;
        plVar5 = plVar6;
        if ((long *)*plVar6 == (long *)0x0) goto code_r0x01f87104;
      }
      plVar1 = plVar6 + 1;
      plVar6 = plVar5;
      plVar2 = (long *)*plVar1;
    } while ((long *)*plVar1 != (long *)0x0);
code_r0x01f87104:
    if ((plVar6 != plVar8) && (*(uint *)(plVar6 + 4) <= uVar3)) goto code_r0x01f8711c;
  }
  plVar6 = plVar8;
code_r0x01f8711c:
  Framework::CHash32::~CHash32()(auStack_30);
  if (plVar6 == (long *)(*(long *)(param_1 + 0x10) + 8)) {
    uVar4 = 0xffffffff;
  }
  else {
    uVar4 = (undefined4)plVar6[5];
  }
  return uVar4;
}

// ==== Framework::CInteroperateParameter::IsBlank(char const*, char const*) const
// vaddr 0x1e87190 | ghidra 0x1f87190 | size 60 | symbol _ZNK9Framework22CInteroperateParameter7IsBlankEPKcS2_ | lib libSOA-3.7.0.so | 2026-10-08
void _ZNK9Framework22CInteroperateParameter7IsBlankEPKcS2_
               (undefined8 param_1,undefined8 param_2,undefined8 param_3)

{
  int iVar1;
  int iVar2;
  
  iVar1 = Framework::CInteroperateParameter::ConvertToRow(char const*) const();
  iVar2 = Framework::CInteroperateParameter::ConvertToColumn(char const*) const(param_1,param_3);
  (*(code *)PTR__ZNK9Framework22CInteroperateParameter7IsBlankEmm_02c9f478)
            (param_1,(long)iVar1,(long)iVar2);
  return;
}

// ==== Framework::CInteroperateParameter::ConvertToColumn(char const*) const
// vaddr 0x1e871cc | ghidra 0x1f871cc | size 256 | symbol _ZNK9Framework22CInteroperateParameter15ConvertToColumnEPKc | lib libSOA-3.7.0.so | 2026-10-08
undefined4
_ZNK9Framework22CInteroperateParameter15ConvertToColumnEPKc(long param_1,undefined8 param_2)

{
  long *plVar1;
  long *plVar2;
  uint uVar3;
  undefined4 uVar4;
  long *plVar5;
  long *plVar6;
  long lVar7;
  long *plVar8;
  undefined1 auStack_30 [16];
  
  if (*(long *)(param_1 + 8) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964324/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\InteroperateParameter.cpp"*/,0x221,&UNK_0296448a/*"m_pCSV is null."*/);
    lVar7 = *(long *)(param_1 + 0x18);
  }
  else {
    lVar7 = *(long *)(param_1 + 0x18);
  }
  if (lVar7 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964324/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\InteroperateParameter.cpp"*/,0x222,&UNK_029644ae/*"m_pColumnHash is null."*/);
    lVar7 = *(long *)(param_1 + 0x18);
  }
  Framework::CHash32::CHash32(char const*)(auStack_30,param_2);
  uVar3 = Framework::CHash32::Get() const(auStack_30);
  plVar8 = (long *)(lVar7 + 8);
  plVar2 = (long *)*plVar8;
  plVar5 = plVar8;
  if ((long *)*plVar8 != (long *)0x0) {
    do {
      while (plVar6 = plVar2, uVar3 <= *(uint *)(plVar6 + 4)) {
        plVar2 = (long *)*plVar6;
        plVar5 = plVar6;
        if ((long *)*plVar6 == (long *)0x0) goto code_r0x01f87240;
      }
      plVar1 = plVar6 + 1;
      plVar6 = plVar5;
      plVar2 = (long *)*plVar1;
    } while ((long *)*plVar1 != (long *)0x0);
code_r0x01f87240:
    if ((plVar6 != plVar8) && (*(uint *)(plVar6 + 4) <= uVar3)) goto code_r0x01f87258;
  }
  plVar6 = plVar8;
code_r0x01f87258:
  Framework::CHash32::~CHash32()(auStack_30);
  if (plVar6 == (long *)(*(long *)(param_1 + 0x18) + 8)) {
    uVar4 = 0xffffffff;
  }
  else {
    uVar4 = (undefined4)plVar6[5];
  }
  return uVar4;
}

// ==== Framework::CInteroperateParameter::IsValue(char const*, unsigned long) const
// vaddr 0x1e872cc | ghidra 0x1f872cc | size 92 | symbol _ZNK9Framework22CInteroperateParameter7IsValueEPKcm | lib libSOA-3.7.0.so | 2026-10-08
void _ZNK9Framework22CInteroperateParameter7IsValueEPKcm
               (long param_1,undefined8 param_2,long param_3)

{
  int iVar1;
  long *plVar2;
  
  iVar1 = Framework::CInteroperateParameter::ConvertToRow(char const*) const();
  plVar2 = *(long **)(param_1 + 8);
  if (plVar2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964324/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\InteroperateParameter.cpp"*/,0x1fb,&UNK_0296448a/*"m_pCSV is null."*/);
    plVar2 = *(long **)(param_1 + 8);
  }
                    /* WARNING: Could not recover jumptable at 0x01f87324. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*plVar2 + 0x48))(plVar2,(long)iVar1,param_3 + 1);
  return;
}

// ==== Framework::CInteroperateParameter::IsValue(unsigned long, unsigned long) const
// vaddr 0x1e87328 | ghidra 0x1f87328 | size 84 | symbol _ZNK9Framework22CInteroperateParameter7IsValueEmm | lib libSOA-3.7.0.so | 2026-10-08
void _ZNK9Framework22CInteroperateParameter7IsValueEmm(long param_1,undefined8 param_2,long param_3)

{
  long *plVar1;
  
  plVar1 = *(long **)(param_1 + 8);
  if (plVar1 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964324/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\InteroperateParameter.cpp"*/,0x1fb,&UNK_0296448a/*"m_pCSV is null."*/);
    plVar1 = *(long **)(param_1 + 8);
  }
                    /* WARNING: Could not recover jumptable at 0x01f87378. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*plVar1 + 0x48))(plVar1,param_2,param_3 + 1);
  return;
}

// ==== Framework::CInteroperateParameter::IsValue(char const*, char const*) const
// vaddr 0x1e8737c | ghidra 0x1f8737c | size 108 | symbol _ZNK9Framework22CInteroperateParameter7IsValueEPKcS2_ | lib libSOA-3.7.0.so | 2026-10-08
void _ZNK9Framework22CInteroperateParameter7IsValueEPKcS2_
               (long param_1,undefined8 param_2,undefined8 param_3)

{
  int iVar1;
  int iVar2;
  long *plVar3;
  
  iVar1 = Framework::CInteroperateParameter::ConvertToRow(char const*) const();
  iVar2 = Framework::CInteroperateParameter::ConvertToColumn(char const*) const(param_1,param_3);
  plVar3 = *(long **)(param_1 + 8);
  if (plVar3 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964324/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\InteroperateParameter.cpp"*/,0x1fb,&UNK_0296448a/*"m_pCSV is null."*/);
    plVar3 = *(long **)(param_1 + 8);
  }
                    /* WARNING: Could not recover jumptable at 0x01f873e4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*plVar3 + 0x48))(plVar3,(long)iVar1,(long)iVar2 + 1);
  return;
}

// ==== Framework::CInteroperateParameter::IsString(char const*, unsigned long) const
// vaddr 0x1e873e8 | ghidra 0x1f873e8 | size 92 | symbol _ZNK9Framework22CInteroperateParameter8IsStringEPKcm | lib libSOA-3.7.0.so | 2026-10-08
void _ZNK9Framework22CInteroperateParameter8IsStringEPKcm
               (long param_1,undefined8 param_2,long param_3)

{
  int iVar1;
  long *plVar2;
  
  iVar1 = Framework::CInteroperateParameter::ConvertToRow(char const*) const();
  plVar2 = *(long **)(param_1 + 8);
  if (plVar2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964324/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\InteroperateParameter.cpp"*/,0x201,&UNK_0296448a/*"m_pCSV is null."*/);
    plVar2 = *(long **)(param_1 + 8);
  }
                    /* WARNING: Could not recover jumptable at 0x01f87440. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*plVar2 + 0x50))(plVar2,(long)iVar1,param_3 + 1);
  return;
}

// ==== Framework::CInteroperateParameter::IsString(unsigned long, unsigned long) const
// vaddr 0x1e87444 | ghidra 0x1f87444 | size 84 | symbol _ZNK9Framework22CInteroperateParameter8IsStringEmm | lib libSOA-3.7.0.so | 2026-10-08
void _ZNK9Framework22CInteroperateParameter8IsStringEmm
               (long param_1,undefined8 param_2,long param_3)

{
  long *plVar1;
  
  plVar1 = *(long **)(param_1 + 8);
  if (plVar1 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964324/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\InteroperateParameter.cpp"*/,0x201,&UNK_0296448a/*"m_pCSV is null."*/);
    plVar1 = *(long **)(param_1 + 8);
  }
                    /* WARNING: Could not recover jumptable at 0x01f87494. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*plVar1 + 0x50))(plVar1,param_2,param_3 + 1);
  return;
}

// ==== Framework::CInteroperateParameter::IsString(char const*, char const*) const
// vaddr 0x1e87498 | ghidra 0x1f87498 | size 108 | symbol _ZNK9Framework22CInteroperateParameter8IsStringEPKcS2_ | lib libSOA-3.7.0.so | 2026-10-08
void _ZNK9Framework22CInteroperateParameter8IsStringEPKcS2_
               (long param_1,undefined8 param_2,undefined8 param_3)

{
  int iVar1;
  int iVar2;
  long *plVar3;
  
  iVar1 = Framework::CInteroperateParameter::ConvertToRow(char const*) const();
  iVar2 = Framework::CInteroperateParameter::ConvertToColumn(char const*) const(param_1,param_3);
  plVar3 = *(long **)(param_1 + 8);
  if (plVar3 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964324/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\InteroperateParameter.cpp"*/,0x201,&UNK_0296448a/*"m_pCSV is null."*/);
    plVar3 = *(long **)(param_1 + 8);
  }
                    /* WARNING: Could not recover jumptable at 0x01f87500. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*plVar3 + 0x50))(plVar3,(long)iVar1,(long)iVar2 + 1);
  return;
}

// ==== Framework::CInteroperateParameter::Value(char const*, unsigned long) const
// vaddr 0x1e87504 | ghidra 0x1f87504 | size 92 | symbol _ZNK9Framework22CInteroperateParameter5ValueEPKcm | lib libSOA-3.7.0.so | 2026-10-08
void _ZNK9Framework22CInteroperateParameter5ValueEPKcm(long param_1,undefined8 param_2,long param_3)

{
  int iVar1;
  long *plVar2;
  
  iVar1 = Framework::CInteroperateParameter::ConvertToRow(char const*) const();
  plVar2 = *(long **)(param_1 + 8);
  if (plVar2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964324/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\InteroperateParameter.cpp"*/,0x207,&UNK_0296448a/*"m_pCSV is null."*/);
    plVar2 = *(long **)(param_1 + 8);
  }
                    /* WARNING: Could not recover jumptable at 0x01f8755c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*plVar2 + 0x58))(plVar2,(long)iVar1,param_3 + 1);
  return;
}

// ==== Framework::CInteroperateParameter::Value(unsigned long, unsigned long) const
// vaddr 0x1e87560 | ghidra 0x1f87560 | size 84 | symbol _ZNK9Framework22CInteroperateParameter5ValueEmm | lib libSOA-3.7.0.so | 2026-10-08
void _ZNK9Framework22CInteroperateParameter5ValueEmm(long param_1,undefined8 param_2,long param_3)

{
  long *plVar1;
  
  plVar1 = *(long **)(param_1 + 8);
  if (plVar1 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964324/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\InteroperateParameter.cpp"*/,0x207,&UNK_0296448a/*"m_pCSV is null."*/);
    plVar1 = *(long **)(param_1 + 8);
  }
                    /* WARNING: Could not recover jumptable at 0x01f875b0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*plVar1 + 0x58))(plVar1,param_2,param_3 + 1);
  return;
}

// ==== Framework::CInteroperateParameter::Value(char const*, char const*) const
// vaddr 0x1e875b4 | ghidra 0x1f875b4 | size 108 | symbol _ZNK9Framework22CInteroperateParameter5ValueEPKcS2_ | lib libSOA-3.7.0.so | 2026-10-08
void _ZNK9Framework22CInteroperateParameter5ValueEPKcS2_
               (long param_1,undefined8 param_2,undefined8 param_3)

{
  int iVar1;
  int iVar2;
  long *plVar3;
  
  iVar1 = Framework::CInteroperateParameter::ConvertToRow(char const*) const();
  iVar2 = Framework::CInteroperateParameter::ConvertToColumn(char const*) const(param_1,param_3);
  plVar3 = *(long **)(param_1 + 8);
  if (plVar3 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964324/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\InteroperateParameter.cpp"*/,0x207,&UNK_0296448a/*"m_pCSV is null."*/);
    plVar3 = *(long **)(param_1 + 8);
  }
                    /* WARNING: Could not recover jumptable at 0x01f8761c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*plVar3 + 0x58))(plVar3,(long)iVar1,(long)iVar2 + 1);
  return;
}

// ==== Framework::CInteroperateParameter::String(char const*, unsigned long) const
// vaddr 0x1e87620 | ghidra 0x1f87620 | size 108 | symbol _ZNK9Framework22CInteroperateParameter6StringEPKcm | lib libSOA-3.7.0.so | 2026-10-08
void _ZNK9Framework22CInteroperateParameter6StringEPKcm
               (undefined8 param_1,long param_2,undefined8 param_3,long param_4)

{
  int iVar1;
  long *plVar2;
  
  iVar1 = Framework::CInteroperateParameter::ConvertToRow(char const*) const();
  plVar2 = *(long **)(param_2 + 8);
  if (plVar2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964324/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\InteroperateParameter.cpp"*/,0x20d,&UNK_0296448a/*"m_pCSV is null."*/);
    plVar2 = *(long **)(param_2 + 8);
  }
                    /* WARNING: Could not recover jumptable at 0x01f87688. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*plVar2 + 0x68))(param_1,plVar2,(long)iVar1,param_4 + 1);
  return;
}

// ==== Framework::CInteroperateParameter::String(unsigned long, unsigned long) const
// vaddr 0x1e8768c | ghidra 0x1f8768c | size 100 | symbol _ZNK9Framework22CInteroperateParameter6StringEmm | lib libSOA-3.7.0.so | 2026-10-08
void _ZNK9Framework22CInteroperateParameter6StringEmm
               (undefined8 param_1,long param_2,undefined8 param_3,long param_4)

{
  long *plVar1;
  
  plVar1 = *(long **)(param_2 + 8);
  if (plVar1 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964324/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\InteroperateParameter.cpp"*/,0x20d,&UNK_0296448a/*"m_pCSV is null."*/);
    plVar1 = *(long **)(param_2 + 8);
  }
                    /* WARNING: Could not recover jumptable at 0x01f876ec. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*plVar1 + 0x68))(param_1,plVar1,param_3,param_4 + 1);
  return;
}

// ==== Framework::CInteroperateParameter::String(char const*, char const*) const
// vaddr 0x1e876f0 | ghidra 0x1f876f0 | size 124 | symbol _ZNK9Framework22CInteroperateParameter6StringEPKcS2_ | lib libSOA-3.7.0.so | 2026-10-08
void _ZNK9Framework22CInteroperateParameter6StringEPKcS2_
               (undefined8 param_1,long param_2,undefined8 param_3,undefined8 param_4)

{
  int iVar1;
  int iVar2;
  long *plVar3;
  
  iVar1 = Framework::CInteroperateParameter::ConvertToRow(char const*) const();
  iVar2 = Framework::CInteroperateParameter::ConvertToColumn(char const*) const(param_2,param_4);
  plVar3 = *(long **)(param_2 + 8);
  if (plVar3 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964324/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\InteroperateParameter.cpp"*/,0x20d,&UNK_0296448a/*"m_pCSV is null."*/);
    plVar3 = *(long **)(param_2 + 8);
  }
                    /* WARNING: Could not recover jumptable at 0x01f87768. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*plVar3 + 0x68))(param_1,plVar3,(long)iVar1,(long)iVar2 + 1);
  return;
}

// ==== Framework::CInteroperateParameter::ValueSafe(unsigned long, unsigned long, float) const
// vaddr 0x1e8776c | ghidra 0x1f8776c | size 180 | symbol _ZNK9Framework22CInteroperateParameter9ValueSafeEmmf | lib libSOA-3.7.0.so | 2026-10-08
undefined1  [16]
_ZNK9Framework22CInteroperateParameter9ValueSafeEmmf
          (undefined1 param_1 [16],long param_2,undefined8 param_3,long param_4)

{
  long *plVar1;
  ulong uVar2;
  undefined1 auVar3 [16];
  undefined8 uVar4;
  
  uVar4 = param_1._8_8_;
  auVar3._0_8_ = param_1._0_8_;
  plVar1 = *(long **)(param_2 + 8);
  if (plVar1 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964324/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\InteroperateParameter.cpp"*/,0x1fb,&UNK_0296448a/*"m_pCSV is null."*/);
    plVar1 = *(long **)(param_2 + 8);
  }
  uVar2 = (**(code **)(*plVar1 + 0x48))(plVar1,param_3,param_4 + 1);
  if ((uVar2 & 1) != 0) {
    plVar1 = *(long **)(param_2 + 8);
    if (plVar1 == (long *)0x0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964324/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\InteroperateParameter.cpp"*/,0x207,&UNK_0296448a/*"m_pCSV is null."*/);
      plVar1 = *(long **)(param_2 + 8);
    }
                    /* WARNING: Could not recover jumptable at 0x01f87808. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    auVar3 = (**(code **)(*plVar1 + 0x58))(plVar1,param_3,param_4 + 1);
    return auVar3;
  }
  auVar3._8_8_ = uVar4;
  return auVar3;
}

// ==== Framework::CInteroperateParameter::ValueSafe(char const*, unsigned long, float) const
// vaddr 0x1e87820 | ghidra 0x1f87820 | size 188 | symbol _ZNK9Framework22CInteroperateParameter9ValueSafeEPKcmf | lib libSOA-3.7.0.so | 2026-10-08
undefined1  [16]
_ZNK9Framework22CInteroperateParameter9ValueSafeEPKcmf
          (undefined1 param_1 [16],long param_2,undefined8 param_3,long param_4)

{
  int iVar1;
  ulong uVar2;
  long *plVar3;
  undefined1 auVar4 [16];
  undefined8 uVar5;
  
  uVar5 = param_1._8_8_;
  auVar4._0_8_ = param_1._0_8_;
  iVar1 = Framework::CInteroperateParameter::ConvertToRow(char const*) const();
  plVar3 = *(long **)(param_2 + 8);
  if (plVar3 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964324/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\InteroperateParameter.cpp"*/,0x1fb,&UNK_0296448a/*"m_pCSV is null."*/);
    plVar3 = *(long **)(param_2 + 8);
  }
  uVar2 = (**(code **)(*plVar3 + 0x48))(plVar3,(long)iVar1,param_4 + 1);
  if ((uVar2 & 1) != 0) {
    plVar3 = *(long **)(param_2 + 8);
    if (plVar3 == (long *)0x0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964324/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\InteroperateParameter.cpp"*/,0x207,&UNK_0296448a/*"m_pCSV is null."*/);
      plVar3 = *(long **)(param_2 + 8);
    }
                    /* WARNING: Could not recover jumptable at 0x01f878c4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    auVar4 = (**(code **)(*plVar3 + 0x58))(plVar3,(long)iVar1,param_4 + 1);
    return auVar4;
  }
  auVar4._8_8_ = uVar5;
  return auVar4;
}

// ==== Framework::CInteroperateParameter::ValueSafe(char const*, char const*, float) const
// vaddr 0x1e878dc | ghidra 0x1f878dc | size 204 | symbol _ZNK9Framework22CInteroperateParameter9ValueSafeEPKcS2_f | lib libSOA-3.7.0.so | 2026-10-08
undefined1  [16]
_ZNK9Framework22CInteroperateParameter9ValueSafeEPKcS2_f
          (undefined1 param_1 [16],long param_2,undefined8 param_3,undefined8 param_4)

{
  int iVar1;
  int iVar2;
  ulong uVar3;
  long *plVar4;
  undefined1 auVar5 [16];
  undefined8 uVar6;
  
  uVar6 = param_1._8_8_;
  auVar5._0_8_ = param_1._0_8_;
  iVar1 = Framework::CInteroperateParameter::ConvertToRow(char const*) const();
  iVar2 = Framework::CInteroperateParameter::ConvertToColumn(char const*) const(param_2,param_4);
  plVar4 = *(long **)(param_2 + 8);
  if (plVar4 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964324/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\InteroperateParameter.cpp"*/,0x1fb,&UNK_0296448a/*"m_pCSV is null."*/);
    plVar4 = *(long **)(param_2 + 8);
  }
  uVar3 = (**(code **)(*plVar4 + 0x48))(plVar4,(long)iVar1,(long)iVar2 + 1);
  if ((uVar3 & 1) != 0) {
    plVar4 = *(long **)(param_2 + 8);
    if (plVar4 == (long *)0x0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964324/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\InteroperateParameter.cpp"*/,0x207,&UNK_0296448a/*"m_pCSV is null."*/);
      plVar4 = *(long **)(param_2 + 8);
    }
                    /* WARNING: Could not recover jumptable at 0x01f87990. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    auVar5 = (**(code **)(*plVar4 + 0x58))(plVar4,(long)iVar1,(long)iVar2 + 1);
    return auVar5;
  }
  auVar5._8_8_ = uVar6;
  return auVar5;
}

// ==== Framework::CInteroperateParameter::StringSafe(unsigned long, unsigned long, char const*) const
// vaddr 0x1e879a8 | ghidra 0x1f879a8 | size 356 | symbol _ZNK9Framework22CInteroperateParameter10StringSafeEmmPKc | lib libSOA-3.7.0.so | 2026-10-08
void _ZNK9Framework22CInteroperateParameter10StringSafeEmmPKc
               (ulong *param_1,long param_2,undefined8 param_3,long param_4,undefined8 param_5)

{
  long *plVar1;
  ulong uVar2;
  ulong uVar3;
  ulong uVar4;
  
  plVar1 = *(long **)(param_2 + 8);
  if (plVar1 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964324/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\InteroperateParameter.cpp"*/,0x1c6,&UNK_0296448a/*"m_pCSV is null."*/);
    plVar1 = *(long **)(param_2 + 8);
    if (plVar1 == (long *)0x0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964324/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\InteroperateParameter.cpp"*/,0x201,&UNK_0296448a/*"m_pCSV is null."*/);
      plVar1 = *(long **)(param_2 + 8);
    }
  }
  uVar2 = (**(code **)(*plVar1 + 0x50))(plVar1,param_3,param_4 + 1);
  if ((uVar2 & 1) != 0) {
                    /* WARNING: Could not recover jumptable at 0x01f87a4c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(**(long **)(param_2 + 8) + 0x68))
              (param_1,*(long **)(param_2 + 8),param_3,param_4 + 1);
    return;
  }
  param_1[1] = 0;
  param_1[2] = 0;
  *param_1 = 0;
  uVar2 = strlen(param_5);
  if (uVar2 < 0x17) {
    uVar3 = (long)param_1 + 1;
    *(char *)param_1 = (char)(uVar2 << 1);
    if (uVar2 == 0) goto code_r0x01f87af8;
  }
  else {
    uVar4 = uVar2 + 0x10 & 0xfffffffffffffff0;
    if (uVar4 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296188c/*"C:\BAS_Submission\Client\Library\Framework\Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
    }
    uVar3 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar4,&UNK_029618d8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/STL_String.h"*/,0x1c);
    if (uVar3 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296188c/*"C:\BAS_Submission\Client\Library\Framework\Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
    param_1[1] = uVar2;
    param_1[2] = uVar3;
    *param_1 = uVar4 | 1;
  }
  memcpy(uVar3,param_5,uVar2);
code_r0x01f87af8:
  *(undefined1 *)(uVar3 + uVar2) = 0;
  return;
}

// ==== Framework::CInteroperateParameter::ToCsvColumn(unsigned long) const
// vaddr 0x1e87b0c | ghidra 0x1f87b0c | size 8 | symbol _ZNK9Framework22CInteroperateParameter11ToCsvColumnEm | lib libSOA-3.7.0.so | 2026-10-08
long _ZNK9Framework22CInteroperateParameter11ToCsvColumnEm(undefined8 param_1,long param_2)

{
  return param_2 + 1;
}

// ==== Framework::CInteroperateParameter::StringSafe(char const*, unsigned long, char const*) const
// vaddr 0x1e87b14 | ghidra 0x1f87b14 | size 68 | symbol _ZNK9Framework22CInteroperateParameter10StringSafeEPKcmS2_ | lib libSOA-3.7.0.so | 2026-10-08
void _ZNK9Framework22CInteroperateParameter10StringSafeEPKcmS2_
               (undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               undefined8 param_5)

{
  int iVar1;
  
  iVar1 = Framework::CInteroperateParameter::ConvertToRow(char const*) const();
  (*(code *)PTR__ZNK9Framework22CInteroperateParameter10StringSafeEmmPKc_02ca5600)
            (param_1,param_2,(long)iVar1,param_4,param_5);
  return;
}

// ==== Framework::CInteroperateParameter::StringSafe(char const*, char const*, char const*) const
// vaddr 0x1e87b58 | ghidra 0x1f87b58 | size 84 | symbol _ZNK9Framework22CInteroperateParameter10StringSafeEPKcS2_S2_ | lib libSOA-3.7.0.so | 2026-10-08
void _ZNK9Framework22CInteroperateParameter10StringSafeEPKcS2_S2_
               (undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               undefined8 param_5)

{
  int iVar1;
  int iVar2;
  
  iVar1 = Framework::CInteroperateParameter::ConvertToRow(char const*) const();
  iVar2 = Framework::CInteroperateParameter::ConvertToColumn(char const*) const(param_2,param_4);
  (*(code *)PTR__ZNK9Framework22CInteroperateParameter10StringSafeEmmPKc_02ca5600)
            (param_1,param_2,(long)iVar1,(long)iVar2,param_5);
  return;
}

// ==== Framework::CInteroperateParameter::IsExist(unsigned long, unsigned long) const
// vaddr 0x1e87bac | ghidra 0x1f87bac | size 200 | symbol _ZNK9Framework22CInteroperateParameter7IsExistEmm | lib libSOA-3.7.0.so | 2026-10-08
bool _ZNK9Framework22CInteroperateParameter7IsExistEmm(long param_1,ulong param_2,ulong param_3)

{
  bool bVar1;
  long *plVar2;
  ulong uVar3;
  long lVar4;
  
  plVar2 = *(long **)(param_1 + 8);
  if (plVar2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964324/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\InteroperateParameter.cpp"*/,0x1dc,&UNK_0296448a/*"m_pCSV is null."*/);
    plVar2 = *(long **)(param_1 + 8);
    if (plVar2 == (long *)0x0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964324/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\InteroperateParameter.cpp"*/,0x13f,&UNK_0296448a/*"m_pCSV is null."*/);
      plVar2 = *(long **)(param_1 + 8);
    }
  }
  uVar3 = (**(code **)(*plVar2 + 0x28))();
  if (param_2 < uVar3) {
    plVar2 = *(long **)(param_1 + 8);
    if (plVar2 == (long *)0x0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964324/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\InteroperateParameter.cpp"*/,0x16f,&UNK_0296448a/*"m_pCSV is null."*/);
      plVar2 = *(long **)(param_1 + 8);
    }
    lVar4 = (**(code **)(*plVar2 + 0x30))(plVar2,param_2);
    uVar3 = lVar4 - 1;
    if (lVar4 == 0) {
      uVar3 = 0;
    }
    bVar1 = param_3 < uVar3;
  }
  else {
    bVar1 = false;
  }
  return bVar1;
}

// ==== Framework::CInteroperateParameter::IsNotBlank(unsigned long, unsigned long) const
// vaddr 0x1e87c74 | ghidra 0x1f87c74 | size 24 | symbol _ZNK9Framework22CInteroperateParameter10IsNotBlankEmm | lib libSOA-3.7.0.so | 2026-10-08
uint _ZNK9Framework22CInteroperateParameter10IsNotBlankEmm(void)

{
  uint uVar1;
  
  uVar1 = Framework::CInteroperateParameter::IsBlank(unsigned long, unsigned long) const();
  return ~uVar1 & 1;
}

// ==== Framework::CInteroperateParameter::IsNotBlank(char const*, unsigned long) const
// vaddr 0x1e87c8c | ghidra 0x1f87c8c | size 56 | symbol _ZNK9Framework22CInteroperateParameter10IsNotBlankEPKcm | lib libSOA-3.7.0.so | 2026-10-08
uint _ZNK9Framework22CInteroperateParameter10IsNotBlankEPKcm
               (undefined8 param_1,undefined8 param_2,undefined8 param_3)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = Framework::CInteroperateParameter::ConvertToRow(char const*) const();
  uVar2 = Framework::CInteroperateParameter::IsBlank(unsigned long, unsigned long) const(param_1,(long)iVar1,param_3);
  return ~uVar2 & 1;
}

// ==== Framework::CInteroperateParameter::IsNotBlank(char const*, char const*) const
// vaddr 0x1e87cc4 | ghidra 0x1f87cc4 | size 72 | symbol _ZNK9Framework22CInteroperateParameter10IsNotBlankEPKcS2_ | lib libSOA-3.7.0.so | 2026-10-08
uint _ZNK9Framework22CInteroperateParameter10IsNotBlankEPKcS2_
               (undefined8 param_1,undefined8 param_2,undefined8 param_3)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  iVar1 = Framework::CInteroperateParameter::ConvertToRow(char const*) const();
  iVar2 = Framework::CInteroperateParameter::ConvertToColumn(char const*) const(param_1,param_3);
  uVar3 = Framework::CInteroperateParameter::IsBlank(unsigned long, unsigned long) const(param_1,(long)iVar1,(long)iVar2);
  return ~uVar3 & 1;
}

// ==== Framework::CInteroperateParameter::Value(unsigned long, unsigned long, float)
// vaddr 0x1e87d0c | ghidra 0x1f87d0c | size 100 | symbol _ZN9Framework22CInteroperateParameter5ValueEmmf | lib libSOA-3.7.0.so | 2026-10-08
void _ZN9Framework22CInteroperateParameter5ValueEmmf
               (undefined8 param_1,long param_2,undefined8 param_3,long param_4)

{
  long *plVar1;
  
  plVar1 = *(long **)(param_2 + 8);
  if (plVar1 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964324/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\InteroperateParameter.cpp"*/,0x233,&UNK_0296448a/*"m_pCSV is null."*/);
    plVar1 = *(long **)(param_2 + 8);
  }
                    /* WARNING: Could not recover jumptable at 0x01f87d6c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*plVar1 + 0x70))(param_1,plVar1,param_3,param_4 + 1);
  return;
}

// ==== Framework::CInteroperateParameter::Value(char const*, unsigned long, float)
// vaddr 0x1e87d70 | ghidra 0x1f87d70 | size 108 | symbol _ZN9Framework22CInteroperateParameter5ValueEPKcmf | lib libSOA-3.7.0.so | 2026-10-08
void _ZN9Framework22CInteroperateParameter5ValueEPKcmf
               (undefined8 param_1,long param_2,undefined8 param_3,long param_4)

{
  int iVar1;
  long *plVar2;
  
  iVar1 = Framework::CInteroperateParameter::ConvertToRow(char const*) const();
  plVar2 = *(long **)(param_2 + 8);
  if (plVar2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964324/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\InteroperateParameter.cpp"*/,0x233,&UNK_0296448a/*"m_pCSV is null."*/);
    plVar2 = *(long **)(param_2 + 8);
  }
                    /* WARNING: Could not recover jumptable at 0x01f87dd8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*plVar2 + 0x70))(param_1,plVar2,(long)iVar1,param_4 + 1);
  return;
}

// ==== Framework::CInteroperateParameter::Value(char const*, char const*, float)
// vaddr 0x1e87ddc | ghidra 0x1f87ddc | size 124 | symbol _ZN9Framework22CInteroperateParameter5ValueEPKcS2_f | lib libSOA-3.7.0.so | 2026-10-08
void _ZN9Framework22CInteroperateParameter5ValueEPKcS2_f
               (undefined8 param_1,long param_2,undefined8 param_3,undefined8 param_4)

{
  int iVar1;
  int iVar2;
  long *plVar3;
  
  iVar1 = Framework::CInteroperateParameter::ConvertToRow(char const*) const();
  iVar2 = Framework::CInteroperateParameter::ConvertToColumn(char const*) const(param_2,param_4);
  plVar3 = *(long **)(param_2 + 8);
  if (plVar3 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964324/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\InteroperateParameter.cpp"*/,0x233,&UNK_0296448a/*"m_pCSV is null."*/);
    plVar3 = *(long **)(param_2 + 8);
  }
                    /* WARNING: Could not recover jumptable at 0x01f87e54. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*plVar3 + 0x70))(param_1,plVar3,(long)iVar1,(long)iVar2 + 1);
  return;
}

// ==== Framework::CInteroperateParameter::String(unsigned long, unsigned long, char const*)
// vaddr 0x1e87e58 | ghidra 0x1f87e58 | size 324 | symbol _ZN9Framework22CInteroperateParameter6StringEmmPKc | lib libSOA-3.7.0.so | 2026-10-08
void _ZN9Framework22CInteroperateParameter6StringEmmPKc
               (long param_1,undefined8 param_2,long param_3,undefined8 param_4)

{
  ulong uVar1;
  long *plVar2;
  ulong uVar3;
  ulong uVar4;
  code *pcVar5;
  ulong uStack_68;
  ulong uStack_60;
  ulong uStack_58;
  
  plVar2 = *(long **)(param_1 + 8);
  if (plVar2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964324/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\InteroperateParameter.cpp"*/,0x24a,&UNK_0296448a/*"m_pCSV is null."*/);
    plVar2 = *(long **)(param_1 + 8);
  }
  pcVar5 = *(code **)(*plVar2 + 0x78);
  uStack_60 = 0;
  uStack_58 = 0;
  uStack_68 = 0;
  uVar1 = strlen(param_4);
  if (uVar1 < 0x17) {
    uVar4 = (ulong)&uStack_68 | 1;
    uStack_68 = CONCAT71(uStack_68._1_7_,(char)(uVar1 << 1));
    if (uVar1 == 0) goto code_r0x01f87f58;
  }
  else {
    uVar3 = uVar1 + 0x10 & 0xfffffffffffffff0;
    if (uVar3 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296188c/*"C:\BAS_Submission\Client\Library\Framework\Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
    }
    uVar4 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar3,&UNK_029618d8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/STL_String.h"*/,0x1c);
    if (uVar4 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296188c/*"C:\BAS_Submission\Client\Library\Framework\Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
    uStack_68 = uVar3 | 1;
    uStack_60 = uVar1;
    uStack_58 = uVar4;
  }
  memcpy(uVar4,param_4,uVar1);
code_r0x01f87f58:
  *(undefined1 *)(uVar4 + uVar1) = 0;
  (*pcVar5)(plVar2,param_2,param_3 + 1,&uStack_68);
  if ((uStack_68 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_58);
  }
  return;
}

// ==== Framework::CInteroperateParameter::String(char const*, unsigned long, char const*)
// vaddr 0x1e87f9c | ghidra 0x1f87f9c | size 52 | symbol _ZN9Framework22CInteroperateParameter6StringEPKcmS2_ | lib libSOA-3.7.0.so | 2026-10-08
void _ZN9Framework22CInteroperateParameter6StringEPKcmS2_
               (undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  int iVar1;
  
  iVar1 = Framework::CInteroperateParameter::ConvertToRow(char const*) const();
  (*(code *)PTR__ZN9Framework22CInteroperateParameter6StringEmmPKc_02c95c78)
            (param_1,(long)iVar1,param_3,param_4);
  return;
}

// ==== Framework::CInteroperateParameter::String(char const*, char const*, char const*)
// vaddr 0x1e87fd0 | ghidra 0x1f87fd0 | size 76 | symbol _ZN9Framework22CInteroperateParameter6StringEPKcS2_S2_ | lib libSOA-3.7.0.so | 2026-10-08
void _ZN9Framework22CInteroperateParameter6StringEPKcS2_S2_
               (undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  int iVar1;
  int iVar2;
  
  iVar1 = Framework::CInteroperateParameter::ConvertToRow(char const*) const();
  iVar2 = Framework::CInteroperateParameter::ConvertToColumn(char const*) const(param_1,param_3);
  (*(code *)PTR__ZN9Framework22CInteroperateParameter6StringEmmPKc_02c95c78)
            (param_1,(long)iVar1,(long)iVar2,param_4);
  return;
}

// ==== Framework::CInteroperateParameter::TCSVAccessor<Framework::CCSV>::Initialize()
// vaddr 0x1e8801c | ghidra 0x1f8801c | size 8 | symbol _ZN9Framework22CInteroperateParameter12TCSVAccessorINS_4CCSVEE10InitializeEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN9Framework22CInteroperateParameter12TCSVAccessorINS_4CCSVEE10InitializeEv(long param_1)

{
  (*(code *)PTR__ZN9Framework4CCSV10InitializeEv_02c976d0)(param_1 + 8);
  return;
}

// ==== Framework::CInteroperateParameter::TCSVAccessor<Framework::CCSV>::Parse(char const*)
// vaddr 0x1e88024 | ghidra 0x1f88024 | size 12 | symbol _ZN9Framework22CInteroperateParameter12TCSVAccessorINS_4CCSVEE5ParseEPKc | lib libSOA-3.7.0.so | 2026-10-08
void _ZN9Framework22CInteroperateParameter12TCSVAccessorINS_4CCSVEE5ParseEPKc
               (long param_1,undefined8 param_2)

{
  (*(code *)PTR__ZN9Framework4CCSV5ParseEPKcb_02cb1d08)(param_1 + 8,param_2,0);
  return;
}

// ==== Framework::CInteroperateParameter::TCSVAccessor<Framework::CCSV>::ParseBinary(void const*, unsigned long)
// vaddr 0x1e88030 | ghidra 0x1f88030 | size 24 | symbol _ZN9Framework22CInteroperateParameter12TCSVAccessorINS_4CCSVEE11ParseBinaryEPKvm | lib libSOA-3.7.0.so | 2026-10-08
void _ZN9Framework22CInteroperateParameter12TCSVAccessorINS_4CCSVEE11ParseBinaryEPKvm(void)

{
  (*(code *)PTR__ZN9Framework9gDoAssertEPKciS1_z_02ca3240)(&UNK_02964324/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\InteroperateParameter.cpp"*/,0x27a,&UNK_029644c5/*"Not support."*/);
  return;
}

// ==== Framework::CInteroperateParameter::TCSVAccessor<Framework::CCSV>::NumRows() const
// vaddr 0x1e88048 | ghidra 0x1f88048 | size 8 | symbol _ZNK9Framework22CInteroperateParameter12TCSVAccessorINS_4CCSVEE7NumRowsEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZNK9Framework22CInteroperateParameter12TCSVAccessorINS_4CCSVEE7NumRowsEv(long param_1)

{
  (*(code *)PTR__ZNK9Framework4CCSV7NumRowsEv_02ca33a8)(param_1 + 8);
  return;
}

// ==== Framework::CInteroperateParameter::TCSVAccessor<Framework::CCSV>::NumColumns(unsigned long) const
// vaddr 0x1e88050 | ghidra 0x1f88050 | size 8 | symbol _ZNK9Framework22CInteroperateParameter12TCSVAccessorINS_4CCSVEE10NumColumnsEm | lib libSOA-3.7.0.so | 2026-10-08
void _ZNK9Framework22CInteroperateParameter12TCSVAccessorINS_4CCSVEE10NumColumnsEm(long param_1)

{
  (*(code *)PTR__ZNK9Framework4CCSV11NumElementsEm_02cae470)(param_1 + 8);
  return;
}

// ==== Framework::CInteroperateParameter::TCSVAccessor<Framework::CCSV>::MaxElements() const
// vaddr 0x1e88058 | ghidra 0x1f88058 | size 8 | symbol _ZNK9Framework22CInteroperateParameter12TCSVAccessorINS_4CCSVEE11MaxElementsEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZNK9Framework22CInteroperateParameter12TCSVAccessorINS_4CCSVEE11MaxElementsEv(long param_1)

{
  (*(code *)PTR__ZNK9Framework4CCSV11MaxElementsEv_02c95fc0)(param_1 + 8);
  return;
}

// ==== Framework::CInteroperateParameter::TCSVAccessor<Framework::CCSV>::IsBlank(unsigned long, unsigned long) const
// vaddr 0x1e88060 | ghidra 0x1f88060 | size 20 | symbol _ZNK9Framework22CInteroperateParameter12TCSVAccessorINS_4CCSVEE7IsBlankEmm | lib libSOA-3.7.0.so | 2026-10-08
void _ZNK9Framework22CInteroperateParameter12TCSVAccessorINS_4CCSVEE7IsBlankEmm(long param_1)

{
  Framework::CCSV::Element(unsigned long, unsigned long) const(param_1 + 8);
  (*(code *)PTR__ZNK9Framework4CCSV8tElement7IsBlankEv_02cb5750)();
  return;
}

// ==== Framework::CInteroperateParameter::TCSVAccessor<Framework::CCSV>::IsValue(unsigned long, unsigned long) const
// vaddr 0x1e88074 | ghidra 0x1f88074 | size 20 | symbol _ZNK9Framework22CInteroperateParameter12TCSVAccessorINS_4CCSVEE7IsValueEmm | lib libSOA-3.7.0.so | 2026-10-08
void _ZNK9Framework22CInteroperateParameter12TCSVAccessorINS_4CCSVEE7IsValueEmm(long param_1)

{
  Framework::CCSV::Element(unsigned long, unsigned long) const(param_1 + 8);
  (*(code *)PTR__ZNK9Framework4CCSV8tElement7IsValueEv_02ca2998)();
  return;
}

// ==== Framework::CInteroperateParameter::TCSVAccessor<Framework::CCSV>::IsString(unsigned long, unsigned long) const
// vaddr 0x1e88088 | ghidra 0x1f88088 | size 20 | symbol _ZNK9Framework22CInteroperateParameter12TCSVAccessorINS_4CCSVEE8IsStringEmm | lib libSOA-3.7.0.so | 2026-10-08
void _ZNK9Framework22CInteroperateParameter12TCSVAccessorINS_4CCSVEE8IsStringEmm(long param_1)

{
  Framework::CCSV::Element(unsigned long, unsigned long) const(param_1 + 8);
  (*(code *)PTR__ZNK9Framework4CCSV8tElement8IsStringEv_02cb4830)();
  return;
}

// ==== Framework::CInteroperateParameter::TCSVAccessor<Framework::CCSV>::Value(unsigned long, unsigned long) const
// vaddr 0x1e8809c | ghidra 0x1f8809c | size 28 | symbol _ZNK9Framework22CInteroperateParameter12TCSVAccessorINS_4CCSVEE5ValueEmm | lib libSOA-3.7.0.so | 2026-10-08
float _ZNK9Framework22CInteroperateParameter12TCSVAccessorINS_4CCSVEE5ValueEmm(long param_1)

{
  double dVar1;
  
  Framework::CCSV::Element(unsigned long, unsigned long) const(param_1 + 8);
  dVar1 = (double)Framework::CCSV::tElement::Value() const();
  return (float)dVar1;
}

// ==== Framework::CInteroperateParameter::TCSVAccessor<Framework::CCSV>::ValueSafe(unsigned long, unsigned long, float) const
// vaddr 0x1e880b8 | ghidra 0x1f880b8 | size 44 | symbol _ZNK9Framework22CInteroperateParameter12TCSVAccessorINS_4CCSVEE9ValueSafeEmmf | lib libSOA-3.7.0.so | 2026-10-08
float _ZNK9Framework22CInteroperateParameter12TCSVAccessorINS_4CCSVEE9ValueSafeEmmf
                (float param_1,long param_2)

{
  double dVar1;
  
  Framework::CCSV::Element(unsigned long, unsigned long) const(param_2 + 8);
  dVar1 = (double)Framework::CCSV::tElement::ValueSafe(double) const((double)param_1);
  return (float)dVar1;
}

// ==== Framework::CInteroperateParameter::TCSVAccessor<Framework::CCSV>::String(unsigned long, unsigned long) const
// vaddr 0x1e880e4 | ghidra 0x1f880e4 | size 236 | symbol _ZNK9Framework22CInteroperateParameter12TCSVAccessorINS_4CCSVEE6StringEmm | lib libSOA-3.7.0.so | 2026-10-08
void _ZNK9Framework22CInteroperateParameter12TCSVAccessorINS_4CCSVEE6StringEmm
               (ulong *param_1,long param_2)

{
  ulong uVar1;
  ulong *puVar2;
  ulong uVar3;
  ulong uVar4;
  ulong uVar5;
  
  Framework::CCSV::Element(unsigned long, unsigned long) const(param_2 + 8);
  puVar2 = (ulong *)Framework::CCSV::tElement::String() const();
  param_1[1] = 0;
  param_1[2] = 0;
  *param_1 = 0;
  if ((*puVar2 & 1) == 0) {
    param_1[2] = puVar2[2];
    uVar5 = *puVar2;
    param_1[1] = puVar2[1];
    *param_1 = uVar5;
    return;
  }
  uVar5 = puVar2[1];
  uVar1 = puVar2[2];
  if (uVar5 < 0x17) {
    uVar3 = (long)param_1 + 1;
    *(char *)param_1 = (char)(uVar5 << 1);
    if (uVar5 == 0) goto code_r0x01f881bc;
  }
  else {
    uVar4 = uVar5 + 0x10 & 0xfffffffffffffff0;
    if (uVar4 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296188c/*"C:\BAS_Submission\Client\Library\Framework\Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
    }
    uVar3 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar4,&UNK_029618d8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/STL_String.h"*/,0x1c);
    if (uVar3 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296188c/*"C:\BAS_Submission\Client\Library\Framework\Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
    param_1[1] = uVar5;
    param_1[2] = uVar3;
    *param_1 = uVar4 | 1;
  }
  memcpy(uVar3,uVar1,uVar5);
code_r0x01f881bc:
  *(undefined1 *)(uVar3 + uVar5) = 0;
  return;
}

// ==== Framework::CInteroperateParameter::TCSVAccessor<Framework::CCSV>::Value(unsigned long, unsigned long, float)
// vaddr 0x1e881d0 | ghidra 0x1f881d0 | size 36 | symbol _ZN9Framework22CInteroperateParameter12TCSVAccessorINS_4CCSVEE5ValueEmmf | lib libSOA-3.7.0.so | 2026-10-08
void _ZN9Framework22CInteroperateParameter12TCSVAccessorINS_4CCSVEE5ValueEmmf
               (float param_1,long param_2)

{
  Framework::CCSV::rElement(unsigned long, unsigned long)(param_2 + 8);
  (*(code *)PTR__ZN9Framework4CCSV8tElement5ValueEd_02cb12e8)((double)param_1);
  return;
}

// ==== Framework::CInteroperateParameter::TCSVAccessor<Framework::CCSV>::String(unsigned long, unsigned long, std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > const&)
// vaddr 0x1e881f4 | ghidra 0x1f881f4 | size 28 | symbol _ZN9Framework22CInteroperateParameter12TCSVAccessorINS_4CCSVEE6StringEmmRKNSt6__ndk112basic_stringIcNS4_11char_traitsIcEENS_13CSTLAllocatorIcNS_22CSTLStringAllocatorInfEEEEE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN9Framework22CInteroperateParameter12TCSVAccessorINS_4CCSVEE6StringEmmRKNSt6__ndk112basic_stringIcNS4_11char_traitsIcEENS_13CSTLAllocatorIcNS_22CSTLStringAllocatorInfEEEEE
               (long param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  undefined8 uVar1;
  
  uVar1 = Framework::CCSV::rElement(unsigned long, unsigned long)(param_1 + 8);
  (*(code *)
    PTR__ZN9Framework4CCSV8tElement6StringERKNSt6__ndk112basic_stringIcNS2_11char_traitsIcEENS_13CSTLAllocatorIcNS_22CSTLStringAllocatorInfEEEEE_02c934a8
  )(uVar1,param_4);
  return;
}

// ==== Framework::CInteroperateParameter::TCSVAccessor<Framework::CACSV>::Initialize()
// vaddr 0x1e88210 | ghidra 0x1f88210 | size 8 | symbol _ZN9Framework22CInteroperateParameter12TCSVAccessorINS_5CACSVEE10InitializeEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN9Framework22CInteroperateParameter12TCSVAccessorINS_5CACSVEE10InitializeEv(long param_1)

{
  (*(code *)PTR__ZN9Framework5CACSV10InitializeEv_02cabcb0)(param_1 + 8);
  return;
}

// ==== Framework::CInteroperateParameter::TCSVAccessor<Framework::CACSV>::Parse(char const*)
// vaddr 0x1e88218 | ghidra 0x1f88218 | size 8 | symbol _ZN9Framework22CInteroperateParameter12TCSVAccessorINS_5CACSVEE5ParseEPKc | lib libSOA-3.7.0.so | 2026-10-08
void _ZN9Framework22CInteroperateParameter12TCSVAccessorINS_5CACSVEE5ParseEPKc(long param_1)

{
  (*(code *)PTR__ZN9Framework5CACSV5ParseEPKc_02c9c0f0)(param_1 + 8);
  return;
}

// ==== Framework::CInteroperateParameter::TCSVAccessor<Framework::CACSV>::ParseBinary(void const*, unsigned long)
// vaddr 0x1e88220 | ghidra 0x1f88220 | size 8 | symbol _ZN9Framework22CInteroperateParameter12TCSVAccessorINS_5CACSVEE11ParseBinaryEPKvm | lib libSOA-3.7.0.so | 2026-10-08
void _ZN9Framework22CInteroperateParameter12TCSVAccessorINS_5CACSVEE11ParseBinaryEPKvm(long param_1)

{
  (*(code *)PTR__ZN9Framework5CACSV11ParseBinaryEPKvm_02cb6650)(param_1 + 8);
  return;
}

// ==== Framework::CInteroperateParameter::TCSVAccessor<Framework::CACSV>::NumRows() const
// vaddr 0x1e88228 | ghidra 0x1f88228 | size 8 | symbol _ZNK9Framework22CInteroperateParameter12TCSVAccessorINS_5CACSVEE7NumRowsEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZNK9Framework22CInteroperateParameter12TCSVAccessorINS_5CACSVEE7NumRowsEv(long param_1)

{
  (*(code *)PTR__ZNK9Framework5CACSV7NumRowsEv_02caec78)(param_1 + 8);
  return;
}

// ==== Framework::CInteroperateParameter::TCSVAccessor<Framework::CACSV>::NumColumns(unsigned long) const
// vaddr 0x1e88230 | ghidra 0x1f88230 | size 8 | symbol _ZNK9Framework22CInteroperateParameter12TCSVAccessorINS_5CACSVEE10NumColumnsEm | lib libSOA-3.7.0.so | 2026-10-08
void _ZNK9Framework22CInteroperateParameter12TCSVAccessorINS_5CACSVEE10NumColumnsEm(long param_1)

{
  (*(code *)PTR__ZNK9Framework5CACSV10NumColumnsEv_02ca6a68)(param_1 + 8);
  return;
}

// ==== Framework::CInteroperateParameter::TCSVAccessor<Framework::CACSV>::MaxElements() const
// vaddr 0x1e88238 | ghidra 0x1f88238 | size 8 | symbol _ZNK9Framework22CInteroperateParameter12TCSVAccessorINS_5CACSVEE11MaxElementsEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZNK9Framework22CInteroperateParameter12TCSVAccessorINS_5CACSVEE11MaxElementsEv(long param_1)

{
  (*(code *)PTR__ZNK9Framework5CACSV10NumColumnsEv_02ca6a68)(param_1 + 8);
  return;
}

// ==== Framework::CInteroperateParameter::TCSVAccessor<Framework::CACSV>::IsBlank(unsigned long, unsigned long) const
// vaddr 0x1e88240 | ghidra 0x1f88240 | size 8 | symbol _ZNK9Framework22CInteroperateParameter12TCSVAccessorINS_5CACSVEE7IsBlankEmm | lib libSOA-3.7.0.so | 2026-10-08
void _ZNK9Framework22CInteroperateParameter12TCSVAccessorINS_5CACSVEE7IsBlankEmm(long param_1)

{
  (*(code *)PTR__ZNK9Framework5CACSV7IsBlankEmm_02cb4ed8)(param_1 + 8);
  return;
}

// ==== Framework::CInteroperateParameter::TCSVAccessor<Framework::CACSV>::IsValue(unsigned long, unsigned long) const
// vaddr 0x1e88248 | ghidra 0x1f88248 | size 8 | symbol _ZNK9Framework22CInteroperateParameter12TCSVAccessorINS_5CACSVEE7IsValueEmm | lib libSOA-3.7.0.so | 2026-10-08
void _ZNK9Framework22CInteroperateParameter12TCSVAccessorINS_5CACSVEE7IsValueEmm(long param_1)

{
  (*(code *)PTR__ZNK9Framework5CACSV7IsValueEmm_02c97fe0)(param_1 + 8);
  return;
}

// ==== Framework::CInteroperateParameter::TCSVAccessor<Framework::CACSV>::IsString(unsigned long, unsigned long) const
// vaddr 0x1e88250 | ghidra 0x1f88250 | size 8 | symbol _ZNK9Framework22CInteroperateParameter12TCSVAccessorINS_5CACSVEE8IsStringEmm | lib libSOA-3.7.0.so | 2026-10-08
void _ZNK9Framework22CInteroperateParameter12TCSVAccessorINS_5CACSVEE8IsStringEmm(long param_1)

{
  (*(code *)PTR__ZNK9Framework5CACSV8IsStringEmm_02ca3530)(param_1 + 8);
  return;
}

// ==== Framework::CInteroperateParameter::TCSVAccessor<Framework::CACSV>::Value(unsigned long, unsigned long) const
// vaddr 0x1e88258 | ghidra 0x1f88258 | size 8 | symbol _ZNK9Framework22CInteroperateParameter12TCSVAccessorINS_5CACSVEE5ValueEmm | lib libSOA-3.7.0.so | 2026-10-08
void _ZNK9Framework22CInteroperateParameter12TCSVAccessorINS_5CACSVEE5ValueEmm(long param_1)

{
  (*(code *)PTR__ZNK9Framework5CACSV5ValueEmm_02c99f40)(param_1 + 8);
  return;
}

// ==== Framework::CInteroperateParameter::TCSVAccessor<Framework::CACSV>::ValueSafe(unsigned long, unsigned long, float) const
// vaddr 0x1e88260 | ghidra 0x1f88260 | size 88 | symbol _ZNK9Framework22CInteroperateParameter12TCSVAccessorINS_5CACSVEE9ValueSafeEmmf | lib libSOA-3.7.0.so | 2026-10-08
undefined1  [16]
_ZNK9Framework22CInteroperateParameter12TCSVAccessorINS_5CACSVEE9ValueSafeEmmf
          (undefined1 param_1 [16],long param_2,undefined8 param_3,undefined8 param_4)

{
  ulong uVar1;
  undefined1 auVar2 [16];
  undefined8 uVar3;
  
  uVar3 = param_1._8_8_;
  auVar2._0_8_ = param_1._0_8_;
  uVar1 = Framework::CACSV::IsValue(unsigned long, unsigned long) const(param_2 + 8);
  if ((uVar1 & 1) != 0) {
    auVar2 = (*(code *)PTR__ZNK9Framework5CACSV5ValueEmm_02c99f40)(param_2 + 8,param_3,param_4);
    return auVar2;
  }
  auVar2._8_8_ = uVar3;
  return auVar2;
}

// ==== Framework::CInteroperateParameter::TCSVAccessor<Framework::CACSV>::String(unsigned long, unsigned long) const
// vaddr 0x1e882b8 | ghidra 0x1f882b8 | size 8 | symbol _ZNK9Framework22CInteroperateParameter12TCSVAccessorINS_5CACSVEE6StringEmm | lib libSOA-3.7.0.so | 2026-10-08
void _ZNK9Framework22CInteroperateParameter12TCSVAccessorINS_5CACSVEE6StringEmm(long param_1)

{
  (*(code *)PTR__ZNK9Framework5CACSV6StringEmm_02ca9b48)(param_1 + 8);
  return;
}

// ==== Framework::CInteroperateParameter::TCSVAccessor<Framework::CACSV>::Value(unsigned long, unsigned long, float)
// vaddr 0x1e882c0 | ghidra 0x1f882c0 | size 8 | symbol _ZN9Framework22CInteroperateParameter12TCSVAccessorINS_5CACSVEE5ValueEmmf | lib libSOA-3.7.0.so | 2026-10-08
void _ZN9Framework22CInteroperateParameter12TCSVAccessorINS_5CACSVEE5ValueEmmf(long param_1)

{
  (*(code *)PTR__ZN9Framework5CACSV5ValueEmmf_02c9dc20)(param_1 + 8);
  return;
}

// ==== Framework::CInteroperateParameter::TCSVAccessor<Framework::CACSV>::String(unsigned long, unsigned long, std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > const&)
// vaddr 0x1e882c8 | ghidra 0x1f882c8 | size 8 | symbol _ZN9Framework22CInteroperateParameter12TCSVAccessorINS_5CACSVEE6StringEmmRKNSt6__ndk112basic_stringIcNS4_11char_traitsIcEENS_13CSTLAllocatorIcNS_22CSTLStringAllocatorInfEEEEE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN9Framework22CInteroperateParameter12TCSVAccessorINS_5CACSVEE6StringEmmRKNSt6__ndk112basic_stringIcNS4_11char_traitsIcEENS_13CSTLAllocatorIcNS_22CSTLStringAllocatorInfEEEEE
               (long param_1)

{
  (*(code *)
    PTR__ZN9Framework5CACSV6StringEmmRKNSt6__ndk112basic_stringIcNS1_11char_traitsIcEENS_13CSTLAllocatorIcNS_22CSTLStringAllocatorInfEEEEE_02ca6c60
  )(param_1 + 8);
  return;
}

// ==== Framework::CInteroperateParameter::gRegressionTest()
// vaddr 0x1e882d0 | ghidra 0x1f882d0 | size 1256 | symbol _ZN9Framework22CInteroperateParameter15gRegressionTestEv | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN9Framework22CInteroperateParameter15gRegressionTestEv(void)

{
  undefined *puVar1;
  long lVar2;
  int iVar3;
  int iVar4;
  long *plVar5;
  long *plVar6;
  byte abStack_b0 [16];
  undefined8 uStack_a0;
  byte abStack_98 [16];
  undefined8 uStack_88;
  undefined *puStack_80;
  long *plStack_78;
  long lStack_70;
  long lStack_68;
  undefined4 uStack_5c;
  undefined *puStack_58;
  long *plStack_50;
  long lStack_48;
  long lStack_40;
  undefined4 uStack_34;
  
  puVar1 = PTR__ZTVN9Framework22CInteroperateParameterE_02cc0e38;
  uStack_34 = 0;
  lStack_48 = 0;
  lStack_40 = 0;
  puStack_58 = PTR__ZTVN9Framework22CInteroperateParameterE_02cc0e38 + 0x10;
  plStack_50 = (long *)0x0;
  plVar5 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x48,PTR__ZSt7nothrow_02cb9a80);
  if (plVar5 != (long *)0x0) {
    *plVar5 = (long)(PTR__ZTVN9Framework22CInteroperateParameter12TCSVAccessorINS_4CCSVEEE_02cbae58
                    + 0x10);
    Framework::CCSV::CCSV()(plVar5 + 1);
  }
  Framework::CInteroperateParameter::Initialize(char const*, unsigned int, Framework::CInteroperateParameter::ICSVAccessor*)(&puStack_58,&UNK_029644fe,0,plVar5);
  iVar3 = Framework::CInteroperateParameter::ConvertToRow(char const*) const(&puStack_58,&UNK_029644d2/*"TestParameter0"*/);
  plVar5 = plStack_50;
  if (plStack_50 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964324/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\InteroperateParameter.cpp"*/,0x233,&UNK_0296448a/*"m_pCSV is null."*/);
  }
  (**(code **)(*plVar5 + 0x70))(_UNK_02964320,plVar5,(long)iVar3,1);
  iVar3 = Framework::CInteroperateParameter::ConvertToRow(char const*) const(&puStack_58,&UNK_029644e1/*"TestStringParameter0"*/);
  Framework::CInteroperateParameter::String(unsigned long, unsigned long, char const*)(&puStack_58,(long)iVar3,0,&UNK_029644f6/*"Rewrite"*/);
  puStack_80 = puVar1 + 0x10;
  plStack_78 = (long *)0x0;
  uStack_5c = 0;
  lStack_70 = 0;
  lStack_68 = 0;
  plVar6 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x48,PTR__ZSt7nothrow_02cb9a80);
  if (plVar6 != (long *)0x0) {
    *plVar6 = (long)(PTR__ZTVN9Framework22CInteroperateParameter12TCSVAccessorINS_4CCSVEEE_02cbae58
                    + 0x10);
    Framework::CCSV::CCSV()(plVar6 + 1);
  }
  Framework::CInteroperateParameter::Initialize(char const*, unsigned int, Framework::CInteroperateParameter::ICSVAccessor*)(&puStack_80,&UNK_029645af,1,plVar6);
  iVar3 = Framework::CInteroperateParameter::ConvertToRow(char const*) const(&puStack_80,&UNK_028a4177/*"Player"*/);
  iVar4 = Framework::CInteroperateParameter::ConvertToColumn(char const*) const(&puStack_80,&UNK_029d84d4/*"Name"*/);
  plVar6 = plStack_78;
  if (plStack_78 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964324/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\InteroperateParameter.cpp"*/,0x20d,&UNK_0296448a/*"m_pCSV is null."*/);
  }
  (**(code **)(*plVar6 + 0x68))(abStack_98,plVar6,(long)iVar3,(long)iVar4 + 1);
  iVar3 = Framework::CInteroperateParameter::ConvertToRow(char const*) const(&puStack_80,&UNK_02952d85/*"Enemy"*/);
  iVar4 = Framework::CInteroperateParameter::ConvertToColumn(char const*) const(&puStack_80,&UNK_029d84d4/*"Name"*/);
  if (plVar6 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964324/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\InteroperateParameter.cpp"*/,0x20d,&UNK_0296448a/*"m_pCSV is null."*/);
  }
  (**(code **)(*plVar6 + 0x68))(abStack_b0,plVar6,(long)iVar3,(long)iVar4 + 1);
  iVar3 = Framework::CInteroperateParameter::ConvertToRow(char const*) const(&puStack_80,&UNK_028a4177/*"Player"*/);
  iVar4 = Framework::CInteroperateParameter::ConvertToColumn(char const*) const(&puStack_80,&UNK_027ee88c/*"HP"*/);
  if (plVar6 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964324/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\InteroperateParameter.cpp"*/,0x207,&UNK_0296448a/*"m_pCSV is null."*/);
  }
  (**(code **)(*plVar6 + 0x58))(plVar6,(long)iVar3,(long)iVar4 + 1);
  iVar3 = Framework::CInteroperateParameter::ConvertToRow(char const*) const(&puStack_80,&UNK_028a4177/*"Player"*/);
  iVar4 = Framework::CInteroperateParameter::ConvertToColumn(char const*) const(&puStack_80,&UNK_029cd2ff/*"MP"*/);
  if (plVar6 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964324/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\InteroperateParameter.cpp"*/,0x207,&UNK_0296448a/*"m_pCSV is null."*/);
  }
  (**(code **)(*plVar6 + 0x58))(plVar6,(long)iVar3,(long)iVar4 + 1);
  iVar3 = Framework::CInteroperateParameter::ConvertToRow(char const*) const(&puStack_80,&UNK_02952d85/*"Enemy"*/);
  iVar4 = Framework::CInteroperateParameter::ConvertToColumn(char const*) const(&puStack_80,&UNK_027ee88c/*"HP"*/);
  if (plVar6 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964324/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\InteroperateParameter.cpp"*/,0x207,&UNK_0296448a/*"m_pCSV is null."*/);
  }
  (**(code **)(*plVar6 + 0x58))(plVar6,(long)iVar3,(long)iVar4 + 1);
  iVar3 = Framework::CInteroperateParameter::ConvertToRow(char const*) const(&puStack_80,&UNK_02952d85/*"Enemy"*/);
  iVar4 = Framework::CInteroperateParameter::ConvertToColumn(char const*) const(&puStack_80,&UNK_029cd2ff/*"MP"*/);
  if (plVar6 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964324/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\InteroperateParameter.cpp"*/,0x207,&UNK_0296448a/*"m_pCSV is null."*/);
  }
  (**(code **)(*plVar6 + 0x58))(plVar6,(long)iVar3,(long)iVar4 + 1);
  if ((abStack_b0[0] & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_a0);
  }
  if ((abStack_98[0] & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_88);
  }
  puStack_80 = puVar1 + 0x10;
  (**(code **)(*plVar6 + 8))(plVar6);
  lVar2 = lStack_70;
  plStack_78 = (long *)0x0;
  if (lStack_70 != 0) {
    std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, unsigned long>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, unsigned long>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, unsigned long>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, unsigned long>, void*>*)(lStack_70,*(undefined8 *)(lStack_70 + 8));
    operator delete(void*)(lVar2);
    lStack_70 = 0;
  }
  lVar2 = lStack_68;
  if (lStack_68 != 0) {
    std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, unsigned long>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, unsigned long>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, unsigned long>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, unsigned long>, void*>*)(lStack_68,*(undefined8 *)(lStack_68 + 8));
    operator delete(void*)(lVar2);
    lStack_68 = 0;
  }
  puStack_58 = puVar1 + 0x10;
  (**(code **)(*plVar5 + 8))(plVar5);
  lVar2 = lStack_48;
  plStack_50 = (long *)0x0;
  if (lStack_48 != 0) {
    std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, unsigned long>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, unsigned long>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, unsigned long>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, unsigned long>, void*>*)(lStack_48,*(undefined8 *)(lStack_48 + 8));
    operator delete(void*)(lVar2);
    lStack_48 = 0;
  }
  lVar2 = lStack_40;
  if (lStack_40 != 0) {
    std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, unsigned long>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, unsigned long>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, unsigned long>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, unsigned long>, void*>*)(lStack_40,*(undefined8 *)(lStack_40 + 8));
    operator delete(void*)(lVar2);
  }
  puVar1 = puVar1 + 0x10;
  plStack_50 = (long *)0x0;
  uStack_34 = 0;
  lStack_48 = 0;
  lStack_40 = 0;
  puStack_58 = puVar1;
  Framework::CInteroperateParameter::Initialize(char const*, unsigned int, Framework::CInteroperateParameter::ICSVAccessor*)(&puStack_58,&UNK_029645e9,0,0);
  puStack_58 = puVar1;
  if (plStack_50 != (long *)0x0) {
    (**(code **)(*plStack_50 + 8))();
    plStack_50 = (long *)0x0;
  }
  lVar2 = lStack_48;
  if (lStack_48 != 0) {
    std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, unsigned long>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, unsigned long>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, unsigned long>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, unsigned long>, void*>*)(lStack_48,*(undefined8 *)(lStack_48 + 8));
    operator delete(void*)(lVar2);
    lStack_48 = 0;
  }
  lVar2 = lStack_40;
  if (lStack_40 != 0) {
    std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, unsigned long>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, unsigned long>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, unsigned long>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, unsigned long>, void*>*)(lStack_40,*(undefined8 *)(lStack_40 + 8));
    operator delete(void*)(lVar2);
  }
  return;
}

// ==== Framework::CInteroperateParameter::TCSVAccessor<Framework::CACSV>::~TCSVAccessor()
// vaddr 0x1e8892c | ghidra 0x1f8892c | size 20 | symbol _ZN9Framework22CInteroperateParameter12TCSVAccessorINS_5CACSVEED2Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN9Framework22CInteroperateParameter12TCSVAccessorINS_5CACSVEED2Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN9Framework22CInteroperateParameter12TCSVAccessorINS_5CACSVEEE_02cb8080
                   + 0x10);
  (*(code *)PTR__ZN9Framework5CACSVD1Ev_02cab4a0)(param_1 + 1);
  return;
}

// ==== Framework::CInteroperateParameter::TCSVAccessor<Framework::CACSV>::~TCSVAccessor()
// vaddr 0x1e88940 | ghidra 0x1f88940 | size 40 | symbol _ZN9Framework22CInteroperateParameter12TCSVAccessorINS_5CACSVEED0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN9Framework22CInteroperateParameter12TCSVAccessorINS_5CACSVEED0Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN9Framework22CInteroperateParameter12TCSVAccessorINS_5CACSVEEE_02cb8080
                   + 0x10);
  Framework::CACSV::~CACSV()(param_1 + 1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Framework::CInteroperateParameter::TCSVAccessor<Framework::CCSV>::~TCSVAccessor()
// vaddr 0x1e88aec | ghidra 0x1f88aec | size 20 | symbol _ZN9Framework22CInteroperateParameter12TCSVAccessorINS_4CCSVEED2Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN9Framework22CInteroperateParameter12TCSVAccessorINS_4CCSVEED2Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN9Framework22CInteroperateParameter12TCSVAccessorINS_4CCSVEEE_02cbae58 +
                   0x10);
  (*(code *)PTR__ZN9Framework4CCSVD1Ev_02c9a310)(param_1 + 1);
  return;
}

// ==== Framework::CInteroperateParameter::TCSVAccessor<Framework::CCSV>::~TCSVAccessor()
// vaddr 0x1e88b00 | ghidra 0x1f88b00 | size 40 | symbol _ZN9Framework22CInteroperateParameter12TCSVAccessorINS_4CCSVEED0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN9Framework22CInteroperateParameter12TCSVAccessorINS_4CCSVEED0Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN9Framework22CInteroperateParameter12TCSVAccessorINS_4CCSVEEE_02cbae58 +
                   0x10);
  Framework::CCSV::~CCSV()(param_1 + 1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}


// FAILED to create function at 02964710 typeinfo name for Framework::CInteroperateParameter::TCSVAccessor<Framework::CACSV>
// FAILED to create function at 02964750 typeinfo name for Framework::CInteroperateParameter::ICSVAccessor
// FAILED to create function at 02964790 typeinfo name for Framework::CInteroperateParameter::TCSVAccessor<Framework::CCSV>
// FAILED to create function at 02ba8f98 Framework::CInteroperateParameter::vtable
// FAILED to create function at 02ba8fd0 Framework::CInteroperateParameter::typeinfo
// FAILED to create function at 02ba8ff8 Framework::CInteroperateParameter::TCSVAccessor<Framework::CACSV>::vtable
// FAILED to create function at 02ba9088 Framework::CInteroperateParameter::ICSVAccessor::typeinfo
// FAILED to create function at 02ba90a0 Framework::CInteroperateParameter::TCSVAccessor<Framework::CACSV>::typeinfo
// FAILED to create function at 02ba90b8 Framework::CInteroperateParameter::TCSVAccessor<Framework::CCSV>::vtable
// FAILED to create function at 02ba9150 Framework::CInteroperateParameter::TCSVAccessor<Framework::CCSV>::typeinfo
// FAILED to create function at 02d004e0 Framework::CInteroperateParameter::m_pDefaultKey
// FAILED to create function at 02d004e8 Framework::CInteroperateParameter::m_pDefaultKeyWord
