#pragma once
#include "include.h"
#include "VMTHook.h"

namespace HOOK // Global Hooks
{
	extern VMTHook* D3D9;
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
}

namespace Controller
{
	extern bool windowVisible;//µ¡¤f¥i¨£
	extern bool HookTesting;//±¾¤Äª¬ºA
}

namespace ModuleHandle
{
	extern uintptr_t __dwordEngine; //engine.dll¥y¬`
	extern uintptr_t __dwordClient; //client.dll¥y¬`
}
