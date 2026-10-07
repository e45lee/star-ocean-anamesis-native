#pragma once
// The in-process route's packet log (port code, not guest behaviour): soa --log-packets DIR /
// --log-packets DIR writes DIR/packets.log in the form soa-server --log-packets writes it
// (server/net/game.cpp), so that tools/compare_packets.py compares a run of the in-process port
// with a run against soa-server (tests/diff/). Off unless the option is given. The line formats
// are soa-server's own (server/net/packet_log.h, one formatter for both).
//
//   <date> <time> conn 0 #<n> > <Api> fid=<fid> inproc plain=0 method=<Method> args: <args>
//   <date> <time>   < <Reply> fid=<reply fid> inproc plain=<body size> data{<keys>} status=<s>
//   <date> <time>   < ProtocolError fid=05aed673 inproc plain=0 status=<code> (the server's error code)
//
// <Api> and <fid> are the wire API the request is (server::net::api_by_method of its method, else
// the one of its queued fid): a few FakeApiCaller methods queue under another API's FunctionID
// (EquipAccessory under EquipWeapon's, ...), and are logged, with their reply, as the wire logs
// them; the method is the wire's (server_adapters.cpp kWireMethods: SellItemArray is SellItem).
// The arguments are the captured server::Request laid out in the wire's order (the request
// layouts of server/net/gen/wire_decode.inc), printed as soa-server's decoder prints them; what the
// FakeApiCaller route can't know (the DeviceType of a "dev" field) prints as "dev=?", and a request
// whose captured arguments don't fit its wire layout (Login: the wire's UUID / tokens, which
// IApiCaller::Login doesn't take) prints them raw, "ints=[..] strs=[..] vecs=[..]". The reply's
// data keys are taken after the campaign's additions, as soa-server takes them. Every reply body
// is also written as DIR/<n>-<Reply>.msgp and every battle log as DIR/<n>-<Api>-battle_log.msgp.
#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

#include "soaserver/server.h"

namespace soa::server_port::packet_log {

// Opens DIR/packets.log (appending); "" = off. config_from_options calls it.
void open(const std::string& dir);
bool enabled();

// A request the client made (inproc_request). battle_log: the client's serialized battle log
// (MissionEnd & co.), or empty.
void request(const server::Request& r, const std::vector<uint8_t>& battle_log);
// The answer of the queued request `fid` delivered (FakeApiCaller's ServeProgress): its body, or
// the server's error code.
void reply(uint32_t fid, const std::vector<char>& body);
void refused(uint32_t fid, uint32_t code);

// The wire-form argument text of r (exposed for the selftest).
std::string format_args(const server::Request& r, size_t battle_log_size);

}  // namespace soa::server_port::packet_log
