// port/decomp/yayoi/http.c: Ghidra decompiles for the yayoi subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-04 06:30 UTC: tools/decomp.sh '--into' 'yayoi/http' '[ :]Aska::Yayoi::(HttpProtocoledData|HttpProtocol)::'

// ==== Aska::Yayoi::HttpProtocol::HttpProtocol()
// vaddr 0x22066b0 | ghidra 0x23066b0 | size 48 | symbol _ZN4Aska5Yayoi12HttpProtocolC2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi12HttpProtocolC1Ev(undefined1 *param_1)

{
  *param_1 = 0;
  *(undefined8 *)(param_1 + 8) = 0;
  *(undefined8 *)(param_1 + 0x10) = 0;
  param_1[0x1c] = 0;
  *(undefined8 *)(param_1 + 0x20) = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  *(undefined8 *)(param_1 + 0x38) = 0;
  *(undefined2 *)(param_1 + 0x40) = 0;
  *(undefined4 *)(param_1 + 4) = 0xf7;
  *(undefined4 *)(param_1 + 0x18) = 1;
  param_1[0x30] = 1;
  return;
}

// ==== Aska::Yayoi::HttpProtocol::~HttpProtocol()
// vaddr 0x22066e0 | ghidra 0x23066e0 | size 232 | symbol _ZN4Aska5Yayoi12HttpProtocolD2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi12HttpProtocolD1Ev(long param_1)

{
  int iVar1;
  char cVar2;
  bool bVar3;
  long lVar4;
  int *piVar5;
  char *pcVar6;
  long lVar7;
  
  if (*(long *)(param_1 + 8) != 0) {
    operator delete[](void*)();
    *(undefined8 *)(param_1 + 8) = 0;
  }
  lVar4 = *(long *)(param_1 + 0x38);
  if (lVar4 != 0) {
    pcVar6 = *(char **)(lVar4 + 0x20);
    if ((pcVar6 != (char *)0x0) && (*(long *)(lVar4 + 0x28) != 0)) {
      lVar7 = *(long *)(lVar4 + 0x28) * 0x18;
      do {
        piVar5 = (int *)(lVar4 + 0x10);
        if ((*pcVar6 == '\x01') || (piVar5 = (int *)(lVar4 + 0x14), *pcVar6 == '\x02')) {
          *piVar5 = *piVar5 + -1;
          *pcVar6 = '\0';
        }
        lVar7 = lVar7 + -0x18;
        pcVar6 = pcVar6 + 0x18;
      } while (lVar7 != 0);
    }
    *(undefined8 *)(lVar4 + 0x10) = 0;
    if (*(long **)(param_1 + 0x38) != (long *)0x0) {
      (**(code **)(**(long **)(param_1 + 0x38) + 8))();
    }
  }
  piVar5 = *(int **)(param_1 + 0x28);
  if (piVar5 != (int *)0x0) {
    do {
      iVar1 = *piVar5;
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar5,0x10);
      if (bVar3) {
        *piVar5 = iVar1 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    if (iVar1 + -1 != 0) goto code_r0x023067b8;
  }
  lVar4 = *(long *)(param_1 + 0x20);
  if (lVar4 != 0) {
    Aska::Yayoi::URI::DeleteBuffer()(lVar4);
    operator delete(void*)(lVar4);
  }
  if (*(long *)(param_1 + 0x28) != 0) {
    Aska::TSharedPointerCode::DeleteCounter(int*)();
  }
code_r0x023067b8:
  *(undefined8 *)(param_1 + 0x20) = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  return;
}

// ==== Aska::Yayoi::HttpProtocol::SetUserAgent(char const*)
// vaddr 0x22067c8 | ghidra 0x23067c8 | size 220 | symbol _ZN4Aska5Yayoi12HttpProtocol12SetUserAgentEPKc | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi12HttpProtocol12SetUserAgentEPKc(long param_1,long param_2)

{
  ulong uVar1;
  ulong uVar2;
  ulong uVar3;
  ulong uVar4;
  long lVar5;
  ulong uVar6;
  
  if (*(long *)(param_1 + 8) != 0) {
    operator delete[](void*)();
    *(undefined8 *)(param_1 + 8) = 0;
  }
  if (param_2 != 0) {
    uVar4 = strlen(param_2);
    uVar1 = uVar4 + 1;
    if (uVar1 == 0) {
      *(undefined8 *)(param_1 + 8) = 0;
    }
    else {
      lVar5 = **(long **)PTR__ZN4Aska6Global19m_pNetworkAllocatorE_02cbc200;
      if (lVar5 == 0) {
        lVar5 = Aska::Global::GetAvailableMemoryManager()();
      }
      lVar5 = Aska::MemoryManager::Malloc(unsigned long)(lVar5,uVar1);
      *(long *)(param_1 + 8) = lVar5;
      if (lVar5 != 0) {
        uVar6 = strlen(param_2);
        uVar2 = uVar6 + 1;
        if (uVar2 != uVar4) {
          uVar6 = uVar6 + 1;
        }
        uVar3 = uVar4;
        if (uVar2 <= uVar4) {
          uVar3 = uVar6;
        }
        if (uVar1 <= uVar3) {
          (*(code *)PTR_raise_02c913c0)(5);
          return;
        }
        strncpy(lVar5,param_2,uVar3);
        if (uVar4 <= uVar2) {
          *(undefined1 *)(lVar5 + uVar3) = 0;
        }
      }
    }
  }
  return;
}

// ==== Aska::Yayoi::HttpProtocol::MakeHeader(Aska::Yayoi::HttpProtocoledData*, Aska::TSharedPointer<Aska::Yayoi::URI>, Aska::TSharedPointer<Aska::Yayoi::URI>)
// vaddr 0x22068a4 | ghidra 0x23068a4 | size 1372 | symbol _ZN4Aska5Yayoi12HttpProtocol10MakeHeaderEPNS0_18HttpProtocoledDataENS_14TSharedPointerINS0_3URIEEES6_ | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska5Yayoi12HttpProtocol10MakeHeaderEPNS0_18HttpProtocoledDataENS_14TSharedPointerINS0_3URIEEES6_
               (long param_1,long param_2,long *param_3,long *param_4)

{
  undefined8 *puVar1;
  char cVar2;
  bool bVar3;
  undefined8 *puVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  long lVar10;
  long lVar11;
  long lVar12;
  long lVar13;
  long lVar14;
  long lVar15;
  undefined8 *puVar16;
  undefined8 *puVar17;
  undefined *puVar18;
  undefined8 *puVar19;
  undefined8 *puVar20;
  undefined8 *puVar21;
  undefined8 *puStack_130;
  undefined8 *puStack_128;
  undefined8 *puStack_f8;
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
  long lStack_98;
  long lStack_90;
  int *piStack_88;
  long lStack_80;
  int *piStack_78;
  long lStack_70;
  int *piStack_68;
  
  lStack_80 = *param_4;
  puVar16 = *(undefined8 **)(param_2 + 0x148);
  uVar8 = *(undefined8 *)(*(long *)PTR__ZN4Aska6Global17m_pNetworkManagerE_02cb9e90 + 0x1a0);
  piStack_78 = (int *)param_4[1];
  if (piStack_78 != (int *)0x0) {
    do {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piStack_78,0x10);
      if (bVar3) {
        *piStack_78 = *piStack_78 + 1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
  }
  Aska::Yayoi::CookieManager::GetCookie(Aska::TSharedPointer<Aska::Yayoi::URI>)(&lStack_70,uVar8,&lStack_80);
  lVar10 = lStack_80;
  if (piStack_78 == (int *)0x0) {
code_r0x0230692c:
    if (lStack_80 != 0) {
      Aska::Yayoi::URI::DeleteBuffer()(lStack_80);
      operator delete(void*)(lVar10);
    }
    if (piStack_78 != (int *)0x0) {
      Aska::TSharedPointerCode::DeleteCounter(int*)();
    }
  }
  else {
    do {
      iVar7 = *piStack_78;
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piStack_78,0x10);
      if (bVar3) {
        *piStack_78 = iVar7 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    if (iVar7 + -1 == 0) goto code_r0x0230692c;
  }
  lStack_80 = 0;
  piStack_78 = (int *)0x0;
  lStack_90 = lStack_70;
  piStack_88 = piStack_68;
  if (piStack_68 != (int *)0x0) {
    do {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piStack_68,0x10);
      if (bVar3) {
        *piStack_68 = *piStack_68 + 1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
  }
  uVar5 = Aska::Yayoi::HttpProtocoledData::SetCookie(Aska::TSharedPointer<Aska::Yayoi::Cookie>)(param_2,&lStack_90);
  lVar10 = lStack_90;
  if (piStack_88 == (int *)0x0) {
code_r0x0230699c:
    if (lStack_90 != 0) {
      Aska::Yayoi::Cookie::Clear()(lStack_90);
      *(undefined **)(lVar10 + 0x30) =
           PTR__ZTVN4Aska8THashMapIPKcS2_NS_5Yayoi6Cookie12StringHasherENS4_13StringEqualToENS_10TAllocatorINS_5TPairIKS2_S2_EEEEEE_02cb9918
           + 0x10;
      if (*(long *)(lVar10 + 0x50) != 0) {
        Aska::MemoryManagerAdapter::AlignedFree(void*)();
      }
      operator delete(void*)(lVar10);
    }
    if (piStack_88 != (int *)0x0) {
      Aska::TSharedPointerCode::DeleteCounter(int*)();
    }
  }
  else {
    do {
      iVar7 = *piStack_88;
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piStack_88,0x10);
      if (bVar3) {
        *piStack_88 = iVar7 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    if (iVar7 + -1 == 0) goto code_r0x0230699c;
  }
  lStack_90 = 0;
  piStack_88 = (int *)0x0;
  if (((uVar5 & 1) == 0 && (puVar16 == (undefined8 *)0x0 && *(char *)(param_1 + 0x40) == '\0')) &&
     (*(char *)(param_2 + 0x132) == '\0')) {
    lVar11 = *(long *)(param_2 + 0x140);
    lVar12 = lStack_70;
    goto joined_r0x02306c40;
  }
  lStack_98 = 0;
  iVar7 = *(int *)(param_2 + 0x7c);
  uVar8 = *(undefined8 *)
           (PTR__ZN4Aska5Yayoi18HttpProtocoledData14METHOD_STRINGSE_02cbc250 + (long)iVar7 * 8);
  if (*(char *)(param_1 + 0x1c) == '\0') {
    puVar18 = *(undefined **)PTR__ZN4Aska5Yayoi12HttpProtocol7NULLSTRE_02cbdab0;
    if (lStack_70 == 0) goto code_r0x02306a80;
code_r0x02306a50:
    puStack_f8 = (undefined8 *)Aska::Yayoi::Cookie::MakeHeader(unsigned long*)(lStack_70,&lStack_98);
    puVar20 = *(undefined8 **)PTR__ZN4Aska5Yayoi12HttpProtocol7NULLSTRE_02cbdab0;
  }
  else {
    puVar18 = &UNK_029d4248;
    if (*param_3 == 0) {
      puVar18 = &UNK_029d424e;
    }
    if (lStack_70 != 0) goto code_r0x02306a50;
code_r0x02306a80:
    puVar20 = *(undefined8 **)PTR__ZN4Aska5Yayoi12HttpProtocol7NULLSTRE_02cbdab0;
    puStack_f8 = puVar20;
  }
  uStack_a0 = 0;
  uStack_a8 = 0;
  uStack_b0 = 0;
  uStack_b8 = 0;
  uStack_c0 = 0;
  uStack_c8 = 0;
  uStack_d0 = 0;
  uStack_d8 = 0;
  uStack_e0 = 0;
  uStack_e8 = 0;
  puVar21 = puVar20;
  if (*(long *)(param_2 + 0x70) != 0) {
    iVar6 = __aska_snprintf_s(char*, unsigned long, unsigned long, char const*, ...)(&uStack_e8,0x40,0xffffffffffffffff,&UNK_029d426e,
                            *(undefined8 *)(param_2 + 0x68));
    puVar21 = &uStack_e8;
    if (iVar6 < 1) {
      puVar21 = puVar20;
    }
  }
  puVar17 = *(undefined8 **)(param_1 + 8);
  uVar9 = *(undefined8 *)(*param_4 + 0x10);
  puVar1 = puVar20;
  puVar4 = puVar20;
  if (puVar17 != (undefined8 *)0x0) {
    puVar1 = (undefined8 *)&UNK_029d4284/*"User-Agent: "*/;
    puVar4 = puVar17;
  }
  lVar10 = strlen();
  lVar11 = strlen(puVar18);
  lVar12 = strlen(puVar1);
  lVar13 = strlen(puVar21);
  if (puVar17 == (undefined8 *)0x0) {
    lVar14 = 0;
  }
  else {
    lVar14 = strlen(puVar17);
  }
  lVar10 = lVar10 + lVar11 + lVar12 + lVar13 + 6 + lVar14 + lStack_98;
  puStack_130 = puVar20;
  puStack_128 = puVar20;
  puVar17 = puVar20;
  puVar19 = puVar20;
  if (iVar7 - 3U < 2) {
    lVar12 = Aska::Yayoi::HttpProtocoledData::BuildPostHeaderString()(param_2);
    lVar11 = *(long *)PTR__ZN4Aska5Yayoi12HttpProtocol7NULLSTRE_02cbdab0;
    if (lVar12 != 0) {
      lVar11 = lVar12;
    }
    if (lVar11 == *(long *)PTR__ZN4Aska5Yayoi12HttpProtocol7NULLSTRE_02cbdab0) {
      lVar11 = 0;
    }
    else {
      iVar7 = __aska_snprintf_s(char*, unsigned long, unsigned long, char const*, ...)(&uStack_a8,0x10,0xffffffffffffffff,&UNK_029d427e,
                              *(undefined8 *)(param_2 + 0x50));
      lVar11 = (long)iVar7;
      puStack_130 = (undefined8 *)&UNK_029d4291/*"Content-Length: "*/;
      puStack_128 = (undefined8 *)&UNK_029d42a2/*"Content-Type: "*/;
      puVar17 = *(undefined8 **)
                 (PTR__ZN4Aska5Yayoi18HttpProtocoledData23CONTENT_SUBTYPE_STRINGSE_02cc0cf8 +
                 (ulong)*(uint *)(param_2 + 0x84) * 8);
      puVar19 = *(undefined8 **)
                 (PTR__ZN4Aska5Yayoi18HttpProtocoledData20CONTENT_TYPE_STRINGSE_02cbd518 +
                 (ulong)*(uint *)(param_2 + 0x80) * 8);
    }
    lVar12 = strlen(puStack_130);
    lVar13 = strlen(puStack_128);
    lVar14 = strlen(puVar19);
    lVar15 = strlen(puVar17);
    lVar10 = lVar10 + lVar11 + lVar12 + lVar13 + lVar14 + lVar15;
joined_r0x02306cb0:
    lVar10 = lVar10 + 7;
    if (puVar16 != (undefined8 *)0x0) {
      puVar20 = (undefined8 *)
                (**(code **)*puVar16)(puVar16,uVar8,*(undefined8 *)(*param_4 + 0x50),param_2);
      if (puVar20 == (undefined8 *)0x0) {
        puVar20 = *(undefined8 **)PTR__ZN4Aska5Yayoi12HttpProtocol7NULLSTRE_02cbdab0;
      }
      else {
        lVar11 = strlen(puVar20);
        lVar10 = lVar11 + lVar10;
      }
    }
  }
  else {
    if (iVar7 != 8) {
      if (iVar7 != 1) {
        lVar11 = 0;
        lVar12 = lStack_70;
        goto joined_r0x02306c40;
      }
      goto joined_r0x02306cb0;
    }
    lVar10 = lVar10 + 7;
  }
  lVar11 = Aska::Yayoi::HttpProtocoledData::AllocateHeaderCache(long)(param_2,lVar10);
  lVar12 = lStack_70;
  if (lVar11 != 0) {
    __aska_snprintf_s(char*, unsigned long, unsigned long, char const*, ...)(lVar11,lVar10,0xffffffffffffffff,&UNK_029d42b1,&UNK_029d4267/*"Host: "*/,uVar9,puVar1,puVar4
                    ,puVar18,puVar21,puStack_f8,puStack_130,&uStack_a8,puStack_128,puVar19,puVar17,
                    puVar20);
    if ((puStack_f8 != (undefined8 *)0x0) &&
       (puStack_f8 != *(undefined8 **)PTR__ZN4Aska5Yayoi12HttpProtocol7NULLSTRE_02cbdab0)) {
      operator delete[](void*)(puStack_f8);
    }
    *(undefined1 *)(param_2 + 0x132) = 0;
    *(undefined1 *)(param_1 + 0x40) = 0;
    lVar12 = lStack_70;
  }
joined_r0x02306c40:
  if (piStack_68 != (int *)0x0) {
    do {
      iVar7 = *piStack_68;
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piStack_68,0x10);
      if (bVar3) {
        *piStack_68 = iVar7 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    if (iVar7 + -1 != 0) {
      return lVar11;
    }
  }
  if (lVar12 != 0) {
    Aska::Yayoi::Cookie::Clear()(lVar12);
    *(undefined **)(lVar12 + 0x30) =
         PTR__ZTVN4Aska8THashMapIPKcS2_NS_5Yayoi6Cookie12StringHasherENS4_13StringEqualToENS_10TAllocatorINS_5TPairIKS2_S2_EEEEEE_02cb9918
         + 0x10;
    if (*(long *)(lVar12 + 0x50) != 0) {
      Aska::MemoryManagerAdapter::AlignedFree(void*)();
    }
    operator delete(void*)(lVar12);
  }
  if (piStack_68 != (int *)0x0) {
    Aska::TSharedPointerCode::DeleteCounter(int*)();
  }
  return lVar11;
}

// ==== Aska::Yayoi::HttpProtocol::MakePostHeader(Aska::Yayoi::HttpProtocoledData*)
// vaddr 0x2206e00 | ghidra 0x2306e00 | size 40 | symbol _ZN4Aska5Yayoi12HttpProtocol14MakePostHeaderEPNS0_18HttpProtocoledDataE | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska5Yayoi12HttpProtocol14MakePostHeaderEPNS0_18HttpProtocoledDataE
               (undefined8 param_1,undefined8 param_2)

{
  long lVar1;
  long lVar2;
  
  lVar2 = Aska::Yayoi::HttpProtocoledData::BuildPostHeaderString()(param_2);
  lVar1 = *(long *)PTR__ZN4Aska5Yayoi12HttpProtocol7NULLSTRE_02cbdab0;
  if (lVar2 != 0) {
    lVar1 = lVar2;
  }
  return lVar1;
}

// ==== Aska::Yayoi::HttpProtocol::Open(Aska::Yayoi::Socket*, Aska::Yayoi::IPAddress const&, Aska::TSharedPointer<Aska::Yayoi::URI>)
// vaddr 0x2206e28 | ghidra 0x2306e28 | size 416 | symbol _ZN4Aska5Yayoi12HttpProtocol4OpenEPNS0_6SocketERKNS0_9IPAddressENS_14TSharedPointerINS0_3URIEEE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi12HttpProtocol4OpenEPNS0_6SocketERKNS0_9IPAddressENS_14TSharedPointerINS0_3URIEEE
               (undefined8 *param_1,long param_2,undefined8 param_3,int *param_4,long *param_5)

{
  undefined *puVar1;
  ulong uVar2;
  int iVar3;
  char cVar4;
  bool bVar5;
  long *plVar6;
  undefined1 *puVar7;
  undefined8 uVar8;
  int *piVar9;
  undefined1 *puVar10;
  ulong uVar12;
  ulong uVar13;
  long lVar14;
  undefined1 *puVar11;
  
  if (*param_4 == 0) {
    uVar8 = 0xfffffffffffffc21;
    goto code_r0x02306f3c;
  }
  if (*(long *)(param_2 + 0x38) == 0) {
    plVar6 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x30,PTR__ZSt7nothrow_02cb9a80);
    if (plVar6 != (long *)0x0) {
      puVar1 = PTR__ZTVN4Aska8THashMapIPKcS2_NS_7THasherIS2_EENS_8TEqualToIS2_EENS_10TAllocatorINS_5TPairIKS2_S2_EEEEEE_02cbbae8
               + 0x10;
      *(undefined8 *)((long)plVar6 + 0xc) = 0x3f400000;
      *plVar6 = (long)puVar1;
      *(undefined4 *)((long)plVar6 + 0x14) = 0;
      puVar7 = (undefined1 *)Aska::MemoryManagerAdapter::AlignedMalloc(unsigned long, unsigned long)(0x198,8);
      lVar14 = 0x11;
      if (puVar7 == (undefined1 *)0x0) {
        lVar14 = 0;
      }
      plVar6[4] = (long)puVar7;
      plVar6[5] = lVar14;
      if (puVar7 != (undefined1 *)0x0) {
        uVar2 = (lVar14 * 0x18 - 0x18U) / 0x18 + 1;
        puVar11 = puVar7;
        if ((1 < uVar2) && (uVar12 = uVar2 & 0x1ffffffffffffffe, uVar12 != 0)) {
          uVar13 = uVar12;
          do {
            *puVar11 = 0;
            puVar11[0x18] = 0;
            uVar13 = uVar13 - 2;
            puVar11 = puVar11 + 0x30;
          } while (uVar13 != 0);
          puVar11 = puVar7 + uVar12 * 0x18;
          if (uVar2 == uVar12) goto code_r0x02306f28;
        }
        do {
          puVar10 = puVar11 + 0x18;
          *puVar11 = 0;
          puVar11 = puVar10;
        } while (puVar7 + lVar14 * 0x18 != puVar10);
      }
    }
code_r0x02306f28:
    *(long **)(param_2 + 0x38) = plVar6;
  }
  plVar6 = (long *)(param_2 + 0x20);
  if ((*plVar6 == 0) && (*param_5 != 0)) {
    piVar9 = *(int **)(param_2 + 0x28);
    lVar14 = 0;
    if (piVar9 == (int *)0x0) {
code_r0x02306f7c:
      if (lVar14 != 0) {
        Aska::Yayoi::URI::DeleteBuffer()(lVar14);
        operator delete(void*)(lVar14);
      }
      if (*(long *)(param_2 + 0x28) != 0) {
        Aska::TSharedPointerCode::DeleteCounter(int*)();
      }
    }
    else {
      do {
        iVar3 = *piVar9;
        cVar4 = '\x01';
        bVar5 = (bool)ExclusiveMonitorPass(piVar9,0x10);
        if (bVar5) {
          *piVar9 = iVar3 + -1;
          cVar4 = ExclusiveMonitorsStatus();
        }
      } while (cVar4 != '\0');
      if (iVar3 + -1 == 0) {
        lVar14 = *plVar6;
        goto code_r0x02306f7c;
      }
    }
    *plVar6 = 0;
    *(undefined8 *)(param_2 + 0x28) = 0;
    piVar9 = (int *)param_5[1];
    *(int **)(param_2 + 0x28) = piVar9;
    *(long *)(param_2 + 0x20) = *param_5;
    uVar8 = 0;
    if (piVar9 == (int *)0x0) goto code_r0x02306f3c;
    do {
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar9,0x10);
      if (bVar5) {
        *piVar9 = *piVar9 + 1;
        cVar4 = ExclusiveMonitorsStatus();
      }
    } while (cVar4 != '\0');
  }
  uVar8 = 0;
code_r0x02306f3c:
  *param_1 = uVar8;
  return;
}

// ==== Aska::Yayoi::HttpProtocol::SerializeResponse(Aska::Yayoi::HttpProtocoledData*, signed char**, unsigned long, void const*, unsigned long, unsigned long*)
// vaddr 0x2206fc8 | ghidra 0x2306fc8 | size 196 | symbol _ZN4Aska5Yayoi12HttpProtocol17SerializeResponseEPNS0_18HttpProtocoledDataEPPamPKvmPm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi12HttpProtocol17SerializeResponseEPNS0_18HttpProtocoledDataEPPamPKvmPm
               (undefined8 *param_1,undefined8 param_2,long param_3,long *param_4,undefined8 param_5
               ,undefined8 param_6,long param_7,long *param_8)

{
  int iVar1;
  ulong uVar2;
  long lVar3;
  undefined8 uVar4;
  
  if (param_7 != 0) {
    uVar2 = Aska::Yayoi::HttpProtocoledData::SetContent(signed char*, unsigned long, bool)(param_3,param_6,param_7,0);
    if ((uVar2 & 1) == 0) {
      uVar4 = 0xfffffffffffffc12;
      goto code_r0x02307074;
    }
    *(undefined4 *)(param_3 + 0x7c) = 3;
  }
  lVar3 = *(long *)(param_3 + 0x50);
  uVar4 = *(undefined8 *)(param_3 + 0x28);
  iVar1 = __aska_snprintf_s(char*, unsigned long, unsigned long, char const*, ...)(*param_4,param_5,0xffffffffffffffff,&UNK_029d42ce,lVar3);
  *param_8 = (long)iVar1;
  if (lVar3 == 0) {
    uVar4 = 0;
  }
  else {
    memcpy(*param_4 + (long)iVar1,uVar4,lVar3);
    uVar4 = 0;
    *param_8 = *param_8 + lVar3;
  }
code_r0x02307074:
  *param_1 = uVar4;
  return;
}

// ==== Aska::Yayoi::HttpProtocol::Serialize(Aska::Yayoi::HttpProtocoledData*, signed char**, unsigned long, void const*, unsigned long, unsigned long*)
// vaddr 0x220708c | ghidra 0x230708c | size 1180 | symbol _ZN4Aska5Yayoi12HttpProtocol9SerializeEPNS0_18HttpProtocoledDataEPPamPKvmPm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi12HttpProtocol9SerializeEPNS0_18HttpProtocoledDataEPPamPKvmPm
               (undefined8 *param_1,long param_2,long param_3,long *param_4,ulong param_5,
               undefined8 param_6,long param_7,long *param_8)

{
  undefined8 *puVar1;
  int iVar2;
  int *piVar3;
  char cVar4;
  bool bVar5;
  int iVar6;
  ulong uVar7;
  undefined *puVar8;
  long lVar9;
  long lVar10;
  long lVar11;
  long lVar12;
  long lVar13;
  undefined8 uVar14;
  long lVar15;
  long lVar16;
  undefined1 *puVar17;
  undefined *puVar18;
  undefined1 *puStack_b8;
  long lStack_a8;
  long lStack_88;
  int *piStack_80;
  long lStack_78;
  int *piStack_70;
  long lStack_68;
  
  if (*(int *)(param_2 + 0x18) == 0) {
    if (param_7 != 0) {
      uVar7 = Aska::Yayoi::HttpProtocoledData::SetContent(signed char*, unsigned long, bool)(param_3,param_6,param_7,0);
      if ((uVar7 & 1) == 0) goto code_r0x02307200;
      *(undefined4 *)(param_3 + 0x7c) = 3;
    }
    lVar15 = *(long *)(param_3 + 0x50);
    uVar14 = *(undefined8 *)(param_3 + 0x28);
    iVar6 = __aska_snprintf_s(char*, unsigned long, unsigned long, char const*, ...)(*param_4,param_5,0xffffffffffffffff,&UNK_029d42ce,lVar15);
    *param_8 = (long)iVar6;
    if (lVar15 != 0) {
      memcpy(*param_4 + (long)iVar6,uVar14,lVar15);
      *param_8 = *param_8 + lVar15;
      *param_1 = 0;
      return;
    }
    *param_1 = 0;
    return;
  }
  if (param_7 != 0) {
    uVar7 = Aska::Yayoi::HttpProtocoledData::SetContent(signed char*, unsigned long, bool)(param_3,param_6,param_7,0);
    if ((uVar7 & 1) == 0) {
code_r0x02307200:
      *param_1 = 0xfffffffffffffc12;
      return;
    }
    *(undefined4 *)(param_3 + 0x84) = 9;
    *(undefined8 *)(param_3 + 0x7c) = 0x200000003;
  }
  lStack_88 = *(long *)(param_3 + 0x90);
  piVar3 = *(int **)(param_3 + 0x98);
  if (piVar3 != (int *)0x0) {
    do {
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar3,0x10);
      if (bVar5) {
        *piVar3 = *piVar3 + 1;
        cVar4 = ExclusiveMonitorsStatus();
      }
    } while (cVar4 != '\0');
  }
  iVar6 = *(int *)(param_3 + 0x7c);
  lStack_78 = *(long *)(param_2 + 0x20);
  lStack_a8 = *(long *)PTR__ZN4Aska5Yayoi12HttpProtocol7NULLSTRE_02cbdab0;
  piStack_70 = *(int **)(param_2 + 0x28);
  uVar14 = *(undefined8 *)
            (PTR__ZN4Aska5Yayoi18HttpProtocoledData14METHOD_STRINGSE_02cbc250 + (long)iVar6 * 8);
  if (piStack_70 != (int *)0x0) {
    do {
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piStack_70,0x10);
      if (bVar5) {
        *piStack_70 = *piStack_70 + 1;
        cVar4 = ExclusiveMonitorsStatus();
      }
    } while (cVar4 != '\0');
  }
  if (piVar3 != (int *)0x0) {
    do {
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar3,0x10);
      if (bVar5) {
        *piVar3 = *piVar3 + 1;
        cVar4 = ExclusiveMonitorsStatus();
      }
    } while (cVar4 != '\0');
  }
  piStack_80 = piVar3;
  lStack_68 = lStack_88;
  puVar8 = (undefined *)Aska::Yayoi::HttpProtocol::MakeHeader(Aska::Yayoi::HttpProtocoledData*, Aska::TSharedPointer<Aska::Yayoi::URI>, Aska::TSharedPointer<Aska::Yayoi::URI>)(param_2,param_3,&lStack_78,&lStack_88);
  lVar15 = lStack_88;
  if (piVar3 == (int *)0x0) {
code_r0x02307240:
    if (lStack_88 != 0) {
      Aska::Yayoi::URI::DeleteBuffer()(lStack_88);
      operator delete(void*)(lVar15);
    }
    if (piStack_80 != (int *)0x0) {
      Aska::TSharedPointerCode::DeleteCounter(int*)();
    }
  }
  else {
    do {
      iVar2 = *piVar3;
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar3,0x10);
      if (bVar5) {
        *piVar3 = iVar2 + -1;
        cVar4 = ExclusiveMonitorsStatus();
      }
    } while (cVar4 != '\0');
    if (iVar2 + -1 == 0) goto code_r0x02307240;
  }
  lVar15 = lStack_78;
  lStack_88 = 0;
  piStack_80 = (int *)0x0;
  if (piStack_70 == (int *)0x0) {
code_r0x02307284:
    if (lStack_78 != 0) {
      Aska::Yayoi::URI::DeleteBuffer()(lStack_78);
      operator delete(void*)(lVar15);
    }
    if (piStack_70 != (int *)0x0) {
      Aska::TSharedPointerCode::DeleteCounter(int*)();
    }
  }
  else {
    do {
      iVar2 = *piStack_70;
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piStack_70,0x10);
      if (bVar5) {
        *piStack_70 = iVar2 + -1;
        cVar4 = ExclusiveMonitorsStatus();
      }
    } while (cVar4 != '\0');
    if (iVar2 + -1 == 0) goto code_r0x02307284;
  }
  lVar15 = lStack_68;
  lStack_78 = 0;
  piStack_70 = (int *)0x0;
  puVar1 = (undefined8 *)(lStack_68 + 0x50);
  if (*(long *)(param_2 + 0x20) == 0) {
    puVar1 = (undefined8 *)(lStack_68 + 0x20);
  }
  puVar17 = *(undefined1 **)PTR__ZN4Aska5Yayoi12HttpProtocol7NULLSTRE_02cbdab0;
  puVar18 = &UNK_029c5d3e/*"/"*/;
  if ((undefined *)*puVar1 != (undefined *)0x0) {
    puVar18 = (undefined *)*puVar1;
  }
  if (iVar6 == 8) {
    puStack_b8 = (undefined1 *)0x0;
    lVar9 = 0;
    puVar8 = &UNK_029d4332;
    puVar18 = &UNK_0296e979/*"*"*/;
  }
  else if (iVar6 == 3) {
    lVar10 = Aska::Yayoi::HttpProtocoledData::BuildPostHeaderString()(param_3);
    puStack_b8 = (undefined1 *)0x0;
    lVar9 = *(long *)(param_3 + 0x50);
    lStack_a8 = *(long *)PTR__ZN4Aska5Yayoi12HttpProtocol7NULLSTRE_02cbdab0;
    if (lVar10 != 0) {
      lStack_a8 = lVar10;
    }
  }
  else {
    if (iVar6 != 1) {
      *param_1 = 0xffffffffffffffff;
      goto joined_r0x023074cc;
    }
    lVar9 = Aska::Yayoi::HttpProtocoledData::MakeParamString(char*, unsigned long)(param_3,0,0);
    uVar7 = lVar9 + 1;
    if (uVar7 < 2) {
      puStack_b8 = (undefined1 *)0x0;
      lVar9 = 0;
    }
    else {
      lVar9 = **(long **)PTR__ZN4Aska6Global19m_pNetworkAllocatorE_02cbc200;
      if (lVar9 == 0) {
        lVar9 = Aska::Global::GetAvailableMemoryManager()();
      }
      puVar17 = (undefined1 *)Aska::MemoryManager::Malloc(unsigned long)(lVar9,uVar7);
      *puVar17 = 0x3f;
      Aska::Yayoi::HttpProtocoledData::MakeParamString(char*, unsigned long)(param_3,puVar17 + 1,uVar7);
      lVar9 = 0;
      puStack_b8 = puVar17;
    }
  }
  lVar16 = *(long *)PTR__ZN4Aska5Yayoi18HttpProtocoledData21METHOD_FORMATTER_SIZEE_02cb7a18;
  lVar10 = strlen(uVar14);
  lVar11 = strlen(puVar18);
  lVar12 = strlen(puVar17);
  lVar13 = strlen(puVar8);
  uVar7 = lVar9 + lVar16 + lVar10 + lVar11 + lVar12 + lVar13 + 1;
  if (param_5 < uVar7) {
    *param_1 = 0xfffffffffffffc41;
  }
  else {
    iVar6 = __aska_snprintf_s(char*, unsigned long, unsigned long, char const*, ...)(*param_4,uVar7,0xffffffffffffffff,
                            PTR__ZN4Aska5Yayoi18HttpProtocoledData16METHOD_FORMATTERE_02cc18c8,
                            uVar14,puVar18,puVar17,puVar8);
    lVar10 = (long)iVar6;
    if (lVar9 != 0) {
      memcpy(*param_4 + lVar10,lStack_a8,lVar9);
      lVar10 = lVar9 + lVar10;
    }
    if (puStack_b8 != (undefined1 *)0x0) {
      operator delete[](void*)();
    }
    *param_8 = lVar10;
    *param_1 = 0;
  }
joined_r0x023074cc:
  if (piVar3 != (int *)0x0) {
    do {
      iVar6 = *piVar3;
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar3,0x10);
      if (bVar5) {
        *piVar3 = iVar6 + -1;
        cVar4 = ExclusiveMonitorsStatus();
      }
    } while (cVar4 != '\0');
    lVar15 = lStack_68;
    if (iVar6 + -1 != 0) {
      return;
    }
  }
  if (lVar15 != 0) {
    Aska::Yayoi::URI::DeleteBuffer()(lVar15);
    operator delete(void*)(lVar15);
  }
  if (piVar3 != (int *)0x0) {
    Aska::TSharedPointerCode::DeleteCounter(int*)(piVar3);
  }
  return;
}

// ==== Aska::Yayoi::HttpProtocol::SetEnableField(Aska::Yayoi::HttpProtocol::EnableFields, bool)
// vaddr 0x2207528 | ghidra 0x2307528 | size 36 | symbol _ZN4Aska5Yayoi12HttpProtocol14SetEnableFieldENS1_12EnableFieldsEb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi12HttpProtocol14SetEnableFieldENS1_12EnableFieldsEb
               (long param_1,uint param_2,uint param_3)

{
  if ((param_3 & 1) != 0) {
    *(uint *)(param_1 + 4) = *(uint *)(param_1 + 4) | param_2;
    return;
  }
  *(uint *)(param_1 + 4) = *(uint *)(param_1 + 4) & (param_2 ^ 0xffffffff);
  return;
}

// ==== Aska::Yayoi::HttpProtocol::SetEnableOtherField(char const*, bool)
// vaddr 0x220754c | ghidra 0x230754c | size 444 | symbol _ZN4Aska5Yayoi12HttpProtocol19SetEnableOtherFieldEPKcb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi12HttpProtocol19SetEnableOtherFieldEPKcb(long param_1,ulong param_2,uint param_3)

{
  undefined *puVar1;
  ulong uVar2;
  char cVar3;
  ulong uVar4;
  undefined8 *puVar5;
  undefined1 *puVar6;
  ulong uVar7;
  undefined1 *puVar8;
  ulong uVar10;
  ulong uVar11;
  char *pcVar12;
  long lVar13;
  long *plVar14;
  ulong uStack_28;
  undefined1 *puVar9;
  
  plVar14 = *(long **)(param_1 + 0x38);
  uStack_28 = param_2;
  if (plVar14 != (long *)0x0) goto joined_r0x02307658;
  plVar14 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x30,PTR__ZSt7nothrow_02cb9a80);
  if (plVar14 != (long *)0x0) {
    puVar1 = PTR__ZTVN4Aska8THashMapIPKcS2_NS_7THasherIS2_EENS_8TEqualToIS2_EENS_10TAllocatorINS_5TPairIKS2_S2_EEEEEE_02cbbae8
             + 0x10;
    *(undefined8 *)((long)plVar14 + 0xc) = 0x3f400000;
    *plVar14 = (long)puVar1;
    *(undefined4 *)((long)plVar14 + 0x14) = 0;
    puVar6 = (undefined1 *)Aska::MemoryManagerAdapter::AlignedMalloc(unsigned long, unsigned long)(0x198,8);
    lVar13 = 0x11;
    if (puVar6 == (undefined1 *)0x0) {
      lVar13 = 0;
    }
    plVar14[4] = (long)puVar6;
    plVar14[5] = lVar13;
    if (puVar6 != (undefined1 *)0x0) {
      uVar7 = (lVar13 * 0x18 - 0x18U) / 0x18 + 1;
      puVar9 = puVar6;
      if ((1 < uVar7) && (uVar10 = uVar7 & 0x1ffffffffffffffe, uVar10 != 0)) {
        uVar11 = uVar10;
        do {
          *puVar9 = 0;
          puVar9[0x18] = 0;
          uVar11 = uVar11 - 2;
          puVar9 = puVar9 + 0x30;
        } while (uVar11 != 0);
        puVar9 = puVar6 + uVar10 * 0x18;
        if (uVar7 == uVar10) goto code_r0x02307654;
      }
      do {
        puVar8 = puVar9 + 0x18;
        *puVar9 = 0;
        puVar9 = puVar8;
      } while (puVar6 + lVar13 * 0x18 != puVar8);
    }
  }
code_r0x02307654:
  *(long **)(param_1 + 0x38) = plVar14;
joined_r0x02307658:
  if ((param_3 & 1) == 0) {
    uVar7 = plVar14[5];
    if (uVar7 != 0) {
      uVar10 = ~uStack_28 + uStack_28 * 0x200000;
      uVar10 = (uVar10 ^ uVar10 >> 0x18) * 0x109;
      uVar11 = (uVar10 ^ uVar10 >> 0xe) * 0x15;
      uVar10 = 0;
      do {
        uVar2 = (uVar11 ^ uVar11 >> 0x1c) * 0x80000001 + uVar10;
        uVar4 = 0;
        if (uVar7 != 0) {
          uVar4 = uVar2 / uVar7;
        }
        lVar13 = uVar2 - uVar4 * uVar7;
        pcVar12 = (char *)(plVar14[4] + lVar13 * 0x18);
        cVar3 = *pcVar12;
        if (cVar3 == '\x01') {
          if (*(ulong *)(plVar14[4] + lVar13 * 0x18 + 8) == uStack_28) {
            *(int *)(plVar14 + 2) = (int)plVar14[2] + -1;
            *(int *)((long)plVar14 + 0x14) = *(int *)((long)plVar14 + 0x14) + 1;
            *pcVar12 = '\x02';
            return;
          }
        }
        else if (cVar3 == '\0') {
          return;
        }
        uVar10 = uVar10 + 1;
      } while (uVar10 < uVar7);
    }
  }
  else {
    puVar5 = (undefined8 *)Aska::THashMap<char const*, char const*, Aska::THasher<char const*>, Aska::TEqualTo<char const*>, Aska::TAllocator<Aska::TPair<char const* const, char const*> > >::operator[](char const* const&)(plVar14,&uStack_28);
    *puVar5 = 0;
  }
  return;
}

// ==== Aska::Yayoi::HttpProtocol::ParseHeader(signed char const*, unsigned long, Aska::Yayoi::HttpProtocoledData*, Aska::TSharedPointer<Aska::Yayoi::URI>)
// vaddr 0x2207848 | ghidra 0x2307848 | size 652 | symbol _ZN4Aska5Yayoi12HttpProtocol11ParseHeaderEPKamPNS0_18HttpProtocoledDataENS_14TSharedPointerINS0_3URIEEE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi12HttpProtocol11ParseHeaderEPKamPNS0_18HttpProtocoledDataENS_14TSharedPointerINS0_3URIEEE
               (undefined8 param_1,undefined8 param_2,undefined8 param_3,long param_4,long *param_5)

{
  int iVar1;
  int *piVar2;
  char cVar3;
  bool bVar4;
  long lVar5;
  undefined8 *puVar6;
  int *piVar7;
  undefined1 auStack_68 [8];
  long lStack_60;
  long lStack_58;
  
  if (param_4 == 0) {
    return;
  }
  *(undefined4 *)(param_4 + 0x150) = 2;
  if (*(long *)(param_4 + 0x38) == 0) {
    lVar5 = **(long **)PTR__ZN4Aska6Global19m_pNetworkAllocatorE_02cbc200;
    if (lVar5 == 0) {
      lVar5 = Aska::Global::GetAvailableMemoryManager()();
    }
    puVar6 = (undefined8 *)Aska::MemoryManager::Malloc(unsigned long)(lVar5,0x58);
    *(undefined8 **)(param_4 + 0x38) = puVar6;
    if (puVar6 != (undefined8 *)0x0) {
      *(undefined2 *)(puVar6 + 10) = 0;
      puVar6[4] = 0;
      puVar6[5] = 0;
      puVar6[2] = 0;
      puVar6[3] = 0;
      *puVar6 = 0;
      puVar6[1] = 0;
    }
  }
  lVar5 = *(long *)(param_4 + 0x90);
  piVar2 = *(int **)(param_4 + 0x98);
  if (piVar2 == (int *)0x0) {
joined_r0x02307910:
    if (lVar5 != 0) {
      Aska::Yayoi::URI::DeleteBuffer()(lVar5);
      operator delete(void*)(lVar5);
    }
    if (piVar2 != (int *)0x0) {
      Aska::TSharedPointerCode::DeleteCounter(int*)(piVar2);
    }
  }
  else {
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
      if (bVar4) {
        *piVar2 = *piVar2 + 1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
    do {
      iVar1 = *piVar2;
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
      if (bVar4) {
        *piVar2 = iVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
    if (iVar1 + -1 == 0) goto joined_r0x02307910;
  }
  if (lVar5 == 0) {
    lStack_58 = *param_5;
    piVar2 = (int *)param_5[1];
    if (piVar2 != (int *)0x0) {
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
        if (bVar4) {
          *piVar2 = *piVar2 + 1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
    }
    lVar5 = *(long *)(param_4 + 0x90);
    if (lStack_58 == lVar5) {
      if (piVar2 != (int *)0x0) goto code_r0x023079e0;
code_r0x023079f4:
      lVar5 = lStack_58;
      if (lStack_58 != 0) {
        Aska::Yayoi::URI::DeleteBuffer()(lStack_58);
        operator delete(void*)(lVar5);
      }
      if (piVar2 != (int *)0x0) {
        Aska::TSharedPointerCode::DeleteCounter(int*)(piVar2);
      }
    }
    else {
      piVar7 = *(int **)(param_4 + 0x98);
      if (piVar7 == (int *)0x0) {
code_r0x0230799c:
        if (lVar5 != 0) {
          Aska::Yayoi::URI::DeleteBuffer()(lVar5);
          operator delete(void*)(lVar5);
        }
        if (*(long *)(param_4 + 0x98) != 0) {
          Aska::TSharedPointerCode::DeleteCounter(int*)();
        }
      }
      else {
        do {
          iVar1 = *piVar7;
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar7,0x10);
          if (bVar4) {
            *piVar7 = iVar1 + -1;
            cVar3 = ExclusiveMonitorsStatus();
          }
        } while (cVar3 != '\0');
        if (iVar1 + -1 == 0) {
          lVar5 = *(long *)(param_4 + 0x90);
          goto code_r0x0230799c;
        }
      }
      *(long *)(param_4 + 0x90) = lStack_58;
      *(int **)(param_4 + 0x98) = piVar2;
      if (piVar2 == (int *)0x0) goto code_r0x023079f4;
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
        if (bVar4) {
          *piVar2 = *piVar2 + 1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
code_r0x023079e0:
      do {
        iVar1 = *piVar2;
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
        if (bVar4) {
          *piVar2 = iVar1 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      if (iVar1 + -1 == 0) goto code_r0x023079f4;
    }
    lStack_58 = 0;
  }
  lVar5 = *(long *)(param_4 + 0x90);
  piVar2 = *(int **)(param_4 + 0x98);
  if (piVar2 != (int *)0x0) {
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
      if (bVar4) {
        *piVar2 = *piVar2 + 1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
    do {
      iVar1 = *piVar2;
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
      if (bVar4) {
        *piVar2 = iVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
    if (iVar1 + -1 != 0) goto joined_r0x02307a90;
  }
  lStack_60 = lVar5;
  if (lVar5 != 0) {
    Aska::Yayoi::URI::DeleteBuffer()(lVar5);
    operator delete(void*)(lVar5);
  }
  if (piVar2 != (int *)0x0) {
    Aska::TSharedPointerCode::DeleteCounter(int*)(piVar2);
  }
joined_r0x02307a90:
  if (lVar5 != 0) {
    lStack_60 = 0;
    Aska::Yayoi::HttpProtocol::Deserialize(signed char const*, unsigned long, unsigned long*, Aska::Yayoi::HttpProtocoledData*, Aska::Status&)(param_1,param_2,param_3,auStack_68,param_4);
  }
  return;
}

// ==== Aska::Yayoi::HttpProtocol::Deserialize(signed char const*, unsigned long, unsigned long*, Aska::Yayoi::HttpProtocoledData*, Aska::Status&)
// vaddr 0x2207ad4 | ghidra 0x2307ad4 | size 1616 | symbol _ZN4Aska5Yayoi12HttpProtocol11DeserializeEPKamPmPNS0_18HttpProtocoledDataERNS_6StatusE | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska5Yayoi12HttpProtocol11DeserializeEPKamPmPNS0_18HttpProtocoledDataERNS_6StatusE
               (long param_1,char *param_2,ulong param_3,long *param_4,long param_5)

{
  uint uVar1;
  char cVar2;
  double dVar3;
  bool bVar4;
  bool bVar5;
  bool bVar6;
  undefined *puVar7;
  int iVar8;
  undefined4 uVar9;
  long lVar10;
  undefined8 *puVar11;
  undefined8 uVar12;
  long lVar13;
  ulong uVar14;
  ulong uVar15;
  long *plVar16;
  uint uVar17;
  char *pcVar18;
  ulong uVar19;
  uint uVar20;
  char cStack_f4;
  char cStack_f3;
  char cStack_f2;
  undefined1 uStack_f1;
  char acStack_f0 [128];
  char acStack_70 [16];
  
  if (*(long *)(param_5 + 0x38) == 0) {
    lVar10 = **(long **)PTR__ZN4Aska6Global19m_pNetworkAllocatorE_02cbc200;
    if (lVar10 == 0) {
      lVar10 = Aska::Global::GetAvailableMemoryManager()();
    }
    puVar11 = (undefined8 *)Aska::MemoryManager::Malloc(unsigned long)(lVar10,0x58);
    *(undefined8 **)(param_5 + 0x38) = puVar11;
    if (puVar11 != (undefined8 *)0x0) {
      *(undefined2 *)(puVar11 + 10) = 0;
      puVar11[4] = 0;
      puVar11[5] = 0;
      puVar11[2] = 0;
      puVar11[3] = 0;
      *puVar11 = 0;
      puVar11[1] = 0;
    }
    *(uint *)(param_5 + 0x150) = (uint)(*(int *)(param_1 + 0x18) != 0);
  }
  *(undefined1 *)(param_5 + 0x11) = 1;
  if (param_3 == 0) {
    lVar10 = *(long *)(param_5 + 0x50);
    if (lVar10 == 0) {
      lVar10 = *(long *)(*(long *)(param_5 + 0x38) + 0x18);
      *(long *)(param_5 + 0x50) = lVar10;
    }
    *(bool *)(param_5 + 0x11) = lVar10 == *(long *)(*(long *)(param_5 + 0x38) + 0x18);
    return param_5;
  }
  plVar16 = *(long **)(param_5 + 0x38);
  acStack_70[8] = '\0';
  acStack_70[9] = '\0';
  acStack_70[0] = '\0';
  acStack_70[1] = '\0';
  acStack_70[2] = '\0';
  acStack_70[3] = '\0';
  acStack_70[4] = '\0';
  acStack_70[5] = '\0';
  acStack_70[6] = '\0';
  acStack_70[7] = '\0';
  memset(acStack_f0,0,0x80);
  puVar7 = PTR__ZN4Aska5Yayoi18HttpProtocoledData14METHOD_STRINGSE_02cbc250;
  bVar6 = false;
  bVar5 = false;
  bVar4 = false;
  uVar19 = 0;
  uVar14 = 0;
  uVar20 = 0;
  uVar17 = 0;
  pcVar18 = param_2;
code_r0x02307bbc:
  switch(*(undefined4 *)(param_5 + 0x150)) {
  case 0:
    if (*(int *)(param_5 + 0x7c) == -1) {
      uVar15 = 0;
      do {
        if (pcVar18[uVar15] == ' ') {
          uVar12 = *(undefined8 *)puVar7;
          lVar10 = (ulong)(uVar20 & 0xff) - 1;
          acStack_70[uVar20 & 0xff] = '\0';
          iVar8 = strncmp(uVar12,acStack_70,lVar10);
          if (iVar8 == 0) {
            uVar9 = 0;
            goto code_r0x02308010;
          }
          iVar8 = strncmp(*(undefined8 *)(puVar7 + 8),acStack_70,lVar10);
          if (iVar8 == 0) {
            uVar9 = 1;
            goto code_r0x02308010;
          }
          iVar8 = strncmp(*(undefined8 *)(puVar7 + 0x10),acStack_70,lVar10);
          if (iVar8 == 0) {
            uVar9 = 2;
            goto code_r0x02308010;
          }
          iVar8 = strncmp(*(undefined8 *)(puVar7 + 0x18),acStack_70,lVar10);
          if (iVar8 == 0) {
            uVar9 = 3;
            goto code_r0x02308010;
          }
          iVar8 = strncmp(*(undefined8 *)(puVar7 + 0x20),acStack_70,lVar10);
          if (iVar8 == 0) {
            uVar9 = 4;
            goto code_r0x02308010;
          }
          iVar8 = strncmp(*(undefined8 *)(puVar7 + 0x28),acStack_70,lVar10);
          if (iVar8 == 0) {
            uVar9 = 5;
            goto code_r0x02308010;
          }
          iVar8 = strncmp(*(undefined8 *)(puVar7 + 0x30),acStack_70,lVar10);
          if (iVar8 == 0) {
            uVar9 = 6;
            goto code_r0x02308010;
          }
          iVar8 = strncmp(*(undefined8 *)(puVar7 + 0x38),acStack_70,lVar10);
          if (iVar8 == 0) {
            uVar9 = 7;
            goto code_r0x02308010;
          }
          iVar8 = strncmp(*(undefined8 *)(puVar7 + 0x40),acStack_70,lVar10);
          if (iVar8 == 0) goto code_r0x0230800c;
        }
        else {
          uVar1 = uVar20 & 0xff;
          uVar20 = uVar20 + 1;
          acStack_70[uVar1] = pcVar18[uVar15];
        }
        uVar15 = uVar15 + 1;
        if (param_3 <= uVar15) {
          return 0;
        }
      } while( true );
    }
    if (bVar4) {
      iVar8 = strncmp(&UNK_029d4381/*"HTTP/"*/,pcVar18,5);
      if (iVar8 != 0) {
        return 0;
      }
      cStack_f4 = pcVar18[5];
      cStack_f3 = pcVar18[6];
      cStack_f2 = pcVar18[7];
      uStack_f1 = 0;
      dVar3 = (double)atof(&cStack_f4);
      uVar14 = uVar19 + 9;
      *(undefined4 *)(param_5 + 0x150) = 2;
      pcVar18 = pcVar18 + 9;
      *(float *)(param_5 + 0x78) = (float)dVar3;
      bVar4 = true;
      uVar19 = uVar14;
    }
    else {
      uVar15 = (long)pcVar18 - (long)param_2;
      if (uVar15 < param_3) {
        do {
          cVar2 = *pcVar18;
          if (cVar2 == ' ') {
            acStack_f0[uVar17 & 0xff] = '\0';
            lVar10 = (ulong)(uVar17 & 0xff) + 1;
            lVar13 = **(long **)PTR__ZN4Aska6Global19m_pNetworkAllocatorE_02cbc200;
            if (lVar13 == 0) {
              lVar13 = Aska::Global::GetAvailableMemoryManager()();
            }
            lVar13 = Aska::MemoryManager::Malloc(unsigned long)(lVar13,lVar10);
            *(long *)(param_5 + 0x20) = lVar13;
            if (lVar13 == 0) {
              return 0;
            }
            memcpy(lVar13,acStack_f0,lVar10);
            bVar4 = true;
            uVar14 = uVar19;
            goto code_r0x02308028;
          }
          uVar1 = uVar17 + 1;
          uVar15 = uVar15 + 1;
          pcVar18 = pcVar18 + 1;
          uVar19 = uVar19 + 1;
          acStack_f0[uVar17 & 0xff] = cVar2;
          uVar17 = uVar1;
        } while (uVar15 < param_3);
        bVar4 = false;
      }
      else {
        bVar4 = false;
      }
    }
    break;
  case 1:
    cVar2 = *pcVar18;
    if (cVar2 == '\r') {
      if (pcVar18[1] == '\n') {
        uVar14 = uVar19 + 1;
        *(undefined4 *)(param_5 + 0x150) = 2;
        pcVar18 = pcVar18 + 1;
        uVar19 = uVar14;
      }
    }
    else if (cVar2 == '/') {
      cStack_f4 = pcVar18[1];
      cStack_f3 = pcVar18[2];
      cStack_f2 = pcVar18[3];
      uStack_f1 = 0;
      dVar3 = (double)atof(&cStack_f4);
      *(float *)(param_5 + 0x78) = (float)dVar3;
      uVar14 = uVar19;
    }
    else if ((cVar2 == ' ') && ((char)plVar16[10] == '\0')) {
      cStack_f4 = pcVar18[1];
      cStack_f3 = pcVar18[2];
      cStack_f2 = pcVar18[3];
      uStack_f1 = 0;
      uVar9 = atoi(&cStack_f4);
      *(undefined4 *)(param_5 + 0x8c) = uVar9;
      *(undefined1 *)(plVar16 + 10) = 1;
      uVar14 = uVar19;
    }
    break;
  case 2:
    cVar2 = *pcVar18;
    if (cVar2 < ' ') {
      if (cVar2 == '\n') {
        if (((bVar5) || (plVar16[5] == 0)) || (*(char *)(plVar16[5] + plVar16[2] + -1) == '\r')) {
          if (*(char *)((long)plVar16 + 0x51) == '\0') {
            *(undefined4 *)(param_5 + 0x150) = 3;
          }
          else {
            Aska::Yayoi::HttpProtocol::_SetHeaderField(Aska::Yayoi::HttpProtocoledData*, signed char const*, signed char const*, unsigned long, signed char const*, unsigned long)(param_1,param_5,plVar16 + 6,pcVar18,plVar16[1],plVar16[5],plVar16[2]);
          }
          *(undefined1 *)((long)plVar16 + 0x51) = 0;
          *plVar16 = 0;
          plVar16[1] = 0;
          if (plVar16[5] != 0) {
            operator delete[](void*)();
          }
          bVar5 = false;
          plVar16[5] = 0;
          plVar16[2] = 0;
          uVar14 = uVar19;
        }
        else {
          bVar5 = false;
        }
      }
      else {
        if (cVar2 != '\r') goto code_r0x02307f04;
        bVar5 = (bool)(bVar5 | pcVar18[1] == '\n');
      }
    }
    else if (cVar2 == ' ') {
      if (!bVar6) {
        bVar6 = false;
        goto code_r0x02307f34;
      }
      bVar6 = false;
      uVar14 = uVar19;
    }
    else if (cVar2 == ':') {
      if (*(char *)((long)plVar16 + 0x51) == '\0') {
        bVar6 = true;
        *(undefined1 *)((long)plVar16 + 0x51) = 1;
        *(undefined1 *)((long)plVar16 + *plVar16 + 0x30) = 0;
        *plVar16 = 0;
        uVar14 = uVar19;
      }
      else {
code_r0x02307f34:
        plVar16[1] = plVar16[1] + 1;
      }
    }
    else {
code_r0x02307f04:
      if (*(char *)((long)plVar16 + 0x51) != '\0') goto code_r0x02307f34;
      lVar10 = *plVar16;
      *plVar16 = lVar10 + 1;
      *(char *)((long)plVar16 + lVar10 + 0x30) = cVar2;
    }
    break;
  case 3:
    Aska::Yayoi::HttpProtocol::_SetMessageBody(signed char const*, unsigned long, Aska::Yayoi::HttpProtocoledData*, Aska::Yayoi::_decodingData*)(param_1,pcVar18,param_3 - uVar19,param_5,plVar16);
    *param_4 = *(long *)(param_5 + 0x58) + uVar19;
    return param_5;
  }
  goto code_r0x02308028;
code_r0x0230800c:
  uVar9 = 8;
code_r0x02308010:
  *(undefined4 *)(param_5 + 0x7c) = uVar9;
  uVar14 = uVar19 + uVar15;
  pcVar18 = pcVar18 + uVar15;
  uVar19 = uVar14;
code_r0x02308028:
  uVar19 = uVar19 + 1;
  pcVar18 = pcVar18 + 1;
  if ((uVar19 < param_3) || (*(int *)(param_5 + 0x150) == 3)) goto code_r0x02307bbc;
  *(undefined1 *)(param_5 + 0x11) = 0;
  lVar10 = uVar19 + ~uVar14;
  if (lVar10 == 0) {
    if (plVar16[5] == 0) goto code_r0x023080fc;
  }
  else if (plVar16[5] == 0) {
    lVar13 = **(long **)PTR__ZN4Aska6Global19m_pNetworkAllocatorE_02cbc200;
    if (lVar13 == 0) {
      lVar13 = Aska::Global::GetAvailableMemoryManager()();
    }
    lVar13 = Aska::MemoryManager::Malloc(unsigned long)(lVar13,lVar10);
    plVar16[5] = lVar13;
    plVar16[2] = lVar10;
    memcpy(lVar13,(long)pcVar18 - lVar10,lVar10);
    return param_5;
  }
  operator delete[](void*)();
  plVar16[5] = 0;
code_r0x023080fc:
  plVar16[2] = 0;
  return param_5;
}

// ==== Aska::Yayoi::HttpProtocol::ParseMessageBody(signed char const*, unsigned long, Aska::Yayoi::HttpProtocoledData*)
// vaddr 0x2208124 | ghidra 0x2308124 | size 152 | symbol _ZN4Aska5Yayoi12HttpProtocol16ParseMessageBodyEPKamPNS0_18HttpProtocoledDataE | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska5Yayoi12HttpProtocol16ParseMessageBodyEPKamPNS0_18HttpProtocoledDataE
          (undefined8 param_1,undefined8 param_2,undefined8 param_3,long param_4)

{
  long lVar1;
  undefined8 *puVar2;
  undefined8 uVar3;
  undefined1 auStack_28 [8];
  
  if (param_4 == 0) {
    uVar3 = 0;
  }
  else {
    *(undefined4 *)(param_4 + 0x150) = 3;
    if (*(long *)(param_4 + 0x38) == 0) {
      lVar1 = **(long **)PTR__ZN4Aska6Global19m_pNetworkAllocatorE_02cbc200;
      if (lVar1 == 0) {
        lVar1 = Aska::Global::GetAvailableMemoryManager()();
      }
      puVar2 = (undefined8 *)Aska::MemoryManager::Malloc(unsigned long)(lVar1,0x58);
      *(undefined8 **)(param_4 + 0x38) = puVar2;
      if (puVar2 != (undefined8 *)0x0) {
        *(undefined2 *)(puVar2 + 10) = 0;
        puVar2[4] = 0;
        puVar2[5] = 0;
        puVar2[2] = 0;
        puVar2[3] = 0;
        *puVar2 = 0;
        puVar2[1] = 0;
      }
    }
    uVar3 = Aska::Yayoi::HttpProtocol::Deserialize(signed char const*, unsigned long, unsigned long*, Aska::Yayoi::HttpProtocoledData*, Aska::Status&)(param_1,param_2,param_3,auStack_28,param_4);
  }
  return uVar3;
}

// ==== Aska::Yayoi::HttpProtocol::_SetHeaderField(Aska::Yayoi::HttpProtocoledData*, signed char const*, signed char const*, unsigned long, signed char const*, unsigned long)
// vaddr 0x22081bc | ghidra 0x23081bc | size 1520 | symbol _ZN4Aska5Yayoi12HttpProtocol15_SetHeaderFieldEPNS0_18HttpProtocoledDataEPKaS5_mS5_m | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi12HttpProtocol15_SetHeaderFieldEPNS0_18HttpProtocoledDataEPKaS5_mS5_m
               (long param_1,long param_2,ulong param_3,long param_4,ulong param_5,
               undefined8 param_6,long param_7)

{
  ulong uVar1;
  uint uVar2;
  char cVar3;
  ulong uVar4;
  int iVar5;
  long lVar6;
  ulong *puVar7;
  long *plVar8;
  ulong uVar9;
  long lVar10;
  ulong uVar11;
  ulong uVar12;
  long lVar13;
  int iStack_d4;
  ulong auStack_d0 [16];
  undefined1 auStack_48 [4];
  undefined1 auStack_44 [4];
  
  uVar2 = *(uint *)(param_1 + 4);
  if (((uVar2 >> 1 & 1) != 0) && (iVar5 = strcasecmp(param_3,&UNK_029d4387/*"Content-Length"*/), iVar5 == 0)) {
    lVar10 = param_5 + 1;
    auStack_d0[0] = 0;
    auStack_d0[1] = 0;
    if (param_7 == 0) {
      uVar9 = ~param_5;
      puVar7 = auStack_d0;
    }
    else {
      memcpy(auStack_d0,param_6,param_7);
      lVar10 = lVar10 - param_7;
      puVar7 = (ulong *)((long)auStack_d0 + param_7);
      uVar9 = -lVar10;
    }
    memcpy(puVar7,param_4 + uVar9,lVar10);
    *(undefined1 *)((long)auStack_d0 + param_5) = 0;
    iVar5 = atoi(auStack_d0);
    *(long *)(param_2 + 0x50) = (long)iVar5;
    return;
  }
  if (((uVar2 >> 2 & 1) != 0) && (iVar5 = strcasecmp(param_3,&UNK_029d4396/*"Content-Type"*/), iVar5 == 0)) {
    uVar9 = param_5 + 1;
    if (uVar9 < 0x80) {
      memset(auStack_d0,0,0x80);
      if (param_7 == 0) {
        uVar11 = ~param_5;
        puVar7 = auStack_d0;
      }
      else {
        memcpy(auStack_d0,param_6,param_7);
        uVar9 = uVar9 - param_7;
        puVar7 = (ulong *)((long)auStack_d0 + param_7);
        uVar11 = -uVar9;
      }
      memcpy(puVar7,param_4 + uVar11,uVar9);
      *(undefined1 *)((long)auStack_d0 + param_5) = 0;
      Aska::Yayoi::HttpProtocoledData::ParseContentType(char const*)(param_2,auStack_d0);
      return;
    }
    lVar10 = **(long **)PTR__ZN4Aska6Global19m_pNetworkAllocatorE_02cbc200;
    if (lVar10 == 0) {
      lVar10 = Aska::Global::GetAvailableMemoryManager()();
    }
    lVar10 = Aska::MemoryManager::Malloc(unsigned long)(lVar10,uVar9);
    if (param_7 == 0) {
      uVar11 = ~param_5;
      lVar13 = lVar10;
    }
    else {
      memcpy(lVar10,param_6,param_7);
      uVar9 = uVar9 - param_7;
      uVar11 = -uVar9;
      lVar13 = lVar10 + param_7;
    }
    memcpy(lVar13,param_4 + uVar11,uVar9);
    *(undefined1 *)(lVar10 + param_5) = 0;
    Aska::Yayoi::HttpProtocoledData::ParseContentType(char const*)(param_2,lVar10);
    if (lVar10 == 0) {
      return;
    }
    goto code_r0x011fbb90;
  }
  if (((uVar2 & 1) != 0) && (iVar5 = strcasecmp(param_3,&UNK_0295c2a3/*"Location"*/), iVar5 == 0)) {
    lVar10 = param_5 + 1;
    if (lVar10 == 0) {
      lVar13 = 0;
    }
    else {
      lVar13 = **(long **)PTR__ZN4Aska6Global19m_pNetworkAllocatorE_02cbc200;
      if (lVar13 == 0) {
        lVar13 = Aska::Global::GetAvailableMemoryManager()();
      }
      lVar13 = Aska::MemoryManager::Malloc(unsigned long)(lVar13,lVar10);
    }
    if (param_7 == 0) {
      uVar9 = ~param_5;
      lVar6 = lVar13;
    }
    else {
      memcpy(lVar13,param_6,param_7);
      lVar10 = lVar10 - param_7;
      uVar9 = -lVar10;
      lVar6 = lVar13 + param_7;
    }
    memcpy(lVar6,param_4 + uVar9,lVar10);
    *(long *)(param_2 + 0x20) = lVar13;
    *(undefined1 *)(lVar13 + param_5) = 0;
    return;
  }
  if (((uVar2 >> 3 & 1) != 0) && (iVar5 = strcasecmp(param_3,&UNK_029d43a3/*"Expires"*/), iVar5 == 0)) {
    lVar10 = param_5 + 1;
    if (lVar10 == 0) {
      lVar13 = 0;
    }
    else {
      lVar13 = **(long **)PTR__ZN4Aska6Global19m_pNetworkAllocatorE_02cbc200;
      if (lVar13 == 0) {
        lVar13 = Aska::Global::GetAvailableMemoryManager()();
      }
      lVar13 = Aska::MemoryManager::Malloc(unsigned long)(lVar13,lVar10);
    }
    if (param_7 == 0) {
      uVar9 = ~param_5;
      lVar6 = lVar13;
    }
    else {
      memcpy(lVar13,param_6,param_7);
      lVar10 = lVar10 - param_7;
      uVar9 = -lVar10;
      lVar6 = lVar13 + param_7;
    }
    memcpy(lVar6,param_4 + uVar9,lVar10);
    *(long *)(param_2 + 0x30) = lVar13;
    *(undefined1 *)(lVar13 + param_5) = 0;
    return;
  }
  if (((uVar2 >> 5 & 1) != 0) && (iVar5 = strcasecmp(param_3,&UNK_029d43ab/*"Content-Range"*/), iVar5 == 0)) {
    memset(auStack_d0,0,0x80);
    lVar10 = param_5 + 1;
    if (param_7 == 0) {
      param_5 = ~param_5;
      puVar7 = auStack_d0;
    }
    else {
      memcpy(auStack_d0,param_6,param_7);
      lVar10 = lVar10 - param_7;
      puVar7 = (ulong *)((long)auStack_d0 + param_7);
      param_5 = -lVar10;
    }
    memcpy(puVar7,param_4 + param_5,lVar10);
    sscanf(auStack_d0,&UNK_029d43b9/*"bytes %d-%d/%d"*/,auStack_44,auStack_48,&iStack_d4);
    *(long *)(param_2 + 0x50) = (long)iStack_d4;
    return;
  }
  if (((uVar2 >> 7 & 1) == 0) || (iVar5 = strcasecmp(param_3,&UNK_029d43c8/*"Content-Encoding"*/), iVar5 != 0)) {
    if ((uVar2 >> 4 & 1) != 0) {
      iVar5 = strcasecmp(param_3,&UNK_029d43d9/*"Set-Cookie"*/);
      if (iVar5 == 0) {
        return;
      }
      iVar5 = strcasecmp(param_3,&UNK_029d43dd/*"Cookie"*/);
      if (iVar5 == 0) {
        return;
      }
    }
    if (((uVar2 >> 6 & 1) != 0) && (iVar5 = strcasecmp(param_3,&UNK_029d43e4/*"Transfer-Encoding"*/), iVar5 == 0)) {
      lVar10 = param_5 + 1;
      auStack_d0[0] = 0;
      auStack_d0[1] = 0;
      if (param_7 == 0) {
        uVar9 = ~param_5;
        puVar7 = auStack_d0;
      }
      else {
        memcpy(auStack_d0,param_6,param_7);
        lVar10 = lVar10 - param_7;
        puVar7 = (ulong *)((long)auStack_d0 + param_7);
        uVar9 = -lVar10;
      }
      memcpy(puVar7,param_4 + uVar9,lVar10);
      *(undefined1 *)((long)auStack_d0 + param_5) = 0;
      iVar5 = strcasecmp(auStack_d0,&UNK_029d43f6/*"chunked"*/);
      if (iVar5 != 0) {
        return;
      }
      *(undefined1 *)(param_2 + 0x133) = 1;
      return;
    }
    lVar10 = *(long *)(param_1 + 0x38);
    if (lVar10 == 0) {
      return;
    }
    uVar9 = *(ulong *)(lVar10 + 0x28);
    if (uVar9 == 0) {
      return;
    }
    uVar11 = ~param_3 + param_3 * 0x200000;
    uVar11 = (uVar11 ^ uVar11 >> 0x18) * 0x109;
    uVar12 = (uVar11 ^ uVar11 >> 0xe) * 0x15;
    uVar11 = 0;
    do {
      uVar1 = (uVar12 ^ uVar12 >> 0x1c) * 0x80000001 + uVar11;
      uVar4 = 0;
      if (uVar9 != 0) {
        uVar4 = uVar1 / uVar9;
      }
      lVar13 = uVar1 - uVar4 * uVar9;
      cVar3 = *(char *)(*(long *)(lVar10 + 0x20) + lVar13 * 0x18);
      if (cVar3 == '\x01') {
        if (*(ulong *)(*(long *)(lVar10 + 0x20) + lVar13 * 0x18 + 8) == param_3) {
          lVar10 = param_5 + 1;
          if (lVar10 == 0) {
            lVar13 = 0;
          }
          else {
            lVar13 = **(long **)PTR__ZN4Aska6Global19m_pNetworkAllocatorE_02cbc200;
            if (lVar13 == 0) {
              lVar13 = Aska::Global::GetAvailableMemoryManager()();
            }
            lVar13 = Aska::MemoryManager::Malloc(unsigned long)(lVar13,lVar10);
          }
          if (param_7 == 0) {
            uVar9 = ~param_5;
            param_7 = lVar13;
          }
          else {
            memcpy(lVar13,param_6,param_7);
            lVar10 = lVar10 - param_7;
            param_7 = lVar13 + param_7;
            uVar9 = -lVar10;
          }
          memcpy(param_7,param_4 + uVar9,lVar10);
          *(undefined1 *)(lVar13 + param_5) = 0;
          auStack_d0[0] = param_3;
          plVar8 = (long *)Aska::THashMap<char const*, char const*, Aska::THasher<char const*>, Aska::TEqualTo<char const*>, Aska::TAllocator<Aska::TPair<char const* const, char const*> > >::operator[](char const* const&)(param_2 + 0x168,auStack_d0);
          *plVar8 = lVar13;
          return;
        }
      }
      else if (cVar3 == '\0') {
        return;
      }
      uVar11 = uVar11 + 1;
    } while (uVar11 < uVar9);
    return;
  }
  lVar13 = param_5 + 1;
  if (lVar13 == 0) {
    lVar6 = 0;
    lVar10 = lVar6;
    if (param_7 == 0) goto code_r0x02308684;
code_r0x02308548:
    memcpy(lVar10,param_6,param_7);
    lVar13 = lVar13 - param_7;
    lVar6 = lVar10 + param_7;
    uVar9 = -lVar13;
  }
  else {
    lVar10 = **(long **)PTR__ZN4Aska6Global19m_pNetworkAllocatorE_02cbc200;
    if (lVar10 == 0) {
      lVar10 = Aska::Global::GetAvailableMemoryManager()();
    }
    lVar6 = Aska::MemoryManager::Malloc(unsigned long)(lVar10,lVar13);
    lVar10 = lVar6;
    if (param_7 != 0) goto code_r0x02308548;
code_r0x02308684:
    uVar9 = ~param_5;
    lVar10 = lVar6;
  }
  memcpy(lVar6,param_4 + uVar9,lVar13);
  *(undefined1 *)(lVar10 + param_5) = 0;
  Aska::Yayoi::HttpProtocoledData::ParseContentEncoding(char const*)(param_2,lVar10);
  if (lVar10 == 0) {
    return;
  }
code_r0x011fbb90:
  (*(code *)PTR__ZdaPv_02cb5db8)(lVar10);
  return;
}

// ==== Aska::Yayoi::HttpProtocol::_SetMessageBody(signed char const*, unsigned long, Aska::Yayoi::HttpProtocoledData*, Aska::Yayoi::_decodingData*)
// vaddr 0x22087ac | ghidra 0x23087ac | size 864 | symbol _ZN4Aska5Yayoi12HttpProtocol15_SetMessageBodyEPKamPNS0_18HttpProtocoledDataEPNS0_13_decodingDataE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi12HttpProtocol15_SetMessageBodyEPKamPNS0_18HttpProtocoledDataEPNS0_13_decodingDataE
               (long param_1,char *param_2,char *param_3,long param_4,undefined8 *param_5)

{
  bool bVar1;
  long lVar2;
  undefined8 uVar3;
  long lVar4;
  char *pcVar5;
  char *pcVar6;
  char *pcVar7;
  long *plVar8;
  long lVar9;
  char *pcVar10;
  char *pcVar11;
  
  *(undefined1 *)(param_4 + 0x11) = 0;
  pcVar10 = *(char **)(param_4 + 0x50);
  pcVar11 = param_3;
  if (*(char *)(param_1 + 0x30) == '\0') {
    lVar2 = *(long *)(param_4 + 0x28);
    if (lVar2 == 0) {
      lVar9 = 0;
      bVar1 = true;
      pcVar5 = param_3;
      goto joined_r0x023088f8;
    }
    pcVar5 = *(char **)(param_4 + 0x58);
    if (pcVar5 < param_3) {
      lVar9 = *(long *)(param_1 + 0x10);
      if ((lVar9 == 0) &&
         (lVar9 = **(long **)PTR__ZN4Aska6Global19m_pNetworkAllocatorE_02cbc200, lVar9 == 0)) {
        lVar9 = Aska::Global::GetAvailableMemoryManager()();
      }
      lVar4 = Aska::MemoryManager::Malloc(unsigned long)(lVar9,param_3);
      if (lVar4 == 0) goto code_r0x023088e4;
      memcpy(lVar4,lVar2,*(undefined8 *)(param_4 + 0x58));
      operator delete[](void*)(lVar2);
      lVar9 = 0;
      *(long *)(param_4 + 0x28) = lVar4;
      pcVar5 = param_3;
    }
    else {
      lVar9 = 0;
    }
joined_r0x023088ac:
    if (pcVar10 != (char *)0x0) goto code_r0x02308924;
code_r0x02308908:
    if (*(char *)(param_4 + 0x133) == '\0') goto code_r0x02308924;
    if (param_2 == (char *)0x0) {
      if (param_3 != (char *)0x0) {
        lVar2 = *(long *)(param_1 + 0x10);
        if ((lVar2 == 0) &&
           (lVar2 = **(long **)PTR__ZN4Aska6Global19m_pNetworkAllocatorE_02cbc200, lVar2 == 0)) {
          lVar2 = Aska::Global::GetAvailableMemoryManager()();
        }
        param_2 = (char *)Aska::MemoryManager::Malloc(unsigned long)(lVar2,param_3);
        bVar1 = true;
        pcVar10 = (char *)0x0;
        goto code_r0x02308a0c;
      }
      param_2 = (char *)0x0;
      bVar1 = true;
    }
    else {
      bVar1 = false;
      pcVar10 = param_2;
      if (param_3 != (char *)0x0) {
code_r0x02308a0c:
        pcVar11 = (char *)0x0;
        do {
          pcVar7 = (char *)param_5[4];
          if (pcVar7 == (char *)0x0) {
            pcVar6 = pcVar10;
            if ((*pcVar10 == '\r') && (pcVar10[1] == '\n')) {
              param_3 = param_3 + -2;
              if (param_3 == (char *)0x0) break;
              pcVar6 = pcVar10 + 2;
            }
            pcVar7 = (char *)strtoul(pcVar6,0,0x10);
            param_5[4] = pcVar7;
            if (pcVar7 == (char *)0x0) {
              *(undefined1 *)(param_4 + 0x11) = 1;
              *(char **)(param_4 + 0x50) = pcVar11 + param_5[3];
              break;
            }
            lVar2 = strchr(pcVar6,0xd);
            pcVar10 = pcVar6;
            if (lVar2 != 0) {
              pcVar10 = (char *)(lVar2 + 2);
            }
            param_3 = pcVar6 + ((long)param_3 - (long)pcVar10);
          }
          lVar2 = (long)pcVar7 - (long)param_3;
          pcVar6 = param_3;
          if (pcVar7 < param_3 || lVar2 == 0) {
            lVar2 = 0;
            pcVar6 = pcVar7;
          }
          param_5[4] = lVar2;
          memcpy(param_2 + (long)pcVar11,pcVar10,pcVar6);
          pcVar11 = pcVar6 + (long)pcVar11;
          param_3 = param_3 + -(long)pcVar6;
          pcVar10 = pcVar10 + (long)pcVar6;
        } while (param_3 != (char *)0x0);
      }
    }
  }
  else {
    lVar9 = param_5[3];
    if (pcVar10 == (char *)0x0) {
      pcVar5 = param_3 + lVar9;
      if (pcVar5 == (char *)0x0) {
        *(undefined1 *)(param_4 + 0x11) = 1;
        return;
      }
      plVar8 = (long *)(param_4 + 0x28);
      lVar2 = *plVar8;
      lVar4 = *(long *)(param_1 + 0x10);
      if (lVar4 == 0) {
        lVar4 = **(long **)PTR__ZN4Aska6Global19m_pNetworkAllocatorE_02cbc200;
        if (lVar4 == 0) {
          lVar4 = Aska::Global::GetAvailableMemoryManager()();
        }
        lVar4 = Aska::MemoryManager::Realloc(unsigned long, void*, long)(lVar4,pcVar5,lVar2,4);
        *plVar8 = lVar4;
        if (lVar4 != 0) goto code_r0x02308908;
        lVar4 = Aska::Global::GetAvailableMemoryManager()();
      }
      lVar4 = Aska::MemoryManager::Realloc(unsigned long, void*, long)(lVar4,pcVar5,lVar2,4);
      *plVar8 = lVar4;
      if (lVar4 == 0) {
code_r0x023088e4:
        *(long *)(param_4 + 0x28) = lVar2;
        return;
      }
      goto code_r0x02308908;
    }
    bVar1 = *(long *)(param_4 + 0x28) == 0;
    pcVar5 = pcVar10;
joined_r0x023088f8:
    if ((pcVar5 == (char *)0x0) || (!bVar1)) goto joined_r0x023088ac;
    lVar2 = *(long *)(param_1 + 0x10);
    if ((lVar2 == 0) &&
       (lVar2 = **(long **)PTR__ZN4Aska6Global19m_pNetworkAllocatorE_02cbc200, lVar2 == 0)) {
      lVar2 = Aska::Global::GetAvailableMemoryManager()();
    }
    uVar3 = Aska::MemoryManager::Malloc(unsigned long)(lVar2,pcVar5);
    *(undefined8 *)(param_4 + 0x28) = uVar3;
    if (pcVar10 == (char *)0x0) goto code_r0x02308908;
code_r0x02308924:
    bVar1 = false;
  }
  pcVar10 = pcVar5 + -lVar9;
  if (pcVar11 + lVar9 <= pcVar5) {
    pcVar10 = pcVar11;
  }
  memcpy(*(long *)(param_4 + 0x28) + lVar9,param_2,pcVar10);
  param_5[3] = pcVar10 + param_5[3];
  *(char **)(param_4 + 0x58) = pcVar10;
  if (bVar1) {
    if (param_2 != (char *)0x0) {
      operator delete[](void*)(param_2);
      lVar2 = param_5[5];
      goto joined_r0x02308994;
    }
  }
  else if (*(long *)(param_4 + 0x50) == param_5[3]) {
    *(undefined1 *)(param_4 + 0x11) = 1;
  }
  lVar2 = param_5[5];
joined_r0x02308994:
  if (lVar2 != 0) {
    operator delete[](void*)();
    param_5[5] = 0;
  }
  *(undefined2 *)(param_5 + 10) = 0;
  param_5[1] = 0;
  param_5[2] = 0;
  *param_5 = 0;
  return;
}

// ==== Aska::Yayoi::HttpProtocol::FreeSerializedData(Aska::Status, void const*)
// vaddr 0x2208b0c | ghidra 0x2308b0c | size 16 | symbol _ZN4Aska5Yayoi12HttpProtocol18FreeSerializedDataENS_6StatusEPKv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi12HttpProtocol18FreeSerializedDataENS_6StatusEPKv
               (undefined8 param_1,undefined8 param_2,long param_3)

{
  if (param_3 != 0) {
    (*(code *)PTR__ZdaPv_02cb5db8)(param_3);
    return;
  }
  return;
}

// ==== Aska::Yayoi::HttpProtocol::AllocData()
// vaddr 0x2208b1c | ghidra 0x2308b1c | size 64 | symbol _ZN4Aska5Yayoi12HttpProtocol9AllocDataEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska5Yayoi12HttpProtocol9AllocDataEv(void)

{
  long lVar1;
  
  lVar1 = **(long **)PTR__ZN4Aska6Global19m_pNetworkAllocatorE_02cbc200;
  if (lVar1 == 0) {
    lVar1 = Aska::Global::GetAvailableMemoryManager()();
  }
  lVar1 = Aska::MemoryManager::Malloc(unsigned long)(lVar1,0x198);
  if (lVar1 != 0) {
    Aska::Yayoi::HttpProtocoledData::HttpProtocoledData()(lVar1);
  }
  return lVar1;
}

// ==== Aska::Yayoi::HttpProtocoledData::HttpProtocoledData()
// vaddr 0x22093d0 | ghidra 0x23093d0 | size 456 | symbol _ZN4Aska5Yayoi18HttpProtocoledDataC2Ev | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska5Yayoi18HttpProtocoledDataC1Ev(undefined8 *param_1)

{
  undefined *puVar1;
  ulong uVar2;
  long lVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined *puVar6;
  undefined8 *puVar7;
  undefined1 *puVar8;
  undefined1 *puVar9;
  ulong uVar11;
  ulong uVar12;
  long *plVar13;
  int iVar14;
  undefined1 *puVar10;
  
  *(undefined2 *)(param_1 + 2) = 0;
  *param_1 = 0;
  param_1[1] = 0;
  memset(param_1 + 3,0,100);
  uVar5 = _UNK_029d44f8;
  uVar4 = _UNK_029d44f0;
  plVar13 = param_1 + 0x14;
  *plVar13 = (long)(PTR__ZTVN4Aska11TPoolLegacyINS_5Yayoi10RawdatPairELb0EEE_02cc15b8 + 0x10);
  *(undefined4 *)((long)param_1 + 0x8c) = 200;
  puVar1 = PTR__ZTVN4Aska9TBitArrayIjLb0EEE_02cba038;
  param_1[0x12] = 0;
  param_1[0x13] = 0;
  *(undefined4 *)(param_1 + 0x15) = 0;
  *(undefined4 *)(param_1 + 0x17) = 0;
  param_1[0x16] = puVar1 + 0x10;
  *(undefined1 *)(param_1 + 0x1a) = 0;
  param_1[0x18] = 0;
  param_1[0x19] = 0;
  *(undefined8 *)((long)param_1 + 0x84) = uVar5;
  *(undefined8 *)((long)param_1 + 0x7c) = uVar4;
  param_1[0x1c] = 0;
  Aska::TPoolLegacy<Aska::Yayoi::RawdatPair, false>::SecurePool(unsigned int, bool, void const*, unsigned int const*)(plVar13,0x20,0,0,0);
  puVar7 = (undefined8 *)operator new[](unsigned long, std::nothrow_t const&)(0x88,PTR__ZSt7nothrow_02cb9a80);
  iVar14 = 0x11;
  if (puVar7 == (undefined8 *)0x0) {
    iVar14 = 1;
    puVar7 = param_1 + 0x21;
  }
  memset(puVar7,0,iVar14 << 3);
  *(int *)(param_1 + 0x1f) = iVar14;
  param_1[0x1e] = puVar7;
  param_1[0x20] = puVar7;
  *(undefined4 *)((long)param_1 + 300) = 0;
  param_1[0x23] = 0;
  param_1[0x24] = 0;
  *(undefined1 *)(param_1 + 0x25) = 0;
  param_1[0x22] = 0;
  puVar6 = PTR__ZTVN4Aska5Yayoi15RawdatHashtableE_02cc4020;
  *(undefined4 *)((long)param_1 + 0x131) = 0x101;
  *(undefined1 *)((long)param_1 + 0x135) = 0;
  param_1[0x2b] = 0;
  param_1[0x2c] = 0;
  param_1[0x28] = 0;
  param_1[0x29] = 0;
  param_1[0x27] = 0;
  *(undefined8 *)((long)param_1 + 0x174) = 0x3f400000;
  puVar1 = PTR__ZTVN4Aska8THashMapIPKcS2_NS_7THasherIS2_EENS_8TEqualToIS2_EENS_10TAllocatorINS_5TPairIKS2_S2_EEEEEE_02cbbae8
           + 0x10;
  *plVar13 = (long)(puVar6 + 0x10);
  param_1[0x2d] = puVar1;
  *(undefined4 *)((long)param_1 + 0x17c) = 0;
  puVar8 = (undefined1 *)Aska::MemoryManagerAdapter::AlignedMalloc(unsigned long, unsigned long)(0x198,8);
  lVar3 = 0x11;
  if (puVar8 == (undefined1 *)0x0) {
    lVar3 = 0;
  }
  param_1[0x31] = puVar8;
  param_1[0x32] = lVar3;
  if (puVar8 != (undefined1 *)0x0) {
    uVar2 = (lVar3 * 0x18 - 0x18U) / 0x18 + 1;
    puVar10 = puVar8;
    if ((1 < uVar2) && (uVar11 = uVar2 & 0x1ffffffffffffffe, uVar11 != 0)) {
      uVar12 = uVar11;
      do {
        *puVar10 = 0;
        puVar10[0x18] = 0;
        uVar12 = uVar12 - 2;
        puVar10 = puVar10 + 0x30;
      } while (uVar12 != 0);
      puVar10 = puVar8 + uVar11 * 0x18;
      if (uVar2 == uVar11) {
        return;
      }
    }
    do {
      puVar9 = puVar10 + 0x18;
      *puVar10 = 0;
      puVar10 = puVar9;
    } while (puVar8 + lVar3 * 0x18 != puVar9);
  }
  return;
}

// ==== Aska::Yayoi::HttpProtocoledData::~HttpProtocoledData()
// vaddr 0x2209598 | ghidra 0x2309598 | size 268 | symbol _ZN4Aska5Yayoi18HttpProtocoledDataD2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi18HttpProtocoledDataD1Ev(long param_1)

{
  int iVar1;
  char cVar2;
  bool bVar3;
  int *piVar4;
  long lVar5;
  long *plVar6;
  
  Aska::Yayoi::HttpProtocoledData::ClearAll()();
  *(undefined **)(param_1 + 0x168) =
       PTR__ZTVN4Aska8THashMapIPKcS2_NS_7THasherIS2_EENS_8TEqualToIS2_EENS_10TAllocatorINS_5TPairIKS2_S2_EEEEEE_02cbbae8
       + 0x10;
  if (*(long *)(param_1 + 0x188) != 0) {
    Aska::MemoryManagerAdapter::AlignedFree(void*)();
    *(undefined8 *)(param_1 + 0x188) = 0;
    *(undefined8 *)(param_1 + 400) = 0;
  }
  piVar4 = *(int **)(param_1 + 0x160);
  *(undefined8 *)(param_1 + 0x178) = 0;
  if (piVar4 == (int *)0x0) {
code_r0x023095ec:
    lVar5 = *(long *)(param_1 + 0x158);
    if (lVar5 != 0) {
      Aska::Yayoi::Cookie::Clear()(lVar5);
      *(undefined **)(lVar5 + 0x30) =
           PTR__ZTVN4Aska8THashMapIPKcS2_NS_5Yayoi6Cookie12StringHasherENS4_13StringEqualToENS_10TAllocatorINS_5TPairIKS2_S2_EEEEEE_02cb9918
           + 0x10;
      if (*(long *)(lVar5 + 0x50) != 0) {
        Aska::MemoryManagerAdapter::AlignedFree(void*)();
      }
      operator delete(void*)(lVar5);
    }
    if (*(long *)(param_1 + 0x160) != 0) {
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
    if (iVar1 + -1 == 0) goto code_r0x023095ec;
  }
  plVar6 = (long *)(param_1 + 0xa0);
  *plVar6 = (long)(PTR__ZTVN4Aska5THashINS_5Yayoi10RawdatPairEEE_02cc2840 + 0x10);
  *(undefined8 *)(param_1 + 0x158) = 0;
  *(undefined8 *)(param_1 + 0x160) = 0;
  Aska::TBinaryTree<Aska::Yayoi::RawdatPair>::FreeTable()(plVar6);
  Aska::TBinaryTree<Aska::Yayoi::RawdatPair>::~TBinaryTree()(plVar6);
  piVar4 = *(int **)(param_1 + 0x98);
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
    if (iVar1 + -1 != 0) goto code_r0x02309694;
  }
  lVar5 = *(long *)(param_1 + 0x90);
  if (lVar5 != 0) {
    Aska::Yayoi::URI::DeleteBuffer()(lVar5);
    operator delete(void*)(lVar5);
  }
  if (*(long *)(param_1 + 0x98) != 0) {
    Aska::TSharedPointerCode::DeleteCounter(int*)();
  }
code_r0x02309694:
  *(undefined8 *)(param_1 + 0x90) = 0;
  *(undefined8 *)(param_1 + 0x98) = 0;
  return;
}

// ==== Aska::Yayoi::HttpProtocoledData::ClearAll()
// vaddr 0x22096a4 | ghidra 0x23096a4 | size 560 | symbol _ZN4Aska5Yayoi18HttpProtocoledData8ClearAllEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi18HttpProtocoledData8ClearAllEv(long param_1)

{
  int iVar1;
  char cVar2;
  bool bVar3;
  char *pcVar4;
  int *piVar5;
  long lVar6;
  long lVar7;
  char *pcVar8;
  char *pcVar9;
  char *pcVar10;
  
  if ((*(char *)(param_1 + 0x134) == '\0') || (*(char *)(param_1 + 0x135) != '\0')) {
    if (*(long *)(param_1 + 0x28) != 0) {
      operator delete[](void*)();
      goto code_r0x023096dc;
    }
  }
  else {
code_r0x023096dc:
    *(undefined8 *)(param_1 + 0x28) = 0;
  }
  *(undefined1 *)(param_1 + 0x131) = 1;
  *(undefined2 *)(param_1 + 0x134) = 0;
  *(undefined4 *)(param_1 + 0x150) = 0;
  if (*(long *)(param_1 + 0x20) != 0) {
    operator delete[](void*)();
    *(undefined8 *)(param_1 + 0x20) = 0;
  }
  if (*(long *)(param_1 + 0x30) != 0) {
    operator delete[](void*)();
    *(undefined8 *)(param_1 + 0x30) = 0;
  }
  if (*(long *)(param_1 + 0x18) != 0) {
    operator delete[](void*)();
    *(undefined8 *)(param_1 + 0x18) = 0;
  }
  if (*(long *)(param_1 + 0x40) != 0) {
    operator delete[](void*)();
    *(undefined8 *)(param_1 + 0x40) = 0;
  }
  lVar7 = *(long *)(param_1 + 0x38);
  if (lVar7 != 0) {
    if (*(long *)(lVar7 + 0x28) != 0) {
      operator delete[](void*)();
    }
    operator delete(void*)(lVar7);
    *(undefined8 *)(param_1 + 0x38) = 0;
  }
  pcVar4 = *(char **)(param_1 + 0x188);
  lVar7 = *(long *)(param_1 + 400);
  pcVar10 = pcVar4 + lVar7 * 0x18;
  pcVar9 = pcVar10;
  if ((*(int *)(param_1 + 0x178) != 0) && (pcVar9 = pcVar4, lVar7 != 0)) {
    lVar6 = lVar7 * 0x18;
    pcVar8 = pcVar4;
    do {
      pcVar9 = pcVar8;
      if (*pcVar8 == '\x01') break;
      lVar6 = lVar6 + -0x18;
      pcVar8 = pcVar8 + 0x18;
      pcVar9 = pcVar10;
    } while (lVar6 != 0);
  }
  if (pcVar9 != pcVar4 + lVar7 * 0x18) {
    do {
      pcVar4 = pcVar9;
      if (*(long *)(pcVar9 + 0x10) != 0) {
        operator delete[](void*)();
      }
      do {
        pcVar9 = pcVar10;
        if (pcVar10 == pcVar4) break;
        pcVar9 = pcVar4 + 0x18;
        pcVar4 = pcVar9;
      } while (*pcVar9 != '\x01');
      pcVar4 = *(char **)(param_1 + 0x188);
      lVar7 = *(long *)(param_1 + 400);
    } while (pcVar9 != pcVar4 + lVar7 * 0x18);
  }
  if ((lVar7 != 0) && (pcVar4 != (char *)0x0)) {
    do {
      piVar5 = (int *)(param_1 + 0x178);
      if ((*pcVar4 == '\x01') || (piVar5 = (int *)(param_1 + 0x17c), *pcVar4 == '\x02')) {
        *piVar5 = *piVar5 + -1;
        *pcVar4 = '\0';
      }
      pcVar4 = pcVar4 + 0x18;
    } while (pcVar9 != pcVar4);
  }
  lVar7 = *(long *)(param_1 + 0x158);
  *(undefined8 *)(param_1 + 0x178) = 0;
  *(undefined2 *)(param_1 + 0x134) = 0;
  if (lVar7 == 0) goto code_r0x023098a4;
  piVar5 = *(int **)(param_1 + 0x160);
  if (piVar5 == (int *)0x0) {
code_r0x02309868:
    Aska::Yayoi::Cookie::Clear()(lVar7);
    *(undefined **)(lVar7 + 0x30) =
         PTR__ZTVN4Aska8THashMapIPKcS2_NS_5Yayoi6Cookie12StringHasherENS4_13StringEqualToENS_10TAllocatorINS_5TPairIKS2_S2_EEEEEE_02cb9918
         + 0x10;
    if (*(long *)(lVar7 + 0x50) != 0) {
      Aska::MemoryManagerAdapter::AlignedFree(void*)();
    }
    operator delete(void*)(lVar7);
code_r0x02309894:
    if (*(long *)(param_1 + 0x160) != 0) {
      Aska::TSharedPointerCode::DeleteCounter(int*)();
    }
  }
  else {
    do {
      iVar1 = *piVar5;
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar5,0x10);
      if (bVar3) {
        *piVar5 = iVar1 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    if (iVar1 + -1 == 0) {
      lVar7 = *(long *)(param_1 + 0x158);
      if (lVar7 != 0) goto code_r0x02309868;
      goto code_r0x02309894;
    }
  }
  *(long *)(param_1 + 0x158) = 0;
  *(undefined8 *)(param_1 + 0x160) = 0;
code_r0x023098a4:
  if (*(long *)(param_1 + 0x138) != 0) {
    operator delete[](void*)();
    *(undefined8 *)(param_1 + 0x138) = 0;
  }
  if (*(long *)(param_1 + 0x140) != 0) {
    operator delete[](void*)();
    *(undefined8 *)(param_1 + 0x140) = 0;
  }
  return;
}

// ==== Aska::Yayoi::HttpProtocoledData::ClearContent()
// vaddr 0x22098d4 | ghidra 0x23098d4 | size 84 | symbol _ZN4Aska5Yayoi18HttpProtocoledData12ClearContentEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi18HttpProtocoledData12ClearContentEv(long param_1)

{
  if ((*(char *)(param_1 + 0x134) == '\0') || (*(char *)(param_1 + 0x135) != '\0')) {
    if (*(long *)(param_1 + 0x28) == 0) goto code_r0x0230990c;
    operator delete[](void*)();
  }
  *(undefined8 *)(param_1 + 0x28) = 0;
code_r0x0230990c:
  *(undefined2 *)(param_1 + 0x134) = 0;
  *(undefined1 *)(param_1 + 0x131) = 1;
  *(undefined4 *)(param_1 + 0x150) = 0;
  return;
}

// ==== Aska::Yayoi::HttpProtocoledData::AllocateHeaderCache(long)
// vaddr 0x2209928 | ghidra 0x2309928 | size 92 | symbol _ZN4Aska5Yayoi18HttpProtocoledData19AllocateHeaderCacheEl | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi18HttpProtocoledData19AllocateHeaderCacheEl(long param_1,long param_2)

{
  long lVar1;
  undefined8 uVar2;
  
  if (*(long *)(param_1 + 0x140) != 0) {
    operator delete[](void*)();
    *(undefined8 *)(param_1 + 0x140) = 0;
  }
  if (param_2 == 0) {
    uVar2 = 0;
  }
  else {
    lVar1 = **(long **)PTR__ZN4Aska6Global19m_pNetworkAllocatorE_02cbc200;
    if (lVar1 == 0) {
      lVar1 = Aska::Global::GetAvailableMemoryManager()();
    }
    uVar2 = Aska::MemoryManager::Malloc(unsigned long)(lVar1,param_2);
  }
  *(undefined8 *)(param_1 + 0x140) = uVar2;
  return;
}

// ==== Aska::Yayoi::HttpProtocoledData::BuildPostHeaderString()
// vaddr 0x2209984 | ghidra 0x2309984 | size 152 | symbol _ZN4Aska5Yayoi18HttpProtocoledData21BuildPostHeaderStringEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska5Yayoi18HttpProtocoledData21BuildPostHeaderStringEv(long param_1)

{
  long lVar1;
  long lVar2;
  long lVar3;
  
  lVar1 = *(long *)(param_1 + 0x138);
  if (*(char *)(param_1 + 0x131) != '\0') {
    if (lVar1 != 0) {
      operator delete[](void*)();
      *(undefined8 *)(param_1 + 0x138) = 0;
    }
    lVar2 = Aska::Yayoi::HttpProtocoledData::MakeParamString(char*, unsigned long)(param_1,0,0);
    lVar1 = 0;
    if (lVar2 != 0) {
      lVar1 = **(long **)PTR__ZN4Aska6Global19m_pNetworkAllocatorE_02cbc200;
      if (lVar1 == 0) {
        lVar1 = Aska::Global::GetAvailableMemoryManager()();
      }
      lVar3 = Aska::MemoryManager::Malloc(unsigned long)(lVar1,lVar2);
      *(long *)(param_1 + 0x138) = lVar3;
      lVar1 = 0;
      if (lVar3 != 0) {
        lVar3 = Aska::Yayoi::HttpProtocoledData::MakeParamString(char*, unsigned long)(param_1,lVar3,lVar2);
        lVar1 = *(long *)(param_1 + 0x138);
        *(bool *)(param_1 + 0x131) = lVar2 != lVar3;
      }
    }
  }
  return lVar1;
}

// ==== Aska::Yayoi::HttpProtocoledData::MakeParamString(char*, unsigned long)
// vaddr 0x2209a1c | ghidra 0x2309a1c | size 916 | symbol _ZN4Aska5Yayoi18HttpProtocoledData15MakeParamStringEPcm | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Removing unreachable block (ram,0x02309ae4) */

ulong _ZN4Aska5Yayoi18HttpProtocoledData15MakeParamStringEPcm
                (long param_1,undefined1 *param_2,ulong param_3)

{
  ulong uVar1;
  long lVar2;
  undefined1 *puVar3;
  undefined8 uVar4;
  int *piVar5;
  bool bVar6;
  long lVar7;
  long *plVar8;
  long lVar9;
  long lVar10;
  long lVar11;
  long lVar12;
  undefined8 uVar13;
  int iVar14;
  ulong uVar15;
  code *pcVar16;
  long lVar17;
  char cVar18;
  undefined1 *puVar19;
  ulong uVar20;
  
  if (*(char *)(param_1 + 0x134) != '\0') {
    uVar15 = *(ulong *)(param_1 + 0x50);
    if (param_2 == (undefined1 *)0x0) {
      return uVar15;
    }
    if (uVar15 <= param_3) {
      memcpy(param_2,*(undefined8 *)(param_1 + 0x28),uVar15);
      return *(ulong *)(param_1 + 0x50);
    }
    return uVar15;
  }
  plVar8 = *(long **)(param_1 + 0x148);
  if (plVar8 == (long *)0x0) {
    lVar10 = 0;
    lVar9 = 0;
    iVar14 = *(int *)(param_1 + 300);
  }
  else {
    if (param_2 == (undefined1 *)0x0) {
      lVar10 = *(long *)(param_1 + 0x90);
      piVar5 = *(int **)(param_1 + 0x98);
      pcVar16 = *(code **)*plVar8;
      uVar13 = *(undefined8 *)
                (PTR__ZN4Aska5Yayoi18HttpProtocoledData14METHOD_STRINGSE_02cbc250 +
                (long)*(int *)(param_1 + 0x7c) * 8);
      if (piVar5 == (int *)0x0) {
        lVar9 = (*pcVar16)(plVar8,uVar13,*(undefined8 *)(lVar10 + 0x50),param_1);
code_r0x02309b6c:
        Aska::Yayoi::URI::DeleteBuffer()(lVar10);
        operator delete(void*)(lVar10);
        if (piVar5 != (int *)0x0) {
code_r0x02309b80:
          Aska::TSharedPointerCode::DeleteCounter(int*)(piVar5);
        }
      }
      else {
        do {
          cVar18 = '\x01';
          bVar6 = (bool)ExclusiveMonitorPass(piVar5,0x10);
          if (bVar6) {
            *piVar5 = *piVar5 + 1;
            cVar18 = ExclusiveMonitorsStatus();
          }
        } while (cVar18 != '\0');
        lVar9 = (*pcVar16)(plVar8,uVar13,*(undefined8 *)(lVar10 + 0x50),param_1);
        do {
          iVar14 = *piVar5;
          cVar18 = '\x01';
          bVar6 = (bool)ExclusiveMonitorPass(piVar5,0x10);
          if (bVar6) {
            *piVar5 = iVar14 + -1;
            cVar18 = ExclusiveMonitorsStatus();
          }
        } while (cVar18 != '\0');
        if (iVar14 == 1) {
          if (lVar10 != 0) goto code_r0x02309b6c;
          goto code_r0x02309b80;
        }
      }
    }
    else {
      lVar9 = (**(code **)(*plVar8 + 8))();
    }
    if (lVar9 == 0) {
      lVar10 = 0;
      iVar14 = *(int *)(param_1 + 300);
    }
    else {
      lVar10 = strlen(lVar9);
      iVar14 = *(int *)(param_1 + 300);
      if (lVar10 != 0) goto code_r0x02309b9c;
    }
  }
  if (iVar14 == 0) {
    return 0;
  }
code_r0x02309b9c:
  uVar15 = lVar10 + (iVar14 * 2 + -2) + *(long *)(param_1 + 0x60) + 2;
  if ((param_2 != (undefined1 *)0x0) && (uVar15 <= param_3)) {
    lVar17 = *(long *)(param_1 + 0x110);
    *(undefined1 *)(param_1 + 0x128) = 0;
    *(long *)(param_1 + 0x120) = lVar17;
    cVar18 = lVar17 == 0;
    lVar11 = lVar17;
    puVar19 = param_2;
    if ((bool)cVar18) {
      *(undefined1 *)(param_1 + 0x128) = 1;
      lVar11 = 0;
    }
    while ((lVar17 != 0 ||
           (*(long *)(param_1 + 0x120) = *(long *)(param_1 + 0x110), *(long *)(param_1 + 0x110) != 0
           ))) {
      if (cVar18 != '\0') goto code_r0x02309d7c;
      uVar13 = *(undefined8 *)(lVar11 + 0x30);
      lVar17 = *(long *)(lVar11 + 0x38);
      uVar4 = *(undefined8 *)(lVar11 + 0x40);
      lVar12 = *(long *)(lVar11 + 0x48);
      lVar11 = *(long *)(param_1 + 0x40);
      uVar20 = *(ulong *)(param_1 + 0x48);
      uVar1 = (lVar12 + lVar17) * 3 + 1;
      if (uVar20 < uVar1) {
        if (lVar11 != 0) {
          operator delete[](void*)(lVar11);
          *(undefined8 *)(param_1 + 0x40) = 0;
        }
        lVar11 = **(long **)PTR__ZN4Aska6Global19m_pNetworkAllocatorE_02cbc200;
        if (lVar11 == 0) {
          lVar11 = Aska::Global::GetAvailableMemoryManager()();
        }
        lVar11 = Aska::MemoryManager::Malloc(unsigned long)(lVar11,uVar1);
        *(long *)(param_1 + 0x40) = lVar11;
        if (lVar11 == 0) {
          return 0;
        }
        *(ulong *)(param_1 + 0x48) = uVar1;
        uVar20 = uVar1;
      }
      lVar17 = Aska::Encode::UrlEncodeForPOST(signed char const*, unsigned long, signed char*, unsigned long)(uVar13,lVar17,lVar11,uVar20);
      if (lVar17 == 0) {
        return 0;
      }
      lVar7 = uVar20 - lVar17;
      if (lVar7 == 0) {
        return 0;
      }
      lVar2 = *(long *)(param_1 + 0x40) + lVar17;
      lVar12 = Aska::Encode::UrlEncodeForPOST(signed char const*, unsigned long, signed char*, unsigned long)(uVar4,lVar12,lVar2,lVar7);
      if (lVar12 == 0) {
        return 0;
      }
      if (lVar7 == lVar12) {
        return 0;
      }
      memcpy(puVar19,lVar11,lVar17 + -1);
      puVar19[lVar17 + -1] = 0x3d;
      puVar3 = puVar19 + lVar17;
      memcpy(puVar3,lVar2,lVar12 + -1);
      puVar19 = puVar3 + lVar12 + -1 + 1;
      puVar3[lVar12 + -1] = 0x26;
      lVar17 = *(long *)(param_1 + 0x120);
      if (lVar17 == 0) {
        lVar17 = *(long *)(param_1 + 0x110);
        *(long *)(param_1 + 0x120) = lVar17;
        if (lVar17 != 0) goto code_r0x02309d2c;
code_r0x02309d54:
        lVar17 = 0;
code_r0x02309bf4:
        cVar18 = '\x01';
        *(undefined1 *)(param_1 + 0x128) = 1;
        lVar11 = 0;
      }
      else {
code_r0x02309d2c:
        cVar18 = *(char *)(param_1 + 0x128);
        if (cVar18 == '\0') {
          if (lVar17 == *(long *)(param_1 + 0x118)) goto code_r0x02309bf4;
          lVar17 = *(long *)(lVar17 + 0x10);
          cVar18 = '\0';
          *(long *)(param_1 + 0x120) = lVar17;
          lVar11 = lVar17;
          if (lVar17 == 0) goto code_r0x02309d54;
        }
        else {
          lVar11 = 0;
        }
      }
    }
    *(undefined1 *)(param_1 + 0x128) = 1;
code_r0x02309d7c:
    if (lVar9 != 0) {
      memcpy(puVar19,lVar9,lVar10);
      puVar19 = puVar19 + lVar10;
    }
    puVar19[-1] = 0;
    *(undefined1 **)(param_1 + 0x50) = puVar19 + ~(ulong)param_2;
  }
  return uVar15;
}

// ==== Aska::Yayoi::HttpProtocoledData::SetCookie(Aska::TSharedPointer<Aska::Yayoi::Cookie>)
// vaddr 0x2209db0 | ghidra 0x2309db0 | size 216 | symbol _ZN4Aska5Yayoi18HttpProtocoledData9SetCookieENS_14TSharedPointerINS0_6CookieEEE | lib libSOA-3.7.0.so | 2026-10-04
bool _ZN4Aska5Yayoi18HttpProtocoledData9SetCookieENS_14TSharedPointerINS0_6CookieEEE
               (long param_1,long *param_2)

{
  int iVar1;
  char cVar2;
  bool bVar3;
  long lVar4;
  int *piVar5;
  long lVar6;
  long lVar7;
  
  lVar6 = *param_2;
  lVar7 = *(long *)(param_1 + 0x158);
  if (lVar6 == lVar7) goto code_r0x02309e6c;
  piVar5 = *(int **)(param_1 + 0x160);
  lVar4 = lVar7;
  if (piVar5 == (int *)0x0) {
joined_r0x02309e08:
    if (lVar4 != 0) {
      Aska::Yayoi::Cookie::Clear()(lVar4);
      *(undefined **)(lVar4 + 0x30) =
           PTR__ZTVN4Aska8THashMapIPKcS2_NS_5Yayoi6Cookie12StringHasherENS4_13StringEqualToENS_10TAllocatorINS_5TPairIKS2_S2_EEEEEE_02cb9918
           + 0x10;
      if (*(long *)(lVar4 + 0x50) != 0) {
        Aska::MemoryManagerAdapter::AlignedFree(void*)();
      }
      operator delete(void*)(lVar4);
    }
    if (*(long *)(param_1 + 0x160) != 0) {
      Aska::TSharedPointerCode::DeleteCounter(int*)();
    }
  }
  else {
    do {
      iVar1 = *piVar5;
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar5,0x10);
      if (bVar3) {
        *piVar5 = iVar1 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    if (iVar1 + -1 == 0) {
      lVar4 = *(long *)(param_1 + 0x158);
      goto joined_r0x02309e08;
    }
  }
  *(long *)(param_1 + 0x158) = 0;
  *(undefined8 *)(param_1 + 0x160) = 0;
  piVar5 = (int *)param_2[1];
  *(int **)(param_1 + 0x160) = piVar5;
  *(long *)(param_1 + 0x158) = *param_2;
  if (piVar5 != (int *)0x0) {
    do {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar5,0x10);
      if (bVar3) {
        *piVar5 = *piVar5 + 1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
  }
code_r0x02309e6c:
  return lVar6 != lVar7;
}

// ==== Aska::Yayoi::HttpProtocoledData::SetContent(signed char*, unsigned long, bool)
// vaddr 0x2209e88 | ghidra 0x2309e88 | size 56 | symbol _ZN4Aska5Yayoi18HttpProtocoledData10SetContentEPamb | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska5Yayoi18HttpProtocoledData10SetContentEPamb
          (long param_1,undefined8 param_2,undefined8 param_3,byte param_4)

{
  if (*(int *)(param_1 + 300) != 0) {
    return 0;
  }
  *(undefined8 *)(param_1 + 0x28) = param_2;
  *(undefined8 *)(param_1 + 0x50) = param_3;
  *(undefined1 *)(param_1 + 0x134) = 1;
  *(byte *)(param_1 + 0x135) = param_4 & 1;
  *(undefined1 *)(param_1 + 0x131) = 1;
  return 1;
}

// ==== Aska::Yayoi::HttpProtocoledData::ParseContentEncoding(char const*)
// vaddr 0x2209ec0 | ghidra 0x2309ec0 | size 60 | symbol _ZN4Aska5Yayoi18HttpProtocoledData20ParseContentEncodingEPKc | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska5Yayoi18HttpProtocoledData20ParseContentEncodingEPKc(long param_1,undefined8 param_2)

{
  int iVar1;
  
  iVar1 = strcasecmp(param_2,&UNK_029d4500/*"gzip"*/);
  if (iVar1 != 0) {
    return 0;
  }
  *(undefined4 *)(param_1 + 0x88) = 1;
  return 1;
}

// ==== Aska::Yayoi::HttpProtocoledData::ParseContentType(char const*)
// vaddr 0x2209efc | ghidra 0x2309efc | size 736 | symbol _ZN4Aska5Yayoi18HttpProtocoledData16ParseContentTypeEPKc | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska5Yayoi18HttpProtocoledData16ParseContentTypeEPKc(long param_1,char *param_2)

{
  char cVar1;
  char *pcVar2;
  undefined *puVar3;
  int iVar4;
  undefined4 uVar5;
  long lVar6;
  ulong uVar7;
  char acStack_60 [64];
  
  lVar6 = 0;
  cVar1 = *param_2;
  pcVar2 = acStack_60;
  while( true ) {
    if (cVar1 == '\0') {
      return 0;
    }
    param_2 = param_2 + 1;
    if (cVar1 == '/') break;
    lVar6 = lVar6 + 0x100000000;
    *pcVar2 = cVar1;
    cVar1 = *param_2;
    pcVar2 = pcVar2 + 1;
  }
  acStack_60[lVar6 >> 0x20] = '\0';
  *(undefined4 *)(param_1 + 0x80) = 8;
  puVar3 = PTR__ZN4Aska5Yayoi18HttpProtocoledData20CONTENT_TYPE_STRINGSE_02cbd518;
  iVar4 = strcmp(acStack_60,
                          *(undefined8 *)
                           PTR__ZN4Aska5Yayoi18HttpProtocoledData20CONTENT_TYPE_STRINGSE_02cbd518);
  if (iVar4 == 0) {
    uVar5 = 0;
  }
  else {
    iVar4 = strcmp(acStack_60,*(undefined8 *)(puVar3 + 8));
    if (iVar4 == 0) {
      uVar5 = 1;
    }
    else {
      iVar4 = strcmp(acStack_60,*(undefined8 *)(puVar3 + 0x10));
      if (iVar4 == 0) {
        uVar5 = 2;
      }
      else {
        iVar4 = strcmp(acStack_60,*(undefined8 *)(puVar3 + 0x18));
        if (iVar4 == 0) {
          uVar5 = 3;
        }
        else {
          iVar4 = strcmp(acStack_60,*(undefined8 *)(puVar3 + 0x20));
          if (iVar4 == 0) {
            uVar5 = 4;
          }
          else {
            iVar4 = strcmp(acStack_60,*(undefined8 *)(puVar3 + 0x28));
            if (iVar4 == 0) {
              uVar5 = 5;
            }
            else {
              iVar4 = strcmp(acStack_60,*(undefined8 *)(puVar3 + 0x30));
              if (iVar4 == 0) {
                uVar5 = 6;
              }
              else {
                iVar4 = strcmp(acStack_60,*(undefined8 *)(puVar3 + 0x38));
                if (iVar4 != 0) goto code_r0x0230a028;
                uVar5 = 7;
              }
            }
          }
        }
      }
    }
  }
  *(undefined4 *)(param_1 + 0x80) = uVar5;
code_r0x0230a028:
  lVar6 = 0;
  for (uVar7 = 0; cVar1 = param_2[uVar7], cVar1 != ';'; uVar7 = uVar7 + 1) {
    if (cVar1 == '\n') goto code_r0x0230a078;
    if (cVar1 == '\0') break;
    acStack_60[uVar7] = cVar1;
    lVar6 = lVar6 + 0x100000000;
  }
  uVar7 = (ulong)((int)uVar7 + 1);
  acStack_60[lVar6 >> 0x20] = '\r';
code_r0x0230a078:
  (acStack_60 + (int)uVar7)[0] = '\n';
  (acStack_60 + (int)uVar7)[1] = '\0';
  *(undefined4 *)(param_1 + 0x84) = 0xb;
  puVar3 = PTR__ZN4Aska5Yayoi18HttpProtocoledData23CONTENT_SUBTYPE_STRINGSE_02cc0cf8;
  iVar4 = strcmp(acStack_60,
                          *(long *)
                           PTR__ZN4Aska5Yayoi18HttpProtocoledData23CONTENT_SUBTYPE_STRINGSE_02cc0cf8
                          + 1);
  if (iVar4 == 0) {
    uVar5 = 0;
  }
  else {
    iVar4 = strcmp(acStack_60,*(long *)(puVar3 + 8) + 1);
    if (iVar4 == 0) {
      uVar5 = 1;
    }
    else {
      iVar4 = strcmp(acStack_60,*(long *)(puVar3 + 0x10) + 1);
      if (iVar4 == 0) {
        uVar5 = 2;
      }
      else {
        iVar4 = strcmp(acStack_60,*(long *)(puVar3 + 0x18) + 1);
        if (iVar4 == 0) {
          uVar5 = 3;
        }
        else {
          iVar4 = strcmp(acStack_60,*(long *)(puVar3 + 0x20) + 1);
          if (iVar4 == 0) {
            uVar5 = 4;
          }
          else {
            iVar4 = strcmp(acStack_60,*(long *)(puVar3 + 0x28) + 1);
            if (iVar4 == 0) {
              uVar5 = 5;
            }
            else {
              iVar4 = strcmp(acStack_60,*(long *)(puVar3 + 0x30) + 1);
              if (iVar4 == 0) {
                uVar5 = 6;
              }
              else {
                iVar4 = strcmp(acStack_60,*(long *)(puVar3 + 0x38) + 1);
                if (iVar4 == 0) {
                  uVar5 = 7;
                }
                else {
                  iVar4 = strcmp(acStack_60,*(long *)(puVar3 + 0x40) + 1);
                  if (iVar4 == 0) {
                    uVar5 = 8;
                  }
                  else {
                    iVar4 = strcmp(acStack_60,*(long *)(puVar3 + 0x48) + 1);
                    if (iVar4 == 0) {
                      uVar5 = 9;
                    }
                    else {
                      iVar4 = strcmp(acStack_60,*(long *)(puVar3 + 0x50) + 1);
                      if (iVar4 != 0) {
                        return 1;
                      }
                      uVar5 = 10;
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  *(undefined4 *)(param_1 + 0x84) = uVar5;
  return 1;
}

// ==== Aska::Yayoi::HttpProtocoledData::RemoveParam(signed char const*, unsigned long)
// vaddr 0x220a1dc | ghidra 0x230a1dc | size 156 | symbol _ZN4Aska5Yayoi18HttpProtocoledData11RemoveParamEPKam | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi18HttpProtocoledData11RemoveParamEPKam
               (long param_1,undefined8 param_2,long param_3)

{
  long lVar1;
  long *plVar2;
  undefined8 uStack_40;
  long lStack_38;
  
  if (*(char *)(param_1 + 0x134) == '\0') {
    plVar2 = (long *)(param_1 + 0xa0);
    uStack_40 = param_2;
    lStack_38 = param_3;
    lVar1 = (**(code **)(*plVar2 + 0x58))(plVar2,&uStack_40);
    if ((lVar1 != 0) && (lVar1 = *(long *)(lVar1 + 0x48), lVar1 != 0)) {
      *(undefined2 *)(param_1 + 0x131) = 0x101;
      *(long *)(param_1 + 0x60) = (lVar1 + param_3) * -3 + *(long *)(param_1 + 0x60) + -0x18;
      uStack_40 = param_2;
      lStack_38 = param_3;
      (**(code **)(*(long *)(param_1 + 0xa0) + 0x38))(plVar2,&uStack_40);
    }
  }
  return;
}

// ==== Aska::Yayoi::HttpProtocoledData::GetParam(signed char const*, unsigned long, unsigned long*)
// vaddr 0x220a278 | ghidra 0x230a278 | size 76 | symbol _ZN4Aska5Yayoi18HttpProtocoledData8GetParamEPKamPm | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska5Yayoi18HttpProtocoledData8GetParamEPKamPm
          (long param_1,undefined8 param_2,undefined8 param_3,undefined8 *param_4)

{
  undefined8 uVar1;
  long lVar2;
  undefined8 uStack_20;
  undefined8 uStack_18;
  
  if (*(char *)(param_1 + 0x134) == '\0') {
    uStack_20 = param_2;
    uStack_18 = param_3;
    lVar2 = (**(code **)(*(long *)(param_1 + 0xa0) + 0x58))((long *)(param_1 + 0xa0),&uStack_20);
    uVar1 = 0;
    if (lVar2 != 0) {
      *param_4 = *(undefined8 *)(lVar2 + 0x48);
      uVar1 = *(undefined8 *)(lVar2 + 0x40);
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

// ==== Aska::Yayoi::HttpProtocoledData::GetStringParam(char const*, unsigned long*)
// vaddr 0x220a2c4 | ghidra 0x230a2c4 | size 104 | symbol _ZN4Aska5Yayoi18HttpProtocoledData14GetStringParamEPKcPm | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska5Yayoi18HttpProtocoledData14GetStringParamEPKcPm
          (long param_1,undefined8 param_2,undefined8 *param_3)

{
  undefined8 uVar1;
  long lVar2;
  undefined8 uStack_30;
  undefined8 uStack_28;
  
  if (*(char *)(param_1 + 0x134) == '\0') {
    uStack_28 = strlen(param_2);
    uStack_30 = param_2;
    lVar2 = (**(code **)(*(long *)(param_1 + 0xa0) + 0x58))((long *)(param_1 + 0xa0),&uStack_30);
    uVar1 = 0;
    if (lVar2 != 0) {
      *param_3 = *(undefined8 *)(lVar2 + 0x48);
      uVar1 = *(undefined8 *)(lVar2 + 0x40);
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

// ==== Aska::Yayoi::HttpProtocoledData::SetParam(signed char const*, unsigned long, signed char const*, unsigned long)
// vaddr 0x220a32c | ghidra 0x230a32c | size 248 | symbol _ZN4Aska5Yayoi18HttpProtocoledData8SetParamEPKamS3_m | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska5Yayoi18HttpProtocoledData8SetParamEPKamS3_m
          (long param_1,undefined8 param_2,long param_3,undefined8 param_4,long param_5)

{
  long lVar1;
  ulong uVar2;
  long *plVar3;
  undefined8 uStack_50;
  long lStack_48;
  
  if (*(char *)(param_1 + 0x134) == '\0') {
    plVar3 = (long *)(param_1 + 0xa0);
    uStack_50 = param_2;
    lStack_48 = param_3;
    lVar1 = (**(code **)(*plVar3 + 0x58))(plVar3,&uStack_50);
    if ((lVar1 != 0) && (lVar1 = *(long *)(lVar1 + 0x48), lVar1 != 0)) {
      *(undefined2 *)(param_1 + 0x131) = 0x101;
      *(long *)(param_1 + 0x60) = (lVar1 + param_3) * -3 + *(long *)(param_1 + 0x60) + -0x18;
      uStack_50 = param_2;
      lStack_48 = param_3;
      (**(code **)(*(long *)(param_1 + 0xa0) + 0x38))(plVar3,&uStack_50);
    }
    uVar2 = Aska::Yayoi::RawdatHashtable::Set(signed char const*, unsigned long, signed char const*, unsigned long)(plVar3,param_2,param_3,param_4,param_5);
    if ((uVar2 & 1) != 0) {
      *(undefined2 *)(param_1 + 0x131) = 0x101;
      *(long *)(param_1 + 0x60) = (param_5 + param_3) * 3 + *(long *)(param_1 + 0x60) + 0x18;
      return 1;
    }
  }
  return 0;
}

// ==== Aska::Yayoi::HttpProtocoledData::SetStringParam(char const*, char const*)
// vaddr 0x220a424 | ghidra 0x230a424 | size 264 | symbol _ZN4Aska5Yayoi18HttpProtocoledData14SetStringParamEPKcS3_ | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska5Yayoi18HttpProtocoledData14SetStringParamEPKcS3_
          (long param_1,undefined8 param_2,undefined8 param_3)

{
  long lVar1;
  long lVar2;
  long lVar3;
  ulong uVar4;
  long *plVar5;
  undefined8 uStack_50;
  long lStack_48;
  
  lVar1 = strlen(param_2);
  lVar2 = strlen(param_3);
  if (*(char *)(param_1 + 0x134) == '\0') {
    plVar5 = (long *)(param_1 + 0xa0);
    uStack_50 = param_2;
    lStack_48 = lVar1;
    lVar3 = (**(code **)(*plVar5 + 0x58))(plVar5,&uStack_50);
    if ((lVar3 != 0) && (lVar3 = *(long *)(lVar3 + 0x48), lVar3 != 0)) {
      *(undefined2 *)(param_1 + 0x131) = 0x101;
      *(long *)(param_1 + 0x60) = (lVar3 + lVar1) * -3 + *(long *)(param_1 + 0x60) + -0x18;
      uStack_50 = param_2;
      lStack_48 = lVar1;
      (**(code **)(*(long *)(param_1 + 0xa0) + 0x38))(plVar5,&uStack_50);
    }
    uVar4 = Aska::Yayoi::RawdatHashtable::Set(signed char const*, unsigned long, signed char const*, unsigned long)(plVar5,param_2,lVar1,param_3,lVar2);
    if ((uVar4 & 1) != 0) {
      *(undefined2 *)(param_1 + 0x131) = 0x101;
      *(long *)(param_1 + 0x60) = (lVar2 + lVar1) * 3 + *(long *)(param_1 + 0x60) + 0x18;
      return 1;
    }
  }
  return 0;
}

// ==== Aska::Yayoi::HttpProtocoledData::ClearParam()
// vaddr 0x220a52c | ghidra 0x230a52c | size 216 | symbol _ZN4Aska5Yayoi18HttpProtocoledData10ClearParamEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi18HttpProtocoledData10ClearParamEv(long param_1)

{
  ulong uVar1;
  uint uVar2;
  ulong uVar3;
  
  if ((*(char *)(param_1 + 0x134) == '\0') || (*(char *)(param_1 + 0x135) != '\0')) {
    if (*(long *)(param_1 + 0x28) == 0) goto code_r0x0230a568;
    operator delete[](void*)();
  }
  *(undefined8 *)(param_1 + 0x28) = 0;
code_r0x0230a568:
  uVar2 = *(uint *)(param_1 + 0xf8);
  *(undefined1 *)(param_1 + 0x131) = 1;
  *(undefined2 *)(param_1 + 0x134) = 0;
  *(undefined4 *)(param_1 + 0x150) = 0;
  if (uVar2 != 0) {
    (**(code **)(*(long *)(param_1 + 0xa0) + 0x18))(param_1 + 0xa0,*(undefined8 *)(param_1 + 0xf0));
    if (uVar2 != 1) {
      uVar3 = 1;
      do {
        uVar1 = uVar3;
        if (*(uint *)(param_1 + 0xf8) <= uVar3) {
          uVar1 = 0;
        }
        (**(code **)(*(long *)(param_1 + 0xa0) + 0x18))
                  (param_1 + 0xa0,*(long *)(param_1 + 0xf0) + uVar1 * 8);
        uVar3 = uVar3 + 1;
      } while (uVar2 != uVar3);
    }
  }
  *(undefined1 *)(param_1 + 0x128) = 0;
  *(undefined8 *)(param_1 + 0x118) = 0;
  *(undefined8 *)(param_1 + 0x120) = 0;
  *(undefined8 *)(param_1 + 0x110) = 0;
  *(undefined8 *)(param_1 + 0x60) = 0;
  *(undefined2 *)(param_1 + 0x131) = 0x101;
  *(undefined2 *)(param_1 + 0x134) = 0;
  return;
}

// ==== Aska::Yayoi::HttpProtocoledData::GetForecastSize(unsigned long) const
// vaddr 0x220a604 | ghidra 0x230a604 | size 16 | symbol _ZNK4Aska5Yayoi18HttpProtocoledData15GetForecastSizeEm | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK4Aska5Yayoi18HttpProtocoledData15GetForecastSizeEm(long param_1,long param_2)

{
  return param_2 + *(long *)(param_1 + 0x60) + 0x8f;
}
