#pragma once
// The Sphere 211 APIs' request arguments by name (port code, not guest behaviour), as
// core/request_args.h does for the core's: each struct reads one method's positional arguments
// (docs/api.md's **Method** / **Request** lines; docs/server-rules.md#sphere211-requests),
// with the defaults the handlers used when one is missing (0 / none; none of
// them logs). MissionStart / End / Failed / Continue also name their cell by their first two
// integers (CStageManager+0x68 / +0x6c), which find_cell (floors.cpp) reads.
#include <vector>

#include "core/request_args.h"

namespace soa::server::args {

// Sphere211SelectedFloor(u32 offset): (b) the floor chosen in the next-floor select as the offset
// from the current floor (the request carried 1 when 2F was chosen on 1F).
struct Sphere211SelectedFloorArgs {
    u32 offset = 0;
    static Sphere211SelectedFloorArgs from(const Request& r) { return {(u32)int_at(r, 0)}; }
};

// Sphere211MissionStart(u32 +0x68, u32 cell asset id, u64 uid, u64 uid, u64 uid, u64 slot4, u32 owner)
// (b: CStageManager::CallMissionStart type 5, the captured requests): three party members, the 4th
// (rental) slot's character (an own uid, or a rental id, rental.h) and its owner (the player's own
// id, or the lender's player id).
struct Sphere211MissionStartArgs {
    std::vector<u64> party_slots;  // the three party slots present in the request (0 = empty)
    u64 slot4 = 0;
    bool has_owner = false;
    u32 owner = 0;
    static Sphere211MissionStartArgs from(const Request& r) {
        Sphere211MissionStartArgs a;
        for (size_t k = 2; k < 5 && k < r.ints.size(); k++) a.party_slots.push_back(r.ints[k]);
        a.slot4 = int_at(r, 5);
        a.has_owner = r.ints.size() > 6;
        a.owner = (u32)int_at(r, 6);
        return a;
    }
};

// Sphere211FloorClear(u32 goal asset id): the goal (目標地点) reached; 0 = the floor's is_goal cell.
struct Sphere211FloorClearArgs {
    u32 goal_asset_id = 0;
    static Sphere211FloorClearArgs from(const Request& r) { return {(u32)int_at(r, 0)}; }
};

}  // namespace soa::server::args
