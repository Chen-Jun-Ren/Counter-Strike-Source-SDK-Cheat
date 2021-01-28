// dllmain.cpp : 定義 DLL 應用程式的進入點。

//2020/06/23 TESTING
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
	std::cout << "Present Address: 0x" << (DWORD*)(*(DWORD**)Offset::d3d9Device)[17] << std::endl;

	//#define strenc( s ) ( s )
	//std::cout << "discord_present_address: 0x" << (DWORD*)Tools::FindPattern(strenc("discordhook.dll"), strenc("55 89 E5 53 57 56 83 EC 1C A1 ?? ?? ?? ?? 8B 7D 08 8B 75 14 8B 5D 0C 8D 4D D8 31 E8 89 FA 89 45 F0 53 56 6A 00")) << std::endl;

	std::cout << "IVEngineModel016 Obj Address:	0x" << std::hex << Interface->ModelRender << std::endl;
	std::cout << "VEngineRenderView014 Obj Address:	0x" << std::hex << Interface->RenderView << std::endl;
	std::cout << "VModelInfoClient006 Obj Address:	0x" << std::hex << Interface->ModelInfo << std::endl;

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

