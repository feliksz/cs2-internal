#pragma once
#include <d3d11.h>
#include <Windows.h>
#include "../sdk/types.hpp"

namespace hooks {
	bool __fastcall hkCreateMove(void* a1, i32 slot, bool active);
	inline bool(__fastcall* o_CreateMove)(void*, i32, bool);

	void __fastcall hkFrameStageNotify(void* rcx, i32 frameStage);
	inline void(__fastcall* o_FrameStageNotify)(void*, i32);

	void __fastcall hkGetMatricesForView(void* rcx, void* view, vmatrix_t* pWorldToView, vmatrix_t* pViewToProjection, vmatrix_t* pWorldToProjection, vmatrix_t* pWorldToPixels);
	inline HRESULT(__fastcall* o_GetMatricesForView)(void*, void*, vmatrix_t*, vmatrix_t*, vmatrix_t*, vmatrix_t*);

	HRESULT WINAPI Present(IDXGISwapChain* swapchain, UINT sync_interval, UINT flags);
	inline HRESULT(WINAPI* o_Present)(IDXGISwapChain*, UINT, UINT);

	HRESULT WINAPI ResizeBuffers(IDXGISwapChain* swapchain, UINT buffer_count, UINT width, UINT height, DXGI_FORMAT new_format, UINT flags);
	inline HRESULT(WINAPI* o_ResizeBuffers)(IDXGISwapChain*, UINT, UINT, UINT, DXGI_FORMAT, UINT);
}