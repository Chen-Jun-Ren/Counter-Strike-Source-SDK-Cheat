#include "CreateInterface.h"


CInterface* Interface;
tCreateInterface CreateInterface;

template <typename T>
T* GetInterface(const char* module , const char* name)
{
	CreateInterface = reinterpret_cast<tCreateInterface>(GetProcAddress(GetModuleHandleA(module), "CreateInterface"));
	/*T* inter = nullptr; 
	inter = (T*)CreateInterface(name, 0);
	return inter;*/
	return (T*)CreateInterface(name, 0);
}

CInterface::CInterface()
{
	Panel = GetInterface<IPanel>("vgui2.dll", "VGUI_Panel009");
	ClientEntityList = GetInterface<IClientEntityList>("client.dll", "VClientEntityList003");
	BaseClientDLL = GetInterface<IBaseClientDLL>("client.dll", "VClient017");
	VEngineClient = GetInterface<IVEngineClient>("engine.dll", "VEngineClient013");
	ServerGameDLL = GetInterface<IServerGameDLL>("server.dll","ServerGameDLL010");
	ModelRender = GetInterface<IVModelRender>("engine.dll", "VEngineModel016");
	RenderView = GetInterface<IVRenderView>("engine.dll", "VEngineRenderView014");
	ModelInfo = GetInterface<IVModelInfo>("engine.dll", "VModelInfoClient006");
}

// global declarations
LPDIRECT3D9 d3d;    // the pointer to our Direct3D interface
LPDIRECT3DDEVICE9 d3ddev;    // the pointer to the device class

void initD3D(HWND hWnd)
{
	d3d = Direct3DCreate9(D3D_SDK_VERSION);    // create the Direct3D interface

	D3DPRESENT_PARAMETERS d3dpp;    // create a struct to hold various device information

	ZeroMemory(&d3dpp, sizeof(d3dpp));    // clear out the struct for use
	d3dpp.Windowed = TRUE;    // program windowed, not fullscreen
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;    // discard old frames
	d3dpp.hDeviceWindow = hWnd;    // set the window to be used by Direct3D


	// create a device class using this information and the info from the d3dpp stuct
	d3d->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddev);
}