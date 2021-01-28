#pragma once
#include "include.h"
#include "IClientEntityList.h"
#include "cdll_int.h"
#include "IPanel.h"
#include "ivmodelrender.h"
#include "IVModelInfo.h"
#include "IRenderView.h"
#include "IVModelInfo.h"
#include "ISurface.h"
#include "IMaterialSystem.h"
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
	IVModelRender* ModelRender = nullptr;
	IVRenderView* RenderView = nullptr;
	IVModelInfo* ModelInfo = nullptr;
	IMaterialSystem* MaterialSystem = nullptr;
	ISurface* Surface = nullptr;
};

extern CInterface* Interface;