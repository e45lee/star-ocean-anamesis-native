// port/decomp/master/simple_item.c: Ghidra decompiles for the master subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-08 13:28 UTC: tools/decomp.sh '--into' 'master/simple_item' 'CMasterParameterBaseSqlite_Simple<CMasterParameterItemElement>::' 'DeserializeMsgPack<CMasterParameterItemElement>' 'CSimpleSqliteConnector<MasterDB::CItem,'

// ==== CMasterParameterBaseSqlite_Simple<CMasterParameterItemElement>::pParameterFromHash(unsigned int) const
// vaddr 0x114c0f4 | ghidra 0x124c0f4 | size 1584 | symbol _ZNK33CMasterParameterBaseSqlite_SimpleI27CMasterParameterItemElementE18pParameterFromHashEj | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Possible PIC construction at 0x0124c654: Changing call to branch */
/* WARNING: Possible PIC construction at 0x0124c494: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0x0124c658) */
/* WARNING: Removing unreachable block (ram,0x0124c660) */
/* WARNING: Removing unreachable block (ram,0x0124c498) */
/* WARNING: Removing unreachable block (ram,0x0124c4b0) */
/* WARNING: Removing unreachable block (ram,0x0124c4b8) */
/* WARNING: Removing unreachable block (ram,0x0124c4bc) */
/* WARNING: Removing unreachable block (ram,0x0124c4c0) */
/* WARNING: Removing unreachable block (ram,0x0124c4dc) */
/* WARNING: Removing unreachable block (ram,0x0124c4cc) */
/* WARNING: Removing unreachable block (ram,0x0124c4e0) */
/* WARNING: Removing unreachable block (ram,0x0124c4f0) */
/* WARNING: Removing unreachable block (ram,0x0124c518) */
/* WARNING: Removing unreachable block (ram,0x0124c50c) */
/* WARNING: Removing unreachable block (ram,0x0124c51c) */
/* WARNING: Removing unreachable block (ram,0x0124c534) */
/* WARNING: Removing unreachable block (ram,0x0124c550) */
/* WARNING: Removing unreachable block (ram,0x0124c56c) */
/* WARNING: Removing unreachable block (ram,0x0124c560) */
/* WARNING: Removing unreachable block (ram,0x0124c570) */
/* WARNING: Removing unreachable block (ram,0x0124c528) */
/* WARNING: Removing unreachable block (ram,0x0124c578) */
/* WARNING: Removing unreachable block (ram,0x0124c57c) */

void _ZNK33CMasterParameterBaseSqlite_SimpleI27CMasterParameterItemElementE18pParameterFromHashEj
               (long *param_1,long *param_2,uint param_3)

{
  undefined *puVar1;
  long *plVar2;
  int iVar3;
  uint uVar4;
  char cVar5;
  bool bVar6;
  ulong uVar7;
  ulong uVar8;
  long *plVar9;
  long *plVar10;
  long lVar11;
  long *plVar12;
  ulong uVar13;
  ulong uVar14;
  long lVar15;
  ulong uVar16;
  long *plVar17;
  long *plVar18;
  long lStack_a0;
  undefined8 uStack_98;
  long *plStack_90;
  undefined8 uStack_88;
  undefined4 uStack_80;
  long lStack_78;
  long lStack_70;
  int *piStack_68;
  
  uVar13 = param_2[9];
  uVar16 = (ulong)param_3;
  plVar12 = param_2 + 8;
  if (uVar13 != 0) {
    uVar14 = uVar13 - 1;
    if ((uVar14 & uVar13) == 0) {
      uVar8 = uVar14 & uVar16;
    }
    else {
      uVar8 = 0;
      if (uVar13 != 0) {
        uVar8 = uVar16 / uVar13;
      }
      uVar8 = uVar16 - uVar8 * uVar13;
    }
    plVar10 = *(long **)(*plVar12 + uVar8 * 8);
    if (plVar10 == (long *)0x0) goto code_r0x0124c1ac;
    if ((uVar14 & uVar13) == 0) {
      do {
        plVar10 = (long *)*plVar10;
        if ((plVar10 == (long *)0x0) || ((plVar10[1] & uVar14) != uVar8)) goto code_r0x0124c1ac;
      } while (*(uint *)(plVar10 + 2) != param_3);
    }
    else {
      do {
        plVar10 = (long *)*plVar10;
        if (plVar10 == (long *)0x0) goto code_r0x0124c1ac;
        uVar14 = 0;
        if (uVar13 != 0) {
          uVar14 = (ulong)plVar10[1] / uVar13;
        }
        if (plVar10[1] - uVar14 * uVar13 != uVar8) goto code_r0x0124c1ac;
      } while (*(uint *)(plVar10 + 2) != param_3);
    }
    if (plVar10 == (long *)0x0) goto code_r0x0124c1ac;
code_r0x0124c234:
    *param_1 = plVar10[3];
    plVar10 = (long *)plVar10[4];
    param_1[1] = (long)plVar10;
    if (plVar10 == (long *)0x0) {
      return;
    }
code_r0x011d44c0:
    (*(code *)PTR__ZNSt6__ndk119__shared_weak_count12__add_sharedEv_02ca2250)(plVar10);
    return;
  }
code_r0x0124c1ac:
  uVar13 = param_2[4];
  if (uVar13 != 0) {
    uVar14 = uVar13 - 1;
    if ((uVar14 & uVar13) == 0) {
      uVar8 = uVar14 & uVar16;
    }
    else {
      uVar8 = 0;
      if (uVar13 != 0) {
        uVar8 = uVar16 / uVar13;
      }
      uVar8 = uVar16 - uVar8 * uVar13;
    }
    plVar10 = *(long **)(param_2[3] + uVar8 * 8);
    if (plVar10 != (long *)0x0) {
      if ((uVar14 & uVar13) == 0) {
        do {
          plVar10 = (long *)*plVar10;
          if ((plVar10 == (long *)0x0) || ((plVar10[1] & uVar14) != uVar8)) goto code_r0x0124c268;
        } while (*(uint *)(plVar10 + 2) != param_3);
      }
      else {
        do {
          plVar10 = (long *)*plVar10;
          if (plVar10 == (long *)0x0) goto code_r0x0124c268;
          uVar14 = 0;
          if (uVar13 != 0) {
            uVar14 = (ulong)plVar10[1] / uVar13;
          }
          if (plVar10[1] - uVar14 * uVar13 != uVar8) goto code_r0x0124c268;
        } while (*(uint *)(plVar10 + 2) != param_3);
      }
      if (plVar10 != (long *)0x0) goto code_r0x0124c234;
    }
  }
code_r0x0124c268:
  uVar13 = (**(code **)(*param_2 + 0x28))(param_2);
  if ((uVar13 & 1) == 0) {
    *param_1 = 0;
    param_1[1] = 0;
    return;
  }
  plVar17 = (long *)param_2[1];
  if (plVar17 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dc023/*"C:\BAS_Submission\Client\Project\Android\BASAndroid.NativeActivity\..\..\..\Source\Game/Parameter/Master/MasterParameterBaseSqlite.h"*/,0x4d,&UNK_027dc0a8/*"m_pConnector is null."*/);
  }
  (**(code **)(*plVar17 + 0x10))(plVar17,&UNK_027dc00a/*"sqlite/basmaster.sqlite3"*/);
  lStack_70 = 0;
  piStack_68 = (int *)0x0;
  lStack_78 = 0;
  (**(code **)(*plVar17 + 0x28))(plVar17,1,uVar16,&lStack_70,&lStack_78);
  if (lStack_78 < 1) {
    *param_1 = 0;
    param_1[1] = 0;
  }
  else {
    if ((ulong)param_2[0xd] < (ulong)param_2[0xb]) {
      plVar10 = (long *)param_2[10];
      while (plVar10 != (long *)0x0) {
        lVar15 = *plVar10;
        if (plVar10[4] != 0) {
          std::__ndk1::__shared_weak_count::__release_shared()();
        }
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar10);
        plVar10 = (long *)lVar15;
      }
      lVar15 = param_2[9];
      param_2[10] = 0;
      if (lVar15 != 0) {
        lVar11 = 0;
        do {
          *(undefined8 *)(*plVar12 + lVar11 * 8) = 0;
          lVar11 = lVar11 + 1;
        } while (lVar15 != lVar11);
      }
      param_2[0xb] = 0;
    }
    uStack_98 = 0;
    lStack_a0 = 0;
    uStack_88 = 0;
    plStack_90 = (long *)0x0;
    uStack_80 = 0x3f800000;
    void CMasterParameterBaseSqlite::DeserializeMsgPack<CMasterParameterItemElement>(Aska::TSharedArray<signed char> const&, long const&, CMasterParameterItemElement*, Framework::CSTLUnorderedMap<unsigned int, CMasterParameterItemElement, std::__ndk1::hash<unsigned int>, std::__ndk1::equal_to<unsigned int> >*) const(param_2,&lStack_70,&lStack_78,0,&lStack_a0);
    if (plStack_90 != (long *)0x0) {
      puVar1 = PTR__ZTVNSt6__ndk120__shared_ptr_emplaceI27CMasterParameterItemElement18ParameterAllocatorIS1_EEE_02cba4c0
               + 0x10;
      plVar18 = plStack_90;
      do {
        plVar10 = (long *)operator new(unsigned long)(0x9e8);
        plVar2 = plVar10 + 3;
        plVar10[1] = 0;
        plVar10[2] = 0;
        *plVar10 = (long)puVar1;
        CMasterParameterItemElement::CMasterParameterItemElement()(plVar2);
        CMasterParameterItemElement::operator=(CMasterParameterItemElement const&)(plVar2,plVar18 + 3);
        uVar14 = param_2[9];
        uVar4 = *(uint *)(plVar18 + 2);
        uVar13 = (ulong)uVar4;
        if (uVar14 == 0) {
code_r0x0124c450:
          lVar15 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(0x28,&UNK_027dc2d5/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_UnorderedMap.h"*/,0x1c);
          if (lVar15 == 0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
          }
          lVar11 = plVar18[2];
          *(long **)(lVar15 + 0x18) = plVar2;
          *(long **)(lVar15 + 0x20) = plVar10;
          *(int *)(lVar15 + 0x10) = (int)lVar11;
          goto code_r0x011d44c0;
        }
        uVar8 = uVar14 - 1;
        if ((uVar8 & uVar14) == 0) {
          uVar13 = uVar8 & uVar13;
        }
        else {
          uVar7 = 0;
          if (uVar14 != 0) {
            uVar7 = uVar13 / uVar14;
          }
          uVar13 = uVar13 - uVar7 * uVar14;
        }
        plVar9 = *(long **)(*plVar12 + uVar13 * 8);
        if (plVar9 == (long *)0x0) goto code_r0x0124c450;
        if ((uVar8 & uVar14) == 0) {
          do {
            plVar9 = (long *)*plVar9;
            if ((plVar9 == (long *)0x0) || ((plVar9[1] & uVar8) != uVar13)) goto code_r0x0124c450;
          } while (*(uint *)(plVar9 + 2) != uVar4);
        }
        else {
          do {
            plVar9 = (long *)*plVar9;
            if (plVar9 == (long *)0x0) goto code_r0x0124c450;
            uVar8 = 0;
            if (uVar14 != 0) {
              uVar8 = (ulong)plVar9[1] / uVar14;
            }
            if (plVar9[1] - uVar8 * uVar14 != uVar13) goto code_r0x0124c450;
          } while (*(uint *)(plVar9 + 2) != uVar4);
        }
        std::__ndk1::__shared_weak_count::__release_shared()(plVar10);
        plVar18 = (long *)*plVar18;
      } while (plVar18 != (long *)0x0);
    }
    uVar13 = param_2[9];
    lVar15 = lStack_a0;
    plVar18 = plStack_90;
    if (uVar13 == 0) {
code_r0x0124c664:
      *param_1 = 0;
      param_1[1] = 0;
    }
    else {
      uVar14 = uVar13 - 1;
      if ((uVar14 & uVar13) == 0) {
        uVar16 = uVar14 & uVar16;
      }
      else {
        uVar8 = 0;
        if (uVar13 != 0) {
          uVar8 = uVar16 / uVar13;
        }
        uVar16 = uVar16 - uVar8 * uVar13;
      }
      plVar12 = *(long **)(*plVar12 + uVar16 * 8);
      if (plVar12 == (long *)0x0) goto code_r0x0124c664;
      if ((uVar14 & uVar13) == 0) {
        do {
          plVar12 = (long *)*plVar12;
          if ((plVar12 == (long *)0x0) || ((plVar12[1] & uVar14) != uVar16)) goto code_r0x0124c664;
        } while (*(uint *)(plVar12 + 2) != param_3);
      }
      else {
        do {
          plVar12 = (long *)*plVar12;
          if (plVar12 == (long *)0x0) goto code_r0x0124c664;
          uVar14 = 0;
          if (uVar13 != 0) {
            uVar14 = (ulong)plVar12[1] / uVar13;
          }
          if (plVar12[1] - uVar14 * uVar13 != uVar16) goto code_r0x0124c664;
        } while (*(uint *)(plVar12 + 2) != param_3);
      }
      plVar10 = (long *)plVar12[4];
      *param_1 = plVar12[3];
      param_1[1] = (long)plVar10;
      if (plVar10 != (long *)0x0) goto code_r0x011d44c0;
    }
    while (plVar18 != (long *)0x0) {
      lVar11 = *plVar18;
      lStack_a0 = lVar15;
      CMasterParameterItemElement::~CMasterParameterItemElement()(plVar18 + 3);
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar18);
      lVar15 = lStack_a0;
      plVar18 = (long *)lVar11;
    }
    lStack_a0 = 0;
    if (lVar15 != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)();
    }
  }
  if (piStack_68 != (int *)0x0) {
    do {
      iVar3 = *piStack_68;
      cVar5 = '\x01';
      bVar6 = (bool)ExclusiveMonitorPass(piStack_68,0x10);
      if (bVar6) {
        *piStack_68 = iVar3 + -1;
        cVar5 = ExclusiveMonitorsStatus();
      }
    } while (cVar5 != '\0');
    if (iVar3 + -1 != 0) goto code_r0x0124c6d4;
  }
  if (lStack_70 != 0) {
    operator delete[](void*)();
  }
  if (piStack_68 != (int *)0x0) {
    Aska::TSharedPointerCode::DeleteCounter(int*)();
  }
code_r0x0124c6d4:
  lStack_70 = 0;
  if (plVar17 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dc023/*"C:\BAS_Submission\Client\Project\Android\BASAndroid.NativeActivity\..\..\..\Source\Game/Parameter/Master/MasterParameterBaseSqlite.h"*/,0x52,&UNK_027dc0a8/*"m_pConnector is null."*/);
  }
  (**(code **)(*plVar17 + 0x18))(plVar17);
  return;
}

// ==== void CMasterParameterBaseSqlite::DeserializeMsgPack<CMasterParameterItemElement>(Aska::TSharedArray<signed char> const&, long const&, CMasterParameterItemElement*, Framework::CSTLUnorderedMap<unsigned int, CMasterParameterItemElement, std::__ndk1::hash<unsigned int>, std::__ndk1::equal_to<unsigned int> >*) const
// vaddr 0x11728cc | ghidra 0x12728cc | size 1620 | symbol _ZNK26CMasterParameterBaseSqlite18DeserializeMsgPackI27CMasterParameterItemElementEEvRKN4Aska12TSharedArrayIaEERKlPT_PN9Framework16CSTLUnorderedMapIjS9_NSt6__ndk14hashIjEENSD_8equal_toIjEEEE | lib libSOA-3.7.0.so | 2026-10-08
void _ZNK26CMasterParameterBaseSqlite18DeserializeMsgPackI27CMasterParameterItemElementEEvRKN4Aska12TSharedArrayIaEERKlPT_PN9Framework16CSTLUnorderedMapIjS9_NSt6__ndk14hashIjEENSD_8equal_toIjEEEE
               (long *param_1,undefined8 *param_2,int *param_3,long *param_4,long *param_5)

{
  ulong uVar1;
  uint uVar2;
  undefined8 uVar3;
  int *piVar4;
  ulong uVar5;
  long lVar6;
  long *plVar7;
  long *plVar8;
  ulong uVar9;
  ulong uVar10;
  ulong uVar11;
  ulong unaff_x24;
  int iVar12;
  float fVar13;
  undefined1 auStack_ae0 [16];
  undefined1 auStack_ad0 [16];
  undefined1 auStack_ac0 [2512];
  undefined1 auStack_f0 [96];
  int iStack_90;
  long lStack_88;
  uint uStack_80;
  
  Aska::ASON::ASON()(auStack_f0);
  uVar2 = *param_3 << 2;
  if (uVar2 < 0x2001) {
    uVar2 = 0x2000;
  }
  Aska::ASON::Init(unsigned int, bool)(auStack_f0,uVar2,1);
  Aska::ASON::Deserialize(void const*, unsigned long)(auStack_f0,*param_2,*(undefined8 *)param_3);
  if (iStack_90 == 6) {
    if (param_5 != (long *)0x0) {
      fVar13 = (float)NEON_ucvtf(uStack_80);
      std::__ndk1::__hash_table<std::__ndk1::__hash_value_type<unsigned int, CMasterParameterItemElement>, std::__ndk1::__unordered_map_hasher<unsigned int, std::__ndk1::__hash_value_type<unsigned int, CMasterParameterItemElement>, std::__ndk1::hash<unsigned int>, true>, std::__ndk1::__unordered_map_equal<unsigned int, std::__ndk1::__hash_value_type<unsigned int, CMasterParameterItemElement>, std::__ndk1::equal_to<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__hash_value_type<unsigned int, CMasterParameterItemElement>, Framework::CSTLUnorderedMapAllocatorInf> >::rehash(unsigned long)(param_5,(long)(fVar13 / *(float *)(param_5 + 4)));
    }
    if (uStack_80 != 0) {
      uVar5 = 0;
      do {
        lVar6 = lStack_88 + uVar5 * 0x20;
        if (lVar6 == 0) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dc023/*"C:\BAS_Submission\Client\Project\Android\BASAndroid.NativeActivity\..\..\..\Source\Game/Parameter/Master/MasterParameterBaseSqlite.h"*/,0x1b0,&UNK_0285e8d7/*"pValue is null."*/);
        }
        plVar7 = (long *)(lVar6 + 8);
        uVar3 = (**(code **)(*param_1 + 0x18))(param_1);
        piVar4 = (int *)Aska::ASON::AValue::AMap::Get_(char const*)(plVar7,uVar3);
        if (piVar4 == (int *)0x0) break;
        if (param_5 == (long *)0x0) {
          if (param_4 != (long *)0x0) {
            (**(code **)*param_4)(param_4);
            lVar6 = *param_4;
            goto code_r0x01272d44;
          }
        }
        else {
          CMasterParameterItemElement::CMasterParameterItemElement()(auStack_ac0);
          CMasterParameterItemElement::Initialize()(auStack_ac0);
          CParameterElementBase::Deserialize(Aska::ASON::AValue::AMap const*)(auStack_ac0,plVar7);
          if (*piVar4 == 5) {
            Framework::CHash32::CHash32(char const*)(auStack_ae0,*(undefined8 *)(piVar4 + 4));
            uVar11 = Framework::CHash32::operator unsigned int() const(auStack_ae0);
            uVar11 = uVar11 & 0xffffffff;
            Framework::CHash32::~CHash32()(auStack_ae0);
          }
          else {
            uVar3 = (**(code **)(*param_1 + 0x18))(param_1);
            uVar11 = CParameterParser::GetValueUInt(Aska::ASON::AValue::AMap const*, char const*)(plVar7,uVar3);
            uVar2 = 0;
            if ((uVar11 & 0x100000000) != 0) {
              uVar2 = (uint)uVar11;
            }
            uVar11 = (ulong)uVar2;
          }
          uVar10 = param_5[1];
          iVar12 = (int)uVar11;
          if (uVar10 == 0) {
code_r0x01272b50:
            plVar7 = (long *)Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(0x9e8,&UNK_027dc2d5/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_UnorderedMap.h"*/,0x1c);
            if (plVar7 == (long *)0x0) {
              Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
            }
            *(int *)(plVar7 + 2) = iVar12;
            CMasterParameterItemElement::CMasterParameterItemElement(CMasterParameterItemElement const&)(plVar7 + 3,auStack_ac0);
            *plVar7 = 0;
            plVar7[1] = uVar11;
            if ((uVar10 == 0) || (*(float *)(param_5 + 4) * (float)uVar10 < (float)(param_5[3] + 1))
               ) {
              if (uVar10 < 3) {
                uVar9 = 1;
              }
              else {
                uVar9 = (ulong)((uVar10 - 1 & uVar10) != 0);
              }
              uVar9 = uVar9 | uVar10 << 1;
              uVar10 = (ulong)((float)(param_5[3] + 1) / *(float *)(param_5 + 4));
              if (uVar10 <= uVar9) {
                uVar10 = uVar9;
              }
              std::__ndk1::__hash_table<std::__ndk1::__hash_value_type<unsigned int, CMasterParameterItemElement>, std::__ndk1::__unordered_map_hasher<unsigned int, std::__ndk1::__hash_value_type<unsigned int, CMasterParameterItemElement>, std::__ndk1::hash<unsigned int>, true>, std::__ndk1::__unordered_map_equal<unsigned int, std::__ndk1::__hash_value_type<unsigned int, CMasterParameterItemElement>, std::__ndk1::equal_to<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__hash_value_type<unsigned int, CMasterParameterItemElement>, Framework::CSTLUnorderedMapAllocatorInf> >::rehash(unsigned long)(param_5,uVar10);
              uVar10 = param_5[1];
              if ((uVar10 - 1 & uVar10) == 0) {
                param_2 = (undefined8 *)(uVar10 - 1 & uVar11);
              }
              else {
                uVar9 = 0;
                if (uVar10 != 0) {
                  uVar9 = uVar11 / uVar10;
                }
                param_2 = (undefined8 *)(uVar11 - uVar9 * uVar10);
              }
            }
            plVar8 = *(long **)(*param_5 + (long)param_2 * 8);
            if (plVar8 == (long *)0x0) {
              *plVar7 = param_5[2];
              param_5[2] = (long)plVar7;
              *(long **)(*param_5 + (long)param_2 * 8) = param_5 + 2;
              if (*plVar7 != 0) {
                uVar11 = *(ulong *)(*plVar7 + 8);
                if ((uVar10 - 1 & uVar10) == 0) {
                  uVar11 = uVar11 & uVar10 - 1;
                }
                else {
                  uVar9 = 0;
                  if (uVar10 != 0) {
                    uVar9 = uVar11 / uVar10;
                  }
                  uVar11 = uVar11 - uVar9 * uVar10;
                }
                plVar8 = (long *)(*param_5 + uVar11 * 8);
                goto code_r0x01272c70;
              }
            }
            else {
              *plVar7 = *plVar8;
code_r0x01272c70:
              *plVar8 = (long)plVar7;
            }
            param_5[3] = param_5[3] + 1;
          }
          else {
            uVar9 = uVar10 - 1;
            if ((uVar9 & uVar10) == 0) {
              param_2 = (undefined8 *)(uVar9 & uVar11);
            }
            else {
              uVar1 = 0;
              if (uVar10 != 0) {
                uVar1 = uVar11 / uVar10;
              }
              param_2 = (undefined8 *)(uVar11 - uVar1 * uVar10);
            }
            plVar7 = *(long **)(*param_5 + (long)param_2 * 8);
            if (plVar7 == (long *)0x0) goto code_r0x01272b50;
            if ((uVar9 & uVar10) == 0) {
              do {
                plVar7 = (long *)*plVar7;
                if ((plVar7 == (long *)0x0) || ((undefined8 *)(plVar7[1] & uVar9) != param_2))
                goto code_r0x01272b50;
              } while ((int)plVar7[2] != iVar12);
            }
            else {
              do {
                plVar7 = (long *)*plVar7;
                if (plVar7 == (long *)0x0) goto code_r0x01272b50;
                uVar9 = 0;
                if (uVar10 != 0) {
                  uVar9 = (ulong)plVar7[1] / uVar10;
                }
                if ((undefined8 *)(plVar7[1] - uVar9 * uVar10) != param_2) goto code_r0x01272b50;
              } while (*(int *)(plVar7 + 2) != iVar12);
            }
          }
          CMasterParameterItemElement::~CMasterParameterItemElement()(auStack_ac0);
        }
        uVar2 = (int)uVar5 + 1;
        uVar5 = (ulong)uVar2;
      } while (uVar2 < uStack_80);
    }
    goto code_r0x01272ef8;
  }
  if (iStack_90 != 7) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dc023/*"C:\BAS_Submission\Client\Project\Android\BASAndroid.NativeActivity\..\..\..\Source\Game/Parameter/Master/MasterParameterBaseSqlite.h"*/,0x1d7,&UNK_027dc0be/*"msgpack format invalid."*/);
    goto code_r0x01272ef8;
  }
  plVar7 = &lStack_88;
  if (param_5 == (long *)0x0) {
    if (param_4 != (long *)0x0) {
      (**(code **)*param_4)(param_4);
      lVar6 = *param_4;
code_r0x01272d44:
      (**(code **)(lVar6 + 8))(param_4,plVar7);
    }
    goto code_r0x01272ef8;
  }
  CMasterParameterItemElement::CMasterParameterItemElement()(auStack_ac0);
  CMasterParameterItemElement::Initialize()(auStack_ac0);
  CParameterElementBase::Deserialize(Aska::ASON::AValue::AMap const*)(auStack_ac0,plVar7);
  uVar3 = (**(code **)(*param_1 + 0x18))(param_1);
  piVar4 = (int *)Aska::ASON::AValue::AMap::Get_(char const*)(plVar7,uVar3);
  if (piVar4 != (int *)0x0) {
    if (*piVar4 == 5) {
      Framework::CHash32::CHash32(char const*)(auStack_ad0,*(undefined8 *)(piVar4 + 4));
      uVar5 = Framework::CHash32::operator unsigned int() const(auStack_ad0);
      uVar5 = uVar5 & 0xffffffff;
      Framework::CHash32::~CHash32()(auStack_ad0);
    }
    else {
      uVar3 = (**(code **)(*param_1 + 0x18))(param_1);
      uVar5 = CParameterParser::GetValueUInt(Aska::ASON::AValue::AMap const*, char const*)(plVar7,uVar3);
      uVar2 = 0;
      if ((uVar5 & 0x100000000) != 0) {
        uVar2 = (uint)uVar5;
      }
      uVar5 = (ulong)uVar2;
    }
    uVar11 = param_5[1];
    iVar12 = (int)uVar5;
    if (uVar11 != 0) {
      uVar10 = uVar11 - 1;
      if ((uVar10 & uVar11) == 0) {
        unaff_x24 = uVar10 & uVar5;
      }
      else {
        uVar9 = 0;
        if (uVar11 != 0) {
          uVar9 = uVar5 / uVar11;
        }
        unaff_x24 = uVar5 - uVar9 * uVar11;
      }
      plVar7 = *(long **)(*param_5 + unaff_x24 * 8);
      if (plVar7 != (long *)0x0) {
        if ((uVar10 & uVar11) == 0) {
          do {
            plVar7 = (long *)*plVar7;
            if ((plVar7 == (long *)0x0) || ((plVar7[1] & uVar10) != unaff_x24))
            goto code_r0x01272db8;
          } while ((int)plVar7[2] != iVar12);
        }
        else {
          do {
            plVar7 = (long *)*plVar7;
            if (plVar7 == (long *)0x0) goto code_r0x01272db8;
            uVar10 = 0;
            if (uVar11 != 0) {
              uVar10 = (ulong)plVar7[1] / uVar11;
            }
            if (plVar7[1] - uVar10 * uVar11 != unaff_x24) goto code_r0x01272db8;
          } while (*(int *)(plVar7 + 2) != iVar12);
        }
        goto code_r0x01272ef0;
      }
    }
code_r0x01272db8:
    plVar7 = (long *)Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(0x9e8,&UNK_027dc2d5/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_UnorderedMap.h"*/,0x1c);
    if (plVar7 == (long *)0x0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
    *(int *)(plVar7 + 2) = iVar12;
    CMasterParameterItemElement::CMasterParameterItemElement(CMasterParameterItemElement const&)(plVar7 + 3,auStack_ac0);
    *plVar7 = 0;
    plVar7[1] = uVar5;
    if ((uVar11 == 0) || (*(float *)(param_5 + 4) * (float)uVar11 < (float)(param_5[3] + 1))) {
      if (uVar11 < 3) {
        uVar10 = 1;
      }
      else {
        uVar10 = (ulong)((uVar11 - 1 & uVar11) != 0);
      }
      uVar10 = uVar10 | uVar11 << 1;
      uVar11 = (ulong)((float)(param_5[3] + 1) / *(float *)(param_5 + 4));
      if (uVar11 <= uVar10) {
        uVar11 = uVar10;
      }
      std::__ndk1::__hash_table<std::__ndk1::__hash_value_type<unsigned int, CMasterParameterItemElement>, std::__ndk1::__unordered_map_hasher<unsigned int, std::__ndk1::__hash_value_type<unsigned int, CMasterParameterItemElement>, std::__ndk1::hash<unsigned int>, true>, std::__ndk1::__unordered_map_equal<unsigned int, std::__ndk1::__hash_value_type<unsigned int, CMasterParameterItemElement>, std::__ndk1::equal_to<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__hash_value_type<unsigned int, CMasterParameterItemElement>, Framework::CSTLUnorderedMapAllocatorInf> >::rehash(unsigned long)(param_5,uVar11);
      uVar11 = param_5[1];
      if ((uVar11 - 1 & uVar11) == 0) {
        unaff_x24 = uVar11 - 1 & uVar5;
      }
      else {
        uVar10 = 0;
        if (uVar11 != 0) {
          uVar10 = uVar5 / uVar11;
        }
        unaff_x24 = uVar5 - uVar10 * uVar11;
      }
    }
    plVar8 = *(long **)(*param_5 + unaff_x24 * 8);
    if (plVar8 == (long *)0x0) {
      plVar8 = param_5 + 2;
      *plVar7 = *plVar8;
      *plVar8 = (long)plVar7;
      *(long **)(*param_5 + unaff_x24 * 8) = plVar8;
      if (*plVar7 != 0) {
        uVar5 = *(ulong *)(*plVar7 + 8);
        if ((uVar11 - 1 & uVar11) == 0) {
          uVar5 = uVar5 & uVar11 - 1;
        }
        else {
          uVar10 = 0;
          if (uVar11 != 0) {
            uVar10 = uVar5 / uVar11;
          }
          uVar5 = uVar5 - uVar10 * uVar11;
        }
        plVar8 = (long *)(*param_5 + uVar5 * 8);
        goto code_r0x01272ee0;
      }
    }
    else {
      *plVar7 = *plVar8;
code_r0x01272ee0:
      *plVar8 = (long)plVar7;
    }
    param_5[3] = param_5[3] + 1;
  }
code_r0x01272ef0:
  CMasterParameterItemElement::~CMasterParameterItemElement()(auStack_ac0);
code_r0x01272ef8:
  Aska::ASON::~ASON()(auStack_f0);
  return;
}

// ==== CMasterParameterBaseSqlite_Simple<CMasterParameterItemElement>::~CMasterParameterBaseSqlite_Simple()
// vaddr 0x15c9fd0 | ghidra 0x16c9fd0 | size 256 | symbol _ZN33CMasterParameterBaseSqlite_SimpleI27CMasterParameterItemElementED2Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN33CMasterParameterBaseSqlite_SimpleI27CMasterParameterItemElementED2Ev(long *param_1)

{
  undefined *puVar1;
  long *plVar2;
  long lVar3;
  
  puVar1 = PTR__ZTV33CMasterParameterBaseSqlite_SimpleI27CMasterParameterItemElementE_02cbe128 +
           0x70;
  *param_1 = (long)(
                   PTR__ZTV33CMasterParameterBaseSqlite_SimpleI27CMasterParameterItemElementE_02cbe128
                   + 0x10);
  param_1[2] = (long)puVar1;
  plVar2 = (long *)param_1[0x10];
  while (plVar2 != (long *)0x0) {
    lVar3 = *plVar2;
    if (plVar2[4] != 0) {
      std::__ndk1::__shared_weak_count::__release_shared()();
    }
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar2);
    plVar2 = (long *)lVar3;
  }
  lVar3 = param_1[0xe];
  param_1[0xe] = 0;
  if (lVar3 != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)();
  }
  plVar2 = (long *)param_1[10];
  while (plVar2 != (long *)0x0) {
    lVar3 = *plVar2;
    if (plVar2[4] != 0) {
      std::__ndk1::__shared_weak_count::__release_shared()();
    }
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar2);
    plVar2 = (long *)lVar3;
  }
  lVar3 = param_1[8];
  param_1[8] = 0;
  if (lVar3 != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)();
  }
  plVar2 = (long *)param_1[5];
  while (plVar2 != (long *)0x0) {
    lVar3 = *plVar2;
    if (plVar2[4] != 0) {
      std::__ndk1::__shared_weak_count::__release_shared()();
    }
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar2);
    plVar2 = (long *)lVar3;
  }
  lVar3 = param_1[3];
  param_1[3] = 0;
  if (lVar3 != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)();
  }
  *param_1 = (long)(PTR__ZTV26CMasterParameterBaseSqlite_02cc48f0 + 0x10);
  if ((long *)param_1[1] != (long *)0x0) {
    (**(code **)(*(long *)param_1[1] + 8))();
    param_1[1] = 0;
  }
  return;
}

// ==== CMasterParameterBaseSqlite_Simple<CMasterParameterItemElement>::Initialize()
// vaddr 0x15ca0e8 | ghidra 0x16ca0e8 | size 64 | symbol _ZN33CMasterParameterBaseSqlite_SimpleI27CMasterParameterItemElementE10InitializeEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN33CMasterParameterBaseSqlite_SimpleI27CMasterParameterItemElementE10InitializeEv
               (long *param_1)

{
  long lVar1;
  
  lVar1 = (**(code **)(*param_1 + 0x30))();
  param_1[1] = lVar1;
  if (lVar1 != 0) {
    return;
  }
  (*(code *)PTR__ZN9Framework9gDoAssertEPKciS1_z_02ca3240)(&UNK_027dc023/*"C:\BAS_Submission\Client\Project\Android\BASAndroid.NativeActivity\..\..\..\Source\Game/Parameter/Master/MasterParameterBaseSqlite.h"*/,0x165,&UNK_02845d79/*"m_pSqlConnector is null."*/);
  return;
}

// ==== CMasterParameterBaseSqlite_Simple<CMasterParameterItemElement>::Deserialize(Aska::ASON::AValue::AMap const*)
// vaddr 0x15ca170 | ghidra 0x16ca170 | size 108 | symbol _ZN33CMasterParameterBaseSqlite_SimpleI27CMasterParameterItemElementE11DeserializeEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
bool _ZN33CMasterParameterBaseSqlite_SimpleI27CMasterParameterItemElementE11DeserializeEPKN4Aska4ASON6AValue4AMapE
               (long *param_1,long param_2)

{
  long lVar1;
  
  if (param_2 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dc023/*"C:\BAS_Submission\Client\Project\Android\BASAndroid.NativeActivity\..\..\..\Source\Game/Parameter/Master/MasterParameterBaseSqlite.h"*/,0x200,&UNK_027dc58a/*"apParser is null."*/);
  }
  lVar1 = (**(code **)(param_1[2] + 0x30))(param_1 + 2,param_2);
  if (lVar1 != 0) {
    (**(code **)(*param_1 + 0x48))(param_1,param_1 + 3,lVar1 + 8);
  }
  return lVar1 != 0;
}

// ==== CMasterParameterBaseSqlite_Simple<CMasterParameterItemElement>::ReleaseParameter(char const*)
// vaddr 0x15ca1dc | ghidra 0x16ca1dc | size 600 | symbol _ZN33CMasterParameterBaseSqlite_SimpleI27CMasterParameterItemElementE16ReleaseParameterEPKc | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN33CMasterParameterBaseSqlite_SimpleI27CMasterParameterItemElementE16ReleaseParameterEPKc
          (long param_1,undefined8 param_2)

{
  ulong uVar1;
  long *plVar2;
  uint uVar3;
  int iVar4;
  undefined8 uVar5;
  ulong uVar6;
  long lVar7;
  ulong uVar8;
  ulong uVar9;
  ulong uVar10;
  long *plVar11;
  ulong uVar12;
  long *plVar13;
  long lVar14;
  undefined1 auStack_30 [16];
  
  Framework::CHash32::CHash32(char const*)(auStack_30);
  uVar3 = Framework::CHash32::operator unsigned int() const(auStack_30);
  uVar8 = *(ulong *)(param_1 + 0x20);
  if (uVar8 != 0) {
    uVar9 = uVar8 - 1;
    uVar6 = (ulong)uVar3;
    if ((uVar9 & uVar8) == 0) {
      uVar6 = uVar9 & uVar6;
    }
    else {
      uVar10 = 0;
      if (uVar8 != 0) {
        uVar10 = uVar6 / uVar8;
      }
      uVar6 = uVar6 - uVar10 * uVar8;
    }
    plVar13 = *(long **)(*(long *)(param_1 + 0x18) + uVar6 * 8);
    if (plVar13 != (long *)0x0) {
      if ((uVar9 & uVar8) == 0) {
        do {
          plVar13 = (long *)*plVar13;
          if ((plVar13 == (long *)0x0) || ((plVar13[1] & uVar9) != uVar6)) goto code_r0x016ca2b4;
        } while (*(uint *)(plVar13 + 2) != uVar3);
      }
      else {
        do {
          plVar13 = (long *)*plVar13;
          if (plVar13 == (long *)0x0) goto code_r0x016ca2b4;
          uVar9 = 0;
          if (uVar8 != 0) {
            uVar9 = (ulong)plVar13[1] / uVar8;
          }
          if (plVar13[1] - uVar9 * uVar8 != uVar6) goto code_r0x016ca2b4;
        } while (*(uint *)(plVar13 + 2) != uVar3);
      }
      Framework::CHash32::~CHash32()(auStack_30);
      if (plVar13 != (long *)0x0) {
        uVar6 = *(ulong *)(param_1 + 0x20);
        uVar8 = plVar13[1];
        uVar9 = uVar6 - 1;
        uVar10 = uVar9 & uVar6;
        if (uVar10 == 0) {
          uVar8 = uVar9 & uVar8;
        }
        else {
          uVar12 = 0;
          if (uVar6 != 0) {
            uVar12 = uVar8 / uVar6;
          }
          uVar8 = uVar8 - uVar12 * uVar6;
        }
        plVar2 = *(long **)(*(long *)(param_1 + 0x18) + uVar8 * 8);
        do {
          plVar11 = plVar2;
          plVar2 = (long *)*plVar11;
        } while ((long *)*plVar11 != plVar13);
        if (plVar11 != (long *)(param_1 + 0x28)) {
          uVar12 = plVar11[1];
          if (uVar10 == 0) {
            uVar12 = uVar12 & uVar9;
          }
          else {
            uVar1 = 0;
            if (uVar6 != 0) {
              uVar1 = uVar12 / uVar6;
            }
            uVar12 = uVar12 - uVar1 * uVar6;
          }
          if (uVar12 == uVar8) goto code_r0x016ca3bc;
        }
        if (*plVar13 != 0) {
          uVar12 = *(ulong *)(*plVar13 + 8);
          if (uVar10 == 0) {
            uVar12 = uVar12 & uVar9;
          }
          else {
            uVar1 = 0;
            if (uVar6 != 0) {
              uVar1 = uVar12 / uVar6;
            }
            uVar12 = uVar12 - uVar1 * uVar6;
          }
          if (uVar12 == uVar8) goto code_r0x016ca3bc;
        }
        *(undefined8 *)(*(long *)(param_1 + 0x18) + uVar8 * 8) = 0;
code_r0x016ca3bc:
        if (*plVar13 != 0) {
          uVar12 = *(ulong *)(*plVar13 + 8);
          if (uVar10 == 0) {
            uVar12 = uVar12 & uVar9;
          }
          else {
            uVar9 = 0;
            if (uVar6 != 0) {
              uVar9 = uVar12 / uVar6;
            }
            uVar12 = uVar12 - uVar9 * uVar6;
          }
          if (uVar12 != uVar8) {
            *(long **)(*(long *)(param_1 + 0x18) + uVar12 * 8) = plVar11;
          }
        }
        *plVar11 = *plVar13;
        *plVar13 = 0;
        *(long *)(param_1 + 0x30) = *(long *)(param_1 + 0x30) + -1;
        if (plVar13[4] != 0) {
          std::__ndk1::__shared_weak_count::__release_shared()();
        }
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar13);
        return 1;
      }
      goto code_r0x016ca2bc;
    }
  }
code_r0x016ca2b4:
  Framework::CHash32::~CHash32()(auStack_30);
code_r0x016ca2bc:
  uVar5 = (**(code **)(*(long *)(param_1 + 0x10) + 0x18))();
  iVar4 = strcmp(param_2,uVar5);
  if ((iVar4 == 0) && (*(long *)(param_1 + 0x30) != 0)) {
    plVar13 = (long *)*(long *)(param_1 + 0x28);
    while (plVar13 != (long *)0x0) {
      lVar14 = *plVar13;
      if (plVar13[4] != 0) {
        std::__ndk1::__shared_weak_count::__release_shared()();
      }
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar13);
      plVar13 = (long *)lVar14;
    }
    lVar14 = *(long *)(param_1 + 0x20);
    *(undefined8 *)(param_1 + 0x28) = 0;
    if (lVar14 != 0) {
      lVar7 = 0;
      do {
        *(undefined8 *)(*(long *)(param_1 + 0x18) + lVar7 * 8) = 0;
        lVar7 = lVar7 + 1;
      } while (lVar14 != lVar7);
    }
    *(undefined8 *)(param_1 + 0x30) = 0;
  }
  return 1;
}

// ==== CMasterParameterBaseSqlite_Simple<CMasterParameterItemElement>::DeserializeParameter(Framework::CSTLUnorderedMap<unsigned int, std::__ndk1::shared_ptr<CMasterParameterItemElement>, std::__ndk1::hash<unsigned int>, std::__ndk1::equal_to<unsigned int> >&, Aska::ASON::AValue::AArray const*)
// vaddr 0x15ca434 | ghidra 0x16ca434 | size 1020 | symbol _ZN33CMasterParameterBaseSqlite_SimpleI27CMasterParameterItemElementE20DeserializeParameterERN9Framework16CSTLUnorderedMapIjNSt6__ndk110shared_ptrIS0_EENS4_4hashIjEENS4_8equal_toIjEEEEPKN4Aska4ASON6AValue6AArrayE | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN33CMasterParameterBaseSqlite_SimpleI27CMasterParameterItemElementE20DeserializeParameterERN9Framework16CSTLUnorderedMapIjNSt6__ndk110shared_ptrIS0_EENS4_4hashIjEENS4_8equal_toIjEEEEPKN4Aska4ASON6AValue6AArrayE
          (long *param_1,long *param_2,long *param_3)

{
  undefined *puVar1;
  long lVar2;
  uint uVar3;
  undefined8 uVar4;
  uint *puVar5;
  ulong uVar6;
  long *plVar7;
  ulong uVar8;
  ulong uVar9;
  long *plVar10;
  long *plVar11;
  long *plVar12;
  ulong uVar13;
  ulong uVar14;
  ulong uVar15;
  int iVar16;
  undefined1 auVar17 [16];
  undefined1 auStack_70 [16];
  
  if (param_3 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dc023/*"C:\BAS_Submission\Client\Project\Android\BASAndroid.NativeActivity\..\..\..\Source\Game/Parameter/Master/MasterParameterBaseSqlite.h"*/,0x221,&UNK_02845e17/*"apArray is null."*/);
    iVar16 = iRam0000000000000008;
  }
  else {
    iVar16 = (int)param_3[1];
  }
  if (iVar16 != 0) {
    uVar8 = 0;
    puVar1 = PTR__ZTVNSt6__ndk120__shared_ptr_emplaceI27CMasterParameterItemElement18ParameterAllocatorIS1_EEE_02cba4c0
             + 0x10;
    do {
      lVar2 = *param_3 + uVar8 * 0x20;
      if (lVar2 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dc023/*"C:\BAS_Submission\Client\Project\Android\BASAndroid.NativeActivity\..\..\..\Source\Game/Parameter/Master/MasterParameterBaseSqlite.h"*/,0x224,&UNK_0285e8d7/*"pValue is null."*/);
      }
      lVar2 = lVar2 + 8;
      uVar4 = (**(code **)(*param_1 + 0x18))(param_1);
      puVar5 = (uint *)Aska::ASON::AValue::AMap::Get_(char const*)(lVar2,uVar4);
      if (puVar5 != (uint *)0x0) {
        uVar3 = *puVar5;
        uVar14 = (ulong)uVar3;
        uVar4 = (**(code **)(*param_1 + 0x18))(param_1);
        if (uVar3 == 5) {
          auVar17 = std::__ndk1::pair<char*, bool> CParameterParser::GetValue<char*>(Aska::ASON::AValue::AMap const*, char const*)();
          if ((auVar17._8_8_ & 1) != 0) {
            Framework::CHash32::CHash32(char const*)(auStack_70,auVar17._0_8_);
            uVar6 = Framework::CHash32::operator unsigned int() const(auStack_70);
            uVar6 = uVar6 & 0xffffffff;
            Framework::CHash32::~CHash32()(auStack_70);
code_r0x016ca554:
            uVar13 = param_2[1];
            uVar15 = uVar6 & 0xffffffff;
            iVar16 = (int)uVar6;
            if (uVar13 == 0) {
code_r0x016ca5e8:
              plVar7 = (long *)operator new(unsigned long)(0x9e8);
              plVar12 = plVar7 + 3;
              plVar7[2] = 0;
              *plVar7 = (long)puVar1;
              plVar7[1] = 0;
              CMasterParameterItemElement::CMasterParameterItemElement()(plVar12);
              uVar6 = param_2[1];
              if (uVar6 == 0) {
code_r0x016ca694:
                plVar10 = (long *)Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(0x28,&UNK_027dc2d5/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_UnorderedMap.h"*/,0x1c);
                if (plVar10 == (long *)0x0) {
                  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
                }
                *(int *)(plVar10 + 2) = iVar16;
                plVar10[3] = (long)plVar12;
                plVar10[4] = (long)plVar7;
                std::__ndk1::__shared_weak_count::__add_shared()(plVar7);
                *plVar10 = 0;
                plVar10[1] = uVar15;
                if ((uVar6 == 0) ||
                   (*(float *)(param_2 + 4) * (float)uVar6 < (float)(param_2[3] + 1))) {
                  if (uVar6 < 3) {
                    uVar14 = 1;
                  }
                  else {
                    uVar14 = (ulong)((uVar6 - 1 & uVar6) != 0);
                  }
                  uVar14 = uVar14 | uVar6 << 1;
                  uVar6 = (ulong)((float)(param_2[3] + 1) / *(float *)(param_2 + 4));
                  if (uVar6 <= uVar14) {
                    uVar6 = uVar14;
                  }
                  std::__ndk1::__hash_table<std::__ndk1::__hash_value_type<unsigned int, std::__ndk1::shared_ptr<CMasterParameterItemElement> >, std::__ndk1::__unordered_map_hasher<unsigned int, std::__ndk1::__hash_value_type<unsigned int, std::__ndk1::shared_ptr<CMasterParameterItemElement> >, std::__ndk1::hash<unsigned int>, true>, std::__ndk1::__unordered_map_equal<unsigned int, std::__ndk1::__hash_value_type<unsigned int, std::__ndk1::shared_ptr<CMasterParameterItemElement> >, std::__ndk1::equal_to<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__hash_value_type<unsigned int, std::__ndk1::shared_ptr<CMasterParameterItemElement> >, Framework::CSTLUnorderedMapAllocatorInf> >::rehash(unsigned long)(param_2,uVar6);
                  uVar6 = param_2[1];
                  if ((uVar6 - 1 & uVar6) == 0) {
                    uVar14 = uVar6 - 1 & uVar15;
                  }
                  else {
                    uVar14 = 0;
                    if (uVar6 != 0) {
                      uVar14 = uVar15 / uVar6;
                    }
                    uVar14 = uVar15 - uVar14 * uVar6;
                  }
                }
                plVar11 = *(long **)(*param_2 + uVar14 * 8);
                if (plVar11 == (long *)0x0) {
                  *plVar10 = param_2[2];
                  param_2[2] = (long)plVar10;
                  *(long **)(*param_2 + uVar14 * 8) = param_2 + 2;
                  if (*plVar10 != 0) {
                    uVar14 = *(ulong *)(*plVar10 + 8);
                    if ((uVar6 - 1 & uVar6) == 0) {
                      uVar14 = uVar14 & uVar6 - 1;
                    }
                    else {
                      uVar13 = 0;
                      if (uVar6 != 0) {
                        uVar13 = uVar14 / uVar6;
                      }
                      uVar14 = uVar14 - uVar13 * uVar6;
                    }
                    plVar11 = (long *)(*param_2 + uVar14 * 8);
                    goto code_r0x016ca7bc;
                  }
                }
                else {
                  *plVar10 = *plVar11;
code_r0x016ca7bc:
                  *plVar11 = (long)plVar10;
                }
                param_2[3] = param_2[3] + 1;
              }
              else {
                uVar13 = uVar6 - 1;
                if ((uVar13 & uVar6) == 0) {
                  uVar14 = uVar13 & uVar15;
                }
                else {
                  uVar14 = 0;
                  if (uVar6 != 0) {
                    uVar14 = uVar15 / uVar6;
                  }
                  uVar14 = uVar15 - uVar14 * uVar6;
                }
                plVar10 = *(long **)(*param_2 + uVar14 * 8);
                if (plVar10 == (long *)0x0) goto code_r0x016ca694;
                if ((uVar13 & uVar6) == 0) {
                  do {
                    plVar10 = (long *)*plVar10;
                    if ((plVar10 == (long *)0x0) || ((plVar10[1] & uVar13) != uVar14))
                    goto code_r0x016ca694;
                  } while ((int)plVar10[2] != iVar16);
                }
                else {
                  do {
                    plVar10 = (long *)*plVar10;
                    if (plVar10 == (long *)0x0) goto code_r0x016ca694;
                    uVar13 = 0;
                    if (uVar6 != 0) {
                      uVar13 = (ulong)plVar10[1] / uVar6;
                    }
                    if (plVar10[1] - uVar13 * uVar6 != uVar14) goto code_r0x016ca694;
                  } while (*(int *)(plVar10 + 2) != iVar16);
                }
              }
              (**(code **)plVar7[3])(plVar12);
              std::__ndk1::__shared_weak_count::__release_shared()(plVar7);
            }
            else {
              uVar6 = uVar13 - 1;
              if ((uVar6 & uVar13) == 0) {
                uVar9 = uVar6 & uVar15;
              }
              else {
                uVar9 = 0;
                if (uVar13 != 0) {
                  uVar9 = uVar15 / uVar13;
                }
                uVar9 = uVar15 - uVar9 * uVar13;
              }
              plVar12 = *(long **)(*param_2 + uVar9 * 8);
              if (plVar12 == (long *)0x0) goto code_r0x016ca5e8;
              if ((uVar6 & uVar13) == 0) {
                do {
                  plVar12 = (long *)*plVar12;
                  if ((plVar12 == (long *)0x0) || ((plVar12[1] & uVar6) != uVar9))
                  goto code_r0x016ca5e8;
                } while ((int)plVar12[2] != iVar16);
              }
              else {
                do {
                  plVar12 = (long *)*plVar12;
                  if (plVar12 == (long *)0x0) goto code_r0x016ca5e8;
                  uVar6 = 0;
                  if (uVar13 != 0) {
                    uVar6 = (ulong)plVar12[1] / uVar13;
                  }
                  if (plVar12[1] - uVar6 * uVar13 != uVar9) goto code_r0x016ca5e8;
                } while (*(int *)(plVar12 + 2) != iVar16);
              }
              if (plVar12 == (long *)0x0) goto code_r0x016ca5e8;
              plVar12 = (long *)plVar12[3];
            }
            (**(code **)(*plVar12 + 8))(plVar12,lVar2);
          }
        }
        else {
          uVar6 = std::__ndk1::pair<unsigned int, bool> CParameterParser::GetValue<unsigned int>(Aska::ASON::AValue::AMap const*, char const*)(lVar2,uVar4);
          if ((uVar6 >> 0x20 & 1) != 0) goto code_r0x016ca554;
        }
      }
      uVar3 = (int)uVar8 + 1;
      uVar8 = (ulong)uVar3;
    } while (uVar3 < *(uint *)(param_3 + 1));
  }
  return 1;
}

// ==== non-virtual thunk to CMasterParameterBaseSqlite_Simple<CMasterParameterItemElement>::Initialize()
// vaddr 0x15ca860 | ghidra 0x16ca860 | size 68 | symbol _ZThn16_N33CMasterParameterBaseSqlite_SimpleI27CMasterParameterItemElementE10InitializeEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZThn16_N33CMasterParameterBaseSqlite_SimpleI27CMasterParameterItemElementE10InitializeEv
               (long param_1)

{
  long lVar1;
  
  lVar1 = (**(code **)(*(long *)(param_1 + -0x10) + 0x30))((long *)(param_1 + -0x10));
  *(long *)(param_1 + -8) = lVar1;
  if (lVar1 != 0) {
    return;
  }
  (*(code *)PTR__ZN9Framework9gDoAssertEPKciS1_z_02ca3240)(&UNK_027dc023/*"C:\BAS_Submission\Client\Project\Android\BASAndroid.NativeActivity\..\..\..\Source\Game/Parameter/Master/MasterParameterBaseSqlite.h"*/,0x165,&UNK_02845d79/*"m_pSqlConnector is null."*/);
  return;
}

// ==== non-virtual thunk to CMasterParameterBaseSqlite_Simple<CMasterParameterItemElement>::Deserialize(Aska::ASON::AValue::AMap const*)
// vaddr 0x15ca8b0 | ghidra 0x16ca8b0 | size 108 | symbol _ZThn16_N33CMasterParameterBaseSqlite_SimpleI27CMasterParameterItemElementE11DeserializeEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
bool _ZThn16_N33CMasterParameterBaseSqlite_SimpleI27CMasterParameterItemElementE11DeserializeEPKN4Aska4ASON6AValue4AMapE
               (long *param_1,long param_2)

{
  long lVar1;
  
  if (param_2 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dc023/*"C:\BAS_Submission\Client\Project\Android\BASAndroid.NativeActivity\..\..\..\Source\Game/Parameter/Master/MasterParameterBaseSqlite.h"*/,0x200,&UNK_027dc58a/*"apParser is null."*/);
  }
  lVar1 = (**(code **)(*param_1 + 0x30))(param_1,param_2);
  if (lVar1 != 0) {
    (**(code **)(param_1[-2] + 0x48))(param_1 + -2,param_1 + 1,lVar1 + 8);
  }
  return lVar1 != 0;
}

// ==== non-virtual thunk to CMasterParameterBaseSqlite_Simple<CMasterParameterItemElement>::ReleaseParameter(char const*)
// vaddr 0x15ca91c | ghidra 0x16ca91c | size 8 | symbol _ZThn16_N33CMasterParameterBaseSqlite_SimpleI27CMasterParameterItemElementE16ReleaseParameterEPKc | lib libSOA-3.7.0.so | 2026-10-08
void _ZThn16_N33CMasterParameterBaseSqlite_SimpleI27CMasterParameterItemElementE16ReleaseParameterEPKc
               (long param_1)

{
  (*(code *)
    PTR__ZN33CMasterParameterBaseSqlite_SimpleI27CMasterParameterItemElementE16ReleaseParameterEPKc_02c9d010
  )(param_1 + -0x10);
  return;
}

// ==== CMasterParameterBaseSqlite_Simple<CMasterParameterItemElement>::~CMasterParameterBaseSqlite_Simple()
// vaddr 0x15ca924 | ghidra 0x16ca924 | size 4 | symbol _ZN33CMasterParameterBaseSqlite_SimpleI27CMasterParameterItemElementED0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN33CMasterParameterBaseSqlite_SimpleI27CMasterParameterItemElementED0Ev(void)

{
  code *pcVar1;
  
                    /* WARNING: Does not return */
  pcVar1 = (code *)SoftwareBreakpoint(1,0x16ca928);
  (*pcVar1)();
}

// ==== non-virtual thunk to CMasterParameterBaseSqlite_Simple<CMasterParameterItemElement>::~CMasterParameterBaseSqlite_Simple()
// vaddr 0x15ca928 | ghidra 0x16ca928 | size 8 | symbol _ZThn16_N33CMasterParameterBaseSqlite_SimpleI27CMasterParameterItemElementED1Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZThn16_N33CMasterParameterBaseSqlite_SimpleI27CMasterParameterItemElementED1Ev(long param_1)

{
  (*(code *)PTR__ZN33CMasterParameterBaseSqlite_SimpleI27CMasterParameterItemElementED2Ev_02cad898)
            (param_1 + -0x10);
  return;
}

// ==== non-virtual thunk to CMasterParameterBaseSqlite_Simple<CMasterParameterItemElement>::~CMasterParameterBaseSqlite_Simple()
// vaddr 0x15ca930 | ghidra 0x16ca930 | size 4 | symbol _ZThn16_N33CMasterParameterBaseSqlite_SimpleI27CMasterParameterItemElementED0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZThn16_N33CMasterParameterBaseSqlite_SimpleI27CMasterParameterItemElementED0Ev(void)

{
  code *pcVar1;
  
                    /* WARNING: Does not return */
  pcVar1 = (code *)SoftwareBreakpoint(1,0x16ca934);
  (*pcVar1)();
}

// ==== CSimpleSqliteConnector<MasterDB::CItem, Aska::Yayoi::TEntity_Slave<Aska::Yayoi::SQLiteDriver, MasterDB::CItem, Aska::Yayoi::NoCache> >::~CSimpleSqliteConnector()
// vaddr 0x15ca934 | ghidra 0x16ca934 | size 4 | symbol _ZN22CSimpleSqliteConnectorIN8MasterDB5CItemEN4Aska5Yayoi13TEntity_SlaveINS3_12SQLiteDriverES1_NS3_7NoCacheEEEED2Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN22CSimpleSqliteConnectorIN8MasterDB5CItemEN4Aska5Yayoi13TEntity_SlaveINS3_12SQLiteDriverES1_NS3_7NoCacheEEEED2Ev
               (void)

{
  return;
}

// ==== CSimpleSqliteConnector<MasterDB::CItem, Aska::Yayoi::TEntity_Slave<Aska::Yayoi::SQLiteDriver, MasterDB::CItem, Aska::Yayoi::NoCache> >::~CSimpleSqliteConnector()
// vaddr 0x15ca938 | ghidra 0x16ca938 | size 4 | symbol _ZN22CSimpleSqliteConnectorIN8MasterDB5CItemEN4Aska5Yayoi13TEntity_SlaveINS3_12SQLiteDriverES1_NS3_7NoCacheEEEED0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN22CSimpleSqliteConnectorIN8MasterDB5CItemEN4Aska5Yayoi13TEntity_SlaveINS3_12SQLiteDriverES1_NS3_7NoCacheEEEED0Ev
               (void)

{
  (*(code *)PTR__ZdlPv_02ca4758)();
  return;
}

// ==== CSimpleSqliteConnector<MasterDB::CItem, Aska::Yayoi::TEntity_Slave<Aska::Yayoi::SQLiteDriver, MasterDB::CItem, Aska::Yayoi::NoCache> >::Open(char const*)
// vaddr 0x15ca93c | ghidra 0x16ca93c | size 4 | symbol _ZN22CSimpleSqliteConnectorIN8MasterDB5CItemEN4Aska5Yayoi13TEntity_SlaveINS3_12SQLiteDriverES1_NS3_7NoCacheEEEE4OpenEPKc | lib libSOA-3.7.0.so | 2026-10-08
void _ZN22CSimpleSqliteConnectorIN8MasterDB5CItemEN4Aska5Yayoi13TEntity_SlaveINS3_12SQLiteDriverES1_NS3_7NoCacheEEEE4OpenEPKc
               (void)

{
  return;
}

// ==== CSimpleSqliteConnector<MasterDB::CItem, Aska::Yayoi::TEntity_Slave<Aska::Yayoi::SQLiteDriver, MasterDB::CItem, Aska::Yayoi::NoCache> >::Close()
// vaddr 0x15ca940 | ghidra 0x16ca940 | size 4 | symbol _ZN22CSimpleSqliteConnectorIN8MasterDB5CItemEN4Aska5Yayoi13TEntity_SlaveINS3_12SQLiteDriverES1_NS3_7NoCacheEEEE5CloseEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN22CSimpleSqliteConnectorIN8MasterDB5CItemEN4Aska5Yayoi13TEntity_SlaveINS3_12SQLiteDriverES1_NS3_7NoCacheEEEE5CloseEv
               (void)

{
  return;
}

// ==== CSimpleSqliteConnector<MasterDB::CItem, Aska::Yayoi::TEntity_Slave<Aska::Yayoi::SQLiteDriver, MasterDB::CItem, Aska::Yayoi::NoCache> >::QueryToResultObject(unsigned int, Aska::Yayoi::QueryParam*, unsigned int, Aska::Yayoi::TEntityObject<Aska::Yayoi::SQLiteDriver>&)
// vaddr 0x15ca944 | ghidra 0x16ca944 | size 236 | symbol _ZN22CSimpleSqliteConnectorIN8MasterDB5CItemEN4Aska5Yayoi13TEntity_SlaveINS3_12SQLiteDriverES1_NS3_7NoCacheEEEE19QueryToResultObjectEjPNS3_10QueryParamEjRNS3_13TEntityObjectIS5_EE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN22CSimpleSqliteConnectorIN8MasterDB5CItemEN4Aska5Yayoi13TEntity_SlaveINS3_12SQLiteDriverES1_NS3_7NoCacheEEEE19QueryToResultObjectEjPNS3_10QueryParamEjRNS3_13TEntityObjectIS5_EE
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
     (puVar1 = PTR__ZZNK22CSimpleSqliteConnectorIN8MasterDB5CItemEN4Aska5Yayoi13TEntity_SlaveINS3_12SQLiteDriverES1_NS3_7NoCacheEEEE12CLocalEntityIS1_E8GetQueryEiE7queries_02cbeb58
               + (long)param_2 * 0x20, puVar1 != (undefined *)0x0)) {
    uVar4 = (**(code **)(*(long *)(*(long *)puVar2 + 0x40) + 0x28))
                      ((long *)(*(long *)puVar2 + 0x40),0,0);
    Aska::Yayoi::SQLiteDriver::DoOpen(Aska::Yayoi::Entity::Mode, char const*, Aska::Yayoi::DBAddress const*)(&lStack_48,uVar3,0,0,uVar4);
    if ((-1 < lStack_48) && (lVar5 = char const* Aska::Yayoi::SQLiteDriver::BuildQuery<CSimpleSqliteConnector<MasterDB::CItem, Aska::Yayoi::TEntity_Slave<Aska::Yayoi::SQLiteDriver, MasterDB::CItem, Aska::Yayoi::NoCache> >::CLocalEntity<MasterDB::CItem> >(Aska::Yayoi::QueryObject const*, CSimpleSqliteConnector<MasterDB::CItem, Aska::Yayoi::TEntity_Slave<Aska::Yayoi::SQLiteDriver, MasterDB::CItem, Aska::Yayoi::NoCache> >::CLocalEntity<MasterDB::CItem> const*, char const*)(uVar3,puVar1,param_1 + 0x10,0), lVar5 != 0)) {
      Aska::Yayoi::SQLiteDriver::Find(char const*, Aska::Yayoi::QueryParam const*, unsigned long, Aska::Yayoi::SQLiteDriver::EntityObject*)(&lStack_48,uVar3,lVar5,param_3,param_4,param_5);
    }
  }
  return;
}

// ==== CSimpleSqliteConnector<MasterDB::CItem, Aska::Yayoi::TEntity_Slave<Aska::Yayoi::SQLiteDriver, MasterDB::CItem, Aska::Yayoi::NoCache> >::QueryToMsgPack(unsigned int, unsigned int, Aska::TSharedArray<signed char>&, long&)
// vaddr 0x15caa30 | ghidra 0x16caa30 | size 536 | symbol _ZN22CSimpleSqliteConnectorIN8MasterDB5CItemEN4Aska5Yayoi13TEntity_SlaveINS3_12SQLiteDriverES1_NS3_7NoCacheEEEE14QueryToMsgPackEjjRNS2_12TSharedArrayIaEERl | lib libSOA-3.7.0.so | 2026-10-08
void _ZN22CSimpleSqliteConnectorIN8MasterDB5CItemEN4Aska5Yayoi13TEntity_SlaveINS3_12SQLiteDriverES1_NS3_7NoCacheEEEE14QueryToMsgPackEjjRNS2_12TSharedArrayIaEERl
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
code_r0x016caae8:
    uVar7 = 1;
  }
  else {
    if (param_2 == 2) {
      snprintf(param_1 + 3,0x100,&UNK_027e6d32/*"%u"*/,param_3);
      lVar5 = 1;
      goto code_r0x016caae8;
    }
    lVar5 = 0;
    uVar7 = 0;
  }
  plStack_e8 = param_1 + 3;
  uStack_f8 = *(undefined8 *)
               (
               PTR__ZZNK22CSimpleSqliteConnectorIN8MasterDB5CItemEN4Aska5Yayoi13TEntity_SlaveINS3_12SQLiteDriverES1_NS3_7NoCacheEEEE12CLocalEntityIS1_E15GetPrimaryKeiesEvE5keies_02cb8bc8
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
code_r0x016cab90:
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
        goto code_r0x016cab90;
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
    if (iVar1 + -1 != 0) goto code_r0x016cac0c;
  }
  if (lStack_108 != 0) {
    operator delete[](void*)();
  }
  if (piStack_100 != (int *)0x0) {
    Aska::TSharedPointerCode::DeleteCounter(int*)();
  }
code_r0x016cac0c:
  piStack_100 = (int *)0x0;
  Aska::Yayoi::EntityCache::~EntityCache()(auStack_70);
  Aska::Yayoi::SQLiteDriver::EntityObject::~EntityObject()(auStack_d0);
  CSqliteTransaction::rMutex()(lVar4 + 0x40);
  Framework::CMutex::Unlock()();
  return;
}

// ==== CSimpleSqliteConnector<MasterDB::CItem, Aska::Yayoi::TEntity_Slave<Aska::Yayoi::SQLiteDriver, MasterDB::CItem, Aska::Yayoi::NoCache> >::QueryToMsgPack(char const*, Aska::TSharedArray<signed char>&, long&, Aska::Yayoi::QueryParam*, unsigned int)
// vaddr 0x15cac48 | ghidra 0x16cac48 | size 388 | symbol _ZN22CSimpleSqliteConnectorIN8MasterDB5CItemEN4Aska5Yayoi13TEntity_SlaveINS3_12SQLiteDriverES1_NS3_7NoCacheEEEE14QueryToMsgPackEPKcRNS2_12TSharedArrayIaEERlPNS3_10QueryParamEj | lib libSOA-3.7.0.so | 2026-10-08
void _ZN22CSimpleSqliteConnectorIN8MasterDB5CItemEN4Aska5Yayoi13TEntity_SlaveINS3_12SQLiteDriverES1_NS3_7NoCacheEEEE14QueryToMsgPackEPKcRNS2_12TSharedArrayIaEERlPNS3_10QueryParamEj
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
code_r0x016cad14:
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
        goto code_r0x016cad14;
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
    if (iVar1 + -1 != 0) goto code_r0x016cad90;
  }
  if (lStack_e0 != 0) {
    operator delete[](void*)();
  }
  if (piStack_d8 != (int *)0x0) {
    Aska::TSharedPointerCode::DeleteCounter(int*)();
  }
code_r0x016cad90:
  piStack_d8 = (int *)0x0;
  Aska::Yayoi::EntityCache::~EntityCache()(auStack_70);
  Aska::Yayoi::SQLiteDriver::EntityObject::~EntityObject()(auStack_d0);
  CSqliteTransaction::rMutex()(lVar5 + 0x40);
  Framework::CMutex::Unlock()();
  return;
}

// ==== CSimpleSqliteConnector<MasterDB::CItem, Aska::Yayoi::TEntity_Slave<Aska::Yayoi::SQLiteDriver, MasterDB::CItem, Aska::Yayoi::NoCache> >::QueryToResultObject(char const*, Aska::Yayoi::QueryParam*, unsigned int, Aska::Yayoi::TEntityObject<Aska::Yayoi::SQLiteDriver>&)
// vaddr 0x15cadcc | ghidra 0x16cadcc | size 92 | symbol _ZN22CSimpleSqliteConnectorIN8MasterDB5CItemEN4Aska5Yayoi13TEntity_SlaveINS3_12SQLiteDriverES1_NS3_7NoCacheEEEE19QueryToResultObjectEPKcPNS3_10QueryParamEjRNS3_13TEntityObjectIS5_EE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN22CSimpleSqliteConnectorIN8MasterDB5CItemEN4Aska5Yayoi13TEntity_SlaveINS3_12SQLiteDriverES1_NS3_7NoCacheEEEE19QueryToResultObjectEPKcPNS3_10QueryParamEjRNS3_13TEntityObjectIS5_EE
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

// ==== CSimpleSqliteConnector<MasterDB::CItem, Aska::Yayoi::TEntity_Slave<Aska::Yayoi::SQLiteDriver, MasterDB::CItem, Aska::Yayoi::NoCache> >::CLocalEntity<MasterDB::CItem>::GetQuery(int) const
// vaddr 0x15cae28 | ghidra 0x16cae28 | size 28 | symbol _ZNK22CSimpleSqliteConnectorIN8MasterDB5CItemEN4Aska5Yayoi13TEntity_SlaveINS3_12SQLiteDriverES1_NS3_7NoCacheEEEE12CLocalEntityIS1_E8GetQueryEi | lib libSOA-3.7.0.so | 2026-10-08
undefined *
_ZNK22CSimpleSqliteConnectorIN8MasterDB5CItemEN4Aska5Yayoi13TEntity_SlaveINS3_12SQLiteDriverES1_NS3_7NoCacheEEEE12CLocalEntityIS1_E8GetQueryEi
          (undefined8 param_1,int param_2)

{
  undefined *puVar1;
  
  puVar1 = (undefined *)0x0;
  if (param_2 < 3) {
    puVar1 = PTR__ZZNK22CSimpleSqliteConnectorIN8MasterDB5CItemEN4Aska5Yayoi13TEntity_SlaveINS3_12SQLiteDriverES1_NS3_7NoCacheEEEE12CLocalEntityIS1_E8GetQueryEiE7queries_02cbeb58
             + (long)param_2 * 0x20;
  }
  return puVar1;
}

// ==== char const* Aska::Yayoi::SQLiteDriver::BuildQuery<CSimpleSqliteConnector<MasterDB::CItem, Aska::Yayoi::TEntity_Slave<Aska::Yayoi::SQLiteDriver, MasterDB::CItem, Aska::Yayoi::NoCache> >::CLocalEntity<MasterDB::CItem> >(Aska::Yayoi::QueryObject const*, CSimpleSqliteConnector<MasterDB::CItem, Aska::Yayoi::TEntity_Slave<Aska::Yayoi::SQLiteDriver, MasterDB::CItem, Aska::Yayoi::NoCache> >::CLocalEntity<MasterDB::CItem> const*, char const*)
// vaddr 0x15cae44 | ghidra 0x16cae44 | size 360 | symbol _ZN4Aska5Yayoi12SQLiteDriver10BuildQueryIN22CSimpleSqliteConnectorIN8MasterDB5CItemENS0_13TEntity_SlaveIS1_S5_NS0_7NoCacheEEEE12CLocalEntityIS5_EEEEPKcPKNS0_11QueryObjectEPKT_SD_ | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska5Yayoi12SQLiteDriver10BuildQueryIN22CSimpleSqliteConnectorIN8MasterDB5CItemENS0_13TEntity_SlaveIS1_S5_NS0_7NoCacheEEEE12CLocalEntityIS5_EEEEPKcPKNS0_11QueryObjectEPKT_SD_
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
    puVar3 = &UNK_02846002/*"master_item"*/;
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

// ==== CMasterParameterBaseSqlite_Simple<CMasterParameterItemElement>::ParameterByQuery(char const*, Framework::CSTLUnorderedMap<unsigned int, CMasterParameterItemElement, std::__ndk1::hash<unsigned int>, std::__ndk1::equal_to<unsigned int> >&, Aska::Yayoi::QueryParam*, unsigned int) const
// vaddr 0x16c6d44 | ghidra 0x17c6d44 | size 288 | symbol _ZNK33CMasterParameterBaseSqlite_SimpleI27CMasterParameterItemElementE16ParameterByQueryEPKcRN9Framework16CSTLUnorderedMapIjS0_NSt6__ndk14hashIjEENS6_8equal_toIjEEEEPN4Aska5Yayoi10QueryParamEj | lib libSOA-3.7.0.so | 2026-10-08
void _ZNK33CMasterParameterBaseSqlite_SimpleI27CMasterParameterItemElementE16ParameterByQueryEPKcRN9Framework16CSTLUnorderedMapIjS0_NSt6__ndk14hashIjEENS6_8equal_toIjEEEEPN4Aska5Yayoi10QueryParamEj
               (long *param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               undefined4 param_5)

{
  int iVar1;
  char cVar2;
  bool bVar3;
  ulong uVar4;
  long *plVar5;
  long lStack_50;
  int *piStack_48;
  long lStack_38;
  
  uVar4 = (**(code **)(*param_1 + 0x28))();
  if ((uVar4 & 1) == 0) {
    return;
  }
  plVar5 = (long *)param_1[1];
  if (plVar5 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dc023/*"C:\BAS_Submission\Client\Project\Android\BASAndroid.NativeActivity\..\..\..\Source\Game/Parameter/Master/MasterParameterBaseSqlite.h"*/,0x4d,&UNK_027dc0a8/*"m_pConnector is null."*/);
  }
  (**(code **)(*plVar5 + 0x10))(plVar5,&UNK_027dc00a/*"sqlite/basmaster.sqlite3"*/);
  lStack_50 = 0;
  piStack_48 = (int *)0x0;
  lStack_38 = 0;
  (**(code **)(*plVar5 + 0x30))(plVar5,param_2,&lStack_50,&lStack_38,param_4,param_5);
  if (0 < lStack_38) {
    void CMasterParameterBaseSqlite::DeserializeMsgPack<CMasterParameterItemElement>(Aska::TSharedArray<signed char> const&, long const&, CMasterParameterItemElement*, Framework::CSTLUnorderedMap<unsigned int, CMasterParameterItemElement, std::__ndk1::hash<unsigned int>, std::__ndk1::equal_to<unsigned int> >*) const(param_1,&lStack_50,&lStack_38,0,param_3);
  }
  if (piStack_48 != (int *)0x0) {
    do {
      iVar1 = *piStack_48;
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piStack_48,0x10);
      if (bVar3) {
        *piStack_48 = iVar1 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    if (iVar1 + -1 != 0) goto code_r0x017c6e38;
  }
  if (lStack_50 != 0) {
    operator delete[](void*)();
  }
  if (piStack_48 != (int *)0x0) {
    Aska::TSharedPointerCode::DeleteCounter(int*)();
  }
code_r0x017c6e38:
  lStack_50 = 0;
  (**(code **)(*plVar5 + 0x18))(plVar5);
  return;
}

// ==== CMasterParameterBaseSqlite_Simple<CMasterParameterItemElement>::ParameterFromIdList(Framework::CSTLVector<unsigned int> const&, Framework::CSTLUnorderedMap<unsigned int, CMasterParameterItemElement, std::__ndk1::hash<unsigned int>, std::__ndk1::equal_to<unsigned int> >&, char const*) const
// vaddr 0x16d16b0 | ghidra 0x17d16b0 | size 2072 | symbol _ZNK33CMasterParameterBaseSqlite_SimpleI27CMasterParameterItemElementE19ParameterFromIdListERKN9Framework10CSTLVectorIjEERNS2_16CSTLUnorderedMapIjS0_NSt6__ndk14hashIjEENS8_8equal_toIjEEEEPKc | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Removing unreachable block (ram,0x017d1bcc) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZNK33CMasterParameterBaseSqlite_SimpleI27CMasterParameterItemElementE19ParameterFromIdListERKN9Framework10CSTLVectorIjEERNS2_16CSTLUnorderedMapIjS0_NSt6__ndk14hashIjEENS8_8equal_toIjEEEEPKc
               (long *param_1,long *param_2,undefined8 param_3,long param_4)

{
  undefined4 *puVar1;
  ulong uVar2;
  undefined *puVar3;
  uint7 uVar4;
  bool bVar5;
  byte bVar6;
  undefined8 uVar7;
  ulong uVar8;
  int *piVar9;
  ulong uVar10;
  long lVar11;
  int **ppiVar12;
  int *piVar13;
  int *piVar14;
  int **ppiVar15;
  int *piVar16;
  ulong uVar17;
  ulong uVar18;
  ulong uVar19;
  byte bStack_f8;
  undefined6 uStack_f7;
  undefined1 uStack_f1;
  undefined1 uStack_f0;
  undefined6 uStack_ef;
  undefined1 uStack_e9;
  ulong uStack_e8;
  int *piStack_e0;
  ulong uStack_d8;
  ulong uStack_d0;
  int *piStack_c0;
  ulong uStack_b8;
  ulong uStack_b0;
  int *piStack_a0;
  ulong uStack_98;
  ulong uStack_90;
  int *piStack_80;
  ulong uStack_78;
  ulong uStack_70;
  
  if (*param_2 == param_2[1]) {
    return;
  }
  uStack_e8 = 0;
  bStack_f8 = 0x1c;
  uStack_f7 = _UNK_027f4b62;
  uStack_f1 = (undefined1)_UNK_027f4b68;
  uStack_f0 = (undefined1)((ushort)_UNK_027f4b68 >> 8);
  uStack_ef = _UNK_027f4b6a;
  uStack_e9 = 0;
  uVar7 = (**(code **)(param_1[2] + 0x18))();
  uVar8 = strlen();
  if (uVar8 < 8 || uVar8 - 8 == 0) {
    if (uVar8 != 0) {
      memcpy(&uStack_e9,uVar7,uVar8);
      bStack_f8 = (char)(uVar8 + 0xe) * '\x02';
      *(undefined1 *)(((ulong)&bStack_f8 | 1) + uVar8 + 0xe) = 0;
    }
  }
  else {
    string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&bStack_f8,0x16,uVar8 - 8,0xe,0xe,0,uVar8,uVar7);
  }
  uStack_d0 = uStack_e8;
  bVar6 = bStack_f8;
  uStack_d8 = CONCAT17(uStack_e9,CONCAT61(uStack_ef,uStack_f0));
  uVar4 = CONCAT61(uStack_f7,bStack_f8);
  piStack_e0 = (int *)CONCAT17(uStack_f1,uVar4);
  uStack_f0 = 0;
  uStack_ef = 0;
  uStack_e9 = 0;
  uStack_e8 = 0;
  bStack_f8 = 0;
  uStack_f7 = 0;
  uStack_f1 = 0;
  if ((bVar6 & 1) == 0) {
    lVar11 = 0x16;
    piVar16 = (int *)((ulong)uVar4 & 0xff);
  }
  else {
    lVar11 = ((ulong)piStack_e0 & 0xfffffffffffffffe) - 1;
    piVar16 = piStack_e0;
  }
  uVar8 = (ulong)(((uint)piVar16 & 0xfe) >> 1);
  if (((ulong)piVar16 & 1) != 0) {
    uVar8 = uStack_d8;
  }
  if (lVar11 - uVar8 < 7) {
    string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&piStack_e0,lVar11,(7 - lVar11) + uVar8,uVar8,uVar8,0,7,&UNK_027f4b71/*" WHERE "*/);
  }
  else {
    uVar19 = (ulong)&piStack_e0 | 1;
    if (((ulong)piVar16 & 1) != 0) {
      uVar19 = uStack_d0;
    }
    puVar1 = (undefined4 *)(uVar19 + uVar8);
    *(undefined1 *)((long)puVar1 + 6) = 0x20;
    *(undefined2 *)(puVar1 + 1) = 0x4552;
    *puVar1 = 0x45485720;
    uVar8 = uVar8 + 7;
    uVar18 = uVar8;
    if ((bVar6 & 1) == 0) {
      uVar18 = (ulong)piStack_e0 >> 8;
      piStack_e0 = (int *)CONCAT71((int7)uVar18,(char)uVar8 * '\x02');
      uVar18 = uStack_d8;
    }
    uStack_d8 = uVar18;
    *(undefined1 *)(uVar19 + uVar8) = 0;
  }
  uStack_b0 = uStack_d0;
  uStack_b8 = uStack_d8;
  piStack_c0 = piStack_e0;
  uStack_d8 = 0;
  uStack_d0 = 0;
  piStack_e0 = (int *)0x0;
  if (param_4 == 0) {
    param_4 = (**(code **)(*param_1 + 0x18))(param_1);
  }
  uVar8 = strlen(param_4);
  if (((ulong)piStack_c0 & 1) == 0) {
    lVar11 = 0x16;
    piVar16 = (int *)((ulong)piStack_c0 & 0xff);
  }
  else {
    lVar11 = ((ulong)piStack_c0 & 0xfffffffffffffffe) - 1;
    piVar16 = piStack_c0;
  }
  uVar19 = (ulong)(((uint)piVar16 & 0xfe) >> 1);
  if (((ulong)piVar16 & 1) != 0) {
    uVar19 = uStack_b8;
  }
  if (lVar11 - uVar19 < uVar8) {
    string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&piStack_c0,lVar11,(uVar8 - lVar11) + uVar19,uVar19,uVar19,0,uVar8,param_4);
  }
  else if (uVar8 != 0) {
    uVar18 = (ulong)&piStack_c0 | 1;
    if (((ulong)piVar16 & 1) != 0) {
      uVar18 = uStack_b0;
    }
    memcpy(uVar18 + uVar19,param_4,uVar8);
    uVar19 = uVar19 + uVar8;
    uVar8 = uVar19;
    if (((ulong)piStack_c0 & 1) == 0) {
      piStack_c0 = (int *)CONCAT71(piStack_c0._1_7_,(char)uVar19 * '\x02');
      uVar8 = uStack_b8;
    }
    uStack_b8 = uVar8;
    *(undefined1 *)(uVar18 + uVar19) = 0;
  }
  uStack_90 = uStack_b0;
  uStack_98 = uStack_b8;
  piVar16 = piStack_c0;
  piStack_c0 = (int *)0x0;
  uStack_b8 = 0;
  uStack_b0 = 0;
  piStack_a0 = piVar16;
  if (((ulong)piVar16 & 1) == 0) {
    lVar11 = 0x16;
    piVar9 = (int *)((ulong)piVar16 & 0xff);
  }
  else {
    lVar11 = ((ulong)piVar16 & 0xfffffffffffffffe) - 1;
    piVar9 = piVar16;
  }
  uVar8 = (ulong)(((uint)piVar9 & 0xfe) >> 1);
  if (((ulong)piVar9 & 1) != 0) {
    uVar8 = uStack_98;
  }
  if (lVar11 - uVar8 < 5) {
    string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&piStack_a0,lVar11,(5 - lVar11) + uVar8,uVar8,uVar8,0,5,&UNK_02876955/*" IN ("*/);
  }
  else {
    uVar19 = (ulong)&piStack_a0 | 1;
    if (((ulong)piVar9 & 1) != 0) {
      uVar19 = uStack_90;
    }
    *(undefined1 *)((undefined4 *)(uVar19 + uVar8) + 1) = 0x28;
    *(undefined4 *)(uVar19 + uVar8) = 0x204e4920;
    uVar8 = uVar8 + 5;
    uVar18 = uVar8;
    if (((ulong)piVar16 & 1) == 0) {
      piStack_a0 = (int *)CONCAT71((int7)((ulong)piVar16 >> 8),(char)uVar8 * '\x02');
      uVar18 = uStack_98;
    }
    uStack_98 = uVar18;
    *(undefined1 *)(uVar19 + uVar8) = 0;
  }
  uStack_70 = uStack_90;
  uStack_78 = uStack_98;
  piStack_80 = piStack_a0;
  piStack_a0 = (int *)0x0;
  uStack_98 = 0;
  uStack_90 = 0;
  if (((ulong)piStack_c0 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_b0);
  }
  if (((ulong)piStack_e0 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_d0);
  }
  if ((bStack_f8 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_e8);
  }
  if (param_2[1] - *param_2 == 0) {
    piVar9 = (int *)0x0;
    piVar16 = (int *)0x0;
  }
  else {
    piVar9 = (int *)Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(param_2[1] - *param_2,&UNK_027dc536/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Vector.h"*/,0x20);
    if (piVar9 == (int *)0x0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
    piVar14 = (int *)param_2[1];
    piVar16 = piVar9;
    for (piVar13 = (int *)*param_2; piVar13 != piVar14; piVar13 = piVar13 + 1) {
      if (piVar16 == (int *)0x0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
      }
      *piVar16 = *piVar13;
      piVar16 = piVar16 + 1;
    }
  }
  void std::__ndk1::__sort<std::__ndk1::__less<unsigned int, unsigned int>&, unsigned int*>(unsigned int*, unsigned int*, std::__ndk1::__less<unsigned int, unsigned int>&)(piVar9,piVar16,&piStack_a0);
  piStack_a0 = piVar9;
  if (piVar9 != piVar16) {
    ppiVar12 = &piStack_c0;
    ppiVar15 = &piStack_a0;
    do {
      *ppiVar12 = *ppiVar15;
      piStack_c0 = piStack_c0 + 1;
      if (piStack_c0 == piVar16) goto code_r0x017d1bf4;
      ppiVar15 = &piStack_c0;
      ppiVar12 = &piStack_a0;
    } while (*piStack_a0 != *piStack_c0);
  }
  piVar13 = piStack_a0;
  if (piStack_a0 != piVar16) {
    piVar13 = piStack_a0 + 1;
    piVar14 = piStack_a0;
    while (piVar13 = piVar13 + 1, piVar13 != piVar16) {
      if (*piVar14 != *piVar13) {
        piVar14 = piVar14 + 1;
        *piVar14 = *piVar13;
      }
    }
    piVar13 = piVar14 + 1;
  }
  if ((piVar13 != piVar16) && (piVar13 != piVar16)) {
    piVar16 = (int *)((long)piVar16 +
                     (~((long)piVar16 + (-4 - (long)piVar13)) & 0xfffffffffffffffcU));
  }
code_r0x017d1bf4:
  if (piVar9 == piVar16) goto code_r0x017d1e8c;
  bVar5 = true;
  uVar8 = (ulong)&piStack_80 | 1;
  piVar13 = piVar9;
  do {
    if (*piVar13 != 0) {
      puVar3 = &UNK_027e6d32/*"%u"*/;
      if (!bVar5) {
        puVar3 = &UNK_027f4b79/*",%u"*/;
      }
      Framework::CSTLStringUtility_Base<string >::Format(char const*, ...)(&piStack_a0,puVar3);
      uVar19 = (ulong)piStack_a0 >> 1 & 0x7f;
      uVar18 = (ulong)&piStack_a0 | 1;
      if (((ulong)piStack_a0 & 1) != 0) {
        uVar19 = uStack_98;
        uVar18 = uStack_90;
      }
      if (((ulong)piStack_80 & 1) == 0) {
        lVar11 = 0x16;
        piVar14 = (int *)((ulong)piStack_80 & 0xff);
      }
      else {
        lVar11 = ((ulong)piStack_80 & 0xfffffffffffffffe) - 1;
        piVar14 = piStack_80;
      }
      uVar2 = (ulong)(((uint)piVar14 & 0xfe) >> 1);
      if (((ulong)piVar14 & 1) != 0) {
        uVar2 = uStack_78;
      }
      if (lVar11 - uVar2 < uVar19) {
        string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&piStack_80,lVar11,(uVar19 - lVar11) + uVar2,uVar2,uVar2,0,uVar19);
      }
      else if (uVar19 != 0) {
        uVar17 = uVar8;
        if (((ulong)piVar14 & 1) != 0) {
          uVar17 = uStack_70;
        }
        memcpy(uVar17 + uVar2,uVar18,uVar19);
        uVar2 = uVar2 + uVar19;
        if (((ulong)piStack_80 & 1) == 0) {
          piStack_80 = (int *)CONCAT71(piStack_80._1_7_,(char)uVar2 * '\x02');
          *(undefined1 *)(uVar17 + uVar2) = 0;
        }
        else {
          *(undefined1 *)(uVar17 + uVar2) = 0;
          uStack_78 = uVar2;
        }
      }
      if (((ulong)piStack_a0 & 1) != 0) {
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_90);
      }
      bVar5 = false;
    }
    piVar13 = piVar13 + 1;
  } while (piVar16 != piVar13);
  if (bVar5) goto code_r0x017d1e8c;
  if (((ulong)piStack_80 & 1) == 0) {
    uVar19 = (ulong)piStack_80 >> 1 & 0x7f;
    uVar18 = 0x16;
    piVar16 = (int *)((ulong)piStack_80 & 0xff);
    if (uVar19 != 0x16) goto code_r0x017d1d5c;
code_r0x017d1d7c:
    uVar2 = uVar8;
    if (((ulong)piVar16 & 1) != 0) {
      uVar2 = uStack_70;
    }
    if (uVar18 < 0x7fffffffffffffe7) {
      uVar17 = uVar18 << 1;
      if (uVar17 <= uVar18 + 1) {
        uVar17 = uVar18 + 1;
      }
      if (uVar17 < 0x17) {
        uVar17 = 0x17;
      }
      else {
        uVar17 = uVar17 + 0x10 & 0xfffffffffffffff0;
        if (uVar17 == 0) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
        }
      }
    }
    else {
      uVar17 = 0xffffffffffffffef;
    }
    uVar10 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar17,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
    if (uVar10 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
    memcpy(uVar10,uVar2,uVar18);
    if (uVar18 != 0x16) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uVar2);
    }
    piStack_80 = (int *)(uVar17 | 1);
    uStack_70 = uVar10;
code_r0x017d1e58:
    uStack_78 = uVar19 + 1;
    uVar18 = uStack_70;
  }
  else {
    uVar18 = ((ulong)piStack_80 & 0xfffffffffffffffe) - 1;
    piVar16 = piStack_80;
    uVar19 = uStack_78;
    if (uStack_78 == uVar18) goto code_r0x017d1d7c;
code_r0x017d1d5c:
    if (((ulong)piStack_80 & 1) != 0) goto code_r0x017d1e58;
    piStack_80 = (int *)CONCAT71(piStack_80._1_7_,(char)uVar19 * '\x02' + '\x02');
    uVar18 = uVar8;
  }
  *(undefined2 *)(uVar18 + uVar19) = 0x29;
  if (((ulong)piStack_80 & 1) != 0) {
    uVar8 = uStack_70;
  }
  CMasterParameterBaseSqlite_Simple<CMasterParameterItemElement>::ParameterByQuery(char const*, Framework::CSTLUnorderedMap<unsigned int, CMasterParameterItemElement, std::__ndk1::hash<unsigned int>, std::__ndk1::equal_to<unsigned int> >&, Aska::Yayoi::QueryParam*, unsigned int) const(param_1,uVar8,param_3,0,0);
code_r0x017d1e8c:
  if (piVar9 != (int *)0x0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(piVar9);
  }
  if (((ulong)piStack_80 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_70);
  }
  return;
}

// ==== CMasterParameterBaseSqlite_Simple<CMasterParameterItemElement>::ClearCache()
// vaddr 0x16ee87c | ghidra 0x17ee87c | size 200 | symbol _ZN33CMasterParameterBaseSqlite_SimpleI27CMasterParameterItemElementE10ClearCacheEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN33CMasterParameterBaseSqlite_SimpleI27CMasterParameterItemElementE10ClearCacheEv
               (long param_1)

{
  long *plVar1;
  long lVar2;
  long lVar3;
  
  if (*(long *)(param_1 + 0x58) != 0) {
    plVar1 = (long *)*(long *)(param_1 + 0x50);
    while (plVar1 != (long *)0x0) {
      lVar3 = *plVar1;
      if (plVar1[4] != 0) {
        std::__ndk1::__shared_weak_count::__release_shared()();
      }
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar1);
      plVar1 = (long *)lVar3;
    }
    lVar3 = *(long *)(param_1 + 0x48);
    *(undefined8 *)(param_1 + 0x50) = 0;
    if (lVar3 != 0) {
      lVar2 = 0;
      do {
        *(undefined8 *)(*(long *)(param_1 + 0x40) + lVar2 * 8) = 0;
        lVar2 = lVar2 + 1;
      } while (lVar3 != lVar2);
    }
    *(undefined8 *)(param_1 + 0x58) = 0;
  }
  if (*(long *)(param_1 + 0x88) != 0) {
    plVar1 = (long *)*(long *)(param_1 + 0x80);
    while (plVar1 != (long *)0x0) {
      lVar3 = *plVar1;
      if (plVar1[4] != 0) {
        std::__ndk1::__shared_weak_count::__release_shared()();
      }
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar1);
      plVar1 = (long *)lVar3;
    }
    lVar3 = *(long *)(param_1 + 0x78);
    *(undefined8 *)(param_1 + 0x80) = 0;
    if (lVar3 != 0) {
      lVar2 = 0;
      do {
        *(undefined8 *)(*(long *)(param_1 + 0x70) + lVar2 * 8) = 0;
        lVar2 = lVar2 + 1;
      } while (lVar3 != lVar2);
    }
    *(undefined8 *)(param_1 + 0x88) = 0;
  }
  return;
}

// ==== CMasterParameterBaseSqlite_Simple<CMasterParameterItemElement>::SetStoreAllCacheSize()
// vaddr 0x17b2c68 | ghidra 0x18b2c68 | size 340 | symbol _ZN33CMasterParameterBaseSqlite_SimpleI27CMasterParameterItemElementE20SetStoreAllCacheSizeEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN33CMasterParameterBaseSqlite_SimpleI27CMasterParameterItemElementE20SetStoreAllCacheSizeEv
               (long param_1)

{
  int iVar1;
  char cVar2;
  bool bVar3;
  long lVar4;
  long *plVar5;
  long *plVar6;
  long lVar7;
  long lStack_60;
  undefined8 uStack_58;
  long lStack_50;
  undefined8 uStack_48;
  undefined4 uStack_40;
  long lStack_38;
  long lStack_30;
  int *piStack_28;
  
  plVar6 = *(long **)(param_1 + 8);
  if (plVar6 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dc023/*"C:\BAS_Submission\Client\Project\Android\BASAndroid.NativeActivity\..\..\..\Source\Game/Parameter/Master/MasterParameterBaseSqlite.h"*/,0x4d,&UNK_027dc0a8/*"m_pConnector is null."*/);
  }
  (**(code **)(*plVar6 + 0x10))(plVar6,&UNK_027dc00a/*"sqlite/basmaster.sqlite3"*/);
  lStack_30 = 0;
  piStack_28 = (int *)0x0;
  lStack_38 = 0;
  (**(code **)(*plVar6 + 0x28))(plVar6,0,0,&lStack_30,&lStack_38);
  if (0 < lStack_38) {
    uStack_58 = 0;
    lStack_60 = 0;
    uStack_48 = 0;
    lStack_50 = 0;
    uStack_40 = 0x3f800000;
    void CMasterParameterBaseSqlite::DeserializeMsgPack<CMasterParameterItemElement>(Aska::TSharedArray<signed char> const&, long const&, CMasterParameterItemElement*, Framework::CSTLUnorderedMap<unsigned int, CMasterParameterItemElement, std::__ndk1::hash<unsigned int>, std::__ndk1::equal_to<unsigned int> >*) const(param_1,&lStack_30,&lStack_38,0,&lStack_60);
    *(undefined8 *)(param_1 + 0x68) = uStack_48;
    lVar4 = lStack_60;
    plVar5 = (long *)lStack_50;
    while (plVar5 != (long *)0x0) {
      lVar7 = *plVar5;
      lStack_60 = lVar4;
      CMasterParameterItemElement::~CMasterParameterItemElement()(plVar5 + 3);
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar5);
      lVar4 = lStack_60;
      plVar5 = (long *)lVar7;
    }
    lStack_60 = 0;
    if (lVar4 != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)();
    }
  }
  if (piStack_28 != (int *)0x0) {
    do {
      iVar1 = *piStack_28;
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piStack_28,0x10);
      if (bVar3) {
        *piStack_28 = iVar1 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    if (iVar1 + -1 != 0) goto code_r0x018b2d7c;
  }
  if (lStack_30 != 0) {
    operator delete[](void*)();
  }
  if (piStack_28 != (int *)0x0) {
    Aska::TSharedPointerCode::DeleteCounter(int*)();
  }
code_r0x018b2d7c:
  lStack_30 = 0;
  if (plVar6 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dc023/*"C:\BAS_Submission\Client\Project\Android\BASAndroid.NativeActivity\..\..\..\Source\Game/Parameter/Master/MasterParameterBaseSqlite.h"*/,0x52,&UNK_027dc0a8/*"m_pConnector is null."*/);
  }
  (**(code **)(*plVar6 + 0x18))(plVar6);
  return;
}

// ==== CMasterParameterBaseSqlite_Simple<CMasterParameterItemElement>::ParameterByQuery(char const*, Aska::Yayoi::QueryParam*, unsigned int) const
// vaddr 0x1e007d8 | ghidra 0x1f007d8 | size 584 | symbol _ZNK33CMasterParameterBaseSqlite_SimpleI27CMasterParameterItemElementE16ParameterByQueryEPKcPN4Aska5Yayoi10QueryParamEj | lib libSOA-3.7.0.so | 2026-10-08
void _ZNK33CMasterParameterBaseSqlite_SimpleI27CMasterParameterItemElementE16ParameterByQueryEPKcPN4Aska5Yayoi10QueryParamEj
               (long *param_1,long *param_2,undefined8 param_3,undefined8 param_4,undefined4 param_5
               )

{
  int iVar1;
  char cVar2;
  bool bVar3;
  undefined *puVar4;
  uint uVar5;
  long lVar6;
  long *plVar7;
  ulong uVar8;
  long *plVar9;
  ulong uVar10;
  ulong uVar11;
  ulong uVar12;
  long lStack_58;
  long lStack_50;
  int *piStack_48;
  
  uVar5 = CMasterParameterBaseSqlite_Simple<CMasterParameterItemElement>::MakeCacheKey(char const*, Aska::Yayoi::QueryParam*, unsigned int) const();
  uVar10 = param_2[0xf];
  uVar12 = (ulong)uVar5;
  if (uVar10 != 0) {
    uVar11 = uVar10 - 1;
    if ((uVar11 & uVar10) == 0) {
      uVar8 = uVar11 & uVar12;
    }
    else {
      uVar8 = 0;
      if (uVar10 != 0) {
        uVar8 = uVar12 / uVar10;
      }
      uVar8 = uVar12 - uVar8 * uVar10;
    }
    plVar9 = *(long **)(param_2[0xe] + uVar8 * 8);
    if (plVar9 != (long *)0x0) {
      if ((uVar11 & uVar10) == 0) {
        do {
          plVar9 = (long *)*plVar9;
          if ((plVar9 == (long *)0x0) || ((plVar9[1] & uVar11) != uVar8)) goto code_r0x01f008b8;
        } while (*(uint *)(plVar9 + 2) != uVar5);
      }
      else {
        do {
          plVar9 = (long *)*plVar9;
          if (plVar9 == (long *)0x0) goto code_r0x01f008b8;
          uVar11 = 0;
          if (uVar10 != 0) {
            uVar11 = (ulong)plVar9[1] / uVar10;
          }
          if (plVar9[1] - uVar11 * uVar10 != uVar8) goto code_r0x01f008b8;
        } while (*(uint *)(plVar9 + 2) != uVar5);
      }
      *param_1 = plVar9[3];
      lVar6 = plVar9[4];
      param_1[1] = lVar6;
      if (lVar6 != 0) {
        (*(code *)PTR__ZNSt6__ndk119__shared_weak_count12__add_sharedEv_02ca2250)();
        return;
      }
      return;
    }
  }
code_r0x01f008b8:
  uVar10 = (**(code **)(*param_2 + 0x28))(param_2);
  if ((uVar10 & 1) == 0) {
    *param_1 = 0;
    param_1[1] = 0;
    return;
  }
  plVar9 = (long *)param_2[1];
  if (plVar9 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dc023/*"C:\BAS_Submission\Client\Project\Android\BASAndroid.NativeActivity\..\..\..\Source\Game/Parameter/Master/MasterParameterBaseSqlite.h"*/,0x4d,&UNK_027dc0a8/*"m_pConnector is null."*/);
  }
  (**(code **)(*plVar9 + 0x10))(plVar9,&UNK_027dc00a/*"sqlite/basmaster.sqlite3"*/);
  lStack_50 = 0;
  piStack_48 = (int *)0x0;
  lStack_58 = 0;
  (**(code **)(*plVar9 + 0x30))(plVar9,param_3,&lStack_50,&lStack_58,param_4,param_5);
  if (lStack_58 < 1) {
    *param_1 = 0;
    param_1[1] = 0;
  }
  else {
    lVar6 = operator new(unsigned long, std::nothrow_t const&)(0x9d0,PTR__ZSt7nothrow_02cb9a80);
    if (lVar6 != 0) {
      CMasterParameterItemElement::CMasterParameterItemElement()(lVar6);
    }
    void CMasterParameterBaseSqlite::DeserializeMsgPack<CMasterParameterItemElement>(Aska::TSharedArray<signed char> const&, long const&, CMasterParameterItemElement*, Framework::CSTLUnorderedMap<unsigned int, CMasterParameterItemElement, std::__ndk1::hash<unsigned int>, std::__ndk1::equal_to<unsigned int> >*) const(param_2,&lStack_50,&lStack_58,lVar6,0);
    *param_1 = lVar6;
    plVar7 = (long *)operator new(unsigned long)(0x20);
    puVar4 = 
    PTR__ZTVNSt6__ndk120__shared_ptr_pointerIP27CMasterParameterItemElementNS_14default_deleteIS1_EENS_9allocatorIS1_EEEE_02cc3e60
    ;
    plVar7[2] = 0;
    plVar7[3] = lVar6;
    param_1[1] = (long)plVar7;
    *plVar7 = (long)(puVar4 + 0x10);
    plVar7[1] = 0;
    CMasterParameterBaseSqlite_Simple<CMasterParameterItemElement>::InsertCustomizeCache(unsigned int, std::__ndk1::shared_ptr<CMasterParameterItemElement> const&) const(param_2,uVar12,param_1);
  }
  if (piStack_48 != (int *)0x0) {
    do {
      iVar1 = *piStack_48;
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piStack_48,0x10);
      if (bVar3) {
        *piStack_48 = iVar1 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    if (iVar1 + -1 != 0) goto code_r0x01f009f4;
  }
  if (lStack_50 != 0) {
    operator delete[](void*)();
  }
  if (piStack_48 != (int *)0x0) {
    Aska::TSharedPointerCode::DeleteCounter(int*)();
  }
code_r0x01f009f4:
  lStack_50 = 0;
  (**(code **)(*plVar9 + 0x18))(plVar9);
  return;
}

// ==== CMasterParameterBaseSqlite_Simple<CMasterParameterItemElement>::MakeCacheKey(char const*, Aska::Yayoi::QueryParam*, unsigned int) const
// vaddr 0x1e00a20 | ghidra 0x1f00a20 | size 256 | symbol _ZNK33CMasterParameterBaseSqlite_SimpleI27CMasterParameterItemElementE12MakeCacheKeyEPKcPN4Aska5Yayoi10QueryParamEj | lib libSOA-3.7.0.so | 2026-10-08
undefined4
_ZNK33CMasterParameterBaseSqlite_SimpleI27CMasterParameterItemElementE12MakeCacheKeyEPKcPN4Aska5Yayoi10QueryParamEj
          (undefined8 param_1,undefined8 param_2,long param_3,uint param_4)

{
  undefined4 uVar1;
  long lVar2;
  long lVar3;
  undefined8 uVar4;
  ulong uVar5;
  undefined8 *puVar6;
  undefined1 auStack_150 [16];
  undefined1 auStack_140 [256];
  
  memset(auStack_140,0,0x100);
  snprintf(auStack_140,0x100,&UNK_027f6a37/*"%s"*/,param_2);
  if ((param_3 != 0) && (param_4 != 0)) {
    uVar5 = (ulong)param_4;
    puVar6 = (undefined8 *)(param_3 + 0x10);
    do {
      uVar4 = *puVar6;
      lVar2 = strlen(auStack_140);
      lVar3 = strlen(uVar4);
      if (0xff < (ulong)(lVar3 + lVar2)) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dc32f/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/Utility.h"*/,0x83,&UNK_027e41b7/*"gStrcat() : destination buffer is small. ( ( %d + %d ) < %d )"*/,lVar2,lVar3,0x100);
      }
      strcat(auStack_140,uVar4);
      uVar5 = uVar5 - 1;
      puVar6 = puVar6 + 5;
    } while (uVar5 != 0);
  }
  Framework::CHash32::CHash32(char const*)(auStack_150,auStack_140);
  uVar1 = Framework::CHash32::operator unsigned int() const(auStack_150);
  Framework::CHash32::~CHash32()(auStack_150);
  return uVar1;
}

// ==== CMasterParameterBaseSqlite_Simple<CMasterParameterItemElement>::InsertCustomizeCache(unsigned int, std::__ndk1::shared_ptr<CMasterParameterItemElement> const&) const
// vaddr 0x1e00b20 | ghidra 0x1f00b20 | size 640 | symbol _ZNK33CMasterParameterBaseSqlite_SimpleI27CMasterParameterItemElementE20InsertCustomizeCacheEjRKNSt6__ndk110shared_ptrIS0_EE | lib libSOA-3.7.0.so | 2026-10-08
void _ZNK33CMasterParameterBaseSqlite_SimpleI27CMasterParameterItemElementE20InsertCustomizeCacheEjRKNSt6__ndk110shared_ptrIS0_EE
               (long param_1,uint param_2,long *param_3)

{
  long *plVar1;
  ulong uVar2;
  long *plVar3;
  long *plVar4;
  long lVar5;
  ulong uVar6;
  ulong uVar7;
  long lVar8;
  ulong uVar9;
  ulong unaff_x27;
  float fVar10;
  
  uVar7 = (ulong)param_2;
  plVar1 = (long *)(param_1 + 0x70);
  if ((*(ulong *)(param_1 + 0x98) <= *(ulong *)(param_1 + 0x88)) &&
     (*(ulong *)(param_1 + 0x88) != 0)) {
    plVar3 = (long *)*(long *)(param_1 + 0x80);
    while (plVar3 != (long *)0x0) {
      lVar8 = *plVar3;
      if (plVar3[4] != 0) {
        std::__ndk1::__shared_weak_count::__release_shared()();
      }
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar3);
      plVar3 = (long *)lVar8;
    }
    lVar8 = *(long *)(param_1 + 0x78);
    *(undefined8 *)(param_1 + 0x80) = 0;
    if (lVar8 != 0) {
      lVar5 = 0;
      do {
        *(undefined8 *)(*plVar1 + lVar5 * 8) = 0;
        lVar5 = lVar5 + 1;
      } while (lVar8 != lVar5);
    }
    *(undefined8 *)(param_1 + 0x88) = 0;
  }
  uVar9 = *(ulong *)(param_1 + 0x78);
  if (uVar9 != 0) {
    uVar6 = uVar9 - 1;
    if ((uVar6 & uVar9) == 0) {
      unaff_x27 = uVar6 & uVar7;
    }
    else {
      uVar2 = 0;
      if (uVar9 != 0) {
        uVar2 = uVar7 / uVar9;
      }
      unaff_x27 = uVar7 - uVar2 * uVar9;
    }
    plVar3 = *(long **)(*plVar1 + unaff_x27 * 8);
    if (plVar3 != (long *)0x0) {
      if ((uVar6 & uVar9) == 0) {
        while ((plVar3 = (long *)*plVar3, plVar3 != (long *)0x0 &&
               ((plVar3[1] & uVar6) == unaff_x27))) {
          if (*(uint *)(plVar3 + 2) == param_2) {
            return;
          }
        }
      }
      else {
        while (plVar3 = (long *)*plVar3, plVar3 != (long *)0x0) {
          uVar6 = 0;
          if (uVar9 != 0) {
            uVar6 = (ulong)plVar3[1] / uVar9;
          }
          if (plVar3[1] - uVar6 * uVar9 != unaff_x27) break;
          if (*(uint *)(plVar3 + 2) == param_2) {
            return;
          }
        }
      }
    }
  }
  plVar3 = (long *)Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(0x28,&UNK_027dc2d5/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_UnorderedMap.h"*/,0x1c);
  if (plVar3 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
  }
  *(uint *)(plVar3 + 2) = param_2;
  plVar3[3] = *param_3;
  lVar8 = param_3[1];
  plVar3[4] = lVar8;
  if (lVar8 != 0) {
    std::__ndk1::__shared_weak_count::__add_shared()();
  }
  *plVar3 = 0;
  plVar3[1] = uVar7;
  fVar10 = (float)(*(long *)(param_1 + 0x88) + 1);
  if ((uVar9 == 0) || (*(float *)(param_1 + 0x90) * (float)uVar9 < fVar10)) {
    if (uVar9 < 3) {
      uVar6 = 1;
    }
    else {
      uVar6 = (ulong)((uVar9 - 1 & uVar9) != 0);
    }
    uVar6 = uVar6 | uVar9 << 1;
    uVar9 = (ulong)(fVar10 / *(float *)(param_1 + 0x90));
    if (uVar9 <= uVar6) {
      uVar9 = uVar6;
    }
    std::__ndk1::__hash_table<std::__ndk1::__hash_value_type<unsigned int, std::__ndk1::shared_ptr<CMasterParameterItemElement> >, std::__ndk1::__unordered_map_hasher<unsigned int, std::__ndk1::__hash_value_type<unsigned int, std::__ndk1::shared_ptr<CMasterParameterItemElement> >, std::__ndk1::hash<unsigned int>, true>, std::__ndk1::__unordered_map_equal<unsigned int, std::__ndk1::__hash_value_type<unsigned int, std::__ndk1::shared_ptr<CMasterParameterItemElement> >, std::__ndk1::equal_to<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__hash_value_type<unsigned int, std::__ndk1::shared_ptr<CMasterParameterItemElement> >, Framework::CSTLUnorderedMapAllocatorInf> >::rehash(unsigned long)(plVar1,uVar9);
    uVar9 = *(ulong *)(param_1 + 0x78);
    if ((uVar9 - 1 & uVar9) == 0) {
      unaff_x27 = uVar9 - 1 & uVar7;
    }
    else {
      uVar6 = 0;
      if (uVar9 != 0) {
        uVar6 = uVar7 / uVar9;
      }
      unaff_x27 = uVar7 - uVar6 * uVar9;
    }
  }
  plVar4 = *(long **)(*plVar1 + unaff_x27 * 8);
  if (plVar4 == (long *)0x0) {
    plVar4 = (long *)(param_1 + 0x80);
    *plVar3 = *plVar4;
    *plVar4 = (long)plVar3;
    *(long **)(*(long *)(param_1 + 0x70) + unaff_x27 * 8) = plVar4;
    if (*plVar3 == 0) goto code_r0x01f00d7c;
    uVar7 = *(ulong *)(*plVar3 + 8);
    if ((uVar9 - 1 & uVar9) == 0) {
      uVar7 = uVar7 & uVar9 - 1;
    }
    else {
      uVar6 = 0;
      if (uVar9 != 0) {
        uVar6 = uVar7 / uVar9;
      }
      uVar7 = uVar7 - uVar6 * uVar9;
    }
    plVar4 = (long *)(*plVar1 + uVar7 * 8);
  }
  else {
    *plVar3 = *plVar4;
  }
  *plVar4 = (long)plVar3;
code_r0x01f00d7c:
  *(long *)(param_1 + 0x88) = *(long *)(param_1 + 0x88) + 1;
  return;
}


// FAILED to create function at 02849be0 typeinfo name for CSimpleSqliteConnector<MasterDB::CItem, Aska::Yayoi::TEntity_Slave<Aska::Yayoi::SQLiteDriver, MasterDB::CItem, Aska::Yayoi::NoCache> >
// FAILED to create function at 02849c50 typeinfo name for CSimpleSqliteConnector<MasterDB::CItem, Aska::Yayoi::TEntity_Slave<Aska::Yayoi::SQLiteDriver, MasterDB::CItem, Aska::Yayoi::NoCache> >::CLocalEntity<MasterDB::CItem>
// FAILED to create function at 02aeb5e0 CMasterParameterBaseSqlite_Simple<CMasterParameterItemElement>::typeinfo
// FAILED to create function at 02aeb638 CMasterParameterBaseSqlite_Simple<CMasterParameterItemElement>::vtable
// FAILED to create function at 02aeb6e0 CSimpleSqliteConnector<MasterDB::CItem,Aska::Yayoi::TEntity_Slave<Aska::Yayoi::SQLiteDriver,MasterDB::CItem,Aska::Yayoi::NoCache>>::vtable
// FAILED to create function at 02aeb730 CSimpleSqliteConnector<MasterDB::CItem,Aska::Yayoi::TEntity_Slave<Aska::Yayoi::SQLiteDriver,MasterDB::CItem,Aska::Yayoi::NoCache>>::typeinfo
// FAILED to create function at 02aeb748 CSimpleSqliteConnector<MasterDB::CItem,Aska::Yayoi::TEntity_Slave<Aska::Yayoi::SQLiteDriver,MasterDB::CItem,Aska::Yayoi::NoCache>>::CLocalEntity<MasterDB::CItem>::vtable
// FAILED to create function at 02aeb760 CSimpleSqliteConnector<MasterDB::CItem,Aska::Yayoi::TEntity_Slave<Aska::Yayoi::SQLiteDriver,MasterDB::CItem,Aska::Yayoi::NoCache>>::CLocalEntity<MasterDB::CItem>::typeinfo
// FAILED to create function at 02aeb770 CSimpleSqliteConnector<MasterDB::CItem,Aska::Yayoi::TEntity_Slave<Aska::Yayoi::SQLiteDriver,MasterDB::CItem,Aska::Yayoi::NoCache>>::CLocalEntity<MasterDB::CItem>::GetQuery(int)::queries
// FAILED to create function at 02aeb7d0 CSimpleSqliteConnector<MasterDB::CItem,Aska::Yayoi::TEntity_Slave<Aska::Yayoi::SQLiteDriver,MasterDB::CItem,Aska::Yayoi::NoCache>>::CLocalEntity<MasterDB::CItem>::GetPrimaryKeies()::keies
