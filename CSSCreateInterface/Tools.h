#pragma once
#include "include.h"
#include "psapi.h"
#include "Vector.h"

#define TORAD(x) ((x) * 0.01745329252)
#define ABS(x) ((x < 0) ? (-x) : (x))

struct Vec2
{
	float x, y;
};

struct Vec3
{
	float x, y, z;
};

struct CViewMatrix
{
	float Matrix[16];
};

extern ID3DXFont* g_font;
extern ID3DXLine* m_Line;
extern CViewMatrix pViewMatrix;

namespace Tools
{
	extern uintptr_t FindPattern(std::string moduleName, std::string pattern);
	extern void DrawString(LONG x, LONG y, int R, int G, int B, const char* fmt, ...);
	extern void DrawLine(float x1, float y1, float x2, float y2, float width, bool antialias, IDirect3DDevice9* pDevice, int R, int G, int B);
	extern void DrawCircle(int X, int Y, int radius, int numSides, DWORD Color);
	extern bool WorldToScreen(Vector pos, Vec2& screen);
	extern bool WorldToScreen_Vec3(Vec3 pos, Vec2& screen);
	extern bool GetBonePosEx(uintptr_t boneBase, int boneID, Vec3& bonePos, Vec2& screen);
	
}