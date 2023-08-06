#pragma once
#include "CBaseEntity.hpp"

class CPlayerObserverServices {
public:
	SCHEMA_FIELD_OFFSET(u8, m_iObserverMode, 0x40);
	SCHEMA_FIELD_OFFSET(CHandle, m_hObserverTarget, 0x44);
};