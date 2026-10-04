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
import zlib


def chash32(s: bytes) -> int:
    """Framework::CHash32(const char*): CRC-32 (zlib's polynomial) seeded with the length, no final
    xor. zlib.crc32 inverts the value going in and coming out, so pre- and post-invert around it."""
    return zlib.crc32(s, len(s) ^ 0xFFFFFFFF) ^ 0xFFFFFFFF


def _digits16(s: str) -> bytes:
    """32 decimal digits packed one per nibble, high nibble first: the same bytes as reading them as hex."""
    return bytes.fromhex(s)


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
        from Crypto.Cipher import AES  # pycryptodome; only this branch needs it

        body = AES.new(_digits16("%032u" % h), AES.MODE_CBC, IV).decrypt(body[: len(body) // 16 * 16])
        if body[:4] == b"DCNE" and struct.unpack_from("<I", body, 4)[0] == 1:
            body = body[16:struct.unpack_from("<I", body, 8)[0]]
    return body


if __name__ == "__main__":
    src, name, dst = sys.argv[1:4]
    open(dst, "wb").write(decode(open(src, "rb").read(), name))
