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
		JmpCode[0] = 0xE9;//JMP���O
		*(DWORD*)(&JmpCode[1]) = newfun - oldfun - 5;//�x�s����a�}.
		auto oldProtect = MemoryProtect(oldfun, PAGE_EXECUTE_READWRITE);//�]�w��ƤJ�f�I���O����O�@�϶��ݩ�.
		memcpy((void*)oldCode, (LPVOID)oldfun, 5);//�O�d��ƤJ�f�I���e����Byte.
		memcpy((void*)oldfun, JmpCode, 5);//�ק��ƤJ�f�I���e����Byte�אּ������O.
		MemoryProtect(oldfun, oldProtect);//�٭��ƤJ�f�I���O����O�@�϶��ݩ�.
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
