#pragma once
#include <vector>
#include <Windows.h>
#include "../sdk/types.hpp"

namespace memory {
	namespace _ {
		__forceinline static std::vector<i32> pattern_to_bytes(const char* pattern) {
			auto ret = std::vector<i32>{};
			auto start = (char*)pattern;
			auto end = (char*)pattern + strlen(pattern);
			for (auto i = start; i < end; i++) {
				auto is_wildcard = false;
				if (*i == '?') {
					i += *(i + 1) == '?' ? 2 : 1;
					is_wildcard = true;
				}

				ret.push_back(!is_wildcard ? strtoul(i, &i, 16) : -1);
			}

			return ret;
		}

		__forceinline u32 get_module_size(void* module_handle) {
			auto dos_header = (PIMAGE_DOS_HEADER)module_handle;
			auto nt_header = (PIMAGE_NT_HEADERS)((u8*)module_handle) + dos_header->e_lfanew;
			return nt_header->OptionalHeader.SizeOfImage;
		}
	}

	template<typename T = i32>
	__forceinline u8* from_rel(u8* address, u32 offset) {
		return address + *(T*)(address + offset) + sizeof(T) + offset;
	}

	__forceinline u8* absolute(u8* address, u32 rel = 0x01, u32 abs = 0x00) {
		auto jmp = address + rel;
		return jmp + abs + sizeof(i32) + *(i32*)jmp;
	}

	template <typename T, typename... Args>
	__forceinline T call_vfunc(void* base_class, u32 index, Args... args) {
		using Func = T(__thiscall*)(void*, decltype(args)...);
		return (*(Func**)(base_class))[index](base_class, args...);
	}

	// @to-do: compile-time IDA-style -> raw pattern conversion, use std::search
	__forceinline u8* find_pattern(void* module_handle, const char* pattern) {
		auto scan_bytes = (u8*)module_handle;
		auto size_of_image = _::get_module_size(module_handle);
		auto pattern_bytes = _::pattern_to_bytes(pattern);

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


}