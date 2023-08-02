#include "../util/memory.hpp"
#include "patterns.hpp"

#define GET_PATTERN(var, mod, pat) \
	var = (decltype(var))memory::find_pattern(GetModuleHandleW(mod), pat); \
	printf(#var " -> 0x%llx\n", (u64)var);

#define GET_PATTERN_ABSOLUTE(var, mod, pat, rel, abs) \
	var = (decltype(var))memory::absolute(memory::find_pattern(GetModuleHandleW(mod), pat), rel, abs); \
	printf(#var " -> 0x%llx\n", (u64)var);

void patterns::initialize() {
	GET_PATTERN_ABSOLUTE(p_GetBaseEntity, L"client.dll", signatures::GET_BASE_ENTITY, 0x03, 0x00);
	GET_PATTERN_ABSOLUTE(p_GetHighestEntityIndex, L"client.dll", signatures::GET_HIGHEST_ENTITY_INDEX, 0x03, 0x00);
	GET_PATTERN_ABSOLUTE(p_GetLocalPlayerController, L"client.dll", signatures::GET_LOCAL_PLAYER_CONTROLLER, 0x01, 0x00);
	GET_PATTERN(p_GetMatricesForView, L"client.dll", signatures::GET_MATRICES_FOR_VIEW);
}
