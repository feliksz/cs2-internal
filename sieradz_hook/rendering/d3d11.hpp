#pragma once
#include <D3D11.h>

namespace d3d11 {
	void initialize();
	void deinitialize();

	HRESULT __stdcall present_hk(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
	HRESULT __stdcall resize_buffers_hk(IDXGISwapChain* pSwapChain,
		UINT BufferCount, UINT Width, UINT Height,
		DXGI_FORMAT NewFormat,
		UINT SwapChainFlags);

	using present_t = HRESULT(WINAPI*)(IDXGISwapChain*, UINT, UINT);
	using resize_buffers_t = HRESULT(WINAPI*)(IDXGISwapChain*, UINT, UINT, UINT, DXGI_FORMAT, UINT);

	inline ID3D11Device* d3d_device = nullptr;
	inline ID3D11DeviceContext* d3d_device_ctx = nullptr;
	inline IDXGISwapChain* swap_chain = nullptr;
}