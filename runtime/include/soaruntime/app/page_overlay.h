#pragma once
// A host-drawn image over the game (docs/webview.md "Drawing over the game"): one RGBA picture at a
// rectangle of the game's screen, drawn by the host loop over every presented frame (GfxHooks::
// draw_overlay, before a screenshot is taken, so `shot:` includes it), with the touches inside the
// rectangle given to its owner instead of the game. The web view prototype (the port's --webview:
// port/src/native/ui/webview_page_view.cpp) shows its pages with it, as Android's WebView sits over
// the game's surface in a PopupWindow and takes the touches in its area.
//
// Not drawn, no GL call and no input taken while nothing is shown, so the game's pixels and input
// are unchanged then. The picture is copied (blitted, linearly scaled) into the letterboxed game
// image, opaque: an Android WebView over the game is opaque too (a page paints its own background).
// The game keeps presenting frames while a web view is open (its CWebView::Progress runs each frame),
// so no idle presenting is needed (unlike the keyboard's text box, app/text_overlay).
#include <cstdint>
#include <functional>
#include <vector>

namespace soa::app::page_overlay {

// Shows `rgba` (w x h, top-down rows) at the game-screen rectangle (x, y, w_screen, h_screen) (game
// pixels: platform().width x height). Replaces what was shown. Any thread.
void show(int x, int y, int w_screen, int h_screen, int w, int h, std::vector<uint8_t> rgba);
// Removes the picture (and drops a gesture in progress). Any thread.
void hide();
bool visible();

// The owner's input, in game-screen pixels relative to the rectangle's top-left. kind: 0 down,
// 1 up, 2 move (a touch inside the rectangle and the gesture it starts), 3 the wheel (dy: + up).
// Runs on the host's main thread. Set before show(); nullptr = touches inside are swallowed.
using InputHandler = std::function<void(int kind, float x, float y, float dy)>;
void set_input_handler(InputHandler h);

// ---- the host loop's side (app/host.cpp)
// A touch (Android action 0 down, 1 up, 2 move) at game-screen (x, y): true when the picture takes it
// (a gesture that started inside it, to its end), false: the game's.
bool touch(int action, float x, float y);
// The mouse wheel at (x, y): true when over the picture.
bool wheel(float x, float y, float dy);
// Draws the picture (the render thread, from GfxHooks::draw_overlay): `target_fbo` stands for the
// window; (vx, vy, vw, vh) is the game image's viewport (GL, bottom-up y), (W, H) the game screen.
void draw(unsigned target_fbo, int vx, int vy, int vw, int vh, int W, int H);

}  // namespace soa::app::page_overlay
