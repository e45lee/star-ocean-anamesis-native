"""port/scripts/remaining.py's library reader (pyelftools sections) and its <8B classification."""
import os
import sys

import pytest

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(REPO, "port", "scripts"))
import remaining  # noqa: E402

LIB = os.path.join(REPO, "work", "libSOA-3.7.0.so")


def test_short_kind():
    code = {0x1000: bytes.fromhex("c0035fd6"), 0x2000: (0x14000010).to_bytes(4, "little"), 0x3000: bytes.fromhex("1f2003d5")}
    read = lambda va, n: code.get(va)  # noqa: E731
    assert remaining.short_kind(read, 0x1000, 4) == "lone RET"
    assert remaining.short_kind(read, 0x2000, 4) == "tail branch (B)"
    assert remaining.short_kind(read, 0x3000, 4) == "other one-instruction"
    assert remaining.short_kind(read, 0x1000, 2) == "?"
    assert remaining.short_kind(None, 0x1000, 4) == "?"


def test_unreadable_library():
    assert remaining.elf_reader("/nonexistent/libSOA.so") is None


@pytest.mark.skipif(not os.path.exists(LIB), reason="no work/libSOA-3.7.0.so")
def test_reader_matches_the_load_segments():
    """Section reads equal the file bytes the PT_LOAD segments map (a second route to the same bytes)."""
    from elftools.elf.elffile import ELFFile
    read = remaining.elf_reader(LIB)
    with open(LIB, "rb") as f:
        elf = ELFFile(f)
        segs = [(s["p_vaddr"], s["p_offset"], s["p_filesz"]) for s in elf.iter_segments() if s["p_type"] == "PT_LOAD"]
        funcs = [s["st_value"] for s in elf.get_section_by_name(".dynsym").iter_symbols()
                 if s["st_info"]["type"] == "STT_FUNC" and s["st_value"]][:2000]
        data = open(LIB, "rb").read()
    for va in funcs:
        off = next(o + va - v for v, o, n in segs if v <= va < v + n)
        assert read(va, 8) == data[off:off + 8], hex(va)
    assert read(0, 4) is None  # the ELF header isn't in a PROGBITS section with an address
