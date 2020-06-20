#include"Global.h"

VMTHook* HOOK::D3D9;



uintptr_t Offset::d3d9Device;
BYTE Offset::oldCode[5];



HWND win::Window;
WNDPROC win::oldWNDPROC;



bool Controller::windowVisible = false; //¹w³]¬°false
bool Controller::HookTesting;



uintptr_t ModuleHandle::__dwordClient;
uintptr_t ModuleHandle::__dwordEngine;