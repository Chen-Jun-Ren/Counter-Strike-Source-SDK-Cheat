#pragma once
#include "IHandleEntity.h"

class IClientNetworkable;
class C_BaseEntity;
class IClientRenderable;
class ICollideable;
class IClientEntity;
class IClientThinkable;

class IClientUnknown : public IHandleEntity
{
public:
	virtual ICollideable* GetCollideable() = 0;
	virtual void* GetClientNetworkable() = 0;
	virtual void* GetClientRenderable() = 0;
	virtual void* GetIClientEntity() = 0;
	virtual void* GetBaseEntity() = 0;
	virtual void* GetClientThinkable() = 0;
};