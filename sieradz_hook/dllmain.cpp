#include <iostream>
#include <Windows.h>
#include "rendering/d3d11.hpp"
#include "util/input.hpp"
#include "cs2.hpp"

#pragma warning(suppress : 6387)

#define GET_MODULE_AND_PRINT(md, mdn) md = memory::module_t::get(mdn); if (!md) { printf(#md " -> failed\n"); return false; } printf(#md " -> 0x%llx\n", (u64)md.ptr);
#define GET_INTERFACE_AND_PRINT(id, md, iv) id = md.get_interface<decltype(id)>(iv); if (!id) { printf("%s -> failed\n", #id); return false; } printf(#id " -> 0x%llx\n", (u64)id);

void initialize_console() {
	AllocConsole();
	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
}

bool initialize_modules() {
	printf("initializing modules...\n");
	GET_MODULE_AND_PRINT(cs2::modules::client_dll, L"client.dll");
	GET_MODULE_AND_PRINT(cs2::modules::engine2_dll, L"engine2.dll");
	GET_MODULE_AND_PRINT(cs2::modules::rendersystemdx11_dll, L"rendersystemdx11.dll");
	GET_MODULE_AND_PRINT(cs2::modules::gameoverlayrenderer64_dll, L"gameoverlayrenderer64.dll");
	return true;
}

bool initialize_interfaces() {
	printf("initializing interfaces...\n");
	GET_INTERFACE_AND_PRINT(cs2::interfaces::client, cs2::modules::client_dll, "Source2Client002");
	GET_INTERFACE_AND_PRINT(cs2::interfaces::resource_system, cs2::modules::engine2_dll, "GameResourceServiceClientV001");
	cs2::interfaces::swap_chain = **(cs2::c_swap_chain***)(memory::from_rel(memory::find_pattern(cs2::modules::rendersystemdx11_dll, "66 0F 7F 05 ? ? ? ? 66 0F 7F 0D ? ? ? ? 48 89 35 ? ? ? ?"), 0x4));
	cs2::interfaces::d3d_device = (ID3D11Device*)memory::from_rel(memory::find_pattern(cs2::modules::rendersystemdx11_dll, " 48 89 1D ? ? ? ? 48 89 3D"), 0xA);
	printf("cs2::interfaces::swap_chain -> 0x%llx, ->swap_chain -> 0x%llx\n", (u64)cs2::interfaces::swap_chain, (u64)cs2::interfaces::swap_chain->swap_chain);
	printf("cs2::interfaces::device -> 0x%llx\n", (u64)cs2::interfaces::d3d_device);
	return true;
}


bool initialize_hooks() {
	printf("initializing hooks...\n");

	MH_Initialize();

	input::initialize();
	d3d11::initialize();
	//printf("d3d11 device -> 0x%llx\n", (u64)memory::find_pattern())

	//printf("mhstatus: %s\n", MH_StatusToString(MH_CreateHook(cs2::interfaces::swap_chain->swap_chain, (void*)hkPresent, &present_og)));
	printf("mhstatus e: %s\n", MH_StatusToString(MH_EnableHook(MH_ALL_HOOKS)));
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

	// all done!
	printf("done!\n");

	// wait for exit
	while (true) {
		//printf("%i\n", (i32)ImGui::IsKeyDown(ImGuiKey_UpArrow));
		Sleep(10);
	}

	// wypierdalaj
	FreeLibraryAndExitThread((HMODULE)instance, 0);
	return 0ul;
}

void stop() {
	printf("exiting... (SOOO EXITED!!!)\n");
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
		stop();
	}

	return 
		TRUE;
}