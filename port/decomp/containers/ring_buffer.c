// port/decomp/containers/ring_buffer.c: Ghidra decompiles for the containers subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-04 05:15 UTC: tools/decomp.sh '--into' 'containers/pool_fast' 'Aska::TPoolFast<Aska::Vector, false>::' 'Aska::RingBuffer::'

// ==== Aska::RingBuffer::Open(void const*, unsigned long)
// vaddr 0x2222e68 | ghidra 0x2322e68 | size 132 | symbol _ZN4Aska10RingBuffer4OpenEPKvm | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska10RingBuffer4OpenEPKvm(long *param_1,long param_2,long param_3)

{
  int iVar1;
  char cVar2;
  bool bVar3;
  int *piVar4;
  
  if (param_1[2] != 0) {
    return 0;
  }
  if (param_2 == 0) {
    return 0;
  }
  if (param_3 == 0) {
    return 0;
  }
  if (*param_1 == 0) goto code_r0x02322ed0;
  piVar4 = (int *)param_1[1];
  if (piVar4 == (int *)0x0) {
code_r0x02322ebc:
    operator delete[](void*)();
code_r0x02322ec0:
    if (param_1[1] != 0) {
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
      if (*param_1 != 0) goto code_r0x02322ebc;
      goto code_r0x02322ec0;
    }
  }
  *param_1 = 0;
  param_1[1] = 0;
code_r0x02322ed0:
  param_1[2] = param_2;
  param_1[3] = param_3;
  param_1[4] = 0;
  param_1[5] = 0;
  *(undefined4 *)(param_1 + 6) = 0;
  return 1;
}

// ==== Aska::RingBuffer::Reset()
// vaddr 0x2222eec | ghidra 0x2322eec | size 12 | symbol _ZN4Aska10RingBuffer5ResetEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10RingBuffer5ResetEv(long param_1)

{
  *(undefined8 *)(param_1 + 0x20) = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  *(undefined4 *)(param_1 + 0x30) = 0;
  return;
}

// ==== Aska::RingBuffer::Open(unsigned long)
// vaddr 0x2222ef8 | ghidra 0x2322ef8 | size 208 | symbol _ZN4Aska10RingBuffer4OpenEm | lib libSOA-3.7.0.so | 2026-10-04
bool _ZN4Aska10RingBuffer4OpenEm(long *param_1,long param_2)

{
  int iVar1;
  char cVar2;
  bool bVar3;
  long lVar4;
  long lVar5;
  int *piVar6;
  
  if (param_2 == 0) {
    return false;
  }
  if (param_1[2] != 0) {
    return false;
  }
  lVar4 = operator new[](unsigned long, std::nothrow_t const&)(param_2,PTR__ZSt7nothrow_02cb9a80);
  lVar5 = *param_1;
  if (lVar5 == lVar4) goto code_r0x02322f9c;
  piVar6 = (int *)param_1[1];
  if (piVar6 == (int *)0x0) {
code_r0x02322f58:
    if (lVar5 != 0) {
      operator delete[](void*)(lVar5);
    }
    if (param_1[1] != 0) {
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
      lVar5 = *param_1;
      goto code_r0x02322f58;
    }
  }
  *param_1 = 0;
  param_1[1] = 0;
  if (lVar4 != 0) {
    piVar6 = (int *)Aska::TSharedPointerCode::CreateCounter(int)(0);
    param_1[1] = (long)piVar6;
    if (piVar6 != (int *)0x0) {
      *param_1 = lVar4;
      do {
        cVar2 = '\x01';
        bVar3 = (bool)ExclusiveMonitorPass(piVar6,0x10);
        if (bVar3) {
          *piVar6 = *piVar6 + 1;
          cVar2 = ExclusiveMonitorsStatus();
        }
      } while (cVar2 != '\0');
    }
  }
code_r0x02322f9c:
  lVar4 = *param_1;
  if (lVar4 != 0) {
    param_1[2] = lVar4;
    param_1[3] = param_2;
    param_1[4] = 0;
    param_1[5] = 0;
    *(undefined4 *)(param_1 + 6) = 0;
  }
  return lVar4 != 0;
}

// ==== Aska::RingBuffer::Close()
// vaddr 0x2222fc8 | ghidra 0x2322fc8 | size 28 | symbol _ZN4Aska10RingBuffer5CloseEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10RingBuffer5CloseEv(long param_1)

{
  if (*(long *)(param_1 + 0x10) != 0) {
    *(undefined8 *)(param_1 + 0x18) = 0;
    *(long *)(param_1 + 0x10) = 0;
    *(undefined8 *)(param_1 + 0x28) = 0;
    *(undefined8 *)(param_1 + 0x20) = 0;
    *(undefined4 *)(param_1 + 0x30) = 0;
  }
  return;
}

// ==== Aska::RingBuffer::PushFront(void const*, unsigned long)
// vaddr 0x2222fe4 | ghidra 0x2322fe4 | size 212 | symbol _ZN4Aska10RingBuffer9PushFrontEPKvm | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska10RingBuffer9PushFrontEPKvm(long param_1,undefined8 param_2,long param_3)

{
  int *piVar1;
  ulong uVar2;
  char cVar3;
  bool bVar4;
  ulong uVar5;
  ulong uVar6;
  long lVar7;
  
  if (param_3 == 0) {
    return 0;
  }
  uVar2 = *(ulong *)(param_1 + 0x20);
  uVar6 = *(ulong *)(param_1 + 0x28);
  if ((uVar2 == uVar6) && (0 < *(int *)(param_1 + 0x30))) {
code_r0x02323024:
    param_3 = 0;
  }
  else {
    if (uVar2 < uVar6) {
      if (uVar6 < uVar2 + param_3) goto code_r0x02323024;
      lVar7 = *(long *)(param_1 + 0x10) + uVar2;
    }
    else {
      lVar7 = *(long *)(param_1 + 0x10) + uVar2;
      if ((*(ulong *)(param_1 + 0x18) < uVar2 + param_3) &&
         (param_3 = *(ulong *)(param_1 + 0x18) - uVar2, param_3 == 0)) {
        return 0;
      }
    }
    memcpy(lVar7,param_2,param_3);
    uVar6 = *(ulong *)(param_1 + 0x18);
    uVar2 = *(long *)(param_1 + 0x20) + param_3;
    if ((long)uVar2 < 0) {
      uVar5 = 0;
      if (uVar6 != 0) {
        uVar5 = -uVar2 / uVar6;
      }
      lVar7 = uVar6 - (-uVar2 - uVar5 * uVar6);
    }
    else {
      uVar5 = 0;
      if (uVar6 != 0) {
        uVar5 = uVar2 / uVar6;
      }
      lVar7 = uVar2 - uVar5 * uVar6;
    }
    *(long *)(param_1 + 0x20) = lVar7;
    piVar1 = (int *)(param_1 + 0x30);
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + (int)param_3;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
  }
  return param_3;
}

// ==== Aska::RingBuffer::PrivatePeepPushFront(void**, unsigned long) const
// vaddr 0x22230b8 | ghidra 0x23230b8 | size 144 | symbol _ZNK4Aska10RingBuffer20PrivatePeepPushFrontEPPvm | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK4Aska10RingBuffer20PrivatePeepPushFrontEPPvm(long param_1,long *param_2,long param_3)

{
  ulong uVar1;
  ulong uVar2;
  long lVar3;
  
  lVar3 = 0;
  if ((param_2 != (long *)0x0) && (param_3 != 0)) {
    uVar1 = *(ulong *)(param_1 + 0x20);
    uVar2 = *(ulong *)(param_1 + 0x28);
    if ((uVar1 == uVar2) && (0 < *(int *)(param_1 + 0x30))) {
      return 0;
    }
    lVar3 = param_3;
    if (uVar1 < uVar2) {
      if (uVar2 < uVar1 + param_3) {
        return 0;
      }
      *param_2 = *(long *)(param_1 + 0x10) + uVar1;
    }
    else {
      uVar2 = *(ulong *)(param_1 + 0x18);
      *param_2 = *(long *)(param_1 + 0x10) + uVar1;
      if (uVar2 < uVar1 + param_3) {
        return *(long *)(param_1 + 0x18) - uVar1;
      }
    }
  }
  return lVar3;
}

// ==== Aska::RingBuffer::PopFront(void*, unsigned long)
// vaddr 0x2223148 | ghidra 0x2323148 | size 212 | symbol _ZN4Aska10RingBuffer8PopFrontEPvm | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZN4Aska10RingBuffer8PopFrontEPvm(long param_1,undefined8 param_2,ulong param_3)

{
  int *piVar1;
  ulong uVar2;
  char cVar3;
  bool bVar4;
  ulong uVar5;
  long lVar6;
  ulong uVar7;
  
  if (param_3 == 0) {
    return 0;
  }
  uVar2 = *(ulong *)(param_1 + 0x20);
  uVar7 = *(ulong *)(param_1 + 0x28);
  if ((uVar2 == uVar7) && (*(int *)(param_1 + 0x30) == 0)) {
code_r0x02323184:
    param_3 = 0;
  }
  else {
    if (uVar7 < uVar2) {
      if (uVar2 < uVar7 + param_3) goto code_r0x02323184;
      lVar6 = (uVar2 - param_3) + *(long *)(param_1 + 0x10);
    }
    else {
      lVar6 = *(long *)(param_1 + 0x10);
      if (uVar2 < param_3) {
        param_3 = uVar2;
        if (uVar2 == 0) {
          return 0;
        }
      }
      else {
        lVar6 = (uVar2 - param_3) + lVar6;
      }
    }
    memcpy(param_2,lVar6,param_3);
    uVar2 = *(ulong *)(param_1 + 0x18);
    uVar7 = *(long *)(param_1 + 0x20) - param_3;
    if ((long)uVar7 < 0) {
      uVar5 = 0;
      if (uVar2 != 0) {
        uVar5 = -uVar7 / uVar2;
      }
      lVar6 = uVar2 - (-uVar7 - uVar5 * uVar2);
    }
    else {
      uVar5 = 0;
      if (uVar2 != 0) {
        uVar5 = uVar7 / uVar2;
      }
      lVar6 = uVar7 - uVar5 * uVar2;
    }
    *(long *)(param_1 + 0x20) = lVar6;
    piVar1 = (int *)(param_1 + 0x30);
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 - (int)param_3;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
  }
  return param_3;
}

// ==== Aska::RingBuffer::PrivatePeepPopFront(void**, unsigned long) const
// vaddr 0x222321c | ghidra 0x232321c | size 116 | symbol _ZNK4Aska10RingBuffer19PrivatePeepPopFrontEPPvm | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZNK4Aska10RingBuffer19PrivatePeepPopFrontEPPvm(long param_1,long *param_2,ulong param_3)

{
  ulong uVar1;
  ulong uVar2;
  long lVar3;
  
  uVar2 = 0;
  if ((param_2 != (long *)0x0) && (param_3 != 0)) {
    uVar2 = *(ulong *)(param_1 + 0x20);
    uVar1 = *(ulong *)(param_1 + 0x28);
    if ((uVar2 == uVar1) && (*(int *)(param_1 + 0x30) == 0)) {
      return 0;
    }
    if (uVar1 < uVar2) {
      if (uVar2 < uVar1 + param_3) {
        return 0;
      }
      lVar3 = *(long *)(param_1 + 0x10);
    }
    else {
      lVar3 = *(long *)(param_1 + 0x10);
      if (uVar2 < param_3) {
        *param_2 = lVar3;
        return uVar2;
      }
    }
    *param_2 = (uVar2 - param_3) + lVar3;
    uVar2 = param_3;
  }
  return uVar2;
}

// ==== Aska::RingBuffer::PushBack(void const*, unsigned long)
// vaddr 0x2223290 | ghidra 0x2323290 | size 208 | symbol _ZN4Aska10RingBuffer8PushBackEPKvm | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZN4Aska10RingBuffer8PushBackEPKvm(long param_1,undefined8 param_2,ulong param_3)

{
  int *piVar1;
  char cVar2;
  bool bVar3;
  ulong uVar4;
  ulong uVar5;
  long lVar6;
  ulong uVar7;
  
  if (param_3 == 0) {
    return 0;
  }
  uVar5 = *(ulong *)(param_1 + 0x20);
  uVar7 = *(ulong *)(param_1 + 0x28);
  if ((uVar5 == uVar7) && (0 < *(int *)(param_1 + 0x30))) {
code_r0x023232d0:
    param_3 = 0;
  }
  else {
    if (uVar5 < uVar7) {
      if (uVar7 < uVar5 + param_3) goto code_r0x023232d0;
      lVar6 = (uVar7 - param_3) + *(long *)(param_1 + 0x10);
    }
    else {
      lVar6 = *(long *)(param_1 + 0x10);
      if (uVar7 < param_3) {
        param_3 = uVar7;
        if (uVar7 == 0) {
          return 0;
        }
      }
      else {
        lVar6 = (uVar7 - param_3) + lVar6;
      }
    }
    memcpy(lVar6,param_2,param_3);
    uVar5 = *(ulong *)(param_1 + 0x18);
    uVar7 = *(long *)(param_1 + 0x28) - param_3;
    if ((long)uVar7 < 0) {
      uVar4 = 0;
      if (uVar5 != 0) {
        uVar4 = -uVar7 / uVar5;
      }
      lVar6 = uVar5 - (-uVar7 - uVar4 * uVar5);
    }
    else {
      uVar4 = 0;
      if (uVar5 != 0) {
        uVar4 = uVar7 / uVar5;
      }
      lVar6 = uVar7 - uVar4 * uVar5;
    }
    *(long *)(param_1 + 0x28) = lVar6;
    piVar1 = (int *)(param_1 + 0x30);
    do {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar3) {
        *piVar1 = *piVar1 + (int)param_3;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
  }
  return param_3;
}

// ==== Aska::RingBuffer::PrivatePeepPushBack(void**, unsigned long) const
// vaddr 0x2223360 | ghidra 0x2323360 | size 120 | symbol _ZNK4Aska10RingBuffer19PrivatePeepPushBackEPPvm | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZNK4Aska10RingBuffer19PrivatePeepPushBackEPPvm(long param_1,long *param_2,ulong param_3)

{
  ulong uVar1;
  ulong uVar2;
  long lVar3;
  
  uVar2 = 0;
  if ((param_2 != (long *)0x0) && (param_3 != 0)) {
    uVar2 = *(ulong *)(param_1 + 0x20);
    uVar1 = *(ulong *)(param_1 + 0x28);
    if ((uVar2 == uVar1) && (0 < *(int *)(param_1 + 0x30))) {
      return 0;
    }
    if (uVar2 < uVar1) {
      if (uVar1 < uVar2 + param_3) {
        return 0;
      }
      lVar3 = *(long *)(param_1 + 0x10);
    }
    else {
      lVar3 = *(long *)(param_1 + 0x10);
      if (uVar1 < param_3) {
        *param_2 = lVar3;
        return uVar1;
      }
    }
    *param_2 = (uVar1 - param_3) + lVar3;
    uVar2 = param_3;
  }
  return uVar2;
}

// ==== Aska::RingBuffer::PopBack(void*, unsigned long)
// vaddr 0x22233d8 | ghidra 0x23233d8 | size 220 | symbol _ZN4Aska10RingBuffer7PopBackEPvm | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska10RingBuffer7PopBackEPvm(long param_1,undefined8 param_2,long param_3)

{
  int *piVar1;
  ulong uVar2;
  char cVar3;
  bool bVar4;
  ulong uVar5;
  ulong uVar6;
  long lVar7;
  
  if (param_3 == 0) {
    return 0;
  }
  uVar2 = *(ulong *)(param_1 + 0x20);
  uVar6 = *(ulong *)(param_1 + 0x28);
  if ((uVar2 == uVar6) && (*(int *)(param_1 + 0x30) == 0)) {
code_r0x02323414:
    param_3 = 0;
  }
  else {
    if (uVar6 < uVar2) {
      if (uVar2 < uVar6 + param_3) goto code_r0x02323414;
      lVar7 = *(long *)(param_1 + 0x10) + uVar6;
    }
    else {
      lVar7 = *(long *)(param_1 + 0x10) + uVar6;
      if ((*(ulong *)(param_1 + 0x18) < uVar6 + param_3) &&
         (param_3 = *(ulong *)(param_1 + 0x18) - uVar6, param_3 == 0)) {
        return 0;
      }
    }
    memcpy(param_2,lVar7,param_3);
    uVar6 = *(ulong *)(param_1 + 0x18);
    uVar2 = *(long *)(param_1 + 0x28) + param_3;
    if ((long)uVar2 < 0) {
      uVar5 = 0;
      if (uVar6 != 0) {
        uVar5 = -uVar2 / uVar6;
      }
      lVar7 = uVar6 - (-uVar2 - uVar5 * uVar6);
    }
    else {
      uVar5 = 0;
      if (uVar6 != 0) {
        uVar5 = uVar2 / uVar6;
      }
      lVar7 = uVar2 - uVar5 * uVar6;
    }
    *(long *)(param_1 + 0x28) = lVar7;
    piVar1 = (int *)(param_1 + 0x30);
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 - (int)param_3;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
  }
  return param_3;
}

// ==== Aska::RingBuffer::PrivatePeepPopBack(void**, unsigned long) const
// vaddr 0x22234b4 | ghidra 0x23234b4 | size 140 | symbol _ZNK4Aska10RingBuffer18PrivatePeepPopBackEPPvm | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK4Aska10RingBuffer18PrivatePeepPopBackEPPvm(long param_1,long *param_2,long param_3)

{
  ulong uVar1;
  ulong uVar2;
  long lVar3;
  
  lVar3 = 0;
  if ((param_2 != (long *)0x0) && (param_3 != 0)) {
    uVar1 = *(ulong *)(param_1 + 0x20);
    uVar2 = *(ulong *)(param_1 + 0x28);
    if ((uVar1 == uVar2) && (*(int *)(param_1 + 0x30) == 0)) {
      return 0;
    }
    if (uVar2 < uVar1) {
      if (uVar1 < uVar2 + param_3) {
        return 0;
      }
      *param_2 = *(long *)(param_1 + 0x10) + uVar2;
      return param_3;
    }
    uVar1 = *(ulong *)(param_1 + 0x18);
    *param_2 = *(long *)(param_1 + 0x10) + uVar2;
    lVar3 = param_3;
    if (uVar1 < uVar2 + param_3) {
      lVar3 = *(long *)(param_1 + 0x18) - uVar2;
    }
  }
  return lVar3;
}

// ==== Aska::RingBuffer::PushFront(void**, unsigned long)
// vaddr 0x2223540 | ghidra 0x2323540 | size 200 | symbol _ZN4Aska10RingBuffer9PushFrontEPPvm | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska10RingBuffer9PushFrontEPPvm(long param_1,long *param_2,long param_3)

{
  int *piVar1;
  ulong uVar2;
  char cVar3;
  bool bVar4;
  ulong uVar5;
  ulong uVar6;
  long lVar7;
  
  if (param_3 != 0) {
    uVar2 = *(ulong *)(param_1 + 0x20);
    uVar6 = *(ulong *)(param_1 + 0x28);
    if ((uVar2 == uVar6) && (0 < *(int *)(param_1 + 0x30))) {
      return 0;
    }
    if (uVar2 < uVar6) {
      if (uVar6 < uVar2 + param_3) {
        return 0;
      }
      lVar7 = *(long *)(param_1 + 0x10) + uVar2;
    }
    else {
      lVar7 = *(long *)(param_1 + 0x10) + uVar2;
      if ((*(ulong *)(param_1 + 0x18) < uVar2 + param_3) &&
         (param_3 = *(ulong *)(param_1 + 0x18) - uVar2, param_3 == 0)) {
        return 0;
      }
    }
    *param_2 = lVar7;
    uVar6 = *(ulong *)(param_1 + 0x18);
    uVar2 = *(long *)(param_1 + 0x20) + param_3;
    if ((long)uVar2 < 0) {
      uVar5 = 0;
      if (uVar6 != 0) {
        uVar5 = -uVar2 / uVar6;
      }
      lVar7 = uVar6 - (-uVar2 - uVar5 * uVar6);
    }
    else {
      uVar5 = 0;
      if (uVar6 != 0) {
        uVar5 = uVar2 / uVar6;
      }
      lVar7 = uVar2 - uVar5 * uVar6;
    }
    *(long *)(param_1 + 0x20) = lVar7;
    piVar1 = (int *)(param_1 + 0x30);
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + (int)param_3;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
  }
  return param_3;
}

// ==== Aska::RingBuffer::PopFront(void**, unsigned long)
// vaddr 0x2223608 | ghidra 0x2323608 | size 192 | symbol _ZN4Aska10RingBuffer8PopFrontEPPvm | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZN4Aska10RingBuffer8PopFrontEPPvm(long param_1,long *param_2,ulong param_3)

{
  int *piVar1;
  ulong uVar2;
  char cVar3;
  bool bVar4;
  ulong uVar5;
  long lVar6;
  ulong uVar7;
  
  if (param_3 != 0) {
    uVar2 = *(ulong *)(param_1 + 0x20);
    uVar7 = *(ulong *)(param_1 + 0x28);
    if ((uVar2 == uVar7) && (*(int *)(param_1 + 0x30) == 0)) {
      return 0;
    }
    if (uVar7 < uVar2) {
      if (uVar2 < uVar7 + param_3) {
        return 0;
      }
      lVar6 = (uVar2 - param_3) + *(long *)(param_1 + 0x10);
    }
    else {
      lVar6 = *(long *)(param_1 + 0x10);
      if (uVar2 < param_3) {
        param_3 = uVar2;
        if (uVar2 == 0) {
          return 0;
        }
      }
      else {
        lVar6 = (uVar2 - param_3) + lVar6;
      }
    }
    *param_2 = lVar6;
    uVar2 = *(ulong *)(param_1 + 0x18);
    uVar7 = *(long *)(param_1 + 0x20) - param_3;
    if ((long)uVar7 < 0) {
      uVar5 = 0;
      if (uVar2 != 0) {
        uVar5 = -uVar7 / uVar2;
      }
      lVar6 = uVar2 - (-uVar7 - uVar5 * uVar2);
    }
    else {
      uVar5 = 0;
      if (uVar2 != 0) {
        uVar5 = uVar7 / uVar2;
      }
      lVar6 = uVar7 - uVar5 * uVar2;
    }
    *(long *)(param_1 + 0x20) = lVar6;
    piVar1 = (int *)(param_1 + 0x30);
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 - (int)param_3;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
  }
  return param_3;
}

// ==== Aska::RingBuffer::PushBack(void**, unsigned long)
// vaddr 0x22236c8 | ghidra 0x23236c8 | size 196 | symbol _ZN4Aska10RingBuffer8PushBackEPPvm | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZN4Aska10RingBuffer8PushBackEPPvm(long param_1,long *param_2,ulong param_3)

{
  int *piVar1;
  char cVar2;
  bool bVar3;
  ulong uVar4;
  ulong uVar5;
  long lVar6;
  ulong uVar7;
  
  if (param_3 != 0) {
    uVar5 = *(ulong *)(param_1 + 0x20);
    uVar7 = *(ulong *)(param_1 + 0x28);
    if ((uVar5 == uVar7) && (0 < *(int *)(param_1 + 0x30))) {
      return 0;
    }
    if (uVar5 < uVar7) {
      if (uVar7 < uVar5 + param_3) {
        return 0;
      }
      lVar6 = (uVar7 - param_3) + *(long *)(param_1 + 0x10);
    }
    else {
      lVar6 = *(long *)(param_1 + 0x10);
      if (uVar7 < param_3) {
        param_3 = uVar7;
        if (uVar7 == 0) {
          return 0;
        }
      }
      else {
        lVar6 = (uVar7 - param_3) + lVar6;
      }
    }
    *param_2 = lVar6;
    uVar5 = *(ulong *)(param_1 + 0x18);
    uVar7 = *(long *)(param_1 + 0x28) - param_3;
    if ((long)uVar7 < 0) {
      uVar4 = 0;
      if (uVar5 != 0) {
        uVar4 = -uVar7 / uVar5;
      }
      lVar6 = uVar5 - (-uVar7 - uVar4 * uVar5);
    }
    else {
      uVar4 = 0;
      if (uVar5 != 0) {
        uVar4 = uVar7 / uVar5;
      }
      lVar6 = uVar7 - uVar4 * uVar5;
    }
    *(long *)(param_1 + 0x28) = lVar6;
    piVar1 = (int *)(param_1 + 0x30);
    do {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar3) {
        *piVar1 = *piVar1 + (int)param_3;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
  }
  return param_3;
}

// ==== Aska::RingBuffer::PopBack(void**, unsigned long)
// vaddr 0x222378c | ghidra 0x232378c | size 200 | symbol _ZN4Aska10RingBuffer7PopBackEPPvm | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska10RingBuffer7PopBackEPPvm(long param_1,long *param_2,long param_3)

{
  int *piVar1;
  ulong uVar2;
  char cVar3;
  bool bVar4;
  ulong uVar5;
  ulong uVar6;
  long lVar7;
  
  if (param_3 != 0) {
    uVar2 = *(ulong *)(param_1 + 0x20);
    uVar6 = *(ulong *)(param_1 + 0x28);
    if ((uVar2 == uVar6) && (*(int *)(param_1 + 0x30) == 0)) {
      return 0;
    }
    if (uVar6 < uVar2) {
      if (uVar2 < uVar6 + param_3) {
        return 0;
      }
      lVar7 = *(long *)(param_1 + 0x10) + uVar6;
    }
    else {
      lVar7 = *(long *)(param_1 + 0x10) + uVar6;
      if ((*(ulong *)(param_1 + 0x18) < uVar6 + param_3) &&
         (param_3 = *(ulong *)(param_1 + 0x18) - uVar6, param_3 == 0)) {
        return 0;
      }
    }
    *param_2 = lVar7;
    uVar6 = *(ulong *)(param_1 + 0x18);
    uVar2 = *(long *)(param_1 + 0x28) + param_3;
    if ((long)uVar2 < 0) {
      uVar5 = 0;
      if (uVar6 != 0) {
        uVar5 = -uVar2 / uVar6;
      }
      lVar7 = uVar6 - (-uVar2 - uVar5 * uVar6);
    }
    else {
      uVar5 = 0;
      if (uVar6 != 0) {
        uVar5 = uVar2 / uVar6;
      }
      lVar7 = uVar2 - uVar5 * uVar6;
    }
    *(long *)(param_1 + 0x28) = lVar7;
    piVar1 = (int *)(param_1 + 0x30);
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 - (int)param_3;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
  }
  return param_3;
}
