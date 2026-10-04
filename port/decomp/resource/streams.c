// port/decomp/resource/streams.c: Ghidra decompiles for the resource subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-04 06:13 UTC: tools/decomp.sh '--into' 'resource/streams' 'Aska::IStream::' 'Aska::StaticStream::' 'Aska::StreamingStream::' 'Aska::MultiMediaStream::' 'Aska::DiscReadStream::' 'Aska::FileStream::' 'Aska::File::'

// ==== Aska::File::~File()
// vaddr 0x14f6600 | ghidra 0x15f6600 | size 52 | symbol _ZN4Aska4FileD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska4FileD0Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska4FileE_02cb6e28 + 0x10);
  if (param_1[2] != 0) {
    Aska::File::Close()(param_1);
  }
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::File::~File()
// vaddr 0x14f6634 | ghidra 0x15f6634 | size 32 | symbol _ZN4Aska4FileD2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska4FileD2Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska4FileE_02cb6e28 + 0x10);
  if (param_1[2] != 0) {
    (*(code *)PTR__ZN4Aska4File5CloseEv_02c8e880)();
    return;
  }
  return;
}

// ==== Aska::IStream::ReadAsync(void*, long, unsigned long, unsigned long, Aska::INotify*, long volatile*)
// vaddr 0x17cff3c | ghidra 0x18cff3c | size 248 | symbol _ZN4Aska7IStream9ReadAsyncEPvlmmPNS_7INotifyEPVl | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZN4Aska7IStream9ReadAsyncEPvlmmPNS_7INotifyEPVl
                (long *param_1,undefined8 param_2,undefined8 param_3,long param_4,ulong param_5,
                undefined8 *param_6,ulong *param_7)

{
  ulong uVar1;
  ulong uVar2;
  ulong uStack_50;
  undefined8 uStack_48;
  
  uStack_50 = 0;
  uStack_48 = 0;
  uVar1 = (**(code **)(*param_1 + 0x20))(param_1,param_3,0);
  if ((long)uVar1 < 0) {
    uStack_50 = uVar1;
    if (param_7 != (ulong *)0x0) {
      *param_7 = uVar1;
    }
  }
  else {
    uVar2 = (**(code **)(*param_1 + 0x28))(param_1,param_2,param_4,param_5);
    if (uVar2 == param_5) {
      if (param_7 != (ulong *)0x0) {
        *param_7 = param_5;
      }
      uStack_50 = param_5 * param_4;
    }
    else {
      uVar1 = (**(code **)(*param_1 + 0x58))(param_1);
      uStack_50 = uVar1;
      if (param_7 != (ulong *)0x0) {
        *param_7 = uVar1;
      }
    }
  }
  if (param_6 != (undefined8 *)0x0) {
    (**(code **)*param_6)(param_6,&uStack_50);
  }
  return uVar1 >> 0x3f ^ 1;
}

// ==== Aska::IStream::PeekLastError() const
// vaddr 0x17e6a60 | ghidra 0x18e6a60 | size 64 | symbol _ZNK4Aska7IStream13PeekLastErrorEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska7IStream13PeekLastErrorEv(long *param_1)

{
  undefined8 uVar1;
  
  uVar1 = (**(code **)(*param_1 + 0x50))();
  (**(code **)(*param_1 + 0x48))(param_1,uVar1);
  return uVar1;
}

// ==== Aska::IStream::GetTotalSize() const
// vaddr 0x17e6aa0 | ghidra 0x18e6aa0 | size 288 | symbol _ZNK4Aska7IStream12GetTotalSizeEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK4Aska7IStream12GetTotalSizeEv(long *param_1)

{
  long lVar1;
  ulong uVar2;
  long lVar3;
  long lVar4;
  long lVar5;
  
  uVar2 = (**(code **)(*param_1 + 0x10))();
  if ((uVar2 & 1) != 0) {
    uVar2 = (**(code **)(*param_1 + 0x10))(param_1);
    if ((uVar2 & 1) == 0) {
      lVar3 = -0x3bc;
    }
    else {
      lVar3 = (**(code **)(*param_1 + 0x18))(param_1);
    }
    lVar4 = (**(code **)(*param_1 + 0x18))(param_1);
    lVar5 = lVar4;
    if (((-1 < lVar4) && (lVar5 = (**(code **)(*param_1 + 0x20))(param_1,0,0), -1 < lVar5)) &&
       (lVar5 = (**(code **)(*param_1 + 0x20))(param_1,0,2), -1 < lVar5)) {
      lVar5 = (**(code **)(*param_1 + 0x18))(param_1);
      lVar1 = 0;
      if (-1 < lVar5) {
        lVar1 = lVar4;
      }
      lVar5 = lVar5 - lVar1;
    }
    if ((-1 < lVar3) && (uVar2 = (**(code **)(*param_1 + 0x10))(param_1), (uVar2 & 1) != 0)) {
      (**(code **)(*param_1 + 0x20))(param_1,lVar3,0);
    }
    return lVar5;
  }
                    /* WARNING: Could not recover jumptable at 0x018e6b00. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  lVar3 = (**(code **)(*param_1 + 0x48))(param_1,0xfffffffffffffc44);
  return lVar3;
}

// ==== Aska::IStream::IsAsync() const
// vaddr 0x17e6bc0 | ghidra 0x18e6bc0 | size 8 | symbol _ZNK4Aska7IStream7IsAsyncEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska7IStream7IsAsyncEv(void)

{
  return 0;
}

// ==== Aska::IStream::IsBusy() const
// vaddr 0x17e6bc8 | ghidra 0x18e6bc8 | size 8 | symbol _ZNK4Aska7IStream6IsBusyEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska7IStream6IsBusyEv(void)

{
  return 0;
}

// ==== Aska::IStream::Wait(int) const
// vaddr 0x17e6bd0 | ghidra 0x18e6bd0 | size 8 | symbol _ZNK4Aska7IStream4WaitEi | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska7IStream4WaitEi(void)

{
  return 0;
}

// ==== Aska::IStream::Cancel(unsigned long)
// vaddr 0x17e6bd8 | ghidra 0x18e6bd8 | size 8 | symbol _ZN4Aska7IStream6CancelEm | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska7IStream6CancelEm(void)

{
  return 0;
}

// ==== Aska::IStream::WriteAsync(void const*, long, unsigned long, unsigned long, Aska::INotify*, long volatile*)
// vaddr 0x17e6be0 | ghidra 0x18e6be0 | size 224 | symbol _ZN4Aska7IStream10WriteAsyncEPKvlmmPNS_7INotifyEPVl | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZN4Aska7IStream10WriteAsyncEPKvlmmPNS_7INotifyEPVl
                (long *param_1,undefined8 param_2,undefined8 param_3,long param_4,ulong param_5,
                undefined8 *param_6,ulong *param_7)

{
  ulong uVar1;
  ulong uVar2;
  ulong uStack_50;
  undefined8 uStack_48;
  
  uStack_50 = 0;
  uStack_48 = 0;
  uVar1 = (**(code **)(*param_1 + 0x20))(param_1,param_3,0);
  if (-1 < (long)uVar1) {
    uVar2 = (**(code **)(*param_1 + 0x30))(param_1,param_2,param_4,param_5);
    if (uVar2 == param_5) {
      uStack_50 = param_5 * param_4;
      if (param_7 != (ulong *)0x0) {
        *param_7 = param_5;
      }
      goto joined_r0x018e6c88;
    }
    uVar1 = (**(code **)(*param_1 + 0x58))(param_1);
  }
  uStack_50 = uVar1;
  if (param_7 != (ulong *)0x0) {
    *param_7 = uVar1;
  }
joined_r0x018e6c88:
  if (param_6 != (undefined8 *)0x0) {
    (**(code **)*param_6)(param_6,&uStack_50);
  }
  return uVar1 >> 0x3f ^ 1;
}

// ==== Aska::IStream::ByteSwapInWrite(Aska::IStream*, void const*, unsigned long, unsigned long)
// vaddr 0x1f0231c | ghidra 0x200231c | size 1536 | symbol _ZN4Aska7IStream15ByteSwapInWriteEPS0_PKvmm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska7IStream15ByteSwapInWriteEPS0_PKvmm
               (long *param_1,ulong param_2,ulong param_3,ulong param_4)

{
  undefined1 uVar1;
  ushort uVar2;
  uint uVar3;
  ulong uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  undefined1 *puVar8;
  ushort *puVar9;
  undefined8 *puVar10;
  undefined1 (*pauVar11) [16];
  undefined1 *puVar12;
  ulong uVar13;
  ulong uVar14;
  undefined8 uVar15;
  undefined1 auVar16 [16];
  undefined8 uVar17;
  undefined1 auVar18 [16];
  
  uVar14 = param_3 - 1;
  uVar6 = (uint)param_4;
  if ((uVar14 & param_2) == 0) {
    switch(uVar14) {
    case 0:
      break;
    case 1:
      if (param_4 != 0) {
        if ((param_4 < 4) || (uVar4 = param_4 & 0xfffffffffffffffc, uVar4 == 0)) {
          uVar13 = 0;
          uVar5 = 0;
        }
        else {
          uVar5 = 0;
          uVar13 = 0;
          if (((int)(param_4 - 1) != -1) && (param_4 - 1 >> 0x20 == 0)) {
            uVar5 = (uint)uVar4;
            puVar9 = (ushort *)(param_2 + 4);
            uVar13 = uVar4;
            do {
              uVar15 = NEON_rev32((ulong)CONCAT24(puVar9[-1],(uint)puVar9[-2]),1);
              uVar17 = NEON_rev32((ulong)CONCAT24(puVar9[1],(uint)*puVar9),1);
              puVar9[-2] = (ushort)((ulong)uVar15 >> 0x10);
              *puVar9 = (ushort)((ulong)uVar17 >> 0x10);
              puVar9[-1] = (ushort)((ulong)uVar15 >> 0x30);
              uVar13 = uVar13 - 4;
              puVar9[1] = (ushort)((ulong)uVar17 >> 0x30);
              puVar9 = puVar9 + 4;
            } while (uVar13 != 0);
            uVar13 = uVar4;
            if (uVar4 == param_4) break;
          }
        }
        do {
          uVar5 = uVar5 + 1;
          uVar2 = *(ushort *)(param_2 + uVar13 * 2);
          *(ushort *)(param_2 + uVar13 * 2) = uVar2 >> 8 | uVar2 << 8;
          uVar13 = (ulong)uVar5;
        } while (uVar5 < param_4);
      }
      break;
    default:
      goto code_r0x02002340;
    case 3:
      if (param_4 != 0) {
        if ((param_4 < 4) || (uVar4 = param_4 & 0xfffffffffffffffc, uVar4 == 0)) {
          uVar13 = 0;
          uVar5 = 0;
        }
        else {
          uVar5 = 0;
          uVar13 = 0;
          if (((int)(param_4 - 1) != -1) && (param_4 - 1 >> 0x20 == 0)) {
            uVar5 = (uint)uVar4;
            puVar10 = (undefined8 *)(param_2 + 8);
            uVar13 = uVar4;
            do {
              uVar13 = uVar13 - 4;
              uVar15 = NEON_rev32(puVar10[-1],1);
              uVar17 = NEON_rev32(*puVar10,1);
              puVar10[-1] = uVar15;
              *puVar10 = uVar17;
              puVar10 = puVar10 + 2;
            } while (uVar13 != 0);
            uVar13 = uVar4;
            if (uVar4 == param_4) break;
          }
        }
        do {
          uVar5 = uVar5 + 1;
          uVar3 = *(uint *)(param_2 + uVar13 * 4);
          uVar3 = (uVar3 & 0xff00ff00) >> 8 | (uVar3 & 0xff00ff) << 8;
          *(uint *)(param_2 + uVar13 * 4) = uVar3 >> 0x10 | uVar3 << 0x10;
          uVar13 = (ulong)uVar5;
        } while (uVar5 < param_4);
      }
      break;
    case 7:
      if (param_4 != 0) {
        if ((param_4 < 4) || (uVar4 = param_4 & 0xfffffffffffffffc, uVar4 == 0)) {
          uVar13 = 0;
          uVar5 = 0;
        }
        else {
          uVar5 = 0;
          uVar13 = 0;
          if (((int)(param_4 - 1) != -1) && (param_4 - 1 >> 0x20 == 0)) {
            uVar5 = (uint)uVar4;
            pauVar11 = (undefined1 (*) [16])(param_2 + 0x10);
            uVar13 = uVar4;
            do {
              uVar13 = uVar13 - 4;
              auVar16 = NEON_rev64(pauVar11[-1],1);
              auVar18 = NEON_rev64(*pauVar11,1);
              *(long *)(pauVar11[-1] + 8) = auVar16._8_8_;
              *(long *)pauVar11[-1] = auVar16._0_8_;
              *(long *)(*pauVar11 + 8) = auVar18._8_8_;
              *(long *)*pauVar11 = auVar18._0_8_;
              pauVar11 = pauVar11 + 2;
            } while (uVar13 != 0);
            uVar13 = uVar4;
            if (uVar4 == param_4) break;
          }
        }
        do {
          uVar5 = uVar5 + 1;
          uVar4 = *(ulong *)(param_2 + uVar13 * 8);
          uVar4 = (uVar4 & 0xff00ff00ff00ff00) >> 8 | (uVar4 & 0xff00ff00ff00ff) << 8;
          uVar4 = (uVar4 & 0xffff0000ffff0000) >> 0x10 | (uVar4 & 0xffff0000ffff) << 0x10;
          *(ulong *)(param_2 + uVar13 * 8) = uVar4 >> 0x20 | uVar4 << 0x20;
          uVar13 = (ulong)uVar5;
        } while (uVar5 < param_4);
      }
    }
  }
  else {
code_r0x02002340:
    if (param_4 != 0) {
      if ((int)(param_3 >> 1) == 0) {
        if ((uVar6 < 2) || (uVar5 = uVar6 & 0xfffffffe, (param_4 & 0xfffffffe) == 0)) {
          uVar3 = 0;
        }
        else {
          uVar3 = 0;
          if (((int)(param_4 - 1) != -1) && (uVar7 = uVar5, param_4 - 1 >> 0x20 == 0)) {
            do {
              uVar7 = uVar7 - 2;
            } while (uVar7 != 0);
            uVar3 = uVar5;
            if (uVar5 == uVar6) goto code_r0x02002618;
          }
        }
        do {
          uVar3 = uVar3 + 1;
        } while (uVar3 < param_4);
      }
      else {
        uVar4 = 0;
        do {
          puVar8 = (undefined1 *)((param_2 - 1) + param_3 * (uVar4 + 1));
          puVar12 = (undefined1 *)(param_2 + param_3 * uVar4);
          uVar13 = param_3 >> 1 & 0xffffffff;
          do {
            uVar1 = *puVar12;
            uVar13 = uVar13 - 1;
            *puVar12 = *puVar8;
            *puVar8 = uVar1;
            puVar8 = puVar8 + -1;
            puVar12 = puVar12 + 1;
          } while (uVar13 != 0);
          uVar4 = (ulong)((int)uVar4 + 1);
        } while (uVar4 < param_4);
      }
    }
  }
code_r0x02002618:
  (**(code **)(*param_1 + 0x30))(param_1,param_2,param_3,param_4);
  if ((uVar14 & param_2) == 0) {
    switch(uVar14) {
    case 0:
      break;
    case 1:
      if (param_4 != 0) {
        if ((param_4 < 4) || (uVar14 = param_4 & 0xfffffffffffffffc, uVar14 == 0)) {
          uVar4 = 0;
          uVar6 = 0;
        }
        else {
          uVar6 = 0;
          uVar4 = 0;
          if (((int)(param_4 - 1) != -1) && (param_4 - 1 >> 0x20 == 0)) {
            uVar6 = (uint)uVar14;
            puVar9 = (ushort *)(param_2 + 4);
            uVar4 = uVar14;
            do {
              uVar15 = NEON_rev32((ulong)CONCAT24(puVar9[-1],(uint)puVar9[-2]),1);
              uVar17 = NEON_rev32((ulong)CONCAT24(puVar9[1],(uint)*puVar9),1);
              puVar9[-2] = (ushort)((ulong)uVar15 >> 0x10);
              *puVar9 = (ushort)((ulong)uVar17 >> 0x10);
              puVar9[-1] = (ushort)((ulong)uVar15 >> 0x30);
              uVar4 = uVar4 - 4;
              puVar9[1] = (ushort)((ulong)uVar17 >> 0x30);
              puVar9 = puVar9 + 4;
            } while (uVar4 != 0);
            uVar4 = uVar14;
            if (uVar14 == param_4) {
              return;
            }
          }
        }
        do {
          uVar6 = uVar6 + 1;
          uVar2 = *(ushort *)(param_2 + uVar4 * 2);
          *(ushort *)(param_2 + uVar4 * 2) = uVar2 >> 8 | uVar2 << 8;
          uVar4 = (ulong)uVar6;
        } while (uVar6 < param_4);
      }
      break;
    default:
      goto code_r0x02002634;
    case 3:
      if (param_4 != 0) {
        if ((param_4 < 4) || (uVar14 = param_4 & 0xfffffffffffffffc, uVar14 == 0)) {
          uVar4 = 0;
          uVar6 = 0;
        }
        else {
          uVar6 = 0;
          uVar4 = 0;
          if (((int)(param_4 - 1) != -1) && (param_4 - 1 >> 0x20 == 0)) {
            uVar6 = (uint)uVar14;
            puVar10 = (undefined8 *)(param_2 + 8);
            uVar4 = uVar14;
            do {
              uVar4 = uVar4 - 4;
              uVar15 = NEON_rev32(puVar10[-1],1);
              uVar17 = NEON_rev32(*puVar10,1);
              puVar10[-1] = uVar15;
              *puVar10 = uVar17;
              puVar10 = puVar10 + 2;
            } while (uVar4 != 0);
            uVar4 = uVar14;
            if (uVar14 == param_4) {
              return;
            }
          }
        }
        do {
          uVar6 = uVar6 + 1;
          uVar5 = *(uint *)(param_2 + uVar4 * 4);
          uVar5 = (uVar5 & 0xff00ff00) >> 8 | (uVar5 & 0xff00ff) << 8;
          *(uint *)(param_2 + uVar4 * 4) = uVar5 >> 0x10 | uVar5 << 0x10;
          uVar4 = (ulong)uVar6;
        } while (uVar6 < param_4);
      }
      break;
    case 7:
      if (param_4 != 0) {
        if ((param_4 < 4) || (uVar14 = param_4 & 0xfffffffffffffffc, uVar14 == 0)) {
          uVar4 = 0;
          uVar6 = 0;
        }
        else {
          uVar6 = 0;
          uVar4 = 0;
          if (((int)(param_4 - 1) != -1) && (param_4 - 1 >> 0x20 == 0)) {
            uVar6 = (uint)uVar14;
            pauVar11 = (undefined1 (*) [16])(param_2 + 0x10);
            uVar4 = uVar14;
            do {
              uVar4 = uVar4 - 4;
              auVar16 = NEON_rev64(pauVar11[-1],1);
              auVar18 = NEON_rev64(*pauVar11,1);
              *(long *)(pauVar11[-1] + 8) = auVar16._8_8_;
              *(long *)pauVar11[-1] = auVar16._0_8_;
              *(long *)(*pauVar11 + 8) = auVar18._8_8_;
              *(long *)*pauVar11 = auVar18._0_8_;
              pauVar11 = pauVar11 + 2;
            } while (uVar4 != 0);
            uVar4 = uVar14;
            if (uVar14 == param_4) {
              return;
            }
          }
        }
        do {
          uVar6 = uVar6 + 1;
          uVar14 = *(ulong *)(param_2 + uVar4 * 8);
          uVar14 = (uVar14 & 0xff00ff00ff00ff00) >> 8 | (uVar14 & 0xff00ff00ff00ff) << 8;
          uVar14 = (uVar14 & 0xffff0000ffff0000) >> 0x10 | (uVar14 & 0xffff0000ffff) << 0x10;
          *(ulong *)(param_2 + uVar4 * 8) = uVar14 >> 0x20 | uVar14 << 0x20;
          uVar4 = (ulong)uVar6;
        } while (uVar6 < param_4);
      }
    }
  }
  else {
code_r0x02002634:
    if (param_4 != 0) {
      if ((int)(param_3 >> 1) == 0) {
        if ((uVar6 < 2) || (uVar5 = uVar6 & 0xfffffffe, (param_4 & 0xfffffffe) == 0)) {
          uVar3 = 0;
        }
        else {
          uVar3 = 0;
          if (((int)(param_4 - 1) != -1) && (uVar7 = uVar5, param_4 - 1 >> 0x20 == 0)) {
            do {
              uVar7 = uVar7 - 2;
            } while (uVar7 != 0);
            uVar3 = uVar5;
            if (uVar5 == uVar6) {
              return;
            }
          }
        }
        do {
          uVar3 = uVar3 + 1;
        } while (uVar3 < param_4);
      }
      else {
        uVar14 = 0;
        do {
          puVar8 = (undefined1 *)((param_2 - 1) + param_3 * (uVar14 + 1));
          puVar12 = (undefined1 *)(param_2 + param_3 * uVar14);
          uVar4 = param_3 >> 1 & 0xffffffff;
          do {
            uVar1 = *puVar12;
            uVar4 = uVar4 - 1;
            *puVar12 = *puVar8;
            *puVar8 = uVar1;
            puVar8 = puVar8 + -1;
            puVar12 = puVar12 + 1;
          } while (uVar4 != 0);
          uVar14 = (ulong)((int)uVar14 + 1);
        } while (uVar14 < param_4);
      }
    }
  }
  return;
}

// ==== Aska::File::Close()
// vaddr 0x1f1f510 | ghidra 0x201f510 | size 72 | symbol _ZN4Aska4File5CloseEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska4File5CloseEv(long param_1)

{
  if (*(long *)(param_1 + 0x10) == 0) {
    return;
  }
  if (*(char *)(param_1 + 8) == '\0') {
    fflush();
    if (*(long *)(param_1 + 0x10) == 0) {
      return;
    }
    if (*(char *)(param_1 + 8) == '\0') {
      fclose();
      goto code_r0x0201f530;
    }
  }
  AAsset_close();
  *(undefined8 *)(param_1 + 0x10) = 0;
code_r0x0201f530:
  *(undefined8 *)(param_1 + 0x10) = 0;
  return;
}

// ==== Aska::File::Open(char const*, bool, bool, bool)
// vaddr 0x1f1f570 | ghidra 0x201f570 | size 172 | symbol _ZN4Aska4File4OpenEPKcbbb | lib libSOA-3.7.0.so | 2026-10-04
bool _ZN4Aska4File4OpenEPKcbbb(long param_1,undefined8 param_2,ulong param_3,uint param_4)

{
  bool bVar1;
  long lVar2;
  undefined *puVar3;
  
  if (*(long *)(param_1 + 0x10) == 0) {
    if (*(char *)(param_1 + 8) == '\0') {
      if ((param_4 & 1) == 0) {
        if ((param_3 & 1) == 0) {
          lVar2 = fopen(param_2,&UNK_0296e96f/*"ab+"*/);
          *(long *)(param_1 + 0x10) = lVar2;
          if (lVar2 != 0) {
            fclose();
          }
          puVar3 = &UNK_0296e973/*"rb+"*/;
        }
        else {
          puVar3 = &UNK_0296e96c/*"rb"*/;
        }
      }
      else {
        if ((param_3 & 1) != 0) goto code_r0x0201f588;
        puVar3 = &UNK_0296e968/*"wb+"*/;
      }
      lVar2 = fopen(param_2,puVar3);
    }
    else {
      lVar2 = AAssetManager_open(*(undefined8 *)PTR__ZN4Aska4Boot15m_pAssetManagerE_02cbe710,param_2,0)
      ;
    }
    bVar1 = lVar2 != 0;
    *(long *)(param_1 + 0x10) = lVar2;
  }
  else {
code_r0x0201f588:
    bVar1 = false;
  }
  return bVar1;
}

// ==== Aska::File::DistanceToLineBreakOrEndOrNonPrintable()
// vaddr 0x1f1f61c | ghidra 0x201f61c | size 596 | symbol _ZN4Aska4File38DistanceToLineBreakOrEndOrNonPrintableEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska4File38DistanceToLineBreakOrEndOrNonPrintableEv(long param_1)

{
  int iVar1;
  ulong uVar2;
  long lVar3;
  long lVar4;
  ulong uVar5;
  long lVar6;
  undefined8 uVar7;
  char acStack_24 [4];
  
  if (*(long *)(param_1 + 0x10) == 0) {
    uVar2 = 0;
    lVar3 = 0;
    lVar4 = *(long *)(param_1 + 0x10);
    if (lVar4 != 0) goto code_r0x0201f658;
    uVar5 = 0;
    goto code_r0x0201f66c;
  }
  if (*(char *)(param_1 + 8) == '\0') {
    uVar7 = ftell();
    iVar1 = fseek(*(undefined8 *)(param_1 + 0x10),0,2);
    uVar2 = 0;
    if (iVar1 == 0) {
      uVar2 = ftell(*(undefined8 *)(param_1 + 0x10));
      fseek(*(undefined8 *)(param_1 + 0x10),uVar7,0);
      lVar3 = *(long *)(param_1 + 0x10);
    }
    else {
      lVar3 = *(long *)(param_1 + 0x10);
    }
  }
  else {
    uVar2 = AAsset_getLength();
    lVar3 = *(long *)(param_1 + 0x10);
  }
  if (lVar3 != 0) {
    if (*(char *)(param_1 + 8) == '\0') {
      fseek(lVar3,0,1);
      lVar3 = ftell(*(undefined8 *)(param_1 + 0x10));
    }
    else {
      lVar3 = AAsset_seek(lVar3,0,1);
    }
    lVar4 = *(long *)(param_1 + 0x10);
    if (lVar4 != 0) goto code_r0x0201f658;
    uVar5 = 0;
    goto code_r0x0201f66c;
  }
  lVar3 = 0;
  do {
    lVar4 = *(long *)(param_1 + 0x10);
    uVar5 = 0;
    if (lVar4 == 0) {
code_r0x0201f66c:
      if (uVar2 <= uVar5) {
code_r0x0201f74c:
        lVar4 = 0;
        lVar6 = *(long *)(param_1 + 0x10);
        goto joined_r0x0201f754;
      }
    }
    else {
code_r0x0201f658:
      if (*(char *)(param_1 + 8) != '\0') {
        uVar5 = AAsset_seek(lVar4,0,1);
        goto code_r0x0201f66c;
      }
      fseek(lVar4,0,1);
      uVar5 = ftell(*(undefined8 *)(param_1 + 0x10));
      if (uVar2 <= uVar5) goto code_r0x0201f74c;
    }
    lVar4 = *(long *)(param_1 + 0x10);
    if (lVar4 == 0) {
code_r0x0201f6f0:
      uVar5 = 0;
      if (uVar2 == 0) break;
    }
    else {
      if (*(char *)(param_1 + 8) == '\0') {
        fread(acStack_24,1,1,lVar4);
        lVar4 = *(long *)(param_1 + 0x10);
      }
      else {
        AAsset_read(lVar4,acStack_24,1);
        lVar4 = *(long *)(param_1 + 0x10);
      }
      if (lVar4 == 0) goto code_r0x0201f6f0;
      if (*(char *)(param_1 + 8) == '\0') {
        fseek(lVar4,0,1);
        uVar5 = ftell(*(undefined8 *)(param_1 + 0x10));
      }
      else {
        uVar5 = AAsset_seek(lVar4,0,1);
      }
      if (uVar5 == uVar2) break;
    }
  } while ('\x1f' < acStack_24[0]);
  lVar6 = *(long *)(param_1 + 0x10);
  lVar4 = 0;
  if (lVar6 != 0) {
    if (*(char *)(param_1 + 8) == '\0') {
      fseek(lVar6,0,1);
      lVar4 = ftell(*(undefined8 *)(param_1 + 0x10));
    }
    else {
      lVar4 = AAsset_seek(lVar6,0,1);
    }
  }
  lVar4 = (-lVar3 - (ulong)(uVar5 != uVar2)) + lVar4;
  lVar6 = *(long *)(param_1 + 0x10);
joined_r0x0201f754:
  if (lVar6 != 0) {
    if (*(char *)(param_1 + 8) == '\0') {
      fseek(lVar6,lVar3,0);
      ftell(*(undefined8 *)(param_1 + 0x10));
    }
    else {
      AAsset_seek(lVar6,lVar3,0);
    }
  }
  return lVar4;
}

// ==== Aska::File::GetFileSizeL() const
// vaddr 0x1f1f870 | ghidra 0x201f870 | size 128 | symbol _ZNK4Aska4File12GetFileSizeLEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska4File12GetFileSizeLEv(long param_1)

{
  int iVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  
  if (*(long *)(param_1 + 0x10) != 0) {
    if (*(char *)(param_1 + 8) != '\0') {
      uVar2 = (*(code *)PTR_AAsset_getLength_02c98450)();
      return uVar2;
    }
    uVar2 = ftell();
    iVar1 = fseek(*(undefined8 *)(param_1 + 0x10),0,2);
    if (iVar1 == 0) {
      uVar3 = ftell(*(undefined8 *)(param_1 + 0x10));
      fseek(*(undefined8 *)(param_1 + 0x10),uVar2,0);
      return uVar3;
    }
  }
  return 0;
}

// ==== Aska::File::Read(void*, unsigned long, unsigned int*)
// vaddr 0x1f1f8f0 | ghidra 0x201f8f0 | size 144 | symbol _ZN4Aska4File4ReadEPvmPj | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZN4Aska4File4ReadEPvmPj(long param_1,undefined8 param_2,ulong param_3,undefined4 *param_4)

{
  int iVar1;
  ulong uVar2;
  undefined4 *puVar3;
  long lVar4;
  
  lVar4 = *(long *)(param_1 + 0x10);
  if (lVar4 != 0) {
    if (*(char *)(param_1 + 8) == '\0') {
      uVar2 = fread(param_2,1,param_3,lVar4);
      if (param_4 != (undefined4 *)0x0) {
        puVar3 = (undefined4 *)__errno();
        *param_4 = *puVar3;
      }
      if (uVar2 <= param_3) {
        return uVar2;
      }
    }
    else {
      iVar1 = AAsset_read(lVar4,param_2,param_3);
      if ((ulong)(long)iVar1 <= param_3) {
        return (long)iVar1;
      }
      if (param_4 != (undefined4 *)0x0) {
        *param_4 = (int)param_3;
      }
    }
  }
  return 0;
}

// ==== Aska::File::SeekL(long, Aska::File::Origin)
// vaddr 0x1f1f980 | ghidra 0x201f980 | size 80 | symbol _ZN4Aska4File5SeekLElNS0_6OriginE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska4File5SeekLElNS0_6OriginE(long param_1,undefined8 param_2,ulong param_3)

{
  long lVar1;
  
  lVar1 = *(long *)(param_1 + 0x10);
  if (lVar1 == 0) {
    return;
  }
  if (*(char *)(param_1 + 8) != '\0') {
    (*(code *)PTR_AAsset_seek_02cabb10)
              (lVar1,param_2,*(undefined4 *)(&UNK_0296e97c + (param_3 & 0xffffffff) * 4));
    return;
  }
  fseek(lVar1,param_2,*(undefined4 *)(&UNK_0296e97c + (param_3 & 0xffffffff) * 4));
  (*(code *)PTR_ftell_02cb3080)(*(undefined8 *)(param_1 + 0x10));
  return;
}

// ==== Aska::File::SetFileSize(unsigned long)
// vaddr 0x1f1f9d0 | ghidra 0x201f9d0 | size 8 | symbol _ZN4Aska4File11SetFileSizeEm | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska4File11SetFileSizeEm(void)

{
  return 0;
}

// ==== Aska::File::Flush()
// vaddr 0x1f1f9d8 | ghidra 0x201f9d8 | size 28 | symbol _ZN4Aska4File5FlushEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska4File5FlushEv(long param_1)

{
  if ((*(long *)(param_1 + 0x10) != 0) && (*(char *)(param_1 + 8) == '\0')) {
    (*(code *)PTR_fflush_02c93a20)();
    return;
  }
  return;
}

// ==== Aska::File::ReadWithOffset(void*, unsigned long, unsigned long, unsigned int*)
// vaddr 0x1f1f9f4 | ghidra 0x201f9f4 | size 288 | symbol _ZN4Aska4File14ReadWithOffsetEPvmmPj | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZN4Aska4File14ReadWithOffsetEPvmmPj
                (long param_1,undefined8 param_2,ulong param_3,undefined8 param_4,
                undefined4 *param_5)

{
  int iVar1;
  long lVar2;
  undefined4 *puVar3;
  ulong uVar4;
  
  lVar2 = *(long *)(param_1 + 0x10);
  if (lVar2 != 0) {
    if (*(char *)(param_1 + 8) == '\0') {
      iVar1 = fseek(lVar2,param_4,0);
      if (iVar1 == 0) {
        lVar2 = *(long *)(param_1 + 0x10);
        if (lVar2 != 0) {
          if (*(char *)(param_1 + 8) == '\0') {
            uVar4 = fread(param_2,1,param_3,lVar2);
            if (param_5 != (undefined4 *)0x0) {
              puVar3 = (undefined4 *)__errno();
              *param_5 = *puVar3;
            }
            if (uVar4 <= param_3) {
              return uVar4;
            }
          }
          else {
            iVar1 = AAsset_read(lVar2,param_2,param_3);
            if ((ulong)(long)iVar1 <= param_3) {
              return (long)iVar1;
            }
            if (param_5 != (undefined4 *)0x0) {
              *param_5 = (int)param_3;
            }
          }
        }
      }
      else if (param_5 != (undefined4 *)0x0) {
        puVar3 = (undefined4 *)__errno();
        *param_5 = *puVar3;
        return 0;
      }
    }
    else {
      lVar2 = AAsset_seek(lVar2,param_4,0);
      if (lVar2 < 0) {
        if (param_5 != (undefined4 *)0x0) {
          *param_5 = (int)lVar2;
          return 0;
        }
      }
      else {
        iVar1 = AAsset_read(*(undefined8 *)(param_1 + 0x10),param_2,param_3);
        if ((ulong)(long)iVar1 <= param_3) {
          return (long)iVar1;
        }
        if (param_5 != (undefined4 *)0x0) {
          *param_5 = (int)param_3;
          return 0;
        }
      }
    }
  }
  return 0;
}

// ==== Aska::File::Write(void const*, unsigned long)
// vaddr 0x1f1fb14 | ghidra 0x201fb14 | size 80 | symbol _ZN4Aska4File5WriteEPKvm | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska4File5WriteEPKvm(long param_1,undefined8 param_2,long param_3)

{
  long lVar1;
  
  if ((*(long *)(param_1 + 0x10) != 0) && (*(char *)(param_1 + 8) == '\0')) {
    lVar1 = fwrite(param_2,1,param_3);
    if (lVar1 == param_3) {
      return param_3;
    }
    *(int *)PTR__ZN4Aska4File12ms_LastErrorE_02cb7608 = (int)param_3;
  }
  return 0;
}

// ==== Aska::File::Seek(long, Aska::File::Origin)
// vaddr 0x1f1fb64 | ghidra 0x201fb64 | size 80 | symbol _ZN4Aska4File4SeekElNS0_6OriginE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska4File4SeekElNS0_6OriginE(long param_1,undefined8 param_2,ulong param_3)

{
  long lVar1;
  
  lVar1 = *(long *)(param_1 + 0x10);
  if (lVar1 == 0) {
    return;
  }
  if (*(char *)(param_1 + 8) != '\0') {
    (*(code *)PTR_AAsset_seek_02cabb10)
              (lVar1,param_2,*(undefined4 *)(&UNK_0296e97c + (param_3 & 0xffffffff) * 4));
    return;
  }
  fseek(lVar1,param_2,*(undefined4 *)(&UNK_0296e97c + (param_3 & 0xffffffff) * 4));
  (*(code *)PTR_ftell_02cb3080)(*(undefined8 *)(param_1 + 0x10));
  return;
}

// ==== Aska::File::GetFileSize() const
// vaddr 0x1f1fbb4 | ghidra 0x201fbb4 | size 128 | symbol _ZNK4Aska4File11GetFileSizeEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska4File11GetFileSizeEv(long param_1)

{
  int iVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  
  if (*(long *)(param_1 + 0x10) != 0) {
    if (*(char *)(param_1 + 8) != '\0') {
      uVar2 = (*(code *)PTR_AAsset_getLength_02c98450)();
      return uVar2;
    }
    uVar2 = ftell();
    iVar1 = fseek(*(undefined8 *)(param_1 + 0x10),0,2);
    if (iVar1 == 0) {
      uVar3 = ftell(*(undefined8 *)(param_1 + 0x10));
      fseek(*(undefined8 *)(param_1 + 0x10),uVar2,0);
      return uVar3;
    }
  }
  return 0;
}

// ==== Aska::File::CreateDirectory(char const*)
// vaddr 0x1f1fc68 | ghidra 0x201fc68 | size 228 | symbol _ZN4Aska4File15CreateDirectoryEPKc | lib libSOA-3.7.0.so | 2026-10-04
bool _ZN4Aska4File15CreateDirectoryEPKc(char *param_1)

{
  char cVar1;
  int iVar2;
  long lVar3;
  int *piVar4;
  char *pcVar5;
  char acStack_134 [260];
  
  pcVar5 = acStack_134;
  do {
    cVar1 = *param_1;
    if (cVar1 == '/') {
      *pcVar5 = '\0';
      if (acStack_134[0] != '\0') {
        lVar3 = fopen(acStack_134,&UNK_0296e96c/*"rb"*/);
        if (lVar3 == 0) {
          iVar2 = mkdir(acStack_134,0x1ff);
          if ((iVar2 != 0) && (piVar4 = (int *)__errno(), *piVar4 != 0x11)) {
            return false;
          }
        }
        else {
          fclose();
        }
      }
    }
    else if (cVar1 == '\0') {
      *pcVar5 = '\0';
      lVar3 = fopen(acStack_134,&UNK_0296e96c/*"rb"*/);
      if (lVar3 == 0) {
        iVar2 = mkdir(acStack_134,0x1ff);
        if (iVar2 != 0) {
          piVar4 = (int *)__errno();
          return *piVar4 == 0x11;
        }
      }
      else {
        fclose();
      }
      return true;
    }
    *pcVar5 = cVar1;
    param_1 = param_1 + 1;
    pcVar5 = pcVar5 + 1;
  } while( true );
}

// ==== Aska::File::DoesExist(char const*, bool)
// vaddr 0x1f1fd4c | ghidra 0x201fd4c | size 104 | symbol _ZN4Aska4File9DoesExistEPKcb | lib libSOA-3.7.0.so | 2026-10-04
bool _ZN4Aska4File9DoesExistEPKcb(undefined8 param_1,ulong param_2)

{
  long lVar1;
  
  if ((param_2 & 1) == 0) {
    lVar1 = fopen(param_1,&UNK_0296e96c/*"rb"*/);
    if (lVar1 != 0) {
      fclose(lVar1);
    }
  }
  else {
    lVar1 = AAssetManager_open(*(undefined8 *)PTR__ZN4Aska4Boot15m_pAssetManagerE_02cbe710,param_1,0);
    if (lVar1 != 0) {
      AAsset_close(lVar1);
    }
  }
  return lVar1 != 0;
}

// ==== Aska::File::TraverseDir(char const*, Aska::File::FINDDATA*, int, unsigned int)
// vaddr 0x1f1fdb4 | ghidra 0x201fdb4 | size 612 | symbol _ZN4Aska4File11TraverseDirEPKcPNS0_8FINDDATAEij | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZN4Aska4File11TraverseDirEPKcPNS0_8FINDDATAEij
                (undefined8 param_1,long param_2,uint param_3,uint param_4)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  ulong uVar4;
  long lVar5;
  long lVar6;
  ulong uVar7;
  undefined1 *puStack_250;
  undefined8 uStack_248;
  undefined1 auStack_240 [512];
  
  uVar2 = 0x7fffffff;
  if (param_2 != 0) {
    uVar2 = param_3;
  }
  uVar4 = strlen();
  if (uVar4 < 0x200) {
    strcpy(auStack_240,param_1);
  }
  else {
    raise(5);
  }
  if (param_2 != 0) {
    memset(param_2,0,-(ulong)(param_3 >> 0x1f) & 0xffffffc000000000 | (ulong)param_3 << 6);
  }
  lVar5 = strlen(auStack_240);
  if (lVar5 != 0) {
    iVar3 = strcmp(auStack_240 + lVar5 + -3,&UNK_0296e977/*"*.*"*/);
    if (iVar3 == 0) {
      auStack_240[lVar5 + -3] = 0;
    }
    else if (auStack_240[lVar5 + -1] == '*') {
      auStack_240[lVar5 + -1] = 0;
    }
  }
  lVar5 = strlen(auStack_240);
  if (lVar5 == 0) {
code_r0x0201fe9c:
    if ((param_4 >> 9 & 1) == 0) goto code_r0x0201fea0;
code_r0x0201ff14:
    lVar5 = AAssetManager_openDir(*(undefined8 *)PTR__ZN4Aska4Boot15m_pAssetManagerE_02cbe710,auStack_240)
    ;
    if (lVar5 != 0) {
      if ((int)uVar2 < 1) {
        uVar4 = 0;
      }
      else if (param_2 == 0) {
        uVar4 = 0;
        do {
          lVar6 = AAssetDir_getNextFileName(lVar5);
          if (lVar6 == 0) break;
          uVar1 = (int)uVar4 + 1;
          uVar4 = (ulong)uVar1;
        } while ((int)uVar1 < (int)uVar2);
      }
      else {
        uVar4 = 0;
        do {
          lVar6 = AAssetDir_getNextFileName(lVar5);
          if (lVar6 == 0) break;
          uVar7 = strlen(lVar6);
          if (uVar7 < 0x40) {
            strcpy(param_2,lVar6);
          }
          else {
            raise(5);
          }
          uVar4 = uVar4 + 1;
          param_2 = param_2 + 0x40;
        } while ((long)uVar4 < (long)(int)uVar2);
      }
      goto code_r0x0201ffdc;
    }
  }
  else {
    iVar3 = strcmp(auStack_240 + lVar5 + -1,&UNK_029c5d3e/*"/"*/);
    if (iVar3 != 0) goto code_r0x0201fe9c;
    auStack_240[lVar5 + -1] = 0;
    if ((param_4 >> 9 & 1) != 0) goto code_r0x0201ff14;
code_r0x0201fea0:
    puStack_250 = auStack_240;
    uStack_248 = 0;
    lVar5 = fts_open(&puStack_250,2,0);
    if (lVar5 != 0) {
      if (param_2 == 0) {
        if ((int)uVar2 < 1) goto code_r0x0201ffd0;
        uVar4 = 0;
        do {
          lVar6 = fts_read(lVar5);
          if (lVar6 == 0) break;
        } while ((*(long *)(lVar6 + 0x48) == 0) ||
                (uVar1 = (int)uVar4 + 1, uVar4 = (ulong)uVar1, (int)uVar1 < (int)uVar2));
      }
      else if ((int)uVar2 < 1) {
code_r0x0201ffd0:
        uVar4 = 0;
      }
      else {
        uVar4 = 0;
        do {
          do {
            lVar6 = fts_read(lVar5);
            if (lVar6 == 0) goto code_r0x0201ffd4;
          } while (*(long *)(lVar6 + 0x48) == 0);
          strncpy(param_2 + uVar4 * 0x40,lVar6 + 0x78,0x40);
          uVar4 = uVar4 + 1;
        } while ((long)uVar4 < (long)(int)uVar2);
      }
code_r0x0201ffd4:
      fts_close(lVar5);
      goto code_r0x0201ffdc;
    }
  }
  uVar4 = 0xffffffff;
code_r0x0201ffdc:
  return uVar4 & 0xffffffff;
}

// ==== Aska::File::PutString(char const*, std::__va_list)
// vaddr 0x1f20018 | ghidra 0x2020018 | size 304 | symbol _ZN4Aska4File9PutStringEPKcSt9__va_list | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZN4Aska4File9PutStringEPKcSt9__va_list(long param_1,undefined8 param_2,undefined8 *param_3)

{
  int iVar1;
  int iVar2;
  undefined1 *puVar3;
  ulong uVar4;
  ulong uVar5;
  undefined1 auStack_a0 [64];
  undefined8 uStack_60;
  undefined8 uStack_58;
  undefined8 uStack_50;
  undefined8 uStack_48;
  
  uStack_48 = param_3[3];
  uStack_50 = param_3[2];
  uStack_58 = param_3[1];
  uStack_60 = *param_3;
  puVar3 = auStack_a0;
  iVar1 = vsnprintf(auStack_a0,0x3f,param_2,&uStack_60);
  if (0x3f < iVar1) {
    puVar3 = (undefined1 *)operator new[](unsigned long, std::nothrow_t const&)((long)(iVar1 + 1),PTR__ZSt7nothrow_02cb9a80);
    if (puVar3 != (undefined1 *)0x0) {
      uStack_48 = param_3[3];
      uStack_50 = param_3[2];
      uStack_58 = param_3[1];
      uStack_60 = *param_3;
      iVar2 = vsnprintf(puVar3,(long)(iVar1 + 1) + -1,param_2,&uStack_60);
      if (iVar2 <= iVar1) goto code_r0x020200d0;
      operator delete[](void*)(puVar3);
    }
    uVar5 = 0xffffffff;
    goto code_r0x0202012c;
  }
code_r0x020200d0:
  uVar5 = strlen(puVar3);
  if ((*(long *)(param_1 + 0x10) == 0) || (*(char *)(param_1 + 8) != '\0')) {
code_r0x02020110:
    uVar5 = 0;
  }
  else {
    uVar4 = fwrite(puVar3,1,uVar5);
    if (uVar4 != uVar5) {
      *(int *)PTR__ZN4Aska4File12ms_LastErrorE_02cb7608 = (int)uVar5;
      goto code_r0x02020110;
    }
  }
  if ((puVar3 != (undefined1 *)0x0) && (puVar3 != auStack_a0)) {
    operator delete[](void*)(puVar3);
  }
code_r0x0202012c:
  return uVar5 & 0xffffffff;
}

// ==== Aska::File::GetNumberOfFoundFiles(char const*, unsigned int)
// vaddr 0x1f20148 | ghidra 0x2020148 | size 20 | symbol _ZN4Aska4File21GetNumberOfFoundFilesEPKcj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska4File21GetNumberOfFoundFilesEPKcj(undefined8 param_1,undefined4 param_2)

{
  (*(code *)PTR__ZN4Aska4File11TraverseDirEPKcPNS0_8FINDDATAEij_02c8e5f0)(param_1,0,0,param_2);
  return;
}

// ==== Aska::File::FindFiles(char const*, Aska::File::FINDDATA*, int, unsigned int)
// vaddr 0x1f2015c | ghidra 0x202015c | size 4 | symbol _ZN4Aska4File9FindFilesEPKcPNS0_8FINDDATAEij | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska4File9FindFilesEPKcPNS0_8FINDDATAEij(void)

{
  (*(code *)PTR__ZN4Aska4File11TraverseDirEPKcPNS0_8FINDDATAEij_02c8e5f0)();
  return;
}

// ==== Aska::File::IsReadOnly(char const*)
// vaddr 0x1f20160 | ghidra 0x2020160 | size 8 | symbol _ZN4Aska4File10IsReadOnlyEPKc | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska4File10IsReadOnlyEPKc(void)

{
  return 1;
}

// ==== Aska::File::GetFileSizeL(char const*, bool)
// vaddr 0x1f20168 | ghidra 0x2020168 | size 208 | symbol _ZN4Aska4File12GetFileSizeLEPKcb | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska4File12GetFileSizeLEPKcb(undefined8 param_1,ulong param_2)

{
  int iVar1;
  long lVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  
  if ((param_2 & 1) == 0) {
    lVar2 = fopen(param_1,&UNK_0296e96c/*"rb"*/);
  }
  else {
    lVar2 = AAssetManager_open(*(undefined8 *)PTR__ZN4Aska4Boot15m_pAssetManagerE_02cbe710,param_1,0);
  }
  if (lVar2 == 0) {
    uVar3 = 0;
  }
  else if ((param_2 & 1) == 0) {
    uVar4 = ftell(lVar2);
    iVar1 = fseek(lVar2,0,2);
    uVar3 = 0;
    if (iVar1 == 0) {
      uVar3 = ftell(lVar2);
      fseek(lVar2,uVar4,0);
    }
    fflush(lVar2);
    fclose(lVar2);
  }
  else {
    uVar3 = AAsset_getLength(lVar2);
    AAsset_close(lVar2);
  }
  return uVar3;
}

// ==== Aska::File::GetFileSize(char const*, bool)
// vaddr 0x1f20238 | ghidra 0x2020238 | size 8 | symbol _ZN4Aska4File11GetFileSizeEPKcb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska4File11GetFileSizeEPKcb(undefined8 param_1,uint param_2)

{
  (*(code *)PTR__ZN4Aska4File12GetFileSizeLEPKcb_02ca5898)(param_1,param_2 & 1);
  return;
}

// ==== Aska::File::DeleteFile(char const*)
// vaddr 0x1f20240 | ghidra 0x2020240 | size 24 | symbol _ZN4Aska4File10DeleteFileEPKc | lib libSOA-3.7.0.so | 2026-10-04
bool _ZN4Aska4File10DeleteFileEPKc(void)

{
  int iVar1;
  
  iVar1 = remove();
  return iVar1 == 0;
}

// ==== Aska::File::CopyFile(char const*, char const*, bool)
// vaddr 0x1f20258 | ghidra 0x2020258 | size 8 | symbol _ZN4Aska4File8CopyFileEPKcS2_b | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska4File8CopyFileEPKcS2_b(void)

{
  return 0;
}

// ==== Aska::File::MoveFile(char const*, char const*)
// vaddr 0x1f20260 | ghidra 0x2020260 | size 24 | symbol _ZN4Aska4File8MoveFileEPKcS2_ | lib libSOA-3.7.0.so | 2026-10-04
bool _ZN4Aska4File8MoveFileEPKcS2_(void)

{
  int iVar1;
  
  iVar1 = rename();
  return iVar1 == 0;
}

// ==== Aska::File::OpenAndDumpToBuffer(char const*, bool, char*, unsigned long*, bool)
// vaddr 0x1f20278 | ghidra 0x2020278 | size 436 | symbol _ZN4Aska4File19OpenAndDumpToBufferEPKcbPcPmb | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska4File19OpenAndDumpToBufferEPKcbPcPmb
               (undefined8 param_1,uint param_2,long param_3,ulong *param_4,uint param_5)

{
  long lVar1;
  int iVar2;
  long lVar3;
  long lVar4;
  undefined8 uVar5;
  
  if ((param_5 & 1) == 0) {
    lVar3 = fopen(param_1,&UNK_0296e96c/*"rb"*/);
  }
  else {
    lVar3 = AAssetManager_open(*(undefined8 *)PTR__ZN4Aska4Boot15m_pAssetManagerE_02cbe710,param_1,0);
  }
  if (lVar3 != 0) {
    if ((param_5 & 1) == 0) {
      uVar5 = ftell(lVar3);
      iVar2 = fseek(lVar3,0,2);
      lVar4 = 0;
      if (iVar2 == 0) {
        lVar4 = ftell(lVar3);
        fseek(lVar3,uVar5,0);
      }
    }
    else {
      lVar4 = AAsset_getLength(lVar3);
    }
    lVar1 = 0;
    if ((param_2 & 1) == 0) {
      lVar1 = 2;
    }
    if (param_3 == 0) {
      param_3 = operator new[](unsigned long, std::nothrow_t const&)(lVar4 + lVar1,PTR__ZSt7nothrow_02cb9a80);
      if (param_3 != 0) goto code_r0x02020384;
    }
    else if (*param_4 <= (ulong)(lVar4 + lVar1)) {
code_r0x02020384:
      if ((param_5 & 1) == 0) {
        fread(param_3,1,lVar4,lVar3);
      }
      else {
        AAsset_read(lVar3,param_3,lVar4);
      }
      if ((param_2 & 1) == 0) {
        *(undefined2 *)(param_3 + lVar4) = 10;
      }
      if ((param_5 & 1) == 0) {
        fflush(lVar3);
        fclose(lVar3);
      }
      else {
        AAsset_close(lVar3);
      }
      if (param_4 != (ulong *)0x0) {
        *param_4 = lVar4 + ((ulong)~param_2 & 1);
        return param_3;
      }
      return param_3;
    }
    if ((param_5 & 1) == 0) {
      fflush(lVar3);
      fclose(lVar3);
    }
    else {
      AAsset_close(lVar3);
    }
  }
  if (param_4 != (ulong *)0x0) {
    *param_4 = 0;
  }
  return 0;
}

// ==== Aska::FileStream::Open(char const*, bool, bool, Aska::Machine::Endian)
// vaddr 0x1f21644 | ghidra 0x2021644 | size 148 | symbol _ZN4Aska10FileStream4OpenEPKcbbNS_7Machine6EndianE | lib libSOA-3.7.0.so | 2026-10-04
bool _ZN4Aska10FileStream4OpenEPKcbbNS_7Machine6EndianE
               (long *param_1,undefined8 param_2,uint param_3,uint param_4,byte param_5)

{
  bool bVar1;
  ulong uVar2;
  
  if (param_1[3] != 0) {
    Aska::File::Close()(param_1 + 1);
  }
  *(byte *)(param_1 + 5) = ~param_5 & 1;
  uVar2 = Aska::File::Open(char const*, bool, bool, bool)(param_1 + 1,param_2,param_3 & 1,param_4 & 1,0);
  bVar1 = (uVar2 & 1) == 0;
  if (bVar1) {
    (**(code **)(*param_1 + 0x48))(param_1,0xfffffffffffffc40);
  }
  return !bVar1;
}

// ==== Aska::FileStream::Close()
// vaddr 0x1f216d8 | ghidra 0x20216d8 | size 20 | symbol _ZN4Aska10FileStream5CloseEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10FileStream5CloseEv(long param_1)

{
  if (*(long *)(param_1 + 0x18) != 0) {
    (*(code *)PTR__ZN4Aska4File5CloseEv_02c8e880)(param_1 + 8);
    return;
  }
  return;
}

// ==== Aska::FileStream::Seek(long, int)
// vaddr 0x1f216ec | ghidra 0x20216ec | size 156 | symbol _ZN4Aska10FileStream4SeekEli | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska10FileStream4SeekEli(long *param_1,undefined8 param_2,int param_3)

{
  ulong uVar1;
  undefined8 uVar2;
  long lVar3;
  
  uVar1 = (**(code **)(*param_1 + 0x10))();
  if ((uVar1 & 1) == 0) {
    lVar3 = *param_1;
    uVar2 = 0xfffffffffffffc44;
code_r0x0202173c:
                    /* WARNING: Could not recover jumptable at 0x0202174c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar2 = (**(code **)(lVar3 + 0x48))(param_1,uVar2);
    return uVar2;
  }
  if (param_3 == 2) {
    uVar2 = 2;
  }
  else if (param_3 == 1) {
    uVar2 = 1;
  }
  else {
    if (param_3 != 0) {
      lVar3 = *param_1;
      uVar2 = 0xfffffffffffffc43;
      goto code_r0x0202173c;
    }
    uVar2 = 0;
  }
  Aska::File::Seek(long, Aska::File::Origin)(param_1 + 1,param_2,uVar2);
  return 0;
}

// ==== Aska::FileStream::Tell() const
// vaddr 0x1f21788 | ghidra 0x2021788 | size 68 | symbol _ZNK4Aska10FileStream4TellEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK4Aska10FileStream4TellEv(long *param_1)

{
  ulong uVar1;
  
  uVar1 = (**(code **)(*param_1 + 0x10))();
  if ((uVar1 & 1) != 0) {
    (*(code *)PTR__ZN4Aska4File4SeekElNS0_6OriginE_02c927f8)(param_1 + 1,0,1);
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x020217c8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*param_1 + 0x48))(param_1,0xfffffffffffffc44);
  return;
}

// ==== Aska::FileStream::Read(void*, unsigned long, unsigned long)
// vaddr 0x1f217cc | ghidra 0x20217cc | size 980 | symbol _ZN4Aska10FileStream4ReadEPvmm | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZN4Aska10FileStream4ReadEPvmm(long *param_1,ulong param_2,ulong param_3,long param_4)

{
  uint uVar1;
  ulong uVar2;
  undefined1 uVar3;
  ushort uVar4;
  ulong uVar5;
  ulong uVar6;
  uint uVar7;
  ulong uVar8;
  ulong uVar9;
  uint uVar10;
  undefined1 *puVar11;
  undefined1 *puVar12;
  ulong uVar13;
  ushort *puVar14;
  undefined1 (*pauVar15) [16];
  undefined8 *puVar16;
  undefined8 uVar17;
  undefined1 auVar18 [16];
  undefined8 uVar19;
  undefined1 auVar20 [16];
  
  uVar5 = (**(code **)(*param_1 + 0x10))();
  if ((uVar5 & 1) == 0) {
    (**(code **)(*param_1 + 0x48))(param_1,0xfffffffffffffc44);
    return 0;
  }
  uVar5 = Aska::File::Read(void*, unsigned long, unsigned int*)(param_1 + 1,param_2,param_4 * param_3,0);
  if ((param_3 < 2) || ((char)param_1[5] == '\0')) goto code_r0x02021b70;
  uVar6 = 0;
  if (param_3 != 0) {
    uVar6 = uVar5 / param_3;
  }
  if ((param_3 - 1 & param_2) == 0) {
    if (param_3 == 8) {
      if (7 < uVar5) {
        uVar8 = uVar6;
        if (uVar6 < 2) {
          uVar8 = 1;
        }
        if ((uVar8 < 4) || (uVar13 = uVar8 & 0xfffffffffffffffc, uVar13 == 0)) {
          uVar9 = 0;
          uVar10 = 0;
        }
        else {
          uVar2 = uVar6;
          if (uVar6 < 2) {
            uVar2 = 1;
          }
          uVar10 = 0;
          uVar9 = 0;
          if (((int)(uVar2 - 1) != -1) && (uVar2 - 1 >> 0x20 == 0)) {
            uVar10 = (uint)uVar13;
            pauVar15 = (undefined1 (*) [16])(param_2 + 0x10);
            uVar9 = 0;
            do {
              uVar9 = uVar9 + 4;
              auVar18 = NEON_rev64(pauVar15[-1],1);
              auVar20 = NEON_rev64(*pauVar15,1);
              *(long *)(pauVar15[-1] + 8) = auVar18._8_8_;
              *(long *)pauVar15[-1] = auVar18._0_8_;
              *(long *)(*pauVar15 + 8) = auVar20._8_8_;
              *(long *)*pauVar15 = auVar20._0_8_;
              pauVar15 = pauVar15 + 2;
            } while (uVar9 != uVar13);
            uVar9 = uVar13;
            if (uVar8 == uVar13) goto code_r0x02021b70;
          }
        }
        do {
          uVar10 = uVar10 + 1;
          uVar8 = *(ulong *)(param_2 + uVar9 * 8);
          uVar8 = (uVar8 & 0xff00ff00ff00ff00) >> 8 | (uVar8 & 0xff00ff00ff00ff) << 8;
          uVar8 = (uVar8 & 0xffff0000ffff0000) >> 0x10 | (uVar8 & 0xffff0000ffff) << 0x10;
          *(ulong *)(param_2 + uVar9 * 8) = uVar8 >> 0x20 | uVar8 << 0x20;
          uVar9 = (ulong)uVar10;
        } while (uVar10 < uVar6);
      }
      goto code_r0x02021b70;
    }
    if (param_3 == 4) {
      if (3 < uVar5) {
        uVar8 = uVar6;
        if (uVar6 < 2) {
          uVar8 = 1;
        }
        if ((uVar8 < 4) || (uVar13 = uVar8 & 0xfffffffffffffffc, uVar13 == 0)) {
          uVar9 = 0;
          uVar10 = 0;
        }
        else {
          uVar2 = uVar6;
          if (uVar6 < 2) {
            uVar2 = 1;
          }
          uVar10 = 0;
          uVar9 = 0;
          if (((int)(uVar2 - 1) != -1) && (uVar2 - 1 >> 0x20 == 0)) {
            uVar10 = (uint)uVar13;
            puVar16 = (undefined8 *)(param_2 + 8);
            uVar9 = 0;
            do {
              uVar9 = uVar9 + 4;
              uVar17 = NEON_rev32(puVar16[-1],1);
              uVar19 = NEON_rev32(*puVar16,1);
              puVar16[-1] = uVar17;
              *puVar16 = uVar19;
              puVar16 = puVar16 + 2;
            } while (uVar9 != uVar13);
            uVar9 = uVar13;
            if (uVar8 == uVar13) goto code_r0x02021b70;
          }
        }
        do {
          uVar10 = uVar10 + 1;
          uVar1 = *(uint *)(param_2 + uVar9 * 4);
          uVar1 = (uVar1 & 0xff00ff00) >> 8 | (uVar1 & 0xff00ff) << 8;
          *(uint *)(param_2 + uVar9 * 4) = uVar1 >> 0x10 | uVar1 << 0x10;
          uVar9 = (ulong)uVar10;
        } while (uVar10 < uVar6);
      }
      goto code_r0x02021b70;
    }
    if (param_3 == 2) {
      if (1 < uVar5) {
        uVar8 = uVar6;
        if (uVar6 < 2) {
          uVar8 = 1;
        }
        if ((uVar8 < 4) || (uVar13 = uVar8 & 0xfffffffffffffffc, uVar13 == 0)) {
          uVar9 = 0;
          uVar10 = 0;
        }
        else {
          uVar2 = uVar6;
          if (uVar6 < 2) {
            uVar2 = 1;
          }
          uVar10 = 0;
          uVar9 = 0;
          if (((int)(uVar2 - 1) != -1) && (uVar2 - 1 >> 0x20 == 0)) {
            uVar10 = (uint)uVar13;
            puVar14 = (ushort *)(param_2 + 4);
            uVar9 = 0;
            do {
              uVar17 = NEON_rev32((ulong)CONCAT24(puVar14[-1],(uint)puVar14[-2]),1);
              uVar19 = NEON_rev32((ulong)CONCAT24(puVar14[1],(uint)*puVar14),1);
              puVar14[-2] = (ushort)((ulong)uVar17 >> 0x10);
              uVar9 = uVar9 + 4;
              *puVar14 = (ushort)((ulong)uVar19 >> 0x10);
              puVar14[-1] = (ushort)((ulong)uVar17 >> 0x30);
              puVar14[1] = (ushort)((ulong)uVar19 >> 0x30);
              puVar14 = puVar14 + 4;
            } while (uVar9 != uVar13);
            uVar9 = uVar13;
            if (uVar8 == uVar13) goto code_r0x02021b70;
          }
        }
        do {
          uVar10 = uVar10 + 1;
          uVar4 = *(ushort *)(param_2 + uVar9 * 2);
          *(ushort *)(param_2 + uVar9 * 2) = uVar4 >> 8 | uVar4 << 8;
          uVar9 = (ulong)uVar10;
        } while (uVar10 < uVar6);
      }
      goto code_r0x02021b70;
    }
  }
  if (param_3 <= uVar5) {
    if ((int)(param_3 >> 1) == 0) {
      uVar10 = (uint)uVar6;
      if (uVar6 < 2) {
        uVar10 = 1;
      }
      if ((uVar10 < 2) || (uVar1 = uVar10 & 0xfffffffe, uVar1 == 0)) {
        uVar7 = 0;
      }
      else {
        uVar8 = uVar6;
        if (uVar6 < 2) {
          uVar8 = 1;
        }
        uVar7 = 0;
        if (((int)(uVar8 - 1) != -1) && (uVar8 - 1 >> 0x20 == 0)) {
          uVar7 = 0;
          do {
            uVar7 = uVar7 + 2;
          } while (uVar7 != uVar1);
          uVar7 = uVar1;
          if (uVar10 == uVar1) goto code_r0x02021b70;
        }
      }
      do {
        uVar7 = uVar7 + 1;
      } while (uVar7 < uVar6);
    }
    else {
      uVar8 = 0;
      do {
        puVar11 = (undefined1 *)((param_2 - 1) + param_3 * (uVar8 + 1));
        puVar12 = (undefined1 *)(param_2 + param_3 * uVar8);
        uVar13 = param_3 >> 1 & 0xffffffff;
        do {
          uVar3 = *puVar12;
          uVar13 = uVar13 - 1;
          *puVar12 = *puVar11;
          *puVar11 = uVar3;
          puVar11 = puVar11 + -1;
          puVar12 = puVar12 + 1;
        } while (uVar13 != 0);
        uVar8 = (ulong)((int)uVar8 + 1);
      } while (uVar8 < uVar6);
    }
  }
code_r0x02021b70:
  if (uVar5 != param_4 * param_3) {
    (**(code **)(*param_1 + 0x48))(param_1,0xfffffffffffffc3f);
  }
  uVar6 = 0;
  if (param_3 != 0) {
    uVar6 = uVar5 / param_3;
  }
  return uVar6;
}

// ==== Aska::FileStream::Write(void const*, unsigned long, unsigned long)
// vaddr 0x1f21ba0 | ghidra 0x2021ba0 | size 1684 | symbol _ZN4Aska10FileStream5WriteEPKvmm | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZN4Aska10FileStream5WriteEPKvmm(long *param_1,ulong param_2,ulong param_3,ulong param_4)

{
  undefined1 uVar1;
  ushort uVar2;
  ulong uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  ushort *puVar8;
  undefined1 *puVar9;
  undefined8 *puVar10;
  undefined1 (*pauVar11) [16];
  undefined1 *puVar12;
  ulong uVar13;
  ulong uVar14;
  undefined8 uVar15;
  undefined1 auVar16 [16];
  undefined8 uVar17;
  undefined1 auVar18 [16];
  
  uVar3 = (**(code **)(*param_1 + 0x10))();
  if ((uVar3 & 1) == 0) {
    (**(code **)(*param_1 + 0x48))(param_1,0xfffffffffffffc44);
    return 0;
  }
  if ((param_3 < 2) || ((char)param_1[5] == '\0')) {
    uVar3 = Aska::File::Write(void const*, unsigned long)(param_1 + 1,param_2,param_4 * param_3);
    goto code_r0x02021c70;
  }
  uVar14 = param_3 - 1 & param_2;
  uVar6 = (uint)param_4;
  if (uVar14 == 0) {
    if (param_3 != 8) {
      if (param_3 == 4) {
        if (param_4 == 0) goto code_r0x02021e98;
        if ((param_4 < 4) || (uVar3 = param_4 & 0xfffffffffffffffc, uVar3 == 0)) {
          uVar13 = 0;
          uVar5 = 0;
        }
        else {
          uVar5 = 0;
          uVar13 = 0;
          if (((int)(param_4 - 1) != -1) && (param_4 - 1 >> 0x20 == 0)) {
            uVar5 = (uint)uVar3;
            puVar10 = (undefined8 *)(param_2 + 8);
            uVar13 = uVar3;
            do {
              uVar13 = uVar13 - 4;
              uVar15 = NEON_rev32(puVar10[-1],1);
              uVar17 = NEON_rev32(*puVar10,1);
              puVar10[-1] = uVar15;
              *puVar10 = uVar17;
              puVar10 = puVar10 + 2;
            } while (uVar13 != 0);
            uVar13 = uVar3;
            if (uVar3 == param_4) goto code_r0x02021f40;
          }
        }
        do {
          uVar5 = uVar5 + 1;
          uVar4 = *(uint *)(param_2 + uVar13 * 4);
          uVar4 = (uVar4 & 0xff00ff00) >> 8 | (uVar4 & 0xff00ff) << 8;
          *(uint *)(param_2 + uVar13 * 4) = uVar4 >> 0x10 | uVar4 << 0x10;
          uVar13 = (ulong)uVar5;
        } while (uVar5 < param_4);
      }
      else {
        if (param_3 != 2) goto code_r0x02021bec;
        if (param_4 == 0) goto code_r0x02021e98;
        if ((param_4 < 4) || (uVar3 = param_4 & 0xfffffffffffffffc, uVar3 == 0)) {
          uVar13 = 0;
          uVar5 = 0;
        }
        else {
          uVar5 = 0;
          uVar13 = 0;
          if (((int)(param_4 - 1) != -1) && (param_4 - 1 >> 0x20 == 0)) {
            uVar5 = (uint)uVar3;
            puVar8 = (ushort *)(param_2 + 4);
            uVar13 = uVar3;
            do {
              uVar15 = NEON_rev32((ulong)CONCAT24(puVar8[-1],(uint)puVar8[-2]),1);
              uVar17 = NEON_rev32((ulong)CONCAT24(puVar8[1],(uint)*puVar8),1);
              puVar8[-2] = (ushort)((ulong)uVar15 >> 0x10);
              *puVar8 = (ushort)((ulong)uVar17 >> 0x10);
              puVar8[-1] = (ushort)((ulong)uVar15 >> 0x30);
              uVar13 = uVar13 - 4;
              puVar8[1] = (ushort)((ulong)uVar17 >> 0x30);
              puVar8 = puVar8 + 4;
            } while (uVar13 != 0);
            uVar13 = uVar3;
            if (uVar3 == param_4) goto code_r0x02021f40;
          }
        }
        do {
          uVar5 = uVar5 + 1;
          uVar2 = *(ushort *)(param_2 + uVar13 * 2);
          *(ushort *)(param_2 + uVar13 * 2) = uVar2 >> 8 | uVar2 << 8;
          uVar13 = (ulong)uVar5;
        } while (uVar5 < param_4);
      }
      goto code_r0x02021f40;
    }
    if (param_4 != 0) {
      if ((param_4 < 4) || (uVar3 = param_4 & 0xfffffffffffffffc, uVar3 == 0)) {
        uVar13 = 0;
        uVar5 = 0;
      }
      else {
        uVar5 = 0;
        uVar13 = 0;
        if (((int)(param_4 - 1) != -1) && (param_4 - 1 >> 0x20 == 0)) {
          uVar5 = (uint)uVar3;
          pauVar11 = (undefined1 (*) [16])(param_2 + 0x10);
          uVar13 = uVar3;
          do {
            uVar13 = uVar13 - 4;
            auVar16 = NEON_rev64(pauVar11[-1],1);
            auVar18 = NEON_rev64(*pauVar11,1);
            *(long *)(pauVar11[-1] + 8) = auVar16._8_8_;
            *(long *)pauVar11[-1] = auVar16._0_8_;
            *(long *)(*pauVar11 + 8) = auVar18._8_8_;
            *(long *)*pauVar11 = auVar18._0_8_;
            pauVar11 = pauVar11 + 2;
          } while (uVar13 != 0);
          uVar13 = uVar3;
          if (uVar3 == param_4) goto code_r0x02021f40;
        }
      }
      do {
        uVar5 = uVar5 + 1;
        uVar3 = *(ulong *)(param_2 + uVar13 * 8);
        uVar3 = (uVar3 & 0xff00ff00ff00ff00) >> 8 | (uVar3 & 0xff00ff00ff00ff) << 8;
        uVar3 = (uVar3 & 0xffff0000ffff0000) >> 0x10 | (uVar3 & 0xffff0000ffff) << 0x10;
        *(ulong *)(param_2 + uVar13 * 8) = uVar3 >> 0x20 | uVar3 << 0x20;
        uVar13 = (ulong)uVar5;
      } while (uVar5 < param_4);
      goto code_r0x02021f40;
    }
code_r0x02021e98:
    uVar3 = Aska::File::Write(void const*, unsigned long)(param_1 + 1,param_2,param_4 * param_3);
code_r0x02021fac:
    switch(param_3 - 1) {
    case 0:
      break;
    case 1:
      if (param_4 != 0) {
        if ((param_4 < 4) || (uVar14 = param_4 & 0xfffffffffffffffc, uVar14 == 0)) {
          uVar6 = 0;
          uVar13 = 0;
        }
        else {
          uVar6 = 0;
          uVar13 = 0;
          if (((int)(param_4 - 1) != -1) && (param_4 - 1 >> 0x20 == 0)) {
            uVar6 = (uint)uVar14;
            puVar8 = (ushort *)(param_2 + 4);
            uVar13 = uVar14;
            do {
              uVar15 = NEON_rev32((ulong)CONCAT24(puVar8[-1],(uint)puVar8[-2]),1);
              uVar17 = NEON_rev32((ulong)CONCAT24(puVar8[1],(uint)*puVar8),1);
              puVar8[-2] = (ushort)((ulong)uVar15 >> 0x10);
              *puVar8 = (ushort)((ulong)uVar17 >> 0x10);
              puVar8[-1] = (ushort)((ulong)uVar15 >> 0x30);
              uVar13 = uVar13 - 4;
              puVar8[1] = (ushort)((ulong)uVar17 >> 0x30);
              puVar8 = puVar8 + 4;
            } while (uVar13 != 0);
            uVar13 = uVar14;
            if (uVar14 == param_4) break;
          }
        }
        do {
          uVar6 = uVar6 + 1;
          uVar2 = *(ushort *)(param_2 + uVar13 * 2);
          *(ushort *)(param_2 + uVar13 * 2) = uVar2 >> 8 | uVar2 << 8;
          uVar13 = (ulong)uVar6;
        } while (uVar6 < param_4);
      }
      break;
    default:
      goto code_r0x02021f58;
    case 3:
      if (param_4 != 0) {
        if ((param_4 < 4) || (uVar14 = param_4 & 0xfffffffffffffffc, uVar14 == 0)) {
          uVar6 = 0;
          uVar13 = 0;
        }
        else {
          uVar6 = 0;
          uVar13 = 0;
          if (((int)(param_4 - 1) != -1) && (param_4 - 1 >> 0x20 == 0)) {
            uVar6 = (uint)uVar14;
            puVar10 = (undefined8 *)(param_2 + 8);
            uVar13 = uVar14;
            do {
              uVar13 = uVar13 - 4;
              uVar15 = NEON_rev32(puVar10[-1],1);
              uVar17 = NEON_rev32(*puVar10,1);
              puVar10[-1] = uVar15;
              *puVar10 = uVar17;
              puVar10 = puVar10 + 2;
            } while (uVar13 != 0);
            uVar13 = uVar14;
            if (uVar14 == param_4) break;
          }
        }
        do {
          uVar6 = uVar6 + 1;
          uVar5 = *(uint *)(param_2 + uVar13 * 4);
          uVar5 = (uVar5 & 0xff00ff00) >> 8 | (uVar5 & 0xff00ff) << 8;
          *(uint *)(param_2 + uVar13 * 4) = uVar5 >> 0x10 | uVar5 << 0x10;
          uVar13 = (ulong)uVar6;
        } while (uVar6 < param_4);
      }
      break;
    case 7:
      if (param_4 != 0) {
        if ((param_4 < 4) || (uVar14 = param_4 & 0xfffffffffffffffc, uVar14 == 0)) {
          uVar6 = 0;
          uVar13 = 0;
        }
        else {
          uVar6 = 0;
          uVar13 = 0;
          if (((int)(param_4 - 1) != -1) && (param_4 - 1 >> 0x20 == 0)) {
            uVar6 = (uint)uVar14;
            pauVar11 = (undefined1 (*) [16])(param_2 + 0x10);
            uVar13 = uVar14;
            do {
              uVar13 = uVar13 - 4;
              auVar16 = NEON_rev64(pauVar11[-1],1);
              auVar18 = NEON_rev64(*pauVar11,1);
              *(long *)(pauVar11[-1] + 8) = auVar16._8_8_;
              *(long *)pauVar11[-1] = auVar16._0_8_;
              *(long *)(*pauVar11 + 8) = auVar18._8_8_;
              *(long *)*pauVar11 = auVar18._0_8_;
              pauVar11 = pauVar11 + 2;
            } while (uVar13 != 0);
            uVar13 = uVar14;
            if (uVar14 == param_4) break;
          }
        }
        do {
          uVar6 = uVar6 + 1;
          uVar14 = *(ulong *)(param_2 + uVar13 * 8);
          uVar14 = (uVar14 & 0xff00ff00ff00ff00) >> 8 | (uVar14 & 0xff00ff00ff00ff) << 8;
          uVar14 = (uVar14 & 0xffff0000ffff0000) >> 0x10 | (uVar14 & 0xffff0000ffff) << 0x10;
          *(ulong *)(param_2 + uVar13 * 8) = uVar14 >> 0x20 | uVar14 << 0x20;
          uVar13 = (ulong)uVar6;
        } while (uVar6 < param_4);
      }
    }
  }
  else {
code_r0x02021bec:
    if (param_4 != 0) {
      if ((int)(param_3 >> 1) == 0) {
        if ((uVar6 < 2) || (uVar5 = uVar6 & 0xfffffffe, (param_4 & 0xfffffffe) == 0)) {
          uVar4 = 0;
        }
        else {
          uVar4 = 0;
          if (((int)(param_4 - 1) != -1) && (uVar7 = uVar5, param_4 - 1 >> 0x20 == 0)) {
            do {
              uVar7 = uVar7 - 2;
            } while (uVar7 != 0);
            uVar4 = uVar5;
            if (uVar5 == uVar6) goto code_r0x02021f40;
          }
        }
        do {
          uVar4 = uVar4 + 1;
        } while (uVar4 < param_4);
      }
      else {
        uVar3 = 0;
        do {
          puVar9 = (undefined1 *)((param_2 - 1) + param_3 * (uVar3 + 1));
          puVar12 = (undefined1 *)(param_2 + param_3 * uVar3);
          uVar13 = param_3 >> 1 & 0xffffffff;
          do {
            uVar1 = *puVar12;
            uVar13 = uVar13 - 1;
            *puVar12 = *puVar9;
            *puVar9 = uVar1;
            puVar9 = puVar9 + -1;
            puVar12 = puVar12 + 1;
          } while (uVar13 != 0);
          uVar3 = (ulong)((int)uVar3 + 1);
        } while (uVar3 < param_4);
      }
    }
code_r0x02021f40:
    uVar3 = Aska::File::Write(void const*, unsigned long)(param_1 + 1,param_2,param_4 * param_3);
    if (uVar14 == 0) goto code_r0x02021fac;
code_r0x02021f58:
    if (param_4 != 0) {
      if ((int)(param_3 >> 1) == 0) {
        if ((uVar6 < 2) || (uVar5 = uVar6 & 0xfffffffe, (param_4 & 0xfffffffe) == 0)) {
          uVar4 = 0;
        }
        else {
          uVar4 = 0;
          if (((int)(param_4 - 1) != -1) && (uVar7 = uVar5, param_4 - 1 >> 0x20 == 0)) {
            do {
              uVar7 = uVar7 - 2;
            } while (uVar7 != 0);
            uVar4 = uVar5;
            if (uVar5 == uVar6) goto code_r0x02021c70;
          }
        }
        do {
          uVar4 = uVar4 + 1;
        } while (uVar4 < param_4);
      }
      else {
        uVar14 = 0;
        do {
          puVar9 = (undefined1 *)((param_2 - 1) + param_3 * (uVar14 + 1));
          puVar12 = (undefined1 *)(param_2 + param_3 * uVar14);
          uVar13 = param_3 >> 1 & 0xffffffff;
          do {
            uVar1 = *puVar12;
            uVar13 = uVar13 - 1;
            *puVar12 = *puVar9;
            *puVar9 = uVar1;
            puVar9 = puVar9 + -1;
            puVar12 = puVar12 + 1;
          } while (uVar13 != 0);
          uVar14 = (ulong)((int)uVar14 + 1);
        } while (uVar14 < param_4);
      }
    }
  }
code_r0x02021c70:
  if (uVar3 != param_4 * param_3) {
    (**(code **)(*param_1 + 0x48))(param_1,0xfffffffffffffc3f);
  }
  uVar14 = 0;
  if (param_3 != 0) {
    uVar14 = uVar3 / param_3;
  }
  return uVar14;
}

// ==== Aska::FileStream::Flush()
// vaddr 0x1f22234 | ghidra 0x2022234 | size 68 | symbol _ZN4Aska10FileStream5FlushEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska10FileStream5FlushEv(long *param_1)

{
  ulong uVar1;
  undefined8 uVar2;
  
  uVar1 = (**(code **)(*param_1 + 0x10))();
  if ((uVar1 & 1) != 0) {
    Aska::File::Flush()(param_1 + 1);
    return 0;
  }
                    /* WARNING: Could not recover jumptable at 0x02022274. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  uVar2 = (**(code **)(*param_1 + 0x48))(param_1,0xfffffffffffffc44);
  return uVar2;
}

// ==== Aska::FileStream::IsEnd(long*) const
// vaddr 0x1f22278 | ghidra 0x2022278 | size 128 | symbol _ZNK4Aska10FileStream5IsEndEPl | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK4Aska10FileStream5IsEndEPl(long *param_1,undefined8 *param_2)

{
  bool bVar1;
  ulong uVar2;
  ulong uVar3;
  undefined8 uVar4;
  
  uVar2 = (**(code **)(*param_1 + 0x10))();
  if ((uVar2 & 1) == 0) {
    if (param_2 != (undefined8 *)0x0) {
      uVar4 = (**(code **)(*param_1 + 0x48))(param_1,0xfffffffffffffc44);
      *param_2 = uVar4;
    }
    bVar1 = true;
  }
  else {
    if (param_2 != (undefined8 *)0x0) {
      *param_2 = 0;
    }
    uVar2 = Aska::File::Seek(long, Aska::File::Origin)(param_1 + 1,0,1);
    uVar3 = Aska::File::GetFileSizeL() const(param_1 + 1);
    bVar1 = uVar3 <= uVar2;
  }
  return bVar1;
}

// ==== Aska::FileStream::GetTotalSize() const
// vaddr 0x1f222f8 | ghidra 0x20222f8 | size 100 | symbol _ZNK4Aska10FileStream12GetTotalSizeEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK4Aska10FileStream12GetTotalSizeEv(long *param_1)

{
  ulong uVar1;
  long lVar2;
  
  uVar1 = (**(code **)(*param_1 + 0x10))();
  if ((uVar1 & 1) == 0) {
                    /* WARNING: Could not recover jumptable at 0x02022340. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    lVar2 = (**(code **)(*param_1 + 0x48))(param_1,0xfffffffffffffc44);
    return lVar2;
  }
  lVar2 = Aska::File::GetFileSize() const(param_1 + 1);
  if (-1 < lVar2) {
    return lVar2;
  }
                    /* WARNING: Could not recover jumptable at 0x02022358. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  lVar2 = (**(code **)(*param_1 + 0x48))(param_1,lVar2);
  return lVar2;
}

// ==== Aska::FileStream::~FileStream()
// vaddr 0x1f2235c | ghidra 0x202235c | size 116 | symbol _ZN4Aska10FileStreamD2Ev | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Possible PIC construction at 0x02022388: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0x0202238c) */
/* WARNING: Removing unreachable block (ram,0x020223a4) */

void _ZN4Aska10FileStreamD2Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska10FileStreamE_02cbc9f8 + 0x10);
  if (param_1[3] != 0) {
    (*(code *)PTR__ZN4Aska4File5CloseEv_02c8e880)(param_1 + 1);
    return;
  }
  param_1[1] = (long)(PTR__ZTVN4Aska4FileE_02cb6e28 + 0x10);
  return;
}

// ==== Aska::FileStream::~FileStream()
// vaddr 0x1f223d0 | ghidra 0x20223d0 | size 96 | symbol _ZN4Aska10FileStreamD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10FileStreamD0Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska10FileStreamE_02cbc9f8 + 0x10);
  if (param_1[3] != 0) {
    Aska::File::Close()(param_1 + 1);
    param_1[1] = (long)(PTR__ZTVN4Aska4FileE_02cb6e28 + 0x10);
    if (param_1[3] != 0) {
      Aska::File::Close()(param_1 + 1);
    }
  }
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::FileStream::IsReady() const
// vaddr 0x1f22430 | ghidra 0x2022430 | size 16 | symbol _ZNK4Aska10FileStream7IsReadyEv | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK4Aska10FileStream7IsReadyEv(long param_1)

{
  return *(long *)(param_1 + 0x18) != 0;
}

// ==== Aska::FileStream::SetLastError(long) const
// vaddr 0x1f22440 | ghidra 0x2022440 | size 12 | symbol _ZNK4Aska10FileStream12SetLastErrorEl | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska10FileStream12SetLastErrorEl(long param_1,undefined8 param_2)

{
  *(undefined8 *)(param_1 + 0x20) = param_2;
  return param_2;
}

// ==== Aska::FileStream::GetLastError() const
// vaddr 0x1f2244c | ghidra 0x202244c | size 8 | symbol _ZNK4Aska10FileStream12GetLastErrorEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska10FileStream12GetLastErrorEv(long param_1)

{
  return *(undefined8 *)(param_1 + 0x20);
}

// ==== Aska::IStream::PrintV(Aska::IStream*, char const*, std::__va_list)
// vaddr 0x1f229f8 | ghidra 0x20229f8 | size 184 | symbol _ZN4Aska7IStream6PrintVEPS0_PKcSt9__va_list | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZN4Aska7IStream6PrintVEPS0_PKcSt9__va_list
                (long *param_1,undefined8 param_2,undefined8 *param_3)

{
  int iVar1;
  ulong uVar2;
  ulong uVar3;
  undefined1 auStack_440 [1024];
  undefined8 uStack_40;
  undefined8 uStack_38;
  undefined8 uStack_30;
  undefined8 uStack_28;
  
  uStack_28 = param_3[3];
  uStack_30 = param_3[2];
  uStack_38 = param_3[1];
  uStack_40 = *param_3;
  iVar1 = vsnprintf(auStack_440,0x3ff,param_2,&uStack_40);
  if (iVar1 < 0x400) {
    if (iVar1 < 1) {
      uVar2 = (ulong)iVar1;
    }
    else {
      uVar2 = (ulong)iVar1;
      uVar3 = (**(code **)(*param_1 + 0x30))(param_1,auStack_440,1,uVar2);
      if (uVar3 < uVar2) {
        uVar2 = (**(code **)(*param_1 + 0x58))(param_1);
      }
    }
  }
  else {
    uVar2 = (**(code **)(*param_1 + 0x48))(param_1,0xffffffffffffffff);
  }
  return uVar2;
}

// ==== Aska::IStream::Align(Aska::IStream*, int, unsigned long, long)
// vaddr 0x1f22ab0 | ghidra 0x2022ab0 | size 388 | symbol _ZN4Aska7IStream5AlignEPS0_iml | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZN4Aska7IStream5AlignEPS0_iml(long *param_1,undefined4 param_2,ulong param_3,long param_4)

{
  ulong uVar1;
  ulong uVar2;
  ulong uVar3;
  long lVar4;
  undefined1 auStack_c0 [128];
  
  uVar1 = (**(code **)(*param_1 + 0x18))();
  if ((long)uVar1 < 0) {
    return uVar1;
  }
  if (param_3 == 0) {
    return 0;
  }
  uVar1 = uVar1 + param_4;
  if ((long)uVar1 < 0) {
    uVar3 = 0;
    if (param_3 != 0) {
      uVar3 = -uVar1 / param_3;
    }
    param_3 = -uVar1 - uVar3 * param_3;
    if (param_3 == 0) {
      return 0;
    }
    uVar1 = param_3;
    if (0x7f < param_3) {
      uVar1 = 0x80;
    }
    memset(auStack_c0,param_2,uVar1);
    uVar1 = param_3;
    do {
      uVar3 = uVar1;
      if (0x7f < uVar1) {
        uVar3 = 0x80;
      }
      uVar2 = (**(code **)(*param_1 + 0x30))(param_1,auStack_c0,1,uVar3);
      if (uVar2 != uVar3) {
        uVar3 = (**(code **)(*param_1 + 0x58))(param_1);
        lVar4 = param_3 - uVar1;
        goto code_r0x02022c10;
      }
      uVar1 = uVar1 - uVar3;
      uVar2 = param_3;
    } while (uVar1 != 0);
  }
  else {
    uVar3 = 0;
    if (param_3 != 0) {
      uVar3 = uVar1 / param_3;
    }
    lVar4 = uVar1 - uVar3 * param_3;
    if (lVar4 == 0) {
      return 0;
    }
    param_3 = param_3 - lVar4;
    uVar1 = param_3;
    if (0x7f < param_3) {
      uVar1 = 0x80;
    }
    memset(auStack_c0,param_2,uVar1);
    uVar1 = param_3;
    if (param_3 == 0) {
      uVar3 = 0;
      uVar2 = 0;
      goto code_r0x02022c14;
    }
    do {
      uVar3 = uVar1;
      if (0x7f < uVar1) {
        uVar3 = 0x80;
      }
      uVar2 = (**(code **)(*param_1 + 0x30))(param_1,auStack_c0,1,uVar3);
      if (uVar2 != uVar3) {
        uVar3 = (**(code **)(*param_1 + 0x58))(param_1);
        lVar4 = param_3 - uVar1;
code_r0x02022c10:
        uVar2 = lVar4 + uVar2;
        goto code_r0x02022c14;
      }
      uVar1 = uVar1 - uVar3;
      uVar2 = param_3;
    } while (uVar1 != 0);
  }
  uVar3 = 0;
  param_3 = uVar2;
code_r0x02022c14:
  if (uVar2 != param_3) {
    return uVar3;
  }
  return param_3;
}

// ==== Aska::IStream::Fill(Aska::IStream*, int, unsigned long, long*)
// vaddr 0x1f22c34 | ghidra 0x2022c34 | size 192 | symbol _ZN4Aska7IStream4FillEPS0_imPl | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZN4Aska7IStream4FillEPS0_imPl
                (long *param_1,undefined8 param_2,ulong param_3,undefined8 *param_4)

{
  ulong uVar1;
  ulong uVar2;
  undefined8 uVar3;
  ulong uVar4;
  undefined1 auStack_c0 [128];
  
  uVar4 = param_3;
  if (0x7f < param_3) {
    uVar4 = 0x80;
  }
  memset(auStack_c0,param_2,uVar4);
  uVar4 = param_3;
  while( true ) {
    if (uVar4 == 0) {
      if (param_4 != (undefined8 *)0x0) {
        *param_4 = 0;
      }
      return param_3;
    }
    uVar1 = uVar4;
    if (0x7f < uVar4) {
      uVar1 = 0x80;
    }
    uVar2 = (**(code **)(*param_1 + 0x30))(param_1,auStack_c0,1,uVar1);
    if (uVar2 != uVar1) break;
    uVar4 = uVar4 - uVar1;
  }
  uVar3 = (**(code **)(*param_1 + 0x58))(param_1);
  if (param_4 != (undefined8 *)0x0) {
    *param_4 = uVar3;
  }
  return (param_3 - uVar4) + uVar2;
}

// ==== Aska::IStream::SeekAlign(Aska::IStream*, unsigned long, long)
// vaddr 0x1f22cf4 | ghidra 0x2022cf4 | size 96 | symbol _ZN4Aska7IStream9SeekAlignEPS0_ml | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska7IStream9SeekAlignEPS0_ml(long *param_1,ulong param_2,long param_3)

{
  ulong uVar1;
  long lVar2;
  
  lVar2 = (**(code **)(*param_1 + 0x18))();
  if (-1 < lVar2) {
    uVar1 = 0;
    if (param_2 != 0) {
      uVar1 = (ulong)(lVar2 + param_3) / param_2;
    }
    lVar2 = (lVar2 + param_3) - uVar1 * param_2;
    if (lVar2 != 0) {
                    /* WARNING: Could not recover jumptable at 0x02022d44. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (**(code **)(*param_1 + 0x20))(param_1,param_2 - lVar2,1);
      return;
    }
  }
  return;
}

// ==== Aska::IStream::Transfer(Aska::IStream*, Aska::IStream*, unsigned long, long*)
// vaddr 0x1f22d54 | ghidra 0x2022d54 | size 52 | symbol _ZN4Aska7IStream8TransferEPS0_S1_mPl | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska7IStream8TransferEPS0_S1_mPl
               (undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  undefined1 auStack_1010 [4096];
  
  Aska::IStream::Transfer(Aska::IStream*, Aska::IStream*, unsigned long, unsigned long, void*, unsigned long, long*)(param_1,param_2,1,param_3,auStack_1010,0x1000,param_4);
  return;
}

// ==== Aska::IStream::Transfer(Aska::IStream*, Aska::IStream*, unsigned long, void*, unsigned long, long*)
// vaddr 0x1f22d88 | ghidra 0x2022d88 | size 40 | symbol _ZN4Aska7IStream8TransferEPS0_S1_mPvmPl | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska7IStream8TransferEPS0_S1_mPvmPl
               (undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               undefined8 param_5,undefined8 param_6)

{
  (*(code *)PTR__ZN4Aska7IStream8TransferEPS0_S1_mmPvmPl_02c9a728)
            (param_1,param_2,1,param_3,param_4,param_5,param_6);
  return;
}

// ==== Aska::IStream::Transfer(Aska::IStream*, Aska::IStream*, unsigned long, unsigned long, void*, unsigned long, long*)
// vaddr 0x1f22db0 | ghidra 0x2022db0 | size 640 | symbol _ZN4Aska7IStream8TransferEPS0_S1_mmPvmPl | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZN4Aska7IStream8TransferEPS0_S1_mmPvmPl
                (long *param_1,long *param_2,ulong param_3,ulong param_4,undefined8 param_5,
                ulong param_6,long *param_7)

{
  ulong uVar1;
  bool bVar2;
  ulong uVar3;
  ulong uVar4;
  long lVar5;
  ulong uVar6;
  long lVar7;
  
  if (param_7 != (long *)0x0) {
    *param_7 = 0;
  }
  if (param_4 != 0) {
    uVar1 = 0;
    if (param_3 != 0) {
      uVar1 = param_6 / param_3;
    }
    lVar7 = -param_4;
    uVar6 = param_4;
    if (param_4 == 0xffffffffffffffff) {
      uVar6 = 0xffffffffffffffff;
      do {
        uVar4 = uVar6;
        if (uVar1 <= uVar6) {
          uVar4 = uVar1;
        }
        uVar3 = (**(code **)(*param_1 + 0x28))(param_1,param_5,param_3,uVar4);
        if (uVar3 == uVar4) {
          bVar2 = false;
          uVar3 = uVar4;
        }
        else {
          lVar5 = (**(code **)(*param_1 + 0x58))(param_1);
          if (lVar5 != -0x3c1) goto joined_r0x02022fd4;
          if (uVar3 == 0) goto code_r0x02023008;
          bVar2 = true;
        }
        uVar4 = (**(code **)(*param_2 + 0x30))(param_2,param_5,param_3,uVar3);
        if (uVar4 != uVar3) goto code_r0x02022f48;
        if (bVar2) goto code_r0x02022f88;
        uVar6 = uVar6 - uVar3;
        lVar7 = -uVar6;
      } while (uVar6 != 0);
      param_4 = 0xffffffffffffffff;
    }
    else {
      do {
        uVar4 = uVar6;
        if (uVar1 <= uVar6) {
          uVar4 = uVar1;
        }
        uVar3 = (**(code **)(*param_1 + 0x28))(param_1,param_5,param_3,uVar4);
        if (uVar3 == uVar4) {
          bVar2 = false;
          uVar3 = uVar4;
        }
        else {
          lVar5 = (**(code **)(*param_1 + 0x58))(param_1);
          if (lVar5 != -0x3c1) goto joined_r0x02022fd4;
          if (1 < param_4 + 1) {
            if (param_7 != (long *)0x0) {
              *param_7 = -0x3c1;
            }
            goto code_r0x02023008;
          }
          if (uVar3 == 0) goto code_r0x02023008;
          bVar2 = true;
        }
        uVar4 = (**(code **)(*param_2 + 0x30))(param_2,param_5,param_3,uVar3);
        if (uVar4 != uVar3) {
code_r0x02022f48:
          lVar5 = (**(code **)(*param_2 + 0x58))(param_2);
          if (lVar5 == -0x3c7) {
            (**(code **)(*param_2 + 0x48))(param_2,0xffffffffffffffff);
            if (param_7 != (long *)0x0) {
              *param_7 = -1;
            }
          }
          else if (param_7 != (long *)0x0) {
            *param_7 = lVar5;
          }
          return lVar7 + param_4 + uVar4;
        }
        if (bVar2) {
code_r0x02022f88:
          return lVar7 + param_4 + uVar3;
        }
        uVar6 = uVar6 - uVar3;
        lVar7 = -uVar6;
      } while (uVar6 != 0);
    }
  }
  return param_4;
joined_r0x02022fd4:
  if (lVar5 == -0x3c7) {
    (**(code **)(*param_1 + 0x48))(param_1,0xffffffffffffffff);
    if (param_7 != (long *)0x0) {
      *param_7 = -1;
    }
  }
  else if (param_7 != (long *)0x0) {
    *param_7 = lVar5;
  }
code_r0x02023008:
  return param_4 - uVar6;
}

// ==== Aska::IStream::Transfer(Aska::IStream*, Aska::IStream*, unsigned long, unsigned long, long*)
// vaddr 0x1f23030 | ghidra 0x2023030 | size 40 | symbol _ZN4Aska7IStream8TransferEPS0_S1_mmPl | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska7IStream8TransferEPS0_S1_mmPl(void)

{
  Aska::IStream::Transfer(Aska::IStream*, Aska::IStream*, unsigned long, unsigned long, void*, unsigned long, long*)();
  return;
}

// ==== Aska::IStream::Compare(Aska::IStream*, Aska::IStream*, unsigned long, long*)
// vaddr 0x1f23058 | ghidra 0x2023058 | size 40 | symbol _ZN4Aska7IStream7CompareEPS0_S1_mPl | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska7IStream7CompareEPS0_S1_mPl(void)

{
  Aska::IStream::Compare(Aska::IStream*, Aska::IStream*, unsigned long, void*, unsigned long, long*)();
  return;
}

// ==== Aska::IStream::Compare(Aska::IStream*, Aska::IStream*, unsigned long, void*, unsigned long, long*)
// vaddr 0x1f23080 | ghidra 0x2023080 | size 400 | symbol _ZN4Aska7IStream7CompareEPS0_S1_mPvmPl | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska7IStream7CompareEPS0_S1_mPvmPl
               (long *param_1,long *param_2,ulong param_3,long param_4,ulong param_5,long *param_6)

{
  int iVar1;
  ulong uVar2;
  long lVar3;
  ulong uVar4;
  ulong uVar5;
  
  if (param_6 != (long *)0x0) {
    *param_6 = 0;
  }
  if (param_3 == 0) {
    return 0;
  }
  param_5 = param_5 >> 1;
  if (param_5 <= param_3) {
    param_3 = param_5;
  }
  uVar2 = (**(code **)(*param_1 + 0x28))(param_1,param_4,1,param_3);
  if (uVar2 == param_3) {
code_r0x02023110:
    uVar4 = (**(code **)(*param_2 + 0x28))(param_2,param_4 + param_5,1,param_3);
    if (uVar4 != param_3) {
      lVar3 = (**(code **)(*param_2 + 0x58))(param_2);
      uVar5 = (**(code **)(*param_2 + 0x40))(param_2,0);
      if ((uVar5 & 1) == 0) {
        if (lVar3 != -0x3c7) {
          if (param_6 == (long *)0x0) {
            return 0;
          }
          *param_6 = lVar3;
          return 0;
        }
        lVar3 = *param_2;
        param_1 = param_2;
        goto code_r0x020231b8;
      }
    }
    if (uVar2 - uVar4 != 0) {
      return uVar2 - uVar4;
    }
    if (uVar2 != 0) {
      iVar1 = memcmp(param_4,param_4 + param_5,uVar2);
      return (long)iVar1;
    }
  }
  else {
    lVar3 = (**(code **)(*param_1 + 0x58))(param_1);
    uVar4 = (**(code **)(*param_1 + 0x40))(param_1,0);
    if ((uVar4 & 1) != 0) goto code_r0x02023110;
    if (lVar3 != -0x3c7) {
      if (param_6 == (long *)0x0) {
        return 0;
      }
      *param_6 = lVar3;
      return 0;
    }
    lVar3 = *param_1;
code_r0x020231b8:
    (**(code **)(lVar3 + 0x48))(param_1,0xffffffffffffffff);
    if (param_6 != (long *)0x0) {
      *param_6 = -1;
      return 0;
    }
  }
  return 0;
}

// ==== Aska::IStream::CalcSeekPt(long, long, long, long, int, long*)
// vaddr 0x1f23210 | ghidra 0x2023210 | size 148 | symbol _ZN4Aska7IStream10CalcSeekPtElllliPl | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska7IStream10CalcSeekPtElllliPl
               (long param_1,long param_2,long param_3,long param_4,int param_5,undefined8 *param_6)

{
  if (param_5 != 0) {
    if (param_5 == 2) {
      param_4 = param_4 + param_3;
    }
    else {
      if (param_5 != 1) {
        if (param_6 == (undefined8 *)0x0) {
          return -0x3bd;
        }
        *param_6 = 0xfffffffffffffc43;
        return -0x3bd;
      }
      param_4 = param_4 + param_1;
    }
  }
  if (param_4 < param_2) {
    param_4 = param_2;
    if (param_6 != (undefined8 *)0x0) {
      *param_6 = 0xfffffffffffffc3f;
      return param_2;
    }
  }
  else {
    if (param_3 < param_4) {
      if (param_6 == (undefined8 *)0x0) {
        return param_3;
      }
      *param_6 = 0xfffffffffffffc3f;
      return param_3;
    }
    if (param_6 != (undefined8 *)0x0) {
      *param_6 = 0;
    }
  }
  return param_4;
}

// ==== Aska::MultiMediaStream::IsReady() const
// vaddr 0x1f74dc4 | ghidra 0x2074dc4 | size 16 | symbol _ZNK4Aska16MultiMediaStream7IsReadyEv | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK4Aska16MultiMediaStream7IsReadyEv(long param_1)

{
  return *(long *)(param_1 + 0x40) != 0;
}

// ==== Aska::MultiMediaStream::IsBufferingReady() const
// vaddr 0x1f74dd4 | ghidra 0x2074dd4 | size 28 | symbol _ZNK4Aska16MultiMediaStream16IsBufferingReadyEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska16MultiMediaStream16IsBufferingReadyEv(long *param_1)

{
  undefined8 uVar1;
  
  if (*(char *)((long)param_1 + 0x8e) != '\0') {
                    /* WARNING: Could not recover jumptable at 0x02074de4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = (**(code **)(*param_1 + 0x10))();
    return uVar1;
  }
  return 0;
}

// ==== Aska::TPoolAtomicDynamic<Aska::DiscReadStream::ReadAsyncNotify>::~TPoolAtomicDynamic()
// vaddr 0x1f74df8 | ghidra 0x2074df8 | size 200 | symbol _ZN4Aska18TPoolAtomicDynamicINS_14DiscReadStream15ReadAsyncNotifyEED2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18TPoolAtomicDynamicINS_14DiscReadStream15ReadAsyncNotifyEED2Ev(long *param_1)

{
  long lVar1;
  long lVar2;
  
  *param_1 = (long)(
                   PTR__ZTVN4Aska18TPoolAtomicDynamicINS_14DiscReadStream15ReadAsyncNotifyEEE_02cc1350
                   + 0x10);
  if ((*(char *)((long)param_1 + 0x21) == '\0') || ((char)param_1[4] == '\0'))
  goto code_r0x02074ea0;
  if (param_1[2] != 0) {
    operator delete[](void*)();
    param_1[2] = 0;
  }
  if ((long *)param_1[1] == (long *)0x0) goto code_r0x02074ea0;
  if (*(int *)((long)param_1 + 0x24) < 1) {
code_r0x02074e98:
    operator delete[](void*)();
  }
  else {
    (**(code **)(*(long *)param_1[1] + 8))();
    if (1 < *(int *)((long)param_1 + 0x24)) {
      lVar1 = 1;
      lVar2 = 0x50;
      do {
        (**(code **)(*(long *)(param_1[1] + lVar2) + 8))();
        lVar1 = lVar1 + 1;
        lVar2 = lVar2 + 0x50;
      } while (lVar1 < *(int *)((long)param_1 + 0x24));
    }
    if (param_1[1] != 0) goto code_r0x02074e98;
  }
  param_1[1] = 0;
code_r0x02074ea0:
  *(undefined4 *)((long)param_1 + 0x24) = 0;
  *(undefined4 *)((long)param_1 + 0x1c) = 0;
  *(undefined4 *)(param_1 + 3) = 0;
  *(undefined2 *)(param_1 + 4) = 0;
  *(undefined4 *)(param_1 + 3) = 0;
  return;
}

// ==== Aska::TPoolAtomicDynamic<Aska::DiscReadStream::ReadAsyncNotify>::~TPoolAtomicDynamic()
// vaddr 0x1f74ec0 | ghidra 0x2074ec0 | size 24 | symbol _ZN4Aska18TPoolAtomicDynamicINS_14DiscReadStream15ReadAsyncNotifyEED0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18TPoolAtomicDynamicINS_14DiscReadStream15ReadAsyncNotifyEED0Ev(undefined8 param_1)

{
  Aska::TPoolAtomicDynamic<Aska::DiscReadStream::ReadAsyncNotify>::~TPoolAtomicDynamic()();
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::TPoolAtomic<Aska::StreamingStream::BufferingNotify, 9>::~TPoolAtomic()
// vaddr 0x1f74ed8 | ghidra 0x2074ed8 | size 28 | symbol _ZN4Aska11TPoolAtomicINS_15StreamingStream15BufferingNotifyELi9EED2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11TPoolAtomicINS_15StreamingStream15BufferingNotifyELi9EED2Ev(long *param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZTVN4Aska11TPoolAtomicINS_15StreamingStream15BufferingNotifyELi9EEE_02cc33b0;
  *(undefined1 *)(param_1 + 0x27) = 0;
  *param_1 = (long)(puVar1 + 0x10);
  *(undefined4 *)(param_1 + 0x26) = 0;
  return;
}

// ==== Aska::TPoolAtomic<Aska::StreamingStream::BufferingNotify, 9>::~TPoolAtomic()
// vaddr 0x1f74ef4 | ghidra 0x2074ef4 | size 28 | symbol _ZN4Aska11TPoolAtomicINS_15StreamingStream15BufferingNotifyELi9EED0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11TPoolAtomicINS_15StreamingStream15BufferingNotifyELi9EED0Ev(long *param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZTVN4Aska11TPoolAtomicINS_15StreamingStream15BufferingNotifyELi9EEE_02cc33b0;
  *(undefined1 *)(param_1 + 0x27) = 0;
  *param_1 = (long)(puVar1 + 0x10);
  *(undefined4 *)(param_1 + 0x26) = 0;
  (*(code *)PTR__ZdlPv_02ca4758)();
  return;
}

// ==== Aska::StreamingStream::WorkerThread::~WorkerThread()
// vaddr 0x1f74f10 | ghidra 0x2074f10 | size 104 | symbol _ZN4Aska15StreamingStream12WorkerThreadD2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska15StreamingStream12WorkerThreadD2Ev(long *param_1)

{
  ulong uVar1;
  
  *param_1 = (long)(PTR__ZTVN4Aska15StreamingStream12WorkerThreadE_02cc3220 + 0x10);
  while (uVar1 = Aska::Event::IsSignal() const(param_1 + 3), (uVar1 & 1) != 0) {
    Aska::Thread::SleepU(unsigned int)(100);
  }
  Aska::StreamingStream::WorkerThread::Term()(param_1);
  *param_1 = (long)(PTR__ZTVN4Aska17TWorkerThreadBaseINS_15StreamingStream12WorkerThreadEEE_02cb8f08
                   + 0x10);
  Aska::Event::Exit()(param_1 + 3);
  (*(code *)PTR__ZN4Aska6ThreadD1Ev_02c9be08)(param_1);
  return;
}

// ==== Aska::StreamingStream::WorkerThread::~WorkerThread()
// vaddr 0x1f74f78 | ghidra 0x2074f78 | size 112 | symbol _ZN4Aska15StreamingStream12WorkerThreadD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska15StreamingStream12WorkerThreadD0Ev(long *param_1)

{
  ulong uVar1;
  
  *param_1 = (long)(PTR__ZTVN4Aska15StreamingStream12WorkerThreadE_02cc3220 + 0x10);
  while (uVar1 = Aska::Event::IsSignal() const(param_1 + 3), (uVar1 & 1) != 0) {
    Aska::Thread::SleepU(unsigned int)(100);
  }
  Aska::StreamingStream::WorkerThread::Term()(param_1);
  *param_1 = (long)(PTR__ZTVN4Aska17TWorkerThreadBaseINS_15StreamingStream12WorkerThreadEEE_02cb8f08
                   + 0x10);
  Aska::Event::Exit()(param_1 + 3);
  Aska::Thread::~Thread()(param_1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::TWorkerThreadBase<Aska::StreamingStream::WorkerThread>::Handler()
// vaddr 0x1f74fe8 | ghidra 0x2074fe8 | size 64 | symbol _ZN4Aska17TWorkerThreadBaseINS_15StreamingStream12WorkerThreadEE7HandlerEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska17TWorkerThreadBaseINS_15StreamingStream12WorkerThreadEE7HandlerEv(long param_1)

{
  while( true ) {
    Aska::Event::Wait(unsigned int) const(param_1 + 0x18,0);
    if (*(char *)(param_1 + 0x81) != '\0') break;
    Aska::StreamingStream::WorkerThread::Sequencer()(param_1);
  }
  *(undefined1 *)(param_1 + 0x81) = 0;
  return;
}

// ==== Aska::TWorkerThreadBase<Aska::StreamingStream::WorkerThread>::~TWorkerThreadBase()
// vaddr 0x1f75028 | ghidra 0x2075028 | size 40 | symbol _ZN4Aska17TWorkerThreadBaseINS_15StreamingStream12WorkerThreadEED2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska17TWorkerThreadBaseINS_15StreamingStream12WorkerThreadEED2Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska17TWorkerThreadBaseINS_15StreamingStream12WorkerThreadEEE_02cb8f08
                   + 0x10);
  Aska::Event::Exit()(param_1 + 3);
  (*(code *)PTR__ZN4Aska6ThreadD1Ev_02c9be08)(param_1);
  return;
}

// ==== Aska::TWorkerThreadBase<Aska::StreamingStream::WorkerThread>::~TWorkerThreadBase()
// vaddr 0x1f75050 | ghidra 0x2075050 | size 48 | symbol _ZN4Aska17TWorkerThreadBaseINS_15StreamingStream12WorkerThreadEED0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska17TWorkerThreadBaseINS_15StreamingStream12WorkerThreadEED0Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska17TWorkerThreadBaseINS_15StreamingStream12WorkerThreadEEE_02cb8f08
                   + 0x10);
  Aska::Event::Exit()(param_1 + 3);
  Aska::Thread::~Thread()(param_1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::TQueue<Aska::StreamingStream::WorkerThread::Request, 9>::~TQueue()
// vaddr 0x1f75080 | ghidra 0x2075080 | size 4 | symbol _ZN4Aska6TQueueINS_15StreamingStream12WorkerThread7RequestELi9EED2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6TQueueINS_15StreamingStream12WorkerThread7RequestELi9EED2Ev(void)

{
  return;
}

// ==== Aska::TQueue<Aska::StreamingStream::WorkerThread::Request, 9>::~TQueue()
// vaddr 0x1f75084 | ghidra 0x2075084 | size 4 | symbol _ZN4Aska6TQueueINS_15StreamingStream12WorkerThread7RequestELi9EED0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6TQueueINS_15StreamingStream12WorkerThread7RequestELi9EED0Ev(void)

{
  (*(code *)PTR__ZdlPv_02ca4758)();
  return;
}

// ==== Aska::StreamingStream::~StreamingStream()
// vaddr 0x1f750cc | ghidra 0x20750cc | size 232 | symbol _ZN4Aska15StreamingStreamD2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska15StreamingStreamD2Ev(long *param_1)

{
  int iVar1;
  char cVar2;
  bool bVar3;
  undefined *puVar4;
  ulong uVar5;
  int *piVar6;
  
  *param_1 = (long)(PTR__ZTVN4Aska15StreamingStreamE_02cc1e40 + 0x10);
  Aska::StreamingStream::Close()();
  Aska::FastCriticalSection::~FastCriticalSection()(param_1 + 0x77);
  param_1[0x30] = (long)(PTR__ZTVN4Aska15StreamingStream12WorkerThreadE_02cc3220 + 0x10);
  while (uVar5 = Aska::Event::IsSignal() const(param_1 + 0x33), (uVar5 & 1) != 0) {
    Aska::Thread::SleepU(unsigned int)(100);
  }
  Aska::StreamingStream::WorkerThread::Term()(param_1 + 0x30);
  param_1[0x30] =
       (long)(PTR__ZTVN4Aska17TWorkerThreadBaseINS_15StreamingStream12WorkerThreadEEE_02cb8f08 +
             0x10);
  Aska::Event::Exit()(param_1 + 0x33);
  Aska::Thread::~Thread()(param_1 + 0x30);
  puVar4 = PTR__ZTVN4Aska11TPoolAtomicINS_15StreamingStream15BufferingNotifyELi9EEE_02cc33b0;
  *(undefined1 *)(param_1 + 0x2f) = 0;
  param_1[8] = (long)(puVar4 + 0x10);
  *(undefined4 *)(param_1 + 0x2e) = 0;
  Aska::RingBuffer::Close()(param_1 + 1);
  piVar6 = (int *)param_1[2];
  if (piVar6 != (int *)0x0) {
    do {
      iVar1 = *piVar6;
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar6,0x10);
      if (bVar3) {
        *piVar6 = iVar1 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    if (iVar1 + -1 != 0) goto code_r0x020751a4;
  }
  if (param_1[1] != 0) {
    operator delete[](void*)();
  }
  if (param_1[2] != 0) {
    Aska::TSharedPointerCode::DeleteCounter(int*)();
  }
code_r0x020751a4:
  param_1[1] = 0;
  param_1[2] = 0;
  return;
}

// ==== Aska::StaticStream::Open(signed char const*, unsigned long)
// vaddr 0x1f7b4ec | ghidra 0x207b4ec | size 40 | symbol _ZN4Aska12StaticStream4OpenEPKam | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska12StaticStream4OpenEPKam(long param_1,undefined8 param_2,undefined8 param_3)

{
  if (*(long *)(param_1 + 0x28) != 0) {
    return 0;
  }
  *(undefined8 *)(param_1 + 0x28) = param_2;
  *(undefined8 *)(param_1 + 0x30) = param_3;
  *(undefined8 *)(param_1 + 0x38) = 0;
  *(undefined4 *)(param_1 + 0x40) = 0;
  *(undefined8 *)(param_1 + 0x48) = 0;
  return 1;
}

// ==== Aska::StaticStream::Seek(long, int)
// vaddr 0x1f7b514 | ghidra 0x207b514 | size 156 | symbol _ZN4Aska12StaticStream4SeekEli | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska12StaticStream4SeekEli(long *param_1,undefined8 param_2,undefined4 param_3)

{
  ulong uVar1;
  long lVar2;
  long lStack_28;
  
  uVar1 = (**(code **)(*param_1 + 0x10))();
  if ((uVar1 & 1) != 0) {
    lVar2 = Aska::IStream::CalcSeekPt(long, long, long, long, int, long*)(param_1[7],0,param_1[6],param_2,param_3,&lStack_28);
    if (lStack_28 < 0) {
      (**(code **)(*param_1 + 0x48))(param_1,lStack_28);
    }
    param_1[7] = lVar2;
    return lStack_28;
  }
                    /* WARNING: Could not recover jumptable at 0x0207b5ac. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  lVar2 = (**(code **)(*param_1 + 0x48))(param_1,0xfffffffffffffc44);
  return lVar2;
}

// ==== Aska::StaticStream::Tell() const
// vaddr 0x1f7b5b0 | ghidra 0x207b5b0 | size 80 | symbol _ZNK4Aska12StaticStream4TellEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK4Aska12StaticStream4TellEv(long *param_1)

{
  ulong uVar1;
  undefined8 uVar2;
  long lVar3;
  
  uVar1 = (**(code **)(*param_1 + 0x10))();
  if ((uVar1 & 1) == 0) {
    lVar3 = *param_1;
    uVar2 = 0xfffffffffffffc44;
  }
  else {
    if ((ulong)param_1[7] <= (ulong)param_1[6]) {
      return;
    }
    lVar3 = *param_1;
    uVar2 = 0xfffffffffffffc3f;
  }
                    /* WARNING: Could not recover jumptable at 0x0207b5f4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(lVar3 + 0x48))(param_1,uVar2);
  return;
}

// ==== Aska::StaticStream::Read(void*, unsigned long, unsigned long)
// vaddr 0x1f7b600 | ghidra 0x207b600 | size 204 | symbol _ZN4Aska12StaticStream4ReadEPvmm | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZN4Aska12StaticStream4ReadEPvmm(long *param_1,undefined8 param_2,ulong param_3,ulong param_4)

{
  ulong uVar1;
  ulong uVar2;
  undefined8 uVar3;
  ulong uVar4;
  long lVar5;
  ulong uVar6;
  
  uVar2 = (**(code **)(*param_1 + 0x10))();
  if ((uVar2 & 1) == 0) {
    lVar5 = *param_1;
    uVar3 = 0xfffffffffffffc44;
  }
  else {
    uVar2 = param_1[6];
    uVar4 = param_1[7];
    uVar1 = uVar2 - uVar4;
    if (uVar4 <= uVar2 && uVar1 != 0) {
      uVar6 = param_4 * param_3;
      if (uVar2 < uVar4 + param_4 * param_3) {
        param_4 = 0;
        if (param_3 != 0) {
          param_4 = uVar1 / param_3;
        }
        (**(code **)(*param_1 + 0x48))(param_1,0xfffffffffffffc3f);
        uVar4 = param_1[7];
        uVar6 = uVar1;
      }
      memcpy(param_2,uVar4 + param_1[5],uVar6);
      param_1[7] = param_1[7] + uVar6;
      return param_4;
    }
    lVar5 = *param_1;
    uVar3 = 0xfffffffffffffc3f;
  }
  (**(code **)(lVar5 + 0x48))(param_1,uVar3);
  return 0;
}

// ==== Aska::StaticStream::Write(void const*, unsigned long, unsigned long)
// vaddr 0x1f7b6cc | ghidra 0x207b6cc | size 204 | symbol _ZN4Aska12StaticStream5WriteEPKvmm | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZN4Aska12StaticStream5WriteEPKvmm
                (long *param_1,undefined8 param_2,ulong param_3,ulong param_4)

{
  ulong uVar1;
  ulong uVar2;
  undefined8 uVar3;
  ulong uVar4;
  long lVar5;
  ulong uVar6;
  
  uVar2 = (**(code **)(*param_1 + 0x10))();
  if ((uVar2 & 1) == 0) {
    lVar5 = *param_1;
    uVar3 = 0xfffffffffffffc44;
  }
  else {
    uVar2 = param_1[6];
    uVar4 = param_1[7];
    uVar1 = uVar2 - uVar4;
    if (uVar4 <= uVar2 && uVar1 != 0) {
      uVar6 = param_4 * param_3;
      if (uVar2 < uVar4 + param_4 * param_3) {
        param_4 = 0;
        if (param_3 != 0) {
          param_4 = uVar1 / param_3;
        }
        (**(code **)(*param_1 + 0x48))(param_1,0xfffffffffffffc3f);
        uVar4 = param_1[7];
        uVar6 = uVar1;
      }
      memcpy(uVar4 + param_1[5],param_2,uVar6);
      param_1[7] = param_1[7] + uVar6;
      return param_4;
    }
    lVar5 = *param_1;
    uVar3 = 0xfffffffffffffc3f;
  }
  (**(code **)(lVar5 + 0x48))(param_1,uVar3);
  return 0;
}

// ==== Aska::StaticStream::Flush()
// vaddr 0x1f7b798 | ghidra 0x207b798 | size 60 | symbol _ZN4Aska12StaticStream5FlushEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska12StaticStream5FlushEv(long *param_1)

{
  ulong uVar1;
  undefined8 uVar2;
  
  uVar1 = (**(code **)(*param_1 + 0x10))();
  if ((uVar1 & 1) != 0) {
    return 0;
  }
                    /* WARNING: Could not recover jumptable at 0x0207b7d0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  uVar2 = (**(code **)(*param_1 + 0x48))(param_1,0xfffffffffffffc44);
  return uVar2;
}

// ==== Aska::StaticStream::IsEnd(long*) const
// vaddr 0x1f7b7d4 | ghidra 0x207b7d4 | size 104 | symbol _ZNK4Aska12StaticStream5IsEndEPl | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK4Aska12StaticStream5IsEndEPl(long *param_1,undefined8 *param_2)

{
  bool bVar1;
  ulong uVar2;
  
  uVar2 = (**(code **)(*param_1 + 0x10))();
  if ((uVar2 & 1) == 0) {
    (**(code **)(*param_1 + 0x48))(param_1,0xfffffffffffffc44);
    if (param_2 != (undefined8 *)0x0) {
      *param_2 = 0xfffffffffffffc44;
    }
    bVar1 = true;
  }
  else {
    if (param_2 != (undefined8 *)0x0) {
      *param_2 = 0;
    }
    bVar1 = (ulong)param_1[6] <= (ulong)param_1[7];
  }
  return bVar1;
}

// ==== Aska::StaticStream::Lock(void**, unsigned long)
// vaddr 0x1f7b83c | ghidra 0x207b83c | size 204 | symbol _ZN4Aska12StaticStream4LockEPPvm | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska12StaticStream4LockEPPvm(long *param_1,long *param_2,long param_3)

{
  char cVar1;
  bool bVar2;
  ulong uVar3;
  long lVar4;
  
  uVar3 = (**(code **)(*param_1 + 0xb0))();
  if ((uVar3 & 1) != 0) {
    if (param_3 == 0) {
      param_3 = param_1[6] - param_1[7];
    }
    uVar3 = (**(code **)(*param_1 + 0xa8))(param_1,0,param_3,0);
    if ((uVar3 & 1) == 0) {
      param_3 = param_1[6] - param_1[7];
      (**(code **)(*param_1 + 0x48))(param_1,0xfffffffffffffc3f);
    }
    if (param_3 != 0) {
      *param_2 = param_1[7] + param_1[5];
      param_1[7] = param_1[7] + param_3;
      param_1 = param_1 + 8;
      do {
        cVar1 = '\x01';
        bVar2 = (bool)ExclusiveMonitorPass(param_1,0x10);
        if (bVar2) {
          *(int *)param_1 = (int)*param_1 + (int)param_3;
          cVar1 = ExclusiveMonitorsStatus();
        }
      } while (cVar1 != '\0');
    }
    return param_3;
  }
                    /* WARNING: Could not recover jumptable at 0x0207b904. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  lVar4 = (**(code **)(*param_1 + 0x48))(param_1,0xfffffffffffffc44);
  return lVar4;
}

// ==== Aska::StaticStream::Unlock(unsigned long)
// vaddr 0x1f7b908 | ghidra 0x207b908 | size 168 | symbol _ZN4Aska12StaticStream6UnlockEm | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska12StaticStream6UnlockEm(long *param_1,long param_2)

{
  char cVar1;
  bool bVar2;
  ulong uVar3;
  long lVar4;
  
  uVar3 = (**(code **)(*param_1 + 0xb0))();
  if ((uVar3 & 1) != 0) {
    if (param_2 == 0) {
      param_2 = (long)(int)param_1[8];
    }
    uVar3 = (**(code **)(*param_1 + 0xa8))(param_1,1,param_2,0);
    if ((uVar3 & 1) == 0) {
      param_2 = (long)(int)param_1[8];
      (**(code **)(*param_1 + 0x48))(param_1,0xfffffffffffffc3f);
    }
    if (param_2 != 0) {
      param_1 = param_1 + 8;
      do {
        cVar1 = '\x01';
        bVar2 = (bool)ExclusiveMonitorPass(param_1,0x10);
        if (bVar2) {
          *(int *)param_1 = (int)*param_1 - (int)param_2;
          cVar1 = ExclusiveMonitorsStatus();
        }
      } while (cVar1 != '\0');
    }
    return param_2;
  }
                    /* WARNING: Could not recover jumptable at 0x0207b9ac. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  lVar4 = (**(code **)(*param_1 + 0x48))(param_1,0xfffffffffffffc44);
  return lVar4;
}

// ==== Aska::StaticStream::IsBufferable(int, unsigned long, long*) const
// vaddr 0x1f7b9b0 | ghidra 0x207b9b0 | size 176 | symbol _ZNK4Aska12StaticStream12IsBufferableEimPl | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK4Aska12StaticStream12IsBufferableEimPl
               (long *param_1,int param_2,ulong param_3,undefined8 *param_4)

{
  bool bVar1;
  ulong uVar2;
  
  uVar2 = (**(code **)(*param_1 + 0xb0))();
  if ((uVar2 & 1) == 0) {
    (**(code **)(*param_1 + 0x48))(param_1,0xfffffffffffffc44);
    bVar1 = false;
    if (param_4 != (undefined8 *)0x0) {
      *param_4 = 0xfffffffffffffc44;
    }
  }
  else {
    if (param_4 != (undefined8 *)0x0) {
      *param_4 = 0;
    }
    if (param_2 == 0) {
      if (param_3 == 0) {
        bVar1 = (ulong)param_1[7] < (ulong)param_1[6];
      }
      else {
        bVar1 = param_1[7] + param_3 <= (ulong)param_1[6];
      }
    }
    else if (param_3 == 0) {
      bVar1 = 0 < (int)param_1[8];
    }
    else {
      bVar1 = param_3 <= (ulong)(long)(int)param_1[8];
    }
  }
  return bVar1;
}

// ==== Aska::StaticStream::IsBufferingEnd(int, long*) const
// vaddr 0x1f7ba60 | ghidra 0x207ba60 | size 144 | symbol _ZNK4Aska12StaticStream14IsBufferingEndEiPl | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK4Aska12StaticStream14IsBufferingEndEiPl(long *param_1,int param_2,undefined8 *param_3)

{
  bool bVar1;
  ulong uVar2;
  
  uVar2 = (**(code **)(*param_1 + 0xb0))();
  if ((uVar2 & 1) == 0) {
    (**(code **)(*param_1 + 0x48))(param_1,0xfffffffffffffc44);
    if (param_3 != (undefined8 *)0x0) {
      *param_3 = 0xfffffffffffffc44;
    }
    bVar1 = true;
  }
  else {
    if (param_3 != (undefined8 *)0x0) {
      *param_3 = 0;
    }
    bVar1 = param_2 == 0 && (ulong)param_1[6] <= (ulong)param_1[7];
    if ((param_2 != 0) && ((ulong)param_1[6] <= (ulong)param_1[7])) {
      bVar1 = (int)param_1[8] == 0;
    }
  }
  return bVar1;
}

// ==== Aska::StaticStream::~StaticStream()
// vaddr 0x1f7baf0 | ghidra 0x207baf0 | size 144 | symbol _ZN4Aska12StaticStreamD2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska12StaticStreamD2Ev(long *param_1)

{
  int iVar1;
  char cVar2;
  bool bVar3;
  int *piVar4;
  
  piVar4 = (int *)param_1[4];
  *param_1 = (long)(PTR__ZTVN4Aska12StaticStreamE_02cba478 + 0x10);
  if (piVar4 == (int *)0x0) {
code_r0x0207bb24:
    if (param_1[3] != 0) {
      operator delete[](void*)();
    }
    if (param_1[4] != 0) {
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
    if (iVar1 + -1 == 0) goto code_r0x0207bb24;
  }
  piVar4 = (int *)param_1[2];
  param_1[3] = 0;
  param_1[4] = 0;
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
    if (iVar1 + -1 != 0) goto code_r0x0207bb74;
  }
  if (param_1[1] != 0) {
    operator delete[](void*)();
  }
  if (param_1[2] != 0) {
    Aska::TSharedPointerCode::DeleteCounter(int*)();
  }
code_r0x0207bb74:
  param_1[1] = 0;
  param_1[2] = 0;
  return;
}

// ==== Aska::StaticStream::~StaticStream()
// vaddr 0x1f7bb80 | ghidra 0x207bb80 | size 148 | symbol _ZN4Aska12StaticStreamD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska12StaticStreamD0Ev(long *param_1)

{
  int iVar1;
  char cVar2;
  bool bVar3;
  int *piVar4;
  
  piVar4 = (int *)param_1[4];
  *param_1 = (long)(PTR__ZTVN4Aska12StaticStreamE_02cba478 + 0x10);
  if (piVar4 == (int *)0x0) {
code_r0x0207bbb4:
    if (param_1[3] != 0) {
      operator delete[](void*)();
    }
    if (param_1[4] != 0) {
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
    if (iVar1 + -1 == 0) goto code_r0x0207bbb4;
  }
  piVar4 = (int *)param_1[2];
  param_1[3] = 0;
  param_1[4] = 0;
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
    if (iVar1 + -1 != 0) goto code_r0x011d8ed0;
  }
  if (param_1[1] != 0) {
    operator delete[](void*)();
  }
  if (param_1[2] != 0) {
    Aska::TSharedPointerCode::DeleteCounter(int*)();
  }
code_r0x011d8ed0:
  param_1[1] = 0;
  param_1[2] = 0;
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::StaticStream::IsReady() const
// vaddr 0x1f7bc14 | ghidra 0x207bc14 | size 16 | symbol _ZNK4Aska12StaticStream7IsReadyEv | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK4Aska12StaticStream7IsReadyEv(long param_1)

{
  return *(long *)(param_1 + 0x28) != 0;
}

// ==== Aska::StaticStream::SetLastError(long) const
// vaddr 0x1f7bc24 | ghidra 0x207bc24 | size 12 | symbol _ZNK4Aska12StaticStream12SetLastErrorEl | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska12StaticStream12SetLastErrorEl(long param_1,undefined8 param_2)

{
  *(undefined8 *)(param_1 + 0x48) = param_2;
  return param_2;
}

// ==== Aska::StaticStream::GetLastError() const
// vaddr 0x1f7bc30 | ghidra 0x207bc30 | size 16 | symbol _ZNK4Aska12StaticStream12GetLastErrorEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska12StaticStream12GetLastErrorEv(long param_1)

{
  undefined8 uVar1;
  
  uVar1 = *(undefined8 *)(param_1 + 0x48);
  *(undefined8 *)(param_1 + 0x48) = 0;
  return uVar1;
}

// ==== Aska::StaticStream::PeekLastError() const
// vaddr 0x1f7bc40 | ghidra 0x207bc40 | size 8 | symbol _ZNK4Aska12StaticStream13PeekLastErrorEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska12StaticStream13PeekLastErrorEv(long param_1)

{
  return *(undefined8 *)(param_1 + 0x48);
}

// ==== Aska::StaticStream::GetTotalSize() const
// vaddr 0x1f7bc48 | ghidra 0x207bc48 | size 32 | symbol _ZNK4Aska12StaticStream12GetTotalSizeEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK4Aska12StaticStream12GetTotalSizeEv(long *param_1)

{
  long lVar1;
  
  lVar1 = param_1[6];
  if (-1 < lVar1) {
    return lVar1;
  }
                    /* WARNING: Could not recover jumptable at 0x0207bc64. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  lVar1 = (**(code **)(*param_1 + 0x48))(param_1,lVar1);
  return lVar1;
}

// ==== Aska::StaticStream::IsBufferingReady() const
// vaddr 0x1f7bc68 | ghidra 0x207bc68 | size 12 | symbol _ZNK4Aska12StaticStream16IsBufferingReadyEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK4Aska12StaticStream16IsBufferingReadyEv(long *param_1)

{
                    /* WARNING: Could not recover jumptable at 0x0207bc70. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*param_1 + 0x10))();
  return;
}

// ==== Aska::StreamingStream::Open(Aska::IStream*, unsigned long, unsigned long, unsigned long, unsigned long)
// vaddr 0x1f7bc74 | ghidra 0x207bc74 | size 172 | symbol _ZN4Aska15StreamingStream4OpenEPNS_7IStreamEmmmm | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska15StreamingStream4OpenEPNS_7IStreamEmmmm
          (long param_1,undefined8 param_2,long param_3,undefined8 param_4,undefined8 param_5,
          undefined8 param_6)

{
  long lVar1;
  ulong uVar2;
  
  if ((*(long *)(param_1 + 0x18) == 0) || (*(long *)(param_1 + 0x3b0) == 0)) {
    lVar1 = 0x40000;
    if (param_3 != 0) {
      lVar1 = param_3;
    }
    uVar2 = Aska::RingBuffer::Open(unsigned long)(param_1 + 8,lVar1);
    if (((uVar2 & 1) != 0) &&
       (uVar2 = Aska::StreamingStream::Open_(Aska::IStream*, unsigned long, unsigned long, unsigned long)(param_1,param_2,param_4,param_5,param_6), (uVar2 & 1) != 0)) {
      return 1;
    }
    if ((*(long *)(param_1 + 0x18) != 0) && (*(long *)(param_1 + 0x3b0) != 0)) {
      Aska::StreamingStream::Close_()(param_1);
      Aska::RingBuffer::Close()(param_1 + 8);
    }
  }
  return 0;
}

// ==== Aska::StreamingStream::Close()
// vaddr 0x1f7bd20 | ghidra 0x207bd20 | size 52 | symbol _ZN4Aska15StreamingStream5CloseEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska15StreamingStream5CloseEv(long param_1)

{
  if ((*(long *)(param_1 + 0x18) != 0) && (*(long *)(param_1 + 0x3b0) != 0)) {
    Aska::StreamingStream::Close_()(param_1);
    (*(code *)PTR__ZN4Aska10RingBuffer5CloseEv_02caf3f0)(param_1 + 8);
    return;
  }
  return;
}

// ==== Aska::StreamingStream::Open_(Aska::IStream*, unsigned long, unsigned long, unsigned long)
// vaddr 0x1f7bd54 | ghidra 0x207bd54 | size 428 | symbol _ZN4Aska15StreamingStream5Open_EPNS_7IStreamEmmm | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska15StreamingStream5Open_EPNS_7IStreamEmmm
          (long param_1,long *param_2,ulong param_3,long param_4,long param_5)

{
  ulong uVar1;
  undefined8 uVar2;
  long lVar3;
  ulong uVar4;
  ulong uVar5;
  ulong uVar6;
  
  uVar4 = *(ulong *)(param_1 + 0x20);
  uVar5 = uVar4 >> 2;
  if (param_3 != 0) {
    uVar5 = param_3;
  }
  if (uVar5 << 3 < uVar4) {
    return 0;
  }
  if (param_2 == (long *)0x0) {
    return 0;
  }
  if ((((uint)uVar5 | (uint)uVar4) & 0x1ff) != 0) {
    return 0;
  }
  uVar6 = 0;
  if (uVar5 != 0) {
    uVar6 = uVar4 / uVar5;
  }
  if (uVar4 != uVar6 * uVar5) {
    return 0;
  }
  *(ulong *)(param_1 + 0x450) = uVar5;
  uVar2 = (**(code **)(*param_2 + 0x60))(param_2);
  *(undefined8 *)(param_1 + 0x490) = uVar2;
  lVar3 = (**(code **)(*param_2 + 0x18))(param_2);
  *(long *)(param_1 + 0x478) = lVar3;
  *(long *)(param_1 + 0x460) = lVar3;
  if (param_5 == 0 && param_4 == 0) {
    param_5 = *(long *)(param_1 + 0x490) + lVar3;
    param_4 = lVar3;
  }
  *(long *)(param_1 + 0x480) = param_4;
  *(long *)(param_1 + 0x488) = param_5;
  *(long *)(param_1 + 0x468) = param_4;
  *(long *)(param_1 + 0x470) = param_5;
  *(undefined4 *)(param_1 + 0x448) = 0;
  *(undefined1 *)(param_1 + 0x4a1) = 0;
  *(undefined2 *)(param_1 + 0x4a2) = 0;
  Aska::RingBuffer::Reset()(param_1 + 8);
  *(undefined4 *)(param_1 + 0x498) = 0;
  *(undefined4 *)(param_1 + 0x49c) = 0;
  if (*(long *)(param_1 + 0x3b0) == 0) {
    if (*(char *)(param_1 + 0x200) == '\0') {
      *(undefined1 *)(param_1 + 0x201) = 0;
      uVar5 = Aska::Event::Create(bool, bool)(param_1 + 0x198,0,0);
      if (((uVar5 & 1) == 0) ||
         (uVar5 = Aska::Thread::Create(bool, int, int, bool)(param_1 + 0x180,0,0x7f,0x8000,1), (uVar5 & 1) == 0))
      goto code_r0x0207be24;
      *(undefined1 *)(param_1 + 0x200) = 1;
    }
    *(long **)(param_1 + 0x3b0) = param_2;
    *(undefined1 *)(param_1 + 0x4a0) = 0;
    uVar5 = *(ulong *)(param_1 + 0x450);
    uVar4 = (*(long *)(param_1 + 0x20) - (long)*(int *)(param_1 + 0x38)) -
            (long)*(int *)(param_1 + 0x498);
    if (uVar4 < uVar5) {
      return 1;
    }
    lVar3 = Aska::StreamingStream::Streaming_LockFront(unsigned long)(param_1,uVar5);
    if ((-1 < lVar3) || (lVar3 == -0x3eb)) {
      uVar6 = 0;
      uVar1 = 0;
      if (uVar5 != 0) {
        uVar1 = uVar4 / uVar5;
      }
      do {
        uVar6 = uVar6 + 1;
        if (uVar1 <= uVar6) {
          return 1;
        }
        lVar3 = Aska::StreamingStream::Streaming_LockFront(unsigned long)(param_1,*(undefined8 *)(param_1 + 0x450));
      } while ((-1 < lVar3) || (lVar3 == -0x3eb));
    }
  }
code_r0x0207be24:
  Aska::StreamingStream::Close_()(param_1);
  return 0;
}

// ==== Aska::StreamingStream::Open(Aska::IStream*, void const*, unsigned long, unsigned long, unsigned long, unsigned long)
// vaddr 0x1f7bf00 | ghidra 0x207bf00 | size 168 | symbol _ZN4Aska15StreamingStream4OpenEPNS_7IStreamEPKvmmmm | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska15StreamingStream4OpenEPNS_7IStreamEPKvmmmm
          (long param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5,
          undefined8 param_6,undefined8 param_7)

{
  ulong uVar1;
  
  if ((*(long *)(param_1 + 0x18) == 0) || (*(long *)(param_1 + 0x3b0) == 0)) {
    uVar1 = Aska::RingBuffer::Open(void const*, unsigned long)(param_1 + 8,param_3,param_4);
    if (((uVar1 & 1) != 0) &&
       (uVar1 = Aska::StreamingStream::Open_(Aska::IStream*, unsigned long, unsigned long, unsigned long)(param_1,param_2,param_5,param_6,param_7), (uVar1 & 1) != 0)) {
      return 1;
    }
    if ((*(long *)(param_1 + 0x18) != 0) && (*(long *)(param_1 + 0x3b0) != 0)) {
      Aska::StreamingStream::Close_()(param_1);
      Aska::RingBuffer::Close()(param_1 + 8);
    }
  }
  return 0;
}

// ==== Aska::StreamingStream::Close_()
// vaddr 0x1f7bfa8 | ghidra 0x207bfa8 | size 252 | symbol _ZN4Aska15StreamingStream6Close_Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska15StreamingStream6Close_Ev(long *param_1)

{
  int iVar1;
  long lVar2;
  long lVar3;
  
  *(undefined1 *)(param_1 + 0x94) = 1;
  lVar2 = Aska::Global::GetCPUTime()();
  iVar1 = *(int *)((long)param_1 + 0x174);
  do {
    if (iVar1 == 0) {
      lVar2 = param_1[0x76];
joined_r0x0207bff4:
      if (((lVar2 != 0) && (param_1[0x76] = 0, (char)param_1[0x40] != '\0')) &&
         (*(char *)((long)param_1 + 0x201) == '\0')) {
        *(undefined1 *)((long)param_1 + 0x201) = 1;
        Aska::Event::Set() const(param_1 + 0x33);
        Aska::Thread::WaitEnd()(param_1 + 0x30);
        Aska::Event::Exit()(param_1 + 0x33);
        Aska::Thread::Delete()(param_1 + 0x30);
        *(undefined1 *)(param_1 + 0x40) = 0;
      }
      param_1[0x8a] = 0;
      param_1[0x92] = 0;
      param_1[0x91] = 0;
      param_1[0x90] = 0;
      param_1[0x8f] = 0;
      param_1[0x8e] = 0;
      param_1[0x8d] = 0;
      param_1[0x8c] = 0;
      *(undefined4 *)(param_1 + 0x89) = 0;
      *(undefined1 *)((long)param_1 + 0x4a1) = 0;
      *(undefined2 *)((long)param_1 + 0x4a2) = 0;
      Aska::RingBuffer::Reset()(param_1 + 1);
      *(undefined4 *)(param_1 + 0x93) = 0;
      *(undefined4 *)((long)param_1 + 0x49c) = 0;
      return;
    }
    lVar3 = Aska::Global::GetCPUTime()();
    if ((ulong)param_1[0x8b] <= (ulong)(lVar3 - lVar2)) {
      *(undefined1 *)(param_1 + 0x94) = 0;
      (**(code **)(*param_1 + 0x48))(param_1,0xfffffffffffffc3a);
      lVar2 = param_1[0x76];
      goto joined_r0x0207bff4;
    }
    Aska::Thread::Sleep(unsigned int)(1);
    iVar1 = *(int *)((long)param_1 + 0x174);
  } while( true );
}

// ==== Aska::StreamingStream::Seek(long, int)
// vaddr 0x1f7c0a4 | ghidra 0x207c0a4 | size 304 | symbol _ZN4Aska15StreamingStream4SeekEli | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska15StreamingStream4SeekEli(long *param_1,undefined8 param_2,undefined4 param_3)

{
  bool bVar1;
  ulong uVar2;
  long lVar3;
  long lVar4;
  long lVar5;
  long lStack_38;
  
  uVar2 = (**(code **)(*param_1 + 0x10))();
  if ((uVar2 & 1) != 0) {
    lVar5 = param_1[0x8c];
    lVar4 = param_1[0x8e];
    lVar3 = Aska::IStream::CalcSeekPt(long, long, long, long, int, long*)(lVar5,0,lVar4,param_2,param_3,&lStack_38);
    if (lStack_38 < 0) {
      (**(code **)(*param_1 + 0x48))(param_1);
    }
    lVar5 = lVar3 - lVar5;
    if ((lVar5 < 1) || ((long)(int)param_1[7] - (long)*(int *)((long)param_1 + 0x49c) < lVar5)) {
      bVar1 = lVar4 <= lVar3;
      param_1[0x8c] = lVar3;
      param_1[0x8f] = lVar3;
      *(bool *)((long)param_1 + 0x4a1) = bVar1;
      *(ushort *)((long)param_1 + 0x4a2) = CONCAT11(bVar1,bVar1);
      lVar3 = Aska::StreamingStream::SeekBuffering(long, int, bool)(param_1,lVar3,0,1);
      if (lVar3 < 0) {
        lStack_38 = lVar3;
      }
    }
    else {
      lVar3 = Aska::IBufferingStream::BufferingRead(void*, unsigned long)(param_1,0);
      if (lVar3 < 0) {
        (**(code **)(*param_1 + 0x48))(param_1,lVar3);
        lStack_38 = 0;
      }
    }
    return lStack_38;
  }
                    /* WARNING: Could not recover jumptable at 0x0207c188. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  lVar3 = (**(code **)(*param_1 + 0x48))(param_1,0xfffffffffffffc44);
  return lVar3;
}

// ==== Aska::StreamingStream::SeekBuffering(long, int, bool)
// vaddr 0x1f7c1d4 | ghidra 0x207c1d4 | size 296 | symbol _ZN4Aska15StreamingStream13SeekBufferingElib | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska15StreamingStream13SeekBufferingElib
               (long *param_1,undefined8 param_2,undefined4 param_3,uint param_4)

{
  int iVar1;
  ulong uVar2;
  long lVar3;
  long lVar4;
  ulong uVar5;
  ulong uVar6;
  ulong uVar7;
  
  *(undefined1 *)(param_1 + 0x94) = 1;
  lVar3 = Aska::Global::GetCPUTime()();
  iVar1 = *(int *)((long)param_1 + 0x174);
  do {
    if (iVar1 == 0) {
code_r0x0207c24c:
      lVar3 = (**(code **)(*(long *)param_1[0x76] + 0x20))((long *)param_1[0x76],param_2,param_3);
      if (-1 < lVar3) {
        Aska::RingBuffer::Reset()(param_1 + 1);
        *(undefined4 *)(param_1 + 0x93) = 0;
        *(undefined4 *)((long)param_1 + 0x49c) = 0;
        if ((param_4 & 1) != 0) {
          *(undefined1 *)(param_1 + 0x94) = 0;
          uVar5 = param_1[0x8a];
          uVar7 = (param_1[4] - (long)(int)param_1[7]) - (long)(int)param_1[0x93];
          if (uVar5 <= uVar7) {
            lVar3 = Aska::StreamingStream::Streaming_LockFront(unsigned long)(param_1,uVar5);
            if ((lVar3 < 0) && (lVar3 != -0x3eb)) {
              return lVar3;
            }
            uVar6 = 0;
            uVar2 = 0;
            if (uVar5 != 0) {
              uVar2 = uVar7 / uVar5;
            }
            while (uVar6 = uVar6 + 1, uVar6 < uVar2) {
              lVar3 = Aska::StreamingStream::Streaming_LockFront(unsigned long)(param_1,param_1[0x8a]);
              if ((lVar3 < 0) && (lVar3 != -0x3eb)) {
                return lVar3;
              }
            }
          }
        }
        lVar3 = 0;
      }
      return lVar3;
    }
    lVar4 = Aska::Global::GetCPUTime()();
    if ((ulong)param_1[0x8b] <= (ulong)(lVar4 - lVar3)) {
      *(undefined1 *)(param_1 + 0x94) = 0;
      lVar3 = (**(code **)(*param_1 + 0x48))(param_1,0xfffffffffffffc3a);
      if (lVar3 < 0) {
        return lVar3;
      }
      goto code_r0x0207c24c;
    }
    Aska::Thread::Sleep(unsigned int)(1);
    iVar1 = *(int *)((long)param_1 + 0x174);
  } while( true );
}

// ==== Aska::StreamingStream::Tell() const
// vaddr 0x1f7c2fc | ghidra 0x207c2fc | size 60 | symbol _ZNK4Aska15StreamingStream4TellEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK4Aska15StreamingStream4TellEv(long *param_1)

{
  ulong uVar1;
  long lVar2;
  
  uVar1 = (**(code **)(*param_1 + 0x10))();
  if ((uVar1 & 1) != 0) {
    return param_1[0x8c];
  }
                    /* WARNING: Could not recover jumptable at 0x0207c334. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  lVar2 = (**(code **)(*param_1 + 0x48))(param_1,0xfffffffffffffc44);
  return lVar2;
}

// ==== Aska::StreamingStream::GetTotalSize() const
// vaddr 0x1f7c338 | ghidra 0x207c338 | size 60 | symbol _ZNK4Aska15StreamingStream12GetTotalSizeEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK4Aska15StreamingStream12GetTotalSizeEv(long *param_1)

{
  ulong uVar1;
  long lVar2;
  
  uVar1 = (**(code **)(*param_1 + 0x10))();
  if ((uVar1 & 1) != 0) {
    return param_1[0x92];
  }
                    /* WARNING: Could not recover jumptable at 0x0207c370. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  lVar2 = (**(code **)(*param_1 + 0x48))(param_1,0xfffffffffffffc44);
  return lVar2;
}

// ==== Aska::StreamingStream::Read(void*, unsigned long, unsigned long)
// vaddr 0x1f7c374 | ghidra 0x207c374 | size 364 | symbol _ZN4Aska15StreamingStream4ReadEPvmm | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZN4Aska15StreamingStream4ReadEPvmm(long *param_1,long param_2,ulong param_3,long param_4)

{
  ulong uVar1;
  ulong uVar2;
  long lVar3;
  ulong uVar4;
  long lVar5;
  code *pcVar6;
  ulong uVar7;
  
  uVar1 = (**(code **)(*param_1 + 0x10))();
  if ((uVar1 & 1) == 0) {
    (**(code **)(*param_1 + 0x48))(param_1,0xfffffffffffffc44);
    uVar1 = 0;
  }
  else {
    uVar7 = 0;
    uVar1 = param_4 * param_3;
    if (uVar1 != 0) {
      uVar4 = uVar1;
      if ((ulong)param_1[4] >> 2 <= uVar1) {
        uVar4 = (ulong)param_1[4] >> 2;
      }
      do {
        uVar2 = (**(code **)(*param_1 + 0x40))(param_1,0);
        if ((uVar2 & 1) != 0) {
          (**(code **)(*param_1 + 0x48))(param_1,0xfffffffffffffc3f);
          break;
        }
        uVar2 = uVar1 - uVar7;
        if (uVar4 <= uVar1 - uVar7) {
          uVar2 = uVar4;
        }
        lVar3 = Aska::Global::GetCPUTime()();
        pcVar6 = *(code **)(*param_1 + 0xa8);
        while (uVar4 = (*pcVar6)(param_1,0,uVar2,0), (uVar4 & 1) == 0) {
          lVar5 = Aska::Global::GetCPUTime()();
          if ((ulong)param_1[0x8b] <= (ulong)(lVar5 - lVar3)) {
            lVar3 = (**(code **)(*param_1 + 0x48))(param_1,0xfffffffffffffc3a);
            if (lVar3 < 0) goto code_r0x0207c498;
            break;
          }
          Aska::Thread::Sleep(unsigned int)(1);
          pcVar6 = *(code **)(*param_1 + 0xa8);
        }
        lVar3 = Aska::IBufferingStream::BufferingRead(void*, unsigned long)(param_1,param_2,uVar2);
        if (lVar3 < 0) {
code_r0x0207c498:
          (**(code **)(*param_1 + 0x48))(param_1,lVar3);
          return 0;
        }
        uVar7 = lVar3 + uVar7;
        param_2 = lVar3 + param_2;
        uVar4 = uVar2;
      } while (uVar7 <= uVar1 && uVar1 - uVar7 != 0);
    }
    uVar1 = 0;
    if (param_3 != 0) {
      uVar1 = uVar7 / param_3;
    }
  }
  return uVar1;
}

// ==== Aska::StreamingStream::WaitForBuffering(unsigned long) const
// vaddr 0x1f7c4e0 | ghidra 0x207c4e0 | size 140 | symbol _ZNK4Aska15StreamingStream16WaitForBufferingEm | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska15StreamingStream16WaitForBufferingEm(long *param_1,undefined8 param_2)

{
  long lVar1;
  ulong uVar2;
  long lVar3;
  undefined8 uVar4;
  code *pcVar5;
  
  lVar1 = Aska::Global::GetCPUTime()();
  pcVar5 = *(code **)(*param_1 + 0xa8);
  while( true ) {
    uVar2 = (*pcVar5)(param_1,0,param_2,0);
    if ((uVar2 & 1) != 0) {
      return 0;
    }
    lVar3 = Aska::Global::GetCPUTime()();
    if ((ulong)param_1[0x8b] <= (ulong)(lVar3 - lVar1)) break;
    Aska::Thread::Sleep(unsigned int)(1);
    pcVar5 = *(code **)(*param_1 + 0xa8);
  }
                    /* WARNING: Could not recover jumptable at 0x0207c558. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  uVar4 = (**(code **)(*param_1 + 0x48))(param_1,0xfffffffffffffc3a);
  return uVar4;
}

// ==== Aska::StreamingStream::Write(void const*, unsigned long, unsigned long)
// vaddr 0x1f7c56c | ghidra 0x207c56c | size 32 | symbol _ZN4Aska15StreamingStream5WriteEPKvmm | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska15StreamingStream5WriteEPKvmm(long *param_1)

{
  (**(code **)(*param_1 + 0x48))(param_1,0xfffffffffffffc46);
  return 0;
}

// ==== Aska::StreamingStream::Flush()
// vaddr 0x1f7c58c | ghidra 0x207c58c | size 16 | symbol _ZN4Aska15StreamingStream5FlushEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska15StreamingStream5FlushEv(long *param_1)

{
                    /* WARNING: Could not recover jumptable at 0x0207c598. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*param_1 + 0x48))(param_1,0xfffffffffffffc46);
  return;
}

// ==== Aska::StreamingStream::IsEnd(long*) const
// vaddr 0x1f7c59c | ghidra 0x207c59c | size 24 | symbol _ZNK4Aska15StreamingStream5IsEndEPl | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK4Aska15StreamingStream5IsEndEPl(long *param_1,undefined8 param_2)

{
                    /* WARNING: Could not recover jumptable at 0x0207c5b0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*param_1 + 0xb8))(param_1,1,param_2);
  return;
}

// ==== Aska::StreamingStream::SetLastError(long) const
// vaddr 0x1f7c5b4 | ghidra 0x207c5b4 | size 12 | symbol _ZNK4Aska15StreamingStream12SetLastErrorEl | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska15StreamingStream12SetLastErrorEl(long param_1,undefined8 param_2)

{
  *(int *)(param_1 + 0x448) = (int)param_2;
  return param_2;
}

// ==== Aska::StreamingStream::GetLastError() const
// vaddr 0x1f7c5c0 | ghidra 0x207c5c0 | size 48 | symbol _ZNK4Aska15StreamingStream12GetLastErrorEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK4Aska15StreamingStream12GetLastErrorEv(long param_1)

{
  int *piVar1;
  int iVar2;
  char cVar3;
  bool bVar4;
  long lVar5;
  
  piVar1 = (int *)(param_1 + 0x448);
  do {
    iVar2 = *piVar1;
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar4) {
      *piVar1 = 0;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
  if ((-1 < iVar2) && (*(long **)(param_1 + 0x3b0) != (long *)0x0)) {
                    /* WARNING: Could not recover jumptable at 0x0207c5e4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    lVar5 = (**(code **)(**(long **)(param_1 + 0x3b0) + 0x58))();
    return lVar5;
  }
  return (long)iVar2;
}

// ==== Aska::StreamingStream::PeekLastError() const
// vaddr 0x1f7c5f0 | ghidra 0x207c5f0 | size 40 | symbol _ZNK4Aska15StreamingStream13PeekLastErrorEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK4Aska15StreamingStream13PeekLastErrorEv(long param_1)

{
  long *plVar1;
  
  if ((-1 < *(int *)(param_1 + 0x448)) &&
     (plVar1 = *(long **)(param_1 + 0x3b0), plVar1 != (long *)0x0)) {
                    /* WARNING: Could not recover jumptable at 0x0207c610. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*plVar1 + 0x58))(plVar1);
    return;
  }
  return;
}

// ==== Aska::StreamingStream::Lock(void**, unsigned long)
// vaddr 0x1f7c618 | ghidra 0x207c618 | size 144 | symbol _ZN4Aska15StreamingStream4LockEPPvm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska15StreamingStream4LockEPPvm(long *param_1,undefined8 param_2,undefined8 param_3)

{
  ulong uVar1;
  long lVar2;
  
  uVar1 = (**(code **)(*param_1 + 0x10))();
  if ((uVar1 & 1) != 0) {
    lVar2 = Aska::StreamingStream::LockRingBuffer(int, void**, unsigned long)(param_1,0,param_2,param_3);
    if (((-1 < lVar2) &&
        (param_1[0x8c] = param_1[0x8c] + lVar2, *(char *)((long)param_1 + 0x4a1) != '\0')) &&
       ((int)param_1[7] == *(int *)((long)param_1 + 0x49c))) {
      *(undefined1 *)((long)param_1 + 0x4a2) = 1;
    }
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x0207c6a4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*param_1 + 0x48))(param_1,0xfffffffffffffc44);
  return;
}

// ==== Aska::StreamingStream::Lock_(int, void**, unsigned long)
// vaddr 0x1f7c6a8 | ghidra 0x207c6a8 | size 96 | symbol _ZN4Aska15StreamingStream5Lock_EiPPvm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska15StreamingStream5Lock_EiPPvm(long param_1,int param_2)

{
  long lVar1;
  long lVar2;
  
  lVar1 = Aska::StreamingStream::LockRingBuffer(int, void**, unsigned long)();
  if ((((-1 < lVar1) &&
       (lVar2 = param_1 + (long)param_2 * 0x18,
       *(long *)(lVar2 + 0x460) = *(long *)(lVar2 + 0x460) + lVar1, param_2 == 0)) &&
      (*(char *)(param_1 + 0x4a1) != '\0')) &&
     (*(int *)(param_1 + 0x38) == *(int *)(param_1 + 0x49c))) {
    *(undefined1 *)(param_1 + 0x4a2) = 1;
  }
  return;
}

// ==== Aska::StreamingStream::Unlock(unsigned long)
// vaddr 0x1f7c708 | ghidra 0x207c708 | size 244 | symbol _ZN4Aska15StreamingStream6UnlockEm | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska15StreamingStream6UnlockEm(long *param_1,ulong param_2)

{
  long *plVar1;
  char cVar2;
  bool bVar3;
  ulong uVar4;
  long lVar5;
  int iVar6;
  long lVar7;
  
  uVar4 = (**(code **)(*param_1 + 0x10))();
  if ((uVar4 & 1) == 0) {
                    /* WARNING: Could not recover jumptable at 0x0207c7b4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    lVar7 = (**(code **)(*param_1 + 0x48))(param_1,0xfffffffffffffc44);
    return lVar7;
  }
  plVar1 = param_1 + 0x93;
  if (param_2 == 0) {
    param_2 = (ulong)(int)*plVar1;
  }
  bVar3 = (long)(int)*plVar1 != 0;
  if (param_2 != 0) {
    bVar3 = param_2 <= (ulong)(long)(int)*plVar1;
  }
  if (!bVar3) {
    param_2 = (ulong)(int)param_1[0x93];
    (**(code **)(*param_1 + 0x48))(param_1,0xfffffffffffffc15);
  }
  if (param_2 == 0) {
    lVar7 = 0;
  }
  else {
    iVar6 = (int)param_2;
    do {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(plVar1,0x10);
      if (bVar3) {
        *(int *)plVar1 = (int)*plVar1 - iVar6;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    lVar7 = (long)iVar6;
    if (iVar6 < 0) {
      return lVar7;
    }
  }
  if ((*(char *)((long)param_1 + 0x4a2) != '\0') && ((int)*plVar1 == 0)) {
    *(undefined1 *)((long)param_1 + 0x4a3) = 1;
  }
  lVar5 = Aska::StreamingStream::Streaming_LockFront(unsigned long)(param_1,param_1[0x8a]);
  if (lVar5 == -0x3eb || -1 < lVar5) {
    lVar5 = lVar7;
  }
  return lVar5;
}

// ==== Aska::StreamingStream::Unlock_(int, unsigned long)
// vaddr 0x1f7c7fc | ghidra 0x207c7fc | size 248 | symbol _ZN4Aska15StreamingStream7Unlock_Eim | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska15StreamingStream7Unlock_Eim(long *param_1,int param_2,ulong param_3)

{
  int *piVar1;
  char cVar2;
  bool bVar3;
  long lVar4;
  int iVar5;
  long lVar6;
  
  piVar1 = (int *)((long)param_1 + (long)param_2 * 4 + 0x498);
  if (param_3 == 0) {
    param_3 = (ulong)*piVar1;
  }
  bVar3 = (long)*piVar1 != 0;
  if (param_3 != 0) {
    bVar3 = param_3 <= (ulong)(long)*piVar1;
  }
  if (!bVar3) {
    param_3 = (ulong)*piVar1;
    (**(code **)(*param_1 + 0x48))(param_1,0xfffffffffffffc15);
  }
  if (param_3 == 0) {
    lVar6 = 0;
  }
  else {
    iVar5 = (int)param_3;
    do {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar3) {
        *piVar1 = *piVar1 - iVar5;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    lVar6 = (long)iVar5;
    if (iVar5 < 0) {
      return lVar6;
    }
  }
  if (param_2 == 0) {
    if ((*(char *)((long)param_1 + 0x4a2) != '\0') && ((int)param_1[0x93] == 0)) {
      *(undefined1 *)((long)param_1 + 0x4a3) = 1;
    }
    lVar4 = Aska::StreamingStream::Streaming_LockFront(unsigned long)(param_1,param_1[0x8a]);
    if ((lVar4 < 0) && (lVar4 != -0x3eb)) {
      return lVar4;
    }
  }
  else if (((ulong)param_1[0x91] <= (ulong)param_1[0x8f]) && (*(int *)((long)param_1 + 0x49c) == 0))
  {
    *(undefined1 *)((long)param_1 + 0x4a1) = 1;
  }
  return lVar6;
}

// ==== Aska::StreamingStream::IsBufferable(int, unsigned long, long*) const
// vaddr 0x1f7c8f4 | ghidra 0x207c8f4 | size 156 | symbol _ZNK4Aska15StreamingStream12IsBufferableEimPl | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK4Aska15StreamingStream12IsBufferableEimPl
               (long *param_1,int param_2,ulong param_3,undefined8 *param_4)

{
  bool bVar1;
  ulong uVar2;
  
  uVar2 = (**(code **)(*param_1 + 0x10))();
  if ((uVar2 & 1) == 0) {
    (**(code **)(*param_1 + 0x48))(param_1,0xfffffffffffffc44);
    bVar1 = false;
    if (param_4 != (undefined8 *)0x0) {
      *param_4 = 0xfffffffffffffc44;
    }
  }
  else {
    if (param_4 != (undefined8 *)0x0) {
      *param_4 = 0;
    }
    if (param_2 == 0) {
      uVar2 = (long)(int)param_1[7] - (long)*(int *)((long)param_1 + 0x49c);
    }
    else {
      uVar2 = (ulong)(int)param_1[0x93];
    }
    bVar1 = uVar2 != 0;
    if (param_3 != 0) {
      bVar1 = param_3 <= uVar2;
    }
  }
  return bVar1;
}

// ==== Aska::StreamingStream::IsBufferable_(int, int, unsigned long, long*) const
// vaddr 0x1f7c990 | ghidra 0x207c990 | size 92 | symbol _ZNK4Aska15StreamingStream13IsBufferable_EiimPl | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK4Aska15StreamingStream13IsBufferable_EiimPl
               (long param_1,int param_2,int param_3,ulong param_4,undefined8 *param_5)

{
  bool bVar1;
  ulong uVar2;
  
  if (param_5 != (undefined8 *)0x0) {
    *param_5 = 0;
  }
  if (param_3 == 0) {
    if (param_2 == 0) {
      uVar2 = (long)*(int *)(param_1 + 0x38) - (long)*(int *)(param_1 + 0x49c);
    }
    else {
      uVar2 = (*(long *)(param_1 + 0x20) - (long)*(int *)(param_1 + 0x38)) -
              (long)*(int *)(param_1 + 0x498);
    }
  }
  else {
    uVar2 = (ulong)*(int *)(param_1 + (long)param_2 * 4 + 0x498);
  }
  bVar1 = uVar2 != 0;
  if (param_4 != 0) {
    bVar1 = param_4 <= uVar2;
  }
  return bVar1;
}

// ==== Aska::StreamingStream::IsBufferingEnd(int, long*) const
// vaddr 0x1f7c9ec | ghidra 0x207c9ec | size 112 | symbol _ZNK4Aska15StreamingStream14IsBufferingEndEiPl | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK4Aska15StreamingStream14IsBufferingEndEiPl(long *param_1,int param_2,undefined8 *param_3)

{
  bool bVar1;
  ulong uVar2;
  
  uVar2 = (**(code **)(*param_1 + 0x10))();
  if ((uVar2 & 1) == 0) {
    (**(code **)(*param_1 + 0x48))(param_1,0xfffffffffffffc44);
    if (param_3 != (undefined8 *)0x0) {
      *param_3 = 0xfffffffffffffc44;
    }
    bVar1 = true;
  }
  else {
    if (param_3 != (undefined8 *)0x0) {
      *param_3 = 0;
    }
    bVar1 = *(char *)((long)param_1 + (long)param_2 + 0x4a2) != '\0';
  }
  return bVar1;
}

// ==== Aska::StreamingStream::SetFrontSeekPt(unsigned long, unsigned long)
// vaddr 0x1f7ca5c | ghidra 0x207ca5c | size 280 | symbol _ZN4Aska15StreamingStream14SetFrontSeekPtEmm | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska15StreamingStream14SetFrontSeekPtEmm(long *param_1,long param_2,long param_3)

{
  long *plVar1;
  int iVar2;
  char cVar3;
  bool bVar4;
  undefined8 uVar5;
  uint uVar6;
  undefined8 uStack_3c;
  undefined4 uStack_34;
  
  plVar1 = param_1 + 0x75;
  param_1[0x8f] = param_2;
  param_1[0x91] = param_3;
  do {
    if ((int)*plVar1 != 0) {
      ClearExclusiveLocal();
      uVar6 = 0;
      do {
        uVar6 = uVar6 + 1;
        if ((uVar6 & 0x1ff) == 0) {
          Aska::Thread::SleepU(unsigned int)(0);
        }
        while ((int)*plVar1 == 0) {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(plVar1,0x10);
          if (bVar4) {
            *(int *)plVar1 = 1;
            cVar3 = ExclusiveMonitorsStatus();
          }
          if (cVar3 == '\0') goto code_r0x0207cad0;
        }
        ClearExclusiveLocal();
      } while( true );
    }
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(plVar1,0x10);
    if (bVar4) {
      *(int *)plVar1 = 1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
code_r0x0207cad0:
  uVar6 = *(uint *)(param_1 + 0x42);
  if (*(uint *)((long)param_1 + 0x214) != uVar6) {
    param_1[(ulong)uVar6 * 5 + 0x43] = 0;
    *(undefined4 *)(param_1 + (ulong)uVar6 * 5 + 0x44) = 1;
    param_1[(ulong)uVar6 * 5 + 0x45] = param_2;
    *(undefined4 *)(param_1 + (ulong)uVar6 * 5 + 0x46) = 0;
    *(undefined4 *)((long)param_1 + (ulong)uVar6 * 0x28 + 0x23c) = uStack_34;
    iVar2 = 0;
    if (uVar6 + 1 < 10) {
      iVar2 = uVar6 + 1;
    }
    *(undefined8 *)((long)param_1 + (ulong)uVar6 * 0x28 + 0x234) = uStack_3c;
    *(int *)(param_1 + 0x42) = iVar2;
    *(undefined4 *)(param_1 + 0x75) = 0;
    Aska::Event::Set() const(param_1 + 0x33);
    return 0;
  }
  *(undefined4 *)(param_1 + 0x75) = 0;
                    /* WARNING: Could not recover jumptable at 0x0207cb08. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  uVar5 = (**(code **)(*param_1 + 0x48))(param_1,0xfffffffffffffc02);
  return uVar5;
}

// ==== Aska::StreamingStream::SetBackSeekPt(unsigned long, unsigned long)
// vaddr 0x1f7cb74 | ghidra 0x207cb74 | size 16 | symbol _ZN4Aska15StreamingStream13SetBackSeekPtEmm | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska15StreamingStream13SetBackSeekPtEmm(long param_1,undefined8 param_2,undefined8 param_3)

{
  *(undefined8 *)(param_1 + 0x460) = param_2;
  *(undefined8 *)(param_1 + 0x470) = param_3;
  return 0;
}

// ==== Aska::StreamingStream::ResetRingBuffer()
// vaddr 0x1f7cb84 | ghidra 0x207cb84 | size 32 | symbol _ZN4Aska15StreamingStream15ResetRingBufferEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska15StreamingStream15ResetRingBufferEv(long param_1)

{
  Aska::RingBuffer::Reset()(param_1 + 8);
  *(undefined4 *)(param_1 + 0x498) = 0;
  *(undefined4 *)(param_1 + 0x49c) = 0;
  return;
}

// ==== Aska::StreamingStream::WorkerThread::Init(Aska::IStream*)
// vaddr 0x1f7cba4 | ghidra 0x207cba4 | size 148 | symbol _ZN4Aska15StreamingStream12WorkerThread4InitEPNS_7IStreamE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska15StreamingStream12WorkerThread4InitEPNS_7IStreamE
               (undefined8 *param_1,long param_2,undefined8 param_3)

{
  ulong uVar1;
  undefined8 uVar2;
  
  if (*(long *)(param_2 + 0x230) == 0) {
    if (*(char *)(param_2 + 0x80) == '\0') {
      *(undefined1 *)(param_2 + 0x81) = 0;
      uVar1 = Aska::Event::Create(bool, bool)(param_2 + 0x18,0,0);
      if (((uVar1 & 1) == 0) || (uVar1 = Aska::Thread::Create(bool, int, int, bool)(param_2,0,0x7f,0x8000,1), (uVar1 & 1) == 0)
         ) {
        uVar2 = 0xffffffffffffffff;
        goto code_r0x0207cc24;
      }
      *(undefined1 *)(param_2 + 0x80) = 1;
    }
    uVar2 = 0;
    *(undefined8 *)(param_2 + 0x230) = param_3;
  }
  else {
    uVar2 = 0xfffffffffffffc52;
  }
code_r0x0207cc24:
  *param_1 = uVar2;
  return;
}

// ==== Aska::StreamingStream::StartBuffering()
// vaddr 0x1f7cc38 | ghidra 0x207cc38 | size 144 | symbol _ZN4Aska15StreamingStream14StartBufferingEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska15StreamingStream14StartBufferingEv(long param_1)

{
  ulong uVar1;
  long lVar2;
  ulong uVar3;
  ulong uVar4;
  ulong uVar5;
  
  *(undefined1 *)(param_1 + 0x4a0) = 0;
  uVar3 = *(ulong *)(param_1 + 0x450);
  uVar5 = (*(long *)(param_1 + 0x20) - (long)*(int *)(param_1 + 0x38)) -
          (long)*(int *)(param_1 + 0x498);
  if (uVar5 < uVar3) {
code_r0x0207cc6c:
    lVar2 = 0;
  }
  else {
    lVar2 = Aska::StreamingStream::Streaming_LockFront(unsigned long)(param_1,uVar3);
    if ((-1 < lVar2) || (lVar2 == -0x3eb)) {
      uVar4 = 0;
      uVar1 = 0;
      if (uVar3 != 0) {
        uVar1 = uVar5 / uVar3;
      }
      do {
        uVar4 = uVar4 + 1;
        if (uVar1 <= uVar4) goto code_r0x0207cc6c;
        lVar2 = Aska::StreamingStream::Streaming_LockFront(unsigned long)(param_1,*(undefined8 *)(param_1 + 0x450));
      } while ((-1 < lVar2) || (lVar2 == -0x3eb));
    }
  }
  return lVar2;
}

// ==== Aska::StreamingStream::WaitForPauseBuffering()
// vaddr 0x1f7ccc8 | ghidra 0x207ccc8 | size 120 | symbol _ZN4Aska15StreamingStream21WaitForPauseBufferingEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska15StreamingStream21WaitForPauseBufferingEv(long *param_1)

{
  int iVar1;
  long lVar2;
  long lVar3;
  undefined8 uVar4;
  
  *(undefined1 *)(param_1 + 0x94) = 1;
  lVar2 = Aska::Global::GetCPUTime()();
  iVar1 = *(int *)((long)param_1 + 0x174);
  while( true ) {
    if (iVar1 == 0) {
      return 0;
    }
    lVar3 = Aska::Global::GetCPUTime()();
    if ((ulong)param_1[0x8b] <= (ulong)(lVar3 - lVar2)) break;
    Aska::Thread::Sleep(unsigned int)(1);
    iVar1 = *(int *)((long)param_1 + 0x174);
  }
  *(undefined1 *)(param_1 + 0x94) = 0;
                    /* WARNING: Could not recover jumptable at 0x0207cd3c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  uVar4 = (**(code **)(*param_1 + 0x48))(param_1,0xfffffffffffffc3a);
  return uVar4;
}

// ==== Aska::StreamingStream::WorkerThread::Term()
// vaddr 0x1f7cd40 | ghidra 0x207cd40 | size 100 | symbol _ZN4Aska15StreamingStream12WorkerThread4TermEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska15StreamingStream12WorkerThread4TermEv(long param_1)

{
  if (((*(long *)(param_1 + 0x230) != 0) &&
      (*(undefined8 *)(param_1 + 0x230) = 0, *(char *)(param_1 + 0x80) != '\0')) &&
     (*(char *)(param_1 + 0x81) == '\0')) {
    *(undefined1 *)(param_1 + 0x81) = 1;
    Aska::Event::Set() const(param_1 + 0x18);
    Aska::Thread::WaitEnd()(param_1);
    Aska::Event::Exit()(param_1 + 0x18);
    Aska::Thread::Delete()(param_1);
    *(undefined1 *)(param_1 + 0x80) = 0;
  }
  return;
}

// ==== Aska::StreamingStream::LockRingBuffer(int, void**, unsigned long)
// vaddr 0x1f7cda4 | ghidra 0x207cda4 | size 348 | symbol _ZN4Aska15StreamingStream14LockRingBufferEiPPvm | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska15StreamingStream14LockRingBufferEiPPvm
               (long *param_1,int param_2,undefined8 param_3,ulong param_4)

{
  int *piVar1;
  char cVar2;
  bool bVar3;
  bool bVar4;
  int iVar5;
  long lVar6;
  ulong uVar7;
  
  if (param_4 == 0) {
    if (param_2 == 0) {
      param_4 = (long)(int)param_1[7] - (long)*(int *)((long)param_1 + 0x49c);
      goto code_r0x0207ce30;
    }
    lVar6 = param_1[4];
    param_4 = (lVar6 - (int)param_1[7]) - (long)(int)param_1[0x93];
  }
  else {
    if (param_2 == 0) {
code_r0x0207ce30:
      bVar3 = true;
      uVar7 = (long)(int)param_1[7] - (long)*(int *)((long)param_1 + 0x49c);
      goto code_r0x0207ce40;
    }
    lVar6 = param_1[4];
  }
  bVar3 = false;
  uVar7 = (lVar6 - (int)param_1[7]) - (long)(int)param_1[0x93];
code_r0x0207ce40:
  bVar4 = uVar7 != 0;
  if (param_4 != 0) {
    bVar4 = param_4 <= uVar7;
  }
  if (!bVar4) {
    if (bVar3) {
      param_4 = (long)(int)param_1[7] - (long)*(int *)((long)param_1 + 0x49c);
      (**(code **)(*param_1 + 0x48))(param_1,0xfffffffffffffc14);
    }
    else {
      param_4 = (param_1[4] - (long)(int)param_1[7]) - (long)(int)param_1[0x93];
      (**(code **)(*param_1 + 0x48))(param_1,0xfffffffffffffc15);
    }
  }
  if (param_4 == 0) {
    lVar6 = 0;
  }
  else {
    if (bVar3) {
      iVar5 = Aska::RingBuffer::PopBack(void**, unsigned long)();
    }
    else {
      iVar5 = Aska::RingBuffer::PushFront(void**, unsigned long)(param_1 + 1,param_3,param_4);
    }
    piVar1 = (int *)((long)param_1 + (long)param_2 * 4 + 0x498);
    do {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar3) {
        *piVar1 = *piVar1 + iVar5;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    lVar6 = (long)iVar5;
  }
  return lVar6;
}

// ==== Aska::StreamingStream::UnlockRingBuffer(int, unsigned long)
// vaddr 0x1f7cf00 | ghidra 0x207cf00 | size 128 | symbol _ZN4Aska15StreamingStream16UnlockRingBufferEim | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska15StreamingStream16UnlockRingBufferEim(long *param_1,int param_2,ulong param_3)

{
  int *piVar1;
  char cVar2;
  bool bVar3;
  long lVar4;
  
  piVar1 = (int *)((long)param_1 + (long)param_2 * 4 + 0x498);
  if (param_3 == 0) {
    param_3 = (ulong)*piVar1;
  }
  bVar3 = (long)*piVar1 != 0;
  if (param_3 != 0) {
    bVar3 = param_3 <= (ulong)(long)*piVar1;
  }
  if (!bVar3) {
    param_3 = (ulong)*piVar1;
    (**(code **)(*param_1 + 0x48))(param_1,0xfffffffffffffc15);
  }
  if (param_3 == 0) {
    lVar4 = 0;
  }
  else {
    do {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar3) {
        *piVar1 = *piVar1 - (int)param_3;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    lVar4 = (long)(int)param_3;
  }
  return lVar4;
}

// ==== Aska::StreamingStream::Streaming_LockFront(unsigned long)
// vaddr 0x1f7cf80 | ghidra 0x207cf80 | size 1060 | symbol _ZN4Aska15StreamingStream19Streaming_LockFrontEm | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska15StreamingStream19Streaming_LockFrontEm(long *param_1,ulong param_2)

{
  long *plVar1;
  int *piVar2;
  uint uVar3;
  char cVar4;
  bool bVar5;
  ulong uVar6;
  ulong uVar7;
  undefined8 uVar8;
  int iVar9;
  int iVar10;
  uint *puVar11;
  uint uVar12;
  uint uVar13;
  uint uVar14;
  uint uVar15;
  long lVar16;
  long lStack_58;
  
  uVar7 = param_1[0x91] - param_1[0x8f];
  if (param_2 <= (ulong)(param_1[0x91] - param_1[0x8f])) {
    uVar7 = param_2;
  }
  if ((((char)param_1[0x94] != '\0') || (uVar7 == 0)) || (*(char *)((long)param_1 + 0x4a1) != '\0'))
  {
    return -0x3eb;
  }
  plVar1 = param_1 + 0x7e;
  iVar9 = 0;
code_r0x0207cff0:
  do {
    if ((int)*plVar1 != -1) {
      ClearExclusiveLocal();
      bVar5 = iVar9 < 0x1ff;
      iVar9 = iVar9 + 1;
      if (bVar5) goto code_r0x0207cff0;
      piVar2 = (int *)((long)param_1 + 0x3f4);
      do {
        cVar4 = '\x01';
        bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
        if (bVar5) {
          *piVar2 = *piVar2 + 1;
          cVar4 = ExclusiveMonitorsStatus();
        }
      } while (cVar4 != '\0');
      do {
        if ((int)*plVar1 != -1) {
          ClearExclusiveLocal();
          do {
            uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x86);
            if ((uVar6 & 1) == 0) {
              do {
                cVar4 = '\x01';
                bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
                if (bVar5) {
                  *piVar2 = *piVar2 + -1;
                  cVar4 = ExclusiveMonitorsStatus();
                }
              } while (cVar4 != '\0');
              Aska::Thread::Sleep(unsigned int)(1);
            }
            else {
              Aska::Semaphore::Wait() const(param_1 + 0x86);
            }
            do {
              cVar4 = '\x01';
              bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
              if (bVar5) {
                *piVar2 = *piVar2 + 1;
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
              if (cVar4 == '\0') goto code_r0x0207d0a8;
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
code_r0x0207d0a8:
      do {
        cVar4 = '\x01';
        bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
        if (bVar5) {
          *piVar2 = *piVar2 + -1;
          cVar4 = ExclusiveMonitorsStatus();
        }
      } while (cVar4 != '\0');
code_r0x0207d0b8:
      DataMemoryBarrier(2,3);
      if ((ulong)((param_1[4] - (long)(int)param_1[7]) - (long)(int)param_1[0x93]) < uVar7) {
        lVar16 = -0x3eb;
        goto code_r0x0207d250;
      }
      lVar16 = Aska::StreamingStream::LockRingBuffer(int, void**, unsigned long)(param_1,1,&lStack_58,uVar7);
      if (lVar16 < 0) goto code_r0x0207d250;
      param_1[0x8f] = param_1[0x8f] + lVar16;
      DataMemoryBarrier(2,3);
      if (*(int *)((long)param_1 + 0x174) < 9) {
        uVar13 = *(uint *)(param_1 + 0x2e);
        piVar2 = (int *)((long)param_1 + 0x174);
        uVar12 = uVar13 + 0x1f;
        if (-1 < (int)uVar13) {
          uVar12 = uVar13;
        }
        puVar11 = (uint *)((long)param_1 + (long)((int)uVar12 >> 5) * 4 + 0x48);
        uVar12 = *puVar11;
        uVar15 = 1 << (ulong)(uVar13 & 0x1f);
        uVar14 = uVar15 | uVar12;
        while( true ) {
          uVar3 = 0;
          if ((int)uVar13 < 9) {
            uVar3 = uVar13;
          }
          if ((uVar15 & uVar12) == 0) break;
code_r0x0207d178:
          DataMemoryBarrier(2,3);
          if (8 < *piVar2) goto code_r0x0207d238;
          uVar13 = 0;
          if ((int)uVar3 < 8) {
            uVar13 = uVar3 + 1;
          }
          uVar12 = uVar13 + 0x1f;
          if (-1 < (int)uVar13) {
            uVar12 = uVar13;
          }
          puVar11 = (uint *)((long)param_1 + (long)((int)uVar12 >> 5) * 4 + 0x48);
          uVar12 = *puVar11;
          uVar15 = 1 << (ulong)(uVar13 & 0x1f);
          uVar14 = uVar12 | uVar15;
        }
        do {
          uVar13 = *puVar11;
          if (uVar13 != uVar12) {
            ClearExclusiveLocal();
            break;
          }
          cVar4 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(puVar11,0x10);
          if (bVar5) {
            *puVar11 = uVar14;
            cVar4 = ExclusiveMonitorsStatus();
          }
        } while (cVar4 != '\0');
        if ((uVar12 != uVar13) || (uVar12 == *puVar11)) goto code_r0x0207d178;
        do {
          cVar4 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
          if (bVar5) {
            *piVar2 = *piVar2 + 1;
            cVar4 = ExclusiveMonitorsStatus();
          }
        } while (cVar4 != '\0');
        DataMemoryBarrier(2,3);
        iVar9 = 0;
        if ((int)uVar3 < 8) {
          iVar9 = uVar3 + 1;
        }
        do {
          cVar4 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(param_1 + 0x2e,0x10);
          if (bVar5) {
            *(int *)(param_1 + 0x2e) = iVar9;
            cVar4 = ExclusiveMonitorsStatus();
          }
        } while (cVar4 != '\0');
        param_1[(long)(int)uVar3 * 4 + 0xb] = (long)param_1;
        param_1[(long)(int)uVar3 * 4 + 0xc] = 0;
        param_1[(long)(int)uVar3 * 4 + 0xd] = lVar16;
        plVar1 = param_1 + 0x75;
        do {
          if ((int)*plVar1 != 0) {
            ClearExclusiveLocal();
            uVar12 = 0;
            do {
              uVar12 = uVar12 + 1;
              if ((uVar12 & 0x1ff) == 0) {
                Aska::Thread::SleepU(unsigned int)(0);
              }
              while ((int)*plVar1 == 0) {
                cVar4 = '\x01';
                bVar5 = (bool)ExclusiveMonitorPass(plVar1,0x10);
                if (bVar5) {
                  *(int *)plVar1 = 1;
                  cVar4 = ExclusiveMonitorsStatus();
                }
                if (cVar4 == '\0') goto code_r0x0207d2d4;
              }
              ClearExclusiveLocal();
            } while( true );
          }
          cVar4 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(plVar1,0x10);
          if (bVar5) {
            *(int *)plVar1 = 1;
            cVar4 = ExclusiveMonitorsStatus();
          }
        } while (cVar4 != '\0');
code_r0x0207d2d4:
        uVar12 = *(uint *)(param_1 + 0x42);
        if (*(uint *)((long)param_1 + 0x214) != uVar12) {
          *(undefined4 *)(param_1 + (ulong)uVar12 * 5 + 0x44) = 2;
          param_1[(ulong)uVar12 * 5 + 0x46] = 1;
          iVar9 = 0;
          if (uVar12 + 1 < 10) {
            iVar9 = uVar12 + 1;
          }
          param_1[(ulong)uVar12 * 5 + 0x43] = (long)(param_1 + (long)(int)uVar3 * 4 + 10);
          param_1[(ulong)uVar12 * 5 + 0x45] = lVar16;
          param_1[(ulong)uVar12 * 5 + 0x47] = lStack_58;
          *(int *)(param_1 + 0x42) = iVar9;
          *(undefined4 *)(param_1 + 0x75) = 0;
          Aska::Event::Set() const(param_1 + 0x33);
          goto code_r0x0207d250;
        }
        uVar7 = (long)(param_1 + (long)(int)uVar3 * 4 + 10) - (long)(param_1 + 10);
        *(undefined4 *)(param_1 + 0x75) = 0;
        iVar10 = (int)(uVar7 >> 5);
        iVar9 = iVar10 + 0x1f;
        if (-1 < iVar10) {
          iVar9 = iVar10;
        }
        param_1[(long)(int)uVar3 * 4 + 0xc] = 0;
        param_1[(long)(int)uVar3 * 4 + 0xd] = 0;
        param_1[(long)(int)uVar3 * 4 + 0xb] = 0;
        puVar11 = (uint *)((long)param_1 + (long)(iVar9 >> 5) * 4 + 0x48);
        do {
          cVar4 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(puVar11,0x10);
          if (bVar5) {
            *puVar11 = *puVar11 & ~(1 << (uVar7 >> 5 & 0x1f));
            cVar4 = ExclusiveMonitorsStatus();
          }
        } while (cVar4 != '\0');
        do {
          cVar4 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
          if (bVar5) {
            *piVar2 = *piVar2 + -1;
            cVar4 = ExclusiveMonitorsStatus();
          }
        } while (cVar4 != '\0');
        DataMemoryBarrier(2,3);
        lVar16 = *param_1;
        uVar8 = 0xfffffffffffffc02;
      }
      else {
code_r0x0207d238:
        lVar16 = *param_1;
        uVar8 = 0xfffffffffffffc30;
      }
      lVar16 = (**(code **)(lVar16 + 0x48))(param_1,uVar8);
code_r0x0207d250:
      DataMemoryBarrier(2,3);
      *(undefined4 *)(param_1 + 0x7e) = 0xffffffff;
      DataMemoryBarrier(2,3);
      if (*(int *)((long)param_1 + 0x3f4) < 0x15) {
        return lVar16;
      }
      piVar2 = (int *)((long)param_1 + 0x3f4);
      do {
        cVar4 = '\x01';
        bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
        if (bVar5) {
          *piVar2 = *piVar2 + -1;
          cVar4 = ExclusiveMonitorsStatus();
        }
      } while (cVar4 != '\0');
      uVar7 = Aska::Semaphore::IsReady() const(param_1 + 0x86);
      if ((uVar7 & 1) != 0) {
        Aska::Semaphore::Signal() const(param_1 + 0x86);
        return lVar16;
      }
      return lVar16;
    }
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(plVar1,0x10);
    if (bVar5) {
      *(int *)plVar1 = 0;
      cVar4 = ExclusiveMonitorsStatus();
    }
    if (cVar4 == '\0') goto code_r0x0207d0b8;
  } while( true );
}

// ==== Aska::StreamingStream::IsBufferableRingBuffer(int, int, unsigned long, long*) const
// vaddr 0x1f7d3a4 | ghidra 0x207d3a4 | size 92 | symbol _ZNK4Aska15StreamingStream22IsBufferableRingBufferEiimPl | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK4Aska15StreamingStream22IsBufferableRingBufferEiimPl
               (long param_1,int param_2,int param_3,ulong param_4,undefined8 *param_5)

{
  bool bVar1;
  ulong uVar2;
  
  if (param_5 != (undefined8 *)0x0) {
    *param_5 = 0;
  }
  if (param_3 == 0) {
    if (param_2 == 0) {
      uVar2 = (long)*(int *)(param_1 + 0x38) - (long)*(int *)(param_1 + 0x49c);
    }
    else {
      uVar2 = (*(long *)(param_1 + 0x20) - (long)*(int *)(param_1 + 0x38)) -
              (long)*(int *)(param_1 + 0x498);
    }
  }
  else {
    uVar2 = (ulong)*(int *)(param_1 + (long)param_2 * 4 + 0x498);
  }
  bVar1 = uVar2 != 0;
  if (param_4 != 0) {
    bVar1 = param_4 <= uVar2;
  }
  return bVar1;
}

// ==== Aska::StreamingStream::CalcBufferableSize(int, int) const
// vaddr 0x1f7d400 | ghidra 0x207d400 | size 60 | symbol _ZNK4Aska15StreamingStream18CalcBufferableSizeEii | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK4Aska15StreamingStream18CalcBufferableSizeEii(long param_1,int param_2,int param_3)

{
  if (param_3 != 0) {
    return (long)*(int *)(param_1 + (long)param_2 * 4 + 0x498);
  }
  if (param_2 != 0) {
    return (*(long *)(param_1 + 0x20) - (long)*(int *)(param_1 + 0x38)) -
           (long)*(int *)(param_1 + 0x498);
  }
  return (long)*(int *)(param_1 + 0x38) - (long)*(int *)(param_1 + 0x49c);
}

// ==== Aska::StreamingStream::ClearBuffering(bool)
// vaddr 0x1f7d43c | ghidra 0x207d43c | size 260 | symbol _ZN4Aska15StreamingStream14ClearBufferingEb | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska15StreamingStream14ClearBufferingEb(long *param_1,ulong param_2)

{
  int iVar1;
  ulong uVar2;
  long lVar3;
  long lVar4;
  ulong uVar5;
  ulong uVar6;
  ulong uVar7;
  
  *(undefined1 *)(param_1 + 0x94) = 1;
  lVar3 = Aska::Global::GetCPUTime()();
  iVar1 = *(int *)((long)param_1 + 0x174);
  do {
    if (iVar1 == 0) {
code_r0x0207d4ac:
      Aska::RingBuffer::Reset()(param_1 + 1);
      *(undefined4 *)(param_1 + 0x93) = 0;
      *(undefined4 *)((long)param_1 + 0x49c) = 0;
      if ((param_2 & 1) != 0) {
        *(undefined1 *)(param_1 + 0x94) = 0;
        uVar5 = param_1[0x8a];
        uVar7 = (param_1[4] - (long)(int)param_1[7]) - (long)(int)param_1[0x93];
        if (uVar5 <= uVar7) {
          lVar3 = Aska::StreamingStream::Streaming_LockFront(unsigned long)(param_1,uVar5);
          if ((lVar3 < 0) && (lVar3 != -0x3eb)) {
            return lVar3;
          }
          uVar6 = 0;
          uVar2 = 0;
          if (uVar5 != 0) {
            uVar2 = uVar7 / uVar5;
          }
          while (uVar6 = uVar6 + 1, uVar6 < uVar2) {
            lVar3 = Aska::StreamingStream::Streaming_LockFront(unsigned long)(param_1,param_1[0x8a]);
            if ((lVar3 < 0) && (lVar3 != -0x3eb)) {
              return lVar3;
            }
          }
        }
      }
      return 0;
    }
    lVar4 = Aska::Global::GetCPUTime()();
    if ((ulong)param_1[0x8b] <= (ulong)(lVar4 - lVar3)) {
      *(undefined1 *)(param_1 + 0x94) = 0;
      lVar3 = (**(code **)(*param_1 + 0x48))(param_1,0xfffffffffffffc3a);
      if (lVar3 < 0) {
        return lVar3;
      }
      goto code_r0x0207d4ac;
    }
    Aska::Thread::Sleep(unsigned int)(1);
    iVar1 = *(int *)((long)param_1 + 0x174);
  } while( true );
}

// ==== Aska::StreamingStream::AcquireBufferingNotify(unsigned long)
// vaddr 0x1f7d540 | ghidra 0x207d540 | size 304 | symbol _ZN4Aska15StreamingStream22AcquireBufferingNotifyEm | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska15StreamingStream22AcquireBufferingNotifyEm(long param_1,undefined8 param_2)

{
  int *piVar1;
  long lVar2;
  uint uVar3;
  int iVar4;
  char cVar5;
  bool bVar6;
  uint *puVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  
  DataMemoryBarrier(2,3);
  if (8 < *(int *)(param_1 + 0x174)) {
    return 0;
  }
  uVar9 = *(uint *)(param_1 + 0x170);
  piVar1 = (int *)(param_1 + 0x174);
  uVar8 = uVar9 + 0x1f;
  if (-1 < (int)uVar9) {
    uVar8 = uVar9;
  }
  puVar7 = (uint *)(param_1 + (long)((int)uVar8 >> 5) * 4 + 0x48);
  uVar8 = *puVar7;
  uVar11 = 1 << (ulong)(uVar9 & 0x1f);
  uVar10 = uVar11 | uVar8;
  do {
    uVar3 = 0;
    if ((int)uVar9 < 9) {
      uVar3 = uVar9;
    }
    if ((uVar11 & uVar8) == 0) {
      do {
        uVar9 = *puVar7;
        if (uVar9 != uVar8) {
          ClearExclusiveLocal();
          if (uVar8 != uVar9) goto code_r0x0207d5bc;
          goto code_r0x0207d5b0;
        }
        cVar5 = '\x01';
        bVar6 = (bool)ExclusiveMonitorPass(puVar7,0x10);
        if (bVar6) {
          *puVar7 = uVar10;
          cVar5 = ExclusiveMonitorsStatus();
        }
      } while (cVar5 != '\0');
      if (uVar8 == uVar9) {
code_r0x0207d5b0:
        if (uVar8 != *puVar7) {
          do {
            cVar5 = '\x01';
            bVar6 = (bool)ExclusiveMonitorPass(piVar1,0x10);
            if (bVar6) {
              *piVar1 = *piVar1 + 1;
              cVar5 = ExclusiveMonitorsStatus();
            }
          } while (cVar5 != '\0');
          DataMemoryBarrier(2,3);
          iVar4 = 0;
          if ((int)uVar3 < 8) {
            iVar4 = uVar3 + 1;
          }
          do {
            cVar5 = '\x01';
            bVar6 = (bool)ExclusiveMonitorPass((int *)(param_1 + 0x170),0x10);
            if (bVar6) {
              *(int *)(param_1 + 0x170) = iVar4;
              cVar5 = ExclusiveMonitorsStatus();
            }
          } while (cVar5 != '\0');
          lVar2 = param_1 + (long)(int)uVar3 * 0x20;
          *(long *)(lVar2 + 0x58) = param_1;
          *(undefined8 *)(lVar2 + 0x60) = 0;
          *(undefined8 *)(lVar2 + 0x68) = param_2;
          return lVar2 + 0x50;
        }
      }
    }
code_r0x0207d5bc:
    DataMemoryBarrier(2,3);
    if (8 < *piVar1) {
      return 0;
    }
    uVar9 = 0;
    if ((int)uVar3 < 8) {
      uVar9 = uVar3 + 1;
    }
    uVar8 = uVar9 + 0x1f;
    if (-1 < (int)uVar9) {
      uVar8 = uVar9;
    }
    puVar7 = (uint *)(param_1 + (long)((int)uVar8 >> 5) * 4 + 0x48);
    uVar8 = *puVar7;
    uVar11 = 1 << (ulong)(uVar9 & 0x1f);
    uVar10 = uVar8 | uVar11;
  } while( true );
}

// ==== Aska::StreamingStream::ReleaseBufferingNotify(Aska::StreamingStream::BufferingNotify*)
// vaddr 0x1f7d670 | ghidra 0x207d670 | size 108 | symbol _ZN4Aska15StreamingStream22ReleaseBufferingNotifyEPNS0_15BufferingNotifyE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska15StreamingStream22ReleaseBufferingNotifyEPNS0_15BufferingNotifyE
               (long param_1,long param_2)

{
  int *piVar1;
  int iVar2;
  char cVar3;
  bool bVar4;
  int iVar5;
  uint *puVar6;
  ulong uVar7;
  
  uVar7 = param_2 - (param_1 + 0x50);
  iVar5 = (int)(uVar7 >> 5);
  iVar2 = iVar5 + 0x1f;
  if (-1 < iVar5) {
    iVar2 = iVar5;
  }
  *(undefined8 *)(param_2 + 0x10) = 0;
  *(undefined8 *)(param_2 + 0x18) = 0;
  *(undefined8 *)(param_2 + 8) = 0;
  puVar6 = (uint *)(param_1 + (long)(iVar2 >> 5) * 4 + 0x48);
  do {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(puVar6,0x10);
    if (bVar4) {
      *puVar6 = *puVar6 & ~(1 << (uVar7 >> 5 & 0x1f));
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
  piVar1 = (int *)(param_1 + 0x174);
  do {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar4) {
      *piVar1 = *piVar1 + -1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
  DataMemoryBarrier(2,3);
  return;
}

// ==== Aska::StreamingStream::Streaming_UnlockFront(Aska::StreamingStream::BufferingNotify*)
// vaddr 0x1f7d6dc | ghidra 0x207d6dc | size 208 | symbol _ZN4Aska15StreamingStream21Streaming_UnlockFrontEPNS0_15BufferingNotifyE | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska15StreamingStream21Streaming_UnlockFrontEPNS0_15BufferingNotifyE
               (long *param_1,long param_2)

{
  int *piVar1;
  char cVar2;
  bool bVar3;
  long lVar4;
  long lVar5;
  int iVar6;
  ulong uVar7;
  
  uVar7 = *(ulong *)(param_2 + 0x18);
  piVar1 = (int *)((long)param_1 + 0x49c);
  if (uVar7 == 0) {
    uVar7 = (ulong)*piVar1;
  }
  bVar3 = (long)*piVar1 != 0;
  if (uVar7 != 0) {
    bVar3 = uVar7 <= (ulong)(long)*piVar1;
  }
  if (!bVar3) {
    uVar7 = (ulong)*(int *)((long)param_1 + 0x49c);
    (**(code **)(*param_1 + 0x48))(param_1,0xfffffffffffffc15);
  }
  if (uVar7 == 0) {
    lVar5 = 0;
  }
  else {
    iVar6 = (int)uVar7;
    do {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar3) {
        *piVar1 = *piVar1 - iVar6;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    lVar5 = (long)iVar6;
    if (iVar6 < 0) goto code_r0x0207d77c;
  }
  if (((ulong)param_1[0x91] <= (ulong)param_1[0x8f]) && (*piVar1 == 0)) {
    *(undefined1 *)((long)param_1 + 0x4a1) = 1;
  }
code_r0x0207d77c:
  lVar4 = lVar5;
  if ((-1 < lVar5) &&
     (lVar4 = Aska::StreamingStream::Streaming_LockFront(unsigned long)(param_1,param_1[0x8a]), lVar4 == -0x3eb || -1 < lVar4)) {
    lVar4 = lVar5;
  }
  return lVar4;
}

// ==== Aska::StreamingStream::BufferingNotify::Handler(unsigned long)
// vaddr 0x1f7d7ac | ghidra 0x207d7ac | size 340 | symbol _ZN4Aska15StreamingStream15BufferingNotify7HandlerEm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska15StreamingStream15BufferingNotify7HandlerEm(long param_1,undefined8 *param_2)

{
  int *piVar1;
  char cVar2;
  bool bVar3;
  long lVar4;
  int iVar5;
  uint *puVar6;
  long *plVar7;
  int iVar8;
  ulong uVar9;
  
  plVar7 = *(long **)(param_1 + 8);
  uVar9 = *(ulong *)(param_1 + 0x18);
  piVar1 = (int *)((long)plVar7 + 0x49c);
  *(undefined8 *)(param_1 + 0x10) = *param_2;
  if (uVar9 == 0) {
    uVar9 = (ulong)*piVar1;
  }
  bVar3 = (long)*piVar1 != 0;
  if (uVar9 != 0) {
    bVar3 = uVar9 <= (ulong)(long)*piVar1;
  }
  if (!bVar3) {
    uVar9 = (ulong)*(int *)((long)plVar7 + 0x49c);
    (**(code **)(*plVar7 + 0x48))(plVar7,0xfffffffffffffc15);
  }
  if (uVar9 == 0) {
    lVar4 = 0;
  }
  else {
    iVar8 = (int)uVar9;
    do {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar3) {
        *piVar1 = *piVar1 - iVar8;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    lVar4 = (long)iVar8;
    if (iVar8 < 0) goto joined_r0x0207d8f8;
  }
  if (((ulong)plVar7[0x91] <= (ulong)plVar7[0x8f]) && (*piVar1 == 0)) {
    *(undefined1 *)((long)plVar7 + 0x4a1) = 1;
  }
joined_r0x0207d8f8:
  if ((lVar4 < 0) ||
     ((lVar4 = Aska::StreamingStream::Streaming_LockFront(unsigned long)(plVar7,plVar7[0x8a]), lVar4 < 0 && (lVar4 != -0x3eb)))) {
    *(long *)(param_1 + 0x10) = lVar4;
  }
  lVar4 = *(long *)(param_1 + 8);
  *(undefined8 *)(param_1 + 0x10) = 0;
  *(undefined8 *)(param_1 + 0x18) = 0;
  *(undefined8 *)(param_1 + 8) = 0;
  uVar9 = param_1 - (lVar4 + 0x50);
  iVar5 = (int)(uVar9 >> 5);
  iVar8 = iVar5 + 0x1f;
  if (-1 < iVar5) {
    iVar8 = iVar5;
  }
  puVar6 = (uint *)(lVar4 + (long)(iVar8 >> 5) * 4 + 0x48);
  do {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(puVar6,0x10);
    if (bVar3) {
      *puVar6 = *puVar6 & ~(1 << (uVar9 >> 5 & 0x1f));
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
  piVar1 = (int *)(lVar4 + 0x174);
  do {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar3) {
      *piVar1 = *piVar1 + -1;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
  DataMemoryBarrier(2,3);
  return;
}

// ==== Aska::StreamingStream::WorkerThread::Sequencer()
// vaddr 0x1f7d900 | ghidra 0x207d900 | size 312 | symbol _ZN4Aska15StreamingStream12WorkerThread9SequencerEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska15StreamingStream12WorkerThread9SequencerEv(long param_1)

{
  int *piVar1;
  int iVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  int iVar5;
  char cVar6;
  bool bVar7;
  long lVar8;
  undefined8 uVar9;
  long lVar10;
  uint uVar11;
  undefined8 *puVar12;
  long lStack_40;
  undefined8 uStack_38;
  
  piVar1 = (int *)(param_1 + 0x228);
  lVar10 = lStack_40;
  while (lStack_40 = lVar10, *piVar1 == 0) {
    cVar6 = '\x01';
    bVar7 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar7) {
      *piVar1 = 1;
      cVar6 = ExclusiveMonitorsStatus();
    }
    lVar10 = lStack_40;
    if (cVar6 == '\0') {
code_r0x0207d924:
      iVar2 = 0;
      if (*(int *)(param_1 + 0x94) + 1 < 10) {
        iVar2 = *(int *)(param_1 + 0x94) + 1;
      }
      if (iVar2 == *(int *)(param_1 + 0x90)) {
        *piVar1 = 0;
        return;
      }
      lVar10 = param_1 + (long)iVar2 * 0x28;
      iVar5 = *(int *)(lVar10 + 0xa0);
      puVar12 = *(undefined8 **)(lVar10 + 0x98);
      uVar3 = *(undefined8 *)(lVar10 + 0xa8);
      uVar4 = *(undefined8 *)(lVar10 + 0xb0);
      uVar9 = *(undefined8 *)(lVar10 + 0xb8);
      *(int *)(param_1 + 0x94) = iVar2;
      *(undefined4 *)(param_1 + 0x228) = 0;
      if (iVar5 == 2) {
        lVar8 = (**(code **)(**(long **)(param_1 + 0x230) + 0x28))
                          (*(long **)(param_1 + 0x230),uVar9,uVar4);
        lVar10 = lStack_40;
        if (lVar8 == 0) {
          lVar8 = (**(code **)(**(long **)(param_1 + 0x230) + 0x58))();
          lVar10 = lStack_40;
        }
      }
      else {
        if (iVar5 != 1) {
          return;
        }
        lVar8 = (**(code **)(**(long **)(param_1 + 0x230) + 0x20))
                          (*(long **)(param_1 + 0x230),uVar3);
        lVar10 = lStack_40;
      }
      lStack_40 = lVar8;
      if (puVar12 != (undefined8 *)0x0) {
        uStack_38 = 0;
        (**(code **)*puVar12)(puVar12,&lStack_40);
        lVar10 = lStack_40;
      }
    }
  }
  ClearExclusiveLocal();
  uVar11 = 0;
  do {
    uVar11 = uVar11 + 1;
    if ((uVar11 & 0x1ff) == 0) {
      Aska::Thread::SleepU(unsigned int)(0);
    }
    while (*piVar1 == 0) {
      cVar6 = '\x01';
      bVar7 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar7) {
        *piVar1 = 1;
        cVar6 = ExclusiveMonitorsStatus();
      }
      if (cVar6 == '\0') goto code_r0x0207d924;
    }
    ClearExclusiveLocal();
  } while( true );
}

// ==== Aska::StreamingStream::~StreamingStream()
// vaddr 0x1f7da38 | ghidra 0x207da38 | size 24 | symbol _ZN4Aska15StreamingStreamD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska15StreamingStreamD0Ev(undefined8 param_1)

{
  Aska::StreamingStream::~StreamingStream()();
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::StreamingStream::IsReady() const
// vaddr 0x1f7da50 | ghidra 0x207da50 | size 32 | symbol _ZNK4Aska15StreamingStream7IsReadyEv | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK4Aska15StreamingStream7IsReadyEv(long param_1)

{
  if (*(long *)(param_1 + 0x18) != 0) {
    return *(long *)(param_1 + 0x3b0) != 0;
  }
  return false;
}

// ==== Aska::StreamingStream::IsAsync() const
// vaddr 0x1f7da70 | ghidra 0x207da70 | size 8 | symbol _ZNK4Aska15StreamingStream7IsAsyncEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska15StreamingStream7IsAsyncEv(void)

{
  return 0;
}

// ==== Aska::StreamingStream::IsBusy() const
// vaddr 0x1f7da78 | ghidra 0x207da78 | size 8 | symbol _ZNK4Aska15StreamingStream6IsBusyEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska15StreamingStream6IsBusyEv(void)

{
  return 0;
}

// ==== Aska::StreamingStream::Wait(int) const
// vaddr 0x1f7da80 | ghidra 0x207da80 | size 8 | symbol _ZNK4Aska15StreamingStream4WaitEi | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska15StreamingStream4WaitEi(void)

{
  return 0;
}

// ==== Aska::StreamingStream::Cancel(unsigned long)
// vaddr 0x1f7da88 | ghidra 0x207da88 | size 8 | symbol _ZN4Aska15StreamingStream6CancelEm | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska15StreamingStream6CancelEm(void)

{
  return 0;
}

// ==== Aska::StreamingStream::ReadAsync(void*, long, unsigned long, unsigned long, Aska::INotify*, long volatile*)
// vaddr 0x1f7da90 | ghidra 0x207da90 | size 248 | symbol _ZN4Aska15StreamingStream9ReadAsyncEPvlmmPNS_7INotifyEPVl | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZN4Aska15StreamingStream9ReadAsyncEPvlmmPNS_7INotifyEPVl
                (long *param_1,undefined8 param_2,undefined8 param_3,long param_4,ulong param_5,
                undefined8 *param_6,ulong *param_7)

{
  ulong uVar1;
  ulong uVar2;
  ulong uStack_50;
  undefined8 uStack_48;
  
  uStack_50 = 0;
  uStack_48 = 0;
  uVar1 = (**(code **)(*param_1 + 0x20))(param_1,param_3,0);
  if ((long)uVar1 < 0) {
    uStack_50 = uVar1;
    if (param_7 != (ulong *)0x0) {
      *param_7 = uVar1;
    }
  }
  else {
    uVar2 = (**(code **)(*param_1 + 0x28))(param_1,param_2,param_4,param_5);
    if (uVar2 == param_5) {
      if (param_7 != (ulong *)0x0) {
        *param_7 = param_5;
      }
      uStack_50 = param_5 * param_4;
    }
    else {
      uVar1 = (**(code **)(*param_1 + 0x58))(param_1);
      uStack_50 = uVar1;
      if (param_7 != (ulong *)0x0) {
        *param_7 = uVar1;
      }
    }
  }
  if (param_6 != (undefined8 *)0x0) {
    (**(code **)*param_6)(param_6,&uStack_50);
  }
  return uVar1 >> 0x3f ^ 1;
}

// ==== Aska::StreamingStream::WriteAsync(void const*, long, unsigned long, unsigned long, Aska::INotify*, long volatile*)
// vaddr 0x1f7db88 | ghidra 0x207db88 | size 224 | symbol _ZN4Aska15StreamingStream10WriteAsyncEPKvlmmPNS_7INotifyEPVl | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZN4Aska15StreamingStream10WriteAsyncEPKvlmmPNS_7INotifyEPVl
                (long *param_1,undefined8 param_2,undefined8 param_3,long param_4,ulong param_5,
                undefined8 *param_6,ulong *param_7)

{
  ulong uVar1;
  ulong uVar2;
  ulong uStack_50;
  undefined8 uStack_48;
  
  uStack_50 = 0;
  uStack_48 = 0;
  uVar1 = (**(code **)(*param_1 + 0x20))(param_1,param_3,0);
  if (-1 < (long)uVar1) {
    uVar2 = (**(code **)(*param_1 + 0x30))(param_1,param_2,param_4,param_5);
    if (uVar2 == param_5) {
      uStack_50 = param_5 * param_4;
      if (param_7 != (ulong *)0x0) {
        *param_7 = param_5;
      }
      goto joined_r0x0207dc30;
    }
    uVar1 = (**(code **)(*param_1 + 0x58))(param_1);
  }
  uStack_50 = uVar1;
  if (param_7 != (ulong *)0x0) {
    *param_7 = uVar1;
  }
joined_r0x0207dc30:
  if (param_6 != (undefined8 *)0x0) {
    (**(code **)*param_6)(param_6,&uStack_50);
  }
  return uVar1 >> 0x3f ^ 1;
}

// ==== Aska::StreamingStream::IsBufferingReady() const
// vaddr 0x1f7dc68 | ghidra 0x207dc68 | size 12 | symbol _ZNK4Aska15StreamingStream16IsBufferingReadyEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK4Aska15StreamingStream16IsBufferingReadyEv(long *param_1)

{
                    /* WARNING: Could not recover jumptable at 0x0207dc70. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*param_1 + 0x10))();
  return;
}

// ==== Aska::StreamingStream::BufferingNotify::~BufferingNotify()
// vaddr 0x1f7dc74 | ghidra 0x207dc74 | size 4 | symbol _ZN4Aska15StreamingStream15BufferingNotifyD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska15StreamingStream15BufferingNotifyD0Ev(void)

{
  (*(code *)PTR__ZdlPv_02ca4758)();
  return;
}

// ==== Aska::DiscReadStream::Open(int, unsigned int, unsigned long)
// vaddr 0x222627c | ghidra 0x232627c | size 120 | symbol _ZN4Aska14DiscReadStream4OpenEijm | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska14DiscReadStream4OpenEijm(long param_1,int param_2,int param_3,ulong param_4)

{
  undefined8 uVar1;
  ulong uVar2;
  
  uVar1 = 0;
  if ((((0 < param_2) && (*(long *)(param_1 + 0x158) == 0)) && (uVar1 = 0, param_3 != 0)) &&
     ((param_4 != 0 && ((param_4 & 0x1ff) == 0)))) {
    *(undefined4 *)(param_1 + 0x30) = 0;
    *(undefined8 *)(param_1 + 0x38) = 0;
    *(undefined8 *)(param_1 + 0x40) = 0;
    *(ulong *)(param_1 + 0x48) = param_4;
    uVar2 = Aska::TPoolAtomicDynamic<Aska::DiscReadStream::ReadAsyncNotify>::SecurePool(int)(param_1 + 8,param_3);
    uVar1 = 0;
    if ((uVar2 & 1) != 0) {
      uVar1 = 1;
      *(undefined1 *)(param_1 + 0x160) = 0;
      *(long *)(param_1 + 0x158) = (long)param_2;
    }
  }
  return uVar1;
}

// ==== Aska::DiscReadStream::OpenCommon(unsigned int, unsigned long)
// vaddr 0x22262f4 | ghidra 0x23262f4 | size 48 | symbol _ZN4Aska14DiscReadStream10OpenCommonEjm | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska14DiscReadStream10OpenCommonEjm(long param_1,int param_2,ulong param_3)

{
  undefined8 uVar1;
  
  if (((param_2 != 0) && (param_3 != 0)) && ((param_3 & 0x1ff) == 0)) {
    *(undefined4 *)(param_1 + 0x30) = 0;
    *(undefined8 *)(param_1 + 0x38) = 0;
    *(undefined8 *)(param_1 + 0x40) = 0;
    *(ulong *)(param_1 + 0x48) = param_3;
    uVar1 = (*(code *)
              PTR__ZN4Aska18TPoolAtomicDynamicINS_14DiscReadStream15ReadAsyncNotifyEE10SecurePoolEi_02c9b920
            )(param_1 + 8);
    return uVar1;
  }
  return 0;
}

// ==== Aska::DiscReadStream::Open(char const*, unsigned int, unsigned long, bool)
// vaddr 0x2226324 | ghidra 0x2326324 | size 208 | symbol _ZN4Aska14DiscReadStream4OpenEPKcjmb | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska14DiscReadStream4OpenEPKcjmb
          (long param_1,long param_2,int param_3,ulong param_4,byte param_5)

{
  undefined8 uVar1;
  ulong uVar2;
  
  uVar1 = 0;
  if ((param_2 != 0) && (*(long *)(param_1 + 0x158) == 0)) {
    uVar2 = strlen(param_2);
    if (uVar2 < 0x104) {
      uVar1 = 0;
      if (((param_3 != 0) && (param_4 != 0)) && ((param_4 & 0x1ff) == 0)) {
        *(undefined4 *)(param_1 + 0x30) = 0;
        *(undefined8 *)(param_1 + 0x38) = 0;
        *(undefined8 *)(param_1 + 0x40) = 0;
        *(ulong *)(param_1 + 0x48) = param_4;
        uVar2 = Aska::TPoolAtomicDynamic<Aska::DiscReadStream::ReadAsyncNotify>::SecurePool(int)(param_1 + 8,param_3);
        uVar1 = 0;
        if ((uVar2 & 1) != 0) {
          uVar2 = strlen(param_2);
          if (uVar2 < 0x104) {
            strcpy(param_1 + 0x50,param_2);
          }
          else {
            raise(5);
          }
          uVar1 = 1;
          *(long *)(param_1 + 0x158) = param_1 + 0x50;
          *(undefined1 *)(param_1 + 0x160) = 1;
          *(byte *)(param_1 + 0x161) = param_5 & 1;
        }
      }
    }
    else {
      uVar1 = 0;
    }
  }
  return uVar1;
}

// ==== Aska::DiscReadStream::Close()
// vaddr 0x22263f4 | ghidra 0x23263f4 | size 256 | symbol _ZN4Aska14DiscReadStream5CloseEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska14DiscReadStream5CloseEv(long *param_1)

{
  long lVar1;
  long lVar2;
  
  if (param_1[0x2b] == 0) {
    return;
  }
  (**(code **)(*param_1 + 0x80))(param_1,0);
  (**(code **)(*param_1 + 0x78))(param_1,0xffffffff);
  if ((*(char *)((long)param_1 + 0x29) == '\0') || ((char)param_1[5] == '\0'))
  goto code_r0x023264bc;
  if (param_1[3] != 0) {
    operator delete[](void*)();
    param_1[3] = 0;
  }
  if ((long *)param_1[2] == (long *)0x0) goto code_r0x023264bc;
  if (*(int *)((long)param_1 + 0x2c) < 1) {
code_r0x023264b4:
    operator delete[](void*)();
  }
  else {
    (**(code **)(*(long *)param_1[2] + 8))();
    if (1 < *(int *)((long)param_1 + 0x2c)) {
      lVar1 = 1;
      lVar2 = 0x50;
      do {
        (**(code **)(*(long *)(param_1[2] + lVar2) + 8))();
        lVar1 = lVar1 + 1;
        lVar2 = lVar2 + 0x50;
      } while (lVar1 < *(int *)((long)param_1 + 0x2c));
    }
    if (param_1[2] != 0) goto code_r0x023264b4;
  }
  param_1[2] = 0;
code_r0x023264bc:
  *(undefined2 *)(param_1 + 5) = 0;
  *(undefined4 *)((long)param_1 + 0x2c) = 0;
  *(undefined4 *)((long)param_1 + 0x24) = 0;
  *(undefined4 *)(param_1 + 4) = 0;
  *(undefined4 *)(param_1 + 4) = 0;
  if (param_1[8] != 0) {
    operator delete[](void*)();
    param_1[8] = 0;
  }
  param_1[0x2b] = 0;
  *(undefined2 *)(param_1 + 0x2c) = 0;
  return;
}

// ==== Aska::DiscReadStream::ReadAsync(void*, long, unsigned long, unsigned long, Aska::INotify*, long volatile*)
// vaddr 0x22264f4 | ghidra 0x23264f4 | size 476 | symbol _ZN4Aska14DiscReadStream9ReadAsyncEPvlmmPNS_7INotifyEPVl | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska14DiscReadStream9ReadAsyncEPvlmmPNS_7INotifyEPVl
          (long *param_1,long param_2,ulong param_3,long param_4,long param_5,undefined8 param_6,
          undefined8 *param_7)

{
  long lVar1;
  ulong uVar2;
  long lVar3;
  long lVar4;
  undefined8 uVar5;
  ulong uVar6;
  undefined8 uVar7;
  ulong uVar8;
  
  uVar2 = (**(code **)(*param_1 + 0x10))();
  if ((uVar2 & 1) == 0) {
    lVar3 = *param_1;
    uVar5 = 0xfffffffffffffc44;
    uVar7 = 0xfffffffffffffc44;
  }
  else {
    uVar8 = param_5 * param_4;
    uVar2 = uVar8;
    uVar6 = param_3;
    if ((param_3 & 0x1ff) != 0) {
      uVar6 = param_3 & 0xfffffffffffffe00;
      uVar2 = (param_3 - uVar6) + uVar8;
    }
    if ((uVar2 & 0x1ff) != 0) {
      uVar2 = uVar2 + 0x1ff & 0xfffffffffffffe00;
    }
    lVar3 = Aska::DiscReadStream::AcquireReadAsyncNotify(Aska::INotify*)(param_1,param_6);
    if (lVar3 != 0) {
      if ((uVar6 != param_3) || (uVar2 != uVar8)) {
        lVar4 = param_1[8];
        lVar1 = param_1[9];
        if (lVar4 == 0) {
          lVar4 = operator new[](unsigned long, std::nothrow_t const&)(lVar1,PTR__ZSt7nothrow_02cb9a80);
          param_1[8] = lVar4;
          if (lVar4 == 0) goto code_r0x02326620;
        }
        *(undefined8 *)(lVar3 + 0x18) = 0;
        *(long *)(lVar3 + 0x20) = param_2;
        *(ulong *)(lVar3 + 0x28) = uVar8;
        *(long *)(lVar3 + 0x30) = lVar4;
        *(long *)(lVar3 + 0x38) = lVar1;
        *(ulong *)(lVar3 + 0x40) = param_3;
        *(ulong *)(lVar3 + 0x48) = uVar6;
        param_2 = param_1[8];
        uVar8 = param_1[9];
        if (uVar2 <= (ulong)param_1[9]) {
          uVar8 = uVar2;
        }
      }
      if ((char)param_1[0x2c] == '\0') {
        uVar2 = Aska::FileReadManager::Read(int, unsigned char*, Aska::INotify*, unsigned long, unsigned long, int, int, bool)(*(undefined8 *)PTR__ZN4Aska6Global18m_pFileReadManagerE_02cbf970,
                                (int)param_1[0x2b],param_2,lVar3,uVar8,uVar6,0,0,1);
      }
      else {
        uVar2 = Aska::FileReadManager::Read(char const*, unsigned char*, Aska::INotify*, unsigned long, unsigned long, int, int, bool, bool)(*(undefined8 *)PTR__ZN4Aska6Global18m_pFileReadManagerE_02cbf970,
                                param_1[0x2b],param_2,lVar3,uVar8,uVar6,0,0,0,
                                *(undefined1 *)((long)param_1 + 0x161));
      }
      if ((uVar2 & 1) != 0) {
        (**(code **)(*param_1 + 0x48))(param_1,0xfffffffffffffc39);
        if (param_7 != (undefined8 *)0x0) {
          *param_7 = 0xfffffffffffffc39;
        }
        return 1;
      }
      uVar7 = 0xffffffffffffffff;
      (**(code **)(*param_1 + 0x48))(param_1,0xffffffffffffffff);
      goto joined_r0x02326638;
    }
code_r0x02326620:
    lVar3 = *param_1;
    uVar5 = 0xfffffffffffffc41;
    uVar7 = 0xfffffffffffffc41;
  }
  (**(code **)(lVar3 + 0x48))(param_1,uVar5);
joined_r0x02326638:
  if (param_7 != (undefined8 *)0x0) {
    *param_7 = uVar7;
  }
  return 0;
}

// ==== Aska::DiscReadStream::AcquireReadAsyncNotify(Aska::INotify*)
// vaddr 0x22266d0 | ghidra 0x23266d0 | size 356 | symbol _ZN4Aska14DiscReadStream22AcquireReadAsyncNotifyEPNS_7INotifyE | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska14DiscReadStream22AcquireReadAsyncNotifyEPNS_7INotifyE(long param_1,undefined8 param_2)

{
  uint uVar1;
  char cVar2;
  bool bVar3;
  uint *puVar4;
  long lVar5;
  int *piVar6;
  long lVar7;
  int iVar8;
  uint uVar9;
  uint *puVar10;
  uint uVar11;
  uint uVar12;
  
  DataMemoryBarrier(2,3);
  piVar6 = (int *)(param_1 + 0x24);
  iVar8 = *(int *)(param_1 + 0x2c);
  if (iVar8 <= *piVar6) {
    return 0;
  }
  puVar4 = (uint *)(param_1 + 0x20);
  uVar9 = *puVar4;
  uVar11 = uVar9 + 0x1f;
  if (-1 < (int)uVar9) {
    uVar11 = uVar9;
  }
  puVar10 = (uint *)(*(long *)(param_1 + 0x18) + (long)((int)uVar11 >> 5) * 4);
  uVar11 = *puVar10;
  do {
    uVar12 = 1 << (ulong)(uVar9 & 0x1f);
    if (iVar8 <= (int)uVar9) {
      uVar9 = 0;
    }
    if ((uVar12 & uVar11) == 0) {
      do {
        uVar1 = *puVar10;
        if (uVar1 != uVar11) {
          ClearExclusiveLocal();
          if (uVar11 != uVar1) goto code_r0x02326740;
          goto code_r0x02326734;
        }
        cVar2 = '\x01';
        bVar3 = (bool)ExclusiveMonitorPass(puVar10,0x10);
        if (bVar3) {
          *puVar10 = uVar11 | uVar12;
          cVar2 = ExclusiveMonitorsStatus();
        }
      } while (cVar2 != '\0');
      if (uVar11 == uVar1) {
code_r0x02326734:
        if (uVar11 != *puVar10) {
          do {
            cVar2 = '\x01';
            bVar3 = (bool)ExclusiveMonitorPass(piVar6,0x10);
            if (bVar3) {
              *piVar6 = *piVar6 + 1;
              cVar2 = ExclusiveMonitorsStatus();
            }
          } while (cVar2 != '\0');
          DataMemoryBarrier(2,3);
          uVar11 = 0;
          if ((int)(uVar9 + 1) < *(int *)(param_1 + 0x2c)) {
            uVar11 = uVar9 + 1;
          }
          do {
            cVar2 = '\x01';
            bVar3 = (bool)ExclusiveMonitorPass(puVar4,0x10);
            if (bVar3) {
              *puVar4 = uVar11;
              cVar2 = ExclusiveMonitorsStatus();
            }
          } while (cVar2 != '\0');
          lVar5 = *(long *)(param_1 + 0x10) + (long)(int)uVar9 * 0x50;
          if (lVar5 != 0) {
            lVar7 = *(long *)(param_1 + 0x10) + (long)(int)uVar9 * 0x50;
            *(long *)(lVar7 + 8) = param_1;
            *(undefined8 *)(lVar7 + 0x10) = param_2;
            *(undefined8 *)(lVar7 + 0x48) = 0;
            *(undefined8 *)(lVar7 + 0x40) = 0;
            *(undefined8 *)(lVar7 + 0x38) = 0;
            *(undefined8 *)(lVar7 + 0x30) = 0;
            *(undefined8 *)(lVar7 + 0x28) = 0;
            *(undefined8 *)(lVar7 + 0x20) = 0;
            *(undefined8 *)(lVar7 + 0x18) = 0;
          }
          return lVar5;
        }
      }
    }
code_r0x02326740:
    DataMemoryBarrier(2,3);
    iVar8 = *(int *)(param_1 + 0x2c);
    if (iVar8 <= *(int *)(param_1 + 0x24)) {
      return 0;
    }
    uVar12 = 0;
    if ((int)(uVar9 + 1) < iVar8) {
      uVar12 = uVar9 + 1;
    }
    uVar11 = uVar12 + 0x1f;
    if (-1 < (int)uVar12) {
      uVar11 = uVar12;
    }
    puVar10 = (uint *)(*(long *)(param_1 + 0x18) + (long)((int)uVar11 >> 5) * 4);
    uVar11 = *puVar10;
    uVar9 = uVar12;
  } while( true );
}

// ==== Aska::DiscReadStream::ReadAsyncNotify::SetStreaming(unsigned char*, unsigned long, unsigned char*, unsigned long, unsigned long, unsigned long)
// vaddr 0x2226834 | ghidra 0x2326834 | size 20 | symbol _ZN4Aska14DiscReadStream15ReadAsyncNotify12SetStreamingEPhmS2_mmm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska14DiscReadStream15ReadAsyncNotify12SetStreamingEPhmS2_mmm
               (long param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               undefined8 param_5,undefined8 param_6,undefined8 param_7)

{
  *(undefined8 *)(param_1 + 0x18) = 0;
  *(undefined8 *)(param_1 + 0x20) = param_2;
  *(undefined8 *)(param_1 + 0x28) = param_3;
  *(undefined8 *)(param_1 + 0x30) = param_4;
  *(undefined8 *)(param_1 + 0x38) = param_5;
  *(undefined8 *)(param_1 + 0x40) = param_6;
  *(undefined8 *)(param_1 + 0x48) = param_7;
  return;
}

// ==== Aska::DiscReadStream::Read_(unsigned char*, Aska::INotify*, unsigned long, unsigned long)
// vaddr 0x2226848 | ghidra 0x2326848 | size 152 | symbol _ZN4Aska14DiscReadStream5Read_EPhPNS_7INotifyEmm | lib libSOA-3.7.0.so | 2026-10-04
uint _ZN4Aska14DiscReadStream5Read_EPhPNS_7INotifyEmm
               (long param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               undefined8 param_5)

{
  uint uVar1;
  
  if (*(char *)(param_1 + 0x160) == '\0') {
    uVar1 = Aska::FileReadManager::Read(int, unsigned char*, Aska::INotify*, unsigned long, unsigned long, int, int, bool)(*(undefined8 *)PTR__ZN4Aska6Global18m_pFileReadManagerE_02cbf970,
                            *(undefined4 *)(param_1 + 0x158),param_2,param_3,param_4,param_5,0,0,1);
  }
  else {
    uVar1 = Aska::FileReadManager::Read(char const*, unsigned char*, Aska::INotify*, unsigned long, unsigned long, int, int, bool, bool)(*(undefined8 *)PTR__ZN4Aska6Global18m_pFileReadManagerE_02cbf970,
                            *(undefined8 *)(param_1 + 0x158),param_2,param_3,param_4,param_5,0,0,0,
                            *(undefined1 *)(param_1 + 0x161));
  }
  return uVar1 & 1;
}

// ==== Aska::DiscReadStream::Wait(int) const
// vaddr 0x22268e0 | ghidra 0x23268e0 | size 192 | symbol _ZNK4Aska14DiscReadStream4WaitEi | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska14DiscReadStream4WaitEi(long *param_1,int param_2)

{
  ulong uVar1;
  undefined8 uVar2;
  long lVar3;
  int iVar4;
  
  uVar1 = (**(code **)(*param_1 + 0x10))();
  if ((uVar1 & 1) == 0) {
    lVar3 = *param_1;
    uVar2 = 0xfffffffffffffc44;
code_r0x02326980:
                    /* WARNING: Could not recover jumptable at 0x02326990. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar2 = (**(code **)(lVar3 + 0x48))(param_1,uVar2);
    return uVar2;
  }
  uVar1 = (**(code **)(*param_1 + 0x70))(param_1);
  if ((uVar1 & 1) != 0) {
    if (param_2 < 0) {
      do {
        Aska::Thread::SleepU(unsigned int)(100);
        uVar1 = (**(code **)(*param_1 + 0x70))(param_1);
      } while ((uVar1 & 1) != 0);
    }
    else {
      iVar4 = param_2 * 1000 + 100;
      do {
        iVar4 = iVar4 + -100;
        if (iVar4 < 0) {
          lVar3 = *param_1;
          uVar2 = 0xfffffffffffffc3a;
          goto code_r0x02326980;
        }
        Aska::Thread::SleepU(unsigned int)(100);
        uVar1 = (**(code **)(*param_1 + 0x70))(param_1);
      } while ((uVar1 & 1) != 0);
    }
  }
  return 0;
}

// ==== Aska::DiscReadStream::Cancel(unsigned long)
// vaddr 0x22269a0 | ghidra 0x23269a0 | size 152 | symbol _ZN4Aska14DiscReadStream6CancelEm | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska14DiscReadStream6CancelEm(long *param_1,long param_2)

{
  ulong uVar1;
  undefined8 uVar2;
  long lVar3;
  
  uVar1 = (**(code **)(*param_1 + 0x10))();
  if ((uVar1 & 1) == 0) {
    lVar3 = *param_1;
    uVar2 = 0xfffffffffffffc44;
code_r0x023269f4:
                    /* WARNING: Could not recover jumptable at 0x02326a04. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar2 = (**(code **)(lVar3 + 0x48))(param_1,uVar2);
    return uVar2;
  }
  if (param_2 == 0) {
    uVar1 = (**(code **)(*param_1 + 0x70))(param_1);
    if ((uVar1 & 1) != 0) {
      lVar3 = *param_1;
      uVar2 = 0xfffffffffffffc46;
      goto code_r0x023269f4;
    }
  }
  else {
    Aska::FileReadManager::CancelByParam(int, unsigned char*, unsigned long, unsigned long, int)(*(undefined8 *)PTR__ZN4Aska6Global18m_pFileReadManagerE_02cbf970,0,param_2,0,0,
                    0xffffffff);
  }
  return 0;
}

// ==== Aska::DiscReadStream::IsEnd(long*) const
// vaddr 0x2226a38 | ghidra 0x2326a38 | size 128 | symbol _ZNK4Aska14DiscReadStream5IsEndEPl | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK4Aska14DiscReadStream5IsEndEPl(long *param_1,undefined8 *param_2)

{
  bool bVar1;
  ulong uVar2;
  long lVar3;
  long lVar4;
  
  uVar2 = (**(code **)(*param_1 + 0x10))();
  if ((uVar2 & 1) == 0) {
    if (param_2 != (undefined8 *)0x0) {
      *param_2 = 0xfffffffffffffc44;
    }
    bVar1 = true;
  }
  else {
    if (param_2 != (undefined8 *)0x0) {
      *param_2 = 0;
    }
    lVar4 = param_1[7];
    if ((char)param_1[0x2c] == '\0') {
      lVar3 = Aska::FileReadManager::CalcFileLength(int) const(*(undefined8 *)PTR__ZN4Aska6Global18m_pFileReadManagerE_02cbf970,
                              (int)param_1[0x2b]);
    }
    else {
      lVar3 = Aska::FileReadManager::CalcFileLength(char const*, bool)(param_1[0x2b],*(undefined1 *)((long)param_1 + 0x161));
    }
    bVar1 = lVar3 <= lVar4;
  }
  return bVar1;
}

// ==== Aska::DiscReadStream::CalcFileLength_()
// vaddr 0x2226ab8 | ghidra 0x2326ab8 | size 48 | symbol _ZN4Aska14DiscReadStream15CalcFileLength_Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska14DiscReadStream15CalcFileLength_Ev(long param_1)

{
  if (*(char *)(param_1 + 0x160) != '\0') {
    (*(code *)PTR__ZN4Aska15FileReadManager14CalcFileLengthEPKcb_02c9dce8)
              (*(undefined8 *)(param_1 + 0x158),*(undefined1 *)(param_1 + 0x161));
    return;
  }
  (*(code *)PTR__ZNK4Aska15FileReadManager14CalcFileLengthEi_02c93418)
            (*(undefined8 *)PTR__ZN4Aska6Global18m_pFileReadManagerE_02cbf970,
             *(undefined4 *)(param_1 + 0x158));
  return;
}

// ==== Aska::DiscReadStream::Seek(long, int)
// vaddr 0x2226ae8 | ghidra 0x2326ae8 | size 300 | symbol _ZN4Aska14DiscReadStream4SeekEli | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska14DiscReadStream4SeekEli(long *param_1,ulong param_2,int param_3)

{
  ulong uVar1;
  undefined8 uVar2;
  long lVar3;
  
  uVar1 = (**(code **)(*param_1 + 0x10))();
  if ((uVar1 & 1) == 0) {
    lVar3 = *param_1;
    uVar2 = 0xfffffffffffffc44;
  }
  else {
    uVar1 = (**(code **)(*param_1 + 0x70))(param_1);
    if ((uVar1 & 1) == 0) {
      if ((char)param_1[0x2c] == '\0') {
        uVar1 = Aska::FileReadManager::CalcFileLength(int) const(*(undefined8 *)PTR__ZN4Aska6Global18m_pFileReadManagerE_02cbf970,
                                (int)param_1[0x2b]);
      }
      else {
        uVar1 = Aska::FileReadManager::CalcFileLength(char const*, bool)(param_1[0x2b],*(undefined1 *)((long)param_1 + 0x161));
      }
      if (param_3 != 0) {
        if (param_3 == 2) {
          param_2 = uVar1 + param_2;
        }
        else {
          if (param_3 != 1) {
            lVar3 = *param_1;
            uVar2 = 0xfffffffffffffc43;
            goto code_r0x02326b38;
          }
          param_2 = param_1[7] + param_2;
        }
      }
      if ((long)param_2 < 0) {
        uVar2 = (**(code **)(*param_1 + 0x48))(param_1,0xfffffffffffffc3f);
        param_2 = 0;
      }
      else if (uVar1 < param_2) {
        uVar2 = (**(code **)(*param_1 + 0x48))(param_1,0xfffffffffffffc3f);
        param_2 = uVar1;
      }
      else {
        uVar2 = 0;
      }
      param_1[7] = param_2;
      return uVar2;
    }
    lVar3 = *param_1;
    uVar2 = 0xfffffffffffffc3c;
  }
code_r0x02326b38:
                    /* WARNING: Could not recover jumptable at 0x02326b4c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  uVar2 = (**(code **)(lVar3 + 0x48))(param_1,uVar2);
  return uVar2;
}

// ==== Aska::DiscReadStream::Read(void*, unsigned long, unsigned long)
// vaddr 0x2226c14 | ghidra 0x2326c14 | size 316 | symbol _ZN4Aska14DiscReadStream4ReadEPvmm | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZN4Aska14DiscReadStream4ReadEPvmm
                (long *param_1,undefined8 param_2,ulong param_3,undefined8 param_4)

{
  ulong uVar1;
  undefined8 uVar2;
  long lVar3;
  undefined *puStack_b0;
  undefined1 *puStack_a8;
  ulong uStack_a0;
  undefined1 auStack_98 [104];
  
  uVar1 = (**(code **)(*param_1 + 0x10))();
  if ((uVar1 & 1) == 0) {
    lVar3 = *param_1;
    uVar2 = 0xfffffffffffffc44;
code_r0x02326c6c:
    (**(code **)(lVar3 + 0x48))(param_1,uVar2);
    return 0;
  }
  uVar1 = (**(code **)(*param_1 + 0x70))(param_1);
  if ((uVar1 & 1) != 0) {
    lVar3 = *param_1;
    uVar2 = 0xfffffffffffffc3c;
    goto code_r0x02326c6c;
  }
  Aska::Event::Event()(auStack_98);
  uVar1 = Aska::Event::Create(bool, bool)(auStack_98,0,0);
  if ((uVar1 & 1) == 0) {
    lVar3 = *param_1;
    uVar2 = 0xfffffffffffffc41;
  }
  else {
    uStack_a0 = 0;
    puStack_b0 = PTR__ZTVN4Aska14DiscReadStream10ReadNotifyE_02cbc4b8 + 0x10;
    puStack_a8 = auStack_98;
    lVar3 = (**(code **)(*param_1 + 0x88))(param_1,param_2,param_1[7],param_3,param_4,&puStack_b0,0)
    ;
    if (lVar3 != 0) {
      Aska::Event::Wait(unsigned int) const(auStack_98,0);
      Aska::Event::Exit()(auStack_98);
      uVar1 = 0;
      if (param_3 != 0) {
        uVar1 = uStack_a0 / param_3;
      }
      goto code_r0x02326d30;
    }
    Aska::Event::Exit()(auStack_98);
    lVar3 = *param_1;
    uVar2 = 0xffffffffffffffff;
  }
  (**(code **)(lVar3 + 0x48))(param_1,uVar2);
  uVar1 = 0;
code_r0x02326d30:
  Aska::Event::Exit()(auStack_98);
  return uVar1;
}

// ==== Aska::DiscReadStream::Write(void const*, unsigned long, unsigned long)
// vaddr 0x2226d50 | ghidra 0x2326d50 | size 32 | symbol _ZN4Aska14DiscReadStream5WriteEPKvmm | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska14DiscReadStream5WriteEPKvmm(long *param_1)

{
  (**(code **)(*param_1 + 0x48))(param_1,0xfffffffffffffc46);
  return 0;
}

// ==== Aska::DiscReadStream::Flush()
// vaddr 0x2226d70 | ghidra 0x2326d70 | size 16 | symbol _ZN4Aska14DiscReadStream5FlushEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska14DiscReadStream5FlushEv(long *param_1)

{
                    /* WARNING: Could not recover jumptable at 0x02326d7c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*param_1 + 0x48))(param_1,0xfffffffffffffc46);
  return;
}

// ==== Aska::TPoolAtomicDynamic<Aska::DiscReadStream::ReadAsyncNotify>::SecurePool(int)
// vaddr 0x2226d80 | ghidra 0x2326d80 | size 568 | symbol _ZN4Aska18TPoolAtomicDynamicINS_14DiscReadStream15ReadAsyncNotifyEE10SecurePoolEi | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska18TPoolAtomicDynamicINS_14DiscReadStream15ReadAsyncNotifyEE10SecurePoolEi
          (long param_1,int param_2)

{
  uint uVar1;
  undefined *puVar2;
  int iVar3;
  undefined1 auVar4 [16];
  undefined4 *puVar5;
  long *plVar6;
  ulong uVar7;
  ulong uVar8;
  ulong uVar9;
  long *plVar10;
  long lVar11;
  long lVar12;
  
  if ((param_2 == 0) || (*(char *)(param_1 + 0x20) != '\0')) {
    return 0;
  }
  *(undefined2 *)(param_1 + 0x20) = 0x101;
  iVar3 = param_2 + 0x1f;
  if (-1 < param_2) {
    iVar3 = param_2;
  }
  *(int *)(param_1 + 0x24) = param_2;
  uVar1 = (iVar3 >> 5) + 1;
  auVar4._8_8_ = 0;
  auVar4._0_8_ = (long)(int)uVar1;
  uVar7 = -(ulong)(uVar1 >> 0x1f) & 0xfffffffc00000000 | (ulong)uVar1 << 2;
  if (SUB168(auVar4 * ZEXT816(4),8) != 0) {
    uVar7 = 0xffffffffffffffff;
  }
  puVar5 = (undefined4 *)operator new[](unsigned long, std::nothrow_t const&)(uVar7,PTR__ZSt7nothrow_02cb9a80);
  *(undefined4 **)(param_1 + 0x10) = puVar5;
  if (puVar5 != (undefined4 *)0x0) {
    uVar7 = (ulong)param_2;
    plVar6 = (long *)operator new[](unsigned long, std::nothrow_t const&)((uVar7 + (long)param_2 * 4) * 0x10,PTR__ZSt7nothrow_02cb9a80);
    *(long **)(param_1 + 8) = plVar6;
    if (plVar6 != (long *)0x0) {
      if (0 < param_2) {
        if (param_2 == 1) {
          uVar8 = 0;
        }
        else {
          uVar8 = uVar7 & 0xfffffffffffffffe;
          if (uVar8 != 0) {
            puVar2 = PTR__ZTVN4Aska14DiscReadStream15ReadAsyncNotifyE_02cc2498 + 0x10;
            uVar9 = uVar8;
            plVar10 = plVar6;
            do {
              *plVar10 = (long)puVar2;
              plVar10[10] = (long)puVar2;
              uVar9 = uVar9 - 2;
              plVar10 = plVar10 + 0x14;
            } while (uVar9 != 0);
            if (uVar8 == uVar7) goto code_r0x02326f90;
          }
        }
        puVar2 = PTR__ZTVN4Aska14DiscReadStream15ReadAsyncNotifyE_02cc2498 + 0x10;
        plVar6 = plVar6 + uVar8 * 10;
        do {
          uVar8 = uVar8 + 1;
          *plVar6 = (long)puVar2;
          plVar6 = plVar6 + 10;
        } while ((long)uVar8 < (long)uVar7);
      }
code_r0x02326f90:
      if (uVar1 != 0) {
        uVar7 = ~((long)(int)uVar1 - 1U);
        do {
          uVar7 = uVar7 + 1;
          *puVar5 = 0;
          puVar5 = puVar5 + 1;
        } while (uVar7 != 0);
      }
      return 1;
    }
    operator delete[](void*)(puVar5);
    *(undefined8 *)(param_1 + 0x10) = 0;
    if (*(long **)(param_1 + 8) == (long *)0x0) goto code_r0x02326f18;
    if (0 < *(int *)(param_1 + 0x24)) {
      (**(code **)(**(long **)(param_1 + 8) + 8))();
      if (1 < *(int *)(param_1 + 0x24)) {
        lVar11 = 1;
        lVar12 = 0x50;
        do {
          (**(code **)(*(long *)(*(long *)(param_1 + 8) + lVar12) + 8))();
          lVar11 = lVar11 + 1;
          lVar12 = lVar12 + 0x50;
        } while (lVar11 < *(int *)(param_1 + 0x24));
      }
      goto code_r0x02326f08;
    }
    goto code_r0x02326f10;
  }
  if (*(long **)(param_1 + 8) == (long *)0x0) goto code_r0x02326f18;
  if (*(int *)(param_1 + 0x24) < 1) {
code_r0x02326f10:
    operator delete[](void*)();
  }
  else {
    (**(code **)(**(long **)(param_1 + 8) + 8))();
    if (1 < *(int *)(param_1 + 0x24)) {
      lVar11 = 1;
      lVar12 = 0x50;
      do {
        (**(code **)(*(long *)(*(long *)(param_1 + 8) + lVar12) + 8))();
        lVar11 = lVar11 + 1;
        lVar12 = lVar12 + 0x50;
      } while (lVar11 < *(int *)(param_1 + 0x24));
    }
code_r0x02326f08:
    if (*(long *)(param_1 + 8) != 0) goto code_r0x02326f10;
  }
  *(undefined8 *)(param_1 + 8) = 0;
code_r0x02326f18:
  *(undefined4 *)(param_1 + 0x24) = 0;
  *(undefined4 *)(param_1 + 0x1c) = 0;
  *(undefined4 *)(param_1 + 0x18) = 0;
  *(undefined2 *)(param_1 + 0x20) = 0;
  *(undefined4 *)(param_1 + 0x18) = 0;
  return 0;
}

// ==== Aska::DiscReadStream::ReadAsyncNotify::Init(Aska::DiscReadStream*, Aska::INotify*)
// vaddr 0x2226fb8 | ghidra 0x2326fb8 | size 28 | symbol _ZN4Aska14DiscReadStream15ReadAsyncNotify4InitEPS0_PNS_7INotifyE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska14DiscReadStream15ReadAsyncNotify4InitEPS0_PNS_7INotifyE
               (long param_1,undefined8 param_2,undefined8 param_3)

{
  *(undefined8 *)(param_1 + 8) = param_2;
  *(undefined8 *)(param_1 + 0x10) = param_3;
  *(undefined8 *)(param_1 + 0x48) = 0;
  *(undefined8 *)(param_1 + 0x40) = 0;
  *(undefined8 *)(param_1 + 0x38) = 0;
  *(undefined8 *)(param_1 + 0x30) = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  *(undefined8 *)(param_1 + 0x20) = 0;
  *(undefined8 *)(param_1 + 0x18) = 0;
  return;
}

// ==== Aska::DiscReadStream::ReleaseReadAsyncNotify(Aska::DiscReadStream::ReadAsyncNotify*)
// vaddr 0x2226fd4 | ghidra 0x2326fd4 | size 108 | symbol _ZN4Aska14DiscReadStream22ReleaseReadAsyncNotifyEPNS0_15ReadAsyncNotifyE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska14DiscReadStream22ReleaseReadAsyncNotifyEPNS0_15ReadAsyncNotifyE
               (long param_1,long param_2)

{
  uint *puVar1;
  int *piVar2;
  uint uVar3;
  uint uVar4;
  char cVar5;
  bool bVar6;
  
  uVar4 = (int)((ulong)(param_2 - *(long *)(param_1 + 0x10)) >> 4) * -0x33333333;
  uVar3 = uVar4 + 0x1f;
  if (-1 < (int)uVar4) {
    uVar3 = uVar4;
  }
  puVar1 = (uint *)(*(long *)(param_1 + 0x18) + (long)((int)uVar3 >> 5) * 4);
  do {
    cVar5 = '\x01';
    bVar6 = (bool)ExclusiveMonitorPass(puVar1,0x10);
    if (bVar6) {
      *puVar1 = *puVar1 & ~(1 << (ulong)(uVar4 & 0x1f));
      cVar5 = ExclusiveMonitorsStatus();
    }
  } while (cVar5 != '\0');
  piVar2 = (int *)(param_1 + 0x24);
  do {
    cVar5 = '\x01';
    bVar6 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar6) {
      *piVar2 = *piVar2 + -1;
      cVar5 = ExclusiveMonitorsStatus();
    }
  } while (cVar5 != '\0');
  DataMemoryBarrier(2,3);
  return;
}

// ==== Aska::DiscReadStream::FinishReadAsync(Aska::DiscReadStream::ReadAsyncNotify*, unsigned long)
// vaddr 0x2227040 | ghidra 0x2327040 | size 232 | symbol _ZN4Aska14DiscReadStream15FinishReadAsyncEPNS0_15ReadAsyncNotifyEm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska14DiscReadStream15FinishReadAsyncEPNS0_15ReadAsyncNotifyEm
               (long *param_1,long param_2,long *param_3)

{
  uint *puVar1;
  int *piVar2;
  uint uVar3;
  uint uVar4;
  char cVar5;
  bool bVar6;
  undefined8 *puVar7;
  long lVar8;
  long lVar9;
  
  lVar8 = *param_3;
  if (lVar8 < 0) {
    lVar9 = *param_1;
  }
  else {
    lVar8 = 0;
    param_1[7] = param_1[7] + *(long *)(param_2 + 0x18);
    param_3[1] = *(long *)(param_2 + 0x18);
    lVar9 = *param_1;
  }
  (**(code **)(lVar9 + 0x48))(param_1,lVar8);
  puVar7 = *(undefined8 **)(param_2 + 0x10);
  uVar4 = (int)((ulong)(param_2 - param_1[2]) >> 4) * -0x33333333;
  uVar3 = uVar4 + 0x1f;
  if (-1 < (int)uVar4) {
    uVar3 = uVar4;
  }
  puVar1 = (uint *)(param_1[3] + (long)((int)uVar3 >> 5) * 4);
  do {
    cVar5 = '\x01';
    bVar6 = (bool)ExclusiveMonitorPass(puVar1,0x10);
    if (bVar6) {
      *puVar1 = *puVar1 & ~(1 << (ulong)(uVar4 & 0x1f));
      cVar5 = ExclusiveMonitorsStatus();
    }
  } while (cVar5 != '\0');
  piVar2 = (int *)((long)param_1 + 0x24);
  do {
    cVar5 = '\x01';
    bVar6 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar6) {
      *piVar2 = *piVar2 + -1;
      cVar5 = ExclusiveMonitorsStatus();
    }
  } while (cVar5 != '\0');
  DataMemoryBarrier(2,3);
  if (puVar7 != (undefined8 *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x02327118. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)*puVar7)(puVar7,param_3);
    return;
  }
  return;
}

// ==== Aska::DiscReadStream::ReadAsyncNotify::Handler(unsigned long)
// vaddr 0x2227128 | ghidra 0x2327128 | size 780 | symbol _ZN4Aska14DiscReadStream15ReadAsyncNotify7HandlerEm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska14DiscReadStream15ReadAsyncNotify7HandlerEm(long param_1,long *param_2)

{
  uint *puVar1;
  int *piVar2;
  ulong uVar3;
  uint uVar4;
  uint uVar5;
  char cVar6;
  bool bVar7;
  undefined8 *puVar8;
  long lVar9;
  ulong uVar10;
  long lVar11;
  ulong uVar12;
  ulong uVar13;
  long *plVar14;
  
  lVar9 = *param_2;
  if (lVar9 < 0) {
    plVar14 = *(long **)(param_1 + 8);
    (**(code **)(*plVar14 + 0x48))(plVar14);
    puVar8 = *(undefined8 **)(param_1 + 0x10);
    uVar5 = (int)((ulong)(param_1 - plVar14[2]) >> 4) * -0x33333333;
    uVar4 = uVar5 + 0x1f;
    if (-1 < (int)uVar5) {
      uVar4 = uVar5;
    }
    puVar1 = (uint *)(plVar14[3] + (long)((int)uVar4 >> 5) * 4);
    do {
      cVar6 = '\x01';
      bVar7 = (bool)ExclusiveMonitorPass(puVar1,0x10);
      if (bVar7) {
        *puVar1 = *puVar1 & ~(1 << (ulong)(uVar5 & 0x1f));
        cVar6 = ExclusiveMonitorsStatus();
      }
    } while (cVar6 != '\0');
    piVar2 = (int *)((long)plVar14 + 0x24);
    do {
      cVar6 = '\x01';
      bVar7 = (bool)ExclusiveMonitorPass(piVar2,0x10);
      if (bVar7) {
        *piVar2 = *piVar2 + -1;
        cVar6 = ExclusiveMonitorsStatus();
      }
    } while (cVar6 != '\0');
  }
  else if (*(long *)(param_1 + 0x20) == 0) {
    plVar14 = *(long **)(param_1 + 8);
    lVar9 = *(long *)(param_1 + 0x18) + lVar9;
    *(long *)(param_1 + 0x18) = lVar9;
    lVar11 = *param_2;
    if (lVar11 < 0) {
      lVar9 = *plVar14;
    }
    else {
      lVar11 = 0;
      plVar14[7] = plVar14[7] + lVar9;
      param_2[1] = *(long *)(param_1 + 0x18);
      lVar9 = *plVar14;
    }
    (**(code **)(lVar9 + 0x48))(plVar14,lVar11);
    puVar8 = *(undefined8 **)(param_1 + 0x10);
    uVar5 = (int)((ulong)(param_1 - plVar14[2]) >> 4) * -0x33333333;
    uVar4 = uVar5 + 0x1f;
    if (-1 < (int)uVar5) {
      uVar4 = uVar5;
    }
    puVar1 = (uint *)(plVar14[3] + (long)((int)uVar4 >> 5) * 4);
    do {
      cVar6 = '\x01';
      bVar7 = (bool)ExclusiveMonitorPass(puVar1,0x10);
      if (bVar7) {
        *puVar1 = *puVar1 & ~(1 << (ulong)(uVar5 & 0x1f));
        cVar6 = ExclusiveMonitorsStatus();
      }
    } while (cVar6 != '\0');
    piVar2 = (int *)((long)plVar14 + 0x24);
    do {
      cVar6 = '\x01';
      bVar7 = (bool)ExclusiveMonitorPass(piVar2,0x10);
      if (bVar7) {
        *piVar2 = *piVar2 + -1;
        cVar6 = ExclusiveMonitorsStatus();
      }
    } while (cVar6 != '\0');
  }
  else {
    lVar11 = *(long *)(param_1 + 0x40) - *(long *)(param_1 + 0x48);
    uVar12 = *(long *)(param_1 + 0x28) - *(long *)(param_1 + 0x18);
    uVar13 = lVar9 - lVar11;
    if (uVar13 <= uVar12) {
      uVar12 = uVar13;
    }
    memcpy(*(long *)(param_1 + 0x20),*(long *)(param_1 + 0x30) + lVar11,uVar12);
    uVar13 = *(long *)(param_1 + 0x18) + uVar12;
    *(ulong *)(param_1 + 0x18) = uVar13;
    if (uVar13 < *(ulong *)(param_1 + 0x28)) {
      lVar9 = *(long *)(param_1 + 8);
      uVar3 = *(long *)(param_1 + 0x40) + uVar12;
      uVar10 = uVar3 & 0xfffffffffffffe00;
      *(ulong *)(param_1 + 0x20) = *(long *)(param_1 + 0x20) + uVar12;
      *(ulong *)(param_1 + 0x40) = uVar3;
      *(ulong *)(param_1 + 0x48) = uVar10;
      uVar13 = (*(ulong *)(param_1 + 0x28) + 0x1ff) - uVar13 & 0xfffffffffffffe00;
      uVar12 = *(ulong *)(param_1 + 0x38);
      if (uVar13 <= *(ulong *)(param_1 + 0x38)) {
        uVar12 = uVar13;
      }
      if (*(char *)(lVar9 + 0x160) != '\0') {
        Aska::FileReadManager::Read(char const*, unsigned char*, Aska::INotify*, unsigned long, unsigned long, int, int, bool, bool)(*(undefined8 *)PTR__ZN4Aska6Global18m_pFileReadManagerE_02cbf970,
                        *(undefined8 *)(lVar9 + 0x158),*(undefined8 *)(param_1 + 0x30),param_1,
                        uVar12,uVar10,0,0,0,*(undefined1 *)(lVar9 + 0x161));
        return;
      }
      Aska::FileReadManager::Read(int, unsigned char*, Aska::INotify*, unsigned long, unsigned long, int, int, bool)(*(undefined8 *)PTR__ZN4Aska6Global18m_pFileReadManagerE_02cbf970,
                      *(undefined4 *)(lVar9 + 0x158),*(undefined8 *)(param_1 + 0x30),param_1,uVar12,
                      uVar10,0,0,1);
      return;
    }
    lVar9 = *param_2;
    plVar14 = *(long **)(param_1 + 8);
    if (lVar9 < 0) {
      lVar11 = *plVar14;
    }
    else {
      lVar9 = 0;
      plVar14[7] = plVar14[7] + uVar13;
      param_2[1] = *(long *)(param_1 + 0x18);
      lVar11 = *plVar14;
    }
    (**(code **)(lVar11 + 0x48))(plVar14,lVar9);
    puVar8 = *(undefined8 **)(param_1 + 0x10);
    uVar5 = (int)((ulong)(param_1 - plVar14[2]) >> 4) * -0x33333333;
    uVar4 = uVar5 + 0x1f;
    if (-1 < (int)uVar5) {
      uVar4 = uVar5;
    }
    puVar1 = (uint *)(plVar14[3] + (long)((int)uVar4 >> 5) * 4);
    do {
      cVar6 = '\x01';
      bVar7 = (bool)ExclusiveMonitorPass(puVar1,0x10);
      if (bVar7) {
        *puVar1 = *puVar1 & ~(1 << (ulong)(uVar5 & 0x1f));
        cVar6 = ExclusiveMonitorsStatus();
      }
    } while (cVar6 != '\0');
    piVar2 = (int *)((long)plVar14 + 0x24);
    do {
      cVar6 = '\x01';
      bVar7 = (bool)ExclusiveMonitorPass(piVar2,0x10);
      if (bVar7) {
        *piVar2 = *piVar2 + -1;
        cVar6 = ExclusiveMonitorsStatus();
      }
    } while (cVar6 != '\0');
  }
  DataMemoryBarrier(2,3);
  if (puVar8 == (undefined8 *)0x0) {
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x02327420. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)*puVar8)(puVar8,param_2);
  return;
}

// ==== Aska::DiscReadStream::ReadNotify::Handler(unsigned long)
// vaddr 0x2227434 | ghidra 0x2327434 | size 36 | symbol _ZN4Aska14DiscReadStream10ReadNotify7HandlerEm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska14DiscReadStream10ReadNotify7HandlerEm(long param_1,long *param_2)

{
  long lVar1;
  
  if (*param_2 < 0) {
    lVar1 = 0;
  }
  else {
    lVar1 = param_2[1];
  }
  *(long *)(param_1 + 0x10) = lVar1;
  (*(code *)PTR__ZNK4Aska5Event3SetEv_02c9dcf0)(*(undefined8 *)(param_1 + 8));
  return;
}

// ==== Aska::DiscReadStream::~DiscReadStream()
// vaddr 0x2227458 | ghidra 0x2327458 | size 40 | symbol _ZN4Aska14DiscReadStreamD2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska14DiscReadStreamD2Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska14DiscReadStreamE_02cc4e70 + 0x10);
  Aska::DiscReadStream::Close()();
  (*(code *)PTR__ZN4Aska18TPoolAtomicDynamicINS_14DiscReadStream15ReadAsyncNotifyEED2Ev_02cab5b8)
            (param_1 + 1);
  return;
}

// ==== Aska::DiscReadStream::~DiscReadStream()
// vaddr 0x2227480 | ghidra 0x2327480 | size 60 | symbol _ZN4Aska14DiscReadStreamD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska14DiscReadStreamD0Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska14DiscReadStreamE_02cc4e70 + 0x10);
  Aska::DiscReadStream::Close()();
  Aska::TPoolAtomicDynamic<Aska::DiscReadStream::ReadAsyncNotify>::~TPoolAtomicDynamic()(param_1 + 1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::DiscReadStream::IsReady() const
// vaddr 0x22274bc | ghidra 0x23274bc | size 16 | symbol _ZNK4Aska14DiscReadStream7IsReadyEv | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK4Aska14DiscReadStream7IsReadyEv(long param_1)

{
  return *(long *)(param_1 + 0x158) != 0;
}

// ==== Aska::DiscReadStream::Tell() const
// vaddr 0x22274cc | ghidra 0x23274cc | size 8 | symbol _ZNK4Aska14DiscReadStream4TellEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska14DiscReadStream4TellEv(long param_1)

{
  return *(undefined8 *)(param_1 + 0x38);
}

// ==== Aska::DiscReadStream::SetLastError(long) const
// vaddr 0x22274d4 | ghidra 0x23274d4 | size 12 | symbol _ZNK4Aska14DiscReadStream12SetLastErrorEl | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska14DiscReadStream12SetLastErrorEl(long param_1,undefined8 param_2)

{
  *(int *)(param_1 + 0x30) = (int)param_2;
  return param_2;
}

// ==== Aska::DiscReadStream::GetLastError() const
// vaddr 0x22274e0 | ghidra 0x23274e0 | size 24 | symbol _ZNK4Aska14DiscReadStream12GetLastErrorEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK4Aska14DiscReadStream12GetLastErrorEv(long param_1)

{
  int *piVar1;
  int iVar2;
  char cVar3;
  bool bVar4;
  
  piVar1 = (int *)(param_1 + 0x30);
  do {
    iVar2 = *piVar1;
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar4) {
      *piVar1 = 0;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
  return (long)iVar2;
}

// ==== Aska::DiscReadStream::PeekLastError() const
// vaddr 0x22274f8 | ghidra 0x23274f8 | size 8 | symbol _ZNK4Aska14DiscReadStream13PeekLastErrorEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK4Aska14DiscReadStream13PeekLastErrorEv(long param_1)

{
  return (long)*(int *)(param_1 + 0x30);
}

// ==== Aska::DiscReadStream::GetTotalSize() const
// vaddr 0x2227500 | ghidra 0x2327500 | size 48 | symbol _ZNK4Aska14DiscReadStream12GetTotalSizeEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK4Aska14DiscReadStream12GetTotalSizeEv(long param_1)

{
  if (*(char *)(param_1 + 0x160) != '\0') {
    (*(code *)PTR__ZN4Aska15FileReadManager14CalcFileLengthEPKcb_02c9dce8)
              (*(undefined8 *)(param_1 + 0x158),*(undefined1 *)(param_1 + 0x161));
    return;
  }
  (*(code *)PTR__ZNK4Aska15FileReadManager14CalcFileLengthEi_02c93418)
            (*(undefined8 *)PTR__ZN4Aska6Global18m_pFileReadManagerE_02cbf970,
             *(undefined4 *)(param_1 + 0x158));
  return;
}

// ==== Aska::DiscReadStream::IsAsync() const
// vaddr 0x2227530 | ghidra 0x2327530 | size 8 | symbol _ZNK4Aska14DiscReadStream7IsAsyncEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska14DiscReadStream7IsAsyncEv(void)

{
  return 1;
}

// ==== Aska::DiscReadStream::IsBusy() const
// vaddr 0x2227538 | ghidra 0x2327538 | size 16 | symbol _ZNK4Aska14DiscReadStream6IsBusyEv | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK4Aska14DiscReadStream6IsBusyEv(long param_1)

{
  return *(int *)(param_1 + 0x24) != 0;
}

// ==== Aska::DiscReadStream::ReadNotify::~ReadNotify()
// vaddr 0x2227548 | ghidra 0x2327548 | size 4 | symbol _ZN4Aska14DiscReadStream10ReadNotifyD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska14DiscReadStream10ReadNotifyD0Ev(void)

{
  (*(code *)PTR__ZdlPv_02ca4758)();
  return;
}

// ==== Aska::DiscReadStream::ReadAsyncNotify::~ReadAsyncNotify()
// vaddr 0x222754c | ghidra 0x232754c | size 4 | symbol _ZN4Aska14DiscReadStream15ReadAsyncNotifyD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska14DiscReadStream15ReadAsyncNotifyD0Ev(void)

{
  (*(code *)PTR__ZdlPv_02ca4758)();
  return;
}

// ==== Aska::IStream::Print(Aska::IStream*, char const*, ...)
// vaddr 0x2229aa4 | ghidra 0x2329aa4 | size 104 | symbol _ZN4Aska7IStream5PrintEPS0_PKcz | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska7IStream5PrintEPS0_PKcz
               (undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  undefined8 uStack_80;
  undefined8 uStack_78;
  undefined8 uStack_70;
  undefined8 uStack_68;
  undefined8 uStack_60;
  undefined8 uStack_58;
  undefined1 *puStack_50;
  undefined1 **ppuStack_48;
  undefined8 *puStack_40;
  undefined8 uStack_38;
  
  puStack_40 = &uStack_80;
  ppuStack_48 = &puStack_50;
  uStack_38 = 0xffffff80ffffffd0;
  uStack_80 = param_3;
  uStack_78 = param_4;
  uStack_70 = param_5;
  uStack_68 = param_6;
  uStack_60 = param_7;
  uStack_58 = param_8;
  puStack_50 = (undefined1 *)register0x00000008;
  Aska::IStream::PrintV(Aska::IStream*, char const*, std::__va_list)(param_1,param_2,&puStack_50);
  return;
}

// ==== Aska::MultiMediaStream::Open(Aska::IStream*, unsigned long, unsigned long, Aska::MultiMediaStream::LoopParam*)
// vaddr 0x2234f48 | ghidra 0x2334f48 | size 184 | symbol _ZN4Aska16MultiMediaStream4OpenEPNS_7IStreamEmmPNS0_9LoopParamE | lib libSOA-3.7.0.so | 2026-10-04
undefined4
_ZN4Aska16MultiMediaStream4OpenEPNS_7IStreamEmmPNS0_9LoopParamE
          (long param_1,undefined8 param_2,ulong param_3,ulong param_4,undefined8 *param_5)

{
  ulong uVar1;
  ulong uVar2;
  undefined4 uVar3;
  undefined8 uVar4;
  
  uVar3 = 0;
  if ((param_3 < param_4) && (*(long *)(param_1 + 0x40) == 0)) {
    *(undefined1 *)(param_1 + 0x8e) = 0;
    *(undefined8 *)(param_1 + 0x40) = param_2;
    *(ulong *)(param_1 + 0x48) = param_3;
    *(ulong *)(param_1 + 0x50) = param_4;
    *(undefined4 *)(param_1 + 0x88) = 0;
    if (param_5 == (undefined8 *)0x0) {
      *(undefined2 *)(param_1 + 0x8c) = 0;
      *(undefined8 *)(param_1 + 0x80) = 0;
      *(undefined8 *)(param_1 + 0x78) = 0;
      *(undefined8 *)(param_1 + 0x70) = 0;
      *(undefined8 *)(param_1 + 0x68) = 0;
      *(undefined8 *)(param_1 + 0x60) = 0;
      *(undefined8 *)(param_1 + 0x58) = 0;
    }
    else {
      uVar1 = param_5[1];
      uVar2 = param_5[2];
      if (uVar2 == 0 && uVar1 == 0) {
        param_5[1] = param_3;
        param_5[2] = *(undefined8 *)(param_1 + 0x50);
      }
      else {
        if (param_4 < uVar2) {
          return 0;
        }
        if (uVar1 < param_3) {
          return 0;
        }
        if (uVar2 <= uVar1) {
          return 0;
        }
      }
      *(undefined8 *)(param_1 + 0x58) = *param_5;
      *(undefined8 *)(param_1 + 0x60) = param_5[1];
      *(undefined8 *)(param_1 + 0x68) = param_5[2];
      uVar4 = param_5[3];
      *(undefined2 *)(param_1 + 0x8c) = 0;
      *(undefined8 *)(param_1 + 0x78) = 0;
      *(undefined8 *)(param_1 + 0x80) = 0;
      *(undefined8 *)(param_1 + 0x70) = uVar4;
    }
    uVar3 = 1;
    *(undefined4 *)(param_1 + 0x10) = 1;
    *(undefined4 *)(param_1 + 0x14) = 0;
  }
  return uVar3;
}

// ==== Aska::MultiMediaStream::Open_(Aska::IStream*, bool, unsigned long, unsigned long, Aska::MultiMediaStream::LoopParam*)
// vaddr 0x2235000 | ghidra 0x2335000 | size 208 | symbol _ZN4Aska16MultiMediaStream5Open_EPNS_7IStreamEbmmPNS0_9LoopParamE | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska16MultiMediaStream5Open_EPNS_7IStreamEbmmPNS0_9LoopParamE
          (long param_1,long param_2,uint param_3,ulong param_4,ulong param_5,undefined8 *param_6)

{
  ulong uVar1;
  ulong uVar2;
  undefined1 uVar3;
  undefined8 uVar4;
  
  if (param_5 <= param_4) {
    return 0;
  }
  if (*(long *)(param_1 + 0x40) != 0) {
    return 0;
  }
  if ((param_3 & 1) == 0) {
    uVar3 = 0;
  }
  else {
    if (param_2 == 0) goto code_r0x0233502c;
    uVar3 = 1;
  }
  *(undefined1 *)(param_1 + 0x8e) = uVar3;
code_r0x0233502c:
  *(long *)(param_1 + 0x40) = param_2;
  *(ulong *)(param_1 + 0x48) = param_4;
  *(ulong *)(param_1 + 0x50) = param_5;
  *(undefined4 *)(param_1 + 0x88) = 0;
  if (param_6 == (undefined8 *)0x0) {
    *(undefined2 *)(param_1 + 0x8c) = 0;
    *(undefined8 *)(param_1 + 0x80) = 0;
    *(undefined8 *)(param_1 + 0x78) = 0;
    *(undefined8 *)(param_1 + 0x70) = 0;
    *(undefined8 *)(param_1 + 0x68) = 0;
    *(undefined8 *)(param_1 + 0x60) = 0;
    *(undefined8 *)(param_1 + 0x58) = 0;
  }
  else {
    uVar1 = param_6[1];
    uVar2 = param_6[2];
    if (uVar2 == 0 && uVar1 == 0) {
      param_6[1] = param_4;
      param_6[2] = *(undefined8 *)(param_1 + 0x50);
    }
    else if (((uVar2 <= uVar1) || (uVar1 < param_4)) || (param_5 < uVar2)) {
      return 0;
    }
    *(undefined8 *)(param_1 + 0x58) = *param_6;
    *(undefined8 *)(param_1 + 0x60) = param_6[1];
    *(undefined8 *)(param_1 + 0x68) = param_6[2];
    uVar4 = param_6[3];
    *(undefined2 *)(param_1 + 0x8c) = 0;
    *(undefined8 *)(param_1 + 0x78) = 0;
    *(undefined8 *)(param_1 + 0x80) = 0;
    *(undefined8 *)(param_1 + 0x70) = uVar4;
  }
  *(undefined4 *)(param_1 + 0x10) = 1;
  *(undefined4 *)(param_1 + 0x14) = 0;
  return 1;
}

// ==== Aska::MultiMediaStream::Open(Aska::IBufferingStream*, unsigned long, unsigned long, Aska::MultiMediaStream::LoopParam*)
// vaddr 0x22350d0 | ghidra 0x23350d0 | size 212 | symbol _ZN4Aska16MultiMediaStream4OpenEPNS_16IBufferingStreamEmmPNS0_9LoopParamE | lib libSOA-3.7.0.so | 2026-10-04
undefined4
_ZN4Aska16MultiMediaStream4OpenEPNS_16IBufferingStreamEmmPNS0_9LoopParamE
          (long param_1,long param_2,ulong param_3,ulong param_4,undefined8 *param_5)

{
  ulong uVar1;
  ulong uVar2;
  undefined8 uVar3;
  
  if (*(long *)(param_1 + 0x40) != 0) {
    return 0;
  }
  if (param_4 <= param_3) {
    return 0;
  }
  if (param_2 != 0) {
    *(undefined1 *)(param_1 + 0x8e) = 1;
  }
  *(long *)(param_1 + 0x40) = param_2;
  *(ulong *)(param_1 + 0x48) = param_3;
  *(ulong *)(param_1 + 0x50) = param_4;
  *(undefined4 *)(param_1 + 0x88) = 0;
  if (param_5 == (undefined8 *)0x0) {
    *(undefined2 *)(param_1 + 0x8c) = 0;
    *(undefined8 *)(param_1 + 0x80) = 0;
    *(undefined8 *)(param_1 + 0x78) = 0;
    *(undefined8 *)(param_1 + 0x70) = 0;
    *(undefined8 *)(param_1 + 0x68) = 0;
    *(undefined8 *)(param_1 + 0x60) = 0;
    *(undefined8 *)(param_1 + 0x58) = 0;
  }
  else {
    uVar1 = param_5[1];
    uVar2 = param_5[2];
    if (uVar2 == 0 && uVar1 == 0) {
      param_5[1] = param_3;
      param_5[2] = *(undefined8 *)(param_1 + 0x50);
    }
    else {
      if (param_4 < uVar2) {
        return 0;
      }
      if (uVar1 < param_3) {
        return 0;
      }
      if (uVar2 <= uVar1) {
        return 0;
      }
    }
    *(undefined8 *)(param_1 + 0x58) = *param_5;
    *(undefined8 *)(param_1 + 0x60) = param_5[1];
    *(undefined8 *)(param_1 + 0x68) = param_5[2];
    uVar3 = param_5[3];
    *(undefined2 *)(param_1 + 0x8c) = 0;
    *(undefined8 *)(param_1 + 0x78) = 0;
    *(undefined8 *)(param_1 + 0x80) = 0;
    *(undefined8 *)(param_1 + 0x70) = uVar3;
  }
  *(undefined4 *)(param_1 + 0x10) = 1;
  *(undefined4 *)(param_1 + 0x14) = 0;
  return 1;
}

// ==== Aska::MultiMediaStream::Close()
// vaddr 0x22351a4 | ghidra 0x23351a4 | size 20 | symbol _ZN4Aska16MultiMediaStream5CloseEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16MultiMediaStream5CloseEv(long param_1)

{
  if (*(long *)(param_1 + 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x8e) = 0;
    *(undefined8 *)(param_1 + 0x40) = 0;
  }
  return;
}

// ==== Aska::MultiMediaStream::Seek(long, int)
// vaddr 0x22351b8 | ghidra 0x23351b8 | size 292 | symbol _ZN4Aska16MultiMediaStream4SeekEli | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16MultiMediaStream4SeekEli(long *param_1,undefined8 param_2,undefined4 param_3)

{
  long lVar1;
  ulong uVar2;
  long lVar3;
  undefined8 uVar4;
  long lVar5;
  long lStack_38;
  
  uVar2 = (**(code **)(*param_1 + 0x10))();
  if ((uVar2 & 1) == 0) {
                    /* WARNING: Could not recover jumptable at 0x023352b0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*param_1 + 0x48))(param_1,0xfffffffffffffc44);
    return;
  }
  lVar5 = param_1[0xb];
  if ((lVar5 != -1) && ((lVar5 < 1 || (lVar5 <= param_1[0xf])))) {
                    /* WARNING: Could not recover jumptable at 0x023352d8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*(long *)param_1[8] + 0x20))((long *)param_1[8],param_2,param_3);
    return;
  }
  lVar5 = param_1[0xc];
  lVar1 = param_1[0xd];
  lVar3 = (**(code **)(*param_1 + 0x18))(param_1);
  if (-1 < lVar3) {
    uVar4 = Aska::IStream::CalcSeekPt(long, long, long, long, int, long*)(lVar3,lVar5,lVar1,param_2,param_3,&lStack_38);
    if (lStack_38 < 0) {
      (**(code **)(*param_1 + 0x48))(param_1);
      *(undefined2 *)((long)param_1 + 0x8c) = 0;
      param_1[0xf] = 0;
      param_1[0x10] = 0;
      *(undefined4 *)(param_1 + 2) = 1;
      *(undefined4 *)((long)param_1 + 0x14) = 0;
    }
    (**(code **)(*(long *)param_1[8] + 0x20))((long *)param_1[8],uVar4,0);
  }
  return;
}

// ==== Aska::MultiMediaStream::CalcStartEndPt(int, unsigned long*, unsigned long*) const
// vaddr 0x22352dc | ghidra 0x23352dc | size 92 | symbol _ZNK4Aska16MultiMediaStream14CalcStartEndPtEiPmS1_ | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZNK4Aska16MultiMediaStream14CalcStartEndPtEiPmS1_
          (long param_1,int param_2,undefined8 *param_3,undefined8 *param_4)

{
  undefined8 uVar1;
  undefined8 *puVar2;
  long lVar3;
  undefined8 uVar4;
  
  lVar3 = *(long *)(param_1 + 0x58);
  if (lVar3 == -1) {
code_r0x02335304:
    uVar4 = *(undefined8 *)(param_1 + 0x60);
    puVar2 = (undefined8 *)(param_1 + 0x68);
    uVar1 = 1;
  }
  else {
    if (lVar3 < 1) {
      uVar4 = *(undefined8 *)(param_1 + 0x48);
    }
    else {
      if (*(long *)(param_1 + (long)param_2 * 8 + 0x78) < lVar3) goto code_r0x02335304;
      uVar4 = *(undefined8 *)(param_1 + 0x60);
    }
    uVar1 = 0;
    puVar2 = (undefined8 *)(param_1 + 0x50);
  }
  *param_3 = uVar4;
  *param_4 = *puVar2;
  return uVar1;
}

// ==== Aska::MultiMediaStream::Read(void*, unsigned long, unsigned long)
// vaddr 0x2235338 | ghidra 0x2335338 | size 616 | symbol _ZN4Aska16MultiMediaStream4ReadEPvmm | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZN4Aska16MultiMediaStream4ReadEPvmm(long *param_1,long param_2,long param_3,ulong param_4)

{
  long *plVar1;
  ulong uVar2;
  long *plVar3;
  long lVar4;
  long *plVar5;
  long lVar6;
  long *plVar7;
  ulong uVar8;
  ulong uVar9;
  ulong uVar10;
  long lStack_70;
  long lStack_68;
  
  if (param_3 == 1) {
    uVar9 = 0;
    plVar1 = param_1 + 0xc;
    uVar8 = param_4;
    do {
      do {
        if (param_4 <= uVar9) {
          return uVar9;
        }
        uVar2 = (**(code **)(*param_1 + 0x40))(param_1,0);
        if ((uVar2 & 1) != 0) {
          (**(code **)(*param_1 + 0x48))(param_1,0xfffffffffffffc3f);
          return uVar9;
        }
        lVar6 = param_1[0xb];
        if ((lVar6 != -1) && ((lVar6 < 1 || (lVar6 <= param_1[0xf])))) {
          lVar6 = (**(code **)(*(long *)param_1[8] + 0x28))((long *)param_1[8],param_2,1,uVar8);
code_r0x02335570:
          return lVar6 + uVar9;
        }
        uVar10 = param_1[0xd];
        uVar2 = (**(code **)(*param_1 + 0x18))(param_1);
        if ((long)uVar2 < 0) {
          return uVar2;
        }
        plVar3 = (long *)param_1[8];
        if (uVar8 < uVar10 - uVar2) {
          lVar6 = (**(code **)(*plVar3 + 0x28))(plVar3,param_2,1,uVar8);
          goto code_r0x02335570;
        }
        lVar6 = (**(code **)(*plVar3 + 0x28))(plVar3,param_2);
        if ((lVar6 == 0) && (lVar4 = (**(code **)(*param_1 + 0x58))(param_1), lVar4 < 0)) {
          if (lVar4 != -0x3c1) {
            return uVar9;
          }
          (**(code **)(*param_1 + 0x50))(param_1);
        }
        uVar2 = (**(code **)(*param_1 + 0x18))(param_1);
        if ((long)uVar2 < 0) {
          return uVar2;
        }
        uVar9 = lVar6 + uVar9;
        uVar8 = param_4 - uVar9;
        param_2 = lVar6 + param_2;
      } while (uVar2 < uVar10);
      lVar4 = param_1[0xf];
      lVar6 = param_1[0xb];
      *(undefined2 *)((long)param_1 + 0x8c) = 0x101;
      param_1[0x10] = param_1[0x10] + 1;
      param_1[0xf] = lVar4 + 1;
      plVar3 = param_1 + 0xd;
      plVar7 = plVar1;
      if (((lVar6 != -1) && (plVar3 = param_1 + 10, plVar7 = param_1 + 9, 0 < lVar6)) &&
         (plVar3 = param_1 + 0xd, plVar7 = plVar1, lVar6 <= lVar4 + 1)) {
        plVar3 = param_1 + 10;
      }
      plVar5 = (long *)param_1[0xe];
      if (plVar5 == (long *)0x0) {
        uVar2 = (**(code **)(*param_1 + 0x20))(param_1,*plVar7,0);
      }
      else {
        lStack_68 = *plVar3;
        lStack_70 = *plVar7;
        uVar2 = (**(code **)(*plVar5 + 0x10))(plVar5,&lStack_70);
      }
    } while (-1 < (long)uVar2);
  }
  else {
    (**(code **)(*param_1 + 0x48))(param_1,0xfffffffffffffc43);
    uVar2 = 0;
  }
  return uVar2;
}

// ==== Aska::MultiMediaStream::LoopDelegate(unsigned long, unsigned long)
// vaddr 0x22355a0 | ghidra 0x23355a0 | size 72 | symbol _ZN4Aska16MultiMediaStream12LoopDelegateEmm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16MultiMediaStream12LoopDelegateEmm
               (long *param_1,undefined8 param_2,undefined8 param_3)

{
  long *plVar1;
  undefined8 uStack_20;
  undefined8 uStack_18;
  
  plVar1 = (long *)param_1[0xe];
  if (plVar1 != (long *)0x0) {
    uStack_20 = param_2;
    uStack_18 = param_3;
    (**(code **)(*plVar1 + 0x10))(plVar1,&uStack_20);
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x023355e4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*param_1 + 0x20))(param_1,param_2,0);
  return;
}

// ==== Aska::MultiMediaStream::IsEnd(long*) const
// vaddr 0x22355e8 | ghidra 0x23355e8 | size 192 | symbol _ZNK4Aska16MultiMediaStream5IsEndEPl | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK4Aska16MultiMediaStream5IsEndEPl(long *param_1,ulong *param_2)

{
  ulong uVar1;
  long lVar2;
  
  uVar1 = (**(code **)(*param_1 + 0x10))();
  if ((uVar1 & 1) == 0) {
    (**(code **)(*param_1 + 0x48))(param_1,0xfffffffffffffc44);
    if (param_2 != (ulong *)0x0) {
      *param_2 = 0xfffffffffffffc44;
      return true;
    }
  }
  else {
    uVar1 = (**(code **)(*param_1 + 0x18))(param_1);
    if (-1 < (long)uVar1) {
      if (param_2 != (ulong *)0x0) {
        *param_2 = 0;
      }
      lVar2 = param_1[0xb];
      if ((lVar2 != -1) &&
         (((lVar2 < 1 || (lVar2 <= param_1[0x10])) && ((ulong)param_1[10] <= uVar1)))) {
        return (int)param_1[0x11] == 0;
      }
      return false;
    }
    if (param_2 != (ulong *)0x0) {
      *param_2 = uVar1;
    }
  }
  return true;
}

// ==== Aska::MultiMediaStream::GetTotalSize() const
// vaddr 0x22356a8 | ghidra 0x23356a8 | size 64 | symbol _ZNK4Aska16MultiMediaStream12GetTotalSizeEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK4Aska16MultiMediaStream12GetTotalSizeEv(long *param_1)

{
  ulong uVar1;
  long lVar2;
  
  uVar1 = (**(code **)(*param_1 + 0x10))();
  if ((uVar1 & 1) != 0) {
    return param_1[10] - param_1[9];
  }
                    /* WARNING: Could not recover jumptable at 0x023356e4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  lVar2 = (**(code **)(*param_1 + 0x48))(param_1,0xfffffffffffffc44);
  return lVar2;
}

// ==== Aska::MultiMediaStream::Write(void const*, unsigned long, unsigned long)
// vaddr 0x22356e8 | ghidra 0x23356e8 | size 32 | symbol _ZN4Aska16MultiMediaStream5WriteEPKvmm | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska16MultiMediaStream5WriteEPKvmm(long *param_1)

{
  (**(code **)(*param_1 + 0x48))(param_1,0xfffffffffffffc46);
  return 0;
}

// ==== Aska::MultiMediaStream::Flush()
// vaddr 0x2235708 | ghidra 0x2335708 | size 16 | symbol _ZN4Aska16MultiMediaStream5FlushEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16MultiMediaStream5FlushEv(long *param_1)

{
                    /* WARNING: Could not recover jumptable at 0x02335714. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*param_1 + 0x48))(param_1,0xfffffffffffffc46);
  return;
}

// ==== Aska::MultiMediaStream::Tell() const
// vaddr 0x2235718 | ghidra 0x2335718 | size 40 | symbol _ZNK4Aska16MultiMediaStream4TellEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK4Aska16MultiMediaStream4TellEv(long *param_1)

{
  long *plVar1;
  
  plVar1 = (long *)param_1[8];
  if (plVar1 != (long *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x0233572c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*plVar1 + 0x18))(plVar1);
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x0233573c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*param_1 + 0x48))(param_1,0xfffffffffffffc44);
  return;
}

// ==== Aska::MultiMediaStream::SetLastError(long) const
// vaddr 0x2235740 | ghidra 0x2335740 | size 28 | symbol _ZNK4Aska16MultiMediaStream12SetLastErrorEl | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska16MultiMediaStream12SetLastErrorEl(long param_1)

{
  undefined8 uVar1;
  
  if (*(long **)(param_1 + 0x40) != (long *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x02335750. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = (**(code **)(**(long **)(param_1 + 0x40) + 0x48))();
    return uVar1;
  }
  return 0xfffffffffffffc44;
}

// ==== Aska::MultiMediaStream::GetLastError() const
// vaddr 0x223575c | ghidra 0x233575c | size 28 | symbol _ZNK4Aska16MultiMediaStream12GetLastErrorEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska16MultiMediaStream12GetLastErrorEv(long param_1)

{
  undefined8 uVar1;
  
  if (*(long **)(param_1 + 0x40) != (long *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x0233576c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = (**(code **)(**(long **)(param_1 + 0x40) + 0x50))();
    return uVar1;
  }
  return 0xfffffffffffffc44;
}

// ==== Aska::MultiMediaStream::PeekLastError() const
// vaddr 0x2235778 | ghidra 0x2335778 | size 28 | symbol _ZNK4Aska16MultiMediaStream13PeekLastErrorEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska16MultiMediaStream13PeekLastErrorEv(long param_1)

{
  undefined8 uVar1;
  
  if (*(long **)(param_1 + 0x40) != (long *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x02335788. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = (**(code **)(**(long **)(param_1 + 0x40) + 0x58))();
    return uVar1;
  }
  return 0xfffffffffffffc44;
}

// ==== Aska::MultiMediaStream::Lock(void**, unsigned long)
// vaddr 0x2235794 | ghidra 0x2335794 | size 484 | symbol _ZN4Aska16MultiMediaStream4LockEPPvm | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZN4Aska16MultiMediaStream4LockEPPvm(long *param_1,undefined8 param_2,ulong param_3)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  char cVar4;
  bool bVar5;
  bool bVar6;
  ulong uVar7;
  ulong uVar8;
  long *plVar9;
  long lVar10;
  ulong *puVar11;
  long *plVar12;
  long lVar13;
  long *plVar14;
  ulong uVar15;
  long lStack_40;
  long lStack_38;
  
  uVar7 = (**(code **)(*param_1 + 0xb0))();
  if ((uVar7 & 1) == 0) {
                    /* WARNING: Could not recover jumptable at 0x02335810. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar7 = (**(code **)(*param_1 + 0x48))(param_1,0xfffffffffffffc44);
    return uVar7;
  }
  lVar10 = param_1[0xb];
  *(undefined1 *)((long)param_1 + 0x8c) = 0;
  if ((lVar10 == -1) || ((0 < lVar10 && (param_1[0xf] < lVar10)))) {
    puVar11 = (ulong *)(param_1 + 0xd);
    bVar6 = true;
  }
  else {
    bVar6 = false;
    puVar11 = (ulong *)(param_1 + 10);
  }
  uVar15 = *puVar11;
  uVar7 = (**(code **)(*param_1 + 0x18))(param_1);
  if ((long)uVar7 < 0) {
    return uVar7;
  }
  uVar7 = uVar15 - uVar7;
  if (param_3 - 1 < uVar7) {
    uVar7 = param_3;
  }
  if (uVar7 == 0) {
    return 0;
  }
  uVar7 = (**(code **)(*(long *)param_1[8] + 0x98))((long *)param_1[8],param_2);
  if ((long)uVar7 < 0) {
    return uVar7;
  }
  plVar12 = param_1 + 0x11;
  do {
    iVar1 = (int)*plVar12 + (int)uVar7;
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(plVar12,0x10);
    if (bVar5) {
      *(int *)plVar12 = iVar1;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
  if (!bVar6) {
    return uVar7;
  }
  uVar8 = (**(code **)(*param_1 + 0x18))(param_1);
  if ((long)uVar8 < 0) {
    return uVar8;
  }
  if (uVar8 < uVar15) {
    return uVar7;
  }
  lVar13 = param_1[0xf];
  lVar10 = param_1[0xb];
  *(undefined1 *)((long)param_1 + 0x8c) = 1;
  param_1[0xf] = lVar13 + 1;
  if (lVar10 == -1) {
code_r0x023358c8:
    plVar12 = param_1 + 0xc;
    plVar14 = param_1 + 0xd;
  }
  else {
    if (lVar10 < 1) {
      plVar12 = param_1 + 9;
    }
    else {
      if (lVar13 + 1 < lVar10) goto code_r0x023358c8;
      plVar12 = param_1 + 0xc;
    }
    plVar14 = param_1 + 10;
  }
  plVar9 = (long *)param_1[0xe];
  lStack_40 = *plVar12;
  if (plVar9 == (long *)0x0) {
    uVar15 = (**(code **)(*param_1 + 0x20))(param_1,lStack_40,0);
  }
  else {
    lStack_38 = *plVar14;
    uVar15 = (**(code **)(*plVar9 + 0x10))(plVar9,&lStack_40);
  }
  if (-1 < (long)uVar15) {
    uVar3 = *(uint *)(param_1 + 2);
    if (*(uint *)((long)param_1 + 0x14) == uVar3) {
      uVar15 = 0xfffffffffffffc41;
    }
    else {
      iVar2 = 0;
      if (uVar3 + 1 < 9) {
        iVar2 = uVar3 + 1;
      }
      *(int *)((long)param_1 + (ulong)uVar3 * 4 + 0x18) = iVar1;
      *(int *)(param_1 + 2) = iVar2;
      uVar15 = uVar7;
    }
  }
  return uVar15;
}

// ==== Aska::MultiMediaStream::Unlock(unsigned long)
// vaddr 0x2235978 | ghidra 0x2335978 | size 420 | symbol _ZN4Aska16MultiMediaStream6UnlockEm | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska16MultiMediaStream6UnlockEm(long *param_1,ulong param_2)

{
  bool bVar1;
  int iVar2;
  char cVar3;
  bool bVar4;
  ulong uVar5;
  int iVar6;
  int iVar7;
  long lVar8;
  long *plVar9;
  
  uVar5 = (**(code **)(*param_1 + 0xb0))();
  if ((uVar5 & 1) == 0) {
                    /* WARNING: Could not recover jumptable at 0x023359e0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    lVar8 = (**(code **)(*param_1 + 0x48))(param_1,0xfffffffffffffc44);
    return lVar8;
  }
  lVar8 = param_1[0xb];
  *(undefined1 *)((long)param_1 + 0x8d) = 0;
  if (lVar8 == -1) {
    bVar1 = true;
  }
  else if (lVar8 < 1) {
    bVar1 = false;
  }
  else {
    bVar1 = param_1[0x10] < lVar8;
  }
  plVar9 = param_1 + 0x11;
  uVar5 = (long)(int)*plVar9;
  if (param_2 != 0) {
    if (param_2 <= (ulong)(long)(int)*plVar9) goto code_r0x02335a0c;
    uVar5 = (long)(int)*plVar9;
  }
  param_2 = uVar5;
  if (param_2 == 0) {
    return 0;
  }
code_r0x02335a0c:
  lVar8 = (**(code **)(*(long *)param_1[8] + 0xa0))((long *)param_1[8],param_2);
  if ((-1 < lVar8) || (lVar8 == -0x3c1)) {
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(plVar9,0x10);
      if (bVar4) {
        *(int *)plVar9 = (int)*plVar9 - (int)lVar8;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
    if (bVar1) {
      iVar6 = 8;
      if (*(uint *)((long)param_1 + 0x14) < *(uint *)(param_1 + 2)) {
        iVar6 = -1;
      }
      if (0 < ((int)param_1[2] + iVar6) - *(int *)((long)param_1 + 0x14)) {
        iVar6 = (iVar6 + (int)param_1[2] + 1) - *(int *)((long)param_1 + 0x14);
        iVar7 = *(int *)((long)param_1 + 0x14);
        do {
          iVar2 = 0;
          if (iVar7 < 8) {
            iVar2 = iVar7 + 1;
          }
          if (iVar2 == (int)param_1[2]) {
            return lVar8;
          }
          iVar7 = *(int *)((long)param_1 + (long)iVar2 * 4 + 0x18) - (int)lVar8;
          *(int *)((long)param_1 + (long)iVar2 * 4 + 0x18) = iVar7;
          if (iVar7 < 1) {
            if ((*(int *)((long)param_1 + 0x14) + 1 != (int)param_1[2]) &&
               (*(int *)((long)param_1 + 0x14) = *(int *)((long)param_1 + 0x14) + 1,
               8 < *(uint *)((long)param_1 + 0x14))) {
              *(undefined4 *)((long)param_1 + 0x14) = 0;
            }
            *(undefined1 *)((long)param_1 + 0x8d) = 1;
            param_1[0x10] = param_1[0x10] + 1;
          }
          iVar6 = iVar6 + -1;
          iVar7 = iVar2;
        } while (1 < iVar6);
      }
    }
  }
  return lVar8;
}

// ==== Aska::MultiMediaStream::IsBufferable(int, unsigned long, long*) const
// vaddr 0x2235b1c | ghidra 0x2335b1c | size 312 | symbol _ZNK4Aska16MultiMediaStream12IsBufferableEimPl | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK4Aska16MultiMediaStream12IsBufferableEimPl
               (long *param_1,int param_2,ulong param_3,ulong *param_4)

{
  bool bVar1;
  ulong uVar2;
  long lVar3;
  ulong uVar4;
  
  uVar2 = (**(code **)(*param_1 + 0xb0))();
  if ((uVar2 & 1) == 0) {
    (**(code **)(*param_1 + 0x48))(param_1,0xfffffffffffffc44);
    if (param_4 == (ulong *)0x0) {
      return false;
    }
    *param_4 = 0xfffffffffffffc44;
    return false;
  }
  uVar2 = (**(code **)(*(long *)param_1[8] + 0xa8))((long *)param_1[8],param_2,param_3,param_4);
  if ((uVar2 & 1) == 0) {
code_r0x02335c34:
    bVar1 = false;
  }
  else {
    lVar3 = param_1[0xb];
    if (param_2 == 0) {
      if ((lVar3 == -1) || ((0 < lVar3 && (param_1[0xf] < lVar3)))) {
        uVar4 = param_1[0xd];
        uVar2 = (**(code **)(*param_1 + 0x18))(param_1);
        if (-1 < (long)uVar2) {
          if (param_3 != 0) {
            return uVar2 + param_3 <= uVar4;
          }
          return uVar2 < uVar4;
        }
        if (param_4 != (ulong *)0x0) {
          *param_4 = uVar2;
          return false;
        }
        goto code_r0x02335c34;
      }
    }
    else if ((lVar3 == -1) || ((0 < lVar3 && (param_1[0x10] < lVar3)))) {
      if (param_3 != 0) {
        return param_3 <= (ulong)(long)(int)param_1[0x11];
      }
      return 0 < (int)param_1[0x11];
    }
    bVar1 = true;
  }
  return bVar1;
}

// ==== Aska::MultiMediaStream::IsBufferingEnd(int, long*) const
// vaddr 0x2235c54 | ghidra 0x2335c54 | size 224 | symbol _ZNK4Aska16MultiMediaStream14IsBufferingEndEiPl | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK4Aska16MultiMediaStream14IsBufferingEndEiPl(long *param_1,int param_2,ulong *param_3)

{
  bool bVar1;
  ulong uVar2;
  long lVar3;
  
  uVar2 = (**(code **)(*param_1 + 0xb0))();
  if ((uVar2 & 1) == 0) {
    (**(code **)(*param_1 + 0x48))(param_1,0xfffffffffffffc44);
    if (param_3 != (ulong *)0x0) {
      *param_3 = 0xfffffffffffffc44;
    }
  }
  else {
    uVar2 = (**(code **)(*param_1 + 0x18))(param_1);
    if (-1 < (long)uVar2) {
      if (param_3 != (ulong *)0x0) {
        *param_3 = 0;
      }
      lVar3 = param_1[0xb];
      if ((lVar3 == -1) || ((0 < lVar3 && (param_1[(long)param_2 + 0xf] < lVar3)))) {
        return false;
      }
      bVar1 = param_2 == 0 && (ulong)param_1[10] <= uVar2;
      if (param_2 == 0) {
        return bVar1;
      }
      if (uVar2 < (ulong)param_1[10]) {
        return bVar1;
      }
      return (int)param_1[0x11] == 0;
    }
    if (param_3 != (ulong *)0x0) {
      *param_3 = uVar2;
    }
  }
  return true;
}

// ==== Aska::MultiMediaStream::~MultiMediaStream()
// vaddr 0x2235d34 | ghidra 0x2335d34 | size 36 | symbol _ZN4Aska16MultiMediaStreamD2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16MultiMediaStreamD2Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska16MultiMediaStreamE_02cbd4c8 + 0x10);
  if (param_1[8] != 0) {
    *(undefined1 *)((long)param_1 + 0x8e) = 0;
    param_1[8] = 0;
  }
  return;
}

// ==== Aska::MultiMediaStream::~MultiMediaStream()
// vaddr 0x2235d58 | ghidra 0x2335d58 | size 20 | symbol _ZN4Aska16MultiMediaStreamD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16MultiMediaStreamD0Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska16MultiMediaStreamE_02cbd4c8 + 0x10);
  (*(code *)PTR__ZdlPv_02ca4758)();
  return;
}


// FAILED to create function at 02972010 typeinfo name for Aska::TPoolAtomicDynamic<Aska::DiscReadStream::ReadAsyncNotify>
// FAILED to create function at 02972060 typeinfo name for Aska::TPoolAtomic<Aska::StreamingStream::BufferingNotify, 9>
// FAILED to create function at 029720b0 typeinfo name for Aska::StreamingStream::WorkerThread
// FAILED to create function at 029720e0 typeinfo name for Aska::TWorkerThreadBase<Aska::StreamingStream::WorkerThread>
// FAILED to create function at 02972120 typeinfo name for Aska::TQueue<Aska::StreamingStream::WorkerThread::Request, 9>
// FAILED to create function at 029724a0 typeinfo name for Aska::StreamingStream::BufferingNotify
// FAILED to create function at 029d8bf0 typeinfo name for Aska::DiscReadStream::ReadNotify
// FAILED to create function at 029d8c20 typeinfo name for Aska::DiscReadStream::ReadAsyncNotify
// FAILED to create function at 02ad4158 Aska::File::vtable
// FAILED to create function at 02ad4178 Aska::File::typeinfo
// FAILED to create function at 02baeef8 Aska::IStream::typeinfo
// FAILED to create function at 02bb05c8 Aska::FileStream::vtable
// FAILED to create function at 02bb0670 Aska::FileStream::typeinfo
// FAILED to create function at 02bb3ad8 Aska::TPoolAtomicDynamic<Aska::DiscReadStream::ReadAsyncNotify>::vtable
// FAILED to create function at 02bb3af8 Aska::TPoolAtomicDynamic<Aska::DiscReadStream::ReadAsyncNotify>::typeinfo
// FAILED to create function at 02bb3b08 Aska::TPoolAtomic<Aska::StreamingStream::BufferingNotify,9>::vtable
// FAILED to create function at 02bb3b28 Aska::TPoolAtomic<Aska::StreamingStream::BufferingNotify,9>::typeinfo
// FAILED to create function at 02bb3b38 Aska::StreamingStream::WorkerThread::vtable
// FAILED to create function at 02bb3b60 Aska::TWorkerThreadBase<Aska::StreamingStream::WorkerThread>::typeinfo
// FAILED to create function at 02bb3b80 Aska::StreamingStream::WorkerThread::typeinfo
// FAILED to create function at 02bb3b98 Aska::TWorkerThreadBase<Aska::StreamingStream::WorkerThread>::vtable
// FAILED to create function at 02bb3bc0 Aska::TQueue<Aska::StreamingStream::WorkerThread::Request,9>::vtable
// FAILED to create function at 02bb3be0 Aska::TQueue<Aska::StreamingStream::WorkerThread::Request,9>::typeinfo
// FAILED to create function at 02bb3fe8 Aska::StaticStream::vtable
// FAILED to create function at 02bb40e0 Aska::StaticStream::typeinfo
// FAILED to create function at 02bb40f8 Aska::StreamingStream::vtable
// FAILED to create function at 02bb41d0 Aska::StreamingStream::typeinfo
// FAILED to create function at 02bb41e8 Aska::StreamingStream::BufferingNotify::vtable
// FAILED to create function at 02bb4210 Aska::StreamingStream::BufferingNotify::typeinfo
// FAILED to create function at 02c5e058 Aska::DiscReadStream::vtable
// FAILED to create function at 02c5e100 Aska::DiscReadStream::typeinfo
// FAILED to create function at 02c5e118 Aska::DiscReadStream::ReadNotify::vtable
// FAILED to create function at 02c5e140 Aska::DiscReadStream::ReadNotify::typeinfo
// FAILED to create function at 02c5e158 Aska::DiscReadStream::ReadAsyncNotify::vtable
// FAILED to create function at 02c5e180 Aska::DiscReadStream::ReadAsyncNotify::typeinfo
// FAILED to create function at 02c5eb28 Aska::MultiMediaStream::vtable
// FAILED to create function at 02c5ec00 Aska::MultiMediaStream::typeinfo
// FAILED to create function at 02dc1e38 Aska::File::ms_LastError
