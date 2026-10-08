// port/decomp/audio/voice.c: Ghidra decompiles for the audio subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-08 13:03 UTC: tools/decomp.sh '--into' 'audio/voice' 'Aska::(SLVoice|WavePlayer|WaveVoiceBase|WaveBuffer)::'

// ==== Aska::SLVoice::SLVoice()
// vaddr 0x223bf54 | ghidra 0x233bf54 | size 192 | symbol _ZN4Aska7SLVoiceC1Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska7SLVoiceC2Ev(long *param_1)

{
  undefined *puVar1;
  
  Aska::WaveVoiceBase::WaveVoiceBase()();
  puVar1 = PTR__ZTVN4Aska7SLVoiceE_02cbc328;
  param_1[6] = 0;
  *param_1 = (long)(puVar1 + 0x10);
  Aska::AskaOGG::AskaOGG()(param_1 + 0xb);
  param_1[0x95] =
       (long)(PTR__ZTVN4Aska6TQueueINS_7SLVoice18AdpcmSubmitContextELi3EEE_02cbf3e8 + 0x10);
  puVar1 = PTR__ZTVN4Aska6TQueueINS_7SLVoice16OggSubmitContextELi8EEE_02cbcec0;
  *(undefined4 *)(param_1 + 0x96) = 1;
  *(undefined4 *)((long)param_1 + 0x4b4) = 0;
  param_1[0x98] = (long)(puVar1 + 0x10);
  *(undefined4 *)(param_1 + 0x99) = 1;
  *(undefined4 *)((long)param_1 + 0x4cc) = 0;
  *(undefined4 *)(param_1 + 0xa3) = 0;
  param_1[0xaa] = 0;
  *(undefined4 *)(param_1 + 0xab) = 0;
  param_1[0xa8] = 0;
  param_1[0xa7] = 0;
  param_1[0xa6] = 0;
  param_1[0xa5] = 0;
  param_1[0xa4] = 0;
  *(undefined2 *)(param_1 + 0xa9) = 0;
  *(undefined8 *)((long)param_1 + 0x59c) = 0;
  *(undefined8 *)((long)param_1 + 0x594) = 0;
  *(undefined4 *)((long)param_1 + 0x5a4) = 0xc;
  Aska::FastCriticalSection::FastCriticalSection()(param_1 + 0xb5);
  *(undefined4 *)(param_1 + 199) = 0;
  *(undefined4 *)((long)param_1 + 0x63c) = 0;
  *(undefined1 *)(param_1 + 200) = 0;
  *(undefined1 *)((long)param_1 + 0x641) = 0;
  param_1[0xb1] = 0;
  param_1[0xb0] = 0;
  param_1[0xaf] = 0;
  param_1[0xae] = 0;
  param_1[0xad] = 0;
  param_1[0xac] = 0;
  *(undefined4 *)(param_1 + 0xb2) = 0;
  return;
}

// ==== Aska::SLVoice::~SLVoice()
// vaddr 0x223c014 | ghidra 0x233c014 | size 64 | symbol _ZN4Aska7SLVoiceD1Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska7SLVoiceD2Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska7SLVoiceE_02cbc328 + 0x10);
  Aska::FastCriticalSection::~FastCriticalSection()(param_1 + 0xb5);
  Aska::AskaOGG::DecodeContext::~DecodeContext()(param_1 + 0xb);
  (*(code *)PTR__ZN4Aska13WaveVoiceBaseD1Ev_02c93140)(param_1);
  return;
}

// ==== Aska::TQueue<Aska::SLVoice::OggSubmitContext, 8>::~TQueue()
// vaddr 0x223c054 | ghidra 0x233c054 | size 4 | symbol _ZN4Aska6TQueueINS_7SLVoice16OggSubmitContextELi8EED2Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska6TQueueINS_7SLVoice16OggSubmitContextELi8EED2Ev(void)

{
  return;
}

// ==== Aska::TQueue<Aska::SLVoice::AdpcmSubmitContext, 3>::~TQueue()
// vaddr 0x223c058 | ghidra 0x233c058 | size 4 | symbol _ZN4Aska6TQueueINS_7SLVoice18AdpcmSubmitContextELi3EED2Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska6TQueueINS_7SLVoice18AdpcmSubmitContextELi3EED2Ev(void)

{
  return;
}

// ==== Aska::SLVoice::~SLVoice()
// vaddr 0x223c05c | ghidra 0x233c05c | size 72 | symbol _ZN4Aska7SLVoiceD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska7SLVoiceD0Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska7SLVoiceE_02cbc328 + 0x10);
  Aska::FastCriticalSection::~FastCriticalSection()(param_1 + 0xb5);
  Aska::AskaOGG::DecodeContext::~DecodeContext()(param_1 + 0xb);
  Aska::WaveVoiceBase::~WaveVoiceBase()(param_1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::SLVoice::CreateVoice(Aska::IBus*, void const*, Aska::MultiMediaStream*, Aska::PackedPlayParams const*)
// vaddr 0x223c0a4 | ghidra 0x233c0a4 | size 1940 | symbol _ZN4Aska7SLVoice11CreateVoiceEPNS_4IBusEPKvPNS_16MultiMediaStreamEPKNS_16PackedPlayParamsE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Removing unreachable block (ram,0x0233c7a8) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8
_ZN4Aska7SLVoice11CreateVoiceEPNS_4IBusEPKvPNS_16MultiMediaStreamEPKNS_16PackedPlayParamsE
          (long *param_1,long *param_2,undefined8 param_3,long *param_4,undefined4 *param_5)

{
  uint uVar1;
  undefined *puVar2;
  uint uVar3;
  byte bVar4;
  byte bVar5;
  uint uVar6;
  undefined *puVar7;
  int iVar8;
  ulong uVar9;
  long *plVar10;
  long *plVar11;
  long lVar12;
  undefined8 uVar13;
  undefined8 *puVar14;
  undefined4 uVar15;
  long lVar16;
  long lVar17;
  code *pcVar18;
  uint uVar19;
  undefined8 uVar20;
  undefined8 uVar21;
  float fVar22;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined8 uStack_98;
  undefined4 *puStack_90;
  undefined8 uStack_88;
  undefined4 auStack_80 [2];
  undefined8 uStack_78;
  undefined4 *puStack_70;
  undefined4 *puStack_68;
  undefined4 uStack_60;
  uint uStack_5c;
  int iStack_58;
  uint uStack_54;
  uint uStack_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_38;
  undefined4 uStack_34;
  
  uVar9 = Aska::WaveVoiceBase::CreateVoiceCommon(void const*, Aska::PackedPlayParams const*)(param_1,param_3,param_5);
  if ((uVar9 & 1) == 0) {
    if (param_4 == (long *)0x0) {
      return 0;
    }
    pcVar18 = *(code **)(*param_4 + 8);
    goto code_r0x0233c5c4;
  }
  iVar8 = Aska::AFF::AacUtil::GetBitRateType(Aska::AACWAVFORMAT)(*(undefined1 *)(param_1[2] + 0x14));
  if (iVar8 == 1) {
    plVar10 = (long *)Aska::SoundMemory::Malloc(unsigned long)(0x78);
    param_1[6] = (long)plVar10;
    plVar11 = (long *)0x0;
    if (plVar10 != (long *)0x0) {
      plVar10[1] = 0;
      plVar10[2] = 0;
      puVar2 = PTR__ZTVN4Aska9VBRBufferE_02cbd530 + 0x10;
      plVar10[3] = (long)(PTR__ZTVN4Aska6TQueueIjLi16EEE_02cbd6d0 + 0x10);
      *(undefined4 *)(plVar10 + 4) = 1;
      *(undefined4 *)((long)plVar10 + 0x24) = 0;
      *plVar10 = (long)puVar2;
      *(undefined2 *)((long)plVar10 + 0x74) = 0;
      *(undefined1 *)((long)plVar10 + 0x76) = 0;
      *(undefined4 *)(plVar10 + 0xe) = 1;
code_r0x0233c198:
      plVar11 = (long *)param_1[6];
    }
code_r0x0233c19c:
    if ((plVar11 != (long *)0x0) &&
       (uVar9 = (**(code **)(*plVar11 + 0x10))(plVar11,param_4,param_1[2]), (uVar9 & 1) != 0))
    goto code_r0x0233c1b8;
    if (param_4 != (long *)0x0) {
      (**(code **)(*param_4 + 8))(param_4);
    }
  }
  else {
    if (iVar8 == 0) {
      plVar10 = (long *)Aska::SoundMemory::Malloc(unsigned long)(0x78);
      param_1[6] = (long)plVar10;
      plVar11 = (long *)0x0;
      if (plVar10 != (long *)0x0) {
        plVar10[1] = 0;
        plVar10[2] = 0;
        puVar2 = PTR__ZTVN4Aska9CBRBufferE_02cbe388 + 0x10;
        plVar10[3] = (long)(PTR__ZTVN4Aska6TQueueIjLi16EEE_02cbd6d0 + 0x10);
        *(undefined4 *)(plVar10 + 4) = 1;
        *(undefined4 *)((long)plVar10 + 0x24) = 0;
        *plVar10 = (long)puVar2;
        *(undefined4 *)(plVar10 + 0xe) = 0;
        goto code_r0x0233c198;
      }
      goto code_r0x0233c19c;
    }
code_r0x0233c1b8:
    param_1[0xa4] = (long)param_2;
    fVar22 = (float)NEON_ucvtf(*param_5);
    *(int *)(param_1 + 0xb4) = (int)(fVar22 / _UNK_029d94a4);
    *(undefined4 *)(param_1 + 199) = 0;
    lVar12 = (**(code **)(*param_4 + 0x60))(param_4);
    lVar16 = param_1[2];
    bVar4 = *(byte *)(lVar16 + 0x14);
    *(uint *)((long)param_1 + 0x5a4) = (uint)bVar4;
    lVar17 = _UNK_029d94b0;
    if (bVar4 == 0xe) {
      *(undefined8 *)((long)param_1 + 0x594) = 0x800002000;
      *(undefined4 *)((long)param_1 + 0x59c) = 0;
      *(undefined4 *)(param_1 + 0xa3) = 0;
      if (*(uint *)(lVar16 + 0x58) == 0) {
        iVar8 = 0;
      }
      else {
        iVar8 = *(int *)(lVar16 + 0x68) +
                *(int *)((ulong)*(uint *)(lVar16 + 0x48) + lVar16 +
                        (ulong)*(uint *)(lVar16 + 0x58) * 4);
      }
      Aska::AskaOGG::DecodeInit(unsigned int, unsigned int)(&uStack_60,param_1 + 0xb,*(undefined4 *)(lVar16 + 100),iVar8);
      if ((int)uStack_5c < 0) goto code_r0x0233c5b0;
    }
    else if (bVar4 == 0xd) {
      param_1[0xb3] = _UNK_029d94b8;
      param_1[0xb2] = lVar17;
      uVar9 = Aska::AskaADPCM::Init(int, int, int)(param_1 + 7,*(undefined1 *)(lVar16 + 0x15),
                              *(undefined1 *)(lVar16 + 0x17),0x40);
      if ((uVar9 & 1) == 0) goto code_r0x0233c5b0;
    }
    else if (bVar4 == 0xc) {
      if (*(char *)(param_5 + 4) == '\0') {
        if (lVar12 < 0) goto code_r0x0233c5b0;
        *(int *)((long)param_1 + 0x594) = (int)lVar12;
        param_1[0xb3] = 3;
      }
      else {
        *(undefined4 *)((long)param_1 + 0x594) = 0x4000;
      }
    }
    puVar2 = PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50;
    plVar11 = *(long **)(*(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50 + 0x30);
    uVar13 = (**(code **)(*param_2 + 0x18))(param_2);
    lVar17 = param_1[2];
    bVar4 = *(byte *)(lVar17 + 0x15);
    bVar5 = *(byte *)(lVar17 + 0x17);
    if (bVar4 == 1) {
      uVar15 = 4;
    }
    else if (bVar4 == 4) {
      uVar15 = 0x33;
    }
    else {
      if (bVar4 != 2) goto code_r0x0233c5b0;
      uVar15 = 3;
    }
    iVar8 = *(int *)(lVar17 + 0x18) * 1000;
    if (iVar8 < 32000000) {
      if (iVar8 < 16000000) {
        if (((iVar8 == 8000000) || (iVar8 == 0xa83a68)) || (iVar8 == 12000000)) {
code_r0x0233c450:
          uVar19 = bVar5 - 8;
          uVar19 = uVar19 * 0x40 & 0xff | uVar19 >> 2 & 0x3f;
          if ((uVar19 < 7) && (uVar19 != 1)) {
            uStack_38 = 0x800007bd;
            uStack_34 = (undefined4)param_1[0xb3];
            uStack_60 = 2;
            uStack_54 = (uint)bVar5;
            puStack_70 = &uStack_38;
            uStack_50 = uStack_54;
            if (bVar5 != 0x10 && uStack_54 != 8) {
              uStack_50 = 0x20;
            }
            puStack_68 = &uStack_60;
            auStack_80[0] = 4;
            puStack_90 = auStack_80;
            uStack_a8 = *(undefined8 *)PTR_SL_IID_BUFFERQUEUE_02cba1a8;
            uVar21 = *(undefined8 *)PTR_SL_IID_VOLUME_02cc2f08;
            uStack_88 = 0;
            uVar20 = *(undefined8 *)PTR_SL_IID_PLAYBACKRATE_02cc2858;
            uStack_48 = 2;
            uStack_a0 = uVar21;
            uStack_98 = uVar20;
            uStack_78 = uVar13;
            uStack_5c = (uint)bVar4;
            iStack_58 = iVar8;
            uStack_4c = uVar15;
            iVar8 = (**(code **)(*plVar11 + 0x10))
                              (plVar11,param_1 + 0xa5,&puStack_70,&puStack_90,3,&uStack_a8,
                               &UNK_029d94c0);
            if (((iVar8 == 0) &&
                (puVar14 = (undefined8 *)param_1[0xa5], iVar8 = (**(code **)*puVar14)(puVar14,0),
                iVar8 == 0)) &&
               (iVar8 = (**(code **)(*(long *)param_1[0xa5] + 0x18))
                                  ((long *)param_1[0xa5],*(undefined8 *)PTR_SL_IID_PLAY_02cb8760,
                                   param_1 + 0xa6), iVar8 == 0)) {
              iVar8 = (**(code **)(*(long *)param_1[0xa5] + 0x18))
                                ((long *)param_1[0xa5],
                                 *(undefined8 *)PTR_SL_IID_ANDROIDSIMPLEBUFFERQUEUE_02cb7098,
                                 param_1 + 0xa7);
              if ((iVar8 == 0) &&
                 (iVar8 = (**(code **)(*(long *)param_1[0xa7] + 0x18))
                                    ((long *)param_1[0xa7],
                                     PTR__ZN4Aska7SLVoice16SLPlayerCallbackEPKPK30SLAndroidSimpleBufferQueueItf_Pv_02cbc810
                                     ,param_1), iVar8 == 0)) {
                plVar11 = param_1 + 0xa8;
                iVar8 = (**(code **)(*(long *)param_1[0xa5] + 0x18))
                                  ((long *)param_1[0xa5],uVar21,plVar11);
                if (((iVar8 == 0xc) || (iVar8 == 0)) &&
                   ((plVar10 = (long *)*plVar11, plVar10 == (long *)0x0 ||
                    ((iVar8 = (**(code **)(*plVar10 + 0x10))(plVar10,param_1 + 0xa9), iVar8 == 0 &&
                     (iVar8 = (**(code **)(*(long *)*plVar11 + 0x28))((long *)*plVar11,1),
                     iVar8 == 0)))))) {
                  plVar11 = param_1 + 0xaa;
                  iVar8 = (**(code **)(*(long *)param_1[0xa5] + 0x18))
                                    ((long *)param_1[0xa5],uVar20,plVar11);
                  if ((iVar8 == 0xc) || (iVar8 == 0)) {
                    plVar10 = (long *)*plVar11;
                    if (plVar10 != (long *)0x0) {
                      iVar8 = (**(code **)(*plVar10 + 0x28))
                                        (plVar10,0,param_1 + 0xab,(long)param_1 + 0x55a,&uStack_a8,
                                         &uStack_60);
                      puVar7 = PTR__ZN4Aska7SLVoice12m_bNoWarningE_02cb92c8;
                      if (iVar8 != 0) goto code_r0x0233c5b0;
                      if ((*PTR__ZN4Aska7SLVoice12m_bNoWarningE_02cb92c8 == '\0') &&
                         (iVar8 = (**(code **)(*(long *)*plVar11 + 0x10))((long *)*plVar11,0x800),
                         iVar8 != 0)) {
                        if (iVar8 != 0xc) {
                          *puVar7 = 1;
                          goto code_r0x0233c5b0;
                        }
                        *puVar7 = 1;
                      }
                    }
                    (**(code **)(*param_1 + 0x58))(param_1);
                    (**(code **)(*param_1 + 0x60))(param_1);
                    *(undefined4 *)((long)param_1 + 0x63c) = 0;
                    *(undefined1 *)(param_1 + 200) = 0;
                    if ((int)param_1[0xb3] != 0) {
                      uVar19 = 0;
                      do {
                        iVar8 = *(int *)((long)param_1 + 0x5a4);
                        if (iVar8 == 0xe) {
                          Aska::SLVoice::LockAndSubmitOGG()(&uStack_60,param_1);
code_r0x0233c740:
                          uVar9 = CONCAT44(uStack_5c,uStack_60);
code_r0x0233c744:
                          if (uVar9 == 0xfffffffffffffc3f) break;
code_r0x0233c74c:
                          if ((long)uVar9 < 0) goto code_r0x0233c5b0;
                        }
                        else {
                          if (iVar8 == 0xd) {
                            Aska::SLVoice::LockAndSubmitADPCM()(&uStack_60,param_1);
                            goto code_r0x0233c740;
                          }
                          if (iVar8 == 0xc) {
                            uVar9 = (**(code **)(**(long **)(param_1[6] + 8) + 0xb8))
                                              (*(long **)(param_1[6] + 8),0,0);
                            if ((uVar9 & 1) == 0) {
                              uVar9 = Aska::WaveBuffer::LockBuffer(void**, unsigned long, bool)(param_1[6],&uStack_60,
                                                      *(undefined4 *)((long)param_1 + 0x594),0);
                              if ((long)uVar9 < 0) goto code_r0x0233c744;
                              puVar14 = (undefined8 *)param_1[0xa7];
                              iVar8 = (**(code **)*puVar14)
                                                (puVar14,CONCAT44(uStack_5c,uStack_60),
                                                 uVar9 & 0xffffffff);
                              if (iVar8 == 0) {
                                uVar3 = *(uint *)(param_1 + 0xb3);
                                uVar9 = 0;
                                uVar1 = *(int *)((long)param_1 + 0x59c) + 1;
                                uVar6 = 0;
                                if (uVar3 != 0) {
                                  uVar6 = uVar1 / uVar3;
                                }
                                *(uint *)((long)param_1 + 0x59c) = uVar1 - uVar6 * uVar3;
                              }
                              else {
                                uVar9 = 0xffffffffffffffff;
                              }
                              goto code_r0x0233c74c;
                            }
                            break;
                          }
                        }
                        uVar19 = uVar19 + 1;
                      } while (uVar19 < *(uint *)(param_1 + 0xb3));
                    }
                    *(undefined4 *)(param_1 + 199) = 0;
                    if ((1 < *(int *)((long)param_1 + 0x5a4) - 0xdU) ||
                       (uVar9 = Aska::AudioSignal::AddSignalVoiceList(Aska::SLVoice*)(*(undefined8 *)(*(long *)puVar2 + 0x40),param_1),
                       (uVar9 & 1) != 0)) {
                      *(undefined1 *)((long)param_1 + 0x2a) = 1;
                      return 1;
                    }
                  }
                }
              }
            }
          }
        }
      }
      else if (((iVar8 == 16000000) || (iVar8 == 0x15074d0)) || (iVar8 == 24000000))
      goto code_r0x0233c450;
    }
    else if (iVar8 < 64000000) {
      if (((iVar8 == 32000000) || (iVar8 == 44100000)) || (iVar8 == 48000000))
      goto code_r0x0233c450;
    }
    else if (iVar8 < 96000000) {
      if ((iVar8 == 64000000) || (iVar8 == 88200000)) goto code_r0x0233c450;
    }
    else if ((iVar8 == 192000000) || (iVar8 == 96000000)) goto code_r0x0233c450;
  }
code_r0x0233c5b0:
  *(undefined1 *)((long)param_1 + 0x2a) = 1;
  pcVar18 = *(code **)(*param_1 + 0x18);
  param_4 = param_1;
code_r0x0233c5c4:
  (*pcVar18)(param_4);
  return 0;
}

// ==== Aska::SLVoice::SLPlayerCallback(SLAndroidSimpleBufferQueueItf_ const* const*, void*)
// vaddr 0x223c838 | ghidra 0x233c838 | size 8 | symbol _ZN4Aska7SLVoice16SLPlayerCallbackEPKPK30SLAndroidSimpleBufferQueueItf_Pv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska7SLVoice16SLPlayerCallbackEPKPK30SLAndroidSimpleBufferQueueItf_Pv
               (undefined8 param_1,undefined8 param_2)

{
  (*(code *)PTR__ZN4Aska7SLVoice15ProcAudioBufferEv_02cb3490)(param_2);
  return;
}

// ==== Aska::SLVoice::LockAndSubmitData()
// vaddr 0x223c840 | ghidra 0x233c840 | size 164 | symbol _ZN4Aska7SLVoice17LockAndSubmitDataEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska7SLVoice17LockAndSubmitDataEv(ulong *param_1,long param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  long *plVar5;
  ulong uVar6;
  undefined8 uStack_18;
  
  plVar5 = *(long **)(*(long *)(param_2 + 0x30) + 8);
  uVar6 = (**(code **)(*plVar5 + 0xb8))(plVar5,0,0);
  if ((uVar6 & 1) == 0) {
    uVar6 = Aska::WaveBuffer::LockBuffer(void**, unsigned long, bool)(*(undefined8 *)(param_2 + 0x30),&uStack_18,
                            *(undefined4 *)(param_2 + 0x594),0);
    if (-1 < (long)uVar6) {
      iVar4 = (**(code **)**(undefined8 **)(param_2 + 0x538))
                        (*(undefined8 **)(param_2 + 0x538),uStack_18,uVar6 & 0xffffffff);
      if (iVar4 == 0) {
        uVar2 = *(uint *)(param_2 + 0x598);
        uVar6 = 0;
        uVar1 = *(int *)(param_2 + 0x59c) + 1;
        uVar3 = 0;
        if (uVar2 != 0) {
          uVar3 = uVar1 / uVar2;
        }
        *(uint *)(param_2 + 0x59c) = uVar1 - uVar3 * uVar2;
      }
      else {
        uVar6 = 0xffffffffffffffff;
      }
    }
  }
  else {
    uVar6 = 0xfffffffffffffc3f;
  }
  *param_1 = uVar6;
  return;
}

// ==== Aska::SLVoice::LockAndSubmitADPCM()
// vaddr 0x223c8e4 | ghidra 0x233c8e4 | size 424 | symbol _ZN4Aska7SLVoice18LockAndSubmitADPCMEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska7SLVoice18LockAndSubmitADPCMEv(ulong *param_1,long param_2)

{
  uint uVar1;
  int *piVar2;
  uint uVar3;
  char cVar4;
  bool bVar5;
  uint uVar6;
  int iVar7;
  long *plVar8;
  ulong uVar9;
  int iVar10;
  undefined8 uStack_38;
  
  iVar10 = 0;
  iVar7 = -0x40;
code_r0x0233c904:
  iVar7 = iVar7 + 1;
  if (iVar7 != 0) {
    plVar8 = *(long **)(*(long *)(param_2 + 0x30) + 8);
    uVar9 = (**(code **)(*plVar8 + 0xb8))(plVar8,0,0);
    if ((uVar9 & 1) != 0) {
      piVar2 = (int *)(param_2 + 0x638);
      do {
        cVar4 = '\x01';
        bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
        if (bVar5) {
          *piVar2 = *piVar2 + -1;
          cVar4 = ExclusiveMonitorsStatus();
        }
        uVar9 = 0xfffffffffffffc3f;
      } while (cVar4 != '\0');
      goto code_r0x0233ca54;
    }
    cVar4 = *(char *)(*(long *)(*(long *)(param_2 + 0x30) + 8) + 0x8c);
    uVar9 = Aska::WaveBuffer::LockBuffer(void**, unsigned long, bool)(*(long *)(param_2 + 0x30),&uStack_38,*(undefined4 *)(param_2 + 0x594),
                            iVar10);
    if ((long)uVar9 < 0) {
      *(undefined1 *)(param_2 + 0x641) = 1;
      goto code_r0x0233ca54;
    }
    if ((int)uVar9 != 0) {
      uVar9 = Aska::SLVoice::SubmitBufferDataADPCM(void const*, unsigned int, bool)(param_2,uStack_38,uVar9 & 0xffffffff,cVar4 != '\0');
      if ((long)uVar9 < 0) goto code_r0x0233ca54;
      iVar10 = 1;
      if (uVar9 != 0) {
        uVar9 = 0;
code_r0x0233ca54:
        *param_1 = uVar9;
        return;
      }
      goto code_r0x0233c904;
    }
    if (iVar10 == 0) {
      uVar1 = *(uint *)(param_2 + 0x4b0);
      if (*(uint *)(param_2 + 0x4b4) == uVar1) goto code_r0x0233ca48;
      iVar7 = 0;
      if (uVar1 + 1 < 4) {
        iVar7 = uVar1 + 1;
      }
      *(undefined1 *)(param_2 + (ulong)uVar1 + 0x4b8) = 0;
      *(int *)(param_2 + 0x4b0) = iVar7;
      uVar9 = 0xfffffffffffffc15;
      goto code_r0x0233ca54;
    }
    iVar7 = (**(code **)**(undefined8 **)(param_2 + 0x538))
                      (*(undefined8 **)(param_2 + 0x538),
                       *(undefined8 *)
                        (*(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50 + 0x1228),
                       *(undefined4 *)
                        (*(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50 + 0x1230));
    if (iVar7 == 0) {
      uVar3 = *(uint *)(param_2 + 0x598);
      uVar1 = *(int *)(param_2 + 0x59c) + 1;
      uVar6 = 0;
      if (uVar3 != 0) {
        uVar6 = uVar1 / uVar3;
      }
      *(uint *)(param_2 + 0x59c) = uVar1 - uVar6 * uVar3;
      uVar1 = *(uint *)(param_2 + 0x4b0);
      if (*(uint *)(param_2 + 0x4b4) != uVar1) {
        *(undefined1 *)(param_2 + (ulong)uVar1 + 0x4b8) = 1;
        iVar7 = 0;
        if (uVar1 + 1 < 4) {
          iVar7 = uVar1 + 1;
        }
        piVar2 = (int *)(param_2 + 0x638);
        *(int *)(param_2 + 0x4b0) = iVar7;
        do {
          cVar4 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
          if (bVar5) {
            *piVar2 = *piVar2 + -1;
            cVar4 = ExclusiveMonitorsStatus();
          }
          uVar9 = 0xfffffffffffffc15;
        } while (cVar4 != '\0');
        goto code_r0x0233ca54;
      }
    }
  }
code_r0x0233ca48:
  *(undefined1 *)(param_2 + 0x641) = 1;
  uVar9 = 0xffffffffffffffff;
  goto code_r0x0233ca54;
}

// ==== Aska::SLVoice::LockAndSubmitOGG()
// vaddr 0x223ca8c | ghidra 0x233ca8c | size 416 | symbol _ZN4Aska7SLVoice16LockAndSubmitOGGEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska7SLVoice16LockAndSubmitOGGEv(ulong *param_1,long param_2)

{
  int *piVar1;
  uint uVar2;
  char cVar3;
  bool bVar4;
  uint uVar5;
  int iVar6;
  long *plVar7;
  uint uVar8;
  ulong uVar9;
  undefined8 uVar10;
  undefined8 uStack_38;
  undefined8 uStack_30;
  undefined8 uStack_28;
  
  iVar6 = 0;
code_r0x0233caa4:
  if (*(char *)(param_2 + 0x420) == '\0') {
    plVar7 = *(long **)(*(long *)(param_2 + 0x30) + 8);
    uVar9 = (**(code **)(*plVar7 + 0xb8))(plVar7,0,0);
    if ((uVar9 & 1) != 0) {
      piVar1 = (int *)(param_2 + 0x638);
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
        if (bVar4) {
          *piVar1 = *piVar1 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      uVar9 = 0xfffffffffffffc3f;
      goto code_r0x0233cc18;
    }
    uVar9 = Aska::VBRBuffer::LockBufferEx(void**, unsigned long, unsigned long*, unsigned long*, unsigned long, bool)(*(undefined8 *)(param_2 + 0x30),&uStack_28,
                            *(undefined4 *)(param_2 + 0x594),&uStack_30,&uStack_38,0,iVar6);
    if ((long)uVar9 < 0) {
      *(undefined1 *)(param_2 + 0x641) = 1;
      goto code_r0x0233cc18;
    }
    if ((int)uVar9 == 0) {
      if (iVar6 == 0) {
        uVar8 = *(uint *)(param_2 + 0x4c8);
        if (*(uint *)(param_2 + 0x4cc) == uVar8) goto code_r0x0233cbe8;
        uVar10 = 0;
      }
      else {
        iVar6 = (**(code **)**(undefined8 **)(param_2 + 0x538))
                          (*(undefined8 **)(param_2 + 0x538),
                           *(undefined8 *)
                            (*(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50 + 0x1228),
                           *(undefined4 *)
                            (*(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50 + 0x1230));
        if (iVar6 != 0) goto code_r0x0233cbe8;
        uVar2 = *(uint *)(param_2 + 0x598);
        uVar8 = *(int *)(param_2 + 0x59c) + 1;
        uVar5 = 0;
        if (uVar2 != 0) {
          uVar5 = uVar8 / uVar2;
        }
        *(uint *)(param_2 + 0x59c) = uVar8 - uVar5 * uVar2;
        piVar1 = (int *)(param_2 + 0x638);
        do {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar4) {
            *piVar1 = *piVar1 + -1;
            cVar3 = ExclusiveMonitorsStatus();
          }
        } while (cVar3 != '\0');
        uVar8 = *(uint *)(param_2 + 0x4c8);
        if (*(uint *)(param_2 + 0x4cc) == uVar8) {
code_r0x0233cbe8:
          *(undefined1 *)(param_2 + 0x641) = 1;
          uVar9 = 0xffffffffffffffff;
          goto code_r0x0233cc18;
        }
        uVar10 = 0x100000000;
      }
      iVar6 = 0;
      if (uVar8 + 1 < 9) {
        iVar6 = uVar8 + 1;
      }
      *(undefined8 *)(param_2 + (ulong)uVar8 * 8 + 0x4d0) = uVar10;
      *(int *)(param_2 + 0x4c8) = iVar6;
      uVar9 = 0xfffffffffffffc15;
      goto code_r0x0233cc18;
    }
  }
  else {
    uStack_28 = *(undefined8 *)(param_2 + 0x408);
    uStack_30 = 0;
    uVar9 = (ulong)*(uint *)(param_2 + 0x410);
    uStack_38 = 0;
  }
  uVar9 = Aska::SLVoice::SubmitBufferDataOGG(void const*, unsigned int, unsigned int, unsigned int)(param_2,uStack_28,uVar9 & 0xffffffff,uStack_30,uStack_38);
  if ((long)uVar9 < 0) goto code_r0x0233cc18;
  iVar6 = 1;
  if (uVar9 != 0) goto code_r0x0233cb38;
  goto code_r0x0233caa4;
code_r0x0233cb38:
  uVar9 = 0;
code_r0x0233cc18:
  *param_1 = uVar9;
  return;
}

// ==== Aska::SLVoice::DeleteVoice()
// vaddr 0x223cc2c | ghidra 0x233cc2c | size 608 | symbol _ZN4Aska7SLVoice11DeleteVoiceEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska7SLVoice11DeleteVoiceEv(long param_1)

{
  int *piVar1;
  int *piVar2;
  char cVar3;
  bool bVar4;
  ulong uVar5;
  int iVar6;
  
  if (*(char *)(param_1 + 0x2a) == '\0') {
    return;
  }
  if (*(int *)(param_1 + 0x5a4) - 0xdU < 2) {
    Aska::AudioSignal::DeleteSignalVoiceList(Aska::SLVoice*)(*(undefined8 *)(*(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50 + 0x40),
                    param_1);
  }
  piVar1 = (int *)(param_1 + 0x5e0);
  iVar6 = 0;
  do {
    while (*piVar1 == -1) {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = 0;
        cVar3 = ExclusiveMonitorsStatus();
      }
      if (cVar3 == '\0') goto code_r0x0233cd3c;
    }
    ClearExclusiveLocal();
    bVar4 = iVar6 < 0x1ff;
    iVar6 = iVar6 + 1;
  } while (bVar4);
  piVar2 = (int *)(param_1 + 0x5e4);
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
        uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0x620);
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
          Aska::Semaphore::Wait() const(param_1 + 0x620);
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
          if (cVar3 == '\0') goto code_r0x0233cd2c;
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
code_r0x0233cd2c:
  do {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar4) {
      *piVar2 = *piVar2 + -1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
code_r0x0233cd3c:
  DataMemoryBarrier(2,3);
  if (*(long **)(param_1 + 0x538) != (long *)0x0) {
    (**(code **)(**(long **)(param_1 + 0x538) + 8))();
    (**(code **)(**(long **)(param_1 + 0x538) + 0x18))(*(long **)(param_1 + 0x538),0,0);
  }
  *(undefined8 *)(param_1 + 0x550) = 0;
  *(undefined8 *)(param_1 + 0x540) = 0;
  *(undefined8 *)(param_1 + 0x530) = 0;
  if (*(long **)(param_1 + 0x528) != (long *)0x0) {
    (**(code **)(**(long **)(param_1 + 0x528) + 0x30))();
    *(undefined8 *)(param_1 + 0x528) = 0;
  }
  if (*(long **)(param_1 + 0x30) != (long *)0x0) {
    (**(code **)(**(long **)(param_1 + 0x30) + 8))();
    *(undefined8 *)(param_1 + 0x30) = 0;
  }
  if (*(int *)(param_1 + 0x5a4) == 0xd) {
    if (*(long *)(param_1 + 0x560) != 0) {
      Aska::SoundServer::ReleaseAskaAdpcmDecodeBuffer(void*)(*(undefined8 *)
                       (*(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50 + 0xe8));
      *(undefined8 *)(param_1 + 0x560) = 0;
      *(undefined8 *)(param_1 + 0x578) = 0;
    }
    if (*(long *)(param_1 + 0x568) != 0) {
      Aska::SoundServer::ReleaseAskaAdpcmDecodeBuffer(void*)(*(undefined8 *)
                       (*(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50 + 0xe8));
      *(undefined8 *)(param_1 + 0x568) = 0;
      *(undefined8 *)(param_1 + 0x580) = 0;
    }
    if (*(long *)(param_1 + 0x570) != 0) {
      Aska::SoundServer::ReleaseAskaAdpcmDecodeBuffer(void*)(*(undefined8 *)
                       (*(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50 + 0xe8));
      *(undefined8 *)(param_1 + 0x570) = 0;
      *(undefined8 *)(param_1 + 0x588) = 0;
    }
  }
  Aska::WaveVoiceBase::DeleteVoice()(param_1);
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_1 + 0x5e0) = 0xffffffff;
  DataMemoryBarrier(2,3);
  if (*(int *)(param_1 + 0x5e4) < 0x15) {
    return;
  }
  piVar1 = (int *)(param_1 + 0x5e4);
  do {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar4) {
      *piVar1 = *piVar1 + -1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
  uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0x620);
  if ((uVar5 & 1) == 0) {
    return;
  }
  (*(code *)PTR__ZNK4Aska9Semaphore6SignalEv_02c96cd0)(param_1 + 0x620);
  return;
}

// ==== Aska::SLVoice::Play()
// vaddr 0x223ce8c | ghidra 0x233ce8c | size 64 | symbol _ZN4Aska7SLVoice4PlayEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska7SLVoice4PlayEv(long param_1)

{
  int iVar1;
  
  if ((*(char *)(param_1 + 0x2a) != '\0') &&
     (iVar1 = (**(code **)**(undefined8 **)(param_1 + 0x530))(*(undefined8 **)(param_1 + 0x530),3),
     iVar1 == 0)) {
    *(undefined4 *)(param_1 + 8) = 1;
    return;
  }
  return;
}

// ==== Aska::SLVoice::Stop()
// vaddr 0x223cecc | ghidra 0x233cecc | size 56 | symbol _ZN4Aska7SLVoice4StopEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska7SLVoice4StopEv(long param_1)

{
  int iVar1;
  
  iVar1 = (**(code **)**(undefined8 **)(param_1 + 0x530))(*(undefined8 **)(param_1 + 0x530),1);
  if (iVar1 != 0) {
    return;
  }
  *(undefined4 *)(param_1 + 8) = 3;
  return;
}

// ==== Aska::SLVoice::Pause()
// vaddr 0x223cf04 | ghidra 0x233cf04 | size 56 | symbol _ZN4Aska7SLVoice5PauseEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska7SLVoice5PauseEv(long param_1)

{
  int iVar1;
  
  iVar1 = (**(code **)**(undefined8 **)(param_1 + 0x530))(*(undefined8 **)(param_1 + 0x530),2);
  if (iVar1 == 0) {
    *(undefined4 *)(param_1 + 8) = 2;
  }
  return;
}

// ==== Aska::SLVoice::Resume()
// vaddr 0x223cf3c | ghidra 0x233cf3c | size 56 | symbol _ZN4Aska7SLVoice6ResumeEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska7SLVoice6ResumeEv(long param_1)

{
  int iVar1;
  
  iVar1 = (**(code **)**(undefined8 **)(param_1 + 0x530))(*(undefined8 **)(param_1 + 0x530),3);
  if (iVar1 != 0) {
    return;
  }
  *(undefined4 *)(param_1 + 8) = 1;
  return;
}

// ==== Aska::SLVoice::GetElapsedTime() const
// vaddr 0x223cf74 | ghidra 0x233cf74 | size 28 | symbol _ZNK4Aska7SLVoice14GetElapsedTimeEv | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int _ZNK4Aska7SLVoice14GetElapsedTimeEv(long param_1)

{
  float fVar1;
  
  fVar1 = (float)NEON_ucvtf(*(undefined4 *)(param_1 + 0x5a0));
  return (int)(fVar1 * _UNK_029d94a4);
}

// ==== Aska::SLVoice::UpdateVolumeMatrix()
// vaddr 0x223cf90 | ghidra 0x233cf90 | size 244 | symbol _ZN4Aska7SLVoice18UpdateVolumeMatrixEv | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska7SLVoice18UpdateVolumeMatrixEv(long param_1)

{
  int iVar1;
  float fVar2;
  float fVar3;
  float fStack_18;
  float fStack_14;
  
  if (*(long *)(param_1 + 0x540) != 0) {
    Aska::AudioMixer::BuildFinalVolumeAndPanpot(float*, float*, float, float)(*(undefined4 *)(param_1 + 0x18),*(undefined4 *)(param_1 + 0x20),&fStack_14,
                    &fStack_18);
    fVar3 = _UNK_02965bf8;
    fVar2 = 0.0;
    if (_UNK_02965bf8 < fStack_14) {
      fVar2 = (float)powf(0x41200000,fStack_14 * _UNK_027edb4c);
    }
    if (_UNK_027fac84 <= ABS(fVar2 * *(float *)(param_1 + 0x24))) {
      fVar3 = (float)log10f();
      fVar3 = fVar3 * 20.0;
    }
    iVar1 = (int)(fVar3 * _UNK_027e5198);
    if ((short)iVar1 < -0x2580) {
      iVar1 = 0xda80;
    }
    else if (*(short *)(param_1 + 0x548) <= (short)iVar1) {
      iVar1 = (int)*(short *)(param_1 + 0x548);
    }
    fStack_14 = fVar3;
    (**(code **)**(undefined8 **)(param_1 + 0x540))(*(undefined8 **)(param_1 + 0x540),iVar1);
    (**(code **)(**(long **)(param_1 + 0x540) + 0x38))
              (*(long **)(param_1 + 0x540),(int)(fStack_18 * _UNK_027e51a0));
  }
  return;
}

// ==== Aska::SLVoice::UpdatePitchbend()
// vaddr 0x223d084 | ghidra 0x233d084 | size 104 | symbol _ZN4Aska7SLVoice15UpdatePitchbendEv | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska7SLVoice15UpdatePitchbendEv(long param_1)

{
  ulong uVar1;
  uint uVar2;
  undefined8 *puVar3;
  float fVar4;
  
  puVar3 = *(undefined8 **)(param_1 + 0x550);
  if (puVar3 != (undefined8 *)0x0) {
    fVar4 = (float)exp2f(*(undefined4 *)(param_1 + 0x1c));
    uVar1 = (ulong)*(short *)(param_1 + 0x558);
    uVar2 = (uint)(fVar4 * _UNK_027e51a0);
    if ((int)*(short *)(param_1 + 0x558) <= (int)uVar2) {
      if ((int)*(short *)(param_1 + 0x55a) <= (int)uVar2) {
        uVar2 = (uint)*(short *)(param_1 + 0x55a);
      }
      uVar1 = (ulong)uVar2;
    }
                    /* WARNING: Could not recover jumptable at 0x0233d0dc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)*puVar3)(puVar3,uVar1);
    return;
  }
  return;
}

// ==== Aska::SLVoice::AudioKick()
// vaddr 0x223d0ec | ghidra 0x233d0ec | size 60 | symbol _ZN4Aska7SLVoice9AudioKickEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska7SLVoice9AudioKickEv(long param_1)

{
  int *piVar1;
  char cVar2;
  bool bVar3;
  
  if (*(int *)(param_1 + 8) == 1) {
    if (*(char *)(param_1 + 0x640) == '\0') {
      *(int *)(param_1 + 0x5a0) = *(int *)(param_1 + 0x5a0) + 1;
    }
    else {
      piVar1 = (int *)(param_1 + 0x63c);
      do {
        cVar2 = '\x01';
        bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
        if (bVar3) {
          *piVar1 = *piVar1 + -0x10;
          cVar2 = ExclusiveMonitorsStatus();
        }
      } while (cVar2 != '\0');
    }
  }
  (*(code *)PTR__ZN4Aska13WaveVoiceBase9AudioKickEv_02cac8f8)();
  return;
}

// ==== Aska::SLVoice::AudioSignal(unsigned long)
// vaddr 0x223d128 | ghidra 0x233d128 | size 848 | symbol _ZN4Aska7SLVoice11AudioSignalEm | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska7SLVoice11AudioSignalEm(long param_1)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  char cVar4;
  bool bVar5;
  ulong uVar6;
  long *plVar7;
  ulong uVar8;
  int iVar9;
  long extraout_x8;
  long lVar10;
  int iVar11;
  float fVar12;
  float fVar13;
  long lStack_38;
  
  piVar1 = (int *)(param_1 + 0x5e0);
  iVar9 = 0;
  do {
    while (*piVar1 == -1) {
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar5) {
        *piVar1 = 0;
        cVar4 = ExclusiveMonitorsStatus();
      }
      if (cVar4 == '\0') goto code_r0x0233d20c;
    }
    ClearExclusiveLocal();
    bVar5 = iVar9 < 0x1ff;
    iVar9 = iVar9 + 1;
  } while (bVar5);
  piVar2 = (int *)(param_1 + 0x5e4);
  do {
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar5) {
      *piVar2 = *piVar2 + 1;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
  do {
    if (*piVar1 != -1) {
      ClearExclusiveLocal();
      do {
        uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x620);
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
          Aska::Semaphore::Wait() const(param_1 + 0x620);
        }
        do {
          cVar4 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
          if (bVar5) {
            *piVar2 = *piVar2 + 1;
            cVar4 = ExclusiveMonitorsStatus();
          }
        } while (cVar4 != '\0');
        while (*piVar1 == -1) {
          cVar4 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar5) {
            *piVar1 = 0;
            cVar4 = ExclusiveMonitorsStatus();
          }
          if (cVar4 == '\0') goto code_r0x0233d1fc;
        }
        ClearExclusiveLocal();
      } while( true );
    }
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar5) {
      *piVar1 = 0;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
code_r0x0233d1fc:
  do {
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar5) {
      *piVar2 = *piVar2 + -1;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
code_r0x0233d20c:
  DataMemoryBarrier(2,3);
  if (((*(char *)(param_1 + 0x641) == '\0') && (*(long *)(param_1 + 0x30) != 0)) &&
     (plVar7 = *(long **)(*(long *)(param_1 + 0x30) + 8),
     uVar6 = (**(code **)(*plVar7 + 0xb8))(plVar7,1,0), (uVar6 & 1) == 0)) {
    DataMemoryBarrier(2,3);
    iVar9 = *(int *)(param_1 + 0x638);
    if (0 < iVar9) {
      iVar11 = 0;
      piVar1 = (int *)(param_1 + 0x518);
      lVar10 = extraout_x8;
      do {
        if (*(int *)(param_1 + 0x5a4) == 0xe) {
          iVar3 = 0;
          if (*(int *)(param_1 + 0x4cc) + 1 < 9) {
            iVar3 = *(int *)(param_1 + 0x4cc) + 1;
          }
          if (iVar3 == *(int *)(param_1 + 0x4c8)) {
code_r0x0233d3d4:
            *(undefined1 *)(param_1 + 0x641) = 1;
            break;
          }
          uVar6 = *(ulong *)(param_1 + (long)iVar3 * 8 + 0x4d0);
          *(int *)(param_1 + 0x4cc) = iVar3;
          if ((uVar6 & 0xff00000000) != 0) {
            Aska::WaveBuffer::UnlockBuffer()(*(undefined8 *)(param_1 + 0x30));
            plVar7 = *(long **)(*(long *)(param_1 + 0x30) + 8);
            uVar8 = (**(code **)(*plVar7 + 0xb8))(plVar7,1,0);
            if ((uVar8 & 1) != 0) {
              fVar12 = *(float *)(*(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50 + 0x38);
              DataMemoryBarrier(2,3);
              fVar13 = _UNK_027dbad0;
              if (*(int *)(*(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50 + 0x3c) == 0) {
                fVar13 = 0.0;
              }
              do {
                cVar4 = '\x01';
                bVar5 = (bool)ExclusiveMonitorPass((int *)(param_1 + 0x63c),0x10);
                if (bVar5) {
                  *(int *)(param_1 + 0x63c) = (int)(fVar12 + fVar13);
                  cVar4 = ExclusiveMonitorsStatus();
                }
              } while (cVar4 != '\0');
code_r0x0233d46c:
              *(undefined1 *)(param_1 + 0x640) = 1;
              break;
            }
          }
          do {
            cVar4 = '\x01';
            bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
            if (bVar5) {
              *piVar1 = *piVar1 - (int)uVar6;
              cVar4 = ExclusiveMonitorsStatus();
            }
          } while (cVar4 != '\0');
          Aska::SLVoice::LockAndSubmitOGG()(&lStack_38,param_1);
          lVar10 = lStack_38;
        }
        else if (*(int *)(param_1 + 0x5a4) == 0xd) {
          iVar3 = 0;
          if (*(int *)(param_1 + 0x4b4) + 1 < 4) {
            iVar3 = *(int *)(param_1 + 0x4b4) + 1;
          }
          if (iVar3 == *(int *)(param_1 + 0x4b0)) goto code_r0x0233d3d4;
          cVar4 = *(char *)(param_1 + iVar3 + 0x4b8);
          *(int *)(param_1 + 0x4b4) = iVar3;
          if (cVar4 != '\0') {
            Aska::WaveBuffer::UnlockBuffer()(*(undefined8 *)(param_1 + 0x30));
            plVar7 = *(long **)(*(long *)(param_1 + 0x30) + 8);
            uVar6 = (**(code **)(*plVar7 + 0xb8))(plVar7,1,0);
            if ((uVar6 & 1) != 0) {
              fVar12 = *(float *)(*(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50 + 0x38);
              DataMemoryBarrier(2,3);
              fVar13 = _UNK_027dbad0;
              if (*(int *)(*(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50 + 0x3c) == 0) {
                fVar13 = 0.0;
              }
              do {
                cVar4 = '\x01';
                bVar5 = (bool)ExclusiveMonitorPass((int *)(param_1 + 0x63c),0x10);
                if (bVar5) {
                  *(int *)(param_1 + 0x63c) = (int)(fVar12 + fVar13);
                  cVar4 = ExclusiveMonitorsStatus();
                }
              } while (cVar4 != '\0');
              goto code_r0x0233d46c;
            }
          }
          Aska::SLVoice::LockAndSubmitADPCM()(&lStack_38,param_1);
          lVar10 = lStack_38;
        }
        if ((lVar10 != -0x3c1 && lVar10 < 0) || (iVar11 = iVar11 + 1, iVar9 <= iVar11)) break;
      } while( true );
    }
  }
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_1 + 0x5e0) = 0xffffffff;
  DataMemoryBarrier(2,3);
  if (0x14 < *(int *)(param_1 + 0x5e4)) {
    piVar1 = (int *)(param_1 + 0x5e4);
    do {
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar5) {
        *piVar1 = *piVar1 + -1;
        cVar4 = ExclusiveMonitorsStatus();
      }
    } while (cVar4 != '\0');
    uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x620);
    if ((uVar6 & 1) != 0) {
      (*(code *)PTR__ZNK4Aska9Semaphore6SignalEv_02c96cd0)(param_1 + 0x620);
      return;
    }
  }
  return;
}

// ==== Aska::SLVoice::SetDeleteCountdown()
// vaddr 0x223d478 | ghidra 0x233d478 | size 80 | symbol _ZN4Aska7SLVoice18SetDeleteCountdownEv | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska7SLVoice18SetDeleteCountdownEv(long param_1)

{
  char cVar1;
  bool bVar2;
  float fVar3;
  float fVar4;
  
  fVar3 = *(float *)(*(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50 + 0x38);
  DataMemoryBarrier(2,3);
  fVar4 = _UNK_027dbad0;
  if (*(int *)(*(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50 + 0x3c) == 0) {
    fVar4 = 0.0;
  }
  do {
    cVar1 = '\x01';
    bVar2 = (bool)ExclusiveMonitorPass((int *)(param_1 + 0x63c),0x10);
    if (bVar2) {
      *(int *)(param_1 + 0x63c) = (int)(fVar3 + fVar4);
      cVar1 = ExclusiveMonitorsStatus();
    }
  } while (cVar1 != '\0');
  *(undefined1 *)(param_1 + 0x640) = 1;
  return;
}

// ==== Aska::SLVoice::ProcAudioBuffer()
// vaddr 0x223d4c8 | ghidra 0x233d4c8 | size 588 | symbol _ZN4Aska7SLVoice15ProcAudioBufferEv | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska7SLVoice15ProcAudioBufferEv(long param_1)

{
  uint uVar1;
  int *piVar2;
  int *piVar3;
  uint uVar4;
  char cVar5;
  bool bVar6;
  uint uVar7;
  int iVar8;
  long *plVar9;
  ulong uVar10;
  float fVar11;
  float fVar12;
  undefined8 uStack_28;
  
  if (*(int *)(param_1 + 0x5a4) != 0xc) {
    piVar2 = (int *)(param_1 + 0x638);
    do {
      cVar5 = '\x01';
      bVar6 = (bool)ExclusiveMonitorPass(piVar2,0x10);
      if (bVar6) {
        *piVar2 = *piVar2 + 1;
        cVar5 = ExclusiveMonitorsStatus();
      }
    } while (cVar5 != '\0');
    return;
  }
  piVar2 = (int *)(param_1 + 0x5e0);
  iVar8 = 0;
  do {
    while (*piVar2 == -1) {
      cVar5 = '\x01';
      bVar6 = (bool)ExclusiveMonitorPass(piVar2,0x10);
      if (bVar6) {
        *piVar2 = 0;
        cVar5 = ExclusiveMonitorsStatus();
      }
      if (cVar5 == '\0') goto code_r0x0233d5cc;
    }
    ClearExclusiveLocal();
    bVar6 = iVar8 < 0x1ff;
    iVar8 = iVar8 + 1;
  } while (bVar6);
  piVar3 = (int *)(param_1 + 0x5e4);
  do {
    cVar5 = '\x01';
    bVar6 = (bool)ExclusiveMonitorPass(piVar3,0x10);
    if (bVar6) {
      *piVar3 = *piVar3 + 1;
      cVar5 = ExclusiveMonitorsStatus();
    }
  } while (cVar5 != '\0');
  do {
    if (*piVar2 != -1) {
      ClearExclusiveLocal();
      do {
        uVar10 = Aska::Semaphore::IsReady() const(param_1 + 0x620);
        if ((uVar10 & 1) == 0) {
          do {
            cVar5 = '\x01';
            bVar6 = (bool)ExclusiveMonitorPass(piVar3,0x10);
            if (bVar6) {
              *piVar3 = *piVar3 + -1;
              cVar5 = ExclusiveMonitorsStatus();
            }
          } while (cVar5 != '\0');
          Aska::Thread::Sleep(unsigned int)(1);
        }
        else {
          Aska::Semaphore::Wait() const(param_1 + 0x620);
        }
        do {
          cVar5 = '\x01';
          bVar6 = (bool)ExclusiveMonitorPass(piVar3,0x10);
          if (bVar6) {
            *piVar3 = *piVar3 + 1;
            cVar5 = ExclusiveMonitorsStatus();
          }
        } while (cVar5 != '\0');
        while (*piVar2 == -1) {
          cVar5 = '\x01';
          bVar6 = (bool)ExclusiveMonitorPass(piVar2,0x10);
          if (bVar6) {
            *piVar2 = 0;
            cVar5 = ExclusiveMonitorsStatus();
          }
          if (cVar5 == '\0') goto code_r0x0233d5bc;
        }
        ClearExclusiveLocal();
      } while( true );
    }
    cVar5 = '\x01';
    bVar6 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar6) {
      *piVar2 = 0;
      cVar5 = ExclusiveMonitorsStatus();
    }
  } while (cVar5 != '\0');
code_r0x0233d5bc:
  do {
    cVar5 = '\x01';
    bVar6 = (bool)ExclusiveMonitorPass(piVar3,0x10);
    if (bVar6) {
      *piVar3 = *piVar3 + -1;
      cVar5 = ExclusiveMonitorsStatus();
    }
  } while (cVar5 != '\0');
code_r0x0233d5cc:
  DataMemoryBarrier(2,3);
  if (*(long *)(param_1 + 0x30) != 0) {
    Aska::WaveBuffer::UnlockBuffer()();
    plVar9 = *(long **)(*(long *)(param_1 + 0x30) + 8);
    uVar10 = (**(code **)(*plVar9 + 0xb8))(plVar9,1,0);
    if ((uVar10 & 1) == 0) {
      plVar9 = *(long **)(*(long *)(param_1 + 0x30) + 8);
      uVar10 = (**(code **)(*plVar9 + 0xb8))(plVar9,0,0);
      if ((((uVar10 & 1) == 0) &&
          (uVar10 = Aska::WaveBuffer::LockBuffer(void**, unsigned long, bool)(*(undefined8 *)(param_1 + 0x30),&uStack_28,
                                    *(undefined4 *)(param_1 + 0x594),0), -1 < (long)uVar10)) &&
         (iVar8 = (**(code **)**(undefined8 **)(param_1 + 0x538))
                            (*(undefined8 **)(param_1 + 0x538),uStack_28,uVar10 & 0xffffffff),
         iVar8 == 0)) {
        uVar4 = *(uint *)(param_1 + 0x598);
        uVar1 = *(int *)(param_1 + 0x59c) + 1;
        uVar7 = 0;
        if (uVar4 != 0) {
          uVar7 = uVar1 / uVar4;
        }
        *(uint *)(param_1 + 0x59c) = uVar1 - uVar7 * uVar4;
      }
    }
    else {
      fVar11 = *(float *)(*(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50 + 0x38);
      DataMemoryBarrier(2,3);
      fVar12 = _UNK_027dbad0;
      if (*(int *)(*(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50 + 0x3c) == 0) {
        fVar12 = 0.0;
      }
      do {
        cVar5 = '\x01';
        bVar6 = (bool)ExclusiveMonitorPass((int *)(param_1 + 0x63c),0x10);
        if (bVar6) {
          *(int *)(param_1 + 0x63c) = (int)(fVar11 + fVar12);
          cVar5 = ExclusiveMonitorsStatus();
        }
      } while (cVar5 != '\0');
      *(undefined1 *)(param_1 + 0x640) = 1;
    }
  }
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_1 + 0x5e0) = 0xffffffff;
  DataMemoryBarrier(2,3);
  if (*(int *)(param_1 + 0x5e4) < 0x15) {
    return;
  }
  piVar2 = (int *)(param_1 + 0x5e4);
  do {
    cVar5 = '\x01';
    bVar6 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar6) {
      *piVar2 = *piVar2 + -1;
      cVar5 = ExclusiveMonitorsStatus();
    }
  } while (cVar5 != '\0');
  uVar10 = Aska::Semaphore::IsReady() const(param_1 + 0x620);
  if ((uVar10 & 1) == 0) {
    return;
  }
  Aska::Semaphore::Signal() const(param_1 + 0x620);
  return;
}

// ==== Aska::SLVoice::SubmitBufferDataPCM(void const*, unsigned int)
// vaddr 0x223d714 | ghidra 0x233d714 | size 88 | symbol _ZN4Aska7SLVoice19SubmitBufferDataPCMEPKvj | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska7SLVoice19SubmitBufferDataPCMEPKvj(undefined8 *param_1,long param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  undefined8 uVar5;
  
  iVar4 = (**(code **)**(undefined8 **)(param_2 + 0x538))();
  if (iVar4 == 0) {
    uVar2 = *(uint *)(param_2 + 0x598);
    uVar5 = 0;
    uVar1 = *(int *)(param_2 + 0x59c) + 1;
    uVar3 = 0;
    if (uVar2 != 0) {
      uVar3 = uVar1 / uVar2;
    }
    *(uint *)(param_2 + 0x59c) = uVar1 - uVar3 * uVar2;
  }
  else {
    uVar5 = 0xffffffffffffffff;
  }
  *param_1 = uVar5;
  return;
}

// ==== Aska::SLVoice::SubmitDummyDataAdpcm()
// vaddr 0x223d76c | ghidra 0x233d76c | size 168 | symbol _ZN4Aska7SLVoice20SubmitDummyDataAdpcmEv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska7SLVoice20SubmitDummyDataAdpcmEv(long param_1)

{
  uint uVar1;
  int *piVar2;
  uint uVar3;
  char cVar4;
  bool bVar5;
  uint uVar6;
  int iVar7;
  
  iVar7 = (**(code **)**(undefined8 **)(param_1 + 0x538))
                    (*(undefined8 **)(param_1 + 0x538),
                     *(undefined8 *)
                      (*(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50 + 0x1228),
                     *(undefined4 *)
                      (*(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50 + 0x1230));
  if (iVar7 == 0) {
    uVar3 = *(uint *)(param_1 + 0x598);
    uVar1 = *(int *)(param_1 + 0x59c) + 1;
    uVar6 = 0;
    if (uVar3 != 0) {
      uVar6 = uVar1 / uVar3;
    }
    *(uint *)(param_1 + 0x59c) = uVar1 - uVar6 * uVar3;
    uVar1 = *(uint *)(param_1 + 0x4b0);
    if (*(uint *)(param_1 + 0x4b4) != uVar1) {
      iVar7 = 0;
      if (uVar1 + 1 < 4) {
        iVar7 = uVar1 + 1;
      }
      *(undefined1 *)(param_1 + (ulong)uVar1 + 0x4b8) = 1;
      *(int *)(param_1 + 0x4b0) = iVar7;
      piVar2 = (int *)(param_1 + 0x638);
      do {
        cVar4 = '\x01';
        bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
        if (bVar5) {
          *piVar2 = *piVar2 + -1;
          cVar4 = ExclusiveMonitorsStatus();
        }
      } while (cVar4 != '\0');
      return 0;
    }
  }
  *(undefined1 *)(param_1 + 0x641) = 1;
  return 0xffffffffffffffff;
}

// ==== Aska::SLVoice::SubmitBufferDataADPCM(void const*, unsigned int, bool)
// vaddr 0x223d814 | ghidra 0x233d814 | size 428 | symbol _ZN4Aska7SLVoice21SubmitBufferDataADPCMEPKvjb | lib libSOA-3.7.0.so | 2026-10-08
ulong _ZN4Aska7SLVoice21SubmitBufferDataADPCMEPKvjb
                (long param_1,undefined8 param_2,undefined4 param_3,ulong param_4)

{
  int *piVar1;
  uint uVar2;
  uint uVar3;
  char cVar4;
  bool bVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  undefined8 uVar9;
  ulong uVar10;
  long lVar11;
  long lVar12;
  
  lVar12 = *(long *)(param_1 + (ulong)*(uint *)(param_1 + 0x590) * 8 + 0x560);
  if (lVar12 == 0) {
    uVar9 = Aska::SoundServer::AcquireAskaAdpcmDecodeBuffer()(*(undefined8 *)
                             (*(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50 + 0xe8));
    *(undefined8 *)(param_1 + 0x560 + (ulong)*(uint *)(param_1 + 0x590) * 8) = uVar9;
    if (*(long *)(param_1 + 0x560 + (ulong)*(uint *)(param_1 + 0x590) * 8) == 0) {
      *(undefined1 *)(param_1 + 0x641) = 1;
      return 0xfffffffffffffc41;
    }
    *(undefined8 *)(param_1 + (ulong)*(uint *)(param_1 + 0x590) * 8 + 0x578) = 0x6000;
    lVar12 = *(long *)(param_1 + (ulong)*(uint *)(param_1 + 0x590) * 8 + 0x560);
  }
  uVar7 = Aska::AskaADPCM::Decode(unsigned char const*, unsigned int, unsigned char*)(param_1 + 0x38,param_2,param_3,lVar12);
  if ((param_4 & 1) != 0) {
    lVar11 = *(long *)(param_1 + 0x10);
    uVar3 = *(int *)(lVar11 + 0x58) * (uint)*(byte *)(lVar11 + 0x15) *
            (uint)(*(byte *)(lVar11 + 0x17) >> 3);
    uVar7 = uVar7 - uVar3;
    lVar12 = (ulong)uVar3 + lVar12;
  }
  if (*(char *)(*(long *)(*(long *)(param_1 + 0x30) + 8) + 0x8c) != '\0') {
    lVar11 = *(long *)(param_1 + 0x10);
    uVar7 = uVar7 - *(int *)(lVar11 + 0x5c) * (uint)*(byte *)(lVar11 + 0x15) *
                    (uint)(*(byte *)(lVar11 + 0x17) >> 3);
  }
  if (uVar7 == 0) {
code_r0x0233d9ac:
    uVar10 = (ulong)uVar7;
  }
  else {
    iVar8 = (**(code **)**(undefined8 **)(param_1 + 0x538))
                      (*(undefined8 **)(param_1 + 0x538),lVar12,uVar7);
    if (iVar8 == 0) {
      uVar2 = *(uint *)(param_1 + 0x598);
      uVar3 = *(int *)(param_1 + 0x59c) + 1;
      uVar6 = 0;
      if (uVar2 != 0) {
        uVar6 = uVar3 / uVar2;
      }
      *(uint *)(param_1 + 0x59c) = uVar3 - uVar6 * uVar2;
      piVar1 = (int *)(param_1 + 0x638);
      do {
        cVar4 = '\x01';
        bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
        if (bVar5) {
          *piVar1 = *piVar1 + -1;
          cVar4 = ExclusiveMonitorsStatus();
        }
      } while (cVar4 != '\0');
      uVar3 = *(uint *)(param_1 + 0x4b0);
      if (*(uint *)(param_1 + 0x4b4) != uVar3) {
        iVar8 = 0;
        if (uVar3 + 1 < 4) {
          iVar8 = uVar3 + 1;
        }
        *(undefined1 *)(param_1 + (ulong)uVar3 + 0x4b8) = 1;
        *(int *)(param_1 + 0x4b0) = iVar8;
        *(uint *)(param_1 + 0x590) = (*(int *)(param_1 + 0x590) + 1U) % 3;
        goto code_r0x0233d9ac;
      }
    }
    *(undefined1 *)(param_1 + 0x641) = 1;
    uVar10 = 0xffffffffffffffff;
  }
  return uVar10;
}

// ==== Aska::SLVoice::SubmitDummyDataOgg()
// vaddr 0x223d9c0 | ghidra 0x233d9c0 | size 168 | symbol _ZN4Aska7SLVoice18SubmitDummyDataOggEv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska7SLVoice18SubmitDummyDataOggEv(long param_1)

{
  uint uVar1;
  int *piVar2;
  uint uVar3;
  char cVar4;
  bool bVar5;
  uint uVar6;
  int iVar7;
  
  iVar7 = (**(code **)**(undefined8 **)(param_1 + 0x538))
                    (*(undefined8 **)(param_1 + 0x538),
                     *(undefined8 *)
                      (*(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50 + 0x1228),
                     *(undefined4 *)
                      (*(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50 + 0x1230));
  if (iVar7 == 0) {
    uVar3 = *(uint *)(param_1 + 0x598);
    uVar1 = *(int *)(param_1 + 0x59c) + 1;
    uVar6 = 0;
    if (uVar3 != 0) {
      uVar6 = uVar1 / uVar3;
    }
    *(uint *)(param_1 + 0x59c) = uVar1 - uVar6 * uVar3;
    piVar2 = (int *)(param_1 + 0x638);
    do {
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
      if (bVar5) {
        *piVar2 = *piVar2 + -1;
        cVar4 = ExclusiveMonitorsStatus();
      }
    } while (cVar4 != '\0');
    uVar1 = *(uint *)(param_1 + 0x4c8);
    if (*(uint *)(param_1 + 0x4cc) != uVar1) {
      iVar7 = 0;
      if (uVar1 + 1 < 9) {
        iVar7 = uVar1 + 1;
      }
      *(undefined8 *)(param_1 + (ulong)uVar1 * 8 + 0x4d0) = 0x100000000;
      *(int *)(param_1 + 0x4c8) = iVar7;
      return 0;
    }
  }
  *(undefined1 *)(param_1 + 0x641) = 1;
  return 0xffffffffffffffff;
}

// ==== Aska::SLVoice::SubmitBufferDataOGG(void const*, unsigned int, unsigned int, unsigned int)
// vaddr 0x223da68 | ghidra 0x233da68 | size 288 | symbol _ZN4Aska7SLVoice19SubmitBufferDataOGGEPKvjjj | lib libSOA-3.7.0.so | 2026-10-08
ulong _ZN4Aska7SLVoice19SubmitBufferDataOGGEPKvjjj
                (long param_1,undefined8 param_2,undefined8 param_3,undefined4 param_4,
                undefined4 param_5)

{
  int *piVar1;
  int *piVar2;
  uint uVar3;
  char cVar4;
  bool bVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  ulong uVar9;
  undefined8 uStack_18;
  
  uStack_18 = 0;
  uVar3 = (uint)*(byte *)(*(long *)(param_1 + 0x10) + 0x17) *
          (uint)*(byte *)(*(long *)(param_1 + 0x10) + 0x15) >> 3;
  uVar6 = 0;
  if (uVar3 != 0) {
    uVar6 = *(uint *)(param_1 + 0x518) / uVar3;
  }
  uVar9 = Aska::AskaOGG::Decode(signed char const*, unsigned int, signed char**, unsigned int, unsigned int, unsigned int)(param_1 + 0x58,param_2,param_3,&uStack_18,uVar6,param_4,param_5);
  if ((long)uVar9 < 0) {
    *(undefined1 *)(param_1 + 0x641) = 1;
  }
  else if ((int)uVar9 == 0) {
    uVar9 = uVar9 & 0xffffffff;
  }
  else {
    iVar8 = (**(code **)**(undefined8 **)(param_1 + 0x538))
                      (*(undefined8 **)(param_1 + 0x538),uStack_18,uVar9 & 0xffffffff);
    if (iVar8 == 0) {
      uVar6 = *(uint *)(param_1 + 0x598);
      piVar1 = (int *)(param_1 + 0x518);
      uVar3 = *(int *)(param_1 + 0x59c) + 1;
      uVar7 = 0;
      if (uVar6 != 0) {
        uVar7 = uVar3 / uVar6;
      }
      *(uint *)(param_1 + 0x59c) = uVar3 - uVar7 * uVar6;
      piVar2 = (int *)(param_1 + 0x638);
      do {
        cVar4 = '\x01';
        bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
        if (bVar5) {
          *piVar2 = *piVar2 + -1;
          cVar4 = ExclusiveMonitorsStatus();
        }
      } while (cVar4 != '\0');
      do {
        cVar4 = '\x01';
        bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
        if (bVar5) {
          *piVar1 = *piVar1 + (int)uVar9;
          cVar4 = ExclusiveMonitorsStatus();
        }
      } while (cVar4 != '\0');
      uVar3 = *(uint *)(param_1 + 0x4c8);
      if (*(uint *)(param_1 + 0x4cc) != uVar3) {
        iVar8 = 0;
        if (uVar3 + 1 < 9) {
          iVar8 = uVar3 + 1;
        }
        *(ulong *)(param_1 + (ulong)uVar3 * 8 + 0x4d0) =
             uVar9 & 0xffffffff | (ulong)(*(byte *)(param_1 + 0x420) ^ 1) << 0x20;
        *(int *)(param_1 + 0x4c8) = iVar8;
        return uVar9 & 0xffffffff;
      }
    }
    *(undefined1 *)(param_1 + 0x641) = 1;
    uVar9 = 0xffffffffffffffff;
  }
  return uVar9;
}

// ==== Aska::WaveBuffer::~WaveBuffer()
// vaddr 0x223db88 | ghidra 0x233db88 | size 24 | symbol _ZN4Aska10WaveBufferD2Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska10WaveBufferD2Ev(long *param_1)

{
  code *UNRECOVERED_JUMPTABLE;
  
  UNRECOVERED_JUMPTABLE = *(code **)(PTR__ZTVN4Aska10WaveBufferE_02cb8488 + 0x28);
  *param_1 = (long)(PTR__ZTVN4Aska10WaveBufferE_02cb8488 + 0x10);
                    /* WARNING: Could not recover jumptable at 0x0233db9c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*UNRECOVERED_JUMPTABLE)();
  return;
}

// ==== Aska::TQueue<Aska::SLVoice::AdpcmSubmitContext, 3>::~TQueue()
// vaddr 0x223dbd4 | ghidra 0x233dbd4 | size 4 | symbol _ZN4Aska6TQueueINS_7SLVoice18AdpcmSubmitContextELi3EED0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska6TQueueINS_7SLVoice18AdpcmSubmitContextELi3EED0Ev(void)

{
  (*(code *)PTR__ZdlPv_02ca4758)();
  return;
}

// ==== Aska::TQueue<Aska::SLVoice::OggSubmitContext, 8>::~TQueue()
// vaddr 0x223dbd8 | ghidra 0x233dbd8 | size 4 | symbol _ZN4Aska6TQueueINS_7SLVoice16OggSubmitContextELi8EED0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska6TQueueINS_7SLVoice16OggSubmitContextELi8EED0Ev(void)

{
  (*(code *)PTR__ZdlPv_02ca4758)();
  return;
}

// ==== Aska::WavePlayer::WavePlayer()
// vaddr 0x22447e4 | ghidra 0x23447e4 | size 136 | symbol _ZN4Aska10WavePlayerC1Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska10WavePlayerC2Ev(long *param_1)

{
  undefined *puVar1;
  
  Aska::IAudioDevice::IAudioDevice()();
  puVar1 = PTR__ZTVN4Aska11AudioPlayerE_02cc3ba0;
  *(undefined8 *)((long)param_1 + 0x1c) = 0;
  *(undefined8 *)((long)param_1 + 0x22) = 0;
  *(undefined8 *)((long)param_1 + 0x32) = 0;
  *(undefined8 *)((long)param_1 + 0x2c) = 0;
  *(undefined8 *)((long)param_1 + 0x42) = 0;
  *(undefined8 *)((long)param_1 + 0x3c) = 0;
  param_1[0xd] = 0;
  *(undefined4 *)(param_1 + 0xc) = 0;
  *param_1 = (long)(puVar1 + 0x10);
  param_1[10] = (long)(PTR__ZTVN4Aska18TSoundDynamicQueueINS_12AudioMessageEEE_02cbd5a0 + 0x10);
  param_1[0xb] = 1;
  Aska::FastCriticalSection::FastCriticalSection()(param_1 + 0xe);
  puVar1 = PTR__ZTVN4Aska10WavePlayerE_02cc2540 + 0x10;
  *(undefined4 *)(param_1 + 0x20) = 0;
  *param_1 = (long)puVar1;
  param_1[0x24] = 0;
  param_1[0x23] = 0;
  param_1[0x22] = 0;
  param_1[0x21] = 0;
  return;
}

// ==== Aska::WavePlayer::~WavePlayer()
// vaddr 0x224486c | ghidra 0x234486c | size 240 | symbol _ZN4Aska10WavePlayerD2Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska10WavePlayerD1Ev(long *param_1)

{
  undefined *puVar1;
  long lVar2;
  
  *param_1 = (long)(PTR__ZTVN4Aska10WavePlayerE_02cc2540 + 0x10);
  puVar1 = PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50;
  if (param_1[0x24] != 0) {
    lVar2 = Aska::SoundManager::QueryAudioInterface(Aska::AudioConnector*) const(*(undefined8 *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50,
                            param_1 + 0x20);
    (**(code **)(*param_1 + 0x60))(param_1);
    if (lVar2 != 0) {
      Aska::SoundManager::DeleteAudioInterface(Aska::AudioInterface*)(*(undefined8 *)puVar1,lVar2);
    }
    if ((long *)param_1[0x23] != (long *)0x0) {
      (**(code **)(*(long *)param_1[0x23] + 0x18))();
      Aska::SoundServer::ReleaseWaveVoice(Aska::WaveVoiceBase*)(*(undefined8 *)(*(long *)puVar1 + 0xe8),param_1[0x23]);
      param_1[0x23] = 0;
    }
    if (*(long **)(param_1[0x24] + 8) != (long *)0x0) {
      (**(code **)(**(long **)(param_1[0x24] + 8) + 8))();
    }
    param_1[0x24] = 0;
  }
  *param_1 = (long)(PTR__ZTVN4Aska11AudioPlayerE_02cc3ba0 + 0x10);
  Aska::FastCriticalSection::~FastCriticalSection()(param_1 + 0xe);
  puVar1 = PTR__ZTVN4Aska13TDynamicQueueINS_12AudioMessageELb1EEE_02cc2768;
  *(undefined4 *)(param_1 + 0xc) = 0;
  param_1[10] = (long)(puVar1 + 0x10);
  param_1[0xb] = 1;
  if (param_1[0xd] != 0) {
    operator delete[](void*)();
    param_1[0xd] = 0;
  }
  (*(code *)PTR__ZN4Aska12IAudioDeviceD1Ev_02ca0420)(param_1);
  return;
}

// ==== Aska::WavePlayer::SetAaoHandler(Aska::AaoHandler*, Aska::DirectPlaybackSettings const*, Aska::MultiMediaStream const*, unsigned int)
// vaddr 0x224495c | ghidra 0x234495c | size 312 | symbol _ZN4Aska10WavePlayer13SetAaoHandlerEPNS_10AaoHandlerEPKNS_22DirectPlaybackSettingsEPKNS_16MultiMediaStreamEj | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska10WavePlayer13SetAaoHandlerEPNS_10AaoHandlerEPKNS_22DirectPlaybackSettingsEPKNS_16MultiMediaStreamEj
          (long *param_1,long param_2,undefined8 param_3,long *param_4,undefined4 param_5)

{
  long lVar1;
  ulong uVar2;
  undefined8 uVar3;
  
  if (param_1[0x24] == param_2) {
    if (param_4 == (long *)0x0) {
      uVar3 = 0;
    }
    else {
      (**(code **)(*param_4 + 8))(param_4);
      uVar3 = 0;
    }
  }
  else {
    if (param_1[0x24] != 0) {
      lVar1 = (**(code **)(*param_1 + 0x48))(param_1,0x2ff0000);
      (**(code **)(*param_1 + 0x60))(param_1);
      if (lVar1 != 0) {
        Aska::SoundManager::DeleteAudioInterface(Aska::AudioInterface*)(*(undefined8 *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50,lVar1);
      }
      if ((long *)param_1[0x23] != (long *)0x0) {
        (**(code **)(*(long *)param_1[0x23] + 0x18))();
        Aska::SoundServer::ReleaseWaveVoice(Aska::WaveVoiceBase*)(*(undefined8 *)
                         (*(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50 + 0xe8),
                        param_1[0x23]);
        param_1[0x23] = 0;
      }
      if (*(long **)(param_1[0x24] + 8) != (long *)0x0) {
        (**(code **)(**(long **)(param_1[0x24] + 8) + 8))();
      }
    }
    param_1[0x24] = param_2;
    if (param_2 == 0) {
      if (param_4 != (long *)0x0) {
        (**(code **)(*param_4 + 8))(param_4);
      }
    }
    else {
      uVar2 = Aska::WavePlayer::InitPlayer(Aska::DirectPlaybackSettings const*, Aska::MultiMediaStream const*, unsigned int)(param_1,param_3,param_4,param_5);
      if ((uVar2 & 1) == 0) {
        param_1[0x24] = 0;
        return 0;
      }
    }
    uVar3 = 1;
  }
  return uVar3;
}

// ==== Aska::WavePlayer::~WavePlayer()
// vaddr 0x2244a94 | ghidra 0x2344a94 | size 24 | symbol _ZN4Aska10WavePlayerD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska10WavePlayerD0Ev(undefined8 param_1)

{
  Aska::WavePlayer::~WavePlayer()();
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::WavePlayer::SetupDevice()
// vaddr 0x2244aac | ghidra 0x2344aac | size 140 | symbol _ZN4Aska10WavePlayer11SetupDeviceEv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska10WavePlayer11SetupDeviceEv(long *param_1)

{
  long lVar1;
  
  if ((int)param_1[3] != 0) {
code_r0x02344abc:
    (**(code **)(*param_1 + 0x60))(param_1);
    return 0;
  }
  if ((int)param_1[0xc] != 7) {
    if (param_1[0xd] != 0) {
      operator delete[](void*)();
      param_1[0xd] = 0;
    }
    lVar1 = Aska::SoundMemory::Malloc(unsigned long)(0xa8);
    param_1[0xd] = lVar1;
    if (lVar1 == 0) {
      *(undefined4 *)(param_1 + 0xc) = 0;
      goto code_r0x02344abc;
    }
    *(undefined4 *)(param_1 + 0xc) = 7;
    param_1[0xb] = 1;
  }
  param_1[0x21] = (long)param_1;
  *(undefined4 *)(param_1 + 3) = 1;
  *(undefined4 *)(param_1 + 0x20) = 0x2ff0000;
  return 1;
}

// ==== Aska::WavePlayer::FinishDevice()
// vaddr 0x2244b38 | ghidra 0x2344b38 | size 84 | symbol _ZN4Aska10WavePlayer12FinishDeviceEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska10WavePlayer12FinishDeviceEv(long param_1)

{
  if ((*(int *)(param_1 + 0x18) != 0) &&
     ((*(long *)(param_1 + 0x110) == 0 ||
      (Aska::IAudioDevice::UnplugInterfaces(Aska::AudioInterface*, bool)(param_1,*(long *)(param_1 + 0x110),1), *(int *)(param_1 + 0x18) != 0)))) {
    *(undefined8 *)(param_1 + 0x58) = 1;
    *(undefined4 *)(param_1 + 0x60) = 0;
    if (*(long *)(param_1 + 0x68) != 0) {
      operator delete[](void*)();
      *(undefined8 *)(param_1 + 0x68) = 0;
    }
    *(undefined4 *)(param_1 + 0x18) = 0;
  }
  return;
}

// ==== Aska::WavePlayer::TermPlayer()
// vaddr 0x2244b8c | ghidra 0x2344b8c | size 132 | symbol _ZN4Aska10WavePlayer10TermPlayerEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska10WavePlayer10TermPlayerEv(long *param_1)

{
  long lVar1;
  
  lVar1 = (**(code **)(*param_1 + 0x48))(param_1,0x2ff0000);
  (**(code **)(*param_1 + 0x60))(param_1);
  if (lVar1 != 0) {
    Aska::SoundManager::DeleteAudioInterface(Aska::AudioInterface*)(*(undefined8 *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50,lVar1);
  }
  if ((long *)param_1[0x23] != (long *)0x0) {
    (**(code **)(*(long *)param_1[0x23] + 0x18))();
    Aska::SoundServer::ReleaseWaveVoice(Aska::WaveVoiceBase*)(*(undefined8 *)(*(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50 + 0xe8),
                    param_1[0x23]);
    param_1[0x23] = 0;
  }
  return;
}

// ==== Aska::WavePlayer::InitPlayer(Aska::DirectPlaybackSettings const*, Aska::MultiMediaStream const*, unsigned int)
// vaddr 0x2244c10 | ghidra 0x2344c10 | size 768 | symbol _ZN4Aska10WavePlayer10InitPlayerEPKNS_22DirectPlaybackSettingsEPKNS_16MultiMediaStreamEj | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8
_ZN4Aska10WavePlayer10InitPlayerEPKNS_22DirectPlaybackSettingsEPKNS_16MultiMediaStreamEj
          (long *param_1,long param_2,long *param_3,undefined4 param_4)

{
  uint uVar1;
  float fVar2;
  undefined *puVar3;
  ulong uVar4;
  long lVar5;
  long *plVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  undefined4 uStack_78;
  float fStack_74;
  undefined4 uStack_70;
  float fStack_6c;
  byte bStack_68;
  undefined4 uStack_64;
  
  uVar4 = (**(code **)(*param_1 + 0x58))();
  puVar3 = PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50;
  if ((uVar4 & 1) == 0) {
    if (param_3 != (long *)0x0) {
      (**(code **)(*param_3 + 8))(param_3);
    }
    return 0;
  }
  plVar6 = *(long **)(*(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50 + 0x6c8);
  lVar5 = Aska::SoundServer::AcquireAudioInterface()(*(undefined8 *)
                           (*(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50 + 0xe8));
  if (lVar5 != 0) {
    Aska::SoundManager::AddAudioInterface(Aska::AudioInterface*)(*(undefined8 *)puVar3,lVar5);
    uVar4 = (**(code **)(*param_1 + 0x40))(param_1,0x2ff0000,lVar5);
    if ((uVar4 & 1) == 0) {
      Aska::SoundManager::DeleteAudioInterface(Aska::AudioInterface*)(*(undefined8 *)puVar3,lVar5);
    }
    else {
      uVar4 = (**(code **)(*plVar6 + 0x40))
                        (plVar6,(*(uint *)(param_2 + 0x20) & 0xff) << 0x10 | 0x100ffff,lVar5);
      if ((uVar4 & 1) != 0) {
        fVar9 = *(float *)(param_2 + 0x10);
        if (*(float *)(param_2 + 0x10) <= 0.0) {
          fVar9 = 0.0;
        }
        fVar8 = _UNK_02965bf8;
        if (_UNK_027fac84 <= ABS(fVar9)) {
          fVar9 = (float)log10f();
          fVar8 = fVar9 * 20.0;
        }
        fVar9 = 0.0;
        if ((param_1[0x24] != 0) &&
           (lVar5 = *(long *)(param_1[0x24] + 0x80), fVar9 = 0.0, lVar5 != 0)) {
          uVar1 = *(int *)PTR__ZN4Aska26g_uiLowPrecisionRandomSeedE_02cbb068 * 0x19660d + 0x3c6ef35f
          ;
          *(uint *)PTR__ZN4Aska26g_uiLowPrecisionRandomSeedE_02cbb068 = uVar1;
          fVar9 = *(float *)(lVar5 + 0x14) +
                  (*(float *)(lVar5 + 0x18) - *(float *)(lVar5 + 0x14)) *
                  ((float)(uVar1 & 0x7fffff | 0x3f800000) + -1.0);
        }
        fVar2 = _UNK_02965bf8;
        if (fVar8 <= _UNK_02965bf8) {
          fVar8 = _UNK_02965bf8;
        }
        if (fVar9 <= _UNK_02965bf8) {
          fVar9 = _UNK_02965bf8;
        }
        fStack_74 = (float)Aska::SoundUtility::VolumeDBBlend(float, float)(fVar8,fVar9);
        fVar8 = *(float *)(param_2 + 0x14);
        fVar9 = 0.0;
        if ((param_1[0x24] != 0) && (lVar5 = *(long *)(param_1[0x24] + 0x80), lVar5 != 0)) {
          uVar1 = *(int *)PTR__ZN4Aska26g_uiLowPrecisionRandomSeedE_02cbb068 * 0x19660d + 0x3c6ef35f
          ;
          *(uint *)PTR__ZN4Aska26g_uiLowPrecisionRandomSeedE_02cbb068 = uVar1;
          fVar9 = *(float *)(lVar5 + 0x1c) +
                  (*(float *)(lVar5 + 0x20) - *(float *)(lVar5 + 0x1c)) *
                  ((float)(uVar1 & 0x7fffff | 0x3f800000) + -1.0);
        }
        fVar7 = -12.0;
        if ((-12.0 <= fVar8) && (fVar7 = fVar8, 2.0 < fVar8)) {
          fVar7 = 2.0;
        }
        uStack_70 = Aska::SoundUtility::PitchBlend(float, float)(fVar7,fVar9);
        fVar9 = *(float *)(param_2 + 0x18);
        fStack_6c = -1.0;
        if ((-1.0 <= fVar9) && (fStack_6c = fVar9, 1.0 < fVar9)) {
          fStack_6c = 1.0;
        }
        uStack_78 = *(undefined4 *)(param_2 + 0xc);
        if (*(int *)(param_2 + 8) != 0) {
          fStack_74 = fVar2;
        }
        bStack_68 = *(byte *)(param_1[0x24] + 0xa8) >> 2 & 1;
        uStack_64 = param_4;
        lVar5 = Aska::WavePlayer::CreateVoice(void const*, Aska::MultiMediaStream*, Aska::PackedPlayParams const*)(param_1,*(undefined8 *)(param_1[0x24] + 0x78),param_3,&uStack_78);
        if (lVar5 != 0) {
          return 1;
        }
        goto code_r0x02344d20;
      }
    }
  }
  if (param_3 != (long *)0x0) {
    (**(code **)(*param_3 + 8))(param_3);
  }
code_r0x02344d20:
  lVar5 = (**(code **)(*param_1 + 0x48))(param_1,0x2ff0000);
  (**(code **)(*param_1 + 0x60))(param_1);
  if (lVar5 != 0) {
    Aska::SoundManager::DeleteAudioInterface(Aska::AudioInterface*)(*(undefined8 *)puVar3,lVar5);
  }
  if ((long *)param_1[0x23] != (long *)0x0) {
    (**(code **)(*(long *)param_1[0x23] + 0x18))();
    Aska::SoundServer::ReleaseWaveVoice(Aska::WaveVoiceBase*)(*(undefined8 *)(*(long *)puVar3 + 0xe8),param_1[0x23]);
    param_1[0x23] = 0;
  }
  return 0;
}

// ==== Aska::WavePlayer::CalcMasterVolumeDB(float)
// vaddr 0x2244f10 | ghidra 0x2344f10 | size 112 | symbol _ZN4Aska10WavePlayer18CalcMasterVolumeDBEf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska10WavePlayer18CalcMasterVolumeDBEf(float param_1,long param_2)

{
  uint uVar1;
  long lVar2;
  float fVar3;
  
  fVar3 = 0.0;
  if ((*(long *)(param_2 + 0x120) != 0) &&
     (lVar2 = *(long *)(*(long *)(param_2 + 0x120) + 0x80), lVar2 != 0)) {
    uVar1 = *(int *)PTR__ZN4Aska26g_uiLowPrecisionRandomSeedE_02cbb068 * 0x19660d + 0x3c6ef35f;
    *(uint *)PTR__ZN4Aska26g_uiLowPrecisionRandomSeedE_02cbb068 = uVar1;
    fVar3 = *(float *)(lVar2 + 0x14) +
            (*(float *)(lVar2 + 0x18) - *(float *)(lVar2 + 0x14)) *
            ((float)(uVar1 & 0x7fffff | 0x3f800000) + -1.0);
  }
  if (param_1 <= _UNK_02965bf8) {
    param_1 = _UNK_02965bf8;
  }
  if (fVar3 <= _UNK_02965bf8) {
    fVar3 = _UNK_02965bf8;
  }
  (*(code *)PTR__ZN4Aska12SoundUtility13VolumeDBBlendEff_02ca4c80)(param_1,fVar3);
  return;
}

// ==== Aska::WavePlayer::CalcMasterPitchbend(float)
// vaddr 0x2244f80 | ghidra 0x2344f80 | size 132 | symbol _ZN4Aska10WavePlayer19CalcMasterPitchbendEf | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska10WavePlayer19CalcMasterPitchbendEf(undefined8 param_1,long param_2)

{
  uint uVar1;
  long lVar2;
  float fVar3;
  undefined8 uVar4;
  
  fVar3 = 0.0;
  if ((*(long *)(param_2 + 0x120) != 0) &&
     (lVar2 = *(long *)(*(long *)(param_2 + 0x120) + 0x80), lVar2 != 0)) {
    uVar1 = *(int *)PTR__ZN4Aska26g_uiLowPrecisionRandomSeedE_02cbb068 * 0x19660d + 0x3c6ef35f;
    *(uint *)PTR__ZN4Aska26g_uiLowPrecisionRandomSeedE_02cbb068 = uVar1;
    fVar3 = *(float *)(lVar2 + 0x1c) +
            (*(float *)(lVar2 + 0x20) - *(float *)(lVar2 + 0x1c)) *
            ((float)(uVar1 & 0x7fffff | 0x3f800000) + -1.0);
  }
  uVar4 = 0xc1400000;
  if ((-12.0 <= (float)param_1) && (uVar4 = param_1, 2.0 < (float)param_1)) {
    uVar4 = 0x40000000;
  }
  (*(code *)PTR__ZN4Aska12SoundUtility10PitchBlendEff_02ca82d8)(uVar4,fVar3);
  return;
}

// ==== Aska::WavePlayer::CalcMasterPanpot(float)
// vaddr 0x2245004 | ghidra 0x2345004 | size 40 | symbol _ZN4Aska10WavePlayer16CalcMasterPanpotEf | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska10WavePlayer16CalcMasterPanpotEf(undefined8 param_1)

{
  undefined8 uVar1;
  
  uVar1 = 0xbf800000;
  if ((-1.0 <= (float)param_1) && (uVar1 = param_1, 1.0 < (float)param_1)) {
    uVar1 = 0x3f800000;
  }
  return uVar1;
}

// ==== Aska::WavePlayer::CreateVoice(void const*, Aska::MultiMediaStream*, Aska::PackedPlayParams const*)
// vaddr 0x224502c | ghidra 0x234502c | size 264 | symbol _ZN4Aska10WavePlayer11CreateVoiceEPKvPNS_16MultiMediaStreamEPKNS_16PackedPlayParamsE | lib libSOA-3.7.0.so | 2026-10-08
long _ZN4Aska10WavePlayer11CreateVoiceEPKvPNS_16MultiMediaStreamEPKNS_16PackedPlayParamsE
               (long param_1,long param_2,long *param_3,undefined8 param_4)

{
  undefined *puVar1;
  long lVar2;
  ulong uVar3;
  
  if (*(long **)(param_1 + 0x118) != (long *)0x0) {
    (**(code **)(**(long **)(param_1 + 0x118) + 0x18))();
    Aska::SoundServer::ReleaseWaveVoice(Aska::WaveVoiceBase*)(*(undefined8 *)(*(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50 + 0xe8),
                    *(undefined8 *)(param_1 + 0x118));
    *(undefined8 *)(param_1 + 0x118) = 0;
  }
  puVar1 = PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50;
  lVar2 = Aska::SoundServer::AcquireWaveVoice()(*(undefined8 *)
                           (*(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50 + 0xe8));
  *(long *)(param_1 + 0x118) = lVar2;
  if (lVar2 != 0) {
    if (2 < *(byte *)(param_2 + 0x14) - 0xc) {
      return lVar2;
    }
    lVar2 = Aska::IAudioDevice::GetRouteBus(unsigned int)(param_1,*(undefined4 *)(param_1 + 0x100));
    if (lVar2 != 0) {
      uVar3 = (**(code **)(**(long **)(param_1 + 0x118) + 0x10))
                        (*(long **)(param_1 + 0x118),lVar2,param_2,param_3,param_4);
      if ((uVar3 & 1) != 0) {
        return *(long *)(param_1 + 0x118);
      }
      goto code_r0x023450f8;
    }
  }
  if (param_3 != (long *)0x0) {
    (**(code **)(*param_3 + 8))(param_3);
  }
code_r0x023450f8:
  if (*(long **)(param_1 + 0x118) != (long *)0x0) {
    (**(code **)(**(long **)(param_1 + 0x118) + 0x18))();
    Aska::SoundServer::ReleaseWaveVoice(Aska::WaveVoiceBase*)(*(undefined8 *)(*(long *)puVar1 + 0xe8),*(undefined8 *)(param_1 + 0x118));
    *(undefined8 *)(param_1 + 0x118) = 0;
  }
  return 0;
}

// ==== Aska::WavePlayer::DeleteVoice()
// vaddr 0x2245134 | ghidra 0x2345134 | size 64 | symbol _ZN4Aska10WavePlayer11DeleteVoiceEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska10WavePlayer11DeleteVoiceEv(long param_1)

{
  if (*(long **)(param_1 + 0x118) != (long *)0x0) {
    (**(code **)(**(long **)(param_1 + 0x118) + 0x18))();
    Aska::SoundServer::ReleaseWaveVoice(Aska::WaveVoiceBase*)(*(undefined8 *)(*(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50 + 0xe8),
                    *(undefined8 *)(param_1 + 0x118));
    *(undefined8 *)(param_1 + 0x118) = 0;
  }
  return;
}

// ==== Aska::WavePlayer::AudioRun()
// vaddr 0x2245174 | ghidra 0x2345174 | size 44 | symbol _ZN4Aska10WavePlayer8AudioRunEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska10WavePlayer8AudioRunEv(long param_1)

{
  Aska::AudioPlayer::AudioRun()();
  if (*(long **)(param_1 + 0x118) != (long *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x02345194. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(**(long **)(param_1 + 0x118) + 0x48))();
    return;
  }
  return;
}

// ==== Aska::WavePlayer::Play()
// vaddr 0x22451a0 | ghidra 0x23451a0 | size 44 | symbol _ZN4Aska10WavePlayer4PlayEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska10WavePlayer4PlayEv(long param_1)

{
  if (*(long **)(param_1 + 0x118) != (long *)0x0) {
    (**(code **)(**(long **)(param_1 + 0x118) + 0x20))();
    *(undefined4 *)(param_1 + 0x18) = 2;
  }
  return;
}

// ==== Aska::WavePlayer::Stop()
// vaddr 0x22451cc | ghidra 0x23451cc | size 92 | symbol _ZN4Aska10WavePlayer4StopEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska10WavePlayer4StopEv(long param_1)

{
  if (*(long **)(param_1 + 0x118) != (long *)0x0) {
    (**(code **)(**(long **)(param_1 + 0x118) + 0x28))();
    if (*(long **)(param_1 + 0x118) != (long *)0x0) {
      (**(code **)(**(long **)(param_1 + 0x118) + 0x18))();
      Aska::SoundServer::ReleaseWaveVoice(Aska::WaveVoiceBase*)(*(undefined8 *)
                       (*(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50 + 0xe8),
                      *(undefined8 *)(param_1 + 0x118));
      *(undefined8 *)(param_1 + 0x118) = 0;
    }
    *(undefined4 *)(param_1 + 0x18) = 5;
  }
  return;
}

// ==== Aska::WavePlayer::Pause()
// vaddr 0x2245228 | ghidra 0x2345228 | size 44 | symbol _ZN4Aska10WavePlayer5PauseEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska10WavePlayer5PauseEv(long param_1)

{
  if (*(long **)(param_1 + 0x118) != (long *)0x0) {
    (**(code **)(**(long **)(param_1 + 0x118) + 0x30))();
    *(undefined4 *)(param_1 + 0x18) = 3;
  }
  return;
}

// ==== Aska::WavePlayer::Resume()
// vaddr 0x2245254 | ghidra 0x2345254 | size 44 | symbol _ZN4Aska10WavePlayer6ResumeEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska10WavePlayer6ResumeEv(long param_1)

{
  if (*(long **)(param_1 + 0x118) != (long *)0x0) {
    (**(code **)(**(long **)(param_1 + 0x118) + 0x38))();
    *(undefined4 *)(param_1 + 0x18) = 2;
  }
  return;
}

// ==== Aska::WavePlayer::GetCurrentDeviceParam(unsigned int) const
// vaddr 0x2245280 | ghidra 0x2345280 | size 108 | symbol _ZNK4Aska10WavePlayer21GetCurrentDeviceParamEj | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined1  [16] _ZNK4Aska10WavePlayer21GetCurrentDeviceParamEj(long param_1,int param_2)

{
  undefined4 extraout_s0;
  uint uVar1;
  undefined4 extraout_var;
  undefined8 extraout_var_00;
  float fVar3;
  undefined1 auVar2 [16];
  
  uVar1 = 0;
  if (param_2 == 2) {
    if (*(long *)(param_1 + 0x118) != 0) {
      uVar1 = *(uint *)(*(long *)(param_1 + 0x118) + 0x20);
    }
  }
  else if (param_2 == 1) {
    if (*(long *)(param_1 + 0x118) != 0) {
      return ZEXT416(*(uint *)(*(long *)(param_1 + 0x118) + 0x1c));
    }
  }
  else if (((param_2 == 0) && (*(long *)(param_1 + 0x118) != 0)) &&
          (fVar3 = *(float *)(*(long *)(param_1 + 0x118) + 0x18), _UNK_02965bf8 < fVar3)) {
    (*(code *)PTR_powf_02c96d40)(0x41200000,fVar3 * _UNK_027edb4c);
    auVar2._4_4_ = extraout_var;
    auVar2._0_4_ = extraout_s0;
    auVar2._8_8_ = extraout_var_00;
    return auVar2;
  }
  return ZEXT416(uVar1);
}

// ==== Aska::WavePlayer::SetCurrentDeviceParam(unsigned int, float)
// vaddr 0x22452ec | ghidra 0x23452ec | size 156 | symbol _ZN4Aska10WavePlayer21SetCurrentDeviceParamEjf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska10WavePlayer21SetCurrentDeviceParamEjf(float param_1,long param_2,int param_3)

{
  long lVar1;
  float fVar2;
  
  if (param_3 == 2) {
    lVar1 = *(long *)(param_2 + 0x118);
    if (lVar1 != 0) {
      *(undefined1 *)(lVar1 + 0x28) = 1;
      *(float *)(lVar1 + 0x20) = param_1;
    }
  }
  else if (param_3 == 1) {
    lVar1 = *(long *)(param_2 + 0x118);
    if (lVar1 != 0) {
      *(undefined1 *)(lVar1 + 0x29) = 1;
      *(float *)(lVar1 + 0x1c) = param_1;
      return;
    }
  }
  else if ((param_3 == 0) && (lVar1 = *(long *)(param_2 + 0x118), lVar1 != 0)) {
    fVar2 = _UNK_02965bf8;
    if (_UNK_027fac84 <= ABS(param_1)) {
      fVar2 = (float)log10f();
      fVar2 = fVar2 * 20.0;
    }
    *(undefined1 *)(lVar1 + 0x28) = 1;
    *(float *)(lVar1 + 0x18) = fVar2;
    return;
  }
  return;
}

// ==== Aska::WavePlayer::ProcMessage()
// vaddr 0x2245388 | ghidra 0x2345388 | size 980 | symbol _ZN4Aska10WavePlayer11ProcMessageEv | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska10WavePlayer11ProcMessageEv(long *param_1)

{
  uint uVar1;
  float fVar2;
  float fVar3;
  undefined *puVar4;
  uint uVar5;
  ulong uVar6;
  code *pcVar7;
  long lVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  undefined4 auStack_b8 [2];
  float fStack_b0;
  uint uStack_a8;
  
  uVar6 = Aska::AudioPlayer::GetMessage(Aska::AudioMessage*)(param_1,auStack_b8);
  puVar4 = PTR__ZN4Aska26g_uiLowPrecisionRandomSeedE_02cbb068;
  fVar3 = _UNK_029d94a4;
  fVar2 = _UNK_02965bf8;
  if ((uVar6 & 1) != 0) {
    do {
      uVar5 = uStack_a8;
      fVar10 = fStack_b0;
      switch(auStack_b8[0]) {
      case 0:
        if ((long *)param_1[0x23] != (long *)0x0) {
          pcVar7 = *(code **)(*(long *)param_1[0x23] + 0x20);
code_r0x023454c0:
          (*pcVar7)();
          *(undefined4 *)(param_1 + 3) = 2;
        }
        break;
      case 1:
        if ((long *)param_1[0x23] != (long *)0x0) {
          (**(code **)(*(long *)param_1[0x23] + 0x28))();
          if ((long *)param_1[0x23] != (long *)0x0) {
            (**(code **)(*(long *)param_1[0x23] + 0x18))();
            Aska::SoundServer::ReleaseWaveVoice(Aska::WaveVoiceBase*)(*(undefined8 *)
                             (*(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50 + 0xe8),
                            param_1[0x23]);
            param_1[0x23] = 0;
          }
          *(undefined4 *)(param_1 + 3) = 5;
        }
        break;
      case 2:
        if ((long *)param_1[0x23] != (long *)0x0) {
          (**(code **)(*(long *)param_1[0x23] + 0x30))();
          *(undefined4 *)(param_1 + 3) = 3;
        }
        break;
      case 3:
        if ((long *)param_1[0x23] != (long *)0x0) {
          pcVar7 = *(code **)(*(long *)param_1[0x23] + 0x38);
          goto code_r0x023454c0;
        }
        break;
      case 4:
        fVar9 = (float)(**(code **)(*param_1 + 0x88))(param_1,0);
        if (fVar9 != fVar10) {
          fVar11 = fVar10 - fVar9;
          if (uVar5 != 0) {
            fVar11 = (fVar11 * fVar3) / (float)uVar5;
          }
          *(undefined2 *)(param_1 + 5) = 0x100;
          *(float *)((long)param_1 + 0x1c) = fVar10;
          *(float *)(param_1 + 4) = fVar9;
          *(float *)((long)param_1 + 0x24) = fVar11;
        }
        *(undefined4 *)(param_1 + 3) = 4;
        break;
      case 5:
        fVar10 = 0.0;
        if ((param_1[0x24] != 0) &&
           (lVar8 = *(long *)(param_1[0x24] + 0x80), fVar10 = 0.0, lVar8 != 0)) {
          uVar1 = *(int *)puVar4 * 0x19660d + 0x3c6ef35f;
          *(uint *)puVar4 = uVar1;
          fVar10 = *(float *)(lVar8 + 0x14) +
                   (*(float *)(lVar8 + 0x18) - *(float *)(lVar8 + 0x14)) *
                   ((float)(uVar1 & 0x7fffff | 0x3f800000) + -1.0);
        }
        fVar9 = fStack_b0;
        if (fStack_b0 <= fVar2) {
          fVar9 = fVar2;
        }
        if (fVar10 <= fVar2) {
          fVar10 = fVar2;
        }
        fVar10 = (float)Aska::SoundUtility::VolumeDBBlend(float, float)(fVar9,fVar10);
        fVar9 = (float)(**(code **)(*param_1 + 0x88))(param_1,0);
        if (fVar9 != fVar10) {
          fVar11 = fVar10 - fVar9;
          if (uVar5 != 0) {
            fVar11 = (fVar11 * fVar3) / (float)uVar5;
          }
          *(undefined2 *)(param_1 + 5) = 0x100;
          *(float *)((long)param_1 + 0x1c) = fVar10;
          *(float *)(param_1 + 4) = fVar9;
          *(float *)((long)param_1 + 0x24) = fVar11;
        }
        break;
      case 6:
        fVar10 = 0.0;
        if ((param_1[0x24] != 0) && (lVar8 = *(long *)(param_1[0x24] + 0x80), lVar8 != 0)) {
          uVar1 = *(int *)puVar4 * 0x19660d + 0x3c6ef35f;
          *(uint *)puVar4 = uVar1;
          fVar10 = *(float *)(lVar8 + 0x1c) +
                   (*(float *)(lVar8 + 0x20) - *(float *)(lVar8 + 0x1c)) *
                   ((float)(uVar1 & 0x7fffff | 0x3f800000) + -1.0);
        }
        fVar9 = -12.0;
        if ((-12.0 <= fStack_b0) && (fVar9 = fStack_b0, 2.0 < fStack_b0)) {
          fVar9 = 2.0;
        }
        fVar10 = (float)Aska::SoundUtility::PitchBlend(float, float)(fVar9,fVar10);
        fVar9 = (float)(**(code **)(*param_1 + 0x88))(param_1,1);
        if (fVar9 != fVar10) {
          fVar11 = fVar10 - fVar9;
          if (uVar5 != 0) {
            fVar11 = (fVar11 * fVar3) / (float)uVar5;
          }
          *(undefined2 *)(param_1 + 7) = 0x101;
          *(float *)((long)param_1 + 0x2c) = fVar10;
          *(float *)(param_1 + 6) = fVar9;
          *(float *)((long)param_1 + 0x34) = fVar11;
        }
        break;
      case 7:
        fVar9 = (float)(**(code **)(*param_1 + 0x88))(param_1,2);
        if (fVar9 != fVar10) {
          fVar11 = fVar10 - fVar9;
          if (uVar5 != 0) {
            fVar11 = (fVar11 * fVar3) / (float)uVar5;
          }
          *(undefined2 *)(param_1 + 9) = 0x102;
          *(float *)((long)param_1 + 0x3c) = fVar10;
          *(float *)(param_1 + 8) = fVar9;
          *(float *)((long)param_1 + 0x44) = fVar11;
        }
        break;
      case 8:
        lVar8 = param_1[0x23];
        if (lVar8 != 0) {
          fVar10 = fVar2;
          if (_UNK_027fac84 <= ABS(fStack_b0)) {
            fVar10 = (float)log10f();
            fVar10 = fVar10 * 20.0;
          }
          *(undefined1 *)(lVar8 + 0x28) = 1;
          *(float *)(lVar8 + 0x18) = fVar10;
          lVar8 = param_1[0x23];
          *(undefined1 *)(lVar8 + 0x28) = 1;
          *(uint *)(lVar8 + 0x20) = uVar5;
        }
        break;
      case 9:
        lVar8 = param_1[0x23];
        if (lVar8 != 0) {
          *(undefined1 *)(lVar8 + 0x28) = 1;
          *(float *)(lVar8 + 0x24) = fStack_b0;
          lVar8 = param_1[0x23];
          *(undefined1 *)(lVar8 + 0x28) = 1;
          *(uint *)(lVar8 + 0x20) = uStack_a8;
        }
      }
      uVar6 = Aska::AudioPlayer::GetMessage(Aska::AudioMessage*)(param_1,auStack_b8);
    } while ((uVar6 & 1) != 0);
  }
  return;
}

// ==== Aska::WavePlayer::SetInterface(unsigned int, Aska::AudioInterface*)
// vaddr 0x224575c | ghidra 0x234575c | size 112 | symbol _ZN4Aska10WavePlayer12SetInterfaceEjPNS_14AudioInterfaceE | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska10WavePlayer12SetInterfaceEjPNS_14AudioInterfaceE
          (long *param_1,undefined8 param_2,long param_3)

{
  undefined8 uVar1;
  long lVar2;
  long lVar3;
  
  lVar2 = (**(code **)(*param_1 + 0x50))();
  uVar1 = 0;
  if (lVar2 != 0) {
    if (param_3 != 0) {
      uVar1 = (*(code *)PTR__ZN4Aska14AudioInterface7ConnectEPNS_14AudioConnectorE_02caaf68)
                        (param_3,lVar2);
      return uVar1;
    }
    lVar3 = Aska::SoundManager::QueryAudioInterface(Aska::AudioConnector*) const(*(undefined8 *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50,lVar2);
    if (lVar3 != 0) {
      uVar1 = (*(code *)PTR__ZN4Aska14AudioInterface10DisconnectEPNS_14AudioConnectorE_02c979e0)
                        (lVar3,lVar2);
      return uVar1;
    }
    uVar1 = 1;
  }
  return uVar1;
}

// ==== Aska::WavePlayer::GetInterface(unsigned int)
// vaddr 0x22457cc | ghidra 0x23457cc | size 56 | symbol _ZN4Aska10WavePlayer12GetInterfaceEj | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska10WavePlayer12GetInterfaceEj(long *param_1)

{
  long lVar1;
  
  lVar1 = (**(code **)(*param_1 + 0x50))();
  if (lVar1 != 0) {
    (*(code *)PTR__ZNK4Aska12SoundManager19QueryAudioInterfaceEPNS_14AudioConnectorE_02ca99d0)
              (*(undefined8 *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50,lVar1);
    return;
  }
  return;
}

// ==== Aska::WavePlayer::GetConnector(unsigned int)
// vaddr 0x2245804 | ghidra 0x2345804 | size 24 | symbol _ZN4Aska10WavePlayer12GetConnectorEj | lib libSOA-3.7.0.so | 2026-10-08
long _ZN4Aska10WavePlayer12GetConnectorEj(long param_1,uint param_2)

{
  param_1 = param_1 + 0x100;
  if ((param_2 & 0xff00ffff) != 0x2000000) {
    param_1 = 0;
  }
  return param_1;
}

// ==== Aska::WavePlayer::Get(unsigned long, void*) const
// vaddr 0x224581c | ghidra 0x234581c | size 8 | symbol _ZNK4Aska10WavePlayer3GetEmPv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK4Aska10WavePlayer3GetEmPv(void)

{
  return 0;
}

// ==== Aska::WavePlayer::Set(unsigned long, void const*)
// vaddr 0x2245824 | ghidra 0x2345824 | size 8 | symbol _ZN4Aska10WavePlayer3SetEmPKv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska10WavePlayer3SetEmPKv(void)

{
  return 0;
}

// ==== Aska::WavePlayer::GetClassID(int) const
// vaddr 0x2245868 | ghidra 0x2345868 | size 68 | symbol _ZNK4Aska10WavePlayer10GetClassIDEi | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK4Aska10WavePlayer10GetClassIDEi(undefined8 param_1,int param_2)

{
  undefined8 uVar1;
  undefined8 uVar2;
  
  if (param_2 != 0) {
    uVar2 = 0xf000f001;
    if (param_2 != 2) {
      uVar2 = 0xf000;
    }
    uVar1 = 0xf000f001f212;
    if (param_2 != 1) {
      uVar1 = uVar2;
    }
    return uVar1;
  }
  return 0xf000f212f215;
}

// ==== Aska::WavePlayer::GetThisType() const
// vaddr 0x22458ac | ghidra 0x23458ac | size 8 | symbol _ZNK4Aska10WavePlayer11GetThisTypeEv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK4Aska10WavePlayer11GetThisTypeEv(void)

{
  return 1;
}

// ==== Aska::WaveBuffer::CreateBuffer(Aska::MultiMediaStream*, Aska::AFF::AaoWAVE const*)
// vaddr 0x2247750 | ghidra 0x2347750 | size 28 | symbol _ZN4Aska10WaveBuffer12CreateBufferEPNS_16MultiMediaStreamEPKNS_3AFF7AaoWAVEE | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska10WaveBuffer12CreateBufferEPNS_16MultiMediaStreamEPKNS_3AFF7AaoWAVEE
          (long param_1,undefined8 param_2,undefined8 param_3)

{
  if (*(long *)(param_1 + 8) != 0) {
    return 0;
  }
  *(undefined8 *)(param_1 + 8) = param_2;
  *(undefined8 *)(param_1 + 0x10) = param_3;
  return 1;
}

// ==== Aska::WaveBuffer::DeleteBuffer()
// vaddr 0x224776c | ghidra 0x234776c | size 40 | symbol _ZN4Aska10WaveBuffer12DeleteBufferEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska10WaveBuffer12DeleteBufferEv(long param_1)

{
  long *plVar1;
  
  plVar1 = *(long **)(param_1 + 8);
  if (plVar1 != (long *)0x0) {
    (**(code **)(*plVar1 + 8))();
    *(long *)(param_1 + 8) = 0;
    *(undefined8 *)(param_1 + 0x10) = 0;
  }
  return;
}

// ==== Aska::WaveBuffer::LockBuffer(void**, unsigned long, bool)
// vaddr 0x2247794 | ghidra 0x2347794 | size 184 | symbol _ZN4Aska10WaveBuffer10LockBufferEPPvmb | lib libSOA-3.7.0.so | 2026-10-08
long _ZN4Aska10WaveBuffer10LockBufferEPPvmb(long param_1,long param_2,long param_3,uint param_4)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  long lVar4;
  
  lVar4 = -0x3bd;
  if ((param_2 != 0) && (param_3 != 0)) {
    if (*(long **)(param_1 + 8) == (long *)0x0) {
      lVar4 = -0x3bc;
    }
    else {
      lVar4 = (**(code **)(**(long **)(param_1 + 8) + 0x98))();
      if ((-1 < lVar4) && (lVar4 != 0)) {
        uVar3 = *(uint *)(param_1 + 0x20);
        if ((param_4 & 1) == 0) {
          if (*(uint *)(param_1 + 0x24) != uVar3) {
            iVar2 = 0;
            if (uVar3 + 1 < 0x11) {
              iVar2 = uVar3 + 1;
            }
            *(int *)(param_1 + (ulong)uVar3 * 4 + 0x28) = (int)lVar4;
            *(int *)(param_1 + 0x20) = iVar2;
            return lVar4;
          }
        }
        else {
          iVar2 = 0x10;
          if (-1 < (int)(uVar3 - 1)) {
            iVar2 = uVar3 - 1;
          }
          piVar1 = (int *)(param_1 + (long)iVar2 * 4 + 0x28);
          if (iVar2 != *(int *)(param_1 + 0x24)) {
            *piVar1 = *piVar1 + (int)lVar4;
            return lVar4;
          }
        }
        lVar4 = -1;
      }
    }
  }
  return lVar4;
}

// ==== Aska::WaveBuffer::UnlockBuffer()
// vaddr 0x224784c | ghidra 0x234784c | size 80 | symbol _ZN4Aska10WaveBuffer12UnlockBufferEv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska10WaveBuffer12UnlockBufferEv(long param_1)

{
  uint uVar1;
  long *plVar2;
  undefined8 uVar3;
  
  plVar2 = *(long **)(param_1 + 8);
  if (plVar2 == (long *)0x0) {
    return 0xfffffffffffffc44;
  }
  uVar1 = 0;
  if (*(int *)(param_1 + 0x24) + 1U < 0x11) {
    uVar1 = *(int *)(param_1 + 0x24) + 1;
  }
  if (uVar1 == *(uint *)(param_1 + 0x20)) {
    return 0xffffffffffffffff;
  }
  *(uint *)(param_1 + 0x24) = uVar1;
                    /* WARNING: Could not recover jumptable at 0x02347898. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  uVar3 = (**(code **)(*plVar2 + 0xa0))(plVar2,*(undefined4 *)(param_1 + (ulong)uVar1 * 4 + 0x28));
  return uVar3;
}

// ==== Aska::WaveVoiceBase::WaveVoiceBase()
// vaddr 0x2247b64 | ghidra 0x2347b64 | size 48 | symbol _ZN4Aska13WaveVoiceBaseC2Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska13WaveVoiceBaseC2Ev(long *param_1)

{
  undefined *puVar1;
  
  *(undefined4 *)(param_1 + 1) = 0;
  puVar1 = PTR__ZTVN4Aska13WaveVoiceBaseE_02cc42d0;
  param_1[2] = 0;
  param_1[3] = 0;
  *(undefined4 *)(param_1 + 4) = 0;
  *(undefined4 *)((long)param_1 + 0x24) = 0x3f800000;
  *(undefined2 *)(param_1 + 5) = 0x101;
  *param_1 = (long)(puVar1 + 0x10);
  *(undefined1 *)((long)param_1 + 0x2a) = 0;
  return;
}

// ==== Aska::WaveVoiceBase::~WaveVoiceBase()
// vaddr 0x2247b94 | ghidra 0x2347b94 | size 36 | symbol _ZN4Aska13WaveVoiceBaseD2Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska13WaveVoiceBaseD1Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska13WaveVoiceBaseE_02cc42d0 + 0x10);
  if (*(char *)((long)param_1 + 0x2a) != '\0') {
    param_1[2] = 0;
    *(undefined1 *)((long)param_1 + 0x2a) = 0;
  }
  return;
}

// ==== Aska::WaveVoiceBase::~WaveVoiceBase()
// vaddr 0x2247bb8 | ghidra 0x2347bb8 | size 4 | symbol _ZN4Aska13WaveVoiceBaseD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska13WaveVoiceBaseD0Ev(void)

{
  code *pcVar1;
  
                    /* WARNING: Does not return */
  pcVar1 = (code *)SoftwareBreakpoint(1,0x2347bbc);
  (*pcVar1)();
}

// ==== Aska::WaveVoiceBase::CreateVoiceCommon(void const*, Aska::PackedPlayParams const*)
// vaddr 0x2247bbc | ghidra 0x2347bbc | size 140 | symbol _ZN4Aska13WaveVoiceBase17CreateVoiceCommonEPKvPKNS_16PackedPlayParamsE | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska13WaveVoiceBase17CreateVoiceCommonEPKvPKNS_16PackedPlayParamsE
          (long *param_1,long param_2,long param_3)

{
  if (*(char *)((long)param_1 + 0x2a) == '\0') {
    param_1[2] = param_2;
    if (*(int *)(param_2 + 0x1c) != 0) {
      *(undefined4 *)(param_1 + 3) = *(undefined4 *)(param_3 + 4);
      *(undefined4 *)((long)param_1 + 0x1c) = *(undefined4 *)(param_3 + 8);
      *(undefined4 *)(param_1 + 4) = *(undefined4 *)(param_3 + 0xc);
      (**(code **)(*param_1 + 0x58))(param_1);
      (**(code **)(*param_1 + 0x60))(param_1);
      *(undefined1 *)((long)param_1 + 0x2a) = 1;
      return 1;
    }
    *(undefined1 *)((long)param_1 + 0x2a) = 1;
    (**(code **)(*param_1 + 0x18))(param_1);
  }
  return 0;
}

// ==== Aska::WaveVoiceBase::DeleteVoice()
// vaddr 0x2247c48 | ghidra 0x2347c48 | size 20 | symbol _ZN4Aska13WaveVoiceBase11DeleteVoiceEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska13WaveVoiceBase11DeleteVoiceEv(long param_1)

{
  if (*(char *)(param_1 + 0x2a) != '\0') {
    *(undefined8 *)(param_1 + 0x10) = 0;
    *(undefined1 *)(param_1 + 0x2a) = 0;
  }
  return;
}

// ==== Aska::WaveVoiceBase::AudioKick()
// vaddr 0x2247c5c | ghidra 0x2347c5c | size 72 | symbol _ZN4Aska13WaveVoiceBase9AudioKickEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska13WaveVoiceBase9AudioKickEv(long *param_1)

{
  if ((char)param_1[5] != '\0') {
    (**(code **)(*param_1 + 0x58))(param_1);
    *(undefined1 *)(param_1 + 5) = 0;
  }
  if (*(char *)((long)param_1 + 0x29) != '\0') {
    (**(code **)(*param_1 + 0x60))(param_1);
    *(undefined1 *)((long)param_1 + 0x29) = 0;
  }
  return;
}

// ==== Aska::WaveBuffer::~WaveBuffer()
// vaddr 0x2247ca4 | ghidra 0x2347ca4 | size 56 | symbol _ZN4Aska10WaveBufferD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska10WaveBufferD0Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska10WaveBufferE_02cb8488 + 0x10);
  if ((long *)param_1[1] != (long *)0x0) {
    (**(code **)(*(long *)param_1[1] + 8))();
  }
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::WaveVoiceBase::AudioSignal(unsigned long)
// vaddr 0x2247d14 | ghidra 0x2347d14 | size 4 | symbol _ZN4Aska13WaveVoiceBase11AudioSignalEm | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska13WaveVoiceBase11AudioSignalEm(void)

{
  return;
}

// ==== Aska::WaveVoiceBase::UpdateVolumeMatrix()
// vaddr 0x2247d18 | ghidra 0x2347d18 | size 4 | symbol _ZN4Aska13WaveVoiceBase18UpdateVolumeMatrixEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska13WaveVoiceBase18UpdateVolumeMatrixEv(void)

{
  return;
}

// ==== Aska::WaveVoiceBase::UpdatePitchbend()
// vaddr 0x2247d1c | ghidra 0x2347d1c | size 4 | symbol _ZN4Aska13WaveVoiceBase15UpdatePitchbendEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska13WaveVoiceBase15UpdatePitchbendEv(void)

{
  return;
}


// FAILED to create function at 029d9520 typeinfo name for Aska::TQueue<Aska::SLVoice::AdpcmSubmitContext, 3>
// FAILED to create function at 029d9560 typeinfo name for Aska::TQueue<Aska::SLVoice::OggSubmitContext, 8>
// FAILED to create function at 02c5f128 Aska::SLVoice::vtable
// FAILED to create function at 02c5f1a0 Aska::SLVoice::typeinfo
// FAILED to create function at 02c5f238 Aska::TQueue<Aska::SLVoice::AdpcmSubmitContext,3>::vtable
// FAILED to create function at 02c5f258 Aska::TQueue<Aska::SLVoice::AdpcmSubmitContext,3>::typeinfo
// FAILED to create function at 02c5f268 Aska::TQueue<Aska::SLVoice::OggSubmitContext,8>::vtable
// FAILED to create function at 02c5f288 Aska::TQueue<Aska::SLVoice::OggSubmitContext,8>::typeinfo
// FAILED to create function at 02c5f748 Aska::WavePlayer::vtable
// FAILED to create function at 02c5f810 Aska::WavePlayer::typeinfo
// FAILED to create function at 02c5fab8 Aska::WaveVoiceBase::vtable
// FAILED to create function at 02c5fb30 Aska::WaveBuffer::vtable
// FAILED to create function at 02c5fb60 Aska::WaveBuffer::typeinfo
// FAILED to create function at 02c5fbd0 Aska::WaveVoiceBase::typeinfo
// FAILED to create function at 02e75428 Aska::SLVoice::m_bNoWarning
