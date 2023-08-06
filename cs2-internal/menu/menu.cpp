#include <thread>
#include <mutex>
#include "config.hpp"
#include "gui.hpp"
#include "menu.hpp"

void aimbot_tab() {

}

void visuals_tab() {
	printf("what\n");
	gui::group("Players", { 4, 4 }, { 230, 218 });
	{
		gui::checkbox("Box", &BOOL_GET("visuals.player_esp.box"));
		gui::checkbox("Name", &BOOL_GET("visuals.player_esp.name"));
		gui::checkbox("Health", &BOOL_GET("visuals.player_esp.health"));
		gui::checkbox("Weapon", &BOOL_GET("visuals.player_esp.weapon"));
		gui::checkbox("Ignore allies", &BOOL_GET("visuals.player_esp.ignore_allies"));
	}

	gui::group("Weapons", { 242, 4 }, { 230, 140 });
	{
		gui::checkbox("Box", &BOOL_GET("visuals.weapon_esp.box"));
		gui::checkbox("Name", &BOOL_GET("visuals.weapon_esp.name"));
		gui::checkbox("Ammo", &BOOL_GET("visuals.weapon_esp.ammo"));
	}

	gui::group("Other", { 242, 152 }, { 230, 70 });
	{
		gui::checkbox("Spectators", &BOOL_GET("visuals.other.spectators"));
		gui::checkbox("  Local only", &BOOL_GET("visuals.other.spectators_only_local"));
	}
}

void misc_tab() {
	gui::group("Misc", { 4, 4 }, { 230, 218 });
	{
		gui::checkbox("Draw debug info", &BOOL_GET("misc.draw_debug_info"));
	}
}

void menu::initialize() {
	gui::add_tab("aimbot", aimbot_tab);
	gui::add_tab("visuals", visuals_tab);
	gui::add_tab("misc", misc_tab);
}

void menu::draw() {
	static std::once_flag init_flag;
	std::call_once(init_flag, []() {initialize(); });

	// @to-do: civilised tabs, or just rewrite entire menu
	gui::window("dupaware pl", { 120, 120 }, { 580, 260 });
	printf("nigga %i\n", gui::get_active_tab());
	switch (gui::get_active_tab()) {
	case 0: aimbot_tab(); break;
	case 1: visuals_tab(); break;
	case 2: misc_tab(); break;
	}

}
