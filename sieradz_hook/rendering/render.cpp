#include "../deps/imgui/imgui.h"
#include "render.hpp"

void render::filled_rect(i32 x, i32 y, i32 width, i32 height, const col_t& col) {
	_draw_list->AddRectFilled({ (float)x, (float)y }, { (float)x + width, (float)y + height }, IM_COL32(col.r, col.g, col.b, col.a));
}

void render::rect(i32 x, i32 y, i32 width, i32 height, const col_t& col) {
	_draw_list->AddRect({ (float)x, (float)y }, { (float)x + width, (float)y + height }, IM_COL32(col.r, col.g, col.b, col.a));
}

void render::text(i32 x, i32 y, const std::string& text, const col_t& col) {
	_draw_list->AddText({ (float)x, (float)y }, IM_COL32(col.r, col.g, col.b, col.a), text.data());
}

void render::gradient_h(i32 x, i32 y, i32 width, i32 height, const col_t& col, const col_t& col2) {
	_draw_list->AddRectFilledMultiColor({ (float)x, (float)y }, { (float)x + width, (float)y + height }, IM_COL32(col.r, col.g, col.b, col.a), IM_COL32(col2.r, col2.g, col2.b, col2.a), IM_COL32(col2.r, col2.g, col2.b, col2.a), IM_COL32(col.r, col.g, col.b, col.a));
}

v2i render::get_text_size(const std::string& text) {
	auto v = ImGui::CalcTextSize(text.data());
	return v2i{ (i32)v.x, (i32)v.y };
}
