#pragma once
// Framework::Cocos::CCocosNode, as far as the natives read it (docs/notes.md "Tree" and
// "CCocosNode fields"): the THierarchy links and the name. The fields platform370 reads are in
// platform370/cocos_layout.h (asserted to agree below); a CCocosNode* here always points at a guest node.
#include <cstddef>

#include "native/common/guest_std.h"
#include "native/containers/containers_layout.h"
#include "platform370/cocos_layout.h"

namespace soa::native::ui {

class CCocosNode {
public:
    // CCocosNode::SearchByName(const std::string&) (guest 0x1fb6eac): the first node named `name`
    // in a depth-first, pre-order walk of this node, its first child's subtree, then its next
    // sibling's (and so on along the sibling list); null when none. The guest recurses on both
    // links (one frame per sibling); this walks the siblings in a loop, so it recurses only per
    // tree level. Names compare as std::string ==: the empty name matches an unnamed node.
    CCocosNode* SearchByName(const guest::String& name);

    containers::THierarchy<CCocosNode> m_hierarchy;  // 0x00: vptr, parent, next sibling, first child, 0x20
    guest::String m_name;                            // 0x28
    // 0x40.. not recovered (0x230 bytes in all)
};
static_assert(offsetof(CCocosNode, m_hierarchy) == 0x00);
static_assert(offsetof(CCocosNode, m_name) == 0x28);
// The same object as platform370's raw layout (platform370/cocos_layout.h, the --lang en text code).
static_assert(offsetof(CCocosNode, m_name) == offsetof(platform370::cocos::CCocosNode, m_name));
static_assert(sizeof(guest::String) == sizeof(platform370::cocos::GuestString));

}  // namespace soa::native::ui
