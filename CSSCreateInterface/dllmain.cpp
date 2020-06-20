// dllmain.cpp : 定義 DLL 應用程式的進入點。
#include "include.h"
#include "CreateInterface.h"
#include "NetVarManagement.h"
#include "CBaseEntity.h"
#include "SetupHack.h"
#include "ImGui/imgui.h"
#include "AimBot.h"

DWORD WINAPI GameHackThread(HMODULE hModule)
{
	AllocConsole();
	FILE* f;
	freopen_s(&f, "CONOUT$", "w", stdout);

	//功能區
	
	SetupHack::Setup();//設定初始值

	std::cout << "pDevice: 0x" << *(DWORD**)Offset::d3d9Device << std::endl;

	while (!GetAsyncKeyState(VK_END))
	{
		SetupHack::UpDate();
		//doAimBot();
	}

	ExitHack::Exit();

	if (f) fclose(f);
	FreeConsole();
	FreeLibraryAndExitThread(hModule, 0);
	return 0;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
	{
		HANDLE handle = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)GameHackThread, hModule, 0, nullptr);
		if (handle) CloseHandle(handle);
		ImGui::CreateContext();
	}
		break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

