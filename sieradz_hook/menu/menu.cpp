#include <Windows.h>
#include "../deps/imgui/imgui.h"
#include "config.hpp"
#include "menu.hpp"
#include "gui/gui.hpp"
void menu::on_present() {
	/*ImGui::Begin("TequilaHook By ArixElo");
	ImGui::Checkbox("bhop", &BOOL_GET("misc.movement.bunnyhop"));
	ImGui::End();*/

	gui::window({ 20, 20 }, { 540, 200 }, []() {
		if (gui::tab("aimbot")) {
			gui::checkbox("auto jump", &BOOL_GET("misc.autojump"));
			gui::checkbox("auto strafe", &BOOL_GET("misc.autostrafe"));
			gui::dropdown("mode", &CONFIG_GET(u32, "misc.autostrafemode"), {"normal", "fast"});
			gui::slider("strafe speed", &CONFIG_GET(i32, "misc.strafespeed"), 0, 450);
			gui::slider("fakelag", &CONFIG_GET(i32, "misc.fakelag"), 0, 14);

			if (gui::button("save config", 128, false)) {
				printf("saving config...\n");
				config::save();
			}
			if (gui::button("load config", 128, false)) {
				printf("loading config...\n");
				config::load();
			}
		}
		if (gui::tab("visuals")) {

		}
		if (gui::tab("misc")) {

		}
		});
}
