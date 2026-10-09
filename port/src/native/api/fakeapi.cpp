// FakeApiCaller: the game's built-in offline "server" (an IApiCaller that answers requests
// in-process from FakeApi/*.msgp files the game never shipped), as readable native C++.
//
// The shipped game never constructs a FakeApiCaller (CGame::OnInitialize always makes a
// NetworkApiCaller) and its files aren't shipped, so none of this runs in normal play. The port
// keeps it bit-compatible and brings it up as the in-process server's route (--server inproc, the
// default): the local server answers each request instead of a file. The protocol is in
// docs/notes.md, "Offline server (FakeApiCaller)".
//
// The types (FakeApiCaller, its map of Info, CApiNotify) are in api_layout.h. Every request method
// stores a lambda {vtable, this} (RequestLambda) through AddLocalFile(fid, "FakeApi/x.msgp");
// Progress loads the file through CGameResourceManager and calls the lambda, which hands the bytes
// to CApiNotify::On<Api>Res(&m_notify, data, size). The two login lambdas first deserialize a fake
// {"Player": {"Id", "Name"}} into CParameterManager.
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

#include "soaruntime/core/cpu.h"
#include "soaruntime/core/loader.h"
#include "soaruntime/core/log.h"
#include "core/options.h"
#include "native/api/api_layout.h"
#include "native/common/guest_assert.h"
#include "native/common/guest_std.h"
#include "native/common/native.h"
#include "native/api/gen/api_addresses.h"
#include "native/common/gen/common_addresses.h"
#include "native/data_formats/data_formats_layout.h"
#include "native/info/info_layout.h"
#include "native/libcxx/libcxx_function.h"
#include "soaserver/api_campaign.h"
#include "soa/chash32.h"
#include "soaserver/events.h"
#include "soaserver/server.h"
#include "native/api/server_adapters.h"
#include "native/api/packet_log.h"

namespace soa::native::fakeapi {

using api::CApiNotify;
using api::FakeApiCaller;
using api::Info;
using api::InfoMap;
using api::InfoNode;
using api::RequestLambda;

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

// The in-process server's route (--server inproc; not guest behaviour): set by serve_enabled when
// CGame::OnInitialize's hook is installed. Progress serves the requests (ServeProgress) instead.
bool g_route_on = false;

namespace {

u64 lib_base() { return main_lib()->base; }
u64 g(const char* mangled) { return guest::sym(mangled); }
u64 addr(const void* p) { return reinterpret_cast<u64>(p); }

// Aska::Status, through x8.
void set_status(u64 x8, u64 status) { reinterpret_cast<data_formats::Status*>(x8)->code = static_cast<s64>(status); }

// Slot `slot` of a guest object's vtable (VIRTUALS.md 1.4).
u64 vslot(u64 obj, int slot) { return (*reinterpret_cast<const u64* const*>(obj))[slot]; }

// Framework::TSingleton<T>::m_pInstance, with the header's assertion when it's null.
u64 singleton(const char* instance_sym) {
    const u64* slot = reinterpret_cast<const u64*>(g(instance_sym));
    if (!*slot) guest_assert(kTSingletonClientH, 0x23, kStrInstanceNull);
    return *slot;
}
const char kResMgr[] = "_ZN9Framework10TSingletonI20CGameResourceManagerE11m_pInstanceE";
u64 parameter_manager() { return *reinterpret_cast<const u64*>(g("_ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE")); }

// A request's std::function as its method builds it: the lambda {vtable, this} stored inline.
libcxx::function request_function(FakeApiCaller* self, u64 lambda_vt) {
    libcxx::function fn{};
    auto* lambda = reinterpret_cast<RequestLambda*>(fn.buf);
    lambda->vtable = reinterpret_cast<const void* const*>(lib_base() + lambda_vt);
    lambda->f = self;
    fn.f = reinterpret_cast<libcxx::function_base*>(fn.buf);
    return fn;
}

}  // namespace

}  // namespace soa::native::fakeapi

namespace soa::native::api {

using fakeapi::g;
using fakeapi::kResMgr;
using fakeapi::singleton;

// FakeApiCaller::AddLocalFile(FunctionID, const char*, std::function<Status(s8*, u32&)>)
// A known FunctionID is only re-queued: its first file name and lambda stay.
void FakeApiCaller::AddLocalFile(u32 fid, const char* name, libcxx::function* fn) {
    if (InfoNode* n = FindInfo(fid)) {
        n->value.second.m_state = Info::kQueued;
        return;
    }
    // __emplace_unique_key_args: find the slot, then a node holding {fid, Info{fid, kQueued, name, fn}}.
    libcxx::tree_node_base* parent = m_infos.end_node();
    InfoNode** child = &m_infos.root;  // the end node's left
    for (InfoNode* n = m_infos.root; n;) {
        parent = reinterpret_cast<libcxx::tree_node_base*>(n);
        if (fid < n->value.first) {
            child = &n->left;
            n = n->left;
        } else {
            child = &n->right;
            n = n->right;
        }
    }
    auto* node = static_cast<InfoNode*>(guest::stl_alloc(sizeof(InfoNode)));
    node->value.first = fid;
    Info& info = node->value.second;
    info.m_fid = fid;
    info.m_state = Info::kQueued;
    info.m_name.init(name);
    libcxx::function_copy_construct(&info.m_fn, *fn);
    node->left = nullptr;
    node->right = nullptr;
    node->parent = parent;
    *child = node;
    if (m_infos.begin_node->left) m_infos.begin_node = m_infos.begin_node->left;
    // std::__ndk1::__tree_balance_after_insert<__tree_node_base<void*>*>(root, x): the guest's own
    static const u64 balance = g("_ZNSt6__ndk127__tree_balance_after_insertIPNS_16__tree_node_baseIPvEEEEvT_S5_");
    guest_call(balance, {fakeapi::addr(m_infos.root), fakeapi::addr(*child)});
    m_infos.size++;
}

// FakeApiCaller::Progress(): queue each new request's file, and hand each loaded one to its lambda.
// On the in-process route (not guest behaviour): ServeProgress.
void FakeApiCaller::Progress() {
    if (fakeapi::g_route_on) return ServeProgress();
    for (InfoNode* n = m_infos.begin(); n != m_infos.end(); n = InfoMap::next(n)) {
        Info& info = n->value.second;
        if (info.m_state == Info::kQueued) {
            u64 rm = singleton(kResMgr);
            guest_call(g("_ZN20CGameResourceManager13AddDirectFileEjPKcjbNS_13iPriorityModeE"), {rm, 1, fakeapi::addr(info.m_name.data()), 0, 0, 0});
            info.m_state = Info::kLoading;
        } else if (info.m_state == Info::kLoading) {
            u64 rm = singleton(kResMgr);
            if (guest_call(g("_ZNK20CGameResourceManager9IsLoadingEv"), {rm}) & 1) continue;
            guest_call(g("_ZN20CGameResourceManager4LockEv"), {rm});
            u64 el = guest_call(g("_ZNK20CGameResourceManager27crResourceElementDirectFileEPKc"), {rm, fakeapi::addr(info.m_name.data())});
            u32 size = (u32)guest_call(g("_ZNK9Framework11CFileLoader4SizeEv"), {el});
            u64 data = guest_call(fakeapi::vslot(el, resource::CResourceElement::kSlotPImage), {el});
            data_formats::Status status{};  // discarded
            guest_call(libcxx::function_slot(info.m_fn, libcxx::kFuncSlotCall),
                       GuestArgs().p(info.m_fn.f).p(&data).p(&size).sret(&status));
            guest_call(g("_ZN20CGameResourceManager6UnlockEv"), {rm});
            guest_call(g("_ZN20CGameResourceManager16RemoveDirectFileEPKc"), {rm, fakeapi::addr(info.m_name.data())});
            info.m_state = Info::kDone;
        }
    }
}

// FakeApiCaller::IsRequesting(FunctionID): an unknown request counts as in flight.
bool FakeApiCaller::IsRequesting(u32 fid) const {
    const InfoNode* n = const_cast<FakeApiCaller*>(this)->FindInfo(fid);
    return !n || n->value.second.m_state != Info::kDone;
}

// The map's __tree::destroy(node): post-order; each Info's function, then its name.
void destroy_infos(InfoNode* n) {
    if (!n) return;
    destroy_infos(n->left);
    destroy_infos(n->right);
    libcxx::function_destroy(&n->value.second.m_fn);
    n->value.second.m_name.destroy();
    guest::stl_free(n);
}

// FakeApiCaller::Release(): empties the map.
void FakeApiCaller::Release() {
    destroy_infos(m_infos.root);
    m_infos.begin_node = m_infos.end();
    m_infos.root = nullptr;
    m_infos.size = 0;
}

// Constructor: fiber unit (priority 0x600) attached to the root fiber kernel, empty map,
// CApiNotify(this), then CErrorHandlerWrap::SetFakeAppCaller().
void FakeApiCaller::CtorBase() {
    const u64 vt = g("_ZTV13FakeApiCaller");
    vtable = reinterpret_cast<const void*>(g("_ZTV10IApiCaller") + 0x10);
    guest_call(g("_ZN9Framework10CFiberUnitC2Ej"), {fakeapi::addr(&m_fiber), 0x600});
    m_infos.size = 0;
    m_fiber.vtable = reinterpret_cast<const void*>(vt + 0x700);
    vtable = reinterpret_cast<const void*>(vt + 0x10);
    m_infos.root = nullptr;
    m_infos.begin_node = m_infos.end();
    guest_call(g("_ZN10CApiNotifyC1EP10IApiCaller"), {fakeapi::addr(&m_notify), fakeapi::addr(this)});
    u64 task = singleton("_ZN9Framework10TSingletonINS_12CApplication9CMainTaskEE11m_pInstanceE");
    u64 kernel = guest_call(g("_ZN9Framework12CApplication9CMainTask16rRootFiberKernelEv"), {task});
    guest_call(fakeapi::vslot(kernel, kernel::CFiberUnit::kSlotCreateSubFiber), {kernel, fakeapi::addr(&m_fiber)});
    u64 ehw = singleton("_ZN9Framework10TSingletonI17CErrorHandlerWrapE11m_pInstanceE");
    guest_call(g("_ZN17CErrorHandlerWrap16SetFakeAppCallerEv"), {ehw});
}

// The destructor body (~FakeApiCaller D1): the map emptied, ~CApiNotify, the map member's own
// destructor (now empty), ~CFiberUnit. D0 (DtorDelete) also frees the object.
void FakeApiCaller::Dtor() {
    const u64 vt = g("_ZTV13FakeApiCaller");
    m_fiber.vtable = reinterpret_cast<const void*>(vt + 0x700);
    vtable = reinterpret_cast<const void*>(vt + 0x10);
    destroy_infos(m_infos.root);
    m_infos.begin_node = m_infos.end();
    m_infos.size = 0;
    m_infos.root = nullptr;
    guest_call(g("_ZN10CApiNotifyD1Ev"), {fakeapi::addr(&m_notify)});
    destroy_infos(m_infos.root);
    guest_call(g("_ZN9Framework10CFiberUnitD1Ev"), {fakeapi::addr(&m_fiber)});
}
void FakeApiCaller::DtorDelete() {
    Dtor();
    guest_call(g("_ZdlPv"), {fakeapi::addr(this)});
}

}  // namespace soa::native::api

namespace soa::native::fakeapi {

// Port option (serve mode only): requests the guest fake never queues but the port serves
// (fid -> CApiNotify handler called directly, instead of a guest lambda). See queue_served.
std::map<u32, const char*> g_served_extra;

// The request methods: queue the request's file name with this API's lambda; Status 1.
void Request_(u64 status, FakeApiCaller* self, const Request& r) {
    libcxx::function fn = request_function(self, r.lambda_vt);
    self->AddLocalFile(r.fid, reinterpret_cast<const char*>(lib_base() + r.file), &fn);
    libcxx::function_destroy(&fn);
    set_status(status, 1);
}

// The lambdas' operator()(s8*& data, u32& size) -> Status (x8).
// Common case: return CApiNotify::On<Api>Res(&owner->m_notify, data, size).
void Lambda(u64 status, const RequestLambda* functor, u64 data_ref, u64 size_ref, u64 handler, u64* x0) {
    FakeApiCaller* owner = functor->f;
    *x0 = guest_call(handler, GuestArgs().p(&owner->m_notify).i(*reinterpret_cast<const u64*>(data_ref)).i(size_ref).sret((void*)status)).x0;
}

// Login / SimpleLogin: deserialize a fake player {"Player": {"Id": random, "Name": "Dummy_%x"}}
// into CParameterManager, then OnGetPlayerRes. (The guest also calls gethostname into a
// buffer it never reads; that call is left out.)
void LoginLambda(u64 status, const RequestLambda* functor, u64 data_ref, u64 size_ref, u64* x0) {
    using data_formats::AValue;
    using data_formats::ASON;
    using data_formats::ASON_Pair;
    FakeApiCaller* owner = functor->f;
    const u64 random = g("_ZN4Aska6RandomEv");
    char name[0x40];
    u32 r1 = (u32)guest_call(random, {});
    snprintf(name, sizeof name, "Dummy_%x", r1);
    u32 id = (u32)guest_call(random, {});

    alignas(16) ASON ason;
    data_formats::Status tmp{};
    auto call8 = [&](u64 fn, std::initializer_list<u64> ints) {
        guest_call_raw(fn, ints.begin(), ints.size(), nullptr, 0, addr(&tmp));
    };
    // The map value's first pair (MakeAValue_Map's n pairs), or null for an empty one.
    auto pairs = [](const AValue* v) { return v->m_body.map.m_count ? v->m_body.map.m_pairs : nullptr; };
    guest_call(g("_ZN4Aska4ASONC1Ev"), {addr(&ason)});
    guest_call(g("_ZN4Aska4ASON4InitEjb"), {addr(&ason), 0x4000, 1});
    const u64 make_map = g("_ZN4Aska4ASON14MakeAValue_MapEPNS0_6AValueEj");
    const u64 set_string = g("_ZN4Aska4ASON6AValue9SetStringEPKcPS0_");
    call8(make_map, {addr(&ason), addr(&ason.m_root), 4});
    ASON_Pair* root = pairs(&ason.m_root);
    call8(set_string, {addr(root ? &root[0].key : nullptr), (u64) "Player", addr(&ason)});
    AValue* player = root ? &pairs(&ason.m_root)[0].value : nullptr;
    call8(make_map, {addr(&ason), addr(player), 2});
    ASON_Pair* fields = player->m_body.map.m_pairs;
    call8(set_string, {addr(pairs(player) ? &fields[0].key : nullptr), (u64) "Id", addr(&ason)});
    fields[0].value.m_kind = AValue::kUInt;
    fields[0].value.m_body.u = id;
    const bool two = player->m_body.map.m_count >= 2;
    call8(set_string, {addr(two ? &fields[1].key : nullptr), (u64) "Name", addr(&ason)});
    call8(set_string, {addr(two ? &fields[1].value : nullptr), (u64)name, addr(&ason)});
    guest_call(g("_ZN17CParameterManager11DeserializeEPKN4Aska4ASON6AValue4AMapE"), {parameter_manager(), addr(&ason.m_root.m_body.map)});
    guest_call(g("_ZN4Aska4ASOND1Ev"), {addr(&ason)});

    *x0 = guest_call(g("_ZN10CApiNotify14OnGetPlayerResEPaRj"),
                     GuestArgs().p(&owner->m_notify).i(*reinterpret_cast<const u64*>(data_ref)).i(size_ref).sret((void*)status)).x0;
}

// ---- the in-process server's route (--server inproc) -----------------------------------
// Our invention, not guest behaviour. The shipped game never constructs FakeApiCaller and
// never shipped its FakeApi/*.msgp files. With --server inproc (the default):
//  - after CGame::OnInitialize, a FakeApiCaller is constructed (its own constructor: fiber,
//    CApiNotify, CErrorHandlerWrap::SetFakeAppCaller) and put in TSingleton<CApiCaller> in
//    place of the NetworkApiCaller, which stays alive but unused;
//  - Progress answers each request with the local server's reply instead of the resource
//    manager's file, one frame after the request, like the guest's two steps. A request no
//    handler answers gets an empty map (0x80) and is logged (`no handler: <Method>`, by the
//    library); the guest would crash on a missing file. (The port's earlier fallback, a
//    folder of generated files, is gone: docs/history/fake-server-responses.md.)
// The handlers are called exactly as the guest lambdas call them.
}  // namespace soa::native::fakeapi

namespace soa::native::api {

void FakeApiCaller::ServeProgress() {
    using fakeapi::g_served_extra;
    namespace server_port = ::soa::server_port;
    for (InfoNode* n = m_infos.begin(); n != m_infos.end(); n = InfoMap::next(n)) {
        Info& info = n->value.second;
        if (info.m_state == Info::kQueued) {
            info.m_state = Info::kLoading;
            continue;
        }
        if (info.m_state != Info::kLoading) continue;
        std::string name = info.m_name.str();
        std::string file = name.rfind("FakeApi/", 0) == 0 ? name.substr(8) : name;
        std::vector<char> body;
        // The in-process server (--server inproc): the local server (top-level server/) answers the
        // request the client made (server_port::take: kept when it was made) through its one
        // request lifecycle, server::answer, as soa-server's wire does; what no handler answers is
        // {} (the library logs `no handler: <Method>`; the guest would crash on a missing file).
        // The story campaign's data is added either way (server::answer).
        u32 fid = n->value.first;
        server::Request req = server_port::take(fid);
        if (req.method.empty() && server::enabled()) LOGW("fakeapi", "fid %08x: %s: no request was kept for it", fid, file.c_str());
        server::Reply reply = server::answer(req, [&] {
            LOGW("fakeapi", "fid %08x: %s: no handler; answering {}", fid, file.c_str());
            return std::vector<u8>{0x80};
        });
        if (reply.handled) {
            if (u32 code = reply.error_code) {
                // Port plumbing (--server inproc): the local server refused the request. Do what
                // CApiNotify::OnProtocolError does on the network path: ErrorHandler::Handle(fid,
                // Status = code), whose CErrorHandlerWrap callback (CallBackCore -> ErrKind ->
                // OpenDialogCatch) shows master_text error_message_text_<code>, while the entry is
                // still in flight (IsRequesting true, so an Auto-registered screen keeps its
                // handler); then m_notify.m_errorCode = code. The body isn't delivered (no On*Res),
                // as on the network path. IsSuccess / IsFailure / ErrorCode report the code.
                u64 eh = *reinterpret_cast<const u64*>(g("_ZN9Framework10TSingletonI12ErrorHandlerE11m_pInstanceE"));
                alignas(16) int64_t status = (int64_t)code;
                LOGI("fakeapi", "fid %08x: %s refused by the local server with error %u", fid, file.c_str(), code);
                if (eh)
                    guest_call(g("_ZN12ErrorHandler6HandleEN4Aska5Yayoi7GameRPC12GameProtocol10FunctionIDENS0_6StatusE"),
                               {eh, fid, fakeapi::addr(&status)});
                m_notify.m_errorCode = static_cast<s32>(code);
                info.m_state = Info::kDone;
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
        data_formats::Status status{};
        info.m_state = Info::kDone;  // before the call: a handler may queue this API again
        auto extra = g_served_extra.find(n->value.first);
        if (extra != g_served_extra.end()) {
            guest_call(g(extra->second), GuestArgs().p(&m_notify).i(data).p(&size).sret(&status));
        } else {
            guest_call(libcxx::function_slot(info.m_fn, libcxx::kFuncSlotCall), GuestArgs().p(info.m_fn.f).p(&data).p(&size).sret(&status));
        }
        guest::delete_array((void*)data);
    }
}

}  // namespace soa::native::api

namespace soa::native::fakeapi {

// --fake-server-schema FILE (with the route): writes the response schema the handlers
// accept, i.e. what CParameterManager::Deserialize walks: each registered parameter set (the list
// CParameterManager::m_parameters, plus its CInfoManager) with its top-level key (pParseName), its
// properties (InfoBase::m_properties: key name recovered by hashing every string in .rodata, and the
// property's class) and child infos (InfoBase::m_children).
void dump_schema_info(FILE* f, const std::map<u32, std::string>& dict, info::InfoBase* info, int depth) {
    auto key_name = [&](u32 h) {
        auto it = dict.find(h);
        char b[16];
        snprintf(b, sizeof b, "#%08x", h);
        return it != dict.end() ? it->second : std::string(b);
    };
    std::string pad(depth * 2, ' ');
    u64 name = guest_call(vslot(addr(info), info::InfoBase::kSlotParseName), {addr(info)});
    fprintf(f, "%s%s  [%s]\n", pad.c_str(), name ? (const char*)name : "?", describe_guest_addr(addr(info->vtable)).c_str());
    // Only InfoBase subclasses have the two maps; the CParameter* sets in the list don't.
    auto valid_map = [](info::PropertyMap& m) {
        if (m.size > 100000) return false;
        if (m.size == 0) return m.begin_node == m.end();
        return m.root && m.root->parent == m.end_node();
    };
    if (depth > 6 || !valid_map(info->m_properties) || !valid_map(info->m_children)) return;
    const u64 pm = parameter_manager();
    info->m_properties.for_each([&](info::PropertyNode* n) {
        auto* prop = static_cast<const u8*>(n->value.second);
        fprintf(f, "%s  .%s : %s  @+%#" PRIx64 " #%08x\n", pad.c_str(), key_name(n->value.first).c_str(),
                prop ? describe_guest_addr(*reinterpret_cast<const u64*>(prop)).c_str() : "null", (u64)(addr(prop) - addr(info)),
                n->value.first);
    });
    info->m_children.for_each([&](info::PropertyNode* n) {
        u64 child = addr(n->value.second);
        if (child > pm && child < pm + 0x10000)
            fprintf(f, "%s  child %s (CParameterManager+%#" PRIx64 "):\n", pad.c_str(), key_name(n->value.first).c_str(), (u64)(child - pm));
        else
            fprintf(f, "%s  child %s:\n", pad.c_str(), key_name(n->value.first).c_str());
        if (child) dump_schema_info(f, dict, reinterpret_cast<info::InfoBase*>(child), depth + 2);
    });
}

void dump_schema(const char* path) {
    FILE* f = fopen(path, "w");
    if (!f) return;
    std::map<u32, std::string> dict;
    u64 ro_addr = 0, ro_size = 0;
    if (!main_lib()->section(".rodata", ro_addr, ro_size)) return;
    const char* ro = (const char*)ro_addr;  // (a guest address)
    for (size_t i = 0; i < ro_size;) {
        size_t j = i;
        while (j < ro_size && ro[j] >= 0x20 && ro[j] < 0x7f) j++;
        if (j < ro_size && ro[j] == 0 && j - i >= 1 && j - i < 64)
            for (size_t k = i; k < j; k++) dict.emplace(chash32(ro + k, j - k), std::string(ro + k, j - k));
        i = j + 1;
    }
    auto* pm = reinterpret_cast<info::CParameterManager*>(parameter_manager());
    fprintf(f, "# FakeApiCaller response schema (port dump; key names by CHash32 of .rodata strings)\n");
    for (auto* n = pm->m_parameters.next; n != pm->m_parameters.sentinel(); n = n->next) {
        info::InfoBase* info = n->value;
        if (addr(info) > addr(pm) && addr(info) < addr(pm) + 0x10000)
            fprintf(f, "# at CParameterManager+%#" PRIx64 ":\n", (u64)(addr(info) - addr(pm)));
        dump_schema_info(f, dict, info, 0);
    }
    fprintf(f, "# CParameterManager+0x600 (map or array under its own key)\n");
    dump_schema_info(f, dict, &pm->m_infoManager.base, 0);
    fprintf(f, "# CParameterManager+0xf70: child infos by name hash\n");
    pm->m_infoManager.m_infosByHash.for_each(
        [&](info::PropertyNode* n) { dump_schema_info(f, dict, static_cast<info::InfoBase*>(n->value.second), 0); });
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
        dump_schema_info(f, dict, reinterpret_cast<info::InfoBase*>(obj), 0);  // leaked: a one-off debug dump
    }
    fclose(f);
    LOGI("fakeapi", "response schema written to %s", path);
}

u64 g_orig_game_init = 0;

// The route's switch: --server inproc (options().server.enabled; the default). With --server HOST
// the client keeps its NetworkApiCaller.
bool serve_enabled() {
    if (!options().server.enabled) return false;
    g_route_on = true;
    return true;
}

// CGame::OnInitialize, then swap the API caller.
void h_game_init(Cpu& c) {
    u64 game = c.x(0);
    guest_call(g_orig_game_init, {game});
    u64* slot = reinterpret_cast<u64*>(g("_ZN9Framework10TSingletonI10CApiCallerE11m_pInstanceE"));
    // FakeApiCaller is 0x60 bytes plus CApiNotify (api_layout.h; its size isn't pinned): 0x2000, the rest slack.
    u64 self = (u64)guest::new_array_nothrow(0x2000);
    memset((void*)self, 0, 0x2000);
    guest_call(g("_ZN13FakeApiCallerC2Ev"), {self});
    u64 old = *slot;
    *slot = self;
    if (!options().client.fake_server_schema.empty()) dump_schema(options().client.fake_server_schema.c_str());
    LOGI("fakeapi", "in-process server: FakeApiCaller at %#" PRIx64 " replaces the API caller %#" PRIx64, (u64)self, (u64)old);
}

NATIVE_ROUTE_FUNCTION_ORIG_IF("_ZN5CGame12OnInitializeEv", h_game_init, "--server inproc: FakeApiCaller as the API caller",
                              serve_enabled, &g_orig_game_init);

namespace {

// ---- hooks --------------------------------------------------------------------------------

FakeApiCaller* caller(Cpu& c) { return reinterpret_cast<FakeApiCaller*>(c.x(0)); }

// Any request's lambda: a valid guest std::function for a queue entry whose answer goes to a
// handler of g_served_extra (the map copies and destroys it; ServeProgress never calls it).
// GetGachaRate's.
const Request& any_request_lambda() {
    static const Request* const r = [] {
        const Request* found = nullptr;
        for (const Request& q : kRequests)
            if (q.fid == 0xd6bcb49d) found = &q;  // GetGachaRate
        return found;
    }();
    return *r;
}

// Port code (the in-process route): queues fid under `file` with any request's lambda, answered by
// CApiNotify's `handler` (g_served_extra; what NetworkApiCaller's response goes to); Status 1.
void queue_served(Cpu& c, u32 fid, const char* handler, const char* file) {
    g_served_extra[fid] = handler;
    libcxx::function fn = request_function(caller(c), any_request_lambda().lambda_vt);
    caller(c)->AddLocalFile(fid, file, &fn);
    libcxx::function_destroy(&fn);
    set_status(c.x(8), 1);
}

// Request methods whose offline FakeApiCaller lambda answers through another method's handler
// (port code, not guest behaviour): the three ClearNew* queue FakeApi/sale.msgp under SellItem's
// FunctionID and call CApiNotify::OnSellItemRes, so the client never clears a NEW badge. On the
// in-process route they are queued like the served base-class methods instead: NetworkApiCaller's
// FunctionID (docs/api.md) and the handler its response goes to (docs/client-changes.md
// "FakeApiCaller::ClearNew*").
bool on_fake_caller(u64 self);
struct RoutedRequest {
    const char* sym;
    u32 fid;  // NetworkApiCaller's FunctionID
    const char* handler;
    const char* file;  // the name the queue entry and the logs show
};
const RoutedRequest kRoutedRequests[] = {
    {"_ZN13FakeApiCaller17ClearNewCharacterERKN9Framework10CSTLVectorImEE", 0x36ce009c, "_ZN10CApiNotify22OnClearNewCharacterResEPaRj",
     "FakeApi/clear_new_character.msgp"},
    {"_ZN13FakeApiCaller12ClearNewItemERKN9Framework10CSTLVectorImEE", 0x22b15407, "_ZN10CApiNotify17OnClearNewItemResEPaRj",
     "FakeApi/clear_new_item.msgp"},
    {"_ZN13FakeApiCaller17ClearNewStackItemERKN9Framework10CSTLVectorIjEE", 0xaabac605, "_ZN10CApiNotify22OnClearNewStackItemResEPaRj",
     "FakeApi/clear_new_stack_item.msgp"},
};
const RoutedRequest* routed_request(const char* sym) {
    for (const RoutedRequest& r : kRoutedRequests)
        if (!strcmp(r.sym, sym)) return &r;
    return nullptr;
}

template <int I>
void h_request(Cpu& c) {
    if (const RoutedRequest* routed = routed_request(kRequests[I].sym); routed && on_fake_caller(c.x(0))) {
        u64 x[8];
        for (int k = 0; k < 8; k++) x[k] = c.x(k);
        server_port::capture(routed->sym, routed->fid, x);
        queue_served(c, routed->fid, routed->handler, routed->file);
        return;
    }
    // The in-process server (--server inproc; not guest behaviour): the request's arguments, kept
    // until Progress answers it (server::answer).
    if (server::enabled()) {
        u64 x[8];
        for (int k = 0; k < 8; k++) x[k] = c.x(k);
        // the request as the wire carries it (MissionEnd & co.: with the client's battle log; the
        // varargs methods' uids past x7 from the stack)
        server_port::remember(server_port::inproc_request(kRequests[I].sym, kRequests[I].fid, x, (const u64*)c.sp()));
    }
    Request_(c.x(8), caller(c), kRequests[I]);
}

template <int... I>
constexpr std::array<HostFn, sizeof...(I)> request_hooks(std::integer_sequence<int, I...>) {
    return {&h_request<I>...};
}
constexpr auto kRequestHooks = request_hooks(std::make_integer_sequence<int, kNumRequests>{});

// One hook for every lambda operator(): the functor's vtable says which API it is.
void h_lambda(Cpu& c) {
    const auto* functor = reinterpret_cast<const RequestLambda*>(c.x(0));
    u64 vt = addr(functor->vtable) - lib_base();
    for (const Request& r : kRequests) {
        if (r.lambda_vt != vt) continue;
        u64 x0 = 0;
        if (r.handler) Lambda(c.x(8), functor, c.x(1), c.x(2), g(r.handler), &x0);
        // The in-process server (--server inproc): Login / SimpleLogin apply the local server's answer (the whole
        // player state) instead of the invented "Dummy" player.
        else if (server::enabled()) Lambda(c.x(8), functor, c.x(1), c.x(2), g("_ZN10CApiNotify14OnGetPlayerResEPaRj"), &x0);
        else LoginLambda(c.x(8), functor, c.x(1), c.x(2), &x0);
        c.set_x(0, x0);
        return;
    }
    fatal("FakeApiCaller lambda with unknown vtable 0x%" PRIx64, (u64)vt);
}

// The status-only FakeApiCaller methods (FAKEAPI_STATUS_ONLY) the port doesn't serve: the guest's
// Status, nothing queued, so nothing reaches the local server. On the in-process route (port code,
// not guest behaviour) each call is logged, `no handler: <Method>`, as the library logs a request
// it has no handler for (docs/unimplemented-apis.md "Stub logging"); the client carries on without
// an answer (CErrorHandlerWrap::Auto sees the fid not requesting and reports success).
#define FAKEAPI_ST_ENTRY(sym, v) {sym, (u64)(v)},
struct StatusOnly {
    const char* sym;
    u64 status;
};
constexpr StatusOnly kStatusOnly[] = {FAKEAPI_STATUS_ONLY(FAKEAPI_ST_ENTRY)};
#undef FAKEAPI_ST_ENTRY
// "_ZN13FakeApiCaller9GetConfigEv" -> "GetConfig"
std::string status_method(const char* sym) {
    const char* p = sym + strlen("_ZN13FakeApiCaller");
    size_t n = 0;
    while (*p >= '0' && *p <= '9') n = n * 10 + (size_t)(*p++ - '0');
    return std::string(p, n);
}
// Initialize, BeginBridge and EndBridge are the caller's plumbing, not requests: not logged.
bool is_plumbing(const std::string& m) { return m == "Initialize" || m == "BeginBridge" || m == "EndBridge"; }
template <int I>
void h_status(Cpu& c) {
    if (on_fake_caller(c.x(0))) {
        static const std::string m = status_method(kStatusOnly[I].sym);
        if (!is_plumbing(m))
            LOGW("fakeapi", "no handler: %s (status only, not served in-process: nothing sent, nothing stored; "
                 "docs/unimplemented-apis.md)", m.c_str());
    }
    set_status(c.x(8), kStatusOnly[I].status);
}
template <int... I>
constexpr std::array<HostFn, sizeof...(I)> status_hooks(std::integer_sequence<int, I...>) {
    return {&h_status<I>...};
}
constexpr auto kStatusHooks = status_hooks(std::make_integer_sequence<int, (int)(sizeof(kStatusOnly) / sizeof(kStatusOnly[0]))>{});

// FakeApiCaller::GetGachaInData(): the guest only returns Status 0 (nothing queued, so the gacha
// screen gets no GachaHashMap and lists no gachas). In-process server (--server inproc; not guest
// behaviour): queue it like the other requests, answered by the local server and handed to
// CApiNotify::OnGetGachaInDataRes (the handler NetworkApiCaller's response goes to).
constexpr char kGetGachaInData[] = "_ZN13FakeApiCaller14GetGachaInDataEv";
constexpr u32 kFidGetGachaInData = 0x8e4a88d7;
void h_get_gacha_in_data(Cpu& c) {
    if (!g_route_on) {
        set_status(c.x(8), 0);
        return;
    }
    if (server::enabled()) {
        u64 x[8] = {c.x(0)};
        server_port::capture(kGetGachaInData, kFidGetGachaInData, x);
    }
    queue_served(c, kFidGetGachaInData, "_ZN10CApiNotify19OnGetGachaInDataResEPaRj", "FakeApi/gacha_in_data.msgp");
}
// FakeApiCaller::GetWorldMapInfoList(u32 episode): the guest only returns Status 0. Restore run
// (--server inproc; port code, not guest behaviour): queued like GetGachaInData and answered by
// CApiNotify::OnGetWorldMapInfoListRes, the handler NetworkApiCaller's response goes to; the local
// server (server/campaign.cpp) fills the body. On another caller it stays a Status-only method.
constexpr char kGetWorldMapInfoList[] = "_ZN13FakeApiCaller19GetWorldMapInfoListEj";
constexpr u32 kFidGetWorldMapInfoList = 0x15a9bdbd;
void h_get_world_map_info_list(Cpu& c) {
    if (!g_route_on || !server::campaign::enabled()) {
        set_status(c.x(8), 0);
        return;
    }
    u64 x[8];
    for (int i = 0; i < 8; i++) x[i] = c.x(i);
    server_port::remember(server_port::inproc_request(kGetWorldMapInfoList, kFidGetWorldMapInfoList, x));
    queue_served(c, kFidGetWorldMapInfoList, "_ZN10CApiNotify24OnGetWorldMapInfoListResEPaRj", "FakeApi/world_map_info_list.msgp");
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
    return server::enabled() && g_route_on && addr(reinterpret_cast<const FakeApiCaller*>(self)->vtable) == fake_vt;
}

// IApiCaller::UpdatePartySet(PartySetInfo const&): the server gets the party set as
// PartySetInfo::Serialize() text (what NetworkApiCaller sends).
constexpr char kUpdatePartySet[] = "_ZN10IApiCaller14UpdatePartySetERK12PartySetInfo";
void h_update_party_set(Cpu& c) {
    if (!on_fake_caller(c.x(0))) {
        set_status(c.x(8), 0);  // guest behaviour
        return;
    }
    static const u64 serialize = main_lib()->sym("_ZNK12PartySetInfo9SerializeEv");
    guest::String text;
    guest_call(serialize, GuestArgs().i(c.x(1)).sret(&text));
    std::string s = text.str();
    text.destroy();
    u64 x[8] = {c.x(0), (u64)s.c_str()};
    server_port::capture("_ZN13FakeApiCaller14UpdatePartySetEPKa", 0xc119d0d8, x);
    queue_served(c, 0xc119d0d8, "_ZN10CApiNotify19OnUpdatePartySetResEPaRj", "FakeApi/party_set_update.msgp");
}

// IApiCaller::SetAssist(unsigned long character, unsigned long assist character).
constexpr char kSetAssist[] = "_ZN10IApiCaller9SetAssistEmm";
void h_set_assist(Cpu& c) {
    if (!on_fake_caller(c.x(0))) {
        set_status(c.x(8), 0);  // guest behaviour
        return;
    }
    u64 x[8] = {c.x(0), c.x(1), c.x(2)};
    server_port::capture("_ZN13FakeApiCaller9SetAssistEmm", 0x741e0072, x);
    queue_served(c, 0x741e0072, "_ZN10CApiNotify14OnSetAssistResEPaRj", "FakeApi/set_assist.msgp");
}

// IApiCaller::UpdateView(Common::ViewFlagType kind, unsigned long flags): the "already seen"
// flags of UI tutorials and dialogs (CTutorialManager::ST_Net_Tutoflag).
constexpr char kUpdateView[] = "_ZN10IApiCaller10UpdateViewEN6Common12ViewFlagTypeEm";
void h_update_view(Cpu& c) {
    if (!on_fake_caller(c.x(0))) {
        set_status(c.x(8), 0);  // guest behaviour
        return;
    }
    u64 x[8] = {c.x(0), (u8)c.x(1), c.x(2)};
    server_port::capture("_ZN13FakeApiCaller10UpdateViewEhm", 0xa2eb69ba, x);
    queue_served(c, 0xa2eb69ba, "_ZN10CApiNotify15OnUpdateViewResEPaRj", "FakeApi/update_view.msgp");
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
        set_status(c.x(8), 0);  // guest behaviour
        return;
    }
    u64 x[8] = {c.x(0), 0};
    server_port::capture("_ZN13FakeApiCaller14GetMissionListEi", 0x57308f4d, x);
    queue_served(c, 0x57308f4d, "_ZN10CApiNotify19OnGetMissionListResEPaRj", "FakeApi/mission_list.msgp");
}

// Status-only FakeApiCaller methods (the guest stores a Status and sends nothing) that the
// local server answers in-process (agent server-rules; port code, not guest behaviour): the
// arguments go to server_port::capture and the request is queued with NetworkApiCaller's FunctionID,
// answered by the CApiNotify handler NetworkApiCaller's response goes to. On another caller
// the guest's Status. The gear screens (CCustomGear), the favor-achievement receive
// (CAdjutantSelect -> AchievementListReceive), the settings and account screens
// (docs/client-changes.md), the defeat dialog's continue (CPauseMenu -> MissionContinue;
// MissionLose has no 3.7.0 caller) and the accessory inheritance (CItemStrengtheningPotal ->
// InheritAccessory), the mascot and the role change, and the coin shop's purchase (CPaymentManager) use them.
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
    // settings and account (server/src/api/settings/): the options (その他設定 / バトル設定, 初期設定に戻す),
    // the birth month (BirthDialogUtility::RequestGetAge, CBirthDialog), 期限情報's read marks
    // (CTermInfoUI), the guide popup's link (CGuideInformation), シナリオライブラリ (CScenarioLibrary)
    {"_ZN13FakeApiCaller9GetConfigEv", 0, 0x8fcedcac, "_ZN10CApiNotify14OnGetConfigResEPaRj", "FakeApi/get_config.msgp"},
    {"_ZN13FakeApiCaller12UpdateConfigEjPKaj", 0, 0xf82ca7ca, "_ZN10CApiNotify17OnUpdateConfigResEPaRj", "FakeApi/update_config.msgp"},
    {"_ZN13FakeApiCaller11ResetConfigEv", 0, 0x685d66f3, "_ZN10CApiNotify16OnResetConfigResEPaRj", "FakeApi/reset_config.msgp"},
    {"_ZN13FakeApiCaller17GetBirthYearMonthEv", 1, 0x59a48d41, "_ZN10CApiNotify22OnGetBirthYearMonthResEPaRj", "FakeApi/get_birth_year_month.msgp"},
    {"_ZN13FakeApiCaller20UpdateBirthYearMonthEth", 1, 0x0088b260, "_ZN10CApiNotify25OnUpdateBirthYearMonthResEPaRj",
     "FakeApi/update_birth_year_month.msgp"},
    {"_ZN13FakeApiCaller18ReadExpirationInfoERKN9Framework10CSTLVectorIjEE", 0, 0xdc269365, "_ZN10CApiNotify23OnReadExpirationInfoResEPaRj",
     "FakeApi/read_expiration_info.msgp"},
    {"_ZN13FakeApiCaller20SendGuideInformationEj", 0, 0x5cf6a3e9, "_ZN10CApiNotify25OnSendGuideInformationResEPaRj",
     "FakeApi/send_guide_information.msgp"},
    {"_ZN13FakeApiCaller26GetScenarioLibraryInfoListEj", 0, 0xe08c972e, "_ZN10CApiNotify31OnGetScenarioLibraryInfoListResEPaRj",
     "FakeApi/get_scenario_library_info_list.msgp"},
    // The equipment storage and the overflow box (server/src/api/storage/; the item menu's
    // 装備倉庫 and 一時保管庫 screens, CItemStorage).
    {"_ZN13FakeApiCaller14GetStorageInfoEv", 0, 0x06669069, "_ZN10CApiNotify19OnGetStorageInfoResEPaRj", "FakeApi/storage_info.msgp"},
    {"_ZN13FakeApiCaller11DepositItemERKN9Framework10CSTLVectorImEE", 0, 0xc4cd3b1a, "_ZN10CApiNotify16OnDepositItemResEPaRj",
     "FakeApi/deposit_item.msgp"},
    {"_ZN13FakeApiCaller23WithdrawItemFromStorageERKN9Framework10CSTLVectorImEE", 0, 0xde86bab0,
     "_ZN10CApiNotify28OnWithdrawItemFromStorageResEPaRj", "FakeApi/withdraw_item_from_storage.msgp"},
    {"_ZN13FakeApiCaller20SellItemsFromStorageERKN9Framework10CSTLVectorImEE", 0, 0x81416fa8,
     "_ZN10CApiNotify25OnSellItemsFromStorageResEPaRj", "FakeApi/sell_items_from_storage.msgp"},
    {"_ZN13FakeApiCaller15LockStorageItemERKN9Framework10CSTLVectorImEE", 0, 0xb398671e, "_ZN10CApiNotify20OnLockStorageItemResEPaRj",
     "FakeApi/lock_storage_item.msgp"},
    {"_ZN13FakeApiCaller17UnlockStorageItemERKN9Framework10CSTLVectorImEE", 0, 0xb28403c2, "_ZN10CApiNotify22OnUnlockStorageItemResEPaRj",
     "FakeApi/unlock_storage_item.msgp"},
    {"_ZN13FakeApiCaller21GetOneTimeStorageInfoEv", 0, 0x074df139, "_ZN10CApiNotify26OnGetOneTimeStorageInfoResEPaRj",
     "FakeApi/one_time_storage_info.msgp"},
    {"_ZN13FakeApiCaller30WithdrawItemFromOneTimeStorageEjj", 0, 0xaa6a1d11, "_ZN10CApiNotify35OnWithdrawItemFromOneTimeStorageResEPaRj",
     "FakeApi/withdraw_item_from_one_time_storage.msgp"},
    {"_ZN13FakeApiCaller34BulkWithdrawItemFromOneTimeStorageERKN9Framework10CSTLVectorIjEES4_", 0, 0x59f02ddd,
     "_ZN10CApiNotify39OnBulkWithdrawItemFromOneTimeStorageResEPaRj", "FakeApi/bulk_withdraw_item_from_one_time_storage.msgp"},
    {"_ZN13FakeApiCaller26ClearNewOneTimeStorageItemERKN9Framework10CSTLVectorIjEE", 0, 0xd4f178a3,
     "_ZN10CApiNotify31OnClearNewOneTimeStorageItemResEPaRj", "FakeApi/clear_new_one_time_storage_item.msgp"},
    {"_ZN13FakeApiCaller15MissionContinueEb", 0, 0x755cba3d, "_ZN10CApiNotify20OnMissionContinueResEPaRj", "FakeApi/mission_continue.msgp"},
    {"_ZN13FakeApiCaller11MissionLoseEv", 0, 0x863bb1ec, "_ZN10CApiNotify16OnMissionLoseResEPaRj", "FakeApi/mission_lose.msgp"},
    {"_ZN13FakeApiCaller16InheritAccessoryEmm", 1, 0xd9feb3e8, "_ZN10CApiNotify21OnInheritAccessoryResEPaRj", "FakeApi/inherit_accessory.msgp"},
    // the home's mascot (CAdjutantSelect -> CMascotSelectDialog) and a character's role (CRoleSelect)
    {"_ZN13FakeApiCaller12ChangeMascotEj", 1, 0xd1bcebee, "_ZN10CApiNotify17OnChangeMascotResEPaRj", "FakeApi/change_mascot.msgp"},
    {"_ZN13FakeApiCaller10ChangeRoleEmj", 0, 0x720e2bac, "_ZN10CApiNotify15OnChangeRoleResEPaRj", "FakeApi/change_role.msgp"},
    // Paid currency (server/src/api/shop/coins.cpp): the coin shop's purchase (CPaymentManager::
    // Progress_Purchase / VerifyReceipt_) and the premium shop's list.
    {"_ZN13FakeApiCaller8CoinListEv", 0, 0xd859bb89, "_ZN10CApiNotify13OnCoinListResEPaRj", "FakeApi/coin_list.msgp"},
    {"_ZN13FakeApiCaller17CoinDepositCreateEhiPKc", 0, 0x3850fb96, "_ZN10CApiNotify22OnCoinDepositCreateResEPaRj",
     "FakeApi/coin_deposit_create.msgp"},
    {"_ZN13FakeApiCaller24CoinDepositAndroidUpdateEjPKcS1_", 1, 0x089ac659, "_ZN10CApiNotify29OnCoinDepositAndroidUpdateResEPaRj",
     "FakeApi/coin_deposit_android_update.msgp"},
    {"_ZN13FakeApiCaller20CoinDepositIOSUpdateEjPKcS1_", 1, 0xc5193b15, "_ZN10CApiNotify25OnCoinDepositIOSUpdateResEPaRj",
     "FakeApi/coin_deposit_ios_update.msgp"},
    {"_ZN13FakeApiCaller23CoinDepositAmazonUpdateEjPKcS1_", 1, 0x0bc7f736, "_ZN10CApiNotify28OnCoinDepositAmazonUpdateResEPaRj",
     "FakeApi/coin_deposit_amazon_update.msgp"},
    {"_ZN13FakeApiCaller18DirectItemShopListEv", 1, 0xc367268b, "_ZN10CApiNotify23OnDirectItemShopListResEPaRj",
     "FakeApi/direct_item_shop_list.msgp"},
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
        set_status(c.x(8), s.status);  // guest behaviour
        return;
    }
    u64 x[8];
    for (int k = 0; k < 8; k++) x[k] = c.x(k);
    server_port::capture(s.sym, s.fid, x);
    queue_served(c, s.fid, s.handler, s.file);
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
        set_status(c.x(8), 0);  // guest behaviour
        return;
    }
    u64 x[8] = {c.x(0)};
    server_port::capture(kDeepSpaceActiveList, 0xa7a82ef5, x);
    queue_served(c, 0xa7a82ef5, "_ZN10CApiNotify24OnDeepSpaceActiveListResEPaRj", "FakeApi/deep_space_active_list.msgp");
}

// FakeApiCaller::Home3DAnd2DSwitching(u8 is_3d): the guest returns Status 1 and queues nothing, so
// the home that sent it (CHome::Progress, a home character shown in 2D only, or the 会話モード
// 2D/3D変更 button) never continues: with a 2D-only character it stays empty. In-process server
// (--server inproc; port code, not guest behaviour): queued like the base-class methods above and
// answered by CApiNotify::OnHome3DAnd2DSwitchingRes, the handler NetworkApiCaller's response goes
// to; the local server (server/src/api/player/home.cpp) stores the mode. Otherwise the guest's
// Status 1.
constexpr char kHome3DAnd2DSwitching[] = "_ZN13FakeApiCaller20Home3DAnd2DSwitchingEh";
void h_home3d_and_2d_switching(Cpu& c) {
    if (!on_fake_caller(c.x(0))) {
        set_status(c.x(8), 1);  // guest behaviour
        return;
    }
    u64 x[8] = {c.x(0), c.x(1) & 0xff};
    server_port::capture(kHome3DAnd2DSwitching, 0xa092292c, x);
    queue_served(c, 0xa092292c, "_ZN10CApiNotify25OnHome3DAnd2DSwitchingResEPaRj", "FakeApi/home3d_switching.msgp");
}

// Sphere 211 (restore run, --server inproc; agent sphere211): the Sphere211* requests. The
// IApiCaller base methods return Status 0 and send nothing, and FakeApiCaller's own overrides
// (ReturnSphere211, StaminaHeal, UseRerollItem, FloorClear, SelectedFloor) only return a Status.
// In-process server (--server inproc; not guest behaviour): on the FakeApiCaller, queue them for the local
// server (server/src/api/sphere211/sphere211.cpp), answered by the CApiNotify handler NetworkApiCaller's
// response goes to. Otherwise the guest behaviour. {hooked symbol, capture symbol (the
// FakeApiCaller-style mangling server_port::capture parses), fid (docs/api.md), handler}.
struct ServedMethod {
    const char *sym, *capture;
    u32 fid;
    const char* handler;
};
template <int N>
bool in_table(const ServedMethod (&table)[N], const char* sym) {
    for (const ServedMethod& m : table)
        if (!strcmp(sym, m.sym)) return true;
    return false;
}
// One served method of a table (kSphere, kEventApi): on the FakeApiCaller its arguments go to the
// local server and the request is queued under `File`; on another caller the guest's Status 0 (both
// the base and the FakeApiCaller bodies).
template <const ServedMethod* Table, const char* File, int I>
void h_served_method(Cpu& c) {
    if (!on_fake_caller(c.x(0))) {
        set_status(c.x(8), 0);
        return;
    }
    u64 x[8];
    for (int k = 0; k < 8; k++) x[k] = c.x(k);
    server_port::capture(Table[I].capture, Table[I].fid, x);
    queue_served(c, Table[I].fid, Table[I].handler, File);
}
template <const ServedMethod* Table, const char* File, int... I>
constexpr std::array<HostFn, sizeof...(I)> served_method_hooks(std::integer_sequence<int, I...>) {
    return {&h_served_method<Table, File, I>...};
}

constexpr ServedMethod kSphere[] = {
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
constexpr char kSphereFile[] = "FakeApi/sphere211.msgp";
constexpr auto kSphereHooks = served_method_hooks<kSphere, kSphereFile>(std::make_integer_sequence<int, kNumSphere>{});

// Event rankings and world bosses (restore run, --server inproc; agent events-extras): the
// IApiCaller base methods of the five ranking requests return Status 0 and send nothing, and
// FakeApiCaller::GetWorldBossInfo only returns a Status. In-process server (not guest
// behaviour): on the FakeApiCaller, queue them for the local server (server/src/api/events/ranking.cpp,
// server/src/api/events/world_boss.cpp), answered by the CApiNotify handler NetworkApiCaller's response goes to
// (all plain apply; the ranking results also AddItem / UpdateStackItem). Otherwise the guest
// behaviour. Same row shape as kSphere.
constexpr ServedMethod kEventApi[] = {
    {"_ZN10IApiCaller23CheckEventRankingResultEv", "_ZN13FakeApiCaller23CheckEventRankingResultEv", 0x83809bfb, "_ZN10CApiNotify28OnCheckEventRankingResultResEPaRj"},
    {"_ZN10IApiCaller25ReceiveEventRankingResultEv", "_ZN13FakeApiCaller25ReceiveEventRankingResultEv", 0x4700c6f7, "_ZN10CApiNotify30OnReceiveEventRankingResultResEPaRj"},
    {"_ZN10IApiCaller19GetEventRankingInfoEj", "_ZN13FakeApiCaller19GetEventRankingInfoEj", 0x94456167, "_ZN10CApiNotify24OnGetEventRankingInfoResEPaRj"},
    {"_ZN10IApiCaller20ClearNewEventRankingERKN9Framework10CSTLVectorIjEE", "_ZN13FakeApiCaller20ClearNewEventRankingERKN9Framework10CSTLVectorIjEE", 0xcb1a5781, "_ZN10CApiNotify25OnClearNewEventRankingResEPaRj"},
    {"_ZN10IApiCaller19GetPlayerDetailInfoEj", "_ZN13FakeApiCaller19GetPlayerDetailInfoEj", 0x626e1e5f, "_ZN10CApiNotify24OnGetPlayerDetailInfoResEPaRj"},
    {"_ZN13FakeApiCaller16GetWorldBossInfoEj", "_ZN13FakeApiCaller16GetWorldBossInfoEj", 0x86d6a220, "_ZN10CApiNotify21OnGetWorldBossInfoResEPaRj"},
};
constexpr int kNumEventApi = sizeof(kEventApi) / sizeof(kEventApi[0]);
constexpr char kEventApiFile[] = "FakeApi/event_extras.msgp";
constexpr auto kEventApiHooks = served_method_hooks<kEventApi, kEventApiFile>(std::make_integer_sequence<int, kNumEventApi>{});

// IApiCaller::EndMissionTalk(unsigned int type, unsigned int mission, unsigned char, unsigned int):
// the end of a story mission's scene. 3.7.0's EventScenario::CEventScenario::Exit sends it
// (CErrorHandlerWrap::Auto, fid 1d00a78c); FakeApiCaller doesn't override it, so the base stub
// sends nothing and a story mission never clears. On the FakeApiCaller route (port code, not
// guest behaviour) it is queued like the other served base-class methods (kSphere): the local
// server answers it through its one request lifecycle, server::answer, as soa-server's wire does
// (the scene's effect, then GetPlayMission's answer: server/src/core/lifecycle.cpp), and the
// answer goes to CApiNotify::OnEndMissionTalkRes, the handler NetworkApiCaller's response goes to
// ((b) @014c0d68: DeserializeToInfo, ErrorHandler::Success, the same body as
// OnGetPlayMissionRes @014cd380). Before CR2 (2026-10-07) the hook re-implemented server::answer's
// EndMissionTalk itself (end_mission_talk, then a queued GetPlayMission); before the rebase's
// revision 2 restore_campaign.cpp did the same from a CEventScenario::Exit hook (the offline build
// had dropped the request). Otherwise the guest behaviour.
constexpr char kEndMissionTalk[] = "_ZN10IApiCaller14EndMissionTalkEjjhj";
constexpr u32 kFidEndMissionTalk = 0x1d00a78c;
void h_end_mission_talk(Cpu& c) {
    if (!on_fake_caller(c.x(0))) {
        set_status(c.x(8), 0);  // the base stub's Status (nothing in flight)
        return;
    }
    u64 x[8];
    for (int k = 0; k < 8; k++) x[k] = c.x(k);
    server_port::capture("_ZN13FakeApiCaller14EndMissionTalkEjjhj", kFidEndMissionTalk, x);
    queue_served(c, kFidEndMissionTalk, "_ZN10CApiNotify19OnEndMissionTalkResEPaRj", "FakeApi/end_mission_talk.msgp");
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
    for (size_t i = 0; i < kStatusHooks.size(); i++) {
        const char* sym = kStatusOnly[i].sym;
        if (strcmp(sym, kGetGachaInData) != 0 && strcmp(sym, kGetWorldMapInfoList) != 0 && !is_served_status_only(sym) &&
            strcmp(sym, kDeepSpaceActiveList) != 0 && strcmp(sym, kHome3DAnd2DSwitching) != 0 && !in_table(kSphere, sym) &&
            !in_table(kEventApi, sym))
            reg({sym, kStatusHooks[i], "FakeApiCaller status"});
    }
    reg({kGetGachaInData, h_get_gacha_in_data, "FakeApiCaller status (served by the local server in-process)"});
    for (size_t i = 0; i < kServedHooks.size(); i++)
        reg({kServedStatusOnly[i].sym, kServedHooks[i], "FakeApiCaller status (served by the local server in-process)"});
    reg({kUpdatePartySet, h_update_party_set, "IApiCaller::UpdatePartySet (served by the local server in-process)"});
    reg({kSetAssist, h_set_assist, "IApiCaller::SetAssist (served by the local server in-process)"});
    reg({kUpdateView, h_update_view, "IApiCaller::UpdateView (served by the local server in-process)"});
    reg({kGetMissionList, h_get_mission_list, "IApiCaller::GetMissionList (served by the local server in-process)"});
    reg({kEndMissionTalk, h_end_mission_talk, "IApiCaller::EndMissionTalk (served by the local server in-process)"});
    reg({kGetWorldMapInfoList, h_get_world_map_info_list, "FakeApiCaller status (served in-process)"});
    reg({kDeepSpaceActiveList, h_deep_space_active_list, "FakeApiCaller status (served by the local server in-process)"});
    reg({kHome3DAnd2DSwitching, h_home3d_and_2d_switching, "FakeApiCaller status (served by the local server in-process)"});
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

NATIVE_ROUTE_METHOD("_ZN13FakeApiCaller12AddLocalFileEN4Aska5Yayoi7GameRPC12GameProtocol10FunctionIDEPKcNSt6__ndk18functionIFNS0_6StatusEPaRjEEE",
                    &FakeApiCaller::AddLocalFile, "FakeApiCaller");
NATIVE_ROUTE_METHOD("_ZN13FakeApiCaller8ProgressEv", &FakeApiCaller::Progress, "FakeApiCaller");
NATIVE_ROUTE_FUNCTION("_ZThn8_N13FakeApiCaller8ProgressEv", [](Cpu& c) { reinterpret_cast<FakeApiCaller*>(c.x(0) - 8)->Progress(); },
                      "FakeApiCaller");
NATIVE_ROUTE_FUNCTION("_ZNK13FakeApiCaller12IsRequestingEN4Aska5Yayoi7GameRPC12GameProtocol10FunctionIDE",
                [](Cpu& c) {
                    // In-process server (--server inproc; not guest behaviour): a request the fake
                    // never queues (the status-only methods) is finished rather than in flight
                    // forever, so the screens waiting on it move on.
                    if (g_route_on && !caller(c)->FindInfo((u32)c.x(1))) return c.set_x(0, 0);
                    c.set_x(0, caller(c)->IsRequesting((u32)c.x(1)));
                }, "FakeApiCaller");
NATIVE_ROUTE_METHOD("_ZN13FakeApiCaller7ReleaseEv", &FakeApiCaller::Release, "FakeApiCaller");
NATIVE_ROUTE_FUNCTION("_ZN13FakeApiCaller10InitializeEv", [](Cpu& c) { set_status(c.x(8), 1); }, "FakeApiCaller");
NATIVE_ROUTE_METHOD("_ZN13FakeApiCallerC2Ev", &FakeApiCaller::CtorBase, "FakeApiCaller");
NATIVE_ROUTE_METHOD("_ZN13FakeApiCallerD1Ev", &FakeApiCaller::Dtor, "FakeApiCaller");
NATIVE_ROUTE_METHOD("_ZN13FakeApiCallerD0Ev", &FakeApiCaller::DtorDelete, "FakeApiCaller");
NATIVE_ROUTE_FUNCTION("_ZThn8_N13FakeApiCallerD1Ev", [](Cpu& c) { reinterpret_cast<FakeApiCaller*>(c.x(0) - 8)->Dtor(); }, "FakeApiCaller");
NATIVE_ROUTE_FUNCTION("_ZThn8_N13FakeApiCallerD0Ev", [](Cpu& c) { reinterpret_cast<FakeApiCaller*>(c.x(0) - 8)->DtorDelete(); },
                      "FakeApiCaller");

}  // namespace soa::native::fakeapi

// ---- differential tests -------------------------------------------------------------------
// The game never constructs a FakeApiCaller, so the tests build bare objects (vtable-less: the
// methods under test only use the map and the address of m_notify) and compare the guest and
// native code on them. CApiNotify handlers, the resource manager, Aska::Random and
// CParameterManager::Deserialize are stubbed and their calls compared.
#include "native/common/guest_stub.h"
#include "native/common/test.h"

namespace soa::native::fakeapi {
namespace {

struct Obj {
    alignas(16) u8 raw[sizeof(FakeApiCaller)] = {};
    FakeApiCaller* obj() { return reinterpret_cast<FakeApiCaller*>(raw); }
    u64 p() { return (u64)raw; }
    Obj() { obj()->m_infos.begin_node = obj()->m_infos.end(); }
};

// The map as text: per node key, Info fid/state, name, and the stored functor (vtable, captured
// owner relative to the object, inline or not).
std::string dump(FakeApiCaller* self) {
    std::string s;
    char b[256];
    InfoMap& m = self->m_infos;
    snprintf(b, sizeof b, "size=%" PRIu64 " begin=%s;", (u64)m.size, m.begin_node == m.end() ? "end" : "node");
    s += b;
    for (InfoNode* n = m.begin(); n != m.end(); n = InfoMap::next(n)) {
        const Info& info = n->value.second;
        const auto* f = reinterpret_cast<const RequestLambda*>(info.m_fn.f);
        snprintf(b, sizeof b, " [%08x %08x st%u %s vt=%" PRIx64 " own=%" PRId64 " inl=%d]", n->value.first, info.m_fid, info.m_state,
                 info.m_name.str().c_str(), f ? (u64)(addr(f->vtable) - lib_base()) : (u64)0, f ? (s64)(addr(f->f) - addr(self)) : (s64)0,
                 info.m_fn.is_inline());
        s += b;
    }
    return s;
}

u64 guest_request(TestContext& t, FakeApiCaller* self, const Request& r) {
    u64 st = 0xdead;
    GuestArgs a;
    a.p(self).sret(&st);
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
            u64 sg = guest_request(t, A.obj(), r), sn = 0xdead;
            Request_((u64)&sn, B.obj(), r);
            if (sg != sn) { t.fail("%s status %" PRIu64 " vs %" PRIu64, r.sym, sg, sn); bad++; }
        } else if (kind < 8) {
            // Move a request along (what Progress would do).
            u32 fid = fids[t.rand_int(0, (int)fids.size() - 1)];
            InfoNode *na = A.obj()->FindInfo(fid), *nb = B.obj()->FindInfo(fid);
            if (na && nb) na->value.second.m_state = nb->value.second.m_state = (u32)t.rand_int(0, 2);
        } else {
            u32 fid = kind == 8 ? fids[t.rand_int(0, (int)fids.size() - 1)] : (u32)t.rand_u64();
            bool g = guest_call(is_req, {A.p(), fid}) & 1, n = B.obj()->IsRequesting(fid);
            if (g != n) { t.fail("IsRequesting(%08x) %d vs %d", fid, g, n); bad++; }
        }
        std::string da = dump(A.obj()), db = dump(B.obj());
        if (da != db) {
            t.fail("step %d map differs:\n  guest  %s\n  native %s", step, da.c_str(), db.c_str());
            bad++;
        }
    }
    // Every request on a fresh object, in table order (the shared-FunctionID quirk).
    Obj C, D;
    for (const Request& r : kRequests) {
        guest_request(t, C.obj(), r);
        u64 sn;
        Request_((u64)&sn, D.obj(), r);
    }
    t.expect_eq(dump(C.obj()), dump(D.obj()), "all requests");
    guest_call(t.sym("_ZN13FakeApiCaller7ReleaseEv"), {A.p()});
    B.obj()->Release();
    guest_call(t.sym("_ZN13FakeApiCaller7ReleaseEv"), {C.p()});
    D.obj()->Release();
    t.expect_eq(dump(A.obj()), dump(B.obj()), "Release");
    t.expect_eq(dump(C.obj()), dump(D.obj()), "Release (all)");
    t.expect_eq((u64)B.obj()->m_infos.root, (u64)0, "Release root");
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
std::string ason_text(const data_formats::AValue* v, int depth = 0) {
    using data_formats::AValue;
    if (!v) return "null";
    char b[64];
    switch (v->m_kind) {
        case AValue::kUInt: case AValue::kSInt: snprintf(b, sizeof b, "%" PRIu64, (u64)v->m_body.u); return b;
        case AValue::kString: return "\"" + std::string(v->m_body.str.m_data, v->m_length) + "\"";
        case AValue::kMap: {
            std::string s = "{";
            const data_formats::AMap& m = v->m_body.map;
            for (u32 i = 0; i < m.m_count && depth < 4; i++)
                s += ason_text(&m.m_pairs[i].key, depth + 1) + ":" + ason_text(&m.m_pairs[i].value, depth + 1) + ",";
            return s + "}";
        }
        default: snprintf(b, sizeof b, "<type %u>", v->m_kind); return b;
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
                if (v == addr(&owner.obj()->m_notify)) return "notify";
                if (v == (u64)payload) return "data";
                if (v == (u64)&size) return "&size";
                return std::to_string(v);
            };
            for (const std::string& h : names) {
                if (h == kRandom || h == kDeser) continue;
                s.behave[h] = [&, h](Cpu& c) {
                    set_status(c.x(8), 0x5000 + h.size());
                    c.set_x(0, 0x77);
                };
            }
            s.behave[kRandom] = s.behave["Random"] = [&](Cpu& c) { c.set_x(0, rnd += 0x111); };
            s.arity["Random"] = {0, 0};
            s.behave[kDeser] = [&](Cpu& c) {
                // (x1 is the root AValue's AMap body: the value 8 bytes before it)
                s.log.push_back("Deserialize " + std::string(c.x(0) == parameter_manager() ? "pm" : "?") + " " +
                                ason_text(reinterpret_cast<const data_formats::AValue*>(c.x(1) - offsetof(data_formats::AValue, m_body))));
            };
            libcxx::function fn = request_function(owner.obj(), r.lambda_vt);
            const auto* functor = reinterpret_cast<const RequestLambda*>(fn.buf);
            status[side] = 0xdead;
            if (side == 0) {
                x0[side] = guest_call(lib_base() + r.lambda_op, GuestArgs().p(functor).p(&data).p(&size).sret(&status[side])).x0;
            } else if (r.handler) {
                Lambda((u64)&status[side], functor, (u64)&data, (u64)&size, guest::sym(r.handler), &x0[side]);
            } else {
                LoginLambda((u64)&status[side], functor, (u64)&data, (u64)&size, &x0[side]);
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
    void obj(FakeApiCaller* self) {
        m[addr(self)] = "self";
        m[addr(&self->m_fiber)] = "self+8";
        m[addr(&self->m_notify)] = "notify";
    }
    void names_of(FakeApiCaller* self) {
        self->m_infos.for_each([&](InfoNode* n) { m[addr(n->value.second.m_name.data())] = n->value.second.m_name.str(); });
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
            guest_request(t, A.obj(), r);
            u64 st;
            Request_((u64)&st, B.obj(), r);
        }
        std::vector<int> loading;
        for (int i = 0; i < 200; i++) loading.push_back(t.rand_int(0, 3) == 0);
        std::vector<std::string> logs[2];
        for (int side = 0; side < 2; side++) {
            FakeApiCaller* self = side ? B.obj() : A.obj();
            Names nm;
            nm.obj(self);
            nm.names_of(self);
            nm.m[*reinterpret_cast<const u64*>(guest::sym("_ZN9Framework10TSingletonI20CGameResourceManagerE11m_pInstanceE"))] = "rm";
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
                    if (pass & 1) guest_call(t.sym("_ZThn8_N13FakeApiCaller8ProgressEv"), {addr(&self->m_fiber)});
                    else guest_call(t.sym("_ZN13FakeApiCaller8ProgressEv"), {addr(self)});
                } else {
                    self->Progress();
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

// The in-process route's answer to a request no handler answers (docs/unimplemented-apis.md step
// 9: no canned files): ServeProgress hands the guest lambda an empty map, {} (one byte 0x80), and
// the entry finishes (state 2). SetStampSlot is the request (the last one without a handler when
// this was written); the server is switched off for the test, so server::answer takes the host's
// fallback for any method, as it does for one without a handler (and logs `no handler`).
NATIVE_TEST("fakeapi/serve-no-handler") {
    const Request* r = nullptr;
    for (const Request& q : kRequests)
        if (strstr(q.sym, "12SetStampSlot")) r = &q;
    if (!r || !r->handler) return t.fail("SetStampSlot not in the request table");
    if (!stub(r->handler, r->handler, 3)) return t.fail("can't stub %s", r->handler);
    const char* kDeser = "_ZN17CParameterManager11DeserializeEPKN4Aska4ASON6AValue4AMapE";
    if (!stub(kDeser, kDeser, 1)) return t.fail("can't stub %s", kDeser);
    server::ServerConfig& cfg = server::config();
    const bool was_enabled = cfg.enabled, was_on = g_route_on;
    cfg.enabled = false;
    g_route_on = true;
    Obj B;
    u64 st = 0;
    Request_((u64)&st, B.obj(), *r);
    server_port::remember(server::Request{"SetStampSlot", r->fid, {}, {}, {}});
    std::vector<u8> body;
    u32 size = 0xffffffff;
    int calls = 0;
    {
        StubSession s;
        s.only = {r->handler, kDeser};
        s.behave[r->handler] = [&](Cpu& c) {
            calls++;
            size = *reinterpret_cast<const u32*>(c.x(2));
            body.assign((const u8*)c.x(1), (const u8*)c.x(1) + size);
        };
        s.behave[kDeser] = [&](Cpu&) {};
        B.obj()->ServeProgress();  // state 0 -> 1 (the guest's first step)
        t.expect_eq(calls, 0, "not answered on the first frame");
        B.obj()->ServeProgress();  // answered
    }
    t.expect_eq(calls, 1, "the handler ran once");
    t.expect_eq(size, (u32)1, "the body is one byte");
    t.expect_eq(body.empty() ? -1 : (int)body[0], 0x80, "the body is {}");
    InfoNode* n = B.obj()->m_infos.begin();
    t.expect_eq(n != B.obj()->m_infos.end() ? (int)n->value.second.m_state : -1, 2, "the entry finished (state 2)");
    B.obj()->Release();
    cfg.enabled = was_enabled;
    g_route_on = was_on;
}

namespace {
// The object's own words, as the constructor / destructor leave them.
std::string header(FakeApiCaller* self) {
    char b[160];
    snprintf(b, sizeof b, "vt=%" PRIx64 " fiber_vt=%" PRIx64 " begin=%" PRId64 " root=%" PRIx64 " size=%" PRIx64, (u64)(addr(self->vtable) - lib_base()),
             (u64)(addr(self->m_fiber.vtable) - lib_base()), (s64)(addr(self->m_infos.begin_node) - addr(self)), addr(self->m_infos.root),
             (u64)self->m_infos.size);
    return b;
}
}  // namespace

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
            FakeApiCaller* self = objs[side].obj();
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
            if (side == 0) guest_call(t.sym("_ZN13FakeApiCallerC2Ev"), {addr(self)});
            else self->CtorBase();
            s.log.push_back("ctor: " + header(self));
            for (int i : reqs) {
                u64 st;
                if (side == 0) guest_request(t, self, kRequests[i]);
                else Request_((u64)&st, self, kRequests[i]);
            }
            s.log.push_back(dump(self));
            u64 arg = cs.thunk ? addr(&self->m_fiber) : addr(self);
            if (side == 0) guest_call(t.sym(cs.dtor), {arg});
            else if (cs.deleting) self->DtorDelete();
            else self->Dtor();
            s.log.push_back("dtor: " + header(self));
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
