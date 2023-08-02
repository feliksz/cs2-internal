#include "../sdk/types.hpp"
#include "../globals.hpp"
#include "hooks.hpp"

void __fastcall hooks::hkGetMatricesForView(void* rcx, void* view, vmatrix_t* pWorldToView, vmatrix_t* pViewToProjection, vmatrix_t* pWorldToProjection, vmatrix_t* pWorldToPixels) {
	o_GetMatricesForView(rcx, view, pWorldToView, pViewToProjection, pWorldToProjection, pWorldToPixels);

	globals::view_matrix = *pWorldToProjection;
}