#include <iostream>
#include <algorithm>
#include "../sdk/interfaces.hpp"
#include "hooks.hpp"

bool __fastcall hooks::hkCreateMove(void* a1, i32 slot, bool active) {
	auto ret = o_CreateMove(a1, slot, active);

	auto cmd = interfaces::input->GetUserCmd();
	if (!cmd) {
		return ret;
	}

	/*
	printf("cmd base 0x%llx\n", (u64)cmd->base);

	// clamp forwardmove, sidemove and viewangles to safe values
	cmd->base->forwardmove = std::clamp(cmd->base->forwardmove, -450.f, 450.f);
	cmd->base->sidemove = std::clamp(cmd->base->sidemove, -450.f, 450.f);

	auto cmd_angle = cmd->base->view;
	cmd_angle->viewangles.x = std::clamp(cmd_angle->viewangles.x, -89.f, 89.f);
	cmd_angle->viewangles.y = std::clamp(cmd_angle->viewangles.y, -180.f, 180.f);
	cmd_angle->viewangles.z = 0.f;

	printf("forwardmove: %.2f, sidemove: %.2f\n", cmd->base->forwardmove, cmd->base->sidemove);
	printf("viewangles: (x: %.2f, y: %.2f, z: %.2f)\n", cmd_angle->viewangles.x, cmd_angle->viewangles.y, cmd_angle->viewangles.z);
	*/

	return ret;
}
