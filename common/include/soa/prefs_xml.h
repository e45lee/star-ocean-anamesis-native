#pragma once
// Android SharedPreferences XML files, the string entries (soa_codec; common/src/prefs_xml.cpp): the
// runtime's shared_prefs/<name>.xml (runtime/src/android/prefs.cpp) and the game's Game.xml /
// Aska.xml (Aska::LocalKVS; server/src/state/kvs.cpp) are both this format:
//   <?xml version='1.0' encoding='utf-8' standalone='yes' ?>
//   <map>
//       <string name="NAME">TEXT</string>
//   </map>
// Read with pugixml; written by hand, because the bytes must be the ones Android's
// FastXmlSerializer (XmlUtils.writeMapXml) writes, which pugixml's serializer doesn't reproduce
// (the header's quotes, &#10; and &quot; in text).
#include <string>
#include <string_view>
#include <utility>
#include <vector>

namespace soa::prefs_xml {

using Entries = std::vector<std::pair<std::string, std::string>>;  // name, text (unescaped)

// The <map>'s <string> entries in file order, names and texts unescaped (entities and character
// references decoded). <string name="x" /> is an empty text; other elements (<int>, <boolean>,
// <set>, ...) are skipped. A malformed file gives the entries before the error.
Entries parse(std::string_view xml);

// The file Android writes for these entries: the header line, "<map>", one line per entry (four
// spaces of indentation), "</map>\n". Names and texts are escaped as FastXmlSerializer does: & < > "
// as entities, the control characters below 0x20 as &#N; (a value's line breaks: &#10;).
std::string serialize(const Entries& entries);

// The escaping serialize uses.
std::string escape(std::string_view s);

}  // namespace soa::prefs_xml
