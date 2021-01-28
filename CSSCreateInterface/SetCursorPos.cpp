#include"Hooks.h"

BOOL WINAPI Hooks::HookSetCursorPos(int X, int Y)
{
	return true;
}