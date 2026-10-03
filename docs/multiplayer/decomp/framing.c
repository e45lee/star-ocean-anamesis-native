// framing: Ghidra decompiles of work/libSOA-3.7.0.so (3.7.0), extracted by extract.py.
// Data, not code: see README.md and docs/multiplayer.md for what they show.

// ==== undefined Aska::Yayoi::GameRPC::GameProtocol::Serialize(Aska::Yayoi::GameRPC::GameProtocoledData *,signed * *,unsigned long,void const *,unsigned long,unsigned long *)
// _ZN4Aska5Yayoi7GameRPC12GameProtocol9SerializeEPNS1_18GameProtocoledDataEPPamPKvmPm @ 0150d248

void _ZN4Aska5Yayoi7GameRPC12GameProtocol9SerializeEPNS1_18GameProtocoledDataEPPamPKvmPm
               (long *param_1,undefined8 param_2,long param_3,long *param_4,ulong param_5,
               undefined8 param_6,long param_7,long *param_8)

{
  undefined *puVar1;
  int iVar2;
  char cVar3;
  bool bVar4;
  ulong uVar5;
  undefined *puStack_90;
  long lStack_88;
  int *piStack_80;
  long lStack_78;
  int *piStack_70;
  undefined8 uStack_68;
  long lStack_38;
  
  if (param_7 != 0) {
    *param_1 = -0x3b5;
    return;
  }
  uVar5 = (ulong)*(uint *)(param_3 + 0x24);
  if (param_5 < uVar5) {
    *param_1 = -0x3eb;
    return;
  }
  memcpy(*param_4,*(undefined8 *)(param_3 + 0x40),uVar5);
  puVar1 = PTR__ZTVN4Aska12StaticStreamE_02cba478 + 0x10;
  uStack_68 = 0;
  piStack_70 = (int *)0x0;
  lStack_78 = 0;
  piStack_80 = (int *)0x0;
  lStack_88 = 0;
  puStack_90 = puVar1;
  Aska::StaticStream::Open(signed char const*, unsigned long)(&puStack_90,*param_4,uVar5);
  Aska::Hash::SHA1(Aska::IStream*, unsigned long, char*, unsigned long)(&lStack_38,&puStack_90,uVar5,*param_4 + uVar5,param_5 - uVar5);
  if (-1 < lStack_38) {
    lStack_38 = 0;
    *param_8 = uVar5 + 0x14;
  }
  *param_1 = lStack_38;
  if (piStack_70 != (int *)0x0) {
    do {
      iVar2 = *piStack_70;
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piStack_70,0x10);
      if (bVar4) {
        *piStack_70 = iVar2 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
    puStack_90 = puVar1;
    if (iVar2 + -1 != 0) goto code_r0x0150d340;
  }
  puStack_90 = puVar1;
  if (lStack_78 != 0) {
    operator delete[](void*)();
  }
  if (piStack_70 != (int *)0x0) {
    Aska::TSharedPointerCode::DeleteCounter(int*)();
  }
code_r0x0150d340:
  lStack_78 = 0;
  piStack_70 = (int *)0x0;
  if (piStack_80 != (int *)0x0) {
    do {
      iVar2 = *piStack_80;
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piStack_80,0x10);
      if (bVar4) {
        *piStack_80 = iVar2 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
    if (iVar2 + -1 != 0) {
      return;
    }
  }
  if (lStack_88 != 0) {
    operator delete[](void*)();
  }
  if (piStack_80 != (int *)0x0) {
    Aska::TSharedPointerCode::DeleteCounter(int*)();
  }
  return;
}

// ==== undefined Aska::Yayoi::GameRPC::GameProtocol::Deserialize(signed const *,unsigned long,unsigned long *,Aska::Yayoi::GameRPC::GameProtocoledData *,Aska::Status &)
// _ZN4Aska5Yayoi7GameRPC12GameProtocol11DeserializeEPKamPmPNS1_18GameProtocoledDataERNS_6StatusE @ 0150d394

undefined8
_ZN4Aska5Yayoi7GameRPC12GameProtocol11DeserializeEPKamPmPNS1_18GameProtocoledDataERNS_6StatusE
          (long param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5,
          long *param_6)

{
  long lStack_28;
  
  Aska::Yayoi::GameRPC::GameProtocoledData::Deserialize(signed char const*, unsigned long*, unsigned long)(&lStack_28,param_5,param_2,param_4,param_3);
  *param_6 = lStack_28;
  if (lStack_28 < 0) {
    param_5 = 0;
    *(undefined8 *)(param_1 + 0x448) = *(undefined8 *)(param_1 + 0x450);
  }
  else {
    *(undefined8 *)(param_1 + 0x450) = *(undefined8 *)(param_1 + 0x448);
  }
  return param_5;
}

// ==== undefined Aska::Yayoi::GameRPC::GameProtocoledData::Deserialize(signed const *,unsigned long *,unsigned long)
// _ZN4Aska5Yayoi7GameRPC18GameProtocoledData11DeserializeEPKaPmm @ 0150d3fc

void _ZN4Aska5Yayoi7GameRPC18GameProtocoledData11DeserializeEPKaPmm
               (long *param_1,long param_2,long param_3,ulong *param_4,ulong param_5)

{
  undefined *puVar1;
  uint uVar2;
  uint uVar3;
  char cVar4;
  bool bVar5;
  undefined *puVar6;
  int iVar7;
  ulong uVar8;
  undefined8 *puVar9;
  ulong uVar10;
  ulong uVar11;
  uint *puVar12;
  uint *puVar13;
  long *plVar14;
  undefined8 uVar15;
  undefined1 auStack_c4 [20];
  undefined *puStack_b0;
  long lStack_a8;
  int *piStack_a0;
  long lStack_98;
  int *piStack_90;
  undefined8 uStack_88;
  long lStack_58;
  
  *param_4 = 0;
  if (*(char *)(param_2 + 0x60) == '\0') {
    uVar3 = *(uint *)(param_2 + 0x1c);
    uVar2 = (uint)param_5;
    if (0x18 - uVar3 <= param_5) {
      uVar2 = 0x18 - uVar3;
    }
    uVar11 = (ulong)uVar2;
    memcpy(param_2 + 0x48 + (ulong)uVar3,param_3,uVar11);
    uVar2 = uVar2 + uVar3;
    *(uint *)(param_2 + 0x1c) = uVar2;
    *(bool *)(param_2 + 0x60) = uVar2 == 0x18;
    if (uVar2 != 0x18) {
      *param_4 = param_5;
      goto code_r0x0150faac;
    }
    uVar10 = (ulong)*(byte *)(param_2 + 0x4c) << 0x38 | (ulong)*(byte *)(param_2 + 0x48) << 0x30 |
             (ulong)*(byte *)(param_2 + 0x4f) << 0x28 | (ulong)*(byte *)(param_2 + 0x49) << 0x20 |
             (ulong)*(byte *)(param_2 + 0x4a) << 0x18 | (ulong)*(byte *)(param_2 + 0x4e) << 0x10 |
             (ulong)*(byte *)(param_2 + 0x4b) | (ulong)*(byte *)(param_2 + 0x4d) << 8;
    uVar8 = *(ulong *)(param_2 + 0x50) ^ uVar10;
    uVar10 = *(uint5 *)(param_2 + 0x58) ^ uVar10;
    iVar7 = (int)uVar8;
    uVar2 = iVar7 + 0x14;
    *(uint *)(param_2 + 0x24) = uVar2;
    *(int *)(param_2 + 0x30) = (int)(uVar8 >> 0x20);
    *(int *)(param_2 + 0x34) = (int)uVar10;
    *(char *)(param_2 + 0x38) = (char)(uVar10 >> 0x20);
    if (uVar2 < 0x18) goto code_r0x0150d5f4;
    if ((long)(uVar10 << 0x18) < 0) {
      uVar2 = iVar7 + (iVar7 + 0x94U & 0xffffff80 | 0x20) + 0x34;
    }
    Aska::Yayoi::GameRPC::GameProtocoledData::AllocateBuffer(int)(&puStack_b0,param_2,uVar2);
    if ((long)puStack_b0 < 0) {
      *param_1 = (long)puStack_b0;
      return;
    }
    puVar9 = *(undefined8 **)(param_2 + 0x40);
    param_5 = param_5 - uVar11;
    param_3 = param_3 + uVar11;
    puVar9[2] = *(undefined8 *)(param_2 + 0x58);
    uVar15 = *(undefined8 *)(param_2 + 0x48);
    puVar9[1] = *(undefined8 *)(param_2 + 0x50);
    *puVar9 = uVar15;
    *param_4 = uVar11;
  }
  puVar13 = (uint *)(param_2 + 0x24);
  plVar14 = (long *)(param_2 + 0x40);
  puVar12 = (uint *)(param_2 + 0x1c);
  uVar2 = *puVar12;
  uVar11 = (ulong)(*puVar13 - uVar2);
  if (param_5 + uVar2 <= (ulong)*puVar13) {
    uVar11 = param_5;
  }
  memcpy(*plVar14 + (ulong)uVar2,param_3,uVar11);
  iVar7 = *(int *)(param_2 + 0x30);
  if (iVar7 < -0x5687796) {
    if (iVar7 < -0x4892c09e) {
      if (iVar7 < -0x64223629) {
        if (iVar7 < -0x7234acbc) {
          if (iVar7 < -0x7ad8d772) {
            if (iVar7 < -0x7cc6f0c1) {
              if (iVar7 < -0x7d3c4620) {
                if (((iVar7 != -0x7fa6f92a) && (iVar7 != -0x7ebe9058)) && (iVar7 != -0x7e92374c))
                goto code_r0x0150d5f4;
              }
              else if (((iVar7 != -0x7d3c4620) && (iVar7 != -0x7cf1daab)) && (iVar7 != -0x7ced59b4))
              goto code_r0x0150d5f4;
            }
            else if (iVar7 < -0x7b4ced06) {
              if (((iVar7 != -0x7cc6f0c1) && (iVar7 != -0x7c960b07)) && (iVar7 != -0x7c7f6405))
              goto code_r0x0150d5f4;
            }
            else if (((iVar7 != -0x7b4ced06) && (iVar7 != -0x7b326cb4)) && (iVar7 != -0x7af8ca2c))
            goto code_r0x0150d5f4;
          }
          else if (iVar7 < -0x77a50396) {
            if (iVar7 < -0x79295de0) {
              if (((iVar7 != -0x7ad8d772) && (iVar7 != -0x79c44e14)) && (iVar7 != -0x79717c96))
              goto code_r0x0150d5f4;
            }
            else if (((iVar7 != -0x79295de0) && (iVar7 != -0x7875ae36)) && (iVar7 != -0x784af043))
            goto code_r0x0150d5f4;
          }
          else if (iVar7 < -0x76ad55fe) {
            if (((iVar7 != -0x77a50396) && (iVar7 != -0x77506a62)) && (iVar7 != -0x770d6c7d))
            goto code_r0x0150d5f4;
          }
          else if (((iVar7 != -0x76ad55fe) && (iVar7 != -0x738770c7)) && (iVar7 != -0x728762df))
          goto code_r0x0150d5f4;
        }
        else if (iVar7 < -0x67d72cfe) {
          if (iVar7 < -0x6c834132) {
            if (iVar7 < -0x7108671d) {
              if (((iVar7 != -0x7234acbc) && (iVar7 != -0x71b57729)) && (iVar7 != -0x71953774))
              goto code_r0x0150d5f4;
            }
            else if (((iVar7 != -0x7108671d) && (iVar7 != -0x70629709)) && (iVar7 != -0x70312354))
            goto code_r0x0150d5f4;
          }
          else if (iVar7 < -0x6bba9e99) {
            if (((iVar7 != -0x6c834132) && (iVar7 != -0x6c7edfaf)) && (iVar7 != -0x6bd707e3))
            goto code_r0x0150d5f4;
          }
          else if (((iVar7 != -0x6bba9e99) && (iVar7 != -0x6a7fb7c9)) && (iVar7 != -0x69fab95d))
          goto code_r0x0150d5f4;
        }
        else if (iVar7 < -0x663df3cb) {
          if (iVar7 < -0x66f6de4a) {
            if (((iVar7 != -0x67d72cfe) && (iVar7 != -0x6762fe52)) && (iVar7 != -0x674fc6d0))
            goto code_r0x0150d5f4;
          }
          else if (((iVar7 != -0x66f6de4a) && (iVar7 != -0x66d3341b)) && (iVar7 != -0x668af173))
          goto code_r0x0150d5f4;
        }
        else if (iVar7 < -0x657f6312) {
          if (((iVar7 != -0x663df3cb) && (iVar7 != -0x65fa96fb)) && (iVar7 != -0x65a83037))
          goto code_r0x0150d5f4;
        }
        else if (((iVar7 != -0x657f6312) && (iVar7 != -0x654f9a53)) && (iVar7 != -0x6431a37b))
        goto code_r0x0150d5f4;
      }
      else if (iVar7 < -0x56945048) {
        if (iVar7 < -0x5cbbd2ae) {
          if (iVar7 < -0x600866dc) {
            if (iVar7 < -0x6194ed2a) {
              if (((iVar7 != -0x64223629) && (iVar7 != -0x637450be)) && (iVar7 != -0x63181bd2))
              goto code_r0x0150d5f4;
            }
            else if (((iVar7 != -0x6194ed2a) && (iVar7 != -0x613926a5)) && (iVar7 != -0x60d7f765))
            goto code_r0x0150d5f4;
          }
          else if (iVar7 < -0x5f5e6bf5) {
            if (((iVar7 != -0x600866dc) && (iVar7 != -0x5fe39811)) && (iVar7 != -0x5f6dd6d4))
            goto code_r0x0150d5f4;
          }
          else if (((iVar7 != -0x5f5e6bf5) && (iVar7 != -0x5e88a839)) && (iVar7 != -0x5d149646))
          goto code_r0x0150d5f4;
        }
        else if (iVar7 < -0x595b8f45) {
          if (iVar7 < -0x5c8519de) {
            if (((iVar7 != -0x5cbbd2ae) && (iVar7 != -0x5ca8c6fa)) && (iVar7 != -0x5c8c21e6))
            goto code_r0x0150d5f4;
          }
          else if (((iVar7 != -0x5c8519de) && (iVar7 != -0x5adc1a39)) && (iVar7 != -0x598cf4bf))
          goto code_r0x0150d5f4;
        }
        else if (iVar7 < -0x5857fbde) {
          if (((iVar7 != -0x595b8f45) && (iVar7 != -0x59310f81)) && (iVar7 != -0x58b0c731))
          goto code_r0x0150d5f4;
        }
        else if (((iVar7 != -0x5857fbde) && (iVar7 != -0x5857d10b)) && (iVar7 != -0x57252b1c))
        goto code_r0x0150d5f4;
      }
      else if (iVar7 < -0x4fb3eee4) {
        if (iVar7 < -0x53aee629) {
          if (iVar7 < -0x55c75f2b) {
            if (((iVar7 != -0x56945048) && (iVar7 != -0x566d9b0c)) && (iVar7 != -0x55f0a877))
            goto code_r0x0150d5f4;
          }
          else if (((iVar7 != -0x55c75f2b) && (iVar7 != -0x5595e2ef)) && (iVar7 != -0x554539fb))
          goto code_r0x0150d5f4;
        }
        else if (iVar7 < -0x50e3a2cd) {
          if (((iVar7 != -0x53aee629) && (iVar7 != -0x52391d16)) && (iVar7 != -0x5180f08a))
          goto code_r0x0150d5f4;
        }
        else if (((iVar7 != -0x50e3a2cd) && (iVar7 != -0x50dafdca)) && (iVar7 != -0x4ff6d997))
        goto code_r0x0150d5f4;
      }
      else if (iVar7 < -0x4d74d27a) {
        if (iVar7 < -0x4e61fff3) {
          if (((iVar7 != -0x4fb3eee4) && (iVar7 != -0x4f11fe18)) && (iVar7 != -0x4e9b4b3b))
          goto code_r0x0150d5f4;
        }
        else if (((iVar7 != -0x4e61fff3) && (iVar7 != -0x4e3f6e89)) && (iVar7 != -0x4d7bfc3e))
        goto code_r0x0150d5f4;
      }
      else if (iVar7 < -0x4b84bb2f) {
        if (((iVar7 != -0x4d74d27a) && (iVar7 != -0x4cd4e3a8)) && (iVar7 != -0x4c6798e2))
        goto code_r0x0150d5f4;
      }
      else if (iVar7 < -0x4a2ebb8e) {
        if ((iVar7 != -0x4b84bb2f) && (iVar7 != -0x4aa53dcf)) goto code_r0x0150d5f4;
      }
      else if ((iVar7 != -0x4a2ebb8e) && (iVar7 != -0x4a2ab71f)) goto code_r0x0150d5f4;
    }
    else if (iVar7 < -0x24831f15) {
      if (iVar7 < -0x3ace9372) {
        if (iVar7 < -0x42b3ebc6) {
          if (iVar7 < -0x45115e46) {
            if (iVar7 < -0x47636752) {
              if (((iVar7 != -0x4892c09e) && (iVar7 != -0x48441461)) && (iVar7 != -0x4839d43e))
              goto code_r0x0150d5f4;
            }
            else if (((iVar7 != -0x47636752) && (iVar7 != -0x46a87e54)) && (iVar7 != -0x45b0a60a))
            goto code_r0x0150d5f4;
          }
          else if (iVar7 < -0x44366331) {
            if (((iVar7 != -0x45115e46) && (iVar7 != -0x44f18107)) && (iVar7 != -0x443d1475))
            goto code_r0x0150d5f4;
          }
          else if (((iVar7 != -0x44366331) && (iVar7 != -0x431d180e)) && (iVar7 != -0x4311f02a))
          goto code_r0x0150d5f4;
        }
        else if (iVar7 < -0x3c98d975) {
          if (iVar7 < -0x3f46a05c) {
            if (((iVar7 != -0x42b3ebc6) && (iVar7 != -0x420361ee)) && (iVar7 != -0x4163dd24))
            goto code_r0x0150d5f4;
          }
          else if (((iVar7 != -0x3f46a05c) && (iVar7 != -0x3ee62f28)) && (iVar7 != -0x3d6d30b8))
          goto code_r0x0150d5f4;
        }
        else if (iVar7 < -0x3b6fde2c) {
          if (((iVar7 != -0x3c98d975) && (iVar7 != -0x3bf56623)) && (iVar7 != -0x3b802ada))
          goto code_r0x0150d5f4;
        }
        else if (((iVar7 != -0x3b6fde2c) && (iVar7 != -0x3b32c4e6)) && (iVar7 != -0x3ae6c4eb))
        goto code_r0x0150d5f4;
      }
      else if (iVar7 < -0x2ef197fa) {
        if (iVar7 < -0x33aba404) {
          if (iVar7 < -0x35789093) {
            if (((iVar7 != -0x3ace9372) && (iVar7 != -0x3a384f8b)) && (iVar7 != -0x36db590e))
            goto code_r0x0150d5f4;
          }
          else if (((iVar7 != -0x35789093) && (iVar7 != -0x34e5a87f)) && (iVar7 != -0x3469cf96))
          goto code_r0x0150d5f4;
        }
        else if (iVar7 < -0x30c633a4) {
          if (((iVar7 != -0x33aba404) && (iVar7 != -0x3375f857)) && (iVar7 != -0x3217317c))
          goto code_r0x0150d5f4;
        }
        else if (((iVar7 != -0x30c633a4) && (iVar7 != -0x3030d35a)) && (iVar7 != -0x2f4da34a))
        goto code_r0x0150d5f4;
      }
      else if (iVar7 < -0x2b0e875d) {
        if (iVar7 < -0x2dc9adb3) {
          if (((iVar7 != -0x2ef197fa) && (iVar7 != -0x2eaa114e)) && (iVar7 != -0x2e431412)) {
code_r0x0150d5f4:
            *param_1 = -0x3b8;
            return;
          }
        }
        else if (((iVar7 != -0x2dc9adb3) && (iVar7 != -0x2dc02319)) && (iVar7 != -0x2bfac17b))
        goto code_r0x0150d5f4;
      }
      else if (iVar7 < -0x29434b63) {
        if (((iVar7 != -0x2b0e875d) && (iVar7 != -0x2a13015e)) && (iVar7 != -0x29e6dc25))
        goto code_r0x0150d5f4;
      }
      else if (iVar7 < -0x26014c18) {
        if ((iVar7 != -0x29434b63) && (iVar7 != -0x27a64477)) goto code_r0x0150d5f4;
      }
      else if ((iVar7 != -0x26014c18) && (iVar7 != -0x2534649a)) goto code_r0x0150d5f4;
    }
    else if (iVar7 < -0x16c0e1ab) {
      if (iVar7 < -0x1d9db0a7) {
        if (iVar7 < -0x21648efc) {
          if (iVar7 < -0x231f99c5) {
            if (((iVar7 != -0x24831f15) && (iVar7 != -0x24768b92)) && (iVar7 != -0x23d96c9b))
            goto code_r0x0150d5f4;
          }
          else if (((iVar7 != -0x231f99c5) && (iVar7 != -0x21e6e44a)) && (iVar7 != -0x21794550))
          goto code_r0x0150d5f4;
        }
        else if (iVar7 < -0x1f91384d) {
          if (((iVar7 != -0x21648efc) && (iVar7 != -0x214bea67)) && (iVar7 != -0x20aa8941))
          goto code_r0x0150d5f4;
        }
        else if (((iVar7 != -0x1f91384d) && (iVar7 != -0x1f7368d2)) && (iVar7 != -0x1dd357bf))
        goto code_r0x0150d5f4;
      }
      else if (iVar7 < -0x1a50b774) {
        if (iVar7 < -0x1bda5a86) {
          if (((iVar7 != -0x1d9db0a7) && (iVar7 != -0x1d6b4ac7)) && (iVar7 != -0x1c1b9c53))
          goto code_r0x0150d5f4;
        }
        else if (((iVar7 != -0x1bda5a86) && (iVar7 != -0x1b6019ff)) && (iVar7 != -0x1a5fb24a))
        goto code_r0x0150d5f4;
      }
      else if (iVar7 < -0x1979c55d) {
        if (((iVar7 != -0x1a50b774) && (iVar7 != -0x19bc48f3)) && (iVar7 != -0x198503fb))
        goto code_r0x0150d5f4;
      }
      else if (((iVar7 != -0x1979c55d) && (iVar7 != -0x188b46db)) && (iVar7 != -0x171a3b26))
      goto code_r0x0150d5f4;
    }
    else if (iVar7 < -0xcd8b543) {
      if (iVar7 < -0x126551d8) {
        if (iVar7 < -0x130df39a) {
          if (((iVar7 != -0x16c0e1ab) && (iVar7 != -0x16871917)) && (iVar7 != -0x15fb0c03))
          goto code_r0x0150d5f4;
        }
        else if (((iVar7 != -0x130df39a) && (iVar7 != -0x13068c5a)) && (iVar7 != -0x12e1cb0a))
        goto code_r0x0150d5f4;
      }
      else if (iVar7 < -0xf891b30) {
        if (((iVar7 != -0x126551d8) && (iVar7 != -0x11ee3c2d)) && (iVar7 != -0x10fd227d))
        goto code_r0x0150d5f4;
      }
      else if (((iVar7 != -0xf891b30) && (iVar7 != -0xdc5c989)) && (iVar7 != -0xd913c10))
      goto code_r0x0150d5f4;
    }
    else if (iVar7 < -0x8d02a67) {
      if (iVar7 < -0xb88a07e) {
        if (((iVar7 != -0xcd8b543) && (iVar7 != -0xc5df1ef)) && (iVar7 != -0xbc569a3))
        goto code_r0x0150d5f4;
      }
      else if (((iVar7 != -0xb88a07e) && (iVar7 != -0x91e66c0)) && (iVar7 != -0x8dc2b69))
      goto code_r0x0150d5f4;
    }
    else if (iVar7 < -0x7c8edf7) {
      if (((iVar7 != -0x8d02a67) && (iVar7 != -0x804116e)) && (iVar7 != -0x7d35836))
      goto code_r0x0150d5f4;
    }
    else if (iVar7 < -0x65b4574) {
      if ((iVar7 != -0x7c8edf7) && (iVar7 != -0x78d2070)) goto code_r0x0150d5f4;
    }
    else if ((iVar7 != -0x65b4574) && (iVar7 != -0x587d5bb)) goto code_r0x0150d5f4;
  }
  else if (iVar7 < 0x3c6bb766) {
    if (iVar7 < 0x1d00a78c) {
      if (iVar7 < 0xa9bbfc6) {
        if (iVar7 < 0x465aa57) {
          if (iVar7 < 0x2d3011) {
            if (iVar7 < -0x242e8f3) {
              if (((iVar7 != -0x5687796) && (iVar7 != -0x4124367)) && (iVar7 != -0x3f2982e))
              goto code_r0x0150d5f4;
            }
            else if (((iVar7 != -0x242e8f3) && (iVar7 != -0x1e8ce61)) && (iVar7 != -0x149c28c))
            goto code_r0x0150d5f4;
          }
          else if (iVar7 < 0x2901c34) {
            if (((iVar7 != 0x2d3011) && (iVar7 != 0x88b260)) && (iVar7 != 0xee45f7))
            goto code_r0x0150d5f4;
          }
          else if (((iVar7 != 0x2901c34) && (iVar7 != 0x2a5cd1d)) && (iVar7 != 0x3f169b2))
          goto code_r0x0150d5f4;
        }
        else if (iVar7 < 0x747f39c) {
          if (iVar7 < 0x4ec9513) {
            if (((iVar7 != 0x465aa57) && (iVar7 != 0x488ed8b)) && (iVar7 != 0x4e93cba))
            goto code_r0x0150d5f4;
          }
          else if (((iVar7 != 0x4ec9513) && (iVar7 != 0x5aed673)) && (iVar7 != 0x6669069))
          goto code_r0x0150d5f4;
        }
        else if (iVar7 < 0xa16fd90) {
          if (((iVar7 != 0x747f39c) && (iVar7 != 0x74df139)) && (iVar7 != 0x89ac659))
          goto code_r0x0150d5f4;
        }
        else if (((iVar7 != 0xa16fd90) && (iVar7 != 0xa548dfb)) && (iVar7 != 0xa6cb929))
        goto code_r0x0150d5f4;
      }
      else if (iVar7 < 0x1680b258) {
        if (iVar7 < 0x12ed414b) {
          if (iVar7 < 0x111cebbc) {
            if (((iVar7 != 0xa9bbfc6) && (iVar7 != 0xbc7f736)) && (iVar7 != 0xdceac23))
            goto code_r0x0150d5f4;
          }
          else if (((iVar7 != 0x111cebbc) && (iVar7 != 0x1145eeb1)) && (iVar7 != 0x11d83292))
          goto code_r0x0150d5f4;
        }
        else if (iVar7 < 0x14e81e78) {
          if (((iVar7 != 0x12ed414b) && (iVar7 != 0x13d038c6)) && (iVar7 != 0x140e365b))
          goto code_r0x0150d5f4;
        }
        else if (((iVar7 != 0x14e81e78) && (iVar7 != 0x15a9bdbd)) && (iVar7 != 0x16110d36))
        goto code_r0x0150d5f4;
      }
      else if (iVar7 < 0x19e61236) {
        if (iVar7 < 0x174dfb83) {
          if (((iVar7 != 0x1680b258) && (iVar7 != 0x1700186d)) && (iVar7 != 0x172f3b5f))
          goto code_r0x0150d5f4;
        }
        else if (((iVar7 != 0x174dfb83) && (iVar7 != 0x178ab10d)) && (iVar7 != 0x17d0f2da))
        goto code_r0x0150d5f4;
      }
      else if (iVar7 < 0x1c0f79a8) {
        if (((iVar7 != 0x19e61236) && (iVar7 != 0x19f32f45)) && (iVar7 != 0x1bf95343))
        goto code_r0x0150d5f4;
      }
      else if (((iVar7 != 0x1c0f79a8) && (iVar7 != 0x1cf2b3d7)) && (iVar7 != 0x1cf7bf29))
      goto code_r0x0150d5f4;
    }
    else if (iVar7 < 0x2d714808) {
      if (iVar7 < 0x21e2c5f5) {
        if (iVar7 < 0x1eefb8e1) {
          if (iVar7 < 0x1d6647c0) {
            if (((iVar7 != 0x1d00a78c) && (iVar7 != 0x1d302dde)) && (iVar7 != 0x1d3bd009))
            goto code_r0x0150d5f4;
          }
          else if (((iVar7 != 0x1d6647c0) && (iVar7 != 0x1d7cbc6a)) && (iVar7 != 0x1e03058b))
          goto code_r0x0150d5f4;
        }
        else if (iVar7 < 0x1ff80da4) {
          if (((iVar7 != 0x1eefb8e1) && (iVar7 != 0x1f3c9eca)) && (iVar7 != 0x1f96f310))
          goto code_r0x0150d5f4;
        }
        else if (((iVar7 != 0x1ff80da4) && (iVar7 != 0x20059792)) && (iVar7 != 0x204af931))
        goto code_r0x0150d5f4;
      }
      else if (iVar7 < 0x27614ef3) {
        if (iVar7 < 0x2559b5a1) {
          if (((iVar7 != 0x21e2c5f5) && (iVar7 != 0x22b15407)) && (iVar7 != 0x22e8e9d7))
          goto code_r0x0150d5f4;
        }
        else if (((iVar7 != 0x2559b5a1) && (iVar7 != 0x263ff8f5)) && (iVar7 != 0x26be4983))
        goto code_r0x0150d5f4;
      }
      else if (iVar7 < 0x2b486f97) {
        if (((iVar7 != 0x27614ef3) && (iVar7 != 0x283a5a13)) && (iVar7 != 0x2acff1ed))
        goto code_r0x0150d5f4;
      }
      else if (((iVar7 != 0x2b486f97) && (iVar7 != 0x2d0a3ab3)) && (iVar7 != 0x2d230806))
      goto code_r0x0150d5f4;
    }
    else if (iVar7 < 0x33da88ce) {
      if (iVar7 < 0x319b66cd) {
        if (iVar7 < 0x2f9569e5) {
          if (((iVar7 != 0x2d714808) && (iVar7 != 0x2df0328c)) && (iVar7 != 0x2df9900d))
          goto code_r0x0150d5f4;
        }
        else if (((iVar7 != 0x2f9569e5) && (iVar7 != 0x30dccfe0)) && (iVar7 != 0x31054d24))
        goto code_r0x0150d5f4;
      }
      else if (iVar7 < 0x33015ed5) {
        if (((iVar7 != 0x319b66cd) && (iVar7 != 0x327e91c4)) && (iVar7 != 0x32907d0e))
        goto code_r0x0150d5f4;
      }
      else if (((iVar7 != 0x33015ed5) && (iVar7 != 0x337d16ba)) && (iVar7 != 0x33d09fb7))
      goto code_r0x0150d5f4;
    }
    else if (iVar7 < 0x388092cc) {
      if (iVar7 < 0x36ce009c) {
        if (((iVar7 != 0x33da88ce) && (iVar7 != 0x35b9d0d8)) && (iVar7 != 0x3663149d))
        goto code_r0x0150d5f4;
      }
      else if (((iVar7 != 0x36ce009c) && (iVar7 != 0x36ed89b2)) && (iVar7 != 0x3850fb96))
      goto code_r0x0150d5f4;
    }
    else if (iVar7 < 0x3a3ab3ed) {
      if (((iVar7 != 0x388092cc) && (iVar7 != 0x39a5d47f)) && (iVar7 != 0x39b9ddd6))
      goto code_r0x0150d5f4;
    }
    else if (iVar7 < 0x3b6edbb0) {
      if ((iVar7 != 0x3a3ab3ed) && (iVar7 != 0x3a498604)) goto code_r0x0150d5f4;
    }
    else if ((iVar7 != 0x3b6edbb0) && (iVar7 != 0x3ba507e7)) goto code_r0x0150d5f4;
  }
  else if (iVar7 < 0x5be25d4b) {
    if (iVar7 < 0x47e9dee6) {
      if (iVar7 < 0x445ab956) {
        if (iVar7 < 0x4072d7e1) {
          if (iVar7 < 0x3e77af96) {
            if (((iVar7 != 0x3c6bb766) && (iVar7 != 0x3c9d0c11)) && (iVar7 != 0x3cb70efe))
            goto code_r0x0150d5f4;
          }
          else if (((iVar7 != 0x3e77af96) && (iVar7 != 0x3fe3d55a)) && (iVar7 != 0x40452e0c))
          goto code_r0x0150d5f4;
        }
        else if (iVar7 < 0x42ff2e75) {
          if (((iVar7 != 0x4072d7e1) && (iVar7 != 0x408f02f6)) && (iVar7 != 0x40db9f93))
          goto code_r0x0150d5f4;
        }
        else if (((iVar7 != 0x42ff2e75) && (iVar7 != 0x4332363c)) && (iVar7 != 0x440cf28b))
        goto code_r0x0150d5f4;
      }
      else if (iVar7 < 0x4638051b) {
        if (iVar7 < 0x451d30bf) {
          if (((iVar7 != 0x445ab956) && (iVar7 != 0x447fafb8)) && (iVar7 != 0x45141737))
          goto code_r0x0150d5f4;
        }
        else if (((iVar7 != 0x451d30bf) && (iVar7 != 0x45bea005)) && (iVar7 != 0x45ebe6cf))
        goto code_r0x0150d5f4;
      }
      else if (iVar7 < 0x46e0807c) {
        if (((iVar7 != 0x4638051b) && (iVar7 != 0x4656d729)) && (iVar7 != 0x466bfd80))
        goto code_r0x0150d5f4;
      }
      else if (((iVar7 != 0x46e0807c) && (iVar7 != 0x4700c6f7)) && (iVar7 != 0x479604f6))
      goto code_r0x0150d5f4;
    }
    else if (iVar7 < 0x53dd1932) {
      if (iVar7 < 0x4af4eaf3) {
        if (iVar7 < 0x4a6a4344) {
          if (((iVar7 != 0x47e9dee6) && (iVar7 != 0x49898ba4)) && (iVar7 != 0x4a05654a))
          goto code_r0x0150d5f4;
        }
        else if (((iVar7 != 0x4a6a4344) && (iVar7 != 0x4a8aa6e2)) && (iVar7 != 0x4ac5eaa0))
        goto code_r0x0150d5f4;
      }
      else if (iVar7 < 0x4cc0afb2) {
        if (((iVar7 != 0x4af4eaf3) && (iVar7 != 0x4afdaba2)) && (iVar7 != 0x4b76b6d7))
        goto code_r0x0150d5f4;
      }
      else if (((iVar7 != 0x4cc0afb2) && (iVar7 != 0x4ff23fbb)) && (iVar7 != 0x5187adb1))
      goto code_r0x0150d5f4;
    }
    else if (iVar7 < 0x591b749a) {
      if (iVar7 < 0x56d6425e) {
        if (((iVar7 != 0x53dd1932) && (iVar7 != 0x5458404e)) && (iVar7 != 0x56b64bfe))
        goto code_r0x0150d5f4;
      }
      else if (((iVar7 != 0x56d6425e) && (iVar7 != 0x57308f4d)) && (iVar7 != 0x58123949))
      goto code_r0x0150d5f4;
    }
    else if (iVar7 < 0x59cce58a) {
      if (((iVar7 != 0x591b749a) && (iVar7 != 0x5943ae5c)) && (iVar7 != 0x59a48d41))
      goto code_r0x0150d5f4;
    }
    else if (iVar7 < 0x5a401f57) {
      if ((iVar7 != 0x59cce58a) && (iVar7 != 0x59f02ddd)) goto code_r0x0150d5f4;
    }
    else if ((iVar7 != 0x5a401f57) && (iVar7 != 0x5ac657b3)) goto code_r0x0150d5f4;
  }
  else if (iVar7 < 0x741e0072) {
    if (iVar7 < 0x6c448c17) {
      if (iVar7 < 0x614fa7ea) {
        if (iVar7 < 0x5e598152) {
          if (((iVar7 != 0x5be25d4b) && (iVar7 != 0x5cf6a3e9)) && (iVar7 != 0x5df89dfc))
          goto code_r0x0150d5f4;
        }
        else if (((iVar7 != 0x5e598152) && (iVar7 != 0x5f583f50)) && (iVar7 != 0x60739c9d))
        goto code_r0x0150d5f4;
      }
      else if (iVar7 < 0x63c9927a) {
        if (((iVar7 != 0x614fa7ea) && (iVar7 != 0x61d246ee)) && (iVar7 != 0x626e1e5f))
        goto code_r0x0150d5f4;
      }
      else if (((iVar7 != 0x63c9927a) && (iVar7 != 0x655d0ece)) && (iVar7 != 0x685d66f3))
      goto code_r0x0150d5f4;
    }
    else if (iVar7 < 0x716f7fd6) {
      if (iVar7 < 0x6e46623e) {
        if (((iVar7 != 0x6c448c17) && (iVar7 != 0x6c67993d)) && (iVar7 != 0x6da21fe9))
        goto code_r0x0150d5f4;
      }
      else if (((iVar7 != 0x6e46623e) && (iVar7 != 0x70abaa88)) && (iVar7 != 0x70d0f3ce))
      goto code_r0x0150d5f4;
    }
    else if (iVar7 < 0x72a94d0c) {
      if (iVar7 != 0x716f7fd6) {
        if (iVar7 == 0x717cc46f) {
          uVar8 = Aska::Yayoi::GameRPC::GameProtocol::CheckRecast(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, long)(*(undefined8 *)(param_2 + 0x10),0x717cc46f,5000);
          if ((uVar8 & 1) == 0) {
            *param_1 = -0x38a;
            return;
          }
        }
        else if (iVar7 != 0x720e2bac) goto code_r0x0150d5f4;
      }
    }
    else if (((iVar7 != 0x72a94d0c) && (iVar7 != 0x7329eff2)) && (iVar7 != 0x737fac92))
    goto code_r0x0150d5f4;
  }
  else if (iVar7 < 0x78972d03) {
    if (iVar7 < 0x75ec29fd) {
      if (iVar7 < 0x74e09417) {
        if (((iVar7 != 0x741e0072) && (iVar7 != 0x7475e348)) && (iVar7 != 0x74d51575))
        goto code_r0x0150d5f4;
      }
      else if (((iVar7 != 0x74e09417) && (iVar7 != 0x755c193d)) && (iVar7 != 0x755cba3d))
      goto code_r0x0150d5f4;
    }
    else if (iVar7 < 0x77f99232) {
      if (((iVar7 != 0x75ec29fd) && (iVar7 != 0x76969a00)) && (iVar7 != 0x77c6528c))
      goto code_r0x0150d5f4;
    }
    else if (((iVar7 != 0x77f99232) && (iVar7 != 0x7810f1f7)) && (iVar7 != 0x7827ff6a))
    goto code_r0x0150d5f4;
  }
  else if (iVar7 < 0x7c137ead) {
    if (iVar7 < 0x7a71be2c) {
      if (((iVar7 != 0x78972d03) && (iVar7 != 0x7980a5eb)) && (iVar7 != 0x7a7121ad))
      goto code_r0x0150d5f4;
    }
    else if (((iVar7 != 0x7a71be2c) && (iVar7 != 0x7aaa4087)) && (iVar7 != 0x7bb39ae6))
    goto code_r0x0150d5f4;
  }
  else if (iVar7 < 0x7c49b449) {
    if (((iVar7 != 0x7c137ead) && (iVar7 != 0x7c1b7a1b)) && (iVar7 != 0x7c2b82bf))
    goto code_r0x0150d5f4;
  }
  else if (iVar7 < 0x7e277fa1) {
    if ((iVar7 != 0x7c49b449) && (iVar7 != 0x7ce2cd81)) goto code_r0x0150d5f4;
  }
  else if ((iVar7 != 0x7e277fa1) && (iVar7 != 0x7e549638)) goto code_r0x0150d5f4;
  uVar2 = *puVar12 + (int)uVar11;
  *puVar12 = uVar2;
  puVar6 = PTR__ZTVN4Aska12StaticStreamE_02cba478;
  if (uVar2 != *puVar13) {
code_r0x0150faa0:
    *param_4 = *param_4 + uVar11;
code_r0x0150faac:
    *param_1 = 0;
    return;
  }
  puVar1 = PTR__ZTVN4Aska12StaticStreamE_02cba478 + 0x10;
  uStack_88 = 0;
  piStack_90 = (int *)0x0;
  lStack_98 = 0;
  piStack_a0 = (int *)0x0;
  lStack_a8 = 0;
  puStack_b0 = puVar1;
  Aska::StaticStream::Open(signed char const*, unsigned long)(&puStack_b0,*plVar14,uVar2 - 0x14);
  Aska::Hash::SHA1(Aska::IStream*, unsigned long, char*, unsigned long)(&lStack_58,&puStack_b0,*puVar13 - 0x14,auStack_c4,0x14);
  if (lStack_58 < 0) {
    *param_1 = lStack_58;
    if (piStack_90 == (int *)0x0) {
code_r0x0150f9c0:
      puStack_b0 = puVar1;
      if (lStack_98 != 0) {
        operator delete[](void*)();
      }
      if (piStack_90 != (int *)0x0) {
        Aska::TSharedPointerCode::DeleteCounter(int*)();
      }
    }
    else {
      do {
        iVar7 = *piStack_90;
        cVar4 = '\x01';
        bVar5 = (bool)ExclusiveMonitorPass(piStack_90,0x10);
        if (bVar5) {
          *piStack_90 = iVar7 + -1;
          cVar4 = ExclusiveMonitorsStatus();
        }
      } while (cVar4 != '\0');
      puStack_b0 = puVar1;
      if (iVar7 + -1 == 0) goto code_r0x0150f9c0;
    }
    if (piStack_a0 == (int *)0x0) goto code_r0x0150f9f8;
    do {
      iVar7 = *piStack_a0 + -1;
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piStack_a0,0x10);
      if (bVar5) {
        *piStack_a0 = iVar7;
        cVar4 = ExclusiveMonitorsStatus();
      }
    } while (cVar4 != '\0');
  }
  else {
    uVar2 = *puVar13;
    iVar7 = memcmp(auStack_c4,*plVar14 + (ulong)uVar2 + -0x14,0x14);
    if (iVar7 == 0) {
      *(uint *)(param_2 + 0x24) = uVar2 - 0x14;
      *(undefined1 *)(param_2 + 0x19) = 1;
      puStack_b0 = puVar6 + 0x10;
      if (piStack_90 == (int *)0x0) {
code_r0x0150fa4c:
        if (lStack_98 != 0) {
          operator delete[](void*)();
        }
        if (piStack_90 != (int *)0x0) {
          Aska::TSharedPointerCode::DeleteCounter(int*)();
        }
      }
      else {
        do {
          iVar7 = *piStack_90;
          cVar4 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(piStack_90,0x10);
          if (bVar5) {
            *piStack_90 = iVar7 + -1;
            cVar4 = ExclusiveMonitorsStatus();
          }
        } while (cVar4 != '\0');
        if (iVar7 + -1 == 0) goto code_r0x0150fa4c;
      }
      lStack_98 = 0;
      piStack_90 = (int *)0x0;
      if (piStack_a0 != (int *)0x0) {
        do {
          iVar7 = *piStack_a0;
          cVar4 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(piStack_a0,0x10);
          if (bVar5) {
            *piStack_a0 = iVar7 + -1;
            cVar4 = ExclusiveMonitorsStatus();
          }
        } while (cVar4 != '\0');
        if (iVar7 + -1 != 0) goto code_r0x0150faa0;
      }
      if (lStack_a8 != 0) {
        operator delete[](void*)();
      }
      if (piStack_a0 != (int *)0x0) {
        Aska::TSharedPointerCode::DeleteCounter(int*)();
      }
      goto code_r0x0150faa0;
    }
    puStack_b0 = puVar6 + 0x10;
    *param_1 = -0x3b8;
    if (piStack_90 == (int *)0x0) {
code_r0x0150f964:
      if (lStack_98 != 0) {
        operator delete[](void*)();
      }
      if (piStack_90 != (int *)0x0) {
        Aska::TSharedPointerCode::DeleteCounter(int*)();
      }
    }
    else {
      do {
        iVar7 = *piStack_90;
        cVar4 = '\x01';
        bVar5 = (bool)ExclusiveMonitorPass(piStack_90,0x10);
        if (bVar5) {
          *piStack_90 = iVar7 + -1;
          cVar4 = ExclusiveMonitorsStatus();
        }
      } while (cVar4 != '\0');
      if (iVar7 + -1 == 0) goto code_r0x0150f964;
    }
    if (piStack_a0 == (int *)0x0) goto code_r0x0150f9f8;
    do {
      iVar7 = *piStack_a0 + -1;
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piStack_a0,0x10);
      if (bVar5) {
        *piStack_a0 = iVar7;
        cVar4 = ExclusiveMonitorsStatus();
      }
    } while (cVar4 != '\0');
  }
  if (iVar7 != 0) {
    return;
  }
code_r0x0150f9f8:
  piStack_90 = (int *)0x0;
  lStack_98 = 0;
  if (lStack_a8 != 0) {
    operator delete[](void*)();
  }
  if (piStack_a0 == (int *)0x0) {
    return;
  }
  Aska::TSharedPointerCode::DeleteCounter(int*)();
  return;
}

// ==== undefined Aska::Yayoi::GameRPC::GameProtocoledData::_read_header(signed *,unsigned int)
// _ZN4Aska5Yayoi7GameRPC18GameProtocoledData12_read_headerEPaj @ 0150fdb0

void _ZN4Aska5Yayoi7GameRPC18GameProtocoledData12_read_headerEPaj
               (undefined8 *param_1,long param_2,byte *param_3,int param_4)

{
  ulong uVar1;
  ulong uVar2;
  
  uVar1 = (ulong)param_3[4] << 0x38 | (ulong)*param_3 << 0x30 | (ulong)param_3[7] << 0x28 |
          (ulong)param_3[1] << 0x20 | (ulong)param_3[2] << 0x18 | (ulong)param_3[6] << 0x10 |
          (ulong)param_3[3] | (ulong)param_3[5] << 8;
  uVar2 = *(ulong *)(param_3 + 8) ^ uVar1;
  uVar1 = *(ulong *)(param_3 + 0x10) ^ uVar1;
  *(int *)(param_2 + 0x30) = (int)(uVar2 >> 0x20);
  *(int *)(param_2 + 0x34) = (int)uVar1;
  *(int *)(param_2 + 0x24) = (int)uVar2 + param_4;
  *(char *)(param_2 + 0x38) = (char)(uVar1 >> 0x20);
  *param_1 = 0;
  return;
}

// ==== undefined Aska::Yayoi::MO::BattleProtocol::Serialize(Aska::Yayoi::MO::BattleProtocoledData *,signed * *,unsigned long,void const *,unsigned long,unsigned long *)
// _ZN4Aska5Yayoi2MO14BattleProtocol9SerializeEPNS1_20BattleProtocoledDataEPPamPKvmPm @ 015926a0

void _ZN4Aska5Yayoi2MO14BattleProtocol9SerializeEPNS1_20BattleProtocoledDataEPPamPKvmPm
               (undefined8 *param_1,undefined8 param_2,long param_3,undefined8 *param_4,
               ulong param_5,undefined8 param_6,long param_7,ulong *param_8)

{
  undefined8 uVar1;
  ulong uVar2;
  
  if (param_7 == 0) {
    uVar2 = (ulong)*(uint *)(param_3 + 0x24);
    if (param_5 < uVar2) {
      uVar1 = 0xfffffffffffffc15;
    }
    else {
      memcpy(*param_4,*(undefined8 *)(param_3 + 0x40),uVar2);
      uVar1 = 0;
      *param_8 = uVar2;
    }
  }
  else {
    uVar1 = 0xfffffffffffffc4b;
  }
  *param_1 = uVar1;
  return;
}

// ==== undefined Aska::Yayoi::MO::BattleProtocol::Deserialize(signed const *,unsigned long,unsigned long *,Aska::Yayoi::MO::BattleProtocoledData *,Aska::Status &)
// _ZN4Aska5Yayoi2MO14BattleProtocol11DeserializeEPKamPmPNS1_20BattleProtocoledDataERNS_6StatusE @ 015926f8

undefined8
_ZN4Aska5Yayoi2MO14BattleProtocol11DeserializeEPKamPmPNS1_20BattleProtocoledDataERNS_6StatusE
          (long param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5,
          long *param_6)

{
  long lStack_28;
  
  Aska::Yayoi::MO::BattleProtocoledData::Deserialize(signed char const*, unsigned long*, unsigned long)(&lStack_28,param_5,param_2,param_4,param_3);
  *param_6 = lStack_28;
  if (lStack_28 < 0) {
    param_5 = 0;
    *(undefined8 *)(param_1 + 0x90) = *(undefined8 *)(param_1 + 0x98);
  }
  else {
    *(undefined8 *)(param_1 + 0x98) = *(undefined8 *)(param_1 + 0x90);
  }
  return param_5;
}

// ==== undefined Aska::Yayoi::MO::BattleProtocoledData::Deserialize(signed const *,unsigned long *,unsigned long)
// _ZN4Aska5Yayoi2MO20BattleProtocoledData11DeserializeEPKaPmm @ 01592760

void _ZN4Aska5Yayoi2MO20BattleProtocoledData11DeserializeEPKaPmm
               (long *param_1,long param_2,long param_3,ulong *param_4,ulong param_5)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  ulong uVar4;
  ulong uVar5;
  undefined8 *puVar6;
  ulong uVar7;
  uint *puVar8;
  undefined8 uVar9;
  long lStack_58;
  
  *param_4 = 0;
  if (*(char *)(param_2 + 0x60) == '\0') {
    uVar1 = *(uint *)(param_2 + 0x1c);
    uVar3 = (uint)param_5;
    if (0x18 - uVar1 <= param_5) {
      uVar3 = 0x18 - uVar1;
    }
    uVar7 = (ulong)uVar3;
    memcpy(param_2 + 0x48 + (ulong)uVar1,param_3,uVar7);
    uVar3 = uVar3 + uVar1;
    *(uint *)(param_2 + 0x1c) = uVar3;
    *(bool *)(param_2 + 0x60) = uVar3 == 0x18;
    if (uVar3 != 0x18) {
      lStack_58 = 0;
      *param_4 = param_5;
      goto code_r0x01592d5c;
    }
    uVar5 = (ulong)*(byte *)(param_2 + 0x4c) << 0x38 | (ulong)*(byte *)(param_2 + 0x48) << 0x30 |
            (ulong)*(byte *)(param_2 + 0x4f) << 0x28 | (ulong)*(byte *)(param_2 + 0x49) << 0x20 |
            (ulong)*(byte *)(param_2 + 0x4a) << 0x18 | (ulong)*(byte *)(param_2 + 0x4e) << 0x10 |
            (ulong)*(byte *)(param_2 + 0x4b) | (ulong)*(byte *)(param_2 + 0x4d) << 8;
    uVar4 = *(ulong *)(param_2 + 0x50) ^ uVar5;
    uVar5 = *(uint5 *)(param_2 + 0x58) ^ uVar5;
    uVar3 = (uint)uVar4;
    *(uint *)(param_2 + 0x24) = uVar3;
    *(int *)(param_2 + 0x30) = (int)(uVar4 >> 0x20);
    *(int *)(param_2 + 0x34) = (int)uVar5;
    *(char *)(param_2 + 0x38) = (char)(uVar5 >> 0x20);
    if (uVar3 < 0x18) {
      lStack_58 = -0x3b8;
      goto code_r0x01592d5c;
    }
    Aska::Yayoi::MO::BattleProtocoledData::AllocateBuffer(int)(&lStack_58,param_2,uVar3 << (uVar5 >> 0x27 & 1));
    if (lStack_58 < 0) goto code_r0x01592d5c;
    puVar6 = *(undefined8 **)(param_2 + 0x40);
    param_5 = param_5 - uVar7;
    param_3 = param_3 + uVar7;
    puVar6[2] = *(undefined8 *)(param_2 + 0x58);
    uVar9 = *(undefined8 *)(param_2 + 0x48);
    puVar6[1] = *(undefined8 *)(param_2 + 0x50);
    *puVar6 = uVar9;
    *param_4 = uVar7;
  }
  puVar8 = (uint *)(param_2 + 0x1c);
  uVar3 = *puVar8;
  uVar1 = *(uint *)(param_2 + 0x24);
  uVar7 = (ulong)(uVar1 - uVar3);
  if (param_5 + uVar3 <= (ulong)uVar1) {
    uVar7 = param_5;
  }
  memcpy(*(long *)(param_2 + 0x40) + (ulong)uVar3,param_3,uVar7);
  iVar2 = *(int *)(param_2 + 0x30);
  lStack_58 = -0x3b8;
  if (iVar2 < -0xd2accff) {
    if (iVar2 < -0x4dbbcb2f) {
      if (iVar2 < -0x5d99834f) {
        if (iVar2 < -0x6d689a3d) {
          if ((iVar2 != -0x7ced59b4) && (iVar2 != -0x7a99355b)) goto code_r0x01592d5c;
        }
        else if ((iVar2 != -0x6d689a3d) && ((iVar2 != -0x6b74f8ea && (iVar2 != -0x676fa26b))))
        goto code_r0x01592d5c;
      }
      else if (iVar2 < -0x5902e8eb) {
        if (((iVar2 != -0x5d99834f) && (iVar2 != -0x5bf952c8)) && (iVar2 != -0x59d622ca))
        goto code_r0x01592d5c;
      }
      else if (((iVar2 != -0x5902e8eb) && (iVar2 != -0x514ce136)) && (iVar2 != -0x4eaccd9f))
      goto code_r0x01592d5c;
    }
    else if (iVar2 < -0x2f5a7193) {
      if (iVar2 < -0x4269077e) {
        if (((iVar2 != -0x4dbbcb2f) && (iVar2 != -0x452ca1d8)) && (iVar2 != -0x4353226f))
        goto code_r0x01592d5c;
      }
      else if (((iVar2 != -0x4269077e) && (iVar2 != -0x3e0cc534)) && (iVar2 != -0x3b874246))
      goto code_r0x01592d5c;
    }
    else if (iVar2 < -0x1d2dcd80) {
      if (((iVar2 != -0x2f5a7193) && (iVar2 != -0x2b37d136)) && (iVar2 != -0x1fbdcd68))
      goto code_r0x01592d5c;
    }
    else if (((iVar2 != -0x1d2dcd80) && (iVar2 != -0x1a3b64a6)) && (iVar2 != -0x14011ec9))
    goto code_r0x01592d5c;
  }
  else if (iVar2 < 0x399501b0) {
    if (iVar2 < 0xf074e01) {
      if (iVar2 < -0x1416904) {
        if (((iVar2 != -0xd2accff) && (iVar2 != -0x9213ce3)) && (iVar2 != -0x7968181))
        goto code_r0x01592d5c;
      }
      else if (((iVar2 != -0x1416904) && (iVar2 != 0x214d5cf)) && (iVar2 != 0x5aed673))
      goto code_r0x01592d5c;
    }
    else if (iVar2 < 0x3712ac8e) {
      if (((iVar2 != 0xf074e01) && (iVar2 != 0x10ce4f8f)) && (iVar2 != 0x16287e9b))
      goto code_r0x01592d5c;
    }
    else if (((iVar2 != 0x3712ac8e) && (iVar2 != 0x3764a958)) && (iVar2 != 0x38c5438d))
    goto code_r0x01592d5c;
  }
  else if (iVar2 < 0x5528c22a) {
    if (iVar2 < 0x440ed5b8) {
      if (((iVar2 != 0x399501b0) && (iVar2 != 0x40db9f93)) && (iVar2 != 0x43610d78))
      goto code_r0x01592d5c;
    }
    else if (((iVar2 != 0x440ed5b8) && (iVar2 != 0x44ac9b5c)) && (iVar2 != 0x535410ce))
    goto code_r0x01592d5c;
  }
  else if (iVar2 < 0x62cd4997) {
    if (((iVar2 != 0x5528c22a) && (iVar2 != 0x57faa296)) && (iVar2 != 0x5e3b82b4))
    goto code_r0x01592d5c;
  }
  else if (((iVar2 != 0x62cd4997) && (iVar2 != 0x755cba3d)) && (iVar2 != 0x7309d699))
  goto code_r0x01592d5c;
  uVar3 = *puVar8 + (int)uVar7;
  *puVar8 = uVar3;
  if (uVar3 == *(uint *)(param_2 + 0x24)) {
    *(undefined1 *)(param_2 + 0x19) = 1;
  }
  lStack_58 = 0;
  *param_4 = *param_4 + uVar7;
code_r0x01592d5c:
  *param_1 = lStack_58;
  return;
}

// ==== undefined Aska::Yayoi::MO::BattleProtocol::CheckRecast(Aska::Yayoi::MO::BattleProtocol::FunctionID,long)
// _ZN4Aska5Yayoi2MO14BattleProtocol11CheckRecastENS2_10FunctionIDEl @ 01592d7c

undefined8 _ZN4Aska5Yayoi2MO14BattleProtocol11CheckRecastENS2_10FunctionIDEl(void)

{
  return 1;
}

// ==== undefined Aska::Yayoi::MO::BattleProtocol::CheckTime(unsigned long *)
// _ZN4Aska5Yayoi2MO14BattleProtocol9CheckTimeEPm @ 01592d84

void _ZN4Aska5Yayoi2MO14BattleProtocol9CheckTimeEPm(undefined8 *param_1)

{
  *param_1 = 0;
  return;
}

// ==== undefined Aska::Yayoi::MO::BattleProtocoledData::_read_header(signed *,unsigned int)
// _ZN4Aska5Yayoi2MO20BattleProtocoledData12_read_headerEPaj @ 01592dec

void _ZN4Aska5Yayoi2MO20BattleProtocoledData12_read_headerEPaj
               (undefined8 *param_1,long param_2,byte *param_3,int param_4)

{
  ulong uVar1;
  ulong uVar2;
  
  uVar1 = (ulong)param_3[4] << 0x38 | (ulong)*param_3 << 0x30 | (ulong)param_3[7] << 0x28 |
          (ulong)param_3[1] << 0x20 | (ulong)param_3[2] << 0x18 | (ulong)param_3[6] << 0x10 |
          (ulong)param_3[3] | (ulong)param_3[5] << 8;
  uVar2 = *(ulong *)(param_3 + 8) ^ uVar1;
  uVar1 = *(ulong *)(param_3 + 0x10) ^ uVar1;
  *(int *)(param_2 + 0x30) = (int)(uVar2 >> 0x20);
  *(int *)(param_2 + 0x34) = (int)uVar1;
  *(int *)(param_2 + 0x24) = (int)uVar2 + param_4;
  *(char *)(param_2 + 0x38) = (char)(uVar1 >> 0x20);
  *param_1 = 0;
  return;
}

// ==== undefined Aska::Yayoi::MultiplayRPC::LobbyProtocoledData::Deserialize(signed const *,unsigned long *,unsigned long)
// _ZN4Aska5Yayoi12MultiplayRPC19LobbyProtocoledData11DeserializeEPKaPmm @ 022f8b64

void _ZN4Aska5Yayoi12MultiplayRPC19LobbyProtocoledData11DeserializeEPKaPmm
               (long *param_1,long param_2,long param_3,ulong *param_4,ulong param_5)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  ulong uVar4;
  ulong uVar5;
  undefined8 *puVar6;
  ulong uVar7;
  uint *puVar8;
  undefined8 uVar9;
  long lStack_58;
  
  *param_4 = 0;
  if (*(char *)(param_2 + 0x60) == '\0') {
    uVar1 = *(uint *)(param_2 + 0x1c);
    uVar3 = (uint)param_5;
    if (0x18 - uVar1 <= param_5) {
      uVar3 = 0x18 - uVar1;
    }
    uVar7 = (ulong)uVar3;
    memcpy(param_2 + 0x48 + (ulong)uVar1,param_3,uVar7);
    uVar3 = uVar3 + uVar1;
    *(uint *)(param_2 + 0x1c) = uVar3;
    *(bool *)(param_2 + 0x60) = uVar3 == 0x18;
    if (uVar3 != 0x18) {
      lStack_58 = 0;
      *param_4 = param_5;
      goto code_r0x022f8e18;
    }
    uVar5 = (ulong)*(byte *)(param_2 + 0x4c) << 0x38 | (ulong)*(byte *)(param_2 + 0x48) << 0x30 |
            (ulong)*(byte *)(param_2 + 0x4f) << 0x28 | (ulong)*(byte *)(param_2 + 0x49) << 0x20 |
            (ulong)*(byte *)(param_2 + 0x4a) << 0x18 | (ulong)*(byte *)(param_2 + 0x4e) << 0x10 |
            (ulong)*(byte *)(param_2 + 0x4b) | (ulong)*(byte *)(param_2 + 0x4d) << 8;
    uVar4 = *(ulong *)(param_2 + 0x50) ^ uVar5;
    uVar5 = *(uint5 *)(param_2 + 0x58) ^ uVar5;
    uVar3 = (uint)uVar4;
    *(uint *)(param_2 + 0x24) = uVar3;
    *(int *)(param_2 + 0x30) = (int)(uVar4 >> 0x20);
    *(int *)(param_2 + 0x34) = (int)uVar5;
    *(char *)(param_2 + 0x38) = (char)(uVar5 >> 0x20);
    if (uVar3 < 0x18) {
      lStack_58 = -0x3b8;
      goto code_r0x022f8e18;
    }
    Aska::Yayoi::MultiplayRPC::LobbyProtocoledData::AllocateBuffer(int)(&lStack_58,param_2,uVar3 << (uVar5 >> 0x27 & 1));
    if (lStack_58 < 0) goto code_r0x022f8e18;
    puVar6 = *(undefined8 **)(param_2 + 0x40);
    param_5 = param_5 - uVar7;
    param_3 = param_3 + uVar7;
    puVar6[2] = *(undefined8 *)(param_2 + 0x58);
    uVar9 = *(undefined8 *)(param_2 + 0x48);
    puVar6[1] = *(undefined8 *)(param_2 + 0x50);
    *puVar6 = uVar9;
    *param_4 = uVar7;
  }
  puVar8 = (uint *)(param_2 + 0x1c);
  uVar3 = *puVar8;
  uVar1 = *(uint *)(param_2 + 0x24);
  uVar7 = (ulong)(uVar1 - uVar3);
  if (param_5 + uVar3 <= (ulong)uVar1) {
    uVar7 = param_5;
  }
  memcpy(*(long *)(param_2 + 0x40) + (ulong)uVar3,param_3,uVar7);
  iVar2 = *(int *)(param_2 + 0x30);
  lStack_58 = -0x3b8;
  if (iVar2 < -0x4a2f28d) {
    if (iVar2 < -0x17042556) {
      if (((iVar2 != -0x57102278) && (iVar2 != -0x33779874)) && (iVar2 != -0x1c565ad8))
      goto code_r0x022f8e18;
    }
    else if (((iVar2 != -0x17042556) && (iVar2 != -0x153bdfff)) && (iVar2 != -0x101e124a))
    goto code_r0x022f8e18;
  }
  else if (iVar2 < 0x2ddf640d) {
    if (((iVar2 != -0x4a2f28d) && (iVar2 != 0x5aed673)) && (iVar2 != 0x1fed00e2))
    goto code_r0x022f8e18;
  }
  else if (iVar2 < 0x6a1b49a5) {
    if ((iVar2 != 0x2ddf640d) && (iVar2 != 0x4e466d87)) goto code_r0x022f8e18;
  }
  else if ((iVar2 != 0x6b177840) && (iVar2 != 0x6a1b49a5)) goto code_r0x022f8e18;
  uVar3 = *puVar8 + (int)uVar7;
  *puVar8 = uVar3;
  if (uVar3 == *(uint *)(param_2 + 0x24)) {
    *(undefined1 *)(param_2 + 0x19) = 1;
  }
  lStack_58 = 0;
  *param_4 = *param_4 + uVar7;
code_r0x022f8e18:
  *param_1 = lStack_58;
  return;
}

// ==== undefined Aska::Yayoi::MultiplayRPC::LobbyProtocol::CheckTime(unsigned long *)
// _ZN4Aska5Yayoi12MultiplayRPC13LobbyProtocol9CheckTimeEPm @ 022f8e8c

void _ZN4Aska5Yayoi12MultiplayRPC13LobbyProtocol9CheckTimeEPm(undefined8 *param_1)

{
  *param_1 = 0;
  return;
}

// ==== undefined Aska::Yayoi::MO::BattleProtocoledData::_write_header(unsigned int,Aska::Yayoi::MO::BattleProtocol::FunctionID,unsigned int,signed)
// _ZN4Aska5Yayoi2MO20BattleProtocoledData13_write_headerEjNS1_14BattleProtocol10FunctionIDEja @ 01593198

undefined8
_ZN4Aska5Yayoi2MO20BattleProtocoledData13_write_headerEjNS1_14BattleProtocol10FunctionIDEja
          (long param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined1 param_5)

{
  bool bVar1;
  long lVar2;
  byte bVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  undefined8 *puVar7;
  ulong uVar8;
  byte bVar9;
  byte bVar10;
  byte bVar11;
  byte bVar12;
  byte bVar13;
  byte bVar14;
  undefined8 uStack_40;
  undefined8 uStack_38;
  long lStack_30;
  long lStack_20;
  long lStack_18;
  
  uStack_40 = CONCAT44(param_3,param_2);
  *(undefined4 *)(param_1 + 0x30) = param_3;
  *(undefined4 *)(param_1 + 0x34) = param_4;
  *(undefined1 *)(param_1 + 0x38) = param_5;
  uStack_38 = (ulong)CONCAT14(param_5,param_4);
  clock_gettime(1,&lStack_20);
  lStack_18 = lStack_18 + lStack_20 * 1000000000;
  iVar6 = 0xf;
  bVar3 = (byte)((ulong)lStack_18 >> 0x38);
  bVar9 = (byte)((ulong)lStack_18 >> 8);
  bVar10 = (byte)((ulong)lStack_18 >> 0x10);
  bVar11 = (byte)((ulong)lStack_18 >> 0x18);
  bVar12 = (byte)((ulong)lStack_18 >> 0x20);
  bVar13 = (byte)((ulong)lStack_18 >> 0x28);
  bVar14 = (byte)((ulong)lStack_18 >> 0x30);
  uStack_38 = CONCAT17((byte)(uStack_38 >> 0x38) ^ bVar3,
                       CONCAT16((byte)(uStack_38 >> 0x30) ^ bVar14,
                                CONCAT15((byte)(uStack_38 >> 0x28) ^ bVar13,
                                         CONCAT14((byte)(uStack_38 >> 0x20) ^ bVar12,
                                                  CONCAT13((byte)(uStack_38 >> 0x18) ^ bVar11,
                                                           CONCAT12((byte)(uStack_38 >> 0x10) ^
                                                                    bVar10,CONCAT11((byte)(uStack_38
                                                                                          >> 8) ^
                                                                                    bVar9,(byte)
                                                  uStack_38 ^ (byte)lStack_18)))))));
  uStack_40 = CONCAT17((byte)((ulong)uStack_40 >> 0x38) ^ bVar3,
                       CONCAT16((byte)((ulong)uStack_40 >> 0x30) ^ bVar14,
                                CONCAT15((byte)((ulong)uStack_40 >> 0x28) ^ bVar13,
                                         CONCAT14((byte)((ulong)uStack_40 >> 0x20) ^ bVar12,
                                                  CONCAT13((byte)((ulong)uStack_40 >> 0x18) ^ bVar11
                                                           ,CONCAT12((byte)((ulong)uStack_40 >> 0x10
                                                                           ) ^ bVar10,
                                                                     CONCAT11((byte)((ulong)
                                                  uStack_40 >> 8) ^ bVar9,
                                                  (byte)uStack_40 ^ (byte)lStack_18)))))));
  uVar8 = 0x17;
  lStack_30 = lStack_18;
  do {
    uVar4 = (uint)((ulong)lStack_18 >> 0x20);
    uVar5 = (uint)bVar3;
    switch(uVar8 & 0xffffffff) {
    case 0:
      uVar5 = (uint)(ushort)((ulong)lStack_18 >> 0x30);
      break;
    case 1:
      uVar5 = uVar4;
      break;
    case 2:
      uVar5 = (uint)((ulong)lStack_18 >> 0x18);
      break;
    case 3:
      uVar5 = (uint)lStack_18;
      break;
    case 4:
      break;
    case 5:
      uVar5 = (uint)((ulong)lStack_18 >> 8);
      break;
    case 6:
      uVar5 = (uint)((ulong)lStack_18 >> 0x10);
      break;
    case 7:
      uVar5 = uVar4 >> 8;
      break;
    default:
      lVar2 = (long)iVar6;
      iVar6 = iVar6 + -1;
      uVar5 = (uint)*(byte *)((long)&uStack_40 + lVar2);
    }
    *(char *)((long)&uStack_40 + uVar8) = (char)uVar5;
    bVar1 = 0 < (long)uVar8;
    uVar8 = uVar8 - 1;
  } while (bVar1);
  puVar7 = *(undefined8 **)(param_1 + 0x40);
  puVar7[2] = lStack_30;
  puVar7[1] = uStack_38;
  *puVar7 = uStack_40;
  return 0x18;
}

// ==== undefined Aska::Yayoi::MO::BattleProtocol::GetFunctionName(Aska::Yayoi::MO::BattleProtocol::FunctionID)
// _ZN4Aska5Yayoi2MO14BattleProtocol15GetFunctionNameENS2_10FunctionIDE @ 0159afb0

undefined * _ZN4Aska5Yayoi2MO14BattleProtocol15GetFunctionNameENS2_10FunctionIDE(int param_1)

{
  if (param_1 < -0x9213ce3) {
    if (param_1 < -0x452ca1d8) {
      if (param_1 < -0x5bf952c8) {
        if (param_1 < -0x6b74f8ea) {
          if (param_1 == -0x7ced59b4) {
            return &UNK_028126f8/*"kMissionEnd"*/;
          }
          if (param_1 == -0x7a99355b) {
            return &UNK_0281a490/*"kForceWinBattleStagePush"*/;
          }
          if (param_1 == -0x6d689a3d) {
            return &UNK_0281a524/*"kAIParameter"*/;
          }
        }
        else {
          if (param_1 == -0x6b74f8ea) {
            return &UNK_0281a5d1/*"kStartMultiplayRes"*/;
          }
          if (param_1 == -0x676fa26b) {
            return &UNK_0281a440/*"kStartBattleStage"*/;
          }
          if (param_1 == -0x5d99834f) {
            return &UNK_0281a6ab/*"kDisconnectNodePush"*/;
          }
        }
      }
      else if (param_1 < -0x514ce136) {
        if (param_1 == -0x5bf952c8) {
          return &UNK_0281a40c/*"kStamp"*/;
        }
        if (param_1 == -0x59d622ca) {
          return &UNK_0281a5f6/*"kUpdatePlayerListResult"*/;
        }
        if (param_1 == -0x5902e8eb) {
          return &UNK_0281a4cc/*"kSyncStartRushCombo"*/;
        }
      }
      else {
        if (param_1 == -0x514ce136) {
          return &UNK_0281a5c1/*"kStartMultiplay"*/;
        }
        if (param_1 == -0x4eaccd9f) {
          return &UNK_0281a6bf/*"kReconnect"*/;
        }
        if (param_1 == -0x4dbbcb2f) {
          return &UNK_0281a467/*"kFinishBattleStage"*/;
        }
      }
    }
    else if (param_1 < -0x2b37d136) {
      if (param_1 < -0x3e0cc534) {
        if (param_1 == -0x452ca1d8) {
          return &UNK_0281a4a9/*"kStartRushCombo"*/;
        }
        if (param_1 == -0x4353226f) {
          return &UNK_0281a50c/*"kSyncFinishRushComboRes"*/;
        }
        if (param_1 == -0x4269077e) {
          return &UNK_0281a5e4/*"kUpdatePlayerList"*/;
        }
      }
      else {
        if (param_1 == -0x3e0cc534) {
          return &UNK_0281a5ac/*"kMessage"*/;
        }
        if (param_1 == -0x3b874246) {
          return &UNK_0281a54f/*"kDebugMessageRes"*/;
        }
        if (param_1 == -0x2f5a7193) {
          return &UNK_0281a661/*"kChangePublicRoomRes"*/;
        }
      }
    }
    else if (param_1 < -0x1a3b64a6) {
      if (param_1 == -0x2b37d136) {
        return &UNK_0281a64f/*"kChangePublicRoom"*/;
      }
      if (param_1 == -0x1fbdcd68) {
        return &UNK_0281a595/*"kSnapshot"*/;
      }
      if (param_1 == -0x1d2dcd80) {
        return &UNK_0281a430/*"kMissionEndPush"*/;
      }
    }
    else {
      if (param_1 == -0x1a3b64a6) {
        return &UNK_0281a641/*"kExitRoomPush"*/;
      }
      if (param_1 == -0x14011ec9) {
        return &UNK_0281a4e0/*"kSyncStartRushComboRes"*/;
      }
      if (param_1 == -0xd2accff) {
        return &UNK_0281a62a/*"kExitRoom"*/;
      }
    }
  }
  else if (param_1 < 0x40db9f93) {
    if (param_1 < 0x10ce4f8f) {
      if (param_1 < 0x214d5cf) {
        if (param_1 == -0x9213ce3) {
          return &UNK_0281a619/*"kEnterRoomResult"*/;
        }
        if (param_1 == -0x7968181) {
          return &UNK_0281a560/*"kRequestProxy"*/;
        }
        if (param_1 == -0x1416904) {
          return &UNK_0281a582/*"kPacket"*/;
        }
      }
      else {
        if (param_1 == 0x214d5cf) {
          return &UNK_0281a4f7/*"kSyncFinishRushCombo"*/;
        }
        if (param_1 == 0x5aed673) {
          return &UNK_02812075/*"kError"*/;
        }
        if (param_1 == 0xf074e01) {
          return &UNK_0281a452/*"kStartBattleStageRes"*/;
        }
      }
    }
    else if (param_1 < 0x3764a958) {
      if (param_1 == 0x10ce4f8f) {
        return &UNK_0281a541/*"kDebugMessage"*/;
      }
      if (param_1 == 0x16287e9b) {
        return &UNK_0281a531/*"kAIParameterRes"*/;
      }
      if (param_1 == 0x3712ac8e) {
        return &UNK_0281a59f/*"kSnapshotRes"*/;
      }
    }
    else {
      if (param_1 == 0x3764a958) {
        return &UNK_0281a676/*"kUpdatePlayerStatus"*/;
      }
      if (param_1 == 0x38c5438d) {
        return &UNK_0281a413/*"kStampPush"*/;
      }
      if (param_1 == 0x399501b0) {
        return &UNK_0281a41e/*"kMissionStartPush"*/;
      }
    }
  }
  else if (param_1 < 0x57faa296) {
    if (param_1 < 0x44ac9b5c) {
      if (param_1 == 0x40db9f93) {
        return &UNK_02812724/*"kMissionContinueRes"*/;
      }
      if (param_1 == 0x43610d78) {
        return &UNK_0281a60e/*"kEnterRoom"*/;
      }
      if (param_1 == 0x440ed5b8) {
        return &UNK_0281a6a1/*"kRSSIPush"*/;
      }
    }
    else {
      if (param_1 == 0x44ac9b5c) {
        return &UNK_0281a634/*"kExitRoomRes"*/;
      }
      if (param_1 == 0x535410ce) {
        return &UNK_0281a58a/*"kPacketRes"*/;
      }
      if (param_1 == 0x5528c22a) {
        return &UNK_0281a56e/*"kRequestProxyResult"*/;
      }
    }
  }
  else if (param_1 < 0x7309d699) {
    if (param_1 == 0x57faa296) {
      return &UNK_0281a5b5/*"kMessageRes"*/;
    }
    if (param_1 == 0x5e3b82b4) {
      return &UNK_0281a68a/*"kUpdatePlayerStatusRes"*/;
    }
    if (param_1 == 0x62cd4997) {
      return &UNK_0281a4b9/*"kStartRushComboRes"*/;
    }
  }
  else {
    if (param_1 == 0x7309d699) {
      return &UNK_0281a47a/*"kFinishBattleStageRes"*/;
    }
    if (param_1 == 0x755cba3d) {
      return &UNK_02812713/*"kMissionContinue"*/;
    }
    if (param_1 == 0x7b1a9377) {
      return &UNK_0281206c/*"kInvalid"*/;
    }
  }
  return &UNK_029d2011;
}

// ==== undefined Aska::Yayoi::TProtocolSuite<Aska::Yayoi::MultiplayRPC::LobbyProtocol,Aska::Yayoi::NoProtocol<1>,Aska::Yayoi::NoProtocol<2>>::Open(Aska::Yayoi::Socket *,Aska::Yayoi::IPAddress const &,Aska::TSharedPointer<Aska::Yayoi::URI>)
// _ZN4Aska5Yayoi14TProtocolSuiteINS0_12MultiplayRPC13LobbyProtocolENS0_10NoProtocolILi1EEENS4_ILi2EEEE4OpenEPNS0_6SocketERKNS0_9IPAddressENS_14TSharedPointerINS0_3URIEEE @ 015b50fc

/* WARNING: Possible PIC construction at 0x015b5174: Changing call to branch */
/* WARNING: Possible PIC construction at 0x015b51e4: Changing call to branch */

void _ZN4Aska5Yayoi14TProtocolSuiteINS0_12MultiplayRPC13LobbyProtocolENS0_10NoProtocolILi1EEENS4_ILi2EEEE4OpenEPNS0_6SocketERKNS0_9IPAddressENS_14TSharedPointerINS0_3URIEEE
               (long *param_1,char *param_2,undefined8 param_3,undefined8 param_4,long *param_5)

{
  int iVar1;
  long lVar2;
  char cVar3;
  bool bVar4;
  int *piVar5;
  
  if (*param_2 == '\0') {
    lVar2 = *param_5;
    piVar5 = (int *)param_5[1];
    if (piVar5 == (int *)0x0) {
      *param_1 = 0;
joined_r0x015b5284:
      if (lVar2 != 0) {
        Aska::Yayoi::URI::DeleteBuffer()(lVar2);
        operator delete(void*)(lVar2);
      }
      if (piVar5 != (int *)0x0) goto code_r0x011cf7b0;
    }
    else {
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar5,0x10);
        if (bVar4) {
          *piVar5 = *piVar5 + 1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      *param_1 = 0;
      do {
        iVar1 = *piVar5;
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar5,0x10);
        if (bVar4) {
          *piVar5 = iVar1 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      if (iVar1 + -1 == 0) goto joined_r0x015b5284;
    }
    if (*param_1 < 0) {
      return;
    }
  }
  if (param_2[0xa0] == '\0') {
    lVar2 = *param_5;
    piVar5 = (int *)param_5[1];
    if (piVar5 == (int *)0x0) {
      *param_1 = -0x3ba;
joined_r0x015b5298:
      if (lVar2 != 0) {
        Aska::Yayoi::URI::DeleteBuffer()(lVar2);
        operator delete(void*)(lVar2);
      }
      if (piVar5 != (int *)0x0) goto code_r0x011cf7b0;
    }
    else {
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar5,0x10);
        if (bVar4) {
          *piVar5 = *piVar5 + 1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      *param_1 = -0x3ba;
      do {
        iVar1 = *piVar5;
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar5,0x10);
        if (bVar4) {
          *piVar5 = iVar1 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      if (iVar1 + -1 == 0) goto joined_r0x015b5298;
    }
    if (*param_1 < 0) {
      return;
    }
  }
  if (param_2[0xa1] == '\0') {
    lVar2 = *param_5;
    piVar5 = (int *)param_5[1];
    if (piVar5 == (int *)0x0) {
      *param_1 = -0x3ba;
    }
    else {
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar5,0x10);
        if (bVar4) {
          *piVar5 = *piVar5 + 1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      *param_1 = -0x3ba;
      do {
        iVar1 = *piVar5;
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar5,0x10);
        if (bVar4) {
          *piVar5 = iVar1 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      if (iVar1 + -1 != 0) {
        return;
      }
    }
    if (lVar2 != 0) {
      Aska::Yayoi::URI::DeleteBuffer()(lVar2);
      operator delete(void*)(lVar2);
    }
    if (piVar5 != (int *)0x0) {
code_r0x011cf7b0:
      (*(code *)PTR__ZN4Aska18TSharedPointerCode13DeleteCounterEPi_02c9fbc8)(piVar5);
      return;
    }
  }
  return;
}

// ==== undefined Aska::Yayoi::MultiplayRPC::LobbyProtocol::Serialize(Aska::Yayoi::MultiplayRPC::LobbyProtocoledData *,signed * *,unsigned long,void const *,unsigned long,unsigned long *)
// _ZN4Aska5Yayoi12MultiplayRPC13LobbyProtocol9SerializeEPNS1_19LobbyProtocoledDataEPPamPKvmPm @ 022f8aa4

void _ZN4Aska5Yayoi12MultiplayRPC13LobbyProtocol9SerializeEPNS1_19LobbyProtocoledDataEPPamPKvmPm
               (undefined8 *param_1,undefined8 param_2,long param_3,undefined8 *param_4,
               ulong param_5,undefined8 param_6,long param_7,ulong *param_8)

{
  undefined8 uVar1;
  ulong uVar2;
  
  if (param_7 == 0) {
    uVar2 = (ulong)*(uint *)(param_3 + 0x24);
    if (param_5 < uVar2) {
      uVar1 = 0xfffffffffffffc15;
    }
    else {
      memcpy(*param_4,*(undefined8 *)(param_3 + 0x40),uVar2);
      uVar1 = 0;
      *param_8 = uVar2;
    }
  }
  else {
    uVar1 = 0xfffffffffffffc4b;
  }
  *param_1 = uVar1;
  return;
}

// ==== undefined Aska::Yayoi::MultiplayRPC::LobbyProtocol::Deserialize(signed const *,unsigned long,unsigned long *,Aska::Yayoi::MultiplayRPC::LobbyProtocoledData *,Aska::Status &)
// _ZN4Aska5Yayoi12MultiplayRPC13LobbyProtocol11DeserializeEPKamPmPNS1_19LobbyProtocoledDataERNS_6StatusE @ 022f8afc

undefined8
_ZN4Aska5Yayoi12MultiplayRPC13LobbyProtocol11DeserializeEPKamPmPNS1_19LobbyProtocoledDataERNS_6StatusE
          (long param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5,
          long *param_6)

{
  long lStack_28;
  
  Aska::Yayoi::MultiplayRPC::LobbyProtocoledData::Deserialize(signed char const*, unsigned long*, unsigned long)(&lStack_28,param_5,param_2,param_4,param_3);
  *param_6 = lStack_28;
  if (lStack_28 < 0) {
    param_5 = 0;
    *(undefined8 *)(param_1 + 0x90) = *(undefined8 *)(param_1 + 0x98);
  }
  else {
    *(undefined8 *)(param_1 + 0x98) = *(undefined8 *)(param_1 + 0x90);
  }
  return param_5;
}

// ==== undefined Aska::Yayoi::MultiplayRPC::LobbyProtocol::CheckRecast(Aska::Yayoi::MultiplayRPC::LobbyProtocol::FunctionID,long)
// _ZN4Aska5Yayoi12MultiplayRPC13LobbyProtocol11CheckRecastENS2_10FunctionIDEl @ 022f8e84

undefined8 _ZN4Aska5Yayoi12MultiplayRPC13LobbyProtocol11CheckRecastENS2_10FunctionIDEl(void)

{
  return 1;
}

// ==== undefined Aska::Yayoi::MultiplayRPC::LobbyProtocoledData::_read_header(signed *,unsigned int)
// _ZN4Aska5Yayoi12MultiplayRPC19LobbyProtocoledData12_read_headerEPaj @ 022f8ef4

void _ZN4Aska5Yayoi12MultiplayRPC19LobbyProtocoledData12_read_headerEPaj
               (undefined8 *param_1,long param_2,byte *param_3,int param_4)

{
  ulong uVar1;
  ulong uVar2;
  
  uVar1 = (ulong)param_3[4] << 0x38 | (ulong)*param_3 << 0x30 | (ulong)param_3[7] << 0x28 |
          (ulong)param_3[1] << 0x20 | (ulong)param_3[2] << 0x18 | (ulong)param_3[6] << 0x10 |
          (ulong)param_3[3] | (ulong)param_3[5] << 8;
  uVar2 = *(ulong *)(param_3 + 8) ^ uVar1;
  uVar1 = *(ulong *)(param_3 + 0x10) ^ uVar1;
  *(int *)(param_2 + 0x30) = (int)(uVar2 >> 0x20);
  *(int *)(param_2 + 0x34) = (int)uVar1;
  *(int *)(param_2 + 0x24) = (int)uVar2 + param_4;
  *(char *)(param_2 + 0x38) = (char)(uVar1 >> 0x20);
  *param_1 = 0;
  return;
}

// ==== undefined Aska::Yayoi::MultiplayRPC::LobbyProtocoledData::_write_header(unsigned int,Aska::Yayoi::MultiplayRPC::LobbyProtocol::FunctionID,unsigned int,signed)
// _ZN4Aska5Yayoi12MultiplayRPC19LobbyProtocoledData13_write_headerEjNS1_13LobbyProtocol10FunctionIDEja @ 022f92a0

undefined8
_ZN4Aska5Yayoi12MultiplayRPC19LobbyProtocoledData13_write_headerEjNS1_13LobbyProtocol10FunctionIDEja
          (long param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined1 param_5)

{
  bool bVar1;
  long lVar2;
  byte bVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  undefined8 *puVar7;
  ulong uVar8;
  byte bVar9;
  byte bVar10;
  byte bVar11;
  byte bVar12;
  byte bVar13;
  byte bVar14;
  undefined8 uStack_40;
  undefined8 uStack_38;
  long lStack_30;
  long lStack_20;
  long lStack_18;
  
  uStack_40 = CONCAT44(param_3,param_2);
  *(undefined4 *)(param_1 + 0x30) = param_3;
  *(undefined4 *)(param_1 + 0x34) = param_4;
  *(undefined1 *)(param_1 + 0x38) = param_5;
  uStack_38 = (ulong)CONCAT14(param_5,param_4);
  clock_gettime(1,&lStack_20);
  lStack_18 = lStack_18 + lStack_20 * 1000000000;
  iVar6 = 0xf;
  bVar3 = (byte)((ulong)lStack_18 >> 0x38);
  bVar9 = (byte)((ulong)lStack_18 >> 8);
  bVar10 = (byte)((ulong)lStack_18 >> 0x10);
  bVar11 = (byte)((ulong)lStack_18 >> 0x18);
  bVar12 = (byte)((ulong)lStack_18 >> 0x20);
  bVar13 = (byte)((ulong)lStack_18 >> 0x28);
  bVar14 = (byte)((ulong)lStack_18 >> 0x30);
  uStack_38 = CONCAT17((byte)(uStack_38 >> 0x38) ^ bVar3,
                       CONCAT16((byte)(uStack_38 >> 0x30) ^ bVar14,
                                CONCAT15((byte)(uStack_38 >> 0x28) ^ bVar13,
                                         CONCAT14((byte)(uStack_38 >> 0x20) ^ bVar12,
                                                  CONCAT13((byte)(uStack_38 >> 0x18) ^ bVar11,
                                                           CONCAT12((byte)(uStack_38 >> 0x10) ^
                                                                    bVar10,CONCAT11((byte)(uStack_38
                                                                                          >> 8) ^
                                                                                    bVar9,(byte)
                                                  uStack_38 ^ (byte)lStack_18)))))));
  uStack_40 = CONCAT17((byte)((ulong)uStack_40 >> 0x38) ^ bVar3,
                       CONCAT16((byte)((ulong)uStack_40 >> 0x30) ^ bVar14,
                                CONCAT15((byte)((ulong)uStack_40 >> 0x28) ^ bVar13,
                                         CONCAT14((byte)((ulong)uStack_40 >> 0x20) ^ bVar12,
                                                  CONCAT13((byte)((ulong)uStack_40 >> 0x18) ^ bVar11
                                                           ,CONCAT12((byte)((ulong)uStack_40 >> 0x10
                                                                           ) ^ bVar10,
                                                                     CONCAT11((byte)((ulong)
                                                  uStack_40 >> 8) ^ bVar9,
                                                  (byte)uStack_40 ^ (byte)lStack_18)))))));
  uVar8 = 0x17;
  lStack_30 = lStack_18;
  do {
    uVar4 = (uint)((ulong)lStack_18 >> 0x20);
    uVar5 = (uint)bVar3;
    switch(uVar8 & 0xffffffff) {
    case 0:
      uVar5 = (uint)(ushort)((ulong)lStack_18 >> 0x30);
      break;
    case 1:
      uVar5 = uVar4;
      break;
    case 2:
      uVar5 = (uint)((ulong)lStack_18 >> 0x18);
      break;
    case 3:
      uVar5 = (uint)lStack_18;
      break;
    case 4:
      break;
    case 5:
      uVar5 = (uint)((ulong)lStack_18 >> 8);
      break;
    case 6:
      uVar5 = (uint)((ulong)lStack_18 >> 0x10);
      break;
    case 7:
      uVar5 = uVar4 >> 8;
      break;
    default:
      lVar2 = (long)iVar6;
      iVar6 = iVar6 + -1;
      uVar5 = (uint)*(byte *)((long)&uStack_40 + lVar2);
    }
    *(char *)((long)&uStack_40 + uVar8) = (char)uVar5;
    bVar1 = 0 < (long)uVar8;
    uVar8 = uVar8 - 1;
  } while (bVar1);
  puVar7 = *(undefined8 **)(param_1 + 0x40);
  puVar7[2] = lStack_30;
  puVar7[1] = uStack_38;
  *puVar7 = uStack_40;
  return 0x18;
}

// ==== undefined Aska::Yayoi::MultiplayRPC::LobbyProtocol::GetFunctionName(Aska::Yayoi::MultiplayRPC::LobbyProtocol::FunctionID)
// _ZN4Aska5Yayoi12MultiplayRPC13LobbyProtocol15GetFunctionNameENS2_10FunctionIDE @ 022fadec

undefined *
_ZN4Aska5Yayoi12MultiplayRPC13LobbyProtocol15GetFunctionNameENS2_10FunctionIDE(int param_1)

{
  if (param_1 < 0x5aed673) {
    if (param_1 < -0x17042556) {
      if (param_1 == -0x57102278) {
        return &UNK_029d3bf0/*"kUpdateRoomInfo"*/;
      }
      if (param_1 == -0x33779874) {
        return &UNK_029d3bdd/*"kGetRoomListResult"*/;
      }
      if (param_1 == -0x1c565ad8) {
        return &UNK_029d3c16/*"kAutomatch"*/;
      }
    }
    else if (param_1 < -0x101e124a) {
      if (param_1 == -0x17042556) {
        return &UNK_029d3bbf/*"kCloseRoomResult"*/;
      }
      if (param_1 == -0x153bdfff) {
        return &UNK_029d3ba2/*"kCreateRoomResult"*/;
      }
    }
    else {
      if (param_1 == -0x101e124a) {
        return &UNK_029d3bb4/*"kCloseRoom"*/;
      }
      if (param_1 == -0x4a2f28d) {
        return &UNK_029d3b78/*"kEnterLobby"*/;
      }
    }
  }
  else if (param_1 < 0x4e466d87) {
    if (param_1 == 0x5aed673) {
      return &UNK_02812075/*"kError"*/;
    }
    if (param_1 == 0x1fed00e2) {
      return &UNK_029d3c21/*"kAutomatchResult"*/;
    }
    if (param_1 == 0x2ddf640d) {
      return &UNK_029d3bd0/*"kGetRoomList"*/;
    }
  }
  else if (param_1 < 0x6b177840) {
    if (param_1 == 0x4e466d87) {
      return &UNK_029d3b84/*"kEnterLobbyResult"*/;
    }
    if (param_1 == 0x6a1b49a5) {
      return &UNK_029d3b96/*"kCreateRoom"*/;
    }
  }
  else {
    if (param_1 == 0x6b177840) {
      return &UNK_029d3c00/*"kUpdateRoomInfoResult"*/;
    }
    if (param_1 == 0x7b1a9377) {
      return &UNK_0281206c/*"kInvalid"*/;
    }
  }
  return &UNK_029d2011;
}

