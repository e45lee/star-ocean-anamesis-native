#pragma once
// The CDN content soa-server serves to the unmodified 3.7.0 client (library code, no sockets: the
// wire layer's HTTP server mounts Tree::lookup). docs/online-server.md section 6 has the protocol;
// server/README.md "CDN" the layout.
//
// What the client fetches (CGameResourceDownloader, 3.7.0): every URL is
//   CInfoManager::GetDownloadURL() = "<AssetPath>/<r_ver>/"  (both from the Login response)
//   + "Android/" + <name>                                     (CDownloadNode::StartDownload)
// where <name> is "version.bin", "manifest/<format>/<quality>/version*.{bin,version}", or a
// bundle of the manifests ("I/<h>/<h>.bin", "B/<h>/<h>.bin", "EP<n>/.../<h>.bin"). The client
// never fetches single assets: it downloads the bundle (an "\0ISF" FileStream image of the member
// payloads, below), checks its SHA-1 against the manifest's "md5", and unpacks each member into
// its storage with a fresh ADLD header (encType = the member's "e").
//
// The tree is built at startup from the 3.7.0 download (work/download-3.7.0, which holds the
// unpacked members, not the bundles):
//   - the master DB: the decrypted 3.7.0 master (ServerConfig::master) copied, given the server's
//     client-master overrides (apply_client_master: event date shifts, texts, tower banners, shop
//     windows, Sphere 211), VACUUMed and ADLD-AES packed as "sqlite/basmaster.sqlite3";
//   - optional stand-in assets (standin-assets) added as new members; with --english also the
//     generated "-en" files (the English master), the same way;
//   - every bundle rebuilt from the members on disk; the manifests and version.bin get the new
//     bundle hashes and sizes, the master's and stand-ins' entries, new version ids, and version.bin
//     the next revision (1471 -> 1472), which Login's r_ver then reports.
// The 3.7.0 bundles' own byte layout isn't recoverable (they aren't in the download and their
// header words are unknown), so every bundle's "md5" in the served manifests is ours.
#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "soaserver/hooks.h"
#include "soaserver/msgpack.h"

namespace soa {
class FileTree;  // soa/file_tree.h
}

namespace soa::server::cdn {

struct Member;

// A body read in pieces (Response::open): the CDN's answers run to hundreds of MB (the bundles),
// so a reader that needn't hold them whole. Not thread-safe; one reader per request.
class Reader {
public:
    virtual ~Reader() = default;
    virtual uint64_t size() const = 0;               // the whole body's length
    virtual int64_t read(uint8_t* buf, size_t n) = 0;  // > 0 bytes read, 0 at the end, < 0 on an error
};

// One HTTP answer: `body` in memory, the file `file` (whole), or the bundle `bundle` (its members;
// only from Tree::lookup(..., stream = true)); 404 when not found.
struct Response {
    int status = 404;
    std::string content_type;
    std::vector<uint8_t> body;
    std::string file;
    // With file_range: only bytes [file_offset, file_offset + file_len) of `file` (a stored entry of
    // the download's zip, soa/file_tree.h, served in place).
    bool file_range = false;
    uint64_t file_offset = 0, file_len = 0;
    std::shared_ptr<const std::vector<Member>> bundle;  // keeps its Tree alive
    uint64_t size() const;               // the body's length (stats the file)
    bool read(std::vector<uint8_t>& out) const;  // the body's bytes (reads the file, builds the bundle)
    // The body as a reader that reads the file / builds the bundle as it goes (nullptr when the
    // file can't be opened). Copies an in-memory body.
    std::unique_ptr<Reader> open() const;
};

struct Options {
    std::string mirror;          // the 3.7.0 download: a folder (work/download-3.7.0) or its zip (soa/file_tree.h)
    std::string master;          // the decrypted 3.7.0 master DB (data/basmaster-3.7.0.sqlite3)
    std::string scratch;         // the served master and the bundle-hash cache are written here
    std::string standins;        // stand-in overlay ("" = none): <rel> files added as members
    // More roots like `standins`, after it: their <rel> files the download lacks become new
    // members (a name an earlier root added is skipped).
    std::vector<std::string> member_roots;
    // --english (docs/server-rules.md#english): the generated root <scratch>/lang-en (the English
    // master, make_english_master, built from `english_text`) is added after member_roots. Off:
    // nothing of it is read or served.
    bool english = false;
    std::string english_text;    // the English text table ("" with english: no -en master, warned)
    std::string format = "etc2/hi";  // the manifest directory served (manifest/<format>/)
    bool overrides = true;       // apply_client_master on the served master
    int64_t now = 0;             // the clock for the overrides and version.bin times (0 = the server clock)
    int threads = 0;             // bundle hashing (0 = up to 8)
    bool hash_cache = true;      // reuse <scratch>/cdn-bundles.cache
};

// ---- the pieces (unit-tested on their own) ----------------------------------------------------

// A bundle member: its manifest name, encType ("e"), and where its payload comes from: the bytes
// of `file` after `skip` bytes (the ADLD header of the stored asset), or `mem` when set.
struct Member {
    std::string name;
    uint32_t enc = 0;
    std::string file;
    uint64_t skip = 0;
    uint64_t len = 0;  // payload length
    std::shared_ptr<const std::vector<uint8_t>> mem;
};
// The bundle ("\0ISF" FileStream image, Framework::FileStream::tImage): header {0x46534900,
// 0x20130304, count, 0}, count entries {name offset, payload offset, payload length, 0}, the
// NUL-terminated names packed, each payload 32-byte aligned, the whole padded to 32 (the sizes of
// the 3.7.0 bundles follow this layout; its zero words are ours).
uint64_t bundle_size(const std::vector<Member>& members);
bool bundle_bytes(const std::vector<Member>& members, std::vector<uint8_t>& out);
// SHA-1 (lowercase hex) of the bundle, streamed; "" when a member can't be read.
std::string bundle_sha1(const std::vector<Member>& members);
std::string sha1_hex(const uint8_t* data, size_t n);

// The master DB to serve: copies `master` to `plain_out`, applies the overrides (unless
// opts.overrides is false), VACUUMs, and returns the ADLD (encType 2) file's bytes; the plaintext's
// SHA-1 in *plain_sha1 and its size in *plain_size. Empty on error (logged).
std::vector<uint8_t> make_served_master(const std::string& master, const std::string& plain_out, bool overrides, int64_t now, std::string* plain_sha1,
                                        uint64_t* plain_size);

// What make_english_master did with the English text table (docs/server-rules.md#english).
struct EnglishStats {
    size_t replaced = 0;  // ja_ rows whose text_value became English
    size_t inserted = 0;  // new rows (ids the master lacks)
    size_t stale = 0;     // English for another Japanese text: the row stays Japanese
    size_t skipped = 0;   // rows that can't be applied (an id the master lacks with a ja_sha1, an id taken)
};
// The English master (--english, served as "sqlite/basmaster-en.sqlite3"): copies the served
// master's plaintext `served_plain` (make_served_master's `plain_out`: after every ClientMaster
// hook) to `plain_out`, applies the English text table `table` (english_text.h: text_value of the
// ja_ rows whose Japanese it translates, new rows for new ids; no row deleted, no id changed),
// VACUUMs, and returns the ADLD (encType 2) file's bytes, keyed by the -en name; the plaintext's
// SHA-1 and size as make_served_master. Empty on error (logged).
std::vector<uint8_t> make_english_master(const std::string& served_plain, const std::string& table, const std::string& plain_out,
                                         std::string* plain_sha1, uint64_t* plain_size, EnglishStats* stats = nullptr);

// ---- the tree ---------------------------------------------------------------------------------

class Tree : public std::enable_shared_from_this<Tree> {
public:
    // Builds everything (seconds; the bundle hashes are cached in opts.scratch). nullptr on error
    // (*err says why).
    static std::shared_ptr<Tree> build(const Options& opts, std::string* err = nullptr);

    // The answer for an HTTP GET of `url_path` (the path of the URL, a query is ignored):
    //   .../Android/<name>  : version.bin, manifest/<format>/..., a bundle, the served master
    //                         ("sqlite/basmaster.sqlite3"), a stand-in, or the download's file <name>;
    //   /master/<rev>/<name>: the same (the client's "download/" -> "master/" swap, unused in 3.7.0).
    //   With `stream`, a bundle comes back as Response::bundle (read it with Response::open)
    //   instead of its bytes in `body`.
    // Thread-safe: the tree doesn't change after build(), and lookup only reads it.
    bool lookup(const std::string& url_path, Response& out, bool stream = false) const;

    const std::string& revision() const { return revision_; }      // the served version.bin revision
    const std::string& version_id() const { return version_id_; }  // version.bin "version"
    // The bundle that holds `member` in manifest `manifest` ("Individual", "Bulk", "ep1".."ep3").
    std::string bundle_of(const std::string& manifest, const std::string& member) const;
    const Value& version_bin() const { return version_; }
    // Statistics for the log: bundles, members, stand-ins.
    std::string summary() const;

    struct Bundle {
        std::vector<Member> members;
        uint64_t size = 0;
        std::string sha1;
    };

private:
    friend struct TreeBuilder;  // Tree::build's steps (src/cdn/tree.cpp)
    Options opts_;
    std::string revision_, version_id_;
    Value version_;
    std::map<std::string, std::vector<uint8_t>> files_;  // in-memory files by name (version.bin, manifests)
    std::map<std::string, Bundle> bundles_;              // by name ("I/86c7aec3/3a05a888.bin")
    std::map<std::string, std::map<std::string, std::string>> member_bundle_;  // manifest -> member -> bundle
    std::map<std::string, std::string> overlay_;         // member name -> file (served master, stand-ins, -en files)
    std::shared_ptr<const FileTree> src_;                // the download (opts_.mirror), a folder or a zip
    size_t standins_ = 0;  // members added from the roots (stand-ins and -en files)
};

// Options from config() (master, download_dir, standin_dir / cdn_standins, cdn_scratch, data_root).
Options options_from_config();
// The stand-in overlay from config(): standin_dir, else the repository's standin-assets
// (find_repo_file); "" when cdn_standins is off (--standin-assets off).
std::string standin_dir_from_config();
// soa-server's asset index (hooks.h): the files the CDN serves, i.e. the download dir and then the
// stand-in overlay (options_from_config's mirror and standins), so the server's content gates (an
// enabled gacha's banner image, docs/server-rules.md#enabling-events) see the stand-ins as soa's
// AssetManager does with --standin-assets.
std::shared_ptr<const AssetIndex> asset_index_from_config();
// Builds the tree from config() and records its revision in config().cdn_revision (for Login's
// r_ver). nullptr on error (logged).
std::shared_ptr<Tree> build_from_config();

}  // namespace soa::server::cdn
