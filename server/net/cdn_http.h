#pragma once
// The CDN on soa-server's HTTP server (our code): cdn::Tree (soaserver/cdn.h) mounted on the
// router under the prefixes the 3.7.0 client's URLs start with: "<AssetPath>/<r_ver>/Android/<name>"
// with AssetPath = <cdn_url>/download, the "master/" spelling of the same, and a bare "/Android/".
#include <memory>

#include "http.h"
#include "soaserver/cdn.h"

namespace soa::server::net {

// GET / HEAD of a path the tree knows -> its bytes (Content-Type from the tree); else passes (404).
HttpHandler cdn_handler(std::shared_ptr<const cdn::Tree> tree);
// Routes /download/, /master/ and /Android/ to cdn_handler(tree).
void mount_cdn(HttpRouter& router, std::shared_ptr<const cdn::Tree> tree);

}  // namespace soa::server::net
