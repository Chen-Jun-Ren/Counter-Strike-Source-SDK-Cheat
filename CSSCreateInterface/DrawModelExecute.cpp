#include "Hooks.h"
#include "IVModelInfo.h"
#include "IMaterial.h"
DrawModelExecuteFn oDrawModelExecute;

const float* pColor;

float W_Color = 255.0f;
float BK_Color = 0;

void __stdcall Hooks::HookDrawModelExecute(/*const ModelRenderInfo_t &*/void* state, /*const ModelRenderInfo_t&*/void* pInfo, /*matrix3x4_t**/void* pCustomBoneToWorld)
{
	HOOK::DrawModle->UnHook();
	std::cout << HOOK::DrawModle->GetFuncAddress(19) << std::endl;
	HOOK::DrawModle->ReHook();
	//oDrawModelExecute = (DrawModelExecuteFn)HOOK::DrawModle->GetFuncAddress(19);
	//oDrawModelExecute(state, pInfo, pCustomBoneToWorld);
	//HOOK::DrawModle->UnHook();
	//if (pInfo.pModel)
	//{
	//	std::string pszModelName = Interface->ModelInfo->GetModelName((const model_t*)pInfo.pModel);
	//	IMaterial* mats[MAXSTUDIOSKINS];
	//	//studiohdr_t* hdr = Interface->ModelInfo->GetStudioModel((const model_t*)pInfo.pModel);
	//	if (pszModelName.find("models/player"))
	//	{
	//		C_BaseEntity* pModelEntity = (C_BaseEntity*)Interface->ClientEntityList->GetClientEntity(pInfo.entity_index);
	//		if (pModelEntity)
	//		{
	//			C_BaseEntity* LocalPlayer = (C_BaseEntity*)Interface->ClientEntityList->GetClientEntity(1);
	//			if (LocalPlayer)
	//			{
	//				if (pModelEntity->GetHealthValue() >= 1 && pModelEntity->GetTeamNumber() != LocalPlayer->GetTeamNumber())
	//				{
	//					//Interface->ModelInfo->GetModelMaterials((const model_t*)pInfo.pModel, hdr->numtextures, mats);
	//					//for (int i = 0; i < hdr->numtextures; i++)
	//					//{
	//					//	IMaterial* mat = mats[i];
	//					//	if (!mat)
	//					//		continue;
	//					//	// Here we use SetMaterialVarFlag from the IMaterial class (31st index)
	//					//	mat->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);
	//					//	mat->SetMaterialVarFlag(MATERIAL_VAR_FLAT, true);
	//					//	mat->SetMaterialVarFlag(MATERIAL_VAR_ALPHATEST, true);
	//					//	mat->AlphaModulate(1.0f); // don't need this, I just use it just cause.

	//						/*col = gCvars.esp_color2;*/
	//						// Here is your homework. Find the g_pRenderView class
	//					pColor = &W_Color;
	//					Interface->RenderView->SetColorModulation(pColor);
	//					// Call to our original DrawModelExecute (we could juat as easily call oDrawModelExecute).
	//					// We call the original so we can have different colors based on visibility
	//					oDrawModelExecute(state, pInfo, pCustomBoneToWorld);

	//					/*mat->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
	//					mat->SetMaterialVarFlag(MATERIAL_VAR_FLAT, false);
	//					mat->SetMaterialVarFlag(MATERIAL_VAR_ALPHATEST, false);
	//					mat->AlphaModulate(1.0f);*/

	//					pColor = &BK_Color;
	//					/*col2 = gCvars.esp_color;*/
	//					Interface->RenderView->SetColorModulation(pColor);
	//					//}
	//				}
	//				else // The else clause for if the model is not alive or on our team
	//				{   // Basically all this does is do what DrawModelExecute normally does to draw our regular legit models.
	//					/*Interface->ModelInfo->GetModelMaterials((const model_t*)pInfo.pModel, hdr->numtextures, mats);
	//					for (int i = 0; i < hdr->numtextures; i++)
	//					{
	//						IMaterial* mat = mats[i];
	//						if (!mat)
	//							continue;

	//						mat->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
	//						mat->SetMaterialVarFlag(MATERIAL_VAR_ALPHATEST, false);
	//						mat->SetMaterialVarFlag(MATERIAL_VAR_FLAT, false);

	//					}*/
	//					oDrawModelExecute(state, pInfo, pCustomBoneToWorld);
	//				}
	//			}
	//		}
	//	}
	//}
	//HOOK::DrawModle->ReHook();
	//oDrawModelExecute(ctx, state, pInfo, pCustomBoneToWorld);
}