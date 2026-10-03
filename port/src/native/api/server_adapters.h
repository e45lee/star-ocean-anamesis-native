#pragma once
// The port's side of the server library (top-level server/, libsoaserver; port code): what the
// in-process server needs from the game, read from the guest. server_adapters.cpp installs, before
// main(), the library's log sink (into core/log.h) and its soaserver/hooks.h AssetIndex (the
// AssetManager: APKs, --download-dir, stand-ins). Everything else the server learns from the
// requests, built here as the 3.7.0 wire carries them (inproc_request).
#include <cstdint>
#include <memory>
#include <string>

#include "soaserver/server.h"

namespace soa::server::cdn {
class Tree;
}

namespace soa::server_port {

// Fills server::config() from the run options (soa::options(), core/paths.h repo roots) and the
// data dir; main() calls it once the options are final, before the server is first used.
void config_from_options(const std::string& data_dir);

// The arguments of a FakeApiCaller request method, read from the guest registers x0..x7 (x0 =
// this) by walking the method's mangled parameter list (`mangled`: its symbol): j/m/h/i/a/b
// integers (only the argument's bits, zero-extended), PKa strings,
// RKN9Framework10CSTLVectorI{m,j}EE vectors; f/d (floats, in s/d registers) and z (varargs) end
// the walk.
server::Request capture_from_guest(const char* mangled, uint32_t fid, const uint64_t* x);
// The request as the 3.7.0 wire carries it: capture_from_guest plus, for MissionEnd,
// MissionFailed, Sphere211MissionEnd and Sphere211MissionFailed, the battle log the client's own
// serializer makes (client_battle_log.h) as Request::battle_log (none, logged, when the client
// wouldn't send it: over 0x1000 bytes).
server::Request inproc_request(const char* mangled, uint32_t fid, const uint64_t* x);
// The requests the client made, kept until FakeApiCaller's Progress answers them through
// server::answer (fakeapi.cpp ServeProgress), one per FunctionID (the queue's key): remember()
// keeps `r` (the last one of its fid wins, as in the queue), take() hands it over (a request of
// method "" when none was kept).
void remember(server::Request r);
server::Request take(uint32_t fid);
// inproc_request + remember, when the server is on (what the FakeApiCaller hooks call).
void capture(const char* mangled, uint32_t fid, const uint64_t* x);

// --server inproc: the library's CDN (soaserver/cdn.h) on soa-server's HTTP router, installed as
// platform370's HTTP backend: no socket, no thread (server_cdn.cpp); sets config().cdn_url so Login
// sends the CDN keys. false with the reason in *err (on success *err describes the CDN).
bool start_inproc_cdn(std::string* err);
// Its tree (nullptr before start_inproc_cdn).
std::shared_ptr<const server::cdn::Tree> inproc_cdn_tree();

}  // namespace soa::server_port
