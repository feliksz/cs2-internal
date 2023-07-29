#pragma once
#include <functional>
#include "../../types.hpp"

namespace gui {
	struct gui_context_t {
		v2i m_pos, m_size;
		v2i m_cursor_pos, m_container_size;
		const char* m_title;
		std::vector<std::string> m_tabs;
		std::size_t m_active_tab_hash;
	};

	inline gui_context_t ctx;

	void window(const v2i& pos, const v2i& size, const std::function<void()>& action);
	bool tab(std::string title);

	bool checkbox(const std::string& title, bool* var);
	bool button(const std::string& title, i32 width, bool end_line = true);
	i32 slider(const std::string& title, i32* var, i32 min_value, i32 max_value);
	void dropdown(const std::string& title, u32* var, const std::vector<std::string>& items);
}