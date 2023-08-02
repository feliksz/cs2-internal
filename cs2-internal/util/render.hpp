#pragma once
#include "../vendor/imgui/imgui.h"
#include "../sdk/types.hpp"

namespace render {
	inline ImDrawList* _draw_list;
	inline ImFont* _default_font;

	void initialize_fonts();

	void rect(i32 x, i32 y, i32 width, i32 height, const col_t& color);
	void filled_rect(i32 x, i32 y, i32 width, i32 height, const col_t& color);
	void text(i32 x, i32 y, const char* str, const col_t& color);

	void gradient_h(i32 x, i32 y, i32 width, i32 height, const col_t& l_color, const col_t& r_color);
	void gradient_v(i32 x, i32 y, i32 width, i32 height, const col_t& l_color, const col_t& r_color);

	v2i get_text_size(const char* str);

	__forceinline void rect(const v2i& pos, const v2i& size, const col_t& color) {
		rect(pos.x, pos.y, size.x, size.y, color);
	}

	__forceinline void filled_rect(const v2i& pos, const v2i& size, const col_t& color) {
		filled_rect(pos.x, pos.y, size.x, size.y, color);
	}

	__forceinline void text(const v2i& pos, const char* str, const col_t& color) {
		text(pos.x, pos.y, str, color);
	}

	__forceinline void gradient_h(const v2i& pos, const v2i& size, const col_t& l_color, const col_t& r_color) {
		gradient_h(pos.x, pos.y, size.x, size.y, l_color, r_color);
	}

	__forceinline void gradient_v(const v2i& pos, const v2i& size, const col_t& l_color, const col_t& r_color) {
		gradient_v(pos.x, pos.y, size.x, size.y, l_color, r_color);
	}
}