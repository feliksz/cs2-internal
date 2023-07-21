#pragma once
#include <D3D11.h>

namespace d3d11 {
	void initialize();
	void deinitialize();

	void create_render_target();
	void cleanup_render_target();
	
	void set_swap_chain(IDXGISwapChain* swap_chain);

	HRESULT WINAPI present_hk(IDXGISwapChain* thisptr, UINT sync_interval, UINT flags);
	HRESULT WINAPI resize_buffers_hk(IDXGISwapChain* thisptr, UINT buffer_count, UINT width, UINT height, DXGI_FORMAT new_format, UINT flags);

	using present_t = HRESULT(WINAPI*)(IDXGISwapChain*, UINT, UINT);
	using resize_buffers_t = HRESULT(WINAPI*)(IDXGISwapChain*, UINT, UINT, UINT, DXGI_FORMAT, UINT);

	inline ID3D11Device* d3d_device = nullptr;
	inline ID3D11DeviceContext* d3d_device_ctx = nullptr;
	inline ID3D11RenderTargetView* render_target_view = nullptr;
	inline IDXGISwapChain* swap_chain = nullptr;
}