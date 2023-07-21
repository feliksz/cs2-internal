#include "memory.hpp"

u8* memory::find_pattern(module_t mod, const char* pattern) {
	static auto pattern_to_byte = [](const char* pat) {
		auto bytes = std::vector<i32>{};
		auto start = (char*)pat;
		auto end = (char*)(pat)+strlen(pat);

		for (auto current = start; current < end; ++current) {
			if (*current == '?') {
				++current;
				if (*current == '?')
					++current;
				bytes.push_back(-1);
			}
			else {
				bytes.push_back(strtoul(current, &current, 16));
			}
		}
		return bytes;
	};

	auto size_of_image = mod.size;
	auto pattern_bytes = pattern_to_byte(pattern);
	auto scan_bytes = (u8*)mod.ptr;

	auto s = pattern_bytes.size();
	auto d = pattern_bytes.data();

	for (auto i = 0ul; i < size_of_image - s; ++i) {
		bool found = true;
		for (auto j = 0ul; j < s; ++j) {
			if (scan_bytes[i + j] != d[j] && d[j] != -1) {
				found = false;
				break;
			}
		}
		if (found) {
			return &scan_bytes[i];
		}
	}
	return nullptr;

}