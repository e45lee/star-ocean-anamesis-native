#pragma once
// Host-side objects behind the NDK opaque types handed to the guest.
#include <atomic>
#include <deque>
#include <memory>
#include <mutex>
#include <string>
#include <unordered_map>
#include <vector>

#include <soa/file_tree.h>

#include "android/zip.h"
#include "core/cpu.h"

namespace soa {

// ---- AAssetManager ----
class AssetManager {
public:
    // Adds an APK whose assets/ directory is merged into the asset namespace (later wins).
    bool add_apk(const std::string& path);
    struct Found {
        const ZipArchive* zip;
        const ZipArchive::Entry* entry;
    };
    bool find(const std::string& name, Found& out) const;
    std::vector<std::string> list_files(const std::string& dir) const;
    size_t file_count() const { return index_.size(); }

    // Port option (--download / --download-dir, off by default): the online game's downloadable
    // asset tree (Sound/, Parameter/, Motion/, ..., sqlite/), a folder or its zip read in place
    // (SOA-3.7.0-canonical-data.zip; soa/file_tree.h). A "builtin_data/<rel>" asset missing from
    // the APKs is served from <tree>/<rel>, as if the game's downloader had fetched it. With
    // `prefer` (--download-prefer) the tree wins over the APKs (e.g. to use the 3.7.0 master DB).
    // A folder is looked up on every open, so files that appear while the game runs are found.
    // False when `path` is neither a folder nor a zip.
    bool set_download_dir(const std::string& path, bool prefer);
    // Port option (--standin-assets; on by default with --server inproc): an
    // overlay of made-up stand-in files (standin-assets/<rel>, e.g. lost gacha banners) for
    // "builtin_data/<rel>" assets that neither the APKs nor the download dir have. Real assets
    // always win: the overlay is searched last.
    void set_standin_dir(const std::string& dir) { standin_dir_ = dir; }
    const std::string& standin_dir() const { return standin_dir_; }
    // <download>/<rel> for a "builtin_data/<rel>" asset name, if that file exists; else
    // <stand-in dir>/<rel> when the APKs don't have the asset either.
    struct Download {
        std::shared_ptr<const FileTree> tree;
        std::string rel;
        FileTree::Loc loc;  // where its bytes are (a host file's range; or not in place: tree->read)
    };
    bool find_download(const std::string& name, Download& out) const;
    bool download_prefer() const { return download_prefer_; }

private:
    std::shared_ptr<const FileTree> download_;
    std::string standin_dir_;
    bool download_prefer_ = false;

    std::vector<std::unique_ptr<ZipArchive>> zips_;
    std::unordered_map<std::string, Found> index_;  // path relative to assets/
};
AssetManager& asset_manager();

struct Asset {
    const u8* data = nullptr;
    std::vector<u8> owned;
    u64 size = 0, pos = 0;
};

// ---- ANativeWindow ----
struct NativeWindow {
    u32 magic = 0x5f776e64;  // "dnw_"
    int width = 0, height = 0;
    int format = 0;
    int buffer_width = 0, buffer_height = 0;  // ANativeWindow_setBuffersGeometry (0 = window size)
    void* host_window = nullptr;  // the frontend's window (app/host.cpp: the SDL_Window); opaque to the runtime
};
NativeWindow& native_window();

// ---- AInputEvent / AInputQueue ----
struct InputEvent {
    s32 type = 0;    // AINPUT_EVENT_TYPE_KEY=1 / MOTION=2
    s32 source = 0;  // AINPUT_SOURCE_*
    s32 action = 0;
    s32 keycode = 0;
    s32 meta = 0;
    s64 time_ns = 0;
    int pointer_count = 0;
    struct Pointer {
        s32 id;
        float x, y, pressure;
    } pointers[10];
};

class InputQueue {
public:
    InputQueue();
    // Returns the event's sequence number: the count of events pushed so far, this one included.
    u64 push(const InputEvent& e);
    bool pop(InputEvent*& out);
    int fd() const { return efd_; }
    // Events the guest has read (AInputQueue_getEvent) so far; event N has been read once this is
    // >= N (frontend/touch_script.h paces scripted taps by it).
    u64 consumed() const { return popped_.load(std::memory_order_acquire); }

private:
    std::mutex m_;
    std::deque<InputEvent*> q_;
    u64 pushed_ = 0;
    std::atomic<u64> popped_{0};
    int efd_;
};
InputQueue& input_queue();

// ---- AConfiguration ----
struct Configuration {
    char language[2] = {'j', 'a'};
    char country[2] = {'J', 'P'};
    s32 density = 480;
};

}  // namespace soa
