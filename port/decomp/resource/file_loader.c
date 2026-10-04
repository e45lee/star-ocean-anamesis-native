// port/decomp/resource/file_loader.c: Ghidra decompiles for the resource subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-04 06:12 UTC: tools/decomp.sh '--into' 'resource/file_loader' 'Framework::CFileLoader::'

// ==== Framework::CFileLoader::CFileLoader()
// vaddr 0x1e828f4 | ghidra 0x1f828f4 | size 144 | symbol _ZN9Framework11CFileLoaderC2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework11CFileLoaderC1Ev(long *param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  uint7 uStack_2f;
  
  puVar2 = PTR__ZTVN9Framework11CFileLoaderE_02cb9740;
  *(undefined1 *)(param_1 + 6) = 0;
  *(undefined4 *)(param_1 + 1) = 0xffffffff;
  puVar1 = PTR__ZTVN4Aska4FileE_02cb6e28;
  *param_1 = (long)(puVar2 + 0x10);
  *(undefined1 *)(param_1 + 8) = 0;
  param_1[3] = 0;
  param_1[2] = 0;
  param_1[5] = 0;
  param_1[4] = 0;
  param_1[7] = (long)(puVar1 + 0x10);
  memset(param_1 + 9,0,0x51);
  Framework::CHash32::CHash32()(param_1 + 0x14);
  param_1[0x17] = 0;
  *(undefined1 *)(param_1 + 0x16) = 1;
  param_1[9] = 0;
  param_1[8] = (ulong)uStack_2f << 8;
  return;
}

// ==== Framework::CFileLoader::DummySize(unsigned long)
// vaddr 0x1e82984 | ghidra 0x1f82984 | size 68 | symbol _ZN9Framework11CFileLoader9DummySizeEm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework11CFileLoader9DummySizeEm(long param_1,undefined8 param_2)

{
  if (*(int *)(param_1 + 8) != -1) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296396a/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\FileLoader.cpp"*/,0x30,&UNK_027f6dcb/*"Already initialized.(%d)"*/);
  }
  *(undefined8 *)(param_1 + 0x28) = param_2;
  return;
}

// ==== Framework::CFileLoader::Initialize(unsigned int, unsigned long, bool)
// vaddr 0x1e829c8 | ghidra 0x1f829c8 | size 552 | symbol _ZN9Framework11CFileLoader10InitializeEjmb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework11CFileLoader10InitializeEjmb
               (long param_1,undefined4 param_2,undefined8 param_3,ulong param_4)

{
  byte bVar1;
  uint uVar2;
  ulong uVar3;
  undefined8 uVar4;
  long lVar5;
  undefined8 uVar6;
  undefined1 auStack_48 [8];
  uint uStack_40;
  undefined4 uStack_3c;
  undefined8 uStack_38;
  
  uVar6 = *(undefined8 *)PTR__ZN4Aska6Global18m_pFileReadManagerE_02cbf970;
  if (*(int *)(param_1 + 8) != -1) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296396a/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\FileLoader.cpp"*/,0x3c,&UNK_027f6dcb/*"Already initialized.(%d)"*/);
  }
  *(undefined4 *)(param_1 + 8) = param_2;
  uVar3 = Aska::FileReadManager::FileExists(int) const(uVar6,param_2);
  if ((uVar3 & 1) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296396a/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\FileLoader.cpp"*/,0x3e,&UNK_029639c0/*"File not found.(%d)"*/,*(undefined4 *)(param_1 + 8));
  }
  *(undefined8 *)(param_1 + 0xb8) = 0;
  uVar4 = Framework::FileID::gpFileName(unsigned int)(*(undefined4 *)(param_1 + 8));
  *(undefined8 *)(param_1 + 0x10) = uVar4;
  lVar5 = Aska::FileReadManager::CalcFileLength(int) const(uVar6,*(undefined4 *)(param_1 + 8));
  *(long *)(param_1 + 0x20) = lVar5;
  if (lVar5 == 0) {
    uVar4 = Framework::FileID::gpFileName(unsigned int)(*(undefined4 *)(param_1 + 8));
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296396a/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\FileLoader.cpp"*/,0x45,&UNK_029639d4/*"The file [%s]'s size is zero."*/,uVar4);
    lVar5 = *(long *)(param_1 + 0x18);
  }
  else {
    lVar5 = *(long *)(param_1 + 0x18);
  }
  if (lVar5 != 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296396a/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\FileLoader.cpp"*/,0x47,&UNK_029639f2/*"m_pBuffer isn't null.(%08x)"*/);
  }
  lVar5 = *(long *)(param_1 + 0x28) + *(long *)(param_1 + 0x20);
  if ((param_4 & 1) == 0) {
    uVar4 = operator new[](unsigned long, unsigned long, bool)(lVar5,param_3,1);
  }
  else {
    uVar4 = Framework::gMAllocHigh(unsigned long, unsigned long)(lVar5,param_3);
  }
  *(undefined8 *)(param_1 + 0x18) = uVar4;
  memset(uVar4,0,*(long *)(param_1 + 0x28) + *(long *)(param_1 + 0x20));
  if (*(char *)(param_1 + 0x30) != '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296396a/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\FileLoader.cpp"*/,0x50,&UNK_02963a0e/*"Internal error. m_IsLoading is already true."*/);
  }
  *(undefined1 *)(param_1 + 0x30) = 1;
  uVar3 = Aska::FileReadManager::Read(int, unsigned char*, Aska::INotify*, unsigned long, unsigned long, int, int, bool)(uVar6,*(undefined4 *)(param_1 + 8),*(undefined8 *)(param_1 + 0x18),param_1
                          ,*(undefined8 *)(param_1 + 0x20),0,0,0,1);
  if ((uVar3 & 1) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296396a/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\FileLoader.cpp"*/,0x68,&UNK_02963a3b/*"FileReadManager read failed.(Queue full)"*/);
  }
  if (*(long *)(param_1 + 0x28) != 0) {
    memset(*(long *)(param_1 + 0x18) + *(long *)(param_1 + 0x20),0);
  }
  uVar2 = uStack_40;
  uStack_40 = uStack_40 & 0xffffff00;
  uStack_38 = 0;
  *(undefined8 *)(param_1 + 0x48) = 0;
  *(ulong *)(param_1 + 0x40) = CONCAT44(uStack_3c,uVar2) & 0xffffffffffffff00;
  if ((*(byte *)(param_1 + 0x50) & 1) == 0) {
    *(undefined2 *)(param_1 + 0x50) = 0;
    bVar1 = *(byte *)(param_1 + 0x68);
  }
  else {
    **(undefined1 **)(param_1 + 0x60) = 0;
    *(undefined8 *)(param_1 + 0x58) = 0;
    bVar1 = *(byte *)(param_1 + 0x68);
  }
  if ((bVar1 & 1) == 0) {
    *(undefined2 *)(param_1 + 0x68) = 0;
  }
  else {
    **(undefined1 **)(param_1 + 0x78) = 0;
    *(undefined8 *)(param_1 + 0x70) = 0;
  }
  *(undefined1 *)(param_1 + 0x98) = 0;
  Framework::CHash32::CHash32()(auStack_48);
  *(uint *)(param_1 + 0xa8) = uStack_40;
  Framework::CHash32::~CHash32()(auStack_48);
  return;
}

// ==== Framework::CFileLoader::BufferOffset(unsigned long)
// vaddr 0x1e82bf0 | ghidra 0x1f82bf0 | size 68 | symbol _ZN9Framework11CFileLoader12BufferOffsetEm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework11CFileLoader12BufferOffsetEm(long param_1,ulong param_2)

{
  if (*(ulong *)(param_1 + 0x20) < param_2) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296396a/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\FileLoader.cpp"*/,0x27e,&UNK_02963c0e);
  }
  *(ulong *)(param_1 + 0xb8) = param_2;
  return;
}

// ==== Framework::CFileLoader::QueryToExternalProcessCache(char const*)
// vaddr 0x1e82c34 | ghidra 0x1f82c34 | size 8 | symbol _ZN9Framework11CFileLoader27QueryToExternalProcessCacheEPKc | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN9Framework11CFileLoader27QueryToExternalProcessCacheEPKc(void)

{
  return 0;
}

// ==== Framework::CFileLoader::InitializeDefaultDirectLoadFolder()
// vaddr 0x1e82c3c | ghidra 0x1f82c3c | size 84 | symbol _ZN9Framework11CFileLoader33InitializeDefaultDirectLoadFolderEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework11CFileLoader33InitializeDefaultDirectLoadFolderEv(void)

{
  undefined *puVar1;
  undefined8 *puVar2;
  
  puVar1 = PTR__ZN9Framework11CFileLoader29gpDefalutDirectLoadRootFolderE_02cbbba8;
  if (*(long *)PTR__ZN9Framework11CFileLoader29gpDefalutDirectLoadRootFolderE_02cbbba8 != 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296396a/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\FileLoader.cpp"*/,0xeb,&UNK_02963a64/*"CFileLoader::gpDefalutDirectLoadRootFolder isn't null.(%08x)"*/);
  }
  puVar2 = (undefined8 *)operator new(unsigned long, std::nothrow_t const&)(0x18,PTR__ZSt7nothrow_02cb9a80);
  if (puVar2 != (undefined8 *)0x0) {
    puVar2[1] = 0;
    puVar2[2] = 0;
    *puVar2 = 0;
  }
  *(undefined8 **)puVar1 = puVar2;
  return;
}

// ==== Framework::CFileLoader::ReleaseDefaultDirectLoadFolder()
// vaddr 0x1e82c90 | ghidra 0x1f82c90 | size 64 | symbol _ZN9Framework11CFileLoader30ReleaseDefaultDirectLoadFolderEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework11CFileLoader30ReleaseDefaultDirectLoadFolderEv(void)

{
  undefined *puVar1;
  byte *pbVar2;
  
  puVar1 = PTR__ZN9Framework11CFileLoader29gpDefalutDirectLoadRootFolderE_02cbbba8;
  pbVar2 = *(byte **)PTR__ZN9Framework11CFileLoader29gpDefalutDirectLoadRootFolderE_02cbbba8;
  if (pbVar2 != (byte *)0x0) {
    if ((*pbVar2 & 1) != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(*(undefined8 *)(pbVar2 + 0x10));
    }
    operator delete(void*)(pbVar2);
    *(undefined8 *)puVar1 = 0;
  }
  return;
}

// ==== Framework::CFileLoader::SetDefaultDirectLoadFolder(char const*)
// vaddr 0x1e82cd0 | ghidra 0x1f82cd0 | size 252 | symbol _ZN9Framework11CFileLoader26SetDefaultDirectLoadFolderEPKc | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework11CFileLoader26SetDefaultDirectLoadFolderEPKc(undefined8 param_1)

{
  undefined *puVar1;
  ulong uVar2;
  ulong uVar3;
  long lVar4;
  ulong uVar5;
  ulong *puVar6;
  byte *pbVar7;
  
  puVar1 = PTR__ZN9Framework11CFileLoader29gpDefalutDirectLoadRootFolderE_02cbbba8;
  puVar6 = *(ulong **)PTR__ZN9Framework11CFileLoader29gpDefalutDirectLoadRootFolderE_02cbbba8;
  if (puVar6 == (ulong *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296396a/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\FileLoader.cpp"*/,0xf6,&UNK_02963aa1/*"gpDefalutDirectLoadRootFolder is null."*/);
    puVar6 = *(ulong **)puVar1;
  }
  uVar2 = strlen(param_1);
  uVar5 = (ulong)(byte)*puVar6;
  if (((byte)*puVar6 & 1) == 0) {
    uVar3 = 0x16;
    lVar4 = uVar2 - 0x16;
    if (0x15 < uVar2 && lVar4 != 0) {
code_r0x01f82d50:
      if ((uVar5 & 1) == 0) {
        uVar5 = (ulong)(((uint)uVar5 & 0xfe) >> 1);
      }
      else {
        uVar5 = puVar6[1];
      }
      (*(code *)
        PTR__ZNSt6__ndk112basic_stringIcNS_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS3_22CSTLStringAllocatorInfEEEE21__grow_by_and_replaceEmmmmmmPKc_02ca6d40
      )(puVar6,uVar3,lVar4,uVar5,0,uVar5,uVar2,param_1);
      return;
    }
  }
  else {
    uVar5 = *puVar6;
    uVar3 = (uVar5 & 0xfffffffffffffffe) - 1;
    lVar4 = uVar2 - uVar3;
    if (uVar3 <= uVar2 && lVar4 != 0) goto code_r0x01f82d50;
  }
  if ((uVar5 & 1) == 0) {
    pbVar7 = (byte *)((long)puVar6 + 1);
  }
  else {
    pbVar7 = (byte *)puVar6[2];
  }
  if (uVar2 != 0) {
    memmove(pbVar7,param_1,uVar2);
  }
  pbVar7[uVar2] = 0;
  if ((*puVar6 & 1) == 0) {
    *(byte *)puVar6 = (byte)(uVar2 << 1);
  }
  else {
    puVar6[1] = uVar2;
  }
  return;
}

// ==== Framework::CFileLoader::ResetDefaultDirectLoadFolder()
// vaddr 0x1e82dcc | ghidra 0x1f82dcc | size 96 | symbol _ZN9Framework11CFileLoader28ResetDefaultDirectLoadFolderEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework11CFileLoader28ResetDefaultDirectLoadFolderEv(void)

{
  byte bVar1;
  undefined *puVar2;
  byte *pbVar3;
  
  puVar2 = PTR__ZN9Framework11CFileLoader29gpDefalutDirectLoadRootFolderE_02cbbba8;
  pbVar3 = *(byte **)PTR__ZN9Framework11CFileLoader29gpDefalutDirectLoadRootFolderE_02cbbba8;
  if (pbVar3 == (byte *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296396a/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\FileLoader.cpp"*/,0xfc,&UNK_02963aa1/*"gpDefalutDirectLoadRootFolder is null."*/);
    pbVar3 = *(byte **)puVar2;
    bVar1 = *pbVar3;
  }
  else {
    bVar1 = *pbVar3;
  }
  if ((bVar1 & 1) == 0) {
    pbVar3[0] = 0;
    pbVar3[1] = 0;
    return;
  }
  **(undefined1 **)(pbVar3 + 0x10) = 0;
  pbVar3[8] = 0;
  pbVar3[9] = 0;
  pbVar3[10] = 0;
  pbVar3[0xb] = 0;
  pbVar3[0xc] = 0;
  pbVar3[0xd] = 0;
  pbVar3[0xe] = 0;
  pbVar3[0xf] = 0;
  return;
}

// ==== Framework::CFileLoader::pDefaultDirectLoadFolder()
// vaddr 0x1e82e2c | ghidra 0x1f82e2c | size 88 | symbol _ZN9Framework11CFileLoader24pDefaultDirectLoadFolderEv | lib libSOA-3.7.0.so | 2026-10-04
byte * _ZN9Framework11CFileLoader24pDefaultDirectLoadFolderEv(void)

{
  byte bVar1;
  undefined *puVar2;
  byte *pbVar3;
  
  puVar2 = PTR__ZN9Framework11CFileLoader29gpDefalutDirectLoadRootFolderE_02cbbba8;
  pbVar3 = *(byte **)PTR__ZN9Framework11CFileLoader29gpDefalutDirectLoadRootFolderE_02cbbba8;
  if (pbVar3 == (byte *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296396a/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\FileLoader.cpp"*/,0x102,&UNK_02963aa1/*"gpDefalutDirectLoadRootFolder is null."*/);
    pbVar3 = *(byte **)puVar2;
    bVar1 = *pbVar3;
  }
  else {
    bVar1 = *pbVar3;
  }
  if ((bVar1 & 1) == 0) {
    return pbVar3 + 1;
  }
  return *(byte **)(pbVar3 + 0x10);
}

// ==== Framework::CFileLoader::InitializeByDirectFile(char const*, unsigned long, bool)
// vaddr 0x1e82e84 | ghidra 0x1f82e84 | size 1452 | symbol _ZN9Framework11CFileLoader22InitializeByDirectFileEPKcmb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework11CFileLoader22InitializeByDirectFileEPKcmb
               (long param_1,undefined8 param_2,undefined8 param_3,ulong param_4)

{
  byte bVar1;
  byte bVar2;
  ulong uVar3;
  long *plVar4;
  undefined8 uVar5;
  ulong uVar6;
  long lVar7;
  ulong uVar8;
  ulong *puVar9;
  byte *pbVar10;
  long lVar11;
  ulong uVar12;
  ulong uStack_70;
  ulong uStack_68;
  ulong uStack_60;
  
  if (*(int *)(param_1 + 8) != -1) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296396a/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\FileLoader.cpp"*/,0x10b,&UNK_027f6dcb/*"Already initialized.(%d)"*/);
  }
  *(undefined4 *)(param_1 + 8) = 0xfffffffe;
  *(undefined **)(param_1 + 0x10) = &UNK_02963ac8/*"DummyFileByDirectFile"*/;
  if (*(char *)(param_1 + 0x98) != '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296396a/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\FileLoader.cpp"*/,0x10f,&UNK_02963ade/*"Already DirectOpenedFile."*/);
  }
  if (*(long *)(param_1 + 0x48) != 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296396a/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\FileLoader.cpp"*/,0x110,&UNK_02963af8/*"m_DirectOpenedFile is already used."*/);
  }
  bVar1 = *(byte *)(param_1 + 0x80);
  if ((bVar1 & 1) == 0) {
    if (bVar1 >> 1 == 0) goto code_r0x01f82f7c;
code_r0x01f82f38:
    puVar9 = (ulong *)(param_1 + 0x68);
    uVar8 = (ulong)*(byte *)puVar9;
    uVar3 = *(ulong *)(param_1 + 0x88);
    lVar7 = *(long *)(param_1 + 0x90);
    if ((bVar1 & 1) == 0) {
      lVar7 = param_1 + 0x81;
      uVar3 = (ulong)(bVar1 >> 1);
    }
    if ((*(byte *)puVar9 & 1) == 0) {
      uVar6 = 0x16;
      lVar11 = uVar3 - 0x16;
      if (0x15 < uVar3 && lVar11 != 0) goto code_r0x01f82fc4;
code_r0x01f82f64:
      if ((uVar8 & 1) == 0) {
        lVar11 = param_1 + 0x69;
      }
      else {
        lVar11 = *(long *)(param_1 + 0x78);
      }
      if (uVar3 != 0) {
        memmove(lVar11,lVar7,uVar3);
      }
      *(undefined1 *)(lVar11 + uVar3) = 0;
      if ((*(byte *)puVar9 & 1) == 0) {
        *(byte *)puVar9 = (byte)(uVar3 << 1);
      }
      else {
        *(ulong *)(param_1 + 0x70) = uVar3;
      }
    }
    else {
      uVar8 = *puVar9;
      uVar6 = (uVar8 & 0xfffffffffffffffe) - 1;
      lVar11 = uVar3 - uVar6;
      if (uVar3 < uVar6 || lVar11 == 0) goto code_r0x01f82f64;
code_r0x01f82fc4:
      if ((uVar8 & 1) == 0) {
        uVar8 = (ulong)(((uint)uVar8 & 0xfe) >> 1);
      }
      else {
        uVar8 = *(ulong *)(param_1 + 0x70);
      }
      string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(puVar9,uVar6,lVar11,uVar8,0,uVar8,uVar3);
    }
  }
  else {
    if (*(long *)(param_1 + 0x88) != 0) goto code_r0x01f82f38;
code_r0x01f82f7c:
    uStack_70 = 0;
    uStack_68 = 0;
    uStack_60 = 0;
    puVar9 = *(ulong **)PTR__ZN9Framework11CFileLoader29gpDefalutDirectLoadRootFolderE_02cbbba8;
    if (puVar9 == (ulong *)0x0) {
      uStack_70 = 0;
    }
    else if ((*puVar9 & 1) == 0) {
      uStack_60 = puVar9[2];
      uStack_68 = puVar9[1];
      uStack_70 = *puVar9;
    }
    else {
      uVar3 = puVar9[1];
      uVar8 = puVar9[2];
      if (uVar3 < 0x17) {
        uVar12 = (ulong)&uStack_70 | 1;
        uStack_70 = (uVar3 & 0x7f) << 1;
        if (uVar3 != 0) goto code_r0x01f830b8;
      }
      else {
        uVar6 = uVar3 + 0x10 & 0xfffffffffffffff0;
        if (uVar6 == 0) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296188c/*"C:\BAS_Submission\Client\Library\Framework\Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
        }
        uVar12 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar6,&UNK_029618d8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/STL_String.h"*/,0x1c);
        if (uVar12 == 0) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296188c/*"C:\BAS_Submission\Client\Library\Framework\Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
        }
        uStack_70 = uVar6 | 1;
        uStack_68 = uVar3;
        uStack_60 = uVar12;
code_r0x01f830b8:
        memcpy(uVar12,uVar8,uVar3);
      }
      *(undefined1 *)(uVar12 + uVar3) = 0;
    }
    puVar9 = (ulong *)(param_1 + 0x68);
    if ((*(byte *)puVar9 & 1) == 0) {
      *(undefined2 *)puVar9 = 0;
    }
    else {
      **(undefined1 **)(param_1 + 0x78) = 0;
      *(undefined8 *)(param_1 + 0x70) = 0;
    }
    string::reserve(unsigned long)(puVar9,0);
    *(ulong *)(param_1 + 0x78) = uStack_60;
    *(ulong *)(param_1 + 0x70) = uStack_68;
    *puVar9 = uStack_70;
  }
  pbVar10 = (byte *)(param_1 + 0x68);
  uVar3 = strlen(param_2);
  bVar1 = *pbVar10;
  uVar8 = (ulong)bVar1;
  if ((bVar1 & 1) == 0) {
    lVar7 = 0x16;
    if ((bVar1 & 1) == 0) goto code_r0x01f8313c;
code_r0x01f83124:
    uVar6 = *(ulong *)(param_1 + 0x70);
  }
  else {
    uVar8 = *(ulong *)(param_1 + 0x68);
    lVar7 = (uVar8 & 0xfffffffffffffffe) - 1;
    if ((uVar8 & 1) != 0) goto code_r0x01f83124;
code_r0x01f8313c:
    uVar6 = (ulong)(((uint)uVar8 & 0xfe) >> 1);
  }
  if (lVar7 - uVar6 < uVar3) {
    string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(pbVar10,lVar7,(uVar3 - lVar7) + uVar6,uVar6,uVar6,0,uVar3,param_2);
  }
  else if (uVar3 != 0) {
    if ((uVar8 & 1) == 0) {
      lVar7 = param_1 + 0x69;
    }
    else {
      lVar7 = *(long *)(param_1 + 0x78);
    }
    memcpy(lVar7 + uVar6,param_2,uVar3);
    lVar11 = uVar6 + uVar3;
    if ((*pbVar10 & 1) == 0) {
      *pbVar10 = (char)lVar11 * '\x02';
    }
    else {
      *(long *)(param_1 + 0x70) = lVar11;
    }
    *(undefined1 *)(lVar7 + lVar11) = 0;
  }
  *(undefined1 *)(param_1 + 0x98) = 1;
  if ((*(byte *)(param_1 + 0x68) & 1) == 0) {
    uVar3 = param_1 + 0x69;
  }
  else {
    uVar3 = *(ulong *)(param_1 + 0x78);
  }
  plVar4 = *(long **)(PTR__ZN9Framework11CFileLoader31m_AssetManagerEvalutionFunctionE_02cb7c98 +
                     0x20);
  if (plVar4 == (long *)0x0) {
    bVar2 = 0;
    *(undefined8 *)(param_1 + 0xb8) = 0;
    bVar1 = 0;
    if ((*(byte *)(param_1 + 0x68) & 1) == 0) goto code_r0x01f8320c;
code_r0x01f83220:
    lVar7 = *(long *)(param_1 + 0x78);
  }
  else {
    uStack_70 = uVar3;
    bVar2 = (**(code **)(*plVar4 + 0x30))(plVar4,&uStack_70);
    *(undefined8 *)(param_1 + 0xb8) = 0;
    bVar1 = bVar2;
    if ((*pbVar10 & 1) != 0) goto code_r0x01f83220;
code_r0x01f8320c:
    bVar2 = bVar1;
    lVar7 = param_1 + 0x69;
  }
  lVar7 = Aska::File::GetFileSizeL(char const*, bool)(lVar7,bVar2 & 1);
  *(long *)(param_1 + 0x20) = lVar7;
  if (lVar7 == 0) {
    if ((*pbVar10 & 1) == 0) {
      lVar7 = param_1 + 0x69;
    }
    else {
      lVar7 = *(long *)(param_1 + 0x78);
    }
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296396a/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\FileLoader.cpp"*/,0x12a,&UNK_02963b1c/*"File not found or there is no size of this file.[%s]"*/,lVar7);
  }
  if (*(long *)(param_1 + 0x18) != 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296396a/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\FileLoader.cpp"*/,300,&UNK_029639f2/*"m_pBuffer isn't null.(%08x)"*/);
  }
  lVar7 = *(long *)(param_1 + 0x28) + *(long *)(param_1 + 0x20);
  if ((param_4 & 1) == 0) {
    uVar5 = operator new[](unsigned long, unsigned long, bool)(lVar7,param_3,1);
  }
  else {
    uVar5 = Framework::gMAllocHigh(unsigned long, unsigned long)(lVar7,param_3);
  }
  *(undefined8 *)(param_1 + 0x18) = uVar5;
  if (*(char *)(param_1 + 0x30) != '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296396a/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\FileLoader.cpp"*/,0x132,&UNK_02963a0e/*"Internal error. m_IsLoading is already true."*/);
  }
  *(undefined1 *)(param_1 + 0x30) = 1;
  uVar3 = strlen(param_2);
  puVar9 = (ulong *)(param_1 + 0x50);
  uVar8 = (ulong)*(byte *)puVar9;
  if ((*(byte *)puVar9 & 1) == 0) {
    uVar6 = 0x16;
    lVar7 = uVar3 - 0x16;
    if (0x15 < uVar3 && lVar7 != 0) {
code_r0x01f83318:
      if ((uVar8 & 1) == 0) {
        uVar8 = (ulong)(((uint)uVar8 & 0xfe) >> 1);
      }
      else {
        uVar8 = *(ulong *)(param_1 + 0x58);
      }
      string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(puVar9,uVar6,lVar7,uVar8,0,uVar8,uVar3,param_2);
      goto code_r0x01f8337c;
    }
  }
  else {
    uVar8 = *puVar9;
    uVar6 = (uVar8 & 0xfffffffffffffffe) - 1;
    lVar7 = uVar3 - uVar6;
    if (uVar6 <= uVar3 && lVar7 != 0) goto code_r0x01f83318;
  }
  if ((uVar8 & 1) == 0) {
    lVar7 = param_1 + 0x51;
  }
  else {
    lVar7 = *(long *)(param_1 + 0x60);
  }
  if (uVar3 != 0) {
    memmove(lVar7,param_2,uVar3);
  }
  *(undefined1 *)(lVar7 + uVar3) = 0;
  if ((*(byte *)puVar9 & 1) == 0) {
    *(byte *)puVar9 = (byte)(uVar3 << 1);
  }
  else {
    *(ulong *)(param_1 + 0x58) = uVar3;
  }
code_r0x01f8337c:
  Framework::CHash32::CHash32(string const&)(&uStack_70,puVar9);
  *(undefined4 *)(param_1 + 0xa8) = (undefined4)uStack_68;
  Framework::CHash32::~CHash32()(&uStack_70);
  if ((*(byte *)(param_1 + 0x68) & 1) == 0) {
    lVar7 = param_1 + 0x69;
  }
  else {
    lVar7 = *(long *)(param_1 + 0x78);
  }
  uVar3 = Aska::FileReadManager::Read(char const*, unsigned char*, Aska::INotify*, unsigned long, unsigned long, int, int, bool, bool)(*(undefined8 *)PTR__ZN4Aska6Global18m_pFileReadManagerE_02cbf970,lVar7,
                          *(undefined8 *)(param_1 + 0x18),param_1,*(undefined8 *)(param_1 + 0x20),0,
                          0,0,1,bVar2 & 1);
  if ((uVar3 & 1) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296396a/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\FileLoader.cpp"*/,0x146,&UNK_02963a3b/*"FileReadManager read failed.(Queue full)"*/);
  }
  if (*(long *)(param_1 + 0x28) != 0) {
    memset(*(long *)(param_1 + 0x18) + *(long *)(param_1 + 0x20),0);
  }
  return;
}

// ==== Framework::CFileLoader::IsAssetManagerPath(char const*)
// vaddr 0x1e83430 | ghidra 0x1f83430 | size 68 | symbol _ZN9Framework11CFileLoader18IsAssetManagerPathEPKc | lib libSOA-3.7.0.so | 2026-10-04
uint _ZN9Framework11CFileLoader18IsAssetManagerPathEPKc(undefined8 param_1)

{
  uint uVar1;
  long *plVar2;
  undefined8 uStack_8;
  
  plVar2 = *(long **)(PTR__ZN9Framework11CFileLoader31m_AssetManagerEvalutionFunctionE_02cb7c98 +
                     0x20);
  if (plVar2 != (long *)0x0) {
    uStack_8 = param_1;
    uVar1 = (**(code **)(*plVar2 + 0x30))(plVar2,&uStack_8);
    return uVar1 & 1;
  }
  return 0;
}

// ==== Framework::CFileLoader::EnableDirectLoad(char const*)
// vaddr 0x1e83474 | ghidra 0x1f83474 | size 216 | symbol _ZN9Framework11CFileLoader16EnableDirectLoadEPKc | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework11CFileLoader16EnableDirectLoadEPKc(long param_1,undefined8 param_2)

{
  ulong uVar1;
  ulong uVar2;
  ulong uVar3;
  ulong *puVar4;
  long lVar5;
  
  uVar1 = strlen(param_2);
  puVar4 = (ulong *)(param_1 + 0x80);
  uVar3 = (ulong)*(byte *)puVar4;
  if ((*(byte *)puVar4 & 1) == 0) {
    uVar2 = 0x16;
    lVar5 = uVar1 - 0x16;
    if (0x15 < uVar1 && lVar5 != 0) {
code_r0x01f834d0:
      if ((uVar3 & 1) == 0) {
        uVar3 = (ulong)(((uint)uVar3 & 0xfe) >> 1);
      }
      else {
        uVar3 = *(ulong *)(param_1 + 0x88);
      }
      (*(code *)
        PTR__ZNSt6__ndk112basic_stringIcNS_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS3_22CSTLStringAllocatorInfEEEE21__grow_by_and_replaceEmmmmmmPKc_02ca6d40
      )(puVar4,uVar2,lVar5,uVar3,0,uVar3,uVar1,param_2);
      return;
    }
  }
  else {
    uVar3 = *puVar4;
    uVar2 = (uVar3 & 0xfffffffffffffffe) - 1;
    lVar5 = uVar1 - uVar2;
    if (uVar2 <= uVar1 && lVar5 != 0) goto code_r0x01f834d0;
  }
  if ((uVar3 & 1) == 0) {
    lVar5 = param_1 + 0x81;
  }
  else {
    lVar5 = *(long *)(param_1 + 0x90);
  }
  if (uVar1 != 0) {
    memmove(lVar5,param_2,uVar1);
  }
  *(undefined1 *)(lVar5 + uVar1) = 0;
  if ((*(byte *)puVar4 & 1) == 0) {
    *(byte *)puVar4 = (byte)(uVar1 << 1);
  }
  else {
    *(ulong *)(param_1 + 0x88) = uVar1;
  }
  return;
}

// ==== Framework::CFileLoader::pDirectOpenedFileRelativeName() const
// vaddr 0x1e8354c | ghidra 0x1f8354c | size 136 | symbol _ZNK9Framework11CFileLoader29pDirectOpenedFileRelativeNameEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK9Framework11CFileLoader29pDirectOpenedFileRelativeNameEv(long param_1)

{
  byte bVar1;
  
  if (*(char *)(param_1 + 0x98) == '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296396a/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\FileLoader.cpp"*/,0x156,&UNK_02963b51/*"Illegal access."*/);
  }
  bVar1 = *(byte *)(param_1 + 0x50);
  if ((bVar1 & 1) == 0) {
    if (bVar1 >> 1 != 0) goto joined_r0x01f83598;
  }
  else if (*(long *)(param_1 + 0x58) != 0) goto joined_r0x01f83598;
  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296396a/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\FileLoader.cpp"*/,0x157,&UNK_027f75ea/*"Internal error."*/);
  bVar1 = *(byte *)(param_1 + 0x50);
joined_r0x01f83598:
  if ((bVar1 & 1) == 0) {
    param_1 = param_1 + 0x51;
  }
  else {
    param_1 = *(long *)(param_1 + 0x60);
  }
  return param_1;
}

// ==== Framework::CFileLoader::InitializeByImmediateLoad(char const*, unsigned long, bool)
// vaddr 0x1e835d4 | ghidra 0x1f835d4 | size 428 | symbol _ZN9Framework11CFileLoader25InitializeByImmediateLoadEPKcmb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework11CFileLoader25InitializeByImmediateLoadEPKcmb
               (long param_1,undefined8 param_2,undefined8 param_3,ulong param_4)

{
  byte bVar1;
  uint uVar2;
  long lVar3;
  undefined8 uVar4;
  undefined1 auStack_148 [8];
  uint uStack_140;
  undefined4 uStack_13c;
  undefined8 uStack_138;
  undefined1 auStack_130 [256];
  
  if (*(int *)(param_1 + 8) != -1) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296396a/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\FileLoader.cpp"*/,0x163,&UNK_027f6dcb/*"Already initialized.(%d)"*/);
  }
  *(undefined4 *)(param_1 + 8) = 0xfffffffe;
  *(undefined **)(param_1 + 0x10) = &UNK_02963b61/*"DummyFileByImmediateLoad"*/;
  Aska::Global::MakeStoragePath(char*, unsigned int, char const*)(auStack_130,0xff,param_2);
  *(undefined8 *)(param_1 + 0xb8) = 0;
  lVar3 = Aska::FileReadManager::CalcFileLength(char const*, bool)(auStack_130,0);
  *(long *)(param_1 + 0x20) = lVar3;
  if (lVar3 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296396a/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\FileLoader.cpp"*/,0x16d,&UNK_02963b1c/*"File not found or there is no size of this file.[%s]"*/,param_2);
    lVar3 = *(long *)(param_1 + 0x18);
  }
  else {
    lVar3 = *(long *)(param_1 + 0x18);
  }
  if (lVar3 != 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296396a/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\FileLoader.cpp"*/,0x16f,&UNK_029639f2/*"m_pBuffer isn't null.(%08x)"*/);
  }
  lVar3 = *(long *)(param_1 + 0x28) + *(long *)(param_1 + 0x20);
  if ((param_4 & 1) == 0) {
    uVar4 = operator new[](unsigned long, unsigned long, bool)(lVar3,param_3,1);
  }
  else {
    uVar4 = Framework::gMAllocHigh(unsigned long, unsigned long)(lVar3,param_3);
  }
  *(undefined8 *)(param_1 + 0x18) = uVar4;
  if (*(char *)(param_1 + 0x30) != '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296396a/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\FileLoader.cpp"*/,0x174,&UNK_02963a0e/*"Internal error. m_IsLoading is already true."*/);
  }
  *(undefined1 *)(param_1 + 0x30) = 1;
  if (*(long *)(param_1 + 0x28) != 0) {
    memset(*(long *)(param_1 + 0x18) + *(long *)(param_1 + 0x20),0);
  }
  uVar2 = uStack_140;
  uStack_140 = uStack_140 & 0xffffff00;
  uStack_138 = 0;
  *(undefined8 *)(param_1 + 0x48) = 0;
  *(ulong *)(param_1 + 0x40) = CONCAT44(uStack_13c,uVar2) & 0xffffffffffffff00;
  if ((*(byte *)(param_1 + 0x50) & 1) == 0) {
    *(undefined2 *)(param_1 + 0x50) = 0;
    bVar1 = *(byte *)(param_1 + 0x68);
  }
  else {
    **(undefined1 **)(param_1 + 0x60) = 0;
    *(undefined8 *)(param_1 + 0x58) = 0;
    bVar1 = *(byte *)(param_1 + 0x68);
  }
  if ((bVar1 & 1) == 0) {
    *(undefined2 *)(param_1 + 0x68) = 0;
  }
  else {
    **(undefined1 **)(param_1 + 0x78) = 0;
    *(undefined8 *)(param_1 + 0x70) = 0;
  }
  *(undefined1 *)(param_1 + 0x98) = 0;
  Framework::CHash32::CHash32()(auStack_148);
  *(uint *)(param_1 + 0xa8) = uStack_140;
  Framework::CHash32::~CHash32()(auStack_148);
  return;
}

// ==== Framework::CFileLoader::gIsImmediateFileExist(char const*)
// vaddr 0x1e83780 | ghidra 0x1f83780 | size 196 | symbol _ZN9Framework11CFileLoader21gIsImmediateFileExistEPKc | lib libSOA-3.7.0.so | 2026-10-04
bool _ZN9Framework11CFileLoader21gIsImmediateFileExistEPKc(undefined *param_1)

{
  undefined *puVar1;
  bool bVar2;
  int iVar3;
  ulong uVar4;
  long *plVar5;
  undefined *puStack_a0;
  undefined1 uStack_98;
  long lStack_90;
  
  plVar5 = *(long **)(PTR__ZN9Framework11CFileLoader31m_AssetManagerEvalutionFunctionE_02cb7c98 +
                     0x20);
  if ((plVar5 == (long *)0x0) ||
     (puStack_a0 = param_1, uVar4 = (**(code **)(*plVar5 + 0x30))(plVar5,&puStack_a0),
     (uVar4 & 1) == 0)) {
    iVar3 = stat(param_1,&puStack_a0);
    return iVar3 == 0;
  }
  puVar1 = PTR__ZTVN4Aska4FileE_02cb6e28 + 0x10;
  lStack_90 = 0;
  uStack_98 = 1;
  puStack_a0 = puVar1;
  uVar4 = Aska::File::Open(char const*, bool, bool, bool)(&puStack_a0,param_1,1,0,0);
  bVar2 = (uVar4 & 1) != 0;
  if (bVar2) {
    Aska::File::Close()(&puStack_a0);
  }
  if (lStack_90 == 0) {
    return bVar2;
  }
  puStack_a0 = puVar1;
  Aska::File::Close()(&puStack_a0);
  return bVar2;
}

// ==== Framework::CFileLoader::gIsFileExist(char const*, char const*)
// vaddr 0x1e83844 | ghidra 0x1f83844 | size 656 | symbol _ZN9Framework11CFileLoader12gIsFileExistEPKcS2_ | lib libSOA-3.7.0.so | 2026-10-04
bool _ZN9Framework11CFileLoader12gIsFileExistEPKcS2_(undefined8 param_1,byte *param_2)

{
  undefined *puVar1;
  ulong uVar2;
  bool bVar3;
  int iVar4;
  ulong uVar5;
  long *plVar6;
  long lVar7;
  undefined *puVar8;
  ulong uVar9;
  ulong uStack_c8;
  ulong uStack_c0;
  undefined *puStack_b8;
  undefined *puStack_b0;
  undefined1 uStack_a8;
  long lStack_a0;
  
  if (param_2 == (byte *)0x0) {
    param_2 = *(byte **)PTR__ZN9Framework11CFileLoader29gpDefalutDirectLoadRootFolderE_02cbbba8;
    if ((*param_2 & 1) == 0) {
      param_2 = param_2 + 1;
    }
    else {
      param_2 = *(byte **)(param_2 + 0x10);
    }
  }
  if (param_2 == (byte *)0x0) {
    param_2 = &UNK_029d2011;
  }
  uStack_c0 = 0;
  puStack_b8 = (undefined *)0x0;
  uStack_c8 = 0;
  uVar5 = strlen(param_2);
  if (uVar5 < 0x17) {
    puVar8 = (undefined *)((ulong)&uStack_c8 | 1);
    uStack_c8 = CONCAT71(uStack_c8._1_7_,(char)(uVar5 << 1));
    if (uVar5 == 0) goto code_r0x01f83934;
  }
  else {
    uVar9 = uVar5 + 0x10 & 0xfffffffffffffff0;
    if (uVar9 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296188c/*"C:\BAS_Submission\Client\Library\Framework\Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
    }
    puVar8 = (undefined *)Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar9,&UNK_029618d8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/STL_String.h"*/,0x1c);
    if (puVar8 == (undefined *)0x0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296188c/*"C:\BAS_Submission\Client\Library\Framework\Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
    uStack_c8 = uVar9 | 1;
    uStack_c0 = uVar5;
    puStack_b8 = puVar8;
  }
  memcpy(puVar8,param_2,uVar5);
code_r0x01f83934:
  puVar8[uVar5] = 0;
  uVar5 = strlen(param_1);
  if ((uStack_c8 & 1) == 0) {
    lVar7 = 0x16;
    uVar9 = uStack_c8 & 0xff;
  }
  else {
    lVar7 = (uStack_c8 & 0xfffffffffffffffe) - 1;
    uVar9 = uStack_c8;
  }
  uVar2 = (ulong)(((uint)uVar9 & 0xfe) >> 1);
  if ((uVar9 & 1) != 0) {
    uVar2 = uStack_c0;
  }
  if (lVar7 - uVar2 < uVar5) {
    string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&uStack_c8,lVar7,(uVar5 - lVar7) + uVar2,uVar2,uVar2,0,uVar5,param_1);
  }
  else if (uVar5 != 0) {
    puVar8 = (undefined *)((ulong)&uStack_c8 | 1);
    if ((uVar9 & 1) != 0) {
      puVar8 = puStack_b8;
    }
    memcpy(puVar8 + uVar2,param_1,uVar5);
    uVar2 = uVar2 + uVar5;
    uVar5 = uVar2;
    if ((uStack_c8 & 1) == 0) {
      uStack_c8 = CONCAT71(uStack_c8._1_7_,(char)uVar2 * '\x02');
      uVar5 = uStack_c0;
    }
    uStack_c0 = uVar5;
    puVar8[uVar2] = 0;
  }
  plVar6 = *(long **)(PTR__ZN9Framework11CFileLoader31m_AssetManagerEvalutionFunctionE_02cb7c98 +
                     0x20);
  puVar8 = (undefined *)((ulong)&uStack_c8 | 1);
  if ((uStack_c8 & 1) != 0) {
    puVar8 = puStack_b8;
  }
  if ((plVar6 == (long *)0x0) ||
     (puStack_b0 = puVar8, uVar5 = (**(code **)(*plVar6 + 0x30))(plVar6,&puStack_b0),
     (uVar5 & 1) == 0)) {
    iVar4 = stat(puVar8,&puStack_b0);
    bVar3 = iVar4 == 0;
  }
  else {
    puVar1 = PTR__ZTVN4Aska4FileE_02cb6e28 + 0x10;
    lStack_a0 = 0;
    uStack_a8 = 1;
    puStack_b0 = puVar1;
    uVar5 = Aska::File::Open(char const*, bool, bool, bool)(&puStack_b0,puVar8,1,0,0);
    bVar3 = (uVar5 & 1) != 0;
    if (bVar3) {
      Aska::File::Close()(&puStack_b0);
    }
    puStack_b0 = puVar1;
    if (lStack_a0 != 0) {
      Aska::File::Close()(&puStack_b0);
    }
  }
  if ((uStack_c8 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puStack_b8);
  }
  return bVar3;
}

// ==== Framework::CFileLoader::SetFileNumberToInitializeByImmediateLoaded(unsigned int)
// vaddr 0x1e83ad4 | ghidra 0x1f83ad4 | size 68 | symbol _ZN9Framework11CFileLoader42SetFileNumberToInitializeByImmediateLoadedEj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework11CFileLoader42SetFileNumberToInitializeByImmediateLoadedEj
               (long param_1,undefined4 param_2)

{
  if (*(int *)(param_1 + 8) != -2) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296396a/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\FileLoader.cpp"*/,0x1e0,&UNK_02963b7a/*"Does not initialized  by InitializeByImmediateLoad.(%d)"*/);
  }
  *(undefined4 *)(param_1 + 8) = param_2;
  return;
}

// ==== Framework::CFileLoader::SetAssetManagerEvaluationFunction(std::__ndk1::function<bool (char const*)> const&)
// vaddr 0x1e83b48 | ghidra 0x1f83b48 | size 152 | symbol _ZN9Framework11CFileLoader33SetAssetManagerEvaluationFunctionERKNSt6__ndk18functionIFbPKcEEE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework11CFileLoader33SetAssetManagerEvaluationFunctionERKNSt6__ndk18functionIFbPKcEEE
               (long *param_1)

{
  long *plVar1;
  code *pcVar2;
  long alStack_40 [4];
  long *plStack_20;
  
  plStack_20 = alStack_40;
  plVar1 = (long *)param_1[4];
  if (plVar1 == (long *)0x0) {
    plStack_20 = (long *)0x0;
  }
  else if (param_1 == plVar1) {
    (**(code **)(*plVar1 + 0x18))(plVar1,alStack_40);
  }
  else {
    plStack_20 = (long *)(**(code **)(*plVar1 + 0x10))();
  }
  std::__ndk1::function<bool (char const*)>::swap(std::__ndk1::function<bool (char const*)>&)(alStack_40,
                  PTR__ZN9Framework11CFileLoader31m_AssetManagerEvalutionFunctionE_02cb7c98);
  if (alStack_40 == plStack_20) {
    pcVar2 = *(code **)(*plStack_20 + 0x20);
  }
  else {
    if (plStack_20 == (long *)0x0) {
      return;
    }
    pcVar2 = *(code **)(*plStack_20 + 0x28);
  }
  (*pcVar2)();
  return;
}

// ==== Framework::CFileLoader::SetDecryptFunction(std::__ndk1::function<void (Framework::CFileLoader*, char const*, char const*, unsigned char**, unsigned long&)> const&)
// vaddr 0x1e83c10 | ghidra 0x1f83c10 | size 152 | symbol _ZN9Framework11CFileLoader18SetDecryptFunctionERKNSt6__ndk18functionIFvPS0_PKcS5_PPhRmEEE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework11CFileLoader18SetDecryptFunctionERKNSt6__ndk18functionIFvPS0_PKcS5_PPhRmEEE
               (long *param_1)

{
  long *plVar1;
  code *pcVar2;
  long alStack_40 [4];
  long *plStack_20;
  
  plStack_20 = alStack_40;
  plVar1 = (long *)param_1[4];
  if (plVar1 == (long *)0x0) {
    plStack_20 = (long *)0x0;
  }
  else if (param_1 == plVar1) {
    (**(code **)(*plVar1 + 0x18))(plVar1,alStack_40);
  }
  else {
    plStack_20 = (long *)(**(code **)(*plVar1 + 0x10))();
  }
  std::__ndk1::function<void (Framework::CFileLoader*, char const*, char const*, unsigned char**, unsigned long&)>::swap(std::__ndk1::function<void (Framework::CFileLoader*, char const*, char const*, unsigned char**, unsigned long&)>&)(alStack_40,PTR__ZN9Framework11CFileLoader17m_DecryptFunctionE_02cc23c0);
  if (alStack_40 == plStack_20) {
    pcVar2 = *(code **)(*plStack_20 + 0x20);
  }
  else {
    if (plStack_20 == (long *)0x0) {
      return;
    }
    pcVar2 = *(code **)(*plStack_20 + 0x28);
  }
  (*pcVar2)();
  return;
}

// ==== Framework::CFileLoader::Release()
// vaddr 0x1e83ca8 | ghidra 0x1f83ca8 | size 220 | symbol _ZN9Framework11CFileLoader7ReleaseEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework11CFileLoader7ReleaseEv(long param_1)

{
  byte bVar1;
  undefined1 auStack_20 [8];
  undefined4 uStack_18;
  
  if (*(char *)(param_1 + 0x30) != '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296396a/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\FileLoader.cpp"*/,0x1fd,&UNK_02963bb2/*"m_IsLoading is true."*/);
  }
  if (*(int *)(param_1 + 8) == -1) {
    return;
  }
  *(undefined4 *)(param_1 + 8) = 0xffffffff;
  *(undefined8 *)(param_1 + 0x10) = 0;
  if (*(long *)(param_1 + 0x18) != 0) {
    Aska::DeleteManager::AddMain(void*, unsigned char, unsigned char, Aska::IDeleteHandler*)(PTR__ZN4Aska6Global21m_systemDeleteManagerE_02cb77c0,*(long *)(param_1 + 0x18),0
                    ,1,0);
    *(undefined8 *)(param_1 + 0x18) = 0;
    *(undefined8 *)(param_1 + 0xb8) = 0;
  }
  if (*(char *)(param_1 + 0x98) != '\0') {
    Aska::File::Close()(param_1 + 0x38);
    if ((*(byte *)(param_1 + 0x50) & 1) == 0) {
      *(undefined2 *)(param_1 + 0x50) = 0;
      bVar1 = *(byte *)(param_1 + 0x68);
    }
    else {
      **(undefined1 **)(param_1 + 0x60) = 0;
      *(undefined8 *)(param_1 + 0x58) = 0;
      bVar1 = *(byte *)(param_1 + 0x68);
    }
    if ((bVar1 & 1) == 0) {
      *(undefined2 *)(param_1 + 0x68) = 0;
    }
    else {
      **(undefined1 **)(param_1 + 0x78) = 0;
      *(undefined8 *)(param_1 + 0x70) = 0;
    }
    Framework::CHash32::CHash32()(auStack_20);
    *(undefined4 *)(param_1 + 0xa8) = uStack_18;
    Framework::CHash32::~CHash32()(auStack_20);
    return;
  }
  return;
}

// ==== Framework::CFileLoader::DirectReleaseBuffer(bool)
// vaddr 0x1e83d84 | ghidra 0x1f83d84 | size 76 | symbol _ZN9Framework11CFileLoader19DirectReleaseBufferEb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework11CFileLoader19DirectReleaseBufferEb(long param_1,ulong param_2)

{
  long lVar1;
  
  lVar1 = *(long *)(param_1 + 0x18);
  if (lVar1 != 0) {
    if ((param_2 & 1) == 0) {
      operator delete[](void*)(lVar1);
    }
    else {
      Aska::DeleteManager::AddMain(void*, unsigned char, unsigned char, Aska::IDeleteHandler*)(PTR__ZN4Aska6Global21m_systemDeleteManagerE_02cb77c0,lVar1,0,1,0);
    }
    *(undefined8 *)(param_1 + 0x18) = 0;
    *(undefined8 *)(param_1 + 0xb8) = 0;
  }
  return;
}

// ==== Framework::CFileLoader::FileNumber() const
// vaddr 0x1e83dd0 | ghidra 0x1f83dd0 | size 8 | symbol _ZNK9Framework11CFileLoader10FileNumberEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK9Framework11CFileLoader10FileNumberEv(long param_1)

{
  return *(undefined4 *)(param_1 + 8);
}

// ==== Framework::CFileLoader::pFileName() const
// vaddr 0x1e83dd8 | ghidra 0x1f83dd8 | size 108 | symbol _ZNK9Framework11CFileLoader9pFileNameEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK9Framework11CFileLoader9pFileNameEv(long param_1)

{
  char cVar1;
  long lVar2;
  
  if (*(int *)(param_1 + 8) == -1) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296396a/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\FileLoader.cpp"*/,0x22e,&UNK_02961b3b/*"Uninitialized object."*/);
    cVar1 = *(char *)(param_1 + 0x98);
  }
  else {
    cVar1 = *(char *)(param_1 + 0x98);
  }
  if (cVar1 != '\0') {
    if ((*(byte *)(param_1 + 0x50) & 1) != 0) {
      return *(long *)(param_1 + 0x60);
    }
    return param_1 + 0x51;
  }
  lVar2 = (*(code *)PTR__ZN9Framework6FileID10gpFileNameEj_02cb6588)(*(undefined4 *)(param_1 + 8));
  return lVar2;
}

// ==== Framework::CFileLoader::FileNameHash() const
// vaddr 0x1e83e44 | ghidra 0x1f83e44 | size 120 | symbol _ZNK9Framework11CFileLoader12FileNameHashEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK9Framework11CFileLoader12FileNameHashEv(long *param_1,long param_2)

{
  char cVar1;
  
  if (*(int *)(param_2 + 8) == -1) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296396a/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\FileLoader.cpp"*/,0x23b,&UNK_02961b3b/*"Uninitialized object."*/);
    cVar1 = *(char *)(param_2 + 0x98);
  }
  else {
    cVar1 = *(char *)(param_2 + 0x98);
  }
  if (cVar1 != '\0') {
    *param_1 = (long)(PTR__ZTVN9Framework7CHash32E_02cba528 + 0x10);
    *(undefined4 *)(param_1 + 1) = *(undefined4 *)(param_2 + 0xa8);
    return;
  }
  (*(code *)PTR__ZN9Framework7CHash32C1Ev_02cad230)(param_1);
  return;
}

// ==== Framework::CFileLoader::pBuffer() const
// vaddr 0x1e83ebc | ghidra 0x1f83ebc | size 152 | symbol _ZNK9Framework11CFileLoader7pBufferEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK9Framework11CFileLoader7pBufferEv(long param_1)

{
  char cVar1;
  long lVar2;
  
  if (*(int *)(param_1 + 8) == -1) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296396a/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\FileLoader.cpp"*/,0x248,&UNK_02961b3b/*"Uninitialized object."*/);
    lVar2 = *(long *)(param_1 + 0x18);
  }
  else {
    lVar2 = *(long *)(param_1 + 0x18);
  }
  if (lVar2 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296396a/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\FileLoader.cpp"*/,0x249,&UNK_02963bc7/*"m_pBuffer is null."*/);
    cVar1 = *(char *)(param_1 + 0x30);
  }
  else {
    cVar1 = *(char *)(param_1 + 0x30);
  }
  if (cVar1 != '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296396a/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\FileLoader.cpp"*/,0x24a,&UNK_02963bda/*"Loading is not terminated yet.(%d)"*/,*(undefined4 *)(param_1 + 8));
  }
  return *(long *)(param_1 + 0x18) + *(long *)(param_1 + 0xb8);
}

// ==== Framework::CFileLoader::BufferOffset() const
// vaddr 0x1e83f54 | ghidra 0x1f83f54 | size 8 | symbol _ZNK9Framework11CFileLoader12BufferOffsetEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK9Framework11CFileLoader12BufferOffsetEv(long param_1)

{
  return *(undefined8 *)(param_1 + 0xb8);
}

// ==== Framework::CFileLoader::Size() const
// vaddr 0x1e83f5c | ghidra 0x1f83f5c | size 108 | symbol _ZNK9Framework11CFileLoader4SizeEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK9Framework11CFileLoader4SizeEv(long param_1)

{
  long lVar1;
  
  if (*(int *)(param_1 + 8) == -1) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296396a/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\FileLoader.cpp"*/,0x250,&UNK_02961b3b/*"Uninitialized object."*/);
    lVar1 = *(long *)(param_1 + 0x18);
  }
  else {
    lVar1 = *(long *)(param_1 + 0x18);
  }
  if (lVar1 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296396a/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\FileLoader.cpp"*/,0x251,&UNK_02963bc7/*"m_pBuffer is null."*/);
  }
  return *(long *)(param_1 + 0x20) - *(long *)(param_1 + 0xb8);
}

// ==== Framework::CFileLoader::Handler(unsigned long)
// vaddr 0x1e83fc8 | ghidra 0x1f83fc8 | size 220 | symbol _ZN9Framework11CFileLoader7HandlerEm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework11CFileLoader7HandlerEm(long param_1,undefined8 *param_2)

{
  byte bVar1;
  long *plVar2;
  ulong uVar3;
  long lStack_30;
  long lStack_28;
  byte *pbStack_20;
  long lStack_18;
  
  if (((uint)((long)*param_2 >> 0x3f) & (uint)*param_2) != 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296396a/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\FileLoader.cpp"*/,0x268,&UNK_02963bfd/*"Read failed.(%d)"*/,*(undefined4 *)(param_1 + 8));
  }
  plVar2 = *(long **)(PTR__ZN9Framework11CFileLoader17m_DecryptFunctionE_02cc23c0 + 0x20);
  if (plVar2 != (long *)0x0) {
    bVar1 = *(byte *)(param_1 + 0x80);
    if ((bVar1 & 1) == 0) {
      uVar3 = (ulong)(bVar1 >> 1);
    }
    else {
      uVar3 = *(ulong *)(param_1 + 0x88);
    }
    pbStack_20 = *(byte **)PTR__ZN9Framework11CFileLoader29gpDefalutDirectLoadRootFolderE_02cbbba8;
    if (uVar3 != 0) {
      pbStack_20 = (byte *)(param_1 + 0x80);
    }
    if ((*pbStack_20 & 1) == 0) {
      pbStack_20 = pbStack_20 + 1;
    }
    else {
      pbStack_20 = *(byte **)(pbStack_20 + 0x10);
    }
    if ((*(byte *)(param_1 + 0x50) & 1) == 0) {
      lStack_28 = param_1 + 0x51;
    }
    else {
      lStack_28 = *(long *)(param_1 + 0x60);
    }
    lStack_30 = param_1 + 0x18;
    lStack_18 = param_1;
    (**(code **)(*plVar2 + 0x30))
              (plVar2,&lStack_18,&pbStack_20,&lStack_28,&lStack_30,param_1 + 0x20);
  }
  *(undefined1 *)(param_1 + 0x30) = 0;
  return;
}

// ==== Framework::CFileLoader::pBufferTop() const
// vaddr 0x1e840a4 | ghidra 0x1f840a4 | size 8 | symbol _ZNK9Framework11CFileLoader10pBufferTopEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK9Framework11CFileLoader10pBufferTopEv(long param_1)

{
  return *(undefined8 *)(param_1 + 0x18);
}

// ==== Framework::CFileLoader::IsLoading() const
// vaddr 0x1e840ac | ghidra 0x1f840ac | size 8 | symbol _ZNK9Framework11CFileLoader9IsLoadingEv | lib libSOA-3.7.0.so | 2026-10-04
undefined1 _ZNK9Framework11CFileLoader9IsLoadingEv(long param_1)

{
  return *(undefined1 *)(param_1 + 0x30);
}

// ==== Framework::CFileLoader::SwapBufferPointer(void*, unsigned long)
// vaddr 0x1e840b4 | ghidra 0x1f840b4 | size 136 | symbol _ZN9Framework11CFileLoader17SwapBufferPointerEPvm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework11CFileLoader17SwapBufferPointerEPvm
               (long param_1,undefined8 param_2,undefined8 param_3)

{
  char cVar1;
  
  if (*(long *)(param_1 + 0x18) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296396a/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\FileLoader.cpp"*/,0x292,&UNK_02963bc7/*"m_pBuffer is null."*/);
    cVar1 = *(char *)(param_1 + 0x30);
  }
  else {
    cVar1 = *(char *)(param_1 + 0x30);
  }
  if (cVar1 != '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296396a/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\FileLoader.cpp"*/,0x293,&UNK_02963bda/*"Loading is not terminated yet.(%d)"*/,*(undefined4 *)(param_1 + 8));
  }
  if (*(long *)(param_1 + 0x18) != 0) {
    operator delete[](void*)();
    *(undefined8 *)(param_1 + 0x18) = 0;
  }
  *(undefined8 *)(param_1 + 0x18) = param_2;
  *(undefined8 *)(param_1 + 0x20) = param_3;
  *(undefined8 *)(param_1 + 0xb8) = 0;
  return;
}

// ==== Framework::CFileLoader::~CFileLoader()
// vaddr 0x1e8413c | ghidra 0x1f8413c | size 148 | symbol _ZN9Framework11CFileLoaderD2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework11CFileLoaderD2Ev(long *param_1)

{
  byte bVar1;
  
  *param_1 = (long)(PTR__ZTVN9Framework11CFileLoaderE_02cb9740 + 0x10);
  Framework::CFileLoader::Release()();
  Framework::CHash32::~CHash32()(param_1 + 0x14);
  if ((*(byte *)(param_1 + 0x10) & 1) == 0) {
    bVar1 = *(byte *)(param_1 + 0xd);
  }
  else {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(param_1[0x12]);
    bVar1 = *(byte *)(param_1 + 0xd);
  }
  if ((bVar1 & 1) == 0) {
    bVar1 = *(byte *)(param_1 + 10);
  }
  else {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(param_1[0xf]);
    bVar1 = *(byte *)(param_1 + 10);
  }
  if ((bVar1 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(param_1[0xc]);
  }
  param_1[7] = (long)(PTR__ZTVN4Aska4FileE_02cb6e28 + 0x10);
  if (param_1[9] == 0) {
    return;
  }
  (*(code *)PTR__ZN4Aska4File5CloseEv_02c8e880)(param_1 + 7);
  return;
}

// ==== Framework::CFileLoader::~CFileLoader()
// vaddr 0x1e841d0 | ghidra 0x1f841d0 | size 24 | symbol _ZN9Framework11CFileLoaderD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework11CFileLoaderD0Ev(undefined8 param_1)

{
  Framework::CFileLoader::~CFileLoader()();
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}


// FAILED to create function at 02ba8ea8 Framework::CFileLoader::vtable
// FAILED to create function at 02ba8ef0 Framework::CFileLoader::typeinfo
// FAILED to create function at 02d00478 Framework::CFileLoader::gpDefalutDirectLoadRootFolder
// FAILED to create function at 02d00480 Framework::CFileLoader::m_AssetManagerEvalutionFunction
// FAILED to create function at 02d004b0 Framework::CFileLoader::m_DecryptFunction
