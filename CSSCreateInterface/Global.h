#pragma once
#include "include.h"
#include "VMTHook.h"
#include "ImGui/imgui.h"
#include "CreateInterface.h"
#include <mutex>
#define ALT_KEY 0x12

namespace MutexLock
{
	/*extern std::recursive_mutex gMutex;*/
}

namespace HOOK // Global Hooks
{
	extern VMTHook* D3D9;
	extern VMTHook* Panel;
	extern VMTHook* DrawModle;
}

namespace Offset
{
	extern uintptr_t d3d9Device;
	extern BYTE oldCode[5];
}

namespace win
{
	extern HWND Window;
	extern WNDPROC oldWNDPROC;
	extern RECT m_Rect;
	extern int windowHeight;
	extern int windowWidth;
}

namespace Controller
{
	extern bool HookTesting;//掛勾狀態

	 
	extern bool windowVisible;//窗口可見
	extern bool TargetLine;
	extern bool BonesESP;
	extern bool ESPBOX;
	extern bool EspPlayerInfo;
	extern bool AimBot;

	////
	extern ImVec4 TargetLine_color_Team;
	extern ImVec4 TargetLine_color_Weapon;
	extern ImVec4 TargetLine_color_Enemy;

	extern bool TargetLine_check_Team;
	extern bool TargetLine_check_Weapon;
	extern bool TargetLine_check_Enemy;

	extern float TargetLine_Thickness;
	extern int TargetLineSelectedIndex;

	////
	extern ImVec4 BonesESP_color_Team;
	extern ImVec4 BonesESP_color_Weapon;
	extern ImVec4 BonesESP_color_Enemy;

	extern bool BonesESP_check_Team;
	extern bool BonesESP_check_Weapon;
	extern bool BonesESP_check_Enemy;

	extern bool BonesESP_Shadow;

	extern float BonesESP_Thickness;

	////
	extern bool ESPBOX_CHECK_TEAM;
	extern bool ESPBOX_CHECK_WEAPON;
	extern bool ESPBOX_CHECK_ENEMY;

	extern int ESPBOXSelectedIndex;

	////
	extern player_info_t info;
	extern bool info_Shadow;

	extern ImVec4 info_color_Team;//設定顏色控制條
	extern ImVec4 info_color_Weapon;
	extern ImVec4 info_color_Enemy;

	////
	extern float AimBotCircle;
	
}

namespace ModuleHandle
{
	extern uintptr_t __dwordEngine; //engine.dll句柄
	extern uintptr_t __dwordClient; //client.dll句柄
}
