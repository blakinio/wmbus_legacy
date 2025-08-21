#include <iostream>
#include <vector>
#include <string>
#include <cstdio>

enum class KindOfData { PROTOCOL, CONTENT };
enum class Understanding { NONE, ENCRYPTED, COMPRESSED, PARTIAL, FULL };

struct Explanation {
    int pos;
    int len;
    std::string info;
    KindOfData kind;
    Understanding understanding;
};

static std::string json_escape(const std::string& in) {
    std::string out;
    out.reserve(in.size());
    for (unsigned char c : in) {
        switch (c) {
            case '"': out += "\\\""; break;
            case '\\': out += "\\\\"; break;
            case '\b': out += "\\b"; break;
            case '\f': out += "\\f"; break;
            case '\n': out += "\\n"; break;
            case '\r': out += "\\r"; break;
            case '\t': out += "\\t"; break;
            default:
                if (c < 0x20) {
                    char buf[7];
                    std::snprintf(buf, sizeof(buf), "\\u%04x", c);
                    out += buf;
                } else {
                    out += c;
                }
        }
    }
    return out;
}

std::string renderAnalysisAsJson(std::vector<Explanation>& explanations) {
    std::string s = "[\n";
    bool first = true;
    for (auto& e : explanations) {
        if (!first) s += ",\n";
        first = false;

        const char* kind = e.kind == KindOfData::PROTOCOL ? "protocol" : "content";
        const char* understanding = "none";
        switch (e.understanding) {
            case Understanding::NONE: understanding = "none"; break;
            case Understanding::ENCRYPTED: understanding = "encrypted"; break;
            case Understanding::COMPRESSED: understanding = "compressed"; break;
            case Understanding::PARTIAL: understanding = "partial"; break;
            case Understanding::FULL: understanding = "full"; break;
        }

        s += "  {";
        s += "\"pos\":" + std::to_string(e.pos);
        s += ",\"len\":" + std::to_string(e.len);
        s += ",\"kind\":\"" + std::string(kind) + "\"";
        s += ",\"understanding\":\"" + std::string(understanding) + "\"";
        s += ",\"info\":\"" + json_escape(e.info) + "\"";
        s += "}";
    }
    if (!first) s += "\n";
    s += "]\n";
    return s;
}

int main() {
    std::vector<Explanation> ex {
        {1, 2, "ok", KindOfData::PROTOCOL, Understanding::FULL},
        {3, 4, "needs \"escape\" &\nnewline", KindOfData::CONTENT, Understanding::PARTIAL}
    };
    std::cout << renderAnalysisAsJson(ex);
    return 0;
}

