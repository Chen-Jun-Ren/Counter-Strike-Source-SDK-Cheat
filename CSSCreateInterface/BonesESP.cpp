#include "TargetLine.h"
#include "Global.h"
#include "CreateInterface.h"
#include "CBaseEntity.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx9.h"
#include "ImGui/imgui_impl_win32.h"
#include "Tools.h"
#include "Vector.h"

Vec2 Bone2D_Pos_A;
Vec2 Bone2D_Pos_B;

void DrawBoneShadow(IDirect3DDevice9* pDevice);//影子


void doBonesESP(IDirect3DDevice9* pDevice)
{
	if (Controller::BonesESP && Interface)
	{
		static const int Bone_ID_A[] = { 16,29,6,7,2,3,29,29,30,16,17,18,12,14,15,28 };//骨骼座標1
		static const int Bone_ID_B[] = { 9,9,9,6,9,2,28,30,31,15,16,17,9,12,12,12 };//骨骼座標2

		Vec3 Bone3D_Pos_A;

		Vec3 Bone3D_Pos_B;

		C_BaseEntity* LocalPlayer = (C_BaseEntity*)Interface->ClientEntityList->GetClientEntity(1);

		for (int j = 0; j <= 32; j++)
		{
			if (!Interface) break;
			C_BaseEntity* BaseEntity = (C_BaseEntity*)Interface->ClientEntityList->GetClientEntity(j);
			if (BaseEntity == nullptr)
				continue;
			if (BaseEntity == Interface->ClientEntityList->GetClientEntity(1))
				continue;
			if (BaseEntity->GetlifeState() == false)
				continue;
			if (BaseEntity->isDormant() == true)
				continue;
			if (BaseEntity->GetvecOrigin().x == 0.000000 && BaseEntity->GetvecOrigin().y == 0.000000 && BaseEntity->GetvecOrigin().z == 0.000000)
				continue;
			if (BaseEntity->IsPlayer() == true)//------Players------//
			{
				//for (int i = 0; i <= 50; i++)//繪製骨骼ID
				//{
				//	if (Tools::GetBonePosEx(BaseEntity->GetBoneBaseAddress(), i, Bone3D_Pos_A, Bone2D_Pos_A))
				//	{
				//		Tools::DrawString(Bone2D_Pos_A.x, Bone2D_Pos_A.y, 255, 255, 255, "%d", i);
				//	}
				//}
				for (int i = 0; i <= (IM_ARRAYSIZE(Bone_ID_A) - 1); i++)//sizeof(Bone_ID_A) = 72
				{
					if (BaseEntity->GetTeamNumber() == LocalPlayer->GetTeamNumber() && Controller::BonesESP_check_Team)//------Team------//
					{
						if ((Tools::GetBonePosEx(BaseEntity->GetBoneBaseAddress(), Bone_ID_A[i], Bone3D_Pos_A, Bone2D_Pos_A)) && (Tools::GetBonePosEx(BaseEntity->GetBoneBaseAddress(), Bone_ID_B[i], Bone3D_Pos_B, Bone2D_Pos_B)))
						{
							if (Controller::BonesESP_Shadow)DrawBoneShadow(pDevice);
							Tools::DrawLine(Bone2D_Pos_A.x, Bone2D_Pos_A.y, Bone2D_Pos_B.x, Bone2D_Pos_B.y, Controller::BonesESP_Thickness, 0, pDevice, (int)(Controller::BonesESP_color_Team.x * 255.0f), (int)(Controller::BonesESP_color_Team.y * 255.0f), (int)(Controller::BonesESP_color_Team.z * 255.0f));
						}
					}
					if (BaseEntity->GetTeamNumber() != LocalPlayer->GetTeamNumber() && Controller::BonesESP_check_Enemy)//------Enemy------//
					{
						if ((Tools::GetBonePosEx(BaseEntity->GetBoneBaseAddress(), Bone_ID_A[i], Bone3D_Pos_A, Bone2D_Pos_A)) && (Tools::GetBonePosEx(BaseEntity->GetBoneBaseAddress(), Bone_ID_B[i], Bone3D_Pos_B, Bone2D_Pos_B)))
						{
							if (Controller::BonesESP_Shadow)DrawBoneShadow(pDevice);
							Tools::DrawLine(Bone2D_Pos_A.x, Bone2D_Pos_A.y, Bone2D_Pos_B.x, Bone2D_Pos_B.y, Controller::BonesESP_Thickness, 0, pDevice, (int)(Controller::BonesESP_color_Enemy.x * 255.0f), (int)(Controller::BonesESP_color_Enemy.y * 255.0f), (int)(Controller::BonesESP_color_Enemy.z * 255.0f));
						}
					}
				}
			}
			if (!Interface) break;
		}
	}
}

void DrawBoneShadow(IDirect3DDevice9* pDevice)//影子
{
	Tools::DrawLine(Bone2D_Pos_A.x - 1, Bone2D_Pos_A.y - 1, Bone2D_Pos_B.x - 1, Bone2D_Pos_B.y - 1, Controller::BonesESP_Thickness, 0, pDevice, 0, 0, 0);
	Tools::DrawLine(Bone2D_Pos_A.x + 1, Bone2D_Pos_A.y + 1, Bone2D_Pos_B.x + 1, Bone2D_Pos_B.y + 1, Controller::BonesESP_Thickness, 0, pDevice, 0, 0, 0);
	Tools::DrawLine(Bone2D_Pos_A.x + 1, Bone2D_Pos_A.y - 1, Bone2D_Pos_B.x + 1, Bone2D_Pos_B.y - 1, Controller::BonesESP_Thickness, 0, pDevice, 0, 0, 0);
	Tools::DrawLine(Bone2D_Pos_A.x - 1, Bone2D_Pos_A.y + 1, Bone2D_Pos_B.x - 1, Bone2D_Pos_B.y + 1, Controller::BonesESP_Thickness, 0, pDevice, 0, 0, 0);
}