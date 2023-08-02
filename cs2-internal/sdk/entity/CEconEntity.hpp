#pragma once
#include "CBaseEntity.hpp"

class CEconItemDefinition {
public:
	SCHEMA_FIELD_OFFSET(const char*, GetSimpleWeaponName, 0x210);
};
class CEconItemView {
public:
	SCHEMA_FIELD_VIRTUAL(CEconItemDefinition*, GetStaticData, 13);

	SCHEMA_FIELD_OFFSET(u64, m_iItemID, 0x1C8);
	SCHEMA_FIELD_OFFSET(u32, m_iItemIDHigh, 0x1D0);
	SCHEMA_FIELD_OFFSET(u32, m_iItemIDLow, 0x1D4);
};

class CAttributeManager {
public:
	SCHEMA_FIELD_OFFSET(CEconItemView, m_Item, 0x50);
};

class CEconEntity : public CBaseEntity {
public:
	SCHEMA_FIELD_OFFSET(CAttributeManager, m_AttributeManager, 0x10D0);
};