#pragma once
#include "../schema.hpp"

class CCollisionProperty {
public:
	SCHEMA_FIELD_OFFSET(v3, m_vecMins, 0x40);
	SCHEMA_FIELD_OFFSET(v3, m_vecMaxs, 0x4C);
};