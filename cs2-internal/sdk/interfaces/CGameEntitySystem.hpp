#pragma once
#include "../entity/CBaseEntity.hpp"
#include "../entity/CBasePlayerController.hpp"
#include "../types.hpp"

class CGameEntitySystem {
public:
	CBaseEntity* GetBaseEntity(i32 index);

	template <typename T>
	T* GetEntity(i32 index) {
		return GetBaseEntity(index);
	}

	CBasePlayerController* GetLocalPlayerController();

	i32          GetHighestEntityIndex();

};