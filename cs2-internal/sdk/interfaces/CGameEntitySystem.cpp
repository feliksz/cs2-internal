#include "../patterns.hpp"
#include "CGameEntitySystem.hpp"

CBaseEntity* CGameEntitySystem::GetBaseEntity(i32 index) {
    return (CBaseEntity*) patterns::pfnGetBaseEntity(this, index);
}

CBasePlayerController* CGameEntitySystem::GetLocalPlayerController() {
    return (CBasePlayerController*) patterns::pfnGetLocalPlayerController(-1);
}

i32 CGameEntitySystem::GetHighestEntityIndex() {
    i32 highest_idx = -1;
    patterns::pfnGetHighestEntityIndex(this, &highest_idx);
    return highest_idx;
}
