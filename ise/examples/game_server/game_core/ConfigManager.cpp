#include "ConfigManager.h"
#include "../tools/CommonTools.h"
#include "../game_define/BaseType.h"
#include "../game_define/Protocol.h"
#include "GamePlayer.h"

bool ConfigManager::loadAllFile()
{
	 loadLevelFile();
	 loadPLayerFile();

     return true;
}

bool ConfigManager::loadLevelFile()
{
	string path=CONFIG_ROOT_PATH;
	path.append("exp.txt");

	FILE * fp=fopen(path.c_str(),"r");
 	if(!fp)
 	{
		return false;
	}

	char buffer[BUFFLEN];
    uint32 expline=3;
	 while(!feof(fp))
	 {
	 	memset(buffer,0,BUFFLEN);
		fgets(buffer,BUFFLEN,fp);
		if(expline!=0)
		{
            expline--;
            continue;
		}
		StrContaonType conVec;
		CommonTools::split(buffer,"\t",conVec);
		if(!conVec.empty()&&conVec.size()!=3)
		{
			return false;
		}
		{
			LevelDataEntry *data=new LevelDataEntry();

			data->id= atoi( conVec[0].c_str());
			data->level=atoi(conVec[1].c_str());
			data->exp=atoi(conVec[2].c_str());
			configLevelManager[data->getIndex()]=data;
		}
	 }
	 fclose(fp);
	 return true;
}

bool ConfigManager::loadPLayerFile()
{
	string path=CONFIG_ROOT_PATH;
	path.append("attr.txt");

	FILE * fp=fopen(path.c_str(),"r");
 	if(!fp)
 	{
		return false;
	}

	char buffer[BUFFLEN];
    uint32 expline=3;
	 while(!feof(fp))
	 {
	 	memset(buffer,0,BUFFLEN);
		fgets(buffer,BUFFLEN,fp);
		if(expline!=0)
		{
            expline--;
            continue;
		}
		StrContaonType conVec;
		CommonTools::split(buffer,"\t",conVec);
		if(!conVec.empty()&&conVec.size()!=19)
		{
			return false;
		}
		{
			PlayerDataEntry *data=new PlayerDataEntry();
            data->id= atoi(conVec[ 0 ].c_str());
            data->physicsAttack= atoi(conVec[ 1 ].c_str());
            data->magicAttack= atoi(conVec[ 2 ].c_str());
            data->barmor= atoi(conVec[ 3 ].c_str());
            data->bresistance= atoi(conVec[ 4 ].c_str());
            data->hp= atoi(conVec[ 5 ].c_str());
            data->hit= atoi(conVec[ 6 ].c_str());
            data->dodge= atoi(conVec[ 7 ].c_str());
            data->crit= atoi(conVec[ 8 ].c_str());
            data->opposeCrit= atoi(conVec[ 9 ].c_str());
            data->physicsAttackz= atoi(conVec[ 10 ].c_str());
            data->magicAttackz= atoi(conVec[ 11 ].c_str());
            data->barmorz= atoi(conVec[ 12 ].c_str());
            data->bresistancez= atoi(conVec[ 13 ].c_str());
            data->hpz= atoi(conVec[ 14 ].c_str());
            data->hitz= atoi(conVec[ 15 ].c_str());
            data->dodgez= atoi(conVec[ 16 ].c_str());
            data->critz= atoi(conVec[ 17 ].c_str());
            data->opposeCritz= atoi(conVec[ 18 ].c_str());

			configPlayerManager[data->getIndex()]=data;
		}
	 }
	 fclose(fp);
	 return true;

}


bool ConfigManager::loadItemFile()
{
	return true;

}
bool ConfigManager::loadEquipFile()
{
	return true;

}
bool ConfigManager::loadSoulFile()
{
	return true;

}
bool ConfigManager::loadTreasureFile()
{
	return true;

}


const LevelDataEntry* ConfigManager::getLevelData(uint32 id)
{
    configLevelType::iterator it=configLevelManager.find(id);
    if(it!=configLevelManager.end())
    {
        return (*it).second;
    }
    return NULL;
}
const PlayerDataEntry* ConfigManager::getPlayerData(uint32 id)
{
    configPlayerType::iterator it=configPlayerManager.find(id);
    if(it!=configPlayerManager.end())
    {
        return (*it).second;
    }
    return NULL;
}

const ItemDataEntry* ConfigManager::getItemData(uint32 id)
{
    configItemType::iterator it=configItemManager.find(id);
    if(it!=configItemManager.end())
    {
        return (*it).second;
    }
    return NULL;
}

const EquipDataEntry* ConfigManager::getEquipData(uint32 id)
{
    configEquipType::iterator it=configEquipManager.find(id);
    if(it!=configEquipManager.end())
    {
        return (*it).second;
    }
    return NULL;
}

const SoulDataEntry* ConfigManager::getSoulData(uint32 id)
{
    configSoulType::iterator it=configSoulManager.find(id);
    if(it!=configSoulManager.end())
    {
        return (*it).second;
    }
    return NULL;

}

const TreasureDataEntry* ConfigManager::getTreasureData(uint32 id)
{
	configTreasureType::iterator it=configTreasureManager.find(id);
    if(it!=configTreasureManager.end())
    {
        return (*it).second;
    }
    return NULL;
}

