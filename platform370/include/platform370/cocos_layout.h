#pragma once
// Framework::Cocos::CCocosNode and CCocosLabel of the 3.7.0 client, the fields platform370's
// --lang en text code (src/text_370.cpp) reads and writes. Recovered from the decompiles (work/decomp
// enc_label: CCocosLabel's constructor, Read_TextObjectData, DrawSelf; tc_msgwin:
// CEventScenarioMessageWindow::Show / Append; docs/notes.md "Tree" and "CCocosNode fields"). Plain
// guest memory: a pointer to one of these always points at a guest object, and the guest's vtable
// stays guest data (no C++ virtual here; port/src/native/VIRTUALS.md).
//
// Shared with the port's natives: port/src/native/ui/cocos_node.h (its CCocosNode, with typed
// containers platform370 can't include) static_asserts its offsets against these. platform370 may
// include only runtime/ and common/; the port may include platform370/include, so the layout lives
// here.
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <string_view>

namespace soa::platform370::cocos {

// A guest libc++ std::string (24 bytes; Framework::CSTLAllocator): the short form when bit 0 of
// byte 0 is clear (length in byte 0 >> 1, the characters from byte 1), else {capacity | 1, size, data}.
struct GuestString {
    uint8_t raw[24];
    std::string_view view() const {
        if (!(raw[0] & 1)) return {(const char*)raw + 1, (size_t)(raw[0] >> 1)};
        uint64_t size, data;
        std::memcpy(&size, raw + 8, 8);
        std::memcpy(&data, raw + 16, 8);
        return {(const char*)(uintptr_t)data, (size_t)size};
    }
};
static_assert(sizeof(GuestString) == 24);

// The dirty bits of m_flags (+0xcc) that make DrawSelf lay a label out again (CHome::PlayTalk and
// CEventScenarioMessageWindow::Show set them after changing the text, the box or the font).
constexpr uint32_t kRelayoutFlags = 0x9e000;
constexpr uint32_t kFontFlags = 0xe000;  // Show / Append after changing FontSize or the spacing

class CCocosNode {
public:
    uint64_t m_vptr;           // 0x00
    uint64_t m_parent;         // 0x08: THierarchy's parent (CCocosNode*)
    uint64_t m_nextSibling;    // 0x10
    uint64_t m_firstChild;     // 0x18
    uint64_t m_hierarchy20;    // 0x20: THierarchy's last field
    GuestString m_name;        // 0x28: SearchByName's key
    uint8_t m_pad40[0x84 - 0x40];
    float m_anchorX;           // 0x84
    float m_anchorY;           // 0x88
    float m_posX;              // 0x8c: Append writes the segment's x here
    float m_posY;              // 0x90: Append writes the line's y here
    float m_width;             // 0x94: the size (a label's box when IsCustomSize)
    float m_height;            // 0x98
    uint8_t m_pad9c[0xc0 - 0x9c];
    uint32_t m_color;          // 0xc0: Append's text colour
    uint8_t m_padC4[0xcc - 0xc4];
    uint32_t m_flags;          // 0xcc: dirty bits (kRelayoutFlags)
    uint8_t m_padD0[0xe8 - 0xd0];
    uint64_t m_renderer;       // 0xe8: a label's CDirectAofTextRenderer (CalcStringRect)
    uint8_t m_padF0[0x230 - 0xf0];
};
static_assert(sizeof(CCocosNode) == 0x230);
static_assert(offsetof(CCocosNode, m_parent) == 0x08);
static_assert(offsetof(CCocosNode, m_name) == 0x28);
static_assert(offsetof(CCocosNode, m_anchorX) == 0x84);
static_assert(offsetof(CCocosNode, m_posX) == 0x8c);
static_assert(offsetof(CCocosNode, m_width) == 0x94);
static_assert(offsetof(CCocosNode, m_height) == 0x98);
static_assert(offsetof(CCocosNode, m_color) == 0xc0);
static_assert(offsetof(CCocosNode, m_flags) == 0xcc);
static_assert(offsetof(CCocosNode, m_renderer) == 0xe8);

class CCocosLabel : public CCocosNode {
public:
    GuestString m_text;        // 0x230: SetText's copy
    uint8_t m_pad248[0x258 - 0x248];
    float m_fontSize;          // 0x258: CalcStringRect's size (the font's 24 px scaled by FontSize / 24)
    float m_unk25c;            // 0x25c: Show sets 0
    float m_lineSpacing;       // 0x260: CalcStringRect's spacing; lines are FontSize + this apart (Append)
    uint32_t m_hAlign;         // 0x264: HorizontalAlignmentType (Read_TextObjectData): 0 HT_Left, 1 HT_Center, 2 HT_Right
    uint8_t m_pad268[0x280 - 0x268];
    uint8_t m_customSize;      // 0x280: IsCustomSize (Read_TextObjectData): a fixed box at m_width x m_height
    uint8_t m_tagMode;         // 0x281: <font color=...> markup (CUIUtility::SetLabelTextTag)
    uint8_t m_shrink;          // 0x282: shrink a fixed box's text to fit (default 1)

    std::string_view name() const { return m_name.view(); }
    std::string_view text() const { return m_text.view(); }
    const CCocosNode* parent() const { return (const CCocosNode*)(uintptr_t)m_parent; }
};
static_assert(offsetof(CCocosLabel, m_text) == 0x230);
static_assert(offsetof(CCocosLabel, m_fontSize) == 0x258);
static_assert(offsetof(CCocosLabel, m_lineSpacing) == 0x260);
static_assert(offsetof(CCocosLabel, m_hAlign) == 0x264);
static_assert(offsetof(CCocosLabel, m_customSize) == 0x280);
static_assert(offsetof(CCocosLabel, m_tagMode) == 0x281);
static_assert(offsetof(CCocosLabel, m_shrink) == 0x282);

}  // namespace soa::platform370::cocos
