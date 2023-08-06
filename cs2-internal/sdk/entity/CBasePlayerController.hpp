#pragma once
#include "CBaseEntity.hpp"
#include "CBasePlayerPawn.hpp"

class CBasePlayerController : public CBaseEntity {
public:
	__forceinline bool IsAlive() {
		return m_iPawnHealth() > 0;
	}

	SCHEMA_FIELD_OFFSET(CHandle, m_hPawn, 0x5DC);
	SCHEMA_FIELD_OFFSET(u32, m_iPawnHealth, 0x800);
	SCHEMA_FIELD_OFFSET(bool, m_bIsLocalPlayerController, 0x6A0);
};