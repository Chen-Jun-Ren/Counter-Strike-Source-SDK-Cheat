#pragma once
#include "client_server_class.h"

#define MAX_PLAYER_NAME_LENGTH		32
#define MAX_CUSTOM_FILES			4	
#define SIGNED_GUID_LEN				32

class IBaseClientDLL
{
public:
	virtual void			Whatever_fun_0() = 0;
	virtual void			Whatever_fun_1() = 0;
	virtual void			Whatever_fun_2() = 0;
	virtual void			Whatever_fun_3() = 0;
	virtual void			Whatever_fun_4() = 0;
	virtual void			Whatever_fun_5() = 0;
	virtual void			Whatever_fun_6() = 0;
	virtual void			Whatever_fun_7() = 0;
	virtual ClientClass* GetAllClasses(void) = 0;
};

typedef struct player_info_s
{
	//DECLARE_BYTESWAP_DATADESC();
	// scoreboard information
	char			name[MAX_PLAYER_NAME_LENGTH];
	// local server user ID, unique while server is running
	int				userID;
	// global unique player identifer
	char			guid[SIGNED_GUID_LEN + 1];
	// friends identification number
	void* friendsID;
	// friends name
	char			friendsName[MAX_PLAYER_NAME_LENGTH];
	// true, if player is a bot controlled by game.dll
	bool			fakeplayer;
	// true if player is the HLTV proxy
	bool			ishltv;
#if defined( REPLAY_ENABLED )
	// true if player is the Replay proxy
	bool			isreplay;
#endif
	// custom files CRC for this player
	void* customFiles[MAX_CUSTOM_FILES];
	// this counter increases each time the server downloaded a new file
	unsigned char	filesDownloaded;
} player_info_t;

class IVEngineClient
{
public:
	virtual void			Whatever_fun_0() = 0;
	virtual void			Whatever_fun_1() = 0;
	virtual void			Whatever_fun_2() = 0;
	virtual void			Whatever_fun_3() = 0;
	virtual void			Whatever_fun_4() = 0;
	virtual void			Whatever_fun_5() = 0;
	virtual void			Whatever_fun_6() = 0;
	virtual void			Whatever_fun_7() = 0;
	// Fill in the player info structure for the specified player index (name, model, etc.)
	virtual bool				GetPlayerInfo(int ent_num, player_info_t* pinfo) = 0;
};

class IServerGameDLL
{
public:
	virtual void			Whatever_fun_0() = 0;
	virtual void			DLLShutdown(void) = 0;
	// Get the simulation interval (must be compiled with identical values into both client and game .dll for MOD!!!)
	virtual void			Whatever_fun_1() = 0;
	virtual float			GetTickInterval(void) const = 0;
	virtual bool			GameInit(void) = 0;
	virtual void			GameShutdown(void) = 0;
	virtual bool			LevelInit(const char* pMapName, char const* pMapEntities, char const* pOldLevel, char const* pLandmarkName, bool loadGame, bool background) = 0;
	virtual void			Whatever_fun_2() = 0;
	virtual void			LevelShutdown(void) = 0;
	virtual void			GameFrame(bool simulating) = 0; // could be called multiple times before sending data to clients
	virtual void			PreClientUpdate(bool simulating) = 0; // called after all GameFrame() calls, before sending data to clients

	virtual ServerClass* GetAllServerClasses(void) = 0;
};
