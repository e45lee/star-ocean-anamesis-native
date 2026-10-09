// api_layout.h: the guest data layouts of the `api` subsystem (the API callers: FakeApiCaller (the in-process route) and the request notifications).
//
// Types first (port/PLAN.md task 6): every guest class or struct this subsystem's natives touch is
// recovered here before the code that uses it, as a C++ class with the guest's layout byte for byte
// and the guest's methods attached as members (not a struct + free functions):
//   - fields at the guest's offsets, named after their use (m_hp); unknown bytes as named padding
//     (u8 unk_0c[4]), never offset arithmetic in the natives;
//   - a static_assert per known field offset and one for sizeof, so a wrong guess fails the build;
//   - a comment naming where the layout was read (constructor, decompile in port/decomp/api/).
// Natives are these members (this->m_hp), never *(T*)(p + off). Keep the classes standard-layout (no
// C++ virtual, no non-static members of reference type), so offsetof works. The guest is AArch64 LP64; the
// host (x86-64 / AArch64) has the same sizes and alignments for these plain types.
// `tools/subsystem.py export-types api` turns the structs into port/decomp/api/types.json for Ghidra.
#ifndef SOA_NATIVE_API_LAYOUT_H
#define SOA_NATIVE_API_LAYOUT_H

#include <cstddef>
#include <cstdint>

#include "../kernel/kernel_layout.h"
#include "../libcxx/libcxx_layout.h"

namespace soa::native::api {

using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using s8 = std::int8_t;
using s16 = std::int16_t;
using s32 = std::int32_t;
using s64 = std::int64_t;

// ---- CApiNotify: the responses' handlers ----------------------------------------------------------------

// CApiNotify: the IApiCaller's response handlers (On<Api>Res(data, size) deserialize a reply into the
// parameter manager) and its error state; embedded in the callers (FakeApiCaller + 0x60). Only the fields
// the route touches are recovered; layout from the constructor CApiNotify(IApiCaller*) and OnProtocolError
// (port/decomp/api/notify.c). The constructor's last write is the byte at +0x518; the whole size isn't
// pinned (no code in the lib allocates one alone), 0x520 is what the recovered fields round up to.
class CApiNotify {
public:
    const void* vtable;              // 0x00: _ZTV10CApiNotify + 0x10
    u8 unk_08[8];                    // 0x08
    libcxx::function m_function10;   // 0x10: a std::function the constructor empties (= nullptr)
    u8 unk_40[0x510 - 0x40];         // 0x40: the HTTP client, the protocol, the queues (not recovered)
    u32 m_fid;                       // 0x510: the request in flight's FunctionID (the constructor: 0x7b1a9377);
                                     //        On<Api>Res end with ErrorHandler::Success(m_fid)
    s32 m_errorCode;                 // 0x514: OnProtocolError: CNetworkUtility::AskaStatus2ApiErrorCode
                                     //        (Status); 0 after a success (the callers' ErrorCode)
    u8 m_pending;                    // 0x518: a request is in flight (OnProtocolError ignores the error when 0
                                     //        and clears it; On<Api>Res clear it)
    u8 unk_519[7];                   // 0x519
};
static_assert(offsetof(CApiNotify, m_function10) == 0x10);
static_assert(offsetof(CApiNotify, m_fid) == 0x510);
static_assert(offsetof(CApiNotify, m_errorCode) == 0x514);
static_assert(offsetof(CApiNotify, m_pending) == 0x518);
static_assert(sizeof(CApiNotify) == 0x520 && alignof(CApiNotify) == 16);

// ---- FakeApiCaller: the offline caller (the in-process route's) --------------------------------------------

// FakeApiCaller::Info: one queued request, guest size 0x50 (std::function's 16-byte alignment). Layout from
// Info::Info (the FunctionID, the name copied, the function moved; state 0) and Progress / IsRequesting
// (the state) (port/decomp/api/fakeapi.c).
class Info {
public:
    enum State : u32 {
        kQueued = 0,   // AddLocalFile: Progress asks the resource manager for the file next
        kLoading = 1,  // the file is being read: Progress hands it to m_fn once loaded
        kDone = 2,     // handed over (IsRequesting false)
    };
    // FakeApiCaller::Info::Info(FunctionID, string const&, function<Status(s8*, u32&)>)  _ZN13FakeApiCaller4InfoC2E...
    void Ctor(u32 fid, const libcxx::String* name, libcxx::function* fn);

    u32 m_fid;               // 0x00: Aska::Yayoi::GameRPC::GameProtocol::FunctionID
    u32 m_state;             // 0x04: State
    libcxx::String m_name;   // 0x08: the file, "FakeApi/<name>.msgp"
    libcxx::function m_fn;   // 0x20: std::function<Aska::Status(s8* data, u32& size)>: the request's lambda
};
static_assert(offsetof(Info, m_state) == 0x04);
static_assert(offsetof(Info, m_name) == 0x08);
static_assert(offsetof(Info, m_fn) == 0x20);
static_assert(sizeof(Info) == 0x50 && alignof(Info) == 16);

// FakeApiCaller's std::map<FunctionID, Info> (the CSTL map allocator): node 0x80, key at +0x20, Info at +0x30.
using InfoPair = libcxx::pair<u32, Info>;
using InfoMap = libcxx::tree<InfoPair>;
using InfoNode = libcxx::tree_node<InfoPair>;
static_assert(offsetof(InfoNode, value) == 0x20 && offsetof(InfoPair, second) == 0x10);
static_assert(sizeof(InfoNode) == 0x80);

// FakeApiCaller: an IApiCaller that answers every request from a local file, FakeApi/<name>.msgp, read
// through CGameResourceManager (none shipped; the game never constructs one: the in-process route does,
// fakeapi.cpp). Layout from the constructor (the fiber unit with priority 0x600, the empty map, CApiNotify
// (this)), the destructors, Release, Progress, IsRequesting and AddLocalFile (port/decomp/api/fakeapi.c).
// A request method stores {its lambda's vtable, this} through AddLocalFile; Progress hands the loaded file
// to the lambda, which calls CApiNotify::On<Api>Res(&m_notify, data, size).
class FakeApiCaller {
public:
    void CtorBase();                     // FakeApiCaller()  _ZN13FakeApiCallerC2Ev
    void Dtor();                         // ~FakeApiCaller() _ZN13FakeApiCallerD1Ev (also through _ZThn8_ at this + 8)
    void DtorDelete();                   // ~FakeApiCaller() _ZN13FakeApiCallerD0Ev (frees itself)
    void Release();                      // _ZN13FakeApiCaller7ReleaseEv: empties the map
    void Progress();                     // _ZN13FakeApiCaller8ProgressEv (the fiber unit's: _ZThn8_ at this + 8)
    bool IsRequesting(u32 fid) const;    // _ZNK13FakeApiCaller12IsRequestingE...: an unknown request counts as in flight
    // AddLocalFile(FunctionID, char const*, std::function<Status(s8*, u32&)>): fn by value, which AArch64
    // passes as a pointer to the caller's copy (a non-trivial type).
    void AddLocalFile(u32 fid, const char* name, libcxx::function* fn);

    // Port: the in-process route's Progress (fakeapi.cpp; not guest behaviour).
    void ServeProgress();
    // The map's entry for fid, or nullptr.
    InfoNode* FindInfo(u32 fid) {
        InfoNode* n = m_infos.find(fid);
        return n != m_infos.end() ? n : nullptr;
    }

    const void* vtable;              // 0x00: _ZTV13FakeApiCaller + 0x10 (IApiCaller's interface)
    kernel::CFiberUnit m_fiber;      // 0x08: priority 0x600, in the root fiber kernel; vtable _ZTV13FakeApiCaller + 0x700
    InfoMap m_infos;                 // 0x40: the requests by FunctionID
    u8 unk_58[8];                    // 0x58: (CApiNotify's alignment)
    CApiNotify m_notify;             // 0x60: the handlers the lambdas call
};
static_assert(offsetof(FakeApiCaller, m_fiber) == 0x08);
static_assert(offsetof(FakeApiCaller, m_infos) == 0x40);
static_assert(offsetof(FakeApiCaller, m_notify) == 0x60);
static_assert(sizeof(FakeApiCaller) == 0x580);

// A request method's lambda, [this] (FakeApiCaller::<Api>()::$_N): the __func<lambda, allocator,
// Status(s8*, u32&)> stored inline in its std::function: {its vtable (one per API), the caller}. The
// vtable's operator() (slot kFuncSlotCall) calls CApiNotify::On<Api>Res(&caller->m_notify, data, size).
using RequestLambda = libcxx::func<FakeApiCaller*>;
static_assert(offsetof(RequestLambda, f) == 0x08 && sizeof(RequestLambda) == 0x10);

}  // namespace soa::native::api

#endif  // SOA_NATIVE_API_LAYOUT_H
