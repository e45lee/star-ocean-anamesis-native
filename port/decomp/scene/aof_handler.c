// port/decomp/scene/aof_handler.c: Ghidra decompiles for the scene subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-04 06:31 UTC: tools/decomp.sh '--into' 'scene/aof_handler' 'Aska::AofHandler::'

// ==== Aska::AofHandler::NotifyMapping()
// vaddr 0x1e77e7c | ghidra 0x1f77e7c | size 4 | symbol _ZN4Aska10AofHandler13NotifyMappingEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10AofHandler13NotifyMappingEv(void)

{
  return;
}

// ==== non-virtual thunk to Aska::AofHandler::NotifyMapping()
// vaddr 0x1e77ea4 | ghidra 0x1f77ea4 | size 4 | symbol _ZThn152_N4Aska10AofHandler13NotifyMappingEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZThn152_N4Aska10AofHandler13NotifyMappingEv(void)

{
  return;
}

// ==== Aska::AofHandler::AttachTextures(Aska::AFF::AskaFile const*, Aska::ITextureHandler*, bool, int, int)
// vaddr 0x20bf740 | ghidra 0x21bf740 | size 352 | symbol _ZN4Aska10AofHandler14AttachTexturesEPKNS_3AFF8AskaFileEPNS_15ITextureHandlerEbii | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska10AofHandler14AttachTexturesEPKNS_3AFF8AskaFileEPNS_15ITextureHandlerEbii
          (int *param_1,undefined8 param_2,uint param_3,undefined4 param_4,undefined4 param_5)

{
  long lVar1;
  uint uVar2;
  undefined *puVar3;
  ulong uVar4;
  int *piVar5;
  long lVar6;
  int *piVar7;
  undefined8 uStack_70;
  int *piStack_68;
  
  puVar3 = PTR__ZN4Aska6Global17m_pTextureManagerE_02cc19f0;
  piVar5 = param_1 + 0x34;
  if (*param_1 != 0x616f5f5f) {
    return 0;
  }
  piVar7 = piVar5;
  do {
    if (*piVar7 == 0x41494620) {
      Hint_Prefetch((long)piVar7 + (ulong)(uint)piVar7[3],0,2,0);
      if (piVar7 == (int *)0x0) {
        piStack_68 = (int *)0x0;
code_r0x021bf7ec:
        lVar6 = *(long *)puVar3;
        lVar1 = lVar6 + 0xb0;
        uStack_70 = param_2;
        Aska::CriticalSection::Enter() const(lVar1);
        uVar4 = Aska::TextureManager::RegisterTextureEx(Aska::TextureMemory::tagKey const*, bool, int, int)(lVar6,&uStack_70,param_3 & 1,param_4,param_5);
        Aska::CriticalSection::Leave() const(lVar1);
        if ((uVar4 & 1) == 0) {
          if (*param_1 != 0x616f5f5f) {
            return 0;
          }
          while( true ) {
            if (*piVar5 == 0x41494620) {
              Aska::ITextureHandler::DetachTexture(Aska::AFF::AskaFile const*, bool)(param_2,piVar5,0);
            }
            if (piVar5[3] == 0) break;
            piVar5 = (int *)((long)piVar5 + (ulong)(uint)piVar5[3]);
          }
          return 0;
        }
      }
      else if (piVar7[1] != 0) {
        piStack_68 = piVar7 + 4;
        goto code_r0x021bf7ec;
      }
      uVar2 = piVar7[3];
    }
    else {
      uVar2 = piVar7[3];
    }
    if (uVar2 == 0) {
      return 1;
    }
    piVar7 = (int *)((long)piVar7 + (ulong)uVar2);
  } while( true );
}

// ==== Aska::AofHandler::DetachTextures(Aska::AFF::AskaFile const*, Aska::ITextureHandler*, bool)
// vaddr 0x20bf8a0 | ghidra 0x21bf8a0 | size 112 | symbol _ZN4Aska10AofHandler14DetachTexturesEPKNS_3AFF8AskaFileEPNS_15ITextureHandlerEb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10AofHandler14DetachTexturesEPKNS_3AFF8AskaFileEPNS_15ITextureHandlerEb
               (int *param_1,undefined8 param_2,uint param_3)

{
  if (*param_1 == 0x616f5f5f) {
    param_1 = param_1 + 0x34;
    while( true ) {
      if (*param_1 == 0x41494620) {
        Aska::ITextureHandler::DetachTexture(Aska::AFF::AskaFile const*, bool)(param_2,param_1,param_3 & 1);
      }
      if (param_1[3] == 0) break;
      param_1 = (int *)((long)param_1 + (ulong)(uint)param_1[3]);
    }
  }
  return;
}

// ==== Aska::AofHandler::Attach(void const*, bool, int, int)
// vaddr 0x20bf910 | ghidra 0x21bf910 | size 1308 | symbol _ZN4Aska10AofHandler6AttachEPKvbii | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska10AofHandler6AttachEPKvbii
          (long *param_1,long param_2,uint param_3,undefined4 param_4,undefined4 param_5)

{
  undefined *puVar1;
  uint uVar2;
  uint uVar3;
  undefined4 uVar4;
  byte bVar5;
  ushort uVar6;
  uint uVar7;
  int iVar8;
  bool bVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  long lVar13;
  ulong uVar14;
  undefined8 uVar15;
  undefined8 uVar16;
  long lVar17;
  long *plVar18;
  uint uVar19;
  int *piVar20;
  int *piVar21;
  ulong uVar22;
  long lVar23;
  undefined8 *puVar24;
  long *plStack_70;
  int *piStack_68;
  
  (**(code **)(*param_1 + 0x20))();
  param_1[0x16] = param_2;
  uVar6 = *(ushort *)(param_2 + 0x70);
  *(byte *)(param_1 + 0x15) = *(byte *)(param_1 + 0x15) & 0xe5 | 10;
  piVar21 = (int *)(param_2 + 0xd0);
  *(undefined1 *)(param_1 + 0x17) = *(undefined1 *)(param_2 + 0x92);
  *(undefined4 *)((long)param_1 + 0xbc) = *(undefined4 *)(param_2 + 0x98);
  *(undefined4 *)(param_1 + 0x18) = *(undefined4 *)(param_2 + 0x9c);
  puVar1 = PTR__ZN4Aska6Global17m_pTextureManagerE_02cc19f0;
  uVar19 = (uint)*(ushort *)(param_2 + 0x7e);
  if (*(ushort *)(param_2 + 0x7e) != 0) {
    do {
      piStack_68 = (int *)0x0;
      plStack_70 = param_1;
      if (piVar21 == (int *)0x0) {
        piStack_68 = (int *)0x0;
code_r0x021bf9bc:
        lVar23 = *(long *)puVar1;
        lVar13 = lVar23 + 0xb0;
        Aska::CriticalSection::Enter() const(lVar13);
        Aska::TextureManager::RegisterTextureEx(Aska::TextureMemory::tagKey const*, bool, int, int)(lVar23,&plStack_70,param_3 & 1,param_4,param_5);
        Aska::CriticalSection::Leave() const(lVar13);
      }
      else if (piVar21[1] != 0) {
        piStack_68 = piVar21 + 4;
        goto code_r0x021bf9bc;
      }
      uVar19 = uVar19 - 1;
      piVar21 = (int *)((long)piVar21 + (long)piVar21[3]);
    } while (uVar19 != 0);
  }
  do {
    piVar20 = piVar21;
    piVar21 = (int *)((long)piVar20 + (long)piVar20[3]);
  } while (*piVar20 != 0x6d6c5f5f);
  if (*piVar21 != 0x626e706c) {
    param_1[0x1c] = 0;
    goto code_r0x021bfa5c;
  }
  param_1[0x1c] = (long)(piVar21 + 4);
  do {
    piVar21 = (int *)((long)piVar21 + (long)piVar21[3]);
code_r0x021bfa5c:
  } while (*piVar21 != 0x6d657373);
  uVar19 = (uint)uVar6 * 8 + 0xf & 0xffff0;
  plVar18 = param_1 + 0x1d;
  *(undefined4 *)((long)param_1 + 0xcc) = 0;
  *(undefined8 *)((long)param_1 + 0xc4) = 0;
  uVar2 = uVar19 + (uint)uVar6 * 0x78 + 0xf & 0x1fffff0;
  iVar10 = Aska::MaterialList::GetAllocBufSize(int, Aska::AFF::Meshset const*) const(plVar18,uVar6,piVar21);
  lVar13 = operator new[](unsigned long, std::nothrow_t const&)((long)(int)(iVar10 + uVar2),PTR__ZSt7nothrow_02cb9a80);
  if (lVar13 != 0) {
    param_1[0x1a] = lVar13;
    uVar14 = Aska::MaterialList::Alloc(int, void*)(plVar18,*(undefined2 *)(param_2 + 0x70),lVar13 + (ulong)uVar2);
    if ((uVar14 & 1) != 0) {
      memset(param_1[0x1a],0,(ulong)*(ushort *)(param_2 + 0x70) << 3);
      if (*(short *)(param_2 + 0x70) == 0) {
        uVar14 = 0;
      }
      else {
        bVar9 = false;
        uVar22 = 0;
        puVar24 = (undefined8 *)(lVar13 + (ulong)uVar19);
        uVar19 = 2;
        if ((param_3 & 1) == 0) {
          uVar19 = 0;
        }
        puVar1 = PTR__ZTVN4Aska13MeshPrimitiveE_02cbcfd0 + 0x10;
        do {
          Aska::PrimitiveBuffer::PrimitiveBuffer()(puVar24 + 8);
          *(undefined4 *)(puVar24 + 0xd) = 0;
          *(undefined1 *)((long)puVar24 + 0x6c) = 0;
          puVar24[8] = puVar1;
          *(undefined8 **)(param_1[0x1a] + uVar22 * 8) = puVar24;
          lVar13 = (long)piVar21[4] + (long)piVar21;
          *puVar24 = piVar21;
          puVar24[1] = lVar13;
          lVar23 = (long)piVar21[5] + (long)piVar21;
          if (8 < *(byte *)(lVar23 + 0x18)) {
            return 0;
          }
          iVar10 = piVar21[3];
          if ((short)piVar21[7] == 0) {
code_r0x021bfb7c:
            lVar17 = lVar13 + 0x20;
            puVar24[2] = lVar17;
            if (*(int *)(lVar13 + 0x20) == 0x626e7069) {
              puVar24[4] = lVar17;
              lVar17 = lVar17 + *(int *)(lVar13 + 0x2c);
              puVar24[2] = lVar17;
            }
            puVar24[3] = lVar17 + *(int *)(lVar17 + 0xc);
            uVar6 = *(ushort *)((long)piVar21 + 0x1e);
            uVar2 = uVar6 & 0x20;
            uVar7 = uVar19 | uVar2 >> 2;
            uVar3 = uVar7 | 0x80;
            if (*(uint *)(lVar13 + 0x10) < 0x10001) {
              uVar3 = uVar7;
            }
            uVar14 = Aska::AofHandler::Attach_IndexList(Aska::AofhMeshset*, Aska::AFF::Meshbody const*, unsigned int)(param_1,puVar24,lVar13,uVar3);
            if (((uVar14 & 1) == 0) ||
               (uVar14 = Aska::AofHandler::Attach_VertexList(Aska::AofhMeshset*, Aska::AFF::Meshbody const*, unsigned int, bool)(param_1,puVar24,lVar13,uVar19 | uVar2 >> 3,
                                         (uVar6 & 0x20) != 0), (uVar14 & 1) == 0)) {
              return 0;
            }
            puVar24[6] = 0;
            puVar24[7] = 0;
            puVar24[5] = 0;
            bVar5 = *(byte *)(puVar24[1] + 0x18);
            iVar11 = Aska::PrimitiveBuffer::Static::GetStripHeadCount(Aska::PrimType::Type)(bVar5);
            iVar12 = Aska::PrimitiveBuffer::Static::GetPrimUnitCount(Aska::PrimType::Type)(bVar5);
            iVar8 = 0;
            if (iVar12 != 0) {
              iVar8 = (*(int *)(puVar24[1] + 0x14) - iVar11) / iVar12;
            }
            *(int *)((long)puVar24 + 0x5c) = iVar8;
            *(int *)((long)param_1 + 0xc4) = *(int *)((long)param_1 + 0xc4) + iVar8;
            uVar4 = *(undefined4 *)(lVar13 + 0x10);
            *(ushort *)(puVar24 + 0xb) = (ushort)bVar5;
            *(undefined4 *)(puVar24 + 0xd) = uVar4;
            Aska::RenderablePrimitive::SetKickBuffer()(puVar24 + 8);
            *(int *)(param_1 + 0x19) = (int)param_1[0x19] + *(int *)(lVar13 + 0x10);
            Aska::MaterialList::Connect(int, int, Aska::MaterialData const*)(plVar18,uVar22 & 0xffffffff,0,lVar23);
          }
          else {
            if (uVar22 == ((long)*(char *)((long)piVar21 + 0x19) & 0xffffffffU)) {
              bVar9 = true;
              goto code_r0x021bfb7c;
            }
            Aska::RenderablePrimitive::CreateReference(Aska::RenderablePrimitive const*)(puVar24 + 8,
                            *(long *)(param_1[0x1a] + (long)*(char *)((long)piVar21 + 0x19) * 8) +
                            0x40);
            Aska::MaterialList::Connect(int, int, Aska::MaterialData const*)(plVar18,uVar22 & 0xffffffff,0,lVar23);
            bVar9 = true;
          }
          uVar14 = (ulong)*(ushort *)(param_2 + 0x70);
          uVar22 = uVar22 + 1;
          puVar24 = puVar24 + 0xf;
          piVar21 = (int *)((long)piVar21 + (long)iVar10);
        } while ((long)uVar22 < (long)uVar14);
        if (bVar9) {
          Aska::MaterialList::EnablePerMatLightContext(bool)(plVar18,1);
          uVar6 = *(ushort *)(param_2 + 0x70);
          if ((ulong)uVar6 != 0) {
            uVar14 = 0;
            do {
              if (*(short *)(**(long **)(param_1[0x1a] + uVar14 * 8) + 0x1c) == 0) {
                uVar15 = 3;
                uVar16 = 1;
              }
              else {
                uVar15 = 1;
                uVar16 = 2;
              }
              Aska::MaterialList::SetPerMatLightContext(int, int, Aska::MaterialList::LightFreq)(plVar18,uVar14 & 0xffffffff,uVar15,uVar16);
              uVar14 = uVar14 + 1;
            } while (uVar6 != uVar14);
          }
          *(ushort *)(param_1 + 0x21) = *(ushort *)(param_1 + 0x21) | 0x1000;
          Aska::MaterialList::Activate(void const*, Aska::AFF::MaterialInfo const*, int, Aska::AofhMeshset**)(plVar18,piVar20,param_2 + 0x90,*(undefined2 *)(param_2 + 0x70),
                          param_1[0x1a]);
          plVar18 = (long *)param_1[0x27];
          *(byte *)(param_1 + 0x15) = *(byte *)(param_1 + 0x15) | 1;
          if (param_1 + 0x25 == plVar18) {
            return 1;
          }
          do {
            Aska::RenderPass::InvalidateShaders()(plVar18[3]);
            Aska::RenderPassManager::InvalidateShaders(bool)(plVar18,0);
            plVar18 = (long *)plVar18[2];
          } while (param_1 + 0x25 != plVar18);
          return 1;
        }
      }
      Aska::MaterialList::Activate(void const*, Aska::AFF::MaterialInfo const*, int, Aska::AofhMeshset**)(plVar18,piVar20,param_2 + 0x90,uVar14,param_1[0x1a]);
      *(byte *)(param_1 + 0x15) = *(byte *)(param_1 + 0x15) | 1;
      return 1;
    }
  }
  (**(code **)(*param_1 + 0x20))(param_1);
  *(byte *)(param_1 + 0x15) = *(byte *)(param_1 + 0x15) & 0xfd;
  return 0;
}

// ==== Aska::AofHandler::Attach_IndexList(Aska::AofhMeshset*, Aska::AFF::Meshbody const*, unsigned int)
// vaddr 0x20bfe2c | ghidra 0x21bfe2c | size 280 | symbol _ZN4Aska10AofHandler16Attach_IndexListEPNS_11AofhMeshsetEPKNS_3AFF8MeshbodyEj | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska10AofHandler16Attach_IndexListEPNS_11AofhMeshsetEPKNS_3AFF8MeshbodyEj
          (long *param_1,long param_2,long param_3,undefined4 param_4)

{
  long lVar1;
  ulong uVar2;
  int iVar3;
  long lVar4;
  long lVar5;
  
  lVar4 = *(long *)(param_2 + 0x10);
  if ((((*(int *)(lVar4 + 0x20) == 0) && (*(int *)(lVar4 + 0x24) == 0)) &&
      (*(int *)(lVar4 + 0x28) == 0)) && (*(int *)(lVar4 + 0x2c) == 0)) {
    lVar4 = lVar4 + *(int *)(lVar4 + 0x10);
    iVar3 = *(int *)(param_3 + 0x14);
  }
  else {
    lVar5 = *(long *)PTR__ZN4Aska6Global22m_pMappedMemoryManagerE_02cc0368;
    lVar1 = lVar5 + 8;
    Aska::CriticalSection::Enter() const(lVar1);
    lVar4 = Aska::MappedMemoryManager::QueryMappingEx(Aska::IMappingHandler const*, Aska::AUID const*, unsigned long*, Aska::MappedTarget*)(lVar5,param_1 + 0x13,lVar4 + 0x20,0,0);
    Aska::CriticalSection::Leave() const(lVar1);
    iVar3 = *(int *)(param_3 + 0x14);
  }
  if (iVar3 == 0) {
    iVar3 = 0;
  }
  else {
    uVar2 = Aska::PrimitiveBuffer::CreateIndexBuffer(int, void const*, unsigned int, bool)(param_2 + 0x40,iVar3,lVar4,param_4,0);
    if ((uVar2 & 1) == 0) {
      (**(code **)(*param_1 + 0x20))(param_1);
      *(byte *)(param_1 + 0x15) = *(byte *)(param_1 + 0x15) & 0xfd;
      return 0;
    }
    iVar3 = *(int *)(param_3 + 0x14);
  }
  *(int *)((long)param_1 + 0xcc) = *(int *)((long)param_1 + 0xcc) + iVar3;
  return 1;
}

// ==== Aska::AofHandler::Attach_VertexList(Aska::AofhMeshset*, Aska::AFF::Meshbody const*, unsigned int, bool)
// vaddr 0x20bff44 | ghidra 0x21bff44 | size 440 | symbol _ZN4Aska10AofHandler17Attach_VertexListEPNS_11AofhMeshsetEPKNS_3AFF8MeshbodyEjb | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska10AofHandler17Attach_VertexListEPNS_11AofhMeshsetEPKNS_3AFF8MeshbodyEjb
          (long *param_1,long *param_2,long param_3,undefined4 param_4,ulong param_5)

{
  ulong uVar1;
  undefined8 uVar2;
  long lVar3;
  long lVar4;
  long lVar5;
  
  lVar3 = param_2[3];
  if ((((*(int *)(lVar3 + 0x20) == 0) && (*(int *)(lVar3 + 0x24) == 0)) &&
      (*(int *)(lVar3 + 0x28) == 0)) && (*(int *)(lVar3 + 0x2c) == 0)) {
    lVar5 = lVar3 + *(int *)(lVar3 + 0x1c);
  }
  else {
    lVar5 = *(long *)PTR__ZN4Aska6Global22m_pMappedMemoryManagerE_02cc0368;
    lVar4 = lVar5 + 8;
    Aska::CriticalSection::Enter() const(lVar4);
    lVar5 = Aska::MappedMemoryManager::QueryMappingEx(Aska::IMappingHandler const*, Aska::AUID const*, unsigned long*, Aska::MappedTarget*)(lVar5,param_1 + 0x13,lVar3 + 0x20,0,0);
    Aska::CriticalSection::Leave() const(lVar4);
    lVar3 = param_2[3];
  }
  uVar1 = Aska::PrimitiveBuffer::CreateVertexBuffer(int, unsigned long, int, void const*, unsigned int, bool)(param_2 + 8,*(undefined4 *)(param_3 + 0x10),*(undefined8 *)(lVar3 + 0x10),
                          *(undefined2 *)(lVar3 + 0x18),lVar5,param_4,0);
  if ((((uVar1 & 1) == 0) || (*(int *)(param_2[10] + 0x60) != *(int *)(param_3 + 0x10))) ||
     (((*(byte *)(*param_2 + 0x1e) >> 4 & 1) != 0 &&
      (uVar1 = Aska::PrimitiveBuffer::SetWeightsAndIndicesPtr(void const*)(param_2 + 8,
                               lVar5 + (int)(*(int *)(param_2[10] + 0x60) *
                                            (uint)*(ushort *)(param_2[3] + 0x18)) + 0x7fU &
                               0xffffffffffffff80), (uVar1 & 1) == 0)))) {
    (**(code **)(*param_1 + 0x20))(param_1);
    uVar2 = 0;
    *(byte *)(param_1 + 0x15) = *(byte *)(param_1 + 0x15) & 0xfd;
  }
  else {
    if (((param_5 & 1) != 0) &&
       (((lVar3 = param_2[3], *(int *)(lVar3 + 0x30) != 0 || (*(int *)(lVar3 + 0x34) != 0)) ||
        ((*(int *)(lVar3 + 0x38) != 0 || (*(int *)(lVar3 + 0x3c) != 0)))))) {
      lVar4 = *(long *)PTR__ZN4Aska6Global22m_pMappedMemoryManagerE_02cc0368;
      lVar5 = lVar4 + 8;
      Aska::CriticalSection::Enter() const(lVar5);
      Aska::MappedMemoryManager::QueryMappingEx(Aska::IMappingHandler const*, Aska::AUID const*, unsigned long*, Aska::MappedTarget*)(lVar4,param_1 + 0x13,lVar3 + 0x30,0,0);
      Aska::CriticalSection::Leave() const(lVar5);
    }
    uVar2 = 1;
  }
  return uVar2;
}

// ==== Aska::AofHandler::Attach_AdditionalBuffers(Aska::AofhMeshset*, Aska::AFF::Meshset const*)
// vaddr 0x20c00fc | ghidra 0x21c00fc | size 16 | symbol _ZN4Aska10AofHandler24Attach_AdditionalBuffersEPNS_11AofhMeshsetEPKNS_3AFF7MeshsetE | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska10AofHandler24Attach_AdditionalBuffersEPNS_11AofhMeshsetEPKNS_3AFF7MeshsetE
          (undefined8 param_1,long param_2)

{
  *(undefined8 *)(param_2 + 0x30) = 0;
  *(undefined8 *)(param_2 + 0x38) = 0;
  *(undefined8 *)(param_2 + 0x28) = 0;
  return 1;
}

// ==== Aska::AofHandler::Attach_CalcPrimitiveInfo(Aska::AofhMeshset*, Aska::AFF::Meshbody const*)
// vaddr 0x20c010c | ghidra 0x21c010c | size 136 | symbol _ZN4Aska10AofHandler24Attach_CalcPrimitiveInfoEPNS_11AofhMeshsetEPKNS_3AFF8MeshbodyE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10AofHandler24Attach_CalcPrimitiveInfoEPNS_11AofhMeshsetEPKNS_3AFF8MeshbodyE
               (long param_1,long param_2,long param_3)

{
  undefined4 uVar1;
  byte bVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  bVar2 = *(byte *)(*(long *)(param_2 + 8) + 0x18);
  iVar4 = Aska::PrimitiveBuffer::Static::GetStripHeadCount(Aska::PrimType::Type)(bVar2);
  iVar5 = Aska::PrimitiveBuffer::Static::GetPrimUnitCount(Aska::PrimType::Type)(bVar2);
  iVar3 = 0;
  if (iVar5 != 0) {
    iVar3 = (*(int *)(*(long *)(param_2 + 8) + 0x14) - iVar4) / iVar5;
  }
  *(int *)(param_2 + 0x5c) = iVar3;
  *(int *)(param_1 + 0xc4) = *(int *)(param_1 + 0xc4) + iVar3;
  uVar1 = *(undefined4 *)(param_3 + 0x10);
  *(ushort *)(param_2 + 0x58) = (ushort)bVar2;
  *(undefined4 *)(param_2 + 0x68) = uVar1;
  Aska::RenderablePrimitive::SetKickBuffer()(param_2 + 0x40);
  *(int *)(param_1 + 200) = *(int *)(param_1 + 200) + *(int *)(param_3 + 0x10);
  return;
}

// ==== Aska::AofHandler::HookMeshset(int, Aska::AofhMeshset*)
// vaddr 0x20c0194 | ghidra 0x21c0194 | size 188 | symbol _ZN4Aska10AofHandler11HookMeshsetEiPNS_11AofhMeshsetE | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska10AofHandler11HookMeshsetEiPNS_11AofhMeshsetE(long param_1,uint param_2,undefined8 param_3)

{
  ulong uVar1;
  long lVar2;
  long lVar3;
  long lVar4;
  
  lVar4 = *(long *)(param_1 + 0xd0);
  if (lVar4 == 0) {
    lVar2 = 0;
    lVar3 = *(long *)(param_1 + 0xd8);
  }
  else {
    lVar2 = (ulong)*(ushort *)(*(long *)(param_1 + 0xb0) + 0x70) << 3;
    lVar3 = *(long *)(param_1 + 0xd8);
  }
  if (lVar3 == 0) {
    lVar3 = operator new[](unsigned long, std::nothrow_t const&)(lVar2,PTR__ZSt7nothrow_02cb9a80);
    *(long *)(param_1 + 0xd8) = lVar3;
    if (lVar3 == 0) {
      return 0;
    }
    memset(lVar3,0,lVar2);
  }
  uVar1 = -(ulong)(param_2 >> 0x1f) & 0xfffffff800000000 | (ulong)param_2 << 3;
  *(undefined8 *)(lVar3 + uVar1) = *(undefined8 *)(lVar4 + uVar1);
  *(undefined8 *)(*(long *)(param_1 + 0xd0) + uVar1) = param_3;
  *(long *)(*(long *)(param_1 + 0x150) + (long)(int)param_2 * 0x1b8 + 0x28) =
       *(long *)(*(long *)(param_1 + 0xd0) + uVar1) + 0x40;
  return 1;
}

// ==== Aska::AofHandler::UnhookMeshset(int)
// vaddr 0x20c0250 | ghidra 0x21c0250 | size 56 | symbol _ZN4Aska10AofHandler13UnhookMeshsetEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10AofHandler13UnhookMeshsetEi(long param_1,uint param_2)

{
  ulong uVar1;
  
  uVar1 = -(ulong)(param_2 >> 0x1f) & 0xfffffff800000000 | (ulong)param_2 << 3;
  *(undefined8 *)(*(long *)(param_1 + 0xd0) + uVar1) =
       *(undefined8 *)(*(long *)(param_1 + 0xd8) + uVar1);
  *(undefined8 *)(*(long *)(param_1 + 0xd8) + uVar1) = 0;
  *(long *)(*(long *)(param_1 + 0x150) + (long)(int)param_2 * 0x1b8 + 0x28) =
       *(long *)(*(long *)(param_1 + 0xd0) + uVar1) + 0x40;
  return;
}

// ==== Aska::AofHandler::Clone(Aska::AofHandler const*, bool)
// vaddr 0x20c0288 | ghidra 0x21c0288 | size 460 | symbol _ZN4Aska10AofHandler5CloneEPKS0_b | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska10AofHandler5CloneEPKS0_b(long *param_1,long param_2,uint param_3)

{
  undefined *puVar1;
  undefined8 *puVar2;
  ushort uVar3;
  ulong uVar4;
  undefined8 uVar5;
  long lVar6;
  long lVar7;
  long lVar8;
  long lVar9;
  undefined8 *puVar10;
  undefined8 *puVar11;
  long *plStack_70;
  long lStack_68;
  
  uVar4 = (**(code **)(*param_1 + 0x30))();
  if ((uVar4 & 1) == 0) {
    (**(code **)(*param_1 + 0x20))(param_1);
    *(byte *)(param_1 + 0x15) = *(byte *)(param_1 + 0x15) | 4;
    lVar9 = *(long *)(param_2 + 0xb0);
    param_1[0x16] = lVar9;
    uVar3 = *(ushort *)(lVar9 + 0x70);
    lVar6 = operator new[](unsigned long, std::nothrow_t const&)((ulong)uVar3 << 7,PTR__ZSt7nothrow_02cb9a80);
    uVar5 = 0;
    if (lVar6 != 0) {
      param_1[0x1a] = lVar6;
      if ((*(byte *)(param_2 + 0xa8) >> 1 & 1) != 0) {
        lStack_68 = 0;
        plStack_70 = param_1;
        if (*(int *)(lVar9 + 0xd4) != 0) {
          lVar7 = *(long *)PTR__ZN4Aska6Global17m_pTextureManagerE_02cc19f0;
          lStack_68 = lVar9 + 0xe0;
          lVar8 = lVar7 + 0xb0;
          Aska::CriticalSection::Enter() const(lVar8);
          Aska::TextureManager::RegisterTextureEx(Aska::TextureMemory::tagKey const*, bool, int, int)(lVar7,&plStack_70,0,0,1);
          Aska::CriticalSection::Leave() const(lVar8);
        }
      }
      param_1[0x1c] = *(long *)(param_2 + 0xe0);
      *(undefined4 *)(param_1 + 0x19) = *(undefined4 *)(param_2 + 200);
      *(undefined4 *)((long)param_1 + 0xcc) = *(undefined4 *)(param_2 + 0xcc);
      if (*(short *)(lVar9 + 0x70) != 0) {
        lVar8 = 0;
        puVar1 = PTR__ZTVN4Aska13MeshPrimitiveE_02cbcfd0 + 0x10;
        puVar10 = (undefined8 *)(lVar6 + (ulong)uVar3 * 8);
        do {
          puVar2 = puVar10 + 8;
          puVar11 = *(undefined8 **)(*(long *)(param_2 + 0xd0) + lVar8 * 8);
          Aska::PrimitiveBuffer::PrimitiveBuffer()(puVar2);
          *(undefined4 *)(puVar10 + 0xd) = 0;
          *(undefined1 *)((long)puVar10 + 0x6c) = 0;
          puVar10[8] = puVar1;
          *(undefined8 **)(param_1[0x1a] + lVar8 * 8) = puVar10;
          *puVar10 = *puVar11;
          puVar10[2] = puVar11[2];
          puVar10[4] = puVar11[4];
          puVar10[2] = puVar11[2];
          puVar10[3] = puVar11[3];
          Aska::RenderablePrimitive::Clone(Aska::RenderablePrimitive*)(puVar2,puVar11 + 8);
          Aska::RenderablePrimitive::SetKickBuffer()(puVar2);
          lVar8 = lVar8 + 1;
          puVar10 = puVar10 + 0xf;
        } while (lVar8 < (long)(ulong)*(ushort *)(lVar9 + 0x70));
      }
      Aska::MaterialList::Clone(Aska::MaterialList const*, bool)(param_1 + 0x1d,param_2 + 0xe8,param_3 & 1);
      uVar5 = 1;
      *(byte *)(param_1 + 0x15) = *(byte *)(param_1 + 0x15) | 1;
    }
  }
  else {
    uVar5 = 0;
  }
  return uVar5;
}

// ==== Aska::AofHandler::InitializeShaderKey(Aska::RenderPass*, int, bool)
// vaddr 0x20c0454 | ghidra 0x21c0454 | size 156 | symbol _ZN4Aska10AofHandler19InitializeShaderKeyEPNS_10RenderPassEib | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska10AofHandler19InitializeShaderKeyEPNS_10RenderPassEib
          (long param_1,long param_2,int param_3,uint param_4)

{
  byte bVar1;
  int iVar2;
  ulong uVar3;
  
  bVar1 = *(byte *)(param_2 + 0x2d);
  param_1 = param_1 + 0xe8;
  if (bVar1 == 0) {
    iVar2 = Aska::MaterialList::GetActualPerPixelLightCount() const(param_1);
    if (param_3 <= iVar2 && param_3 != -1) {
      iVar2 = param_3;
    }
    uVar3 = Aska::RenderPass::ReadyShaderKey(int, int, Aska::MaterialList*, bool)(param_2,0,iVar2,param_1,param_4 & 1);
    if ((uVar3 & 1) == 0) {
      return 0;
    }
  }
  else {
    uVar3 = Aska::RenderPass::ReadyShaderKey(int, int, Aska::MaterialList*, bool)(param_2,bVar1,
                            *(undefined2 *)
                             (PTR__ZN4Aska13ObjectManager20m_LightConfigurationE_02cbf638 +
                             (ulong)(uint)bVar1 * 4 + 2),param_1,param_4 & 1);
    if ((uVar3 & 1) == 0) {
      return 0;
    }
  }
  return 1;
}

// ==== Aska::AofHandler::InitializeShader(Aska::RenderPass*, int, bool, bool)
// vaddr 0x20c04f0 | ghidra 0x21c04f0 | size 168 | symbol _ZN4Aska10AofHandler16InitializeShaderEPNS_10RenderPassEibb | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZN4Aska10AofHandler16InitializeShaderEPNS_10RenderPassEibb
                (long param_1,long param_2,int param_3,uint param_4,ulong param_5)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  ulong uVar4;
  
  bVar1 = *(byte *)(param_2 + 0x2d);
  param_1 = param_1 + 0xe8;
  if (bVar1 == 0) {
    iVar3 = Aska::MaterialList::GetActualPerPixelLightCount() const(param_1);
    if (param_3 <= iVar3 && param_3 != -1) {
      iVar3 = param_3;
    }
    uVar2 = Aska::RenderPass::ReadyShaderKey(int, int, Aska::MaterialList*, bool)(param_2,0,iVar3,param_1,param_4 & 1);
  }
  else {
    uVar2 = Aska::RenderPass::ReadyShaderKey(int, int, Aska::MaterialList*, bool)(param_2,bVar1,
                            *(undefined2 *)
                             (PTR__ZN4Aska13ObjectManager20m_LightConfigurationE_02cbf638 +
                             (ulong)(uint)bVar1 * 4 + 2),param_1,param_4 & 1);
  }
  if (((uVar2 & 1) != 0) && ((param_5 & 1) == 0)) {
    uVar4 = (*(code *)PTR__ZN4Aska10RenderPass11ReadyShaderEv_02caea70)(param_2);
    return uVar4;
  }
  return (ulong)(uVar2 & 1);
}

// ==== Aska::AofHandler::CheckShaderKeyIsInAHSLPrebuiltDatabase(Aska::RenderPass*)
// vaddr 0x20c0598 | ghidra 0x21c0598 | size 4 | symbol _ZN4Aska10AofHandler38CheckShaderKeyIsInAHSLPrebuiltDatabaseEPNS_10RenderPassE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10AofHandler38CheckShaderKeyIsInAHSLPrebuiltDatabaseEPNS_10RenderPassE(void)

{
  return;
}

// ==== Aska::AofHandler::MakeRenderContext(Aska::RenderContext*, Aska::AofObject*, Aska::RENDERINFO const*, Aska::RenderPass*, Aska::CommandBufferManager*)
// vaddr 0x20c059c | ghidra 0x21c059c | size 3464 | symbol _ZN4Aska10AofHandler17MakeRenderContextEPNS_13RenderContextEPNS_9AofObjectEPKNS_10RENDERINFOEPNS_10RenderPassEPNS_20CommandBufferManagerE | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Type propagation algorithm not settling */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8
_ZN4Aska10AofHandler17MakeRenderContextEPNS_13RenderContextEPNS_9AofObjectEPKNS_10RENDERINFOEPNS_10RenderPassEPNS_20CommandBufferManagerE
          (long param_1,long param_2,long *param_3,short *param_4,long param_5)

{
  uint uVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  float fVar4;
  char cVar5;
  byte bVar6;
  byte bVar7;
  ushort uVar8;
  char cVar9;
  undefined8 *puVar10;
  short sVar11;
  undefined *puVar12;
  float *pfVar13;
  undefined8 *puVar14;
  undefined8 uVar15;
  uint uVar16;
  undefined8 *puVar17;
  long lVar18;
  code *pcVar19;
  ulong uVar20;
  long lVar21;
  long lVar22;
  ulong uVar23;
  long *plVar24;
  ulong uVar25;
  float *pfVar26;
  long lVar27;
  long lVar28;
  int iVar29;
  byte bVar30;
  float fVar31;
  float fVar32;
  float fVar33;
  float fVar34;
  short sStack_19c;
  undefined8 *puStack_188;
  undefined8 uStack_180;
  undefined8 uStack_178;
  undefined8 uStack_170;
  undefined8 uStack_168;
  undefined8 uStack_160;
  undefined8 uStack_158;
  undefined8 uStack_150;
  undefined8 uStack_148;
  undefined8 uStack_140;
  ulong uStack_138;
  undefined8 uStack_130;
  undefined8 uStack_128;
  undefined8 uStack_120;
  undefined8 uStack_118;
  undefined8 uStack_110;
  undefined8 uStack_108;
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
  long lStack_78;
  
  lVar27 = *(long *)(param_4 + 8);
  puVar17 = (undefined8 *)(param_2 + 0x7fU & 0xffffffffffffff80);
  uVar1 = ((int)param_2 + 0x230) - (int)puVar17 & 0xffffff80;
  if (0 < (int)uVar1) {
    uVar1 = uVar1 >> 5;
    Hint_Prefetch(puVar17,2,2,0);
    if (uVar1 != 0) {
      iVar29 = -uVar1;
      do {
        Hint_Prefetch(puVar17 + 4,2,2,0);
        iVar29 = iVar29 + 1;
        puVar17[1] = 0;
        *puVar17 = 0;
        puVar17[3] = 0;
        puVar17[2] = 0;
        puVar17 = puVar17 + 4;
      } while (iVar29 != 0);
    }
  }
  *(undefined8 *)(param_2 + 0x10) = 0;
  puVar12 = PTR__ZN4Aska6Camera19m_avDisableFogConstE_02cb91a8;
  if ((*(ushort *)(param_5 + 0x2f) >> 10 & 1) != 0) {
    puVar12 = (undefined *)Aska::Camera::GetFogConst()(lVar27);
  }
  *(undefined **)(param_2 + 0x150) = puVar12;
  if (((*(byte *)((long)param_3 + 0x1b5) >> 1 & 1) == 0) || (param_3[0x78] != 0)) {
    lVar18 = 0;
  }
  else {
    lVar18 = param_3[(ulong)(*(byte *)((long)param_3 + 0x387) ^ 1) + 0x79];
  }
  *(long *)(param_2 + 0x18) = lVar18;
  *(long *)(param_2 + 0x20) = param_5;
  *(byte *)(param_2 + 10) = *(byte *)(param_2 + 10) | 4;
  pfVar13 = (float *)(**(code **)(*param_3 + 0x98))(param_3);
  if ((*(byte *)((long)param_4 + 3) & 7) == 4) {
    puVar17 = (undefined8 *)(lVar27 + 0xa20);
    fVar33 = *(float *)(lVar27 + 0xde0) *
             *(float *)PTR__ZN4Aska6Camera23m_fMasterMotionBlurRateE_02cb81b8 *
             *(float *)(param_3 + 0x9e);
    uStack_100 = CONCAT44(pfVar13[1] + fVar33 * (*(float *)((long)param_3 + 0x564) - pfVar13[1]),
                          *pfVar13 + fVar33 * (*(float *)(param_3 + 0xac) - *pfVar13));
    uStack_f8 = CONCAT44(pfVar13[3] + fVar33 * (*(float *)((long)param_3 + 0x56c) - pfVar13[3]),
                         pfVar13[2] + fVar33 * (*(float *)(param_3 + 0xad) - pfVar13[2]));
    uStack_f0 = CONCAT44(pfVar13[5] + fVar33 * (*(float *)((long)param_3 + 0x574) - pfVar13[5]),
                         pfVar13[4] + fVar33 * (*(float *)(param_3 + 0xae) - pfVar13[4]));
    uStack_e8 = CONCAT44(pfVar13[7] + fVar33 * (*(float *)((long)param_3 + 0x57c) - pfVar13[7]),
                         pfVar13[6] + fVar33 * (*(float *)(param_3 + 0xaf) - pfVar13[6]));
    uStack_e0 = CONCAT44(pfVar13[9] + fVar33 * (*(float *)((long)param_3 + 0x584) - pfVar13[9]),
                         pfVar13[8] + fVar33 * (*(float *)(param_3 + 0xb0) - pfVar13[8]));
    uStack_d8 = CONCAT44(pfVar13[0xb] + fVar33 * (*(float *)((long)param_3 + 0x58c) - pfVar13[0xb]),
                         pfVar13[10] + fVar33 * (*(float *)(param_3 + 0xb1) - pfVar13[10]));
    uStack_d0 = CONCAT44(pfVar13[0xd] + fVar33 * (*(float *)((long)param_3 + 0x594) - pfVar13[0xd]),
                         pfVar13[0xc] + fVar33 * (*(float *)(param_3 + 0xb2) - pfVar13[0xc]));
    uStack_c8 = CONCAT44(pfVar13[0xf] + fVar33 * (*(float *)((long)param_3 + 0x59c) - pfVar13[0xf]),
                         pfVar13[0xe] + fVar33 * (*(float *)(param_3 + 0xb3) - pfVar13[0xe]));
    uStack_b8 = *(undefined8 *)(lVar27 + 0xda8);
    uStack_c0 = *(undefined8 *)(lVar27 + 0xda0);
    uStack_a8 = *(undefined8 *)(lVar27 + 0xdb8);
    uStack_b0 = *(undefined8 *)(lVar27 + 0xdb0);
    uStack_98 = *(undefined8 *)(lVar27 + 0xdc8);
    uStack_a0 = *(undefined8 *)(lVar27 + 0xdc0);
    uStack_88 = *(undefined8 *)(lVar27 + 0xdd8);
    uStack_90 = *(undefined8 *)(lVar27 + 0xdd0);
    Aska::Matrix::Mul(Aska::Matrix const*)(&uStack_c0,&uStack_100);
    lVar18 = *(long *)(lVar27 + 0xe18);
    *(undefined8 *)(param_2 + 0x1c8) = uStack_b8;
    *(undefined8 *)(param_2 + 0x1c0) = uStack_c0;
    *(undefined8 *)(param_2 + 0x1d8) = uStack_a8;
    *(undefined8 *)(param_2 + 0x1d0) = uStack_b0;
    *(undefined8 *)(param_2 + 0x1e8) = uStack_98;
    *(undefined8 *)(param_2 + 0x1e0) = uStack_a0;
    *(undefined8 *)(param_2 + 0x1f8) = uStack_88;
    *(undefined8 *)(param_2 + 0x1f0) = uStack_90;
    fVar31 = *(float *)(lVar18 + 0x2ac);
    *(float *)(param_2 + 0x200) = fVar31;
    *(float *)(param_2 + 0x204) = 0.5 / fVar31;
    fVar31 = *(float *)(lVar18 + 0x2b4);
    *(float *)(param_2 + 0x20c) = fVar33;
    *(float *)(param_2 + 0x208) = 1.0 / fVar31;
  }
  else if ((*(byte *)((long)param_3 + 0x1b6) & 1) == 0) {
    cVar5 = *(char *)(lVar27 + 0xeb1);
    if (cVar5 == '\x01') {
code_r0x021c0924:
      lVar18 = 1;
    }
    else {
      if (cVar5 == -1) {
        cVar9 = *PTR__ZN4Aska6Camera15m_cActiveTileNoE_02cbb2c8;
      }
      else {
        cVar9 = *PTR__ZN4Aska6Camera15m_cActiveTileNoE_02cbb2c8;
        if (cVar5 <= cVar9) goto code_r0x021c0924;
      }
      lVar18 = (long)cVar9 + 2;
    }
    puVar17 = (undefined8 *)(lVar27 + lVar18 * 0x40 + 0x9e0);
  }
  else {
    puVar17 = (undefined8 *)(lVar27 + 0x9e0);
  }
  uVar1 = *(uint *)(param_3 + 0x36);
  uVar16 = *(uint *)(param_3 + 0x32);
  if ((uVar1 >> 0x11 & 1) != 0) {
    uStack_f8 = _UNK_027dbb08;
    uStack_100 = _UNK_027dbb00;
    uStack_e8 = _UNK_027dbb18;
    uStack_f0 = _UNK_027dbb10;
    fVar31 = 0.0;
    uStack_d8 = _UNK_027dbb28;
    uStack_e0 = _UNK_027dbb20;
    uStack_c8 = _UNK_027dbb38;
    uStack_d0 = _UNK_027dbb30;
    uStack_b8 = puVar17[1];
    uStack_c0 = *puVar17;
    uStack_a8 = puVar17[3];
    uStack_b0 = puVar17[2];
    uStack_98 = puVar17[5];
    uStack_a0 = puVar17[4];
    uStack_88 = puVar17[7];
    uStack_90 = puVar17[6];
    if ((uVar1 >> 0x10 & 1) != 0) {
      fVar31 = *(float *)((long)param_3 + 0x1c4);
    }
    fVar34 = *(float *)(param_3 + 0x39);
    fVar33 = (float)Aska::RenderableObject::GetShallowestZ(int) const(param_3,(long)*param_4);
    fVar32 = (float)Aska::RenderableObject::GetDeepestZ(int) const(param_3,(long)*param_4);
    fVar31 = fVar31 + fVar33 + ((fVar31 + fVar32) - (fVar31 + fVar33)) * 0.5;
    uStack_f8 = uStack_f8 & 0xffffffff;
    uStack_e8 = uStack_e8 & 0xffffffff;
    uStack_d8 = CONCAT44((*(float *)(lVar27 + 0x988) +
                         *(float *)(lVar27 + 0x98c) / (fVar31 - fVar34)) -
                         (*(float *)(lVar27 + 0x988) + *(float *)(lVar27 + 0x98c) / fVar31),
                         (undefined4)uStack_d8);
    puVar17 = &uStack_c0;
    Aska::Matrix::MulFromLeft(Aska::Matrix const*)(&uStack_c0,&uStack_100);
  }
  if ((0 < *param_4) &&
     (((*(byte *)((long)param_4 + 3) & 7) != 0 || ((*(byte *)(lVar27 + 0xeb4) >> 2 & 1) == 0)))) {
    uStack_f8 = puVar17[1];
    uStack_100 = *puVar17;
    uStack_e8 = puVar17[3];
    uStack_f0 = puVar17[2];
    uStack_d8 = puVar17[5];
    uStack_e0 = puVar17[4];
    uStack_c8 = puVar17[7];
    uStack_d0 = puVar17[6];
    uStack_138 = _UNK_027dbb08;
    uStack_140 = _UNK_027dbb00;
    uStack_118 = _UNK_027dbb28;
    uStack_120 = _UNK_027dbb20;
    uStack_108 = _UNK_027dbb38;
    uStack_110 = _UNK_027dbb30;
    puVar17 = &uStack_100;
    uStack_128 = _UNK_029c68f8;
    uStack_130 = _UNK_029c68f0;
    Aska::Matrix::MulFromLeft(Aska::Matrix const*)(&uStack_100,&uStack_140);
  }
  if (((*(byte *)((long)param_4 + 3) & 7) == 2) &&
     (fVar31 = *(float *)PTR__ZN4Aska13ShadowManager24m_fMasterShaderDepthBiasE_02cb8d10,
     fVar31 != 1.0)) {
    uStack_138 = puVar17[1];
    uStack_140 = *puVar17;
    uStack_128 = puVar17[3];
    uStack_130 = puVar17[2];
    puVar14 = puVar17 + 4;
    puVar10 = puVar17 + 5;
    uStack_108 = puVar17[7];
    uStack_110 = puVar17[6];
    puVar17 = &uStack_140;
    uStack_120 = CONCAT44(fVar31 * (float)((ulong)*puVar14 >> 0x20),fVar31 * (float)*puVar14);
    uStack_118 = CONCAT44(fVar31 * (float)((ulong)*puVar10 >> 0x20),fVar31 * (float)*puVar10);
  }
  if (((uVar1 & 0x600) == 0) || ((uVar16 & 0x1c) == 0)) {
    if ((uVar1 & 7) != 0) {
      pcVar19 = *(code **)(*param_3 + 0x1c8);
      goto code_r0x021c0b04;
    }
  }
  else {
    pcVar19 = *(code **)(*param_3 + 0x1d0);
code_r0x021c0b04:
    pfVar13 = (float *)(*pcVar19)(param_3,lVar27);
  }
  Aska::Matrix::Mul(Aska::Matrix const*, Aska::Matrix const*)(param_2 + 0x60,puVar17,pfVar13);
  uVar15 = *(undefined8 *)pfVar13;
  *(undefined8 *)(param_2 + 0xe8) = *(undefined8 *)(pfVar13 + 2);
  *(undefined8 *)(param_2 + 0xe0) = uVar15;
  uVar15 = *(undefined8 *)(pfVar13 + 4);
  *(undefined8 *)(param_2 + 0xf8) = *(undefined8 *)(pfVar13 + 6);
  *(undefined8 *)(param_2 + 0xf0) = uVar15;
  uVar15 = *(undefined8 *)(pfVar13 + 8);
  *(undefined8 *)(param_2 + 0x108) = *(undefined8 *)(pfVar13 + 10);
  *(undefined8 *)(param_2 + 0x100) = uVar15;
  if ((int)param_3[0x6f] < 0) {
    lVar18 = param_3[0xd0];
    if (lVar18 != 0) {
      *(undefined1 *)(param_2 + 0x3c) = *(undefined1 *)(lVar18 + 0x99);
      iVar29 = *(int *)(lVar18 + (ulong)*(byte *)(lVar18 + 0x98) * 0x10 +
                        (ulong)*(uint *)(param_3 + 0xd1) * 8 + 0x38);
      if (iVar29 != 0) {
        *(int *)(param_2 + 0x38) = iVar29;
        iVar29 = Aska::RenderDeviceGL::GetGLVersion() const(*(undefined8 *)PTR__ZN4Aska12g_pRenderDevE_02cbb1a0);
        if (iVar29 == 0) {
          *(undefined8 *)(param_2 + 0x28) =
               *(undefined8 *)(lVar18 + (ulong)*(byte *)(lVar18 + 0x98) * 8 + 0x58);
          *(ulong *)(param_2 + 0x30) =
               *(long *)(lVar18 + (ulong)*(byte *)(lVar18 + 0x98) * 8 + 0x68) +
               (ulong)*(uint *)(lVar18 + (ulong)*(byte *)(lVar18 + 0x98) * 0x10 +
                                (ulong)*(uint *)(param_3 + 0xd1) * 8 + 0x3c) * 4;
        }
        else {
          uVar15 = Aska::MeshGenerator::GetActiveInstanceResource(Aska::MeshGenerator::OBJ_TYPE)(lVar18,(int)param_3[0xd1]);
          *(undefined8 *)(param_2 + 0x40) = uVar15;
        }
        goto code_r0x021c0b48;
      }
    }
    return 0;
  }
  *(undefined1 *)(param_2 + 0x3c) = 0;
code_r0x021c0b48:
  uVar20 = *(ulong *)(param_5 + 0x10);
  *(ulong *)(param_2 + 0x140) = uVar20;
  uVar23 = *(ulong *)(param_5 + 0x18);
  *(ulong *)(param_2 + 0x148) = uVar23;
  uVar1 = *(uint *)(param_5 + 0x20);
  if ((uVar1 >> 0x10 & 1) != 0) {
    *(ulong *)(param_2 + 0x140) = uVar20 | 4;
    *(ulong *)(param_2 + 0x148) = uVar23 | 4;
  }
  puVar14 = (undefined8 *)Aska::AofObject::GetObjectRenderState(unsigned int)(param_3,*(byte *)((long)param_4 + 3) & 7);
  *(undefined8 *)(param_2 + 0x48) = *puVar14;
  *(undefined8 *)(param_2 + 0x50) = puVar14[1];
  *(undefined4 *)(param_2 + 0x110) = *(undefined4 *)(lVar27 + 0xc60);
  *(undefined4 *)(param_2 + 0x114) = *(undefined4 *)(lVar27 + 0xc64);
  *(undefined4 *)(param_2 + 0x118) = *(undefined4 *)(lVar27 + 0xc68);
  *(undefined4 *)(param_2 + 0x11c) = *(undefined4 *)(lVar27 + 0xc6c);
  uVar16 = (uint)*(undefined8 *)(param_5 + 0x18);
  if ((((uVar16 >> 2 & 1) != 0) || ((uVar1 >> 0x10 & 1) != 0)) ||
     (((uint)*(undefined8 *)(param_5 + 0x10) >> 2 & 1) != 0)) {
    uVar15 = *(undefined8 *)(lVar27 + 0x130);
    *(undefined8 *)(param_2 + 0x178) = *(undefined8 *)(lVar27 + 0x138);
    *(undefined8 *)(param_2 + 0x170) = uVar15;
    uVar15 = *(undefined8 *)(lVar27 + 0x140);
    *(undefined8 *)(param_2 + 0x188) = *(undefined8 *)(lVar27 + 0x148);
    *(undefined8 *)(param_2 + 0x180) = uVar15;
    uVar15 = *(undefined8 *)(lVar27 + 0x150);
    *(undefined8 *)(param_2 + 0x198) = *(undefined8 *)(lVar27 + 0x158);
    *(undefined8 *)(param_2 + 400) = uVar15;
    uVar16 = (uint)*(undefined8 *)(param_5 + 0x18);
  }
  if ((uVar16 >> 0x11 & 1) != 0) {
    *(undefined4 *)(param_2 + 0x1b0) = *(undefined4 *)(lVar27 + 0xc70);
    *(undefined4 *)(param_2 + 0x1b4) = *(undefined4 *)(lVar27 + 0xc74);
    *(undefined4 *)(param_2 + 0x1b8) = *(undefined4 *)(lVar27 + 0xc78);
    *(undefined4 *)(param_2 + 0x1bc) = *(undefined4 *)(lVar27 + 0xc7c);
    uVar16 = (uint)*(undefined8 *)(param_5 + 0x18);
  }
  if (((uVar16 >> 9 & 1) != 0) || ((*(byte *)(param_5 + 0x11) >> 1 & 1) != 0)) {
    uVar15 = *puVar17;
    *(undefined8 *)(param_2 + 0xa8) = puVar17[1];
    *(undefined8 *)(param_2 + 0xa0) = uVar15;
    uVar15 = puVar17[2];
    *(undefined8 *)(param_2 + 0xb8) = puVar17[3];
    *(undefined8 *)(param_2 + 0xb0) = uVar15;
    uVar15 = puVar17[4];
    *(undefined8 *)(param_2 + 200) = puVar17[5];
    *(undefined8 *)(param_2 + 0xc0) = uVar15;
    uVar15 = puVar17[6];
    *(undefined8 *)(param_2 + 0xd8) = puVar17[7];
    *(undefined8 *)(param_2 + 0xd0) = uVar15;
    uVar16 = (uint)*(undefined8 *)(param_5 + 0x18);
  }
  if ((uVar16 >> 0xc & 1) == 0) {
    bVar6 = *(byte *)(param_5 + 0x12);
    puVar3 = (undefined4 *)PTR__ZN4Aska6Vector10zeroVectorE_02cc0768;
  }
  else {
    *(undefined4 *)(param_2 + 0x1a0) = *(undefined4 *)(lVar27 + 0xc80);
    *(undefined4 *)(param_2 + 0x1a4) = *(undefined4 *)(lVar27 + 0xc84);
    *(undefined4 *)(param_2 + 0x1a8) = *(undefined4 *)(lVar27 + 0xc88);
    *(undefined4 *)(param_2 + 0x1ac) = *(undefined4 *)(lVar27 + 0xc8c);
    *(int *)(param_2 + 0x1a0) = (int)param_3[0x39];
    bVar6 = *(byte *)(param_5 + 0x12);
    puVar3 = (undefined4 *)PTR__ZN4Aska6Vector10zeroVectorE_02cc0768;
  }
  PTR__ZN4Aska6Vector10zeroVectorE_02cc0768 = (undefined *)puVar3;
  if ((bVar6 & 1) != 0) {
    puVar2 = puVar3;
    if (param_3[0x30] != 0) {
      puVar2 = (undefined4 *)(param_3[0x30] + 0x70);
    }
    *(undefined4 *)(param_2 + 0x210) = *puVar2;
    *(undefined4 *)(param_2 + 0x214) = puVar2[1];
    *(undefined4 *)(param_2 + 0x218) = puVar2[2];
    *(undefined4 *)(param_2 + 0x21c) = puVar2[3];
    if (param_3[0x30] != 0) {
      puVar3 = (undefined4 *)(param_3[0x30] + 0x80);
    }
    *(undefined4 *)(param_2 + 0x220) = *puVar3;
    *(undefined4 *)(param_2 + 0x224) = puVar3[1];
    *(undefined4 *)(param_2 + 0x228) = puVar3[2];
    *(undefined4 *)(param_2 + 0x22c) = puVar3[3];
  }
  bVar6 = *(byte *)(param_5 + 0x26);
  pfVar13 = (float *)Aska::RenderContext::AllocBatch(int)(param_2,(ulong)bVar6);
  uVar15 = 0;
  if (pfVar13 != (float *)0x0) {
    puVar17 = (undefined8 *)((long)pfVar13 + 0x7fU & 0xffffffffffffff80);
    uVar1 = ((int)pfVar13 + (uint)bVar6 * 0x130) - (int)puVar17 & 0xffffff80;
    if (0 < (int)uVar1) {
      uVar1 = uVar1 >> 5;
      Hint_Prefetch(puVar17,2,2,0);
      if (uVar1 != 0) {
        iVar29 = -uVar1;
        do {
          Hint_Prefetch(puVar17 + 4,2,2,0);
          iVar29 = iVar29 + 1;
          puVar17[1] = 0;
          *puVar17 = 0;
          puVar17[3] = 0;
          puVar17[2] = 0;
          puVar17 = puVar17 + 4;
        } while (iVar29 != 0);
      }
    }
    if ((~*(uint *)(param_3 + 0x6f) & 0xc) == 0) {
      uStack_178 = *(undefined8 *)(lVar27 + 0x138);
      uStack_180 = *(undefined8 *)(lVar27 + 0x130);
      uStack_168 = *(undefined8 *)(lVar27 + 0x148);
      uStack_170 = *(undefined8 *)(lVar27 + 0x140);
      uStack_158 = *(undefined8 *)(lVar27 + 0x158);
      uStack_160 = *(undefined8 *)(lVar27 + 0x150);
      uStack_148 = *(undefined8 *)(lVar27 + 0x168);
      uStack_150 = *(undefined8 *)(lVar27 + 0x160);
      uVar15 = (**(code **)(*param_3 + 0x98))(param_3);
      Aska::Matrix::Mul(Aska::Matrix const*)(&uStack_180,uVar15);
    }
    fVar31 = _UNK_028014f8;
    if (bVar6 == 0) {
      sStack_19c = 0;
    }
    else {
      sStack_19c = 0;
      lVar27 = param_3[0x74];
      bVar7 = *(byte *)((long)param_4 + 3);
      uVar20 = 0;
      do {
        lVar18 = *(long *)(*(long *)(param_1 + 0xd0) + uVar20 * 8);
        if (((lVar18 != 0) &&
            ((*(byte *)(*(long *)(param_5 + 8) + uVar20 * 0x1b8 + 0x58) >> 2 & 1) == 0)) &&
           (((bVar7 & 7) != 1 ||
            (*(char *)(*(long *)(*(long *)(param_1 + 0x100) + uVar20 * 0x2a0) + 0x14) == '\0')))) {
          pfVar26 = pfVar13 + 8;
          iVar29 = (int)uVar20;
          *(char *)(pfVar13 + 0x45) = (char)uVar20;
          memset(pfVar26,0,0x98);
          pfVar13[0x34] = 0.0;
          pfVar13[0x35] = 0.0;
          *(undefined2 *)(pfVar13 + 0x44) = 0;
          if (lVar27 != 0) {
            lVar21 = **(long **)(*(long *)(param_1 + 0xd0) + uVar20 * 8);
            if (*(short *)(lVar21 + 0x1c) == 0) {
              bVar30 = *(byte *)(lVar27 + 10);
            }
            else {
              iVar29 = (int)*(char *)(lVar21 + 0x19);
              bVar30 = *(byte *)(lVar27 + 10);
            }
            if ((bVar30 >> 1 & 1) == 0) {
              sVar11 = Aska::SkinMatricesBase::GetSkinMatrixCount(int) const(lVar27,iVar29);
              uVar8 = *(ushort *)(*(long *)(lVar27 + 0x40) + (long)iVar29 * 2);
              lVar21 = *(long *)(lVar27 + (ulong)*(byte *)(lVar27 + 0xb) * 8 + 0x18);
              *(short *)(pfVar13 + 0x44) = sVar11 * 3;
              *(ulong *)(pfVar13 + 0x34) = lVar21 + (ulong)uVar8 * 0x30;
            }
            else {
              lVar21 = *(long *)(lVar27 + (ulong)*(byte *)(lVar27 + 0xb) * 8 + 0x50);
              uVar15 = 0;
              if (lVar21 != 0) {
                uVar15 = **(undefined8 **)(lVar21 + 0x60);
              }
              *(undefined8 *)(pfVar13 + 0x28) = uVar15;
              if ((*(byte *)((long)param_4 + 3) & 7) == 4) {
                if ((*(byte *)(lVar27 + 10) >> 1 & 1) == 0) {
                  uVar15 = 0;
                }
                else {
                  uVar15 = 0;
                  if (*(long *)(lVar27 + 0x60) != 0) {
                    uVar15 = **(undefined8 **)(*(long *)(lVar27 + 0x60) + 0x60);
                  }
                }
                *(undefined8 *)(pfVar13 + 0x2a) = uVar15;
              }
            }
          }
          *(undefined1 *)((long)pfVar13 + 0x112) = 0;
          *(long *)(pfVar13 + 0x2e) = lVar18 + 0x40;
          *(undefined8 *)(pfVar13 + 0x30) =
               *(undefined8 *)(*(long *)(param_5 + 8) + uVar20 * 0x1b8 + 0x50);
          uVar8 = *(ushort *)(param_5 + 0x2f);
          lVar18 = param_5;
          while ((uVar8 >> 8 & 1) != 0) {
            lVar18 = *(long *)(lVar18 + 0x38);
            uVar8 = *(ushort *)(lVar18 + 0x2f);
          }
          *(undefined8 *)(pfVar13 + 0x32) =
               *(undefined8 *)(*(long *)(lVar18 + 8) + uVar20 * 0x1b8 + 0x48);
          lVar18 = 0;
          if (*(long *)(param_1 + 0x100) != 0) {
            lVar18 = *(long *)(param_1 + 0x100) + uVar20 * 0x2a0 + 0x10;
          }
          bVar30 = *(byte *)(lVar18 + 0x231);
          *(long *)(pfVar13 + 0x42) = lVar18;
          fVar33 = (float)NEON_ucvtf((uint)bVar30);
          pfVar13[0x36] = fVar33 / fVar31;
          lVar28 = *(long *)(param_5 + 8);
          lVar21 = lVar28 + uVar20 * 0x1b8;
          lVar22 = *(long *)(lVar21 + 0x30);
          if (lVar22 != 0) {
            *(long *)(pfVar13 + 0x38) = lVar22;
            *(undefined8 *)(pfVar13 + 0x3c) = **(undefined8 **)(lVar22 + 0x10);
            puVar17 = *(undefined8 **)(lVar28 + uVar20 * 0x1b8 + 0x40);
            if (puVar17 == (undefined8 *)0x0) {
              pfVar13[0x3a] = 0.0;
              pfVar13[0x3b] = 0.0;
            }
            else {
              *(undefined8 **)(pfVar13 + 0x3a) = puVar17;
              *(undefined8 *)(pfVar13 + 0x3e) = *puVar17;
            }
            fVar33 = *(float *)(param_3 + 0x7e);
            *pfVar13 = fVar33;
            fVar32 = *(float *)((long)param_3 + 0x3f4);
            pfVar13[1] = fVar32;
            fVar34 = *(float *)(param_3 + 0x7f);
            pfVar13[2] = fVar34;
            fVar4 = *(float *)((long)param_3 + 0x3fc);
            pfVar13[3] = fVar4;
            pfVar13[4] = *(float *)(param_3 + 0x80);
            pfVar13[5] = *(float *)((long)param_3 + 0x404);
            pfVar13[6] = *(float *)(param_3 + 0x81);
            pfVar13[7] = *(float *)((long)param_3 + 0x40c);
            if (*(char *)(lVar18 + 0x230) != -1) {
              *pfVar13 = *(float *)(lVar18 + 0x220) * fVar33;
              pfVar13[1] = *(float *)(lVar18 + 0x224) * fVar32;
              pfVar13[2] = *(float *)(lVar18 + 0x228) * fVar34;
              pfVar13[3] = *(float *)(lVar18 + 0x22c) * fVar4;
            }
            bVar30 = *(byte *)(lVar28 + uVar20 * 0x1b8 + 0x58);
            if ((*(byte *)(param_1 + 0x108) >> 6 & 1) == 0) {
              lVar22 = 0;
            }
            else {
              iVar29 = Aska::AofObject::GetActualLightConfiguration() const(param_3);
              if (iVar29 == 0) {
                uVar23 = (ulong)*(byte *)(lVar18 + 0x248);
              }
              else {
                uVar23 = 1;
              }
              uVar25 = (ulong)(*(byte *)((long)param_3 + 0x387) ^ 1);
              if (param_3[0x78] == 0) {
                lVar22 = param_3[uVar25 + 0x79];
              }
              else {
                lVar22 = param_3[0x78] + uVar25 * 0x1a90;
              }
              lVar22 = lVar22 + uVar23 * 0x550;
            }
            *(long *)(pfVar13 + 0x40) = lVar22;
            if (*(char *)((long)param_3 + 0x38f) != *(char *)((long)param_3 + 0x38e)) {
              if ((((bVar30 >> 1 & 1) != 0) || (*(short *)(lVar18 + 0x238) != 0)) ||
                 (uVar23 = Aska::RenderPassBatch::GetAssertionShaderCache(Aska::BindedVSCache**, Aska::ShaderCache**, unsigned int)(lVar21,&lStack_78,&puStack_188,(short)param_3[0x72]),
                 (uVar23 & 1) == 0)) goto code_r0x021c11a0;
              *(long *)(pfVar13 + 0x38) = lStack_78;
              *(undefined8 *)(pfVar13 + 0x3c) = **(undefined8 **)(lStack_78 + 0x10);
              if (puStack_188 == (undefined8 *)0x0) {
                pfVar13[0x3a] = 0.0;
                pfVar13[0x3b] = 0.0;
              }
              else {
                *(undefined8 **)(pfVar13 + 0x3a) = puStack_188;
                *(undefined8 *)(pfVar13 + 0x3e) = *puStack_188;
              }
            }
            bVar30 = *(byte *)(lVar28 + uVar20 * 0x1b8 + 0x59);
            uVar23 = (ulong)bVar30;
            if ((*(byte *)(lVar18 + 0x246) >> 6 & 1) == 0) {
              *(byte *)((long)pfVar13 + 0x113) = bVar30;
              if (bVar30 != 0) {
                plVar24 = (long *)(lVar28 + uVar20 * 0x1b8 + 0x60);
                pfVar26 = pfVar13 + 8;
                do {
                  uVar15 = 0;
                  if (*plVar24 != 0) {
                    uVar15 = **(undefined8 **)(*plVar24 + 0x60);
                  }
                  *(undefined8 *)pfVar26 = uVar15;
                  uVar23 = uVar23 - 1;
                  plVar24 = plVar24 + 1;
                  pfVar26 = pfVar26 + 2;
                } while (uVar23 != 0);
              }
            }
            else {
              plVar24 = (long *)(lVar28 + uVar20 * 0x1b8 + 0x60);
              if (bVar30 < 3) {
                lVar18 = *(long *)(lVar28 + uVar20 * 0x1b8 + 0x68);
                uVar15 = 0;
                if (lVar18 != 0) {
                  uVar15 = **(undefined8 **)(lVar18 + 0x60);
                }
                *(undefined8 *)(pfVar13 + 0x2c) = uVar15;
                *(undefined1 *)((long)pfVar13 + 0x113) = 1;
                lVar18 = *plVar24;
                uVar15 = 0;
                if (lVar18 != 0) {
                  uVar15 = **(undefined8 **)(lVar18 + 0x60);
                }
                *(undefined8 *)pfVar26 = uVar15;
              }
              else {
                lVar18 = *(long *)(lVar28 + uVar20 * 0x1b8 + 0x70);
                uVar15 = 0;
                if (lVar18 != 0) {
                  uVar15 = **(undefined8 **)(lVar18 + 0x60);
                }
                *(undefined8 *)(pfVar13 + 0x2c) = uVar15;
                *(undefined1 *)((long)pfVar13 + 0x113) = 2;
                lVar18 = *plVar24;
                uVar15 = 0;
                if (lVar18 != 0) {
                  uVar15 = **(undefined8 **)(lVar18 + 0x60);
                }
                *(undefined8 *)pfVar26 = uVar15;
                lVar18 = *(long *)(lVar28 + uVar20 * 0x1b8 + 0x68);
                uVar15 = 0;
                if (lVar18 != 0) {
                  uVar15 = **(undefined8 **)(lVar18 + 0x60);
                }
                *(undefined8 *)(pfVar13 + 10) = uVar15;
              }
            }
            pfVar13 = pfVar13 + 0x4c;
            sStack_19c = sStack_19c + 1;
          }
        }
code_r0x021c11a0:
        uVar20 = uVar20 + 1;
      } while (uVar20 != bVar6);
    }
    uVar15 = 1;
    *(short *)(param_2 + 8) = sStack_19c;
  }
  return uVar15;
}

// ==== Aska::AofHandler::Detach()
// vaddr 0x20c1324 | ghidra 0x21c1324 | size 248 | symbol _ZN4Aska10AofHandler6DetachEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10AofHandler6DetachEv(long param_1)

{
  long *plVar1;
  long lVar2;
  long lVar3;
  uint uVar4;
  uint uVar5;
  
  if ((*(byte *)(param_1 + 0xa8) & 6) != 0) {
    Aska::MaterialList::DeleteBuffer()(param_1 + 0xe8);
    lVar3 = *(long *)(param_1 + 0xb0);
    uVar4 = (uint)*(ushort *)(lVar3 + 0x7e);
    if (*(ushort *)(lVar3 + 0x7e) != 0) {
      lVar3 = lVar3 + 0xd0;
      do {
        Aska::ITextureHandler::DetachTexture(Aska::AFF::AskaFile const*, bool)(param_1,lVar3,0);
        uVar4 = uVar4 - 1;
        lVar3 = lVar3 + *(int *)(lVar3 + 0xc);
      } while (uVar4 != 0);
      lVar3 = *(long *)(param_1 + 0xb0);
    }
    if (*(long *)(param_1 + 0xd8) != 0) {
      operator delete[](void*)();
    }
    plVar1 = *(long **)(param_1 + 0xd0);
    if (plVar1 != (long *)0x0) {
      uVar4 = (uint)*(ushort *)(lVar3 + 0x70);
      if (*(ushort *)(lVar3 + 0x70) != 0) {
        uVar5 = 0;
        lVar2 = *plVar1;
        while( true ) {
          if (lVar2 != 0) {
            Aska::PrimitiveBuffer::ReleaseBuffer()(lVar2 + 0x40);
            Aska::PrimitiveBuffer::~PrimitiveBuffer()(lVar2 + 0x40);
            uVar4 = (uint)*(ushort *)(lVar3 + 0x70);
          }
          uVar5 = uVar5 + 1;
          if (uVar4 <= uVar5) break;
          lVar2 = *(long *)(*(long *)(param_1 + 0xd0) + (ulong)uVar5 * 8);
        }
        plVar1 = *(long **)(param_1 + 0xd0);
      }
      if (plVar1 != (long *)0x0) {
        operator delete[](void*)();
      }
      *(undefined8 *)(param_1 + 0xd0) = 0;
    }
    if (*(long **)(param_1 + 0x328) != (long *)0x0) {
      (**(code **)(**(long **)(param_1 + 0x328) + 8))();
      *(undefined8 *)(param_1 + 0x328) = 0;
    }
    *(byte *)(param_1 + 0xa8) = *(byte *)(param_1 + 0xa8) & 0xf8;
  }
  return;
}

// ==== Aska::AofHandler::AofHandler()
// vaddr 0x20c141c | ghidra 0x21c141c | size 400 | symbol _ZN4Aska10AofHandlerC2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10AofHandlerC1Ev(long *param_1)

{
  long *plVar1;
  undefined *puVar2;
  long lVar3;
  char cVar4;
  bool bVar5;
  long lVar6;
  uint uVar7;
  long *plStack_40;
  undefined8 uStack_38;
  
  *(undefined4 *)(param_1 + 1) = 0;
  plVar1 = param_1 + 3;
  puVar2 = PTR__ZTVN4Aska16TBarrierSlimBaseINS_12TBarrierSlimILb1EEEEE_02cbf998 + 0x10;
  *param_1 = (long)(PTR__ZTVN4Aska15ITextureHandlerE_02cc0f80 + 0x10);
  param_1[2] = (long)puVar2;
  do {
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(plVar1,0x10);
    if (bVar5) {
      *(undefined4 *)plVar1 = 0;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
  Aska::Event::Event()(param_1 + 4);
  param_1[2] = (long)(PTR__ZTVN4Aska12TBarrierSlimILb1EEE_02cba3c0 + 0x10);
  *(undefined4 *)(param_1 + 0x11) = 0;
  do {
    if ((int)*plVar1 != 0) {
      ClearExclusiveLocal();
      uVar7 = 0;
      do {
        uVar7 = uVar7 + 1;
        if ((uVar7 & 0x1ff) == 0) {
          Aska::Thread::SleepU(unsigned int)(0);
        }
        while ((int)*plVar1 == 0) {
          cVar4 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(plVar1,0x10);
          if (bVar5) {
            *(undefined4 *)plVar1 = 1;
            cVar4 = ExclusiveMonitorsStatus();
          }
          if (cVar4 == '\0') goto code_r0x021c14d0;
        }
        ClearExclusiveLocal();
      } while( true );
    }
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(plVar1,0x10);
    if (bVar5) {
      *(undefined4 *)plVar1 = 1;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
code_r0x021c14d0:
  *(undefined4 *)((long)param_1 + 0x1c) = 0;
  *(undefined4 *)(param_1 + 3) = 0;
  *(undefined1 *)((long)param_1 + 0x94) = 0;
  do {
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(param_1 + 0x12,0x10);
    if (bVar5) {
      *(undefined4 *)(param_1 + 0x12) = 0;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
  uStack_38 = 0;
  lVar6 = *(long *)PTR__ZN4Aska6Global17m_pTextureManagerE_02cc19f0;
  lVar3 = lVar6 + 0xb0;
  plStack_40 = param_1;
  Aska::CriticalSection::Enter() const(lVar3);
  Aska::TextureManager::RegisterTextureEx(Aska::TextureMemory::tagKey const*, bool, int, int)(lVar6,&plStack_40,1,0,0);
  Aska::CriticalSection::Leave() const(lVar3);
  puVar2 = PTR__ZTVN4Aska10AofHandlerE_02cc3728;
  *(undefined8 *)((long)param_1 + 0xbc) = 0x3f8000003f800000;
  param_1[0x14] = (long)(puVar2 + 0xb8);
  param_1[0x13] = (long)(puVar2 + 0x90);
  *param_1 = (long)(puVar2 + 0x10);
  *(undefined1 *)((long)param_1 + 0xa9) = 0;
  param_1[0x16] = 0;
  *(undefined1 *)(param_1 + 0x17) = 0;
  *(undefined8 *)((long)param_1 + 0xdc) = 0;
  *(undefined8 *)((long)param_1 + 0xd4) = 0;
  *(undefined8 *)((long)param_1 + 0xcc) = 0;
  *(undefined8 *)((long)param_1 + 0xc4) = 0;
  *(byte *)(param_1 + 0x15) = *(byte *)(param_1 + 0x15) & 0xe0;
  *(undefined4 *)((long)param_1 + 0xe4) = 0;
  Aska::MaterialList::MaterialList()(param_1 + 0x1d);
  param_1[0x65] = 0;
  param_1[100] = 0;
  param_1[99] = 0;
  return;
}

// ==== Aska::AofHandler::~AofHandler()
// vaddr 0x20c1720 | ghidra 0x21c1720 | size 208 | symbol _ZN4Aska10AofHandlerD1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10AofHandlerD2Ev(long *param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  long lVar3;
  long lVar4;
  long *plVar5;
  
  puVar1 = PTR__ZTVN4Aska10AofHandlerE_02cc3728 + 0x90;
  puVar2 = PTR__ZTVN4Aska10AofHandlerE_02cc3728 + 0xb8;
  *param_1 = (long)(PTR__ZTVN4Aska10AofHandlerE_02cc3728 + 0x10);
  plVar5 = param_1 + 0x13;
  param_1[0x14] = (long)puVar2;
  *plVar5 = (long)puVar1;
  Aska::AofHandler::Detach()();
  Aska::MaterialList::DeleteBuffer()(param_1 + 0x1d);
  Aska::RenderPassManagerList::~RenderPassManagerList()(param_1 + 0x24);
  *plVar5 = (long)(PTR__ZTVN4Aska15IMappingHandlerE_02cc1230 + 0x10);
  lVar4 = *(long *)PTR__ZN4Aska6Global22m_pMappedMemoryManagerE_02cc0368;
  lVar3 = lVar4 + 8;
  Aska::CriticalSection::Enter() const(lVar3);
  Aska::MappedMemoryManager::RemoveHandlerEx(Aska::IMappingHandler const*)(lVar4,plVar5);
  Aska::CriticalSection::Leave() const(lVar3);
  *param_1 = (long)(PTR__ZTVN4Aska15ITextureHandlerE_02cc0f80 + 0x10);
  Aska::ITextureHandler::DetachTexture()(param_1);
  Aska::TBarrierSlim<true>::~TBarrierSlim()(param_1 + 2);
  *param_1 = (long)(PTR__ZTVN4Aska13TSmartPointerILb0EEE_02cc2320 + 0x10);
  return;
}

// ==== non-virtual thunk to Aska::AofHandler::~AofHandler()
// vaddr 0x20c17f0 | ghidra 0x21c17f0 | size 208 | symbol _ZThn152_N4Aska10AofHandlerD1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZThn152_N4Aska10AofHandlerD1Ev(long *param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  long lVar3;
  long *plVar4;
  long lVar5;
  
  puVar1 = PTR__ZTVN4Aska10AofHandlerE_02cc3728 + 0x90;
  puVar2 = PTR__ZTVN4Aska10AofHandlerE_02cc3728 + 0x10;
  plVar4 = param_1 + -0x13;
  param_1[1] = (long)(PTR__ZTVN4Aska10AofHandlerE_02cc3728 + 0xb8);
  *param_1 = (long)puVar1;
  *plVar4 = (long)puVar2;
  Aska::AofHandler::Detach()(plVar4);
  Aska::MaterialList::DeleteBuffer()(param_1 + 10);
  Aska::RenderPassManagerList::~RenderPassManagerList()(param_1 + 0x11);
  *param_1 = (long)(PTR__ZTVN4Aska15IMappingHandlerE_02cc1230 + 0x10);
  lVar5 = *(long *)PTR__ZN4Aska6Global22m_pMappedMemoryManagerE_02cc0368;
  lVar3 = lVar5 + 8;
  Aska::CriticalSection::Enter() const(lVar3);
  Aska::MappedMemoryManager::RemoveHandlerEx(Aska::IMappingHandler const*)(lVar5,param_1);
  Aska::CriticalSection::Leave() const(lVar3);
  *plVar4 = (long)(PTR__ZTVN4Aska15ITextureHandlerE_02cc0f80 + 0x10);
  Aska::ITextureHandler::DetachTexture()(plVar4);
  Aska::TBarrierSlim<true>::~TBarrierSlim()(param_1 + -0x11);
  *plVar4 = (long)(PTR__ZTVN4Aska13TSmartPointerILb0EEE_02cc2320 + 0x10);
  return;
}

// ==== non-virtual thunk to Aska::AofHandler::~AofHandler()
// vaddr 0x20c18c0 | ghidra 0x21c18c0 | size 204 | symbol _ZThn160_N4Aska10AofHandlerD1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZThn160_N4Aska10AofHandlerD1Ev(long *param_1)

{
  undefined *puVar1;
  long lVar2;
  undefined *puVar3;
  long *plVar4;
  long *plVar5;
  long lVar6;
  
  puVar3 = PTR__ZTVN4Aska10AofHandlerE_02cc3728;
  puVar1 = PTR__ZTVN4Aska10AofHandlerE_02cc3728 + 0x90;
  plVar4 = param_1 + -1;
  *param_1 = (long)(PTR__ZTVN4Aska10AofHandlerE_02cc3728 + 0xb8);
  *plVar4 = (long)puVar1;
  plVar5 = param_1 + -0x14;
  *plVar5 = (long)(puVar3 + 0x10);
  Aska::AofHandler::Detach()(plVar5);
  Aska::MaterialList::DeleteBuffer()(param_1 + 9);
  Aska::RenderPassManagerList::~RenderPassManagerList()(param_1 + 0x10);
  *plVar4 = (long)(PTR__ZTVN4Aska15IMappingHandlerE_02cc1230 + 0x10);
  lVar6 = *(long *)PTR__ZN4Aska6Global22m_pMappedMemoryManagerE_02cc0368;
  lVar2 = lVar6 + 8;
  Aska::CriticalSection::Enter() const(lVar2);
  Aska::MappedMemoryManager::RemoveHandlerEx(Aska::IMappingHandler const*)(lVar6,plVar4);
  Aska::CriticalSection::Leave() const(lVar2);
  *plVar5 = (long)(PTR__ZTVN4Aska15ITextureHandlerE_02cc0f80 + 0x10);
  Aska::ITextureHandler::DetachTexture()(plVar5);
  Aska::TBarrierSlim<true>::~TBarrierSlim()(param_1 + -0x12);
  *plVar5 = (long)(PTR__ZTVN4Aska13TSmartPointerILb0EEE_02cc2320 + 0x10);
  return;
}

// ==== Aska::AofHandler::~AofHandler()
// vaddr 0x20c198c | ghidra 0x21c198c | size 196 | symbol _ZN4Aska10AofHandlerD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10AofHandlerD0Ev(long *param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  long lVar3;
  long lVar4;
  long *plVar5;
  
  puVar1 = PTR__ZTVN4Aska10AofHandlerE_02cc3728 + 0x90;
  puVar2 = PTR__ZTVN4Aska10AofHandlerE_02cc3728 + 0xb8;
  *param_1 = (long)(PTR__ZTVN4Aska10AofHandlerE_02cc3728 + 0x10);
  plVar5 = param_1 + 0x13;
  param_1[0x14] = (long)puVar2;
  *plVar5 = (long)puVar1;
  Aska::AofHandler::Detach()();
  Aska::MaterialList::DeleteBuffer()(param_1 + 0x1d);
  Aska::RenderPassManagerList::~RenderPassManagerList()(param_1 + 0x24);
  *plVar5 = (long)(PTR__ZTVN4Aska15IMappingHandlerE_02cc1230 + 0x10);
  lVar4 = *(long *)PTR__ZN4Aska6Global22m_pMappedMemoryManagerE_02cc0368;
  lVar3 = lVar4 + 8;
  Aska::CriticalSection::Enter() const(lVar3);
  Aska::MappedMemoryManager::RemoveHandlerEx(Aska::IMappingHandler const*)(lVar4,plVar5);
  Aska::CriticalSection::Leave() const(lVar3);
  *param_1 = (long)(PTR__ZTVN4Aska15ITextureHandlerE_02cc0f80 + 0x10);
  Aska::ITextureHandler::DetachTexture()(param_1);
  Aska::TBarrierSlim<true>::~TBarrierSlim()(param_1 + 2);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== non-virtual thunk to Aska::AofHandler::~AofHandler()
// vaddr 0x20c1a50 | ghidra 0x21c1a50 | size 196 | symbol _ZThn152_N4Aska10AofHandlerD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZThn152_N4Aska10AofHandlerD0Ev(long *param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  long lVar3;
  long *plVar4;
  long lVar5;
  
  puVar1 = PTR__ZTVN4Aska10AofHandlerE_02cc3728 + 0x90;
  puVar2 = PTR__ZTVN4Aska10AofHandlerE_02cc3728 + 0x10;
  plVar4 = param_1 + -0x13;
  param_1[1] = (long)(PTR__ZTVN4Aska10AofHandlerE_02cc3728 + 0xb8);
  *param_1 = (long)puVar1;
  *plVar4 = (long)puVar2;
  Aska::AofHandler::Detach()(plVar4);
  Aska::MaterialList::DeleteBuffer()(param_1 + 10);
  Aska::RenderPassManagerList::~RenderPassManagerList()(param_1 + 0x11);
  *param_1 = (long)(PTR__ZTVN4Aska15IMappingHandlerE_02cc1230 + 0x10);
  lVar5 = *(long *)PTR__ZN4Aska6Global22m_pMappedMemoryManagerE_02cc0368;
  lVar3 = lVar5 + 8;
  Aska::CriticalSection::Enter() const(lVar3);
  Aska::MappedMemoryManager::RemoveHandlerEx(Aska::IMappingHandler const*)(lVar5,param_1);
  Aska::CriticalSection::Leave() const(lVar3);
  *plVar4 = (long)(PTR__ZTVN4Aska15ITextureHandlerE_02cc0f80 + 0x10);
  Aska::ITextureHandler::DetachTexture()(plVar4);
  Aska::TBarrierSlim<true>::~TBarrierSlim()(param_1 + -0x11);
  (*(code *)PTR__ZdlPv_02ca4758)(plVar4);
  return;
}

// ==== non-virtual thunk to Aska::AofHandler::~AofHandler()
// vaddr 0x20c1b14 | ghidra 0x21c1b14 | size 192 | symbol _ZThn160_N4Aska10AofHandlerD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZThn160_N4Aska10AofHandlerD0Ev(long *param_1)

{
  undefined *puVar1;
  long lVar2;
  undefined *puVar3;
  long *plVar4;
  long *plVar5;
  long lVar6;
  
  puVar3 = PTR__ZTVN4Aska10AofHandlerE_02cc3728;
  puVar1 = PTR__ZTVN4Aska10AofHandlerE_02cc3728 + 0x90;
  plVar4 = param_1 + -1;
  *param_1 = (long)(PTR__ZTVN4Aska10AofHandlerE_02cc3728 + 0xb8);
  *plVar4 = (long)puVar1;
  plVar5 = param_1 + -0x14;
  *plVar5 = (long)(puVar3 + 0x10);
  Aska::AofHandler::Detach()(plVar5);
  Aska::MaterialList::DeleteBuffer()(param_1 + 9);
  Aska::RenderPassManagerList::~RenderPassManagerList()(param_1 + 0x10);
  *plVar4 = (long)(PTR__ZTVN4Aska15IMappingHandlerE_02cc1230 + 0x10);
  lVar6 = *(long *)PTR__ZN4Aska6Global22m_pMappedMemoryManagerE_02cc0368;
  lVar2 = lVar6 + 8;
  Aska::CriticalSection::Enter() const(lVar2);
  Aska::MappedMemoryManager::RemoveHandlerEx(Aska::IMappingHandler const*)(lVar6,plVar4);
  Aska::CriticalSection::Leave() const(lVar2);
  *plVar5 = (long)(PTR__ZTVN4Aska15ITextureHandlerE_02cc0f80 + 0x10);
  Aska::ITextureHandler::DetachTexture()(plVar5);
  Aska::TBarrierSlim<true>::~TBarrierSlim()(param_1 + -0x12);
  (*(code *)PTR__ZdlPv_02ca4758)(plVar5);
  return;
}

// ==== Aska::AofHandler::NotifyTexture()
// vaddr 0x20c1bd4 | ghidra 0x21c1bd4 | size 224 | symbol _ZN4Aska10AofHandler13NotifyTextureEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10AofHandler13NotifyTextureEv(long param_1)

{
  long *plVar1;
  undefined *puVar2;
  undefined4 uVar3;
  ulong uVar4;
  long lVar5;
  uint uVar6;
  int iVar7;
  long *plVar8;
  long lVar9;
  long *plVar10;
  code *pcVar11;
  ulong uStack_58;
  
  puVar2 = PTR__ZN4Aska6Global17m_pTextureManagerE_02cc19f0;
  lVar5 = *(long *)(param_1 + 0x100);
  if (((lVar5 != 0) && (*(long *)(param_1 + 0xd0) != 0)) &&
     (uVar6 = (uint)*(ushort *)(*(long *)(param_1 + 0xb0) + 0x70), uVar6 != 0)) {
    iVar7 = 0;
    plVar8 = (long *)(lVar5 + 0x40);
    do {
      lVar9 = (ulong)*(byte *)(lVar5 + 0x2b) + (ulong)*(byte *)(lVar5 + 599);
      if ((int)lVar9 != 0) {
        plVar1 = (long *)(*(long *)puVar2 + 0x2a8);
        plVar10 = plVar8;
        do {
          if (*plVar10 != 0) {
            uStack_58 = plVar10[-2] & 0xffffffffffffff80;
            pcVar11 = *(code **)(*plVar1 + 0x78);
            uVar3 = (**(code **)(*plVar1 + 0x60))(plVar1,&uStack_58);
            uVar4 = (*pcVar11)(plVar1,&uStack_58,uVar3);
            if ((uVar4 & 1) != 0) {
              *plVar10 = 0;
            }
          }
          lVar9 = lVar9 + -1;
          plVar10 = plVar10 + 4;
        } while (lVar9 != 0);
      }
      iVar7 = iVar7 + 1;
      lVar5 = lVar5 + 0x2a0;
      plVar8 = plVar8 + 0x54;
    } while (iVar7 < (int)uVar6);
  }
  return;
}

// ==== Aska::AofHandler::UpdateForProceduralTexture()
// vaddr 0x20c1cb4 | ghidra 0x21c1cb4 | size 24 | symbol _ZN4Aska10AofHandler26UpdateForProceduralTextureEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10AofHandler26UpdateForProceduralTextureEv(long param_1)

{
  if (*(long *)(param_1 + 0x328) != 0) {
    (*(code *)PTR__ZN4Aska17CDRFShaderHandler6UpdateEPNS_10AofHandlerE_02c99310)
              (*(long *)(param_1 + 0x328),param_1);
    return;
  }
  return;
}

// ==== Aska::AofHandler::UsesTexturePaletteBySkinning() const
// vaddr 0x20c1ccc | ghidra 0x21c1ccc | size 8 | symbol _ZNK4Aska10AofHandler28UsesTexturePaletteBySkinningEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska10AofHandler28UsesTexturePaletteBySkinningEv(void)

{
  return 0;
}

// ==== Aska::AofHandler::InitializeSkinPaletteConstant(Aska::SkinMatricesBase*)
// vaddr 0x20c1cd4 | ghidra 0x21c1cd4 | size 204 | symbol _ZN4Aska10AofHandler29InitializeSkinPaletteConstantEPNS_16SkinMatricesBaseE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10AofHandler29InitializeSkinPaletteConstantEPNS_16SkinMatricesBaseE
               (long param_1,long param_2)

{
  byte bVar1;
  ulong uVar2;
  long lVar3;
  long lVar4;
  ulong uVar5;
  float fStack_40;
  undefined4 uStack_3c;
  float fStack_38;
  
  if ((*(byte *)(param_1 + 0xa8) >> 4 & 1) == 0) {
    *(byte *)(param_1 + 0xa8) = *(byte *)(param_1 + 0xa8) | 0x10;
    bVar1 = *(byte *)(param_1 + 0x16e);
    fStack_40 = (float)NEON_ucvtf(*(undefined4 *)(param_2 + 0x68));
    fStack_40 = 1.0 / fStack_40;
    fStack_38 = (float)NEON_ucvtf(*(undefined4 *)(param_2 + 0x6c));
    fStack_38 = 1.0 / fStack_38;
    if ((ulong)bVar1 != 0) {
      lVar4 = 0;
      uVar5 = 0;
      do {
        lVar3 = **(long **)(*(long *)(param_1 + 0xd0) + uVar5 * 8);
        uVar2 = uVar5;
        if (*(short *)(lVar3 + 0x1c) != 0) {
          uVar2 = (ulong)*(char *)(lVar3 + 0x19);
        }
        uStack_3c = NEON_ucvtf((uint)*(ushort *)
                                      (*(long *)(param_2 + 0x40) +
                                      (-(uVar2 >> 0x1f & 1) & 0xfffffffe00000000 |
                                      (uVar2 & 0xffffffff) << 1)));
        Aska::ShaderConstantManager::SetShaderConstantFUC(int, int, Aska::Vector const*, int)(*(long *)(param_1 + 0x150) + lVar4,0x5c,0,&fStack_40,1);
        uVar5 = uVar5 + 1;
        lVar4 = lVar4 + 0x1b8;
      } while (bVar1 != uVar5);
    }
  }
  return;
}

// ==== Aska::AofHandler::GetShaderContextFlag() const
// vaddr 0x20c1da0 | ghidra 0x21c1da0 | size 8 | symbol _ZNK4Aska10AofHandler20GetShaderContextFlagEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska10AofHandler20GetShaderContextFlagEv(void)

{
  return 0;
}

// ==== Aska::AofHandler::SetShaderContextFlag()
// vaddr 0x20c1da8 | ghidra 0x21c1da8 | size 420 | symbol _ZN4Aska10AofHandler20SetShaderContextFlagEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10AofHandler20SetShaderContextFlagEv(long *param_1)

{
  long lVar1;
  uint uVar2;
  ulong uVar3;
  long lVar4;
  
  uVar2 = (**(code **)(*param_1 + 0x50))();
  if (((uVar2 & 1) != 0) && (uVar3 = (ulong)*(byte *)((long)param_1 + 0x10a), uVar3 != 0)) {
    lVar4 = 0x10;
    do {
      uVar3 = uVar3 - 1;
      lVar1 = 0;
      if (param_1[0x20] != 0) {
        lVar1 = param_1[0x20] + lVar4;
      }
      lVar4 = lVar4 + 0x2a0;
      *(byte *)(lVar1 + 0x1e) = *(byte *)(lVar1 + 0x1e) | 1;
    } while (uVar3 != 0);
  }
  if (((uVar2 >> 1 & 1) != 0) && (uVar3 = (ulong)*(byte *)((long)param_1 + 0x10a), uVar3 != 0)) {
    lVar4 = 0x10;
    do {
      uVar3 = uVar3 - 1;
      lVar1 = 0;
      if (param_1[0x20] != 0) {
        lVar1 = param_1[0x20] + lVar4;
      }
      lVar4 = lVar4 + 0x2a0;
      *(byte *)(lVar1 + 0x1e) = *(byte *)(lVar1 + 0x1e) | 2;
    } while (uVar3 != 0);
  }
  if (((uVar2 >> 2 & 1) != 0) && (uVar3 = (ulong)*(byte *)((long)param_1 + 0x10a), uVar3 != 0)) {
    lVar4 = 0x10;
    do {
      uVar3 = uVar3 - 1;
      lVar1 = 0;
      if (param_1[0x20] != 0) {
        lVar1 = param_1[0x20] + lVar4;
      }
      lVar4 = lVar4 + 0x2a0;
      *(byte *)(lVar1 + 0x1e) = *(byte *)(lVar1 + 0x1e) | 4;
    } while (uVar3 != 0);
  }
  if (((uVar2 >> 3 & 1) != 0) && (uVar3 = (ulong)*(byte *)((long)param_1 + 0x10a), uVar3 != 0)) {
    lVar4 = 0x10;
    do {
      uVar3 = uVar3 - 1;
      lVar1 = 0;
      if (param_1[0x20] != 0) {
        lVar1 = param_1[0x20] + lVar4;
      }
      lVar4 = lVar4 + 0x2a0;
      *(byte *)(lVar1 + 0x1e) = *(byte *)(lVar1 + 0x1e) | 8;
    } while (uVar3 != 0);
  }
  if (((uVar2 >> 4 & 1) != 0) && (uVar3 = (ulong)*(byte *)((long)param_1 + 0x10a), uVar3 != 0)) {
    lVar4 = 0x10;
    do {
      uVar3 = uVar3 - 1;
      lVar1 = 0;
      if (param_1[0x20] != 0) {
        lVar1 = param_1[0x20] + lVar4;
      }
      lVar4 = lVar4 + 0x2a0;
      *(byte *)(lVar1 + 0x1e) = *(byte *)(lVar1 + 0x1e) | 0x10;
    } while (uVar3 != 0);
  }
  if (((uVar2 >> 5 & 1) != 0) && (uVar3 = (ulong)*(byte *)((long)param_1 + 0x10a), uVar3 != 0)) {
    lVar4 = 0x10;
    do {
      uVar3 = uVar3 - 1;
      lVar1 = 0;
      if (param_1[0x20] != 0) {
        lVar1 = param_1[0x20] + lVar4;
      }
      lVar4 = lVar4 + 0x2a0;
      *(byte *)(lVar1 + 0x1e) = *(byte *)(lVar1 + 0x1e) | 0x20;
    } while (uVar3 != 0);
  }
  if (((uVar2 >> 6 & 1) != 0) && (uVar3 = (ulong)*(byte *)((long)param_1 + 0x10a), uVar3 != 0)) {
    lVar4 = 0x10;
    do {
      uVar3 = uVar3 - 1;
      lVar1 = 0;
      if (param_1[0x20] != 0) {
        lVar1 = param_1[0x20] + lVar4;
      }
      lVar4 = lVar4 + 0x2a0;
      *(byte *)(lVar1 + 0x1e) = *(byte *)(lVar1 + 0x1e) | 0x40;
    } while (uVar3 != 0);
  }
  return;
}

// ==== Aska::AofHandler::DeleteCallback(int, void*)
// vaddr 0x20c1f4c | ghidra 0x21c1f4c | size 60 | symbol _ZN4Aska10AofHandler14DeleteCallbackEiPv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10AofHandler14DeleteCallbackEiPv(long param_1,undefined8 param_2,long *param_3)

{
  if (param_3 != (long *)0x0) {
    (**(code **)(*(long *)(param_1 + 0x120) + 0x28))(param_1 + 0x120,param_3);
                    /* WARNING: Could not recover jumptable at 0x021c1f7c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*param_3 + 8))(param_3);
    return;
  }
  return;
}

// ==== non-virtual thunk to Aska::AofHandler::DeleteCallback(int, void*)
// vaddr 0x20c1f88 | ghidra 0x21c1f88 | size 56 | symbol _ZThn160_N4Aska10AofHandler14DeleteCallbackEiPv | lib libSOA-3.7.0.so | 2026-10-04
void _ZThn160_N4Aska10AofHandler14DeleteCallbackEiPv(long param_1,undefined8 param_2,long *param_3)

{
  if (param_3 != (long *)0x0) {
    (**(code **)(*(long *)(param_1 + 0x80) + 0x28))((long *)(param_1 + 0x80),param_3);
                    /* WARNING: Could not recover jumptable at 0x021c1fb4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*param_3 + 8))(param_3);
    return;
  }
  return;
}

// ==== Aska::AofHandler::CancelCallback(int, void*)
// vaddr 0x20c1fc0 | ghidra 0x21c1fc0 | size 4 | symbol _ZN4Aska10AofHandler14CancelCallbackEiPv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10AofHandler14CancelCallbackEiPv(void)

{
  return;
}

// ==== non-virtual thunk to Aska::AofHandler::CancelCallback(int, void*)
// vaddr 0x20c1fc4 | ghidra 0x21c1fc4 | size 4 | symbol _ZThn160_N4Aska10AofHandler14CancelCallbackEiPv | lib libSOA-3.7.0.so | 2026-10-04
void _ZThn160_N4Aska10AofHandler14CancelCallbackEiPv(void)

{
  return;
}

// ==== Aska::AofHandler::CreateSkinMatrices() const
// vaddr 0x20c1fc8 | ghidra 0x21c1fc8 | size 32 | symbol _ZNK4Aska10AofHandler18CreateSkinMatricesEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska10AofHandler18CreateSkinMatricesEv(void)

{
  undefined8 uVar1;
  
  uVar1 = operator new(unsigned long)(0x98);
  Aska::SkinMatrices::SkinMatrices()();
  return uVar1;
}

// ==== Aska::AofHandler::IsDirectAof() const
// vaddr 0x20c2038 | ghidra 0x21c2038 | size 8 | symbol _ZNK4Aska10AofHandler11IsDirectAofEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska10AofHandler11IsDirectAofEv(void)

{
  return 0;
}

// ==== Aska::AofHandler::OnSkinMatricesCreated(Aska::AofObject&)
// vaddr 0x20c2040 | ghidra 0x21c2040 | size 4 | symbol _ZN4Aska10AofHandler21OnSkinMatricesCreatedERNS_9AofObjectE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10AofHandler21OnSkinMatricesCreatedERNS_9AofObjectE(void)

{
  return;
}


// FAILED to create function at 02c48830 Aska::AofHandler::vtable
// FAILED to create function at 02c48930 Aska::AofHandler::typeinfo
