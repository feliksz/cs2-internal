#pragma once
#include "../../types.hpp"

struct c_base_entity {
public:
	int& get_max_health() {
		return *(int*)((u64)this + 0x318);
	}

	int& get_health() {
		return *(int*)((u64)this + 0x31c);
	}
};