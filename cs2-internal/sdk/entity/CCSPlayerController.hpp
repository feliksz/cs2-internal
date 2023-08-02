#pragma once
#include "CBasePlayerController.hpp"
class CCSPlayerController : public CBasePlayerController {
public:
	SCHEMA_FIELD_OFFSET(const char*, m_sSanitizedPlayerName, 0x720);
};