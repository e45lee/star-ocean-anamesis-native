// The CDN's bundles and answers (soaserver/cdn.h): the "\0ISF" bundle image built from its members,
// its size and SHA-1, and a Response's body (in memory, a file, or a bundle streamed in pieces).
// Our code; what the 3.7.0 client expects is labelled (b) client evidence, the rest (d) assumption
// (docs/server-rules.md#cdn).
#include <fcntl.h>
#include <unistd.h>

#include <algorithm>
#include <cstring>

#include "cdn/files.h"
#include "soaserver/cdn.h"

namespace soa::server::cdn {

using files::align;
using files::read_file;
using files::stat_file;

namespace {

constexpr uint32_t kIsfMagic = 0x46534900;    // "\0ISF" (b: CDownloadNode::UnpackChildData)
constexpr uint32_t kIsfVersion = 0x20130304;  // (b) the highest version the client accepts
constexpr uint64_t kHeaderSize = 16, kEntrySize = 16, kPayloadAlign = 32;

// The bundle's head: header, entries and names; the payload offsets in *offs.
std::vector<uint8_t> bundle_head(const std::vector<Member>& members, std::vector<uint64_t>* offs) {
    uint64_t names = kHeaderSize + kEntrySize * members.size(), end = names;
    for (auto& m : members) end += m.name.size() + 1;
    std::vector<uint64_t> payload_at;
    for (auto& m : members) {
        end = align(end, kPayloadAlign);
        payload_at.push_back(end);
        end += m.len;
    }
    std::vector<uint8_t> head(names);
    auto put = [&](size_t at, uint32_t v) { std::memcpy(&head[at], &v, 4); };
    put(0, kIsfMagic);
    put(4, kIsfVersion);
    put(8, (uint32_t)members.size());
    put(12, 0);
    uint64_t name_at = names;
    for (size_t i = 0; i < members.size(); i++) {
        put(16 + 16 * i, (uint32_t)name_at);
        put(20 + 16 * i, (uint32_t)payload_at[i]);
        put(24 + 16 * i, (uint32_t)members[i].len);
        put(28 + 16 * i, 0);
        name_at += members[i].name.size() + 1;
    }
    for (auto& m : members) head.insert(head.end(), m.name.c_str(), m.name.c_str() + m.name.size() + 1);
    if (offs) *offs = payload_at;
    return head;
}

// Streams the bundle's bytes to `sink`; false when a member can't be read.
template <typename Sink>
bool bundle_stream(const std::vector<Member>& members, Sink&& sink) {
    std::vector<uint64_t> offs;
    std::vector<uint8_t> head = bundle_head(members, &offs);
    sink(head.data(), head.size());
    uint64_t pos = head.size();
    static const uint8_t zeros[64] = {};
    std::vector<uint8_t> buf(1 << 20);
    for (size_t i = 0; i < members.size(); i++) {
        sink(zeros, offs[i] - pos);
        pos = offs[i];
        const Member& m = members[i];
        if (m.mem) {
            if (m.skip + m.len > m.mem->size()) return false;
            sink(m.mem->data() + m.skip, m.len);
        } else {
            int fd = open(m.file.c_str(), O_RDONLY);
            if (fd < 0) return false;
            uint64_t left = m.len, at = m.skip;
            while (left) {
                ssize_t n = pread(fd, buf.data(), (size_t)std::min<uint64_t>(left, buf.size()), (off_t)at);
                if (n <= 0) {
                    close(fd);
                    return false;
                }
                sink(buf.data(), (size_t)n);
                left -= (uint64_t)n;
                at += (uint64_t)n;
            }
            close(fd);
        }
        pos += m.len;
    }
    sink(zeros, align(pos, kPayloadAlign) - pos);
    return true;
}

}  // namespace

// ---- Response --------------------------------------------------------------------------------
uint64_t Response::size() const {
    if (bundle) return bundle_size(*bundle);
    if (file.empty()) return body.size();
    if (file_range) return file_len;
    uint64_t n = 0;
    stat_file(file, &n);
    return n;
}
bool Response::read(std::vector<uint8_t>& out) const {
    if (bundle) return bundle_bytes(*bundle, out);
    if (file.empty()) {
        out = body;
        return true;
    }
    if (file_range) {
        int fd = ::open(file.c_str(), O_RDONLY);
        if (fd < 0) return false;
        out.resize(file_len);
        uint64_t at = 0;
        while (at < file_len) {
            ssize_t n = pread(fd, out.data() + at, (size_t)std::min<uint64_t>(file_len - at, 1u << 30), (off_t)(file_offset + at));
            if (n <= 0) break;
            at += (uint64_t)n;
        }
        ::close(fd);
        return at == file_len;
    }
    return read_file(file, out);
}

namespace {

// A body as a list of pieces read in order: bytes in memory, zeros (the bundle's padding), or a
// range of a file (opened when reached, closed after). The bundle's pieces are bundle_stream's.
class PieceReader : public Reader {
public:
    struct Piece {
        const uint8_t* mem = nullptr;  // in memory (else `file`, else zeros)
        const std::string* file = nullptr;
        uint64_t off = 0, len = 0;
    };
    std::vector<Piece> pieces;
    std::vector<uint8_t> owned;                       // bytes `mem` may point into
    std::shared_ptr<const std::vector<Member>> keep;  // the bundle the pieces point into
    std::string file_name;                            // a plain file's name
    uint64_t total = 0;

    ~PieceReader() override { close_fd(); }
    uint64_t size() const override { return total; }
    int64_t read(uint8_t* buf, size_t n) override {
        while (i_ < pieces.size() && at_ >= pieces[i_].len) next();
        if (i_ >= pieces.size()) return 0;
        const Piece& p = pieces[i_];
        size_t k = (size_t)std::min<uint64_t>(n, p.len - at_);
        if (p.mem) {
            memcpy(buf, p.mem + p.off + at_, k);
        } else if (p.file) {
            if (fd_ < 0 && (fd_ = ::open(p.file->c_str(), O_RDONLY | O_CLOEXEC)) < 0) return -1;
            ssize_t r = pread(fd_, buf, k, (off_t)(p.off + at_));
            if (r <= 0) return -1;  // a short file: the caller's size / SHA-1 checks catch it
            k = (size_t)r;
        } else {
            memset(buf, 0, k);
        }
        at_ += k;
        return (int64_t)k;
    }

private:
    void next() {
        close_fd();
        i_++;
        at_ = 0;
    }
    void close_fd() {
        if (fd_ >= 0) ::close(fd_);
        fd_ = -1;
    }
    size_t i_ = 0;
    uint64_t at_ = 0;
    int fd_ = -1;
};

}  // namespace

std::unique_ptr<Reader> Response::open() const {
    auto reader = std::make_unique<PieceReader>();
    if (bundle) {
        const std::vector<Member>& members = *bundle;
        std::vector<uint64_t> offs;
        reader->owned = bundle_head(members, &offs);
        reader->keep = bundle;
        reader->pieces.push_back({reader->owned.data(), nullptr, 0, reader->owned.size()});
        uint64_t pos = reader->owned.size();
        for (size_t i = 0; i < members.size(); i++) {
            if (offs[i] > pos) reader->pieces.push_back({nullptr, nullptr, 0, offs[i] - pos});
            const Member& m = members[i];
            if (m.mem) {
                if (m.skip + m.len > m.mem->size()) return nullptr;
                reader->pieces.push_back({m.mem->data(), nullptr, m.skip, m.len});
            } else {
                reader->pieces.push_back({nullptr, &m.file, m.skip, m.len});
            }
            pos = offs[i] + m.len;
        }
        if (align(pos, kPayloadAlign) > pos) reader->pieces.push_back({nullptr, nullptr, 0, align(pos, kPayloadAlign) - pos});
        reader->total = align(pos, kPayloadAlign);
        return reader;
    }
    if (!file.empty()) {
        uint64_t n = 0;
        if (!stat_file(file, &n)) return nullptr;
        reader->file_name = file;
        uint64_t off = file_range ? file_offset : 0, len = file_range ? file_len : n;
        if (off + len > n) return nullptr;
        reader->pieces.push_back({nullptr, &reader->file_name, off, len});
        reader->total = len;
        return reader;
    }
    reader->owned = body;
    reader->pieces.push_back({reader->owned.data(), nullptr, 0, reader->owned.size()});
    reader->total = reader->owned.size();
    return reader;
}

// ---- bundles ---------------------------------------------------------------------------------
uint64_t bundle_size(const std::vector<Member>& members) {
    std::vector<uint64_t> offs;
    bundle_head(members, &offs);
    return members.empty() ? align(kHeaderSize, kPayloadAlign) : align(offs.back() + members.back().len, kPayloadAlign);
}
bool bundle_bytes(const std::vector<Member>& members, std::vector<uint8_t>& out) {
    out.clear();
    out.reserve(bundle_size(members));
    return bundle_stream(members, [&](const uint8_t* d, size_t n) { out.insert(out.end(), d, d + n); });
}
std::string bundle_sha1(const std::vector<Member>& members) {
    files::Sha1 h;
    if (!bundle_stream(members, [&](const uint8_t* d, size_t n) { h.add(d, n); })) return "";
    return h.hex();
}
std::string sha1_hex(const uint8_t* data, size_t n) {
    files::Sha1 h;
    h.add(data, n);
    return h.hex();
}

}  // namespace soa::server::cdn
