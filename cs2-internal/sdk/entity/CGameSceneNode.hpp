#pragma once
#include "../schema.hpp"

class CGameSceneNode {
public:
	SCHEMA_FIELD_OFFSET(const char*, m_name, 0xF0);
	SCHEMA_FIELD_OFFSET(v3, m_vecAbsOrigin, 0xC8);
};