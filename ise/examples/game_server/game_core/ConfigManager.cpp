#include "ConfigManager.h"
#include "../tools/CommonTools.h"
#include "../game_define/BaseType.h"
#include "../game_define/Protocol.h"
#include "GamePlayer.h"

bool ConfigManager::loadAllFile()
{

	 CheckCondition(loadLevelFile(),false);

	 std::cout << std::endl << "exp.txt  load success" << std::endl;
	 CheckCondition(loadPLayerFile(),false);
     std::cout << std::endl << "attr.txt  load success" << std::endl;
     CheckCondition(loadItemFile(),false);
     std::cout << std::endl << "item.txt  load success" << std::endl;
     CheckCondition(loadEquipFile(),false);
     std::cout << std::endl << "equip.txt  load success" << std::endl;
     CheckCondition(loadSoulFile(),false);
     std::cout << std::endl << "soul.txt  load success" << std::endl;

     CheckCondition(loadStoreFile(),false);
     std::cout << std::endl << "malls.txt  load success" << std::endl;

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
    memset(buffer,0,BUFFLEN);
    fgets(buffer,BUFFLEN,fp);
	 while(!feof(fp))
	 {
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
		memset(buffer,0,BUFFLEN);
        fgets(buffer,BUFFLEN,fp);
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
    memset(buffer,0,BUFFLEN);
    fgets(buffer,BUFFLEN,fp);
	 while(!feof(fp))
	 {

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
        memset(buffer,0,BUFFLEN);
		fgets(buffer,BUFFLEN,fp);
	 }
	 fclose(fp);
	 return true;

}


bool ConfigManager::loadItemFile()
{
    string path=CONFIG_ROOT_PATH;
	path.append("item.txt");

	FILE * fp=fopen(path.c_str(),"r");
 	if(!fp)
 	{
		return false;
	}

	char buffer[BUFFLEN];
    uint32 expline=3;
    memset(buffer,0,BUFFLEN);
    fgets(buffer,BUFFLEN,fp);
	 while(!feof(fp))
	 {

		if(expline!=0)
		{
            expline--;
            continue;
		}
		StrContaonType conVec;
		CommonTools::split(buffer,"\t",conVec);
		if(!conVec.empty()&&conVec.size()!=10)
		{
			return false;
		}
		{

			ItemDataEntry *data=new ItemDataEntry();
            data->itemid = atoi(conVec[ 0 ].c_str());
            memcpy(data->name,conVec[ 1 ].c_str(),conVec[ 1 ].length());
            data->quality = atoi(conVec[ 2 ].c_str());
            data->type = atoi(conVec[ 3 ].c_str());
            data->level = atoi(conVec[ 4 ].c_str());
            data->use_type = atoi(conVec[ 5 ].c_str());
            data->effect = atoi(conVec[ 6 ].c_str());
            data->cd = atoi(conVec[ 7 ].c_str());
            data->add_max = atoi(conVec[ 8 ].c_str());
			configItemManager[data->getIndex()]=data;
		}
        memset(buffer,0,BUFFLEN);
		fgets(buffer,BUFFLEN,fp);
	 }
	 fclose(fp);


	return true;

}
bool ConfigManager::loadEquipFile()
{
    string path=CONFIG_ROOT_PATH;
	path.append("equip.txt");

	FILE * fp=fopen(path.c_str(),"r");
 	if(!fp)
 	{
		return false;
	}

	char buffer[BUFFLEN];
    uint32 expline=3;
    memset(buffer,0,BUFFLEN);
    fgets(buffer,BUFFLEN,fp);
	 while(!feof(fp))
	 {

		if(expline!=0)
		{
            expline--;
            continue;
		}
		StrContaonType conVec;
		CommonTools::split(buffer,"\t",conVec);
		if(!conVec.empty()&&conVec.size()!=17)
		{
			return false;
		}
		{

			EquipDataEntry *data=new EquipDataEntry();
            data->itemid = atoi(conVec[ 0 ].c_str());
            memcpy(data->name,conVec[ 1 ].c_str(),conVec[ 1 ].length());
            data->profession = atoi(conVec[ 2 ].c_str());
            data->part = atoi(conVec[ 3 ].c_str());
            data->grade = atoi(conVec[ 4 ].c_str());
            data->quality = atoi(conVec[ 5 ].c_str());
            data->icon = atoi(conVec[ 6 ].c_str());
            data->physicsAttack = atoi(conVec[ 7 ].c_str());
            data->magicAttack = atoi(conVec[ 8 ].c_str());
            data->n_barmor = atoi(conVec[ 9 ].c_str());
            data->bresistance = atoi(conVec[ 10 ].c_str());
            data->hp = atoi(conVec[ 11 ].c_str());
            data->hit = atoi(conVec[ 12 ].c_str());
            data->dodge = atoi(conVec[ 13 ].c_str());
            data->n_crit = atoi(conVec[ 14 ].c_str());
            data->n_opposeCrit = atoi(conVec[ 15 ].c_str());

			configEquipManager[data->getIndex()]=data;
		}
        memset(buffer,0,BUFFLEN);
		fgets(buffer,BUFFLEN,fp);
	 }
	 fclose(fp);


	return true;

}
bool ConfigManager::loadSoulFile()
{
     string path=CONFIG_ROOT_PATH;
	path.append("soul.txt");

	FILE * fp=fopen(path.c_str(),"r");
 	if(!fp)
 	{
		return false;
	}

	char buffer[BUFFLEN];
    uint32 expline=3;
    memset(buffer,0,BUFFLEN);
    fgets(buffer,BUFFLEN,fp);
	 while(!feof(fp))
	 {

		if(expline!=0)
		{
            expline--;
            continue;
		}
		StrContaonType conVec;
		CommonTools::split(buffer,"\t",conVec);
		if(!conVec.empty()&&conVec.size()!=7)
		{
			return false;
		}
		{

			SoulDataEntry *data=new SoulDataEntry();
            data->itemid = atoi(conVec[ 0 ].c_str());
            memcpy(data->name,conVec[ 1 ].c_str(),conVec[ 1 ].length());
            data->quality = atoi(conVec[ 2 ].c_str());
            data->type = atoi(conVec[ 3 ].c_str());
            data->useType = atoi(conVec[ 4 ].c_str());
            data->effect = atoi(conVec[ 5 ].c_str());
			configSoulManager[data->getIndex()]=data;
		}
        memset(buffer,0,BUFFLEN);
		fgets(buffer,BUFFLEN,fp);
	 }
	 fclose(fp);

	return true;

}
bool ConfigManager::loadTreasureFile()
{
	string path=CONFIG_ROOT_PATH;
	path.append("treasure.txt");

	FILE * fp=fopen(path.c_str(),"r");
 	if(!fp)
 	{
		return false;
	}

	char buffer[BUFFLEN];
    uint32 expline=3;
    memset(buffer,0,BUFFLEN);
    fgets(buffer,BUFFLEN,fp);
	 while(!feof(fp))
	 {

		if(expline!=0)
		{
            expline--;
            continue;
		}
		StrContaonType conVec;
		CommonTools::split(buffer,"\t",conVec);
		if(!conVec.empty()&&conVec.size()!=10)
		{
			return false;
		}
		{

			TreasureDataEntry *data=new TreasureDataEntry();
            data->itemid = atoi(conVec[ 0 ].c_str());
            memcpy(data->name,conVec[ 1 ].c_str(),conVec[ 1 ].length());
            data->part = atoi(conVec[ 2 ].c_str());
            data->quality = atoi(conVec[ 3 ].c_str());
            data->harm = atoi(conVec[ 4 ].c_str());
            data->missHarm = atoi(conVec[ 5 ].c_str());
            data->attackSpeed = atoi(conVec[ 6 ].c_str());
            data->speed = atoi(conVec[ 7 ].c_str());
			configTreasureManager[data->getIndex()]=data;
		}
        memset(buffer,0,BUFFLEN);
		fgets(buffer,BUFFLEN,fp);
    }
	 fclose(fp);

	return true;

}

bool ConfigManager::loadStoreFile()
{
    string path=CONFIG_ROOT_PATH;
	path.append("malls.txt");

	FILE * fp=fopen(path.c_str(),"r");
 	if(!fp)
 	{
		return false;
	}

	char buffer[BUFFLEN];
    uint32 expline=3;
    memset(buffer,0,BUFFLEN);
    fgets(buffer,BUFFLEN,fp);
	 while(!feof(fp))
	 {

		if(expline!=0)
		{
            expline--;
            continue;
		}
		StrContaonType conVec;
		CommonTools::split(buffer,"\t",conVec);
		if(!conVec.empty()&&conVec.size()!=9)
		{
			return false;
		}
		{

			StoreDataEntry *data=new StoreDataEntry();
            data->id = atoi(conVec[ 0 ].c_str());
            data->itemId = atoi(conVec[ 1 ].c_str());
            data->itemType = atoi(conVec[ 2 ].c_str());
            data->itemCount = atoi(conVec[ 3 ].c_str());
            data->price = atoi(conVec[ 4 ].c_str());
            data->discount = atoi(conVec[ 5 ].c_str());
            data->hot = atoi(conVec[ 6 ].c_str());
            data->buyCount = atoi(conVec[ 7 ].c_str());
            data->limit = atoi(conVec[ 8 ].c_str());
			configStoreManager[data->getIndex()]=data;
		}
        memset(buffer,0,BUFFLEN);
		fgets(buffer,BUFFLEN,fp);
    }
	 fclose(fp);

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
const StoreDataEntry* ConfigManager::getStoreData(uint32 id)
{
    configStoreType::iterator it=configStoreManager.find(id);
    if(it!=configStoreManager.end())
    {
        return (*it).second;
    }
    return NULL;
}
