#pragma once
#include "include.h"
namespace SetupHack 
{
	extern void Setup();
	extern void SetupInterface();
	extern void SetupPatternScanning();
	extern void SetupHook();
	extern void SetNetVarManagement();
	extern void SetModuleHandle();
	extern void SetFontA();
	extern void SetImGui();
	extern void SetWNDPROC();
}

namespace ExitHack
{
	extern void Exit();
}