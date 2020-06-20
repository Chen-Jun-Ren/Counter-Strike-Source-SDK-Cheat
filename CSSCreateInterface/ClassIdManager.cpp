#include "client_server_class.h"
#include "ClassIdManager.h"
#include "CreateInterface.h"

ClassIdManager* ClassId;
ClassIdManager* AimClassId;

inline int ClassIdManager::GetClassID(const char* classname)
{
	ServerClass* serverclass = Interface->ServerGameDLL->GetAllServerClasses();
	
	for (serverclass; serverclass; serverclass = serverclass->m_pNext)
	{
		if (!strcmp(serverclass->m_pNetworkName, classname))//strcmp相同時還傳0
		{
			return serverclass->m_ClassID;
		}
	}
	return -1;
	//int id = 0;
	//ServerClass* serverclass = Interface->ServerGameDLL->GetAllServerClasses();
	//while (serverclass)
	//{
	//	if (!strcmp(serverclass->m_pNetworkName, classname))//strcmp相同時還傳0
	//		return id;
	//	serverclass = serverclass->m_pNext, id++;
	//}
	//return -1;
}

ClassIdManager::ClassIdManager()
{
	CAI_BaseNPC = GetClassID("CAI_BaseNPC");
	CAK47 = GetClassID("CAK47");
	CBaseAnimating = GetClassID("CBaseAnimating");
	CBaseAnimatingOverlay = GetClassID("CBaseAnimatingOverlay");
	CBaseAttributableItem = GetClassID("CBaseAttributableItem");
	CBaseButton = GetClassID("CBaseButton");
	CBaseCombatCharacter = GetClassID("CBaseCombatCharacter");
	CBaseCombatWeapon = GetClassID("CBaseCombatWeapon");
	CBaseCSGrenade = GetClassID("CBaseCSGrenade");
	CBaseCSGrenadeProjectile = GetClassID("CBaseCSGrenadeProjectile");
	CBaseDoor = GetClassID("CBaseDoor");
	CBaseEntity = GetClassID("CBaseEntity");
	CBaseFlex = GetClassID("CBaseFlex");
	CBaseGrenade = GetClassID("CBaseGrenade");
	CBaseParticleEntity = GetClassID("CBaseParticleEntity");
	CBasePlayer = GetClassID("CBasePlayer");
	CBasePropDoor = GetClassID("CBasePropDoor");
	CBaseTeamObjectiveResource = GetClassID("CBaseTeamObjectiveResource");
	CBaseTempEntity = GetClassID("CBaseTempEntity");
	CBaseToggle = GetClassID("CBaseToggle");
	CBaseTrigger = GetClassID("CBaseTrigger");
	CBaseViewModel = GetClassID("CBaseViewModel");
	CBaseVPhysicsTrigger = GetClassID("CBaseVPhysicsTrigger");
	CBaseWeaponWorldModel = GetClassID("CBaseWeaponWorldModel");
	CBeam = GetClassID("CBeam");
	CBeamSpotlight = GetClassID("CBeamSpotlight");
	CBoneFollower = GetClassID("CBoneFollower");
	CBRC4Target = GetClassID("CBRC4Target");
	CBreachCharge = GetClassID("CBreachCharge");
	CBreachChargeProjectile = GetClassID("CBreachChargeProjectile");
	CBreakableProp = GetClassID("CBreakableProp");
	CBreakableSurface = GetClassID("CBreakableSurface");
	CC4 = GetClassID("CC4");
	CCascadeLight = GetClassID("CCascadeLight");
	CChicken = GetClassID("CChicken");
	CColorCorrection = GetClassID("CColorCorrection");
	CColorCorrectionVolume = GetClassID("CColorCorrectionVolume");
	CCSGameRulesProxy = GetClassID("CCSGameRulesProxy");
	CCSPlayer = GetClassID("CCSPlayer");
	CCSPlayerResource = GetClassID("CCSPlayerResource");
	CCSRagdoll = GetClassID("CCSRagdoll");
	CCSTeam = GetClassID("CCSTeam");
	CDangerZone = GetClassID("CDangerZone");
	CDangerZoneController = GetClassID("CDangerZoneController");
	CDEagle = GetClassID("CDEagle");
	CDecoyGrenade = GetClassID("CDecoyGrenade");
	CDecoyProjectile = GetClassID("CDecoyProjectile");
	CDrone = GetClassID("CDrone");
	CDronegun = GetClassID("CDronegun");
	CDynamicLight = GetClassID("CDynamicLight");
	CDynamicProp = GetClassID("CDynamicProp");
	CEconEntity = GetClassID("CEconEntity");
	CEconWearable = GetClassID("CEconWearable");
	CEmbers = GetClassID("CEmbers");
	CEntityDissolve = GetClassID("CEntityDissolve");
	CEntityFlame = GetClassID("CEntityFlame");
	CEntityFreezing = GetClassID("CEntityFreezing");
	CEntityParticleTrail = GetClassID("CEntityParticleTrail");
	CEnvAmbientLight = GetClassID("CEnvAmbientLight");
	CEnvDetailController = GetClassID("CEnvDetailController");
	CEnvDOFController = GetClassID("CEnvDOFController");
	CEnvGasCanister = GetClassID("CEnvGasCanister");
	CEnvParticleScript = GetClassID("CEnvParticleScript");
	CEnvProjectedTexture = GetClassID("CEnvProjectedTexture");
	CEnvQuadraticBeam = GetClassID("CEnvQuadraticBeam");
	CEnvScreenEffect = GetClassID("CEnvScreenEffect");
	CEnvScreenOverlay = GetClassID("CEnvScreenOverlay");
	CEnvTonemapController = GetClassID("CEnvTonemapController");
	CEnvWind = GetClassID("CEnvWind");
	CFEPlayerDecal = GetClassID("CFEPlayerDecal");
	CFireCrackerBlast = GetClassID("CFireCrackerBlast");
	CFireSmoke = GetClassID("CFireSmoke");
	CFireTrail = GetClassID("CFireTrail");
	CFish = GetClassID("CFish");
	CFists = GetClassID("CFists");
	CFlashbang = GetClassID("CFlashbang");
	CFogController = GetClassID("CFogController");
	CFootstepControl = GetClassID("CFootstepControl");
	CFunc_Dust = GetClassID("CFunc_Dust");
	CFunc_LOD = GetClassID("CFunc_LOD");
	CFuncAreaPortalWindow = GetClassID("CFuncAreaPortalWindow");
	CFuncBrush = GetClassID("CFuncBrush");
	CFuncConveyor = GetClassID("CFuncConveyor");
	CFuncLadder = GetClassID("CFuncLadder");
	CFuncMonitor = GetClassID("CFuncMonitor");
	CFuncMoveLinear = GetClassID("CFuncMoveLinear");
	CFuncOccluder = GetClassID("CFuncOccluder");
	CFuncReflectiveGlass = GetClassID("CFuncReflectiveGlass");
	CFuncRotating = GetClassID("CFuncRotating");
	CFuncSmokeVolume = GetClassID("CFuncSmokeVolume");
	CFuncTrackTrain = GetClassID("CFuncTrackTrain");
	CGameRulesProxy = GetClassID("CGameRulesProxy");
	CGrassBurn = GetClassID("CGrassBurn");
	CHandleTest = GetClassID("CHandleTest");
	CHEGrenade = GetClassID("CHEGrenade");
	CHostage = GetClassID("CHostage");
	CHostageCarriableProp = GetClassID("CHostageCarriableProp");
	CIncendiaryGrenade = GetClassID("CIncendiaryGrenade");
	CInferno = GetClassID("CInferno");
	CInfoLadderDismount = GetClassID("CInfoLadderDismount");
	CInfoMapRegion = GetClassID("CInfoMapRegion");
	CInfoOverlayAccessor = GetClassID("CInfoOverlayAccessor");
	CItem_Healthshot = GetClassID("CItem_Healthshot");
	CItemCash = GetClassID("CItemCash");
	CItemDogtags = GetClassID("CItemDogtags");
	CKnife = GetClassID("CKnife");
	CKnifeGG = GetClassID("CKnifeGG");
	CLightGlow = GetClassID("CLightGlow");
	CMaterialModifyControl = GetClassID("CMaterialModifyControl");
	CMelee = GetClassID("CMelee");
	CMolotovGrenade = GetClassID("CMolotovGrenade");
	CMolotovProjectile = GetClassID("CMolotovProjectile");
	CMovieDisplay = GetClassID("CMovieDisplay");
	CParadropChopper = GetClassID("CParadropChopper");
	CParticleFire = GetClassID("CParticleFire");
	CParticlePerformanceMonitor = GetClassID("CParticlePerformanceMonitor");
	CParticleSystem = GetClassID("CParticleSystem");
	CPhysBox = GetClassID("CPhysBox");
	CPhysBoxMultiplayer = GetClassID("CPhysBoxMultiplayer");
	CPhysicsProp = GetClassID("CPhysicsProp");
	CPhysicsPropMultiplayer = GetClassID("CPhysicsPropMultiplayer");
	CPhysMagnet = GetClassID("CPhysMagnet");
	CPhysPropAmmoBox = GetClassID("CPhysPropAmmoBox");
	CPhysPropLootCrate = GetClassID("CPhysPropLootCrate");
	CPhysPropRadarJammer = GetClassID("CPhysPropRadarJammer");
	CPhysPropWeaponUpgrade = GetClassID("CPhysPropWeaponUpgrade");
	CPlantedC4 = GetClassID("CPlantedC4");
	CPlasma = GetClassID("CPlasma");
	CPlayerResource = GetClassID("CPlayerResource");
	CPointCamera = GetClassID("CPointCamera");
	CPointCommentaryNode = GetClassID("CPointCommentaryNode");
	CPointWorldText = GetClassID("CPointWorldText");
	CPoseController = GetClassID("CPoseController");
	CPostProcessController = GetClassID("CPostProcessController");
	CPrecipitation = GetClassID("CPrecipitation");
	CPrecipitationBlocker = GetClassID("CPrecipitationBlocker");
	CPredictedViewModel = GetClassID("CPredictedViewModel");
	CProp_Hallucination = GetClassID("CProp_Hallucination");
	CPropCounter = GetClassID("CPropCounter");
	CPropDoorRotating = GetClassID("CPropDoorRotating");
	CPropJeep = GetClassID("CPropJeep");
	CPropVehicleDriveable = GetClassID("CPropVehicleDriveable");
	CRagdollManager = GetClassID("CRagdollManager");
	CRagdollProp = GetClassID("CRagdollProp");
	CRagdollPropAttached = GetClassID("CRagdollPropAttached");
	CRopeKeyframe = GetClassID("CRopeKeyframe");
	CSCAR17 = GetClassID("CSCAR17");
	CSceneEntity = GetClassID("CSceneEntity");
	CSensorGrenade = GetClassID("CSensorGrenade");
	CSensorGrenadeProjectile = GetClassID("CSensorGrenadeProjectile");
	CShadowControl = GetClassID("CShadowControl");
	CSlideshowDisplay = GetClassID("CSlideshowDisplay");
	CSmokeGrenade = GetClassID("CSmokeGrenade");
	CSmokeGrenadeProjectile = GetClassID("CSmokeGrenadeProjectile");
	CSmokeStack = GetClassID("CSmokeStack");
	CSnowball = GetClassID("CSnowball");
	CSnowballPile = GetClassID("CSnowballPile");
	CSnowballProjectile = GetClassID("CSnowballProjectile");
	CSpatialEntity = GetClassID("CSpatialEntity");
	CSpotlightEnd = GetClassID("CSpotlightEnd");
	CSprite = GetClassID("CSprite");
	CSpriteOriented = GetClassID("CSpriteOriented");
	CSpriteTrail = GetClassID("CSpriteTrail");
	CStatueProp = GetClassID("CStatueProp");
	CSteamJet = GetClassID("CSteamJet");
	CSun = GetClassID("CSun");
	CSunlightShadowControl = GetClassID("CSunlightShadowControl");
	CSurvivalSpawnChopper = GetClassID("CSurvivalSpawnChopper");
	CTablet = GetClassID("CTablet");
	CTeam = GetClassID("CTeam");
	CTeamplayRoundBasedRulesProxy = GetClassID("CTeamplayRoundBasedRulesProxy");
	CTEArmorRicochet = GetClassID("CTEArmorRicochet");
	CTEBaseBeam = GetClassID("CTEBaseBeam");
	CTEBeamEntPoint = GetClassID("CTEBeamEntPoint");
	CTEBeamEnts = GetClassID("CTEBeamEnts");
	CTEBeamFollow = GetClassID("CTEBeamFollow");
	CTEBeamLaser = GetClassID("CTEBeamLaser");
	CTEBeamPoints = GetClassID("CTEBeamPoints");
	CTEBeamRing = GetClassID("CTEBeamRing");
	CTEBeamRingPoint = GetClassID("CTEBeamRingPoint");
	CTEBeamSpline = GetClassID("CTEBeamSpline");
	CTEBloodSprite = GetClassID("CTEBloodSprite");
	CTEBloodStream = GetClassID("CTEBloodStream");
	CTEBreakModel = GetClassID("CTEBreakModel");
	CTEBSPDecal = GetClassID("CTEBSPDecal");
	CTEBubbles = GetClassID("CTEBubbles");
	CTEBubbleTrail = GetClassID("CTEBubbleTrail");
	CTEClientProjectile = GetClassID("CTEClientProjectile");
	CTEDecal = GetClassID("CTEDecal");
	CTEDust = GetClassID("CTEDust");
	CTEDynamicLight = GetClassID("CTEDynamicLight");
	CTEEffectDispatch = GetClassID("CTEEffectDispatch");
	CTEEnergySplash = GetClassID("CTEEnergySplash");
	CTEExplosion = GetClassID("CTEExplosion");
	CTEFireBullets = GetClassID("CTEFireBullets");
	CTEFizz = GetClassID("CTEFizz");
	CTEFootprintDecal = GetClassID("CTEFootprintDecal");
	CTEFoundryHelpers = GetClassID("CTEFoundryHelpers");
	CTEGaussExplosion = GetClassID("CTEGaussExplosion");
	CTEGlowSprite = GetClassID("CTEGlowSprite");
	CTEImpact = GetClassID("CTEImpact");
	CTEKillPlayerAttachments = GetClassID("CTEKillPlayerAttachments");
	CTELargeFunnel = GetClassID("CTELargeFunnel");
	CTEMetalSparks = GetClassID("CTEMetalSparks");
	CTEMuzzleFlash = GetClassID("CTEMuzzleFlash");
	CTEParticleSystem = GetClassID("CTEParticleSystem");
	CTEPhysicsProp = GetClassID("CTEPhysicsProp");
	CTEPlantBomb = GetClassID("CTEPlantBomb");
	CTEPlayerAnimEvent = GetClassID("CTEPlayerAnimEvent");
	CTEPlayerDecal = GetClassID("CTEPlayerDecal");
	CTEProjectedDecal = GetClassID("CTEProjectedDecal");
	CTERadioIcon = GetClassID("CTERadioIcon");
	CTEShatterSurface = GetClassID("CTEShatterSurface");
	CTEShowLine = GetClassID("CTEShowLine");
	CTesla = GetClassID("CTesla");
	CTESmoke = GetClassID("CTESmoke");
	CTESparks = GetClassID("CTESparks");
	CTESprite = GetClassID("CTESprite");
	CTESpriteSpray = GetClassID("CTESpriteSpray");
	CTest_ProxyToggle_Networkable = GetClassID("CTest_ProxyToggle_Networkable");
	CTestTraceline = GetClassID("CTestTraceline");
	CTEWorldDecal = GetClassID("CTEWorldDecal");
	CTriggerPlayerMovement = GetClassID("CTriggerPlayerMovement");
	CTriggerSoundOperator = GetClassID("CTriggerSoundOperator");
	CVGuiScreen = GetClassID("CVGuiScreen");
	CVoteController = GetClassID("CVoteController");
	CWaterBullet = GetClassID("CWaterBullet");
	CWaterLODControl = GetClassID("CWaterLODControl");
	CWeaponAug = GetClassID("CWeaponAug");
	CWeaponAWP = GetClassID("CWeaponAWP");
	CWeaponBaseItem = GetClassID("CWeaponBaseItem");
	CWeaponBizon = GetClassID("CWeaponBizon");
	CWeaponCSBase = GetClassID("CWeaponCSBase");
	CWeaponCSBaseGun = GetClassID("CWeaponCSBaseGun");
	CWeaponCycler = GetClassID("CWeaponCycler");
	CWeaponElite = GetClassID("CWeaponElite");
	CWeaponFamas = GetClassID("CWeaponFamas");
	CWeaponFiveSeven = GetClassID("CWeaponFiveSeven");
	CWeaponG3SG1 = GetClassID("CWeaponG3SG1");
	CWeaponGalil = GetClassID("CWeaponGalil");
	CWeaponGalilAR = GetClassID("CWeaponGalilAR");
	CWeaponGlock = GetClassID("CWeaponGlock");
	CWeaponHKP2000 = GetClassID("CWeaponHKP2000");
	CWeaponM249 = GetClassID("CWeaponM249");
	CWeaponM3 = GetClassID("CWeaponM3");
	CWeaponM4A1 = GetClassID("CWeaponM4A1");
	CWeaponMAC10 = GetClassID("CWeaponMAC10");
	CWeaponMag7 = GetClassID("CWeaponMag7");
	CWeaponMP5Navy = GetClassID("CWeaponMP5Navy");
	CWeaponMP7 = GetClassID("CWeaponMP7");
	CWeaponMP9 = GetClassID("CWeaponMP9");
	CWeaponNegev = GetClassID("CWeaponNegev");
	CWeaponNOVA = GetClassID("CWeaponNOVA");
	CWeaponP228 = GetClassID("CWeaponP228");
	CWeaponP250 = GetClassID("CWeaponP250");
	CWeaponP90 = GetClassID("CWeaponP90");
	CWeaponSawedoff = GetClassID("CWeaponSawedoff");
	CWeaponSCAR20 = GetClassID("CWeaponSCAR20");
	CWeaponScout = GetClassID("CWeaponScout");
	CWeaponSG550 = GetClassID("CWeaponSG550");
	CWeaponSG552 = GetClassID("CWeaponSG552");
	CWeaponSG556 = GetClassID("CWeaponSG556");
	CWeaponSSG08 = GetClassID("CWeaponSSG08");
	CWeaponTaser = GetClassID("CWeaponTaser");
	CWeaponTec9 = GetClassID("CWeaponTec9");
	CWeaponTMP = GetClassID("CWeaponTMP");
	CWeaponUMP45 = GetClassID("CWeaponUMP45");
	CWeaponUSP = GetClassID("CWeaponUSP");
	CWeaponXM1014 = GetClassID("CWeaponXM1014");
	CWorld = GetClassID("CWorld");
	CWorldVguiText = GetClassID("CWorldVguiText");
	DustTrail = GetClassID("DustTrail");
	MovieExplosion = GetClassID("MovieExplosion");
	ParticleSmokeGrenade = GetClassID("ParticleSmokeGrenade");
	RocketTrail = GetClassID("RocketTrail");
	SmokeTrail = GetClassID("SmokeTrail");
	SporeExplosion = GetClassID("SporeExplosion");
	SporeTrail = GetClassID("SporeTrail");
}