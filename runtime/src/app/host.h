#pragma once
// The desktop host loop: what a program running libSOA.so needs around the runtime to be an
// Android NativeActivity on a Linux desktop. SDL2 window and GLES contexts (X11 or Wayland; the
// guest's EGL is emulated over them: app/sdl_gl.h, hle/egl.cpp), presentation and screenshots,
// mouse/keyboard -> touch/key input (wheel = pinch), text entry (an on-screen box:
// app/text_overlay.h), the audio device (and the null sink), movies, the scripted/remote control commands (--do, --shot, --control FIFO:
// control/soactl.py), the ANativeActivity bring-up (JNI_OnLoad, onCreate and the start-up
// callbacks) and the main loop.
//
// Built as the separate target `soaruntime_app` (it links SDL2; the rest of the runtime
// doesn't). Used by the port (port/src/main.cpp) and the 3.7.0 emulator (emulator/src/main.cpp).
//
// Order (port/src/main.cpp is the reference):
//   app::install_host_hooks();              // host_hooks(): audio, text input, movies
//   ... vfs_init, cpu_global_init, hle_init, Vm::init, load_library, assets, run_initializers ...
//   app::start_watchdog();                  // optional: SOA_WATCHDOG
//   return app::run(*lib, cfg);             // window, activity, main loop; never returns
#include <functional>
#include <string>
#include <vector>

namespace soa {
struct LoadedLib;

namespace app {

struct HostConfig {
    std::string title = "STAR OCEAN -anamnesis-";  // window title (the fps is appended)
    int width = 0, height = 0;                      // window size; 0 = portrait 9:16 at 90% of the desktop height
    bool landscape = false;                         // default to a 16:9 landscape window instead
    bool fullscreen = false;                        // start in (desktop) fullscreen
    bool hidden = false;                            // don't show the window (it still renders: screenshots work)
    std::string render_size = "desktop";            // 'desktop', 'window' or WxH: the game's screen size
    std::string size_note;                          // appended to the "window ..." log line
    std::vector<std::string> shots;                 // "S:PATH": a screenshot S seconds after start
    std::vector<std::string> actions;               // "S:COMMAND": a control command S seconds after start
    std::string control_path;                       // read control commands from this FIFO (Windows: named pipe), or "tcp:HOST:PORT"
    std::string font;                               // the text box's font (app/text_overlay.h): a path,
                                                    // "none", or "" (a system CJK font)

    // Hooks (optional):
    // a control command the host loop doesn't know; return true when handled
    std::function<bool(const std::string& cmd)> command;
    // runs once per main-loop iteration, after the UI-thread tasks and input
    std::function<void()> tick;
};

// Sets host_hooks() (android/platform.h): start_audio (SDL audio device + the null sink),
// start_text_input, play_movie.
void install_host_hooks();

// SOA_WATCHDOG=SECONDS: once frames have started, if none is presented for that long, log it and
// print every guest thread's stack. No-op without the variable.
void start_watchdog();

// Opens the window, starts the activity (JNI_OnLoad, ANativeActivity_onCreate, onStart/onResume/
// window/input-queue/content-rect/focus callbacks), starts the control FIFO thread and runs the
// main loop until the game or the user quits; then profile_dump() and _exit(0).
[[noreturn]] void run(LoadedLib& lib, HostConfig& cfg);

}  // namespace app
}  // namespace soa
