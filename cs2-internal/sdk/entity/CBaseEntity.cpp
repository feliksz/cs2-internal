#include "../../util/math.hpp"
#include "../patterns.hpp"
#include "CBaseEntity.hpp"

bool CBaseEntity::get_bounding_box(bbox_t& bbox, bool compute_surrounding_box) {
    auto collision = m_pCollision();
    if (!collision)
        return false;

    v3 min, max;
    if (compute_surrounding_box) {
        if (!patterns::pfnComputeHitboxSurroundingBox(this, min, max))
            return false;
    }
    else {
        auto origin = m_pGameSceneNode()->m_vecAbsOrigin();
        min = collision->m_vecMins() + origin;
        max = collision->m_vecMaxs() + origin;
    }

    bbox.x = bbox.y = std::numeric_limits<f32>::max();
    bbox.w = bbox.h = -std::numeric_limits<f32>::max();

    for (i32 i = 0; i < 8; ++i) {
        auto point = v3(
            i & 1 ? max.x : min.x,
            i & 2 ? max.y : min.y,
            i & 4 ? max.z : min.z
        );

        auto screen = v2i{};
        if (!math::world_to_screen(point, screen))
            return false;

        bbox.x = std::min(bbox.x, (f32)screen.x);
        bbox.y = std::min(bbox.y, (f32)screen.y);
        bbox.w = std::max(bbox.w, (f32)screen.x);
        bbox.h = std::max(bbox.h, (f32)screen.y);
    }

    bbox.w = bbox.w - bbox.x;
    bbox.h = bbox.h - bbox.y;
    return true;
}
