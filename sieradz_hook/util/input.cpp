#include "../imgui/imgui_impl_win32.h"
#include "../cs2.hpp"
#include "input.hpp"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

void input::initialize() {
    ImGui::CreateContext();
    ImGui_ImplWin32_Init(cs2::globals::window_handle);
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    cs2::globals::wndproc_orig = (WNDPROC)SetWindowLongPtrW(cs2::globals::window_handle, GWLP_WNDPROC, (LONG_PTR)input::wndproc_hk);
}

bool input::is_key_down(u32 key_code) {
    return ImGui::IsKeyDown(ImGuiKey_A);
}

LRESULT input::wndproc_hk(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param) {
    if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, w_param, l_param))
        return true;

    //printf("wndproc [handle: 0x%llx, msg: %u, wparam: %llu, lparam: %llu]\n", (u64)hwnd, msg, w_param, l_param);
    return CallWindowProcA(cs2::globals::wndproc_orig, hwnd, msg, w_param, l_param);
}
