#pragma once
#include "../deps/imgui/imgui.h"
#include "../types.hpp"
#include <Windows.h>

namespace input {
	inline ImGuiIO* io;

	void initialize();
	void deinitialize();


	bool is_mouse_in_region(const v2i& pos, const v2i& size);

	bool is_key_down(u32 key_code);
	bool is_key_pressed(ImGuiKey key);

	static LRESULT wndproc_hk(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param);
}