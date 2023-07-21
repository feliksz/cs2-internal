#pragma once
#include <d3d11.h>
#include <vector>
#include "minhook/MinHook.h"
#include "sdk/interfaces/game_resource_system.hpp"
#include "sdk/interfaces/entity_system.hpp"
#include "util/memory.hpp"
#include "types.hpp"

#pragma warning(disable : 6011)

// ░░░░░▄▄▄▄▀▀▀▀▀▀▀▀▄▄▄▄▄▄░░░░░░░
// ░░░░░█░░░░▒▒▒▒▒▒▒▒▒▒▒▒░░▀▀▄░░░░
// ░░░░█░░░▒▒▒▒▒▒░░░░░░░░▒▒▒░░█░░░
// ░░░█░░░░░░▄██▀▄▄░░░░░▄▄▄░░░░█░░
// ░▄▀▒▄▄▄▒░█▀▀▀▀▄▄█░░░██▄▄█░░░░█░
// █░▒█▒▄░▀▄▄▄▀░░░░░░░░█░░░▒▒▒▒▒░█
// █░▒█░█▀▄▄░░░░░█▀░░░░▀▄░░▄▀▀▀▄▒█
// ░█░▀▄░█▄░█▀▄▄░▀░▀▀░▄▄▀░░░░█░░█░
// ░░█░░░▀▄▀█▄▄░█▀▀▀▄▄▄▄▀▀█▀██░█░░
// ░░░█░░░░██░░▀█▄▄▄█▄▄█▄████░█░░░
// ░░░░█░░░░▀▀▄░█░░░█░█▀██████░█░░
// ░░░░░▀▄░░░░░▀▀▄▄▄█▄█▄█▄█▄▀░░█░░
// ░░░░░░░▀▄▄░▒▒▒▒░░░░░░░░░░▒░░░█░
// ░░░░░░░░░░▀▀▄▄░▒▒▒▒▒▒▒▒▒▒░░░░█░
// ░░░░░░░░░░░░░░▀▄▄▄▄▄░░░░░░░░█░░

namespace cs2 {
	namespace modules {
		inline memory::module_t client_dll, engine2_dll, rendersystemdx11_dll, gameoverlayrenderer64_dll;
	}

	struct c_swap_chain {
		char __pad[0x178];
		IDXGISwapChain* swap_chain;
	};
	namespace interfaces {
		inline void*                   client;
		inline c_game_resource_system* resource_system;

		inline ID3D11Device*           d3d_device;
		inline c_swap_chain* swap_chain;
	}

	namespace globals {
		inline HWND    window_handle;
		inline WNDPROC wndproc_orig;
	}


	HWND get_window_handle();
}