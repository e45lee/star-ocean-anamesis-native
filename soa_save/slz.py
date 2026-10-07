"""SLZ, Aska's chunked compression (docs/notes.md "SLZ compressed files"; the C++ twin is
common/include/soa/aska_image.h).

Header (little-endian): b"SLZ", u8 codec (0 stored, 5 raw deflate, 7 zstd), ..., i32 size at 0xc,
u32 payload offset at 0x14, u8 chunk KiB at 0x19 (0: one chunk), u32 chain at 0x1c (0: none).
Each chunk of a codec 5 / 7 file is a u16 size and that many bytes; size 0 means the chunk is
stored raw. Codec 7 needs the zstandard module (imported when a zstd chunk is met).
"""
import struct
import zlib

MAGIC = b"SLZ"
HEADER_SIZE = 0x20
STORED, DEFLATE, ZSTD = 0, 5, 7
CHUNK = 65536  # what encode() writes (the shipped files' 64 KiB chunks)


def is_slz(d: bytes) -> bool:
    return len(d) >= HEADER_SIZE and d[:3] == MAGIC


def _inflate(codec, data):
    if codec == DEFLATE:
        return zlib.decompressobj(-15).decompress(data)
    if codec == ZSTD:
        import zstandard  # only zstd chunks need it

        return zstandard.ZstdDecompressor().decompressobj().decompress(data)
    raise ValueError(f"SLZ codec {codec} not supported")


def decode(d: bytes, partial: bool = False) -> bytes:
    """The decompressed bytes of SLZ data `d`; data that isn't SLZ is returned as is. A chained or
    truncated file raises ValueError, unless `partial`: then `d` may be a file's first bytes, and the
    result is what they give (a chunk cut short decompressed as far as it goes)."""
    if not is_slz(d):
        return d
    codec, size = d[3], struct.unpack_from("<i", d, 0xc)[0]
    p = struct.unpack_from("<I", d, 0x14)[0]
    chunk = d[0x19] * 1024 or size
    if struct.unpack_from("<I", d, 0x1c)[0]:
        raise ValueError("chained SLZ not supported")
    if size < 0:
        raise ValueError("SLZ: bad size")
    out, done = bytearray(), 0
    while done < size:
        want = min(chunk, size - done)
        raw = codec == STORED
        n = want
        if not raw:
            if p + 2 > len(d):
                if partial:
                    break
                raise ValueError("SLZ truncated")
            n = struct.unpack_from("<H", d, p)[0]
            p += 2
            raw = n == 0  # a chunk that didn't shrink is stored
            if raw:
                n = want
        data = d[p:p + n]
        if p + n > len(d) and not partial:
            raise ValueError("SLZ truncated")
        out += data if raw else _inflate(codec, data)
        if p + n > len(d):  # (partial: cut short here)
            break
        p += n
        done += want
    return bytes(out)


def encode(plain: bytes) -> bytes:
    """SLZ codec 5 as the shipped files have it (soa::aska::slz_encode): 64 KiB raw-deflate chunks
    at zlib level 9, a chunk that doesn't shrink stored (size 0); header {"SLZ", 5, 0, 1, 0x25,
    compressed size, size, 0, payload at 0x20, flags 1, 64 KiB chunks, 0x10, no chain}; the whole
    padded to 4. The same input gives the same bytes."""
    chunks = []
    for i in range(0, len(plain), CHUNK):
        raw = plain[i:i + CHUNK]
        co = zlib.compressobj(9, zlib.DEFLATED, -15)
        z = co.compress(raw) + co.flush()
        chunks.append(struct.pack("<H", len(z)) + z if len(z) < min(len(raw), CHUNK) else struct.pack("<H", 0) + raw)
    payload = b"".join(chunks)
    hdr = struct.pack("<3sBBBHiiIIBBHI", MAGIC, DEFLATE, 0, 1, 0x25, len(payload), len(plain), 0, HEADER_SIZE, 1, CHUNK // 1024, 0x10, 0)
    out = hdr + payload
    return out + b"\0" * (-len(out) % 4)
