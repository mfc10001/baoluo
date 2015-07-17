#ifndef _ISE_PLAYERMANGER_H_
#define _ISE_PLAYERMANGER_H_


#include "ise/main/ise.h"

class GamePlayer;
const uint16 TOKEN_LEN=48;
const uint32 TOKEN_MAX_VALID_TIME=600000;

struct TokenInfo
{
	TokenInfo(){memset(this,0,sizeof(TokenInfo));}
    uint32 aid;
	uint32 uid;
	//string token;
    char token[TOKEN_LEN];
	Timestamp valid_time;
};


class TokenManager:public Singleton<TokenManager>
{
	public:

		void AddToken(uint32 aid,string token);

		void DelToken(uint32 aid );

		bool IsExist(uint32 aid);

		uint32 Authentication(uint32 &aid,string &token);

	private:
		typedef map<uint32 ,TokenInfo*> ToeknManagerMap;
		ToeknManagerMap m_token_manager_;

		friend class Singleton<TokenManager>;

};
class GamePlayerManager:public Singleton<GamePlayerManager>
{
	public:
		bool AddPlayer(GamePlayer *player);
		void DelPlayer(uint32 uid);

		void SaveAll();

		uint32 GetCount();

		GamePlayer *getPlayer(uint32 uid);

	private:
		 friend class Singleton<GamePlayerManager>;

		 typedef map<uint32 ,GamePlayer*> PlayerManagerMap;
		 PlayerManagerMap m_player_manager_;
};

#endif
