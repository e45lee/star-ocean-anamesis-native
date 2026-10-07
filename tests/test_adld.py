"""soa_save.adld's CHash32 (zlib.crc32 underneath) and key packing against the bit-by-bit
definitions they replaced, ADLD and SLZ (soa_save.slz) round trips, and soa_save.kvs's Base64
layouts and XML reading."""
import base64
import random
import struct
import zlib

import pytest

from soa_save import adld, kvs, slz


def chash32_reference(s: bytes) -> int:
    """Framework::CHash32 as the guest computes it: reflected CRC-32 (0xEDB88320), bit by bit,
    the register seeded with the length, no final xor."""
    c = len(s)
    for b in s:
        c ^= b
        for _ in range(8):
            c = (c >> 1) ^ (0xEDB88320 if c & 1 else 0)
    return c


def digits16_reference(s: str) -> bytes:
    out = bytearray(16)
    for i, ch in enumerate(s):
        out[i // 2] |= int(ch) << 4 if i % 2 == 0 else int(ch)
    return bytes(out)


def inputs():
    rng = random.Random(1)
    yield from (b"", b"\0", b"\xff" * 300, b"sqlite/basmaster.sqlite3", b"Image/etc2/u_chip_cp0001.aif")
    for _ in range(2000):
        yield bytes(rng.randrange(256) for _ in range(rng.randrange(0, 80)))


def test_chash32_matches_the_bitwise_definition():
    for s in inputs():
        assert adld.chash32(s) == chash32_reference(s), s
    assert adld.chash32(b"role_cc0050_b01a_6073") == 7715287


def test_key_packing():
    rng = random.Random(2)
    for _ in range(500):
        d = "%032u" % rng.randrange(2 ** 32)
        assert adld.digits16(d) == digits16_reference(d)
    assert adld.IV == digits16_reference("09375711857134629684891855841614")


def test_decode_xor_and_aes():
    from Crypto.Cipher import AES
    name = "Script/1000_010.msgp"
    plain = bytes(range(256)) * 3
    k = b"%x" % chash32_reference(name.encode())
    xored = b"ADLD" + struct.pack("<I", 1) + bytes(8) + bytes(b ^ k[i % len(k)] for i, b in enumerate(plain))
    assert adld.decode(xored, name) == plain
    key = digits16_reference("%032u" % chash32_reference(name.encode()))
    dcne = b"DCNE" + struct.pack("<II", 1, 16 + len(plain)) + bytes(4) + plain
    dcne += bytes(-len(dcne) % 16)
    aes = b"ADLD" + struct.pack("<I", 2) + bytes(8) + AES.new(key, AES.MODE_CBC, adld.IV).encrypt(dcne)
    assert adld.decode(aes, name) == plain
    assert adld.decode(b"not ADLD", name) == b"not ADLD"
    # encode is the inverse, byte for byte the files above (soa::adld::encrypt's layout)
    assert adld.encode(plain, name) == xored and adld.encode(plain, name, adld.AES) == aes
    assert adld.encode(plain, name, 0) == b"ADLD" + bytes(12) + plain


def test_xor_in_pieces():
    name = "Image/etc2/u_chip_cp0001.aif"
    plain = bytes(range(256)) * 41
    whole = adld.xor(plain, name)
    assert adld.xor(whole, name) == plain and adld.xor(b"", name) == b""
    for cut in (1, 7, 8, 1000, len(plain) - 1):  # (a payload XORed in pieces: the key continues)
        assert adld.xor(plain[:cut], name) + adld.xor(plain[cut:], name, cut) == whole


def slz_reference(raw_chunks, codec, size, chunk_kib):
    """An SLZ file of the given chunk bodies (each already u16-size-prefixed unless codec 0)."""
    payload = b"".join(raw_chunks)
    return struct.pack("<3sBBBHiiIIBBHI", b"SLZ", codec, 0, 1, 0x25, len(payload), size, 0, 0x20, 1, chunk_kib, 0x10, 0) + payload


def test_slz_round_trips_and_rules():
    rng = random.Random(3)
    for n in (0, 1, 100, 65536, 65537, 200000):
        plain = bytes(rng.randrange(256) for _ in range(n)) if n > 100000 else bytes(i // 7 & 0xff for i in range(n))
        enc = slz.encode(plain)
        assert enc[:4] == b"SLZ\x05" and len(enc) % 4 == 0 and slz.decode(enc) == plain, n
    assert slz.decode(b"not SLZ") == b"not SLZ"
    # codec 0 (stored, no size fields), and a size-0 (stored) chunk in a codec-5 file
    assert slz.decode(slz_reference([b"abcdef"], 0, 6, 0)) == b"abcdef"
    co = zlib.compressobj(9, zlib.DEFLATED, -15)
    z = co.compress(b"x" * 1024) + co.flush()
    f = slz_reference([struct.pack("<H", len(z)) + z, struct.pack("<H", 0) + b"y" * 1024], 5, 2048, 1)
    assert slz.decode(f) == b"x" * 1024 + b"y" * 1024
    # a file's first bytes: partial gives what they hold; whole decoding refuses
    assert slz.decode(f[:-10], partial=True) == b"x" * 1024 + b"y" * 1014
    with pytest.raises(ValueError):
        slz.decode(f[:-10])
    chained = bytearray(f)
    chained[0x1c] = 1
    with pytest.raises(ValueError):
        slz.decode(bytes(chained))


def test_java_b64_layout():
    for n in (0, 1, 56, 57, 58, 114, 1000):
        data = bytes(range(256)) * 4
        data = data[:n]
        s = base64.b64encode(data).decode()
        assert kvs.java_b64(data) == "".join(s[i:i + 76] + "\n" for i in range(0, len(s), 76))


def test_native_b64_quirk_and_lenient_decode():
    assert kvs.native_b64(b"abc") == "YWJj===="  # no padding needed: Aska appends four '='
    assert kvs.native_b64(b"ab") == "YWI="
    assert kvs._b64decode_lenient("YWJj====") == b"abc"
    assert kvs._b64decode_lenient("YWI") == b"ab"
    assert kvs._b64decode_lenient("YW\nJj\n    ") == b"abc"


def test_load_rejects_other_entries(tmp_path):
    good = kvs.KVSFile({"k": b"v\0"})
    p = tmp_path / "Game.xml"
    p.write_text(good.dumps(), encoding="utf-8")
    assert kvs.KVSFile.load(p).entries == {"k": b"v\0"}
    p.write_text(kvs.HEADER + '    <int name="x" value="1" />\n' + kvs.FOOTER, encoding="utf-8")
    with pytest.raises(ValueError):
        kvs.KVSFile.load(p)
    p.write_text(kvs.HEADER + "    <string name=\"x\">abc\n" + kvs.FOOTER, encoding="utf-8")
    with pytest.raises(ValueError):
        kvs.KVSFile.load(p)
    p.write_text("<map>\n</map>\n", encoding="utf-8")
    with pytest.raises(ValueError):
        kvs.KVSFile.load(p)
