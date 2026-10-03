#pragma once
// Host platform state shared between the frontend (SDL) and the fake Java side.
#include <atomic>
#include <functional>
#include <mutex>
#include <string>

namespace soa {

struct Platform {
    // Surface size reported to the game (Display.getRealSize etc.)
    std::atomic<int> width{1280}, height{720};

    // KeyboardActivity emulation (SOAActivity.StartKeyboardActivity / GetEditText).
    std::mutex text_mutex;
    std::atomic<bool> text_active{false};
    std::string text_value;     // result once finished
    std::string text_editing;   // in-progress text
    int text_max_len = 0;
    bool text_numeric = false;

    // MoviePlayerActivity emulation.
    std::atomic<bool> movie_playing{false};
    std::string movie_path;
    float movie_volume = 1.0f;
    bool movie_is_file = false;

    std::atomic<bool> quit_requested{false};
};

Platform& platform();

// Runs fn on the frontend's main ("UI") thread, like Activity.runOnUiThread / Task listeners.
void platform_post_ui(std::function<void()> fn);
void platform_run_ui_tasks();

// Play Asset Delivery packs available as split APKs (e.g. "assetfastfollow").
void platform_add_asset_pack(const std::string& name);
bool platform_has_asset_pack(const std::string& name);

// What the host program (its window/frontend) does for the Java side and the audio HLE. Unset
// hooks do nothing. Set them before the game starts (port/src/main.cpp sets all three).
struct HostHooks {
    std::function<void()> start_text_input;  // SOAActivity.StartKeyboardActivity: platform().text_* is set
    std::function<void()> play_movie;        // SOAActivity.PlayMovie: platform().movie_* is set
    std::function<void()> start_audio;       // the first OpenSL ES output mix is realized (hle/audio.h)
};
HostHooks& host_hooks();

// Call the hooks above.
void frontend_start_text_input();
void frontend_play_movie();

}  // namespace soa
