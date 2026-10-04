"""Read/write the Aska::LocalKVS SharedPreferences files (Aska.xml, Game.xml).

Each <string> entry is:
  name = Base64(ChaCha20(key))            -- native Aska::Encode::Base64Encode, which
                                             appends "====" when len(key) % 3 == 0
  text = Base64.DEFAULT(ChaCha20(value)) + "    "   (Java encoder: 76-col lines, trailing \n)
ChaCha20 restarts at counter 0 for every key and value. See docs/notes.md.
"""
import base64
import re
import struct
import xml.etree.ElementTree as ET

from Crypto.Cipher import ChaCha20

KEY_V11 = b"xp1666a2P7QGhOCRxCjG8aWj5PmxZOrY"
NONCE_V11 = b"g7TtZVIKyqc0"
KEY_V10_BASE = b'"pO%q8Yu2.gb\\/(bG7L+ 6{S,O1z}_=w'
NONCE_V10_BASE = b"vH9=-2.OP(VN"

HEADER = "<?xml version='1.0' encoding='utf-8' standalone='yes' ?>\n<map>\n"
FOOTER = "</map>\n"


def legacy_key(uid8: bytes):
    """Key/nonce for version "1.0" stores, derived from Aska::Machine::GetUniqueID."""
    def x(base):
        return bytes(b ^ uid8[i % len(uid8)] for i, b in enumerate(base))
    return x(KEY_V10_BASE), x(NONCE_V10_BASE)


def crypt(data: bytes, key=KEY_V11, nonce=NONCE_V11) -> bytes:
    return ChaCha20.new(key=key, nonce=nonce).encrypt(data)


def _b64decode_lenient(s: str) -> bytes:
    s = re.sub(r"\s", "", s).rstrip("=")
    return base64.b64decode(s + "=" * (-len(s) % 4))


def native_b64(data: bytes) -> str:
    """Aska::Encode::Base64Encode: standard, but emits '====' when no padding is needed."""
    s = base64.b64encode(data).decode()
    return s + "====" if len(data) % 3 == 0 else s


def java_b64(data: bytes) -> str:
    """android.util.Base64.encodeToString(data, DEFAULT): 76-char lines, each ending in a newline
    (the MIME layout base64.encodebytes writes)."""
    return base64.encodebytes(data).decode()


class KVSFile:
    """Ordered plaintext view of one prefs file. Values are raw bytes."""

    def __init__(self, entries=None, key=KEY_V11, nonce=NONCE_V11):
        self.entries = dict(entries or {})
        self.key, self.nonce = key, nonce

    @classmethod
    def load(cls, path, key=KEY_V11, nonce=NONCE_V11):
        raw = open(path, encoding="utf-8").read()
        if not raw.startswith(HEADER) or not raw.endswith(FOOTER):
            raise ValueError(f"{path}: unexpected SharedPreferences layout")
        self = cls(key=key, nonce=nonce)
        try:
            root = ET.fromstring(raw)
        except ET.ParseError as e:
            raise ValueError(f"{path}: {e}") from e
        for el in root:
            if el.tag != "string" or set(el.attrib) != {"name"} or len(el):
                raise ValueError(f"{path}: unexpected <{el.tag}> entry")
            name = crypt(_b64decode_lenient(el.attrib["name"]), key, nonce).decode("utf-8")
            self.entries[name] = crypt(_b64decode_lenient(el.text or ""), key, nonce)
        return self

    def dumps(self) -> str:
        out = [HEADER]
        for name, value in self.entries.items():
            n = native_b64(crypt(name.encode("utf-8"), self.key, self.nonce))
            t = (java_b64(crypt(value, self.key, self.nonce)) + "    ").replace("\n", "&#10;")
            out.append(f'    <string name="{n}">{t}</string>\n')
        out.append(FOOTER)
        return "".join(out)

    def save(self, path):
        with open(path, "w", encoding="utf-8", newline="") as f:
            f.write(self.dumps())

    # Typed accessors -------------------------------------------------------
    def get_u32(self, name):
        return struct.unpack("<I", self.entries[name])[0]

    def set_u32(self, name, v):
        self.entries[name] = struct.pack("<I", v & 0xFFFFFFFF)

    def get_u8(self, name):
        return self.entries[name][0]

    def set_u8(self, name, v):
        self.entries[name] = bytes([v & 0xFF])

    def get_str(self, name):
        return self.entries[name].rstrip(b"\0").decode("utf-8")

    def set_str(self, name, s):
        self.entries[name] = s.encode("utf-8") + b"\0"


def describe(v: bytes):
    """Best-effort (type, value) guess for display/JSON."""
    if len(v) > 1 and v.endswith(b"\0") and all(32 <= c < 127 or c >= 0x80 for c in v[:-1]):
        try:
            return "str", v[:-1].decode("utf-8")
        except UnicodeDecodeError:
            pass
    if len(v) == 4:
        return "u32", struct.unpack("<I", v)[0]
    if len(v) == 1:
        return "u8", v[0]
    return "hex", v.hex()
