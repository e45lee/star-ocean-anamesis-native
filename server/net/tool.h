#pragma once
// soa-server --wire-tool: builds and reads packets of the wire format from the command line, for
// the client-side checks (server/tests/ninja/tools/gen_ninja_vectors.py wire-replies feeds these
// packets to the client's own receiver under unicorn). Our code.
namespace soa::server::net {
int wire_tool(int argc, char** argv);
}
