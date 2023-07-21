#include <Windows.h>
#include "../deps/imgui/imgui.h"
#include "menu.hpp"

void menu::on_present() {
	ImGui::Begin("TequilaHook By ArixElo");
	if (ImGui::Button("Zaplac raty")) {
		MessageBoxA(0, "nie da sie", "ximi bloked", MB_OK);
	}
	ImGui::End();
}
