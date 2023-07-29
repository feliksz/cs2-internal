#include <iostream>
#include <Windows.h>
#include "menu/config.hpp"
#include "rendering/d3d11.hpp"
#include "util/input.hpp"
#include "cs2.hpp"

#pragma warning(suppress : 6387)

#define GET_MODULE_AND_PRINT(md, mdn) md = memory::module_t::get(mdn); if (!md) { printf(#md " -> failed\n"); return false; } printf(#md " -> 0x%llx\n", (u64)md.ptr);
#define GET_INTERFACE_AND_PRINT(id, md, iv) id = md.get_interface<decltype(id)>(iv); if (!id) { printf(#id " -> failed\n"); return false; } printf(#id " -> 0x%llx\n", (u64)id);

void initialize_console() {
	AllocConsole();
	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
}

bool initialize_modules() {
	printf("initializing modules...\n");
	GET_MODULE_AND_PRINT(cs2::modules::client_dll, L"client.dll");
	GET_MODULE_AND_PRINT(cs2::modules::engine2_dll, L"engine2.dll");
	GET_MODULE_AND_PRINT(cs2::modules::rendersystemdx11_dll, L"rendersystemdx11.dll");
	return true;
}

bool initialize_interfaces() {
	printf("initializing interfaces...\n");
	GET_INTERFACE_AND_PRINT(cs2::interfaces::client, cs2::modules::client_dll, "Source2Client002");
	GET_INTERFACE_AND_PRINT(cs2::interfaces::resource_system, cs2::modules::engine2_dll, "GameResourceServiceClientV001");

	const auto swap_chain_ptr = memory::from_rel(memory::find_pattern(cs2::modules::rendersystemdx11_dll, "66 0F 7F 05 ? ? ? ? 66 0F 7F 0D ? ? ? ? 48 89 35 ? ? ? ?"), 0x4);
	cs2::interfaces::swap_chain = *(IDXGISwapChain**)(**(uintptr_t**)swap_chain_ptr + 0x178);
	printf("cs2::interfaces::swap_chain -> 0x%llx\n", (u64)cs2::interfaces::swap_chain);

	return true;
}


bool initialize_hooks() {
	printf("initializing hooks...\n");

	MH_Initialize();
	input::initialize();
	d3d11::initialize();
	MH_EnableHook(MH_ALL_HOOKS);

	return true;
}

bool revert_hooks() {
	input::deinitialize();
	d3d11::deinitialize();
	MH_DisableHook(MH_ALL_HOOKS);

	return true;
}

unsigned long __stdcall start(void* instance) {
	initialize_console();

	printf("sieradzhook (c) thc mafia hooligans\ndel - uninject; end - menu\n\n ");

	// get window handle
	cs2::globals::window_handle = cs2::get_window_handle();
	printf("window handle -> 0x%llu\n", (u64)cs2::globals::window_handle);

	if (!initialize_modules() || !initialize_interfaces() || !initialize_hooks()) {
		printf("failed to initialize cheat...\n");
		return 0ul;
	}

	config::initialize();
	config::save();

	// all done!
	printf("done!\n");

	// wait for exit
	while (!ImGui::IsKeyDown(ImGuiKey_Delete)) {
		Sleep(10);
	}

	revert_hooks();

	FreeConsole();
	FreeLibraryAndExitThread((HMODULE)instance, 0);
	return 0ul;
}

int __stdcall DllMain(HINSTANCE instance, UINT reason, LPVOID reserved) {
	if (reason == DLL_PROCESS_ATTACH) {
		// inject
		DisableThreadLibraryCalls(instance);
		auto fred = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)start, instance, 0, 0);
		if (fred) {
			CloseHandle(fred);
		}

	}
	else if (reason == DLL_PROCESS_DETACH && !reserved) {
		// uninject
	}

	return 
		TRUE;
}