#pragma once
#include "types.hpp"
namespace patterns {
	namespace signatures {
		constexpr static auto GET_BASE_ENTITY = "8B D3 E8 ? ? ? ? 48 8B F8 48 85 C0 74 76";
		constexpr static auto GET_HIGHEST_ENTITY_INDEX = "33 DB E8 ? ? ? ? 8B 08";
		constexpr static auto GET_LOCAL_PLAYER_CONTROLLER = "E8 ? ? ? ? 49 89 47 08";
		constexpr static auto GET_MATRICES_FOR_VIEW = "40 53 48 81 EC ? ? ? ? 49 8B C1";
	}

	void initialize();

	inline void*(__thiscall* pfnGetBaseEntity)(void*, i32);
	inline i32(__thiscall* pfnGetHighestEntityIndex)(void*, i32*);
	inline void* (__fastcall* pfnGetLocalPlayerController)(i32);
	inline void* pfnGetMatricesForView{};

}