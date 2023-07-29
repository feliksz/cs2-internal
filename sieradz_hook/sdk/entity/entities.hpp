#pragma once
#include "../../util/memory.hpp"
#include "../c_handle.hpp"

#define NOMINMAX

class CEntityInstance {
public:
	CHandle get_ref_handle() {
		CHandle ret;
		memory::call_vfunc<void*, 2>(this, &ret);
		return ret;
	}

};

class CGameSceneNode {
public:
	v3& m_vecOrigin() {
		return *(v3*)(u64(this) + 0x80);
	}

	transform_t& m_nodeToWorld() {
		return *(transform_t*)(u64(this) + 0x10);
	}
};

class CCollisionProperty {
	struct {
		u64 m_collisionAttribute = 0x10;
		u64 m_vecMins = 0x40;
		u64 m_vecMaxs = 0x4C;
	} offsets;
public:
	v3& m_vecMins() {
		return *(v3*)(u64(this) + offsets.m_vecMins);
	}

	v3& m_vecMaxs() {
		return *(v3*)(u64(this) + offsets.m_vecMaxs);
	}
};


class CGameSceneNode;
class CBasePlayerController;
class CBaseEntity : public CEntityInstance {
	struct {
		u64 m_iHealth = 0x32C;
		u64 m_iTeamNum = 0x3BF;
		u64 m_pGameSceneNode = 0x310;
		u64 m_pCollision = 0x320;
	} offsets;
public:
	bool IsBasePlayerController() {
		return memory::call_vfunc<bool, 142>(this);
	}

	CCollisionProperty*& m_pCollision() {
		return *(CCollisionProperty**)(u64(this) + offsets.m_pCollision);
	}

	CGameSceneNode*& m_pGameSceneNode() {
		return *(CGameSceneNode**)(u64(this) + offsets.m_pGameSceneNode);
	}

	uint8_t& m_iTeamNum() {
		return *(uint8_t*)(u64(this) + offsets.m_iTeamNum);
	}

	
	v4i get_bounding_box() {
		auto collision = m_pCollision();
		auto scene_node = m_pGameSceneNode();
		if (!collision || !scene_node)
			return v4i{};

		auto origin = scene_node->m_vecOrigin();
		auto mins = collision->m_vecMins(), maxs = collision->m_vecMaxs();
		
		v2 min{}, max{};
		min = { mins.x + origin.x, mins.y + origin.y };
		max = { maxs.x + origin.x, maxs.y + origin.y };
		printf("%f %f %f %f\n", mins.x, mins.y, maxs.x, maxs.y);
		return { (i32)min.x, (i32)min.y, (i32)max.x, (i32)max.y };
	}
};

class CBasePlayerPawn : public CBaseEntity {
	struct {
		u64 m_hController = 0x12BC;
	} offsets;
public:
	CHandle& m_hController() const {
		return *(CHandle*)(u64(this) + offsets.m_hController);
	}
};

class CBasePlayerController : public CBaseEntity {
	struct {
		u64 m_hPawn = 0x5DC;
		u64 m_iHealth = 0x800;
		u64 m_sSanitizedPlayerName = 0x720;
	} offsets;

public:
	CHandle& m_hPawn() {
		return *(CHandle*)(u64(this) + offsets.m_hPawn);
	}

	u32& m_iHealth() {
		return *(u32*)(u64(this) + 0x32c);
	}

	u32& m_iPawnHealth() {
		return *(u32*)(u64(this) + 0x800);
	}

	const char* m_sSanitizedPlayerName() {
		return *(const char**)(u64(this) + offsets.m_sSanitizedPlayerName);
	}
	/*const char*& m_sSanitizedPlayerName() {
		return *(const char**)(u64(this) + offsets.m_sSanitizedPlayerName);
	}*/

};
