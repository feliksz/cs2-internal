#pragma once
#include <vector>
#include <Windows.h>
#include "../deps/minhook/MinHook.h"
#include "../types.hpp"

#pragma warning(disable : 6011)

namespace memory {
	struct module_t {
		void* ptr{};
		u64 size{};
		
		using create_interface_t = void*(*)(const char*, i32*);

		create_interface_t create_interface{};

		template <typename T>
		T get_interface(const char* interface_version) {
			if (!this->create_interface)
				return nullptr;

			// call createinterface export
			auto iface = this->create_interface(interface_version, nullptr);
			return (T)iface;
		}

		static module_t get(const wchar_t* module_name) {
			module_t ret;
			ret.ptr = GetModuleHandleW(module_name);

			const auto dos_hdr = (PIMAGE_DOS_HEADER)ret.ptr;
			const auto nt_hdr = (PIMAGE_NT_HEADERS)((u8*)ret.ptr + dos_hdr->e_lfanew);
			ret.size = nt_hdr->OptionalHeader.SizeOfImage;

			if (ret.ptr) {
				ret.create_interface = (create_interface_t)GetProcAddress((HMODULE)ret.ptr, "CreateInterface");
			}

			return ret;
		}

		operator bool() const {
			return !(this->ptr == nullptr);
		}
	};

	struct hook_t {
		bool create(void* target, u64 index, void* detour) {
			return printf("%s\n", MH_StatusToString(MH_CreateHook((void*)get_vfunc(target, index), detour, (void**)&original_fn))) == 0;
		}

		bool remove(void* target, u64 index) {
			return MH_RemoveHook((void*)get_vfunc(target, index)) == MH_OK;
			
		}

		u64 get_vfunc(void* cls, u64 index) {
			return (u64)((*(i64**)(cls))[index]);
		}

		void* original_fn;
	};

	template<typename T = i32>
	inline u8* from_rel(u8* address, u32 offset) {
		return address + *(T*)(address + offset) + sizeof(T) + offset;
	}

	u8* find_pattern(module_t mod, const char* pattern);

	template <typename T, u32 index = 0, typename... Args_t>
	inline T call_vfunc(void* base_class, Args_t... args) {
		using func_t = T(__thiscall*)(void*, decltype(args)...);
		return (*(func_t**)(base_class))[index](base_class, args...);
	}
}
