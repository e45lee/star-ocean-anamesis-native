// The battle log a MissionEnd carries (soaserver/battle_log.h; library code).
#include "soaserver/battle_log.h"

namespace soa::server {

uint32_t BattleLog::prop_u32(const char* name, uint32_t dflt) const {
    const Value* v = root_.find(name);
    if (!v) return dflt;
    switch (v->type) {
        case Value::UInt:
            return (uint32_t)v->u;
        case Value::Int:
            return (uint32_t)v->i;
        case Value::Bool:
            return v->b ? 1 : 0;
        case Value::Float:
            return (uint32_t)v->f;
        default:
            return dflt;
    }
}

int64_t BattleLog::evaluation(int type) const {
    const Value* a = root_.find("BattleEvaluationInfo");
    if (!a || a->type != Value::Arr) return -1;
    for (size_t k = a->arr.size(); k-- > 0;) {
        const Value& e = a->arr[k];
        const Value* t = e.find("evaluation_type");
        const Value* s = e.find("score");
        if (!t || !s) continue;
        int64_t tv = t->type == Value::Int ? t->i : (int64_t)t->u;
        if (tv != type) continue;
        return s->type == Value::Int ? s->i : s->type == Value::Float ? (int64_t)s->f : (int64_t)s->u;
    }
    return -1;
}

bool carries_battle_log(const std::string& method) {
    return method == "MissionEnd" || method == "MissionFailed" || method == "Sphere211MissionEnd" || method == "Sphere211MissionFailed";
}

std::shared_ptr<const BattleLog> parse_battle_log(const uint8_t* p, size_t n) {
    if (!n) return nullptr;
    const uint8_t* q = p;
    Value root = mp_decode(q, p + n);
    if (root.type != Value::Map) return nullptr;
    return std::make_shared<const BattleLog>(std::vector<uint8_t>(p, p + n), std::move(root));
}

}  // namespace soa::server
