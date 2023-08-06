#pragma once
#include <d3d11.h>
#include "interfaces/CCSGOInput.hpp"
#include "interfaces/CGameEntitySystem.hpp"
#include "interfaces/ISchemaSystem.hpp"
#include "interfaces/IVEngineClient.hpp"
#include "types.hpp"

namespace interfaces {
	namespace _ {
		using CreateInterface_t = void* (*)(const char*, i32*);

		void* get_interface(const wchar_t* module_name, const char* interface_name);
	}
	bool initialize();

	inline void* client;
	inline ISchemaSystem* schema_system;
	inline IVEngineClient* engine;
	inline CCSGOInput* input;

	inline void* game_resource_system;
	inline CGameEntitySystem* game_entity_system;
	inline IDXGISwapChain* swapchain;


}