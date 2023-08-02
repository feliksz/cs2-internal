#pragma once
#include <Windows.h>
#include "../sdk/types.hpp"
#include "../vendor/imgui/imgui.h"

namespace input {
	void initialize();
	void shutdown();

	static LRESULT WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
	inline WNDPROC o_WndProc{};
	
	bool is_mouse_in_region(i32 x, i32 y, i32 w, i32 h);
	bool is_key_pressed(ImGuiKey key);
	bool is_key_pressed(ImGuiMouseButton key);
}