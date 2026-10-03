// Repository resources (see paths.h).
#include "core/paths.h"

#include <limits.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#include "core/log.h"
#include "core/options.h"

namespace soa {

namespace {

bool exists(const std::string& p) {
    struct stat st;
    return !p.empty() && stat(p.c_str(), &st) == 0;
}

std::string real(const std::string& p) {
    char buf[PATH_MAX];
    return realpath(p.c_str(), buf) ? std::string(buf) : std::string();
}

std::string parent(const std::string& p) {
    size_t s = p.find_last_of('/');
    if (s == std::string::npos) return "";
    return s == 0 ? "/" : p.substr(0, s);
}

bool is_repo(const std::string& dir) { return exists(dir + "/port/CMakeLists.txt"); }

// The first directory from `dir` upwards that is a repo root.
std::string upwards(std::string dir) {
    while (!dir.empty()) {
        if (is_repo(dir)) return dir;
        if (dir == "/") break;
        dir = parent(dir);
    }
    return "";
}

struct Roots {
    std::string root;
    std::vector<std::string> all;
    Roots() {
        const std::string& o = options().repo_dir;  // --repo
        if (!o.empty()) {
            root = real(o);
            if (root.empty()) LOGW("paths", "--repo: %s not found", o.c_str());
        }
        const char* how = "--repo";
        if (root.empty()) {
            how = "the executable";
            std::string exe = real("/proc/self/exe");
            if (!exe.empty()) root = upwards(parent(exe));
        }
        if (root.empty()) {
            how = "the working directory";
            root = upwards(real("."));
        }
        if (root.empty()) {
            LOGW("paths", "the repository wasn't found (use --repo DIR); repo files are looked up in the working directory");
            return;
        }
        all.push_back(root);
        // A git worktree (.claude/worktrees/NAME) links work/ into the main checkout: search that too.
        struct stat st;
        if (lstat((root + "/work").c_str(), &st) == 0 && S_ISLNK(st.st_mode)) {
            std::string w = real(root + "/work");
            std::string main = w.empty() ? "" : parent(w);
            if (!main.empty() && main != root && is_repo(main)) all.push_back(main);
        }
        LOGI("paths", "repo %s (from %s)%s%s", root.c_str(), how, all.size() > 1 ? ", main checkout " : "",
             all.size() > 1 ? all[1].c_str() : "");
    }
};

const Roots& roots() {
    static Roots r;
    return r;
}

}  // namespace

const std::string& repo_root() { return roots().root; }
const std::vector<std::string>& repo_roots() { return roots().all; }

std::string repo_path(const std::string& rel) {
    const std::string& r = repo_root();
    return r.empty() ? rel : r + "/" + rel;
}

std::string find_repo_file(std::initializer_list<const char*> rels) {
    const auto& all = repo_roots();
    for (const char* rel : rels) {
        if (all.empty()) {
            if (exists(rel)) return rel;
            continue;
        }
        for (auto& r : all) {
            std::string p = r + "/" + rel;
            if (exists(p)) return p;
        }
    }
    return "";
}

std::string find_repo_file(const std::string& rel) { return find_repo_file({rel.c_str()}); }

std::vector<std::string> repo_files(std::initializer_list<const char*> rels) {
    std::vector<std::string> v;
    for (const char* rel : rels)
        if (std::string p = find_repo_file(rel); !p.empty()) v.push_back(p);
    return v;
}

}  // namespace soa
