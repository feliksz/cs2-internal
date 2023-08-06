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
	
	bool is_key_down(ImGuiKey key);
	bool is_key_down(ImGuiMouseButton key);

	bool is_key_pressed(ImGuiKey key);
	bool is_key_pressed(ImGuiMouseButton key);

	v2i get_mouse_pos();

	__forceinline bool is_mouse_in_region(const v2i& pos, const v2i& size) {
		return is_mouse_in_region(pos.x, pos.y, size.x, size.y);
	}
}