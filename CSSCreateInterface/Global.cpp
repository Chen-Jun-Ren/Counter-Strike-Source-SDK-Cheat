#include"Global.h"
#include <mutex>

std::recursive_mutex MutexLock::gMutex;

VMTHook* HOOK::D3D9;
VMTHook* HOOK::Panel;
VMTHook* HOOK::DrawModle;


uintptr_t Offset::d3d9Device;
BYTE Offset::oldCode[5];



HWND win::Window;
WNDPROC win::oldWNDPROC;
RECT win::m_Rect;
int  win::windowHeight;
int  win::windowWidth;

bool Controller::HookTesting;

bool Controller::windowVisible = false; //預設為false
bool Controller::TargetLine = false;
bool Controller::BonesESP = false;
bool Controller::ESPBOX = false;
bool Controller::EspPlayerInfo = false;
bool Controller::AimBot = false;

//////targerline
ImVec4 Controller::TargetLine_color_Team = ImVec4(0.0f, 0.0f, 1.0f, 1.00f);//設定顏色控制條
ImVec4 Controller::TargetLine_color_Weapon = ImVec4(0.0f, 1.0f, 0.0f, 1.00f);
ImVec4 Controller::TargetLine_color_Enemy = ImVec4(1.0f, 0.0f, 0.0f, 1.00f);

bool Controller::TargetLine_check_Team;
bool Controller::TargetLine_check_Weapon;
bool Controller::TargetLine_check_Enemy;

float Controller::TargetLine_Thickness;

int Controller::TargetLineSelectedIndex = 2;

//////bonesesp
ImVec4 Controller::BonesESP_color_Team = ImVec4(0.0f, 0.0f, 1.0f, 1.00f);//設定顏色控制條
ImVec4 Controller::BonesESP_color_Weapon = ImVec4(0.0f, 1.0f, 0.0f, 1.00f);
ImVec4 Controller::BonesESP_color_Enemy = ImVec4(1.0f, 0.0f, 0.0f, 1.00f);

bool Controller::BonesESP_check_Team;
bool Controller::BonesESP_check_Weapon;
bool Controller::BonesESP_check_Enemy;

bool Controller::BonesESP_Shadow;

float Controller::BonesESP_Thickness;

//////ESP BOX
bool Controller::ESPBOX_CHECK_TEAM;
bool Controller::ESPBOX_CHECK_WEAPON;
bool Controller::ESPBOX_CHECK_ENEMY;

int Controller::ESPBOXSelectedIndex = 0;

//////EntityObjInfo
player_info_t Controller::info;
bool Controller::info_Shadow;
ImVec4 Controller::info_color_Team = ImVec4(0.0f, 1.0f, 1.0f, 1.00f);//設定顏色控制條
ImVec4 Controller::info_color_Weapon = ImVec4(0.0f, 1.0f, 0.0f, 1.00f);
ImVec4 Controller::info_color_Enemy = ImVec4(1.0f, 0.0f, 1.0f, 1.00f);

/////AIMBOT
float Controller::AimBotCircle = 170.0f;


uintptr_t ModuleHandle::__dwordClient;
uintptr_t ModuleHandle::__dwordEngine;