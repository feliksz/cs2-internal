#pragma once
#include "../../util/memory.hpp"
#include "CHandle.hpp"

class CEntityInstance {
public:
	__forceinline CHandle get_ref_handle() {
		CHandle handle;
		memory::call_vfunc<CHandle>(this, 2, &handle);
		return handle;
	}
};