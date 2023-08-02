#pragma once
#include <string>
#include <unordered_map>
#include "../sdk/types.hpp"
#include "../vendor/imgui/imgui.h"

#define CONFIG_GET(T, id) config::get<T>(std::hash<std::string>{}(id))
#define BOOL_GET(id) CONFIG_GET(bool, id)
#define KEYBIND_GET(id) CONFIG_GET(i32, id)

// @to-do: use something normal instead of that millionware meme
namespace config {
	struct item_t {
		u8 data[32]{};
	};

	inline std::unordered_map<u64, item_t> items{};

	void initialize();

	template <typename T>
	constexpr static inline T& get(u64 id) {
		if (items.find(id) == items.end()) {
			items[id] = item_t();
		}

		return *(T*)(items[id].data);
	}
}