"""The 3.7.0 download as a read-only tree of files: a folder or a ZIP archive, read in place.

The Python counterpart of soa::FileTree (common/include/soa/file_tree.h). The canonical form of the
download is the user's archive work/SOA-3.7.0-canonical-data.zip (DEFAULT): every entry stored, so a
member is a byte range of the zip and nothing is extracted, inflated into a temporary file or loaded
whole. A folder (an extracted download, a phone's data/files/download) works the same way: what a
path is decides, not its name.

    from soa_save.download_tree import DownloadTree
    t = DownloadTree.open()                     # the default zip; or DownloadTree.open(PATH)
    t.files("Sound")                            # every file under Sound/, recursive, sorted
    t.list("Image/etc2")                        # the file names directly in a folder
    t.read("version.bin"); t.open("Movie/x.mp4") (a seekable binary stream); t.size(rel)
    t.locate(rel)                               # (host file, offset, size) for a stored entry / a file

Paths are relative and '/'-separated. A zip whose only top-level entry is one folder holding the
tree (e.g. NAME/version.bin, ...) is read from inside that folder (FileTree's rule). Reading a member
reads only that member's bytes; listing reads only the zip's central directory (about 0.15 s for the
26,000 entries of the 3.7.0 zip).
"""
from __future__ import annotations

import fnmatch
import io
import os
import struct
import threading
import zipfile
from typing import BinaryIO, Optional

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
ZIP_NAME = "SOA-3.7.0-canonical-data.zip"
# The download in a checkout: the zip (an extracted folder is passed explicitly).
DEFAULT_REL = "work/" + ZIP_NAME
DEFAULT = os.path.join(REPO, "work", ZIP_NAME)


def default_path(repo: Optional[str] = None) -> str:
    """The checkout's download zip (it may not exist: callers check exists() / open())."""
    return os.path.join(repo or REPO, "work", ZIP_NAME)


class RangeFile(io.RawIOBase):
    """A read-only, seekable view of `size` bytes at `offset` of a file (a stored zip entry)."""

    def __init__(self, path: str, offset: int, size: int):
        self._f = open(path, "rb")
        self._off, self._size, self._pos = offset, size, 0

    def readable(self):
        return True

    def seekable(self):
        return True

    def tell(self):
        return self._pos

    def seek(self, pos, whence=io.SEEK_SET):
        base = {io.SEEK_SET: 0, io.SEEK_CUR: self._pos, io.SEEK_END: self._size}[whence]
        self._pos = max(0, base + pos)
        return self._pos

    def readinto(self, b):
        n = max(0, min(len(b), self._size - self._pos))
        if n == 0:
            return 0
        self._f.seek(self._off + self._pos)
        got = self._f.readinto(memoryview(b)[:n])
        self._pos += got
        return got

    def read(self, n=-1):
        if n is None or n < 0:
            n = self._size - self._pos
        buf = bytearray(max(0, min(n, self._size - self._pos)))
        got = self.readinto(buf)
        return bytes(buf[:got])

    def readall(self):
        return self.read(-1)

    def close(self):
        self._f.close()
        super().close()


class DownloadTree:
    """A folder or a zip of the download (open() decides by what `path` is)."""

    path: str
    is_zip: bool = False
    prefix: str = ""

    @staticmethod
    def open(path: Optional[str] = None) -> "DownloadTree":
        """The folder or the zip at `path` (default: DEFAULT). FileNotFoundError when it is
        neither."""
        p = os.fspath(path) if path is not None else DEFAULT
        if os.path.isdir(p):
            return _FolderTree(p)
        if os.path.isfile(p) and zipfile.is_zipfile(p):
            return _ZipTree(p)
        raise FileNotFoundError(f"{p}: neither a folder nor a zip (the 3.7.0 download: {DEFAULT_REL}, or an extracted folder)")

    @staticmethod
    def open_or_none(path: Optional[str] = None) -> Optional["DownloadTree"]:
        try:
            return DownloadTree.open(path)
        except FileNotFoundError:
            return None

    # ---- the interface (both kinds) ----
    def files(self, dir: str = "") -> list[str]:
        """Every regular file under the folder `dir` ("" = all), recursive, relative, sorted."""
        raise NotImplementedError

    def list(self, dir: str) -> list[str]:
        """The names of the regular files directly in the folder `dir`, sorted."""
        d = _norm_dir(dir)
        return sorted(n[len(d):] for n in self.files(dir) if "/" not in n[len(d):])

    def glob(self, pattern: str) -> list[str]:
        """The files whose relative path matches `pattern` (fnmatch; '*' also crosses '/'), sorted."""
        head = pattern.split("*", 1)[0].split("?", 1)[0].split("[", 1)[0]
        d = head.rsplit("/", 1)[0] if "/" in head else ""
        return [n for n in self.files(d) if fnmatch.fnmatchcase(n, pattern)]

    def exists(self, rel: str) -> bool:
        """A regular file?"""
        raise NotImplementedError

    def is_dir(self, rel: str) -> bool:
        raise NotImplementedError

    def size(self, rel: str) -> int:
        raise NotImplementedError

    def open_file(self, rel: str) -> BinaryIO:
        """A seekable binary stream of the file (FileNotFoundError when absent)."""
        raise NotImplementedError

    def read(self, rel: str) -> bytes:
        with self.open_file(rel) as f:
            return f.read()

    def locate(self, rel: str) -> Optional[tuple[str, int, int]]:
        """(host file, offset, size) of the file's bytes in place: the folder's file itself, or a
        stored zip entry; None for a missing file or a compressed entry."""
        raise NotImplementedError

    def host_spec(self, rel: str) -> Optional[str]:
        """The file as a path a host tool reads: the folder's file, or "ZIP@OFFSET+SIZE" for a stored
        zip entry (tools/aif2png takes both); None when it can't be read in place."""
        loc = self.locate(rel)
        if loc is None:
            return None
        return loc[0] if not self.is_zip else f"{loc[0]}@{loc[1]}+{loc[2]}"

    def __reduce__(self):
        # (pickled for a process pool: the other process opens its own)
        return (DownloadTree.open, (self.path,))

    def describe(self) -> str:
        return f"{self.path} ({'zip' if self.is_zip else 'folder'})"

    def __repr__(self):
        return f"DownloadTree({self.describe()})"


def _norm(rel: str) -> str:
    return rel.replace("\\", "/").strip("/")


def _norm_dir(rel: str) -> str:
    r = _norm(rel)
    return r + "/" if r else ""


class _FolderTree(DownloadTree):
    def __init__(self, path: str):
        self.path = os.path.abspath(path)
        self.is_zip = False

    def _p(self, rel: str) -> str:
        return os.path.join(self.path, *_norm(rel).split("/")) if _norm(rel) else self.path

    def files(self, dir: str = "") -> list[str]:
        out = []
        for dp, dns, fns in os.walk(self._p(dir)):
            dns.sort()
            rel = os.path.relpath(dp, self.path).replace(os.sep, "/")
            rel = "" if rel == "." else rel + "/"
            out.extend(rel + f for f in fns if os.path.isfile(os.path.join(dp, f)))
        return sorted(out)

    def list(self, dir: str) -> list[str]:
        p = self._p(dir)
        if not os.path.isdir(p):
            return []
        return sorted(f for f in os.listdir(p) if os.path.isfile(os.path.join(p, f)))

    def exists(self, rel):
        return bool(_norm(rel)) and os.path.isfile(self._p(rel))

    def is_dir(self, rel):
        return os.path.isdir(self._p(rel))

    def size(self, rel):
        return os.path.getsize(self._p(rel))

    def open_file(self, rel):
        if not self.exists(rel):
            raise FileNotFoundError(f"{self.path}: no {rel}")
        return open(self._p(rel), "rb")

    def locate(self, rel):
        return (self._p(rel), 0, os.path.getsize(self._p(rel))) if self.exists(rel) else None


class _ZipTree(DownloadTree):
    def __init__(self, path: str):
        self.path = os.path.abspath(path)
        self.is_zip = True
        self._zip = zipfile.ZipFile(self.path)
        self._lock = threading.Lock()
        infos = [i for i in self._zip.infolist() if not i.is_dir()]
        tops = {i.filename.split("/", 1)[0] for i in self._zip.infolist()}
        self.prefix = ""
        if len(tops) == 1 and all("/" in i.filename for i in infos):  # one top folder holding the tree
            self.prefix = next(iter(tops)) + "/"
        n = len(self.prefix)
        self._info = {i.filename[n:]: i for i in infos}
        self._names = sorted(self._info)
        self._dirs = {""}
        for name in self._names:
            parts = name.split("/")[:-1]
            for k in range(1, len(parts) + 1):
                self._dirs.add("/".join(parts[:k]))
        self._data_off: dict[str, int] = {}
        self._fd: Optional[int] = None

    def files(self, dir: str = "") -> list[str]:
        import bisect

        d = _norm_dir(dir)
        if not d:
            return list(self._names)
        lo = bisect.bisect_left(self._names, d)
        hi = bisect.bisect_left(self._names, d[:-1] + chr(ord("/") + 1))
        return self._names[lo:hi]

    def exists(self, rel):
        return _norm(rel) in self._info

    def is_dir(self, rel):
        return _norm(rel) in self._dirs

    def size(self, rel):
        i = self._info.get(_norm(rel))
        if i is None:
            raise FileNotFoundError(f"{self.path}: no {rel}")
        return i.file_size

    def info(self, rel) -> Optional[zipfile.ZipInfo]:
        return self._info.get(_norm(rel))

    def locate(self, rel):
        i = self._info.get(_norm(rel))
        if i is None or i.compress_type != zipfile.ZIP_STORED or i.flag_bits & 1:
            return None
        off = self._data_off.get(i.filename)
        if off is None:
            h = self._pread(i.header_offset, 30)  # the local header's name and extra lengths: where the data starts
            if len(h) != 30 or h[:4] != b"PK\x03\x04":
                return None
            nlen, xlen = struct.unpack_from("<HH", h, 26)
            off = i.header_offset + 30 + nlen + xlen
            self._data_off[i.filename] = off
        return (self.path, off, i.file_size)

    def _pread(self, off: int, n: int) -> bytes:
        # (a positioned read on our own descriptor: no shared file offset, so also safe in a forked
        # child that inherited this tree)
        if self._fd is None:
            with self._lock:
                if self._fd is None:
                    self._fd = os.open(self.path, os.O_RDONLY | getattr(os, "O_BINARY", 0))
        if hasattr(os, "pread"):
            return os.pread(self._fd, n, off)
        with open(self.path, "rb") as f:  # (Windows: no pread)
            f.seek(off)
            return f.read(n)

    def open_file(self, rel):
        loc = self.locate(rel)
        if loc is not None:  # a stored entry: a byte range of the zip, no zipfile state shared
            return io.BufferedReader(RangeFile(*loc), buffer_size=1 << 20)
        i = self._info.get(_norm(rel))
        if i is None:
            raise FileNotFoundError(f"{self.path}: no {rel}")
        return io.BytesIO(self.read(rel))

    def read(self, rel):
        loc = self.locate(rel)
        if loc is not None:
            return self._pread(loc[1], loc[2])
        if _norm(rel) not in self._info:
            raise FileNotFoundError(f"{self.path}: no {rel}")
        with self._lock:  # (zipfile's own reader: a compressed entry; not used by the 3.7.0 zip)
            with self._zip.open(self._info[_norm(rel)]) as f:
                return f.read()


def open_member_or_file(path: str, tree: Optional[DownloadTree] = None) -> bytes:
    """`path` read as a file when it is one, else as a member of `tree` (default: the default
    download), for tools whose input is "a file, or a member of the download"."""
    if os.path.isfile(path):
        with open(path, "rb") as f:
            return f.read()
    return (tree or DownloadTree.open()).read(path)

