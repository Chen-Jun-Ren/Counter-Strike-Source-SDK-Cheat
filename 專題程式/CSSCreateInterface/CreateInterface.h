#pragma once
#include "include.h"
#include "IClientEntityList.h"
#include "cdll_int.h"
typedef void* (__cdecl* tCreateInterface)(const char* name, int* pReturnCode);
extern tCreateInterface CreateInterface;

class CInterface
{
public:
	CInterface();
public:
	IClientEntityList* ClientEntityList = nullptr;
	IBaseClientDLL* BaseClientDLL = nullptr;
	IVEngineClient013* VEngineClient = nullptr;
};
extern CInterface* Interface;