#pragma once
#include "../types.hpp"

class CBaseEntity;

class CHandle {
public:
	u32 m_index;

	__forceinline bool is_valid() const {
		return m_index != 0xFFFFFFFF;
	}

	__forceinline i32 get_index() const {
		return m_index & 0x7fff;
	}

	template <typename T = CBaseEntity>
	__forceinline T* get() {
		return (T*) get_base_entity();
	}

private:
	CBaseEntity* get_base_entity();
};