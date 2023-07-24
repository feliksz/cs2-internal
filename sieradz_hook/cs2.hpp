#pragma once
#include <d3d11.h>
#include <vector>
#include "deps/minhook/MinHook.h"
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
		inline memory::module_t client_dll, engine2_dll, rendersystemdx11_dll;
	}

	namespace interfaces {
		inline void*                   client;
		inline c_game_resource_system* resource_system;

		inline IDXGISwapChain* swap_chain;
	}

	namespace globals {
		inline HWND    window_handle;
		inline WNDPROC wndproc_orig;
	}


	HWND get_window_handle();
}