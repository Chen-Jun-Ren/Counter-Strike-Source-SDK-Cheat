#pragma once
#include "IMaterial.h"
#include "getvfunc.h"
class IMaterialSystem
{
public:
	IMaterial* CreateMaterial(bool flat, bool ignorez, bool wireframed)
	{

	}
	IMaterial* FindMaterial(char const* pMaterialName, const char* pTextureGroupName, bool complain = true, const char* pComplainPrefix = NULL)
	{
		typedef IMaterial* (__thiscall* OriginalFn)(void*, char const* pMaterialName, const char* pTextureGroupName, bool complain, const char* pComplainPrefix);
		return getvfunc< OriginalFn >(this, 84)(this, pMaterialName, pTextureGroupName, complain, pComplainPrefix);
	}
};