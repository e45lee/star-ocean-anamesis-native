#pragma once
// CUIUtility's resolution switches (ui_utility.cpp): the render size of the game's back buffer.
//
// CGame::OnColdStart (ELF 0x11414b0) builds the Aska description from the window's size:
//   - legacy (IsResolutionLegacy() true, as shipped): the UI screen (+0x68 / +0x6a of
//     tFrameworkArguments) is the window scaled to a long side of 1280 (720x1280 on a 9:16 screen),
//     and the back buffer (+0x78 / +0x7a), where the 3D scene is drawn, is that times
//     GetDefaultBackBufferScale() (0.75: 540x960); the UI is drawn at the screen's 720x1280;
//     CCocosDirector::ms_DisplayScale = 720 / the window's width.
//   - not legacy: the UI screen and the back buffer are the window's own size (ms_DisplayScale 1).
// OnColdStart is the only caller of both getters (tools/callers.py). docs/notes.md "Rendering",
// docs/client-changes.md "High-resolution rendering".
#include <cstddef>

namespace soa::native::ui {

// The port's resolution modes (soa --legacy-res, --render-scale S; the default: hi-res).
enum class Resolution {
    HiRes,     // default: IsResolutionLegacy() false: the back buffer is the game screen (--render-size)
    Scaled,    // --render-scale S: the legacy 720x1280 screen (the UI), the 3D at S x 720x1280
    Legacy,    // --legacy-res: no natives: the game as shipped (0.75)
};
// From options().client (legacy_res, render_scale).
Resolution resolution();

// Aska's CUIUtility (static members only; no object).
class CUIUtility {
public:
    // bool IsResolutionLegacy(): guest `return true`; native false (HiRes) or true (Scaled).
    static bool IsResolutionLegacy();
    // float GetDefaultBackBufferScale(): guest `return 0.75f`; native the --render-scale (Scaled only;
    // with HiRes OnColdStart never calls it, and it isn't replaced).
    static float GetDefaultBackBufferScale();
};

}  // namespace soa::native::ui
