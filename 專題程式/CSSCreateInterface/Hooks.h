#pragma once
#include "include.h"

typedef void(APIENTRY* EndSceneFn)(IDirect3DDevice9* pDevice);
extern EndSceneFn oEndScene;

typedef BOOL(WINAPI* SetCursorPosFn)(int X, int Y);
extern SetCursorPosFn oSetCursorPos;

namespace Hooks
{
	extern void __stdcall EndScene(IDirect3DDevice9* pDevice);
	extern BOOL WINAPI HookSetCursorPos(int X,int Y);
}