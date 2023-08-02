#include "../patterns.hpp"
#include "CGameEntitySystem.hpp"

CBaseEntity* CGameEntitySystem::GetBaseEntity(i32 index) {
    return (CBaseEntity*) patterns::p_GetBaseEntity(this, index);
}

CBasePlayerController* CGameEntitySystem::GetLocalPlayerController() {
    // !!! crashes
    return (CBasePlayerController*) patterns::p_GetLocalPlayerController(this, -1);
}

i32 CGameEntitySystem::GetHighestEntityIndex() {
    i32 highest_idx = -1;
    patterns::p_GetHighestEntityIndex(this, &highest_idx);
    return highest_idx;
}
