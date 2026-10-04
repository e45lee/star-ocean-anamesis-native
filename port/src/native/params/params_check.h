#pragma once
// The live check of the params natives (soa --live-check params[:every=N][:budget=N][:only=..][:out=FILE]
// [:dump]): a run-both family (native/common/live_run_both.h). Every native runs first, for real; then
// the guest original (its hook's trampoline) runs on the same inputs, or on a private copy of what the
// call changes, and the results are compared:
//   - the parser's getters only read the map: x0 (and x1) of both runs on the same arguments;
//   - a value property's Deserialize: its 0x30 bytes after the native, then put back, the original run
//     on the object, the bytes and the result compared;
//   - CryptString / a string property's Deserialize / GetValue<std::string>: the original runs on a
//     private copy of the destination string (same capacity), compared by size, capacity and bytes;
//   - CParameterElementBase::Deserialize: the sequence of (property, map) Deserialize calls; the
//     original runs with the properties' natives recording instead of deserializing (t_record);
//   - AddProperty: the original runs on a private copy of the property chain.
// Nested natives run unchecked inside a check (live::t_busy). `dump`: also records every
// ElementBase::Deserialize input to OUT.corpus (params_corpus.cpp: the differential test's corpus).
#include <cstring>
#include <vector>

#include "core/cpu.h"
#include "native/common/live_run_both.h"
#include "native/params/params_layout.h"

namespace soa::native::params {

live::RunBothFamily& fam();
using Fn = live::RunBothFamily::Fn;
using Outcome = live::RunBothFamily::Outcome;

// The result registers of a getter.
struct Regs {
    u64 x0 = 0, x1 = 0;
};
// A getter's pair as the guest returns it (params_layout.h ParserResult): x0, and x1 for an 8-byte T.
template <typename T>
Regs ToRegs(ParserResult<T> r) {
    u64 b = 0;
    std::memcpy(&b, &r.value, sizeof(T));
    if constexpr (sizeof(T) == 8) return {b, r.found};
    else return {b | (u64)r.found << (8 * sizeof(T)), 0};
}

// A function that only reads memory: the native's result registers against the original's on the same
// arguments (x0 only, or x0 and x1 when `wide`); a difference that a rerun of both doesn't reproduce
// is a race (another thread wrote the map in between).
template <typename Native>
Regs check_pure(Fn& f, Native native, std::initializer_list<u64> args, bool wide) {
    live::RunBothFamily::Scope scope;
    auto run_guest = [&] {
        GuestResult g = guest_call_raw(f.orig, args.begin(), args.size(), nullptr, 0, 0);
        return Regs{g.x0, wide ? g.x1 : 0};
    };
    auto same = [&](Regs a, Regs b) { return a.x0 == b.x0 && (!wide || a.x1 == b.x1); };
    Regs n = native();
    Regs g = run_guest();
    if (same(n, g)) {
        fam().result(f, Outcome::Ok);
        return n;
    }
    Regs n2 = native(), g2 = run_guest();
    if (same(n2, g2)) {
        fam().result(f, Outcome::Race);
        return n2;
    }
    char m[160];
    snprintf(m, sizeof m, "args %#llx %#llx: native %#llx %#llx guest %#llx %#llx", (unsigned long long)args.begin()[0],
             (unsigned long long)(args.size() > 1 ? args.begin()[1] : 0), (unsigned long long)n2.x0, (unsigned long long)n2.x1,
             (unsigned long long)g2.x0, (unsigned long long)g2.x1);
    fam().result(f, Outcome::Mismatch, m);
    return n2;
}

// ElementBase::Deserialize's check: while t_record is set (the original's run), the properties'
// Deserialize natives append (this, map) here instead of deserializing; while t_trace is set (the
// native's run), the native appends each property it deserializes.
struct PropertyCall {
    const void* property;
    const AMap* map;
    bool operator==(const PropertyCall& o) const { return property == o.property && map == o.map; }
};
extern thread_local std::vector<PropertyCall>* t_record;
extern thread_local std::vector<PropertyCall>* t_trace;

// A private copy of a game string with the same representation (a long one gets its own block of the
// same capacity from the STL allocator; Free with free_copy).
void copy_string(String& dst, const String& src);
void free_copy(String& s);
// "" when the two strings have the same representation (long / short, size, capacity, bytes incl. the
// NUL), else what differs.
std::string diff_strings(const String& native, const String& guest);

}  // namespace soa::native::params
