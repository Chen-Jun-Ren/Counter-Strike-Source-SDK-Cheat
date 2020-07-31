#pragma once
#include "include.h"
#include "CreateInterface.h"

typedef void(APIENTRY* EndSceneFn)(IDirect3DDevice9* pDevice);
extern EndSceneFn oEndScene;

typedef BOOL(WINAPI* SetCursorPosFn)(int X, int Y);
extern SetCursorPosFn oSetCursorPos;

//using PaintTraverseFn = void(__thiscall*)(void*, unsigned int, bool, bool);
//extern PaintTraverseFn oPaintTraverse;

typedef void(__thiscall* PaintTraverseFn)(void*, unsigned int, bool, bool);
extern PaintTraverseFn oPaintTraverse;

typedef void(__stdcall* DrawModelExecuteFn)(const ModelRenderInfo_t& state, const ModelRenderInfo_t& pInfo, matrix3x4_t* pCustomBoneToWorld);
extern DrawModelExecuteFn oDrawModelExecute;

namespace Hooks
{
	extern void __stdcall EndScene(IDirect3DDevice9* pDevice);
	extern BOOL WINAPI HookSetCursorPos(int X,int Y);
	extern void __stdcall HookPaintTraverse(int VGUIPanel, bool ForceRepaint, bool AllowForce);
	extern void __stdcall HookDrawModelExecute(const ModelRenderInfo_t& state, const ModelRenderInfo_t& pInfo, matrix3x4_t* pCustomBoneToWorld);
}