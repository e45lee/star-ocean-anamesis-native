// The module registry's order (server/src/core/modules.cpp; --selftest "server/module-order"). Each hook
// kind runs in registration order, and the player-load / response hooks add keys to one response
// map whose insertion order is on the wire, so the order is pinned here: a change to it is a change
// to the reply bytes and must be deliberate (update this list in the same commit, and say so).
#include <map>
#include <string>
#include <vector>

#include "soaserver/native_test.h"
#include "soaserver/ext.h"

namespace soa::server {
namespace {

// Per kind: the registering modules in run order, with the detail (Grant: content type) where
// there is one. Today's order is the one the file names gave before step R4 of
// server/PLAN-readability.md (static initializers in link order). (The Schema kind went with
// PLAN-schema S1: every table is state/schema.cpp's.)
const char* const kExpected[] = {
    "OnPlayerLoad: login_bonus, achievements, daily, event, follow, gear, home, notice, shop, sphere211, subscription, title, tower, worldboss, settings",
    "OnResponse: event, title",
    "MissionStartExtra: favor_drop, worldboss",
    "MissionResultExtra: event_ranking, tower, worldboss",
    "Grant: daily (content type 11), gear (content type 15), gear (content type 98), subscription (content type 20), title (content type 13)",
    "ItemExtra: gear",
    "ClientMaster: event, home, shop, sphere211, sphere211, tower",
    "AreaExtra: worldboss",
};

NATIVE_TEST("server/module-order") {
    for (const std::string& e : ext::registration_errors()) t.fail("registration error: %s", e.c_str());
    std::vector<std::string> kinds;
    std::map<std::string, std::string> got;
    for (const ext::HookInfo& h : ext::hook_order()) {
        auto it = got.find(h.kind);
        if (it == got.end()) {
            kinds.push_back(h.kind);
            it = got.emplace(h.kind, h.kind + ": ").first;
        } else {
            it->second += ", ";
        }
        it->second += h.module + (h.detail.empty() ? "" : " (" + h.detail + ")");
    }
    std::map<std::string, bool> seen;
    for (const char* line : kExpected) {
        std::string want = line, kind = want.substr(0, want.find(':'));
        seen[kind] = true;
        auto it = got.find(kind);
        if (it == got.end()) t.fail("no %s hooks registered; want \"%s\"", kind.c_str(), line);
        else if (it->second != want) t.fail("hook order changed:\n  want %s\n  got  %s", line, it->second.c_str());
    }
    for (const std::string& k : kinds)
        if (!seen.count(k)) t.fail("a hook kind the list doesn't name: %s", got[k].c_str());
}

}  // namespace
}  // namespace soa::server
