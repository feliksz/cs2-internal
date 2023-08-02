#include <Windows.h>
#include "hooks/hooks.hpp"
#include "menu/config.hpp"
#include "sdk/interfaces.hpp"
#include "sdk/patterns.hpp"
#include "util/console.hpp"
#include "util/input.hpp"
#include "sdk/entity/CCSPlayerController.hpp"
#include "sdk/types.hpp"

#include "vendor/minhook/minhook.h"

static HMODULE module_instance{};

void cs2_initialize() {
	interfaces::initialize();
	patterns::initialize();
	input::initialize();
	config::initialize();

	const auto swapchain_ptr = memory::from_rel(memory::find_pattern(GetModuleHandleW(L"rendersystemdx11.dll"), "66 0F 7F 05 ? ? ? ? 66 0F 7F 0D ? ? ? ? 48 89 35 ? ? ? ?"), 0x4);
	interfaces::swapchain = *(IDXGISwapChain**)(**(uintptr_t**)swapchain_ptr + 0x178);

	MH_Initialize();
	MH_CreateHook((void*)((*(i64**)(interfaces::swapchain))[8]), (void*)hooks::Present, (void**)&hooks::o_Present);
	MH_CreateHook((void*)((*(i64**)(interfaces::swapchain))[13]), (void*)hooks::ResizeBuffers, (void**)&hooks::o_ResizeBuffers);
	MH_CreateHook((void*)((*(i64**)(interfaces::client))[31]), (void*)hooks::hkFrameStageNotify, (void**)&hooks::o_FrameStageNotify);
	MH_CreateHook(patterns::p_GetMatricesForView, (void*)hooks::hkGetMatricesForView, (void**)&hooks::o_GetMatricesForView);
	MH_EnableHook(MH_ALL_HOOKS);

	while (!GetAsyncKeyState(VK_DELETE)) {
		Sleep(10);
	}

	input::shutdown();

	MH_RemoveHook((void*)((*(i64**)(interfaces::swapchain))[8]));
	MH_RemoveHook((void*)((*(i64**)(interfaces::swapchain))[13]));
	MH_RemoveHook((void*)((*(i64**)(interfaces::client))[31]));
	MH_RemoveHook(patterns::p_GetMatricesForView);

	MH_DisableHook(MH_ALL_HOOKS);

	FreeLibraryAndExitThread(module_instance, 0);
}

int __stdcall DllMain(void* inst, u32 reason, void*) {
	if (reason == DLL_PROCESS_ATTACH) {
		module_instance = (HMODULE) inst;

#ifdef _DEBUG
		console::initialize();
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)cs2_initialize, inst, 0, 0);
#elif
		cs2_initialize();
#endif
	}
	else if (reason == DLL_PROCESS_DETACH) {
		console::shutdown();
	}


	return 1;
}