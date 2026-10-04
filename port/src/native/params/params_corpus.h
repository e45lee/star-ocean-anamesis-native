#pragma once
// The corpus of CParameterElementBase::Deserialize inputs (the differential test's data,
// params/corpus-*): `soa --live-check params:dump:out=FILE` writes every distinct call's input to
// FILE.corpus as it happens (before the native runs): the element's properties (list order, offset
// from the element, vtable symbol, bytes; a string property's string with its capacity) and the map
// (the whole ASON value tree). The test rebuilds each record twice in host memory and deserializes one
// copy with the guest's code and one with the natives.
//
// File: "PRMC" u32 version, then records: u32 byte count, the record (little endian):
//   str element vtable symbol ("" when not a symbol)
//   u32 n, n x { s64 offset, str vtable symbol, u8 kind (0 value, 1 string, 2 other),
//                bytes[0x28] (the property's head: vtable / m_next as 0), then kind 0: bytes[8] value;
//                kind 1: u64 capacity, str bytes }
//   u8 self_linked (the last property's m_next is itself)
//   value tree: u32 kind, then kind 1-4: bytes[8] body; 5: u32 m_length, u8 has data, str data,
//               u8 has cstr, str cstr; 6: u32 n, n x value; 7: u32 n, n x (key value, value);
//               8 / 9: s8 ext type, str bytes; 0 / other: nothing
//   (str = u32 length + bytes)
#include <memory>
#include <string>
#include <vector>

#include "native/params/params_layout.h"

namespace soa::native::params {

bool corpus_on();
void corpus_record(const CParameterElementBase* e, const AMap* map);

// ---- reading (the test) ----

struct CorpusValue {
    u32 kind = 0;
    u8 body[8] = {};
    u32 length = 0;
    bool has_data = false, has_cstr = false;
    std::string data, cstr;
    s8 ext = 0;
    std::vector<CorpusValue> items;  // array elements, or map keys and values alternating
};
struct CorpusProperty {
    s64 offset;
    std::string ztv;
    u8 kind;
    u8 head[0x28];
    u8 value[8];
    u64 capacity;
    std::string bytes;
};
struct CorpusRecord {
    std::string element;
    std::vector<CorpusProperty> props;
    bool self_linked = false;
    CorpusValue map;
};
// The records of a corpus file (false: missing or malformed).
bool corpus_read(const std::string& path, std::vector<CorpusRecord>& out);

// An ASON value tree rebuilt in host memory (strings, pairs and elements owned here).
class HostAson {
public:
    explicit HostAson(const CorpusValue& root);
    const AValue* root() const { return root_; }

private:
    void build(const CorpusValue& v, AValue& out);
    std::vector<std::unique_ptr<u8[]>> blocks_;
    AValue* root_;
};

}  // namespace soa::native::params
