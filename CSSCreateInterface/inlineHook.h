#pragma once
#include "include.h"

namespace inlineHook
{

	DWORD MemoryProtect(DWORD address, DWORD changeProtect)
	{
		DWORD oldProt;
		VirtualProtect((LPVOID)address, sizeof(BYTE[5]), changeProtect, &oldProt);
		return oldProt;
	}

	void Hook(DWORD newfun, DWORD oldfun, DWORD oldCode)
	{
		BYTE JmpCode[5];
		JmpCode[0] = 0xE9;//JMP指令
		*(DWORD*)(&JmpCode[1]) = newfun - oldfun - 5;//儲存跳轉地址.
		auto oldProtect = MemoryProtect(oldfun, PAGE_EXECUTE_READWRITE);//設定函數入口點的記憶體保護區塊屬性.
		memcpy((void*)oldCode, (LPVOID)oldfun, 5);//保留函數入口點的前五個Byte.
		memcpy((void*)oldfun, JmpCode, 5);//修改函數入口點的前五個Byte改為跳轉指令.
		MemoryProtect(oldfun, oldProtect);//還原函數入口點的記憶體保護區塊屬性.
	}

	void UnHook(DWORD oldfun, BYTE* oldCode)
	{
		auto oldProtection = MemoryProtect(oldfun, PAGE_EXECUTE_READWRITE);
		/*for (int i = 0; i <= 4; i++)
		{
			JmpCode[i] = *(BYTE*)(oldfun + i);
		}*/
		for (int i = 0; i <= 4; i++)
		{
			*(BYTE*)(oldfun + i) = oldCode[i];
		}
		/*memcpy((void*)oldfun, oldCode, 5);*/
		MemoryProtect(oldfun, oldProtection);
	}
}
