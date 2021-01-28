#include "EspBox.h"
#include "Global.h"
#include "CreateInterface.h"
#include "CBaseEntity.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx9.h"
#include "ImGui/imgui_impl_win32.h"
#include "Tools.h"
#include <math.h>



Vector head3DPos;
Vec2 head2DPos;

Vec2 Origin2DPos;

void EspBox(IDirect3DDevice9* pDevice, int R, int G, int B);

void doEspBox(IDirect3DDevice9* pDevice)
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
				//測試代碼(失敗)
				/*{
					for (int j = 0; j <= 2; j++)
					{
						if (Tools::GetBonePosEx(BaseEntity->GetBoneBaseAddress(), j, WeaponBonse3Dpos_1, WeaponBonse2Dpos_1))
						{
							Tools::DrawString(WeaponBonse2Dpos_1.x, WeaponBonse2Dpos_1.y, 255, 255, 255, "Id = %d", j);
						}
					}
				}*/
			}
			if (BaseEntity->IsPlayer())
			{
				if (BaseEntity->GetTeamNumber() == LocalPlayer->GetTeamNumber() && Controller::ESPBOX_CHECK_TEAM)
				{
					if (Tools::GetBonePosEx(BaseEntity->GetBoneBaseAddress(), 14, head3DPos, head2DPos) && Controller::ESPBOX_CHECK_TEAM)
					{
						Vec3 headCircle3DPos;
						Vec2 headCircle2DPos;

						headCircle3DPos.x = head3DPos.x + 5;
						headCircle3DPos.y = head3DPos.y + 5;
						headCircle3DPos.z = head3DPos.z + 5;

						if (Tools::WorldToScreen_Vec3(headCircle3DPos, headCircle2DPos))//頭
						{
							float headCircleLong = sqrtf(powf(head2DPos.x - headCircle2DPos.x, 2) + powf(head2DPos.y - headCircle2DPos.y, 2));//兩點距離計算公式
							Tools::DrawCircle(head2DPos.x, head2DPos.y, headCircleLong, 20, D3DCOLOR_ARGB(255, 0, 255, 0));
						}
						if (Tools::WorldToScreen(BaseEntity->GetvecOrigin(), Origin2DPos))//方框
						{
							EspBox(pDevice, 0, 255, 0);
							//float tall = sqrtf(powf(head2DPos.x - Origin2DPos.x, 2) + powf(head2DPos.y - Origin2DPos.y, 2));//兩點距離計算公式
							//Vec2 tl, tr, bl, br;
							//tl.x = head2DPos.x - (tall / 4.2);//左上
							//tl.y = head2DPos.y - (tall / 5.25);
							//tr.x = head2DPos.x + (tall / 4.2);//右上
							//tr.y = head2DPos.y - (tall / 5.25);
							//bl.x = Origin2DPos.x - (tall / 4.2);//左下
							//bl.y = Origin2DPos.y;
							//br.x = Origin2DPos.x + (tall / 4.2);//右下
							//br.y = Origin2DPos.y;
							//Tools::DrawLine(tl.x, tl.y, tr.x, tr.y, 2, 0, pDevice, 0, 255, 0);
							//Tools::DrawLine(tr.x, tr.y, br.x, br.y, 2, 0, pDevice, 0, 255, 0);
							//Tools::DrawLine(br.x, br.y, bl.x, bl.y, 2, 0, pDevice, 0, 255, 0);
							//Tools::DrawLine(bl.x, bl.y, tl.x, tl.y, 2, 0, pDevice, 0, 255, 0);

							//vec2 t, b, ml, mr;
							//t.x = head2DPos.x;
							//t.y = head2DPos.y;
							//ml.x = head2DPos.x - (tall / 2);
							//ml.y = head2DPos.y + (tall / 2);
							//mr.x = head2DPos.x + (tall / 2);
							//mr.y = head2DPos.y + (tall / 2);
							//b.x = Origin2DPos.x;
							//b.y = Origin2DPos.y;
							//Tools::DrawLine(t.x, t.y, mr.x, mr.y, 2, 0, pDevice, 0, 255, 0);
							//Tools::DrawLine(mr.x, mr.y, b.x, b.y, 2, 0, pDevice, 0, 255, 0);
							//Tools::DrawLine(b.x, b.y, ml.x, ml.y, 2, 0, pDevice, 0, 255, 0);
							//Tools::DrawLine(ml.x, ml.y, t.x, t.y, 2, 0, pDevice, 0, 255, 0);
						}
					}
				}

				if (BaseEntity->GetTeamNumber() != LocalPlayer->GetTeamNumber() && Controller::ESPBOX_CHECK_ENEMY)
				{
					if (Tools::GetBonePosEx(BaseEntity->GetBoneBaseAddress(), 14, head3DPos, head2DPos) && Controller::ESPBOX_CHECK_ENEMY)
					{
						Vec3 headCircle3DPos;
						Vec2 headCircle2DPos;

						headCircle3DPos.x = head3DPos.x + 5;
						headCircle3DPos.y = head3DPos.y + 5;
						headCircle3DPos.z = head3DPos.z + 5;

						if (Tools::WorldToScreen_Vec3(headCircle3DPos, headCircle2DPos))//頭
						{
							float headCircleLong = sqrtf(powf(head2DPos.x - headCircle2DPos.x, 2) + powf(head2DPos.y - headCircle2DPos.y, 2));//兩點距離計算公式
							Tools::DrawCircle(head2DPos.x, head2DPos.y, headCircleLong, 20, D3DCOLOR_ARGB(255, 255, 0, 0));
						}
						if (Tools::WorldToScreen(BaseEntity->GetvecOrigin(), Origin2DPos))
						{
							EspBox(pDevice, 255, 0, 0);
							//float tall = sqrtf(powf(head2DPos.x - Origin2DPos.x, 2) + powf(head2DPos.y - Origin2DPos.y, 2));//兩點距離計算公式
							//Vec2 tl, tr, bl, br;
							//tl.x = head2DPos.x - (tall / 4.2);
							//tl.y = head2DPos.y - (tall / 5.25);
							//tr.x = head2DPos.x + (tall / 4.2);
							//tr.y = head2DPos.y - (tall / 5.25);
							//bl.x = Origin2DPos.x - (tall / 4.2);
							//bl.y = Origin2DPos.y;
							//br.x = Origin2DPos.x + (tall / 4.2);
							//br.y = Origin2DPos.y;
							//Tools::DrawLine(tl.x, tl.y, tr.x, tr.y, 2, 0, pDevice, 255, 0, 0);
							//Tools::DrawLine(tr.x, tr.y, br.x, br.y, 2, 0, pDevice, 255, 0, 0);
							//Tools::DrawLine(br.x, br.y, bl.x, bl.y, 2, 0, pDevice, 255, 0, 0);
							//Tools::DrawLine(bl.x, bl.y, tl.x, tl.y, 2, 0, pDevice, 255, 0, 0);

							//vec2 t, b, ml, mr;
							//t.x = head2DPos.x;
							//t.y = head2DPos.y;
							//ml.x = head2DPos.x - (tall / 2);
							//ml.y = head2DPos.y + (tall / 2);
							//mr.x = head2DPos.x + (tall / 2);
							//mr.y = head2DPos.y + (tall / 2);
							//b.x = Origin2DPos.x;
							//b.y = Origin2DPos.y;
							//Tools::DrawLine(t.x, t.y, mr.x, mr.y, 2, 0, pDevice, 0, 255, 0);
							//Tools::DrawLine(mr.x, mr.y, b.x, b.y, 2, 0, pDevice, 0, 255, 0);
							//Tools::DrawLine(b.x, b.y, ml.x, ml.y, 2, 0, pDevice, 0, 255, 0);
							//Tools::DrawLine(ml.x, ml.y, t.x, t.y, 2, 0, pDevice, 0, 255, 0);
						}
					}
				}
			}
		}
	}
}


void EspBox(IDirect3DDevice9* pDevice, int R, int G, int B)
{
	float tall = sqrtf(powf(head2DPos.x - Origin2DPos.x, 2) + powf(head2DPos.y - Origin2DPos.y, 2));//兩點距離計算公式
	switch (Controller::ESPBOXSelectedIndex)
	{
	case 0:
		Vec2 tl, tr, bl, br;
		tl.x = head2DPos.x - (tall / 4.2);
		tl.y = head2DPos.y - (tall / 5.25);
		tr.x = head2DPos.x + (tall / 4.2);
		tr.y = head2DPos.y - (tall / 5.25);
		bl.x = Origin2DPos.x - (tall / 4.2);
		bl.y = Origin2DPos.y;
		br.x = Origin2DPos.x + (tall / 4.2);
		br.y = Origin2DPos.y;
		Tools::DrawLine(tl.x, tl.y, tr.x, tr.y, 2, 0, pDevice, R, G, B);
		Tools::DrawLine(tr.x, tr.y, br.x, br.y, 2, 0, pDevice, R, G, B);
		Tools::DrawLine(br.x, br.y, bl.x, bl.y, 2, 0, pDevice, R, G, B);
		Tools::DrawLine(bl.x, bl.y, tl.x, tl.y, 2, 0, pDevice, R, G, B);
		break;
	case 1:
		vec2 t, b, ml, mr;
		t.x = head2DPos.x;
		t.y = head2DPos.y;
		ml.x = head2DPos.x - (tall / 2);
		ml.y = head2DPos.y + (tall / 2);
		mr.x = head2DPos.x + (tall / 2);
		mr.y = head2DPos.y + (tall / 2);
		b.x = Origin2DPos.x;
		b.y = Origin2DPos.y;
		Tools::DrawLine(t.x, t.y, mr.x, mr.y, 2, 0, pDevice, R, G, B);
		Tools::DrawLine(mr.x, mr.y, b.x, b.y, 2, 0, pDevice, R, G, B);
		Tools::DrawLine(b.x, b.y, ml.x, ml.y, 2, 0, pDevice, R, G, B);
		Tools::DrawLine(ml.x, ml.y, t.x, t.y, 2, 0, pDevice, R, G, B);
		break;
	default:
		break;
	}
}
