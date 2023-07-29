#pragma once
#include "../entity/entities.hpp"
#include "../../types.hpp"

namespace cs2 {
	class c_entity_system {
	public:
		CBaseEntity* get_base_entity(i32 index);

		CBasePlayerController* get_base_player_controller(i32 index);
	};
}