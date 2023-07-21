#include "../../util/memory.hpp"
#include "../../cs2.hpp"
#include "entity_system.hpp"

void* cs2::c_entity_system::get_base_entity(i32 index) {
	using get_base_entity_t = void* (__thiscall*)(void*, i32);
	static auto get_base_entity_ptr = (get_base_entity_t)memory::from_rel(memory::find_pattern(cs2::modules::client_dll, "8B D3 E8 ? ? ? ? 48 8B F8 48 85 C0 74 76") + 2, 1);
    return get_base_entity_ptr(this, index);
}
