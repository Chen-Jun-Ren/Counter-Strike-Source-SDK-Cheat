#pragma once
#include "include.h"
#include "Vector.h"
#include "Matrix3x4_t.h"

struct ModelRenderInfo_t
{
	Vector origin;
	QAngle angles;
	void*/*IClientRenderable**/ pRenderable;
	const void* pModel;
	const matrix3x4_t* pModelToWorld;
	const matrix3x4_t* pLightingOffset;
	const Vector* pLightingOrigin;
	int flags;
	int entity_index;
	int skin;
	int body;
	int hitboxset;
	/*ModelInstanceHandle_t instance;*/

	ModelRenderInfo_t()
	{
		pModelToWorld = NULL;
		pLightingOffset = NULL;
		pLightingOrigin = NULL;
	}
};

class IVModelRender
{
public:
	//void ForcedMaterialOverride(IMaterial* mat);
	void DrawModelExecute(const ModelRenderInfo_t& state, const ModelRenderInfo_t& pInfo, matrix3x4_t* pCustomBoneToWorld);
};