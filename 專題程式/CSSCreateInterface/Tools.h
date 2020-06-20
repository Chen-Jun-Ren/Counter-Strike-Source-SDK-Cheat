#pragma once
#include "include.h"
#include "psapi.h"
extern ID3DXFont* g_font;

namespace Tools
{
	extern uintptr_t FindPattern(std::string moduleName, std::string pattern);
	extern void DrawString(LONG x, LONG y, int r, int g, int b, const char* fmt, ...);
}