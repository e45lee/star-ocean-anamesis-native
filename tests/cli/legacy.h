#pragma once
// The old hand-written parsers (legacy.cpp), filling the new parsers' structs.
#include "emulator-viewer/src/cli.h"
#include "emulator/src/cli.h"
#include "port/src/core/cli.h"
#include "server/app/cli.h"
#include "webview/tools/cli.h"

namespace legacy {
int parse_soa(int argc, const char* const* argv, soa::SoaArgs& r);
int parse_server(int argc, const char* const* argv, soa::server::app::ServerArgs& r);
int parse_emu(int argc, const char* const* argv, soa::emu::EmuArgs& r);
int parse_viewer(int argc, const char* const* argv, soa::viewer::ViewerArgs& r);
int parse_render(int argc, const char* const* argv, soa::webview::RenderArgs& r);
}  // namespace legacy
