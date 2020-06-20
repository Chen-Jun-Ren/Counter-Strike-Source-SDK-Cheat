#include "TargetLine.h"
#include "Global.h"
#include "CreateInterface.h"
#include "CBaseEntity.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx9.h"
#include "ImGui/imgui_impl_win32.h"
#include "Tools.h"

void SelectedDrawTargetLine(IDirect3DDevice9* pDevice, C_BaseEntity* Entity);

Vec2 Targetpoint;
Vec2 Headpoint;
Vec3 Head3Dpoint;

static int MyWindowWidth;
static int MyWindowHeight;


void TargetLineESP(IDirect3DDevice9* pDevice)
{
	if (Controller::TargetLine && Interface)
	{
		C_BaseEntity* LocalPlayer = (C_BaseEntity*)Interface->ClientEntityList->GetClientEntity(1);

		for (int i = 0; i <= /*Interface->ClientEntityList->GetMaxEntities()*/2048; i++)
		{
			if (!Interface) break;
			C_BaseEntity* BaseEntity = (C_BaseEntity*)Interface->ClientEntityList->GetClientEntity(i);
			if (BaseEntity == nullptr)
				continue;
			if (BaseEntity == Interface->ClientEntityList->GetClientEntity(1))
				continue;
			if (BaseEntity->isDormant() == true)
				continue;
			if (BaseEntity->GetlifeState() == false)
				continue;
			if (BaseEntity->GetvecOrigin().x == 0.000000 && BaseEntity->GetvecOrigin().y == 0.000000 && BaseEntity->GetvecOrigin().z == 0.000000)//在原點座標的Entity捨棄
				continue;
			if (BaseEntity->IsWeapon() == true)//------Weapon------//
			{
				if (Tools::WorldToScreen(BaseEntity->GetPos(), Targetpoint) && Controller::TargetLine_check_Weapon)
				{
					SelectedDrawTargetLine(pDevice,BaseEntity);
					Tools::DrawLine(MyWindowWidth, MyWindowHeight, Targetpoint.x, Targetpoint.y, Controller::TargetLine_Thickness, 0, pDevice, (int)(Controller::TargetLine_color_Weapon.x * 255.0f), (int)(Controller::TargetLine_color_Weapon.y * 255.0f), (int)(Controller::TargetLine_color_Weapon.z * 255.0f));
					//測試代碼
					/*{
						Tools::DrawString(Targetpoint.x + 1, Targetpoint.y - 1, 0, 0, 0, "ID = %d \nPos.x = %f \nPos.y = %f\nPos.z = %f", BaseEntity->GetClientClass()->m_ClassID, BaseEntity->GetvecOrigin().x, BaseEntity->GetvecOrigin().y, BaseEntity->GetvecOrigin().z);
						Tools::DrawString(Targetpoint.x - 1, Targetpoint.y + 1, 0, 0, 0, "ID = %d \nPos.x = %f \nPos.y = %f\nPos.z = %f", BaseEntity->GetClientClass()->m_ClassID, BaseEntity->GetvecOrigin().x, BaseEntity->GetvecOrigin().y, BaseEntity->GetvecOrigin().z);
						Tools::DrawString(Targetpoint.x + 1, Targetpoint.y + 1, 0, 0, 0, "ID = %d \nPos.x = %f \nPos.y = %f\nPos.z = %f", BaseEntity->GetClientClass()->m_ClassID, BaseEntity->GetvecOrigin().x, BaseEntity->GetvecOrigin().y, BaseEntity->GetvecOrigin().z);
						Tools::DrawString(Targetpoint.x - 1, Targetpoint.y - 1, 0, 0, 0, "ID = %d \nPos.x = %f \nPos.y = %f\nPos.z = %f", BaseEntity->GetClientClass()->m_ClassID, BaseEntity->GetvecOrigin().x, BaseEntity->GetvecOrigin().y, BaseEntity->GetvecOrigin().z);
						Tools::DrawString(Targetpoint.x, Targetpoint.y, 255, 0, 255, "ID = %d \nPos.x = %f \nPos.y = %f\nPos.z = %f", BaseEntity->GetClientClass()->m_ClassID, BaseEntity->GetvecOrigin().x, BaseEntity->GetvecOrigin().y, BaseEntity->GetvecOrigin().z);
					}*/
				}
			}
			if (BaseEntity->IsPlayer() == true)//------Players------//
			{
				if (Tools::WorldToScreen(BaseEntity->GetPos(), Targetpoint))
				{
					if (BaseEntity->GetTeamNumber() == LocalPlayer->GetTeamNumber() && Tools::GetBonePosEx(BaseEntity->GetBoneBaseAddress(), 14, Head3Dpoint, Headpoint) && Controller::TargetLine_check_Team)//Team
					{
						SelectedDrawTargetLine(pDevice,BaseEntity);
						Tools::DrawLine(MyWindowWidth, MyWindowHeight, Targetpoint.x, Targetpoint.y, Controller::TargetLine_Thickness, 0, pDevice, (int)(Controller::TargetLine_color_Team.x * 255.0f), (int)(Controller::TargetLine_color_Team.y * 255.0f), (int)(Controller::TargetLine_color_Team.z * 255.0f));
					}
					if (BaseEntity->GetTeamNumber() != LocalPlayer->GetTeamNumber() && Tools::GetBonePosEx(BaseEntity->GetBoneBaseAddress(), 14, Head3Dpoint, Headpoint) && Controller::TargetLine_check_Enemy)//Enemy
					{
						SelectedDrawTargetLine(pDevice,BaseEntity);
						Tools::DrawLine(MyWindowWidth, MyWindowHeight, Targetpoint.x, Targetpoint.y, Controller::TargetLine_Thickness, 0, pDevice, (int)(Controller::TargetLine_color_Enemy.x * 255.0f), (int)(Controller::TargetLine_color_Enemy.y * 255.0f), (int)(Controller::TargetLine_color_Enemy.z * 255.0f));
					}
				}
			}
			if (!Interface) break;
		}
	}
}


void SelectedDrawTargetLine(IDirect3DDevice9* pDevice, C_BaseEntity* Entity)
{
	if (Controller::TargetLineSelectedIndex == 0)
	{
		Tools::DrawLine(win::windowWidth - 1, win::windowHeight - 1, Targetpoint.x - 1, Targetpoint.y - 1, Controller::TargetLine_Thickness, 0, pDevice, 0, 0, 0);
		Tools::DrawLine(win::windowWidth + 1, win::windowHeight + 1, Targetpoint.x + 1, Targetpoint.y + 1, Controller::TargetLine_Thickness, 0, pDevice, 0, 0, 0);
		Tools::DrawLine(win::windowWidth + 1, win::windowHeight - 1, Targetpoint.x + 1, Targetpoint.y - 1, Controller::TargetLine_Thickness, 0, pDevice, 0, 0, 0);
		Tools::DrawLine(win::windowWidth - 1, win::windowHeight + 1, Targetpoint.x - 1, Targetpoint.y + 1, Controller::TargetLine_Thickness, 0, pDevice, 0, 0, 0);
		MyWindowWidth = win::windowWidth;
		MyWindowHeight = win::windowHeight;
	}
	if (Controller::TargetLineSelectedIndex == 1)
	{
		Tools::DrawLine(0 - 1, win::windowHeight - 1, Targetpoint.x - 1, Targetpoint.y - 1, Controller::TargetLine_Thickness, 0, pDevice, 0, 0, 0);
		Tools::DrawLine(0 + 1, win::windowHeight + 1, Targetpoint.x + 1, Targetpoint.y + 1, Controller::TargetLine_Thickness, 0, pDevice, 0, 0, 0);
		Tools::DrawLine(0 + 1, win::windowHeight - 1, Targetpoint.x + 1, Targetpoint.y - 1, Controller::TargetLine_Thickness, 0, pDevice, 0, 0, 0);
		Tools::DrawLine(0 - 1, win::windowHeight + 1, Targetpoint.x - 1, Targetpoint.y + 1, Controller::TargetLine_Thickness, 0, pDevice, 0, 0, 0);
		MyWindowWidth = 0;
		MyWindowHeight = win::windowHeight;
	}
	if (Controller::TargetLineSelectedIndex == 2)
	{
		Tools::DrawLine(win::windowWidth / 2 - 1, win::windowHeight - 1, Targetpoint.x - 1, Targetpoint.y - 1, Controller::TargetLine_Thickness, 0, pDevice, 0, 0, 0);
		Tools::DrawLine(win::windowWidth / 2 + 1, win::windowHeight + 1, Targetpoint.x + 1, Targetpoint.y + 1, Controller::TargetLine_Thickness, 0, pDevice, 0, 0, 0);
		Tools::DrawLine(win::windowWidth / 2 + 1, win::windowHeight - 1, Targetpoint.x + 1, Targetpoint.y - 1, Controller::TargetLine_Thickness, 0, pDevice, 0, 0, 0);
		Tools::DrawLine(win::windowWidth / 2 - 1, win::windowHeight + 1, Targetpoint.x - 1, Targetpoint.y + 1, Controller::TargetLine_Thickness, 0, pDevice, 0, 0, 0);
		MyWindowWidth = win::windowWidth / 2;
		MyWindowHeight = win::windowHeight;
	}
	if (Controller::TargetLineSelectedIndex == 3)
	{
		if (Entity->IsWeapon() == true)
		{
			Tools::DrawLine(win::windowWidth - 1, 0 - 1, Targetpoint.x - 1, Targetpoint.y - 1, Controller::TargetLine_Thickness, 0, pDevice, 0, 0, 0);
			Tools::DrawLine(win::windowWidth + 1, 0 + 1, Targetpoint.x + 1, Targetpoint.y + 1, Controller::TargetLine_Thickness, 0, pDevice, 0, 0, 0);
			Tools::DrawLine(win::windowWidth + 1, 0 - 1, Targetpoint.x + 1, Targetpoint.y - 1, Controller::TargetLine_Thickness, 0, pDevice, 0, 0, 0);
			Tools::DrawLine(win::windowWidth - 1, 0 + 1, Targetpoint.x - 1, Targetpoint.y + 1, Controller::TargetLine_Thickness, 0, pDevice, 0, 0, 0);
			MyWindowWidth = win::windowWidth;
			MyWindowHeight = 0;
		}
		if (Entity->IsWeapon() == false)
		{
			float tall = sqrtf(powf(Headpoint.x - Targetpoint.x, 2) + powf(Headpoint.y - Targetpoint.y, 2));//兩點距離計算公式
			Targetpoint.x = Headpoint.x;
			Targetpoint.y = Headpoint.y - (tall / 5.25);

			Tools::DrawLine(win::windowWidth - 1, 0 - 1, Targetpoint.x - 1, Targetpoint.y - 1, Controller::TargetLine_Thickness, 0, pDevice, 0, 0, 0);
			Tools::DrawLine(win::windowWidth + 1, 0 + 1, Targetpoint.x + 1, Targetpoint.y + 1, Controller::TargetLine_Thickness, 0, pDevice, 0, 0, 0);
			Tools::DrawLine(win::windowWidth + 1, 0 - 1, Targetpoint.x + 1, Targetpoint.y - 1, Controller::TargetLine_Thickness, 0, pDevice, 0, 0, 0);
			Tools::DrawLine(win::windowWidth - 1, 0 + 1, Targetpoint.x - 1, Targetpoint.y + 1, Controller::TargetLine_Thickness, 0, pDevice, 0, 0, 0);
			MyWindowWidth = win::windowWidth;
			MyWindowHeight = 0;
		}
	}
	if (Controller::TargetLineSelectedIndex == 4)
	{
		if (Entity->IsWeapon() == true)
		{
			Tools::DrawLine(0 - 1, 0 - 1, Targetpoint.x - 1, Targetpoint.y - 1, Controller::TargetLine_Thickness, 0, pDevice, 0, 0, 0);
			Tools::DrawLine(0 + 1, 0 + 1, Targetpoint.x + 1, Targetpoint.y + 1, Controller::TargetLine_Thickness, 0, pDevice, 0, 0, 0);
			Tools::DrawLine(0 + 1, 0 - 1, Targetpoint.x + 1, Targetpoint.y - 1, Controller::TargetLine_Thickness, 0, pDevice, 0, 0, 0);
			Tools::DrawLine(0 - 1, 0 + 1, Targetpoint.x - 1, Targetpoint.y + 1, Controller::TargetLine_Thickness, 0, pDevice, 0, 0, 0);
			MyWindowWidth = 0;
			MyWindowHeight = 0;
		}
		if (Entity->IsWeapon() == false)
		{
			float tall = sqrtf(powf(Headpoint.x - Targetpoint.x, 2) + powf(Headpoint.y - Targetpoint.y, 2));//兩點距離計算公式
			Targetpoint.x = Headpoint.x;
			Targetpoint.y = Headpoint.y - (tall / 5.25);

			Tools::DrawLine(0 - 1, 0 - 1, Targetpoint.x - 1, Targetpoint.y - 1, Controller::TargetLine_Thickness, 0, pDevice, 0, 0, 0);
			Tools::DrawLine(0 + 1, 0 + 1, Targetpoint.x + 1, Targetpoint.y + 1, Controller::TargetLine_Thickness, 0, pDevice, 0, 0, 0);
			Tools::DrawLine(0 + 1, 0 - 1, Targetpoint.x + 1, Targetpoint.y - 1, Controller::TargetLine_Thickness, 0, pDevice, 0, 0, 0);
			Tools::DrawLine(0 - 1, 0 + 1, Targetpoint.x - 1, Targetpoint.y + 1, Controller::TargetLine_Thickness, 0, pDevice, 0, 0, 0);
			MyWindowWidth = 0;
			MyWindowHeight = 0;
		}
	}
	if (Controller::TargetLineSelectedIndex == 5)
	{
		if (Entity->IsWeapon() == true)
		{
			Tools::DrawLine(win::windowWidth / 2 - 1, 0 - 1, Targetpoint.x - 1, Targetpoint.y - 1, Controller::TargetLine_Thickness, 0, pDevice, 0, 0, 0);
			Tools::DrawLine(win::windowWidth / 2 + 1, 0 + 1, Targetpoint.x + 1, Targetpoint.y + 1, Controller::TargetLine_Thickness, 0, pDevice, 0, 0, 0);
			Tools::DrawLine(win::windowWidth / 2 + 1, 0 - 1, Targetpoint.x + 1, Targetpoint.y - 1, Controller::TargetLine_Thickness, 0, pDevice, 0, 0, 0);
			Tools::DrawLine(win::windowWidth / 2 - 1, 0 + 1, Targetpoint.x - 1, Targetpoint.y + 1, Controller::TargetLine_Thickness, 0, pDevice, 0, 0, 0);
			MyWindowWidth = win::windowWidth / 2;
			MyWindowHeight = 0;
		}
		if (Entity->IsWeapon() == false)
		{
			float tall = sqrtf(powf(Headpoint.x - Targetpoint.x, 2) + powf(Headpoint.y - Targetpoint.y, 2));//兩點距離計算公式
			Targetpoint.x = Headpoint.x;
			Targetpoint.y = Headpoint.y - (tall / 5.25);

			Tools::DrawLine(win::windowWidth / 2 - 1, 0 - 1, Targetpoint.x - 1, Targetpoint.y - 1, Controller::TargetLine_Thickness, 0, pDevice, 0, 0, 0);
			Tools::DrawLine(win::windowWidth / 2 + 1, 0 + 1, Targetpoint.x + 1, Targetpoint.y + 1, Controller::TargetLine_Thickness, 0, pDevice, 0, 0, 0);
			Tools::DrawLine(win::windowWidth / 2 + 1, 0 - 1, Targetpoint.x + 1, Targetpoint.y - 1, Controller::TargetLine_Thickness, 0, pDevice, 0, 0, 0);
			Tools::DrawLine(win::windowWidth / 2 - 1, 0 + 1, Targetpoint.x - 1, Targetpoint.y + 1, Controller::TargetLine_Thickness, 0, pDevice, 0, 0, 0);
			MyWindowWidth = win::windowWidth / 2;
			MyWindowHeight = 0;
		}
	}
}