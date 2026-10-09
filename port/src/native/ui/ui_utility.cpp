// CUIUtility::IsResolutionLegacy / GetDefaultBackBufferScale: the port's high-resolution rendering
// (ui_utility.h; docs/client-changes.md "High-resolution rendering"; docs/notes.md "Rendering").
//
// As shipped both are constants (`return true`, `return 0.75f`, 8 bytes each: ELF 0x1de87b0 and
// 0x1de87f8), so on any 9:16 screen the game draws its UI at 720x1280 and its 3D scene into a
// 540x960 back buffer, and the frontend scales the result up. The port's default (hi-res) answers IsResolutionLegacy() false: the
// UI and the 3D are drawn at the game screen's size (--render-size; 728x1296 for a 729x1296 window).
// With --render-scale S it keeps the legacy 720x1280 screen (the UI) and answers S for the scale (the
// 3D at S x 720x1280, independent of the window); --legacy-res installs neither (the game as shipped).
// A behaviour change, not a bit-exact port: one of the port's own hooks, installed by predicate
// (NATIVE_PORT_FUNCTION_IF), so the selftest (no natives) and --natives none see the shipped values.
#include "native/ui/ui_utility.h"

#include "soaruntime/core/abi.h"
#include "soaruntime/core/cpu.h"
#include "soaruntime/core/log.h"
#include "core/options.h"
#include "native/common/native.h"
#include "native/common/test.h"

namespace soa::native::ui {

Resolution resolution() {
    const ClientOptions& c = options().client;
    if (c.legacy_res) return Resolution::Legacy;
    if (c.render_scale > 0) return Resolution::Scaled;
    return Resolution::HiRes;
}

bool CUIUtility::IsResolutionLegacy() {
    const bool legacy = resolution() != Resolution::HiRes;
    static bool logged = false;  // OnColdStart calls it once; log the first answer
    if (!logged) {
        logged = true;
        if (legacy)
            LOGI("ui", "resolution: the legacy 720x1280 layout, back buffer scale %.3g (--render-scale)", options().client.render_scale);
        else
            LOGI("ui", "resolution: hi-res: the back buffer is the game screen (--legacy-res for the game's 0.75)");
    }
    return legacy;
}

float CUIUtility::GetDefaultBackBufferScale() { return options().client.render_scale; }

namespace {
bool not_legacy() { return resolution() != Resolution::Legacy; }
bool scaled() { return resolution() == Resolution::Scaled; }
}  // namespace

NATIVE_PORT_FUNCTION_IF("_ZN10CUIUtility18IsResolutionLegacyEv", wrap<&CUIUtility::IsResolutionLegacy>(),
                   "ui: CUIUtility::IsResolutionLegacy: false (hi-res, the default) or true (--render-scale); not with --legacy-res",
                   not_legacy);
NATIVE_PORT_FUNCTION_IF("_ZN10CUIUtility25GetDefaultBackBufferScaleEv", wrap<&CUIUtility::GetDefaultBackBufferScale>(),
                   "ui: CUIUtility::GetDefaultBackBufferScale: the --render-scale (only with it)", scaled);

// ui/resolution: the guest originals are the shipped constants the natives replace (true, 0.75f;
// their code is the two 8-byte functions), and the natives answer for each mode. The effect on the
// back buffer is checked in a run: the log's "resolution:" and "default framebuffer" lines.
NATIVE_TEST("ui/resolution") {
    const u64 legacy_fn = t.sym("_ZN10CUIUtility18IsResolutionLegacyEv");
    const u64 scale_fn = t.sym("_ZN10CUIUtility25GetDefaultBackBufferScaleEv");
    t.expect_eq((u32)(guest_call(legacy_fn, {}) & 0xff), 1u, "guest IsResolutionLegacy()");
    t.expect_eq(guest_invoke<float>(scale_fn), 0.75f, "guest GetDefaultBackBufferScale()");
    // the shipped code: orr w0, wzr, #1; ret / fmov s0, #0.75; ret (8 bytes each, the native patch's size)
    const u32* l = (const u32*)legacy_fn;
    const u32* s = (const u32*)scale_fn;
    t.expect_eq(l[0], 0x320003e0u, "IsResolutionLegacy: orr w0, wzr, #1");
    t.expect_eq(l[1], 0xd65f03c0u, "IsResolutionLegacy: ret");
    t.expect_eq(s[0], 0x1e2d1000u, "GetDefaultBackBufferScale: fmov s0, #0.75");
    t.expect_eq(s[1], 0xd65f03c0u, "GetDefaultBackBufferScale: ret");

    RunOptions& o = mutable_options();
    const ClientOptions saved = o.client;
    o.client.legacy_res = false, o.client.render_scale = 0;
    t.expect_eq((int)resolution(), (int)Resolution::HiRes, "default mode");
    t.expect_eq(CUIUtility::IsResolutionLegacy(), false, "hi-res IsResolutionLegacy");
    o.client.render_scale = 1.5f;
    t.expect_eq((int)resolution(), (int)Resolution::Scaled, "--render-scale mode");
    t.expect_eq(CUIUtility::IsResolutionLegacy(), true, "--render-scale IsResolutionLegacy");
    t.expect_eq(CUIUtility::GetDefaultBackBufferScale(), 1.5f, "--render-scale 1.5");
    o.client.legacy_res = true, o.client.render_scale = 0;
    t.expect_eq((int)resolution(), (int)Resolution::Legacy, "--legacy-res mode");
    o.client = saved;
}

}  // namespace soa::native::ui
