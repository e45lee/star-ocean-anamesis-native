// Port-only reachability hooks (not game behaviour; inert unless a control command asks):
//
//   phase:N               CPhase::RequestSwitch(N) on the game thread, as a menu button would.
//                         Ids: 5 Mission, 0xa Shop, 0xe Presentbox, 0xf/0x10 Battle, 0x11 Gacha,
//                         0x19 BattleResumeCheck, ... (docs/notes.md).
//   call:SYMBOL[:A...]    guest_call(SYMBOL, A...) on the game thread; each A is an integer
//                         (0x.. / decimal), "s=TEXT" (a guest C string), or "f=FLOAT" (s0..).
//                         The result is logged (I/port_debug).
//   mission:LABEL         CParameterUI+0x1a0 (the selected mission CPhase_Battle hands to
//                         CStageManager::Initialize) = CHash32(LABEL), as the stripped mission
//                         select screen would; e.g. mission:mf01_001.
//   clock:+SECONDS        (--server inproc) moves the local server's clock forward (server.h
//                         set_server_clock), e.g. to bring deep-space expeditions home; the
//                         client follows with the next response's data.Time.
//   uiset:OFF:VAL         *(u32*)(CParameterUI + OFF) = VAL, e.g. uiset:0x140:5 (the mission type
//                         CPhase_Mission opens: 5 = the extra dungeon / Sphere 211 menu, 2 tower).
//   debugwin:W:H          Framework::CDebugWindows::Initialize(W, H) once, then
//                         CDebugWindows::Progress(1/30) every frame (the release build never
//                         creates the debug window manager).
//
// They run from the CPhase::Progress wrapper below (a port native: not with --natives none).
#include "native/common/port_debug.h"

#include <cinttypes>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <mutex>
#include <vector>

#include "soaruntime/core/log.h"
#include "native/common/guest_std.h"
#include "native/common/memstats.h"
#include "native/common/native.h"
#include "native/game/game_layout.h"
#include "native/params/params_layout.h"
#include "soa/chash32.h"
#include "soaserver/server.h"

namespace soa::native::port_debug {
namespace {

std::mutex g_mutex;
std::deque<std::string> g_queue;
bool g_debugwin = false;

using game::CBase;
using game::CPhase;
using game::CPhase_Base;
using params::CParameterUI;

// CParameterManager::pParameterUI(), or null.
CParameterUI* parameter_ui() {
    static u64 pm = guest::sym("_ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE");
    static u64 ui_fn = guest::sym("_ZNK17CParameterManager12pParameterUIEv");
    u64 mgr = *(const u64*)pm;
    return mgr ? reinterpret_cast<CParameterUI*>(guest_call(ui_fn, {mgr})) : nullptr;  // (none before the title)
}

u64 guest_cstr(const std::string& s) {
    u64 p = (u64)guest::new_array_nothrow(s.size() + 1);
    memcpy((void*)p, s.c_str(), s.size() + 1);
    return p;  // leaked on purpose: the callee may keep it
}

void run(const std::string& cmd, CPhase* phase_mgr) {
    if (cmd == "memstats" || cmd.rfind("memstats:", 0) == 0) {
        memstats::log(cmd.size() > 9 ? cmd.c_str() + 9 : "requested");
        return;
    }
    if (cmd.rfind("phase:", 0) == 0) {
        u32 id = (u32)strtoul(cmd.c_str() + 6, nullptr, 0);
        // What CPhase::RequestSwitch does: ToRelease the present phase, remember the request.
        CBase* cur = phase_mgr->m_pPresentSubstance;
        if (!cur) return;
        u32 now = phase_mgr->m_present;
        // A menu phase (Home, OtherMenu, Shop, Gacha, ...; a CPhase_Base) leaves when its screen
        // closes: m_nextPhase = the next phase, then delete the screen (m_screenUiId), as a menu
        // button does.
        static const u32 menu[] = {4, 7, 8, 9, 0xa, 0xb, 0xc, 0xe, 0x11, 0x12, 0x1c};
        auto* menu_phase = reinterpret_cast<CPhase_Base*>(cur);
        for (u32 m : menu)
            if (m == now && menu_phase->m_step == 2) {
                static u64 del = guest::sym("_ZN10CUIManager8DeleteUIEj");
                static u64 inst = guest::sym("_ZN9Framework10TSingletonI10CUIManagerE11m_pInstanceE");
                LOGI("port_debug", "menu phase %u: close screen %u, next phase %#x", now, menu_phase->m_screenUiId, id);
                menu_phase->m_nextPhase = id;
                guest_call(del, {*(u64*)inst, menu_phase->m_screenUiId});
                return;
            }
        LOGI("port_debug", "RequestSwitch(%#x) from phase %u", id, now);
        guest_call(static_cast<const u64*>(cur->vtable)[CBase::kSlotToRelease], {(u64)cur});
        phase_mgr->m_request = id;
        return;
    }
    if (cmd.rfind("mission:", 0) == 0) {
        CParameterUI* ui = parameter_ui();
        u32 id = chash32(cmd.c_str() + 8);
        LOGI("port_debug", "selected mission %s (%#x), was %#x", cmd.c_str() + 8, id, ui ? ui->m_selectMissionId : 0);
        if (ui) ui->m_selectMissionId = id;
        return;
    }
    if (cmd.rfind("uiset:", 0) == 0) {
        // By design a write at an offset the command names (to try fields not recovered yet; the known
        // ones: params_layout.h CParameterUI).
        CParameterUI* ui = parameter_ui();
        u64 off = 0, val = 0;
        char* e;
        off = strtoull(cmd.c_str() + 6, &e, 0);
        if (*e == ':') val = strtoull(e + 1, nullptr, 0);
        if (ui && off < 0x10000) {
            u8* field = reinterpret_cast<u8*>(ui) + off;
            u32 was, now = (u32)val;
            memcpy(&was, field, 4);
            LOGI("port_debug", "CParameterUI+%#" PRIx64 " = %#" PRIx64 " (was %#x)", off, val, was);
            memcpy(field, &now, 4);
        }
        return;
    }
    if (cmd.rfind("debugwin:", 0) == 0) {
        unsigned w = 0, h = 0;
        sscanf(cmd.c_str(), "debugwin:%u:%u", &w, &h);
        static u64 init = guest::sym("_ZN9Framework13CDebugWindows10InitializeEjj");
        LOGI("port_debug", "CDebugWindows::Initialize(%u, %u)", w, h);
        guest_call(init, {(u64)w, (u64)h});
        g_debugwin = true;
        return;
    }
    if (cmd.rfind("call:", 0) == 0) {
        std::vector<std::string> parts;
        size_t pos = 5;
        while (true) {
            size_t e = cmd.find(':', pos);
            parts.push_back(cmd.substr(pos, e == std::string::npos ? std::string::npos : e - pos));
            if (e == std::string::npos) break;
            pos = e + 1;
        }
        u64 fn = main_lib()->sym(parts[0].c_str());  // (0 when unknown: guest::sym would end the game)
        if (!fn) {
            LOGW("port_debug", "call: unknown symbol %s", parts[0].c_str());
            return;
        }
        GuestArgs a;
        for (size_t i = 1; i < parts.size(); i++) {
            const std::string& p = parts[i];
            if (p.rfind("s=", 0) == 0) a.i(guest_cstr(p.substr(2)));
            else if (p.rfind("f=", 0) == 0) a.f(strtof(p.c_str() + 2, nullptr));
            else a.i(strtoull(p.c_str(), nullptr, 0));
        }
        u64 r = guest_call(fn, a).x0;
        LOGI("port_debug", "call %s -> %#llx", parts[0].c_str(), (unsigned long long)r);
        return;
    }
}

}  // namespace

bool command(const std::string& cmd) {
    if (cmd.rfind("clock:+", 0) == 0) {
        int64_t n = strtoll(cmd.c_str() + 7, nullptr, 10);
        int64_t t = (server::clock_now() + n).v;
        server::set_server_clock(t);
        LOGI("port_debug", "clock +%lld s: the server clock is now %lld", (long long)n, (long long)t);
        return true;
    }
    if (cmd == "memstats" || cmd.rfind("memstats:", 0) == 0) {
        std::lock_guard lk(g_mutex);
        g_queue.push_back(cmd);
        return true;
    }
    if (cmd.rfind("phase:", 0) != 0 && cmd.rfind("call:", 0) != 0 && cmd.rfind("debugwin:", 0) != 0 &&
        cmd.rfind("mission:", 0) != 0 && cmd.rfind("uiset:", 0) != 0)
        return false;
    std::lock_guard lk(g_mutex);
    g_queue.push_back(cmd);
    return true;
}

void on_phase_progress(u64 phase_mgr) {
    // One log line per phase change, so scripts (control/flowctl.py wait-log) can wait on it.
    static u32 last = ~0u;
    u32 now = reinterpret_cast<const CPhase*>(phase_mgr)->m_present;
    if (now != last) {
        LOGI("port_debug", "phase %u (%#x)", now, now);
        last = now;
    }
    memstats::on_phase(now);
    std::deque<std::string> q;
    {
        std::lock_guard lk(g_mutex);
        q.swap(g_queue);
    }
    for (auto& c : q) run(c, reinterpret_cast<CPhase*>(phase_mgr));
    if (g_debugwin) {
        static u64 progress = guest::sym("_ZN9Framework13CDebugWindows8ProgressEf");
        GuestArgs a;
        a.f(1.0f / 30);
        guest_call(progress, a);
    }
}

}  // namespace soa::native::port_debug

// The control commands above and the "port_debug: phase N" log lines the scripts wait on run from
// this wrapper of CPhase::Progress: on_phase_progress at the start, then the original guest code.
// (Before the rebase's revision 2 the native CPhase::Progress of ui/screen called it.)
namespace soa::native::port_debug {
namespace {
u64 g_phase_progress_orig = 0;
void h_phase_progress(Cpu& c) {
    u64 self = c.x(0);
    on_phase_progress(self);
    guest_call(g_phase_progress_orig, {self});
}
NATIVE_PORT_FUNCTION_ORIG("_ZN6CPhase8ProgressEv", h_phase_progress, "port: CPhase::Progress wrapper (port_debug control commands, phase log)",
                     &g_phase_progress_orig);
}  // namespace
}  // namespace soa::native::port_debug
