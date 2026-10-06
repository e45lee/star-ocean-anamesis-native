// The guest's file calls with Linux semantics on either host (hle/libc_stdio.cpp, libc_win32.cpp).
//
// On Linux these are the host's own calls. On Windows the C runtime's differ from what the game
// relies on:
//   - remove() / unlink() refuse a file with the read-only attribute (Linux needs only a writable
//     directory). The shared pre-downloaded phone's files are hard links with chmod a-w, which the
//     Windows drive keeps as the read-only attribute;
//   - a file the CRT opened can't be deleted or renamed over (no FILE_SHARE_DELETE), and a deleted
//     file's name stays taken until its last handle closes;
//   - rename() never replaces an existing file. Our rename is soa_rename (common/win32/posix_compat.h,
//     force-included), which now also replaces an open or read-only target
//     (FILE_RENAME_FLAG_REPLACE_IF_EXISTS | POSIX_SEMANTICS | IGNORE_READONLY_ATTRIBUTE).
// The game's downloader writes NAME.tmp, then calls Aska::File::MoveFile(NAME.tmp, NAME) (rename).
// If that fails it calls DeleteFile(NAME) (remove) and MoveFile again (GameResourceDownloader.cpp
// line 0x1205). On a read-only NAME both failed, so the downloaded file was never put in place: the
// served master, I/86c7aec3/3a05a888.bin -> sqlite/basmaster.sqlite3, stayed NAME.tmp.
// Here every open shares delete access, and unlink / remove use POSIX semantics
// (FILE_DISPOSITION_FLAG_POSIX_SEMANTICS | IGNORE_READONLY_ATTRIBUTE, Windows 10 1809+). Where the
// file system has no POSIX semantics they fall back to the classic call. Errors set errno (the host
// CRT's numbers) as the CRT calls would.
// Tests: hle/host-file-* (host_file_tests.cpp; soaruntime_tests on both hosts).
#pragma once
#include <stdio.h>

namespace soa::hostfile {

// open(2) with the host's O_* flags (Windows: the CRT's _O_* flags) and permission bits; a CRT
// descriptor on Windows.
int open(const char* path, int oflag, int pmode);
// fopen(3); mode as bionic takes it ("r", "w+", "ab", "re", "wx", ...).
FILE* fopen(const char* path, const char* mode);
int unlink(const char* path);
// remove(3): unlink for a file, rmdir for a directory.
int remove(const char* path);

}  // namespace soa::hostfile
