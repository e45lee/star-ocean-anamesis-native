// Repository resources (see paths.h).
#include "core/paths.h"

#include <sys/stat.h>

#include <soa/install.h>

#include "core/log.h"
#include "core/options.h"

namespace soa {

namespace {

bool exists(const std::string& p) {
    struct stat st;
    return !p.empty() && stat(p.c_str(), &st) == 0;
}

bool is_repo(const std::string& dir) { return exists(dir + "/port/CMakeLists.txt"); }

// The repo roots (common soa/install.h repo_roots: one rule for every program; a release build
// never searches for a checkout around it).
struct Roots {
    std::string root;
    std::vector<std::string> all;
    Roots() {
        install::RepoRoots r = install::repo_roots(options().repo_dir, is_repo);  // --repo
        if (!r.warning.empty()) LOGW("paths", "%s", r.warning.c_str());
        LOGI("paths", "%s", r.describe().c_str());
        root = r.root;
        all = r.all;
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
