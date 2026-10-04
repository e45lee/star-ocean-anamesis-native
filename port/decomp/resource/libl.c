// port/decomp/resource/libl.c: Ghidra decompiles for the resource subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-04 06:14 UTC: tools/decomp.sh '--into' 'resource/libl' 'Aska::LIBLManager::'

// ==== Aska::LIBLManager::Initialize(int)
// vaddr 0x2136840 | ghidra 0x2236840 | size 20 | symbol _ZN4Aska11LIBLManager10InitializeEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11LIBLManager10InitializeEi(long param_1,undefined8 param_2)

{
  (*(code *)
    PTR__ZN4Aska11TPoolLegacyINS_11LIBLManager14_AarLoaderElemELb0EE10SecurePoolEjbPKvPKj_02c8eab0)
            (param_1 + 0x620,param_2,0,0,0);
  return;
}

// ==== Aska::TPoolLegacy<Aska::LIBLManager::_AarLoaderElem, false>::SecurePool(unsigned int, bool, void const*, unsigned int const*)
// vaddr 0x2136880 | ghidra 0x2236880 | size 328 | symbol _ZN4Aska11TPoolLegacyINS_11LIBLManager14_AarLoaderElemELb0EE10SecurePoolEjbPKvPKj | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska11TPoolLegacyINS_11LIBLManager14_AarLoaderElemELb0EE10SecurePoolEjbPKvPKj
          (long param_1,uint param_2,ulong param_3,long param_4,undefined8 param_5)

{
  long lVar1;
  ulong uVar2;
  undefined8 uVar3;
  long lVar4;
  long *plVar5;
  
  plVar5 = (long *)(param_1 + 0x20);
  if ((*plVar5 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 0x30) = 0;
  }
  *plVar5 = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  *(undefined8 *)(param_1 + 0x38) = 0;
  if (*(long *)(param_1 + 0x40) != 0) {
    if (*(char *)(param_1 + 0x48) != '\0') {
      operator delete[](void*)();
    }
    *(undefined8 *)(param_1 + 0x40) = 0;
  }
  if (param_2 == 0) {
code_r0x0223696c:
    uVar3 = 1;
  }
  else {
    if (param_4 == 0) {
      lVar1 = operator new[](unsigned long, unsigned long, bool)(param_2 * 0x268,8,1);
      *(undefined1 *)(param_1 + 0x48) = 1;
      *(long *)(param_1 + 0x40) = lVar1;
      lVar4 = 0;
      if (lVar1 != 0) goto code_r0x02236924;
    }
    else {
      *(undefined1 *)(param_1 + 0x48) = 0;
      *(long *)(param_1 + 0x40) = param_4;
code_r0x02236924:
      uVar2 = Aska::TBitArray<unsigned int, false>::Alloc(unsigned int, unsigned int const*)(param_1 + 0x10,param_2,param_5);
      if ((uVar2 & 1) != 0) {
        if ((param_3 & 1) != 0) {
          memset(*(undefined8 *)(param_1 + 0x40),0,(ulong)param_2 * 0x268);
        }
        *(undefined8 *)(param_1 + 0x38) = 0;
        if (*(int *)(param_1 + 0x28) != 0) {
          memset(*plVar5,0,*(int *)(param_1 + 0x28) << 2);
        }
        goto code_r0x0223696c;
      }
      lVar4 = *(long *)(param_1 + 0x40);
    }
    if (lVar4 != 0) {
      if (*(char *)(param_1 + 0x48) != '\0') {
        operator delete[](void*)();
      }
      *(undefined8 *)(param_1 + 0x40) = 0;
    }
    *(char *)(param_1 + 0x48) = '\0';
    if ((*plVar5 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
      operator delete[](void*)();
      *(undefined1 *)(param_1 + 0x30) = 0;
    }
    uVar3 = 0;
    *plVar5 = 0;
    *(undefined8 *)(param_1 + 0x28) = 0;
  }
  return uVar3;
}

// ==== Aska::LIBLManager::Delete()
// vaddr 0x21369c8 | ghidra 0x22369c8 | size 492 | symbol _ZN4Aska11LIBLManager6DeleteEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11LIBLManager6DeleteEv(long param_1)

{
  int *piVar1;
  int *piVar2;
  char cVar3;
  bool bVar4;
  ulong uVar5;
  int iVar6;
  long lVar7;
  long lVar8;
  long lVar9;
  
  piVar1 = (int *)(param_1 + 0x5c8);
  iVar6 = 0;
code_r0x022369e0:
  do {
    if (*piVar1 != -1) {
      ClearExclusiveLocal();
      bVar4 = iVar6 < 0x1ff;
      iVar6 = iVar6 + 1;
      if (bVar4) goto code_r0x022369e0;
      piVar2 = (int *)(param_1 + 0x5cc);
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
            uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0x608);
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
              Aska::Semaphore::Wait() const(param_1 + 0x608);
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
              if (cVar3 == '\0') goto code_r0x02236a98;
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
code_r0x02236a98:
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
        if (bVar4) {
          *piVar2 = *piVar2 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
code_r0x02236aa8:
      DataMemoryBarrier(2,3);
      for (lVar9 = *(long *)(param_1 + 0x688); param_1 + 0x678 != lVar9;
          lVar9 = *(long *)(lVar9 + 0x10)) {
        if (lVar9 != 0) {
          lVar7 = *(long *)(lVar9 + 8);
          lVar8 = *(long *)(lVar9 + 0x10);
          if (lVar7 != 0) {
            *(long *)(lVar7 + 0x10) = lVar8;
          }
          if (lVar8 != 0) {
            *(long *)(lVar8 + 8) = lVar7;
          }
          if (0 < *(int *)(param_1 + 0x8e0)) {
            *(int *)(param_1 + 0x8e0) = *(int *)(param_1 + 0x8e0) + -1;
          }
          *(long *)(lVar9 + 8) = 0;
          *(undefined8 *)(lVar9 + 0x10) = 0;
        }
        Aska::LIBLManager::_AarLoaderElem::Detach()(lVar9);
      }
      DataMemoryBarrier(2,3);
      *(undefined4 *)(param_1 + 0x5c8) = 0xffffffff;
      DataMemoryBarrier(2,3);
      if (0x14 < *(int *)(param_1 + 0x5cc)) {
        piVar1 = (int *)(param_1 + 0x5cc);
        do {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar4) {
            *piVar1 = *piVar1 + -1;
            cVar3 = ExclusiveMonitorsStatus();
          }
        } while (cVar3 != '\0');
        uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0x608);
        if ((uVar5 & 1) != 0) {
          Aska::Semaphore::Signal() const(param_1 + 0x608);
        }
      }
      if ((*(long *)(param_1 + 0x640) != 0) && (*(char *)(param_1 + 0x650) != '\0')) {
        operator delete[](void*)();
        *(undefined1 *)(param_1 + 0x650) = 0;
      }
      *(undefined8 *)(param_1 + 0x640) = 0;
      *(undefined8 *)(param_1 + 0x648) = 0;
      *(undefined8 *)(param_1 + 0x658) = 0;
      if (*(long *)(param_1 + 0x660) != 0) {
        if (*(char *)(param_1 + 0x668) != '\0') {
          operator delete[](void*)();
        }
        *(undefined8 *)(param_1 + 0x660) = 0;
      }
      if (*(long *)(param_1 + 0x9b0) != 0) {
        operator delete[](void*)(*(long *)(param_1 + 0x9b0) + -0x10);
        *(undefined8 *)(param_1 + 0x9b0) = 0;
      }
      return;
    }
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar4) {
      *piVar1 = 0;
      cVar3 = ExclusiveMonitorsStatus();
    }
    if (cVar3 == '\0') goto code_r0x02236aa8;
  } while( true );
}

// ==== Aska::TList<Aska::LIBLManager::_AarLoaderElem>::Delete(Aska::LIBLManager::_AarLoaderElem*)
// vaddr 0x2136bb4 | ghidra 0x2236bb4 | size 64 | symbol _ZN4Aska5TListINS_11LIBLManager14_AarLoaderElemEE6DeleteEPS2_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5TListINS_11LIBLManager14_AarLoaderElemEE6DeleteEPS2_(long param_1,long param_2)

{
  long lVar1;
  long lVar2;
  
  if ((param_1 + 8 != param_2) && (param_2 != 0)) {
    lVar1 = *(long *)(param_2 + 8);
    lVar2 = *(long *)(param_2 + 0x10);
    if (lVar1 != 0) {
      *(long *)(lVar1 + 0x10) = lVar2;
    }
    if (lVar2 != 0) {
      *(long *)(lVar2 + 8) = lVar1;
    }
    if (0 < *(int *)(param_1 + 0x270)) {
      *(int *)(param_1 + 0x270) = *(int *)(param_1 + 0x270) + -1;
    }
    *(long *)(param_2 + 8) = 0;
    *(undefined8 *)(param_2 + 0x10) = 0;
  }
  return;
}

// ==== Aska::LIBLManager::_AarLoaderElem::Detach()
// vaddr 0x2136bf4 | ghidra 0x2236bf4 | size 540 | symbol _ZN4Aska11LIBLManager14_AarLoaderElem6DetachEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11LIBLManager14_AarLoaderElem6DetachEv(long param_1)

{
  long lVar1;
  ulong uVar2;
  uint uVar3;
  undefined *puVar4;
  undefined8 *puVar5;
  long *plVar6;
  ulong uVar7;
  long lVar8;
  ulong uVar9;
  int *piVar10;
  long lVar11;
  uint uVar12;
  
  if (*(long *)(*(long *)(param_1 + 0xb8) + 8) == 0) goto code_r0x011c03c0;
  piVar10 = *(int **)(*(long *)(param_1 + 0xb8) + 0x18);
  if (((piVar10 == (int *)0x0) || (*piVar10 != 0x41727279)) ||
     ((*(ushort *)(piVar10 + 7) & 0xfff) != 2)) {
    return;
  }
  uVar3 = piVar10[4];
  lVar11 = *(long *)PTR__ZN4Aska6Global14m_pLIBLManagerE_02cc46a8;
  if (uVar3 != 0) {
    uVar12 = 0;
    lVar8 = *(long *)PTR__ZN4Aska6Global17m_pTextureManagerE_02cc19f0;
    lVar1 = lVar8 + 0xb0;
    do {
      uVar9 = *(ulong *)((long)piVar10 +
                        (long)(int)uVar12 * (ulong)*(ushort *)((long)piVar10 + 0x1e) +
                        (ulong)(uint)piVar10[5]);
      Aska::CriticalSection::Enter() const(lVar1);
      Aska::TextureAliases::GetOriginID(unsigned long)(lVar8 + 0x338,uVar9);
      Aska::CriticalSection::Leave() const(lVar1);
      Aska::CriticalSection::Enter() const(lVar1);
      if (uVar9 < 0x80) {
        while (*(int *)(lVar8 + 0x3c4) != 0) {
          plVar6 = *(long **)(lVar8 + 0x3a8);
          *(undefined1 *)(lVar8 + 0x3c0) = 0;
          *(long **)(lVar8 + 0x3b8) = plVar6;
          if (plVar6 == (long *)0x0) {
            *(undefined1 *)(lVar8 + 0x3c0) = 1;
            break;
          }
          puVar5 = (undefined8 *)(**(code **)(*plVar6 + 0x30))();
          Aska::TextureManager::AliasTextureEx(unsigned long, unsigned long)(lVar8,*puVar5,0);
        }
      }
      else {
        Aska::TextureManager::AliasTextureEx(unsigned long, unsigned long)(lVar8,uVar9,0);
      }
      Aska::CriticalSection::Leave() const(lVar1);
      uVar12 = uVar12 + 1;
    } while (uVar12 != uVar3);
  }
  puVar4 = PTR__ZN4Aska6Global21m_systemDeleteManagerE_02cb77c0;
  uVar9 = *(ulong *)(param_1 + 0x250);
  if (uVar9 == 0) goto code_r0x011c03c0;
  if (uVar3 == 0) {
code_r0x02236dc8:
    operator delete[](void*)(uVar9);
  }
  else {
    uVar2 = uVar9 + (ulong)uVar3 * 0x20;
    lVar1 = lVar11 + 0x910;
    lVar11 = lVar11 + 0x918;
    do {
      lVar8 = *(long *)(uVar9 + 8);
      if ((lVar8 != 0) && (uVar7 = Aska::DeleteManager::AddMain(void*, unsigned char, unsigned char, Aska::IDeleteHandler*)(puVar4,lVar8,0,0,lVar1), (uVar7 & 1) == 0)) {
        Aska::ITextureHandler::DetachTexture(Aska::AFF::AskaFile const*, bool)(lVar11,lVar8,0);
        operator delete[](void*)(lVar8);
      }
      lVar8 = *(long *)(uVar9 + 0x18);
      if ((lVar8 != 0) && (uVar7 = Aska::DeleteManager::AddMain(void*, unsigned char, unsigned char, Aska::IDeleteHandler*)(puVar4,lVar8,0,0,lVar1), (uVar7 & 1) == 0)) {
        Aska::ITextureHandler::DetachTexture(Aska::AFF::AskaFile const*, bool)(lVar11,lVar8,0);
        operator delete[](void*)(lVar8);
      }
      uVar9 = uVar9 + 0x20;
    } while (uVar9 < uVar2);
    uVar9 = *(ulong *)(param_1 + 0x250);
    if (uVar9 != 0) goto code_r0x02236dc8;
  }
  *(undefined8 *)(param_1 + 0x250) = 0;
code_r0x011c03c0:
  (*(code *)PTR__ZN4Aska24AarLoaderForBlendTexture6DetachEv_02c981d0)(param_1 + 0x18);
  return;
}

// ==== Aska::LIBLManager::CreateNotify(int)
// vaddr 0x2136e10 | ghidra 0x2236e10 | size 300 | symbol _ZN4Aska11LIBLManager12CreateNotifyEi | lib libSOA-3.7.0.so | 2026-10-04
bool _ZN4Aska11LIBLManager12CreateNotifyEi(long param_1,int param_2)

{
  undefined *puVar1;
  undefined1 auVar2 [16];
  long lVar3;
  ulong uVar4;
  long lVar5;
  long lVar6;
  ulong uVar7;
  long *plVar8;
  ulong uVar9;
  ulong uVar10;
  
  if (param_2 == 0) {
    return true;
  }
  uVar10 = (ulong)param_2;
  auVar2._8_8_ = 0;
  auVar2._0_8_ = uVar10;
  uVar4 = (uVar10 + (long)param_2 * 8) * 0x10;
  lVar3 = uVar4 + 0x10;
  if (SUB168(auVar2 * ZEXT816(0x90),8) != 0 || 0xffffffffffffffef < uVar4) {
    lVar3 = -1;
  }
  lVar3 = operator new[](unsigned long, std::nothrow_t const&)(lVar3,PTR__ZSt7nothrow_02cb9a80);
  if (lVar3 == 0) {
    lVar5 = 0;
  }
  else {
    lVar5 = lVar3 + 0x10;
    uVar4 = (uVar10 * 0x90 - 0x90) / 0x90 + 1;
    *(ulong *)(lVar3 + 8) = uVar10;
    lVar6 = lVar5;
    if ((1 < uVar4) && (uVar7 = uVar4 & 0x3fffffffffffffe, uVar7 != 0)) {
      plVar8 = (long *)(lVar3 + 0xa0);
      puVar1 = PTR__ZTVN4Aska11LIBLManager11_LIBLNotifyE_02cb7510 + 0x10;
      uVar9 = uVar7;
      do {
        plVar8[-0x12] = (long)puVar1;
        *plVar8 = (long)puVar1;
        uVar9 = uVar9 - 2;
        plVar8 = plVar8 + 0x24;
      } while (uVar9 != 0);
      lVar6 = lVar5 + uVar7 * 0x90;
      if (uVar4 == uVar7) goto code_r0x02236f20;
    }
    lVar6 = lVar6 + -0x10;
    puVar1 = PTR__ZTVN4Aska11LIBLManager11_LIBLNotifyE_02cb7510 + 0x10;
    do {
      *(undefined **)(lVar6 + 0x10) = puVar1;
      lVar6 = lVar6 + 0x90;
    } while (lVar3 + uVar10 * 0x90 != lVar6);
  }
code_r0x02236f20:
  *(long *)(param_1 + 0x9b0) = lVar5;
  *(int *)(param_1 + 0x9b8) = param_2;
  return lVar5 != 0;
}

// ==== Aska::LIBLManager::Update()
// vaddr 0x2136f3c | ghidra 0x2236f3c | size 856 | symbol _ZN4Aska11LIBLManager6UpdateEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11LIBLManager6UpdateEv(long param_1)

{
  bool bVar1;
  bool bVar2;
  ulong uVar3;
  long lVar4;
  long lVar5;
  long *plVar6;
  long *plVar7;
  int iVar8;
  long *plVar9;
  long lVar10;
  byte bVar11;
  long lVar12;
  
  iVar8 = *(int *)(param_1 + 0x88);
  plVar9 = (long *)(param_1 + 8U);
  do {
    if (*plVar9 != 0) {
      lVar10 = (long)plVar9 - (long)(param_1 + 8U) >> 3;
      lVar4 = *(long *)(param_1 + lVar10 * 0x50 + 0xd0);
      if (lVar4 == 0) {
code_r0x02237070:
        bVar1 = false;
      }
      else {
        lVar5 = param_1 + lVar10 * 0x50;
        plVar7 = (long *)(lVar5 + 0x90);
        plVar6 = *(long **)(**(long **)(lVar4 + 0xd8) + 0x38);
        if ((*(byte *)(plVar6 + 0x25) & 1) != 0) {
          (**(code **)(*plVar6 + 0xa8))(plVar6);
        }
        plVar6 = (long *)(**(code **)(*plVar6 + 0x98))(plVar6);
        if (((((*plVar7 == *plVar6) && (*(long *)(param_1 + lVar10 * 0x50 + 0x98) == plVar6[1])) &&
             (*(long *)(param_1 + lVar10 * 0x50 + 0xa0) == plVar6[2])) &&
            ((*(long *)(param_1 + lVar10 * 0x50 + 0xa8) == plVar6[3] &&
             (*(long *)(param_1 + lVar10 * 0x50 + 0xb0) == plVar6[4])))) &&
           ((*(long *)(param_1 + lVar10 * 0x50 + 0xb8) == plVar6[5] &&
            ((*(long *)(param_1 + lVar10 * 0x50 + 0xc0) == plVar6[6] &&
             (*(long *)(param_1 + lVar10 * 0x50 + 200) == plVar6[7])))))) goto code_r0x02237070;
        lVar12 = *plVar6;
        lVar4 = param_1 + lVar10 * 0x50;
        bVar1 = true;
        *(long *)(lVar5 + 0x98) = plVar6[1];
        *plVar7 = lVar12;
        lVar10 = plVar6[2];
        *(long *)(lVar4 + 0xa8) = plVar6[3];
        *(long *)(lVar4 + 0xa0) = lVar10;
        lVar10 = plVar6[4];
        *(long *)(lVar4 + 0xb8) = plVar6[5];
        *(long *)(lVar4 + 0xb0) = lVar10;
        lVar10 = plVar6[6];
        *(long *)(lVar4 + 200) = plVar6[7];
        *(long *)(lVar4 + 0xc0) = lVar10;
      }
      lVar4 = *(long *)(*plVar9 + 0x30);
      if (lVar4 == 0) {
        if (bVar1) goto code_r0x02237244;
      }
      else {
        if (bVar1) {
          bVar11 = 0;
          do {
            lVar10 = *(long *)(lVar4 + 0x120);
            lVar5 = *(long *)(lVar4 + 0x10);
            plVar7 = *(long **)(lVar10 + 0x408);
            if (plVar7 == (long *)0x0) {
code_r0x02237148:
              bVar2 = false;
              plVar7 = *(long **)(lVar10 + 0x410);
            }
            else {
              if ((*(byte *)(plVar7 + 0x25) & 1) != 0) {
                (**(code **)(*plVar7 + 0xa8))(plVar7);
              }
              uVar3 = Aska::IAnimatable::IsThisIt(unsigned short) const(plVar7,0xf1a3);
              if ((uVar3 & 1) == 0) goto code_r0x02237148;
              lVar12 = plVar7[0x33];
              *(undefined1 *)(plVar7 + 0x33) = 0;
              bVar2 = (char)lVar12 != '\0';
              plVar7 = *(long **)(lVar10 + 0x410);
            }
            if (plVar7 != (long *)0x0) {
              if ((*(byte *)(plVar7 + 0x25) & 1) != 0) {
                (**(code **)(*plVar7 + 0xa8))(plVar7);
              }
              uVar3 = Aska::IAnimatable::IsThisIt(unsigned short) const(plVar7,0xf1a3);
              if ((uVar3 & 1) != 0) {
                lVar10 = plVar7[0x33];
                *(undefined1 *)(plVar7 + 0x33) = 0;
                bVar2 = (char)lVar10 != '\0';
              }
            }
            bVar11 = bVar11 | bVar2;
            *(undefined1 *)(lVar4 + 0x128) = 0;
            *(undefined1 *)(lVar4 + 0x21) = 1;
            lVar4 = lVar5;
          } while (lVar5 != 0);
        }
        else {
          bVar11 = 0;
          do {
            while( true ) {
              lVar10 = *(long *)(lVar4 + 0x120);
              lVar5 = *(long *)(lVar4 + 0x10);
              plVar7 = *(long **)(lVar10 + 0x408);
              if (plVar7 != (long *)0x0) break;
code_r0x02237220:
              bVar2 = false;
              plVar7 = *(long **)(lVar10 + 0x410);
              if (plVar7 == (long *)0x0) goto code_r0x0223722c;
code_r0x022371d0:
              if ((*(byte *)(plVar7 + 0x25) & 1) != 0) {
                (**(code **)(*plVar7 + 0xa8))(plVar7);
              }
              uVar3 = Aska::IAnimatable::IsThisIt(unsigned short) const(plVar7,0xf1a3);
              if ((uVar3 & 1) == 0) goto code_r0x0223722c;
              lVar10 = plVar7[0x33];
              *(undefined1 *)(plVar7 + 0x33) = 0;
              *(undefined1 *)(lVar4 + 0x128) = 0;
              bVar11 = bVar11 | (char)lVar10 != '\0';
              if ((char)lVar10 == '\0') goto code_r0x02237238;
code_r0x02237214:
              *(undefined1 *)(lVar4 + 0x21) = 1;
              lVar4 = lVar5;
              if (lVar5 == 0) goto code_r0x0223723c;
            }
            if ((*(byte *)(plVar7 + 0x25) & 1) != 0) {
              (**(code **)(*plVar7 + 0xa8))(plVar7);
            }
            uVar3 = Aska::IAnimatable::IsThisIt(unsigned short) const(plVar7,0xf1a3);
            if ((uVar3 & 1) == 0) goto code_r0x02237220;
            lVar12 = plVar7[0x33];
            *(undefined1 *)(plVar7 + 0x33) = 0;
            bVar2 = (char)lVar12 != '\0';
            plVar7 = *(long **)(lVar10 + 0x410);
            if (plVar7 != (long *)0x0) goto code_r0x022371d0;
code_r0x0223722c:
            bVar11 = bVar11 | bVar2;
            *(undefined1 *)(lVar4 + 0x128) = 0;
            if (bVar2) goto code_r0x02237214;
code_r0x02237238:
            lVar4 = lVar5;
          } while (lVar5 != 0);
        }
code_r0x0223723c:
        if ((bool)(bVar1 | bVar11)) {
code_r0x02237244:
          *(undefined1 *)(*plVar9 + 0x94) = 1;
        }
      }
      Aska::IntegratedDynamicsEnvironment::FrameUpdate()(*plVar9);
      if (iVar8 < 2) {
        return;
      }
      iVar8 = iVar8 + -1;
    }
    plVar9 = plVar9 + 1;
    if ((long *)(param_1 + 0x88) <= plVar9) {
      return;
    }
  } while( true );
}

// ==== Aska::LIBLManager::Intersect(Aska::RenderableObject**, int, int)
// vaddr 0x2137294 | ghidra 0x2237294 | size 976 | symbol _ZN4Aska11LIBLManager9IntersectEPPNS_16RenderableObjectEii | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11LIBLManager9IntersectEPPNS_16RenderableObjectEii
               (long param_1,long param_2,int param_3,int param_4)

{
  undefined8 *puVar1;
  ulong uVar2;
  undefined8 uVar3;
  ulong uVar4;
  ulong uVar5;
  long *plVar6;
  undefined8 *puVar7;
  int iVar9;
  undefined8 *puVar10;
  float fVar11;
  float fVar12;
  long lStack_c0;
  undefined4 uStack_b8;
  undefined4 uStack_b4;
  float fStack_b0;
  float fStack_ac;
  float fStack_a8;
  undefined4 uStack_a4;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  undefined4 uStack_94;
  float fStack_90;
  float fStack_8c;
  ulong uStack_88;
  undefined8 uStack_80;
  float fStack_78;
  undefined4 uStack_74;
  undefined8 *puVar8;
  
  iVar9 = 0;
  plVar6 = (long *)(param_1 + 8);
  do {
    if (*plVar6 != 0) {
      *(long *)(param_1 + (long)iVar9 * 8 + 0x9c0) = *plVar6;
      iVar9 = iVar9 + 1;
      if (*(int *)(param_1 + 0x88) <= iVar9) break;
    }
    plVar6 = plVar6 + 1;
  } while (plVar6 < (long *)(param_1 + 0x88U));
  if (0 < param_4) {
    puVar10 = (undefined8 *)(param_2 + (long)param_3 * 8);
    uVar5 = *(long *)(param_1 + 0x9b0) + (long)param_3 * 0x90;
    puVar1 = puVar10 + param_4;
    uVar4 = uVar5 + (long)(*(int *)(param_1 + 0x9b8) - param_3) * 0x90;
    do {
      if (uVar5 < uVar4) {
        plVar6 = (long *)*puVar10;
        uVar2 = (**(code **)(*plVar6 + 0x268))(plVar6);
        if ((uVar2 & 1) == 0) {
          if ((*(byte *)(plVar6 + 0x25) >> 4 & 1) == 0) {
            (**(code **)(*plVar6 + 600))(plVar6,1);
          }
          lStack_c0 = plVar6[0x5a];
          uStack_b8 = (undefined4)plVar6[0x5b];
          fStack_b0 = *(float *)((long)plVar6 + 0x2dc);
          fStack_a0 = 1.0;
          uStack_b4 = 0x3f800000;
          fStack_98 = 0.0;
          fStack_9c = 0.0;
          fStack_90 = 0.0;
          fStack_8c = 1.0;
          uStack_88 = 0;
          uStack_80 = 0;
          fStack_78 = 1.0;
          fStack_ac = fStack_b0;
          fStack_a8 = fStack_b0;
        }
        else {
          uVar2 = (**(code **)(*plVar6 + 0x260))(plVar6,&lStack_c0);
          uVar3 = (**(code **)(*plVar6 + 0x98))(plVar6);
          Aska::Vector::ApplyMatrix(Aska::Matrix const*)(&lStack_c0,uVar3);
          Aska::Vector::ApplyMatrixNoTransport(Aska::Matrix const*)(&fStack_a0,uVar3);
          Aska::Vector::ApplyMatrixNoTransport(Aska::Matrix const*)(&fStack_90,uVar3);
          Aska::Vector::ApplyMatrixNoTransport(Aska::Matrix const*)(&uStack_80,uVar3);
          fVar12 = fStack_a0 * fStack_a0 + fStack_9c * fStack_9c + fStack_98 * fStack_98;
          fVar11 = SQRT(fVar12);
          if (NAN(fVar11)) {
            fVar11 = (float)sqrtf(fVar12);
          }
          fStack_b0 = fVar11 * fStack_b0;
          fVar11 = 1.0 / fVar11;
          fStack_a0 = fVar11 * fStack_a0;
          fStack_9c = fVar11 * fStack_9c;
          fStack_98 = fVar11 * fStack_98;
          fVar12 = fStack_90 * fStack_90 + fStack_8c * fStack_8c +
                   (float)uStack_88 * (float)uStack_88;
          fVar11 = SQRT(fVar12);
          if (NAN(fVar11)) {
            fVar11 = (float)sqrtf(fVar12);
          }
          fStack_ac = fVar11 * fStack_ac;
          fVar11 = 1.0 / fVar11;
          fStack_90 = fVar11 * fStack_90;
          fStack_8c = fVar11 * fStack_8c;
          uStack_88 = CONCAT44(uStack_88._4_4_,fVar11 * (float)uStack_88);
          fVar12 = (float)uStack_80 * (float)uStack_80 + uStack_80._4_4_ * uStack_80._4_4_ +
                   fStack_78 * fStack_78;
          fVar11 = SQRT(fVar12);
          if (NAN(fVar11)) {
            fVar11 = (float)sqrtf(fVar12);
          }
          uStack_94 = 0;
          uStack_88 = uStack_88 & 0xffffffff;
          fStack_a8 = fVar11 * fStack_a8;
          fVar11 = 1.0 / fVar11;
          uStack_80 = CONCAT44(fVar11 * uStack_80._4_4_,fVar11 * (float)uStack_80);
          fStack_78 = fVar11 * fStack_78;
          uStack_74 = 0;
          if ((uVar2 & 1) == 0) goto code_r0x02237630;
        }
        uStack_94 = 0;
        uStack_74 = 0;
        if ((char)plVar6[0x49] != '\0') {
          if ((long *)(uVar5 + 0x10) != &lStack_c0) {
            *(ulong *)(uVar5 + 0x18) = CONCAT44(uStack_b4,uStack_b8);
            *(long *)(uVar5 + 0x10) = lStack_c0;
            *(ulong *)(uVar5 + 0x28) = CONCAT44(uStack_a4,fStack_a8);
            *(ulong *)(uVar5 + 0x20) = CONCAT44(fStack_ac,fStack_b0);
            *(float *)(uVar5 + 0x30) = fStack_a0;
            *(float *)(uVar5 + 0x34) = fStack_9c;
            *(float *)(uVar5 + 0x38) = fStack_98;
            *(undefined4 *)(uVar5 + 0x3c) = 0;
            *(float *)(uVar5 + 0x40) = fStack_90;
            *(float *)(uVar5 + 0x44) = fStack_8c;
            *(float *)(uVar5 + 0x48) = (float)uStack_88;
            *(undefined4 *)(uVar5 + 0x4c) = 0;
            *(float *)(uVar5 + 0x50) = (float)uStack_80;
            *(float *)(uVar5 + 0x54) = uStack_80._4_4_;
            *(float *)(uVar5 + 0x58) = fStack_78;
            *(undefined4 *)(uVar5 + 0x5c) = 0;
          }
          *(long **)(uVar5 + 0x60) = plVar6;
          *(undefined8 *)(uVar5 + 0x68) = 0;
          *(undefined4 *)(uVar5 + 0x70) = 0;
          *(undefined8 *)(uVar5 + 0x78) = 0;
          *(undefined4 *)(uVar5 + 0x80) = 0;
          if (0 < iVar9) {
            puVar7 = (undefined8 *)(param_1 + 0x9c0);
            do {
              puVar8 = puVar7 + 1;
              Aska::IntegratedDynamicsEnvironment::PostFindIntersectObjects(Aska::IDE_ResultOfFindObjects*, int, unsigned int*, unsigned int*, Aska::INotify*, Aska::Box const*, unsigned int, unsigned short)(*puVar7,0,0,0,0,uVar5,uVar5 + 0x10,0,0xffff);
              puVar7 = puVar8;
            } while (puVar8 < (undefined8 *)(param_1 + (long)iVar9 * 8 + 0x9c0U));
          }
        }
      }
code_r0x02237630:
      puVar10 = puVar10 + 1;
      uVar5 = uVar5 + 0x90;
    } while (puVar10 < puVar1);
  }
  return;
}

// ==== Aska::LIBLManager::_LIBLNotify::Reset(Aska::RenderableObject*, Aska::OrientedBoundingBox*)
// vaddr 0x2137664 | ghidra 0x2237664 | size 168 | symbol _ZN4Aska11LIBLManager11_LIBLNotify5ResetEPNS_16RenderableObjectEPNS_19OrientedBoundingBoxE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11LIBLManager11_LIBLNotify5ResetEPNS_16RenderableObjectEPNS_19OrientedBoundingBoxE
               (long param_1,undefined8 param_2,undefined4 *param_3)

{
  if ((undefined4 *)(param_1 + 0x10) != param_3) {
    *(undefined4 *)(param_1 + 0x10) = *param_3;
    *(undefined4 *)(param_1 + 0x14) = param_3[1];
    *(undefined4 *)(param_1 + 0x18) = param_3[2];
    *(undefined4 *)(param_1 + 0x1c) = param_3[3];
    *(undefined4 *)(param_1 + 0x20) = param_3[4];
    *(undefined4 *)(param_1 + 0x24) = param_3[5];
    *(undefined4 *)(param_1 + 0x28) = param_3[6];
    *(undefined4 *)(param_1 + 0x2c) = param_3[7];
    *(undefined4 *)(param_1 + 0x30) = param_3[8];
    *(undefined4 *)(param_1 + 0x34) = param_3[9];
    *(undefined4 *)(param_1 + 0x38) = param_3[10];
    *(undefined4 *)(param_1 + 0x3c) = 0;
    *(undefined4 *)(param_1 + 0x40) = param_3[0xc];
    *(undefined4 *)(param_1 + 0x44) = param_3[0xd];
    *(undefined4 *)(param_1 + 0x48) = param_3[0xe];
    *(undefined4 *)(param_1 + 0x4c) = 0;
    *(undefined4 *)(param_1 + 0x50) = param_3[0x10];
    *(undefined4 *)(param_1 + 0x54) = param_3[0x11];
    *(undefined4 *)(param_1 + 0x58) = param_3[0x12];
    *(undefined4 *)(param_1 + 0x5c) = 0;
  }
  *(undefined8 *)(param_1 + 0x60) = param_2;
  *(undefined8 *)(param_1 + 0x68) = 0;
  *(undefined4 *)(param_1 + 0x70) = 0;
  *(undefined8 *)(param_1 + 0x78) = 0;
  *(undefined4 *)(param_1 + 0x80) = 0;
  return;
}

// ==== Aska::LIBLManager::SetResult(Aska::RenderableObject**, int)
// vaddr 0x213770c | ghidra 0x223770c | size 136 | symbol _ZN4Aska11LIBLManager9SetResultEPPNS_16RenderableObjectEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11LIBLManager9SetResultEPPNS_16RenderableObjectEi
               (long param_1,long *param_2,int param_3)

{
  long *plVar1;
  float *pfVar2;
  long lVar3;
  undefined8 uVar4;
  float fVar5;
  
  if (0 < param_3) {
    plVar1 = param_2 + param_3;
    pfVar2 = (float *)(*(long *)(param_1 + 0x9b0) + 0x80);
    do {
      lVar3 = *param_2;
      *(undefined8 *)(lVar3 + 0x230) = *(undefined8 *)(pfVar2 + -6);
      if (*(byte *)(lVar3 + 0x248) < 2) {
code_r0x02237758:
        fVar5 = 0.0;
        *(undefined4 *)(lVar3 + 0x240) = 0x3f800000;
      }
      else {
        fVar5 = pfVar2[-4];
        if ((fVar5 == 0.0) && (*pfVar2 == 0.0)) goto code_r0x02237758;
        uVar4 = *(undefined8 *)(pfVar2 + -2);
        fVar5 = fVar5 / (fVar5 + *pfVar2);
        *(float *)(lVar3 + 0x240) = fVar5;
        *(undefined8 *)(lVar3 + 0x238) = uVar4;
        fVar5 = 1.0 - fVar5;
      }
      param_2 = param_2 + 1;
      pfVar2 = pfVar2 + 0x24;
      *(float *)(lVar3 + 0x244) = fVar5;
    } while (param_2 < plVar1);
  }
  return;
}

// ==== Aska::LIBLManager::MakeEffectiveLIBLList()
// vaddr 0x2137794 | ghidra 0x2237794 | size 116 | symbol _ZN4Aska11LIBLManager21MakeEffectiveLIBLListEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11LIBLManager21MakeEffectiveLIBLListEv(long param_1)

{
  bool bVar1;
  ulong uVar2;
  int iVar3;
  long lVar4;
  ushort uVar5;
  int iVar6;
  long *plVar7;
  long lVar8;
  long lVar9;
  
  uVar5 = 0;
  lVar4 = *(long *)PTR__ZN4Aska6Global15m_pLightManagerE_02cc1770;
  iVar6 = *(int *)(param_1 + 0x88);
  plVar7 = (long *)(param_1 + 8);
  do {
    if (*plVar7 != 0) {
      lVar9 = *(long *)(*plVar7 + 0x30);
      while (lVar8 = lVar9, lVar8 != 0) {
        lVar9 = *(long *)(lVar8 + 0x10);
        if (*(char *)(lVar8 + 0x128) != '\0') {
          uVar2 = (ulong)uVar5;
          uVar5 = uVar5 + 1;
          *(undefined8 *)(lVar4 + uVar2 * 8 + 0x1ff0) = *(undefined8 *)(lVar8 + 0x120);
        }
      }
      iVar3 = iVar6 + -1;
      bVar1 = iVar6 < 1;
      iVar6 = iVar3;
      if (iVar3 == 0 || bVar1) break;
    }
    plVar7 = plVar7 + 1;
  } while (plVar7 < (long *)(param_1 + 0x88));
  *(ushort *)(lVar4 + 0x2ffa) = uVar5;
  return;
}

// ==== Aska::LIBLManager::Add(Aska::IntegratedDynamicsEnvironment*, Aska::AsfHandler const*)
// vaddr 0x2137808 | ghidra 0x2237808 | size 100 | symbol _ZN4Aska11LIBLManager3AddEPNS_29IntegratedDynamicsEnvironmentEPKNS_10AsfHandlerE | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

bool _ZN4Aska11LIBLManager3AddEPNS_29IntegratedDynamicsEnvironmentEPKNS_10AsfHandlerE
               (long param_1,undefined8 param_2,undefined8 param_3)

{
  undefined8 uVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  int iVar8;
  
  iVar8 = Aska::GlobalIDEManager::Add(Aska::IntegratedDynamicsEnvironment*)();
  uVar7 = _UNK_027dbb38;
  uVar6 = _UNK_027dbb30;
  uVar5 = _UNK_027dbb28;
  uVar4 = _UNK_027dbb20;
  uVar3 = _UNK_027dbb18;
  uVar2 = _UNK_027dbb10;
  uVar1 = _UNK_027dbb00;
  if (-1 < iVar8) {
    param_1 = param_1 + (long)iVar8 * 0x50;
    *(undefined8 *)(param_1 + 0x98) = _UNK_027dbb08;
    *(undefined8 *)(param_1 + 0x90) = uVar1;
    *(undefined8 *)(param_1 + 0xa8) = uVar3;
    *(undefined8 *)(param_1 + 0xa0) = uVar2;
    *(undefined8 *)(param_1 + 0xd0) = param_3;
    *(undefined8 *)(param_1 + 0xb8) = uVar5;
    *(undefined8 *)(param_1 + 0xb0) = uVar4;
    *(undefined8 *)(param_1 + 200) = uVar7;
    *(undefined8 *)(param_1 + 0xc0) = uVar6;
  }
  return -1 < iVar8;
}

// ==== Aska::LIBLManager::Add(Aska::IntegratedDynamicsEnvironment*)
// vaddr 0x213786c | ghidra 0x223786c | size 92 | symbol _ZN4Aska11LIBLManager3AddEPNS_29IntegratedDynamicsEnvironmentE | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 _ZN4Aska11LIBLManager3AddEPNS_29IntegratedDynamicsEnvironmentE(long param_1)

{
  undefined8 uVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  int iVar8;
  
  iVar8 = Aska::GlobalIDEManager::Add(Aska::IntegratedDynamicsEnvironment*)();
  uVar7 = _UNK_027dbb38;
  uVar6 = _UNK_027dbb30;
  uVar5 = _UNK_027dbb28;
  uVar4 = _UNK_027dbb20;
  uVar3 = _UNK_027dbb18;
  uVar2 = _UNK_027dbb10;
  uVar1 = _UNK_027dbb00;
  if (-1 < iVar8) {
    param_1 = param_1 + (long)iVar8 * 0x50;
    *(undefined8 *)(param_1 + 0x98) = _UNK_027dbb08;
    *(undefined8 *)(param_1 + 0x90) = uVar1;
    *(undefined8 *)(param_1 + 0xa8) = uVar3;
    *(undefined8 *)(param_1 + 0xa0) = uVar2;
    *(undefined8 *)(param_1 + 0xd0) = 0;
    *(undefined8 *)(param_1 + 0xb8) = uVar5;
    *(undefined8 *)(param_1 + 0xb0) = uVar4;
    *(undefined8 *)(param_1 + 200) = uVar7;
    *(undefined8 *)(param_1 + 0xc0) = uVar6;
    return 1;
  }
  return 0;
}

// ==== Aska::LIBLManager::_LIBLNotify::GetMarginOBB(Aska::Box*, Aska::Light const*)
// vaddr 0x21378c8 | ghidra 0x22378c8 | size 468 | symbol _ZN4Aska11LIBLManager11_LIBLNotify12GetMarginOBBEPNS_3BoxEPKNS_5LightE | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska11LIBLManager11_LIBLNotify12GetMarginOBBEPNS_3BoxEPKNS_5LightE
               (undefined8 *param_1,long param_2)

{
  undefined8 uVar1;
  long *plVar2;
  undefined8 uVar3;
  float *pfVar4;
  float fVar5;
  float fVar6;
  
  uVar1 = _UNK_027dbb38;
  uVar3 = _UNK_027dbb30;
  plVar2 = *(long **)(param_2 + 0x410);
  pfVar4 = (float *)(param_1 + 4);
  *pfVar4 = 1.0;
  *(undefined8 *)((long)param_1 + 0x2c) = 0;
  *(undefined8 *)((long)param_1 + 0x24) = 0;
  *(undefined4 *)((long)param_1 + 0x34) = 0x3f800000;
  param_1[7] = 0;
  param_1[8] = 0;
  param_1[9] = 0x3f800000;
  *(undefined4 *)(param_1 + 2) = 0x3f800000;
  *(undefined8 *)((long)param_1 + 0x14) = 0x3f8000003f800000;
  param_1[1] = uVar1;
  *param_1 = uVar3;
  uVar3 = (**(code **)(*plVar2 + 0x98))();
  Aska::Vector::ApplyMatrix(Aska::Matrix const*)(param_1,uVar3);
  Aska::Vector::ApplyMatrixNoTransport(Aska::Matrix const*)(pfVar4,uVar3);
  Aska::Vector::ApplyMatrixNoTransport(Aska::Matrix const*)(param_1 + 6,uVar3);
  Aska::Vector::ApplyMatrixNoTransport(Aska::Matrix const*)(param_1 + 8,uVar3);
  fVar6 = *pfVar4 * *pfVar4 + *(float *)((long)param_1 + 0x24) * *(float *)((long)param_1 + 0x24) +
          *(float *)(param_1 + 5) * *(float *)(param_1 + 5);
  fVar5 = SQRT(fVar6);
  if (NAN(fVar5)) {
    fVar5 = (float)sqrtf(fVar6);
  }
  fVar6 = 1.0 / fVar5;
  *(float *)(param_1 + 2) = fVar5 * *(float *)(param_1 + 2);
  *(float *)(param_1 + 4) = fVar6 * *(float *)(param_1 + 4);
  *(float *)((long)param_1 + 0x24) = fVar6 * *(float *)((long)param_1 + 0x24);
  *(float *)(param_1 + 5) = fVar6 * *(float *)(param_1 + 5);
  fVar6 = *(float *)(param_1 + 6) * *(float *)(param_1 + 6) +
          *(float *)((long)param_1 + 0x34) * *(float *)((long)param_1 + 0x34) +
          *(float *)(param_1 + 7) * *(float *)(param_1 + 7);
  fVar5 = SQRT(fVar6);
  if (NAN(fVar5)) {
    fVar5 = (float)sqrtf(fVar6);
  }
  fVar6 = 1.0 / fVar5;
  *(float *)((long)param_1 + 0x14) = fVar5 * *(float *)((long)param_1 + 0x14);
  *(float *)(param_1 + 6) = fVar6 * *(float *)(param_1 + 6);
  *(float *)((long)param_1 + 0x34) = fVar6 * *(float *)((long)param_1 + 0x34);
  *(float *)(param_1 + 7) = fVar6 * *(float *)(param_1 + 7);
  fVar6 = *(float *)(param_1 + 8) * *(float *)(param_1 + 8) +
          *(float *)((long)param_1 + 0x44) * *(float *)((long)param_1 + 0x44) +
          *(float *)(param_1 + 9) * *(float *)(param_1 + 9);
  fVar5 = SQRT(fVar6);
  if (NAN(fVar5)) {
    fVar5 = (float)sqrtf(fVar6);
  }
  fVar6 = 1.0 / fVar5;
  *(float *)(param_1 + 3) = fVar5 * *(float *)(param_1 + 3);
  *(undefined4 *)((long)param_1 + 0x2c) = 0;
  *(undefined4 *)((long)param_1 + 0x3c) = 0;
  *(float *)(param_1 + 8) = fVar6 * *(float *)(param_1 + 8);
  *(float *)((long)param_1 + 0x44) = fVar6 * *(float *)((long)param_1 + 0x44);
  *(float *)(param_1 + 9) = fVar6 * *(float *)(param_1 + 9);
  *(undefined4 *)((long)param_1 + 0x4c) = 0;
  return;
}

// ==== Aska::LIBLManager::_LIBLNotify::Handler(unsigned long)
// vaddr 0x2137a9c | ghidra 0x2237a9c | size 520 | symbol _ZN4Aska11LIBLManager11_LIBLNotify7HandlerEm | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska11LIBLManager11_LIBLNotify7HandlerEm(long param_1,long param_2)

{
  long lVar1;
  long *plVar2;
  long lVar3;
  long lVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  undefined1 auStack_90 [80];
  
  lVar3 = *(long *)(param_2 + 0x120);
  if ((*(ushort *)(lVar3 + 0x2a5) & 1) == 0) {
    return;
  }
  if (*(float *)(lVar3 + 0x2b8) < _UNK_027daba4) {
    return;
  }
  lVar4 = *(long *)(param_1 + 0x60);
  lVar1 = Aska::Light::GetIBLTextureID(int) const(lVar3,0);
  if (lVar1 == 0) {
    return;
  }
  if ((*(ushort *)(lVar3 + 0x2a5) >> 0xd & 1) != 0) {
    return;
  }
  if ((*(ulong *)(lVar4 + 0x260) & *(ulong *)(lVar3 + 0x2a8)) == 0) {
    return;
  }
  *(undefined1 *)(param_2 + 0x128) = 1;
  fVar7 = *(float *)(param_2 + 0x90) * *(float *)(param_2 + 0x94) * *(float *)(param_2 + 0x98);
  if (*(long *)(lVar3 + 0x410) == 0) {
    lVar3 = *(long *)(param_2 + 0x120);
    plVar2 = (long *)(param_1 + 0x68);
    if (*plVar2 == 0) {
      fVar5 = *(float *)(param_1 + 0x74);
code_r0x02237c4c:
      lVar1 = 0;
      *(long *)(param_1 + 0x78) = *plVar2;
      *(undefined4 *)(param_1 + 0x80) = *(undefined4 *)(param_1 + 0x70);
      *(float *)(param_1 + 0x84) = fVar5;
    }
    else {
      fVar5 = *(float *)(param_1 + 0x74);
      if ((fVar7 + fVar7 < fVar5) || ((fVar7 <= fVar5 && (*(float *)(param_1 + 0x70) < 1.0))))
      goto code_r0x02237c4c;
      plVar2 = (long *)(param_1 + 0x78);
      if ((*plVar2 != 0) && (*(float *)(param_1 + 0x84) <= fVar7 + fVar7)) {
        if (*(float *)(param_1 + 0x84) < fVar7) {
          return;
        }
        if (1.0 <= *(float *)(param_1 + 0x80)) {
          return;
        }
      }
      lVar1 = 1;
    }
    *plVar2 = lVar3;
    param_1 = param_1 + lVar1 * 0x10;
    *(undefined4 *)(param_1 + 0x70) = 0x3f800000;
    goto code_r0x02237c6c;
  }
  Aska::LIBLManager::_LIBLNotify::GetMarginOBB(Aska::Box*, Aska::Light const*)(auStack_90,lVar3);
  fVar5 = (float)Aska::Collision::CalcWeightMarginOBB(Aska::Box const*, Aska::Box const*, Aska::Box const*)(param_1 + 0x10,param_2 + 0x80,auStack_90);
  lVar3 = *(long *)(param_2 + 0x120);
  plVar2 = (long *)(param_1 + 0x68);
  if (*plVar2 == 0) {
    fVar6 = *(float *)(param_1 + 0x74);
code_r0x02237c28:
    lVar1 = 0;
    *(long *)(param_1 + 0x78) = *plVar2;
    *(undefined4 *)(param_1 + 0x80) = *(undefined4 *)(param_1 + 0x70);
    *(float *)(param_1 + 0x84) = fVar6;
  }
  else {
    fVar6 = *(float *)(param_1 + 0x74);
    if ((fVar7 + fVar7 < fVar6) || ((fVar7 <= fVar6 && (*(float *)(param_1 + 0x70) < fVar5))))
    goto code_r0x02237c28;
    plVar2 = (long *)(param_1 + 0x78);
    if ((*plVar2 != 0) && (*(float *)(param_1 + 0x84) <= fVar7 + fVar7)) {
      if (*(float *)(param_1 + 0x84) < fVar7) {
        return;
      }
      if (fVar5 <= *(float *)(param_1 + 0x80)) {
        return;
      }
    }
    lVar1 = 1;
  }
  *plVar2 = lVar3;
  param_1 = param_1 + lVar1 * 0x10;
  *(float *)(param_1 + 0x70) = fVar5;
code_r0x02237c6c:
  *(float *)(param_1 + 0x74) = fVar7;
  return;
}

// ==== Aska::LIBLManager::_LIBLNotify::Set(Aska::RenderableObject*, float, float)
// vaddr 0x2137ca4 | ghidra 0x2237ca4 | size 136 | symbol _ZN4Aska11LIBLManager11_LIBLNotify3SetEPNS_16RenderableObjectEff | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11LIBLManager11_LIBLNotify3SetEPNS_16RenderableObjectEff
               (float param_1,float param_2,long param_3,long param_4)

{
  long *plVar1;
  long lVar2;
  
  plVar1 = (long *)(param_3 + 0x68);
  if (*plVar1 != 0) {
    if ((*(float *)(param_3 + 0x74) <= param_2 + param_2) &&
       ((*(float *)(param_3 + 0x74) < param_2 || (param_1 <= *(float *)(param_3 + 0x70))))) {
      plVar1 = (long *)(param_3 + 0x78);
      if ((*plVar1 != 0) && (*(float *)(param_3 + 0x84) <= param_2 + param_2)) {
        if (*(float *)(param_3 + 0x84) < param_2) {
          return;
        }
        if (param_1 <= *(float *)(param_3 + 0x80)) {
          return;
        }
      }
      lVar2 = 1;
      goto code_r0x02237ce8;
    }
  }
  lVar2 = 0;
  *(undefined8 *)(param_3 + 0x78) = *(undefined8 *)(param_3 + 0x68);
  *(undefined4 *)(param_3 + 0x80) = *(undefined4 *)(param_3 + 0x70);
  *(undefined4 *)(param_3 + 0x84) = *(undefined4 *)(param_3 + 0x74);
code_r0x02237ce8:
  *plVar1 = param_4;
  param_3 = param_3 + lVar2 * 0x10;
  *(float *)(param_3 + 0x70) = param_1;
  *(float *)(param_3 + 0x74) = param_2;
  return;
}

// ==== Aska::LIBLManager::Get(unsigned long, void*) const
// vaddr 0x2137d2c | ghidra 0x2237d2c | size 8 | symbol _ZNK4Aska11LIBLManager3GetEmPv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska11LIBLManager3GetEmPv(void)

{
  return 0;
}

// ==== Aska::LIBLManager::Set(unsigned long, void const*)
// vaddr 0x2137d34 | ghidra 0x2237d34 | size 8 | symbol _ZN4Aska11LIBLManager3SetEmPKv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska11LIBLManager3SetEmPKv(void)

{
  return 0;
}

// ==== Aska::LIBLManager::AddAar(Aska::AarHandler*, int, unsigned long)
// vaddr 0x2137d3c | ghidra 0x2237d3c | size 780 | symbol _ZN4Aska11LIBLManager6AddAarEPNS_10AarHandlerEim | lib libSOA-3.7.0.so | 2026-10-04
undefined4
_ZN4Aska11LIBLManager6AddAarEPNS_10AarHandlerEim
          (long param_1,long param_2,undefined4 param_3,undefined8 param_4)

{
  int *piVar1;
  uint uVar2;
  char cVar3;
  bool bVar4;
  ulong uVar5;
  ulong uVar6;
  int iVar7;
  long lVar8;
  int *piVar9;
  undefined4 uVar10;
  
  if ((*(long *)(param_2 + 8) == 0) || (*(int *)(*(long *)(param_2 + 0x10) + 0x20) != 0x4c49424c)) {
    return 0;
  }
  piVar9 = (int *)(param_1 + 0x5c8);
  iVar7 = 0;
code_r0x02237d84:
  if (*piVar9 == -1) {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
    if (bVar4) {
      *piVar9 = 0;
      cVar3 = ExclusiveMonitorsStatus();
    }
    if (cVar3 == '\0') goto code_r0x02237e68;
    goto code_r0x02237d84;
  }
  ClearExclusiveLocal();
  bVar4 = iVar7 < 0x1ff;
  iVar7 = iVar7 + 1;
  if (bVar4) goto code_r0x02237d84;
  piVar1 = (int *)(param_1 + 0x5cc);
  do {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar4) {
      *piVar1 = *piVar1 + 1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
  do {
    if (*piVar9 != -1) {
      ClearExclusiveLocal();
      do {
        uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0x608);
        if ((uVar5 & 1) == 0) {
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
          Aska::Semaphore::Wait() const(param_1 + 0x608);
        }
        do {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar4) {
            *piVar1 = *piVar1 + 1;
            cVar3 = ExclusiveMonitorsStatus();
          }
        } while (cVar3 != '\0');
        while (*piVar9 == -1) {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
          if (bVar4) {
            *piVar9 = 0;
            cVar3 = ExclusiveMonitorsStatus();
          }
          if (cVar3 == '\0') goto code_r0x02237e58;
        }
        ClearExclusiveLocal();
      } while( true );
    }
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
    if (bVar4) {
      *piVar9 = 0;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
code_r0x02237e58:
  do {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar4) {
      *piVar1 = *piVar1 + -1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
code_r0x02237e68:
  DataMemoryBarrier(2,3);
  for (lVar8 = *(long *)(param_1 + 0x688); param_1 + 0x678 != lVar8; lVar8 = *(long *)(lVar8 + 0x10)
      ) {
    if (*(long *)(lVar8 + 0xb8) == param_2) goto code_r0x02237ff8;
  }
  uVar5 = Aska::TPoolLegacy<Aska::LIBLManager::_AarLoaderElem, false>::Scoop()(param_1 + 0x620);
  if (uVar5 != 0) {
    if (*(long *)(uVar5 + 0x250) != 0) {
      Aska::LIBLManager::_AarLoaderElem::Detach()(uVar5);
    }
    uVar6 = Aska::AarLoaderForBlendTexture::AttachMain(Aska::AarHandler const*, int, unsigned long)(uVar5 + 0x18,param_2,param_3,param_4);
    if ((uVar6 & 1) != 0) {
      if ((((*(long *)(param_2 + 8) != 0) &&
           (piVar9 = *(int **)(param_2 + 0x18), piVar9 != (int *)0x0)) && (*piVar9 == 0x41727279))
         && ((*(ushort *)(piVar9 + 7) & 0xfff) == 2)) {
        uVar2 = piVar9[4];
        lVar8 = operator new[](unsigned long, std::nothrow_t const&)((ulong)uVar2 << 5,PTR__ZSt7nothrow_02cb9a80);
        *(long *)(uVar5 + 0x250) = lVar8;
        if (lVar8 != 0) {
          memset(lVar8,0,(ulong)uVar2 << 5);
          *(undefined4 *)(uVar5 + 0x25c) = 0xff7fffff;
          lVar8 = *(long *)(param_1 + 0x680);
          uVar10 = 1;
          *(long *)(uVar5 + 8) = lVar8;
          *(long *)(uVar5 + 0x10) = param_1 + 0x678;
          *(ulong *)(param_1 + 0x680) = uVar5;
          *(ulong *)(lVar8 + 0x10) = uVar5;
          *(int *)(param_1 + 0x8e0) = *(int *)(param_1 + 0x8e0) + 1;
          goto code_r0x02237ffc;
        }
      }
      Aska::LIBLManager::_AarLoaderElem::Detach()(uVar5);
    }
    uVar6 = *(ulong *)(param_1 + 0x660);
    uVar10 = 0;
    if ((uVar6 == 0) || (uVar5 < uVar6)) goto code_r0x02237ffc;
    if (uVar5 < uVar6 + (ulong)*(uint *)(param_1 + 0x64c) * 0x268) {
      uVar5 = ((long)(uVar5 - uVar6) >> 3) * 0x4fcace213f2b3885;
      (*(code *)**(undefined8 **)(uVar6 + (uVar5 & 0xffffffff) * 0x268))();
      lVar8 = (uVar5 >> 5 & 0x7ffffff) * 4;
      uVar10 = 0;
      *(uint *)(*(long *)(param_1 + 0x640) + lVar8) =
           *(uint *)(*(long *)(param_1 + 0x640) + lVar8) &
           (1 << (ulong)((uint)uVar5 & 0x1f) ^ 0xffffffffU);
      *(int *)(param_1 + 0x65c) = *(int *)(param_1 + 0x65c) + -1;
      goto code_r0x02237ffc;
    }
  }
code_r0x02237ff8:
  uVar10 = 0;
code_r0x02237ffc:
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_1 + 0x5c8) = 0xffffffff;
  DataMemoryBarrier(2,3);
  if (*(int *)(param_1 + 0x5cc) < 0x15) {
    return uVar10;
  }
  piVar9 = (int *)(param_1 + 0x5cc);
  do {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
    if (bVar4) {
      *piVar9 = *piVar9 + -1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
  uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0x608);
  if ((uVar5 & 1) == 0) {
    return uVar10;
  }
  Aska::Semaphore::Signal() const(param_1 + 0x608);
  return uVar10;
}

// ==== Aska::LIBLManager::ExistsLocal(Aska::AarHandler const*) const
// vaddr 0x2138048 | ghidra 0x2238048 | size 64 | symbol _ZNK4Aska11LIBLManager11ExistsLocalEPKNS_10AarHandlerE | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska11LIBLManager11ExistsLocalEPKNS_10AarHandlerE(long param_1,long param_2)

{
  long lVar1;
  
  lVar1 = *(long *)(param_1 + 0x688);
  if (param_1 + 0x678 == lVar1) {
    return 0;
  }
  do {
    if (*(long *)(lVar1 + 0xb8) == param_2) {
      return 1;
    }
    lVar1 = *(long *)(lVar1 + 0x10);
  } while (param_1 + 0x678 != lVar1);
  return 0;
}

// ==== Aska::TPoolLegacy<Aska::LIBLManager::_AarLoaderElem, false>::Scoop()
// vaddr 0x2138088 | ghidra 0x2238088 | size 280 | symbol _ZN4Aska11TPoolLegacyINS_11LIBLManager14_AarLoaderElemELb0EE5ScoopEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska11TPoolLegacyINS_11LIBLManager14_AarLoaderElemELb0EE5ScoopEv(long param_1)

{
  undefined *puVar1;
  long *plVar2;
  uint uVar3;
  undefined *puVar4;
  uint uVar5;
  long lVar6;
  uint uVar7;
  long lVar8;
  ulong uVar9;
  ulong uVar10;
  ulong uVar11;
  
  if (*(uint *)(param_1 + 0x3c) < *(uint *)(param_1 + 0x2c)) {
    lVar6 = *(long *)(param_1 + 0x20);
    uVar5 = *(uint *)(param_1 + 0x38);
    do {
      uVar7 = uVar5;
      if (*(uint *)(param_1 + 0x2c) <= uVar7) {
        uVar7 = 0;
      }
      uVar3 = 1 << (ulong)(uVar7 & 0x1f);
      uVar5 = uVar7 + 1;
    } while ((uVar3 & *(uint *)(lVar6 + (ulong)(uVar7 >> 5) * 4)) != 0);
    uVar9 = *(long *)(param_1 + 0x40) + (ulong)uVar7 * 0x268;
    uVar10 = uVar9;
    do {
      uVar11 = uVar10 + 0x7f & 0xffffffffffffff81;
      Hint_Prefetch(uVar10,0,2,0);
      uVar10 = uVar11;
    } while (uVar11 < uVar9 + 0x268);
    lVar8 = (ulong)(uVar7 >> 5) * 4;
    *(uint *)(param_1 + 0x38) = uVar7 + 1;
    *(uint *)(param_1 + 0x3c) = *(uint *)(param_1 + 0x3c) + 1;
    puVar4 = PTR__ZTVN4Aska11LIBLManager14_AarLoaderElemE_02cbe138;
    *(uint *)(lVar6 + lVar8) = *(uint *)(lVar6 + lVar8) | uVar3;
    puVar1 = PTR__ZTVN4Aska24AarLoaderForBlendTextureE_02cb9820 + 0x10;
    plVar2 = (long *)(*(long *)(param_1 + 0x40) + (ulong)uVar7 * 0x268);
    plVar2[2] = 0;
    plVar2[1] = 0;
    *plVar2 = (long)(puVar4 + 0x10);
    plVar2[3] = (long)puVar1;
    Aska::FastCriticalSection::FastCriticalSection()(plVar2 + 4);
    plVar2[0x18] = 0;
    plVar2[0x17] = 0;
    plVar2[0x16] = 0;
    Aska::AsyncStream::AsyncStream(unsigned int)(plVar2 + 0x19,0x80);
    plVar2[0x46] = 0;
    plVar2[0x4c] = 0;
    plVar2[0x4a] = 0;
    plVar2[0x49] = 0;
    lVar6 = *(long *)(param_1 + 0x40) + (ulong)uVar7 * 0x268;
  }
  else {
    lVar6 = 0;
  }
  return lVar6;
}

// ==== Aska::LIBLManager::_AarLoaderElem::Attach(Aska::AarHandler*, int, unsigned long)
// vaddr 0x21381a0 | ghidra 0x22381a0 | size 208 | symbol _ZN4Aska11LIBLManager14_AarLoaderElem6AttachEPNS_10AarHandlerEim | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska11LIBLManager14_AarLoaderElem6AttachEPNS_10AarHandlerEim
          (long param_1,long param_2,undefined4 param_3,undefined8 param_4)

{
  uint uVar1;
  ulong uVar2;
  long lVar3;
  int *piVar4;
  
  if (*(long *)(param_1 + 0x250) != 0) {
    Aska::LIBLManager::_AarLoaderElem::Detach()(param_1);
  }
  uVar2 = Aska::AarLoaderForBlendTexture::AttachMain(Aska::AarHandler const*, int, unsigned long)(param_1 + 0x18,param_2,param_3,param_4);
  if ((uVar2 & 1) != 0) {
    if ((((*(long *)(param_2 + 8) != 0) &&
         (piVar4 = *(int **)(param_2 + 0x18), piVar4 != (int *)0x0)) && (*piVar4 == 0x41727279)) &&
       ((*(ushort *)(piVar4 + 7) & 0xfff) == 2)) {
      uVar1 = piVar4[4];
      lVar3 = operator new[](unsigned long, std::nothrow_t const&)((ulong)uVar1 << 5,PTR__ZSt7nothrow_02cb9a80);
      *(long *)(param_1 + 0x250) = lVar3;
      if (lVar3 != 0) {
        memset(lVar3,0,(ulong)uVar1 << 5);
        *(undefined4 *)(param_1 + 0x25c) = 0xff7fffff;
        return 1;
      }
    }
    Aska::LIBLManager::_AarLoaderElem::Detach()(param_1);
  }
  return 0;
}

// ==== Aska::TList<Aska::LIBLManager::_AarLoaderElem>::Add(Aska::LIBLManager::_AarLoaderElem*)
// vaddr 0x2138270 | ghidra 0x2238270 | size 36 | symbol _ZN4Aska5TListINS_11LIBLManager14_AarLoaderElemEE3AddEPS2_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5TListINS_11LIBLManager14_AarLoaderElemEE3AddEPS2_(long param_1,long param_2)

{
  long lVar1;
  
  lVar1 = *(long *)(param_1 + 0x10);
  *(long *)(param_2 + 8) = lVar1;
  *(long *)(param_2 + 0x10) = param_1 + 8;
  *(long *)(param_1 + 0x10) = param_2;
  *(long *)(lVar1 + 0x10) = param_2;
  *(int *)(param_1 + 0x270) = *(int *)(param_1 + 0x270) + 1;
  return;
}

// ==== Aska::LIBLManager::AddAar(Aska::AarHandler*, Aska::IStream*)
// vaddr 0x2138294 | ghidra 0x2238294 | size 772 | symbol _ZN4Aska11LIBLManager6AddAarEPNS_10AarHandlerEPNS_7IStreamE | lib libSOA-3.7.0.so | 2026-10-04
undefined4
_ZN4Aska11LIBLManager6AddAarEPNS_10AarHandlerEPNS_7IStreamE
          (long param_1,long param_2,undefined8 param_3)

{
  int *piVar1;
  uint uVar2;
  char cVar3;
  bool bVar4;
  ulong uVar5;
  ulong uVar6;
  int iVar7;
  long lVar8;
  int *piVar9;
  undefined4 uVar10;
  
  if ((*(long *)(param_2 + 8) == 0) || (*(int *)(*(long *)(param_2 + 0x10) + 0x20) != 0x4c49424c)) {
    return 0;
  }
  piVar9 = (int *)(param_1 + 0x5c8);
  iVar7 = 0;
code_r0x022382d8:
  if (*piVar9 == -1) {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
    if (bVar4) {
      *piVar9 = 0;
      cVar3 = ExclusiveMonitorsStatus();
    }
    if (cVar3 == '\0') goto code_r0x022383bc;
    goto code_r0x022382d8;
  }
  ClearExclusiveLocal();
  bVar4 = iVar7 < 0x1ff;
  iVar7 = iVar7 + 1;
  if (bVar4) goto code_r0x022382d8;
  piVar1 = (int *)(param_1 + 0x5cc);
  do {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar4) {
      *piVar1 = *piVar1 + 1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
  do {
    if (*piVar9 != -1) {
      ClearExclusiveLocal();
      do {
        uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0x608);
        if ((uVar5 & 1) == 0) {
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
          Aska::Semaphore::Wait() const(param_1 + 0x608);
        }
        do {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar4) {
            *piVar1 = *piVar1 + 1;
            cVar3 = ExclusiveMonitorsStatus();
          }
        } while (cVar3 != '\0');
        while (*piVar9 == -1) {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
          if (bVar4) {
            *piVar9 = 0;
            cVar3 = ExclusiveMonitorsStatus();
          }
          if (cVar3 == '\0') goto code_r0x022383ac;
        }
        ClearExclusiveLocal();
      } while( true );
    }
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
    if (bVar4) {
      *piVar9 = 0;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
code_r0x022383ac:
  do {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar4) {
      *piVar1 = *piVar1 + -1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
code_r0x022383bc:
  DataMemoryBarrier(2,3);
  for (lVar8 = *(long *)(param_1 + 0x688); param_1 + 0x678 != lVar8; lVar8 = *(long *)(lVar8 + 0x10)
      ) {
    if (*(long *)(lVar8 + 0xb8) == param_2) goto code_r0x02238548;
  }
  uVar5 = Aska::TPoolLegacy<Aska::LIBLManager::_AarLoaderElem, false>::Scoop()(param_1 + 0x620);
  if (uVar5 != 0) {
    if (*(long *)(uVar5 + 0x250) != 0) {
      Aska::LIBLManager::_AarLoaderElem::Detach()(uVar5);
    }
    uVar6 = Aska::AarLoaderForBlendTexture::AttachMain(Aska::AarHandler const*, Aska::IStream*)(uVar5 + 0x18,param_2,param_3);
    if ((uVar6 & 1) != 0) {
      if ((((*(long *)(param_2 + 8) != 0) &&
           (piVar9 = *(int **)(param_2 + 0x18), piVar9 != (int *)0x0)) && (*piVar9 == 0x41727279))
         && ((*(ushort *)(piVar9 + 7) & 0xfff) == 2)) {
        uVar2 = piVar9[4];
        lVar8 = operator new[](unsigned long, std::nothrow_t const&)((ulong)uVar2 << 5,PTR__ZSt7nothrow_02cb9a80);
        *(long *)(uVar5 + 0x250) = lVar8;
        if (lVar8 != 0) {
          memset(lVar8,0,(ulong)uVar2 << 5);
          *(undefined4 *)(uVar5 + 0x25c) = 0xff7fffff;
          lVar8 = *(long *)(param_1 + 0x680);
          uVar10 = 1;
          *(long *)(uVar5 + 8) = lVar8;
          *(long *)(uVar5 + 0x10) = param_1 + 0x678;
          *(ulong *)(param_1 + 0x680) = uVar5;
          *(ulong *)(lVar8 + 0x10) = uVar5;
          *(int *)(param_1 + 0x8e0) = *(int *)(param_1 + 0x8e0) + 1;
          goto code_r0x0223854c;
        }
      }
      Aska::LIBLManager::_AarLoaderElem::Detach()(uVar5);
    }
    uVar6 = *(ulong *)(param_1 + 0x660);
    uVar10 = 0;
    if ((uVar6 == 0) || (uVar5 < uVar6)) goto code_r0x0223854c;
    if (uVar5 < uVar6 + (ulong)*(uint *)(param_1 + 0x64c) * 0x268) {
      uVar5 = ((long)(uVar5 - uVar6) >> 3) * 0x4fcace213f2b3885;
      (*(code *)**(undefined8 **)(uVar6 + (uVar5 & 0xffffffff) * 0x268))();
      lVar8 = (uVar5 >> 5 & 0x7ffffff) * 4;
      uVar10 = 0;
      *(uint *)(*(long *)(param_1 + 0x640) + lVar8) =
           *(uint *)(*(long *)(param_1 + 0x640) + lVar8) &
           (1 << (ulong)((uint)uVar5 & 0x1f) ^ 0xffffffffU);
      *(int *)(param_1 + 0x65c) = *(int *)(param_1 + 0x65c) + -1;
      goto code_r0x0223854c;
    }
  }
code_r0x02238548:
  uVar10 = 0;
code_r0x0223854c:
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_1 + 0x5c8) = 0xffffffff;
  DataMemoryBarrier(2,3);
  if (*(int *)(param_1 + 0x5cc) < 0x15) {
    return uVar10;
  }
  piVar9 = (int *)(param_1 + 0x5cc);
  do {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
    if (bVar4) {
      *piVar9 = *piVar9 + -1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
  uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0x608);
  if ((uVar5 & 1) == 0) {
    return uVar10;
  }
  Aska::Semaphore::Signal() const(param_1 + 0x608);
  return uVar10;
}

// ==== Aska::LIBLManager::_AarLoaderElem::Attach(Aska::AarHandler*, Aska::IStream*)
// vaddr 0x2138598 | ghidra 0x2238598 | size 192 | symbol _ZN4Aska11LIBLManager14_AarLoaderElem6AttachEPNS_10AarHandlerEPNS_7IStreamE | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska11LIBLManager14_AarLoaderElem6AttachEPNS_10AarHandlerEPNS_7IStreamE
          (long param_1,long param_2,undefined8 param_3)

{
  uint uVar1;
  ulong uVar2;
  long lVar3;
  int *piVar4;
  
  if (*(long *)(param_1 + 0x250) != 0) {
    Aska::LIBLManager::_AarLoaderElem::Detach()(param_1);
  }
  uVar2 = Aska::AarLoaderForBlendTexture::AttachMain(Aska::AarHandler const*, Aska::IStream*)(param_1 + 0x18,param_2,param_3);
  if ((uVar2 & 1) != 0) {
    if ((((*(long *)(param_2 + 8) != 0) &&
         (piVar4 = *(int **)(param_2 + 0x18), piVar4 != (int *)0x0)) && (*piVar4 == 0x41727279)) &&
       ((*(ushort *)(piVar4 + 7) & 0xfff) == 2)) {
      uVar1 = piVar4[4];
      lVar3 = operator new[](unsigned long, std::nothrow_t const&)((ulong)uVar1 << 5,PTR__ZSt7nothrow_02cb9a80);
      *(long *)(param_1 + 0x250) = lVar3;
      if (lVar3 != 0) {
        memset(lVar3,0,(ulong)uVar1 << 5);
        *(undefined4 *)(param_1 + 0x25c) = 0xff7fffff;
        return 1;
      }
    }
    Aska::LIBLManager::_AarLoaderElem::Detach()(param_1);
  }
  return 0;
}

// ==== Aska::LIBLManager::RemoveAar(Aska::AarHandler*)
// vaddr 0x2138658 | ghidra 0x2238658 | size 560 | symbol _ZN4Aska11LIBLManager9RemoveAarEPNS_10AarHandlerE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11LIBLManager9RemoveAarEPNS_10AarHandlerE(long param_1,long param_2)

{
  int *piVar1;
  int *piVar2;
  char cVar3;
  bool bVar4;
  int iVar5;
  ulong uVar6;
  ulong *puVar7;
  long lVar8;
  long lVar9;
  ulong uVar10;
  
  piVar1 = (int *)(param_1 + 0x5c8);
  iVar5 = 0;
code_r0x02238674:
  if (*piVar1 == -1) {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar4) {
      *piVar1 = 0;
      cVar3 = ExclusiveMonitorsStatus();
    }
    if (cVar3 == '\0') goto code_r0x0223873c;
    goto code_r0x02238674;
  }
  ClearExclusiveLocal();
  bVar4 = iVar5 < 0x1ff;
  iVar5 = iVar5 + 1;
  if (bVar4) goto code_r0x02238674;
  piVar2 = (int *)(param_1 + 0x5cc);
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
        uVar10 = Aska::Semaphore::IsReady() const(param_1 + 0x608);
        if ((uVar10 & 1) == 0) {
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
          Aska::Semaphore::Wait() const(param_1 + 0x608);
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
          if (cVar3 == '\0') goto code_r0x0223872c;
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
code_r0x0223872c:
  do {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar4) {
      *piVar2 = *piVar2 + -1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
code_r0x0223873c:
  DataMemoryBarrier(2,3);
  puVar7 = (ulong *)(param_1 + 0x688);
  do {
    uVar10 = *puVar7;
    if (param_1 + 0x678U == uVar10) goto code_r0x02238824;
    puVar7 = (ulong *)(uVar10 + 0x10);
  } while (*(long *)(uVar10 + 0xb8) != param_2);
  lVar8 = *(long *)(uVar10 + 8);
  lVar9 = *(long *)(uVar10 + 0x10);
  if (lVar8 != 0) {
    *(long *)(lVar8 + 0x10) = lVar9;
  }
  if (lVar9 != 0) {
    *(long *)(lVar9 + 8) = lVar8;
  }
  if (0 < *(int *)(param_1 + 0x8e0)) {
    *(int *)(param_1 + 0x8e0) = *(int *)(param_1 + 0x8e0) + -1;
  }
  *(long *)(uVar10 + 8) = 0;
  *(undefined8 *)(uVar10 + 0x10) = 0;
  Aska::LIBLManager::_AarLoaderElem::Detach()(uVar10);
  uVar6 = *(ulong *)(param_1 + 0x660);
  if (((uVar6 != 0) && (uVar6 <= uVar10)) &&
     (uVar10 < uVar6 + (ulong)*(uint *)(param_1 + 0x64c) * 0x268)) {
    uVar10 = ((long)(uVar10 - uVar6) >> 3) * 0x4fcace213f2b3885;
    (*(code *)**(undefined8 **)(uVar6 + (uVar10 & 0xffffffff) * 0x268))();
    lVar8 = (uVar10 >> 5 & 0x7ffffff) * 4;
    *(uint *)(*(long *)(param_1 + 0x640) + lVar8) =
         *(uint *)(*(long *)(param_1 + 0x640) + lVar8) &
         (1 << (ulong)((uint)uVar10 & 0x1f) ^ 0xffffffffU);
    *(int *)(param_1 + 0x65c) = *(int *)(param_1 + 0x65c) + -1;
  }
code_r0x02238824:
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_1 + 0x5c8) = 0xffffffff;
  DataMemoryBarrier(2,3);
  if (0x14 < *(int *)(param_1 + 0x5cc)) {
    piVar1 = (int *)(param_1 + 0x5cc);
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
    uVar10 = Aska::Semaphore::IsReady() const(param_1 + 0x608);
    if ((uVar10 & 1) != 0) {
      (*(code *)PTR__ZNK4Aska9Semaphore6SignalEv_02c96cd0)(param_1 + 0x608);
      return;
    }
  }
  return;
}

// ==== Aska::LIBLManager::UpdateTexture(Aska::Box const*, float)
// vaddr 0x2138888 | ghidra 0x2238888 | size 184 | symbol _ZN4Aska11LIBLManager13UpdateTextureEPKNS_3BoxEf | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11LIBLManager13UpdateTextureEPKNS_3BoxEf
               (undefined4 param_1,long param_2,undefined8 param_3)

{
  int iVar1;
  long *plVar2;
  long *plVar3;
  undefined *puStack_b8;
  undefined4 uStack_b0;
  long lStack_a8;
  long alStack_a0 [16];
  
  if (param_2 + 0x678 != *(long *)(param_2 + 0x688)) {
    iVar1 = 0;
    plVar2 = (long *)(param_2 + 8);
    do {
      if (*plVar2 != 0) {
        alStack_a0[iVar1] = *plVar2;
        iVar1 = iVar1 + 1;
        if (*(int *)(param_2 + 0x88) <= iVar1) break;
      }
      plVar2 = plVar2 + 1;
    } while (plVar2 < (long *)(param_2 + 0x88U));
    puStack_b8 = PTR__ZTVN4Aska11LIBLManager16_StreamingNotifyE_02cbe278 + 0x10;
    if (0 < iVar1) {
      plVar2 = alStack_a0;
      uStack_b0 = param_1;
      do {
        lStack_a8 = *plVar2;
        plVar3 = plVar2 + 1;
        Aska::IntegratedDynamicsEnvironment::FindIntersectObjects(Aska::INotify*, Aska::Box const*, unsigned short)(*plVar2,&puStack_b8,param_3,0xffff);
        plVar2 = plVar3;
      } while (plVar3 < alStack_a0 + iVar1);
    }
  }
  return;
}

// ==== Aska::LIBLManager::_StreamingNotify::Handler(unsigned long)
// vaddr 0x2138940 | ghidra 0x2238940 | size 304 | symbol _ZN4Aska11LIBLManager16_StreamingNotify7HandlerEm | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska11LIBLManager16_StreamingNotify7HandlerEm(long param_1,long param_2)

{
  long lVar1;
  long *plVar2;
  undefined8 uVar4;
  long lVar5;
  float fVar6;
  long alStack_60 [2];
  long lStack_50;
  undefined1 auStack_48 [8];
  undefined1 auStack_40 [16];
  undefined4 *puStack_30;
  int iStack_24;
  long *plVar3;
  
  plVar2 = (long *)(*(long *)PTR__ZN4Aska6Global14m_pLIBLManagerE_02cc46a8 + 8);
  while( true ) {
    plVar3 = plVar2 + 1;
    if ((*plVar2 != 0) && (*plVar2 == *(long *)(param_1 + 0x10))) break;
    plVar2 = plVar3;
    if ((long *)(*(long *)PTR__ZN4Aska6Global14m_pLIBLManagerE_02cc46a8 + 0x88U) <= plVar3) {
      return;
    }
  }
  lVar5 = *(long *)(param_2 + 0x120);
  if ((*(ushort *)(lVar5 + 0x2a5) & 1) == 0) {
    return;
  }
  if (*(float *)(lVar5 + 0x2b8) < _UNK_027daba4) {
    return;
  }
  lVar1 = Aska::Light::GetIBLTextureID(int) const(lVar5,0);
  if (lVar1 == 0) {
    return;
  }
  if ((*(ushort *)(lVar5 + 0x2a5) >> 0xd & 1) != 0) {
    return;
  }
  lVar1 = Aska::Light::GetIBLTextureID(int) const(lVar5,0);
  if (lVar1 == 0) {
    return;
  }
  lStack_50 = 0;
  Aska::LIBLManager::_AarLoaderList::Find(unsigned long, Aska::LIBLManager::_AarLoaderElem**)(alStack_60,lVar1,lVar1,&lStack_50);
  if (lStack_50 == 0) {
    return;
  }
  if (alStack_60[0] == 0) {
    return;
  }
  fVar6 = *(float *)(param_1 + 8);
  uVar4 = *(undefined8 *)(param_1 + 0x10);
  lVar1 = lStack_50 + 0x18;
  *(float *)(lStack_50 + 600) = fVar6;
  *(undefined8 *)(lStack_50 + 0x260) = uVar4;
  iStack_24 = (int)(fVar6 + 0.5);
  Aska::AarHandler::Iterator Aska::AarHandler::Find<unsigned int, Aska::AAR::LIBLAnimIndex, Aska::TBinarySearchLessEqual<unsigned int, Aska::AAR::LIBLAnimIndex, Aska::TCompare<unsigned int, Aska::AAR::LIBLAnimIndex> > >(Aska::AarHandler::Iterator const&, unsigned int const&, Aska::AAR::LIBLAnimIndex const**, Aska::TBinarySearchLessEqual<unsigned int, Aska::AAR::LIBLAnimIndex, Aska::TCompare<unsigned int, Aska::AAR::LIBLAnimIndex> > const&) const(auStack_40,*(undefined8 *)(lStack_50 + 0xb8),alStack_60,&iStack_24,&puStack_30,
                  auStack_48);
  Aska::AarLoaderForBlendTexture::Read(unsigned int, Aska::AarHandler::Iterator&, Aska::AarHandler::Iterator&, void const*, void const*)(lVar1,*puStack_30,alStack_60,auStack_40,lVar5);
  return;
}

// ==== Aska::LIBLManager::ExistsIDE(Aska::IntegratedDynamicsEnvironment const*)
// vaddr 0x2138a70 | ghidra 0x2238a70 | size 48 | symbol _ZN4Aska11LIBLManager9ExistsIDEEPKNS_29IntegratedDynamicsEnvironmentE | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska11LIBLManager9ExistsIDEEPKNS_29IntegratedDynamicsEnvironmentE(long param_1,long param_2)

{
  long *plVar1;
  long *plVar2;
  
  plVar1 = (long *)(param_1 + 8);
  while( true ) {
    plVar2 = plVar1 + 1;
    if ((*plVar1 != 0) && (*plVar1 == param_2)) break;
    plVar1 = plVar2;
    if ((long *)(param_1 + 0x88U) <= plVar2) {
      return 0;
    }
  }
  return 1;
}

// ==== Aska::LIBLManager::_AarLoaderList::Find(unsigned long, Aska::LIBLManager::_AarLoaderElem**)
// vaddr 0x2138aa0 | ghidra 0x2238aa0 | size 448 | symbol _ZN4Aska11LIBLManager14_AarLoaderList4FindEmPPNS0_14_AarLoaderElemE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11LIBLManager14_AarLoaderList4FindEmPPNS0_14_AarLoaderElemE
               (long *param_1,undefined8 param_2,undefined8 param_3,long *param_4)

{
  int *piVar1;
  int *piVar2;
  char cVar3;
  bool bVar4;
  long lVar5;
  ulong uVar6;
  int iVar7;
  long lVar8;
  long lVar9;
  undefined8 uStack_58;
  undefined8 uStack_50;
  undefined8 uStack_48;
  
  lVar9 = *(long *)PTR__ZN4Aska6Global14m_pLIBLManagerE_02cc46a8;
  piVar1 = (int *)(lVar9 + 0x5c8);
  iVar7 = 0;
  do {
    while (*piVar1 == -1) {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = 0;
        cVar3 = ExclusiveMonitorsStatus();
      }
      if (cVar3 == '\0') goto code_r0x02238b9c;
    }
    ClearExclusiveLocal();
    bVar4 = iVar7 < 0x1ff;
    iVar7 = iVar7 + 1;
  } while (bVar4);
  piVar2 = (int *)(lVar9 + 0x5cc);
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
        uVar6 = Aska::Semaphore::IsReady() const(lVar9 + 0x608);
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
          Aska::Semaphore::Wait() const(lVar9 + 0x608);
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
          if (cVar3 == '\0') goto code_r0x02238b8c;
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
code_r0x02238b8c:
  do {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar4) {
      *piVar2 = *piVar2 + -1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
code_r0x02238b9c:
  DataMemoryBarrier(2,3);
  lVar8 = *(long *)(lVar9 + 0x688);
  do {
    if (lVar9 + 0x678 == lVar8) {
      *param_1 = 0;
      param_1[1] = 0;
code_r0x02238c00:
      DataMemoryBarrier(2,3);
      *(undefined4 *)(lVar9 + 0x5c8) = 0xffffffff;
      DataMemoryBarrier(2,3);
      if (0x14 < *(int *)(lVar9 + 0x5cc)) {
        piVar1 = (int *)(lVar9 + 0x5cc);
        do {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar4) {
            *piVar1 = *piVar1 + -1;
            cVar3 = ExclusiveMonitorsStatus();
          }
        } while (cVar3 != '\0');
        uVar6 = Aska::Semaphore::IsReady() const(lVar9 + 0x608);
        if ((uVar6 & 1) != 0) {
          Aska::Semaphore::Signal() const(lVar9 + 0x608);
        }
      }
      return;
    }
    lVar5 = *(long *)(lVar8 + 0xb8);
    uStack_50 = 0;
    if (*(long *)(lVar5 + 8) != 0) {
      uStack_50 = *(undefined8 *)(lVar5 + 0x18);
    }
    uStack_48 = 0;
    uStack_58 = param_3;
    Aska::AarHandler::Find(Aska::AarHandler::Iterator const&, void const*, unsigned long) const(param_1,lVar5,&uStack_50,&uStack_58,8);
    if (*param_1 != 0) {
      *param_4 = lVar8;
      goto code_r0x02238c00;
    }
    lVar8 = *(long *)(lVar8 + 0x10);
  } while( true );
}

// ==== Aska::LIBLManager::_AarLoaderElem::Read(float, Aska::AarHandler::Iterator&, void const*, Aska::IntegratedDynamicsEnvironment*)
// vaddr 0x2138c60 | ghidra 0x2238c60 | size 124 | symbol _ZN4Aska11LIBLManager14_AarLoaderElem4ReadEfRNS_10AarHandler8IteratorEPKvPNS_29IntegratedDynamicsEnvironmentE | lib libSOA-3.7.0.so | 2026-10-04
uint _ZN4Aska11LIBLManager14_AarLoaderElem4ReadEfRNS_10AarHandler8IteratorEPKvPNS_29IntegratedDynamicsEnvironmentE
               (float param_1,long param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5)

{
  uint uVar1;
  undefined1 auStack_48 [8];
  undefined1 auStack_40 [16];
  undefined4 *puStack_30;
  int iStack_24;
  
  *(float *)(param_2 + 600) = param_1;
  iStack_24 = (int)(param_1 + 0.5);
  *(undefined8 *)(param_2 + 0x260) = param_5;
  Aska::AarHandler::Iterator Aska::AarHandler::Find<unsigned int, Aska::AAR::LIBLAnimIndex, Aska::TBinarySearchLessEqual<unsigned int, Aska::AAR::LIBLAnimIndex, Aska::TCompare<unsigned int, Aska::AAR::LIBLAnimIndex> > >(Aska::AarHandler::Iterator const&, unsigned int const&, Aska::AAR::LIBLAnimIndex const**, Aska::TBinarySearchLessEqual<unsigned int, Aska::AAR::LIBLAnimIndex, Aska::TCompare<unsigned int, Aska::AAR::LIBLAnimIndex> > const&) const(auStack_40,*(undefined8 *)(param_2 + 0xb8),param_3,&iStack_24,&puStack_30,
                  auStack_48);
  uVar1 = Aska::AarLoaderForBlendTexture::Read(unsigned int, Aska::AarHandler::Iterator&, Aska::AarHandler::Iterator&, void const*, void const*)(param_2 + 0x18,*puStack_30,param_3,auStack_40,param_4);
  return uVar1 & 1;
}

// ==== Aska::LIBLManager::_AarLoaderElem::AttachMain(Aska::AarHandler*)
// vaddr 0x2138cdc | ghidra 0x2238cdc | size 140 | symbol _ZN4Aska11LIBLManager14_AarLoaderElem10AttachMainEPNS_10AarHandlerE | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska11LIBLManager14_AarLoaderElem10AttachMainEPNS_10AarHandlerE(long param_1,long param_2)

{
  uint uVar1;
  long lVar2;
  undefined8 uVar3;
  int *piVar4;
  
  if ((((*(long *)(param_2 + 8) == 0) || (piVar4 = *(int **)(param_2 + 0x18), piVar4 == (int *)0x0))
      || (*piVar4 != 0x41727279)) || ((*(ushort *)(piVar4 + 7) & 0xfff) != 2)) {
    uVar3 = 0;
  }
  else {
    uVar1 = piVar4[4];
    lVar2 = operator new[](unsigned long, std::nothrow_t const&)((ulong)uVar1 << 5,PTR__ZSt7nothrow_02cb9a80);
    *(long *)(param_1 + 0x250) = lVar2;
    uVar3 = 0;
    if (lVar2 != 0) {
      memset(lVar2,0,(ulong)uVar1 << 5);
      uVar3 = 1;
      *(undefined4 *)(param_1 + 0x25c) = 0xff7fffff;
    }
  }
  return uVar3;
}

// ==== Aska::LIBLManager::DetachTexture(void*)
// vaddr 0x2138d68 | ghidra 0x2238d68 | size 92 | symbol _ZN4Aska11LIBLManager13DetachTextureEPv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11LIBLManager13DetachTextureEPv(long param_1,long param_2)

{
  ulong uVar1;
  
  uVar1 = Aska::DeleteManager::AddMain(void*, unsigned char, unsigned char, Aska::IDeleteHandler*)(PTR__ZN4Aska6Global21m_systemDeleteManagerE_02cb77c0,param_2,0,0,
                          param_1 + 0x910);
  if (((uVar1 & 1) == 0) && (Aska::ITextureHandler::DetachTexture(Aska::AFF::AskaFile const*, bool)(param_1 + 0x918,param_2,0), param_2 != 0)) {
    (*(code *)PTR__ZdaPv_02cb5db8)(param_2);
    return;
  }
  return;
}

// ==== Aska::LIBLManager::_AarLoaderElem::Exists(unsigned long)
// vaddr 0x2138eec | ghidra 0x2238eec | size 56 | symbol _ZN4Aska11LIBLManager14_AarLoaderElem6ExistsEm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11LIBLManager14_AarLoaderElem6ExistsEm(long param_1,undefined8 param_2)

{
  long lVar1;
  undefined8 uStack_20;
  undefined8 uStack_18;
  undefined8 uStack_8;
  
  lVar1 = *(long *)(param_1 + 0xb8);
  uStack_20 = 0;
  if (*(long *)(lVar1 + 8) != 0) {
    uStack_20 = *(undefined8 *)(lVar1 + 0x18);
  }
  uStack_18 = 0;
  uStack_8 = param_2;
  Aska::AarHandler::Find(Aska::AarHandler::Iterator const&, void const*, unsigned long) const(lVar1,&uStack_20,&uStack_8,8);
  return;
}

// ==== Aska::LIBLManager::_AarLoaderUpdateTask::Run(int)
// vaddr 0x2138f24 | ghidra 0x2238f24 | size 16 | symbol _ZN4Aska11LIBLManager20_AarLoaderUpdateTask3RunEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11LIBLManager20_AarLoaderUpdateTask3RunEi(void)

{
  (*(code *)PTR__ZN4Aska11LIBLManager11CopyTextureEv_02c9a3d8)
            (*(undefined8 *)PTR__ZN4Aska6Global14m_pLIBLManagerE_02cc46a8);
  return;
}

// ==== Aska::LIBLManager::CopyTexture()
// vaddr 0x2138f34 | ghidra 0x2238f34 | size 3244 | symbol _ZN4Aska11LIBLManager11CopyTextureEv | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska11LIBLManager11CopyTextureEv(long param_1)

{
  long lVar1;
  long lVar2;
  undefined *puVar3;
  long lVar4;
  undefined *puVar5;
  long *plVar6;
  long lVar7;
  uint *puVar8;
  int iVar9;
  char cVar10;
  float fVar11;
  int *piVar12;
  float fVar13;
  bool bVar14;
  bool bVar15;
  bool bVar16;
  uint uVar17;
  ulong uVar18;
  int iVar19;
  long lVar20;
  long lVar21;
  long *plVar22;
  uint *puVar24;
  long lVar25;
  bool bVar26;
  long lVar27;
  long lVar28;
  long lVar29;
  int *piVar30;
  int *piVar31;
  long lVar32;
  long lVar33;
  undefined8 uVar34;
  long lVar35;
  long lVar36;
  float fVar37;
  float fVar38;
  float fVar39;
  uint uStack_15c;
  long lStack_158;
  long lStack_150;
  long lStack_148;
  uint uStack_13c;
  long lStack_130;
  uint uStack_114;
  undefined8 uStack_f0;
  float fStack_e8;
  float fStack_e4;
  float fStack_e0;
  float fStack_dc;
  float fStack_d8;
  float fStack_d4;
  float fStack_d0;
  float fStack_cc;
  float fStack_c8;
  float fStack_c4;
  float fStack_c0;
  float fStack_bc;
  float fStack_b8;
  float fStack_b4;
  long lStack_a0;
  long lStack_98;
  long lStack_90;
  long lStack_88;
  long *plVar23;
  
  piVar30 = (int *)(param_1 + 0x5c8);
  iVar19 = 0;
code_r0x02238f64:
  do {
    if (*piVar30 == -1) goto code_r0x02238f70;
    ClearExclusiveLocal();
    bVar26 = iVar19 < 0x1ff;
    iVar19 = iVar19 + 1;
  } while (bVar26);
  piVar31 = (int *)(param_1 + 0x5cc);
  do {
    cVar10 = '\x01';
    bVar26 = (bool)ExclusiveMonitorPass(piVar31,0x10);
    if (bVar26) {
      *piVar31 = *piVar31 + 1;
      cVar10 = ExclusiveMonitorsStatus();
    }
  } while (cVar10 != '\0');
  do {
    if (*piVar30 != -1) {
      ClearExclusiveLocal();
      do {
        uVar18 = Aska::Semaphore::IsReady() const(param_1 + 0x608);
        if ((uVar18 & 1) == 0) {
          do {
            cVar10 = '\x01';
            bVar26 = (bool)ExclusiveMonitorPass(piVar31,0x10);
            if (bVar26) {
              *piVar31 = *piVar31 + -1;
              cVar10 = ExclusiveMonitorsStatus();
            }
          } while (cVar10 != '\0');
          Aska::Thread::Sleep(unsigned int)(1);
        }
        else {
          Aska::Semaphore::Wait() const(param_1 + 0x608);
        }
        do {
          cVar10 = '\x01';
          bVar26 = (bool)ExclusiveMonitorPass(piVar31,0x10);
          if (bVar26) {
            *piVar31 = *piVar31 + 1;
            cVar10 = ExclusiveMonitorsStatus();
          }
        } while (cVar10 != '\0');
        while (*piVar30 == -1) {
          cVar10 = '\x01';
          bVar26 = (bool)ExclusiveMonitorPass(piVar30,0x10);
          if (bVar26) {
            *piVar30 = 0;
            cVar10 = ExclusiveMonitorsStatus();
          }
          if (cVar10 == '\0') goto code_r0x0223901c;
        }
        ClearExclusiveLocal();
      } while( true );
    }
    cVar10 = '\x01';
    bVar26 = (bool)ExclusiveMonitorPass(piVar30,0x10);
    if (bVar26) {
      *piVar30 = 0;
      cVar10 = ExclusiveMonitorsStatus();
    }
  } while (cVar10 != '\0');
code_r0x0223901c:
  do {
    cVar10 = '\x01';
    bVar26 = (bool)ExclusiveMonitorPass(piVar31,0x10);
    if (bVar26) {
      *piVar31 = *piVar31 + -1;
      cVar10 = ExclusiveMonitorsStatus();
    }
  } while (cVar10 != '\0');
code_r0x0223902c:
  fVar13 = _UNK_027ebde0;
  DataMemoryBarrier(2,3);
  lVar35 = *(long *)(param_1 + 0x688);
  if (param_1 + 0x678 == lVar35) goto code_r0x02239b6c;
  lVar1 = param_1 + 0x918;
  lVar2 = param_1 + 0x910;
  lVar25 = *(long *)PTR__ZN4Aska6Global17m_pTextureManagerE_02cc19f0;
  puVar3 = PTR__ZTVN4Aska12StaticStreamE_02cba478 + 0x10;
  lVar4 = lVar25 + 0xb0;
code_r0x022390b0:
  plVar22 = (long *)(param_1 + 8);
  do {
    plVar23 = plVar22 + 1;
    if ((*plVar22 != 0) && (*plVar22 == *(long *)(lVar35 + 0x260))) {
      lVar28 = *(long *)(lVar35 + 0xb0);
      if (*(uint *)(lVar28 + 0x58) != 0) {
        lVar29 = *(long *)(lVar35 + 0x250);
        uVar17 = 0;
        goto code_r0x022390ec;
      }
      break;
    }
    plVar22 = plVar23;
  } while (plVar23 < (long *)(param_1 + 0x88U));
  goto code_r0x02239b5c;
code_r0x02238f70:
  cVar10 = '\x01';
  bVar26 = (bool)ExclusiveMonitorPass(piVar30,0x10);
  if (bVar26) {
    *piVar30 = 0;
    cVar10 = ExclusiveMonitorsStatus();
  }
  if (cVar10 == '\0') goto code_r0x0223902c;
  goto code_r0x02238f64;
  while (uVar17 = uVar17 + 1, uVar17 < *(uint *)(lVar28 + 0x58)) {
code_r0x022390ec:
    lVar33 = *(long *)(*(long *)(lVar28 + 0x50) + (ulong)uVar17 * 8);
    if (lVar33 != 0) {
      lVar32 = *(long *)(lVar33 + 0x18);
      if (*(long *)(lVar33 + 0x18) != 0) {
        do {
          lVar33 = lVar32;
          lVar32 = *(long *)(lVar33 + 0x18);
          if (*(long *)(lVar33 + 0x18) == 0) goto joined_r0x02239118;
        } while( true );
      }
      goto code_r0x02239124;
    }
  }
  goto code_r0x02239b5c;
code_r0x02239124:
  do {
    lVar32 = (long)(int)*(uint *)(lVar33 + 0x100);
    uVar17 = *(uint *)(lVar33 + 0x100) ^ 1;
    piVar30 = (int *)(lVar33 + 0x30 + lVar32 * 0x68 + 0x40);
    iVar19 = *piVar30;
    piVar31 = (int *)(lVar33 + 0x30 + (long)(int)uVar17 * 0x68 + 0x40);
    iVar9 = *piVar31;
    if ((3 < iVar19) && (3 < iVar9)) {
      lStack_a0 = 0;
      lStack_98 = 0;
      lVar27 = lVar33 + 0x30 + lVar32 * 0x68;
      lVar7 = *(long *)(lVar27 + 0x48);
      puVar8 = *(uint **)(lVar27 + 0x50);
      lVar27 = (long)(int)uVar17;
      puVar24 = *(uint **)(lVar33 + 0x30 + lVar27 * 0x68 + 0x50);
      fVar39 = *(float *)(lVar7 + 0x300) * fVar13;
      bVar26 = 0.0 < fVar39;
      if ((iVar19 == 4) || (iVar9 == 4)) {
        plVar22 = (long *)(lVar29 + lVar32 * 0x10);
        plVar23 = (long *)(lVar29 + lVar27 * 0x10);
        lVar20 = lVar32;
        if (iVar19 == 4) {
          lStack_150 = Aska::AarTextureCommon::TextureHandler::GetTextureID(void*)(lVar1,*(undefined8 *)(lVar33 + lVar32 * 0x68 + 0x50));
          if ((*plVar22 == lStack_150) || (lVar20 = lVar27, *plVar23 == lStack_150))
          goto code_r0x02239214;
          lVar20 = 0;
          bVar14 = true;
        }
        else {
          lStack_150 = *plVar22;
code_r0x02239214:
          lVar20 = *(long *)(lVar29 + lVar20 * 0x10 + 8);
          bVar14 = false;
        }
        lStack_148 = lVar20;
        lVar21 = lVar27;
        if (iVar9 == 4) {
          lStack_130 = Aska::AarTextureCommon::TextureHandler::GetTextureID(void*)(lVar1,*(undefined8 *)(lVar33 + lVar27 * 0x68 + 0x50));
          if ((*plVar23 == lStack_130) || (lVar21 = lVar32, *plVar22 == lStack_130))
          goto code_r0x02239278;
          lStack_158 = 0;
          bVar16 = true;
          if (!bVar14) goto code_r0x022393a8;
code_r0x0223928c:
          lVar21 = lVar33 + lVar32 * 0x68;
          fStack_c4 = 0.0;
          fStack_c8 = 0.0;
          fStack_dc = 0.0;
          fStack_e0 = 0.0;
          fStack_e4 = 0.0;
          fStack_e8 = 0.0;
          fStack_cc = 0.0;
          fStack_d0 = 0.0;
          fStack_d4 = 0.0;
          fStack_d8 = 0.0;
          uStack_f0 = puVar3;
          Aska::StaticStream::Open(signed char const*, unsigned long)(&uStack_f0,*(undefined8 *)(lVar21 + 0x50),*(undefined8 *)(lVar21 + 0x60));
          Aska::ResourceReadyQueue::Invoke(Aska::IStream*, void**, long*, Aska::INotify*, Aska::IMemoryManager*, Aska::ResourceReadyQueue::AllocationType, bool)(*(undefined8 *)PTR__ZN4Aska6Global21m_pResourceReadyQueueE_02cbc808,
                          &uStack_f0,&lStack_98,0,0,0,0,0);
          if (lStack_98 == 0) {
            uStack_13c = 0;
            uStack_114 = 1;
            iVar19 = 7;
          }
          else {
            lStack_88 = 0;
            if (*(int *)(lStack_98 + 4) == 0) {
              uStack_114 = 0;
              uStack_13c = 1;
              lStack_148 = lStack_98;
              iVar19 = 0;
              lStack_90 = lVar1;
            }
            else {
              lStack_88 = lStack_98 + 0x10;
              lVar36 = *(long *)PTR__ZN4Aska6Global17m_pTextureManagerE_02cc19f0;
              lVar21 = lVar36 + 0xb0;
              lStack_90 = lVar1;
              Aska::CriticalSection::Enter() const(lVar21);
              uVar17 = Aska::TextureManager::RegisterTextureEx(Aska::TextureMemory::tagKey const*, bool, int, int)(lVar36,&lStack_90,0,0,1);
              Aska::CriticalSection::Leave() const(lVar21);
              uStack_13c = uVar17 & 1;
              uStack_114 = ~uVar17 & 1;
              bVar14 = (uVar17 & 1) == 0;
              lStack_148 = lStack_98;
              if (bVar14) {
                lStack_148 = lVar20;
              }
              iVar19 = 0;
              if (bVar14) {
                iVar19 = 7;
              }
            }
          }
          uStack_f0 = PTR__ZTVN4Aska12StaticStreamE_02cba478 + 0x10;
          piVar12 = (int *)CONCAT44(fStack_cc,fStack_d0);
          if (piVar12 == (int *)0x0) {
code_r0x022393f8:
            if (CONCAT44(fStack_d4,fStack_d8) != 0) {
              operator delete[](void*)();
            }
            if (CONCAT44(fStack_cc,fStack_d0) != 0) {
              Aska::TSharedPointerCode::DeleteCounter(int*)();
            }
          }
          else {
            do {
              iVar9 = *piVar12;
              cVar10 = '\x01';
              bVar14 = (bool)ExclusiveMonitorPass(piVar12,0x10);
              if (bVar14) {
                *piVar12 = iVar9 + -1;
                cVar10 = ExclusiveMonitorsStatus();
              }
            } while (cVar10 != '\0');
            if (iVar9 + -1 == 0) goto code_r0x022393f8;
          }
          fStack_d4 = 0.0;
          fStack_d8 = 0.0;
          fStack_cc = 0.0;
          fStack_d0 = 0.0;
          piVar12 = (int *)CONCAT44(fStack_dc,fStack_e0);
          if (piVar12 == (int *)0x0) {
code_r0x02239434:
            if (CONCAT44(fStack_e4,fStack_e8) != 0) {
              operator delete[](void*)();
            }
            if (CONCAT44(fStack_dc,fStack_e0) != 0) {
              Aska::TSharedPointerCode::DeleteCounter(int*)();
            }
          }
          else {
            do {
              iVar9 = *piVar12;
              cVar10 = '\x01';
              bVar14 = (bool)ExclusiveMonitorPass(piVar12,0x10);
              if (bVar14) {
                *piVar12 = iVar9 + -1;
                cVar10 = ExclusiveMonitorsStatus();
              }
            } while (cVar10 != '\0');
            if (iVar9 + -1 == 0) goto code_r0x02239434;
          }
          if (iVar19 == 0) goto code_r0x0223946c;
          uStack_15c = 0;
        }
        else {
          lStack_130 = *plVar23;
code_r0x02239278:
          lStack_158 = *(long *)(lVar29 + lVar21 * 0x10 + 8);
          bVar16 = false;
          if (bVar14) goto code_r0x0223928c;
code_r0x022393a8:
          uStack_13c = 0;
          uStack_114 = 0;
code_r0x0223946c:
          if (bVar16) {
            lVar20 = lVar33 + lVar27 * 0x68;
            puVar5 = PTR__ZTVN4Aska12StaticStreamE_02cba478 + 0x10;
            fStack_c4 = 0.0;
            fStack_c8 = 0.0;
            fStack_dc = 0.0;
            fStack_e0 = 0.0;
            fStack_e4 = 0.0;
            fStack_e8 = 0.0;
            fStack_cc = 0.0;
            fStack_d0 = 0.0;
            fStack_d4 = 0.0;
            fStack_d8 = 0.0;
            uStack_f0 = puVar5;
            Aska::StaticStream::Open(signed char const*, unsigned long)(&uStack_f0,*(undefined8 *)(lVar20 + 0x50),*(undefined8 *)(lVar20 + 0x60)
                           );
            Aska::ResourceReadyQueue::Invoke(Aska::IStream*, void**, long*, Aska::INotify*, Aska::IMemoryManager*, Aska::ResourceReadyQueue::AllocationType, bool)(*(undefined8 *)PTR__ZN4Aska6Global21m_pResourceReadyQueueE_02cbc808,
                            &uStack_f0,&lStack_a0,0,0,0,0,0);
            if (lStack_a0 == 0) {
              uStack_15c = 0;
              uStack_114 = 1;
              iVar19 = 7;
            }
            else {
              lStack_88 = 0;
              if (*(int *)(lStack_a0 + 4) == 0) {
                uStack_15c = 1;
                lStack_158 = lStack_a0;
                iVar19 = 0;
                lStack_90 = lVar1;
              }
              else {
                lStack_88 = lStack_a0 + 0x10;
                lVar21 = *(long *)PTR__ZN4Aska6Global17m_pTextureManagerE_02cc19f0;
                lVar20 = lVar21 + 0xb0;
                lStack_90 = lVar1;
                Aska::CriticalSection::Enter() const(lVar20);
                uVar17 = Aska::TextureManager::RegisterTextureEx(Aska::TextureMemory::tagKey const*, bool, int, int)(lVar21,&lStack_90,0,0,1);
                Aska::CriticalSection::Leave() const(lVar20);
                uStack_15c = uVar17 & 1;
                bVar14 = (uVar17 & 1) == 0;
                lVar20 = lStack_a0;
                if (bVar14) {
                  uStack_114 = 1;
                  lVar20 = lStack_158;
                }
                iVar19 = 0;
                lStack_158 = lVar20;
                if (bVar14) {
                  iVar19 = 7;
                }
              }
            }
            piVar12 = (int *)CONCAT44(fStack_cc,fStack_d0);
            if (piVar12 == (int *)0x0) {
code_r0x022395b8:
              uStack_f0 = puVar5;
              if (CONCAT44(fStack_d4,fStack_d8) != 0) {
                operator delete[](void*)();
              }
              if (CONCAT44(fStack_cc,fStack_d0) != 0) {
                Aska::TSharedPointerCode::DeleteCounter(int*)();
              }
            }
            else {
              do {
                iVar9 = *piVar12;
                cVar10 = '\x01';
                bVar14 = (bool)ExclusiveMonitorPass(piVar12,0x10);
                if (bVar14) {
                  *piVar12 = iVar9 + -1;
                  cVar10 = ExclusiveMonitorsStatus();
                }
              } while (cVar10 != '\0');
              uStack_f0 = puVar5;
              if (iVar9 + -1 == 0) goto code_r0x022395b8;
            }
            fStack_d4 = 0.0;
            fStack_d8 = 0.0;
            fStack_cc = 0.0;
            fStack_d0 = 0.0;
            piVar12 = (int *)CONCAT44(fStack_dc,fStack_e0);
            if (piVar12 == (int *)0x0) {
code_r0x022395f4:
              if (CONCAT44(fStack_e4,fStack_e8) != 0) {
                operator delete[](void*)();
              }
              if (CONCAT44(fStack_dc,fStack_e0) != 0) {
                Aska::TSharedPointerCode::DeleteCounter(int*)();
              }
            }
            else {
              do {
                iVar9 = *piVar12;
                cVar10 = '\x01';
                bVar14 = (bool)ExclusiveMonitorPass(piVar12,0x10);
                if (bVar14) {
                  *piVar12 = iVar9 + -1;
                  cVar10 = ExclusiveMonitorsStatus();
                }
              } while (cVar10 != '\0');
              if (iVar9 + -1 == 0) goto code_r0x022395f4;
            }
            if (iVar19 != 0) goto code_r0x0223987c;
          }
          else {
            uStack_15c = 0;
          }
          if ((((*plVar22 != lStack_150) && (*plVar22 != lStack_130)) &&
              (lVar20 = *(long *)(lVar29 + lVar32 * 0x10 + 8), lVar20 != 0)) &&
             (uVar18 = Aska::DeleteManager::AddMain(void*, unsigned char, unsigned char, Aska::IDeleteHandler*)(PTR__ZN4Aska6Global21m_systemDeleteManagerE_02cb77c0,lVar20,0
                                       ,0,lVar2), (uVar18 & 1) == 0)) {
            Aska::ITextureHandler::DetachTexture(Aska::AFF::AskaFile const*, bool)(lVar1,lVar20,0);
            operator delete[](void*)(lVar20);
          }
          plVar6 = (long *)(lVar29 + lVar27 * 0x10 + 8);
          if (((*plVar23 != lStack_150) && (*plVar23 != lStack_130)) &&
             ((lVar20 = *plVar6, lVar20 != 0 &&
              (uVar18 = Aska::DeleteManager::AddMain(void*, unsigned char, unsigned char, Aska::IDeleteHandler*)(PTR__ZN4Aska6Global21m_systemDeleteManagerE_02cb77c0,lVar20,
                                        0,0,lVar2), (uVar18 & 1) == 0)))) {
            Aska::ITextureHandler::DetachTexture(Aska::AFF::AskaFile const*, bool)(lVar1,lVar20,0);
            operator delete[](void*)(lVar20);
          }
          *plVar22 = lStack_150;
          *(long *)(lVar29 + lVar32 * 0x10 + 8) = lStack_148;
          *plVar23 = lStack_130;
          *plVar6 = lStack_158;
          if (0.0 < fVar39) {
            if (*(long *)(lVar35 + 0x248) == 0) {
              *(int *)PTR__ZN4Aska11LIBLManager18m_uBlendTexIDIndexE_02cbea58 =
                   *(int *)PTR__ZN4Aska11LIBLManager18m_uBlendTexIDIndexE_02cbea58 + 1;
              lVar20 = *plVar22;
              Aska::CriticalSection::Enter() const(lVar4);
              Aska::TextureManager::QueryTextureEx(unsigned long, bool)(lVar25,lVar20,0);
              Aska::CriticalSection::Leave() const(lVar4);
              bVar26 = false;
              goto code_r0x0223975c;
            }
          }
          else {
code_r0x0223975c:
            uVar34 = *(undefined8 *)(lVar33 + 0x110);
            lVar36 = *plVar22;
            lVar21 = *(long *)PTR__ZN4Aska6Global17m_pTextureManagerE_02cc19f0;
            lVar20 = lVar21 + 0xb0;
            Aska::CriticalSection::Enter() const(lVar20);
            uVar18 = Aska::TextureManager::AliasTextureEx(unsigned long, unsigned long)(lVar21,uVar34,lVar36);
            Aska::CriticalSection::Leave() const(lVar20);
            if ((uVar18 & 1) == 0) {
              iVar19 = 7;
              uStack_114 = 1;
              goto code_r0x0223987c;
            }
            if ((lVar7 != 0) && (puVar8 != (uint *)0x0)) {
              *(uint *)(lVar7 + 0x240) = puVar8[4];
              *(uint *)(lVar7 + 0x244) = puVar8[5];
              *(uint *)(lVar7 + 0x248) = puVar8[6];
              *(uint *)(lVar7 + 0x24c) = puVar8[7];
              *(uint *)(lVar7 + 0x250) = puVar8[8];
              *(uint *)(lVar7 + 0x254) = puVar8[9];
              *(uint *)(lVar7 + 600) = puVar8[10];
              *(uint *)(lVar7 + 0x25c) = puVar8[0xb];
              *(uint *)(lVar7 + 0x260) = puVar8[0xc];
              *(uint *)(lVar7 + 0x264) = puVar8[0xd];
              *(uint *)(lVar7 + 0x268) = puVar8[0xe];
              *(uint *)(lVar7 + 0x26c) = puVar8[0xf];
              *(uint *)(lVar7 + 0x270) = puVar8[0x10];
              *(uint *)(lVar7 + 0x274) = puVar8[0x11];
              *(uint *)(lVar7 + 0x278) = puVar8[0x12];
              *(uint *)(lVar7 + 0x27c) = puVar8[0x13];
            }
          }
          *piVar30 = 5;
          *piVar31 = 5;
          iVar19 = 0;
        }
code_r0x0223987c:
        bVar15 = uStack_15c != 0;
        bVar16 = uStack_13c != 0;
        bVar14 = uStack_114 != 0;
        lVar20 = lStack_98;
        if (iVar19 == 0) goto code_r0x022398a0;
      }
      else {
        bVar15 = false;
        bVar16 = false;
        bVar14 = false;
code_r0x022398a0:
        lVar20 = lStack_98;
        if ((((*(long *)(lVar29 + lVar32 * 0x10 + 8) != 0) &&
             (*(long *)(lVar29 + lVar27 * 0x10 + 8) != 0)) && (bVar26)) &&
           (((puVar8 != (uint *)0x0 && (puVar24 != (uint *)0x0)) && (*puVar8 < *puVar24)))) {
          fVar37 = (float)NEON_ucvtf(*(undefined4 *)(lVar33 + 0x118));
          fVar11 = fVar39 + fVar37;
          if (*(float *)(lVar35 + 600) <= fVar39 + fVar37) {
            fVar11 = *(float *)(lVar35 + 600);
          }
          if (fVar11 != *(float *)(lVar35 + 0x25c)) {
            fVar39 = (fVar11 - fVar37) / fVar39;
            fVar38 = (float)NEON_fminnm(fVar39,0x3f800000);
            fVar37 = 0.0;
            if (0.0 <= fVar39) {
              fVar37 = fVar38;
            }
            if (lVar7 != 0) {
              fVar39 = 1.0 - fVar37;
              uStack_f0 = (undefined *)
                          CONCAT44(fVar37 * (float)puVar24[5] + fVar39 * (float)puVar8[5],
                                   fVar37 * (float)puVar24[4] + fVar39 * (float)puVar8[4]);
              fStack_e8 = fVar37 * (float)puVar24[6] + fVar39 * (float)puVar8[6];
              fStack_e4 = fVar37 * (float)puVar24[7] + fVar39 * (float)puVar8[7];
              fStack_e0 = fVar37 * (float)puVar24[8] + fVar39 * (float)puVar8[8];
              fStack_dc = fVar37 * (float)puVar24[9] + fVar39 * (float)puVar8[9];
              fStack_d8 = fVar37 * (float)puVar24[10] + fVar39 * (float)puVar8[10];
              fStack_d4 = fVar37 * (float)puVar24[0xb] + fVar39 * (float)puVar8[0xb];
              fStack_d0 = fVar37 * (float)puVar24[0xc] + fVar39 * (float)puVar8[0xc];
              fStack_cc = fVar37 * (float)puVar24[0xd] + fVar39 * (float)puVar8[0xd];
              fStack_c8 = fVar37 * (float)puVar24[0xe] + fVar39 * (float)puVar8[0xe];
              fStack_c4 = fVar37 * (float)puVar24[0xf] + fVar39 * (float)puVar8[0xf];
              fStack_c0 = fVar37 * (float)puVar24[0x10] + fVar39 * (float)puVar8[0x10];
              fStack_bc = fVar37 * (float)puVar24[0x11] + fVar39 * (float)puVar8[0x11];
              fStack_b8 = fVar37 * (float)puVar24[0x12] + fVar39 * (float)puVar8[0x12];
              fStack_b4 = fVar37 * (float)puVar24[0x13] + fVar39 * (float)puVar8[0x13];
              *(ulong *)(lVar7 + 0x248) = CONCAT44(fStack_e4,fStack_e8);
              *(undefined **)(lVar7 + 0x240) = uStack_f0;
              *(float *)(lVar7 + 0x260) = fStack_d0;
              *(float *)(lVar7 + 0x264) = fStack_cc;
              *(float *)(lVar7 + 0x268) = fStack_c8;
              *(float *)(lVar7 + 0x26c) = fStack_c4;
              *(float *)(lVar7 + 0x270) = fStack_c0;
              *(float *)(lVar7 + 0x274) = fStack_bc;
              *(float *)(lVar7 + 0x278) = fStack_b8;
              *(ulong *)(lVar7 + 600) = CONCAT44(fStack_d4,fStack_d8);
              *(ulong *)(lVar7 + 0x250) = CONCAT44(fStack_dc,fStack_e0);
              *(float *)(lVar7 + 0x27c) = fStack_b4;
            }
            *(float *)(lVar35 + 0x25c) = fVar11;
          }
        }
      }
      lStack_98 = lVar20;
      if (bVar14) {
        if (((lVar20 != 0) && (bVar16)) &&
           (uVar18 = Aska::DeleteManager::AddMain(void*, unsigned char, unsigned char, Aska::IDeleteHandler*)(PTR__ZN4Aska6Global21m_systemDeleteManagerE_02cb77c0,lVar20,0,0
                                     ,lVar2), (uVar18 & 1) == 0)) {
          Aska::ITextureHandler::DetachTexture(Aska::AFF::AskaFile const*, bool)(lVar1,lVar20,0);
          operator delete[](void*)(lVar20);
        }
        lVar32 = lStack_a0;
        if (((lStack_a0 != 0) && (bVar15)) &&
           (uVar18 = Aska::DeleteManager::AddMain(void*, unsigned char, unsigned char, Aska::IDeleteHandler*)(PTR__ZN4Aska6Global21m_systemDeleteManagerE_02cb77c0,lStack_a0,
                                     0,0,lVar2), (uVar18 & 1) == 0)) {
          Aska::ITextureHandler::DetachTexture(Aska::AFF::AskaFile const*, bool)(lVar1,lVar32,0);
          operator delete[](void*)(lVar32);
        }
      }
    }
    lVar29 = lVar29 + 0x20;
    lVar33 = Aska::THash<Aska::AarLoaderForBlendTexture::ArrayInfo>::FindNext(Aska::AarLoaderForBlendTexture::ArrayInfo const*) const(lVar28,lVar33);
joined_r0x02239118:
  } while (lVar33 != 0);
code_r0x02239b5c:
  lVar35 = *(long *)(lVar35 + 0x10);
  if (param_1 + 0x678 == lVar35) {
code_r0x02239b6c:
    DataMemoryBarrier(2,3);
    *(undefined4 *)(param_1 + 0x5c8) = 0xffffffff;
    DataMemoryBarrier(2,3);
    if (0x14 < *(int *)(param_1 + 0x5cc)) {
      piVar30 = (int *)(param_1 + 0x5cc);
      do {
        cVar10 = '\x01';
        bVar26 = (bool)ExclusiveMonitorPass(piVar30,0x10);
        if (bVar26) {
          *piVar30 = *piVar30 + -1;
          cVar10 = ExclusiveMonitorsStatus();
        }
      } while (cVar10 != '\0');
      uVar18 = Aska::Semaphore::IsReady() const(param_1 + 0x608);
      if ((uVar18 & 1) != 0) {
        Aska::Semaphore::Signal() const(param_1 + 0x608);
      }
    }
    return;
  }
  goto code_r0x022390b0;
}

// ==== Aska::LIBLManager::~LIBLManager()
// vaddr 0x2139db4 | ghidra 0x2239db4 | size 348 | symbol _ZN4Aska11LIBLManagerD2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11LIBLManagerD2Ev(long *param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  
  *param_1 = (long)(PTR__ZTVN4Aska11LIBLManagerE_02cbbc70 + 0x10);
  Aska::LIBLManager::Delete()();
  puVar1 = PTR__ZTVN4Aska16AarTextureCommon20DetachTextureHandlerE_02cb9b38 + 0x10;
  param_1[0x123] = (long)(PTR__ZTVN4Aska15ITextureHandlerE_02cc0f80 + 0x10);
  param_1[0x122] = (long)puVar1;
  Aska::ITextureHandler::DetachTexture()(param_1 + 0x123);
  Aska::TBarrierSlim<true>::~TBarrierSlim()(param_1 + 0x125);
  puVar2 = PTR__ZTVN4Aska13TSmartPointerILb0EEE_02cc2320;
  param_1[0x123] = (long)(PTR__ZTVN4Aska13TSmartPointerILb0EEE_02cc2320 + 0x10);
  Aska::Task::~Task()(param_1 + 0x11d);
  puVar1 = PTR__ZTVN4Aska5TListINS_11LIBLManager14_AarLoaderElemEEE_02cbf788 + 0x10;
  param_1[0xcf] = (long)(PTR__ZTVN4Aska11LIBLManager14_AarLoaderElemE_02cbe138 + 0x10);
  param_1[0xce] = (long)puVar1;
  Aska::AarLoaderForBlendTexture::~AarLoaderForBlendTexture()(param_1 + 0xd2);
  param_1[0xc4] =
       (long)(PTR__ZTVN4Aska11TPoolLegacyINS_11LIBLManager14_AarLoaderElemELb0EEE_02cc17b8 + 0x10);
  if ((param_1[200] != 0) && ((char)param_1[0xca] != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 0xca) = 0;
  }
  param_1[200] = 0;
  param_1[0xc9] = 0;
  param_1[0xcb] = 0;
  if (param_1[0xcc] != 0) {
    if ((char)param_1[0xcd] != '\0') {
      operator delete[](void*)();
      param_1[0xcc] = 0;
      param_1[0xc6] = (long)(PTR__ZTVN4Aska9TBitArrayIjLb0EEE_02cba038 + 0x10);
      if ((param_1[200] != 0) && ((char)param_1[0xca] != '\0')) {
        operator delete[](void*)();
        *(undefined1 *)(param_1 + 0xca) = 0;
      }
      goto code_r0x011f2790;
    }
    param_1[0xcc] = 0;
  }
  param_1[0xc6] = (long)(PTR__ZTVN4Aska9TBitArrayIjLb0EEE_02cba038 + 0x10);
code_r0x011f2790:
  param_1[200] = 0;
  param_1[0xc9] = 0;
  param_1[0xc6] = (long)(puVar2 + 0x10);
  param_1[0xc4] = (long)(puVar2 + 0x10);
  Aska::FastCriticalSection::~FastCriticalSection()(param_1 + 0xb2);
  (*(code *)PTR__ZN4Aska11IAnimatableD2Ev_02cb13b8)(param_1);
  return;
}

// ==== Aska::LIBLManager::~LIBLManager()
// vaddr 0x2139f10 | ghidra 0x2239f10 | size 24 | symbol _ZN4Aska11LIBLManagerD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11LIBLManagerD0Ev(undefined8 param_1)

{
  Aska::LIBLManager::~LIBLManager()();
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::LIBLManager::GetClassID(int) const
// vaddr 0x2139f28 | ghidra 0x2239f28 | size 36 | symbol _ZNK4Aska11LIBLManager10GetClassIDEi | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska11LIBLManager10GetClassIDEi(undefined8 param_1,int param_2)

{
  undefined8 uVar1;
  undefined8 uVar2;
  
  uVar1 = 0xf19f;
  if (param_2 != 1) {
    uVar1 = 0xf000;
  }
  uVar2 = 0xf19ff1a0;
  if (param_2 != 0) {
    uVar2 = uVar1;
  }
  return uVar2;
}

// ==== Aska::LIBLManager::_LIBLNotify::~_LIBLNotify()
// vaddr 0x2139f4c | ghidra 0x2239f4c | size 4 | symbol _ZN4Aska11LIBLManager11_LIBLNotifyD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11LIBLManager11_LIBLNotifyD0Ev(void)

{
  (*(code *)PTR__ZdlPv_02ca4758)();
  return;
}

// ==== Aska::LIBLManager::_StreamingNotify::~_StreamingNotify()
// vaddr 0x2139f50 | ghidra 0x2239f50 | size 4 | symbol _ZN4Aska11LIBLManager16_StreamingNotifyD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11LIBLManager16_StreamingNotifyD0Ev(void)

{
  (*(code *)PTR__ZdlPv_02ca4758)();
  return;
}

// ==== Aska::LIBLManager::_AarLoaderUpdateTask::~_AarLoaderUpdateTask()
// vaddr 0x2139f54 | ghidra 0x2239f54 | size 24 | symbol _ZN4Aska11LIBLManager20_AarLoaderUpdateTaskD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11LIBLManager20_AarLoaderUpdateTaskD0Ev(undefined8 param_1)

{
  Aska::Task::~Task()();
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::LIBLManager::_AarLoaderUpdateTask::GetDefaultLevel() const
// vaddr 0x2139f6c | ghidra 0x2239f6c | size 8 | symbol _ZNK4Aska11LIBLManager20_AarLoaderUpdateTask15GetDefaultLevelEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska11LIBLManager20_AarLoaderUpdateTask15GetDefaultLevelEv(void)

{
  return 0x400000;
}

// ==== Aska::TPoolLegacy<Aska::LIBLManager::_AarLoaderElem, false>::~TPoolLegacy()
// vaddr 0x2139f74 | ghidra 0x2239f74 | size 220 | symbol _ZN4Aska11TPoolLegacyINS_11LIBLManager14_AarLoaderElemELb0EED2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11TPoolLegacyINS_11LIBLManager14_AarLoaderElemELb0EED2Ev(long *param_1)

{
  undefined *puVar1;
  long *plVar2;
  
  *param_1 = (long)(PTR__ZTVN4Aska11TPoolLegacyINS_11LIBLManager14_AarLoaderElemELb0EEE_02cc17b8 +
                   0x10);
  plVar2 = param_1 + 4;
  if ((*plVar2 != 0) && ((char)param_1[6] != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 6) = 0;
  }
  *plVar2 = 0;
  param_1[5] = 0;
  param_1[7] = 0;
  if (param_1[8] == 0) {
    param_1[2] = (long)(PTR__ZTVN4Aska9TBitArrayIjLb0EEE_02cba038 + 0x10);
  }
  else if ((char)param_1[9] == '\0') {
    param_1[2] = (long)(PTR__ZTVN4Aska9TBitArrayIjLb0EEE_02cba038 + 0x10);
    param_1[8] = 0;
  }
  else {
    operator delete[](void*)();
    param_1[2] = (long)(PTR__ZTVN4Aska9TBitArrayIjLb0EEE_02cba038 + 0x10);
    param_1[8] = 0;
    if ((param_1[4] != 0) && ((char)param_1[6] != '\0')) {
      operator delete[](void*)();
      *(undefined1 *)(param_1 + 6) = 0;
    }
  }
  *plVar2 = 0;
  param_1[5] = 0;
  puVar1 = PTR__ZTVN4Aska13TSmartPointerILb0EEE_02cc2320 + 0x10;
  param_1[2] = (long)puVar1;
  *param_1 = (long)puVar1;
  return;
}

// ==== Aska::TPoolLegacy<Aska::LIBLManager::_AarLoaderElem, false>::~TPoolLegacy()
// vaddr 0x213a050 | ghidra 0x223a050 | size 220 | symbol _ZN4Aska11TPoolLegacyINS_11LIBLManager14_AarLoaderElemELb0EED0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11TPoolLegacyINS_11LIBLManager14_AarLoaderElemELb0EED0Ev(long *param_1)

{
  long *plVar1;
  
  *param_1 = (long)(PTR__ZTVN4Aska11TPoolLegacyINS_11LIBLManager14_AarLoaderElemELb0EEE_02cc17b8 +
                   0x10);
  plVar1 = param_1 + 4;
  if ((*plVar1 != 0) && ((char)param_1[6] != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 6) = 0;
  }
  *plVar1 = 0;
  param_1[5] = 0;
  param_1[7] = 0;
  if (param_1[8] == 0) {
    param_1[2] = (long)(PTR__ZTVN4Aska9TBitArrayIjLb0EEE_02cba038 + 0x10);
  }
  else if ((char)param_1[9] == '\0') {
    param_1[2] = (long)(PTR__ZTVN4Aska9TBitArrayIjLb0EEE_02cba038 + 0x10);
    param_1[8] = 0;
  }
  else {
    operator delete[](void*)();
    param_1[2] = (long)(PTR__ZTVN4Aska9TBitArrayIjLb0EEE_02cba038 + 0x10);
    param_1[8] = 0;
    if ((param_1[4] != 0) && ((char)param_1[6] != '\0')) {
      operator delete[](void*)();
      *(undefined1 *)(param_1 + 6) = 0;
    }
  }
  *plVar1 = 0;
  param_1[5] = 0;
  param_1[2] = (long)(PTR__ZTVN4Aska13TSmartPointerILb0EEE_02cc2320 + 0x10);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::TList<Aska::LIBLManager::_AarLoaderElem>::~TList()
// vaddr 0x213a12c | ghidra 0x223a12c | size 40 | symbol _ZN4Aska5TListINS_11LIBLManager14_AarLoaderElemEED2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5TListINS_11LIBLManager14_AarLoaderElemEED2Ev(long *param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZTVN4Aska5TListINS_11LIBLManager14_AarLoaderElemEEE_02cbf788 + 0x10;
  param_1[1] = (long)(PTR__ZTVN4Aska11LIBLManager14_AarLoaderElemE_02cbe138 + 0x10);
  *param_1 = (long)puVar1;
  (*(code *)PTR__ZN4Aska24AarLoaderForBlendTextureD2Ev_02ca9c28)(param_1 + 4);
  return;
}

// ==== Aska::LIBLManager::_AarLoaderList::~_AarLoaderList()
// vaddr 0x213a154 | ghidra 0x223a154 | size 60 | symbol _ZN4Aska11LIBLManager14_AarLoaderListD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11LIBLManager14_AarLoaderListD0Ev(long *param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZTVN4Aska5TListINS_11LIBLManager14_AarLoaderElemEEE_02cbf788 + 0x10;
  param_1[1] = (long)(PTR__ZTVN4Aska11LIBLManager14_AarLoaderElemE_02cbe138 + 0x10);
  *param_1 = (long)puVar1;
  Aska::AarLoaderForBlendTexture::~AarLoaderForBlendTexture()(param_1 + 4);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::TList<Aska::LIBLManager::_AarLoaderElem>::AddTop(Aska::LIBLManager::_AarLoaderElem*)
// vaddr 0x213a190 | ghidra 0x223a190 | size 36 | symbol _ZN4Aska5TListINS_11LIBLManager14_AarLoaderElemEE6AddTopEPS2_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5TListINS_11LIBLManager14_AarLoaderElemEE6AddTopEPS2_(long param_1,long param_2)

{
  long lVar1;
  
  lVar1 = *(long *)(param_1 + 0x18);
  *(long *)(param_2 + 8) = param_1 + 8;
  *(long *)(param_2 + 0x10) = lVar1;
  *(long *)(lVar1 + 8) = param_2;
  *(long *)(param_1 + 0x18) = param_2;
  *(int *)(param_1 + 0x270) = *(int *)(param_1 + 0x270) + 1;
  return;
}

// ==== Aska::TList<Aska::LIBLManager::_AarLoaderElem>::Insert(Aska::LIBLManager::_AarLoaderElem*, Aska::LIBLManager::_AarLoaderElem*)
// vaddr 0x213a1b4 | ghidra 0x223a1b4 | size 32 | symbol _ZN4Aska5TListINS_11LIBLManager14_AarLoaderElemEE6InsertEPS2_S4_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5TListINS_11LIBLManager14_AarLoaderElemEE6InsertEPS2_S4_
               (long param_1,long param_2,long param_3)

{
  long lVar1;
  
  lVar1 = *(long *)(param_2 + 0x10);
  *(long *)(param_3 + 8) = param_2;
  *(long *)(param_3 + 0x10) = lVar1;
  *(long *)(lVar1 + 8) = param_3;
  *(long *)(param_2 + 0x10) = param_3;
  *(int *)(param_1 + 0x270) = *(int *)(param_1 + 0x270) + 1;
  return;
}

// ==== Aska::TList<Aska::LIBLManager::_AarLoaderElem>::~TList()
// vaddr 0x213a1d4 | ghidra 0x223a1d4 | size 60 | symbol _ZN4Aska5TListINS_11LIBLManager14_AarLoaderElemEED0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5TListINS_11LIBLManager14_AarLoaderElemEED0Ev(long *param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZTVN4Aska5TListINS_11LIBLManager14_AarLoaderElemEEE_02cbf788 + 0x10;
  param_1[1] = (long)(PTR__ZTVN4Aska11LIBLManager14_AarLoaderElemE_02cbe138 + 0x10);
  *param_1 = (long)puVar1;
  Aska::AarLoaderForBlendTexture::~AarLoaderForBlendTexture()(param_1 + 4);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::LIBLManager::_AarLoaderElem::~_AarLoaderElem()
// vaddr 0x213a210 | ghidra 0x223a210 | size 20 | symbol _ZN4Aska11LIBLManager14_AarLoaderElemD2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11LIBLManager14_AarLoaderElemD2Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska11LIBLManager14_AarLoaderElemE_02cbe138 + 0x10);
  (*(code *)PTR__ZN4Aska24AarLoaderForBlendTextureD2Ev_02ca9c28)(param_1 + 3);
  return;
}

// ==== Aska::LIBLManager::_AarLoaderElem::~_AarLoaderElem()
// vaddr 0x213a224 | ghidra 0x223a224 | size 40 | symbol _ZN4Aska11LIBLManager14_AarLoaderElemD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11LIBLManager14_AarLoaderElemD0Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska11LIBLManager14_AarLoaderElemE_02cbe138 + 0x10);
  Aska::AarLoaderForBlendTexture::~AarLoaderForBlendTexture()(param_1 + 3);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}


// FAILED to create function at 029cbee0 typeinfo name for Aska::LIBLManager::_LIBLNotify
// FAILED to create function at 029cbf10 typeinfo name for Aska::LIBLManager::_StreamingNotify
// FAILED to create function at 029cbf40 typeinfo name for Aska::LIBLManager::_AarLoaderUpdateTask
// FAILED to create function at 029cbf70 typeinfo name for Aska::TPoolLegacy<Aska::LIBLManager::_AarLoaderElem, false>
// FAILED to create function at 029cbfb0 typeinfo name for Aska::LIBLManager::_AarLoaderList
// FAILED to create function at 029cbfe0 typeinfo name for Aska::TList<Aska::LIBLManager::_AarLoaderElem>
// FAILED to create function at 029cc020 typeinfo name for Aska::LIBLManager::_AarLoaderElem
// FAILED to create function at 02c4e3f8 Aska::LIBLManager::vtable
// FAILED to create function at 02c4e460 Aska::LIBLManager::typeinfo
// FAILED to create function at 02c4e478 Aska::LIBLManager::_LIBLNotify::vtable
// FAILED to create function at 02c4e4a0 Aska::LIBLManager::_LIBLNotify::typeinfo
// FAILED to create function at 02c4e4b8 Aska::LIBLManager::_StreamingNotify::vtable
// FAILED to create function at 02c4e4e0 Aska::LIBLManager::_StreamingNotify::typeinfo
// FAILED to create function at 02c4e4f8 Aska::LIBLManager::_AarLoaderUpdateTask::vtable
// FAILED to create function at 02c4e5a0 Aska::LIBLManager::_AarLoaderUpdateTask::typeinfo
// FAILED to create function at 02c4e5b8 Aska::TPoolLegacy<Aska::LIBLManager::_AarLoaderElem,false>::vtable
// FAILED to create function at 02c4e5e0 Aska::TPoolLegacy<Aska::LIBLManager::_AarLoaderElem,false>::typeinfo
// FAILED to create function at 02c4e5f8 Aska::LIBLManager::_AarLoaderList::vtable
// FAILED to create function at 02c4e638 Aska::TList<Aska::LIBLManager::_AarLoaderElem>::typeinfo
// FAILED to create function at 02c4e650 Aska::LIBLManager::_AarLoaderList::typeinfo
// FAILED to create function at 02c4e668 Aska::TList<Aska::LIBLManager::_AarLoaderElem>::vtable
// FAILED to create function at 02c4e6a8 Aska::LIBLManager::_AarLoaderElem::vtable
// FAILED to create function at 02c4e6d0 Aska::LIBLManager::_AarLoaderElem::typeinfo
// FAILED to create function at 02dce490 Aska::LIBLManager::m_uBlendTexIDIndex
