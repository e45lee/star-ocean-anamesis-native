// port/decomp/lib_vorbis/aska_ogg.c: Ghidra decompiles for the lib_vorbis subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-04 05:06 UTC: tools/decomp.sh '--into' 'lib_vorbis/aska_ogg' 'Aska::AskaOGG::'

// ==== Aska::AskaOGG::InitializeMemory()
// vaddr 0x223f9a4 | ghidra 0x233f9a4 | size 36 | symbol _ZN4Aska7AskaOGG16InitializeMemoryEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska7AskaOGG16InitializeMemoryEv(void)

{
  (*(code *)PTR_ogg_memory_hook_02ca5028)
            (PTR_aska_ogg_malloc_02cbdd38,PTR_aska_ogg_calloc_02cc12d8,PTR_aska_ogg_realloc_02cc3470
             ,PTR_aska_ogg_free_02cbeea8);
  return;
}

// ==== Aska::AskaOGG::AskaOGG()
// vaddr 0x223f9c8 | ghidra 0x233f9c8 | size 64 | symbol _ZN4Aska7AskaOGGC2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska7AskaOGGC1Ev(long param_1)

{
  *(undefined8 *)(param_1 + 0x440) = 0;
  memset(param_1,0,0x3ca);
  memset(param_1 + 0x3d0,0,0x6e);
  *(undefined4 *)(param_1 + 0x448) = 0;
  return;
}

// ==== Aska::AskaOGG::DecodeInit(unsigned int, unsigned int)
// vaddr 0x223fa08 | ghidra 0x233fa08 | size 424 | symbol _ZN4Aska7AskaOGG10DecodeInitEjj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska7AskaOGG10DecodeInitEjj
               (undefined8 *param_1,long param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  int iVar2;
  long lVar3;
  undefined8 uVar4;
  
  iVar2 = *(int *)PTR__ZN4Aska7AskaOGG18m_uiDecodePoolSizeE_02cb88d8;
  if (*(long *)(param_2 + 0x3d0) != 0) {
    Aska::SoundMemory::ResourceFree(void*)();
    *(undefined8 *)(param_2 + 0x3d0) = 0;
  }
  lVar3 = Aska::SoundMemory::ResourceAlloc(unsigned long, unsigned long)(iVar2,0x200);
  *(long *)(param_2 + 0x3d0) = lVar3;
  if (lVar3 != 0) {
    uVar1 = iVar2 + 0x1ffU & 0xfffffe00;
    *(uint *)(param_2 + 0x410) = uVar1;
    if (*(long *)(param_2 + 0x3d8) != 0) {
      Aska::SoundMemory::ResourceFree(void*)();
      *(undefined8 *)(param_2 + 0x3d8) = 0;
    }
    lVar3 = Aska::SoundMemory::ResourceAlloc(unsigned long, unsigned long)(iVar2,0x200);
    *(long *)(param_2 + 0x3d8) = lVar3;
    if (lVar3 != 0) {
      *(uint *)(param_2 + 0x414) = uVar1;
      if (*(long *)(param_2 + 0x3e0) != 0) {
        Aska::SoundMemory::ResourceFree(void*)();
        *(undefined8 *)(param_2 + 0x3e0) = 0;
      }
      lVar3 = Aska::SoundMemory::ResourceAlloc(unsigned long, unsigned long)(iVar2,0x200);
      *(long *)(param_2 + 0x3e0) = lVar3;
      if (lVar3 != 0) {
        *(uint *)(param_2 + 0x418) = uVar1;
        if (*(long *)(param_2 + 1000) != 0) {
          Aska::SoundMemory::ResourceFree(void*)();
          *(undefined8 *)(param_2 + 1000) = 0;
        }
        lVar3 = Aska::SoundMemory::ResourceAlloc(unsigned long, unsigned long)(iVar2,0x200);
        *(long *)(param_2 + 1000) = lVar3;
        if (lVar3 != 0) {
          *(uint *)(param_2 + 0x41c) = uVar1;
          if (*(long *)(param_2 + 0x3f0) != 0) {
            Aska::SoundMemory::ResourceFree(void*)();
            *(undefined8 *)(param_2 + 0x3f0) = 0;
          }
          lVar3 = Aska::SoundMemory::ResourceAlloc(unsigned long, unsigned long)(iVar2,0x200);
          *(long *)(param_2 + 0x3f0) = lVar3;
          if (lVar3 != 0) {
            *(uint *)(param_2 + 0x420) = uVar1;
            if (*(long *)(param_2 + 0x3f8) != 0) {
              Aska::SoundMemory::ResourceFree(void*)();
              *(undefined8 *)(param_2 + 0x3f8) = 0;
            }
            lVar3 = Aska::SoundMemory::ResourceAlloc(unsigned long, unsigned long)(iVar2,0x200);
            *(long *)(param_2 + 0x3f8) = lVar3;
            if (lVar3 != 0) {
              *(uint *)(param_2 + 0x424) = uVar1;
              if (*(long *)(param_2 + 0x400) != 0) {
                Aska::SoundMemory::ResourceFree(void*)();
                *(undefined8 *)(param_2 + 0x400) = 0;
              }
              lVar3 = Aska::SoundMemory::ResourceAlloc(unsigned long, unsigned long)(iVar2,0x200);
              *(long *)(param_2 + 0x400) = lVar3;
              if (lVar3 != 0) {
                *(uint *)(param_2 + 0x428) = uVar1;
                if (*(long *)(param_2 + 0x408) != 0) {
                  Aska::SoundMemory::ResourceFree(void*)();
                  *(undefined8 *)(param_2 + 0x408) = 0;
                }
                lVar3 = Aska::SoundMemory::ResourceAlloc(unsigned long, unsigned long)(iVar2,0x200);
                *(long *)(param_2 + 0x408) = lVar3;
                if (lVar3 != 0) {
                  uVar4 = 0;
                  *(uint *)(param_2 + 0x42c) = uVar1;
                  *(undefined4 *)(param_2 + 0x438) = param_3;
                  *(undefined4 *)(param_2 + 0x430) = 0;
                  *(undefined1 *)(param_2 + 0x43c) = 0;
                  *(undefined4 *)(param_2 + 0x448) = param_4;
                  goto code_r0x0233fb98;
                }
              }
            }
          }
        }
      }
    }
  }
  uVar4 = 0xfffffffffffffc41;
code_r0x0233fb98:
  *param_1 = uVar4;
  return;
}

// ==== Aska::AskaOGG::Decode(signed char const*, unsigned int, signed char**, unsigned int, unsigned int, unsigned int)
// vaddr 0x223fbb0 | ghidra 0x233fbb0 | size 176 | symbol _ZN4Aska7AskaOGG6DecodeEPKajPPajjj | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska7AskaOGG6DecodeEPKajPPajjj
               (long param_1,long param_2,uint param_3,long param_4,undefined4 param_5,
               undefined8 param_6,undefined4 param_7)

{
  uint uVar1;
  long lVar2;
  
  lVar2 = -0x3bd;
  if ((param_2 != 0) && (param_4 != 0)) {
    if (2 < *(byte *)(param_1 + 0x43c)) {
      lVar2 = 0;
code_r0x011bd5f0:
      lVar2 = (*(code *)PTR__ZN4Aska7AskaOGG10DecodeBodyEPKajPPajjj_02c96ae8)
                        (param_1,param_2 + lVar2,param_3 - (int)lVar2,param_4,param_5,param_6,
                         param_7);
      return lVar2;
    }
    uVar1 = param_3;
    if (0x1fff < param_3) {
      uVar1 = 0x2000;
    }
    lVar2 = Aska::AskaOGG::DecodeHeader(signed char const*, unsigned long)(param_1,param_2,uVar1);
    if (-1 < lVar2) {
      if (2 < *(byte *)(param_1 + 0x43c)) goto code_r0x011bd5f0;
      lVar2 = 0;
    }
  }
  return lVar2;
}

// ==== Aska::AskaOGG::DecodeHeader(signed char const*, unsigned long)
// vaddr 0x223fc60 | ghidra 0x233fc60 | size 636 | symbol _ZN4Aska7AskaOGG12DecodeHeaderEPKam | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

ulong _ZN4Aska7AskaOGG12DecodeHeaderEPKam(long param_1,undefined8 param_2,ulong param_3)

{
  long lVar1;
  long lVar2;
  int iVar3;
  undefined4 uVar4;
  undefined8 uVar5;
  byte bVar6;
  ulong uVar7;
  ulong uVar8;
  float fVar9;
  float fVar10;
  
  if (*(char *)(param_1 + 0x43c) == '\0') {
    ogg_sync_init(param_1);
  }
  if (param_3 == 0) {
    uVar7 = 0;
  }
  else {
    if (0x1fff < param_3) {
      param_3 = 0x2000;
    }
    uVar5 = ogg_sync_buffer(param_1,0x2000);
    memcpy(uVar5,param_2,param_3);
    iVar3 = ogg_sync_wrote(param_1,param_3);
    if (-1 < iVar3) {
      bVar6 = *(byte *)(param_1 + 0x43c);
      if (bVar6 == 0) {
        lVar1 = param_1 + 0x1b8;
        iVar3 = ogg_sync_pageout(param_1,lVar1);
        if (iVar3 != 1) {
          return 0xfffffffffffffc48;
        }
        lVar2 = param_1 + 0x20;
        uVar4 = ogg_page_serialno(lVar1);
        iVar3 = ogg_stream_init(lVar2,uVar4);
        if (iVar3 < 0) {
          return 0xffffffffffffffff;
        }
        vorbis_info_init(param_1 + 0x208);
        vorbis_comment_init(param_1 + 0x240);
        bVar6 = *(byte *)(param_1 + 0x43c);
        if (bVar6 == 0) {
          iVar3 = ogg_stream_pagein(lVar2,lVar1);
          if (iVar3 < 0) {
            return 0xfffffffffffffc47;
          }
          iVar3 = ogg_stream_packetout(lVar2,param_1 + 0x1d8);
          if (iVar3 != 1) {
            return 0xfffffffffffffc48;
          }
          iVar3 = vorbis_synthesis_headerin(param_1 + 0x208,param_1 + 0x240,param_1 + 0x1d8);
          if (iVar3 < 0) {
            return 0xfffffffffffffc48;
          }
          bVar6 = *(char *)(param_1 + 0x43c) + 1;
          *(byte *)(param_1 + 0x43c) = bVar6;
        }
      }
      if (bVar6 < 3) {
        do {
          iVar3 = ogg_sync_pageout(param_1,param_1 + 0x1b8);
          if (iVar3 == 1) {
            iVar3 = ogg_stream_pagein(param_1 + 0x20,param_1 + 0x1b8);
            if (iVar3 < 0) {
              return 0xfffffffffffffc48;
            }
            bVar6 = *(byte *)(param_1 + 0x43c);
            while( true ) {
              if (2 < bVar6) goto code_r0x0233fd68;
              iVar3 = ogg_stream_packetout(param_1 + 0x20,param_1 + 0x1d8);
              if (iVar3 == 0) break;
              if (iVar3 < 0) {
                return 0xfffffffffffffc48;
              }
              iVar3 = vorbis_synthesis_headerin(param_1 + 0x208,param_1 + 0x240,param_1 + 0x1d8);
              if (iVar3 < 0) {
                return 0xfffffffffffffc48;
              }
              bVar6 = *(char *)(param_1 + 0x43c) + 1;
              *(char *)(param_1 + 0x43c) = *(char *)(param_1 + 0x43c) + '\x01';
            }
          }
          else if (iVar3 == 0) {
            if (*(byte *)(param_1 + 0x43c) < 3) {
              return param_3;
            }
            break;
          }
        } while (*(byte *)(param_1 + 0x43c) < 3);
      }
code_r0x0233fd68:
      iVar3 = vorbis_synthesis_init(param_1 + 0x260,param_1 + 0x208);
      if (iVar3 != 0) {
        return 0xfffffffffffffc48;
      }
      vorbis_block_init(param_1 + 0x260,param_1 + 0x2f0);
      fVar9 = (float)*(int *)(param_1 + 0x210) / _UNK_027e51a0;
      fVar10 = fVar9 * _UNK_027fd0f0;
      *(int *)(param_1 + 0x3bc) = (int)(fVar9 * _UNK_02806d20);
      *(undefined4 *)(param_1 + 0x3c4) = 0;
      *(undefined1 *)(param_1 + 0x3c9) = 0;
      *(undefined8 *)(param_1 + 0x3b0) = 0;
      *(undefined4 *)(param_1 + 0x3b8) = 0;
      *(int *)(param_1 + 0x3c0) = (int)fVar10;
      return param_3;
    }
    uVar7 = 0xfffffffffffffc12;
  }
  uVar8 = 0xfffffffffffffc5c;
  if (uVar7 != 0) {
    uVar8 = uVar7;
  }
  return uVar8;
}

// ==== Aska::AskaOGG::DecodeBody(signed char const*, unsigned int, signed char**, unsigned int, unsigned int, unsigned int)
// vaddr 0x223fedc | ghidra 0x233fedc | size 596 | symbol _ZN4Aska7AskaOGG10DecodeBodyEPKajPPajjj | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZN4Aska7AskaOGG10DecodeBodyEPKajPPajjj
                (long param_1,long param_2,uint param_3,undefined8 *param_4,undefined4 param_5,
                undefined8 param_6,undefined4 param_7)

{
  long lVar1;
  int iVar2;
  int iVar3;
  char cVar4;
  byte bVar5;
  int iVar6;
  int iVar7;
  ulong uVar8;
  undefined8 uVar9;
  ulong uVar10;
  ulong uVar11;
  ulong uVar12;
  int iVar13;
  long lVar14;
  
  lVar14 = 0;
  lVar1 = param_1 + 0x1b8;
  uVar12 = 0;
  do {
    do {
      while (iVar13 = (int)lVar14, *(char *)(param_1 + 0x3c8) != '\0') {
        cVar4 = *(char *)(param_1 + 0x43d);
joined_r0x0233ff88:
        if (cVar4 == '\0') {
          uVar8 = Aska::AskaOGG::DecodePackets(unsigned int, unsigned int)(param_1,uVar12 & 0xffffffff,param_5);
        }
        else {
          uVar8 = Aska::AskaOGG::Decode_LoopStart(unsigned int, unsigned int)(param_1,uVar12 & 0xffffffff,param_5);
        }
        if ((long)uVar8 < 0) {
          return uVar8;
        }
        uVar8 = uVar8 + uVar12;
        if ((*(char *)(param_1 + 0x3c8) != '\0') ||
           (iVar6 = ogg_page_eos(lVar1), uVar12 = uVar8, 0 < iVar6)) goto code_r0x02340038;
      }
      iVar6 = ogg_sync_pageout(param_1,lVar1);
      if (iVar6 != 0) {
        iVar6 = ogg_stream_pagein(param_1 + 0x20,lVar1);
        if (iVar6 < 0) {
          return 0xfffffffffffffc48;
        }
        bVar5 = *(byte *)(*(long *)(param_1 + 0x1b8) + 5);
        *(undefined4 *)(param_1 + 0x434) = param_7;
        *(byte *)(param_1 + 0x3c9) = bVar5 >> 2 & 1;
        cVar4 = *(char *)(param_1 + 0x43d);
        goto joined_r0x0233ff88;
      }
      uVar10 = (ulong)(uint)(iVar13 + *(int *)(param_1 + 0x3c4));
      uVar8 = uVar12;
      if (param_3 <= uVar10) goto code_r0x02340038;
      uVar11 = param_3 - uVar10;
    } while (uVar11 == 0);
    if (0x1fff < uVar11) {
      uVar11 = 0x2000;
    }
    uVar9 = ogg_sync_buffer(param_1,0x2000);
    memcpy(uVar9,param_2 + uVar10,uVar11);
    iVar6 = ogg_sync_wrote(param_1,uVar11);
    uVar8 = 0xfffffffffffffc12;
    if (-1 < iVar6) {
      uVar8 = uVar12;
    }
    uVar12 = 0;
    if (-1 < iVar6) {
      uVar12 = uVar11;
    }
    lVar14 = uVar12 + lVar14;
    iVar13 = (int)lVar14;
    uVar12 = uVar8;
  } while ((iVar6 >> 0x1f & 6U) == 0);
code_r0x02340038:
  if (-1 < (long)uVar8) {
    *param_4 = *(undefined8 *)(param_1 + (ulong)*(uint *)(param_1 + 0x430) * 8 + 0x3d0);
    iVar6 = *(int *)(param_1 + 0x434);
    if (iVar6 != 0) {
      iVar2 = *(int *)(param_1 + 0x438);
      iVar3 = *(int *)(param_1 + 0x20c);
      iVar7 = ogg_stream_reset(param_1 + 0x20);
      if ((iVar7 != 0) || (iVar7 = vorbis_synthesis_restart(param_1 + 0x260), iVar7 != 0)) {
        return 0xffffffffffffffff;
      }
      uVar8 = uVar8 - (uint)((iVar2 - iVar6) * iVar3 * 2);
      ogg_sync_reset(param_1);
      *(undefined4 *)(param_1 + 0x434) = 0;
      *(undefined1 *)(param_1 + 0x43d) = 1;
    }
    if (0 < (long)uVar8) {
      *(uint *)(param_1 + 0x430) = *(int *)(param_1 + 0x430) + 1U & 7;
    }
    if (*(char *)(param_1 + 0x3c8) == '\0') {
      *(undefined4 *)(param_1 + 0x3c4) = 0;
      *(undefined1 *)(param_1 + 0x3c9) = 0;
      *(undefined8 *)(param_1 + 0x3b0) = 0;
      *(undefined4 *)(param_1 + 0x3b8) = 0;
    }
    else {
      *(uint *)(param_1 + 0x3b8) = param_3;
      *(long *)(param_1 + 0x3b0) = param_2;
      *(int *)(param_1 + 0x3c4) = *(int *)(param_1 + 0x3c4) + iVar13;
    }
  }
  return uVar8;
}

// ==== Aska::AskaOGG::Decode_ReadSrcBuffer(signed char const*, unsigned long)
// vaddr 0x2240130 | ghidra 0x2340130 | size 100 | symbol _ZN4Aska7AskaOGG20Decode_ReadSrcBufferEPKam | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZN4Aska7AskaOGG20Decode_ReadSrcBufferEPKam
                (undefined8 param_1,undefined8 param_2,ulong param_3)

{
  int iVar1;
  undefined8 uVar2;
  ulong uVar3;
  
  if (param_3 == 0) {
    uVar3 = 0;
  }
  else {
    if (0x1fff < param_3) {
      param_3 = 0x2000;
    }
    uVar2 = ogg_sync_buffer(param_1,0x2000);
    memcpy(uVar2,param_2,param_3);
    iVar1 = ogg_sync_wrote(param_1,param_3);
    uVar3 = 0xfffffffffffffc12;
    if (-1 < iVar1) {
      uVar3 = param_3;
    }
  }
  return uVar3;
}

// ==== Aska::AskaOGG::PacketDecoder::Init(unsigned int)
// vaddr 0x2240194 | ghidra 0x2340194 | size 68 | symbol _ZN4Aska7AskaOGG13PacketDecoder4InitEj | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska7AskaOGG13PacketDecoder4InitEj(undefined8 *param_1,int param_2)

{
  float fVar1;
  float fVar2;
  
  fVar2 = ((float)param_2 / _UNK_027e51a0) * _UNK_02806d20;
  fVar1 = ((float)param_2 / _UNK_027e51a0) * _UNK_027fd0f0;
  *(undefined1 *)((long)param_1 + 0x19) = 0;
  *param_1 = 0;
  *(int *)(param_1 + 2) = (int)fVar1;
  *(undefined4 *)((long)param_1 + 0x14) = 0;
  *(undefined4 *)(param_1 + 1) = 0;
  *(int *)((long)param_1 + 0xc) = (int)fVar2;
  return;
}

// ==== Aska::AskaOGG::PacketDecoder::SetPage(ogg_page*)
// vaddr 0x22401d8 | ghidra 0x23401d8 | size 20 | symbol _ZN4Aska7AskaOGG13PacketDecoder7SetPageEP8ogg_page | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska7AskaOGG13PacketDecoder7SetPageEP8ogg_page(long param_1,long *param_2)

{
  *(byte *)(param_1 + 0x19) = *(byte *)(*param_2 + 5) >> 2 & 1;
  return;
}

// ==== Aska::AskaOGG::Decode_LoopStart(unsigned int, unsigned int)
// vaddr 0x22401ec | ghidra 0x23401ec | size 936 | symbol _ZN4Aska7AskaOGG16Decode_LoopStartEjj | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska7AskaOGG16Decode_LoopStartEjj(long param_1,int param_2,uint param_3)

{
  long lVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  long lVar5;
  char cVar6;
  uint uVar7;
  long lVar8;
  long lVar9;
  uint uVar10;
  
  cVar6 = *(char *)(param_1 + 0x43d);
  uVar10 = *(uint *)(param_1 + 0x448);
  if (cVar6 == '\x01') {
    lVar5 = param_1 + 0x20;
    iVar2 = ogg_stream_packetpeek(lVar5,param_1 + 0x1d8);
    while( true ) {
      if (iVar2 < 0) {
        return -1;
      }
      if (iVar2 == 0) {
        return -0x3b8;
      }
      if (*(long *)(param_1 + 0x1f8) != -1) break;
      ogg_stream_packetout(lVar5,0);
      iVar2 = ogg_stream_packetpeek(lVar5,param_1 + 0x1d8);
    }
    *(int *)(param_1 + 0x440) = (int)*(long *)(param_1 + 0x1f8);
    *(undefined4 *)(param_1 + 0x444) = 0;
    *(undefined1 *)(param_1 + 0x43d) = 2;
  }
  else if (cVar6 != '\x02') {
code_r0x02340358:
    if (cVar6 == '\x03') {
code_r0x02340360:
      uVar7 = *(uint *)(param_1 + 0x440);
      if (uVar7 < uVar10) {
        lVar5 = param_1 + 0x260;
        do {
          iVar4 = uVar10 - uVar7;
          iVar3 = vorbis_synthesis_pcmout(lVar5,0);
          iVar2 = iVar4;
          if (iVar3 <= iVar4) {
            iVar2 = iVar3;
          }
          vorbis_synthesis_read(lVar5,iVar2);
          uVar7 = *(int *)(param_1 + 0x440) + iVar2;
          *(uint *)(param_1 + 0x440) = uVar7;
          if (iVar3 < iVar4) {
            iVar2 = ogg_stream_packetout(param_1 + 0x20,param_1 + 0x1d8);
            if (iVar2 < 0) {
              return -1;
            }
            if (iVar2 == 0) {
              cVar6 = *(char *)(param_1 + 0x43d);
              goto code_r0x0234043c;
            }
            iVar2 = vorbis_synthesis(param_1 + 0x2f0,param_1 + 0x1d8);
            if (iVar2 != 0) {
              return -1;
            }
            iVar2 = vorbis_synthesis_blockin(lVar5,param_1 + 0x2f0);
            if (iVar2 != 0) {
              return -0x3b8;
            }
            uVar7 = *(uint *)(param_1 + 0x440);
          }
        } while (uVar7 < uVar10);
      }
      *(undefined1 *)(param_1 + 0x43d) = 4;
      uVar10 = *(uint *)(param_1 + 0x3bc);
    }
    else {
code_r0x0234043c:
      if (cVar6 != '\x04') {
        return 0;
      }
      uVar10 = *(uint *)(param_1 + 0x3bc);
    }
    if (uVar10 == 0) {
      uVar10 = 0;
    }
    else {
      uVar7 = *(uint *)(param_1 + 0x3c0);
      if (param_3 <= uVar7 && uVar7 != 0) {
        uVar10 = uVar7;
      }
    }
    *(undefined1 *)(param_1 + 0x3c8) = 0;
    lVar5 = Aska::AskaOGG::Decode_Pcmout(unsigned int)(param_1,param_2);
    if (-1 < lVar5) {
      lVar8 = param_1 + 0x1d8;
      lVar1 = param_1 + 0x2f0;
      lVar9 = 0;
      if (uVar10 == 0) {
        do {
          iVar2 = *(int *)(param_1 + 0x20c);
          iVar4 = ogg_stream_packetout(param_1 + 0x20,lVar8);
          if (iVar4 < 0) {
            return -1;
          }
          lVar9 = lVar5 + lVar9;
          lVar5 = lVar9 * iVar2 * 2;
          if (iVar4 == 0) goto code_r0x02340570;
          iVar2 = vorbis_synthesis(lVar1,lVar8);
          if (iVar2 == 0) {
            vorbis_synthesis_blockin(param_1 + 0x260,lVar1);
          }
          lVar5 = Aska::AskaOGG::Decode_Pcmout(unsigned int)(param_1,(int)lVar5 + param_2);
        } while (-1 < lVar5);
      }
      else {
        while( true ) {
          lVar9 = lVar5 + lVar9;
          lVar5 = lVar9 * *(int *)(param_1 + 0x20c) * 2;
          if (((*(int *)(param_1 + 0x434) == 0) && ((long)(ulong)uVar10 <= lVar9)) &&
             (*(char *)(param_1 + 0x3c9) == '\0')) break;
          iVar2 = ogg_stream_packetout(param_1 + 0x20,lVar8);
          if (iVar2 < 0) {
            return -1;
          }
          if (iVar2 == 0) goto code_r0x02340570;
          iVar2 = vorbis_synthesis(lVar1,lVar8);
          if (iVar2 == 0) {
            vorbis_synthesis_blockin(param_1 + 0x260,lVar1);
          }
          lVar5 = Aska::AskaOGG::Decode_Pcmout(unsigned int)(param_1,(int)lVar5 + param_2);
          if (lVar5 < 0) {
            return lVar5;
          }
        }
        *(undefined1 *)(param_1 + 0x3c8) = 1;
code_r0x02340570:
        *(undefined1 *)(param_1 + 0x43d) = 0;
      }
    }
    return lVar5;
  }
  lVar8 = param_1 + 0x1d8;
  lVar5 = param_1 + 0x20;
  iVar2 = ogg_stream_packetpeek(lVar5,lVar8);
  if ((-1 < iVar2) || (iVar2 == -3)) {
    do {
      if (iVar2 == 0) {
        cVar6 = *(char *)(param_1 + 0x43d);
        goto code_r0x02340358;
      }
      iVar2 = vorbis_packet_blocksize(param_1 + 0x208,lVar8);
      if (iVar2 < 0) {
        ogg_stream_packetout(lVar5,0);
      }
      else {
        if (*(int *)(param_1 + 0x444) == 0) {
          iVar4 = *(int *)(param_1 + 0x440);
        }
        else {
          iVar4 = *(int *)(param_1 + 0x440) + ((uint)(*(int *)(param_1 + 0x444) + iVar2) >> 2);
          *(int *)(param_1 + 0x440) = iVar4;
        }
        iVar3 = vorbis_info_blocksize(param_1 + 0x208,1);
        if (uVar10 <= (uint)(iVar4 + (iVar3 + iVar2 >> 2))) {
          *(undefined1 *)(param_1 + 0x43d) = 3;
          goto code_r0x02340360;
        }
        ogg_stream_packetout(lVar5,0);
        vorbis_synthesis_trackonly(param_1 + 0x2f0,lVar8);
        vorbis_synthesis_blockin(param_1 + 0x260,param_1 + 0x2f0);
        if (*(long *)(param_1 + 0x1f8) != -1) {
          *(int *)(param_1 + 0x440) = (int)*(long *)(param_1 + 0x1f8);
        }
        *(int *)(param_1 + 0x444) = iVar2;
      }
      iVar2 = ogg_stream_packetpeek(lVar5,lVar8);
    } while ((-1 < iVar2) || (iVar2 == -3));
  }
  return -0x3b8;
}

// ==== Aska::AskaOGG::DecodePackets(unsigned int, unsigned int)
// vaddr 0x2240594 | ghidra 0x2340594 | size 252 | symbol _ZN4Aska7AskaOGG13DecodePacketsEjj | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZN4Aska7AskaOGG13DecodePacketsEjj(long param_1,int param_2,uint param_3)

{
  int iVar1;
  ulong uVar2;
  ulong uVar3;
  uint uVar4;
  uint uVar5;
  
  if (*(uint *)(param_1 + 0x3bc) == 0) {
    uVar4 = 0xffffffff;
  }
  else {
    uVar5 = *(uint *)(param_1 + 0x3c0);
    uVar4 = *(uint *)(param_1 + 0x3bc);
    if (param_3 <= uVar5 && uVar5 != 0) {
      uVar4 = uVar5;
    }
    uVar4 = uVar4 - 1;
  }
  uVar3 = 0;
  uVar5 = 0;
  *(undefined1 *)(param_1 + 0x3c8) = 0;
  do {
    do {
      iVar1 = ogg_stream_packetout(param_1 + 0x20,param_1 + 0x1d8);
      if (iVar1 == 0) {
        return uVar3;
      }
    } while (iVar1 < 0);
    iVar1 = vorbis_synthesis(param_1 + 0x2f0,param_1 + 0x1d8);
    if ((iVar1 == 0) && (iVar1 = vorbis_synthesis_blockin(param_1 + 0x260,param_1 + 0x2f0), iVar1 != 0)) {
      return 0xfffffffffffffc48;
    }
    uVar2 = Aska::AskaOGG::Decode_Pcmout(unsigned int)(param_1,(int)uVar3 + param_2);
    if ((long)uVar2 < 0) {
      return uVar2;
    }
    uVar5 = uVar5 + (int)uVar2;
    uVar3 = uVar3 + (uVar2 & 0xffffffff) * 2 * (long)*(int *)(param_1 + 0x20c);
  } while (((*(int *)(param_1 + 0x434) != 0) || (uVar5 <= uVar4)) ||
          (*(char *)(param_1 + 0x3c9) != '\0'));
  *(undefined1 *)(param_1 + 0x3c8) = 1;
  return uVar3;
}

// ==== Aska::AskaOGG::DecodePageReset()
// vaddr 0x2240690 | ghidra 0x2340690 | size 80 | symbol _ZN4Aska7AskaOGG15DecodePageResetEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska7AskaOGG15DecodePageResetEv(undefined8 *param_1,long param_2)

{
  int iVar1;
  
  *param_1 = 0;
  iVar1 = ogg_stream_reset(param_2 + 0x20);
  if ((iVar1 == 0) && (iVar1 = vorbis_synthesis_restart(param_2 + 0x260), iVar1 == 0)) {
    (*(code *)PTR_ogg_sync_reset_02c9b388)(param_2);
    return;
  }
  *param_1 = 0xffffffffffffffff;
  return;
}

// ==== Aska::AskaOGG::PacketDecoder::Reset()
// vaddr 0x22406e0 | ghidra 0x23406e0 | size 20 | symbol _ZN4Aska7AskaOGG13PacketDecoder5ResetEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska7AskaOGG13PacketDecoder5ResetEv(undefined8 *param_1)

{
  *(undefined4 *)((long)param_1 + 0x14) = 0;
  *(undefined1 *)((long)param_1 + 0x19) = 0;
  *param_1 = 0;
  *(undefined4 *)(param_1 + 1) = 0;
  return;
}

// ==== Aska::AskaOGG::PacketDecoder::Progress(unsigned int, signed char const*, unsigned int)
// vaddr 0x22406f4 | ghidra 0x23406f4 | size 24 | symbol _ZN4Aska7AskaOGG13PacketDecoder8ProgressEjPKaj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska7AskaOGG13PacketDecoder8ProgressEjPKaj
               (undefined8 *param_1,int param_2,undefined8 param_3,undefined4 param_4)

{
  *param_1 = param_3;
  *(undefined4 *)(param_1 + 1) = param_4;
  *(int *)((long)param_1 + 0x14) = *(int *)((long)param_1 + 0x14) + param_2;
  return;
}

// ==== Aska::AskaOGG::Decode_CalcFrameSample(unsigned int) const
// vaddr 0x224070c | ghidra 0x234070c | size 36 | symbol _ZNK4Aska7AskaOGG22Decode_CalcFrameSampleEj | lib libSOA-3.7.0.so | 2026-10-04
uint _ZNK4Aska7AskaOGG22Decode_CalcFrameSampleEj(long param_1,uint param_2)

{
  uint uVar1;
  uint uVar2;
  
  if (*(uint *)(param_1 + 0x3bc) != 0) {
    uVar2 = *(uint *)(param_1 + 0x3c0);
    uVar1 = *(uint *)(param_1 + 0x3bc);
    if (param_2 <= uVar2 && uVar2 != 0) {
      uVar1 = uVar2;
    }
    return uVar1;
  }
  return 0;
}

// ==== Aska::AskaOGG::Decode_Pcmout(unsigned int)
// vaddr 0x2240730 | ghidra 0x2340730 | size 540 | symbol _ZN4Aska7AskaOGG13Decode_PcmoutEj | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

long _ZN4Aska7AskaOGG13Decode_PcmoutEj(long param_1,int param_2)

{
  int iVar1;
  float fVar2;
  uint uVar3;
  long lVar4;
  uint uVar5;
  ulong uVar6;
  long lVar7;
  uint uVar8;
  float *pfVar9;
  undefined2 *puVar10;
  int iVar11;
  long lVar12;
  undefined8 uVar13;
  uint uVar14;
  long lStack_78;
  
  fVar2 = _UNK_029d311c;
  lVar12 = 0;
  iVar1 = *(int *)(param_1 + 0x20c) * 2;
  do {
    uVar3 = vorbis_synthesis_pcmout(param_1 + 0x260,&lStack_78);
    if (uVar3 == 0) {
      return lVar12;
    }
    if ((int)uVar3 < 0) {
      return -1;
    }
    uVar6 = (ulong)*(uint *)(param_1 + 0x430);
    uVar5 = param_2 + (int)lVar12 * iVar1;
    uVar14 = *(uint *)(param_1 + uVar6 * 4 + 0x410);
    while (lVar4 = param_1 + uVar6 * 8, uVar14 < uVar5 + uVar3 * iVar1) {
      uVar13 = *(undefined8 *)(lVar4 + 0x3d0);
      lVar4 = Aska::SoundMemory::ResourceAlloc(unsigned long, unsigned long)(uVar14 + 0x10000,0x200);
      if (lVar4 == 0) {
        return -0x3bf;
      }
      lVar7 = param_1 + 0x410;
      memcpy(lVar4,uVar13,*(undefined4 *)(lVar7 + (ulong)*(uint *)(param_1 + 0x430) * 4));
      Aska::SoundMemory::ResourceFree(void*)(uVar13);
      *(long *)(param_1 + (ulong)*(uint *)(param_1 + 0x430) * 8 + 0x3d0) = lVar4;
      *(uint *)(lVar7 + (ulong)*(uint *)(param_1 + 0x430) * 4) = uVar14 + 0x101ff & 0xfffffe00;
      *(uint *)PTR__ZN4Aska7AskaOGG18m_uiDecodePoolSizeE_02cb88d8 = uVar14 + 0x10000;
      uVar6 = (ulong)*(uint *)(param_1 + 0x430);
      uVar14 = *(uint *)(lVar7 + uVar6 * 4);
    }
    lVar4 = *(long *)(lVar4 + 0x3d0) + (ulong)uVar5;
    if (lVar4 == 0) {
      return -0x3bf;
    }
    uVar14 = *(uint *)(param_1 + 0x20c);
    if (0 < (int)uVar14) {
      if ((int)uVar3 < 1) {
        if (uVar14 < 2) {
          uVar5 = 0;
        }
        else {
          uVar5 = uVar14 & 0xfffffffe;
          uVar8 = uVar5;
          if (uVar5 != 0) {
            do {
              uVar8 = uVar8 - 2;
            } while (uVar8 != 0);
            if (uVar14 == uVar5) goto code_r0x023408fc;
          }
        }
        do {
          uVar5 = uVar5 + 1;
        } while ((int)uVar5 < (int)uVar14);
      }
      else {
        lVar7 = 0;
        do {
          puVar10 = (undefined2 *)(lVar4 + lVar7 * 2);
          pfVar9 = *(float **)(lStack_78 + lVar7 * 8);
          uVar6 = (ulong)uVar3;
          do {
            uVar6 = uVar6 - 1;
            iVar11 = (int)(*pfVar9 * fVar2 + 0.5);
            if (0x7ffe < iVar11) {
              iVar11 = 0x7fff;
            }
            if (iVar11 < -0x7fff) {
              iVar11 = -0x8000;
            }
            *puVar10 = (short)iVar11;
            puVar10 = puVar10 + *(int *)(param_1 + 0x20c);
            pfVar9 = pfVar9 + 1;
          } while (uVar6 != 0);
          lVar7 = lVar7 + 1;
        } while (lVar7 < *(int *)(param_1 + 0x20c));
      }
    }
code_r0x023408fc:
    iVar11 = vorbis_synthesis_read(param_1 + 0x260,uVar3);
    lVar12 = lVar12 + (int)uVar3;
    if (iVar11 != 0) {
      return -0x3b8;
    }
  } while( true );
}

// ==== Aska::AskaOGG::Decode_GetDstBuffer(unsigned int, unsigned int)
// vaddr 0x224094c | ghidra 0x234094c | size 224 | symbol _ZN4Aska7AskaOGG19Decode_GetDstBufferEjj | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska7AskaOGG19Decode_GetDstBufferEjj(long param_1,uint param_2,int param_3)

{
  long lVar1;
  uint uVar2;
  undefined *puVar3;
  long lVar4;
  ulong uVar5;
  undefined8 uVar6;
  
  puVar3 = PTR__ZN4Aska7AskaOGG18m_uiDecodePoolSizeE_02cb88d8;
  uVar5 = (ulong)*(uint *)(param_1 + 0x430);
  uVar2 = *(uint *)(param_1 + uVar5 * 4 + 0x410);
  while( true ) {
    if (param_3 + param_2 <= uVar2) {
      return *(long *)(param_1 + uVar5 * 8 + 0x3d0) + (ulong)param_2;
    }
    uVar6 = *(undefined8 *)(param_1 + uVar5 * 8 + 0x3d0);
    lVar4 = Aska::SoundMemory::ResourceAlloc(unsigned long, unsigned long)(uVar2 + 0x10000,0x200);
    if (lVar4 == 0) break;
    lVar1 = param_1 + 0x410;
    memcpy(lVar4,uVar6,*(undefined4 *)(lVar1 + (ulong)*(uint *)(param_1 + 0x430) * 4));
    Aska::SoundMemory::ResourceFree(void*)(uVar6);
    *(long *)(param_1 + (ulong)*(uint *)(param_1 + 0x430) * 8 + 0x3d0) = lVar4;
    *(uint *)(lVar1 + (ulong)*(uint *)(param_1 + 0x430) * 4) = uVar2 + 0x101ff & 0xfffffe00;
    *(uint *)puVar3 = uVar2 + 0x10000;
    uVar5 = (ulong)*(uint *)(param_1 + 0x430);
    uVar2 = *(uint *)(lVar1 + uVar5 * 4);
  }
  return 0;
}

// ==== Aska::AskaOGG::PacketDecoder::PacketDecoder()
// vaddr 0x2240a2c | ghidra 0x2340a2c | size 16 | symbol _ZN4Aska7AskaOGG13PacketDecoderC1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska7AskaOGG13PacketDecoderC2Ev(undefined8 *param_1)

{
  *(undefined2 *)(param_1 + 3) = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  *param_1 = 0;
  return;
}

// ==== Aska::AskaOGG::DecodeContext::DecodeContext()
// vaddr 0x2240a3c | ghidra 0x2340a3c | size 48 | symbol _ZN4Aska7AskaOGG13DecodeContextC2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska7AskaOGG13DecodeContextC1Ev(long param_1)

{
  *(undefined8 *)(param_1 + 0x440) = 0;
  memset(param_1,0,0x3ca);
  memset(param_1 + 0x3d0,0,0x6e);
  return;
}

// ==== Aska::AskaOGG::DecodeContext::~DecodeContext()
// vaddr 0x2240a6c | ghidra 0x2340a6c | size 188 | symbol _ZN4Aska7AskaOGG13DecodeContextD2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska7AskaOGG13DecodeContextD1Ev(long param_1)

{
  if (*(long *)(param_1 + 0x3d0) != 0) {
    Aska::SoundMemory::ResourceFree(void*)();
    *(undefined8 *)(param_1 + 0x3d0) = 0;
  }
  if (*(long *)(param_1 + 0x3d8) != 0) {
    Aska::SoundMemory::ResourceFree(void*)();
    *(undefined8 *)(param_1 + 0x3d8) = 0;
  }
  if (*(long *)(param_1 + 0x3e0) != 0) {
    Aska::SoundMemory::ResourceFree(void*)();
    *(undefined8 *)(param_1 + 0x3e0) = 0;
  }
  if (*(long *)(param_1 + 1000) != 0) {
    Aska::SoundMemory::ResourceFree(void*)();
    *(undefined8 *)(param_1 + 1000) = 0;
  }
  if (*(long *)(param_1 + 0x3f0) != 0) {
    Aska::SoundMemory::ResourceFree(void*)();
    *(undefined8 *)(param_1 + 0x3f0) = 0;
  }
  if (*(long *)(param_1 + 0x3f8) != 0) {
    Aska::SoundMemory::ResourceFree(void*)();
    *(undefined8 *)(param_1 + 0x3f8) = 0;
  }
  if (*(long *)(param_1 + 0x400) != 0) {
    Aska::SoundMemory::ResourceFree(void*)();
    *(undefined8 *)(param_1 + 0x400) = 0;
  }
  if (*(long *)(param_1 + 0x408) != 0) {
    Aska::SoundMemory::ResourceFree(void*)();
    *(undefined8 *)(param_1 + 0x408) = 0;
  }
  vorbis_block_clear(param_1 + 0x2f0);
  vorbis_dsp_clear(param_1 + 0x260);
  vorbis_comment_clear(param_1 + 0x240);
  vorbis_info_clear(param_1 + 0x208);
  ogg_stream_clear(param_1 + 0x20);
  (*(code *)PTR_ogg_sync_clear_02c9f128)(param_1);
  return;
}


// FAILED to create function at 02ce7120 Aska::AskaOGG::m_uiDecodePoolSize
