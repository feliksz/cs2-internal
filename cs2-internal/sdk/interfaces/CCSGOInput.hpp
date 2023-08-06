#pragma once
#include "../classes/CUserCmd.hpp"
class CCSGOInput {
public:
	void* table;
	char __pad0[584];
	CUserCmd* m_pUserCmds;
	char __pad1[1];
	bool m_bInThirdPerson;
	char __pad2[34];
	i32 m_iSequenceNumber;
	uint64_t button_state1;
	uint64_t button_state2;
	uint64_t button_state3;
	uint64_t button_state4;
	float forwardmove;
	float sidemove;
	float upmove;

	auto GetUserCmd() {
		return &m_pUserCmds[m_iSequenceNumber % 150];
	}
};