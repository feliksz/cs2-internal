#pragma once
#include "../../util/memory.hpp"

class IVEngineClient {
public:
	bool IsInGame() {
		return memory::call_vfunc<bool, 30>(this);
	}

	bool IsConnected() {
		return memory::call_vfunc<bool, 31>(this);
	}
};