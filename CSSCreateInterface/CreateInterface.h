#pragma once
#include "include.h"
#include "IClientEntityList.h"
#include "cdll_int.h"
#include "IPanel.h"
typedef void* (__cdecl* tCreateInterface)(const char* name, int* pReturnCode);
extern tCreateInterface CreateInterface;

class CInterface
{
public:
	CInterface();
public:
	IClientEntityList* ClientEntityList = nullptr;
	IBaseClientDLL* BaseClientDLL = nullptr;
	IVEngineClient* VEngineClient = nullptr;
	IServerGameDLL* ServerGameDLL = nullptr;
	IPanel* Panel = nullptr;
};

extern CInterface* Interface;