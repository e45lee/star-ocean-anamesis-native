// port/decomp/yayoi/downloader.c: Ghidra decompiles for the yayoi subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-04 06:29 UTC: tools/decomp.sh '--into' 'yayoi/downloader' '[ :]Aska::Yayoi::Downloader::'

// ==== Aska::Yayoi::Downloader::Download(unsigned int, char const*, Aska::INotify*, char const*, char const*, Aska::Yayoi::Downloader::UriParam const*, unsigned long, Aska::Yayoi::Downloader::IDownloadStream*)
// vaddr 0x21ee0c8 | ghidra 0x22ee0c8 | size 660 | symbol _ZN4Aska5Yayoi10Downloader8DownloadEjPKcPNS_7INotifyES3_S3_PKNS1_8UriParamEmPNS1_15IDownloadStreamE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi10Downloader8DownloadEjPKcPNS_7INotifyES3_S3_PKNS1_8UriParamEmPNS1_15IDownloadStreamE
               (long *param_1,long param_2,undefined4 param_3,char *param_4,undefined8 param_5,
               long param_6,long param_7,undefined8 param_8,undefined8 param_9,undefined8 param_10)

{
  long lVar1;
  int iVar2;
  char cVar3;
  bool bVar4;
  ulong uVar5;
  undefined4 *puVar6;
  int *piVar7;
  undefined4 *puStack_1c8;
  int *piStack_1c0;
  long lStack_1b8;
  long alStack_1b0 [41];
  undefined4 *puStack_68;
  
  if ((param_4 == (char *)0x0) || (*param_4 == '\0')) {
    *param_1 = -1;
    return;
  }
  if (*(char *)(param_2 + 0x560) == '\0') {
code_r0x022ee2b8:
    *param_1 = -0x3bd;
    return;
  }
  uVar5 = Aska::File::DoesExist(char const*, bool)(param_2 + 0x560,0);
  if ((uVar5 & 1) == 0) goto code_r0x022ee2b8;
  puVar6 = (undefined4 *)operator new(unsigned long, std::nothrow_t const&)(0x100,PTR__ZSt7nothrow_02cb9a80);
  if (puVar6 == (undefined4 *)0x0) {
    piVar7 = (int *)0x0;
    puStack_68 = (undefined4 *)0x0;
  }
  else {
    *puVar6 = 5;
    memset(puVar6 + 2,0,0x61);
    Aska::Yayoi::IPAddress::IPAddress()(puVar6 + 0x1c);
    *(undefined1 *)(puVar6 + 0x3e) = 0;
    puStack_68 = (undefined4 *)0x0;
    piVar7 = (int *)Aska::TSharedPointerCode::CreateCounter(int)(0);
    if (piVar7 != (int *)0x0) {
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar7,0x10);
        if (bVar4) {
          *piVar7 = *piVar7 + 1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      puStack_68 = puVar6;
      if (puVar6 != (undefined4 *)0x0) {
        Aska::Yayoi::URI::Deserialize(char const*, unsigned short, Aska::Yayoi::AddressFamily, signed char*, unsigned long)(alStack_1b0,puVar6,param_4,0x50,0,0,0);
        if (alStack_1b0[0] < 0) {
          *param_1 = alStack_1b0[0];
          puVar6 = puStack_68;
          goto joined_r0x022ee344;
        }
        if ((param_6 == 0) &&
           (param_6 = Aska::PathUtil::GetTailName(char const*, unsigned long*)(*(undefined8 *)(puVar6 + 8),alStack_1b0), param_6 == 0)) {
          *param_1 = -1;
          puVar6 = puStack_68;
          goto joined_r0x022ee344;
        }
        lVar1 = param_2 + 0x560;
        if (param_7 != 0) {
          lVar1 = param_7;
        }
        sprintf(alStack_1b0,&UNK_02866ccf/*"%s/%s"*/,lVar1,param_6);
        do {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar7,0x10);
          if (bVar4) {
            *piVar7 = *piVar7 + 1;
            cVar3 = ExclusiveMonitorsStatus();
          }
        } while (cVar3 != '\0');
        puStack_1c8 = puVar6;
        piStack_1c0 = piVar7;
        Aska::Yayoi::Downloader::AddDownloadQueueList(unsigned int, Aska::TSharedPointer<Aska::Yayoi::URI>, Aska::INotify*, char const*, Aska::Yayoi::Downloader::IDownloadStream*, Aska::Yayoi::Downloader::UriParam const*, unsigned long)(&lStack_1b8,param_2,param_3,&puStack_1c8,param_5,alStack_1b0,param_10,
                        param_8,param_9);
        puVar6 = puStack_1c8;
        if (piVar7 == (int *)0x0) {
code_r0x022ee26c:
          if (puStack_1c8 != (undefined4 *)0x0) {
            Aska::Yayoi::URI::DeleteBuffer()(puStack_1c8);
            operator delete(void*)(puVar6);
          }
          if (piStack_1c0 != (int *)0x0) {
            Aska::TSharedPointerCode::DeleteCounter(int*)();
          }
        }
        else {
          do {
            iVar2 = *piVar7;
            cVar3 = '\x01';
            bVar4 = (bool)ExclusiveMonitorPass(piVar7,0x10);
            if (bVar4) {
              *piVar7 = iVar2 + -1;
              cVar3 = ExclusiveMonitorsStatus();
            }
          } while (cVar3 != '\0');
          if (iVar2 + -1 == 0) goto code_r0x022ee26c;
        }
        puStack_1c8 = (undefined4 *)0x0;
        piStack_1c0 = (int *)0x0;
        if (lStack_1b8 < 0) {
          *param_1 = lStack_1b8;
          puVar6 = puStack_68;
        }
        else {
          Aska::Event::Set() const(param_2 + 0x20);
          *param_1 = 0;
          puVar6 = puStack_68;
        }
        goto joined_r0x022ee344;
      }
    }
  }
  *param_1 = -0x3bf;
  puVar6 = puStack_68;
joined_r0x022ee344:
  if (piVar7 != (int *)0x0) {
    do {
      iVar2 = *piVar7;
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar7,0x10);
      if (bVar4) {
        *piVar7 = iVar2 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
    if (iVar2 + -1 != 0) {
      return;
    }
  }
  puStack_68 = puVar6;
  if (puVar6 != (undefined4 *)0x0) {
    Aska::Yayoi::URI::DeleteBuffer()(puVar6);
    operator delete(void*)(puVar6);
  }
  if (piVar7 == (int *)0x0) {
    return;
  }
  Aska::TSharedPointerCode::DeleteCounter(int*)(piVar7);
  return;
}

// ==== Aska::Yayoi::Downloader::AddDownloadQueueList(unsigned int, Aska::TSharedPointer<Aska::Yayoi::URI>, Aska::INotify*, char const*, Aska::Yayoi::Downloader::IDownloadStream*, Aska::Yayoi::Downloader::UriParam const*, unsigned long)
// vaddr 0x21ee35c | ghidra 0x22ee35c | size 812 | symbol _ZN4Aska5Yayoi10Downloader20AddDownloadQueueListEjNS_14TSharedPointerINS0_3URIEEEPNS_7INotifyEPKcPNS1_15IDownloadStreamEPKNS1_8UriParamEm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi10Downloader20AddDownloadQueueListEjNS_14TSharedPointerINS0_3URIEEEPNS_7INotifyEPKcPNS1_15IDownloadStreamEPKNS1_8UriParamEm
               (long *param_1,long param_2,undefined4 param_3,long *param_4,undefined8 param_5,
               undefined8 param_6,undefined8 param_7,undefined8 param_8,undefined8 param_9)

{
  int *piVar1;
  int *piVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined *puVar5;
  uint uVar6;
  char cVar7;
  bool bVar8;
  undefined *puVar9;
  ulong uVar10;
  int iVar11;
  long lVar12;
  long *plVar13;
  long lStack_78;
  int *piStack_70;
  long lStack_68;
  
  piVar1 = (int *)(param_2 + 0x478);
  iVar11 = 0;
code_r0x022ee3a4:
  do {
    if (*piVar1 != -1) {
      ClearExclusiveLocal();
      bVar8 = iVar11 < 0x1ff;
      iVar11 = iVar11 + 1;
      if (bVar8) goto code_r0x022ee3a4;
      piVar2 = (int *)(param_2 + 0x47c);
      do {
        cVar7 = '\x01';
        bVar8 = (bool)ExclusiveMonitorPass(piVar2,0x10);
        if (bVar8) {
          *piVar2 = *piVar2 + 1;
          cVar7 = ExclusiveMonitorsStatus();
        }
      } while (cVar7 != '\0');
      do {
        if (*piVar1 != -1) {
          ClearExclusiveLocal();
          uVar10 = Aska::Semaphore::IsReady() const();
          if ((uVar10 & 1) == 0) goto code_r0x022ee42c;
          do {
            Aska::Semaphore::Wait() const(param_2 + 0x4b8);
            while( true ) {
              do {
                cVar7 = '\x01';
                bVar8 = (bool)ExclusiveMonitorPass(piVar2,0x10);
                if (bVar8) {
                  *piVar2 = *piVar2 + 1;
                  cVar7 = ExclusiveMonitorsStatus();
                }
              } while (cVar7 != '\0');
              while (*piVar1 == -1) {
                cVar7 = '\x01';
                bVar8 = (bool)ExclusiveMonitorPass(piVar1,0x10);
                if (bVar8) {
                  *piVar1 = 0;
                  cVar7 = ExclusiveMonitorsStatus();
                }
                if (cVar7 == '\0') goto code_r0x022ee468;
              }
              ClearExclusiveLocal();
              uVar10 = Aska::Semaphore::IsReady() const(param_2 + 0x4b8);
              if ((uVar10 & 1) != 0) break;
code_r0x022ee42c:
              do {
                cVar7 = '\x01';
                bVar8 = (bool)ExclusiveMonitorPass(piVar2,0x10);
                if (bVar8) {
                  *piVar2 = *piVar2 + -1;
                  cVar7 = ExclusiveMonitorsStatus();
                }
              } while (cVar7 != '\0');
              Aska::Thread::Sleep(unsigned int)(1);
            }
          } while( true );
        }
        cVar7 = '\x01';
        bVar8 = (bool)ExclusiveMonitorPass(piVar1,0x10);
        if (bVar8) {
          *piVar1 = 0;
          cVar7 = ExclusiveMonitorsStatus();
        }
      } while (cVar7 != '\0');
code_r0x022ee468:
      do {
        cVar7 = '\x01';
        bVar8 = (bool)ExclusiveMonitorPass(piVar2,0x10);
        if (bVar8) {
          *piVar2 = *piVar2 + -1;
          cVar7 = ExclusiveMonitorsStatus();
        }
      } while (cVar7 != '\0');
code_r0x022ee478:
      DataMemoryBarrier(2,3);
      uVar6 = 0;
      if (*(int *)(param_2 + 0x3ec) + 1U < *(uint *)(param_2 + 0x3f0)) {
        uVar6 = *(int *)(param_2 + 0x3ec) + 1;
      }
      if (uVar6 == *(uint *)(param_2 + 1000)) {
        lStack_68 = -1;
        goto code_r0x022ee600;
      }
      *(uint *)(param_2 + 0x3ec) = uVar6;
      puVar9 = PTR__ZTVN4Aska4FileE_02cb6e28;
      puVar3 = PTR__ZTVN4Aska5Yayoi10Downloader14DownloadStreamE_02cc1c28 + 0x10;
      puVar4 = PTR__ZTVN4Aska10FileStreamE_02cbc9f8 + 0x10;
      plVar13 = *(long **)(*(long *)(param_2 + 0x3f8) + (ulong)uVar6 * 8);
      puVar5 = PTR__ZTVN4Aska5Yayoi10Downloader15DownloadElementE_02cc0d00 + 0x10;
      plVar13[1] = 0;
      plVar13[2] = 0;
      *plVar13 = (long)puVar5;
      plVar13[6] = 0;
      plVar13[7] = 0;
      plVar13[0x33] = (long)puVar4;
      plVar13[0x32] = (long)puVar3;
      plVar13[0x34] = (long)(puVar9 + 0x10);
      *(undefined1 *)(plVar13 + 0x35) = 0;
      *(undefined1 *)(plVar13 + 0x38) = 0;
      plVar13[0x36] = 0;
      plVar13[0x37] = 0;
      plVar13[0x31] = 0;
      plVar13[0x65] = 0;
      Aska::Yayoi::Downloader::DownloadElement::Reset()(plVar13);
      lStack_78 = *param_4;
      piVar1 = (int *)param_4[1];
      if (piVar1 != (int *)0x0) {
        do {
          cVar7 = '\x01';
          bVar8 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar8) {
            *piVar1 = *piVar1 + 1;
            cVar7 = ExclusiveMonitorsStatus();
          }
        } while (cVar7 != '\0');
      }
      piStack_70 = piVar1;
      Aska::Yayoi::Downloader::DownloadElement::Set(unsigned int, Aska::TSharedPointer<Aska::Yayoi::URI>, Aska::INotify*, char const*, Aska::Yayoi::Downloader::IDownloadStream*, Aska::Yayoi::Downloader::UriParam const*, unsigned long)(&lStack_68,plVar13,param_3,&lStack_78,param_5,param_6,param_7,param_8,param_9)
      ;
      lVar12 = lStack_78;
      if (piVar1 == (int *)0x0) {
code_r0x022ee578:
        if (lStack_78 != 0) {
          Aska::Yayoi::URI::DeleteBuffer()(lStack_78);
          operator delete(void*)(lVar12);
        }
        if (piStack_70 != (int *)0x0) {
          Aska::TSharedPointerCode::DeleteCounter(int*)();
        }
      }
      else {
        do {
          iVar11 = *piVar1;
          cVar7 = '\x01';
          bVar8 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar8) {
            *piVar1 = iVar11 + -1;
            cVar7 = ExclusiveMonitorsStatus();
          }
        } while (cVar7 != '\0');
        if (iVar11 + -1 == 0) goto code_r0x022ee578;
      }
      lStack_78 = 0;
      piStack_70 = (int *)0x0;
      if (lStack_68 < 0) {
        if (*(uint *)(param_2 + 0x3ec) != *(uint *)(param_2 + 1000)) {
          *(long **)(*(long *)(param_2 + 0x3f8) + (ulong)*(uint *)(param_2 + 1000) * 8) = plVar13;
          iVar11 = 0;
          if (*(int *)(param_2 + 1000) + 1U < *(uint *)(param_2 + 0x3f0)) {
            iVar11 = *(int *)(param_2 + 1000) + 1;
          }
          *(int *)(param_2 + 1000) = iVar11;
        }
      }
      else {
        lVar12 = *(long *)(param_2 + 0xa8);
        lStack_68 = 0;
        plVar13[1] = lVar12;
        plVar13[2] = param_2 + 0xa0;
        *(long **)(param_2 + 0xa8) = plVar13;
        *(long **)(lVar12 + 0x10) = plVar13;
        *(int *)(param_2 + 0x3d8) = *(int *)(param_2 + 0x3d8) + 1;
      }
code_r0x022ee600:
      *param_1 = lStack_68;
      DataMemoryBarrier(2,3);
      *(undefined4 *)(param_2 + 0x478) = 0xffffffff;
      DataMemoryBarrier(2,3);
      if (0x14 < *(int *)(param_2 + 0x47c)) {
        piVar1 = (int *)(param_2 + 0x47c);
        do {
          cVar7 = '\x01';
          bVar8 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar8) {
            *piVar1 = *piVar1 + -1;
            cVar7 = ExclusiveMonitorsStatus();
          }
        } while (cVar7 != '\0');
        uVar10 = Aska::Semaphore::IsReady() const(param_2 + 0x4b8);
        if ((uVar10 & 1) != 0) {
          (*(code *)PTR__ZNK4Aska9Semaphore6SignalEv_02c96cd0)(param_2 + 0x4b8);
          return;
        }
      }
      return;
    }
    cVar7 = '\x01';
    bVar8 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar8) {
      *piVar1 = 0;
      cVar7 = ExclusiveMonitorsStatus();
    }
    if (cVar7 == '\0') goto code_r0x022ee478;
  } while( true );
}

// ==== Aska::Yayoi::Downloader::Stop(unsigned int)
// vaddr 0x21ee688 | ghidra 0x22ee688 | size 28 | symbol _ZN4Aska5Yayoi10Downloader4StopEj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi10Downloader4StopEj(long param_1,undefined8 param_2)

{
  Aska::Yayoi::Downloader::OrFlagDownload(unsigned int, unsigned char)(param_1,param_2,1);
  (*(code *)PTR__ZNK4Aska5Event3SetEv_02c9dcf0)(param_1 + 0x20);
  return;
}

// ==== Aska::Yayoi::Downloader::OrFlagDownload(unsigned int, unsigned char)
// vaddr 0x21ee6a4 | ghidra 0x22ee6a4 | size 556 | symbol _ZN4Aska5Yayoi10Downloader14OrFlagDownloadEjh | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi10Downloader14OrFlagDownloadEjh
               (undefined8 *param_1,long param_2,int param_3,byte param_4)

{
  int *piVar1;
  int *piVar2;
  char cVar3;
  bool bVar4;
  ulong uVar5;
  int iVar6;
  long lVar7;
  undefined8 uVar8;
  
  piVar1 = (int *)(param_2 + 0x478);
  iVar6 = 0;
code_r0x022ee6cc:
  do {
    if (*piVar1 != -1) {
      ClearExclusiveLocal();
      bVar4 = iVar6 < 0x1ff;
      iVar6 = iVar6 + 1;
      if (bVar4) goto code_r0x022ee6cc;
      piVar2 = (int *)(param_2 + 0x47c);
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
            uVar5 = Aska::Semaphore::IsReady() const(param_2 + 0x4b8);
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
              Aska::Semaphore::Wait() const(param_2 + 0x4b8);
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
              if (cVar3 == '\0') goto code_r0x022ee784;
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
code_r0x022ee784:
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
        if (bVar4) {
          *piVar2 = *piVar2 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
code_r0x022ee794:
      DataMemoryBarrier(2,3);
      lVar7 = *(long *)(param_2 + 0xb0);
      if (param_3 == -1) {
        for (; param_2 + 0xa0 != lVar7; lVar7 = *(long *)(lVar7 + 0x10)) {
          *(byte *)(lVar7 + 0x331) = *(byte *)(lVar7 + 0x331) | param_4;
        }
        DataMemoryBarrier(2,3);
        *(undefined4 *)(param_2 + 0x478) = 0xffffffff;
        DataMemoryBarrier(2,3);
        if (0x14 < *(int *)(param_2 + 0x47c)) {
          piVar1 = (int *)(param_2 + 0x47c);
          do {
            cVar3 = '\x01';
            bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
            if (bVar4) {
              *piVar1 = *piVar1 + -1;
              cVar3 = ExclusiveMonitorsStatus();
            }
          } while (cVar3 != '\0');
code_r0x022ee84c:
          uVar5 = Aska::Semaphore::IsReady() const(param_2 + 0x4b8);
          if ((uVar5 & 1) != 0) {
            Aska::Semaphore::Signal() const(param_2 + 0x4b8);
          }
        }
      }
      else {
        while( true ) {
          if (param_2 + 0xa0 == lVar7) {
            DataMemoryBarrier(2,3);
            *(undefined4 *)(param_2 + 0x478) = 0xffffffff;
            DataMemoryBarrier(2,3);
            if (0x14 < *(int *)(param_2 + 0x47c)) {
              piVar1 = (int *)(param_2 + 0x47c);
              do {
                cVar3 = '\x01';
                bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
                if (bVar4) {
                  *piVar1 = *piVar1 + -1;
                  cVar3 = ExclusiveMonitorsStatus();
                }
              } while (cVar3 != '\0');
              uVar5 = Aska::Semaphore::IsReady() const(param_2 + 0x4b8);
              if ((uVar5 & 1) != 0) {
                Aska::Semaphore::Signal() const(param_2 + 0x4b8);
              }
            }
            uVar8 = 0xfffffffffffffc38;
            goto code_r0x022ee8b8;
          }
          if (*(int *)(lVar7 + 0x20) == param_3) break;
          lVar7 = *(long *)(lVar7 + 0x10);
        }
        *(byte *)(lVar7 + 0x331) = *(byte *)(lVar7 + 0x331) | param_4;
        DataMemoryBarrier(2,3);
        *(undefined4 *)(param_2 + 0x478) = 0xffffffff;
        DataMemoryBarrier(2,3);
        if (0x14 < *(int *)(param_2 + 0x47c)) {
          piVar1 = (int *)(param_2 + 0x47c);
          do {
            cVar3 = '\x01';
            bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
            if (bVar4) {
              *piVar1 = *piVar1 + -1;
              cVar3 = ExclusiveMonitorsStatus();
            }
          } while (cVar3 != '\0');
          goto code_r0x022ee84c;
        }
      }
      uVar8 = 0;
code_r0x022ee8b8:
      *param_1 = uVar8;
      return;
    }
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar4) {
      *piVar1 = 0;
      cVar3 = ExclusiveMonitorsStatus();
    }
    if (cVar3 == '\0') goto code_r0x022ee794;
  } while( true );
}

// ==== Aska::Yayoi::Downloader::Pause(unsigned int)
// vaddr 0x21ee8d0 | ghidra 0x22ee8d0 | size 28 | symbol _ZN4Aska5Yayoi10Downloader5PauseEj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi10Downloader5PauseEj(long param_1,undefined8 param_2)

{
  Aska::Yayoi::Downloader::OrFlagDownload(unsigned int, unsigned char)(param_1,param_2,2);
  (*(code *)PTR__ZNK4Aska5Event3SetEv_02c9dcf0)(param_1 + 0x20);
  return;
}

// ==== Aska::Yayoi::Downloader::Resume(unsigned int)
// vaddr 0x21ee8ec | ghidra 0x22ee8ec | size 28 | symbol _ZN4Aska5Yayoi10Downloader6ResumeEj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi10Downloader6ResumeEj(long param_1,undefined8 param_2)

{
  Aska::Yayoi::Downloader::OrFlagDownload(unsigned int, unsigned char)(param_1,param_2,4);
  (*(code *)PTR__ZNK4Aska5Event3SetEv_02c9dcf0)(param_1 + 0x20);
  return;
}

// ==== Aska::Yayoi::Downloader::SetPath(char const*)
// vaddr 0x21ee908 | ghidra 0x22ee908 | size 112 | symbol _ZN4Aska5Yayoi10Downloader7SetPathEPKc | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska5Yayoi10Downloader7SetPathEPKc(long param_1,char *param_2)

{
  ulong uVar1;
  
  if (((param_2 != (char *)0x0) && (*param_2 != '\0')) &&
     (uVar1 = strlen(param_2), uVar1 < 0x104)) {
    param_1 = param_1 + 0x560;
    strcpy(param_1,param_2);
    uVar1 = Aska::File::DoesExist(char const*, bool)(param_1,0);
    if (((uVar1 & 1) != 0) || (uVar1 = Aska::File::CreateDirectory(char const*)(param_1), (uVar1 & 1) != 0)) {
      return 1;
    }
  }
  return 0;
}

// ==== Aska::Yayoi::Downloader::GetDownloadStatus(unsigned int, Aska::Yayoi::Downloader::DownloadStatus*) const
// vaddr 0x21ee978 | ghidra 0x22ee978 | size 80 | symbol _ZNK4Aska5Yayoi10Downloader17GetDownloadStatusEjPNS1_14DownloadStatusE | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK4Aska5Yayoi10Downloader17GetDownloadStatusEjPNS1_14DownloadStatusE
               (undefined8 *param_1,undefined8 param_2,undefined8 param_3,long param_4)

{
  long lVar1;
  undefined8 uVar2;
  
  if (param_4 == 0) {
    uVar2 = 0xfffffffffffffc43;
  }
  else {
    lVar1 = Aska::Yayoi::Downloader::QueryDownloadElement(unsigned int) const();
    if ((lVar1 == 0) || (*(long *)(lVar1 + 0x18) == 0)) {
      uVar2 = 0xfffffffffffffc38;
    }
    else {
      Aska::Yayoi::Downloader::DownloadContext::GetDownloadStatus(Aska::Yayoi::Downloader::DownloadStatus*) const(*(long *)(lVar1 + 0x18),param_4);
      uVar2 = 0;
    }
  }
  *param_1 = uVar2;
  return;
}

// ==== Aska::Yayoi::Downloader::QueryDownloadElement(unsigned int) const
// vaddr 0x21ee9c8 | ghidra 0x22ee9c8 | size 376 | symbol _ZNK4Aska5Yayoi10Downloader20QueryDownloadElementEj | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK4Aska5Yayoi10Downloader20QueryDownloadElementEj(long param_1,int param_2)

{
  int *piVar1;
  int *piVar2;
  char cVar3;
  bool bVar4;
  ulong uVar5;
  int iVar6;
  long lVar7;
  
  piVar1 = (int *)(param_1 + 0x478);
  iVar6 = 0;
  do {
    while (*piVar1 == -1) {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = 0;
        cVar3 = ExclusiveMonitorsStatus();
      }
      if (cVar3 == '\0') goto code_r0x022eeaac;
    }
    ClearExclusiveLocal();
    bVar4 = iVar6 < 0x1ff;
    iVar6 = iVar6 + 1;
  } while (bVar4);
  piVar2 = (int *)(param_1 + 0x47c);
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
        uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0x4b8);
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
          Aska::Semaphore::Wait() const(param_1 + 0x4b8);
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
          if (cVar3 == '\0') goto code_r0x022eea9c;
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
code_r0x022eea9c:
  do {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar4) {
      *piVar2 = *piVar2 + -1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
code_r0x022eeaac:
  DataMemoryBarrier(2,3);
  for (lVar7 = *(long *)(param_1 + 0xb0); param_1 + 0xa0 != lVar7; lVar7 = *(long *)(lVar7 + 0x10))
  {
    if (*(int *)(lVar7 + 0x20) == param_2) goto code_r0x022eeae4;
  }
  lVar7 = 0;
code_r0x022eeae4:
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_1 + 0x478) = 0xffffffff;
  DataMemoryBarrier(2,3);
  if (0x14 < *(int *)(param_1 + 0x47c)) {
    piVar1 = (int *)(param_1 + 0x47c);
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
    uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0x4b8);
    if ((uVar5 & 1) != 0) {
      Aska::Semaphore::Signal() const(param_1 + 0x4b8);
    }
  }
  return lVar7;
}

// ==== Aska::Yayoi::Downloader::DownloadContext::GetDownloadStatus(Aska::Yayoi::Downloader::DownloadStatus*) const
// vaddr 0x21eeb40 | ghidra 0x22eeb40 | size 360 | symbol _ZNK4Aska5Yayoi10Downloader15DownloadContext17GetDownloadStatusEPNS1_14DownloadStatusE | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK4Aska5Yayoi10Downloader15DownloadContext17GetDownloadStatusEPNS1_14DownloadStatusE
               (long param_1,long param_2)

{
  int *piVar1;
  int *piVar2;
  char cVar3;
  bool bVar4;
  ulong uVar5;
  int iVar6;
  
  if (param_2 == 0) {
    return;
  }
  piVar1 = (int *)(param_1 + 0x4c0);
  iVar6 = 0;
  do {
    while (*piVar1 != -1) {
      ClearExclusiveLocal();
      bVar4 = 0x1fe < iVar6;
      iVar6 = iVar6 + 1;
      if (bVar4) {
        piVar2 = (int *)(param_1 + 0x4c4);
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
              uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0x500);
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
                Aska::Semaphore::Wait() const(param_1 + 0x500);
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
                if (cVar3 == '\0') goto code_r0x022eec90;
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
code_r0x022eec90:
        do {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
          if (bVar4) {
            *piVar2 = *piVar2 + -1;
            cVar3 = ExclusiveMonitorsStatus();
          }
        } while (cVar3 != '\0');
        DataMemoryBarrier(2,3);
        goto code_r0x022eebbc;
      }
    }
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar4) {
      *piVar1 = 0;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
  DataMemoryBarrier(2,3);
code_r0x022eebbc:
  memcpy(param_2,param_1 + 0x518,0x160);
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_1 + 0x4c0) = 0xffffffff;
  DataMemoryBarrier(2,3);
  piVar1 = (int *)(param_1 + 0x4c4);
  if (*piVar1 < 0x15) {
    return;
  }
  do {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar4) {
      *piVar1 = *piVar1 + -1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
  uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0x500);
  if ((uVar5 & 1) == 0) {
    return;
  }
  (*(code *)PTR__ZNK4Aska9Semaphore6SignalEv_02c96cd0)(param_1 + 0x500);
  return;
}

// ==== Aska::Yayoi::Downloader::Downloader()
// vaddr 0x21eeca8 | ghidra 0x22eeca8 | size 356 | symbol _ZN4Aska5Yayoi10DownloaderC2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi10DownloaderC1Ev(long *param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  undefined *puVar3;
  long *plVar4;
  
  *param_1 = (long)(PTR__ZTVN4Aska5Yayoi10DownloaderE_02cbb190 + 0x10);
  Aska::Thread::Thread()(param_1 + 1);
  param_1[1] = (long)(
                     PTR__ZTVN4Aska17TWorkerThreadBaseINS_5Yayoi10Downloader12WorkerThreadEEE_02cbbb98
                     + 0x10);
  Aska::Event::Event()(param_1 + 4);
  *(undefined1 *)(param_1 + 0x11) = 0;
  *(undefined1 *)((long)param_1 + 0x89) = 0;
  puVar3 = PTR__ZTVN4Aska5Yayoi10Downloader12WorkerThreadE_02cc3e18;
  puVar2 = PTR__ZTVN4Aska5TListINS_5Yayoi10Downloader15DownloadElementEEE_02cc20b8;
  param_1[0x15] = 0;
  param_1[0x16] = 0;
  puVar1 = PTR__ZTVN4Aska5Yayoi10Downloader15DownloadElementE_02cc0d00;
  param_1[1] = (long)(puVar3 + 0x10);
  param_1[0x12] = (long)param_1;
  param_1[0x13] = (long)(puVar2 + 0x10);
  puVar2 = PTR__ZTVN4Aska5Yayoi10Downloader14DownloadStreamE_02cc1c28;
  plVar4 = param_1 + 0x14;
  *plVar4 = (long)(puVar1 + 0x10);
  param_1[0x48] = (long)(PTR__ZTVN4Aska4FileE_02cb6e28 + 0x10);
  puVar1 = PTR__ZTVN4Aska10FileStreamE_02cbc9f8;
  param_1[0x1a] = 0;
  param_1[0x1b] = 0;
  *(undefined1 *)(param_1 + 0x49) = 0;
  *(undefined1 *)(param_1 + 0x4c) = 0;
  param_1[0x4b] = 0;
  param_1[0x4a] = 0;
  param_1[0x45] = 0;
  param_1[0x47] = (long)(puVar1 + 0x10);
  param_1[0x46] = (long)(puVar2 + 0x10);
  param_1[0x79] = 0;
  Aska::Yayoi::Downloader::DownloadElement::Reset()(plVar4);
  *(undefined4 *)(param_1 + 0x7b) = 0;
  param_1[0x15] = (long)plVar4;
  param_1[0x16] = (long)plVar4;
  puVar1 = PTR__ZTVN4Aska13TDynamicQueueIPNS_5Yayoi10Downloader15DownloadElementELb0EEE_02cb88b8;
  *(undefined4 *)(param_1 + 0x7e) = 0;
  param_1[0x7f] = 0;
  param_1[0x7d] = 1;
  param_1[0x81] = 1;
  param_1[0x85] = 1;
  puVar2 = PTR__ZTVN4Aska13TDynamicQueueIPNS_5Yayoi10Downloader15DownloadContextELb0EEE_02cba150;
  *(undefined4 *)(param_1 + 0x82) = 0;
  param_1[0x83] = 0;
  param_1[0x7c] = (long)(puVar1 + 0x10);
  puVar1 = PTR__ZTVN4Aska13TDynamicQueueIjLb0EEE_02cc16b8;
  *(undefined4 *)(param_1 + 0x86) = 0;
  param_1[0x87] = 0;
  param_1[0x80] = (long)(puVar2 + 0x10);
  param_1[0x84] = (long)(puVar1 + 0x10);
  Aska::FastCriticalSection::FastCriticalSection()(param_1 + 0x88);
  Aska::FastCriticalSection::FastCriticalSection()(param_1 + 0x9a);
  param_1[0xcd] = 0;
  *(undefined4 *)(param_1 + 0xce) = 0;
  *(undefined8 *)((long)param_1 + 0x674) = 0;
  *(undefined1 *)(param_1 + 0xac) = 0;
  return;
}

// ==== Aska::Yayoi::Downloader::~Downloader()
// vaddr 0x21eee0c | ghidra 0x22eee0c | size 152 | symbol _ZN4Aska5Yayoi10DownloaderD2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi10DownloaderD1Ev(long *param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  
  *param_1 = (long)(PTR__ZTVN4Aska5Yayoi10DownloaderE_02cbb190 + 0x10);
  Aska::Yayoi::Downloader::Term()();
  Aska::FastCriticalSection::~FastCriticalSection()(param_1 + 0x9a);
  Aska::FastCriticalSection::~FastCriticalSection()(param_1 + 0x88);
  puVar1 = PTR__ZTVN4Aska13TDynamicQueueIjLb0EEE_02cc16b8;
  *(undefined4 *)(param_1 + 0x86) = 0;
  param_1[0x87] = 0;
  param_1[0x85] = 1;
  param_1[0x81] = 1;
  param_1[0x7d] = 1;
  puVar2 = PTR__ZTVN4Aska13TDynamicQueueIPNS_5Yayoi10Downloader15DownloadContextELb0EEE_02cba150;
  *(undefined4 *)(param_1 + 0x82) = 0;
  param_1[0x83] = 0;
  param_1[0x84] = (long)(puVar1 + 0x10);
  puVar1 = PTR__ZTVN4Aska13TDynamicQueueIPNS_5Yayoi10Downloader15DownloadElementELb0EEE_02cb88b8;
  *(undefined4 *)(param_1 + 0x7e) = 0;
  param_1[0x7f] = 0;
  param_1[0x80] = (long)(puVar2 + 0x10);
  param_1[0x7c] = (long)(puVar1 + 0x10);
  Aska::TList<Aska::Yayoi::Downloader::DownloadElement>::~TList()(param_1 + 0x13);
  (*(code *)PTR__ZN4Aska5Yayoi10Downloader12WorkerThreadD2Ev_02cb2fa0)(param_1 + 1);
  return;
}

// ==== Aska::Yayoi::Downloader::Term()
// vaddr 0x21eeea4 | ghidra 0x22eeea4 | size 564 | symbol _ZN4Aska5Yayoi10Downloader4TermEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi10Downloader4TermEv(long param_1)

{
  int *piVar1;
  int *piVar2;
  char cVar3;
  bool bVar4;
  ulong uVar5;
  int iVar6;
  undefined8 *puVar7;
  undefined8 *puVar8;
  
  if (-1 < *(int *)(param_1 + 0x674)) {
    puVar7 = (undefined8 *)
             (*(long *)(param_1 + 0x668) + (long)*(int *)(param_1 + 0x678) * 0x344 + 0x344);
    puVar8 = puVar7 + (long)(*(int *)(param_1 + 0x674) + 1) * 0xd2;
    do {
      (**(code **)*puVar7)(puVar7);
      puVar7 = puVar7 + 0xd2;
    } while (puVar7 < puVar8);
  }
  piVar1 = (int *)(param_1 + 0x478);
  iVar6 = 0;
  do {
    while (*piVar1 == -1) {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = 0;
        cVar3 = ExclusiveMonitorsStatus();
      }
      if (cVar3 == '\0') goto code_r0x022eefc8;
    }
    ClearExclusiveLocal();
    bVar4 = iVar6 < 0x1ff;
    iVar6 = iVar6 + 1;
  } while (bVar4);
  piVar2 = (int *)(param_1 + 0x47c);
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
        uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0x4b8);
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
          Aska::Semaphore::Wait() const(param_1 + 0x4b8);
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
          if (cVar3 == '\0') goto code_r0x022eefb8;
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
code_r0x022eefb8:
  do {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar4) {
      *piVar2 = *piVar2 + -1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
code_r0x022eefc8:
  DataMemoryBarrier(2,3);
  if (param_1 + 0xa0 != *(long *)(param_1 + 0xb0)) {
    do {
      (**(code **)(*(long *)(param_1 + 0x98) + 0x28))(param_1 + 0x98);
    } while (param_1 + 0xa0 != *(long *)(param_1 + 0xb0));
  }
  *(undefined4 *)(param_1 + 0x3d8) = 0;
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_1 + 0x478) = 0xffffffff;
  DataMemoryBarrier(2,3);
  if (0x14 < *(int *)(param_1 + 0x47c)) {
    piVar1 = (int *)(param_1 + 0x47c);
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
    uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0x4b8);
    if ((uVar5 & 1) != 0) {
      Aska::Semaphore::Signal() const(param_1 + 0x4b8);
    }
  }
  *(undefined8 *)(param_1 + 0x428) = 1;
  *(undefined4 *)(param_1 + 0x430) = 0;
  *(undefined8 *)(param_1 + 0x438) = 0;
  if (*(long *)(param_1 + 0x668) != 0) {
    operator delete[](void*)();
    *(undefined8 *)(param_1 + 0x668) = 0;
  }
  *(undefined4 *)(param_1 + 0x670) = 0;
  *(undefined8 *)(param_1 + 0x674) = 0;
  if ((((*(char *)(param_1 + 0x88) != '\0') || (*(char *)(param_1 + 0x89) != '\0')) &&
      (*(char *)(param_1 + 0x88) != '\0')) && (*(char *)(param_1 + 0x89) == '\0')) {
    *(undefined1 *)(param_1 + 0x89) = 1;
    Aska::Event::Set() const(param_1 + 0x20);
    Aska::Thread::WaitEnd()(param_1 + 8);
    Aska::Event::Exit()(param_1 + 0x20);
    Aska::Thread::Delete()(param_1 + 8);
    *(undefined1 *)(param_1 + 0x88) = 0;
  }
  return;
}

// ==== Aska::Yayoi::Downloader::WorkerThread::~WorkerThread()
// vaddr 0x21ef208 | ghidra 0x22ef208 | size 148 | symbol _ZN4Aska5Yayoi10Downloader12WorkerThreadD2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi10Downloader12WorkerThreadD2Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska5Yayoi10Downloader12WorkerThreadE_02cc3e18 + 0x10);
  if (((((char)param_1[0x10] != '\0') || (*(char *)((long)param_1 + 0x81) != '\0')) &&
      ((char)param_1[0x10] != '\0')) && (*(char *)((long)param_1 + 0x81) == '\0')) {
    *(undefined1 *)((long)param_1 + 0x81) = 1;
    Aska::Event::Set() const(param_1 + 3);
    Aska::Thread::WaitEnd()(param_1);
    Aska::Event::Exit()(param_1 + 3);
    Aska::Thread::Delete()(param_1);
    *(undefined1 *)(param_1 + 0x10) = 0;
  }
  *param_1 = (long)(
                   PTR__ZTVN4Aska17TWorkerThreadBaseINS_5Yayoi10Downloader12WorkerThreadEEE_02cbbb98
                   + 0x10);
  Aska::Event::Exit()(param_1 + 3);
  (*(code *)PTR__ZN4Aska6ThreadD1Ev_02c9be08)(param_1);
  return;
}

// ==== Aska::Yayoi::Downloader::~Downloader()
// vaddr 0x21ef29c | ghidra 0x22ef29c | size 160 | symbol _ZN4Aska5Yayoi10DownloaderD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi10DownloaderD0Ev(long *param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  
  *param_1 = (long)(PTR__ZTVN4Aska5Yayoi10DownloaderE_02cbb190 + 0x10);
  Aska::Yayoi::Downloader::Term()();
  Aska::FastCriticalSection::~FastCriticalSection()(param_1 + 0x9a);
  Aska::FastCriticalSection::~FastCriticalSection()(param_1 + 0x88);
  puVar1 = PTR__ZTVN4Aska13TDynamicQueueIjLb0EEE_02cc16b8;
  *(undefined4 *)(param_1 + 0x86) = 0;
  param_1[0x87] = 0;
  param_1[0x85] = 1;
  param_1[0x81] = 1;
  param_1[0x7d] = 1;
  puVar2 = PTR__ZTVN4Aska13TDynamicQueueIPNS_5Yayoi10Downloader15DownloadContextELb0EEE_02cba150;
  *(undefined4 *)(param_1 + 0x82) = 0;
  param_1[0x83] = 0;
  param_1[0x84] = (long)(puVar1 + 0x10);
  puVar1 = PTR__ZTVN4Aska13TDynamicQueueIPNS_5Yayoi10Downloader15DownloadElementELb0EEE_02cb88b8;
  *(undefined4 *)(param_1 + 0x7e) = 0;
  param_1[0x7f] = 0;
  param_1[0x80] = (long)(puVar2 + 0x10);
  param_1[0x7c] = (long)(puVar1 + 0x10);
  Aska::TList<Aska::Yayoi::Downloader::DownloadElement>::~TList()(param_1 + 0x13);
  Aska::Yayoi::Downloader::WorkerThread::~WorkerThread()(param_1 + 1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::Yayoi::Downloader::Init(int, int)
// vaddr 0x21ef33c | ghidra 0x22ef33c | size 1604 | symbol _ZN4Aska5Yayoi10Downloader4InitEii | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi10Downloader4InitEii(undefined8 *param_1,long param_2,int param_3,int param_4)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int *piVar4;
  undefined *puVar5;
  undefined *puVar6;
  undefined *puVar7;
  long lVar8;
  char cVar9;
  bool bVar10;
  bool bVar11;
  ulong uVar12;
  ulong uVar13;
  int iVar14;
  uint uVar15;
  undefined1 *puVar16;
  ulong uVar17;
  undefined1 *puVar18;
  ulong uVar19;
  undefined8 uVar20;
  undefined1 *puVar21;
  long lVar22;
  undefined1 *puVar23;
  
  uVar20 = 0xfffffffffffffc43;
  if ((param_3 != 0) && (param_4 != 0)) {
    if (*(long *)(param_2 + 0x668) != 0) {
      Aska::Yayoi::Downloader::Term()(param_2);
    }
    *(undefined4 *)(param_2 + 0x670) = 0;
    *(int *)(param_2 + 0x674) = param_3;
    *(int *)(param_2 + 0x678) = param_4;
    iVar1 = param_3 + 1;
    iVar2 = param_4 + 1;
    uVar12 = operator new[](unsigned long, std::nothrow_t const&)((long)iVar1 * 0x698 + (long)iVar2 * 0x344,PTR__ZSt7nothrow_02cb9a80);
    *(ulong *)(param_2 + 0x668) = uVar12;
    if (uVar12 != 0) {
      lVar22 = (long)iVar2;
      uVar19 = uVar12 + lVar22 * 0x338;
      lVar8 = uVar19 + lVar22 * 8;
      puVar21 = (undefined1 *)(lVar8 + lVar22 * 4);
      puVar16 = puVar21 + (long)iVar1 * 0x690;
      piVar3 = (int *)(param_2 + 0x478);
      iVar14 = 0;
code_r0x022ef3fc:
      do {
        if (*piVar3 == -1) goto code_r0x022ef408;
        ClearExclusiveLocal();
        bVar10 = iVar14 < 0x1ff;
        iVar14 = iVar14 + 1;
      } while (bVar10);
      piVar4 = (int *)(param_2 + 0x47c);
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
          ClearExclusiveLocal();
          uVar13 = Aska::Semaphore::IsReady() const();
          if ((uVar13 & 1) == 0) goto code_r0x022ef48c;
          do {
            Aska::Semaphore::Wait() const(param_2 + 0x4b8);
            while( true ) {
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
                if (cVar9 == '\0') goto code_r0x022ef4c8;
              }
              ClearExclusiveLocal();
              uVar13 = Aska::Semaphore::IsReady() const(param_2 + 0x4b8);
              if ((uVar13 & 1) != 0) break;
code_r0x022ef48c:
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
          } while( true );
        }
        cVar9 = '\x01';
        bVar10 = (bool)ExclusiveMonitorPass(piVar3,0x10);
        if (bVar10) {
          *piVar3 = 0;
          cVar9 = ExclusiveMonitorsStatus();
        }
      } while (cVar9 != '\0');
code_r0x022ef4c8:
      do {
        cVar9 = '\x01';
        bVar10 = (bool)ExclusiveMonitorPass(piVar4,0x10);
        if (bVar10) {
          *piVar4 = *piVar4 + -1;
          cVar9 = ExclusiveMonitorsStatus();
        }
      } while (cVar9 != '\0');
code_r0x022ef4d8:
      DataMemoryBarrier(2,3);
      bVar10 = true;
      uVar20 = 0xffffffffffffffff;
      if ((-1 < param_4) && (uVar19 != 0)) {
        *(ulong *)(param_2 + 0x3f8) = uVar19;
        *(int *)(param_2 + 0x3f0) = iVar2;
        *(undefined8 *)(param_2 + 1000) = 1;
        if (uVar12 < uVar19) {
          uVar13 = uVar12 + 0x338;
          uVar15 = 1;
          uVar17 = uVar12;
          do {
            *(ulong *)(*(long *)(param_2 + 0x3f8) + (ulong)uVar15 * 8) = uVar17;
            uVar15 = 0;
            if (*(int *)(param_2 + 1000) + 1U < *(uint *)(param_2 + 0x3f0)) {
              uVar15 = *(int *)(param_2 + 1000) + 1;
            }
            *(uint *)(param_2 + 1000) = uVar15;
            do {
              uVar17 = uVar13;
              if (uVar19 <= uVar17) goto code_r0x022ef55c;
              uVar13 = uVar17 + 0x338;
            } while (*(uint *)(param_2 + 0x3ec) == uVar15);
          } while( true );
        }
code_r0x022ef55c:
        uVar20 = 0;
        bVar10 = false;
      }
      DataMemoryBarrier(2,3);
      *(undefined4 *)(param_2 + 0x478) = 0xffffffff;
      DataMemoryBarrier(2,3);
      if (0x14 < *(int *)(param_2 + 0x47c)) {
        piVar3 = (int *)(param_2 + 0x47c);
        do {
          cVar9 = '\x01';
          bVar11 = (bool)ExclusiveMonitorPass(piVar3,0x10);
          if (bVar11) {
            *piVar3 = *piVar3 + -1;
            cVar9 = ExclusiveMonitorsStatus();
          }
        } while (cVar9 != '\0');
        uVar19 = Aska::Semaphore::IsReady() const(param_2 + 0x4b8);
        if ((uVar19 & 1) != 0) {
          Aska::Semaphore::Signal() const(param_2 + 0x4b8);
        }
      }
      if (((!bVar10) && (uVar20 = 0xffffffffffffffff, -1 < param_4)) && (lVar8 != 0)) {
        uVar20 = 0xffffffffffffffff;
        *(int *)(param_2 + 0x430) = iVar2;
        *(long *)(param_2 + 0x438) = lVar8;
        *(undefined8 *)(param_2 + 0x428) = 1;
        if ((-1 < param_3) && (puVar16 != (undefined1 *)0x0)) {
          *(int *)(param_2 + 0x410) = iVar1;
          *(undefined8 *)(param_2 + 0x408) = 1;
          *(undefined1 **)(param_2 + 0x418) = puVar16;
          if (puVar21 < puVar16) {
            puVar5 = PTR__ZTVN4Aska5Yayoi10Downloader15DownloadContextE_02cbee80 + 0x10;
            puVar6 = PTR__ZTVN4Aska5Yayoi11THttpClientINS0_3TCPELi5EEE_02cc2e80 + 0x10;
            puVar7 = PTR__ZTVN4Aska6TQueueINS_5Yayoi11SSLProtocol11RecordLayerELi10EEE_02cbc400 +
                     0x10;
            puVar23 = (undefined1 *)(uVar12 + lVar22 * 0x344 + 0x348);
            do {
              puVar18 = puVar23 + -0x330;
              *(undefined **)(puVar23 + -0x348) = puVar5;
              *(undefined **)(puVar23 + -0x338) = puVar6;
              Aska::Yayoi::HttpProtocol::HttpProtocol()(puVar18);
              puVar23[-0x2e8] = 0;
              *(undefined **)(puVar23 + -0x2e0) = puVar7;
              *(undefined4 *)(puVar23 + -0x2d8) = 1;
              *(undefined4 *)(puVar23 + -0x2d4) = 0;
              *(undefined8 *)(puVar23 + -0x2b8) = 0;
              puVar23[-0x2b0] = 0;
              *(undefined8 *)(puVar23 + -0x2c8) = 0;
              *(undefined8 *)(puVar23 + -0x2d0) = 0;
              puVar23[-0x2c0] = 0;
              *(undefined8 *)(puVar23 + -0x290) = 0;
              puVar23[-0x288] = 0;
              *(undefined8 *)(puVar23 + -0x2a0) = 0;
              *(undefined8 *)(puVar23 + -0x2a8) = 0;
              puVar23[-0x298] = 0;
              *(undefined8 *)(puVar23 + -0x268) = 0;
              puVar23[-0x260] = 0;
              *(undefined8 *)(puVar23 + -0x278) = 0;
              *(undefined8 *)(puVar23 + -0x280) = 0;
              puVar23[-0x270] = 0;
              *(undefined8 *)(puVar23 + -0x240) = 0;
              puVar23[-0x238] = 0;
              puVar23[-0x248] = 0;
              *(undefined8 *)(puVar23 + -0x250) = 0;
              *(undefined8 *)(puVar23 + -600) = 0;
              *(undefined8 *)(puVar23 + -0x218) = 0;
              puVar23[-0x210] = 0;
              puVar23[-0x220] = 0;
              *(undefined8 *)(puVar23 + -0x228) = 0;
              *(undefined8 *)(puVar23 + -0x230) = 0;
              *(undefined8 *)(puVar23 + -0x1f0) = 0;
              puVar23[-0x1e8] = 0;
              puVar23[-0x1f8] = 0;
              *(undefined8 *)(puVar23 + -0x200) = 0;
              *(undefined8 *)(puVar23 + -0x208) = 0;
              *(undefined8 *)(puVar23 + -0x1c8) = 0;
              puVar23[-0x1c0] = 0;
              puVar23[-0x1d0] = 0;
              *(undefined8 *)(puVar23 + -0x1d8) = 0;
              *(undefined8 *)(puVar23 + -0x1e0) = 0;
              *(undefined8 *)(puVar23 + -0x1a0) = 0;
              puVar23[-0x198] = 0;
              puVar23[-0x1a8] = 0;
              *(undefined8 *)(puVar23 + -0x1b0) = 0;
              *(undefined8 *)(puVar23 + -0x1b8) = 0;
              *(undefined8 *)(puVar23 + -0x178) = 0;
              puVar23[-0x170] = 0;
              puVar23[-0x180] = 0;
              *(undefined8 *)(puVar23 + -0x188) = 0;
              *(undefined8 *)(puVar23 + -400) = 0;
              *(undefined8 *)(puVar23 + -0x150) = 0;
              puVar23[-0x148] = 0;
              puVar23[-0x158] = 0;
              *(undefined8 *)(puVar23 + -0x160) = 0;
              *(undefined8 *)(puVar23 + -0x168) = 0;
              *(undefined8 *)(puVar23 + -0x128) = 0;
              puVar23[-0x120] = 0;
              puVar23[-0x130] = 0;
              *(undefined8 *)(puVar23 + -0x138) = 0;
              *(undefined8 *)(puVar23 + -0x140) = 0;
              *(undefined8 *)(puVar23 + -0x110) = 0;
              *(undefined8 *)(puVar23 + -0x118) = 0;
              *(undefined8 *)(puVar23 + -0xf8) = 0;
              *(undefined8 *)(puVar23 + -0x100) = 0;
              *(undefined8 *)(puVar23 + -0xa8) = 0;
              *(undefined8 *)(puVar23 + -0xb0) = 0;
              *(undefined8 *)(puVar23 + -0x50) = 0;
              *(undefined8 *)(puVar23 + -0x68) = 0;
              *(undefined8 *)(puVar23 + -0x70) = 0;
              *(undefined8 *)(puVar23 + -0x58) = 0;
              *(undefined8 *)(puVar23 + -0x60) = 0;
              *(undefined2 *)(puVar23 + -0x30) = 0;
              *(undefined8 *)(puVar23 + -0x38) = 0;
              *(undefined8 *)(puVar23 + -0x40) = 0;
              *(undefined8 *)(puVar23 + -0x20) = 0;
              *(undefined8 *)(puVar23 + -0x28) = 0;
              *(undefined2 *)(puVar23 + -0x18) = 0x301;
              *(undefined8 *)(puVar23 + -8) = 0;
              *(undefined8 *)(puVar23 + -0x10) = 0;
              *puVar23 = 1;
              puVar23[8] = 1;
              puVar23[0x30] = 0;
              *(undefined8 *)(puVar23 + 0x18) = 0;
              *(undefined8 *)(puVar23 + 0x10) = 0;
              *(undefined8 *)(puVar23 + 0x28) = 0;
              *(undefined8 *)(puVar23 + 0x20) = 0;
              memset(puVar23 + 0x34,0,0x54);
              Aska::Yayoi::IPAddress::IPAddress()(puVar23 + 0x90);
              puVar23[0x118] = 0;
              *(undefined8 *)(puVar23 + 0x130) = 0;
              *(undefined8 *)(puVar23 + 0x128) = 0;
              *(undefined8 *)(puVar23 + 0x120) = 0;
              *(undefined4 *)(puVar23 + 0x138) = 0;
              Aska::FastCriticalSection::FastCriticalSection()(puVar23 + 0x140);
              puVar23[0x1d0] = 0;
              *(undefined8 *)(puVar23 + 0x33d) = 0;
              *(undefined8 *)(puVar23 + 0x338) = 0;
              *(undefined8 *)(puVar23 + 0x330) = 0;
              *(undefined8 *)(puVar23 + 0x328) = 0;
              *(undefined8 *)(puVar23 + 800) = 0;
              *(undefined8 *)(puVar23 + 0x318) = 0;
              if (puVar23[0x118] == '\0') {
                *(undefined1 **)(puVar23 + 0x120) = puVar23 + -0x2e8;
                *(undefined1 **)(puVar23 + 0x128) = puVar18;
                *(undefined8 *)(puVar23 + 0x28) = 0;
                puVar23[0x118] = 1;
code_r0x022ef8bc:
                puVar18[0x30] = 0;
              }
              else {
                puVar18 = *(undefined1 **)(puVar23 + 0x128);
                if (puVar18 != (undefined1 *)0x0) goto code_r0x022ef8bc;
              }
              puVar23[0x344] = 1;
              if (*(uint *)(param_2 + 0x40c) != *(uint *)(param_2 + 0x408)) {
                *(undefined1 **)(*(long *)(param_2 + 0x418) + (ulong)*(uint *)(param_2 + 0x408) * 8)
                     = puVar21;
                iVar1 = 0;
                if (*(int *)(param_2 + 0x408) + 1U < *(uint *)(param_2 + 0x410)) {
                  iVar1 = *(int *)(param_2 + 0x408) + 1;
                }
                *(int *)(param_2 + 0x408) = iVar1;
              }
              puVar21 = puVar23 + 0x348;
              puVar23 = puVar23 + 0x690;
            } while (puVar21 < puVar16);
          }
          if ((*(char *)(param_2 + 0x88) == '\0') || (*(char *)(param_2 + 0x89) != '\0')) {
            if (*(char *)(param_2 + 0x88) != '\0') {
              uVar20 = 0;
              goto code_r0x022ef5bc;
            }
            *(undefined1 *)(param_2 + 0x89) = 0;
            uVar12 = Aska::Event::Create(bool, bool)(param_2 + 0x20,0,0);
            if (((uVar12 & 1) != 0) &&
               (uVar12 = Aska::Thread::Create(bool, int, int, bool)(param_2 + 8,0,0x7f,0xc000,1), (uVar12 & 1) != 0)) {
              uVar20 = 0;
              *(undefined1 *)(param_2 + 0x88) = 1;
              goto code_r0x022ef5bc;
            }
            uVar20 = 0xffffffffffffffff;
          }
          else {
            uVar20 = 0xfffffffffffffc52;
          }
        }
      }
      goto code_r0x022ef5b4;
    }
    uVar20 = 0xfffffffffffffc41;
code_r0x022ef5b4:
    Aska::Yayoi::Downloader::Term()(param_2);
  }
code_r0x022ef5bc:
  *param_1 = uVar20;
  return;
code_r0x022ef408:
  cVar9 = '\x01';
  bVar10 = (bool)ExclusiveMonitorPass(piVar3,0x10);
  if (bVar10) {
    *piVar3 = 0;
    cVar9 = ExclusiveMonitorsStatus();
  }
  if (cVar9 == '\0') goto code_r0x022ef4d8;
  goto code_r0x022ef3fc;
}

// ==== Aska::Yayoi::Downloader::DownloadContext::Initialize()
// vaddr 0x21ef980 | ghidra 0x22ef980 | size 88 | symbol _ZN4Aska5Yayoi10Downloader15DownloadContext10InitializeEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska5Yayoi10Downloader15DownloadContext10InitializeEv(long param_1)

{
  long lVar1;
  
  if (*(char *)(param_1 + 0x68c) != '\0') {
    return 0;
  }
  if (*(char *)(param_1 + 0x460) == '\0') {
    lVar1 = param_1 + 0x18;
    *(undefined8 *)(param_1 + 0x370) = 0;
    *(long *)(param_1 + 0x470) = lVar1;
    *(long *)(param_1 + 0x468) = param_1 + 0x60;
    *(undefined1 *)(param_1 + 0x460) = 1;
  }
  else {
    lVar1 = *(long *)(param_1 + 0x470);
    if (lVar1 == 0) goto code_r0x022ef9c8;
  }
  *(undefined1 *)(lVar1 + 0x30) = 0;
code_r0x022ef9c8:
  *(undefined1 *)(param_1 + 0x68c) = 1;
  return 1;
}

// ==== Aska::Yayoi::Downloader::WorkerThread::Init()
// vaddr 0x21ef9d8 | ghidra 0x22ef9d8 | size 144 | symbol _ZN4Aska5Yayoi10Downloader12WorkerThread4InitEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi10Downloader12WorkerThread4InitEv(undefined8 *param_1,long param_2)

{
  ulong uVar1;
  undefined8 uVar2;
  
  if ((*(char *)(param_2 + 0x80) == '\0') || (*(char *)(param_2 + 0x81) != '\0')) {
    if (*(char *)(param_2 + 0x80) == '\0') {
      *(undefined1 *)(param_2 + 0x81) = 0;
      uVar1 = Aska::Event::Create(bool, bool)(param_2 + 0x18,0,0);
      if (((uVar1 & 1) == 0) || (uVar1 = Aska::Thread::Create(bool, int, int, bool)(param_2,0,0x7f,0xc000,1), (uVar1 & 1) == 0)
         ) {
        uVar2 = 0xffffffffffffffff;
      }
      else {
        uVar2 = 0;
        *(undefined1 *)(param_2 + 0x80) = 1;
      }
    }
    else {
      uVar2 = 0;
    }
  }
  else {
    uVar2 = 0xfffffffffffffc52;
  }
  *param_1 = uVar2;
  return;
}

// ==== Aska::Yayoi::Downloader::WorkerThread::Term()
// vaddr 0x21efa68 | ghidra 0x22efa68 | size 104 | symbol _ZN4Aska5Yayoi10Downloader12WorkerThread4TermEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi10Downloader12WorkerThread4TermEv(long param_1)

{
  if ((((*(char *)(param_1 + 0x80) != '\0') || (*(char *)(param_1 + 0x81) != '\0')) &&
      (*(char *)(param_1 + 0x80) != '\0')) && (*(char *)(param_1 + 0x81) == '\0')) {
    *(undefined1 *)(param_1 + 0x81) = 1;
    Aska::Event::Set() const(param_1 + 0x18);
    Aska::Thread::WaitEnd()(param_1);
    Aska::Event::Exit()(param_1 + 0x18);
    Aska::Thread::Delete()(param_1);
    *(undefined1 *)(param_1 + 0x80) = 0;
  }
  return;
}

// ==== Aska::Yayoi::Downloader::ThreadHandler()
// vaddr 0x21efad0 | ghidra 0x22efad0 | size 1796 | symbol _ZN4Aska5Yayoi10Downloader13ThreadHandlerEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi10Downloader13ThreadHandlerEv(long param_1)

{
  int *piVar1;
  int *piVar2;
  long lVar3;
  long lVar4;
  int *piVar5;
  uint uVar6;
  uint uVar7;
  undefined4 uVar8;
  byte bVar9;
  char cVar10;
  bool bVar11;
  long lVar12;
  ulong uVar13;
  int iVar14;
  uint uVar15;
  long lVar16;
  long lVar17;
  undefined1 auStack_1d8 [328];
  long lStack_90;
  undefined8 uStack_88;
  undefined8 uStack_80;
  long lStack_78;
  int *piStack_70;
  long lStack_68;
  
  uVar6 = *(uint *)(param_1 + 0x428);
  uVar7 = *(uint *)(param_1 + 0x42c);
  uVar15 = uVar6;
  if (uVar6 <= uVar7) {
    uVar15 = *(int *)(param_1 + 0x430) + uVar6;
  }
  if (0 < (int)(uVar15 + ~uVar7)) {
    uVar15 = 0;
    if (uVar7 + 1 < *(uint *)(param_1 + 0x430)) {
      uVar15 = uVar7 + 1;
    }
    if (uVar15 != uVar6) {
      do {
        uVar8 = *(undefined4 *)(*(long *)(param_1 + 0x438) + (ulong)uVar15 * 4);
        *(uint *)(param_1 + 0x42c) = uVar15;
        lVar12 = Aska::Yayoi::Downloader::QueryDownloadElement(unsigned int) const(param_1,uVar8);
        if (lVar12 != 0) {
          lVar16 = *(long *)(lVar12 + 0x18);
          if (lVar16 != 0) {
            Aska::Yayoi::Downloader::DownloadContext::FinishDownload()(lVar16);
            *(undefined1 *)(lVar16 + 0x518) = 0;
            *(undefined8 *)(lVar16 + 0x680) = 0;
            *(undefined8 *)(lVar16 + 0x678) = 0;
            *(undefined8 *)(lVar16 + 0x670) = 0;
            *(undefined8 *)(lVar16 + 0x668) = 0;
            *(undefined8 *)(lVar16 + 0x660) = 0;
            *(undefined4 *)(lVar16 + 0x688) = 0;
            if (*(uint *)(param_1 + 0x40c) != *(uint *)(param_1 + 0x408)) {
              *(long *)(*(long *)(param_1 + 0x418) + (ulong)*(uint *)(param_1 + 0x408) * 8) = lVar16
              ;
              iVar14 = 0;
              if (*(int *)(param_1 + 0x408) + 1U < *(uint *)(param_1 + 0x410)) {
                iVar14 = *(int *)(param_1 + 0x408) + 1;
              }
              *(int *)(param_1 + 0x408) = iVar14;
            }
          }
          *(undefined8 *)(lVar12 + 0x18) = 0;
          *(undefined1 *)(lVar12 + 0x330) = 0;
          Aska::Yayoi::Downloader::RemoveDownloadQueueList(Aska::Yayoi::Downloader::DownloadElement*)(param_1,lVar12);
        }
        uVar15 = 0;
        if (*(int *)(param_1 + 0x42c) + 1U < *(uint *)(param_1 + 0x430)) {
          uVar15 = *(int *)(param_1 + 0x42c) + 1;
        }
      } while (uVar15 != *(uint *)(param_1 + 0x428));
    }
  }
  if (*(int *)(param_1 + 0x3d8) < 1) {
    return;
  }
  piVar1 = (int *)(param_1 + 0x478);
  iVar14 = 0;
code_r0x022efbf0:
  if (*piVar1 == -1) {
    cVar10 = '\x01';
    bVar11 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar11) {
      *piVar1 = 0;
      cVar10 = ExclusiveMonitorsStatus();
    }
    if (cVar10 == '\0') goto code_r0x022efcb8;
    goto code_r0x022efbf0;
  }
  ClearExclusiveLocal();
  bVar11 = iVar14 < 0x1ff;
  iVar14 = iVar14 + 1;
  if (bVar11) goto code_r0x022efbf0;
  piVar2 = (int *)(param_1 + 0x47c);
  do {
    cVar10 = '\x01';
    bVar11 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar11) {
      *piVar2 = *piVar2 + 1;
      cVar10 = ExclusiveMonitorsStatus();
    }
  } while (cVar10 != '\0');
  do {
    if (*piVar1 != -1) {
      ClearExclusiveLocal();
      do {
        uVar13 = Aska::Semaphore::IsReady() const(param_1 + 0x4b8);
        if ((uVar13 & 1) == 0) {
          do {
            cVar10 = '\x01';
            bVar11 = (bool)ExclusiveMonitorPass(piVar2,0x10);
            if (bVar11) {
              *piVar2 = *piVar2 + -1;
              cVar10 = ExclusiveMonitorsStatus();
            }
          } while (cVar10 != '\0');
          Aska::Thread::Sleep(unsigned int)(1);
        }
        else {
          Aska::Semaphore::Wait() const(param_1 + 0x4b8);
        }
        do {
          cVar10 = '\x01';
          bVar11 = (bool)ExclusiveMonitorPass(piVar2,0x10);
          if (bVar11) {
            *piVar2 = *piVar2 + 1;
            cVar10 = ExclusiveMonitorsStatus();
          }
        } while (cVar10 != '\0');
        while (*piVar1 == -1) {
          cVar10 = '\x01';
          bVar11 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar11) {
            *piVar1 = 0;
            cVar10 = ExclusiveMonitorsStatus();
          }
          if (cVar10 == '\0') goto code_r0x022efca8;
        }
        ClearExclusiveLocal();
      } while( true );
    }
    cVar10 = '\x01';
    bVar11 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar11) {
      *piVar1 = 0;
      cVar10 = ExclusiveMonitorsStatus();
    }
  } while (cVar10 != '\0');
code_r0x022efca8:
  do {
    cVar10 = '\x01';
    bVar11 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar11) {
      *piVar2 = *piVar2 + -1;
      cVar10 = ExclusiveMonitorsStatus();
    }
  } while (cVar10 != '\0');
code_r0x022efcb8:
  DataMemoryBarrier(2,3);
  lVar12 = param_1 + 0xa0;
  lVar16 = *(long *)(param_1 + 0xb0);
  while (lVar3 = lVar16, lVar12 != lVar3) {
    lVar16 = *(long *)(lVar3 + 0x10);
    if ((*(byte *)(lVar3 + 0x331) & 1) == 0) {
      if ((*(byte *)(lVar3 + 0x331) >> 1 & 1) == 0) goto code_r0x022efcf4;
code_r0x022efd4c:
      if ((*(char *)(lVar3 + 0x330) != '\x03') && (*(char *)(lVar3 + 0x330) != '\x02')) {
        *(undefined1 *)(lVar3 + 0x330) = 2;
      }
      *(byte *)(lVar3 + 0x331) = *(byte *)(lVar3 + 0x331) & 0xfd;
      bVar9 = *(byte *)(lVar3 + 0x331);
    }
    else {
      if (*(char *)(lVar3 + 0x330) != '\x03') {
        if (*(long *)(lVar3 + 0x18) == 0) {
          Aska::Yayoi::Downloader::AddDownloadFinishQueue(unsigned int)(auStack_1d8,param_1,*(undefined4 *)(lVar3 + 0x20));
        }
        else {
          lVar17 = *(long *)(*(long *)(lVar3 + 0x18) + 0x470);
          if (lVar17 != 0) {
            *(undefined1 *)(lVar17 + 0x41) = 1;
          }
        }
        *(undefined1 *)(lVar3 + 0x330) = 3;
      }
      *(byte *)(lVar3 + 0x331) = *(byte *)(lVar3 + 0x331) & 0xfe;
      if ((*(byte *)(lVar3 + 0x331) >> 1 & 1) != 0) goto code_r0x022efd4c;
code_r0x022efcf4:
      bVar9 = *(byte *)(lVar3 + 0x331);
    }
    if ((bVar9 >> 2 & 1) != 0) {
      if (*(char *)(lVar3 + 0x330) == '\x02') {
        *(bool *)(lVar3 + 0x330) = *(long *)(lVar3 + 0x18) != 0;
      }
      *(byte *)(lVar3 + 0x331) = *(byte *)(lVar3 + 0x331) & 0xfb;
    }
  }
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_1 + 0x478) = 0xffffffff;
  DataMemoryBarrier(2,3);
  piVar2 = (int *)(param_1 + 0x47c);
  if (0x14 < *(int *)(param_1 + 0x47c)) {
    do {
      cVar10 = '\x01';
      bVar11 = (bool)ExclusiveMonitorPass(piVar2,0x10);
      if (bVar11) {
        *piVar2 = *piVar2 + -1;
        cVar10 = ExclusiveMonitorsStatus();
      }
    } while (cVar10 != '\0');
    uVar13 = Aska::Semaphore::IsReady() const(param_1 + 0x4b8);
    if ((uVar13 & 1) != 0) {
      Aska::Semaphore::Signal() const(param_1 + 0x4b8);
    }
  }
  if (*(int *)(param_1 + 0x3d8) < 1) {
    return;
  }
  iVar14 = 0;
  do {
    while (*piVar1 == -1) {
      cVar10 = '\x01';
      bVar11 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar11) {
        *piVar1 = 0;
        cVar10 = ExclusiveMonitorsStatus();
      }
      if (cVar10 == '\0') goto code_r0x022efecc;
    }
    ClearExclusiveLocal();
    bVar11 = iVar14 < 0x1ff;
    iVar14 = iVar14 + 1;
  } while (bVar11);
  do {
    cVar10 = '\x01';
    bVar11 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar11) {
      *piVar2 = *piVar2 + 1;
      cVar10 = ExclusiveMonitorsStatus();
    }
  } while (cVar10 != '\0');
  do {
    if (*piVar1 != -1) {
      ClearExclusiveLocal();
      do {
        uVar13 = Aska::Semaphore::IsReady() const(param_1 + 0x4b8);
        if ((uVar13 & 1) == 0) {
          do {
            cVar10 = '\x01';
            bVar11 = (bool)ExclusiveMonitorPass(piVar2,0x10);
            if (bVar11) {
              *piVar2 = *piVar2 + -1;
              cVar10 = ExclusiveMonitorsStatus();
            }
          } while (cVar10 != '\0');
          Aska::Thread::Sleep(unsigned int)(1);
        }
        else {
          Aska::Semaphore::Wait() const(param_1 + 0x4b8);
        }
        do {
          cVar10 = '\x01';
          bVar11 = (bool)ExclusiveMonitorPass(piVar2,0x10);
          if (bVar11) {
            *piVar2 = *piVar2 + 1;
            cVar10 = ExclusiveMonitorsStatus();
          }
        } while (cVar10 != '\0');
        while (*piVar1 == -1) {
          cVar10 = '\x01';
          bVar11 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar11) {
            *piVar1 = 0;
            cVar10 = ExclusiveMonitorsStatus();
          }
          if (cVar10 == '\0') goto code_r0x022efebc;
        }
        ClearExclusiveLocal();
      } while( true );
    }
    cVar10 = '\x01';
    bVar11 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar11) {
      *piVar1 = 0;
      cVar10 = ExclusiveMonitorsStatus();
    }
  } while (cVar10 != '\0');
code_r0x022efebc:
  do {
    cVar10 = '\x01';
    bVar11 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar11) {
      *piVar2 = *piVar2 + -1;
      cVar10 = ExclusiveMonitorsStatus();
    }
  } while (cVar10 != '\0');
code_r0x022efecc:
  DataMemoryBarrier(2,3);
  lVar16 = *(long *)(param_1 + 0xb0);
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_1 + 0x478) = 0xffffffff;
  DataMemoryBarrier(2,3);
  if (0x14 < *(int *)(param_1 + 0x47c)) {
    do {
      cVar10 = '\x01';
      bVar11 = (bool)ExclusiveMonitorPass(piVar2,0x10);
      if (bVar11) {
        *piVar2 = *piVar2 + -1;
        cVar10 = ExclusiveMonitorsStatus();
      }
    } while (cVar10 != '\0');
    uVar13 = Aska::Semaphore::IsReady() const(param_1 + 0x4b8);
    if ((uVar13 & 1) != 0) {
      Aska::Semaphore::Signal() const(param_1 + 0x4b8);
    }
  }
  if (lVar12 == lVar16) {
    return;
  }
  lVar3 = param_1 + 0x4b8;
  do {
    if (*(int *)(param_1 + 0x674) <= *(int *)(param_1 + 0x670)) {
      return;
    }
    if (*(char *)(lVar16 + 0x330) == '\0') {
      uVar15 = 0;
      if (*(int *)(param_1 + 0x40c) + 1U < *(uint *)(param_1 + 0x410)) {
        uVar15 = *(int *)(param_1 + 0x40c) + 1;
      }
      if (uVar15 == *(uint *)(param_1 + 0x408)) {
        lVar17 = 0;
      }
      else {
        *(uint *)(param_1 + 0x40c) = uVar15;
        lVar17 = *(long *)(*(long *)(param_1 + 0x418) + (ulong)uVar15 * 8);
      }
      lStack_78 = *(long *)(lVar16 + 0x30);
      piVar5 = *(int **)(lVar16 + 0x38);
      uVar8 = *(undefined4 *)(lVar16 + 0x20);
      if (piVar5 != (int *)0x0) {
        do {
          cVar10 = '\x01';
          bVar11 = (bool)ExclusiveMonitorPass(piVar5,0x10);
          if (bVar11) {
            *piVar5 = *piVar5 + 1;
            cVar10 = ExclusiveMonitorsStatus();
          }
        } while (cVar10 != '\0');
      }
      lVar4 = lVar16 + 0x40;
      if (*(long *)(lVar16 + 0x188) != 0) {
        lVar4 = *(long *)(lVar16 + 0x188);
      }
      piStack_70 = piVar5;
      Aska::Yayoi::Downloader::DownloadContext::StartDownload(Aska::Yayoi::Downloader*, unsigned int, Aska::TSharedPointer<Aska::Yayoi::URI>, char const*, Aska::INotify*, Aska::Yayoi::Downloader::IDownloadStream*, Aska::Yayoi::Downloader::UriParam const*, unsigned long)(&lStack_68,lVar17,param_1,uVar8,&lStack_78,lVar4,
                      *(undefined8 *)(lVar16 + 0x28),*(undefined8 *)(lVar16 + 0x310),
                      *(undefined8 *)(lVar16 + 0x318),*(undefined8 *)(lVar16 + 800));
      lVar4 = lStack_78;
      if (piVar5 == (int *)0x0) {
code_r0x022efffc:
        if (lStack_78 != 0) {
          Aska::Yayoi::URI::DeleteBuffer()(lStack_78);
          operator delete(void*)(lVar4);
        }
        if (piStack_70 != (int *)0x0) {
          Aska::TSharedPointerCode::DeleteCounter(int*)();
        }
      }
      else {
        do {
          iVar14 = *piVar5;
          cVar10 = '\x01';
          bVar11 = (bool)ExclusiveMonitorPass(piVar5,0x10);
          if (bVar11) {
            *piVar5 = iVar14 + -1;
            cVar10 = ExclusiveMonitorsStatus();
          }
        } while (cVar10 != '\0');
        if (iVar14 + -1 == 0) goto code_r0x022efffc;
      }
      lStack_78 = 0;
      piStack_70 = (int *)0x0;
      if (lStack_68 < 0) {
        if (*(long *)(lVar16 + 0x28) != 0) {
          auStack_1d8[0] = 0;
          lStack_90 = lStack_68;
          uStack_88 = 0;
          uStack_80 = 0;
          (**(code **)**(undefined8 **)(lVar16 + 0x28))(*(undefined8 **)(lVar16 + 0x28),auStack_1d8)
          ;
        }
        *(undefined1 *)(lVar17 + 0x518) = 0;
        *(undefined8 *)(lVar17 + 0x680) = 0;
        *(undefined8 *)(lVar17 + 0x678) = 0;
        *(undefined8 *)(lVar17 + 0x670) = 0;
        *(undefined8 *)(lVar17 + 0x668) = 0;
        *(undefined8 *)(lVar17 + 0x660) = 0;
        *(undefined4 *)(lVar17 + 0x688) = 0;
        if (*(uint *)(param_1 + 0x40c) == *(uint *)(param_1 + 0x408)) goto code_r0x022eff4c;
        *(long *)(*(long *)(param_1 + 0x418) + (ulong)*(uint *)(param_1 + 0x408) * 8) = lVar17;
        iVar14 = 0;
        if (*(int *)(param_1 + 0x408) + 1U < *(uint *)(param_1 + 0x410)) {
          iVar14 = *(int *)(param_1 + 0x408) + 1;
        }
        *(int *)(param_1 + 0x408) = iVar14;
        iVar14 = 0;
      }
      else {
        *(long *)(lVar16 + 0x18) = lVar17;
        *(undefined1 *)(lVar16 + 0x330) = 1;
        iVar14 = 0;
      }
    }
    else {
code_r0x022eff4c:
      iVar14 = 0;
    }
    do {
      while (*piVar1 == -1) {
        cVar10 = '\x01';
        bVar11 = (bool)ExclusiveMonitorPass(piVar1,0x10);
        if (bVar11) {
          *piVar1 = 0;
          cVar10 = ExclusiveMonitorsStatus();
        }
        if (cVar10 == '\0') goto code_r0x022f0168;
      }
      ClearExclusiveLocal();
      bVar11 = iVar14 < 0x1ff;
      iVar14 = iVar14 + 1;
    } while (bVar11);
    do {
      cVar10 = '\x01';
      bVar11 = (bool)ExclusiveMonitorPass(piVar2,0x10);
      if (bVar11) {
        *piVar2 = *piVar2 + 1;
        cVar10 = ExclusiveMonitorsStatus();
      }
    } while (cVar10 != '\0');
    do {
      if (*piVar1 != -1) {
        do {
          ClearExclusiveLocal();
          uVar13 = Aska::Semaphore::IsReady() const(lVar3);
          if ((uVar13 & 1) == 0) {
            do {
              cVar10 = '\x01';
              bVar11 = (bool)ExclusiveMonitorPass(piVar2,0x10);
              if (bVar11) {
                *piVar2 = *piVar2 + -1;
                cVar10 = ExclusiveMonitorsStatus();
              }
            } while (cVar10 != '\0');
            Aska::Thread::Sleep(unsigned int)(1);
          }
          else {
            Aska::Semaphore::Wait() const(lVar3);
          }
          do {
            cVar10 = '\x01';
            bVar11 = (bool)ExclusiveMonitorPass(piVar2,0x10);
            if (bVar11) {
              *piVar2 = *piVar2 + 1;
              cVar10 = ExclusiveMonitorsStatus();
            }
          } while (cVar10 != '\0');
          while (*piVar1 == -1) {
            cVar10 = '\x01';
            bVar11 = (bool)ExclusiveMonitorPass(piVar1,0x10);
            if (bVar11) {
              *piVar1 = 0;
              cVar10 = ExclusiveMonitorsStatus();
            }
            if (cVar10 == '\0') goto code_r0x022f0158;
          }
        } while( true );
      }
      cVar10 = '\x01';
      bVar11 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar11) {
        *piVar1 = 0;
        cVar10 = ExclusiveMonitorsStatus();
      }
    } while (cVar10 != '\0');
code_r0x022f0158:
    do {
      cVar10 = '\x01';
      bVar11 = (bool)ExclusiveMonitorPass(piVar2,0x10);
      if (bVar11) {
        *piVar2 = *piVar2 + -1;
        cVar10 = ExclusiveMonitorsStatus();
      }
    } while (cVar10 != '\0');
code_r0x022f0168:
    DataMemoryBarrier(2,3);
    lVar16 = *(long *)(lVar16 + 0x10);
    DataMemoryBarrier(2,3);
    *piVar1 = -1;
    DataMemoryBarrier(2,3);
    if (0x14 < *piVar2) {
      do {
        cVar10 = '\x01';
        bVar11 = (bool)ExclusiveMonitorPass(piVar2,0x10);
        if (bVar11) {
          *piVar2 = *piVar2 + -1;
          cVar10 = ExclusiveMonitorsStatus();
        }
      } while (cVar10 != '\0');
      uVar13 = Aska::Semaphore::IsReady() const(lVar3);
      if ((uVar13 & 1) != 0) {
        Aska::Semaphore::Signal() const(lVar3);
      }
    }
    if (lVar12 == lVar16) {
      return;
    }
  } while( true );
}

// ==== Aska::Yayoi::Downloader::DownloadContext::FinishDownload()
// vaddr 0x21f01d4 | ghidra 0x22f01d4 | size 220 | symbol _ZN4Aska5Yayoi10Downloader15DownloadContext14FinishDownloadEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi10Downloader15DownloadContext14FinishDownloadEv(long param_1)

{
  long *plVar1;
  ulong uVar2;
  undefined8 *puVar3;
  undefined8 uStack_188;
  undefined1 auStack_180 [328];
  long lStack_38;
  undefined8 uStack_30;
  undefined8 uStack_28;
  
  auStack_180[0] = 0;
  uStack_30 = 0;
  uStack_28 = 0;
  lStack_38 = 0;
  Aska::Yayoi::Downloader::DownloadContext::GetDownloadStatus(Aska::Yayoi::Downloader::DownloadStatus*) const(param_1,auStack_180);
  plVar1 = *(long **)(param_1 + 8);
  if (lStack_38 < 0) {
    (**(code **)(*plVar1 + 0xa0))(plVar1,0);
    puVar3 = *(undefined8 **)(param_1 + 0x680);
  }
  else {
    uVar2 = (**(code **)(*plVar1 + 0xa0))(plVar1,1);
    if ((uVar2 & 1) == 0) {
      uStack_188 = 0xfffffffffffffc59;
      Aska::Yayoi::Downloader::DownloadContext::SetDownloadStatus(Aska::Status)(param_1,&uStack_188);
      Aska::Yayoi::Downloader::DownloadContext::GetDownloadStatus(Aska::Yayoi::Downloader::DownloadStatus*) const(param_1,auStack_180);
    }
    puVar3 = *(undefined8 **)(param_1 + 0x680);
  }
  if (puVar3 != (undefined8 *)0x0) {
    (**(code **)*puVar3)(puVar3,auStack_180);
  }
  *(int *)(*(long *)(param_1 + 0x678) + 0x670) = *(int *)(*(long *)(param_1 + 0x678) + 0x670) + -1;
  Aska::Event::Set() const(*(long *)(param_1 + 0x678) + 0x20);
  *(undefined1 *)(param_1 + 0x518) = 0;
  *(undefined8 *)(param_1 + 0x680) = 0;
  *(undefined8 *)(param_1 + 0x678) = 0;
  *(undefined8 *)(param_1 + 0x670) = 0;
  *(undefined8 *)(param_1 + 0x668) = 0;
  *(undefined4 *)(param_1 + 0x688) = 0;
  *(undefined8 *)(param_1 + 0x660) = 0;
  return;
}

// ==== Aska::Yayoi::Downloader::ReleaseFreeDownloadContext(Aska::Yayoi::Downloader::DownloadContext*)
// vaddr 0x21f02b0 | ghidra 0x22f02b0 | size 88 | symbol _ZN4Aska5Yayoi10Downloader26ReleaseFreeDownloadContextEPNS1_15DownloadContextE | lib libSOA-3.7.0.so | 2026-10-04
undefined4
_ZN4Aska5Yayoi10Downloader26ReleaseFreeDownloadContextEPNS1_15DownloadContextE
          (long param_1,long param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  *(undefined1 *)(param_2 + 0x518) = 0;
  *(undefined8 *)(param_2 + 0x680) = 0;
  *(undefined4 *)(param_2 + 0x688) = 0;
  *(undefined8 *)(param_2 + 0x678) = 0;
  *(undefined8 *)(param_2 + 0x670) = 0;
  *(undefined8 *)(param_2 + 0x668) = 0;
  *(undefined8 *)(param_2 + 0x660) = 0;
  uVar2 = 0;
  if (*(uint *)(param_1 + 0x40c) != *(uint *)(param_1 + 0x408)) {
    *(long *)(*(long *)(param_1 + 0x418) + (ulong)*(uint *)(param_1 + 0x408) * 8) = param_2;
    iVar1 = 0;
    if (*(int *)(param_1 + 0x408) + 1U < *(uint *)(param_1 + 0x410)) {
      iVar1 = *(int *)(param_1 + 0x408) + 1;
    }
    *(int *)(param_1 + 0x408) = iVar1;
    uVar2 = 1;
  }
  return uVar2;
}

// ==== Aska::Yayoi::Downloader::RemoveDownloadQueueList(Aska::Yayoi::Downloader::DownloadElement*)
// vaddr 0x21f0308 | ghidra 0x22f0308 | size 452 | symbol _ZN4Aska5Yayoi10Downloader23RemoveDownloadQueueListEPNS1_15DownloadElementE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi10Downloader23RemoveDownloadQueueListEPNS1_15DownloadElementE
               (long param_1,long param_2)

{
  int *piVar1;
  int *piVar2;
  char cVar3;
  bool bVar4;
  ulong uVar5;
  int iVar6;
  long lVar7;
  long lVar8;
  
  Aska::Yayoi::Downloader::DownloadElement::Reset()(param_2);
  piVar1 = (int *)(param_1 + 0x478);
  iVar6 = 0;
  do {
    while (*piVar1 == -1) {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = 0;
        cVar3 = ExclusiveMonitorsStatus();
      }
      if (cVar3 == '\0') goto code_r0x022f03f4;
    }
    ClearExclusiveLocal();
    bVar4 = iVar6 < 0x1ff;
    iVar6 = iVar6 + 1;
  } while (bVar4);
  piVar2 = (int *)(param_1 + 0x47c);
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
        uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0x4b8);
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
          Aska::Semaphore::Wait() const(param_1 + 0x4b8);
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
          if (cVar3 == '\0') goto code_r0x022f03e4;
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
code_r0x022f03e4:
  do {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar4) {
      *piVar2 = *piVar2 + -1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
code_r0x022f03f4:
  DataMemoryBarrier(2,3);
  if ((param_1 + 0xa0 != param_2) && (param_2 != 0)) {
    lVar7 = *(long *)(param_2 + 8);
    lVar8 = *(long *)(param_2 + 0x10);
    if (lVar7 != 0) {
      *(long *)(lVar7 + 0x10) = lVar8;
    }
    if (lVar8 != 0) {
      *(long *)(lVar8 + 8) = lVar7;
    }
    if (0 < *(int *)(param_1 + 0x3d8)) {
      *(int *)(param_1 + 0x3d8) = *(int *)(param_1 + 0x3d8) + -1;
    }
    *(long *)(param_2 + 8) = 0;
    *(undefined8 *)(param_2 + 0x10) = 0;
  }
  if (*(uint *)(param_1 + 0x3ec) != *(uint *)(param_1 + 1000)) {
    *(long *)(*(long *)(param_1 + 0x3f8) + (ulong)*(uint *)(param_1 + 1000) * 8) = param_2;
    iVar6 = 0;
    if (*(int *)(param_1 + 1000) + 1U < *(uint *)(param_1 + 0x3f0)) {
      iVar6 = *(int *)(param_1 + 1000) + 1;
    }
    *(int *)(param_1 + 1000) = iVar6;
  }
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_1 + 0x478) = 0xffffffff;
  DataMemoryBarrier(2,3);
  if (0x14 < *(int *)(param_1 + 0x47c)) {
    piVar1 = (int *)(param_1 + 0x47c);
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
    uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0x4b8);
    if ((uVar5 & 1) != 0) {
      (*(code *)PTR__ZNK4Aska9Semaphore6SignalEv_02c96cd0)(param_1 + 0x4b8);
      return;
    }
  }
  return;
}

// ==== Aska::Yayoi::Downloader::DownloadContext::StopDownload()
// vaddr 0x21f04cc | ghidra 0x22f04cc | size 40 | symbol _ZN4Aska5Yayoi10Downloader15DownloadContext12StopDownloadEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi10Downloader15DownloadContext12StopDownloadEv(undefined8 *param_1,long param_2)

{
  if (*(long *)(param_2 + 0x470) != 0) {
    *(undefined1 *)(*(long *)(param_2 + 0x470) + 0x41) = 1;
    *param_1 = 0;
    return;
  }
  *param_1 = 0xfffffffffffffc5b;
  return;
}

// ==== Aska::Yayoi::Downloader::AddDownloadFinishQueue(unsigned int)
// vaddr 0x21f04f4 | ghidra 0x22f04f4 | size 488 | symbol _ZN4Aska5Yayoi10Downloader22AddDownloadFinishQueueEj | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Possible PIC construction at 0x022f06b8: Changing call to branch */

void _ZN4Aska5Yayoi10Downloader22AddDownloadFinishQueueEj
               (undefined8 *param_1,long param_2,undefined4 param_3)

{
  int *piVar1;
  int *piVar2;
  char cVar3;
  bool bVar4;
  ulong uVar5;
  int iVar6;
  
  piVar1 = (int *)(param_2 + 0x508);
  iVar6 = 0;
code_r0x022f0518:
  do {
    if (*piVar1 != -1) {
      ClearExclusiveLocal();
      bVar4 = iVar6 < 0x1ff;
      iVar6 = iVar6 + 1;
      if (bVar4) goto code_r0x022f0518;
      piVar2 = (int *)(param_2 + 0x50c);
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
            uVar5 = Aska::Semaphore::IsReady() const(param_2 + 0x548);
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
              Aska::Semaphore::Wait() const(param_2 + 0x548);
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
              if (cVar3 == '\0') goto code_r0x022f05d0;
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
code_r0x022f05d0:
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
        if (bVar4) {
          *piVar2 = *piVar2 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
code_r0x022f05e0:
      DataMemoryBarrier(2,3);
      if (*(uint *)(param_2 + 0x42c) == *(uint *)(param_2 + 0x428)) {
        *param_1 = 0xffffffffffffffff;
        DataMemoryBarrier(2,3);
        *(undefined4 *)(param_2 + 0x508) = 0xffffffff;
        DataMemoryBarrier(2,3);
        if (0x14 < *(int *)(param_2 + 0x50c)) {
          piVar1 = (int *)(param_2 + 0x50c);
          do {
            cVar3 = '\x01';
            bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
            if (bVar4) {
              *piVar1 = *piVar1 + -1;
              cVar3 = ExclusiveMonitorsStatus();
            }
          } while (cVar3 != '\0');
          uVar5 = Aska::Semaphore::IsReady() const(param_2 + 0x548);
          if ((uVar5 & 1) != 0) {
code_r0x011bd9c0:
            (*(code *)PTR__ZNK4Aska9Semaphore6SignalEv_02c96cd0)(param_2 + 0x548);
            return;
          }
        }
      }
      else {
        *(undefined4 *)(*(long *)(param_2 + 0x438) + (ulong)*(uint *)(param_2 + 0x428) * 4) =
             param_3;
        iVar6 = 0;
        if (*(int *)(param_2 + 0x428) + 1U < *(uint *)(param_2 + 0x430)) {
          iVar6 = *(int *)(param_2 + 0x428) + 1;
        }
        *(int *)(param_2 + 0x428) = iVar6;
        DataMemoryBarrier(2,3);
        *(undefined4 *)(param_2 + 0x508) = 0xffffffff;
        DataMemoryBarrier(2,3);
        if (0x14 < *(int *)(param_2 + 0x50c)) {
          piVar1 = (int *)(param_2 + 0x50c);
          do {
            cVar3 = '\x01';
            bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
            if (bVar4) {
              *piVar1 = *piVar1 + -1;
              cVar3 = ExclusiveMonitorsStatus();
            }
          } while (cVar3 != '\0');
          uVar5 = Aska::Semaphore::IsReady() const(param_2 + 0x548);
          if ((uVar5 & 1) != 0) goto code_r0x011bd9c0;
        }
        Aska::Event::Set() const(param_2 + 0x20);
        *param_1 = 0;
      }
      return;
    }
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar4) {
      *piVar1 = 0;
      cVar3 = ExclusiveMonitorsStatus();
    }
    if (cVar3 == '\0') goto code_r0x022f05e0;
  } while( true );
}

// ==== Aska::Yayoi::Downloader::DownloadContext::PauseDownload()
// vaddr 0x21f06dc | ghidra 0x22f06dc | size 12 | symbol _ZN4Aska5Yayoi10Downloader15DownloadContext13PauseDownloadEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi10Downloader15DownloadContext13PauseDownloadEv(undefined8 *param_1)

{
  *param_1 = 0xfffffffffffffc46;
  return;
}

// ==== Aska::Yayoi::Downloader::DownloadContext::ResumeDownload()
// vaddr 0x21f06e8 | ghidra 0x22f06e8 | size 12 | symbol _ZN4Aska5Yayoi10Downloader15DownloadContext14ResumeDownloadEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi10Downloader15DownloadContext14ResumeDownloadEv(undefined8 *param_1)

{
  *param_1 = 0xfffffffffffffc46;
  return;
}

// ==== Aska::Yayoi::Downloader::AcquireFreeDownloadContext()
// vaddr 0x21f06f4 | ghidra 0x22f06f4 | size 56 | symbol _ZN4Aska5Yayoi10Downloader26AcquireFreeDownloadContextEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska5Yayoi10Downloader26AcquireFreeDownloadContextEv(long param_1)

{
  uint uVar1;
  
  uVar1 = 0;
  if (*(int *)(param_1 + 0x40c) + 1U < *(uint *)(param_1 + 0x410)) {
    uVar1 = *(int *)(param_1 + 0x40c) + 1;
  }
  if (uVar1 == *(uint *)(param_1 + 0x408)) {
    return 0;
  }
  *(uint *)(param_1 + 0x40c) = uVar1;
  return *(undefined8 *)(*(long *)(param_1 + 0x418) + (ulong)uVar1 * 8);
}

// ==== Aska::Yayoi::Downloader::DownloadContext::StartDownload(Aska::Yayoi::Downloader*, unsigned int, Aska::TSharedPointer<Aska::Yayoi::URI>, char const*, Aska::INotify*, Aska::Yayoi::Downloader::IDownloadStream*, Aska::Yayoi::Downloader::UriParam const*, unsigned long)
// vaddr 0x21f072c | ghidra 0x22f072c | size 668 | symbol _ZN4Aska5Yayoi10Downloader15DownloadContext13StartDownloadEPS1_jNS_14TSharedPointerINS0_3URIEEEPKcPNS_7INotifyEPNS1_15IDownloadStreamEPKNS1_8UriParamEm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi10Downloader15DownloadContext13StartDownloadEPS1_jNS_14TSharedPointerINS0_3URIEEEPKcPNS_7INotifyEPNS1_15IDownloadStreamEPKNS1_8UriParamEm
               (long *param_1,long param_2,undefined8 param_3,undefined4 param_4,long *param_5,
               undefined8 param_6,undefined8 param_7,long *param_8,undefined8 *param_9,long param_10
               )

{
  int iVar1;
  char cVar2;
  bool bVar3;
  long lVar4;
  int *piVar5;
  ulong uVar6;
  long lStack_80;
  long lStack_78;
  long lStack_70;
  int *piStack_68;
  long lStack_60;
  int *piStack_58;
  
  uVar6 = strlen(param_6);
  if (0x147 < uVar6) {
    *param_1 = -0x3bd;
    return;
  }
  strcpy(param_2 + 0x518,param_6);
  *(undefined8 *)(param_2 + 0x660) = 0;
  *(undefined8 *)(param_2 + 0x670) = 0;
  *(undefined8 *)(param_2 + 0x668) = 0;
  *(undefined8 *)(param_2 + 0x678) = param_3;
  *(undefined4 *)(param_2 + 0x688) = param_4;
  *(undefined8 *)(param_2 + 0x680) = param_7;
  *(long **)(param_2 + 8) = param_8;
  uVar6 = (**(code **)(*param_8 + 0x98))(param_8,param_6);
  if ((uVar6 & 1) == 0) {
    *param_1 = -0x3c8;
    return;
  }
  lStack_70 = *param_5;
  piStack_68 = (int *)param_5[1];
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
  Aska::Yayoi::THttpClient<Aska::Yayoi::TCP, 5>::CreateRequest(Aska::TSharedPointer<Aska::Yayoi::URI>)(&lStack_60,param_2 + 0x10,&lStack_70);
  lVar4 = lStack_70;
  if (piStack_68 == (int *)0x0) {
code_r0x022f0818:
    if (lStack_70 != 0) {
      Aska::Yayoi::URI::DeleteBuffer()(lStack_70);
      operator delete(void*)(lVar4);
    }
    if (piStack_68 != (int *)0x0) {
      Aska::TSharedPointerCode::DeleteCounter(int*)();
    }
  }
  else {
    do {
      iVar1 = *piStack_68;
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piStack_68,0x10);
      if (bVar3) {
        *piStack_68 = iVar1 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    if (iVar1 + -1 == 0) goto code_r0x022f0818;
  }
  piVar5 = piStack_58;
  lVar4 = lStack_60;
  lStack_70 = 0;
  piStack_68 = (int *)0x0;
  lStack_78 = lStack_60;
  if (piStack_58 != (int *)0x0) {
    do {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piStack_58,0x10);
      if (bVar3) {
        *piStack_58 = *piStack_58 + 1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    do {
      iVar1 = *piStack_58;
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piStack_58,0x10);
      if (bVar3) {
        *piStack_58 = iVar1 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    if (iVar1 != 1) goto code_r0x022f08cc;
  }
  if (lStack_60 != 0) {
    Aska::Yayoi::SSLProtocoledData::FreeInnerData()(lStack_60 + 0x198);
    Aska::Yayoi::HttpProtocoledData::~HttpProtocoledData()(lVar4);
    operator delete(void*)(lVar4);
  }
  if (piVar5 != (int *)0x0) {
    Aska::TSharedPointerCode::DeleteCounter(int*)(piVar5);
  }
code_r0x022f08cc:
  lStack_78 = 0;
  *(undefined4 *)(lVar4 + 0x7c) = 1;
  if (param_9 != (undefined8 *)0x0) {
    for (; param_10 != 0; param_10 = param_10 + -1) {
      Aska::Yayoi::HttpProtocoledData::SetParam(signed char const*, unsigned long, signed char const*, unsigned long)(lVar4,*param_9,param_9[2],param_9[1],param_9[3]);
    }
  }
  Aska::Yayoi::THttpClient<Aska::Yayoi::TCP, 5>::InvokeRequests(Aska::Yayoi::TPeerNotify<Aska::Yayoi::TProtocolSuite<Aska::Yayoi::HttpProtocol, Aska::Yayoi::SSLProtocol, Aska::Yayoi::NoProtocol<2> > >*)(&lStack_80,param_2 + 0x10,param_2);
  if (lStack_80 < 0) {
    *(undefined1 *)(param_2 + 0x518) = 0;
    *(undefined4 *)(param_2 + 0x688) = 0;
    *(undefined8 *)(param_2 + 0x680) = 0;
    *(undefined8 *)(param_2 + 0x668) = 0;
    *(undefined8 *)(param_2 + 0x660) = 0;
    *(undefined8 *)(param_2 + 0x678) = 0;
    *(undefined8 *)(param_2 + 0x670) = 0;
    (**(code **)(**(long **)(param_2 + 8) + 0xa0))(*(long **)(param_2 + 8),0);
  }
  else {
    lStack_80 = 0;
    *(int *)(*(long *)(param_2 + 0x678) + 0x670) = *(int *)(*(long *)(param_2 + 0x678) + 0x670) + 1;
  }
  *param_1 = lStack_80;
  if (piStack_58 != (int *)0x0) {
    do {
      iVar1 = *piStack_58;
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piStack_58,0x10);
      if (bVar3) {
        *piStack_58 = iVar1 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    if (iVar1 + -1 != 0) {
      return;
    }
  }
  if (lStack_60 != 0) {
    Aska::Yayoi::SSLProtocoledData::FreeInnerData()(lStack_60 + 0x198);
    Aska::Yayoi::HttpProtocoledData::~HttpProtocoledData()(lStack_60);
    operator delete(void*)(lStack_60);
  }
  if (piStack_58 != (int *)0x0) {
    Aska::TSharedPointerCode::DeleteCounter(int*)();
  }
  return;
}

// ==== Aska::Yayoi::Downloader::DownloadElement::Set(unsigned int, Aska::TSharedPointer<Aska::Yayoi::URI>, Aska::INotify*, char const*, Aska::Yayoi::Downloader::IDownloadStream*, Aska::Yayoi::Downloader::UriParam const*, unsigned long)
// vaddr 0x21f09c8 | ghidra 0x22f09c8 | size 640 | symbol _ZN4Aska5Yayoi10Downloader15DownloadElement3SetEjNS_14TSharedPointerINS0_3URIEEEPNS_7INotifyEPKcPNS1_15IDownloadStreamEPKNS1_8UriParamEm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi10Downloader15DownloadElement3SetEjNS_14TSharedPointerINS0_3URIEEEPNS_7INotifyEPKcPNS1_15IDownloadStreamEPKNS1_8UriParamEm
               (undefined8 *param_1,long param_2,undefined4 param_3,long *param_4,undefined8 param_5
               ,undefined8 param_6,long param_7,long param_8,long param_9)

{
  long lVar1;
  undefined8 *puVar2;
  int iVar3;
  long lVar4;
  char cVar5;
  bool bVar6;
  long lVar7;
  long lVar8;
  undefined8 uVar9;
  long lVar10;
  int *piVar11;
  long lVar12;
  long *plVar13;
  long lVar14;
  
  if (((param_8 == 0) && (param_9 != 0)) || ((param_8 != 0 && (param_9 == 0)))) {
    uVar9 = 0xfffffffffffffc43;
    goto code_r0x022f0a1c;
  }
  lVar7 = strlen(param_6);
  if (0x147 < lVar7 + 1) {
    lVar7 = operator new[](unsigned long, std::nothrow_t const&)(lVar7 + 1,PTR__ZSt7nothrow_02cb9a80);
    *(long *)(param_2 + 0x188) = lVar7;
    if (lVar7 != 0) {
      strcpy(lVar7,param_6);
      goto code_r0x022f0a8c;
    }
code_r0x022f0c30:
    if (*(long *)(param_2 + 0x328) != 0) {
      operator delete[](void*)();
      *(undefined8 *)(param_2 + 0x328) = 0;
    }
    uVar9 = 0xfffffffffffffc41;
    goto code_r0x022f0a1c;
  }
  strcpy(param_2 + 0x40,param_6);
  *(undefined8 *)(param_2 + 0x188) = 0;
code_r0x022f0a8c:
  lVar7 = param_2 + 400;
  if (param_7 != 0) {
    lVar7 = param_7;
  }
  if (param_8 == 0) {
    *(undefined8 *)(param_2 + 0x328) = 0;
    *(undefined8 *)(param_2 + 800) = 0;
    *(undefined8 *)(param_2 + 0x318) = 0;
  }
  else {
    if (param_9 == 0) {
      lVar8 = 0;
    }
    else {
      lVar8 = param_9 * 0x20 + (*(long *)(param_8 + 0x10) + *(long *)(param_8 + 0x18)) * param_9;
    }
    lVar8 = operator new[](unsigned long, std::nothrow_t const&)(lVar8,PTR__ZSt7nothrow_02cb9a80);
    *(long *)(param_2 + 0x328) = lVar8;
    if (lVar8 == 0) {
      if (*(long *)(param_2 + 0x188) != 0) {
        operator delete[](void*)();
        *(undefined8 *)(param_2 + 0x188) = 0;
      }
      goto code_r0x022f0c30;
    }
    *(long *)(param_2 + 800) = param_9;
    *(long *)(param_2 + 0x318) = lVar8;
    if (param_9 != 0) {
      lVar14 = 0;
      lVar10 = 0;
      lVar1 = param_9 * 0x20 + lVar8;
      while( true ) {
        param_9 = param_9 + -1;
        puVar2 = (undefined8 *)(param_8 + lVar14);
        *(long *)(lVar8 + lVar14) = lVar10 + lVar1;
        lVar12 = puVar2[2];
        *(long *)(*(long *)(param_2 + 0x318) + lVar14 + 8) = lVar12 + lVar10 + lVar1;
        lVar4 = puVar2[3];
        *(undefined8 *)(*(long *)(param_2 + 0x318) + lVar14 + 0x10) = puVar2[2];
        *(undefined8 *)(*(long *)(param_2 + 0x318) + lVar14 + 0x18) = puVar2[3];
        memcpy(*(undefined8 *)(*(long *)(param_2 + 0x318) + lVar14),*puVar2,puVar2[2]);
        memcpy(*(undefined8 *)(*(long *)(param_2 + 0x318) + lVar14 + 8),puVar2[1],puVar2[3]
                       );
        if (param_9 == 0) break;
        lVar8 = *(long *)(param_2 + 0x318);
        lVar10 = lVar4 + lVar12 + lVar10;
        lVar14 = lVar14 + 0x20;
      }
    }
  }
  plVar13 = (long *)(param_2 + 0x30);
  lVar8 = *plVar13;
  *(undefined4 *)(param_2 + 0x20) = param_3;
  *(undefined8 *)(param_2 + 0x28) = param_5;
  *(long *)(param_2 + 0x310) = lVar7;
  if (*param_4 != lVar8) {
    piVar11 = *(int **)(param_2 + 0x38);
    if (piVar11 == (int *)0x0) {
code_r0x022f0bd0:
      if (lVar8 != 0) {
        Aska::Yayoi::URI::DeleteBuffer()(lVar8);
        operator delete(void*)(lVar8);
      }
      if (*(long *)(param_2 + 0x38) != 0) {
        Aska::TSharedPointerCode::DeleteCounter(int*)();
      }
    }
    else {
      do {
        iVar3 = *piVar11;
        cVar5 = '\x01';
        bVar6 = (bool)ExclusiveMonitorPass(piVar11,0x10);
        if (bVar6) {
          *piVar11 = iVar3 + -1;
          cVar5 = ExclusiveMonitorsStatus();
        }
      } while (cVar5 != '\0');
      if (iVar3 + -1 == 0) {
        lVar8 = *plVar13;
        goto code_r0x022f0bd0;
      }
    }
    *plVar13 = 0;
    *(undefined8 *)(param_2 + 0x38) = 0;
    piVar11 = (int *)param_4[1];
    *(int **)(param_2 + 0x38) = piVar11;
    *(long *)(param_2 + 0x30) = *param_4;
    uVar9 = 0;
    if (piVar11 == (int *)0x0) goto code_r0x022f0a1c;
    do {
      cVar5 = '\x01';
      bVar6 = (bool)ExclusiveMonitorPass(piVar11,0x10);
      if (bVar6) {
        *piVar11 = *piVar11 + 1;
        cVar5 = ExclusiveMonitorsStatus();
      }
    } while (cVar5 != '\0');
  }
  uVar9 = 0;
code_r0x022f0a1c:
  *param_1 = uVar9;
  return;
}

// ==== Aska::Yayoi::Downloader::DownloadElement::Reset()
// vaddr 0x21f0c6c | ghidra 0x22f0c6c | size 176 | symbol _ZN4Aska5Yayoi10Downloader15DownloadElement5ResetEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi10Downloader15DownloadElement5ResetEv(long param_1)

{
  int iVar1;
  char cVar2;
  bool bVar3;
  int *piVar4;
  long lVar5;
  long *plVar6;
  
  plVar6 = (long *)(param_1 + 0x30);
  lVar5 = *plVar6;
  *(undefined8 *)(param_1 + 0x18) = 0;
  *(undefined4 *)(param_1 + 0x20) = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  *(undefined8 *)(param_1 + 0x310) = 0;
  if (lVar5 == 0) goto code_r0x022f0cd8;
  piVar4 = *(int **)(param_1 + 0x38);
  if (piVar4 == (int *)0x0) {
code_r0x022f0cb8:
    Aska::Yayoi::URI::DeleteBuffer()(lVar5);
    operator delete(void*)(lVar5);
code_r0x022f0cc8:
    if (*(long *)(param_1 + 0x38) != 0) {
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
    if (iVar1 + -1 == 0) {
      lVar5 = *plVar6;
      if (lVar5 != 0) goto code_r0x022f0cb8;
      goto code_r0x022f0cc8;
    }
  }
  *plVar6 = 0;
  *(undefined8 *)(param_1 + 0x38) = 0;
code_r0x022f0cd8:
  *(undefined8 *)(param_1 + 800) = 0;
  *(undefined8 *)(param_1 + 0x318) = 0;
  *(undefined1 *)(param_1 + 0x330) = 0;
  *(undefined1 *)(param_1 + 0x331) = 0;
  if (*(long *)(param_1 + 0x188) != 0) {
    operator delete[](void*)();
    *(undefined8 *)(param_1 + 0x188) = 0;
  }
  if (*(long *)(param_1 + 0x328) != 0) {
    operator delete[](void*)();
    *(undefined8 *)(param_1 + 0x328) = 0;
  }
  *(undefined1 *)(param_1 + 0x40) = 0;
  return;
}

// ==== Aska::Yayoi::Downloader::DownloadContext::Reset()
// vaddr 0x21f0d5c | ghidra 0x22f0d5c | size 28 | symbol _ZN4Aska5Yayoi10Downloader15DownloadContext5ResetEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi10Downloader15DownloadContext5ResetEv(long param_1)

{
  *(undefined1 *)(param_1 + 0x518) = 0;
  *(undefined8 *)(param_1 + 0x680) = 0;
  *(undefined8 *)(param_1 + 0x678) = 0;
  *(undefined8 *)(param_1 + 0x670) = 0;
  *(undefined8 *)(param_1 + 0x668) = 0;
  *(undefined8 *)(param_1 + 0x660) = 0;
  *(undefined4 *)(param_1 + 0x688) = 0;
  return;
}

// ==== Aska::Yayoi::Downloader::DownloadElement::DownloadElement()
// vaddr 0x21f0d78 | ghidra 0x22f0d78 | size 100 | symbol _ZN4Aska5Yayoi10Downloader15DownloadElementC1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi10Downloader15DownloadElementC2Ev(long *param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  undefined *puVar3;
  
  param_1[2] = 0;
  puVar3 = PTR__ZTVN4Aska5Yayoi10Downloader14DownloadStreamE_02cc1c28;
  puVar2 = PTR__ZTVN4Aska5Yayoi10Downloader15DownloadElementE_02cc0d00;
  param_1[6] = 0;
  param_1[7] = 0;
  param_1[0x34] = (long)(PTR__ZTVN4Aska4FileE_02cb6e28 + 0x10);
  puVar1 = PTR__ZTVN4Aska10FileStreamE_02cbc9f8;
  *(undefined1 *)(param_1 + 0x35) = 0;
  *(undefined1 *)(param_1 + 0x38) = 0;
  param_1[0x36] = 0;
  param_1[0x37] = 0;
  param_1[0x31] = 0;
  *param_1 = (long)(puVar2 + 0x10);
  param_1[1] = 0;
  param_1[0x33] = (long)(puVar1 + 0x10);
  param_1[0x32] = (long)(puVar3 + 0x10);
  param_1[0x65] = 0;
  (*(code *)PTR__ZN4Aska5Yayoi10Downloader15DownloadElement5ResetEv_02c99308)();
  return;
}

// ==== Aska::Yayoi::Downloader::DownloadContext::DownloadContext()
// vaddr 0x21f0ddc | ghidra 0x22f0ddc | size 460 | symbol _ZN4Aska5Yayoi10Downloader15DownloadContextC1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi10Downloader15DownloadContextC2Ev(long *param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZTVN4Aska5Yayoi11THttpClientINS0_3TCPELi5EEE_02cc2e80 + 0x10;
  *param_1 = (long)(PTR__ZTVN4Aska5Yayoi10Downloader15DownloadContextE_02cbee80 + 0x10);
  param_1[2] = (long)puVar1;
  Aska::Yayoi::HttpProtocol::HttpProtocol()(param_1 + 3);
  *(undefined1 *)(param_1 + 0xc) = 0;
  param_1[0xd] = (long)(PTR__ZTVN4Aska6TQueueINS_5Yayoi11SSLProtocol11RecordLayerELi10EEE_02cbc400 +
                       0x10);
  *(undefined4 *)(param_1 + 0xe) = 1;
  *(undefined4 *)((long)param_1 + 0x74) = 0;
  param_1[0x12] = 0;
  *(undefined1 *)(param_1 + 0x13) = 0;
  param_1[0x10] = 0;
  param_1[0xf] = 0;
  *(undefined1 *)(param_1 + 0x11) = 0;
  param_1[0x17] = 0;
  *(undefined1 *)(param_1 + 0x18) = 0;
  param_1[0x15] = 0;
  param_1[0x14] = 0;
  *(undefined1 *)(param_1 + 0x16) = 0;
  param_1[0x1c] = 0;
  *(undefined1 *)(param_1 + 0x1d) = 0;
  *(undefined1 *)(param_1 + 0x1b) = 0;
  param_1[0x19] = 0;
  param_1[0x1a] = 0;
  param_1[0x21] = 0;
  *(undefined1 *)(param_1 + 0x22) = 0;
  *(undefined1 *)(param_1 + 0x20) = 0;
  param_1[0x1e] = 0;
  param_1[0x1f] = 0;
  param_1[0x26] = 0;
  *(undefined1 *)(param_1 + 0x27) = 0;
  *(undefined1 *)(param_1 + 0x25) = 0;
  param_1[0x23] = 0;
  param_1[0x24] = 0;
  param_1[0x2b] = 0;
  *(undefined1 *)(param_1 + 0x2c) = 0;
  *(undefined1 *)(param_1 + 0x2a) = 0;
  param_1[0x28] = 0;
  param_1[0x29] = 0;
  param_1[0x30] = 0;
  *(undefined1 *)(param_1 + 0x31) = 0;
  *(undefined1 *)(param_1 + 0x2f) = 0;
  param_1[0x2d] = 0;
  param_1[0x2e] = 0;
  param_1[0x35] = 0;
  *(undefined1 *)(param_1 + 0x36) = 0;
  *(undefined1 *)(param_1 + 0x34) = 0;
  param_1[0x32] = 0;
  param_1[0x33] = 0;
  param_1[0x3a] = 0;
  *(undefined1 *)(param_1 + 0x3b) = 0;
  *(undefined1 *)(param_1 + 0x39) = 0;
  param_1[0x37] = 0;
  param_1[0x38] = 0;
  param_1[0x3f] = 0;
  *(undefined1 *)(param_1 + 0x40) = 0;
  *(undefined1 *)(param_1 + 0x3e) = 0;
  param_1[0x3c] = 0;
  param_1[0x3d] = 0;
  param_1[0x44] = 0;
  *(undefined1 *)(param_1 + 0x45) = 0;
  param_1[0x41] = 0;
  *(undefined1 *)(param_1 + 0x43) = 0;
  param_1[0x42] = 0;
  param_1[0x47] = 0;
  param_1[0x46] = 0;
  param_1[0x4a] = 0;
  param_1[0x49] = 0;
  param_1[0x54] = 0;
  param_1[0x53] = 0;
  param_1[0x5f] = 0;
  param_1[0x5e] = 0;
  param_1[0x5d] = 0;
  param_1[0x5c] = 0;
  param_1[0x5b] = 0;
  param_1[0x62] = 0;
  param_1[0x61] = 0;
  *(undefined2 *)(param_1 + 0x66) = 0x301;
  *(undefined2 *)(param_1 + 99) = 0;
  param_1[0x65] = 0;
  param_1[100] = 0;
  param_1[0x68] = 0;
  param_1[0x67] = 0;
  *(undefined1 *)(param_1 + 0x69) = 1;
  *(undefined1 *)(param_1 + 0x6a) = 1;
  *(undefined8 *)((long)param_1 + 900) = 0;
  *(undefined8 *)((long)param_1 + 0x37c) = 0;
  *(undefined4 *)((long)param_1 + 0x38c) = 0;
  param_1[0x6c] = 0;
  param_1[0x6b] = 0;
  param_1[0x6e] = 0;
  param_1[0x6d] = 0;
  *(undefined1 *)(param_1 + 0x6f) = 0;
  param_1[0x73] = 0;
  param_1[0x72] = 0;
  param_1[0x75] = 0;
  param_1[0x74] = 0;
  param_1[0x77] = 0;
  param_1[0x76] = 0;
  param_1[0x79] = 0;
  param_1[0x78] = 0;
  Aska::Yayoi::IPAddress::IPAddress()(param_1 + 0x7b);
  *(undefined1 *)(param_1 + 0x8c) = 0;
  param_1[0x8e] = 0;
  param_1[0x8d] = 0;
  param_1[0x8f] = 0;
  *(undefined4 *)(param_1 + 0x90) = 0;
  Aska::FastCriticalSection::FastCriticalSection()(param_1 + 0x91);
  *(undefined1 *)(param_1 + 0xa3) = 0;
  *(undefined8 *)((long)param_1 + 0x685) = 0;
  param_1[0xd0] = 0;
  param_1[0xcf] = 0;
  param_1[0xce] = 0;
  param_1[0xcd] = 0;
  param_1[0xcc] = 0;
  return;
}

// ==== Aska::Yayoi::Downloader::DownloadContext::~DownloadContext()
// vaddr 0x21f0fa8 | ghidra 0x22f0fa8 | size 112 | symbol _ZN4Aska5Yayoi10Downloader15DownloadContextD2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi10Downloader15DownloadContextD1Ev(long *param_1)

{
  char cVar1;
  bool bVar2;
  
  *param_1 = (long)(PTR__ZTVN4Aska5Yayoi10Downloader15DownloadContextE_02cbee80 + 0x10);
  if (*(char *)((long)param_1 + 0x68c) != '\0') {
    DataMemoryBarrier(2,3);
    if ((int)param_1[0x90] != 0) {
      *(undefined4 *)(param_1 + 0x7a) = 0;
      *(undefined4 *)((long)param_1 + 0x37c) = 0;
      Aska::Yayoi::IPAddress::Clear()(param_1 + 0x7b);
      do {
        cVar1 = '\x01';
        bVar2 = (bool)ExclusiveMonitorPass(param_1 + 0x90,0x10);
        if (bVar2) {
          *(undefined4 *)(param_1 + 0x90) = 0;
          cVar1 = ExclusiveMonitorsStatus();
        }
      } while (cVar1 != '\0');
    }
    *(undefined1 *)(param_1 + 0x8c) = 0;
    *(undefined1 *)((long)param_1 + 0x68c) = 0;
  }
  Aska::FastCriticalSection::~FastCriticalSection()(param_1 + 0x91);
  (*(code *)PTR__ZN4Aska5Yayoi11THttpClientINS0_3TCPELi5EED2Ev_02c90460)(param_1 + 2);
  return;
}

// ==== Aska::Yayoi::Downloader::DownloadContext::Finalize()
// vaddr 0x21f1018 | ghidra 0x22f1018 | size 84 | symbol _ZN4Aska5Yayoi10Downloader15DownloadContext8FinalizeEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi10Downloader15DownloadContext8FinalizeEv(long param_1)

{
  char cVar1;
  bool bVar2;
  
  if (*(char *)(param_1 + 0x68c) != '\0') {
    DataMemoryBarrier(2,3);
    if (*(int *)(param_1 + 0x480) != 0) {
      *(undefined4 *)(param_1 + 0x3d0) = 0;
      *(undefined4 *)(param_1 + 0x37c) = 0;
      Aska::Yayoi::IPAddress::Clear()(param_1 + 0x3d8);
      do {
        cVar1 = '\x01';
        bVar2 = (bool)ExclusiveMonitorPass((undefined4 *)(param_1 + 0x480),0x10);
        if (bVar2) {
          *(undefined4 *)(param_1 + 0x480) = 0;
          cVar1 = ExclusiveMonitorsStatus();
        }
      } while (cVar1 != '\0');
    }
    *(undefined1 *)(param_1 + 0x460) = 0;
    *(undefined1 *)(param_1 + 0x68c) = 0;
  }
  return;
}

// ==== Aska::Yayoi::Downloader::DownloadContext::~DownloadContext()
// vaddr 0x21f106c | ghidra 0x22f106c | size 120 | symbol _ZN4Aska5Yayoi10Downloader15DownloadContextD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi10Downloader15DownloadContextD0Ev(long *param_1)

{
  char cVar1;
  bool bVar2;
  
  *param_1 = (long)(PTR__ZTVN4Aska5Yayoi10Downloader15DownloadContextE_02cbee80 + 0x10);
  if (*(char *)((long)param_1 + 0x68c) != '\0') {
    DataMemoryBarrier(2,3);
    if ((int)param_1[0x90] != 0) {
      *(undefined4 *)(param_1 + 0x7a) = 0;
      *(undefined4 *)((long)param_1 + 0x37c) = 0;
      Aska::Yayoi::IPAddress::Clear()(param_1 + 0x7b);
      do {
        cVar1 = '\x01';
        bVar2 = (bool)ExclusiveMonitorPass(param_1 + 0x90,0x10);
        if (bVar2) {
          *(undefined4 *)(param_1 + 0x90) = 0;
          cVar1 = ExclusiveMonitorsStatus();
        }
      } while (cVar1 != '\0');
    }
    *(undefined1 *)(param_1 + 0x8c) = 0;
    *(undefined1 *)((long)param_1 + 0x68c) = 0;
  }
  Aska::FastCriticalSection::~FastCriticalSection()(param_1 + 0x91);
  Aska::Yayoi::THttpClient<Aska::Yayoi::TCP, 5>::~THttpClient()(param_1 + 2);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::Yayoi::Downloader::DownloadContext::SetDownloadStatus(Aska::Status)
// vaddr 0x21f10e4 | ghidra 0x22f10e4 | size 348 | symbol _ZN4Aska5Yayoi10Downloader15DownloadContext17SetDownloadStatusENS_6StatusE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi10Downloader15DownloadContext17SetDownloadStatusENS_6StatusE
               (long param_1,undefined8 *param_2)

{
  int *piVar1;
  int *piVar2;
  char cVar3;
  bool bVar4;
  ulong uVar5;
  int iVar6;
  
  piVar1 = (int *)(param_1 + 0x4c0);
  iVar6 = 0;
  do {
    while (*piVar1 != -1) {
      ClearExclusiveLocal();
      bVar4 = 0x1fe < iVar6;
      iVar6 = iVar6 + 1;
      if (bVar4) {
        piVar2 = (int *)(param_1 + 0x4c4);
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
              uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0x500);
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
                Aska::Semaphore::Wait() const(param_1 + 0x500);
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
                if (cVar3 == '\0') goto code_r0x022f1228;
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
code_r0x022f1228:
        do {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
          if (bVar4) {
            *piVar2 = *piVar2 + -1;
            cVar3 = ExclusiveMonitorsStatus();
          }
        } while (cVar3 != '\0');
        DataMemoryBarrier(2,3);
code_r0x022f115c:
        *(undefined8 *)(param_1 + 0x660) = *param_2;
        DataMemoryBarrier(2,3);
        *(undefined4 *)(param_1 + 0x4c0) = 0xffffffff;
        DataMemoryBarrier(2,3);
        piVar1 = (int *)(param_1 + 0x4c4);
        if (0x14 < *piVar1) {
          do {
            cVar3 = '\x01';
            bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
            if (bVar4) {
              *piVar1 = *piVar1 + -1;
              cVar3 = ExclusiveMonitorsStatus();
            }
          } while (cVar3 != '\0');
          uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0x500);
          if ((uVar5 & 1) != 0) {
            (*(code *)PTR__ZNK4Aska9Semaphore6SignalEv_02c96cd0)(param_1 + 0x500);
            return;
          }
        }
        return;
      }
    }
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar4) {
      *piVar1 = 0;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
  DataMemoryBarrier(2,3);
  goto code_r0x022f115c;
}

// ==== Aska::Yayoi::Downloader::DownloadContext::OnReceiving(Aska::Status, Aska::TSharedPointer<Aska::Yayoi::TDataSuite<Aska::Yayoi::TProtocolSuite<Aska::Yayoi::HttpProtocol, Aska::Yayoi::SSLProtocol, Aska::Yayoi::NoProtocol<2> > > >, char const*)
// vaddr 0x21f1240 | ghidra 0x22f1240 | size 504 | symbol _ZN4Aska5Yayoi10Downloader15DownloadContext11OnReceivingENS_6StatusENS_14TSharedPointerINS0_10TDataSuiteINS0_14TProtocolSuiteINS0_12HttpProtocolENS0_11SSLProtocolENS0_10NoProtocolILi2EEEEEEEEEPKc | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8
_ZN4Aska5Yayoi10Downloader15DownloadContext11OnReceivingENS_6StatusENS_14TSharedPointerINS0_10TDataSuiteINS0_14TProtocolSuiteINS0_12HttpProtocolENS0_11SSLProtocolENS0_10NoProtocolILi2EEEEEEEEEPKc
          (long *param_1,undefined8 *param_2,long *param_3,undefined8 param_4)

{
  int iVar1;
  long lVar2;
  int *piVar3;
  char cVar4;
  bool bVar5;
  long lVar6;
  code *pcVar7;
  long lVar8;
  float fVar9;
  long lStack_78;
  int *piStack_70;
  undefined8 uStack_68;
  undefined8 uStack_60;
  undefined8 uStack_58;
  
  lVar2 = *param_3;
  piVar3 = (int *)param_3[1];
  if (piVar3 != (int *)0x0) {
    do {
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar3,0x10);
      if (bVar5) {
        *piVar3 = *piVar3 + 1;
        cVar4 = ExclusiveMonitorsStatus();
      }
    } while (cVar4 != '\0');
    do {
      iVar1 = *piVar3;
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar3,0x10);
      if (bVar5) {
        *piVar3 = iVar1 + -1;
        cVar4 = ExclusiveMonitorsStatus();
      }
    } while (cVar4 != '\0');
    if (iVar1 != 1) goto code_r0x022f12e8;
  }
  if (lVar2 != 0) {
    Aska::Yayoi::SSLProtocoledData::FreeInnerData()(lVar2 + 0x198);
    Aska::Yayoi::HttpProtocoledData::~HttpProtocoledData()(lVar2);
    operator delete(void*)(lVar2);
  }
  if (piVar3 != (int *)0x0) {
    Aska::TSharedPointerCode::DeleteCounter(int*)(piVar3);
  }
code_r0x022f12e8:
  if (*(int *)(lVar2 + 0x8c) - 200U < 100) {
    lVar8 = *(long *)(lVar2 + 0x58);
    lVar6 = (**(code **)(*(long *)param_1[1] + 0x30))
                      ((long *)param_1[1],*(undefined8 *)(lVar2 + 0x28),1,lVar8);
    fVar9 = _UNK_029d33c0;
    if (*(long *)(lVar2 + 0x38) != 0) {
      fVar9 = (float)*(ulong *)(*(long *)(lVar2 + 0x38) + 0x18);
    }
    fVar9 = fVar9 / (float)*(ulong *)(lVar2 + 0x50);
    if (lVar6 == lVar8) {
      uStack_58 = 0;
      Aska::Yayoi::Downloader::DownloadContext::SetDownloadStatus(Aska::Status, int, float, unsigned long)(fVar9,param_1,&uStack_58,0);
      return 1;
    }
    uStack_60 = 0xfffffffffffffc33;
    Aska::Yayoi::Downloader::DownloadContext::SetDownloadStatus(Aska::Status, int, float, unsigned long)(fVar9,param_1,&uStack_60,0);
  }
  else {
    uStack_68 = *param_2;
    pcVar7 = *(code **)(*param_1 + 0x50);
    lStack_78 = *param_3;
    piStack_70 = (int *)param_3[1];
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
    (*pcVar7)(param_1,&uStack_68,param_4,&lStack_78);
    lVar2 = lStack_78;
    if (piStack_70 != (int *)0x0) {
      do {
        iVar1 = *piStack_70;
        cVar4 = '\x01';
        bVar5 = (bool)ExclusiveMonitorPass(piStack_70,0x10);
        if (bVar5) {
          *piStack_70 = iVar1 + -1;
          cVar4 = ExclusiveMonitorsStatus();
        }
      } while (cVar4 != '\0');
      if (iVar1 != 1) {
        return 0;
      }
    }
    if (lStack_78 != 0) {
      Aska::Yayoi::SSLProtocoledData::FreeInnerData()(lStack_78 + 0x198);
      Aska::Yayoi::HttpProtocoledData::~HttpProtocoledData()(lVar2);
      operator delete(void*)(lVar2);
    }
    if (piStack_70 == (int *)0x0) {
      return 0;
    }
    Aska::TSharedPointerCode::DeleteCounter(int*)();
  }
  return 0;
}

// ==== Aska::Yayoi::Downloader::DownloadContext::SetDownloadStatus(Aska::Status, int, float, unsigned long)
// vaddr 0x21f1438 | ghidra 0x22f1438 | size 396 | symbol _ZN4Aska5Yayoi10Downloader15DownloadContext17SetDownloadStatusENS_6StatusEifm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi10Downloader15DownloadContext17SetDownloadStatusENS_6StatusEifm
               (undefined4 param_1,long param_2,undefined8 *param_3,undefined4 param_4,
               undefined8 param_5)

{
  int *piVar1;
  int *piVar2;
  char cVar3;
  bool bVar4;
  ulong uVar5;
  int iVar6;
  undefined8 uVar7;
  
  piVar1 = (int *)(param_2 + 0x4c0);
  iVar6 = 0;
  do {
    while (*piVar1 != -1) {
      ClearExclusiveLocal();
      bVar4 = 0x1fe < iVar6;
      iVar6 = iVar6 + 1;
      if (bVar4) {
        piVar2 = (int *)(param_2 + 0x4c4);
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
              uVar5 = Aska::Semaphore::IsReady() const(param_2 + 0x500);
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
                Aska::Semaphore::Wait() const(param_2 + 0x500);
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
                if (cVar3 == '\0') goto code_r0x022f15ac;
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
code_r0x022f15ac:
        do {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
          if (bVar4) {
            *piVar2 = *piVar2 + -1;
            cVar3 = ExclusiveMonitorsStatus();
          }
        } while (cVar3 != '\0');
        DataMemoryBarrier(2,3);
code_r0x022f14c4:
        uVar7 = *param_3;
        *(undefined4 *)(param_2 + 0x668) = param_4;
        *(undefined4 *)(param_2 + 0x66c) = param_1;
        *(undefined8 *)(param_2 + 0x670) = param_5;
        *(undefined8 *)(param_2 + 0x660) = uVar7;
        DataMemoryBarrier(2,3);
        *(undefined4 *)(param_2 + 0x4c0) = 0xffffffff;
        DataMemoryBarrier(2,3);
        piVar1 = (int *)(param_2 + 0x4c4);
        if (0x14 < *piVar1) {
          do {
            cVar3 = '\x01';
            bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
            if (bVar4) {
              *piVar1 = *piVar1 + -1;
              cVar3 = ExclusiveMonitorsStatus();
            }
          } while (cVar3 != '\0');
          uVar5 = Aska::Semaphore::IsReady() const(param_2 + 0x500);
          if ((uVar5 & 1) != 0) {
            (*(code *)PTR__ZNK4Aska9Semaphore6SignalEv_02c96cd0)(param_2 + 0x500);
            return;
          }
        }
        return;
      }
    }
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar4) {
      *piVar1 = 0;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
  DataMemoryBarrier(2,3);
  goto code_r0x022f14c4;
}

// ==== Aska::Yayoi::Downloader::DownloadContext::OnReceive(Aska::Status, Aska::TSharedPointer<Aska::Yayoi::TDataSuite<Aska::Yayoi::TProtocolSuite<Aska::Yayoi::HttpProtocol, Aska::Yayoi::SSLProtocol, Aska::Yayoi::NoProtocol<2> > > >, char const*)
// vaddr 0x21f15c4 | ghidra 0x22f15c4 | size 620 | symbol _ZN4Aska5Yayoi10Downloader15DownloadContext9OnReceiveENS_6StatusENS_14TSharedPointerINS0_10TDataSuiteINS0_14TProtocolSuiteINS0_12HttpProtocolENS0_11SSLProtocolENS0_10NoProtocolILi2EEEEEEEEEPKc | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi10Downloader15DownloadContext9OnReceiveENS_6StatusENS_14TSharedPointerINS0_10TDataSuiteINS0_14TProtocolSuiteINS0_12HttpProtocolENS0_11SSLProtocolENS0_10NoProtocolILi2EEEEEEEEEPKc
               (long *param_1,undefined8 *param_2,long *param_3,undefined8 param_4)

{
  int iVar1;
  long lVar2;
  int *piVar3;
  char cVar4;
  bool bVar5;
  long lVar6;
  long lVar7;
  ulong uVar8;
  undefined8 *puVar9;
  code *pcVar10;
  ulong uVar11;
  undefined8 uVar12;
  undefined1 auStack_90 [8];
  long lStack_88;
  int *piStack_80;
  undefined8 uStack_78;
  undefined8 uStack_70;
  undefined8 uStack_68;
  undefined8 uStack_60;
  undefined8 uStack_58;
  
  if (param_1[0xcf] == 0) {
    return;
  }
  lVar2 = *param_3;
  piVar3 = (int *)param_3[1];
  if (piVar3 != (int *)0x0) {
    do {
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar3,0x10);
      if (bVar5) {
        *piVar3 = *piVar3 + 1;
        cVar4 = ExclusiveMonitorsStatus();
      }
    } while (cVar4 != '\0');
    do {
      iVar1 = *piVar3;
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar3,0x10);
      if (bVar5) {
        *piVar3 = iVar1 + -1;
        cVar4 = ExclusiveMonitorsStatus();
      }
    } while (cVar4 != '\0');
    if (iVar1 != 1) goto code_r0x022f1674;
  }
  if (lVar2 != 0) {
    Aska::Yayoi::SSLProtocoledData::FreeInnerData()(lVar2 + 0x198);
    Aska::Yayoi::HttpProtocoledData::~HttpProtocoledData()(lVar2);
    operator delete(void*)(lVar2);
  }
  if (piVar3 != (int *)0x0) {
    Aska::TSharedPointerCode::DeleteCounter(int*)(piVar3);
  }
code_r0x022f1674:
  if (*(int *)(lVar2 + 0x8c) - 200U < 100) {
    uVar12 = *(undefined8 *)(lVar2 + 0x28);
    lVar7 = *(long *)(lVar2 + 0x50);
    uVar11 = *(ulong *)(lVar2 + 0x58);
    lVar6 = (**(code **)(*(long *)param_1[1] + 0x18))();
    if ((ulong)(lVar7 - lVar6) < uVar11) {
      lVar6 = *(long *)(lVar2 + 0x50);
      lVar7 = (**(code **)(*(long *)param_1[1] + 0x18))();
      uVar11 = lVar6 - lVar7;
    }
    if (uVar11 == 0) {
      uVar8 = 0;
    }
    else {
      uVar8 = (**(code **)(*(long *)param_1[1] + 0x30))((long *)param_1[1],uVar12,1,uVar11);
    }
    if ((*(long *)(lVar2 + 0x38) == 0) ||
       (*(ulong *)(lVar2 + 0x50) <= *(ulong *)(*(long *)(lVar2 + 0x38) + 0x18))) {
      if (uVar11 == 0) {
        puVar9 = &uStack_70;
        uStack_70 = 0;
      }
      else if (uVar8 == uVar11) {
        uStack_60 = 0;
        puVar9 = &uStack_60;
      }
      else {
        uStack_68 = 0xffffffffffffffff;
        puVar9 = &uStack_68;
      }
    }
    else {
      uStack_58 = 0xfffffffffffffc09;
      puVar9 = &uStack_58;
    }
    Aska::Yayoi::Downloader::DownloadContext::SetDownloadStatus(Aska::Status, int, float, unsigned long)(0x3f800000,param_1,puVar9,0);
    Aska::Yayoi::Downloader::AddDownloadFinishQueue(unsigned int)(auStack_90,param_1[0xcf],(int)param_1[0xd1]);
  }
  else {
    uStack_78 = *param_2;
    pcVar10 = *(code **)(*param_1 + 0x50);
    lStack_88 = *param_3;
    piStack_80 = (int *)param_3[1];
    if (piStack_80 != (int *)0x0) {
      do {
        cVar4 = '\x01';
        bVar5 = (bool)ExclusiveMonitorPass(piStack_80,0x10);
        if (bVar5) {
          *piStack_80 = *piStack_80 + 1;
          cVar4 = ExclusiveMonitorsStatus();
        }
      } while (cVar4 != '\0');
    }
    (*pcVar10)(param_1,&uStack_78,param_4,&lStack_88);
    lVar2 = lStack_88;
    if (piStack_80 != (int *)0x0) {
      do {
        iVar1 = *piStack_80;
        cVar4 = '\x01';
        bVar5 = (bool)ExclusiveMonitorPass(piStack_80,0x10);
        if (bVar5) {
          *piStack_80 = iVar1 + -1;
          cVar4 = ExclusiveMonitorsStatus();
        }
      } while (cVar4 != '\0');
      if (iVar1 + -1 != 0) {
        return;
      }
    }
    if (lStack_88 != 0) {
      Aska::Yayoi::SSLProtocoledData::FreeInnerData()(lStack_88 + 0x198);
      Aska::Yayoi::HttpProtocoledData::~HttpProtocoledData()(lVar2);
      operator delete(void*)(lVar2);
    }
    if (piStack_80 != (int *)0x0) {
      Aska::TSharedPointerCode::DeleteCounter(int*)();
    }
  }
  return;
}

// ==== Aska::Yayoi::Downloader::DownloadContext::OnError(Aska::Status, char const*, Aska::TSharedPointer<Aska::Yayoi::TDataSuite<Aska::Yayoi::TProtocolSuite<Aska::Yayoi::HttpProtocol, Aska::Yayoi::SSLProtocol, Aska::Yayoi::NoProtocol<2> > > >)
// vaddr 0x21f1830 | ghidra 0x22f1830 | size 316 | symbol _ZN4Aska5Yayoi10Downloader15DownloadContext7OnErrorENS_6StatusEPKcNS_14TSharedPointerINS0_10TDataSuiteINS0_14TProtocolSuiteINS0_12HttpProtocolENS0_11SSLProtocolENS0_10NoProtocolILi2EEEEEEEEE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi10Downloader15DownloadContext7OnErrorENS_6StatusEPKcNS_14TSharedPointerINS0_10TDataSuiteINS0_14TProtocolSuiteINS0_12HttpProtocolENS0_11SSLProtocolENS0_10NoProtocolILi2EEEEEEEEE
               (long param_1,long *param_2,undefined8 param_3,long *param_4)

{
  int iVar1;
  int *piVar2;
  char cVar3;
  bool bVar4;
  long *plVar5;
  long lVar6;
  undefined1 auStack_68 [8];
  long lStack_60;
  long lStack_58;
  long lStack_50;
  long lStack_48;
  long lStack_38;
  
  if (*(long *)(param_1 + 0x678) == 0) {
    return;
  }
  lVar6 = *param_2;
  if (lVar6 == -0x3b4) {
    if (*(long *)(param_1 + 0x660) < 0) goto code_r0x022f1944;
    lStack_38 = -0x3b4;
    plVar5 = &lStack_38;
  }
  else if (lVar6 < 0) {
    if (lVar6 == -0x3b5) {
      lVar6 = *param_4;
      piVar2 = (int *)param_4[1];
      if (piVar2 == (int *)0x0) {
joined_r0x022f18e4:
        lStack_48 = lVar6;
        if (lVar6 != 0) {
          Aska::Yayoi::SSLProtocoledData::FreeInnerData()(lVar6 + 0x198);
          Aska::Yayoi::HttpProtocoledData::~HttpProtocoledData()(lVar6);
          operator delete(void*)(lVar6);
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
        if (iVar1 == 1) goto joined_r0x022f18e4;
      }
      lStack_48 = 0;
      lStack_50 = *param_2;
      Aska::Yayoi::Downloader::DownloadContext::SetDownloadStatus(Aska::Status, int)(param_1,&lStack_50,*(undefined4 *)(lVar6 + 0x8c));
      lVar6 = *param_2;
    }
    plVar5 = &lStack_58;
    lStack_58 = lVar6;
  }
  else {
    plVar5 = &lStack_60;
    lStack_60 = -1;
  }
  Aska::Yayoi::Downloader::DownloadContext::SetDownloadStatus(Aska::Status)(param_1,plVar5);
code_r0x022f1944:
  Aska::Yayoi::Downloader::AddDownloadFinishQueue(unsigned int)(auStack_68,*(undefined8 *)(param_1 + 0x678),*(undefined4 *)(param_1 + 0x688));
  return;
}

// ==== Aska::Yayoi::Downloader::DownloadContext::SetDownloadStatus(Aska::Status, int)
// vaddr 0x21f196c | ghidra 0x22f196c | size 368 | symbol _ZN4Aska5Yayoi10Downloader15DownloadContext17SetDownloadStatusENS_6StatusEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi10Downloader15DownloadContext17SetDownloadStatusENS_6StatusEi
               (long param_1,undefined8 *param_2,undefined4 param_3)

{
  int *piVar1;
  int *piVar2;
  char cVar3;
  bool bVar4;
  ulong uVar5;
  int iVar6;
  undefined8 uVar7;
  
  piVar1 = (int *)(param_1 + 0x4c0);
  iVar6 = 0;
  do {
    while (*piVar1 != -1) {
      ClearExclusiveLocal();
      bVar4 = 0x1fe < iVar6;
      iVar6 = iVar6 + 1;
      if (bVar4) {
        piVar2 = (int *)(param_1 + 0x4c4);
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
              uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0x500);
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
                Aska::Semaphore::Wait() const(param_1 + 0x500);
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
                if (cVar3 == '\0') goto code_r0x022f1ac4;
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
code_r0x022f1ac4:
        do {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
          if (bVar4) {
            *piVar2 = *piVar2 + -1;
            cVar3 = ExclusiveMonitorsStatus();
          }
        } while (cVar3 != '\0');
        DataMemoryBarrier(2,3);
code_r0x022f19ec:
        uVar7 = *param_2;
        *(undefined4 *)(param_1 + 0x668) = param_3;
        *(undefined8 *)(param_1 + 0x660) = uVar7;
        DataMemoryBarrier(2,3);
        *(undefined4 *)(param_1 + 0x4c0) = 0xffffffff;
        DataMemoryBarrier(2,3);
        piVar1 = (int *)(param_1 + 0x4c4);
        if (0x14 < *piVar1) {
          do {
            cVar3 = '\x01';
            bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
            if (bVar4) {
              *piVar1 = *piVar1 + -1;
              cVar3 = ExclusiveMonitorsStatus();
            }
          } while (cVar3 != '\0');
          uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0x500);
          if ((uVar5 & 1) != 0) {
            (*(code *)PTR__ZNK4Aska9Semaphore6SignalEv_02c96cd0)(param_1 + 0x500);
            return;
          }
        }
        return;
      }
    }
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar4) {
      *piVar1 = 0;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
  DataMemoryBarrier(2,3);
  goto code_r0x022f19ec;
}

// ==== Aska::Yayoi::Downloader::DownloadStream::Open(char const*)
// vaddr 0x21f1adc | ghidra 0x22f1adc | size 160 | symbol _ZN4Aska5Yayoi10Downloader14DownloadStream4OpenEPKc | lib libSOA-3.7.0.so | 2026-10-04
uint _ZN4Aska5Yayoi10Downloader14DownloadStream4OpenEPKc(long param_1,char *param_2)

{
  uint uVar1;
  ulong uVar2;
  undefined1 auStack_168 [328];
  
  if ((param_2 == (char *)0x0) || (*param_2 == '\0')) {
    uVar1 = 0;
  }
  else {
    uVar2 = strlen(param_2);
    if (uVar2 < 0x148) {
      strcpy(param_1 + 0x38,param_2);
    }
    else {
      raise(5);
    }
    __aska_snprintf_s(char*, unsigned long, unsigned long, char const*, ...)(auStack_168,0x148,0xffffffffffffffff,&UNK_029dbc6a/*"%s.%s"*/,param_2,&UNK_02866c1e/*"tmp"*/);
    uVar1 = Aska::FileStream::Open(char const*, bool, bool, Aska::Machine::Endian)(param_1 + 8,auStack_168,0,1,3);
  }
  return uVar1 & 1;
}

// ==== Aska::Yayoi::Downloader::DownloadStream::Close(bool)
// vaddr 0x21f1b7c | ghidra 0x22f1b7c | size 168 | symbol _ZN4Aska5Yayoi10Downloader14DownloadStream5CloseEb | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska5Yayoi10Downloader14DownloadStream5CloseEb(long param_1,ulong param_2)

{
  ulong uVar1;
  undefined1 auStack_168 [328];
  
  Aska::FileStream::Close()(param_1 + 8);
  param_1 = param_1 + 0x38;
  __aska_snprintf_s(char*, unsigned long, unsigned long, char const*, ...)(auStack_168,0x148,0xffffffffffffffff,&UNK_029dbc6a/*"%s.%s"*/,param_1,&UNK_02866c1e/*"tmp"*/);
  if ((param_2 & 1) == 0) {
    uVar1 = Aska::File::DeleteFile(char const*)(auStack_168);
    if ((uVar1 & 1) != 0) {
      return 1;
    }
  }
  else {
    uVar1 = Aska::File::DoesExist(char const*, bool)(param_1,0);
    if ((((uVar1 & 1) == 0) || (uVar1 = Aska::File::DeleteFile(char const*)(param_1), (uVar1 & 1) != 0)) &&
       (uVar1 = Aska::File::MoveFile(char const*, char const*)(auStack_168,param_1), (uVar1 & 1) != 0)) {
      return 1;
    }
    Aska::File::DeleteFile(char const*)(auStack_168);
  }
  return 0;
}

// ==== Aska::Yayoi::Downloader::DownloadStream::~DownloadStream()
// vaddr 0x21f1c24 | ghidra 0x22f1c24 | size 92 | symbol _ZN4Aska5Yayoi10Downloader14DownloadStreamD2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi10Downloader14DownloadStreamD2Ev(long *param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZTVN4Aska5Yayoi10Downloader14DownloadStreamE_02cc1c28 + 0x10;
  param_1[1] = (long)(PTR__ZTVN4Aska10FileStreamE_02cbc9f8 + 0x10);
  *param_1 = (long)puVar1;
  Aska::FileStream::Close()(param_1 + 1);
  param_1[2] = (long)(PTR__ZTVN4Aska4FileE_02cb6e28 + 0x10);
  if (param_1[4] != 0) {
    (*(code *)PTR__ZN4Aska4File5CloseEv_02c8e880)(param_1 + 2);
    return;
  }
  return;
}

// ==== Aska::Yayoi::Downloader::DownloadStream::~DownloadStream()
// vaddr 0x21f1c80 | ghidra 0x22f1c80 | size 92 | symbol _ZN4Aska5Yayoi10Downloader14DownloadStreamD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi10Downloader14DownloadStreamD0Ev(long *param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZTVN4Aska5Yayoi10Downloader14DownloadStreamE_02cc1c28 + 0x10;
  param_1[1] = (long)(PTR__ZTVN4Aska10FileStreamE_02cbc9f8 + 0x10);
  *param_1 = (long)puVar1;
  Aska::FileStream::Close()(param_1 + 1);
  param_1[2] = (long)(PTR__ZTVN4Aska4FileE_02cb6e28 + 0x10);
  if (param_1[4] != 0) {
    Aska::File::Close()();
  }
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::Yayoi::Downloader::DownloadStream::IsReady() const
// vaddr 0x21f1cdc | ghidra 0x22f1cdc | size 16 | symbol _ZNK4Aska5Yayoi10Downloader14DownloadStream7IsReadyEv | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK4Aska5Yayoi10Downloader14DownloadStream7IsReadyEv(long param_1)

{
  return *(long *)(param_1 + 0x20) != 0;
}

// ==== Aska::Yayoi::Downloader::DownloadStream::Tell() const
// vaddr 0x21f1cec | ghidra 0x22f1cec | size 8 | symbol _ZNK4Aska5Yayoi10Downloader14DownloadStream4TellEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK4Aska5Yayoi10Downloader14DownloadStream4TellEv(long param_1)

{
  (*(code *)PTR__ZNK4Aska10FileStream4TellEv_02cb2738)(param_1 + 8);
  return;
}

// ==== Aska::Yayoi::Downloader::DownloadStream::Seek(long, int)
// vaddr 0x21f1cf4 | ghidra 0x22f1cf4 | size 8 | symbol _ZN4Aska5Yayoi10Downloader14DownloadStream4SeekEli | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi10Downloader14DownloadStream4SeekEli(long param_1)

{
  (*(code *)PTR__ZN4Aska10FileStream4SeekEli_02ca4d68)(param_1 + 8);
  return;
}

// ==== Aska::Yayoi::Downloader::DownloadStream::Read(void*, unsigned long, unsigned long)
// vaddr 0x21f1cfc | ghidra 0x22f1cfc | size 8 | symbol _ZN4Aska5Yayoi10Downloader14DownloadStream4ReadEPvmm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi10Downloader14DownloadStream4ReadEPvmm(long param_1)

{
  (*(code *)PTR__ZN4Aska10FileStream4ReadEPvmm_02c9e0d0)(param_1 + 8);
  return;
}

// ==== Aska::Yayoi::Downloader::DownloadStream::Write(void const*, unsigned long, unsigned long)
// vaddr 0x21f1d04 | ghidra 0x22f1d04 | size 8 | symbol _ZN4Aska5Yayoi10Downloader14DownloadStream5WriteEPKvmm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi10Downloader14DownloadStream5WriteEPKvmm(long param_1)

{
  (*(code *)PTR__ZN4Aska10FileStream5WriteEPKvmm_02c93088)(param_1 + 8);
  return;
}

// ==== Aska::Yayoi::Downloader::DownloadStream::Flush()
// vaddr 0x21f1d0c | ghidra 0x22f1d0c | size 8 | symbol _ZN4Aska5Yayoi10Downloader14DownloadStream5FlushEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi10Downloader14DownloadStream5FlushEv(long param_1)

{
  (*(code *)PTR__ZN4Aska10FileStream5FlushEv_02cadfe0)(param_1 + 8);
  return;
}

// ==== Aska::Yayoi::Downloader::DownloadStream::IsEnd(long*) const
// vaddr 0x21f1d14 | ghidra 0x22f1d14 | size 8 | symbol _ZNK4Aska5Yayoi10Downloader14DownloadStream5IsEndEPl | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK4Aska5Yayoi10Downloader14DownloadStream5IsEndEPl(long param_1)

{
  (*(code *)PTR__ZNK4Aska10FileStream5IsEndEPl_02c9e928)(param_1 + 8);
  return;
}

// ==== Aska::Yayoi::Downloader::DownloadStream::SetLastError(long) const
// vaddr 0x21f1d1c | ghidra 0x22f1d1c | size 12 | symbol _ZNK4Aska5Yayoi10Downloader14DownloadStream12SetLastErrorEl | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZNK4Aska5Yayoi10Downloader14DownloadStream12SetLastErrorEl(long param_1,undefined8 param_2)

{
  *(undefined8 *)(param_1 + 0x28) = param_2;
  return param_2;
}

// ==== Aska::Yayoi::Downloader::DownloadStream::GetLastError() const
// vaddr 0x21f1d28 | ghidra 0x22f1d28 | size 8 | symbol _ZNK4Aska5Yayoi10Downloader14DownloadStream12GetLastErrorEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska5Yayoi10Downloader14DownloadStream12GetLastErrorEv(long param_1)

{
  return *(undefined8 *)(param_1 + 0x28);
}

// ==== Aska::Yayoi::Downloader::DownloadContext::OnStart(Aska::Status, char const*)
// vaddr 0x21f1d30 | ghidra 0x22f1d30 | size 4 | symbol _ZN4Aska5Yayoi10Downloader15DownloadContext7OnStartENS_6StatusEPKc | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi10Downloader15DownloadContext7OnStartENS_6StatusEPKc(void)

{
  return;
}

// ==== Aska::Yayoi::Downloader::DownloadContext::OnAccept(Aska::Status, Aska::Yayoi::Socket, char const*)
// vaddr 0x21f1d34 | ghidra 0x22f1d34 | size 4 | symbol _ZN4Aska5Yayoi10Downloader15DownloadContext8OnAcceptENS_6StatusENS0_6SocketEPKc | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi10Downloader15DownloadContext8OnAcceptENS_6StatusENS0_6SocketEPKc(void)

{
  return;
}

// ==== Aska::Yayoi::Downloader::DownloadContext::OnSend(Aska::Status, long, char const*)
// vaddr 0x21f1d38 | ghidra 0x22f1d38 | size 4 | symbol _ZN4Aska5Yayoi10Downloader15DownloadContext6OnSendENS_6StatusElPKc | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi10Downloader15DownloadContext6OnSendENS_6StatusElPKc(void)

{
  return;
}

// ==== Aska::Yayoi::Downloader::DownloadContext::OnReceiveUDP(Aska::Status, Aska::TSharedPointer<Aska::Yayoi::TDataSuite<Aska::Yayoi::TProtocolSuite<Aska::Yayoi::HttpProtocol, Aska::Yayoi::SSLProtocol, Aska::Yayoi::NoProtocol<2> > > >, Aska::Yayoi::IPAddress const&, char const*)
// vaddr 0x21f1d3c | ghidra 0x22f1d3c | size 4 | symbol _ZN4Aska5Yayoi10Downloader15DownloadContext12OnReceiveUDPENS_6StatusENS_14TSharedPointerINS0_10TDataSuiteINS0_14TProtocolSuiteINS0_12HttpProtocolENS0_11SSLProtocolENS0_10NoProtocolILi2EEEEEEEEERKNS0_9IPAddressEPKc | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi10Downloader15DownloadContext12OnReceiveUDPENS_6StatusENS_14TSharedPointerINS0_10TDataSuiteINS0_14TProtocolSuiteINS0_12HttpProtocolENS0_11SSLProtocolENS0_10NoProtocolILi2EEEEEEEEERKNS0_9IPAddressEPKc
               (void)

{
  return;
}

// ==== Aska::Yayoi::Downloader::DownloadContext::OnReceivingUDP(Aska::Status, Aska::TSharedPointer<Aska::Yayoi::TDataSuite<Aska::Yayoi::TProtocolSuite<Aska::Yayoi::HttpProtocol, Aska::Yayoi::SSLProtocol, Aska::Yayoi::NoProtocol<2> > > >, Aska::Yayoi::IPAddress const&, char const*)
// vaddr 0x21f1d40 | ghidra 0x22f1d40 | size 8 | symbol _ZN4Aska5Yayoi10Downloader15DownloadContext14OnReceivingUDPENS_6StatusENS_14TSharedPointerINS0_10TDataSuiteINS0_14TProtocolSuiteINS0_12HttpProtocolENS0_11SSLProtocolENS0_10NoProtocolILi2EEEEEEEEERKNS0_9IPAddressEPKc | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska5Yayoi10Downloader15DownloadContext14OnReceivingUDPENS_6StatusENS_14TSharedPointerINS0_10TDataSuiteINS0_14TProtocolSuiteINS0_12HttpProtocolENS0_11SSLProtocolENS0_10NoProtocolILi2EEEEEEEEERKNS0_9IPAddressEPKc
          (void)

{
  return 1;
}

// ==== Aska::Yayoi::Downloader::DownloadContext::OnDisconnect(Aska::Status, Aska::TSharedPointer<Aska::Yayoi::TDataSuite<Aska::Yayoi::TProtocolSuite<Aska::Yayoi::HttpProtocol, Aska::Yayoi::SSLProtocol, Aska::Yayoi::NoProtocol<2> > > >, char const*)
// vaddr 0x21f1d48 | ghidra 0x22f1d48 | size 4 | symbol _ZN4Aska5Yayoi10Downloader15DownloadContext12OnDisconnectENS_6StatusENS_14TSharedPointerINS0_10TDataSuiteINS0_14TProtocolSuiteINS0_12HttpProtocolENS0_11SSLProtocolENS0_10NoProtocolILi2EEEEEEEEEPKc | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi10Downloader15DownloadContext12OnDisconnectENS_6StatusENS_14TSharedPointerINS0_10TDataSuiteINS0_14TProtocolSuiteINS0_12HttpProtocolENS0_11SSLProtocolENS0_10NoProtocolILi2EEEEEEEEEPKc
               (void)

{
  return;
}

// ==== Aska::Yayoi::Downloader::DownloadContext::OnShutdown(Aska::Status, char const*)
// vaddr 0x21f1d4c | ghidra 0x22f1d4c | size 8 | symbol _ZN4Aska5Yayoi10Downloader15DownloadContext10OnShutdownENS_6StatusEPKc | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska5Yayoi10Downloader15DownloadContext10OnShutdownENS_6StatusEPKc(void)

{
  return 0;
}

// ==== Aska::Yayoi::Downloader::DownloadElement::~DownloadElement()
// vaddr 0x21f1d54 | ghidra 0x22f1d54 | size 184 | symbol _ZN4Aska5Yayoi10Downloader15DownloadElementD2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi10Downloader15DownloadElementD2Ev(long *param_1)

{
  undefined *puVar1;
  int iVar2;
  char cVar3;
  bool bVar4;
  undefined *puVar5;
  int *piVar6;
  long lVar7;
  
  puVar5 = PTR__ZTVN4Aska10FileStreamE_02cbc9f8;
  puVar1 = PTR__ZTVN4Aska5Yayoi10Downloader14DownloadStreamE_02cc1c28 + 0x10;
  *param_1 = (long)(PTR__ZTVN4Aska5Yayoi10Downloader15DownloadElementE_02cc0d00 + 0x10);
  param_1[0x33] = (long)(puVar5 + 0x10);
  param_1[0x32] = (long)puVar1;
  Aska::FileStream::Close()(param_1 + 0x33);
  param_1[0x34] = (long)(PTR__ZTVN4Aska4FileE_02cb6e28 + 0x10);
  if (param_1[0x36] != 0) {
    Aska::File::Close()(param_1 + 0x34);
  }
  piVar6 = (int *)param_1[7];
  if (piVar6 != (int *)0x0) {
    do {
      iVar2 = *piVar6;
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar6,0x10);
      if (bVar4) {
        *piVar6 = iVar2 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
    if (iVar2 + -1 != 0) goto code_r0x022f1dfc;
  }
  lVar7 = param_1[6];
  if (lVar7 != 0) {
    Aska::Yayoi::URI::DeleteBuffer()(lVar7);
    operator delete(void*)(lVar7);
  }
  if (param_1[7] != 0) {
    Aska::TSharedPointerCode::DeleteCounter(int*)();
  }
code_r0x022f1dfc:
  param_1[6] = 0;
  param_1[7] = 0;
  return;
}

// ==== Aska::Yayoi::Downloader::DownloadElement::~DownloadElement()
// vaddr 0x21f1e0c | ghidra 0x22f1e0c | size 188 | symbol _ZN4Aska5Yayoi10Downloader15DownloadElementD0Ev | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Possible PIC construction at 0x022f1ea4: Changing call to branch */

void _ZN4Aska5Yayoi10Downloader15DownloadElementD0Ev(long *param_1)

{
  undefined *puVar1;
  int iVar2;
  char cVar3;
  bool bVar4;
  undefined *puVar5;
  int *piVar6;
  long *plVar7;
  
  puVar5 = PTR__ZTVN4Aska10FileStreamE_02cbc9f8;
  puVar1 = PTR__ZTVN4Aska5Yayoi10Downloader14DownloadStreamE_02cc1c28 + 0x10;
  *param_1 = (long)(PTR__ZTVN4Aska5Yayoi10Downloader15DownloadElementE_02cc0d00 + 0x10);
  param_1[0x33] = (long)(puVar5 + 0x10);
  param_1[0x32] = (long)puVar1;
  Aska::FileStream::Close()(param_1 + 0x33);
  param_1[0x34] = (long)(PTR__ZTVN4Aska4FileE_02cb6e28 + 0x10);
  if (param_1[0x36] != 0) {
    Aska::File::Close()(param_1 + 0x34);
  }
  piVar6 = (int *)param_1[7];
  if (piVar6 == (int *)0x0) {
code_r0x022f1e90:
    plVar7 = (long *)param_1[6];
    if (plVar7 != (long *)0x0) {
      Aska::Yayoi::URI::DeleteBuffer()(plVar7);
      param_1 = plVar7;
      goto code_r0x011d8ed0;
    }
    if (param_1[7] != 0) {
      Aska::TSharedPointerCode::DeleteCounter(int*)();
    }
  }
  else {
    do {
      iVar2 = *piVar6;
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar6,0x10);
      if (bVar4) {
        *piVar6 = iVar2 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
    if (iVar2 + -1 == 0) goto code_r0x022f1e90;
  }
  param_1[6] = 0;
  param_1[7] = 0;
code_r0x011d8ed0:
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::Yayoi::Downloader::WorkerThread::~WorkerThread()
// vaddr 0x21f1ec8 | ghidra 0x22f1ec8 | size 24 | symbol _ZN4Aska5Yayoi10Downloader12WorkerThreadD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi10Downloader12WorkerThreadD0Ev(undefined8 param_1)

{
  Aska::Yayoi::Downloader::WorkerThread::~WorkerThread()();
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}


// FAILED to create function at 029d33f0 typeinfo name for Aska::Yayoi::Downloader::DownloadStream
// FAILED to create function at 029d3420 typeinfo name for Aska::Yayoi::Downloader::IDownloadStream
// FAILED to create function at 029d3450 typeinfo name for Aska::Yayoi::Downloader::DownloadContext
// FAILED to create function at 029d3480 typeinfo name for Aska::Yayoi::Downloader::DownloadElement
// FAILED to create function at 029d34b0 typeinfo name for Aska::Yayoi::Downloader::WorkerThread
