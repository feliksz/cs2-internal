#include "../deps/imgui/imgui.h"
#include "../deps/imgui/imgui_impl_dx11.h"
#include "../deps/imgui/imgui_impl_win32.h"
#include "../hooks/hooks.hpp"
#include "../menu/menu.hpp"
#include "../cs2.hpp"
#include "d3d11.hpp"
#include "render.hpp"
#pragma comment(lib, "d3d11.lib")

#include "../sdk/entity/entities.hpp"
void d3d11::initialize() {
	printf("initializing d3d11 renderer...\n");
	
	set_swap_chain(cs2::interfaces::swap_chain);
	create_render_target();

	ImGui::CreateContext();

	ImGui::GetIO().BackendPlatformUserData = nullptr;

	ImGui_ImplWin32_Init(cs2::globals::window_handle);
	ImGui_ImplDX11_Init(d3d_device, d3d_device_ctx);

	printf("hooking d3d11 functions...\n");
	hooks::present.create(cs2::interfaces::swap_chain, 8, present_hk);
	hooks::resize_buffers.create(cs2::interfaces::swap_chain, 13, resize_buffers_hk);

}

void d3d11::deinitialize() {
	hooks::present.remove(cs2::interfaces::swap_chain, 8);
	hooks::resize_buffers.remove(cs2::interfaces::swap_chain, 13);
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

void render_esp() {
	for (auto i = 0; i < 32; i++) {
		auto entity = cs2::interfaces::resource_system->entity_system->get_base_entity(i);
		if (!entity)
			continue;

		auto handle = entity->get_ref_handle();
		if (!handle.is_valid())
			continue;

		printf("idx: %d\n", handle.m_index);
		if (!handle.as<CBaseEntity>()->IsBasePlayerController())
			continue;

		auto player = entity->get_ref_handle().as<CBasePlayerController>();
		auto health = player->m_iPawnHealth();

		auto pawn = player->m_hPawn().as<CBasePlayerPawn>();
		//->get_bounding_box();
		printf("hp: %i\n", health);
		//printf("bbox: %i %i %i %i\n", bbox.x, bbox.y, bbox.w, bbox.h);
		/*auto entity = *(CBaseEntity**)(controller + 0x10);
		if (!entity)
			continue;

		if (!entity->IsBasePlayerController())
			continue;

		printf("entity id: %i\n", 1);
		printf("\tcontroller: 0x%llx\n", (u64)controller);
		printf("\tidentity: 0x%llx\n", (u64)entity);
		printf("\thealth: %d\n", controller->m_iHealth());
		printf("\tpawn health: %d\n", controller->m_iPawnHealth());
		printf("\tname: %s\n", controller->m_sSanitizedPlayerName());*/
	}
}
HRESULT __stdcall d3d11::present_hk(IDXGISwapChain* thisptr, UINT sync_interval, UINT flags) {
	/*if (!ImGui::GetIO().BackendRendererUserData) {
		if (SUCCEEDED(thisptr->GetDevice(IID_PPV_ARGS(&d3d_device)))) {
			d3d_device->GetImmediateContext(&d3d_device_ctx);
			ImGui_ImplDX11_Init(d3d_device, d3d_device_ctx);
		}
	}*/

	//printf("swapchain: 0x%llx, sync_interval: %u, flags: %u\n", (u64)thisptr, sync_interval, flags);
	
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	render::_draw_list = ImGui::GetForegroundDrawList();

	//ImGui::GetForegroundDrawList()->AddRectFilled({ 10, 10 }, { 200, 200 }, IM_COL32(255, 0, 255, 255));
	menu::on_present();
	//render_esp();

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
