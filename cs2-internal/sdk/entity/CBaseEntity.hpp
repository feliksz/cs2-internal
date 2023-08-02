#pragma once
#include "../schema.hpp"
#include "../types.hpp"
#include "CCollisionProperty.hpp"
#include "CEntityInstance.hpp"
#include "CGameSceneNode.hpp"

class CBaseEntity : public CEntityInstance {
public:
	SCHEMA_FIELD_VIRTUAL(bool, IsBasePlayerController, 142);
	SCHEMA_FIELD_VIRTUAL(bool, IsBaseWeaponController, 148);
	SCHEMA_FIELD_OFFSET(CGameSceneNode*, m_pGameSceneNode, 0x310);
	SCHEMA_FIELD_OFFSET(CCollisionProperty*, m_pCollision, 0x320);
	SCHEMA_FIELD_OFFSET(i32, m_iTeamNum, 0x3BF);

	bool get_bounding_box(bbox_t& bbox, bool compute_surrounding_box = false);
};