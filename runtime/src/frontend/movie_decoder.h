#pragma once
// Movie decoding on FFmpeg's libraries (libavformat, libavcodec, libswresample: vcpkg.json's ffmpeg,
// an LGPL build): the movie player's decoder (frontend/movie.cpp) and the comparison tool
// (tools/movie_check). Self-contained: no runtime state, errors are returned as text.
//
// The bytes come from a MovieSource through a custom AVIOContext: a range of memory (a stored
// entry of an APK or of the data zip, in place in its mapping; or an inflated copy) or a host file.
// No ffmpeg protocol, no temporary file.
//
// A MovieStream demuxes and decodes ONE stream kind of a movie (its first video or audio stream).
// The player opens one per kind on the same source, each with its own reader, so the video and
// the audio are read independently, as the two ffmpeg processes it replaces did.
#include <cstdint>
#include <functional>
#include <memory>
#include <string>
#include <vector>

namespace soa {

class MovieSource {
public:
    MovieSource() = default;
    // `size` bytes at `data`, valid while `keep` (if any) is held.
    static MovieSource memory(const uint8_t* data, uint64_t size, std::shared_ptr<const void> keep = {});
    // A copy owned by the source (an inflated zip entry).
    static MovieSource owned(std::vector<uint8_t> bytes);
    // The host file at `path`, the whole of it.
    static MovieSource file(std::string path);

    bool is_file() const { return !file_.empty(); }
    const std::string& path() const { return file_; }
    const uint8_t* data() const { return data_; }
    uint64_t size() const { return size_; }

private:
    const uint8_t* data_ = nullptr;
    uint64_t size_ = 0;
    std::shared_ptr<const void> keep_;
    std::string file_;
};

// A decoded picture: 8-bit 4:2:0 planes (yuv420p), packed without padding: Y (w*h), then U and V
// (((w+1)/2) * ((h+1)/2) each).
struct MovieFrame {
    int w = 0, h = 0;
    std::vector<uint8_t> planes;
    int chroma_w() const { return (w + 1) / 2; }
    int chroma_h() const { return (h + 1) / 2; }
};

class MovieStream {
public:
    enum class Kind { video, audio };
    // The audio format next_audio() delivers: interleaved float stereo at this rate.
    static constexpr int kAudioRate = 48000;

    MovieStream();
    ~MovieStream();
    MovieStream(const MovieStream&) = delete;
    MovieStream& operator=(const MovieStream&) = delete;

    // Opens `src`'s first stream of `kind` and its decoder. `interrupt` (optional) is polled while
    // reading; returning true aborts (next_* then return false). False with *err when the source
    // can't be read, has no such stream or no decoder for it.
    bool open(const MovieSource& src, Kind kind, std::string* err, std::function<bool()> interrupt = {});

    // Video: the stream's size (the cropped picture, as ffprobe's width / height) and its
    // r_frame_rate (as ffprobe's; 0 when unknown).
    int width() const;
    int height() const;
    double frame_rate() const;

    // Video: the next picture in presentation order. False at the end (after the decoder's
    // delayed pictures) or on an error (*err, if given, says which).
    bool next_video(MovieFrame& out, std::string* err = nullptr);
    // Audio: the next decoded samples, interleaved float stereo at kAudioRate (replaces `out`).
    // False at the end or on an error.
    bool next_audio(std::vector<float>& out, std::string* err = nullptr);

    // FFmpeg's version and license, e.g. "9.0.2 (LGPL version 2.1 or later)".
    static std::string library_info();

private:
    struct Impl;
    std::unique_ptr<Impl> d_;
};

}  // namespace soa
