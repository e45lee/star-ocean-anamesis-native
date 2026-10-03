// Scripted input paced by the game's frames (frontend/touch_script.h).
#include "frontend/touch_script.h"

#include <algorithm>

#include "core/log.h"

namespace soa::touch_script {

std::vector<Step> tap(float x, float y) {
    Step down, up;
    down.action = 0, down.x = x, down.y = y;
    up.action = 1, up.x = x, up.y = y;
    up.min_ms = kTapMs, up.min_frames = kTapFrames;
    return {down, up};
}

std::vector<Step> drag(float x1, float y1, float x2, float y2, float ms) {
    std::vector<Step> s;
    Step down;
    down.action = 0, down.x = x1, down.y = y1;
    s.push_back(down);
    int steps = std::max(10, (int)(ms / 30));
    for (int i = 1; i <= steps; i++) {
        Step m;
        m.action = 2;
        m.x = x1 + (x2 - x1) * i / steps, m.y = y1 + (y2 - y1) * i / steps;
        m.min_ms = 30;
        m.min_frames = i == 1 ? 1 : 0;  // the down seen before the finger moves
        s.push_back(m);
    }
    Step up;
    up.action = 1, up.x = x2, up.y = y2;
    if (ms > 300) up.min_ms = 200, up.min_frames = kTapFrames;
    else up.after_read = false;
    s.push_back(up);
    return s;
}

std::vector<Step> key(int keycode) {
    Step down, up;
    down.kind = up.kind = Step::Key;
    down.keycode = up.keycode = keycode;
    down.action = 0, up.action = 1;
    up.min_ms = kTapMs, up.min_frames = kTapFrames;
    return {down, up};
}

void Player::start(std::vector<Step> steps, const Clock& c, const Send& send) {
    if (active()) LOGW("control", "input sequence cut short by the next one");
    steps_ = std::move(steps);
    next_ = 0;
    if (active()) send_next(c, send);
}

void Player::send_next(const Clock& c, const Send& send) {
    const Step& s = steps_[next_++];
    seq_ = send(s);
    sent_ms_ = c.now_ms;
    read_ = false;
    read_frames_ = 0;
}

void Player::poll(const Clock& c, const Send& send) {
    while (active()) {
        const Step& s = steps_[next_];
        if (!read_ && c.consumed >= seq_) read_ = true, read_frames_ = c.frames;
        int64_t waited = c.now_ms - sent_ms_;
        uint64_t frames = read_ ? c.frames - read_frames_ : 0;
        bool due = waited >= s.min_ms && (!paced_ || !s.after_read || (read_ && frames >= (uint64_t)s.min_frames));
        if (!due) {
            if (waited < s.min_ms + kMaxWaitMs) return;
            timeouts_++;
            LOGW("control", "input step sent after %lld ms without %s (%llu of %d frames)", (long long)waited,
                 read_ ? "the frames" : "the guest reading the previous event", (unsigned long long)frames, s.min_frames);
        }
        if (next_ + 1 == steps_.size()) last_frames_ = frames, last_ms_ = waited;
        send_next(c, send);
    }
}

}  // namespace soa::touch_script
