#pragma once
#include <Windows.h>
#include "../util/memory.hpp"

namespace hooks {
	inline memory::hook_t present;
	inline memory::hook_t resize_buffers;
	inline memory::hook_t create_move;

}