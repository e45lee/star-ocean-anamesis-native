#pragma once
// soa-server --replay: runs a recorded request sequence through the server library, as soa-server's
// game connection would (server/tests/replay/README.md; server/PLAN-readability.md section 4.1).
// The proof that a refactor changes nothing: tools/server_replay_diff.sh replays every corpus with
// two builds and compares what they wrote.
#include <string>

namespace soa::server::app {

// Replays the corpus DIR/requests.txt into OUT (created):
//   OUT/<n>-<Method>.msgp   each reply body, as the library answered it (before the wire's envelope);
//   OUT/replies.txt         the same bodies as text, one request per block (for reading a diff);
//   OUT/errors.txt          "<n> <Method> <code>" per request (0 accepted, "not-handled" no handler);
//   OUT/state.sql           the end state: every table's schema and rows (sorted), then the side
//                           files of the data dir (server_campaign.txt);
//   OUT/server.log          the server's log lines.
// The server options (the master, the seed, --seed-rng, --clock, the modules' switches) must
// already be in config(), as the corpus's DIR/options lists them. The state DB and the data dir
// are OUT/data/ (deleted first; --db is refused). Each request runs with the server clock at its
// recorded time (the clock source seam, server.h set_clock_source). Returns the process exit status.
int replay(const std::string& dir, const std::string& out, bool verbose);

// soa-server --list-apis: every method the wire knows or the library answers, one per line:
// "<method>\t<fid>\t<answered by>" where <answered by> is "core" (server.cpp's dispatcher),
// the registering module file (server/src/...), or "-" (no handler: soa-server answers data.Time).
int list_apis();
// soa-server --list-hooks: every module hook in its run order (ext::hook_order), one per line:
// "<kind>\t<module>\t<file>:<line>\t<detail>".
int list_hooks();

}  // namespace soa::server::app
