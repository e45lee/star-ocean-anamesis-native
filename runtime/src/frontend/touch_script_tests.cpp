// Scripted input paced by frames (frontend/touch_script.h), against a model of the game's input
// path: the guest reads the queue once per frame, the frame after that folds what it read into one
// state (CTouchPanel::Progress / CCocosDirector::InputProgress: a frame whose records hold both the
// down and the up starts no touch, so the tap is lost), then a frame is presented. Also run by
// build/runtime/soaruntime_tests.
#include <cstdint>
#include <vector>

#include "soaruntime/core/selftest.h"
#include "frontend/touch_script.h"

namespace soa {
namespace {

using namespace touch_script;

struct Game {
    int frame_ms;             // the frame time (0: no frames at all, the guest reads nothing)
    std::vector<Step> queue;  // pushed, not read
    std::vector<Step> read;   // read, folded into the next frame
    uint64_t pushed = 0, consumed = 0, frames = 0;
    bool touching = false;  // a touch began (the director's +100)
    int taps = 0, lost = 0, moves = 0, backs = 0;
    bool back_level = false;
    float end_x = -1;

    uint64_t send(const Step& s) {
        queue.push_back(s);
        return ++pushed;
    }
    void frame() {
        // Progress: this frame's records, in order, into the drag state.
        int state = -1;  // -1 none, 0 began, 1 moved, 2 ended
        float x = 0;
        for (auto& s : read) {
            if (s.kind == Step::Key) {
                back_level = s.action == 0;
                continue;
            }
            if (s.action == 0) state = 0;
            else if (s.action == 2) state = state == 0 ? 0 : 1;  // a move in the frame of the down is dropped
            else state = 2;
            x = s.x;
        }
        if (back_level) backs++;  // PadDroid::m_bBack sampled once per frame
        if (state == 0) touching = true;
        else if (state == 1 && touching) moves++;
        else if (state == 2) {
            if (touching) taps++, end_x = x;
            else lost++;
            touching = false;
        }
        read.clear();
        // The guest reads the queue (Aska::TouchCallback); seen by the next frame's Progress.
        read = std::move(queue);
        queue.clear();
        consumed = pushed;
        frames++;
    }
};

// Plays `steps` against a game at `frame_ms` (frames at multiples of it, polls every 10 ms);
// returns the game; `elapsed_ms`: when the sequence finished.
Game play(std::vector<Step> steps, int frame_ms, int* elapsed_ms = nullptr, int* timeouts = nullptr) {
    Game g{frame_ms};
    Player p;
    auto send = [&](const Step& s) { return g.send(s); };
    Clock c;
    int64_t t = 0, next_frame = 0;
    p.start(steps, c, send);
    for (; t < 20000 && p.active(); t += 10) {
        for (; frame_ms && t >= next_frame; next_frame += frame_ms) g.frame();
        c.now_ms = t, c.frames = g.frames, c.consumed = g.consumed;
        p.poll(c, send);
        if (!p.active() && elapsed_ms && !*elapsed_ms) *elapsed_ms = (int)t;
    }
    for (int i = 0; i < 3 && frame_ms; i++) g.frame();  // the last events reach Progress
    if (timeouts) *timeouts = p.timeouts();
    return g;
}

// The fixed holds before frame pacing, as raw timelines: events sent at the given times (ms),
// whether the guest read the one before or not; frames every frame_ms from 0.
Game raw(std::vector<std::pair<int, Step>> events, int frame_ms) {
    Game g{frame_ms};
    size_t i = 0;
    for (int t = 0, next_frame = 0; t < 5000; t += 10) {
        for (; t >= next_frame; next_frame += frame_ms) g.frame();
        for (; i < events.size() && events[i].first <= t; i++) g.send(events[i].second);
    }
    return g;
}

RUNTIME_TEST("frontend/touch-tap-any-frame-rate") {
    // The model reproduces the loss: an 80 ms hold at 4 fps puts the down and the up in one frame.
    auto s = tap(10, 20);
    Game old = raw({{1000, s[0]}, {1080, s[1]}}, 250);
    t.expect_eq(old.lost, 1, "an 80 ms tap at 4 fps is lost (the model)");
    old = raw({{1000, s[0]}, {1080, s[1]}}, 40);
    t.expect_eq(old.taps, 1, "an 80 ms tap at 25 fps is taken (the model)");
    for (int fm : {10, 16, 33, 50, 80, 100, 150, 250, 400, 700}) {
        int elapsed = 0;
        Game g = play(tap(10, 20), fm, &elapsed);
        if (g.taps != 1 || g.lost != 0) t.fail("tap at %d ms frames: %d taps, %d lost", fm, g.taps, g.lost);
        if (elapsed < kTapMs) t.fail("tap at %d ms frames released after %d ms (< %d)", fm, elapsed, kTapMs);
        if (fm <= 16 && elapsed > 100) t.fail("tap at %d ms frames held %d ms (fast frames: about %d)", fm, elapsed, kTapMs);
    }
}

RUNTIME_TEST("frontend/touch-tap-waits-for-read-and-frames") {
    Game g{0};
    Player p;
    auto send = [&](const Step& s) { return g.send(s); };
    Clock c;
    p.start(tap(1, 2), c, send);
    t.expect_eq(g.pushed, (uint64_t)1, "the down sent at once");
    c.now_ms = 500, c.frames = 10;  // time and frames, but the guest hasn't read the down
    p.poll(c, send);
    t.expect_eq(g.pushed, (uint64_t)1, "held while the down is unread");
    c.consumed = 1;  // read now; frames counted from here
    p.poll(c, send);
    c.frames = 12;
    p.poll(c, send);
    t.expect_eq(g.pushed, (uint64_t)1, "held for the third frame after the read");
    c.frames = 13;
    p.poll(c, send);
    t.expect_eq(g.pushed, (uint64_t)2, "released three frames after the read");
    t.expect_eq(p.active(), false, "done");
    // Frames but not the time: a fast client still holds kTapMs.
    p.start(tap(1, 2), c, send);
    c.consumed = 3, c.now_ms = 510;
    p.poll(c, send);  // read
    c.frames += 3, c.now_ms = 520;
    p.poll(c, send);
    t.expect_eq(g.pushed, (uint64_t)3, "held for the minimum time");
    c.now_ms = 500 + kTapMs;
    p.poll(c, send);
    t.expect_eq(g.pushed, (uint64_t)4, "released after the minimum time");
    // A step taken by a host-drawn page (sequence 0) counts as read at once.
    int n = 0;
    auto page = [&](const Step&) { n++; return (uint64_t)0; };
    p.start(tap(1, 2), c, page);
    p.poll(c, page);
    c.frames += 3, c.now_ms += kTapMs;
    p.poll(c, page);
    t.expect_eq(n, 2, "a page's tap released on frames and time");
}

RUNTIME_TEST("frontend/touch-gives-up-without-frames") {
    int elapsed = 0, timeouts = 0;
    Game g = play(tap(1, 2), 0, &elapsed, &timeouts);
    t.expect_eq(g.pushed, (uint64_t)2, "the up sent without frames");
    t.expect_eq(timeouts, 1, "counted as a timeout");
    if (elapsed < kTapMs + kMaxWaitMs || elapsed > kTapMs + kMaxWaitMs + 20) t.fail("gave up after %d ms", elapsed);
}

RUNTIME_TEST("frontend/touch-drag-and-back") {
    for (int fm : {16, 100, 250}) {
        for (float ms : {300.f, 800.f}) {
            Game g = play(drag(100, 0, 300, 0, ms), fm);
            if (g.taps != 1 || g.lost != 0) t.fail("%g ms drag at %d ms frames: began/ended %d, lost %d", ms, fm, g.taps, g.lost);
            if (g.end_x != 300) t.fail("%g ms drag at %d ms frames ended at x %g", ms, fm, g.end_x);
        }
        auto swipe = drag(100, 0, 300, 0, 300);
        t.expect_eq(swipe.back().after_read || swipe.back().min_ms, false, "a swipe's up follows its last move at once");
        Game g = play(swipe, fm);
        if (g.taps != 1 || g.lost != 0) t.fail("drag at %d ms frames: began/ended %d, lost %d", fm, g.taps, g.lost);
        if (g.end_x != 300) t.fail("drag at %d ms frames ended at x %g", fm, g.end_x);
        if (fm <= 100 && g.moves < 1) t.fail("drag at %d ms frames: no move frame", fm);
        Game b = play(key(4), fm);
        if (b.backs < 1) t.fail("back at %d ms frames not seen", fm);
    }
    Game b = raw({{1010, key(4)[0]}, {1010, key(4)[1]}}, 100);
    t.expect_eq(b.backs, 0, "back down/up at once is lost (the model)");
}

}  // namespace
}  // namespace soa
