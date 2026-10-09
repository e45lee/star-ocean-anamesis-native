// resource_layout.h: the guest data layouts of the `resource` subsystem (files, streams, the resource cache, the downloader).
//
// Types first (port/PLAN.md task 6): every guest class or struct this subsystem's natives touch is
// recovered here before the code that uses it, as a C++ class with the guest's layout byte for byte
// and the guest's methods attached as members (not a struct + free functions):
//   - fields at the guest's offsets, named after their use (m_hp); unknown bytes as named padding
//     (u8 unk_0c[4]), never offset arithmetic in the natives;
//   - a static_assert per known field offset and one for sizeof, so a wrong guess fails the build;
//   - a comment naming where the layout was read (constructor, decompile in port/decomp/resource/).
// Natives are these members (this->m_hp), never *(T*)(p + off). Keep the classes standard-layout (no
// C++ virtual, no non-static members of reference type), so offsetof works. The guest is AArch64 LP64; the
// host (x86-64 / AArch64) has the same sizes and alignments for these plain types (fields use fixed-width
// types only: on Windows `long` is 32-bit).
// `tools/subsystem.py export-types resource` turns the structs into port/decomp/resource/types.json for Ghidra.
//
// The guest classes are Aska::*, Framework::* and the client's C*; here they are flat in
// soa::native::resource, each comment naming the guest class. A guest base class with data is the first
// member `base` (standard layout), as in containers_layout.h. Proofs: resource_layout_test.cpp
// (`soa --selftest resource/`); the README's types table says which class each test covers.
#ifndef SOA_NATIVE_RESOURCE_LAYOUT_H
#define SOA_NATIVE_RESOURCE_LAYOUT_H

#include <cstddef>
#include <cstdint>

#include "../containers/containers_layout.h"
#include "../data_formats/data_formats_layout.h"
#include "../hash/hash_layout.h"
#include "../kernel/kernel_layout.h"
#include "../libcxx/libcxx_layout.h"
#include "../memory/memory_layout.h"
#include "../sync/sync_layout.h"

namespace soa::native::resource {

using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using s8 = std::int8_t;
using s16 = std::int16_t;
using s32 = std::int32_t;
using s64 = std::int64_t;
using f32 = float;

using String = libcxx::String;  // std::__ndk1::basic_string<char, ..., Framework::CSTLAllocator<char, ...>>

// ---- Other subsystems' classes held as sized bytes (their headers are not merged yet) ----------------
//
// sync (sync_layout.h): its classes are embedded where the guest embeds them.
using sync::CMutex;
using sync::CriticalSection;
using sync::Event;
using sync::FastCriticalSection;
// kernel (the sibling type agent recovers it): Aska::Task, guest size 0x28, data size 0x27 (a derived
// class's first byte goes at +0x27: Framework::CResourceManager::m_isInitialized). Its constructor
// (inlined in CResourceManager's / CResourceElement's): vtable, +0x08 / +0x10 / +0x18 = 0, +0x20 u32 =
// GetDefaultLevel() (vtable slot 11), +0x24 u16 = 0, +0x26 u8 = 0.
inline constexpr u64 kTaskDataSize = 0x27;
// kernel: Framework::CFiberUnit (kernel_layout.h, 0x38) is CGameResourceDownloader's base; the
// downloader's first field the constructor writes is at +0x40, so +0x38..0x3f is either the derived
// class's own (never written by its constructor) or alignment: unknown.
// Aska::Task as a member (CResourceElement's second base at +0xc0, LIBLManager's update task):
// kernel_layout.h's Task (0x28). CResourceManager keeps it as inline bytes (its own field sits in the
// Task's tail padding at +0x27).
using TaskBytes = kernel::Task;
static_assert(sizeof(TaskBytes) == 0x28);

// Framework::CHash32: the `hash` subsystem's class (hash_layout.h: {vtable, u32 m_hash}, 0x10).
using CHash32Bytes = hash::CHash32;
static_assert(sizeof(CHash32Bytes) == 0x10);

// ==== Files and streams ===============================================================================

// Aska::File: guest size 0x18; layout from Open / Close / Read / Seek / GetFileSizeL (port/decomp/resource/
// streams.c) and the constructor inlined in CFileLoader's (vtable, +8 = 0, +0x10 = 0). A stdio FILE* or,
// for an APK asset (m_isAsset), an AAsset* (AAssetManager_open on Aska::Boot::m_pAssetManager).
class File {
public:
    void DtorDelete();                                       // ~File() D0 (closes)
    bool Open(const char* path, bool readOnly, bool create, bool unused);  // Open(char const*, bool, bool, bool): "rb" / "wb+" / "rb+"
    void Close();                                            // Close()
    u64 Read(void* dst, u64 size, u32* err);                 // Read(void*, unsigned long, unsigned int*)
    u64 ReadWithOffset(void* dst, u64 offset, u64 size, u32* err);
    u64 Write(const void* src, u64 size);                    // Write(void const*, unsigned long)
    s64 Seek(s64 offset, s32 origin);                        // Seek(long, Origin): returns ftell for stdio
    s64 SeekL(s64 offset, s32 origin);
    s64 GetFileSizeL() const;                                // GetFileSizeL() const
    s64 GetFileSize() const;
    bool SetFileSize(u64 size);
    void Flush();
    s64 DistanceToLineBreakOrEndOrNonPrintable();
    // statics
    static s64 GetFileSizeL(const char* path, bool asset);   // GetFileSizeL(char const*, bool)
    static s64 GetFileSize(const char* path, bool asset);
    static bool DoesExist(const char* path, bool asset);     // DoesExist(char const*, bool)
    static bool CreateDirectory(const char* path);
    static bool DeleteFile(const char* path);
    static bool CopyFile(const char* from, const char* to, bool overwrite);
    static bool MoveFile(const char* from, const char* to);
    static bool IsReadOnly(const char* path);
    static bool OpenAndDumpToBuffer(const char* path, bool asset, char* buf, u64* size, bool text);

    const void* vtable;  // 0x00: _ZTVN4Aska4FileE + 0x10 (slot 0 / 1 the destructors)
    u8 m_isAsset;        // 0x08: m_handle is an AAsset* (else a FILE*)
    u8 unk_09[7];        // 0x09: padding
    u64 m_handle;        // 0x10: FILE* / AAsset* (guest address), 0 when closed
};
static_assert(offsetof(File, m_isAsset) == 0x08);
static_assert(offsetof(File, m_handle) == 0x10);
static_assert(sizeof(File) == 0x18);

// Aska::IStream: the stream interface (vtable only; the implementations below). Status codes (Aska::Status):
// -0x3bc not ready (0xfffffffffffffc44), -0x3c1 short read / out of range (…c3f), -0x3c0 open failed (…c40).
// Its statics (Transfer, Compare, Align, Fill, SeekAlign, Print, CalcSeekPt) take the stream as an argument.
class IStream {
public:
    // Virtuals in vtable order (every stream class here keeps these slots):
    //   0 / 1 destructors, 2 IsReady() const, 3 Tell() const, 4 Seek(long, int), 5 Read(void*, size, count),
    //   6 Write(void const*, size, count), 7 Flush(), 8 IsEnd(long*) const, 9 SetLastError(long) const,
    //   10 GetLastError() const, 11 PeekLastError() const, 12 GetTotalSize() const, 13 IsAsync() const,
    //   14 IsBusy() const, 15 Wait(int) const, 16 Cancel(unsigned long), 17 ReadAsync(...), 18 WriteAsync(...);
    //   the buffering streams (Aska::IBufferingStream) add 19 Lock(void**, size), 20 Unlock(size),
    //   21 IsBufferable(int, size, long*) const, 22 IsBufferingReady() const, 23 IsBufferingEnd(int, long*) const.
    static s64 CalcSeekPt(s64 pos, s64 base, s64 size, s64 offset, s32 origin, s64* status);  // CalcSeekPt(long, long, long, long, int, long*)
    static u64 Transfer(IStream* to, IStream* from, u64 size, s64* status);
    static bool Compare(IStream* a, IStream* b, u64 size, s64* status);

    const void* vtable;  // 0x00
};
static_assert(sizeof(IStream) == 0x08);

inline constexpr int kStreamSlotIsReady = 2;
inline constexpr int kStreamSlotTell = 3;
inline constexpr int kStreamSlotSeek = 4;
inline constexpr int kStreamSlotRead = 5;
inline constexpr int kStreamSlotIsEnd = 8;
inline constexpr int kStreamSlotSetLastError = 9;
inline constexpr int kStreamSlotGetTotalSize = 12;
inline constexpr int kStreamSlotLock = 19;
inline constexpr int kStreamSlotUnlock = 20;

// Aska::FileStream: an IStream over an Aska::File; guest size 0x30 (no exported constructor: the fields from
// Open / Read / Tell / IsEnd / SetLastError / the destructor, streams.c).
class FileStream {
public:
    void DtorBase();                                         // ~FileStream() D2
    void DtorDelete();                                       // ~FileStream() D0
    bool Open(const char* path, bool readOnly, bool create, s32 endian);  // Open(char const*, bool, bool, Machine::Endian)
    void Close();
    // vtable (IStream's slots): IsReady, Tell, Seek, Read, Write, Flush, IsEnd, SetLastError, GetLastError,
    // PeekLastError (the IStream defaults), GetTotalSize
    bool IsReady() const;                                    // slot 2: m_file.m_handle != 0
    s64 Tell() const;                                        // slot 3
    s64 Seek(s64 offset, s32 origin);                        // slot 4
    u64 Read(void* dst, u64 size, u64 count);                // slot 5: byte-swaps elements of 2 / 4 / 8 bytes when m_swapBytes
    u64 Write(const void* src, u64 size, u64 count);         // slot 6
    void Flush();                                            // slot 7
    bool IsEnd(s64* status) const;                           // slot 8
    s64 SetLastError(s64 status) const;                      // slot 9: m_lastError = status
    s64 GetLastError() const;                                // slot 10
    s64 GetTotalSize() const;                                // slot 12

    const void* vtable;  // 0x00: _ZTVN4Aska10FileStreamE + 0x10
    File m_file;         // 0x08
    s64 m_lastError;     // 0x20: Aska::Status
    u8 m_swapBytes;      // 0x28: Open: !(endian argument & 1) (the file's endianness differs from the machine's)
    u8 unk_29[7];        // 0x29: padding
};
static_assert(offsetof(FileStream, m_file) == 0x08);
static_assert(offsetof(FileStream, m_lastError) == 0x20);
static_assert(offsetof(FileStream, m_swapBytes) == 0x28);
static_assert(sizeof(FileStream) == 0x30);

// Aska::StaticStream: a buffering stream over memory; guest size 0x50 (no exported constructor: the fields
// from Open / Read / Write / Seek / Tell / Lock / Unlock / IsEnd / the destructor, streams.c).
class StaticStream {
public:
    void DtorBase();                                         // ~StaticStream() D2: releases both shared arrays
    void DtorDelete();                                       // ~StaticStream() D0
    bool Open(const s8* data, u64 size);                     // Open(signed char const*, unsigned long): fails when already open
    bool IsReady() const;                                    // slot 2: m_data != 0
    s64 Tell() const;                                        // slot 3: m_pos (SetLastError(-0x3c1) past the end)
    s64 Seek(s64 offset, s32 origin);                        // slot 4: CalcSeekPt(m_pos, 0, m_size, ...)
    u64 Read(void* dst, u64 size, u64 count);                // slot 5: memcpy from m_data + m_pos
    u64 Write(const void* src, u64 size, u64 count);         // slot 6: memcpy to m_data + m_pos
    void Flush();                                            // slot 7
    bool IsEnd(s64* status) const;                           // slot 8: m_pos >= m_size
    s64 SetLastError(s64 status) const;                      // slot 9
    s64 GetLastError() const;                                // slot 10
    s64 PeekLastError() const;                               // slot 11
    s64 GetTotalSize() const;                                // slot 12: m_size
    s64 Lock(void** out, u64 size);                          // slot 19: *out = m_data + m_pos, m_pos += size, m_lockedBytes += size
    s64 Unlock(u64 size);                                    // slot 20: m_lockedBytes -= size (0: all)
    bool IsBufferable(s32 dir, u64 size, s64* status) const; // slot 21
    bool IsBufferingReady() const;                           // slot 22
    bool IsBufferingEnd(s32 dir, s64* status) const;         // slot 23

    const void* vtable;                           // 0x00: _ZTVN4Aska12StaticStreamE + 0x10
    containers::TSharedPointer<s8> m_owned;       // 0x08: an owned buffer (Aska::TSharedArray<signed char>: delete[] at 0)
    containers::TSharedPointer<s8> m_owned2;      // 0x18: a second owned buffer (released first)
    const s8* m_data;                             // 0x28
    u64 m_size;                                   // 0x30
    u64 m_pos;                                    // 0x38
    s32 m_lockedBytes;                            // 0x40: Lock adds, Unlock subtracts (LL/SC)
    u8 unk_44[4];                                 // 0x44: zeroed by Open (as part of a u32 store at 0x40)
    s64 m_lastError;                              // 0x48: Aska::Status (Open clears it)
};
static_assert(offsetof(StaticStream, m_owned) == 0x08);
static_assert(offsetof(StaticStream, m_owned2) == 0x18);
static_assert(offsetof(StaticStream, m_data) == 0x28);
static_assert(offsetof(StaticStream, m_size) == 0x30);
static_assert(offsetof(StaticStream, m_pos) == 0x38);
static_assert(offsetof(StaticStream, m_lockedBytes) == 0x40);
static_assert(offsetof(StaticStream, m_lastError) == 0x48);
static_assert(sizeof(StaticStream) == 0x50);

// Aska::MultiMediaStream::LoopParam: the loop section Open takes (copied to +0x58).
struct MultiMediaLoopParam {
    u64 m_count;    // 0x00: loops (IsEnd: -1 forever)
    u64 m_start;    // 0x08: loop start (0 / 0: the whole stream)
    u64 m_end;      // 0x10: loop end
    u64 m_user;     // 0x18: copied as is (the loop delegate's argument)
};
static_assert(sizeof(MultiMediaLoopParam) == 0x20);

// Aska::MultiMediaStream: a windowed (and looping) view of another stream, used by the sound and movie
// players; the fields from Open_ / Close / Tell / GetTotalSize / IsEnd / IsBufferingReady / the destructor
// (streams.c). No exported constructor; the size is not confirmed (the last known field ends at 0x8f).
class MultiMediaStream {
public:
    void DtorBase();                                         // ~MultiMediaStream() D2
    void DtorDelete();
    bool Open(IStream* s, u64 start, u64 end, MultiMediaLoopParam* loop);   // Open(IStream*, unsigned long, unsigned long, LoopParam*)
    bool Open_(IStream* s, bool buffering, u64 start, u64 end, MultiMediaLoopParam* loop);
    void Close();                                            // m_stream = 0, m_bufferingSource = 0
    bool IsReady() const;                                    // slot 2: m_stream != 0
    s64 Tell() const;                                        // slot 3: m_stream->Tell()
    s64 Seek(s64 offset, s32 origin);                        // slot 4
    u64 Read(void* dst, u64 size, u64 count);                // slot 5
    bool IsEnd(s64* status) const;                           // slot 8
    s64 SetLastError(s64 status) const;                      // slot 9: forwards to m_stream
    s64 GetTotalSize() const;                                // slot 12: m_end - m_start
    s64 Lock(void** out, u64 size);                          // slot 19
    s64 Unlock(u64 size);                                    // slot 20
    bool IsBufferingReady() const;                           // slot 22: m_bufferingSource && IsReady()
    void LoopDelegate(u64 a, u64 b);
    bool CalcStartEndPt(s32 dir, u64* start, u64* end) const;

    const void* vtable;              // 0x00: _ZTVN4Aska16MultiMediaStreamE + 0x10
    u8 unk_08[8];                    // 0x08
    s32 m_state;                     // 0x10: Open_ sets 1
    s32 unk_14;                      // 0x14: Open_ sets 0
    u8 unk_18[0x28];                 // 0x18
    IStream* m_stream;               // 0x40: the source stream
    u64 m_start;                     // 0x48
    u64 m_end;                       // 0x50
    MultiMediaLoopParam m_loop;      // 0x58
    u64 unk_78;                      // 0x78: Open_ clears it
    u64 m_loopsDone;                 // 0x80: IsEnd compares m_loop.m_count with it
    s32 unk_88;                      // 0x88: Open_ clears it; IsEnd: 0 at the end
    u16 unk_8c;                      // 0x8c: Open_ clears it
    u8 m_bufferingSource;            // 0x8e: Open(IBufferingStream*): the source buffers itself
    u8 unk_8f;                       // 0x8f
};
static_assert(offsetof(MultiMediaStream, m_state) == 0x10);
static_assert(offsetof(MultiMediaStream, m_stream) == 0x40);
static_assert(offsetof(MultiMediaStream, m_start) == 0x48);
static_assert(offsetof(MultiMediaStream, m_end) == 0x50);
static_assert(offsetof(MultiMediaStream, m_loop) == 0x58);
static_assert(offsetof(MultiMediaStream, m_loopsDone) == 0x80);
static_assert(offsetof(MultiMediaStream, unk_88) == 0x88);
static_assert(offsetof(MultiMediaStream, m_bufferingSource) == 0x8e);

// ==== The read devices ==================================================================================

// Aska::BaseReadDevice: a reader thread (Aska::Thread base) with a request queue; fields from
// InitializeSub / Initialize / GetRequest (read_device.c) and FileReadManager's use (+0x240 / +0x244 /
// +0x249 / +0x24a). Its size is the derived device's (DirectReadDevice: 0x250, FileReadManager's member).
class BaseReadDevice {
public:
    void DtorBase();                                          // ~BaseReadDevice() D2
    // vtable: 0 / 1 destructors, 2 Handler() (the thread), 3 Initialize(int, int, int), 4 FileExists(int) const,
    // 5 FileExists(int, int) const, 6 CalcFileLength(int) const, 7 GetCompressedFileLength(int) const,
    // 8 GetDecompressedFileLength(int) const, 9 GetReadAlign() const, 10 GetType() const,
    // 11 InitProgressParameter(int, void*), 12 SetReadProgress(unsigned long), 13 CalcReadPos(int, unsigned long,
    // unsigned long), 14 LocalGetFileLength(int) const, 15 LocalGetDecompressedFileLength(int) const,
    // 16 LocalCalcExistingFileLength(ReadRequest*) const, 17 LocalInitialize(), 18 ReadMain(ReadRequest*)
    void Handler();                                           // slot 2
    bool Initialize(s32 id, s32 requests, s32 priority);      // slot 3: InitializeSub, else tear down
    bool FileExists(s32 file) const;                          // slot 4
    s32 GetType() const;                                      // slot 10
    bool InitializeSub(s32 id, s32 requests, s32 priority);   // the request pool (0x80 bytes each), the event, the thread
    void Finalize();
    void CancelAll();
    bool Read(void* request);                                 // Read(ReadRequest*)
    void* GetRequest();                                       // the next queued request; sets m_isIdle when none
    bool Cancel(s32 file);

    const void* vtable;                     // 0x00: (Aska::Thread base) the device's vtable
    u64 m_thread;                           // 0x08: (Aska::Thread base) the guest pthread_t
    u8 unk_10[8];                           // 0x10
    FastCriticalSection m_queueCs;          // 0x18: Aska::FastCriticalSection (sync): the request queue's lock (lock word 0x50)
    FastCriticalSection m_poolCs;           // 0xa8: Aska::FastCriticalSection (sync): the request pool's lock (lock word 0xe0)
    u8 unk_138[8];                          // 0x138
    u8 m_queue[0x68];                       // 0x140: the queued requests (ReadRequestList: empty when +0x10 == this + 0x140)
    u32 m_freeHead;                         // 0x1a8: free-request ring: next slot to fill
    u32 m_freeTail;                         // 0x1ac
    u32 m_freeCapacity;                     // 0x1b0: = the request count
    u8 unk_1b4[4];                          // 0x1b4
    void** m_freeRing;                      // 0x1b8: request pointers (after the requests in the pool block)
    void* m_decompressNotifies;             // 0x1c0: BaseReadDevice::DecompressNotify[count] (0x20 each)
    void* m_requestPool;                    // 0x1c8: new[](count * 0x80): ReadRequest[count] (0x58 each), the ring, the notifies
    u32 unk_1d0;                            // 0x1d0
    s32 m_requestCount;                     // 0x1d4
    Event m_wakeEvent;                      // 0x1d8: Aska::Event (sync): wakes the thread
    s32 m_priority;                         // 0x240: FileReadManager keeps devices sorted by it (descending)
    s32 m_deviceId;                         // 0x244: FileReadManager::GetDevice(id); < 0 not addable
    u8 unk_248;                             // 0x248
    u8 m_isActive;                          // 0x249: InitializeSub succeeded (GetReadableDevice)
    u8 m_isIdle;                            // 0x24a: no queued request (FileReadManager::IsEmpty)
    u8 m_quit;                              // 0x24b: Initialize's failure path: stop the thread
    u8 unk_24c[4];                          // 0x24c
};
static_assert(offsetof(BaseReadDevice, m_queueCs) == 0x18);
static_assert(offsetof(BaseReadDevice, m_poolCs) == 0xa8);
static_assert(offsetof(BaseReadDevice, m_queue) == 0x140);
static_assert(offsetof(BaseReadDevice, m_freeHead) == 0x1a8);
static_assert(offsetof(BaseReadDevice, m_freeCapacity) == 0x1b0);
static_assert(offsetof(BaseReadDevice, m_freeRing) == 0x1b8);
static_assert(offsetof(BaseReadDevice, m_requestPool) == 0x1c8);
static_assert(offsetof(BaseReadDevice, m_requestCount) == 0x1d4);
static_assert(offsetof(BaseReadDevice, m_wakeEvent) == 0x1d8);
static_assert(offsetof(BaseReadDevice, m_priority) == 0x240);
static_assert(offsetof(BaseReadDevice, m_deviceId) == 0x244);
static_assert(offsetof(BaseReadDevice, m_isActive) == 0x249);
static_assert(offsetof(BaseReadDevice, m_isIdle) == 0x24a);
static_assert(sizeof(BaseReadDevice) == 0x250);  // = DirectReadDevice's (FileReadManager embeds one at +8, its devices start at +0x258)

// Aska::FileReadManager (Global::m_pFileReadManager): the device list; layout from AddDevice / GetDevice /
// GetDeviceByIndex / IsEmpty / the destructor (read_device.c).
class FileReadManager {
public:
    void DtorBase();                                                          // ~FileReadManager() D2
    bool AddDevice(BaseReadDevice* d);                                        // at most 3, sorted by m_priority
    bool RemoveDevice(BaseReadDevice* d);
    BaseReadDevice* GetDevice(s32 id);                                        // by m_deviceId
    BaseReadDevice* GetDeviceByIndex(s32 i);                                  // m_devices[i]
    BaseReadDevice* GetReadableDevice(s32 file);
    bool IsEmpty() const;                                                     // every device m_isIdle
    bool FileExists(s32 file) const;
    s64 CalcFileLength(s32 file) const;
    bool Read(s32 file, u8* dst, void* notify, u64 size, u64 offset, s32 a, s32 b, bool c);  // Read(int, unsigned char*, INotify*, ...)
    bool Read(const char* path, u8* dst, void* notify, u64 size, u64 offset, s32 a, s32 b, bool c, bool asset);
    static bool FileExists(const char* path, bool asset);
    static s64 CalcFileLength(const char* path, bool asset);

    const void* vtable;             // 0x00: _ZTVN4Aska15FileReadManagerE + 0x10
    BaseReadDevice m_direct;        // 0x08: Aska::DirectReadDevice (EnableDirectReadDevice)
    BaseReadDevice* m_devices[3];   // 0x258
    s32 m_numDevices;               // 0x270
    u8 unk_274[4];                  // 0x274
};
static_assert(offsetof(FileReadManager, m_direct) == 0x08);
static_assert(offsetof(FileReadManager, m_devices) == 0x258);
static_assert(offsetof(FileReadManager, m_numDevices) == 0x270);
static_assert(sizeof(FileReadManager) == 0x278);

// Aska::DecompressQueue (Global::m_pDecompressQueue): guest size 0xa0 (constructor, queues.c).
class DecompressQueue {
public:
    void Ctor(s32 n);                                          // DecompressQueue(int): new DecompressThread (0x140), Thread::Create
    void Dtor();
    u32 GetSize() const;                                       // the thread's ring: queued elements
    bool IsEmpty() const;
    bool Add(const void* src, void* info, s32 prio, void* notify, void* m0, void* m1, void* m2, void* m3);  // Add(void const*, DecompressInfo*, int, INotify*, IMemoryManager* x4)
    void Clear();

    void* m_thread;                          // 0x00: Aska::DecompressThread* (0x140; ring head +0x98, tail +0x9c, capacity +0xa0)
    FastCriticalSection m_cs;                // 0x08: Aska::FastCriticalSection (sync)
    u32 unk_98;                              // 0x98: the constructor clears it
    u8 m_running;                            // 0x9c: the thread started
    u8 unk_9d[3];                            // 0x9d
};
static_assert(offsetof(DecompressQueue, m_cs) == 0x08);
static_assert(offsetof(DecompressQueue, m_running) == 0x9c);
static_assert(sizeof(DecompressQueue) == 0xa0);

// ==== The framework's loaders and the resource cache ====================================================

// Framework::CFileLoader: a file read into one buffer, by file number (FileReadManager) or by path
// ("direct file"); guest size 0xc0 (CResourceElement's base; CResourceElement's own fields start at +0xc0).
// Layout from the constructor, Initialize, InitializeByDirectFile, Release, the accessors (file_loader.c).
// It is the read's Aska::INotify: vtable slot 0 Handler(unsigned long) ends the load (and decrypts through
// the static m_DecryptFunction, a std::function).
class CFileLoader {
public:
    void CtorBase();                                            // CFileLoader() C2
    void DtorBase();                                            // ~CFileLoader() D2
    void DtorDelete();                                          // ~CFileLoader() D0
    // vtable: 0 Handler(unsigned long), 1 / 2 destructors, 3 Initialize(unsigned, unsigned long, bool),
    // 4 InitializeByDirectFile(char const*, unsigned long, bool), 5 pBuffer() const
    void Handler(u64 status);                                   // slot 0
    void Initialize(u32 fileNumber, u64 align, bool high);      // slot 3
    void InitializeByDirectFile(const char* path, u64 align, bool high);  // slot 4
    const u8* pBuffer() const;                                  // slot 5: m_pBuffer + m_bufferOffset
    void Release();                                             // frees the buffer (DeleteManager), closes the direct file
    void DummySize(u64 n);                                      // m_dummySize (before Initialize)
    void EnableDirectLoad(const char* folder);                  // m_directLoadFolder
    const char* pDirectOpenedFileRelativeName() const;          // m_directRelativeName
    s32 FileNumber() const;                                     // m_fileNumber
    const char* pFileName() const;                              // m_directRelativeName or FileID::gpFileName(m_fileNumber)
    CHash32Bytes FileNameHash() const;                          // x8: m_directNameHash (direct files)
    u64 BufferOffset() const;                                   // m_bufferOffset
    u64 Size() const;                                           // m_size - m_bufferOffset
    const u8* pBufferTop() const;                               // m_pBuffer
    bool IsLoading() const;                                     // m_isLoading
    void SwapBufferPointer(void* buf, u64 size);                // delete[] m_pBuffer; take buf
    void DirectReleaseBuffer(bool now);
    static bool gIsFileExist(const char* path, const char* folder);
    static void SetDefaultDirectLoadFolder(const char* folder); // gpDefalutDirectLoadRootFolder (a String*)
    static bool IsAssetManagerPath(const char* path);

    const void* vtable;              // 0x00: _ZTVN9Framework11CFileLoaderE + 0x10 (or the derived class's)
    s32 m_fileNumber;                // 0x08: -1 uninitialized, -2 a direct file
    u8 unk_0c[4];                    // 0x0c
    const char* m_pFileName;         // 0x10: FileID::gpFileName(n), or "DummyFileByDirectFile"
    u8* m_pBuffer;                   // 0x18: new[] / gMAllocHigh(m_size + m_dummySize, align)
    u64 m_size;                      // 0x20: the file's length
    u64 m_dummySize;                 // 0x28: extra zeroed bytes after the data
    u8 m_isLoading;                  // 0x30: set by Initialize*, cleared by Handler
    u8 unk_31[7];                    // 0x31
    File m_directFile;               // 0x38: Aska::File (closed by Release when m_isDirectOpened)
    String m_directRelativeName;     // 0x50: the name InitializeByDirectFile was given
    String m_directPath;             // 0x68: the folder + the name: what is read
    String m_directLoadFolder;       // 0x80: EnableDirectLoad's folder (else the default root folder)
    u8 m_isDirectOpened;             // 0x98
    u8 unk_99[7];                    // 0x99
    CHash32Bytes m_directNameHash;   // 0xa0: CHash32(m_directRelativeName)
    u8 unk_b0;                       // 0xb0: the constructor sets 1
    u8 unk_b1[7];                    // 0xb1
    u64 m_bufferOffset;              // 0xb8: pBuffer() = m_pBuffer + this
};
static_assert(offsetof(CFileLoader, m_fileNumber) == 0x08);
static_assert(offsetof(CFileLoader, m_pFileName) == 0x10);
static_assert(offsetof(CFileLoader, m_pBuffer) == 0x18);
static_assert(offsetof(CFileLoader, m_size) == 0x20);
static_assert(offsetof(CFileLoader, m_dummySize) == 0x28);
static_assert(offsetof(CFileLoader, m_isLoading) == 0x30);
static_assert(offsetof(CFileLoader, m_directFile) == 0x38);
static_assert(offsetof(CFileLoader, m_directRelativeName) == 0x50);
static_assert(offsetof(CFileLoader, m_directPath) == 0x68);
static_assert(offsetof(CFileLoader, m_directLoadFolder) == 0x80);
static_assert(offsetof(CFileLoader, m_isDirectOpened) == 0x98);
static_assert(offsetof(CFileLoader, m_directNameHash) == 0xa0);
static_assert(offsetof(CFileLoader, m_bufferOffset) == 0xb8);
static_assert(sizeof(CFileLoader) == 0xc0);

// Framework::CResourceElement::tMemoryDescription: 3 bytes, from tMemoryDescription::Create(high, archive,
// mapping), which sets at most one: byte 0 high & plain, byte 1 high & archive, byte 2 high & mapping.
struct tMemoryDescription {
    u8 m_high;          // 0x00: CFileLoader::Initialize's `high` (gMAllocHigh)
    u8 m_highArchive;   // 0x01: PhaseLoadingFinish: DecompressInfo flag 2
    u8 m_highMapping;   // 0x02
};
static_assert(sizeof(tMemoryDescription) == 3);

// Framework::CResourceElement::tMappingImage: 0x30 bytes (vector element: CResourceElement::Release,
// pFindMappingImage, the destructor).
struct tMappingImage {
    void* m_image;      // 0x00: freed through DeleteManager::AddMain by Release
    u8 unk_08[8];       // 0x08
    String m_name;      // 0x10: pFindMappingImage compares it
    u8 unk_28[8];       // 0x28
};
static_assert(offsetof(tMappingImage, m_name) == 0x10);
static_assert(sizeof(tMappingImage) == 0x30);

class CResourceElement;

// Framework::CResourceElement::CFinishNotify: the decompression's INotify; 0x18 bytes at CResourceElement+0x120.
struct CFinishNotify {
    const void* vtable;           // 0x00: _ZTVN9Framework16CResourceElement13CFinishNotifyE + 0x10 (slot 0 Handler)
    u8 m_done;                    // 0x08: Handler(0) sets it (after SwapBufferPointer)
    u8 unk_09[7];                 // 0x09
    CResourceElement* m_owner;    // 0x10
};
static_assert(offsetof(CFinishNotify, m_done) == 0x08);
static_assert(offsetof(CFinishNotify, m_owner) == 0x10);
static_assert(sizeof(CFinishNotify) == 0x18);

// Framework::CResourceElement: a CFileLoader that is also an Aska::Task (second base at +0xc0), expanding
// (decompressing) its buffer when loaded; guest size 0x150 (gpInstantiate's operator new for the plain
// types; _Aif / _Lua 0x158). Layout from the constructor, _Initialize, Release, PhaseLoadingFinish,
// SwapDecompressBuffer, the accessors (resource_manager.c). Phases (m_phase): 0 none, 1 loading,
// 2 loaded (Handler), 3 decompressing, 4 expanded, ..., 9 done (IsDone; Done() also removes the task).
// The subclasses (CResourceElement_Aif, _Asf, _Aaf, _Acf, _Bsb, _Lua, _Aet, _Bin, _Apk, _Spk, _Tpk, _Csv, ...)
// are gpInstantiate(type)'s cases.
class CResourceElement {
public:
    void Ctor(u32 type);                                        // CResourceElement(unsigned int) C1
    void DtorBase();                                            // ~CResourceElement() D2
    void DtorDelete();                                          // ~CResourceElement() D0
    // vtable (primary, _ZTV + 0x10): 0 Handler(unsigned long), 1 / 2 destructors, 3 CFileLoader::Initialize,
    // 4 CFileLoader::InitializeByDirectFile, 5 pBuffer() const (forbidden), 6 Align() const (0x20),
    // 7 Initialize(unsigned, tMemoryDescription const&), 8 InitializeByDirectFile(char const*, tMemoryDescription
    // const&, char const*), 9 Run(int), 10 pImage() const, 11 pResourceElement_Bsb(), 12 _Initialize,
    // 13 _InitializeByDirectFile, 14 _InitializeByMemory, 15 pBufferDirect() const, 16 IsExpansionFinished() const,
    // 17 StartExpansion(); the Aska::Task vtable at +0xc0 is _ZTV + 0xb0 (Run at its slot 13 through a thunk).
    void Handler(u64 status);                                   // slot 0: CFileLoader::Handler, PhaseLoadingFinish, 1 -> 2
    static constexpr int kSlotPImage = 10;                      // const u8* pImage() const: the loaded bytes
    u64 Align() const;                                          // slot 6
    void Initialize(u32 fileNumber, const tMemoryDescription* desc);                 // slot 7
    void InitializeByDirectFile(const char* path, const tMemoryDescription* desc, const char* folder);  // slot 8
    void Run(s32 level);                                        // slot 9: the phase machine (a Task)
    const void* pImage() const;                                 // slot 10 (asserts m_phase == 9)
    void _Initialize(u32 fileNumber, u64 align, const tMemoryDescription* desc);     // slot 12: phase 1, TaskManager::Add
    void _InitializeByDirectFile(const char* path, u64 align, const tMemoryDescription* desc, const char* folder);  // slot 13
    void _InitializeByMemory(void* image, const tMemoryDescription* desc);           // slot 14
    bool IsExpansionFinished() const;                           // slot 16
    void StartExpansion();                                      // slot 17
    void Release();                                             // CFileLoader::Release, mapping images, m_phase = 0
    void PhaseLoadingFinish();                                  // compressed: DecompressQueue::Add (phase 3), else phase 4
    void SwapDecompressBuffer();
    u32 Type() const;                                           // m_type
    s32 Phase() const;                                          // m_phase
    bool IsInitialized() const;                                 // m_phase != 0
    bool IsDone() const;                                        // m_phase == 9
    void Done();                                                // m_phase = 9, Task::Remove
    const tMappingImage* pFindMappingImage(const char* name) const;
    static CResourceElement* gpInstantiate(u32 type);           // operator new(nothrow) + the subclass's constructor
    static bool IsArchiveType(u32 type);
    static bool IsRquestMappingMemoryType(u32 type);

    CFileLoader base;                              // 0x000: Framework::CFileLoader
    TaskBytes m_task;                              // 0x0c0: Aska::Task (kernel)
    u32 m_type;                                    // 0x0e8: the resource type (gpInstantiate's switch)
    s32 m_phase;                                   // 0x0ec
    u64 unk_f0;                                    // 0x0f0: Release clears it; PhaseLoadingFinish waits for the load only when 0
    u8 unk_f8[8];                                  // 0x0f8
    libcxx::vector<tMappingImage> m_mappingImages; // 0x100: std::__ndk1::vector (CSTLAllocator)
    u8 unk_118[8];                                 // 0x118
    CFinishNotify m_finishNotify;                  // 0x120
    u64 m_decompressedSize;                        // 0x138: the compressed header's size (+0xc)
    void* m_pDecompressInfo;                       // 0x140: Aska::DecompressInfo (0x28, operator new) while decompressing
    tMemoryDescription m_memDesc;                  // 0x148
    u8 unk_14b[5];                                 // 0x14b
};
static_assert(offsetof(CResourceElement, m_task) == 0xc0);
static_assert(offsetof(CResourceElement, m_type) == 0xe8);
static_assert(offsetof(CResourceElement, m_phase) == 0xec);
static_assert(offsetof(CResourceElement, unk_f0) == 0xf0);
static_assert(offsetof(CResourceElement, m_mappingImages) == 0x100);
static_assert(offsetof(CResourceElement, m_finishNotify) == 0x120);
static_assert(offsetof(CResourceElement, m_decompressedSize) == 0x138);
static_assert(offsetof(CResourceElement, m_pDecompressInfo) == 0x140);
static_assert(offsetof(CResourceElement, m_memDesc) == 0x148);
static_assert(sizeof(CResourceElement) == 0x150);

// Framework::CResourceManager::tElement: a reference-counted handle in the manager's list; 0x10 bytes
// (Initialize / the counters / rResourceElement; the list node is {prev, next, tElement}).
class tElement {
public:
    void Initialize(u32 type, u32 fileNumber, u32 uniqueBitFlag, bool high);      // gpInstantiate + vtable slot 7
    void InitializeByDirectFile(u32 type, const char* path, u32 uniqueBitFlag, bool high);  // slot 8
    void InitializeByDirectFileWithFolder(u32 type, const char* path, const char* folder, u32 flag, bool high);
    void IncrementReferenceCounter();
    bool DecrementReferenceCounter();                           // true at 0
    s32 ReferenceCounter() const;
    void Release();
    void ForceRelease();
    CResourceElement* rResourceElement();                       // (asserts ResourceManager.cpp:0x7e when null)
    const CResourceElement* crResourceElement() const;          // (asserts ResourceManager.cpp:0x84 when null)
    u32 UniqueBitFlag() const;
    void OrUniqueBitFlag(u32 f);
    void AndUniqueBitFlag(u32 f);

    s32 m_referenceCounter;                 // 0x00
    u32 m_uniqueBitFlag;                    // 0x04
    CResourceElement* m_pResourceElement;   // 0x08
};
static_assert(offsetof(tElement, m_uniqueBitFlag) == 0x04);
static_assert(offsetof(tElement, m_pResourceElement) == 0x08);
static_assert(sizeof(tElement) == 0x10);

// Framework::CResourceManager: an Aska::Task holding the loaded resources; guest size 0xf0 (operator new in
// CApplication::CMainTask::Run, which keeps it at CMainTask + 0x60: CMainTask::rResourceManager()).
// Layout from the constructor, Initialize, Run, Add, pSearch, Num (resource_manager.c). Every method takes
// m_mutex (Initialize'ing it lazily).
class CResourceManager {
public:
    void Ctor(const char* name);                                // CResourceManager(char const*) C1
    void Dtor();                                                // ~CResourceManager() D1
    void DtorDelete();                                          // D0
    // vtable (Aska::Task's): 0 / 1 destructors, 2 GetClassID(int) const, 11 GetDefaultLevel() const, 13 Run(int);
    // the rest Aska::Task's
    u64 GetClassID(s32 i) const;                                // slot 2
    s32 GetDefaultLevel() const;                                // slot 11
    void Run(s32 level);                                        // slot 13: done elements with no reference -> CDelayDelete
    void Initialize();                                          // TaskManager::Add, m_isInitialized = 1
    void Release();
    tElement* pSearch(u32 fileNumber);                          // by CFileLoader::FileNumber (the caller holds m_mutex)
    const tElement* pSearch(u32 fileNumber) const;              // (the same; its asserts' lines differ)
    tElement* pSearchByDirectPath(const char* path);            // by pFileName (strcmp)
    const tElement* pSearchByDirectPath(const char* path) const;
    void Add(u32 type, u32 fileNumber, u32 flag, bool high);    // a found element: m_referenceCounter++, flag |= ...
    void AddByName(u32 type, const char* name, u32 flag, bool high);
    void AddDirectFile(u32 type, const char* path, u32 flag, bool high);
    void AddDirectFileWithFolder(u32 type, const char* path, const char* folder, u32 flag, bool high);
    void Remove(u32 fileNumber);
    void RemoveByName(const char* name);
    void RemoveDirectFile(const char* path);
    void RemoveForce(u32 fileNumber);
    void RemoveByUniqueBitFlag(u32 flag);
    bool IsReady(u32 fileNumber, bool* found) const;            // under m_mutex: *found = in the list; true when done
    bool IsReadyDirectFile(const char* path, bool* found) const;
    void Lock();
    void Unlock();
    bool IsLocked() const;
    s32 LockCounter() const;
    CResourceElement* rResourceElement(u32 fileNumber);
    CResourceElement* rResourceElementDirectFile(const char* path);
    const CResourceElement* crResourceElementByIndex(u32 i) const;
    s32 NumLoading() const;                                     // elements not IsDone
    bool IsLoading() const;
    s32 Num() const;                                            // m_elements.size
    s32 NumByUniqueBitFlag(u32 flag) const;

    const void* vtable;                // 0x00: (Aska::Task) _ZTVN9Framework16CResourceManagerE + 0x10
    u8 task_08[0x1f];                  // 0x08: Aska::Task's fields (kernel; its data ends at 0x27)
    u8 m_isInitialized;                // 0x27: in Aska::Task's tail padding
    libcxx::list<tElement> m_elements; // 0x28: std::__ndk1::list (CSTLAllocator; node 0x20: prev, next, tElement)
    CMutex m_mutex;                    // 0x40: Framework::CMutex (sync)
};
static_assert(offsetof(CResourceManager, m_isInitialized) == 0x27);
static_assert(offsetof(CResourceManager, m_elements) == 0x28);
static_assert(offsetof(CResourceManager, m_mutex) == 0x40);
static_assert(sizeof(CResourceManager) == 0xf0);
using ListNodeTElement = libcxx::list_node<tElement>;
static_assert(offsetof(ListNodeTElement, value) == 0x10);
static_assert(sizeof(ListNodeTElement) == 0x20);

// CGameResourceManager (TSingleton<CGameResourceManager>): the client's front for the CResourceManager plus
// the downloaded-file map; layout from the constructor, the destructor, SearchFileMap, IsLoading
// (game_resource_manager.c). Size: the last field ends at 0x70 (no allocation site read).
class CGameResourceManager {
public:
    void Ctor(const char* name);                                // CGameResourceManager(char const*): m_pSubstance = CMainTask::rResourceManager()
    void Dtor();
    void Initialize();
    void Release();
    CResourceManager* pSubstance();
    void AddDirectFile(u32 type, const char* path, u32 flag, bool high, s32 mode);
    const char* ReplaceFileName(const char* name) const;
    const char* SearchFileMap(const char* name) const;          // CHash32(name) -> m_fileMap's TStaticString (else name)
    bool IsFileExist(const char* name, bool download) const;
    bool IsLoading() const;                                     // the downloader's state, then m_pSubstance->IsLoading
    s32 NumLoading() const;
    s32 Num() const;
    s32 CheckResourceStatusByFileName(const char* name, s32 mode) const;

    const void* vtable;                             // 0x00: _ZTV20CGameResourceManager + 0x10
    CResourceManager* m_pSubstance;                 // 0x08
    u8 unk_10[0x10];                                // 0x10: zeroed by the constructor
    void* m_pDownLoader;                            // 0x20: CGameResourceDownloader* (set by Initialize)
    containers::THashMapU32Str256 m_fileMap;        // 0x28: Aska::THashMap<u32, Framework::TStaticString<256>> (17 buckets at first)
    String m_resolutionPath;                        // 0x58: (MakeCurrentResolutionPath)
};
static_assert(offsetof(CGameResourceManager, m_pSubstance) == 0x08);
static_assert(offsetof(CGameResourceManager, m_pDownLoader) == 0x20);
static_assert(offsetof(CGameResourceManager, m_fileMap) == 0x28);
static_assert(offsetof(CGameResourceManager, m_resolutionPath) == 0x58);
static_assert(sizeof(CGameResourceManager) == 0x70);
using FileMapBucket = containers::THashMapBucket<containers::TPair<u32, containers::TStaticString<256>>>;
static_assert(sizeof(FileMapBucket) == 0x108);  // SearchFileMap's stride; key at +4, the name at +8

// CGameResourceDownloader: the asset downloader (a Framework::CFiberUnit, kernel); the fields from the
// constructor and the state accessors (downloader.c). Only what those show is named; the rest is padding.
// Size: the last field the constructor writes ends at 0x5e8 (no allocation site read).
class CGameResourceDownloader {
public:
    void CtorBase();                                            // CGameResourceDownloader() C2: CFiberUnit(0x600)
    bool IsReadyDownload() const;                               // m_readyFlag || m_isReady
    bool IsReadyDownloadFlag() const;                           // m_readyFlag
    bool IsIdele() const;                                       // m_mode == 0 (sic)
    bool IsModeDownload() const;                                // m_mode == 4
    bool IsDownloading() const;                                 // !m_isReady && m_downloading.m_size
    bool IsErrorStatus() const;                                 // m_errorStatus != 0
    s32 NumDownloading() const;
    s32 NumNodeDownloading() const;
    void Progress();                                            // the fiber's step (hot: Progress_Setup / _Download)
    void Progress_Setup();
    void Progress_Download();

    kernel::CFiberUnit fiberUnit;                               // 0x000: Framework::CFiberUnit (kernel)
    u8 unk_038[8];                                              // 0x038: unknown (see kernel::CFiberUnit above)
    containers::TArray<void*, false> m_nodes;                   // 0x040: TArray<CDownloadNode*, false>
    containers::TArray<void*, false> m_downloading;             // 0x078: TArray<CDownloadNode*, false> (node +0x190: its state)
    containers::TArray<u8, false> m_nodeInitializers;           // 0x0b0: TArray<tDownloadNodeInitializer, false>
    u8 unk_0e8[0x50];                                           // 0x0e8: zeroed by the constructor
    f32 unk_138;                                                // 0x138: 1.0
    u8 unk_13c[4];                                              // 0x13c
    u64 unk_140;                                                // 0x140
    u8 unk_148[4];                                              // 0x148
    s32 m_mode;                                                 // 0x14c: 0 idle, 4 downloading (IsModeDownload)
    u8 unk_150[4];                                              // 0x150
    u8 m_isReady;                                               // 0x154: the constructor sets 1
    u8 unk_155;                                                 // 0x155
    u8 m_readyFlag;                                             // 0x156
    u8 unk_157[9];                                              // 0x157: 1, 1, 0, 0, 1, ... (the constructor)
    s64 m_errorStatus;                                          // 0x160: Aska::Status; != 0 an error
    u8 unk_168[8];                                              // 0x168
    CMutex m_mutex;                                             // 0x170: Framework::CMutex (sync)
    u8 unk_220[0x60];                                           // 0x220: +0x221 a flag, 0x238.. zeroed (0x44 bytes)
    data_formats::ASON m_ason[3];                               // 0x280: Aska::ASON x3 (the manifests / version JSON)
    u8 unk_430[0x18];                                           // 0x430: zeroed by the constructor
    containers::TArray<containers::TStaticString<256>, false> m_names;  // 0x448: TArray<TStaticString<256>, false>
    u8 unk_480[0x168];                                          // 0x480: zeroed by the constructor (+0x5a8: a flag CGameResourceManager::IsLoading reads)
};
static_assert(offsetof(CGameResourceDownloader, m_nodes) == 0x40);
static_assert(offsetof(CGameResourceDownloader, m_downloading) == 0x78);
static_assert(offsetof(CGameResourceDownloader, m_nodeInitializers) == 0xb0);
static_assert(offsetof(CGameResourceDownloader, m_mode) == 0x14c);
static_assert(offsetof(CGameResourceDownloader, m_isReady) == 0x154);
static_assert(offsetof(CGameResourceDownloader, m_readyFlag) == 0x156);
static_assert(offsetof(CGameResourceDownloader, m_errorStatus) == 0x160);
static_assert(offsetof(CGameResourceDownloader, m_mutex) == 0x170);
static_assert(offsetof(CGameResourceDownloader, m_ason) == 0x280);
static_assert(offsetof(CGameResourceDownloader, m_names) == 0x448);
static_assert(sizeof(CGameResourceDownloader) == 0x5e8);

// ==== Key-value store ===================================================================================

// Aska::Cryption::TChaCha20<false>: the LocalKVS's cipher state (0x80 bytes at LocalKVS + 0x100): the 16-word
// ChaCha20 input block (constant "expand 32-byte k", the 32-byte key, the counter, the 12-byte nonce) and
// keystream bytes. Layout from LocalKVS::SetCipher and CGameLocalKVS's inlined construction.
struct ChaCha20State {
    u8 m_constant[16];  // 0x00: TChaCha20<false>::TChaCha20()::constant ("expand 32-byte k")
    u8 m_key[32];       // 0x10: SetCipher's key (or a key derived from the device id)
    u32 m_counter;      // 0x30: SetCipher sets 0
    u8 m_nonce[12];     // 0x34
    u8 unk_40[0x40];    // 0x40: the keystream block (not read here)
};
static_assert(offsetof(ChaCha20State, m_key) == 0x10);
static_assert(offsetof(ChaCha20State, m_counter) == 0x30);
static_assert(offsetof(ChaCha20State, m_nonce) == 0x34);
static_assert(sizeof(ChaCha20State) == 0x80);

// Aska::LocalKVS (Global::m_pLocalKVS; CGameLocalKVS's "Game" store): a named key-value store on Android's
// SharedPreferences (the *Android methods), optionally ChaCha20-encrypted; guest size 0x188 (CGameLocalKVS's
// operator new). Layout from Init / SetKVSName / SetCipher / GetBinary (local_kvs.c). Status results through x8.
class LocalKVS {
public:
    s64 Init(const char* name, bool cipher, char* key, char* nonce);          // x8 Status: strcpy(m_name), SetCipher
    s64 SetKVSName(const char* name);                                         // x8 Status
    s64 SetCipher(bool on, char* key, char* nonce);                           // x8 Status
    s64 SetBinary(const char* key, const s8* data, s64 size);                 // x8 Status
    // GetBinary(char const*, long*) const: x8 = TSharedArray<signed char> (the value), *size or the Status
    s64 Clear(const char* key);
    s64 ClearAll();

    char m_name[0x100];        // 0x000: the store's name (< 0x100 chars; "" until Init)
    ChaCha20State m_cipher;    // 0x100
    u8 m_keyReady;             // 0x180: SetCipher set the key
    u8 m_keyDerived;           // 0x181: SetCipher: the key / nonce were given or derived (both set 1)
    u8 unk_182[2];             // 0x182: cleared with m_keyReady (a u16 store)
    u8 m_cipherEnabled;        // 0x184: SetCipher's first argument: keys and values are encrypted
    u8 unk_185[3];             // 0x185
};
static_assert(offsetof(LocalKVS, m_cipher) == 0x100);
static_assert(offsetof(LocalKVS, m_keyReady) == 0x180);
static_assert(offsetof(LocalKVS, m_keyDerived) == 0x181);
static_assert(offsetof(LocalKVS, m_cipherEnabled) == 0x184);
static_assert(sizeof(LocalKVS) == 0x188);

// CGameLocalKVS (TSingleton<CGameLocalKVS>): owns the "Game" LocalKVS; layout from the constructor,
// pSubstance, Result, the destructor (local_kvs.c). Size: the last field ends at 0x20.
class CGameLocalKVS {
public:
    void Ctor();                                         // new LocalKVS (0x188), Init("Game", true), _VersionCheck x2
    void Dtor();
    LocalKVS* pSubstance() const;                        // m_pKVS
    const s64* Result() const;                           // &m_result
    void VersionCheck();
    void VersionUpdate();
    // template Get<T>(char const*, T const&) / Set<T>(char const*, T const&) for bool, int, unsigned, unsigned long, String

    const void* vtable;  // 0x00: _ZTV13CGameLocalKVS + 0x10
    LocalKVS* m_pKVS;    // 0x08
    s64 m_result;        // 0x10: Aska::Status of the last operation (Init's)
    u8 unk_18;           // 0x18: the constructor clears it
    u8 unk_19[7];        // 0x19
};
static_assert(offsetof(CGameLocalKVS, m_pKVS) == 0x08);
static_assert(offsetof(CGameLocalKVS, m_result) == 0x10);
static_assert(sizeof(CGameLocalKVS) == 0x20);

// ==== The shader cache (Aska::AHSL*) ======================================================================

// Aska::AHSLDatabase<T, 9>: a lock and a two-level table keyed by shader keys: 2^9 buckets chosen by the key's
// first 9 bits (bytes 0..1), each with up to m_capacity one-byte tags (byte 1 << 1 | byte 2 >> 7) and the
// matching {key, data} entries; 8 of each inline, more in m_ext. Layout from GetData / GetNodeCount /
// GetNodeDirect and the construction inlined in AHSLCacheManagerV2's constructor (ahsl.c).
struct AHSLTagBucket {
    u8* m_extTags;       // 0x00: when not null, the tags (else m_tags)
    u16 m_capacity;      // 0x08: 8 at construction
    u16 m_count;         // 0x0a
    u8 unk_0c[4];        // 0x0c
    u64 unk_10;          // 0x10: 0 at construction
    u8 m_tags[8];        // 0x18
};
static_assert(offsetof(AHSLTagBucket, m_capacity) == 0x08);
static_assert(offsetof(AHSLTagBucket, m_tags) == 0x18);
static_assert(sizeof(AHSLTagBucket) == 0x20);

template <typename T>
struct AHSLEntry {
    const u8* m_key;     // 0x00: the shader key (its bytes from 2 on are compared)
    T* m_data;           // 0x08: GetData's result
};

template <typename T>
struct AHSLNode {
    AHSLEntry<T>* m_ext;       // 0x00: when not null, the entries (else m_entries)
    u16 m_capacity;            // 0x08: 8 at construction
    u16 m_count;               // 0x0a: GetData scans this many; GetNodeCount(i)
    u8 unk_0c[4];              // 0x0c
    u64 unk_10;                // 0x10
    AHSLEntry<T> m_entries[8]; // 0x18
};

template <typename T>
class AHSLDatabase {
public:
    T* GetData(const u8* key);                        // GetData(unsigned char const*): under m_cs
    bool SetData(u8* key, T* data);
    bool DeleteData(u8* key, T* data);
    s32 GetNodeCount(s32 bucket) const;               // m_nodes[bucket].m_count
    T* GetNodeDirect(s32 bucket, s32 i);              // the i-th entry's data
    void DeleteAll();

    FastCriticalSection m_cs;           // 0x00000: Aska::FastCriticalSection (sync; lock word at +0x38)
    AHSLTagBucket m_tags[512];          // 0x00090
    AHSLNode<T> m_nodes[512];           // 0x04090
    u32 m_count;                        // 0x17090
    u8 unk_17094[4];                    // 0x17094
};
struct ShaderCache;      // Aska::ShaderCache (render's; opaque here)
struct ShaderDiskCache;  // Aska::ShaderDiskCache (render's; opaque here)
using AHSLDatabaseShaderCache = AHSLDatabase<ShaderCache>;          // Aska::AHSLDatabase<Aska::ShaderCache, (unsigned char)9>
using AHSLDatabaseShaderDiskCache = AHSLDatabase<ShaderDiskCache>;  // Aska::AHSLDatabase<Aska::ShaderDiskCache, (unsigned char)9>
using AHSLNodeShaderCache = AHSLNode<ShaderCache>;
static_assert(sizeof(AHSLEntry<ShaderCache>) == 0x10);
static_assert(offsetof(AHSLNodeShaderCache, m_count) == 0x0a);
static_assert(offsetof(AHSLNodeShaderCache, m_entries) == 0x18);
static_assert(sizeof(AHSLNodeShaderCache) == 0x98);
static_assert(offsetof(AHSLDatabaseShaderCache, m_tags) == 0x90);
static_assert(offsetof(AHSLDatabaseShaderCache, m_nodes) == 0x4090);
static_assert(offsetof(AHSLDatabaseShaderCache, m_count) == 0x17090);
static_assert(sizeof(AHSLDatabaseShaderCache) == 0x17098);

// Aska::AHSLCacheManagerV2: the shader cache (L1: compiled shaders, L2: the disk cache), an Aska::Thread
// (the background compiler); the live one is the Aska::AofAhslManager at Global::m_pShaderLinkManager + 8 (derived:
// its fields go on past 0x30b60, e.g. the error shaders at +0x30da0 / +0x30dc0). Layout from the constructor,
// Init, Tick (ahsl.c); only the members those show. Size: AofAhslManager's (not read).
class AHSLCacheManagerV2 {
public:
    void Ctor();                                                 // AHSLCacheManagerV2() C1 (also builds a 3 MB MemoryManager heap)
    bool Init();                                                 // the disk-cache header, the event, Thread::Create, AttachDiskCache(0, 1)
    void Tick();                                                 // per frame: m_frame++, hands a pending request to the thread
    ShaderCache* SearchOrCompile(const u8* key, s32* status);    // hot
    ShaderCache* SearchBindedVS(ShaderCache* ps, u64 key, s32 i);// hot
    void AddToL1Cache(const ShaderDiskCache* a, const ShaderDiskCache* b);
    void Handler();                                              // the thread

    const void* vtable;                           // 0x00000: (Aska::Thread base) _ZTVN4Aska18AHSLCacheManagerV2E + 0x10 (or AofAhslManager's)
    u64 m_thread;                                 // 0x00008: (Aska::Thread base)
    u8 unk_10[8];                                 // 0x00010
    u64 unk_18;                                   // 0x00018: 0
    s32 m_targetConsole;                          // 0x00020: -1, then Init: Aska::s_eTC
    u8 unk_24[4];                                 // 0x00024
    u64 unk_28;                                   // 0x00028: 0
    AHSLDatabaseShaderCache m_l1;                 // 0x00030: the compiled shaders (SearchOrCompile's lookup)
    memory::MemoryManager m_l1Heap;               // 0x170c8: Aska::MemoryManager over a 0x300000-byte block (+0x17268)
    u8 unk_171b8[0x0c];                           // 0x171b8
    s32 m_frame;                                  // 0x171c4: Tick's counter (2 at construction)
    FastCriticalSection m_l1Cs;                   // 0x171c8: Aska::FastCriticalSection (sync)
    u8 unk_17258[0x2660];                         // 0x17258: the file-cache header (0x17490..), the key work area (0x174b0, 0x2000 bytes), ...
    AHSLDatabaseShaderDiskCache m_l2;             // 0x198b8: the disk cache's entries
    u8 unk_30950[0x20];                           // 0x30950
    FastCriticalSection m_l2Cs;                   // 0x30970: Aska::FastCriticalSection (sync)
    u8 unk_30a00[0x18];                           // 0x30a00
    u8 m_requestPending;                          // 0x30a18: Tick: set -> signal m_requestEvent, wait m_doneEvent, clear
    u8 unk_30a19[7];                              // 0x30a19
    Event m_requestEvent;                         // 0x30a20: Aska::Event (sync)
    Event m_doneEvent;                            // 0x30a88: Aska::Event (sync)
    u8 unk_30af0[8];                              // 0x30af0
    Event m_threadEvent;                          // 0x30af8: Aska::Event (sync; Init creates it)
};
static_assert(offsetof(AHSLCacheManagerV2, m_targetConsole) == 0x20);
static_assert(offsetof(AHSLCacheManagerV2, m_l1) == 0x30);
static_assert(offsetof(AHSLCacheManagerV2, m_l1Heap) == 0x170c8);
static_assert(offsetof(AHSLCacheManagerV2, m_frame) == 0x171c4);
static_assert(offsetof(AHSLCacheManagerV2, m_l1Cs) == 0x171c8);
static_assert(offsetof(AHSLCacheManagerV2, m_l2) == 0x198b8);
static_assert(offsetof(AHSLCacheManagerV2, m_l2Cs) == 0x30970);
static_assert(offsetof(AHSLCacheManagerV2, m_requestPending) == 0x30a18);
static_assert(offsetof(AHSLCacheManagerV2, m_requestEvent) == 0x30a20);
static_assert(offsetof(AHSLCacheManagerV2, m_doneEvent) == 0x30a88);
static_assert(offsetof(AHSLCacheManagerV2, m_threadEvent) == 0x30af8);
static_assert(sizeof(AHSLCacheManagerV2) == 0x30b60);  // the members shown end here; the live object is larger (AofAhslManager)

// Aska::ShaderLinkManager (Global::m_pShaderLinkManager): guest size 0x30e78 (operator new in
// Global::InstantiateShaderLinkManager, which also shows the members): an AofAhslManager (an
// AHSLCacheManagerV2 with more fields) at +8 and a FilterShaderManager.
class ShaderLinkManager {
public:
    static bool InstantiateShaderLinkManager();   // Aska::Global::InstantiateShaderLinkManager()

    const void* vtable;              // 0x00000: _ZTVN4Aska17ShaderLinkManagerE + 0x10
    u8 m_aofAhsl[0x30e50];           // 0x00008: Aska::AofAhslManager (its AHSLCacheManagerV2 part: the class above)
    u8 m_filterShaders[0x18];        // 0x30e58: Aska::FilterShaderManager
    u32 unk_30e70;                   // 0x30e70: 0
    u8 unk_30e74[4];                 // 0x30e74
};
static_assert(offsetof(ShaderLinkManager, m_aofAhsl) == 0x08);
static_assert(offsetof(ShaderLinkManager, m_filterShaders) == 0x30e58);
static_assert(offsetof(ShaderLinkManager, unk_30e70) == 0x30e70);
static_assert(sizeof(ShaderLinkManager) == 0x30e78);
static_assert(sizeof(AHSLCacheManagerV2) <= sizeof(ShaderLinkManager::m_aofAhsl));

// ==== Aska::LIBLManager (the light-baked textures) ========================================================

// Aska::LIBLManager (Global::m_pLIBLManager): the members its destructor and CopyTexture (the hottest
// resource function) show; an Aska::IAnimatable at 0 (vtable). Mostly render's business: the rest is padding.
// Size: the last member the destructor names ends at 0x930 or later (not confirmed).
class LIBLManager {
public:
    void Dtor();                                      // ~LIBLManager() D2
    void Initialize(s32 n);                           // m_loaderPool.SecurePool(n)
    void Update();
    void CopyTexture();                               // hot (427 samples): under m_cs
    bool Get(u64 id, void* out) const;                // IAnimatable's Get / Set
    bool Set(u64 id, const void* in);

    const void* vtable;                                       // 0x000: _ZTVN4Aska11LIBLManagerE + 0x10
    u8 unk_008[0x588];                                        // 0x008
    FastCriticalSection m_cs;                                 // 0x590: Aska::FastCriticalSection (sync; lock word 0x5c8 in CopyTexture)
    containers::TPoolLegacy<u8> m_loaderPool;                 // 0x620: TPoolLegacy<_AarLoaderElem, false>
    u8 m_loaderList[0x20];                                    // 0x670: LIBLManager::_AarLoaderList (a TList<_AarLoaderElem>; its sentinel is an _AarLoaderElem: vtable at 0x678)
    u8 m_blendTextureLoader[0x258];                           // 0x690: Aska::AarLoaderForBlendTexture
    TaskBytes m_updateTask;                                   // 0x8e8: _AarLoaderUpdateTask (an Aska::Task)
    const void* m_detachHandlerVtable;                        // 0x910: AarTextureCommon::DetachTextureHandler
    const void* m_textureHandlerVtable;                       // 0x918: Aska::ITextureHandler (DetachTexture)
    u8 unk_920[8];                                            // 0x920
    u8 m_barrier[8];                                          // 0x928: Aska::TBarrierSlim<true> (size not read)
};
static_assert(offsetof(LIBLManager, m_cs) == 0x590);
static_assert(offsetof(LIBLManager, m_loaderPool) == 0x620);
static_assert(offsetof(LIBLManager, m_loaderList) == 0x670);
static_assert(offsetof(LIBLManager, m_blendTextureLoader) == 0x690);
static_assert(offsetof(LIBLManager, m_updateTask) == 0x8e8);
static_assert(offsetof(LIBLManager, m_detachHandlerVtable) == 0x910);
static_assert(offsetof(LIBLManager, m_barrier) == 0x928);

// Aska::ResourceReadyQueue (Global::m_pResourceReadyQueue): an Aska::Thread preparing streams for the
// loaders; the members its constructor and Init show (queues.c). Size not confirmed.
class ResourceReadyQueue {
public:
    void Ctor(u32 n);                                  // ResourceReadyQueue(unsigned int)
    bool Init(u32 a, u32 b);
    void Term();
    bool IsBusy() const;
    bool IsReady() const;
    void Handler();                                    // the thread
    void Sequencer(void* item);                        // hot: one EvItem's state machine

    const void* vtable;                           // 0x000: (Aska::Thread base) _ZTVN4Aska18ResourceReadyQueueE + 0x10
    u64 m_thread;                                 // 0x008: (Aska::Thread base)
    u8 unk_10;                                    // 0x010
    u8 m_initialized;                             // 0x011: Init returns at once when set
    u8 unk_12;                                    // 0x012
    u8 unk_13[5];                                 // 0x013
    Event m_event;                                // 0x018: Aska::Event (sync; Create(true, true))
    CriticalSection m_cs;                         // 0x080: Aska::CriticalSection (sync)
    u32 unk_a8;                                   // 0x0a8
    u8 unk_ac[4];                                 // 0x0ac
    const void* m_portVtable;                     // 0x0b0: Aska::TEventPort<EvItem>
    u8 unk_b8[0x18];                              // 0x0b8
    containers::TSharedPointer<u8> m_queue;       // 0x0d0: TSharedPointer<TEventQueue<EvItem>> (Init: new 0x78)
    u8 unk_e0[0x20];                              // 0x0e0
    const void* m_fakeStreamVtable;               // 0x100: an Aska::FakeStream (0x38)
    u8 unk_108[0x30];                             // 0x108
    const void* m_fakeStream2Vtable;              // 0x138: a second Aska::FakeStream
    u8 unk_140[0x40];                             // 0x140
    containers::TSharedPointer<s8> m_work;        // 0x180: TSharedArray<signed char> (0x1000 bytes)
    s8* m_workData;                               // 0x190
    u32 m_workSize;                               // 0x198: 0x1000
    u8 unk_19c[0x80];                             // 0x19c
    u32 unk_21c;                                  // 0x21c: 0x10
    CriticalSection m_cs2;                        // 0x220: Aska::CriticalSection (sync)
};
static_assert(offsetof(ResourceReadyQueue, m_initialized) == 0x11);
static_assert(offsetof(ResourceReadyQueue, m_event) == 0x18);
static_assert(offsetof(ResourceReadyQueue, m_cs) == 0x80);
static_assert(offsetof(ResourceReadyQueue, m_portVtable) == 0xb0);
static_assert(offsetof(ResourceReadyQueue, m_queue) == 0xd0);
static_assert(offsetof(ResourceReadyQueue, m_fakeStreamVtable) == 0x100);
static_assert(offsetof(ResourceReadyQueue, m_fakeStream2Vtable) == 0x138);
static_assert(offsetof(ResourceReadyQueue, m_work) == 0x180);
static_assert(offsetof(ResourceReadyQueue, m_workSize) == 0x198);
static_assert(offsetof(ResourceReadyQueue, unk_21c) == 0x21c);
static_assert(offsetof(ResourceReadyQueue, m_cs2) == 0x220);

}  // namespace soa::native::resource

#endif  // SOA_NATIVE_RESOURCE_LAYOUT_H
