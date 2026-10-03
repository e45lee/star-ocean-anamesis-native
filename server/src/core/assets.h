#pragma once
// The one asset gate of the local server (port code, not guest behaviour): whether the game can
// load an asset file, decided at run time from the host's AssetIndex (soaserver/hooks.h), never
// from a list (docs/server-rules.md). Tests install one override predicate for the whole library;
// events::set_asset_check and sphere211::set_asset_check are this override.
#include <cstdint>
#include <functional>
#include <string>

namespace soa::server::assets {

using Check = std::function<bool(const std::string& rel)>;

// Installs the tests' predicate on "<dir>/<file>" names (an empty function removes it). Every
// cache of verdicts derived from assets is stale afterwards (generation()).
void set_override(Check fn);
bool has_override();
// Counts set_override calls: a cache of asset verdicts keeps the generation it was filled at and
// starts over when it changed.
uint64_t generation();

// No asset source at all (the unit tests without the game's APKs): the gates then let everything
// through rather than nothing.
bool no_source();
// The host's index: "builtin_data/<rel>" (the APKs, then --download-dir) or "assetpack/<rel>" (the
// install-time asset pack), each also under the texture quality subdirectories etc2/ and etc2/hi/
// (soa: its AssetManager, find then find_download).
bool found(const std::string& rel);
// The gate: the override when one is installed, else true without any asset source, else found().
bool available(const std::string& rel);

}  // namespace soa::server::assets
