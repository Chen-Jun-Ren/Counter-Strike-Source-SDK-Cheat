#pragma once
#include "NetVarManagement.h"
#include "ClassIdManager.h"
#include "iclientnetworkable.h"
#include "IClientUnknown.h"
#include "IClientRenderable.h"
#include "IClientThinkable.h"
#include "Vector.h"
#include "Global.h"
class IClientEntity : public IClientUnknown, public IClientRenderable, public IClientNetworkable, public IClientThinkable
{
public:
	virtual void			Release(void) = 0;
	virtual const Vector& GetAbsOrigin(void) const = 0;
	virtual const QAngle& GetAbsAngles(void) const = 0;
	/*virtual void			IClientEntity_Whatever_fun_0() = 0;
	virtual void			IClientEntity_Whatever_fun_1() = 0;*/
};

class C_BaseEntity : public IClientEntity
{
public:
	uintptr_t* GetThisptr();
	int GetHealthValue();
	int GetTeamNumber();
	int GetArmorValue();
	bool GetlifeState();
	bool isDormant();
	Vector GetvecOrigin();
	Vector	GetViewAngle();
	Vector GetPos();
	bool IsPlayer();
	bool IsPlayer_Aim();
	bool IsWeapon();
	int GetCurrentWeaponEntityAddress();
	uintptr_t GetBoneBaseAddress();
	QAngle GetEyeAngles();
	int Getm_fFlags();
};
