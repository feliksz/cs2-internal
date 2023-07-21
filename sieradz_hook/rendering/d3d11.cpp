#include "../deps/imgui/imgui.h"
#include "../deps/imgui/imgui_impl_dx11.h"
#include "../deps/imgui/imgui_impl_win32.h"
#include "../hooks/hooks.hpp"
#include "../menu/menu.hpp"
#include "../cs2.hpp"
#include "d3d11.hpp"
#pragma comment(lib, "d3d11.lib")

void d3d11::initialize() {
	printf("initializing d3d11 renderer...\n");
	
	set_swap_chain(cs2::interfaces::swap_chain->swap_chain);
	create_render_target();

	//ImGui::CreateContext();
	ImGui_ImplWin32_Init(cs2::globals::window_handle);
	ImGui_ImplDX11_Init(d3d_device, d3d_device_ctx);

	printf("hooking d3d11 functions...\n");
	hooks::present.create(cs2::interfaces::swap_chain->swap_chain, 8, present_hk);
	hooks::resize_buffers.create(cs2::interfaces::swap_chain->swap_chain, 13, resize_buffers_hk);

}

void d3d11::create_render_target() {
	ID3D11Texture2D* backbuffer;
	if (SUCCEEDED(swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backbuffer))) {
		D3D11_RENDER_TARGET_VIEW_DESC desc{};
		desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DMS;
		d3d_device->CreateRenderTargetView(backbuffer, &desc, &render_target_view);

		if (backbuffer) {
			backbuffer->Release();
			backbuffer = nullptr;
		}
	}
}

void d3d11::cleanup_render_target() {
	if (render_target_view) {
		render_target_view->Release();
		render_target_view = nullptr;
	}
}

void d3d11::set_swap_chain(IDXGISwapChain* swap_chain) {
	d3d11::swap_chain = swap_chain;
	d3d11::swap_chain->GetDevice(__uuidof(ID3D11Device), (void**)&d3d11::d3d_device);
	d3d11::d3d_device->GetImmediateContext(&d3d11::d3d_device_ctx);
}

HRESULT __stdcall d3d11::present_hk(IDXGISwapChain* thisptr, UINT sync_interval, UINT flags) {
	/*if (!ImGui::GetIO().BackendRendererUserData) {
		if (SUCCEEDED(thisptr->GetDevice(IID_PPV_ARGS(&d3d_device)))) {
			d3d_device->GetImmediateContext(&d3d_device_ctx);
			ImGui_ImplDX11_Init(d3d_device, d3d_device_ctx);
		}
	}*/

	printf("swapchain: 0x%llx, sync_interval: %u, flags: %u\n", (u64)thisptr, sync_interval, flags);
	
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	//ImGui::GetForegroundDrawList()->AddRectFilled({ 10, 10 }, { 200, 200 }, IM_COL32(255, 0, 255, 255));
	menu::on_present();
	d3d_device_ctx->OMSetRenderTargets(1, &render_target_view, 0);

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	return ((present_t)hooks::present.original_fn)(thisptr, sync_interval, flags);
}

HRESULT __stdcall d3d11::resize_buffers_hk(IDXGISwapChain* thisptr, UINT buffer_count, UINT width, UINT height, DXGI_FORMAT new_format, UINT flags) {
	auto resize_buffers = ((resize_buffers_t)hooks::resize_buffers.original_fn)(thisptr, buffer_count, width, height, new_format, flags);
	
	// cleanup
	cleanup_render_target();

	ImGui_ImplDX11_InvalidateDeviceObjects();
	if (SUCCEEDED(resize_buffers)) {
		set_swap_chain(thisptr);
		create_render_target();

		ImGui_ImplDX11_CreateDeviceObjects();
	}

	return resize_buffers;
}
