// lobby_messages: Ghidra decompiles of work/libSOA-3.7.0.so (3.7.0), extracted by extract.py.
// Data, not code: see README.md and docs/multiplayer.md for what they show.

// ==== undefined Aska::Yayoi::MultiplayRPC::LobbyProtocoledData::GetFID(void)
// _ZNK4Aska5Yayoi12MultiplayRPC19LobbyProtocoledData6GetFIDEv @ 022f9048

undefined4 _ZNK4Aska5Yayoi12MultiplayRPC19LobbyProtocoledData6GetFIDEv(long param_1)

{
  if (*(long *)(param_1 + 0x40) != 0) {
    return *(undefined4 *)(param_1 + 0x30);
  }
  return 0x7b1a9377;
}

// ==== undefined Aska::Yayoi::MultiplayRPC::LobbyProtocoledData::GetProtocolError(Aska::Yayoi::MultiplayRPC::LobbyProtocol::FunctionID &,Aska::Status &)
// _ZN4Aska5Yayoi12MultiplayRPC19LobbyProtocoledData16GetProtocolErrorERNS1_13LobbyProtocol10FunctionIDERNS_6StatusE @ 022f9064

void _ZN4Aska5Yayoi12MultiplayRPC19LobbyProtocoledData16GetProtocolErrorERNS1_13LobbyProtocol10FunctionIDERNS_6StatusE
               (undefined8 *param_1,long param_2,undefined4 *param_3,undefined8 *param_4)

{
  undefined8 uVar1;
  long lVar2;
  
  lVar2 = *(long *)(param_2 + 0x40);
  *param_4 = *(undefined8 *)(lVar2 + 0x18);
  *param_3 = *(undefined4 *)(lVar2 + 0x20);
  uVar1 = 0xfffffffffffffc6b;
  if ((ulong)((lVar2 + 0x24) - *(long *)(param_2 + 0x40)) <= (ulong)*(uint *)(param_2 + 0x24)) {
    uVar1 = 0;
  }
  *param_1 = uVar1;
  return;
}

// ==== undefined Aska::Yayoi::MultiplayRPC::LobbyProtocoledData::GetEnterLobby(Aska::Yayoi::MultiplayRPC::PlayerInfo * &)
// _ZN4Aska5Yayoi12MultiplayRPC19LobbyProtocoledData13GetEnterLobbyERPNS1_10PlayerInfoE @ 022f93b8

void _ZN4Aska5Yayoi12MultiplayRPC19LobbyProtocoledData13GetEnterLobbyERPNS1_10PlayerInfoE
               (undefined8 *param_1,long param_2,long *param_3)

{
  undefined8 uVar1;
  long lVar2;
  
  lVar2 = *(long *)(param_2 + 0x40);
  *param_3 = lVar2 + 0x18;
  uVar1 = 0xfffffffffffffc6b;
  if ((ulong)((lVar2 + 0x88) - *(long *)(param_2 + 0x40)) <= (ulong)*(uint *)(param_2 + 0x24)) {
    uVar1 = 0;
  }
  *param_1 = uVar1;
  return;
}

// ==== undefined Aska::Yayoi::MultiplayRPC::LobbyProtocoledData::GetEnterLobbyResult(Aska::Status &)
// _ZN4Aska5Yayoi12MultiplayRPC19LobbyProtocoledData19GetEnterLobbyResultERNS_6StatusE @ 022f93e8

void _ZN4Aska5Yayoi12MultiplayRPC19LobbyProtocoledData19GetEnterLobbyResultERNS_6StatusE
               (undefined8 *param_1,long param_2,undefined8 *param_3)

{
  undefined8 uVar1;
  long lVar2;
  
  lVar2 = *(long *)(param_2 + 0x40);
  *param_3 = *(undefined8 *)(lVar2 + 0x18);
  uVar1 = 0xfffffffffffffc6b;
  if ((ulong)((lVar2 + 0x20) - *(long *)(param_2 + 0x40)) <= (ulong)*(uint *)(param_2 + 0x24)) {
    uVar1 = 0;
  }
  *param_1 = uVar1;
  return;
}

// ==== undefined Aska::Yayoi::MultiplayRPC::LobbyProtocoledData::GetCreateRoom(Aska::Yayoi::MultiplayRPC::PlayerInfo * &,Aska::Yayoi::MultiplayRPC::RoomCondition * &)
// _ZN4Aska5Yayoi12MultiplayRPC19LobbyProtocoledData13GetCreateRoomERPNS1_10PlayerInfoERPNS1_13RoomConditionE @ 022f9438

void _ZN4Aska5Yayoi12MultiplayRPC19LobbyProtocoledData13GetCreateRoomERPNS1_10PlayerInfoERPNS1_13RoomConditionE
               (undefined8 *param_1,long param_2,long *param_3,long *param_4)

{
  undefined8 uVar1;
  long lVar2;
  
  lVar2 = *(long *)(param_2 + 0x40);
  *param_3 = lVar2 + 0x18;
  *param_4 = lVar2 + 0x88;
  uVar1 = 0xfffffffffffffc6b;
  if ((ulong)((lVar2 + 0x270) - *(long *)(param_2 + 0x40)) <= (ulong)*(uint *)(param_2 + 0x24)) {
    uVar1 = 0;
  }
  *param_1 = uVar1;
  return;
}

// ==== undefined Aska::Yayoi::MultiplayRPC::LobbyProtocoledData::GetCreateRoomResult(Aska::Yayoi::MultiplayRPC::RoomInfo * &)
// _ZN4Aska5Yayoi12MultiplayRPC19LobbyProtocoledData19GetCreateRoomResultERPNS1_8RoomInfoE @ 022f9470

void _ZN4Aska5Yayoi12MultiplayRPC19LobbyProtocoledData19GetCreateRoomResultERPNS1_8RoomInfoE
               (undefined8 *param_1,long param_2,long *param_3)

{
  undefined8 uVar1;
  long lVar2;
  
  lVar2 = *(long *)(param_2 + 0x40);
  *param_3 = lVar2 + 0x18;
  uVar1 = 0xfffffffffffffc6b;
  if ((ulong)((lVar2 + 0x468) - *(long *)(param_2 + 0x40)) <= (ulong)*(uint *)(param_2 + 0x24)) {
    uVar1 = 0;
  }
  *param_1 = uVar1;
  return;
}

// ==== undefined Aska::Yayoi::MultiplayRPC::LobbyProtocoledData::GetCloseRoom(int &,unsigned int &)
// _ZN4Aska5Yayoi12MultiplayRPC19LobbyProtocoledData12GetCloseRoomERiRj @ 022f94a0

void _ZN4Aska5Yayoi12MultiplayRPC19LobbyProtocoledData12GetCloseRoomERiRj
               (undefined8 *param_1,long param_2,undefined4 *param_3,undefined4 *param_4)

{
  undefined8 uVar1;
  long lVar2;
  
  lVar2 = *(long *)(param_2 + 0x40);
  *param_3 = *(undefined4 *)(lVar2 + 0x18);
  *param_4 = *(undefined4 *)(lVar2 + 0x1c);
  uVar1 = 0xfffffffffffffc6b;
  if ((ulong)((lVar2 + 0x20) - *(long *)(param_2 + 0x40)) <= (ulong)*(uint *)(param_2 + 0x24)) {
    uVar1 = 0;
  }
  *param_1 = uVar1;
  return;
}

// ==== undefined Aska::Yayoi::MultiplayRPC::LobbyProtocoledData::GetCloseRoomResult(Aska::Status &)
// _ZN4Aska5Yayoi12MultiplayRPC19LobbyProtocoledData18GetCloseRoomResultERNS_6StatusE @ 022f94d8

void _ZN4Aska5Yayoi12MultiplayRPC19LobbyProtocoledData18GetCloseRoomResultERNS_6StatusE
               (undefined8 *param_1,long param_2,undefined8 *param_3)

{
  undefined8 uVar1;
  long lVar2;
  
  lVar2 = *(long *)(param_2 + 0x40);
  *param_3 = *(undefined8 *)(lVar2 + 0x18);
  uVar1 = 0xfffffffffffffc6b;
  if ((ulong)((lVar2 + 0x20) - *(long *)(param_2 + 0x40)) <= (ulong)*(uint *)(param_2 + 0x24)) {
    uVar1 = 0;
  }
  *param_1 = uVar1;
  return;
}

// ==== undefined Aska::Yayoi::MultiplayRPC::LobbyProtocoledData::GetGetRoomList(Aska::Yayoi::MultiplayRPC::PlayerInfo * &,Aska::Yayoi::MultiplayRPC::RoomCondition * &,int &,int &)
// _ZN4Aska5Yayoi12MultiplayRPC19LobbyProtocoledData14GetGetRoomListERPNS1_10PlayerInfoERPNS1_13RoomConditionERiS9_ @ 022f9528

void _ZN4Aska5Yayoi12MultiplayRPC19LobbyProtocoledData14GetGetRoomListERPNS1_10PlayerInfoERPNS1_13RoomConditionERiS9_
               (undefined8 *param_1,long param_2,long *param_3,long *param_4,uint *param_5,
               uint *param_6)

{
  undefined8 uVar1;
  uint uVar2;
  uint uVar3;
  long lVar4;
  
  lVar4 = *(long *)(param_2 + 0x40);
  *param_3 = lVar4 + 0x18;
  *param_4 = lVar4 + 0x88;
  *param_5 = *(uint *)(lVar4 + 0x270);
  uVar2 = *(uint *)(lVar4 + 0x274);
  *param_6 = uVar2;
  if ((ulong)*(uint *)(param_2 + 0x24) < (ulong)((lVar4 + 0x278) - *(long *)(param_2 + 0x40))) {
    *param_1 = 0xfffffffffffffc6b;
    return;
  }
  uVar3 = *param_5;
  uVar1 = 0;
  if ((0x7fffffff < (uVar3 | uVar2) || uVar2 == uVar3) ||
      -1 < (int)(uVar3 | uVar2) && (int)uVar2 < (int)uVar3) {
    uVar1 = 0xfffffffffffffc43;
  }
  *param_1 = uVar1;
  return;
}

// ==== undefined Aska::Yayoi::MultiplayRPC::LobbyProtocoledData::GetGetRoomListResult(Aska::Yayoi::MultiplayRPC::RoomInfo * &,unsigned int &,int &,int &)
// _ZN4Aska5Yayoi12MultiplayRPC19LobbyProtocoledData20GetGetRoomListResultERPNS1_8RoomInfoERjRiS7_ @ 022f9590

void _ZN4Aska5Yayoi12MultiplayRPC19LobbyProtocoledData20GetGetRoomListResultERPNS1_8RoomInfoERjRiS7_
               (undefined8 *param_1,long param_2,long *param_3,uint *param_4,undefined4 *param_5,
               undefined4 *param_6)

{
  undefined4 *puVar1;
  undefined8 uVar2;
  long lVar3;
  uint *puVar4;
  
  lVar3 = *(long *)(param_2 + 0x40);
  puVar4 = (uint *)(lVar3 + 0x18);
  *param_4 = *puVar4;
  *param_3 = lVar3 + 0x1c;
  puVar1 = (undefined4 *)((long)puVar4 + ((ulong)*param_4 * 0x450 | 4));
  *param_5 = *puVar1;
  *param_6 = puVar1[1];
  uVar2 = 0xfffffffffffffc6b;
  if ((ulong)((long)puVar1 + (8 - *(long *)(param_2 + 0x40))) <= (ulong)*(uint *)(param_2 + 0x24)) {
    uVar2 = 0;
  }
  *param_1 = uVar2;
  return;
}

// ==== undefined Aska::Yayoi::MultiplayRPC::LobbyProtocoledData::GetUpdateRoomInfo(Aska::Yayoi::MultiplayRPC::RoomInfo * &)
// _ZN4Aska5Yayoi12MultiplayRPC19LobbyProtocoledData17GetUpdateRoomInfoERPNS1_8RoomInfoE @ 022f95ec

void _ZN4Aska5Yayoi12MultiplayRPC19LobbyProtocoledData17GetUpdateRoomInfoERPNS1_8RoomInfoE
               (undefined8 *param_1,long param_2,long *param_3)

{
  undefined8 uVar1;
  long lVar2;
  
  lVar2 = *(long *)(param_2 + 0x40);
  *param_3 = lVar2 + 0x18;
  uVar1 = 0xfffffffffffffc6b;
  if ((ulong)((lVar2 + 0x468) - *(long *)(param_2 + 0x40)) <= (ulong)*(uint *)(param_2 + 0x24)) {
    uVar1 = 0;
  }
  *param_1 = uVar1;
  return;
}

// ==== undefined Aska::Yayoi::MultiplayRPC::LobbyProtocoledData::GetUpdateRoomInfoResult(Aska::Yayoi::MultiplayRPC::RoomInfo * &)
// _ZN4Aska5Yayoi12MultiplayRPC19LobbyProtocoledData23GetUpdateRoomInfoResultERPNS1_8RoomInfoE @ 022f961c

void _ZN4Aska5Yayoi12MultiplayRPC19LobbyProtocoledData23GetUpdateRoomInfoResultERPNS1_8RoomInfoE
               (undefined8 *param_1,long param_2,long *param_3)

{
  undefined8 uVar1;
  long lVar2;
  
  lVar2 = *(long *)(param_2 + 0x40);
  *param_3 = lVar2 + 0x18;
  uVar1 = 0xfffffffffffffc6b;
  if ((ulong)((lVar2 + 0x468) - *(long *)(param_2 + 0x40)) <= (ulong)*(uint *)(param_2 + 0x24)) {
    uVar1 = 0;
  }
  *param_1 = uVar1;
  return;
}

// ==== undefined Aska::Yayoi::MultiplayRPC::LobbyProtocoledData::GetAutomatch(Aska::Yayoi::MultiplayRPC::PlayerInfo * &,Aska::Yayoi::MultiplayRPC::RoomCondition * &)
// _ZN4Aska5Yayoi12MultiplayRPC19LobbyProtocoledData12GetAutomatchERPNS1_10PlayerInfoERPNS1_13RoomConditionE @ 022f964c

void _ZN4Aska5Yayoi12MultiplayRPC19LobbyProtocoledData12GetAutomatchERPNS1_10PlayerInfoERPNS1_13RoomConditionE
               (undefined8 *param_1,long param_2,long *param_3,long *param_4)

{
  undefined8 uVar1;
  long lVar2;
  
  lVar2 = *(long *)(param_2 + 0x40);
  *param_3 = lVar2 + 0x18;
  *param_4 = lVar2 + 0x88;
  uVar1 = 0xfffffffffffffc6b;
  if ((ulong)((lVar2 + 0x270) - *(long *)(param_2 + 0x40)) <= (ulong)*(uint *)(param_2 + 0x24)) {
    uVar1 = 0;
  }
  *param_1 = uVar1;
  return;
}

// ==== undefined Aska::Yayoi::MultiplayRPC::LobbyProtocoledData::GetAutomatchResult(Aska::Status &,Aska::Yayoi::MultiplayRPC::RoomInfo * &,int &)
// _ZN4Aska5Yayoi12MultiplayRPC19LobbyProtocoledData18GetAutomatchResultERNS_6StatusERPNS1_8RoomInfoERi @ 022f9684

void _ZN4Aska5Yayoi12MultiplayRPC19LobbyProtocoledData18GetAutomatchResultERNS_6StatusERPNS1_8RoomInfoERi
               (undefined8 *param_1,long param_2,undefined8 *param_3,long *param_4,
               undefined4 *param_5)

{
  undefined8 uVar1;
  long lVar2;
  
  lVar2 = *(long *)(param_2 + 0x40);
  *param_3 = *(undefined8 *)(lVar2 + 0x18);
  *param_4 = lVar2 + 0x20;
  *param_5 = *(undefined4 *)(lVar2 + 0x470);
  uVar1 = 0xfffffffffffffc6b;
  if ((ulong)((lVar2 + 0x474) - *(long *)(param_2 + 0x40)) <= (ulong)*(uint *)(param_2 + 0x24)) {
    uVar1 = 0;
  }
  *param_1 = uVar1;
  return;
}

// ==== undefined Aska::Yayoi::MultiplayRPC::LobbyProtocoledData::SetEnterLobby(Aska::Yayoi::MultiplayRPC::PlayerInfo const &)
// _ZN4Aska5Yayoi12MultiplayRPC19LobbyProtocoledData13SetEnterLobbyERKNS1_10PlayerInfoE @ 022f96e4

void _ZN4Aska5Yayoi12MultiplayRPC19LobbyProtocoledData13SetEnterLobbyERKNS1_10PlayerInfoE
               (undefined8 *param_1,long param_2,undefined8 param_3)

{
  bool bVar1;
  byte bVar2;
  long lVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  undefined8 *puVar7;
  undefined8 uVar8;
  ulong uVar9;
  byte bVar10;
  byte bVar11;
  byte bVar12;
  byte bVar13;
  byte bVar14;
  byte bVar15;
  undefined8 uStack_60;
  ulong uStack_58;
  long lStack_50;
  long lStack_40;
  long lStack_38;
  
  if (*(long *)(param_2 + 0x40) == 0) {
    lVar3 = **(long **)PTR__ZN4Aska6Global19m_pNetworkAllocatorE_02cbc200;
    if (lVar3 == 0) {
      lVar3 = Aska::Global::GetAvailableMemoryManager()();
    }
    lVar3 = Aska::MemoryManager::Malloc(unsigned long)(lVar3,0x88);
    *(long *)(param_2 + 0x40) = lVar3;
joined_r0x022f98a4:
    if (lVar3 == 0) {
      *(undefined4 *)(param_2 + 0x20) = 0;
      uVar8 = 0xfffffffffffffc41;
      goto code_r0x022f98b0;
    }
    *(undefined4 *)(param_2 + 0x20) = 0x88;
  }
  else if (*(uint *)(param_2 + 0x20) < 0x88) {
    operator delete[](void*)();
    lVar3 = **(long **)PTR__ZN4Aska6Global19m_pNetworkAllocatorE_02cbc200;
    if (lVar3 == 0) {
      lVar3 = Aska::Global::GetAvailableMemoryManager()();
    }
    lVar3 = Aska::MemoryManager::Malloc(unsigned long)(lVar3,0x88);
    *(long *)(param_2 + 0x40) = lVar3;
    goto joined_r0x022f98a4;
  }
  uStack_60 = 0xfb5d0d7300000088;
  *(undefined4 *)(param_2 + 0x30) = 0xfb5d0d73;
  *(undefined1 *)(param_2 + 0x38) = 0;
  uStack_58 = (ulong)*(uint *)(param_2 + 0x34);
  clock_gettime(1,&lStack_40);
  lStack_38 = lStack_38 + lStack_40 * 1000000000;
  iVar6 = 0xf;
  bVar2 = (byte)((ulong)lStack_38 >> 0x38);
  bVar10 = (byte)((ulong)lStack_38 >> 8);
  bVar11 = (byte)((ulong)lStack_38 >> 0x10);
  bVar12 = (byte)((ulong)lStack_38 >> 0x18);
  bVar13 = (byte)((ulong)lStack_38 >> 0x20);
  bVar14 = (byte)((ulong)lStack_38 >> 0x28);
  bVar15 = (byte)((ulong)lStack_38 >> 0x30);
  uStack_58 = CONCAT17((byte)(uStack_58 >> 0x38) ^ bVar2,
                       CONCAT16((byte)(uStack_58 >> 0x30) ^ bVar15,
                                CONCAT15((byte)(uStack_58 >> 0x28) ^ bVar14,
                                         CONCAT14((byte)(uStack_58 >> 0x20) ^ bVar13,
                                                  CONCAT13((byte)(uStack_58 >> 0x18) ^ bVar12,
                                                           CONCAT12((byte)(uStack_58 >> 0x10) ^
                                                                    bVar11,CONCAT11((byte)(uStack_58
                                                                                          >> 8) ^
                                                                                    bVar10,(byte)
                                                  uStack_58 ^ (byte)lStack_38)))))));
  uStack_60 = CONCAT17((byte)((ulong)uStack_60 >> 0x38) ^ bVar2,
                       CONCAT16((byte)((ulong)uStack_60 >> 0x30) ^ bVar15,
                                CONCAT15((byte)((ulong)uStack_60 >> 0x28) ^ bVar14,
                                         CONCAT14((byte)((ulong)uStack_60 >> 0x20) ^ bVar13,
                                                  CONCAT13((byte)((ulong)uStack_60 >> 0x18) ^ bVar12
                                                           ,CONCAT12((byte)((ulong)uStack_60 >> 0x10
                                                                           ) ^ bVar11,
                                                                     CONCAT11((byte)((ulong)
                                                  uStack_60 >> 8) ^ bVar10,
                                                  (byte)uStack_60 ^ (byte)lStack_38)))))));
  uVar9 = 0x17;
  lStack_50 = lStack_38;
  do {
    uVar4 = (uint)((ulong)lStack_38 >> 0x20);
    uVar5 = (uint)bVar2;
    switch(uVar9 & 0xffffffff) {
    case 0:
      uVar5 = (uint)(ushort)((ulong)lStack_38 >> 0x30);
      break;
    case 1:
      uVar5 = uVar4;
      break;
    case 2:
      uVar5 = (uint)((ulong)lStack_38 >> 0x18);
      break;
    case 3:
      uVar5 = (uint)lStack_38;
      break;
    case 4:
      break;
    case 5:
      uVar5 = (uint)((ulong)lStack_38 >> 8);
      break;
    case 6:
      uVar5 = (uint)((ulong)lStack_38 >> 0x10);
      break;
    case 7:
      uVar5 = uVar4 >> 8;
      break;
    default:
      lVar3 = (long)iVar6;
      iVar6 = iVar6 + -1;
      uVar5 = (uint)*(byte *)((long)&uStack_60 + lVar3);
    }
    *(char *)((long)&uStack_60 + uVar9) = (char)uVar5;
    bVar1 = 0 < (long)uVar9;
    uVar9 = uVar9 - 1;
  } while (bVar1);
  puVar7 = *(undefined8 **)(param_2 + 0x40);
  puVar7[2] = lStack_50;
  puVar7[1] = uStack_58;
  *puVar7 = uStack_60;
  memcpy(*(long *)(param_2 + 0x40) + 0x18,param_3,0x70);
  uVar8 = 0;
  *(undefined4 *)(param_2 + 0x24) = 0x88;
code_r0x022f98b0:
  *param_1 = uVar8;
  return;
}

// ==== undefined Aska::Yayoi::MultiplayRPC::LobbyProtocoledData::SetCreateRoom(Aska::Yayoi::MultiplayRPC::PlayerInfo const &,Aska::Yayoi::MultiplayRPC::RoomCondition const &)
// _ZN4Aska5Yayoi12MultiplayRPC19LobbyProtocoledData13SetCreateRoomERKNS1_10PlayerInfoERKNS1_13RoomConditionE @ 022f9aa4

void _ZN4Aska5Yayoi12MultiplayRPC19LobbyProtocoledData13SetCreateRoomERKNS1_10PlayerInfoERKNS1_13RoomConditionE
               (undefined8 *param_1,long param_2,undefined8 param_3,undefined8 param_4)

{
  bool bVar1;
  byte bVar2;
  long lVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  undefined8 *puVar7;
  undefined8 uVar8;
  ulong uVar9;
  byte bVar10;
  byte bVar11;
  byte bVar12;
  byte bVar13;
  byte bVar14;
  byte bVar15;
  undefined8 uStack_60;
  ulong uStack_58;
  long lStack_50;
  long lStack_40;
  long lStack_38;
  
  if (*(long *)(param_2 + 0x40) == 0) {
    lVar3 = **(long **)PTR__ZN4Aska6Global19m_pNetworkAllocatorE_02cbc200;
    if (lVar3 == 0) {
      lVar3 = Aska::Global::GetAvailableMemoryManager()();
    }
    lVar3 = Aska::MemoryManager::Malloc(unsigned long)(lVar3,0x270);
    *(long *)(param_2 + 0x40) = lVar3;
joined_r0x022f9c78:
    if (lVar3 == 0) {
      *(undefined4 *)(param_2 + 0x20) = 0;
      uVar8 = 0xfffffffffffffc41;
      goto code_r0x022f9c84;
    }
    *(undefined4 *)(param_2 + 0x20) = 0x270;
  }
  else if (*(uint *)(param_2 + 0x20) < 0x270) {
    operator delete[](void*)();
    lVar3 = **(long **)PTR__ZN4Aska6Global19m_pNetworkAllocatorE_02cbc200;
    if (lVar3 == 0) {
      lVar3 = Aska::Global::GetAvailableMemoryManager()();
    }
    lVar3 = Aska::MemoryManager::Malloc(unsigned long)(lVar3,0x270);
    *(long *)(param_2 + 0x40) = lVar3;
    goto joined_r0x022f9c78;
  }
  uStack_60 = 0x6a1b49a500000270;
  *(undefined4 *)(param_2 + 0x30) = 0x6a1b49a5;
  *(undefined1 *)(param_2 + 0x38) = 0;
  uStack_58 = (ulong)*(uint *)(param_2 + 0x34);
  clock_gettime(1,&lStack_40);
  lStack_38 = lStack_38 + lStack_40 * 1000000000;
  iVar6 = 0xf;
  bVar2 = (byte)((ulong)lStack_38 >> 0x38);
  bVar10 = (byte)((ulong)lStack_38 >> 8);
  bVar11 = (byte)((ulong)lStack_38 >> 0x10);
  bVar12 = (byte)((ulong)lStack_38 >> 0x18);
  bVar13 = (byte)((ulong)lStack_38 >> 0x20);
  bVar14 = (byte)((ulong)lStack_38 >> 0x28);
  bVar15 = (byte)((ulong)lStack_38 >> 0x30);
  uStack_58 = CONCAT17((byte)(uStack_58 >> 0x38) ^ bVar2,
                       CONCAT16((byte)(uStack_58 >> 0x30) ^ bVar15,
                                CONCAT15((byte)(uStack_58 >> 0x28) ^ bVar14,
                                         CONCAT14((byte)(uStack_58 >> 0x20) ^ bVar13,
                                                  CONCAT13((byte)(uStack_58 >> 0x18) ^ bVar12,
                                                           CONCAT12((byte)(uStack_58 >> 0x10) ^
                                                                    bVar11,CONCAT11((byte)(uStack_58
                                                                                          >> 8) ^
                                                                                    bVar10,(byte)
                                                  uStack_58 ^ (byte)lStack_38)))))));
  uStack_60 = CONCAT17((byte)((ulong)uStack_60 >> 0x38) ^ bVar2,
                       CONCAT16((byte)((ulong)uStack_60 >> 0x30) ^ bVar15,
                                CONCAT15((byte)((ulong)uStack_60 >> 0x28) ^ bVar14,
                                         CONCAT14((byte)((ulong)uStack_60 >> 0x20) ^ bVar13,
                                                  CONCAT13((byte)((ulong)uStack_60 >> 0x18) ^ bVar12
                                                           ,CONCAT12((byte)((ulong)uStack_60 >> 0x10
                                                                           ) ^ bVar11,
                                                                     CONCAT11((byte)((ulong)
                                                  uStack_60 >> 8) ^ bVar10,
                                                  (byte)uStack_60 ^ (byte)lStack_38)))))));
  uVar9 = 0x17;
  lStack_50 = lStack_38;
  do {
    uVar4 = (uint)((ulong)lStack_38 >> 0x20);
    uVar5 = (uint)bVar2;
    switch(uVar9 & 0xffffffff) {
    case 0:
      uVar5 = (uint)(ushort)((ulong)lStack_38 >> 0x30);
      break;
    case 1:
      uVar5 = uVar4;
      break;
    case 2:
      uVar5 = (uint)((ulong)lStack_38 >> 0x18);
      break;
    case 3:
      uVar5 = (uint)lStack_38;
      break;
    case 4:
      break;
    case 5:
      uVar5 = (uint)((ulong)lStack_38 >> 8);
      break;
    case 6:
      uVar5 = (uint)((ulong)lStack_38 >> 0x10);
      break;
    case 7:
      uVar5 = uVar4 >> 8;
      break;
    default:
      lVar3 = (long)iVar6;
      iVar6 = iVar6 + -1;
      uVar5 = (uint)*(byte *)((long)&uStack_60 + lVar3);
    }
    *(char *)((long)&uStack_60 + uVar9) = (char)uVar5;
    bVar1 = 0 < (long)uVar9;
    uVar9 = uVar9 - 1;
  } while (bVar1);
  puVar7 = *(undefined8 **)(param_2 + 0x40);
  puVar7[2] = lStack_50;
  puVar7[1] = uStack_58;
  *puVar7 = uStack_60;
  lVar3 = *(long *)(param_2 + 0x40);
  memcpy(lVar3 + 0x18,param_3,0x70);
  memcpy(lVar3 + 0x88,param_4,0x1e8);
  uVar8 = 0;
  *(undefined4 *)(param_2 + 0x24) = 0x270;
code_r0x022f9c84:
  *param_1 = uVar8;
  return;
}

// ==== undefined Aska::Yayoi::MultiplayRPC::LobbyProtocoledData::SetCloseRoom(int,unsigned int)
// _ZN4Aska5Yayoi12MultiplayRPC19LobbyProtocoledData12SetCloseRoomEij @ 022f9e80

void _ZN4Aska5Yayoi12MultiplayRPC19LobbyProtocoledData12SetCloseRoomEij
               (undefined8 *param_1,long param_2,undefined4 param_3,undefined4 param_4)

{
  bool bVar1;
  byte bVar2;
  long lVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  undefined8 uVar7;
  ulong uVar8;
  undefined8 *puVar9;
  byte bVar10;
  byte bVar11;
  byte bVar12;
  byte bVar13;
  byte bVar14;
  byte bVar15;
  undefined8 uStack_60;
  ulong uStack_58;
  long lStack_50;
  long lStack_40;
  long lStack_38;
  
  if (*(long *)(param_2 + 0x40) == 0) {
    lVar3 = **(long **)PTR__ZN4Aska6Global19m_pNetworkAllocatorE_02cbc200;
    if (lVar3 == 0) {
      lVar3 = Aska::Global::GetAvailableMemoryManager()();
    }
    lVar3 = Aska::MemoryManager::Malloc(unsigned long)(lVar3,0x20);
    *(long *)(param_2 + 0x40) = lVar3;
joined_r0x022fa038:
    if (lVar3 == 0) {
      *(undefined4 *)(param_2 + 0x20) = 0;
      uVar7 = 0xfffffffffffffc41;
      goto code_r0x022fa044;
    }
    *(undefined4 *)(param_2 + 0x20) = 0x20;
  }
  else if (*(uint *)(param_2 + 0x20) < 0x20) {
    operator delete[](void*)();
    lVar3 = **(long **)PTR__ZN4Aska6Global19m_pNetworkAllocatorE_02cbc200;
    if (lVar3 == 0) {
      lVar3 = Aska::Global::GetAvailableMemoryManager()();
    }
    lVar3 = Aska::MemoryManager::Malloc(unsigned long)(lVar3,0x20);
    *(long *)(param_2 + 0x40) = lVar3;
    goto joined_r0x022fa038;
  }
  uStack_60 = 0xefe1edb600000020;
  *(undefined4 *)(param_2 + 0x30) = 0xefe1edb6;
  *(undefined1 *)(param_2 + 0x38) = 0;
  uStack_58 = (ulong)*(uint *)(param_2 + 0x34);
  clock_gettime(1,&lStack_40);
  lStack_38 = lStack_38 + lStack_40 * 1000000000;
  iVar6 = 0xf;
  bVar2 = (byte)((ulong)lStack_38 >> 0x38);
  bVar10 = (byte)((ulong)lStack_38 >> 8);
  bVar11 = (byte)((ulong)lStack_38 >> 0x10);
  bVar12 = (byte)((ulong)lStack_38 >> 0x18);
  bVar13 = (byte)((ulong)lStack_38 >> 0x20);
  bVar14 = (byte)((ulong)lStack_38 >> 0x28);
  bVar15 = (byte)((ulong)lStack_38 >> 0x30);
  uStack_58 = CONCAT17((byte)(uStack_58 >> 0x38) ^ bVar2,
                       CONCAT16((byte)(uStack_58 >> 0x30) ^ bVar15,
                                CONCAT15((byte)(uStack_58 >> 0x28) ^ bVar14,
                                         CONCAT14((byte)(uStack_58 >> 0x20) ^ bVar13,
                                                  CONCAT13((byte)(uStack_58 >> 0x18) ^ bVar12,
                                                           CONCAT12((byte)(uStack_58 >> 0x10) ^
                                                                    bVar11,CONCAT11((byte)(uStack_58
                                                                                          >> 8) ^
                                                                                    bVar10,(byte)
                                                  uStack_58 ^ (byte)lStack_38)))))));
  uStack_60 = CONCAT17((byte)((ulong)uStack_60 >> 0x38) ^ bVar2,
                       CONCAT16((byte)((ulong)uStack_60 >> 0x30) ^ bVar15,
                                CONCAT15((byte)((ulong)uStack_60 >> 0x28) ^ bVar14,
                                         CONCAT14((byte)((ulong)uStack_60 >> 0x20) ^ bVar13,
                                                  CONCAT13((byte)((ulong)uStack_60 >> 0x18) ^ bVar12
                                                           ,CONCAT12((byte)((ulong)uStack_60 >> 0x10
                                                                           ) ^ bVar11,
                                                                     CONCAT11((byte)((ulong)
                                                  uStack_60 >> 8) ^ bVar10,
                                                  (byte)uStack_60 ^ (byte)lStack_38)))))));
  uVar8 = 0x17;
  lStack_50 = lStack_38;
  do {
    uVar4 = (uint)((ulong)lStack_38 >> 0x20);
    uVar5 = (uint)bVar2;
    switch(uVar8 & 0xffffffff) {
    case 0:
      uVar5 = (uint)(ushort)((ulong)lStack_38 >> 0x30);
      break;
    case 1:
      uVar5 = uVar4;
      break;
    case 2:
      uVar5 = (uint)((ulong)lStack_38 >> 0x18);
      break;
    case 3:
      uVar5 = (uint)lStack_38;
      break;
    case 4:
      break;
    case 5:
      uVar5 = (uint)((ulong)lStack_38 >> 8);
      break;
    case 6:
      uVar5 = (uint)((ulong)lStack_38 >> 0x10);
      break;
    case 7:
      uVar5 = uVar4 >> 8;
      break;
    default:
      lVar3 = (long)iVar6;
      iVar6 = iVar6 + -1;
      uVar5 = (uint)*(byte *)((long)&uStack_60 + lVar3);
    }
    *(char *)((long)&uStack_60 + uVar8) = (char)uVar5;
    bVar1 = 0 < (long)uVar8;
    uVar8 = uVar8 - 1;
  } while (bVar1);
  puVar9 = *(undefined8 **)(param_2 + 0x40);
  uVar7 = 0;
  puVar9[2] = lStack_50;
  puVar9[1] = uStack_58;
  *puVar9 = uStack_60;
  lVar3 = *(long *)(param_2 + 0x40);
  *(undefined4 *)(lVar3 + 0x18) = param_3;
  *(undefined4 *)(lVar3 + 0x1c) = param_4;
  *(undefined4 *)(param_2 + 0x24) = 0x20;
code_r0x022fa044:
  *param_1 = uVar7;
  return;
}

// ==== undefined Aska::Yayoi::MultiplayRPC::LobbyProtocoledData::SetGetRoomList(Aska::Yayoi::MultiplayRPC::PlayerInfo const &,Aska::Yayoi::MultiplayRPC::RoomCondition const &,int,int)
// _ZN4Aska5Yayoi12MultiplayRPC19LobbyProtocoledData14SetGetRoomListERKNS1_10PlayerInfoERKNS1_13RoomConditionEii @ 022fa238

void _ZN4Aska5Yayoi12MultiplayRPC19LobbyProtocoledData14SetGetRoomListERKNS1_10PlayerInfoERKNS1_13RoomConditionEii
               (undefined8 *param_1,long param_2,undefined8 param_3,undefined8 param_4,uint param_5,
               uint param_6)

{
  bool bVar1;
  byte bVar2;
  long lVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  undefined8 uVar7;
  undefined8 *puVar8;
  ulong uVar9;
  byte bVar10;
  byte bVar11;
  byte bVar12;
  byte bVar13;
  byte bVar14;
  byte bVar15;
  undefined8 uStack_70;
  ulong uStack_68;
  long lStack_60;
  long lStack_50;
  long lStack_48;
  
  uVar7 = 0xfffffffffffffc43;
  if (((int)param_6 <= (int)param_5) || ((int)(param_6 | param_5) < 0)) goto code_r0x022fa440;
  if (*(long *)(param_2 + 0x40) == 0) {
    lVar3 = **(long **)PTR__ZN4Aska6Global19m_pNetworkAllocatorE_02cbc200;
    if (lVar3 == 0) {
      lVar3 = Aska::Global::GetAvailableMemoryManager()();
    }
    lVar3 = Aska::MemoryManager::Malloc(unsigned long)(lVar3,0x278);
    *(long *)(param_2 + 0x40) = lVar3;
joined_r0x022fa434:
    if (lVar3 == 0) {
      *(undefined4 *)(param_2 + 0x20) = 0;
      uVar7 = 0xfffffffffffffc41;
      goto code_r0x022fa440;
    }
    *(undefined4 *)(param_2 + 0x20) = 0x278;
  }
  else if (*(uint *)(param_2 + 0x20) < 0x278) {
    operator delete[](void*)();
    lVar3 = **(long **)PTR__ZN4Aska6Global19m_pNetworkAllocatorE_02cbc200;
    if (lVar3 == 0) {
      lVar3 = Aska::Global::GetAvailableMemoryManager()();
    }
    lVar3 = Aska::MemoryManager::Malloc(unsigned long)(lVar3,0x278);
    *(long *)(param_2 + 0x40) = lVar3;
    goto joined_r0x022fa434;
  }
  uStack_70 = 0x2ddf640d00000278;
  *(undefined4 *)(param_2 + 0x30) = 0x2ddf640d;
  *(undefined1 *)(param_2 + 0x38) = 0;
  uStack_68 = (ulong)*(uint *)(param_2 + 0x34);
  clock_gettime(1,&lStack_50);
  lStack_48 = lStack_48 + lStack_50 * 1000000000;
  iVar6 = 0xf;
  bVar2 = (byte)((ulong)lStack_48 >> 0x38);
  bVar10 = (byte)((ulong)lStack_48 >> 8);
  bVar11 = (byte)((ulong)lStack_48 >> 0x10);
  bVar12 = (byte)((ulong)lStack_48 >> 0x18);
  bVar13 = (byte)((ulong)lStack_48 >> 0x20);
  bVar14 = (byte)((ulong)lStack_48 >> 0x28);
  bVar15 = (byte)((ulong)lStack_48 >> 0x30);
  uStack_68 = CONCAT17((byte)(uStack_68 >> 0x38) ^ bVar2,
                       CONCAT16((byte)(uStack_68 >> 0x30) ^ bVar15,
                                CONCAT15((byte)(uStack_68 >> 0x28) ^ bVar14,
                                         CONCAT14((byte)(uStack_68 >> 0x20) ^ bVar13,
                                                  CONCAT13((byte)(uStack_68 >> 0x18) ^ bVar12,
                                                           CONCAT12((byte)(uStack_68 >> 0x10) ^
                                                                    bVar11,CONCAT11((byte)(uStack_68
                                                                                          >> 8) ^
                                                                                    bVar10,(byte)
                                                  uStack_68 ^ (byte)lStack_48)))))));
  uStack_70 = CONCAT17((byte)((ulong)uStack_70 >> 0x38) ^ bVar2,
                       CONCAT16((byte)((ulong)uStack_70 >> 0x30) ^ bVar15,
                                CONCAT15((byte)((ulong)uStack_70 >> 0x28) ^ bVar14,
                                         CONCAT14((byte)((ulong)uStack_70 >> 0x20) ^ bVar13,
                                                  CONCAT13((byte)((ulong)uStack_70 >> 0x18) ^ bVar12
                                                           ,CONCAT12((byte)((ulong)uStack_70 >> 0x10
                                                                           ) ^ bVar11,
                                                                     CONCAT11((byte)((ulong)
                                                  uStack_70 >> 8) ^ bVar10,
                                                  (byte)uStack_70 ^ (byte)lStack_48)))))));
  uVar9 = 0x17;
  lStack_60 = lStack_48;
  do {
    uVar4 = (uint)((ulong)lStack_48 >> 0x20);
    uVar5 = (uint)bVar2;
    switch(uVar9 & 0xffffffff) {
    case 0:
      uVar5 = (uint)(ushort)((ulong)lStack_48 >> 0x30);
      break;
    case 1:
      uVar5 = uVar4;
      break;
    case 2:
      uVar5 = (uint)((ulong)lStack_48 >> 0x18);
      break;
    case 3:
      uVar5 = (uint)lStack_48;
      break;
    case 4:
      break;
    case 5:
      uVar5 = (uint)((ulong)lStack_48 >> 8);
      break;
    case 6:
      uVar5 = (uint)((ulong)lStack_48 >> 0x10);
      break;
    case 7:
      uVar5 = uVar4 >> 8;
      break;
    default:
      lVar3 = (long)iVar6;
      iVar6 = iVar6 + -1;
      uVar5 = (uint)*(byte *)((long)&uStack_70 + lVar3);
    }
    *(char *)((long)&uStack_70 + uVar9) = (char)uVar5;
    bVar1 = 0 < (long)uVar9;
    uVar9 = uVar9 - 1;
  } while (bVar1);
  puVar8 = *(undefined8 **)(param_2 + 0x40);
  puVar8[2] = lStack_60;
  puVar8[1] = uStack_68;
  *puVar8 = uStack_70;
  lVar3 = *(long *)(param_2 + 0x40);
  memcpy(lVar3 + 0x18,param_3,0x70);
  memcpy(lVar3 + 0x88,param_4,0x1e8);
  uVar7 = 0;
  *(uint *)(lVar3 + 0x270) = param_5;
  *(uint *)(lVar3 + 0x274) = param_6;
  *(undefined4 *)(param_2 + 0x24) = 0x278;
code_r0x022fa440:
  *param_1 = uVar7;
  return;
}

