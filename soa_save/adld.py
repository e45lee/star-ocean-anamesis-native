"""Decode tri-Ace "ADLD" asset containers (e.g. assets/builtin_data/sqlite/basmaster.sqlite3).

Mirrors the decrypt callback registered in CGame::OnInitialize (vaddr 0x1149238):
  header: b"ADLD", u32 flags, 8 unused bytes; payload follows at +0x10.
  flags & 1: XOR payload with the ASCII hex of CHash32(name), repeating.
  flags & 2: AES-128-CBC. Key = digits of "%032u" % CHash32(name), one digit per nibble;
             IV = same packing of "09375711857134629684891855841614".
             If the plaintext starts with b"DCNE" v1, the real payload is at +16 with
             length u32@8 - 16.
`name` is the asset path relative to builtin_data, e.g. "sqlite/basmaster.sqlite3".
"""
import struct
import sys

from Crypto.Cipher import AES

_T = []
for _i in range(256):
    _c = _i
    for _ in range(8):
        _c = (_c >> 1) ^ 0xEDB88320 if _c & 1 else _c >> 1
    _T.append(_c)


def chash32(s: bytes) -> int:
    """Framework::CHash32(const char*): CRC-32 table, seeded with the length, no final xor."""
    c = len(s)
    for b in s:
        c = _T[(c ^ b) & 0xFF] ^ (c >> 8)
    return c & 0xFFFFFFFF


def _digits16(s: str) -> bytes:
    out = bytearray(16)
    for i, ch in enumerate(s):
        out[i // 2] |= int(ch) << 4 if i % 2 == 0 else int(ch)
    return bytes(out)


IV = _digits16("09375711857134629684891855841614")


def decode(data: bytes, name: str) -> bytes:
    if data[:4] != b"ADLD":
        return data
    flags = struct.unpack_from("<I", data, 4)[0]
    body = data[16:]
    h = chash32(name.encode())
    if flags & 1:
        k = b"%x" % h
        return bytes(b ^ k[i % len(k)] for i, b in enumerate(body))
    if flags & 2:
        body = AES.new(_digits16("%032u" % h), AES.MODE_CBC, IV).decrypt(body[: len(body) // 16 * 16])
        if body[:4] == b"DCNE" and struct.unpack_from("<I", body, 4)[0] == 1:
            body = body[16:struct.unpack_from("<I", body, 8)[0]]
    return body


if __name__ == "__main__":
    src, name, dst = sys.argv[1:4]
    open(dst, "wb").write(decode(open(src, "rb").read(), name))
