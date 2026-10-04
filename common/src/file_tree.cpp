// A read-only tree of files, a folder or a ZIP archive (soa/file_tree.h).
#include "soa/file_tree.h"

#include <sys/stat.h>

#include <algorithm>
#include <cstdio>
#include <filesystem>
#include <system_error>

#include "soa/zip.h"

namespace soa {

namespace fs = std::filesystem;

namespace {
bool safe_rel(const std::string& rel) {
    return !rel.empty() && rel[0] != '/' && rel.find("..") == std::string::npos && rel.find('\\') == std::string::npos;
}
int64_t mtime_of(const std::string& p) {
    struct stat st;
    return stat(p.c_str(), &st) == 0 ? (int64_t)st.st_mtime : 0;
}
}  // namespace

FileTree::~FileTree() = default;

std::shared_ptr<const FileTree> FileTree::open(const std::string& path, std::string* err) {
    std::shared_ptr<FileTree> t(new FileTree());
    t->path_ = path;
    while (t->path_.size() > 1 && t->path_.back() == '/') t->path_.pop_back();
    std::error_code ec;
    if (fs::is_directory(fs::path(t->path_), ec)) return t;
    if (!fs::is_regular_file(fs::path(t->path_), ec)) {
        if (err) *err = path + ": not found";
        return nullptr;
    }
    t->zip_ = std::make_unique<ZipArchive>();
    if (!t->zip_->open(t->path_)) {
        if (err) *err = path + ": neither a folder nor a zip";
        return nullptr;
    }
    t->mtime_ = mtime_of(t->path_);
    std::vector<std::string> all;
    for (auto& [name, e] : t->zip_->entries())
        if (!name.empty() && name.back() != '/') all.push_back(name);
    std::sort(all.begin(), all.end());
    // one top-level folder holding everything: read the tree from inside it
    if (!all.empty()) {
        size_t s = all[0].find('/');
        std::string top = s == std::string::npos ? "" : all[0].substr(0, s + 1);
        if (!top.empty() && std::all_of(all.begin(), all.end(), [&](const std::string& n) { return n.compare(0, top.size(), top) == 0; }))
            t->prefix_ = top;
    }
    for (auto& n : all) t->names_.push_back(n.substr(t->prefix_.size()));
    return t;
}

bool FileTree::locate(const std::string& rel, Loc* out) const {
    if (!safe_rel(rel)) return false;
    if (!zip_) {
        std::string p = path_ + "/" + rel;
        struct stat st;
        if (stat(p.c_str(), &st) != 0 || !S_ISREG(st.st_mode)) return false;
        if (out) *out = Loc{p, 0, (uint64_t)st.st_size, true, (int64_t)st.st_mtime};
        return true;
    }
    const ZipArchive::Entry* e = zip_->find(prefix_ + rel);
    if (!e || (!rel.empty() && rel.back() == '/')) return false;
    if (out) {
        out->file = zip_->path();
        out->size = e->size;
        out->in_place = e->method == 0 && e->comp_size == e->size;
        out->offset = out->in_place ? zip_->data_offset_of(*e) : 0;
        out->mtime = mtime_;
    }
    return true;
}

bool FileTree::is_dir(const std::string& rel) const {
    if (!zip_) {
        std::error_code ec;
        return fs::is_directory(fs::path(rel.empty() ? path_ : path_ + "/" + rel), ec);
    }
    if (rel.empty()) return true;
    std::string d = rel.back() == '/' ? rel : rel + "/";
    auto it = std::lower_bound(names_.begin(), names_.end(), d);
    return it != names_.end() && it->compare(0, d.size(), d) == 0;
}

bool FileTree::read(const std::string& rel, std::vector<uint8_t>& out) const {
    if (!safe_rel(rel)) return false;
    if (zip_) {
        const ZipArchive::Entry* e = zip_->find(prefix_ + rel);
        return e && zip_->extract(*e, out);
    }
    FILE* f = fopen((path_ + "/" + rel).c_str(), "rb");
    if (!f) return false;
    out.clear();
    uint8_t buf[1 << 16];
    size_t n;
    while ((n = fread(buf, 1, sizeof buf, f)) > 0) out.insert(out.end(), buf, buf + n);
    bool ok = !ferror(f);
    fclose(f);
    return ok;
}

std::vector<std::string> FileTree::files(const std::string& dir) const {
    std::string d = dir.empty() || dir.back() == '/' ? dir : dir + "/";
    std::vector<std::string> v;
    if (zip_) {
        for (auto it = std::lower_bound(names_.begin(), names_.end(), d); it != names_.end() && it->compare(0, d.size(), d) == 0; ++it)
            v.push_back(*it);
        return v;
    }
    std::error_code ec;
    fs::path root(path_);
    for (fs::recursive_directory_iterator it(d.empty() ? root : root / d, ec), end; !ec && it != end; it.increment(ec))
        if (it->is_regular_file(ec)) v.push_back(fs::relative(it->path(), root, ec).generic_string());
    std::sort(v.begin(), v.end());
    return v;
}

std::vector<std::string> FileTree::list(const std::string& dir) const {
    std::string d = dir.empty() || dir.back() == '/' ? dir : dir + "/";
    std::vector<std::string> v;
    if (zip_) {
        for (auto it = std::lower_bound(names_.begin(), names_.end(), d); it != names_.end() && it->compare(0, d.size(), d) == 0; ++it)
            if (it->find('/', d.size()) == std::string::npos) v.push_back(it->substr(d.size()));
        return v;
    }
    std::error_code ec;
    for (fs::directory_iterator it(fs::path(path_ + "/" + d), ec), end; !ec && it != end; it.increment(ec))
        if (it->is_regular_file(ec)) v.push_back(it->path().filename().string());
    std::sort(v.begin(), v.end());
    return v;
}

bool is_download_tree(const FileTree& t) {
    return t.exists("version.bin") && t.is_dir("manifest") && t.exists("sqlite/basmaster.sqlite3");
}

}  // namespace soa
