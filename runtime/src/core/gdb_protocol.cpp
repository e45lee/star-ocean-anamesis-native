#include "core/gdb_protocol.h"

#include <cstdio>

namespace soa::gdbrsp {

uint8_t checksum(const std::string& data) {
    uint8_t c = 0;
    for (unsigned char ch : data) c += ch;
    return c;
}

std::string escape(const std::string& s) {
    std::string out;
    out.reserve(s.size());
    for (char ch : s) {
        if (ch == '$' || ch == '#' || ch == '}' || ch == '*') {
            out += '}';
            out += (char)(ch ^ 0x20);
        } else {
            out += ch;
        }
    }
    return out;
}

std::string frame(const std::string& data) {
    std::string e = escape(data);
    char cs[4];
    snprintf(cs, sizeof cs, "%02x", checksum(e));
    return "$" + e + "#" + cs;
}

std::string unescape(const std::string& s) {
    std::string out;
    out.reserve(s.size());
    for (size_t i = 0; i < s.size(); i++) {
        if (s[i] == '}' && i + 1 < s.size()) {
            out += (char)(s[++i] ^ 0x20);
        } else if (s[i] == '*' && !out.empty() && i + 1 < s.size()) {
            int n = (unsigned char)s[++i] - 29;
            out.append(n > 0 ? (size_t)n : 0, out.back());
        } else {
            out += s[i];
        }
    }
    return out;
}

std::optional<std::string> Reader::next(bool* bad) {
    if (bad) *bad = false;
    for (;;) {
        size_t i = 0;
        while (i < buf.size() && (buf[i] == '+' || buf[i] == '-')) i++;
        buf.erase(0, i);
        if (buf.empty()) return std::nullopt;
        if (buf[0] == '\x03') {
            buf.erase(0, 1);
            return std::string("\x03");
        }
        if (buf[0] != '$') {  // noise between packets
            size_t d = buf.find_first_of("$\x03");
            buf.erase(0, d == std::string::npos ? buf.size() : d);
            continue;
        }
        size_t h = buf.find('#');
        if (h == std::string::npos || h + 2 >= buf.size()) return std::nullopt;
        std::string raw = buf.substr(1, h - 1);
        unsigned want = 0;
        bool ok = sscanf(buf.substr(h + 1, 2).c_str(), "%2x", &want) == 1;
        buf.erase(0, h + 3);
        if (!ok || checksum(raw) != want) {
            if (bad) *bad = true;
            return std::string();
        }
        return unescape(raw);
    }
}

std::string to_hex(const void* p, size_t n) {
    static const char* d = "0123456789abcdef";
    std::string out(n * 2, '0');
    const unsigned char* b = (const unsigned char*)p;
    for (size_t i = 0; i < n; i++) {
        out[2 * i] = d[b[i] >> 4];
        out[2 * i + 1] = d[b[i] & 15];
    }
    return out;
}
std::string to_hex(const std::string& s) { return to_hex(s.data(), s.size()); }

static int hexval(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    return -1;
}

bool from_hex(const std::string& h, std::string& out) {
    if (h.size() % 2) return false;
    out.clear();
    out.reserve(h.size() / 2);
    for (size_t i = 0; i < h.size(); i += 2) {
        int a = hexval(h[i]), b = hexval(h[i + 1]);
        if (a < 0 || b < 0) return false;
        out += (char)(a << 4 | b);
    }
    return true;
}

std::string le_hex(uint64_t v, int bytes) {
    unsigned char b[8];
    for (int i = 0; i < 8; i++) b[i] = (unsigned char)(v >> (8 * i));
    return to_hex(b, (size_t)bytes);
}

uint64_t le_from_hex(const std::string& h) {
    std::string b;
    if (!from_hex(h, b)) return 0;
    uint64_t v = 0;
    for (size_t i = 0; i < b.size() && i < 8; i++) v |= (uint64_t)(unsigned char)b[i] << (8 * i);
    return v;
}

bool parse_hex(const std::string& s, size_t& i, uint64_t& v) {
    size_t start = i;
    v = 0;
    while (i < s.size() && hexval(s[i]) >= 0) v = v << 4 | (uint64_t)hexval(s[i++]);
    return i > start;
}

bool parse_vcont(const std::string& p, std::vector<VContAction>& out) {
    out.clear();
    if (p.rfind("vCont;", 0) != 0) return false;
    size_t i = 6;
    while (i < p.size()) {
        char op = p[i++];
        if (op == 'C' || op == 'S') {  // signal: skip it
            uint64_t sig;
            if (!parse_hex(p, i, sig)) return false;
            op = op == 'C' ? 'c' : 's';
        }
        if (op != 'c' && op != 's' && op != 't') return false;
        int tid = -1;
        if (i < p.size() && p[i] == ':') {
            i++;
            if (p.compare(i, 2, "-1") == 0) {
                i += 2;
            } else {
                uint64_t t;
                if (!parse_hex(p, i, t)) return false;
                tid = (int)t;
            }
        }
        out.push_back({op, tid});
        if (i < p.size()) {
            if (p[i] != ';') return false;
            i++;
        }
    }
    return !out.empty();
}

}  // namespace soa::gdbrsp
