// port/decomp/memory/stl_allocator.c: Ghidra decompiles for the memory subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-04 05:04 UTC: tools/decomp.sh '--into' 'memory/stl_allocator' 'Framework::CAssignedMemoryManager' 'Framework::CFixedLengthAllocatorContainer::' 'Framework::TFixedLengthAllocator<' 'Framework::IFixedLengthAllocator'

// ==== Framework::TFixedLengthAllocator<16ul>::TFixedLengthAllocator(char, char, char, unsigned long)
// vaddr 0x1142bcc | ghidra 0x1242bcc | size 268 | symbol _ZN9Framework21TFixedLengthAllocatorILm16EEC2Ecccm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework21TFixedLengthAllocatorILm16EEC2Ecccm
               (long *param_1,undefined1 param_2,undefined1 param_3,undefined1 param_4,long param_5)

{
  uint uVar1;
  undefined2 *puVar2;
  undefined1 uVar3;
  undefined1 auVar4 [16];
  undefined *puVar5;
  long lVar6;
  long lVar7;
  ulong uVar8;
  
  puVar5 = PTR__ZTVN9Framework21TFixedLengthAllocatorILm16EEE_02cc39b0;
  *(undefined1 *)(param_1 + 3) = param_2;
  *(undefined1 *)((long)param_1 + 0x19) = param_3;
  *(undefined1 *)((long)param_1 + 0x1a) = param_4;
  *(undefined1 *)((long)param_1 + 0x1b) = 0;
  param_1[4] = param_5;
  *(undefined8 *)((long)param_1 + 0x34) = 0;
  *(undefined1 *)(param_1 + 6) = 1;
  *param_1 = (long)(puVar5 + 0x10);
  param_1[8] = 0;
  lVar6 = operator new(unsigned long, std::nothrow_t const&)(0xb0,PTR__ZSt7nothrow_02cb9a80);
  if (lVar6 != 0) {
    Framework::CMutex::CMutex()(lVar6);
  }
  param_1[8] = lVar6;
  Framework::CMutex::Initialize()(lVar6);
  uVar8 = param_1[4];
  auVar4._8_8_ = 0;
  auVar4._0_8_ = uVar8;
  lVar6 = uVar8 << 5;
  if (SUB168(auVar4 * ZEXT816(0x20),8) != 0) {
    lVar6 = -1;
  }
  lVar6 = operator new[](unsigned long, std::nothrow_t const&)(lVar6,PTR__ZSt7nothrow_02cb9a80);
  param_1[5] = lVar6;
  memset(lVar6,0xcc,uVar8 << 5);
  if (uVar8 == 0) {
    lVar7 = -1;
  }
  else {
    uVar8 = 0;
    do {
      lVar7 = param_1[3];
      uVar3 = *(undefined1 *)((long)param_1 + 0x1a);
      puVar2 = (undefined2 *)(lVar6 + uVar8 * 0x20);
      *(int *)(puVar2 + 2) = (int)uVar8;
      uVar1 = (int)uVar8 + 1;
      uVar8 = (ulong)uVar1;
      *(undefined1 *)((long)puVar2 + 3) = 1;
      *puVar2 = (short)lVar7;
      *(undefined1 *)(puVar2 + 1) = uVar3;
      *(uint *)(puVar2 + 4) = uVar1;
      lVar6 = param_1[5];
    } while (uVar8 < (ulong)param_1[4]);
    lVar7 = param_1[4] - 1;
  }
  *(undefined4 *)(lVar6 + lVar7 * 0x20 + 8) = 0xffffffff;
  return;
}

// ==== Framework::TFixedLengthAllocator<32ul>::TFixedLengthAllocator(char, char, char, unsigned long)
// vaddr 0x1142cd8 | ghidra 0x1242cd8 | size 284 | symbol _ZN9Framework21TFixedLengthAllocatorILm32EEC2Ecccm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework21TFixedLengthAllocatorILm32EEC2Ecccm
               (long *param_1,undefined1 param_2,undefined1 param_3,undefined1 param_4,long param_5)

{
  uint uVar1;
  undefined1 uVar2;
  undefined1 auVar3 [16];
  undefined *puVar4;
  long lVar5;
  long lVar6;
  undefined2 *puVar7;
  ulong uVar8;
  
  puVar4 = PTR__ZTVN9Framework21TFixedLengthAllocatorILm32EEE_02cb6fd0;
  *(undefined1 *)(param_1 + 3) = param_2;
  *(undefined1 *)((long)param_1 + 0x19) = param_3;
  *(undefined1 *)((long)param_1 + 0x1a) = param_4;
  *(undefined1 *)((long)param_1 + 0x1b) = 0;
  param_1[4] = param_5;
  *(undefined8 *)((long)param_1 + 0x34) = 0;
  *(undefined1 *)(param_1 + 6) = 1;
  *param_1 = (long)(puVar4 + 0x10);
  param_1[8] = 0;
  lVar5 = operator new(unsigned long, std::nothrow_t const&)(0xb0,PTR__ZSt7nothrow_02cb9a80);
  if (lVar5 != 0) {
    Framework::CMutex::CMutex()(lVar5);
  }
  param_1[8] = lVar5;
  Framework::CMutex::Initialize()(lVar5);
  uVar8 = param_1[4];
  auVar3._8_8_ = 0;
  auVar3._0_8_ = uVar8;
  lVar5 = uVar8 * 0x30;
  if (SUB168(auVar3 * ZEXT816(0x30),8) != 0) {
    lVar5 = -1;
  }
  lVar5 = operator new[](unsigned long, std::nothrow_t const&)(lVar5,PTR__ZSt7nothrow_02cb9a80);
  param_1[5] = lVar5;
  memset(lVar5,0xcc,uVar8 * 0x30);
  if (uVar8 == 0) {
    lVar6 = -1;
  }
  else {
    uVar8 = 0;
    do {
      lVar6 = param_1[3];
      uVar2 = *(undefined1 *)((long)param_1 + 0x1a);
      puVar7 = (undefined2 *)(lVar5 + uVar8 * 0x30);
      *(int *)(puVar7 + 2) = (int)uVar8;
      uVar1 = (int)uVar8 + 1;
      uVar8 = (ulong)uVar1;
      *(undefined1 *)((long)puVar7 + 3) = 1;
      *puVar7 = (short)lVar6;
      *(undefined1 *)(puVar7 + 1) = uVar2;
      *(uint *)(puVar7 + 4) = uVar1;
      lVar5 = param_1[5];
    } while (uVar8 < (ulong)param_1[4]);
    lVar6 = param_1[4] - 1;
  }
  *(undefined4 *)(lVar5 + lVar6 * 0x30 + 8) = 0xffffffff;
  return;
}

// ==== Framework::TFixedLengthAllocator<64ul>::TFixedLengthAllocator(char, char, char, unsigned long)
// vaddr 0x1142df4 | ghidra 0x1242df4 | size 284 | symbol _ZN9Framework21TFixedLengthAllocatorILm64EEC2Ecccm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework21TFixedLengthAllocatorILm64EEC2Ecccm
               (long *param_1,undefined1 param_2,undefined1 param_3,undefined1 param_4,long param_5)

{
  uint uVar1;
  undefined1 uVar2;
  undefined1 auVar3 [16];
  undefined *puVar4;
  long lVar5;
  long lVar6;
  undefined2 *puVar7;
  ulong uVar8;
  
  puVar4 = PTR__ZTVN9Framework21TFixedLengthAllocatorILm64EEE_02cb8310;
  *(undefined1 *)(param_1 + 3) = param_2;
  *(undefined1 *)((long)param_1 + 0x19) = param_3;
  *(undefined1 *)((long)param_1 + 0x1a) = param_4;
  *(undefined1 *)((long)param_1 + 0x1b) = 0;
  param_1[4] = param_5;
  *(undefined8 *)((long)param_1 + 0x34) = 0;
  *(undefined1 *)(param_1 + 6) = 1;
  *param_1 = (long)(puVar4 + 0x10);
  param_1[8] = 0;
  lVar5 = operator new(unsigned long, std::nothrow_t const&)(0xb0,PTR__ZSt7nothrow_02cb9a80);
  if (lVar5 != 0) {
    Framework::CMutex::CMutex()(lVar5);
  }
  param_1[8] = lVar5;
  Framework::CMutex::Initialize()(lVar5);
  uVar8 = param_1[4];
  auVar3._8_8_ = 0;
  auVar3._0_8_ = uVar8;
  lVar5 = uVar8 * 0x50;
  if (SUB168(auVar3 * ZEXT816(0x50),8) != 0) {
    lVar5 = -1;
  }
  lVar5 = operator new[](unsigned long, std::nothrow_t const&)(lVar5,PTR__ZSt7nothrow_02cb9a80);
  param_1[5] = lVar5;
  memset(lVar5,0xcc,uVar8 * 0x50);
  if (uVar8 == 0) {
    lVar6 = -1;
  }
  else {
    uVar8 = 0;
    do {
      lVar6 = param_1[3];
      uVar2 = *(undefined1 *)((long)param_1 + 0x1a);
      puVar7 = (undefined2 *)(lVar5 + uVar8 * 0x50);
      *(int *)(puVar7 + 2) = (int)uVar8;
      uVar1 = (int)uVar8 + 1;
      uVar8 = (ulong)uVar1;
      *(undefined1 *)((long)puVar7 + 3) = 1;
      *puVar7 = (short)lVar6;
      *(undefined1 *)(puVar7 + 1) = uVar2;
      *(uint *)(puVar7 + 4) = uVar1;
      lVar5 = param_1[5];
    } while (uVar8 < (ulong)param_1[4]);
    lVar6 = param_1[4] - 1;
  }
  *(undefined4 *)(lVar5 + lVar6 * 0x50 + 8) = 0xffffffff;
  return;
}

// ==== Framework::TFixedLengthAllocator<128ul>::TFixedLengthAllocator(char, char, char, unsigned long)
// vaddr 0x1142f10 | ghidra 0x1242f10 | size 284 | symbol _ZN9Framework21TFixedLengthAllocatorILm128EEC2Ecccm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework21TFixedLengthAllocatorILm128EEC2Ecccm
               (long *param_1,undefined1 param_2,undefined1 param_3,undefined1 param_4,long param_5)

{
  uint uVar1;
  undefined1 uVar2;
  undefined1 auVar3 [16];
  undefined *puVar4;
  long lVar5;
  long lVar6;
  undefined2 *puVar7;
  ulong uVar8;
  
  puVar4 = PTR__ZTVN9Framework21TFixedLengthAllocatorILm128EEE_02cb8f48;
  *(undefined1 *)(param_1 + 3) = param_2;
  *(undefined1 *)((long)param_1 + 0x19) = param_3;
  *(undefined1 *)((long)param_1 + 0x1a) = param_4;
  *(undefined1 *)((long)param_1 + 0x1b) = 0;
  param_1[4] = param_5;
  *(undefined8 *)((long)param_1 + 0x34) = 0;
  *(undefined1 *)(param_1 + 6) = 1;
  *param_1 = (long)(puVar4 + 0x10);
  param_1[8] = 0;
  lVar5 = operator new(unsigned long, std::nothrow_t const&)(0xb0,PTR__ZSt7nothrow_02cb9a80);
  if (lVar5 != 0) {
    Framework::CMutex::CMutex()(lVar5);
  }
  param_1[8] = lVar5;
  Framework::CMutex::Initialize()(lVar5);
  uVar8 = param_1[4];
  auVar3._8_8_ = 0;
  auVar3._0_8_ = uVar8;
  lVar5 = uVar8 * 0x90;
  if (SUB168(auVar3 * ZEXT816(0x90),8) != 0) {
    lVar5 = -1;
  }
  lVar5 = operator new[](unsigned long, std::nothrow_t const&)(lVar5,PTR__ZSt7nothrow_02cb9a80);
  param_1[5] = lVar5;
  memset(lVar5,0xcc,uVar8 * 0x90);
  if (uVar8 == 0) {
    lVar6 = -1;
  }
  else {
    uVar8 = 0;
    do {
      lVar6 = param_1[3];
      uVar2 = *(undefined1 *)((long)param_1 + 0x1a);
      puVar7 = (undefined2 *)(lVar5 + uVar8 * 0x90);
      *(int *)(puVar7 + 2) = (int)uVar8;
      uVar1 = (int)uVar8 + 1;
      uVar8 = (ulong)uVar1;
      *(undefined1 *)((long)puVar7 + 3) = 1;
      *puVar7 = (short)lVar6;
      *(undefined1 *)(puVar7 + 1) = uVar2;
      *(uint *)(puVar7 + 4) = uVar1;
      lVar5 = param_1[5];
    } while (uVar8 < (ulong)param_1[4]);
    lVar6 = param_1[4] - 1;
  }
  *(undefined4 *)(lVar5 + lVar6 * 0x90 + 8) = 0xffffffff;
  return;
}

// ==== Framework::TFixedLengthAllocator<256ul>::TFixedLengthAllocator(char, char, char, unsigned long)
// vaddr 0x114302c | ghidra 0x124302c | size 284 | symbol _ZN9Framework21TFixedLengthAllocatorILm256EEC2Ecccm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework21TFixedLengthAllocatorILm256EEC2Ecccm
               (long *param_1,undefined1 param_2,undefined1 param_3,undefined1 param_4,long param_5)

{
  uint uVar1;
  undefined1 uVar2;
  undefined1 auVar3 [16];
  undefined *puVar4;
  long lVar5;
  long lVar6;
  undefined2 *puVar7;
  ulong uVar8;
  
  puVar4 = PTR__ZTVN9Framework21TFixedLengthAllocatorILm256EEE_02cb8030;
  *(undefined1 *)(param_1 + 3) = param_2;
  *(undefined1 *)((long)param_1 + 0x19) = param_3;
  *(undefined1 *)((long)param_1 + 0x1a) = param_4;
  *(undefined1 *)((long)param_1 + 0x1b) = 0;
  param_1[4] = param_5;
  *(undefined8 *)((long)param_1 + 0x34) = 0;
  *(undefined1 *)(param_1 + 6) = 1;
  *param_1 = (long)(puVar4 + 0x10);
  param_1[8] = 0;
  lVar5 = operator new(unsigned long, std::nothrow_t const&)(0xb0,PTR__ZSt7nothrow_02cb9a80);
  if (lVar5 != 0) {
    Framework::CMutex::CMutex()(lVar5);
  }
  param_1[8] = lVar5;
  Framework::CMutex::Initialize()(lVar5);
  uVar8 = param_1[4];
  auVar3._8_8_ = 0;
  auVar3._0_8_ = uVar8;
  lVar5 = uVar8 * 0x110;
  if (SUB168(auVar3 * ZEXT816(0x110),8) != 0) {
    lVar5 = -1;
  }
  lVar5 = operator new[](unsigned long, std::nothrow_t const&)(lVar5,PTR__ZSt7nothrow_02cb9a80);
  param_1[5] = lVar5;
  memset(lVar5,0xcc,uVar8 * 0x110);
  if (uVar8 == 0) {
    lVar6 = -1;
  }
  else {
    uVar8 = 0;
    do {
      lVar6 = param_1[3];
      uVar2 = *(undefined1 *)((long)param_1 + 0x1a);
      puVar7 = (undefined2 *)(lVar5 + uVar8 * 0x110);
      *(int *)(puVar7 + 2) = (int)uVar8;
      uVar1 = (int)uVar8 + 1;
      uVar8 = (ulong)uVar1;
      *(undefined1 *)((long)puVar7 + 3) = 1;
      *puVar7 = (short)lVar6;
      *(undefined1 *)(puVar7 + 1) = uVar2;
      *(uint *)(puVar7 + 4) = uVar1;
      lVar5 = param_1[5];
    } while (uVar8 < (ulong)param_1[4]);
    lVar6 = param_1[4] - 1;
  }
  *(undefined4 *)(lVar5 + lVar6 * 0x110 + 8) = 0xffffffff;
  return;
}

// ==== Framework::TFixedLengthAllocator<512ul>::TFixedLengthAllocator(char, char, char, unsigned long)
// vaddr 0x1143148 | ghidra 0x1243148 | size 284 | symbol _ZN9Framework21TFixedLengthAllocatorILm512EEC2Ecccm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework21TFixedLengthAllocatorILm512EEC2Ecccm
               (long *param_1,undefined1 param_2,undefined1 param_3,undefined1 param_4,long param_5)

{
  uint uVar1;
  undefined1 uVar2;
  undefined1 auVar3 [16];
  undefined *puVar4;
  long lVar5;
  long lVar6;
  undefined2 *puVar7;
  ulong uVar8;
  
  puVar4 = PTR__ZTVN9Framework21TFixedLengthAllocatorILm512EEE_02cbfa08;
  *(undefined1 *)(param_1 + 3) = param_2;
  *(undefined1 *)((long)param_1 + 0x19) = param_3;
  *(undefined1 *)((long)param_1 + 0x1a) = param_4;
  *(undefined1 *)((long)param_1 + 0x1b) = 0;
  param_1[4] = param_5;
  *(undefined8 *)((long)param_1 + 0x34) = 0;
  *(undefined1 *)(param_1 + 6) = 1;
  *param_1 = (long)(puVar4 + 0x10);
  param_1[8] = 0;
  lVar5 = operator new(unsigned long, std::nothrow_t const&)(0xb0,PTR__ZSt7nothrow_02cb9a80);
  if (lVar5 != 0) {
    Framework::CMutex::CMutex()(lVar5);
  }
  param_1[8] = lVar5;
  Framework::CMutex::Initialize()(lVar5);
  uVar8 = param_1[4];
  auVar3._8_8_ = 0;
  auVar3._0_8_ = uVar8;
  lVar5 = uVar8 * 0x210;
  if (SUB168(auVar3 * ZEXT816(0x210),8) != 0) {
    lVar5 = -1;
  }
  lVar5 = operator new[](unsigned long, std::nothrow_t const&)(lVar5,PTR__ZSt7nothrow_02cb9a80);
  param_1[5] = lVar5;
  memset(lVar5,0xcc,uVar8 * 0x210);
  if (uVar8 == 0) {
    lVar6 = -1;
  }
  else {
    uVar8 = 0;
    do {
      lVar6 = param_1[3];
      uVar2 = *(undefined1 *)((long)param_1 + 0x1a);
      puVar7 = (undefined2 *)(lVar5 + uVar8 * 0x210);
      *(int *)(puVar7 + 2) = (int)uVar8;
      uVar1 = (int)uVar8 + 1;
      uVar8 = (ulong)uVar1;
      *(undefined1 *)((long)puVar7 + 3) = 1;
      *puVar7 = (short)lVar6;
      *(undefined1 *)(puVar7 + 1) = uVar2;
      *(uint *)(puVar7 + 4) = uVar1;
      lVar5 = param_1[5];
    } while (uVar8 < (ulong)param_1[4]);
    lVar6 = param_1[4] - 1;
  }
  *(undefined4 *)(lVar5 + lVar6 * 0x210 + 8) = 0xffffffff;
  return;
}

// ==== Framework::TFixedLengthAllocator<16ul>::~TFixedLengthAllocator()
// vaddr 0x11491a8 | ghidra 0x12491a8 | size 64 | symbol _ZN9Framework21TFixedLengthAllocatorILm16EED2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework21TFixedLengthAllocatorILm16EED2Ev(long *param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZTVN9Framework21TFixedLengthAllocatorILm16EEE_02cc39b0 + 0x10;
  *param_1 = (long)puVar1;
  if (((char)param_1[6] != '\0') && (param_1[5] != 0)) {
    operator delete[](void*)();
    puVar1 = (undefined *)*param_1;
  }
                    /* WARNING: Could not recover jumptable at 0x012491e4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(puVar1 + 0x68))(param_1);
  return;
}

// ==== Framework::TFixedLengthAllocator<16ul>::~TFixedLengthAllocator()
// vaddr 0x11491e8 | ghidra 0x12491e8 | size 72 | symbol _ZN9Framework21TFixedLengthAllocatorILm16EED0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework21TFixedLengthAllocatorILm16EED0Ev(long *param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZTVN9Framework21TFixedLengthAllocatorILm16EEE_02cc39b0 + 0x10;
  *param_1 = (long)puVar1;
  if (((char)param_1[6] != '\0') && (param_1[5] != 0)) {
    operator delete[](void*)();
    puVar1 = (undefined *)*param_1;
  }
  (**(code **)(puVar1 + 0x68))(param_1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Framework::TFixedLengthAllocator<16ul>::BlockSize() const
// vaddr 0x1149230 | ghidra 0x1249230 | size 8 | symbol _ZNK9Framework21TFixedLengthAllocatorILm16EE9BlockSizeEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK9Framework21TFixedLengthAllocatorILm16EE9BlockSizeEv(void)

{
  return 0x10;
}

// ==== Framework::TFixedLengthAllocator<16ul>::MaxBlock() const
// vaddr 0x1149238 | ghidra 0x1249238 | size 8 | symbol _ZNK9Framework21TFixedLengthAllocatorILm16EE8MaxBlockEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK9Framework21TFixedLengthAllocatorILm16EE8MaxBlockEv(long param_1)

{
  return *(undefined8 *)(param_1 + 0x20);
}

// ==== Framework::TFixedLengthAllocator<16ul>::pAllocate(char const*, unsigned int)
// vaddr 0x1149240 | ghidra 0x1249240 | size 236 | symbol _ZN9Framework21TFixedLengthAllocatorILm16EE9pAllocateEPKcj | lib libSOA-3.7.0.so | 2026-10-04
long _ZN9Framework21TFixedLengthAllocatorILm16EE9pAllocateEPKcj(long param_1)

{
  ulong uVar1;
  long lVar2;
  long lVar3;
  long lVar4;
  
  lVar3 = *(long *)(param_1 + 0x40);
  if (lVar3 != 0) {
    uVar1 = Framework::CMutex::IsInitialized() const(lVar3);
    if ((uVar1 & 1) == 0) {
      Framework::CMutex::Initialize()(lVar3);
    }
    Framework::CMutex::Lock()(lVar3);
  }
  if ((ulong)*(uint *)(param_1 + 0x34) < *(ulong *)(param_1 + 0x20)) {
    uVar1 = (ulong)*(uint *)(param_1 + 0x38);
    if (*(ulong *)(param_1 + 0x20) <= uVar1) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db199/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TFixedLengthAllocator.h"*/,0xf9,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,uVar1);
    }
    lVar2 = *(long *)(param_1 + 0x28);
    lVar4 = lVar2 + uVar1 * 0x20;
    *(undefined4 *)(param_1 + 0x38) = *(undefined4 *)(lVar4 + 8);
    if (*(char *)(lVar4 + 3) != '\x01') {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db199/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TFixedLengthAllocator.h"*/,0xfc,&UNK_027db22d/*"Not free."*/);
      lVar2 = *(long *)(param_1 + 0x28);
    }
    *(int *)(param_1 + 0x34) = *(int *)(param_1 + 0x34) + 1;
    *(undefined1 *)(lVar2 + uVar1 * 0x20 + 3) = 0;
    lVar4 = *(long *)(param_1 + 0x28) + uVar1 * 0x20 + 0x10;
  }
  else {
    lVar4 = 0;
  }
  if (lVar3 != 0) {
    Framework::CMutex::Unlock()(lVar3);
  }
  return lVar4;
}

// ==== Framework::TFixedLengthAllocator<16ul>::Free(void*)
// vaddr 0x114932c | ghidra 0x124932c | size 208 | symbol _ZN9Framework21TFixedLengthAllocatorILm16EE4FreeEPv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework21TFixedLengthAllocatorILm16EE4FreeEPv(long *param_1,long param_2)

{
  ulong uVar1;
  long lVar2;
  
  lVar2 = param_1[8];
  if (lVar2 != 0) {
    uVar1 = Framework::CMutex::IsInitialized() const(lVar2);
    if ((uVar1 & 1) == 0) {
      Framework::CMutex::Initialize()(lVar2);
    }
    Framework::CMutex::Lock()(lVar2);
  }
  if (param_2 != 0) {
    uVar1 = (**(code **)(*param_1 + 0x30))(param_1,param_2);
    if ((uVar1 & 1) == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db199/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TFixedLengthAllocator.h"*/,0x10f,&UNK_027db237,param_2);
    }
    if (*(char *)(param_2 + -0xd) != '\0') {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db199/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TFixedLengthAllocator.h"*/,0x111,&UNK_027db24f/*"Double free."*/);
    }
    *(undefined1 *)(param_2 + -0xd) = 1;
    *(int *)(param_2 + -8) = (int)param_1[7];
    *(undefined4 *)(param_1 + 7) = *(undefined4 *)(param_2 + -0xc);
    *(int *)((long)param_1 + 0x34) = *(int *)((long)param_1 + 0x34) + -1;
  }
  if (lVar2 != 0) {
    (*(code *)PTR__ZN9Framework6CMutex6UnlockEv_02cb3f98)(lVar2);
    return;
  }
  return;
}

// ==== Framework::TFixedLengthAllocator<16ul>::IsMine(void*) const
// vaddr 0x11493fc | ghidra 0x12493fc | size 124 | symbol _ZNK9Framework21TFixedLengthAllocatorILm16EE6IsMineEPv | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK9Framework21TFixedLengthAllocatorILm16EE6IsMineEPv(long param_1,ulong param_2)

{
  if (param_2 < *(ulong *)(param_1 + 0x28)) {
    return false;
  }
  if (*(ulong *)(param_1 + 0x28) + *(long *)(param_1 + 0x20) * 0x20 <= param_2) {
    return false;
  }
  if (*(char *)(param_1 + 0x18) == '\0') {
    return false;
  }
  if (*(char *)(param_2 - 0x10) == *(char *)(param_1 + 0x18)) {
    if (*(char *)(param_2 - 0xf) == *(char *)(param_1 + 0x19)) {
      return *(char *)(param_2 - 0xe) == *(char *)(param_1 + 0x1a);
    }
    return false;
  }
  return false;
}

// ==== Framework::TFixedLengthAllocator<16ul>::NumAllocated() const
// vaddr 0x1149478 | ghidra 0x1249478 | size 84 | symbol _ZNK9Framework21TFixedLengthAllocatorILm16EE12NumAllocatedEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK9Framework21TFixedLengthAllocatorILm16EE12NumAllocatedEv(long param_1)

{
  ulong uVar1;
  long lVar2;
  undefined4 uVar3;
  
  lVar2 = *(long *)(param_1 + 0x40);
  if (lVar2 == 0) {
    uVar3 = *(undefined4 *)(param_1 + 0x34);
  }
  else {
    uVar1 = Framework::CMutex::IsInitialized() const(lVar2);
    if ((uVar1 & 1) == 0) {
      Framework::CMutex::Initialize()(lVar2);
    }
    Framework::CMutex::Lock()(lVar2);
    uVar3 = *(undefined4 *)(param_1 + 0x34);
    Framework::CMutex::Unlock()(lVar2);
  }
  return uVar3;
}

// ==== Framework::TFixedLengthAllocator<16ul>::IsFree() const
// vaddr 0x11494cc | ghidra 0x12494cc | size 92 | symbol _ZNK9Framework21TFixedLengthAllocatorILm16EE6IsFreeEv | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK9Framework21TFixedLengthAllocatorILm16EE6IsFreeEv(long param_1)

{
  uint uVar1;
  ulong uVar2;
  long lVar3;
  
  lVar3 = *(long *)(param_1 + 0x40);
  if (lVar3 != 0) {
    uVar2 = Framework::CMutex::IsInitialized() const(lVar3);
    if ((uVar2 & 1) == 0) {
      Framework::CMutex::Initialize()(lVar3);
    }
    Framework::CMutex::Lock()(lVar3);
  }
  uVar1 = *(uint *)(param_1 + 0x34);
  uVar2 = *(ulong *)(param_1 + 0x20);
  if (lVar3 != 0) {
    Framework::CMutex::Unlock()(lVar3);
  }
  return uVar1 < uVar2;
}

// ==== Framework::TFixedLengthAllocator<16ul>::ActivityRatio() const
// vaddr 0x1149528 | ghidra 0x1249528 | size 104 | symbol _ZNK9Framework21TFixedLengthAllocatorILm16EE13ActivityRatioEv | lib libSOA-3.7.0.so | 2026-10-04
float _ZNK9Framework21TFixedLengthAllocatorILm16EE13ActivityRatioEv(long param_1)

{
  ulong uVar1;
  long lVar2;
  float fVar3;
  
  lVar2 = *(long *)(param_1 + 0x40);
  if (lVar2 != 0) {
    uVar1 = Framework::CMutex::IsInitialized() const(lVar2);
    if ((uVar1 & 1) == 0) {
      Framework::CMutex::Initialize()(lVar2);
    }
    Framework::CMutex::Lock()(lVar2);
  }
  uVar1 = *(ulong *)(param_1 + 0x20);
  fVar3 = (float)NEON_ucvtf(*(undefined4 *)(param_1 + 0x34));
  if (lVar2 != 0) {
    Framework::CMutex::Unlock()(lVar2);
  }
  return fVar3 / (float)uVar1;
}

// ==== Framework::TFixedLengthAllocator<16ul>::TotalMemoryAmount() const
// vaddr 0x1149590 | ghidra 0x1249590 | size 12 | symbol _ZNK9Framework21TFixedLengthAllocatorILm16EE17TotalMemoryAmountEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK9Framework21TFixedLengthAllocatorILm16EE17TotalMemoryAmountEv(long param_1)

{
  return *(long *)(param_1 + 0x20) << 5;
}

// ==== Framework::TFixedLengthAllocator<16ul>::UsedMemoryAmount() const
// vaddr 0x114959c | ghidra 0x124959c | size 88 | symbol _ZNK9Framework21TFixedLengthAllocatorILm16EE16UsedMemoryAmountEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK9Framework21TFixedLengthAllocatorILm16EE16UsedMemoryAmountEv(long param_1)

{
  ulong uVar1;
  long lVar2;
  uint uVar3;
  
  lVar2 = *(long *)(param_1 + 0x40);
  if (lVar2 == 0) {
    uVar3 = *(uint *)(param_1 + 0x34);
  }
  else {
    uVar1 = Framework::CMutex::IsInitialized() const(lVar2);
    if ((uVar1 & 1) == 0) {
      Framework::CMutex::Initialize()(lVar2);
    }
    Framework::CMutex::Lock()(lVar2);
    uVar3 = *(uint *)(param_1 + 0x34);
    Framework::CMutex::Unlock()(lVar2);
  }
  return (ulong)uVar3 << 5;
}

// ==== Framework::TFixedLengthAllocator<16ul>::EnableMutex()
// vaddr 0x11495f4 | ghidra 0x12495f4 | size 84 | symbol _ZN9Framework21TFixedLengthAllocatorILm16EE11EnableMutexEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework21TFixedLengthAllocatorILm16EE11EnableMutexEv(long param_1)

{
  long lVar1;
  
  if (*(long *)(param_1 + 0x40) != 0) {
    return;
  }
  lVar1 = operator new(unsigned long, std::nothrow_t const&)(0xb0,PTR__ZSt7nothrow_02cb9a80);
  if (lVar1 != 0) {
    Framework::CMutex::CMutex()(lVar1);
  }
  *(long *)(param_1 + 0x40) = lVar1;
  (*(code *)PTR__ZN9Framework6CMutex10InitializeEv_02ca3bf0)(lVar1);
  return;
}

// ==== Framework::TFixedLengthAllocator<16ul>::DisableMutex()
// vaddr 0x1149648 | ghidra 0x1249648 | size 40 | symbol _ZN9Framework21TFixedLengthAllocatorILm16EE12DisableMutexEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework21TFixedLengthAllocatorILm16EE12DisableMutexEv(long param_1)

{
  if (*(long **)(param_1 + 0x40) != (long *)0x0) {
    (**(code **)(**(long **)(param_1 + 0x40) + 8))();
    *(undefined8 *)(param_1 + 0x40) = 0;
  }
  return;
}

// ==== Framework::TFixedLengthAllocator<32ul>::~TFixedLengthAllocator()
// vaddr 0x1149670 | ghidra 0x1249670 | size 64 | symbol _ZN9Framework21TFixedLengthAllocatorILm32EED2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework21TFixedLengthAllocatorILm32EED2Ev(long *param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZTVN9Framework21TFixedLengthAllocatorILm32EEE_02cb6fd0 + 0x10;
  *param_1 = (long)puVar1;
  if (((char)param_1[6] != '\0') && (param_1[5] != 0)) {
    operator delete[](void*)();
    puVar1 = (undefined *)*param_1;
  }
                    /* WARNING: Could not recover jumptable at 0x012496ac. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(puVar1 + 0x68))(param_1);
  return;
}

// ==== Framework::TFixedLengthAllocator<32ul>::~TFixedLengthAllocator()
// vaddr 0x11496b0 | ghidra 0x12496b0 | size 72 | symbol _ZN9Framework21TFixedLengthAllocatorILm32EED0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework21TFixedLengthAllocatorILm32EED0Ev(long *param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZTVN9Framework21TFixedLengthAllocatorILm32EEE_02cb6fd0 + 0x10;
  *param_1 = (long)puVar1;
  if (((char)param_1[6] != '\0') && (param_1[5] != 0)) {
    operator delete[](void*)();
    puVar1 = (undefined *)*param_1;
  }
  (**(code **)(puVar1 + 0x68))(param_1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Framework::TFixedLengthAllocator<32ul>::BlockSize() const
// vaddr 0x11496f8 | ghidra 0x12496f8 | size 8 | symbol _ZNK9Framework21TFixedLengthAllocatorILm32EE9BlockSizeEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK9Framework21TFixedLengthAllocatorILm32EE9BlockSizeEv(void)

{
  return 0x20;
}

// ==== Framework::TFixedLengthAllocator<32ul>::MaxBlock() const
// vaddr 0x1149700 | ghidra 0x1249700 | size 8 | symbol _ZNK9Framework21TFixedLengthAllocatorILm32EE8MaxBlockEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK9Framework21TFixedLengthAllocatorILm32EE8MaxBlockEv(long param_1)

{
  return *(undefined8 *)(param_1 + 0x20);
}

// ==== Framework::TFixedLengthAllocator<32ul>::pAllocate(char const*, unsigned int)
// vaddr 0x1149708 | ghidra 0x1249708 | size 244 | symbol _ZN9Framework21TFixedLengthAllocatorILm32EE9pAllocateEPKcj | lib libSOA-3.7.0.so | 2026-10-04
long _ZN9Framework21TFixedLengthAllocatorILm32EE9pAllocateEPKcj(long param_1)

{
  ulong uVar1;
  long lVar2;
  long lVar3;
  long lVar4;
  
  lVar4 = *(long *)(param_1 + 0x40);
  if (lVar4 != 0) {
    uVar1 = Framework::CMutex::IsInitialized() const(lVar4);
    if ((uVar1 & 1) == 0) {
      Framework::CMutex::Initialize()(lVar4);
    }
    Framework::CMutex::Lock()(lVar4);
  }
  if ((ulong)*(uint *)(param_1 + 0x34) < *(ulong *)(param_1 + 0x20)) {
    uVar1 = (ulong)*(uint *)(param_1 + 0x38);
    if (*(ulong *)(param_1 + 0x20) <= uVar1) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db199/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TFixedLengthAllocator.h"*/,0xf9,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,uVar1);
    }
    lVar2 = *(long *)(param_1 + 0x28);
    lVar3 = lVar2 + uVar1 * 0x30;
    *(undefined4 *)(param_1 + 0x38) = *(undefined4 *)(lVar3 + 8);
    if (*(char *)(lVar3 + 3) != '\x01') {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db199/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TFixedLengthAllocator.h"*/,0xfc,&UNK_027db22d/*"Not free."*/);
      lVar2 = *(long *)(param_1 + 0x28);
    }
    *(int *)(param_1 + 0x34) = *(int *)(param_1 + 0x34) + 1;
    *(undefined1 *)(lVar2 + uVar1 * 0x30 + 3) = 0;
    lVar2 = *(long *)(param_1 + 0x28) + uVar1 * 0x30 + 0x10;
  }
  else {
    lVar2 = 0;
  }
  if (lVar4 != 0) {
    Framework::CMutex::Unlock()(lVar4);
  }
  return lVar2;
}

// ==== Framework::TFixedLengthAllocator<32ul>::Free(void*)
// vaddr 0x11497fc | ghidra 0x12497fc | size 208 | symbol _ZN9Framework21TFixedLengthAllocatorILm32EE4FreeEPv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework21TFixedLengthAllocatorILm32EE4FreeEPv(long *param_1,long param_2)

{
  ulong uVar1;
  long lVar2;
  
  lVar2 = param_1[8];
  if (lVar2 != 0) {
    uVar1 = Framework::CMutex::IsInitialized() const(lVar2);
    if ((uVar1 & 1) == 0) {
      Framework::CMutex::Initialize()(lVar2);
    }
    Framework::CMutex::Lock()(lVar2);
  }
  if (param_2 != 0) {
    uVar1 = (**(code **)(*param_1 + 0x30))(param_1,param_2);
    if ((uVar1 & 1) == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db199/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TFixedLengthAllocator.h"*/,0x10f,&UNK_027db237,param_2);
    }
    if (*(char *)(param_2 + -0xd) != '\0') {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db199/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TFixedLengthAllocator.h"*/,0x111,&UNK_027db24f/*"Double free."*/);
    }
    *(undefined1 *)(param_2 + -0xd) = 1;
    *(int *)(param_2 + -8) = (int)param_1[7];
    *(undefined4 *)(param_1 + 7) = *(undefined4 *)(param_2 + -0xc);
    *(int *)((long)param_1 + 0x34) = *(int *)((long)param_1 + 0x34) + -1;
  }
  if (lVar2 != 0) {
    (*(code *)PTR__ZN9Framework6CMutex6UnlockEv_02cb3f98)(lVar2);
    return;
  }
  return;
}

// ==== Framework::TFixedLengthAllocator<32ul>::IsMine(void*) const
// vaddr 0x11498cc | ghidra 0x12498cc | size 128 | symbol _ZNK9Framework21TFixedLengthAllocatorILm32EE6IsMineEPv | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK9Framework21TFixedLengthAllocatorILm32EE6IsMineEPv(long param_1,ulong param_2)

{
  if (param_2 < *(ulong *)(param_1 + 0x28)) {
    return false;
  }
  if (*(ulong *)(param_1 + 0x28) + *(long *)(param_1 + 0x20) * 0x30 <= param_2) {
    return false;
  }
  if (*(char *)(param_1 + 0x18) == '\0') {
    return false;
  }
  if (*(char *)(param_2 - 0x10) == *(char *)(param_1 + 0x18)) {
    if (*(char *)(param_2 - 0xf) == *(char *)(param_1 + 0x19)) {
      return *(char *)(param_2 - 0xe) == *(char *)(param_1 + 0x1a);
    }
    return false;
  }
  return false;
}

// ==== Framework::TFixedLengthAllocator<32ul>::NumAllocated() const
// vaddr 0x114994c | ghidra 0x124994c | size 84 | symbol _ZNK9Framework21TFixedLengthAllocatorILm32EE12NumAllocatedEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK9Framework21TFixedLengthAllocatorILm32EE12NumAllocatedEv(long param_1)

{
  ulong uVar1;
  long lVar2;
  undefined4 uVar3;
  
  lVar2 = *(long *)(param_1 + 0x40);
  if (lVar2 == 0) {
    uVar3 = *(undefined4 *)(param_1 + 0x34);
  }
  else {
    uVar1 = Framework::CMutex::IsInitialized() const(lVar2);
    if ((uVar1 & 1) == 0) {
      Framework::CMutex::Initialize()(lVar2);
    }
    Framework::CMutex::Lock()(lVar2);
    uVar3 = *(undefined4 *)(param_1 + 0x34);
    Framework::CMutex::Unlock()(lVar2);
  }
  return uVar3;
}

// ==== Framework::TFixedLengthAllocator<32ul>::IsFree() const
// vaddr 0x11499a0 | ghidra 0x12499a0 | size 92 | symbol _ZNK9Framework21TFixedLengthAllocatorILm32EE6IsFreeEv | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK9Framework21TFixedLengthAllocatorILm32EE6IsFreeEv(long param_1)

{
  uint uVar1;
  ulong uVar2;
  long lVar3;
  
  lVar3 = *(long *)(param_1 + 0x40);
  if (lVar3 != 0) {
    uVar2 = Framework::CMutex::IsInitialized() const(lVar3);
    if ((uVar2 & 1) == 0) {
      Framework::CMutex::Initialize()(lVar3);
    }
    Framework::CMutex::Lock()(lVar3);
  }
  uVar1 = *(uint *)(param_1 + 0x34);
  uVar2 = *(ulong *)(param_1 + 0x20);
  if (lVar3 != 0) {
    Framework::CMutex::Unlock()(lVar3);
  }
  return uVar1 < uVar2;
}

// ==== Framework::TFixedLengthAllocator<32ul>::ActivityRatio() const
// vaddr 0x11499fc | ghidra 0x12499fc | size 104 | symbol _ZNK9Framework21TFixedLengthAllocatorILm32EE13ActivityRatioEv | lib libSOA-3.7.0.so | 2026-10-04
float _ZNK9Framework21TFixedLengthAllocatorILm32EE13ActivityRatioEv(long param_1)

{
  ulong uVar1;
  long lVar2;
  float fVar3;
  
  lVar2 = *(long *)(param_1 + 0x40);
  if (lVar2 != 0) {
    uVar1 = Framework::CMutex::IsInitialized() const(lVar2);
    if ((uVar1 & 1) == 0) {
      Framework::CMutex::Initialize()(lVar2);
    }
    Framework::CMutex::Lock()(lVar2);
  }
  uVar1 = *(ulong *)(param_1 + 0x20);
  fVar3 = (float)NEON_ucvtf(*(undefined4 *)(param_1 + 0x34));
  if (lVar2 != 0) {
    Framework::CMutex::Unlock()(lVar2);
  }
  return fVar3 / (float)uVar1;
}

// ==== Framework::TFixedLengthAllocator<32ul>::TotalMemoryAmount() const
// vaddr 0x1149a64 | ghidra 0x1249a64 | size 16 | symbol _ZNK9Framework21TFixedLengthAllocatorILm32EE17TotalMemoryAmountEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK9Framework21TFixedLengthAllocatorILm32EE17TotalMemoryAmountEv(long param_1)

{
  return *(long *)(param_1 + 0x20) * 0x30;
}

// ==== Framework::TFixedLengthAllocator<32ul>::UsedMemoryAmount() const
// vaddr 0x1149a74 | ghidra 0x1249a74 | size 88 | symbol _ZNK9Framework21TFixedLengthAllocatorILm32EE16UsedMemoryAmountEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK9Framework21TFixedLengthAllocatorILm32EE16UsedMemoryAmountEv(long param_1)

{
  ulong uVar1;
  long lVar2;
  uint uVar3;
  
  lVar2 = *(long *)(param_1 + 0x40);
  if (lVar2 == 0) {
    uVar3 = *(uint *)(param_1 + 0x34);
  }
  else {
    uVar1 = Framework::CMutex::IsInitialized() const(lVar2);
    if ((uVar1 & 1) == 0) {
      Framework::CMutex::Initialize()(lVar2);
    }
    Framework::CMutex::Lock()(lVar2);
    uVar3 = *(uint *)(param_1 + 0x34);
    Framework::CMutex::Unlock()(lVar2);
  }
  return (ulong)uVar3 * 0x30;
}

// ==== Framework::TFixedLengthAllocator<32ul>::EnableMutex()
// vaddr 0x1149acc | ghidra 0x1249acc | size 84 | symbol _ZN9Framework21TFixedLengthAllocatorILm32EE11EnableMutexEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework21TFixedLengthAllocatorILm32EE11EnableMutexEv(long param_1)

{
  long lVar1;
  
  if (*(long *)(param_1 + 0x40) != 0) {
    return;
  }
  lVar1 = operator new(unsigned long, std::nothrow_t const&)(0xb0,PTR__ZSt7nothrow_02cb9a80);
  if (lVar1 != 0) {
    Framework::CMutex::CMutex()(lVar1);
  }
  *(long *)(param_1 + 0x40) = lVar1;
  (*(code *)PTR__ZN9Framework6CMutex10InitializeEv_02ca3bf0)(lVar1);
  return;
}

// ==== Framework::TFixedLengthAllocator<32ul>::DisableMutex()
// vaddr 0x1149b20 | ghidra 0x1249b20 | size 40 | symbol _ZN9Framework21TFixedLengthAllocatorILm32EE12DisableMutexEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework21TFixedLengthAllocatorILm32EE12DisableMutexEv(long param_1)

{
  if (*(long **)(param_1 + 0x40) != (long *)0x0) {
    (**(code **)(**(long **)(param_1 + 0x40) + 8))();
    *(undefined8 *)(param_1 + 0x40) = 0;
  }
  return;
}

// ==== Framework::TFixedLengthAllocator<64ul>::~TFixedLengthAllocator()
// vaddr 0x1149b48 | ghidra 0x1249b48 | size 64 | symbol _ZN9Framework21TFixedLengthAllocatorILm64EED2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework21TFixedLengthAllocatorILm64EED2Ev(long *param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZTVN9Framework21TFixedLengthAllocatorILm64EEE_02cb8310 + 0x10;
  *param_1 = (long)puVar1;
  if (((char)param_1[6] != '\0') && (param_1[5] != 0)) {
    operator delete[](void*)();
    puVar1 = (undefined *)*param_1;
  }
                    /* WARNING: Could not recover jumptable at 0x01249b84. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(puVar1 + 0x68))(param_1);
  return;
}

// ==== Framework::TFixedLengthAllocator<64ul>::~TFixedLengthAllocator()
// vaddr 0x1149b88 | ghidra 0x1249b88 | size 72 | symbol _ZN9Framework21TFixedLengthAllocatorILm64EED0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework21TFixedLengthAllocatorILm64EED0Ev(long *param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZTVN9Framework21TFixedLengthAllocatorILm64EEE_02cb8310 + 0x10;
  *param_1 = (long)puVar1;
  if (((char)param_1[6] != '\0') && (param_1[5] != 0)) {
    operator delete[](void*)();
    puVar1 = (undefined *)*param_1;
  }
  (**(code **)(puVar1 + 0x68))(param_1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Framework::TFixedLengthAllocator<64ul>::BlockSize() const
// vaddr 0x1149bd0 | ghidra 0x1249bd0 | size 8 | symbol _ZNK9Framework21TFixedLengthAllocatorILm64EE9BlockSizeEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK9Framework21TFixedLengthAllocatorILm64EE9BlockSizeEv(void)

{
  return 0x40;
}

// ==== Framework::TFixedLengthAllocator<64ul>::MaxBlock() const
// vaddr 0x1149bd8 | ghidra 0x1249bd8 | size 8 | symbol _ZNK9Framework21TFixedLengthAllocatorILm64EE8MaxBlockEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK9Framework21TFixedLengthAllocatorILm64EE8MaxBlockEv(long param_1)

{
  return *(undefined8 *)(param_1 + 0x20);
}

// ==== Framework::TFixedLengthAllocator<64ul>::pAllocate(char const*, unsigned int)
// vaddr 0x1149be0 | ghidra 0x1249be0 | size 244 | symbol _ZN9Framework21TFixedLengthAllocatorILm64EE9pAllocateEPKcj | lib libSOA-3.7.0.so | 2026-10-04
long _ZN9Framework21TFixedLengthAllocatorILm64EE9pAllocateEPKcj(long param_1)

{
  ulong uVar1;
  long lVar2;
  long lVar3;
  long lVar4;
  
  lVar4 = *(long *)(param_1 + 0x40);
  if (lVar4 != 0) {
    uVar1 = Framework::CMutex::IsInitialized() const(lVar4);
    if ((uVar1 & 1) == 0) {
      Framework::CMutex::Initialize()(lVar4);
    }
    Framework::CMutex::Lock()(lVar4);
  }
  if ((ulong)*(uint *)(param_1 + 0x34) < *(ulong *)(param_1 + 0x20)) {
    uVar1 = (ulong)*(uint *)(param_1 + 0x38);
    if (*(ulong *)(param_1 + 0x20) <= uVar1) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db199/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TFixedLengthAllocator.h"*/,0xf9,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,uVar1);
    }
    lVar2 = *(long *)(param_1 + 0x28);
    lVar3 = lVar2 + uVar1 * 0x50;
    *(undefined4 *)(param_1 + 0x38) = *(undefined4 *)(lVar3 + 8);
    if (*(char *)(lVar3 + 3) != '\x01') {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db199/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TFixedLengthAllocator.h"*/,0xfc,&UNK_027db22d/*"Not free."*/);
      lVar2 = *(long *)(param_1 + 0x28);
    }
    *(int *)(param_1 + 0x34) = *(int *)(param_1 + 0x34) + 1;
    *(undefined1 *)(lVar2 + uVar1 * 0x50 + 3) = 0;
    lVar2 = *(long *)(param_1 + 0x28) + uVar1 * 0x50 + 0x10;
  }
  else {
    lVar2 = 0;
  }
  if (lVar4 != 0) {
    Framework::CMutex::Unlock()(lVar4);
  }
  return lVar2;
}

// ==== Framework::TFixedLengthAllocator<64ul>::Free(void*)
// vaddr 0x1149cd4 | ghidra 0x1249cd4 | size 208 | symbol _ZN9Framework21TFixedLengthAllocatorILm64EE4FreeEPv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework21TFixedLengthAllocatorILm64EE4FreeEPv(long *param_1,long param_2)

{
  ulong uVar1;
  long lVar2;
  
  lVar2 = param_1[8];
  if (lVar2 != 0) {
    uVar1 = Framework::CMutex::IsInitialized() const(lVar2);
    if ((uVar1 & 1) == 0) {
      Framework::CMutex::Initialize()(lVar2);
    }
    Framework::CMutex::Lock()(lVar2);
  }
  if (param_2 != 0) {
    uVar1 = (**(code **)(*param_1 + 0x30))(param_1,param_2);
    if ((uVar1 & 1) == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db199/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TFixedLengthAllocator.h"*/,0x10f,&UNK_027db237,param_2);
    }
    if (*(char *)(param_2 + -0xd) != '\0') {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db199/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TFixedLengthAllocator.h"*/,0x111,&UNK_027db24f/*"Double free."*/);
    }
    *(undefined1 *)(param_2 + -0xd) = 1;
    *(int *)(param_2 + -8) = (int)param_1[7];
    *(undefined4 *)(param_1 + 7) = *(undefined4 *)(param_2 + -0xc);
    *(int *)((long)param_1 + 0x34) = *(int *)((long)param_1 + 0x34) + -1;
  }
  if (lVar2 != 0) {
    (*(code *)PTR__ZN9Framework6CMutex6UnlockEv_02cb3f98)(lVar2);
    return;
  }
  return;
}

// ==== Framework::TFixedLengthAllocator<64ul>::IsMine(void*) const
// vaddr 0x1149da4 | ghidra 0x1249da4 | size 128 | symbol _ZNK9Framework21TFixedLengthAllocatorILm64EE6IsMineEPv | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK9Framework21TFixedLengthAllocatorILm64EE6IsMineEPv(long param_1,ulong param_2)

{
  if (param_2 < *(ulong *)(param_1 + 0x28)) {
    return false;
  }
  if (*(ulong *)(param_1 + 0x28) + *(long *)(param_1 + 0x20) * 0x50 <= param_2) {
    return false;
  }
  if (*(char *)(param_1 + 0x18) == '\0') {
    return false;
  }
  if (*(char *)(param_2 - 0x10) == *(char *)(param_1 + 0x18)) {
    if (*(char *)(param_2 - 0xf) == *(char *)(param_1 + 0x19)) {
      return *(char *)(param_2 - 0xe) == *(char *)(param_1 + 0x1a);
    }
    return false;
  }
  return false;
}

// ==== Framework::TFixedLengthAllocator<64ul>::NumAllocated() const
// vaddr 0x1149e24 | ghidra 0x1249e24 | size 84 | symbol _ZNK9Framework21TFixedLengthAllocatorILm64EE12NumAllocatedEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK9Framework21TFixedLengthAllocatorILm64EE12NumAllocatedEv(long param_1)

{
  ulong uVar1;
  long lVar2;
  undefined4 uVar3;
  
  lVar2 = *(long *)(param_1 + 0x40);
  if (lVar2 == 0) {
    uVar3 = *(undefined4 *)(param_1 + 0x34);
  }
  else {
    uVar1 = Framework::CMutex::IsInitialized() const(lVar2);
    if ((uVar1 & 1) == 0) {
      Framework::CMutex::Initialize()(lVar2);
    }
    Framework::CMutex::Lock()(lVar2);
    uVar3 = *(undefined4 *)(param_1 + 0x34);
    Framework::CMutex::Unlock()(lVar2);
  }
  return uVar3;
}

// ==== Framework::TFixedLengthAllocator<64ul>::IsFree() const
// vaddr 0x1149e78 | ghidra 0x1249e78 | size 92 | symbol _ZNK9Framework21TFixedLengthAllocatorILm64EE6IsFreeEv | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK9Framework21TFixedLengthAllocatorILm64EE6IsFreeEv(long param_1)

{
  uint uVar1;
  ulong uVar2;
  long lVar3;
  
  lVar3 = *(long *)(param_1 + 0x40);
  if (lVar3 != 0) {
    uVar2 = Framework::CMutex::IsInitialized() const(lVar3);
    if ((uVar2 & 1) == 0) {
      Framework::CMutex::Initialize()(lVar3);
    }
    Framework::CMutex::Lock()(lVar3);
  }
  uVar1 = *(uint *)(param_1 + 0x34);
  uVar2 = *(ulong *)(param_1 + 0x20);
  if (lVar3 != 0) {
    Framework::CMutex::Unlock()(lVar3);
  }
  return uVar1 < uVar2;
}

// ==== Framework::TFixedLengthAllocator<64ul>::ActivityRatio() const
// vaddr 0x1149ed4 | ghidra 0x1249ed4 | size 104 | symbol _ZNK9Framework21TFixedLengthAllocatorILm64EE13ActivityRatioEv | lib libSOA-3.7.0.so | 2026-10-04
float _ZNK9Framework21TFixedLengthAllocatorILm64EE13ActivityRatioEv(long param_1)

{
  ulong uVar1;
  long lVar2;
  float fVar3;
  
  lVar2 = *(long *)(param_1 + 0x40);
  if (lVar2 != 0) {
    uVar1 = Framework::CMutex::IsInitialized() const(lVar2);
    if ((uVar1 & 1) == 0) {
      Framework::CMutex::Initialize()(lVar2);
    }
    Framework::CMutex::Lock()(lVar2);
  }
  uVar1 = *(ulong *)(param_1 + 0x20);
  fVar3 = (float)NEON_ucvtf(*(undefined4 *)(param_1 + 0x34));
  if (lVar2 != 0) {
    Framework::CMutex::Unlock()(lVar2);
  }
  return fVar3 / (float)uVar1;
}

// ==== Framework::TFixedLengthAllocator<64ul>::TotalMemoryAmount() const
// vaddr 0x1149f3c | ghidra 0x1249f3c | size 16 | symbol _ZNK9Framework21TFixedLengthAllocatorILm64EE17TotalMemoryAmountEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK9Framework21TFixedLengthAllocatorILm64EE17TotalMemoryAmountEv(long param_1)

{
  return *(long *)(param_1 + 0x20) * 0x50;
}

// ==== Framework::TFixedLengthAllocator<64ul>::UsedMemoryAmount() const
// vaddr 0x1149f4c | ghidra 0x1249f4c | size 88 | symbol _ZNK9Framework21TFixedLengthAllocatorILm64EE16UsedMemoryAmountEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK9Framework21TFixedLengthAllocatorILm64EE16UsedMemoryAmountEv(long param_1)

{
  ulong uVar1;
  long lVar2;
  uint uVar3;
  
  lVar2 = *(long *)(param_1 + 0x40);
  if (lVar2 == 0) {
    uVar3 = *(uint *)(param_1 + 0x34);
  }
  else {
    uVar1 = Framework::CMutex::IsInitialized() const(lVar2);
    if ((uVar1 & 1) == 0) {
      Framework::CMutex::Initialize()(lVar2);
    }
    Framework::CMutex::Lock()(lVar2);
    uVar3 = *(uint *)(param_1 + 0x34);
    Framework::CMutex::Unlock()(lVar2);
  }
  return (ulong)uVar3 * 0x50;
}

// ==== Framework::TFixedLengthAllocator<64ul>::EnableMutex()
// vaddr 0x1149fa4 | ghidra 0x1249fa4 | size 84 | symbol _ZN9Framework21TFixedLengthAllocatorILm64EE11EnableMutexEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework21TFixedLengthAllocatorILm64EE11EnableMutexEv(long param_1)

{
  long lVar1;
  
  if (*(long *)(param_1 + 0x40) != 0) {
    return;
  }
  lVar1 = operator new(unsigned long, std::nothrow_t const&)(0xb0,PTR__ZSt7nothrow_02cb9a80);
  if (lVar1 != 0) {
    Framework::CMutex::CMutex()(lVar1);
  }
  *(long *)(param_1 + 0x40) = lVar1;
  (*(code *)PTR__ZN9Framework6CMutex10InitializeEv_02ca3bf0)(lVar1);
  return;
}

// ==== Framework::TFixedLengthAllocator<64ul>::DisableMutex()
// vaddr 0x1149ff8 | ghidra 0x1249ff8 | size 40 | symbol _ZN9Framework21TFixedLengthAllocatorILm64EE12DisableMutexEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework21TFixedLengthAllocatorILm64EE12DisableMutexEv(long param_1)

{
  if (*(long **)(param_1 + 0x40) != (long *)0x0) {
    (**(code **)(**(long **)(param_1 + 0x40) + 8))();
    *(undefined8 *)(param_1 + 0x40) = 0;
  }
  return;
}

// ==== Framework::TFixedLengthAllocator<128ul>::~TFixedLengthAllocator()
// vaddr 0x114a020 | ghidra 0x124a020 | size 64 | symbol _ZN9Framework21TFixedLengthAllocatorILm128EED2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework21TFixedLengthAllocatorILm128EED2Ev(long *param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZTVN9Framework21TFixedLengthAllocatorILm128EEE_02cb8f48 + 0x10;
  *param_1 = (long)puVar1;
  if (((char)param_1[6] != '\0') && (param_1[5] != 0)) {
    operator delete[](void*)();
    puVar1 = (undefined *)*param_1;
  }
                    /* WARNING: Could not recover jumptable at 0x0124a05c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(puVar1 + 0x68))(param_1);
  return;
}

// ==== Framework::TFixedLengthAllocator<128ul>::~TFixedLengthAllocator()
// vaddr 0x114a060 | ghidra 0x124a060 | size 72 | symbol _ZN9Framework21TFixedLengthAllocatorILm128EED0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework21TFixedLengthAllocatorILm128EED0Ev(long *param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZTVN9Framework21TFixedLengthAllocatorILm128EEE_02cb8f48 + 0x10;
  *param_1 = (long)puVar1;
  if (((char)param_1[6] != '\0') && (param_1[5] != 0)) {
    operator delete[](void*)();
    puVar1 = (undefined *)*param_1;
  }
  (**(code **)(puVar1 + 0x68))(param_1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Framework::TFixedLengthAllocator<128ul>::BlockSize() const
// vaddr 0x114a0a8 | ghidra 0x124a0a8 | size 8 | symbol _ZNK9Framework21TFixedLengthAllocatorILm128EE9BlockSizeEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK9Framework21TFixedLengthAllocatorILm128EE9BlockSizeEv(void)

{
  return 0x80;
}

// ==== Framework::TFixedLengthAllocator<128ul>::MaxBlock() const
// vaddr 0x114a0b0 | ghidra 0x124a0b0 | size 8 | symbol _ZNK9Framework21TFixedLengthAllocatorILm128EE8MaxBlockEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK9Framework21TFixedLengthAllocatorILm128EE8MaxBlockEv(long param_1)

{
  return *(undefined8 *)(param_1 + 0x20);
}

// ==== Framework::TFixedLengthAllocator<128ul>::pAllocate(char const*, unsigned int)
// vaddr 0x114a0b8 | ghidra 0x124a0b8 | size 244 | symbol _ZN9Framework21TFixedLengthAllocatorILm128EE9pAllocateEPKcj | lib libSOA-3.7.0.so | 2026-10-04
long _ZN9Framework21TFixedLengthAllocatorILm128EE9pAllocateEPKcj(long param_1)

{
  ulong uVar1;
  long lVar2;
  long lVar3;
  long lVar4;
  
  lVar4 = *(long *)(param_1 + 0x40);
  if (lVar4 != 0) {
    uVar1 = Framework::CMutex::IsInitialized() const(lVar4);
    if ((uVar1 & 1) == 0) {
      Framework::CMutex::Initialize()(lVar4);
    }
    Framework::CMutex::Lock()(lVar4);
  }
  if ((ulong)*(uint *)(param_1 + 0x34) < *(ulong *)(param_1 + 0x20)) {
    uVar1 = (ulong)*(uint *)(param_1 + 0x38);
    if (*(ulong *)(param_1 + 0x20) <= uVar1) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db199/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TFixedLengthAllocator.h"*/,0xf9,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,uVar1);
    }
    lVar2 = *(long *)(param_1 + 0x28);
    lVar3 = lVar2 + uVar1 * 0x90;
    *(undefined4 *)(param_1 + 0x38) = *(undefined4 *)(lVar3 + 8);
    if (*(char *)(lVar3 + 3) != '\x01') {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db199/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TFixedLengthAllocator.h"*/,0xfc,&UNK_027db22d/*"Not free."*/);
      lVar2 = *(long *)(param_1 + 0x28);
    }
    *(int *)(param_1 + 0x34) = *(int *)(param_1 + 0x34) + 1;
    *(undefined1 *)(lVar2 + uVar1 * 0x90 + 3) = 0;
    lVar2 = *(long *)(param_1 + 0x28) + uVar1 * 0x90 + 0x10;
  }
  else {
    lVar2 = 0;
  }
  if (lVar4 != 0) {
    Framework::CMutex::Unlock()(lVar4);
  }
  return lVar2;
}

// ==== Framework::TFixedLengthAllocator<128ul>::Free(void*)
// vaddr 0x114a1ac | ghidra 0x124a1ac | size 208 | symbol _ZN9Framework21TFixedLengthAllocatorILm128EE4FreeEPv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework21TFixedLengthAllocatorILm128EE4FreeEPv(long *param_1,long param_2)

{
  ulong uVar1;
  long lVar2;
  
  lVar2 = param_1[8];
  if (lVar2 != 0) {
    uVar1 = Framework::CMutex::IsInitialized() const(lVar2);
    if ((uVar1 & 1) == 0) {
      Framework::CMutex::Initialize()(lVar2);
    }
    Framework::CMutex::Lock()(lVar2);
  }
  if (param_2 != 0) {
    uVar1 = (**(code **)(*param_1 + 0x30))(param_1,param_2);
    if ((uVar1 & 1) == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db199/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TFixedLengthAllocator.h"*/,0x10f,&UNK_027db237,param_2);
    }
    if (*(char *)(param_2 + -0xd) != '\0') {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db199/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TFixedLengthAllocator.h"*/,0x111,&UNK_027db24f/*"Double free."*/);
    }
    *(undefined1 *)(param_2 + -0xd) = 1;
    *(int *)(param_2 + -8) = (int)param_1[7];
    *(undefined4 *)(param_1 + 7) = *(undefined4 *)(param_2 + -0xc);
    *(int *)((long)param_1 + 0x34) = *(int *)((long)param_1 + 0x34) + -1;
  }
  if (lVar2 != 0) {
    (*(code *)PTR__ZN9Framework6CMutex6UnlockEv_02cb3f98)(lVar2);
    return;
  }
  return;
}

// ==== Framework::TFixedLengthAllocator<128ul>::IsMine(void*) const
// vaddr 0x114a27c | ghidra 0x124a27c | size 128 | symbol _ZNK9Framework21TFixedLengthAllocatorILm128EE6IsMineEPv | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK9Framework21TFixedLengthAllocatorILm128EE6IsMineEPv(long param_1,ulong param_2)

{
  if (param_2 < *(ulong *)(param_1 + 0x28)) {
    return false;
  }
  if (*(ulong *)(param_1 + 0x28) + *(long *)(param_1 + 0x20) * 0x90 <= param_2) {
    return false;
  }
  if (*(char *)(param_1 + 0x18) == '\0') {
    return false;
  }
  if (*(char *)(param_2 - 0x10) == *(char *)(param_1 + 0x18)) {
    if (*(char *)(param_2 - 0xf) == *(char *)(param_1 + 0x19)) {
      return *(char *)(param_2 - 0xe) == *(char *)(param_1 + 0x1a);
    }
    return false;
  }
  return false;
}

// ==== Framework::TFixedLengthAllocator<128ul>::NumAllocated() const
// vaddr 0x114a2fc | ghidra 0x124a2fc | size 84 | symbol _ZNK9Framework21TFixedLengthAllocatorILm128EE12NumAllocatedEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK9Framework21TFixedLengthAllocatorILm128EE12NumAllocatedEv(long param_1)

{
  ulong uVar1;
  long lVar2;
  undefined4 uVar3;
  
  lVar2 = *(long *)(param_1 + 0x40);
  if (lVar2 == 0) {
    uVar3 = *(undefined4 *)(param_1 + 0x34);
  }
  else {
    uVar1 = Framework::CMutex::IsInitialized() const(lVar2);
    if ((uVar1 & 1) == 0) {
      Framework::CMutex::Initialize()(lVar2);
    }
    Framework::CMutex::Lock()(lVar2);
    uVar3 = *(undefined4 *)(param_1 + 0x34);
    Framework::CMutex::Unlock()(lVar2);
  }
  return uVar3;
}

// ==== Framework::TFixedLengthAllocator<128ul>::IsFree() const
// vaddr 0x114a350 | ghidra 0x124a350 | size 92 | symbol _ZNK9Framework21TFixedLengthAllocatorILm128EE6IsFreeEv | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK9Framework21TFixedLengthAllocatorILm128EE6IsFreeEv(long param_1)

{
  uint uVar1;
  ulong uVar2;
  long lVar3;
  
  lVar3 = *(long *)(param_1 + 0x40);
  if (lVar3 != 0) {
    uVar2 = Framework::CMutex::IsInitialized() const(lVar3);
    if ((uVar2 & 1) == 0) {
      Framework::CMutex::Initialize()(lVar3);
    }
    Framework::CMutex::Lock()(lVar3);
  }
  uVar1 = *(uint *)(param_1 + 0x34);
  uVar2 = *(ulong *)(param_1 + 0x20);
  if (lVar3 != 0) {
    Framework::CMutex::Unlock()(lVar3);
  }
  return uVar1 < uVar2;
}

// ==== Framework::TFixedLengthAllocator<128ul>::ActivityRatio() const
// vaddr 0x114a3ac | ghidra 0x124a3ac | size 104 | symbol _ZNK9Framework21TFixedLengthAllocatorILm128EE13ActivityRatioEv | lib libSOA-3.7.0.so | 2026-10-04
float _ZNK9Framework21TFixedLengthAllocatorILm128EE13ActivityRatioEv(long param_1)

{
  ulong uVar1;
  long lVar2;
  float fVar3;
  
  lVar2 = *(long *)(param_1 + 0x40);
  if (lVar2 != 0) {
    uVar1 = Framework::CMutex::IsInitialized() const(lVar2);
    if ((uVar1 & 1) == 0) {
      Framework::CMutex::Initialize()(lVar2);
    }
    Framework::CMutex::Lock()(lVar2);
  }
  uVar1 = *(ulong *)(param_1 + 0x20);
  fVar3 = (float)NEON_ucvtf(*(undefined4 *)(param_1 + 0x34));
  if (lVar2 != 0) {
    Framework::CMutex::Unlock()(lVar2);
  }
  return fVar3 / (float)uVar1;
}

// ==== Framework::TFixedLengthAllocator<128ul>::TotalMemoryAmount() const
// vaddr 0x114a414 | ghidra 0x124a414 | size 16 | symbol _ZNK9Framework21TFixedLengthAllocatorILm128EE17TotalMemoryAmountEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK9Framework21TFixedLengthAllocatorILm128EE17TotalMemoryAmountEv(long param_1)

{
  return *(long *)(param_1 + 0x20) * 0x90;
}

// ==== Framework::TFixedLengthAllocator<128ul>::UsedMemoryAmount() const
// vaddr 0x114a424 | ghidra 0x124a424 | size 88 | symbol _ZNK9Framework21TFixedLengthAllocatorILm128EE16UsedMemoryAmountEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK9Framework21TFixedLengthAllocatorILm128EE16UsedMemoryAmountEv(long param_1)

{
  ulong uVar1;
  long lVar2;
  uint uVar3;
  
  lVar2 = *(long *)(param_1 + 0x40);
  if (lVar2 == 0) {
    uVar3 = *(uint *)(param_1 + 0x34);
  }
  else {
    uVar1 = Framework::CMutex::IsInitialized() const(lVar2);
    if ((uVar1 & 1) == 0) {
      Framework::CMutex::Initialize()(lVar2);
    }
    Framework::CMutex::Lock()(lVar2);
    uVar3 = *(uint *)(param_1 + 0x34);
    Framework::CMutex::Unlock()(lVar2);
  }
  return (ulong)uVar3 * 0x90;
}

// ==== Framework::TFixedLengthAllocator<128ul>::EnableMutex()
// vaddr 0x114a47c | ghidra 0x124a47c | size 84 | symbol _ZN9Framework21TFixedLengthAllocatorILm128EE11EnableMutexEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework21TFixedLengthAllocatorILm128EE11EnableMutexEv(long param_1)

{
  long lVar1;
  
  if (*(long *)(param_1 + 0x40) != 0) {
    return;
  }
  lVar1 = operator new(unsigned long, std::nothrow_t const&)(0xb0,PTR__ZSt7nothrow_02cb9a80);
  if (lVar1 != 0) {
    Framework::CMutex::CMutex()(lVar1);
  }
  *(long *)(param_1 + 0x40) = lVar1;
  (*(code *)PTR__ZN9Framework6CMutex10InitializeEv_02ca3bf0)(lVar1);
  return;
}

// ==== Framework::TFixedLengthAllocator<128ul>::DisableMutex()
// vaddr 0x114a4d0 | ghidra 0x124a4d0 | size 40 | symbol _ZN9Framework21TFixedLengthAllocatorILm128EE12DisableMutexEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework21TFixedLengthAllocatorILm128EE12DisableMutexEv(long param_1)

{
  if (*(long **)(param_1 + 0x40) != (long *)0x0) {
    (**(code **)(**(long **)(param_1 + 0x40) + 8))();
    *(undefined8 *)(param_1 + 0x40) = 0;
  }
  return;
}

// ==== Framework::TFixedLengthAllocator<256ul>::~TFixedLengthAllocator()
// vaddr 0x114a4f8 | ghidra 0x124a4f8 | size 64 | symbol _ZN9Framework21TFixedLengthAllocatorILm256EED2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework21TFixedLengthAllocatorILm256EED2Ev(long *param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZTVN9Framework21TFixedLengthAllocatorILm256EEE_02cb8030 + 0x10;
  *param_1 = (long)puVar1;
  if (((char)param_1[6] != '\0') && (param_1[5] != 0)) {
    operator delete[](void*)();
    puVar1 = (undefined *)*param_1;
  }
                    /* WARNING: Could not recover jumptable at 0x0124a534. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(puVar1 + 0x68))(param_1);
  return;
}

// ==== Framework::TFixedLengthAllocator<256ul>::~TFixedLengthAllocator()
// vaddr 0x114a538 | ghidra 0x124a538 | size 72 | symbol _ZN9Framework21TFixedLengthAllocatorILm256EED0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework21TFixedLengthAllocatorILm256EED0Ev(long *param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZTVN9Framework21TFixedLengthAllocatorILm256EEE_02cb8030 + 0x10;
  *param_1 = (long)puVar1;
  if (((char)param_1[6] != '\0') && (param_1[5] != 0)) {
    operator delete[](void*)();
    puVar1 = (undefined *)*param_1;
  }
  (**(code **)(puVar1 + 0x68))(param_1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Framework::TFixedLengthAllocator<256ul>::BlockSize() const
// vaddr 0x114a580 | ghidra 0x124a580 | size 8 | symbol _ZNK9Framework21TFixedLengthAllocatorILm256EE9BlockSizeEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK9Framework21TFixedLengthAllocatorILm256EE9BlockSizeEv(void)

{
  return 0x100;
}

// ==== Framework::TFixedLengthAllocator<256ul>::MaxBlock() const
// vaddr 0x114a588 | ghidra 0x124a588 | size 8 | symbol _ZNK9Framework21TFixedLengthAllocatorILm256EE8MaxBlockEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK9Framework21TFixedLengthAllocatorILm256EE8MaxBlockEv(long param_1)

{
  return *(undefined8 *)(param_1 + 0x20);
}

// ==== Framework::TFixedLengthAllocator<256ul>::pAllocate(char const*, unsigned int)
// vaddr 0x114a590 | ghidra 0x124a590 | size 244 | symbol _ZN9Framework21TFixedLengthAllocatorILm256EE9pAllocateEPKcj | lib libSOA-3.7.0.so | 2026-10-04
long _ZN9Framework21TFixedLengthAllocatorILm256EE9pAllocateEPKcj(long param_1)

{
  ulong uVar1;
  long lVar2;
  long lVar3;
  long lVar4;
  
  lVar4 = *(long *)(param_1 + 0x40);
  if (lVar4 != 0) {
    uVar1 = Framework::CMutex::IsInitialized() const(lVar4);
    if ((uVar1 & 1) == 0) {
      Framework::CMutex::Initialize()(lVar4);
    }
    Framework::CMutex::Lock()(lVar4);
  }
  if ((ulong)*(uint *)(param_1 + 0x34) < *(ulong *)(param_1 + 0x20)) {
    uVar1 = (ulong)*(uint *)(param_1 + 0x38);
    if (*(ulong *)(param_1 + 0x20) <= uVar1) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db199/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TFixedLengthAllocator.h"*/,0xf9,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,uVar1);
    }
    lVar2 = *(long *)(param_1 + 0x28);
    lVar3 = lVar2 + uVar1 * 0x110;
    *(undefined4 *)(param_1 + 0x38) = *(undefined4 *)(lVar3 + 8);
    if (*(char *)(lVar3 + 3) != '\x01') {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db199/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TFixedLengthAllocator.h"*/,0xfc,&UNK_027db22d/*"Not free."*/);
      lVar2 = *(long *)(param_1 + 0x28);
    }
    *(int *)(param_1 + 0x34) = *(int *)(param_1 + 0x34) + 1;
    *(undefined1 *)(lVar2 + uVar1 * 0x110 + 3) = 0;
    lVar2 = *(long *)(param_1 + 0x28) + uVar1 * 0x110 + 0x10;
  }
  else {
    lVar2 = 0;
  }
  if (lVar4 != 0) {
    Framework::CMutex::Unlock()(lVar4);
  }
  return lVar2;
}

// ==== Framework::TFixedLengthAllocator<256ul>::Free(void*)
// vaddr 0x114a684 | ghidra 0x124a684 | size 208 | symbol _ZN9Framework21TFixedLengthAllocatorILm256EE4FreeEPv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework21TFixedLengthAllocatorILm256EE4FreeEPv(long *param_1,long param_2)

{
  ulong uVar1;
  long lVar2;
  
  lVar2 = param_1[8];
  if (lVar2 != 0) {
    uVar1 = Framework::CMutex::IsInitialized() const(lVar2);
    if ((uVar1 & 1) == 0) {
      Framework::CMutex::Initialize()(lVar2);
    }
    Framework::CMutex::Lock()(lVar2);
  }
  if (param_2 != 0) {
    uVar1 = (**(code **)(*param_1 + 0x30))(param_1,param_2);
    if ((uVar1 & 1) == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db199/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TFixedLengthAllocator.h"*/,0x10f,&UNK_027db237,param_2);
    }
    if (*(char *)(param_2 + -0xd) != '\0') {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db199/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TFixedLengthAllocator.h"*/,0x111,&UNK_027db24f/*"Double free."*/);
    }
    *(undefined1 *)(param_2 + -0xd) = 1;
    *(int *)(param_2 + -8) = (int)param_1[7];
    *(undefined4 *)(param_1 + 7) = *(undefined4 *)(param_2 + -0xc);
    *(int *)((long)param_1 + 0x34) = *(int *)((long)param_1 + 0x34) + -1;
  }
  if (lVar2 != 0) {
    (*(code *)PTR__ZN9Framework6CMutex6UnlockEv_02cb3f98)(lVar2);
    return;
  }
  return;
}

// ==== Framework::TFixedLengthAllocator<256ul>::IsMine(void*) const
// vaddr 0x114a754 | ghidra 0x124a754 | size 128 | symbol _ZNK9Framework21TFixedLengthAllocatorILm256EE6IsMineEPv | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK9Framework21TFixedLengthAllocatorILm256EE6IsMineEPv(long param_1,ulong param_2)

{
  if (param_2 < *(ulong *)(param_1 + 0x28)) {
    return false;
  }
  if (*(ulong *)(param_1 + 0x28) + *(long *)(param_1 + 0x20) * 0x110 <= param_2) {
    return false;
  }
  if (*(char *)(param_1 + 0x18) == '\0') {
    return false;
  }
  if (*(char *)(param_2 - 0x10) == *(char *)(param_1 + 0x18)) {
    if (*(char *)(param_2 - 0xf) == *(char *)(param_1 + 0x19)) {
      return *(char *)(param_2 - 0xe) == *(char *)(param_1 + 0x1a);
    }
    return false;
  }
  return false;
}

// ==== Framework::TFixedLengthAllocator<256ul>::NumAllocated() const
// vaddr 0x114a7d4 | ghidra 0x124a7d4 | size 84 | symbol _ZNK9Framework21TFixedLengthAllocatorILm256EE12NumAllocatedEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK9Framework21TFixedLengthAllocatorILm256EE12NumAllocatedEv(long param_1)

{
  ulong uVar1;
  long lVar2;
  undefined4 uVar3;
  
  lVar2 = *(long *)(param_1 + 0x40);
  if (lVar2 == 0) {
    uVar3 = *(undefined4 *)(param_1 + 0x34);
  }
  else {
    uVar1 = Framework::CMutex::IsInitialized() const(lVar2);
    if ((uVar1 & 1) == 0) {
      Framework::CMutex::Initialize()(lVar2);
    }
    Framework::CMutex::Lock()(lVar2);
    uVar3 = *(undefined4 *)(param_1 + 0x34);
    Framework::CMutex::Unlock()(lVar2);
  }
  return uVar3;
}

// ==== Framework::TFixedLengthAllocator<256ul>::IsFree() const
// vaddr 0x114a828 | ghidra 0x124a828 | size 92 | symbol _ZNK9Framework21TFixedLengthAllocatorILm256EE6IsFreeEv | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK9Framework21TFixedLengthAllocatorILm256EE6IsFreeEv(long param_1)

{
  uint uVar1;
  ulong uVar2;
  long lVar3;
  
  lVar3 = *(long *)(param_1 + 0x40);
  if (lVar3 != 0) {
    uVar2 = Framework::CMutex::IsInitialized() const(lVar3);
    if ((uVar2 & 1) == 0) {
      Framework::CMutex::Initialize()(lVar3);
    }
    Framework::CMutex::Lock()(lVar3);
  }
  uVar1 = *(uint *)(param_1 + 0x34);
  uVar2 = *(ulong *)(param_1 + 0x20);
  if (lVar3 != 0) {
    Framework::CMutex::Unlock()(lVar3);
  }
  return uVar1 < uVar2;
}

// ==== Framework::TFixedLengthAllocator<256ul>::ActivityRatio() const
// vaddr 0x114a884 | ghidra 0x124a884 | size 104 | symbol _ZNK9Framework21TFixedLengthAllocatorILm256EE13ActivityRatioEv | lib libSOA-3.7.0.so | 2026-10-04
float _ZNK9Framework21TFixedLengthAllocatorILm256EE13ActivityRatioEv(long param_1)

{
  ulong uVar1;
  long lVar2;
  float fVar3;
  
  lVar2 = *(long *)(param_1 + 0x40);
  if (lVar2 != 0) {
    uVar1 = Framework::CMutex::IsInitialized() const(lVar2);
    if ((uVar1 & 1) == 0) {
      Framework::CMutex::Initialize()(lVar2);
    }
    Framework::CMutex::Lock()(lVar2);
  }
  uVar1 = *(ulong *)(param_1 + 0x20);
  fVar3 = (float)NEON_ucvtf(*(undefined4 *)(param_1 + 0x34));
  if (lVar2 != 0) {
    Framework::CMutex::Unlock()(lVar2);
  }
  return fVar3 / (float)uVar1;
}

// ==== Framework::TFixedLengthAllocator<256ul>::TotalMemoryAmount() const
// vaddr 0x114a8ec | ghidra 0x124a8ec | size 16 | symbol _ZNK9Framework21TFixedLengthAllocatorILm256EE17TotalMemoryAmountEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK9Framework21TFixedLengthAllocatorILm256EE17TotalMemoryAmountEv(long param_1)

{
  return *(long *)(param_1 + 0x20) * 0x110;
}

// ==== Framework::TFixedLengthAllocator<256ul>::UsedMemoryAmount() const
// vaddr 0x114a8fc | ghidra 0x124a8fc | size 88 | symbol _ZNK9Framework21TFixedLengthAllocatorILm256EE16UsedMemoryAmountEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK9Framework21TFixedLengthAllocatorILm256EE16UsedMemoryAmountEv(long param_1)

{
  ulong uVar1;
  long lVar2;
  uint uVar3;
  
  lVar2 = *(long *)(param_1 + 0x40);
  if (lVar2 == 0) {
    uVar3 = *(uint *)(param_1 + 0x34);
  }
  else {
    uVar1 = Framework::CMutex::IsInitialized() const(lVar2);
    if ((uVar1 & 1) == 0) {
      Framework::CMutex::Initialize()(lVar2);
    }
    Framework::CMutex::Lock()(lVar2);
    uVar3 = *(uint *)(param_1 + 0x34);
    Framework::CMutex::Unlock()(lVar2);
  }
  return (ulong)uVar3 * 0x110;
}

// ==== Framework::TFixedLengthAllocator<256ul>::EnableMutex()
// vaddr 0x114a954 | ghidra 0x124a954 | size 84 | symbol _ZN9Framework21TFixedLengthAllocatorILm256EE11EnableMutexEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework21TFixedLengthAllocatorILm256EE11EnableMutexEv(long param_1)

{
  long lVar1;
  
  if (*(long *)(param_1 + 0x40) != 0) {
    return;
  }
  lVar1 = operator new(unsigned long, std::nothrow_t const&)(0xb0,PTR__ZSt7nothrow_02cb9a80);
  if (lVar1 != 0) {
    Framework::CMutex::CMutex()(lVar1);
  }
  *(long *)(param_1 + 0x40) = lVar1;
  (*(code *)PTR__ZN9Framework6CMutex10InitializeEv_02ca3bf0)(lVar1);
  return;
}

// ==== Framework::TFixedLengthAllocator<256ul>::DisableMutex()
// vaddr 0x114a9a8 | ghidra 0x124a9a8 | size 40 | symbol _ZN9Framework21TFixedLengthAllocatorILm256EE12DisableMutexEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework21TFixedLengthAllocatorILm256EE12DisableMutexEv(long param_1)

{
  if (*(long **)(param_1 + 0x40) != (long *)0x0) {
    (**(code **)(**(long **)(param_1 + 0x40) + 8))();
    *(undefined8 *)(param_1 + 0x40) = 0;
  }
  return;
}

// ==== Framework::TFixedLengthAllocator<512ul>::~TFixedLengthAllocator()
// vaddr 0x114a9d0 | ghidra 0x124a9d0 | size 64 | symbol _ZN9Framework21TFixedLengthAllocatorILm512EED2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework21TFixedLengthAllocatorILm512EED2Ev(long *param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZTVN9Framework21TFixedLengthAllocatorILm512EEE_02cbfa08 + 0x10;
  *param_1 = (long)puVar1;
  if (((char)param_1[6] != '\0') && (param_1[5] != 0)) {
    operator delete[](void*)();
    puVar1 = (undefined *)*param_1;
  }
                    /* WARNING: Could not recover jumptable at 0x0124aa0c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(puVar1 + 0x68))(param_1);
  return;
}

// ==== Framework::TFixedLengthAllocator<512ul>::~TFixedLengthAllocator()
// vaddr 0x114aa10 | ghidra 0x124aa10 | size 72 | symbol _ZN9Framework21TFixedLengthAllocatorILm512EED0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework21TFixedLengthAllocatorILm512EED0Ev(long *param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZTVN9Framework21TFixedLengthAllocatorILm512EEE_02cbfa08 + 0x10;
  *param_1 = (long)puVar1;
  if (((char)param_1[6] != '\0') && (param_1[5] != 0)) {
    operator delete[](void*)();
    puVar1 = (undefined *)*param_1;
  }
  (**(code **)(puVar1 + 0x68))(param_1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Framework::TFixedLengthAllocator<512ul>::BlockSize() const
// vaddr 0x114aa58 | ghidra 0x124aa58 | size 8 | symbol _ZNK9Framework21TFixedLengthAllocatorILm512EE9BlockSizeEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK9Framework21TFixedLengthAllocatorILm512EE9BlockSizeEv(void)

{
  return 0x200;
}

// ==== Framework::TFixedLengthAllocator<512ul>::MaxBlock() const
// vaddr 0x114aa60 | ghidra 0x124aa60 | size 8 | symbol _ZNK9Framework21TFixedLengthAllocatorILm512EE8MaxBlockEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK9Framework21TFixedLengthAllocatorILm512EE8MaxBlockEv(long param_1)

{
  return *(undefined8 *)(param_1 + 0x20);
}

// ==== Framework::TFixedLengthAllocator<512ul>::pAllocate(char const*, unsigned int)
// vaddr 0x114aa68 | ghidra 0x124aa68 | size 244 | symbol _ZN9Framework21TFixedLengthAllocatorILm512EE9pAllocateEPKcj | lib libSOA-3.7.0.so | 2026-10-04
long _ZN9Framework21TFixedLengthAllocatorILm512EE9pAllocateEPKcj(long param_1)

{
  ulong uVar1;
  long lVar2;
  long lVar3;
  long lVar4;
  
  lVar4 = *(long *)(param_1 + 0x40);
  if (lVar4 != 0) {
    uVar1 = Framework::CMutex::IsInitialized() const(lVar4);
    if ((uVar1 & 1) == 0) {
      Framework::CMutex::Initialize()(lVar4);
    }
    Framework::CMutex::Lock()(lVar4);
  }
  if ((ulong)*(uint *)(param_1 + 0x34) < *(ulong *)(param_1 + 0x20)) {
    uVar1 = (ulong)*(uint *)(param_1 + 0x38);
    if (*(ulong *)(param_1 + 0x20) <= uVar1) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db199/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TFixedLengthAllocator.h"*/,0xf9,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,uVar1);
    }
    lVar2 = *(long *)(param_1 + 0x28);
    lVar3 = lVar2 + uVar1 * 0x210;
    *(undefined4 *)(param_1 + 0x38) = *(undefined4 *)(lVar3 + 8);
    if (*(char *)(lVar3 + 3) != '\x01') {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db199/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TFixedLengthAllocator.h"*/,0xfc,&UNK_027db22d/*"Not free."*/);
      lVar2 = *(long *)(param_1 + 0x28);
    }
    *(int *)(param_1 + 0x34) = *(int *)(param_1 + 0x34) + 1;
    *(undefined1 *)(lVar2 + uVar1 * 0x210 + 3) = 0;
    lVar2 = *(long *)(param_1 + 0x28) + uVar1 * 0x210 + 0x10;
  }
  else {
    lVar2 = 0;
  }
  if (lVar4 != 0) {
    Framework::CMutex::Unlock()(lVar4);
  }
  return lVar2;
}

// ==== Framework::TFixedLengthAllocator<512ul>::Free(void*)
// vaddr 0x114ab5c | ghidra 0x124ab5c | size 208 | symbol _ZN9Framework21TFixedLengthAllocatorILm512EE4FreeEPv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework21TFixedLengthAllocatorILm512EE4FreeEPv(long *param_1,long param_2)

{
  ulong uVar1;
  long lVar2;
  
  lVar2 = param_1[8];
  if (lVar2 != 0) {
    uVar1 = Framework::CMutex::IsInitialized() const(lVar2);
    if ((uVar1 & 1) == 0) {
      Framework::CMutex::Initialize()(lVar2);
    }
    Framework::CMutex::Lock()(lVar2);
  }
  if (param_2 != 0) {
    uVar1 = (**(code **)(*param_1 + 0x30))(param_1,param_2);
    if ((uVar1 & 1) == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db199/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TFixedLengthAllocator.h"*/,0x10f,&UNK_027db237,param_2);
    }
    if (*(char *)(param_2 + -0xd) != '\0') {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db199/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TFixedLengthAllocator.h"*/,0x111,&UNK_027db24f/*"Double free."*/);
    }
    *(undefined1 *)(param_2 + -0xd) = 1;
    *(int *)(param_2 + -8) = (int)param_1[7];
    *(undefined4 *)(param_1 + 7) = *(undefined4 *)(param_2 + -0xc);
    *(int *)((long)param_1 + 0x34) = *(int *)((long)param_1 + 0x34) + -1;
  }
  if (lVar2 != 0) {
    (*(code *)PTR__ZN9Framework6CMutex6UnlockEv_02cb3f98)(lVar2);
    return;
  }
  return;
}

// ==== Framework::TFixedLengthAllocator<512ul>::IsMine(void*) const
// vaddr 0x114ac2c | ghidra 0x124ac2c | size 128 | symbol _ZNK9Framework21TFixedLengthAllocatorILm512EE6IsMineEPv | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK9Framework21TFixedLengthAllocatorILm512EE6IsMineEPv(long param_1,ulong param_2)

{
  if (param_2 < *(ulong *)(param_1 + 0x28)) {
    return false;
  }
  if (*(ulong *)(param_1 + 0x28) + *(long *)(param_1 + 0x20) * 0x210 <= param_2) {
    return false;
  }
  if (*(char *)(param_1 + 0x18) == '\0') {
    return false;
  }
  if (*(char *)(param_2 - 0x10) == *(char *)(param_1 + 0x18)) {
    if (*(char *)(param_2 - 0xf) == *(char *)(param_1 + 0x19)) {
      return *(char *)(param_2 - 0xe) == *(char *)(param_1 + 0x1a);
    }
    return false;
  }
  return false;
}

// ==== Framework::TFixedLengthAllocator<512ul>::NumAllocated() const
// vaddr 0x114acac | ghidra 0x124acac | size 84 | symbol _ZNK9Framework21TFixedLengthAllocatorILm512EE12NumAllocatedEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK9Framework21TFixedLengthAllocatorILm512EE12NumAllocatedEv(long param_1)

{
  ulong uVar1;
  long lVar2;
  undefined4 uVar3;
  
  lVar2 = *(long *)(param_1 + 0x40);
  if (lVar2 == 0) {
    uVar3 = *(undefined4 *)(param_1 + 0x34);
  }
  else {
    uVar1 = Framework::CMutex::IsInitialized() const(lVar2);
    if ((uVar1 & 1) == 0) {
      Framework::CMutex::Initialize()(lVar2);
    }
    Framework::CMutex::Lock()(lVar2);
    uVar3 = *(undefined4 *)(param_1 + 0x34);
    Framework::CMutex::Unlock()(lVar2);
  }
  return uVar3;
}

// ==== Framework::TFixedLengthAllocator<512ul>::IsFree() const
// vaddr 0x114ad00 | ghidra 0x124ad00 | size 92 | symbol _ZNK9Framework21TFixedLengthAllocatorILm512EE6IsFreeEv | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK9Framework21TFixedLengthAllocatorILm512EE6IsFreeEv(long param_1)

{
  uint uVar1;
  ulong uVar2;
  long lVar3;
  
  lVar3 = *(long *)(param_1 + 0x40);
  if (lVar3 != 0) {
    uVar2 = Framework::CMutex::IsInitialized() const(lVar3);
    if ((uVar2 & 1) == 0) {
      Framework::CMutex::Initialize()(lVar3);
    }
    Framework::CMutex::Lock()(lVar3);
  }
  uVar1 = *(uint *)(param_1 + 0x34);
  uVar2 = *(ulong *)(param_1 + 0x20);
  if (lVar3 != 0) {
    Framework::CMutex::Unlock()(lVar3);
  }
  return uVar1 < uVar2;
}

// ==== Framework::TFixedLengthAllocator<512ul>::ActivityRatio() const
// vaddr 0x114ad5c | ghidra 0x124ad5c | size 104 | symbol _ZNK9Framework21TFixedLengthAllocatorILm512EE13ActivityRatioEv | lib libSOA-3.7.0.so | 2026-10-04
float _ZNK9Framework21TFixedLengthAllocatorILm512EE13ActivityRatioEv(long param_1)

{
  ulong uVar1;
  long lVar2;
  float fVar3;
  
  lVar2 = *(long *)(param_1 + 0x40);
  if (lVar2 != 0) {
    uVar1 = Framework::CMutex::IsInitialized() const(lVar2);
    if ((uVar1 & 1) == 0) {
      Framework::CMutex::Initialize()(lVar2);
    }
    Framework::CMutex::Lock()(lVar2);
  }
  uVar1 = *(ulong *)(param_1 + 0x20);
  fVar3 = (float)NEON_ucvtf(*(undefined4 *)(param_1 + 0x34));
  if (lVar2 != 0) {
    Framework::CMutex::Unlock()(lVar2);
  }
  return fVar3 / (float)uVar1;
}

// ==== Framework::TFixedLengthAllocator<512ul>::TotalMemoryAmount() const
// vaddr 0x114adc4 | ghidra 0x124adc4 | size 16 | symbol _ZNK9Framework21TFixedLengthAllocatorILm512EE17TotalMemoryAmountEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK9Framework21TFixedLengthAllocatorILm512EE17TotalMemoryAmountEv(long param_1)

{
  return *(long *)(param_1 + 0x20) * 0x210;
}

// ==== Framework::TFixedLengthAllocator<512ul>::UsedMemoryAmount() const
// vaddr 0x114add4 | ghidra 0x124add4 | size 88 | symbol _ZNK9Framework21TFixedLengthAllocatorILm512EE16UsedMemoryAmountEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK9Framework21TFixedLengthAllocatorILm512EE16UsedMemoryAmountEv(long param_1)

{
  ulong uVar1;
  long lVar2;
  uint uVar3;
  
  lVar2 = *(long *)(param_1 + 0x40);
  if (lVar2 == 0) {
    uVar3 = *(uint *)(param_1 + 0x34);
  }
  else {
    uVar1 = Framework::CMutex::IsInitialized() const(lVar2);
    if ((uVar1 & 1) == 0) {
      Framework::CMutex::Initialize()(lVar2);
    }
    Framework::CMutex::Lock()(lVar2);
    uVar3 = *(uint *)(param_1 + 0x34);
    Framework::CMutex::Unlock()(lVar2);
  }
  return (ulong)uVar3 * 0x210;
}

// ==== Framework::TFixedLengthAllocator<512ul>::EnableMutex()
// vaddr 0x114ae2c | ghidra 0x124ae2c | size 84 | symbol _ZN9Framework21TFixedLengthAllocatorILm512EE11EnableMutexEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework21TFixedLengthAllocatorILm512EE11EnableMutexEv(long param_1)

{
  long lVar1;
  
  if (*(long *)(param_1 + 0x40) != 0) {
    return;
  }
  lVar1 = operator new(unsigned long, std::nothrow_t const&)(0xb0,PTR__ZSt7nothrow_02cb9a80);
  if (lVar1 != 0) {
    Framework::CMutex::CMutex()(lVar1);
  }
  *(long *)(param_1 + 0x40) = lVar1;
  (*(code *)PTR__ZN9Framework6CMutex10InitializeEv_02ca3bf0)(lVar1);
  return;
}

// ==== Framework::TFixedLengthAllocator<512ul>::DisableMutex()
// vaddr 0x114ae80 | ghidra 0x124ae80 | size 40 | symbol _ZN9Framework21TFixedLengthAllocatorILm512EE12DisableMutexEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework21TFixedLengthAllocatorILm512EE12DisableMutexEv(long param_1)

{
  if (*(long **)(param_1 + 0x40) != (long *)0x0) {
    (**(code **)(**(long **)(param_1 + 0x40) + 8))();
    *(undefined8 *)(param_1 + 0x40) = 0;
  }
  return;
}

// ==== Framework::TFixedLengthAllocator<192ul>::TFixedLengthAllocator(char, char, char, unsigned long)
// vaddr 0x13b5260 | ghidra 0x14b5260 | size 280 | symbol _ZN9Framework21TFixedLengthAllocatorILm192EEC2Ecccm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework21TFixedLengthAllocatorILm192EEC2Ecccm
               (long *param_1,undefined1 param_2,undefined1 param_3,undefined1 param_4,long param_5)

{
  uint uVar1;
  undefined1 uVar2;
  undefined1 auVar3 [16];
  undefined *puVar4;
  long lVar5;
  long lVar6;
  undefined2 *puVar7;
  ulong uVar8;
  
  puVar4 = PTR__ZTVN9Framework21TFixedLengthAllocatorILm192EEE_02cc4058;
  *(undefined1 *)(param_1 + 3) = param_2;
  *(undefined1 *)((long)param_1 + 0x19) = param_3;
  *(undefined1 *)((long)param_1 + 0x1a) = param_4;
  *(undefined1 *)((long)param_1 + 0x1b) = 0;
  param_1[4] = param_5;
  *(undefined8 *)((long)param_1 + 0x34) = 0;
  *(undefined1 *)(param_1 + 6) = 1;
  *param_1 = (long)(puVar4 + 0x10);
  param_1[8] = 0;
  lVar5 = operator new(unsigned long, std::nothrow_t const&)(0xb0,PTR__ZSt7nothrow_02cb9a80);
  if (lVar5 != 0) {
    Framework::CMutex::CMutex()(lVar5);
  }
  param_1[8] = lVar5;
  Framework::CMutex::Initialize()(lVar5);
  uVar8 = param_1[4];
  auVar3._8_8_ = 0;
  auVar3._0_8_ = uVar8;
  lVar5 = uVar8 * 0xd0;
  if (SUB168(auVar3 * ZEXT816(0xd0),8) != 0) {
    lVar5 = -1;
  }
  lVar5 = operator new[](unsigned long, std::nothrow_t const&)(lVar5,PTR__ZSt7nothrow_02cb9a80);
  param_1[5] = lVar5;
  memset(lVar5,0xcc,uVar8 * 0xd0);
  if (uVar8 == 0) {
    lVar6 = -1;
  }
  else {
    uVar8 = 0;
    do {
      lVar6 = param_1[3];
      uVar2 = *(undefined1 *)((long)param_1 + 0x1a);
      puVar7 = (undefined2 *)(lVar5 + uVar8 * 0xd0);
      *(int *)(puVar7 + 2) = (int)uVar8;
      uVar1 = (int)uVar8 + 1;
      uVar8 = (ulong)uVar1;
      *(undefined1 *)((long)puVar7 + 3) = 1;
      *puVar7 = (short)lVar6;
      *(undefined1 *)(puVar7 + 1) = uVar2;
      *(uint *)(puVar7 + 4) = uVar1;
      lVar5 = param_1[5];
    } while (uVar8 < (ulong)param_1[4]);
    lVar6 = param_1[4] - 1;
  }
  *(undefined4 *)(lVar5 + lVar6 * 0xd0 + 8) = 0xffffffff;
  return;
}

// ==== Framework::TFixedLengthAllocator<192ul>::~TFixedLengthAllocator()
// vaddr 0x13b65dc | ghidra 0x14b65dc | size 64 | symbol _ZN9Framework21TFixedLengthAllocatorILm192EED2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework21TFixedLengthAllocatorILm192EED2Ev(long *param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZTVN9Framework21TFixedLengthAllocatorILm192EEE_02cc4058 + 0x10;
  *param_1 = (long)puVar1;
  if (((char)param_1[6] != '\0') && (param_1[5] != 0)) {
    operator delete[](void*)();
    puVar1 = (undefined *)*param_1;
  }
                    /* WARNING: Could not recover jumptable at 0x014b6618. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(puVar1 + 0x68))(param_1);
  return;
}

// ==== Framework::TFixedLengthAllocator<192ul>::~TFixedLengthAllocator()
// vaddr 0x13b661c | ghidra 0x14b661c | size 72 | symbol _ZN9Framework21TFixedLengthAllocatorILm192EED0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework21TFixedLengthAllocatorILm192EED0Ev(long *param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZTVN9Framework21TFixedLengthAllocatorILm192EEE_02cc4058 + 0x10;
  *param_1 = (long)puVar1;
  if (((char)param_1[6] != '\0') && (param_1[5] != 0)) {
    operator delete[](void*)();
    puVar1 = (undefined *)*param_1;
  }
  (**(code **)(puVar1 + 0x68))(param_1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Framework::TFixedLengthAllocator<192ul>::BlockSize() const
// vaddr 0x13b6664 | ghidra 0x14b6664 | size 8 | symbol _ZNK9Framework21TFixedLengthAllocatorILm192EE9BlockSizeEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK9Framework21TFixedLengthAllocatorILm192EE9BlockSizeEv(void)

{
  return 0xc0;
}

// ==== Framework::TFixedLengthAllocator<192ul>::MaxBlock() const
// vaddr 0x13b666c | ghidra 0x14b666c | size 8 | symbol _ZNK9Framework21TFixedLengthAllocatorILm192EE8MaxBlockEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK9Framework21TFixedLengthAllocatorILm192EE8MaxBlockEv(long param_1)

{
  return *(undefined8 *)(param_1 + 0x20);
}

// ==== Framework::TFixedLengthAllocator<192ul>::pAllocate(char const*, unsigned int)
// vaddr 0x13b6674 | ghidra 0x14b6674 | size 244 | symbol _ZN9Framework21TFixedLengthAllocatorILm192EE9pAllocateEPKcj | lib libSOA-3.7.0.so | 2026-10-04
long _ZN9Framework21TFixedLengthAllocatorILm192EE9pAllocateEPKcj(long param_1)

{
  ulong uVar1;
  long lVar2;
  long lVar3;
  long lVar4;
  
  lVar4 = *(long *)(param_1 + 0x40);
  if (lVar4 != 0) {
    uVar1 = Framework::CMutex::IsInitialized() const(lVar4);
    if ((uVar1 & 1) == 0) {
      Framework::CMutex::Initialize()(lVar4);
    }
    Framework::CMutex::Lock()(lVar4);
  }
  if ((ulong)*(uint *)(param_1 + 0x34) < *(ulong *)(param_1 + 0x20)) {
    uVar1 = (ulong)*(uint *)(param_1 + 0x38);
    if (*(ulong *)(param_1 + 0x20) <= uVar1) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0280bd96/*"C:\BAS_Submission\Client\Project\..\Library\Framework\Source\Framework/TFixedLengthAllocator.h"*/,0xf9,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,uVar1);
    }
    lVar2 = *(long *)(param_1 + 0x28);
    lVar3 = lVar2 + uVar1 * 0xd0;
    *(undefined4 *)(param_1 + 0x38) = *(undefined4 *)(lVar3 + 8);
    if (*(char *)(lVar3 + 3) != '\x01') {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0280bd96/*"C:\BAS_Submission\Client\Project\..\Library\Framework\Source\Framework/TFixedLengthAllocator.h"*/,0xfc,&UNK_027db22d/*"Not free."*/);
      lVar2 = *(long *)(param_1 + 0x28);
    }
    *(int *)(param_1 + 0x34) = *(int *)(param_1 + 0x34) + 1;
    *(undefined1 *)(lVar2 + uVar1 * 0xd0 + 3) = 0;
    lVar2 = *(long *)(param_1 + 0x28) + uVar1 * 0xd0 + 0x10;
  }
  else {
    lVar2 = 0;
  }
  if (lVar4 != 0) {
    Framework::CMutex::Unlock()(lVar4);
  }
  return lVar2;
}

// ==== Framework::TFixedLengthAllocator<192ul>::Free(void*)
// vaddr 0x13b6768 | ghidra 0x14b6768 | size 208 | symbol _ZN9Framework21TFixedLengthAllocatorILm192EE4FreeEPv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework21TFixedLengthAllocatorILm192EE4FreeEPv(long *param_1,long param_2)

{
  ulong uVar1;
  long lVar2;
  
  lVar2 = param_1[8];
  if (lVar2 != 0) {
    uVar1 = Framework::CMutex::IsInitialized() const(lVar2);
    if ((uVar1 & 1) == 0) {
      Framework::CMutex::Initialize()(lVar2);
    }
    Framework::CMutex::Lock()(lVar2);
  }
  if (param_2 != 0) {
    uVar1 = (**(code **)(*param_1 + 0x30))(param_1,param_2);
    if ((uVar1 & 1) == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0280bd96/*"C:\BAS_Submission\Client\Project\..\Library\Framework\Source\Framework/TFixedLengthAllocator.h"*/,0x10f,&UNK_027db237,param_2);
    }
    if (*(char *)(param_2 + -0xd) != '\0') {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0280bd96/*"C:\BAS_Submission\Client\Project\..\Library\Framework\Source\Framework/TFixedLengthAllocator.h"*/,0x111,&UNK_027db24f/*"Double free."*/);
    }
    *(undefined1 *)(param_2 + -0xd) = 1;
    *(int *)(param_2 + -8) = (int)param_1[7];
    *(undefined4 *)(param_1 + 7) = *(undefined4 *)(param_2 + -0xc);
    *(int *)((long)param_1 + 0x34) = *(int *)((long)param_1 + 0x34) + -1;
  }
  if (lVar2 != 0) {
    (*(code *)PTR__ZN9Framework6CMutex6UnlockEv_02cb3f98)(lVar2);
    return;
  }
  return;
}

// ==== Framework::TFixedLengthAllocator<192ul>::IsMine(void*) const
// vaddr 0x13b6838 | ghidra 0x14b6838 | size 128 | symbol _ZNK9Framework21TFixedLengthAllocatorILm192EE6IsMineEPv | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK9Framework21TFixedLengthAllocatorILm192EE6IsMineEPv(long param_1,ulong param_2)

{
  if (param_2 < *(ulong *)(param_1 + 0x28)) {
    return false;
  }
  if (*(ulong *)(param_1 + 0x28) + *(long *)(param_1 + 0x20) * 0xd0 <= param_2) {
    return false;
  }
  if (*(char *)(param_1 + 0x18) == '\0') {
    return false;
  }
  if (*(char *)(param_2 - 0x10) == *(char *)(param_1 + 0x18)) {
    if (*(char *)(param_2 - 0xf) == *(char *)(param_1 + 0x19)) {
      return *(char *)(param_2 - 0xe) == *(char *)(param_1 + 0x1a);
    }
    return false;
  }
  return false;
}

// ==== Framework::TFixedLengthAllocator<192ul>::NumAllocated() const
// vaddr 0x13b68b8 | ghidra 0x14b68b8 | size 84 | symbol _ZNK9Framework21TFixedLengthAllocatorILm192EE12NumAllocatedEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK9Framework21TFixedLengthAllocatorILm192EE12NumAllocatedEv(long param_1)

{
  ulong uVar1;
  long lVar2;
  undefined4 uVar3;
  
  lVar2 = *(long *)(param_1 + 0x40);
  if (lVar2 == 0) {
    uVar3 = *(undefined4 *)(param_1 + 0x34);
  }
  else {
    uVar1 = Framework::CMutex::IsInitialized() const(lVar2);
    if ((uVar1 & 1) == 0) {
      Framework::CMutex::Initialize()(lVar2);
    }
    Framework::CMutex::Lock()(lVar2);
    uVar3 = *(undefined4 *)(param_1 + 0x34);
    Framework::CMutex::Unlock()(lVar2);
  }
  return uVar3;
}

// ==== Framework::TFixedLengthAllocator<192ul>::IsFree() const
// vaddr 0x13b690c | ghidra 0x14b690c | size 92 | symbol _ZNK9Framework21TFixedLengthAllocatorILm192EE6IsFreeEv | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK9Framework21TFixedLengthAllocatorILm192EE6IsFreeEv(long param_1)

{
  uint uVar1;
  ulong uVar2;
  long lVar3;
  
  lVar3 = *(long *)(param_1 + 0x40);
  if (lVar3 != 0) {
    uVar2 = Framework::CMutex::IsInitialized() const(lVar3);
    if ((uVar2 & 1) == 0) {
      Framework::CMutex::Initialize()(lVar3);
    }
    Framework::CMutex::Lock()(lVar3);
  }
  uVar1 = *(uint *)(param_1 + 0x34);
  uVar2 = *(ulong *)(param_1 + 0x20);
  if (lVar3 != 0) {
    Framework::CMutex::Unlock()(lVar3);
  }
  return uVar1 < uVar2;
}

// ==== Framework::TFixedLengthAllocator<192ul>::ActivityRatio() const
// vaddr 0x13b6968 | ghidra 0x14b6968 | size 104 | symbol _ZNK9Framework21TFixedLengthAllocatorILm192EE13ActivityRatioEv | lib libSOA-3.7.0.so | 2026-10-04
float _ZNK9Framework21TFixedLengthAllocatorILm192EE13ActivityRatioEv(long param_1)

{
  ulong uVar1;
  long lVar2;
  float fVar3;
  
  lVar2 = *(long *)(param_1 + 0x40);
  if (lVar2 != 0) {
    uVar1 = Framework::CMutex::IsInitialized() const(lVar2);
    if ((uVar1 & 1) == 0) {
      Framework::CMutex::Initialize()(lVar2);
    }
    Framework::CMutex::Lock()(lVar2);
  }
  uVar1 = *(ulong *)(param_1 + 0x20);
  fVar3 = (float)NEON_ucvtf(*(undefined4 *)(param_1 + 0x34));
  if (lVar2 != 0) {
    Framework::CMutex::Unlock()(lVar2);
  }
  return fVar3 / (float)uVar1;
}

// ==== Framework::TFixedLengthAllocator<192ul>::TotalMemoryAmount() const
// vaddr 0x13b69d0 | ghidra 0x14b69d0 | size 16 | symbol _ZNK9Framework21TFixedLengthAllocatorILm192EE17TotalMemoryAmountEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK9Framework21TFixedLengthAllocatorILm192EE17TotalMemoryAmountEv(long param_1)

{
  return *(long *)(param_1 + 0x20) * 0xd0;
}

// ==== Framework::TFixedLengthAllocator<192ul>::UsedMemoryAmount() const
// vaddr 0x13b69e0 | ghidra 0x14b69e0 | size 88 | symbol _ZNK9Framework21TFixedLengthAllocatorILm192EE16UsedMemoryAmountEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK9Framework21TFixedLengthAllocatorILm192EE16UsedMemoryAmountEv(long param_1)

{
  ulong uVar1;
  long lVar2;
  uint uVar3;
  
  lVar2 = *(long *)(param_1 + 0x40);
  if (lVar2 == 0) {
    uVar3 = *(uint *)(param_1 + 0x34);
  }
  else {
    uVar1 = Framework::CMutex::IsInitialized() const(lVar2);
    if ((uVar1 & 1) == 0) {
      Framework::CMutex::Initialize()(lVar2);
    }
    Framework::CMutex::Lock()(lVar2);
    uVar3 = *(uint *)(param_1 + 0x34);
    Framework::CMutex::Unlock()(lVar2);
  }
  return (ulong)uVar3 * 0xd0;
}

// ==== Framework::TFixedLengthAllocator<192ul>::EnableMutex()
// vaddr 0x13b6a38 | ghidra 0x14b6a38 | size 84 | symbol _ZN9Framework21TFixedLengthAllocatorILm192EE11EnableMutexEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework21TFixedLengthAllocatorILm192EE11EnableMutexEv(long param_1)

{
  long lVar1;
  
  if (*(long *)(param_1 + 0x40) != 0) {
    return;
  }
  lVar1 = operator new(unsigned long, std::nothrow_t const&)(0xb0,PTR__ZSt7nothrow_02cb9a80);
  if (lVar1 != 0) {
    Framework::CMutex::CMutex()(lVar1);
  }
  *(long *)(param_1 + 0x40) = lVar1;
  (*(code *)PTR__ZN9Framework6CMutex10InitializeEv_02ca3bf0)(lVar1);
  return;
}

// ==== Framework::TFixedLengthAllocator<192ul>::DisableMutex()
// vaddr 0x13b6a8c | ghidra 0x14b6a8c | size 40 | symbol _ZN9Framework21TFixedLengthAllocatorILm192EE12DisableMutexEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework21TFixedLengthAllocatorILm192EE12DisableMutexEv(long param_1)

{
  if (*(long **)(param_1 + 0x40) != (long *)0x0) {
    (**(code **)(**(long **)(param_1 + 0x40) + 8))();
    *(undefined8 *)(param_1 + 0x40) = 0;
  }
  return;
}

// ==== Framework::CAssignedMemoryManagerForSTLAllocator::Attach(Aska::MemoryManager*)
// vaddr 0x1e9b39c | ghidra 0x1f9b39c | size 68 | symbol _ZN9Framework37CAssignedMemoryManagerForSTLAllocator6AttachEPN4Aska13MemoryManagerE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework37CAssignedMemoryManagerForSTLAllocator6AttachEPN4Aska13MemoryManagerE
               (undefined8 param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZN9Framework37CAssignedMemoryManagerForSTLAllocator16m_pMemoryManagerE_02cbf908;
  if (*(long *)PTR__ZN9Framework37CAssignedMemoryManagerForSTLAllocator16m_pMemoryManagerE_02cbf908
      != 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029660bb/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\STL_Allocator.cpp"*/,0x18,&UNK_02966114/*"m_pMemoryManager isn't null.(%08x)"*/);
  }
  *(undefined8 *)puVar1 = param_1;
  return;
}

// ==== Framework::CAssignedMemoryManagerForSTLAllocator::CreateAndAttach(unsigned long)
// vaddr 0x1e9b3e0 | ghidra 0x1f9b3e0 | size 212 | symbol _ZN9Framework37CAssignedMemoryManagerForSTLAllocator15CreateAndAttachEm | lib libSOA-3.7.0.so | 2026-10-04
long _ZN9Framework37CAssignedMemoryManagerForSTLAllocator15CreateAndAttachEm(undefined8 param_1)

{
  undefined *puVar1;
  long lVar2;
  ulong uVar3;
  long lVar4;
  undefined8 uVar5;
  
  lVar2 = operator new(unsigned long, std::nothrow_t const&)(0xf0,PTR__ZSt7nothrow_02cb9a80);
  if (lVar2 != 0) {
    Aska::MemoryManager::MemoryManager()(lVar2);
  }
  uVar3 = Aska::MemoryManager::InitHeap(unsigned long)(lVar2,param_1);
  if ((uVar3 & 1) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029660bb/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\STL_Allocator.cpp"*/,0x22,&UNK_029614eb/*"result is null."*/);
  }
  puVar1 = PTR__ZN9Framework10TSingletonINS_18CApplicationMemoryEE11m_pInstanceE_02cb8148;
  lVar4 = *(long *)PTR__ZN9Framework10TSingletonINS_18CApplicationMemoryEE11m_pInstanceE_02cb8148;
  if (lVar4 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029612b1/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar4 = *(long *)puVar1;
  }
  uVar5 = Framework::CApplicationMemory::rDefaultBadAllocateNotifyRetry()(lVar4);
  *(undefined8 *)(lVar2 + 0x30) = uVar5;
  puVar1 = PTR__ZN9Framework37CAssignedMemoryManagerForSTLAllocator16m_pMemoryManagerE_02cbf908;
  if (*(long *)PTR__ZN9Framework37CAssignedMemoryManagerForSTLAllocator16m_pMemoryManagerE_02cbf908
      != 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029660bb/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\STL_Allocator.cpp"*/,0x18,&UNK_02966114/*"m_pMemoryManager isn't null.(%08x)"*/);
  }
  *(long *)puVar1 = lVar2;
  Framework::gReportMemoryManagerC(Aska::MemoryManager&, char const*)(lVar2,&UNK_02966168/*"STL"*/);
  return lVar2;
}

// ==== Framework::CAssignedMemoryManagerForSTLAllocator::ReportC()
// vaddr 0x1e9b4b4 | ghidra 0x1f9b4b4 | size 32 | symbol _ZN9Framework37CAssignedMemoryManagerForSTLAllocator7ReportCEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework37CAssignedMemoryManagerForSTLAllocator7ReportCEv(void)

{
  if (*(long *)PTR__ZN9Framework37CAssignedMemoryManagerForSTLAllocator16m_pMemoryManagerE_02cbf908
      != 0) {
    (*(code *)PTR__ZN9Framework21gReportMemoryManagerCERN4Aska13MemoryManagerEPKc_02cb3d38)
              (*(long *)
                PTR__ZN9Framework37CAssignedMemoryManagerForSTLAllocator16m_pMemoryManagerE_02cbf908
               ,&UNK_02966168/*"STL"*/);
    return;
  }
  return;
}

// ==== Framework::CAssignedMemoryManagerForSTLAllocator::AttachFixedLengthAllocator(Framework::CFixedLengthAllocatorContainer*)
// vaddr 0x1e9b4d4 | ghidra 0x1f9b4d4 | size 68 | symbol _ZN9Framework37CAssignedMemoryManagerForSTLAllocator26AttachFixedLengthAllocatorEPNS_30CFixedLengthAllocatorContainerE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework37CAssignedMemoryManagerForSTLAllocator26AttachFixedLengthAllocatorEPNS_30CFixedLengthAllocatorContainerE
               (long param_1)

{
  ulong uVar1;
  
  if ((param_1 != 0) && (uVar1 = Framework::CFixedLengthAllocatorContainer::IsInitialized() const(param_1), (uVar1 & 1) == 0)) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029660bb/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\STL_Allocator.cpp"*/,0x37,&UNK_02966137/*"apFixedLengthAllocator->IsInitialized() is null."*/);
  }
  *(long *)
   PTR__ZN9Framework37CAssignedMemoryManagerForSTLAllocator32m_pFixedLengthAllocatorContainerE_02cbac40
       = param_1;
  return;
}

// ==== Framework::CAssignedMemoryManagerForSTLAllocator::pAttachFixedLengthAllocator()
// vaddr 0x1e9b518 | ghidra 0x1f9b518 | size 16 | symbol _ZN9Framework37CAssignedMemoryManagerForSTLAllocator27pAttachFixedLengthAllocatorEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN9Framework37CAssignedMemoryManagerForSTLAllocator27pAttachFixedLengthAllocatorEv(void)

{
  return *(undefined8 *)
          PTR__ZN9Framework37CAssignedMemoryManagerForSTLAllocator32m_pFixedLengthAllocatorContainerE_02cbac40
  ;
}

// ==== Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)
// vaddr 0x1e9b528 | ghidra 0x1f9b528 | size 112 | symbol _ZN9Framework37CAssignedMemoryManagerForSTLAllocator8AllocateEmPKcj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework37CAssignedMemoryManagerForSTLAllocator8AllocateEmPKcj
               (undefined8 param_1,undefined8 param_2,undefined4 param_3)

{
  long lVar1;
  
  if ((*(long *)
        PTR__ZN9Framework37CAssignedMemoryManagerForSTLAllocator32m_pFixedLengthAllocatorContainerE_02cbac40
       != 0) &&
     (lVar1 = Framework::CFixedLengthAllocatorContainer::pAllocate(unsigned long, char const*, unsigned int)(*(long *)
                               PTR__ZN9Framework37CAssignedMemoryManagerForSTLAllocator32m_pFixedLengthAllocatorContainerE_02cbac40
                              ,param_1,param_2,param_3), lVar1 != 0)) {
    return;
  }
  if (*(long *)PTR__ZN9Framework37CAssignedMemoryManagerForSTLAllocator16m_pMemoryManagerE_02cbf908
      != 0) {
    (*(code *)PTR__ZN4Aska13MemoryManager6MallocEm_02ca1310)
              (*(long *)
                PTR__ZN9Framework37CAssignedMemoryManagerForSTLAllocator16m_pMemoryManagerE_02cbf908
               ,param_1);
    return;
  }
  (*(code *)PTR__ZnamRKSt9nothrow_t_02cb0738)(param_1,PTR__ZSt7nothrow_02cb9a80);
  return;
}

// ==== Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)
// vaddr 0x1e9b598 | ghidra 0x1f9b598 | size 88 | symbol _ZN9Framework37CAssignedMemoryManagerForSTLAllocator4FreeEPv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework37CAssignedMemoryManagerForSTLAllocator4FreeEPv(long param_1)

{
  ulong uVar1;
  
  if (param_1 != 0) {
    if ((*(long *)
          PTR__ZN9Framework37CAssignedMemoryManagerForSTLAllocator32m_pFixedLengthAllocatorContainerE_02cbac40
         == 0) ||
       (uVar1 = Framework::CFixedLengthAllocatorContainer::Free(void*)(*(long *)
                                 PTR__ZN9Framework37CAssignedMemoryManagerForSTLAllocator32m_pFixedLengthAllocatorContainerE_02cbac40
                                ,param_1), (uVar1 & 1) == 0)) {
      if (*(long *)
           PTR__ZN9Framework37CAssignedMemoryManagerForSTLAllocator16m_pMemoryManagerE_02cbf908 != 0
         ) {
        (*(code *)PTR__ZN4Aska13MemoryManager9LocalFreeEPv_02cb5c60)
                  (*(long *)
                    PTR__ZN9Framework37CAssignedMemoryManagerForSTLAllocator16m_pMemoryManagerE_02cbf908
                   ,param_1);
        return;
      }
      (*(code *)PTR__ZdaPv_02cb5db8)(param_1);
      return;
    }
  }
  return;
}

// ==== Framework::CAssignedMemoryManagerForSTLAllocator::ReportS()
// vaddr 0x1e9b5f0 | ghidra 0x1f9b5f0 | size 32 | symbol _ZN9Framework37CAssignedMemoryManagerForSTLAllocator7ReportSEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework37CAssignedMemoryManagerForSTLAllocator7ReportSEv(void)

{
  if (*(long *)PTR__ZN9Framework37CAssignedMemoryManagerForSTLAllocator16m_pMemoryManagerE_02cbf908
      != 0) {
    (*(code *)PTR__ZN9Framework21gReportMemoryManagerSERN4Aska13MemoryManagerEPKc_02c8f658)
              (*(long *)
                PTR__ZN9Framework37CAssignedMemoryManagerForSTLAllocator16m_pMemoryManagerE_02cbf908
               ,&UNK_02966168/*"STL"*/);
    return;
  }
  return;
}

// ==== Framework::CAssignedMemoryManagerForSTLAllocator::IsEnableReportByEachAccess(bool)
// vaddr 0x1e9b610 | ghidra 0x1f9b610 | size 28 | symbol _ZN9Framework37CAssignedMemoryManagerForSTLAllocator26IsEnableReportByEachAccessEb | lib libSOA-3.7.0.so | 2026-10-04
undefined1
_ZN9Framework37CAssignedMemoryManagerForSTLAllocator26IsEnableReportByEachAccessEb(byte param_1)

{
  undefined1 uVar1;
  
  uVar1 = *
          PTR__ZN9Framework37CAssignedMemoryManagerForSTLAllocator28m_IsEnableReportByEachAccessE_02cbe2c8
  ;
  *PTR__ZN9Framework37CAssignedMemoryManagerForSTLAllocator28m_IsEnableReportByEachAccessE_02cbe2c8
       = param_1 & 1;
  return uVar1;
}

// ==== Framework::CAssignedMemoryManagerForSTLAllocator::pAttachedMemoryManager()
// vaddr 0x1e9b62c | ghidra 0x1f9b62c | size 16 | symbol _ZN9Framework37CAssignedMemoryManagerForSTLAllocator22pAttachedMemoryManagerEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN9Framework37CAssignedMemoryManagerForSTLAllocator22pAttachedMemoryManagerEv(void)

{
  return *(undefined8 *)
          PTR__ZN9Framework37CAssignedMemoryManagerForSTLAllocator16m_pMemoryManagerE_02cbf908;
}

// ==== Framework::CFixedLengthAllocatorContainer::CFixedLengthAllocatorContainer()
// vaddr 0x1e9d6c0 | ghidra 0x1f9d6c0 | size 24 | symbol _ZN9Framework30CFixedLengthAllocatorContainerC2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework30CFixedLengthAllocatorContainerC1Ev(long *param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZTVN9Framework16TObjectContainerIPNS_21IFixedLengthAllocatorEEE_02cb8158;
  param_1[2] = 0;
  *param_1 = (long)(puVar1 + 0x10);
  return;
}

// ==== Framework::CFixedLengthAllocatorContainer::~CFixedLengthAllocatorContainer()
// vaddr 0x1e9d6d8 | ghidra 0x1f9d6d8 | size 52 | symbol _ZN9Framework30CFixedLengthAllocatorContainerD2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework30CFixedLengthAllocatorContainerD1Ev(long *param_1)

{
  Framework::CFixedLengthAllocatorContainer::Release()();
  *param_1 = (long)(PTR__ZTVN9Framework16TObjectContainerIPNS_21IFixedLengthAllocatorEEE_02cb8158 +
                   0x10);
  if (param_1[2] != 0) {
    operator delete[](void*)();
    param_1[2] = 0;
  }
  return;
}

// ==== Framework::CFixedLengthAllocatorContainer::Release()
// vaddr 0x1e9d70c | ghidra 0x1f9d70c | size 256 | symbol _ZN9Framework30CFixedLengthAllocatorContainer7ReleaseEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework30CFixedLengthAllocatorContainer7ReleaseEv(long *param_1)

{
  long lVar1;
  ulong uVar2;
  undefined8 uVar3;
  long *plVar4;
  ulong uVar5;
  
  lVar1 = param_1[2];
  if (lVar1 != 0) {
    uVar5 = 0;
    while( true ) {
      if (lVar1 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965e66/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TObjectContainer.h"*/,0x3e,&UNK_027ee29f/*"m_pElements is null."*/);
        lVar1 = param_1[2];
      }
      if ((ulong)param_1[1] <= uVar5) break;
      if (lVar1 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965e66/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TObjectContainer.h"*/,0x44,&UNK_027ee29f/*"m_pElements is null."*/);
      }
      uVar2 = (**(code **)(*param_1 + 0x20))(param_1);
      if (uVar2 <= uVar5) {
        uVar3 = (**(code **)(*param_1 + 0x20))(param_1);
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965e66/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TObjectContainer.h"*/,0x45,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,uVar5,uVar3);
      }
      lVar1 = param_1[2];
      plVar4 = *(long **)(lVar1 + uVar5 * 8);
      if (plVar4 != (long *)0x0) {
        (**(code **)(*plVar4 + 8))(plVar4);
        lVar1 = param_1[2];
      }
      uVar5 = (ulong)((int)uVar5 + 1);
    }
    if (lVar1 != 0) {
      operator delete[](void*)();
      param_1[2] = 0;
    }
  }
  return;
}

// ==== Framework::TObjectContainer<Framework::IFixedLengthAllocator*>::~TObjectContainer()
// vaddr 0x1e9d80c | ghidra 0x1f9d80c | size 48 | symbol _ZN9Framework16TObjectContainerIPNS_21IFixedLengthAllocatorEED2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework16TObjectContainerIPNS_21IFixedLengthAllocatorEED2Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN9Framework16TObjectContainerIPNS_21IFixedLengthAllocatorEEE_02cb8158 +
                   0x10);
  if (param_1[2] != 0) {
    operator delete[](void*)();
    param_1[2] = 0;
  }
  return;
}

// ==== Framework::CFixedLengthAllocatorContainer::Initialize(Framework::IFixedLengthAllocator**, unsigned int)
// vaddr 0x1e9d83c | ghidra 0x1f9d83c | size 340 | symbol _ZN9Framework30CFixedLengthAllocatorContainer10InitializeEPPNS_21IFixedLengthAllocatorEj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework30CFixedLengthAllocatorContainer10InitializeEPPNS_21IFixedLengthAllocatorEj
               (long *param_1,long param_2,uint param_3)

{
  long lVar1;
  ulong uVar2;
  undefined8 uVar3;
  ulong uVar4;
  undefined8 uVar5;
  
  if ((param_1[2] != 0) && (Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029663d3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\TFixedLengthAllocator.cpp"*/,0x65,&UNK_02966434/*"m_Allocators.IsInitialized() isn't null.(%08x)"*/,1), param_1[2] != 0)) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965e66/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TObjectContainer.h"*/,0x25,&UNK_027ee2b4/*"m_pElements isn't null.(%08x)"*/);
  }
  param_1[1] = (ulong)param_3;
  lVar1 = operator new[](unsigned long, std::nothrow_t const&)((ulong)param_3 << 3,PTR__ZSt7nothrow_02cb9a80);
  param_1[2] = lVar1;
  uVar4 = 0;
  while( true ) {
    if (lVar1 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965e66/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TObjectContainer.h"*/,0x3e,&UNK_027ee29f/*"m_pElements is null."*/);
    }
    if ((ulong)param_1[1] <= uVar4) break;
    uVar5 = *(undefined8 *)(param_2 + uVar4 * 8);
    if (param_1[2] == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965e66/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TObjectContainer.h"*/,0x44,&UNK_027ee29f/*"m_pElements is null."*/);
    }
    uVar2 = (**(code **)(*param_1 + 0x20))(param_1);
    if (uVar2 <= uVar4) {
      uVar3 = (**(code **)(*param_1 + 0x20))(param_1);
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965e66/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TObjectContainer.h"*/,0x45,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,uVar4,uVar3);
    }
    *(undefined8 *)(param_1[2] + uVar4 * 8) = uVar5;
    lVar1 = param_1[2];
    uVar4 = (ulong)((int)uVar4 + 1);
  }
  return;
}

// ==== Framework::TObjectContainer<Framework::IFixedLengthAllocator*>::Initialize(unsigned long)
// vaddr 0x1e9d990 | ghidra 0x1f9d990 | size 100 | symbol _ZN9Framework16TObjectContainerIPNS_21IFixedLengthAllocatorEE10InitializeEm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework16TObjectContainerIPNS_21IFixedLengthAllocatorEE10InitializeEm
               (long param_1,ulong param_2)

{
  undefined1 auVar1 [16];
  undefined8 uVar2;
  long lVar3;
  
  if (*(long *)(param_1 + 0x10) != 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965e66/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TObjectContainer.h"*/,0x25,&UNK_027ee2b4/*"m_pElements isn't null.(%08x)"*/);
  }
  *(ulong *)(param_1 + 8) = param_2;
  auVar1._8_8_ = 0;
  auVar1._0_8_ = param_2;
  lVar3 = param_2 << 3;
  if (SUB168(auVar1 * ZEXT816(8),8) != 0) {
    lVar3 = -1;
  }
  uVar2 = operator new[](unsigned long, std::nothrow_t const&)(lVar3,PTR__ZSt7nothrow_02cb9a80);
  *(undefined8 *)(param_1 + 0x10) = uVar2;
  return;
}

// ==== Framework::TObjectContainer<Framework::IFixedLengthAllocator*>::NumElements() const
// vaddr 0x1e9d9f4 | ghidra 0x1f9d9f4 | size 52 | symbol _ZNK9Framework16TObjectContainerIPNS_21IFixedLengthAllocatorEE11NumElementsEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZNK9Framework16TObjectContainerIPNS_21IFixedLengthAllocatorEE11NumElementsEv(long param_1)

{
  if (*(long *)(param_1 + 0x10) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965e66/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TObjectContainer.h"*/,0x3e,&UNK_027ee29f/*"m_pElements is null."*/);
  }
  return *(undefined8 *)(param_1 + 8);
}

// ==== Framework::TObjectContainer<Framework::IFixedLengthAllocator*>::rElement(unsigned long)
// vaddr 0x1e9da28 | ghidra 0x1f9da28 | size 140 | symbol _ZN9Framework16TObjectContainerIPNS_21IFixedLengthAllocatorEE8rElementEm | lib libSOA-3.7.0.so | 2026-10-04
long _ZN9Framework16TObjectContainerIPNS_21IFixedLengthAllocatorEE8rElementEm
               (long *param_1,ulong param_2)

{
  ulong uVar1;
  undefined8 uVar2;
  
  if (param_1[2] == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965e66/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TObjectContainer.h"*/,0x44,&UNK_027ee29f/*"m_pElements is null."*/);
  }
  uVar1 = (**(code **)(*param_1 + 0x20))(param_1);
  if (uVar1 <= param_2) {
    uVar2 = (**(code **)(*param_1 + 0x20))(param_1);
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965e66/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TObjectContainer.h"*/,0x45,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,param_2,uVar2);
  }
  return param_1[2] + param_2 * 8;
}

// ==== Framework::CFixedLengthAllocatorContainer::IsInitialized() const
// vaddr 0x1e9dab4 | ghidra 0x1f9dab4 | size 16 | symbol _ZNK9Framework30CFixedLengthAllocatorContainer13IsInitializedEv | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK9Framework30CFixedLengthAllocatorContainer13IsInitializedEv(long param_1)

{
  return *(long *)(param_1 + 0x10) != 0;
}

// ==== Framework::CFixedLengthAllocatorContainer::pAllocate(unsigned long, char const*, unsigned int)
// vaddr 0x1e9dac4 | ghidra 0x1f9dac4 | size 336 | symbol _ZN9Framework30CFixedLengthAllocatorContainer9pAllocateEmPKcj | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN9Framework30CFixedLengthAllocatorContainer9pAllocateEmPKcj
          (long *param_1,ulong param_2,undefined8 param_3,undefined4 param_4)

{
  ulong uVar1;
  undefined8 uVar2;
  ulong uVar3;
  long *plVar4;
  uint uVar5;
  
  if (param_1[2] == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029663d3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\TFixedLengthAllocator.cpp"*/,0x83,&UNK_02966463/*"m_Allocators.IsInitialized() is null."*/);
    uVar5 = 0;
    goto code_r0x01f9db14;
  }
  uVar3 = 0;
  uVar5 = 0;
  while( true ) {
    if ((ulong)param_1[1] <= uVar3) {
      return 0;
    }
    if (param_1[2] == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965e66/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TObjectContainer.h"*/,0x44,&UNK_027ee29f/*"m_pElements is null."*/);
    }
    uVar1 = (**(code **)(*param_1 + 0x20))(param_1);
    if (uVar1 <= uVar3) {
      uVar2 = (**(code **)(*param_1 + 0x20))(param_1);
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965e66/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TObjectContainer.h"*/,0x45,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,uVar3,uVar2);
    }
    plVar4 = *(long **)(param_1[2] + uVar3 * 8);
    uVar3 = (**(code **)(*plVar4 + 0x10))(plVar4);
    if (param_2 <= uVar3) break;
    uVar5 = uVar5 + 1;
code_r0x01f9db14:
    uVar3 = (ulong)uVar5;
    if (param_1[2] == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965e66/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TObjectContainer.h"*/,0x3e,&UNK_027ee29f/*"m_pElements is null."*/);
    }
  }
                    /* WARNING: Could not recover jumptable at 0x01f9dc10. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  uVar2 = (**(code **)(*plVar4 + 0x20))(plVar4,param_3,param_4);
  return uVar2;
}

// ==== Framework::CFixedLengthAllocatorContainer::Free(void*)
// vaddr 0x1e9dc14 | ghidra 0x1f9dc14 | size 308 | symbol _ZN9Framework30CFixedLengthAllocatorContainer4FreeEPv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN9Framework30CFixedLengthAllocatorContainer4FreeEPv(long *param_1,undefined8 param_2)

{
  ulong uVar1;
  undefined8 uVar2;
  ulong uVar3;
  long *plVar4;
  uint uVar5;
  
  if (param_1[2] == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029663d3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\TFixedLengthAllocator.cpp"*/,0x9d,&UNK_02966463/*"m_Allocators.IsInitialized() is null."*/);
    uVar5 = 0;
    goto code_r0x01f9dc58;
  }
  uVar3 = 0;
  uVar5 = 0;
  while( true ) {
    if ((ulong)param_1[1] <= uVar3) {
      return 0;
    }
    if (param_1[2] == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965e66/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TObjectContainer.h"*/,0x44,&UNK_027ee29f/*"m_pElements is null."*/);
    }
    uVar1 = (**(code **)(*param_1 + 0x20))(param_1);
    if (uVar1 <= uVar3) {
      uVar2 = (**(code **)(*param_1 + 0x20))(param_1);
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965e66/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TObjectContainer.h"*/,0x45,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,uVar3,uVar2);
    }
    plVar4 = *(long **)(param_1[2] + uVar3 * 8);
    uVar3 = (**(code **)(*plVar4 + 0x30))(plVar4,param_2);
    if ((uVar3 & 1) != 0) break;
    uVar5 = uVar5 + 1;
code_r0x01f9dc58:
    uVar3 = (ulong)uVar5;
    if (param_1[2] == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965e66/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TObjectContainer.h"*/,0x3e,&UNK_027ee29f/*"m_pElements is null."*/);
    }
  }
  (**(code **)(*plVar4 + 0x28))(plVar4,param_2);
  return 1;
}

// ==== Framework::CFixedLengthAllocatorContainer::IsMine(void*) const
// vaddr 0x1e9dd48 | ghidra 0x1f9dd48 | size 284 | symbol _ZNK9Framework30CFixedLengthAllocatorContainer6IsMineEPv | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZNK9Framework30CFixedLengthAllocatorContainer6IsMineEPv(long *param_1,undefined8 param_2)

{
  ulong uVar1;
  undefined8 uVar2;
  long *plVar3;
  ulong uVar4;
  uint uVar5;
  
  if (param_1[2] == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029663d3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\TFixedLengthAllocator.cpp"*/,0xae,&UNK_02966463/*"m_Allocators.IsInitialized() is null."*/);
    uVar5 = 0;
    goto code_r0x01f9dd8c;
  }
  uVar4 = 0;
  uVar5 = 0;
  while( true ) {
    if ((ulong)param_1[1] <= uVar4) {
      return 0;
    }
    if (param_1[2] == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965e66/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TObjectContainer.h"*/,0x4b,&UNK_027ee29f/*"m_pElements is null."*/);
    }
    uVar1 = (**(code **)(*param_1 + 0x20))(param_1);
    if (uVar1 <= uVar4) {
      uVar2 = (**(code **)(*param_1 + 0x20))(param_1);
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965e66/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TObjectContainer.h"*/,0x4c,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,uVar4,uVar2);
    }
    plVar3 = *(long **)(param_1[2] + uVar4 * 8);
    uVar4 = (**(code **)(*plVar3 + 0x30))(plVar3,param_2);
    if ((uVar4 & 1) != 0) break;
    uVar5 = uVar5 + 1;
code_r0x01f9dd8c:
    uVar4 = (ulong)uVar5;
    if (param_1[2] == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965e66/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TObjectContainer.h"*/,0x3e,&UNK_027ee29f/*"m_pElements is null."*/);
    }
  }
  return 1;
}

// ==== Framework::TObjectContainer<Framework::IFixedLengthAllocator*>::crElement(unsigned long) const
// vaddr 0x1e9de64 | ghidra 0x1f9de64 | size 140 | symbol _ZNK9Framework16TObjectContainerIPNS_21IFixedLengthAllocatorEE9crElementEm | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK9Framework16TObjectContainerIPNS_21IFixedLengthAllocatorEE9crElementEm
               (long *param_1,ulong param_2)

{
  ulong uVar1;
  undefined8 uVar2;
  
  if (param_1[2] == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965e66/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TObjectContainer.h"*/,0x4b,&UNK_027ee29f/*"m_pElements is null."*/);
  }
  uVar1 = (**(code **)(*param_1 + 0x20))(param_1);
  if (uVar1 <= param_2) {
    uVar2 = (**(code **)(*param_1 + 0x20))(param_1);
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965e66/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TObjectContainer.h"*/,0x4c,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,param_2,uVar2);
  }
  return param_1[2] + param_2 * 8;
}

// ==== Framework::CFixedLengthAllocatorContainer::EnableMutex()
// vaddr 0x1e9def0 | ghidra 0x1f9def0 | size 252 | symbol _ZN9Framework30CFixedLengthAllocatorContainer11EnableMutexEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework30CFixedLengthAllocatorContainer11EnableMutexEv(long *param_1)

{
  ulong uVar1;
  undefined8 uVar2;
  ulong uVar3;
  uint uVar4;
  
  if (param_1[2] != 0) {
    uVar3 = 0;
    uVar4 = 0;
    while (uVar3 < (ulong)param_1[1]) {
      if (param_1[2] == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965e66/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TObjectContainer.h"*/,0x44,&UNK_027ee29f/*"m_pElements is null."*/);
      }
      uVar1 = (**(code **)(*param_1 + 0x20))(param_1);
      if (uVar1 <= uVar3) {
        uVar2 = (**(code **)(*param_1 + 0x20))(param_1);
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965e66/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TObjectContainer.h"*/,0x45,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,uVar3,uVar2);
      }
      (**(code **)(**(long **)(param_1[2] + uVar3 * 8) + 0x60))();
      uVar4 = uVar4 + 1;
code_r0x01f9df2c:
      uVar3 = (ulong)uVar4;
      if (param_1[2] == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965e66/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TObjectContainer.h"*/,0x3e,&UNK_027ee29f/*"m_pElements is null."*/);
      }
    }
    return;
  }
  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029663d3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\TFixedLengthAllocator.cpp"*/,0xbd,&UNK_02966463/*"m_Allocators.IsInitialized() is null."*/);
  uVar4 = 0;
  goto code_r0x01f9df2c;
}

// ==== Framework::CFixedLengthAllocatorContainer::DisableMutex()
// vaddr 0x1e9dfec | ghidra 0x1f9dfec | size 252 | symbol _ZN9Framework30CFixedLengthAllocatorContainer12DisableMutexEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework30CFixedLengthAllocatorContainer12DisableMutexEv(long *param_1)

{
  ulong uVar1;
  undefined8 uVar2;
  ulong uVar3;
  uint uVar4;
  
  if (param_1[2] != 0) {
    uVar3 = 0;
    uVar4 = 0;
    while (uVar3 < (ulong)param_1[1]) {
      if (param_1[2] == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965e66/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TObjectContainer.h"*/,0x44,&UNK_027ee29f/*"m_pElements is null."*/);
      }
      uVar1 = (**(code **)(*param_1 + 0x20))(param_1);
      if (uVar1 <= uVar3) {
        uVar2 = (**(code **)(*param_1 + 0x20))(param_1);
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965e66/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TObjectContainer.h"*/,0x45,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,uVar3,uVar2);
      }
      (**(code **)(**(long **)(param_1[2] + uVar3 * 8) + 0x68))();
      uVar4 = uVar4 + 1;
code_r0x01f9e028:
      uVar3 = (ulong)uVar4;
      if (param_1[2] == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965e66/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TObjectContainer.h"*/,0x3e,&UNK_027ee29f/*"m_pElements is null."*/);
      }
    }
    return;
  }
  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029663d3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\TFixedLengthAllocator.cpp"*/,199,&UNK_02966463/*"m_Allocators.IsInitialized() is null."*/);
  uVar4 = 0;
  goto code_r0x01f9e028;
}

// ==== Framework::CFixedLengthAllocatorContainer::ReportS()
// vaddr 0x1e9e0e8 | ghidra 0x1f9e0e8 | size 272 | symbol _ZN9Framework30CFixedLengthAllocatorContainer7ReportSEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework30CFixedLengthAllocatorContainer7ReportSEv(long *param_1)

{
  ulong uVar1;
  undefined8 uVar2;
  ulong uVar3;
  long *plVar4;
  uint uVar5;
  
  if (param_1[2] != 0) {
    uVar3 = 0;
    uVar5 = 0;
    while (uVar3 < (ulong)param_1[1]) {
      if (param_1[2] == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965e66/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TObjectContainer.h"*/,0x44,&UNK_027ee29f/*"m_pElements is null."*/);
      }
      uVar1 = (**(code **)(*param_1 + 0x20))(param_1);
      if (uVar1 <= uVar3) {
        uVar2 = (**(code **)(*param_1 + 0x20))(param_1);
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965e66/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TObjectContainer.h"*/,0x45,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,uVar3,uVar2);
      }
      plVar4 = *(long **)(param_1[2] + uVar3 * 8);
      (**(code **)(*plVar4 + 0x58))(plVar4);
      (**(code **)(*plVar4 + 0x50))(plVar4);
      uVar5 = uVar5 + 1;
code_r0x01f9e124:
      uVar3 = (ulong)uVar5;
      if (param_1[2] == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965e66/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TObjectContainer.h"*/,0x3e,&UNK_027ee29f/*"m_pElements is null."*/);
      }
    }
    return;
  }
  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029663d3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\TFixedLengthAllocator.cpp"*/,0xd2,&UNK_02966463/*"m_Allocators.IsInitialized() is null."*/);
  uVar5 = 0;
  goto code_r0x01f9e124;
}

// ==== Framework::CFixedLengthAllocatorContainer::ReportC()
// vaddr 0x1e9e1f8 | ghidra 0x1f9e1f8 | size 272 | symbol _ZN9Framework30CFixedLengthAllocatorContainer7ReportCEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework30CFixedLengthAllocatorContainer7ReportCEv(long *param_1)

{
  ulong uVar1;
  undefined8 uVar2;
  ulong uVar3;
  long *plVar4;
  uint uVar5;
  
  if (param_1[2] != 0) {
    uVar3 = 0;
    uVar5 = 0;
    while (uVar3 < (ulong)param_1[1]) {
      if (param_1[2] == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965e66/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TObjectContainer.h"*/,0x44,&UNK_027ee29f/*"m_pElements is null."*/);
      }
      uVar1 = (**(code **)(*param_1 + 0x20))(param_1);
      if (uVar1 <= uVar3) {
        uVar2 = (**(code **)(*param_1 + 0x20))(param_1);
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965e66/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TObjectContainer.h"*/,0x45,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,uVar3,uVar2);
      }
      plVar4 = *(long **)(param_1[2] + uVar3 * 8);
      (**(code **)(*plVar4 + 0x58))(plVar4);
      (**(code **)(*plVar4 + 0x50))(plVar4);
      uVar5 = uVar5 + 1;
code_r0x01f9e234:
      uVar3 = (ulong)uVar5;
      if (param_1[2] == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965e66/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TObjectContainer.h"*/,0x3e,&UNK_027ee29f/*"m_pElements is null."*/);
      }
    }
    return;
  }
  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029663d3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\TFixedLengthAllocator.cpp"*/,0xec,&UNK_02966463/*"m_Allocators.IsInitialized() is null."*/);
  uVar5 = 0;
  goto code_r0x01f9e234;
}

// ==== Framework::CFixedLengthAllocatorContainer::ReportL()
// vaddr 0x1e9e308 | ghidra 0x1f9e308 | size 272 | symbol _ZN9Framework30CFixedLengthAllocatorContainer7ReportLEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework30CFixedLengthAllocatorContainer7ReportLEv(long *param_1)

{
  ulong uVar1;
  undefined8 uVar2;
  ulong uVar3;
  long *plVar4;
  uint uVar5;
  
  if (param_1[2] != 0) {
    uVar3 = 0;
    uVar5 = 0;
    while (uVar3 < (ulong)param_1[1]) {
      if (param_1[2] == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965e66/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TObjectContainer.h"*/,0x44,&UNK_027ee29f/*"m_pElements is null."*/);
      }
      uVar1 = (**(code **)(*param_1 + 0x20))(param_1);
      if (uVar1 <= uVar3) {
        uVar2 = (**(code **)(*param_1 + 0x20))(param_1);
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965e66/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TObjectContainer.h"*/,0x45,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,uVar3,uVar2);
      }
      plVar4 = *(long **)(param_1[2] + uVar3 * 8);
      (**(code **)(*plVar4 + 0x58))(plVar4);
      (**(code **)(*plVar4 + 0x50))(plVar4);
      uVar5 = uVar5 + 1;
code_r0x01f9e344:
      uVar3 = (ulong)uVar5;
      if (param_1[2] == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965e66/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TObjectContainer.h"*/,0x3e,&UNK_027ee29f/*"m_pElements is null."*/);
      }
    }
    return;
  }
  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029663d3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\TFixedLengthAllocator.cpp"*/,0x106,&UNK_02966463/*"m_Allocators.IsInitialized() is null."*/);
  uVar5 = 0;
  goto code_r0x01f9e344;
}

// ==== Framework::TObjectContainer<Framework::IFixedLengthAllocator*>::~TObjectContainer()
// vaddr 0x1e9e418 | ghidra 0x1f9e418 | size 48 | symbol _ZN9Framework16TObjectContainerIPNS_21IFixedLengthAllocatorEED0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework16TObjectContainerIPNS_21IFixedLengthAllocatorEED0Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN9Framework16TObjectContainerIPNS_21IFixedLengthAllocatorEEE_02cb8158 +
                   0x10);
  if (param_1[2] != 0) {
    operator delete[](void*)();
  }
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Framework::TObjectContainer<Framework::IFixedLengthAllocator*>::Reset()
// vaddr 0x1e9e448 | ghidra 0x1f9e448 | size 4 | symbol _ZN9Framework16TObjectContainerIPNS_21IFixedLengthAllocatorEE5ResetEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework16TObjectContainerIPNS_21IFixedLengthAllocatorEE5ResetEv(void)

{
  return;
}


// FAILED to create function at 027db6a0 typeinfo name for Framework::TFixedLengthAllocator<16ul>
// FAILED to create function at 027db6d0 typeinfo name for Framework::IFixedLengthAllocator
// FAILED to create function at 027db700 typeinfo name for Framework::TFixedLengthAllocator<32ul>
// FAILED to create function at 027db730 typeinfo name for Framework::TFixedLengthAllocator<64ul>
// FAILED to create function at 027db760 typeinfo name for Framework::TFixedLengthAllocator<128ul>
// FAILED to create function at 027db790 typeinfo name for Framework::TFixedLengthAllocator<256ul>
// FAILED to create function at 027db7c0 typeinfo name for Framework::TFixedLengthAllocator<512ul>
// FAILED to create function at 0280be50 typeinfo name for Framework::TFixedLengthAllocator<192ul>
// FAILED to create function at 02966490 typeinfo name for Framework::TObjectContainer<Framework::IFixedLengthAllocator*>
// FAILED to create function at 02a968e8 Framework::TFixedLengthAllocator<16ul>::vtable
// FAILED to create function at 02a96968 Framework::IFixedLengthAllocator::typeinfo
// FAILED to create function at 02a96980 Framework::TFixedLengthAllocator<16ul>::typeinfo
// FAILED to create function at 02a96998 Framework::TFixedLengthAllocator<32ul>::vtable
// FAILED to create function at 02a96a20 Framework::TFixedLengthAllocator<32ul>::typeinfo
// FAILED to create function at 02a96a38 Framework::TFixedLengthAllocator<64ul>::vtable
// FAILED to create function at 02a96ac0 Framework::TFixedLengthAllocator<64ul>::typeinfo
// FAILED to create function at 02a96ad8 Framework::TFixedLengthAllocator<128ul>::vtable
// FAILED to create function at 02a96b60 Framework::TFixedLengthAllocator<128ul>::typeinfo
// FAILED to create function at 02a96b78 Framework::TFixedLengthAllocator<256ul>::vtable
// FAILED to create function at 02a96c00 Framework::TFixedLengthAllocator<256ul>::typeinfo
// FAILED to create function at 02a96c18 Framework::TFixedLengthAllocator<512ul>::vtable
// FAILED to create function at 02a96ca0 Framework::TFixedLengthAllocator<512ul>::typeinfo
// FAILED to create function at 02abdb68 Framework::TFixedLengthAllocator<192ul>::vtable
// FAILED to create function at 02abdbf0 Framework::TFixedLengthAllocator<192ul>::typeinfo
// FAILED to create function at 02bab3c8 Framework::TObjectContainer<Framework::IFixedLengthAllocator*>::vtable
// FAILED to create function at 02bab410 Framework::TObjectContainer<Framework::IFixedLengthAllocator*>::typeinfo
// FAILED to create function at 02d00528 Framework::CAssignedMemoryManagerForSTLAllocator::m_pMemoryManager
// FAILED to create function at 02d00530 Framework::CAssignedMemoryManagerForSTLAllocator::m_pFixedLengthAllocatorContainer
// FAILED to create function at 02d00538 Framework::CAssignedMemoryManagerForSTLAllocator::m_IsEnableReportByEachAccess
