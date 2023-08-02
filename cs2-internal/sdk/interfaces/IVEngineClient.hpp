#pragma once
#include "../../util/memory.hpp"

class IVEngineClient {
public:
	bool IsInGame() {
		return memory::call_vfunc<bool>(this, 30);
	}
};