// movie_check: decodes a movie with the movie player's decoder (runtime/src/frontend/movie_decoder.cpp,
// FFmpeg's libraries) and writes what it decoded, for tools/movie_compare.py to compare with the
// ffmpeg program's output.
//
//   movie_check SOURCE --info          size, frame rate, picture and sample counts, FFmpeg's version
//   movie_check SOURCE --yuv           every picture's yuv420p planes (= ffmpeg -f rawvideo -pix_fmt yuv420p)
//   movie_check SOURCE --audio         the sound as f32le stereo 48 kHz (= ffmpeg -f f32le -ac 2 -ar 48000)
//   movie_check SOURCE --rgba N [STEP] N pictures as RGBA (every STEP-th from the first; STEP 1), turned
//                                      upright, converted the way the player's shader converts them
//                                      (frontend/movie.cpp kFs)
//
// SOURCE is how the player reads a movie (MovieSource):
//   file:PATH                          a file (a guest file path, a download folder's file)
//   zip:ARCHIVE:ENTRY                  a zip's entry in place (stored) or inflated: an APK's
//                                      assets/builtin_data/Movie/*.mp4
//   tree:FOLDER_OR_ZIP:REL             a download tree's file (soa/file_tree.h): a folder's file, or the
//                                      data zip's entry read in place
#include <soa/file_tree.h>
#include <soa/zip.h>

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <string>

#include "soaruntime/frontend/movie_decoder.h"

#ifdef _WIN32
#include <fcntl.h>
#include <io.h>
#endif

using namespace soa;

namespace {

[[noreturn]] void die(const std::string& msg) {
    fprintf(stderr, "movie_check: %s\n", msg.c_str());
    exit(1);
}

// Keeps the archive / tree open for the source's lifetime.
std::shared_ptr<ZipArchive> g_zip;
std::shared_ptr<const FileTree> g_tree;

MovieSource open_source(const std::string& spec) {
    auto split = [&](size_t from) {
        size_t c = spec.find(':', from);
        if (c == std::string::npos) die("bad SOURCE " + spec);
        return c;
    };
    if (spec.rfind("file:", 0) == 0) return MovieSource::file(spec.substr(5));
    if (spec.rfind("zip:", 0) == 0) {
        size_t c = split(4);
        g_zip = std::make_shared<ZipArchive>();
        if (!g_zip->open(spec.substr(4, c - 4))) die("can't open the zip " + spec.substr(4, c - 4));
        const ZipArchive::Entry* e = g_zip->find(spec.substr(c + 1));
        if (!e) die("no entry " + spec.substr(c + 1));
        if (const uint8_t* p = g_zip->stored_data(*e)) {
            fprintf(stderr, "movie_check: a stored entry, read in place\n");
            return MovieSource::memory(p, e->size, g_zip);
        }
        std::vector<uint8_t> data;
        if (!g_zip->extract(*e, data)) die("can't inflate " + spec.substr(c + 1));
        fprintf(stderr, "movie_check: a compressed entry, inflated\n");
        return MovieSource::owned(std::move(data));
    }
    if (spec.rfind("tree:", 0) == 0) {
        size_t c = split(5);
        std::string err;
        g_tree = FileTree::open(spec.substr(5, c - 5), &err);
        if (!g_tree) die(err);
        std::string rel = spec.substr(c + 1);
        FileTree::Loc loc;
        if (!g_tree->locate(rel, &loc)) die("no file " + rel);
        if (const ZipArchive* zip = g_tree->zip()) {
            const ZipArchive::Entry* e = zip->find(g_tree->prefix() + rel);
            if (const uint8_t* p = e ? zip->stored_data(*e) : nullptr) {
                fprintf(stderr, "movie_check: the tree's zip entry, read in place\n");
                return MovieSource::memory(p, e->size, g_tree);
            }
            std::vector<uint8_t> data;
            if (!g_tree->read(rel, data)) die("can't read " + rel);
            return MovieSource::owned(std::move(data));
        }
        return MovieSource::file(loc.file);
    }
    die("bad SOURCE " + spec + " (file:, zip: or tree:)");
}

void put(const void* p, size_t n) {
    if (fwrite(p, 1, n, stdout) != n) die("write failed");
}

// frontend/movie.cpp kFs, on the CPU: BT.601 limited range, the 2x2 block's chroma, the picture turned
// 90 degrees counter-clockwise when it is portrait. GL stores a fragment's float as round(x * 255).
void to_rgba(const MovieFrame& f, std::vector<uint8_t>& out, int& ow, int& oh) {
    bool rot = f.h > f.w;
    ow = rot ? f.h : f.w, oh = rot ? f.w : f.h;
    out.resize((size_t)ow * oh * 4);
    const uint8_t* Y = f.planes.data();
    const uint8_t* U = Y + (size_t)f.w * f.h;
    const uint8_t* V = U + (size_t)f.chroma_w() * f.chroma_h();
    auto unorm = [](float x) { return (uint8_t)std::lround(std::fmin(std::fmax(x, 0.0f), 1.0f) * 255.0f); };
    for (int dy = 0; dy < oh; dy++)
        for (int dx = 0; dx < ow; dx++) {
            int sx = rot ? f.w - 1 - dy : dx, sy = rot ? dx : dy;
            float y = 1.1643836f * (Y[(size_t)sy * f.w + sx] / 255.0f - 0.0627451f);
            float u = U[(size_t)(sy / 2) * f.chroma_w() + sx / 2] / 255.0f - 0.5019608f;
            float v = V[(size_t)(sy / 2) * f.chroma_w() + sx / 2] / 255.0f - 0.5019608f;
            uint8_t* o = &out[((size_t)dy * ow + dx) * 4];
            o[0] = unorm(y + 1.5960268f * v);
            o[1] = unorm(y - 0.3917623f * u - 0.8129676f * v);
            o[2] = unorm(y + 2.0172321f * u);
            o[3] = 255;
        }
}

}  // namespace

int main(int argc, char** argv) {
    if (argc < 3) die("usage: movie_check SOURCE --info | --yuv | --audio | --rgba N   (see the source's header)");
#ifdef _WIN32
    _setmode(_fileno(stdout), _O_BINARY);
#endif
    MovieSource src = open_source(argv[1]);
    std::string mode = argv[2], err;
    if (mode == "--info") {
        MovieStream v, a;
        if (!v.open(src, MovieStream::Kind::video, &err)) die("video: " + err);
        long frames = 0;
        MovieFrame f;
        while (v.next_video(f, &err)) frames++;
        if (!err.empty()) die("video: " + err);
        long samples = 0;
        if (a.open(src, MovieStream::Kind::audio, &err)) {
            std::vector<float> s;
            while (a.next_audio(s, &err)) samples += (long)s.size() / 2;
            if (!err.empty()) die("audio: " + err);
        }
        printf("width=%d height=%d fps=%.6f frames=%ld samples=%ld ffmpeg=%s\n", v.width(), v.height(), v.frame_rate(), frames, samples,
               MovieStream::library_info().c_str());
    } else if (mode == "--yuv" || mode == "--rgba") {
        long limit = mode == "--rgba" ? (argc > 3 ? atol(argv[3]) : 1) : -1;
        long step = mode == "--rgba" && argc > 4 ? std::max(1L, atol(argv[4])) : 1;
        MovieStream v;
        if (!v.open(src, MovieStream::Kind::video, &err)) die("video: " + err);
        MovieFrame f;
        std::vector<uint8_t> rgba;
        long written = 0;
        for (long k = 0; (limit < 0 || written < limit) && v.next_video(f, &err); k++) {
            if (k % step) continue;
            written++;
            if (mode == "--yuv") {
                put(f.planes.data(), f.planes.size());
            } else {
                int w, h;
                to_rgba(f, rgba, w, h);
                put(rgba.data(), rgba.size());
            }
        }
        if (!err.empty()) die("video: " + err);
    } else if (mode == "--audio") {
        MovieStream a;
        if (!a.open(src, MovieStream::Kind::audio, &err)) die("audio: " + err);
        std::vector<float> s;
        while (a.next_audio(s, &err)) put(s.data(), s.size() * sizeof(float));
        if (!err.empty()) die("audio: " + err);
    } else {
        die("unknown mode " + mode);
    }
    fflush(stdout);
    return 0;
}
