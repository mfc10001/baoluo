#include "GameFbManager.h"

bool GameFbDataManager::IsFbPass(const uint32 &fbidx)
{
	FbDataMap::iterator it = m_fbdata.find(fbidx);
	if(it == m_fbdata.end())
	{
		  return false;   
	}

	return (*it).second.ispass;	
}


void GameFbDataManager::AddFbdata(PlayerFbData fbdata)
{
	if(!isHaveFbData())
	{
		m_fbdata.insert(std::make_pair(fbdata.fb_idx,fbdata));
	}
}
void GameFbDataManager::AddFbdata(uint32 fbidx,uint8 fbtype,uint32 times = 0)
{
	PlayerFbData fbdata;
	fbdata.fb_idx=fbidx;
	fbdata.fb_type=fbtype;
	AddFbdata(fbdata);
}
bool GameFbDataManager::isHaveFbData(const uint32 &fbidx)
{
	  FbDataMap::iterator it = m_fbdata.find(fbidx);
	  if(it == m_fbdata.end())
	  {
			return false;	
	  }
	  return true;
}


