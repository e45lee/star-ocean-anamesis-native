// soa-server's CDN tree (soaserver/cdn.h Tree): built from the 3.7.0 download (Tree::build, in the
// steps of TreeBuilder), then answered by URL path (Tree::lookup). The served master is
// served_master.cpp's, the bundles bundle.cpp's. Our code; what the 3.7.0 client expects is
// labelled (b) client evidence, the rest (d) assumption (docs/server-rules.md#cdn).
#include <unistd.h>

#include <algorithm>
#include <atomic>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <set>
#include <sstream>
#include <thread>
#include <tuple>

#include "cdn/files.h"
#include "core/log.h"
#include "soaserver/adld.h"
#include "soaserver/cdn.h"
#include "soaserver/chash32.h"
#include "soaserver/config.h"
#include "soaserver/server.h"

namespace soa::server::cdn {

using files::kMasterName;
using files::map_find;
using files::read_file;
using files::stat_file;
using files::write_file;

namespace {

constexpr const char* kLayoutTag = "isf1";  // bump when the bundle layout changes (hash cache key)
const char* const kManifests[] = {"Bulk", "Individual", "ep1", "ep2", "ep3"};
// The stand-ins' bundles (d): one each in Individual, all in one in Bulk; "5374616e" = "Stan".
constexpr const char* kStandinIndividualFormat = "I/5374616e/%08x.bin";
constexpr const char* kStandinBulk = "B/5374616e/standins.bin";
constexpr uint64_t kAdldHeaderSize = 16;  // (b) the stored asset's ADLD header, not in the bundle

// The bundle-hash cache: "<bundle>\t<fingerprint>\t<size>\t<sha1>" lines.
std::string fingerprint(const std::vector<Member>& members) {
    files::Sha1 h;
    h.add(kLayoutTag, strlen(kLayoutTag));
    for (auto& m : members) {
        uint64_t size = 0;
        int64_t mtime = 0;
        if (!m.mem) stat_file(m.file, &size, &mtime);
        std::string s = m.name + "|" + std::to_string(m.enc) + "|" + m.file + "|" + std::to_string(m.skip) + "|" + std::to_string(m.len) + "|" +
                        std::to_string(size) + "|" + std::to_string(mtime) + "|" + (m.mem ? sha1_hex(m.mem->data(), m.mem->size()) : "") + "\n";
        h.add(s.data(), s.size());
    }
    return h.hex();
}

// A derived 32-hex version id (the manifests' ids are 32 hex digits, b).
std::string derive_id(const std::string& orig, const std::string& salt) {
    std::string s = orig + "|" + salt;
    return sha1_hex((const uint8_t*)s.data(), s.size()).substr(0, 32);
}

std::string content_type(const std::string& name) {
    if (name.size() > 8 && name.compare(name.size() - 8, 8, ".version") == 0) return "text/plain";
    return "application/octet-stream";
}

// "a/b/../c" and friends are refused; "%xx" decoded.
bool clean_path(std::string path, std::string& out) {
    size_t q = path.find_first_of("?#");
    if (q != std::string::npos) path.resize(q);
    std::string decoded;
    for (size_t i = 0; i < path.size(); i++) {
        if (path[i] == '%' && i + 2 < path.size() && isxdigit((unsigned char)path[i + 1]) && isxdigit((unsigned char)path[i + 2])) {
            decoded += (char)strtol(path.substr(i + 1, 2).c_str(), nullptr, 16);
            i += 2;
        } else decoded += path[i];
    }
    std::string clean;
    std::stringstream ss(decoded);
    std::string seg;
    while (std::getline(ss, seg, '/')) {
        if (seg.empty() || seg == ".") continue;
        if (seg == ".." || seg.find('\0') != std::string::npos) return false;
        if (!clean.empty()) clean += '/';
        clean += seg;
    }
    out = clean;
    return true;
}

}  // namespace

// ---- the tree's build, step by step ---------------------------------------------------------------
// Tree::build's state between its steps (a friend of Tree: it fills the tree's members).
struct TreeBuilder {
    // A stand-in asset (opts.standins): a new member of its own bundles.
    struct Standin {
        std::string name, file, sha;
        uint32_t enc;
        uint64_t disk, plain;
    };
    // One manifest of manifest/<format>/ (kManifests).
    struct Manifest {
        std::string name;
        Value v;
        bool shared_id = false;  // carries version.bin's id (Bulk, Individual)
    };

    const Options& opts;
    std::string* err;
    std::shared_ptr<Tree> t;
    const std::string& mirror;
    std::string manifest_dir, scratch;
    int64_t now = 0;
    Value *assets = nullptr, *revision = nullptr, *version_id = nullptr;  // version.bin's entries
    std::string master_sha1, master_path;                               // the served master: plaintext SHA-1, ADLD file
    uint64_t master_plain_size = 0;
    std::vector<Standin> standins;
    std::vector<Manifest> manifests;
    size_t missing = 0;

    TreeBuilder(const Options& opts_, std::string* err_) : opts(opts_), err(err_), t(new Tree()), mirror(opts_.mirror) {
        t->opts_ = opts_;
        manifest_dir = "manifest/" + opts_.format;
    }

    std::shared_ptr<Tree> fail(const std::string& why) {
        LOGE("cdn", "%s", why.c_str());
        if (err) *err = why;
        return nullptr;
    }

    std::shared_ptr<Tree> build() {
        if (!read_version_bin()) return nullptr;
        scratch = opts.scratch.empty() ? "/tmp/soa-server-cdn" : opts.scratch;
        files::mkdirs(scratch);
        now = opts.now ? opts.now : files::server_time();
        if (!serve_master()) return nullptr;
        add_standins();
        if (!read_manifests()) return nullptr;
        for (auto& manifest : manifests) collect_bundles(manifest);
        hash_bundles();
        renew_ids();
        write_version_bin();
        LOGI("cdn", "%s", t->summary().c_str());
        return t;
    }

    // 0. version.bin of the download: its assets, revision and version id.
    bool read_version_bin() {
        std::vector<uint8_t> raw;
        if (!read_file(mirror + "/version.bin", raw)) return (bool)fail("cdn: no version.bin in " + mirror);
        t->version_ = mp_decode(raw);
        assets = map_find(t->version_, "assets");
        revision = map_find(t->version_, "revision");
        version_id = map_find(t->version_, "version");
        if (!assets || assets->type != Value::Map || !revision || revision->type != Value::Str || !version_id)
            return (bool)fail("cdn: " + mirror + "/version.bin: not a version file");
        return true;
    }

    // 1. the served master (b: version.bin's master entry: md5 = SHA-1 of the plaintext, size =
    // the ADLD file's size, encType 2; the manifests' member: size = the plaintext's size).
    bool serve_master() {
        master_path = scratch + "/basmaster-served.adld";
        std::vector<uint8_t> enc =
            make_served_master(opts.master, scratch + "/basmaster-served.sqlite3", opts.overrides, now, &master_sha1, &master_plain_size);
        if (enc.empty()) return (bool)fail("cdn: cannot prepare the master from " + opts.master);
        if (!write_file(master_path, enc.data(), enc.size())) return (bool)fail("cdn: cannot write " + master_path);
        t->overlay_[kMasterName] = master_path;
        LOGI("cdn", "master: %s -> %s (%llu bytes, plaintext SHA-1 %s)", opts.master.c_str(), master_path.c_str(), (unsigned long long)enc.size(),
             master_sha1.c_str());
        return true;
    }

    // 2. the stand-ins (d: new members of their own bundles; a real asset of the same name wins).
    void add_standins() {
        std::set<std::string> known;
        for (auto& entry : assets->map) known.insert(entry.first);
        if (opts.standins.empty()) return;
        std::vector<std::string> names;
        files::walk(opts.standins, "", names);
        for (auto& rel : names) {
            if (known.count(rel)) {
                LOGI("cdn", "stand-in %s: the download has it; not added", rel.c_str());
                continue;
            }
            std::vector<uint8_t> data;
            if (!read_file(opts.standins + "/" + rel, data)) continue;
            uint32_t enc = adld::flags_of(data.data(), data.size());
            if (enc != 0 && enc != adld::kXor && enc != adld::kAes) continue;
            std::vector<uint8_t> plain = adld::decrypt(rel, data);
            standins.push_back({rel, opts.standins + "/" + rel, sha1_hex(plain.data(), plain.size()), enc, data.size(), plain.size()});
            t->overlay_[rel] = opts.standins + "/" + rel;
        }
        t->standins_ = standins.size();
    }

    // 3a. the manifests of the served format.
    bool read_manifests() {
        std::vector<uint8_t> raw;
        for (const char* name : kManifests) {
            std::string path = mirror + "/" + manifest_dir + "/version_latest_" + name + ".bin";
            if (!read_file(path, raw)) continue;
            Manifest manifest{name, mp_decode(raw)};
            Value* manifest_assets = map_find(manifest.v, "assets");
            Value* id = map_find(manifest.v, "version");
            if (!manifest_assets || manifest_assets->type != Value::Map) return (bool)fail("cdn: " + path + ": no assets");
            manifest.shared_id = id && id->type == Value::Str && version_id->type == Value::Str && id->s == version_id->s;
            manifests.push_back(std::move(manifest));
        }
        if (manifests.empty()) return (bool)fail("cdn: no manifests in " + mirror + "/" + manifest_dir);
        return true;
    }

    // A member's payload: the overlay's file (the served master, a stand-in) or the download's,
    // (b) minus its 16-byte ADLD header when "e" is set, the whole file otherwise.
    bool member_of(const std::string& name, uint32_t enc, Member& member) {
        member = Member{};
        member.name = name;
        member.enc = enc;
        auto overlay = t->overlay_.find(name);
        member.file = overlay != t->overlay_.end() ? overlay->second : mirror + "/" + name;
        uint64_t size = 0;
        if (!stat_file(member.file, &size)) return false;
        member.skip = enc ? kAdldHeaderSize : 0;
        if (size < member.skip) return false;
        member.len = size - member.skip;
        return true;
    }

    // 3b. every bundle's members from the download; the master's member gets the served master's
    // size and SHA-1; then the stand-in bundles of this manifest.
    void collect_bundles(Manifest& manifest) {
        Value& manifest_assets = *map_find(manifest.v, "assets");
        for (auto& bundle_entry : manifest_assets.map) {
            Tree::Bundle bundle;
            for (auto& member_entry : bundle_entry.second.map) {
                if (member_entry.second.type != Value::Map) continue;
                Value* e = map_find(member_entry.second, "e");
                uint32_t enc = e ? (uint32_t)e->u : 0;
                Member member;
                if (!member_of(member_entry.first, enc, member)) {
                    missing++;
                    LOGW("cdn", "%s: %s: member %s missing from the download", manifest.name.c_str(), bundle_entry.first.c_str(),
                         member_entry.first.c_str());
                    continue;
                }
                if (member_entry.first == kMasterName) {
                    member_entry.second["size"] = Value((unsigned long long)master_plain_size);
                    member_entry.second["md5"] = Value(master_sha1);
                }
                bundle.members.push_back(std::move(member));
                t->member_bundle_[manifest.name][member_entry.first] = bundle_entry.first;
            }
            t->bundles_[bundle_entry.first] = std::move(bundle);
        }
        if (!standins.empty() && manifest.name == "Individual")
            for (auto& standin : standins) {
                char name[64];
                snprintf(name, sizeof name, kStandinIndividualFormat, chash32(standin.name.c_str()));
                add_standin_bundle(manifest, manifest_assets, name, {&standin});
            }
        if (!standins.empty() && manifest.name == "Bulk") {
            std::vector<const Standin*> all;
            for (auto& standin : standins) all.push_back(&standin);
            add_standin_bundle(manifest, manifest_assets, kStandinBulk, all);
        }
    }
    void add_standin_bundle(Manifest& manifest, Value& manifest_assets, const std::string& bundle_name, const std::vector<const Standin*>& list) {
        Value bundle_value = Value::object();
        Tree::Bundle bundle;
        std::string path = bundle_name.substr(0, bundle_name.size() - 4);
        for (const Standin* standin : list) {
            Value member_value = Value::object();
            member_value["size"] = Value((unsigned long long)standin->plain);
            member_value["md5"] = Value(standin->sha);
            member_value["meta"] = Value::array();
            member_value["p"] = Value(path);
            member_value["e"] = Value(standin->enc);
            member_value["ep_data"] = Value("");
            bundle_value[standin->name] = member_value;
            Member member;
            member_of(standin->name, standin->enc, member);
            bundle.members.push_back(member);
            t->member_bundle_[manifest.name][standin->name] = bundle_name;
        }
        bundle_value["md5"] = Value("");
        bundle_value["size"] = Value(0u);
        bundle_value["meta"] = Value::array();
        manifest_assets.map.emplace_back(bundle_name, bundle_value);
        t->bundles_[bundle_name] = std::move(bundle);
    }

    // 4. the bundle hashes (threads; cached by fingerprint in <scratch>/cdn-bundles.cache).
    void hash_bundles() {
        std::string cache_path = scratch + "/cdn-bundles.cache";
        std::map<std::string, std::tuple<std::string, uint64_t, std::string>> cache;  // bundle -> (fingerprint, size, sha1)
        if (opts.hash_cache) {
            std::ifstream in(cache_path);
            std::string line;
            while (std::getline(in, line)) {
                std::stringstream ss(line);
                std::string bundle, fp, size, sha;
                if (std::getline(ss, bundle, '\t') && std::getline(ss, fp, '\t') && std::getline(ss, size, '\t') && std::getline(ss, sha, '\t'))
                    cache[bundle] = {fp, strtoull(size.c_str(), nullptr, 10), sha};
            }
        }
        std::vector<std::pair<const std::string*, Tree::Bundle*>> work;
        size_t reused = 0;
        for (auto& [name, bundle] : t->bundles_) {
            std::string fp = fingerprint(bundle.members);
            auto cached = cache.find(name);
            bundle.size = bundle_size(bundle.members);
            if (cached != cache.end() && std::get<0>(cached->second) == fp && std::get<1>(cached->second) == bundle.size) {
                bundle.sha1 = std::get<2>(cached->second);
                reused++;
            } else work.push_back({&name, &bundle});
            cache[name] = {fp, bundle.size, ""};
        }
        {
            std::atomic<size_t> next{0};
            std::atomic<size_t> bad{0};
            int n = opts.threads > 0 ? opts.threads : (int)std::min<unsigned>(8, std::max(1u, std::thread::hardware_concurrency()));
            std::vector<std::thread> pool;
            for (int k = 0; k < n; k++)
                pool.emplace_back([&] {
                    for (size_t i; (i = next++) < work.size();) {
                        work[i].second->sha1 = bundle_sha1(work[i].second->members);
                        if (work[i].second->sha1.empty()) bad++;
                    }
                });
            for (auto& thread : pool) thread.join();
            if (bad) LOGW("cdn", "%zu bundles could not be read", (size_t)bad);
        }
        LOGI("cdn", "bundles: %zu (%zu hashed, %zu from the cache), %zu members missing", t->bundles_.size(), work.size(), reused, missing);
        if (opts.hash_cache) {
            std::string out;
            for (auto& [name, bundle] : t->bundles_)
                out += name + "\t" + std::get<0>(cache[name]) + "\t" + std::to_string(bundle.size) + "\t" + bundle.sha1 + "\n";
            write_file(cache_path, (const uint8_t*)out.data(), out.size());
        }
    }

    // 5. new ids and revision (b: the client fetches version.bin and the manifests again when
    // Login's r_ver differs from the revision it saw; d: the ids only need to differ); each
    // manifest's .bin and .version with the bundles' new md5 / size.
    void renew_ids() {
        uint64_t old_revision = strtoull(revision->s.c_str(), nullptr, 10);
        t->revision_ = std::to_string(old_revision + 1);
        std::string all_shas;
        for (auto& [name, bundle] : t->bundles_) all_shas += bundle.sha1;
        std::string salt = t->revision_ + "|" + sha1_hex((const uint8_t*)all_shas.data(), all_shas.size());
        std::string orig_version_id = version_id->type == Value::Str ? version_id->s : "";
        t->version_id_ = derive_id(orig_version_id, salt);
        for (auto& manifest : manifests) {
            Value& manifest_assets = *map_find(manifest.v, "assets");
            uint64_t total = 0;
            for (auto& bundle_entry : manifest_assets.map) {
                auto& bundle = t->bundles_[bundle_entry.first];
                if (!bundle.sha1.empty()) {
                    bundle_entry.second["md5"] = Value(bundle.sha1);
                    bundle_entry.second["size"] = Value((unsigned long long)bundle.size);
                }
                for (auto& member_entry : bundle_entry.second.map)
                    if (member_entry.second.type == Value::Map)
                        if (Value* size = map_find(member_entry.second, "size")) total += size->u;
            }
            Value* id = map_find(manifest.v, "version");
            std::string new_id = manifest.shared_id ? t->version_id_ : derive_id(id && id->type == Value::Str ? id->s : manifest.name, salt);
            if (id) *id = Value(new_id);
            std::string base = manifest_dir + "/version_latest_" + manifest.name;
            t->files_[base + ".bin"] = mp_encode(manifest.v);
            // (b) "version:<id>\r\ntotalSize:<the members' sizes>\r\n", as the 3.7.0 files
            std::string version = "version:" + new_id + "\r\ntotalSize:" + std::to_string(total) + "\r\n";
            t->files_[base + ".version"] = std::vector<uint8_t>(version.begin(), version.end());
        }
        t->files_[manifest_dir + "/version.version"] = std::vector<uint8_t>(t->version_id_.begin(), t->version_id_.end());
    }

    // 6. version.bin: the revision, the id, the master's entry, the bundles' own entries (b: the
    // Individual bundles it lists carry the bundle's md5), the stand-ins.
    void write_version_bin() {
        *revision = Value(t->revision_);
        *version_id = Value(t->version_id_);
        for (auto& entry : assets->map) {
            if (entry.second.type != Value::Map) continue;
            if (entry.first == kMasterName) {
                uint64_t enc_size = 0;
                stat_file(master_path, &enc_size);
                entry.second["md5"] = Value(master_sha1);
                entry.second["size"] = Value((unsigned long long)enc_size);
                entry.second["time"] = Value((unsigned long long)now);
                continue;
            }
            auto bundle = t->bundles_.find(entry.first);
            if (bundle != t->bundles_.end() && !bundle->second.sha1.empty()) entry.second["md5"] = Value(bundle->second.sha1);
        }
        for (auto& standin : standins) {
            Value v = Value::object();
            v["md5"] = Value(standin.sha);
            v["size"] = Value((unsigned long long)standin.disk);
            v["time"] = Value((unsigned long long)now);
            // (b) parentHash = CHash32 of the member's Individual bundle (3.7.0 entries match this)
            v["parentHash"] = Value(chash32(t->member_bundle_["Individual"][standin.name].c_str()));
            v["flags"] = Value(0u);
            v["encType"] = Value(standin.enc);
            v["ep_data"] = Value("");
            v["meta"] = Value::array();
            assets->map.emplace_back(standin.name, v);
        }
        t->files_["version.bin"] = mp_encode(t->version_);
    }
};

std::shared_ptr<Tree> Tree::build(const Options& opts, std::string* err) { return TreeBuilder(opts, err).build(); }

std::string Tree::summary() const {
    char b[512];
    snprintf(b, sizeof b, "CDN: revision %s, version %s, %zu bundles, %zu stand-ins; <AssetPath>/%s/Android/<name> from %s", revision_.c_str(),
             version_id_.c_str(), bundles_.size(), standins_, revision_.c_str(), opts_.mirror.c_str());
    return b;
}

std::string Tree::bundle_of(const std::string& manifest, const std::string& member) const {
    auto m = member_bundle_.find(manifest);
    if (m == member_bundle_.end()) return "";
    auto b = m->second.find(member);
    return b == m->second.end() ? "" : b->second;
}

bool Tree::lookup(const std::string& url_path, Response& out, bool stream) const {
    out = Response{};
    std::string path;
    if (!clean_path(url_path, path)) return false;
    // (b) "<AssetPath>/<r_ver>/Android/<name>"; any prefix before the first "Android" segment.
    std::string name;
    size_t a;
    if (path.compare(0, 8, "Android/") == 0) name = path.substr(8);
    else if ((a = path.find("/Android/")) != std::string::npos) name = path.substr(a + 9);
    else if (path.compare(0, 7, "master/") == 0) {
        // (b) the "download/" -> "master/" swap of master nodes: "<host>/master/<rev>/<name>"
        size_t s = path.find('/', 7);
        if (s == std::string::npos) return false;
        name = path.substr(s + 1);
    } else return false;
    if (name.empty()) return false;
    out.content_type = content_type(name);
    auto f = files_.find(name);
    if (f != files_.end()) {
        out.status = 200;
        out.body = f->second;
        return true;
    }
    auto b = bundles_.find(name);
    if (b != bundles_.end()) {
        if (stream) {
            // Aliasing the tree's owner keeps the tree (and its members) alive with the response.
            out.bundle = std::shared_ptr<const std::vector<Member>>(weak_from_this().lock(), &b->second.members);
            out.status = 200;
            return true;
        }
        if (!bundle_bytes(b->second.members, out.body)) {
            LOGW("cdn", "bundle %s: a member can't be read", name.c_str());
            out.body.clear();
            out.status = 500;
            return false;
        }
        out.status = 200;
        return true;
    }
    auto o = overlay_.find(name);
    std::string file = o != overlay_.end() ? o->second : opts_.mirror + "/" + name;
    if (!stat_file(file, nullptr)) return false;
    out.status = 200;
    out.file = file;
    return true;
}

std::string standin_dir_from_config() {
    const ServerConfig& c = config();
    if (!c.cdn_standins) return {};
    return c.standin_dir.empty() ? find_repo_file("standin-assets") : c.standin_dir;
}

std::shared_ptr<const AssetIndex> asset_index_from_config() {
    Options o = options_from_config();
    return dir_asset_index({o.mirror, o.standins});
}

Options options_from_config() {
    const ServerConfig& c = config();
    Options o;
    o.mirror = c.download_dir.empty() ? find_repo_file("work/download-3.7.0") : c.download_dir;
    o.master = c.master.empty() ? find_repo_file("data/basmaster-3.7.0.sqlite3") : c.master;
    o.standins = standin_dir_from_config();
    o.scratch = !c.cdn_scratch.empty() ? c.cdn_scratch
                : !c.data_root.empty() ? c.data_root + "/cdn"
                                       : "/tmp/soa-server-cdn-" + std::to_string(getuid());
    return o;
}

std::shared_ptr<Tree> build_from_config() {
    Options o = options_from_config();
    if (o.mirror.empty() || o.master.empty()) {
        LOGE("cdn", "no download tree (--download-dir) or master DB (--master)");
        return nullptr;
    }
    auto t = Tree::build(o);
    if (t) config().cdn_revision = t->revision();
    return t;
}

}  // namespace soa::server::cdn
