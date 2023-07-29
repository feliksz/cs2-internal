#pragma once
#include <string>
#include <unordered_map>
#include "../types.hpp"

#define CONFIG_GET(type, id) config::get<type>(id)
#define BOOL_GET(id) CONFIG_GET(bool, id)


namespace config {
	namespace detail {
		struct item_t {
			u8 data[32]{};
		};
		inline std::unordered_map<size_t, item_t> items{};
	}

	void initialize();
	void save();
	void load();

	std::vector<char> dump();

	template <typename T>
	constexpr static inline T& get(const std::string& id) {
		using namespace detail;

		auto hash = std::hash<std::string>{}(id);
		if (items.find(hash) == items.end()) {
			items[hash] = item_t();
		}

		return *(T*)(items[hash].data);
	}
}