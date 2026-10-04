// CCocosNode natives (cocos_node.h); bound where they are used (restore/restore_tower.cpp).
#include "native/ui/cocos_node.h"

namespace soa::native::ui {

CCocosNode* CCocosNode::SearchByName(const guest::String& name) {
    const std::string_view want = name.view();
    for (CCocosNode* n = this; n; n = n->m_hierarchy.m_nextSibling) {
        if (n->m_name.view() == want) return n;
        if (CCocosNode* child = n->m_hierarchy.m_firstChild)
            if (CCocosNode* found = child->SearchByName(name)) return found;
    }
    return nullptr;
}

}  // namespace soa::native::ui
