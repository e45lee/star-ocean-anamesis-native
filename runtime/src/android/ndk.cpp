// NDK: ALooper, AInputQueue/AInputEvent, AAssetManager, AConfiguration, ANativeWindow, liblog.
#include "android/ndk.h"

#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

#include <algorithm>
#include <cinttypes>
#include <cstring>
#include <set>

#include "core/hle.h"
#include "core/host_fd.h"
#include "core/log.h"
#include "hle/format.h"

namespace soa {

// ===========================================================================
// AAssetManager

bool AssetManager::add_apk(const std::string& path) {
    auto z = std::make_unique<ZipArchive>();
    if (!z->open(path)) {
        LOGE("assets", "cannot open %s", path.c_str());
        return false;
    }
    return add_zip(std::move(z), path);
}

bool AssetManager::add_zip(std::unique_ptr<ZipArchive> z, const std::string& label) {
    if (!z) return false;
    size_t n = 0;
    for (auto& [name, e] : z->entries()) {
        if (name.compare(0, 7, "assets/") != 0 || name.back() == '/') continue;
        index_[name.substr(7)] = {z.get(), &e};
        n++;
    }
    LOGI("assets", "%s: %zu assets", label.c_str(), n);
    zips_.push_back(std::move(z));
    return true;
}

static std::string normalize(std::string p) {
    while (!p.empty() && p[0] == '/') p.erase(0, 1);
    std::string out;
    size_t i = 0;
    // collapse "./" and "//"
    while (i < p.size()) {
        if (p.compare(i, 2, "./") == 0) {
            i += 2;
            continue;
        }
        if (p[i] == '/' && !out.empty() && out.back() == '/') {
            i++;
            continue;
        }
        out.push_back(p[i++]);
    }
    return out;
}

bool AssetManager::find(const std::string& name, Found& out) const {
    auto it = index_.find(normalize(name));
    if (it == index_.end()) return false;
    out = it->second;
    return true;
}

static const char kBuiltinData[] = "builtin_data/";

namespace {
// <dir>/<rel> for a "builtin_data/<rel>" asset name, if that regular file exists.
bool find_under(const std::string& dir, const std::string& n, std::string& host) {
    if (dir.empty() || n.compare(0, sizeof(kBuiltinData) - 1, kBuiltinData) != 0) return false;
    std::string rel = n.substr(sizeof(kBuiltinData) - 1);
    if (rel.empty() || rel.find("..") != std::string::npos) return false;
    host = dir + "/" + rel;
    struct stat st;
    return stat(host.c_str(), &st) == 0 && S_ISREG(st.st_mode);
}
}  // namespace

bool AssetManager::find_download(const std::string& name, std::string& host) const {
    if (download_dir_.empty() && standin_dir_.empty()) return false;
    std::string n = normalize(name);
    if (find_under(download_dir_, n, host)) return true;
    // the stand-in overlay: only for assets no real source has
    return !standin_dir_.empty() && !index_.count(n) && find_under(standin_dir_, n, host);
}

std::vector<std::string> AssetManager::list_files(const std::string& dir) const {
    std::string d = normalize(dir);
    while (!d.empty() && d.back() == '/') d.pop_back();
    std::string prefix = d.empty() ? "" : d + "/";
    std::set<std::string> out;
    for (auto& [name, f] : index_) {
        if (name.compare(0, prefix.size(), prefix) != 0) continue;
        std::string rest = name.substr(prefix.size());
        if (rest.find('/') == std::string::npos) out.insert(rest);
    }
    // --download-dir / --standin-assets: merge the files of <dir>/<rel> for "builtin_data/<rel>"
    // (read now, not cached).
    for (const std::string* root : {&download_dir_, &standin_dir_})
        if (!root->empty() && prefix.compare(0, sizeof(kBuiltinData) - 1, kBuiltinData) == 0) {
            std::string host = *root + "/" + prefix.substr(sizeof(kBuiltinData) - 1);
            if (DIR* dh = opendir(host.c_str())) {
                while (dirent* e = readdir(dh)) {
#ifdef _WIN32  // (MinGW's dirent has no d_type)
                    struct stat st;
                    if (stat((host + "/" + e->d_name).c_str(), &st) == 0 && S_ISREG(st.st_mode)) out.insert(e->d_name);
#else
                    if (e->d_type == DT_REG) out.insert(e->d_name);
#endif
                }
                closedir(dh);
            }
        }
    return {out.begin(), out.end()};
}

AssetManager& asset_manager() {
    static AssetManager m;
    return m;
}

namespace {

struct AssetDir {
    std::vector<std::string> names;
    size_t idx = 0;
};

// --download-dir: an asset read from <download dir>/<rel>.
bool open_download(Cpu& c, const char* name, const std::string& host) {
    FILE* fp = fopen(host.c_str(), "rb");
    if (!fp) return false;
    auto* a = new Asset();
    fseek(fp, 0, SEEK_END);
    long n = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    a->owned.resize(n > 0 ? (size_t)n : 0);
    size_t got = n > 0 ? fread(a->owned.data(), 1, (size_t)n, fp) : 0;
    fclose(fp);
    if (got != a->owned.size()) {
        delete a;
        return false;
    }
    a->size = a->owned.size();
    a->data = a->owned.data();
    LOGD("assets", "open(%s) = %" PRIu64 " bytes from %s", name, a->size, host.c_str());
    ret_ptr(c, a);
    return true;
}

void th_AAssetManager_open(Cpu& c) {
    const char* name = arg_str(c, 1);
    auto& am = asset_manager();
    std::string host;
    if (am.download_prefer() && am.find_download(name, host) && open_download(c, name, host)) return;
    AssetManager::Found f;
    if (!am.find(name, f)) {
        if (!am.download_prefer() && am.find_download(name, host) && open_download(c, name, host)) return;
        LOGD("assets", "open(%s): not found", name);
        ret(c, 0);
        return;
    }
    auto* a = new Asset();
    a->size = f.entry->size;
    a->data = f.zip->stored_data(*f.entry);
    if (!a->data) {
        if (!f.zip->extract(*f.entry, a->owned)) {
            LOGE("assets", "failed to inflate %s", name);
            delete a;
            ret(c, 0);
            return;
        }
        a->data = a->owned.data();
    }
    LOGT("assets", "open(%s) = %" PRIu64 " bytes", name, a->size);
    ret_ptr(c, a);
}
void th_AAsset_close(Cpu& c) { delete (Asset*)c.x(0); }
void th_AAsset_getLength(Cpu& c) { ret(c, ((Asset*)c.x(0))->size); }
void th_AAsset_read(Cpu& c) {
    auto* a = (Asset*)c.x(0);
    u64 n = std::min<u64>(c.x(2), a->size - a->pos);
    memcpy((void*)c.x(1), a->data + a->pos, n);
    a->pos += n;
    ret(c, n);
}
void th_AAsset_seek(Cpu& c) {
    auto* a = (Asset*)c.x(0);
    s64 off = (s64)c.x(1);
    int whence = (int)c.x(2);
    s64 np = whence == SEEK_SET ? off : whence == SEEK_CUR ? (s64)a->pos + off : (s64)a->size + off;
    if (np < 0 || np > (s64)a->size) {
        ret(c, (u64)-1);
        return;
    }
    a->pos = np;
    ret(c, (u64)np);
}
void th_AAssetManager_openDir(Cpu& c) {
    auto* d = new AssetDir();
    d->names = asset_manager().list_files(arg_str(c, 1));
    LOGD("assets", "openDir(%s): %zu files", arg_str(c, 1), d->names.size());
    ret_ptr(c, d);
}
void th_AAssetDir_getNextFileName(Cpu& c) {
    auto* d = (AssetDir*)c.x(0);
    ret_ptr(c, d->idx < d->names.size() ? d->names[d->idx++].c_str() : nullptr);
}
void th_AAssetDir_close(Cpu& c) { delete (AssetDir*)c.x(0); }

// ===========================================================================
// AConfiguration

void th_AConfiguration_new(Cpu& c) { ret_ptr(c, new Configuration()); }
void th_AConfiguration_delete(Cpu& c) { delete (Configuration*)c.x(0); }
void th_AConfiguration_fromAssetManager(Cpu& c) { *(Configuration*)c.x(0) = Configuration(); }
void th_AConfiguration_getLanguage(Cpu& c) { memcpy((void*)c.x(1), ((Configuration*)c.x(0))->language, 2); }
void th_AConfiguration_getCountry(Cpu& c) { memcpy((void*)c.x(1), ((Configuration*)c.x(0))->country, 2); }
void th_AConfiguration_getDensity(Cpu& c) { ret(c, (u64)((Configuration*)c.x(0))->density); }

// ===========================================================================
// ANativeWindow

void th_ANativeWindow_getWidth(Cpu& c) {
    auto* w = (NativeWindow*)c.x(0);
    ret(c, (u64)(w->buffer_width ? w->buffer_width : w->width));
}
void th_ANativeWindow_getHeight(Cpu& c) {
    auto* w = (NativeWindow*)c.x(0);
    ret(c, (u64)(w->buffer_height ? w->buffer_height : w->height));
}
void th_ANativeWindow_setBuffersGeometry(Cpu& c) {
    auto* w = (NativeWindow*)c.x(0);
    LOGD("window", "setBuffersGeometry(%d, %d, fmt %d)", (int)c.x(1), (int)c.x(2), (int)c.x(3));
    w->format = (int)c.x(3);
    w->buffer_width = (int)c.x(1);
    w->buffer_height = (int)c.x(2);
    ret(c, 0);
}

// ===========================================================================
// ALooper

struct Looper {
    struct Fd {
        int fd, ident, events;
        u64 callback, data;
    };
    std::mutex m;
    std::vector<Fd> fds;
};
thread_local Looper* t_looper = nullptr;

void th_ALooper_prepare(Cpu& c) {
    if (!t_looper) t_looper = new Looper();
    ret_ptr(c, t_looper);
}
void th_ALooper_addFd(Cpu& c) {
    auto* l = (Looper*)c.x(0);
    Looper::Fd f{(int)c.x(1), (int)c.x(2), (int)c.x(3), c.x(4), c.x(5)};
    std::lock_guard lk(l->m);
    for (auto& e : l->fds)
        if (e.fd == f.fd) {
            e = f;
            ret(c, 1);
            return;
        }
    l->fds.push_back(f);
    ret(c, 1);
}
void looper_remove_fd(Looper* l, int fd) {
    std::lock_guard lk(l->m);
    l->fds.erase(std::remove_if(l->fds.begin(), l->fds.end(), [&](auto& e) { return e.fd == fd; }), l->fds.end());
}

void th_ALooper_pollAll(Cpu& c) {
    int timeout = (int)c.x(0);
    u64 out_fd = c.x(1), out_events = c.x(2), out_data = c.x(3);
    Looper* l = t_looper;
    if (!l) {
        ret(c, (u64)-4);
        return;
    }
    std::vector<Looper::Fd> fds;
    {
        std::lock_guard lk(l->m);
        fds = l->fds;
    }
    std::vector<hostfd::PollFd> pfd;
    for (auto& f : fds) pfd.push_back({f.fd, (short)((f.events & 1) ? hostfd::kIn : 0), 0});
    int r = hostfd::poll(pfd.data(), pfd.size(), timeout);
    if (r <= 0) {
        ret(c, (u64)(r == 0 ? -3 : -4));  // ALOOPER_POLL_TIMEOUT / ERROR
        return;
    }
    for (size_t i = 0; i < pfd.size(); i++) {
        if (!pfd[i].revents) continue;
        const auto& f = fds[i];
        int ev = ((pfd[i].revents & hostfd::kIn) ? 1 : 0) | ((pfd[i].revents & hostfd::kErr) ? 4 : 0) | ((pfd[i].revents & hostfd::kHup) ? 8 : 0);
        if (f.callback) {
            if (!guest_call(f.callback, {(u64)f.fd, (u64)ev, f.data})) looper_remove_fd(l, f.fd);
            ret(c, (u64)-2);  // ALOOPER_POLL_CALLBACK
            return;
        }
        if (out_fd) *(s32*)out_fd = f.fd;
        if (out_events) *(s32*)out_events = ev;
        if (out_data) *(u64*)out_data = f.data;
        ret(c, (u64)(s64)f.ident);
        return;
    }
    ret(c, (u64)-3);
}

// ===========================================================================
// AInputQueue / events

void th_AInputQueue_attachLooper(Cpu& c) {
    auto* q = (InputQueue*)c.x(0);
    auto* l = (Looper*)c.x(1);
    std::lock_guard lk(l->m);
    l->fds.push_back({q->fd(), (int)c.x(2), 1, c.x(3), c.x(4)});
}
void th_AInputQueue_detachLooper(Cpu& c) {
    // The looper isn't passed; detach from the calling thread's looper.
    if (t_looper) looper_remove_fd(t_looper, ((InputQueue*)c.x(0))->fd());
}
void th_AInputQueue_getEvent(Cpu& c) {
    InputEvent* e;
    if (((InputQueue*)c.x(0))->pop(e)) {
        *(u64*)c.x(1) = (u64)e;
        ret(c, 0);
    } else {
        ret(c, (u64)-1);
    }
}
void th_AInputQueue_preDispatchEvent(Cpu& c) { ret(c, 0); }
void th_AInputQueue_finishEvent(Cpu& c) { delete (InputEvent*)c.x(1); }

InputEvent* ev(Cpu& c) { return (InputEvent*)c.x(0); }
void th_AInputEvent_getType(Cpu& c) { ret(c, (u64)ev(c)->type); }
void th_AInputEvent_getSource(Cpu& c) { ret(c, (u64)ev(c)->source); }
void th_AKeyEvent_getKeyCode(Cpu& c) { ret(c, (u64)ev(c)->keycode); }
void th_AMotionEvent_getAction(Cpu& c) { ret(c, (u64)ev(c)->action); }
void th_AMotionEvent_getPointerCount(Cpu& c) { ret(c, (u64)ev(c)->pointer_count); }
void th_AMotionEvent_getPointerId(Cpu& c) {
    size_t i = c.x(1);
    ret(c, i < 10 ? (u64)ev(c)->pointers[i].id : 0);
}
void th_AMotionEvent_getX(Cpu& c) { c.set_s(0, c.x(1) < 10 ? ev(c)->pointers[c.x(1)].x : 0.f); }
void th_AMotionEvent_getY(Cpu& c) { c.set_s(0, c.x(1) < 10 ? ev(c)->pointers[c.x(1)].y : 0.f); }
void th_AMotionEvent_getPressure(Cpu& c) { c.set_s(0, c.x(1) < 10 ? ev(c)->pointers[c.x(1)].pressure : 0.f); }

// ===========================================================================
// liblog

void th_android_log_print(Cpu& c) {
    int prio = (int)c.x(0);
    const char* tag = arg_str(c, 1);
    RegVa va(c, 3);
    std::string s = guest_format(arg_str(c, 2), va);
    while (!s.empty() && s.back() == '\n') s.pop_back();
    LogLevel l = prio <= 3 ? LogLevel::Debug : prio == 4 ? LogLevel::Info : prio == 5 ? LogLevel::Warn : LogLevel::Error;
    if (l == LogLevel::Debug && g_log_level > LogLevel::Debug) return;
    log_write(l, tag ? tag : "guest", "%s", s.c_str());
    ret(c, s.size());
}

}  // namespace

// ===========================================================================

InputQueue::InputQueue() { efd_ = hostfd::make_event(); }

u64 InputQueue::push(const InputEvent& e) {
    std::lock_guard lk(m_);
    q_.push_back(new InputEvent(e));
    hostfd::event_signal(efd_);
    return ++pushed_;
}

bool InputQueue::pop(InputEvent*& out) {
    std::lock_guard lk(m_);
    if (q_.empty()) {
        hostfd::event_drain(efd_);
        return false;
    }
    out = q_.front();
    q_.pop_front();
    popped_.fetch_add(1, std::memory_order_release);
    if (q_.empty()) hostfd::event_drain(efd_);
    return true;
}

InputQueue& input_queue() {
    static InputQueue q;
    return q;
}

NativeWindow& native_window() {
    static NativeWindow w;
    return w;
}

void register_android(Hle& h) {
    h.fn("AAssetManager_open", th_AAssetManager_open);
    h.fn("AAssetManager_openDir", th_AAssetManager_openDir);
    h.fn("AAsset_close", th_AAsset_close);
    h.fn("AAsset_getLength", th_AAsset_getLength);
    h.fn("AAsset_read", th_AAsset_read);
    h.fn("AAsset_seek", th_AAsset_seek);
    h.fn("AAssetDir_getNextFileName", th_AAssetDir_getNextFileName);
    h.fn("AAssetDir_close", th_AAssetDir_close);
    h.fn("AConfiguration_new", th_AConfiguration_new);
    h.fn("AConfiguration_delete", th_AConfiguration_delete);
    h.fn("AConfiguration_fromAssetManager", th_AConfiguration_fromAssetManager);
    h.fn("AConfiguration_getLanguage", th_AConfiguration_getLanguage);
    h.fn("AConfiguration_getCountry", th_AConfiguration_getCountry);
    h.fn("AConfiguration_getDensity", th_AConfiguration_getDensity);
    h.fn("ANativeWindow_getWidth", th_ANativeWindow_getWidth);
    h.fn("ANativeWindow_getHeight", th_ANativeWindow_getHeight);
    h.fn("ANativeWindow_setBuffersGeometry", th_ANativeWindow_setBuffersGeometry);
    h.fn("ALooper_prepare", th_ALooper_prepare);
    h.fn("ALooper_addFd", th_ALooper_addFd);
    h.fn("ALooper_pollAll", th_ALooper_pollAll);
    h.fn("AInputQueue_attachLooper", th_AInputQueue_attachLooper);
    h.fn("AInputQueue_detachLooper", th_AInputQueue_detachLooper);
    h.fn("AInputQueue_getEvent", th_AInputQueue_getEvent);
    h.fn("AInputQueue_preDispatchEvent", th_AInputQueue_preDispatchEvent);
    h.fn("AInputQueue_finishEvent", th_AInputQueue_finishEvent);
    h.fn("AInputEvent_getType", th_AInputEvent_getType);
    h.fn("AInputEvent_getSource", th_AInputEvent_getSource);
    h.fn("AKeyEvent_getKeyCode", th_AKeyEvent_getKeyCode);
    h.fn("AMotionEvent_getAction", th_AMotionEvent_getAction);
    h.fn("AMotionEvent_getPointerCount", th_AMotionEvent_getPointerCount);
    h.fn("AMotionEvent_getPointerId", th_AMotionEvent_getPointerId);
    h.fn("AMotionEvent_getX", th_AMotionEvent_getX);
    h.fn("AMotionEvent_getY", th_AMotionEvent_getY);
    h.fn("AMotionEvent_getPressure", th_AMotionEvent_getPressure);
    h.fn("__android_log_print", th_android_log_print);
}

}  // namespace soa
