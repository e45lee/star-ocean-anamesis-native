"""Decode and encode tri-Ace "ADLD" asset containers (e.g. assets/builtin_data/sqlite/basmaster.sqlite3;
the C++ twin is common/include/soa/adld.h).

Mirrors the decrypt callback registered in CGame::OnInitialize (vaddr 0x1149238):
  header: b"ADLD", u32 flags, 8 unused bytes; payload follows at +0x10.
  flags & 1: XOR payload with the ASCII hex of CHash32(name), repeating.
  flags & 2: AES-128-CBC. Key = digits of "%032u" % CHash32(name), one digit per nibble;
             IV = same packing of "09375711857134629684891855841614".
             If the plaintext starts with b"DCNE" v1, the real payload is at +16 with
             length u32@8 - 16.
`name` is the asset path relative to builtin_data, e.g. "sqlite/basmaster.sqlite3".
The AES half needs pycryptodome (imported only there).
"""
import struct
import sys
import zlib

MAGIC = b"ADLD"
HEADER_SIZE = 16
XOR, AES = 1, 2  # the flags (the manifests' encType)


def chash32(s: bytes) -> int:
    """Framework::CHash32(const char*): CRC-32 (zlib's polynomial) seeded with the length, no final
    xor. zlib.crc32 inverts the value going in and coming out, so pre- and post-invert around it."""
    return zlib.crc32(s, len(s) ^ 0xFFFFFFFF) ^ 0xFFFFFFFF


def digits16(s: str) -> bytes:
    """32 decimal digits packed one per nibble, high nibble first: the same bytes as reading them as hex."""
    return bytes.fromhex(s)


IV = digits16("09375711857134629684891855841614")


def xor_key(name: str) -> bytes:
    return b"%x" % chash32(name.encode())


def xor(data: bytes, name: str, start: int = 0) -> bytes:
    """`data` XORed with the repeating XOR key of `name`, from key position `start` (the offset of
    `data` in the payload: a payload can be XORed in pieces). Its own inverse."""
    k = xor_key(name)
    if not data:
        return b""
    s = start % len(k)
    stream = (k[s:] + k * (len(data) // len(k) + 1))[:len(data)]
    # (one big-integer XOR: C speed without numpy)
    return (int.from_bytes(data, "little") ^ int.from_bytes(stream, "little")).to_bytes(len(data), "little")


def aes_cipher(name: str):
    """A fresh AES-128-CBC cipher (pycryptodome) with the key of `name` and the fixed IV."""
    from Crypto.Cipher import AES as _AES  # pycryptodome; only the AES flavour needs it

    return _AES.new(digits16("%032u" % chash32(name.encode())), _AES.MODE_CBC, IV)


def decode(data: bytes, name: str) -> bytes:
    if data[:4] != MAGIC:
        return data
    flags = struct.unpack_from("<I", data, 4)[0]
    body = data[HEADER_SIZE:]
    if flags & XOR:
        return xor(body, name)
    if flags & AES:
        body = aes_cipher(name).decrypt(body[: len(body) // 16 * 16])
        if body[:4] == b"DCNE" and struct.unpack_from("<I", body, 4)[0] == 1:
            body = body[16:struct.unpack_from("<I", body, 8)[0]]
    return body


def encode(plain: bytes, name: str, flags: int = XOR) -> bytes:
    """The ADLD file of `plain` with `flags` (soa::adld::encrypt): XOR (every Script / Scenario /
    Image file), or AES with the DCNE v1 header, zero-padded to 16 bytes (as the 3.7.0 master is
    packed)."""
    if flags & XOR:
        body = xor(plain, name)
    elif flags & AES:
        dcne = b"DCNE" + struct.pack("<II", 1, 16 + len(plain)) + bytes(4) + plain
        body = aes_cipher(name).encrypt(dcne + bytes(-len(dcne) % 16))
    else:  # (neither: stored)
        body = plain
    return MAGIC + struct.pack("<I", flags) + bytes(8) + body


if __name__ == "__main__":
    src, name, dst = sys.argv[1:4]
    open(dst, "wb").write(decode(open(src, "rb").read(), name))
