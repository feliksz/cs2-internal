#pragma once
#include "../imgui/imgui.h"
#include "../types.hpp"
#include <Windows.h>

namespace input {
	inline ImGuiIO* io;

	void initialize();

	bool is_key_down(u32 key_code);

	static LRESULT wndproc_hk(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param);
}