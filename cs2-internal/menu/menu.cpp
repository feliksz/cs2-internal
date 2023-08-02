#include <thread>
#include <mutex>
#include "config.hpp"
#include "gui.hpp"
#include "menu.hpp"

void aimbot_tab() {

}

void visuals_tab() {

}

void misc_tab() {

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
	gui::window("cs2hack", { 120, 120 }, { 320, 200 });

	gui::group("Players", { 4, 4 }, { 144, 160 });
	{
		gui::checkbox("Box", &BOOL_GET("visuals.player_esp.box"));
		gui::checkbox("Name", &BOOL_GET("visuals.player_esp.name"));
		gui::checkbox("Health", &BOOL_GET("visuals.player_esp.health"));
		gui::checkbox("Weapon", &BOOL_GET("visuals.player_esp.weapon"));
	}

	gui::group("Weapons", { 156, 4 }, { 144, 100 });
	{
		gui::checkbox("Box", &BOOL_GET("visuals.weapon_esp.box"));
		gui::checkbox("Name", &BOOL_GET("visuals.weapon_esp.name"));
		gui::checkbox("Ammo", &BOOL_GET("visuals.weapon_esp.ammo"));
	}

	gui::group("Other", { 156, 112 }, { 144, 50 });
	{
		gui::checkbox("Spectator list", &BOOL_GET("visuals.other.spectator_list"));
	}

}
