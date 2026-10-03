// Unit tests of the SQL wrapper's typed ids (soaserver/sql.h, soaserver/ids.h; PLAN-readability
// R12). Run in --selftest; not differential (the server has no guest counterpart).
#include <optional>
#include <type_traits>

#include "soaserver/ids.h"
#include "soaserver/native_test.h"
#include "soaserver/sql.h"

namespace soa::server {
namespace {

// No implicit conversion between kinds, nor from or to a plain number.
static_assert(!std::is_convertible_v<RoleId, CharacterUid>);
static_assert(!std::is_constructible_v<CharacterUid, RoleId>);
static_assert(!std::is_constructible_v<CharacterUid, ItemUid>);
static_assert(!std::is_convertible_v<uint64_t, CharacterUid>);
static_assert(!std::is_convertible_v<CharacterUid, uint64_t>);
static_assert(std::is_constructible_v<CharacterUid, uint64_t>);  // explicitly

NATIVE_TEST("server/sql-typed-ids") {
    sql::Sql db;
    if (!db.open(":memory:", false)) return t.fail("open");
    db.exec("create table t (k integer primary key, a integer)");
    std::optional<CharacterUid> none, some = CharacterUid(0x7e000003);
    db.q("insert into t (k, a) values (1, ?), (2, ?), (3, ?)", {none, some, ItemUid(0x7d000001)});
    t.expect_eq(db.one("select count(*) from t where a is null", {}), (int64_t)1, "an empty optional binds NULL");
    t.expect_eq(db.one("select a from t where k = 2", {}), (int64_t)0x7e000003, "a present one its number");
    db.q("select a from t where k = 1", {}, [&](const sql::Row& row) {
        t.expect_eq(row.opt<CharacterUid>("a").has_value(), false, "NULL reads as none");
        t.expect_eq((uint64_t)row.id<CharacterUid>("a").v, (uint64_t)0, "NULL reads as id 0 through id()");
    });
    db.q("select a from t where k = 3", {}, [&](const sql::Row& row) {
        t.expect_eq((uint64_t)row.id<ItemUid>("a").v, (uint64_t)0x7d000001, "id()");
        t.expect_eq((uint64_t)or_zero(row.opt<ItemUid>("a")), (uint64_t)0x7d000001, "opt()");
    });
    t.expect_eq(db.one_opt<CharacterUid>("select a from t where k = 1", {}).has_value(), false, "one_opt: NULL");
    t.expect_eq(db.one_opt<CharacterUid>("select a from t where k = 9", {}).has_value(), false, "one_opt: no row");
    t.expect_eq((uint64_t)or_zero(db.one_opt<CharacterUid>("select a from t where k = ?", {2})), (uint64_t)0x7e000003, "one_opt");
    t.expect_eq((uint64_t)db.one_id<CharacterUid>("select a from t where k = 9", {}).v, (uint64_t)0, "one_id: no row");
    t.expect_eq(nonzero<CharacterUid>(0).has_value(), false, "nonzero(0)");
    t.expect_eq(CharacterUid(1) < CharacterUid(2), true, "ordered");
    db.close();
}

}  // namespace
}  // namespace soa::server
