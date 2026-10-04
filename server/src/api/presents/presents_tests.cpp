// Unit tests of the present box lines (present_texts.cpp), on a scratch server seeded from the test seed save
// (--selftest; not differential: the server has no guest counterpart).
#include <algorithm>

#include "soaserver/native_test.h"
#include "soaserver/ext.h"
#include "soaserver/msgpack.h"
#include "testing/module_test.h"

namespace soa::server {
namespace {
using namespace ext;
using module_test::call;
using module_test::master_id;
using module_test::player_load_data;

NATIVE_TEST("presents/present-texts") {
    t.expect_eq(format_present("%s %d日目", "ログインボーナス", 3), std::string("ログインボーナス 3日目"), "template");
    t.expect_eq(format_present("%sより", "X"), std::string("Xより"), "no %d");
    bool ran = with_scratch_server(t.rand_u64(), [&](Ctx& c) {
        c.st.exec("begin");
        // (a) Present_box_1 "%s %d日目": the login bonus stores its line
        add_present(c, 4, 0, 500, kPresentLoginBonus, 1, format_present(text(c.m, "Present_box_1"), "テスト", 2));
        int64_t id = c.st.one("select max(id) from presents", {});
        auto stored = [&](int64_t present_id) {
            std::string text;
            c.st.q("select text from presents where id = ?", {present_id}, [&](const Row& r) { text = r.s("text"); });
            return text;
        };
        t.expect_eq(present_text(c.m, stored(id), kPresentLoginBonus, 1), std::string("テスト 2日目"), "stored line");
        // PLAN-schema S8: the line is the present's text column; a coin present's content_id is NULL
        t.expect_eq(c.st.one("select count(*) from presents where id = ? and content_id is null and text is not null", {id}), (int64_t)1,
                    "text stored, the wallet type's content_id NULL");
        // fallback: a mission clear present names the mission (Present_box_2 "%sより")
        u32 mid = master_id(c, "mc01_001", "master_mission");
        add_present(c, 4, 0, 50, kPresentMissionClear, mid);
        id = c.st.one("select max(id) from presents", {});
        t.expect_eq(c.st.one("select count(*) from presents where id = ? and text is null", {id}), (int64_t)1, "no line: text NULL");
        std::string mt = present_text(c.m, stored(id), kPresentMissionClear, mid);
        if (mt.size() < 4 || mt.substr(mt.size() - 6) != "より") t.fail("mission clear line '%s'", mt.c_str());
        // an item present keeps its content id
        add_present(c, 1, 1234, 1, kPresentMissionClear, mid);
        t.expect_eq(c.st.one("select content_id from presents where id = (select max(id) from presents)", {}), (int64_t)1234, "item content id");
        // anything else: Present_box_99 運営からのプレゼント
        t.expect_eq(present_text(c.m, "", 0, 0), std::string("運営からのプレゼント"), "operator present");
        c.st.exec("rollback");
    });
    if (!ran) return;
}

}  // namespace
}  // namespace soa::server
