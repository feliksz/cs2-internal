#pragma once
#include <functional>
#include <string>
#include <vector>
#include "../sdk/types.hpp"

namespace gui {
	struct {
		v2i pos, size;

		v2i client_area_pos, client_area_size;
		v2i cursor_pos;
		size_t                    active_tab;
		std::vector<std::string>  tabs;
	} ctx;

	void window(const char* title, v2i initial_pos, v2i size);
	void add_tab(const char* title, const std::function<void()>& action);
	void group(const char* title, const v2i& pos, const v2i& size);
	void checkbox(const char* title, bool* var);
}