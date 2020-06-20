#include "include.h"
#include "Hooks.h"
#include "Tools.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx9.h"
#include "ImGui/imgui_impl_win32.h"
#include "Global.h"
#include "ClassIdManager.h"
#include "BonesESP.h"
#include "TargetLine.h"
#include "EspBox.h"
#include "Espinformation.h"
#include "SetupHack.h"
#include "AimBot.h"

EndSceneFn oEndScene;

bool bInit;

static const char* Pos_Index[] = { "RightBottom","LeftBottom","MiddleBottom","RightTop","LeftTop","MiddleTop" };//下拉是清單
static const char* ESPBOx_Index[] = {"Rect","Diamond"};

void __stdcall Hooks::EndScene(IDirect3DDevice9* Device)
{
	MutexLock::gMutex.lock();

	SetupHack::SetClassIdManager();//特殊必須寫在函數裡,使用完之後立即釋放.

	if (bInit == false)
	{
		bInit = true;
	}

	if(Controller::windowVisible)
	{
		ImGui_ImplDX9_NewFrame();
		ImGui_ImplWin32_NewFrame();

		ImGui::StyleColorsClassic();

		ImGui::NewFrame();
		
		/*Menu rendering here*/

		ImGui::Begin(" Counter-Strike:Source - SDK GameHacking");
		{
			if (ImGui::CollapsingHeader("AIM-Bot"))
			{
				ImGui::Checkbox("AIMBOT", &Controller::AimBot);
				if (Controller::AimBot)
				{
					ImGui::Text("Press 'ALT' to use AIMBOT");
					ImGui::SliderFloat("AIMBOT_Circle", &Controller::AimBotCircle,0,1200);
				}
			}

			if (ImGui::CollapsingHeader("ESP-Hack"))//主介面
			{
				ImGui::Checkbox("TargitLine", &Controller::TargetLine);//目標線條
				if (Controller::TargetLine)
				{
					ImGui::SliderFloat("TargetLine_Thickness", &Controller::TargetLine_Thickness, 1, 10);
					ImGui::Combo("ListBox", &Controller::TargetLineSelectedIndex, Pos_Index, IM_ARRAYSIZE(Pos_Index));

					ImGui::Checkbox("Team###TargetLine_Team", &Controller::TargetLine_check_Team);
					if (Controller::TargetLine_check_Team)
					{
						ImGui::ColorEdit3("Team_Color###TargetLine_Team_Color", (float*)&Controller::TargetLine_color_Team);
					}

					ImGui::Checkbox("Enemy###TargetLine_Enemy", &Controller::TargetLine_check_Enemy);
					if (Controller::TargetLine_check_Enemy)
					{
						ImGui::ColorEdit3("Enemy_Color###TargetLine_Enemy_Color", (float*)&Controller::TargetLine_color_Enemy);
					}

					ImGui::Checkbox("Weapon###TargetLine_Weapon", &Controller::TargetLine_check_Weapon);
					if (Controller::TargetLine_check_Weapon)
					{
						ImGui::ColorEdit3("Weapon_Color###TargetLine_Weapon_Color", (float*)&Controller::TargetLine_color_Weapon);
					}
				}

				ImGui::Checkbox("BonesESP", &Controller::BonesESP);//骨骼透視
				if (Controller::BonesESP)
				{
					ImGui::Checkbox("Shadow", &Controller::BonesESP_Shadow);
					ImGui::SliderFloat("BonesESP_Thickness", &Controller::BonesESP_Thickness, 1, 10);
					
					ImGui::Checkbox("Team###BonesESP_Team", &Controller::BonesESP_check_Team);
					if (Controller::BonesESP_check_Team)
					{
						ImGui::ColorEdit3("Team_Color###BonesESP_Team_Color", (float*)&Controller::BonesESP_color_Team);
					}
					/*ImGui::Checkbox("Weapon###BonesESP", &Controller::BonesESP_check_Weapon);
					if (Controller::BonesESP_check_Weapon)
					{
						ImGui::ColorEdit3("Weapon_Color###BonesESP", (float*)&Controller::BonesESP_color_Weapon);
					}*/
					ImGui::Checkbox("Enemy###BonesESP_Enemy", &Controller::BonesESP_check_Enemy);
					if (Controller::BonesESP_check_Enemy)
					{
						ImGui::ColorEdit3("Enemy_Color###BonesESP_Enemy_Color", (float*)&Controller::BonesESP_color_Enemy);
					}
				}

				ImGui::Checkbox("ESP-BOX", &Controller::ESPBOX);//ESP BOX 透視
				if(Controller::ESPBOX)
				{
					ImGui::Combo("ListBox###LISTBOX_ESP_BOX", &Controller::ESPBOXSelectedIndex, ESPBOx_Index, IM_ARRAYSIZE(ESPBOx_Index));
					ImGui::Checkbox("Team###ESPBOX_CHECK_TEAM", &Controller::ESPBOX_CHECK_TEAM);
					ImGui::Checkbox("Enemy###ESPBOX_CHECK_ENEMY", &Controller::ESPBOX_CHECK_ENEMY);
				}

				ImGui::Checkbox("ESP-Information", &Controller::EspPlayerInfo);//玩家資訊
				if (Controller::EspPlayerInfo)
				{
					ImGui::Checkbox("Shadow###Information-Shadow", &Controller::info_Shadow);
					ImGui::ColorEdit3("Team_Color###Information_Team_Color", (float*)&Controller::info_color_Team);
					ImGui::ColorEdit3("Enemy_Color###Information_Enemy_Color", (float*)&Controller::info_color_Enemy);
				}
			}
			
		}

		//ImGui::ShowTestWindow();//測試窗口
				
		/*Menu rendering here*/
		ImGui::End();
		ImGui::EndFrame();
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
	}

	TargetLineESP(Device);//呼叫目標線條函數;
	doBonesESP(Device);//呼叫骨骼函數;
	doEspBox(Device);//呼叫box函數
	doInformation(Device);//呼叫Entiy_Info;
	if (Controller::AimBot)//控制圓圈
	{
		doAimBot();
		Tools::DrawCircle(win::windowWidth / 2, win::windowHeight / 2, Controller::AimBotCircle, 50, D3DCOLOR_ARGB(255, 255, 0, 0));
	}
	
	
	Tools::DrawString(800 + 1, 10 + 1, 0, 0, 0, "為美好的世界獻上祝福");
	Tools::DrawString(800 + 1, 10 - 1, 0, 0, 0, "為美好的世界獻上祝福");
	Tools::DrawString(800 - 1, 10 - 1, 0, 0, 0, "為美好的世界獻上祝福");
	Tools::DrawString(800 - 1, 10 + 1, 0, 0, 0, "為美好的世界獻上祝福");
	Tools::DrawString(800, 10, 230, 0, 230, "為美好的世界獻上祝福");

	delete ClassId;//
	
	MutexLock::gMutex.unlock();
	return oEndScene(Device);
}