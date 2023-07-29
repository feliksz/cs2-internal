#pragma once
#include <string>
#include "../deps/imgui/imgui.h"
#include "../types.hpp"

namespace render {
	inline ImDrawList* _draw_list;

	void filled_rect(i32 x, i32 y, i32 width, i32 height, const col_t& col);
	void rect(i32 x, i32 y, i32 width, i32 height, const col_t& col);
	void text(i32 x, i32 y, const std::string& text, const col_t& col);

	void gradient_h(i32 x, i32 y, i32 width, i32 height, const col_t& col, const col_t& col2);

	v2i get_text_size(const std::string& text);
}