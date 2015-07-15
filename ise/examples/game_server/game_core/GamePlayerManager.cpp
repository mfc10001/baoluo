
#include "GamePlayerManager.h"
#include "../game_define/Protocol.h"
#include "GamePlayer.h"
bool TokenManager::IsExist(uint32 uid)
{
	ToeknManagerMap::iterator it=m_token_manager_.find(uid);
	if(it!=m_token_manager_.end())
	{
		return false;
	}
	return true;
}

void TokenManager::AddToken(uint32 &uid,string &token)
{
	if(!IsExist(uid))
	{
		TokenInfo *ptr=new TokenInfo();
		ptr->uid=uid;
		ptr->token=token;
		ptr->valid_time=Timestamp::now()+TOKEN_MAX_VALID_TIME;
		m_token_manager_[uid]=ptr;
	}
}
void TokenManager::DelToken(uint32 uid )
{

}
uint32 TokenManager::Authentication(uint32 &uid,string &token)
{
	if(IsExist(uid))
	{
		ToeknManagerMap::iterator it=m_token_manager_.find(uid);
		TokenInfo* ptr=(*it).second;
		if(ptr->valid_time>=Timestamp::now())
		{
			if(strcmp(ptr->token.c_str(),token.c_str())==0)
			{
				return ERR_SUCCESS;
			}
			else
			{
				return ERR_TOKEN_TIME;
			}
		}
		return ERR_TOKEN_TIME;
	}
}


void GamePlayerManager::AddPlayer(GamePlayer *player)
{
}
void GamePlayerManager::DelPlayer(uint32 uid)
{
}

void GamePlayerManager::SaveAll()
{
	for(PlayerManagerMap::iterator it=m_player_manager_.end();it!=m_player_manager_.end();it++)
	{
		(*it).second->save();
	}
}

uint32 GamePlayerManager::GetCount()
{
	return m_player_manager_.size();
}

