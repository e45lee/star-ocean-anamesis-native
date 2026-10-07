#pragma once
// The packet log's line formats (our code; soa-server --log-packets DIR, net/game.cpp, and soa's
// in-process route, port/src/native/api/packet_log.cpp, write the same lines, so that
// tools/compare_packets.py compares a run of one with a run of the other: tests/diff/). One
// formatter for both writers:
//
//   <date> <time> conn <id> #<n> > <Api> fid=<fid> <alg> plain=<size> method=<Method> args: <args>
//   <date> <time>   < <Reply> fid=<fid> <alg> plain=<size>[ packet=<size>][ <note>]
//
// <alg> is the envelope's cipher ("clear", "AES-128", ...; "inproc" for the in-process route,
// which has no packets); the reply's note is data_keys() of its body, or the ProtocolError's status.
#include <cstddef>
#include <cstdint>
#include <ctime>
#include <optional>
#include <string>
#include <vector>

namespace soa::server::net {

// A string argument as the log prints it: quoted, or its bytes in hex ("0x...") when it isn't
// plain ASCII.
std::string printable(const std::string& s);
// A reply body's top-level data keys and status: "data{<k1>,<k2>} status=<s>".
std::string data_keys(const std::vector<uint8_t>& msgpack);
// "%08x".
std::string fid_hex(uint32_t fid);
// A line's stamp: the host's local time, "YYYY-MM-DD HH:MM:SS".
std::string log_stamp(time_t t);
// "conn <conn> #<seq> > <api> fid=<fid>": the start of every request line.
std::string request_head(uint64_t conn, uint64_t seq, const std::string& api, uint32_t fid);
// "<head> <alg> plain=<plain> method=<method> args: <args>".
std::string request_line(const std::string& head, const std::string& alg, size_t plain, const std::string& method, const std::string& args);
// "  < <reply> fid=<fid> <alg> plain=<plain>[ packet=<packet>][ <note>]".
std::string reply_line(const std::string& reply, uint32_t fid, const std::string& alg, size_t plain, std::optional<size_t> packet,
                       const std::string& note);

}  // namespace soa::server::net
