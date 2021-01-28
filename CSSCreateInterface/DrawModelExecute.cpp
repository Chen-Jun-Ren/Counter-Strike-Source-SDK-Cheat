#include "Hooks.h"
#include "IVModelInfo.h"
#include "IMaterial.h"
#define charenc( s ) ( s )
#define TEXTURE_GROUP_MODEL							"Model textures"
DrawModelExecuteFn oDrawModelExecute;

const float* pColor;

float W_Color = 255.0f;
float BK_Color = 0;

//void ForceMaterial(IMaterial* material, Color color)
//{
//	if (material != NULL)
//	{
//		Interface->RenderView->SetColorModulation(color.Base());
//		Interface->ModelRender->ForcedMaterialOverride(material);
//	}
//}

void __stdcall Hooks::HookDrawModelExecute(void* state, const ModelRenderInfo_t& pInfo, matrix3x4_t* pCustomBoneToWorld)
{
	//if (pInfo.pModel)
	//{
	//	std::string pszModelName = Interface->ModelInfo->GetModelName((const model_t*)pInfo.pModel);
	//	IMaterial* mats[MAXSTUDIOSKINS];
	//	studiohdr_t* hdr = (studiohdr_t*)Interface->ModelInfo->GetStudioModel(Interface->ModelInfo, (/*const model_t**/int)pInfo.pModel);//index 28
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
	//					Interface->ModelInfo->GetModelMaterials(Interface->ModelInfo, (const model_t*)pInfo.pModel, hdr->numtextures, mats);
	//					for (int i = 0; i < hdr->numtextures; i++)
	//					{
	//						IMaterial* mat = mats[i];
	//						if (!mat)
	//							continue;
	//						// Here we use SetMaterialVarFlag from the IMaterial class (31st index)
	//						mat->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);
	//						mat->SetMaterialVarFlag(MATERIAL_VAR_FLAT, true);
	//						mat->SetMaterialVarFlag(MATERIAL_VAR_ALPHATEST, true);
	//						mat->AlphaModulate(1.0f); // don't need this, I just use it just cause.
	//						float colorInvis[3] = { 0.74f, 0.205f, 0.205f };
	//						mat->ColorModulate(colorInvis[0], colorInvis[1], colorInvis[2]);





	//							/*col = gCvars.esp_color2;*/
	//							// Here is your homework. Find the g_pRenderView class
	//						pColor = &W_Color;
	//						Interface->RenderView->SetColorModulation(pColor);
	//						// Call to our original DrawModelExecute (we could juat as easily call oDrawModelExecute).
	//						// We call the original so we can have different colors based on visibility
	//						oDrawModelExecute(Interface->ModelRender, state, pInfo, pCustomBoneToWorld);//index 16

	//						mat->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
	//						mat->SetMaterialVarFlag(MATERIAL_VAR_FLAT, false);
	//						mat->SetMaterialVarFlag(MATERIAL_VAR_ALPHATEST, false);
	//						mat->AlphaModulate(1.0f);

	//						pColor = &BK_Color;
	//						/*col2 = gCvars.esp_color;*/
	//						Interface->RenderView->SetColorModulation(pColor);
	//					}
	//				}
	//				else // The else clause for if the model is not alive or on our team
	//				{   // Basically all this does is do what DrawModelExecute normally does to draw our regular legit models.
	//					Interface->ModelInfo->GetModelMaterials(Interface->ModelRender,(const model_t*)pInfo.pModel, hdr->numtextures, mats);
	//					for (int i = 0; i < hdr->numtextures; i++)
	//					{
	//						IMaterial* mat = mats[i];
	//						if (!mat)
	//							continue;

	//						mat->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
	//						mat->SetMaterialVarFlag(MATERIAL_VAR_ALPHATEST, false);
	//						mat->SetMaterialVarFlag(MATERIAL_VAR_FLAT, false);
	//						float colorInvis[3] = { 0.74f, 0.205f, 0.205f };
	//						mat->ColorModulate(colorInvis[0], colorInvis[1], colorInvis[2]);

	//					}
	//					oDrawModelExecute(Interface->ModelRender, state, pInfo, pCustomBoneToWorld);
	//				}
	//			}
	//		}
	//	}
	//}
	////HOOK::DrawModle->ReHook();


	//if (pInfo.pModel)
	//{
	//	// The name of the model that is currently being rendered
	//	const char* modelName = Interface->ModelInfo->GetModelName((const model_t*)pInfo.pModel);

	//	// Check if a player model is being rendered
	//	if (strstr(modelName, "models/player"))
	//	{
	//		// Get the Entity pointer of the player that is being rendered
	//		// Forgot to mention you need ClientEntityList interface. If you don't have it you're a bad person since you didn't do the CreateInterface tutorial
	//		//Ent* modelEnt = (Ent*)interfaces::ClientEntityList->GetClientEntity(pInfo.entity_index);
	//		C_BaseEntity* modelEnt = (C_BaseEntity*)Interface->ClientEntityList->GetClientEntity(pInfo.entity_index);

	//		// Validity check (not dormant, alive, etc...)
	//		if (!(modelEnt->GetHealthValue() >= 1))
	//		{
	//			oDrawModelExecute(Interface->ModelRender, state, pInfo, pCustomBoneToWorld);
	//			return;
	//		}

	//		// Get the materials that we want to override this model with
	//		IMaterial* matInvis = Interface->MaterialSystem->FindMaterial("debug/debugambientcube", charenc(TEXTURE_GROUP_MODEL));
	//		IMaterial* matVis = Interface->MaterialSystem->FindMaterial("debug/debugambientcube", charenc(TEXTURE_GROUP_MODEL));

	//		// Draw material that will be visible through walls
	//		if (matInvis)
	//		{
	//			// This flag tells the game to draw the model even if it's behind a wall
	//			matInvis->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);

	//			// Change the color of our Material (doesn't necessarily work on all materials)
	//			float colorInvis[3] = { 0.74f, 0.205f, 0.205f };
	//			matInvis->ColorModulate(colorInvis[0], colorInvis[1], colorInvis[2]);
	//			// Set alpha value
	//			matInvis->AlphaModulate(1.f);

	//			// Override the material with ours
	//			Interface->ModelRender->ForcedMaterialOverride(matInvis);
	//			// By calling the original function here, we can have different materials for the non-visible and visible part of the model
	//			oDrawModelExecute(Interface->ModelRender, state, pInfo, pCustomBoneToWorld);
	//		}

	//		// Draw material for the part of the player model that is visible
	//		if (matVis)
	//		{
	//			// Don't let the material display through walls
	//			matVis->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
	//			float colVis[3] = { 0.205f, 0.74f, 0.205f };
	//			matVis->ColorModulate(colVis[0], colVis[1], colVis[2]);

	//			//matVis->AlphaModulate(settings::colors::visibleChams.w);

	//			Interface->ModelRender->ForcedMaterialOverride(matVis);
	//			// Draw our visible material "on top" of our previous material
	//			oDrawModelExecute(Interface->ModelRender, state, pInfo, pCustomBoneToWorld);
	//		}

	//		// Reset state
	//		Interface->ModelRender->ForcedMaterialOverride(nullptr);
	//	}
	//}


	return oDrawModelExecute(Interface->ModelRender,state, pInfo, pCustomBoneToWorld);
}