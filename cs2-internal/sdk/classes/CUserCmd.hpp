#pragma once
#include "../types.hpp"

class CSubTickContainer {
public:
	i32 tick_count;
	char __pad0[0x4];
	u8* tick_ptr;
};

class CCmdQAngle {
public:
	char pad1[0x18];
	v3 viewangles;
};
static_assert(sizeof(CCmdQAngle) == 0x24);


class CUserCmdBase {
public:
	char __pad0[0x40];
	CCmdQAngle* view;
	char __pad1[0x8];
	float forwardmove;
	float sidemove;

};

class CUserCmd {
public:
	char __pad0[0x20];
	CSubTickContainer subtick_container;
	CUserCmdBase* base;
	char __pad1[0x18];
	u32 buttons;
};