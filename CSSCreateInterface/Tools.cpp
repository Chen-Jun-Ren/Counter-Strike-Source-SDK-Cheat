#include "Tools.h"
#include "Global.h"

#define PI 3.14159265359 
#define INRANGE(x,a,b)    (x >= a && x <= b)
#define getBits( x )    (INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))
#define getByte( x )    (getBits(x[0]) << 4 | getBits(x[1]))

CViewMatrix pViewMatrix;
ID3DXFont* g_font;
ID3DXLine* m_Line;

uintptr_t Tools::FindPattern(std::string moduleName, std::string pattern)
{
	const char* pat = pattern.c_str();
	DWORD firstMatch = 0;
	DWORD rangeStart = (DWORD)GetModuleHandleA(moduleName.c_str());
	MODULEINFO miModInfo;
	GetModuleInformation(GetCurrentProcess(), (HMODULE)rangeStart, &miModInfo, sizeof(MODULEINFO));
	DWORD rangeEnd = rangeStart + miModInfo.SizeOfImage;
	for (DWORD pCur = rangeStart; pCur < rangeEnd; pCur++)
	{
		if (!*pat)
			return firstMatch;

		if (*(PBYTE)pat == '\?' || *(BYTE*)pCur == getByte(pat))
		{
			if (!firstMatch)
				firstMatch = pCur;

			if (!pat[2])
				return firstMatch;

			if (*(PWORD)pat == '\?\?' || *(PBYTE)pat != '\?')
				pat += 3;

			else
				pat += 2; //one ?
		}
		else
		{
			pat = pattern.c_str();
			firstMatch = 0;
		}
	}
	return NULL;
}

void Tools::DrawString(LONG x, LONG y, int r, int g, int b, const char* fmt, ...)
{
	RECT FontPos = { x, y, x + 120, y + 16 };
	char buf[1024] = { '\0' };
	va_list va_alist;

	va_start(va_alist, fmt);
	vsprintf_s(buf, fmt, va_alist);
	va_end(va_alist);

	RECT rect = { x, y, x + 240, y + 25 };
	g_font->DrawText(NULL, buf, -1, &rect, DT_NOCLIP, D3DCOLOR_XRGB(r, g, b));
}

void Tools::DrawLine(float x1, float y1, float x2, float y2, float width, bool antialias, IDirect3DDevice9* pDevice, int R, int G, int B)
{
	D3DXVECTOR2 line[] = { D3DXVECTOR2(x1, y1), D3DXVECTOR2(x2, y2) };
	m_Line->SetWidth(width);
	if (antialias) m_Line->SetAntialias(1);
	m_Line->Draw(line, 2, D3DCOLOR_ARGB(255, R, G, B));
}

void Tools::DrawCircle(int X, int Y, int radius, int numSides, DWORD Color)
{
	D3DXVECTOR2 Line[128];
	float Step = PI * 2.0 / numSides;
	int Count = 0;
	for (float a = 0; a < PI * 2.0; a += Step)
	{
		float X1 = radius * cos(a) + X;
		float Y1 = radius * sin(a) + Y;
		float X2 = radius * cos(a + Step) + X;
		float Y2 = radius * sin(a + Step) + Y;
		Line[Count].x = X1;
		Line[Count].y = Y1;
		Line[Count + 1].x = X2;
		Line[Count + 1].y = Y2;
		Count += 2;
	}
	m_Line->Begin();
	m_Line->SetWidth(2);
	m_Line->Draw(Line, Count, Color);
	m_Line->End();
}

bool Tools::WorldToScreen(Vector pos, Vec2& screen)
{
	D3DXVECTOR4 clipCoords;
	clipCoords.x = pos.x * pViewMatrix.Matrix[0] + pos.y * pViewMatrix.Matrix[1] + pos.z * pViewMatrix.Matrix[2] + pViewMatrix.Matrix[3];
	clipCoords.y = pos.x * pViewMatrix.Matrix[4] + pos.y * pViewMatrix.Matrix[5] + pos.z * pViewMatrix.Matrix[6] + pViewMatrix.Matrix[7];
	clipCoords.z = pos.x * pViewMatrix.Matrix[8] + pos.y * pViewMatrix.Matrix[9] + pos.z * pViewMatrix.Matrix[10] + pViewMatrix.Matrix[11];
	clipCoords.w = pos.x * pViewMatrix.Matrix[12] + pos.y * pViewMatrix.Matrix[13] + pos.z * pViewMatrix.Matrix[14] + pViewMatrix.Matrix[15];

	if (clipCoords.w < 0.1f)
		return false;

	D3DXVECTOR3 NDC;
	NDC.x = clipCoords.x / clipCoords.w;
	NDC.y = clipCoords.y / clipCoords.w;
	/*NDC.z = clipCoords.z / clipCoords.w;*/

	screen.x = (win::windowWidth / 2 * NDC.x) + (NDC.x + win::windowWidth / 2);
	screen.y = -(win::windowHeight / 2 * NDC.y) + (NDC.y + win::windowHeight / 2);
	return true;
}

bool Tools::WorldToScreen_Vec3(Vec3 pos, Vec2& screen)
{
	D3DXVECTOR4 clipCoords;
	clipCoords.x = pos.x * pViewMatrix.Matrix[0] + pos.y * pViewMatrix.Matrix[1] + pos.z * pViewMatrix.Matrix[2] + pViewMatrix.Matrix[3];
	clipCoords.y = pos.x * pViewMatrix.Matrix[4] + pos.y * pViewMatrix.Matrix[5] + pos.z * pViewMatrix.Matrix[6] + pViewMatrix.Matrix[7];
	clipCoords.z = pos.x * pViewMatrix.Matrix[8] + pos.y * pViewMatrix.Matrix[9] + pos.z * pViewMatrix.Matrix[10] + pViewMatrix.Matrix[11];
	clipCoords.w = pos.x * pViewMatrix.Matrix[12] + pos.y * pViewMatrix.Matrix[13] + pos.z * pViewMatrix.Matrix[14] + pViewMatrix.Matrix[15];

	if (clipCoords.w < 0.1f)
		return false;

	D3DXVECTOR3 NDC;
	NDC.x = clipCoords.x / clipCoords.w;
	NDC.y = clipCoords.y / clipCoords.w;
	/*NDC.z = clipCoords.z / clipCoords.w;*/

	screen.x = (win::windowWidth / 2 * NDC.x) + (NDC.x + win::windowWidth / 2);
	screen.y = -(win::windowHeight / 2 * NDC.y) + (NDC.y + win::windowHeight / 2);
	return true;
}

bool Tools::GetBonePosEx(uintptr_t boneBase, int boneID, Vec3& bonePos, Vec2& screen)
{
	bonePos.x = *(float*)((boneBase + 0x30 * boneID + 0x0C));
	bonePos.y = *(float*)((boneBase + 0x30 * boneID + 0x1C));
	bonePos.z = *(float*)((boneBase + 0x30 * boneID + 0x2C));

	D3DXVECTOR4 clipCoords;
	clipCoords.x = bonePos.x * pViewMatrix.Matrix[0] + bonePos.y * pViewMatrix.Matrix[1] + bonePos.z * pViewMatrix.Matrix[2] + pViewMatrix.Matrix[3];
	clipCoords.y = bonePos.x * pViewMatrix.Matrix[4] + bonePos.y * pViewMatrix.Matrix[5] + bonePos.z * pViewMatrix.Matrix[6] + pViewMatrix.Matrix[7];
	clipCoords.z = bonePos.x * pViewMatrix.Matrix[8] + bonePos.y * pViewMatrix.Matrix[9] + bonePos.z * pViewMatrix.Matrix[10] + pViewMatrix.Matrix[11];
	clipCoords.w = bonePos.x * pViewMatrix.Matrix[12] + bonePos.y * pViewMatrix.Matrix[13] + bonePos.z * pViewMatrix.Matrix[14] + pViewMatrix.Matrix[15];

	if (clipCoords.w < 0.1f)
		return false;

	D3DXVECTOR3 NDC;
	NDC.x = clipCoords.x / clipCoords.w;
	NDC.y = clipCoords.y / clipCoords.w;
	NDC.z = clipCoords.z / clipCoords.w;

	screen.x = (win::windowWidth / 2 * NDC.x) + (NDC.x + win::windowWidth / 2);
	screen.y = -(win::windowHeight / 2 * NDC.y) + (NDC.y + win::windowHeight / 2);
	return true;
}