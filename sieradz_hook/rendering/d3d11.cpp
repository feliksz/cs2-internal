#include "../hooks/hooks.hpp"
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_dx11.h"
#include "../imgui/imgui_impl_win32.h"
#include "../cs2.hpp"
#include "d3d11.hpp"
#pragma comment(lib, "d3d11.lib")
static bool create_d3d11_device() {
	DXGI_SWAP_CHAIN_DESC swap_chain_desc{};
	swap_chain_desc.Windowed = TRUE;
	swap_chain_desc.BufferCount = 2;
	swap_chain_desc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swap_chain_desc.OutputWindow = cs2::globals::window_handle;
	swap_chain_desc.SampleDesc.Count = 1;

	const D3D_FEATURE_LEVEL feature_levels[] = {
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_0
	};

	if (auto hr = D3D11CreateDeviceAndSwapChain(
		0,
		D3D_DRIVER_TYPE_NULL,
		0,
		0,
		feature_levels,
		2,
		D3D11_SDK_VERSION,
		&swap_chain_desc,
		&d3d11::swap_chain,
		&d3d11::d3d_device,
		0,
		0) != S_OK) {
		printf("couldn't init deviec and swapchain. error code: %lu\n", hr);
		return false;
	}

	return true;
}

void d3d11::initialize() {
	printf("creating d3d11 device...\n");
	create_d3d11_device();

	printf("hooking d3d11 functions...\n");
	hooks::present.create(swap_chain, 8, present_hk);
	hooks::resize_buffers.create(swap_chain, 13, resize_buffers_hk);

}

HRESULT __stdcall d3d11::present_hk(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags) {
	if (!ImGui::GetIO().BackendRendererUserData) {
		if (SUCCEEDED(pSwapChain->GetDevice(IID_PPV_ARGS(&d3d_device)))) {
			d3d_device->GetImmediateContext(&d3d_device_ctx);
			ImGui_ImplDX11_Init(d3d_device, d3d_device_ctx);
		}
	}

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGui::GetForegroundDrawList()->AddRectFilled({ 10, 10 }, { 200, 200 }, IM_COL32(255, 0, 255, 255));

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	return ((present_t)hooks::present.original_fn)(pSwapChain, SyncInterval, Flags);
}

HRESULT __stdcall d3d11::resize_buffers_hk(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags) {
	return ((resize_buffers_t)hooks::resize_buffers.original_fn)(pSwapChain, BufferCount, Width, Height, NewFormat, SwapChainFlags);
}
