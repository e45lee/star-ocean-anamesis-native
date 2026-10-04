#pragma once
// The present box (port code, not guest behaviour): PresentList and GetPresent /
// GetPresentArray (api/presents/presents.cpp; docs/server-rules.md#presents-rules).
#include <vector>

#include "soaserver/ext.h"

namespace soa::server {

std::vector<u8> present_list(ext::Ctx& ctx, const Request& req);
std::vector<u8> get_present(ext::Ctx& ctx, const Request& req);

// The CPresentBoxInfo of one row of the `presents` table (the box's entry; the achievements'
// AddPresent sends the same).
Value present_box_info(ext::Ctx& ctx, const ext::Row& present_row);

}  // namespace soa::server
