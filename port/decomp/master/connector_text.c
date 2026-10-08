// port/decomp/master/connector_text.c: Ghidra decompiles for the master subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-08 13:04 UTC: tools/decomp.sh '--into' 'master/connector_text' 'CSimpleSqliteConnector<MasterDB::CText,'

// ==== CSimpleSqliteConnector<MasterDB::CText, Aska::Yayoi::TEntity_Slave<Aska::Yayoi::SQLiteDriver, MasterDB::CText, Aska::Yayoi::NoCache> >::~CSimpleSqliteConnector()
// vaddr 0x16fe248 | ghidra 0x17fe248 | size 4 | symbol _ZN22CSimpleSqliteConnectorIN8MasterDB5CTextEN4Aska5Yayoi13TEntity_SlaveINS3_12SQLiteDriverES1_NS3_7NoCacheEEEED2Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN22CSimpleSqliteConnectorIN8MasterDB5CTextEN4Aska5Yayoi13TEntity_SlaveINS3_12SQLiteDriverES1_NS3_7NoCacheEEEED2Ev
               (void)

{
  return;
}

// ==== CSimpleSqliteConnector<MasterDB::CText, Aska::Yayoi::TEntity_Slave<Aska::Yayoi::SQLiteDriver, MasterDB::CText, Aska::Yayoi::NoCache> >::~CSimpleSqliteConnector()
// vaddr 0x16fe24c | ghidra 0x17fe24c | size 4 | symbol _ZN22CSimpleSqliteConnectorIN8MasterDB5CTextEN4Aska5Yayoi13TEntity_SlaveINS3_12SQLiteDriverES1_NS3_7NoCacheEEEED0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN22CSimpleSqliteConnectorIN8MasterDB5CTextEN4Aska5Yayoi13TEntity_SlaveINS3_12SQLiteDriverES1_NS3_7NoCacheEEEED0Ev
               (void)

{
  (*(code *)PTR__ZdlPv_02ca4758)();
  return;
}

// ==== CSimpleSqliteConnector<MasterDB::CText, Aska::Yayoi::TEntity_Slave<Aska::Yayoi::SQLiteDriver, MasterDB::CText, Aska::Yayoi::NoCache> >::Open(char const*)
// vaddr 0x16fe250 | ghidra 0x17fe250 | size 4 | symbol _ZN22CSimpleSqliteConnectorIN8MasterDB5CTextEN4Aska5Yayoi13TEntity_SlaveINS3_12SQLiteDriverES1_NS3_7NoCacheEEEE4OpenEPKc | lib libSOA-3.7.0.so | 2026-10-08
void _ZN22CSimpleSqliteConnectorIN8MasterDB5CTextEN4Aska5Yayoi13TEntity_SlaveINS3_12SQLiteDriverES1_NS3_7NoCacheEEEE4OpenEPKc
               (void)

{
  return;
}

// ==== CSimpleSqliteConnector<MasterDB::CText, Aska::Yayoi::TEntity_Slave<Aska::Yayoi::SQLiteDriver, MasterDB::CText, Aska::Yayoi::NoCache> >::Close()
// vaddr 0x16fe254 | ghidra 0x17fe254 | size 4 | symbol _ZN22CSimpleSqliteConnectorIN8MasterDB5CTextEN4Aska5Yayoi13TEntity_SlaveINS3_12SQLiteDriverES1_NS3_7NoCacheEEEE5CloseEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN22CSimpleSqliteConnectorIN8MasterDB5CTextEN4Aska5Yayoi13TEntity_SlaveINS3_12SQLiteDriverES1_NS3_7NoCacheEEEE5CloseEv
               (void)

{
  return;
}

// ==== CSimpleSqliteConnector<MasterDB::CText, Aska::Yayoi::TEntity_Slave<Aska::Yayoi::SQLiteDriver, MasterDB::CText, Aska::Yayoi::NoCache> >::QueryToResultObject(unsigned int, Aska::Yayoi::QueryParam*, unsigned int, Aska::Yayoi::TEntityObject<Aska::Yayoi::SQLiteDriver>&)
// vaddr 0x16fe258 | ghidra 0x17fe258 | size 236 | symbol _ZN22CSimpleSqliteConnectorIN8MasterDB5CTextEN4Aska5Yayoi13TEntity_SlaveINS3_12SQLiteDriverES1_NS3_7NoCacheEEEE19QueryToResultObjectEjPNS3_10QueryParamEjRNS3_13TEntityObjectIS5_EE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN22CSimpleSqliteConnectorIN8MasterDB5CTextEN4Aska5Yayoi13TEntity_SlaveINS3_12SQLiteDriverES1_NS3_7NoCacheEEEE19QueryToResultObjectEjPNS3_10QueryParamEjRNS3_13TEntityObjectIS5_EE
               (long param_1,int param_2,undefined8 param_3,undefined4 param_4,undefined8 param_5)

{
  undefined *puVar1;
  undefined *puVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  long lVar5;
  long lStack_48;
  
  puVar2 = PTR__ZN9Framework10TSingletonI18CStaticTransactionE11m_pInstanceE_02cc41b0;
  uVar3 = (**(code **)(*(long *)(*(long *)
                                  PTR__ZN9Framework10TSingletonI18CStaticTransactionE11m_pInstanceE_02cc41b0
                                + 0x40) + 0x20))
                    ((long *)(*(long *)
                               PTR__ZN9Framework10TSingletonI18CStaticTransactionE11m_pInstanceE_02cc41b0
                             + 0x40));
  if ((param_2 < 3) &&
     (puVar1 = PTR__ZZNK22CSimpleSqliteConnectorIN8MasterDB5CTextEN4Aska5Yayoi13TEntity_SlaveINS3_12SQLiteDriverES1_NS3_7NoCacheEEEE12CLocalEntityIS1_E8GetQueryEiE7queries_02cbfab0
               + (long)param_2 * 0x20, puVar1 != (undefined *)0x0)) {
    uVar4 = (**(code **)(*(long *)(*(long *)puVar2 + 0x40) + 0x28))
                      ((long *)(*(long *)puVar2 + 0x40),0,0);
    Aska::Yayoi::SQLiteDriver::DoOpen(Aska::Yayoi::Entity::Mode, char const*, Aska::Yayoi::DBAddress const*)(&lStack_48,uVar3,0,0,uVar4);
    if ((-1 < lStack_48) && (lVar5 = char const* Aska::Yayoi::SQLiteDriver::BuildQuery<CSimpleSqliteConnector<MasterDB::CText, Aska::Yayoi::TEntity_Slave<Aska::Yayoi::SQLiteDriver, MasterDB::CText, Aska::Yayoi::NoCache> >::CLocalEntity<MasterDB::CText> >(Aska::Yayoi::QueryObject const*, CSimpleSqliteConnector<MasterDB::CText, Aska::Yayoi::TEntity_Slave<Aska::Yayoi::SQLiteDriver, MasterDB::CText, Aska::Yayoi::NoCache> >::CLocalEntity<MasterDB::CText> const*, char const*)(uVar3,puVar1,param_1 + 0x10,0), lVar5 != 0)) {
      Aska::Yayoi::SQLiteDriver::Find(char const*, Aska::Yayoi::QueryParam const*, unsigned long, Aska::Yayoi::SQLiteDriver::EntityObject*)(&lStack_48,uVar3,lVar5,param_3,param_4,param_5);
    }
  }
  return;
}

// ==== CSimpleSqliteConnector<MasterDB::CText, Aska::Yayoi::TEntity_Slave<Aska::Yayoi::SQLiteDriver, MasterDB::CText, Aska::Yayoi::NoCache> >::QueryToMsgPack(unsigned int, unsigned int, Aska::TSharedArray<signed char>&, long&)
// vaddr 0x16fe344 | ghidra 0x17fe344 | size 536 | symbol _ZN22CSimpleSqliteConnectorIN8MasterDB5CTextEN4Aska5Yayoi13TEntity_SlaveINS3_12SQLiteDriverES1_NS3_7NoCacheEEEE14QueryToMsgPackEjjRNS2_12TSharedArrayIaEERl | lib libSOA-3.7.0.so | 2026-10-08
void _ZN22CSimpleSqliteConnectorIN8MasterDB5CTextEN4Aska5Yayoi13TEntity_SlaveINS3_12SQLiteDriverES1_NS3_7NoCacheEEEE14QueryToMsgPackEjjRNS2_12TSharedArrayIaEERl
               (long *param_1,int param_2,undefined4 param_3,long *param_4,undefined8 param_5)

{
  int iVar1;
  char cVar2;
  bool bVar3;
  long lVar4;
  long lVar5;
  int *piVar6;
  undefined4 uVar7;
  long lStack_108;
  int *piStack_100;
  undefined8 uStack_f8;
  undefined8 uStack_f0;
  long *plStack_e8;
  undefined8 uStack_e0;
  undefined4 uStack_d8;
  undefined1 uStack_d4;
  undefined1 auStack_d0 [96];
  undefined1 auStack_70 [24];
  undefined1 uStack_58;
  
  lVar4 = *(long *)PTR__ZN9Framework10TSingletonI18CStaticTransactionE11m_pInstanceE_02cc41b0;
  CSqliteTransaction::rMutex()(lVar4 + 0x40);
  Framework::CMutex::Lock()();
  Aska::Yayoi::SQLiteDriver::EntityObject::EntityObject()(auStack_d0);
  Aska::Yayoi::EntityCache::EntityCache()(auStack_70);
  uStack_58 = 0;
  if (param_2 == 1) {
    snprintf(param_1 + 3,0x100,&UNK_027e6d32/*"%u"*/,param_3);
    lVar5 = 0;
code_r0x017fe3fc:
    uVar7 = 1;
  }
  else {
    if (param_2 == 2) {
      snprintf(param_1 + 3,0x100,&UNK_027e6d32/*"%u"*/,param_3);
      lVar5 = 1;
      goto code_r0x017fe3fc;
    }
    lVar5 = 0;
    uVar7 = 0;
  }
  plStack_e8 = param_1 + 3;
  uStack_f8 = *(undefined8 *)
               (
               PTR__ZZNK22CSimpleSqliteConnectorIN8MasterDB5CTextEN4Aska5Yayoi13TEntity_SlaveINS3_12SQLiteDriverES1_NS3_7NoCacheEEEE12CLocalEntityIS1_E15GetPrimaryKeiesEvE5keies_02cc3e00
               + lVar5 * 0x10);
  uStack_f0 = 7;
  uStack_e0 = strlen(plStack_e8);
  uStack_d8 = 0;
  uStack_d4 = 0;
  (**(code **)(*param_1 + 0x20))(param_1,param_2,&uStack_f8,uVar7,auStack_d0);
  Aska::Yayoi::SQLiteDriver::EntityObject::Serialize(long*)(&lStack_108,auStack_d0,param_5);
  lVar5 = *param_4;
  if (lStack_108 != lVar5) {
    piVar6 = (int *)param_4[1];
    if (piVar6 == (int *)0x0) {
code_r0x017fe4a4:
      if (lVar5 != 0) {
        operator delete[](void*)();
      }
      if (param_4[1] != 0) {
        Aska::TSharedPointerCode::DeleteCounter(int*)();
      }
    }
    else {
      do {
        iVar1 = *piVar6;
        cVar2 = '\x01';
        bVar3 = (bool)ExclusiveMonitorPass(piVar6,0x10);
        if (bVar3) {
          *piVar6 = iVar1 + -1;
          cVar2 = ExclusiveMonitorsStatus();
        }
      } while (cVar2 != '\0');
      if (iVar1 + -1 == 0) {
        lVar5 = *param_4;
        goto code_r0x017fe4a4;
      }
    }
    *param_4 = lStack_108;
    param_4[1] = (long)piStack_100;
    if (piStack_100 != (int *)0x0) {
      do {
        cVar2 = '\x01';
        bVar3 = (bool)ExclusiveMonitorPass(piStack_100,0x10);
        if (bVar3) {
          *piStack_100 = *piStack_100 + 1;
          cVar2 = ExclusiveMonitorsStatus();
        }
      } while (cVar2 != '\0');
    }
  }
  if (piStack_100 != (int *)0x0) {
    do {
      iVar1 = *piStack_100;
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piStack_100,0x10);
      if (bVar3) {
        *piStack_100 = iVar1 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    if (iVar1 + -1 != 0) goto code_r0x017fe520;
  }
  if (lStack_108 != 0) {
    operator delete[](void*)();
  }
  if (piStack_100 != (int *)0x0) {
    Aska::TSharedPointerCode::DeleteCounter(int*)();
  }
code_r0x017fe520:
  piStack_100 = (int *)0x0;
  Aska::Yayoi::EntityCache::~EntityCache()(auStack_70);
  Aska::Yayoi::SQLiteDriver::EntityObject::~EntityObject()(auStack_d0);
  CSqliteTransaction::rMutex()(lVar4 + 0x40);
  Framework::CMutex::Unlock()();
  return;
}

// ==== CSimpleSqliteConnector<MasterDB::CText, Aska::Yayoi::TEntity_Slave<Aska::Yayoi::SQLiteDriver, MasterDB::CText, Aska::Yayoi::NoCache> >::QueryToMsgPack(char const*, Aska::TSharedArray<signed char>&, long&, Aska::Yayoi::QueryParam*, unsigned int)
// vaddr 0x16fe55c | ghidra 0x17fe55c | size 388 | symbol _ZN22CSimpleSqliteConnectorIN8MasterDB5CTextEN4Aska5Yayoi13TEntity_SlaveINS3_12SQLiteDriverES1_NS3_7NoCacheEEEE14QueryToMsgPackEPKcRNS2_12TSharedArrayIaEERlPNS3_10QueryParamEj | lib libSOA-3.7.0.so | 2026-10-08
void _ZN22CSimpleSqliteConnectorIN8MasterDB5CTextEN4Aska5Yayoi13TEntity_SlaveINS3_12SQLiteDriverES1_NS3_7NoCacheEEEE14QueryToMsgPackEPKcRNS2_12TSharedArrayIaEERlPNS3_10QueryParamEj
               (long *param_1,undefined8 param_2,long *param_3,undefined8 param_4,undefined8 param_5
               ,undefined4 param_6)

{
  int iVar1;
  char cVar2;
  bool bVar3;
  long lVar4;
  long lVar5;
  int *piVar6;
  long lStack_e0;
  int *piStack_d8;
  undefined1 auStack_d0 [96];
  undefined1 auStack_70 [24];
  undefined1 uStack_58;
  
  lVar5 = *(long *)PTR__ZN9Framework10TSingletonI18CStaticTransactionE11m_pInstanceE_02cc41b0;
  CSqliteTransaction::rMutex()(lVar5 + 0x40);
  Framework::CMutex::Lock()();
  Aska::Yayoi::SQLiteDriver::EntityObject::EntityObject()(auStack_d0);
  Aska::Yayoi::EntityCache::EntityCache()(auStack_70);
  uStack_58 = 0;
  (**(code **)(*param_1 + 0x38))(param_1,param_2,param_5,param_6,auStack_d0);
  Aska::Yayoi::SQLiteDriver::EntityObject::Serialize(long*)(&lStack_e0,auStack_d0,param_4);
  lVar4 = *param_3;
  if (lStack_e0 != lVar4) {
    piVar6 = (int *)param_3[1];
    if (piVar6 == (int *)0x0) {
code_r0x017fe628:
      if (lVar4 != 0) {
        operator delete[](void*)();
      }
      if (param_3[1] != 0) {
        Aska::TSharedPointerCode::DeleteCounter(int*)();
      }
    }
    else {
      do {
        iVar1 = *piVar6;
        cVar2 = '\x01';
        bVar3 = (bool)ExclusiveMonitorPass(piVar6,0x10);
        if (bVar3) {
          *piVar6 = iVar1 + -1;
          cVar2 = ExclusiveMonitorsStatus();
        }
      } while (cVar2 != '\0');
      if (iVar1 + -1 == 0) {
        lVar4 = *param_3;
        goto code_r0x017fe628;
      }
    }
    *param_3 = lStack_e0;
    param_3[1] = (long)piStack_d8;
    if (piStack_d8 != (int *)0x0) {
      do {
        cVar2 = '\x01';
        bVar3 = (bool)ExclusiveMonitorPass(piStack_d8,0x10);
        if (bVar3) {
          *piStack_d8 = *piStack_d8 + 1;
          cVar2 = ExclusiveMonitorsStatus();
        }
      } while (cVar2 != '\0');
    }
  }
  if (piStack_d8 != (int *)0x0) {
    do {
      iVar1 = *piStack_d8;
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piStack_d8,0x10);
      if (bVar3) {
        *piStack_d8 = iVar1 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    if (iVar1 + -1 != 0) goto code_r0x017fe6a4;
  }
  if (lStack_e0 != 0) {
    operator delete[](void*)();
  }
  if (piStack_d8 != (int *)0x0) {
    Aska::TSharedPointerCode::DeleteCounter(int*)();
  }
code_r0x017fe6a4:
  piStack_d8 = (int *)0x0;
  Aska::Yayoi::EntityCache::~EntityCache()(auStack_70);
  Aska::Yayoi::SQLiteDriver::EntityObject::~EntityObject()(auStack_d0);
  CSqliteTransaction::rMutex()(lVar5 + 0x40);
  Framework::CMutex::Unlock()();
  return;
}

// ==== CSimpleSqliteConnector<MasterDB::CText, Aska::Yayoi::TEntity_Slave<Aska::Yayoi::SQLiteDriver, MasterDB::CText, Aska::Yayoi::NoCache> >::QueryToResultObject(char const*, Aska::Yayoi::QueryParam*, unsigned int, Aska::Yayoi::TEntityObject<Aska::Yayoi::SQLiteDriver>&)
// vaddr 0x16fe6e0 | ghidra 0x17fe6e0 | size 92 | symbol _ZN22CSimpleSqliteConnectorIN8MasterDB5CTextEN4Aska5Yayoi13TEntity_SlaveINS3_12SQLiteDriverES1_NS3_7NoCacheEEEE19QueryToResultObjectEPKcPNS3_10QueryParamEjRNS3_13TEntityObjectIS5_EE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN22CSimpleSqliteConnectorIN8MasterDB5CTextEN4Aska5Yayoi13TEntity_SlaveINS3_12SQLiteDriverES1_NS3_7NoCacheEEEE19QueryToResultObjectEPKcPNS3_10QueryParamEjRNS3_13TEntityObjectIS5_EE
               (undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined4 param_4,
               undefined8 param_5)

{
  undefined8 uVar1;
  undefined1 auStack_28 [8];
  
  uVar1 = (**(code **)(*(long *)(*(long *)
                                  PTR__ZN9Framework10TSingletonI18CStaticTransactionE11m_pInstanceE_02cc41b0
                                + 0x40) + 0x20))();
  Aska::Yayoi::SQLiteDriver::Find(char const*, Aska::Yayoi::QueryParam const*, unsigned long, Aska::Yayoi::SQLiteDriver::EntityObject*)(auStack_28,uVar1,param_2,param_3,param_4,param_5);
  return;
}

// ==== CSimpleSqliteConnector<MasterDB::CText, Aska::Yayoi::TEntity_Slave<Aska::Yayoi::SQLiteDriver, MasterDB::CText, Aska::Yayoi::NoCache> >::CLocalEntity<MasterDB::CText>::GetQuery(int) const
// vaddr 0x16fe73c | ghidra 0x17fe73c | size 28 | symbol _ZNK22CSimpleSqliteConnectorIN8MasterDB5CTextEN4Aska5Yayoi13TEntity_SlaveINS3_12SQLiteDriverES1_NS3_7NoCacheEEEE12CLocalEntityIS1_E8GetQueryEi | lib libSOA-3.7.0.so | 2026-10-08
undefined *
_ZNK22CSimpleSqliteConnectorIN8MasterDB5CTextEN4Aska5Yayoi13TEntity_SlaveINS3_12SQLiteDriverES1_NS3_7NoCacheEEEE12CLocalEntityIS1_E8GetQueryEi
          (undefined8 param_1,int param_2)

{
  undefined *puVar1;
  
  puVar1 = (undefined *)0x0;
  if (param_2 < 3) {
    puVar1 = PTR__ZZNK22CSimpleSqliteConnectorIN8MasterDB5CTextEN4Aska5Yayoi13TEntity_SlaveINS3_12SQLiteDriverES1_NS3_7NoCacheEEEE12CLocalEntityIS1_E8GetQueryEiE7queries_02cbfab0
             + (long)param_2 * 0x20;
  }
  return puVar1;
}

// ==== char const* Aska::Yayoi::SQLiteDriver::BuildQuery<CSimpleSqliteConnector<MasterDB::CText, Aska::Yayoi::TEntity_Slave<Aska::Yayoi::SQLiteDriver, MasterDB::CText, Aska::Yayoi::NoCache> >::CLocalEntity<MasterDB::CText> >(Aska::Yayoi::QueryObject const*, CSimpleSqliteConnector<MasterDB::CText, Aska::Yayoi::TEntity_Slave<Aska::Yayoi::SQLiteDriver, MasterDB::CText, Aska::Yayoi::NoCache> >::CLocalEntity<MasterDB::CText> const*, char const*)
// vaddr 0x16fe758 | ghidra 0x17fe758 | size 360 | symbol _ZN4Aska5Yayoi12SQLiteDriver10BuildQueryIN22CSimpleSqliteConnectorIN8MasterDB5CTextENS0_13TEntity_SlaveIS1_S5_NS0_7NoCacheEEEE12CLocalEntityIS5_EEEEPKcPKNS0_11QueryObjectEPKT_SD_ | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska5Yayoi12SQLiteDriver10BuildQueryIN22CSimpleSqliteConnectorIN8MasterDB5CTextENS0_13TEntity_SlaveIS1_S5_NS0_7NoCacheEEEE12CLocalEntityIS5_EEEEPKcPKNS0_11QueryObjectEPKT_SD_
          (long param_1,long *param_2,undefined8 param_3,long param_4)

{
  ulong uVar1;
  long lVar2;
  undefined *puVar3;
  long lVar4;
  long lVar5;
  long lVar6;
  undefined8 uVar7;
  long lVar8;
  undefined auStack_6c [12];
  
  if (*(long **)(param_1 + 0x48) != param_2) {
    *(undefined1 *)(param_1 + 0x60) = 0;
    lVar4 = *param_2;
    lVar5 = param_2[1];
    lVar8 = *(long *)(param_1 + 0x38);
    lVar2 = 0xb;
    puVar3 = &UNK_0285ebc6/*"master_text"*/;
    if (param_4 != 0) {
      lVar2 = 0;
      puVar3 = auStack_6c;
    }
    uVar1 = lVar2 + lVar5 + 1;
    lVar6 = lVar8;
    if (*(ulong *)(param_1 + 0x40) < uVar1) {
      lVar6 = **(long **)PTR__ZN4Aska6Global19m_pNetworkAllocatorE_02cbc200;
      if (lVar6 == 0) {
        lVar6 = Aska::Global::GetAvailableMemoryManager()();
      }
      lVar6 = Aska::MemoryManager::Realloc(unsigned long, void*, long)(lVar6,uVar1,lVar8,4);
      *(long *)(param_1 + 0x38) = lVar6;
      if (lVar6 == 0) {
        uVar7 = Aska::Global::GetAvailableMemoryManager()();
        lVar6 = Aska::MemoryManager::Realloc(unsigned long, void*, long)(uVar7,uVar1,lVar8,4);
        *(long *)(param_1 + 0x38) = lVar6;
      }
      *(ulong *)(param_1 + 0x40) = uVar1;
    }
    if (lVar6 == 0) {
      return 0;
    }
    lVar8 = strstr(lVar4,&UNK_02845da0/*"__TABLE_NAME__"*/);
    while (lVar8 != 0) {
      memcpy(lVar6,lVar4,lVar8 - lVar4);
      lVar6 = lVar6 + (lVar8 - lVar4);
      memcpy(lVar6,puVar3,lVar2);
      lVar6 = lVar6 + lVar2;
      lVar4 = lVar8 + 0xe;
      lVar8 = strstr(lVar4,&UNK_02845da0/*"__TABLE_NAME__"*/);
    }
    memcpy(lVar6,lVar4,((lVar5 + 1) - lVar4) + *param_2);
  }
  return *(undefined8 *)(param_1 + 0x38);
}


// FAILED to create function at 0285ece0 typeinfo name for CSimpleSqliteConnector<MasterDB::CText, Aska::Yayoi::TEntity_Slave<Aska::Yayoi::SQLiteDriver, MasterDB::CText, Aska::Yayoi::NoCache> >
// FAILED to create function at 0285ed50 typeinfo name for CSimpleSqliteConnector<MasterDB::CText, Aska::Yayoi::TEntity_Slave<Aska::Yayoi::SQLiteDriver, MasterDB::CText, Aska::Yayoi::NoCache> >::CLocalEntity<MasterDB::CText>
// FAILED to create function at 02b0bec0 CSimpleSqliteConnector<MasterDB::CText,Aska::Yayoi::TEntity_Slave<Aska::Yayoi::SQLiteDriver,MasterDB::CText,Aska::Yayoi::NoCache>>::vtable
// FAILED to create function at 02b0bf10 CSimpleSqliteConnector<MasterDB::CText,Aska::Yayoi::TEntity_Slave<Aska::Yayoi::SQLiteDriver,MasterDB::CText,Aska::Yayoi::NoCache>>::typeinfo
// FAILED to create function at 02b0bf28 CSimpleSqliteConnector<MasterDB::CText,Aska::Yayoi::TEntity_Slave<Aska::Yayoi::SQLiteDriver,MasterDB::CText,Aska::Yayoi::NoCache>>::CLocalEntity<MasterDB::CText>::vtable
// FAILED to create function at 02b0bf40 CSimpleSqliteConnector<MasterDB::CText,Aska::Yayoi::TEntity_Slave<Aska::Yayoi::SQLiteDriver,MasterDB::CText,Aska::Yayoi::NoCache>>::CLocalEntity<MasterDB::CText>::typeinfo
// FAILED to create function at 02b0bf50 CSimpleSqliteConnector<MasterDB::CText,Aska::Yayoi::TEntity_Slave<Aska::Yayoi::SQLiteDriver,MasterDB::CText,Aska::Yayoi::NoCache>>::CLocalEntity<MasterDB::CText>::GetQuery(int)::queries
// FAILED to create function at 02b0bfb0 CSimpleSqliteConnector<MasterDB::CText,Aska::Yayoi::TEntity_Slave<Aska::Yayoi::SQLiteDriver,MasterDB::CText,Aska::Yayoi::NoCache>>::CLocalEntity<MasterDB::CText>::GetPrimaryKeies()::keies
