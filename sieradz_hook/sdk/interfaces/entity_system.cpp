#include "../../util/memory.hpp"
#include "../../cs2.hpp"
#include "entity_system.hpp"

CBaseEntity* cs2::c_entity_system::get_base_entity(i32 index) {
	using get_base_entity_t = void* (__thiscall*)(void*, i32);
	static auto get_base_entity_ptr = (get_base_entity_t)memory::from_rel(memory::find_pattern(cs2::modules::client_dll, "8B D3 E8 ? ? ? ? 48 8B F8 48 85 C0 74 76") + 2, 1);
	//printf("cs2h get_base_entity -> 0x%llx\n", (u64)get_base_entity_ptr);
    return (CBaseEntity*) get_base_entity_ptr(this, index);
}


CBasePlayerController* cs2::c_entity_system::get_base_player_controller(i32 index) {
	using get_base_player_controller_t = CBasePlayerController*(__fastcall*)(void*, i32);
	static auto get_base_player_controller_fn = (get_base_player_controller_t)memory::find_pattern(cs2::modules::client_dll, "81 FA FE 7F 00 00 77 3B 8B C2 C1 F8 09 83 F8 3F");
	//printf("cs2h get_base_player_controller -> 0x%llx\n", (u64)get_base_player_controller_fn);
	return get_base_player_controller_fn(this, index);
}
