#pragma once
#include "../vendor/imgui/imgui.h"
#include "../sdk/types.hpp"

namespace render {
	inline ImDrawList* _draw_list;

	void rect(i32 x, i32 y, i32 width, i32 height, const col_t& color);
	void filled_rect(i32 x, i32 y, i32 width, i32 height, const col_t& color);
	void text(i32 x, i32 y, const char* str, const col_t& color);

	void gradient_h(i32 x, i32 y, i32 width, i32 height, const col_t& l_color, const col_t& r_color);

	v2i get_text_size(const char* str);

	__forceinline void rect(const v2i& pos, const v2i& size, const col_t& color) {
		rect(pos.x, pos.y, size.x, size.y, color);
	}

	__forceinline void filled_rect(const v2i& pos, const v2i& size, const col_t& color) {
		filled_rect(pos.x, pos.y, size.x, size.y, color);
	}
}