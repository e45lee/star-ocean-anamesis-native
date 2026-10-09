// Unit tests of the gacha (api/gacha/gacha.h). Run in --selftest; not differential (the server has no guest counterpart). Test names are
// their seeds (testing.h): gacha/... since R18 (were server/gacha-stepup-box, server/enable-events-gachas).
#include <unistd.h>

#include <set>
#include <string>
#include <vector>

#include <algorithm>

#include "api/events/enable_events.h"
#include "api/gacha/gacha.h"
#include "soaserver/config.h"
#include "soaserver/fids.h"
#include "soaserver/events.h"
#include "soaserver/native_test.h"
#include "testing/scratch.h"

namespace soa::server {
namespace {

using ext::Row;

NATIVE_TEST("gacha/stepup-box") {
    ScratchServer S(t.rand_u64());
    if (!S.ok) return;
    Server& sv = S.sv;
    RequestContext rc = sv.new_request();  // for the handlers called directly
    ext::Ctx ctx = sv.make_ctx(rc);
    S.set_clock("2021-05-25 12:00:00");
    u32 s1 = S.id("master_gacha", "gacha_pickup_role_1011"), s2 = S.id("master_gacha", "gacha_pickup_role_1012"),
        s3 = S.id("master_gacha", "gacha_pickup_role_1013");
    auto chain = stepup_chain(ctx, s2);
    t.expect_eq(chain.size(), (size_t)10, "chain of 10");
    t.expect_eq(chain[0], s1, "step 1 first");
    sv.st.q("update player set free_coin = 100000", {});
    // step 3 before step 1: refused (10403), no coins taken
    t.expect_eq(S.call(Request{"Gacha", fids::kGacha, {s3}, {"x"}, {}}), 10403u, "out of order");
    t.expect_eq((u32)sv.st.one("select free_coin from player", {}), 100000u, "no coins taken");
    t.expect_eq(S.call(Request{"Gacha", fids::kGacha, {s1}, {"x"}, {}}), 0u, "step 1");
    t.expect_eq((u32)sv.st.one("select next_id from stepup where head = ?", {s1}), s2, "at step 2");
    t.expect_eq((u32)sv.st.one("select free_coin from player", {}), 100000u - (u32)sv.m.one("select bulk_coin from master_gacha where id = ?", {s1}),
                "step 1 price");
    t.expect_eq(S.call(Request{"Gacha", fids::kGacha, {s2}, {"x"}, {}}), 0u, "step 2");
    t.expect_eq((u32)sv.st.one("select next_id from stepup where head = ?", {s1}), s3, "at step 3");
    // (b) the client's view: a map keyed by step id; the current step open with try_count 0 on
    // it and next = step 4, every other step of the chain closed
    {
        Value v = stepup_gacha_info(ctx);
        if (v.type != Value::Map) return t.fail("StepUpGacha is not a map");
        const Value* e = v.find(std::to_string(s3));
        if (!e) return t.fail("StepUpGacha has no entry for the current step");
        t.expect_eq((u32)e->get_u("master_gacha_id"), s3, "StepUpGacha.master_gacha_id = the key");
        t.expect_eq((u32)e->get_u("try_count"), 0u, "no draw on step 3 yet");
        t.expect_eq((u32)e->get_u("next_master_gacha_id"), chain[3], "next = step 4");
        t.expect_eq(e->find("is_close")->b, false, "step 3 open");
        int open = 0;
        for (u32 s : chain) {
            const Value* x = v.find(std::to_string(s));
            if (!x) t.fail("step %u missing", s);
            else if (!x->find("is_close")->b) open++;
        }
        t.expect_eq(open, 1, "one open step per chain");
        // a chain never drawn is listed at step 1 (the clock is inside 1021's window too)
        u32 other = S.id("master_gacha", "gacha_pickup_role_1021");
        if (sv.m.one("select stepup_number from master_gacha where id = ?", {other}) == 1) {
            const Value* o = v.find(std::to_string(other));
            t.expect_eq(o && !o->find("is_close")->b, true, "untouched open chain at step 1");
        }
    }
    // chips: every duplicate of a chip gacha adds chip x chip_rate / 100 of its role's chip item
    if (sv.m.one("select ifnull(universe_chip_flg, 0) from master_gacha where id = ?", {s1})) {
        u64 want = 0;
        sv.st.q("select role_id from gacha_history where duplicate = 1", {}, [&](const Row& h) {
            if (sv.m.one("select ifnull(universe_chip_item_id, 0) from master_role where id = ?", {h.i("role_id")}))
                want += (u64)sv.m.one(
                    "select cast(chip * chip_rate / 100 as integer) from master_universe_chip_gacha_exchange where rank = "
                    "(select rank from master_role where id = ?)",
                    {h.i("role_id")});
        });
        u64 chips = 0;
        sv.st.q("select master_item_id, count from stock", {}, [&](const Row& x) {
            if (sv.m.one("select count(*) from master_role where universe_chip_item_id = ?", {x.i("master_item_id")})) chips += (u64)x.i("count");
        });
        t.expect_eq(chips, want, "chips for the duplicates");
    }
    // Gacha(id, hash, 1) is the single draw (b: CGacha::RequestGacha): coin, 1 unit; (…, 0) the bulk
    {
        u32 perm = S.id("master_gacha", "gacha_role_0001");
        sv.st.q("update player set free_coin = 100000, pay_coin = 0", {});
        std::vector<u8> out;
        t.expect_eq(S.call(Request{"Gacha", fids::kGacha, {perm, 1}, {"x"}, {}}, &out), 0u, "single draw");
        Value r = mp_decode(out);
        const Value* it = r.find("data") ? r.find("data")->find("GachaItems") : nullptr;
        t.expect_eq(it ? (u32)it->arr.size() : 0u, 1u, "one unit");
        t.expect_eq((u32)sv.st.one("select free_coin from player", {}), 100000u - (u32)sv.m.one("select coin from master_gacha where id = ?", {perm}),
                    "the single price");
        out.clear();
        t.expect_eq(S.call(Request{"Gacha", fids::kGacha, {perm, 0}, {"x"}, {}}, &out), 0u, "bulk draw");
        r = mp_decode(out);
        it = r.find("data") ? r.find("data")->find("GachaItems") : nullptr;
        t.expect_eq(it ? (u32)it->arr.size() : 0u, (u32)sv.m.one("select bulk_count from master_gacha where id = ?", {perm}), "bulk units");
    }
    // coins short: 20003 紋章石が不足しています (the code the draw's answer opens the coin shop on)
    sv.st.q("update player set free_coin = 0, pay_coin = 0", {});
    t.expect_eq(S.call(Request{"Gacha", fids::kGacha, {s3}, {"x"}, {}}), 20003u, "coins short");
    t.expect_eq((u32)sv.st.one("select next_id from stepup where head = ?", {s1}), s3, "still at step 3");
    // box gacha: box_event_gacha_yumenonagisa_003 (50 slots, item_coin_294 x 5 per draw, resettable)
    u32 box = S.id("master_gacha", "box_event_gacha_yumenonagisa_003");
    u32 coin = (u32)sv.m.one("select ticket_item_id from master_gacha where id = ?", {box});
    u32 slots = (u32)sv.m.one("select sum(box_count) from master_box_gacha where master_gacha_id = ?", {box});
    t.expect_eq(S.call(Request{"BoxGacha", fids::kBoxGacha, {box, 3}, {}, {}}), 10206u, "no event coins");
    sv.st.q(
        "insert into stock (master_item_id, item_type, count) values (?, 9, 100000)"
        " on conflict(master_item_id) do update set item_type = excluded.item_type, count = excluded.count",
        {coin});
    t.expect_eq(S.call(Request{"BoxGacha", fids::kBoxGacha, {box, 3}, {}, {}}), 0u, "3 draws");
    t.expect_eq((u32)sv.st.one("select sum(drawn) from box_slots where gacha_id = ?", {box}), 3u, "3 slots drawn");
    t.expect_eq((u32)sv.st.one("select count from stock where master_item_id = ?", {coin}), 100000u - 15u, "15 coins");
    // the rest in one request: the draws stop at the box's copies (each once); the ∞ box (the
    // series' last) then refills by itself, counted as a reset
    std::vector<u8> out;
    t.expect_eq(S.call(Request{"BoxGacha", fids::kBoxGacha, {box, 1000}, {}, {}}, &out), 0u, "the rest");
    {
        Value r = mp_decode(out);
        const Value* it = r.find("data") ? r.find("data")->find("BoxGachaItems") : nullptr;
        t.expect_eq(it ? (u32)it->arr.size() : 0u, slots - 3, "the rest: the copies left");
        std::set<u32> ids;
        if (it)
            for (auto& x : it->arr) ids.insert((u32)x.get_u("master_box_gacha_id"));
        t.expect_eq((u32)ids.size(), slots - 3, "each slot once");
    }
    t.expect_eq((u32)sv.st.one("select count(*) from box_slots where gacha_id = ?", {box}), 0u, "the ∞ box refilled");
    t.expect_eq((u32)sv.st.one("select reset_count from box_state where gacha_id = ?", {box}), 1u, "refill counted");
    t.expect_eq(S.call(Request{"BoxGacha", fids::kBoxGacha, {box, 1}, {}, {}}), 0u, "drawn again");
    t.expect_eq(S.call(Request{"ResetBoxGacha", fids::kResetBoxGacha, {box}, {}, {}}), 0u, "reset");
    t.expect_eq((u32)sv.st.one("select count(*) from box_slots where gacha_id = ?", {box}), 0u, "refilled");
    t.expect_eq((u32)sv.st.one("select reset_count from box_state where gacha_id = ?", {box}), 2u, "reset counted");
    // BoxGachaList (b): a map keyed by box id; a series lists its boxes up to the current one,
    // the emptied ones closed; GetGachaInData carries the series open at the clock
    u32 b1 = S.id("master_gacha", "box_event_gacha_yumenonagisa_001"), b2 = S.id("master_gacha", "box_event_gacha_yumenonagisa_002");
    S.set_clock("2020-08-10 12:00:00");
    {
        struct ResetAssets {
            ~ResetAssets() { events::set_asset_check({}); }
        } reset_assets;
        events::set_asset_check([](const std::string&) { return true; });  // the banners present
        Value r = mp_decode(get_gacha_in_data(ctx, Request{"GetGachaInData", 0, {}, {}, {}}));
        const Value* d = r.find("data");
        const Value* bl = d ? d->find("BoxGachaList") : nullptr;
        if (!bl || bl->type != Value::Map) return t.fail("GetGachaInData: BoxGachaList is not a map");
        const Value* e = bl->find(std::to_string(b1));
        t.expect_eq(e && !e->find("is_close")->b &&
                        e->get_u("box_num") == sv.m.one("select sum(box_count) from master_box_gacha where master_gacha_id = ?", {b1}),
                    true, "box 1 of an open series listed, box_num = its copies");
        t.expect_eq(bl->find(std::to_string(b2)) == nullptr, true, "box 2 not yet");
        const Value* su = d->find("StepUpGacha");
        t.expect_eq(su && su->type == Value::Map && !su->map.empty(), true, "step-ups open on 2020-08-10");
    }
    t.expect_eq(S.call(Request{"BoxGacha", fids::kBoxGacha, {b1, 1000}, {}, {}}), 0u, "empty box 1");
    {
        Value l = box_gacha_list_info(ctx, b1);
        const Value *e1 = l.find(std::to_string(b1)), *e2 = l.find(std::to_string(b2));
        t.expect_eq(e1 && e1->find("is_close")->b, true, "box 1 closed");
        t.expect_eq(e2 && !e2->find("is_close")->b &&
                        e2->get_u("box_num") == sv.m.one("select sum(box_count) from master_box_gacha where master_gacha_id = ?", {b2}),
                    true, "box 2 current, full");
        t.expect_eq(e1 ? (u32)e1->get_u("next_master_gacha_id") : 0u, b2, "box 1 -> box 2");
    }
}

// --enable-events (enable_events.h): with the option, every gacha whose name matches the keywords
// is in GetGachaInData at a clock outside its window, with the open window; without it, none that
// the clock doesn't open.
NATIVE_TEST("gacha/enable-events") {
    ScratchServer S(t.rand_u64());
    if (!S.ok) return;
    Server& sv = S.sv;
    RequestContext rc = sv.new_request();  // for the handlers called directly
    ext::Ctx ctx = sv.make_ctx(rc);
    S.set_clock("2026-09-30 12:00:00");
    ServerConfig& opt = config();
    ServerConfig saved = opt;
    ext::Sql em{sv.m.h};
    // every asset present first (the banner images decide which gachas are shown)
    struct ResetAssets {
        ~ResetAssets() { events::set_asset_check({}); }
    } reset_assets;
    events::set_asset_check([](const std::string&) { return true; });
    std::set<u32> want = enable_events::shown_gacha_ids(em, kDefaultEventKeywords);
    if (want.empty()) return t.fail("no gacha matches the default keywords");
    auto listed = [&]() {
        std::set<u32> ids;
        Value r = mp_decode(get_gacha_in_data(ctx, Request{"GetGachaInData", 0, {}, {}, {}}));
        const Value* d = r.find("data");
        const Value* hm = d ? d->find("GachaHashMap") : nullptr;
        if (hm)
            for (auto& kv : hm->map) {
                ids.insert((u32)std::stoul(kv.first));
                const Value* l = kv.second.find("GachaHashList");
                if (l && !l->arr.empty() && want.count((u32)std::stoul(kv.first)) && opt.enable_events) {
                    const Value* c = l->arr[0].find("closed_at");
                    if (!c || c->s != enable_events::kClosedAt) t.fail("gacha %s: closed_at not the open window", kv.first.c_str());
                }
            }
        return ids;
    };
    opt.enable_events = false;
    opt.event_keywords.clear();
    std::set<u32> off = listed();
    int closed_listed = 0;
    for (u32 g : want) {
        std::string c;
        sv.m.q("select ifnull(closed_at, '') as c from master_gacha where id = ?", {g}, [&](const Row& r) { c = r.s("c"); });
        if (!c.empty() && c < "2026-09-30" && off.count(g)) closed_listed++;
    }
    t.expect_eq(closed_listed, 0, "without the option: no closed matching gacha listed");
    opt.enable_events = true;
    std::set<u32> on = listed();
    int missing = 0;
    for (u32 g : want) missing += !on.count(g);
    t.expect_eq(missing, 0, "with the option: every matching gacha listed");
    t.expect_eq(on.size(), off.size() + std::count_if(want.begin(), want.end(), [&](u32 g) { return !off.count(g); }), "nothing else added");
    // no banner images: only the box gachas (reached from their event) are opened
    events::set_asset_check([](const std::string&) { return false; });
    std::set<u32> bare = listed();
    int non_box = 0;
    for (u32 g : want)
        if (bare.count(g) && !off.count(g) && !sv.m.one("select ifnull(is_box, 0) from master_gacha where id = ?", {g})) non_box++;
    t.expect_eq(non_box, 0, "without banner images: no list gacha opened");
    events::set_asset_check([](const std::string&) { return true; });
    // a keyword list of its own replaces the default
    opt.event_keywords = "!";
    t.expect_eq(listed().size(), off.size(), "an empty keyword list opens nothing");
    opt.enable_events = saved.enable_events;
    opt.event_keywords = saved.event_keywords;
}

// The fake-out (is_mutation; gacha.cpp roll_surprise, docs/server-rules.md#gacha-surprise): with
// --gacha-surprise 100 every drawn ★5 unit is one and no other; with 0 none; at 50 about half of
// the ★5 units; the default reads master_global.gacha_mutation (2). The field is a bool on every
// GachaItems entry.
NATIVE_TEST("gacha/surprise") {
    ScratchServer S(t.rand_u64());
    if (!S.ok) return;
    Server& sv = S.sv;
    S.set_clock("2021-05-25 12:00:00");
    const int32_t saved = config().gacha_surprise;
    const u32 perm = S.id("master_gacha", "gacha_role_0001");
    // `draws` bulk draws at `percent`: (★5 units, of them surprises, other units that were surprises)
    struct Counts {
        u32 five = 0, five_surprise = 0, other_surprise = 0, units = 0;
        bool shape = true;
    };
    auto draw = [&](int32_t percent, int draws) {
        config().gacha_surprise = percent;
        Counts c;
        for (int k = 0; k < draws; k++) {
            sv.st.q("update player set free_coin = 100000, pay_coin = 0", {});
            std::vector<u8> out;
            if (S.call(Request{"Gacha", fids::kGacha, {perm, 0}, {"x"}, {}}, &out) != 0) {
                t.fail("draw %d refused", k);
                break;
            }
            Value r = mp_decode(out);
            const Value* items = r.find("data") ? r.find("data")->find("GachaItems") : nullptr;
            if (!items) {
                t.fail("no GachaItems");
                break;
            }
            for (const Value& e : items->arr) {
                const Value* m = e.find("is_mutation");
                if (!m || m->type != Value::Bool) c.shape = false;
                const bool surprise = m && m->type == Value::Bool && m->b;
                const u64 role = e.get_u("master_role_id"), item = e.get_u("master_item_id");
                const int64_t rarity = role ? sv.m.one("select rarity from master_role where id = ?", {role})
                                            : sv.m.one("select rarity from master_item where id = ?", {item});
                c.units++;
                if (rarity >= 5) c.five++, c.five_surprise += surprise;
                else c.other_surprise += surprise;
            }
        }
        return c;
    };
    Counts all = draw(100, 30);
    t.expect_eq(all.shape, true, "is_mutation is a bool on every entry");
    t.expect_eq(all.five > 0, true, "30 bulk draws bring a 5-star unit");
    t.expect_eq(all.five_surprise, all.five, "100: every 5-star unit a surprise");
    t.expect_eq(all.other_surprise, 0u, "100: no other unit");
    Counts none = draw(0, 30);
    t.expect_eq(none.five_surprise + none.other_surprise, 0u, "0: none");
    Counts half = draw(50, 120);
    if (half.five < 20) t.fail("only %u 5-star units in 1200 draws", half.five);
    else if (half.five_surprise * 10 < half.five * 2 || half.five_surprise * 10 > half.five * 8)
        t.fail("50: %u of %u 5-star units", half.five_surprise, half.five);
    t.expect_eq(half.other_surprise, 0u, "50: no other unit");
    t.expect_eq((u32)sv.m.one("select value from master_global where key = 'gacha_mutation'", {}), 2u, "master_global.gacha_mutation");
    Counts dflt = draw(-1, 40);
    t.expect_eq(dflt.other_surprise, 0u, "default: no other unit");
    if (dflt.five && dflt.five_surprise * 4 > dflt.five + 4) t.fail("default (2%%): %u of %u 5-star units", dflt.five_surprise, dflt.five);
    config().gacha_surprise = saved;
}

}  // namespace
}  // namespace soa::server
