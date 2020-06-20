#pragma once
#include "include.h"
#include <WinBase.h>
class VMTHook 
{
public:
	VMTHook()
	{
		ZeroMemory(this, sizeof(VMTHook));
	}

	VMTHook(uintptr_t** ppClassBase)
	{
		Initialize(ppClassBase);
	}

	void Initialize(uintptr_t** ppClassBase)
	{
		ClassBase = ppClassBase;
		oldVMT = *ppClassBase;
		VMTsize = GetVMTcount(*ppClassBase);
		newVMT = new uintptr_t[VMTsize];
		memcpy(newVMT, oldVMT, sizeof(uintptr_t) * VMTsize);
		*ppClassBase = newVMT;
	}

	~VMTHook()
	{
		if (ClassBase)
		{
			*ClassBase = oldVMT;
		}
	}

	void UnHook()
	{
		if (ClassBase)
		{
			*ClassBase = oldVMT;
		}
	}

	void ReHook()
	{
		if (ClassBase)
		{
			*ClassBase = newVMT;
		}
	}

	int GetFuncCount()
	{
		return VMTsize;
	}

	uintptr_t GetFuncAddress(int Index)
	{
		if (Index >= 0 && Index <= VMTsize && oldVMT != NULL)
		{
			return oldVMT[Index];
		}
		return NULL;
	}

	uintptr_t* GetOldVT()
	{
		return oldVMT;
	}

	uintptr_t HookFunction(DWORD dwNewFunc, unsigned int iIndex)
	{
		if (newVMT && oldVMT && iIndex <= (unsigned int)VMTsize && iIndex >= 0)
		{
			newVMT[iIndex] = dwNewFunc;
			return oldVMT[iIndex];
		}

		return NULL;
	}

private:

	int GetVMTcount(uintptr_t* ppClassBase)
	{
		int Index = 0;

		while (!IsBadCodePtr((FARPROC)ppClassBase[Index]))
		{
			Index++;
		}
		return Index;
	}

	uintptr_t** ClassBase;
	uintptr_t* oldVMT;
	uintptr_t* newVMT;
	int VMTsize;

};