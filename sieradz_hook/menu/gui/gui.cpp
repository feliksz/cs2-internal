#include "../../rendering/render.hpp"
#include "../../util/input.hpp"
#include "gui.hpp"

void gui::window(const v2i& pos, const v2i& size, const std::function<void()>& action) {
	if (!ctx.m_pos) {
		ctx.m_pos = pos;
	}

	ctx.m_size = size;
	ctx.m_tabs.clear();

	render::filled_rect(ctx.m_pos.x, ctx.m_pos.y, ctx.m_size.x, ctx.m_size.y, { 30, 30, 30, 255 });

	// title
	render::filled_rect(ctx.m_pos.x, ctx.m_pos.y, ctx.m_size.x, 26, { 10, 10, 10, 255 });
	render::text(ctx.m_pos.x + 8, ctx.m_pos.y + 6, "cs2-hack", { 255, 255, 255, 255 });

	/*
	render::filled_rect(ctx.m_pos.x, ctx.m_pos.y + 25, 120, 2, { 250, 128, 114, 255 });
	render::gradient_h(ctx.m_pos.x + 120, ctx.m_pos.y + 25, 120, 2, { 250, 128, 114, 255 }, { 250, 128, 114, 100 });
	render::gradient_h(ctx.m_pos.x + 240, ctx.m_pos.y + 25, ctx.m_size.x - 240, 2, { 250, 128, 114, 100 },{ 250, 128, 114, 255 });
	*/

	ImGui::GetForegroundDrawList()->PushClipRect({ (float)ctx.m_pos.x, (float)ctx.m_pos.y + 24 }, { (float)ctx.m_pos.x + ctx.m_size.x, ctx.m_pos.y + 25.f + 4.f });
	static auto x = 0.f;
	auto progress = ctx.m_size.x * x;
	auto x_pos = ctx.m_pos.x + progress;
	auto width = ctx.m_size.x * 2.f;
	//render::gradient_h(x_pos, ctx.m_pos.y + 25, ctx.m_size.x, 2, { 250, 128, 114, 255 }, { 250, 128, 114, 60 });
	//render::gradient_h(ctx.m_pos.x + progress - (ctx.m_size.x), ctx.m_pos.y + 25, ctx.m_size.x, 2, {250, 128, 114, 60}, {250, 128, 114, 255});
	render::gradient_h(x_pos - 128, ctx.m_pos.y + 24, ctx.m_size.x + 128, 2, { 250, 128, 114, 255 }, { 250, 128, 114, 60 });
	render::gradient_h(ctx.m_pos.x + progress - ctx.m_size.x - 256, ctx.m_pos.y + 24, ctx.m_size.x + 128, 2, { 250, 128, 114, 60 }, { 250, 128, 114, 255});
	x += 0.002f;
	if (x >= 1.f) {
		x = 0.f;
	}
	ImGui::GetForegroundDrawList()->PopClipRect();


	// contents
	auto container_pos = v2i{ ctx.m_pos.x + 144, ctx.m_pos.y + 32 };
	auto container_size = v2i{ ctx.m_size.x - 24 - 128, ctx.m_size.y - 40 };
	
	render::filled_rect(container_pos.x, container_pos.y, container_size.x, container_size.y, { 10, 10, 10, 255 });

	ctx.m_cursor_pos = container_pos;
	ctx.m_container_size = container_size;

	std::invoke(action);

	render::rect(container_pos.x, container_pos.y, container_size.x, container_size.y, col_t::black());
	
	// tabs
	if (!ctx.m_active_tab_hash) {
		ctx.m_active_tab_hash = std::hash<std::string>{}(ctx.m_tabs.front());
	}

	auto tab_container_pos = v2i{ ctx.m_pos.x + 8, ctx.m_pos.y + 32 };
	auto tab_container_size = v2i{ 128, ctx.m_size.y - 40 };
	render::filled_rect(tab_container_pos.x, tab_container_pos.y, tab_container_size.x, tab_container_size.y, {10, 10, 10, 255});
	for (auto i = 0; i < ctx.m_tabs.size(); i++) {
		auto tab_pos = v2i{ tab_container_pos.x, tab_container_pos.y + (i * 16) };
		auto tab_size = v2i{ tab_container_size.x, 16 };
		
		auto is_active = std::hash<std::string>{}(ctx.m_tabs[i]) == ctx.m_active_tab_hash;
		auto is_hovered = input::is_mouse_in_region(tab_pos, tab_size);
		if (is_hovered) {
			if (ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
				ctx.m_active_tab_hash = std::hash<std::string>{}(ctx.m_tabs[i]);
			}
			render::filled_rect(tab_pos.x, tab_pos.y, tab_size.x, tab_size.y, { 25, 25, 25, 255 });

		}
		else if (is_active) {
			render::filled_rect(tab_pos.x, tab_pos.y, tab_size.x, tab_size.y, { 35, 35, 35, 255 });
		}


		render::text(tab_pos.x + 2, tab_pos.y + 2, ctx.m_tabs[i], { 255, 255, 255, 255 });
	}

	render::rect(tab_container_pos.x, tab_container_pos.y, tab_container_size.x, tab_container_size.y, col_t::black());

	render::rect(ctx.m_pos.x, ctx.m_pos.y, ctx.m_size.x, ctx.m_size.y, { 0, 0, 0, 255 });
}

bool gui::tab(std::string title) {
	ctx.m_tabs.push_back(title);
	return ctx.m_active_tab_hash == std::hash<std::string>{}(title);
}

bool gui::checkbox(const std::string& title, bool* var) {
	auto label_pos = v2i{ ctx.m_cursor_pos.x + 4, ctx.m_cursor_pos.y + 2 };
	auto checkbox_size = v2i{ 12, 12 };
	auto checkbox_pos = v2i{ ctx.m_cursor_pos.x + ctx.m_container_size.x - checkbox_size.x - 4, ctx.m_cursor_pos.y + 4};

	auto is_hovering = input::is_mouse_in_region(checkbox_pos, checkbox_size);
	if (is_hovering && ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
		*var = !*var;
	}

	render::text(label_pos.x, label_pos.y, title, { 255, 255, 255, 255 });

	render::filled_rect(checkbox_pos.x, checkbox_pos.y, checkbox_size.x, checkbox_size.y, is_hovering ? col_t{ 25, 25, 25, 255 } : col_t{ 35, 35, 35, 255 });

	if (*var) {
		render::filled_rect(checkbox_pos.x + 2, checkbox_pos.y + 2, checkbox_size.x - 4, checkbox_size.y - 4, { 250, 128, 114, 255 });
		render::rect(checkbox_pos.x + 2, checkbox_pos.y + 2, checkbox_size.x - 4, checkbox_size.y - 4, { 250, 140, 128, 255 });
	}
	
	render::rect(checkbox_pos.x, checkbox_pos.y, checkbox_size.x, checkbox_size.y, col_t::black());

	ctx.m_cursor_pos.y += 20;
	return *var;
}

bool gui::button(const std::string& title, i32 width, bool end_line) {
	auto button_pos = v2i{ ctx.m_cursor_pos.x + 4, ctx.m_cursor_pos.y + 2};
	auto button_size = v2i{ width, 20 };

	auto is_hovered = input::is_mouse_in_region(button_pos, button_size);
	auto is_clicked = false;
	if (is_hovered) {
		if (ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
			is_clicked = true;
		}
	}

	render::filled_rect(button_pos.x, button_pos.y, button_size.x, button_size.y, is_hovered ? col_t{35, 35, 35, 255} : col_t{ 25, 25, 25, 255 });
	render::text(button_pos.x + 4, button_pos.y + 2, title, { 255, 255, 255, 255 });
	render::rect(button_pos.x, button_pos.y, button_size.x, button_size.y, col_t::black());

	if (end_line) {
		ctx.m_cursor_pos.y += 28;
	}
	else {
		ctx.m_cursor_pos.x += width + 4;
	}
	return is_clicked;
}

i32 gui::slider(const std::string& title, i32* var, i32 min_value, i32 max_value) {
	auto label_pos = v2i{ ctx.m_cursor_pos.x + 4, ctx.m_cursor_pos.y + 2 };
	auto slider_size = v2i{ ctx.m_container_size.x / 2 - 4, 16 };
	auto slider_pos = v2i{ ctx.m_cursor_pos.x + ctx.m_container_size.x - slider_size.x - 4, ctx.m_cursor_pos.y + 2 };

	render::text(label_pos.x, label_pos.y, title, col_t::white());

	auto dynamic_width = std::max((i32)(((float)*var - min_value) / (max_value - min_value) * slider_size.x - 2), 0);
	auto slider_thumb_size = v2i{ 8, 16 };
	auto nigg = std::max(dynamic_width - slider_thumb_size.x, 0);
	auto slider_thumb_pos = v2i{ slider_pos.x + nigg, slider_pos.y };

	render::filled_rect(slider_pos.x, slider_pos.y, slider_size.x, slider_size.y, { 25, 25, 25, 255 });
	render::filled_rect(slider_pos.x, slider_pos.y, dynamic_width, slider_size.y, { 250, 128, 114, 255 });
	render::filled_rect(slider_thumb_pos.x, slider_thumb_pos.y, slider_thumb_size.x, slider_thumb_size.y, { 35, 35, 35, 255 });
	render::rect(slider_thumb_pos.x, slider_thumb_pos.y, slider_thumb_size.x, slider_thumb_size.y, col_t::black());

	render::rect(slider_pos.x, slider_pos.y, slider_size.x, slider_size.y, col_t::black());

	ctx.m_cursor_pos.y += 20;
	return *var;
}

void gui::dropdown(const std::string& title, u32* var, const std::vector<std::string>& items) {
	auto label_pos = v2i{ ctx.m_cursor_pos.x + 4, ctx.m_cursor_pos.y + 2 };
	auto dropdown_size = v2i{ ctx.m_container_size.x / 2 - 4, 16 };
	auto dropdown_pos = v2i{ ctx.m_cursor_pos.x + ctx.m_container_size.x - dropdown_size.x - 4, ctx.m_cursor_pos.y + 2 };

	render::text(label_pos.x, label_pos.y, title, col_t::white());

	render::filled_rect(dropdown_pos.x, dropdown_pos.y, dropdown_size.x, dropdown_size.y, { 25, 25, 25, 255 });
	render::rect(dropdown_pos.x, dropdown_pos.y, dropdown_size.x, dropdown_size.y, col_t::black());
	ctx.m_cursor_pos.y += 20;
}
