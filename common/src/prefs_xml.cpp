// soa/prefs_xml.h: pugixml reads, the writer is Android's format by hand.
#include <soa/prefs_xml.h>

#include <pugixml.hpp>

namespace soa::prefs_xml {

Entries parse(std::string_view xml) {
    Entries out;
    pugi::xml_document doc;
    // parse_ws_pcdata_single: a text of only whitespace (<string name="x">    </string>) is kept.
    // On a parse error the document holds what was read before it.
    doc.load_buffer(xml.data(), xml.size(), pugi::parse_default | pugi::parse_ws_pcdata_single, pugi::encoding_utf8);
    for (pugi::xml_node s : doc.child("map").children("string")) out.emplace_back(s.attribute("name").value(), s.child_value());
    return out;
}

std::string escape(std::string_view s) {
    std::string out;
    out.reserve(s.size());
    for (char c : s) {
        switch (c) {
        case '&': out += "&amp;"; break;
        case '<': out += "&lt;"; break;
        case '>': out += "&gt;"; break;
        case '"': out += "&quot;"; break;
        default:
            if ((unsigned char)c < 0x20) out += "&#" + std::to_string((int)c) + ";";
            else out.push_back(c);
        }
    }
    return out;
}

std::string serialize(const Entries& entries) {
    std::string out = "<?xml version='1.0' encoding='utf-8' standalone='yes' ?>\n<map>\n";
    for (auto& [name, text] : entries) out += "    <string name=\"" + escape(name) + "\">" + escape(text) + "</string>\n";
    out += "</map>\n";
    return out;
}

}  // namespace soa::prefs_xml
