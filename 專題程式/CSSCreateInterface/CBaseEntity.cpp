#include "CBaseEntity.h"

//C_BaseEntity�~��IClientEntity��this���w�n�j�������ഫ��DWORD
//��]:

int C_BaseEntity::GetHealthValue()
{
	return *(int*)((DWORD)this + NetVarManagement->DT_BasePlayer.m_iHealth);//this���w�OCBaseEntity�ҫ��V������Address
}

int C_BaseEntity::GetTeamNumber()
{
	return *(int*)((DWORD)this + NetVarManagement->DT_BaseEntity.m_iTeamNum);
}

bool C_BaseEntity::GetlifeState()
{
	if (*(int*)((DWORD)this + NetVarManagement->DT_BasePlayer.m_lifeState) == 257)//257��ܪ��a���`
	{
		return false;
	}
	else
	{
		return true;
	}
}

Vector C_BaseEntity::GetvecOrigin()
{
	return *(Vector*)((DWORD)this + NetVarManagement->DT_BaseEntity.m_vecOrigin);
}

uintptr_t* C_BaseEntity::GetBoneMatrixPtr()
{
	return (uintptr_t*)((DWORD)this + 0x578);
}

bool C_BaseEntity::isDormant()
{
	return *(bool*)((DWORD)this + 0x17E);

}

int C_BaseEntity::GetArmorValue()
{
	return *(int*)((DWORD)this + NetVarManagement->DT_CSPlayer.m_ArmorValue);
}

uintptr_t* C_BaseEntity::GetThisptr()
{
	return (uintptr_t*)this;
}