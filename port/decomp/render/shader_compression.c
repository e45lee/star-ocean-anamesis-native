// port/decomp/render/shader_compression.c: Ghidra decompiles for the render subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-04 06:27 UTC: tools/decomp.sh '--into' 'render/shader_compression' 'Aska::ShaderComprssionTree::' 'Aska::ShaderCompression::'

// ==== Aska::ShaderComprssionTree::ShaderComprssionTree()
// vaddr 0x21c626c | ghidra 0x22c626c | size 60 | symbol _ZN4Aska20ShaderComprssionTreeC2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska20ShaderComprssionTreeC1Ev(long param_1)

{
  long lVar1;
  long lVar2;
  undefined8 *puVar3;
  
  lVar1 = 0x10000;
  puVar3 = (undefined8 *)(param_1 + 0xc024);
  do {
    puVar3[-1] = 0x100000001000;
    puVar3[-2] = 0x100000001000;
    puVar3[1] = 0x100000001000;
    *puVar3 = 0x100000001000;
    lVar1 = lVar1 + -8;
    puVar3 = puVar3 + 4;
    lVar2 = 0;
  } while (lVar1 != 0);
  do {
    lVar1 = param_1 + lVar2;
    lVar2 = lVar2 + 0x20;
    *(undefined8 *)(lVar1 + 0x10) = 0x100000001000;
    *(undefined8 *)(lVar1 + 8) = 0x100000001000;
    *(undefined8 *)(lVar1 + 0x20) = 0x100000001000;
    *(undefined8 *)(lVar1 + 0x18) = 0x100000001000;
  } while (lVar2 != 0x4000);
  return;
}

// ==== Aska::ShaderComprssionTree::InsertNode(int, int)
// vaddr 0x21c62a8 | ghidra 0x22c62a8 | size 396 | symbol _ZN4Aska20ShaderComprssionTree10InsertNodeEii | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska20ShaderComprssionTree10InsertNodeEii(uint *param_1,uint param_2,int param_3)

{
  uint uVar1;
  bool bVar2;
  long lVar3;
  uint uVar4;
  ulong uVar5;
  uint uVar6;
  ulong uVar7;
  int iVar8;
  uint *puVar9;
  
  param_1[(long)(int)param_2 + 0x1003] = 0x1000;
  param_1[(long)(int)param_2 + 0x2004] = 0x1000;
  uVar4 = param_1[(long)(int)param_2 + 0x13005] + 0x1001;
  uVar5 = (ulong)uVar4;
  param_1[1] = 0;
  if (param_3 < 2) {
    puVar9 = param_1 + (long)(int)uVar4 + 0x2004;
    uVar6 = *puVar9;
    if (uVar6 == 0x1000) {
code_r0x022c63ac:
      *puVar9 = param_2;
      param_1[(long)(int)param_2 + 2] = uVar4;
      return;
    }
    *param_1 = uVar6;
    param_1[1] = 1;
    uVar5 = (ulong)uVar6;
  }
  else {
    iVar8 = 1;
    uVar6 = 0;
    do {
      do {
        uVar4 = (uint)uVar5;
        if (iVar8 < 0) {
          lVar3 = (long)(int)uVar4 + 0x1003;
        }
        else {
          lVar3 = (long)(int)uVar4 + 0x2004;
        }
        puVar9 = param_1 + lVar3;
        uVar1 = *puVar9;
        if (uVar1 == 0x1000) goto code_r0x022c63ac;
        uVar5 = (ulong)uVar1;
        uVar4 = 1;
        do {
          iVar8 = param_1[(ulong)(param_2 + uVar4 & 0xfff) + 0x13005] -
                  param_1[(ulong)(uVar1 + uVar4 & 0xfff) + 0x13005];
          if (iVar8 != 0) {
            bVar2 = true;
            goto joined_r0x022c6380;
          }
          uVar4 = uVar4 + 1;
        } while ((int)uVar4 < param_3);
        bVar2 = false;
        iVar8 = 0;
joined_r0x022c6380:
      } while ((int)uVar4 <= (int)uVar6);
      *param_1 = uVar1;
      param_1[1] = uVar4;
      uVar6 = uVar4;
    } while (bVar2);
  }
  uVar7 = -(uVar5 >> 0x1f) & 0xfffffffc00000000 | uVar5 << 2;
  param_1[(long)(int)param_2 + 2] = *(uint *)((long)param_1 + uVar7 + 8);
  param_1[(long)(int)param_2 + 0x1003] = *(uint *)((long)param_1 + uVar7 + 0x400c);
  param_1[(long)(int)param_2 + 0x2004] = *(uint *)((long)param_1 + uVar7 + 0x8010);
  param_1[(long)*(int *)((long)param_1 + uVar7 + 0x400c) + 2] = param_2;
  param_1[(long)*(int *)((long)param_1 + uVar7 + 0x8010) + 2] = param_2;
  lVar3 = (long)*(int *)((long)param_1 + uVar7 + 8);
  puVar9 = param_1 + lVar3 + 0x2004;
  if (param_1[lVar3 + 0x2004] != (uint)uVar5) {
    puVar9 = param_1 + lVar3 + 0x1003;
  }
  *puVar9 = param_2;
  *(undefined4 *)((long)param_1 + uVar7 + 8) = 0x1000;
  return;
}

// ==== Aska::ShaderComprssionTree::DeleteNode(int)
// vaddr 0x21c6434 | ghidra 0x22c6434 | size 280 | symbol _ZN4Aska20ShaderComprssionTree10DeleteNodeEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska20ShaderComprssionTree10DeleteNodeEi(long param_1,int param_2)

{
  long lVar1;
  int *piVar2;
  int *piVar3;
  long lVar4;
  int *piVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  long lVar9;
  int iVar10;
  
  piVar5 = (int *)(param_1 + (long)param_2 * 4 + 8);
  iVar8 = *piVar5;
  if (iVar8 != 0x1000) {
    lVar1 = param_1 + (long)param_2 * 4;
    piVar2 = (int *)(lVar1 + 0x8010);
    iVar10 = *piVar2;
    piVar3 = (int *)(lVar1 + 0x400c);
    iVar6 = *piVar3;
    iVar7 = iVar6;
    if ((iVar10 != 0x1000) && (iVar7 = iVar10, iVar6 != 0x1000)) {
      iVar8 = *(int *)(param_1 + (long)iVar6 * 4 + 0x8010);
      if (iVar8 != 0x1000) {
        do {
          iVar6 = iVar8;
          iVar8 = *(int *)(param_1 + (long)iVar6 * 4 + 0x8010);
        } while (iVar8 != 0x1000);
        lVar1 = param_1 + 8;
        lVar9 = (long)iVar6 * 4;
        lVar4 = param_1 + lVar9;
        *(undefined4 *)(param_1 + (long)*(int *)(lVar1 + lVar9) * 4 + 0x8010) =
             *(undefined4 *)(lVar4 + 0x400c);
        *(undefined4 *)(lVar1 + (long)*(int *)(lVar4 + 0x400c) * 4) = *(undefined4 *)(lVar1 + lVar9)
        ;
        *(int *)(lVar4 + 0x400c) = *piVar3;
        *(int *)(lVar1 + (long)*piVar3 * 4) = iVar6;
        iVar10 = *piVar2;
      }
      *(int *)(param_1 + (long)iVar6 * 4 + 0x8010) = iVar10;
      *(int *)(param_1 + (long)*piVar2 * 4 + 8) = iVar6;
      iVar8 = *piVar5;
      iVar7 = iVar6;
    }
    *(int *)(param_1 + (long)iVar7 * 4 + 8) = iVar8;
    param_1 = param_1 + (long)*piVar5 * 4;
    piVar2 = (int *)(param_1 + 0x8010);
    if (*piVar2 != param_2) {
      piVar2 = (int *)(param_1 + 0x400c);
    }
    *piVar2 = iVar7;
    *piVar5 = 0x1000;
  }
  return;
}

// ==== Aska::ShaderCompression::DecompressLZ(unsigned char*, unsigned char*)
// vaddr 0x21c654c | ghidra 0x22c654c | size 136 | symbol _ZN4Aska17ShaderCompression12DecompressLZEPhS1_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska17ShaderCompression12DecompressLZEPhS1_(byte *param_1,byte *param_2)

{
  uint uVar1;
  byte bVar2;
  byte *pbVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  
code_r0x022c657c:
  pbVar3 = param_1 + 1;
  bVar2 = *param_1;
  uVar4 = (uint)bVar2;
  iVar5 = 8;
  param_1 = pbVar3;
  if ((bVar2 & 1) != 0) goto code_r0x022c6560;
  do {
    uVar1 = (uint)*param_1 | (param_1[1] & 0xf) << 8;
    if (uVar1 == 0) {
      return;
    }
    bVar2 = param_1[1] >> 4;
    iVar6 = bVar2 + 3;
    pbVar3 = param_2;
    do {
      iVar6 = iVar6 + -1;
      *pbVar3 = pbVar3[-(ulong)uVar1];
      pbVar3 = pbVar3 + 1;
    } while (iVar6 != 0);
    param_2 = param_2 + (ulong)bVar2 + 3;
    param_1 = param_1 + 2;
    while( true ) {
      iVar5 = iVar5 + -1;
      if (iVar5 == 0) goto code_r0x022c657c;
      uVar4 = (int)uVar4 >> 1;
      if ((uVar4 & 1) == 0) break;
code_r0x022c6560:
      *param_2 = *param_1;
      param_2 = param_2 + 1;
      param_1 = param_1 + 1;
    }
  } while( true );
}

// ==== Aska::ShaderCompression::CompressLZ(void*, int, void*)
// vaddr 0x21c65d4 | ghidra 0x22c65d4 | size 2084 | symbol _ZN4Aska17ShaderCompression10CompressLZEPviS1_ | lib libSOA-3.7.0.so | 2026-10-04
int _ZN4Aska17ShaderCompression10CompressLZEPviS1_(byte *param_1,int param_2,byte *param_3)

{
  uint uVar1;
  uint uVar2;
  long lVar3;
  undefined8 *puVar4;
  int *piVar5;
  int iVar6;
  long lVar7;
  byte bVar8;
  uint uVar9;
  int *piVar10;
  ulong uVar11;
  uint uVar12;
  ulong uVar13;
  long lVar14;
  ulong uVar15;
  byte *pbVar16;
  byte *pbVar17;
  uint uVar18;
  undefined8 *puVar19;
  ulong uVar20;
  uint uVar21;
  uint uVar22;
  uint uVar23;
  uint uVar24;
  uint uVar25;
  undefined8 uVar26;
  undefined8 uVar27;
  undefined8 uVar28;
  int iStack_a8;
  byte abStack_84 [8];
  undefined8 auStack_7c [3];
  
  piVar5 = (int *)operator new(unsigned long, std::nothrow_t const&)(0x50058,PTR__ZSt7nothrow_02cb9a80);
  if (piVar5 == (int *)0x0) {
    return 0;
  }
  lVar7 = 0x10000;
  piVar10 = piVar5 + 0x3009;
  do {
    piVar10[-2] = 0x1000;
    piVar10[-1] = 0x1000;
    piVar10[-4] = 0x1000;
    piVar10[-3] = 0x1000;
    piVar10[2] = 0x1000;
    piVar10[3] = 0x1000;
    piVar10[0] = 0x1000;
    piVar10[1] = 0x1000;
    lVar7 = lVar7 + -8;
    piVar10 = piVar10 + 8;
    lVar14 = 0;
  } while (lVar7 != 0);
  do {
    lVar7 = lVar14 + 0x20;
    *(undefined8 *)((long)piVar5 + lVar14 + 0x10) = 0x100000001000;
    *(undefined8 *)((long)piVar5 + lVar14 + 8) = 0x100000001000;
    *(undefined8 *)((long)piVar5 + lVar14 + 0x20) = 0x100000001000;
    *(undefined8 *)((long)piVar5 + lVar14 + 0x18) = 0x100000001000;
    lVar14 = lVar7;
  } while (lVar7 != 0x4000);
  abStack_84[0] = 0;
  if (param_2 < 0x1011) {
    iVar6 = param_2 + 0x12;
    if (0x1010 < iVar6) {
      iVar6 = 0x1011;
    }
    if (param_2 < iVar6) {
      iVar6 = -0x13 - param_2;
      if (iVar6 < -0x1011) {
        iVar6 = -0x1012;
      }
      memset(piVar5 + (long)param_2 + 0x13005,0,
                      (ulong)(uint)((-2 - param_2) - iVar6) * 4 + 4);
    }
    if (param_2 < 1) {
      uVar25 = 0;
    }
    else {
      piVar5[0x13005] = (uint)*param_1;
      if (param_2 == 1) {
        uVar25 = 1;
      }
      else {
        piVar5[0x13006] = (uint)param_1[1];
        if (param_2 < 3) {
          uVar25 = 2;
        }
        else {
          piVar5[0x13007] = (uint)param_1[2];
          if (param_2 == 3) {
            uVar25 = 3;
          }
          else {
            piVar5[0x13008] = (uint)param_1[3];
            if (param_2 < 5) {
              uVar25 = 4;
            }
            else {
              piVar5[0x13009] = (uint)param_1[4];
              if (param_2 == 5) {
                uVar25 = 5;
              }
              else {
                piVar5[0x1300a] = (uint)param_1[5];
                if (param_2 < 7) {
                  uVar25 = 6;
                }
                else {
                  piVar5[0x1300b] = (uint)param_1[6];
                  if (param_2 == 7) {
                    uVar25 = 7;
                  }
                  else {
                    piVar5[0x1300c] = (uint)param_1[7];
                    if (param_2 < 9) {
                      uVar25 = 8;
                    }
                    else {
                      piVar5[0x1300d] = (uint)param_1[8];
                      if (param_2 == 9) {
                        uVar25 = 9;
                      }
                      else {
                        piVar5[0x1300e] = (uint)param_1[9];
                        if (param_2 < 0xb) {
                          uVar25 = 10;
                        }
                        else {
                          piVar5[0x1300f] = (uint)param_1[10];
                          if (param_2 == 0xb) {
                            uVar25 = 0xb;
                          }
                          else {
                            piVar5[0x13010] = (uint)param_1[0xb];
                            if (param_2 < 0xd) {
                              uVar25 = 0xc;
                            }
                            else {
                              piVar5[0x13011] = (uint)param_1[0xc];
                              if (param_2 == 0xd) {
                                uVar25 = 0xd;
                              }
                              else {
                                piVar5[0x13012] = (uint)param_1[0xd];
                                if (param_2 < 0xf) {
                                  uVar25 = 0xe;
                                }
                                else {
                                  piVar5[0x13013] = (uint)param_1[0xe];
                                  if (param_2 == 0xf) {
                                    uVar25 = 0xf;
                                  }
                                  else {
                                    piVar5[0x13014] = (uint)param_1[0xf];
                                    if (param_2 < 0x11) {
                                      uVar25 = 0x10;
                                    }
                                    else {
                                      piVar5[0x13015] = (uint)param_1[0x10];
                                      if (param_2 != 0x11) goto code_r0x022c6800;
                                      uVar25 = 0x11;
                                    }
                                  }
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
    piVar5[(ulong)uVar25 + 0x13005] = 0;
  }
  else {
    piVar5[0x13005] = (uint)*param_1;
    piVar5[0x13006] = (uint)param_1[1];
    piVar5[0x13007] = (uint)param_1[2];
    piVar5[0x13008] = (uint)param_1[3];
    piVar5[0x13009] = (uint)param_1[4];
    piVar5[0x1300a] = (uint)param_1[5];
    piVar5[0x1300b] = (uint)param_1[6];
    piVar5[0x1300c] = (uint)param_1[7];
    piVar5[0x1300d] = (uint)param_1[8];
    piVar5[0x1300e] = (uint)param_1[9];
    piVar5[0x1300f] = (uint)param_1[10];
    piVar5[0x13010] = (uint)param_1[0xb];
    piVar5[0x13011] = (uint)param_1[0xc];
    piVar5[0x13012] = (uint)param_1[0xd];
    piVar5[0x13013] = (uint)param_1[0xe];
    piVar5[0x13014] = (uint)param_1[0xf];
    piVar5[0x13015] = (uint)param_1[0x10];
code_r0x022c6800:
    uVar25 = 0x12;
    piVar5[0x13016] = (uint)param_1[0x11];
  }
  uVar24 = 0x12;
  Aska::ShaderComprssionTree::InsertNode(int, int)(piVar5,0,0x12);
  uVar23 = 0;
  uVar9 = 1;
  uVar18 = 1;
  iStack_a8 = 0;
  uVar2 = uVar25;
  uVar21 = uVar25;
  do {
    uVar12 = piVar5[1];
    uVar22 = uVar25;
    if ((int)uVar12 <= (int)uVar25) {
      uVar22 = uVar12;
    }
    iVar6 = uVar2 + uVar22 + -0x11;
    if (param_2 <= iVar6) {
      uVar22 = param_2 - uVar2;
    }
    if (((int)uVar25 < (int)uVar12) || (param_2 <= iVar6)) {
      piVar5[1] = uVar22;
      if ((int)uVar22 < 3) goto code_r0x022c6918;
code_r0x022c694c:
      uVar12 = uVar18 + 1;
      bVar8 = (char)uVar22 * '\x10' - 0x30U | (byte)(uVar23 - *piVar5 >> 8) & 0xf;
      iVar6 = 2;
      abStack_84[(int)uVar18] = (byte)(uVar23 - *piVar5);
    }
    else {
      if (2 < (int)uVar22) goto code_r0x022c694c;
code_r0x022c6918:
      uVar22 = 1;
      piVar5[1] = 1;
      bVar8 = (byte)piVar5[(long)(int)uVar23 + 0x13005];
      abStack_84[0] = abStack_84[0] | (byte)uVar9;
      iVar6 = 1;
      uVar12 = uVar18;
    }
    uVar1 = iVar6 + uVar18;
    abStack_84[(int)uVar12] = bVar8;
    if ((uVar9 << 1 & 0xfe) == 0) {
      if (0 < (int)uVar1) {
        uVar13 = (ulong)uVar1;
        pbVar16 = param_3;
        if (uVar1 < 0x20) {
code_r0x022c69cc:
          lVar7 = 0;
code_r0x022c69d4:
          lVar14 = uVar13 - lVar7;
          pbVar17 = abStack_84 + lVar7;
          do {
            lVar14 = lVar14 + -1;
            *pbVar16 = *pbVar17;
            pbVar16 = pbVar16 + 1;
            pbVar17 = pbVar17 + 1;
          } while (lVar14 != 0);
        }
        else {
          lVar7 = uVar13 - (uVar1 & 0x1f);
          if (lVar7 == 0) goto code_r0x022c69d4;
          if ((param_3 < abStack_84 + uVar13) && (abStack_84 < param_3 + uVar13))
          goto code_r0x022c69cc;
          pbVar16 = param_3 + 0x10;
          lVar14 = lVar7;
          puVar19 = auStack_7c + 1;
          do {
            puVar4 = puVar19 + -1;
            uVar26 = puVar19[-2];
            uVar28 = puVar19[1];
            uVar27 = *puVar19;
            lVar14 = lVar14 + -0x20;
            puVar19 = puVar19 + 4;
            *(undefined8 *)(pbVar16 + -8) = *puVar4;
            *(undefined8 *)(pbVar16 + -0x10) = uVar26;
            *(undefined8 *)(pbVar16 + 8) = uVar28;
            *(undefined8 *)pbVar16 = uVar27;
            pbVar16 = pbVar16 + 0x20;
          } while (lVar14 != 0);
          pbVar16 = param_3 + lVar7;
          if ((uVar1 & 0x1f) != 0) goto code_r0x022c69d4;
        }
        param_3 = param_3 + (ulong)((uVar18 + iVar6) - 1) + 1;
      }
      uVar18 = 1;
      abStack_84[0] = 0;
      iStack_a8 = uVar1 + iStack_a8;
      uVar9 = 1;
    }
    else {
      uVar9 = uVar9 << 1 & 0x1fe;
      uVar18 = uVar1;
    }
    lVar7 = 0;
    if ((0 < (int)uVar22) && ((int)uVar21 < param_2)) {
      lVar14 = 0;
      do {
        bVar8 = param_1[lVar14 + (int)uVar21];
        Aska::ShaderComprssionTree::DeleteNode(int)(piVar5,uVar24);
        uVar23 = uVar23 + 1 & 0xfff;
        piVar5[(long)(int)uVar24 + 0x13005] = (uint)bVar8;
        uVar24 = uVar24 + 1 & 0xfff;
        Aska::ShaderComprssionTree::InsertNode(int, int)(piVar5,uVar23,0x12);
        lVar7 = lVar14 + 1;
        if ((int)uVar22 <= (int)lVar7) break;
        lVar3 = (long)(int)uVar21 + 1 + lVar14;
        lVar14 = lVar7;
      } while (lVar3 < param_2);
      uVar21 = uVar21 + (int)lVar7;
    }
    iVar6 = (int)lVar7;
    uVar2 = iVar6 + uVar2;
    if (iVar6 < (int)uVar22) {
      iVar6 = uVar22 - iVar6;
      do {
        Aska::ShaderComprssionTree::DeleteNode(int)(piVar5,uVar24);
        uVar25 = uVar25 - 1;
        uVar24 = uVar24 + 1 & 0xfff;
        uVar23 = uVar23 + 1 & 0xfff;
        if (uVar25 != 0) {
          Aska::ShaderComprssionTree::InsertNode(int, int)(piVar5,uVar23,0x12);
        }
        iVar6 = iVar6 + -1;
      } while (iVar6 != 0);
    }
  } while (0 < (int)uVar25);
  (abStack_84 + (int)uVar18)[0] = 0;
  (abStack_84 + (int)uVar18)[1] = 0;
  if ((int)uVar18 < 0) goto code_r0x022c6ba0;
  uVar11 = (ulong)(int)(uVar18 + 2);
  uVar13 = uVar11;
  if ((long)uVar11 < 2) {
    uVar13 = 1;
  }
  if (uVar13 < 0x20) {
code_r0x022c6b70:
    uVar15 = 0;
code_r0x022c6b80:
    do {
      pbVar16 = abStack_84 + uVar15;
      uVar15 = uVar15 + 1;
      *param_3 = *pbVar16;
      param_3 = param_3 + 1;
    } while ((long)uVar15 < (long)uVar11);
  }
  else {
    uVar15 = uVar13 & 0x7fffffffffffffe0;
    if (uVar15 == 0) goto code_r0x022c6b80;
    uVar20 = uVar11;
    if ((long)uVar11 < 2) {
      uVar20 = 1;
    }
    if ((param_3 < abStack_84 + uVar20) && (abStack_84 < param_3 + uVar20)) goto code_r0x022c6b70;
    pbVar16 = param_3 + 0x10;
    puVar19 = auStack_7c + 1;
    uVar20 = uVar15;
    do {
      puVar4 = puVar19 + -1;
      uVar26 = puVar19[-2];
      uVar28 = puVar19[1];
      uVar27 = *puVar19;
      uVar20 = uVar20 - 0x20;
      puVar19 = puVar19 + 4;
      *(undefined8 *)(pbVar16 + -8) = *puVar4;
      *(undefined8 *)(pbVar16 + -0x10) = uVar26;
      *(undefined8 *)(pbVar16 + 8) = uVar28;
      *(undefined8 *)pbVar16 = uVar27;
      pbVar16 = pbVar16 + 0x20;
    } while (uVar20 != 0);
    param_3 = param_3 + uVar15;
    if (uVar13 != uVar15) goto code_r0x022c6b80;
  }
  iStack_a8 = iStack_a8 + uVar18 + 2;
code_r0x022c6ba0:
  operator delete(void*)(piVar5);
  return iStack_a8;
}

// ==== Aska::ShaderCompression::DecompressLZword(unsigned short*, unsigned short*)
// vaddr 0x21c6df8 | ghidra 0x22c6df8 | size 244 | symbol _ZN4Aska17ShaderCompression16DecompressLZwordEPtS1_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska17ShaderCompression16DecompressLZwordEPtS1_(ushort *param_1,undefined8 *param_2)

{
  undefined8 *puVar1;
  uint uVar2;
  ushort *puVar3;
  undefined8 *puVar4;
  uint uVar5;
  int iVar6;
  ulong uVar7;
  ulong uVar8;
  int iVar9;
  long lVar10;
  long lVar11;
  undefined8 uVar12;
  undefined8 uVar13;
  undefined8 uVar14;
  
code_r0x022c6ebc:
  puVar3 = param_1 + 1;
  uVar5 = (uint)*param_1;
  iVar6 = 0x10;
  uVar7 = (ulong)*puVar3;
  puVar4 = param_2;
  if ((*param_1 & 1) == 0) goto code_r0x022c6ee0;
  do {
    param_2 = (undefined8 *)((long)puVar4 + 2);
    *(short *)puVar4 = (short)uVar7;
    while( true ) {
      puVar3 = puVar3 + 1;
      iVar6 = iVar6 + -1;
      param_1 = puVar3;
      if (iVar6 == 0) goto code_r0x022c6ebc;
      uVar5 = (int)uVar5 >> 1;
      uVar7 = (ulong)*puVar3;
      puVar4 = param_2;
      if ((uVar5 & 1) != 0) break;
code_r0x022c6ee0:
      uVar8 = (ulong)((uint)uVar7 & 0xfff);
      if ((uVar7 & 0xfff) == 0) {
        return;
      }
      uVar7 = uVar7 >> 0xc;
      puVar4 = param_2;
      if (uVar7 + 2 < 0x10) {
code_r0x022c6e54:
        lVar10 = 0;
code_r0x022c6e5c:
        iVar9 = ((int)uVar7 + 2) - (int)lVar10;
        do {
          iVar9 = iVar9 + -1;
          *(undefined2 *)puVar4 = *(undefined2 *)((long)puVar4 + uVar8 * -2);
          puVar4 = (undefined8 *)((long)puVar4 + 2);
        } while (iVar9 != 0);
      }
      else {
        uVar2 = (int)uVar7 + 2U & 0xf;
        lVar10 = (uVar7 + 2) - (ulong)uVar2;
        if (lVar10 == 0) goto code_r0x022c6e5c;
        if ((param_2 < (undefined8 *)((long)param_2 + (uVar7 - uVar8) * 2 + 4)) &&
           ((undefined2 *)((long)param_2 + uVar8 * -2) <
            (undefined2 *)((long)param_2 + uVar7 * 2 + 4))) goto code_r0x022c6e54;
        lVar11 = lVar10;
        do {
          puVar1 = (undefined8 *)(uVar8 * -2 + (long)puVar4);
          uVar12 = *puVar1;
          uVar14 = puVar1[3];
          uVar13 = puVar1[2];
          lVar11 = lVar11 + -0x10;
          puVar4[1] = puVar1[1];
          *puVar4 = uVar12;
          puVar4[3] = uVar14;
          puVar4[2] = uVar13;
          puVar4 = puVar4 + 4;
        } while (lVar11 != 0);
        puVar4 = (undefined8 *)((long)param_2 + lVar10 * 2);
        if (uVar2 != 0) goto code_r0x022c6e5c;
      }
      param_2 = (undefined8 *)((long)param_2 + uVar7 * 2 + 4);
    }
  } while( true );
}

// ==== Aska::ShaderCompression::CompressLZword(void*, int, void*)
// vaddr 0x21c6eec | ghidra 0x22c6eec | size 1808 | symbol _ZN4Aska17ShaderCompression14CompressLZwordEPviS1_ | lib libSOA-3.7.0.so | 2026-10-04
int _ZN4Aska17ShaderCompression14CompressLZwordEPviS1_(ushort *param_1,uint param_2,ushort *param_3)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  undefined8 *puVar5;
  undefined4 *puVar6;
  int iVar7;
  long lVar8;
  ushort uVar9;
  undefined8 *puVar10;
  ulong uVar11;
  long lVar12;
  ulong uVar13;
  int iVar14;
  ushort *puVar15;
  ushort *puVar16;
  int iVar17;
  uint uVar18;
  uint uVar19;
  int iVar20;
  int iVar21;
  undefined8 uVar22;
  undefined8 uVar23;
  undefined8 uVar24;
  int iStack_cc;
  ushort *puStack_c8;
  uint uStack_b4;
  uint uStack_b0;
  ushort auStack_a8 [4];
  undefined8 auStack_a0 [8];
  
  puVar6 = (undefined4 *)operator new(unsigned long, std::nothrow_t const&)(0x50058,PTR__ZSt7nothrow_02cb9a80);
  if (puVar6 == (undefined4 *)0x0) {
    return 0;
  }
  lVar8 = 0x10000;
  puVar10 = (undefined8 *)(puVar6 + 0x3009);
  do {
    puVar10[-1] = 0x100000001000;
    puVar10[-2] = 0x100000001000;
    puVar10[1] = 0x100000001000;
    *puVar10 = 0x100000001000;
    lVar8 = lVar8 + -8;
    puVar10 = puVar10 + 4;
    lVar12 = 0;
  } while (lVar8 != 0);
  do {
    lVar8 = lVar12 + 0x20;
    *(undefined8 *)((long)puVar6 + lVar12 + 0x10) = 0x100000001000;
    *(undefined8 *)((long)puVar6 + lVar12 + 8) = 0x100000001000;
    *(undefined8 *)((long)puVar6 + lVar12 + 0x20) = 0x100000001000;
    *(undefined8 *)((long)puVar6 + lVar12 + 0x18) = 0x100000001000;
    lVar12 = lVar8;
  } while (lVar8 != 0x4000);
  auStack_a8[0] = 0;
  if ((int)param_2 < 0x1011) {
    iVar21 = param_2 + 0x12;
    if (0x1010 < iVar21) {
      iVar21 = 0x1011;
    }
    if ((int)param_2 < iVar21) {
      iVar21 = -0x13 - param_2;
      if (iVar21 < -0x1011) {
        iVar21 = -0x1012;
      }
      memset(puVar6 + (long)(int)param_2 + 0x13005,0,
                      (ulong)((-2 - param_2) - iVar21) * 4 + 4);
    }
  }
  uVar3 = param_2;
  if ((int)param_2 < 0) {
    uVar3 = param_2 + 1;
  }
  puVar6[0x13005] = (uint)*param_1;
  if ((int)param_2 < 2) {
    iVar14 = 0;
    iVar21 = 1;
  }
  else {
    puVar6[0x13006] = (uint)param_1[1];
    if ((int)param_2 < 4) {
      iVar14 = 1;
      iVar21 = 2;
    }
    else {
      puVar6[0x13007] = (uint)param_1[2];
      if ((int)param_2 < 6) {
        iVar14 = 2;
        iVar21 = 3;
      }
      else {
        puVar6[0x13008] = (uint)param_1[3];
        if ((int)param_2 < 8) {
          iVar14 = 3;
          iVar21 = 4;
        }
        else {
          puVar6[0x13009] = (uint)param_1[4];
          if ((int)param_2 < 10) {
            iVar14 = 4;
            iVar21 = 5;
          }
          else {
            puVar6[0x1300a] = (uint)param_1[5];
            if ((int)param_2 < 0xc) {
              iVar14 = 5;
              iVar21 = 6;
            }
            else {
              puVar6[0x1300b] = (uint)param_1[6];
              if ((int)param_2 < 0xe) {
                iVar14 = 6;
                iVar21 = 7;
              }
              else {
                puVar6[0x1300c] = (uint)param_1[7];
                if ((int)param_2 < 0x10) {
                  iVar14 = 7;
                  iVar21 = 8;
                }
                else {
                  puVar6[0x1300d] = (uint)param_1[8];
                  if ((int)param_2 < 0x12) {
                    iVar14 = 8;
                    iVar21 = 9;
                  }
                  else {
                    puVar6[0x1300e] = (uint)param_1[9];
                    if ((int)param_2 < 0x14) {
                      iVar14 = 9;
                      iVar21 = 10;
                    }
                    else {
                      puVar6[0x1300f] = (uint)param_1[10];
                      if ((int)param_2 < 0x16) {
                        iVar14 = 10;
                        iVar21 = 0xb;
                      }
                      else {
                        puVar6[0x13010] = (uint)param_1[0xb];
                        if ((int)param_2 < 0x18) {
                          iVar14 = 0xb;
                          iVar21 = 0xc;
                        }
                        else {
                          puVar6[0x13011] = (uint)param_1[0xc];
                          if ((int)param_2 < 0x1a) {
                            iVar14 = 0xc;
                            iVar21 = 0xd;
                          }
                          else {
                            puVar6[0x13012] = (uint)param_1[0xd];
                            if ((int)param_2 < 0x1c) {
                              iVar14 = 0xd;
                              iVar21 = 0xe;
                            }
                            else {
                              puVar6[0x13013] = (uint)param_1[0xe];
                              if ((int)param_2 < 0x1e) {
                                iVar14 = 0xe;
                                iVar21 = 0xf;
                              }
                              else {
                                puVar6[0x13014] = (uint)param_1[0xf];
                                if ((int)param_2 < 0x20) {
                                  iVar14 = 0xf;
                                  iVar21 = 0x10;
                                }
                                else {
                                  iVar14 = 0x10;
                                  if (0x21 < (int)param_2) {
                                    iVar14 = 0x11;
                                  }
                                  puVar6[0x13015] = (uint)param_1[0x10];
                                  iVar21 = 0x11;
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  uVar19 = 0x11;
  Aska::ShaderComprssionTree::InsertNode(int, int)(puVar6,0,0x11);
  uVar18 = 0;
  uStack_b4 = 1;
  uStack_b0 = 1;
  iStack_cc = 0;
  iVar2 = iVar14;
  puStack_c8 = param_3;
  do {
    iVar7 = puVar6[1];
    iVar20 = (int)uVar3 >> 1;
    iVar17 = iVar14;
    if (iVar7 <= iVar14) {
      iVar17 = iVar7;
    }
    iVar4 = iVar2 + iVar17 + -0x10;
    if (iVar20 <= iVar4) {
      iVar17 = iVar20 - iVar2;
    }
    if ((iVar14 < iVar7) || (iVar20 <= iVar4)) {
      puVar6[1] = iVar17;
      if (1 < iVar17) goto code_r0x022c72fc;
code_r0x022c72c8:
      iVar17 = 1;
      puVar6[1] = 1;
      uVar9 = (ushort)puVar6[(long)(int)uVar18 + 0x13005];
      auStack_a8[0] = auStack_a8[0] | (ushort)uStack_b4;
    }
    else {
      if (iVar17 < 2) goto code_r0x022c72c8;
code_r0x022c72fc:
      uVar9 = (short)iVar17 * 0x1000 + 0xe000U | (short)uVar18 - (short)*puVar6 & 0xfffU;
    }
    uVar1 = uStack_b0 + 1;
    auStack_a8[(int)uStack_b0] = uVar9;
    if ((uStack_b4 << 1 & 0xfffe) == 0) {
      if ((int)uStack_b0 < 0) {
        auStack_a8[0] = 0;
code_r0x022c7420:
        iStack_cc = iStack_cc + uVar1;
        auStack_a8[0] = 0;
        uStack_b0 = 1;
        uStack_b4 = 1;
        goto code_r0x022c7430;
      }
      uVar11 = (ulong)uStack_b0;
      uVar13 = (ulong)uVar1;
      puVar15 = puStack_c8;
      if (uVar1 < 0x10) {
code_r0x022c7380:
        lVar8 = 0;
code_r0x022c73d8:
        lVar12 = uVar13 - lVar8;
        puVar16 = auStack_a8 + lVar8;
        do {
          lVar12 = lVar12 + -1;
          *puVar15 = *puVar16;
          puVar15 = puVar15 + 1;
          puVar16 = puVar16 + 1;
        } while (lVar12 != 0);
      }
      else {
        lVar8 = uVar13 - (uVar1 & 0xf);
        if (lVar8 == 0) goto code_r0x022c73d8;
        if ((puStack_c8 < auStack_a8 + uVar13) && (auStack_a8 < puStack_c8 + uVar13))
        goto code_r0x022c7380;
        puVar15 = puStack_c8 + 8;
        lVar12 = lVar8;
        puVar10 = auStack_a0 + 1;
        do {
          puVar5 = puVar10 + -1;
          uVar22 = puVar10[-2];
          uVar24 = puVar10[1];
          uVar23 = *puVar10;
          lVar12 = lVar12 + -0x10;
          puVar10 = puVar10 + 4;
          *(undefined8 *)(puVar15 + -4) = *puVar5;
          *(undefined8 *)(puVar15 + -8) = uVar22;
          *(undefined8 *)(puVar15 + 4) = uVar24;
          *(undefined8 *)puVar15 = uVar23;
          puVar15 = puVar15 + 0x10;
        } while (lVar12 != 0);
        puVar15 = puStack_c8 + lVar8;
        if ((uVar1 & 0xf) != 0) goto code_r0x022c73d8;
      }
      uStack_b0 = 1;
      auStack_a8[0] = 0;
      puStack_c8 = puStack_c8 + uVar11 + 1;
      if (0 < iVar17) goto code_r0x022c7420;
      iVar7 = 0;
      uStack_b4 = 1;
      iStack_cc = iStack_cc + uVar1;
    }
    else {
      uStack_b4 = uStack_b4 << 1 & 0x1fffe;
      uStack_b0 = uVar1;
code_r0x022c7430:
      uVar11 = 0;
      do {
        uVar13 = uVar11;
        if ((long)((ulong)uVar3 << 0x20) >> 0x21 <= (long)((long)iVar21 + uVar13)) {
          uVar11 = uVar13 & 0xffffffff;
          break;
        }
        uVar9 = param_1[(long)iVar21 + uVar13];
        Aska::ShaderComprssionTree::DeleteNode(int)(puVar6,uVar19);
        uVar18 = uVar18 + 1 & 0xfff;
        puVar6[(long)(int)uVar19 + 0x13005] = (uint)uVar9;
        uVar19 = uVar19 + 1 & 0xfff;
        Aska::ShaderComprssionTree::InsertNode(int, int)(puVar6,uVar18,0x11);
        uVar11 = uVar13 + 1;
      } while ((int)uVar11 < iVar17);
      iVar7 = (int)uVar11;
      iVar21 = iVar21 + (int)uVar13 + 1;
    }
    iVar2 = iVar7 + iVar2;
    if (iVar7 < iVar17) {
      iVar17 = iVar17 - iVar7;
      do {
        Aska::ShaderComprssionTree::DeleteNode(int)(puVar6,uVar19);
        iVar14 = iVar14 + -1;
        uVar19 = uVar19 + 1 & 0xfff;
        uVar18 = uVar18 + 1 & 0xfff;
        if (iVar14 != 0) {
          Aska::ShaderComprssionTree::InsertNode(int, int)(puVar6,uVar18,0x11);
        }
        iVar17 = iVar17 + -1;
      } while (iVar17 != 0);
    }
  } while (0 < iVar14);
  auStack_a8[(int)uStack_b0] = 0;
  if ((int)uStack_b0 < 1) goto code_r0x022c75d0;
  uStack_b0 = uStack_b0 + 1;
  uVar11 = (ulong)uStack_b0;
  if (uStack_b0 < 0x10) {
code_r0x022c7564:
    lVar8 = 0;
code_r0x022c75b0:
    lVar12 = uVar11 - lVar8;
    puVar15 = auStack_a8 + lVar8;
    do {
      lVar12 = lVar12 + -1;
      *puStack_c8 = *puVar15;
      puStack_c8 = puStack_c8 + 1;
      puVar15 = puVar15 + 1;
    } while (lVar12 != 0);
  }
  else {
    lVar8 = uVar11 - (uStack_b0 & 0xf);
    if (lVar8 == 0) goto code_r0x022c75b0;
    if ((puStack_c8 < auStack_a8 + uVar11) && (auStack_a8 < puStack_c8 + uVar11))
    goto code_r0x022c7564;
    puVar10 = auStack_a0 + 1;
    puVar15 = puStack_c8 + 8;
    lVar12 = lVar8;
    do {
      puVar5 = puVar10 + -1;
      uVar22 = puVar10[-2];
      uVar24 = puVar10[1];
      uVar23 = *puVar10;
      lVar12 = lVar12 + -0x10;
      puVar10 = puVar10 + 4;
      *(undefined8 *)(puVar15 + -4) = *puVar5;
      *(undefined8 *)(puVar15 + -8) = uVar22;
      *(undefined8 *)(puVar15 + 4) = uVar24;
      *(undefined8 *)puVar15 = uVar23;
      puVar15 = puVar15 + 0x10;
    } while (lVar12 != 0);
    puStack_c8 = puStack_c8 + lVar8;
    if ((uStack_b0 & 0xf) != 0) goto code_r0x022c75b0;
  }
  iStack_cc = uStack_b0 + iStack_cc;
code_r0x022c75d0:
  operator delete(void*)(puVar6);
  return iStack_cc << 1;
}

// ==== Aska::ShaderCompression::DecompressLZwordDic(unsigned short*, unsigned short*, unsigned char*)
// vaddr 0x21c75fc | ghidra 0x22c75fc | size 544 | symbol _ZN4Aska17ShaderCompression19DecompressLZwordDicEPtS1_Ph | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska17ShaderCompression19DecompressLZwordDicEPtS1_Ph
               (byte *param_1,undefined8 *param_2,long param_3)

{
  byte *pbVar1;
  uint uVar2;
  long lVar3;
  undefined8 *puVar4;
  byte bVar5;
  ulong uVar6;
  undefined8 *puVar7;
  long lVar8;
  uint uVar9;
  undefined8 *puVar10;
  int iVar11;
  ulong uVar12;
  uint uVar13;
  int iVar14;
  undefined8 *puVar15;
  undefined2 *puVar16;
  ulong uVar17;
  long lVar18;
  undefined8 uVar19;
  undefined8 uVar20;
  undefined8 uVar21;
  
  lVar3 = param_3 + 0x2000;
  puVar10 = param_2;
code_r0x022c7644:
  bVar5 = *param_1;
  pbVar1 = param_1 + 1;
  param_1 = param_1 + 2;
  uVar9 = (uint)CONCAT11(bVar5,*pbVar1);
  iVar11 = 0x10;
  if ((*pbVar1 & 1) != 0) goto code_r0x022c7628;
  do {
    uVar13 = (uint)param_1[1] | (*param_1 & 0xf) << 8;
    uVar6 = (ulong)uVar13;
    if (uVar13 == 0) {
      return;
    }
    bVar5 = *param_1 >> 4;
    uVar2 = bVar5 + 2;
    uVar17 = (ulong)uVar2;
    puVar15 = (undefined8 *)((long)puVar10 + (ulong)uVar13 * -2);
    uVar13 = (uint)bVar5;
    if (param_2 < (undefined8 *)((long)puVar15 + uVar17 * 2)) {
      uVar12 = (ulong)(bVar5 + 1);
      if (puVar15 < param_2) {
        puVar15 = puVar10;
        do {
          puVar7 = (undefined8 *)((long)puVar15 + uVar6 * -2);
          if (puVar7 < param_2) {
            puVar7 = (undefined8 *)(lVar3 - ((long)param_2 - (long)puVar7));
          }
          uVar13 = (int)uVar17 - 1;
          uVar17 = (ulong)uVar13;
          *(undefined2 *)puVar15 = *(undefined2 *)puVar7;
          puVar15 = (undefined8 *)((long)puVar15 + 2);
        } while (uVar13 != 0);
      }
      else {
        uVar2 = uVar13 + 2;
        puVar7 = puVar10;
        if (uVar2 < 0x10) {
code_r0x022c7750:
          lVar18 = 0;
        }
        else {
          lVar18 = (ulong)uVar2 - (ulong)(uVar2 & 0xf);
          if (lVar18 != 0) {
            if ((puVar10 < (undefined8 *)((long)puVar10 + (bVar5 - uVar6) * 2 + 4)) &&
               (puVar15 < (undefined8 *)((long)puVar10 + (ulong)uVar13 * 2 + 4)))
            goto code_r0x022c7750;
            puVar15 = (undefined8 *)((long)puVar15 + lVar18 * 2);
            lVar8 = lVar18;
            do {
              puVar4 = (undefined8 *)(uVar6 * -2 + (long)puVar7);
              uVar19 = *puVar4;
              uVar21 = puVar4[3];
              uVar20 = puVar4[2];
              lVar8 = lVar8 + -0x10;
              puVar7[1] = puVar4[1];
              *puVar7 = uVar19;
              puVar7[3] = uVar21;
              puVar7[2] = uVar20;
              puVar7 = puVar7 + 4;
            } while (lVar8 != 0);
            puVar7 = (undefined8 *)((long)puVar10 + lVar18 * 2);
            if ((uVar2 & 0xf) == 0) goto code_r0x022c7800;
          }
        }
        iVar14 = uVar2 - (int)lVar18;
        do {
          iVar14 = iVar14 + -1;
          *(undefined2 *)puVar7 = *(undefined2 *)puVar15;
          puVar7 = (undefined8 *)((long)puVar7 + 2);
          puVar15 = (undefined8 *)((long)puVar15 + 2);
        } while (iVar14 != 0);
      }
    }
    else {
      lVar18 = (long)param_2 - (long)puVar15;
      puVar16 = (undefined2 *)(lVar3 - lVar18);
      uVar12 = (ulong)(bVar5 + 1);
      puVar15 = puVar10;
      if (uVar2 < 0x10) {
code_r0x022c770c:
        lVar8 = 0;
      }
      else {
        lVar8 = uVar17 - (uVar2 & 0xf);
        if (lVar8 != 0) {
          if ((puVar10 < (undefined8 *)(param_3 + 0x2004 + ((ulong)bVar5 * 2 - lVar18))) &&
             ((ulong)(lVar3 + (lVar18 >> 1) * -2) < (long)puVar10 + (ulong)uVar13 * 2 + 4))
          goto code_r0x022c770c;
          puVar15 = puVar10 + 2;
          puVar16 = puVar16 + lVar8;
          puVar7 = (undefined8 *)(param_3 + 0x2010 + (lVar18 >> 1) * -2);
          lVar18 = lVar8;
          do {
            puVar4 = puVar7 + -1;
            uVar19 = puVar7[-2];
            uVar21 = puVar7[1];
            uVar20 = *puVar7;
            lVar18 = lVar18 + -0x10;
            puVar7 = puVar7 + 4;
            puVar15[-1] = *puVar4;
            puVar15[-2] = uVar19;
            puVar15[1] = uVar21;
            *puVar15 = uVar20;
            puVar15 = puVar15 + 4;
          } while (lVar18 != 0);
          puVar15 = (undefined8 *)((long)puVar10 + lVar8 * 2);
          if ((uVar2 & 0xf) == 0) goto code_r0x022c7800;
        }
      }
      iVar14 = (bVar5 + 2) - (int)lVar8;
      do {
        iVar14 = iVar14 + -1;
        *(undefined2 *)puVar15 = *puVar16;
        puVar16 = puVar16 + 1;
        puVar15 = (undefined8 *)((long)puVar15 + 2);
      } while (iVar14 != 0);
    }
code_r0x022c7800:
    puVar10 = (undefined8 *)((long)puVar10 + uVar12 * 2 + 2);
    while( true ) {
      iVar11 = iVar11 + -1;
      param_1 = param_1 + 2;
      if (iVar11 == 0) goto code_r0x022c7644;
      uVar9 = (int)uVar9 >> 1;
      if ((uVar9 & 1) == 0) break;
code_r0x022c7628:
      *(undefined2 *)puVar10 = *(undefined2 *)param_1;
      puVar10 = (undefined8 *)((long)puVar10 + 2);
    }
  } while( true );
}

// ==== Aska::ShaderCompression::CompressLZwordDic(void*, int, void*, unsigned char*)
// vaddr 0x21c781c | ghidra 0x22c781c | size 2000 | symbol _ZN4Aska17ShaderCompression17CompressLZwordDicEPviS1_Ph | lib libSOA-3.7.0.so | 2026-10-04
int _ZN4Aska17ShaderCompression17CompressLZwordDicEPviS1_Ph
              (undefined1 *param_1,uint param_2,ushort *param_3,long param_4)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  undefined1 uVar4;
  undefined1 uVar5;
  int iVar6;
  undefined4 *puVar7;
  int iVar8;
  long lVar9;
  ulong uVar10;
  ushort uVar11;
  undefined8 *puVar12;
  long lVar13;
  ulong uVar14;
  int iVar15;
  ushort *puVar16;
  ushort *puVar17;
  int iVar18;
  uint uVar19;
  uint uVar20;
  int iVar21;
  undefined1 *puVar22;
  int iVar23;
  undefined8 uVar24;
  undefined8 uVar25;
  undefined8 uVar26;
  undefined8 uVar27;
  int iStack_cc;
  ushort *puStack_c8;
  uint uStack_b4;
  uint uStack_b0;
  ushort auStack_a8 [4];
  undefined8 auStack_a0 [8];
  
  puVar7 = (undefined4 *)operator new(unsigned long, std::nothrow_t const&)(0x50058,PTR__ZSt7nothrow_02cb9a80);
  if (puVar7 == (undefined4 *)0x0) {
    return 0;
  }
  lVar9 = 0x10000;
  puVar12 = (undefined8 *)(puVar7 + 0x3009);
  do {
    puVar12[-1] = 0x100000001000;
    puVar12[-2] = 0x100000001000;
    puVar12[1] = 0x100000001000;
    *puVar12 = 0x100000001000;
    lVar9 = lVar9 + -8;
    puVar12 = puVar12 + 4;
    lVar13 = 0;
  } while (lVar9 != 0);
  do {
    lVar9 = lVar13 + 0x20;
    *(undefined8 *)((long)puVar7 + lVar13 + 0x10) = 0x100000001000;
    *(undefined8 *)((long)puVar7 + lVar13 + 8) = 0x100000001000;
    *(undefined8 *)((long)puVar7 + lVar13 + 0x20) = 0x100000001000;
    *(undefined8 *)((long)puVar7 + lVar13 + 0x18) = 0x100000001000;
    lVar13 = lVar9;
  } while (lVar9 != 0x4000);
  lVar9 = 0;
  lVar13 = 0x4c014;
  auStack_a8[0] = 0;
  do {
    puVar22 = (undefined1 *)(param_4 + lVar9);
    lVar9 = lVar9 + 2;
    *(uint *)((long)puVar7 + lVar13) = (uint)CONCAT11(*puVar22,puVar22[1]);
    lVar13 = lVar13 + 4;
  } while (lVar9 != 0x2000);
  iVar18 = 0x11;
  do {
    Aska::ShaderComprssionTree::InsertNode(int, int)(puVar7,iVar18,0x11);
    iVar18 = iVar18 + 1;
  } while (iVar18 != 0x1000);
  uVar3 = param_2;
  if ((int)param_2 < 0) {
    uVar3 = param_2 + 1;
  }
  puVar7[0x13005] = (uint)CONCAT11(*param_1,param_1[1]);
  if ((int)param_2 < 2) {
    iVar15 = 0;
    iVar18 = 1;
  }
  else {
    puVar7[0x13006] = (uint)CONCAT11(param_1[2],param_1[3]);
    if ((int)param_2 < 4) {
      iVar15 = 1;
      iVar18 = 2;
    }
    else {
      puVar7[0x13007] = (uint)CONCAT11(param_1[4],param_1[5]);
      if ((int)param_2 < 6) {
        iVar15 = 2;
        iVar18 = 3;
      }
      else {
        puVar7[0x13008] = (uint)CONCAT11(param_1[6],param_1[7]);
        if ((int)param_2 < 8) {
          iVar15 = 3;
          iVar18 = 4;
        }
        else {
          puVar7[0x13009] = (uint)CONCAT11(param_1[8],param_1[9]);
          if ((int)param_2 < 10) {
            iVar15 = 4;
            iVar18 = 5;
          }
          else {
            puVar7[0x1300a] = (uint)CONCAT11(param_1[10],param_1[0xb]);
            if ((int)param_2 < 0xc) {
              iVar15 = 5;
              iVar18 = 6;
            }
            else {
              puVar7[0x1300b] = (uint)CONCAT11(param_1[0xc],param_1[0xd]);
              if ((int)param_2 < 0xe) {
                iVar15 = 6;
                iVar18 = 7;
              }
              else {
                puVar7[0x1300c] = (uint)CONCAT11(param_1[0xe],param_1[0xf]);
                if ((int)param_2 < 0x10) {
                  iVar15 = 7;
                  iVar18 = 8;
                }
                else {
                  puVar7[0x1300d] = (uint)CONCAT11(param_1[0x10],param_1[0x11]);
                  if ((int)param_2 < 0x12) {
                    iVar15 = 8;
                    iVar18 = 9;
                  }
                  else {
                    puVar7[0x1300e] = (uint)CONCAT11(param_1[0x12],param_1[0x13]);
                    if ((int)param_2 < 0x14) {
                      iVar15 = 9;
                      iVar18 = 10;
                    }
                    else {
                      puVar7[0x1300f] = (uint)CONCAT11(param_1[0x14],param_1[0x15]);
                      if ((int)param_2 < 0x16) {
                        iVar15 = 10;
                        iVar18 = 0xb;
                      }
                      else {
                        puVar7[0x13010] = (uint)CONCAT11(param_1[0x16],param_1[0x17]);
                        if ((int)param_2 < 0x18) {
                          iVar15 = 0xb;
                          iVar18 = 0xc;
                        }
                        else {
                          puVar7[0x13011] = (uint)CONCAT11(param_1[0x18],param_1[0x19]);
                          if ((int)param_2 < 0x1a) {
                            iVar15 = 0xc;
                            iVar18 = 0xd;
                          }
                          else {
                            puVar7[0x13012] = (uint)CONCAT11(param_1[0x1a],param_1[0x1b]);
                            if ((int)param_2 < 0x1c) {
                              iVar15 = 0xd;
                              iVar18 = 0xe;
                            }
                            else {
                              puVar7[0x13013] = (uint)CONCAT11(param_1[0x1c],param_1[0x1d]);
                              if ((int)param_2 < 0x1e) {
                                iVar15 = 0xe;
                                iVar18 = 0xf;
                              }
                              else {
                                puVar7[0x13014] = (uint)CONCAT11(param_1[0x1e],param_1[0x1f]);
                                if ((int)param_2 < 0x20) {
                                  iVar15 = 0xf;
                                  iVar18 = 0x10;
                                }
                                else {
                                  iVar15 = 0x10;
                                  if (0x21 < (int)param_2) {
                                    iVar15 = 0x11;
                                  }
                                  puVar7[0x13015] = (uint)CONCAT11(param_1[0x20],param_1[0x21]);
                                  iVar18 = 0x11;
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  uVar20 = 0x11;
  Aska::ShaderComprssionTree::InsertNode(int, int)(puVar7,0,0x11);
  uVar19 = 0;
  uStack_b4 = 1;
  uStack_b0 = 1;
  iStack_cc = 0;
  iVar2 = iVar15;
  puStack_c8 = param_3;
  do {
    iVar8 = puVar7[1];
    iVar21 = (int)uVar3 >> 1;
    iVar23 = iVar15;
    if (iVar8 <= iVar15) {
      iVar23 = iVar8;
    }
    iVar6 = iVar2 + iVar23 + -0x10;
    if (iVar21 <= iVar6) {
      iVar23 = iVar21 - iVar2;
    }
    if ((iVar15 < iVar8) || (iVar21 <= iVar6)) {
      puVar7[1] = iVar23;
      if (1 < iVar23) goto code_r0x022c7c9c;
code_r0x022c7c68:
      iVar23 = 1;
      puVar7[1] = 1;
      uVar11 = (ushort)puVar7[(long)(int)uVar19 + 0x13005];
      auStack_a8[0] = auStack_a8[0] | (ushort)uStack_b4;
    }
    else {
      if (iVar23 < 2) goto code_r0x022c7c68;
code_r0x022c7c9c:
      uVar11 = (short)iVar23 * 0x1000 + 0xe000U | (short)uVar19 - (short)*puVar7 & 0xfffU;
    }
    uVar1 = uStack_b0 + 1;
    auStack_a8[(int)uStack_b0] = uVar11;
    if ((uStack_b4 << 1 & 0xfffe) == 0) {
      if ((int)uStack_b0 < 0) {
        auStack_a8[0] = 0;
code_r0x022c7de4:
        iStack_cc = uVar1 + iStack_cc;
        auStack_a8[0] = 0;
        uStack_b0 = 1;
        uStack_b4 = 1;
        goto code_r0x022c7df4;
      }
      uVar10 = (ulong)uStack_b0;
      uVar14 = (ulong)uVar1;
      puVar16 = puStack_c8;
      if (uVar1 < 0x10) {
code_r0x022c7d20:
        lVar9 = 0;
code_r0x022c7d90:
        lVar13 = uVar14 - lVar9;
        puVar17 = auStack_a8 + lVar9;
        do {
          lVar13 = lVar13 + -1;
          *(undefined1 *)puVar16 = *(undefined1 *)((long)puVar17 + 1);
          *(char *)((long)puVar16 + 1) = (char)*puVar17;
          puVar16 = puVar16 + 1;
          puVar17 = puVar17 + 1;
        } while (lVar13 != 0);
      }
      else {
        lVar9 = uVar14 - (uVar1 & 0xf);
        if (lVar9 == 0) goto code_r0x022c7d90;
        if ((puStack_c8 < auStack_a8 + uVar14) && (auStack_a8 < puStack_c8 + uVar14))
        goto code_r0x022c7d20;
        puVar16 = puStack_c8 + 8;
        lVar13 = lVar9;
        puVar12 = auStack_a0 + 1;
        do {
          uVar25 = puVar12[-1];
          uVar24 = puVar12[-2];
          uVar27 = puVar12[1];
          uVar26 = *puVar12;
          lVar13 = lVar13 + -0x10;
          puVar12 = puVar12 + 4;
          *(char *)(puVar16 + -8) = (char)((ulong)uVar24 >> 8);
          *(char *)((long)puVar16 + -0xf) = (char)uVar24;
          *(char *)(puVar16 + -7) = (char)((ulong)uVar24 >> 0x18);
          *(char *)((long)puVar16 + -0xd) = (char)((ulong)uVar24 >> 0x10);
          *(char *)(puVar16 + -6) = (char)((ulong)uVar24 >> 0x28);
          *(char *)((long)puVar16 + -0xb) = (char)((ulong)uVar24 >> 0x20);
          *(char *)(puVar16 + -5) = (char)((ulong)uVar24 >> 0x38);
          *(char *)((long)puVar16 + -9) = (char)((ulong)uVar24 >> 0x30);
          *(char *)(puVar16 + -4) = (char)((ulong)uVar25 >> 8);
          *(char *)((long)puVar16 + -7) = (char)uVar25;
          *(char *)(puVar16 + -3) = (char)((ulong)uVar25 >> 0x18);
          *(char *)((long)puVar16 + -5) = (char)((ulong)uVar25 >> 0x10);
          *(char *)(puVar16 + -2) = (char)((ulong)uVar25 >> 0x28);
          *(char *)((long)puVar16 + -3) = (char)((ulong)uVar25 >> 0x20);
          *(char *)(puVar16 + -1) = (char)((ulong)uVar25 >> 0x38);
          *(char *)((long)puVar16 + -1) = (char)((ulong)uVar25 >> 0x30);
          *(char *)puVar16 = (char)((ulong)uVar26 >> 8);
          *(char *)((long)puVar16 + 1) = (char)uVar26;
          *(char *)(puVar16 + 1) = (char)((ulong)uVar26 >> 0x18);
          *(char *)((long)puVar16 + 3) = (char)((ulong)uVar26 >> 0x10);
          *(char *)(puVar16 + 2) = (char)((ulong)uVar26 >> 0x28);
          *(char *)((long)puVar16 + 5) = (char)((ulong)uVar26 >> 0x20);
          *(char *)(puVar16 + 3) = (char)((ulong)uVar26 >> 0x38);
          *(char *)((long)puVar16 + 7) = (char)((ulong)uVar26 >> 0x30);
          *(char *)(puVar16 + 4) = (char)((ulong)uVar27 >> 8);
          *(char *)((long)puVar16 + 9) = (char)uVar27;
          *(char *)(puVar16 + 5) = (char)((ulong)uVar27 >> 0x18);
          *(char *)((long)puVar16 + 0xb) = (char)((ulong)uVar27 >> 0x10);
          *(char *)(puVar16 + 6) = (char)((ulong)uVar27 >> 0x28);
          *(char *)((long)puVar16 + 0xd) = (char)((ulong)uVar27 >> 0x20);
          *(char *)(puVar16 + 7) = (char)((ulong)uVar27 >> 0x38);
          *(char *)((long)puVar16 + 0xf) = (char)((ulong)uVar27 >> 0x30);
          puVar16 = puVar16 + 0x10;
        } while (lVar13 != 0);
        puVar16 = puStack_c8 + lVar9;
        if ((uVar1 & 0xf) != 0) goto code_r0x022c7d90;
      }
      uStack_b0 = 1;
      auStack_a8[0] = 0;
      puStack_c8 = puStack_c8 + uVar10 + 1;
      if (0 < iVar23) goto code_r0x022c7de4;
      iVar8 = 0;
      uStack_b4 = 1;
      iStack_cc = uVar1 + iStack_cc;
    }
    else {
      uStack_b4 = uStack_b4 << 1 & 0x1fffe;
      uStack_b0 = uVar1;
code_r0x022c7df4:
      uVar10 = 0;
      puVar22 = param_1 + (long)iVar18 * 2 + 1;
      do {
        uVar14 = uVar10;
        if ((long)((ulong)uVar3 << 0x20) >> 0x21 <= (long)((long)iVar18 + uVar14)) {
          uVar10 = uVar14 & 0xffffffff;
          break;
        }
        uVar5 = puVar22[-1];
        uVar4 = *puVar22;
        Aska::ShaderComprssionTree::DeleteNode(int)(puVar7,uVar20);
        uVar19 = uVar19 + 1 & 0xfff;
        puVar7[(long)(int)uVar20 + 0x13005] = (uint)CONCAT11(uVar5,uVar4);
        uVar20 = uVar20 + 1 & 0xfff;
        Aska::ShaderComprssionTree::InsertNode(int, int)(puVar7,uVar19,0x11);
        uVar10 = uVar14 + 1;
        puVar22 = puVar22 + 2;
      } while ((int)uVar10 < iVar23);
      iVar8 = (int)uVar10;
      iVar18 = iVar18 + (int)uVar14 + 1;
    }
    iVar2 = iVar8 + iVar2;
    if (iVar8 < iVar23) {
      iVar23 = iVar23 - iVar8;
      do {
        Aska::ShaderComprssionTree::DeleteNode(int)(puVar7,uVar20);
        iVar15 = iVar15 + -1;
        uVar20 = uVar20 + 1 & 0xfff;
        uVar19 = uVar19 + 1 & 0xfff;
        if (iVar15 != 0) {
          Aska::ShaderComprssionTree::InsertNode(int, int)(puVar7,uVar19,0x11);
        }
        iVar23 = iVar23 + -1;
      } while (iVar23 != 0);
    }
  } while (0 < iVar15);
  auStack_a8[(int)uStack_b0] = 0;
  if ((int)uStack_b0 < 1) goto code_r0x022c7fc0;
  uVar3 = uStack_b0 + 1;
  uVar10 = (ulong)uVar3;
  if (uVar3 < 0x10) {
code_r0x022c7f2c:
    lVar9 = 0;
code_r0x022c7f90:
    lVar13 = uVar10 - lVar9;
    puVar16 = auStack_a8 + lVar9;
    do {
      lVar13 = lVar13 + -1;
      *(undefined1 *)puStack_c8 = *(undefined1 *)((long)puVar16 + 1);
      *(char *)((long)puStack_c8 + 1) = (char)*puVar16;
      puStack_c8 = puStack_c8 + 1;
      puVar16 = puVar16 + 1;
    } while (lVar13 != 0);
  }
  else {
    lVar9 = uVar10 - (uVar3 & 0xf);
    if (lVar9 == 0) goto code_r0x022c7f90;
    if ((puStack_c8 < auStack_a8 + uVar10) && (auStack_a8 < puStack_c8 + uVar10))
    goto code_r0x022c7f2c;
    puVar12 = auStack_a0 + 1;
    puVar16 = puStack_c8 + 8;
    lVar13 = lVar9;
    do {
      uVar25 = puVar12[-1];
      uVar24 = puVar12[-2];
      uVar27 = puVar12[1];
      uVar26 = *puVar12;
      lVar13 = lVar13 + -0x10;
      puVar12 = puVar12 + 4;
      *(char *)(puVar16 + -8) = (char)((ulong)uVar24 >> 8);
      *(char *)((long)puVar16 + -0xf) = (char)uVar24;
      *(char *)(puVar16 + -7) = (char)((ulong)uVar24 >> 0x18);
      *(char *)((long)puVar16 + -0xd) = (char)((ulong)uVar24 >> 0x10);
      *(char *)(puVar16 + -6) = (char)((ulong)uVar24 >> 0x28);
      *(char *)((long)puVar16 + -0xb) = (char)((ulong)uVar24 >> 0x20);
      *(char *)(puVar16 + -5) = (char)((ulong)uVar24 >> 0x38);
      *(char *)((long)puVar16 + -9) = (char)((ulong)uVar24 >> 0x30);
      *(char *)(puVar16 + -4) = (char)((ulong)uVar25 >> 8);
      *(char *)((long)puVar16 + -7) = (char)uVar25;
      *(char *)(puVar16 + -3) = (char)((ulong)uVar25 >> 0x18);
      *(char *)((long)puVar16 + -5) = (char)((ulong)uVar25 >> 0x10);
      *(char *)(puVar16 + -2) = (char)((ulong)uVar25 >> 0x28);
      *(char *)((long)puVar16 + -3) = (char)((ulong)uVar25 >> 0x20);
      *(char *)(puVar16 + -1) = (char)((ulong)uVar25 >> 0x38);
      *(char *)((long)puVar16 + -1) = (char)((ulong)uVar25 >> 0x30);
      *(char *)puVar16 = (char)((ulong)uVar26 >> 8);
      *(char *)((long)puVar16 + 1) = (char)uVar26;
      *(char *)(puVar16 + 1) = (char)((ulong)uVar26 >> 0x18);
      *(char *)((long)puVar16 + 3) = (char)((ulong)uVar26 >> 0x10);
      *(char *)(puVar16 + 2) = (char)((ulong)uVar26 >> 0x28);
      *(char *)((long)puVar16 + 5) = (char)((ulong)uVar26 >> 0x20);
      *(char *)(puVar16 + 3) = (char)((ulong)uVar26 >> 0x38);
      *(char *)((long)puVar16 + 7) = (char)((ulong)uVar26 >> 0x30);
      *(char *)(puVar16 + 4) = (char)((ulong)uVar27 >> 8);
      *(char *)((long)puVar16 + 9) = (char)uVar27;
      *(char *)(puVar16 + 5) = (char)((ulong)uVar27 >> 0x18);
      *(char *)((long)puVar16 + 0xb) = (char)((ulong)uVar27 >> 0x10);
      *(char *)(puVar16 + 6) = (char)((ulong)uVar27 >> 0x28);
      *(char *)((long)puVar16 + 0xd) = (char)((ulong)uVar27 >> 0x20);
      *(char *)(puVar16 + 7) = (char)((ulong)uVar27 >> 0x38);
      *(char *)((long)puVar16 + 0xf) = (char)((ulong)uVar27 >> 0x30);
      puVar16 = puVar16 + 0x10;
    } while (lVar13 != 0);
    puStack_c8 = puStack_c8 + lVar9;
    if ((uVar3 & 0xf) != 0) goto code_r0x022c7f90;
  }
  iStack_cc = iStack_cc + uStack_b0 + 1;
code_r0x022c7fc0:
  operator delete(void*)(puVar7);
  return iStack_cc << 1;
}
