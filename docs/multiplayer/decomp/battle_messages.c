// battle_messages: Ghidra decompiles of work/libSOA-3.7.0.so (3.7.0), extracted by extract.py.
// Data, not code: see README.md and docs/multiplayer.md for what they show.

// ==== undefined Aska::Yayoi::MO::BattleProtocoledData::GetFID(void)
// _ZNK4Aska5Yayoi2MO20BattleProtocoledData6GetFIDEv @ 01592f40

undefined4 _ZNK4Aska5Yayoi2MO20BattleProtocoledData6GetFIDEv(long param_1)

{
  if (*(long *)(param_1 + 0x40) != 0) {
    return *(undefined4 *)(param_1 + 0x30);
  }
  return 0x7b1a9377;
}

// ==== undefined Aska::Yayoi::MO::BattleProtocoledData::GetProtocolError(Aska::Yayoi::MO::BattleProtocol::FunctionID &,Aska::Status &)
// _ZN4Aska5Yayoi2MO20BattleProtocoledData16GetProtocolErrorERNS1_14BattleProtocol10FunctionIDERNS_6StatusE @ 01592f5c

void _ZN4Aska5Yayoi2MO20BattleProtocoledData16GetProtocolErrorERNS1_14BattleProtocol10FunctionIDERNS_6StatusE
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

// ==== undefined Aska::Yayoi::MO::BattleProtocoledData::GetStamp(unsigned int &)
// _ZN4Aska5Yayoi2MO20BattleProtocoledData8GetStampERj @ 015932b0

void _ZN4Aska5Yayoi2MO20BattleProtocoledData8GetStampERj
               (undefined8 *param_1,long param_2,int *param_3)

{
  undefined8 uVar1;
  undefined8 uVar2;
  int iVar3;
  long lVar4;
  
  lVar4 = *(long *)(param_2 + 0x40);
  iVar3 = *(int *)(lVar4 + 0x18);
  *param_3 = iVar3;
  uVar1 = 0xfffffffffffffc43;
  if (iVar3 != 0) {
    uVar1 = 0;
  }
  uVar2 = 0xfffffffffffffc6b;
  if ((ulong)((lVar4 + 0x1c) - *(long *)(param_2 + 0x40)) <= (ulong)*(uint *)(param_2 + 0x24)) {
    uVar2 = uVar1;
  }
  *param_1 = uVar2;
  return;
}

// ==== undefined Aska::Yayoi::MO::BattleProtocoledData::GetStampPush(int &,unsigned int &)
// _ZN4Aska5Yayoi2MO20BattleProtocoledData12GetStampPushERiRj @ 015932ec

void _ZN4Aska5Yayoi2MO20BattleProtocoledData12GetStampPushERiRj
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

// ==== undefined Aska::Yayoi::MO::BattleProtocoledData::GetMissionStartPush(unsigned char * &,signed * &,unsigned int &,Aska::Cryption::TChaCha20<false> *)
// _ZN4Aska5Yayoi2MO20BattleProtocoledData19GetMissionStartPushERPhRPaRjPNS_8Cryption9TChaCha20ILb0EEE @ 01593324

void _ZN4Aska5Yayoi2MO20BattleProtocoledData19GetMissionStartPushERPhRPaRjPNS_8Cryption9TChaCha20ILb0EEE
               (undefined8 *param_1,long param_2,long *param_3,long *param_4,uint *param_5,
               undefined8 *param_6)

{
  long lVar1;
  ulong uVar2;
  ulong uVar3;
  undefined8 *puVar4;
  ulong uVar5;
  uint uVar6;
  bool bVar7;
  ulong uVar8;
  byte *pbVar9;
  undefined8 uVar10;
  ulong uVar11;
  ulong uVar12;
  undefined8 *puVar13;
  long lVar14;
  long lVar15;
  long lVar16;
  ulong uVar17;
  long lVar18;
  ulong uVar19;
  ulong uVar20;
  ulong uVar21;
  undefined8 uVar22;
  undefined8 uVar23;
  undefined8 uVar24;
  undefined8 uVar25;
  undefined8 uVar26;
  undefined8 uVar27;
  undefined8 uVar28;
  
  lVar18 = *(long *)(param_2 + 0x40);
  uVar6 = *(uint *)(param_2 + 0x24);
  uVar19 = (ulong)uVar6;
  uVar22 = *(undefined8 *)
            (PTR__ZZN4Aska8Cryption9TChaCha20ILb0EE11ResetStatusEvE8constant_02cc10e8 + 8);
  uVar10 = *(undefined8 *)PTR__ZZN4Aska8Cryption9TChaCha20ILb0EE11ResetStatusEvE8constant_02cc10e8;
  *(undefined4 *)(param_6 + 6) = 0;
  param_6[1] = uVar22;
  *param_6 = uVar10;
  if ((*(char *)((long)param_6 + 0x81) == '\0') || (*(char *)(param_6 + 0x10) == '\0')) {
    uVar10 = 0xfffffffffffffc5b;
  }
  else {
    uVar6 = uVar6 - 0x18;
    uVar21 = (ulong)uVar6;
    uVar20 = 0;
    lVar1 = lVar18 + uVar19;
    lVar16 = lVar18;
    uVar17 = ~uVar21;
    do {
      lVar15 = uVar20 * 0x40;
      uVar2 = lVar15 + ~uVar21;
      uVar12 = uVar17;
      if ((long)uVar17 < -0x40) {
        uVar12 = 0xffffffffffffffbf;
      }
      if ((long)uVar2 < -0x40) {
        uVar2 = 0xffffffffffffffbf;
      }
      Aska::Cryption::TChaCha20<false>::CreateKeyStream()(param_6);
      uVar5 = lVar15 + 0x40;
      if ((long)(uVar21 + uVar20 * -0x40) < 0x41) {
        uVar5 = uVar21;
      }
      if (lVar15 < (long)uVar5) {
        if (uVar2 < 0xffffffffffffffe0) {
          uVar11 = ~uVar2 & 0xffffffffffffffe0;
          if (uVar11 == 0) goto code_r0x015934d0;
          uVar3 = lVar18 + lVar15 + uVar19;
          puVar13 = (undefined8 *)((lVar18 + (uVar19 - 1) + lVar15) - uVar2);
          uVar8 = 0;
          if (((lVar18 + (uVar20 << 6 | 0x17)) - uVar2 <= uVar3 ||
               puVar13 <= (undefined8 *)(lVar18 + (uVar20 << 6 | 0x18))) &&
             ((long)param_6 + (0x3f - uVar2) <= uVar3 || puVar13 <= param_6 + 8)) {
            uVar12 = ~uVar12 & 0xffffffffffffffe0;
            lVar15 = lVar15 + uVar11;
            puVar13 = param_6 + 10;
            lVar14 = lVar16;
            do {
              uVar22 = *(undefined8 *)(lVar14 + 0x20);
              uVar10 = *(undefined8 *)(lVar14 + 0x18);
              uVar24 = *(undefined8 *)(lVar14 + 0x30);
              uVar23 = *(undefined8 *)(lVar14 + 0x28);
              uVar26 = puVar13[-1];
              uVar25 = puVar13[-2];
              uVar28 = puVar13[1];
              uVar27 = *puVar13;
              puVar4 = (undefined8 *)(lVar14 + uVar19);
              lVar14 = lVar14 + 0x20;
              uVar12 = uVar12 - 0x20;
              puVar13 = puVar13 + 4;
              puVar4[1] = CONCAT17((byte)((ulong)uVar26 >> 0x38) ^ (byte)((ulong)uVar22 >> 0x38),
                                   CONCAT16((byte)((ulong)uVar26 >> 0x30) ^
                                            (byte)((ulong)uVar22 >> 0x30),
                                            CONCAT15((byte)((ulong)uVar26 >> 0x28) ^
                                                     (byte)((ulong)uVar22 >> 0x28),
                                                     CONCAT14((byte)((ulong)uVar26 >> 0x20) ^
                                                              (byte)((ulong)uVar22 >> 0x20),
                                                              CONCAT13((byte)((ulong)uVar26 >> 0x18)
                                                                       ^ (byte)((ulong)uVar22 >>
                                                                               0x18),
                                                                       CONCAT12((byte)((ulong)uVar26
                                                                                      >> 0x10) ^
                                                                                (byte)((ulong)uVar22
                                                                                      >> 0x10),
                                                                                CONCAT11((byte)((
                                                  ulong)uVar26 >> 8) ^ (byte)((ulong)uVar22 >> 8),
                                                  (byte)uVar26 ^ (byte)uVar22)))))));
              *puVar4 = CONCAT17((byte)((ulong)uVar25 >> 0x38) ^ (byte)((ulong)uVar10 >> 0x38),
                                 CONCAT16((byte)((ulong)uVar25 >> 0x30) ^
                                          (byte)((ulong)uVar10 >> 0x30),
                                          CONCAT15((byte)((ulong)uVar25 >> 0x28) ^
                                                   (byte)((ulong)uVar10 >> 0x28),
                                                   CONCAT14((byte)((ulong)uVar25 >> 0x20) ^
                                                            (byte)((ulong)uVar10 >> 0x20),
                                                            CONCAT13((byte)((ulong)uVar25 >> 0x18) ^
                                                                     (byte)((ulong)uVar10 >> 0x18),
                                                                     CONCAT12((byte)((ulong)uVar25
                                                                                    >> 0x10) ^
                                                                              (byte)((ulong)uVar10
                                                                                    >> 0x10),
                                                                              CONCAT11((byte)((ulong
                                                  )uVar25 >> 8) ^ (byte)((ulong)uVar10 >> 8),
                                                  (byte)uVar25 ^ (byte)uVar10)))))));
              puVar4[3] = CONCAT17((byte)((ulong)uVar28 >> 0x38) ^ (byte)((ulong)uVar24 >> 0x38),
                                   CONCAT16((byte)((ulong)uVar28 >> 0x30) ^
                                            (byte)((ulong)uVar24 >> 0x30),
                                            CONCAT15((byte)((ulong)uVar28 >> 0x28) ^
                                                     (byte)((ulong)uVar24 >> 0x28),
                                                     CONCAT14((byte)((ulong)uVar28 >> 0x20) ^
                                                              (byte)((ulong)uVar24 >> 0x20),
                                                              CONCAT13((byte)((ulong)uVar28 >> 0x18)
                                                                       ^ (byte)((ulong)uVar24 >>
                                                                               0x18),
                                                                       CONCAT12((byte)((ulong)uVar28
                                                                                      >> 0x10) ^
                                                                                (byte)((ulong)uVar24
                                                                                      >> 0x10),
                                                                                CONCAT11((byte)((
                                                  ulong)uVar28 >> 8) ^ (byte)((ulong)uVar24 >> 8),
                                                  (byte)uVar28 ^ (byte)uVar24)))))));
              puVar4[2] = CONCAT17((byte)((ulong)uVar27 >> 0x38) ^ (byte)((ulong)uVar23 >> 0x38),
                                   CONCAT16((byte)((ulong)uVar27 >> 0x30) ^
                                            (byte)((ulong)uVar23 >> 0x30),
                                            CONCAT15((byte)((ulong)uVar27 >> 0x28) ^
                                                     (byte)((ulong)uVar23 >> 0x28),
                                                     CONCAT14((byte)((ulong)uVar27 >> 0x20) ^
                                                              (byte)((ulong)uVar23 >> 0x20),
                                                              CONCAT13((byte)((ulong)uVar27 >> 0x18)
                                                                       ^ (byte)((ulong)uVar23 >>
                                                                               0x18),
                                                                       CONCAT12((byte)((ulong)uVar27
                                                                                      >> 0x10) ^
                                                                                (byte)((ulong)uVar23
                                                                                      >> 0x10),
                                                                                CONCAT11((byte)((
                                                  ulong)uVar27 >> 8) ^ (byte)((ulong)uVar23 >> 8),
                                                  (byte)uVar27 ^ (byte)uVar23)))))));
            } while (uVar12 != 0);
            uVar8 = uVar11;
            if (uVar11 == ~uVar2) goto code_r0x015934fc;
          }
        }
        else {
code_r0x015934d0:
          uVar8 = 0;
        }
        pbVar9 = (byte *)((long)(param_6 + 8) + uVar8);
        do {
          *(byte *)(lVar1 + lVar15) = *pbVar9 ^ *(byte *)(lVar18 + lVar15 + 0x18);
          lVar15 = lVar15 + 1;
          pbVar9 = pbVar9 + 1;
        } while (lVar15 < (long)uVar5);
      }
code_r0x015934fc:
      uVar17 = uVar17 + 0x40;
      lVar16 = lVar16 + 0x40;
      bVar7 = uVar20 != uVar6 >> 6;
      uVar20 = uVar20 + 1;
      *(int *)(param_6 + 6) = *(int *)(param_6 + 6) + 1;
    } while (bVar7);
    *param_3 = lVar1;
    *param_5 = *(uint *)(lVar1 + 4);
    *param_4 = lVar1 + 8;
    uVar10 = 0xfffffffffffffc6b;
    if (lVar1 + 4 + (((ulong)*param_5 + 4) - *(long *)(param_2 + 0x40)) <=
        (ulong)*(uint *)(param_2 + 0x20)) {
      uVar10 = 0;
    }
  }
  *param_1 = uVar10;
  return;
}

// ==== undefined Aska::Yayoi::MO::BattleProtocoledData::GetMissionEnd(signed * &,Aska::Yayoi::MO::DeviceType &,signed * &,unsigned int &,Aska::Cryption::TChaCha20<false> *)
// _ZN4Aska5Yayoi2MO20BattleProtocoledData13GetMissionEndERPaRNS1_10DeviceTypeES4_RjPNS_8Cryption9TChaCha20ILb0EEE @ 01593598

void _ZN4Aska5Yayoi2MO20BattleProtocoledData13GetMissionEndERPaRNS1_10DeviceTypeES4_RjPNS_8Cryption9TChaCha20ILb0EEE
               (undefined8 *param_1,long param_2,long *param_3,int *param_4,long *param_5,
               uint *param_6,undefined8 *param_7)

{
  long lVar1;
  ulong uVar2;
  ulong uVar3;
  undefined8 *puVar4;
  ulong uVar5;
  uint uVar6;
  bool bVar7;
  ulong uVar8;
  byte *pbVar9;
  undefined8 uVar10;
  ulong uVar11;
  ulong uVar12;
  undefined8 *puVar13;
  long lVar14;
  ulong uVar15;
  long lVar16;
  long lVar17;
  ulong uVar18;
  long lVar19;
  ulong uVar20;
  ulong uVar21;
  undefined8 uVar22;
  undefined8 uVar23;
  undefined8 uVar24;
  undefined8 uVar25;
  undefined8 uVar26;
  undefined8 uVar27;
  undefined8 uVar28;
  
  lVar19 = *(long *)(param_2 + 0x40);
  uVar6 = *(uint *)(param_2 + 0x24);
  uVar20 = (ulong)uVar6;
  uVar22 = *(undefined8 *)
            (PTR__ZZN4Aska8Cryption9TChaCha20ILb0EE11ResetStatusEvE8constant_02cc10e8 + 8);
  uVar10 = *(undefined8 *)PTR__ZZN4Aska8Cryption9TChaCha20ILb0EE11ResetStatusEvE8constant_02cc10e8;
  *(undefined4 *)(param_7 + 6) = 0;
  param_7[1] = uVar22;
  *param_7 = uVar10;
  if ((*(char *)((long)param_7 + 0x81) == '\0') || (*(char *)(param_7 + 0x10) == '\0')) {
    uVar10 = 0xfffffffffffffc5b;
  }
  else {
    uVar6 = uVar6 - 0x18;
    uVar15 = (ulong)uVar6;
    uVar21 = 0;
    lVar1 = lVar19 + uVar20;
    lVar16 = lVar19;
    uVar18 = ~uVar15;
    do {
      lVar17 = uVar21 * 0x40;
      uVar2 = lVar17 + ~uVar15;
      uVar12 = uVar18;
      if ((long)uVar18 < -0x40) {
        uVar12 = 0xffffffffffffffbf;
      }
      if ((long)uVar2 < -0x40) {
        uVar2 = 0xffffffffffffffbf;
      }
      Aska::Cryption::TChaCha20<false>::CreateKeyStream()(param_7);
      uVar5 = lVar17 + 0x40;
      if ((long)(uVar15 + uVar21 * -0x40) < 0x41) {
        uVar5 = uVar15;
      }
      if (lVar17 < (long)uVar5) {
        if (uVar2 < 0xffffffffffffffe0) {
          uVar11 = ~uVar2 & 0xffffffffffffffe0;
          if (uVar11 == 0) goto code_r0x01593744;
          uVar3 = lVar19 + lVar17 + uVar20;
          puVar13 = (undefined8 *)((lVar19 + (uVar20 - 1) + lVar17) - uVar2);
          uVar8 = 0;
          if (((lVar19 + (uVar21 << 6 | 0x17)) - uVar2 <= uVar3 ||
               puVar13 <= (undefined8 *)(lVar19 + (uVar21 << 6 | 0x18))) &&
             ((long)param_7 + (0x3f - uVar2) <= uVar3 || puVar13 <= param_7 + 8)) {
            uVar12 = ~uVar12 & 0xffffffffffffffe0;
            lVar17 = lVar17 + uVar11;
            puVar13 = param_7 + 10;
            lVar14 = lVar16;
            do {
              uVar22 = *(undefined8 *)(lVar14 + 0x20);
              uVar10 = *(undefined8 *)(lVar14 + 0x18);
              uVar24 = *(undefined8 *)(lVar14 + 0x30);
              uVar23 = *(undefined8 *)(lVar14 + 0x28);
              uVar26 = puVar13[-1];
              uVar25 = puVar13[-2];
              uVar28 = puVar13[1];
              uVar27 = *puVar13;
              puVar4 = (undefined8 *)(lVar14 + uVar20);
              lVar14 = lVar14 + 0x20;
              uVar12 = uVar12 - 0x20;
              puVar13 = puVar13 + 4;
              puVar4[1] = CONCAT17((byte)((ulong)uVar26 >> 0x38) ^ (byte)((ulong)uVar22 >> 0x38),
                                   CONCAT16((byte)((ulong)uVar26 >> 0x30) ^
                                            (byte)((ulong)uVar22 >> 0x30),
                                            CONCAT15((byte)((ulong)uVar26 >> 0x28) ^
                                                     (byte)((ulong)uVar22 >> 0x28),
                                                     CONCAT14((byte)((ulong)uVar26 >> 0x20) ^
                                                              (byte)((ulong)uVar22 >> 0x20),
                                                              CONCAT13((byte)((ulong)uVar26 >> 0x18)
                                                                       ^ (byte)((ulong)uVar22 >>
                                                                               0x18),
                                                                       CONCAT12((byte)((ulong)uVar26
                                                                                      >> 0x10) ^
                                                                                (byte)((ulong)uVar22
                                                                                      >> 0x10),
                                                                                CONCAT11((byte)((
                                                  ulong)uVar26 >> 8) ^ (byte)((ulong)uVar22 >> 8),
                                                  (byte)uVar26 ^ (byte)uVar22)))))));
              *puVar4 = CONCAT17((byte)((ulong)uVar25 >> 0x38) ^ (byte)((ulong)uVar10 >> 0x38),
                                 CONCAT16((byte)((ulong)uVar25 >> 0x30) ^
                                          (byte)((ulong)uVar10 >> 0x30),
                                          CONCAT15((byte)((ulong)uVar25 >> 0x28) ^
                                                   (byte)((ulong)uVar10 >> 0x28),
                                                   CONCAT14((byte)((ulong)uVar25 >> 0x20) ^
                                                            (byte)((ulong)uVar10 >> 0x20),
                                                            CONCAT13((byte)((ulong)uVar25 >> 0x18) ^
                                                                     (byte)((ulong)uVar10 >> 0x18),
                                                                     CONCAT12((byte)((ulong)uVar25
                                                                                    >> 0x10) ^
                                                                              (byte)((ulong)uVar10
                                                                                    >> 0x10),
                                                                              CONCAT11((byte)((ulong
                                                  )uVar25 >> 8) ^ (byte)((ulong)uVar10 >> 8),
                                                  (byte)uVar25 ^ (byte)uVar10)))))));
              puVar4[3] = CONCAT17((byte)((ulong)uVar28 >> 0x38) ^ (byte)((ulong)uVar24 >> 0x38),
                                   CONCAT16((byte)((ulong)uVar28 >> 0x30) ^
                                            (byte)((ulong)uVar24 >> 0x30),
                                            CONCAT15((byte)((ulong)uVar28 >> 0x28) ^
                                                     (byte)((ulong)uVar24 >> 0x28),
                                                     CONCAT14((byte)((ulong)uVar28 >> 0x20) ^
                                                              (byte)((ulong)uVar24 >> 0x20),
                                                              CONCAT13((byte)((ulong)uVar28 >> 0x18)
                                                                       ^ (byte)((ulong)uVar24 >>
                                                                               0x18),
                                                                       CONCAT12((byte)((ulong)uVar28
                                                                                      >> 0x10) ^
                                                                                (byte)((ulong)uVar24
                                                                                      >> 0x10),
                                                                                CONCAT11((byte)((
                                                  ulong)uVar28 >> 8) ^ (byte)((ulong)uVar24 >> 8),
                                                  (byte)uVar28 ^ (byte)uVar24)))))));
              puVar4[2] = CONCAT17((byte)((ulong)uVar27 >> 0x38) ^ (byte)((ulong)uVar23 >> 0x38),
                                   CONCAT16((byte)((ulong)uVar27 >> 0x30) ^
                                            (byte)((ulong)uVar23 >> 0x30),
                                            CONCAT15((byte)((ulong)uVar27 >> 0x28) ^
                                                     (byte)((ulong)uVar23 >> 0x28),
                                                     CONCAT14((byte)((ulong)uVar27 >> 0x20) ^
                                                              (byte)((ulong)uVar23 >> 0x20),
                                                              CONCAT13((byte)((ulong)uVar27 >> 0x18)
                                                                       ^ (byte)((ulong)uVar23 >>
                                                                               0x18),
                                                                       CONCAT12((byte)((ulong)uVar27
                                                                                      >> 0x10) ^
                                                                                (byte)((ulong)uVar23
                                                                                      >> 0x10),
                                                                                CONCAT11((byte)((
                                                  ulong)uVar27 >> 8) ^ (byte)((ulong)uVar23 >> 8),
                                                  (byte)uVar27 ^ (byte)uVar23)))))));
            } while (uVar12 != 0);
            uVar8 = uVar11;
            if (uVar11 == ~uVar2) goto code_r0x01593770;
          }
        }
        else {
code_r0x01593744:
          uVar8 = 0;
        }
        pbVar9 = (byte *)((long)(param_7 + 8) + uVar8);
        do {
          *(byte *)(lVar1 + lVar17) = *pbVar9 ^ *(byte *)(lVar19 + lVar17 + 0x18);
          lVar17 = lVar17 + 1;
          pbVar9 = pbVar9 + 1;
        } while (lVar17 < (long)uVar5);
      }
code_r0x01593770:
      uVar18 = uVar18 + 0x40;
      lVar16 = lVar16 + 0x40;
      bVar7 = uVar21 != uVar6 >> 6;
      uVar21 = uVar21 + 1;
      *(int *)(param_7 + 6) = *(int *)(param_7 + 6) + 1;
    } while (bVar7);
    *param_3 = lVar1;
    *param_4 = *(int *)(lVar1 + 0x24);
    *param_6 = *(uint *)(lVar1 + 0x28);
    *param_5 = lVar1 + 0x2c;
    if ((ulong)*(uint *)(param_2 + 0x20) <
        lVar1 + 0x28 + (((ulong)*param_6 + 4) - *(long *)(param_2 + 0x40))) {
      uVar10 = 0xfffffffffffffc6b;
    }
    else if ((char *)*param_3 == (char *)0x0) {
      uVar10 = 0xfffffffffffffc43;
    }
    else {
      uVar10 = 0xfffffffffffffc43;
      if ((*(char *)*param_3 != '\0') && (uVar10 = 0xfffffffffffffc43, *param_4 - 1U < 99)) {
        uVar10 = 0;
      }
    }
  }
  *param_1 = uVar10;
  return;
}

// ==== undefined Aska::Yayoi::MO::BattleProtocoledData::GetMissionEndPush(signed * &,unsigned int &,Aska::Cryption::TChaCha20<false> *)
// _ZN4Aska5Yayoi2MO20BattleProtocoledData17GetMissionEndPushERPaRjPNS_8Cryption9TChaCha20ILb0EEE @ 01593848

void _ZN4Aska5Yayoi2MO20BattleProtocoledData17GetMissionEndPushERPaRjPNS_8Cryption9TChaCha20ILb0EEE
               (undefined8 *param_1,long param_2,undefined8 *param_3,uint *param_4,
               undefined8 *param_5)

{
  uint *puVar1;
  ulong uVar2;
  ulong uVar3;
  undefined8 *puVar4;
  ulong uVar5;
  uint uVar6;
  bool bVar7;
  ulong uVar8;
  byte *pbVar9;
  undefined8 uVar10;
  ulong uVar11;
  ulong uVar12;
  undefined8 *puVar13;
  long lVar14;
  long lVar15;
  long lVar16;
  long lVar17;
  ulong uVar18;
  ulong uVar19;
  ulong uVar20;
  ulong uVar21;
  undefined8 uVar22;
  undefined8 uVar23;
  undefined8 uVar24;
  undefined8 uVar25;
  undefined8 uVar26;
  undefined8 uVar27;
  undefined8 uVar28;
  
  lVar17 = *(long *)(param_2 + 0x40);
  uVar6 = *(uint *)(param_2 + 0x24);
  uVar18 = (ulong)uVar6;
  uVar22 = *(undefined8 *)
            (PTR__ZZN4Aska8Cryption9TChaCha20ILb0EE11ResetStatusEvE8constant_02cc10e8 + 8);
  uVar10 = *(undefined8 *)PTR__ZZN4Aska8Cryption9TChaCha20ILb0EE11ResetStatusEvE8constant_02cc10e8;
  *(undefined4 *)(param_5 + 6) = 0;
  param_5[1] = uVar22;
  *param_5 = uVar10;
  if ((*(char *)((long)param_5 + 0x81) == '\0') || (*(char *)(param_5 + 0x10) == '\0')) {
    uVar10 = 0xfffffffffffffc5b;
  }
  else {
    uVar6 = uVar6 - 0x18;
    uVar20 = (ulong)uVar6;
    uVar19 = 0;
    puVar1 = (uint *)(lVar17 + uVar18);
    lVar16 = lVar17;
    uVar21 = ~uVar20;
    do {
      lVar15 = uVar19 * 0x40;
      uVar2 = lVar15 + ~uVar20;
      uVar12 = uVar21;
      if ((long)uVar21 < -0x40) {
        uVar12 = 0xffffffffffffffbf;
      }
      if ((long)uVar2 < -0x40) {
        uVar2 = 0xffffffffffffffbf;
      }
      Aska::Cryption::TChaCha20<false>::CreateKeyStream()(param_5);
      uVar5 = lVar15 + 0x40;
      if ((long)(uVar20 + uVar19 * -0x40) < 0x41) {
        uVar5 = uVar20;
      }
      if (lVar15 < (long)uVar5) {
        if (uVar2 < 0xffffffffffffffe0) {
          uVar11 = ~uVar2 & 0xffffffffffffffe0;
          if (uVar11 == 0) goto code_r0x015939f0;
          uVar3 = lVar17 + lVar15 + uVar18;
          puVar13 = (undefined8 *)((lVar17 + (uVar18 - 1) + lVar15) - uVar2);
          uVar8 = 0;
          if (((lVar17 + (uVar19 << 6 | 0x17)) - uVar2 <= uVar3 ||
               puVar13 <= (undefined8 *)(lVar17 + (uVar19 << 6 | 0x18))) &&
             ((long)param_5 + (0x3f - uVar2) <= uVar3 || puVar13 <= param_5 + 8)) {
            uVar12 = ~uVar12 & 0xffffffffffffffe0;
            lVar15 = lVar15 + uVar11;
            puVar13 = param_5 + 10;
            lVar14 = lVar16;
            do {
              uVar22 = *(undefined8 *)(lVar14 + 0x20);
              uVar10 = *(undefined8 *)(lVar14 + 0x18);
              uVar24 = *(undefined8 *)(lVar14 + 0x30);
              uVar23 = *(undefined8 *)(lVar14 + 0x28);
              uVar26 = puVar13[-1];
              uVar25 = puVar13[-2];
              uVar28 = puVar13[1];
              uVar27 = *puVar13;
              puVar4 = (undefined8 *)(lVar14 + uVar18);
              lVar14 = lVar14 + 0x20;
              uVar12 = uVar12 - 0x20;
              puVar13 = puVar13 + 4;
              puVar4[1] = CONCAT17((byte)((ulong)uVar26 >> 0x38) ^ (byte)((ulong)uVar22 >> 0x38),
                                   CONCAT16((byte)((ulong)uVar26 >> 0x30) ^
                                            (byte)((ulong)uVar22 >> 0x30),
                                            CONCAT15((byte)((ulong)uVar26 >> 0x28) ^
                                                     (byte)((ulong)uVar22 >> 0x28),
                                                     CONCAT14((byte)((ulong)uVar26 >> 0x20) ^
                                                              (byte)((ulong)uVar22 >> 0x20),
                                                              CONCAT13((byte)((ulong)uVar26 >> 0x18)
                                                                       ^ (byte)((ulong)uVar22 >>
                                                                               0x18),
                                                                       CONCAT12((byte)((ulong)uVar26
                                                                                      >> 0x10) ^
                                                                                (byte)((ulong)uVar22
                                                                                      >> 0x10),
                                                                                CONCAT11((byte)((
                                                  ulong)uVar26 >> 8) ^ (byte)((ulong)uVar22 >> 8),
                                                  (byte)uVar26 ^ (byte)uVar22)))))));
              *puVar4 = CONCAT17((byte)((ulong)uVar25 >> 0x38) ^ (byte)((ulong)uVar10 >> 0x38),
                                 CONCAT16((byte)((ulong)uVar25 >> 0x30) ^
                                          (byte)((ulong)uVar10 >> 0x30),
                                          CONCAT15((byte)((ulong)uVar25 >> 0x28) ^
                                                   (byte)((ulong)uVar10 >> 0x28),
                                                   CONCAT14((byte)((ulong)uVar25 >> 0x20) ^
                                                            (byte)((ulong)uVar10 >> 0x20),
                                                            CONCAT13((byte)((ulong)uVar25 >> 0x18) ^
                                                                     (byte)((ulong)uVar10 >> 0x18),
                                                                     CONCAT12((byte)((ulong)uVar25
                                                                                    >> 0x10) ^
                                                                              (byte)((ulong)uVar10
                                                                                    >> 0x10),
                                                                              CONCAT11((byte)((ulong
                                                  )uVar25 >> 8) ^ (byte)((ulong)uVar10 >> 8),
                                                  (byte)uVar25 ^ (byte)uVar10)))))));
              puVar4[3] = CONCAT17((byte)((ulong)uVar28 >> 0x38) ^ (byte)((ulong)uVar24 >> 0x38),
                                   CONCAT16((byte)((ulong)uVar28 >> 0x30) ^
                                            (byte)((ulong)uVar24 >> 0x30),
                                            CONCAT15((byte)((ulong)uVar28 >> 0x28) ^
                                                     (byte)((ulong)uVar24 >> 0x28),
                                                     CONCAT14((byte)((ulong)uVar28 >> 0x20) ^
                                                              (byte)((ulong)uVar24 >> 0x20),
                                                              CONCAT13((byte)((ulong)uVar28 >> 0x18)
                                                                       ^ (byte)((ulong)uVar24 >>
                                                                               0x18),
                                                                       CONCAT12((byte)((ulong)uVar28
                                                                                      >> 0x10) ^
                                                                                (byte)((ulong)uVar24
                                                                                      >> 0x10),
                                                                                CONCAT11((byte)((
                                                  ulong)uVar28 >> 8) ^ (byte)((ulong)uVar24 >> 8),
                                                  (byte)uVar28 ^ (byte)uVar24)))))));
              puVar4[2] = CONCAT17((byte)((ulong)uVar27 >> 0x38) ^ (byte)((ulong)uVar23 >> 0x38),
                                   CONCAT16((byte)((ulong)uVar27 >> 0x30) ^
                                            (byte)((ulong)uVar23 >> 0x30),
                                            CONCAT15((byte)((ulong)uVar27 >> 0x28) ^
                                                     (byte)((ulong)uVar23 >> 0x28),
                                                     CONCAT14((byte)((ulong)uVar27 >> 0x20) ^
                                                              (byte)((ulong)uVar23 >> 0x20),
                                                              CONCAT13((byte)((ulong)uVar27 >> 0x18)
                                                                       ^ (byte)((ulong)uVar23 >>
                                                                               0x18),
                                                                       CONCAT12((byte)((ulong)uVar27
                                                                                      >> 0x10) ^
                                                                                (byte)((ulong)uVar23
                                                                                      >> 0x10),
                                                                                CONCAT11((byte)((
                                                  ulong)uVar27 >> 8) ^ (byte)((ulong)uVar23 >> 8),
                                                  (byte)uVar27 ^ (byte)uVar23)))))));
            } while (uVar12 != 0);
            uVar8 = uVar11;
            if (uVar11 == ~uVar2) goto code_r0x01593a1c;
          }
        }
        else {
code_r0x015939f0:
          uVar8 = 0;
        }
        pbVar9 = (byte *)((long)(param_5 + 8) + uVar8);
        do {
          *(byte *)((long)puVar1 + lVar15) = *pbVar9 ^ *(byte *)(lVar17 + lVar15 + 0x18);
          lVar15 = lVar15 + 1;
          pbVar9 = pbVar9 + 1;
        } while (lVar15 < (long)uVar5);
      }
code_r0x01593a1c:
      uVar21 = uVar21 + 0x40;
      lVar16 = lVar16 + 0x40;
      bVar7 = uVar19 != uVar6 >> 6;
      uVar19 = uVar19 + 1;
      *(int *)(param_5 + 6) = *(int *)(param_5 + 6) + 1;
    } while (bVar7);
    *param_4 = *puVar1;
    *param_3 = puVar1 + 1;
    uVar10 = 0xfffffffffffffc6b;
    if ((long)puVar1 + (((ulong)*param_4 + 4) - *(long *)(param_2 + 0x40)) <=
        (ulong)*(uint *)(param_2 + 0x20)) {
      uVar10 = 0;
    }
  }
  *param_1 = uVar10;
  return;
}

// ==== undefined Aska::Yayoi::MO::BattleProtocoledData::GetMissionContinue(signed * &,Aska::Yayoi::MO::DeviceType &,unsigned char &,Aska::Cryption::TChaCha20<false> *)
// _ZN4Aska5Yayoi2MO20BattleProtocoledData18GetMissionContinueERPaRNS1_10DeviceTypeERhPNS_8Cryption9TChaCha20ILb0EEE @ 01593ab0

void _ZN4Aska5Yayoi2MO20BattleProtocoledData18GetMissionContinueERPaRNS1_10DeviceTypeERhPNS_8Cryption9TChaCha20ILb0EEE
               (undefined8 *param_1,long param_2,long *param_3,int *param_4,undefined1 *param_5,
               undefined8 *param_6)

{
  long lVar1;
  ulong uVar2;
  ulong uVar3;
  undefined8 *puVar4;
  ulong uVar5;
  uint uVar6;
  bool bVar7;
  ulong uVar8;
  byte *pbVar9;
  undefined8 uVar10;
  ulong uVar11;
  ulong uVar12;
  undefined8 *puVar13;
  long lVar14;
  long lVar15;
  ulong uVar16;
  long lVar17;
  long lVar18;
  ulong uVar19;
  ulong uVar20;
  ulong uVar21;
  undefined8 uVar22;
  undefined8 uVar23;
  undefined8 uVar24;
  undefined8 uVar25;
  undefined8 uVar26;
  undefined8 uVar27;
  undefined8 uVar28;
  
  lVar18 = *(long *)(param_2 + 0x40);
  uVar6 = *(uint *)(param_2 + 0x24);
  uVar19 = (ulong)uVar6;
  uVar22 = *(undefined8 *)
            (PTR__ZZN4Aska8Cryption9TChaCha20ILb0EE11ResetStatusEvE8constant_02cc10e8 + 8);
  uVar10 = *(undefined8 *)PTR__ZZN4Aska8Cryption9TChaCha20ILb0EE11ResetStatusEvE8constant_02cc10e8;
  *(undefined4 *)(param_6 + 6) = 0;
  param_6[1] = uVar22;
  *param_6 = uVar10;
  if ((*(char *)((long)param_6 + 0x81) == '\0') || (*(char *)(param_6 + 0x10) == '\0')) {
    uVar10 = 0xfffffffffffffc5b;
  }
  else {
    uVar6 = uVar6 - 0x18;
    uVar21 = (ulong)uVar6;
    uVar20 = 0;
    lVar1 = lVar18 + uVar19;
    uVar16 = ~uVar21;
    lVar17 = lVar18;
    do {
      lVar15 = uVar20 * 0x40;
      uVar2 = lVar15 + ~uVar21;
      uVar12 = uVar16;
      if ((long)uVar16 < -0x40) {
        uVar12 = 0xffffffffffffffbf;
      }
      if ((long)uVar2 < -0x40) {
        uVar2 = 0xffffffffffffffbf;
      }
      Aska::Cryption::TChaCha20<false>::CreateKeyStream()(param_6);
      uVar5 = lVar15 + 0x40;
      if ((long)(uVar21 + uVar20 * -0x40) < 0x41) {
        uVar5 = uVar21;
      }
      if (lVar15 < (long)uVar5) {
        if (uVar2 < 0xffffffffffffffe0) {
          uVar11 = ~uVar2 & 0xffffffffffffffe0;
          if (uVar11 == 0) goto code_r0x01593c5c;
          uVar3 = lVar18 + lVar15 + uVar19;
          puVar13 = (undefined8 *)((lVar18 + (uVar19 - 1) + lVar15) - uVar2);
          uVar8 = 0;
          if (((lVar18 + (uVar20 << 6 | 0x17)) - uVar2 <= uVar3 ||
               puVar13 <= (undefined8 *)(lVar18 + (uVar20 << 6 | 0x18))) &&
             ((long)param_6 + (0x3f - uVar2) <= uVar3 || puVar13 <= param_6 + 8)) {
            uVar12 = ~uVar12 & 0xffffffffffffffe0;
            lVar15 = lVar15 + uVar11;
            puVar13 = param_6 + 10;
            lVar14 = lVar17;
            do {
              uVar22 = *(undefined8 *)(lVar14 + 0x20);
              uVar10 = *(undefined8 *)(lVar14 + 0x18);
              uVar24 = *(undefined8 *)(lVar14 + 0x30);
              uVar23 = *(undefined8 *)(lVar14 + 0x28);
              uVar26 = puVar13[-1];
              uVar25 = puVar13[-2];
              uVar28 = puVar13[1];
              uVar27 = *puVar13;
              puVar4 = (undefined8 *)(lVar14 + uVar19);
              lVar14 = lVar14 + 0x20;
              uVar12 = uVar12 - 0x20;
              puVar13 = puVar13 + 4;
              puVar4[1] = CONCAT17((byte)((ulong)uVar26 >> 0x38) ^ (byte)((ulong)uVar22 >> 0x38),
                                   CONCAT16((byte)((ulong)uVar26 >> 0x30) ^
                                            (byte)((ulong)uVar22 >> 0x30),
                                            CONCAT15((byte)((ulong)uVar26 >> 0x28) ^
                                                     (byte)((ulong)uVar22 >> 0x28),
                                                     CONCAT14((byte)((ulong)uVar26 >> 0x20) ^
                                                              (byte)((ulong)uVar22 >> 0x20),
                                                              CONCAT13((byte)((ulong)uVar26 >> 0x18)
                                                                       ^ (byte)((ulong)uVar22 >>
                                                                               0x18),
                                                                       CONCAT12((byte)((ulong)uVar26
                                                                                      >> 0x10) ^
                                                                                (byte)((ulong)uVar22
                                                                                      >> 0x10),
                                                                                CONCAT11((byte)((
                                                  ulong)uVar26 >> 8) ^ (byte)((ulong)uVar22 >> 8),
                                                  (byte)uVar26 ^ (byte)uVar22)))))));
              *puVar4 = CONCAT17((byte)((ulong)uVar25 >> 0x38) ^ (byte)((ulong)uVar10 >> 0x38),
                                 CONCAT16((byte)((ulong)uVar25 >> 0x30) ^
                                          (byte)((ulong)uVar10 >> 0x30),
                                          CONCAT15((byte)((ulong)uVar25 >> 0x28) ^
                                                   (byte)((ulong)uVar10 >> 0x28),
                                                   CONCAT14((byte)((ulong)uVar25 >> 0x20) ^
                                                            (byte)((ulong)uVar10 >> 0x20),
                                                            CONCAT13((byte)((ulong)uVar25 >> 0x18) ^
                                                                     (byte)((ulong)uVar10 >> 0x18),
                                                                     CONCAT12((byte)((ulong)uVar25
                                                                                    >> 0x10) ^
                                                                              (byte)((ulong)uVar10
                                                                                    >> 0x10),
                                                                              CONCAT11((byte)((ulong
                                                  )uVar25 >> 8) ^ (byte)((ulong)uVar10 >> 8),
                                                  (byte)uVar25 ^ (byte)uVar10)))))));
              puVar4[3] = CONCAT17((byte)((ulong)uVar28 >> 0x38) ^ (byte)((ulong)uVar24 >> 0x38),
                                   CONCAT16((byte)((ulong)uVar28 >> 0x30) ^
                                            (byte)((ulong)uVar24 >> 0x30),
                                            CONCAT15((byte)((ulong)uVar28 >> 0x28) ^
                                                     (byte)((ulong)uVar24 >> 0x28),
                                                     CONCAT14((byte)((ulong)uVar28 >> 0x20) ^
                                                              (byte)((ulong)uVar24 >> 0x20),
                                                              CONCAT13((byte)((ulong)uVar28 >> 0x18)
                                                                       ^ (byte)((ulong)uVar24 >>
                                                                               0x18),
                                                                       CONCAT12((byte)((ulong)uVar28
                                                                                      >> 0x10) ^
                                                                                (byte)((ulong)uVar24
                                                                                      >> 0x10),
                                                                                CONCAT11((byte)((
                                                  ulong)uVar28 >> 8) ^ (byte)((ulong)uVar24 >> 8),
                                                  (byte)uVar28 ^ (byte)uVar24)))))));
              puVar4[2] = CONCAT17((byte)((ulong)uVar27 >> 0x38) ^ (byte)((ulong)uVar23 >> 0x38),
                                   CONCAT16((byte)((ulong)uVar27 >> 0x30) ^
                                            (byte)((ulong)uVar23 >> 0x30),
                                            CONCAT15((byte)((ulong)uVar27 >> 0x28) ^
                                                     (byte)((ulong)uVar23 >> 0x28),
                                                     CONCAT14((byte)((ulong)uVar27 >> 0x20) ^
                                                              (byte)((ulong)uVar23 >> 0x20),
                                                              CONCAT13((byte)((ulong)uVar27 >> 0x18)
                                                                       ^ (byte)((ulong)uVar23 >>
                                                                               0x18),
                                                                       CONCAT12((byte)((ulong)uVar27
                                                                                      >> 0x10) ^
                                                                                (byte)((ulong)uVar23
                                                                                      >> 0x10),
                                                                                CONCAT11((byte)((
                                                  ulong)uVar27 >> 8) ^ (byte)((ulong)uVar23 >> 8),
                                                  (byte)uVar27 ^ (byte)uVar23)))))));
            } while (uVar12 != 0);
            uVar8 = uVar11;
            if (uVar11 == ~uVar2) goto code_r0x01593c88;
          }
        }
        else {
code_r0x01593c5c:
          uVar8 = 0;
        }
        pbVar9 = (byte *)((long)(param_6 + 8) + uVar8);
        do {
          *(byte *)(lVar1 + lVar15) = *pbVar9 ^ *(byte *)(lVar18 + lVar15 + 0x18);
          lVar15 = lVar15 + 1;
          pbVar9 = pbVar9 + 1;
        } while (lVar15 < (long)uVar5);
      }
code_r0x01593c88:
      uVar16 = uVar16 + 0x40;
      lVar17 = lVar17 + 0x40;
      bVar7 = uVar20 != uVar6 >> 6;
      uVar20 = uVar20 + 1;
      *(int *)(param_6 + 6) = *(int *)(param_6 + 6) + 1;
    } while (bVar7);
    *param_3 = lVar1;
    *param_4 = *(int *)(lVar1 + 0x24);
    *param_5 = *(undefined1 *)(lVar1 + 0x28);
    if ((ulong)*(uint *)(param_2 + 0x20) < (ulong)((lVar1 + 0x29) - *(long *)(param_2 + 0x40))) {
      uVar10 = 0xfffffffffffffc6b;
    }
    else if ((char *)*param_3 == (char *)0x0) {
      uVar10 = 0xfffffffffffffc43;
    }
    else {
      uVar10 = 0xfffffffffffffc43;
      if ((*(char *)*param_3 != '\0') && (uVar10 = 0xfffffffffffffc43, *param_4 - 1U < 99)) {
        uVar10 = 0;
      }
    }
  }
  *param_1 = uVar10;
  return;
}

// ==== undefined Aska::Yayoi::MO::BattleProtocoledData::GetMissionContinueRes(signed * &,unsigned int &,Aska::Cryption::TChaCha20<false> *)
// _ZN4Aska5Yayoi2MO20BattleProtocoledData21GetMissionContinueResERPaRjPNS_8Cryption9TChaCha20ILb0EEE @ 01593d4c

void _ZN4Aska5Yayoi2MO20BattleProtocoledData21GetMissionContinueResERPaRjPNS_8Cryption9TChaCha20ILb0EEE
               (undefined8 *param_1,long param_2,undefined8 *param_3,uint *param_4,
               undefined8 *param_5)

{
  uint *puVar1;
  ulong uVar2;
  ulong uVar3;
  undefined8 *puVar4;
  ulong uVar5;
  uint uVar6;
  bool bVar7;
  ulong uVar8;
  byte *pbVar9;
  undefined8 uVar10;
  ulong uVar11;
  ulong uVar12;
  undefined8 *puVar13;
  long lVar14;
  long lVar15;
  long lVar16;
  long lVar17;
  ulong uVar18;
  ulong uVar19;
  ulong uVar20;
  ulong uVar21;
  undefined8 uVar22;
  undefined8 uVar23;
  undefined8 uVar24;
  undefined8 uVar25;
  undefined8 uVar26;
  undefined8 uVar27;
  undefined8 uVar28;
  
  lVar17 = *(long *)(param_2 + 0x40);
  uVar6 = *(uint *)(param_2 + 0x24);
  uVar18 = (ulong)uVar6;
  uVar22 = *(undefined8 *)
            (PTR__ZZN4Aska8Cryption9TChaCha20ILb0EE11ResetStatusEvE8constant_02cc10e8 + 8);
  uVar10 = *(undefined8 *)PTR__ZZN4Aska8Cryption9TChaCha20ILb0EE11ResetStatusEvE8constant_02cc10e8;
  *(undefined4 *)(param_5 + 6) = 0;
  param_5[1] = uVar22;
  *param_5 = uVar10;
  if ((*(char *)((long)param_5 + 0x81) == '\0') || (*(char *)(param_5 + 0x10) == '\0')) {
    uVar10 = 0xfffffffffffffc5b;
  }
  else {
    uVar6 = uVar6 - 0x18;
    uVar20 = (ulong)uVar6;
    uVar19 = 0;
    puVar1 = (uint *)(lVar17 + uVar18);
    lVar16 = lVar17;
    uVar21 = ~uVar20;
    do {
      lVar15 = uVar19 * 0x40;
      uVar2 = lVar15 + ~uVar20;
      uVar12 = uVar21;
      if ((long)uVar21 < -0x40) {
        uVar12 = 0xffffffffffffffbf;
      }
      if ((long)uVar2 < -0x40) {
        uVar2 = 0xffffffffffffffbf;
      }
      Aska::Cryption::TChaCha20<false>::CreateKeyStream()(param_5);
      uVar5 = lVar15 + 0x40;
      if ((long)(uVar20 + uVar19 * -0x40) < 0x41) {
        uVar5 = uVar20;
      }
      if (lVar15 < (long)uVar5) {
        if (uVar2 < 0xffffffffffffffe0) {
          uVar11 = ~uVar2 & 0xffffffffffffffe0;
          if (uVar11 == 0) goto code_r0x01593ef4;
          uVar3 = lVar17 + lVar15 + uVar18;
          puVar13 = (undefined8 *)((lVar17 + (uVar18 - 1) + lVar15) - uVar2);
          uVar8 = 0;
          if (((lVar17 + (uVar19 << 6 | 0x17)) - uVar2 <= uVar3 ||
               puVar13 <= (undefined8 *)(lVar17 + (uVar19 << 6 | 0x18))) &&
             ((long)param_5 + (0x3f - uVar2) <= uVar3 || puVar13 <= param_5 + 8)) {
            uVar12 = ~uVar12 & 0xffffffffffffffe0;
            lVar15 = lVar15 + uVar11;
            puVar13 = param_5 + 10;
            lVar14 = lVar16;
            do {
              uVar22 = *(undefined8 *)(lVar14 + 0x20);
              uVar10 = *(undefined8 *)(lVar14 + 0x18);
              uVar24 = *(undefined8 *)(lVar14 + 0x30);
              uVar23 = *(undefined8 *)(lVar14 + 0x28);
              uVar26 = puVar13[-1];
              uVar25 = puVar13[-2];
              uVar28 = puVar13[1];
              uVar27 = *puVar13;
              puVar4 = (undefined8 *)(lVar14 + uVar18);
              lVar14 = lVar14 + 0x20;
              uVar12 = uVar12 - 0x20;
              puVar13 = puVar13 + 4;
              puVar4[1] = CONCAT17((byte)((ulong)uVar26 >> 0x38) ^ (byte)((ulong)uVar22 >> 0x38),
                                   CONCAT16((byte)((ulong)uVar26 >> 0x30) ^
                                            (byte)((ulong)uVar22 >> 0x30),
                                            CONCAT15((byte)((ulong)uVar26 >> 0x28) ^
                                                     (byte)((ulong)uVar22 >> 0x28),
                                                     CONCAT14((byte)((ulong)uVar26 >> 0x20) ^
                                                              (byte)((ulong)uVar22 >> 0x20),
                                                              CONCAT13((byte)((ulong)uVar26 >> 0x18)
                                                                       ^ (byte)((ulong)uVar22 >>
                                                                               0x18),
                                                                       CONCAT12((byte)((ulong)uVar26
                                                                                      >> 0x10) ^
                                                                                (byte)((ulong)uVar22
                                                                                      >> 0x10),
                                                                                CONCAT11((byte)((
                                                  ulong)uVar26 >> 8) ^ (byte)((ulong)uVar22 >> 8),
                                                  (byte)uVar26 ^ (byte)uVar22)))))));
              *puVar4 = CONCAT17((byte)((ulong)uVar25 >> 0x38) ^ (byte)((ulong)uVar10 >> 0x38),
                                 CONCAT16((byte)((ulong)uVar25 >> 0x30) ^
                                          (byte)((ulong)uVar10 >> 0x30),
                                          CONCAT15((byte)((ulong)uVar25 >> 0x28) ^
                                                   (byte)((ulong)uVar10 >> 0x28),
                                                   CONCAT14((byte)((ulong)uVar25 >> 0x20) ^
                                                            (byte)((ulong)uVar10 >> 0x20),
                                                            CONCAT13((byte)((ulong)uVar25 >> 0x18) ^
                                                                     (byte)((ulong)uVar10 >> 0x18),
                                                                     CONCAT12((byte)((ulong)uVar25
                                                                                    >> 0x10) ^
                                                                              (byte)((ulong)uVar10
                                                                                    >> 0x10),
                                                                              CONCAT11((byte)((ulong
                                                  )uVar25 >> 8) ^ (byte)((ulong)uVar10 >> 8),
                                                  (byte)uVar25 ^ (byte)uVar10)))))));
              puVar4[3] = CONCAT17((byte)((ulong)uVar28 >> 0x38) ^ (byte)((ulong)uVar24 >> 0x38),
                                   CONCAT16((byte)((ulong)uVar28 >> 0x30) ^
                                            (byte)((ulong)uVar24 >> 0x30),
                                            CONCAT15((byte)((ulong)uVar28 >> 0x28) ^
                                                     (byte)((ulong)uVar24 >> 0x28),
                                                     CONCAT14((byte)((ulong)uVar28 >> 0x20) ^
                                                              (byte)((ulong)uVar24 >> 0x20),
                                                              CONCAT13((byte)((ulong)uVar28 >> 0x18)
                                                                       ^ (byte)((ulong)uVar24 >>
                                                                               0x18),
                                                                       CONCAT12((byte)((ulong)uVar28
                                                                                      >> 0x10) ^
                                                                                (byte)((ulong)uVar24
                                                                                      >> 0x10),
                                                                                CONCAT11((byte)((
                                                  ulong)uVar28 >> 8) ^ (byte)((ulong)uVar24 >> 8),
                                                  (byte)uVar28 ^ (byte)uVar24)))))));
              puVar4[2] = CONCAT17((byte)((ulong)uVar27 >> 0x38) ^ (byte)((ulong)uVar23 >> 0x38),
                                   CONCAT16((byte)((ulong)uVar27 >> 0x30) ^
                                            (byte)((ulong)uVar23 >> 0x30),
                                            CONCAT15((byte)((ulong)uVar27 >> 0x28) ^
                                                     (byte)((ulong)uVar23 >> 0x28),
                                                     CONCAT14((byte)((ulong)uVar27 >> 0x20) ^
                                                              (byte)((ulong)uVar23 >> 0x20),
                                                              CONCAT13((byte)((ulong)uVar27 >> 0x18)
                                                                       ^ (byte)((ulong)uVar23 >>
                                                                               0x18),
                                                                       CONCAT12((byte)((ulong)uVar27
                                                                                      >> 0x10) ^
                                                                                (byte)((ulong)uVar23
                                                                                      >> 0x10),
                                                                                CONCAT11((byte)((
                                                  ulong)uVar27 >> 8) ^ (byte)((ulong)uVar23 >> 8),
                                                  (byte)uVar27 ^ (byte)uVar23)))))));
            } while (uVar12 != 0);
            uVar8 = uVar11;
            if (uVar11 == ~uVar2) goto code_r0x01593f20;
          }
        }
        else {
code_r0x01593ef4:
          uVar8 = 0;
        }
        pbVar9 = (byte *)((long)(param_5 + 8) + uVar8);
        do {
          *(byte *)((long)puVar1 + lVar15) = *pbVar9 ^ *(byte *)(lVar17 + lVar15 + 0x18);
          lVar15 = lVar15 + 1;
          pbVar9 = pbVar9 + 1;
        } while (lVar15 < (long)uVar5);
      }
code_r0x01593f20:
      uVar21 = uVar21 + 0x40;
      lVar16 = lVar16 + 0x40;
      bVar7 = uVar19 != uVar6 >> 6;
      uVar19 = uVar19 + 1;
      *(int *)(param_5 + 6) = *(int *)(param_5 + 6) + 1;
    } while (bVar7);
    *param_4 = *puVar1;
    *param_3 = puVar1 + 1;
    uVar10 = 0xfffffffffffffc6b;
    if ((long)puVar1 + (((ulong)*param_4 + 4) - *(long *)(param_2 + 0x40)) <=
        (ulong)*(uint *)(param_2 + 0x20)) {
      uVar10 = 0;
    }
  }
  *param_1 = uVar10;
  return;
}

// ==== undefined Aska::Yayoi::MO::BattleProtocoledData::GetStartBattleStage(void)
// _ZN4Aska5Yayoi2MO20BattleProtocoledData19GetStartBattleStageEv @ 01593fb4

void _ZN4Aska5Yayoi2MO20BattleProtocoledData19GetStartBattleStageEv
               (undefined8 *param_1,long param_2)

{
  undefined8 uVar1;
  
  uVar1 = 0xfffffffffffffc6b;
  if (0x17 < *(uint *)(param_2 + 0x24)) {
    uVar1 = 0;
  }
  *param_1 = uVar1;
  return;
}

// ==== undefined Aska::Yayoi::MO::BattleProtocoledData::GetStartBattleStageRes(unsigned char * &)
// _ZN4Aska5Yayoi2MO20BattleProtocoledData22GetStartBattleStageResERPh @ 01593fcc

void _ZN4Aska5Yayoi2MO20BattleProtocoledData22GetStartBattleStageResERPh
               (undefined8 *param_1,long param_2,long *param_3)

{
  undefined8 uVar1;
  long lVar2;
  
  lVar2 = *(long *)(param_2 + 0x40);
  *param_3 = lVar2 + 0x18;
  uVar1 = 0xfffffffffffffc6b;
  if ((ulong)((lVar2 + 0x1c) - *(long *)(param_2 + 0x40)) <= (ulong)*(uint *)(param_2 + 0x24)) {
    uVar1 = 0;
  }
  *param_1 = uVar1;
  return;
}

// ==== undefined Aska::Yayoi::MO::BattleProtocoledData::GetFinishBattleStage(void)
// _ZN4Aska5Yayoi2MO20BattleProtocoledData20GetFinishBattleStageEv @ 01593ffc

void _ZN4Aska5Yayoi2MO20BattleProtocoledData20GetFinishBattleStageEv
               (undefined8 *param_1,long param_2)

{
  undefined8 uVar1;
  
  uVar1 = 0xfffffffffffffc6b;
  if (0x17 < *(uint *)(param_2 + 0x24)) {
    uVar1 = 0;
  }
  *param_1 = uVar1;
  return;
}

// ==== undefined Aska::Yayoi::MO::BattleProtocoledData::GetFinishBattleStageRes(void)
// _ZN4Aska5Yayoi2MO20BattleProtocoledData23GetFinishBattleStageResEv @ 01594014

void _ZN4Aska5Yayoi2MO20BattleProtocoledData23GetFinishBattleStageResEv
               (undefined8 *param_1,long param_2)

{
  undefined8 uVar1;
  
  uVar1 = 0xfffffffffffffc6b;
  if (0x17 < *(uint *)(param_2 + 0x24)) {
    uVar1 = 0;
  }
  *param_1 = uVar1;
  return;
}

// ==== undefined Aska::Yayoi::MO::BattleProtocoledData::GetForceWinBattleStagePush(void)
// _ZN4Aska5Yayoi2MO20BattleProtocoledData26GetForceWinBattleStagePushEv @ 0159402c

void _ZN4Aska5Yayoi2MO20BattleProtocoledData26GetForceWinBattleStagePushEv
               (undefined8 *param_1,long param_2)

{
  undefined8 uVar1;
  
  uVar1 = 0xfffffffffffffc6b;
  if (0x17 < *(uint *)(param_2 + 0x24)) {
    uVar1 = 0;
  }
  *param_1 = uVar1;
  return;
}

// ==== undefined Aska::Yayoi::MO::BattleProtocoledData::GetStartRushCombo(signed &,signed &,float &)
// _ZN4Aska5Yayoi2MO20BattleProtocoledData17GetStartRushComboERaS3_Rf @ 01594044

void _ZN4Aska5Yayoi2MO20BattleProtocoledData17GetStartRushComboERaS3_Rf
               (undefined8 *param_1,long param_2,byte *param_3,byte *param_4,undefined4 *param_5)

{
  long lVar1;
  undefined8 uVar2;
  
  lVar1 = *(long *)(param_2 + 0x40);
  *param_3 = *(byte *)(lVar1 + 0x18);
  *param_4 = *(byte *)(lVar1 + 0x19);
  *param_5 = *(undefined4 *)(lVar1 + 0x1a);
  if ((ulong)((lVar1 + 0x1e) - *(long *)(param_2 + 0x40)) <= (ulong)*(uint *)(param_2 + 0x24)) {
    uVar2 = 0xfffffffffffffc43;
    if ((*param_3 < 4) && (uVar2 = 0xfffffffffffffc43, *param_4 - 4 < 8)) {
      uVar2 = 0;
    }
    *param_1 = uVar2;
    return;
  }
  *param_1 = 0xfffffffffffffc6b;
  return;
}

// ==== undefined Aska::Yayoi::MO::BattleProtocoledData::GetStartRushComboRes(signed &,signed &)
// _ZN4Aska5Yayoi2MO20BattleProtocoledData20GetStartRushComboResERaS3_ @ 015940ac

void _ZN4Aska5Yayoi2MO20BattleProtocoledData20GetStartRushComboResERaS3_
               (undefined8 *param_1,long param_2,undefined1 *param_3,undefined1 *param_4)

{
  undefined8 uVar1;
  long lVar2;
  
  lVar2 = *(long *)(param_2 + 0x40);
  *param_3 = *(undefined1 *)(lVar2 + 0x18);
  *param_4 = *(undefined1 *)(lVar2 + 0x19);
  uVar1 = 0xfffffffffffffc6b;
  if ((ulong)((lVar2 + 0x1a) - *(long *)(param_2 + 0x40)) <= (ulong)*(uint *)(param_2 + 0x24)) {
    uVar1 = 0;
  }
  *param_1 = uVar1;
  return;
}

// ==== undefined Aska::Yayoi::MO::BattleProtocoledData::GetSyncStartRushCombo(signed &,unsigned char &,float &)
// _ZN4Aska5Yayoi2MO20BattleProtocoledData21GetSyncStartRushComboERaRhRf @ 015940e4

void _ZN4Aska5Yayoi2MO20BattleProtocoledData21GetSyncStartRushComboERaRhRf
               (undefined8 *param_1,long param_2,byte *param_3,undefined1 *param_4,
               undefined4 *param_5)

{
  undefined8 uVar1;
  long lVar2;
  
  lVar2 = *(long *)(param_2 + 0x40);
  *param_3 = *(byte *)(lVar2 + 0x18);
  *param_4 = *(undefined1 *)(lVar2 + 0x19);
  *param_5 = *(undefined4 *)(lVar2 + 0x1a);
  if ((ulong)*(uint *)(param_2 + 0x24) < (ulong)((lVar2 + 0x1e) - *(long *)(param_2 + 0x40))) {
    *param_1 = 0xfffffffffffffc6b;
    return;
  }
  uVar1 = 0xfffffffffffffc43;
  if (*param_3 < 4) {
    uVar1 = 0;
  }
  *param_1 = uVar1;
  return;
}

// ==== undefined Aska::Yayoi::MO::BattleProtocoledData::GetSyncStartRushComboRes(signed &,signed &,unsigned char &,unsigned char &,float &,unsigned int &)
// _ZN4Aska5Yayoi2MO20BattleProtocoledData24GetSyncStartRushComboResERaS3_RhS4_RfRj @ 0159413c

void _ZN4Aska5Yayoi2MO20BattleProtocoledData24GetSyncStartRushComboResERaS3_RhS4_RfRj
               (undefined8 *param_1,long param_2,undefined1 *param_3,undefined1 *param_4,
               undefined1 *param_5,undefined1 *param_6,undefined4 *param_7,undefined4 *param_8)

{
  undefined8 uVar1;
  long lVar2;
  
  lVar2 = *(long *)(param_2 + 0x40);
  *param_3 = *(undefined1 *)(lVar2 + 0x18);
  *param_4 = *(undefined1 *)(lVar2 + 0x19);
  *param_5 = *(undefined1 *)(lVar2 + 0x1a);
  *param_6 = *(undefined1 *)(lVar2 + 0x1b);
  *param_7 = *(undefined4 *)(lVar2 + 0x1c);
  *param_8 = *(undefined4 *)(lVar2 + 0x20);
  uVar1 = 0xfffffffffffffc6b;
  if ((ulong)((lVar2 + 0x24) - *(long *)(param_2 + 0x40)) <= (ulong)*(uint *)(param_2 + 0x24)) {
    uVar1 = 0;
  }
  *param_1 = uVar1;
  return;
}

// ==== undefined Aska::Yayoi::MO::BattleProtocoledData::GetSyncFinishRushCombo(float &,int &)
// _ZN4Aska5Yayoi2MO20BattleProtocoledData22GetSyncFinishRushComboERfRi @ 01594194

void _ZN4Aska5Yayoi2MO20BattleProtocoledData22GetSyncFinishRushComboERfRi
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

// ==== undefined Aska::Yayoi::MO::BattleProtocoledData::GetSyncFinishRushComboRes(float &,int &,unsigned char &)
// _ZN4Aska5Yayoi2MO20BattleProtocoledData25GetSyncFinishRushComboResERfRiRh @ 015941cc

void _ZN4Aska5Yayoi2MO20BattleProtocoledData25GetSyncFinishRushComboResERfRiRh
               (undefined8 *param_1,long param_2,undefined4 *param_3,undefined4 *param_4,
               undefined1 *param_5)

{
  undefined8 uVar1;
  long lVar2;
  
  lVar2 = *(long *)(param_2 + 0x40);
  *param_3 = *(undefined4 *)(lVar2 + 0x18);
  *param_4 = *(undefined4 *)(lVar2 + 0x1c);
  *param_5 = *(undefined1 *)(lVar2 + 0x20);
  uVar1 = 0xfffffffffffffc6b;
  if ((ulong)((lVar2 + 0x21) - *(long *)(param_2 + 0x40)) <= (ulong)*(uint *)(param_2 + 0x24)) {
    uVar1 = 0;
  }
  *param_1 = uVar1;
  return;
}

// ==== undefined Aska::Yayoi::MO::BattleProtocoledData::GetAIParameter(Aska::Yayoi::MO::HateParameter * &,unsigned int &)
// _ZN4Aska5Yayoi2MO20BattleProtocoledData14GetAIParameterERPNS1_13HateParameterERj @ 0159420c

void _ZN4Aska5Yayoi2MO20BattleProtocoledData14GetAIParameterERPNS1_13HateParameterERj
               (undefined8 *param_1,long param_2,long *param_3,uint *param_4)

{
  uint uVar1;
  uint *puVar2;
  long lVar3;
  undefined8 uVar4;
  long lVar5;
  ulong uVar6;
  
  puVar2 = (uint *)(*(long *)(param_2 + 0x40) + 0x1c);
  *param_4 = *(uint *)(*(long *)(param_2 + 0x40) + 0x18);
  *param_3 = (long)puVar2;
  lVar5 = *(long *)(param_2 + 0x40);
  lVar3 = lVar5 + 0x18;
  if (*param_4 != 0) {
    *(ulong *)puVar2 = (ulong)*puVar2 + lVar3;
    if (1 < *param_4) {
      uVar6 = 1;
      do {
        lVar5 = uVar6 * 0x10;
        uVar1 = (int)uVar6 + 1;
        uVar6 = (ulong)uVar1;
        *(ulong *)(*param_3 + lVar5) = (ulong)*(uint *)(*param_3 + lVar5) + lVar3;
      } while (uVar1 < *param_4);
    }
    lVar5 = *(long *)(param_2 + 0x40);
  }
  uVar4 = 0xfffffffffffffc6b;
  if ((ulong)(lVar3 - lVar5) <= (ulong)*(uint *)(param_2 + 0x24)) {
    uVar4 = 0;
  }
  *param_1 = uVar4;
  return;
}

// ==== undefined Aska::Yayoi::MO::BattleProtocoledData::GetAIParameterRes(Aska::Yayoi::MO::HateParameter * &,unsigned int &)
// _ZN4Aska5Yayoi2MO20BattleProtocoledData17GetAIParameterResERPNS1_13HateParameterERj @ 01594294

void _ZN4Aska5Yayoi2MO20BattleProtocoledData17GetAIParameterResERPNS1_13HateParameterERj
               (undefined8 *param_1,long param_2,long *param_3,uint *param_4)

{
  uint uVar1;
  uint *puVar2;
  long lVar3;
  undefined8 uVar4;
  long lVar5;
  ulong uVar6;
  
  puVar2 = (uint *)(*(long *)(param_2 + 0x40) + 0x1c);
  *param_4 = *(uint *)(*(long *)(param_2 + 0x40) + 0x18);
  *param_3 = (long)puVar2;
  lVar5 = *(long *)(param_2 + 0x40);
  lVar3 = lVar5 + 0x18;
  if (*param_4 != 0) {
    *(ulong *)puVar2 = (ulong)*puVar2 + lVar3;
    if (1 < *param_4) {
      uVar6 = 1;
      do {
        lVar5 = uVar6 * 0x10;
        uVar1 = (int)uVar6 + 1;
        uVar6 = (ulong)uVar1;
        *(ulong *)(*param_3 + lVar5) = (ulong)*(uint *)(*param_3 + lVar5) + lVar3;
      } while (uVar1 < *param_4);
    }
    lVar5 = *(long *)(param_2 + 0x40);
  }
  uVar4 = 0xfffffffffffffc6b;
  if ((ulong)(lVar3 - lVar5) <= (ulong)*(uint *)(param_2 + 0x24)) {
    uVar4 = 0;
  }
  *param_1 = uVar4;
  return;
}

// ==== undefined Aska::Yayoi::MO::BattleProtocoledData::GetDebugMessage(unsigned int &)
// _ZN4Aska5Yayoi2MO20BattleProtocoledData15GetDebugMessageERj @ 0159431c

void _ZN4Aska5Yayoi2MO20BattleProtocoledData15GetDebugMessageERj
               (undefined8 *param_1,long param_2,undefined4 *param_3)

{
  undefined8 uVar1;
  long lVar2;
  
  lVar2 = *(long *)(param_2 + 0x40);
  *param_3 = *(undefined4 *)(lVar2 + 0x18);
  uVar1 = 0xfffffffffffffc6b;
  if ((ulong)((lVar2 + 0x1c) - *(long *)(param_2 + 0x40)) <= (ulong)*(uint *)(param_2 + 0x24)) {
    uVar1 = 0;
  }
  *param_1 = uVar1;
  return;
}

// ==== undefined Aska::Yayoi::MO::BattleProtocoledData::GetDebugMessageRes(unsigned int &)
// _ZN4Aska5Yayoi2MO20BattleProtocoledData18GetDebugMessageResERj @ 0159434c

void _ZN4Aska5Yayoi2MO20BattleProtocoledData18GetDebugMessageResERj
               (undefined8 *param_1,long param_2,undefined4 *param_3)

{
  undefined8 uVar1;
  long lVar2;
  
  lVar2 = *(long *)(param_2 + 0x40);
  *param_3 = *(undefined4 *)(lVar2 + 0x18);
  uVar1 = 0xfffffffffffffc6b;
  if ((ulong)((lVar2 + 0x1c) - *(long *)(param_2 + 0x40)) <= (ulong)*(uint *)(param_2 + 0x24)) {
    uVar1 = 0;
  }
  *param_1 = uVar1;
  return;
}

// ==== undefined Aska::Yayoi::MO::BattleProtocoledData::GetRequestProxy(signed * &,unsigned int &,unsigned short &)
// _ZN4Aska5Yayoi2MO20BattleProtocoledData15GetRequestProxyERPaRjRt @ 0159437c

void _ZN4Aska5Yayoi2MO20BattleProtocoledData15GetRequestProxyERPaRjRt
               (undefined8 *param_1,long param_2,long *param_3,uint *param_4,undefined2 *param_5)

{
  undefined8 uVar1;
  uint uVar2;
  long lVar3;
  uint *puVar4;
  
  lVar3 = *(long *)(param_2 + 0x40);
  puVar4 = (uint *)(lVar3 + 0x18);
  *param_4 = *puVar4;
  *param_3 = lVar3 + 0x1c;
  uVar2 = *param_4;
  *param_5 = *(undefined2 *)((long)puVar4 + (ulong)uVar2 + 4);
  uVar1 = 0xfffffffffffffc6b;
  if ((long)puVar4 + (((ulong)uVar2 + 6) - *(long *)(param_2 + 0x40)) <=
      (ulong)*(uint *)(param_2 + 0x24)) {
    uVar1 = 0;
  }
  *param_1 = uVar1;
  return;
}

// ==== undefined Aska::Yayoi::MO::BattleProtocoledData::GetRequestProxyResult(Aska::Status &)
// _ZN4Aska5Yayoi2MO20BattleProtocoledData21GetRequestProxyResultERNS_6StatusE @ 015943c4

void _ZN4Aska5Yayoi2MO20BattleProtocoledData21GetRequestProxyResultERNS_6StatusE
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

// ==== undefined Aska::Yayoi::MO::BattleProtocoledData::GetPacket(Aska::Yayoi::MultiplayRPC::Message * &,unsigned int &,signed * &,unsigned int &)
// _ZN4Aska5Yayoi2MO20BattleProtocoledData9GetPacketERPNS0_12MultiplayRPC7MessageERjRPaS7_ @ 01594414

void _ZN4Aska5Yayoi2MO20BattleProtocoledData9GetPacketERPNS0_12MultiplayRPC7MessageERjRPaS7_
               (undefined8 *param_1,long param_2,long *param_3,uint *param_4,undefined8 *param_5,
               undefined4 *param_6)

{
  undefined4 *puVar1;
  undefined8 uVar2;
  long lVar3;
  uint *puVar4;
  uint uVar5;
  long lVar6;
  ulong uVar7;
  
  lVar3 = *(long *)(param_2 + 0x40);
  puVar4 = (uint *)(lVar3 + 0x18);
  *param_4 = *puVar4;
  *param_3 = lVar3 + 0x1c;
  puVar1 = (undefined4 *)((long)puVar4 + ((ulong)*param_4 << 4 | 4));
  *param_6 = *puVar1;
  *param_5 = puVar1 + 1;
  lVar6 = *(long *)(param_2 + 0x40);
  lVar3 = lVar6 + 0x18;
  if (*param_4 != 0) {
    uVar5 = 0;
    do {
      uVar7 = (ulong)uVar5;
      uVar5 = uVar5 + 1;
      *(ulong *)(*param_3 + uVar7 * 0x10) = (ulong)*(uint *)(*param_3 + uVar7 * 0x10) + lVar3;
    } while (uVar5 < *param_4);
    lVar6 = *(long *)(param_2 + 0x40);
  }
  uVar2 = 0xfffffffffffffc6b;
  if ((ulong)(lVar3 - lVar6) <= (ulong)*(uint *)(param_2 + 0x24)) {
    uVar2 = 0;
  }
  *param_1 = uVar2;
  return;
}

// ==== undefined Aska::Yayoi::MO::BattleProtocoledData::GetPacketRes(Aska::Yayoi::MultiplayRPC::Message * &,unsigned int &,signed * &,unsigned int &)
// _ZN4Aska5Yayoi2MO20BattleProtocoledData12GetPacketResERPNS0_12MultiplayRPC7MessageERjRPaS7_ @ 015944a0

void _ZN4Aska5Yayoi2MO20BattleProtocoledData12GetPacketResERPNS0_12MultiplayRPC7MessageERjRPaS7_
               (undefined8 *param_1,long param_2,long *param_3,uint *param_4,undefined8 *param_5,
               undefined4 *param_6)

{
  undefined4 *puVar1;
  undefined8 uVar2;
  long lVar3;
  uint *puVar4;
  uint uVar5;
  long lVar6;
  ulong uVar7;
  
  lVar3 = *(long *)(param_2 + 0x40);
  puVar4 = (uint *)(lVar3 + 0x18);
  *param_4 = *puVar4;
  *param_3 = lVar3 + 0x1c;
  puVar1 = (undefined4 *)((long)puVar4 + ((ulong)*param_4 << 4 | 4));
  *param_6 = *puVar1;
  *param_5 = puVar1 + 1;
  lVar6 = *(long *)(param_2 + 0x40);
  lVar3 = lVar6 + 0x18;
  if (*param_4 != 0) {
    uVar5 = 0;
    do {
      uVar7 = (ulong)uVar5;
      uVar5 = uVar5 + 1;
      *(ulong *)(*param_3 + uVar7 * 0x10) = (ulong)*(uint *)(*param_3 + uVar7 * 0x10) + lVar3;
    } while (uVar5 < *param_4);
    lVar6 = *(long *)(param_2 + 0x40);
  }
  uVar2 = 0xfffffffffffffc6b;
  if ((ulong)(lVar3 - lVar6) <= (ulong)*(uint *)(param_2 + 0x24)) {
    uVar2 = 0;
  }
  *param_1 = uVar2;
  return;
}

// ==== undefined Aska::Yayoi::MO::BattleProtocoledData::GetSnapshot(signed * &,unsigned int &)
// _ZN4Aska5Yayoi2MO20BattleProtocoledData11GetSnapshotERPaRj @ 0159452c

void _ZN4Aska5Yayoi2MO20BattleProtocoledData11GetSnapshotERPaRj
               (undefined8 *param_1,long param_2,long *param_3,uint *param_4)

{
  char *pcVar1;
  undefined8 uVar2;
  long lVar3;
  uint *puVar4;
  
  lVar3 = *(long *)(param_2 + 0x40);
  puVar4 = (uint *)(lVar3 + 0x18);
  *param_4 = *puVar4;
  pcVar1 = (char *)(lVar3 + 0x1c);
  *param_3 = (long)pcVar1;
  if ((ulong)*(uint *)(param_2 + 0x24) <
      (long)puVar4 + (((ulong)*param_4 + 4) - *(long *)(param_2 + 0x40))) {
    *param_1 = 0xfffffffffffffc6b;
    return;
  }
  uVar2 = 0xfffffffffffffc43;
  if (*pcVar1 != '\0' && *param_4 != 0) {
    uVar2 = 0;
  }
  *param_1 = uVar2;
  return;
}

// ==== undefined Aska::Yayoi::MO::BattleProtocoledData::GetSnapshotRes(signed * &,unsigned int &)
// _ZN4Aska5Yayoi2MO20BattleProtocoledData14GetSnapshotResERPaRj @ 01594588

void _ZN4Aska5Yayoi2MO20BattleProtocoledData14GetSnapshotResERPaRj
               (undefined8 *param_1,long param_2,long *param_3,uint *param_4)

{
  undefined8 uVar1;
  long lVar2;
  uint *puVar3;
  
  lVar2 = *(long *)(param_2 + 0x40);
  puVar3 = (uint *)(lVar2 + 0x18);
  *param_4 = *puVar3;
  *param_3 = lVar2 + 0x1c;
  uVar1 = 0xfffffffffffffc6b;
  if ((long)puVar3 + (((ulong)*param_4 + 4) - *(long *)(param_2 + 0x40)) <=
      (ulong)*(uint *)(param_2 + 0x24)) {
    uVar1 = 0;
  }
  *param_1 = uVar1;
  return;
}

// ==== undefined Aska::Yayoi::MO::BattleProtocoledData::GetMessage(int &,Aska::Yayoi::MultiplayRPC::Message * &,unsigned int &)
// _ZN4Aska5Yayoi2MO20BattleProtocoledData10GetMessageERiRPNS0_12MultiplayRPC7MessageERj @ 015945c8

void _ZN4Aska5Yayoi2MO20BattleProtocoledData10GetMessageERiRPNS0_12MultiplayRPC7MessageERj
               (undefined8 *param_1,long param_2,undefined4 *param_3,long *param_4,uint *param_5)

{
  uint uVar1;
  uint *puVar2;
  undefined8 uVar3;
  long lVar4;
  long lVar5;
  ulong uVar6;
  
  lVar4 = *(long *)(param_2 + 0x40);
  puVar2 = (uint *)(lVar4 + 0x20);
  *param_3 = *(undefined4 *)(lVar4 + 0x18);
  *param_5 = *(uint *)(lVar4 + 0x1c);
  *param_4 = (long)puVar2;
  lVar5 = *(long *)(param_2 + 0x40);
  lVar4 = lVar5 + 0x18;
  if (*param_5 != 0) {
    *(ulong *)puVar2 = (ulong)*puVar2 + lVar4;
    if (1 < *param_5) {
      uVar6 = 1;
      do {
        lVar5 = uVar6 * 0x10;
        uVar1 = (int)uVar6 + 1;
        uVar6 = (ulong)uVar1;
        *(ulong *)(*param_4 + lVar5) = (ulong)*(uint *)(*param_4 + lVar5) + lVar4;
      } while (uVar1 < *param_5);
    }
    lVar5 = *(long *)(param_2 + 0x40);
  }
  uVar3 = 0xfffffffffffffc6b;
  if ((ulong)(lVar4 - lVar5) <= (ulong)*(uint *)(param_2 + 0x24)) {
    uVar3 = 0;
  }
  *param_1 = uVar3;
  return;
}

// ==== undefined Aska::Yayoi::MO::BattleProtocoledData::GetMessageRes(Aska::Yayoi::MultiplayRPC::Message * &,unsigned int &)
// _ZN4Aska5Yayoi2MO20BattleProtocoledData13GetMessageResERPNS0_12MultiplayRPC7MessageERj @ 01594658

void _ZN4Aska5Yayoi2MO20BattleProtocoledData13GetMessageResERPNS0_12MultiplayRPC7MessageERj
               (undefined8 *param_1,long param_2,long *param_3,uint *param_4)

{
  uint uVar1;
  uint *puVar2;
  long lVar3;
  undefined8 uVar4;
  long lVar5;
  ulong uVar6;
  
  puVar2 = (uint *)(*(long *)(param_2 + 0x40) + 0x1c);
  *param_4 = *(uint *)(*(long *)(param_2 + 0x40) + 0x18);
  *param_3 = (long)puVar2;
  lVar5 = *(long *)(param_2 + 0x40);
  lVar3 = lVar5 + 0x18;
  if (*param_4 != 0) {
    *(ulong *)puVar2 = (ulong)*puVar2 + lVar3;
    if (1 < *param_4) {
      uVar6 = 1;
      do {
        lVar5 = uVar6 * 0x10;
        uVar1 = (int)uVar6 + 1;
        uVar6 = (ulong)uVar1;
        *(ulong *)(*param_3 + lVar5) = (ulong)*(uint *)(*param_3 + lVar5) + lVar3;
      } while (uVar1 < *param_4);
    }
    lVar5 = *(long *)(param_2 + 0x40);
  }
  uVar4 = 0xfffffffffffffc6b;
  if ((ulong)(lVar3 - lVar5) <= (ulong)*(uint *)(param_2 + 0x24)) {
    uVar4 = 0;
  }
  *param_1 = uVar4;
  return;
}

// ==== undefined Aska::Yayoi::MO::BattleProtocoledData::GetStartMultiplay(void)
// _ZN4Aska5Yayoi2MO20BattleProtocoledData17GetStartMultiplayEv @ 015946e0

void _ZN4Aska5Yayoi2MO20BattleProtocoledData17GetStartMultiplayEv(undefined8 *param_1,long param_2)

{
  undefined8 uVar1;
  
  uVar1 = 0xfffffffffffffc6b;
  if (0x17 < *(uint *)(param_2 + 0x24)) {
    uVar1 = 0;
  }
  *param_1 = uVar1;
  return;
}

// ==== undefined Aska::Yayoi::MO::BattleProtocoledData::GetStartMultiplayRes(Aska::Yayoi::MultiplayRPC::PlayerDetailInfo * &,unsigned short &)
// _ZN4Aska5Yayoi2MO20BattleProtocoledData20GetStartMultiplayResERPNS0_12MultiplayRPC16PlayerDetailInfoERt @ 015946f8

void _ZN4Aska5Yayoi2MO20BattleProtocoledData20GetStartMultiplayResERPNS0_12MultiplayRPC16PlayerDetailInfoERt
               (undefined8 *param_1,long param_2,long *param_3,undefined2 *param_4)

{
  undefined8 uVar1;
  long lVar2;
  
  lVar2 = *(long *)(param_2 + 0x40);
  *param_3 = lVar2 + 0x18;
  *param_4 = *(undefined2 *)(lVar2 + 0x1218);
  uVar1 = 0xfffffffffffffc6b;
  if ((ulong)((lVar2 + 0x121a) - *(long *)(param_2 + 0x40)) <= (ulong)*(uint *)(param_2 + 0x24)) {
    uVar1 = 0;
  }
  *param_1 = uVar1;
  return;
}

// ==== undefined Aska::Yayoi::MO::BattleProtocoledData::GetUpdatePlayerList(void)
// _ZN4Aska5Yayoi2MO20BattleProtocoledData19GetUpdatePlayerListEv @ 01594734

void _ZN4Aska5Yayoi2MO20BattleProtocoledData19GetUpdatePlayerListEv
               (undefined8 *param_1,long param_2)

{
  undefined8 uVar1;
  
  uVar1 = 0xfffffffffffffc6b;
  if (0x17 < *(uint *)(param_2 + 0x24)) {
    uVar1 = 0;
  }
  *param_1 = uVar1;
  return;
}

// ==== undefined Aska::Yayoi::MO::BattleProtocoledData::GetUpdatePlayerListResult(Aska::Yayoi::MultiplayRPC::PlayerDetailInfo * &,unsigned short &,signed &,unsigned long &)
// _ZN4Aska5Yayoi2MO20BattleProtocoledData25GetUpdatePlayerListResultERPNS0_12MultiplayRPC16PlayerDetailInfoERtRaRm @ 0159474c

void _ZN4Aska5Yayoi2MO20BattleProtocoledData25GetUpdatePlayerListResultERPNS0_12MultiplayRPC16PlayerDetailInfoERtRaRm
               (undefined8 *param_1,long param_2,long *param_3,undefined2 *param_4,
               undefined1 *param_5,undefined8 *param_6)

{
  undefined8 uVar1;
  long lVar2;
  
  lVar2 = *(long *)(param_2 + 0x40);
  *param_3 = lVar2 + 0x18;
  *param_4 = *(undefined2 *)(lVar2 + 0x1218);
  *param_5 = *(undefined1 *)(lVar2 + 0x121a);
  *param_6 = *(undefined8 *)(lVar2 + 0x121b);
  uVar1 = 0xfffffffffffffc6b;
  if ((ulong)((lVar2 + 0x1223) - *(long *)(param_2 + 0x40)) <= (ulong)*(uint *)(param_2 + 0x24)) {
    uVar1 = 0;
  }
  *param_1 = uVar1;
  return;
}

// ==== undefined Aska::Yayoi::MO::BattleProtocoledData::GetEnterRoom(Aska::Yayoi::MultiplayRPC::PlayerDetailInfo * &,int &)
// _ZN4Aska5Yayoi2MO20BattleProtocoledData12GetEnterRoomERPNS0_12MultiplayRPC16PlayerDetailInfoERi @ 015947c4

void _ZN4Aska5Yayoi2MO20BattleProtocoledData12GetEnterRoomERPNS0_12MultiplayRPC16PlayerDetailInfoERi
               (undefined8 *param_1,long param_2,long *param_3,undefined4 *param_4)

{
  undefined8 uVar1;
  long lVar2;
  
  lVar2 = *(long *)(param_2 + 0x40);
  *param_3 = lVar2 + 0x18;
  *param_4 = *(undefined4 *)(lVar2 + 0x498);
  uVar1 = 0xfffffffffffffc6b;
  if ((ulong)((lVar2 + 0x49c) - *(long *)(param_2 + 0x40)) <= (ulong)*(uint *)(param_2 + 0x24)) {
    uVar1 = 0;
  }
  *param_1 = uVar1;
  return;
}

// ==== undefined Aska::Yayoi::MO::BattleProtocoledData::GetEnterRoomResult(int &,Aska::Status &,Aska::Yayoi::MultiplayRPC::PlayerDetailInfo * &,int &)
// _ZN4Aska5Yayoi2MO20BattleProtocoledData18GetEnterRoomResultERiRNS_6StatusERPNS0_12MultiplayRPC16PlayerDetailInfoES3_ @ 015947fc

void _ZN4Aska5Yayoi2MO20BattleProtocoledData18GetEnterRoomResultERiRNS_6StatusERPNS0_12MultiplayRPC16PlayerDetailInfoES3_
               (undefined8 *param_1,long param_2,undefined4 *param_3,undefined8 *param_4,
               long *param_5,undefined4 *param_6)

{
  undefined8 uVar1;
  long lVar2;
  
  lVar2 = *(long *)(param_2 + 0x40);
  *param_3 = *(undefined4 *)(lVar2 + 0x18);
  *param_4 = *(undefined8 *)(lVar2 + 0x1c);
  *param_5 = lVar2 + 0x24;
  *param_6 = *(undefined4 *)(lVar2 + 0x1224);
  uVar1 = 0xfffffffffffffc6b;
  if ((ulong)((lVar2 + 0x1228) - *(long *)(param_2 + 0x40)) <= (ulong)*(uint *)(param_2 + 0x24)) {
    uVar1 = 0;
  }
  *param_1 = uVar1;
  return;
}

// ==== undefined Aska::Yayoi::MO::BattleProtocoledData::GetExitRoom(Aska::Yayoi::MultiplayRPC::ExitType &,int &)
// _ZN4Aska5Yayoi2MO20BattleProtocoledData11GetExitRoomERNS0_12MultiplayRPC8ExitTypeERi @ 01594868

void _ZN4Aska5Yayoi2MO20BattleProtocoledData11GetExitRoomERNS0_12MultiplayRPC8ExitTypeERi
               (undefined8 *param_1,long param_2,uint *param_3,int *param_4)

{
  undefined8 uVar1;
  int iVar2;
  long lVar3;
  
  lVar3 = *(long *)(param_2 + 0x40);
  *param_3 = *(uint *)(lVar3 + 0x18);
  iVar2 = *(int *)(lVar3 + 0x1c);
  *param_4 = iVar2;
  if ((ulong)*(uint *)(param_2 + 0x24) < (ulong)((lVar3 + 0x20) - *(long *)(param_2 + 0x40))) {
    *param_1 = 0xfffffffffffffc6b;
    return;
  }
  uVar1 = 0xfffffffffffffc43;
  if (*param_3 < 3 && iVar2 < 4) {
    uVar1 = 0;
  }
  *param_1 = uVar1;
  return;
}

// ==== undefined Aska::Yayoi::MO::BattleProtocoledData::GetExitRoomRes(Aska::Yayoi::MultiplayRPC::ExitType &)
// _ZN4Aska5Yayoi2MO20BattleProtocoledData14GetExitRoomResERNS0_12MultiplayRPC8ExitTypeE @ 015948bc

void _ZN4Aska5Yayoi2MO20BattleProtocoledData14GetExitRoomResERNS0_12MultiplayRPC8ExitTypeE
               (undefined8 *param_1,long param_2,undefined4 *param_3)

{
  undefined8 uVar1;
  long lVar2;
  
  lVar2 = *(long *)(param_2 + 0x40);
  *param_3 = *(undefined4 *)(lVar2 + 0x18);
  uVar1 = 0xfffffffffffffc6b;
  if ((ulong)((lVar2 + 0x1c) - *(long *)(param_2 + 0x40)) <= (ulong)*(uint *)(param_2 + 0x24)) {
    uVar1 = 0;
  }
  *param_1 = uVar1;
  return;
}

// ==== undefined Aska::Yayoi::MO::BattleProtocoledData::GetExitRoomPush(Aska::Yayoi::MultiplayRPC::ExitType &)
// _ZN4Aska5Yayoi2MO20BattleProtocoledData15GetExitRoomPushERNS0_12MultiplayRPC8ExitTypeE @ 015948ec

void _ZN4Aska5Yayoi2MO20BattleProtocoledData15GetExitRoomPushERNS0_12MultiplayRPC8ExitTypeE
               (undefined8 *param_1,long param_2,undefined4 *param_3)

{
  undefined8 uVar1;
  long lVar2;
  
  lVar2 = *(long *)(param_2 + 0x40);
  *param_3 = *(undefined4 *)(lVar2 + 0x18);
  uVar1 = 0xfffffffffffffc6b;
  if ((ulong)((lVar2 + 0x1c) - *(long *)(param_2 + 0x40)) <= (ulong)*(uint *)(param_2 + 0x24)) {
    uVar1 = 0;
  }
  *param_1 = uVar1;
  return;
}

// ==== undefined Aska::Yayoi::MO::BattleProtocoledData::GetChangePublicRoom(signed &)
// _ZN4Aska5Yayoi2MO20BattleProtocoledData19GetChangePublicRoomERa @ 0159491c

void _ZN4Aska5Yayoi2MO20BattleProtocoledData19GetChangePublicRoomERa
               (undefined8 *param_1,long param_2,undefined1 *param_3)

{
  undefined8 uVar1;
  long lVar2;
  
  lVar2 = *(long *)(param_2 + 0x40);
  *param_3 = *(undefined1 *)(lVar2 + 0x18);
  uVar1 = 0xfffffffffffffc6b;
  if ((ulong)((lVar2 + 0x19) - *(long *)(param_2 + 0x40)) <= (ulong)*(uint *)(param_2 + 0x24)) {
    uVar1 = 0;
  }
  *param_1 = uVar1;
  return;
}

// ==== undefined Aska::Yayoi::MO::BattleProtocoledData::GetChangePublicRoomRes(Aska::Status &)
// _ZN4Aska5Yayoi2MO20BattleProtocoledData22GetChangePublicRoomResERNS_6StatusE @ 0159494c

void _ZN4Aska5Yayoi2MO20BattleProtocoledData22GetChangePublicRoomResERNS_6StatusE
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

// ==== undefined Aska::Yayoi::MO::BattleProtocoledData::GetUpdatePlayerStatus(Aska::Yayoi::MultiplayRPC::PlayerDetailInfo * &,signed &)
// _ZN4Aska5Yayoi2MO20BattleProtocoledData21GetUpdatePlayerStatusERPNS0_12MultiplayRPC16PlayerDetailInfoERa @ 0159499c

void _ZN4Aska5Yayoi2MO20BattleProtocoledData21GetUpdatePlayerStatusERPNS0_12MultiplayRPC16PlayerDetailInfoERa
               (undefined8 *param_1,long param_2,long *param_3,undefined1 *param_4)

{
  undefined8 uVar1;
  long lVar2;
  
  lVar2 = *(long *)(param_2 + 0x40);
  *param_3 = lVar2 + 0x18;
  *param_4 = *(undefined1 *)(lVar2 + 0x498);
  uVar1 = 0xfffffffffffffc6b;
  if ((ulong)((lVar2 + 0x499) - *(long *)(param_2 + 0x40)) <= (ulong)*(uint *)(param_2 + 0x24)) {
    uVar1 = 0;
  }
  *param_1 = uVar1;
  return;
}

// ==== undefined Aska::Yayoi::MO::BattleProtocoledData::GetUpdatePlayerStatusRes(Aska::Status &)
// _ZN4Aska5Yayoi2MO20BattleProtocoledData24GetUpdatePlayerStatusResERNS_6StatusE @ 015949d4

void _ZN4Aska5Yayoi2MO20BattleProtocoledData24GetUpdatePlayerStatusResERNS_6StatusE
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

// ==== undefined Aska::Yayoi::MO::BattleProtocoledData::GetRSSIPush(float * &)
// _ZN4Aska5Yayoi2MO20BattleProtocoledData11GetRSSIPushERPf @ 01594a24

void _ZN4Aska5Yayoi2MO20BattleProtocoledData11GetRSSIPushERPf
               (undefined8 *param_1,long param_2,long *param_3)

{
  undefined8 uVar1;
  long lVar2;
  
  lVar2 = *(long *)(param_2 + 0x40);
  *param_3 = lVar2 + 0x18;
  uVar1 = 0xfffffffffffffc6b;
  if ((ulong)((lVar2 + 0x28) - *(long *)(param_2 + 0x40)) <= (ulong)*(uint *)(param_2 + 0x24)) {
    uVar1 = 0;
  }
  *param_1 = uVar1;
  return;
}

// ==== undefined Aska::Yayoi::MO::BattleProtocoledData::GetDisconnectNodePush(int &,int &)
// _ZN4Aska5Yayoi2MO20BattleProtocoledData21GetDisconnectNodePushERiS3_ @ 01594a54

void _ZN4Aska5Yayoi2MO20BattleProtocoledData21GetDisconnectNodePushERiS3_
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

// ==== undefined Aska::Yayoi::MO::BattleProtocoledData::GetReconnect(int &)
// _ZN4Aska5Yayoi2MO20BattleProtocoledData12GetReconnectERi @ 01594a8c

void _ZN4Aska5Yayoi2MO20BattleProtocoledData12GetReconnectERi
               (undefined8 *param_1,long param_2,int *param_3)

{
  undefined8 uVar1;
  undefined8 uVar2;
  int iVar3;
  long lVar4;
  
  lVar4 = *(long *)(param_2 + 0x40);
  iVar3 = *(int *)(lVar4 + 0x18);
  *param_3 = iVar3;
  uVar1 = 0xfffffffffffffc43;
  if (iVar3 < 4) {
    uVar1 = 0;
  }
  uVar2 = 0xfffffffffffffc6b;
  if ((ulong)((lVar4 + 0x1c) - *(long *)(param_2 + 0x40)) <= (ulong)*(uint *)(param_2 + 0x24)) {
    uVar2 = uVar1;
  }
  *param_1 = uVar2;
  return;
}

// ==== undefined Aska::Yayoi::MO::BattleProtocoledData::SetMissionEnd(signed const *,Aska::Yayoi::MO::DeviceType,signed const *,unsigned int,Aska::Cryption::TChaCha20<false> *)
// _ZN4Aska5Yayoi2MO20BattleProtocoledData13SetMissionEndEPKaNS1_10DeviceTypeES4_jPNS_8Cryption9TChaCha20ILb0EEE @ 0159525c

void _ZN4Aska5Yayoi2MO20BattleProtocoledData13SetMissionEndEPKaNS1_10DeviceTypeES4_jPNS_8Cryption9TChaCha20ILb0EEE
               (long *param_1,long param_2,char *param_3,int param_4,undefined8 param_5,uint param_6
               ,undefined8 *param_7)

{
  uint uVar1;
  ulong uVar2;
  ulong uVar3;
  ulong uVar4;
  ulong uVar5;
  byte bVar6;
  bool bVar7;
  uint uVar8;
  uint uVar9;
  int iVar10;
  long lVar11;
  ulong uVar12;
  byte *pbVar13;
  undefined8 *puVar14;
  long lVar15;
  ulong uVar16;
  ulong uVar17;
  undefined8 *puVar18;
  undefined8 *puVar19;
  long lVar20;
  undefined8 *puVar21;
  ulong uVar22;
  ulong uVar23;
  long lVar24;
  long lVar25;
  ulong uVar26;
  undefined8 *puVar27;
  ulong uVar28;
  undefined8 uVar29;
  undefined8 uVar30;
  byte bVar32;
  byte bVar33;
  byte bVar34;
  byte bVar35;
  byte bVar36;
  byte bVar37;
  undefined8 uVar31;
  undefined8 uVar38;
  undefined8 uVar39;
  undefined8 uVar40;
  undefined8 uVar41;
  undefined8 uVar42;
  long lStack_98;
  undefined8 uStack_90;
  undefined8 uStack_88;
  long lStack_80;
  long lStack_70;
  long lStack_68;
  
  if (((param_3 == (char *)0x0) || (0x62 < param_4 - 1U)) || (*param_3 == '\0')) {
    lStack_98 = -0x3bd;
  }
  else {
    uVar22 = (ulong)param_6;
    if (uVar22 + 0x44 >> 0x20 == 0) {
      uVar1 = param_6 + 0x44;
      uVar28 = (ulong)uVar1;
      uVar23 = uVar22 + 0x44 + uVar28;
      Aska::Yayoi::MO::BattleProtocoledData::AllocateBuffer(int)(&lStack_98,param_2,uVar23 & 0xffffffff);
      if (-1 < lStack_98) {
        lVar11 = *(long *)(param_2 + 0x40);
        uVar2 = uVar22 + 0x2c;
        lVar15 = uVar23 - uVar2;
        puVar14 = (undefined8 *)(lVar11 + lVar15);
        *(undefined4 *)(puVar14 + 4) = *(undefined4 *)(param_3 + 0x20);
        uVar29 = *(undefined8 *)(param_3 + 0x10);
        puVar14[3] = *(undefined8 *)(param_3 + 0x18);
        puVar14[2] = uVar29;
        uVar30 = *(undefined8 *)(param_3 + 8);
        uVar29 = *(undefined8 *)param_3;
        *(int *)((long)puVar14 + 0x24) = param_4;
        *(uint *)(puVar14 + 5) = param_6;
        puVar14[1] = uVar30;
        *puVar14 = uVar29;
        memcpy((long)puVar14 + 0x2c,param_5,uVar22);
        lVar24 = *(long *)(param_2 + 0x40);
        uVar30 = *(undefined8 *)
                  (PTR__ZZN4Aska8Cryption9TChaCha20ILb0EE11ResetStatusEvE8constant_02cc10e8 + 8);
        uVar29 = *(undefined8 *)
                  PTR__ZZN4Aska8Cryption9TChaCha20ILb0EE11ResetStatusEvE8constant_02cc10e8;
        *(undefined4 *)(param_7 + 6) = 0;
        param_7[1] = uVar30;
        *param_7 = uVar29;
        if ((*(char *)((long)param_7 + 0x81) == '\0') || (*(char *)(param_7 + 0x10) == '\0')) {
          lStack_98 = -0x3a5;
        }
        else {
          uVar26 = 0;
          puVar14 = (undefined8 *)(lVar24 + 0x28);
          puVar27 = (undefined8 *)(lVar11 + uVar28 + 0x28);
          uVar23 = -uVar22 - 0x2d;
          do {
            lVar25 = uVar26 * 0x40;
            uVar3 = (-uVar22 - 0x2d) + lVar25;
            uVar17 = uVar23;
            if ((long)uVar23 < -0x40) {
              uVar17 = 0xffffffffffffffbf;
            }
            if ((long)uVar3 < -0x40) {
              uVar3 = 0xffffffffffffffbf;
            }
            Aska::Cryption::TChaCha20<false>::CreateKeyStream()(param_7);
            uVar5 = lVar25 + 0x40;
            if ((long)(uVar2 + uVar26 * -0x40) < 0x41) {
              uVar5 = uVar2;
            }
            if (lVar25 < (long)uVar5) {
              if (uVar3 < 0xffffffffffffffe0) {
                uVar16 = ~uVar3 & 0xffffffffffffffe0;
                if (uVar16 == 0) goto code_r0x015954e0;
                uVar4 = lVar24 + (uVar26 << 6 | 0x18);
                puVar18 = (undefined8 *)((lVar24 + (uVar26 << 6 | 0x17)) - uVar3);
                uVar12 = 0;
                if (((lVar11 + uVar28 + 0x17 + lVar25) - uVar3 <= uVar4 ||
                     puVar18 <= (undefined8 *)(lVar11 + lVar15 + lVar25)) &&
                   ((long)param_7 + (0x3f - uVar3) <= uVar4 || puVar18 <= param_7 + 8)) {
                  uVar17 = ~uVar17 & 0xffffffffffffffe0;
                  lVar25 = lVar25 + uVar16;
                  puVar19 = puVar27;
                  puVar18 = param_7 + 10;
                  puVar21 = puVar14;
                  do {
                    uVar30 = puVar19[-1];
                    uVar29 = puVar19[-2];
                    uVar38 = puVar19[1];
                    uVar31 = *puVar19;
                    uVar40 = puVar18[-1];
                    uVar39 = puVar18[-2];
                    uVar42 = puVar18[1];
                    uVar41 = *puVar18;
                    uVar17 = uVar17 - 0x20;
                    puVar18 = puVar18 + 4;
                    puVar19 = puVar19 + 4;
                    puVar21[-1] = CONCAT17((byte)((ulong)uVar40 >> 0x38) ^
                                           (byte)((ulong)uVar30 >> 0x38),
                                           CONCAT16((byte)((ulong)uVar40 >> 0x30) ^
                                                    (byte)((ulong)uVar30 >> 0x30),
                                                    CONCAT15((byte)((ulong)uVar40 >> 0x28) ^
                                                             (byte)((ulong)uVar30 >> 0x28),
                                                             CONCAT14((byte)((ulong)uVar40 >> 0x20)
                                                                      ^ (byte)((ulong)uVar30 >> 0x20
                                                                              ),
                                                                      CONCAT13((byte)((ulong)uVar40
                                                                                     >> 0x18) ^
                                                                               (byte)((ulong)uVar30
                                                                                     >> 0x18),
                                                                               CONCAT12((byte)((
                                                  ulong)uVar40 >> 0x10) ^
                                                  (byte)((ulong)uVar30 >> 0x10),
                                                  CONCAT11((byte)((ulong)uVar40 >> 8) ^
                                                           (byte)((ulong)uVar30 >> 8),
                                                           (byte)uVar40 ^ (byte)uVar30)))))));
                    puVar21[-2] = CONCAT17((byte)((ulong)uVar39 >> 0x38) ^
                                           (byte)((ulong)uVar29 >> 0x38),
                                           CONCAT16((byte)((ulong)uVar39 >> 0x30) ^
                                                    (byte)((ulong)uVar29 >> 0x30),
                                                    CONCAT15((byte)((ulong)uVar39 >> 0x28) ^
                                                             (byte)((ulong)uVar29 >> 0x28),
                                                             CONCAT14((byte)((ulong)uVar39 >> 0x20)
                                                                      ^ (byte)((ulong)uVar29 >> 0x20
                                                                              ),
                                                                      CONCAT13((byte)((ulong)uVar39
                                                                                     >> 0x18) ^
                                                                               (byte)((ulong)uVar29
                                                                                     >> 0x18),
                                                                               CONCAT12((byte)((
                                                  ulong)uVar39 >> 0x10) ^
                                                  (byte)((ulong)uVar29 >> 0x10),
                                                  CONCAT11((byte)((ulong)uVar39 >> 8) ^
                                                           (byte)((ulong)uVar29 >> 8),
                                                           (byte)uVar39 ^ (byte)uVar29)))))));
                    puVar21[1] = CONCAT17((byte)((ulong)uVar42 >> 0x38) ^
                                          (byte)((ulong)uVar38 >> 0x38),
                                          CONCAT16((byte)((ulong)uVar42 >> 0x30) ^
                                                   (byte)((ulong)uVar38 >> 0x30),
                                                   CONCAT15((byte)((ulong)uVar42 >> 0x28) ^
                                                            (byte)((ulong)uVar38 >> 0x28),
                                                            CONCAT14((byte)((ulong)uVar42 >> 0x20) ^
                                                                     (byte)((ulong)uVar38 >> 0x20),
                                                                     CONCAT13((byte)((ulong)uVar42
                                                                                    >> 0x18) ^
                                                                              (byte)((ulong)uVar38
                                                                                    >> 0x18),
                                                                              CONCAT12((byte)((ulong
                                                  )uVar42 >> 0x10) ^ (byte)((ulong)uVar38 >> 0x10),
                                                  CONCAT11((byte)((ulong)uVar42 >> 8) ^
                                                           (byte)((ulong)uVar38 >> 8),
                                                           (byte)uVar42 ^ (byte)uVar38)))))));
                    *puVar21 = CONCAT17((byte)((ulong)uVar41 >> 0x38) ^
                                        (byte)((ulong)uVar31 >> 0x38),
                                        CONCAT16((byte)((ulong)uVar41 >> 0x30) ^
                                                 (byte)((ulong)uVar31 >> 0x30),
                                                 CONCAT15((byte)((ulong)uVar41 >> 0x28) ^
                                                          (byte)((ulong)uVar31 >> 0x28),
                                                          CONCAT14((byte)((ulong)uVar41 >> 0x20) ^
                                                                   (byte)((ulong)uVar31 >> 0x20),
                                                                   CONCAT13((byte)((ulong)uVar41 >>
                                                                                  0x18) ^
                                                                            (byte)((ulong)uVar31 >>
                                                                                  0x18),
                                                                            CONCAT12((byte)((ulong)
                                                  uVar41 >> 0x10) ^ (byte)((ulong)uVar31 >> 0x10),
                                                  CONCAT11((byte)((ulong)uVar41 >> 8) ^
                                                           (byte)((ulong)uVar31 >> 8),
                                                           (byte)uVar41 ^ (byte)uVar31)))))));
                    puVar21 = puVar21 + 4;
                  } while (uVar17 != 0);
                  uVar12 = uVar16;
                  if (uVar16 == ~uVar3) goto code_r0x01595514;
                }
              }
              else {
code_r0x015954e0:
                uVar12 = 0;
              }
              pbVar13 = (byte *)((long)(param_7 + 8) + uVar12);
              lVar25 = lVar25 + 0x18;
              do {
                lVar20 = lVar25 + -0x17;
                *(byte *)(lVar24 + lVar25) = *pbVar13 ^ *(byte *)(lVar11 + uVar28 + lVar25);
                pbVar13 = pbVar13 + 1;
                lVar25 = lVar25 + 1;
              } while (lVar20 < (long)uVar5);
            }
code_r0x01595514:
            uVar23 = uVar23 + 0x40;
            puVar14 = puVar14 + 8;
            bVar7 = uVar26 != uVar2 >> 6;
            uVar26 = uVar26 + 1;
            puVar27 = puVar27 + 8;
            *(int *)(param_7 + 6) = *(int *)(param_7 + 6) + 1;
          } while (bVar7);
          *(undefined4 *)(param_2 + 0x30) = 0x8312a64c;
          uStack_90 = CONCAT44(0x8312a64c,uVar1);
          *(undefined1 *)(param_2 + 0x38) = 0x80;
          uStack_88 = (ulong)CONCAT14(0x80,*(undefined4 *)(param_2 + 0x34));
          clock_gettime(1,&lStack_70);
          lStack_68 = lStack_68 + lStack_70 * 1000000000;
          iVar10 = 0xf;
          bVar6 = (byte)((ulong)lStack_68 >> 0x38);
          bVar32 = (byte)((ulong)lStack_68 >> 8);
          bVar33 = (byte)((ulong)lStack_68 >> 0x10);
          bVar34 = (byte)((ulong)lStack_68 >> 0x18);
          bVar35 = (byte)((ulong)lStack_68 >> 0x20);
          bVar36 = (byte)((ulong)lStack_68 >> 0x28);
          bVar37 = (byte)((ulong)lStack_68 >> 0x30);
          uStack_88 = CONCAT17((byte)(uStack_88 >> 0x38) ^ bVar6,
                               CONCAT16((byte)(uStack_88 >> 0x30) ^ bVar37,
                                        CONCAT15((byte)(uStack_88 >> 0x28) ^ bVar36,
                                                 CONCAT14((byte)(uStack_88 >> 0x20) ^ bVar35,
                                                          CONCAT13((byte)(uStack_88 >> 0x18) ^
                                                                   bVar34,CONCAT12((byte)(uStack_88
                                                                                         >> 0x10) ^
                                                                                   bVar33,CONCAT11((
                                                  byte)(uStack_88 >> 8) ^ bVar32,
                                                  (byte)uStack_88 ^ (byte)lStack_68)))))));
          uStack_90 = CONCAT17((byte)((ulong)uStack_90 >> 0x38) ^ bVar6,
                               CONCAT16((byte)((ulong)uStack_90 >> 0x30) ^ bVar37,
                                        CONCAT15((byte)((ulong)uStack_90 >> 0x28) ^ bVar36,
                                                 CONCAT14((byte)((ulong)uStack_90 >> 0x20) ^ bVar35,
                                                          CONCAT13((byte)((ulong)uStack_90 >> 0x18)
                                                                   ^ bVar34,CONCAT12((byte)((ulong)
                                                  uStack_90 >> 0x10) ^ bVar33,
                                                  CONCAT11((byte)((ulong)uStack_90 >> 8) ^ bVar32,
                                                           (byte)uStack_90 ^ (byte)lStack_68)))))));
          uVar22 = 0x17;
          lStack_80 = lStack_68;
          do {
            uVar8 = (uint)((ulong)lStack_68 >> 0x20);
            uVar9 = (uint)bVar6;
            switch(uVar22 & 0xffffffff) {
            case 0:
              uVar9 = (uint)(ushort)((ulong)lStack_68 >> 0x30);
              break;
            case 1:
              uVar9 = uVar8;
              break;
            case 2:
              uVar9 = (uint)((ulong)lStack_68 >> 0x18);
              break;
            case 3:
              uVar9 = (uint)lStack_68;
              break;
            case 4:
              break;
            case 5:
              uVar9 = (uint)((ulong)lStack_68 >> 8);
              break;
            case 6:
              uVar9 = (uint)((ulong)lStack_68 >> 0x10);
              break;
            case 7:
              uVar9 = uVar8 >> 8;
              break;
            default:
              lVar11 = (long)iVar10;
              iVar10 = iVar10 + -1;
              uVar9 = (uint)*(byte *)((long)&uStack_90 + lVar11);
            }
            *(char *)((long)&uStack_90 + uVar22) = (char)uVar9;
            bVar7 = 0 < (long)uVar22;
            uVar22 = uVar22 - 1;
          } while (bVar7);
          puVar14 = *(undefined8 **)(param_2 + 0x40);
          lStack_98 = 0;
          puVar14[2] = lStack_80;
          puVar14[1] = uStack_88;
          *puVar14 = uStack_90;
          *(uint *)(param_2 + 0x24) = uVar1;
        }
      }
    }
    else {
      lStack_98 = -999;
    }
  }
  *param_1 = lStack_98;
  return;
}

// ==== undefined Aska::Yayoi::MO::BattleProtocoledData::SetMessage(int,Aska::Yayoi::MultiplayRPC::Message const *,unsigned int)
// _ZN4Aska5Yayoi2MO20BattleProtocoledData10SetMessageEiPKNS0_12MultiplayRPC7MessageEj @ 01598b98

void _ZN4Aska5Yayoi2MO20BattleProtocoledData10SetMessageEiPKNS0_12MultiplayRPC7MessageEj
               (long *param_1,long param_2,undefined4 param_3,long param_4,uint param_5)

{
  bool bVar1;
  ulong uVar2;
  ulong uVar3;
  undefined8 *puVar4;
  byte bVar5;
  int *piVar6;
  int *piVar7;
  uint uVar8;
  uint uVar9;
  long lVar10;
  long lVar11;
  undefined8 *puVar12;
  int *piVar13;
  int *piVar14;
  ulong uVar15;
  int iVar16;
  ulong uVar17;
  undefined8 uVar18;
  long lVar19;
  byte bVar21;
  byte bVar22;
  byte bVar23;
  byte bVar24;
  byte bVar25;
  byte bVar26;
  long lVar20;
  long lVar27;
  int iVar28;
  long lStack_98;
  undefined8 uStack_90;
  ulong uStack_88;
  long lStack_80;
  long lStack_70;
  long lStack_68;
  
  uVar17 = (ulong)param_5;
  uVar2 = uVar17 << 4 | 8;
  if (param_5 == 0) {
    uVar15 = 8;
  }
  else {
    uVar15 = uVar2;
    if (param_5 < 4) {
      lVar10 = 0;
    }
    else {
      uVar3 = 4;
      if ((param_5 & 3) != 0) {
        uVar3 = (ulong)(param_5 & 3);
      }
      lVar10 = uVar17 - uVar3;
      if (lVar10 != 0) {
        lVar19 = 0;
        piVar13 = (int *)(param_4 + 0x28);
        lVar20 = 0;
        lVar27 = 0;
        lVar11 = lVar10;
        do {
          piVar14 = piVar13 + -8;
          iVar28 = *piVar13;
          piVar6 = piVar13 + 4;
          piVar7 = piVar13 + -4;
          lVar11 = lVar11 + -4;
          piVar13 = piVar13 + 0x10;
          lVar20 = ((long)iVar28 + 3U & 0xfffffffffffffffc) + lVar20;
          lVar27 = ((long)*piVar6 + 3U & 0xfffffffffffffffc) + lVar27;
          uVar15 = ((long)*piVar14 + 3U & 0xfffffffffffffffc) + uVar15;
          lVar19 = ((long)*piVar7 + 3U & 0xfffffffffffffffc) + lVar19;
        } while (lVar11 != 0);
        uVar15 = lVar20 + uVar15 + lVar27 + lVar19;
        if (uVar3 == 0) goto code_r0x01598c9c;
      }
    }
    lVar11 = uVar17 - lVar10;
    piVar13 = (int *)(param_4 + lVar10 * 0x10 + 8);
    do {
      lVar11 = lVar11 + -1;
      uVar15 = ((long)*piVar13 + 3U & 0xfffffffffffffffc) + uVar15;
      piVar13 = piVar13 + 4;
    } while (lVar11 != 0);
  }
code_r0x01598c9c:
  uVar15 = uVar15 + 0x18;
  if (uVar15 >> 0x20 == 0) {
    Aska::Yayoi::MO::BattleProtocoledData::AllocateBuffer(int)(&lStack_98,param_2,uVar15 & 0xffffffff);
    if (-1 < lStack_98) {
      *(undefined4 *)(param_2 + 0x30) = 0xc1f33acc;
      uStack_90 = CONCAT44(0xc1f33acc,(int)uVar15);
      *(undefined1 *)(param_2 + 0x38) = 0;
      uStack_88 = (ulong)*(uint *)(param_2 + 0x34);
      clock_gettime(1,&lStack_70);
      lStack_68 = lStack_68 + lStack_70 * 1000000000;
      iVar28 = 0xf;
      bVar5 = (byte)((ulong)lStack_68 >> 0x38);
      bVar21 = (byte)((ulong)lStack_68 >> 8);
      bVar22 = (byte)((ulong)lStack_68 >> 0x10);
      bVar23 = (byte)((ulong)lStack_68 >> 0x18);
      bVar24 = (byte)((ulong)lStack_68 >> 0x20);
      bVar25 = (byte)((ulong)lStack_68 >> 0x28);
      bVar26 = (byte)((ulong)lStack_68 >> 0x30);
      uStack_88 = CONCAT17((byte)(uStack_88 >> 0x38) ^ bVar5,
                           CONCAT16((byte)(uStack_88 >> 0x30) ^ bVar26,
                                    CONCAT15((byte)(uStack_88 >> 0x28) ^ bVar25,
                                             CONCAT14((byte)(uStack_88 >> 0x20) ^ bVar24,
                                                      CONCAT13((byte)(uStack_88 >> 0x18) ^ bVar23,
                                                               CONCAT12((byte)(uStack_88 >> 0x10) ^
                                                                        bVar22,CONCAT11((byte)(
                                                  uStack_88 >> 8) ^ bVar21,
                                                  (byte)uStack_88 ^ (byte)lStack_68)))))));
      uStack_90 = CONCAT17((byte)((ulong)uStack_90 >> 0x38) ^ bVar5,
                           CONCAT16((byte)((ulong)uStack_90 >> 0x30) ^ bVar26,
                                    CONCAT15((byte)((ulong)uStack_90 >> 0x28) ^ bVar25,
                                             CONCAT14((byte)((ulong)uStack_90 >> 0x20) ^ bVar24,
                                                      CONCAT13((byte)((ulong)uStack_90 >> 0x18) ^
                                                               bVar23,CONCAT12((byte)((ulong)
                                                  uStack_90 >> 0x10) ^ bVar22,
                                                  CONCAT11((byte)((ulong)uStack_90 >> 8) ^ bVar21,
                                                           (byte)uStack_90 ^ (byte)lStack_68)))))));
      uVar15 = 0x17;
      lStack_80 = lStack_68;
      do {
        uVar8 = (uint)((ulong)lStack_68 >> 0x20);
        uVar9 = (uint)bVar5;
        switch(uVar15 & 0xffffffff) {
        case 0:
          uVar9 = (uint)(ushort)((ulong)lStack_68 >> 0x30);
          break;
        case 1:
          uVar9 = uVar8;
          break;
        case 2:
          uVar9 = (uint)((ulong)lStack_68 >> 0x18);
          break;
        case 3:
          uVar9 = (uint)lStack_68;
          break;
        case 4:
          break;
        case 5:
          uVar9 = (uint)((ulong)lStack_68 >> 8);
          break;
        case 6:
          uVar9 = (uint)((ulong)lStack_68 >> 0x10);
          break;
        case 7:
          uVar9 = uVar8 >> 8;
          break;
        default:
          lVar10 = (long)iVar28;
          iVar28 = iVar28 + -1;
          uVar9 = (uint)*(byte *)((long)&uStack_90 + lVar10);
        }
        *(char *)((long)&uStack_90 + uVar15) = (char)uVar9;
        bVar1 = 0 < (long)uVar15;
        uVar15 = uVar15 - 1;
      } while (bVar1);
      puVar12 = *(undefined8 **)(param_2 + 0x40);
      puVar12[2] = lStack_80;
      puVar12[1] = uStack_88;
      *puVar12 = uStack_90;
      lVar10 = *(long *)(param_2 + 0x40);
      *(undefined4 *)(lVar10 + 0x18) = param_3;
      *(uint *)(lVar10 + 0x1c) = param_5;
      if (param_5 == 0) {
        iVar16 = 0;
        iVar28 = 0x20;
      }
      else {
        lVar11 = 0;
        iVar16 = 0;
        do {
          puVar12 = (undefined8 *)(param_4 + lVar11);
          uVar18 = *puVar12;
          uVar15 = (ulong)((int)lVar11 + 0x20);
          puVar4 = (undefined8 *)(lVar10 + uVar15);
          puVar4[1] = puVar12[1];
          *puVar4 = uVar18;
          memcpy(lVar10 + uVar2 + 0x18 + (long)iVar16,*puVar12,(long)*(int *)(puVar12 + 1))
          ;
          *(ulong *)(lVar10 + uVar15) = uVar2 + (long)iVar16;
          uVar17 = uVar17 - 1;
          lVar11 = lVar11 + 0x10;
          iVar16 = (*(int *)(puVar12 + 1) + 3U & 0xfffffffc) + iVar16;
        } while (uVar17 != 0);
        iVar28 = param_5 * 0x10 + 0x20;
      }
      lStack_98 = 0;
      *(int *)(param_2 + 0x24) = iVar28 + iVar16;
    }
  }
  else {
    lStack_98 = -999;
  }
  *param_1 = lStack_98;
  return;
}

// ==== undefined Aska::Yayoi::MO::BattleProtocoledData::SetStartMultiplayRes(Aska::Yayoi::MultiplayRPC::PlayerDetailInfo const *,unsigned short)
// _ZN4Aska5Yayoi2MO20BattleProtocoledData20SetStartMultiplayResEPKNS0_12MultiplayRPC16PlayerDetailInfoEt @ 01599338

void _ZN4Aska5Yayoi2MO20BattleProtocoledData20SetStartMultiplayResEPKNS0_12MultiplayRPC16PlayerDetailInfoEt
               (undefined8 *param_1,long param_2,undefined8 param_3,undefined2 param_4)

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
    lVar3 = Aska::MemoryManager::Malloc(unsigned long)(lVar3,0x121a);
    *(long *)(param_2 + 0x40) = lVar3;
joined_r0x01599504:
    if (lVar3 == 0) {
      *(undefined4 *)(param_2 + 0x20) = 0;
      uVar8 = 0xfffffffffffffc41;
      goto code_r0x01599510;
    }
    *(undefined4 *)(param_2 + 0x20) = 0x121a;
  }
  else if (*(uint *)(param_2 + 0x20) >> 1 < 0x90d) {
    operator delete[](void*)();
    lVar3 = **(long **)PTR__ZN4Aska6Global19m_pNetworkAllocatorE_02cbc200;
    if (lVar3 == 0) {
      lVar3 = Aska::Global::GetAvailableMemoryManager()();
    }
    lVar3 = Aska::MemoryManager::Malloc(unsigned long)(lVar3,0x121a);
    *(long *)(param_2 + 0x40) = lVar3;
    goto joined_r0x01599504;
  }
  uStack_60 = 0x948b07160000121a;
  *(undefined4 *)(param_2 + 0x30) = 0x948b0716;
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
  memcpy(lVar3 + 0x18,param_3,0x1200);
  uVar8 = 0;
  *(undefined2 *)(lVar3 + 0x1218) = param_4;
  *(undefined4 *)(param_2 + 0x24) = 0x121a;
code_r0x01599510:
  *param_1 = uVar8;
  return;
}

// ==== undefined Aska::Yayoi::MO::BattleProtocoledData::SetEnterRoom(Aska::Yayoi::MultiplayRPC::PlayerDetailInfo const &,int)
// _ZN4Aska5Yayoi2MO20BattleProtocoledData12SetEnterRoomERKNS0_12MultiplayRPC16PlayerDetailInfoEi @ 015998fc

void _ZN4Aska5Yayoi2MO20BattleProtocoledData12SetEnterRoomERKNS0_12MultiplayRPC16PlayerDetailInfoEi
               (undefined8 *param_1,long param_2,undefined8 param_3,undefined4 param_4)

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
    lVar3 = Aska::MemoryManager::Malloc(unsigned long)(lVar3,0x49c);
    *(long *)(param_2 + 0x40) = lVar3;
joined_r0x01599ac4:
    if (lVar3 == 0) {
      *(undefined4 *)(param_2 + 0x20) = 0;
      uVar8 = 0xfffffffffffffc41;
      goto code_r0x01599ad0;
    }
    *(undefined4 *)(param_2 + 0x20) = 0x49c;
  }
  else if (*(uint *)(param_2 + 0x20) < 0x49c) {
    operator delete[](void*)();
    lVar3 = **(long **)PTR__ZN4Aska6Global19m_pNetworkAllocatorE_02cbc200;
    if (lVar3 == 0) {
      lVar3 = Aska::Global::GetAvailableMemoryManager()();
    }
    lVar3 = Aska::MemoryManager::Malloc(unsigned long)(lVar3,0x49c);
    *(long *)(param_2 + 0x40) = lVar3;
    goto joined_r0x01599ac4;
  }
  uStack_60 = 0x43610d780000049c;
  *(undefined4 *)(param_2 + 0x30) = 0x43610d78;
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
  memcpy(lVar3 + 0x18,param_3,0x480);
  uVar8 = 0;
  *(undefined4 *)(lVar3 + 0x498) = param_4;
  *(undefined4 *)(param_2 + 0x24) = 0x49c;
code_r0x01599ad0:
  *param_1 = uVar8;
  return;
}

