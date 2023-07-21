#include "cs2.hpp"

HWND cs2::get_window_handle() {
	// @todo: rewrite because vac is probably hookin this bih fr fr
	return FindWindowW(nullptr, L"Counter-Strike 2");
}
