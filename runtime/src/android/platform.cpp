// Host platform state (see platform.h). Moved from port/src/main.cpp; the frontend's actions are
// the host program's HostHooks.
#include "soaruntime/android/platform.h"

#include <algorithm>
#include <vector>

#include "hle/audio.h"

namespace soa {

Platform& platform() {
    static Platform p;
    return p;
}

HostHooks& host_hooks() {
    static HostHooks h;
    return h;
}

void frontend_start_text_input() {
    if (auto& f = host_hooks().start_text_input) f();
}
void frontend_play_movie() {
    if (auto& f = host_hooks().play_movie) f();
}
void audio_start_mixer() {
    if (auto& f = host_hooks().start_audio) f();
}

static std::mutex g_ui_mutex;
static std::vector<std::function<void()>> g_ui_tasks;
void platform_post_ui(std::function<void()> fn) {
    std::lock_guard lk(g_ui_mutex);
    g_ui_tasks.push_back(std::move(fn));
}
static std::mutex g_pack_mutex;
static std::vector<std::string> g_packs;
void platform_add_asset_pack(const std::string& name) {
    std::lock_guard lk(g_pack_mutex);
    g_packs.push_back(name);
}
bool platform_has_asset_pack(const std::string& name) {
    std::lock_guard lk(g_pack_mutex);
    return std::find(g_packs.begin(), g_packs.end(), name) != g_packs.end();
}

void platform_run_ui_tasks() {
    std::vector<std::function<void()>> tasks;
    {
        std::lock_guard lk(g_ui_mutex);
        tasks.swap(g_ui_tasks);
    }
    for (auto& t : tasks) t();
}

}  // namespace soa
