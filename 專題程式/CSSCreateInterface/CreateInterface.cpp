#include "CreateInterface.h"


CInterface* Interface;
tCreateInterface CreateInterface;

template <typename T>
T* GetInterface(const char* module , const char* name)
{
	CreateInterface = reinterpret_cast<tCreateInterface>(GetProcAddress(GetModuleHandleA(module), "CreateInterface"));
	T* inter = nullptr; 
	inter = (T*)CreateInterface(name, 0);
	return inter;
}

CInterface::CInterface()
{
	ClientEntityList = GetInterface<IClientEntityList>("client.dll", "VClientEntityList003");
	BaseClientDLL = GetInterface<IBaseClientDLL>("client.dll", "VClient017");
	VEngineClient = GetInterface<IVEngineClient013>("engine.dll", "VEngineClient013");
}