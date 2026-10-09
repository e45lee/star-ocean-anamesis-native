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

    // vtable slot 5: CCocosNode* Clone(CCocosNode* into) const (a copy of this node: into, or a new one
    // when null; e.g. _ZNK9Framework5Cocos11CCocosLabel5CloneEPNS0_10CCocosNodeE).
    static constexpr int kSlotClone = 5;

    containers::THierarchy<CCocosNode> m_hierarchy;  // 0x00: vptr, parent, next sibling, first child, 0x20
    guest::String m_name;                            // 0x28
    u8 unk_40[0x84 - 0x40];                          // 0x40
    float m_anchor[2];                               // 0x84: x, y (a label's 0.5, 0.5 by default)
    float m_position[2];                             // 0x8c
    float m_size[2];                                 // 0x94: the content size
    float m_scale[2];                                // 0x9c: x, y
    // 0xa4.. not recovered (0x230 bytes in all; docs/notes.md "CCocosNode fields")
};
static_assert(offsetof(CCocosNode, m_hierarchy) == 0x00);
static_assert(offsetof(CCocosNode, m_name) == 0x28);
static_assert(offsetof(CCocosNode, m_anchor) == 0x84);
static_assert(offsetof(CCocosNode, m_position) == 0x8c);
static_assert(offsetof(CCocosNode, m_size) == 0x94);
static_assert(offsetof(CCocosNode, m_scale) == 0x9c);
// The same object as platform370's raw layout (platform370/cocos_layout.h, the --lang en text code).
static_assert(offsetof(CCocosNode, m_name) == offsetof(platform370::cocos::CCocosNode, m_name));
static_assert(offsetof(CCocosNode, m_anchor) == offsetof(platform370::cocos::CCocosNode, m_anchorX));
static_assert(offsetof(CCocosNode, m_position) == offsetof(platform370::cocos::CCocosNode, m_posX));
static_assert(offsetof(CCocosNode, m_size) == offsetof(platform370::cocos::CCocosNode, m_width));

// CCocosSceneUnit: a screen built from a Cocos scene (the base of CDialog, CWebView, ...). Only the vtable
// slot the port calls: 11 GetCocosScene() const, the scene's root node (_ZTV8CWebView slot 11 is
// CCocosSceneUnit::GetCocosScene; CWebView::OpenView gets its popup's layout this way).
class CCocosSceneUnit {
public:
    static constexpr int kSlotGetCocosScene = 11;
    const void* vtable;  // 0x00
};
static_assert(sizeof(guest::String) == sizeof(platform370::cocos::GuestString));

}  // namespace soa::native::ui
