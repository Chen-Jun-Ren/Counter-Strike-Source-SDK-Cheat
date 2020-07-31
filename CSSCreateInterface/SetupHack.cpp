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

const DWORD cl_mouseenable = 0x4F3FD0;//��w�������O����
const DWORD viewMatrixOffset = 0x5A78EC;//���ϯx�}����

extern IMGUI_IMPL_API LRESULT  ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK newWNDPROC(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (GetAsyncKeyState(VK_INSERT) & true)
	{
		Controller::windowVisible = !Controller::windowVisible;
	}
	if (Controller::windowVisible)
	{
		if (!Controller::HookTesting)//�T�{���ĬO�_�����W
		{
			*(DWORD*)(ModuleHandle::__dwordClient + cl_mouseenable) = 0;//��w����
			inlineHook::Hook((DWORD)Hooks::HookSetCursorPos, (DWORD)SetCursorPos, (DWORD)Offset::oldCode);//�w�˱���
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
		if (Controller::HookTesting)//�T�{���ĬO�_�w���W
		{
			*(DWORD*)(ModuleHandle::__dwordClient + cl_mouseenable) = 1;//�������
			inlineHook::UnHook((DWORD)SetCursorPos, Offset::oldCode);//��������
			Controller::HookTesting = !Controller::HookTesting;
		}
		return CallWindowProc(win::oldWNDPROC, hWnd, uMsg, wParam, lParam);
	}
}

//�]�w�����q��l��
void SetupHack::SetNetVarManagement()
{
	NetVarManagement = new CNetVarManagement();
}

//�]�wClassId��l��
void SetupHack::SetClassIdManager()
{
	ClassId = new ClassIdManager();
}

void SetupHack::SetAimClassIdManager()
{
	AimClassId = new ClassIdManager();
}

//�]�w����
void SetupHack::SetupHook()
{
	HOOK::D3D9 = new VMTHook((uintptr_t**)Offset::d3d9Device);
	oEndScene = (EndSceneFn)HOOK::D3D9->HookFunction((DWORD)Hooks::EndScene, 42);

	HOOK::Panel = new VMTHook((uintptr_t**)Interface->Panel);
	oPaintTraverse = (PaintTraverseFn)HOOK::Panel->HookFunction((DWORD)Hooks::HookPaintTraverse, 41);

	HOOK::DrawModle = new VMTHook((uintptr_t**)Interface->ModelRender);
	oDrawModelExecute = (DrawModelExecuteFn)HOOK::DrawModle->HookFunction((DWORD)Hooks::HookDrawModelExecute, 19);
}

//�]�w�S�x�X��l��
void SetupHack::SetupPatternScanning()
{
	Offset::d3d9Device = **(uintptr_t**)(Tools::FindPattern(strenc("shaderapidx9.dll"), strenc("A1 ?? ?? ?? ?? 50 8B 08 FF 51 0C")) + 1);
}

//�Ыؤ���
void SetupHack::SetupInterface()
{
	Interface = new CInterface();
}

//�]�w�Ҷ��y�`
void SetupHack::SetModuleHandle()
{
	win::Window = FindWindowA("Valve001",NULL);//�z�L���f���W������f�y�`
	ModuleHandle::__dwordEngine = (uintptr_t)GetModuleHandle("engine.dll"); //engine.dll����Ҷ��y�`
	ModuleHandle::__dwordClient = (uintptr_t)GetModuleHandle("client.dll"); //client.dll����Ҷ��y�` ���տ��~
}

//��l�Ƥ�r
void SetupHack::SetFontA()
{
	D3DXCreateFontA((IDirect3DDevice9*)Offset::d3d9Device, 13, 0, FW_HEAVY, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "���^", &g_font);
	D3DXCreateLine((IDirect3DDevice9*)Offset::d3d9Device, &m_Line);
	m_Line->SetWidth(1.0f);
	m_Line->SetPattern(0xFFFFFFFF);
	m_Line->SetAntialias(false);//�����Ͽ���
}

//��l��ImGui
void SetupHack::SetImGui()
{
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//ImGui::GetIO().MouseDrawCursor = TRUE;//��ܷƹ����
	io.MouseDrawCursor = TRUE;//��ܷƹ����
	ImGui::StyleColorsDark();
	ImGui_ImplWin32_Init(win::Window);
	ImGui_ImplDX9_Init((IDirect3DDevice9*)Offset::d3d9Device);
}

//�������f�����B�z���
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
	GetClientRect(win::Window, &win::m_Rect);//������f�y��
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

//����
void ExitHack::Exit()
{
	//�����٭챾��
	delete HOOK::D3D9;
	delete HOOK::Panel;
	//HOOK::D3D9->UnHook();

	//�p�G���Ĭ����_���A��������
	if (Controller::HookTesting)
	{
		inlineHook::UnHook((DWORD)SetCursorPos, Offset::oldCode);
		*(bool*)(ModuleHandle::__dwordClient + cl_mouseenable) = 1;//������w
	}

	//�٭쵡�f�����B�̨��
	SetWindowLongA(win::Window, GWL_WNDPROC, (LONG)win::oldWNDPROC);
	//����
	delete Interface;
}



//��s���
void SetupHack::UpDate()
{
	//SetupHack::GetViewMatrix();//���o���ϯx�};
	SetupHack::GetWindowSize();//������f �� �e

	//SetupHack::SetClassIdManager();//�`�Nupdate
}