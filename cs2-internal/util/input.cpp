#include "../menu/config.hpp"
#include "../menu/menu.hpp"
#include "../vendor/imgui/imgui.h"
#include "../vendor/imgui/imgui_impl_win32.h"
#include "input.hpp"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

void input::initialize() {
	auto hwnd = FindWindowW(nullptr, L"Counter-Strike 2");

	ImGui::CreateContext();
	ImGui_ImplWin32_Init(hwnd);

	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

	o_WndProc = (WNDPROC)SetWindowLongPtrW(hwnd, GWLP_WNDPROC, (LONG_PTR)WndProc);
}

void input::shutdown() {
	auto hwnd = FindWindowW(nullptr, L"Counter-Strike 2");
	SetWindowLongPtrW(hwnd, GWLP_WNDPROC, (LONG_PTR)o_WndProc);
}

LRESULT input::WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wparam, lparam) && menu::is_open)
		return true;

	return CallWindowProcA(o_WndProc, hwnd, msg, wparam, lparam);
}

bool input::is_mouse_in_region(i32 x, i32 y, i32 w, i32 h) {
	return ImGui::IsMouseHoveringRect({ (f32)x, (f32)y }, { (f32)x + w, (f32)y + h }, false);
}

bool input::is_key_pressed(ImGuiKey key) {
	return ImGui::IsKeyPressed(key);
}

bool input::is_key_pressed(ImGuiMouseButton key) {
	return ImGui::IsMouseClicked(key);
}
