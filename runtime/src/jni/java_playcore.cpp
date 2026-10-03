// java.util collections and the Play Core (asset packs / tasks) API used by the game's
// statically linked Play Core native SDK. All assets ship in the install-time pack, so every
// query reports "nothing to download".
#include <vector>

#include "android/platform.h"
#include "core/log.h"
#include "core/vfs.h"
#include "jni/jvm.h"

namespace soa::jni {

namespace {

u64 R(Object* o) { return (u64)o; }

// ---- java.util ----
struct MapObj : Instance {
    std::vector<std::pair<Object*, Object*>> items;
};
struct Iter : Instance {
    std::vector<Object*> items;
    size_t pos = 0;
};

Iter* make_iter(Vm& vm, std::vector<Object*> items) {
    auto* it = new Iter();
    it->cls = vm.find_class("java/util/Iterator");
    it->items = std::move(items);
    return it;
}

// Task results are delivered to listeners on the "UI thread" (the frontend's main loop).
struct Task : Instance {
    Object* result = nullptr;
    bool success = true;
};

// ArrayList contents, keyed by instance (NewObject allocates plain Instances).
std::map<Object*, std::vector<Object*>> lists;
std::mutex lists_m;

std::vector<std::string> list_strings(u64 ref) {
    std::vector<std::string> out;
    std::lock_guard lk(lists_m);
    for (Object* o : lists[(Object*)ref]) out.push_back(o ? ((String*)o)->utf8 : "");
    return out;
}

}  // namespace

void install_playcore_classes(Vm& vm) {
    // java/util/ArrayList, List, Iterator, Map, Set
    vm.define_class("java/util/List");
    vm.define_class("java/util/ArrayList", "java/util/List");
    vm.define_class("java/util/Iterator");
    vm.define_class("java/util/Set");
    vm.define_class("java/util/Map");
    vm.define_class("java/util/HashMap", "java/util/Map");
    vm.define_class("java/util/Map$Entry");

    vm.def("java/util/ArrayList", "<init>", "()V", [](Object*, const Args&) -> u64 { return 0; });
    vm.def("java/util/List", "add", "(Ljava/lang/Object;)Z", [](Object* s, const Args& a) -> u64 {
        std::lock_guard lk(lists_m);
        lists[s].push_back((Object*)a[0]);
        return 1;
    });
    vm.def("java/util/List", "size", "()I", [](Object* s, const Args&) -> u64 {
        std::lock_guard lk(lists_m);
        return lists[s].size();
    });
    vm.def("java/util/List", "get", "(I)Ljava/lang/Object;", [](Object* s, const Args& a) -> u64 {
        std::lock_guard lk(lists_m);
        auto& v = lists[s];
        return (u32)a[0] < v.size() ? R(v[(u32)a[0]]) : 0;
    });
    auto list_items = [](Object* s) {
        std::lock_guard lk(lists_m);
        return lists[s];
    };
    vm.def("java/util/List", "iterator", "()Ljava/util/Iterator;", [&vm, list_items](Object* s, const Args&) -> u64 { return R(make_iter(vm, list_items(s))); });
    vm.def("java/util/Iterator", "hasNext", "()Z", [](Object* s, const Args&) -> u64 {
        auto* it = (Iter*)s;
        return it->pos < it->items.size();
    });
    vm.def("java/util/Iterator", "next", "()Ljava/lang/Object;", [](Object* s, const Args&) -> u64 {
        auto* it = (Iter*)s;
        return it->pos < it->items.size() ? R(it->items[it->pos++]) : 0;
    });
    vm.def("java/util/Map", "size", "()I", [](Object* s, const Args&) -> u64 { return ((MapObj*)s)->items.size(); });
    vm.def("java/util/Map", "entrySet", "()Ljava/util/Set;", [&vm](Object* s, const Args&) -> u64 {
        auto* set = vm.instance("java/util/Set");
        set->fields["map"] = R(s);
        return R(set);
    });
    vm.def("java/util/Map", "keySet", "()Ljava/util/Set;", [&vm](Object* s, const Args&) -> u64 {
        auto* set = vm.instance("java/util/Set");
        set->fields["map"] = R(s);
        set->fields["keys"] = 1;
        return R(set);
    });
    vm.def("java/util/Map", "get", "(Ljava/lang/Object;)Ljava/lang/Object;", [](Object* s, const Args& a) -> u64 {
        auto* key = (String*)a[0];
        for (auto& [k, v] : ((MapObj*)s)->items)
            if (k == key || (key && k && ((String*)k)->utf8 == key->utf8)) return R(v);
        return 0;
    });
    vm.def("java/util/Set", "iterator", "()Ljava/util/Iterator;", [&vm](Object* s, const Args&) -> u64 {
        auto* set = (Instance*)s;
        auto* m = (MapObj*)set->fields["map"];
        std::vector<Object*> items;
        for (auto& [k, v] : m->items) {
            if (set->fields["keys"]) {
                items.push_back(k);
            } else {
                auto* e = vm.instance("java/util/Map$Entry");
                e->fields["k"] = R(k);
                e->fields["v"] = R(v);
                items.push_back(e);
            }
        }
        return R(make_iter(vm, items));
    });
    vm.def("java/util/Map$Entry", "getKey", "()Ljava/lang/Object;", [](Object* s, const Args&) -> u64 { return ((Instance*)s)->fields["k"]; });
    vm.def("java/util/Map$Entry", "getValue", "()Ljava/lang/Object;", [](Object* s, const Args&) -> u64 { return ((Instance*)s)->fields["v"]; });

    // ---- Play Core tasks ----
    const std::string PC = "com/google/android/play/core/";
    vm.define_class(PC + "tasks/Task");
    vm.define_class(PC + "tasks/OnCompleteListener");
    vm.define_class(PC + "tasks/NativeOnCompleteListener", PC + "tasks/OnCompleteListener");
    vm.def(PC + "tasks/NativeOnCompleteListener", "<init>", "(JI)V", [](Object* s, const Args& a) -> u64 {
        ((Instance*)s)->fields["ctx"] = a[0];
        ((Instance*)s)->fields["type"] = a[1];
        return 0;
    });
    auto add_listener = [&vm, PC](Object* s, const Args& a) -> u64 {
        auto* task = (Task*)s;
        auto* l = (Instance*)a[a.size() - 1];
        if (!l) return R(s);
        platform_post_ui([&vm, task, l, PC]() {
            Method* m = vm.find_method(l->cls, "nativeOnComplete", "(JILjava/lang/Object;I)V", false);
            if (m && m->impl) {
                LOGD("playcore", "task complete -> nativeOnComplete(type=%d)", (int)l->fields["type"]);
                m->impl(l, {l->fields["ctx"], l->fields["type"], R(task->success ? task->result : nullptr), task->success ? 0u : (u64)-100});
            }
        });
        return R(s);
    };
    vm.def(PC + "tasks/Task", "addOnCompleteListener", "(L" + PC + "tasks/OnCompleteListener;)L" + PC + "tasks/Task;", add_listener);
    vm.def(PC + "tasks/Task", "addOnCompleteListener", "(Ljava/util/concurrent/Executor;L" + PC + "tasks/OnCompleteListener;)L" + PC + "tasks/Task;", add_listener);
    vm.def(PC + "tasks/Task", "isSuccessful", "()Z", [](Object* s, const Args&) -> u64 { return ((Task*)s)->success; });
    vm.def(PC + "tasks/Task", "isComplete", "()Z", [](Object*, const Args&) -> u64 { return 1; });
    vm.def(PC + "tasks/Task", "getResult", "()Ljava/lang/Object;", [](Object* s, const Args&) -> u64 { return R(((Task*)s)->result); });

    // ---- asset packs ----
    const std::string AP = PC + "assetpacks/";
    vm.define_class(AP + "AssetPackManager");
    vm.define_class(AP + "AssetPackStates");
    vm.define_class(AP + "AssetPackState");
    vm.define_class(AP + "AssetPackLocation");
    vm.define_class(AP + "AssetPackStateUpdateListener");
    vm.define_class(AP + "NativeAssetPackStateUpdateListener", AP + "AssetPackStateUpdateListener");
    vm.def(AP + "NativeAssetPackStateUpdateListener", "<init>", "()V", [](Object*, const Args&) -> u64 { return 0; });

    vm.def(AP + "AssetPackManagerFactory", "getInstance", "(Landroid/content/Context;)L" + AP + "AssetPackManager;",
           [&vm, AP](Object*, const Args&) -> u64 {
               static Instance* mgr = vm.instance(AP + "AssetPackManager");
               return R(mgr);
           },
           true);
    auto ok = [](Object*, const Args&) -> u64 { return 0; };
    vm.def(AP + "AssetPackManager", "registerListener", "(L" + AP + "AssetPackStateUpdateListener;)V", ok);
    vm.def(AP + "AssetPackManager", "unregisterListener", "(L" + AP + "AssetPackStateUpdateListener;)V", ok);
    // Packs whose split APK was found (see main.cpp) are installed like Play Core's
    // STORAGE_FILES packs: extracted to <files>/assetpacks/<name>/assets, which the game reads
    // with fopen as "<assetsPath>/assetpack/...".
    vm.def(AP + "AssetPackManager", "getPackLocation", "(Ljava/lang/String;)L" + AP + "AssetPackLocation;", [&vm, AP](Object*, const Args& a) -> u64 {
        std::string name = jstr(a[0]);
        if (!platform_has_asset_pack(name)) {
            LOGD("playcore", "getPackLocation(%s) -> not installed", name.c_str());
            return 0;
        }
        std::string path = guest_internal_dir() + "/assetpacks/" + name + "/assets";
        LOGI("playcore", "getPackLocation(%s) -> %s", name.c_str(), path.c_str());
        auto* loc = vm.instance(AP + "AssetPackLocation");
        loc->fields["assetsPath"] = R(vm.str(path));
        loc->fields["path"] = R(vm.str(guest_internal_dir() + "/assetpacks/" + name));
        return R(loc);
    });
    // AssetPackStates for a list of pack names, all reported NOT_INSTALLED with nothing to download.
    auto states_for = [&vm, AP](u64 list) {
        auto* map = new MapObj();
        map->cls = vm.find_class("java/util/Map");
        for (auto& name : list_strings(list)) {
            auto* st = vm.instance(AP + "AssetPackState");
            st->fields["name"] = R(vm.str(name));
            st->fields["status"] = platform_has_asset_pack(name) ? 4 : 8;  // COMPLETED / NOT_INSTALLED
            map->items.emplace_back(vm.str(name), st);
        }
        auto* states = vm.instance(AP + "AssetPackStates");
        states->fields["map"] = R(map);
        return states;
    };
    auto task_with = [&vm, PC](Object* result) {
        auto* t = new Task();
        t->cls = vm.find_class(PC + "tasks/Task");
        t->result = result;
        return t;
    };
    vm.def(AP + "AssetPackManager", "getPackStates", "(Ljava/util/List;)L" + PC + "tasks/Task;", [&vm, states_for, task_with](Object*, const Args& a) -> u64 {
        LOGD("playcore", "getPackStates");
        return R(task_with(states_for(a[0])));
    });
    vm.def(AP + "AssetPackManager", "fetch", "(Ljava/util/List;)L" + PC + "tasks/Task;", [&vm, states_for, task_with](Object*, const Args& a) -> u64 {
        for (auto& n : list_strings(a[0])) LOGW("playcore", "fetch(%s): no such asset pack in the offline build", n.c_str());
        return R(task_with(states_for(a[0])));
    });
    vm.def(AP + "AssetPackManager", "cancel", "(Ljava/util/List;)L" + AP + "AssetPackStates;", [&vm, states_for, task_with](Object*, const Args& a) -> u64 { return R(states_for(a[0])); });
    vm.def(AP + "AssetPackManager", "removePack", "(Ljava/lang/String;)L" + PC + "tasks/Task;", [&vm, states_for, task_with](Object*, const Args&) -> u64 { return R(task_with(nullptr)); });
    vm.def(AP + "AssetPackManager", "showCellularDataConfirmation", "(Landroid/app/Activity;)L" + PC + "tasks/Task;",
           [&vm, states_for, task_with](Object*, const Args&) -> u64 { return R(task_with(vm.integer(-1))); });
    vm.def(AP + "AssetPackStates", "packStates", "()Ljava/util/Map;", [](Object* s, const Args&) -> u64 { return ((Instance*)s)->fields["map"]; });
    vm.def(AP + "AssetPackStates", "totalBytes", "()J", [](Object*, const Args&) -> u64 { return 0; });
    vm.def(AP + "AssetPackState", "name", "()Ljava/lang/String;", [](Object* s, const Args&) -> u64 { return ((Instance*)s)->fields["name"]; });
    vm.def(AP + "AssetPackState", "status", "()I", [](Object* s, const Args&) -> u64 { return ((Instance*)s)->fields["status"]; });
    for (const char* n : {"errorCode", "transferProgressPercentage"}) vm.def(AP + "AssetPackState", n, "()I", ok);
    for (const char* n : {"bytesDownloaded", "totalBytesToDownload"}) vm.def(AP + "AssetPackState", n, "()J", ok);
    vm.def(AP + "AssetPackLocation", "packStorageMethod", "()I", [](Object*, const Args&) -> u64 { return 0; });  // STORAGE_FILES
    vm.def(AP + "AssetPackLocation", "assetsPath", "()Ljava/lang/String;", [](Object* s, const Args&) -> u64 { return ((Instance*)s)->fields["assetsPath"]; });
    vm.def(AP + "AssetPackLocation", "path", "()Ljava/lang/String;", [](Object* s, const Args&) -> u64 { return ((Instance*)s)->fields["path"]; });
}

}  // namespace soa::jni
