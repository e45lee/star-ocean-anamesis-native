#pragma once
// Scripted input that the game sees at any frame rate: the control commands `tap:`, `drag:` and
// `back` (app/host.cpp run_command) as a sequence of input events, each sent only once the game
// has had the frames to see the one before it.
//
// Why: the game samples input once per logic frame. Aska::TouchCallback (the activity's input hook)
// queues each motion event; the PeripheralManager thread copies them into the panel's records every
// 8 ms; CTouchPanel::Progress, once per logic frame, folds the frame's records into one drag state
// (SetDragBegin: 0, SetDragEnd: 2), and CCocosDirector::InputProgress turns that state into one
// touch event. When the down and the up land in the same frame the state reads "ended" with no
// touch begun, InputProgress drops it and no button sees a press. The Back key is a level
// (PadDroid::m_bBack, set on down, cleared on up) that Progress samples per frame. A fixed 80 ms
// hold lost taps whenever a frame (or a hitch) took longer than that: software GL under load,
// 20-38 fps (docs/testing-software-gl.md).
//
// So each step after the first waits until the event before it was read by the guest
// (InputQueue::consumed) and then `min_frames` frames were presented, and `min_ms` passed since it
// was sent. A step whose wait exceeds `kMaxWaitMs` (no frames: a load, a movie, the keyboard) is
// sent anyway, so the control queue never wedges. Pure logic (no window, no clock of its own):
// the host's main loop feeds it the time and the counters (frontend/touch_script_tests.cpp).
#include <cstdint>
#include <functional>
#include <string>
#include <vector>

namespace soa::touch_script {

struct Step {
    enum Kind { Touch, Key } kind = Touch;
    int action = 0;      // touch: AMOTION_EVENT_ACTION_DOWN 0 / UP 1 / MOVE 2; key: AKEY_EVENT_ACTION_DOWN 0 / UP 1
    float x = 0, y = 0;  // touch: game coordinates
    int keycode = 0;     // key: AKEYCODE_*
    int min_ms = 0;      // at least this long after the previous step was sent
    int min_frames = 0;  // and this many frames presented after the guest read the previous step
};

// The touch hold: a tap's up waits for kTapFrames frames after the guest read the down, and at
// least kTapMs. Three frames, not one: the logic thread's Progress, the 8 ms peripheral copy and the
// RenderThread's present are not in lockstep, so the second frame presented after the read can
// still belong to a logic frame that ran before the copy.
constexpr int kTapMs = 80;
constexpr int kTapFrames = 3;
// Longest wait for a step's frames before it is sent anyway.
constexpr int kMaxWaitMs = 3000;

// What the host reports each poll.
struct Clock {
    int64_t now_ms = 0;     // a steady clock
    uint64_t frames = 0;    // frames presented so far
    uint64_t consumed = 0;  // input events the guest has read so far (InputQueue::consumed)
};

// Sends one event; returns its sequence number in the input queue (InputQueue::push: the count of
// events pushed, this one included), or 0 when it never enters the queue (a host-drawn page took
// it), which counts as read at once.
using Send = std::function<uint64_t(const Step&)>;

// tap:X:Y: down, then up after kTapFrames / kTapMs.
std::vector<Step> tap(float x, float y);
// drag:X1:Y1:X2:Y2:MS: down; moves every 30 ms (at least 10, MS in all), the first one frame after
// the down was read; the up kTapFrames frames after the last move was read (and 200 ms after it
// for a drag slower than 300 ms, as before), so the game sees the last position before the end.
std::vector<Step> drag(float x1, float y1, float x2, float y2, float ms);
// back: the Back key down, then up like a tap's.
std::vector<Step> key(int keycode);

class Player {
public:
    // Starts a sequence (drops one still in flight); its first step is sent at once.
    void start(std::vector<Step> steps, const Clock& c, const Send& send);
    // Sends every step that is due. Call it often (the host: every main-loop pass).
    void poll(const Clock& c, const Send& send);
    bool active() const { return next_ < steps_.size(); }
    // Off: each step waits min_ms only, the fixed holds before frame pacing (the test hook
    // input-pacing:0 reproduces the lost taps with it).
    void set_paced(bool on) { paced_ = on; }
    // Steps sent because kMaxWaitMs ran out (also logged).
    int timeouts() const { return timeouts_; }
    // For the log: frames and ms the last finished sequence's final step waited.
    uint64_t last_frames() const { return last_frames_; }
    int64_t last_ms() const { return last_ms_; }

private:
    void send_next(const Clock& c, const Send& send);

    std::vector<Step> steps_;
    size_t next_ = 0;
    bool paced_ = true;
    int64_t sent_ms_ = 0;     // when the previous step was sent
    uint64_t seq_ = 0;        // its sequence number
    bool read_ = false;       // the guest has read it
    uint64_t read_frames_ = 0;  // frames presented when that was first seen
    int timeouts_ = 0;
    uint64_t last_frames_ = 0;
    int64_t last_ms_ = 0;
};

}  // namespace soa::touch_script
