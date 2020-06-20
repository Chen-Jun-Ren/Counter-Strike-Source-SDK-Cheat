#pragma once
#include "include.h"
#include "Tools.h"

extern void doAimBot();

class AimBotData
{
public:
	Vec3 Player3DPos;
	Vec2 Player2DPos;
private:
	
};

struct CalculationDistance
{
public:
	CalculationDistance(void)
	{

	}
	void SetPlayerPos2D(Vec2 Pos) { Player2DPos = Pos; }
	void SetPlayerPos3D(Vec3 Pos) { Player3DPos = Pos; }

	Vec3 GetPlayer3DPos() { return this->Player3DPos; }
	int GetDistance() { return this->Distance; }
	CalculationDistance(Vec2 Pos,Vec3 Pos3D, int winWidth, int winHight)
	{
		SetPlayerPos2D(Pos);
		SetPlayerPos3D(Pos3D);

		//兩點距離計算公式
		Distance = sqrtf(powf(winWidth / 2 - Player2DPos.x, 2) + powf(winHight / 2 - Player2DPos.y, 2));
	}
private:
	Vec3 Player3DPos;
	Vec2 Player2DPos;
	float Distance;
};



