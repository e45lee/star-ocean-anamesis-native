#pragma once
// soa-server's sockets (our code): one poll() loop over the game server's TCP port (game.h) and
// the HTTP port (http.h). Single-threaded; the server library is called from the loop's thread.
#include <atomic>
#include <cstdint>
#include <map>
#include <string>
#include <vector>

#include "game.h"
#include "http.h"

namespace soa::server::net {

// "HOST:PORT" -> host, port; false when malformed.
bool parse_host_port(const std::string& s, std::string* host, uint16_t* port);

class Loop {
public:
    Loop(GameServer& game, HttpRouter& http) : game_(game), http_(http) {}
    ~Loop();
    // Listen on host:port (port 0: any; the bound port is game_port() / http_port()).
    bool listen_game(const std::string& host, uint16_t port, std::string* err);
    bool listen_http(const std::string& host, uint16_t port, std::string* err);
    uint16_t game_port() const { return game_port_; }
    uint16_t http_port() const { return http_port_; }
    // One poll() round (timeout in ms).
    void run_once(int timeout_ms);
    // Until *stop is set (checked every 100 ms).
    void run(const std::atomic<bool>& stop);

private:
    struct Conn {
        bool http = false;
        uint64_t game_id = 0;
        HttpParser parser;
        std::vector<uint8_t> out;
        bool close_after = false;  // close once out is sent
    };
    bool listen_on(const std::string& host, uint16_t port, int* fd, uint16_t* bound, std::string* err);
    void accept_on(int lfd, bool http);
    void on_readable(int fd, Conn& c);
    void drop(int fd);

    GameServer& game_;
    HttpRouter& http_;
    int game_fd_ = -1, http_fd_ = -1;
    uint16_t game_port_ = 0, http_port_ = 0;
    std::map<int, Conn> conns_;
};

}  // namespace soa::server::net
