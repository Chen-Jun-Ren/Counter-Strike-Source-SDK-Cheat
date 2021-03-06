#include "SetupHack.h"
#include "include.h"
#include "Global.h"
#include "Tools.h"
#include "Hooks.h"
#include "CreateInterface.h"
#include "NetVarManagement.h"
#include "ClassIdManager.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx9.h"
#include "ImGui/imgui_impl_win32.h"
#include "inlineHook.h"


//#include "Tools.h"


#define strenc( s ) ( s )

const DWORD cl_mouseenable = 0x4F3FD0;//鎖定視角指令偏移
const DWORD viewMatrixOffset = 0x5A78EC;//視圖矩陣偏移

extern IMGUI_IMPL_API LRESULT  ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK newWNDPROC(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (GetAsyncKeyState(VK_INSERT) & true)
	{
		Controller::windowVisible = !Controller::windowVisible;
	}
	if (Controller::windowVisible)
	{
		if (!Controller::HookTesting)//確認掛勾是否未掛上
		{
			*(DWORD*)(ModuleHandle::__dwordClient + cl_mouseenable) = 0;//鎖定視角
			inlineHook::Hook((DWORD)Hooks::HookSetCursorPos, (DWORD)SetCursorPos, (DWORD)Offset::oldCode);//安裝掛勾
			Controller::HookTesting = !Controller::HookTesting;
		}
		if (ImGui::GetCurrentContext())
		{
			ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);
			return true;
		}
	}
	else
	{
		if (Controller::HookTesting)//確認掛勾是否已掛上
		{
			*(DWORD*)(ModuleHandle::__dwordClient + cl_mouseenable) = 1;//解鎖視角
			inlineHook::UnHook((DWORD)SetCursorPos, Offset::oldCode);//卸載掛勾
			Controller::HookTesting = !Controller::HookTesting;
		}
		return CallWindowProc(win::oldWNDPROC, hWnd, uMsg, wParam, lParam);
	}
}

//設定偏移量初始值
void SetupHack::SetNetVarManagement()
{
	NetVarManagement = new CNetVarManagement();
}

//設定ClassId初始值
void SetupHack::SetClassIdManager()
{
	ClassId = new ClassIdManager();
}

void SetupHack::SetAimClassIdManager()
{
	AimClassId = new ClassIdManager();
}

//設定掛勾
void SetupHack::SetupHook()
{
	HOOK::D3D9 = new VMTHook((uintptr_t**)Offset::d3d9Device);
	oEndScene = (EndSceneFn)HOOK::D3D9->HookFunction((DWORD)Hooks::EndScene, 42);

	HOOK::Panel = new VMTHook((uintptr_t**)Interface->Panel);
	oPaintTraverse = (PaintTraverseFn)HOOK::Panel->HookFunction((DWORD)Hooks::HookPaintTraverse, 41);

	HOOK::DrawModle = new VMTHook((uintptr_t**)Interface->ModelRender);
	oDrawModelExecute = (DrawModelExecuteFn)HOOK::DrawModle->HookFunction((DWORD)Hooks::HookDrawModelExecute, 19);
}

//設定特徵碼初始值
void SetupHack::SetupPatternScanning()
{
	Offset::d3d9Device = **(uintptr_t**)(Tools::FindPattern(strenc("shaderapidx9.dll"), strenc("A1 ?? ?? ?? ?? 50 8B 08 FF 51 0C")) + 1);
}

//創建介面
void SetupHack::SetupInterface()
{
	Interface = new CInterface();
}

//設定模塊句柄
void SetupHack::SetModuleHandle()
{
	win::Window = FindWindowA("Valve001",NULL);//透過窗口類名獲取窗口句柄
	ModuleHandle::__dwordEngine = (uintptr_t)GetModuleHandle("engine.dll"); //engine.dll獲取模塊句柄
	ModuleHandle::__dwordClient = (uintptr_t)GetModuleHandle("client.dll"); //client.dll獲取模塊句柄 測試錯誤
}

//初始化文字
void SetupHack::SetFontA()
{
	D3DXCreateFontA((IDirect3DDevice9*)Offset::d3d9Device, 13, 0, FW_HEAVY, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "宋体", &g_font);
	D3DXCreateLine((IDirect3DDevice9*)Offset::d3d9Device, &m_Line);
	m_Line->SetWidth(1.0f);
	m_Line->SetPattern(0xFFFFFFFF);
	m_Line->SetAntialias(false);//關閉反鋸齒
}

//初始化ImGui
void SetupHack::SetImGui()
{
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//ImGui::GetIO().MouseDrawCursor = TRUE;//顯示滑鼠游標
	io.MouseDrawCursor = TRUE;//顯示滑鼠游標
	ImGui::StyleColorsDark();
	ImGui_ImplWin32_Init(win::Window);
	ImGui_ImplDX9_Init((IDirect3DDevice9*)Offset::d3d9Device);
}

//替換窗口消息處理函數
void SetupHack::SetWNDPROC()
{
	win::oldWNDPROC = (WNDPROC)SetWindowLongA(win::Window, GWL_WNDPROC,(LONG)newWNDPROC);
}

void SetupHack::GetViewMatrix()
{
	pViewMatrix = *(CViewMatrix*)(ModuleHandle::__dwordEngine + viewMatrixOffset);
}

void SetupHack::GetWindowSize()
{
	//GetWindowRect(win::Window, &win::m_Rect);
	GetClientRect(win::Window, &win::m_Rect);//獲取窗口座標
	win::windowWidth = win::m_Rect.right - win::m_Rect.left;
	win::windowHeight = win::m_Rect.bottom - win::m_Rect.top;
}

void SetupHack::Setup()
{

	SetupHack::SetModuleHandle();

	SetupHack::SetupInterface();

	SetupHack::SetNetVarManagement();

	//SetupHack::SetClassIdManager();

	SetupHack::SetupPatternScanning();

	SetupHack::SetFontA();

	SetupHack::SetWNDPROC();

	SetupHack::SetImGui();
	
	SetupHack::SetupHook();
}

//卸載
void ExitHack::Exit()
{
	//卸載還原掛勾
	delete HOOK::D3D9;
	delete HOOK::Panel;
	//HOOK::D3D9->UnHook();

	//如果掛勾為掛起狀態卸載掛勾
	if (Controller::HookTesting)
	{
		inlineHook::UnHook((DWORD)SetCursorPos, Offset::oldCode);
		*(bool*)(ModuleHandle::__dwordClient + cl_mouseenable) = 1;//卸載鎖定
	}

	//還原窗口消息處裡函數
	SetWindowLongA(win::Window, GWL_WNDPROC, (LONG)win::oldWNDPROC);
	//釋放
	delete Interface;
}



//更新資料
void SetupHack::UpDate()
{
	//SetupHack::GetViewMatrix();//取得視圖矩陣;
	SetupHack::GetWindowSize();//獲取窗口 高 寬

	//SetupHack::SetClassIdManager();//注意update
}