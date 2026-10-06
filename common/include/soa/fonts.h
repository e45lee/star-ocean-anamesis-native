#pragma once
// The fonts built into the programs (cmake/fonts.cmake, library soa_fonts): Noto Sans JP, regular
// and bold, as bytes in the executable. Used by the keyboard's text box
// (runtime/src/app/text_overlay.cpp: regular) and the web view (webview/src/fonts.cpp: both).
// Every platform draws with these; there is no font setting and no system font search.
#include <cstddef>
#include <cstdint>

extern "C" {
extern const uint8_t soa_font_regular[], soa_font_regular_end[];
extern const uint8_t soa_font_bold[], soa_font_bold_end[];
}

namespace soa::fonts {

struct Data {
    const uint8_t* bytes;
    size_t size;
    const char* name;  // for messages
};

inline Data regular() { return {soa_font_regular, (size_t)(soa_font_regular_end - soa_font_regular), "Noto Sans JP Regular"}; }
inline Data bold() { return {soa_font_bold, (size_t)(soa_font_bold_end - soa_font_bold), "Noto Sans JP Bold"}; }

}  // namespace soa::fonts
