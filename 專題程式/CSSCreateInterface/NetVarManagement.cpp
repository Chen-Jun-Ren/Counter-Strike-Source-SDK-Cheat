#include "include.h"
#include "dt_recv.h"
#include "cdll_int.h"
#include "NetVarManagement.h"
#include "CreateInterface.h"

CNetVarManagement* NetVarManagement;

intptr_t GetOffset(RecvTable* table, const char* tableName, const char* netvarName)
{
	for (int i = 0; i < table->m_nProps; i++)
	{
		RecvProp prop = table->m_pProps[i];

		if (!_stricmp(prop.m_pVarName, netvarName))
		{
			return prop.m_Offset;
		}

		if (prop.m_pDataTable)
		{
			intptr_t offset = GetOffset(prop.m_pDataTable, tableName, netvarName);

			if (offset)
			{
				return offset + prop.m_Offset;
			}
		}
	}
	return 0;
}

intptr_t GetNetVarOffset(const char* tableName, const char* netvarName, ClientClass* clientClass)
{
	ClientClass* currNode = clientClass;

	for (auto currNode = clientClass; currNode; currNode = currNode->m_pNext)
	{
		if (!_stricmp(tableName, currNode->m_pRecvTable->m_pNetTableName))
		{
			return GetOffset(currNode->m_pRecvTable, tableName, netvarName);
		}
	}

	return 0;
}

CNetVarManagement::CNetVarManagement()
{
	ClientClass* clientClass = Interface->BaseClientDLL->GetAllClasses();

	this->DT_BasePlayer.m_iHealth = GetNetVarOffset("DT_BasePlayer", "m_iHealth", clientClass);
	this->DT_BasePlayer.m_lifeState = GetNetVarOffset("DT_BasePlayer", "m_lifeState", clientClass);
	this->DT_BaseEntity.m_iTeamNum = GetNetVarOffset("DT_BaseEntity", "m_iTeamNum", clientClass);
	this->DT_BaseEntity.m_vecOrigin = GetNetVarOffset("DT_BaseEntity", "m_vecOrigin", clientClass);
	this->DT_CSPlayer.m_ArmorValue = GetNetVarOffset("DT_CSPlayer", "m_ArmorValue", clientClass);
}
