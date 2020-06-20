#include "Espinformation.h"
#include "Global.h"
#include "CreateInterface.h"
#include "CBaseEntity.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx9.h"
#include "ImGui/imgui_impl_win32.h"
#include "Tools.h"
#include <math.h>

void DrawNawe(Vec2 projectTOscreen, ImVec4 Setcolor);
void DrawHealth(Vec2 projectTOscreen, ImVec4 Setcolor, C_BaseEntity* BaseEntity);
void DrawDistance(Vec2 projectTOscreen, ImVec4 Setcolor, C_BaseEntity* BaseEntity, C_BaseEntity* LocalPlayer);
void DrawTeam(C_BaseEntity* BaseEntity, C_BaseEntity* LocalPlayer, int tall, ImVec4 Setcolor);
void DrawWeaponsName(C_BaseEntity* BaseEntity);

Vec3 Headpoint3D;
Vec2 Headpoint2D;


void doInformation(IDirect3DDevice9* pDevice)
{
	if (Controller::EspPlayerInfo && Interface)
	{
		C_BaseEntity* LocalPlayer = (C_BaseEntity*)Interface->ClientEntityList->GetClientEntity(1);
		for (int i = 0; i <= /*Interface->ClientEntityList->GetMaxEntities()*/2048; i++)
		{
			if (!Interface) break;
			C_BaseEntity* BaseEntity = (C_BaseEntity*)Interface->ClientEntityList->GetClientEntity(i);
			if (BaseEntity == nullptr || BaseEntity == LocalPlayer || !BaseEntity->GetlifeState() || BaseEntity->isDormant() || BaseEntity->GetvecOrigin().x == 0.000000 || BaseEntity->GetvecOrigin().y == 0.000000 || BaseEntity->GetvecOrigin().z == 0.000000)
				continue;
			if (BaseEntity->IsWeapon())
			{
				if (Tools::WorldToScreen(BaseEntity->GetPos(), Headpoint2D))
				{
					DrawWeaponsName(BaseEntity);
				}
			}
			if (BaseEntity->IsPlayer())
			{
				if (BaseEntity->GetTeamNumber() == LocalPlayer->GetTeamNumber())
				{
					Vec2 projectTOscreen;
					Interface->VEngineClient->GetPlayerInfo(i, &Controller::info);
					if (Tools::WorldToScreen(BaseEntity->GetvecOrigin(), projectTOscreen) && Tools::GetBonePosEx(BaseEntity->GetBoneBaseAddress(), 14, Headpoint3D, Headpoint2D))
					{
						float tall = sqrtf(powf(Headpoint2D.x - projectTOscreen.x, 2) + powf(Headpoint2D.y - projectTOscreen.y, 2));//兩點距離計算公式
						DrawNawe(projectTOscreen,Controller::info_color_Team);
						DrawHealth(projectTOscreen, Controller::info_color_Team, BaseEntity);
						DrawDistance(projectTOscreen, Controller::info_color_Team, BaseEntity, LocalPlayer);
						DrawTeam(BaseEntity, LocalPlayer, tall, Controller::info_color_Team);
					}
				}
				if (BaseEntity->GetTeamNumber() != LocalPlayer->GetTeamNumber())
				{
					Vec2 projectTOscreen;
					Interface->VEngineClient->GetPlayerInfo(i, &Controller::info);
					if (Tools::WorldToScreen(BaseEntity->GetvecOrigin(), projectTOscreen) && Tools::GetBonePosEx(BaseEntity->GetBoneBaseAddress(), 14, Headpoint3D, Headpoint2D))
					{
						float tall = sqrtf(powf(Headpoint2D.x - projectTOscreen.x, 2) + powf(Headpoint2D.y - projectTOscreen.y, 2));//兩點距離計算公式
						DrawNawe(projectTOscreen, Controller::info_color_Enemy);
						DrawHealth(projectTOscreen, Controller::info_color_Enemy, BaseEntity);
						DrawDistance(projectTOscreen, Controller::info_color_Enemy, BaseEntity, LocalPlayer);
						DrawTeam(BaseEntity, LocalPlayer, tall, Controller::info_color_Enemy);
					}
				}
			}
			if (!Interface) break;
		}
	}
}

void DrawNawe(Vec2 projectTOscreen,ImVec4 Setcolor)
{
	if (Controller::info_Shadow)
	{
		Tools::DrawString(projectTOscreen.x + 1 - 20, projectTOscreen.y + 1, 0, 0, 0, "名稱:%c%c%c%c%c%c%c%c%c%c", *Controller::info.name, *(Controller::info.name + 1), *(Controller::info.name + 2), *(Controller::info.name + 3), *(Controller::info.name + 4), *(Controller::info.name + 5), *(Controller::info.name + 6), *(Controller::info.name + 7), *(Controller::info.name + 8), *(Controller::info.name + 9));
		Tools::DrawString(projectTOscreen.x - 1 - 20, projectTOscreen.y - 1, 0, 0, 0, "名稱:%c%c%c%c%c%c%c%c%c%c", *Controller::info.name, *(Controller::info.name + 1), *(Controller::info.name + 2), *(Controller::info.name + 3), *(Controller::info.name + 4), *(Controller::info.name + 5), *(Controller::info.name + 6), *(Controller::info.name + 7), *(Controller::info.name + 8), *(Controller::info.name + 9));
		Tools::DrawString(projectTOscreen.x + 1 - 20, projectTOscreen.y - 1, 0, 0, 0, "名稱:%c%c%c%c%c%c%c%c%c%c", *Controller::info.name, *(Controller::info.name + 1), *(Controller::info.name + 2), *(Controller::info.name + 3), *(Controller::info.name + 4), *(Controller::info.name + 5), *(Controller::info.name + 6), *(Controller::info.name + 7), *(Controller::info.name + 8), *(Controller::info.name + 9));
		Tools::DrawString(projectTOscreen.x - 1 - 20, projectTOscreen.y + 1, 0, 0, 0, "名稱:%c%c%c%c%c%c%c%c%c%c", *Controller::info.name, *(Controller::info.name + 1), *(Controller::info.name + 2), *(Controller::info.name + 3), *(Controller::info.name + 4), *(Controller::info.name + 5), *(Controller::info.name + 6), *(Controller::info.name + 7), *(Controller::info.name + 8), *(Controller::info.name + 9));
	}
	//Tools::DrawString(projectTOscreen.x - 20, projectTOscreen.y, (int)(Setcolor.x * 255), (int)(Setcolor.y * 255), (int)(Setcolor.z * 255), "名稱:%c%c%c%c%c%c%c%c%c%c", *Controller::info.name, *(Controller::info.name + 1), *(Controller::info.name + 2), *(Controller::info.name + 3), *(Controller::info.name + 4), *(Controller::info.name + 5), *(Controller::info.name + 6), *(Controller::info.name + 7), *(Controller::info.name + 8), *(Controller::info.name + 9));
	Tools::DrawString(projectTOscreen.x - 20, projectTOscreen.y, (int)(Setcolor.x * 255), (int)(Setcolor.y * 255), (int)(Setcolor.z * 255), "名稱:%s", Controller::info.name);
}

void DrawHealth(Vec2 projectTOscreen, ImVec4 Setcolor, C_BaseEntity* BaseEntity)
{
	if (Controller::info_Shadow)
	{
		Tools::DrawString(projectTOscreen.x + 1 - 20, projectTOscreen.y + 1 + 15, 0, 0, 0, "血量:%d", BaseEntity->GetHealthValue());
		Tools::DrawString(projectTOscreen.x - 1 - 20, projectTOscreen.y - 1 + 15, 0, 0, 0, "血量:%d", BaseEntity->GetHealthValue());
		Tools::DrawString(projectTOscreen.x + 1 - 20, projectTOscreen.y - 1 + 15, 0, 0, 0, "血量:%d", BaseEntity->GetHealthValue());
		Tools::DrawString(projectTOscreen.x - 1 - 20, projectTOscreen.y + 1 + 15, 0, 0, 0, "血量:%d", BaseEntity->GetHealthValue());
	}
	Tools::DrawString(projectTOscreen.x - 20, projectTOscreen.y + 15, (int)(Setcolor.x * 255), (int)(Setcolor.y * 255), (int)(Setcolor.z * 255), "血量:%d", BaseEntity->GetHealthValue());
}

void DrawDistance(Vec2 projectTOscreen, ImVec4 Setcolor, C_BaseEntity* BaseEntity, C_BaseEntity* LocalPlayer)
{
	int distance = sqrtf(powf(BaseEntity->GetvecOrigin().x - LocalPlayer->GetvecOrigin().x, 2) + powf(BaseEntity->GetvecOrigin().y - LocalPlayer->GetvecOrigin().y, 2) + powf(BaseEntity->GetvecOrigin().z - LocalPlayer->GetvecOrigin().z, 2));
	distance = distance / 10;
	if (Controller::info_Shadow)
	{
		Tools::DrawString(projectTOscreen.x + 1 - 20, projectTOscreen.y + 1 + 30, 0, 0, 0, "距離:%d", distance);
		Tools::DrawString(projectTOscreen.x - 1 - 20, projectTOscreen.y - 1 + 30, 0, 0, 0, "距離:%d", distance);
		Tools::DrawString(projectTOscreen.x + 1 - 20, projectTOscreen.y - 1 + 30, 0, 0, 0, "距離:%d", distance);
		Tools::DrawString(projectTOscreen.x - 1 - 20, projectTOscreen.y + 1 + 30, 0, 0, 0, "距離:%d", distance);
	}
	Tools::DrawString(projectTOscreen.x - 20, projectTOscreen.y + 30, (int)(Setcolor.x * 255), (int)(Setcolor.y * 255), (int)(Setcolor.z * 255), "距離:%d", distance);
}

void DrawTeam(C_BaseEntity* BaseEntity, C_BaseEntity* LocalPlayer, int tall, ImVec4 Setcolor)
{
	Headpoint2D.y = Headpoint2D.y - tall / 5.25;
	if (Controller::info_Shadow)
	{
		Tools::DrawString(Headpoint2D.x + 1, Headpoint2D.y + 1 - 20, 0, 0, 0, (BaseEntity->GetTeamNumber() == LocalPlayer->GetTeamNumber()) ? "隊友" : "敵人");
		Tools::DrawString(Headpoint2D.x - 1, Headpoint2D.y - 1 - 20, 0, 0, 0, (BaseEntity->GetTeamNumber() == LocalPlayer->GetTeamNumber()) ? "隊友" : "敵人");
		Tools::DrawString(Headpoint2D.x + 1, Headpoint2D.y - 1 - 20, 0, 0, 0, (BaseEntity->GetTeamNumber() == LocalPlayer->GetTeamNumber()) ? "隊友" : "敵人");
		Tools::DrawString(Headpoint2D.x - 1, Headpoint2D.y + 1 - 20, 0, 0, 0, (BaseEntity->GetTeamNumber() == LocalPlayer->GetTeamNumber()) ? "隊友" : "敵人");
	}
	Tools::DrawString(Headpoint2D.x, Headpoint2D.y - 20, (int)(Setcolor.x * 255), (int)(Setcolor.y * 255), (int)(Setcolor.z * 255), (BaseEntity->GetTeamNumber() == LocalPlayer->GetTeamNumber()) ? "隊友" : "敵人");
}

void DrawWeaponsName(C_BaseEntity* BaseEntity)
{
	if (BaseEntity->GetClientClass()->m_ClassID == ClassId->CBaseCombatWeapon)
	{
		Tools::DrawString(Headpoint2D.x + 1, Headpoint2D.y + 1, 0, 0, 0, "BaseCombatWeapon");
		Tools::DrawString(Headpoint2D.x - 1, Headpoint2D.y - 1, 0, 0, 0, "BaseCombatWeapon");
		Tools::DrawString(Headpoint2D.x + 1, Headpoint2D.y - 1, 0, 0, 0, "BaseCombatWeapon");
		Tools::DrawString(Headpoint2D.x - 1, Headpoint2D.y + 1, 0, 0, 0, "BaseCombatWeapon");
		Tools::DrawString(Headpoint2D.x, Headpoint2D.y, 255, 255, 255, "BaseCombatWeapon");
	}
	if (BaseEntity->GetClientClass()->m_ClassID == ClassId->CAK47)
	{
		Tools::DrawString(Headpoint2D.x + 1, Headpoint2D.y + 1, 0, 0, 0, "AK47");
		Tools::DrawString(Headpoint2D.x - 1, Headpoint2D.y - 1, 0, 0, 0, "AK47");
		Tools::DrawString(Headpoint2D.x + 1, Headpoint2D.y - 1, 0, 0, 0, "AK47");
		Tools::DrawString(Headpoint2D.x - 1, Headpoint2D.y + 1, 0, 0, 0, "AK47");
		Tools::DrawString(Headpoint2D.x, Headpoint2D.y, 255, 255, 255, "AK47");
	}
	if (BaseEntity->GetClientClass()->m_ClassID == ClassId->CWeaponAug)
	{
		Tools::DrawString(Headpoint2D.x + 1, Headpoint2D.y + 1, 0, 0, 0, "Aug");
		Tools::DrawString(Headpoint2D.x - 1, Headpoint2D.y - 1, 0, 0, 0, "Aug");
		Tools::DrawString(Headpoint2D.x + 1, Headpoint2D.y - 1, 0, 0, 0, "Aug");
		Tools::DrawString(Headpoint2D.x - 1, Headpoint2D.y + 1, 0, 0, 0, "Aug");
		Tools::DrawString(Headpoint2D.x, Headpoint2D.y, 255, 255, 255, "Aug");
	}
	if (BaseEntity->GetClientClass()->m_ClassID == ClassId->CWeaponAWP)
	{
		Tools::DrawString(Headpoint2D.x + 1, Headpoint2D.y + 1, 0, 0, 0, "AWP");
		Tools::DrawString(Headpoint2D.x - 1, Headpoint2D.y - 1, 0, 0, 0, "AWP");
		Tools::DrawString(Headpoint2D.x + 1, Headpoint2D.y - 1, 0, 0, 0, "AWP");
		Tools::DrawString(Headpoint2D.x - 1, Headpoint2D.y + 1, 0, 0, 0, "AWP");
		Tools::DrawString(Headpoint2D.x, Headpoint2D.y, 255, 255, 255, "AWP");
	}
	if (BaseEntity->GetClientClass()->m_ClassID == ClassId->CWeaponCSBase)
	{
		Tools::DrawString(Headpoint2D.x + 1, Headpoint2D.y + 1, 0, 0, 0, "CSBase");
		Tools::DrawString(Headpoint2D.x - 1, Headpoint2D.y - 1, 0, 0, 0, "CSBase");
		Tools::DrawString(Headpoint2D.x + 1, Headpoint2D.y - 1, 0, 0, 0, "CSBase");
		Tools::DrawString(Headpoint2D.x - 1, Headpoint2D.y + 1, 0, 0, 0, "CSBase");
		Tools::DrawString(Headpoint2D.x, Headpoint2D.y, 255, 255, 255, "CSBase");
	}
	if (BaseEntity->GetClientClass()->m_ClassID == ClassId->CWeaponCSBaseGun)
	{
		Tools::DrawString(Headpoint2D.x + 1, Headpoint2D.y + 1, 0, 0, 0, "CSBaseGun");
		Tools::DrawString(Headpoint2D.x - 1, Headpoint2D.y - 1, 0, 0, 0, "CSBaseGun");
		Tools::DrawString(Headpoint2D.x + 1, Headpoint2D.y - 1, 0, 0, 0, "CSBaseGun");
		Tools::DrawString(Headpoint2D.x - 1, Headpoint2D.y + 1, 0, 0, 0, "CSBaseGun");
		Tools::DrawString(Headpoint2D.x, Headpoint2D.y, 255, 255, 255, "CSBaseGun");
	}
	if (BaseEntity->GetClientClass()->m_ClassID == ClassId->CWeaponElite)
	{
		Tools::DrawString(Headpoint2D.x + 1, Headpoint2D.y + 1, 0, 0, 0, "Elite");
		Tools::DrawString(Headpoint2D.x - 1, Headpoint2D.y - 1, 0, 0, 0, "Elite");
		Tools::DrawString(Headpoint2D.x + 1, Headpoint2D.y - 1, 0, 0, 0, "Elite");
		Tools::DrawString(Headpoint2D.x - 1, Headpoint2D.y + 1, 0, 0, 0, "Elite");
		Tools::DrawString(Headpoint2D.x, Headpoint2D.y, 255, 255, 255, "Elite");
	}
	if (BaseEntity->GetClientClass()->m_ClassID == ClassId->CWeaponFamas)
	{
		Tools::DrawString(Headpoint2D.x + 1, Headpoint2D.y + 1, 0, 0, 0, "Famas");
		Tools::DrawString(Headpoint2D.x - 1, Headpoint2D.y - 1, 0, 0, 0, "Famas");
		Tools::DrawString(Headpoint2D.x + 1, Headpoint2D.y - 1, 0, 0, 0, "Famas");
		Tools::DrawString(Headpoint2D.x - 1, Headpoint2D.y + 1, 0, 0, 0, "Famas");
		Tools::DrawString(Headpoint2D.x, Headpoint2D.y, 255, 255, 255, "Famas");
	}
	if (BaseEntity->GetClientClass()->m_ClassID == ClassId->CWeaponFiveSeven)
	{
		Tools::DrawString(Headpoint2D.x + 1, Headpoint2D.y + 1, 0, 0, 0, "FiveSeven");
		Tools::DrawString(Headpoint2D.x - 1, Headpoint2D.y - 1, 0, 0, 0, "FiveSeven");
		Tools::DrawString(Headpoint2D.x + 1, Headpoint2D.y - 1, 0, 0, 0, "FiveSeven");
		Tools::DrawString(Headpoint2D.x - 1, Headpoint2D.y + 1, 0, 0, 0, "FiveSeven");
		Tools::DrawString(Headpoint2D.x, Headpoint2D.y, 255, 255, 255, "FiveSeven");
	}
	if (BaseEntity->GetClientClass()->m_ClassID == ClassId->CWeaponG3SG1)
	{
		Tools::DrawString(Headpoint2D.x + 1, Headpoint2D.y + 1, 0, 0, 0, "G3SG1");
		Tools::DrawString(Headpoint2D.x - 1, Headpoint2D.y - 1, 0, 0, 0, "G3SG1");
		Tools::DrawString(Headpoint2D.x + 1, Headpoint2D.y - 1, 0, 0, 0, "G3SG1");
		Tools::DrawString(Headpoint2D.x - 1, Headpoint2D.y + 1, 0, 0, 0, "G3SG1");
		Tools::DrawString(Headpoint2D.x, Headpoint2D.y, 255, 255, 255, "G3SG1");
	}
	if (BaseEntity->GetClientClass()->m_ClassID == ClassId->CWeaponGalil)
	{
		Tools::DrawString(Headpoint2D.x + 1, Headpoint2D.y + 1, 0, 0, 0, "Galil");
		Tools::DrawString(Headpoint2D.x - 1, Headpoint2D.y - 1, 0, 0, 0, "Galil");
		Tools::DrawString(Headpoint2D.x + 1, Headpoint2D.y - 1, 0, 0, 0, "Galil");
		Tools::DrawString(Headpoint2D.x - 1, Headpoint2D.y + 1, 0, 0, 0, "Galil");
		Tools::DrawString(Headpoint2D.x, Headpoint2D.y, 255, 255, 255, "Galil");
	}
	if (BaseEntity->GetClientClass()->m_ClassID == ClassId->CWeaponGlock)
	{
		Tools::DrawString(Headpoint2D.x + 1, Headpoint2D.y + 1, 0, 0, 0, "Glock");
		Tools::DrawString(Headpoint2D.x - 1, Headpoint2D.y - 1, 0, 0, 0, "Glock");
		Tools::DrawString(Headpoint2D.x + 1, Headpoint2D.y - 1, 0, 0, 0, "Glock");
		Tools::DrawString(Headpoint2D.x - 1, Headpoint2D.y + 1, 0, 0, 0, "Glock");
		Tools::DrawString(Headpoint2D.x, Headpoint2D.y, 255, 255, 255, "Glock");
	}
	if (BaseEntity->GetClientClass()->m_ClassID == ClassId->CWeaponM249)
	{
		Tools::DrawString(Headpoint2D.x + 1, Headpoint2D.y + 1, 0, 0, 0, "M249");
		Tools::DrawString(Headpoint2D.x - 1, Headpoint2D.y - 1, 0, 0, 0, "M249");
		Tools::DrawString(Headpoint2D.x + 1, Headpoint2D.y - 1, 0, 0, 0, "M249");
		Tools::DrawString(Headpoint2D.x - 1, Headpoint2D.y + 1, 0, 0, 0, "M249");
		Tools::DrawString(Headpoint2D.x, Headpoint2D.y, 255, 255, 255, "M249");
	}
	if (BaseEntity->GetClientClass()->m_ClassID == ClassId->CWeaponM3)
	{
		Tools::DrawString(Headpoint2D.x + 1, Headpoint2D.y + 1, 0, 0, 0, "M3");
		Tools::DrawString(Headpoint2D.x - 1, Headpoint2D.y - 1, 0, 0, 0, "M3");
		Tools::DrawString(Headpoint2D.x + 1, Headpoint2D.y - 1, 0, 0, 0, "M3");
		Tools::DrawString(Headpoint2D.x - 1, Headpoint2D.y + 1, 0, 0, 0, "M3");
		Tools::DrawString(Headpoint2D.x, Headpoint2D.y, 255, 255, 255, "M3");
	}
	if (BaseEntity->GetClientClass()->m_ClassID == ClassId->CWeaponM4A1)
	{
		Tools::DrawString(Headpoint2D.x + 1, Headpoint2D.y + 1, 0, 0, 0, "M4A1");
		Tools::DrawString(Headpoint2D.x - 1, Headpoint2D.y - 1, 0, 0, 0, "M4A1");
		Tools::DrawString(Headpoint2D.x + 1, Headpoint2D.y - 1, 0, 0, 0, "M4A1");
		Tools::DrawString(Headpoint2D.x - 1, Headpoint2D.y + 1, 0, 0, 0, "M4A1");
		Tools::DrawString(Headpoint2D.x, Headpoint2D.y, 255, 255, 255, "M4A1");
	}
	if (BaseEntity->GetClientClass()->m_ClassID == ClassId->CWeaponMAC10)
	{
		Tools::DrawString(Headpoint2D.x + 1, Headpoint2D.y + 1, 0, 0, 0, "MAC10");
		Tools::DrawString(Headpoint2D.x - 1, Headpoint2D.y - 1, 0, 0, 0, "MAC10");
		Tools::DrawString(Headpoint2D.x + 1, Headpoint2D.y - 1, 0, 0, 0, "MAC10");
		Tools::DrawString(Headpoint2D.x - 1, Headpoint2D.y + 1, 0, 0, 0, "MAC10");
		Tools::DrawString(Headpoint2D.x, Headpoint2D.y, 255, 255, 255, "MAC10");
	}
	if (BaseEntity->GetClientClass()->m_ClassID == ClassId->CWeaponMP5Navy)
	{
		Tools::DrawString(Headpoint2D.x + 1, Headpoint2D.y + 1, 0, 0, 0, "MP5Navy");
		Tools::DrawString(Headpoint2D.x - 1, Headpoint2D.y - 1, 0, 0, 0, "MP5Navy");
		Tools::DrawString(Headpoint2D.x + 1, Headpoint2D.y - 1, 0, 0, 0, "MP5Navy");
		Tools::DrawString(Headpoint2D.x - 1, Headpoint2D.y + 1, 0, 0, 0, "MP5Navy");
		Tools::DrawString(Headpoint2D.x, Headpoint2D.y, 255, 255, 255, "MP5Navy");
	}
	if (BaseEntity->GetClientClass()->m_ClassID == ClassId->CWeaponP228)
	{
		Tools::DrawString(Headpoint2D.x + 1, Headpoint2D.y + 1, 0, 0, 0, "P228");
		Tools::DrawString(Headpoint2D.x - 1, Headpoint2D.y - 1, 0, 0, 0, "P228");
		Tools::DrawString(Headpoint2D.x + 1, Headpoint2D.y - 1, 0, 0, 0, "P228");
		Tools::DrawString(Headpoint2D.x - 1, Headpoint2D.y + 1, 0, 0, 0, "P228");
		Tools::DrawString(Headpoint2D.x, Headpoint2D.y, 255, 255, 255, "P228");
	}
	if (BaseEntity->GetClientClass()->m_ClassID == ClassId->CWeaponP90)
	{
		Tools::DrawString(Headpoint2D.x + 1, Headpoint2D.y + 1, 0, 0, 0, "P90");
		Tools::DrawString(Headpoint2D.x - 1, Headpoint2D.y - 1, 0, 0, 0, "P90");
		Tools::DrawString(Headpoint2D.x + 1, Headpoint2D.y - 1, 0, 0, 0, "P90");
		Tools::DrawString(Headpoint2D.x - 1, Headpoint2D.y + 1, 0, 0, 0, "P90");
		Tools::DrawString(Headpoint2D.x, Headpoint2D.y, 255, 255, 255, "P90");
	}
	if (BaseEntity->GetClientClass()->m_ClassID == ClassId->CWeaponScout)
	{
		Tools::DrawString(Headpoint2D.x + 1, Headpoint2D.y + 1, 0, 0, 0, "Scout");
		Tools::DrawString(Headpoint2D.x - 1, Headpoint2D.y - 1, 0, 0, 0, "Scout");
		Tools::DrawString(Headpoint2D.x + 1, Headpoint2D.y - 1, 0, 0, 0, "Scout");
		Tools::DrawString(Headpoint2D.x - 1, Headpoint2D.y + 1, 0, 0, 0, "Scout");
		Tools::DrawString(Headpoint2D.x, Headpoint2D.y, 255, 255, 255, "Scout");
	}
	if (BaseEntity->GetClientClass()->m_ClassID == ClassId->CWeaponSG550)
	{
		Tools::DrawString(Headpoint2D.x + 1, Headpoint2D.y + 1, 0, 0, 0, "SG550");
		Tools::DrawString(Headpoint2D.x - 1, Headpoint2D.y - 1, 0, 0, 0, "SG550");
		Tools::DrawString(Headpoint2D.x + 1, Headpoint2D.y - 1, 0, 0, 0, "SG550");
		Tools::DrawString(Headpoint2D.x - 1, Headpoint2D.y + 1, 0, 0, 0, "SG550");
		Tools::DrawString(Headpoint2D.x, Headpoint2D.y, 255, 255, 255, "SG550");
	}
	if (BaseEntity->GetClientClass()->m_ClassID == ClassId->CWeaponSG552)
	{
		Tools::DrawString(Headpoint2D.x + 1, Headpoint2D.y + 1, 0, 0, 0, "SG552");
		Tools::DrawString(Headpoint2D.x - 1, Headpoint2D.y - 1, 0, 0, 0, "SG552");
		Tools::DrawString(Headpoint2D.x + 1, Headpoint2D.y - 1, 0, 0, 0, "SG552");
		Tools::DrawString(Headpoint2D.x - 1, Headpoint2D.y + 1, 0, 0, 0, "SG552");
		Tools::DrawString(Headpoint2D.x, Headpoint2D.y, 255, 255, 255, "SG552");
	}
	if (BaseEntity->GetClientClass()->m_ClassID == ClassId->CWeaponTMP)
	{
		Tools::DrawString(Headpoint2D.x + 1, Headpoint2D.y + 1, 0, 0, 0, "TMP");
		Tools::DrawString(Headpoint2D.x - 1, Headpoint2D.y - 1, 0, 0, 0, "TMP");
		Tools::DrawString(Headpoint2D.x + 1, Headpoint2D.y - 1, 0, 0, 0, "TMP");
		Tools::DrawString(Headpoint2D.x - 1, Headpoint2D.y + 1, 0, 0, 0, "TMP");
		Tools::DrawString(Headpoint2D.x, Headpoint2D.y, 255, 255, 255, "TMP");
	}
	if (BaseEntity->GetClientClass()->m_ClassID == ClassId->CWeaponUMP45)
	{
		Tools::DrawString(Headpoint2D.x + 1, Headpoint2D.y + 1, 0, 0, 0, "UMP45");
		Tools::DrawString(Headpoint2D.x - 1, Headpoint2D.y - 1, 0, 0, 0, "UMP45");
		Tools::DrawString(Headpoint2D.x + 1, Headpoint2D.y - 1, 0, 0, 0, "UMP45");
		Tools::DrawString(Headpoint2D.x - 1, Headpoint2D.y + 1, 0, 0, 0, "UMP45");
		Tools::DrawString(Headpoint2D.x, Headpoint2D.y, 255, 255, 255, "UMP45");
	}
	if (BaseEntity->GetClientClass()->m_ClassID == ClassId->CWeaponUSP)
	{
		Tools::DrawString(Headpoint2D.x + 1, Headpoint2D.y + 1, 0, 0, 0, "USP");
		Tools::DrawString(Headpoint2D.x - 1, Headpoint2D.y - 1, 0, 0, 0, "USP");
		Tools::DrawString(Headpoint2D.x + 1, Headpoint2D.y - 1, 0, 0, 0, "USP");
		Tools::DrawString(Headpoint2D.x - 1, Headpoint2D.y + 1, 0, 0, 0, "USP");
		Tools::DrawString(Headpoint2D.x, Headpoint2D.y, 255, 255, 255, "USP");
	}
	if (BaseEntity->GetClientClass()->m_ClassID == ClassId->CWeaponXM1014)
	{
		Tools::DrawString(Headpoint2D.x + 1, Headpoint2D.y + 1, 0, 0, 0, "XM1014");
		Tools::DrawString(Headpoint2D.x - 1, Headpoint2D.y - 1, 0, 0, 0, "XM1014");
		Tools::DrawString(Headpoint2D.x + 1, Headpoint2D.y - 1, 0, 0, 0, "XM1014");
		Tools::DrawString(Headpoint2D.x - 1, Headpoint2D.y + 1, 0, 0, 0, "XM1014");
		Tools::DrawString(Headpoint2D.x, Headpoint2D.y, 255, 255, 255, "XM1014");
	}
	if (BaseEntity->GetClientClass()->m_ClassID == ClassId->CDEagle)
	{
		Tools::DrawString(Headpoint2D.x + 1, Headpoint2D.y + 1, 0, 0, 0, "DEagle");
		Tools::DrawString(Headpoint2D.x - 1, Headpoint2D.y - 1, 0, 0, 0, "DEagle");
		Tools::DrawString(Headpoint2D.x + 1, Headpoint2D.y - 1, 0, 0, 0, "DEagle");
		Tools::DrawString(Headpoint2D.x - 1, Headpoint2D.y + 1, 0, 0, 0, "DEagle");
		Tools::DrawString(Headpoint2D.x, Headpoint2D.y, 255, 255, 255, "DEagle");
	}
	if (BaseEntity->GetClientClass()->m_ClassID == ClassId->CBaseCSGrenadeProjectile)
	{
		Tools::DrawString(Headpoint2D.x + 1, Headpoint2D.y + 1, 0, 0, 0, "Grenade");
		Tools::DrawString(Headpoint2D.x - 1, Headpoint2D.y - 1, 0, 0, 0, "Grenade");
		Tools::DrawString(Headpoint2D.x + 1, Headpoint2D.y - 1, 0, 0, 0, "Grenade");
		Tools::DrawString(Headpoint2D.x - 1, Headpoint2D.y + 1, 0, 0, 0, "Grenade");
		Tools::DrawString(Headpoint2D.x, Headpoint2D.y, 255, 255, 255, "Grenade");
	}
}