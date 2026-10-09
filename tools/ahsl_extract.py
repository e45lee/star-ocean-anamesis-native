#!/usr/bin/env -S sh -c 'exec "${0%/*}/py" "$0" "$@"'
"""Decrypt and unpack the AHSL shader disk cache (Shader/AHSLDiskCacheAdd) into GLSL files.

Usage: .venv/bin/python tools/ahsl_extract.py [AHSLDiskCacheAdd] -o OUTDIR [--grep REGEX]
  default input: Shader/AHSLDiskCacheAdd of the 3.7.0 download (work/SOA-3.7.0-canonical-data.zip,
  read in place; --download names another zip or folder); a file path works too (the APK's
  assets/builtin_data copy is the same contents without the ADLD wrapper; both work). Writes OUTDIR/NNNN_{vs,ps}_<key-crc>.glsl
  (one per cache entry, with the constant list as a header comment), OUTDIR/index.tsv and
  OUTDIR/programs.tsv (the linked VS/PS pairs). --grep only writes entries whose source matches REGEX.

Format, from libSOA 3.7.0 (Ghidra addresses):
  ADLD wrapper (flag 1 = XOR) keyed on the name "Shader/AHSLDiskCacheAdd" (soa_save/adld.py).
  File  : "KPHS" (u32 0x5348504b), u16 section count @0xC, sections from 0x2020.
          AHSLCacheManagerV2::RebuildL2Database @021af660.
  Section: u32 crc-ish, u32 size (4-aligned stride), then an AHSLFileCacheHeader (0x2020 bytes):
          magic ("3AHA" = AHSLDISKCACHEMAGIC: shaders; "03LA" = AHSLLINKEDDISKCACHEMAGIC: programs),
          u16 version @8/@10 (must equal the device's), u16 entry count @0xC, and @0x20 an
          8 KiB LZ dictionary (CRC16-checked). Entries follow the header.
  Shader entry (ShaderDiskCache): u16 ?, u16 stored size, u16 unpacked size, u16 info offset,
          u16 ?, u8 flags (&3: 1 LZ, 2 LZword, 3 LZwordDic; bit5 = binds another entry's VS),
          u8 ?, shader key @+0xC. The first (info offset + 48) bytes are stored raw
          (AHSLBase::UncompressShaderCache @021b2fa8; 48 = per-target table @029c5dc0), the rest is
          compressed (ShaderCompression::DecompressLZwordDic @022c75fc; the only mode the 3.7.0 cache uses,
          so lz_bytes/lz_word below are untested transcriptions).
  Info (at info offset): u16 @+0x1a = offset of the code blob from the entry start.
  Code blob (RenderDeviceGL::CreateShaderFromMemory @02275bf8): u32 ?, u32 text offset; +8 is
          the constant list (const_list below); the NUL-terminated GLSL ES 3.00 text is at
          blob+text offset.
  Shader key: ShaderKeyUtil; GetTarget() 0 = vertex, 1 = pixel (BuildLinkedDiskCacheL2 @021ad2a8).
"""
import argparse
import os
import re
import struct
import sys

from soa_save.adld import decode
from soa_save.download_tree import DEFAULT, DownloadTree, open_member_or_file

KPHS = 0x5348504B
NAME = "Shader/AHSLDiskCacheAdd"
INFO_RAW = 48


def lzword_dic(src: bytes, pos: int, dic: bytes, out_len: int) -> bytes:
    """ShaderCompression::DecompressLZwordDic: 16-bit units; a big-endian flag word covers 16
    items, LSB first (1 = literal word, 0 = match). A match is BE: len-2 in the top nibble,
    distance in words in the low 12 bits (0 ends the stream); distances reaching before the
    output read from the end of the 8 KiB dictionary."""
    buf = bytearray(dic)
    base = len(buf)
    while True:
        flags = (src[pos] << 8) | src[pos + 1]
        pos += 2
        for _ in range(16):
            if flags & 1:
                buf += src[pos:pos + 2]
            else:
                b0, b1 = src[pos], src[pos + 1]
                dist = ((b0 & 0xF) << 8) | b1
                if dist == 0:
                    return bytes(buf[base:])
                n = (b0 >> 4) + 2
                for _ in range(n):
                    p = len(buf) - dist * 2
                    buf += buf[p:p + 2]
            pos += 2
            flags >>= 1
            if len(buf) - base >= out_len + 64:
                return bytes(buf[base:])


def lz_bytes(src: bytes, pos: int) -> bytes:  # ShaderCompression::DecompressLZ (flags & 3 == 1)
    out = bytearray()
    while True:
        flags = src[pos]
        pos += 1
        for _ in range(8):
            if flags & 1:
                out.append(src[pos])
                pos += 1
            else:
                dist = src[pos] | ((src[pos + 1] & 0xF) << 8)
                if dist == 0:
                    return bytes(out)
                for _ in range((src[pos + 1] >> 4) + 3):
                    out.append(out[-dist])
                pos += 2
            flags >>= 1


def lz_word(src: bytes, pos: int) -> bytes:  # DecompressLZword (flags & 3 == 2), little-endian
    out = bytearray()
    while True:
        flags = struct.unpack_from("<H", src, pos)[0]
        pos += 2
        for _ in range(16):
            w = struct.unpack_from("<H", src, pos)[0]
            if flags & 1:
                out += src[pos:pos + 2]
            else:
                if w & 0xFFF == 0:
                    return bytes(out)
                for _ in range((w >> 12) + 2):
                    out += out[len(out) - (w & 0xFFF) * 2:len(out) - (w & 0xFFF) * 2 + 2]
            pos += 2
            flags >>= 1


def unpack_entry(d: bytes, e: int, dic: bytes) -> bytes:
    _, stored, unpacked, info = struct.unpack_from("<HHHH", d, e)
    flags = d[e + 10]
    if flags & 3 == 0:
        return d[e:e + unpacked]
    raw = info + INFO_RAW
    if flags & 3 == 3:
        body = lzword_dic(d, e + raw, dic, unpacked - raw)
    elif flags & 3 == 2:
        body = lz_word(d, e + raw)
    else:
        body = lz_bytes(d, e + raw)
    return (d[e:e + raw] + body)[:unpacked]


# Material ("e") constant ids, from the name table at 0x2be89f0 (index = id).
E_NAMES = ["eBlinn_Diffuse_Color", "eBlinn_Ambient_Color", "eSURFACE_SPECULAR_COL", "eBlinn_Translucent_Color",
           "eBlinn_Aniso_Coef", "eConstColor_Color_Color", "eConstVector_Vector_Vector", "eParallax_Offset_Scalar",
           "ePARALLAXOCCLUSION_COEF", "ePARALLAXOCCLUSION_STEP", "ePARALLAXOCCLUSION_SHADOW", "eRateValue",
           "eUVSETTRANS_PARAM", "eUVSETTRANS_MATRIX", "eXYTRANS_PARAM", "eXYTRANS_MATRIX", "eBlinn_Specular2nd_Color",
           "eRateValueVector", "eSoftScale", "eSURFACE_VERTEX_SPECULAR", "eALBEDO_CONSTCOLOR", "eMARSCHNER_COEF",
           "eMARSCHNER_PRECALC", "eENVMAP_COEF", "eREFRACTIVEINDEX", "eRateValueCoef", "eUtilityConst", "eToonCoef",
           "eToonUnit", "eCONSTCOLOR2_", "eCONSTCOLOR3_", "eMAKETRANSUV_MATRIX_", "evHairCoef"]


def const_list(blob: bytes) -> list:
    """The constant list at blob+8 (RenderDeviceData::CreateShaderConstantAssign @0227f424):
    u32 sampler mask, u16 skip (words), u16 count, then from +12+4*skip `count` records of
    {u8 kind (0 engine 'cv', 1 material 'e'), u8 type, u16 registers, u16 id, u16 slot}."""
    c = blob[8:]
    _, skip, count = struct.unpack_from("<IHH", c, 0)
    out, p = [], 12 + 4 * skip
    for _ in range(count):
        kind, typ, regs, cid, slot = struct.unpack_from("<BBHHH", c, p)
        name = (E_NAMES[cid] if cid < len(E_NAMES) else "e#%d" % cid) + str(slot) if kind else "cv#%d" % cid
        out.append((name, kind, cid, regs))
        p += 8
    return out


def main() -> None:
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("input", nargs="?", default=NAME, help="a file, or a member of --download (default Shader/AHSLDiskCacheAdd)")
    ap.add_argument("--download", default=DEFAULT, help="the 3.7.0 download: its zip (default work/SOA-3.7.0-canonical-data.zip) or a folder")
    ap.add_argument("-o", "--out", required=True)
    ap.add_argument("--grep")
    a = ap.parse_args()
    d = decode(open_member_or_file(a.input, DownloadTree.open(a.download) if not os.path.isfile(a.input) else None), NAME)
    if struct.unpack_from("<I", d, 0)[0] != KPHS:
        sys.exit("not a KPHS shader cache")
    os.makedirs(a.out, exist_ok=True)
    nsec = struct.unpack_from("<H", d, 12)[0]
    off = 0x2020
    idx = open(os.path.join(a.out, "index.tsv"), "w")
    idx.write("n\tkind\toffset\tkey_crc\tlines\tuniforms\n")
    n = 0
    for _ in range(nsec):
        size = struct.unpack_from("<I", d, off + 4)[0]
        h = off + 8
        magic = d[h:h + 4]
        count = struct.unpack_from("<H", d, h + 12)[0]
        dic = d[h + 0x20:h + 0x2020]
        e = h + 0x2020
        if magic == b"3AHA":
            for _ in range(count):
                stored = struct.unpack_from("<H", d, e + 2)[0]
                u = unpack_entry(d, e, dic)
                info = struct.unpack_from("<H", u, 6)[0]
                boff = struct.unpack_from("<H", u, info + 0x1A)[0]
                blob = u[boff:]
                toff = struct.unpack_from("<I", blob, 4)[0]
                text = blob[toff:blob.index(b"\0", toff)].decode("latin1")
                consts = const_list(blob)
                kind = "ps" if (d[e + 16] >> 3) & 7 else "vs"  # ShaderKeyUtil::GetTarget
                keycrc = struct.unpack_from("<H", d, e)[0]
                if not a.grep or re.search(a.grep, text):
                    fn = os.path.join(a.out, "%04d_%s_%04x.glsl" % (n, kind, keycrc))
                    with open(fn, "w") as f:
                        f.write("// entry %d @0x%x stored %d unpacked %d flags %d\n" % (n, e, stored, len(u), d[e + 10]))
                        for name, kind_, cid, regs in consts:
                            f.write("// const %s (kind %d id %d, %d regs)\n" % (name, kind_, cid, regs))
                        f.write(text)
                idx.write("%d\t%s\t0x%x\t%04x\t%d\t%s\n" % (n, kind, e, keycrc, text.count("\n"),
                                                         ",".join(c[0] for c in consts)))
                n += 1
                e += stored
        elif magic == b"03LA":
            with open(os.path.join(a.out, "programs.tsv"), "w") as f:
                f.write("n\toffset\tsize\thex\n")
                for i in range(count):
                    sz = struct.unpack_from("<I", d, e + 4)[0]
                    f.write("%d\t0x%x\t%d\t%s\n" % (i, e, sz, d[e:e + sz].hex()))
                    e += (sz + 3) & ~3
        off += (size + 3) & ~3
    print("%d shader entries -> %s" % (n, a.out))


if __name__ == "__main__":
    main()
