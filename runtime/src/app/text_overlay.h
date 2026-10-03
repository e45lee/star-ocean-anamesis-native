#pragma once
// The on-screen text box of the emulated KeyboardActivity (jni/java_android.cpp
// StartKeyboardActivity; the editing itself: frontend/text_entry.h, driven by app/host.cpp).
//
// While the game waits for its keyboard (platform().text_active) a semi-transparent panel is drawn
// at the bottom of the game's letterboxed image, in window space, over the presented frame
// (GfxHooks::draw_overlay, so screenshots include it):
//   row 1 (small): "Enter: OK   Esc: Cancel" (+ "Numbers only" for a numeric field), and the
//                  "n/max" counter on the right;
//   row 2: the field: the text, the IME's composition (underlined) at the cursor, a blinking caret,
//          scrolled horizontally to keep the caret visible.
// The game shows no new frames while its keyboard is open, so the host turns on idle presenting
// (hle/gfx.h) for the box to update as you type.
//
// Text is rendered with FreeType from a system font with Japanese glyphs, found at the first draw:
// HostConfig::font (--font: a path; "none" turns the box off), else the known paths of IPAex
// Gothic, Noto Sans CJK and Droid Sans Fallback, else `fc-match :lang=ja` (plus a fallback face from
// fc-match for the code points it lacks: Droid Sans Fallback has no Latin). Without one the box is
// not drawn and the window title alone shows the text (one log line says so).
//
// The panel is composed on the CPU into one premultiplied RGBA image, redrawn only when what it
// shows changes, uploaded to one texture and drawn as one blended quad on the presenting (game's)
// context, with all GL state it touches saved and restored. Nothing is drawn, and no GL call made,
// while text entry is inactive.
#include <string>

namespace soa::app::text_overlay {

// Rectangles in drawable pixels, top-left origin.
struct Rect {
    int x = 0, y = 0, w = 0, h = 0;
};
struct Layout {
    Rect panel;  // the whole box
    Rect field;  // the text field inside it (also the IME's candidate-window anchor)
    int font_px = 0, small_px = 0;
};

// The box's geometry for the game image at (vx, vy, vw, vh) (drawable pixels, GL bottom-up y, as
// GfxHooks::set_viewport_rect gets it) in a drawable of height dh. Font-free: the main thread uses
// it for SDL_SetTextInputRect, the render thread to draw.
Layout layout(int vx, int vy, int vw, int vh, int dh);

// The font: a path, "none" (no box), or "" (the search above). Set before the
// first draw (app::run, from HostConfig::font).
void set_font_request(const std::string& path);

// Draws the box over the frame being presented (the render thread, from GfxHooks::draw_overlay;
// `target_fbo` stands for the window, ww x wh its drawable size). No-op unless text entry is active.
void draw(int ww, int wh, unsigned target_fbo, int vx, int vy, int vw, int vh);

}  // namespace soa::app::text_overlay
