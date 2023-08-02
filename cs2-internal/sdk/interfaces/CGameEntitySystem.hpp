#pragma once
#include "../entity/CBaseEntity.hpp"
#include "../entity/CBasePlayerController.hpp"
#include "../types.hpp"

class CGameEntitySystem {
public:
	CBaseEntity* GetBaseEntity(i32 index);
	CBasePlayerController* GetLocalPlayerController();

	i32          GetHighestEntityIndex();

};