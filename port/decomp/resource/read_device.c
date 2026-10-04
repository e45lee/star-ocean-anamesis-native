// port/decomp/resource/read_device.c: Ghidra decompiles for the resource subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-04 06:13 UTC: tools/decomp.sh '--into' 'resource/read_device' 'Aska::BaseReadDevice::' 'Aska::DiscReadDevice::' 'Aska::DirectReadDevice::' 'Aska::FileReadManager::'

// ==== Aska::FileReadManager::AddDevice(Aska::BaseReadDevice*)
// vaddr 0x1f20818 | ghidra 0x2020818 | size 148 | symbol _ZN4Aska15FileReadManager9AddDeviceEPNS_14BaseReadDeviceE | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska15FileReadManager9AddDeviceEPNS_14BaseReadDeviceE(long param_1,long param_2)

{
  long *plVar1;
  int iVar2;
  long *plVar3;
  long lVar5;
  long lVar6;
  long *plVar4;
  
  if (param_2 == 0) {
    return 0;
  }
  if (*(int *)(param_2 + 0x244) < 0) {
    return 0;
  }
  iVar2 = *(int *)(param_1 + 0x270);
  if (iVar2 < 3) {
    plVar1 = (long *)(param_1 + 600);
    *(int *)(param_1 + 0x270) = iVar2 + 1;
    plVar1[iVar2] = param_2;
    if (1 < *(int *)(param_1 + 0x270)) {
      plVar3 = plVar1 + (*(int *)(param_1 + 0x270) + -1);
      lVar5 = plVar1[*(int *)(param_1 + 0x270) + -1];
      do {
        plVar4 = plVar3 + -1;
        lVar6 = *plVar4;
        if ((lVar6 == 0) || (*(int *)(lVar6 + 0x240) < *(int *)(lVar5 + 0x240))) {
          plVar3[-1] = lVar5;
          *plVar3 = lVar6;
          lVar6 = lVar5;
        }
        plVar3 = plVar4;
        lVar5 = lVar6;
      } while (plVar1 < plVar4);
    }
    return 1;
  }
  return 0;
}

// ==== Aska::FileReadManager::EnableDirectReadDevice()
// vaddr 0x1f208ac | ghidra 0x20208ac | size 68 | symbol _ZN4Aska15FileReadManager22EnableDirectReadDeviceEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska15FileReadManager22EnableDirectReadDeviceEv(long param_1)

{
  ulong uVar1;
  
  uVar1 = Aska::BaseReadDevice::InitializeSub(int, int, int)(param_1 + 8,0xfa00002,0x100,0);
  if ((uVar1 & 1) != 0) {
    return 1;
  }
  Aska::BaseReadDevice::Finalize()(param_1 + 8);
  return 0;
}

// ==== Aska::FileReadManager::Finalize()
// vaddr 0x1f20938 | ghidra 0x2020938 | size 72 | symbol _ZN4Aska15FileReadManager8FinalizeEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska15FileReadManager8FinalizeEv(long param_1)

{
  int iVar1;
  undefined8 *puVar2;
  undefined8 *puVar3;
  
  iVar1 = *(int *)(param_1 + 0x270);
  if (0 < iVar1) {
    puVar2 = (undefined8 *)(param_1 + 600);
    do {
      Aska::BaseReadDevice::Finalize()(*puVar2);
      puVar3 = puVar2 + 1;
      *puVar2 = 0;
      puVar2 = puVar3;
    } while (puVar3 < (undefined8 *)(param_1 + (long)iVar1 * 8 + 600));
  }
  *(undefined4 *)(param_1 + 0x270) = 0;
  return;
}

// ==== Aska::FileReadManager::SortDevice()
// vaddr 0x1f20980 | ghidra 0x2020980 | size 84 | symbol _ZN4Aska15FileReadManager10SortDeviceEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska15FileReadManager10SortDeviceEv(long param_1)

{
  long *plVar1;
  long lVar3;
  long lVar4;
  long *plVar2;
  
  if (1 < *(int *)(param_1 + 0x270)) {
    plVar1 = (long *)(param_1 + 600U) + (*(int *)(param_1 + 0x270) + -1);
    lVar3 = *plVar1;
    do {
      plVar2 = plVar1 + -1;
      lVar4 = *plVar2;
      if ((lVar4 == 0) || (*(int *)(lVar4 + 0x240) < *(int *)(lVar3 + 0x240))) {
        plVar1[-1] = lVar3;
        *plVar1 = lVar4;
        lVar4 = lVar3;
      }
      plVar1 = plVar2;
      lVar3 = lVar4;
    } while ((long *)(param_1 + 600U) < plVar2);
  }
  return;
}

// ==== Aska::FileReadManager::RemoveDevice(Aska::BaseReadDevice*)
// vaddr 0x1f209d4 | ghidra 0x20209d4 | size 416 | symbol _ZN4Aska15FileReadManager12RemoveDeviceEPNS_14BaseReadDeviceE | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska15FileReadManager12RemoveDeviceEPNS_14BaseReadDeviceE(long param_1,long param_2)

{
  ulong uVar1;
  long *plVar2;
  int iVar3;
  long *plVar4;
  ulong uVar6;
  long lVar7;
  ulong uVar8;
  int iVar9;
  ulong uVar10;
  long lVar11;
  ulong uVar12;
  long lVar13;
  long lVar14;
  long *plVar5;
  
  if (param_2 == 0) {
    return 0;
  }
  if (*(int *)(param_2 + 0x244) < 0) {
    return 0;
  }
  iVar3 = *(int *)(param_1 + 0x270);
  if (iVar3 < 1) {
    return 1;
  }
  uVar1 = param_1 + (long)iVar3 * 8 + 600;
  if (uVar1 <= param_1 + 0x260U) {
    uVar1 = param_1 + 0x260U;
  }
  uVar1 = (uVar1 + (-0x259 - param_1) >> 3) + 1;
  plVar2 = (long *)(param_1 + 600);
  if ((uVar1 < 4) || (uVar6 = uVar1 & 0x3ffffffffffffffc, uVar6 == 0)) {
    iVar9 = 0;
    plVar4 = plVar2;
  }
  else {
    plVar4 = (long *)(param_1 + 600);
    uVar10 = 0;
    uVar12 = 0;
    uVar8 = uVar6;
    do {
      lVar7 = plVar4[1];
      lVar11 = *plVar4;
      lVar14 = plVar4[3];
      lVar13 = plVar4[2];
      if ((-(uint)(lVar11 == param_2) & 1) != 0) {
        *plVar4 = 0;
      }
      if ((-(uint)(lVar7 == param_2) & 1) != 0) {
        plVar4[1] = 0;
      }
      if ((-(uint)(lVar13 == param_2) & 1) != 0) {
        plVar4[2] = 0;
      }
      if ((-(uint)(lVar14 == param_2) & 1) != 0) {
        plVar4[3] = 0;
      }
      uVar10 = uVar10 ^ (uVar10 ^ CONCAT44((int)(uVar10 >> 0x20) + 1,(int)uVar10 + 1)) &
                        CONCAT44(-(uint)(lVar7 == param_2),-(uint)(lVar11 == param_2));
      uVar12 = uVar12 ^ (uVar12 ^ CONCAT44((int)(uVar12 >> 0x20) + 1,(int)uVar12 + 1)) &
                        CONCAT44(-(uint)(lVar14 == param_2),-(uint)(lVar13 == param_2));
      uVar8 = uVar8 - 4;
      plVar4 = plVar4 + 4;
    } while (uVar8 != 0);
    iVar9 = (int)uVar12 + (int)uVar10 + (int)(uVar12 >> 0x20) + (int)(uVar10 >> 0x20);
    plVar4 = (long *)(param_1 + uVar6 * 8 + 600);
    if (uVar1 == uVar6) goto code_r0x02020b08;
  }
  do {
    if (*plVar4 == param_2) {
      iVar9 = iVar9 + 1;
      *plVar4 = 0;
    }
    plVar4 = plVar4 + 1;
  } while (plVar4 < plVar2 + iVar3);
code_r0x02020b08:
  if (0 < iVar9) {
    iVar3 = *(int *)(param_1 + 0x270);
    if (1 < iVar3) {
      plVar4 = (long *)(param_1 + (long)(iVar3 + -1) * 8 + 600);
      lVar11 = *plVar4;
      do {
        plVar5 = plVar4 + -1;
        lVar7 = *plVar5;
        if ((lVar7 == 0) || (*(int *)(lVar7 + 0x240) < *(int *)(lVar11 + 0x240))) {
          plVar4[-1] = lVar11;
          *plVar4 = lVar7;
          lVar7 = lVar11;
        }
        plVar4 = plVar5;
        lVar11 = lVar7;
      } while (plVar2 < plVar5);
      iVar3 = *(int *)(param_1 + 0x270);
    }
    *(int *)(param_1 + 0x270) = iVar3 - iVar9;
  }
  return 1;
}

// ==== Aska::FileReadManager::RemoveDevice(int)
// vaddr 0x1f20b74 | ghidra 0x2020b74 | size 184 | symbol _ZN4Aska15FileReadManager12RemoveDeviceEi | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska15FileReadManager12RemoveDeviceEi(long param_1,int param_2)

{
  long *plVar1;
  int iVar2;
  int iVar3;
  long *plVar4;
  long lVar6;
  long lVar7;
  long *plVar5;
  
  if (param_2 < 0) {
    return 0;
  }
  iVar3 = *(int *)(param_1 + 0x270);
  if (0 < iVar3) {
    plVar1 = (long *)(param_1 + 600);
    iVar2 = 0;
    plVar4 = plVar1;
    do {
      if (*(int *)(*plVar4 + 0x244) == param_2) {
        iVar2 = iVar2 + 1;
        *plVar4 = 0;
      }
      plVar4 = plVar4 + 1;
    } while (plVar4 < plVar1 + iVar3);
    if (0 < iVar2) {
      iVar3 = *(int *)(param_1 + 0x270);
      if (1 < iVar3) {
        plVar4 = (long *)(param_1 + (long)(iVar3 + -1) * 8 + 600);
        lVar6 = *plVar4;
        do {
          plVar5 = plVar4 + -1;
          lVar7 = *plVar5;
          if ((lVar7 == 0) || (*(int *)(lVar7 + 0x240) < *(int *)(lVar6 + 0x240))) {
            plVar4[-1] = lVar6;
            *plVar4 = lVar7;
            lVar7 = lVar6;
          }
          plVar4 = plVar5;
          lVar6 = lVar7;
        } while (plVar1 < plVar5);
        iVar3 = *(int *)(param_1 + 0x270);
      }
      *(int *)(param_1 + 0x270) = iVar3 - iVar2;
    }
  }
  return 1;
}

// ==== Aska::FileReadManager::GetDevice(int)
// vaddr 0x1f20c2c | ghidra 0x2020c2c | size 72 | symbol _ZN4Aska15FileReadManager9GetDeviceEi | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska15FileReadManager9GetDeviceEi(long param_1,int param_2)

{
  int iVar1;
  long *plVar2;
  long *plVar3;
  
  if (*(int *)(param_1 + 0x270) < 1) {
    return 0;
  }
  plVar2 = (long *)(param_1 + 600);
  while( true ) {
    plVar3 = plVar2 + 1;
    iVar1 = *(int *)(*plVar2 + 0x244);
    if ((-1 < iVar1) && (iVar1 == param_2)) break;
    plVar2 = plVar3;
    if ((long *)(param_1 + (long)*(int *)(param_1 + 0x270) * 8 + 600U) <= plVar3) {
      return 0;
    }
  }
  return *plVar2;
}

// ==== Aska::FileReadManager::GetDeviceByIndex(int)
// vaddr 0x1f20c74 | ghidra 0x2020c74 | size 36 | symbol _ZN4Aska15FileReadManager16GetDeviceByIndexEi | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska15FileReadManager16GetDeviceByIndexEi(long param_1,int param_2)

{
  undefined8 uVar1;
  
  uVar1 = 0;
  if ((-1 < param_2) && (param_2 < *(int *)(param_1 + 0x270))) {
    uVar1 = *(undefined8 *)(param_1 + (long)param_2 * 8 + 600);
  }
  return uVar1;
}

// ==== Aska::FileReadManager::GetReadableDevice(int)
// vaddr 0x1f20c98 | ghidra 0x2020c98 | size 112 | symbol _ZN4Aska15FileReadManager17GetReadableDeviceEi | lib libSOA-3.7.0.so | 2026-10-04
long * _ZN4Aska15FileReadManager17GetReadableDeviceEi(long param_1,undefined4 param_2)

{
  int iVar1;
  ulong uVar2;
  long *plVar3;
  undefined8 *puVar4;
  
  iVar1 = *(int *)(param_1 + 0x270);
  if (0 < iVar1) {
    puVar4 = (undefined8 *)(param_1 + 600);
    do {
      plVar3 = (long *)*puVar4;
      if ((*(char *)((long)plVar3 + 0x249) != '\0') &&
         (uVar2 = (**(code **)(*plVar3 + 0x20))(plVar3,param_2), (uVar2 & 1) != 0)) {
        return plVar3;
      }
      puVar4 = puVar4 + 1;
    } while (puVar4 < (undefined8 *)(param_1 + (long)iVar1 * 8 + 600U));
  }
  return (long *)0x0;
}

// ==== Aska::FileReadManager::Read(int, unsigned char*, Aska::INotify*, unsigned long, unsigned long, int, int, bool)
// vaddr 0x1f20d08 | ghidra 0x2020d08 | size 224 | symbol _ZN4Aska15FileReadManager4ReadEiPhPNS_7INotifyEmmiib | lib libSOA-3.7.0.so | 2026-10-04
undefined4
_ZN4Aska15FileReadManager4ReadEiPhPNS_7INotifyEmmiib
          (long param_1,undefined4 param_2,long param_3,long param_4,undefined8 param_5,
          undefined8 param_6,undefined4 param_7,undefined4 param_8,byte param_9)

{
  int iVar1;
  ulong uVar2;
  long *plVar3;
  undefined8 *puVar4;
  undefined *puStack_88;
  undefined8 uStack_80;
  undefined8 uStack_78;
  long lStack_70;
  long lStack_68;
  undefined8 uStack_60;
  undefined8 uStack_58;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_40;
  undefined4 uStack_38;
  
  if ((param_3 != 0) && (param_4 != 0)) {
    uStack_80 = 0;
    uStack_78 = 0;
    puStack_88 = PTR__ZTVN4Aska11ReadRequestE_02cbdc38 + 0x10;
    uStack_38 = 1;
    uStack_48 = 0;
    if ((param_9 & 1) != 0) {
      uStack_48 = 2;
    }
    iVar1 = *(int *)(param_1 + 0x270);
    if (0 < iVar1) {
      puVar4 = (undefined8 *)(param_1 + 600);
      lStack_70 = param_3;
      lStack_68 = param_4;
      uStack_60 = param_5;
      uStack_58 = param_6;
      uStack_50 = param_7;
      uStack_4c = param_8;
      uStack_40 = param_2;
      do {
        plVar3 = (long *)*puVar4;
        if (((*(char *)((long)plVar3 + 0x249) != '\0') &&
            (uVar2 = (**(code **)(*plVar3 + 0x20))(plVar3,param_2), (uVar2 & 1) != 0)) &&
           (uVar2 = Aska::BaseReadDevice::Read(Aska::ReadRequest*)(plVar3,&puStack_88), (uVar2 & 1) != 0)) {
          return 1;
        }
        puVar4 = puVar4 + 1;
      } while (puVar4 < (undefined8 *)(param_1 + (long)iVar1 * 8 + 600U));
    }
  }
  return 0;
}

// ==== Aska::FileReadManager::Read(char const*, unsigned char*, Aska::INotify*, unsigned long, unsigned long, int, int, bool, bool)
// vaddr 0x1f20de8 | ghidra 0x2020de8 | size 48 | symbol _ZN4Aska15FileReadManager4ReadEPKcPhPNS_7INotifyEmmiibb | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska15FileReadManager4ReadEPKcPhPNS_7INotifyEmmiibb
          (long param_1,undefined8 param_2,long param_3,long param_4)

{
  undefined8 uVar1;
  
  if ((param_3 != 0) && (param_4 != 0)) {
    uVar1 = (*(code *)PTR__ZN4Aska16DirectReadDevice4ReadEPKcPhPNS_7INotifyEmmiibb_02cb2b90)
                      (param_1 + 8);
    return uVar1;
  }
  return 0;
}

// ==== Aska::FileReadManager::ReadGroup(int, int, unsigned char*, Aska::INotify*, unsigned long, int, int)
// vaddr 0x1f20e18 | ghidra 0x2020e18 | size 420 | symbol _ZN4Aska15FileReadManager9ReadGroupEiiPhPNS_7INotifyEmii | lib libSOA-3.7.0.so | 2026-10-04
undefined4
_ZN4Aska15FileReadManager9ReadGroupEiiPhPNS_7INotifyEmii
          (long param_1,int param_2,int param_3,long param_4,long param_5,undefined8 param_6,
          undefined4 param_7,undefined4 param_8)

{
  long *plVar1;
  int iVar2;
  ulong uVar3;
  long *plVar4;
  long *plVar5;
  undefined8 *puVar6;
  undefined *puStack_98;
  undefined8 uStack_90;
  undefined8 uStack_88;
  long lStack_80;
  long lStack_78;
  undefined8 uStack_70;
  undefined8 uStack_68;
  undefined4 uStack_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  int iStack_50;
  int iStack_48;
  
  if ((param_4 != 0) && (param_5 != 0)) {
    lStack_80 = param_4;
    lStack_78 = param_5;
    uStack_70 = param_6;
    uStack_60 = param_7;
    uStack_5c = param_8;
    iStack_50 = param_2;
    if (param_3 == 1) {
      uStack_90 = 0;
      uStack_88 = 0;
      uStack_68 = 0;
      puStack_98 = PTR__ZTVN4Aska11ReadRequestE_02cbdc38 + 0x10;
      iStack_48 = 1;
      uStack_58 = 0;
      iVar2 = *(int *)(param_1 + 0x270);
      if (0 < iVar2) {
        puVar6 = (undefined8 *)(param_1 + 600);
        do {
          plVar4 = (long *)*puVar6;
          if (((*(char *)((long)plVar4 + 0x249) != '\0') &&
              (uVar3 = (**(code **)(*plVar4 + 0x20))(plVar4,param_2), (uVar3 & 1) != 0)) &&
             (uVar3 = Aska::BaseReadDevice::Read(Aska::ReadRequest*)(plVar4,&puStack_98), (uVar3 & 1) != 0)) {
            return 1;
          }
          puVar6 = puVar6 + 1;
        } while (puVar6 < (undefined8 *)(param_1 + (long)iVar2 * 8 + 600U));
      }
    }
    else {
      uStack_90 = 0;
      uStack_88 = 0;
      uStack_68 = 0;
      puStack_98 = PTR__ZTVN4Aska11ReadRequestE_02cbdc38 + 0x10;
      uStack_58 = 0;
      if (0 < *(int *)(param_1 + 0x270)) {
        plVar4 = (long *)(param_1 + 600);
        plVar1 = plVar4 + *(int *)(param_1 + 0x270);
        iStack_48 = param_3;
        if (param_2 < param_3) {
          do {
            plVar5 = (long *)*plVar4;
            iVar2 = param_2;
            if (*(char *)((long)plVar5 + 0x249) != '\0') {
              do {
                uVar3 = (**(code **)(*plVar5 + 0x20))(plVar5,iVar2);
                if ((uVar3 & 1) == 0) goto code_r0x02020f60;
                iVar2 = iVar2 + 1;
              } while (iVar2 < param_3);
              uVar3 = Aska::BaseReadDevice::Read(Aska::ReadRequest*)(plVar5,&puStack_98);
              if ((uVar3 & 1) != 0) {
                return 1;
              }
            }
code_r0x02020f60:
            plVar4 = plVar4 + 1;
          } while (plVar4 < plVar1);
        }
        else {
          do {
            if ((*(char *)(*plVar4 + 0x249) != '\0') &&
               (uVar3 = Aska::BaseReadDevice::Read(Aska::ReadRequest*)(*plVar4,&puStack_98), (uVar3 & 1) != 0)) {
              return 1;
            }
            plVar4 = plVar4 + 1;
          } while (plVar4 < plVar1);
        }
      }
    }
  }
  return 0;
}

// ==== Aska::FileReadManager::FileExists(Aska::BaseReadDevice*, int, int) const
// vaddr 0x1f20fbc | ghidra 0x2020fbc | size 88 | symbol _ZNK4Aska15FileReadManager10FileExistsEPNS_14BaseReadDeviceEii | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZNK4Aska15FileReadManager10FileExistsEPNS_14BaseReadDeviceEii
          (undefined8 param_1,long *param_2,int param_3,int param_4)

{
  ulong uVar1;
  
  while( true ) {
    if (param_4 <= param_3) {
      return 1;
    }
    uVar1 = (**(code **)(*param_2 + 0x20))(param_2,param_3);
    if ((uVar1 & 1) == 0) break;
    param_3 = param_3 + 1;
  }
  return 0;
}

// ==== Aska::FileReadManager::CancelAll()
// vaddr 0x1f21014 | ghidra 0x2021014 | size 60 | symbol _ZN4Aska15FileReadManager9CancelAllEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska15FileReadManager9CancelAllEv(long param_1)

{
  int iVar1;
  undefined8 *puVar2;
  undefined8 *puVar3;
  
  iVar1 = *(int *)(param_1 + 0x270);
  if (0 < iVar1) {
    puVar2 = (undefined8 *)(param_1 + 600);
    do {
      puVar3 = puVar2 + 1;
      Aska::BaseReadDevice::CancelAll()(*puVar2);
      puVar2 = puVar3;
    } while (puVar3 < (undefined8 *)(param_1 + (long)iVar1 * 8 + 600U));
  }
  return;
}

// ==== Aska::FileReadManager::Cancel(int)
// vaddr 0x1f21050 | ghidra 0x2021050 | size 68 | symbol _ZN4Aska15FileReadManager6CancelEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska15FileReadManager6CancelEi(long param_1,undefined4 param_2)

{
  int iVar1;
  undefined8 *puVar2;
  undefined8 *puVar3;
  
  iVar1 = *(int *)(param_1 + 0x270);
  if (0 < iVar1) {
    puVar2 = (undefined8 *)(param_1 + 600);
    do {
      puVar3 = puVar2 + 1;
      Aska::BaseReadDevice::Cancel(int)(*puVar2,param_2);
      puVar2 = puVar3;
    } while (puVar3 < (undefined8 *)(param_1 + (long)iVar1 * 8 + 600U));
  }
  return;
}

// ==== Aska::FileReadManager::CancelByParam(int, unsigned char*, unsigned long, unsigned long, int)
// vaddr 0x1f21094 | ghidra 0x2021094 | size 116 | symbol _ZN4Aska15FileReadManager13CancelByParamEiPhmmi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska15FileReadManager13CancelByParamEiPhmmi
               (long param_1,undefined4 param_2,undefined8 param_3,undefined8 param_4,
               undefined8 param_5,undefined4 param_6)

{
  int iVar1;
  undefined8 *puVar2;
  undefined8 *puVar3;
  
  iVar1 = *(int *)(param_1 + 0x270);
  if (0 < iVar1) {
    puVar2 = (undefined8 *)(param_1 + 600);
    do {
      puVar3 = puVar2 + 1;
      Aska::BaseReadDevice::CancelByParam(int, unsigned char*, unsigned long, unsigned long, int)(*puVar2,param_2,param_3,param_4,param_5,param_6);
      puVar2 = puVar3;
    } while (puVar3 < (undefined8 *)(param_1 + (long)iVar1 * 8 + 600U));
  }
  return;
}

// ==== Aska::FileReadManager::IsEmpty() const
// vaddr 0x1f21108 | ghidra 0x2021108 | size 68 | symbol _ZNK4Aska15FileReadManager7IsEmptyEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska15FileReadManager7IsEmptyEv(long param_1)

{
  long *plVar1;
  long *plVar2;
  
  if (*(int *)(param_1 + 0x270) < 1) {
    return 1;
  }
  plVar1 = (long *)(param_1 + 600);
  do {
    plVar2 = plVar1 + 1;
    if (*(char *)(*plVar1 + 0x24a) == '\0') {
      return 0;
    }
    plVar1 = plVar2;
  } while (plVar2 < (long *)(param_1 + (long)*(int *)(param_1 + 0x270) * 8 + 600U));
  return 1;
}

// ==== Aska::FileReadManager::FileExists(int) const
// vaddr 0x1f2114c | ghidra 0x202114c | size 92 | symbol _ZNK4Aska15FileReadManager10FileExistsEi | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska15FileReadManager10FileExistsEi(long param_1,undefined4 param_2)

{
  int iVar1;
  ulong uVar2;
  undefined8 *puVar3;
  undefined8 *puVar4;
  
  iVar1 = *(int *)(param_1 + 0x270);
  if (0 < iVar1) {
    puVar3 = (undefined8 *)(param_1 + 600);
    do {
      puVar4 = puVar3 + 1;
      uVar2 = (**(code **)(*(long *)*puVar3 + 0x20))((long *)*puVar3,param_2);
      if ((uVar2 & 1) != 0) {
        return 1;
      }
      puVar3 = puVar4;
    } while (puVar4 < (undefined8 *)(param_1 + (long)iVar1 * 8 + 600U));
  }
  return 0;
}

// ==== Aska::FileReadManager::CalcFileLength(int) const
// vaddr 0x1f211a8 | ghidra 0x20211a8 | size 128 | symbol _ZNK4Aska15FileReadManager14CalcFileLengthEi | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska15FileReadManager14CalcFileLengthEi(long param_1,undefined4 param_2)

{
  int iVar1;
  ulong uVar2;
  undefined8 uVar3;
  long *plVar4;
  undefined8 *puVar5;
  undefined8 *puVar6;
  
  iVar1 = *(int *)(param_1 + 0x270);
  if (0 < iVar1) {
    puVar5 = (undefined8 *)(param_1 + 600);
    do {
      puVar6 = puVar5 + 1;
      plVar4 = (long *)*puVar5;
      uVar2 = (**(code **)(*plVar4 + 0x20))(plVar4,param_2);
      if ((uVar2 & 1) != 0) {
                    /* WARNING: Could not recover jumptable at 0x02021224. Too many branches */
                    /* WARNING: Treating indirect jump as call */
        uVar3 = (**(code **)(*plVar4 + 0x30))(plVar4,param_2);
        return uVar3;
      }
      puVar5 = puVar6;
    } while (puVar6 < (undefined8 *)(param_1 + (long)iVar1 * 8 + 600U));
  }
  return 0;
}

// ==== Aska::FileReadManager::CalcCompressedFileLength(int) const
// vaddr 0x1f21228 | ghidra 0x2021228 | size 128 | symbol _ZNK4Aska15FileReadManager24CalcCompressedFileLengthEi | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska15FileReadManager24CalcCompressedFileLengthEi(long param_1,undefined4 param_2)

{
  int iVar1;
  ulong uVar2;
  undefined8 uVar3;
  long *plVar4;
  undefined8 *puVar5;
  undefined8 *puVar6;
  
  iVar1 = *(int *)(param_1 + 0x270);
  if (0 < iVar1) {
    puVar5 = (undefined8 *)(param_1 + 600);
    do {
      puVar6 = puVar5 + 1;
      plVar4 = (long *)*puVar5;
      uVar2 = (**(code **)(*plVar4 + 0x20))(plVar4,param_2);
      if ((uVar2 & 1) != 0) {
                    /* WARNING: Could not recover jumptable at 0x020212a4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
        uVar3 = (**(code **)(*plVar4 + 0x38))(plVar4,param_2);
        return uVar3;
      }
      puVar5 = puVar6;
    } while (puVar6 < (undefined8 *)(param_1 + (long)iVar1 * 8 + 600U));
  }
  return 0;
}

// ==== Aska::FileReadManager::CalcGroupLength(int, int) const
// vaddr 0x1f212a8 | ghidra 0x20212a8 | size 184 | symbol _ZNK4Aska15FileReadManager15CalcGroupLengthEii | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska15FileReadManager15CalcGroupLengthEii(long param_1,int param_2,int param_3)

{
  int iVar1;
  undefined8 *puVar2;
  undefined8 uVar3;
  ulong uVar4;
  long *plVar5;
  undefined8 *puVar6;
  
  if (0 < *(int *)(param_1 + 0x270)) {
    puVar6 = (undefined8 *)(param_1 + 600);
    if (param_3 < 1) {
      plVar5 = (long *)*puVar6;
      if (plVar5 != (long *)0x0) {
code_r0x011dba70:
        uVar3 = (*(code *)PTR__ZNK4Aska14BaseReadDevice19LocalGetGroupLengthEii_02ca5d28)
                          (plVar5,param_2,param_3);
        return uVar3;
      }
    }
    else {
      puVar2 = puVar6 + *(int *)(param_1 + 0x270);
      do {
        plVar5 = (long *)*puVar6;
        iVar1 = param_2;
        while (uVar4 = (**(code **)(*plVar5 + 0x20))(plVar5,iVar1), (uVar4 & 1) != 0) {
          iVar1 = iVar1 + 1;
          if (param_3 + param_2 <= iVar1) goto code_r0x011dba70;
        }
        puVar6 = puVar6 + 1;
      } while (puVar6 < puVar2);
    }
  }
  return 0;
}

// ==== Aska::FileReadManager::FileExists(char const*, bool)
// vaddr 0x1f21360 | ghidra 0x2021360 | size 8 | symbol _ZN4Aska15FileReadManager10FileExistsEPKcb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska15FileReadManager10FileExistsEPKcb(undefined8 param_1,uint param_2)

{
  (*(code *)PTR__ZN4Aska4File9DoesExistEPKcb_02cb0700)(param_1,param_2 & 1);
  return;
}

// ==== Aska::FileReadManager::CalcFileLength(char const*, bool)
// vaddr 0x1f21368 | ghidra 0x2021368 | size 8 | symbol _ZN4Aska15FileReadManager14CalcFileLengthEPKcb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska15FileReadManager14CalcFileLengthEPKcb(undefined8 param_1,uint param_2)

{
  (*(code *)PTR__ZN4Aska4File11GetFileSizeEPKcb_02c9e240)(param_1,param_2 & 1);
  return;
}

// ==== Aska::FileReadManager::GetDirectReadAlign() const
// vaddr 0x1f21370 | ghidra 0x2021370 | size 8 | symbol _ZNK4Aska15FileReadManager18GetDirectReadAlignEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska15FileReadManager18GetDirectReadAlignEv(void)

{
  return 0x200;
}

// ==== Aska::BaseReadDevice::ReadRequestList::~ReadRequestList()
// vaddr 0x1f2138c | ghidra 0x202138c | size 4 | symbol _ZN4Aska14BaseReadDevice15ReadRequestListD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska14BaseReadDevice15ReadRequestListD0Ev(void)

{
  (*(code *)PTR__ZdlPv_02ca4758)();
  return;
}

// ==== Aska::BaseReadDevice::ReadRequestList::Add(Aska::ReadRequest*)
// vaddr 0x1f21390 | ghidra 0x2021390 | size 84 | symbol _ZN4Aska14BaseReadDevice15ReadRequestList3AddEPNS_11ReadRequestE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska14BaseReadDevice15ReadRequestList3AddEPNS_11ReadRequestE(long *param_1,long param_2)

{
  long *plVar1;
  
  plVar1 = (long *)param_1[2];
  if (param_1 + 1 != plVar1) {
    do {
      if (*(int *)(param_2 + 0x3c) <= *(int *)((long)plVar1 + 0x3c)) {
                    /* WARNING: Could not recover jumptable at 0x020213e0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
        (**(code **)(*param_1 + 0x20))(param_1,plVar1,param_2);
        return;
      }
      plVar1 = (long *)plVar1[1];
    } while (param_1 + 1 != plVar1);
  }
                    /* WARNING: Could not recover jumptable at 0x020213cc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*param_1 + 0x18))(param_1,param_2);
  return;
}

// ==== Aska::FileReadManager::~FileReadManager()
// vaddr 0x1f214b4 | ghidra 0x20214b4 | size 92 | symbol _ZN4Aska15FileReadManagerD2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska15FileReadManagerD2Ev(long *param_1)

{
  long lVar1;
  long *plVar2;
  long *plVar3;
  
  lVar1 = param_1[0x4e];
  *param_1 = (long)(PTR__ZTVN4Aska15FileReadManagerE_02cc3ae0 + 0x10);
  if (0 < (int)lVar1) {
    plVar2 = param_1 + 0x4b;
    do {
      Aska::BaseReadDevice::Finalize()(*plVar2);
      plVar3 = plVar2 + 1;
      *plVar2 = 0;
      plVar2 = plVar3;
    } while (plVar3 < param_1 + (long)(int)lVar1 + 0x4b);
  }
  *(undefined4 *)(param_1 + 0x4e) = 0;
  (*(code *)PTR__ZN4Aska14BaseReadDeviceD2Ev_02c91130)(param_1 + 1);
  return;
}

// ==== Aska::FileReadManager::~FileReadManager()
// vaddr 0x1f21510 | ghidra 0x2021510 | size 196 | symbol _ZN4Aska15FileReadManagerD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska15FileReadManagerD0Ev(long *param_1)

{
  undefined *puVar1;
  long lVar2;
  undefined *puVar3;
  long *plVar4;
  long *plVar5;
  
  lVar2 = param_1[0x4e];
  *param_1 = (long)(PTR__ZTVN4Aska15FileReadManagerE_02cc3ae0 + 0x10);
  if (0 < (int)lVar2) {
    plVar4 = param_1 + 0x4b;
    do {
      Aska::BaseReadDevice::Finalize()(*plVar4);
      plVar5 = plVar4 + 1;
      *plVar4 = 0;
      plVar4 = plVar5;
    } while (plVar5 < param_1 + (long)(int)lVar2 + 0x4b);
  }
  *(undefined4 *)(param_1 + 0x4e) = 0;
  plVar4 = param_1 + 1;
  *plVar4 = (long)(PTR__ZTVN4Aska14BaseReadDeviceE_02cbc9e0 + 0x10);
  Aska::BaseReadDevice::Finalize()(plVar4);
  Aska::Event::Exit()(param_1 + 0x3c);
  puVar3 = PTR__ZTVN4Aska13TDynamicQueueIPNS_11ReadRequestELb0EEE_02cbf580;
  *(undefined4 *)(param_1 + 0x37) = 0;
  param_1[0x38] = 0;
  puVar1 = PTR__ZTVN4Aska5TListINS_11ReadRequestEEE_02cbe550 + 0x10;
  param_1[0x35] = (long)(puVar3 + 0x10);
  param_1[0x36] = 1;
  param_1[0x28] = (long)puVar1;
  Aska::FastCriticalSection::~FastCriticalSection()(param_1 + 0x16);
  Aska::FastCriticalSection::~FastCriticalSection()(param_1 + 4);
  Aska::Thread::~Thread()(plVar4);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::BaseReadDevice::~BaseReadDevice()
// vaddr 0x1f215d4 | ghidra 0x20215d4 | size 108 | symbol _ZN4Aska14BaseReadDeviceD2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska14BaseReadDeviceD2Ev(long *param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  
  *param_1 = (long)(PTR__ZTVN4Aska14BaseReadDeviceE_02cbc9e0 + 0x10);
  Aska::BaseReadDevice::Finalize()();
  Aska::Event::Exit()(param_1 + 0x3b);
  puVar2 = PTR__ZTVN4Aska13TDynamicQueueIPNS_11ReadRequestELb0EEE_02cbf580;
  *(undefined4 *)(param_1 + 0x36) = 0;
  param_1[0x37] = 0;
  puVar1 = PTR__ZTVN4Aska5TListINS_11ReadRequestEEE_02cbe550 + 0x10;
  param_1[0x34] = (long)(puVar2 + 0x10);
  param_1[0x35] = 1;
  param_1[0x27] = (long)puVar1;
  Aska::FastCriticalSection::~FastCriticalSection()(param_1 + 0x15);
  Aska::FastCriticalSection::~FastCriticalSection()(param_1 + 3);
  (*(code *)PTR__ZN4Aska6ThreadD1Ev_02c9be08)(param_1);
  return;
}

// ==== Aska::BaseReadDevice::InitializeSub(int, int, int)
// vaddr 0x2221a0c | ghidra 0x2321a0c | size 824 | symbol _ZN4Aska14BaseReadDevice13InitializeSubEiii | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska14BaseReadDevice13InitializeSubEiii
          (long *param_1,int param_2,uint param_3,undefined4 param_4)

{
  long *plVar1;
  undefined *puVar2;
  long *plVar3;
  char cVar4;
  bool bVar5;
  ulong uVar6;
  long *plVar7;
  int iVar8;
  long *plVar9;
  int *piVar10;
  ulong uVar11;
  ulong uVar12;
  long lVar13;
  
  if (-1 < param_2) {
    *(int *)((long)param_1 + 0x244) = param_2;
    *(undefined4 *)(param_1 + 0x48) = param_4;
    uVar6 = (**(code **)(*param_1 + 0x88))(param_1);
    if ((uVar6 & 1) != 0) {
      plVar7 = (long *)operator new[](unsigned long, std::nothrow_t const&)(-(ulong)(param_3 >> 0x1f) & 0xffffff8000000000 |
                                       (ulong)param_3 << 7,PTR__ZSt7nothrow_02cb9a80);
      param_1[0x39] = (long)plVar7;
      if (plVar7 == (long *)0x0) {
        return 0;
      }
      lVar13 = (long)(int)param_3;
      plVar9 = plVar7 + lVar13 * 0xb;
      *(undefined4 *)(param_1 + 0x3a) = 0;
      *(uint *)((long)param_1 + 0x1d4) = param_3;
      param_1[0x38] = (long)(plVar9 + lVar13);
      plVar1 = param_1 + 0x1c;
      iVar8 = 0;
      do {
        while ((int)*plVar1 == -1) {
          cVar4 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(plVar1,0x10);
          if (bVar5) {
            *(int *)plVar1 = 0;
            cVar4 = ExclusiveMonitorsStatus();
          }
          if (cVar4 == '\0') goto code_r0x02321b50;
        }
        ClearExclusiveLocal();
        bVar5 = iVar8 < 0x1ff;
        iVar8 = iVar8 + 1;
      } while (bVar5);
      piVar10 = (int *)((long)param_1 + 0xe4);
      do {
        cVar4 = '\x01';
        bVar5 = (bool)ExclusiveMonitorPass(piVar10,0x10);
        if (bVar5) {
          *piVar10 = *piVar10 + 1;
          cVar4 = ExclusiveMonitorsStatus();
        }
      } while (cVar4 != '\0');
      do {
        if ((int)*plVar1 != -1) {
          ClearExclusiveLocal();
          do {
            uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x24);
            if ((uVar6 & 1) == 0) {
              do {
                cVar4 = '\x01';
                bVar5 = (bool)ExclusiveMonitorPass(piVar10,0x10);
                if (bVar5) {
                  *piVar10 = *piVar10 + -1;
                  cVar4 = ExclusiveMonitorsStatus();
                }
              } while (cVar4 != '\0');
              Aska::Thread::Sleep(unsigned int)(1);
            }
            else {
              Aska::Semaphore::Wait() const(param_1 + 0x24);
            }
            do {
              cVar4 = '\x01';
              bVar5 = (bool)ExclusiveMonitorPass(piVar10,0x10);
              if (bVar5) {
                *piVar10 = *piVar10 + 1;
                cVar4 = ExclusiveMonitorsStatus();
              }
            } while (cVar4 != '\0');
            while ((int)*plVar1 == -1) {
              cVar4 = '\x01';
              bVar5 = (bool)ExclusiveMonitorPass(plVar1,0x10);
              if (bVar5) {
                *(int *)plVar1 = 0;
                cVar4 = ExclusiveMonitorsStatus();
              }
              if (cVar4 == '\0') goto code_r0x02321b40;
            }
            ClearExclusiveLocal();
          } while( true );
        }
        cVar4 = '\x01';
        bVar5 = (bool)ExclusiveMonitorPass(plVar1,0x10);
        if (bVar5) {
          *(int *)plVar1 = 0;
          cVar4 = ExclusiveMonitorsStatus();
        }
      } while (cVar4 != '\0');
code_r0x02321b40:
      do {
        cVar4 = '\x01';
        bVar5 = (bool)ExclusiveMonitorPass(piVar10,0x10);
        if (bVar5) {
          *piVar10 = *piVar10 + -1;
          cVar4 = ExclusiveMonitorsStatus();
        }
      } while (cVar4 != '\0');
code_r0x02321b50:
      DataMemoryBarrier(2,3);
      if (((int)param_3 < 1) || (plVar9 == (long *)0x0)) {
        DataMemoryBarrier(2,3);
        *(undefined4 *)(param_1 + 0x1c) = 0xffffffff;
        DataMemoryBarrier(2,3);
        piVar10 = (int *)((long)param_1 + 0xe4);
        if (*piVar10 < 0x15) {
          return 0;
        }
        do {
          cVar4 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(piVar10,0x10);
          if (bVar5) {
            *piVar10 = *piVar10 + -1;
            cVar4 = ExclusiveMonitorsStatus();
          }
        } while (cVar4 != '\0');
        uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x24);
        if ((uVar6 & 1) == 0) {
          return 0;
        }
        Aska::Semaphore::Signal() const(param_1 + 0x24);
        return 0;
      }
      param_1[0x37] = (long)plVar9;
      *(uint *)(param_1 + 0x36) = param_3;
      param_1[0x35] = 1;
      if (plVar7 < plVar9) {
        puVar2 = PTR__ZTVN4Aska11ReadRequestE_02cbdc38 + 0x10;
        do {
          plVar7[1] = 0;
          plVar7[2] = 0;
          *plVar7 = (long)puVar2;
          if (*(uint *)((long)param_1 + 0x1ac) != *(uint *)(param_1 + 0x35)) {
            *(long **)(param_1[0x37] + (ulong)*(uint *)(param_1 + 0x35) * 8) = plVar7;
            iVar8 = 0;
            if ((int)param_1[0x35] + 1U < *(uint *)(param_1 + 0x36)) {
              iVar8 = (int)param_1[0x35] + 1;
            }
            *(int *)(param_1 + 0x35) = iVar8;
          }
          plVar7 = plVar7 + 0xb;
        } while (plVar7 < plVar9);
      }
      if (0 < (int)param_3) {
        plVar9 = (long *)param_1[0x38];
        plVar1 = plVar9 + lVar13 * 4;
        plVar7 = plVar9 + 4;
        plVar3 = plVar1;
        if (plVar1 <= plVar7) {
          plVar3 = plVar7;
        }
        uVar6 = ((long)plVar3 + ~(ulong)plVar9 >> 5) + 1;
        if ((1 < uVar6) && (uVar11 = uVar6 & 0xffffffffffffffe, uVar11 != 0)) {
          plVar9 = plVar9 + uVar11 * 4;
          puVar2 = PTR__ZTVN4Aska14BaseReadDevice16DecompressNotifyE_02cc3a38 + 0x10;
          uVar12 = uVar11;
          do {
            plVar7[-4] = (long)puVar2;
            *plVar7 = (long)puVar2;
            uVar12 = uVar12 - 2;
            plVar7 = plVar7 + 8;
          } while (uVar12 != 0);
          if (uVar6 == uVar11) goto code_r0x02321c48;
        }
        puVar2 = PTR__ZTVN4Aska14BaseReadDevice16DecompressNotifyE_02cc3a38 + 0x10;
        do {
          plVar7 = plVar9 + 4;
          *plVar9 = (long)puVar2;
          plVar9 = plVar7;
        } while (plVar7 < plVar1);
      }
code_r0x02321c48:
      DataMemoryBarrier(2,3);
      *(undefined4 *)(param_1 + 0x1c) = 0xffffffff;
      DataMemoryBarrier(2,3);
      piVar10 = (int *)((long)param_1 + 0xe4);
      if (0x14 < *piVar10) {
        do {
          cVar4 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(piVar10,0x10);
          if (bVar5) {
            *piVar10 = *piVar10 + -1;
            cVar4 = ExclusiveMonitorsStatus();
          }
        } while (cVar4 != '\0');
        uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x24);
        if ((uVar6 & 1) != 0) {
          Aska::Semaphore::Signal() const(param_1 + 0x24);
        }
      }
      uVar6 = Aska::Event::Create(bool, bool)(param_1 + 0x3b,0,0);
      if ((uVar6 & 1) != 0) {
        uVar6 = Aska::Thread::Create(bool, int, int, bool)(param_1,0,0x80,0x3000,1);
        if ((uVar6 & 1) != 0) {
          *(undefined1 *)((long)param_1 + 0x249) = 1;
          return 1;
        }
        return 0;
      }
      return 0;
    }
  }
  return 0;
}

// ==== Aska::BaseReadDevice::Finalize()
// vaddr 0x2221d44 | ghidra 0x2321d44 | size 84 | symbol _ZN4Aska14BaseReadDevice8FinalizeEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska14BaseReadDevice8FinalizeEv(long param_1)

{
  *(undefined1 *)(param_1 + 0x249) = 0;
  Aska::BaseReadDevice::CancelAll()();
  *(undefined1 *)(param_1 + 0x24b) = 1;
  Aska::Event::Set() const(param_1 + 0x1d8);
  Aska::Thread::WaitEnd()(param_1);
  Aska::Event::Exit()(param_1 + 0x1d8);
  if (*(long *)(param_1 + 0x1c8) != 0) {
    operator delete[](void*)();
    *(undefined8 *)(param_1 + 0x1c8) = 0;
  }
  return;
}

// ==== Aska::BaseReadDevice::CancelAll()
// vaddr 0x2221d98 | ghidra 0x2321d98 | size 376 | symbol _ZN4Aska14BaseReadDevice9CancelAllEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska14BaseReadDevice9CancelAllEv(long param_1)

{
  int *piVar1;
  char cVar2;
  bool bVar3;
  ulong uVar4;
  int iVar5;
  long lVar6;
  int *piVar7;
  
  piVar7 = (int *)(param_1 + 0x50);
  iVar5 = 0;
  do {
    while (*piVar7 == -1) {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar7,0x10);
      if (bVar3) {
        *piVar7 = 0;
        cVar2 = ExclusiveMonitorsStatus();
      }
      if (cVar2 == '\0') goto code_r0x02321e78;
    }
    ClearExclusiveLocal();
    bVar3 = iVar5 < 0x1ff;
    iVar5 = iVar5 + 1;
  } while (bVar3);
  piVar1 = (int *)(param_1 + 0x54);
  do {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar3) {
      *piVar1 = *piVar1 + 1;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
  do {
    if (*piVar7 != -1) {
      ClearExclusiveLocal();
      do {
        uVar4 = Aska::Semaphore::IsReady() const(param_1 + 0x90);
        if ((uVar4 & 1) == 0) {
          do {
            cVar2 = '\x01';
            bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
            if (bVar3) {
              *piVar1 = *piVar1 + -1;
              cVar2 = ExclusiveMonitorsStatus();
            }
          } while (cVar2 != '\0');
          Aska::Thread::Sleep(unsigned int)(1);
        }
        else {
          Aska::Semaphore::Wait() const(param_1 + 0x90);
        }
        do {
          cVar2 = '\x01';
          bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar3) {
            *piVar1 = *piVar1 + 1;
            cVar2 = ExclusiveMonitorsStatus();
          }
        } while (cVar2 != '\0');
        while (*piVar7 == -1) {
          cVar2 = '\x01';
          bVar3 = (bool)ExclusiveMonitorPass(piVar7,0x10);
          if (bVar3) {
            *piVar7 = 0;
            cVar2 = ExclusiveMonitorsStatus();
          }
          if (cVar2 == '\0') goto code_r0x02321e68;
        }
        ClearExclusiveLocal();
      } while( true );
    }
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar7,0x10);
    if (bVar3) {
      *piVar7 = 0;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
code_r0x02321e68:
  do {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar3) {
      *piVar1 = *piVar1 + -1;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
code_r0x02321e78:
  DataMemoryBarrier(2,3);
  for (lVar6 = *(long *)(param_1 + 0x150); param_1 + 0x140 != lVar6; lVar6 = *(long *)(lVar6 + 0x10)
      ) {
    *(uint *)(lVar6 + 0x40) = *(uint *)(lVar6 + 0x40) | 1;
  }
  *(undefined1 *)(param_1 + 0x24c) = 1;
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_1 + 0x50) = 0xffffffff;
  DataMemoryBarrier(2,3);
  piVar7 = (int *)(param_1 + 0x54);
  if (0x14 < *piVar7) {
    do {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar7,0x10);
      if (bVar3) {
        *piVar7 = *piVar7 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    uVar4 = Aska::Semaphore::IsReady() const(param_1 + 0x90);
    if ((uVar4 & 1) != 0) {
      (*(code *)PTR__ZNK4Aska9Semaphore6SignalEv_02c96cd0)(param_1 + 0x90);
      return;
    }
  }
  return;
}

// ==== Aska::BaseReadDevice::Read(Aska::ReadRequest*)
// vaddr 0x2221f10 | ghidra 0x2321f10 | size 1048 | symbol _ZN4Aska14BaseReadDevice4ReadEPNS_11ReadRequestE | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska14BaseReadDevice4ReadEPNS_11ReadRequestE(long *param_1,long param_2)

{
  long *plVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  char cVar5;
  bool bVar6;
  undefined8 uVar7;
  long lVar8;
  undefined8 *puVar9;
  ulong uVar10;
  long *plVar11;
  uint uVar12;
  int *piVar13;
  int iVar14;
  long lVar15;
  undefined8 uStack_48;
  undefined1 uStack_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  
  if ((*(uint *)(param_2 + 0x40) >> 3 & 1) == 0) {
    if (*(int *)(param_2 + 0x50) < 1) goto code_r0x02321f70;
    iVar14 = *(int *)(param_2 + 0x48);
    lVar15 = 0;
    iVar2 = *(int *)(param_2 + 0x50) + iVar14;
    do {
      lVar8 = (**(code **)(*param_1 + 0x30))(param_1,iVar14);
      iVar14 = iVar14 + 1;
      lVar15 = lVar8 + lVar15;
      uVar7 = uStack_48;
    } while (iVar14 < iVar2);
  }
  else {
    lVar15 = (**(code **)(*param_1 + 0x80))(param_1,param_2);
    uVar7 = uStack_48;
  }
  if (lVar15 != 0) {
    uStack_48._4_4_ = (undefined4)((ulong)uVar7 >> 0x20);
    plVar1 = param_1 + 0x1c;
    iVar14 = 0;
code_r0x02321fc0:
    if ((int)*plVar1 == -1) {
      cVar5 = '\x01';
      bVar6 = (bool)ExclusiveMonitorPass(plVar1,0x10);
      if (bVar6) {
        *(int *)plVar1 = 0;
        cVar5 = ExclusiveMonitorsStatus();
      }
      if (cVar5 == '\0') goto code_r0x02322088;
      goto code_r0x02321fc0;
    }
    ClearExclusiveLocal();
    bVar6 = iVar14 < 0x1ff;
    iVar14 = iVar14 + 1;
    if (bVar6) goto code_r0x02321fc0;
    piVar13 = (int *)((long)param_1 + 0xe4);
    do {
      cVar5 = '\x01';
      bVar6 = (bool)ExclusiveMonitorPass(piVar13,0x10);
      if (bVar6) {
        *piVar13 = *piVar13 + 1;
        cVar5 = ExclusiveMonitorsStatus();
      }
    } while (cVar5 != '\0');
    do {
      if ((int)*plVar1 != -1) {
        ClearExclusiveLocal();
        uStack_48 = uVar7;
        do {
          uVar10 = Aska::Semaphore::IsReady() const(param_1 + 0x24);
          if ((uVar10 & 1) == 0) {
            do {
              cVar5 = '\x01';
              bVar6 = (bool)ExclusiveMonitorPass(piVar13,0x10);
              if (bVar6) {
                *piVar13 = *piVar13 + -1;
                cVar5 = ExclusiveMonitorsStatus();
              }
            } while (cVar5 != '\0');
            Aska::Thread::Sleep(unsigned int)(1);
          }
          else {
            Aska::Semaphore::Wait() const(param_1 + 0x24);
          }
          do {
            cVar5 = '\x01';
            bVar6 = (bool)ExclusiveMonitorPass(piVar13,0x10);
            if (bVar6) {
              *piVar13 = *piVar13 + 1;
              cVar5 = ExclusiveMonitorsStatus();
            }
          } while (cVar5 != '\0');
          while ((int)*plVar1 == -1) {
            cVar5 = '\x01';
            bVar6 = (bool)ExclusiveMonitorPass(plVar1,0x10);
            if (bVar6) {
              *(int *)plVar1 = 0;
              cVar5 = ExclusiveMonitorsStatus();
            }
            uVar7 = uStack_48;
            if (cVar5 == '\0') goto code_r0x02322078;
          }
          ClearExclusiveLocal();
        } while( true );
      }
      cVar5 = '\x01';
      bVar6 = (bool)ExclusiveMonitorPass(plVar1,0x10);
      if (bVar6) {
        *(int *)plVar1 = 0;
        cVar5 = ExclusiveMonitorsStatus();
      }
    } while (cVar5 != '\0');
code_r0x02322078:
    do {
      uStack_48 = uVar7;
      cVar5 = '\x01';
      bVar6 = (bool)ExclusiveMonitorPass(piVar13,0x10);
      if (bVar6) {
        *piVar13 = *piVar13 + -1;
        cVar5 = ExclusiveMonitorsStatus();
      }
      uVar7 = uStack_48;
    } while (cVar5 != '\0');
code_r0x02322088:
    DataMemoryBarrier(2,3);
    uVar12 = *(uint *)((long)param_1 + 0x1ac);
    uVar4 = *(uint *)(param_1 + 0x35);
    uVar3 = 0;
    if (uVar12 + 1 < *(uint *)(param_1 + 0x36)) {
      uVar3 = uVar12 + 1;
    }
    if (uVar3 != uVar4) {
      *(uint *)((long)param_1 + 0x1ac) = uVar3;
      uVar12 = uVar3;
    }
    lVar15 = *(long *)(param_1[0x37] + (ulong)uVar12 * 8);
    DataMemoryBarrier(2,3);
    *(undefined4 *)(param_1 + 0x1c) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar13 = (int *)((long)param_1 + 0xe4);
    if (0x14 < *piVar13) {
      do {
        cVar5 = '\x01';
        bVar6 = (bool)ExclusiveMonitorPass(piVar13,0x10);
        if (bVar6) {
          *piVar13 = *piVar13 + -1;
          cVar5 = ExclusiveMonitorsStatus();
        }
      } while (cVar5 != '\0');
      uVar10 = Aska::Semaphore::IsReady() const(param_1 + 0x24);
      if ((uVar10 & 1) != 0) {
        Aska::Semaphore::Signal() const(param_1 + 0x24);
      }
    }
    if (uVar3 == uVar4) {
      puVar9 = *(undefined8 **)(param_2 + 0x20);
      if (puVar9 != (undefined8 *)0x0) {
        uStack_3c = *(undefined4 *)(param_2 + 0x48);
        uStack_48 = CONCAT44(uStack_48._4_4_,0xfffffc61);
        uStack_40 = 0;
        uStack_38 = 0;
        (**(code **)*puVar9)(puVar9,&uStack_48);
        return 0;
      }
      return 0;
    }
    plVar1 = param_1 + 10;
    *(undefined8 *)(lVar15 + 0x18) = *(undefined8 *)(param_2 + 0x18);
    *(undefined8 *)(lVar15 + 0x20) = *(undefined8 *)(param_2 + 0x20);
    *(undefined8 *)(lVar15 + 0x28) = *(undefined8 *)(param_2 + 0x28);
    *(undefined8 *)(lVar15 + 0x30) = *(undefined8 *)(param_2 + 0x30);
    *(undefined4 *)(lVar15 + 0x38) = *(undefined4 *)(param_2 + 0x38);
    *(undefined4 *)(lVar15 + 0x3c) = *(undefined4 *)(param_2 + 0x3c);
    *(uint *)(lVar15 + 0x40) = *(uint *)(param_2 + 0x40) & 0xfffffffe;
    *(undefined8 *)(lVar15 + 0x48) = *(undefined8 *)(param_2 + 0x48);
    *(undefined4 *)(lVar15 + 0x50) = *(undefined4 *)(param_2 + 0x50);
    iVar14 = 0;
code_r0x02322168:
    do {
      if ((int)*plVar1 != -1) {
        ClearExclusiveLocal();
        bVar6 = iVar14 < 0x1ff;
        iVar14 = iVar14 + 1;
        if (bVar6) goto code_r0x02322168;
        piVar13 = (int *)((long)param_1 + 0x54);
        do {
          cVar5 = '\x01';
          bVar6 = (bool)ExclusiveMonitorPass(piVar13,0x10);
          if (bVar6) {
            *piVar13 = *piVar13 + 1;
            cVar5 = ExclusiveMonitorsStatus();
          }
        } while (cVar5 != '\0');
        do {
          if ((int)*plVar1 != -1) {
            ClearExclusiveLocal();
            do {
              uVar10 = Aska::Semaphore::IsReady() const(param_1 + 0x12);
              if ((uVar10 & 1) == 0) {
                do {
                  cVar5 = '\x01';
                  bVar6 = (bool)ExclusiveMonitorPass(piVar13,0x10);
                  if (bVar6) {
                    *piVar13 = *piVar13 + -1;
                    cVar5 = ExclusiveMonitorsStatus();
                  }
                } while (cVar5 != '\0');
                Aska::Thread::Sleep(unsigned int)(1);
              }
              else {
                Aska::Semaphore::Wait() const(param_1 + 0x12);
              }
              do {
                cVar5 = '\x01';
                bVar6 = (bool)ExclusiveMonitorPass(piVar13,0x10);
                if (bVar6) {
                  *piVar13 = *piVar13 + 1;
                  cVar5 = ExclusiveMonitorsStatus();
                }
              } while (cVar5 != '\0');
              while ((int)*plVar1 == -1) {
                cVar5 = '\x01';
                bVar6 = (bool)ExclusiveMonitorPass(plVar1,0x10);
                if (bVar6) {
                  *(int *)plVar1 = 0;
                  cVar5 = ExclusiveMonitorsStatus();
                }
                if (cVar5 == '\0') goto code_r0x02322254;
              }
              ClearExclusiveLocal();
            } while( true );
          }
          cVar5 = '\x01';
          bVar6 = (bool)ExclusiveMonitorPass(plVar1,0x10);
          if (bVar6) {
            *(int *)plVar1 = 0;
            cVar5 = ExclusiveMonitorsStatus();
          }
        } while (cVar5 != '\0');
code_r0x02322254:
        do {
          cVar5 = '\x01';
          bVar6 = (bool)ExclusiveMonitorPass(piVar13,0x10);
          if (bVar6) {
            *piVar13 = *piVar13 + -1;
            cVar5 = ExclusiveMonitorsStatus();
          }
        } while (cVar5 != '\0');
code_r0x02322264:
        DataMemoryBarrier(2,3);
        plVar11 = (long *)param_1[0x29];
        plVar1 = param_1 + 0x27;
        if (param_1 + 0x28 != plVar11) {
          do {
            if (*(int *)(lVar15 + 0x3c) <= *(int *)((long)plVar11 + 0x3c)) {
              (**(code **)(*plVar1 + 0x20))(plVar1,plVar11,lVar15);
              goto code_r0x023222bc;
            }
            plVar11 = (long *)plVar11[1];
          } while (param_1 + 0x28 != plVar11);
        }
        (**(code **)(*plVar1 + 0x18))(plVar1,lVar15);
code_r0x023222bc:
        *(undefined1 *)((long)param_1 + 0x24a) = 0;
        DataMemoryBarrier(2,3);
        *(undefined4 *)(param_1 + 10) = 0xffffffff;
        DataMemoryBarrier(2,3);
        piVar13 = (int *)((long)param_1 + 0x54);
        if (0x14 < *piVar13) {
          do {
            cVar5 = '\x01';
            bVar6 = (bool)ExclusiveMonitorPass(piVar13,0x10);
            if (bVar6) {
              *piVar13 = *piVar13 + -1;
              cVar5 = ExclusiveMonitorsStatus();
            }
          } while (cVar5 != '\0');
          uVar10 = Aska::Semaphore::IsReady() const(param_1 + 0x12);
          if ((uVar10 & 1) != 0) {
            Aska::Semaphore::Signal() const(param_1 + 0x12);
          }
        }
        Aska::Event::Set() const(param_1 + 0x3b);
        return 1;
      }
      cVar5 = '\x01';
      bVar6 = (bool)ExclusiveMonitorPass(plVar1,0x10);
      if (bVar6) {
        *(int *)plVar1 = 0;
        cVar5 = ExclusiveMonitorsStatus();
      }
      if (cVar5 == '\0') goto code_r0x02322264;
    } while( true );
  }
code_r0x02321f70:
  puVar9 = *(undefined8 **)(param_2 + 0x20);
  if (puVar9 != (undefined8 *)0x0) {
    uStack_3c = *(undefined4 *)(param_2 + 0x48);
    uStack_38 = *(undefined4 *)(param_2 + 0x50);
    uStack_48 = 0;
    uStack_40 = 0;
    (**(code **)*puVar9)(puVar9,&uStack_48);
  }
  return 1;
}

// ==== Aska::BaseReadDevice::LocalGetGroupLength(int, int) const
// vaddr 0x2222328 | ghidra 0x2322328 | size 92 | symbol _ZNK4Aska14BaseReadDevice19LocalGetGroupLengthEii | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK4Aska14BaseReadDevice19LocalGetGroupLengthEii(long *param_1,int param_2,int param_3)

{
  long lVar1;
  long lVar2;
  
  lVar2 = 0;
  if (0 < param_3) {
    param_3 = param_3 + param_2;
    do {
      lVar1 = (**(code **)(*param_1 + 0x30))(param_1,param_2);
      param_2 = param_2 + 1;
      lVar2 = lVar1 + lVar2;
    } while (param_2 < param_3);
  }
  return lVar2;
}

// ==== Aska::BaseReadDevice::Cancel(int)
// vaddr 0x2222384 | ghidra 0x2322384 | size 392 | symbol _ZN4Aska14BaseReadDevice6CancelEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska14BaseReadDevice6CancelEi(long param_1,int param_2)

{
  int *piVar1;
  char cVar2;
  bool bVar3;
  ulong uVar4;
  int iVar5;
  long lVar6;
  int *piVar7;
  
  piVar7 = (int *)(param_1 + 0x50);
  iVar5 = 0;
code_r0x023223a0:
  do {
    if (*piVar7 != -1) {
      ClearExclusiveLocal();
      bVar3 = iVar5 < 0x1ff;
      iVar5 = iVar5 + 1;
      if (bVar3) goto code_r0x023223a0;
      piVar1 = (int *)(param_1 + 0x54);
      do {
        cVar2 = '\x01';
        bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
        if (bVar3) {
          *piVar1 = *piVar1 + 1;
          cVar2 = ExclusiveMonitorsStatus();
        }
      } while (cVar2 != '\0');
      do {
        if (*piVar7 != -1) {
          ClearExclusiveLocal();
          do {
            uVar4 = Aska::Semaphore::IsReady() const(param_1 + 0x90);
            if ((uVar4 & 1) == 0) {
              do {
                cVar2 = '\x01';
                bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
                if (bVar3) {
                  *piVar1 = *piVar1 + -1;
                  cVar2 = ExclusiveMonitorsStatus();
                }
              } while (cVar2 != '\0');
              Aska::Thread::Sleep(unsigned int)(1);
            }
            else {
              Aska::Semaphore::Wait() const(param_1 + 0x90);
            }
            do {
              cVar2 = '\x01';
              bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
              if (bVar3) {
                *piVar1 = *piVar1 + 1;
                cVar2 = ExclusiveMonitorsStatus();
              }
            } while (cVar2 != '\0');
            while (*piVar7 == -1) {
              cVar2 = '\x01';
              bVar3 = (bool)ExclusiveMonitorPass(piVar7,0x10);
              if (bVar3) {
                *piVar7 = 0;
                cVar2 = ExclusiveMonitorsStatus();
              }
              if (cVar2 == '\0') goto code_r0x02322458;
            }
            ClearExclusiveLocal();
          } while( true );
        }
        cVar2 = '\x01';
        bVar3 = (bool)ExclusiveMonitorPass(piVar7,0x10);
        if (bVar3) {
          *piVar7 = 0;
          cVar2 = ExclusiveMonitorsStatus();
        }
      } while (cVar2 != '\0');
code_r0x02322458:
      do {
        cVar2 = '\x01';
        bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
        if (bVar3) {
          *piVar1 = *piVar1 + -1;
          cVar2 = ExclusiveMonitorsStatus();
        }
      } while (cVar2 != '\0');
code_r0x02322468:
      DataMemoryBarrier(2,3);
      for (lVar6 = *(long *)(param_1 + 0x150); param_1 + 0x140 != lVar6;
          lVar6 = *(long *)(lVar6 + 0x10)) {
        if (*(int *)(lVar6 + 0x38) == param_2) {
          *(uint *)(lVar6 + 0x40) = *(uint *)(lVar6 + 0x40) | 1;
          *(undefined1 *)(param_1 + 0x24c) = 1;
        }
      }
      DataMemoryBarrier(2,3);
      *(undefined4 *)(param_1 + 0x50) = 0xffffffff;
      DataMemoryBarrier(2,3);
      piVar7 = (int *)(param_1 + 0x54);
      if (0x14 < *piVar7) {
        do {
          cVar2 = '\x01';
          bVar3 = (bool)ExclusiveMonitorPass(piVar7,0x10);
          if (bVar3) {
            *piVar7 = *piVar7 + -1;
            cVar2 = ExclusiveMonitorsStatus();
          }
        } while (cVar2 != '\0');
        uVar4 = Aska::Semaphore::IsReady() const(param_1 + 0x90);
        if ((uVar4 & 1) != 0) {
          (*(code *)PTR__ZNK4Aska9Semaphore6SignalEv_02c96cd0)(param_1 + 0x90);
          return;
        }
      }
      return;
    }
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar7,0x10);
    if (bVar3) {
      *piVar7 = 0;
      cVar2 = ExclusiveMonitorsStatus();
    }
    if (cVar2 == '\0') goto code_r0x02322468;
  } while( true );
}

// ==== Aska::BaseReadDevice::CancelByParam(int, unsigned char*, unsigned long, unsigned long, int)
// vaddr 0x222250c | ghidra 0x232250c | size 696 | symbol _ZN4Aska14BaseReadDevice13CancelByParamEiPhmmi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska14BaseReadDevice13CancelByParamEiPhmmi
               (long param_1,int param_2,long param_3,long param_4,long param_5,int param_6)

{
  int *piVar1;
  long lVar2;
  char cVar3;
  bool bVar4;
  ulong uVar5;
  int iVar6;
  long lVar7;
  int *piVar8;
  
  piVar8 = (int *)(param_1 + 0x50);
  iVar6 = 0;
  do {
    while (*piVar8 == -1) {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
      if (bVar4) {
        *piVar8 = 0;
        cVar3 = ExclusiveMonitorsStatus();
      }
      if (cVar3 == '\0') goto code_r0x02322608;
    }
    ClearExclusiveLocal();
    bVar4 = iVar6 < 0x1ff;
    iVar6 = iVar6 + 1;
  } while (bVar4);
  piVar1 = (int *)(param_1 + 0x54);
  do {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar4) {
      *piVar1 = *piVar1 + 1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
  do {
    if (*piVar8 != -1) {
      ClearExclusiveLocal();
      do {
        uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0x90);
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
          Aska::Semaphore::Wait() const(param_1 + 0x90);
        }
        do {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar4) {
            *piVar1 = *piVar1 + 1;
            cVar3 = ExclusiveMonitorsStatus();
          }
        } while (cVar3 != '\0');
        while (*piVar8 == -1) {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
          if (bVar4) {
            *piVar8 = 0;
            cVar3 = ExclusiveMonitorsStatus();
          }
          if (cVar3 == '\0') goto code_r0x023225f8;
        }
        ClearExclusiveLocal();
      } while( true );
    }
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
    if (bVar4) {
      *piVar8 = 0;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
code_r0x023225f8:
  do {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar4) {
      *piVar1 = *piVar1 + -1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
code_r0x02322608:
  DataMemoryBarrier(2,3);
  lVar7 = *(long *)(param_1 + 0x150);
  lVar2 = param_1 + 0x140;
  if (lVar2 != lVar7) {
    if (param_2 < 1) {
      if (param_3 == 0) {
        do {
          if ((((param_4 == 0) || (*(long *)(lVar7 + 0x28) == param_4)) &&
              ((param_5 == 0 || (*(long *)(lVar7 + 0x30) == param_5)))) &&
             ((param_6 < 0 || (*(int *)(lVar7 + 0x3c) == param_6)))) {
            *(uint *)(lVar7 + 0x40) = *(uint *)(lVar7 + 0x40) | 1;
            *(undefined1 *)(param_1 + 0x24c) = 1;
          }
          lVar7 = *(long *)(lVar7 + 0x10);
        } while (lVar2 != lVar7);
      }
      else {
        do {
          if ((((*(long *)(lVar7 + 0x18) == param_3) &&
               ((param_4 == 0 || (*(long *)(lVar7 + 0x28) == param_4)))) &&
              ((param_5 == 0 || (*(long *)(lVar7 + 0x30) == param_5)))) &&
             ((param_6 < 0 || (*(int *)(lVar7 + 0x3c) == param_6)))) {
            *(uint *)(lVar7 + 0x40) = *(uint *)(lVar7 + 0x40) | 1;
            *(undefined1 *)(param_1 + 0x24c) = 1;
          }
          lVar7 = *(long *)(lVar7 + 0x10);
        } while (lVar2 != lVar7);
      }
    }
    else {
      do {
        if (((*(int *)(lVar7 + 0x48) == param_2) &&
            ((param_3 == 0 || (*(long *)(lVar7 + 0x18) == param_3)))) &&
           (((param_4 == 0 || (*(long *)(lVar7 + 0x28) == param_4)) &&
            (((param_5 == 0 || (*(long *)(lVar7 + 0x30) == param_5)) &&
             ((param_6 < 0 || (*(int *)(lVar7 + 0x3c) == param_6)))))))) {
          *(uint *)(lVar7 + 0x40) = *(uint *)(lVar7 + 0x40) | 1;
          *(undefined1 *)(param_1 + 0x24c) = 1;
        }
        lVar7 = *(long *)(lVar7 + 0x10);
      } while (lVar2 != lVar7);
    }
  }
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_1 + 0x50) = 0xffffffff;
  DataMemoryBarrier(2,3);
  piVar8 = (int *)(param_1 + 0x54);
  if (0x14 < *piVar8) {
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
      if (bVar4) {
        *piVar8 = *piVar8 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
    uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0x90);
    if ((uVar5 & 1) != 0) {
      (*(code *)PTR__ZNK4Aska9Semaphore6SignalEv_02c96cd0)(param_1 + 0x90);
      return;
    }
  }
  return;
}

// ==== Aska::BaseReadDevice::GetRequest()
// vaddr 0x22227c4 | ghidra 0x23227c4 | size 348 | symbol _ZN4Aska14BaseReadDevice10GetRequestEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska14BaseReadDevice10GetRequestEv(long param_1)

{
  int *piVar1;
  char cVar2;
  bool bVar3;
  ulong uVar4;
  int iVar5;
  int *piVar6;
  long lVar7;
  
  piVar6 = (int *)(param_1 + 0x50);
  iVar5 = 0;
  do {
    while (*piVar6 == -1) {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar6,0x10);
      if (bVar3) {
        *piVar6 = 0;
        cVar2 = ExclusiveMonitorsStatus();
      }
      if (cVar2 == '\0') goto code_r0x023228a4;
    }
    ClearExclusiveLocal();
    bVar3 = iVar5 < 0x1ff;
    iVar5 = iVar5 + 1;
  } while (bVar3);
  piVar1 = (int *)(param_1 + 0x54);
  do {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar3) {
      *piVar1 = *piVar1 + 1;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
  do {
    if (*piVar6 != -1) {
      ClearExclusiveLocal();
      do {
        uVar4 = Aska::Semaphore::IsReady() const(param_1 + 0x90);
        if ((uVar4 & 1) == 0) {
          do {
            cVar2 = '\x01';
            bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
            if (bVar3) {
              *piVar1 = *piVar1 + -1;
              cVar2 = ExclusiveMonitorsStatus();
            }
          } while (cVar2 != '\0');
          Aska::Thread::Sleep(unsigned int)(1);
        }
        else {
          Aska::Semaphore::Wait() const(param_1 + 0x90);
        }
        do {
          cVar2 = '\x01';
          bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar3) {
            *piVar1 = *piVar1 + 1;
            cVar2 = ExclusiveMonitorsStatus();
          }
        } while (cVar2 != '\0');
        while (*piVar6 == -1) {
          cVar2 = '\x01';
          bVar3 = (bool)ExclusiveMonitorPass(piVar6,0x10);
          if (bVar3) {
            *piVar6 = 0;
            cVar2 = ExclusiveMonitorsStatus();
          }
          if (cVar2 == '\0') goto code_r0x02322894;
        }
        ClearExclusiveLocal();
      } while( true );
    }
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar6,0x10);
    if (bVar3) {
      *piVar6 = 0;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
code_r0x02322894:
  do {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar3) {
      *piVar1 = *piVar1 + -1;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
code_r0x023228a4:
  DataMemoryBarrier(2,3);
  lVar7 = *(long *)(param_1 + 0x150);
  if (param_1 + 0x140 == lVar7) {
    lVar7 = 0;
    *(undefined1 *)(param_1 + 0x24a) = 1;
  }
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_1 + 0x50) = 0xffffffff;
  DataMemoryBarrier(2,3);
  piVar6 = (int *)(param_1 + 0x54);
  if (0x14 < *piVar6) {
    do {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar6,0x10);
      if (bVar3) {
        *piVar6 = *piVar6 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    uVar4 = Aska::Semaphore::IsReady() const(param_1 + 0x90);
    if ((uVar4 & 1) != 0) {
      Aska::Semaphore::Signal() const(param_1 + 0x90);
    }
  }
  return lVar7;
}

// ==== Aska::BaseReadDevice::Handler()
// vaddr 0x2222920 | ghidra 0x2322920 | size 788 | symbol _ZN4Aska14BaseReadDevice7HandlerEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska14BaseReadDevice7HandlerEv(long *param_1)

{
  long *plVar1;
  int *piVar2;
  long *plVar3;
  long *plVar4;
  int *piVar5;
  long *plVar6;
  char cVar7;
  bool bVar8;
  long *plVar9;
  ulong uVar10;
  int iVar11;
  long lVar12;
  long lVar13;
  
  Aska::Event::Wait(unsigned int) const(param_1 + 0x3b,0);
  if (*(char *)((long)param_1 + 0x24b) == '\0') {
    plVar1 = param_1 + 10;
    piVar2 = (int *)((long)param_1 + 0x54);
    plVar3 = param_1 + 0x12;
    plVar4 = param_1 + 0x1c;
    piVar5 = (int *)((long)param_1 + 0xe4);
    plVar6 = param_1 + 0x24;
code_r0x02322998:
    do {
      plVar9 = (long *)Aska::BaseReadDevice::GetRequest()(param_1);
      if (plVar9 != (long *)0x0) {
        (**(code **)(*param_1 + 0x90))(param_1,plVar9);
        iVar11 = 0;
        do {
          while ((int)*plVar1 != -1) {
            ClearExclusiveLocal();
            bVar8 = 0x1fe < iVar11;
            iVar11 = iVar11 + 1;
            if (bVar8) goto code_r0x023229e8;
          }
          cVar7 = '\x01';
          bVar8 = (bool)ExclusiveMonitorPass(plVar1,0x10);
          if (bVar8) {
            *(int *)plVar1 = 0;
            cVar7 = ExclusiveMonitorsStatus();
          }
        } while (cVar7 != '\0');
        goto code_r0x02322a78;
      }
      Aska::Event::Wait(unsigned int) const(param_1 + 0x3b,0);
    } while (*(char *)((long)param_1 + 0x24b) == '\0');
  }
  return;
code_r0x023229e8:
  do {
    cVar7 = '\x01';
    bVar8 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar8) {
      *piVar2 = *piVar2 + 1;
      cVar7 = ExclusiveMonitorsStatus();
    }
  } while (cVar7 != '\0');
  do {
    if ((int)*plVar1 != -1) {
      do {
        ClearExclusiveLocal();
        uVar10 = Aska::Semaphore::IsReady() const(plVar3);
        if ((uVar10 & 1) == 0) {
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
        else {
          Aska::Semaphore::Wait() const(plVar3);
        }
        do {
          cVar7 = '\x01';
          bVar8 = (bool)ExclusiveMonitorPass(piVar2,0x10);
          if (bVar8) {
            *piVar2 = *piVar2 + 1;
            cVar7 = ExclusiveMonitorsStatus();
          }
        } while (cVar7 != '\0');
        while ((int)*plVar1 == -1) {
          cVar7 = '\x01';
          bVar8 = (bool)ExclusiveMonitorPass(plVar1,0x10);
          if (bVar8) {
            *(int *)plVar1 = 0;
            cVar7 = ExclusiveMonitorsStatus();
          }
          if (cVar7 == '\0') goto code_r0x02322a68;
        }
      } while( true );
    }
    cVar7 = '\x01';
    bVar8 = (bool)ExclusiveMonitorPass(plVar1,0x10);
    if (bVar8) {
      *(int *)plVar1 = 0;
      cVar7 = ExclusiveMonitorsStatus();
    }
  } while (cVar7 != '\0');
code_r0x02322a68:
  do {
    cVar7 = '\x01';
    bVar8 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar8) {
      *piVar2 = *piVar2 + -1;
      cVar7 = ExclusiveMonitorsStatus();
    }
  } while (cVar7 != '\0');
code_r0x02322a78:
  DataMemoryBarrier(2,3);
  if (param_1 + 0x28 != plVar9) {
    lVar12 = plVar9[1];
    lVar13 = plVar9[2];
    if (lVar12 != 0) {
      *(long *)(lVar12 + 0x10) = lVar13;
    }
    if (lVar13 != 0) {
      *(long *)(lVar13 + 8) = lVar12;
    }
    if (0 < (int)param_1[0x33]) {
      *(int *)(param_1 + 0x33) = (int)param_1[0x33] + -1;
    }
    plVar9[1] = 0;
    plVar9[2] = 0;
  }
  DataMemoryBarrier(2,3);
  *(int *)plVar1 = -1;
  DataMemoryBarrier(2,3);
  if (0x14 < *piVar2) {
    do {
      cVar7 = '\x01';
      bVar8 = (bool)ExclusiveMonitorPass(piVar2,0x10);
      if (bVar8) {
        *piVar2 = *piVar2 + -1;
        cVar7 = ExclusiveMonitorsStatus();
      }
    } while (cVar7 != '\0');
    uVar10 = Aska::Semaphore::IsReady() const(plVar3);
    if ((uVar10 & 1) != 0) {
      Aska::Semaphore::Signal() const(plVar3);
    }
  }
  iVar11 = 0;
  do {
    while ((int)*plVar4 != -1) {
      ClearExclusiveLocal();
      bVar8 = 0x1fe < iVar11;
      iVar11 = iVar11 + 1;
      if (bVar8) goto code_r0x02322b1c;
    }
    cVar7 = '\x01';
    bVar8 = (bool)ExclusiveMonitorPass(plVar4,0x10);
    if (bVar8) {
      *(int *)plVar4 = 0;
      cVar7 = ExclusiveMonitorsStatus();
    }
  } while (cVar7 != '\0');
code_r0x02322bac:
  DataMemoryBarrier(2,3);
  if (*(uint *)((long)param_1 + 0x1ac) != *(uint *)(param_1 + 0x35)) {
    *(long **)(param_1[0x37] + (ulong)*(uint *)(param_1 + 0x35) * 8) = plVar9;
    iVar11 = 0;
    if ((int)param_1[0x35] + 1U < *(uint *)(param_1 + 0x36)) {
      iVar11 = (int)param_1[0x35] + 1;
    }
    *(int *)(param_1 + 0x35) = iVar11;
  }
  DataMemoryBarrier(2,3);
  *(int *)plVar4 = -1;
  DataMemoryBarrier(2,3);
  if (0x14 < *piVar5) {
    do {
      cVar7 = '\x01';
      bVar8 = (bool)ExclusiveMonitorPass(piVar5,0x10);
      if (bVar8) {
        *piVar5 = *piVar5 + -1;
        cVar7 = ExclusiveMonitorsStatus();
      }
    } while (cVar7 != '\0');
    uVar10 = Aska::Semaphore::IsReady() const(plVar6);
    if ((uVar10 & 1) != 0) {
      Aska::Semaphore::Signal() const(plVar6);
    }
  }
  goto code_r0x02322998;
code_r0x02322b1c:
  do {
    cVar7 = '\x01';
    bVar8 = (bool)ExclusiveMonitorPass(piVar5,0x10);
    if (bVar8) {
      *piVar5 = *piVar5 + 1;
      cVar7 = ExclusiveMonitorsStatus();
    }
  } while (cVar7 != '\0');
  do {
    if ((int)*plVar4 != -1) {
      do {
        ClearExclusiveLocal();
        uVar10 = Aska::Semaphore::IsReady() const(plVar6);
        if ((uVar10 & 1) == 0) {
          do {
            cVar7 = '\x01';
            bVar8 = (bool)ExclusiveMonitorPass(piVar5,0x10);
            if (bVar8) {
              *piVar5 = *piVar5 + -1;
              cVar7 = ExclusiveMonitorsStatus();
            }
          } while (cVar7 != '\0');
          Aska::Thread::Sleep(unsigned int)(1);
        }
        else {
          Aska::Semaphore::Wait() const(plVar6);
        }
        do {
          cVar7 = '\x01';
          bVar8 = (bool)ExclusiveMonitorPass(piVar5,0x10);
          if (bVar8) {
            *piVar5 = *piVar5 + 1;
            cVar7 = ExclusiveMonitorsStatus();
          }
        } while (cVar7 != '\0');
        while ((int)*plVar4 == -1) {
          cVar7 = '\x01';
          bVar8 = (bool)ExclusiveMonitorPass(plVar4,0x10);
          if (bVar8) {
            *(int *)plVar4 = 0;
            cVar7 = ExclusiveMonitorsStatus();
          }
          if (cVar7 == '\0') goto code_r0x02322b9c;
        }
      } while( true );
    }
    cVar7 = '\x01';
    bVar8 = (bool)ExclusiveMonitorPass(plVar4,0x10);
    if (bVar8) {
      *(int *)plVar4 = 0;
      cVar7 = ExclusiveMonitorsStatus();
    }
  } while (cVar7 != '\0');
code_r0x02322b9c:
  do {
    cVar7 = '\x01';
    bVar8 = (bool)ExclusiveMonitorPass(piVar5,0x10);
    if (bVar8) {
      *piVar5 = *piVar5 + -1;
      cVar7 = ExclusiveMonitorsStatus();
    }
  } while (cVar7 != '\0');
  goto code_r0x02322bac;
}

// ==== Aska::BaseReadDevice::Decompress(unsigned char*, unsigned char*, Aska::INotify*, unsigned long, int, bool)
// vaddr 0x2222c34 | ghidra 0x2322c34 | size 192 | symbol _ZN4Aska14BaseReadDevice10DecompressEPhS1_PNS_7INotifyEmib | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska14BaseReadDevice10DecompressEPhS1_PNS_7INotifyEmib
          (long param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5,
          undefined4 param_6,byte param_7)

{
  int iVar1;
  long lVar2;
  int iVar3;
  int iVar4;
  ulong uVar5;
  undefined8 uVar6;
  
  uVar5 = Aska::DecompressBase::IsCompressed(void const*)(param_2);
  if ((uVar5 & 1) == 0) {
    uVar6 = 0;
  }
  else {
    lVar2 = *(long *)(param_1 + 0x1c0) + (long)*(int *)(param_1 + 0x1d0) * 0x20;
    *(undefined8 *)(lVar2 + 8) = param_4;
    *(undefined8 *)(lVar2 + 0x10) = param_5;
    *(undefined4 *)(lVar2 + 0x18) = param_6;
    *(byte *)(lVar2 + 0x1c) = param_7 & 1;
    uVar6 = *(undefined8 *)PTR__ZN4Aska6Global18m_pDecompressQueueE_02cc0f20;
    while (uVar5 = Aska::DecompressQueue::Add(void const*, unsigned char*, int, Aska::INotify*)(uVar6,param_2,param_3,0,lVar2), (uVar5 & 1) == 0) {
      Aska::Thread::Sleep(unsigned int)(1);
    }
    iVar3 = *(int *)(param_1 + 0x1d4);
    uVar6 = 1;
    iVar1 = *(int *)(param_1 + 0x1d0) + 1;
    iVar4 = 0;
    if (iVar3 != 0) {
      iVar4 = iVar1 / iVar3;
    }
    *(int *)(param_1 + 0x1d0) = iVar1 - iVar4 * iVar3;
  }
  return uVar6;
}

// ==== Aska::BaseReadDevice::~BaseReadDevice()
// vaddr 0x2222cf4 | ghidra 0x2322cf4 | size 24 | symbol _ZN4Aska14BaseReadDeviceD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska14BaseReadDeviceD0Ev(undefined8 param_1)

{
  Aska::BaseReadDevice::~BaseReadDevice()();
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::BaseReadDevice::Initialize(int, int, int)
// vaddr 0x2222d0c | ghidra 0x2322d0c | size 112 | symbol _ZN4Aska14BaseReadDevice10InitializeEiii | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZN4Aska14BaseReadDevice10InitializeEiii(long param_1)

{
  ulong uVar1;
  undefined4 uVar2;
  
  uVar1 = Aska::BaseReadDevice::InitializeSub(int, int, int)();
  uVar2 = 1;
  if ((uVar1 & 1) == 0) {
    *(undefined1 *)(param_1 + 0x249) = 0;
    Aska::BaseReadDevice::CancelAll()(param_1);
    *(undefined1 *)(param_1 + 0x24b) = 1;
    Aska::Event::Set() const(param_1 + 0x1d8);
    Aska::Thread::WaitEnd()(param_1);
    Aska::Event::Exit()(param_1 + 0x1d8);
    if (*(long *)(param_1 + 0x1c8) == 0) {
      uVar2 = 0;
    }
    else {
      operator delete[](void*)();
      uVar2 = 0;
      *(undefined8 *)(param_1 + 0x1c8) = 0;
    }
  }
  return uVar2;
}

// ==== Aska::BaseReadDevice::FileExists(int) const
// vaddr 0x2222d7c | ghidra 0x2322d7c | size 8 | symbol _ZNK4Aska14BaseReadDevice10FileExistsEi | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska14BaseReadDevice10FileExistsEi(void)

{
  return 0;
}

// ==== Aska::BaseReadDevice::FileExists(int, int) const
// vaddr 0x2222d84 | ghidra 0x2322d84 | size 8 | symbol _ZNK4Aska14BaseReadDevice10FileExistsEii | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska14BaseReadDevice10FileExistsEii(void)

{
  return 0;
}

// ==== Aska::BaseReadDevice::CalcFileLength(int) const
// vaddr 0x2222d8c | ghidra 0x2322d8c | size 12 | symbol _ZNK4Aska14BaseReadDevice14CalcFileLengthEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK4Aska14BaseReadDevice14CalcFileLengthEi(long *param_1)

{
                    /* WARNING: Could not recover jumptable at 0x02322d94. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*param_1 + 0x78))();
  return;
}

// ==== Aska::BaseReadDevice::GetCompressedFileLength(int) const
// vaddr 0x2222d98 | ghidra 0x2322d98 | size 12 | symbol _ZNK4Aska14BaseReadDevice23GetCompressedFileLengthEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK4Aska14BaseReadDevice23GetCompressedFileLengthEi(long *param_1)

{
                    /* WARNING: Could not recover jumptable at 0x02322da0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*param_1 + 0x70))();
  return;
}

// ==== Aska::BaseReadDevice::GetDecompressedFileLength(int) const
// vaddr 0x2222da4 | ghidra 0x2322da4 | size 8 | symbol _ZNK4Aska14BaseReadDevice25GetDecompressedFileLengthEi | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska14BaseReadDevice25GetDecompressedFileLengthEi(void)

{
  return 0;
}

// ==== Aska::BaseReadDevice::GetReadAlign() const
// vaddr 0x2222dac | ghidra 0x2322dac | size 8 | symbol _ZNK4Aska14BaseReadDevice12GetReadAlignEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska14BaseReadDevice12GetReadAlignEv(void)

{
  return 0x200;
}

// ==== Aska::BaseReadDevice::GetType() const
// vaddr 0x2222db4 | ghidra 0x2322db4 | size 8 | symbol _ZNK4Aska14BaseReadDevice7GetTypeEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska14BaseReadDevice7GetTypeEv(void)

{
  return 0;
}

// ==== Aska::BaseReadDevice::InitProgressParameter(int, void*)
// vaddr 0x2222dbc | ghidra 0x2322dbc | size 4 | symbol _ZN4Aska14BaseReadDevice21InitProgressParameterEiPv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska14BaseReadDevice21InitProgressParameterEiPv(void)

{
  return;
}

// ==== Aska::BaseReadDevice::SetReadProgress(unsigned long)
// vaddr 0x2222dc0 | ghidra 0x2322dc0 | size 4 | symbol _ZN4Aska14BaseReadDevice15SetReadProgressEm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska14BaseReadDevice15SetReadProgressEm(void)

{
  return;
}

// ==== Aska::BaseReadDevice::CalcReadPos(int, unsigned long, unsigned long)
// vaddr 0x2222dc4 | ghidra 0x2322dc4 | size 8 | symbol _ZN4Aska14BaseReadDevice11CalcReadPosEimm | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska14BaseReadDevice11CalcReadPosEimm(void)

{
  return 0;
}

// ==== Aska::BaseReadDevice::LocalGetFileLength(int) const
// vaddr 0x2222dcc | ghidra 0x2322dcc | size 8 | symbol _ZNK4Aska14BaseReadDevice18LocalGetFileLengthEi | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska14BaseReadDevice18LocalGetFileLengthEi(void)

{
  return 0;
}

// ==== Aska::BaseReadDevice::LocalGetDecompressedFileLength(int) const
// vaddr 0x2222dd4 | ghidra 0x2322dd4 | size 8 | symbol _ZNK4Aska14BaseReadDevice30LocalGetDecompressedFileLengthEi | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska14BaseReadDevice30LocalGetDecompressedFileLengthEi(void)

{
  return 0;
}

// ==== Aska::BaseReadDevice::LocalCalcExistingFileLength(Aska::ReadRequest*) const
// vaddr 0x2222ddc | ghidra 0x2322ddc | size 16 | symbol _ZNK4Aska14BaseReadDevice27LocalCalcExistingFileLengthEPNS_11ReadRequestE | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK4Aska14BaseReadDevice27LocalCalcExistingFileLengthEPNS_11ReadRequestE
               (long *param_1,long param_2)

{
                    /* WARNING: Could not recover jumptable at 0x02322de8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*param_1 + 0x70))(param_1,*(undefined4 *)(param_2 + 0x48));
  return;
}

// ==== Aska::BaseReadDevice::LocalInitialize()
// vaddr 0x2222dec | ghidra 0x2322dec | size 8 | symbol _ZN4Aska14BaseReadDevice15LocalInitializeEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska14BaseReadDevice15LocalInitializeEv(void)

{
  return 1;
}

// ==== Aska::BaseReadDevice::ReadMain(Aska::ReadRequest*)
// vaddr 0x2222df4 | ghidra 0x2322df4 | size 4 | symbol _ZN4Aska14BaseReadDevice8ReadMainEPNS_11ReadRequestE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska14BaseReadDevice8ReadMainEPNS_11ReadRequestE(void)

{
  return;
}

// ==== Aska::BaseReadDevice::DecompressNotify::Handler(unsigned long)
// vaddr 0x2222df8 | ghidra 0x2322df8 | size 108 | symbol _ZN4Aska14BaseReadDevice16DecompressNotify7HandlerEm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska14BaseReadDevice16DecompressNotify7HandlerEm(long param_1,long param_2)

{
  undefined8 *puVar1;
  undefined8 uStack_28;
  undefined1 uStack_20;
  undefined4 uStack_1c;
  uint uStack_18;
  
  puVar1 = *(undefined8 **)(param_1 + 8);
  if ((puVar1 != (undefined8 *)0x0) && (*(char *)(param_1 + 0x1c) != '\0')) {
    if (param_2 == 0) {
      uStack_28 = *(undefined8 *)(param_1 + 0x10);
      uStack_1c = *(undefined4 *)(param_1 + 0x18);
    }
    else {
      uStack_28 = CONCAT44(uStack_28._4_4_,0xfffffc65);
      uStack_1c = 0xffffffff;
    }
    uStack_18 = (uint)(param_2 == 0);
    uStack_20 = 0;
    (**(code **)*puVar1)(puVar1,&uStack_28);
  }
  return;
}

// ==== Aska::BaseReadDevice::DecompressNotify::~DecompressNotify()
// vaddr 0x2222e64 | ghidra 0x2322e64 | size 4 | symbol _ZN4Aska14BaseReadDevice16DecompressNotifyD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska14BaseReadDevice16DecompressNotifyD0Ev(void)

{
  (*(code *)PTR__ZdlPv_02ca4758)();
  return;
}

// ==== Aska::DirectReadDevice::Read(char const*, unsigned char*, Aska::INotify*, unsigned long, unsigned long, int, int, bool, bool)
// vaddr 0x2224e6c | ghidra 0x2324e6c | size 188 | symbol _ZN4Aska16DirectReadDevice4ReadEPKcPhPNS_7INotifyEmmiibb | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska16DirectReadDevice4ReadEPKcPhPNS_7INotifyEmmiibb
          (long param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5,
          undefined8 param_6,undefined4 param_7,undefined4 param_8,byte param_9,byte param_10)

{
  char cVar1;
  ulong uVar2;
  undefined8 uVar3;
  undefined *puStack_68;
  undefined8 uStack_60;
  undefined8 uStack_58;
  undefined8 uStack_50;
  undefined8 uStack_48;
  undefined8 uStack_40;
  undefined8 uStack_38;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  uint uStack_28;
  undefined8 uStack_20;
  undefined4 uStack_18;
  
  uStack_60 = 0;
  uStack_58 = 0;
  puStack_68 = PTR__ZTVN4Aska11ReadRequestE_02cbdc38 + 0x10;
  uStack_18 = 1;
  uStack_28 = 8;
  if ((param_9 & 1) != 0) {
    uStack_28 = 10;
  }
  if ((param_10 & 1) == 0) {
    cVar1 = *(char *)(param_1 + 0x249);
  }
  else {
    uStack_28 = uStack_28 | 0x10;
    cVar1 = *(char *)(param_1 + 0x249);
  }
  if (((cVar1 == '\0') ||
      (uStack_50 = param_3, uStack_48 = param_4, uStack_40 = param_5, uStack_38 = param_6,
      uStack_30 = param_7, uStack_2c = param_8, uStack_20 = param_2,
      uVar2 = Aska::File::DoesExist(char const*, bool)(param_2,param_10 & 1), (uVar2 & 1) == 0)) ||
     (uVar2 = Aska::BaseReadDevice::Read(Aska::ReadRequest*)(param_1,&puStack_68), (uVar2 & 1) == 0)) {
    uVar3 = 0;
  }
  else {
    uVar3 = 1;
  }
  return uVar3;
}

// ==== Aska::DirectReadDevice::ReadMain(Aska::ReadRequest*)
// vaddr 0x2224f28 | ghidra 0x2324f28 | size 152 | symbol _ZN4Aska16DirectReadDevice8ReadMainEPNS_11ReadRequestE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16DirectReadDevice8ReadMainEPNS_11ReadRequestE(long *param_1,long param_2)

{
  undefined *puVar1;
  int iVar2;
  undefined8 uVar3;
  undefined *puStack_70;
  undefined1 uStack_68;
  long lStack_60;
  long lStack_58;
  undefined1 *puStack_50;
  undefined8 uStack_48;
  long *plStack_40;
  undefined1 uStack_38;
  
  uStack_68 = 0;
  lStack_60 = 0;
  puVar1 = PTR__ZTVN4Aska4FileE_02cb6e28 + 0x10;
  uVar3 = *(undefined8 *)(param_2 + 0x48);
  puStack_70 = puVar1;
  iVar2 = (**(code **)(*param_1 + 0x48))();
  lStack_58 = (long)iVar2;
  uStack_38 = 0;
  if ((*(uint *)(param_2 + 0x40) >> 4 & 1) != 0) {
    uStack_68 = 1;
  }
  puStack_50 = (undefined1 *)&puStack_70;
  uStack_48 = uVar3;
  plStack_40 = param_1;
  void Aska::TDeviceReadMain<false, false, true, true>(Aska::ReadRequest*, Aska::ReadDeviceArgs&)(param_2,&lStack_58);
  if (lStack_60 != 0) {
    puStack_70 = puVar1;
    Aska::File::Close()(&puStack_70);
  }
  return;
}

// ==== Aska::DirectReadDevice::~DirectReadDevice()
// vaddr 0x22252a8 | ghidra 0x23252a8 | size 116 | symbol _ZN4Aska16DirectReadDeviceD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16DirectReadDeviceD0Ev(long *param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  
  *param_1 = (long)(PTR__ZTVN4Aska14BaseReadDeviceE_02cbc9e0 + 0x10);
  Aska::BaseReadDevice::Finalize()();
  Aska::Event::Exit()(param_1 + 0x3b);
  puVar2 = PTR__ZTVN4Aska13TDynamicQueueIPNS_11ReadRequestELb0EEE_02cbf580;
  *(undefined4 *)(param_1 + 0x36) = 0;
  param_1[0x37] = 0;
  puVar1 = PTR__ZTVN4Aska5TListINS_11ReadRequestEEE_02cbe550 + 0x10;
  param_1[0x34] = (long)(puVar2 + 0x10);
  param_1[0x35] = 1;
  param_1[0x27] = (long)puVar1;
  Aska::FastCriticalSection::~FastCriticalSection()(param_1 + 0x15);
  Aska::FastCriticalSection::~FastCriticalSection()(param_1 + 3);
  Aska::Thread::~Thread()(param_1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::DirectReadDevice::LocalCalcExistingFileLength(Aska::ReadRequest*) const
// vaddr 0x222531c | ghidra 0x232531c | size 16 | symbol _ZNK4Aska16DirectReadDevice27LocalCalcExistingFileLengthEPNS_11ReadRequestE | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK4Aska16DirectReadDevice27LocalCalcExistingFileLengthEPNS_11ReadRequestE
               (undefined8 param_1,long param_2)

{
  (*(code *)PTR__ZN4Aska4File11GetFileSizeEPKcb_02c9e240)
            (*(undefined8 *)(param_2 + 0x48),*(uint *)(param_2 + 0x40) >> 4 & 1);
  return;
}

// ==== Aska::DiscReadDevice::MakeLayerFileName(char*, int)
// vaddr 0x222532c | ghidra 0x232532c | size 128 | symbol _ZN4Aska14DiscReadDevice17MakeLayerFileNameEPci | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska14DiscReadDevice17MakeLayerFileNameEPci(long param_1,char *param_2,undefined4 param_3)

{
  char cVar1;
  char *pcVar2;
  undefined1 auStack_28 [8];
  
  Aska::AppStorageCommonSettingProxy::AppStorageCommonSettingProxy()(auStack_28);
  pcVar2 = *(char **)(param_1 + 0xf260);
  cVar1 = *pcVar2;
  while (cVar1 != '\0') {
    pcVar2 = pcVar2 + 1;
    *param_2 = cVar1;
    param_2 = param_2 + 1;
    cVar1 = *pcVar2;
  }
  pcVar2 = (char *)Aska::AppStorageCommonSettingProxy::GetFileName(int) const(auStack_28,param_3);
  cVar1 = *pcVar2;
  while (cVar1 != '\0') {
    pcVar2 = pcVar2 + 1;
    *param_2 = cVar1;
    param_2 = param_2 + 1;
    cVar1 = *pcVar2;
  }
  *param_2 = '\0';
  Aska::AppStorageCommonSettingProxy::~AppStorageCommonSettingProxy()(auStack_28);
  return;
}

// ==== Aska::DiscReadDevice::MakeFileSystem()
// vaddr 0x22253ac | ghidra 0x23253ac | size 704 | symbol _ZN4Aska14DiscReadDevice14MakeFileSystemEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZN4Aska14DiscReadDevice14MakeFileSystemEv(long *param_1)

{
  long lVar1;
  undefined8 *puVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  long *plVar7;
  ulong uVar8;
  long lVar9;
  char cVar10;
  int iVar11;
  long *plVar12;
  int iVar13;
  char *pcVar14;
  long *plVar15;
  undefined4 uVar16;
  ulong uVar17;
  char *pcVar18;
  undefined8 uVar20;
  undefined8 uVar21;
  undefined8 uVar22;
  char acStack_170 [256];
  undefined1 auStack_70 [8];
  undefined1 auStack_68 [8];
  char *pcVar19;
  
  *(undefined1 *)(param_1 + 0x49) = 0;
  *(undefined1 *)((long)param_1 + 0x24c) = 0;
  uVar5 = (**(code **)(*param_1 + 0x48))();
  uVar3 = 0;
  if (uVar5 != 0) {
    uVar3 = 0xf000 / uVar5;
  }
  iVar13 = uVar3 * uVar5;
  if (iVar13 == 0xf000) {
    plVar7 = param_1 + 0x4a;
    uVar3 = 0xf000;
  }
  else {
    iVar6 = (**(code **)(*param_1 + 0x48))(param_1);
    uVar3 = iVar6 + 0xefffU & -iVar6;
    plVar7 = (long *)operator new[](unsigned long, std::nothrow_t const&)(uVar3,PTR__ZSt7nothrow_02cb9a80);
    if (plVar7 == (long *)0x0) {
      return 0;
    }
  }
  Aska::AppStorageCommonSettingProxy::AppStorageCommonSettingProxy()(auStack_70);
  iVar6 = Aska::AppStorageCommonSettingProxy::GetLayerNum() const(auStack_70);
  if (0 < iVar6) {
    uVar17 = 0;
    do {
      Aska::AppStorageCommonSettingProxy::AppStorageCommonSettingProxy()(auStack_68);
      pcVar14 = (char *)param_1[0x1e4c];
      cVar10 = *pcVar14;
      if (cVar10 == '\0') {
        pcVar18 = acStack_170;
      }
      else {
        pcVar19 = acStack_170;
        do {
          pcVar14 = pcVar14 + 1;
          pcVar18 = pcVar19 + 1;
          *pcVar19 = cVar10;
          cVar10 = *pcVar14;
          pcVar19 = pcVar18;
        } while (cVar10 != '\0');
      }
      pcVar14 = (char *)Aska::AppStorageCommonSettingProxy::GetFileName(int) const(auStack_68,uVar17 & 0xffffffff);
      cVar10 = *pcVar14;
      while (cVar10 != '\0') {
        pcVar14 = pcVar14 + 1;
        *pcVar18 = cVar10;
        pcVar18 = pcVar18 + 1;
        cVar10 = *pcVar14;
      }
      *pcVar18 = '\0';
      Aska::AppStorageCommonSettingProxy::~AppStorageCommonSettingProxy()(auStack_68);
      *(undefined1 *)(param_1 + uVar17 * 3 + 0x1e4e) = 1;
      uVar8 = Aska::File::Open(char const*, bool, bool, bool)(param_1 + uVar17 * 3 + 0x1e4d,acStack_170,1,0,1);
      if ((uVar8 & 1) == 0) {
        iVar4 = 999;
        do {
          iVar11 = iVar4;
          if (iVar11 + 1 < 2) break;
          Aska::Thread::Sleep(unsigned int)(1);
          uVar8 = Aska::File::Open(char const*, bool, bool, bool)(param_1 + uVar17 * 3 + 0x1e4d,acStack_170,1,0,1);
          iVar4 = iVar11 + -1;
        } while ((uVar8 & 1) == 0);
        if (iVar11 == 0 && (uint)uVar17 == 0) goto code_r0x023255d0;
      }
      else if (((uint)uVar17 | 1000) == 0) {
code_r0x023255d0:
        uVar16 = 0;
        goto code_r0x02325640;
      }
      uVar17 = uVar17 + 1;
    } while ((long)uVar17 < (long)iVar6);
  }
  lVar9 = Aska::File::Read(void*, unsigned long, unsigned int*)(param_1 + 0x1e4d,plVar7,uVar3,0);
  if (lVar9 == 0) {
    uVar16 = 0;
    if ((plVar7 != (long *)0x0) && (iVar13 != 0xf000)) {
      operator delete[](void*)(plVar7);
      uVar16 = 0;
    }
  }
  else {
    if (iVar13 != 0xf000) {
      if ((param_1 + 0x4a < plVar7 + 0x1e00) && (plVar7 < param_1 + 0x1e4a)) {
        iVar13 = 0x3c00;
        plVar12 = param_1 + 0x4a;
        plVar15 = plVar7;
        do {
          iVar13 = iVar13 + -1;
          *(int *)plVar12 = (int)*plVar15;
          plVar12 = (long *)((long)plVar12 + 4);
          plVar15 = (long *)((long)plVar15 + 4);
        } while (iVar13 != 0);
      }
      else {
        lVar9 = 0;
        do {
          puVar2 = (undefined8 *)((long)plVar7 + lVar9);
          uVar20 = *puVar2;
          uVar22 = puVar2[3];
          uVar21 = puVar2[2];
          lVar1 = lVar9 + 0x20;
          *(undefined8 *)((long)param_1 + lVar9 + 600) = puVar2[1];
          *(undefined8 *)((long)param_1 + lVar9 + 0x250) = uVar20;
          *(undefined8 *)((long)param_1 + lVar9 + 0x268) = uVar22;
          *(undefined8 *)((long)param_1 + lVar9 + 0x260) = uVar21;
          lVar9 = lVar1;
        } while (lVar1 != 0xf000);
      }
      if (plVar7 != (long *)0x0) {
        operator delete[](void*)(plVar7);
      }
    }
    Aska::FileSystemEncode(void*)(param_1 + 0x4a);
    uVar16 = 1;
    *(char *)(param_1 + 0x1e4b) = (char)(int)param_1[0x4a];
    *(undefined1 *)(param_1 + 0x49) = 1;
  }
code_r0x02325640:
  Aska::AppStorageCommonSettingProxy::~AppStorageCommonSettingProxy()(auStack_70);
  return uVar16;
}

// ==== Aska::DiscReadDevice::SetPath(char const*)
// vaddr 0x222566c | ghidra 0x232566c | size 152 | symbol _ZN4Aska14DiscReadDevice7SetPathEPKc | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska14DiscReadDevice7SetPathEPKc(long param_1,undefined8 param_2)

{
  undefined8 uVar1;
  long lVar2;
  long lVar3;
  ulong uVar4;
  
  if (*(long *)(param_1 + 0xf250) == 0) {
    if (*(long *)(param_1 + 0xf260) != 0) {
      operator delete[](void*)();
    }
    lVar2 = strlen(param_2);
    lVar3 = operator new[](unsigned long, std::nothrow_t const&)(lVar2 + 1U,PTR__ZSt7nothrow_02cb9a80);
    *(long *)(param_1 + 0xf260) = lVar3;
    uVar4 = strlen(param_2);
    if (uVar4 < lVar2 + 1U) {
      strcpy(lVar3,param_2);
    }
    else {
      raise(5);
    }
    uVar1 = 1;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

// ==== Aska::DiscReadDevice::LocalGetFileLength(int) const
// vaddr 0x2225704 | ghidra 0x2325704 | size 44 | symbol _ZNK4Aska14DiscReadDevice18LocalGetFileLengthEi | lib libSOA-3.7.0.so | 2026-10-04
int _ZNK4Aska14DiscReadDevice18LocalGetFileLengthEi(long *param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = *(uint *)((long)param_1 + (long)param_2 * 0xc + 0x250);
  iVar2 = (**(code **)(*param_1 + 0x48))();
  return iVar2 * (uVar1 & 0xffffff);
}

// ==== Aska::DiscReadDevice::LocalGetDecompressedFileLength(int) const
// vaddr 0x2225730 | ghidra 0x2325730 | size 16 | symbol _ZNK4Aska14DiscReadDevice30LocalGetDecompressedFileLengthEi | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK4Aska14DiscReadDevice30LocalGetDecompressedFileLengthEi(long param_1,int param_2)

{
  return *(undefined4 *)(param_1 + (long)param_2 * 0xc + 0x254);
}

// ==== Aska::DiscReadDevice::LocalInitialize()
// vaddr 0x2225740 | ghidra 0x2325740 | size 128 | symbol _ZN4Aska14DiscReadDevice15LocalInitializeEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska14DiscReadDevice15LocalInitializeEv(long param_1)

{
  long *plVar1;
  long lVar2;
  ulong uVar3;
  undefined8 uVar4;
  
  if (*(long *)(param_1 + 0xf260) == 0) {
    *(long *)(param_1 + 0xf260) = *(long *)PTR__ZN4Aska6Global20m_pszStorageRootPathE_02cbf040;
  }
  lVar2 = operator new[](unsigned long, std::nothrow_t const&)(0x10000,PTR__ZSt7nothrow_02cb9a80);
  plVar1 = (long *)(param_1 + 0xf250);
  *plVar1 = lVar2;
  uVar4 = 0;
  if (lVar2 != 0) {
    uVar3 = Aska::DiscReadDevice::MakeFileSystem()(param_1);
    if ((uVar3 & 1) == 0) {
      uVar4 = 0;
      if (*plVar1 != 0) {
        operator delete[](void*)();
        uVar4 = 0;
        *plVar1 = 0;
      }
    }
    else {
      uVar4 = 1;
    }
  }
  return uVar4;
}

// ==== Aska::DiscReadDevice::LocalFinalize()
// vaddr 0x22257c0 | ghidra 0x23257c0 | size 92 | symbol _ZN4Aska14DiscReadDevice13LocalFinalizeEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska14DiscReadDevice13LocalFinalizeEv(long param_1)

{
  long lVar1;
  
  if (*(long *)(param_1 + 0xf250) != 0) {
    operator delete[](void*)();
    *(long *)(param_1 + 0xf250) = 0;
  }
  lVar1 = *(long *)(param_1 + 0xf260);
  if ((lVar1 != 0) && (lVar1 != *(long *)PTR__ZN4Aska6Global20m_pszStorageRootPathE_02cbf040)) {
    operator delete[](void*)();
    *(long *)(param_1 + 0xf260) = 0;
  }
  return;
}

// ==== Aska::DiscReadDevice::ReadMain(Aska::ReadRequest*)
// vaddr 0x222581c | ghidra 0x232581c | size 132 | symbol _ZN4Aska14DiscReadDevice8ReadMainEPNS_11ReadRequestE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska14DiscReadDevice8ReadMainEPNS_11ReadRequestE(long *param_1,long param_2)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  long lStack_58;
  long *plStack_50;
  undefined8 uStack_48;
  long *plStack_40;
  byte bStack_38;
  
  uVar1 = *(uint *)(param_2 + 0x40);
  uVar2 = *(uint *)((long)param_1 + (long)*(int *)(param_2 + 0x48) * 0xc + 600);
  iVar3 = (**(code **)(*param_1 + 0x48))();
  lStack_58 = (long)iVar3;
  bStack_38 = (byte)(uVar1 >> 1) & 1;
  uStack_48 = 0;
  plStack_50 = param_1 + (ulong)(uVar2 >> 0x1c) * 3 + 0x1e4d;
  plStack_40 = param_1;
  void Aska::TDeviceReadMain<true, true, false, true>(Aska::ReadRequest*, Aska::ReadDeviceArgs&)(param_2,&lStack_58);
  return;
}

// ==== Aska::DiscReadDevice::GetProgress(int, void*)
// vaddr 0x2225c7c | ghidra 0x2325c7c | size 416 | symbol _ZN4Aska14DiscReadDevice11GetProgressEiPv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska14DiscReadDevice11GetProgressEiPv(long param_1,int param_2,long param_3)

{
  int *piVar1;
  int *piVar2;
  char cVar3;
  bool bVar4;
  ulong uVar5;
  int iVar6;
  undefined8 uVar7;
  
  piVar1 = (int *)(param_1 + 0xf360);
  iVar6 = 0;
  do {
    while (*piVar1 == -1) {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = 0;
        cVar3 = ExclusiveMonitorsStatus();
      }
      if (cVar3 == '\0') goto code_r0x02325d74;
    }
    ClearExclusiveLocal();
    bVar4 = iVar6 < 0x1ff;
    iVar6 = iVar6 + 1;
  } while (bVar4);
  piVar2 = (int *)(param_1 + 0xf364);
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
        uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0xf3a0);
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
          Aska::Semaphore::Wait() const(param_1 + 0xf3a0);
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
          if (cVar3 == '\0') goto code_r0x02325d64;
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
code_r0x02325d64:
  do {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar4) {
      *piVar2 = *piVar2 + -1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
code_r0x02325d74:
  DataMemoryBarrier(2,3);
  if (((param_2 < 1) || (*(int *)(param_1 + 0xf3b8) == param_2)) &&
     ((param_3 == 0 || (*(long *)(param_1 + 0xf3c8) == param_3)))) {
    uVar7 = *(undefined8 *)(param_1 + 0xf3c0);
  }
  else {
    uVar7 = 0;
  }
  DataMemoryBarrier(2,3);
  *piVar1 = -1;
  DataMemoryBarrier(2,3);
  piVar1 = (int *)(param_1 + 0xf364);
  if (0x14 < *piVar1) {
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
    uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0xf3a0);
    if ((uVar5 & 1) != 0) {
      Aska::Semaphore::Signal() const(param_1 + 0xf3a0);
    }
  }
  return uVar7;
}

// ==== Aska::DiscReadDevice::InitProgressParameter(int, void*)
// vaddr 0x2225e1c | ghidra 0x2325e1c | size 400 | symbol _ZN4Aska14DiscReadDevice21InitProgressParameterEiPv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska14DiscReadDevice21InitProgressParameterEiPv
               (long param_1,undefined4 param_2,undefined8 param_3)

{
  int *piVar1;
  char cVar2;
  bool bVar3;
  ulong uVar4;
  int iVar5;
  int *piVar6;
  
  piVar1 = (int *)(param_1 + 0xf360);
  iVar5 = 0;
  do {
    while (*piVar1 != -1) {
      ClearExclusiveLocal();
      bVar3 = 0x1fe < iVar5;
      iVar5 = iVar5 + 1;
      if (bVar3) {
        piVar6 = (int *)(param_1 + 0xf364);
        do {
          cVar2 = '\x01';
          bVar3 = (bool)ExclusiveMonitorPass(piVar6,0x10);
          if (bVar3) {
            *piVar6 = *piVar6 + 1;
            cVar2 = ExclusiveMonitorsStatus();
          }
        } while (cVar2 != '\0');
        do {
          if (*piVar1 != -1) {
            ClearExclusiveLocal();
            do {
              uVar4 = Aska::Semaphore::IsReady() const(param_1 + 0xf3a0);
              if ((uVar4 & 1) == 0) {
                do {
                  cVar2 = '\x01';
                  bVar3 = (bool)ExclusiveMonitorPass(piVar6,0x10);
                  if (bVar3) {
                    *piVar6 = *piVar6 + -1;
                    cVar2 = ExclusiveMonitorsStatus();
                  }
                } while (cVar2 != '\0');
                Aska::Thread::Sleep(unsigned int)(1);
              }
              else {
                Aska::Semaphore::Wait() const(param_1 + 0xf3a0);
              }
              do {
                cVar2 = '\x01';
                bVar3 = (bool)ExclusiveMonitorPass(piVar6,0x10);
                if (bVar3) {
                  *piVar6 = *piVar6 + 1;
                  cVar2 = ExclusiveMonitorsStatus();
                }
              } while (cVar2 != '\0');
              while (*piVar1 == -1) {
                cVar2 = '\x01';
                bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
                if (bVar3) {
                  *piVar1 = 0;
                  cVar2 = ExclusiveMonitorsStatus();
                }
                if (cVar2 == '\0') goto code_r0x02325f94;
              }
              ClearExclusiveLocal();
            } while( true );
          }
          cVar2 = '\x01';
          bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar3) {
            *piVar1 = 0;
            cVar2 = ExclusiveMonitorsStatus();
          }
        } while (cVar2 != '\0');
code_r0x02325f94:
        do {
          cVar2 = '\x01';
          bVar3 = (bool)ExclusiveMonitorPass(piVar6,0x10);
          if (bVar3) {
            *piVar6 = *piVar6 + -1;
            cVar2 = ExclusiveMonitorsStatus();
          }
        } while (cVar2 != '\0');
        DataMemoryBarrier(2,3);
code_r0x02325ea8:
        piVar6 = (int *)(param_1 + 0xf364);
        *(undefined8 *)(param_1 + 0xf3c0) = 0;
        *(undefined4 *)(param_1 + 0xf3b8) = param_2;
        *(undefined8 *)(param_1 + 0xf3c8) = param_3;
        DataMemoryBarrier(2,3);
        *piVar1 = -1;
        DataMemoryBarrier(2,3);
        if (0x14 < *piVar6) {
          do {
            cVar2 = '\x01';
            bVar3 = (bool)ExclusiveMonitorPass(piVar6,0x10);
            if (bVar3) {
              *piVar6 = *piVar6 + -1;
              cVar2 = ExclusiveMonitorsStatus();
            }
          } while (cVar2 != '\0');
          uVar4 = Aska::Semaphore::IsReady() const(param_1 + 0xf3a0);
          if ((uVar4 & 1) != 0) {
            (*(code *)PTR__ZNK4Aska9Semaphore6SignalEv_02c96cd0)(param_1 + 0xf3a0);
            return;
          }
        }
        return;
      }
    }
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar3) {
      *piVar1 = 0;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
  DataMemoryBarrier(2,3);
  goto code_r0x02325ea8;
}

// ==== Aska::DiscReadDevice::SetReadProgress(unsigned long)
// vaddr 0x2225fac | ghidra 0x2325fac | size 12 | symbol _ZN4Aska14DiscReadDevice15SetReadProgressEm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska14DiscReadDevice15SetReadProgressEm(long param_1,undefined8 param_2)

{
  *(undefined8 *)(param_1 + 0xf3c0) = param_2;
  return;
}

// ==== Aska::DiscReadDevice::CalcReadPos(int, unsigned long, unsigned long)
// vaddr 0x2225fb8 | ghidra 0x2325fb8 | size 24 | symbol _ZN4Aska14DiscReadDevice11CalcReadPosEimm | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska14DiscReadDevice11CalcReadPosEimm(long param_1,int param_2,long param_3,long param_4)

{
  return param_4 + ((ulong)*(uint *)(param_1 + (long)param_2 * 0xc + 600) & 0xfffffff) * param_3;
}

// ==== Aska::DiscReadDevice::SwapDisc(int, Aska::Event*, Aska::INotify*)
// vaddr 0x2225fd0 | ghidra 0x2325fd0 | size 8 | symbol _ZN4Aska14DiscReadDevice8SwapDiscEiPNS_5EventEPNS_7INotifyE | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska14DiscReadDevice8SwapDiscEiPNS_5EventEPNS_7INotifyE(void)

{
  return 0;
}

// ==== Aska::DiscReadDevice::SwapDiscMain(int, Aska::Event*, Aska::INotify*)
// vaddr 0x2225fd8 | ghidra 0x2325fd8 | size 72 | symbol _ZN4Aska14DiscReadDevice12SwapDiscMainEiPNS_5EventEPNS_7INotifyE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska14DiscReadDevice12SwapDiscMainEiPNS_5EventEPNS_7INotifyE(void)

{
  ulong uVar1;
  undefined8 *in_x3;
  
  uVar1 = Aska::DiscReadDevice::MakeFileSystem()();
  if ((uVar1 & 1) == 0) {
    (**(code **)*in_x3)(in_x3,0);
  }
  else if (in_x3 == (undefined8 *)0x0) {
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x0232601c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)*in_x3)(in_x3,1);
  return;
}

// ==== Aska::DiscReadDevice::SwapCancel()
// vaddr 0x2226020 | ghidra 0x2326020 | size 8 | symbol _ZN4Aska14DiscReadDevice10SwapCancelEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska14DiscReadDevice10SwapCancelEv(void)

{
  return 0;
}

// ==== Aska::DiscReadDevice::GetPlayGoChunk(int)
// vaddr 0x2226028 | ghidra 0x2326028 | size 8 | symbol _ZN4Aska14DiscReadDevice14GetPlayGoChunkEi | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska14DiscReadDevice14GetPlayGoChunkEi(void)

{
  return 0;
}

// ==== Aska::DiscReadDevice::PrefetchPlayGoChunk(int)
// vaddr 0x2226030 | ghidra 0x2326030 | size 4 | symbol _ZN4Aska14DiscReadDevice19PrefetchPlayGoChunkEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska14DiscReadDevice19PrefetchPlayGoChunkEi(void)

{
  return;
}

// ==== Aska::DiscReadDevice::PrefetchPlayGoChunkByFileID(int)
// vaddr 0x2226034 | ghidra 0x2326034 | size 4 | symbol _ZN4Aska14DiscReadDevice27PrefetchPlayGoChunkByFileIDEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska14DiscReadDevice27PrefetchPlayGoChunkByFileIDEi(void)

{
  return;
}

// ==== Aska::DiscReadDevice::~DiscReadDevice()
// vaddr 0x2226038 | ghidra 0x2326038 | size 464 | symbol _ZN4Aska14DiscReadDeviceD2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska14DiscReadDeviceD2Ev(long *param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  long lVar3;
  
  *param_1 = (long)(PTR__ZTVN4Aska14DiscReadDeviceE_02cc1a40 + 0x10);
  if (param_1[0x1e4a] != 0) {
    operator delete[](void*)();
    param_1[0x1e4a] = 0;
  }
  lVar3 = param_1[0x1e4c];
  if ((lVar3 != 0) && (lVar3 != *(long *)PTR__ZN4Aska6Global20m_pszStorageRootPathE_02cbf040)) {
    operator delete[](void*)();
    param_1[0x1e4c] = 0;
  }
  Aska::FastCriticalSection::~FastCriticalSection()(param_1 + 0x1e65);
  puVar2 = PTR__ZTVN4Aska4FileE_02cb6e28;
  puVar1 = PTR__ZTVN4Aska4FileE_02cb6e28 + 0x10;
  param_1[0x1e62] = (long)puVar1;
  if (param_1[0x1e64] != 0) {
    Aska::File::Close()();
  }
  param_1[0x1e5f] = (long)puVar1;
  if (param_1[0x1e61] != 0) {
    Aska::File::Close()();
  }
  param_1[0x1e5c] = (long)(puVar2 + 0x10);
  if (param_1[0x1e5e] != 0) {
    Aska::File::Close()();
  }
  param_1[0x1e59] = (long)(puVar2 + 0x10);
  if (param_1[0x1e5b] != 0) {
    Aska::File::Close()();
  }
  param_1[0x1e56] = (long)(puVar2 + 0x10);
  if (param_1[0x1e58] != 0) {
    Aska::File::Close()();
  }
  param_1[0x1e53] = (long)(puVar2 + 0x10);
  if (param_1[0x1e55] != 0) {
    Aska::File::Close()();
  }
  param_1[0x1e50] = (long)(puVar2 + 0x10);
  if (param_1[0x1e52] != 0) {
    Aska::File::Close()();
  }
  param_1[0x1e4d] = (long)(puVar2 + 0x10);
  if (param_1[0x1e4f] != 0) {
    Aska::File::Close()();
  }
  *param_1 = (long)(PTR__ZTVN4Aska14BaseReadDeviceE_02cbc9e0 + 0x10);
  Aska::BaseReadDevice::Finalize()(param_1);
  Aska::Event::Exit()(param_1 + 0x3b);
  puVar2 = PTR__ZTVN4Aska13TDynamicQueueIPNS_11ReadRequestELb0EEE_02cbf580;
  *(undefined4 *)(param_1 + 0x36) = 0;
  param_1[0x37] = 0;
  puVar1 = PTR__ZTVN4Aska5TListINS_11ReadRequestEEE_02cbe550 + 0x10;
  param_1[0x34] = (long)(puVar2 + 0x10);
  param_1[0x35] = 1;
  param_1[0x27] = (long)puVar1;
  Aska::FastCriticalSection::~FastCriticalSection()(param_1 + 0x15);
  Aska::FastCriticalSection::~FastCriticalSection()(param_1 + 3);
  (*(code *)PTR__ZN4Aska6ThreadD1Ev_02c9be08)(param_1);
  return;
}

// ==== Aska::DiscReadDevice::~DiscReadDevice()
// vaddr 0x2226208 | ghidra 0x2326208 | size 24 | symbol _ZN4Aska14DiscReadDeviceD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska14DiscReadDeviceD0Ev(undefined8 param_1)

{
  Aska::DiscReadDevice::~DiscReadDevice()();
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::DiscReadDevice::FileExists(int) const
// vaddr 0x2226220 | ghidra 0x2326220 | size 48 | symbol _ZNK4Aska14DiscReadDevice10FileExistsEi | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK4Aska14DiscReadDevice10FileExistsEi(long param_1,int param_2)

{
  if (0x13fe < param_2 - 1U) {
    return false;
  }
  return *(int *)(param_1 + (long)param_2 * 0xc + 600) != 0;
}

// ==== Aska::DiscReadDevice::CalcFileLength(int) const
// vaddr 0x2226250 | ghidra 0x2326250 | size 12 | symbol _ZNK4Aska14DiscReadDevice14CalcFileLengthEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK4Aska14DiscReadDevice14CalcFileLengthEi(long *param_1)

{
                    /* WARNING: Could not recover jumptable at 0x02326258. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*param_1 + 0x78))();
  return;
}

// ==== Aska::DiscReadDevice::GetDecompressedFileLength(int) const
// vaddr 0x222625c | ghidra 0x232625c | size 12 | symbol _ZNK4Aska14DiscReadDevice25GetDecompressedFileLengthEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK4Aska14DiscReadDevice25GetDecompressedFileLengthEi(long *param_1)

{
                    /* WARNING: Could not recover jumptable at 0x02326264. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*param_1 + 0x78))();
  return;
}

// ==== Aska::DiscReadDevice::GetType() const
// vaddr 0x2226268 | ghidra 0x2326268 | size 8 | symbol _ZNK4Aska14DiscReadDevice7GetTypeEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska14DiscReadDevice7GetTypeEv(void)

{
  return 1;
}

// ==== Aska::DiscReadDevice::GetFileLength(int) const
// vaddr 0x2226270 | ghidra 0x2326270 | size 12 | symbol _ZNK4Aska14DiscReadDevice13GetFileLengthEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK4Aska14DiscReadDevice13GetFileLengthEi(long *param_1)

{
                    /* WARNING: Could not recover jumptable at 0x02326278. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*param_1 + 0x78))();
  return;
}


// FAILED to create function at 0296e990 typeinfo name for Aska::BaseReadDevice::ReadRequestList
// FAILED to create function at 029d8b40 typeinfo name for Aska::BaseReadDevice::DecompressNotify
// FAILED to create function at 02bb0478 Aska::BaseReadDevice::ReadRequestList::vtable
// FAILED to create function at 02bb04d0 Aska::BaseReadDevice::ReadRequestList::typeinfo
// FAILED to create function at 02bb0558 Aska::FileReadManager::vtable
// FAILED to create function at 02bb0578 Aska::FileReadManager::typeinfo
// FAILED to create function at 02c5dcf8 Aska::BaseReadDevice::vtable
// FAILED to create function at 02c5dda0 Aska::BaseReadDevice::typeinfo
// FAILED to create function at 02c5ddb8 Aska::BaseReadDevice::DecompressNotify::vtable
// FAILED to create function at 02c5dde0 Aska::BaseReadDevice::DecompressNotify::typeinfo
// FAILED to create function at 02c5dec8 Aska::DirectReadDevice::vtable
// FAILED to create function at 02c5df70 Aska::DirectReadDevice::typeinfo
// FAILED to create function at 02c5df88 Aska::DiscReadDevice::vtable
// FAILED to create function at 02c5e040 Aska::DiscReadDevice::typeinfo
// FAILED to create function at 02e753d0 Aska::BaseReadDevice::m_pReadErrorNotify
