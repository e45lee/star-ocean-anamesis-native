// Repository resources (see paths.h).
#include "core/paths.h"

#include <soa/install.h>

#include "soaruntime/core/log.h"
#include "core/options.h"

namespace soa {

namespace {

// The repo roots (common soa/install.h repo_roots: one rule for every program; a release build
// never searches for a checkout around it).
struct Roots {
    std::string root;
    std::vector<std::string> all;
    Roots() {
        install::RepoRoots r = install::repo_roots(options().repo_dir);  // --repo (install::is_checkout)
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

std::string find_repo_file(std::initializer_list<const char*> rels) { return install::find_file(repo_roots(), rels); }

std::string find_repo_file(const std::string& rel) { return find_repo_file({rel.c_str()}); }

std::vector<std::string> repo_files(std::initializer_list<const char*> rels) {
    std::vector<std::string> v;
    for (const char* rel : rels)
        if (std::string p = find_repo_file(rel); !p.empty()) v.push_back(p);
    return v;
}

}  // namespace soa
