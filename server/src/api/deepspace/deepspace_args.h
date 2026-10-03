#pragma once
// The deep space APIs' request arguments by name (port code, not guest behaviour), as
// core/request_args.h does for the core's: each struct reads one method's positional arguments
// (docs/api.md's **Method** / **Request** lines; docs/server-rules.md "Deep space", "Requests as the
// client sends them"), with the defaults the handlers used when one is missing (0 / none; none of
// them logs).
#include <vector>

#include "core/request_args.h"

namespace soa::server::args {

// DeepSpaceAutoMemberSelect(u32 bonus_set_id, u32 bonus_id): (b) the offer's bonus set and the
// bonus the player tapped on the party screen (the captured requests). The handler reads the bonus.
struct DeepSpaceAutoMemberSelectArgs {
    u32 bonus_set_id = 0, bonus_id = 0;
    static DeepSpaceAutoMemberSelectArgs from(const Request& r) { return {(u32)int_at(r, 0), (u32)int_at(r, 1)}; }
};

// DeepSpaceMissionStart(u32 mission_id, u32 item_id, vector<u64> uids): (b) the mission, the
// master item id of the bonus item chosen in CDeepSpaceItemSelectDialog (0 = none; the dialog lists
// stack items, content type 9, of master_deep_space_bonus_item) and the party's uids (the captured
// request).
struct DeepSpaceMissionStartArgs {
    u32 mission_id = 0, item_id = 0;
    std::vector<u64> uids;
    static DeepSpaceMissionStartArgs from(const Request& r) {
        return {(u32)int_at(r, 0), (u32)int_at(r, 1), r.vecs.empty() ? std::vector<u64>{} : r.vecs[0]};
    }
};

// DeepSpaceMissionEnd(u32 ship_id) and DeepSpaceMissionEndNow(u32 ship_id).
struct DeepSpaceMissionEndArgs {
    u32 ship_id = 0;
    static DeepSpaceMissionEndArgs from(const Request& r) { return {(u32)int_at(r, 0)}; }
};

}  // namespace soa::server::args
