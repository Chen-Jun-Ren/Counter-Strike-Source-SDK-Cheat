#include "AimBot.h"
#include <math.h>
#include "CBaseEntity.h"
#include "Tools.h"
#include "Global.h"
#include "SetupHack.h"
#include <algorithm>

AimBotData AimData[50];

int TargetLoop = 0;

const DWORD YAW = 0x4791B8;
const DWORD PITCH = 0x4791B4;

void CalculatorAimAngle(Vector* MyPos, Vec3* EntityPos);

struct CompareTargetDistanceArray
{
	//重載函數 從小到大排序物件順序
	bool operator() (CalculationDistance& lhs, CalculationDistance& rhs)
	{
		return (lhs.GetDistance() < rhs.GetDistance());
	}
};

void doAimBot()
{
	if (Controller::AimBot && GetAsyncKeyState(ALT_KEY) && true && Interface)
	{
		/*SetupHack::SetAimClassIdManager();*///特殊必須寫在函數裡,使用完之後立即釋放.

		CalculationDistance* AimDistance = new CalculationDistance[50];
		C_BaseEntity* LocalPlayer = (C_BaseEntity*)Interface->ClientEntityList->GetClientEntity(1);
		for (int i = 0; i <= 49; i++)
		{
			C_BaseEntity* BaseEntity = (C_BaseEntity*)Interface->ClientEntityList->GetClientEntity(i);
			if (BaseEntity == nullptr || BaseEntity == LocalPlayer || !BaseEntity->GetlifeState() || BaseEntity->isDormant() || BaseEntity->GetvecOrigin().x == 0.000000 || BaseEntity->GetvecOrigin().y == 0.000000 || BaseEntity->GetvecOrigin().z == 0.000000)
				continue;
			if (/*BaseEntity->IsPlayer_Aim()*/BaseEntity->IsPlayer())
			{
				if (BaseEntity->GetTeamNumber() == LocalPlayer->GetTeamNumber())
					continue;
				if (Tools::GetBonePosEx(BaseEntity->GetBoneBaseAddress(), 14, AimData[i].Player3DPos, AimData[i].Player2DPos))
				{
					if (Controller::AimBotCircle < sqrtf(powf(win::windowWidth / 2 - AimData[i].Player2DPos.x, 2) + powf(win::windowHeight / 2 - AimData[i].Player2DPos.y, 2)))
						continue;
					AimDistance[TargetLoop] = CalculationDistance(AimData[i].Player2DPos, AimData[i].Player3DPos, win::windowWidth, win::windowHeight);
					TargetLoop++;
				}
			}
			if (!Interface) break;
		}
		if (TargetLoop > 0)
		{
			std::sort(AimDistance, AimDistance + TargetLoop, CompareTargetDistanceArray());
			CalculatorAimAngle(&LocalPlayer->GetPos(), &AimDistance->GetPlayer3DPos());
		}

		TargetLoop = 0;
		delete[] AimDistance;
		/*delete AimClassId;*///釋放
	}
}


void CalculatorAimAngle(Vector* MyPos, Vec3* EntityPos)
{
	EntityPos->z -= 62;//扣掉誤差
	float Hypotenuse = sqrtf(pow(MyPos->x - EntityPos->x, 2) + powf(MyPos->y - EntityPos->y, 2) + powf(MyPos->z - EntityPos->z, 2));
	float setYAW = atanf((EntityPos->y - MyPos->y) / (EntityPos->x - MyPos->x)) * 57.295779513082f;
	float setPITCH = asinf((MyPos->z - EntityPos->z) / Hypotenuse) * 57.295779513082f;
	if (MyPos->x - EntityPos->x >= 0.0f)//X大於0 + 180
	{
		setYAW += 180.0f;
	}
	*(float*)(ModuleHandle::__dwordEngine + YAW) = setYAW;
	*(float*)(ModuleHandle::__dwordEngine + PITCH) = setPITCH;
}

//				90
//				Y
//				=				X : ( - 8 - 8 ) = -16
//				=				Y : ( 3 - ( -3 ) ) = 6
//				=
//		.(-8,3)	=				atan( 6 / -16 ) = - 20.5度
//				=
//	 180		=			 0
//	========================= X	
//	-180		=
//				=
//				=		.(8,-3)
//				=
//				=
//				=
//			   -90