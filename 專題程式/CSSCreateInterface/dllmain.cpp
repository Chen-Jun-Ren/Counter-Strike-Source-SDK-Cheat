// dllmain.cpp : 定義 DLL 應用程式的進入點。
#include "include.h"
#include "CreateInterface.h"
#include "NetVarManagement.h"
#include "CBaseEntity.h"
#include "SetupHack.h"
#include "ImGui/imgui.h"

DWORD WINAPI GameHackThread(HMODULE hModule)
{
	AllocConsole();
	FILE* f;
	freopen_s(&f, "CONOUT$", "w", stdout);

	//功能區
	player_info_t info;
	SetupHack::Setup();//設定初始值

	while (!GetAsyncKeyState(VK_END))
	{
		for (int i = 1; i <= 10/*Interface->ClientEntityList->GetMaxEntities()*/; i++)
		{
			C_BaseEntity* EntityObj = (C_BaseEntity*)Interface->ClientEntityList->GetClientEntity(i);
			Interface->VEngineClient->GetPlayerInfo(i, &info);
			if (!EntityObj)
				continue;
			if (!EntityObj->GetlifeState())
				continue;

			/*std::cout 
				<< "C_BaseEntity size: " << sizeof(EntityObj)
				<< " \n Entity" << i << " Address :" << EntityObj->GetThisptr()
				<< " \n Health: " << EntityObj->GetHealthValue()
				<< " \n Team: " << EntityObj->GetTeamNumber()
				<< " \n PlayerName: " << info.name
				<< " \n LifeState: " << EntityObj->GetlifeState()
				<< " \n m_vecOrigin X: " << EntityObj->GetvecOrigin().x
				<< " \n m_vecOrigin Y: " << EntityObj->GetvecOrigin().y
				<< " \n m_vecOrigin Z: " << EntityObj->GetvecOrigin().z
				<< " \n isDormant: " << EntityObj->IsDormant()
				<< " \n ArmorValue: " << EntityObj->GetArmorValue()
				<< " \n GetClassID: " << EntityObj->GetClientClass()->m_ClassID
				<<  std::endl << std::endl;*/
		}
		//system("cls");
		//Sleep(2);
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

