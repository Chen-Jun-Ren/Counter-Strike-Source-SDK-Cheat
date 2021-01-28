#include "CBaseEntity.h"

//C_BaseEntity繼承IClientEntity後this指針要強制類型轉換成DWORD
//原因:

int C_BaseEntity::GetHealthValue()
{
	return *(int*)((DWORD)this + NetVarManagement->DT_BasePlayer.m_iHealth);//this指針是CBaseEntity所指向的物件Address
}

int C_BaseEntity::GetTeamNumber()
{
	return *(int*)((DWORD)this + NetVarManagement->DT_BaseEntity.m_iTeamNum);
}

bool C_BaseEntity::GetlifeState()
{
	if (*(int*)((DWORD)this + NetVarManagement->DT_BasePlayer.m_lifeState) == 257)//257表示玩家死亡
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


bool C_BaseEntity::isDormant()
{
	return *(bool*)((DWORD)this + 0x17E);

}

Vector C_BaseEntity::GetPos()
{
	const DWORD dw_Pos = 0x260;
	return *(Vector*)((DWORD)this + dw_Pos);
}



int C_BaseEntity::GetArmorValue()
{
	return *(int*)((DWORD)this + NetVarManagement->DT_CSPlayer.m_ArmorValue);
}

uintptr_t* C_BaseEntity::GetThisptr()
{
	return (uintptr_t*)this;
}

bool C_BaseEntity::IsPlayer()
{
	if (this->GetClientClass()->m_ClassID == ClassId->CCSPlayer)
		return true;
	return false;
}

bool C_BaseEntity::IsPlayer_Aim()
{
	if (this->GetClientClass()->m_ClassID == AimClassId->CCSPlayer)
		return true;
	return false;
}

bool C_BaseEntity::IsWeapon()
{
	const int id = this->GetClientClass()->m_ClassID;
	if (id == ClassId->CBaseCombatWeapon ||
		id == ClassId->CAK47 ||
		id == ClassId->CWeaponAug ||
		id == ClassId->CWeaponAWP ||
		id == ClassId->CWeaponCSBase ||
		id == ClassId->CWeaponCSBaseGun ||
		id == ClassId->CWeaponElite ||
		id == ClassId->CWeaponFamas ||
		id == ClassId->CWeaponFiveSeven ||
		id == ClassId->CWeaponG3SG1 ||
		id == ClassId->CWeaponGalil ||
		id == ClassId->CWeaponGlock ||
		id == ClassId->CWeaponM249 ||
		id == ClassId->CWeaponM3 ||
		id == ClassId->CWeaponM4A1 ||
		id == ClassId->CWeaponMAC10 ||
		id == ClassId->CWeaponMP5Navy ||
		id == ClassId->CWeaponP228 ||
		id == ClassId->CWeaponP90 ||
		id == ClassId->CWeaponScout ||
		id == ClassId->CWeaponSG550 ||
		id == ClassId->CWeaponSG552 ||
		id == ClassId->CWeaponTMP ||
		id == ClassId->CWeaponUMP45 ||
		id == ClassId->CWeaponUSP ||
		id == ClassId->CWeaponXM1014||
		id == ClassId->CDEagle||
		id == ClassId->CBaseCSGrenadeProjectile
		)
		return true;
	return false;
}

int C_BaseEntity::GetCurrentWeaponEntityAddress()
{
	return *(int*)((DWORD)this + NetVarManagement->DT_BaseCombatCharacter.m_hActiveWeapon);
}

uintptr_t C_BaseEntity::GetBoneBaseAddress()
{
	return *(uintptr_t*)((DWORD)this + 0x578);
}

QAngle C_BaseEntity::GetEyeAngles()
{
	return *(QAngle*)(((uintptr_t)this + NetVarManagement->DT_CSPlayer.m_angEyeAngles));
}

int C_BaseEntity::Getm_fFlags()
{
	return *(int*)((uintptr_t)this + 0x350);
}

Vector	C_BaseEntity::GetViewAngle()
{
	return *(Vector*)(((uintptr_t)this + 0x149C));
}