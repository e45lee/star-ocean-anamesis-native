#include "frontend/movie_decoder.h"

#include <cstdio>
#include <cstring>
#include <mutex>

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/channel_layout.h>
#include <libavutil/pixdesc.h>
#include <libswresample/swresample.h>
}

namespace soa {

MovieSource MovieSource::memory(const uint8_t* data, uint64_t size, std::shared_ptr<const void> keep) {
    MovieSource s;
    s.data_ = data;
    s.size_ = size;
    s.keep_ = std::move(keep);
    return s;
}

MovieSource MovieSource::owned(std::vector<uint8_t> bytes) {
    auto v = std::make_shared<std::vector<uint8_t>>(std::move(bytes));
    return memory(v->data(), v->size(), v);
}

MovieSource MovieSource::file(std::string path) {
    MovieSource s;
    s.file_ = std::move(path);
    return s;
}

namespace {

std::string av_err(int r) {
    char buf[AV_ERROR_MAX_STRING_SIZE] = {};
    av_strerror(r, buf, sizeof buf);
    return buf;
}

// The custom AVIOContext's reader: a position in a memory range or a FILE*.
struct Reader {
    MovieSource src;
    FILE* f = nullptr;
    uint64_t size = 0, pos = 0;

    bool open() {
        if (!src.is_file()) {
            size = src.size();
            return src.data() != nullptr || size == 0;
        }
        f = fopen(src.path().c_str(), "rb");
        if (!f) return false;
#ifdef _WIN32
        _fseeki64(f, 0, SEEK_END);
        size = (uint64_t)_ftelli64(f);
        _fseeki64(f, 0, SEEK_SET);
#else
        fseeko(f, 0, SEEK_END);
        size = (uint64_t)ftello(f);
        fseeko(f, 0, SEEK_SET);
#endif
        return true;
    }
    ~Reader() {
        if (f) fclose(f);
    }

    static int read(void* opaque, uint8_t* buf, int n) {
        auto* r = (Reader*)opaque;
        if (r->pos >= r->size) return AVERROR_EOF;
        size_t want = (size_t)std::min<uint64_t>((uint64_t)n, r->size - r->pos);
        size_t got;
        if (r->f) {
            got = fread(buf, 1, want, r->f);
            if (got == 0) return ferror(r->f) ? AVERROR(EIO) : AVERROR_EOF;
        } else {
            memcpy(buf, r->src.data() + r->pos, want);
            got = want;
        }
        r->pos += got;
        return (int)got;
    }
    static int64_t seek(void* opaque, int64_t off, int whence) {
        auto* r = (Reader*)opaque;
        whence &= ~AVSEEK_FORCE;
        if (whence == AVSEEK_SIZE) return (int64_t)r->size;
        int64_t to = whence == SEEK_SET ? off : whence == SEEK_CUR ? (int64_t)r->pos + off : whence == SEEK_END ? (int64_t)r->size + off : -1;
        if (to < 0) return AVERROR(EINVAL);
        if (r->f) {
#ifdef _WIN32
            if (_fseeki64(r->f, to, SEEK_SET) != 0) return AVERROR(EIO);
#else
            if (fseeko(r->f, to, SEEK_SET) != 0) return AVERROR(EIO);
#endif
        }
        r->pos = (uint64_t)to;
        return to;
    }
};

void quiet_ffmpeg() {
    // As the ffmpeg command line's "-v error": the library's info and warning lines stay out of the log.
    static std::once_flag once;
    std::call_once(once, [] { av_log_set_level(AV_LOG_ERROR); });
}

}  // namespace

struct MovieStream::Impl {
    Kind kind = Kind::video;
    Reader reader;
    std::function<bool()> interrupt;
    AVIOContext* io = nullptr;
    AVFormatContext* fmt = nullptr;
    AVCodecContext* dec = nullptr;
    SwrContext* swr = nullptr;
    AVPacket* pkt = nullptr;
    AVFrame* frame = nullptr;
    int index = -1;
    bool flushed = false;      // the end of the input was sent to the decoder
    bool swr_drained = false;  // the resampler's tail was taken
    bool failed = false;

    ~Impl() {
        av_frame_free(&frame);
        av_packet_free(&pkt);
        swr_free(&swr);
        avcodec_free_context(&dec);
        avformat_close_input(&fmt);  // a custom pb isn't freed by it (AVFMT_FLAG_CUSTOM_IO)
        if (io) av_freep(&io->buffer);
        avio_context_free(&io);
    }

    static int on_interrupt(void* opaque) {
        auto* d = (Impl*)opaque;
        return d->interrupt && d->interrupt() ? 1 : 0;
    }

    // The decoder's next frame into `frame`: 0, AVERROR_EOF at the end, or another error.
    int receive() {
        for (int errors = 0;;) {
            int r = avcodec_receive_frame(dec, frame);
            if (r == 0 || r == AVERROR_EOF) return r;
            if (r != AVERROR(EAGAIN)) {
                // A decoding error: the ffmpeg program logs it and goes on with the next packet.
                if (on_interrupt(this) || ++errors > 100) return r;
                continue;
            }
            if (flushed) return AVERROR_EOF;
            // Feed the next packet of our stream; at the end of the input, the flush packet (the
            // decoder then returns its delayed frames: B-frame reordering, frame threads).
            for (;;) {
                r = av_read_frame(fmt, pkt);
                if (r < 0) {
                    if (r != AVERROR_EOF && on_interrupt(this)) return r;
                    avcodec_send_packet(dec, nullptr);
                    flushed = true;
                    break;
                }
                if (pkt->stream_index == index) {
                    // A damaged packet is skipped, as the ffmpeg program does (it logs and goes on).
                    avcodec_send_packet(dec, pkt);
                    av_packet_unref(pkt);
                    break;
                }
                av_packet_unref(pkt);
            }
        }
    }
};

MovieStream::MovieStream() : d_(std::make_unique<Impl>()) {}
MovieStream::~MovieStream() = default;

bool MovieStream::open(const MovieSource& src, Kind kind, std::string* err, std::function<bool()> interrupt) {
    quiet_ffmpeg();
    d_ = std::make_unique<Impl>();
    Impl& d = *d_;
    auto fail = [&](const std::string& why) {
        if (err) *err = why;
        d_ = std::make_unique<Impl>();
        d_->failed = true;
        return false;
    };
    d.kind = kind;
    d.interrupt = std::move(interrupt);
    d.reader.src = src;
    if (!d.reader.open()) return fail("can't open " + (src.is_file() ? src.path() : std::string("the movie's bytes")));

    constexpr int kIoBuf = 1 << 16;
    auto* buf = (unsigned char*)av_malloc(kIoBuf);
    if (!buf) return fail("out of memory");
    d.io = avio_alloc_context(buf, kIoBuf, 0, &d.reader, &Reader::read, nullptr, &Reader::seek);
    if (!d.io) {
        av_free(buf);
        return fail("out of memory");
    }
    d.fmt = avformat_alloc_context();
    if (!d.fmt) return fail("out of memory");
    d.fmt->pb = d.io;
    d.fmt->flags |= AVFMT_FLAG_CUSTOM_IO;
    d.fmt->interrupt_callback = {&Impl::on_interrupt, &d};
    int r = avformat_open_input(&d.fmt, nullptr, nullptr, nullptr);  // frees fmt on failure
    if (r < 0) return fail("not a movie: " + av_err(r));
    if ((r = avformat_find_stream_info(d.fmt, nullptr)) < 0) return fail("no stream info: " + av_err(r));

    AVMediaType type = kind == Kind::video ? AVMEDIA_TYPE_VIDEO : AVMEDIA_TYPE_AUDIO;
    const AVCodec* codec = nullptr;
    d.index = av_find_best_stream(d.fmt, type, -1, -1, &codec, 0);
    if (d.index < 0) return fail(kind == Kind::video ? "no video stream" : "no audio stream");
    // Only this stream's packets matter: the demuxer skips the others' (no copy).
    for (unsigned i = 0; i < d.fmt->nb_streams; i++)
        if ((int)i != d.index) d.fmt->streams[i]->discard = AVDISCARD_ALL;
    AVStream* st = d.fmt->streams[d.index];

    d.dec = avcodec_alloc_context3(codec);
    if (!d.dec) return fail("out of memory");
    if ((r = avcodec_parameters_to_context(d.dec, st->codecpar)) < 0) return fail("codec parameters: " + av_err(r));
    d.dec->pkt_timebase = st->time_base;
    // Frame threads: decoding stays bit-exact. A few, not one per core: several clients may run at once.
    d.dec->thread_count = kind == Kind::video ? 4 : 1;
    if ((r = avcodec_open2(d.dec, codec, nullptr)) < 0) return fail(std::string("can't open the ") + codec->name + " decoder: " + av_err(r));

    if (kind == Kind::audio) {
        AVChannelLayout in_layout{}, out_layout{};
        if (d.dec->ch_layout.order == AV_CHANNEL_ORDER_UNSPEC || d.dec->ch_layout.nb_channels == 0)
            av_channel_layout_default(&in_layout, std::max(1, d.dec->ch_layout.nb_channels));
        else
            av_channel_layout_copy(&in_layout, &d.dec->ch_layout);
        av_channel_layout_default(&out_layout, 2);
        r = swr_alloc_set_opts2(&d.swr, &out_layout, AV_SAMPLE_FMT_FLT, kAudioRate, &in_layout, d.dec->sample_fmt, d.dec->sample_rate, 0, nullptr);
        av_channel_layout_uninit(&in_layout);
        av_channel_layout_uninit(&out_layout);
        if (r < 0 || swr_init(d.swr) < 0) return fail("can't set up the audio conversion");
    }
    d.pkt = av_packet_alloc();
    d.frame = av_frame_alloc();
    if (!d.pkt || !d.frame) return fail("out of memory");
    return true;
}

int MovieStream::width() const { return d_->dec ? d_->fmt->streams[d_->index]->codecpar->width : 0; }
int MovieStream::height() const { return d_->dec ? d_->fmt->streams[d_->index]->codecpar->height : 0; }
double MovieStream::frame_rate() const {
    if (!d_->dec) return 0;
    AVRational r = d_->fmt->streams[d_->index]->r_frame_rate;
    return r.num > 0 && r.den > 0 ? av_q2d(r) : 0;
}

bool MovieStream::next_video(MovieFrame& out, std::string* err) {
    Impl& d = *d_;
    if (!d.dec || d.failed || d.kind != Kind::video) return false;
    int r = d.receive();
    if (r < 0) {
        if (r != AVERROR_EOF && err) *err = av_err(r);
        return false;
    }
    AVFrame* f = d.frame;
    if (f->format != AV_PIX_FMT_YUV420P) {
        if (err) *err = std::string("unsupported pixel format ") + std::to_string(f->format);
        av_frame_unref(f);
        d.failed = true;
        return false;
    }
    out.w = f->width;
    out.h = f->height;
    int cw = out.chroma_w(), ch = out.chroma_h();
    out.planes.resize((size_t)out.w * out.h + 2 * (size_t)cw * ch);
    uint8_t* o = out.planes.data();
    for (int y = 0; y < out.h; y++, o += out.w) memcpy(o, f->data[0] + (ptrdiff_t)y * f->linesize[0], out.w);
    for (int p = 1; p <= 2; p++)
        for (int y = 0; y < ch; y++, o += cw) memcpy(o, f->data[p] + (ptrdiff_t)y * f->linesize[p], cw);
    av_frame_unref(f);
    return true;
}

bool MovieStream::next_audio(std::vector<float>& out, std::string* err) {
    Impl& d = *d_;
    if (!d.dec || d.failed || d.kind != Kind::audio) return false;
    for (;;) {
        int r = d.receive();
        if (r == 0) {
            int cap = swr_get_out_samples(d.swr, d.frame->nb_samples);
            out.resize((size_t)std::max(cap, 0) * 2);
            uint8_t* dst = (uint8_t*)out.data();
            int n = swr_convert(d.swr, &dst, cap, (const uint8_t**)d.frame->extended_data, d.frame->nb_samples);
            av_frame_unref(d.frame);
            if (n < 0) {
                if (err) *err = "audio conversion: " + av_err(n);
                d.failed = true;
                return false;
            }
            out.resize((size_t)n * 2);
            if (n > 0) return true;
            continue;
        }
        if (r != AVERROR_EOF) {
            if (err) *err = av_err(r);
            return false;
        }
        // The end: what the resampler still holds (nothing when the rate doesn't change).
        if (d.swr_drained) return false;
        d.swr_drained = true;
        int cap = swr_get_out_samples(d.swr, 0);
        if (cap <= 0) return false;
        out.resize((size_t)cap * 2);
        uint8_t* dst = (uint8_t*)out.data();
        int n = swr_convert(d.swr, &dst, cap, nullptr, 0);
        if (n <= 0) return false;
        out.resize((size_t)n * 2);
        return true;
    }
}

std::string MovieStream::library_info() {
    unsigned v = avcodec_version();
    return std::string(av_version_info()) + " (libavcodec " + std::to_string(AV_VERSION_MAJOR(v)) + "." + std::to_string(AV_VERSION_MINOR(v)) + "." +
           std::to_string(AV_VERSION_MICRO(v)) + ", " + avcodec_license() + ")";
}

}  // namespace soa
