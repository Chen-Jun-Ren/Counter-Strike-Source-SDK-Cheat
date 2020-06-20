#pragma once
#include "IHandleEntity.h"
class IClientUnknown : public IHandleEntity
{
public:
	virtual void* GetCollideable() = 0;
	virtual void* GetClientNetworkable() = 0;
	virtual void* GetClientRenderable() = 0;
	virtual void* GetIClientEntity() = 0;
	virtual void* GetBaseEntity() = 0;
	virtual void* GetClientThinkable() = 0;
};