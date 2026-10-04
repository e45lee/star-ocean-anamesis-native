"""Which asset files exist: the sources (a directory tree or a zip such as the APK), the presence
index over them, and the AIF image header reader (ADLD / SLZ unwrapping) used for sibling sizes."""
from __future__ import annotations

import os
import re
import struct
import zipfile
import zlib
from dataclasses import dataclass
from typing import Optional

from . import ROOT  # noqa: F401  (puts the repo root on sys.path for soa_save)
from soa_save.adld import chash32

try:
    import zstandard
except ImportError:  # sizes of zstd images are then unknown
    zstandard = None

#: Everything up to one of these folders is dropped from a stored path (APK / storage layouts).
STORAGE_ROOTS = ("builtin_data/", "assetpack/")
STORAGE_ROOT_RE = re.compile(r"^.*?(builtin_data/|assetpack/)")
#: Texture-quality folders folded away: `Image/etc2/x.aif` and `Image/etc2/hi/x.aif` are `Image/x.aif`.
QUALITY_FOLDER_RE = re.compile(r"/etc2(/hi)?/")
#: The source label of the repo's made-up files; they are no evidence for sibling sizes.
STANDIN_LABEL = "stand-in"

# AIF / ADLD / SLZ layout (docs/notes.md "Asset encryption", "SLZ")
HEADER_READ_LIMIT = 0x40000      # the image header is within the first 256 KiB
ADLD_MAGIC = b"ADLD"
ADLD_FLAGS_OFFSET = 4
ADLD_HEADER_SIZE = 16
ADLD_FLAG_XOR = 1                # body XORed with the hex CHash32 of the stored name
SLZ_MAGIC = b"SLZ"
SLZ_CODEC_OFFSET = 3
SLZ_SIZE_OFFSET = 0xc            # int32 decompressed size
SLZ_DATA_OFFSET = 0x14           # u32 offset of the first chunk
SLZ_CHUNK_KIB_OFFSET = 0x19      # chunk size in KiB (0 = one chunk)
SLZ_CODEC_STORED, SLZ_CODEC_DEFLATE, SLZ_CODEC_ZSTD = 0, 5, 7
XGMI_MAGIC = b"Xgmi"             # the image header: format byte at +0x20, u16 w, h at +0x28
XGMI_FORMAT_OFFSET = 0x20
XGMI_SIZE_OFFSET = 0x28
XGMI_MIN_TAIL = 0x30
AIF_FORMATS = {39: "JPEG", 47: "ETC2 RGB", 48: "ETC2 RGB+A1", 49: "ETC2 RGBA"}


def logical_name(stored: str) -> str:
    """A stored path as a logical asset name: storage roots dropped, quality folders folded."""
    p = stored.replace("\\", "/")
    for marker in STORAGE_ROOTS:
        i = p.find(marker)
        if i >= 0:
            p = p[i + len(marker):]
    return QUALITY_FOLDER_RE.sub("/", p)


class Source:
    """An asset source: a directory tree or a zip; `files` maps logical name -> stored path.
    Zero-size files don't count; the first stored file of a logical name wins."""

    def __init__(self, label: str, path: Optional[str]):
        self.label, self.path = label, path
        self.files: dict[str, str] = {}
        self.zip: Optional[zipfile.ZipFile] = None
        if not path or not os.path.exists(path):
            return
        if os.path.isdir(path):
            self._index_tree(path)
        else:
            self._index_zip(path)

    def _index_tree(self, path: str) -> None:
        for dirpath, _, names in os.walk(path):
            for name in names:
                full = os.path.join(dirpath, name)
                if os.path.getsize(full) > 0:
                    self.files.setdefault(logical_name(os.path.relpath(full, path)), full)

    def _index_zip(self, path: str) -> None:
        self.zip = zipfile.ZipFile(path)
        for info in self.zip.infolist():
            if info.file_size > 0 and not info.is_dir():
                self.files.setdefault(logical_name(info.filename), info.filename)

    def read(self, logical: str, limit: Optional[int] = None) -> bytes:
        """The file's bytes (the first `limit` bytes when given)."""
        p = self.files[logical]
        if self.zip:
            with self.zip.open(p) as f:
                return f.read(limit) if limit else f.read()
        with open(p, "rb") as f:
            return f.read(limit) if limit else f.read()

    def stored_name(self, logical: str) -> str:
        """The name the file's ADLD key is made from (relative to builtin_data / assetpack)."""
        p = self.files[logical]
        if self.zip:
            return STORAGE_ROOT_RE.sub("", p)
        return os.path.relpath(p, self.path)


class Presence:
    """The sources in lookup order; `where(path)` names the first that has a logical path."""

    def __init__(self, sources: list[Source]):
        self.sources = sources

    def where(self, path: str) -> Optional[str]:
        for s in self.sources:
            if path in s.files:
                return s.label
        return None

    def real_sources(self) -> list[Source]:
        """The sources whose files are evidence (not made-up stand-ins)."""
        return [s for s in self.sources if s.label != STANDIN_LABEL]


@dataclass(frozen=True)
class ImageInfo:
    width: int
    height: int
    format: str


def _unwrap_adld(data: bytes, stored_name: str) -> bytes:
    """The body of an ADLD container, XOR-decrypted when its flag says so."""
    flags = struct.unpack_from("<I", data, ADLD_FLAGS_OFFSET)[0]
    body = data[ADLD_HEADER_SIZE:]
    if flags & ADLD_FLAG_XOR:
        key = b"%x" % chash32(stored_name.encode())
        stream = (key * (len(body) // len(key) + 1))[:len(body)]
        body = bytes(a ^ b for a, b in zip(body, stream))
    return body


def _unwrap_slz(data: bytes) -> Optional[bytes]:
    """The first chunk of an SLZ stream, decompressed; None when the codec is unknown or broken."""
    codec = data[SLZ_CODEC_OFFSET]
    size = struct.unpack_from("<i", data, SLZ_SIZE_OFFSET)[0]
    off = struct.unpack_from("<I", data, SLZ_DATA_OFFSET)[0]
    chunk_kib = data[SLZ_CHUNK_KIB_OFFSET]
    want = min(chunk_kib * 1024 if chunk_kib else size, size)
    try:
        if codec == SLZ_CODEC_STORED:
            return data[off:off + want]
        n = struct.unpack_from("<H", data, off)[0]
        p = off + 2
        if n == 0:  # a stored chunk
            return data[p:p + want]
        if codec == SLZ_CODEC_ZSTD and zstandard:
            return zstandard.ZstdDecompressor().decompressobj().decompress(data[p:p + n])
        if codec == SLZ_CODEC_DEFLATE:
            return zlib.decompressobj(-15).decompress(data[p:p + n])
        return None
    except Exception:  # noqa: BLE001 - a broken file just has no known size
        return None


def _find_xgmi(data: bytes) -> Optional[ImageInfo]:
    """The first image header (16-byte aligned) in decoded AIF data."""
    for i in range(0, len(data) - XGMI_MIN_TAIL, 16):
        if data[i:i + 4] == XGMI_MAGIC:
            w, h = struct.unpack_from("<HH", data, i + XGMI_SIZE_OFFSET)
            fmt = data[i + XGMI_FORMAT_OFFSET]
            return ImageInfo(w, h, AIF_FORMATS.get(fmt, f"fmt {fmt}"))
    return None


def image_info(src: Source, logical: str) -> Optional[ImageInfo]:
    """Width, height and format from an Image/ file's AIF image header, or None."""
    try:
        data = src.read(logical, HEADER_READ_LIMIT)
    except (KeyError, OSError):
        return None
    if data[:4] == ADLD_MAGIC:
        data = _unwrap_adld(data, src.stored_name(logical))
    if data[:3] == SLZ_MAGIC:
        data = _unwrap_slz(data)
        if data is None:
            return None
    return _find_xgmi(data)
