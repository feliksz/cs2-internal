#include "../util/input.hpp"
#include "../util/render.hpp"
#include "gui.hpp"

void gui::window(const char* title, v2i initial_pos, v2i size) {
	if (!ctx.pos) {
		ctx.pos = initial_pos;
	}

	ctx.size = size;

	constexpr auto TITLEBAR_HEIGHT = 24;

	// window
	render::filled_rect(ctx.pos, ctx.size, col_t(20, 20, 20));
	
	// header
	render::filled_rect(ctx.pos, { ctx.size.x, TITLEBAR_HEIGHT }, col_t(10, 10, 10));
	render::text(ctx.pos.x + 4, ctx.pos.y + 4, title, col_t::white());

	// header gradient
	render::gradient_h(ctx.pos.x, ctx.pos.y + TITLEBAR_HEIGHT, 64, 2, col_t(250, 128, 114), col_t(250, 128, 114, 90));
	render::gradient_h(ctx.pos.x + 64, ctx.pos.y + TITLEBAR_HEIGHT, ctx.size.x - 64, 2, col_t(250, 128, 114, 90), col_t(250, 128, 114));

	// tabs
	for (auto t : ctx.tabs) {

	}

	ctx.client_area_pos = { ctx.pos.x + 4, ctx.pos.y + TITLEBAR_HEIGHT + 6 };
	ctx.client_area_size = { ctx.size.x - 8, ctx.size.y - TITLEBAR_HEIGHT - 10 };

	// window outline
	render::rect(ctx.pos, ctx.size, col_t::black(100));
}

void gui::add_tab(const char* title, const std::function<void()>& action) {

	if (ctx.active_tab == std::hash<std::string>{}(title)) {
		std::invoke(action);
	}
}

void gui::group(const char* title, const v2i& pos, const v2i& size) {
	auto group_pos = v2i{ ctx.client_area_pos.x + pos.x, ctx.client_area_pos.y + pos.y };
	auto group_size = size;

	render::filled_rect(group_pos, group_size, col_t(35, 35, 35));
	render::text(group_pos.x + 4, group_pos.y + 2, title, col_t::white());

	render::rect(group_pos, group_size, col_t(70, 70, 70));
	render::rect(group_pos, { group_size.x, 20 }, col_t(70, 70, 70));

	ctx.cursor_pos = { group_pos.x + 4, group_pos.y + 28 };
}

void gui::checkbox(const char* title, bool* var) {
	auto control_pos = v2i{ ctx.cursor_pos.x + 2, ctx.cursor_pos.y + 2};
	auto control_size = v2i{ 13, 13 };

	auto hover = input::is_mouse_in_region(control_pos.x, control_pos.y, control_size.x, control_size.y);
	if (hover && input::is_key_pressed(ImGuiMouseButton_Left)) {
		*var = !*var;
	}

	render::filled_rect(control_pos, control_size, hover ? col_t(30, 30, 30) : col_t(20, 20, 20));
	if (*var) {
		render::filled_rect(control_pos, control_size, col_t(250, 128, 114));
	}

	render::rect(control_pos, control_size, col_t::black(80));

	auto label_pos = v2i{ ctx.cursor_pos.x + control_size.x + 6, ctx.cursor_pos.y + 1};
	render::text(label_pos.x, label_pos.y, title, col_t::white());

	ctx.cursor_pos.y += 16;
}
