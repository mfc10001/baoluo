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
			ConfigLevelData *data=new ConfigLevelData();

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
			ConfigPlayerData *data=new ConfigPlayerData();
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
	 return true;
}

const ConfigLevelData* ConfigManager::getLevelData(uint32 id)
{
    configLevelType::iterator it=configLevelManager.find(id);
    if(it!=configLevelManager.end())
    {
        return (*it).second;
    }
    return NULL;
}
const ConfigPlayerData* ConfigManager::getPlayerData(uint32 id)
{
    configPlayerType::iterator it=configPlayerManager.find(id);
    if(it!=configPlayerManager.end())
    {
        return (*it).second;
    }
    return NULL;
}

