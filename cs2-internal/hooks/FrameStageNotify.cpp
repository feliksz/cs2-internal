#include "../sdk/entity/CBasePlayerController.hpp"
#include "../sdk/entity/CBasePlayerPawn.hpp"
#include "../sdk/entity/CWeaponCSBase.hpp"
#include "../features/features.hpp"
#include "../sdk/interfaces.hpp"
#include "hooks.hpp"

void __fastcall hooks::hkFrameStageNotify(void* rcx, i32 frameStage) {
	if (interfaces::engine->IsInGame() && frameStage == 6) {
		features::skin_changer::on_frame_stage_notify();
	}

	return o_FrameStageNotify(rcx, frameStage);
}