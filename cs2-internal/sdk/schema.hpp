#pragma once
#include <memory>
#include "../util/memory.hpp"
#include "types.hpp"

#define SCHEMA_FIELD_OFFSET(type, var, offset)					\
	__forceinline std::add_lvalue_reference_t<type> var() {					\
		return *(std::add_pointer_t<type>)(u64(this) + offset); \
	}

#define SCHEMA_FIELD_VIRTUAL(type, var, index, ...) \
	__forceinline type var() { \
		return memory::call_vfunc<type>(this, index, __VA_ARGS__); \
	}

// @to-do: schema manager
namespace schema {
	void initialize();
}
