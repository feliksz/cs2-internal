#pragma once
#include "sdk/entity/CBasePlayerController.hpp"
#include "sdk/entity/CBasePlayerPawn.hpp"
#include "sdk/types.hpp"

namespace globals {
	struct local_player_t {
		CBasePlayerController* controller;
		CBasePlayerPawn* pawn;
	};

	inline local_player_t local_player;
	inline vmatrix_t view_matrix;
}