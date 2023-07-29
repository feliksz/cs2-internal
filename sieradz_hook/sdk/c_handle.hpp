#pragma once

class CBaseEntity;
class CHandle {
public:
	CBaseEntity* get_base_entity() const;

	__forceinline bool is_valid() const { return m_index != 0xFFFFFFFF; }

	template <typename T = CBaseEntity>
	__forceinline T* as() const {
		return (T*)get_base_entity();
	}

	u32 m_index;
};