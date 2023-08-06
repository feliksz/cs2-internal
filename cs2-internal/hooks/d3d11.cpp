#include <iostream>
#include "../vendor/imgui/imgui_impl_dx11.h"
#include "../vendor/imgui/imgui_impl_win32.h"
#include "../util/render.hpp"
#include "hooks.hpp"

#include "../features/features.hpp"
static ID3D11Device* d3d_device;
static ID3D11DeviceContext* d3d_context;
static ID3D11RenderTargetView* d3d_target_view;

static void create_render_target(IDXGISwapChain* swapchain) {
	ID3D11Texture2D* backbuffer;
	if (SUCCEEDED(swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backbuffer))) {
		D3D11_RENDER_TARGET_VIEW_DESC desc{};
		desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DMS;
		d3d_device->CreateRenderTargetView(backbuffer, &desc, &d3d_target_view);

		if (backbuffer) {
			backbuffer->Release();
			backbuffer = nullptr;
		}
	}
}
#include "../menu/menu.hpp"
static auto imgui_initialized = false;
HRESULT WINAPI hooks::Present(IDXGISwapChain* swapchain, UINT sync_interval, UINT flags) {
	if (!imgui_initialized) {
		if (SUCCEEDED(swapchain->GetDevice(IID_PPV_ARGS(&d3d_device)))) {
			d3d_device->GetImmediateContext(&d3d_context);
			
			ImGui_ImplDX11_Init(d3d_device, d3d_context);
			imgui_initialized = true;

			auto& style = ImGui::GetStyle();
			style.AntiAliasedLines = false;
			style.AntiAliasedFill = false;

			render::initialize_fonts();
		}
		else {
			printf("couldn't init imgui.\n");
		}
	}

	if (!d3d_target_view && imgui_initialized) {
		create_render_target(swapchain);
	}
	else if (imgui_initialized) {
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		render::_draw_list = ImGui::GetForegroundDrawList();

		features::visuals::draw();
		render::text(9, 9, "Jacek \"Ganja\" Internal By ThcFaniPl " __DATE__, col_t::black());
		render::text(11, 9, "Jacek \"Ganja\" Internal By ThcFaniPl " __DATE__, col_t::black());
		render::text(9, 11, "Jacek \"Ganja\" Internal By ThcFaniPl " __DATE__, col_t::black());
		render::text(11, 11, "Jacek \"Ganja\" Internal By ThcFaniPl " __DATE__, col_t::black());
		render::text(10, 10, "Jacek \"Ganja\" Internal By ThcFaniPl " __DATE__, col_t::white());

		if (ImGui::IsKeyPressed(ImGuiKey_Insert, false)) {
			menu::is_open = !menu::is_open;
		}

		if (menu::is_open) {
			menu::draw();
		}

		ImGui::Render();
		d3d_context->OMSetRenderTargets(1, &d3d_target_view, 0);

		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}

	return o_Present(swapchain, sync_interval, flags);
}

HRESULT __stdcall hooks::ResizeBuffers(IDXGISwapChain* swapchain, UINT buffer_count, UINT width, UINT height, DXGI_FORMAT new_format, UINT flags) {
	auto resize_buffers = o_ResizeBuffers(swapchain, buffer_count, width, height, new_format, flags);

	if (d3d_target_view) {
		d3d_target_view->Release();
		d3d_target_view = nullptr;
	}

	ImGui_ImplDX11_InvalidateDeviceObjects();
	if (SUCCEEDED(resize_buffers)) {
		create_render_target(swapchain);

		swapchain->GetDevice(IID_PPV_ARGS(&d3d_device));
		d3d_device->GetImmediateContext(&d3d_context);


		ImGui_ImplDX11_CreateDeviceObjects();
	}

	return resize_buffers;
}