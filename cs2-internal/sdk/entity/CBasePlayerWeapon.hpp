#pragma once
#include "CEconEntity.hpp"

class CBasePlayerWeapon : public CEconEntity {
public:
	SCHEMA_FIELD_OFFSET(CHandle, m_hOwnerEntity, 0x418);
	SCHEMA_FIELD_OFFSET(i32, m_iClip1, 0x160C);
	SCHEMA_FIELD_OFFSET(i32, m_iClip2, 0x1610);
};