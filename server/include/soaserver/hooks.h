#pragma once
// What the local server asks of its host (library code). The server takes everything about the
// client from the requests themselves (as the 3.7.0 wire carries it, docs/server-hooks-review.md);
// the one question left is which asset files exist. soa installs its AssetManager
// (port/src/native/api/server_adapters.cpp), soa-server a directory index. Install it before the
// first request.
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace soa::server {

// ---- which asset files exist --------------------------------------------------------------------------
// The server offers only content whose files the client can load (docs/server-rules.md: never a
// list of names). It asks by asset name as the client's file loader names them:
// "builtin_data/<rel>" (APKs and the download dir) and "assetpack/<rel>" (the install-time pack).
// soa: its AssetManager (APKs, --download-dir, stand-ins); soa-server: dir_asset_index over the
// download dir and the stand-ins (cdn::asset_index_from_config). With none (or an empty one)
// nothing is gated (unit tests).
struct AssetIndex {
    virtual ~AssetIndex() = default;
    // Whether the asset `name` ("builtin_data/<rel>" or "assetpack/<rel>") can be loaded.
    virtual bool exists(const std::string& name) const = 0;
    // No asset source at all.
    virtual bool empty() const = 0;
};
// nullptr = none. Returns the index it replaces (a test puts it back).
std::shared_ptr<const AssetIndex> set_asset_index(std::shared_ptr<const AssetIndex> index);
const AssetIndex& asset_index();
// A filesystem index: "builtin_data/<rel>" is <dir>/<rel> for each dir in order (as the port's
// --download-dir); a dir may be a zip of the tree (the download's SOA-3.7.0-canonical-data.zip,
// soa/file_tree.h); other names are absent. empty() when no dir opens.
std::shared_ptr<const AssetIndex> dir_asset_index(std::vector<std::string> dirs);

}  // namespace soa::server
