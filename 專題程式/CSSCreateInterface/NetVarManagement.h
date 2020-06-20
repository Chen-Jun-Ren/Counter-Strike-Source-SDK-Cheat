#pragma once
#include "cdll_int.h"
#include "Global.h"
class CNetVarManagement
{
public:
	CNetVarManagement();
public:
	struct
	{
		uintptr_t m_iHealth;
		uintptr_t m_lifeState;

	}DT_BasePlayer;

	struct
	{
		uintptr_t m_iName;
		uintptr_t m_iTeamNum;
		uintptr_t m_vecOrigin;

	}DT_BaseEntity;

	struct
	{
		uintptr_t m_ArmorValue;

	}DT_CSPlayer;
};

extern CNetVarManagement* NetVarManagement;