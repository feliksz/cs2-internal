#include "../vendor/imgui/imgui_freetype.h"
#include "render.hpp"

void render::initialize_fonts() {
	ImFontConfig cfg;
	cfg.FontBuilderFlags = ImGuiFreeTypeBuilderFlags_MonoHinting | ImGuiFreeTypeBuilderFlags_Monochrome;
	render::_default_font = ImGui::GetIO().Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Tahoma.ttf", 13.f, &cfg);

}

void render::rect(i32 x, i32 y, i32 width, i32 height, const col_t& color) {
	_draw_list->AddRect({(f32)x, (f32)y}, {(f32)x + width, (f32)y + height}, color);
}

void render::filled_rect(i32 x, i32 y, i32 width, i32 height, const col_t& color) {
	_draw_list->AddRectFilled({ (f32)x, (f32)y }, { (f32)x + width, (f32)y + height }, color);
}

void render::text(i32 x, i32 y, const char* str, const col_t& color) {
	_draw_list->AddText(_default_font, 13.f, { (f32)x, (f32)y }, color, str);
}

void render::gradient_h(i32 x, i32 y, i32 width, i32 height, const col_t& l_color, const col_t& r_color) {
	_draw_list->AddRectFilledMultiColor(
		{ (f32)x, (f32)y },
		{ (f32)x + width, (f32)y + height },
		l_color, 
		r_color, 
		r_color, 
		l_color);
}
void render::gradient_v(i32 x, i32 y, i32 width, i32 height, const col_t& l_color, const col_t& r_color) {
	_draw_list->AddRectFilledMultiColor(
		{ (f32)x, (f32)y }, 
		{ (f32)x + width, (f32)y + height }, 
		l_color, 
		l_color, 
		r_color, 
		r_color
	);
}

v2i render::get_text_size(const char* str) {
	ImVec2 size = ImGui::CalcTextSize(str);
	return v2i{ (i32)size.x, (i32)size.y };
}
