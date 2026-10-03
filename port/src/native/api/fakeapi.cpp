// FakeApiCaller: the game's built-in offline "server" (an IApiCaller that answers requests
// in-process from canned FakeApi/*.msgp files), as readable native C++.
//
// The shipped game never constructs a FakeApiCaller (CGame::OnInitialize always makes a
// NetworkApiCaller) and the canned files aren't shipped, so none of this runs in normal play.
// The port keeps it bit-compatible so a port option (or a debug route) can bring it up. The
// protocol is in docs/notes.md, "Offline server (FakeApiCaller)".
//
// Layout (guest object, kept as is):
//   +0x00 IApiCaller vtable   +0x08 Framework::CFiberUnit (Progress runs once per frame)
//   +0x40 std::map<FunctionID, Info> {begin, root, size}   +0x60 CApiNotify
// Map node (0x80): +0x00 left, +0x08 right, +0x10 parent, +0x18 colour, +0x20 key (u32),
//   +0x30 Info: +0 fid, +4 state (0 queued, 1 loading, 2 done), +8 name (CSTL string),
//   +0x20 std::function<Aska::Status(s8*, u32&)> (32-byte buffer, __f_ at +0x40).
//
// Every request method stores a lambda {vtable, this} in AddLocalFile(fid, "FakeApi/x.msgp");
// Progress loads the file through CGameResourceManager and calls the lambda, which hands the
// bytes to CApiNotify::On<Api>Res(this+0x60, data, size). The two login lambdas first
// deserialize a fake {"Player": {"Id", "Name"}} into CParameterManager.
//
// The lambdas' std::function objects keep their guest vtables, so the guest's copies and
// destructors of them still work; this file replaces the vtable's operator() entries.
#include <array>
#include <cinttypes>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <utility>
#include <map>
#include <set>
#include <string>
#include <vector>

#include "core/cpu.h"
#include "core/loader.h"
#include "core/log.h"
#include "core/options.h"
#include "native/common/guest_std.h"
#include "native/common/native.h"
#include "native/api/fakeapi.h"
#include "soaserver/api_campaign.h"
#include "soaserver/chash32.h"
#include "soaserver/events.h"
#include "soaserver/server.h"
#include "native/api/server_adapters.h"
#include "native/api/packet_log.h"

namespace soa::native::fakeapi {

struct Request {
    const char* sym;  // the FakeApiCaller method
    u32 fid;          // Aska::Yayoi::GameRPC::GameProtocol::FunctionID
    u64 file;         // vaddr of "FakeApi/<name>.msgp"
    u64 lambda_vt;    // vaddr of the lambda's __func vtable (address point)
    u64 lambda_op;    // vaddr of its operator()
    const char* handler;  // CApiNotify::On<Api>Res, or nullptr for the login lambda
};

#define FAKEAPI_REQ(sym, fid, file, vt, op, handler) {sym, fid, file, vt, op, handler},
const Request kRequests[] = {
#include "native/api/gen/fakeapi_tables.inc"
    FAKEAPI_REQUESTS(FAKEAPI_REQ)};
#undef FAKEAPI_REQ
constexpr int kNumRequests = sizeof(kRequests) / sizeof(kRequests[0]);

namespace {

u64 lib_base() { return main_lib()->base; }

template <typename T>
T& at(u64 p, u64 off) { return *(T*)(p + off); }

constexpr u64 kMap = 0x40;      // std::map: begin node
constexpr u64 kMapEnd = 0x48;   // end node (its left = root)
constexpr u64 kMapSize = 0x50;
constexpr u64 kNotify = 0x60;   // CApiNotify

// Map node fields.
constexpr u64 kKey = 0x20, kInfo = 0x30, kState = 0x34, kName = 0x38, kFn = 0x50, kFnF = 0x70;

// Guest std::function (libc++): 32-byte buffer, then __f_ (the stored __base*). __base vtable:
// [2] __clone() (heap copy), [3] __clone(dst) (placement copy), [4] destroy(),
// [5] destroy_deallocate(), [6] operator().
constexpr u64 kFunctionF = 0x20;
u64 vslot(u64 obj, int i) { return at<u64>(at<u64>(obj, 0), i * 8); }

// function(const function&) into uninitialised storage at dst.
void function_copy(u64 dst, u64 src) {
    u64 f = at<u64>(src, kFunctionF);
    if (!f) {
        at<u64>(dst, kFunctionF) = 0;
    } else if (f == src) {
        at<u64>(dst, kFunctionF) = dst;
        guest_call(vslot(f, 3), {f, dst});
    } else {
        at<u64>(dst, kFunctionF) = guest_call(vslot(f, 2), {f});
    }
}

// ~function()
void function_destroy(u64 fn) {
    u64 f = at<u64>(fn, kFunctionF);
    if (f == fn) guest_call(vslot(f, 4), {f});
    else if (f) guest_call(vslot(f, 5), {f});
}

u64 g(const char* mangled) { return guest::sym(mangled); }

// Framework::TSingleton<T>::m_pInstance, with the header's assertion when it's null.
u64 singleton(const char* instance_sym) {
    u64 slot = g(instance_sym);
    u64 p = at<u64>(slot, 0);
    if (!p) {
        guest_call(g("_ZN9Framework9gDoAssertEPKciS1_z"), {lib_base() + 0x26dae91, 0x23, lib_base() + 0x26daf21});  // TSingleton.h, "m_pInstance is null." (3.7.0)
        p = at<u64>(slot, 0);
    }
    return p;
}
const char kResMgr[] = "_ZN9Framework10TSingletonI20CGameResourceManagerE11m_pInstanceE";

// libc++ __tree_next / __tree_min
u64 tree_next(u64 x) {
    if (at<u64>(x, 8)) {
        x = at<u64>(x, 8);
        while (at<u64>(x, 0)) x = at<u64>(x, 0);
        return x;
    }
    while (at<u64>(at<u64>(x, 0x10), 0) != x) x = at<u64>(x, 0x10);
    return at<u64>(x, 0x10);
}

// map.lower_bound(fid), or end.
u64 lower_bound(u64 self, u32 fid) {
    u64 end = self + kMapEnd, res = end;
    for (u64 n = at<u64>(end, 0); n;) {
        if (at<u32>(n, kKey) < fid) {
            n = at<u64>(n, 8);
        } else {
            res = n;
            n = at<u64>(n, 0);
        }
    }
    return res;
}

// map.find(fid), or 0.
u64 find(u64 self, u32 fid) {
    u64 n = lower_bound(self, fid);
    return (n != self + kMapEnd && at<u32>(n, kKey) <= fid) ? n : 0;
}

// __tree::destroy(node): post-order; each Info's function and name.
void tree_destroy(u64 n) {
    if (!n) return;
    tree_destroy(at<u64>(n, 0));
    tree_destroy(at<u64>(n, 8));
    function_destroy(n + kFn);
    ((guest::String*)(n + kName))->destroy();
    guest::stl_free((void*)n);
}

}  // namespace

// FakeApiCaller::AddLocalFile(FunctionID, const char*, std::function<Status(s8*, u32&)>)
// A known FunctionID is only re-queued: its first file name and lambda stay.
void AddLocalFile(u64 self, u32 fid, const char* name, u64 fn) {
    if (u64 n = find(self, fid)) {
        at<u32>(n, kState) = 0;
        return;
    }
    // __emplace_unique_key_args: find the slot, then a 0x80-byte node holding
    // {fid, Info{fid, state 0, name, fn}}.
    u64 end = self + kMapEnd, parent = end;
    u64* child = (u64*)end;
    for (u64 n = at<u64>(end, 0); n;) {
        parent = n;
        if (fid < at<u32>(n, kKey)) {
            child = (u64*)n;
            n = at<u64>(n, 0);
        } else {
            child = (u64*)(n + 8);
            n = at<u64>(n, 8);
        }
    }
    u64 node = (u64)guest::stl_alloc(0x80);
    at<u32>(node, kKey) = fid;
    at<u32>(node, kInfo) = fid;
    at<u32>(node, kState) = 0;
    ((guest::String*)(node + kName))->init(name);
    function_copy(node + kFn, fn);
    at<u64>(node, 0) = 0;
    at<u64>(node, 8) = 0;
    at<u64>(node, 0x10) = parent;
    *child = node;
    u64 begin = at<u64>(self, kMap);
    if (at<u64>(begin, 0)) at<u64>(self, kMap) = at<u64>(begin, 0);
    // std::__ndk1::__tree_balance_after_insert<__tree_node_base<void*>*>(root, x): the guest's own
    static const u64 balance = g("_ZNSt6__ndk127__tree_balance_after_insertIPNS_16__tree_node_baseIPvEEEEvT_S5_");
    guest_call(balance, {at<u64>(end, 0), *child});
    at<u64>(self, kMapSize)++;
}

// FakeApiCaller::Progress(): queue each new request's file, and hand each loaded one to its lambda.
// Port option --fake-server DIR (not guest behaviour): see ServeProgress below.
std::string g_serve_dir;
void ServeProgress(u64 self);
// Port option (serve mode only): requests the guest fake never queues but the port serves
// (fid -> CApiNotify handler called directly, instead of a guest lambda). See h_served_extra.
std::map<u32, const char*> g_served_extra;
// Port test hook: called at the start of every served Progress (api_notify_live.cpp).
void (*g_serve_tick)(u64 self) = nullptr;
bool request_by_name(u64 self, const char* method);

void Progress(u64 self) {
    if (!g_serve_dir.empty()) return ServeProgress(self);
    u64 end = self + kMapEnd;
    for (u64 n = at<u64>(self, kMap); n != end; n = tree_next(n)) {
        u32 state = at<u32>(n, kState);
        const char* name = ((guest::String*)(n + kName))->data();
        if (state == 0) {
            u64 rm = singleton(kResMgr);
            guest_call(g("_ZN20CGameResourceManager13AddDirectFileEjPKcjbNS_13iPriorityModeE"), {rm, 1, (u64)name, 0, 0, 0});
            at<u32>(n, kState) = 1;
        } else if (state == 1) {
            u64 rm = singleton(kResMgr);
            if (guest_call(g("_ZNK20CGameResourceManager9IsLoadingEv"), {rm}) & 1) continue;
            guest_call(g("_ZN20CGameResourceManager4LockEv"), {rm});
            u64 el = guest_call(g("_ZNK20CGameResourceManager27crResourceElementDirectFileEPKc"), {rm, (u64)name});
            u32 size = (u32)guest_call(g("_ZNK9Framework11CFileLoader4SizeEv"), {el});
            u64 data = guest_call(vslot(el, 10), {el});
            u64 status = 0;  // discarded
            u64 f = at<u64>(n, kFnF);
            u64 args[3] = {f, (u64)&data, (u64)&size};
            guest_call_raw(vslot(f, 6), args, 3, nullptr, 0, (u64)&status);
            guest_call(g("_ZN20CGameResourceManager6UnlockEv"), {rm});
            name = ((guest::String*)(n + kName))->data();
            guest_call(g("_ZN20CGameResourceManager16RemoveDirectFileEPKc"), {rm, (u64)name});
            at<u32>(n, kState) = 2;
        }
    }
}

// FakeApiCaller::IsRequesting(FunctionID): an unknown request counts as in flight.
bool IsRequesting(u64 self, u32 fid) {
    u64 n = find(self, fid);
    return !n || at<u32>(n, kState) != 2;
}

// FakeApiCaller::Release(): empties the map.
void Release(u64 self) {
    tree_destroy(at<u64>(self, kMapEnd));
    at<u64>(self, kMap) = self + kMapEnd;
    at<u64>(self, kMapEnd) = 0;
    at<u64>(self, kMapSize) = 0;
}

// The request methods: queue the canned file with this API's lambda; Status 1.
void Request_(u64 status, u64 self, const Request& r) {
    alignas(16) u64 fn[6] = {lib_base() + r.lambda_vt, self, 0, 0, 0, 0};
    at<u64>((u64)fn, kFunctionF) = (u64)fn;
    AddLocalFile(self, r.fid, (const char*)(lib_base() + r.file), (u64)fn);
    function_destroy((u64)fn);
    at<u64>(status, 0) = 1;
}

// Port helper (queue_request; once the api_notify_live.cpp test hook, removed): queues the request of the
// FakeApiCaller method `method` (e.g. "Gacha") as if the game had called it; the native request
// methods ignore their arguments. False if there is no such method.
// The FakeApiCaller request table entry of a method name (for the drive hook's arguments).
const Request* request_entry(const char* method) {
    for (const Request& r : kRequests) {
        const char* p = r.sym + strlen("_ZN13FakeApiCaller");
        char* e;
        unsigned long n = strtoul(p, &e, 10);
        if (strlen(method) == n && strncmp(e, method, n) == 0) return &r;
    }
    return nullptr;
}
std::string method_symbol(const char* method) {
    const Request* r = request_entry(method);
    return r ? r->sym : "";
}
u32 method_fid(const char* method) {
    const Request* r = request_entry(method);
    return r ? r->fid : 0;
}

// `method` is "Name" or "Name:arg1:arg2..." (integer arguments in x1.., passed to the local
// server's capture in-process; string arguments as null).
bool request_by_name(u64 self, const char* method) {
    std::string m = method, name = m.substr(0, m.find(':'));
    u64 x[8] = {self};
    int k = 1;
    for (size_t p = m.find(':'); p != std::string::npos && k < 8; p = m.find(':', p + 1))
        x[k++] = strtoull(m.c_str() + p + 1, nullptr, 0);
    for (const Request& r : kRequests) {
        const char* p = r.sym + strlen("_ZN13FakeApiCaller");
        char* e;
        unsigned long n = strtoul(p, &e, 10);
        if (name.size() != n || strncmp(e, name.c_str(), n) != 0) continue;
        if (server::enabled()) server_port::capture(r.sym, r.fid, x);
        u64 st = 0;
        Request_((u64)&st, self, r);
        return true;
    }
    return false;
}

// The lambdas' operator()(s8*& data, u32& size) -> Status (x8).
// Common case: return CApiNotify::On<Api>Res(owner + 0x60, data, size).
void Lambda(u64 status, u64 functor, u64 data_ref, u64 size_ref, u64 handler, u64* x0) {
    u64 owner = at<u64>(functor, 8);
    u64 args[3] = {owner + kNotify, at<u64>(data_ref, 0), size_ref};
    *x0 = guest_call_raw(handler, args, 3, nullptr, 0, status).x0;
}

// Login / SimpleLogin: deserialize a fake player {"Player": {"Id": random, "Name": "Dummy_%x"}}
// into CParameterManager, then OnGetPlayerRes. (The guest also calls gethostname into a
// buffer it never reads; that call is left out.)
void LoginLambda(u64 status, u64 functor, u64 data_ref, u64 size_ref, u64* x0) {
    u64 owner = at<u64>(functor, 8);
    const u64 random = g("_ZN4Aska6RandomEv");
    char name[0x40];
    u32 r1 = (u32)guest_call(random, {});
    snprintf(name, sizeof name, "Dummy_%x", r1);
    u32 id = (u32)guest_call(random, {});

    alignas(16) u8 ason[0x90];
    u64 a = (u64)ason, tmp[2] = {};
    auto call8 = [&](u64 fn, std::initializer_list<u64> ints) {
        guest_call_raw(fn, ints.begin(), ints.size(), nullptr, 0, (u64)tmp);
    };
    guest_call(g("_ZN4Aska4ASONC1Ev"), {a});
    guest_call(g("_ZN4Aska4ASON4InitEjb"), {a, 0x4000, 1});
    const u64 make_map = g("_ZN4Aska4ASON14MakeAValue_MapEPNS0_6AValueEj");
    const u64 set_string = g("_ZN4Aska4ASON6AValue9SetStringEPKcPS0_");
    call8(make_map, {a, a + 0x60, 4});
    // root map entries: {key AValue, value AValue} (0x40 each); AMap = {entries, count} at +0x68.
    u64 root = at<u32>(a, 0x70) ? at<u64>(a, 0x68) : 0;
    call8(set_string, {root, lib_base() + 0x27a4177 /* "Player" */, a});
    u64 player = at<u32>(a, 0x70) ? at<u64>(a, 0x68) + 0x20 : 0;
    call8(make_map, {a, player, 2});
    call8(set_string, {at<u32>(player, 0x10) ? at<u64>(player, 8) : 0, lib_base() + 0x272e7f6 /* "Id" */, a});
    u64 e = at<u64>(player, 8);
    at<u32>(e, 0x20) = 2;  // uint
    at<u64>(e, 0x28) = id;
    call8(set_string, {at<u32>(player, 0x10) >= 2 ? at<u64>(player, 8) + 0x40 : 0, lib_base() + 0x28d84d4 /* "Name" */, a});
    call8(set_string, {at<u32>(player, 0x10) >= 2 ? at<u64>(player, 8) + 0x60 : 0, (u64)name, a});
    u64 pm = at<u64>(g("_ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE"), 0);
    guest_call(g("_ZN17CParameterManager11DeserializeEPKN4Aska4ASON6AValue4AMapE"), {pm, a + 0x68});
    guest_call(g("_ZN4Aska4ASOND1Ev"), {a});

    u64 args[3] = {owner + kNotify, at<u64>(data_ref, 0), size_ref};
    *x0 = guest_call_raw(g("_ZN10CApiNotify14OnGetPlayerResEPaRj"), args, 3, nullptr, 0, status).x0;
}

// Constructor: fiber unit (stack 0x600) registered with the root fiber kernel, empty map,
// CApiNotify(this), then CErrorHandlerWrap::SetFakeAppCaller().
void Construct(u64 self) {
    const u64 vt = g("_ZTV13FakeApiCaller");
    at<u64>(self, 0) = g("_ZTV10IApiCaller") + 0x10;
    guest_call(g("_ZN9Framework10CFiberUnitC2Ej"), {self + 8, 0x600});
    at<u64>(self, 0x50) = 0;
    at<u64>(self, 8) = vt + 0x700;
    at<u64>(self, 0) = vt + 0x10;
    at<u64>(self, 0x48) = 0;
    at<u64>(self, 0x40) = self + 0x48;
    guest_call(g("_ZN10CApiNotifyC1EP10IApiCaller"), {self + kNotify, self});
    u64 task = singleton("_ZN9Framework10TSingletonINS_12CApplication9CMainTaskEE11m_pInstanceE");
    u64 kernel = guest_call(g("_ZN9Framework12CApplication9CMainTask16rRootFiberKernelEv"), {task});
    guest_call(vslot(kernel, 9), {kernel, self + 8});
    u64 ehw = singleton("_ZN9Framework10TSingletonI17CErrorHandlerWrapE11m_pInstanceE");
    guest_call(g("_ZN17CErrorHandlerWrap16SetFakeAppCallerEv"), {ehw});
}

// Destructor body (~FakeApiCaller D1); D0 also frees the object.
void Destruct(u64 self, bool deleting) {
    const u64 vt = g("_ZTV13FakeApiCaller");
    at<u64>(self, 8) = vt + 0x700;
    at<u64>(self, 0) = vt + 0x10;
    tree_destroy(at<u64>(self, kMapEnd));
    at<u64>(self, kMap) = self + kMapEnd;
    at<u64>(self, kMapSize) = 0;
    at<u64>(self, kMapEnd) = 0;
    guest_call(g("_ZN10CApiNotifyD1Ev"), {self + kNotify});
    tree_destroy(at<u64>(self, kMapEnd));  // the map member's own destructor (now empty)
    guest_call(g("_ZN9Framework10CFiberUnitD1Ev"), {self + 8});
    if (deleting) guest_call(g("_ZdlPv"), {self});
}

// ---- port option: the fake server, live (--fake-server DIR) ---------------------------
// Our invention, not guest behaviour. The shipped game never constructs FakeApiCaller and
// never shipped its FakeApi/*.msgp files. With --fake-server DIR:
//  - after CGame::OnInitialize, a FakeApiCaller is constructed (its own constructor: fiber,
//    CApiNotify, CErrorHandlerWrap::SetFakeAppCaller) and put in TSingleton<CApiCaller> in
//    place of the NetworkApiCaller, which stays alive but unused;
//  - Progress answers each request from DIR/<name>.msgp (the file name without "FakeApi/")
//    instead of the resource manager, one frame after the request, like the guest's two
//    steps. A missing file is answered with an empty map (0x80) and logged; the guest would
//    crash on it.
// The handlers are called exactly as the guest lambdas call them.
void ServeProgress(u64 self) {
    if (g_serve_tick) g_serve_tick(self);
    u64 end = self + kMapEnd;
    for (u64 n = at<u64>(self, kMap); n != end; n = tree_next(n)) {
        u32 state = at<u32>(n, kState);
        if (state == 0) {
            at<u32>(n, kState) = 1;
            continue;
        }
        if (state != 1) continue;
        std::string name = ((guest::String*)(n + kName))->str();
        std::string file = name.rfind("FakeApi/", 0) == 0 ? name.substr(8) : name;
        std::string path = g_serve_dir + "/" + file;
        std::vector<char> body;
        // The in-process server (--server inproc): the local server (top-level server/) answers the
        // request the client made (server_port::take: kept when it was made) through its one
        // request lifecycle, server::answer, as soa-server's wire does; what no handler answers comes
        // from DIR, or {} (the guest would crash on a missing file). The story campaign's data is
        // added either way (server::answer).
        u32 fid = at<u32>(n, kKey);
        server::Request req = server_port::take(fid);
        if (req.method.empty() && server::enabled()) LOGW("fakeapi", "fid %08x: %s: no request was kept for it", fid, file.c_str());
        server::Reply reply = server::answer(req, [&] {
            std::vector<u8> b;
            if (FILE* f = fopen(path.c_str(), "rb")) {
                char buf[65536];
                size_t k;
                while ((k = fread(buf, 1, sizeof buf, f)) > 0) b.insert(b.end(), buf, buf + k);
                fclose(f);
                LOGI("fakeapi", "fid %08x: %s (%zu bytes)", fid, path.c_str(), b.size());
            } else {
                b.push_back(0x80);
                LOGW("fakeapi", "fid %08x: %s missing; answering {}", fid, path.c_str());
            }
            return b;
        });
        if (reply.handled) {
            if (u32 code = reply.error_code) {
                // Port plumbing (--server inproc): the local server refused the request. Do what
                // CApiNotify::OnProtocolError does on the network path: ErrorHandler::Handle(fid,
                // Status = code), whose CErrorHandlerWrap callback (CallBackCore -> ErrKind ->
                // OpenDialogCatch) shows master_text error_message_text_<code>, while the entry is
                // still in flight (IsRequesting true, so an Auto-registered screen keeps its
                // handler); then CApiNotify+0x514 = code. The body isn't delivered (no On*Res),
                // as on the network path. IsSuccess / IsFailure / ErrorCode report the code.
                u64 eh = at<u64>(g("_ZN9Framework10TSingletonI12ErrorHandlerE11m_pInstanceE"), 0);
                alignas(16) int64_t status = (int64_t)code;
                LOGI("fakeapi", "fid %08x: %s refused by the local server with error %u", fid, file.c_str(), code);
                if (eh)
                    guest_call(g("_ZN12ErrorHandler6HandleEN4Aska5Yayoi7GameRPC12GameProtocol10FunctionIDENS0_6StatusE"),
                               {eh, fid, (u64)&status});
                at<u32>(self + kNotify, 0x514) = code;
                at<u32>(n, kState) = 2;
                server_port::packet_log::refused(fid, code);
                continue;
            }
            LOGI("fakeapi", "fid %08x: %s from the local server (%zu bytes)", fid, file.c_str(), reply.body.size());
        }
        body.assign(reply.body.begin(), reply.body.end());
        server_port::packet_log::reply(fid, body);  // --log-packets (after the campaign's additions)
        // Guest-heap copy: the handler's ASON may point into it while it runs.
        u64 data = (u64)guest::new_array_nothrow(body.size() + 16);
        memcpy((void*)data, body.data(), body.size());
        u32 size = (u32)body.size();
        u64 status = 0;
        u64 f = at<u64>(n, kFnF);
        u64 args[3] = {f, (u64)&data, (u64)&size};
        at<u32>(n, kState) = 2;  // before the call: a handler may queue this API again
        auto extra = g_served_extra.find(at<u32>(n, kKey));
        if (extra != g_served_extra.end()) {
            u64 hargs[3] = {self + kNotify, data, (u64)&size};
            guest_call_raw(g(extra->second), hargs, 3, nullptr, 0, (u64)&status);
        } else {
            guest_call_raw(vslot(f, 6), args, 3, nullptr, 0, (u64)&status);
        }
        guest::delete_array((void*)data);
    }
}

// --fake-server-schema FILE (with the route): writes the response schema the handlers
// accept, i.e. what CParameterManager::Deserialize walks: each registered InfoBase (the list at
// CParameterManager+0x68, plus the one at +0x600) with its top-level key (pParseName), its
// properties (map<u32 CHash32(key), IParameterProperty*> at +0x08: key name recovered by
// hashing every string in .rodata, and the property's class) and child infos (map at +0x20).
void dump_schema_info(FILE* f, const std::map<u32, std::string>& dict, u64 info, int depth) {
    auto key_name = [&](u32 h) {
        auto it = dict.find(h);
        char b[16];
        snprintf(b, sizeof b, "#%08x", h);
        return it != dict.end() ? it->second : std::string(b);
    };
    std::string pad(depth * 2, ' ');
    u64 name = guest_call(vslot(info, 3), {info});
    fprintf(f, "%s%s  [%s]\n", pad.c_str(), name ? (const char*)name : "?", describe_guest_addr(at<u64>(info, 0)).c_str());
    // Only InfoBase subclasses have the two maps; the CParameter* sets in the list don't.
    auto valid_map = [](u64 m) {
        u64 begin = at<u64>(m, 0), end = m + 8, size = at<u64>(m, 0x10);
        if (size > 100000) return false;
        if (size == 0) return begin == end;
        u64 root = at<u64>(end, 0);
        return root && at<u64>(root, 0x10) == end;
    };
    if (depth > 6 || !valid_map(info + 0x08) || !valid_map(info + 0x20)) return;
    for (u64 n = at<u64>(info, 0x08); n && n != info + 0x10; n = tree_next(n)) {
        u64 prop = at<u64>(n, 0x28);
        fprintf(f, "%s  .%s : %s  @+%#" PRIx64 " #%08x\n", pad.c_str(), key_name(at<u32>(n, 0x20)).c_str(),
                prop ? describe_guest_addr(at<u64>(prop, 0)).c_str() : "null", (u64)(prop - info),
                at<u32>(n, 0x20));
    }
    for (u64 n = at<u64>(info, 0x20); n && n != info + 0x28; n = tree_next(n)) {
        u64 child = at<u64>(n, 0x28);
        u64 pm = at<u64>(g("_ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE"), 0);
        if (child > pm && child < pm + 0x10000)
            fprintf(f, "%s  child %s (CParameterManager+%#" PRIx64 "):\n", pad.c_str(), key_name(at<u32>(n, 0x20)).c_str(),
                    (u64)(child - pm));
        else
            fprintf(f, "%s  child %s:\n", pad.c_str(), key_name(at<u32>(n, 0x20)).c_str());
        if (child) dump_schema_info(f, dict, child, depth + 2);
    }
}

void dump_schema(const char* path) {
    FILE* f = fopen(path, "w");
    if (!f) return;
    std::map<u32, std::string> dict;
    const char* ro = (const char*)(lib_base() + 0x26d41e0);  // .rodata (3.7.0)
    const size_t ro_size = 0x27ede4;
    for (size_t i = 0; i < ro_size;) {
        size_t j = i;
        while (j < ro_size && ro[j] >= 0x20 && ro[j] < 0x7f) j++;
        if (j < ro_size && ro[j] == 0 && j - i >= 1 && j - i < 64)
            for (size_t k = i; k < j; k++) dict.emplace(server::chash32(ro + k, j - k), std::string(ro + k, j - k));
        i = j + 1;
    }
    u64 pm = at<u64>(g("_ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE"), 0);
    fprintf(f, "# FakeApiCaller response schema (port dump; key names by CHash32 of .rodata strings)\n");
    for (u64 n = at<u64>(pm, 0x70); n != pm + 0x68; n = at<u64>(n, 8)) {
        u64 info = at<u64>(n, 0x10);
        if (info > pm && info < pm + 0x10000) fprintf(f, "# at CParameterManager+%#" PRIx64 ":\n", (u64)(info - pm));
        dump_schema_info(f, dict, info, 0);
    }
    fprintf(f, "# CParameterManager+0x600 (map or array under its own key)\n");
    dump_schema_info(f, dict, pm + 0x600, 0);
    fprintf(f, "# CParameterManager+0xf70: child infos by name hash\n");
    for (u64 n = at<u64>(pm, 0xf70); n != pm + 0xf78; n = tree_next(n)) dump_schema_info(f, dict, at<u64>(n, 0x28), 0);
    // Array element classes (InfoBaseArray<T> registers no properties of its own): a fresh
    // element, constructed and initialised, with its property offsets.
    // (Only classes with an exported constructor: the inlined ones also construct the
    // embedded properties.)
    const std::pair<const char*, u32> elems[] = {{"CPersonStatusInfo", 0x1690}, {"CMissionStageInfo", 0x1000}, {"Sphere211FloorAssetInfo", 0x800}};
    for (auto [cls, size] : elems) {
        std::string c = std::to_string(strlen(cls)) + cls;
        auto opt = [](const std::string& m) { return main_lib()->sym(m.c_str()); };
        u64 ctor = opt("_ZN" + c + "C2Ev"), init = opt("_ZN" + c + "10InitializeEv");
        if (!ctor || !init) continue;
        u64 obj = (u64)guest::new_array_nothrow(size);
        memset((void*)obj, 0, size);
        guest_call(ctor, {obj});
        guest_call(init, {obj});
        fprintf(f, "# element %s (0x%x bytes)\n", cls, size);
        dump_schema_info(f, dict, obj, 0);  // leaked: a one-off debug dump
    }
    fclose(f);
    LOGI("fakeapi", "response schema written to %s", path);
}

u64 g_fake_caller = 0;
u64 g_orig_game_init = 0;

bool serve_enabled() {
    const std::string& d = options().client.fake_server_dir;  // --fake-server (--server inproc defaults it)
    if (d.empty()) return false;
    g_serve_dir = d;
    return true;
}

// CGame::OnInitialize, then swap the API caller.
void h_game_init(Cpu& c) {
    u64 game = c.x(0);
    guest_call(g_orig_game_init, {game});
    u64 slot = g("_ZN9Framework10TSingletonI10CApiCallerE11m_pInstanceE");
    // FakeApiCaller is 0x60 bytes plus CApiNotify (under 0x600); the rest is slack.
    u64 self = (u64)guest::new_array_nothrow(0x2000);
    memset((void*)self, 0, 0x2000);
    guest_call(g("_ZN13FakeApiCallerC2Ev"), {self});
    u64 old = at<u64>(slot, 0);
    at<u64>(slot, 0) = self;
    g_fake_caller = self;
    if (!options().client.fake_server_schema.empty()) dump_schema(options().client.fake_server_schema.c_str());
    LOGI("fakeapi", "fake server %s: FakeApiCaller at %#" PRIx64 " replaces the API caller %#" PRIx64, g_serve_dir.c_str(),
         (u64)self, (u64)old);
}
// Port code for the restore run's local server: queues the request of the FakeApiCaller method
// `method` (e.g. "GetPlayMission") as if the game had called it, so the server can deliver data
// the offline client never asks for. False without the fake server or for an unknown method.
bool queue_request(const char* method) {
    if (!g_fake_caller) return false;
    for (const Request& r : kRequests) {
        const char* p = r.sym + strlen("_ZN13FakeApiCaller");
        char* e;
        unsigned long n = strtoul(p, &e, 10);
        if (strlen(method) != n || strncmp(e, method, n) != 0) continue;
        // The local server sees it like a request the game made (no arguments).
        u64 x[8] = {g_fake_caller, 0, 0, 0, 0, 0, 0, 0};
        if (server::enabled()) server_port::capture(r.sym, r.fid, x);
        return request_by_name(g_fake_caller, method);
    }
    return false;
}

NATIVE_ROUTE_FUNCTION_ORIG_IF("_ZN5CGame12OnInitializeEv", h_game_init, "port option --fake-server: FakeApiCaller as the API caller",
                              serve_enabled, &g_orig_game_init);

namespace {

// ---- hooks --------------------------------------------------------------------------------

template <int I>
void h_request(Cpu& c) {
    // The in-process server (--server inproc; not guest behaviour): the request's arguments, kept
    // until Progress answers it (server::answer).
    if (server::enabled()) {
        u64 x[8];
        for (int k = 0; k < 8; k++) x[k] = c.x(k);
        // the request as the wire carries it (MissionEnd & co.: with the client's battle log)
        server_port::remember(server_port::inproc_request(kRequests[I].sym, kRequests[I].fid, x));
    }
    Request_(c.x(8), c.x(0), kRequests[I]);
}

template <int... I>
constexpr std::array<HostFn, sizeof...(I)> request_hooks(std::integer_sequence<int, I...>) {
    return {&h_request<I>...};
}
constexpr auto kRequestHooks = request_hooks(std::make_integer_sequence<int, kNumRequests>{});

// One hook for every lambda operator(): the functor's vtable says which API it is.
void h_lambda(Cpu& c) {
    u64 vt = at<u64>(c.x(0), 0) - lib_base();
    for (const Request& r : kRequests) {
        if (r.lambda_vt != vt) continue;
        u64 x0 = 0;
        if (r.handler) Lambda(c.x(8), c.x(0), c.x(1), c.x(2), g(r.handler), &x0);
        // The in-process server (--server inproc): Login / SimpleLogin apply the local server's answer (the whole
        // player state) instead of the invented "Dummy" player.
        else if (server::enabled()) Lambda(c.x(8), c.x(0), c.x(1), c.x(2), g("_ZN10CApiNotify14OnGetPlayerResEPaRj"), &x0);
        else LoginLambda(c.x(8), c.x(0), c.x(1), c.x(2), &x0);
        c.set_x(0, x0);
        return;
    }
    fatal("FakeApiCaller lambda with unknown vtable 0x%" PRIx64, (u64)vt);
}

template <u64 V>
void h_status(Cpu& c) { at<u64>(c.x(8), 0) = V; }

// FakeApiCaller::GetGachaInData(): the guest only returns Status 0 (nothing queued, so the gacha
// screen gets no GachaHashMap and lists no gachas). Port option --fake-server (not guest
// behaviour): queue it like the other requests, from DIR/gacha_in_data.msgp, answered by
// CApiNotify::OnGetGachaInDataRes (the handler NetworkApiCaller's response goes to).
constexpr char kGetGachaInData[] = "_ZN13FakeApiCaller14GetGachaInDataEv";
constexpr u32 kFidGetGachaInData = 0x8e4a88d7;
void h_get_gacha_in_data(Cpu& c) {
    if (g_serve_dir.empty()) {
        at<u64>(c.x(8), 0) = 0;
        return;
    }
    // Any request's lambda gives the queue entry a valid guest std::function (copied and
    // destroyed by the map); ServeProgress calls the handler below instead of it.
    const Request* rate = nullptr;
    for (const Request& r : kRequests)
        if (r.fid == 0xd6bcb49d) rate = &r;  // GetGachaRate
    g_served_extra[kFidGetGachaInData] = "_ZN10CApiNotify19OnGetGachaInDataResEPaRj";
    if (server::enabled()) {
        u64 x[8] = {c.x(0)};
        server_port::capture(kGetGachaInData, kFidGetGachaInData, x);
    }
    u64 self = c.x(0);
    alignas(16) u64 fn[6] = {lib_base() + rate->lambda_vt, self, 0, 0, 0, 0};
    at<u64>((u64)fn, kFunctionF) = (u64)fn;
    static const char file[] = "FakeApi/gacha_in_data.msgp";
    AddLocalFile(self, kFidGetGachaInData, file, (u64)fn);
    function_destroy((u64)fn);
    at<u64>(c.x(8), 0) = 1;
}
// FakeApiCaller::GetWorldMapInfoList(u32 episode): the guest only returns Status 0. Restore run
// (--server inproc; port code, not guest behaviour): queued like GetGachaInData and answered by
// CApiNotify::OnGetWorldMapInfoListRes, the handler NetworkApiCaller's response goes to; the local
// server (server/campaign.cpp) fills the body. On another caller it stays a Status-only method.
constexpr char kGetWorldMapInfoList[] = "_ZN13FakeApiCaller19GetWorldMapInfoListEj";
constexpr u32 kFidGetWorldMapInfoList = 0x15a9bdbd;
void h_get_world_map_info_list(Cpu& c) {
    if (g_serve_dir.empty() || !server::campaign::enabled()) {
        at<u64>(c.x(8), 0) = 0;
        return;
    }
    u64 x[8];
    for (int i = 0; i < 8; i++) x[i] = c.x(i);
    server_port::remember(server_port::inproc_request(kGetWorldMapInfoList, kFidGetWorldMapInfoList, x));
    const Request* rate = nullptr;
    for (const Request& r : kRequests)
        if (r.fid == 0xd6bcb49d) rate = &r;  // GetGachaRate: any request's lambda will do
    g_served_extra[kFidGetWorldMapInfoList] = "_ZN10CApiNotify24OnGetWorldMapInfoListResEPaRj";
    u64 self = c.x(0);
    alignas(16) u64 fn[6] = {lib_base() + rate->lambda_vt, self, 0, 0, 0, 0};
    at<u64>((u64)fn, kFunctionF) = (u64)fn;
    static const char file[] = "FakeApi/world_map_info_list.msgp";
    AddLocalFile(self, kFidGetWorldMapInfoList, file, (u64)fn);
    function_destroy((u64)fn);
    at<u64>(c.x(8), 0) = 1;
}

template <u64 V>
void h_const(Cpu& c) { c.set_x(0, V); }

// IApiCaller methods FakeApiCaller doesn't override: the base-class stub returns Status 0 and
// sends nothing. In-process server (--server inproc; not guest behaviour): on the FakeApiCaller, queue them
// for the local server like the other requests (the restored 3.7.0 party screen uses them),
// answered by the CApiNotify handler NetworkApiCaller's response goes to. Otherwise the guest
// behaviour.
bool on_fake_caller(u64 self) {
    static const u64 fake_vt = main_lib()->sym("_ZTV13FakeApiCaller") + 0x10;
    return server::enabled() && !g_serve_dir.empty() && at<u64>(self, 0) == fake_vt;
}
void queue_base_method(Cpu& c, u32 fid, const char* handler, const char* file) {
    u64 self = c.x(0);
    const Request* any = nullptr;
    for (const Request& r : kRequests)
        if (r.fid == 0xd6bcb49d) any = &r;  // GetGachaRate: a valid lambda for the queue entry
    g_served_extra[fid] = handler;
    alignas(16) u64 fn[6] = {lib_base() + any->lambda_vt, self, 0, 0, 0, 0};
    at<u64>((u64)fn, kFunctionF) = (u64)fn;
    AddLocalFile(self, fid, file, (u64)fn);
    function_destroy((u64)fn);
    at<u64>(c.x(8), 0) = 1;
}

// IApiCaller::UpdatePartySet(PartySetInfo const&): the server gets the party set as
// PartySetInfo::Serialize() text (what NetworkApiCaller sends).
constexpr char kUpdatePartySet[] = "_ZN10IApiCaller14UpdatePartySetERK12PartySetInfo";
void h_update_party_set(Cpu& c) {
    if (!on_fake_caller(c.x(0))) {
        at<u64>(c.x(8), 0) = 0;  // guest behaviour
        return;
    }
    static const u64 serialize = main_lib()->sym("_ZNK12PartySetInfo9SerializeEv");
    guest::String text;
    guest_call(serialize, GuestArgs().i(c.x(1)).sret(&text));
    std::string s = text.str();
    text.destroy();
    u64 x[8] = {c.x(0), (u64)s.c_str()};
    server_port::capture("_ZN13FakeApiCaller14UpdatePartySetEPKa", 0xc119d0d8, x);
    queue_base_method(c, 0xc119d0d8, "_ZN10CApiNotify19OnUpdatePartySetResEPaRj", "FakeApi/party_set_update.msgp");
}

// IApiCaller::SetAssist(unsigned long character, unsigned long assist character).
constexpr char kSetAssist[] = "_ZN10IApiCaller9SetAssistEmm";
void h_set_assist(Cpu& c) {
    if (!on_fake_caller(c.x(0))) {
        at<u64>(c.x(8), 0) = 0;  // guest behaviour
        return;
    }
    u64 x[8] = {c.x(0), c.x(1), c.x(2)};
    server_port::capture("_ZN13FakeApiCaller9SetAssistEmm", 0x741e0072, x);
    queue_base_method(c, 0x741e0072, "_ZN10CApiNotify14OnSetAssistResEPaRj", "FakeApi/set_assist.msgp");
}

// IApiCaller::UpdateView(Common::ViewFlagType kind, unsigned long flags): the "already seen"
// flags of UI tutorials and dialogs (CTutorialManager::ST_Net_Tutoflag).
constexpr char kUpdateView[] = "_ZN10IApiCaller10UpdateViewEN6Common12ViewFlagTypeEm";
void h_update_view(Cpu& c) {
    if (!on_fake_caller(c.x(0))) {
        at<u64>(c.x(8), 0) = 0;  // guest behaviour
        return;
    }
    u64 x[8] = {c.x(0), (u8)c.x(1), c.x(2)};
    server_port::capture("_ZN13FakeApiCaller10UpdateViewEhm", 0xa2eb69ba, x);
    queue_base_method(c, 0xa2eb69ba, "_ZN10CApiNotify15OnUpdateViewResEPaRj", "FakeApi/update_view.msgp");
}

// IApiCaller::GetMissionList(): CPhase_Mission::Progress asks it for the story campaign's mission
// select (docs/api.md). FakeApiCaller doesn't override the base stub, which returns Status 0 and
// sends nothing, so on this route the server never saw the request (the select used the
// ActiveMissionList of earlier replies). On the FakeApiCaller (port code, not guest behaviour; found
// by tests/diff, whose packet logs showed it only on the wire) it is queued like SetAssist, answered
// by CApiNotify::OnGetMissionListRes. The wire call carries an int, always 0 from
// NetworkApiCaller::GetMissionList's request lambda: it is captured as that 0, as the wire decodes it.
constexpr char kGetMissionList[] = "_ZN10IApiCaller14GetMissionListEv";
void h_get_mission_list(Cpu& c) {
    if (!on_fake_caller(c.x(0))) {
        at<u64>(c.x(8), 0) = 0;  // guest behaviour
        return;
    }
    u64 x[8] = {c.x(0), 0};
    server_port::capture("_ZN13FakeApiCaller14GetMissionListEi", 0x57308f4d, x);
    queue_base_method(c, 0x57308f4d, "_ZN10CApiNotify19OnGetMissionListResEPaRj", "FakeApi/mission_list.msgp");
}

// Status-only FakeApiCaller methods (the guest stores a Status and sends nothing) that the
// local server answers in-process (agent server-rules; port code, not guest behaviour): the
// arguments go to server_port::capture and the request is queued with NetworkApiCaller's FunctionID,
// answered by the CApiNotify handler NetworkApiCaller's response goes to. On another caller
// the guest's Status. The gear screens (CCustomGear) and the favor-achievement
// receive (CAdjutantSelect -> AchievementListReceive) use them.
struct ServedStatusOnly {
    const char* sym;
    u64 status;  // the guest's Status
    u32 fid;     // NetworkApiCaller's FunctionID (docs/api.md)
    const char* handler;
    const char* file;  // the name the queue entry and the logs show
};
const ServedStatusOnly kServedStatusOnly[] = {
    {"_ZN13FakeApiCaller11GetGearInfoEv", 0, 0x388092cc, "_ZN10CApiNotify16OnGetGearInfoResEPaRj", "FakeApi/gear_info.msgp"},
    {"_ZN13FakeApiCaller10AttachGearEmmj", 0, 0xbce2e7f2, "_ZN10CApiNotify15OnAttachGearResEPaRj", "FakeApi/attach_gear.msgp"},
    {"_ZN13FakeApiCaller12ClearNewGearERKN9Framework10CSTLVectorImEE", 0, 0xb0092669, "_ZN10CApiNotify17OnClearNewGearResEPaRj",
     "FakeApi/clear_new_gear.msgp"},
    {"_ZN13FakeApiCaller8SellGearERKN9Framework10CSTLVectorImEE", 0, 0x1700186d, "_ZN10CApiNotify13OnSellGearResEPaRj", "FakeApi/sell_gear.msgp"},
    {"_ZN13FakeApiCaller10RemoveGearEm", 0, 0x33da88ce, "_ZN10CApiNotify15OnRemoveGearResEPaRj", "FakeApi/remove_gear.msgp"},
    {"_ZN13FakeApiCaller12GenerateGearEmjRKN9Framework10CSTLVectorImEE", 0, 0xaf1c5d33, "_ZN10CApiNotify17OnGenerateGearResEPaRj",
     "FakeApi/generate_gear.msgp"},
    {"_ZN13FakeApiCaller15UpdateGearStockEv", 0, 0xd10e6806, "_ZN10CApiNotify20OnUpdateGearStockResEPaRj", "FakeApi/update_gear_stock.msgp"},
    {"_ZN13FakeApiCaller22AchievementListReceiveERKN9Framework10CSTLVectorImEE", 1, 0xbbc99ccf,
     "_ZN10CApiNotify27OnAchievementListReceiveResEPaRj", "FakeApi/achievement_list_receive.msgp"},
};
bool is_served_status_only(const char* sym) {
    for (const auto& s : kServedStatusOnly)
        if (!strcmp(s.sym, sym)) return true;
    return false;
}
template <int I>
void h_served_status_only(Cpu& c) {
    const ServedStatusOnly& s = kServedStatusOnly[I];
    if (!on_fake_caller(c.x(0))) {
        at<u64>(c.x(8), 0) = s.status;  // guest behaviour
        return;
    }
    u64 x[8];
    for (int k = 0; k < 8; k++) x[k] = c.x(k);
    server_port::capture(s.sym, s.fid, x);
    queue_base_method(c, s.fid, s.handler, s.file);
}
template <int... I>
constexpr std::array<HostFn, sizeof...(I)> served_hooks(std::integer_sequence<int, I...>) {
    return {&h_served_status_only<I>...};
}
constexpr auto kServedHooks =
    served_hooks(std::make_integer_sequence<int, (int)(sizeof(kServedStatusOnly) / sizeof(kServedStatusOnly[0]))>{});

// FakeApiCaller::DeepSpaceActiveList(): the guest only returns Status 0 (nothing queued), so the
// deep space screen (CDeepSpace::Progress) never gets its area / ship lists. Restore run
// (--server inproc; port code, not guest behaviour): queued like the base-class methods above and
// answered by CApiNotify::OnDeepSpaceActiveListRes, the handler NetworkApiCaller's response goes
// to; the local server (server/src/api/deepspace/deepspace.cpp) fills the body. Otherwise the guest behaviour.
constexpr char kDeepSpaceActiveList[] = "_ZN13FakeApiCaller19DeepSpaceActiveListEv";
void h_deep_space_active_list(Cpu& c) {
    if (!on_fake_caller(c.x(0))) {
        at<u64>(c.x(8), 0) = 0;  // guest behaviour
        return;
    }
    u64 x[8] = {c.x(0)};
    server_port::capture(kDeepSpaceActiveList, 0xa7a82ef5, x);
    queue_base_method(c, 0xa7a82ef5, "_ZN10CApiNotify24OnDeepSpaceActiveListResEPaRj", "FakeApi/deep_space_active_list.msgp");
}

// Sphere 211 (restore run, --server inproc; agent sphere211): the Sphere211* requests. The
// IApiCaller base methods return Status 0 and send nothing, and FakeApiCaller's own overrides
// (ReturnSphere211, StaminaHeal, UseRerollItem, FloorClear, SelectedFloor) only return a Status.
// In-process server (--server inproc; not guest behaviour): on the FakeApiCaller, queue them for the local
// server (server/src/api/sphere211/sphere211.cpp), answered by the CApiNotify handler NetworkApiCaller's
// response goes to. Otherwise the guest behaviour. {hooked symbol, capture symbol (the
// FakeApiCaller-style mangling server_port::capture parses), fid (docs/api.md), handler}.
struct SphereMethod {
    const char *sym, *capture;
    u32 fid;
    const char* handler;
};
constexpr SphereMethod kSphere[] = {
    {"_ZN10IApiCaller16GetSphere211InfoEv", "_ZN13FakeApiCaller16GetSphere211InfoEv", 0x1e03058b, "_ZN10CApiNotify21OnGetSphere211InfoResEPaRj"},
    {"_ZN10IApiCaller23GetSphere211RankingInfoEb", "_ZN13FakeApiCaller23GetSphere211RankingInfoEb", 0x5943ae5c, "_ZN10CApiNotify28OnGetSphere211RankingInfoResEPaRj"},
    {"_ZN10IApiCaller25Sphere211AutoMemberSelectEjjj", "_ZN13FakeApiCaller25Sphere211AutoMemberSelectEjjj", 0x2d0a3ab3, "_ZN10CApiNotify30OnSphere211AutoMemberSelectResEPaRj"},
    {"_ZN10IApiCaller18Sphere211EquipAutoEjjRKN9Framework10CSTLVectorImEE", "_ZN13FakeApiCaller18Sphere211EquipAutoEjjRKN9Framework10CSTLVectorImEE", 0x9ce7e42e, "_ZN10CApiNotify23OnSphere211EquipAutoResEPaRj"},
    {"_ZN10IApiCaller24Sphere211MissionContinueEjjb", "_ZN13FakeApiCaller24Sphere211MissionContinueEjjb", 0x5ac657b3, "_ZN10CApiNotify29OnSphere211MissionContinueResEPaRj"},
    {"_ZN10IApiCaller19Sphere211MissionEndEjj", "_ZN13FakeApiCaller19Sphere211MissionEndEjj", 0x03f169b2, "_ZN10CApiNotify24OnSphere211MissionEndResEPaRj"},
    {"_ZN10IApiCaller22Sphere211MissionFailedEjj", "_ZN13FakeApiCaller22Sphere211MissionFailedEjj", 0x172f3b5f, "_ZN10CApiNotify27OnSphere211MissionFailedResEPaRj"},
    {"_ZN10IApiCaller21Sphere211MissionStartEjjmmmmj", "_ZN13FakeApiCaller21Sphere211MissionStartEjjmmmmj", 0x04ec9513, "_ZN10CApiNotify26OnSphere211MissionStartResEPaRj"},
    {"_ZN13FakeApiCaller15ReturnSphere211Ev", "_ZN13FakeApiCaller15ReturnSphere211Ev", 0x83390f3f, "_ZN10CApiNotify20OnReturnSphere211ResEPaRj"},
    {"_ZN13FakeApiCaller20Sphere211StaminaHealEv", "_ZN13FakeApiCaller20Sphere211StaminaHealEv", 0x3a3ab3ed, "_ZN10CApiNotify25OnSphere211StaminaHealResEPaRj"},
    {"_ZN13FakeApiCaller22Sphere211UseRerollItemEv", "_ZN13FakeApiCaller22Sphere211UseRerollItemEv", 0x19e61236, "_ZN10CApiNotify27OnSphere211UseRerollItemResEPaRj"},
    {"_ZN13FakeApiCaller19Sphere211FloorClearEj", "_ZN13FakeApiCaller19Sphere211FloorClearEj", 0x5187adb1, "_ZN10CApiNotify24OnSphere211FloorClearResEPaRj"},
    {"_ZN13FakeApiCaller22Sphere211SelectedFloorEj", "_ZN13FakeApiCaller22Sphere211SelectedFloorEj", 0xf8371209, "_ZN10CApiNotify27OnSphere211SelectedFloorResEPaRj"},
};
constexpr int kNumSphere = sizeof(kSphere) / sizeof(kSphere[0]);
bool is_sphere_method(const char* sym) {
    for (const SphereMethod& m : kSphere)
        if (!strcmp(sym, m.sym)) return true;
    return false;
}
template <int I>
void h_sphere(Cpu& c) {
    if (!on_fake_caller(c.x(0))) {
        at<u64>(c.x(8), 0) = 0;  // guest behaviour (both the base and the FakeApiCaller bodies)
        return;
    }
    u64 x[8];
    for (int k = 0; k < 8; k++) x[k] = c.x(k);
    server_port::capture(kSphere[I].capture, kSphere[I].fid, x);
    queue_base_method(c, kSphere[I].fid, kSphere[I].handler, "FakeApi/sphere211.msgp");
}
template <int... I>
constexpr std::array<HostFn, sizeof...(I)> sphere_hooks(std::integer_sequence<int, I...>) {
    return {&h_sphere<I>...};
}
constexpr auto kSphereHooks = sphere_hooks(std::make_integer_sequence<int, kNumSphere>{});

// Event rankings and world bosses (restore run, --server inproc; agent events-extras): the
// IApiCaller base methods of the five ranking requests return Status 0 and send nothing, and
// FakeApiCaller::GetWorldBossInfo only returns a Status. In-process server (not guest
// behaviour): on the FakeApiCaller, queue them for the local server (server/src/api/events/ranking.cpp,
// server/src/api/events/world_boss.cpp), answered by the CApiNotify handler NetworkApiCaller's response goes to
// (all plain apply; the ranking results also AddItem / UpdateStackItem). Otherwise the guest
// behaviour. Same row shape as kSphere.
constexpr SphereMethod kEventApi[] = {
    {"_ZN10IApiCaller23CheckEventRankingResultEv", "_ZN13FakeApiCaller23CheckEventRankingResultEv", 0x83809bfb, "_ZN10CApiNotify28OnCheckEventRankingResultResEPaRj"},
    {"_ZN10IApiCaller25ReceiveEventRankingResultEv", "_ZN13FakeApiCaller25ReceiveEventRankingResultEv", 0x4700c6f7, "_ZN10CApiNotify30OnReceiveEventRankingResultResEPaRj"},
    {"_ZN10IApiCaller19GetEventRankingInfoEj", "_ZN13FakeApiCaller19GetEventRankingInfoEj", 0x94456167, "_ZN10CApiNotify24OnGetEventRankingInfoResEPaRj"},
    {"_ZN10IApiCaller20ClearNewEventRankingERKN9Framework10CSTLVectorIjEE", "_ZN13FakeApiCaller20ClearNewEventRankingERKN9Framework10CSTLVectorIjEE", 0xcb1a5781, "_ZN10CApiNotify25OnClearNewEventRankingResEPaRj"},
    {"_ZN10IApiCaller19GetPlayerDetailInfoEj", "_ZN13FakeApiCaller19GetPlayerDetailInfoEj", 0x626e1e5f, "_ZN10CApiNotify24OnGetPlayerDetailInfoResEPaRj"},
    {"_ZN13FakeApiCaller16GetWorldBossInfoEj", "_ZN13FakeApiCaller16GetWorldBossInfoEj", 0x86d6a220, "_ZN10CApiNotify21OnGetWorldBossInfoResEPaRj"},
};
constexpr int kNumEventApi = sizeof(kEventApi) / sizeof(kEventApi[0]);
bool is_event_api(const char* sym) {
    for (const SphereMethod& m : kEventApi)
        if (!strcmp(sym, m.sym)) return true;
    return false;
}
template <int I>
void h_event_api(Cpu& c) {
    if (!on_fake_caller(c.x(0))) {
        at<u64>(c.x(8), 0) = 0;  // guest behaviour (both the base and the FakeApiCaller bodies)
        return;
    }
    u64 x[8];
    for (int k = 0; k < 8; k++) x[k] = c.x(k);
    server_port::capture(kEventApi[I].capture, kEventApi[I].fid, x);
    queue_base_method(c, kEventApi[I].fid, kEventApi[I].handler, "FakeApi/event_extras.msgp");
}
template <int... I>
constexpr std::array<HostFn, sizeof...(I)> event_api_hooks(std::integer_sequence<int, I...>) {
    return {&h_event_api<I>...};
}
constexpr auto kEventApiHooks = event_api_hooks(std::make_integer_sequence<int, kNumEventApi>{});

// IApiCaller::EndMissionTalk(unsigned int type, unsigned int mission, unsigned char, unsigned int):
// the end of a story mission's scene. 3.7.0's EventScenario::CEventScenario::Exit sends it
// (CErrorHandlerWrap::Auto, fid 1d00a78c); FakeApiCaller doesn't override it, so the base stub
// sends nothing and a story mission never clears. On the FakeApiCaller route (port code, not
// guest behaviour) the request goes to the local server as soa-server's wire does
// (server::answer): the scene's effect, server::end_mission_talk (events, else the story
// campaign), then the GetPlayMission answer (a plain apply, like CApiNotify::OnEndMissionTalkRes),
// here as a queued GetPlayMission request (FakeApiCaller has no EndMissionTalk entry to answer). Before the rebase's revision 2 restore_campaign.cpp did the same
// from a CEventScenario::Exit hook (the offline build had dropped the request). Otherwise the guest behaviour.
constexpr char kEndMissionTalk[] = "_ZN10IApiCaller14EndMissionTalkEjjhj";
void h_end_mission_talk(Cpu& c) {
    at<u64>(c.x(8), 0) = 0;  // the base stub's Status (nothing in flight)
    if (!on_fake_caller(c.x(0))) return;
    u64 x[8];
    for (int k = 0; k < 8; k++) x[k] = c.x(k);
    // The request line (port/scripts/episode_movie_session.sh reads it) and the pending request.
    server::submit(server_port::inproc_request("_ZN13FakeApiCaller14EndMissionTalkEjjhj", 0x1d00a78c, x));
    u32 mission = (u32)c.x(2);
    if (mission) server::end_mission_talk(mission);
    // --log-packets: soa-server answers EndMissionTalk itself with this GetPlayMission body
    server_port::packet_log::answer_as(0x7c1b7a1b /* GetPlayMission */, 0x1d00a78c /* EndMissionTalk */);
    queue_request("GetPlayMission");
}

// IsSuccess / IsFailure / ErrorCode: the guest's constants 1 / 0 / 0, unless the local server
// (--server inproc) refused the fid's last request (server::error_code, port plumbing; 0 when
// it didn't).
constexpr char kIsSuccess[] = "_ZNK13FakeApiCaller9IsSuccessEN4Aska5Yayoi7GameRPC12GameProtocol10FunctionIDE";
constexpr char kIsFailure[] = "_ZNK13FakeApiCaller9IsFailureEN4Aska5Yayoi7GameRPC12GameProtocol10FunctionIDE";
constexpr char kErrorCode[] = "_ZNK13FakeApiCaller9ErrorCodeEN4Aska5Yayoi7GameRPC12GameProtocol10FunctionIDE";
bool is_error_query(const char* sym) { return !strcmp(sym, kIsSuccess) || !strcmp(sym, kIsFailure) || !strcmp(sym, kErrorCode); }
// LoggedIn: the guest's constant 1, or in-process (--server inproc) the local server's session
// (server::logged_in: false until a Login was answered). The restored 3.7.0 login
// (native/restore/restore370.cpp) sends Login only when LoggedIn is false.
constexpr char kLoggedIn[] = "_ZNK13FakeApiCaller8LoggedInEv";
void h_logged_in(Cpu& c) { c.set_x(0, server::logged_in() ? 1 : 0); }
void h_is_success(Cpu& c) { c.set_x(0, server::error_code((u32)c.x(1)) == 0 ? 1 : 0); }
void h_is_failure(Cpu& c) { c.set_x(0, server::error_code((u32)c.x(1)) != 0 ? 1 : 0); }
void h_error_code(Cpu& c) { c.set_x(0, server::error_code((u32)c.x(1))); }

// Everything in this file is the in-process server route (group kGroupRoute: soa --natives
// route installs it on an otherwise unmodified guest).
bool reg(NativeFunction f) {
    f.group = kGroupRoute;
    return register_native_function(f);
}

bool register_all() {
    reg({kLoggedIn, h_logged_in, "FakeApiCaller const (in-process: the local server's session)"});
    for (int i = 0; i < kNumRequests; i++) {
        reg({kRequests[i].sym, kRequestHooks[i], "FakeApiCaller request"});
        // (Login and SimpleLogin share a lambda body shape but not the address.)
        char* at_sym = (char*)malloc(24);
        snprintf(at_sym, 24, "@0x%" PRIx64, (u64)kRequests[i].lambda_op);
        reg({at_sym, h_lambda, "FakeApiCaller lambda"});
    }
#define FAKEAPI_ST(sym, v) \
    if (strcmp(sym, kGetGachaInData) != 0 && strcmp(sym, kGetWorldMapInfoList) != 0 && !is_served_status_only(sym) && \
        strcmp(sym, kDeepSpaceActiveList) != 0 && !is_sphere_method(sym) && !is_event_api(sym)) \
        reg({sym, &h_status<v>, "FakeApiCaller status"});
    FAKEAPI_STATUS_ONLY(FAKEAPI_ST)
#undef FAKEAPI_ST
    reg({kGetGachaInData, h_get_gacha_in_data, "FakeApiCaller status (served with --fake-server)"});
    for (size_t i = 0; i < kServedHooks.size(); i++)
        reg({kServedStatusOnly[i].sym, kServedHooks[i], "FakeApiCaller status (served by the local server in-process)"});
    reg({kUpdatePartySet, h_update_party_set, "IApiCaller::UpdatePartySet (served by the local server in-process)"});
    reg({kSetAssist, h_set_assist, "IApiCaller::SetAssist (served by the local server in-process)"});
    reg({kUpdateView, h_update_view, "IApiCaller::UpdateView (served by the local server in-process)"});
    reg({kGetMissionList, h_get_mission_list, "IApiCaller::GetMissionList (served by the local server in-process)"});
    reg({kEndMissionTalk, h_end_mission_talk, "IApiCaller::EndMissionTalk (served by the local server in-process)"});
    reg({kGetWorldMapInfoList, h_get_world_map_info_list, "FakeApiCaller status (served in-process)"});
    reg({kDeepSpaceActiveList, h_deep_space_active_list, "FakeApiCaller status (served by the local server in-process)"});
    for (int i = 0; i < kNumSphere; i++)
        reg({kSphere[i].sym, kSphereHooks[i], "Sphere 211 request (served by the local server in-process)"});
    for (int i = 0; i < kNumEventApi; i++)
        reg({kEventApi[i].sym, kEventApiHooks[i], "event ranking / world boss request (served by the local server in-process)"});
    // Methods returning a constant in x0 (the lone-RET ones stay guest code).
#define FAKEAPI_CONST_REG(sym, v) \
    if (v >= 0 && !is_error_query(sym) && strcmp(sym, kLoggedIn) != 0) reg({sym, &h_const<(u64)(v < 0 ? 0 : v)>, "FakeApiCaller const"});
    FAKEAPI_CONST(FAKEAPI_CONST_REG)
#undef FAKEAPI_CONST_REG
    reg({kIsSuccess, h_is_success, "FakeApiCaller const (local-server errors in-process)"});
    reg({kIsFailure, h_is_failure, "FakeApiCaller const (local-server errors in-process)"});
    reg({kErrorCode, h_error_code, "FakeApiCaller const (local-server errors in-process)"});
    return true;
}
const bool registered = register_all();

}  // namespace

NATIVE_ROUTE_FUNCTION("_ZN13FakeApiCaller12AddLocalFileEN4Aska5Yayoi7GameRPC12GameProtocol10FunctionIDEPKcNSt6__ndk18functionIFNS0_6StatusEPaRjEEE",
                [](Cpu& c) { AddLocalFile(c.x(0), (u32)c.x(1), (const char*)c.x(2), c.x(3)); }, "FakeApiCaller");
NATIVE_ROUTE_FUNCTION("_ZN13FakeApiCaller8ProgressEv", [](Cpu& c) { Progress(c.x(0)); }, "FakeApiCaller");
NATIVE_ROUTE_FUNCTION("_ZThn8_N13FakeApiCaller8ProgressEv", [](Cpu& c) { Progress(c.x(0) - 8); }, "FakeApiCaller");
NATIVE_ROUTE_FUNCTION("_ZNK13FakeApiCaller12IsRequestingEN4Aska5Yayoi7GameRPC12GameProtocol10FunctionIDE",
                [](Cpu& c) {
                    // Port option --fake-server (not guest behaviour): a request the fake never
                    // queues (the status-only methods, e.g. GetGachaInData) is finished rather
                    // than in flight forever, so the screens waiting on it move on.
                    if (!g_serve_dir.empty() && !find(c.x(0), (u32)c.x(1))) return c.set_x(0, 0);
                    c.set_x(0, IsRequesting(c.x(0), (u32)c.x(1)));
                }, "FakeApiCaller");
NATIVE_ROUTE_FUNCTION("_ZN13FakeApiCaller7ReleaseEv", [](Cpu& c) { Release(c.x(0)); }, "FakeApiCaller");
NATIVE_ROUTE_FUNCTION("_ZN13FakeApiCaller10InitializeEv", [](Cpu& c) { at<u64>(c.x(8), 0) = 1; }, "FakeApiCaller");
NATIVE_ROUTE_FUNCTION("_ZN13FakeApiCallerC2Ev", [](Cpu& c) { Construct(c.x(0)); }, "FakeApiCaller");
NATIVE_ROUTE_FUNCTION("_ZN13FakeApiCallerD1Ev", [](Cpu& c) { Destruct(c.x(0), false); }, "FakeApiCaller");
NATIVE_ROUTE_FUNCTION("_ZN13FakeApiCallerD0Ev", [](Cpu& c) { Destruct(c.x(0), true); }, "FakeApiCaller");
NATIVE_ROUTE_FUNCTION("_ZThn8_N13FakeApiCallerD1Ev", [](Cpu& c) { Destruct(c.x(0) - 8, false); }, "FakeApiCaller");
NATIVE_ROUTE_FUNCTION("_ZThn8_N13FakeApiCallerD0Ev", [](Cpu& c) { Destruct(c.x(0) - 8, true); }, "FakeApiCaller");

}  // namespace soa::native::fakeapi

// ---- differential tests -------------------------------------------------------------------
// The game never constructs a FakeApiCaller, so the tests build bare objects (vtable-less: the
// methods under test only use the map at +0x40 and the address of +0x60) and compare the guest
// and native code on them. CApiNotify handlers, the resource manager, Aska::Random and
// CParameterManager::Deserialize are stubbed and their calls compared.
#include "native/common/guest_stub.h"
#include "native/common/test.h"

namespace soa::native::fakeapi {
namespace {

struct Obj {
    alignas(16) u8 raw[0x100] = {};
    u64 p() { return (u64)raw; }
    Obj() { at<u64>(p(), kMap) = p() + kMapEnd; }
};

// The map as text: per node key, Info fid/state, name, and the stored functor (vtable, captured
// owner relative to the object, inline or not).
std::string dump(u64 self) {
    std::string s;
    char b[256];
    snprintf(b, sizeof b, "size=%" PRIu64 " begin=%s;", (u64)at<u64>(self, kMapSize),
             at<u64>(self, kMap) == self + kMapEnd ? "end" : "node");
    s += b;
    for (u64 n = at<u64>(self, kMap); n != self + kMapEnd; n = tree_next(n)) {
        u64 f = at<u64>(n, kFnF);
        snprintf(b, sizeof b, " [%08x %08x st%u %s vt=%" PRIx64 " own=%" PRId64 " inl=%d]", at<u32>(n, kKey), at<u32>(n, kInfo),
                 at<u32>(n, kState), ((guest::String*)(n + kName))->str().c_str(),
                 f ? (u64)(at<u64>(f, 0) - lib_base()) : (u64)0, f ? (s64)(at<u64>(f, 8) - self) : (s64)0,
                 f == n + kFn);
        s += b;
    }
    return s;
}

u64 guest_request(TestContext& t, u64 self, const Request& r) {
    u64 st = 0xdead;
    GuestArgs a;
    a.p((void*)self).sret(&st);
    guest_call(t.sym(r.sym), a);
    return st;
}

}  // namespace

NATIVE_TEST("fakeapi/requests") {
    Obj A, B;
    std::vector<u32> fids;
    for (const Request& r : kRequests) fids.push_back(r.fid);
    const u64 is_req = t.sym("_ZNK13FakeApiCaller12IsRequestingEN4Aska5Yayoi7GameRPC12GameProtocol10FunctionIDE");
    int bad = 0;
    for (int step = 0; step < 400 && bad < 5; step++) {
        int kind = t.rand_int(0, 9);
        if (kind < 6) {
            const Request& r = kRequests[t.rand_int(0, kNumRequests - 1)];
            u64 sg = guest_request(t, A.p(), r), sn = 0xdead;
            Request_((u64)&sn, B.p(), r);
            if (sg != sn) { t.fail("%s status %" PRIu64 " vs %" PRIu64, r.sym, sg, sn); bad++; }
        } else if (kind < 8) {
            // Move a request along (what Progress would do).
            u32 fid = fids[t.rand_int(0, (int)fids.size() - 1)];
            u64 na = find(A.p(), fid), nb = find(B.p(), fid);
            if (na && nb) at<u32>(na, kState) = at<u32>(nb, kState) = (u32)t.rand_int(0, 2);
        } else {
            u32 fid = kind == 8 ? fids[t.rand_int(0, (int)fids.size() - 1)] : (u32)t.rand_u64();
            bool g = guest_call(is_req, {A.p(), fid}) & 1, n = IsRequesting(B.p(), fid);
            if (g != n) { t.fail("IsRequesting(%08x) %d vs %d", fid, g, n); bad++; }
        }
        std::string da = dump(A.p()), db = dump(B.p());
        if (da != db) {
            t.fail("step %d map differs:\n  guest  %s\n  native %s", step, da.c_str(), db.c_str());
            bad++;
        }
    }
    // Every request on a fresh object, in table order (the shared-FunctionID quirk).
    Obj C, D;
    for (const Request& r : kRequests) {
        guest_request(t, C.p(), r);
        u64 sn;
        Request_((u64)&sn, D.p(), r);
    }
    t.expect_eq(dump(C.p()), dump(D.p()), "all requests");
    guest_call(t.sym("_ZN13FakeApiCaller7ReleaseEv"), {A.p()});
    Release(B.p());
    guest_call(t.sym("_ZN13FakeApiCaller7ReleaseEv"), {C.p()});
    Release(D.p());
    t.expect_eq(dump(A.p()), dump(B.p()), "Release");
    t.expect_eq(dump(C.p()), dump(D.p()), "Release (all)");
    t.expect_eq(at<u64>(B.p(), kMapEnd), (u64)0, "Release root");
}

NATIVE_TEST("fakeapi/trivial") {
    Obj A;
    auto st = [&](const char* sym, u64 want) {
        u64 v = 0xdead;
        GuestArgs a;
        a.p((void*)A.p()).i(1).i(2).i(3).sret(&v);
        guest_call(t.sym(sym), a);
        if (v != want) t.fail("%s: guest status %" PRIu64 ", native %" PRIu64, sym, v, want);
    };
    auto cst = [&](const char* sym, s64 want) {
        if (want < 0) return;  // lone RET, left as guest code
        u64 v = guest_call(t.sym(sym), {A.p(), 0x1234});
        if (v != (u64)want) t.fail("%s: guest %" PRIu64 ", native %" PRId64, sym, v, want);
    };
#define FAKEAPI_T_ST(sym, v) st(sym, v);
    FAKEAPI_STATUS_ONLY(FAKEAPI_T_ST)
#undef FAKEAPI_T_ST
#define FAKEAPI_T_C(sym, v) cst(sym, v);
    FAKEAPI_CONST(FAKEAPI_T_C)
#undef FAKEAPI_T_C
    st("_ZN13FakeApiCaller10InitializeEv", 1);
}

namespace {

// Renders an ASON value (for the stubbed CParameterManager::Deserialize).
std::string ason_text(u64 v, int depth = 0) {
    if (!v) return "null";
    u32 type = at<u32>(v, 0);
    char b[64];
    switch (type) {
        case 2: case 3: snprintf(b, sizeof b, "%" PRIu64, (u64)at<u64>(v, 8)); return b;
        case 5: return "\"" + std::string((const char*)at<u64>(v, 8), at<u32>(v, 0x18)) + "\"";
        case 7: {
            std::string s = "{";
            u32 n = at<u32>(v, 0x10);
            for (u32 i = 0; i < n && depth < 4; i++)
                s += ason_text(at<u64>(v, 8) + i * 0x40, depth + 1) + ":" + ason_text(at<u64>(v, 8) + i * 0x40 + 0x20, depth + 1) + ",";
            return s + "}";
        }
        default: snprintf(b, sizeof b, "<type %u>", type); return b;
    }
}

}  // namespace

NATIVE_TEST("fakeapi/lambdas") {
    // Stub every handler plus the login's callees.
    std::set<std::string> names;
    for (const Request& r : kRequests) {
        const char* h = r.handler ? r.handler : "_ZN10CApiNotify14OnGetPlayerResEPaRj";
        if (names.insert(h).second && !stub(h, h, 3)) t.fail("can't stub %s", h);
    }
    const char* kRandom = "_ZN4Aska6RandomEv";
    const char* kDeser = "_ZN17CParameterManager11DeserializeEPKN4Aska4ASON6AValue4AMapE";
    if (!stub(kRandom, kRandom, 0) || !stub(kDeser, kDeser, 1)) t.fail("can't stub the login callees");
    names.insert(kRandom);
    names.insert(kDeser);
    names.insert("Random");  // event_runtime_test stubs Aska::Random first under this name

    Obj owner;
    u8 payload[16] = {1, 2, 3};
    for (const Request& r : kRequests) {
        std::vector<std::string> logs[2];
        u64 status[2], x0[2];
        for (int side = 0; side < 2; side++) {
            StubSession s;
            s.only = names;
            u32 rnd = 0x1000;
            u64 data = (u64)payload;
            u32 size = 0x55;
            s.fmt_ptr = [&](u64 v) -> std::string {
                if (v == owner.p() + kNotify) return "notify";
                if (v == (u64)payload) return "data";
                if (v == (u64)&size) return "&size";
                return std::to_string(v);
            };
            for (const std::string& h : names) {
                if (h == kRandom || h == kDeser) continue;
                s.behave[h] = [&, h](Cpu& c) {
                    at<u64>(c.x(8), 0) = 0x5000 + h.size();
                    c.set_x(0, 0x77);
                };
            }
            s.behave[kRandom] = s.behave["Random"] = [&](Cpu& c) { c.set_x(0, rnd += 0x111); };
            s.arity["Random"] = {0, 0};
            s.behave[kDeser] = [&](Cpu& c) {
                s.log.push_back("Deserialize " + std::string(c.x(0) == at<u64>(guest::sym("_ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE"), 0) ? "pm" : "?") +
                                " " + ason_text(c.x(1) - 8));
            };
            alignas(16) u64 functor[6] = {lib_base() + r.lambda_vt, owner.p(), 0, 0, 0, (u64)0};
            status[side] = 0xdead;
            if (side == 0) {
                u64 args[3] = {(u64)functor, (u64)&data, (u64)&size};
                x0[side] = guest_call_raw(lib_base() + r.lambda_op, args, 3, nullptr, 0, (u64)&status[side]).x0;
            } else if (r.handler) {
                Lambda((u64)&status[side], (u64)functor, (u64)&data, (u64)&size, guest::sym(r.handler), &x0[side]);
            } else {
                LoginLambda((u64)&status[side], (u64)functor, (u64)&data, (u64)&size, &x0[side]);
            }
            logs[side] = s.log;
        }
        if (logs[0] != logs[1] || status[0] != status[1] || x0[0] != x0[1]) {
            std::string a, b;
            for (auto& l : logs[0]) a += "\n    " + l;
            for (auto& l : logs[1]) b += "\n    " + l;
            t.fail("%s lambda: status %" PRIx64 "/%" PRIx64 " x0 %" PRIx64 "/%" PRIx64 "\n  guest:%s\n  native:%s", r.sym, status[0], status[1], x0[0], x0[1],
                   a.c_str(), b.c_str());
        }
        if (logs[1].empty()) t.fail("%s lambda: no handler call recorded", r.sym);
    }
}

namespace {

// Pointer names shared by the Progress / lifetime tests' logs.
struct Names {
    std::map<u64, std::string> m;
    void obj(u64 self) {
        m[self] = "self";
        m[self + 8] = "self+8";
        m[self + kNotify] = "notify";
    }
    void names_of(u64 self) {
        for (u64 n = at<u64>(self, kMap); n != self + kMapEnd; n = tree_next(n))
            m[(u64)((guest::String*)(n + kName))->data()] = ((guest::String*)(n + kName))->str();
    }
    std::string operator()(u64 v) const {
        auto it = m.find(v);
        if (it != m.end()) return it->second;
        return v > 0x100000000ull ? "ptr" : std::to_string(v);
    }
};

}  // namespace

NATIVE_TEST("fakeapi/progress") {
    const char* kIsLoading = "_ZNK20CGameResourceManager9IsLoadingEv";
    const char* kSize = "_ZNK9Framework11CFileLoader4SizeEv";
    const char* kEl = "_ZNK20CGameResourceManager27crResourceElementDirectFileEPKc";
    const char* stubs[][2] = {
        {kIsLoading, "1"}, {"_ZN20CGameResourceManager4LockEv", "1"}, {"_ZN20CGameResourceManager6UnlockEv", "1"},
        {"_ZN20CGameResourceManager13AddDirectFileEjPKcjbNS_13iPriorityModeE", "6"}, {kEl, "2"}, {kSize, "1"},
        {"_ZN20CGameResourceManager16RemoveDirectFileEPKc", "2"},
    };
    std::set<std::string> only;
    for (auto& st : stubs) {
        if (!stub(st[0], st[0], atoi(st[1]))) t.fail("can't stub %s", st[0]);
        only.insert(st[0]);
    }
    for (const Request& r : kRequests) {
        const char* h = r.handler ? r.handler : "_ZN10CApiNotify14OnGetPlayerResEPaRj";
        if (only.insert(h).second && !stub(h, h, 3)) t.fail("can't stub %s", h);
    }
    const char* kRandom = "_ZN4Aska6RandomEv";
    const char* kDeser = "_ZN17CParameterManager11DeserializeEPKN4Aska4ASON6AValue4AMapE";
    if (!stub(kRandom, kRandom, 0) || !stub(kDeser, kDeser, 1)) t.fail("can't stub the login callees");
    only.insert(kRandom);
    only.insert(kDeser);
    // Names event_runtime_test gives the same functions when it stubs them first.
    only.insert("Random");
    only.insert("Resource::IsLoading");
    static const u64 el_data = fake_function("fakeapi.el.data", 1);
    only.insert("fakeapi.el.data");

    alignas(16) u64 el_vt[16] = {};
    el_vt[10] = el_data;
    alignas(16) u64 el[4] = {(u64)el_vt};
    u8 payload[32] = {9, 8, 7};

    for (int round = 0; round < 6; round++) {
        Obj A, B;
        int nreq = t.rand_int(1, 25);
        for (int i = 0; i < nreq; i++) {
            const Request& r = kRequests[t.rand_int(0, kNumRequests - 1)];
            guest_request(t, A.p(), r);
            u64 st;
            Request_((u64)&st, B.p(), r);
        }
        std::vector<int> loading;
        for (int i = 0; i < 200; i++) loading.push_back(t.rand_int(0, 3) == 0);
        std::vector<std::string> logs[2];
        for (int side = 0; side < 2; side++) {
            u64 self = side ? B.p() : A.p();
            Names nm;
            nm.obj(self);
            nm.names_of(self);
            nm.m[at<u64>(guest::sym("_ZN9Framework10TSingletonI20CGameResourceManagerE11m_pInstanceE"), 0)] = "rm";
            nm.m[(u64)el] = "el";
            nm.m[(u64)payload] = "data";
            size_t li = 0;
            u32 rnd = 0x2000;
            for (int pass = 0; pass < 4; pass++) {
                StubSession s;
                s.only = only;
                s.fmt_ptr = [&](u64 v) { return nm(v); };
                s.behave[kIsLoading] = s.behave["Resource::IsLoading"] = [&](Cpu& c) { c.set_x(0, loading[li++ % loading.size()]); };
                s.arity["Resource::IsLoading"] = {1, 0};
                s.arity["Random"] = {0, 0};
                s.behave[kEl] = [&](Cpu& c) { c.set_x(0, (u64)el); };
                s.behave[kSize] = [&](Cpu& c) { c.set_x(0, 0x1234); };
                s.behave["fakeapi.el.data"] = [&](Cpu& c) { c.set_x(0, (u64)payload); };
                s.behave[kRandom] = s.behave["Random"] = [&](Cpu& c) { c.set_x(0, rnd += 0x111); };
                s.behave[kDeser] = [&](Cpu& c) {};
                if (side == 0) {
                    // The non-virtual thunk (this - 8) on odd passes.
                    if (pass & 1) guest_call(t.sym("_ZThn8_N13FakeApiCaller8ProgressEv"), {self + 8});
                    else guest_call(t.sym("_ZN13FakeApiCaller8ProgressEv"), {self});
                } else {
                    Progress(self);
                }
                for (auto& l : s.log) logs[side].push_back(l);
                logs[side].push_back("-- " + dump(self));
            }
        }
        if (logs[0] != logs[1]) {
            std::string a, b;
            for (auto& l : logs[0]) a += "\n    " + l;
            for (auto& l : logs[1]) b += "\n    " + l;
            t.fail("round %d:\n  guest:%s\n  native:%s", round, a.c_str(), b.c_str());
            break;
        }
    }
}

NATIVE_TEST("fakeapi/lifetime") {
    const char* kFiberCtor = "_ZN9Framework10CFiberUnitC2Ej";
    const char* kFiberDtor = "_ZN9Framework10CFiberUnitD1Ev";
    const char* kNotifyCtor = "_ZN10CApiNotifyC1EP10IApiCaller";
    const char* kNotifyDtor = "_ZN10CApiNotifyD1Ev";
    const char* kKernel = "_ZN9Framework12CApplication9CMainTask16rRootFiberKernelEv";
    const char* kSetFake = "_ZN17CErrorHandlerWrap16SetFakeAppCallerEv";
    const char* kDelete = "_ZdlPv";
    std::set<std::string> only;
    for (const char* sym : {kFiberCtor, kFiberDtor, kNotifyCtor, kNotifyDtor, kKernel, kSetFake, kDelete}) {
        if (!stub(sym, sym, 2)) t.fail("can't stub %s", sym);
        only.insert(sym);
    }
    only.insert("op_delete");  // event_runtime_test's name for operator delete, if it stubbed it first
    static const u64 kernel_add = fake_function("fakeapi.kernel.add", 2);
    only.insert("fakeapi.kernel.add");
    alignas(16) u64 kernel_vt[16] = {};
    kernel_vt[9] = kernel_add;
    alignas(16) u64 kernel[2] = {(u64)kernel_vt};

    // {guest destructor symbol, via the thunk, deleting}
    struct Case { const char* dtor; bool thunk, deleting; } cases[] = {
        {"_ZN13FakeApiCallerD1Ev", false, false}, {"_ZN13FakeApiCallerD0Ev", false, true},
        {"_ZThn8_N13FakeApiCallerD1Ev", true, false}, {"_ZThn8_N13FakeApiCallerD0Ev", true, true}};
    for (const Case& cs : cases) {
        Obj objs[2];
        std::vector<std::string> logs[2];
        std::string after[2];
        int nreq = t.rand_int(0, 12);
        std::vector<int> reqs;
        for (int i = 0; i < nreq; i++) reqs.push_back(t.rand_int(0, kNumRequests - 1));
        for (int side = 0; side < 2; side++) {
            u64 self = objs[side].p();
            memset(objs[side].raw, 0xcc, sizeof objs[side].raw);
            Names nm;
            nm.obj(self);
            nm.m[(u64)kernel] = "kernel";
            StubSession s;
            s.only = only;
            s.fmt_ptr = [&](u64 v) { return nm(v); };
            s.behave[kKernel] = [&](Cpu& c) { c.set_x(0, (u64)kernel); };
            for (const char* one : {kFiberDtor, kNotifyDtor, kKernel, kSetFake, kDelete, "op_delete"}) s.arity[one] = {1, 0};
            // The objects live on the host stack: operator delete must never run for real.
            s.behave[kDelete] = s.behave["op_delete"] = [](Cpu& c) {};
            if (side == 0) guest_call(t.sym("_ZN13FakeApiCallerC2Ev"), {self});
            else Construct(self);
            char b[160];
            snprintf(b, sizeof b, "ctor: vt=%" PRIx64 " fiber_vt=%" PRIx64 " begin=%" PRId64 " root=%" PRIx64 " size=%" PRIx64, (u64)(at<u64>(self, 0) - lib_base()),
                     (u64)(at<u64>(self, 8) - lib_base()), (s64)(at<u64>(self, kMap) - self),
                     (u64)at<u64>(self, kMapEnd), (u64)at<u64>(self, kMapSize));
            s.log.push_back(b);
            for (int i : reqs) {
                u64 st;
                if (side == 0) guest_request(t, self, kRequests[i]);
                else Request_((u64)&st, self, kRequests[i]);
            }
            s.log.push_back(dump(self));
            u64 arg = cs.thunk ? self + 8 : self;
            if (side == 0) guest_call(t.sym(cs.dtor), {arg});
            else Destruct(self, cs.deleting);
            snprintf(b, sizeof b, "dtor: vt=%" PRIx64 " fiber_vt=%" PRIx64 " begin=%" PRId64 " root=%" PRIx64 " size=%" PRIx64, (u64)(at<u64>(self, 0) - lib_base()),
                     (u64)(at<u64>(self, 8) - lib_base()), (s64)(at<u64>(self, kMap) - self),
                     (u64)at<u64>(self, kMapEnd), (u64)at<u64>(self, kMapSize));
            s.log.push_back(b);
            logs[side] = s.log;
        }
        if (logs[0] != logs[1]) {
            std::string a, b;
            for (auto& l : logs[0]) a += "\n    " + l;
            for (auto& l : logs[1]) b += "\n    " + l;
            t.fail("%s:\n  guest:%s\n  native:%s", cs.dtor, a.c_str(), b.c_str());
        }
    }
}

}  // namespace soa::native::fakeapi
