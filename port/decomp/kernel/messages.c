// port/decomp/kernel/messages.c: Ghidra decompiles for the kernel subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-04 06:17 UTC: tools/decomp.sh '--into' 'kernel/messages' 'Framework::CMessageManager::' 'Framework::ResponderChain::' 'Aska::Global::DeleteEndNotify' 'Aska::MessageDispatcher::'

// ==== void Framework::CMessageManager::SendMessage<CFieldMessage_Behavior_CancelAction>(CFieldMessage_Behavior_CancelAction const&)
// vaddr 0x119d8bc | ghidra 0x129d8bc | size 340 | symbol _ZN9Framework15CMessageManager11SendMessageI35CFieldMessage_Behavior_CancelActionEEvRKT_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework15CMessageManager11SendMessageI35CFieldMessage_Behavior_CancelActionEEvRKT_
               (long param_1,long param_2)

{
  undefined8 *puVar1;
  long *plVar2;
  ulong uVar3;
  long lVar4;
  long *plStack_28;
  
  if (*(int *)(param_2 + 0x18) == 0) {
    if (((*(long *)(param_1 + 0x18) != 0) &&
        (plVar2 = (long *)Framework::CFixedLengthAllocatorContainer::pAllocate(unsigned long, char const*, unsigned int)(*(long *)(param_1 + 0x18),0x20,0,0), plVar2 != (long *)0x0
        )) || (plVar2 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x20,PTR__ZSt7nothrow_02cb9a80),
              plVar2 != (long *)0x0)) {
      *plVar2 = (long)(PTR__ZTVN9Framework12CMessageBaseE_02cbb910 + 0x10);
      *(undefined4 *)(plVar2 + 3) = *(undefined4 *)(param_2 + 0x18);
      lVar4 = *(long *)(param_2 + 8);
      plVar2[2] = *(long *)(param_2 + 0x10);
      plVar2[1] = lVar4;
      *plVar2 = (long)(PTR__ZTV35CFieldMessage_Behavior_CancelAction_02cc18b8 + 0x10);
      *(undefined4 *)((long)plVar2 + 0x1c) = *(undefined4 *)(param_2 + 0x1c);
    }
    lVar4 = *(long *)(param_1 + 0x10);
    if (lVar4 != 0) {
      uVar3 = Framework::CMutex::IsInitialized() const(lVar4);
      if ((uVar3 & 1) == 0) {
        Framework::CMutex::Initialize()(lVar4);
      }
      Framework::CMutex::Lock()(lVar4);
    }
    puVar1 = *(undefined8 **)(param_1 + 0x78);
    plStack_28 = plVar2;
    if (puVar1 < *(undefined8 **)(param_1 + 0x80)) {
      if (puVar1 == (undefined8 *)0x0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
      }
      *puVar1 = plVar2;
      *(long *)(param_1 + 0x78) = *(long *)(param_1 + 0x78) + 8;
    }
    else {
      void std::__ndk1::vector<Framework::CMessageBase*, Framework::CSTLAllocator<Framework::CMessageBase*, Framework::CSTLVectorAllocatorInf> >::__push_back_slow_path<Framework::CMessageBase*>(Framework::CMessageBase*&&)(param_1 + 0x70,&plStack_28);
    }
    if (lVar4 != 0) {
      Framework::CMutex::Unlock()(lVar4);
    }
    return;
  }
  if (*(int *)(param_2 + 0x18) != 1) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027e64e8/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/MessageManager.h"*/,0x9e,&UNK_027e6540/*"Illegal attribute.(%d)"*/);
  }
  (*(code *)PTR__ZN9Framework15CMessageManager17DirectSendMessageERKNS_12CMessageBaseE_02c8fff0)
            (param_1,param_2);
  return;
}

// ==== void Framework::CMessageManager::SendMessage<CFieldMessage_CreateBehavior_MoveTo>(CFieldMessage_CreateBehavior_MoveTo const&)
// vaddr 0x119db30 | ghidra 0x129db30 | size 372 | symbol _ZN9Framework15CMessageManager11SendMessageI35CFieldMessage_CreateBehavior_MoveToEEvRKT_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework15CMessageManager11SendMessageI35CFieldMessage_CreateBehavior_MoveToEEvRKT_
               (long param_1,long param_2)

{
  undefined8 *puVar1;
  long *plVar2;
  ulong uVar3;
  long lVar4;
  long *plStack_28;
  
  if (*(int *)(param_2 + 0x18) == 0) {
    if (((*(long *)(param_1 + 0x18) != 0) &&
        (plVar2 = (long *)Framework::CFixedLengthAllocatorContainer::pAllocate(unsigned long, char const*, unsigned int)(*(long *)(param_1 + 0x18),0x40,0,0), plVar2 != (long *)0x0
        )) || (plVar2 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x40,PTR__ZSt7nothrow_02cb9a80),
              plVar2 != (long *)0x0)) {
      *plVar2 = (long)(PTR__ZTVN9Framework12CMessageBaseE_02cbb910 + 0x10);
      *(undefined4 *)(plVar2 + 3) = *(undefined4 *)(param_2 + 0x18);
      lVar4 = *(long *)(param_2 + 8);
      plVar2[2] = *(long *)(param_2 + 0x10);
      plVar2[1] = lVar4;
      *plVar2 = (long)(PTR__ZTV35CFieldMessage_CreateBehavior_MoveTo_02cbff30 + 0x10);
      *(undefined4 *)(plVar2 + 4) = *(undefined4 *)(param_2 + 0x20);
      *(undefined4 *)((long)plVar2 + 0x24) = *(undefined4 *)(param_2 + 0x24);
      *(undefined4 *)(plVar2 + 5) = *(undefined4 *)(param_2 + 0x28);
      *(undefined4 *)((long)plVar2 + 0x2c) = *(undefined4 *)(param_2 + 0x2c);
      plVar2[6] = *(long *)(param_2 + 0x30);
    }
    lVar4 = *(long *)(param_1 + 0x10);
    if (lVar4 != 0) {
      uVar3 = Framework::CMutex::IsInitialized() const(lVar4);
      if ((uVar3 & 1) == 0) {
        Framework::CMutex::Initialize()(lVar4);
      }
      Framework::CMutex::Lock()(lVar4);
    }
    puVar1 = *(undefined8 **)(param_1 + 0x78);
    plStack_28 = plVar2;
    if (puVar1 < *(undefined8 **)(param_1 + 0x80)) {
      if (puVar1 == (undefined8 *)0x0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
      }
      *puVar1 = plVar2;
      *(long *)(param_1 + 0x78) = *(long *)(param_1 + 0x78) + 8;
    }
    else {
      void std::__ndk1::vector<Framework::CMessageBase*, Framework::CSTLAllocator<Framework::CMessageBase*, Framework::CSTLVectorAllocatorInf> >::__push_back_slow_path<Framework::CMessageBase*>(Framework::CMessageBase*&&)(param_1 + 0x70,&plStack_28);
    }
    if (lVar4 != 0) {
      Framework::CMutex::Unlock()(lVar4);
    }
    return;
  }
  if (*(int *)(param_2 + 0x18) != 1) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027e64e8/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/MessageManager.h"*/,0x9e,&UNK_027e6540/*"Illegal attribute.(%d)"*/);
  }
  (*(code *)PTR__ZN9Framework15CMessageManager17DirectSendMessageERKNS_12CMessageBaseE_02c8fff0)
            (param_1,param_2);
  return;
}

// ==== void Framework::CMessageManager::SendMessage<CFieldMessage_CreateBehavior_Move>(CFieldMessage_CreateBehavior_Move const&)
// vaddr 0x119dca4 | ghidra 0x129dca4 | size 340 | symbol _ZN9Framework15CMessageManager11SendMessageI33CFieldMessage_CreateBehavior_MoveEEvRKT_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework15CMessageManager11SendMessageI33CFieldMessage_CreateBehavior_MoveEEvRKT_
               (long param_1,long param_2)

{
  undefined8 *puVar1;
  long *plVar2;
  ulong uVar3;
  long lVar4;
  long *plStack_28;
  
  if (*(int *)(param_2 + 0x18) == 0) {
    if (((*(long *)(param_1 + 0x18) != 0) &&
        (plVar2 = (long *)Framework::CFixedLengthAllocatorContainer::pAllocate(unsigned long, char const*, unsigned int)(*(long *)(param_1 + 0x18),0x20,0,0), plVar2 != (long *)0x0
        )) || (plVar2 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x20,PTR__ZSt7nothrow_02cb9a80),
              plVar2 != (long *)0x0)) {
      *plVar2 = (long)(PTR__ZTVN9Framework12CMessageBaseE_02cbb910 + 0x10);
      *(undefined4 *)(plVar2 + 3) = *(undefined4 *)(param_2 + 0x18);
      lVar4 = *(long *)(param_2 + 8);
      plVar2[2] = *(long *)(param_2 + 0x10);
      plVar2[1] = lVar4;
      *plVar2 = (long)(PTR__ZTV33CFieldMessage_CreateBehavior_Move_02cb9538 + 0x10);
      *(undefined4 *)((long)plVar2 + 0x1c) = *(undefined4 *)(param_2 + 0x1c);
    }
    lVar4 = *(long *)(param_1 + 0x10);
    if (lVar4 != 0) {
      uVar3 = Framework::CMutex::IsInitialized() const(lVar4);
      if ((uVar3 & 1) == 0) {
        Framework::CMutex::Initialize()(lVar4);
      }
      Framework::CMutex::Lock()(lVar4);
    }
    puVar1 = *(undefined8 **)(param_1 + 0x78);
    plStack_28 = plVar2;
    if (puVar1 < *(undefined8 **)(param_1 + 0x80)) {
      if (puVar1 == (undefined8 *)0x0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
      }
      *puVar1 = plVar2;
      *(long *)(param_1 + 0x78) = *(long *)(param_1 + 0x78) + 8;
    }
    else {
      void std::__ndk1::vector<Framework::CMessageBase*, Framework::CSTLAllocator<Framework::CMessageBase*, Framework::CSTLVectorAllocatorInf> >::__push_back_slow_path<Framework::CMessageBase*>(Framework::CMessageBase*&&)(param_1 + 0x70,&plStack_28);
    }
    if (lVar4 != 0) {
      Framework::CMutex::Unlock()(lVar4);
    }
    return;
  }
  if (*(int *)(param_2 + 0x18) != 1) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027e64e8/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/MessageManager.h"*/,0x9e,&UNK_027e6540/*"Illegal attribute.(%d)"*/);
  }
  (*(code *)PTR__ZN9Framework15CMessageManager17DirectSendMessageERKNS_12CMessageBaseE_02c8fff0)
            (param_1,param_2);
  return;
}

// ==== void Framework::CMessageManager::SendMessage<CFieldMessage_CreateBehavior_NormalAttack>(CFieldMessage_CreateBehavior_NormalAttack const&)
// vaddr 0x119ddf8 | ghidra 0x129ddf8 | size 352 | symbol _ZN9Framework15CMessageManager11SendMessageI41CFieldMessage_CreateBehavior_NormalAttackEEvRKT_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework15CMessageManager11SendMessageI41CFieldMessage_CreateBehavior_NormalAttackEEvRKT_
               (long param_1,long param_2)

{
  undefined8 *puVar1;
  undefined *puVar2;
  long *plVar3;
  ulong uVar4;
  long lVar5;
  long *plStack_28;
  
  if (*(int *)(param_2 + 0x18) != 0) {
    if (*(int *)(param_2 + 0x18) != 1) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027e64e8/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/MessageManager.h"*/,0x9e,&UNK_027e6540/*"Illegal attribute.(%d)"*/);
    }
    (*(code *)PTR__ZN9Framework15CMessageManager17DirectSendMessageERKNS_12CMessageBaseE_02c8fff0)
              (param_1,param_2);
    return;
  }
  if ((*(long *)(param_1 + 0x18) == 0) ||
     (plVar3 = (long *)Framework::CFixedLengthAllocatorContainer::pAllocate(unsigned long, char const*, unsigned int)(*(long *)(param_1 + 0x18),0x28,0,0), plVar3 == (long *)0x0))
  {
    plVar3 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x28,PTR__ZSt7nothrow_02cb9a80);
    if (plVar3 == (long *)0x0) goto code_r0x0129dec8;
  }
  else {
    *plVar3 = (long)(PTR__ZTVN9Framework12CMessageBaseE_02cbb910 + 0x10);
  }
  *(undefined4 *)(plVar3 + 3) = *(undefined4 *)(param_2 + 0x18);
  puVar2 = PTR__ZTV41CFieldMessage_CreateBehavior_NormalAttack_02cbb978;
  lVar5 = *(long *)(param_2 + 8);
  plVar3[2] = *(long *)(param_2 + 0x10);
  plVar3[1] = lVar5;
  *plVar3 = (long)(puVar2 + 0x10);
  *(undefined1 *)((long)plVar3 + 0x24) = *(undefined1 *)(param_2 + 0x24);
  *(undefined8 *)((long)plVar3 + 0x1c) = *(undefined8 *)(param_2 + 0x1c);
code_r0x0129dec8:
  lVar5 = *(long *)(param_1 + 0x10);
  if (lVar5 != 0) {
    uVar4 = Framework::CMutex::IsInitialized() const(lVar5);
    if ((uVar4 & 1) == 0) {
      Framework::CMutex::Initialize()(lVar5);
    }
    Framework::CMutex::Lock()(lVar5);
  }
  puVar1 = *(undefined8 **)(param_1 + 0x78);
  plStack_28 = plVar3;
  if (puVar1 < *(undefined8 **)(param_1 + 0x80)) {
    if (puVar1 == (undefined8 *)0x0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
    }
    *puVar1 = plVar3;
    *(long *)(param_1 + 0x78) = *(long *)(param_1 + 0x78) + 8;
  }
  else {
    void std::__ndk1::vector<Framework::CMessageBase*, Framework::CSTLAllocator<Framework::CMessageBase*, Framework::CSTLVectorAllocatorInf> >::__push_back_slow_path<Framework::CMessageBase*>(Framework::CMessageBase*&&)(param_1 + 0x70,&plStack_28);
  }
  if (lVar5 != 0) {
    Framework::CMutex::Unlock()(lVar5);
  }
  return;
}

// ==== void Framework::CMessageManager::SendMessage<CFieldMessage_CreateBehavior_Magic>(CFieldMessage_CreateBehavior_Magic const&)
// vaddr 0x119df58 | ghidra 0x129df58 | size 352 | symbol _ZN9Framework15CMessageManager11SendMessageI34CFieldMessage_CreateBehavior_MagicEEvRKT_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework15CMessageManager11SendMessageI34CFieldMessage_CreateBehavior_MagicEEvRKT_
               (long param_1,long param_2)

{
  undefined8 *puVar1;
  undefined *puVar2;
  long *plVar3;
  ulong uVar4;
  long lVar5;
  long lVar6;
  long *plStack_28;
  
  if (*(int *)(param_2 + 0x18) != 0) {
    if (*(int *)(param_2 + 0x18) != 1) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027e64e8/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/MessageManager.h"*/,0x9e,&UNK_027e6540/*"Illegal attribute.(%d)"*/);
    }
    (*(code *)PTR__ZN9Framework15CMessageManager17DirectSendMessageERKNS_12CMessageBaseE_02c8fff0)
              (param_1,param_2);
    return;
  }
  if ((*(long *)(param_1 + 0x18) == 0) ||
     (plVar3 = (long *)Framework::CFixedLengthAllocatorContainer::pAllocate(unsigned long, char const*, unsigned int)(*(long *)(param_1 + 0x18),0x80,0,0), plVar3 == (long *)0x0))
  {
    plVar3 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x80,PTR__ZSt7nothrow_02cb9a80);
    if (plVar3 == (long *)0x0) goto code_r0x0129e028;
  }
  else {
    *plVar3 = (long)(PTR__ZTVN9Framework12CMessageBaseE_02cbb910 + 0x10);
  }
  puVar2 = PTR__ZTV34CFieldMessage_CreateBehavior_Magic_02cc45e8;
  *(undefined4 *)(plVar3 + 3) = *(undefined4 *)(param_2 + 0x18);
  lVar6 = *(long *)(param_2 + 0x10);
  lVar5 = *(long *)(param_2 + 8);
  *plVar3 = (long)(puVar2 + 0x10);
  plVar3[2] = lVar6;
  plVar3[1] = lVar5;
  memcpy((long)plVar3 + 0x1c,param_2 + 0x1c,0x60);
code_r0x0129e028:
  lVar5 = *(long *)(param_1 + 0x10);
  if (lVar5 != 0) {
    uVar4 = Framework::CMutex::IsInitialized() const(lVar5);
    if ((uVar4 & 1) == 0) {
      Framework::CMutex::Initialize()(lVar5);
    }
    Framework::CMutex::Lock()(lVar5);
  }
  puVar1 = *(undefined8 **)(param_1 + 0x78);
  plStack_28 = plVar3;
  if (puVar1 < *(undefined8 **)(param_1 + 0x80)) {
    if (puVar1 == (undefined8 *)0x0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
    }
    *puVar1 = plVar3;
    *(long *)(param_1 + 0x78) = *(long *)(param_1 + 0x78) + 8;
  }
  else {
    void std::__ndk1::vector<Framework::CMessageBase*, Framework::CSTLAllocator<Framework::CMessageBase*, Framework::CSTLVectorAllocatorInf> >::__push_back_slow_path<Framework::CMessageBase*>(Framework::CMessageBase*&&)(param_1 + 0x70,&plStack_28);
  }
  if (lVar5 != 0) {
    Framework::CMutex::Unlock()(lVar5);
  }
  return;
}

// ==== void Framework::CMessageManager::SendMessage<CFieldMessage_CreateBehavior_ExAttack>(CFieldMessage_CreateBehavior_ExAttack const&)
// vaddr 0x119e0b8 | ghidra 0x129e0b8 | size 352 | symbol _ZN9Framework15CMessageManager11SendMessageI37CFieldMessage_CreateBehavior_ExAttackEEvRKT_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework15CMessageManager11SendMessageI37CFieldMessage_CreateBehavior_ExAttackEEvRKT_
               (long param_1,long param_2)

{
  undefined8 *puVar1;
  undefined *puVar2;
  long *plVar3;
  ulong uVar4;
  long lVar5;
  long lVar6;
  long *plStack_28;
  
  if (*(int *)(param_2 + 0x18) != 0) {
    if (*(int *)(param_2 + 0x18) != 1) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027e64e8/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/MessageManager.h"*/,0x9e,&UNK_027e6540/*"Illegal attribute.(%d)"*/);
    }
    (*(code *)PTR__ZN9Framework15CMessageManager17DirectSendMessageERKNS_12CMessageBaseE_02c8fff0)
              (param_1,param_2);
    return;
  }
  if ((*(long *)(param_1 + 0x18) == 0) ||
     (plVar3 = (long *)Framework::CFixedLengthAllocatorContainer::pAllocate(unsigned long, char const*, unsigned int)(*(long *)(param_1 + 0x18),0x78,0,0), plVar3 == (long *)0x0))
  {
    plVar3 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x78,PTR__ZSt7nothrow_02cb9a80);
    if (plVar3 == (long *)0x0) goto code_r0x0129e188;
  }
  else {
    *plVar3 = (long)(PTR__ZTVN9Framework12CMessageBaseE_02cbb910 + 0x10);
  }
  puVar2 = PTR__ZTV37CFieldMessage_CreateBehavior_ExAttack_02cb8070;
  *(undefined4 *)(plVar3 + 3) = *(undefined4 *)(param_2 + 0x18);
  lVar6 = *(long *)(param_2 + 0x10);
  lVar5 = *(long *)(param_2 + 8);
  *plVar3 = (long)(puVar2 + 0x10);
  plVar3[2] = lVar6;
  plVar3[1] = lVar5;
  memcpy((long)plVar3 + 0x1c,param_2 + 0x1c,0x58);
code_r0x0129e188:
  lVar5 = *(long *)(param_1 + 0x10);
  if (lVar5 != 0) {
    uVar4 = Framework::CMutex::IsInitialized() const(lVar5);
    if ((uVar4 & 1) == 0) {
      Framework::CMutex::Initialize()(lVar5);
    }
    Framework::CMutex::Lock()(lVar5);
  }
  puVar1 = *(undefined8 **)(param_1 + 0x78);
  plStack_28 = plVar3;
  if (puVar1 < *(undefined8 **)(param_1 + 0x80)) {
    if (puVar1 == (undefined8 *)0x0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
    }
    *puVar1 = plVar3;
    *(long *)(param_1 + 0x78) = *(long *)(param_1 + 0x78) + 8;
  }
  else {
    void std::__ndk1::vector<Framework::CMessageBase*, Framework::CSTLAllocator<Framework::CMessageBase*, Framework::CSTLVectorAllocatorInf> >::__push_back_slow_path<Framework::CMessageBase*>(Framework::CMessageBase*&&)(param_1 + 0x70,&plStack_28);
  }
  if (lVar5 != 0) {
    Framework::CMutex::Unlock()(lVar5);
  }
  return;
}

// ==== void Framework::CMessageManager::SendMessage<CFieldMessage_ReceiveDamage>(CFieldMessage_ReceiveDamage const&)
// vaddr 0x11a98c4 | ghidra 0x12a98c4 | size 244 | symbol _ZN9Framework15CMessageManager11SendMessageI27CFieldMessage_ReceiveDamageEEvRKT_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework15CMessageManager11SendMessageI27CFieldMessage_ReceiveDamageEEvRKT_
               (long param_1,long param_2)

{
  undefined8 *puVar1;
  undefined8 uVar2;
  ulong uVar3;
  long lVar4;
  undefined8 uStack_28;
  
  if (*(int *)(param_2 + 0x18) == 0) {
    uVar2 = CFieldMessage_ReceiveDamage* Framework::CMessageManager::CopyMessage<CFieldMessage_ReceiveDamage>(CFieldMessage_ReceiveDamage const&) const(param_1,param_2);
    lVar4 = *(long *)(param_1 + 0x10);
    if (lVar4 != 0) {
      uVar3 = Framework::CMutex::IsInitialized() const(lVar4);
      if ((uVar3 & 1) == 0) {
        Framework::CMutex::Initialize()(lVar4);
      }
      Framework::CMutex::Lock()(lVar4);
    }
    puVar1 = *(undefined8 **)(param_1 + 0x78);
    uStack_28 = uVar2;
    if (puVar1 < *(undefined8 **)(param_1 + 0x80)) {
      if (puVar1 == (undefined8 *)0x0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
      }
      *puVar1 = uVar2;
      *(long *)(param_1 + 0x78) = *(long *)(param_1 + 0x78) + 8;
    }
    else {
      void std::__ndk1::vector<Framework::CMessageBase*, Framework::CSTLAllocator<Framework::CMessageBase*, Framework::CSTLVectorAllocatorInf> >::__push_back_slow_path<Framework::CMessageBase*>(Framework::CMessageBase*&&)(param_1 + 0x70,&uStack_28);
    }
    if (lVar4 != 0) {
      Framework::CMutex::Unlock()(lVar4);
    }
    return;
  }
  if (*(int *)(param_2 + 0x18) != 1) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027e64e8/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/MessageManager.h"*/,0x9e,&UNK_027e6540/*"Illegal attribute.(%d)"*/);
  }
  (*(code *)PTR__ZN9Framework15CMessageManager17DirectSendMessageERKNS_12CMessageBaseE_02c8fff0)
            (param_1,param_2);
  return;
}

// ==== CFieldMessage_ReceiveDamage* Framework::CMessageManager::CopyMessage<CFieldMessage_ReceiveDamage>(CFieldMessage_ReceiveDamage const&) const
// vaddr 0x11a99b8 | ghidra 0x12a99b8 | size 292 | symbol _ZNK9Framework15CMessageManager11CopyMessageI27CFieldMessage_ReceiveDamageEEPT_RKS3_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK9Framework15CMessageManager11CopyMessageI27CFieldMessage_ReceiveDamageEEPT_RKS3_
               (long param_1,long param_2)

{
  undefined *puVar1;
  long *plVar2;
  long lVar3;
  
  if ((*(long *)(param_1 + 0x18) == 0) ||
     (plVar2 = (long *)Framework::CFixedLengthAllocatorContainer::pAllocate(unsigned long, char const*, unsigned int)(*(long *)(param_1 + 0x18),0xa0,0,0), plVar2 == (long *)0x0))
  {
    plVar2 = (long *)operator new(unsigned long, std::nothrow_t const&)(0xa0,PTR__ZSt7nothrow_02cb9a80);
    if (plVar2 == (long *)0x0) {
      return;
    }
    *(undefined4 *)(plVar2 + 3) = *(undefined4 *)(param_2 + 0x18);
    puVar1 = PTR__ZTV27CFieldMessage_ReceiveDamage_02cc2d20;
    lVar3 = *(long *)(param_2 + 8);
    plVar2[2] = *(long *)(param_2 + 0x10);
    plVar2[1] = lVar3;
    *plVar2 = (long)(puVar1 + 0x10);
    *(undefined4 *)(plVar2 + 6) = *(undefined4 *)(param_2 + 0x30);
    lVar3 = *(long *)(param_2 + 0x20);
    plVar2[5] = *(long *)(param_2 + 0x28);
    plVar2[4] = lVar3;
    lVar3 = *(long *)(param_2 + 0x40);
    plVar2[9] = *(long *)(param_2 + 0x48);
    plVar2[8] = lVar3;
    lVar3 = *(long *)(param_2 + 0x50);
    plVar2[0xb] = *(long *)(param_2 + 0x58);
    plVar2[10] = lVar3;
  }
  else {
    *plVar2 = (long)(PTR__ZTVN9Framework12CMessageBaseE_02cbb910 + 0x10);
    *(undefined4 *)(plVar2 + 3) = *(undefined4 *)(param_2 + 0x18);
    puVar1 = PTR__ZTV27CFieldMessage_ReceiveDamage_02cc2d20;
    lVar3 = *(long *)(param_2 + 8);
    plVar2[2] = *(long *)(param_2 + 0x10);
    plVar2[1] = lVar3;
    *plVar2 = (long)(puVar1 + 0x10);
    *(undefined4 *)(plVar2 + 6) = *(undefined4 *)(param_2 + 0x30);
    lVar3 = *(long *)(param_2 + 0x20);
    plVar2[5] = *(long *)(param_2 + 0x28);
    plVar2[4] = lVar3;
    *(undefined4 *)(plVar2 + 8) = *(undefined4 *)(param_2 + 0x40);
    *(undefined4 *)((long)plVar2 + 0x44) = *(undefined4 *)(param_2 + 0x44);
    *(undefined4 *)(plVar2 + 9) = *(undefined4 *)(param_2 + 0x48);
    *(undefined4 *)((long)plVar2 + 0x4c) = *(undefined4 *)(param_2 + 0x4c);
    *(undefined4 *)(plVar2 + 10) = *(undefined4 *)(param_2 + 0x50);
    *(undefined4 *)((long)plVar2 + 0x54) = *(undefined4 *)(param_2 + 0x54);
    *(undefined4 *)(plVar2 + 0xb) = *(undefined4 *)(param_2 + 0x58);
    *(undefined4 *)((long)plVar2 + 0x5c) = *(undefined4 *)(param_2 + 0x5c);
  }
  *(undefined2 *)(plVar2 + 0xe) = *(undefined2 *)(param_2 + 0x70);
  lVar3 = *(long *)(param_2 + 0x60);
  plVar2[0xd] = *(long *)(param_2 + 0x68);
  plVar2[0xc] = lVar3;
  *(undefined2 *)(plVar2 + 0x10) = *(undefined2 *)(param_2 + 0x80);
  plVar2[0x12] = *(long *)(param_2 + 0x90);
  return;
}

// ==== void Framework::CMessageManager::SendMessage<CFieldMessage_StartFactor>(CFieldMessage_StartFactor const&)
// vaddr 0x1217660 | ghidra 0x1317660 | size 352 | symbol _ZN9Framework15CMessageManager11SendMessageI25CFieldMessage_StartFactorEEvRKT_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework15CMessageManager11SendMessageI25CFieldMessage_StartFactorEEvRKT_
               (long param_1,long param_2)

{
  undefined8 *puVar1;
  undefined *puVar2;
  long *plVar3;
  ulong uVar4;
  long lVar5;
  long *plStack_28;
  
  if (*(int *)(param_2 + 0x18) != 0) {
    if (*(int *)(param_2 + 0x18) != 1) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027e64e8/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/MessageManager.h"*/,0x9e,&UNK_027e6540/*"Illegal attribute.(%d)"*/);
    }
    (*(code *)PTR__ZN9Framework15CMessageManager17DirectSendMessageERKNS_12CMessageBaseE_02c8fff0)
              (param_1,param_2);
    return;
  }
  if ((*(long *)(param_1 + 0x18) == 0) ||
     (plVar3 = (long *)Framework::CFixedLengthAllocatorContainer::pAllocate(unsigned long, char const*, unsigned int)(*(long *)(param_1 + 0x18),0x30,0,0), plVar3 == (long *)0x0))
  {
    plVar3 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x30,PTR__ZSt7nothrow_02cb9a80);
    if (plVar3 == (long *)0x0) goto code_r0x01317730;
  }
  else {
    *plVar3 = (long)(PTR__ZTVN9Framework12CMessageBaseE_02cbb910 + 0x10);
  }
  *(undefined4 *)(plVar3 + 3) = *(undefined4 *)(param_2 + 0x18);
  puVar2 = PTR__ZTV25CFieldMessage_StartFactor_02cb9b18;
  lVar5 = *(long *)(param_2 + 8);
  plVar3[2] = *(long *)(param_2 + 0x10);
  plVar3[1] = lVar5;
  *plVar3 = (long)(puVar2 + 0x10);
  *(undefined8 *)((long)plVar3 + 0x21) = *(undefined8 *)(param_2 + 0x21);
  *(undefined8 *)((long)plVar3 + 0x1c) = *(undefined8 *)(param_2 + 0x1c);
code_r0x01317730:
  lVar5 = *(long *)(param_1 + 0x10);
  if (lVar5 != 0) {
    uVar4 = Framework::CMutex::IsInitialized() const(lVar5);
    if ((uVar4 & 1) == 0) {
      Framework::CMutex::Initialize()(lVar5);
    }
    Framework::CMutex::Lock()(lVar5);
  }
  puVar1 = *(undefined8 **)(param_1 + 0x78);
  plStack_28 = plVar3;
  if (puVar1 < *(undefined8 **)(param_1 + 0x80)) {
    if (puVar1 == (undefined8 *)0x0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
    }
    *puVar1 = plVar3;
    *(long *)(param_1 + 0x78) = *(long *)(param_1 + 0x78) + 8;
  }
  else {
    void std::__ndk1::vector<Framework::CMessageBase*, Framework::CSTLAllocator<Framework::CMessageBase*, Framework::CSTLVectorAllocatorInf> >::__push_back_slow_path<Framework::CMessageBase*>(Framework::CMessageBase*&&)(param_1 + 0x70,&plStack_28);
  }
  if (lVar5 != 0) {
    Framework::CMutex::Unlock()(lVar5);
  }
  return;
}

// ==== void Framework::CMessageManager::SendMessage<CFieldMessage_CreateBehavior_Revival>(CFieldMessage_CreateBehavior_Revival const&)
// vaddr 0x122e180 | ghidra 0x132e180 | size 340 | symbol _ZN9Framework15CMessageManager11SendMessageI36CFieldMessage_CreateBehavior_RevivalEEvRKT_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework15CMessageManager11SendMessageI36CFieldMessage_CreateBehavior_RevivalEEvRKT_
               (long param_1,long param_2)

{
  undefined8 *puVar1;
  long *plVar2;
  ulong uVar3;
  long lVar4;
  long *plStack_28;
  
  if (*(int *)(param_2 + 0x18) == 0) {
    if (((*(long *)(param_1 + 0x18) != 0) &&
        (plVar2 = (long *)Framework::CFixedLengthAllocatorContainer::pAllocate(unsigned long, char const*, unsigned int)(*(long *)(param_1 + 0x18),0x20,0,0), plVar2 != (long *)0x0
        )) || (plVar2 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x20,PTR__ZSt7nothrow_02cb9a80),
              plVar2 != (long *)0x0)) {
      *plVar2 = (long)(PTR__ZTVN9Framework12CMessageBaseE_02cbb910 + 0x10);
      *(undefined4 *)(plVar2 + 3) = *(undefined4 *)(param_2 + 0x18);
      lVar4 = *(long *)(param_2 + 8);
      plVar2[2] = *(long *)(param_2 + 0x10);
      plVar2[1] = lVar4;
      *plVar2 = (long)(PTR__ZTV36CFieldMessage_CreateBehavior_Revival_02cbf4e0 + 0x10);
      *(undefined1 *)((long)plVar2 + 0x1c) = *(undefined1 *)(param_2 + 0x1c);
    }
    lVar4 = *(long *)(param_1 + 0x10);
    if (lVar4 != 0) {
      uVar3 = Framework::CMutex::IsInitialized() const(lVar4);
      if ((uVar3 & 1) == 0) {
        Framework::CMutex::Initialize()(lVar4);
      }
      Framework::CMutex::Lock()(lVar4);
    }
    puVar1 = *(undefined8 **)(param_1 + 0x78);
    plStack_28 = plVar2;
    if (puVar1 < *(undefined8 **)(param_1 + 0x80)) {
      if (puVar1 == (undefined8 *)0x0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
      }
      *puVar1 = plVar2;
      *(long *)(param_1 + 0x78) = *(long *)(param_1 + 0x78) + 8;
    }
    else {
      void std::__ndk1::vector<Framework::CMessageBase*, Framework::CSTLAllocator<Framework::CMessageBase*, Framework::CSTLVectorAllocatorInf> >::__push_back_slow_path<Framework::CMessageBase*>(Framework::CMessageBase*&&)(param_1 + 0x70,&plStack_28);
    }
    if (lVar4 != 0) {
      Framework::CMutex::Unlock()(lVar4);
    }
    return;
  }
  if (*(int *)(param_2 + 0x18) != 1) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027e64e8/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/MessageManager.h"*/,0x9e,&UNK_027e6540/*"Illegal attribute.(%d)"*/);
  }
  (*(code *)PTR__ZN9Framework15CMessageManager17DirectSendMessageERKNS_12CMessageBaseE_02c8fff0)
            (param_1,param_2);
  return;
}

// ==== void Framework::CMessageManager::SendMessage<CFieldMessage_ReceiveRecover>(CFieldMessage_ReceiveRecover const&)
// vaddr 0x122e2d4 | ghidra 0x132e2d4 | size 244 | symbol _ZN9Framework15CMessageManager11SendMessageI28CFieldMessage_ReceiveRecoverEEvRKT_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework15CMessageManager11SendMessageI28CFieldMessage_ReceiveRecoverEEvRKT_
               (long param_1,long param_2)

{
  undefined8 *puVar1;
  undefined8 uVar2;
  ulong uVar3;
  long lVar4;
  undefined8 uStack_28;
  
  if (*(int *)(param_2 + 0x18) == 0) {
    uVar2 = CFieldMessage_ReceiveRecover* Framework::CMessageManager::CopyMessage<CFieldMessage_ReceiveRecover>(CFieldMessage_ReceiveRecover const&) const(param_1,param_2);
    lVar4 = *(long *)(param_1 + 0x10);
    if (lVar4 != 0) {
      uVar3 = Framework::CMutex::IsInitialized() const(lVar4);
      if ((uVar3 & 1) == 0) {
        Framework::CMutex::Initialize()(lVar4);
      }
      Framework::CMutex::Lock()(lVar4);
    }
    puVar1 = *(undefined8 **)(param_1 + 0x78);
    uStack_28 = uVar2;
    if (puVar1 < *(undefined8 **)(param_1 + 0x80)) {
      if (puVar1 == (undefined8 *)0x0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
      }
      *puVar1 = uVar2;
      *(long *)(param_1 + 0x78) = *(long *)(param_1 + 0x78) + 8;
    }
    else {
      void std::__ndk1::vector<Framework::CMessageBase*, Framework::CSTLAllocator<Framework::CMessageBase*, Framework::CSTLVectorAllocatorInf> >::__push_back_slow_path<Framework::CMessageBase*>(Framework::CMessageBase*&&)(param_1 + 0x70,&uStack_28);
    }
    if (lVar4 != 0) {
      Framework::CMutex::Unlock()(lVar4);
    }
    return;
  }
  if (*(int *)(param_2 + 0x18) != 1) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027e64e8/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/MessageManager.h"*/,0x9e,&UNK_027e6540/*"Illegal attribute.(%d)"*/);
  }
  (*(code *)PTR__ZN9Framework15CMessageManager17DirectSendMessageERKNS_12CMessageBaseE_02c8fff0)
            (param_1,param_2);
  return;
}

// ==== CFieldMessage_ReceiveRecover* Framework::CMessageManager::CopyMessage<CFieldMessage_ReceiveRecover>(CFieldMessage_ReceiveRecover const&) const
// vaddr 0x122e3c8 | ghidra 0x132e3c8 | size 292 | symbol _ZNK9Framework15CMessageManager11CopyMessageI28CFieldMessage_ReceiveRecoverEEPT_RKS3_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK9Framework15CMessageManager11CopyMessageI28CFieldMessage_ReceiveRecoverEEPT_RKS3_
               (long param_1,long param_2)

{
  undefined *puVar1;
  long *plVar2;
  long lVar3;
  
  if ((*(long *)(param_1 + 0x18) == 0) ||
     (plVar2 = (long *)Framework::CFixedLengthAllocatorContainer::pAllocate(unsigned long, char const*, unsigned int)(*(long *)(param_1 + 0x18),0xa0,0,0), plVar2 == (long *)0x0))
  {
    plVar2 = (long *)operator new(unsigned long, std::nothrow_t const&)(0xa0,PTR__ZSt7nothrow_02cb9a80);
    if (plVar2 == (long *)0x0) {
      return;
    }
    *(undefined4 *)(plVar2 + 3) = *(undefined4 *)(param_2 + 0x18);
    puVar1 = PTR__ZTV28CFieldMessage_ReceiveRecover_02cba3b0;
    lVar3 = *(long *)(param_2 + 8);
    plVar2[2] = *(long *)(param_2 + 0x10);
    plVar2[1] = lVar3;
    *plVar2 = (long)(puVar1 + 0x10);
    *(undefined4 *)(plVar2 + 6) = *(undefined4 *)(param_2 + 0x30);
    lVar3 = *(long *)(param_2 + 0x20);
    plVar2[5] = *(long *)(param_2 + 0x28);
    plVar2[4] = lVar3;
    lVar3 = *(long *)(param_2 + 0x40);
    plVar2[9] = *(long *)(param_2 + 0x48);
    plVar2[8] = lVar3;
    lVar3 = *(long *)(param_2 + 0x50);
    plVar2[0xb] = *(long *)(param_2 + 0x58);
    plVar2[10] = lVar3;
  }
  else {
    *plVar2 = (long)(PTR__ZTVN9Framework12CMessageBaseE_02cbb910 + 0x10);
    *(undefined4 *)(plVar2 + 3) = *(undefined4 *)(param_2 + 0x18);
    puVar1 = PTR__ZTV28CFieldMessage_ReceiveRecover_02cba3b0;
    lVar3 = *(long *)(param_2 + 8);
    plVar2[2] = *(long *)(param_2 + 0x10);
    plVar2[1] = lVar3;
    *plVar2 = (long)(puVar1 + 0x10);
    *(undefined4 *)(plVar2 + 6) = *(undefined4 *)(param_2 + 0x30);
    lVar3 = *(long *)(param_2 + 0x20);
    plVar2[5] = *(long *)(param_2 + 0x28);
    plVar2[4] = lVar3;
    *(undefined4 *)(plVar2 + 8) = *(undefined4 *)(param_2 + 0x40);
    *(undefined4 *)((long)plVar2 + 0x44) = *(undefined4 *)(param_2 + 0x44);
    *(undefined4 *)(plVar2 + 9) = *(undefined4 *)(param_2 + 0x48);
    *(undefined4 *)((long)plVar2 + 0x4c) = *(undefined4 *)(param_2 + 0x4c);
    *(undefined4 *)(plVar2 + 10) = *(undefined4 *)(param_2 + 0x50);
    *(undefined4 *)((long)plVar2 + 0x54) = *(undefined4 *)(param_2 + 0x54);
    *(undefined4 *)(plVar2 + 0xb) = *(undefined4 *)(param_2 + 0x58);
    *(undefined4 *)((long)plVar2 + 0x5c) = *(undefined4 *)(param_2 + 0x5c);
  }
  *(undefined2 *)(plVar2 + 0xe) = *(undefined2 *)(param_2 + 0x70);
  lVar3 = *(long *)(param_2 + 0x60);
  plVar2[0xd] = *(long *)(param_2 + 0x68);
  plVar2[0xc] = lVar3;
  *(undefined2 *)(plVar2 + 0x10) = *(undefined2 *)(param_2 + 0x80);
  *(undefined4 *)(plVar2 + 0x12) = *(undefined4 *)(param_2 + 0x90);
  return;
}

// ==== void Framework::CMessageManager::SendMessage<CFieldMessage_CreateBehavior_Abnormal>(CFieldMessage_CreateBehavior_Abnormal const&)
// vaddr 0x122e4ec | ghidra 0x132e4ec | size 352 | symbol _ZN9Framework15CMessageManager11SendMessageI37CFieldMessage_CreateBehavior_AbnormalEEvRKT_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework15CMessageManager11SendMessageI37CFieldMessage_CreateBehavior_AbnormalEEvRKT_
               (long param_1,long param_2)

{
  undefined8 *puVar1;
  undefined *puVar2;
  long *plVar3;
  ulong uVar4;
  long lVar5;
  undefined8 uVar6;
  long *plStack_28;
  
  if (*(int *)(param_2 + 0x18) != 0) {
    if (*(int *)(param_2 + 0x18) != 1) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027e64e8/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/MessageManager.h"*/,0x9e,&UNK_027e6540/*"Illegal attribute.(%d)"*/);
    }
    (*(code *)PTR__ZN9Framework15CMessageManager17DirectSendMessageERKNS_12CMessageBaseE_02c8fff0)
              (param_1,param_2);
    return;
  }
  if ((*(long *)(param_1 + 0x18) == 0) ||
     (plVar3 = (long *)Framework::CFixedLengthAllocatorContainer::pAllocate(unsigned long, char const*, unsigned int)(*(long *)(param_1 + 0x18),0x30,0,0), plVar3 == (long *)0x0))
  {
    plVar3 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x30,PTR__ZSt7nothrow_02cb9a80);
    if (plVar3 == (long *)0x0) goto code_r0x0132e5bc;
  }
  else {
    *plVar3 = (long)(PTR__ZTVN9Framework12CMessageBaseE_02cbb910 + 0x10);
  }
  *(undefined4 *)(plVar3 + 3) = *(undefined4 *)(param_2 + 0x18);
  puVar2 = PTR__ZTV37CFieldMessage_CreateBehavior_Abnormal_02cbfd70;
  lVar5 = *(long *)(param_2 + 8);
  plVar3[2] = *(long *)(param_2 + 0x10);
  plVar3[1] = lVar5;
  *plVar3 = (long)(puVar2 + 0x10);
  *(undefined4 *)((long)plVar3 + 0x2c) = *(undefined4 *)(param_2 + 0x2c);
  uVar6 = *(undefined8 *)(param_2 + 0x1c);
  *(undefined8 *)((long)plVar3 + 0x24) = *(undefined8 *)(param_2 + 0x24);
  *(undefined8 *)((long)plVar3 + 0x1c) = uVar6;
code_r0x0132e5bc:
  lVar5 = *(long *)(param_1 + 0x10);
  if (lVar5 != 0) {
    uVar4 = Framework::CMutex::IsInitialized() const(lVar5);
    if ((uVar4 & 1) == 0) {
      Framework::CMutex::Initialize()(lVar5);
    }
    Framework::CMutex::Lock()(lVar5);
  }
  puVar1 = *(undefined8 **)(param_1 + 0x78);
  plStack_28 = plVar3;
  if (puVar1 < *(undefined8 **)(param_1 + 0x80)) {
    if (puVar1 == (undefined8 *)0x0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
    }
    *puVar1 = plVar3;
    *(long *)(param_1 + 0x78) = *(long *)(param_1 + 0x78) + 8;
  }
  else {
    void std::__ndk1::vector<Framework::CMessageBase*, Framework::CSTLAllocator<Framework::CMessageBase*, Framework::CSTLVectorAllocatorInf> >::__push_back_slow_path<Framework::CMessageBase*>(Framework::CMessageBase*&&)(param_1 + 0x70,&plStack_28);
  }
  if (lVar5 != 0) {
    Framework::CMutex::Unlock()(lVar5);
  }
  return;
}

// ==== void Framework::CMessageManager::SendMessage<CFieldMessage_BunkerOrderBomb>(CFieldMessage_BunkerOrderBomb const&)
// vaddr 0x122e64c | ghidra 0x132e64c | size 340 | symbol _ZN9Framework15CMessageManager11SendMessageI29CFieldMessage_BunkerOrderBombEEvRKT_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework15CMessageManager11SendMessageI29CFieldMessage_BunkerOrderBombEEvRKT_
               (long param_1,long param_2)

{
  undefined8 *puVar1;
  long *plVar2;
  ulong uVar3;
  long lVar4;
  long *plStack_28;
  
  if (*(int *)(param_2 + 0x18) == 0) {
    if (((*(long *)(param_1 + 0x18) != 0) &&
        (plVar2 = (long *)Framework::CFixedLengthAllocatorContainer::pAllocate(unsigned long, char const*, unsigned int)(*(long *)(param_1 + 0x18),0x28,0,0), plVar2 != (long *)0x0
        )) || (plVar2 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x28,PTR__ZSt7nothrow_02cb9a80),
              plVar2 != (long *)0x0)) {
      *plVar2 = (long)(PTR__ZTVN9Framework12CMessageBaseE_02cbb910 + 0x10);
      *(undefined4 *)(plVar2 + 3) = *(undefined4 *)(param_2 + 0x18);
      lVar4 = *(long *)(param_2 + 8);
      plVar2[2] = *(long *)(param_2 + 0x10);
      plVar2[1] = lVar4;
      *plVar2 = (long)(PTR__ZTV29CFieldMessage_BunkerOrderBomb_02cbba78 + 0x10);
      *(undefined8 *)((long)plVar2 + 0x1c) = *(undefined8 *)(param_2 + 0x1c);
    }
    lVar4 = *(long *)(param_1 + 0x10);
    if (lVar4 != 0) {
      uVar3 = Framework::CMutex::IsInitialized() const(lVar4);
      if ((uVar3 & 1) == 0) {
        Framework::CMutex::Initialize()(lVar4);
      }
      Framework::CMutex::Lock()(lVar4);
    }
    puVar1 = *(undefined8 **)(param_1 + 0x78);
    plStack_28 = plVar2;
    if (puVar1 < *(undefined8 **)(param_1 + 0x80)) {
      if (puVar1 == (undefined8 *)0x0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
      }
      *puVar1 = plVar2;
      *(long *)(param_1 + 0x78) = *(long *)(param_1 + 0x78) + 8;
    }
    else {
      void std::__ndk1::vector<Framework::CMessageBase*, Framework::CSTLAllocator<Framework::CMessageBase*, Framework::CSTLVectorAllocatorInf> >::__push_back_slow_path<Framework::CMessageBase*>(Framework::CMessageBase*&&)(param_1 + 0x70,&plStack_28);
    }
    if (lVar4 != 0) {
      Framework::CMutex::Unlock()(lVar4);
    }
    return;
  }
  if (*(int *)(param_2 + 0x18) != 1) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027e64e8/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/MessageManager.h"*/,0x9e,&UNK_027e6540/*"Illegal attribute.(%d)"*/);
  }
  (*(code *)PTR__ZN9Framework15CMessageManager17DirectSendMessageERKNS_12CMessageBaseE_02c8fff0)
            (param_1,param_2);
  return;
}

// ==== void Framework::CMessageManager::SendMessage<CFieldMessage_RequestTransSync>(CFieldMessage_RequestTransSync const&)
// vaddr 0x1271f1c | ghidra 0x1371f1c | size 340 | symbol _ZN9Framework15CMessageManager11SendMessageI30CFieldMessage_RequestTransSyncEEvRKT_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework15CMessageManager11SendMessageI30CFieldMessage_RequestTransSyncEEvRKT_
               (long param_1,long param_2)

{
  undefined8 *puVar1;
  long *plVar2;
  ulong uVar3;
  long lVar4;
  long *plStack_28;
  
  if (*(int *)(param_2 + 0x18) == 0) {
    if (((*(long *)(param_1 + 0x18) != 0) &&
        (plVar2 = (long *)Framework::CFixedLengthAllocatorContainer::pAllocate(unsigned long, char const*, unsigned int)(*(long *)(param_1 + 0x18),0x20,0,0), plVar2 != (long *)0x0
        )) || (plVar2 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x20,PTR__ZSt7nothrow_02cb9a80),
              plVar2 != (long *)0x0)) {
      *plVar2 = (long)(PTR__ZTVN9Framework12CMessageBaseE_02cbb910 + 0x10);
      *(undefined4 *)(plVar2 + 3) = *(undefined4 *)(param_2 + 0x18);
      lVar4 = *(long *)(param_2 + 8);
      plVar2[2] = *(long *)(param_2 + 0x10);
      plVar2[1] = lVar4;
      *plVar2 = (long)(PTR__ZTV30CFieldMessage_RequestTransSync_02cc0e60 + 0x10);
      *(undefined4 *)((long)plVar2 + 0x1c) = *(undefined4 *)(param_2 + 0x1c);
    }
    lVar4 = *(long *)(param_1 + 0x10);
    if (lVar4 != 0) {
      uVar3 = Framework::CMutex::IsInitialized() const(lVar4);
      if ((uVar3 & 1) == 0) {
        Framework::CMutex::Initialize()(lVar4);
      }
      Framework::CMutex::Lock()(lVar4);
    }
    puVar1 = *(undefined8 **)(param_1 + 0x78);
    plStack_28 = plVar2;
    if (puVar1 < *(undefined8 **)(param_1 + 0x80)) {
      if (puVar1 == (undefined8 *)0x0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
      }
      *puVar1 = plVar2;
      *(long *)(param_1 + 0x78) = *(long *)(param_1 + 0x78) + 8;
    }
    else {
      void std::__ndk1::vector<Framework::CMessageBase*, Framework::CSTLAllocator<Framework::CMessageBase*, Framework::CSTLVectorAllocatorInf> >::__push_back_slow_path<Framework::CMessageBase*>(Framework::CMessageBase*&&)(param_1 + 0x70,&plStack_28);
    }
    if (lVar4 != 0) {
      Framework::CMutex::Unlock()(lVar4);
    }
    return;
  }
  if (*(int *)(param_2 + 0x18) != 1) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027e64e8/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/MessageManager.h"*/,0x9e,&UNK_027e6540/*"Illegal attribute.(%d)"*/);
  }
  (*(code *)PTR__ZN9Framework15CMessageManager17DirectSendMessageERKNS_12CMessageBaseE_02c8fff0)
            (param_1,param_2);
  return;
}

// ==== void Framework::CMessageManager::SendMessage<CFieldMessage_RequestTrans>(CFieldMessage_RequestTrans const&)
// vaddr 0x1272070 | ghidra 0x1372070 | size 332 | symbol _ZN9Framework15CMessageManager11SendMessageI26CFieldMessage_RequestTransEEvRKT_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework15CMessageManager11SendMessageI26CFieldMessage_RequestTransEEvRKT_
               (long param_1,long param_2)

{
  undefined8 *puVar1;
  long *plVar2;
  ulong uVar3;
  long lVar4;
  long *plStack_28;
  
  if (*(int *)(param_2 + 0x18) == 0) {
    if (((*(long *)(param_1 + 0x18) != 0) &&
        (plVar2 = (long *)Framework::CFixedLengthAllocatorContainer::pAllocate(unsigned long, char const*, unsigned int)(*(long *)(param_1 + 0x18),0x20,0,0), plVar2 != (long *)0x0
        )) || (plVar2 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x20,PTR__ZSt7nothrow_02cb9a80),
              plVar2 != (long *)0x0)) {
      *plVar2 = (long)(PTR__ZTVN9Framework12CMessageBaseE_02cbb910 + 0x10);
      *(undefined4 *)(plVar2 + 3) = *(undefined4 *)(param_2 + 0x18);
      lVar4 = *(long *)(param_2 + 8);
      plVar2[2] = *(long *)(param_2 + 0x10);
      plVar2[1] = lVar4;
      *plVar2 = (long)(PTR__ZTV26CFieldMessage_RequestTrans_02cba820 + 0x10);
    }
    lVar4 = *(long *)(param_1 + 0x10);
    if (lVar4 != 0) {
      uVar3 = Framework::CMutex::IsInitialized() const(lVar4);
      if ((uVar3 & 1) == 0) {
        Framework::CMutex::Initialize()(lVar4);
      }
      Framework::CMutex::Lock()(lVar4);
    }
    puVar1 = *(undefined8 **)(param_1 + 0x78);
    plStack_28 = plVar2;
    if (puVar1 < *(undefined8 **)(param_1 + 0x80)) {
      if (puVar1 == (undefined8 *)0x0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
      }
      *puVar1 = plVar2;
      *(long *)(param_1 + 0x78) = *(long *)(param_1 + 0x78) + 8;
    }
    else {
      void std::__ndk1::vector<Framework::CMessageBase*, Framework::CSTLAllocator<Framework::CMessageBase*, Framework::CSTLVectorAllocatorInf> >::__push_back_slow_path<Framework::CMessageBase*>(Framework::CMessageBase*&&)(param_1 + 0x70,&plStack_28);
    }
    if (lVar4 != 0) {
      Framework::CMutex::Unlock()(lVar4);
    }
    return;
  }
  if (*(int *)(param_2 + 0x18) != 1) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027e64e8/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/MessageManager.h"*/,0x9e,&UNK_027e6540/*"Illegal attribute.(%d)"*/);
  }
  (*(code *)PTR__ZN9Framework15CMessageManager17DirectSendMessageERKNS_12CMessageBaseE_02c8fff0)
            (param_1,param_2);
  return;
}

// ==== void Framework::CMessageManager::SendMessage<CFieldMessage_CreateBehavior_Dead>(CFieldMessage_CreateBehavior_Dead const&)
// vaddr 0x1272ac0 | ghidra 0x1372ac0 | size 332 | symbol _ZN9Framework15CMessageManager11SendMessageI33CFieldMessage_CreateBehavior_DeadEEvRKT_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework15CMessageManager11SendMessageI33CFieldMessage_CreateBehavior_DeadEEvRKT_
               (long param_1,long param_2)

{
  undefined8 *puVar1;
  long *plVar2;
  ulong uVar3;
  long lVar4;
  long *plStack_28;
  
  if (*(int *)(param_2 + 0x18) == 0) {
    if (((*(long *)(param_1 + 0x18) != 0) &&
        (plVar2 = (long *)Framework::CFixedLengthAllocatorContainer::pAllocate(unsigned long, char const*, unsigned int)(*(long *)(param_1 + 0x18),0x20,0,0), plVar2 != (long *)0x0
        )) || (plVar2 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x20,PTR__ZSt7nothrow_02cb9a80),
              plVar2 != (long *)0x0)) {
      *plVar2 = (long)(PTR__ZTVN9Framework12CMessageBaseE_02cbb910 + 0x10);
      *(undefined4 *)(plVar2 + 3) = *(undefined4 *)(param_2 + 0x18);
      lVar4 = *(long *)(param_2 + 8);
      plVar2[2] = *(long *)(param_2 + 0x10);
      plVar2[1] = lVar4;
      *plVar2 = (long)(PTR__ZTV33CFieldMessage_CreateBehavior_Dead_02cb8cf0 + 0x10);
    }
    lVar4 = *(long *)(param_1 + 0x10);
    if (lVar4 != 0) {
      uVar3 = Framework::CMutex::IsInitialized() const(lVar4);
      if ((uVar3 & 1) == 0) {
        Framework::CMutex::Initialize()(lVar4);
      }
      Framework::CMutex::Lock()(lVar4);
    }
    puVar1 = *(undefined8 **)(param_1 + 0x78);
    plStack_28 = plVar2;
    if (puVar1 < *(undefined8 **)(param_1 + 0x80)) {
      if (puVar1 == (undefined8 *)0x0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
      }
      *puVar1 = plVar2;
      *(long *)(param_1 + 0x78) = *(long *)(param_1 + 0x78) + 8;
    }
    else {
      void std::__ndk1::vector<Framework::CMessageBase*, Framework::CSTLAllocator<Framework::CMessageBase*, Framework::CSTLVectorAllocatorInf> >::__push_back_slow_path<Framework::CMessageBase*>(Framework::CMessageBase*&&)(param_1 + 0x70,&plStack_28);
    }
    if (lVar4 != 0) {
      Framework::CMutex::Unlock()(lVar4);
    }
    return;
  }
  if (*(int *)(param_2 + 0x18) != 1) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027e64e8/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/MessageManager.h"*/,0x9e,&UNK_027e6540/*"Illegal attribute.(%d)"*/);
  }
  (*(code *)PTR__ZN9Framework15CMessageManager17DirectSendMessageERKNS_12CMessageBaseE_02c8fff0)
            (param_1,param_2);
  return;
}

// ==== void Framework::CMessageManager::SendMessage<CFieldMessage_BlowAway>(CFieldMessage_BlowAway const&)
// vaddr 0x1272c0c | ghidra 0x1372c0c | size 364 | symbol _ZN9Framework15CMessageManager11SendMessageI22CFieldMessage_BlowAwayEEvRKT_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework15CMessageManager11SendMessageI22CFieldMessage_BlowAwayEEvRKT_
               (long param_1,long param_2)

{
  undefined8 *puVar1;
  long *plVar2;
  ulong uVar3;
  long lVar4;
  long *plStack_28;
  
  if (*(int *)(param_2 + 0x18) == 0) {
    if (((*(long *)(param_1 + 0x18) != 0) &&
        (plVar2 = (long *)Framework::CFixedLengthAllocatorContainer::pAllocate(unsigned long, char const*, unsigned int)(*(long *)(param_1 + 0x18),0x30,0,0), plVar2 != (long *)0x0
        )) || (plVar2 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x30,PTR__ZSt7nothrow_02cb9a80),
              plVar2 != (long *)0x0)) {
      *plVar2 = (long)(PTR__ZTVN9Framework12CMessageBaseE_02cbb910 + 0x10);
      *(undefined4 *)(plVar2 + 3) = *(undefined4 *)(param_2 + 0x18);
      lVar4 = *(long *)(param_2 + 8);
      plVar2[2] = *(long *)(param_2 + 0x10);
      plVar2[1] = lVar4;
      *plVar2 = (long)(PTR__ZTV22CFieldMessage_BlowAway_02cc3418 + 0x10);
      *(undefined4 *)(plVar2 + 4) = *(undefined4 *)(param_2 + 0x20);
      *(undefined4 *)((long)plVar2 + 0x24) = *(undefined4 *)(param_2 + 0x24);
      *(undefined4 *)(plVar2 + 5) = *(undefined4 *)(param_2 + 0x28);
      *(undefined4 *)((long)plVar2 + 0x2c) = *(undefined4 *)(param_2 + 0x2c);
    }
    lVar4 = *(long *)(param_1 + 0x10);
    if (lVar4 != 0) {
      uVar3 = Framework::CMutex::IsInitialized() const(lVar4);
      if ((uVar3 & 1) == 0) {
        Framework::CMutex::Initialize()(lVar4);
      }
      Framework::CMutex::Lock()(lVar4);
    }
    puVar1 = *(undefined8 **)(param_1 + 0x78);
    plStack_28 = plVar2;
    if (puVar1 < *(undefined8 **)(param_1 + 0x80)) {
      if (puVar1 == (undefined8 *)0x0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
      }
      *puVar1 = plVar2;
      *(long *)(param_1 + 0x78) = *(long *)(param_1 + 0x78) + 8;
    }
    else {
      void std::__ndk1::vector<Framework::CMessageBase*, Framework::CSTLAllocator<Framework::CMessageBase*, Framework::CSTLVectorAllocatorInf> >::__push_back_slow_path<Framework::CMessageBase*>(Framework::CMessageBase*&&)(param_1 + 0x70,&plStack_28);
    }
    if (lVar4 != 0) {
      Framework::CMutex::Unlock()(lVar4);
    }
    return;
  }
  if (*(int *)(param_2 + 0x18) != 1) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027e64e8/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/MessageManager.h"*/,0x9e,&UNK_027e6540/*"Illegal attribute.(%d)"*/);
  }
  (*(code *)PTR__ZN9Framework15CMessageManager17DirectSendMessageERKNS_12CMessageBaseE_02c8fff0)
            (param_1,param_2);
  return;
}

// ==== void Framework::CMessageManager::SendMessage<CFieldMessage_CreateBehavior_Guard>(CFieldMessage_CreateBehavior_Guard const&)
// vaddr 0x1272d78 | ghidra 0x1372d78 | size 372 | symbol _ZN9Framework15CMessageManager11SendMessageI34CFieldMessage_CreateBehavior_GuardEEvRKT_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework15CMessageManager11SendMessageI34CFieldMessage_CreateBehavior_GuardEEvRKT_
               (long param_1,long param_2)

{
  undefined8 *puVar1;
  long *plVar2;
  ulong uVar3;
  long lVar4;
  long *plStack_28;
  
  if (*(int *)(param_2 + 0x18) == 0) {
    if (((*(long *)(param_1 + 0x18) != 0) &&
        (plVar2 = (long *)Framework::CFixedLengthAllocatorContainer::pAllocate(unsigned long, char const*, unsigned int)(*(long *)(param_1 + 0x18),0x40,0,0), plVar2 != (long *)0x0
        )) || (plVar2 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x40,PTR__ZSt7nothrow_02cb9a80),
              plVar2 != (long *)0x0)) {
      *plVar2 = (long)(PTR__ZTVN9Framework12CMessageBaseE_02cbb910 + 0x10);
      *(undefined4 *)(plVar2 + 3) = *(undefined4 *)(param_2 + 0x18);
      lVar4 = *(long *)(param_2 + 8);
      plVar2[2] = *(long *)(param_2 + 0x10);
      plVar2[1] = lVar4;
      *plVar2 = (long)(PTR__ZTV34CFieldMessage_CreateBehavior_Guard_02cbee20 + 0x10);
      *(undefined4 *)(plVar2 + 4) = *(undefined4 *)(param_2 + 0x20);
      *(undefined4 *)((long)plVar2 + 0x24) = *(undefined4 *)(param_2 + 0x24);
      *(undefined4 *)(plVar2 + 5) = *(undefined4 *)(param_2 + 0x28);
      *(undefined4 *)((long)plVar2 + 0x2c) = *(undefined4 *)(param_2 + 0x2c);
      *(undefined1 *)(plVar2 + 6) = *(undefined1 *)(param_2 + 0x30);
    }
    lVar4 = *(long *)(param_1 + 0x10);
    if (lVar4 != 0) {
      uVar3 = Framework::CMutex::IsInitialized() const(lVar4);
      if ((uVar3 & 1) == 0) {
        Framework::CMutex::Initialize()(lVar4);
      }
      Framework::CMutex::Lock()(lVar4);
    }
    puVar1 = *(undefined8 **)(param_1 + 0x78);
    plStack_28 = plVar2;
    if (puVar1 < *(undefined8 **)(param_1 + 0x80)) {
      if (puVar1 == (undefined8 *)0x0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
      }
      *puVar1 = plVar2;
      *(long *)(param_1 + 0x78) = *(long *)(param_1 + 0x78) + 8;
    }
    else {
      void std::__ndk1::vector<Framework::CMessageBase*, Framework::CSTLAllocator<Framework::CMessageBase*, Framework::CSTLVectorAllocatorInf> >::__push_back_slow_path<Framework::CMessageBase*>(Framework::CMessageBase*&&)(param_1 + 0x70,&plStack_28);
    }
    if (lVar4 != 0) {
      Framework::CMutex::Unlock()(lVar4);
    }
    return;
  }
  if (*(int *)(param_2 + 0x18) != 1) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027e64e8/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/MessageManager.h"*/,0x9e,&UNK_027e6540/*"Illegal attribute.(%d)"*/);
  }
  (*(code *)PTR__ZN9Framework15CMessageManager17DirectSendMessageERKNS_12CMessageBaseE_02c8fff0)
            (param_1,param_2);
  return;
}

// ==== void Framework::CMessageManager::SendMessage<CFieldMessage_CreateBehavior_Down>(CFieldMessage_CreateBehavior_Down const&)
// vaddr 0x1272eec | ghidra 0x1372eec | size 372 | symbol _ZN9Framework15CMessageManager11SendMessageI33CFieldMessage_CreateBehavior_DownEEvRKT_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework15CMessageManager11SendMessageI33CFieldMessage_CreateBehavior_DownEEvRKT_
               (long param_1,long param_2)

{
  undefined8 *puVar1;
  long *plVar2;
  ulong uVar3;
  long lVar4;
  long *plStack_28;
  
  if (*(int *)(param_2 + 0x18) == 0) {
    if (((*(long *)(param_1 + 0x18) != 0) &&
        (plVar2 = (long *)Framework::CFixedLengthAllocatorContainer::pAllocate(unsigned long, char const*, unsigned int)(*(long *)(param_1 + 0x18),0x30,0,0), plVar2 != (long *)0x0
        )) || (plVar2 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x30,PTR__ZSt7nothrow_02cb9a80),
              plVar2 != (long *)0x0)) {
      *plVar2 = (long)(PTR__ZTVN9Framework12CMessageBaseE_02cbb910 + 0x10);
      *(undefined4 *)(plVar2 + 3) = *(undefined4 *)(param_2 + 0x18);
      lVar4 = *(long *)(param_2 + 8);
      plVar2[2] = *(long *)(param_2 + 0x10);
      plVar2[1] = lVar4;
      *plVar2 = (long)(PTR__ZTV33CFieldMessage_CreateBehavior_Down_02cbb150 + 0x10);
      *(undefined4 *)((long)plVar2 + 0x1c) = *(undefined4 *)(param_2 + 0x1c);
      *(undefined4 *)(plVar2 + 4) = *(undefined4 *)(param_2 + 0x20);
      *(undefined4 *)((long)plVar2 + 0x24) = *(undefined4 *)(param_2 + 0x24);
      *(undefined4 *)(plVar2 + 5) = *(undefined4 *)(param_2 + 0x28);
      *(undefined4 *)((long)plVar2 + 0x2c) = *(undefined4 *)(param_2 + 0x2c);
    }
    lVar4 = *(long *)(param_1 + 0x10);
    if (lVar4 != 0) {
      uVar3 = Framework::CMutex::IsInitialized() const(lVar4);
      if ((uVar3 & 1) == 0) {
        Framework::CMutex::Initialize()(lVar4);
      }
      Framework::CMutex::Lock()(lVar4);
    }
    puVar1 = *(undefined8 **)(param_1 + 0x78);
    plStack_28 = plVar2;
    if (puVar1 < *(undefined8 **)(param_1 + 0x80)) {
      if (puVar1 == (undefined8 *)0x0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
      }
      *puVar1 = plVar2;
      *(long *)(param_1 + 0x78) = *(long *)(param_1 + 0x78) + 8;
    }
    else {
      void std::__ndk1::vector<Framework::CMessageBase*, Framework::CSTLAllocator<Framework::CMessageBase*, Framework::CSTLVectorAllocatorInf> >::__push_back_slow_path<Framework::CMessageBase*>(Framework::CMessageBase*&&)(param_1 + 0x70,&plStack_28);
    }
    if (lVar4 != 0) {
      Framework::CMutex::Unlock()(lVar4);
    }
    return;
  }
  if (*(int *)(param_2 + 0x18) != 1) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027e64e8/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/MessageManager.h"*/,0x9e,&UNK_027e6540/*"Illegal attribute.(%d)"*/);
  }
  (*(code *)PTR__ZN9Framework15CMessageManager17DirectSendMessageERKNS_12CMessageBaseE_02c8fff0)
            (param_1,param_2);
  return;
}

// ==== void Framework::CMessageManager::SendMessage<CFieldMessage_CreateBehavior_Damage>(CFieldMessage_CreateBehavior_Damage const&)
// vaddr 0x1273060 | ghidra 0x1373060 | size 372 | symbol _ZN9Framework15CMessageManager11SendMessageI35CFieldMessage_CreateBehavior_DamageEEvRKT_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework15CMessageManager11SendMessageI35CFieldMessage_CreateBehavior_DamageEEvRKT_
               (long param_1,long param_2)

{
  undefined8 *puVar1;
  long *plVar2;
  ulong uVar3;
  long lVar4;
  long *plStack_28;
  
  if (*(int *)(param_2 + 0x18) == 0) {
    if (((*(long *)(param_1 + 0x18) != 0) &&
        (plVar2 = (long *)Framework::CFixedLengthAllocatorContainer::pAllocate(unsigned long, char const*, unsigned int)(*(long *)(param_1 + 0x18),0x30,0,0), plVar2 != (long *)0x0
        )) || (plVar2 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x30,PTR__ZSt7nothrow_02cb9a80),
              plVar2 != (long *)0x0)) {
      *plVar2 = (long)(PTR__ZTVN9Framework12CMessageBaseE_02cbb910 + 0x10);
      *(undefined4 *)(plVar2 + 3) = *(undefined4 *)(param_2 + 0x18);
      lVar4 = *(long *)(param_2 + 8);
      plVar2[2] = *(long *)(param_2 + 0x10);
      plVar2[1] = lVar4;
      *plVar2 = (long)(PTR__ZTV35CFieldMessage_CreateBehavior_Damage_02cb9a98 + 0x10);
      *(undefined4 *)((long)plVar2 + 0x1c) = *(undefined4 *)(param_2 + 0x1c);
      *(undefined4 *)(plVar2 + 4) = *(undefined4 *)(param_2 + 0x20);
      *(undefined4 *)((long)plVar2 + 0x24) = *(undefined4 *)(param_2 + 0x24);
      *(undefined4 *)(plVar2 + 5) = *(undefined4 *)(param_2 + 0x28);
      *(undefined4 *)((long)plVar2 + 0x2c) = *(undefined4 *)(param_2 + 0x2c);
    }
    lVar4 = *(long *)(param_1 + 0x10);
    if (lVar4 != 0) {
      uVar3 = Framework::CMutex::IsInitialized() const(lVar4);
      if ((uVar3 & 1) == 0) {
        Framework::CMutex::Initialize()(lVar4);
      }
      Framework::CMutex::Lock()(lVar4);
    }
    puVar1 = *(undefined8 **)(param_1 + 0x78);
    plStack_28 = plVar2;
    if (puVar1 < *(undefined8 **)(param_1 + 0x80)) {
      if (puVar1 == (undefined8 *)0x0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
      }
      *puVar1 = plVar2;
      *(long *)(param_1 + 0x78) = *(long *)(param_1 + 0x78) + 8;
    }
    else {
      void std::__ndk1::vector<Framework::CMessageBase*, Framework::CSTLAllocator<Framework::CMessageBase*, Framework::CSTLVectorAllocatorInf> >::__push_back_slow_path<Framework::CMessageBase*>(Framework::CMessageBase*&&)(param_1 + 0x70,&plStack_28);
    }
    if (lVar4 != 0) {
      Framework::CMutex::Unlock()(lVar4);
    }
    return;
  }
  if (*(int *)(param_2 + 0x18) != 1) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027e64e8/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/MessageManager.h"*/,0x9e,&UNK_027e6540/*"Illegal attribute.(%d)"*/);
  }
  (*(code *)PTR__ZN9Framework15CMessageManager17DirectSendMessageERKNS_12CMessageBaseE_02c8fff0)
            (param_1,param_2);
  return;
}

// ==== void Framework::CMessageManager::SendMessage<CFieldMessage_CreateBehavior_Idle>(CFieldMessage_CreateBehavior_Idle const&)
// vaddr 0x12731d4 | ghidra 0x13731d4 | size 332 | symbol _ZN9Framework15CMessageManager11SendMessageI33CFieldMessage_CreateBehavior_IdleEEvRKT_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework15CMessageManager11SendMessageI33CFieldMessage_CreateBehavior_IdleEEvRKT_
               (long param_1,long param_2)

{
  undefined8 *puVar1;
  long *plVar2;
  ulong uVar3;
  long lVar4;
  long *plStack_28;
  
  if (*(int *)(param_2 + 0x18) == 0) {
    if (((*(long *)(param_1 + 0x18) != 0) &&
        (plVar2 = (long *)Framework::CFixedLengthAllocatorContainer::pAllocate(unsigned long, char const*, unsigned int)(*(long *)(param_1 + 0x18),0x20,0,0), plVar2 != (long *)0x0
        )) || (plVar2 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x20,PTR__ZSt7nothrow_02cb9a80),
              plVar2 != (long *)0x0)) {
      *plVar2 = (long)(PTR__ZTVN9Framework12CMessageBaseE_02cbb910 + 0x10);
      *(undefined4 *)(plVar2 + 3) = *(undefined4 *)(param_2 + 0x18);
      lVar4 = *(long *)(param_2 + 8);
      plVar2[2] = *(long *)(param_2 + 0x10);
      plVar2[1] = lVar4;
      *plVar2 = (long)(PTR__ZTV33CFieldMessage_CreateBehavior_Idle_02cbf428 + 0x10);
    }
    lVar4 = *(long *)(param_1 + 0x10);
    if (lVar4 != 0) {
      uVar3 = Framework::CMutex::IsInitialized() const(lVar4);
      if ((uVar3 & 1) == 0) {
        Framework::CMutex::Initialize()(lVar4);
      }
      Framework::CMutex::Lock()(lVar4);
    }
    puVar1 = *(undefined8 **)(param_1 + 0x78);
    plStack_28 = plVar2;
    if (puVar1 < *(undefined8 **)(param_1 + 0x80)) {
      if (puVar1 == (undefined8 *)0x0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
      }
      *puVar1 = plVar2;
      *(long *)(param_1 + 0x78) = *(long *)(param_1 + 0x78) + 8;
    }
    else {
      void std::__ndk1::vector<Framework::CMessageBase*, Framework::CSTLAllocator<Framework::CMessageBase*, Framework::CSTLVectorAllocatorInf> >::__push_back_slow_path<Framework::CMessageBase*>(Framework::CMessageBase*&&)(param_1 + 0x70,&plStack_28);
    }
    if (lVar4 != 0) {
      Framework::CMutex::Unlock()(lVar4);
    }
    return;
  }
  if (*(int *)(param_2 + 0x18) != 1) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027e64e8/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/MessageManager.h"*/,0x9e,&UNK_027e6540/*"Illegal attribute.(%d)"*/);
  }
  (*(code *)PTR__ZN9Framework15CMessageManager17DirectSendMessageERKNS_12CMessageBaseE_02c8fff0)
            (param_1,param_2);
  return;
}

// ==== void Framework::CMessageManager::SendMessage<CFieldMessage_CreateBehavior_Skill>(CFieldMessage_CreateBehavior_Skill const&)
// vaddr 0x128c378 | ghidra 0x138c378 | size 332 | symbol _ZN9Framework15CMessageManager11SendMessageI34CFieldMessage_CreateBehavior_SkillEEvRKT_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework15CMessageManager11SendMessageI34CFieldMessage_CreateBehavior_SkillEEvRKT_
               (long param_1,long param_2)

{
  undefined8 *puVar1;
  long *plVar2;
  ulong uVar3;
  long lVar4;
  long *plStack_28;
  
  if (*(int *)(param_2 + 0x18) == 0) {
    if (((*(long *)(param_1 + 0x18) != 0) &&
        (plVar2 = (long *)Framework::CFixedLengthAllocatorContainer::pAllocate(unsigned long, char const*, unsigned int)(*(long *)(param_1 + 0x18),0x20,0,0), plVar2 != (long *)0x0
        )) || (plVar2 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x20,PTR__ZSt7nothrow_02cb9a80),
              plVar2 != (long *)0x0)) {
      *plVar2 = (long)(PTR__ZTVN9Framework12CMessageBaseE_02cbb910 + 0x10);
      *(undefined4 *)(plVar2 + 3) = *(undefined4 *)(param_2 + 0x18);
      lVar4 = *(long *)(param_2 + 8);
      plVar2[2] = *(long *)(param_2 + 0x10);
      plVar2[1] = lVar4;
      *plVar2 = (long)(PTR__ZTV34CFieldMessage_CreateBehavior_Skill_02cc4ba8 + 0x10);
    }
    lVar4 = *(long *)(param_1 + 0x10);
    if (lVar4 != 0) {
      uVar3 = Framework::CMutex::IsInitialized() const(lVar4);
      if ((uVar3 & 1) == 0) {
        Framework::CMutex::Initialize()(lVar4);
      }
      Framework::CMutex::Lock()(lVar4);
    }
    puVar1 = *(undefined8 **)(param_1 + 0x78);
    plStack_28 = plVar2;
    if (puVar1 < *(undefined8 **)(param_1 + 0x80)) {
      if (puVar1 == (undefined8 *)0x0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
      }
      *puVar1 = plVar2;
      *(long *)(param_1 + 0x78) = *(long *)(param_1 + 0x78) + 8;
    }
    else {
      void std::__ndk1::vector<Framework::CMessageBase*, Framework::CSTLAllocator<Framework::CMessageBase*, Framework::CSTLVectorAllocatorInf> >::__push_back_slow_path<Framework::CMessageBase*>(Framework::CMessageBase*&&)(param_1 + 0x70,&plStack_28);
    }
    if (lVar4 != 0) {
      Framework::CMutex::Unlock()(lVar4);
    }
    return;
  }
  if (*(int *)(param_2 + 0x18) != 1) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027e64e8/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/MessageManager.h"*/,0x9e,&UNK_027e6540/*"Illegal attribute.(%d)"*/);
  }
  (*(code *)PTR__ZN9Framework15CMessageManager17DirectSendMessageERKNS_12CMessageBaseE_02c8fff0)
            (param_1,param_2);
  return;
}

// ==== void Framework::CMessageManager::SendMessage<CFieldMessage_StartAssistSkill>(CFieldMessage_StartAssistSkill const&)
// vaddr 0x128c4c4 | ghidra 0x138c4c4 | size 332 | symbol _ZN9Framework15CMessageManager11SendMessageI30CFieldMessage_StartAssistSkillEEvRKT_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework15CMessageManager11SendMessageI30CFieldMessage_StartAssistSkillEEvRKT_
               (long param_1,long param_2)

{
  undefined8 *puVar1;
  long *plVar2;
  ulong uVar3;
  long lVar4;
  long *plStack_28;
  
  if (*(int *)(param_2 + 0x18) == 0) {
    if (((*(long *)(param_1 + 0x18) != 0) &&
        (plVar2 = (long *)Framework::CFixedLengthAllocatorContainer::pAllocate(unsigned long, char const*, unsigned int)(*(long *)(param_1 + 0x18),0x20,0,0), plVar2 != (long *)0x0
        )) || (plVar2 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x20,PTR__ZSt7nothrow_02cb9a80),
              plVar2 != (long *)0x0)) {
      *plVar2 = (long)(PTR__ZTVN9Framework12CMessageBaseE_02cbb910 + 0x10);
      *(undefined4 *)(plVar2 + 3) = *(undefined4 *)(param_2 + 0x18);
      lVar4 = *(long *)(param_2 + 8);
      plVar2[2] = *(long *)(param_2 + 0x10);
      plVar2[1] = lVar4;
      *plVar2 = (long)(PTR__ZTV30CFieldMessage_StartAssistSkill_02cbe9b0 + 0x10);
    }
    lVar4 = *(long *)(param_1 + 0x10);
    if (lVar4 != 0) {
      uVar3 = Framework::CMutex::IsInitialized() const(lVar4);
      if ((uVar3 & 1) == 0) {
        Framework::CMutex::Initialize()(lVar4);
      }
      Framework::CMutex::Lock()(lVar4);
    }
    puVar1 = *(undefined8 **)(param_1 + 0x78);
    plStack_28 = plVar2;
    if (puVar1 < *(undefined8 **)(param_1 + 0x80)) {
      if (puVar1 == (undefined8 *)0x0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
      }
      *puVar1 = plVar2;
      *(long *)(param_1 + 0x78) = *(long *)(param_1 + 0x78) + 8;
    }
    else {
      void std::__ndk1::vector<Framework::CMessageBase*, Framework::CSTLAllocator<Framework::CMessageBase*, Framework::CSTLVectorAllocatorInf> >::__push_back_slow_path<Framework::CMessageBase*>(Framework::CMessageBase*&&)(param_1 + 0x70,&plStack_28);
    }
    if (lVar4 != 0) {
      Framework::CMutex::Unlock()(lVar4);
    }
    return;
  }
  if (*(int *)(param_2 + 0x18) != 1) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027e64e8/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/MessageManager.h"*/,0x9e,&UNK_027e6540/*"Illegal attribute.(%d)"*/);
  }
  (*(code *)PTR__ZN9Framework15CMessageManager17DirectSendMessageERKNS_12CMessageBaseE_02c8fff0)
            (param_1,param_2);
  return;
}

// ==== void Framework::CMessageManager::SendMessage<CFieldMessage_CreateBehavior_Order>(CFieldMessage_CreateBehavior_Order const&)
// vaddr 0x128c610 | ghidra 0x138c610 | size 344 | symbol _ZN9Framework15CMessageManager11SendMessageI34CFieldMessage_CreateBehavior_OrderEEvRKT_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework15CMessageManager11SendMessageI34CFieldMessage_CreateBehavior_OrderEEvRKT_
               (long param_1,long param_2)

{
  undefined8 *puVar1;
  undefined *puVar2;
  long *plVar3;
  ulong uVar4;
  long lVar5;
  undefined8 uVar6;
  long *plStack_28;
  
  if (*(int *)(param_2 + 0x18) != 0) {
    if (*(int *)(param_2 + 0x18) != 1) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027e64e8/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/MessageManager.h"*/,0x9e,&UNK_027e6540/*"Illegal attribute.(%d)"*/);
    }
    (*(code *)PTR__ZN9Framework15CMessageManager17DirectSendMessageERKNS_12CMessageBaseE_02c8fff0)
              (param_1,param_2);
    return;
  }
  if ((*(long *)(param_1 + 0x18) == 0) ||
     (plVar3 = (long *)Framework::CFixedLengthAllocatorContainer::pAllocate(unsigned long, char const*, unsigned int)(*(long *)(param_1 + 0x18),0x30,0,0), plVar3 == (long *)0x0))
  {
    plVar3 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x30,PTR__ZSt7nothrow_02cb9a80);
    if (plVar3 == (long *)0x0) goto code_r0x0138c6d8;
  }
  else {
    *plVar3 = (long)(PTR__ZTVN9Framework12CMessageBaseE_02cbb910 + 0x10);
  }
  *(undefined4 *)(plVar3 + 3) = *(undefined4 *)(param_2 + 0x18);
  puVar2 = PTR__ZTV34CFieldMessage_CreateBehavior_Order_02cbead0;
  lVar5 = *(long *)(param_2 + 8);
  plVar3[2] = *(long *)(param_2 + 0x10);
  plVar3[1] = lVar5;
  *plVar3 = (long)(puVar2 + 0x10);
  uVar6 = *(undefined8 *)(param_2 + 0x1c);
  *(undefined8 *)((long)plVar3 + 0x24) = *(undefined8 *)(param_2 + 0x24);
  *(undefined8 *)((long)plVar3 + 0x1c) = uVar6;
code_r0x0138c6d8:
  lVar5 = *(long *)(param_1 + 0x10);
  if (lVar5 != 0) {
    uVar4 = Framework::CMutex::IsInitialized() const(lVar5);
    if ((uVar4 & 1) == 0) {
      Framework::CMutex::Initialize()(lVar5);
    }
    Framework::CMutex::Lock()(lVar5);
  }
  puVar1 = *(undefined8 **)(param_1 + 0x78);
  plStack_28 = plVar3;
  if (puVar1 < *(undefined8 **)(param_1 + 0x80)) {
    if (puVar1 == (undefined8 *)0x0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
    }
    *puVar1 = plVar3;
    *(long *)(param_1 + 0x78) = *(long *)(param_1 + 0x78) + 8;
  }
  else {
    void std::__ndk1::vector<Framework::CMessageBase*, Framework::CSTLAllocator<Framework::CMessageBase*, Framework::CSTLVectorAllocatorInf> >::__push_back_slow_path<Framework::CMessageBase*>(Framework::CMessageBase*&&)(param_1 + 0x70,&plStack_28);
  }
  if (lVar5 != 0) {
    Framework::CMutex::Unlock()(lVar5);
  }
  return;
}

// ==== void Framework::CMessageManager::SendMessage<CFieldMessage_ComboPlus>(CFieldMessage_ComboPlus const&)
// vaddr 0x128c768 | ghidra 0x138c768 | size 340 | symbol _ZN9Framework15CMessageManager11SendMessageI23CFieldMessage_ComboPlusEEvRKT_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework15CMessageManager11SendMessageI23CFieldMessage_ComboPlusEEvRKT_
               (long param_1,long param_2)

{
  undefined8 *puVar1;
  long *plVar2;
  ulong uVar3;
  long lVar4;
  long *plStack_28;
  
  if (*(int *)(param_2 + 0x18) == 0) {
    if (((*(long *)(param_1 + 0x18) != 0) &&
        (plVar2 = (long *)Framework::CFixedLengthAllocatorContainer::pAllocate(unsigned long, char const*, unsigned int)(*(long *)(param_1 + 0x18),0x20,0,0), plVar2 != (long *)0x0
        )) || (plVar2 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x20,PTR__ZSt7nothrow_02cb9a80),
              plVar2 != (long *)0x0)) {
      *plVar2 = (long)(PTR__ZTVN9Framework12CMessageBaseE_02cbb910 + 0x10);
      *(undefined4 *)(plVar2 + 3) = *(undefined4 *)(param_2 + 0x18);
      lVar4 = *(long *)(param_2 + 8);
      plVar2[2] = *(long *)(param_2 + 0x10);
      plVar2[1] = lVar4;
      *plVar2 = (long)(PTR__ZTV23CFieldMessage_ComboPlus_02cc3d10 + 0x10);
      *(undefined4 *)((long)plVar2 + 0x1c) = *(undefined4 *)(param_2 + 0x1c);
    }
    lVar4 = *(long *)(param_1 + 0x10);
    if (lVar4 != 0) {
      uVar3 = Framework::CMutex::IsInitialized() const(lVar4);
      if ((uVar3 & 1) == 0) {
        Framework::CMutex::Initialize()(lVar4);
      }
      Framework::CMutex::Lock()(lVar4);
    }
    puVar1 = *(undefined8 **)(param_1 + 0x78);
    plStack_28 = plVar2;
    if (puVar1 < *(undefined8 **)(param_1 + 0x80)) {
      if (puVar1 == (undefined8 *)0x0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
      }
      *puVar1 = plVar2;
      *(long *)(param_1 + 0x78) = *(long *)(param_1 + 0x78) + 8;
    }
    else {
      void std::__ndk1::vector<Framework::CMessageBase*, Framework::CSTLAllocator<Framework::CMessageBase*, Framework::CSTLVectorAllocatorInf> >::__push_back_slow_path<Framework::CMessageBase*>(Framework::CMessageBase*&&)(param_1 + 0x70,&plStack_28);
    }
    if (lVar4 != 0) {
      Framework::CMutex::Unlock()(lVar4);
    }
    return;
  }
  if (*(int *)(param_2 + 0x18) != 1) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027e64e8/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/MessageManager.h"*/,0x9e,&UNK_027e6540/*"Illegal attribute.(%d)"*/);
  }
  (*(code *)PTR__ZN9Framework15CMessageManager17DirectSendMessageERKNS_12CMessageBaseE_02c8fff0)
            (param_1,param_2);
  return;
}

// ==== void Framework::CMessageManager::SendMessage<CFieldMessage_StartTensionMaxMode>(CFieldMessage_StartTensionMaxMode const&)
// vaddr 0x128d128 | ghidra 0x138d128 | size 340 | symbol _ZN9Framework15CMessageManager11SendMessageI33CFieldMessage_StartTensionMaxModeEEvRKT_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework15CMessageManager11SendMessageI33CFieldMessage_StartTensionMaxModeEEvRKT_
               (long param_1,long param_2)

{
  undefined8 *puVar1;
  long *plVar2;
  ulong uVar3;
  long lVar4;
  long *plStack_28;
  
  if (*(int *)(param_2 + 0x18) == 0) {
    if (((*(long *)(param_1 + 0x18) != 0) &&
        (plVar2 = (long *)Framework::CFixedLengthAllocatorContainer::pAllocate(unsigned long, char const*, unsigned int)(*(long *)(param_1 + 0x18),0x20,0,0), plVar2 != (long *)0x0
        )) || (plVar2 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x20,PTR__ZSt7nothrow_02cb9a80),
              plVar2 != (long *)0x0)) {
      *plVar2 = (long)(PTR__ZTVN9Framework12CMessageBaseE_02cbb910 + 0x10);
      *(undefined4 *)(plVar2 + 3) = *(undefined4 *)(param_2 + 0x18);
      lVar4 = *(long *)(param_2 + 8);
      plVar2[2] = *(long *)(param_2 + 0x10);
      plVar2[1] = lVar4;
      *plVar2 = (long)(PTR__ZTV33CFieldMessage_StartTensionMaxMode_02cc1300 + 0x10);
      *(undefined4 *)((long)plVar2 + 0x1c) = *(undefined4 *)(param_2 + 0x1c);
    }
    lVar4 = *(long *)(param_1 + 0x10);
    if (lVar4 != 0) {
      uVar3 = Framework::CMutex::IsInitialized() const(lVar4);
      if ((uVar3 & 1) == 0) {
        Framework::CMutex::Initialize()(lVar4);
      }
      Framework::CMutex::Lock()(lVar4);
    }
    puVar1 = *(undefined8 **)(param_1 + 0x78);
    plStack_28 = plVar2;
    if (puVar1 < *(undefined8 **)(param_1 + 0x80)) {
      if (puVar1 == (undefined8 *)0x0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
      }
      *puVar1 = plVar2;
      *(long *)(param_1 + 0x78) = *(long *)(param_1 + 0x78) + 8;
    }
    else {
      void std::__ndk1::vector<Framework::CMessageBase*, Framework::CSTLAllocator<Framework::CMessageBase*, Framework::CSTLVectorAllocatorInf> >::__push_back_slow_path<Framework::CMessageBase*>(Framework::CMessageBase*&&)(param_1 + 0x70,&plStack_28);
    }
    if (lVar4 != 0) {
      Framework::CMutex::Unlock()(lVar4);
    }
    return;
  }
  if (*(int *)(param_2 + 0x18) != 1) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027e64e8/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/MessageManager.h"*/,0x9e,&UNK_027e6540/*"Illegal attribute.(%d)"*/);
  }
  (*(code *)PTR__ZN9Framework15CMessageManager17DirectSendMessageERKNS_12CMessageBaseE_02c8fff0)
            (param_1,param_2);
  return;
}

// ==== void Framework::CMessageManager::SendMessage<CFieldMessage_CreateBehavior_Avoid>(CFieldMessage_CreateBehavior_Avoid const&)
// vaddr 0x1293a10 | ghidra 0x1393a10 | size 340 | symbol _ZN9Framework15CMessageManager11SendMessageI34CFieldMessage_CreateBehavior_AvoidEEvRKT_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework15CMessageManager11SendMessageI34CFieldMessage_CreateBehavior_AvoidEEvRKT_
               (long param_1,long param_2)

{
  undefined8 *puVar1;
  long *plVar2;
  ulong uVar3;
  long lVar4;
  long *plStack_28;
  
  if (*(int *)(param_2 + 0x18) == 0) {
    if (((*(long *)(param_1 + 0x18) != 0) &&
        (plVar2 = (long *)Framework::CFixedLengthAllocatorContainer::pAllocate(unsigned long, char const*, unsigned int)(*(long *)(param_1 + 0x18),0x20,0,0), plVar2 != (long *)0x0
        )) || (plVar2 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x20,PTR__ZSt7nothrow_02cb9a80),
              plVar2 != (long *)0x0)) {
      *plVar2 = (long)(PTR__ZTVN9Framework12CMessageBaseE_02cbb910 + 0x10);
      *(undefined4 *)(plVar2 + 3) = *(undefined4 *)(param_2 + 0x18);
      lVar4 = *(long *)(param_2 + 8);
      plVar2[2] = *(long *)(param_2 + 0x10);
      plVar2[1] = lVar4;
      *plVar2 = (long)(PTR__ZTV34CFieldMessage_CreateBehavior_Avoid_02cbf388 + 0x10);
      *(undefined4 *)((long)plVar2 + 0x1c) = *(undefined4 *)(param_2 + 0x1c);
    }
    lVar4 = *(long *)(param_1 + 0x10);
    if (lVar4 != 0) {
      uVar3 = Framework::CMutex::IsInitialized() const(lVar4);
      if ((uVar3 & 1) == 0) {
        Framework::CMutex::Initialize()(lVar4);
      }
      Framework::CMutex::Lock()(lVar4);
    }
    puVar1 = *(undefined8 **)(param_1 + 0x78);
    plStack_28 = plVar2;
    if (puVar1 < *(undefined8 **)(param_1 + 0x80)) {
      if (puVar1 == (undefined8 *)0x0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
      }
      *puVar1 = plVar2;
      *(long *)(param_1 + 0x78) = *(long *)(param_1 + 0x78) + 8;
    }
    else {
      void std::__ndk1::vector<Framework::CMessageBase*, Framework::CSTLAllocator<Framework::CMessageBase*, Framework::CSTLVectorAllocatorInf> >::__push_back_slow_path<Framework::CMessageBase*>(Framework::CMessageBase*&&)(param_1 + 0x70,&plStack_28);
    }
    if (lVar4 != 0) {
      Framework::CMutex::Unlock()(lVar4);
    }
    return;
  }
  if (*(int *)(param_2 + 0x18) != 1) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027e64e8/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/MessageManager.h"*/,0x9e,&UNK_027e6540/*"Illegal attribute.(%d)"*/);
  }
  (*(code *)PTR__ZN9Framework15CMessageManager17DirectSendMessageERKNS_12CMessageBaseE_02c8fff0)
            (param_1,param_2);
  return;
}

// ==== void Framework::CMessageManager::SendMessage<CFieldMessage_RequestRepop>(CFieldMessage_RequestRepop const&)
// vaddr 0x12c03a0 | ghidra 0x13c03a0 | size 372 | symbol _ZN9Framework15CMessageManager11SendMessageI26CFieldMessage_RequestRepopEEvRKT_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework15CMessageManager11SendMessageI26CFieldMessage_RequestRepopEEvRKT_
               (long param_1,long param_2)

{
  undefined8 *puVar1;
  long *plVar2;
  ulong uVar3;
  long lVar4;
  long *plStack_28;
  
  if (*(int *)(param_2 + 0x18) == 0) {
    if (((*(long *)(param_1 + 0x18) != 0) &&
        (plVar2 = (long *)Framework::CFixedLengthAllocatorContainer::pAllocate(unsigned long, char const*, unsigned int)(*(long *)(param_1 + 0x18),0x40,0,0), plVar2 != (long *)0x0
        )) || (plVar2 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x40,PTR__ZSt7nothrow_02cb9a80),
              plVar2 != (long *)0x0)) {
      *plVar2 = (long)(PTR__ZTVN9Framework12CMessageBaseE_02cbb910 + 0x10);
      *(undefined4 *)(plVar2 + 3) = *(undefined4 *)(param_2 + 0x18);
      lVar4 = *(long *)(param_2 + 8);
      plVar2[2] = *(long *)(param_2 + 0x10);
      plVar2[1] = lVar4;
      *plVar2 = (long)(PTR__ZTV26CFieldMessage_RequestRepop_02cc1388 + 0x10);
      *(undefined4 *)(plVar2 + 4) = *(undefined4 *)(param_2 + 0x20);
      *(undefined4 *)((long)plVar2 + 0x24) = *(undefined4 *)(param_2 + 0x24);
      *(undefined4 *)(plVar2 + 5) = *(undefined4 *)(param_2 + 0x28);
      *(undefined4 *)((long)plVar2 + 0x2c) = *(undefined4 *)(param_2 + 0x2c);
      *(undefined4 *)(plVar2 + 6) = *(undefined4 *)(param_2 + 0x30);
    }
    lVar4 = *(long *)(param_1 + 0x10);
    if (lVar4 != 0) {
      uVar3 = Framework::CMutex::IsInitialized() const(lVar4);
      if ((uVar3 & 1) == 0) {
        Framework::CMutex::Initialize()(lVar4);
      }
      Framework::CMutex::Lock()(lVar4);
    }
    puVar1 = *(undefined8 **)(param_1 + 0x78);
    plStack_28 = plVar2;
    if (puVar1 < *(undefined8 **)(param_1 + 0x80)) {
      if (puVar1 == (undefined8 *)0x0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
      }
      *puVar1 = plVar2;
      *(long *)(param_1 + 0x78) = *(long *)(param_1 + 0x78) + 8;
    }
    else {
      void std::__ndk1::vector<Framework::CMessageBase*, Framework::CSTLAllocator<Framework::CMessageBase*, Framework::CSTLVectorAllocatorInf> >::__push_back_slow_path<Framework::CMessageBase*>(Framework::CMessageBase*&&)(param_1 + 0x70,&plStack_28);
    }
    if (lVar4 != 0) {
      Framework::CMutex::Unlock()(lVar4);
    }
    return;
  }
  if (*(int *)(param_2 + 0x18) != 1) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027e64e8/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/MessageManager.h"*/,0x9e,&UNK_027e6540/*"Illegal attribute.(%d)"*/);
  }
  (*(code *)PTR__ZN9Framework15CMessageManager17DirectSendMessageERKNS_12CMessageBaseE_02c8fff0)
            (param_1,param_2);
  return;
}

// ==== void Framework::CMessageManager::SendMessage<CFieldMessage_CreateBehavior_Repop>(CFieldMessage_CreateBehavior_Repop const&)
// vaddr 0x12c0514 | ghidra 0x13c0514 | size 372 | symbol _ZN9Framework15CMessageManager11SendMessageI34CFieldMessage_CreateBehavior_RepopEEvRKT_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework15CMessageManager11SendMessageI34CFieldMessage_CreateBehavior_RepopEEvRKT_
               (long param_1,long param_2)

{
  undefined8 *puVar1;
  long *plVar2;
  ulong uVar3;
  long lVar4;
  long *plStack_28;
  
  if (*(int *)(param_2 + 0x18) == 0) {
    if (((*(long *)(param_1 + 0x18) != 0) &&
        (plVar2 = (long *)Framework::CFixedLengthAllocatorContainer::pAllocate(unsigned long, char const*, unsigned int)(*(long *)(param_1 + 0x18),0x40,0,0), plVar2 != (long *)0x0
        )) || (plVar2 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x40,PTR__ZSt7nothrow_02cb9a80),
              plVar2 != (long *)0x0)) {
      *plVar2 = (long)(PTR__ZTVN9Framework12CMessageBaseE_02cbb910 + 0x10);
      *(undefined4 *)(plVar2 + 3) = *(undefined4 *)(param_2 + 0x18);
      lVar4 = *(long *)(param_2 + 8);
      plVar2[2] = *(long *)(param_2 + 0x10);
      plVar2[1] = lVar4;
      *plVar2 = (long)(PTR__ZTV34CFieldMessage_CreateBehavior_Repop_02cbb4e8 + 0x10);
      *(undefined4 *)(plVar2 + 4) = *(undefined4 *)(param_2 + 0x20);
      *(undefined4 *)((long)plVar2 + 0x24) = *(undefined4 *)(param_2 + 0x24);
      *(undefined4 *)(plVar2 + 5) = *(undefined4 *)(param_2 + 0x28);
      *(undefined4 *)((long)plVar2 + 0x2c) = *(undefined4 *)(param_2 + 0x2c);
      *(undefined4 *)(plVar2 + 6) = *(undefined4 *)(param_2 + 0x30);
    }
    lVar4 = *(long *)(param_1 + 0x10);
    if (lVar4 != 0) {
      uVar3 = Framework::CMutex::IsInitialized() const(lVar4);
      if ((uVar3 & 1) == 0) {
        Framework::CMutex::Initialize()(lVar4);
      }
      Framework::CMutex::Lock()(lVar4);
    }
    puVar1 = *(undefined8 **)(param_1 + 0x78);
    plStack_28 = plVar2;
    if (puVar1 < *(undefined8 **)(param_1 + 0x80)) {
      if (puVar1 == (undefined8 *)0x0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
      }
      *puVar1 = plVar2;
      *(long *)(param_1 + 0x78) = *(long *)(param_1 + 0x78) + 8;
    }
    else {
      void std::__ndk1::vector<Framework::CMessageBase*, Framework::CSTLAllocator<Framework::CMessageBase*, Framework::CSTLVectorAllocatorInf> >::__push_back_slow_path<Framework::CMessageBase*>(Framework::CMessageBase*&&)(param_1 + 0x70,&plStack_28);
    }
    if (lVar4 != 0) {
      Framework::CMutex::Unlock()(lVar4);
    }
    return;
  }
  if (*(int *)(param_2 + 0x18) != 1) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027e64e8/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/MessageManager.h"*/,0x9e,&UNK_027e6540/*"Illegal attribute.(%d)"*/);
  }
  (*(code *)PTR__ZN9Framework15CMessageManager17DirectSendMessageERKNS_12CMessageBaseE_02c8fff0)
            (param_1,param_2);
  return;
}

// ==== void Framework::CMessageManager::SendMessage<CFieldMessage_StartRushComboSetHeatUpBonus>(CFieldMessage_StartRushComboSetHeatUpBonus const&)
// vaddr 0x13b6ab4 | ghidra 0x14b6ab4 | size 340 | symbol _ZN9Framework15CMessageManager11SendMessageI42CFieldMessage_StartRushComboSetHeatUpBonusEEvRKT_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework15CMessageManager11SendMessageI42CFieldMessage_StartRushComboSetHeatUpBonusEEvRKT_
               (long param_1,long param_2)

{
  undefined8 *puVar1;
  long *plVar2;
  ulong uVar3;
  long lVar4;
  long *plStack_28;
  
  if (*(int *)(param_2 + 0x18) == 0) {
    if (((*(long *)(param_1 + 0x18) != 0) &&
        (plVar2 = (long *)Framework::CFixedLengthAllocatorContainer::pAllocate(unsigned long, char const*, unsigned int)(*(long *)(param_1 + 0x18),0x20,0,0), plVar2 != (long *)0x0
        )) || (plVar2 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x20,PTR__ZSt7nothrow_02cb9a80),
              plVar2 != (long *)0x0)) {
      *plVar2 = (long)(PTR__ZTVN9Framework12CMessageBaseE_02cbb910 + 0x10);
      *(undefined4 *)(plVar2 + 3) = *(undefined4 *)(param_2 + 0x18);
      lVar4 = *(long *)(param_2 + 8);
      plVar2[2] = *(long *)(param_2 + 0x10);
      plVar2[1] = lVar4;
      *plVar2 = (long)(PTR__ZTV42CFieldMessage_StartRushComboSetHeatUpBonus_02cc3fe0 + 0x10);
      *(undefined4 *)((long)plVar2 + 0x1c) = *(undefined4 *)(param_2 + 0x1c);
    }
    lVar4 = *(long *)(param_1 + 0x10);
    if (lVar4 != 0) {
      uVar3 = Framework::CMutex::IsInitialized() const(lVar4);
      if ((uVar3 & 1) == 0) {
        Framework::CMutex::Initialize()(lVar4);
      }
      Framework::CMutex::Lock()(lVar4);
    }
    puVar1 = *(undefined8 **)(param_1 + 0x78);
    plStack_28 = plVar2;
    if (puVar1 < *(undefined8 **)(param_1 + 0x80)) {
      if (puVar1 == (undefined8 *)0x0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
      }
      *puVar1 = plVar2;
      *(long *)(param_1 + 0x78) = *(long *)(param_1 + 0x78) + 8;
    }
    else {
      void std::__ndk1::vector<Framework::CMessageBase*, Framework::CSTLAllocator<Framework::CMessageBase*, Framework::CSTLVectorAllocatorInf> >::__push_back_slow_path<Framework::CMessageBase*>(Framework::CMessageBase*&&)(param_1 + 0x70,&plStack_28);
    }
    if (lVar4 != 0) {
      Framework::CMutex::Unlock()(lVar4);
    }
    return;
  }
  if (*(int *)(param_2 + 0x18) != 1) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027e64e8/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/MessageManager.h"*/,0x9e,&UNK_027e6540/*"Illegal attribute.(%d)"*/);
  }
  (*(code *)PTR__ZN9Framework15CMessageManager17DirectSendMessageERKNS_12CMessageBaseE_02c8fff0)
            (param_1,param_2);
  return;
}

// ==== void Framework::CMessageManager::SendMessage<CFieldMessage_Multiplay_CharacterParameter>(CFieldMessage_Multiplay_CharacterParameter const&)
// vaddr 0x13b6c08 | ghidra 0x14b6c08 | size 352 | symbol _ZN9Framework15CMessageManager11SendMessageI42CFieldMessage_Multiplay_CharacterParameterEEvRKT_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework15CMessageManager11SendMessageI42CFieldMessage_Multiplay_CharacterParameterEEvRKT_
               (long param_1,long param_2)

{
  undefined8 *puVar1;
  undefined *puVar2;
  long *plVar3;
  ulong uVar4;
  long lVar5;
  long lVar6;
  long *plStack_28;
  
  if (*(int *)(param_2 + 0x18) != 0) {
    if (*(int *)(param_2 + 0x18) != 1) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027e64e8/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/MessageManager.h"*/,0x9e,&UNK_027e6540/*"Illegal attribute.(%d)"*/);
    }
    (*(code *)PTR__ZN9Framework15CMessageManager17DirectSendMessageERKNS_12CMessageBaseE_02c8fff0)
              (param_1,param_2);
    return;
  }
  if ((*(long *)(param_1 + 0x18) == 0) ||
     (plVar3 = (long *)Framework::CFixedLengthAllocatorContainer::pAllocate(unsigned long, char const*, unsigned int)(*(long *)(param_1 + 0x18),0xa0,0,0), plVar3 == (long *)0x0))
  {
    plVar3 = (long *)operator new(unsigned long, std::nothrow_t const&)(0xa0,PTR__ZSt7nothrow_02cb9a80);
    if (plVar3 == (long *)0x0) goto code_r0x014b6cd8;
  }
  else {
    *plVar3 = (long)(PTR__ZTVN9Framework12CMessageBaseE_02cbb910 + 0x10);
  }
  puVar2 = PTR__ZTV42CFieldMessage_Multiplay_CharacterParameter_02cc43d0;
  *(undefined4 *)(plVar3 + 3) = *(undefined4 *)(param_2 + 0x18);
  lVar6 = *(long *)(param_2 + 0x10);
  lVar5 = *(long *)(param_2 + 8);
  *plVar3 = (long)(puVar2 + 0x10);
  plVar3[2] = lVar6;
  plVar3[1] = lVar5;
  memcpy((long)plVar3 + 0x1c,param_2 + 0x1c,0x82);
code_r0x014b6cd8:
  lVar5 = *(long *)(param_1 + 0x10);
  if (lVar5 != 0) {
    uVar4 = Framework::CMutex::IsInitialized() const(lVar5);
    if ((uVar4 & 1) == 0) {
      Framework::CMutex::Initialize()(lVar5);
    }
    Framework::CMutex::Lock()(lVar5);
  }
  puVar1 = *(undefined8 **)(param_1 + 0x78);
  plStack_28 = plVar3;
  if (puVar1 < *(undefined8 **)(param_1 + 0x80)) {
    if (puVar1 == (undefined8 *)0x0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
    }
    *puVar1 = plVar3;
    *(long *)(param_1 + 0x78) = *(long *)(param_1 + 0x78) + 8;
  }
  else {
    void std::__ndk1::vector<Framework::CMessageBase*, Framework::CSTLAllocator<Framework::CMessageBase*, Framework::CSTLVectorAllocatorInf> >::__push_back_slow_path<Framework::CMessageBase*>(Framework::CMessageBase*&&)(param_1 + 0x70,&plStack_28);
  }
  if (lVar5 != 0) {
    Framework::CMutex::Unlock()(lVar5);
  }
  return;
}

// ==== void Framework::CMessageManager::SendMessage<CFieldMessage_Multiplay_DamageUIParameter>(CFieldMessage_Multiplay_DamageUIParameter const&)
// vaddr 0x13b6d68 | ghidra 0x14b6d68 | size 352 | symbol _ZN9Framework15CMessageManager11SendMessageI41CFieldMessage_Multiplay_DamageUIParameterEEvRKT_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework15CMessageManager11SendMessageI41CFieldMessage_Multiplay_DamageUIParameterEEvRKT_
               (long param_1,long param_2)

{
  undefined8 *puVar1;
  undefined *puVar2;
  long *plVar3;
  ulong uVar4;
  long lVar5;
  long lVar6;
  long *plStack_28;
  
  if (*(int *)(param_2 + 0x18) != 0) {
    if (*(int *)(param_2 + 0x18) != 1) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027e64e8/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/MessageManager.h"*/,0x9e,&UNK_027e6540/*"Illegal attribute.(%d)"*/);
    }
    (*(code *)PTR__ZN9Framework15CMessageManager17DirectSendMessageERKNS_12CMessageBaseE_02c8fff0)
              (param_1,param_2);
    return;
  }
  if ((*(long *)(param_1 + 0x18) == 0) ||
     (plVar3 = (long *)Framework::CFixedLengthAllocatorContainer::pAllocate(unsigned long, char const*, unsigned int)(*(long *)(param_1 + 0x18),0x80,0,0), plVar3 == (long *)0x0))
  {
    plVar3 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x80,PTR__ZSt7nothrow_02cb9a80);
    if (plVar3 == (long *)0x0) goto code_r0x014b6e38;
  }
  else {
    *plVar3 = (long)(PTR__ZTVN9Framework12CMessageBaseE_02cbb910 + 0x10);
  }
  puVar2 = PTR__ZTV41CFieldMessage_Multiplay_DamageUIParameter_02cb7128;
  *(undefined4 *)(plVar3 + 3) = *(undefined4 *)(param_2 + 0x18);
  lVar6 = *(long *)(param_2 + 0x10);
  lVar5 = *(long *)(param_2 + 8);
  *plVar3 = (long)(puVar2 + 0x10);
  plVar3[2] = lVar6;
  plVar3[1] = lVar5;
  memcpy((long)plVar3 + 0x1c,param_2 + 0x1c,100);
code_r0x014b6e38:
  lVar5 = *(long *)(param_1 + 0x10);
  if (lVar5 != 0) {
    uVar4 = Framework::CMutex::IsInitialized() const(lVar5);
    if ((uVar4 & 1) == 0) {
      Framework::CMutex::Initialize()(lVar5);
    }
    Framework::CMutex::Lock()(lVar5);
  }
  puVar1 = *(undefined8 **)(param_1 + 0x78);
  plStack_28 = plVar3;
  if (puVar1 < *(undefined8 **)(param_1 + 0x80)) {
    if (puVar1 == (undefined8 *)0x0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
    }
    *puVar1 = plVar3;
    *(long *)(param_1 + 0x78) = *(long *)(param_1 + 0x78) + 8;
  }
  else {
    void std::__ndk1::vector<Framework::CMessageBase*, Framework::CSTLAllocator<Framework::CMessageBase*, Framework::CSTLVectorAllocatorInf> >::__push_back_slow_path<Framework::CMessageBase*>(Framework::CMessageBase*&&)(param_1 + 0x70,&plStack_28);
  }
  if (lVar5 != 0) {
    Framework::CMutex::Unlock()(lVar5);
  }
  return;
}

// ==== void Framework::CMessageManager::SendMessage<CFieldMessage_Multiplay_SystemParameter>(CFieldMessage_Multiplay_SystemParameter const&)
// vaddr 0x13b6ec8 | ghidra 0x14b6ec8 | size 352 | symbol _ZN9Framework15CMessageManager11SendMessageI39CFieldMessage_Multiplay_SystemParameterEEvRKT_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework15CMessageManager11SendMessageI39CFieldMessage_Multiplay_SystemParameterEEvRKT_
               (long param_1,long param_2)

{
  undefined8 *puVar1;
  undefined *puVar2;
  long *plVar3;
  ulong uVar4;
  long lVar5;
  long *plStack_28;
  
  if (*(int *)(param_2 + 0x18) != 0) {
    if (*(int *)(param_2 + 0x18) != 1) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027e64e8/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/MessageManager.h"*/,0x9e,&UNK_027e6540/*"Illegal attribute.(%d)"*/);
    }
    (*(code *)PTR__ZN9Framework15CMessageManager17DirectSendMessageERKNS_12CMessageBaseE_02c8fff0)
              (param_1,param_2);
    return;
  }
  if ((*(long *)(param_1 + 0x18) == 0) ||
     (plVar3 = (long *)Framework::CFixedLengthAllocatorContainer::pAllocate(unsigned long, char const*, unsigned int)(*(long *)(param_1 + 0x18),0x28,0,0), plVar3 == (long *)0x0))
  {
    plVar3 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x28,PTR__ZSt7nothrow_02cb9a80);
    if (plVar3 == (long *)0x0) goto code_r0x014b6f98;
  }
  else {
    *plVar3 = (long)(PTR__ZTVN9Framework12CMessageBaseE_02cbb910 + 0x10);
  }
  *(undefined4 *)(plVar3 + 3) = *(undefined4 *)(param_2 + 0x18);
  puVar2 = PTR__ZTV39CFieldMessage_Multiplay_SystemParameter_02cbef88;
  lVar5 = *(long *)(param_2 + 8);
  plVar3[2] = *(long *)(param_2 + 0x10);
  plVar3[1] = lVar5;
  *plVar3 = (long)(puVar2 + 0x10);
  *(undefined4 *)((long)plVar3 + 0x24) = *(undefined4 *)(param_2 + 0x24);
  *(undefined8 *)((long)plVar3 + 0x1c) = *(undefined8 *)(param_2 + 0x1c);
code_r0x014b6f98:
  lVar5 = *(long *)(param_1 + 0x10);
  if (lVar5 != 0) {
    uVar4 = Framework::CMutex::IsInitialized() const(lVar5);
    if ((uVar4 & 1) == 0) {
      Framework::CMutex::Initialize()(lVar5);
    }
    Framework::CMutex::Lock()(lVar5);
  }
  puVar1 = *(undefined8 **)(param_1 + 0x78);
  plStack_28 = plVar3;
  if (puVar1 < *(undefined8 **)(param_1 + 0x80)) {
    if (puVar1 == (undefined8 *)0x0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
    }
    *puVar1 = plVar3;
    *(long *)(param_1 + 0x78) = *(long *)(param_1 + 0x78) + 8;
  }
  else {
    void std::__ndk1::vector<Framework::CMessageBase*, Framework::CSTLAllocator<Framework::CMessageBase*, Framework::CSTLVectorAllocatorInf> >::__push_back_slow_path<Framework::CMessageBase*>(Framework::CMessageBase*&&)(param_1 + 0x70,&plStack_28);
  }
  if (lVar5 != 0) {
    Framework::CMutex::Unlock()(lVar5);
  }
  return;
}

// ==== void Framework::CMessageManager::SendMessage<CFieldMessage_Multiplay_BattleTime>(CFieldMessage_Multiplay_BattleTime const&)
// vaddr 0x13b7028 | ghidra 0x14b7028 | size 340 | symbol _ZN9Framework15CMessageManager11SendMessageI34CFieldMessage_Multiplay_BattleTimeEEvRKT_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework15CMessageManager11SendMessageI34CFieldMessage_Multiplay_BattleTimeEEvRKT_
               (long param_1,long param_2)

{
  undefined8 *puVar1;
  long *plVar2;
  ulong uVar3;
  long lVar4;
  long *plStack_28;
  
  if (*(int *)(param_2 + 0x18) == 0) {
    if (((*(long *)(param_1 + 0x18) != 0) &&
        (plVar2 = (long *)Framework::CFixedLengthAllocatorContainer::pAllocate(unsigned long, char const*, unsigned int)(*(long *)(param_1 + 0x18),0x20,0,0), plVar2 != (long *)0x0
        )) || (plVar2 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x20,PTR__ZSt7nothrow_02cb9a80),
              plVar2 != (long *)0x0)) {
      *plVar2 = (long)(PTR__ZTVN9Framework12CMessageBaseE_02cbb910 + 0x10);
      *(undefined4 *)(plVar2 + 3) = *(undefined4 *)(param_2 + 0x18);
      lVar4 = *(long *)(param_2 + 8);
      plVar2[2] = *(long *)(param_2 + 0x10);
      plVar2[1] = lVar4;
      *plVar2 = (long)(PTR__ZTV34CFieldMessage_Multiplay_BattleTime_02cba130 + 0x10);
      *(undefined4 *)((long)plVar2 + 0x1c) = *(undefined4 *)(param_2 + 0x1c);
    }
    lVar4 = *(long *)(param_1 + 0x10);
    if (lVar4 != 0) {
      uVar3 = Framework::CMutex::IsInitialized() const(lVar4);
      if ((uVar3 & 1) == 0) {
        Framework::CMutex::Initialize()(lVar4);
      }
      Framework::CMutex::Lock()(lVar4);
    }
    puVar1 = *(undefined8 **)(param_1 + 0x78);
    plStack_28 = plVar2;
    if (puVar1 < *(undefined8 **)(param_1 + 0x80)) {
      if (puVar1 == (undefined8 *)0x0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
      }
      *puVar1 = plVar2;
      *(long *)(param_1 + 0x78) = *(long *)(param_1 + 0x78) + 8;
    }
    else {
      void std::__ndk1::vector<Framework::CMessageBase*, Framework::CSTLAllocator<Framework::CMessageBase*, Framework::CSTLVectorAllocatorInf> >::__push_back_slow_path<Framework::CMessageBase*>(Framework::CMessageBase*&&)(param_1 + 0x70,&plStack_28);
    }
    if (lVar4 != 0) {
      Framework::CMutex::Unlock()(lVar4);
    }
    return;
  }
  if (*(int *)(param_2 + 0x18) != 1) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027e64e8/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/MessageManager.h"*/,0x9e,&UNK_027e6540/*"Illegal attribute.(%d)"*/);
  }
  (*(code *)PTR__ZN9Framework15CMessageManager17DirectSendMessageERKNS_12CMessageBaseE_02c8fff0)
            (param_1,param_2);
  return;
}

// ==== void Framework::CMessageManager::SendMessage<CFieldMessage_StartRushCombo>(CFieldMessage_StartRushCombo const&)
// vaddr 0x14ac910 | ghidra 0x15ac910 | size 344 | symbol _ZN9Framework15CMessageManager11SendMessageI28CFieldMessage_StartRushComboEEvRKT_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework15CMessageManager11SendMessageI28CFieldMessage_StartRushComboEEvRKT_
               (long param_1,long param_2)

{
  undefined8 *puVar1;
  undefined *puVar2;
  long *plVar3;
  ulong uVar4;
  long lVar5;
  undefined8 uVar6;
  long *plStack_28;
  
  if (*(int *)(param_2 + 0x18) != 0) {
    if (*(int *)(param_2 + 0x18) != 1) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027e64e8/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/MessageManager.h"*/,0x9e,&UNK_027e6540/*"Illegal attribute.(%d)"*/);
    }
    (*(code *)PTR__ZN9Framework15CMessageManager17DirectSendMessageERKNS_12CMessageBaseE_02c8fff0)
              (param_1,param_2);
    return;
  }
  if ((*(long *)(param_1 + 0x18) == 0) ||
     (plVar3 = (long *)Framework::CFixedLengthAllocatorContainer::pAllocate(unsigned long, char const*, unsigned int)(*(long *)(param_1 + 0x18),0x30,0,0), plVar3 == (long *)0x0))
  {
    plVar3 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x30,PTR__ZSt7nothrow_02cb9a80);
    if (plVar3 == (long *)0x0) goto code_r0x015ac9d8;
  }
  else {
    *plVar3 = (long)(PTR__ZTVN9Framework12CMessageBaseE_02cbb910 + 0x10);
  }
  *(undefined4 *)(plVar3 + 3) = *(undefined4 *)(param_2 + 0x18);
  puVar2 = PTR__ZTV28CFieldMessage_StartRushCombo_02cbb638;
  lVar5 = *(long *)(param_2 + 8);
  plVar3[2] = *(long *)(param_2 + 0x10);
  plVar3[1] = lVar5;
  *plVar3 = (long)(puVar2 + 0x10);
  uVar6 = *(undefined8 *)(param_2 + 0x1c);
  *(undefined8 *)((long)plVar3 + 0x24) = *(undefined8 *)(param_2 + 0x24);
  *(undefined8 *)((long)plVar3 + 0x1c) = uVar6;
code_r0x015ac9d8:
  lVar5 = *(long *)(param_1 + 0x10);
  if (lVar5 != 0) {
    uVar4 = Framework::CMutex::IsInitialized() const(lVar5);
    if ((uVar4 & 1) == 0) {
      Framework::CMutex::Initialize()(lVar5);
    }
    Framework::CMutex::Lock()(lVar5);
  }
  puVar1 = *(undefined8 **)(param_1 + 0x78);
  plStack_28 = plVar3;
  if (puVar1 < *(undefined8 **)(param_1 + 0x80)) {
    if (puVar1 == (undefined8 *)0x0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
    }
    *puVar1 = plVar3;
    *(long *)(param_1 + 0x78) = *(long *)(param_1 + 0x78) + 8;
  }
  else {
    void std::__ndk1::vector<Framework::CMessageBase*, Framework::CSTLAllocator<Framework::CMessageBase*, Framework::CSTLVectorAllocatorInf> >::__push_back_slow_path<Framework::CMessageBase*>(Framework::CMessageBase*&&)(param_1 + 0x70,&plStack_28);
  }
  if (lVar5 != 0) {
    Framework::CMutex::Unlock()(lVar5);
  }
  return;
}

// ==== void Framework::CMessageManager::SendMessage<CFieldMessage_RideTogetherRushCombo>(CFieldMessage_RideTogetherRushCombo const&)
// vaddr 0x14aca68 | ghidra 0x15aca68 | size 340 | symbol _ZN9Framework15CMessageManager11SendMessageI35CFieldMessage_RideTogetherRushComboEEvRKT_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework15CMessageManager11SendMessageI35CFieldMessage_RideTogetherRushComboEEvRKT_
               (long param_1,long param_2)

{
  undefined8 *puVar1;
  long *plVar2;
  ulong uVar3;
  long lVar4;
  long *plStack_28;
  
  if (*(int *)(param_2 + 0x18) == 0) {
    if (((*(long *)(param_1 + 0x18) != 0) &&
        (plVar2 = (long *)Framework::CFixedLengthAllocatorContainer::pAllocate(unsigned long, char const*, unsigned int)(*(long *)(param_1 + 0x18),0x20,0,0), plVar2 != (long *)0x0
        )) || (plVar2 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x20,PTR__ZSt7nothrow_02cb9a80),
              plVar2 != (long *)0x0)) {
      *plVar2 = (long)(PTR__ZTVN9Framework12CMessageBaseE_02cbb910 + 0x10);
      *(undefined4 *)(plVar2 + 3) = *(undefined4 *)(param_2 + 0x18);
      lVar4 = *(long *)(param_2 + 8);
      plVar2[2] = *(long *)(param_2 + 0x10);
      plVar2[1] = lVar4;
      *plVar2 = (long)(PTR__ZTV35CFieldMessage_RideTogetherRushCombo_02cb7fb0 + 0x10);
      *(undefined4 *)((long)plVar2 + 0x1c) = *(undefined4 *)(param_2 + 0x1c);
    }
    lVar4 = *(long *)(param_1 + 0x10);
    if (lVar4 != 0) {
      uVar3 = Framework::CMutex::IsInitialized() const(lVar4);
      if ((uVar3 & 1) == 0) {
        Framework::CMutex::Initialize()(lVar4);
      }
      Framework::CMutex::Lock()(lVar4);
    }
    puVar1 = *(undefined8 **)(param_1 + 0x78);
    plStack_28 = plVar2;
    if (puVar1 < *(undefined8 **)(param_1 + 0x80)) {
      if (puVar1 == (undefined8 *)0x0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
      }
      *puVar1 = plVar2;
      *(long *)(param_1 + 0x78) = *(long *)(param_1 + 0x78) + 8;
    }
    else {
      void std::__ndk1::vector<Framework::CMessageBase*, Framework::CSTLAllocator<Framework::CMessageBase*, Framework::CSTLVectorAllocatorInf> >::__push_back_slow_path<Framework::CMessageBase*>(Framework::CMessageBase*&&)(param_1 + 0x70,&plStack_28);
    }
    if (lVar4 != 0) {
      Framework::CMutex::Unlock()(lVar4);
    }
    return;
  }
  if (*(int *)(param_2 + 0x18) != 1) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027e64e8/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/MessageManager.h"*/,0x9e,&UNK_027e6540/*"Illegal attribute.(%d)"*/);
  }
  (*(code *)PTR__ZN9Framework15CMessageManager17DirectSendMessageERKNS_12CMessageBaseE_02c8fff0)
            (param_1,param_2);
  return;
}

// ==== Framework::CMessageManager::CMessageManager()
// vaddr 0x1e8a69c | ghidra 0x1f8a69c | size 80 | symbol _ZN9Framework15CMessageManagerC2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework15CMessageManagerC1Ev(long *param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZTVN9Framework15CMessageManagerE_02cbaec8;
  *(undefined1 *)(param_1 + 1) = 0;
  param_1[2] = 0;
  *param_1 = (long)(puVar1 + 0x10);
  Framework::CHandleManager_Base::CHandleManager_Base()(param_1 + 4);
  puVar1 = PTR__ZTVN9Framework14THandleManagerINS_16CMessageReceiverEEE_02cc4930;
  param_1[0x10] = 0;
  param_1[0xf] = 0;
  param_1[0xe] = 0;
  param_1[0xd] = 0;
  param_1[4] = (long)(puVar1 + 0x10);
  param_1[0xc] = 0;
  param_1[0xb] = 0;
  return;
}

// ==== Framework::CMessageManager::~CMessageManager()
// vaddr 0x1e8a6ec | ghidra 0x1f8a6ec | size 136 | symbol _ZN9Framework15CMessageManagerD1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework15CMessageManagerD2Ev(long *param_1)

{
  long lVar1;
  long lVar2;
  
  *param_1 = (long)(PTR__ZTVN9Framework15CMessageManagerE_02cbaec8 + 0x10);
  Framework::CMessageManager::Release()();
  lVar1 = param_1[0xe];
  if (lVar1 != 0) {
    lVar2 = param_1[0xf];
    if (lVar2 != lVar1) {
      param_1[0xf] = lVar2 + (~((lVar2 + -8) - lVar1) & 0xfffffffffffffff8U);
    }
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)();
  }
  lVar1 = param_1[0xb];
  if (lVar1 != 0) {
    lVar2 = param_1[0xc];
    if (lVar2 != lVar1) {
      param_1[0xc] = lVar2 + (~((lVar2 + -8) - lVar1) & 0xfffffffffffffff8U);
    }
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)();
  }
  (*(code *)PTR__ZN9Framework19CHandleManager_BaseD1Ev_02cb1720)(param_1 + 4);
  return;
}

// ==== Framework::CMessageManager::Release()
// vaddr 0x1e8a774 | ghidra 0x1f8a774 | size 580 | symbol _ZN9Framework15CMessageManager7ReleaseEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework15CMessageManager7ReleaseEv(long param_1)

{
  long lVar1;
  undefined8 *puVar2;
  ulong uVar3;
  long lVar4;
  long lVar5;
  long lVar6;
  char *pcVar7;
  char *pcVar8;
  char *pcVar9;
  undefined8 uVar10;
  long lVar11;
  
  lVar6 = *(long *)(param_1 + 0x10);
  if (lVar6 != 0) {
    uVar3 = Framework::CMutex::IsInitialized() const(lVar6);
    if ((uVar3 & 1) == 0) {
      Framework::CMutex::Initialize()(lVar6);
    }
    Framework::CMutex::Lock()(lVar6);
  }
  puVar2 = *(undefined8 **)(param_1 + 0x58);
  if (puVar2 != *(undefined8 **)(param_1 + 0x60)) {
    do {
      if (*(long *)(param_1 + 0x18) == 0) {
        (**(code **)(*(long *)*puVar2 + 8))((long *)*puVar2);
      }
      else {
        Framework::CFixedLengthAllocatorContainer::Free(void*)();
      }
    } while (puVar2 != *(undefined8 **)(param_1 + 0x60));
    if (puVar2 != *(undefined8 **)(param_1 + 0x58)) {
      *(ulong *)(param_1 + 0x60) =
           (long)puVar2 +
           (~((long)puVar2 + (-8 - (long)*(undefined8 **)(param_1 + 0x58))) & 0xfffffffffffffff8U);
    }
  }
  puVar2 = *(undefined8 **)(param_1 + 0x70);
  if (puVar2 != *(undefined8 **)(param_1 + 0x78)) {
    do {
      if (*(long *)(param_1 + 0x18) == 0) {
        (**(code **)(*(long *)*puVar2 + 8))((long *)*puVar2);
      }
      else {
        Framework::CFixedLengthAllocatorContainer::Free(void*)();
      }
    } while (puVar2 != *(undefined8 **)(param_1 + 0x78));
    if (puVar2 != *(undefined8 **)(param_1 + 0x70)) {
      *(ulong *)(param_1 + 0x78) =
           (long)puVar2 +
           (~((long)puVar2 + (-8 - (long)*(undefined8 **)(param_1 + 0x70))) & 0xfffffffffffffff8U);
    }
  }
  lVar1 = param_1 + 0x20;
  uVar3 = Framework::CHandleManager_Base::IsInitialized() const(lVar1);
  if ((uVar3 & 1) != 0) {
    lVar4 = Framework::CHandleManager_Base::rElementContainer()(lVar1);
    if (*(int *)(lVar4 + 0x10) != 0) {
      pcVar9 = *(char **)(lVar4 + 0x20);
      lVar11 = *(long *)(lVar4 + 0x28);
      pcVar8 = pcVar9;
      if (lVar11 == 0) {
code_r0x01f8a8ec:
        pcVar9 = pcVar9 + lVar11 * 0x18;
        if (pcVar8 != pcVar9) {
          uVar10 = *(undefined8 *)PTR__ZN9Framework19CHandleManager_Base14iInvalidHandleE_02cc4410;
          do {
            lVar11 = *(long *)(pcVar8 + 0x10);
            if (lVar11 == 0) {
              Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029649b0/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\MessageManager.cpp"*/,0x52,&UNK_02964a45/*"addressReceiver is null."*/);
            }
            *(undefined8 *)(lVar11 + 8) = 0;
            *(undefined8 *)(lVar11 + 0x10) = uVar10;
            pcVar7 = pcVar8;
            do {
              pcVar8 = pcVar9;
              if (pcVar9 == pcVar7) break;
              pcVar8 = pcVar7 + 0x18;
              pcVar7 = pcVar8;
            } while (*pcVar8 != '\x01');
          } while (pcVar8 != (char *)(*(long *)(lVar4 + 0x20) + *(long *)(lVar4 + 0x28) * 0x18));
        }
      }
      else {
        lVar5 = lVar11 * 0x18;
        do {
          if (*pcVar8 == '\x01') goto code_r0x01f8a8ec;
          lVar5 = lVar5 + -0x18;
          pcVar8 = pcVar8 + 0x18;
        } while (lVar5 != 0);
      }
    }
    Framework::CHandleManager_Base::Release()(lVar1);
  }
  *(undefined1 *)(param_1 + 8) = 0;
  if (lVar6 != 0) {
    Framework::CMutex::Unlock()(lVar6);
  }
  if (*(long **)(param_1 + 0x10) != (long *)0x0) {
    (**(code **)(**(long **)(param_1 + 0x10) + 8))();
    *(undefined8 *)(param_1 + 0x10) = 0;
  }
  *(undefined8 *)(param_1 + 0x18) = 0;
  return;
}

// ==== Framework::CMessageManager::~CMessageManager()
// vaddr 0x1e8a9b8 | ghidra 0x1f8a9b8 | size 144 | symbol _ZN9Framework15CMessageManagerD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework15CMessageManagerD0Ev(long *param_1)

{
  long lVar1;
  long lVar2;
  
  *param_1 = (long)(PTR__ZTVN9Framework15CMessageManagerE_02cbaec8 + 0x10);
  Framework::CMessageManager::Release()();
  lVar1 = param_1[0xe];
  if (lVar1 != 0) {
    lVar2 = param_1[0xf];
    if (lVar2 != lVar1) {
      param_1[0xf] = lVar2 + (~((lVar2 + -8) - lVar1) & 0xfffffffffffffff8U);
    }
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)();
  }
  lVar1 = param_1[0xb];
  if (lVar1 != 0) {
    lVar2 = param_1[0xc];
    if (lVar2 != lVar1) {
      param_1[0xc] = lVar2 + (~((lVar2 + -8) - lVar1) & 0xfffffffffffffff8U);
    }
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)();
  }
  Framework::CHandleManager_Base::~CHandleManager_Base()(param_1 + 4);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Framework::CMessageManager::Initialize(bool, unsigned int, unsigned int, unsigned int)
// vaddr 0x1e8aa48 | ghidra 0x1f8aa48 | size 224 | symbol _ZN9Framework15CMessageManager10InitializeEbjjj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework15CMessageManager10InitializeEbjjj
               (long param_1,byte param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5)

{
  long lVar1;
  
  param_2 = param_2 & 1;
  if (*(char *)(param_1 + 8) != '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029649b0/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\MessageManager.cpp"*/,0x22,&UNK_02964a0a/*"m_IsInitialized isn't null.(%08x)"*/);
  }
  Framework::CMessageManager::Release()(param_1);
  Framework::CHandleManager_Base::Initialize(unsigned int, unsigned int, unsigned int)(param_1 + 0x20,param_3,param_4,param_5);
  *(byte *)(param_1 + 9) = param_2;
  if (*(long *)(param_1 + 0x10) != 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029649b0/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\MessageManager.cpp"*/,0x29,&UNK_02963d3d/*"m_pMutex isn't null.(%08x)"*/);
    param_2 = *(byte *)(param_1 + 9);
  }
  if (param_2 != 0) {
    lVar1 = operator new(unsigned long, std::nothrow_t const&)(0xb0,PTR__ZSt7nothrow_02cb9a80);
    if (lVar1 != 0) {
      Framework::CMutex::CMutex()(lVar1);
    }
    *(long *)(param_1 + 0x10) = lVar1;
    Framework::CMutex::Initialize()(lVar1);
    Framework::CHandleManager_Base::EnableMutex()(param_1 + 0x20);
  }
  *(undefined1 *)(param_1 + 8) = 1;
  return;
}

// ==== Framework::CMessageManager::AttachFixedMemoryAllocator(Framework::CFixedLengthAllocatorContainer&)
// vaddr 0x1e8ab28 | ghidra 0x1f8ab28 | size 64 | symbol _ZN9Framework15CMessageManager26AttachFixedMemoryAllocatorERNS_30CFixedLengthAllocatorContainerE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework15CMessageManager26AttachFixedMemoryAllocatorERNS_30CFixedLengthAllocatorContainerE
               (long param_1,undefined8 param_2)

{
  if (*(char *)(param_1 + 8) == '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029649b0/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\MessageManager.cpp"*/,0x39,&UNK_02964a2c/*"m_IsInitialized is null."*/);
  }
  *(undefined8 *)(param_1 + 0x18) = param_2;
  return;
}

// ==== Framework::CMessageManager::DeleteMessage(Framework::CMessageBase&)
// vaddr 0x1e8ab68 | ghidra 0x1f8ab68 | size 28 | symbol _ZN9Framework15CMessageManager13DeleteMessageERNS_12CMessageBaseE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework15CMessageManager13DeleteMessageERNS_12CMessageBaseE(long param_1,long *param_2)

{
  if (*(long *)(param_1 + 0x18) != 0) {
    (*(code *)PTR__ZN9Framework30CFixedLengthAllocatorContainer4FreeEPv_02c90330)();
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x01f8ab80. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*param_2 + 8))(param_2);
  return;
}

// ==== Framework::CMessageManager::NumSendMessage() const
// vaddr 0x1e8ab84 | ghidra 0x1f8ab84 | size 52 | symbol _ZNK9Framework15CMessageManager14NumSendMessageEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK9Framework15CMessageManager14NumSendMessageEv(long param_1)

{
  if (*(char *)(param_1 + 8) == '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029649b0/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\MessageManager.cpp"*/,0x70,&UNK_02964a2c/*"m_IsInitialized is null."*/);
  }
  return *(undefined4 *)(param_1 + 0x88);
}

// ==== Framework::CMessageManager::AddReceiver(Framework::CMessageReceiver&)
// vaddr 0x1e8abb8 | ghidra 0x1f8abb8 | size 196 | symbol _ZN9Framework15CMessageManager11AddReceiverERNS_16CMessageReceiverE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework15CMessageManager11AddReceiverERNS_16CMessageReceiverE(long param_1,long param_2)

{
  ulong uVar1;
  long lVar2;
  long lVar3;
  long lVar4;
  
  lVar3 = *(long *)(param_1 + 0x10);
  if (lVar3 != 0) {
    uVar1 = Framework::CMutex::IsInitialized() const(lVar3);
    if ((uVar1 & 1) == 0) {
      Framework::CMutex::Initialize()(lVar3);
    }
    Framework::CMutex::Lock()(lVar3);
  }
  lVar2 = Framework::CHandleManager_Base::Register(unsigned long)(param_1 + 0x20,param_2);
  lVar4 = *(long *)PTR__ZN9Framework19CHandleManager_Base14iInvalidHandleE_02cc4410;
  if (lVar2 == lVar4) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964ae3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/HandleManager.h"*/,0x15b,&UNK_02964b3a/*"Handle register failed."*/);
  }
  if (*(long *)(param_2 + 0x10) != lVar4) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964a70/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/MessageReceiver.h"*/,0x4f,&UNK_02964ac9/*"Already has handle.(%08x)"*/);
  }
  *(long *)(param_2 + 8) = param_1;
  *(long *)(param_2 + 0x10) = lVar2;
  if (lVar3 != 0) {
    (*(code *)PTR__ZN9Framework6CMutex6UnlockEv_02cb3f98)(lVar3);
    return;
  }
  return;
}

// ==== Framework::CMessageManager::AddReceiver(Framework::CMessageReceiver&, unsigned int)
// vaddr 0x1e8ac7c | ghidra 0x1f8ac7c | size 204 | symbol _ZN9Framework15CMessageManager11AddReceiverERNS_16CMessageReceiverEj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework15CMessageManager11AddReceiverERNS_16CMessageReceiverEj
               (long param_1,long param_2,undefined4 param_3)

{
  ulong uVar1;
  long lVar2;
  long lVar3;
  long lVar4;
  
  lVar3 = *(long *)(param_1 + 0x10);
  if (lVar3 != 0) {
    uVar1 = Framework::CMutex::IsInitialized() const(lVar3);
    if ((uVar1 & 1) == 0) {
      Framework::CMutex::Initialize()(lVar3);
    }
    Framework::CMutex::Lock()(lVar3);
  }
  lVar2 = Framework::CHandleManager_Base::RegisterToReserve(unsigned long, unsigned int)(param_1 + 0x20,param_2,param_3);
  lVar4 = *(long *)PTR__ZN9Framework19CHandleManager_Base14iInvalidHandleE_02cc4410;
  if (lVar2 == lVar4) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964ae3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/HandleManager.h"*/,0x172,&UNK_02964b3a/*"Handle register failed."*/);
  }
  if (*(long *)(param_2 + 0x10) != lVar4) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964a70/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/MessageReceiver.h"*/,0x4f,&UNK_02964ac9/*"Already has handle.(%08x)"*/);
  }
  *(long *)(param_2 + 8) = param_1;
  *(long *)(param_2 + 0x10) = lVar2;
  if (lVar3 != 0) {
    (*(code *)PTR__ZN9Framework6CMutex6UnlockEv_02cb3f98)(lVar3);
    return;
  }
  return;
}

// ==== Framework::CMessageManager::RemoveReceiver(Framework::CMessageReceiver&)
// vaddr 0x1e8ad48 | ghidra 0x1f8ad48 | size 180 | symbol _ZN9Framework15CMessageManager14RemoveReceiverERNS_16CMessageReceiverE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework15CMessageManager14RemoveReceiverERNS_16CMessageReceiverE
               (long param_1,long param_2)

{
  ulong uVar1;
  long lVar2;
  long lVar3;
  long lVar4;
  
  lVar2 = *(long *)(param_1 + 0x10);
  if (lVar2 != 0) {
    uVar1 = Framework::CMutex::IsInitialized() const(lVar2);
    if ((uVar1 & 1) == 0) {
      Framework::CMutex::Initialize()(lVar2);
    }
    Framework::CMutex::Lock()(lVar2);
  }
  lVar3 = *(long *)(param_2 + 0x10);
  lVar4 = *(long *)PTR__ZN9Framework19CHandleManager_Base14iInvalidHandleE_02cc4410;
  if (lVar3 != lVar4) {
    uVar1 = Framework::CHandleManager_Base::IsIssuedHandle(unsigned long) const(param_1 + 0x20,lVar3);
    if ((uVar1 & 1) == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029649b0/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\MessageManager.cpp"*/,0x8e,&UNK_02964a5e/*"Illegal receiver."*/);
    }
    Framework::CHandleManager_Base::Unregister(unsigned long)(param_1 + 0x20,lVar3);
    *(undefined8 *)(param_2 + 8) = 0;
    *(long *)(param_2 + 0x10) = lVar4;
  }
  if (lVar2 != 0) {
    (*(code *)PTR__ZN9Framework6CMutex6UnlockEv_02cb3f98)(lVar2);
    return;
  }
  return;
}

// ==== Framework::CMessageManager::Deliver()
// vaddr 0x1e8adfc | ghidra 0x1f8adfc | size 308 | symbol _ZN9Framework15CMessageManager7DeliverEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework15CMessageManager7DeliverEv(long param_1)

{
  long lVar1;
  undefined8 uVar2;
  long lVar3;
  ulong uVar4;
  undefined8 *puVar5;
  long lVar6;
  long *plVar7;
  undefined8 *puVar8;
  
  if (*(char *)(param_1 + 8) == '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029649b0/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\MessageManager.cpp"*/,0x9d,&UNK_02964a2c/*"m_IsInitialized is null."*/);
  }
  lVar6 = *(long *)(param_1 + 0x10);
  *(undefined4 *)(param_1 + 0x88) = 0;
  if (lVar6 != 0) {
    uVar4 = Framework::CMutex::IsInitialized() const(lVar6);
    if ((uVar4 & 1) == 0) {
      Framework::CMutex::Initialize()(lVar6);
    }
    Framework::CMutex::Lock()(lVar6);
  }
  lVar1 = *(long *)(param_1 + 0x58);
  lVar3 = *(long *)(param_1 + 0x60);
  uVar2 = *(undefined8 *)(param_1 + 0x68);
  puVar5 = *(undefined8 **)(param_1 + 0x70);
  puVar8 = *(undefined8 **)(param_1 + 0x78);
  *(undefined8 **)(param_1 + 0x58) = puVar5;
  *(long *)(param_1 + 0x70) = lVar1;
  *(long *)(param_1 + 0x78) = lVar3;
  *(undefined8 *)(param_1 + 0x68) = *(undefined8 *)(param_1 + 0x80);
  *(undefined8 **)(param_1 + 0x60) = puVar8;
  *(undefined8 *)(param_1 + 0x80) = uVar2;
  if (lVar3 != lVar1) {
    *(ulong *)(param_1 + 0x78) = lVar3 + (~((lVar3 + -8) - lVar1) & 0xfffffffffffffff8U);
  }
  if (lVar6 == 0) {
    if (puVar5 == puVar8) goto code_r0x01f8af04;
  }
  else {
    Framework::CMutex::Unlock()(lVar6);
    puVar5 = *(undefined8 **)(param_1 + 0x58);
    puVar8 = *(undefined8 **)(param_1 + 0x60);
    if (puVar5 == puVar8) goto code_r0x01f8af04;
  }
  do {
    plVar7 = (long *)*puVar5;
    Framework::CMessageManager::DirectSendMessage(Framework::CMessageBase const&)(param_1,plVar7);
    if (*(long *)(param_1 + 0x18) == 0) {
      (**(code **)(*plVar7 + 8))(plVar7);
    }
    else {
      Framework::CFixedLengthAllocatorContainer::Free(void*)(*(long *)(param_1 + 0x18),plVar7);
    }
    puVar8 = puVar5 + 1;
    puVar5 = puVar8;
  } while (puVar8 != *(undefined8 **)(param_1 + 0x60));
  puVar5 = *(undefined8 **)(param_1 + 0x58);
code_r0x01f8af04:
  if (puVar8 != puVar5) {
    *(ulong *)(param_1 + 0x60) =
         (long)puVar8 + (~((long)puVar8 + (-8 - (long)puVar5)) & 0xfffffffffffffff8U);
  }
  return;
}

// ==== Framework::CMessageManager::DirectSendMessage(Framework::CMessageBase const&)
// vaddr 0x1e8af30 | ghidra 0x1f8af30 | size 1692 | symbol _ZN9Framework15CMessageManager17DirectSendMessageERKNS_12CMessageBaseE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework15CMessageManager17DirectSendMessageERKNS_12CMessageBaseE
               (long param_1,long param_2)

{
  long lVar1;
  undefined8 *puVar2;
  undefined4 *puVar3;
  int iVar4;
  long lVar5;
  undefined8 *puVar6;
  ulong uVar7;
  uint *puVar8;
  long lVar9;
  long lVar10;
  char *pcVar11;
  undefined8 *puVar12;
  long lVar13;
  undefined4 *puVar14;
  ulong uVar15;
  uint *puVar16;
  long *plVar17;
  long *plVar18;
  long *plVar20;
  long *plVar21;
  long *plVar22;
  char *pcVar23;
  char *pcVar24;
  long *plStack_a8;
  undefined8 uStack_88;
  long lStack_80;
  undefined8 *puStack_78;
  undefined8 *puStack_70;
  undefined8 *puStack_68;
  long *plVar19;
  
  lVar1 = param_1 + 0x20;
  lVar5 = Framework::CHandleManager_Base::rElementContainer()(lVar1);
  if (*(int *)(lVar5 + 0x10) != 0) {
    pcVar11 = *(char **)(lVar5 + 0x20);
    lVar9 = *(long *)(lVar5 + 0x28);
    pcVar24 = pcVar11;
    if (lVar9 == 0) {
code_r0x01f8afa4:
      pcVar11 = pcVar11 + lVar9 * 0x18;
      if (pcVar24 != pcVar11) {
        plVar20 = (long *)0x0;
        plVar21 = (long *)0x0;
        plStack_a8 = (long *)0x0;
        do {
          lVar9 = *(long *)(pcVar24 + 0x10);
          if (lVar9 == 0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029649b0/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\MessageManager.cpp"*/,0xcd,&UNK_02964a45/*"addressReceiver is null."*/);
          }
          puStack_70 = (undefined8 *)0x0;
          puStack_68 = (undefined8 *)0x0;
          puStack_78 = (undefined8 *)0x0;
          puVar3 = *(undefined4 **)(lVar9 + 0x18);
          lStack_80 = lVar9;
          if (*(undefined4 **)(lVar9 + 0x20) != *(undefined4 **)(lVar9 + 0x18)) {
            do {
              puVar6 = puStack_70;
              puVar14 = puVar3 + 1;
              uStack_88 = CONCAT44(*puVar3,*puVar3);
              if (puStack_70 == puStack_68) {
                void std::__ndk1::vector<Framework::CMessageBase::tIDRange, Framework::CSTLAllocator<Framework::CMessageBase::tIDRange, Framework::CSTLVectorAllocatorInf> >::__push_back_slow_path<Framework::CMessageBase::tIDRange const&>(Framework::CMessageBase::tIDRange const&)(&puStack_78,&uStack_88);
              }
              else {
                if (puStack_70 == (undefined8 *)0x0) {
                  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296188c/*"C:\BAS_Submission\Client\Library\Framework\Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
                }
                *puVar6 = uStack_88;
                puStack_70 = puStack_70 + 1;
              }
              puVar3 = puVar14;
            } while (puVar14 != *(undefined4 **)(lVar9 + 0x20));
          }
          puVar6 = *(undefined8 **)(lVar9 + 0x30);
          if (*(undefined8 **)(lVar9 + 0x38) != puVar6) {
            do {
              puVar12 = puStack_70;
              if (puStack_70 == puStack_68) {
                void std::__ndk1::vector<Framework::CMessageBase::tIDRange, Framework::CSTLAllocator<Framework::CMessageBase::tIDRange, Framework::CSTLVectorAllocatorInf> >::__push_back_slow_path<Framework::CMessageBase::tIDRange const&>(Framework::CMessageBase::tIDRange const&)(&puStack_78,puVar6);
              }
              else {
                if (puStack_70 == (undefined8 *)0x0) {
                  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296188c/*"C:\BAS_Submission\Client\Library\Framework\Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
                }
                *puVar12 = *puVar6;
                puStack_70 = puStack_70 + 1;
              }
              puVar6 = puVar6 + 1;
            } while (puVar6 != *(undefined8 **)(lVar9 + 0x38));
          }
          if (puStack_78 != puStack_70) {
            if (plVar20 == plStack_a8) {
              lVar9 = (long)plVar20 - (long)plVar21 >> 5;
              if ((ulong)((long)plStack_a8 - (long)plVar21 >> 5) < 0x3ffffffffffffff) {
                uVar7 = (long)plStack_a8 - (long)plVar21 >> 4;
                uVar15 = lVar9 + 1U;
                if (lVar9 + 1U <= uVar7) {
                  uVar15 = uVar7;
                }
                if (uVar15 != 0) goto code_r0x01f8b1f8;
                lVar10 = 0;
              }
              else {
                uVar15 = 0x7ffffffffffffff;
code_r0x01f8b1f8:
                lVar10 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar15 << 5,&UNK_02962054/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/STL_Vector.h"*/,0x20);
                if (lVar10 == 0) {
                  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296188c/*"C:\BAS_Submission\Client\Library\Framework\Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
                }
              }
              plVar22 = (long *)(lVar10 + lVar9 * 0x20);
              if (plVar22 == (long *)0x0) {
                Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296188c/*"C:\BAS_Submission\Client\Library\Framework\Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
              }
              *plVar22 = lStack_80;
              plVar22[1] = 0;
              plVar22[2] = 0;
              plVar22[3] = 0;
              lVar13 = (long)puStack_70 - (long)puStack_78 >> 3;
              if (lVar13 != 0) {
                puVar6 = (undefined8 *)
                         Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)((long)puStack_70 - (long)puStack_78,&UNK_02962054/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/STL_Vector.h"*/,0x20);
                if (puVar6 == (undefined8 *)0x0) {
                  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296188c/*"C:\BAS_Submission\Client\Library\Framework\Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
                }
                puVar2 = puStack_70;
                lVar9 = lVar10 + lVar9 * 0x20;
                plVar17 = (long *)(lVar9 + 0x10);
                *plVar17 = (long)puVar6;
                plVar22[1] = (long)puVar6;
                *(undefined8 **)(lVar9 + 0x18) = puVar6 + lVar13;
                for (puVar12 = puStack_78; puVar12 != puVar2; puVar12 = puVar12 + 1) {
                  if (puVar6 == (undefined8 *)0x0) {
                    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296188c/*"C:\BAS_Submission\Client\Library\Framework\Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
                  }
                  *puVar6 = *puVar12;
                  puVar6 = (undefined8 *)(*plVar17 + 8);
                  *plVar17 = (long)puVar6;
                }
              }
              plStack_a8 = (long *)(lVar10 + uVar15 * 0x20);
              plVar17 = plVar22;
              plVar18 = plVar20;
              if (plVar20 != plVar21) {
                do {
                  plVar19 = plVar18 + -4;
                  lVar9 = *plVar19;
                  plVar17[-2] = 0;
                  plVar17[-1] = 0;
                  plVar17[-4] = lVar9;
                  plVar17[-3] = 0;
                  lVar9 = plVar18[-2] - plVar18[-3] >> 3;
                  if (lVar9 != 0) {
                    puVar6 = (undefined8 *)
                             Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(plVar18[-2] - plVar18[-3],&UNK_02962054/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/STL_Vector.h"*/,0x20);
                    if (puVar6 == (undefined8 *)0x0) {
                      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296188c/*"C:\BAS_Submission\Client\Library\Framework\Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
                    }
                    plVar17[-3] = (long)puVar6;
                    plVar17[-2] = (long)puVar6;
                    plVar17[-1] = (long)(puVar6 + lVar9);
                    puVar2 = (undefined8 *)plVar18[-2];
                    for (puVar12 = (undefined8 *)plVar18[-3]; puVar12 != puVar2;
                        puVar12 = puVar12 + 1) {
                      if (puVar6 == (undefined8 *)0x0) {
                        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296188c/*"C:\BAS_Submission\Client\Library\Framework\Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
                      }
                      *puVar6 = *puVar12;
                      puVar6 = (undefined8 *)(plVar17[-2] + 8);
                      plVar17[-2] = (long)puVar6;
                    }
                  }
                  plVar17 = plVar17 + -4;
                  plVar18 = plVar19;
                } while (plVar19 != plVar21);
                do {
                  lVar9 = plVar20[-3];
                  plVar18 = plVar20 + -4;
                  if (lVar9 != 0) {
                    lVar10 = plVar20[-2];
                    if (lVar10 != lVar9) {
                      plVar20[-2] = lVar10 + (~((lVar10 + -8) - lVar9) & 0xfffffffffffffff8U);
                    }
                    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)();
                  }
                  plVar20 = plVar18;
                } while (plVar21 != plVar18);
              }
              plVar20 = plVar22;
              if (plVar21 != (long *)0x0) {
                Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar21);
              }
            }
            else {
              if (plVar20 == (long *)0x0) {
                Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296188c/*"C:\BAS_Submission\Client\Library\Framework\Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
              }
              plVar20[2] = 0;
              plVar20[3] = 0;
              *plVar20 = lStack_80;
              plVar20[1] = 0;
              lVar9 = (long)puStack_70 - (long)puStack_78 >> 3;
              plVar17 = plVar21;
              if (lVar9 != 0) {
                puVar6 = (undefined8 *)
                         Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)((long)puStack_70 - (long)puStack_78,&UNK_02962054/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/STL_Vector.h"*/,0x20);
                if (puVar6 == (undefined8 *)0x0) {
                  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296188c/*"C:\BAS_Submission\Client\Library\Framework\Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
                }
                puVar2 = puStack_70;
                plVar20[1] = (long)puVar6;
                plVar20[2] = (long)puVar6;
                plVar20[3] = (long)(puVar6 + lVar9);
                for (puVar12 = puStack_78; puVar12 != puVar2; puVar12 = puVar12 + 1) {
                  if (puVar6 == (undefined8 *)0x0) {
                    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296188c/*"C:\BAS_Submission\Client\Library\Framework\Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
                  }
                  *puVar6 = *puVar12;
                  puVar6 = (undefined8 *)(plVar20[2] + 8);
                  plVar20[2] = (long)puVar6;
                }
              }
            }
            plVar20 = plVar20 + 4;
            plVar21 = plVar17;
          }
          pcVar23 = pcVar24;
          if (puStack_78 != (undefined8 *)0x0) {
            if (puStack_70 != puStack_78) {
              puStack_70 = (undefined8 *)
                           ((long)puStack_70 +
                           (~((long)puStack_70 + (-8 - (long)puStack_78)) & 0xfffffffffffffff8U));
            }
            Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)();
          }
          do {
            pcVar24 = pcVar11;
            if (pcVar11 == pcVar23) break;
            pcVar24 = pcVar23 + 0x18;
            pcVar23 = pcVar24;
          } while (*pcVar24 != '\x01');
          plVar22 = plVar21;
        } while (pcVar24 != (char *)(*(long *)(lVar5 + 0x20) + *(long *)(lVar5 + 0x28) * 0x18));
        goto joined_r0x01f8b48c;
      }
    }
    else {
      lVar10 = lVar9 * 0x18;
      do {
        if (*pcVar24 == '\x01') goto code_r0x01f8afa4;
        lVar10 = lVar10 + -0x18;
        pcVar24 = pcVar24 + 0x18;
      } while (lVar10 != 0);
    }
  }
  plVar21 = (long *)0x0;
  plVar20 = (long *)0x0;
  plVar22 = plVar21;
joined_r0x01f8b48c:
  for (; plVar21 != plVar20; plVar21 = plVar21 + 4) {
    puVar16 = (uint *)plVar21[1];
    puVar8 = (uint *)plVar21[2];
    if (puVar16 != puVar8) {
      do {
        if ((*puVar16 <= *(uint *)(param_2 + 8)) && (*(uint *)(param_2 + 8) <= puVar16[1])) {
          (**(code **)(*(long *)*plVar21 + 0x10))((long *)*plVar21,param_2);
          *(int *)(param_1 + 0x88) = *(int *)(param_1 + 0x88) + 1;
          puVar8 = (uint *)plVar21[2];
        }
        puVar16 = puVar16 + 2;
      } while (puVar16 != puVar8);
    }
  }
  if (plVar22 != (long *)0x0) {
    while (plVar21 = plVar20, plVar22 != plVar21) {
      lVar5 = plVar21[-3];
      plVar20 = plVar21 + -4;
      if (lVar5 != 0) {
        lVar9 = plVar21[-2];
        if (lVar9 != lVar5) {
          plVar21[-2] = lVar9 + (~((lVar9 + -8) - lVar5) & 0xfffffffffffffff8U);
        }
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)();
      }
    }
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar22);
  }
  uVar15 = *(ulong *)(param_2 + 0x10);
  iVar4 = Framework::CHandleManager_Base::UnmountAdditionalInformation(unsigned long)(uVar15);
  if (iVar4 == 0) {
    uVar15 = Framework::CHandleManager_Base::MountAdditionalInformationBySelf(unsigned int) const(lVar1,uVar15 & 0xffffffff);
  }
  plVar21 = (long *)Framework::CHandleManager_Base::Refer(unsigned long) const(lVar1,uVar15);
  if (plVar21 != (long *)0x0) {
    (**(code **)(*plVar21 + 0x10))(plVar21,param_2);
    *(int *)(param_1 + 0x88) = *(int *)(param_1 + 0x88) + 1;
  }
  return;
}

// ==== Framework::CMessageManager::ReportS()
// vaddr 0x1e8b5cc | ghidra 0x1f8b5cc | size 72 | symbol _ZN9Framework15CMessageManager7ReportSEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework15CMessageManager7ReportSEv(long param_1)

{
  long lVar1;
  
  if (*(char *)(param_1 + 8) == '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029649b0/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\MessageManager.cpp"*/,0x122,&UNK_02964a2c/*"m_IsInitialized is null."*/);
    lVar1 = *(long *)(param_1 + 0x18);
  }
  else {
    lVar1 = *(long *)(param_1 + 0x18);
  }
  if (lVar1 != 0) {
    (*(code *)PTR__ZN9Framework30CFixedLengthAllocatorContainer7ReportSEv_02c90d28)();
    return;
  }
  return;
}

// ==== Framework::ResponderChain::CResponder::CResponder()
// vaddr 0x1e97058 | ghidra 0x1f97058 | size 116 | symbol _ZN9Framework14ResponderChain10CResponderC2Ev | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Removing unreachable block (ram,0x01f9707c) */
/* WARNING: Removing unreachable block (ram,0x01f970ac) */
/* WARNING: Removing unreachable block (ram,0x01f9708c) */
/* WARNING: Removing unreachable block (ram,0x01f970b0) */

void _ZN9Framework14ResponderChain10CResponderC1Ev(long *param_1)

{
  undefined *puVar1;
  
  param_1[2] = 0;
  puVar1 = PTR__ZTVN9Framework14ResponderChain10CResponderE_02cc2a70;
  param_1[4] = 0;
  *param_1 = (long)(puVar1 + 0x10);
  param_1[1] = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  *(undefined4 *)((long)param_1 + 0x1c) = 0;
  *(undefined1 *)((long)param_1 + 0x19) = 1;
  return;
}

// ==== Framework::ResponderChain::CResponder::Attach(Framework::ResponderChain::CResponder*)
// vaddr 0x1e970cc | ghidra 0x1f970cc | size 172 | symbol _ZN9Framework14ResponderChain10CResponder6AttachEPS1_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework14ResponderChain10CResponder6AttachEPS1_(long param_1,long param_2)

{
  if ((*(long *)(param_1 + 8) == 0) && (*(long *)(param_1 + 0x10) == 0)) {
    *(long *)(param_1 + 8) = param_2;
    *(undefined8 *)(param_1 + 0x10) = *(undefined8 *)(param_2 + 0x10);
    if (*(long *)(param_2 + 0x10) != 0) {
      *(long *)(*(long *)(param_2 + 0x10) + 8) = param_1;
    }
    *(long *)(param_2 + 0x10) = param_1;
  }
  else {
    if (*(long *)(param_2 + 8) != 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02963548/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TChain.h"*/,0x52,&UNK_02963598/*"Target has already m_pPrevious."*/);
    }
    if (*(long *)(param_2 + 0x10) != 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02963548/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TChain.h"*/,0x53,&UNK_029635b8/*"Target has already m_pNext."*/);
    }
    *(long *)(param_2 + 0x10) = param_1;
    *(undefined8 *)(param_2 + 8) = *(undefined8 *)(param_1 + 8);
    if (*(long *)(param_1 + 8) != 0) {
      *(long *)(*(long *)(param_1 + 8) + 0x10) = param_2;
    }
    *(long *)(param_1 + 8) = param_2;
  }
  *(undefined1 *)(param_1 + 0x18) = 0;
  return;
}

// ==== Framework::ResponderChain::CResponder::AccessAuthority() const
// vaddr 0x1e97178 | ghidra 0x1f97178 | size 60 | symbol _ZNK9Framework14ResponderChain10CResponder15AccessAuthorityEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK9Framework14ResponderChain10CResponder15AccessAuthorityEv(long param_1)

{
  if ((*(long *)(param_1 + 8) == 0) && (*(long *)(param_1 + 0x10) == 0)) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965b0f/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResponderChain.cpp"*/,0x26,&UNK_02965b69/*"pPrevious() || pNext() is null."*/);
  }
  return param_1 + 0x20;
}

// ==== Framework::ResponderChain::CResponder::Demand()
// vaddr 0x1e971b4 | ghidra 0x1f971b4 | size 64 | symbol _ZN9Framework14ResponderChain10CResponder6DemandEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework14ResponderChain10CResponder6DemandEv(long param_1)

{
  if ((*(long *)(param_1 + 8) == 0) && (*(long *)(param_1 + 0x10) == 0)) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965b0f/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResponderChain.cpp"*/,0x31,&UNK_02965b69/*"pPrevious() || pNext() is null."*/);
  }
  *(undefined1 *)(param_1 + 0x18) = 1;
  return;
}

// ==== Framework::ResponderChain::CResponder::Progress(Framework::ResponderChain::CAccessAuthority&)
// vaddr 0x1e971f4 | ghidra 0x1f971f4 | size 116 | symbol _ZN9Framework14ResponderChain10CResponder8ProgressERNS0_16CAccessAuthorityE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework14ResponderChain10CResponder8ProgressERNS0_16CAccessAuthorityE
               (long param_1,undefined8 *param_2)

{
  undefined8 *puVar1;
  
  if ((*(long *)(param_1 + 8) == 0) && (*(long *)(param_1 + 0x10) == 0)) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965b0f/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResponderChain.cpp"*/,0x3c,&UNK_02965b69/*"pPrevious() || pNext() is null."*/);
  }
  puVar1 = (undefined8 *)(param_1 + 0x20);
  if (*(char *)(param_1 + 0x18) != '\0') {
    *(undefined8 *)(param_1 + 0x20) = *param_2;
    puVar1 = param_2;
  }
  *puVar1 = 0;
  if (*(long *)(param_1 + 0x10) != 0) {
    _ZN9Framework14ResponderChain10CResponder8ProgressERNS0_16CAccessAuthorityE
              (*(long *)(param_1 + 0x10),param_2);
  }
  *(undefined1 *)(param_1 + 0x18) = 0;
  return;
}

// ==== Framework::ResponderChain::CManager::CManager()
// vaddr 0x1e97268 | ghidra 0x1f97268 | size 60 | symbol _ZN9Framework14ResponderChain8CManagerC1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework14ResponderChain8CManagerC2Ev(undefined1 *param_1)

{
  undefined *puVar1;
  
  *param_1 = 0;
  puVar1 = PTR__ZTVN9Framework14ResponderChain10CResponderE_02cc2a70;
  *(undefined4 *)(param_1 + 0x24) = 0;
  *(undefined8 *)(param_1 + 0x10) = 0;
  *(undefined8 *)(param_1 + 0x18) = 0;
  *(undefined8 *)(param_1 + 0x50) = 0;
  *(undefined4 *)(param_1 + 0x4c) = 0;
  *(undefined8 *)(param_1 + 0x38) = 0;
  *(undefined8 *)(param_1 + 0x40) = 0;
  param_1[0x21] = 1;
  *(undefined **)(param_1 + 8) = puVar1 + 0x10;
  *(undefined8 *)(param_1 + 0x28) = 0;
  *(undefined **)(param_1 + 0x30) = puVar1 + 0x10;
  param_1[0x49] = 1;
  return;
}

// ==== Framework::ResponderChain::CManager::~CManager()
// vaddr 0x1e972a4 | ghidra 0x1f972a4 | size 340 | symbol _ZN9Framework14ResponderChain8CManagerD1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework14ResponderChain8CManagerD2Ev(long param_1)

{
  undefined *puVar1;
  long lVar2;
  long *plVar3;
  
  Framework::ResponderChain::CManager::Release()();
  puVar1 = PTR__ZTVN9Framework6TChainINS_14ResponderChain10CResponderEEE_02cbd2d8;
  plVar3 = (long *)(param_1 + 0x30);
  *plVar3 = (long)(PTR__ZTVN9Framework6TChainINS_14ResponderChain10CResponderEEE_02cbd2d8 + 0x10);
  lVar2 = *(long *)(param_1 + 0x38);
  if (lVar2 == 0) {
    lVar2 = *(long *)(param_1 + 0x40);
  }
  else {
    if (*(long **)(lVar2 + 0x10) != plVar3) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02963548/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TChain.h"*/,0x31,&UNK_029635d4/*"Previous hasn't myself."*/);
      lVar2 = *(long *)(param_1 + 0x38);
    }
    *(long *)(lVar2 + 0x10) = *(long *)(param_1 + 0x40);
    lVar2 = *(long *)(param_1 + 0x40);
  }
  if (lVar2 != 0) {
    if (*(long **)(lVar2 + 8) != plVar3) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02963548/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TChain.h"*/,0x36,&UNK_029635ec/*"Next hasn't myself."*/);
      lVar2 = *(long *)(param_1 + 0x40);
    }
    *(undefined8 *)(lVar2 + 8) = *(undefined8 *)(param_1 + 0x38);
  }
  plVar3 = (long *)(param_1 + 8);
  *plVar3 = (long)(puVar1 + 0x10);
  lVar2 = *(long *)(param_1 + 0x10);
  *(undefined8 *)(param_1 + 0x38) = 0;
  *(undefined8 *)(param_1 + 0x40) = 0;
  if (lVar2 == 0) {
    lVar2 = *(long *)(param_1 + 0x18);
  }
  else {
    if (*(long **)(lVar2 + 0x10) != plVar3) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02963548/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TChain.h"*/,0x31,&UNK_029635d4/*"Previous hasn't myself."*/);
      lVar2 = *(long *)(param_1 + 0x10);
    }
    *(long *)(lVar2 + 0x10) = *(long *)(param_1 + 0x18);
    lVar2 = *(long *)(param_1 + 0x18);
  }
  if (lVar2 != 0) {
    if (*(long **)(lVar2 + 8) != plVar3) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02963548/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TChain.h"*/,0x36,&UNK_029635ec/*"Next hasn't myself."*/);
      lVar2 = *(long *)(param_1 + 0x18);
    }
    *(undefined8 *)(lVar2 + 8) = *(undefined8 *)(param_1 + 0x10);
  }
  *(undefined8 *)(param_1 + 0x10) = 0;
  *(undefined8 *)(param_1 + 0x18) = 0;
  return;
}

// ==== Framework::ResponderChain::CManager::Release()
// vaddr 0x1e973f8 | ghidra 0x1f973f8 | size 308 | symbol _ZN9Framework14ResponderChain8CManager7ReleaseEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework14ResponderChain8CManager7ReleaseEv(undefined1 *param_1)

{
  long lVar1;
  
  lVar1 = *(long *)(param_1 + 0x10);
  if (lVar1 == 0) {
    lVar1 = *(long *)(param_1 + 0x18);
  }
  else {
    if (*(undefined1 **)(lVar1 + 0x10) != param_1 + 8) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02963548/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TChain.h"*/,0x31,&UNK_029635d4/*"Previous hasn't myself."*/);
      lVar1 = *(long *)(param_1 + 0x10);
    }
    *(long *)(lVar1 + 0x10) = *(long *)(param_1 + 0x18);
    lVar1 = *(long *)(param_1 + 0x18);
  }
  if (lVar1 != 0) {
    if (*(undefined1 **)(lVar1 + 8) != param_1 + 8) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02963548/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TChain.h"*/,0x36,&UNK_029635ec/*"Next hasn't myself."*/);
      lVar1 = *(long *)(param_1 + 0x18);
    }
    *(undefined8 *)(lVar1 + 8) = *(undefined8 *)(param_1 + 0x10);
  }
  lVar1 = *(long *)(param_1 + 0x38);
  *(undefined8 *)(param_1 + 0x10) = 0;
  *(undefined8 *)(param_1 + 0x18) = 0;
  if (lVar1 == 0) {
    lVar1 = *(long *)(param_1 + 0x40);
  }
  else {
    if (*(undefined1 **)(lVar1 + 0x10) != param_1 + 0x30) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02963548/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TChain.h"*/,0x31,&UNK_029635d4/*"Previous hasn't myself."*/);
      lVar1 = *(long *)(param_1 + 0x38);
    }
    *(long *)(lVar1 + 0x10) = *(long *)(param_1 + 0x40);
    lVar1 = *(long *)(param_1 + 0x40);
  }
  if (lVar1 != 0) {
    if (*(undefined1 **)(lVar1 + 8) != param_1 + 0x30) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02963548/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TChain.h"*/,0x36,&UNK_029635ec/*"Next hasn't myself."*/);
      lVar1 = *(long *)(param_1 + 0x40);
    }
    *(undefined8 *)(lVar1 + 8) = *(undefined8 *)(param_1 + 0x38);
  }
  *(undefined8 *)(param_1 + 0x38) = 0;
  *(undefined8 *)(param_1 + 0x40) = 0;
  *param_1 = 0;
  return;
}

// ==== Framework::TChain<Framework::ResponderChain::CResponder>::~TChain()
// vaddr 0x1e9752c | ghidra 0x1f9752c | size 176 | symbol _ZN9Framework6TChainINS_14ResponderChain10CResponderEED2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework6TChainINS_14ResponderChain10CResponderEED2Ev(long *param_1)

{
  long lVar1;
  
  lVar1 = param_1[1];
  *param_1 = (long)(PTR__ZTVN9Framework6TChainINS_14ResponderChain10CResponderEEE_02cbd2d8 + 0x10);
  if (lVar1 == 0) {
    lVar1 = param_1[2];
  }
  else {
    if (*(long **)(lVar1 + 0x10) != param_1) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02963548/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TChain.h"*/,0x31,&UNK_029635d4/*"Previous hasn't myself."*/);
      lVar1 = param_1[1];
    }
    *(long *)(lVar1 + 0x10) = param_1[2];
    lVar1 = param_1[2];
  }
  if (lVar1 != 0) {
    if (*(long **)(lVar1 + 8) != param_1) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02963548/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TChain.h"*/,0x36,&UNK_029635ec/*"Next hasn't myself."*/);
      lVar1 = param_1[2];
    }
    *(long *)(lVar1 + 8) = param_1[1];
  }
  param_1[1] = 0;
  param_1[2] = 0;
  return;
}

// ==== Framework::ResponderChain::CManager::Initialize()
// vaddr 0x1e975dc | ghidra 0x1f975dc | size 212 | symbol _ZN9Framework14ResponderChain8CManager10InitializeEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework14ResponderChain8CManager10InitializeEv(char *param_1)

{
  char *pcVar1;
  char *pcVar2;
  long lVar3;
  
  if (*param_1 != '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965b0f/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResponderChain.cpp"*/,0x73,&UNK_02964a0a/*"m_IsInitialized isn't null.(%08x)"*/);
  }
  pcVar1 = param_1 + 0x30;
  pcVar2 = param_1 + 8;
  if ((*(long *)(param_1 + 0x38) == 0) && (*(long *)(param_1 + 0x40) == 0)) {
    lVar3 = *(long *)(param_1 + 0x18);
    *(char **)(param_1 + 0x38) = pcVar2;
    *(long *)(param_1 + 0x40) = lVar3;
    if (lVar3 != 0) {
      *(char **)(lVar3 + 8) = pcVar1;
    }
    *(char **)(param_1 + 0x18) = pcVar1;
  }
  else {
    if (*(long *)(param_1 + 0x10) != 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02963548/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TChain.h"*/,0x52,&UNK_02963598/*"Target has already m_pPrevious."*/);
    }
    if (*(long *)(param_1 + 0x18) != 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02963548/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TChain.h"*/,0x53,&UNK_029635b8/*"Target has already m_pNext."*/);
    }
    lVar3 = *(long *)(param_1 + 0x38);
    *(long *)(param_1 + 0x10) = lVar3;
    *(char **)(param_1 + 0x18) = pcVar1;
    if (lVar3 != 0) {
      *(char **)(lVar3 + 0x10) = pcVar2;
    }
    *(char **)(param_1 + 0x38) = pcVar2;
  }
  param_1[0x48] = '\0';
  param_1[0x24] = '\0';
  param_1[0x25] = '\0';
  param_1[0x26] = '\0';
  param_1[0x27] = '\0';
  param_1[0x4c] = -1;
  param_1[0x4d] = -1;
  param_1[0x4e] = -1;
  param_1[0x4f] = -1;
  *param_1 = '\x01';
  return;
}

// ==== Framework::ResponderChain::CManager::rBeginResponder()
// vaddr 0x1e976b0 | ghidra 0x1f976b0 | size 52 | symbol _ZN9Framework14ResponderChain8CManager15rBeginResponderEv | lib libSOA-3.7.0.so | 2026-10-04
char * _ZN9Framework14ResponderChain8CManager15rBeginResponderEv(char *param_1)

{
  if (*param_1 == '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965b0f/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResponderChain.cpp"*/,0x89,&UNK_02964a2c/*"m_IsInitialized is null."*/);
  }
  return param_1 + 8;
}

// ==== Framework::ResponderChain::CManager::rEndResponder()
// vaddr 0x1e976e4 | ghidra 0x1f976e4 | size 52 | symbol _ZN9Framework14ResponderChain8CManager13rEndResponderEv | lib libSOA-3.7.0.so | 2026-10-04
char * _ZN9Framework14ResponderChain8CManager13rEndResponderEv(char *param_1)

{
  if (*param_1 == '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965b0f/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResponderChain.cpp"*/,0x90,&UNK_02964a2c/*"m_IsInitialized is null."*/);
  }
  return param_1 + 0x30;
}

// ==== Framework::ResponderChain::CManager::Attach(Framework::ResponderChain::CResponder&, unsigned int)
// vaddr 0x1e97718 | ghidra 0x1f97718 | size 100 | symbol _ZN9Framework14ResponderChain8CManager6AttachERNS0_10CResponderEj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework14ResponderChain8CManager6AttachERNS0_10CResponderEj
               (long param_1,long param_2,uint param_3)

{
  long *plVar1;
  
  plVar1 = (long *)(param_1 + 8);
  if (*(uint *)(param_1 + 0x24) <= param_3) {
    do {
      if ((plVar1 == (long *)0x0) || (plVar1 == (long *)(param_1 + 0x30))) break;
      plVar1 = (long *)plVar1[2];
    } while (*(uint *)((long)plVar1 + 0x1c) <= param_3);
  }
  (**(code **)(*plVar1 + 0x10))(plVar1,param_2);
  *(uint *)(param_2 + 0x1c) = param_3;
  return;
}

// ==== Framework::ResponderChain::CManager::Progress()
// vaddr 0x1e9777c | ghidra 0x1f9777c | size 188 | symbol _ZN9Framework14ResponderChain8CManager8ProgressEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework14ResponderChain8CManager8ProgressEv(char *param_1)

{
  undefined *puVar1;
  int iVar2;
  long lVar3;
  undefined8 uStack_18;
  
  if (*param_1 == '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965b0f/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ResponderChain.cpp"*/,0xb4,&UNK_02964a2c/*"m_IsInitialized is null."*/);
  }
  puVar1 = PTR__ZN9Framework10TSingletonINS_4CPadEE11m_pInstanceE_02cbef78;
  uStack_18 = 0;
  if (*(long *)PTR__ZN9Framework10TSingletonINS_4CPadEE11m_pInstanceE_02cbef78 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029612b1/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    iVar2 = Framework::CPad::NumUnits() const(*(undefined8 *)puVar1);
  }
  else {
    iVar2 = Framework::CPad::NumUnits() const();
  }
  if (iVar2 == 0) {
    uStack_18 = 0;
  }
  else {
    lVar3 = *(long *)puVar1;
    if (lVar3 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029612b1/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
      lVar3 = *(long *)puVar1;
    }
    uStack_18 = Framework::CPad::rUnit(unsigned int)(lVar3,0);
  }
  Framework::ResponderChain::CResponder::Progress(Framework::ResponderChain::CAccessAuthority&)(param_1 + 8,&uStack_18);
  return;
}

// ==== Framework::ResponderChain::CResponder::~CResponder()
// vaddr 0x1e97838 | ghidra 0x1f97838 | size 180 | symbol _ZN9Framework14ResponderChain10CResponderD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework14ResponderChain10CResponderD0Ev(long *param_1)

{
  long lVar1;
  
  lVar1 = param_1[1];
  *param_1 = (long)(PTR__ZTVN9Framework6TChainINS_14ResponderChain10CResponderEEE_02cbd2d8 + 0x10);
  if (lVar1 == 0) {
    lVar1 = param_1[2];
  }
  else {
    if (*(long **)(lVar1 + 0x10) != param_1) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02963548/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TChain.h"*/,0x31,&UNK_029635d4/*"Previous hasn't myself."*/);
      lVar1 = param_1[1];
    }
    *(long *)(lVar1 + 0x10) = param_1[2];
    lVar1 = param_1[2];
  }
  if (lVar1 != 0) {
    if (*(long **)(lVar1 + 8) != param_1) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02963548/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TChain.h"*/,0x36,&UNK_029635ec/*"Next hasn't myself."*/);
      lVar1 = param_1[2];
    }
    *(long *)(lVar1 + 8) = param_1[1];
  }
  param_1[1] = 0;
  param_1[2] = 0;
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Framework::ResponderChain::CResponder::pTop()
// vaddr 0x1e978ec | ghidra 0x1f978ec | size 20 | symbol _ZN9Framework14ResponderChain10CResponder4pTopEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZN9Framework14ResponderChain10CResponder4pTopEv(long param_1)

{
  long lVar1;
  
  do {
    lVar1 = param_1;
    param_1 = *(long *)(lVar1 + 8);
  } while (param_1 != 0);
  return lVar1;
}

// ==== Framework::ResponderChain::CResponder::pBottom()
// vaddr 0x1e97900 | ghidra 0x1f97900 | size 20 | symbol _ZN9Framework14ResponderChain10CResponder7pBottomEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZN9Framework14ResponderChain10CResponder7pBottomEv(long param_1)

{
  long lVar1;
  
  do {
    lVar1 = param_1;
    param_1 = *(long *)(lVar1 + 0x10);
  } while (param_1 != 0);
  return lVar1;
}

// ==== Framework::TChain<Framework::ResponderChain::CResponder>::~TChain()
// vaddr 0x1e97914 | ghidra 0x1f97914 | size 4 | symbol _ZN9Framework6TChainINS_14ResponderChain10CResponderEED0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework6TChainINS_14ResponderChain10CResponderEED0Ev(void)

{
  code *pcVar1;
  
                    /* WARNING: Does not return */
  pcVar1 = (code *)SoftwareBreakpoint(1,0x1f97918);
  (*pcVar1)();
}

// ==== Aska::Global::DeleteEndNotify::IsEmpty()
// vaddr 0x2210588 | ghidra 0x2310588 | size 80 | symbol _ZN4Aska6Global15DeleteEndNotify7IsEmptyEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska6Global15DeleteEndNotify7IsEmptyEv(void)

{
  ulong uVar1;
  
  uVar1 = Aska::DeleteManager::IsEmpty()(PTR__ZN4Aska6Global21m_systemDeleteManagerE_02cb77c0);
  if ((uVar1 & 1) == 0) {
    return 0;
  }
  if ((*(long *)PTR__ZN4Aska6Global22m_pMappedMemoryManagerE_02cc0368 != 0) &&
     (uVar1 = Aska::MappedMemoryManager::IsEmpty() const(), (uVar1 & 1) == 0)) {
    return 0;
  }
  return 1;
}

// ==== Aska::Global::DeleteEndNotify::ShutdownHandler()
// vaddr 0x22105d8 | ghidra 0x23105d8 | size 16 | symbol _ZN4Aska6Global15DeleteEndNotify15ShutdownHandlerEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6Global15DeleteEndNotify15ShutdownHandlerEv(undefined8 *param_1)

{
                    /* WARNING: Could not recover jumptable at 0x023105e4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)*param_1)(param_1,0);
  return;
}

// ==== Aska::Global::DeleteEndNotify::Handler(unsigned long)
// vaddr 0x2210e64 | ghidra 0x2310e64 | size 272 | symbol _ZN4Aska6Global15DeleteEndNotify7HandlerEm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6Global15DeleteEndNotify7HandlerEm(void)

{
  long lVar1;
  undefined *puVar2;
  undefined *puVar3;
  ulong uVar4;
  long lVar5;
  
  puVar3 = PTR__ZN4Aska6Global17m_pTextureManagerE_02cc19f0;
  puVar2 = PTR__ZN4Aska6Global21m_systemDeleteManagerE_02cb77c0;
  lVar5 = *(long *)PTR__ZN4Aska6Global17m_pTextureManagerE_02cc19f0;
  if (lVar5 == 0) {
    Aska::DeleteManager::PreFlushMain()(PTR__ZN4Aska6Global21m_systemDeleteManagerE_02cb77c0);
    do {
      uVar4 = Aska::DeleteManager::FlushMain()(puVar2);
    } while ((uVar4 & 1) == 0);
  }
  else {
    lVar1 = lVar5 + 0xb0;
    Aska::CriticalSection::Enter() const(lVar1);
    Aska::TextureManager::FlushTextureEx(unsigned int)(lVar5,1);
    Aska::CriticalSection::Leave() const(lVar1);
    puVar2 = PTR__ZN4Aska6Global21m_systemDeleteManagerE_02cb77c0;
    Aska::DeleteManager::PreFlushMain()(PTR__ZN4Aska6Global21m_systemDeleteManagerE_02cb77c0);
    do {
      Aska::CriticalSection::Enter() const(lVar1);
      Aska::TextureManager::FlushTextureEx(unsigned int)(lVar5,1);
      Aska::CriticalSection::Leave() const(lVar1);
      uVar4 = Aska::DeleteManager::FlushMain()(puVar2);
    } while ((uVar4 & 1) == 0);
  }
  lVar5 = *(long *)PTR__ZN4Aska6Global22m_pMappedMemoryManagerE_02cc0368;
  if (lVar5 != 0) {
    Aska::CriticalSection::Enter() const(lVar5 + 8);
    Aska::MappedMemoryManager::FlushMappingEx()(lVar5);
    Aska::CriticalSection::Leave() const(lVar5 + 8);
  }
  lVar5 = *(long *)puVar3;
  if (lVar5 != 0) {
    Aska::CriticalSection::Enter() const(lVar5 + 0xb0);
    Aska::TextureManager::FlushTextureEx(unsigned int)(lVar5,2);
    Aska::CriticalSection::Leave() const(lVar5 + 0xb0);
  }
  Aska::DeleteManager::PostFlushMain()(PTR__ZN4Aska6Global21m_systemDeleteManagerE_02cb77c0);
  (*(code *)PTR__ZN4Aska17RenderManagerBase24DecideDeleteGpuResourcesEv_02ca41d8)
            (*(undefined8 *)PTR__ZN4Aska12g_pRenderDevE_02cbb1a0);
  return;
}

// ==== Aska::Global::DeleteEndNotify::~DeleteEndNotify()
// vaddr 0x2210f94 | ghidra 0x2310f94 | size 4 | symbol _ZN4Aska6Global15DeleteEndNotifyD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6Global15DeleteEndNotifyD0Ev(void)

{
  (*(code *)PTR__ZdlPv_02ca4758)();
  return;
}

// ==== Aska::MessageDispatcher::~MessageDispatcher()
// vaddr 0x2210f98 | ghidra 0x2310f98 | size 132 | symbol _ZN4Aska17MessageDispatcherD2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska17MessageDispatcherD2Ev(long *param_1)

{
  undefined *puVar1;
  
  *param_1 = (long)(PTR__ZTVN4Aska17MessageDispatcherE_02cbe770 + 0x10);
  Aska::MessageDispatcher::Release()();
  *param_1 = (long)(PTR__ZTVN4Aska23SimpleMessageDispatcherE_02cba3a8 + 0x10);
  Aska::SimpleMessageDispatcher::Release()(param_1);
  if (param_1[0x28] != 0) {
    operator delete[](void*)();
  }
  Aska::Event::Exit()(param_1 + 0x29);
  Aska::Event::Exit()(param_1 + 0x29);
  puVar1 = PTR__ZTVN4Aska13TDynamicQueueIPNS_29MessageDispatcherBlockForListELb0EEE_02cc17a8;
  *(undefined4 *)(param_1 + 0x25) = 0;
  param_1[0x26] = 0;
  param_1[0x23] = (long)(puVar1 + 0x10);
  param_1[0x24] = 1;
  (*(code *)PTR__ZN4Aska19FastCriticalSectionD2Ev_02ca21e0)(param_1 + 1);
  return;
}

// ==== Aska::MessageDispatcher::~MessageDispatcher()
// vaddr 0x221101c | ghidra 0x231101c | size 140 | symbol _ZN4Aska17MessageDispatcherD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska17MessageDispatcherD0Ev(long *param_1)

{
  undefined *puVar1;
  
  *param_1 = (long)(PTR__ZTVN4Aska17MessageDispatcherE_02cbe770 + 0x10);
  Aska::MessageDispatcher::Release()();
  *param_1 = (long)(PTR__ZTVN4Aska23SimpleMessageDispatcherE_02cba3a8 + 0x10);
  Aska::SimpleMessageDispatcher::Release()(param_1);
  if (param_1[0x28] != 0) {
    operator delete[](void*)();
  }
  Aska::Event::Exit()(param_1 + 0x29);
  Aska::Event::Exit()(param_1 + 0x29);
  puVar1 = PTR__ZTVN4Aska13TDynamicQueueIPNS_29MessageDispatcherBlockForListELb0EEE_02cc17a8;
  *(undefined4 *)(param_1 + 0x25) = 0;
  param_1[0x26] = 0;
  param_1[0x23] = (long)(puVar1 + 0x10);
  param_1[0x24] = 1;
  Aska::FastCriticalSection::~FastCriticalSection()(param_1 + 1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::MessageDispatcher::Initialize()
// vaddr 0x2233858 | ghidra 0x2333858 | size 4 | symbol _ZN4Aska17MessageDispatcher10InitializeEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska17MessageDispatcher10InitializeEv(void)

{
  return;
}

// ==== Aska::MessageDispatcher::Release()
// vaddr 0x223385c | ghidra 0x233385c | size 4 | symbol _ZN4Aska17MessageDispatcher7ReleaseEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska17MessageDispatcher7ReleaseEv(void)

{
  return;
}


// FAILED to create function at 02965b90 typeinfo name for Framework::ResponderChain::CResponder
// FAILED to create function at 02965bc0 typeinfo name for Framework::TChain<Framework::ResponderChain::CResponder>
// FAILED to create function at 029d4c90 typeinfo name for Aska::Global::DeleteEndNotify
// FAILED to create function at 02ba9168 Framework::CMessageManager::vtable
// FAILED to create function at 02ba9188 Framework::CMessageManager::typeinfo
// FAILED to create function at 02baae48 Framework::ResponderChain::CResponder::vtable
// FAILED to create function at 02baae80 Framework::TChain<Framework::ResponderChain::CResponder>::typeinfo
// FAILED to create function at 02baae90 Framework::ResponderChain::CResponder::typeinfo
// FAILED to create function at 02baaea8 Framework::TChain<Framework::ResponderChain::CResponder>::vtable
// FAILED to create function at 02c579b8 Aska::Global::DeleteEndNotify::vtable
// FAILED to create function at 02c579c8 Aska::Global::DeleteEndNotify[16]::vtable
// FAILED to create function at 02c579e0 Aska::Global::DeleteEndNotify::typeinfo
// FAILED to create function at 02c579f8 Aska::MessageDispatcher::vtable
// FAILED to create function at 02c57a30 Aska::MessageDispatcher::typeinfo
