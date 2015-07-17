
#include "GamePlayerManager.h"
#include "../game_define/Protocol.h"
#include "GamePlayer.h"
bool TokenManager::IsExist(uint32 aid)
{
	ToeknManagerMap::iterator it=m_token_manager_.find(aid);
	if(it!=m_token_manager_.end())
	{
		return true;
	}
	return false;
}

void TokenManager::AddToken(uint32 aid,string token)
{
	if(!IsExist(aid))
	{
		TokenInfo *ptr=new TokenInfo();
		ptr->aid=aid;
		//ptr.token=token;

		memcpy(ptr->token,token.c_str(),token.length());
		ptr->valid_time=Timestamp::now()+TOKEN_MAX_VALID_TIME;
		m_token_manager_[aid]=ptr;
	}
}
void TokenManager::DelToken(uint32 aid )
{

}
uint32 TokenManager::Authentication(uint32 &aid,string &token)
{
	if(IsExist(aid))
	{
		ToeknManagerMap::iterator it=m_token_manager_.find(aid);
		TokenInfo* ptr=(*it).second;
        Timestamp temp = ptr->valid_time;
        Timestamp ntime=Timestamp::now();
		if(temp>=ntime)
		{
			if(strcmp(ptr->token,token.c_str())==0)
			{
				return ERR_SUCCESS;
			}
			else
			{
				return ERR_TOKEN_INVALID;
			}
		}
		return ERR_TOKEN_TIME;
	}
	return ERR_TOKEN_NULL;
}


bool  GamePlayerManager::AddPlayer(GamePlayer *player)
{
	PlayerManagerMap::iterator it = m_player_manager_.find(player->getUid());
	if(it!=m_player_manager_.end())
	{
		return false;
	}
	m_player_manager_[player->getUid()]=player;
	return true;
}
void GamePlayerManager::DelPlayer(uint32 uid)
{
	PlayerManagerMap::iterator it = m_player_manager_.find(uid);
	if(it!=m_player_manager_.end())
	{
		delete (*it).second;
		(*it).second=NULL;
		m_player_manager_.erase(it);
	}
}
GamePlayer *GamePlayerManager::getPlayer(uint32 uid)
{
	PlayerManagerMap::iterator it = m_player_manager_.find(uid);
	if(it==m_player_manager_.end())
	{
		return NULL;
	}
	return (*it).second;
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

