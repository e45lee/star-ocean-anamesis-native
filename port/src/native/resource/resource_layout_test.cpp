// Layout tests for resource_layout.h (port/PLAN.md task 6, types first): the recovered classes read
// against real guest objects. Each test either builds a private object (with the guest's constructor, or
// the vtable + zeroes its inlined constructor writes) and drives it with the guest's own methods, then
// reads the fields through the layout classes and compares them with the guest's accessors and with what
// the test did; or walks a live object of the running game read-only (under its lock where it has one),
// comparing its fields with the guest's getters and the invariants the decompile shows.
// No natives here: in --selftest every t.call reaches the guest code.
#include <cstdio>
#include <cstring>
#include <string>
#include <thread>
#include <vector>

#include "core/cpu.h"
#include "core/loader.h"
#include "native/common/test.h"
#include "native/resource/resource_layout.h"

using namespace soa;
using namespace soa::native::resource;

namespace {

u64 vtable_of(TestContext& t, const char* ztv) { return t.sym(ztv) + 0x10; }

template <typename T>
T* global_ptr(TestContext& t, const char* sym) {
    return *reinterpret_cast<T* const*>(t.sym(sym));
}

// Calls vtable slot `slot` of the guest object `obj`.
GuestResult vcall(const void* obj, int slot, std::initializer_list<u64> rest = {}) {
    const u64* vt = *reinterpret_cast<const u64* const*>(obj);
    GuestArgs ga;
    ga.p(obj);
    for (u64 a : rest) ga.i(a);
    return guest_call(vt[slot], ga);
}

std::string str_of(const String& s) {
    const u8* b = reinterpret_cast<const u8*>(&s);
    if (b[0] & 1) {
        u64 size, data;
        std::memcpy(&size, b + 8, 8);
        std::memcpy(&data, b + 16, 8);
        return std::string(reinterpret_cast<const char*>(data), size);
    }
    return std::string(reinterpret_cast<const char*>(b + 1), b[0] >> 1);
}

constexpr s64 kNotReady = -0x3bc;   // Aska::Status 0xfffffffffffffc44
constexpr s64 kOutOfRange = -0x3c1; // 0xfffffffffffffc3f
constexpr s64 kOpenFailed = -0x3c0; // 0xfffffffffffffc40

// A scratch path the guest's stdio can create: the game's temp folder (Global::m_pszTempFilePath).
std::string scratch_path(TestContext& t, const char* name) {
    const char* tmp = global_ptr<const char>(t, "_ZN4Aska6Global17m_pszTempFilePathE");
    if (!tmp || !*tmp) return {};
    std::string p = tmp;
    if (p.back() != '/') p += '/';
    return p + name;
}

}  // namespace

// Aska::File / FileStream on a private file, StaticStream / MultiMediaStream over private memory.
NATIVE_TEST("resource/layout-streams") {
    // StaticStream: the vtable and zeroes (its constructor is inlined at every use).
    alignas(16) static u8 ss_mem[sizeof(StaticStream)];
    std::memset(ss_mem, 0, sizeof ss_mem);
    auto* ss = reinterpret_cast<StaticStream*>(ss_mem);
    ss->vtable = reinterpret_cast<const void*>(vtable_of(t, "_ZTVN4Aska12StaticStreamE"));
    static s8 data[200];
    for (int i = 0; i < 200; i++) data[i] = (s8)(i * 7);
    t.expect_eq(vcall(ss, kStreamSlotIsReady).x0 & 1, (u64)0, "StaticStream not ready before Open");
    t.expect_eq(t.call("_ZN4Aska12StaticStream4OpenEPKam", {(u64)ss, (u64)data, 200}) & 1, (u64)1, "StaticStream::Open");
    t.expect_eq(ss->m_data, (const s8*)data, "m_data");
    t.expect_eq(ss->m_size, (u64)200, "m_size");
    t.expect_eq(ss->m_pos, (u64)0, "m_pos");
    t.expect_eq(t.call("_ZN4Aska12StaticStream4OpenEPKam", {(u64)ss, (u64)data, 10}) & 1, (u64)0, "second Open fails");
    t.expect_eq((s64)vcall(ss, kStreamSlotGetTotalSize).x0, (s64)200, "GetTotalSize = m_size");
    s8 buf[256];
    t.expect_eq(vcall(ss, kStreamSlotRead, {(u64)buf, 1, 30}).x0, (u64)30, "Read 30");
    t.expect_eq(ss->m_pos, (u64)30, "m_pos after Read");
    t.expect_eq(std::memcmp(buf, data, 30), 0, "Read's bytes");
    t.expect_eq((s64)vcall(ss, kStreamSlotTell).x0, (s64)30, "Tell = m_pos");
    t.expect_eq(vcall(ss, kStreamSlotIsEnd, {0}).x0 & 1, (u64)0, "not at the end");
    void* locked = nullptr;
    t.expect_eq((s64)vcall(ss, kStreamSlotLock, {(u64)&locked, 20}).x0, (s64)20, "Lock 20");
    t.expect_eq(locked, (void*)(data + 30), "Lock's pointer = m_data + m_pos");
    t.expect_eq(ss->m_pos, (u64)50, "Lock advances m_pos");
    t.expect_eq(ss->m_lockedBytes, (s32)20, "m_lockedBytes");
    t.expect_eq((s64)vcall(ss, kStreamSlotUnlock, {0}).x0, (s64)20, "Unlock(0) = all");
    t.expect_eq(ss->m_lockedBytes, (s32)0, "m_lockedBytes after Unlock");
    vcall(ss, kStreamSlotSetLastError, {0x1234});
    t.expect_eq(ss->m_lastError, (s64)0x1234, "SetLastError -> m_lastError");
    t.expect_eq((s64)vcall(ss, 10).x0, (s64)0x1234, "GetLastError");
    ss->m_lastError = 0;
    t.expect_eq(vcall(ss, kStreamSlotRead, {(u64)buf, 1, 200}).x0, (u64)150, "Read past the end: the rest");
    t.expect_eq(ss->m_lastError, kOutOfRange, "short read's status");
    t.expect_eq(vcall(ss, kStreamSlotIsEnd, {0}).x0 & 1, (u64)1, "IsEnd");
    t.expect_eq(ss->m_owned.m_ptr, (s8*)nullptr, "no owned buffer");

    // MultiMediaStream over the StaticStream: a window [10, 60).
    ss->m_pos = 10;
    alignas(16) static u8 mm_mem[0x100];
    std::memset(mm_mem, 0, sizeof mm_mem);
    auto* mm = reinterpret_cast<MultiMediaStream*>(mm_mem);
    mm->vtable = reinterpret_cast<const void*>(vtable_of(t, "_ZTVN4Aska16MultiMediaStreamE"));
    t.expect_eq(t.call("_ZN4Aska16MultiMediaStream4OpenEPNS_7IStreamEmmPNS0_9LoopParamE", {(u64)mm, (u64)ss, 10, 60, 0}) & 1,
                (u64)1, "MultiMediaStream::Open");
    t.expect_eq(mm->m_stream, reinterpret_cast<IStream*>(ss), "m_stream");
    t.expect_eq(mm->m_start, (u64)10, "m_start");
    t.expect_eq(mm->m_end, (u64)60, "m_end");
    t.expect_eq(mm->m_state, (s32)1, "m_state = 1");
    t.expect_eq(mm->m_loop.m_count, (u64)0, "no loop");
    t.expect_eq(vcall(mm, kStreamSlotIsReady).x0 & 1, (u64)1, "IsReady");
    t.expect_eq((s64)vcall(mm, kStreamSlotGetTotalSize).x0, (s64)50, "GetTotalSize = m_end - m_start");
    t.expect_eq((s64)vcall(mm, kStreamSlotTell).x0, (s64)ss->m_pos, "Tell = the source's Tell");
    vcall(mm, kStreamSlotSetLastError, {0x55});
    t.expect_eq(ss->m_lastError, (s64)0x55, "SetLastError forwards to m_stream");
    MultiMediaLoopParam loop{3, 20, 40, 0x77};
    mm->m_stream = nullptr;
    t.expect_eq(t.call("_ZN4Aska16MultiMediaStream4OpenEPNS_7IStreamEmmPNS0_9LoopParamE", {(u64)mm, (u64)ss, 10, 60, (u64)&loop}) & 1,
                (u64)1, "Open with a loop");
    t.expect_eq(mm->m_loop.m_count, (u64)3, "m_loop.m_count");
    t.expect_eq(mm->m_loop.m_start, (u64)20, "m_loop.m_start");
    t.expect_eq(mm->m_loop.m_end, (u64)40, "m_loop.m_end");
    t.expect_eq(mm->m_loop.m_user, (u64)0x77, "m_loop.m_user");
    t.call("_ZN4Aska16MultiMediaStream5CloseEv", {(u64)mm});
    t.expect_eq(mm->m_stream, (IStream*)nullptr, "Close clears m_stream");

    // Aska::File and FileStream on a scratch file.
    std::string path = scratch_path(t, "soa_resource_layout_test.bin");
    if (!t.expect_eq(path.empty(), false, "Global::m_pszTempFilePath")) return;
    alignas(16) static u8 f_mem[sizeof(File)];
    std::memset(f_mem, 0, sizeof f_mem);
    auto* f = reinterpret_cast<File*>(f_mem);
    f->vtable = reinterpret_cast<const void*>(vtable_of(t, "_ZTVN4Aska4FileE"));
    if (!t.expect_eq(t.call("_ZN4Aska4File4OpenEPKcbbb", {(u64)f, (u64)path.c_str(), 0, 1, 0}) & 1, (u64)1, "File::Open wb+"))
        return;
    t.expect_eq(f->m_handle != 0, true, "m_handle");
    t.expect_eq(f->m_isAsset, (u8)0, "not an asset");
    t.expect_eq(t.call("_ZN4Aska4File5WriteEPKvm", {(u64)f, (u64)data, 200}), (u64)200, "File::Write");
    t.expect_eq((s64)t.call("_ZNK4Aska4File12GetFileSizeLEv", {(u64)f}), (s64)200, "GetFileSizeL");
    t.call("_ZN4Aska4File5CloseEv", {(u64)f});
    t.expect_eq(f->m_handle, (u64)0, "Close clears m_handle");

    alignas(16) static u8 fs_mem[sizeof(FileStream)];
    std::memset(fs_mem, 0, sizeof fs_mem);
    auto* fs = reinterpret_cast<FileStream*>(fs_mem);
    fs->vtable = reinterpret_cast<const void*>(vtable_of(t, "_ZTVN4Aska10FileStreamE"));
    fs->m_file.vtable = f->vtable;
    std::string missing = path + ".missing";
    t.expect_eq(t.call("_ZN4Aska10FileStream4OpenEPKcbbNS_7Machine6EndianE", {(u64)fs, (u64)missing.c_str(), 1, 0, 1}) & 1, (u64)0,
                "FileStream::Open of a missing file");
    t.expect_eq(fs->m_lastError, kOpenFailed, "its status in m_lastError");
    t.expect_eq(t.call("_ZN4Aska10FileStream4OpenEPKcbbNS_7Machine6EndianE", {(u64)fs, (u64)path.c_str(), 1, 0, 0}) & 1, (u64)1,
                "FileStream::Open (other endian)");
    t.expect_eq(fs->m_swapBytes, (u8)1, "m_swapBytes = !(endian & 1)");
    t.expect_eq(fs->m_file.m_handle != 0, true, "m_file.m_handle");
    t.expect_eq((s64)vcall(fs, kStreamSlotGetTotalSize).x0, (s64)200, "GetTotalSize");
    u32 words[4] = {};
    t.expect_eq(vcall(fs, kStreamSlotRead, {(u64)words, 4, 4}).x0, (u64)4, "Read 4 u32");
    u32 w0;
    std::memcpy(&w0, data, 4);
    t.expect_eq(words[0], __builtin_bswap32(w0), "elements byte-swapped");
    t.expect_eq((s64)vcall(fs, kStreamSlotTell).x0, (s64)16, "Tell");
    t.call("_ZN4Aska10FileStream5CloseEv", {(u64)fs});
    t.expect_eq(fs->m_file.m_handle, (u64)0, "FileStream::Close");
    t.expect_eq(vcall(fs, kStreamSlotIsReady).x0 & 1, (u64)0, "not ready after Close");
    std::remove(path.c_str());  // the guest path is the host path only with the identity VFS; harmless otherwise
}

// Framework::CFileLoader / CResourceElement: a private element (its constructor), then a direct-file load
// of a scratch file through the guest's FileReadManager.
NATIVE_TEST("resource/layout-file-loader") {
    alignas(16) static u8 mem[sizeof(CResourceElement)];
    std::memset(mem, 0xa5, sizeof mem);
    auto* e = reinterpret_cast<CResourceElement*>(mem);
    t.call("_ZN9Framework16CResourceElementC1Ej", {(u64)e, 1});
    const u64 vt = vtable_of(t, "_ZTVN9Framework16CResourceElementE");
    t.expect_eq((u64)e->base.vtable, vt, "primary vtable");
    t.expect_eq((u64)e->m_task.link.vtable, vt - 0x10 + 0xb0, "Aska::Task vtable at +0xc0 (_ZTV + 0xb0)");
    t.expect_eq((u64)e->m_finishNotify.vtable, vtable_of(t, "_ZTVN9Framework16CResourceElement13CFinishNotifyE"), "CFinishNotify vtable");
    t.expect_eq(e->m_finishNotify.m_owner, e, "CFinishNotify owner");
    t.expect_eq(e->m_finishNotify.m_done, (u8)0, "CFinishNotify done");
    t.expect_eq(e->m_type, (u32)1, "m_type");
    t.expect_eq((u32)t.call("_ZNK9Framework16CResourceElement4TypeEv", {(u64)e}), e->m_type, "Type()");
    t.expect_eq(e->m_phase, (s32)0, "m_phase");
    t.expect_eq((s32)t.call("_ZNK9Framework16CResourceElement5PhaseEv", {(u64)e}), e->m_phase, "Phase()");
    t.expect_eq(t.call("_ZNK9Framework16CResourceElement13IsInitializedEv", {(u64)e}) & 1, (u64)0, "IsInitialized()");
    t.expect_eq(e->m_mappingImages.begin_, (tMappingImage*)nullptr, "mapping images empty");
    t.expect_eq(e->m_pDecompressInfo, (void*)nullptr, "m_pDecompressInfo");
    t.expect_eq(e->m_decompressedSize, (u64)0, "m_decompressedSize");
    t.expect_eq(e->m_memDesc.m_high, (u8)0, "m_memDesc");
    CFileLoader& fl = e->base;
    t.expect_eq(fl.m_fileNumber, (s32)-1, "m_fileNumber = -1");
    t.expect_eq((u64)fl.m_directFile.vtable, vtable_of(t, "_ZTVN4Aska4FileE"), "m_directFile vtable");
    t.expect_eq(fl.m_directFile.m_handle, (u64)0, "m_directFile closed");
    t.expect_eq((u64)fl.m_directNameHash.vtable, vtable_of(t, "_ZTVN9Framework7CHash32E"), "m_directNameHash vtable");
    t.expect_eq(fl.unk_b0, (u8)1, "+0xb0 = 1");
    t.expect_eq(fl.m_pBuffer, (u8*)nullptr, "m_pBuffer");
    t.expect_eq(fl.m_isDirectOpened, (u8)0, "m_isDirectOpened");
    t.call("_ZN9Framework11CFileLoader9DummySizeEm", {(u64)e, 0x20});
    t.expect_eq(fl.m_dummySize, (u64)0x20, "DummySize -> m_dummySize");

    // A direct-file load of a scratch file (written with Aska::File), in the temp folder.
    // The folder: <Global::m_pszDownloadContentPath>/download/: CGame::OnInitialize's asset-manager
    // evaluation function (a lambda: CFileLoader::IsAssetManagerPath) sends paths without "/download/" to
    // the APK (AAssetManager), where a scratch file isn't.
    const char* tmp = global_ptr<const char>(t, "_ZN4Aska6Global24m_pszDownloadContentPathE");
    if (!t.expect_eq(tmp != nullptr && *tmp, true, "Global::m_pszDownloadContentPath")) return;
    std::string folder = tmp;
    if (folder.back() != '/') folder += '/';
    if (folder.find("/download/") == std::string::npos) folder += "download/";
    const char* name = "soa_resource_loader_test.bin";
    std::string path = folder + name;
    static u8 data[300];
    for (int i = 0; i < 300; i++) data[i] = (u8)(i * 13 + 1);
    alignas(16) static u8 f_mem[sizeof(File)];
    std::memset(f_mem, 0, sizeof f_mem);
    auto* f = reinterpret_cast<File*>(f_mem);
    f->vtable = fl.m_directFile.vtable;
    if (!t.expect_eq(t.call("_ZN4Aska4File4OpenEPKcbbb", {(u64)f, (u64)path.c_str(), 0, 1, 0}) & 1, (u64)1, "File::Open wb+")) return;
    t.call("_ZN4Aska4File5WriteEPKvm", {(u64)f, (u64)data, sizeof data});
    t.call("_ZN4Aska4File5CloseEv", {(u64)f});

    t.expect_eq((s64)t.call("_ZN4Aska4File12GetFileSizeLEPKcb", {(u64)path.c_str(), 0}), (s64)sizeof data, "File::GetFileSizeL(path)");
    t.expect_eq(t.call("_ZN9Framework11CFileLoader18IsAssetManagerPathEPKc", {(u64)path.c_str()}) & 1, (u64)0,
                "a /download/ path is not an APK asset");
    t.call("_ZN9Framework11CFileLoader16EnableDirectLoadEPKc", {(u64)e, (u64)folder.c_str()});
    t.expect_eq(str_of(fl.m_directLoadFolder), folder, "EnableDirectLoad -> m_directLoadFolder");
    // CFileLoader's own InitializeByDirectFile (vtable slot 4): not the element's (which adds a task).
    t.call("_ZN9Framework11CFileLoader22InitializeByDirectFileEPKcmb", {(u64)e, (u64)name, 0x10, 0});
    t.expect_eq(fl.m_fileNumber, (s32)-2, "m_fileNumber = -2 (direct)");
    t.expect_eq(fl.m_isDirectOpened, (u8)1, "m_isDirectOpened");
    t.expect_eq(str_of(fl.m_directRelativeName), std::string(name), "m_directRelativeName");
    t.expect_eq(str_of(fl.m_directPath), path, "m_directPath = folder + name");
    t.expect_eq(fl.m_size, (u64)sizeof data, "m_size");
    t.expect_eq(fl.m_pBuffer != nullptr, true, "m_pBuffer");
    for (int i = 0; i < 2000 && t.call("_ZNK9Framework11CFileLoader9IsLoadingEv", {(u64)e}) & 1; i++)
        std::this_thread::sleep_for(std::chrono::milliseconds(2));
    t.expect_eq(fl.m_isLoading, (u8)0, "loaded (m_isLoading cleared by Handler)");
    t.expect_eq(std::memcmp(fl.m_pBuffer, data, sizeof data), 0, "the buffer holds the file");
    t.expect_eq(std::memcmp(fl.m_pBuffer + sizeof data, "\0\0\0\0\0\0\0\0", 8), 0, "the dummy bytes are zero");
    t.expect_eq(t.call("_ZNK9Framework11CFileLoader7pBufferEv", {(u64)e}), (u64)(fl.m_pBuffer + fl.m_bufferOffset), "pBuffer()");
    t.expect_eq(t.call("_ZNK9Framework11CFileLoader4SizeEv", {(u64)e}), fl.m_size - fl.m_bufferOffset, "Size()");
    t.expect_eq(t.call("_ZNK9Framework11CFileLoader12BufferOffsetEv", {(u64)e}), fl.m_bufferOffset, "BufferOffset()");
    t.expect_eq((s32)t.call("_ZNK9Framework11CFileLoader10FileNumberEv", {(u64)e}), fl.m_fileNumber, "FileNumber()");
    t.expect_eq(std::string((const char*)t.call("_ZNK9Framework11CFileLoader9pFileNameEv", {(u64)e})), std::string(name),
                "pFileName() = m_directRelativeName");
    t.expect_eq(std::string((const char*)t.call("_ZNK9Framework11CFileLoader29pDirectOpenedFileRelativeNameEv", {(u64)e})),
                std::string(name), "pDirectOpenedFileRelativeName()");
    alignas(16) CHash32Bytes h{};
    t.call("_ZNK9Framework11CFileLoader12FileNameHashEv", GuestArgs().sret(&h).p(e));
    t.expect_eq(h.m_hash, fl.m_directNameHash.m_hash, "FileNameHash() = m_directNameHash");
    t.expect_eq(h.m_hash != 0, true, "the name's hash");
    t.call("_ZN9Framework11CFileLoader7ReleaseEv", {(u64)e});
    t.expect_eq(fl.m_fileNumber, (s32)-1, "Release: m_fileNumber = -1");
    t.expect_eq(fl.m_pBuffer, (u8*)nullptr, "Release: m_pBuffer");
    t.expect_eq(str_of(fl.m_directPath), std::string(), "Release clears m_directPath");
    t.call("_ZN9Framework16CResourceElementD2Ev", {(u64)e});
    std::remove(path.c_str());
}

// Framework::CResourceManager (CMainTask's), its tElements and their CResourceElements, read under the
// manager's lock; CGameResourceManager and its downloader.
NATIVE_TEST("resource/layout-resource-manager") {
    void* main_task = global_ptr<void>(t, "_ZN9Framework10TSingletonINS_12CApplication9CMainTaskEE11m_pInstanceE");
    if (!t.expect_eq(main_task != nullptr, true, "TSingleton<CMainTask>")) return;
    auto* rm = reinterpret_cast<CResourceManager*>(t.call("_ZNK9Framework12CApplication9CMainTask16rResourceManagerEv", {(u64)main_task}));
    t.expect_eq((u64)rm, *reinterpret_cast<u64*>((u8*)main_task + 0x60), "rResourceManager() = CMainTask + 0x60");
    if (!t.expect_eq(rm != nullptr, true, "the resource manager")) return;
    t.expect_eq((u64)rm->vtable, vtable_of(t, "_ZTVN9Framework16CResourceManagerE"), "vtable");
    t.expect_eq(rm->m_isInitialized, (u8)1, "m_isInitialized");
    t.expect_eq(vcall(rm, 11).x0 & 0xffffffff, (u64)*reinterpret_cast<const u32*>(rm->task_08 + 0x18),
                "Aska::Task +0x20 = GetDefaultLevel() (vtable slot 11)");

    t.call("_ZN9Framework16CResourceManager4LockEv", {(u64)rm});
    const u64 n = rm->m_elements.size;
    t.expect_eq((u64)(u32)t.call("_ZNK9Framework16CResourceManager3NumEv", {(u64)rm}), n, "Num() = m_elements.size");
    auto* sentinel = reinterpret_cast<ListNodeTElement*>(&rm->m_elements);
    u64 i = 0, loading = 0;
    const u64 notify_vt = vtable_of(t, "_ZTVN9Framework16CResourceElement13CFinishNotifyE");
    for (ListNodeTElement* node = rm->m_elements.next; node != sentinel && i < 100000; node = node->next, i++) {
        t.expect_eq(node->next->prev, node, "list links");
        tElement& te = node->value;
        CResourceElement* e = te.m_pResourceElement;
        if (!t.expect_eq(e != nullptr, true, "tElement's element")) break;
        t.expect_eq(t.call("_ZNK9Framework16CResourceManager24crResourceElementByIndexEj", {(u64)rm, i}), (u64)e,
                    "crResourceElementByIndex(i)");
        t.expect_eq((s32)t.call("_ZNK9Framework16CResourceManager8tElement16ReferenceCounterEv", {(u64)&te}), te.m_referenceCounter,
                    "tElement::ReferenceCounter()");
        t.expect_eq((u32)t.call("_ZNK9Framework16CResourceManager8tElement13UniqueBitFlagEv", {(u64)&te}), te.m_uniqueBitFlag,
                    "tElement::UniqueBitFlag()");
        t.expect_eq((u64)e->m_finishNotify.vtable, notify_vt, "element's CFinishNotify vtable");
        t.expect_eq(e->m_finishNotify.m_owner, e, "element's CFinishNotify owner");
        t.expect_eq((u32)t.call("_ZNK9Framework16CResourceElement4TypeEv", {(u64)e}), e->m_type, "element Type()");
        t.expect_eq((s32)t.call("_ZNK9Framework16CResourceElement5PhaseEv", {(u64)e}), e->m_phase, "element Phase()");
        t.expect_eq((s32)t.call("_ZNK9Framework11CFileLoader10FileNumberEv", {(u64)e}), e->base.m_fileNumber, "element FileNumber()");
        t.expect_eq(t.call("_ZNK9Framework11CFileLoader9IsLoadingEv", {(u64)e}) & 1, (u64)e->base.m_isLoading, "element IsLoading()");
        if (e->m_phase != 9) loading++;
        if (e->base.m_fileNumber == -2) {
            t.expect_eq(e->base.m_isDirectOpened, (u8)1, "direct element opened");
            std::string nm = str_of(e->base.m_directRelativeName);
            t.expect_eq(std::string((const char*)t.call("_ZNK9Framework11CFileLoader9pFileNameEv", {(u64)e})), nm,
                        "pFileName() = m_directRelativeName");
            u64 found = t.call("_ZNK9Framework16CResourceManager19pSearchByDirectPathEPKc", {(u64)rm, (u64)nm.c_str()});
            if (found == (u64)&te || found == 0)
                t.expect_eq(found, (u64)&te, "pSearchByDirectPath = &node->value");
            else  // an earlier element with the same name: it must be one
                t.expect_eq(reinterpret_cast<tElement*>(found)->m_pResourceElement->base.m_fileNumber, (s32)-2, "pSearchByDirectPath's match");
        } else if (e->base.m_fileNumber >= 0) {
            u64 found = t.call("_ZNK9Framework16CResourceManager7pSearchEj", {(u64)rm, (u64)(u32)e->base.m_fileNumber});
            t.expect_eq(reinterpret_cast<tElement*>(found)->m_pResourceElement->base.m_fileNumber, e->base.m_fileNumber, "pSearch's match");
        }
        if (e->m_phase == 9 && e->base.m_pBuffer) {
            t.expect_eq(t.call("_ZNK9Framework11CFileLoader4SizeEv", {(u64)e}), e->base.m_size - e->base.m_bufferOffset, "element Size()");
        }
    }
    t.expect_eq(i, n, "list length = m_elements.size");
    t.expect_eq((u64)(u32)t.call("_ZNK9Framework16CResourceManager10NumLoadingEv", {(u64)rm}), loading, "NumLoading() = phases != 9");
    t.call("_ZN9Framework16CResourceManager6UnlockEv", {(u64)rm});
    std::fprintf(stderr, "resource/layout-resource-manager: %llu elements (%llu loading)\n", (unsigned long long)n,
                 (unsigned long long)loading);

    auto* grm = global_ptr<CGameResourceManager>(t, "_ZN9Framework10TSingletonI20CGameResourceManagerE11m_pInstanceE");
    if (!t.expect_eq(grm != nullptr, true, "TSingleton<CGameResourceManager>")) return;
    t.expect_eq((u64)grm->vtable, vtable_of(t, "_ZTV20CGameResourceManager"), "CGameResourceManager vtable");
    t.expect_eq(grm->m_pSubstance, rm, "m_pSubstance = CMainTask's resource manager");
    t.expect_eq(t.call("_ZN20CGameResourceManager10pSubstanceEv", {(u64)grm}), (u64)grm->m_pSubstance, "pSubstance()");
    t.expect_eq(t.call("_ZNK20CGameResourceManager11cpSubstanceEv", {(u64)grm}), (u64)grm->m_pSubstance, "cpSubstance()");
    const auto& tab = grm->m_fileMap.table;
    t.expect_eq(tab.m_buckets.m_data != nullptr, true, "file map buckets");
    u64 used = 0;
    for (u64 b = 0; b < tab.m_buckets.m_count; b++) used += tab.m_buckets.m_data[b].m_state == 1;
    t.expect_eq(used, (u64)tab.m_size, "file map: used buckets = m_size");
    // SearchFileMap(name) of an unmapped name returns the name itself.
    const char* probe = "soa/layout/not-a-mapped-file";
    t.expect_eq(t.call("_ZNK20CGameResourceManager13SearchFileMapEPKc", {(u64)grm, (u64)probe}), (u64)probe, "SearchFileMap (miss)");

    auto* dl = reinterpret_cast<CGameResourceDownloader*>(grm->m_pDownLoader);
    if (!dl) return;
    t.expect_eq((u64)dl->fiberUnit.vtable, vtable_of(t, "_ZTV23CGameResourceDownloader"), "downloader vtable");
    const u64 node_array_vt = vtable_of(t, "_ZTVN4Aska6TArrayIPN23CGameResourceDownloader13CDownloadNodeELb0EEE");
    t.expect_eq((u64)dl->m_nodes.vtable, node_array_vt, "m_nodes vtable");
    t.expect_eq((u64)dl->m_downloading.vtable, node_array_vt, "m_downloading vtable");
    t.expect_eq((u64)dl->m_names.vtable, vtable_of(t, "_ZTVN4Aska6TArrayIN9Framework13TStaticStringILm256EEELb0EEE"), "m_names vtable");
    for (int k = 0; k < 3; k++) t.expect_eq((u64)dl->m_ason[k].vtable, vtable_of(t, "_ZTVN4Aska4ASONE"), "m_ason[k] vtable");
    t.expect_eq(t.call("_ZNK23CGameResourceDownloader7IsIdeleEv", {(u64)dl}) & 1, (u64)(dl->m_mode == 0), "IsIdele()");
    t.expect_eq(t.call("_ZNK23CGameResourceDownloader14IsModeDownloadEv", {(u64)dl}) & 1, (u64)(dl->m_mode == 4), "IsModeDownload()");
    t.expect_eq(t.call("_ZNK23CGameResourceDownloader13IsErrorStatusEv", {(u64)dl}) & 1, (u64)(dl->m_errorStatus != 0), "IsErrorStatus()");
    t.expect_eq(t.call("_ZNK23CGameResourceDownloader19IsReadyDownloadFlagEv", {(u64)dl}) & 1, (u64)dl->m_readyFlag, "IsReadyDownloadFlag()");
    t.expect_eq(t.call("_ZNK23CGameResourceDownloader15IsReadyDownloadEv", {(u64)dl}) & 1, (u64)(dl->m_readyFlag || dl->m_isReady),
                "IsReadyDownload()");
    t.expect_eq((u32)t.call("_ZNK23CGameResourceDownloader14NumDownloadingEv", {(u64)dl}),
                (u32)(dl->m_isReady ? 0 : dl->m_downloading.m_size), "NumDownloading()");
}

// Aska::FileReadManager and its devices, the DecompressQueue, the ResourceReadyQueue (read-only).
NATIVE_TEST("resource/layout-read-devices") {
    auto* frm = global_ptr<FileReadManager>(t, "_ZN4Aska6Global18m_pFileReadManagerE");
    if (!t.expect_eq(frm != nullptr, true, "Global::m_pFileReadManager")) return;
    t.expect_eq((u64)frm->vtable, vtable_of(t, "_ZTVN4Aska15FileReadManagerE"), "FileReadManager vtable");
    t.expect_eq((u64)frm->m_direct.vtable, vtable_of(t, "_ZTVN4Aska16DirectReadDeviceE"), "m_direct: a DirectReadDevice");
    t.expect_eq(frm->m_numDevices >= 1 && frm->m_numDevices <= 3, true, "1..3 devices");
    for (s32 i = 0; i < frm->m_numDevices && i < 3; i++) {
        BaseReadDevice* d = frm->m_devices[i];
        t.expect_eq(t.call("_ZN4Aska15FileReadManager16GetDeviceByIndexEi", {(u64)frm, (u64)i}), (u64)d, "GetDeviceByIndex(i)");
        if (!d) continue;
        t.expect_eq(d->m_deviceId >= 0, true, "device id >= 0");
        BaseReadDevice* byid = reinterpret_cast<BaseReadDevice*>(t.call("_ZN4Aska15FileReadManager9GetDeviceEi", {(u64)frm, (u64)d->m_deviceId}));
        t.expect_eq(byid ? byid->m_deviceId : -1, d->m_deviceId, "GetDevice(m_deviceId)");
        if (i > 0) t.expect_eq(frm->m_devices[i - 1]->m_priority >= d->m_priority, true, "sorted by m_priority");
        t.expect_eq(d->m_isActive, (u8)1, "m_isActive");
        t.expect_eq(d->m_requestCount > 0, true, "m_requestCount");
        t.expect_eq((s32)d->m_freeCapacity, d->m_requestCount, "m_freeCapacity = m_requestCount");
        t.expect_eq(d->m_requestPool != nullptr, true, "m_requestPool");
        t.expect_eq((u64)d->m_freeRing, (u64)d->m_requestPool + (u64)d->m_requestCount * 0x58, "the ring after the requests");
        t.expect_eq((u64)d->m_decompressNotifies, (u64)d->m_freeRing + (u64)d->m_requestCount * 8, "the notifies after the ring");
        t.expect_eq(d->m_thread != 0, true, "the device thread");
    }

    auto* dq = global_ptr<DecompressQueue>(t, "_ZN4Aska6Global18m_pDecompressQueueE");
    if (t.expect_eq(dq != nullptr, true, "Global::m_pDecompressQueue")) {
        t.expect_eq(dq->m_running, (u8)1, "DecompressQueue m_running");
        if (t.expect_eq(dq->m_thread != nullptr, true, "DecompressQueue m_thread"))
            t.expect_eq(*reinterpret_cast<const u64*>(dq->m_thread), vtable_of(t, "_ZTVN4Aska16DecompressThreadE"), "m_thread's vtable");
    }

    auto* rq = global_ptr<ResourceReadyQueue>(t, "_ZN4Aska6Global21m_pResourceReadyQueueE");
    if (rq) {
        t.expect_eq((u64)rq->vtable, vtable_of(t, "_ZTVN4Aska18ResourceReadyQueueE"), "ResourceReadyQueue vtable");
        t.expect_eq((u64)rq->m_portVtable, vtable_of(t, "_ZTVN4Aska10TEventPortINS_18ResourceReadyQueue6EvItemEEE"), "TEventPort vtable");
        const u64 fake = vtable_of(t, "_ZTVN4Aska10FakeStreamE");
        t.expect_eq((u64)rq->m_fakeStreamVtable, fake, "FakeStream at +0x100");
        t.expect_eq((u64)rq->m_fakeStream2Vtable, fake, "FakeStream at +0x138");
        t.expect_eq(rq->m_workSize, (u32)0x1000, "work buffer size");
        t.expect_eq((u64)rq->m_workData, (u64)rq->m_work.m_ptr, "work data = the shared array's");
        t.expect_eq(rq->unk_21c, (u32)0x10, "+0x21c = 0x10");
        t.expect_eq(rq->m_initialized, (u8)1, "m_initialized");
    }
}

// Aska::LocalKVS: a private store (Init / SetCipher), the live Global::m_pLocalKVS and CGameLocalKVS's.
NATIVE_TEST("resource/layout-local-kvs") {
    static const char kConstant[] = "expand 32-byte k";
    alignas(16) static u8 mem[sizeof(LocalKVS)];
    std::memset(mem, 0, sizeof mem);
    auto* kvs = reinterpret_cast<LocalKVS*>(mem);
    std::memcpy(kvs->m_cipher.m_constant, kConstant, 16);
    s64 st = -1;
    t.call("_ZN4Aska8LocalKVS4InitEPKcbPcS3_", GuestArgs().sret(&st).p(kvs).p("SoaLayoutTest").i(0).i(0).i(0));
    t.expect_eq(st, (s64)0, "Init's status");
    t.expect_eq(std::string(kvs->m_name), std::string("SoaLayoutTest"), "m_name");
    t.expect_eq(kvs->m_cipherEnabled, (u8)0, "m_cipherEnabled (Init without cipher)");
    static char key[32];
    for (int i = 0; i < 32; i++) key[i] = (char)(0x40 + i);
    static u8 nonce[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    st = -1;
    t.call("_ZN4Aska8LocalKVS9SetCipherEbPcS1_", GuestArgs().sret(&st).p(kvs).i(1).p(key).p(nonce));
    t.expect_eq(st, (s64)0, "SetCipher's status");
    t.expect_eq(kvs->m_cipherEnabled, (u8)1, "m_cipherEnabled");
    t.expect_eq(kvs->m_keyReady, (u8)1, "m_keyReady");
    t.expect_eq(kvs->m_keyDerived, (u8)1, "m_keyDerived");
    t.expect_eq(std::memcmp(kvs->m_cipher.m_key, key, 32), 0, "m_cipher.m_key");
    t.expect_eq(std::memcmp(kvs->m_cipher.m_nonce, nonce, 12), 0, "m_cipher.m_nonce");
    t.expect_eq(kvs->m_cipher.m_counter, (u32)0, "m_cipher.m_counter");
    t.expect_eq(std::memcmp(kvs->m_cipher.m_constant, kConstant, 16), 0, "m_cipher.m_constant untouched");

    auto* g = global_ptr<LocalKVS>(t, "_ZN4Aska6Global11m_pLocalKVSE");
    if (t.expect_eq(g != nullptr, true, "Global::m_pLocalKVS")) {
        t.expect_eq(g->m_name[0] != 0, true, "global store's name");
        t.expect_eq(std::memcmp(g->m_cipher.m_constant, kConstant, 16), 0, "global store's ChaCha20 constant");
    }
    auto* gk = global_ptr<CGameLocalKVS>(t, "_ZN9Framework10TSingletonI13CGameLocalKVSE11m_pInstanceE");
    if (t.expect_eq(gk != nullptr, true, "TSingleton<CGameLocalKVS>")) {
        t.expect_eq((u64)gk->vtable, vtable_of(t, "_ZTV13CGameLocalKVS"), "CGameLocalKVS vtable");
        t.expect_eq(t.call("_ZNK13CGameLocalKVS10pSubstanceEv", {(u64)gk}), (u64)gk->m_pKVS, "pSubstance()");
        t.expect_eq(t.call("_ZNK13CGameLocalKVS6ResultEv", {(u64)gk}), (u64)&gk->m_result, "Result() = &m_result");
        t.expect_eq(gk->m_result, (s64)0, "Init's status");
        if (gk->m_pKVS) {
            t.expect_eq(std::string(gk->m_pKVS->m_name), std::string("Game"), "the store's name");
            t.expect_eq(gk->m_pKVS->m_cipherEnabled, (u8)1, "the Game store is encrypted");
            t.expect_eq(gk->m_pKVS->m_keyReady, (u8)1, "its key is set");
            t.expect_eq(std::memcmp(gk->m_pKVS->m_cipher.m_constant, kConstant, 16), 0, "its ChaCha20 constant");
        }
    }
}

// The shader cache (Global::m_pShaderLinkManager + 8: an AofAhslManager, an AHSLCacheManagerV2) and LIBLManager.
NATIVE_TEST("resource/layout-ahsl-libl") {
    auto* slm = global_ptr<ShaderLinkManager>(t, "_ZN4Aska6Global20m_pShaderLinkManagerE");
    auto* ahsl = slm ? reinterpret_cast<AHSLCacheManagerV2*>(slm->m_aofAhsl) : nullptr;
    if (t.expect_eq(ahsl != nullptr, true, "Global::m_pShaderLinkManager")) {
        t.expect_eq((u64)slm->vtable, vtable_of(t, "_ZTVN4Aska17ShaderLinkManagerE"), "ShaderLinkManager vtable");
        t.expect_eq((u64)ahsl->vtable, vtable_of(t, "_ZTVN4Aska14AofAhslManagerE"), "an AofAhslManager");
        t.expect_eq((u64)ahsl->m_l1Heap.vtable, vtable_of(t, "_ZTVN4Aska13MemoryManagerE"), "m_l1Heap: a MemoryManager");
        t.expect_eq(ahsl->m_l1Heap.m_heapSize >= 0x2f0000 && ahsl->m_l1Heap.m_heapSize <= 0x300000, true, "m_l1Heap's heap (0x300000)");
        t.expect_eq(ahsl->m_targetConsole, *reinterpret_cast<const s32*>(t.sym("_ZN4Aska5s_eTCE")), "m_targetConsole = s_eTC");
        // The game's frames advance it; under load (or while the game loads) one frame can take far
        // longer than a fixed wait (a 200 ms one once failed a loaded gate): poll up to 20 s.
        const volatile s32& frame = ahsl->m_frame;  // (the game's thread writes it)
        s32 f0 = frame;
        auto deadline = std::chrono::steady_clock::now() + std::chrono::seconds(20);
        while (frame == f0 && std::chrono::steady_clock::now() < deadline) std::this_thread::sleep_for(std::chrono::milliseconds(20));
        t.expect_eq(frame != f0, true, "m_frame advances (Tick per frame)");
        // L1: GetNodeCount / GetNodeDirect / GetData against the buckets.
        AHSLDatabaseShaderCache& db = ahsl->m_l1;
        u64 entries = 0, checked = 0;
        for (s32 b = 0; b < 512; b++) {
            const AHSLNodeShaderCache& node = db.m_nodes[b];
            s32 cnt = (s32)t.call("_ZNK4Aska12AHSLDatabaseINS_11ShaderCacheELh9EE12GetNodeCountEi", {(u64)&db, (u64)b});
            t.expect_eq(cnt, (s32)node.m_count, "GetNodeCount(b) = m_nodes[b].m_count");
            t.expect_eq(node.m_capacity >= node.m_count, true, "capacity >= count");
            entries += node.m_count;
            const AHSLEntry<ShaderCache>* es = node.m_ext ? node.m_ext : node.m_entries;
            for (s32 j = 0; j < node.m_count && j < 4; j++) {
                t.expect_eq(t.call("_ZN4Aska12AHSLDatabaseINS_11ShaderCacheELh9EE13GetNodeDirectEii", {(u64)&db, (u64)b, (u64)j}),
                            (u64)es[j].m_data, "GetNodeDirect(b, j) = the entry's data");
                if (checked < 64) {
                    t.expect_eq(t.call("_ZN4Aska12AHSLDatabaseINS_11ShaderCacheELh9EE7GetDataEPKh", {(u64)&db, (u64)es[j].m_key}),
                                (u64)es[j].m_data, "GetData(key) = the entry's data");
                    u32 bucket = ((u32)es[j].m_key[0] << 1) | (es[j].m_key[1] >> 7);
                    t.expect_eq(bucket, (u32)b, "bucket = the key's first 9 bits");
                    checked++;
                }
            }
        }
        std::fprintf(stderr, "resource/layout-ahsl-libl: L1 %llu entries (%llu looked up)\n", (unsigned long long)entries,
                     (unsigned long long)checked);
    }

    auto* libl = global_ptr<LIBLManager>(t, "_ZN4Aska6Global14m_pLIBLManagerE");
    if (!libl) return;  // created with the first scene that has one
    t.expect_eq((u64)libl->vtable, vtable_of(t, "_ZTVN4Aska11LIBLManagerE"), "LIBLManager vtable");
    t.expect_eq((u64)libl->m_loaderPool.vtable, vtable_of(t, "_ZTVN4Aska11TPoolLegacyINS_11LIBLManager14_AarLoaderElemELb0EEE"),
                "m_loaderPool vtable");
    t.expect_eq(*reinterpret_cast<const u64*>(libl->m_loaderList), vtable_of(t, "_ZTVN4Aska11LIBLManager14_AarLoaderListE"),
                "m_loaderList: an _AarLoaderList (a TList<_AarLoaderElem>)");
    t.expect_eq(*reinterpret_cast<const u64*>(libl->m_loaderList + 8), vtable_of(t, "_ZTVN4Aska11LIBLManager14_AarLoaderElemE"),
                "the list's sentinel element");
    t.expect_eq((u64)libl->m_updateTask.link.vtable, vtable_of(t, "_ZTVN4Aska11LIBLManager20_AarLoaderUpdateTaskE"), "m_updateTask vtable");
    t.expect_eq((u64)libl->m_detachHandlerVtable, vtable_of(t, "_ZTVN4Aska16AarTextureCommon20DetachTextureHandlerE"),
                "the DetachTextureHandler");
}
