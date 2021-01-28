#include "Hooks.h"
#include "SetupHack.h"
#include <mutex>
#include "Global.h"
#include "EspBox.h"
#include "CreateInterface.h"
#include "CBaseEntity.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx9.h"
#include "ImGui/imgui_impl_win32.h"
#include "Tools.h"
#include <math.h>
#include <cmath>

Vector head3DPos_P;
Vec2 head2DPos_P;

Vec2 Origin2DPos_P;

Vec2 esp3D_box_pos[8];

PaintTraverseFn oPaintTraverse;

void PaintTraverse_EspBox(int R, int G, int B, C_BaseEntity* BaseEntity);
void PaintTraverse_doEspBox()
{
	if (Controller::ESPBOX && Interface)
	{
		C_BaseEntity* LocalPlayer = (C_BaseEntity*)Interface->ClientEntityList->GetClientEntity(Interface->VEngineClient->GetLocalPlayer());
		for (int i = 0; i <= 50; i++)
		{
			if (!Interface) break;
			C_BaseEntity* BaseEntity = (C_BaseEntity*)Interface->ClientEntityList->GetClientEntity(i);
			if (BaseEntity == nullptr || BaseEntity == LocalPlayer || !BaseEntity->GetlifeState() || BaseEntity->isDormant() || BaseEntity->GetvecOrigin().x == 0.000000 || BaseEntity->GetvecOrigin().y == 0.000000 || BaseEntity->GetvecOrigin().z == 0.000000)
				continue;
			if (BaseEntity->IsWeapon() && Controller::ESPBOX_CHECK_WEAPON)
			{

			}
			if (BaseEntity->IsPlayer())
			{
				if (BaseEntity->GetTeamNumber() == LocalPlayer->GetTeamNumber() && Controller::ESPBOX_CHECK_TEAM)
				{
					if (Controller::ESPBOX_CHECK_TEAM)
					{
						PaintTraverse_EspBox(0, 255, 0, BaseEntity);
					}
				}

				if (BaseEntity->GetTeamNumber() != LocalPlayer->GetTeamNumber() && Controller::ESPBOX_CHECK_ENEMY)
				{
					if (Controller::ESPBOX_CHECK_TEAM)
					{
						PaintTraverse_EspBox(255, 0, 0, BaseEntity);
					}
				}
			}
		}
	}
}

float degrees_to_radian(float deg)
{
	return deg * M_PI / 180.0;//C++內有定義常數M_PI=3.14159
}

Vector Rotation(C_BaseEntity* BaseEntity, float x, float y, float z, float angle)
{

	//x' = x * cos(theta) - sin(theta) * y
	//y' = x * sin(theta) + cos(theta) * y
	Vector Rotation;
	float rAngles = BaseEntity->GetViewAngle().y;
	Rotation.x = BaseEntity->GetPos().x + (std::cos(degrees_to_radian(rAngles + angle)) * x - std::sin(degrees_to_radian(rAngles + angle)) * y);
	Rotation.y = BaseEntity->GetPos().y + (std::sin(degrees_to_radian(rAngles + angle)) * x + std::cos(degrees_to_radian(rAngles + angle)) * y);
	Rotation.z = BaseEntity->GetPos().z + z;
	return Rotation;
}

void PaintTraverse_EspBox(int R, int G, int B, C_BaseEntity* BaseEntity)
{
	//float tall = sqrtf(powf(head2DPos_P.x - Origin2DPos_P.x, 2) + powf(head2DPos_P.y - Origin2DPos_P.y, 2));//兩點距離計算公式
	if (BaseEntity->Getm_fFlags() == 0x301 || BaseEntity->Getm_fFlags() == 0x101)
	{
		//2d
		if (!(Tools::WorldToScreen(BaseEntity->GetPos() + Vector(0, 0,70), head2DPos_P) &&
			Tools::WorldToScreen(BaseEntity->GetPos(), Origin2DPos_P)))
			return;

		//3d
		if (!(Tools::WorldToScreen(Rotation(BaseEntity, 20, 20, 0, 0), esp3D_box_pos[0]) &&
			Tools::WorldToScreen(Rotation(BaseEntity, 20, 20, 0, 90), esp3D_box_pos[1]) &&
			Tools::WorldToScreen(Rotation(BaseEntity, 20, 20, 0, 180), esp3D_box_pos[2]) &&
			Tools::WorldToScreen(Rotation(BaseEntity, 20, 20, 0, 270), esp3D_box_pos[3]) &&
			Tools::WorldToScreen(Rotation(BaseEntity, 20, 20, 70, 0), esp3D_box_pos[4]) &&
			Tools::WorldToScreen(Rotation(BaseEntity, 20, 20, 70, 90), esp3D_box_pos[5]) &&
			Tools::WorldToScreen(Rotation(BaseEntity, 20, 20, 70, 180), esp3D_box_pos[6]) &&
			Tools::WorldToScreen(Rotation(BaseEntity, 20, 20, 70, 270), esp3D_box_pos[7])))
			return;
	}
	else
	{
		if (!(Tools::WorldToScreen(BaseEntity->GetPos() + Vector(0, 0, 54), head2DPos_P) &&
			Tools::WorldToScreen(BaseEntity->GetPos(), Origin2DPos_P)))
			return;
			//2d

			//3d
		if (!(Tools::WorldToScreen(Rotation(BaseEntity, 20, 20, 0, 0), esp3D_box_pos[0]) &&
			Tools::WorldToScreen(Rotation(BaseEntity, 20, 20, 0, 90), esp3D_box_pos[1]) &&
			Tools::WorldToScreen(Rotation(BaseEntity, 20, 20, 0, 180), esp3D_box_pos[2]) &&
			Tools::WorldToScreen(Rotation(BaseEntity, 20, 20, 0, 270), esp3D_box_pos[3]) &&
			Tools::WorldToScreen(Rotation(BaseEntity, 20, 20, 54, 0), esp3D_box_pos[4]) &&
			Tools::WorldToScreen(Rotation(BaseEntity, 20, 20, 54, 90), esp3D_box_pos[5]) &&
			Tools::WorldToScreen(Rotation(BaseEntity, 20, 20, 54, 180), esp3D_box_pos[6]) &&
			Tools::WorldToScreen(Rotation(BaseEntity, 20, 20, 54, 270), esp3D_box_pos[7])))
			return;
		//3d

	}

	int width = (Origin2DPos_P.y - head2DPos_P.y) / 2;
	int hight = (Origin2DPos_P.y - head2DPos_P.y);

	switch (Controller::ESPBOXSelectedIndex)
	{
	case 0://2d esp box
		Interface->Surface->DrawSetColor(R, G, B, 25);
		Interface->Surface->DrawFilledRect(head2DPos_P.x - width / 2, head2DPos_P.y, head2DPos_P.x + width / 2, head2DPos_P.y + hight);
		Interface->Surface->DrawSetColor(0, 0, 0, 255);
		Interface->Surface->DrawOutlinedRect(head2DPos_P.x - width / 2, head2DPos_P.y, head2DPos_P.x + width / 2, head2DPos_P.y + hight);

		break;
	case 1://3d esp box
		
		Interface->Surface->DrawSetColor(R, G, B, 255);
		for (int i = 0; i <= 2; i++)
		{
			Interface->Surface->DrawLine(esp3D_box_pos[i].x, esp3D_box_pos[i].y, esp3D_box_pos[i + 1].x, esp3D_box_pos[i + 1].y);
		}

		Interface->Surface->DrawLine(esp3D_box_pos[3].x, esp3D_box_pos[3].y, esp3D_box_pos[0].x, esp3D_box_pos[0].y);

		for (int i = 4; i <= 6; i++)
		{
			Interface->Surface->DrawLine(esp3D_box_pos[i].x, esp3D_box_pos[i].y, esp3D_box_pos[i + 1].x, esp3D_box_pos[i + 1].y);
		}

		Interface->Surface->DrawLine(esp3D_box_pos[7].x, esp3D_box_pos[7].y, esp3D_box_pos[4].x, esp3D_box_pos[4].y);

		for (int i = 0; i <= 3; i++)
		{
			Interface->Surface->DrawLine(esp3D_box_pos[i].x, esp3D_box_pos[i].y, esp3D_box_pos[i + 4].x, esp3D_box_pos[i + 4].y);
		}

		break;
	default:
		break;
	}
}

void __stdcall Hooks::HookPaintTraverse(int VGUIPanel, bool ForceRepaint, bool AllowForce)
{

	oPaintTraverse(Interface->Panel, VGUIPanel, ForceRepaint, AllowForce);
	{ // So we only render on 1 panel.
		static int drawPanel = 0;
		if (!drawPanel)
			if (!strcmp(Interface->Panel->GetName(VGUIPanel), "MatSystemTopPanel"))
				drawPanel = VGUIPanel;
			else
				return;
		if (drawPanel != VGUIPanel)
			return;
	}
	SetupHack::GetViewMatrix();
	SetupHack::SetClassIdManager();
	PaintTraverse_doEspBox();
	delete ClassId;
}