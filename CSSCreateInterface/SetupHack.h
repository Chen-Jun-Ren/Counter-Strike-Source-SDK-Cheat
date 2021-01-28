#pragma once
#include "include.h"

namespace SetupHack 
{
	extern void Setup();
	extern void SetupInterface();
	extern void SetupPatternScanning();
	extern void SetupHook();
	extern void SetNetVarManagement();
	extern void SetClassIdManager();
	extern void SetAimClassIdManager();
	extern void SetModuleHandle();
	extern void SetFontA();
	extern void SetImGui();
	extern void SetWNDPROC();
	
	extern void UpDate();
	extern void GetViewMatrix();
	extern void GetWindowSize();

}

namespace ExitHack
{
	extern void Exit();
}
