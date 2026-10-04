#pragma once
// Framework::Cocos::CCocosNode, as far as the natives read it (docs/notes.md "Tree" and
// "CCocosNode fields"): the THierarchy links and the name. The rest of the 0x230 bytes is not
// recovered yet; a CCocosNode* here always points at a guest node.
#include <cstddef>

#include "native/common/guest_std.h"
#include "native/containers/containers_layout.h"

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

}  // namespace soa::native::ui
