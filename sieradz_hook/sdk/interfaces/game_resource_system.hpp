#pragma once
#include "entity_system.hpp"

namespace cs2 {
	class c_game_resource_system {
		char __pad0[0x58];
	public:
		c_entity_system* entity_system;
	};
}