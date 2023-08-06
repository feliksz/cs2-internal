#include "../util/input.hpp"
#include "../util/render.hpp"
#include "gui.hpp"

void gui::window(const char* title, v2i initial_pos, v2i size) {
	if (!ctx.pos) {
		ctx.pos = initial_pos;
	}

	if (!ctx.active_tab) {
		ctx.active_tab = 0u;
	}
	ctx.size = size;

	constexpr auto TITLEBAR_HEIGHT = 24;
	if (input::is_key_pressed(ImGuiMouseButton_Left) && input::is_mouse_in_region(ctx.pos.x, ctx.pos.y, ctx.size.x, TITLEBAR_HEIGHT)) {
		ctx.moving = true;
		ctx.move_start_pos = ctx.pos;
		ctx.move_mouse_start_pos = input::get_mouse_pos();
	}
	else if (ctx.moving) {
		if (input::is_key_down(ImGuiMouseButton_Left)) {
			ctx.pos = ctx.move_start_pos + input::get_mouse_pos() - ctx.move_mouse_start_pos;
		}
		else {
			ctx.moving = false;
		}
	}

	// window
	render::filled_rect(ctx.pos, ctx.size, col_t(20, 20, 20));
	
	// header
	render::filled_rect(ctx.pos, { ctx.size.x, TITLEBAR_HEIGHT }, col_t(10, 10, 10));
	render::text(ctx.pos.x + 4, ctx.pos.y + 5, title, col_t::white());

	// header gradient
	render::gradient_h(ctx.pos.x, ctx.pos.y + TITLEBAR_HEIGHT, 96, 2, col_t(250, 128, 114), col_t(250, 128, 114, 90));
	render::gradient_h(ctx.pos.x + 96, ctx.pos.y + TITLEBAR_HEIGHT, ctx.size.x - 96, 2, col_t(250, 128, 114, 90), col_t(250, 128, 114));

	// tabs
	render::filled_rect(ctx.pos.x, ctx.pos.y + TITLEBAR_HEIGHT + 4, 96, ctx.size.y - TITLEBAR_HEIGHT - 8, col_t(10, 10, 10));
	auto ty = 0;
	for (auto i = 0u; i < ctx.tabs.size(); i++) {
		auto tab_pos = v2i{ ctx.pos.x, ctx.pos.y + TITLEBAR_HEIGHT + ty + 4 };
		auto tab_size = v2i{ 96, 16 };
		if (input::is_mouse_in_region(tab_pos, tab_size) && input::is_key_down(ImGuiMouseButton_Left)) {
			ctx.active_tab = i;
		}

		if (ctx.active_tab == i) {
			render::filled_rect(tab_pos, tab_size, col_t(15, 15, 15));
			render::text(tab_pos, ctx.tabs[i].data(), col_t::white());
		}
		else {
			render::text(tab_pos, ctx.tabs[i].data(), col_t::white(180));
		}

		ty += 16;
	}

	ctx.client_area_pos = { ctx.pos.x + 100, ctx.pos.y + TITLEBAR_HEIGHT + 6 };
	ctx.client_area_size = { ctx.size.x - 104, ctx.size.y - TITLEBAR_HEIGHT - 10 };

	// window outline
	render::rect(ctx.pos, ctx.size, col_t::black(100));
}

void gui::add_tab(const char* title, const std::function<void()>& action) {
	ctx.tabs.push_back(title);
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
	auto control_pos = v2i{ ctx.cursor_pos.x + 2, ctx.cursor_pos.y + 2 };
	auto control_size = v2i{ 13, 13 };

	auto hover = input::is_mouse_in_region(control_pos.x, control_pos.y, control_size.x, control_size.y);
	if (hover && input::is_key_pressed(ImGuiMouseButton_Left)) {
		*var = !*var;
	}

	render::filled_rect(control_pos, control_size, hover ? col_t(30, 30, 30) : col_t(20, 20, 20));
	if (*var) {
		render::filled_rect(control_pos, control_size, col_t(250, 128, 114));
	}

	render::rect(control_pos, control_size, *var ? col_t(230, 108, 94) : col_t(10, 10, 10));

	auto label_pos = v2i{ ctx.cursor_pos.x + control_size.x + 7, ctx.cursor_pos.y + 1 };
	render::text(label_pos.x, label_pos.y, title, col_t::white());

	ctx.cursor_pos.y += 16;
}
