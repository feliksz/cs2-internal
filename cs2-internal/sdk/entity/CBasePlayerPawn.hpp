#pragma once
#include "CBaseEntity.hpp"
#include "CPlayerObserverServices.hpp"

class CPlayerWeaponServices {
public:
	SCHEMA_FIELD_OFFSET(CHandle, m_hActiveWeapon, 0x60);
	SCHEMA_FIELD_OFFSET(CNetworkUtlVectorBase<CHandle>, m_hMyWeapons, 0x48);
};

class CBasePlayerPawn : public CBaseEntity {
public:
	SCHEMA_FIELD_OFFSET(CPlayerWeaponServices*, m_pWeaponServices, 0x1138);
	SCHEMA_FIELD_OFFSET(CPlayerObserverServices*, m_pObserverServices, 0x1150);
};