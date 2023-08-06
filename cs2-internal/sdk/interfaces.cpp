#include <Windows.h>
#include "../util/console.hpp"
#include "interfaces.hpp"

#define GET_INTERFACE(iface, mod, ver) \
	iface = (decltype(iface))interfaces::_::get_interface(L##mod, ver); \
	LOG(#iface " -> 0x%llx\n", (u64)iface);

#define GET_INTERFACE_CUSTOM(iface, addr) \
	iface = (decltype(iface))addr; \
	LOG(#iface " -> 0x%llx\n", (u64)iface)

bool interfaces::initialize() {
	GET_INTERFACE(client, "client.dll", "Source2Client002");
	GET_INTERFACE(schema_system, "schemasystem.dll", "SchemaSystem_001");
	GET_INTERFACE(engine, "engine2.dll", "Source2EngineToClient001");
	GET_INTERFACE(game_resource_system, "engine2.dll", "GameResourceServiceClientV001");
	
	GET_INTERFACE_CUSTOM(game_entity_system, *(CGameEntitySystem**)(u64(game_resource_system) + 0x58));
	GET_INTERFACE_CUSTOM(input, *(CCSGOInput**)(memory::absolute(memory::find_pattern(GetModuleHandleW(L"client.dll"), "48 8B 0D ? ? ? ? 48 8B 01 FF 50 ? 8B DF"), 0x3)));
	//printf("%i\n", schema_system->GetTypeScopes().m_size);
	return true;
}

void* interfaces::_::get_interface(const wchar_t* module_name, const char* interface_name) {
	auto module_handle = GetModuleHandleW(module_name);
	if (!module_handle)
		return nullptr;

	auto create_interface_exp = GetProcAddress(module_handle, "CreateInterface");
	if (!create_interface_exp)
		return nullptr;

	return ((CreateInterface_t)create_interface_exp)(interface_name, nullptr);
}
