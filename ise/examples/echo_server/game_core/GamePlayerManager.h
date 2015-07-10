#ifndef _ISE_PLAYERMANGER_H_
#define _ISE_PLAYERMANGER_H_

#include "GamePlayer.h"
#include "ise/main/ise.h"

const uint16 TOKEN_LEN=48;
const uint16 TOKEN_MAX_VALID_TIME=3600;
struct TokenInfo
{
	TokenInfo(){memset(this,0,sizeof(TokenInfo));}

	uint32 uid;
	char   token[TOKEN_LEN];
	uint32 valid_time;
};


class TokenManager:public Singleton<TokenManager>
{
	public:

		void AddToken(uint32 uid,string token);

		void DelToken(uint32 uid );

		bool IsExist(uint32 uid);

		uint32 Authentication(uint32 uid,string token);
	
	private:
		typedef map<uint32 ,TokenInfo*> ToeknManagerMap;
		ToeknManagerMap m_token_manager_;
		
		friend class Singleton<TokenManager>;
		
};
class GamePlayerManager:public Singleton<GamePlayerManager>
{
	public:
		void AddPlayer(uint32 uid);
		void DelPlayer(uint32 uid);
	private:
		 friend class Singleton<ConfigManager>;

		 typedef map<uint32 ,GamePlayer*> PlayerManagerMap;
		 PlayerManagerMap m_player_manager_;
};

#endif