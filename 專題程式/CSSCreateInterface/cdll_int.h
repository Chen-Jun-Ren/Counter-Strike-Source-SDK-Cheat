#pragma once
#include "client_class.h"

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
	void*			friendsID;
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
	void*		customFiles[MAX_CUSTOM_FILES];
	// this counter increases each time the server downloaded a new file
	unsigned char	filesDownloaded;
} player_info_t;

class IVEngineClient013
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