#include "config.hpp"

void config::initialize() {
	BOOL_GET("visuals.player_esp.box") = true;
	BOOL_GET("visuals.player_esp.name") = false;
	BOOL_GET("visuals.player_esp.health") = false;
	BOOL_GET("visuals.player_esp.weapon") = false;

	KEYBIND_GET("ui.toggle") = ImGuiKey_Insert;
}
