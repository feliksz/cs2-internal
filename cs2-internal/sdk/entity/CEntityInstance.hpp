#pragma once
#include "../../util/memory.hpp"
#include "../interfaces/ISchemaSystem.hpp"
#include "CHandle.hpp"

class CEntityInstance {
public:
	__forceinline SchemaClassInfoData_t* Schema_DynamicBinding() {
		return memory::call_vfunc<SchemaClassInfoData_t*>(this, 0);
	}

	__forceinline CHandle GetRefEHandle() {
		CHandle handle;
		memory::call_vfunc<CHandle>(this, 2, &handle);
		return handle;
	}
};